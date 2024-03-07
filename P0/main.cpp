#include <string>
#include <iostream>
#include <stddef.h>
#include "fecha.hpp"
#include "cadena.hpp"


int main()
{
    using namespace std;
    Cadena s1(20, '['), s2(20, ']'),
        c1(" !Bravo "), c2("a "), c3("todos "),
        s = s1 + c1;
}