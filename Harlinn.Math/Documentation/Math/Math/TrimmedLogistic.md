# TrimmedLogistic

Description

`TrimmedLogistic` returns the probability density function (PDF) of the Logistic distribution with scale parameter `s > 0` trimmed (restricted) to an interval `[a, b]` and renormalized so the area under the PDF on `[a,b]` is 1.

Mathematical definition

Let the standard logistic PDF and CDF with scale `s` (and zero location) be

$$
f(x; s) = \frac{e^{-x/s}}{s\left(1 + e^{-x/s}\right)^2},
\qquad
F(x; s) = \frac{1}{1 + e^{-x/s}}\,.
$$

The trimmed (truncated) logistic PDF on the interval $[a,b]$ is

$$
f_{[a,b]}(x; s) = \begin{cases}
\dfrac{f(x; s)}{F(b; s) - F(a; s)}, & x \in [a,b],\\[8pt]
0, & \text{otherwise.}
\end{cases}
$$

The denominator is the normalization constant equal to the probability mass of the original logistic distribution inside $[a,b]$.

Function signature (C++)

```cpp
template<typename FloatT>
    requires IsFloatingPoint<FloatT>
constexpr inline FloatT TrimmedLogistic( FloatT x, FloatT s, FloatT a, FloatT b )
```

Parameters

- `x`: point at which to evaluate the trimmed PDF
- `s`: scale parameter (must be positive)
- `a`: lower trimming bound
- `b`: upper trimming bound

Return value

Returns the trimmed (renormalized) logistic PDF value at `x`.

Numerical notes

- If `F(b; s) - F(a; s)` is zero (for extremely small intervals or numerically identical `a` and `b`), the function is ill-conditioned; callers should avoid zero-width trimming or handle the degenerate case separately.
- The implementation uses the library `Logistic` and `LogisticCDF` helpers for PDF and CDF evaluation respectively.

Examples

Basic usage:

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;

    double s = 1.0;        // scale
    double a = -1.0;       // lower bound
    double b = 2.0;        // upper bound

    std::cout << std::fixed << std::setprecision(6);
    for ( double x = -2.0; x <= 4.0; x += 0.5 )
    {
        double pdf = TrimmedLogistic( x, s, a, b );
        std::cout << "x=" << std::setw(5) << x << "  TrimmedPDF=" << pdf << "\n";
    }
    return 0;
}
```

Example interpretation

- Values of `x` outside `[a,b]` produce `0`.
- Values inside `[a,b]` give the logistic PDF scaled up by dividing by `F(b;s)-F(a;s)`.

See also

- `Logistic` — logistic PDF (Harlinn::Math::Logistic)
- `LogisticCDF` — logistic CDF (Harlinn::Math::LogisticCDF)
