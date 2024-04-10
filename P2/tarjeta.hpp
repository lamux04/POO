#ifndef TARJETA_HPP_
#define TARJETA_HPP_

class Cadena;

class Numero
{
public:
    class Incorrecto;

    enum Razon { LONGITUD, DIGITOS, NO_VALIDO };
    Numero(Cadena num);
    operator const char*();
    friend bool operator<(const Numero&, const Numero&);

private:
    Cadena numero_;
};

class Numero::Incorrecto
{
public:
    Incorrecto(Razon razon_) : razon_(razon_) {}
    Razon razon() const noexcept { return razon_; }
private:
    Razon razon_;
};

class Usuario;
class Fecha;

class Tarjeta
{
public:
    enum Tipo { Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress };
    class Caducada;
    Tarjeta(const Numero&, const Usuario&, const Fecha&);


private:
    const Numero numero_;
    const Usuario titula_;
    const Fecha caducidad_;
    bool activa;
};

#endif