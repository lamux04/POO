#include <stddef.h>
#include <string.h>

#include "Cadena.hpp"

const char vacia{ '\0' };

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
    s_ = new char[tam + 1];
    strcpy(s_, A);
    tam_ = tam;
    delete[] t;
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
    s_ = new char[tam_ + 1];
    strcpy(s_, t);
    strcat(s_, A.s_);
    delete[] t;

    return *this;
}

Cadena& operator+(const Cadena& A, const Cadena& B)
{
    Cadena res;
    res.s_ = new char[A.tam_ + B.tam_ + 1];
    strcpy(res.s_, A.s_);
    strcat(res.s_, B.s_);
    res.tam_ = A.tam_ + B.tam_;
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