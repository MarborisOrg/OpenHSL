// OpenMP

// ===========================================================
#pragma once
#include "../core/cc.hpp"
// ===========================================================

class GoRoutine
{
public:
    template <typename Func>
    GoRoutine &operator>>(Func &&func)
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

GoRoutine go;

// تست GoRoutine با OpenMP
void go_test()
{
    go >> []
    {
        std::cout << "Task 1 executed\n";
    } >> []
    {
        std::cout << "Task 2 executed\n";
    } >> []
    {
        std::cout << "Immediate Task executed\n";
    };

    std::cout << "Waiting for all tasks to complete...\n";
    go.wait();

    std::cout << "All tasks completed.\n";
}

void omp_test()
{
    // تنظیم تعداد رشته‌های OpenMP
    omp_set_dynamic(0);     // Disable dynamic adjustment of the number of threads
    omp_set_num_threads(4); // Set number of threads

    go_test();
}
