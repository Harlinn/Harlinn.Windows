# NewtonBisection

[Optimized basic math functions](Readme.md)/[Power and root finding functions](PowerFunctions.md)/`NewtonBisection`

Description

`NewtonBisection` finds a root of a scalar function using a hybrid of Newton's method and bisection to provide robustness and fast local convergence. The routine keeps a bracketing interval \([x_0, x_1]\) that contains a root, uses a Newton step when safe, and falls back to bisection when the Newton step leaves the bracket or is otherwise unreliable.

Mathematical formulation

Let \(f\) be a real-valued function with derivative \(f'\). Newton's iteration for a current guess \(x_n\) is:

$$
x_{n+1} = x_n - \frac{f(x_n)}{f'(x_n)}
$$

Bisection replaces the Newton step with the midpoint (or a robust linear approximation) when the Newton step would leave the current bracket or when the method is not converging fast enough.

Function signature (C++)

```cpp
template <typename Func, typename FloatT>
constexpr inline FloatT NewtonBisection( FloatT x0, FloatT x1, Func f, FloatT xEps = static_cast<FloatT>(1e-6), FloatT fEps = static_cast<FloatT>(1e-6) )
```

Requirements for `f`

`f` must be callable with a single `FloatT` argument and return a `std::pair<FloatT, FloatT>` where:

- `.first` is the function value \(f(x)\).
- `.second` is the derivative value \(f'(x)\) (or an approximation of it).

Parameters

- `x0`: left endpoint of the initial bracketing interval.
- `x1`: right endpoint of the initial bracketing interval.
- `f`: a callable returning `std::pair<FloatT,FloatT>` as described above.
- `xEps`: tolerance for the interval width. Stop when `x1 - x0 < xEps`.
- `fEps`: tolerance for the function value. Stop when `|f(x)| < fEps`.

Return value

Returns a `FloatT` approximation to a root of `f` inside the initial bracket. If the provided bracket does not contain a root the behavior is unspecified for that input: callers should supply a bracket where `f(x0)` and `f(x1)` have opposite signs where possible.

Algorithm notes

- The implementation initially forms an estimate for the midpoint using linear interpolation:

$$
x_{\text{mid}} = x_0 + (x_1 - x_0) \frac{-f(x_0)}{f(x_1) - f(x_0)}
$$

This accelerates convergence when the function is approximately linear on the interval.

- At each iteration the algorithm evaluates `f` at the candidate point. If the Newton step would leave the bracket or if convergence checks fail, a bisection step is used to shrink the bracket. The iteration stops when the interval width is below `xEps` or the absolute function value is below `fEps`.

- Using both Newton and bisection gives the method the local quadratic convergence of Newton's method when near a simple root and the global robustness of bisection when Newton fails.

Example

This example finds a root of \(f(x) = x^3 - 2x - 5\). The derivative is \(f'(x) = 3x^2 - 2\).

```cpp
#include <iostream>
#include <iomanip>
#include <utility>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;
    using FloatT = double;

    auto f = []( FloatT x ) -> std::pair<FloatT, FloatT>
    {
        // f(x) = x^3 - 2x - 5
        // f'(x) = 3x^2 - 2
        return { x * x * x - 2.0 * x - 5.0, 3.0 * x * x - 2.0 };
    };

    FloatT a = 1.0; // left bracket
    FloatT b = 3.0; // right bracket

    FloatT root = NewtonBisection( a, b, f, 1e-12, 1e-12 );

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "root = " << root << "\n";
    auto [fv, dv] = f( root );
    std::cout << "f(root) = " << fv << "\n";

    return 0;
}
```

Remarks

- Choose `xEps` and `fEps` according to the desired accuracy and the scale of `f`.
- Ensure `f` provides a reliable derivative, or supply a numerical derivative approximation inside `f` if an analytic derivative is not available.

See also:

- `DifferenceOfProducts` : accurate computation of differences of products used in robust discriminant evaluation
- `InnerProduct` : compensated dot product for sums of products
