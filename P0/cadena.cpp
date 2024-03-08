#include <stddef.h>
#include <string.h>
#include <stdexcept>

#include "cadena.hpp"

const char Cadena::vacia[1] = "";

Cadena::Cadena(size_t n /* = 0 */, char c /* = ' ' */) : tam_(n), s_(new char[n + 1])
{
    for (size_t i = 0; i < tam_; ++i)
        s_[i] = c;

    s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& A) : tam_(A.tam_), s_(new char[A.tam_ + 1])
{
    strcpy(s_, A.s_);
}

Cadena::Cadena(const char *cad) : tam_(strlen(cad)), s_(new char[tam_ + 1])
{
    strcpy(s_, cad);
}

Cadena& Cadena::operator=(const Cadena& A)
{
    if (this != &A)
    {
        char *t = s_;
        s_ = new char[A.tam_ + 1];
        strcpy(s_, A.s_);
        tam_ = A.tam_;
        delete[] t;
    }

    return *this;
}

Cadena& Cadena::operator=(const char *A)
{
    char *t = s_;
    int tam = strlen(A);
    if (strcmp(A, s_) != 0)
    {
        s_ = new char[tam + 1];
        strcpy(s_, A);
        delete[] t;
    }
    tam_ = tam;
    return *this;
}

Cadena::operator const char*() const
{
    if (tam_ == 0) return vacia;
    return s_;
}

Cadena& Cadena::operator+=(const Cadena& A)
{
    char *t = s_;
    int tam = tam_ + A.tam_;
    s_ = new char[tam + 1];
    strcpy(s_, t);
    strcat(s_, A.s_);
    delete[] t;
    tam_ = tam;

    return *this;
}

Cadena operator+(const Cadena& A, const Cadena& B)
{
    Cadena res(A);
    res += B;
    return res;
}

bool operator==(const Cadena& A, const Cadena& B)
{
    return strcmp(A.s_, B.s_) == 0;
}

bool operator<(const Cadena& A, const Cadena& B)
{
    return strcmp(A.s_, B.s_) < 0;
}

bool operator>(const Cadena& A, const Cadena& B)
{
    return B < A;
}

bool operator!=(const Cadena& A, const Cadena& B)
{
    return !(A == B);
}

bool operator>=(const Cadena& A, const Cadena& B)
{
    return !(A < B);
}

bool operator<=(const Cadena& A, const Cadena& B)
{
    return !(B < A);
}

char Cadena::operator[](size_t i) const
{
    return s_[i];
}
char& Cadena::operator[](size_t i)
{
    return s_[i];
}

char Cadena::at(size_t i) const
{
    if (i < 0 || i >= tam_)
        throw std::out_of_range("El índice no es válido");
    return s_[i];
}

char& Cadena::at(size_t i)
{
    if (i < 0 || i >= tam_)
        throw std::out_of_range("El índice no es válido");
    return s_[i];
}

Cadena Cadena::substr(int indice, int tama) const
{
    if (indice < 0 || indice >= tam_)
        throw std::out_of_range("El índice no es válido");
    if (tama < 0 || tama + indice - 1 >= tam_)
        throw std::out_of_range("El tamaño está fuera de rango");
    Cadena A(tama, ' ');
    for (size_t i = 0; i < tama; ++indice, ++i)
        A.s_[i] = s_[indice];

    return A;
}