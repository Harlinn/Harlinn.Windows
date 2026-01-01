# Remainder

[Optimized basic math functions](Readme.md)/[Basic operations](BasicOperations.md)/`Remainder`

## Summary

`Remainder` computes the IEEE-style remainder of the division operation `x / y` for floating-point arguments. It delegates to the library's `OpenLibM` helpers and is `constexpr`-friendly when those helpers are available in constant-evaluation contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Remainder( T x, T y ) noexcept;
```

## Behavior

- Returns the IEEE remainder r = x - n*y where n is the nearest integer to the exact value x / y. If |n - x/y| = 0.5 the even integer is chosen for n.
- The result lies in the interval [-|y|/2, |y|/2].
- For `float` the implementation delegates to `Math::Internal::OpenLibM::remainderf`; for `double` it delegates to `Math::Internal::OpenLibM::remainder`.
- The function is `noexcept` and follows the underlying `OpenLibM` semantics for special values (NaN, infinities, signed zeros).

## Notes

- `Remainder` differs from `fmod`/`FMod`: `fmod` returns a value with the sign of `x` and magnitude less than |y|, while `Remainder` returns a symmetric remainder around zero using the nearest-integer quotient rule.
- Use `Remainder` when an IEEE-style remainder (round-to-nearest quotient) is required, for example in certain numerical algorithms and periodic reductions.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Remainder;

    double x = 5.3;
    double y = 2.0;

    // IEEE remainder: nearest integer to 5.3/2.0 is 3 -> remainder = 5.3 - 3*2.0 = -0.7
    std::cout << "Remainder(5.3, 2.0) = " << Remainder( x, y ) << '\n';

    // Compare with fmod (or Mod) which uses truncation toward zero: fmod(5.3,2.0) = 1.3
    std::cout << "Mod(5.3, 2.0) = " << Harlinn::Math::Mod( x, y ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double r = Harlinn::Math::Remainder( 5.3, 2.0 );
static_assert( r < 0 );
```

## See also

- `FMod`, `Mod` � floating-point remainder using truncation toward zero.
- `RemQuo` � remainder with additional quotient bits information.

---

Created for the Harlinn.Math library documentation.
