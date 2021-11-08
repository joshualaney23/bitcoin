#include "FieldElement.hpp"
#include "Helpers.hpp"

#include <exception>
#include <sstream>

namespace crypto
{

FieldElement::FieldElement(int number, int prime)
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

bool operator==(const FieldElement& lhs, const FieldElement& rhs)
{
    return lhs.Number == rhs.Number && lhs.Prime == rhs.Prime;
}

bool operator!=(const FieldElement& lhs, const FieldElement& rhs)
{
    return !(lhs == rhs);
}

FieldElement operator+(const FieldElement& lhs, const FieldElement& rhs)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (lhs.Prime != rhs.Prime)
    {
        throw std::runtime_error("Cannot add two numbers in different fields");
    }

    auto number = (lhs.Number + rhs.Number) % lhs.Prime;
    return FieldElement(number, lhs.Prime);
}

FieldElement operator-(const FieldElement& lhs, const FieldElement& rhs)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (lhs.Prime != rhs.Prime)
    {
        throw std::runtime_error("Cannot substract two numbers in different fields");
    }

    // Negative lhs % in C++ results in a negative rhs. Make lhs positive before the modulus
    auto number = (lhs.Prime + (lhs.Number - rhs.Number)) % lhs.Prime;
    return FieldElement(number, lhs.Prime);
}

FieldElement operator*(const FieldElement& lhs, const FieldElement& rhs)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (lhs.Prime != rhs.Prime)
    {
        throw std::runtime_error("Cannot multiply two numbers in different fields");
    }

    auto number = (lhs.Number * rhs.Number) % lhs.Prime;
    return FieldElement(number, lhs.Prime);
}

FieldElement operator^(const FieldElement& lhs, const int& power)
{
    // a^(p-1) = 1, so exploit this to force the power to be positive
    auto exponent = power;
    while (exponent < 0)
        exponent += lhs.Prime - 1;
    auto number = PowerModulo(lhs.Number, exponent, lhs.Prime);
    return FieldElement(number, lhs.Prime);
}

FieldElement operator/(const FieldElement& lhs, const FieldElement& rhs)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (lhs.Prime != rhs.Prime)
    {
        throw std::runtime_error("Cannot divide two numbers in different fields");
    }

    // Fermat's Little Theorem: Number^(Prime-1) % Prime == 1, or 1/Number == pow(Number, Prime - 2, Prime)
    auto number = (lhs.Number * (PowerModulo(rhs.Number, lhs.Prime - 2, lhs.Prime))) % lhs.Prime;
    return FieldElement(number, lhs.Prime);
}

std::ostream& operator<<(std::ostream& os, const FieldElement& element)
{
    // Write FieldElement to stream
    os << "FieldElement_" << element.Prime << "(" << element.Number << ")";
    return os;
}

} // namespace crypto
