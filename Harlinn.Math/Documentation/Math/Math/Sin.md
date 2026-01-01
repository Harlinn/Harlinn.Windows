# Sin

[Optimized basic math functions](Readme.md)/[Trigonometric functions](TrigonometricFunctions.md)/`Sin`

## Summary

`Sin` computes the sine of a floating-point value given in radians. The function is `constexpr`-friendly and delegates to the library's `OpenLibM` helpers for consistent behavior in both compile-time and runtime contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Sin( T x ) noexcept;
```

## Behavior

- Returns the sine of `x` (x in radians).
- For `float` the function delegates to `Math::Internal::OpenLibM::sinf`.
- For `double` the function uses `Math::Internal::OpenLibM::sin` in const-evaluation contexts and `std::sin` at runtime for performance when available.
- The implementation follows IEEE semantics for special values: `Sin(NaN)` is `NaN` and `Sin(-inf)` is `NaN` (or implementation-defined by the underlying math helpers).
- The function is `noexcept` and usable in `constexpr` contexts when the underlying helpers are constexpr-capable.

## Notes

- Input is in radians. Use `Deg2Rad` to convert degrees to radians when needed.
- Prefer `Sin` over direct calls to `std::sin` when you need consistent constexpr-capable behavior across compile-time and runtime.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Sin;

    double x = Harlinn::Math::Deg2Rad( 30.0 ); // 30 degrees -> pi/6
    std::cout << "Sin(pi/6) = " << Sin( x ) << '\n'; // 0.5

    float xf = Harlinn::Math::Deg2Rad( 90.0f );
    std::cout << "Sin(pi/2) = " << Sin( xf ) << '\n'; // 1.0

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s30 = Harlinn::Math::Sin( Harlinn::Math::Deg2Rad( 30.0 ) );
static_assert( s30 > 0.499999 && s30 < 0.500001 );

constexpr float s90 = Harlinn::Math::Sin( Harlinn::Math::Deg2Rad( 90.0f ) );
static_assert( s90 > 0.999999f && s90 < 1.000001f );
```

## See also

- `Cos`, `Tan`, `SinCos` � related trigonometric helpers.
- `Deg2Rad`, `Rad2Deg` � degree/radian conversion helpers.

---

Created for the Harlinn.Math library documentation.
