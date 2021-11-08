#include <gtest/gtest.h>

#include "FieldElement.hpp"
#include "Point.hpp"

using namespace crypto;

TEST(IntegrationTests, AdditionOfFieldElements)
{
   auto a = FieldElement(0, 223);
   auto b = FieldElement(7, 223);
   auto x = FieldElement(192, 223);
   auto y = FieldElement(105, 223);
   auto point = Point<FieldElement>(x, y, a, b);
   std::cout << point;
}
