//
//  FieldElement.hpp
//  bitcoin
//
//  Created by Josh Laney on 11/1/21.
//  Copyright © 2021 Josh Laney. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>

namespace field
{

class FieldElement
{
  public:
    FieldElement(int number, int prime);
    ~FieldElement() = default;

    friend bool operator==(const FieldElement& lhs, const FieldElement& rhs);
    friend bool operator!=(const FieldElement& lhs, const FieldElement& rhs);
    friend FieldElement operator+(const FieldElement& other);
    friend FieldElement operator-(const FieldElement& other);
    friend FieldElement operator*(const FieldElement& other);
    // Note: Bitwise OR is commandeered for the power operator
    friend FieldElement operator^(const int& power);
    friend FieldElement operator/(const FieldElement& other);
    friend std::ostream& operator<<(std::ostream& os, const FieldElement& element);
    
    int Number;
    int Prime;
};

}
