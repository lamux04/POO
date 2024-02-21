#include <iostream>
#include <ctime>

int main()
{
    auto t = std::time(nullptr);
    std::cout << std::localtime(&t);
}