#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include "pedido.hpp"
#include "articulo.hpp"

class Pedido;
class Articulo;

class LineaPedido
{
public:
    explicit LineaPedido(double precio_venta_ = 0.0, int cantidad_ = 1)
        : precio_venta_(precio_venta_), cantidad_(cantidad_) {}

    double precio_venta() const { return precio_venta_; }
    int cantidad() const { return cantidad_; }

private:
    double precio_venta_;
    int cantidad_;
};

std::ostream& operator<<(std::ostream&, const LineaPedido&);


class Pedido_Articulo
{
public:
    class OrdenaPedidos
    {
    public:
        bool operator () (Pedido* A, Pedido* B) const
        {
            return A->numero() < B->numero();
        }
    };
    class OrdenaArticulos
    {
    public:
        bool operator () (Articulo* A, Articulo* B) const
        {
            return A->referencia() < B->referencia();
        }
    };
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    void pedir(Pedido&, Articulo&, double, int = 1);
    void pedir(Articulo&, Pedido&, double, int = 1);
    const ItemsPedido& detalle(Pedido& P) const;
    const Pedidos& ventas(Articulo&) const;
    void mostrarDetallesPedidos() const;
    void mostrarVentasArticulos() const;
private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> directa;
    std::map<Articulo*, Pedidos, OrdenaArticulos> inversa;

};

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& IP);
std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& IP);


#endif