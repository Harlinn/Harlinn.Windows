# DivAdjustUp

## Summary

`DivAdjustUp` returns the result of dividing two floating-point values adjusted upward to conservatively account for rounding error. It computes `NextUp(a / b)` which yields the smallest representable floating-point number strictly greater than the computed quotient, providing a safe upper bound for numerical algorithms and interval arithmetic.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T DivAdjustUp( T a, T b );
```

## Behavior

- Computes the arithmetic quotient `a / b` and then returns the next representable floating-point value greater than that quotient using `NextUp`.
- Useful for producing conservative upper bounds when forming intervals or working with error propagation.
- The function is `constexpr` and can be evaluated at compile time when its arguments are constant expressions.

## Notes

- `DivAdjustUp` does not perform special handling for NaN or infinities beyond the behavior of `NextUp` and the underlying floating-point division. If `a / b` is infinite or NaN, the result follows IEEE floating-point semantics adjusted by `NextUp`.
- When dividing by an interval that straddles zero, interval division returns an interval representing all real numbers; use interval-aware helpers where appropriate.
- For a conservative lower bound use `DivAdjustDown`.

## Example

Runtime example:

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::DivAdjustUp;

    double a = 10.0;
    double b = 3.0;

    double q = a / b;
    double adjusted = DivAdjustUp( a, b );

    std::cout << "a / b = " << q << '\n';
    std::cout << "DivAdjustUp(a, b) = " << adjusted << " (conservative upper bound)" << '\n';

    // division by zero behavior
    double inf = std::numeric_limits<double>::infinity();
    std::cout << "DivAdjustUp(+inf, 2.0) = " << DivAdjustUp( inf, 2.0 ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = 6.0;
constexpr double b = 2.0;
constexpr double qUp = Harlinn::Math::DivAdjustUp( a, b );
static_assert( qUp >= 3.0 );
```

## See also

- `DivAdjustDown` — conservative lower bound for division.
- `NextUp`, `NextDown` — functions that step to adjacent representable floating-point values.
- `Interval<T>::operator/` — interval-aware division helpers that use adjusted operations.

---

Created for the Harlinn.Math library documentation.
