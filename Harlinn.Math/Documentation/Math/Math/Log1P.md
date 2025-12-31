# Log1P

## Summary

`Log1P` computes the natural logarithm of `1 + x` (i.e. `ln(1 + x)`) with improved accuracy for values of `x` near zero. The function is `constexpr`-friendly and delegates to the library's `OpenLibM` helpers for consistent behavior in both compile-time and runtime contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Log1P( T x ) noexcept;
```

## Behavior

- Returns `ln(1 + x)` computed in a numerically stable way for small `x` to avoid catastrophic cancellation when `x` is close to zero.
- In constant-evaluation contexts the implementation calls `Math::Internal::OpenLibM::log1p`/`log1pf` to provide constexpr-capable and platform-consistent behavior.
- For runtime evaluation the same internal helpers are used.
- Special values follow IEEE rules: `Log1P(+inf) = +inf`, `Log1P(-1) = -inf`, and `Log1P(NaN) = NaN`.
- The function is `noexcept`.

## Notes

- Prefer `Log1P` when computing `ln(1 + x)` for small `x` (for example, `|x| << 1`) to preserve precision compared to computing `Log(1 + x)` directly.
- Use `ExpM1` when you need `exp(x) - 1` with improved accuracy for small `x`.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Log1P;

    double small = 1e-8;
    double normal = 0.5;

    std::cout << "Log1P(1e-8) = " << Log1P( small ) << '\n';
    std::cout << "Log(1 + 1e-8) = " << Harlinn::Math::Log( 1.0 + small ) << '\n';

    std::cout << "Log1P(0.5) = " << Log1P( normal ) << '\n'; // ~0.405465

    // Edge cases
    std::cout << "Log1P(-1) is -inf: " << std::isinf( Log1P( -1.0 ) ) << '\n';
    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "Log1P(NaN) is NaN: " << std::isnan( Log1P( qnan ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double v0 = Harlinn::Math::Log1P( 0.0 );
static_assert( v0 == 0.0 );

constexpr double v1 = Harlinn::Math::Log1P( 1e-8 );
static_assert( v1 > 0.0 );
```

## See also

- `Log` — natural logarithm of `x`.
- `Log2`, `Log10` — logarithms with different bases.
- `ExpM1` — computes `exp(x) - 1` with improved accuracy for small `x`.

---

Created for the Harlinn.Math library documentation.
