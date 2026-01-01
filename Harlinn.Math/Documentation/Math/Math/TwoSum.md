# TwoSum

Description

`TwoSum` computes the rounded sum of two floating-point numbers together with the exact rounding error using Dekker's TwoSum algorithm. The function returns a `CompensatedFloat` containing the rounded result `s` and the small correction `err` such that the exact mathematical sum is `s + err`.

Mathematical definition

Given two floating-point numbers \(a\) and \(b\), `TwoSum` produces

- a rounded result \(s = \operatorname{fl}(a + b)\), and
- an error term \(\delta\) such that

$$
a + b = s + \delta.
$$

One stable computation of the error uses the intermediate value \(\mathrm{delta} = s - a\) and computes

$$
\delta = (a - (s - \mathrm{delta})) + (b - \mathrm{delta}).
$$

Function signature (C++)

```cpp
template<typename FloatT>
    requires IsFloatingPoint<FloatT>
constexpr inline CompensatedFloat<FloatT> TwoSum( FloatT a, FloatT b )
```

Return value

Returns a `CompensatedFloat<FloatT>` where:

- `.v` (or `v`) is the rounded sum \(s\).
- `.err` (or `err`) is the rounding error \(\delta\) so that the exact sum is `v + err`.

Usage notes

- Use `TwoSum` when you need to preserve additional precision when adding two floating values, or as a building block for higher-accuracy summation and dot-product algorithms.
- Combining `TwoSum` with `CompensatedSum` or by explicitly propagating `err` terms yields a more accurate final result than naive accumulation.

Examples

Simple usage showing components and reconstructed exact sum:

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;
    using FloatT = double;

    FloatT a = 1e16;
    FloatT b = 1.0;

    auto res = TwoSum( a, b ); // CompensatedFloat<double>

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "rounded = " << res.v << "\n";
    std::cout << "error   = " << res.err << "\n";
    std::cout << "recon   = " << static_cast<double>( res ) << "\n"; // v + err

    // Verify mathematical identity
    double exact = a + b;
    std::cout << "exact   = " << exact << "\n";

    return 0;
}
```

Example interpretation

- For large-magnitude differences between `a` and `b`, the rounded `v` may lose the small term; `err` recovers that lost part so `v + err` matches the true sum.

See also

- `TwoProd` — compute product and rounding error
- `CompensatedSum` — Kahan summation for sequences
- `CompensatedFloat` — pair type storing value and error
