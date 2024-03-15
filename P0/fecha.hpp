#ifndef FECHA_HPP_
#define FECHA_HPP_

class Fecha
{
public:
    /* TIPOS */
    class Invalida;

    /* CONSTANTES */
    static const int AnnoMaximo;
    static const int AnnoMinimo;

    /* CONSTRUCTORES */
    explicit Fecha(int d = 0, int m = 0, int a = 0);
    Fecha(char *cad);

    operator const char* () const;

    /* METODOS PUBLICOS */
    int dia() const noexcept { return dia_; };
    int mes() const noexcept { return mes_; };
    int anno() const noexcept { return anno_; };
    Fecha& operator+=(int n);
    Fecha& operator-=(int n);
    Fecha& operator++();
    Fecha& operator++(int);
    Fecha& operator--();
    Fecha& operator--(int);

    Fecha operator+(int n) const;
    Fecha operator-(int n) const;

    friend bool operator<(const Fecha& A, const Fecha& B);
    friend bool operator==(const Fecha& A, const Fecha& B);

private:
    int dia_,
        mes_,
        anno_;
    mutable char crep[40];
    mutable bool actual = false;
    void validar() const;
    void aumentar_dias(int n);
};

bool operator>(const Fecha& A, const Fecha& B);
bool operator>=(const Fecha& A, const Fecha& B);
bool operator<=(const Fecha& A, const Fecha& B);
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