#include <iostream>

#include "fecha.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

#include "pedido.hpp"

Pedido::Pedido(Usuario_Pedido& U_P, Pedido_Articulo& P_A, Usuario& usuario, const Tarjeta& tarjeta_, Fecha fecha_ = Fecha())
    : tarjeta_(&tarjeta_), fecha_(fecha_), numero_(total_pedidos), importe_total(0)
{
    // Carrito vacio
    if (usuario.compra().empty())
        throw Vacio(usuario);

    // Impostor
    if (&usuario != tarjeta_.titular())
        throw Impostor(usuario);

    // Tarjeta caducada
    if (fecha_ > tarjeta_.caducidad())
        throw Tarjeta::Caducada(tarjeta_.caducidad());

    if (!tarjeta_.activa())
        throw Tarjeta::Desactivada();

    // Introducimos los articulos en el pedido
    for (auto i : usuario.compra())
    {
        if (i.second > i.first->stock())
        {
            usuario.vaciar_carro();
            throw SinStock(*(i.first));
        }
        importe_total += i.first->precio() * i.second;
        i.first->stock() -= i.second;

        P_A.asocia(*this, *(i.first));
    }

    U_P.asocia(usuario, *this);
    usuario.vaciar_carro();

    total_pedidos++;
}

std::ostream& operator<<(std::ostream& os, const Pedido& P)
{
    using namespace std;
    os << endl;
    os.width(13);
    os << "Num. pedido: " << P.numero() << endl;
    os.width(13);
    os << "Fecha: " << P.fecha() << endl;
    os.width(13);
    os << "Pagado con: " << P.tarjeta()->tipo() << " nº: " << P.tarjeta()->numero() << endl;
    os.width(13);
    os << "Importe: ";
    os.precision(2);
    os << P.total() << " €" << endl;
}