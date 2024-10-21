#include <iostream>
#include <utility> // برای std::forward
#include <omp.h>   // برای OpenMP

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

// مثال از استفاده
void exampleFunction() {
    std::cout << "Hello from thread " << omp_get_thread_num() << std::endl;
}

int main() {
    FireAndForget f;
    omp_set_dynamic(0);     // Disable dynamic adjustment of the number of threads
    omp_set_num_threads(4); // Set number of threads

    f >> exampleFunction; // تابع را به عملگر ارسال می‌کنیم
    return 0;
}
