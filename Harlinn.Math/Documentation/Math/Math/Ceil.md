# Ceil

[Optimized basic math functions](Readme.md)/[Nearest integer floating point operations](NearestIntegerFloatingPointOperations.md)/`Ceil`

## Summary

`Ceil` returns the smallest integer value not less than its argument. Overloads exist for floating-point and integer types. For floating-point types the function is `constexpr`-friendly and preserves signed zero semantics where applicable.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
template<FloatingPointType T>
constexpr inline T Ceil( T value ) noexcept;

template<IntegerType T>
constexpr inline T Ceil( T value ) noexcept;
```

## Behavior

- Floating-point overload:
  - Returns the smallest integer value not less than `value` (rounding toward positive infinity).
  - In `consteval` contexts this uses `Internal::FloatingPoint<T>::Ceil()`; at runtime it uses platform intrinsics or library routines for performance.
- Integer overload:
  - Returns the argument unchanged.

All overloads are `constexpr` and `noexcept` where applicable.

## Notes

- Use `Ceil` when you need consistent, constexpr-capable ceiling behavior across platforms.
- For truncation toward zero use `Trunc`; for floor (rounding down) use `Floor`.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Ceil;

    double a = 3.2;
    double b = -2.7;
    float c = 0.0f;
    float d = -0.0f;
    int i = 5;

    std::cout << "Ceil(3.2) = " << Ceil( a ) << '\n';    // 4.0
    std::cout << "Ceil(-2.7) = " << Ceil( b ) << '\n';   // -2.0
    std::cout << "Ceil(0.0f) = " << Ceil( c ) << '\n';   // 0.0
    std::cout << "Ceil(-0.0f) = " << Ceil( d ) << '\n';  // -0.0 (sign preserved)
    std::cout << "Ceil(5) = " << Ceil( i ) << '\n';      // 5

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::Ceil( 3.1 ) == 4.0 );
static_assert( Harlinn::Math::Ceil( -3.9 ) == -3.0 );
static_assert( Harlinn::Math::Ceil( 42 ) == 42 );
```

## See also

- `Floor`, `Trunc`, `Round`: related rounding utilities.


