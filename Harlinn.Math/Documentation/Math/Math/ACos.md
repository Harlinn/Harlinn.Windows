# ACos

[Optimized basic math functions](Readme.md)/[Trigonometric functions](TrigonometricFunctions.md)/`ACos`

## Summary

`ACos` computes the principal value of the arc cosine (inverse cosine) of a floating-point value and is `constexpr`-friendly via the library's internal helpers. For inputs in the domain [-1, 1] it returns a value in radians in the range [0, pi].

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T ACos( T x ) noexcept;
```

## Behavior

- Returns the principal value of the arc cosine of `x` in radians.
- Inputs outside the domain [-1, 1] produce `NaN` per IEEE semantics.
- The implementation delegates to `Math::Internal::OpenLibM::FastACos` which provides constexpr-capable behavior and consistent results across platforms.
- Special values follow the underlying helpers' semantics: `ACos(NaN) = NaN` and `ACos(x)` for |x| > 1 returns `NaN`.
- The function is `noexcept` and can be used in constant-evaluation contexts when the underlying helpers are constexpr-capable.

## Notes

- The result is in radians. Use `Rad2Deg` to convert to degrees when needed.
- Use `SafeACos` to clamp inputs into the valid range when you want to avoid `NaN` for slightly out-of-range inputs due to rounding.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ACos;
    using Harlinn::Math::Rad2Deg;

    double v1 = 1.0;    // acos(1) = 0
    double v2 = 0.5;    // acos(0.5) = pi/3
    double v3 = -1.0;   // acos(-1) = pi
    double v4 = 2.0;    // out of domain -> NaN

    std::cout << "ACos(1.0) = " << ACos( v1 ) << " (degrees: " << Rad2Deg( ACos( v1 ) ) << ")\n";
    std::cout << "ACos(0.5) = " << ACos( v2 ) << " (degrees: " << Rad2Deg( ACos( v2 ) ) << ")\n";
    std::cout << "ACos(-1.0) = " << ACos( v3 ) << " (pi = " << Harlinn::Math::Constants<double>::Pi << ")\n";
    std::cout << "ACos(2.0) is NaN: " << std::isnan( ACos( v4 ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double c0 = Harlinn::Math::ACos( 1.0 );
static_assert( c0 == 0.0 );

constexpr double c60 = Harlinn::Math::ACos( 0.5 );
static_assert( c60 > Harlinn::Math::Constants<double>::Pi / 3 - 1e-12 && c60 < Harlinn::Math::Constants<double>::Pi / 3 + 1e-12 );
```

## See also

- `Sin`, `Cos`, `ASin` � related trigonometric helpers.
- `SafeACos`, `SafeASin` � clamped inverse trig helpers.
- `Deg2Rad`, `Rad2Deg` � conversion helpers between degrees and radians.

---

Created for the Harlinn.Math library documentation.
