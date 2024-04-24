#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <random>

#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

#include "usuario.hpp"

std::unordered_set<Cadena> Usuario::ids{};

const char Clave::caracteres[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '/'
};

Clave::Clave(const char* cad)
{
    // Tamano correcto
    if (strlen(cad) < 5)
        throw Clave::Incorrecta(CORTA);

    try
    {
        std::random_device r;
        std::default_random_engine el(r());
        std::uniform_int_distribution<int> uniform_dist(0, 61);
        char *seed = new char[3];
        seed[0] = caracteres[uniform_dist(el)];
        seed[1] = caracteres[uniform_dist(el)];
        seed[2] = '\0';
        clave_ = crypt(cad, seed);
        delete[] seed;
    }
    catch (...)
    {
        throw Clave::Incorrecta(ERROR_CRYPT);
    }
}

bool Clave::verifica(const char* cad) const
{
    char *seed = new char[3];
    seed[0] = clave_[0];
    seed[1] = clave_[1];
    seed[2] = '\0';
    return strcmp(crypt(cad, seed), (const char*)clave_) == 0;
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
        throw Id_duplicado(identificador_);
}

void Usuario::es_titular_de(Tarjeta& tarjeta)
{
    // El titular de la tarjeta es el usuario
    if (tarjeta.titular() == this)
        tarjetas_.insert(std::make_pair(tarjeta.numero(), &tarjeta));
}

void Usuario::no_es_titular_de(Tarjeta& tarjeta)
{
    tarjetas_.erase(tarjeta.numero_);
}

Usuario::~Usuario()
{
    for (auto i : tarjetas_)
        i.second->anula_titular();
    ids.erase(identificador_);
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
    return articulos_.size();
}

std::ostream& operator<<(std::ostream& os, const Usuario& usuario)
{
    using namespace std;
    os
        << usuario.identificador_ << " [" << usuario.contrasenna_.clave() << "] " << usuario.nombre_ << " " << usuario.apellidos_ << endl
        << usuario.direccion_ << endl
        << "Tarjetas:" << endl;

    for (auto i : usuario.tarjetas_)
        os << *i.second << endl;
    return os;
}

void mostrar_carro(std::ostream& os, const Usuario& usuario)
{
    using namespace std;
    os << endl;
    os
        << "Carrito de compra de " << usuario.id() << " [Artículos: " << usuario.n_articulos() << "]" << endl
        << " Cant.  Artículo" << endl;
    os.fill('=');
    os.width(60);
    os << "";
    os << endl;
    Usuario::Articulos carrito = usuario.compra();
    for (Usuario::Articulos::const_iterator p = carrito.begin(); p != carrito.end(); ++p)
    {
        os << "  " << p->second << "   " << *(p->first) << endl;
    }
}