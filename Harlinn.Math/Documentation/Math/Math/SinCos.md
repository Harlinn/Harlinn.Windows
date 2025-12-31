# SinCos

## Summary

`SinCos` computes sine and cosine of an angle `x` (in radians) simultaneously and stores the results in the provided outputs. Computing both together can be more efficient and produce slightly better consistent results compared to calling `Sin` and `Cos` separately.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
template<FloatingPointType T>
inline constexpr void SinCos( T x, T& sinResult, T& cosResult ) noexcept;

template<FloatingPointType T>
inline constexpr void SinCos( T x, T* sinResult, T* cosResult ) noexcept;
```

## Behavior

- Computes both `sin(x)` and `cos(x)` where `x` is given in radians.
- For `float` delegates to `Math::Internal::OpenLibM::sincosf`; for `double` delegates to `Math::Internal::OpenLibM::sincos`.
- `constexpr`-friendly: the implementation can be used in constant evaluation when the underlying helpers are constexpr-capable.
- The function is `noexcept` and follows IEEE semantics for special values (NaN/infinities) according to the underlying math helpers.

## Notes

- Use `SinCos` when you need both sine and cosine for the same argument to improve performance and numerical consistency.
- Inputs are radians. Use `Deg2Rad` to convert degrees to radians if needed.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SinCos;
    using Harlinn::Math::Deg2Rad;

    double angle = Deg2Rad( 45.0 ); // pi/4
    double s, c;
    SinCos( angle, s, c );
    std::cout << "Sin(45deg) = " << s << "  Cos(45deg) = " << c << '\n'; // ~0.7071, ~0.7071

    float af = Deg2Rad( 60.0f );
    float sf, cf;
    SinCos( af, &sf, &cf );
    std::cout << "Sin(60deg) = " << sf << "  Cos(60deg) = " << cf << '\n'; // ~0.866025, ~0.5

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s0 = [](){ double s,c; Harlinn::Math::SinCos( Harlinn::Math::Deg2Rad( 30.0 ), s, c ); return s; }();
static_assert( s0 > 0.499999 && s0 < 0.500001 ); // ~0.5

constexpr double c0 = [](){ double s,c; Harlinn::Math::SinCos( Harlinn::Math::Deg2Rad( 60.0 ), s, c ); return c; }();
static_assert( c0 > 0.499999 && c0 < 0.500001 ); // ~0.5
```

## See also

- `Sin`, `Cos`, `Tan` — individual trigonometric functions.
- `Deg2Rad`, `Rad2Deg` — conversion helpers between degrees and radians.

---

Created for the Harlinn.Math library documentation.
