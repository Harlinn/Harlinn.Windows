# ASin

## Summary

`ASin` computes the principal value of the arc sine (inverse sine) of a floating-point value and is `constexpr`-friendly via the library's internal helpers. For inputs in the domain [-1, 1] it returns a value in radians in the range [-pi/2, pi/2].

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T ASin( T x ) noexcept;
```

## Behavior

- Returns the principal value of the arc sine of `x` in radians.
- Inputs outside the domain [-1, 1] produce NaN per IEEE semantics.
- The implementation delegates to `Math::Internal::OpenLibM::FastASin` which provides constexpr-capable behavior and consistent results across platforms.
- Special values follow the underlying helpers semantics: `ASin(NaN) = NaN` and `ASin(x)` for |x| > 1 returns NaN.
- The function is `noexcept` and can be used in constant-evaluation contexts when the underlying helpers are constexpr-capable.

## Notes

- Input is expected in the range [-1, 1]. Use `Clamp` or `SafeASin` when you want to guard inputs to the valid domain.
- The result is in radians. Convert to degrees with `Rad2Deg` if needed.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ASin;
    using Harlinn::Math::Deg2Rad;
    using Harlinn::Math::Rad2Deg;

    double v1 = 0.5; // sin(30deg)
    double v2 = 1.0;
    double v3 = 2.0; // out of domain

    std::cout << "ASin(0.5) (radians) = " << ASin( v1 ) << '\n';
    std::cout << "ASin(0.5) (degrees) = " << Rad2Deg( ASin( v1 ) ) << '\n';
    std::cout << "ASin(1.0) = " << ASin( v2 ) << " (pi/2 = " << Harlinn::Math::Constants<double>::PiOver2 << ")\n";
    std::cout << "ASin(2.0) is NaN: " << std::isnan( ASin( v3 ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s30 = Harlinn::Math::ASin( 0.5 );
static_assert( s30 > 0.523599 && s30 < 0.523601 ); // ~pi/6

// Guarded usage via SafeASin
constexpr double guarded = Harlinn::Math::SafeASin( 2.0 ); // clamps and returns a valid value or calls ASin after clamp
```

## See also

- `Sin`, `Cos`, `Tan` — trigonometric functions.
- `SafeASin` — clamps input into [-1, 1] before calling `ASin`.
- `Deg2Rad`, `Rad2Deg` — conversion helpers between degrees and radians.

---

Created for the Harlinn.Math library documentation.
