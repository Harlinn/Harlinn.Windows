# ReciprocalSqrt

[Optimized basic math functions](Readme.md)/[Power and root finding functions](PowerFunctions.md)/`ReciprocalSqrt`

## Summary

`ReciprocalSqrt` computes the reciprocal of the square root (1 / sqrt(x)) of a floating-point value. The function is `constexpr` and `noexcept` and provides fast runtime implementations while remaining usable in constant-evaluation contexts.

- For `float` in consteval contexts it calls `Internal::OpenLibM::sqrtf` and returns `1 / sqrtf(x)`.
- For `float` at runtime it uses an SSE fast reciprocal-square-root via `_mm_rsqrt_ps` for performance.
- For `double` it uses the library's constexpr `sqrt` in consteval and falls back to `1 / Sqrt(x)` at runtime.

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T ReciprocalSqrt(T x) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- Returns `1 / Sqrt(x)` with IEEE-754 semantics.
- If `x == 0` the function returns signed infinity (with the sign of `x`) when evaluated in consteval for `float`/`double`.
- For runtime `float` the implementation uses an SSE reciprocal-square-root instruction which is fast but may be slightly less accurate than `1.0f / std::sqrtf(x)`; the library uses `_mm_rsqrt_ps` result directly for performance.
- The function supports constexpr evaluation when available via `Internal::OpenLibM` helpers.

## Notes

- Use `ReciprocalSqrt` when you need a fast reciprocal-square-root operation. For highest numerical accuracy prefer `1 / Sqrt(x)` explicitly if required.
- Be aware of special values (zero, subnormals, infinities and NaNs) which are handled according to IEEE rules.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <limits>
#include <iomanip>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ReciprocalSqrt;

    float f = 4.0f;
    std::cout << std::setprecision(9);
    std::cout << "ReciprocalSqrt(4.0f) = " << ReciprocalSqrt(f) << " (expected 0.5)\n";

    double d = 2.0;
    std::cout << "ReciprocalSqrt(2.0) = " << ReciprocalSqrt(d) << " (expected ~0.7071067811865476)\n";

    float zero = 0.0f;
    std::cout << "ReciprocalSqrt(0.0f) = " << ReciprocalSqrt(zero) << " (signed infinity expected)\n";

    float nan = std::numeric_limits<float>::quiet_NaN();
    std::cout << "ReciprocalSqrt(NaN) = " << ReciprocalSqrt(nan) << " (NaN expected)\n";

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::ReciprocalSqrt( 1.0f ) == 1.0f );
static_assert( Harlinn::Math::ReciprocalSqrt( 4.0 ) == 0.5 );
// Value comparisons with non-integers may require tolerance checks if compared outside constexpr
```

## See also

- `Sqrt`, `NextUp`, `NextDown` for related numeric helpers.

