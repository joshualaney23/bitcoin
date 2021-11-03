//
//  FieldElement.cpp
//  bitcoin
//
//  Created by Josh Laney on 11/1/21.
//  Copyright © 2021 Josh Laney. All rights reserved.
//

#include "FieldElement.hpp"

#include <cmath>
#include <exception>

namespace field
{

FieldElement::FieldElement(int number, int prime)
   : Number(number)
   , Prime(prime)
{
   // Valid between 0 and N-1
   if (Number < 0 || Number >= Prime)
   {
       std::stringstream error;
       error << "Number " << Number << " not in field range [0," << Prime-1 << "].";
       throw std::runtime_error(error.str());
   }
}

bool operator==(const FieldElement& lhs, const FieldElement& rhs)
{
    return lhs.Number == rhs.Number && lhs.Prime == rhs.Prime;
}

bool operator!=(const FieldElement& lhs, const FieldElement& rhs)
{
    return lhs.Number != rhs.Number || lhs.Prime != rhs.Prime;
}

FieldElement operator+(const FieldElement& other)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (Prime != other.Prime)
    {
        throw std::runtime_error("Cannot add two numbers in different fields");
    }

    auto number = (Number + other.Number) % Prime;
    return FieldElement(number, Prime);
}

FieldElement operator-(const FieldElement& other)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (Prime != other.Prime)
    {
        throw std::runtime_error("Cannot substract two numbers in different fields");
    }

    auto number = (Number - other.Number) % Prime;
    return FieldElement(number, Prime);
}

FieldElement operator*(const FieldElement& other)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (Prime != other.Prime)
    {
        throw std::runtime_error("Cannot multiply two numbers in different fields");
    }

    auto number = (Number * other.Number) % Prime;
    return FieldElement(number, Prime);
}

FieldElement operator^(const int& power)
{
    // a^(p-1) = 1, so exploit this to force the power to be positive
    auto n = power % (Prime - 1)
    auto number = PowerModulo(Number, n, Prime);
    return FieldElement(number, Prime);
}

FieldElement operator/(const FieldElement& other)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (Prime != other.Prime)
    {
        throw std::runtime_error("Cannot divide two numbers in different fields");
    }

    // Fermat's Little Theorem: Number^(Prime-1) % Prime == 1, or 1/Number == pow(Number, Prime - 2, Prime)
    auto number = (Number * (PowerModulo(other.Number, Prime - 2, Prime)) % Prime;
    return FieldElement(number, Prime);
}

std::ostream& operator<<(std::ostream& os, const FieldElement& element)
{
    // write obj to stream
    os << "FieldElement_" << element.Prime << "(" << element.Number << ")";
    return os;
}

int FieldElement::PowerModulo(int a, int b, int modulus)
{
    int x = 1, y = a;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = x * y;
            x %= modulus;
        }

        y = y * y;
        y %= modulus;

        b /= 2;
    }

    return x;
}

}
