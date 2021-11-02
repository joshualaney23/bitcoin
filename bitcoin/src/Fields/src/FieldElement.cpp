//
//  FieldElement.cpp
//  bitcoin
//
//  Created by Josh Laney on 11/1/21.
//  Copyright © 2021 Josh Laney. All rights reserved.
//

#include "FieldElement.hpp"

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

}
