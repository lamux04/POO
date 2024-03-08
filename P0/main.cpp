#include <string>
#include <iostream>
#include <stddef.h>
#include "fecha.hpp"
#include "cadena.hpp"


int main()
{
    using namespace std;
    const Fecha f(3, 3, 2024);
    const Fecha g((f.operator -(5)));
    cout << g;

}