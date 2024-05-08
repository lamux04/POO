#include <iostream>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <set>
#include <cmath>
#include <algorithm>
#include <functional>

#include "cadena.hpp"
#include "usuario.hpp"
#include "fecha.hpp"
#include "tarjeta.hpp"

std::set<Numero> Tarjeta::nums{};

Numero::Numero(Cadena num) : numero_(num)
{
    int n = num.length();
    if (!(n >= 13 && n <= 19))
        throw Incorrecto(LONGITUD);

    Cadena::const_iterator p = std::remove_if(numero_.begin(), numero_.end(), [](char c) { return c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f'; });
    numero_ = numero_.substr(0, p - numero_.begin());

    std::unary_negate<EsDigito> noEsDigito((EsDigito()));

    Cadena::const_iterator p2 = std::find_if(numero_.begin(), numero_.end(), noEsDigito);

    if (p2 != numero_.end())
        throw Incorrecto(DIGITOS);

    if (!luhn(numero_))
        throw Incorrecto(NO_VALIDO);
}

Numero::operator const char*() const
{
    return (const char*)numero_;
}

bool operator<(const Numero& n1, const Numero& n2)
{
    long long int num1 = 0, num2 = 0;
    int i = 0;
    for (Cadena::const_reverse_iterator p = n1.numero_.crbegin(); p != n1.numero_.crend(); ++p)
    {
        num1 += (*p - '0') * pow(10, i);
        ++i;
    }
    i = 0;
    for (Cadena::const_reverse_iterator p = n2.numero_.crbegin(); p != n2.numero_.crend(); ++p)
    {
        num2 += (*p - '0') * pow(10, i);
        ++i;
    }
    return num1 < num2;
}

Tarjeta::Tarjeta(const Numero& numero, Usuario& usuario, const Fecha& fecha) :
    numero_(numero), titular_(&usuario), caducidad_(fecha), activa_(true)
{
    if (caducidad_ < Fecha())
        throw Caducada(caducidad_);
    usuario.es_titular_de(*this);

    std::pair<tipoIt, bool> res = Tarjeta::nums.insert(numero_);
    if (!res.second)
        throw Num_duplicado(numero_);
}

Tarjeta::Tipo Tarjeta::tipo() const noexcept
{
    Cadena cad = (const char*)numero_;
    switch (cad[0])
    {
    case '3':
        if (cad[1] == '4' || cad[1] == '7') return AmericanExpress;
        else return JCB;
    case '4':
        return VISA;
    case '5':
        return Mastercard;
    case '6':
        return Maestro;
    default:
        return Otro;
    }
}

void Tarjeta::anula_titular()
{
    activa_ = false;
    titular_ = nullptr;
}

Tarjeta::~Tarjeta()
{
    if (titular_ != nullptr)
    {
        const_cast<Usuario*>(titular_)->no_es_titular_de(*this);
        titular_ = nullptr;
    }
    nums.erase(numero_);
}

std::ostream& operator<<(std::ostream& os, Tarjeta::Tipo tipo)
{
    switch (tipo)
    {
    case Tarjeta::AmericanExpress:
        os << "AmericanExpress";
        break;
    case Tarjeta::JCB:
        os << "JCB";
        break;
    case Tarjeta::VISA:
        os << "VISA";
        break;
    case Tarjeta::Mastercard:
        os << "Mastercard";
        break;
    case Tarjeta::Maestro:
        os << "Maestro";
        break;
    case Tarjeta::Otro:
        os << "Otro";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Tarjeta& tarjeta)
{
    using namespace std;

    // Nombres en mayuscula
    char *nombre = new char[tarjeta.titular_->nombre().length()];
    int j = 0;
    for (auto i : tarjeta.titular_->nombre())
    {
        nombre[j] = toupper(i);
        ++j;
    }
    char *apellidos = new char[tarjeta.titular_->apellidos().length()];
    j = 0;
    for (auto i : tarjeta.titular_->apellidos())
    {
        apellidos[j] = toupper(i);
        ++j;
    }

    // Caducidad

    os
        << " ---------------------------- " << endl
        << "/                            \\" << endl
        << "|  " << tarjeta.tipo() << endl
        << "|  " << tarjeta.numero_ << endl
        << "|  " << nombre << " " << apellidos << endl
        << "|  Caduca: ";

    if (tarjeta.caducidad_.mes() < 10)
        os << '0';

    os << tarjeta.caducidad_.mes() << "/" << tarjeta.caducidad_.anno() % 100 << endl
        << "\\___________________________/" << endl;

    delete[] nombre;
    delete[] apellidos;
    return os;
}



