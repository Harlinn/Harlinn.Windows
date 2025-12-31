# JN

## Summary

`JN` computes the Bessel function of the first kind of integer order `n` for a floating-point argument `x`. The implementation delegates to the library's `OpenLibM` helpers and is `constexpr`-friendly when those helpers are available in constant evaluation contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T JN( int n, T x ) noexcept;
```

## Behavior

- Returns the value of the Bessel function of the first kind of order `n`, J_n(x), for integer order `n` and real argument `x`.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::jnf`; for `double` it delegates to `Math::Internal::OpenLibM::jn`.
- The function is `noexcept` and follows the underlying OpenLibM semantics for special values (NaN, infinities).
- For fixed `n` and large |x|, J_n(x) oscillates and its amplitude decays approximately like sqrt(2/(?|x|)).

## Notes

- Use `JN` when you need Bessel functions for arbitrary integer orders; `J0` and `J1` are provided for common special cases.
- For negative integer orders, J_{-n}(x) = (-1)^n * J_n(x) for integer n.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::JN;

    double x = 2.5;
    for ( int n = 0; n <= 4; ++n )
    {
        std::cout << "J" << n << "(" << x << ") = " << JN( n, x ) << '\n';
    }

    // Negative order example
    std::cout << "J-1(2.5) = " << JN( -1, x ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double j0 = Harlinn::Math::JN( 0, 0.0 );
static_assert( j0 == 1.0 );

constexpr double j1_at_1 = Harlinn::Math::JN( 1, 1.0 );
// J1(1) ~ 0.4400505857449335
static_assert( j1_at_1 > 0.4400505857 && j1_at_1 < 0.4400505858 );
```

## See also

- `J0`, `J1` — Bessel functions of the first kind for orders 0 and 1.
- `Y0`, `Y1`, `YN` — Bessel functions of the second kind.

---

Created for the Harlinn.Math library documentation.
