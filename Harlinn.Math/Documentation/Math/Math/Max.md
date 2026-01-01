# Max

[Optimized basic math functions](Readme.md)/[Classification and comparison](ClassificationAndComparison.md)/`Max`

## Summary

`Max` returns the largest of its arguments. Overloads are provided for floating-point and integer types, and variadic overloads accept multiple values. The floating-point overloads handle NaN and signed zeros according to the library's conventions (NaNs are propagated as in `Internal::MaxImpl`).

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
// Floating-point two-argument overload
template<FloatingPointType T>
constexpr inline T Max( T first, T second ) noexcept;

// Integer two-argument overload
template<IntegerType T>
constexpr inline T Max( T first, T second ) noexcept;

// Floating-point variadic overload
template<FloatingPointType T, FloatingPointType ...Args>
constexpr inline T Max( T first, T second, Args... remaining ) noexcept;

// Integer variadic overload
template<IntegerType T, IntegerType ...Args>
constexpr inline T Max( T first, T second, Args... remaining ) noexcept;
```

## Behavior

- For floating-point types:
  - In constant-evaluation contexts the function uses `Internal::MaxImpl` to ensure well-defined `constexpr` behavior and to handle NaNs and signed zeroes consistently.
  - At runtime it forwards to the appropriate `fmax` family functions (`fmaxf` for `float`, `fmax` for `double`) when not evaluated in a constant expression.
  - If either argument is NaN the other argument is returned (matching the library's chosen semantics in `Internal::MaxImpl`). Signed zeroes are distinguished according to the sign bit.
- For integer types the function simply returns the larger of the two values (uses `std::max`).
- Variadic overloads compute the maximum of all provided arguments by repeated application of the two-argument `Max`.

## Notes

- Use `Max` when you need a `constexpr`-friendly, type-generic maximum function that handles both integer and floating-point types uniformly.
- For element-wise maxima on containers prefer algorithms or SIMD helpers.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Max;

    double a = 3.5;
    double b = -1.25;
    double c = std::numeric_limits<double>::quiet_NaN();

    std::cout << "Max(a, b) = " << Max(a, b) << '\n';           // 3.5
    std::cout << "Max(a, b, 10.0) = " << Max(a, b, 10.0) << '\n'; // 10.0

    // NaN handling: library Max returns the non-NaN value when one operand is NaN
    std::cout << "Max(a, NaN) = " << Max(a, c) << '\n';        // 3.5

    int x = 10, y = 4, z = 7;
    std::cout << "Max(x, y, z) = " << Max(x, y, z) << '\n';    // 10

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::Max( 1, 2 ) == 2 );
static_assert( Harlinn::Math::Max( 3.0, 2.0 ) == 3.0 );
constexpr double m = Harlinn::Math::Max( 5.0, 2.5, 7.0 );
static_assert( m == 7.0 );
```

## See also

- `Min`, `IsNaN`, `IsFinite`: related comparison and classification utilities.

