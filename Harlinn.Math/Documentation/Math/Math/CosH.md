# CosH

## Summary

`CosH` computes the hyperbolic cosine (`cosh`) of a floating-point value. The function is `constexpr`-friendly in constant-evaluation contexts and delegates to the library's `OpenLibM` helpers for consistent behavior across platforms.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T CosH( T x ) noexcept;
```

## Behavior

- Returns the hyperbolic cosine of `x`, defined as `(e^x + e^-x)/2`.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::coshf`.
- For `double` the implementation uses `Math::Internal::OpenLibM::cosh` in const-evaluation contexts and `std::cosh` at runtime when appropriate.
- Special values follow the underlying helpers' semantics: `CosH(NaN) = NaN`, `CosH(±inf) = +?`.
- The function is `noexcept` and can be used in `constexpr` contexts when the underlying helpers are constexpr-capable.

## Notes

- Hyperbolic functions are dimensionless; results grow rapidly for large |x| (approximately 0.5 * e^{|x|}).
- Use `CosH` when you need consistent constexpr-capable hyperbolic cosine across compile-time and runtime.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::CosH;

    double v1 = 0.0;    // cosh(0) == 1
    double v2 = 1.0;    // cosh(1) ~ 1.54308
    double v3 = -2.0;   // cosh(-2) == cosh(2) ~ 3.7622

    std::cout << "CosH(0) = " << CosH( v1 ) << '\n';
    std::cout << "CosH(1) = " << CosH( v2 ) << '\n';
    std::cout << "CosH(-2) = " << CosH( v3 ) << '\n';

    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "CosH(NaN) is NaN: " << std::isnan( CosH( qnan ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double c0 = Harlinn::Math::CosH( 0.0 );
static_assert( c0 == 1.0 );

constexpr double c1 = Harlinn::Math::CosH( 1.0 );
static_assert( c1 > 1.54308 - 1e-12 && c1 < 1.54308 + 1e-12 );
```

## See also

- `SinH`, `TanH`, `ASinH` — related hyperbolic functions.
- `Exp`, `Log` — helpers for exponential and logarithmic computations.

---

Created for the Harlinn.Math library documentation.
