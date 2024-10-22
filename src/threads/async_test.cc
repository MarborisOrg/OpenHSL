#include <iostream>
#include <future>
#include <thread>
#include <chrono>

class AsyncTaskClass {
public:
    // متد برای اضافه کردن تابع و برگرداندن future
    template<typename Func>
    auto operator<<(Func&& func) {
        return std::async(std::launch::async, std::forward<Func>(func));
    }
};

AsyncTaskClass async;

void async_test() {
    // ذخیره futures برای استفاده از get()
    auto futureA = async << []() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Function a is running\n";
    };

    auto futureB = async << []() {
        std::cout << "Function b is running\n";
    };

    auto futureC = async << []() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Function c is running\n";
    };

    auto futureD = async << []() {
        std::cout << "Function d is running\n";
    };

    // استفاده از get() بر روی futures
    // futureA.get();
    // futureB.get();
    // futureC.get();
    // futureD.get();
}

int main() {
    async_test();
    return 0;
}
