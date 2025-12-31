# MulAdjustDown

## Summary

`MulAdjustDown` returns the product of two floating-point values adjusted downward to conservatively account for rounding error. It computes `NextDown(a * b)` which yields the largest representable floating-point number strictly less than the computed product, providing a safe lower bound for numerical algorithms and interval arithmetic.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T MulAdjustDown( T a, T b );
```

## Behavior

- Computes the arithmetic product `a * b` and then returns the next representable floating-point value less than that product using `NextDown`.
- Useful for producing conservative lower bounds when forming intervals or working with error propagation.
- The function is `constexpr` and can be evaluated at compile time when its arguments are constant expressions.

## Notes

- `MulAdjustDown` does not perform special handling for NaN or infinities beyond the behavior of `NextDown` and the underlying floating-point multiplication. If `a * b` is infinite or NaN, the result follows IEEE floating-point semantics adjusted by `NextDown`.
- For a conservative upper bound use `MulAdjustUp`.
- This helper is typically used together with interval types such as `Interval<T>` and other numeric utilities in the library.

## Example

Runtime example:

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::MulAdjustDown;

    double a = 1.23456789012345e150;
    double b = 9.87654321098765e-10;

    double prod = a * b;
    double adjusted = MulAdjustDown( a, b );

    std::cout << "a * b = " << prod << '\n';
    std::cout << "MulAdjustDown(a, b) = " << adjusted << " (conservative lower bound)" << '\n';

    // special cases
    double ninf = -std::numeric_limits<double>::infinity();
    std::cout << "MulAdjustDown(-inf, 2.0) = " << MulAdjustDown( ninf, 2.0 ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = 3.0;
constexpr double b = 4.0;
constexpr double p = Harlinn::Math::MulAdjustDown( a, b );
static_assert( p <= 12.0 );
```

## See also

- `MulAdjustUp` — conservative upper bound for multiplication.
- `NextUp`, `NextDown` — functions that step to adjacent representable floating-point values.
- `Interval<T>::FromValueAndError` — uses adjusted operations to construct conservative intervals.

---

Created for the Harlinn.Math library documentation.
