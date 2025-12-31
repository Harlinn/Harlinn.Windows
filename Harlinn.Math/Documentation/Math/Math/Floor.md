# Floor

## Summary

`Floor` returns the largest integer value not greater than its argument. Overloads exist for floating-point and integer types. For floating-point types the function is `constexpr`-friendly and preserves signed zero semantics where applicable.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
template<FloatingPointType T>
constexpr inline T Floor( T value ) noexcept;

template<IntegerType T>
constexpr inline T Floor( T value ) noexcept;
```

## Behavior

- Floating-point overload:
  - Returns the largest integer value not greater than `value` (rounding toward negative infinity).
  - In `consteval` contexts this uses `Internal::FloatingPoint<T>::Floor()`; at runtime it uses platform intrinsics or library routines for performance.
- Integer overload:
  - Returns the argument unchanged.

All overloads are `constexpr` and `noexcept` where applicable.

## Notes

- Use `Floor` when you need consistent, constexpr-capable floor behavior across platforms.
- For truncation toward zero use `Trunc`; for rounding to nearest use `Round`.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Floor;

    double a = 3.7;
    double b = -2.3;
    float c = -0.0f;
    int i = 5;

    std::cout << "Floor(3.7) = " << Floor( a ) << '\n';   // 3.0
    std::cout << "Floor(-2.3) = " << Floor( b ) << '\n';  // -3.0
    std::cout << "Floor(-0.0f) = " << Floor( c ) << '\n'; // -0.0 (sign preserved)
    std::cout << "Floor(5) = " << Floor( i ) << '\n';     // 5

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::Floor( 3.9 ) == 3.0 );
static_assert( Harlinn::Math::Floor( -3.1 ) == -4.0 );
static_assert( Harlinn::Math::Floor( 42 ) == 42 );
```

## See also

- `Trunc`, `Ceil`, `Round` — related rounding utilities.

---

Created for the Harlinn.Math library documentation.
