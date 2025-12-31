# ErfC

## Summary

`ErfC` computes the complementary error function (erfc) of a floating-point value. It delegates to the library's `OpenLibM` helpers and is `constexpr`-friendly when those helpers are available in constant-evaluation contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T ErfC( T x ) noexcept;
```

## Behavior

- Returns the complementary error function, erfc(x) = 1 - erf(x).
- For `float` the implementation delegates to `Math::Internal::OpenLibM::erfcf`; for `double` it delegates to `Math::Internal::OpenLibM::erfc`.
- The function is `noexcept` and can be used in `constexpr` contexts when the underlying helpers are constexpr-capable.
- Special values follow the underlying library semantics: `ErfC(NaN) = NaN`, `ErfC(+inf) = 0`, `ErfC(-inf) = 2`.

## Notes

- `ErfC` is useful for computing tail probabilities of the normal distribution and for numerical stability when x is large, where `1 - Erf(x)` may lose precision.
- Prefer `ErfC` over `1 - Erf(x)` for large positive `x` to preserve accuracy.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ErfC;

    double a = 0.0;
    double b = 0.5;
    double c = 2.0;

    std::cout << "ErfC(0) = " << ErfC( a ) << '\n';      // 1
    std::cout << "ErfC(0.5) = " << ErfC( b ) << '\n';    // ~0.4795001221869535
    std::cout << "ErfC(2.0) = " << ErfC( c ) << '\n';    // ~0.004677734981047266

    double inf = std::numeric_limits<double>::infinity();
    std::cout << "ErfC(inf) = " << ErfC( inf ) << '\n';  // 0
    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double ec0 = Harlinn::Math::ErfC( 0.0 );
static_assert( ec0 == 1.0 );

constexpr double ec1 = Harlinn::Math::ErfC( 1.0 );
// erfc(1) ~ 0.1572992070502851
static_assert( ec1 > 0.1572992070502850 && ec1 < 0.1572992070502852 );
```

## See also

- `Erf` — error function.
- `Gaussian`, `GaussianIntegral` — helpers that use the error function for normal distribution calculations.

---

Created for the Harlinn.Math library documentation.
