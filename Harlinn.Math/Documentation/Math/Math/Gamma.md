# Gamma

## Summary

`Gamma` in this library is a small helper that returns an estimate of the maximum relative error after `n` floating-point operations. It is not the Euler Gamma function. The estimate is calculated using the library machine epsilon for the given floating-point type.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Gamma( int n );
```

## Behavior

- Returns the value

  (n * MachineEpsilon) / (1 - n * MachineEpsilon)

  where `MachineEpsilon` is `Constants<T>::MachineEpsilon` for the floating-point type `T`.
- The result is a conservative estimate of the maximum relative error that can accumulate from `n` operations, taking into account first-order effects of rounding.
- The function is `constexpr` and usable in compile-time contexts when `n` and the type are compile-time known.

## Notes

- This `Gamma` is intended as an error bound helper to adjust tolerances or to create conservative intervals for numerical algorithms — for example when computing guaranteed bounds on sums or polynomial evaluations.
- Do not confuse this helper with the mathematical Euler Gamma function (?). If you need Euler's Gamma use a dedicated special-function implementation.
- For large `n` such that `n * MachineEpsilon` approaches `1`, the expression can overflow or produce very large values; in such situations this estimate is no longer meaningful and `n` should be reduced or a different error model used.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Gamma;

    int n = 10; // estimate error after 10 operations
    double gDouble = Gamma<double>( n );
    float gFloat = Gamma<float>( n );

    std::cout << "Gamma<double>(10) = " << gDouble << '\n';
    std::cout << "Gamma<float>(10)  = " << gFloat << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double g4 = Harlinn::Math::Gamma<double>( 4 );
static_assert( g4 > 0.0 );

constexpr float g0 = Harlinn::Math::Gamma<float>( 0 );
static_assert( g0 == 0.0f );
```

## See also

- `Constants<T>::MachineEpsilon` — machine epsilon used by the estimate.
- Interval helpers such as `Interval::FromValueAndError` and `AddAdjustUp/AddAdjustDown` that use conservative error adjustments.

---

Created for the Harlinn.Math library documentation.
