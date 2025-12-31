# Exp10

## Summary

`Exp10` computes 10 raised to the power `x`, i.e. 10^x, for floating-point inputs. The function is `constexpr`-friendly and uses the library's internal helpers for consistent compile-time and runtime semantics.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Exp10( T x ) noexcept;
```

## Behavior

- Returns 10^x computed in a numerically stable manner.
- In constant-evaluation contexts the implementation computes the result using `Pow(10.0, x)` (via internal helpers). At runtime optimized SIMD or standard-library helpers may be used for performance while preserving semantics.
- Special values follow IEEE rules: `Exp10(+inf) = +inf`, `Exp10(-inf) = 0`, and `Exp10(NaN) = NaN`.
- The function is `constexpr` and `noexcept` where applicable.

## Notes

- Use `Exp10` when converting logarithmic values in base 10 to linear scale, or when working with decimal exponentials.
- For integer exponents and exact powers prefer integer-based scaling when appropriate.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Exp10;

    double a = 2.0;
    double b = -1.0;
    float  c = 0.5f;

    std::cout << std::setprecision(8);
    std::cout << "Exp10(2.0) = " << Exp10( a ) << '\n';    // 100.0
    std::cout << "Exp10(-1.0) = " << Exp10( b ) << '\n';   // 0.1
    std::cout << "Exp10(0.5f) = " << Exp10( c ) << '\n';   // sqrt(10) (~3.1622777)

    // Large exponent -> infinity
    std::cout << "Exp10(400) is infinite: " << std::isinf( Exp10( 400.0 ) ) << '\n';

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

constexpr double r1 = Harlinn::Math::Exp10( 3.0 );
static_assert( r1 == 1000.0 );

constexpr float r2 = Harlinn::Math::Exp10( 0.5f ); // sqrt(10)
static_assert( r2 > 3.162277f && r2 < 3.162278f );
```

## See also

- `Exp`, `Exp2`, `ExpM1` — related exponential helpers.
- `Pow` — general power function.

---

Created for the Harlinn.Math library documentation.
