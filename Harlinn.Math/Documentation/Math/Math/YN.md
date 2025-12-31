# YN

## Summary

`YN` computes the Bessel function of the second kind (Neumann function) of integer order `n` for a floating-point argument `x`. The implementation delegates to the library's `OpenLibM` helpers and is `constexpr`-friendly when those helpers are available in constant-evaluation contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T YN( int n, T x ) noexcept;
```

## Behavior

- Returns the value of the Bessel function of the second kind of order `n`, `Y_n(x)`, for integer order `n` and real argument `x` (typically `x > 0` in the real domain).
- For `float` the implementation delegates to `Math::Internal::OpenLibM::ynf`; for `double` it delegates to `Math::Internal::OpenLibM::yn`.
- The function is `noexcept` and follows the underlying `OpenLibM` semantics for special values (NaN, infinities) and domain errors.
- `Y_n(x)` is singular at `x = 0` (it tends to ±infinity depending on the order) and oscillates for large `x` with amplitude decaying roughly as `sqrt(2/(?|x|))`.
- For negative integer order the relation `Y_{-n}(x) = (-1)^n * Y_n(x)` holds for integer `n` (up to sign conventions of underlying implementation).

## Notes

- `YN` is used with `J_n` when forming general solutions to cylindrical wave problems; `YN` provides the independent solution that is singular at the origin.
- Use `J0`, `J1`, `Y0`, and `Y1` for common low-order special cases when available.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::YN;

    double x = 2.5;
    for ( int n = 0; n <= 4; ++n )
    {
        std::cout << "Y" << n << "(" << x << ") = " << YN( n, x ) << '\n';
    }

    // Negative order example
    std::cout << "Y-1(" << x << ") = " << YN( -1, x ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

// Use positive arguments; YN is singular at 0
constexpr double y0_at_1 = Harlinn::Math::YN( 0, 1.0 );
// Y0(1) ~ 0.08825696421567697
static_assert( y0_at_1 > 0.0882569642156769 && y0_at_1 < 0.0882569642156771 );

constexpr double y1_at_1 = Harlinn::Math::YN( 1, 1.0 );
// Y1(1) ~ -0.7812128213002887
static_assert( y1_at_1 > -0.78121282130029 && y1_at_1 < -0.78121282130028 );
```

## See also

- `Y0`, `Y1` — Bessel functions of the second kind for orders 0 and 1.
- `J0`, `J1`, `JN` — Bessel functions of the first kind.

---

Created for the Harlinn.Math library documentation.
