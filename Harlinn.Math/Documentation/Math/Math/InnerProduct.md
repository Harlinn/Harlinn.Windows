# InnerProduct

Description

`InnerProduct` computes the dot product of a sequence of terms with reduced floating-point error by using compensated arithmetic and FMA where available. The implementation composes `TwoProd` for each product and `TwoSum` to combine intermediate results, producing a `CompensatedFloat` internally and returning a corrected scalar value.

Mathematical definition

Given pairs of terms \((x_1,y_1), (x_2,y_2), \dots, (x_n,y_n)\) the inner product is

$$
I = \sum_{i=1}^n x_i\,y_i.
$$

Floating-point evaluation of this sum can suffer from rounding error. `InnerProduct` reduces this error by computing each product with an associated rounding error and summing the primary results while accumulating the small correction terms.

Function signature (C++)

```cpp
// Public convenience overload
template <typename FloatT, typename... T>
    requires std::conjunction_v<std::is_arithmetic<T>...>
constexpr inline FloatT InnerProduct( FloatT term, T... terms );

// Internal recursive helper (returns CompensatedFloat<FloatT>)
template<typename FloatT>
    requires IsFloatingPoint<FloatT>
constexpr CompensatedFloat<FloatT> Internal::InnerProduct( FloatT a, FloatT b );

template <typename FloatT, typename... T>
    requires IsFloatingPoint<FloatT>
constexpr inline CompensatedFloat<FloatT> Internal::InnerProduct( FloatT a, FloatT b, T... terms );
```

Return value

The public `InnerProduct` returns a scalar of type `FloatT` that represents the compensated sum of products. Internally the computation returns a `CompensatedFloat<FloatT>` with fields `v` and `err` where the exact inner product is approximated by `v + err`.

Usage notes

- Use `InnerProduct` when computing dot products or polynomial accumulations where increased accuracy is desired.
- The implementation is especially effective when `std::fma` is supported by the hardware.
- For manual inspection of intermediate error terms, call the internal helper that returns `CompensatedFloat`.

Example

This example compares naive accumulation with `InnerProduct` for a vector dot product that can suffer from rounding error.

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

    // Construct vectors with mixed magnitudes
    std::vector<FloatT> x{ 1e16, 1.0, 1.0, 1.0 };
    std::vector<FloatT> y{ 1.0, 1e-16, 1e-16, 1e-16 };

    // Naive dot product
    double naive = 0.0;
    for ( size_t i = 0; i < x.size(); ++i )
    {
        naive += x[i] * y[i];
    }

    // Compensated inner product
    // public API expects first term followed by remaining terms as pairs
    // Pack pairs as: x0, y0, x1, y1, ...
    double compensated = InnerProduct( x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3] );

    // Exact reference using long double for illustration
    long double exact = 0;
    for ( size_t i = 0; i < x.size(); ++i )
        exact += (long double)x[i] * (long double)y[i];

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "naive       = " << naive << "\n";
    std::cout << "compensated = " << compensated << "\n";
    std::cout << "exact       = " << static_cast<double>( exact ) << "\n";
    std::cout << "naive error = " << ( naive - static_cast<double>( exact ) ) << "\n";
    std::cout << "comp error  = " << ( compensated - static_cast<double>( exact ) ) << "\n";

    return 0;
}
```

Expected behavior

- `compensated` should be closer to `exact` than `naive` in many cases where rounding loss occurs, especially when terms have mixed magnitudes.

See also:

- `TwoProd` : compute product and its rounding error
- `TwoSum` : compute sum and its rounding error
- `CompensatedSum` : Kahan summation for sequences
- `InnerProduct` internal helpers : `Internal::InnerProduct` for inspecting `CompensatedFloat` results
