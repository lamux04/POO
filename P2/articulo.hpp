#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"

class Cadena;
class Fecha;

class Articulo
{
public:
    Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& f_publicacion, double precio, unsigned existencias = 0);
    const Cadena& referencia() const noexcept { return referencia_; }
    const Cadena& titulo() const noexcept { return titulo_; }
    const Fecha& f_publi() const noexcept { return f_publicacion_; }
    double precio() const noexcept { return precio_; }
    double& precio() noexcept { return precio_; };
    unsigned stock() const noexcept { return existencias_; };
    unsigned& stock() noexcept { return existencias_; };

private:
    const Cadena referencia_, titulo_;
    const Fecha f_publicacion_;
    double precio_;
    unsigned existencias_;
};

std::ostream& operator<<(std::ostream&, const Articulo&);

#endif