#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "fecha.hpp"
#include "tarjeta.hpp"

class Tarjeta;
class Fecha;
class Usuario_Pedido;
class Pedido_Articulo;

class Pedido
{
public:
    Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, Fecha = Fecha());

    class Vacio;
    class Impostor;
    class SinStock;

    int numero() const { return numero_; }
    const Tarjeta* tarjeta() const { return tarjeta_; }
    const Fecha& fecha() const { return fecha_; }
    double total() const { return importe_total; }
    static int n_total_pedidos() { return total_pedidos; }

private:
    int numero_;
    const Tarjeta* tarjeta_;
    Fecha fecha_;
    double importe_total;
    static int total_pedidos;
};

class Pedido::Vacio
{
public:
    Vacio(const Usuario& U) : usuario_(U) {}
    const Usuario& usuario() const { return usuario_; }
private:
    const Usuario& usuario_;
};

class Pedido::Impostor
{
public:
    Impostor(const Usuario& U) : usuario_(U) {}
    const Usuario& usuario() const { return usuario_; }
private:
    const Usuario& usuario_;
};

class Pedido::SinStock
{
public:
    SinStock(const Articulo& A) : articulo_(A) {}
    const Articulo& articulo() const { return articulo_; }
private:
    const Articulo& articulo_;
};

std::ostream& operator<<(std::ostream& os, const Pedido& P);

#endif