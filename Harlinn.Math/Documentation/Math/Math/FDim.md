# FDim

## Summary

`FDim` returns the positive difference between two floating-point values: if `x > y` it returns `x - y`, otherwise it returns positive zero. The implementation delegates to the library's `OpenLibM` helpers and is usable in constant-evaluation contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T FDim( T x, T y ) noexcept;
```

## Behavior

- If `x > y` the function returns `x - y` (calculated with the semantics of the underlying math implementation).
- If `x <= y` the function returns `+0` (positive zero of the appropriate floating type).
- For `float` the implementation delegates to `Math::Internal::OpenLibM::fdimf`; for `double` it delegates to `Math::Internal::OpenLibM::fdim`.
- The function is `noexcept` and follows the underlying OpenLibM semantics for special values (NaN, infinities, signed zeros).

## Notes

- `FDim` differs from a plain subtraction in that it guarantees a non-negative result (or +0) even when `x <= y`.
- Useful for computing positive differences, durations, or clamped deltas without branching.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::FDim;

    double a = 5.3;
    double b = 2.0;
    double c = 7.0;

    std::cout << "FDim(5.3, 2.0) = " << FDim( a, b ) << '\n'; // 3.3
    std::cout << "FDim(5.3, 7.0) = " << FDim( a, c ) << '\n'; // +0

    // NaN propagation
    double nan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "FDim(NaN, 1.0) is NaN: " << std::isnan( FDim( nan, 1.0 ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double d1 = Harlinn::Math::FDim( 5.0, 3.0 );
static_assert( d1 == 2.0 );

constexpr double d2 = Harlinn::Math::FDim( 2.0, 4.0 );
static_assert( d2 == 0.0 );
```

## See also

- `FMod`, `Mod` — remainders and modulus operations.
- `Max`, `Clamp` — helpers for bounds and clamping.

---

Created for the Harlinn.Math library documentation.
