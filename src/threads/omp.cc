// OpenMP

// ===========================================================
#pragma once
#include "../core/cc.hpp"
// ===========================================================

class FireAndForget
{
public:
    template <typename Func>
    FireAndForget &operator>>(Func &&func)
    {
        #pragma omp parallel
        #pragma omp single
        {
            #pragma omp task
            func();
        }
        return *this;
    }

    void wait()
    {
        #pragma omp taskwait
    }
};

// تست FireAndForget با OpenMP
void fire_test()
{
    FireAndForget fire;

    fire >> []
    {
        std::cout << "Task 1 executed\n";
    } >> []
    {
        std::cout << "Task 2 executed\n";
    } >> []
    {
        std::cout << "Immediate Task executed\n";
    };

    // صبر کردن برای اتمام تسک‌ها
    std::cout << "Waiting for all tasks to complete...\n";
    fire.wait();

    std::cout << "All tasks completed.\n";
}

void omp_test()
{
    // تنظیم تعداد رشته‌های OpenMP
    omp_set_dynamic(0);     // Disable dynamic adjustment of the number of threads
    omp_set_num_threads(4); // Set number of threads

    fire_test();
}
