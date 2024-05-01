#include <map>
#include <set>
#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario& U, Pedido& P)
{
    if (inversa.find(&P) == inversa.end())
    {
        directa[&U].insert(&P);
        inversa[&P] = &U;
    }
    else {
        directa[inversa[&P]].erase(&P);
        directa[&U].insert(&P);
        inversa[&P] = &U;
    }
}

void Usuario_Pedido::asocia(Pedido& P, Usuario& U)
{
    asocia(U, P);
}

const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& U) const
{
    typename std::map<Usuario*, Pedidos>::const_iterator i = directa.find(&U);
    if (i != directa.end()) return i->second;
    else return Pedidos();
}

Usuario* Usuario_Pedido::cliente(Pedido& P) const
{
    typename std::map<Pedido*, Usuario*>::const_iterator i = inversa.find(&P);
    if (i != inversa.end())
        return i->second;
    else return nullptr;
}
