#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <stddef.h>
#include <iostream>

class Cadena
{
public:
    /* CONSTRUCTORES */
    explicit Cadena(size_t n = 0, char c = ' ') noexcept;
    Cadena(const char *cad);
    Cadena(const Cadena& A);
    Cadena(Cadena&& A);

    /* METODOS PUBLICOS */
    size_t length() const noexcept { return tam_; }
    char at(size_t i) const;
    char& at(size_t i);
    Cadena substr(int indice, int tama) const;

    /* OPERADORES DE CONVERSION */
    explicit operator const char*() const;

    /* OPERADORES */
    Cadena& operator=(const Cadena& A);
    Cadena& operator=(Cadena&& A);
    Cadena& operator=(const char *A);
    Cadena& operator+=(const Cadena& A);
    char operator[](size_t i) const noexcept;
    char& operator[](size_t i) noexcept;

    /* DESTRUCTOR */
    ~Cadena() { if (s_ != vacia) delete[] s_; }

    /* FUNCIONES AMIGAS */
    friend std::ostream& operator<<(std::ostream& os, const Cadena& A);

    /* ITERADORES */
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;
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

std::istream& operator>>(std::istream& is, Cadena& A);

inline Cadena::iterator Cadena::begin() noexcept
{
    return s_;
}

inline Cadena::const_iterator Cadena::begin() const noexcept
{
    return s_;
}

inline Cadena::const_iterator Cadena::cbegin() const noexcept
{
    return s_;
}

inline Cadena::iterator Cadena::end() noexcept
{
    return s_ + tam_;
}

inline Cadena::const_iterator Cadena::end() const noexcept
{
    return s_ + tam_;
}

inline Cadena::const_iterator Cadena::cend() const noexcept
{
    return s_ + tam_;
}

inline Cadena::reverse_iterator Cadena::rbegin() noexcept
{
    return reverse_iterator(end());
}

inline Cadena::reverse_iterator Cadena::rend() noexcept
{
    return reverse_iterator(begin());
}

inline Cadena::const_reverse_iterator Cadena::rbegin() const noexcept
{
    return const_reverse_iterator(end());
}

inline Cadena::const_reverse_iterator Cadena::rend() const noexcept
{
    return const_reverse_iterator(begin());
}

inline Cadena::const_reverse_iterator Cadena::crbegin() const noexcept
{
    return const_reverse_iterator(end());
}

inline Cadena::const_reverse_iterator Cadena::crend() const noexcept
{
    return const_reverse_iterator(begin());
}

template <> // Es una especializaci ón de una plantilla para Cadena.
struct std::hash<Cadena> { // Es una clase con solo un operador público.
    size_t operator() (const Cadena& cad) const // El operador función.
    {
        std::hash<string> hs; // Creamos un objeto hash de string.
        auto p{ (const char*)(cad) }; // Convertimos Cadena a cadena de bajo nivel.
        std::string s{ p }; // Creamos un string desde la cadena de b. nivel .
        size_t res{ hs(s) }; // El hash del string . Como hs.operator()(s);
        return res; // Devolvemos el hash del string .
        // En forma abreviada:
        // return hash<string>{}((const char*)(cad));
    }
};

#endif