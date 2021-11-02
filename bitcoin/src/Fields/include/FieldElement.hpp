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
    friend std::ostream& operator<<(std::ostream& os, const FieldElement& element);
    
    int Number;
    int Prime;
};

bool operator==(const FieldElement& lhs, const FieldElement& rhs)
{
    return lhs.Number == rhs.Number && lhs.Prime == rhs.Prime;
}

bool operator!=(const FieldElement& lhs, const FieldElement& rhs)
{
    return lhs.Number != rhs.Number || lhs.Prime != rhs.Prime;
}

std::ostream& operator<<(std::ostream& os, const FieldElement& element)
{
    // write obj to stream
    os << "FieldElement_" << element.Prime << "(" << element.Number << ")";
    return os;
}

}
