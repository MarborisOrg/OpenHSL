// ===========================================================
#pragma once
#include "../core/cc.hpp"
// ===========================================================

class asyncTaskClass {
public:
    template<typename Func>
    asyncTaskClass& operator<<(Func&& func) {
        std::async(std::launch::async, std::forward<Func>(func));
        return *this;
    }
};

asyncTaskClass async;

int async_test(){

    async << []() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Function a is running\n";
    } << []() {
        std::cout << "Function b is running\n";
    } << []() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Function c is running\n";
    } << []() {
        std::cout << "Function d is running\n";
    };

    return 0;
}