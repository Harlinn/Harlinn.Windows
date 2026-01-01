# Tan

[Optimized basic math functions](Readme.md)/[Trigonometric functions](TrigonometricFunctions.md)/`Tan`

## Summary

`Tan` computes the tangent of a floating-point value given in radians. The function is `constexpr`-friendly and delegates to the library's `OpenLibM` helpers for consistent behavior in both compile-time and runtime contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Tan( T x ) noexcept;
```

## Behavior

- Returns the tangent of `x` (x in radians), i.e. `sin(x)/cos(x)` computed with appropriate numerical care.
- For `float` the function delegates to `Math::Internal::OpenLibM::tanf`.
- For `double` the implementation uses `Math::Internal::OpenLibM::tan` in const-evaluation contexts and `std::tan` at runtime when available.
- The implementation follows IEEE semantics for special values: `Tan(NaN)` is `NaN` and `Tan(�inf)` is `NaN` (or implementation-defined by the underlying math helpers).
- The function is `noexcept` and usable in `constexpr` contexts when the underlying helpers are constexpr-capable.

## Notes

- Input is in radians. Use `Deg2Rad` to convert degrees to radians when needed.
- Be careful near points where `cos(x) == 0` (odd multiples of `pi/2`), where the tangent is undefined and may produce very large values or `NaN`/infinity depending on direction.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Tan;
    using Harlinn::Math::Deg2Rad;

    double v1 = Deg2Rad( 45.0 ); // 45 degrees -> pi/4
    double v2 = Deg2Rad( 0.0 );  // 0 degrees
    double v3 = Deg2Rad( 90.0 ); // 90 degrees -> pi/2 (cos=0)

    std::cout << "Tan(45deg) = " << Tan( v1 ) << '\n'; // ~1
    std::cout << "Tan(0) = " << Tan( v2 ) << '\n';     // 0
    std::cout << "Tan(90deg) is finite: " << std::isfinite( Tan( v3 ) ) << '\n';

    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "Tan(NaN) is NaN: " << std::isnan( Tan( qnan ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double t45 = Harlinn::Math::Tan( Harlinn::Math::Deg2Rad( 45.0 ) );
static_assert( t45 > 0.999999 && t45 < 1.000001 );

constexpr float t0 = Harlinn::Math::Tan( 0.0f );
static_assert( t0 == 0.0f );
```

## See also

- `Sin`, `Cos` � related trigonometric helpers.
- `TanH`, `ATan` � hyperbolic and inverse tangent helpers.
- `Deg2Rad`, `Rad2Deg` � conversion helpers between degrees and radians.

---

Created for the Harlinn.Math library documentation.
