#include <iostream>
#include <map>

#include "pedido-articulo.hpp"

std::ostream& operator<<(std::ostream& os, const LineaPedido& LP)
{
    os.precision(2);
    os << LP.precio_venta() << " €\t" << LP.cantidad();
}

void Pedido_Articulo::pedir(Pedido& P, Articulo& A, double precio, int cant)
{
    directa[&P].insert(std::make_pair(&A, LineaPedido(precio, cant)));
    inversa[&A].insert(std::make_pair(&P, LineaPedido(precio, cant)));
}

void Pedido_Articulo::pedir(Articulo& A, Pedido& P, double precio, int cant)
{
    pedir(P, A, precio, cant);
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& P) const
{
    auto p = directa.find(&P);
    if (p == directa.end()) return ItemsPedido();
    else return p->second;
}

const Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& A) const
{
    auto p = inversa.find(&A);
    if (p == inversa.end()) return Pedidos();
    else return p->second;
}
