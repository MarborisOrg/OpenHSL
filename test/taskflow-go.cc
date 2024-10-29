#include <taskflow/taskflow.hpp>
#include <memory>
#include <functional>
#include <iostream>

class TaskGnrt
{
public:
    template <typename Func>
    TaskGnrt &operator<<(Func &&func)
    {
        auto task = std::make_shared<std::function<void()>>([=]() {
            func();
        });

        executor.silent_async([task]() mutable {
            (*task)();
        });
        return *this;
    }

    void wait() {
        executor.wait_for_all();
    }

    private:
        tf::Executor executor;
};

TaskGnrt go;

void task_function() {
}

int main() {
    for (size_t i = 0; i < 30000000; i++) {
        go << [=](){
            go << [=](){
            go << [=](){
            go << [=](){
            go << [=](){
            
        };
        };
        };
        };
        };
    }

    go.wait();
    return 0;
}
