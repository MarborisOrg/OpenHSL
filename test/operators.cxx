#include <iostream>

class InitClass {
public:
    InitClass() {
        std::cout << "Initialization code executed!" << std::endl;
    }
};

// شیء استاتیک از کلاس InitClass
static InitClass init;

int main() {
    std::cout << "Main function executed." << std::endl;
    return 0;
}
