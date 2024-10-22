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
};

GoRoutine Go; // Parallel execution of tasks in a chain with OpenMP.

void go_test()
{
    Go >> [] {};
}
