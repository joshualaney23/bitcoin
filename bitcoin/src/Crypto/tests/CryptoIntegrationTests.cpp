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

   ASSERT_EQ(point.X.value().Number, 192);
   ASSERT_EQ(point.Y.value().Number, 105);
   ASSERT_EQ(point.A.Number, 0);
   ASSERT_EQ(point.B.Number, 7);
   ASSERT_EQ(point.B.Prime, 223);
}
