#include <gtest/gtest.h>

#include "FieldElement.hpp"

using namespace crypto;

TEST(FieldElementTests, NotEqualTest)
{
   auto a = FieldElement(2, 31);
   auto b = FieldElement(2, 31);
   auto c = FieldElement(15, 31);
   ASSERT_EQ(a, b);
   ASSERT_TRUE(a != c);
   ASSERT_FALSE(a != b);
}

TEST(FieldElementTests, AddTest)
{
   auto a = FieldElement(2, 31);
   auto b = FieldElement(15, 31);
   ASSERT_EQ(a + b, FieldElement(17, 31));
   
   auto c = FieldElement(17, 31);
   auto d = FieldElement(21, 31);
   ASSERT_EQ(c + d, FieldElement(7, 31));
}

TEST(FieldElementTests, SubtractTest)
{
   auto a = FieldElement(29, 31);
   auto b = FieldElement(4, 31);
   ASSERT_EQ(a - b, FieldElement(25, 31));
   
   auto c = FieldElement(15, 31);
   auto d = FieldElement(30, 31);
   ASSERT_EQ(c - d, FieldElement(16, 31));

   auto e = FieldElement(0, 31);
   auto f = FieldElement(30, 31);
   ASSERT_EQ(e - f, FieldElement(1, 31));
}

TEST(FieldElementTests, MultiplyTest)
{
   auto a = FieldElement(24, 31);
   auto b = FieldElement(19, 31);
   ASSERT_EQ(a * b, FieldElement(22, 31));
}

TEST(FieldElementTests, PowerTest)
{
   auto a = FieldElement(17, 31);
   ASSERT_EQ(a ^ 3, FieldElement(15, 31));
   
   auto b = FieldElement(5, 31);
   auto c = FieldElement(18, 31);
   ASSERT_EQ((b ^ 5) * c, FieldElement(16, 31));

   auto d = FieldElement(17, 31);
   ASSERT_EQ(d ^ 300000, FieldElement(1, 31));
}

TEST(FieldElementTests, DivisionTest)
{
   auto a = FieldElement(3, 31);
   auto b = FieldElement(24, 31);
   ASSERT_EQ(a / b, FieldElement(4, 31));
   
   auto c = FieldElement(17, 31);
   ASSERT_EQ(c ^ -3, FieldElement(29, 31));
   
   auto d = FieldElement(4, 31);
   auto e = FieldElement(11, 31);
   ASSERT_EQ((d ^ -4) * e, FieldElement(13, 31));
}

bool OnCurve(FieldElement x, FieldElement y)
{
   auto a = FieldElement(0, 223);
   auto b = FieldElement(7, 223);
   return (y ^ 2) == ((x ^ 3) + a * x + b);
}

TEST(FieldElementTests, Chapter3Exercise1Test)
{
   ASSERT_TRUE(OnCurve(FieldElement(192, 223), FieldElement(105, 223)));
   ASSERT_TRUE(OnCurve(FieldElement(17, 223), FieldElement(56, 223)));
   ASSERT_FALSE(OnCurve(FieldElement(200, 223), FieldElement(119, 223)));
   ASSERT_TRUE(OnCurve(FieldElement(1, 223), FieldElement(193, 223)));
   ASSERT_FALSE(OnCurve(FieldElement(42, 223), FieldElement(99, 223)));
}
