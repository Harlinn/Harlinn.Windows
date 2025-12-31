# Logistic

## Summary

`Logistic` evaluates the probability density function (PDF) of the logistic distribution at a point `x` with scale parameter `s`.

The logistic PDF is

$$
f(x; s)=\frac{e^{-x/s}}{s\left(1+e^{-x/s}\right)^2}
$$

(For a location parameter (mean) `\mu` a shifted form `f(x;\mu,s)=f(x-\mu;s)` is used.)

(Defined in `Harlinn::Math`, header: `Harlinn.Math\\include\\Harlinn\\Math\\Math.h`.)

## Declaration

```cpp
template<typename FloatT>
    requires IsFloatingPoint<FloatT>
constexpr inline FloatT Logistic( FloatT x, FloatT s );
```

There is also the cumulative distribution function helper `LogisticCDF` declared as:

```cpp
template<typename FloatT>
    requires IsFloatingPoint<FloatT>
constexpr inline FloatT LogisticCDF( FloatT x, FloatT s );
```

## Behavior

- `Logistic(x, s)` returns the value of the logistic PDF at `x` with scale `s`.
- `s` (scale) should be positive; passing non-positive `s` yields undefined or non-meaningful results.
- The function is `constexpr` and can be evaluated at compile time for constant inputs.

## Notes

- The logistic distribution is similar in shape to the normal distribution but has heavier tails.
- The corresponding CDF is

$$
F(x; s)=\frac{1}{1+e^{-x/s}}
$$

and is provided by `LogisticCDF`.

- The PDF integrates to 1 over the real line for `s>0`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Logistic;
    using Harlinn::Math::LogisticCDF;

    double x = 0.5;
    double s = 1.0; // scale

    double pdf = Logistic( x, s );
    double cdf = LogisticCDF( x, s );

    std::cout << "Logistic PDF at " << x << " (s=" << s << ") = " << pdf << '\n';
    std::cout << "Logistic CDF at " << x << " (s=" << s << ") = " << cdf << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double p = Harlinn::Math::Logistic( 0.0, 1.0 );
static_assert( p > 0 );
```

## See also

- `LogisticCDF` — cumulative distribution function for the logistic distribution.
- `Gaussian` / `GaussianIntegral` — normal distribution helpers.

---

Created for the Harlinn.Math library documentation.
