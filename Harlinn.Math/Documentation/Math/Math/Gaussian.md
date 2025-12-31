# Gaussian

## Summary

`Gaussian` evaluates the Gaussian (normal) probability density function (PDF) at a point `x` with mean `mu` and standard deviation `sigma`.

The function implements the PDF

$$
f(x;\mu,\sigma)=\frac{1}{\sqrt{2\pi}\,\sigma}\n\exp\left(-\frac{(x-\mu)^2}{2\sigma^2}\right)
$$

and is defined in `Harlinn::Math` (header: `Harlinn.Math\include\Harlinn\Math\Math.h`). The implementation uses `FastExp` for the exponential term and `Sqrt`/`Sqr` helpers from the library.

## Declaration

```cpp
template<typename FloatT>
    requires IsFloatingPoint<FloatT>
constexpr inline FloatT Gaussian( FloatT x, FloatT mu = 0, FloatT sigma = 1 );
```

## Behavior

- Computes the Gaussian PDF value for the scalar `x`, parameterized by mean `mu` and standard deviation `sigma`.
- Returns a value of the same floating-point type as the inputs.
- The function is `constexpr` and can be evaluated at compile time for constant arguments.
- The implementation is numerically efficient and uses the library's `FastExp` for performance-sensitive scenarios. For maximum accuracy use `std::exp`-based implementations if required.

## Notes

- By convention `sigma` should be positive. Passing `sigma <= 0` produces undefined or non-meaningful results.
- For performance-sensitive code paths where many evaluations are required, `Gaussian` is optimized via `FastExp` and other lightweight helpers.
- The function returns the PDF value; it does not perform normalization across a sampled domain — the PDF already integrates to 1 over the real line when `sigma > 0`.

## Example

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Gaussian;

    double x = 0.5;
    double mu = 0.0;
    double sigma = 1.0;

    double pdf = Gaussian( x, mu, sigma );
    std::cout << "Gaussian(" << x << ", mu=" << mu << ", sigma=" << sigma << ") = " << pdf << '\n';

    // Example: evaluate standard normal at several points
    for ( double v : { -2.0, -1.0, 0.0, 1.0, 2.0 } )
    {
        std::cout << "N(0,1) pdf(" << v << ") = " << Gaussian( v ) << '\n';
    }

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double val = Harlinn::Math::Gaussian( 0.0, 0.0, 1.0 );
// val ~= 1 / sqrt(2*pi) ~ 0.3989422804
static_assert( val > 0.398 && val < 0.399 );
```

## See also

- `FastExp` — fast exponential approximation used by `Gaussian`.
- `Sqrt`, `Sqr` — helpers used in the implementation.
- `GaussianIntegral` — helpers for integrating Gaussian PDF over intervals.

---

Created for the Harlinn.Math library documentation.
