# WindowedSinc

## Summary

`WindowedSinc` computes a windowed normalized sinc kernel: it multiplies the normalized sinc `Sinc(x)` by a secondary sinc window `Sinc(x / tau)` and cuts off the function outside a given radius. The function is useful for bandlimited interpolation and kernel-based filtering where a compactly supported, smooth kernel is desired.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T WindowedSinc( T x, T radius, T tau );
```

## Behavior

- If `Abs(x) > radius` the function returns `0` (compact support).
- Otherwise it returns `Sinc(x) * Sinc(x / tau)`, where `Sinc(x) = sin(pi*x) / (pi*x)` (implemented in the library as `Sinc`) and `Abs` is the absolute value helper.
- The parameter `radius` specifies the cutoff radius beyond which the kernel is zero; `tau` controls the width of the windowing sinc (commonly `tau >= 1`).
- The function is `constexpr` and can be evaluated at compile time when used in appropriate contexts.

## Notes

- Choose `tau` to control the tradeoff between main-lobe width and side-lobe attenuation. Typical windowing choices use `tau` between 1 and 2.
- For interpolation use, set `radius` to the desired support (e.g., `radius = 4` for a 4-sample radius) and evaluate the kernel at sample offsets.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::WindowedSinc;

    double radius = 4.0; // support radius
    double tau = 2.0;    // window parameter

    for ( double x = -5.0; x <= 5.0; x += 0.5 )
    {
        double v = WindowedSinc( x, radius, tau );
        std::cout << "WindowedSinc(" << x << ") = " << v << '\n';
    }
    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double radius = 3.0;
constexpr double tau = 1.5;
constexpr double w0 = Harlinn::Math::WindowedSinc( 0.0, radius, tau );
static_assert( w0 == 1.0 ); // Sinc(0) == 1 and window Sinc(0) == 1

constexpr double wOut = Harlinn::Math::WindowedSinc( 4.0, radius, tau );
static_assert( wOut == 0.0 ); // outside radius
```

## See also

- `Sinc` — normalized sinc function (sin(pi*x)/(pi*x)).
- `SinXOverX` — unnormalized sinc (sin(x)/x).
- Window design references for choosing `tau` and `radius` when building interpolation kernels.

---

Created for the Harlinn.Math library documentation.
