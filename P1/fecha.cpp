#include <ctime>
#include <iostream>
#include <cstdio>
#include <cstring>

#include "fecha.hpp"

// Declaracion constantes
const int Fecha::AnnoMaximo(2037);
const int Fecha::AnnoMinimo(1902);

// Los parametros por defecto solo en la definicion
Fecha::Fecha(int d /* = 0 */, int m /* = 0 */, int a /* = 0 */) : dia_(d), mes_(m), anno_(a), actual(false)
{
    if (dia_ != 0 && mes_ != 0 && anno_ != 0)
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
    dia_ = -1; mes_ = -1; anno_ = -1;

    if (/*std::strlen(cad) >= 10 ||*/ sscanf(cad, "%d/%d/%d", &dia_, &mes_, &anno_) != 3)
        throw Invalida("Formato de fecha inválido");

    *this = Fecha(dia_, mes_, anno_);
}

void Fecha::aumentar_dias(int n)
{
    struct std::tm nuevo_tm { 0 };

    nuevo_tm.tm_sec = 0;    // Segundos
    nuevo_tm.tm_min = 0;    // Minutos
    nuevo_tm.tm_hour = 0;   // Horas
    nuevo_tm.tm_mday = dia_ + n;
    nuevo_tm.tm_mon = mes_ - 1;
    nuevo_tm.tm_year = anno_ - 1900;

    mktime(&nuevo_tm); // Normalizamos la fecha
    // tiempo += 60 * 60 * 24 * (n + 1);
    // std::tm *fecha_normalizada = std::localtime(&tiempo);

    dia_ = nuevo_tm.tm_mday;
    mes_ = nuevo_tm.tm_mon + 1;
    anno_ = nuevo_tm.tm_year + 1900;
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
    *this += -n;
    validar();
    actual = false;
    return *this;
}

typename Fecha::Fecha& Fecha::operator++()
{
    *this += 1;
    validar();
    actual = false;
    return *this;
}

typename Fecha::Fecha& Fecha::operator++(int)
{
    Fecha copia{ *this };
    *this += 1;
    validar();
    actual = false;
    return copia;
}

typename Fecha::Fecha& Fecha::operator--()
{
    *this += -1;
    validar();
    actual = false;
    return *this;
}

typename Fecha::Fecha& Fecha::operator--(int)
{
    Fecha copia{ *this };
    *this += -1;
    validar();
    actual = false;
    return copia;
}

Fecha Fecha::operator+(int n) const
{
    Fecha A(*this);
    A += n;
    A.validar();
    return A;
}

Fecha Fecha::operator-(int n) const
{
    Fecha A(*this);
    A += -n;
    A.validar();
    return A;
}

bool operator<(const Fecha& A, const Fecha& B)
{
    if (A.anno_ != B.anno_) return A.anno_ < B.anno_;
    else if (A.mes_ != B.mes_) return A.mes_ < B.mes_;
    else return A.dia_ < B.dia_;
}

bool operator==(const Fecha& A, const Fecha& B)
{
    if (A.anno_ != B.anno_) return false;
    else if (A.mes_ != B.mes_) return false;
    else return A.dia_ == B.dia_;
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

const char* Fecha::cadena() const
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

        struct std::tm * nuevo_tm = new std::tm{ 0 };

        nuevo_tm->tm_sec = 0;    // Segundos
        nuevo_tm->tm_min = 0;    // Minutos
        nuevo_tm->tm_hour = 0;   // Horas
        nuevo_tm->tm_mday = dia_;
        nuevo_tm->tm_mon = mes_ - 1;
        nuevo_tm->tm_year = anno_ - 1900;

        mktime(nuevo_tm);

        sprintf(crep, "%s %i de %s de %i", dia[nuevo_tm->tm_wday], dia_, mes[mes_ - 1], anno_);
        actual = true;
        delete nuevo_tm;
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

// P1

std::istream& operator>>(std::istream& is, Fecha& A)
{
    char cad[11];
    is.width(11);
    is >> cad;
    try
    {
        A = Fecha(cad);
    }
    catch (const Fecha::Invalida& e)
    {
        is.setstate(std::_S_failbit);
        throw;
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Fecha& A)
{
    os << A.cadena();
    return os;
}