#pragma once

#include <iostream>
#include <string>

namespace crypto
{

class FieldElement
{
  public:
    FieldElement(int number, int prime);
    ~FieldElement() = default;

    friend bool operator==(const FieldElement& lhs, const FieldElement& rhs);
    friend bool operator!=(const FieldElement& lhs, const FieldElement& rhs);
    friend FieldElement operator+(const FieldElement& lhs, const FieldElement& rhs);
    friend FieldElement operator-(const FieldElement& lhs, const FieldElement& rhs);
    friend FieldElement operator*(const FieldElement& lhs, const FieldElement& rhs);
    // Note: Bitwise OR is commandeered for the power operator
    friend FieldElement operator^(const FieldElement& lhs, const int& power);
    friend FieldElement operator/(const FieldElement& lhs, const FieldElement& rhs);
    friend std::ostream& operator<<(std::ostream& os, const FieldElement& element);
    
    int Number;
    int Prime;
};

} // namespace crypto
