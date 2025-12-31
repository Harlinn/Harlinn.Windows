# Erf

## Summary

`Erf` computes the error function of a floating-point value. The implementation delegates to the library's `OpenLibM` helpers and is `constexpr`-friendly when those helpers are available in constant-evaluation contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Erf( T x ) noexcept;
```

## Behavior

- Returns the value of the error function, erf(x), which is 2/sqrt(pi) * integral from 0 to x of e^{-t^2} dt.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::erff`; for `double` it delegates to `Math::Internal::OpenLibM::erf`.
- The function is `noexcept` and can be used in `constexpr` contexts when the underlying helpers are constexpr-capable.
- Special values follow the underlying library semantics: `Erf(NaN) = NaN`, `Erf(+inf) = 1`, `Erf(-inf) = -1`.

## Notes

- `Erf` is commonly used in probability, statistics (normal distribution CDF relations), and solutions to diffusion-type differential equations.
- The complementary error function `ErfC` is provided for 1 - erf(x) with higher accuracy for large x.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Erf;

    double a = 0.0;
    double b = 0.5;
    double c = 1.0;

    std::cout << "Erf(0) = " << Erf( a ) << '\n';      // 0
    std::cout << "Erf(0.5) = " << Erf( b ) << '\n';    // ~0.5204998778130465
    std::cout << "Erf(1) = " << Erf( c ) << '\n';      // ~0.8427007929497149

    double inf = std::numeric_limits<double>::infinity();
    std::cout << "Erf(inf) = " << Erf( inf ) << '\n';  // 1
    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double e0 = Harlinn::Math::Erf( 0.0 );
static_assert( e0 == 0.0 );

constexpr double e1 = Harlinn::Math::Erf( 1.0 );
// erf(1) ~ 0.8427007929497149
static_assert( e1 > 0.8427007929497148 && e1 < 0.8427007929497150 );
```

## See also

- `ErfC` — complementary error function.
- `Gaussian`, `GaussianIntegral` — helpers for normal distribution related computations.

---

Created for the Harlinn.Math library documentation.
