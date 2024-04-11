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
    class Num_duplicado;
    Tarjeta(const Numero&, const Usuario&, const Fecha&);
    Tarjeta(const Tarjeta&) = delete;
    Tarjeta& operator=(const Tarjeta&) = delete;

    // OBSERVADORES
    const Numero& numero() const noexcept { return numero_; }
    const Usuario& titular() const noexcept { return titular_; }
    const Fecha& caducidad() const noexcept { return caducidad_; }
    bool activa() const noexcept { return activa_; }
    Tipo tipo() const noexcept;

    // METODOS
    bool activa(bool activada) noexcept { return activa_ = activada; }
    void anular_titular();

    ~Tarjeta();
    friend std::ostream& operator<<(std::ostream&, const Tarjeta&);
    friend bool operator<(const Tarjeta&, const Tarjeta&);

private:
    const Numero numero_;
    const Usuario titular_;
    const Fecha caducidad_;
    bool activa_;
};

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

#endif