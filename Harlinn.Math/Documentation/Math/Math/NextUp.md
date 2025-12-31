# NextUp

## Summary

`NextUp` returns the smallest representable floating-point value of the same type as the argument that is strictly greater than the given value.

The function is `constexpr` and `noexcept` and works for `float`, `double`, and other floating-point types supported by the library. It is implemented using bit-level manipulation so it is usable in constant-evaluation contexts and preserves IEEE-754 semantics for signed zeros, subnormals, infinities and NaNs.

## Declaration

```cpp
template<FloatingPointType T>
inline constexpr T NextUp(T x) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- Returns the smallest representable value `y` of the same type as `x` such that `x < y`.
- Correctly handles special cases:
  - If `x` is `NaN`, behavior follows the library's policy (NaN is typically returned or handled via underlying helpers).
  - If `x` is `+0.0`, `NextUp(+0.0)` returns the smallest positive subnormal.
  - If `x` is `-0.0`, `NextUp(-0.0)` returns the smallest positive subnormal (i.e. it moves upward across signed zero to the smallest positive subnormal).
  - If `x` is `+infinity`, `NextUp(+inf)` returns `+inf` (no larger representable value exists).
  - If `x` is `-infinity`, `NextUp(-inf)` returns the largest negative finite representable value.
- The implementation uses bit manipulations (sign/exponent/fraction masks) so it is `constexpr`-friendly and preserves signed-zero handling.

## Notes

- Use `NextUp` when you need to step a floating-point value one unit in the last place (ULP) upward.
- For the downward counterpart use `NextDown` or `NextFloatDown`.
- There are convenience aliases `NextFloatUp`/`NextFloatDown` which call `NextUp`/`NextDown` respectively.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <iomanip>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::NextUp;

    double v = 1.0;
    double vUp = NextUp(v);
    std::cout << std::setprecision(17);
    std::cout << "NextUp(1.0) = " << vUp << '\n';

    // From positive zero
    float pz = 0.0f;
    float pzUp = NextUp(pz);
    std::cout << "NextUp(+0.0f) = " << std::hexfloat << pzUp << std::defaultfloat << '\n';

    // From negative zero
    float nz = -0.0f;
    float nzUp = NextUp(nz);
    std::cout << "NextUp(-0.0f) = " << std::hexfloat << nzUp << std::defaultfloat << '\n';

    // From +infinity (remains +inf)
    double infUp = NextUp( std::numeric_limits<double>::infinity() );
    std::cout << "NextUp(+inf) = " << infUp << " (+inf)\n";

    // From -infinity (largest finite double)
    double negInfUp = NextUp( -std::numeric_limits<double>::infinity() );
    std::cout << "NextUp(-inf) = " << negInfUp << " (largest finite double)\n";

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::NextUp( 1.0 ) > 1.0 );
static_assert( Harlinn::Math::NextUp( 0.0f ) > 0.0f );
// NextUp(+inf) remains +inf (property check)
static_assert( Harlinn::Math::NextUp( std::numeric_limits<double>::infinity() ) == std::numeric_limits<double>::infinity() );
```

## See also

- `NextDown`, `NextAfter`, `NextFloatUp`, `NextFloatDown` for related stepping operations.

---

Created for the Harlinn.Math library documentation.
