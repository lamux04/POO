#include <iostream>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <unordered_set>

#include "cadena.hpp"
#include "usuario.hpp"
#include "fecha.hpp"
#include "tarjeta.hpp"

bool luhn(const Cadena& numero)
{
    size_t n = numero.length();
    size_t suma = 0;
    bool alt = false;
    for (int i = n - 1; i > -1; --i) {
        n = numero[size_t(i)] - '0';
        if (alt) {
            n *= 2;
            if (n > 9)
                n = (n % 10) + 1;
        }
        alt = !alt;
        suma += n;
    }
    return !(suma % 10);
}


Numero::Numero(Cadena num)
{
    int n = num.length();
    if (!(n >= 13 && n <= 19))
        throw Incorrecto(LONGITUD);
    char *cad = new char[num.length()];
    int j = 0;
    bool valido = true;
    for (int i = 0; i < n && valido; ++i)
    {
        if (num[i] != ' ')
        {
            if (!std::isdigit(num[i]))
                valido = false;
            cad[j] = num[i];
            ++j;
        }
    }
    if (!valido)
        throw Incorrecto(DIGITOS);
    numero_ = Cadena(cad);
    delete[] cad;

    if (!luhn(numero_))
        throw Incorrecto(NO_VALIDO);
}

Numero::operator const char*() const
{
    return (const char*)numero_;
}

bool operator<(const Numero& n1, const Numero& n2)
{
    return strcmp(n1, n2) < 0;
}

Tarjeta::Tarjeta(const Numero& numero, Usuario& usuario, const Fecha& fecha) :
    numero_(numero), titular_(&usuario), caducidad_(fecha), activa_(true)
{
    if (caducidad_ < Fecha())
        throw Caducada(caducidad_);
    usuario.es_titular_de(*this);

    std::pair<tipoIt, bool> res = nums.insert(numero_);
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
    os
        << " ---------------------------- " << endl
        << "/                            \\" << endl
        << "|  " << tarjeta.tipo() << endl
        << "|  " << tarjeta.numero_ << endl
        << "|  " << tarjeta.titular_->nombre() << " " << tarjeta.titular_->apellidos() << endl
        << "|  Caduca: " << tarjeta.caducidad_.mes() << "/" << tarjeta.caducidad_.anno() % 100 << endl
        << "\\___________________________/" << endl;

    return os;
}



