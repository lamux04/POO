#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <set>

class Autor
{
public:
    Autor(Cadena nombre, Cadena apellidos, Cadena direccion) : nombre_(nombre), apellidos_(apellidos), direccion_(direccion) {}

    Cadena nombre() const { return nombre_; }
    Cadena apellidos() const { return apellidos_; }
    Cadena direccion() const { return direccion_; }

private:
    Cadena nombre_, apellidos_, direccion_;
};

class Articulo
{
public:
    class Autores_vacios {};
    typedef std::set<Autor*> Autores;
    Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publicacion, double precio);
    const Cadena& referencia() const noexcept { return referencia_; }
    const Cadena& titulo() const noexcept { return titulo_; }
    const Fecha& f_publi() const noexcept { return f_publicacion_; }
    double precio() const noexcept { return precio_; }
    double& precio() noexcept { return precio_; };
    virtual void impresion_especifica(std::ostream&) const = 0;
    const Autores& autores() const { return autores_; }
    virtual ~Articulo() {}

private:
    const Cadena referencia_, titulo_;
    const Fecha f_publicacion_;
    double precio_;
    const Autores autores_;
};

std::ostream& operator<<(std::ostream&, const Articulo&);

class ArticuloAlmacenable : public Articulo
{
public:
    ArticuloAlmacenable(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publicacion, double precio, unsigned existencias = 0) : Articulo(autores, referencia, titulo, f_publicacion, precio), existencias_(existencias) {}
    unsigned stock() const noexcept { return existencias_; };
    unsigned& stock() noexcept { return existencias_; };
private:
    unsigned existencias_;
};

class Libro : public ArticuloAlmacenable
{
public:
    Libro(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publicacion, double precio, unsigned paginas, unsigned existencias = 0) : ArticuloAlmacenable(autores, referencia, titulo, f_publicacion, precio, existencias), paginas_(paginas) {}
    unsigned n_pag() const { return paginas_; }
    void impresion_especifica(std::ostream&) const override;

private:
    const unsigned paginas_;
};

class Revista : public ArticuloAlmacenable
{
public:
    Revista(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publicacion, double precio, unsigned numero, unsigned periodicidad, unsigned existencias = 0) : ArticuloAlmacenable(autores, referencia, titulo, f_publicacion, precio, existencias), numero_(numero), periodicidad_(periodicidad) {}

    unsigned numero() const { return numero_; }
    unsigned periodicidad() const { return periodicidad_; }
    void impresion_especifica(std::ostream&) const override;

private:
    const unsigned numero_, periodicidad_;
};

class LibroDigital : public Articulo
{
public:
    LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publicacion, double precio, Fecha f_expir) : Articulo(autores, referencia, titulo, f_publicacion, precio), f_expir_(f_expir) {}

    Fecha f_expir() const { return f_expir_; }
    void impresion_especifica(std::ostream&) const override;

private:
    const Fecha f_expir_;
};

#endif