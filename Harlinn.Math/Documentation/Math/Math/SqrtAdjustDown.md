# SqrtAdjustDown

## Summary

`SqrtAdjustDown` computes the square root of a floating-point value and then adjusts the result downward to conservatively account for rounding error. It returns `NextDown(Sqrt(a))`, producing the largest representable floating-point number strictly less than the computed square root. This is useful when constructing safe lower bounds in interval arithmetic or when guarding against overestimation due to floating-point rounding.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T SqrtAdjustDown( T a );
```

## Behavior

- Computes `Sqrt(a)` and returns `NextDown(Sqrt(a))`.
- The function attempts to return a conservative lower bound for the square root operation; if `a` is negative the behavior follows the underlying `Sqrt` semantics (typically NaN).
- If `a` is +infinity, the result is +infinity. If `a` is NaN the result is NaN.
- The function is `constexpr` and can be evaluated at compile time when the argument is a constant expression.

## Notes

- Use `SqrtAdjustDown` when you need a conservative lower bound for a square root operation (for example when computing the lower bound of an interval containing the true square root).
- For a conservative upper bound use `SqrtAdjustUp`.
- This helper is commonly used together with the `Interval<T>` helpers such as `Interval::FromValueAndError`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SqrtAdjustDown;

    double a = 2.0;
    double r = std::sqrt( a );
    double rDown = SqrtAdjustDown( a );

    std::cout << "std::sqrt(2.0) = " << r << '\n';
    std::cout << "SqrtAdjustDown(2.0) = " << rDown << " (conservative lower bound)" << '\n';

    // special case: zero
    std::cout << "SqrtAdjustDown(0.0) = " << SqrtAdjustDown( 0.0 ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s = Harlinn::Math::SqrtAdjustDown( 4.0 );
static_assert( s <= 2.0 );
```

## See also

- `SqrtAdjustUp` — conservative upper bound for square root.
- `NextUp`, `NextDown` — functions that step to adjacent representable floating-point values.
- `Interval<T>` — interval arithmetic utilities that use adjusted operations.

---

Created for the Harlinn.Math library documentation.
