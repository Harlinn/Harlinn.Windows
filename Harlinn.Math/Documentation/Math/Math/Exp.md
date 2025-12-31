# Exp

## Summary

`Exp` computes the exponential function e^x (where e is Euler's number, approximately 2.71828) for floating-point inputs. The function is `constexpr`-friendly and delegates to the library's `OpenLibM` helpers for well-defined compile-time behavior.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Exp( T x ) noexcept;
```

## Behavior

- Returns `e` raised to the power `x` (mathematically e^x).
- For `float` the implementation calls `Math::Internal::OpenLibM::expf` and for `double` it calls `Math::Internal::OpenLibM::exp` to provide constexpr-capable and platform-consistent behavior.
- Special values follow IEEE rules: `Exp(+inf) = +inf`, `Exp(-inf) = 0`, and `Exp(NaN) = NaN`.
- The function is `constexpr` and `noexcept` where applicable.

## Notes

- Use `Exp` when you need a constexpr-capable exponential function with consistent semantics across compile-time and runtime.
- For `exp(x) - 1` with small `x` prefer `ExpM1` for improved numerical accuracy.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Exp;

    double a = 1.0;
    double b = 0.0;
    double c = -1.0;

    std::cout << "Exp(1.0) = " << Exp( a ) << '\n'; // e (~2.7182818)
    std::cout << "Exp(0.0) = " << Exp( b ) << '\n'; // 1.0
    std::cout << "Exp(-1.0) = " << Exp( c ) << '\n';// ~0.367879

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double e = Harlinn::Math::Exp( 1.0 );
static_assert( e > 2.718281 && e < 2.718282 );

constexpr double one = Harlinn::Math::Exp( 0.0 );
static_assert( one == 1.0 );
```

## See also

- `ExpM1` — computes `exp(x) - 1` with better accuracy for small `x`.
- `Exp2`, `Exp10` — exponential functions with different bases (2 and 10 respectively).

---

Created for the Harlinn.Math library documentation.
