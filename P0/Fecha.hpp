#ifndef FECHA_HPP
#define FECHA_HPP

class Fecha
{
public:
    /* TIPOS */
    class Invalida;

    /* CONSTANTES */
    static const int AnnoMaximo;
    static const int AnnoMinimo;

    /* CONSTRUCTORES */
    Fecha(int d = 0, int m = 0, int a = 0);
    Fecha(const Fecha &A);
    Fecha(std::string cad);

private:
    int dia_,
        mes_,
        anno_;
    void validar();
};

class Fecha::Invalida
{
private:
    std::string por_que() const;

public:
    std::string error;
};

#endif