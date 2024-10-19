// OpenMP

    // #pragma omp parallel
    // {
    //     #pragma omp single // فقط یک رشته این بخش را اجرا می‌کند
    //     {
    //         std::vector<omp_task_t> tasks; // لیست کارها

    //         for (int i = 0; i < 5; ++i) {
    //             #pragma omp task // ایجاد یک کار جدید
    //             taskFunction(i);
    //         }
    //         #pragma omp taskwait // منتظر ماندن برای اتمام کارها
    //     }
    // }

// ===========================================================
#pragma once
#include "../core/cc.hpp"
// ===========================================================

class FireAndForget
{
public:
    // اجرای تسک با استفاده از OpenMP
    template <typename Func>
    FireAndForget &operator>>(Func &&func)
    {
        #pragma omp task
        {
            func();
        }
        return *this;
    }

    // انتظار برای تمام تسک‌ها
    void wait()
    {
        #pragma omp taskwait
    }
};

// تست FireAndForget با OpenMP
void fire_test()
{
    FireAndForget fire;

    fire >> [] {
        std::cout << "Task 1 executed\n";
    } >> [] {
        std::cout << "Task 2 executed\n";
    } >> [] {
        std::cout << "Immediate Task executed\n";
    };

    // صبر کردن برای اتمام تسک‌ها
    // std::cout << "Waiting for all tasks to complete...\n";
    // fire.wait();

    std::cout << "All tasks completed.\n";
}

int main() {
    // تنظیم تعداد رشته‌های OpenMP
    omp_set_dynamic(0); // Disable dynamic adjustment of the number of threads
    omp_set_num_threads(4); // Set number of threads

    fire_test();
    return 0;
}