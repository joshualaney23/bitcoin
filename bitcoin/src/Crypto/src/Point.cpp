#include "Point.hpp"

#include "FieldElement.hpp"

namespace crypto
{

// Specialization for FieldElement
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
