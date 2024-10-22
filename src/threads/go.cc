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
                func();
            }
        return *this;
    }

    template <typename Func>
    // Running tasks on a thread with taskwait
    GoRoutine &operator<<(Func &&func)
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

GoRoutine Go; // Parallel execution of tasks in a chain with OpenMP.

// تست GoRoutine با OpenMP
void go_test()
{
    Go << [] { /* کاری انجام دهید */ }
       << [] { /* کار دیگری انجام دهید */ }
       << [] { /* یک کار دیگر انجام دهید */ };

    std::cout << "Waiting for all tasks to complete...\n";
    Go.wait();

    Go >> [] {
        // no waiting
    };

    std::cout << "All tasks completed.\n";
}

void omp_test()
{
    // تنظیم تعداد رشته‌های OpenMP
    omp_set_dynamic(0);     // Disable dynamic adjustment of the number of threads
    omp_set_num_threads(4); // Set number of threads

    go_test();
}
