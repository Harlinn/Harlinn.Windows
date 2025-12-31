# SinXOverX

## Summary

`SinXOverX` computes the sinc function sin(x)/x in a numerically robust way. It returns `1` for arguments near zero to avoid division by zero and loss of precision.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T SinXOverX( T x );
```

## Behavior

- Returns `sin(x)/x` for a floating-point argument `x`.
- For values of `x` sufficiently close to zero the function returns `1` to preserve the limiting value and avoid catastrophic cancellation.
- The implementation calls `Math::Sin(x)/x` and checks the small-argument condition with a comparison that is safe for floating-point arithmetic.
- The function is `constexpr` and can be evaluated at compile time when used in suitable contexts.

## Notes

- The sinc function appears often in signal processing, interpolation kernels, and analysis of Fourier transforms.
- Use `Sinc` (the normalized sinc) when you need sin(pi*x)/(pi*x); `Sinc` is implemented in the library as `Sinc(x) = SinXOverX(Constants<T>::Pi * x)`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h"

int main()
{
    using Harlinn::Math::SinXOverX;

    double vals[] = {0.0, 1e-8, 0.5, 1.0, 3.14159265358979323846};
    for ( double v : vals )
    {
        std::cout << "SinXOverX(" << v << ") = " << SinXOverX( v ) << '\n';
    }

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s0 = Harlinn::Math::SinXOverX( 0.0 );
static_assert( s0 == 1.0 );

constexpr double s1 = Harlinn::Math::SinXOverX( 3.14159265358979323846 );
// sin(pi)/pi == 0
static_assert( s1 == 0.0 );
```

## See also

- `Sinc` — normalized sinc function (sin(pi*x) / (pi*x)).
- `Sin`, `Cos` — basic trigonometric functions.

---

Created for the Harlinn.Math library documentation.
