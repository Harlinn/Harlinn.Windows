# NextDown

## Summary

`NextDown` returns the largest representable floating-point value of the same type as the argument that is strictly less than the given value.

The function is `constexpr` and `noexcept` and works for both `float` and `double` (and other floating-point types supported by the library) including constant-evaluation contexts.

## Declaration

```cpp
template<FloatingPointType T>
inline constexpr T NextDown(T x) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- Returns the largest representable value `y` of the same type as `x` such that `y < x`.
- Correctly handles special cases:
  - If `x` is `NaN`, the implementation follows the library's behavior (generally `NaN` is returned or handled via the underlying helpers).
  - If `x` is `+0.0`, `NextDown(+0.0)` returns the largest negative subnormal (i.e. `-min_denormal`).
  - If `x` is `-0.0`, `NextDown(-0.0)` returns the next more-negative representable value (a negative subnormal closer to negative infinity).
  - If `x` is `-infinity`, `NextDown(-inf)` returns `-inf` (no representable smaller value exists).
  - If `x` is `+infinity`, `NextDown(+inf)` returns the largest finite representable value.
- The implementation uses bit-level manipulation so it can be evaluated in `consteval` contexts and preserves IEEE-754 semantics for signed zeros and NaNs.

## Notes

- Use `NextDown` when you need to step a floating-point value one unit in the last place (ULP) downward.
- For the upward counterpart use `NextUp` or `NextFloatUp`.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <iomanip>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::NextDown;

    double v = 1.0;
    double vDown = NextDown(v);
    std::cout << std::setprecision(17);
    std::cout << "NextDown(1.0) = " << vDown << '\n';

    // From positive zero
    float pz = 0.0f;
    float pzDown = NextDown(pz);
    std::cout << "NextDown(+0.0f) = " << std::hexfloat << pzDown << std::defaultfloat << '\n';

    // From negative zero
    float nz = -0.0f;
    float nzDown = NextDown(nz);
    std::cout << "NextDown(-0.0f) = " << std::hexfloat << nzDown << std::defaultfloat << '\n';

    // From +infinity
    double infDown = NextDown( std::numeric_limits<double>::infinity() );
    std::cout << "NextDown(+inf) = " << infDown << " (largest finite double)\n";

    // From -infinity (remains -inf)
    double negInfDown = NextDown( -std::numeric_limits<double>::infinity() );
    std::cout << "NextDown(-inf) = " << negInfDown << " (-inf)\n";

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::NextDown( 1.0 ) < 1.0 );
static_assert( Harlinn::Math::NextDown( 0.0f ) < 0.0f );
// NextDown(-inf) remains -inf (check property)
static_assert( Harlinn::Math::NextDown( -std::numeric_limits<double>::infinity() ) == -std::numeric_limits<double>::infinity() );
```

## See also

- `NextUp`, `NextFloatUp`, `NextAfter` for related functions that step floating-point values.

---

Created for the Harlinn.Math library documentation.
