# TwoProd

Description

`TwoProd` computes the floating-point product of two numbers together with the exact rounding error using a fused-multiply-add (FMA) based technique. The function returns a `CompensatedFloat` containing the rounded product `p` and the small correction `err` such that the exact mathematical product is `p + err`.

Mathematical definition

Given two floating-point numbers \(a\) and \(b\), `TwoProd` produces

- a rounded result \(p = \operatorname{fl}(a \cdot b)\), and
- an error term \(\varepsilon\) such that

$$
a \cdot b = p + \varepsilon.
$$

When hardware FMA is available (or `std::fma` is used), the error can be computed as

$$
\varepsilon = \operatorname{fma}(a, b, -p).
$$

Function signature (C++)

```cpp
template<typename FloatT>
    requires IsFloatingPoint<FloatT>
constexpr inline CompensatedFloat<FloatT> TwoProd( FloatT a, FloatT b )
```

Return value

Returns a `CompensatedFloat<FloatT>` where:

- `.v` (or `v`) is the rounded product \(p\).
- `.err` (or `err`) is the rounding error \(\varepsilon\) so that the exact product is `v + err`.

Usage notes

- `TwoProd` is useful when building more accurate dot-products, inner products, or polynomial evaluation routines where preserving low-order bits of products improves final accuracy.
- When FMA is available it yields a very accurate error term in a single operation; otherwise the implementation can emulate the same using standard operations but with less efficiency.

Examples

Simple usage showing components and reconstructed exact product:

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;
    using FloatT = double;

    FloatT a = 1e16 + 1.0;
    FloatT b = 1e-16;

    auto res = TwoProd( a, b ); // CompensatedFloat<double>

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "rounded = " << res.v << "\n";
    std::cout << "error   = " << res.err << "\n";
    std::cout << "recon   = " << static_cast<double>( res ) << "\n"; // v + err

    // Verify mathematical identity
    double exact = a * b;
    std::cout << "exact   = " << exact << "\n";

    return 0;
}
```

Example interpretation

- For operands where significant cancellation or loss of low-order bits occurs, `err` recovers the missing contribution so `v + err` matches the true product within the limits of the floating-point format.

See also

- `TwoSum`: sum with error term
- `CompensatedFloat`: pair type storing value and error
- `InnerProduct` / `TwoProd` based accumulation for accurate dot-products
