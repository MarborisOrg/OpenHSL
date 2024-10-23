#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

class jthreadTaskClass
{
public:
    template <typename Func>
    jthreadTaskClass &operator<<(Func &&func)
    {
        std::jthread(std::forward<Func>(func)).detach();
        return *this;
    }
};

jthreadTaskClass go;

int main()
{
    go << []()
    {
        go << []()
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "Function a is running\n";
        } << []()
        {
            std::cout << "Function b is running\n";
            std::this_thread::sleep_for(std::chrono::seconds(5));
        } << []()
        {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "Function c is running\n";
        } << []()
        {
            std::cout << "Function d is running\n";
        };
    };

    go << []()
    {
        std::cout << "Function e is running\n";
    };

    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}