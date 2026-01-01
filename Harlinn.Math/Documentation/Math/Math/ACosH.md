# ACosH

[Optimized basic math functions](Readme.md)/[Hyperbolic functions](HyperbolicFunctions.md)/`ACosH`

## Summary

`ACosH` computes the inverse hyperbolic cosine (`acosh`) of a floating-point value. The function is `constexpr`-friendly in constant-evaluation contexts and delegates to the library's `OpenLibM` helpers for consistent behavior across platforms.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T ACosH( T x ) noexcept;
```

## Behavior

- Returns the inverse hyperbolic cosine of `x`, i.e. `acosh(x)`, the value `y >= 0` such that `cosh(y) = x` for `x >= 1`.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::acoshf`.
- For `double` the implementation uses the `OpenLibM` helpers in const-evaluation contexts and `std::acosh` at runtime when appropriate.
- Inputs less than 1 produce `NaN` per IEEE semantics. `ACosH(NaN) = NaN`, and `ACosH(+inf) = +inf`.
- The function is `noexcept` and can be used in constant evaluation when the underlying helpers are constexpr-capable.

## Notes

- Hyperbolic functions are dimensionless. Use `CosH` to convert back to hyperbolic cosine when needed.
- For values close to 1 numerical cancellation can occur; use library helpers (or higher precision) when extreme robustness is required.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ACosH;

    double v1 = 1.0;   // acosh(1) == 0
    double v2 = 2.0;   // acosh(2) ~ 1.316957
    double v3 = 10.0;  // larger argument

    std::cout << "ACosH(1.0) = " << ACosH( v1 ) << '\n';
    std::cout << "ACosH(2.0) = " << ACosH( v2 ) << '\n';
    std::cout << "ACosH(10.0) = " << ACosH( v3 ) << '\n';

    double nanIn = std::numeric_limits<double>::quiet_NaN();
    std::cout << "ACosH(NaN) is NaN: " << std::isnan( ACosH( nanIn ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a0 = Harlinn::Math::ACosH( 1.0 );
static_assert( a0 == 0.0 );

constexpr double a2 = Harlinn::Math::ACosH( 2.0 );
// acosh(2) = ln(2 + sqrt(3)) ~ 1.316957897
static_assert( a2 > 1.316957897 - 1e-12 && a2 < 1.316957897 + 1e-12 );
```

## See also

- `SinH`, `CosH`, `TanH` � related hyperbolic functions.
- `ASinH`, `ATanH` � other inverse hyperbolic functions.
- `Exp`, `Log` � helpers for exponential and logarithmic computations.

---

Created for the Harlinn.Math library documentation.
