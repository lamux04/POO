#include <string>
#include <iostream>
#include <stddef.h>
#include "fecha.hpp"
#include "cadena.hpp"


int main()
{
    using namespace std;
    Cadena c;
    std::cin >> c;
    std::cout << "Palabra 1: " << c << "\nCter. actual: '"
        << static_cast<char>(std::cin.peek()) << "'" << std::endl;
    std::cin >> c;
    std::cout << "Palabra 2: " << c << std::endl;

}