# ASinH

[Optimized basic math functions](Readme.md)/[Hyperbolic functions](HyperbolicFunctions.md)/`ASinH`

## Summary

`ASinH` computes the inverse hyperbolic sine (asinh) of a floating-point value. The function is `constexpr`-friendly in constant-evaluation contexts and delegates to the library's `OpenLibM` helpers for consistent results across platforms.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T ASinH( T x ) noexcept;
```

## Behavior

- Returns the inverse hyperbolic sine of `x`, i.e. `asinh(x)`, the value `y` such that `sinh(y) = x`.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::asinhf`.
- For `double` the implementation uses the `OpenLibM` helpers in const-evaluation contexts and `std::asinh` at runtime when appropriate.
- Special values follow the underlying helpers' semantics: `ASinH(NaN) = NaN`, and infinities map to infinities with matching sign.
- The function is `noexcept` and can be used in constant-evaluation contexts when the underlying helpers are constexpr-capable.

## Notes

- `ASinH` returns values in the same unit (radians) implied by hyperbolic functions � hyperbolic functions are dimensionless; conversion to other units is not applicable.
- For small `x`, `asinh(x)` is approximately `x` (since `sinh(y) ~ y` for small `y`).

## Examples

Runtime example:

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ASinH;

    double v1 = 0.0;   // asinh(0) == 0
    double v2 = 1.0;   // asinh(1)
    double v3 = -2.0;  // asinh(-2)

    std::cout << "ASinH(0) = " << ASinH( v1 ) << '\n';
    std::cout << "ASinH(1) = " << ASinH( v2 ) << '\n';
    std::cout << "ASinH(-2) = " << ASinH( v3 ) << '\n';

    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "ASinH(NaN) is NaN: " << std::isnan( ASinH( qnan ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a0 = Harlinn::Math::ASinH( 0.0 );
static_assert( a0 == 0.0 );

constexpr double a1 = Harlinn::Math::ASinH( 1.0 );
// asinh(1) ~ 0.881373587019543
static_assert( a1 > 0.881373587019 && a1 < 0.881373587020 );
```

## See also

- `SinH`, `CosH`, `TanH` � hyperbolic functions.
- `Exp`, `Log` � helpers that can be used to implement or reason about hyperbolic functions.

---

Created for the Harlinn.Math library documentation.
