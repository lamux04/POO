#include <string.h>
#include <ctime>
#include <stdio.h>
#include <iostream>

#include "Fecha.hpp"

// Declaracion constantes
const int Fecha::AnnoMaximo(2037);
const int Fecha::AnnoMinimo(1902);



// Los parametros por defecto solo en la definicion
Fecha::Fecha(int d /* = 0 */, int m /* = 0 */, int a /* = 0 */) : dia_(d), mes_(m), anno_(a), actual(false)
{
    if (d != 0 && m != 0 && a != 0)
        validar();

    else
    {
        // Calculamos el tiempo del sistema
        std::time_t tiempo_calendario = std::time(nullptr);
        std::tm *tiempo_descompuesto = std::localtime(&tiempo_calendario);

        if (dia_ == 0) dia_ = tiempo_descompuesto->tm_mday;
        if (mes_ == 0) mes_ = tiempo_descompuesto->tm_mon + 1;
        if (anno_ == 0) anno_ = tiempo_descompuesto->tm_year + 1900;

        validar();
    }
}


Fecha::Fecha(char *cad) : dia_(0), mes_(0), anno_(0), actual(false)
{
    sscanf(cad, "%d/%d/%d", &dia_, &mes_, &anno_);

    // Calculamos el tiempo del sistema
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

    if (dia_ == 0) dia_ = tiempo_descompuesto->tm_mday;
    if (mes_ == 0) mes_ = tiempo_descompuesto->tm_mon + 1;
    if (anno_ == 0) anno_ = tiempo_descompuesto->tm_year + 1900;


    validar();
}

void Fecha::aumentar_dias(int n)
{
    struct std::tm nuevo_tm;

    nuevo_tm.tm_sec = 0;    // Segundos
    nuevo_tm.tm_min = 0;    // Minutos
    nuevo_tm.tm_hour = 0;   // Horas
    nuevo_tm.tm_mday = dia_;
    nuevo_tm.tm_mon = mes_ - 1;
    nuevo_tm.tm_year = anno_ - 1900;

    std::time_t tiempo;
    tiempo = mktime(&nuevo_tm); // Normalizamos la fecha
    tiempo += 60 * 60 * 24 * n;
    std::tm *fecha_normalizada = std::localtime(&tiempo);

    dia_ = fecha_normalizada->tm_mday;
    mes_ = fecha_normalizada->tm_mon + 1;
    anno_ = fecha_normalizada->tm_year + 1900;
}

typename Fecha::Fecha& Fecha::operator+=(int n)
{
    aumentar_dias(n);
    validar();
    actual = false;
    return *this;
}

typename Fecha::Fecha& Fecha::operator-=(int n)
{
    aumentar_dias(-n);
    validar();
    actual = false;
    return *this;
}

typename Fecha::Fecha& Fecha::operator++()
{
    aumentar_dias(1);
    validar();
    actual = false;
    return *this;
}

typename Fecha::Fecha& Fecha::operator++(int)
{
    Fecha copia{ *this };
    aumentar_dias(1);
    validar();
    actual = false;
    return copia;
}

typename Fecha::Fecha& Fecha::operator--()
{
    aumentar_dias(-1);
    validar();
    actual = false;
    return *this;
}

typename Fecha::Fecha& Fecha::operator--(int)
{
    Fecha copia{ *this };
    aumentar_dias(-1);
    validar();
    actual = false;
    return copia;
}

Fecha& operator+(Fecha A, int n)
{
    A.aumentar_dias(n);
    A.validar();
    return A;
}

Fecha& operator-(Fecha A, int n)
{
    A.aumentar_dias(-n);
    A.validar();
    return A;
}

bool operator<(const Fecha& A, const Fecha& B)
{
    if (A.anno() != B.anno()) return A.anno() < B.anno();
    else if (A.mes() != B.mes()) return A.mes() < B.mes();
    else return A.dia() < B.dia();
}

bool operator==(const Fecha& A, const Fecha& B)
{
    if (A.anno() != B.anno()) return false;
    else if (A.mes() != B.mes()) return false;
    else return A.dia() == B.dia();
}

bool operator>(const Fecha& A, const Fecha& B)
{
    return B < A;
}

bool operator!=(const Fecha& A, const Fecha& B)
{
    return !(A == B);
}

bool operator<=(const Fecha& A, const Fecha& B)
{
    return !(B < A);
}

bool operator>=(const Fecha& A, const Fecha& B)
{
    return !(A < B);
}

Fecha::operator const char* () const
{
    if (!actual)
    {
        char *dia[] = {
            "domingo",
            "lunes",
            "martes",
            "miércoles",
            "jueves",
            "viernes",
            "sábado"
        };

        char *mes[] = {
            "enero",
            "febrero",
            "marzo",
            "abril",
            "mayo",
            "junio",
            "julio",
            "agosto",
            "septiembre",
            "octubre",
            "noviembre",
            "diciembre"
        };

        struct std::tm * nuevo_tm = new std::tm;

        nuevo_tm->tm_sec = 0;    // Segundos
        nuevo_tm->tm_min = 0;    // Minutos
        nuevo_tm->tm_hour = 0;   // Horas
        nuevo_tm->tm_mday = dia_;
        nuevo_tm->tm_mon = mes_ - 1;
        nuevo_tm->tm_year = anno_ - 1900;

        std::time_t tiempo = mktime(nuevo_tm);

        sprintf(crep, "%s %i de %s de %i", dia[nuevo_tm->tm_wday], dia_, mes[mes_ - 1], anno_);
        actual = true;
    }

    return crep;
}


// Post: Comprueba que los datos del parametro implicito this sean correctos. Si no lo son lanza un error.
void Fecha::validar() const
{
    if (anno_ < AnnoMinimo || anno_ > AnnoMaximo)
        // Excepcion año no válido
        throw Invalida("Año no válido");

    if (mes_ <= 0 || mes_ >= 13)
        // Excepcion mes no valido
        throw Invalida("Mes no válido");

    if (dia_ <= 0 || dia_ >= 32)
        // Dia invalido
        throw Invalida("Día inválido");

    if (mes_ == 2)
    {
        if ((anno_ % 4 == 0 && anno_ % 100 != 0) || anno_ % 400 == 0)
        {
            if (dia_ >= 30) // Dia invalido
                throw Invalida("Día inválido");
        }
        else
        {
            if (dia_ >= 29) // Dia invalido
                throw Invalida("Día inválido");
        }
    }

    if (mes_ == 4 || mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11)
        if (dia_ >= 31) // Dia invalido
            throw Invalida("Día inválido");
}


// Excepciones
Fecha::Invalida::Invalida(char *cad) : error(cad) {}
char * Fecha::Invalida::por_que() const
{
    return error;
}

