# GaussianIntegral

## Summary

`GaussianIntegral` computes the integral of the Gaussian (normal) probability density function (PDF) between two bounds `x0` and `x1`, with mean `mu` and standard deviation `sigma`.

The function evaluates the definite integral

$$
\int_{x_0}^{x_1} \frac{1}{\sqrt{2\pi}\,\sigma} \exp\left(-\frac{(x-\mu)^2}{2\sigma^2}\right)\,dx
= \frac{1}{2}\left[\operatorname{erf}\left(\frac{\mu - x_0}{\sqrt{2}\,\sigma}\right) - \operatorname{erf}\left(\frac{\mu - x_1}{\sqrt{2}\,\sigma}\right)\right]
$$

where `erf` denotes the error function.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<typename FloatT>
    requires IsFloatingPoint<FloatT>
constexpr inline FloatT GaussianIntegral( FloatT x0, FloatT x1, FloatT mu = 0, FloatT sigma = 1 );
```

## Behavior

- Returns the probability mass of a normal distribution with mean `mu` and standard deviation `sigma` falling in the interval `[x0, x1]`.
- Uses the error function `std::erf` and the library's constants for `Sqrt2`.
- The function is `constexpr` and can be evaluated at compile time for constant inputs.

## Notes

- `sigma` should be positive; passing non-positive `sigma` yields undefined or non-meaningful results.
- The function returns values in the closed interval [0, 1] when `sigma > 0` and `x0 <= x1`.
- For `x0 > x1` the function returns a negative of the integral from `x1` to `x0` (consistent with definite integral sign convention).

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::GaussianIntegral;

    double x0 = -1.0;
    double x1 = 1.0;
    double mu = 0.0;
    double sigma = 1.0;

    double p = GaussianIntegral( x0, x1, mu, sigma );
    std::cout << "P(" << x0 << " <= X <= " << x1 << ") = " << p << '\n';
    // For standard normal this is approximately 0.682689

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double p = Harlinn::Math::GaussianIntegral( -1.0, 1.0 );
static_assert( p > 0.68 && p < 0.69 );
```

## See also

- `Gaussian` — evaluates the Gaussian PDF at a point.
- `Erf` / `std::erf` — error function used to compute the integral.

---

Created for the Harlinn.Math library documentation.
