#ifndef CADENA_HPP
#define CADENA_HPP

class Cadena
{
public:
    /* CONSTRUCTORES */
    explicit Cadena(size_t n = 0, char c = ' ');
    Cadena(const char *cad);
    Cadena(const Cadena& A);

    /* METODOS PUBLICOS */
    size_t length() const { return tam_; }
    size_t at(size_t i) const;
    Cadena substr(size_t indice, size_t tama) const;

    /* OPERADORES DE CONVERSION */
    explicit operator const char*() const;

    /* OPERADORES */
    Cadena& operator=(const Cadena& A);
    Cadena& operator=(const char *A);
    Cadena& operator+=(const Cadena& A);
    char operator[](size_t i) const;
    char& operator[](size_t i);

    /* DESTRUCTOR */
    ~Cadena() { delete[] s_; }

    /* FUNCIONES AMIGAS */
    friend Cadena& operator+(const Cadena& A, const Cadena& B);
    friend bool operator>(const Cadena& A, const Cadena& B);
    friend bool operator<(const Cadena& A, const Cadena& B);
    friend bool operator==(const Cadena& A, const Cadena& B);
    friend bool operator!=(const Cadena& A, const Cadena& B);
    friend bool operator>=(const Cadena& A, const Cadena& B);
    friend bool operator<=(const Cadena& A, const Cadena& B);

private:
    static const char vacia[1];
    size_t tam_;
    char *s_;
};

#endif