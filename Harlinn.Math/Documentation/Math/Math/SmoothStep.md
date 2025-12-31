# SmoothStep

## Summary

`SmoothStep` produces a smooth S-shaped interpolation between two bounds `a` and `b`. The function maps `x` to a value in [0, 1] with zero first derivative at the endpoints, making it useful for smooth transitions in animation, shading and interpolation.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T SmoothStep( T x, T a, T b );
```

## Behavior

- If `a == b` the function returns `0` for `x < a` and `1` for `x >= a` (degenerate interval handling).
- Otherwise it clamps the normalized parameter `t = (x - a) / (b - a)` to [0, 1] and returns the cubic Hermite polynomial `t*t*(3 - 2*t)`, which has zero slope at `t = 0` and `t = 1`.
- The function is `constexpr` and works in compile-time contexts.

## Notes

- Use `SmoothStep` when you need a smooth transition with no discontinuity in slope at the endpoints (unlike a linear interpolation which has kinks).
- For smooth interpolation between two values `v0` and `v1`, compute `v = Lerp(v0, v1, SmoothStep(x, a, b))`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SmoothStep;

    double a = 0.0;
    double b = 1.0;

    for ( double x = -0.2; x <= 1.2; x += 0.2 )
    {
        double s = SmoothStep( x, a, b );
        std::cout << "SmoothStep(" << x << ", " << a << ", " << b << ") = " << s << '\n';
    }
    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s0 = Harlinn::Math::SmoothStep( 0.0, 0.0, 1.0 );
static_assert( s0 == 0.0 );

constexpr double sHalf = Harlinn::Math::SmoothStep( 0.5, 0.0, 1.0 );
// t = 0.5 -> result = 0.5*0.5*(3 - 2*0.5) = 0.5
static_assert( sHalf == 0.5 );
```

## See also

- `Lerp` — linear interpolation.
- `Clamp` — clamps a value to a given range.
- `SmootherStep` (if available) — higher-order smoothing with continuous second derivative.

---

Created for the Harlinn.Math library documentation.
