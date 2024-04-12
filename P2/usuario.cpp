#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <cstring>
#include <unistd.h>

#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

#include "usuario.hpp"

std::unordered_set<Cadena> Usuario::ids{};

Clave::Clave(const char* cad)
{
    // Tamano correcto
    if (std::strlen(cad) < 5)
        throw Clave::Incorrecta(CORTA);

    try
    {
        clave_ = crypt(cad, "aa");
    }
    catch (...)
    {
        throw Clave::Incorrecta(ERROR_CRYPT);
    }
}

bool Clave::verifica(const char* cad) const
{
    return strcmp(crypt(cad, "aa"), (const char*)clave_) == 0;
}

Usuario::Usuario(const Cadena& identificador_, const Cadena& nombre_, const Cadena& apellidos_, const Cadena& direccion_, const Clave& clave_) :
    identificador_(identificador_),
    nombre_(nombre_),
    apellidos_(apellidos_),
    direccion_(direccion_),
    contrasenna_(clave_)
{
    std::pair<tipoIt, bool> res = Usuario::ids.insert(identificador_);
    if (!res.second)
        throw Id_ducplicado(identificador_);
}

void Usuario::es_titular_de(Tarjeta& tarjeta)
{
    tarjetas_.insert(std::make_pair(tarjeta.numero(), &tarjeta));
}

void Usuario::no_es_titular_de(Tarjeta& tarjeta)
{
    tarjetas_.erase(tarjeta.numero());
}

Usuario::~Usuario()
{
    for (auto i : tarjetas_)
        i.second->anula_titular();
}

void Usuario::compra(Articulo& articulo, unsigned int cantidad)
{
    articulos_[&articulo] = cantidad;
    if (cantidad == 0)
        articulos_.erase(&articulo);
}

void Usuario::vaciar_carro()
{
    articulos_.clear();
}

unsigned Usuario::n_articulos() const
{
    articulos_.size();
}

std::ostream& operator<<(std::ostream& os, const Usuario& usuario)
{
    using namespace std;
    os
        << usuario.identificador_ << " [" << usuario.contrasenna_.clave() << "] " << usuario.nombre_ << " " << usuario.apellidos_ << endl
        << usuario.direccion_ << endl
        << "Tarjetas:" << endl;

    for (auto i : usuario.tarjetas_)
        os << i.second << endl;
    return os;
}

void mostrar_carro(std::ostream& os, Usuario& usuario)
{
    using namespace std;
    os
        << "Carrito de compra de " << usuario.id() << " [Artículos: " << usuario.n_articulos() << "]" << endl
        << " Cant.  Artículo" << endl;
    os.fill('=');
    os.width(60);
    os << endl;
    for (auto i : usuario.compra())
        os << "  " << i.second << "   " << i.first << endl;
}