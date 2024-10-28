#include <iostream>
#include <uv.h>
#include <thread>
#include <vector>
#include <memory>
#include <functional> // اضافه کردن هدر

class TaskExecutor
{
public:
    TaskExecutor()
    {
        loop = uv_default_loop();
    }

    template <typename Func>
    void execute(Func &&func)
    {
        uv_work_t *req = new uv_work_t;
        req->data = new std::function<void()>(std::forward<Func>(func)); // مشخص کردن نوع

        uv_queue_work(loop, req,
                      [](uv_work_t *req)
                      {
                          auto func = static_cast<std::function<void()>*>(req->data);
                          (*func)();
                          delete func;
                      },
                      [](uv_work_t *req, int)
                      {
                          delete req;
                      });
    }

    void cleanup()
    {
        uv_run(loop, UV_RUN_DEFAULT);
        uv_loop_close(loop);
    }

    ~TaskExecutor()
    {
        cleanup();
    }

private:
    uv_loop_t *loop;
};

TaskExecutor executor;

int main()
{
    const size_t task_count = 1000000;

    for (size_t i = 0; i < task_count; i++)
    {
        executor.execute([=]()
                         {
            // انجام کارها
            });
            executor.execute([=]()
                         {
            // انجام کارها
            });
    }

    std::cout << "All tasks submitted\n";

    executor.cleanup(); // اطمینان حاصل کنید که cleanup بعد از ارسال همه تسک‌ها انجام شود

    return 0;
}
