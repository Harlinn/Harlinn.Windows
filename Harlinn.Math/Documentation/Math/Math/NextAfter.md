# NextAfter

## Summary

`NextAfter` returns the next representable floating-point value of `x` in the direction of `y`.

- Two overloads are provided:
  - `inline constexpr double NextAfter(double x, double y) noexcept;`
  - `inline constexpr float NextAfter(float x, float y) noexcept;`
- The functions are `constexpr` and `noexcept`.
- When evaluated in a constant evaluation context the implementation uses the library's constexpr math helpers; at runtime it uses standard library facilities or a carefully crafted bit-manipulation implementation for correct IEEE-754 behavior.

## Behavior

- If `x == y` the function returns `y`.
- If `y` is greater than `x` the function returns the smallest representable floating-point value greater than `x` (the next-up value).
- If `y` is less than `x` the function returns the largest representable floating-point value less than `x` (the next-down value).
- The function correctly handles signed zero, subnormal values, infinities and NaNs:
  - If either argument is NaN the float implementation returns `x + y` (propagating NaN according to the implementation).
  - When stepping from zero it returns the smallest subnormal with the sign of `y`.
  - When overflow occurs it returns an infinity with the sign of `y`.

## Notes

- Use `NextAfter` when you need precise control over floating-point stepping (e.g. testing rounding behavior, numerical algorithms requiring next representable values, or adjusting boundaries by one ULP).
- For convenience there are also `NextUp` / `NextDown` wrappers and `NextFloatUp` / `NextFloatDown` aliases in the same header.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <bit>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::NextAfter;

    // If x == y, returns y
    double a = 1.0;
    double b = 1.0;
    std::cout << "NextAfter(1.0, 1.0) = " << NextAfter(a, b) << '\n'; // prints 1

    // Next representable greater than 1.0 (towards 2.0)
    double nextUp = NextAfter(1.0, 2.0);
    std::cout << "Next representable after 1.0 towards 2.0 = " << std::setprecision(17) << nextUp << '\n';

    // Next representable less than 1.0 (towards 0.0)
    double nextDown = NextAfter(1.0, 0.0);
    std::cout << "Next representable after 1.0 towards 0.0 = " << std::setprecision(17) << nextDown << '\n';

    // From zero towards positive: returns smallest positive subnormal
    float zeroNext = NextAfter(0.0f, 1.0f);
    std::cout << "NextAfter(+0.0f, 1.0f) = " << std::hexfloat << zeroNext << std::defaultfloat << '\n';

    // From zero towards negative: returns smallest negative subnormal
    float zeroNextNeg = NextAfter(0.0f, -1.0f);
    std::cout << "NextAfter(+0.0f, -1.0f) = " << std::hexfloat << zeroNextNeg << std::defaultfloat << '\n';

    // Stepping towards infinity: overflow produces signed infinity
    float big = std::numeric_limits<float>::max();
    float overflow = NextAfter(big, std::numeric_limits<float>::infinity());
    std::cout << "NextAfter(max_float, +inf) = " << overflow << '\n'; // prints inf

    return 0;
}
```

Compile-time example using `static_assert` (requires constexpr evaluation):

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::NextAfter( 1.0, 1.0 ) == 1.0 );
// The next representable double greater than 1.0 is strictly greater than 1.0
static_assert( Harlinn::Math::NextAfter( 1.0, 2.0 ) > 1.0 );
// Stepping from zero towards positive yields a non-zero subnormal
static_assert( Harlinn::Math::NextAfter( 0.0, 1.0 ) != 0.0 );
```

## See also

- `NextUp`, `NextDown`, `NextFloatUp`, `NextFloatDown` — helpers for stepping one ULP in a fixed direction.
- `CopySign` — compose sign/magnitude when handling signed zeros and infinities.

---

Created for the Harlinn.Math library documentation.
