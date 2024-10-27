#include <iostream>
#include <uv.h>
#include <functional>

class uvTaskClass
{
public:
    uvTaskClass& operator<<(std::function<void()> func)
    {
        addTask(func);
        return *this;
    }

    void addTask(std::function<void()> func)
    {
        uv_work_t* req = new uv_work_t;
        req->data = new std::function<void()>(func);
        uv_queue_work(uv_default_loop(), req, [](uv_work_t* req) {
            auto func = static_cast<std::function<void()>*>(req->data);
            (*func)();
            delete func;
        }, [](uv_work_t* req, int status) {
            delete req;
        });
    }
};

uvTaskClass go;

int main()
{
    go << []() {
        std::cout << "Function top is running\n";
        go << []() {
            std::cout << "Function a is running\n";
        } << []() {
            std::cout << "Function b is running\n";
        } << []() {
            std::cout << "Function c is running\n";
        } << []() {
            std::cout << "Function d is running\n";
        };
        std::cout << "Function end is running\n";
    };

    go << []() {
        std::cout << "Function e is running\n";
    };

    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    return 0;
}
