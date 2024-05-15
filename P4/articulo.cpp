#include <iostream>
#include <cmath>
#include <iomanip>
#include <set>

#include "cadena.hpp"
#include "fecha.hpp"
#include "articulo.hpp"

Articulo::Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publicacion, double precio) :
    autores_(autores),
    referencia_(referencia),
    titulo_(titulo),
    f_publicacion_(f_publicacion),
    precio_(precio)
{
    if (autores_.empty())
        throw Autores_vacios();
}

std::ostream& operator<<(std::ostream& os, const Articulo& A)
{
    os << "[" << A.referencia() << "] \"" << A.titulo() << "\", "
        << A.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << A.precio() << " €" << std::endl;
    A.impresion_especifica(os);
    return os;
}

void Libro::impresion_especifica(std::ostream& os) const
{
    os << "\t" << paginas_ << " págs., " << stock() << " unidades." << std::endl;
}

void Revista::impresion_especifica(std::ostream& os) const
{
    os << "\tNúmero: " << numero_ << ", Periodicidad: " << periodicidad_ << " días." << std::endl;
    os << "\tPróximo número a partir de: " << f_publi() + periodicidad_ << std::endl;
}

void LibroDigital::impresion_especifica(std::ostream& os) const
{
    os << "\tA la venta hasta el " << f_expir_;
}

