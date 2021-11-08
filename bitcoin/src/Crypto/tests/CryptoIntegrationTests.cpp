#include <gtest/gtest.h>

#include "FieldElement.hpp"
#include "Point.hpp"

using namespace crypto;

TEST(IntegrationTests, AdditionOfFieldElements)
{
    auto prime = 223;
    auto a = FieldElement(0, prime);
    auto b = FieldElement(7, prime);
    auto x = FieldElement(192, prime);
    auto y = FieldElement(105, prime);
    auto point = Point<FieldElement>(x, y, a, b);

    ASSERT_EQ(point.X.value().Number, 192);
    ASSERT_EQ(point.Y.value().Number, 105);
    ASSERT_EQ(point.A.Number, 0);
    ASSERT_EQ(point.B.Number, 7);
    ASSERT_EQ(point.B.Prime, prime);
}

TEST(IntegrationTests, OnCurveTests)
{
    auto prime = 223;
    auto a = FieldElement(0, prime);
    auto b = FieldElement(7, prime);
    std::vector<std::pair<int, int>> validPoints {
        {192, 105},
        {17, 56},
        {1, 193}
    };
    std::vector<std::pair<int, int>> invalidPoints {
        {200, 119},
        {42, 99}
    };

    // for (auto point = validPoints.begin(); point != validPoints.end(); point++)
    for (auto point : validPoints)
    {
        auto x = FieldElement(point.first, prime);
        auto y = FieldElement(point.second, prime);
        auto validPoint = Point(x, y, a, b);

        ASSERT_EQ(validPoint.X.value().Number, point.first);
        ASSERT_EQ(validPoint.Y.value().Number, point.second);
        ASSERT_EQ(validPoint.A.Number, a.Number);
        ASSERT_EQ(validPoint.B.Number, b.Number);
        ASSERT_EQ(validPoint.B.Prime, prime);
    }

    for (auto point : invalidPoints)
    {
        auto x = FieldElement(point.first, prime);
        auto y = FieldElement(point.second, prime);
        EXPECT_THROW(Point(x, y, a, b), std::runtime_error);
    }
}

TEST(IntegrationTests, PointAdditionTests)
{
    auto prime = 223;
    auto a = FieldElement(0, prime);
    auto b = FieldElement(7, prime);
    auto x1 = FieldElement(192, prime);
    auto y1 = FieldElement(105, prime);
    auto x2 = FieldElement(17, prime);
    auto y2 = FieldElement(56, prime);
    auto p1 = Point<FieldElement>(x1, y1, a, b);
    auto p2 = Point<FieldElement>(x2, y2, a, b);

    // std::cout << p1 + p2 << std::endl;
    // ASSERT_EQ(point.X.value().Number, 192);
    // ASSERT_EQ(point.Y.value().Number, 105);
    // ASSERT_EQ(point.A.Number, 0);
    // ASSERT_EQ(point.B.Number, 7);
    // ASSERT_EQ(point.B.Prime, prime);
}
