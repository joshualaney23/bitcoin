#include "Point.hpp"

#include <exception>
#include <sstream>

namespace crypto
{

Point::Point(int x, int y, int a, int b)
    : Point(std::optional<int>(x), std::optional<int>(y), a, b)
{
    // Do nothing
}

Point::Point(std::optional<int> x, std::optional<int> y, int a, int b)
   : X(x)
   , Y(y)
   , A(a)
   , B(b)
{
    // Avoid infinity point
    if (!X && !Y)
        return;

    // Handle case where one of these values is null. This will prevent edge cases in operator+
    if (!X || !Y)
        throw std::runtime_error("X and Y values must either both be null or both non-null");

    // y^2 = x^3 + ax + b is the formula for the curve
    if (Y.value() * Y.value() != X.value() * X.value() * X.value() + (A * X.value()) + B)
    {
        std::stringstream error;
        error << "(" << X.value() << ", " << Y.value() << ") is not on the curve";
        throw std::runtime_error(error.str());
    }
}

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y
        && lhs.A == rhs.A && lhs.B == rhs.B;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs == rhs);
}

Point operator+(const Point& lhs, const Point& rhs)
{
    // Elements must be on the same curve
    if (lhs.A != rhs.A || lhs.B != rhs.B)
    {
        std::stringstream error;
        error << "Points " << lhs << ", " << rhs << "are not on the same curve";
        throw std::runtime_error(error.str());
    }

    // Handle infinity point
    if (!lhs.X)
        return rhs;
    if (!rhs.X)
        return lhs;

    // Handle vertical line
    if (lhs.X == rhs.X && lhs.Y != rhs.Y)
        return Point(std::nullopt, std::nullopt, lhs.A, lhs.B);

    // Handle X1 != X2
    if (lhs.X != rhs.X)
    {
        // TODO: Ensure Y values exist by overloading the subtraction operator
        auto slope = (rhs.Y.value() - lhs.Y.value()) / (rhs.X.value() - lhs.X.value());
        auto x3 = slope * slope - lhs.X.value() - rhs.X.value();
        auto y3 = slope * (lhs.X.value() - x3) - lhs.Y.value();
        return Point(x3, y3, lhs.A, lhs.B);
    }

    // Handle special case of vertical tangent line.
    // TODO: Book has this in Python as `if self == other and self.y == 0 * self.x:`
    if (lhs == rhs && lhs.Y.value() == 0)
        return Point(std::nullopt, std::nullopt, lhs.A, lhs.B);

    // Handle P1 = P2
    if (lhs == rhs)
    {
        // TODO: Ensure values exist
        auto slope = ((3 * lhs.X.value() * lhs.X.value()) + lhs.A) / (2 * lhs.Y.value());
        auto x3 = slope * slope - 2 * lhs.X.value();
        auto y3 = slope * (lhs.X.value() - x3) - lhs.Y.value();
        return Point(x3, y3, lhs.A, lhs.B);
    }

    // Handle this possible error condition
    return Point(0, 0, 0, 0);
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    // Write Point to stream
    if (!point.X)
        os << "Point(infinity)";
    else
        os << "Point(" << point.X.value() << "," << point.Y.value() << ")_" << point.A << "_" << point.B;

    return os;
}

bool operator==(const std::optional<int>& lhs, const std::optional<int>& rhs)
{
    // Both are NULL
    if (!lhs && !rhs)
        return true;
    // Only 1 is NULL
    if (!lhs || !rhs)
        return false;
    // Normal comparison
    return lhs.value() == rhs.value();
}

bool operator!=(const std::optional<int>& lhs, const std::optional<int>& rhs)
{
    return !(lhs == rhs);
}

} // namespace crypto
