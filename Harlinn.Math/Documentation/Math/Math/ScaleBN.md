# ScaleBN

## Summary

`ScaleBN` multiplies a floating-point value `x` by `FLT_RADIX` raised to the integer power `n` (i.e. scales `x` by the floating-point radix to the power `n`). The function provides `float` and `double` overloads and is `constexpr` so it can be used in compile-time contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
inline constexpr double ScaleBN( double x, int n ) noexcept;
inline constexpr float ScaleBN( float x, int n ) noexcept;
```

## Behavior

- Returns the value `x * (FLT_RADIX^n)` while taking care to handle subnormal numbers, zeros, infinities and NaNs in a well-defined manner.
- For subnormal inputs the implementation multiplies by a power-of-two factor to renormalize where appropriate.
- If the resulting exponent would overflow the type's range the function returns an infinity with the sign of `x` (using `CopySign`).
- If the result underflows the function returns a suitably signed zero or a tiny scaled value as the implementation dictates.
- The function does not raise exceptions; special values (NaN/Inf) are propagated according to IEEE rules.

## Notes

- `ScaleBN` is useful when you need to scale a floating-point value by exact powers of the floating-point radix (commonly 2) without losing exactness when possible.
- Prefer this function over manually multiplying by `std::pow` when scaling by radix powers for correctness and performance.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ScaleBN;

    double x = 1.5;
    std::cout << "ScaleBN(1.5, 3) = " << ScaleBN( x, 3 ) << '\n'; // 1.5 * 2^3 = 12.0 (assuming FLT_RADIX == 2)

    float y = 4.0f;
    std::cout << "ScaleBN(4.0f, -2) = " << ScaleBN( y, -2 ) << '\n'; // 4.0 * 2^-2 = 1.0f

    // Large exponent -> overflow to infinity
    double big = ScaleBN( 1.0, 1024 );
    std::cout << "ScaleBN(1.0, 1024) is infinite: " << std::isinf( big ) << '\n';

    // Propagation of NaN
    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "ScaleBN(NaN, 10) is NaN: " << std::isnan( ScaleBN( qnan, 10 ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double scaled = Harlinn::Math::ScaleBN( 3.0, 2 );
static_assert( scaled == 12.0 );

constexpr float scaledF = Harlinn::Math::ScaleBN( 8.0f, -1 );
static_assert( scaledF == 4.0f );
```

## See also

- `NextUp`, `NextDown`, `CopySign` — helpers used for edge-case handling.
- `MulPow2` / `MulAdjustUp` / `MulAdjustDown` — related scaling and adjusted arithmetic helpers.

---

Created for the Harlinn.Math library documentation.
