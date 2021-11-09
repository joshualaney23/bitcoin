#pragma once

#include "Helpers.hpp"

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

namespace crypto
{

template<class T> class FieldElement
{
  public:
    FieldElement(T number, T prime);
    ~FieldElement() = default;

    template<class U> friend bool operator==(const FieldElement& lhs, const FieldElement& rhs);
    template<class U> friend bool operator!=(const FieldElement& lhs, const FieldElement& rhs);
    template<class U> friend FieldElement operator+(const FieldElement& lhs, const FieldElement& rhs);
    template<class U> friend FieldElement operator-(const FieldElement& lhs, const FieldElement& rhs);
    template<class U> friend FieldElement operator*(const FieldElement& lhs, const FieldElement& rhs);
    // Note: Bitwise OR is commandeered for the power operator
    template<class U> friend FieldElement operator^(const FieldElement& lhs, const int& power);
    template<class U> friend FieldElement operator/(const FieldElement& lhs, const FieldElement& rhs);
    template<class U> friend std::ostream& operator<<(std::ostream& os, const FieldElement& element);

    T Number;
    T Prime;
};

template<class T>
FieldElement<T>::FieldElement(T number, T prime)
  : Number(number)
  , Prime(prime)
{
    // Valid between 0 and N-1
    if (Number < 0 || Number >= Prime)
    {
        std::stringstream error;
        error << "Number " << Number << " not in field range [0," << Prime - 1 << "].";
        throw std::runtime_error(error.str());
    }
}

template<class T> bool operator==(const FieldElement<T>& lhs, const FieldElement<T>& rhs)
{
    return lhs.Number == rhs.Number && lhs.Prime == rhs.Prime;
}

template<class T> bool operator!=(const FieldElement<T>& lhs, const FieldElement<T>& rhs)
{
    return !(lhs == rhs);
}

template<class T> FieldElement<T> operator+(const FieldElement<T>& lhs, const FieldElement<T>& rhs)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (lhs.Prime != rhs.Prime)
    {
        throw std::runtime_error("Cannot add two numbers in different fields");
    }

    auto number = (lhs.Number + rhs.Number) % lhs.Prime;
    return FieldElement<T>(number, lhs.Prime);
}

template<class T> FieldElement<T> operator-(const FieldElement<T>& lhs, const FieldElement<T>& rhs)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (lhs.Prime != rhs.Prime)
    {
        throw std::runtime_error("Cannot substract two numbers in different fields");
    }

    // Negative lhs % in C++ results in a negative rhs. Make lhs positive before the modulus
    auto number = (lhs.Prime + (lhs.Number - rhs.Number)) % lhs.Prime;
    return FieldElement<T>(number, lhs.Prime);
}

template<class T> FieldElement<T> operator*(const FieldElement<T>& lhs, const FieldElement<T>& rhs)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (lhs.Prime != rhs.Prime)
    {
        throw std::runtime_error("Cannot multiply two numbers in different fields");
    }

    auto number = (lhs.Number * rhs.Number) % lhs.Prime;
    return FieldElement<T>(number, lhs.Prime);
}

template<class T> FieldElement<T> operator^(const FieldElement<T>& lhs, const int& power)
{
    // a^(p-1) = 1, so exploit this to force the power to be positive
    auto exponent = power;
    while (exponent < 0)
        exponent += lhs.Prime - 1;
    auto number = PowerModulo(lhs.Number, exponent, lhs.Prime);
    return FieldElement<T>(number, lhs.Prime);
}

template<class T> FieldElement<T> operator/(const FieldElement<T>& lhs, const FieldElement<T>& rhs)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (lhs.Prime != rhs.Prime)
    {
        throw std::runtime_error("Cannot divide two numbers in different fields");
    }

    // Fermat's Little Theorem: Number^(Prime-1) % Prime == 1, or 1/Number == pow(Number, Prime - 2, Prime)
    auto number = (lhs.Number * (PowerModulo(rhs.Number, lhs.Prime - 2, lhs.Prime))) % lhs.Prime;
    return FieldElement<T>(number, lhs.Prime);
}

template<class T> std::ostream& operator<<(std::ostream& os, const FieldElement<T>& element)
{
    // Write FieldElement to stream
    os << "FieldElement_" << element.Prime << "(" << element.Number << ")";
    return os;
}

} // namespace crypto
