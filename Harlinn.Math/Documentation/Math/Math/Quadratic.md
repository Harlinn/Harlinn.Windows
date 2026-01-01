# Quadratic

[Optimized basic math functions](Readme.md)/[Power and root finding functions](PowerFunctions.md)/`Quadratic`

Description

`Quadratic` solves the quadratic equation

$$
a x^2 + b x + c = 0
$$

for coefficients \(a\), \(b\), \(c\) of a floating-point type. The function computes the roots in a numerically stable way and returns `true` if real roots exist and `false` otherwise.

Mathematical background

The standard roots of the quadratic are given by the quadratic formula:

$$
x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}
$$

The discriminant is

$$
\Delta = b^2 - 4 a c
$$

and real roots exist when \(\Delta \ge 0\).

Numerical notes

To reduce rounding error when computing the discriminant and subsequent roots, the implementation uses compensated arithmetic and FMA-assisted helpers where available. In particular the discriminant is computed via `DifferenceOfProducts(b, b, 4*a, c)` to reduce cancellation errors when \(b^2\) and \(4ac\) are close in magnitude. The root computation uses a stable formulation to avoid loss of significance in the subtraction of nearly equal quantities.

Function signature (C++)

```cpp
template <typename FloatT, typename... T>
    requires IsFloatingPoint<FloatT>
constexpr inline bool Quadratic( FloatT a, FloatT b, FloatT c, FloatT* t0, FloatT* t1 )
```

Parameters:

- `a`: coefficient of \(x^2\).
- `b`: coefficient of \(x\).
- `c`: constant term.
- `t0`: pointer to receive the first root.
- `t1`: pointer to receive the second root.

Return value:

- `true` if real roots were found (roots stored in `t0` and `t1`), otherwise `false`.

Usage notes:

- If `a` is zero the function falls back to a linear solution for \(bx + c = 0\).
- The function orders the returned roots so that `*t0 <= *t1`.
- For improved discriminant accuracy the implementation uses `DifferenceOfProducts` which leverages FMA when available.

Examples

1) Two distinct real roots:

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;
    using FloatT = double;

    FloatT a = 1.0;
    FloatT b = -3.0;
    FloatT c = 2.0; // roots at x=1 and x=2

    FloatT r0, r1;
    bool hasRoots = Quadratic<FloatT>( a, b, c, &r0, &r1 );

    std::cout << std::fixed << std::setprecision(17);
    if ( hasRoots )
    {
        std::cout << "roots: " << r0 << ", " << r1 << "\n";
    }
    else
    {
        std::cout << "no real roots\n";
    }

    return 0;
}
```

2) Repeated root (discriminant zero):

```cpp
// a = 1, b = -2, c = 1 -> single root x = 1
FloatT a = 1.0, b = -2.0, c = 1.0;
FloatT r0, r1;
if ( Quadratic( a, b, c, &r0, &r1 ) )
    // r0 == r1 == 1
```

3) No real roots:

```cpp
// a = 1, b = 0, c = 1 -> discriminant < 0
FloatT a = 1.0, b = 0.0, c = 1.0;
FloatT r0, r1;
if ( !Quadratic( a, b, c, &r0, &r1 ) )
    // handle complex roots or report none
```

References

- The implementation uses `DifferenceOfProducts` to compute the discriminant more accurately:
  `b^2 - 4*a*c = DifferenceOfProducts(b, b, 4*a, c)`.
- See `TwoProd`, `TwoSum`, and `CompensatedFloat` for the low-level building blocks used for compensated arithmetic.
