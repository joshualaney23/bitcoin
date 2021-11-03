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
    auto number = std::pow(Number, power) % Prime;
    return FieldElement(number, Prime);
}

std::ostream& operator<<(std::ostream& os, const FieldElement& element)
{
    // write obj to stream
    os << "FieldElement_" << element.Prime << "(" << element.Number << ")";
    return os;
}

}
