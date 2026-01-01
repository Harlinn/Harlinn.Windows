# Round

[Optimized basic math functions](Readme.md)/[Nearest integer floating point operations](NearestIntegerFloatingPointOperations.md)/`Round`

## Summary

`Round` returns the value of its argument rounded to the nearest integer, in the same floating-point type. Halfway cases are rounded away from zero. Overloads exist for floating-point and integer types; the integer overload simply returns the argument unchanged.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Round( T value ) noexcept;

template<IntegerType T>
constexpr inline T Round( T value ) noexcept;
```

## Behavior

- For floating-point types:
  - Returns the nearest integer value to `value` with halfway cases (fractional part exactly 0.5) rounded away from zero.
  - In `consteval` contexts the function delegates to `Internal::FloatingPoint<T>::Round()` for well-defined compile-time behavior; at runtime the implementation uses optimized intrinsics or library routines.
- For integer types the function returns the argument unchanged.
- All overloads are `constexpr` and `noexcept` where applicable.

## Notes

- Use `Round` when you need rounding-to-nearest with ties-away-from-zero semantics and `constexpr`-capability across platforms.
- For rounding toward zero use `Trunc`, for floor/ceil use `Floor`/`Ceil` respectively.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Round;

    double a = 3.2;
    double b = 2.5;   // halfway case
    double c = -2.5;  // halfway case negative
    float d = -1.6f;
    int i = 7;

    std::cout << "Round(3.2) = " << Round( a ) << '\n';   // 3.0
    std::cout << "Round(2.5) = " << Round( b ) << '\n';   // 3.0 (ties away from zero)
    std::cout << "Round(-2.5) = " << Round( c ) << '\n';  // -3.0 (ties away from zero)
    std::cout << "Round(-1.6f) = " << Round( d ) << '\n'; // -2.0
    std::cout << "Round(7) = " << Round( i ) << '\n';     // 7 (integer overload)

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::Round( 3.4 ) == 3.0 );
static_assert( Harlinn::Math::Round( 3.5 ) == 4.0 );
static_assert( Harlinn::Math::Round( -3.5 ) == -4.0 );
```

## See also

- `Trunc`, `Floor`, `Ceil`, `FRExp`, `ModF`: related numeric utilities.


