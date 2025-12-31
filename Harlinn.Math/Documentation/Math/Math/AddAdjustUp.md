# AddAdjustUp

## Summary

`AddAdjustUp` returns the sum of two floating-point values adjusted upward to conservatively account for rounding error. It computes `NextUp(a + b)` which yields the smallest representable floating-point number strictly greater than the exact computed sum, providing a safe upper bound for numerical algorithms and interval arithmetic.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T AddAdjustUp( T a, T b );
```

## Behavior

- Computes the arithmetic sum `a + b` and then returns the next representable floating-point value greater than that sum using `NextUp`.
- Useful for producing conservative upper bounds when forming intervals or working with error propagation.
- The function is `constexpr` and can be evaluated at compile time when its arguments are constant expressions.

## Notes

- `AddAdjustUp` does not perform any special handling for NaN or infinities beyond the behavior of `NextUp` and the underlying floating-point addition. If `a + b` is infinite or NaN, the result follows IEEE floating-point semantics adjusted by `NextUp`.
- Use `AddAdjustDown` when a conservative lower bound is required.
- This helper is typically used together with interval types such as `Interval<T>` and other numeric utilities in the library.

## Example

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::AddAdjustUp;

    double a = 1.0e308;
    double b = 1.0e292; // small relative to a

    double adjusted = AddAdjustUp( a, b );
    std::cout << "a + b = " << ( a + b ) << '\n';
    std::cout << "AddAdjustUp(a, b) = " << adjusted << " (conservative upper bound)" << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = 1.0;
constexpr double b = 2.0;
constexpr double s = Harlinn::Math::AddAdjustUp( a, b );
static_assert( s >= 3.0 );
```

## See also

- `AddAdjustDown` — conservative lower bound for addition.
- `NextUp`, `NextDown` — functions that step to adjacent representable floating-point values.
- `Interval<T>::FromValueAndError` — uses adjusted operations to construct conservative intervals.

---

Created for the Harlinn.Math library documentation.
