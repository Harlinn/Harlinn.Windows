# TGamma

[Optimized basic math functions](Readme.md)/[Error and gamma functions](ErrorAndGammaFunctions.md)/`TGamma`

## Summary

`TGamma` computes the Gamma function ?(x) for a floating-point argument `x`. The implementation delegates to the library's `OpenLibM` helpers and is `constexpr`-friendly when those helpers are available in constant-evaluation contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T TGamma( T x ) noexcept;
```

## Behavior

- Returns the value of the Gamma function ?(x) for real-valued `x` (extends factorial to non-integer values: ?(n) = (n-1)! for positive integers `n`).
- For `float` the implementation delegates to `Math::Internal::OpenLibM::tgammaf`; for `double` it delegates to `Math::Internal::OpenLibM::tgamma` (the current header casts the result for the templated type).
- The function is `noexcept` and can be used in constant-evaluation contexts when the underlying helpers are constexpr-capable.
- Special values follow the underlying library semantics: poles at non-positive integers yield �infinity or domain errors per the implementation; NaN inputs propagate NaN; sign and magnitude follow standard Gamma behaviour.

## Notes

- Use `LGamma` to compute the natural logarithm of |?(x)| with better numerical behavior for large arguments.
- `TGamma` grows rapidly for increasing positive arguments and changes sign across poles at non-positive integers.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::TGamma;

    double a = 1.0; // ?(1) = 1
    double b = 4.0; // ?(4) = 3! = 6
    double c = 0.5; // ?(1/2) = sqrt(pi)

    std::cout << "TGamma(1) = " << TGamma( a ) << '\n'; // 1
    std::cout << "TGamma(4) = " << TGamma( b ) << '\n'; // 6
    std::cout << "TGamma(0.5) = " << TGamma( c ) << '\n'; // ~1.7724538509

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double g1 = Harlinn::Math::TGamma( 1.0 );
static_assert( g1 == 1.0 );

constexpr double g4 = Harlinn::Math::TGamma( 4.0 );
static_assert( g4 == 6.0 );

constexpr double ghalf = Harlinn::Math::TGamma( 0.5 );
// ?(1/2) = sqrt(pi) ~ 1.7724538509055160
static_assert( ghalf > 1.7724538509055159 && ghalf < 1.7724538509055161 );
```

## See also

- `LGamma` � natural logarithm of the absolute value of the Gamma function.
- `Erf`, `ErfC` � error functions used in probability and special function computations.

---

Created for the Harlinn.Math library documentation.
