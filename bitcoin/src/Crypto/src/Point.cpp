//
//  FieldElement.cpp
//  bitcoin
//
//  Created by Josh Laney on 11/1/21.
//  Copyright © 2021 Josh Laney. All rights reserved.
//

#include "FieldElement.hpp"

#include <exception>

namespace crypto
{

Point::Point(int x, int y, int a, int b);
   : X(x)
   , Y(y)
   , A(a)
   , B(b)
{
    // Avoid infinity point
    if (x == null && y == null)
        return;

    // y^2 = x^3 + ax + b is the formula for the curve
    if (Y*Y != X*X*X + (A * X) + B)
    {
        std::stringstream error;
        error << "(" << X << ", " << Y << ") is not on the curve";
        throw std::runtime_error(error.str());
    }
}

bool operator==(const FieldElement& lhs, const FieldElement& rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.A == rhs.A && lhs.B == rhs.B;
}

bool operator!=(const FieldElement& lhs, const FieldElement& rhs)
{
    return !(lhs == rhs);
}

Point operator+(const Point& other)
{
    // Elements must be on the same curve
    if (A != other.A || B != other.B)
    {
        std::stringstream error;
        error << "Points " << this << ", " << other << "are not on the same curve";
        throw std::runtime_error(error.str());
    }

    // Handle infinity point
    if (X == null)
        return other;
    if (other.X == null)
        return this;

    // Handle vertical line
    if (X == other.X && Y != other.Y)
        return Point(null, null, A, B);

    // Handle X1 != X2
    if (X != other.X)
    {
        auto slope = (other.Y - Y) / (other.X - X);
        auto x3 = slope * slope - X - other.X;
        auto y3 = slope * (X - x3) - Y;
        return Point(x3, y3, A, B);
    }
}






FieldElement operator-(const FieldElement& other)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (Prime != other.Prime)
    {
        throw std::runtime_error("Cannot substract two numbers in different fields");
    }

    auto number = (Number - other.Number) % Prime;
    return FieldElement(number, Prime);
}

FieldElement operator*(const FieldElement& other)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (Prime != other.Prime)
    {
        throw std::runtime_error("Cannot multiply two numbers in different fields");
    }

    auto number = (Number * other.Number) % Prime;
    return FieldElement(number, Prime);
}

FieldElement operator^(const int& power)
{
    // a^(p-1) = 1, so exploit this to force the power to be positive
    auto n = power % (Prime - 1)
    auto number = PowerModulo(Number, n, Prime);
    return FieldElement(number, Prime);
}

FieldElement operator/(const FieldElement& other)
{
    // Elements must be in the same finite field, otherwise the calculation is meaningless
    if (Prime != other.Prime)
    {
        throw std::runtime_error("Cannot divide two numbers in different fields");
    }

    // Fermat's Little Theorem: Number^(Prime-1) % Prime == 1, or 1/Number == pow(Number, Prime - 2, Prime)
    auto number = (Number * (PowerModulo(other.Number, Prime - 2, Prime)) % Prime;
    return FieldElement(number, Prime);
}






std::ostream& operator<<(std::ostream& os, const Point& point)
{
    // Write Point to stream
    if (point.X == null)
        os << 'Point(infinity)';
    else
        os << "Point(" << point.X << ", " << point.Y << ")_" << point.A << "_" << point.B;

    return os;
}

} // namespace crypto
