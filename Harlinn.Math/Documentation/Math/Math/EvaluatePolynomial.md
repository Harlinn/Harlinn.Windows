# EvaluatePolynomial

[Optimized basic math functions](Readme.md)/[Power and root finding functions](PowerFunctions.md)/`EvaluatePolynomial`

## Summary

`EvaluatePolynomial` evaluates a polynomial at a given point using Horner's method. It is implemented as a `constexpr` template so it can be used at compile time when coefficients and the evaluation point are constant expressions.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template <ArithmeticType T, ArithmeticType C>
constexpr inline T EvaluatePolynomial( T t, C c );

template <ArithmeticType T, ArithmeticType C, ArithmeticType ... Args>
constexpr inline T EvaluatePolynomial( T t, C c, Args... remaining );
```

## Behavior

- Evaluates a polynomial with coefficients provided as argument pack in descending order of powers using Horner's method.
- For a call `EvaluatePolynomial(t, c0, c1, c2, ..., cn)` the value computed is:
  c0 + t*(c1 + t*(c2 + ... + t*(cn)...)).
- Works for any arithmetic types for `t` and coefficients; the return type is the same as `t`.
- The implementation uses `FMA` internally when appropriate to reduce rounding error when available.
- The function is `constexpr` so it can be used in compile-time contexts.

## Notes

- Prefer Horner's method for numerical stability and performance: it reduces the number of multiplications and additions to evaluate a polynomial.
- When coefficients are known at compile time the compiler can (and will typically) inline and optimize the expression.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h"

int main()
{
    using Harlinn::Math::EvaluatePolynomial;

    // Evaluate p(t) = 1 + 2*t + 3*t^2 + 4*t^3 at t = 2
    double t = 2.0;
    double value = EvaluatePolynomial( t, 1.0, 2.0, 3.0, 4.0 );
    // Expected: 1 + 2*2 + 3*4 + 4*8 = 1 + 4 + 12 + 32 = 49
    std::cout << "p(2) = " << value << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

// Evaluate q(t) = 3 + 4*t + 5*t^2 at compile-time for t = 1.5
constexpr double q = Harlinn::Math::EvaluatePolynomial( 1.5, 3.0, 4.0, 5.0 );
static_assert( q > 3.0 );
```

## See also

- `FMA` — fused multiply-add helper used by polynomial evaluation.
- `FastPow` — compile-time integer power helper.
- `EvaluatePolynomial` complements `FastPow` when coefficients are known and Horner's method is preferred.

---

Created for the Harlinn.Math library documentation.
