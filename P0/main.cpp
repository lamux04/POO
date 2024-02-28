#include <string>
#include <iostream>
#include <stddef.h>
#include "Fecha.hpp"
#include "Cadena.hpp"

int main()
{
    using namespace std;
    try
    {
        Fecha t("02/05/2008");
        t -= 10;
        ++t;
        t++;
        t.imprimir();
    }
    catch (Fecha::Invalida& e)
    {
        std::cerr << e.por_que() << std::endl;
    }

}