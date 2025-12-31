# Mod

## Summary

`Mod` computes the floating-point remainder of the division `a / b` using the truncation-toward-zero quotient rule (same semantics as `fmod`). In the `Harlinn.Math` library `Mod` is implemented as a thin wrapper around `FMod` and is `constexpr`-friendly when the underlying helpers are available.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Mod( T a, T b );
```

## Behavior

- Returns the remainder r = a - n*b where n is the integer obtained by truncating the exact quotient toward zero (this matches the C `fmod` behavior).
- The sign of the result matches the sign of the dividend `a` (or is +0 when the remainder is zero).
- For `float` values the implementation delegates to `Math::Internal::OpenLibM::fmodf`; for `double` it delegates to `Math::Internal::OpenLibM::fmod` (via `FMod`).
- The function can be evaluated in `consteval` contexts when the underlying OpenLibM helpers support constant evaluation; otherwise it behaves like the standard library `fmod` at runtime.
- Special values (NaN, infinities, signed zeros) follow the underlying implementation semantics.

## Notes

- `Mod` differs from `Remainder`/`remquo` which use the IEEE round-to-nearest-quota rule and return a symmetric remainder in the interval [-|y|/2, |y|/2]. Use `Mod`/`fmod` when you specifically need truncation toward zero semantics.
- To compute a mathematically positive modulus for potentially negative dividends, use `Mod(a, b)` and if the result is negative add `b` (or use a helper that normalizes the result).

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Mod;

    double a = 5.3;
    double b = 2.0;

    // truncation toward zero: quotient = trunc(5.3/2.0) = 2 -> remainder = 5.3 - 2*2.0 = 1.3
    std::cout << "Mod(5.3, 2.0) = " << Mod( a, b ) << '\n'; // 1.3

    double aneg = -5.3;
    // quotient = trunc(-5.3/2.0) = -2 -> remainder = -5.3 - (-2)*2.0 = -1.3
    std::cout << "Mod(-5.3, 2.0) = " << Mod( aneg, b ) << '\n'; // -1.3

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double r1 = Harlinn::Math::Mod( 5.3, 2.0 );
static_assert( r1 > 1.2999999999999998 && r1 < 1.3000000000000002 );

constexpr double r2 = Harlinn::Math::Mod( -5.3, 2.0 );
static_assert( r2 < 0 );
```

## See also

- `FMod` — underlying implementation that `Mod` forwards to.
- `Remainder`, `RemQuo` — IEEE-style remainder functions using round-to-nearest quotient.

---

Created for the Harlinn.Math library documentation.
