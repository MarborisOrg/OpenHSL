#include <iostream>
#include <uv.h>
#include <chrono>

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
    executor.execute([]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Function a is running\n";
    });

    executor.execute([]() {
        std::cout << "Function b is running\n";
        // std::this_thread::sleep_for(std::chrono::seconds(5));
    });

    executor.execute([]() {
        // std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Function c is running\n";
    });

    executor.execute([]() {
        std::cout << "Function d is running\n";
    });

    executor.execute([]() {
        std::cout << "Function e is running\n";
    });

    // Keep the main thread alive long enough for the tasks to complete
    // std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
