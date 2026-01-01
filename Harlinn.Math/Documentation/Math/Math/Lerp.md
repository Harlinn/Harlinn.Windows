# Lerp

[Optimized basic math functions](Readme.md)/[Other functions](OtherFunctions.md)/`Lerp`

## Summary

`Lerp` computes the linear interpolation between two values `a` and `b` using parameter `t`. It returns `(1 - t) * a + t * b`. The function is generic and works for arithmetic types; it is `constexpr`-friendly.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<ArithmeticType T, ArithmeticType U>
constexpr inline auto Lerp( T a, T b, U t ) noexcept;

template<ArithmeticType T, ArithmeticType U>
constexpr inline auto Lerp2( U t, T a, T b ) noexcept;
```

## Behavior

- Returns the interpolated value `(1 - t) * a + t * b`.
- If `t` is in `[0, 1]` the result lies between `a` and `b`; for `t` outside that range the function performs linear extrapolation.
- The return type is a common arithmetic type deduced from the operands; mixed-type arguments are supported but may involve conversions.
- The function is `constexpr` when the underlying arithmetic operations are available at compile time.

## Notes

- Use `Lerp` for smooth transitions, animations, parameter blending, or for numerical interpolation between scalar values.
- For easing or non-linear interpolation combine `Lerp` with a remapping of `t` (ease functions) before calling.
- Be mindful of floating-point precision when `a` and `b` differ by many orders of magnitude; prefer double precision when needed.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Lerp;

    double a = 0.0;
    double b = 10.0;

    std::cout << "Lerp(a, b, 0.0) = " << Lerp( a, b, 0.0 ) << '\n'; // 0
    std::cout << "Lerp(a, b, 0.5) = " << Lerp( a, b, 0.5 ) << '\n'; // 5
    std::cout << "Lerp(a, b, 1.0) = " << Lerp( a, b, 1.0 ) << '\n'; // 10

    // Extrapolation
    std::cout << "Lerp(a, b, 1.5) = " << Lerp( a, b, 1.5 ) << '\n'; // 15

    // Mixed types
    float af = 1.0f;
    double bd = 3.0;
    double t = 0.25;
    std::cout << "Lerp(af, (float)bd, t) = " << Lerp( af, static_cast<float>( bd ), t ) << '\n';

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

constexpr double r1 = Harlinn::Math::Lerp( 0.0, 10.0, 0.5 );
static_assert( r1 == 5.0 );

constexpr auto r2 = Harlinn::Math::Lerp( 2, 8, 0.25 );
static_assert( r2 == 3.5 );
```

## See also

- `Lerp2`: alternate argument order for convenience.
- `Clamp`, `SmoothStep`: functions often used together with `Lerp`.

