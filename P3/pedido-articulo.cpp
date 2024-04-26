#include <iostream>

#include "pedido-articulo.hpp"

std::ostream& operator<<(std::ostream& os, const LineaPedido& LP)
{
    os.precision(2);
    os << LP.precio_venta() << " €\t" << LP.cantidad();
}