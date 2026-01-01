# ATanH

[Optimized basic math functions](Readme.md)/[Hyperbolic functions](HyperbolicFunctions.md)/`ATanH`

## Summary

`ATanH` computes the inverse hyperbolic tangent (`atanh`) of a floating-point value. The function is `constexpr`-friendly in constant-evaluation contexts and delegates to the library's `OpenLibM` helpers for consistent behavior across platforms.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T ATanH( T x ) noexcept;
```

## Behavior

- Returns the inverse hyperbolic tangent of `x`, i.e. `atanh(x)`, the value `y` such that `tanh(y) = x` for |x| < 1.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::atanhf`.
- For `double` the implementation uses the `OpenLibM` helpers in const-evaluation contexts and `std::atanh` at runtime when appropriate.
- Inputs with |x| >= 1 produce `NaN` for finite values (except signed infinities which follow underlying library semantics). NaN inputs propagate NaN.
- The function is `noexcept` and can be used in constant-evaluation contexts when the underlying helpers are constexpr-capable.

## Notes

- `ATanH` is dimensionless and defined only for |x| < 1 in the real domain.
- For values near zero, `ATanH(x) ? x`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ATanH;

    double a = 0.0;   // atanh(0) == 0
    double b = 0.5;   // atanh(0.5)
    double c = -0.8;  // atanh(-0.8)

    std::cout << "ATanH(0) = " << ATanH( a ) << '\n';
    std::cout << "ATanH(0.5) = " << ATanH( b ) << '\n';
    std::cout << "ATanH(-0.8) = " << ATanH( c ) << '\n';

    double inval = 1.5; // outside domain -> NaN
    std::cout << "ATanH(1.5) is NaN: " << std::isnan( ATanH( inval ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double t0 = Harlinn::Math::ATanH( 0.0 );
static_assert( t0 == 0.0 );

constexpr double t1 = Harlinn::Math::ATanH( 0.5 );
// atanh(0.5) ~ 0.5493061443340548
static_assert( t1 > 0.5493061443340547 && t1 < 0.5493061443340549 );
```

## See also

- `SinH`, `CosH`, `TanH` � hyperbolic functions.
- `ASinH`, `ACosH` � other inverse hyperbolic functions.
- `Exp`, `Log` � helpers used in hyperbolic computations.

---

Created for the Harlinn.Math library documentation.
