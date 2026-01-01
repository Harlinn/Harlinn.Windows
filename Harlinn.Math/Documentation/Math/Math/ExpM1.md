# ExpM1

[Optimized basic math functions](Readme.md)/[Exponential functions](ExponentialFunctions.md)/`ExpM1`

## Summary

`ExpM1` computes `exp(x) - 1` with improved accuracy for small `x`. This avoids catastrophic cancellation when `x` is close to zero and the result is near zero. The function is `constexpr`-friendly and delegates to the library's `OpenLibM` helpers for well-defined compile-time behavior.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T ExpM1( T x ) noexcept;
```

## Behavior

- Returns `exp(x) - 1` computed in a numerically stable way for small `x`.
- For `float` the implementation calls `Math::Internal::OpenLibM::expm1f`; for `double` it calls `Math::Internal::OpenLibM::expm1` when available.
- Special values follow IEEE rules: `ExpM1(+inf) = +inf`, `ExpM1(-inf) = -1`, and `ExpM1(NaN) = NaN`.
- The function is `constexpr` and `noexcept` where applicable.

## Notes

- Prefer `ExpM1` instead of `Exp(x) - 1` when `x` is small (e.g. |x| << 1) to maintain precision.
- Use `Exp` when you need the full exponential value and `ExpM1` when the subtraction by 1 is required.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ExpM1;

    double small = 1e-8;
    double normal = 1.0;

    std::cout << std::setprecision(12);
    std::cout << "ExpM1(1e-8) = " << ExpM1( small ) << '\n';
    std::cout << "Exp(1e-8) - 1 = " << ( Harlinn::Math::Exp( small ) - 1.0 ) << '\n';

    std::cout << "ExpM1(1.0) = " << ExpM1( normal ) << '\n'; // exp(1)-1

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double v1 = Harlinn::Math::ExpM1( 0.0 );
static_assert( v1 == 0.0 );

// small x should produce a value close to x for tiny x
constexpr double v2 = Harlinn::Math::ExpM1( 1e-8 );
static_assert( v2 > 0.0 );
```

## See also

- `Exp` � computes e^x.
- `Exp2`, `Exp10` � exponentials with different bases.

---

Created for the Harlinn.Math library documentation.
