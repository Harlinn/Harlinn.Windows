# SumOfProducts

Description

`SumOfProducts` computes the quantity

$$
a\cdot b + c\cdot d
$$

with reduced floating-point error by using FMA based rearrangements. Instead of evaluating the expression as two independent products followed by an addition (which can lose low-order bits), the implementation forms an FMA for one product and corrects the rounding of the other using another FMA. This reduces the final rounding error in many situations.

Mathematical definition

Given floating-point operands \(a, b, c, d\), the function computes an approximation \(r\) of the exact value

$$
R = a\,b + c\,d
$$

and attempts to minimize rounding so that

$$
R \approx r
$$

When FMA is available the implementation forms:

$$
p = a\,b + (c\,d)\quad\text{computed with FMA for minimal rounding}
$$

and applies a correction term that recovers the small rounding error associated with computing \(c\,d\).

Function signature (C++)

```cpp
template <typename Ta, typename Tb, typename Tc, typename Td>
    requires IsFloatingPoint<Ta>&& IsFloatingPoint<Tb>&& IsFloatingPoint<Tc>&& IsFloatingPoint<Td>
constexpr inline auto SumOfProducts( Ta a, Tb b, Tc c, Td d )
```

Return value

Returns an arithmetic value (type deduced by `auto`) representing the corrected sum of products. The returned value is typically of the common type of the operands and has smaller rounding error than the naive evaluation `a*b + c*d`.

Usage notes

- Prefer `SumOfProducts` when computing expressions of the form \(a\,b + c\,d\) where operands may have mixed magnitudes and naive evaluation can accumulate significant rounding error.
- The function is most effective when `FMA` maps to a hardware fused multiply-add instruction or when `std::fma` is available.

Example

The following example compares the naive evaluation with `SumOfProducts` for values that could produce rounding differences.

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;
    using FloatT = double;

    // Choose values that can produce rounding differences
    FloatT a = 1e16 + 1.0;
    FloatT b = 1.0;
    FloatT c = 1e8;
    FloatT d = 1e8 + 1.0;

    // Naive computation
    double naive = a * b + c * d;

    // Improved computation
    double improved = SumOfProducts( a, b, c, d );

    // Exact reference using extended precision for illustration
    long double exact = (long double)a * (long double)b + (long double)c * (long double)d;

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "naive    = " << naive << "\n";
    std::cout << "improved = " << improved << "\n";
    std::cout << "exact    = " << static_cast<double>( exact ) << "\n";
    std::cout << "naive error    = " << ( naive - static_cast<double>( exact ) ) << "\n";
    std::cout << "improved error = " << ( improved - static_cast<double>( exact ) ) << "\n";

    return 0;
}
```

Expected behavior

- The `improved` result should show a smaller error compared to `naive` for inputs where cancellation or rounding loss occurs.

See also:

- `TwoProd` : compute product and its rounding error
- `TwoSum` : compute sum and its rounding error
- `DifferenceOfProducts` : compute a*b - c*d with reduced error
- `InnerProduct` : accurate accumulation of multiple products
