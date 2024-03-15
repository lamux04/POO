#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena
{
public:
    /* CONSTRUCTORES */
    explicit Cadena(size_t n = 0, char c = ' ') noexcept;
    Cadena(const char *cad);
    Cadena(const Cadena& A);

    /* METODOS PUBLICOS */
    size_t length() const noexcept { return tam_; }
    char at(size_t i) const;
    char& at(size_t i);
    Cadena substr(int indice, int tama) const;

    /* OPERADORES DE CONVERSION */
    explicit operator const char*() const;

    /* OPERADORES */
    Cadena& operator=(const Cadena& A);
    Cadena& operator=(const char *A);
    Cadena& operator+=(const Cadena& A);
    char operator[](size_t i) const noexcept;
    char& operator[](size_t i) noexcept;

    /* DESTRUCTOR */
    ~Cadena() { if (s_ != vacia) delete[] s_; }

    /* FUNCIONES AMIGAS */

private:
    static char vacia[1];
    size_t tam_;
    char *s_;
};
bool operator<(const Cadena& A, const Cadena& B);
bool operator==(const Cadena& A, const Cadena& B);
Cadena operator+(const Cadena& A, const Cadena& B);
bool operator>(const Cadena& A, const Cadena& B);
bool operator!=(const Cadena& A, const Cadena& B);
bool operator>=(const Cadena& A, const Cadena& B);
bool operator<=(const Cadena& A, const Cadena& B);

#endif