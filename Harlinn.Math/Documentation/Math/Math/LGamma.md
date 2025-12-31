# LGamma

## Summary

`LGamma` computes the natural logarithm of the absolute value of the Gamma function for a floating-point argument `x`. The implementation delegates to the library's `OpenLibM` helpers and is `constexpr`-friendly when those helpers are available in constant-evaluation contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T LGamma( T x ) noexcept;
```

## Behavior

- Returns the value of ln(|?(x)|) for real-valued `x`.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::lgammaf`; for `double` it delegates to `Math::Internal::OpenLibM::lgamma`.
- The function is `noexcept` and can be used in constant-evaluation contexts when the underlying helpers are constexpr-capable.
- Poles at non-positive integers are handled per the underlying implementation; NaN inputs propagate NaN and infinities are treated according to OpenLibM semantics.
- Use `TGamma` when you need ?(x) itself; use `LGamma` for better numerical stability when x is large.

## Notes

- `LGamma` is commonly used in statistics and probability (e.g., log of factorial-like terms) and in special-function computations requiring log-domain values to avoid overflow.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::LGamma;

    double a = 1.0; // ?(1) = 1 -> ln|?(1)| = 0
    double b = 4.0; // ?(4) = 6 -> ln|?(4)| = ln(6)
    double c = 0.5; // ?(1/2) = sqrt(pi) -> ln|?(1/2)| = 0.5 * ln(pi)

    std::cout << "LGamma(1) = " << LGamma( a ) << '\n'; // 0
    std::cout << "LGamma(4) = " << LGamma( b ) << " (ln(6) ~ " << std::log(6.0) << ")\n";
    std::cout << "LGamma(0.5) = " << LGamma( c ) << '\n'; // ~0.57236494

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double lg1 = Harlinn::Math::LGamma( 1.0 );
static_assert( lg1 == 0.0 );

constexpr double lg4 = Harlinn::Math::LGamma( 4.0 );
// ln(6) ~ 1.791759469228055
static_assert( lg4 > 1.7917594692280549 && lg4 < 1.7917594692280551 );

constexpr double lgHalf = Harlinn::Math::LGamma( 0.5 );
// ln(|?(1/2)|) = 0.5 * ln(pi) ~ 0.5723649429247001
static_assert( lgHalf > 0.5723649429247000 && lgHalf < 0.5723649429247002 );
```

## See also

- `TGamma` — Gamma function ?(x).
- `Erf`, `ErfC` — related special functions used in probability and statistics.

---

Created for the Harlinn.Math library documentation.
