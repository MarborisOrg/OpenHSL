#include <iostream>
#include <omp.h>
#include <thread>

void func() {
        std::cout << "Function is running in thread " << omp_get_thread_num() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
}

void func2() {
        std::cout << "Function is running in thread " << omp_get_thread_num() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
}

void func3() {
        std::cout << "Function is running in thread " << omp_get_thread_num() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {
    omp_set_dynamic(0);     // Disable dynamic adjustment of the number of threads
    omp_set_num_threads(8); // Set number of threads

    #pragma omp parallel
    {
        #pragma omp single
        {
            func();
        }

        #pragma omp single
        {
            func2();
        }

        #pragma omp single
        {
            func3();
        }

    }

    std::cout << "Function has completed." << std::endl;
    return 0;
}
