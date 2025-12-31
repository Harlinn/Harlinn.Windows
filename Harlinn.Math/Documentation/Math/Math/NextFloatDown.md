# NextFloatDown

## Summary

`NextFloatDown` returns the next representable floating-point value strictly less than the given value `v`. It is a thin wrapper around `NextDown` and is `constexpr`-friendly so it can be used in compile-time contexts as well as at runtime.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T NextFloatDown( T v );
```

## Behavior

- Returns the largest representable floating-point value strictly less than `v`.
- If `v` is -infinity the function returns -infinity. If `v` is NaN the behavior follows the underlying `NextDown` semantics.
- For positive zero, the next float down is the largest negative subnormal value (i.e. -0 or the negative smallest magnitude depending on implementation details).
- The implementation forwards to `NextDown`, which manipulates the bit pattern of the floating-point value to step to the previous representable value and handles special cases such as infinities, zeros, subnormals, and NaNs.
- The function is `constexpr` and can be evaluated at compile time when permitted.

## Notes

- Use `NextFloatDown` when you need conservative lower bounds or want to step downward through representable floating-point values (for example when computing safe lower error bounds).
- For the next representable value greater than `v`, use `NextFloatUp` / `NextUp`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::NextFloatDown;

    float f = 1.0f;
    float fPrev = NextFloatDown( f );
    std::cout << "NextFloatDown(1.0f) = " << fPrev << '\n';

    double d = 0.0;
    double dPrev = NextFloatDown( d );
    std::cout << "NextFloatDown(0.0) = " << dPrev << " (largest negative subnormal for double)" << '\n';

    float ninf = -std::numeric_limits<float>::infinity();
    std::cout << "NextFloatDown(-inf) = " << NextFloatDown( ninf ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"
#include <limits>

constexpr float onePrev = Harlinn::Math::NextFloatDown( 1.0f );
static_assert( onePrev < 1.0f );

constexpr double zeroPrev = Harlinn::Math::NextFloatDown( 0.0 );
static_assert( zeroPrev < 0.0 );
static_assert( zeroPrev == Harlinn::Math::NextDown( 0.0 ) );
```

## See also

- `NextDown`, `NextUp` — lower-level helpers that operate on floating-point bit patterns.
- `NextFloatUp` — returns the next representable value greater than the input.
- `NextAfter` — returns the next representable value of `x` in the direction of `y`.

---

Created for the Harlinn.Math library documentation.
