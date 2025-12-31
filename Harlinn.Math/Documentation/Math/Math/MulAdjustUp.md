# MulAdjustUp

## Summary

`MulAdjustUp` returns the product of two floating-point values adjusted upward to conservatively account for rounding error. It computes `NextUp(a * b)` which yields the smallest representable floating-point number strictly greater than the computed product, providing a safe upper bound for numerical algorithms and interval arithmetic.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T MulAdjustUp( T a, T b );
```

## Behavior

- Computes the arithmetic product `a * b` and then returns the next representable floating-point value greater than that product using `NextUp`.
- Useful for producing conservative upper bounds when forming intervals or working with error propagation.
- The function is `constexpr` and can be evaluated at compile time when its arguments are constant expressions.

## Notes

- `MulAdjustUp` does not perform special handling for NaN or infinities beyond the behavior of `NextUp` and the underlying floating-point multiplication. If `a * b` is infinite or NaN, the result follows IEEE floating-point semantics adjusted by `NextUp`.
- For a conservative lower bound use `MulAdjustDown`.
- This helper is typically used together with interval types such as `Interval<T>` and other numeric utilities in the library.

## Example

Runtime example:

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::MulAdjustUp;

    double a = 1.23456789012345e150;
    double b = 9.87654321098765e-10;

    double prod = a * b;
    double adjusted = MulAdjustUp( a, b );

    std::cout << "a * b = " << prod << '\n';
    std::cout << "MulAdjustUp(a, b) = " << adjusted << " (conservative upper bound)" << '\n';

    // special cases
    double inf = std::numeric_limits<double>::infinity();
    std::cout << "MulAdjustUp(+inf, 2.0) = " << MulAdjustUp( inf, 2.0 ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = 3.0;
constexpr double b = 4.0;
constexpr double p = Harlinn::Math::MulAdjustUp( a, b );
static_assert( p >= 12.0 );
```

## See also

- `MulAdjustDown` — conservative lower bound for multiplication.
- `NextUp`, `NextDown` — functions that step to adjacent representable floating-point values.
- `Interval<T>::FromValueAndError` — uses adjusted operations to construct conservative intervals.

---

Created for the Harlinn.Math library documentation.
