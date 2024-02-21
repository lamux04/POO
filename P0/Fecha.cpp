#include "Fecha.hpp"
#include <string>
#include <chrono>

// Declaracion constantes
const int Fecha::AnnoMaximo(2037);
const int Fecha::AnnoMinimo(1902);

// Los parametros por defecto solo en la definicion
Fecha::Fecha(int d /* = 0 */, int m /* = 0 */, int a /* = 0 */) : dia_(d), mes_(m), anno_(a)
{
    if (d != 0 && m != 0 && a != 0)
        validar();
}

void Fecha::validar()
{
    if (anno_ < AnnoMinimo || anno_ > AnnoMaximo)
        // Excepcion año no válido
        throw;

    if (mes_ <= 0 || mes_ >= 13)
        // Excepcion mes no valido
        throw;

    if (dia_ <= 0 || dia_ >= 32)
        // Dia invalido
        throw;

    if (mes_ == 2)
    {
        if ((anno_ % 4 == 0 && anno_ % 100 != 0) || anno_ % 400 == 0)
        {
            if (dia_ >= 30) // Dia invalido
                throw;
        } else
        {
            if (dia_ >= 29) // Dia invalido
                throw;
        }
    }

    if (mes_ == 4 || mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11)
        if (dia_ >= 31) // Dia invalido
            throw;
}