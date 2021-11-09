#pragma once

#include <exception>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <variant>

namespace crypto
{

// Forward declarations for template specialization
template<class T> class FieldElement;
template<class T> class Point;
template<class T> std::ostream& operator<<(std::ostream& out, const Point<T>& point);
template<class T> std::ostream& operator<<(std::ostream& out, const Point<FieldElement<T>>& point);
template<class T> Point<T> operator+(const Point<T>& lhs, const Point<T>& rhs);
template<class T>
Point<FieldElement<T>> operator+(const Point<FieldElement<T>>& lhs, const Point<FieldElement<T>>& rhs);

template<class T> class Point
{
  public:
    Point(T x, T y, T a, T b);
    Point(std::optional<T> x, std::optional<T> y, T a, T b);
    ~Point() = default;

    template<class U> friend bool operator==(const Point& lhs, const Point& rhs);
    template<class U> friend bool operator!=(const Point& lhs, const Point& rhs);
    template<class U> friend Point operator+(const Point& lhs, const Point& rhs);
    template<class U> friend Point operator*(const Point& lhs, const int& coefficient);
    template<class U> friend Point operator*(const int& coefficient, const Point& rhs);
    template<class U> friend std::ostream& operator<<(std::ostream& os, const Point<U>& element);

    std::optional<T> X;
    std::optional<T> Y;
    T A;
    T B;

  protected:
    template<class U> friend bool operator==(const std::optional<T>& lhs, const std::optional<T>& rhs);
    template<class U> friend bool operator!=(const std::optional<T>& lhs, const std::optional<T>& rhs);
};

template<class T>
Point<T>::Point(T x, T y, T a, T b)
  : Point(std::optional<T>(x), std::optional<T>(y), a, b)
{
    // Do nothing
}

template<class T>
Point<T>::Point(std::optional<T> x, std::optional<T> y, T a, T b)
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

template<class T> bool operator==(const Point<T>& lhs, const Point<T>& rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.A == rhs.A && lhs.B == rhs.B;
}

template<class T> bool operator!=(const Point<T>& lhs, const Point<T>& rhs)
{
    return !(lhs == rhs);
}

template<class T> Point<T> operator+(const Point<T>& lhs, const Point<T>& rhs)
{
    // Elements must be on the same curve
    if (lhs.A != rhs.A || lhs.B != rhs.B)
    {
        std::stringstream error;
        error << "Points " << lhs << ", " << rhs << " are not on the same curve";
        throw std::runtime_error(error.str());
    }

    // Handle infinity point
    if (!lhs.X)
        return rhs;
    if (!rhs.X)
        return lhs;

    // Handle vertical line
    if (lhs.X == rhs.X && lhs.Y != rhs.Y)
        return Point<T>(std::nullopt, std::nullopt, lhs.A, lhs.B);

    // Handle X1 != X2
    if (lhs.X != rhs.X)
    {
        // TODO: Ensure Y values exist by overloading the subtraction operator
        auto slope = (rhs.Y.value() - lhs.Y.value()) / (rhs.X.value() - lhs.X.value());
        auto x3 = slope * slope - lhs.X.value() - rhs.X.value();
        auto y3 = slope * (lhs.X.value() - x3) - lhs.Y.value();
        return Point<T>(x3, y3, lhs.A, lhs.B);
    }

    // Handle special case of vertical tangent line.
    // TODO: Book has this in Python as `if self == other and self.y == 0 * self.x:`
    if (lhs == rhs && lhs.Y.value() == 0)
        return Point<T>(std::nullopt, std::nullopt, lhs.A, lhs.B);

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
    std::stringstream error;
    error << "REACHED EDGE CASE: " << lhs << " + " << rhs;
    throw std::runtime_error(error.str());
}

template<class T> std::ostream& operator<<(std::ostream& os, const Point<T>& point)
{
    // Write Point to stream
    if (!point.X)
        os << "Point(infinity)";
    else
        os << "Point(" << point.X.value() << "," << point.Y.value() << ")_" << point.A << "_" << point.B;

    return os;
}

template<class T> bool operator==(const std::optional<T>& lhs, const std::optional<T>& rhs)
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

template<class T> bool operator!=(const std::optional<T>& lhs, const std::optional<T>& rhs)
{
    return !(lhs == rhs);
}

template<class T> Point<FieldElement<T>> operator+(const Point<FieldElement<T>>& lhs, const Point<FieldElement<T>>& rhs)
{
    // Elements must be on the same curve
    if (lhs.A != rhs.A || lhs.B != rhs.B)
    {
        std::stringstream error;
        error << "Points " << lhs << ", " << rhs << " are not on the same curve";
        throw std::runtime_error(error.str());
    }

    // Handle infinity point
    if (!lhs.X)
        return rhs;
    if (!rhs.X)
        return lhs;

    // Handle vertical line
    if (lhs.X == rhs.X && lhs.Y != rhs.Y)
        return Point<FieldElement<T>>(std::nullopt, std::nullopt, lhs.A, lhs.B);

    // Handle X1 != X2
    if (lhs.X != rhs.X)
    {
        // TODO: Ensure Y values exist by overloading the subtraction operator
        auto slope = (rhs.Y.value() - lhs.Y.value()) / (rhs.X.value() - lhs.X.value());
        auto x3 = slope * slope - lhs.X.value() - rhs.X.value();
        auto y3 = slope * (lhs.X.value() - x3) - lhs.Y.value();
        return Point<FieldElement<T>>(x3, y3, lhs.A, lhs.B);
    }

    // Handle special case of vertical tangent line.
    // TODO: Book has this in Python as `if self == other and self.y == 0 * self.x:`
    if (lhs == rhs && lhs.Y.value().Number == 0)
        return Point<FieldElement<T>>(std::nullopt, std::nullopt, lhs.A, lhs.B);

    // Handle P1 = P2
    if (lhs == rhs)
    {
        // TODO: Ensure values exist
        auto slope = ((FieldElement<T>(3, lhs.A.Prime) * lhs.X.value() * lhs.X.value()) + lhs.A) /
                     (FieldElement<T>(2, lhs.A.Prime) * lhs.Y.value());
        auto x3 = (slope * slope) - (FieldElement<T>(2, lhs.A.Prime) * lhs.X.value());
        auto y3 = slope * (lhs.X.value() - x3) - lhs.Y.value();
        return Point<FieldElement<T>>(x3, y3, lhs.A, lhs.B);
    }

    // Handle this possible error condition
    std::stringstream error;
    error << "REACHED EDGE CASE: " << lhs << " + " << rhs;
    throw std::runtime_error(error.str());
}

template<class T> std::ostream& operator<<(std::ostream& os, const Point<FieldElement<T>>& point)
{
    if (!point.X)
        os << "Point(infinity)";
    else
    {
        os << "Point(" << point.X.value().Number << "," << point.Y.value().Number << ")_" << point.A.Number << "_"
           << point.B.Number << " FieldElement(" << point.X.value().Prime << ")";
    }

    return os;
}

template<class T> Point<T> operator*(const Point<T>& lhs, const int& coefficient)
{
    auto coef = coefficient;
    auto current = lhs;
    auto result = Point<T>(std::nullopt, std::nullopt, lhs.A, lhs.B);
    while (coef)
    {
        if (coef & 1)
        {
            result = result + current;
        }
        current = current + current;
        coef >>= 1;
    }

    return result;
}

template<class T> Point<T> operator*(const int& coefficient, const Point<T>& rhs)
{
    return rhs * coefficient;
}

} // namespace crypto
