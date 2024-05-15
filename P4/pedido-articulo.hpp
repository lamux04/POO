#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include "pedido.hpp"
#include "articulo.hpp"

class Pedido;
class Articulo;

class LineaPedido
{
public:
    explicit LineaPedido(double precio_venta = 0.0, unsigned cantidad = 1)
        : precio_venta_(precio_venta), cantidad_(cantidad) {}

    double precio_venta() const { return precio_venta_; }
    unsigned cantidad() const { return cantidad_; }

private:
    double precio_venta_;
    unsigned cantidad_;
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
    void pedir(Pedido&, Articulo&, double, unsigned = 1);
    void pedir(Articulo&, Pedido&, double, unsigned = 1);
    const ItemsPedido detalle(Pedido& P) const;
    const Pedidos ventas(Articulo&) const;
    void mostrarDetallePedidos(std::ostream& os) const;
    void mostrarVentasArticulos(std::ostream& os) const;
private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> directa;
    std::map<Articulo*, Pedidos, OrdenaArticulos> inversa;

};

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& IP);
std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& IP);


#endif