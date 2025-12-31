# SubAdjustUp

## Summary

`SubAdjustUp` returns the result of subtracting two floating-point values adjusted upward to conservatively account for rounding error. It computes `NextUp(a - b)` which yields the smallest representable floating-point number strictly greater than the computed difference, providing a safe upper bound for numerical algorithms and interval arithmetic.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T SubAdjustUp( T a, T b );
```

## Behavior

- Computes the arithmetic difference `a - b` and then returns the next representable floating-point value greater than that difference using `NextUp`.
- Useful for producing conservative upper bounds when forming intervals or working with error propagation (for example when subtracting two estimates and you want a safe overestimate of the result).
- The function is `constexpr` and can be evaluated at compile time when its arguments are constant expressions.

## Notes

- `SubAdjustUp` is implemented in terms of `AddAdjustUp` by negating the subtrahend, but callers can use it directly for clarity.
- It does not perform special handling for NaN or infinities beyond the behavior of floating-point subtraction and `NextUp`.
- For conservative lower bounds of a subtraction use `SubAdjustDown`.

## Example

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SubAdjustUp;

    double a = 1.0e308;
    double b = 1.0e292; // small relative to a

    double diff = a - b;
    double adjusted = SubAdjustUp( a, b );
    std::cout << "a - b = " << diff << '\n';
    std::cout << "SubAdjustUp(a, b) = " << adjusted << " (conservative upper bound)" << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = 5.0;
constexpr double b = 3.0;
constexpr double s = Harlinn::Math::SubAdjustUp( a, b );
static_assert( s >= 2.0 );
```

## See also

- `SubAdjustDown` — conservative lower bound for subtraction.
- `AddAdjustUp`, `AddAdjustDown` — adjusted addition helpers.
- `NextUp`, `NextDown` — functions that step to adjacent representable floating-point values.
- `Interval<T>` — interval arithmetic utilities that use adjusted operations.

---

Created for the Harlinn.Math library documentation.
