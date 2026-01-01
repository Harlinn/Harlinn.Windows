# LogisticCDF

Description

`LogisticCDF` computes the cumulative distribution function (CDF) of the Logistic distribution with zero location (mean) and scale parameter `s > 0`.

Mathematical definition

The Logistic CDF is given by

$$
F(x; s) = \frac{1}{1 + e^{-x/s}}\,,\quad s > 0
$$

Properties

- Domain: $x \in (-\infty, \infty)$
- Scale: $s > 0$. Larger `s` gives a wider (more spread out) distribution.
- Limit behavior: $\lim_{x\to -\infty}F(x;s)=0$ and $\lim_{x\to \infty}F(x;s)=1$.

Function signature (C++)

```cpp
template<typename FloatT>
    requires IsFloatingPoint<FloatT>
constexpr inline FloatT LogisticCDF( FloatT x, FloatT s )
```

Parameters

- `x`: point at which to evaluate the CDF
- `s`: scale parameter (must be positive)

Return value

The function returns the CDF value at `x` for the logistic distribution with scale `s`.

Numerical notes

The implementation uses the library's `Exp` function to compute the exponential. For very large magnitude values of `x/s` the result is numerically 0 or 1 as expected.

Examples

Basic usage (floating-point):

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;

    double s = 1.0; // scale

    std::cout << std::fixed << std::setprecision(6);
    for ( double x = -6.0; x <= 6.0; x += 1.0 )
    {
        double cdf = LogisticCDF( x, s );
        std::cout << "x=" << std::setw(5) << x << "  CDF=" << cdf << "\n";
    }

    return 0;
}
```

Example output (approximate):

```
x=-6  CDF=0.002472
x=-5  CDF=0.006693
x=-4  CDF=0.017986
x=-3  CDF=0.047426
x=-2  CDF=0.119203
x=-1  CDF=0.268941
x= 0  CDF=0.500000
x= 1  CDF=0.731059
x= 2  CDF=0.880797
x= 3  CDF=0.952574
x= 4  CDF=0.982014
x= 5  CDF=0.993307
x= 6  CDF=0.997527
```

Relationship to the PDF

The logistic probability density function (PDF) with scale `s` is

$$
f(x; s) = \frac{e^{-x/s}}{s\left(1 + e^{-x/s}\right)^2}\,.
$$

The CDF is the integral of the PDF and is implemented by `LogisticCDF` above.

See also

- `Logistic` � returns the Logistic PDF value at `x` (Harlinn::Math::Logistic)
