# FMod

## Summary

`FMod` computes the floating-point remainder of the division `x / y`, matching the semantics of the C `fmod` family: the result has the sign of `x` and magnitude less than `|y|`. Overloads are provided as a template for floating-point types and the implementation is `constexpr`-friendly.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T FMod( T x, T y ) noexcept;
```

## Behavior

- Returns the remainder r of the division `x / y` such that `x = n*y + r` for some integer `n` and `|r| < |y|`.
- The sign of the result `r` follows the sign of `x` (truncation toward zero behavior for the quotient).
- For special values:
  - If `x` is NaN or `y` is NaN the result is NaN.
  - If `y` is zero the behavior follows the underlying platform/library (typically NaN or domain error); the implementation delegates to `Internal::OpenLibM::fmod`/`fmodf` and preserves `constexpr` evaluation when possible.
  - Infinities are handled according to the C standard semantics: `fmod(inf, y)` is NaN, while `fmod(x, inf)` returns `x`.
- The function is `constexpr` and at runtime uses either the library's `OpenLibM` functions or the standard `std::fmod` as available.

## Notes

- Use `FMod` when you need the IEEE/C `fmod`-style remainder (sign matches the dividend) rather than `remainder` (which rounds quotient to nearest integer and may differ in tie cases).
- For integer-like modulus with positive divisors consider using `std::fmod` on floating arguments or convert to integer arithmetic when appropriate.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::FMod;

    double x1 = 5.5, y1 = 2.0;
    std::cout << "FMod(5.5, 2.0) = " << FMod( x1, y1 ) << '\n'; // 1.5

    double x2 = -5.5, y2 = 2.0;
    std::cout << "FMod(-5.5, 2.0) = " << FMod( x2, y2 ) << '\n'; // -1.5 (sign follows x)

    double x3 = 5.5, y3 = -2.0;
    std::cout << "FMod(5.5, -2.0) = " << FMod( x3, y3 ) << '\n'; // 1.5 (magnitude < |y|)

    // Propagation of NaN
    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "FMod(NaN, 1.0) is NaN: " << std::isnan( FMod( qnan, 1.0 ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double r1 = Harlinn::Math::FMod( 5.5, 2.0 );
static_assert( r1 == 1.5 );

constexpr double r2 = Harlinn::Math::FMod( -5.5, 2.0 );
static_assert( r2 == -1.5 );
```

## See also

- `Remainder` — computes the IEEE `remainder` (rounds quotient to nearest integer) and returns possibly different signed results for tie cases.
- `Mod` — an alias for `FMod` in this library.

---

Created for the Harlinn.Math library documentation.
