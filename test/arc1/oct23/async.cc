#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void func() {
    std::cout << "Function 1 is running in thread " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void func2() {
    std::cout << "Function 2 is running in thread " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void func3() {
    std::cout << "Function 3 is running in thread " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {
    // Launch functions asynchronously
    auto future1 = std::async(std::launch::async, func);
    auto future2 = std::async(std::launch::async, func2);
    auto future3 = std::async(std::launch::async, func3);

    // Wait for all futures to complete
    future1.get();
    future2.get();
    future3.get();

    return 0;
}
