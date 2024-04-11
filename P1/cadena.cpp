#include <cstddef>
#include <cstring>
#include <string>
#include <stdexcept>
#include <iostream>
#include <iterator>

#include "cadena.hpp"

char Cadena::vacia[1] = "";

Cadena::Cadena(size_t n /* = 0 */, char c /* = ' ' */) noexcept : tam_(n)
{
    if (tam_ == 0)
        s_ = vacia;
    else
    {
        s_ = new char[tam_ + 1];
        for (size_t i = 0; i < tam_; ++i)
            s_[i] = c;

        s_[tam_] = '\0';
    }
}

Cadena::Cadena(const Cadena& A) : tam_(A.tam_)
{
    if (tam_ == 0)
        s_ = vacia;
    else
    {
        s_ = new char[A.tam_ + 1];
        strcpy(s_, A.s_);
    }
}

Cadena::Cadena(Cadena&& A) : tam_(A.tam_)
{
    s_ = A.s_;
    A.tam_ = 0;
    A.s_ = vacia;
}

Cadena::Cadena(const char *cad) : tam_(strlen(cad))
{
    if (tam_ == 0)
        s_ = vacia;
    else
    {
        s_ = new char[tam_ + 1];
        strcpy(s_, cad);
    }
}

Cadena& Cadena::operator=(const Cadena& A)
{
    if (this != &A)
    {
        char *t = s_;
        if (A.s_ == vacia)
            s_ = vacia;
        else
        {
            s_ = new char[A.tam_ + 1];
            strcpy(s_, A.s_);
        }
        tam_ = A.tam_;
        if (t != vacia)
            delete[] t;
    }

    return *this;
}

Cadena& Cadena::operator=(Cadena&& A)
{
    if (this != &A)
    {
        s_ = A.s_;
        tam_ = A.tam_;
        A.s_ = vacia;
        A.tam_ = 0;
    }

    return *this;
}

Cadena& Cadena::operator=(const char *A)
{
    char *t = s_;
    int tam = strlen(A);
    if (strcmp(A, s_) != 0)
    {
        if (tam == 0)
            s_ = vacia;
        else
        {
            s_ = new char[tam + 1];
            strcpy(s_, A);
        }
        if (t != vacia)
            delete[] t;
    }
    tam_ = tam;
    return *this;
}

Cadena::operator const char*() const
{
    return s_;
}

Cadena& Cadena::operator+=(const Cadena& A)
{
    char *t = s_;
    int tam = tam_ + A.tam_;
    if (tam == 0)
        s_ = vacia;
    else
    {
        s_ = new char[tam + 1];
        strcpy(s_, t);
        strcat(s_, A.s_);
    }
    if (t != vacia)
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
    return strcmp((const char*)A, (const char*)B) == 0;
}

bool operator<(const Cadena& A, const Cadena& B)
{
    return strcmp((const char*)A, (const char*)B) < 0;
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

char Cadena::operator[](size_t i) const noexcept
{
    return s_[i];
}
char& Cadena::operator[](size_t i) noexcept
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

// P1

std::ostream& operator<<(std::ostream& os, const Cadena& A)
{
    os << A.s_;
    return os;
}

std::istream& operator>>(std::istream& is, Cadena& A)
{
    int j = 0;
    char cad[33], cad2[33];
    cad[0] = '\0';
    // is.width(33);
    // is >> cad;
    char c;
    while (is.get(c) && isspace(c));
    if (is)
    {
        cad[0] = c;
        is.get(cad + 1, 32, ' ');
    }
    for (int i = 0; i <= 32 && cad[i] != '\0' && !(j != 0 && isspace(cad[i])); ++i)
        if (!isspace(cad[i]))
        {
            cad2[j] = cad[i];
            ++j;
        }
    cad2[j] = '\0';

    if (j == 0)
        A = Cadena();
    else
        A = Cadena(cad2);
    return is;
}