#include <taskflow/taskflow.hpp>
#include <memory>
#include <functional>
#include <iostream>

tf::Executor executor;

void task_function() {
    // کارهایی که باید انجام شود
}

int main() {
    for (size_t i = 0; i < 30000000; /* 30 million nested task */ i++) {
        // استفاده از shared_ptr به جای unique_ptr
        auto task = std::make_shared<std::function<void()>>([=]() {
            task_function();
        });

        executor.silent_async([task]() mutable {
            (*task)();
        });
    }

    executor.wait_for_all();
    return 0;
}
