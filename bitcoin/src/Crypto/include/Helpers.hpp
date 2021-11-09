#pragma once

namespace crypto
{

// Calculates (a^b) % modulus
template<class T> T PowerModulo(T a, T b, T modulus)
{
    if (b == 0)
        return 1;

    auto p = PowerModulo(a, b / 2, modulus);
    p = (p * p) % modulus;

    return (b % 2 == 0) ? p : (a * p) % modulus;
}

} // namespace crypto
