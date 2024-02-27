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
    Fecha(char *cad);

    void imprimir();

    /* METODOS PUBLICOS */
    int dia() const { return dia_; };
    int mes() const { return mes_; };
    int anno() const { return anno_; };
    Fecha& operator+=(int n);
    Fecha& operator-=(int n);
    Fecha& operator++();
    Fecha& operator++(int);
    Fecha& operator--();
    Fecha& operator--(int);

    /* AMIGOS DE LA CLASE */
    friend Fecha& operator+(Fecha A, int n);
    friend Fecha& operator-(Fecha A, int n);

private:
    int dia_,
        mes_,
        anno_;
    void validar() const;
    void aumentar_dias(int n);
};
bool operator>(const Fecha& A, const Fecha& B);
bool operator<(const Fecha& A, const Fecha& B);
bool operator>=(const Fecha& A, const Fecha& B);
bool operator<=(const Fecha& A, const Fecha& B);
bool operator==(const Fecha& A, const Fecha& B);
bool operator!=(const Fecha& A, const Fecha& B);

class Fecha::Invalida
{
public:
    Invalida(char *cad);
    char * por_que() const;

private:
    char *error;
};

#endif