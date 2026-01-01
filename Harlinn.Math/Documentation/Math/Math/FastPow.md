# FastPow

[Optimized basic math functions](Readme.md)/[Power and root finding functions](PowerFunctions.md)/`FastPow`

## Summary

`FastPow` computes `v` raised to the integer power `n` using exponentiation by squaring. It is a `constexpr` template that generates efficient code for compile-time and runtime use when `n` is a compile-time constant.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<int n, FloatingPointType T>
constexpr inline T FastPow( T v );
```

## Behavior

- Computes v^n where `n` is a signed integer template parameter.
- The implementation uses exponentiation by squaring for logarithmic multiplication count.
- If `n` is negative the result is computed as `1 / FastPow<-n>(v)` (i.e. reciprocal of the positive exponent result).
- For `n == 0` the function returns `Constants<T>::One`.
- The function is `constexpr` and suitable for compile-time evaluation when inputs are constexpr.

## Notes

- Because `n` is a template non-type parameter, the compiler can fully unroll and optimize the sequence of multiplications at compile time.
- This function is intended for integral exponents known at compile time. For variable exponents (runtime) use `std::pow` or a dedicated runtime power routine.
- For integer values of `v` and large exponents prefer careful overflow analysis; `FastPow` performs no overflow checks.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h"

int main()
{
    using Harlinn::Math::FastPow;

    double x = 1.5;
    // Compute 1.5^4 at compile time and use at runtime
    double r = FastPow<4>( x );
    std::cout << "1.5^4 = " << r << '\n'; // 5.0625

    // Negative exponent: 1.5^-2 = 1 / (1.5^2)
    double r2 = FastPow<-2>( x );
    std::cout << "1.5^-2 = " << r2 << '\n'; // ~0.444444

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double p4 = Harlinn::Math::FastPow<4>( 2.0 );
static_assert( p4 == 16.0 );

constexpr double pneg = Harlinn::Math::FastPow<-3>( 2.0 );
// 2^-3 == 1/8
static_assert( pneg == 0.125 );
```

## See also

- `Pow` — general floating-point power function for runtime exponents.
- `FastPow` complements `FastPow` for integer exponents; use `FastPow` when exponents are compile-time constants.

---

Created for the Harlinn.Math library documentation.
