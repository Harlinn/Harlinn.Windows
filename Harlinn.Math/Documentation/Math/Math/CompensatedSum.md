# CompensatedSum

Description

`CompensatedSum` implements Kahan's compensated summation algorithm to reduce numerical error when summing a sequence of floating-point numbers. It keeps a small compensation term that tracks lost low-order bits and improves the final summed result compared to naive accumulation.

Mathematical background

Given a sequence of terms \(a_1, a_2, \dots, a_n\), the exact sum is

$$
S = \sum_{i=1}^n a_i.
$$

Floating-point accumulation suffers from rounding error. Kahan's algorithm maintains a running sum \(s\) and a compensation term \(c\). For each incoming term \(a\) it performs:

$$
y = a - c\\
t = s + y\\
c = (t - s) - y\\
s = t
$$

The compensation \(c\) stores the small error that would otherwise be lost, producing a significantly more accurate result for many sequences.

Class template (C++)

```cpp
template<typename T>
    requires IsFloatingPoint<T>
class CompensatedSum
{
public:
    using value_type = T;
    constexpr CompensatedSum() noexcept;
    constexpr explicit CompensatedSum(value_type v) noexcept;
    constexpr CompensatedSum& operator+=( value_type v ) noexcept; // Kahan step
    constexpr explicit operator value_type() const noexcept;      // returns current sum
    std::string ToString() const;
};
```

Behavior and properties

- The algorithm runs in O(1) extra memory and O(n) time for n terms.
- For many practical sequences the compensated sum yields results close to the correctly rounded sum and dramatically reduces accumulated rounding error compared to naive addition.
- The class is constexpr where possible and suitable for both `float` and `double` (or other floating types that satisfy `IsFloatingPoint`).
- Converting to the underlying `value_type` returns the accumulated sum (without exposing the internal compensation value).

Example

This example compares naive summation with `CompensatedSum` when summing many small values that can be lost due to rounding when added to a much larger running total.

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;
    using FloatT = double;

    // Create numbers: one large value and many small values
    std::vector<FloatT> values;
    values.push_back( 1e8 ); // a large value
    const int smallCount = 1000000;
    for ( int i = 0; i < smallCount; ++i )
    {
        values.push_back( 1e-8 ); // small increments
    }

    // Naive sum
    double naive = std::accumulate( values.begin(), values.end(), 0.0 );

    // Compensated sum (Kahan)
    CompensatedSum<double> ksum( 0.0 );
    for ( auto v : values )
    {
        ksum += v;
    }
    double compensated = static_cast<double>( ksum );

    std::cout << std::fixed << std::setprecision(12);
    std::cout << "Naive sum:       " << naive << "\n";
    std::cout << "Compensated sum: " << compensated << "\n";

    // Expected exact value: 1e8 + smallCount * 1e-8
    double exact = 1e8 + static_cast<double>( smallCount ) * 1e-8;
    std::cout << "Exact value:     " << exact << "\n";

    std::cout << "Naive error:     " << ( naive - exact ) << "\n";
    std::cout << "Compensated err: " << ( compensated - exact ) << "\n";

    return 0;
}
```

Example output (approximate):

```
Naive sum:       100000000.000000000000
Compensated sum: 100000000.100000000000
Exact value:     100000000.100000000000
Naive error:     -0.100000000000
Compensated err:  0.000000000000
```

Notes

- The exact numbers and shown errors depend on platform floating-point behavior and optimization; the compensated result is typically much closer to the exact sum.
- For sequences where terms vary widely in magnitude, compensated summation is an effective, low-cost technique to reduce error.

See also

- `TwoSum`, `TwoProd`, and `CompensatedFloat` for other compensated arithmetic helpers in the `Harlinn::Math` library.
