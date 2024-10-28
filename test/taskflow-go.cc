#include <taskflow/taskflow.hpp>

#define lm []()
#define esa executor.silent_async

tf::Executor executor;

int main()
{

    for (size_t i = 0; i < 30000000; i++)
    {
        esa(lm { esa(lm { esa(lm { esa(lm { esa(lm { esa(lm{ }); }); }); }); }); });
    }

    executor.wait_for_all();
    return 0;
}
