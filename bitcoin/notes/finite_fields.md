Any point has infinite lines that pass through it, but 2 points have exactly 1 line that pass through them.

Remove substraction properties by including the additive inverse: a - b = a + -b
Remove divisional properties by including the multiplicative inverse: a / b = a * b^-1

We only care about how the numbers are related to each other with multiplication and addition, not their value. Therefore we can use irreducible polynomials.

Only use positive integers module N, where N must be prime.
Z101 = {0,1,2,...,100}
a + b := a + b % 101
a * b := a * b % 101
-a    := 101 - a
a^-1  := a^99 % 101

# Fermat's Little Theorem
n^(p-1) % p = 1, where p is prime