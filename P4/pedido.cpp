#include <iostream>
#include <iomanip>
#include <list>

#include "fecha.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

#include "pedido.hpp"

int Pedido::total_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& U_P, Pedido_Articulo& P_A, Usuario& usuario, const Tarjeta& tarjeta_, Fecha fecha_)
    : tarjeta_(&tarjeta_), fecha_(fecha_), numero_(total_pedidos + 1), importe_total(0)
{

    // NO HACE FALTA HACER ESTO -> DINAMYC_CAST LANZA EXCEPCIONES. SI FUNCIONA ES QUE ES DEL TIPO DEL OBJETO
    // Impostor
    if (&usuario != tarjeta_.titular())
        throw Impostor(usuario);

    // COMPROBAMOS QUE EL LIBRODIGITAL TENGA FECHA DE EXPIRACION CORRECTA
    auto p = usuario.compra().begin();
    std::list<Usuario::Articulos::const_iterator> iteradores;
    while (p != usuario.compra().end())
    {
        try {
            LibroDigital *ld = dynamic_cast<LibroDigital*>(p->first);
            if (fecha_ > ld->f_expir())
            {
                // Quitamos el elemento del carrito
                iteradores.insert(static_cast<Articulo*>(ld)); // FALLA ESTO
            }
        }
        catch (std::bad_cast)
        {
        }
        ++p;
    }

    // Carrito vacio
    if (usuario.compra().empty())
        throw Vacio(usuario);

    // Tarjeta caducada
    if (fecha_ > tarjeta_.caducidad())
        throw Tarjeta::Caducada(tarjeta_.caducidad());

    if (!tarjeta_.activa())
        throw Tarjeta::Desactivada();

    // Introducimos los articulos en el pedido
    for (auto i : usuario.compra())
    {
        try {
            ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable*>(i.first);
            if (i.second > aa->stock())
            {
                usuario.vaciar_carro();
                throw SinStock(*aa);
            }

        }
        catch (const SinStock& e)
        {
            throw e;
        }
        catch (std::bad_cast)
        {

        }
    }

    for (auto i : usuario.compra())
    {
        // usuario.vaciar_carro();
        importe_total += i.first->precio() * i.second;
        try {
            ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable*>(i.first);
            aa->stock() -= i.second;
        }
        catch (std::bad_cast)
        {
        }

        P_A.pedir(*this, *(i.first), i.first->precio(), i.second);
    }

    U_P.asocia(usuario, *this);
    usuario.vaciar_carro();

    total_pedidos++;
}

std::ostream& operator<<(std::ostream& os, const Pedido& P)
{
    using namespace std;
    os << endl;
    os << "Núm. pedido: " << P.numero() << endl;
    os << "Fecha: " << P.fecha() << endl;
    if (P.tarjeta()->tipo() == Tarjeta::Tipo::Otro)
        os << "Pagado con: Tipo indeterminado";
    else
        os << "Pagado con: " << P.tarjeta()->tipo();
    os << " nº: " << P.tarjeta()->numero() << endl;
    os << "Importe: ";
    os << std::fixed << std::setprecision(2) << P.total() << " €" << endl;
    return os;
}