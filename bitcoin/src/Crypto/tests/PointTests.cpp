#include <gtest/gtest.h>

#include "Point.hpp"

using namespace crypto;

TEST(PointTests, NotEqualTest)
{
   auto a = Point(3, -7, 5, 7);
   auto b = Point(18, 77, 5, 7);
   ASSERT_TRUE(a != b);
   ASSERT_FALSE(a != a);
}

TEST(PointTests, Add0Test)
{
   auto a = Point(std::optional<int>(), std::optional<int>(), 5, 7);
   auto b = Point(2, 5, 5, 7);
   auto c = Point(2, -5, 5, 7);

   ASSERT_EQ(a + b, b);
   ASSERT_EQ(b + a, b);
   ASSERT_EQ(b + c, a);
}

TEST(PointTests, Add1Test)
{
   auto a = Point(3, 7, 5, 7);
   auto b = Point(-1, -1, 5, 7);
   ASSERT_EQ(a + b, Point(2, -5, 5, 7));
}

TEST(PointTests, Add2Test)
{
   // P1 = P2
   auto a = Point(-1, -1, 5, 7);
   ASSERT_EQ(a + a, Point(18, 77, 5, 7));
}

TEST(PointTests, Add3Test)
{
   // Vertical tangent line
   auto a = Point(-1, 0, 1, 2);
   auto b = Point(-1, 0, 1, 2);
   ASSERT_EQ(a + b, Point(std::nullopt, std::nullopt, 1, 2));
}

TEST(PointTests, Add4Test)
{
   // Invalid Y
   EXPECT_THROW(Point(-1, std::nullopt, 1, 2), std::runtime_error);
   EXPECT_THROW(Point(std::nullopt, -1, 1, 2), std::runtime_error);
}

