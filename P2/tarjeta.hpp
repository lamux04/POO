#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <set>
#include "cadena.hpp"
#include "usuario.hpp"

class Usuario;

class Numero
{
public:
    class Incorrecto;

    enum Razon { LONGITUD, DIGITOS, NO_VALIDO };
    Numero(Cadena num);
    operator const char*() const;

private:
    Cadena numero_;
};
bool operator<(const Numero&, const Numero&);

class Numero::Incorrecto
{
public:
    Incorrecto(Razon razon_) : razon_(razon_) {}
    Razon razon() const noexcept { return razon_; }
private:
    Razon razon_;
};

class Fecha;

class Tarjeta
{
public:
    friend class Usuario;
    enum Tipo { Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress };
    class Caducada;
    class Num_duplicado;
    Tarjeta(const Numero&, Usuario&, const Fecha&);
    Tarjeta(const Tarjeta&) = delete;
    Tarjeta& operator=(const Tarjeta&) = delete;

    // OBSERVADORES
    const Numero& numero() const noexcept { return numero_; }
    const Usuario& titular() const noexcept { return *titular_; }
    const Fecha& caducidad() const noexcept { return caducidad_; }
    bool activa() const noexcept { return activa_; }
    Tipo tipo() const noexcept;

    // METODOS
    bool activa(bool activada) noexcept { return activa_ = activada; }

    ~Tarjeta();
    friend std::ostream& operator<<(std::ostream&, const Tarjeta&);

private:
    const Numero numero_;
    const Usuario *titular_;
    const Fecha caducidad_;
    bool activa_;
    static std::set<Numero> nums;
    typedef std::set<Numero>::iterator tipoIt;
    void anula_titular();
};

std::ostream& operator<<(std::ostream& os, Tarjeta::Tipo);

class Tarjeta::Caducada
{
public:
    Caducada(const Fecha& fecha) : fecha(fecha) {}
    const Fecha& cuando() const noexcept { return fecha; }
private:
    Fecha fecha;
};

class Tarjeta::Num_duplicado
{
public:
    Num_duplicado(const Numero& numero) : numero(numero) {}
    const Numero& que() const noexcept { return numero; }
private:
    Numero numero;
};

inline bool operator<(const Tarjeta& A, const Tarjeta& B)
{
    return A < B;
}

bool luhn(const Cadena& numero);

#endif