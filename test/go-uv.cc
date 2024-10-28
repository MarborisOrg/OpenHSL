#include <iostream>
#include <uv.h>
#include <thread>

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
        req->data = new Func(std::forward<Func>(func));

        uv_queue_work(loop, req, [](uv_work_t *req)
                      {
           
            auto func = static_cast<Func*>(req->data);
            (*func)();
            delete func; }, [](uv_work_t *req, int)
                      { delete req; });

        uv_run(loop, UV_RUN_NOWAIT);
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
    const size_t task_count = 100000;

    for (size_t i = 0; i < task_count; i++)
    {
        executor.execute([=]()
                         {
            executor.execute([=]() {
               
            });
            executor.execute([=]() {
               
            });
            });
    }

    std::cout << "All tasks submitted.\n";

    return 0;
}
