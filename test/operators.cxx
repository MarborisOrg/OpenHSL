#include <iostream>

int operator"" _go(unsigned long long inch)
{
    
    
    return inch * 96;
} //_go = int*96


int main()
{
    int inches = 3_go;             // 3 * 96
    std::cout << inches << std::endl; // 288
}
