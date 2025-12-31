# Multiply

## Summary

`Multiply` computes the product of all elements in a span-like container. It is a generic, constexpr-capable utility that multiplies items of any arithmetic type. The function requires the container type to satisfy the `SimpleSpanLike` concept and its `value_type` to be arithmetic.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<SimpleSpanLike T>
    requires IsArithmetic<typename T::value_type>
constexpr inline typename T::value_type Multiply( const T& values );
```

## Behavior

- The function initializes the running product to `1` (of the container's `value_type`) and multiplies each element in `values` into the accumulator.
- If `values` is empty the function returns `1` (the multiplicative identity).
- The function is `constexpr` so it can be used in compile-time contexts when the container and its elements are constexpr-evaluable.
- The operation uses the container's iteration interface and does not make assumptions about random access; any `SimpleSpanLike` type that provides `value_type` and is range-iterable is accepted.

## Notes

- Be mindful of overflow for integer types when multiplying many values or large values; consider using a wider type or floating point if appropriate.
- For associative stability, the multiplication order is left-to-right as implemented by iteration.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <vector>
#include <array>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Multiply;

    std::vector<double> values{ 1.5, 2.0, -3.0 };
    double prodVec = Multiply( values );
    std::cout << "Product of vector = " << prodVec << '\n'; // -9.0

    std::array<int, 4> ints{ 2, 3, 4, 5 };
    int prodArr = Multiply( ints );
    std::cout << "Product of array = " << prodArr << '\n'; // 120

    // Empty container returns 1
    std::vector<int> empty;
    std::cout << "Product of empty = " << Multiply( empty ) << '\n'; // 1

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include <array>
#include "Harlinn/Math/Math.h"

constexpr std::array<int, 3> a = { 2, 3, 4 };
static_assert( Harlinn::Math::Multiply( a ) == 24 );

constexpr std::array<unsigned, 0> empty = {};
static_assert( Harlinn::Math::Multiply( empty ) == 1u );
```

## See also

- `FMA`, `TwoProd` — utilities for numerically stable multiply/add operations.
- `Sum` / `CompensatedSum` — related summation helpers.

---

Created for the Harlinn.Math library documentation.
