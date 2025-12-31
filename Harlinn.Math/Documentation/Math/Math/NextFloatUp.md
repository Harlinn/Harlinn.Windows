# NextFloatUp

## Summary

`NextFloatUp` returns the next representable floating-point value greater than the given value `v`. It is a thin wrapper around `NextUp` and is `constexpr`-friendly, so it can be used in compile-time contexts as well as at runtime.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T NextFloatUp( T v );
```

## Behavior

- Returns the smallest representable floating-point value strictly greater than `v`.
- If `v` is +infinity the function returns +infinity. If `v` is NaN the behavior follows the underlying `NextUp` semantics.
- For negative zero, the next float up is the smallest positive subnormal value.
- The implementation forwards to `NextUp`, which manipulates the bit-pattern of the floating-point value to step to the next representable value and handles special cases such as infinities, zeros, subnormals, and NaNs.
- The function is `constexpr` and can be evaluated in `consteval` or compile-time contexts where permitted.

## Notes

- Use `NextFloatUp` when you need to perform robust comparisons or set bounds with conservative rounding (for example when computing safe upper bounds for numeric algorithms).
- For the next representable value less than `v`, use `NextFloatDown` / `NextDown`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::NextFloatUp;

    float f = 1.0f;
    float fNext = NextFloatUp( f );
    std::cout << "NextFloatUp(1.0f) = " << fNext << '\n';

    double d = 0.0;
    double dNext = NextFloatUp( d );
    std::cout << "NextFloatUp(0.0) = " << dNext << " (smallest positive subnormal for double)" << '\n';

    float inf = std::numeric_limits<float>::infinity();
    std::cout << "NextFloatUp(+inf) = " << NextFloatUp( inf ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"
#include <limits>

constexpr float oneNext = Harlinn::Math::NextFloatUp( 1.0f );
static_assert( oneNext > 1.0f );

constexpr double zeroNext = Harlinn::Math::NextFloatUp( 0.0 );
static_assert( zeroNext > 0.0 );
static_assert( zeroNext == Harlinn::Math::NextUp( 0.0 ) );
```

## See also

- `NextUp`, `NextDown` — lower-level helpers that operate on floating-point bit patterns.
- `NextFloatDown` — returns the next representable value less than the input.
- `NextAfter` — returns the next representable value of `x` in the direction of `y`.

---

Created for the Harlinn.Math library documentation.
