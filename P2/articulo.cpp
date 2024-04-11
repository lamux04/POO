#include <iostream>
#include <cmath>

#include "cadena.hpp"
#include "fecha.hpp"
#include "articulo.hpp"

Articulo::Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& f_publicacion, double precio, unsigned existencias) :
    referencia_(referencia),
    titulo_(titulo),
    f_publicacion_(f_publicacion),
    precio_(precio),
    existencias_(existencias)
{
}

std::ostream& operator<<(std::ostream& os, const Articulo& A)
{
    os << "[" << A.referencia() << "] \"" << A.titulo() << "\", "
        << A.f_publi().anno() << ". " << std::round(A.precio() / 100.0) * 100.0 << " €";
    return os;
}