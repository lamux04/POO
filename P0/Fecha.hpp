#ifndef FECHA_HPP
#define FECHA_HPP

class Fecha
{
public:
    /* CONSTRUCTORES */

    Fecha(int d = 0, int m = 0, int a = 0);
    Fecha(const Fecha &A);
    Fecha(std::string cad);

private:
    int dia_,
        mes_,
        anno_;
};

#endif