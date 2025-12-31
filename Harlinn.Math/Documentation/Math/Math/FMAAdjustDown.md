# FMAAdjustDown

## Summary

`FMAAdjustDown` computes the fused multiply-add of three floating-point values and then adjusts the result downward to conservatively account for rounding error. It returns `NextDown(FMA(a, b, c))`, producing the largest representable floating-point value strictly less than the fused multiply-add result. This is useful when constructing safe lower bounds in interval arithmetic or when propagating rounding-safe underestimates.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T FMAAdjustDown( T a, T b, T c );
```

## Behavior

- Computes the fused multiply-add `FMA(a, b, c)` (i.e. a * b + c with single rounding when available) and then returns `NextDown` of that result.
- Provides a conservative lower bound for expressions of the form `a * b + c` and is intended for use in interval arithmetic and error propagation.
- The function is `constexpr` and can be evaluated at compile time when its arguments are constant expressions.

## Notes

- On platforms or in compile-time evaluation where an exact fused multiply-add is not available, the implementation falls back to an equivalent expression; the adjustment with `NextDown` still provides a conservative lower bound.
- If any operand or the computed result is NaN or infinite, the returned value follows IEEE floating-point semantics adjusted by `NextDown`.
- Use `FMAAdjustUp` when a conservative upper bound is required.

## Example

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::FMAAdjustDown;

    double a = 1.23456789012345;
    double b = 9.87654321098765;
    double c = 1e-12;

    double fma = std::fma( a, b, c );
    double adjusted = FMAAdjustDown( a, b, c );

    std::cout << "fma(a, b, c) = " << fma << '\n';
    std::cout << "FMAAdjustDown(a, b, c) = " << adjusted << " (conservative lower bound)" << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = 3.0;
constexpr double b = 4.0;
constexpr double c = 1.0;
constexpr double r = Harlinn::Math::FMAAdjustDown( a, b, c );
static_assert( r <= 13.0 );
```

## See also

- `FMAAdjustUp` — conservative upper bound for fused multiply-add.
- `NextUp`, `NextDown` — step to adjacent representable floating-point values.
- `Interval<T>` — interval arithmetic utilities that use adjusted operations.

---

Created for the Harlinn.Math library documentation.
