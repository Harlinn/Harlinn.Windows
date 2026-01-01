# Sqr

[Optimized basic math functions](Readme.md)/[Power and root finding functions](PowerFunctions.md)/`Sqr`

## Summary

`Sqr` returns the square of its argument (`v * v`). The function is defined for arithmetic types and complex floating-point types and is `constexpr` so it can be used in compile-time expressions.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<typename T>
    requires IsArithmetic<T> || Internal::IsComplex<T>
constexpr inline T Sqr( T v );
```

## Behavior

- Computes and returns `v * v` using the semantics of `T`.
- For built-in arithmetic types this is ordinary multiplication.
- For complex types (currently `std::complex<float>` and `std::complex<double>`) the multiplication uses complex multiplication and returns a complex result.
- The function is `constexpr` and has no side effects.

## Notes

- `Sqr` is a small convenience helper intended to improve readability where squaring is needed frequently.
- For performance-critical hot paths, compilers typically inline this simple operation, so there is no overhead.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Sqr;

    double x = 3.0;
    std::cout << "Sqr(3.0) = " << Sqr(x) << '\n'; // 9.0

    int i = -4;
    std::cout << "Sqr(-4) = " << Sqr(i) << '\n'; // 16

    std::complex<double> c{1.0, 2.0};
    auto cs = Sqr(c); // complex multiplication
    std::cout << "Sqr(1+2i) = (" << cs.real() << ", " << cs.imag() << ")" << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double d = Harlinn::Math::Sqr( 1.5 );
static_assert( d == 2.25 );

constexpr int ii = Harlinn::Math::Sqr( 5 );
static_assert( ii == 25 );
```

## See also

- `Sqr` complements helpers such as `Sqrt`, `SafeSqrt`, and `Sqr`-related interval operations.


