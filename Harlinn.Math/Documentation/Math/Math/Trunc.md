# Trunc

[Optimized basic math functions](Readme.md)/[Nearest integer floating point operations](NearestIntegerFloatingPointOperations.md)/`Trunc`

## Summary

`Trunc` computes the integer part of a value by discarding its fractional component. Overloads exist for floating-point and integer types. For floating-point types this function is `constexpr`-friendly and matches the semantics of `std::trunc` with compile-time evaluation provided by the library's internal helpers.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
template<FloatingPointType T>
constexpr inline T Trunc( T value ) noexcept;

template<IntegerType T>
constexpr inline T Trunc( T value ) noexcept;
```

## Behavior

- Floating-point overload:
  - Returns the nearest integer value not greater in magnitude than `value` (i.e., truncation toward zero).
  - Preserves the sign of zero (so `Trunc(-0.5)` yields `-0.0` when the type supports signed zero).
  - In `consteval` contexts the implementation uses `Internal::FloatingPoint<T>::Trunc()`; at runtime it uses platform intrinsics or library routines for optimal performance.
- Integer overload:
  - Returns the argument unchanged.

All overloads are `constexpr` and `noexcept` where applicable.

## Notes

- Use `Trunc` when you need to remove the fractional part of a floating-point value and keep the sign of the result consistent with truncation toward zero.
- For floor/ceiling behavior use `Floor`/`Ceil` respectively.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Trunc;

    double a = 3.7;
    double b = -2.9;
    float c = -0.5f;
    int i = 5;

    std::cout << "Trunc(3.7) = " << Trunc( a ) << '\n';   // 3.0
    std::cout << "Trunc(-2.9) = " << Trunc( b ) << '\n';  // -2.0
    std::cout << "Trunc(-0.5f) = " << Trunc( c ) << '\n'; // -0.0 (sign preserved)
    std::cout << "Trunc(5) = " << Trunc( i ) << '\n';     // 5

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::Trunc( 3.9 ) == 3.0 );
static_assert( Harlinn::Math::Trunc( -3.9 ) == -3.0 );
static_assert( Harlinn::Math::Trunc( 42 ) == 42 );
```

## See also

- `Floor`, `Ceil`, `Round`: other rounding utilities.


