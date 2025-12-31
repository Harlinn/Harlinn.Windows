# FMA

## Summary

`FMA` computes a fused multiply–add: it returns `a * b + c`. For floating-point types the library prefers the hardware/standard `std::fma` at runtime to perform the operation with a single rounding. In constant-evaluation contexts the implementation falls back to the simple expression `a * b + c` so the function can be used in `constexpr` code.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
// Integer overload
template<IntegerType T>
inline constexpr T FMA( T a, T b, T c ) noexcept;

// Floating-point overload
template<FloatingPointType T>
inline constexpr T FMA( T a, T b, T c ) noexcept;
```

## Behavior

- Integer overload: returns `a * b + c` using ordinary integer arithmetic.
- Floating-point overload:
  - If evaluated at compile-time (`consteval` context) the function returns `a * b + c` (simple arithmetic expression) so it can be used in `constexpr` expressions.
  - At runtime the function calls `std::fma(a, b, c)` to perform a fused multiply-add with a single rounding step when available, matching the semantics of the C++ standard library's `std::fma`.
- The function is `noexcept` for both overloads.

## Notes

- Using the fused operation for floating-point types can reduce rounding error compared to performing the multiply and add separately.
- Use the integer overload for integral arithmetic where FMA semantics simply mean `a*b + c`.

## Examples

Runtime example (floating point):

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h"

int main()
{
    using Harlinn::Math::FMA;

    double a = 1e100;
    double b = 1e-100;
    double c = 1.0;

    // std::fma performs the multiplication and addition with a single rounding
    std::cout << "FMA(" << a << ", " << b << ", " << c << ") = " << FMA( a, b, c ) << '\n';

    // Integer example
    int ia = 3, ib = 4, ic = 5;
    std::cout << "FMA(int): " << FMA( ia, ib, ic ) << '\n'; // prints 17

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double g = Harlinn::Math::FMA( 2.0, 3.0, 4.0 );
static_assert( g == 10.0 );

constexpr int gi = Harlinn::Math::FMA( 2, 3, 4 );
static_assert( gi == 10 );
```

## See also

- `TwoProd`, `TwoSum` — helpers that return value plus rounding error for improved numerical accuracy.
- `FMAAdjustUp`, `FMAAdjustDown` — variants used when interval arithmetic adjustments are needed.

---

Created for the Harlinn.Math library documentation.
