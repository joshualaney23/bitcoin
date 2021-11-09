#include "Point.hpp"

#include "FieldElement.hpp"

namespace crypto
{

// Specializations for FieldElement
template<> Point<FieldElement> operator+(const Point<FieldElement>& lhs, const Point<FieldElement>& rhs)
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
        return Point<FieldElement>(std::nullopt, std::nullopt, lhs.A, lhs.B);

    // Handle X1 != X2
    if (lhs.X != rhs.X)
    {
        // TODO: Ensure Y values exist by overloading the subtraction operator
        auto slope = (rhs.Y.value() - lhs.Y.value()) / (rhs.X.value() - lhs.X.value());
        auto x3 = slope * slope - lhs.X.value() - rhs.X.value();
        auto y3 = slope * (lhs.X.value() - x3) - lhs.Y.value();
        return Point<FieldElement>(x3, y3, lhs.A, lhs.B);
    }

    // Handle special case of vertical tangent line.
    // TODO: Book has this in Python as `if self == other and self.y == 0 * self.x:`
    if (lhs == rhs && lhs.Y.value().Number == 0)
        return Point<FieldElement>(std::nullopt, std::nullopt, lhs.A, lhs.B);

    // Handle P1 = P2
    if (lhs == rhs)
    {
        // TODO: Ensure values exist
        auto slope = ((FieldElement(3, lhs.A.Prime) * lhs.X.value() * lhs.X.value()) + lhs.A) /
                     (FieldElement(2, lhs.A.Prime) * lhs.Y.value());
        auto x3 = (slope * slope) - (FieldElement(2, lhs.A.Prime) * lhs.X.value());
        auto y3 = slope * (lhs.X.value() - x3) - lhs.Y.value();
        return Point<FieldElement>(x3, y3, lhs.A, lhs.B);
    }

    // Handle this possible error condition
    std::stringstream error;
    error << "REACHED EDGE CASE: " << lhs << " + " << rhs;
    throw std::runtime_error(error.str());
}

template<> std::ostream& operator<<(std::ostream& os, const Point<FieldElement>& point)
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

} // namespace crypto
