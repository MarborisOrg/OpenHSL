// #include <iostream>
// #include <future>
// #include <vector>
// #include <uv.h>

// class FireAndForget {
// public:
//     FireAndForget() {
//         loop_ = uv_default_loop();
//     }

//     template <typename Func>
//     std::future<void> run(Func&& func) {
//         std::promise<void> promise;
//         auto future = promise.get_future();

//         auto req = new uv_work_t; // Create a new work request

//         // Store the function and promise in a struct to pass to the work callback
//         auto data = new WorkData{ std::move(promise), std::forward<Func>(func) };

//         // Define the work callback
//         uv_queue_work(loop_, req, [](uv_work_t* req) {
//             // Retrieve the data
//             WorkData* data = static_cast<WorkData*>(req->data);
//             try {
//                 // Call the function
//                 data->func();
//                 data->promise.set_value(); // Mark promise as satisfied
//             } catch (const std::exception &e) {
//                 std::cerr << "Exception in task: " << e.what() << '\n';
//                 data->promise.set_exception(std::current_exception());
//             } catch (...) {
//                 std::cerr << "Unknown exception in task.\n";
//                 data->promise.set_exception(std::current_exception());
//             }
//             delete data; // Clean up data after work is done
//             delete req; // Clean up the request
//         }, [](uv_work_t* req, int) {
//             // After work callback, no additional cleanup needed here
//         });

//         // Attach the data to the work request
//         req->data = data;

//         return future;
//     }

//     void waitForAllTasks() {
//         uv_run(loop_, UV_RUN_DEFAULT);
//     }

// private:
//     struct WorkData {
//         std::promise<void> promise; // Promise to fulfill
//         std::function<void()> func; // Task function
//     };

//     uv_loop_t *loop_;
// };

// // Example usage
// void fire_test(FireAndForget &fire) {
//     fire.run([]() {
//         uv_sleep(2000); // Sleep for 2 seconds
//         std::cout << "Task 1 executed\n";
//     });

//     fire.run([]() {
//         uv_sleep(1000); // Sleep for 1 second
//         std::cout << "Task 2 executed\n";
//     });

//     fire.run([]() {
//         std::cout << "Immediate Task executed\n";
//     });

//     fire.run([]() {
//         uv_sleep(3000); // Sleep for 3 seconds
//         std::cout << "Task 3 executed\n";
//     });
// }

// int main() {
//     FireAndForget fire;

//     for (size_t i = 0; i < 10; i++) {
//         fire.run([&fire]() {
//             fire_test(fire); // Pass the FireAndForget instance
//         });
//     }

//     fire.waitForAllTasks(); // Wait for all tasks to complete
//     return 0;
// }
