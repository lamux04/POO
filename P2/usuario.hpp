#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include <map>
#include "cadena.hpp"
#include <unordered_map>
#include <unordered_set>
#include <map>

class Numero;
class Tarjeta;
class Articulo;

class Clave
{
public:
    class Incorrecta;
    enum Razon { CORTA, ERROR_CRYPT };
    Clave(const char* cad);
    Cadena clave() const noexcept { return clave_; }
    bool verifica(const char* cad) const;

private:
    Cadena clave_;
};

class Clave::Incorrecta
{
public:
    Incorrecta(Razon razon_) : razon_(razon_) {}
    Razon razon() const noexcept { return razon_; }
private:
    Razon razon_;
};

class Usuario
{
public:
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;

    class Id_duplicado;

    Usuario(const Cadena& identificador_, const Cadena& nombre_, const Cadena& apellidos_, const Cadena& direccion_, const Clave& clave_);

    Usuario(const Usuario&) = delete;
    Usuario& operator=(const Usuario&) = delete;

    // OBSERVADORES
    const Cadena& id() const noexcept { return identificador_; }
    const Cadena& nombre() const noexcept { return nombre_; }
    const Cadena& apellidos() const noexcept { return apellidos_; }
    const Cadena& direccion() const noexcept { return direccion_; }
    const Tarjetas& tarjetas() const noexcept { return tarjetas_; }
    const Articulos& compra() const noexcept { return articulos_; }

    // ASOCIACIÓN CON TARJETA
    void es_titular_de(Tarjeta&);
    void no_es_titular_de(Tarjeta&);

    // DESTRUCTOR
    ~Usuario();

    // ASOCIACIÓN CON ARTÍCULO
    void compra(Articulo&, unsigned int cantidad = 1);
    const Articulos& compra() { return articulos_; }
    void vaciar_carro();
    unsigned n_articulos() const;

    friend std::ostream& operator<<(std::ostream&, const Usuario&);

private:
    const Cadena identificador_, nombre_, apellidos_, direccion_;
    Clave contrasenna_;
    Tarjetas tarjetas_;
    Articulos articulos_;
    static std::unordered_set<Cadena> ids;
    typedef std::unordered_set<Cadena>::iterator tipoIt;
};

void mostrar_carro(std::ostream&, const Usuario&);

class Usuario::Id_duplicado
{
public:
    Id_duplicado(const Cadena& cad) : idd_(cad) {}
    const Cadena& idd() const noexcept { return idd_; }
private:
    Cadena idd_;
};

#endif