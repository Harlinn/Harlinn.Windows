# SafeACos

## Summary

`SafeACos` computes the arc-cosine (inverse cosine) of `x` while clamping the input into the mathematically valid domain [-1, 1]. This prevents NaN results for inputs that are slightly outside the domain due to rounding errors. The function delegates to `ACos` after clamping and is `constexpr`-friendly.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T SafeACos( T x );
```

## Behavior

- Clamps the input `x` to the interval [-1, 1] using `Clamp` and returns `ACos(clamped_x)`.
- Avoids NaN propagation when `x` is slightly outside the valid domain because of numerical error.
- The function is `constexpr` and can be evaluated at compile time when used in appropriate contexts.

## Notes

- Use `SafeACos` when computing arc-cosine from values produced by finite-precision arithmetic (for example normalized dot products) where tiny overshoot may occur.
- If detection of out-of-range inputs is required, validate `x` before calling `SafeACos` rather than silently clamping.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SafeACos;

    double x1 = 0.0;
    double x2 = -1.0000000001; // slightly outside due to roundoff

    std::cout << "SafeACos(0.0) = " << SafeACos( x1 ) << '\n';
    std::cout << "SafeACos(-1.0000000001) = " << SafeACos( x2 ) << " (clamped)" << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a0 = Harlinn::Math::SafeACos( 1.0 );
// acos(1) == 0
static_assert( a0 == 0.0 );

constexpr double aHalf = Harlinn::Math::SafeACos( 0.0 );
// acos(0) == pi/2
static_assert( aHalf > 1.5707963267948966 - 1e-12 && aHalf < 1.5707963267948966 + 1e-12 );
```

## See also

- `ACos` — raw arc-cosine function that may return NaN for out-of-domain inputs.
- `SafeASin` — clamped variant of arc-sine.
- `Clamp` — helper used to restrict values to an interval.

---

Created for the Harlinn.Math library documentation.
