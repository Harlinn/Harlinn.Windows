# Cos

## Summary

`Cos` computes the cosine of a floating-point value given in radians. The function is `constexpr`-friendly and delegates to the library's `OpenLibM` helpers for consistent behavior in both compile-time and runtime contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Cos( T x ) noexcept;
```

## Behavior

- Returns the cosine of `x` (x in radians).
- For `float` the function delegates to `Math::Internal::OpenLibM::cosf`.
- For `double` the implementation uses `Math::Internal::OpenLibM::cos` in const-evaluation contexts and `std::cos` at runtime for performance when available.
- The implementation follows IEEE semantics for special values: `Cos(NaN)` is `NaN` and `Cos(±inf)` is `NaN` (or implementation-defined by the underlying math helpers).
- The function is `noexcept` and usable in `constexpr` contexts when the underlying helpers are constexpr-capable.

## Notes

- Input is in radians. Use `Deg2Rad` to convert degrees to radians when needed.
- Prefer `Cos` over direct calls to `std::cos` when you need consistent constexpr-capable behavior across compile-time and runtime.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Cos;
    using Harlinn::Math::Deg2Rad;

    double x = Deg2Rad( 60.0 ); // 60 degrees -> pi/3
    std::cout << "Cos(pi/3) = " << Cos( x ) << '\n'; // ~0.5

    float xf = Deg2Rad( 0.0f );
    std::cout << "Cos(0) = " << Cos( xf ) << '\n'; // 1.0

    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "Cos(NaN) is NaN: " << std::isnan( Cos( qnan ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double c60 = Harlinn::Math::Cos( Harlinn::Math::Deg2Rad( 60.0 ) );
static_assert( c60 > 0.499999 && c60 < 0.500001 );

constexpr float c0 = Harlinn::Math::Cos( 0.0f );
static_assert( c0 == 1.0f );
```

## See also

- `Sin`, `Tan`, `CosH` — related trigonometric helpers.
- `Deg2Rad`, `Rad2Deg` — degree/radian conversion helpers.

---

Created for the Harlinn.Math library documentation.
