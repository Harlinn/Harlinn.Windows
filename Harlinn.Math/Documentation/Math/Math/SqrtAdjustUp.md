# SqrtAdjustUp

## Summary

`SqrtAdjustUp` computes the square root of a floating-point value and then adjusts the result upward to conservatively account for rounding error. It returns `NextUp(Sqrt(a))`, producing the smallest representable floating-point number strictly greater than the computed square root. This is useful when constructing safe upper bounds in interval arithmetic or when guarding against underestimation due to floating-point rounding.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T SqrtAdjustUp( T a );
```

## Behavior

- Computes `Sqrt(a)` and returns `NextUp(Sqrt(a))`.
- If `a` is negative the behavior follows the underlying `Sqrt` semantics (typically NaN).
- If `a` is +infinity, the result is +infinity. If `a` is NaN the result is NaN.
- The function is `constexpr` and can be evaluated at compile time when the argument is a constant expression.

## Notes

- Use `SqrtAdjustUp` when you need a conservative upper bound for a square root operation (for example when computing the upper bound of an interval containing the true square root).
- For a conservative lower bound use `SqrtAdjustDown`.
- This helper is commonly used together with the `Interval<T>` helpers such as `Interval::FromValueAndError`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SqrtAdjustUp;

    double a = 2.0;
    double r = std::sqrt( a );
    double rUp = SqrtAdjustUp( a );

    std::cout << "std::sqrt(2.0) = " << r << '\n';
    std::cout << "SqrtAdjustUp(2.0) = " << rUp << " (conservative upper bound)" << '\n';

    // special case: infinity
    double inf = std::numeric_limits<double>::infinity();
    std::cout << "SqrtAdjustUp(+inf) = " << SqrtAdjustUp( inf ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s = Harlinn::Math::SqrtAdjustUp( 4.0 );
static_assert( s >= 2.0 );
```

## See also

- `SqrtAdjustDown` — conservative lower bound for square root.
- `NextUp`, `NextDown` — functions that step to adjacent representable floating-point values.
- `Interval<T>` — interval arithmetic utilities that use adjusted operations.

---

Created for the Harlinn.Math library documentation.
