# SubAdjustDown

## Summary

`SubAdjustDown` returns the result of subtracting two floating-point values adjusted downward to conservatively account for rounding error. It computes `NextDown(a - b)` which yields the largest representable floating-point number strictly less than the computed difference, providing a safe lower bound for numerical algorithms and interval arithmetic.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T SubAdjustDown( T a, T b );
```

## Behavior

- Computes the arithmetic difference `a - b` and then returns the next representable floating-point value less than that difference using `NextDown`.
- Useful for producing conservative lower bounds when forming intervals or working with error propagation (for example when subtracting two estimates and you want a safe underestimate of the result).
- The function is `constexpr` and can be evaluated at compile time when its arguments are constant expressions.

## Notes

- `SubAdjustDown` is implemented in terms of `AddAdjustDown` by negating the subtrahend, but callers can use it directly for clarity.
- It does not perform special handling for NaN or infinities beyond the behavior of floating-point subtraction and `NextDown`.
- For conservative upper bounds of a subtraction use `SubAdjustUp`.

## Example

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SubAdjustDown;

    double a = 1.0e308;
    double b = 1.0e292; // small relative to a

    double diff = a - b;
    double adjusted = SubAdjustDown( a, b );
    std::cout << "a - b = " << diff << '\n';
    std::cout << "SubAdjustDown(a, b) = " << adjusted << " (conservative lower bound)" << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = 5.0;
constexpr double b = 3.0;
constexpr double s = Harlinn::Math::SubAdjustDown( a, b );
static_assert( s <= 2.0 );
```

## See also

- `SubAdjustUp` — conservative upper bound for subtraction.
- `AddAdjustUp`, `AddAdjustDown` — adjusted addition helpers.
- `NextUp`, `NextDown` — functions that step to adjacent representable floating-point values.
- `Interval<T>` — interval arithmetic utilities that use adjusted operations.

---

Created for the Harlinn.Math library documentation.
