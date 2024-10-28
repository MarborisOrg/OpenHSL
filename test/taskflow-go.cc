#include <taskflow/taskflow.hpp>

int main() {
    tf::Taskflow taskflow;
    tf::Executor executor;

    taskflow.emplace([]() { std::cout << "Hello, Taskflow!" << std::endl; });

    executor.run(taskflow).wait();
    return 0;
}
