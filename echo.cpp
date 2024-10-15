#include <iostream>
#include <vector>
#include <memory>

#define echo(x) std::cout << x << std::endl

// کلاس مدیریت حافظه
class MemoryManager {
public:
    std::vector<std::unique_ptr<void, void(*)(void*)>> pointers;

    template<typename T>
    T* allocate(size_t size) {
        T* ptr = new T[size];  // استفاده از new به جای malloc
        if (ptr) {
            pointers.push_back({ ptr, [](void* p) { delete[] static_cast<T*>(p); } }); // استفاده از delete
        } else {
            std::cerr << "Memory allocation failed" << std::endl;
        }
        return ptr;
    }

    void free_all() {
        pointers.clear();
    }

    ~MemoryManager() {
        free_all();
    }
};

// ایجاد شیء سراسری MemoryManager
MemoryManager globalManager;

// کلاس ManagedVar که حافظه را مدیریت می‌کند
template<typename T>
class ManagedVar {
public:
    T* data;

    // سازنده تبدیل که امکان مقداردهی اولیه با استفاده از '=' را فراهم می‌کند
    ManagedVar(T value) {
        data = globalManager.allocate<T>(1); // تخصیص حافظه برای یک مقدار
        *data = value;
    }

    // اپراتور تبدیل به نوع
    operator T&() {
        return *data;
    }

    // دسترسی به پوینتر
    T* operator->() {
        return data;
    }

    // اپراتور تخصیص برای مقداردهی بعد از ایجاد شیء
    ManagedVar& operator=(T value) {
        *data = value;
        return *this;
    }
};

int main() {
    // حالا به صورت ساده‌تر متغیرها تعریف می‌شوند
    ManagedVar<int> arr1 = 10;       // متغیر int با مقدار اولیه 10
    ManagedVar<double> arr2 = 3.14;  // متغیر double با مقدار اولیه 3.14

    // دسترسی به مقادیر متغیرها
    echo("arr1: " << arr1);
    echo("arr2: " << arr2);

    // تغییر مقادیر متغیرها بدون نیاز به *
    arr1 = 20; // تغییر مقدار به سادگی
    arr2 = 6.28;

    echo("arr1 (after modification): " << arr1);
    echo("arr2 (after modification): " << arr2);

    // حافظه به صورت خودکار در پایان برنامه آزاد می‌شود
    return 0;
}