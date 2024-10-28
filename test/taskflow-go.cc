#include <taskflow/taskflow.hpp>

tf::Executor executor;

int main()
{

    // create asynchronous tasks directly from an executor
    // std::future<int> future = executor.async([](){
    // std::cout << "async task returns 1\n";
    // return 1;
    // });

    for (size_t i = 0; i < 1000000; i++)
    {
        executor.silent_async([]()
                              { executor.silent_async([]()
                                                      { executor.silent_async([]() {}); }); });
    }

    // create asynchronous tasks with dynamic dependencies
    // tf::AsyncTask A = executor.silent_dependent_async([](){ printf("A\n"); });
    // tf::AsyncTask B = executor.silent_dependent_async([](){ printf("B\n"); }, A);
    // tf::AsyncTask C = executor.silent_dependent_async([](){ printf("C\n"); }, A);
    // tf::AsyncTask D = executor.silent_dependent_async([](){ printf("D\n"); }, B, C);

    executor.wait_for_all();
    return 0;
}
