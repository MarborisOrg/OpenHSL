// OpenMP (fire)

// ===========================================================
#pragma once
#include "../core/cc.hpp"
// ===========================================================

class FireAndForget {
public:
    template <typename Func>
    FireAndForget &operator>>(Func &&func)
    {
        #pragma omp parallel
        #pragma omp single
        {
            func();
        }
        return *this;
    }
};

FireAndForget fire; // No waiter

// تست FireAndForget با OpenMP
void fire_test()
{

    fire lam
    {
        std::cout << "Task 1 executed\n";
    } lam
    {
        std::cout << "Task 2 executed\n";
    } lam
    {
        std::cout << "Immediate Task executed\n";
    };
}

void omp_test()
{
    // تنظیم تعداد رشته‌های OpenMP
    omp_set_dynamic(0);     // Disable dynamic adjustment of the number of threads
    omp_set_num_threads(4); // Set number of threads

    fire_test();
}
