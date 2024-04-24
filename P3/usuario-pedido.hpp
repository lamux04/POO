#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

class Usuario;
class Pedido;

class Usuario_Pedido
{
public:
    typedef std::set<Pedido*> Pedidos;

    void asocia(Usuario&, Pedido&);
    void asocia(Pedido&, Usuario&);

    const Pedidos& pedidos(Usuario&) const;
    Usuario* cliente(Pedido&) const;

private:
    std::map<Usuario*, Pedidos> directa;
    std::map<Pedido*, Usuario*> inversa;
};

#endif