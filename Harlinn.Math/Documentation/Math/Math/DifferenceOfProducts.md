# DifferenceOfProducts

Description

`DifferenceOfProducts` computes the quantity

$$
a\cdot b - c\cdot d
$$

with reduced floating-point error by using FMA-based rearrangements. Instead of evaluating the expression as two independent products followed by a subtraction (which can lose low-order bits), the implementation forms an FMA to compute one product while subtracting the other, and corrects remaining rounding using another FMA. This reduces the final rounding error in many situations.

Mathematical definition

Given floating-point operands \(a, b, c, d\), the function computes an approximation \(r\) of the exact value

$$
R = a\,b - c\,d
$$

and attempts to minimize the rounding error so that

$$
R \approx r
$$

with a smaller error than the naive evaluation.

Function signature (C++)

```cpp
template <typename Ta, typename Tb, typename Tc, typename Td>
    requires IsFloatingPoint<Ta>&& IsFloatingPoint<Tb>&& IsFloatingPoint<Tc>&& IsFloatingPoint<Td>
constexpr inline auto DifferenceOfProducts( Ta a, Tb b, Tc c, Td d )
```

Implementation notes

- When FMA (`std::fma`) is available the function uses fused multiply-add to compute

  1. an initial difference using `FMA(a,b,-(c*d))`, and
  2. an error correction term computed from the subtraction used to form `c*d`.

- This yields a result equivalent to computing the exact difference and then rounding once, to the extent the hardware and `std::fma` allow.
- The function returns an arithmetic value (type deduced by `auto`) representing the corrected difference.

Usage notes

- Prefer `DifferenceOfProducts` when computing expressions of the form \(a\,b - c\,d\) where cancellation or mixed magnitudes may cause significant rounding error.
- It is most effective when the implementation maps `FMA` to a hardware fused multiply-add instruction.

Example

This example compares the naive evaluation `a*b - c*d` with `DifferenceOfProducts` for values that cause cancellation.

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;
    using FloatT = double;

    // Choose values that lead to cancellation in naive subtraction
    FloatT a = 1e16 + 1.0;
    FloatT b = 1.0;
    FloatT c = 1e8;
    FloatT d = 1e8;

    // Naive computation
    double naive = a * b - c * d;

    // Improved computation
    double improved = DifferenceOfProducts( a, b, c, d );

    // Exact reference (extended precision, computed here for illustration)
    long double exact = (long double)a * (long double)b - (long double)c * (long double)d;

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

- The `improved` result should show a much smaller error compared to `naive` for inputs where cancellation or rounding loss occurs.

See also

- `TwoProd`: compute product and its rounding error
- `TwoSum`: compute sum and its rounding error
- `InnerProduct`: accurate accumulation of multiple products
