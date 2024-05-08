#include <iostream>
#include <map>
#include <iomanip>


#include "pedido-articulo.hpp"

std::ostream& operator<<(std::ostream& os, const LineaPedido& LP)
{
    os << std::fixed << std::setprecision(2) << LP.precio_venta() << " €\t" << LP.cantidad();
    return os;
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

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& IP)
{
    using namespace std;
    double total = 0;
    os << "  PVP     Cantidad           Articulo" << endl;
    os << "===========================================================" << endl;
    for (auto i : IP)
    {
        total += i.second.cantidad() * i.second.precio_venta();
        os << i.second << "              ";
        os << "[" << i.first->referencia() << "] \"" << i.first->titulo() << "\"" << endl;
    }
    os << "===========================================================" << endl;
    os << "Total\t" << std::fixed << std::setprecision(2) << total << " €";
    return os;

}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& P)
{
    using namespace std;
    double total = 0;
    int cTotal = 0;
    os << "[Pedidos: " << P.size() << "]" << endl;
    os << "===========================================================" << endl;
    os << "  PVP     Cantidad           Fecha de venta" << endl;
    os << "===========================================================" << endl;
    for (auto i : P)
    {
        cTotal += i.second.cantidad();
        total += i.second.cantidad() * i.second.precio_venta();
        os << i.second << "              ";
        os << i.first->fecha() << endl;
    }
    os << "===========================================================" << endl;
    os << "Total\t" << std::fixed << std::setprecision(2) << total << " €\t" << cTotal;
    return os;
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream& os) const
{
    using namespace std;
    double total = 0;
    for (auto i : directa)
    {
        os << "Pedido num. " << i.first->numero() << endl;
        os << "Cliente: " << *(i.first->tarjeta()->titular()) << endl;
        os << "Fecha: " << i.first->fecha() << endl;
        os << i.second << endl << endl;
        total += i.first->total();
    }
    os << "TOTAL VENTAS          " << std::fixed << std::setprecision(2) << total << " €" << endl;
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os) const
{
    using namespace std;
    double total = 0;
    for (auto i : inversa)
    {
        total = 0;
        os << "Ventas de [" << i.first->referencia() << "] \"" << i.first->titulo() << "\"" << endl;
        for (auto j : i.second)
        {
            os << "\tPedido num. " << j.first->numero() << endl;
            os << "\tCliente: " << j.first->tarjeta()->titular()->nombre() << endl;
            os << "\tFecha: " << j.first->fecha() << endl << endl;
            os << i.second;
            total += j.first->total();
        }
        os << "\tTOTAL VENTAS          " << std::fixed << std::setprecision(2) << total << " €" << endl << endl;
    }
}