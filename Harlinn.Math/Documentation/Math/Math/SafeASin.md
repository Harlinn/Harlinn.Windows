# SafeASin

## Summary

`SafeASin` computes the arc-sine (inverse sine) of `x` while clamping the input into the mathematically valid domain [-1, 1]. This avoids NaN results for inputs slightly outside the domain due to rounding errors. The function forwards to `ASin` after clamping and is `constexpr`-friendly.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T SafeASin( T x );
```

## Behavior

- Clamps the input `x` to the interval [-1, 1] using `Clamp` and then returns `ASin(clamped_x)`.
- Prevents NaN from propagating when `x` is slightly outside the valid domain due to rounding or small numerical error.
- The function is `constexpr` and can be evaluated at compile time when used in appropriate contexts.

## Notes

- Use `SafeASin` when computing arcsine from values obtained by arithmetic that may introduce tiny rounding errors (for example normalized dot products that should nominally be in [-1,1]).
- If strict detection of out-of-range inputs is required, check the input before calling `SafeASin` rather than silently clamping.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SafeASin;

    double x1 = 0.5;
    double x2 = 1.0000000001; // slightly outside due to roundoff

    std::cout << "SafeASin(0.5) = " << SafeASin( x1 ) << '\n';
    std::cout << "SafeASin(1.0000000001) = " << SafeASin( x2 ) << " (clamped)" << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s0 = Harlinn::Math::SafeASin( 0.0 );
static_assert( s0 == 0.0 );

constexpr double s1 = Harlinn::Math::SafeASin( 1.0 );
// asin(1) == pi/2
static_assert( s1 > 1.5707963267948966 - 1e-12 && s1 < 1.5707963267948966 + 1e-12 );
```

## See also

- `ASin` — raw arc-sine function that may return NaN for out-of-domain inputs.
- `SafeACos` — clamped variant of arc-cosine.
- `Clamp` — helper used to restrict values to an interval.

---

Created for the Harlinn.Math library documentation.
