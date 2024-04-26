#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

class Pedido;
class Articulo;

class LineaPedido
{
public:
    explicit LineaPedido(double precio_venta_ = 0.0, int cantidad_ = 1)
        : precio_venta_(precio_venta_), cantidad_(cantidad_) {}

    double precio_venta() const { return precio_venta_; }
    int cantidad() const { return cantidad_; }

private:
    double precio_venta_;
    int cantidad_;
};

std::ostream& operator<<(std::ostream&, const LineaPedido&);


class Pedido_Articulo
{
public:
    void asocia(Pedido&, Articulo&);
private:

};


#endif