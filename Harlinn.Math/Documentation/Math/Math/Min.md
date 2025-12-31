# Min

## Summary

`Min` returns the smallest of its arguments. Overloads are provided for floating-point and integer types, and variadic overloads accept multiple values. The floating-point overloads handle NaN and signed zeros according to the library's conventions (NaNs are propagated as in `Internal::MinImpl`).

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
// Floating-point two-argument overload
template<FloatingPointType T>
constexpr inline T Min( T first, T second ) noexcept;

// Integer two-argument overload
template<IntegerType T>
constexpr inline T Min( T first, T second ) noexcept;

// Floating-point variadic overload
template<FloatingPointType T, FloatingPointType ...Args>
constexpr inline T Min( T first, T second, Args... remaining ) noexcept;

// Integer variadic overload
template<IntegerType T, IntegerType ...Args>
constexpr inline T Min( T first, T second, Args... remaining ) noexcept;
```

## Behavior

- For floating-point types:
  - In constant-evaluation contexts the function uses `Internal::MinImpl` to ensure well-defined `constexpr` behavior and to handle NaNs and signed zeroes consistently.
  - At runtime it forwards to the appropriate `fmin` family functions (`fminf` for `float`, `fmin` for `double`) when not evaluated in a constant expression.
  - If either argument is NaN the other argument is returned (matching the library's chosen semantics in `Internal::MinImpl`). Signed zeroes are distinguished according to the sign bit.
- For integer types the function simply returns the smaller of the two values (uses `std::min`).
- Variadic overloads compute the minimum of all provided arguments by repeated application of the two-argument `Min`.

## Notes

- Use `Min` when you need a `constexpr`-friendly, type-generic minimum function that handles both integer and floating-point types uniformly.
- For element-wise minima on containers prefer algorithms or SIMD helpers.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Min;

    double a = 3.5;
    double b = -1.25;
    double c = std::numeric_limits<double>::quiet_NaN();

    std::cout << "Min(a, b) = " << Min(a, b) << '\n';           // -1.25
    std::cout << "Min(a, b, 0.0) = " << Min(a, b, 0.0) << '\n'; // -1.25

    // NaN handling: library Min returns the non-NaN value when one operand is NaN
    std::cout << "Min(a, NaN) = " << Min(a, c) << '\n';        // 3.5

    int x = 10, y = 4, z = 7;
    std::cout << "Min(x, y, z) = " << Min(x, y, z) << '\n';    // 4

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::Min( 1, 2 ) == 1 );
static_assert( Harlinn::Math::Min( 3.0, 2.0 ) == 2.0 );
constexpr double m = Harlinn::Math::Min( 5.0, 2.5, 3.0 );
static_assert( m == 2.5 );
```

## See also

- `Max`, `IsNaN`, `IsFinite` — related comparison and classification utilities.

---

Created for the Harlinn.Math library documentation.
