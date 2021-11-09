#include <gtest/gtest.h>

#include "FieldElement.hpp"
#include "Point.hpp"

#include <boost/multiprecision/cpp_int.hpp>

using namespace crypto;

TEST(IntegrationTests, AdditionOfFieldElements)
{
    auto prime = 223;
    auto a = FieldElement(0, prime);
    auto b = FieldElement(7, prime);
    auto x = FieldElement(192, prime);
    auto y = FieldElement(105, prime);
    auto point = Point<FieldElement<int>>(x, y, a, b);

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
    std::vector<std::pair<int, int>> validPoints{{192, 105}, {17, 56}, {1, 193}};
    std::vector<std::pair<int, int>> invalidPoints{{200, 119}, {42, 99}};

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
    auto p1 = Point<FieldElement<int>>(x1, y1, a, b);
    auto p2 = Point<FieldElement<int>>(x2, y2, a, b);
    auto p3 = p1 + p2;

    ASSERT_EQ(p3.X.value().Number, 170);
    ASSERT_EQ(p3.Y.value().Number, 142);
    ASSERT_EQ(p3.A.Number, 0);
    ASSERT_EQ(p3.B.Number, 7);
    ASSERT_EQ(p3.B.Prime, prime);
}

TEST(IntegrationTests, PointAddition2Tests)
{
    // tests the following additions on curve y^2=x^3-7 over F_223:
    // (192,105) + (17,56)
    // (47,71) + (117,141)
    // (143,98) + (76,66)
    std::vector<std::vector<int>> additions = {// (x1, y1, x2, y2, x3, y3)
                                               {192, 105, 17, 56, 170, 142},
                                               {47, 71, 117, 141, 60, 139},
                                               {143, 98, 76, 66, 47, 71}};
    auto prime = 223;
    auto a = FieldElement<int>(0, prime);
    auto b = FieldElement<int>(7, prime);

    for (auto set : additions)
    {
        auto x1 = FieldElement<int>(set[0], prime);
        auto y1 = FieldElement<int>(set[1], prime);
        auto p1 = Point<FieldElement<int>>(x1, y1, a, b);
        auto x2 = FieldElement<int>(set[2], prime);
        auto y2 = FieldElement<int>(set[3], prime);
        auto p2 = Point<FieldElement<int>>(x2, y2, a, b);
        auto x3 = FieldElement<int>(set[4], prime);
        auto y3 = FieldElement<int>(set[5], prime);
        auto p3 = Point<FieldElement<int>>(x3, y3, a, b);

        ASSERT_EQ(p1 + p2, p3);
    }
}

TEST(IntegrationTests, PointMultiplicationTests)
{
    auto prime = 223;
    auto a = FieldElement(0, prime);
    auto b = FieldElement(7, prime);

    auto x1 = FieldElement(192, prime);
    auto y1 = FieldElement(105, prime);
    auto p1 = Point<FieldElement<int>>(x1, y1, a, b);
    auto point = p1 + p1;
    ASSERT_EQ(point.X.value().Number, 49);
    ASSERT_EQ(point.Y.value().Number, 71);
    ASSERT_EQ(point.A.Number, 0);
    ASSERT_EQ(point.B.Number, 7);
    ASSERT_EQ(point.B.Prime, prime);

    auto x2 = FieldElement(143, prime);
    auto y2 = FieldElement(98, prime);
    auto p2 = Point<FieldElement<int>>(x2, y2, a, b);
    point = p2 + p2;
    ASSERT_EQ(point.X.value().Number, 64);
    ASSERT_EQ(point.Y.value().Number, 168);
    ASSERT_EQ(point.A.Number, 0);
    ASSERT_EQ(point.B.Number, 7);
    ASSERT_EQ(point.B.Prime, prime);

    auto x3 = FieldElement(47, prime);
    auto y3 = FieldElement(71, prime);
    auto p3 = Point<FieldElement<int>>(x3, y3, a, b);
    point = p3 + p3;
    ASSERT_EQ(point.X.value().Number, 36);
    ASSERT_EQ(point.Y.value().Number, 111);
    ASSERT_EQ(point.A.Number, 0);
    ASSERT_EQ(point.B.Number, 7);
    ASSERT_EQ(point.B.Prime, prime);

    point = p3 + p3 + p3 + p3;
    ASSERT_EQ(point.X.value().Number, 194);
    ASSERT_EQ(point.Y.value().Number, 51);
    ASSERT_EQ(point.A.Number, 0);
    ASSERT_EQ(point.B.Number, 7);
    ASSERT_EQ(point.B.Prime, prime);

    point = p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3;
    ASSERT_EQ(point.X.value().Number, 116);
    ASSERT_EQ(point.Y.value().Number, 55);
    ASSERT_EQ(point.A.Number, 0);
    ASSERT_EQ(point.B.Number, 7);
    ASSERT_EQ(point.B.Prime, prime);

    // Infinity point
    point = p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3 + p3;
    ASSERT_EQ(point.X, std::nullopt);
    ASSERT_EQ(point.Y, std::nullopt);
    ASSERT_EQ(point.A.Number, 0);
    ASSERT_EQ(point.B.Number, 7);
    ASSERT_EQ(point.B.Prime, prime);
}

TEST(IntegrationTests, PointAdditionUint256tTests)
{
    using boost::multiprecision::uint256_t;
    uint256_t prime = 223;
    auto a = FieldElement<uint256_t>((uint256_t)0, prime);
    auto b = FieldElement<uint256_t>(7, prime);
    auto x1 = FieldElement<uint256_t>(192, prime);
    auto y1 = FieldElement<uint256_t>(105, prime);
    auto x2 = FieldElement<uint256_t>(17, prime);
    auto y2 = FieldElement<uint256_t>(56, prime);
    auto p1 = Point<FieldElement<uint256_t>>(x1, y1, a, b);
    auto p2 = Point<FieldElement<uint256_t>>(x2, y2, a, b);
    auto p3 = p1 + p2;

    ASSERT_EQ(p3.X.value().Number, 170);
    ASSERT_EQ(p3.Y.value().Number, 142);
    ASSERT_EQ(p3.A.Number, 0);
    ASSERT_EQ(p3.B.Number, 7);
    ASSERT_EQ(p3.B.Prime, prime);
}
