#include <map>
#include <iostream>
#include <unordered_map>

#include "articulo.hpp"
#include "cadena.hpp"

#include "usuario.hpp"

Usuario::Usuario(const Cadena& identificador_, const Cadena& nombre_, const Cadena& apellidos_, const Cadena& direccion_, const Clave& clave_) :
    identificador_(identificador_),
    nombre_(nombre_),
    apellidos_(apellidos_),
    direccion_(direccion_),
    contrasenna_(clave_)
{
    // COMPROBAR QUE EL USUARIO SEA CORRECTO
}

