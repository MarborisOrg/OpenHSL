#include <iostream>
#include <uv.h>
#include <thread> // Include this header for std::this_thread

class TaskExecutor {
public:
    TaskExecutor() {
        // Initialize libuv loop
        loop = uv_default_loop();
    }

    template <typename Func>
    void execute(Func&& func) {
        uv_work_t* req = new uv_work_t;
        req->data = new Func(std::forward<Func>(func)); // Store the function

        // Queue the work
        uv_queue_work(loop, req, [](uv_work_t* req) {
            // This function runs in the thread pool
            auto func = static_cast<Func*>(req->data);
            (*func)(); // Call the task
            delete func; // Clean up the function
        }, [](uv_work_t* req, int) {
            // This function runs in the main loop after the task is done
            delete req; // Clean up the request
        });

        // Run the loop immediately to execute tasks
        uv_run(loop, UV_RUN_NOWAIT);
    }

private:
    uv_loop_t* loop;
};

TaskExecutor executor;

int main() {

    for (size_t i = 0; i < 100000; i++)
    {
        executor.execute([]() {
            executor.execute([]() {
                executor.execute([]() {});
            });
            executor.execute([]() {});
        });
    }

    std::cout << "Function e is running\n";

    return 0;
}
