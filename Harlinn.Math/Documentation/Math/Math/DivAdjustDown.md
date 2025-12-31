# DivAdjustDown

## Summary

`DivAdjustDown` returns the result of dividing two floating-point values adjusted downward to conservatively account for rounding error. It computes `NextDown(a / b)` which yields the largest representable floating-point number strictly less than the computed quotient, providing a safe lower bound for numerical algorithms and interval arithmetic.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T DivAdjustDown( T a, T b );
```

## Behavior

- Computes the arithmetic quotient `a / b` and then returns the next representable floating-point value less than that quotient using `NextDown`.
- Useful for producing conservative lower bounds when forming intervals or working with error propagation.
- The function is `constexpr` and can be evaluated at compile time when its arguments are constant expressions.

## Notes

- `DivAdjustDown` does not perform special handling for NaN or infinities beyond the behavior of `NextDown` and the underlying floating-point division. If `a / b` is infinite or NaN, the result follows IEEE floating-point semantics adjusted by `NextDown`.
- When dividing by an interval that straddles zero, interval division returns an interval representing all real numbers; use interval-aware helpers where appropriate.
- For a conservative upper bound use `DivAdjustUp`.

## Example

Runtime example:

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::DivAdjustDown;

    double a = 10.0;
    double b = 3.0;

    double q = a / b;
    double adjusted = DivAdjustDown( a, b );

    std::cout << "a / b = " << q << '\n';
    std::cout << "DivAdjustDown(a, b) = " << adjusted << " (conservative lower bound)" << '\n';

    // division by zero behavior
    double ninf = -std::numeric_limits<double>::infinity();
    std::cout << "DivAdjustDown(-inf, 2.0) = " << DivAdjustDown( ninf, 2.0 ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = 6.0;
constexpr double b = 2.0;
constexpr double qDown = Harlinn::Math::DivAdjustDown( a, b );
static_assert( qDown <= 3.0 );
```

## See also

- `DivAdjustUp` — conservative upper bound for division.
- `NextUp`, `NextDown` — functions that step to adjacent representable floating-point values.
- `Interval<T>::operator/` — interval-aware division helpers that use adjusted operations.

---

Created for the Harlinn.Math library documentation.
