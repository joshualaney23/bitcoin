#include "Helpers.hpp"

namespace crypto
{

int PowerModulo(int a, int b, int modulus)
{
    int x = 1, y = a;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = x * y;
            x %= modulus;
        }

        y = y * y;
        y %= modulus;

        b /= 2;
    }

    return x;
}

} // namespace crypto
