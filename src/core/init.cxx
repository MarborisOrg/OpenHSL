// ===========================================================
#pragma once
#include "../core/cc.hpp"
// ===========================================================

class InitClass {
public:
    InitClass() {
        echo("Hello And Welcome.");
        omp_set_dynamic(0);     // Disable dynamic adjustment of the number of threads
        omp_set_num_threads(std::thread::hardware_concurrency() * 2); // Set number of threads
        echo("Set threads to: " << std::thread::hardware_concurrency() * 2);
    }
};

static InitClass init;
