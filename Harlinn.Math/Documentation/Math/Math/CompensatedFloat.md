# CompensatedFloat

Description

`CompensatedFloat` represents a floating-point value together with an explicit rounding error term. It is intended to store the result of a compensated operation (for example `TwoProd` or `TwoSum`) as a pair

$$
\text{CompensatedFloat} = (v,\; err)
$$

where `v` is the primary floating-point result and `err` contains the small rounding error such that the exact quantity is approximately `v + err`.

Class template (C++)

The class definition in the library (simplified) is:

```cpp
template<typename T>
    requires IsFloatingPoint<T>
class CompensatedFloat
{
public:
    using value_type = T;
    using ValueType = T;

    ValueType v{};   // main value
    ValueType err{}; // rounding/error term

    constexpr CompensatedFloat( ValueType v, ValueType err = 0 ) noexcept;
    constexpr explicit operator float() const noexcept;
    constexpr explicit operator double() const noexcept;
    std::string ToString() const;
};
```

Semantics

- The stored pair `v` and `err` should be interpreted as the compensated value `v + err` which is a more accurate representation of the true mathematical result than `v` alone.
- Typical producers of `CompensatedFloat` values are helper functions like `TwoProd(a,b)` and `TwoSum(a,b)` which return both the rounded result and the associated rounding error.
- Converting a `CompensatedFloat` to a primitive floating type returns `v + err` via the appropriate conversion operator, yielding a more accurate scalar.

Relationship to compensated arithmetic

`TwoSum` and `TwoProd` compute the rounded result and the rounding error for sum and product respectively. For two numbers \(a\) and \(b\):

- `TwoSum(a,b)` produces \(s,\; \delta\) where \(s = \operatorname{fl}(a+b)\) and \(\delta\) is the rounding error such that the exact sum is \(a + b = s + \delta\).
- `TwoProd(a,b)` produces \(p,\; \varepsilon\) where \(p = \operatorname{fl}(a\cdot b)\) and \(\varepsilon\) is the error so that the exact product is \(a\cdot b = p + \varepsilon\).

These pairs are naturally represented by `CompensatedFloat` instances.

Examples

1) Capture product and error with `TwoProd` and convert to a higher-precision scalar:

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

    auto cp = TwoProd( a, b ); // returns CompensatedFloat<double>

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "product (rounded) = " << cp.v << "\n";
    std::cout << "error term        = " << cp.err << "\n";
    std::cout << "reconstructed     = " << static_cast<double>( cp ) << "\n"; // v + err

    return 0;
}
```

2) Use `CompensatedFloat` to improve an accumulation of products:

```cpp
#include <vector>
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;
    using FloatT = double;

    std::vector<FloatT> x{ 1e8, 1e-8, 1e-8 };
    std::vector<FloatT> y{ 1e-8, 1e8, 1e-8 };

    // Naive dot product
    FloatT naive = 0;
    for ( size_t i = 0; i < x.size(); ++i )
        naive += x[i] * y[i];

    // Compensated inner product using TwoProd and accumulating with CompensatedFloat
    CompensatedFloat<FloatT> acc{ 0.0, 0.0 };
    for ( size_t i = 0; i < x.size(); ++i )
    {
        auto prod = TwoProd( x[i], y[i] ); // prod.v and prod.err
        // accumulate main values and errors explicitly
        auto s = TwoSum( acc.v, prod.v );
        acc.v = s.v;
        acc.err += ( s.err + prod.err );
    }

    // Final reconstructed result
    FloatT compensated = static_cast<FloatT>( acc ); // acc.v + acc.err

    std::cout << std::fixed << std::setprecision(12);
    std::cout << "Naive dot:       " << naive << "\n";
    std::cout << "Compensated dot: " << compensated << "\n";

    return 0;
}
```

Notes

- `CompensatedFloat` is a lightweight POD-like container intended to transport both the rounded result and the small correction term between functions.
- When greater accuracy is required you can propagate both `v` and `err` explicitly through algorithms (as in the inner-product example) or convert to a scalar (which returns `v + err`) for use where a single floating result is needed.

See also

- `TwoProd`, `TwoSum`, `CompensatedSum`, and `InnerProduct` in `Harlinn::Math` for related compensated arithmetic utilities.
