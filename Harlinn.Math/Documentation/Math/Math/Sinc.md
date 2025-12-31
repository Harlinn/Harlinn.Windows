# Sinc

## Summary

`Sinc` computes the normalized sinc function defined as sin(pi * x) / (pi * x). The function returns `1` for arguments near zero to preserve the limiting value and avoid cancellation.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Sinc( T x );
```

## Behavior

- Returns sin(pi * x) / (pi * x) for a floating-point argument `x`.
- For values of `x` sufficiently close to zero the function returns `1` to avoid division by zero and loss of precision.
- Implemented in terms of `SinXOverX` as `Sinc(x) = SinXOverX(Constants<T>::Pi * x)`.
- The function is `constexpr` and can be evaluated at compile time when used in appropriate contexts.

## Notes

- The normalized sinc function is commonly used in signal processing (ideal low-pass filter impulse response), interpolation, and windowing kernels.
- For unnormalized sinc use `SinXOverX` which computes sin(x)/x.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Sinc;

    double values[] = { 0.0, 0.25, 0.5, 1.0, 2.0 };
    for ( double v : values )
    {
        std::cout << "Sinc(" << v << ") = " << Sinc( v ) << '\n';
    }

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s0 = Harlinn::Math::Sinc( 0.0 );
static_assert( s0 == 1.0 );

constexpr double s1 = Harlinn::Math::Sinc( 1.0 );
// sin(pi)/ (pi) == 0
static_assert( s1 == 0.0 );
```

## See also

- `SinXOverX` — unnormalized sinc function (sin(x) / x).
- `WindowedSinc` — windowed variant of the sinc function.

---

Created for the Harlinn.Math library documentation.
