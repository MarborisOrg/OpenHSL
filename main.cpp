#include <iostream>
#include <memory>

#define echo(x) std::cout << x << std::endl

#define Main int main

template <typename T>
class ManagedVar
{
public:
    std::unique_ptr<T> data; // استفاده از unique_ptr به جای پوینتر خام

    ManagedVar(T value)
    {
        data = std::make_unique<T>(); // تخصیص حافظه به صورت امن
        *data = value;
    }

    T &operator*()
    {
        return *data;
    }

    T *operator->()
    {
        return data.get();
    }

    ManagedVar &operator=(T value)
    {
        *data = value;
        return *this;
    }
};

Main()
{
    ManagedVar<int> arr1 = 10;
    ManagedVar<double> arr2 = 3.14;

    echo("arr1: " << *arr1);
    echo("arr2: " << *arr2);

    arr1 = 20;
    *arr2 = 6.28;

    echo("arr1 (after modification): " << *arr1);
    echo("arr2 (after modification): " << *arr2);

    return 0;
}
