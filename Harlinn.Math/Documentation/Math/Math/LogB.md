# LogB

## Summary

`LogB` extracts the unbiased radix-independent exponent from a floating-point value and returns it as a floating-point value. This is equivalent to `logb`/`logbf` from the C math library and is `constexpr`-friendly via the library's `OpenLibM` helpers.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T LogB( T x ) noexcept;
```

## Behavior

- Returns the unbiased exponent of `x` as a floating-point value. For finite non-zero values `x = m * 2^e` with `m` in the range [1, 2) (or equivalent), `LogB(x)` returns `e`.
- For zero returns `-inf` (or the implementation-defined behavior of `logb(0)`).
- For infinite `x` returns `+inf`.
- For NaN input returns NaN.
- Uses `Math::Internal::OpenLibM::logb`/`logbf` for `consteval` and consistent behavior.

## Notes

- `LogB` returns the exponent as a floating-point value; to get an integer exponent use `ILogB` which returns an `int`.
- This function is useful when you need the exponent separated from the significand for scaling or numeric analysis.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h"

int main()
{
    using Harlinn::Math::LogB;

    double v1 = 8.0;       // 8.0 == 1.0 * 2^3
    double v2 = 0.15625;   // 0.15625 == 1.25 * 2^-3

    std::cout << "LogB(8.0) = " << LogB( v1 ) << '\n';     // Expected 3
    std::cout << "LogB(0.15625) = " << LogB( v2 ) << '\n'; // Expected -3

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double e1 = Harlinn::Math::LogB( 8.0 );
static_assert( e1 == 3.0 );

constexpr float e2 = Harlinn::Math::LogB( 0.125f ); // 0.125 == 2^-3
static_assert( e2 == -3.f );
```

## See also

- `ILogB` — returns the exponent as an `int`.
- `FRExp`, `Frexp` — decompose a floating-point number into mantissa and exponent.
- `Log`, `Log2`, `Log10` — other logarithm helpers.

---

Created for the Harlinn.Math library documentation.
