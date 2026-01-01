# ModF

[Optimized basic math functions](Readme.md)/[Floating point manipulation functions](FloatingPointManipulationFunctions.md)/`ModF`

## Summary

`ModF` decomposes a floating-point value into its integral and fractional parts. It mirrors the behavior of the C `modf` family while being `constexpr`-friendly via the library's `Internal::OpenLibM` helpers.

There are three overloads:
- `std::pair<T,T> ModF(T val)`: returns `{ integerPart, fractionalPart }`.
- `T ModF(T val, T* integerPart)`: stores the integral part through pointer and returns fractional part.
- `T ModF(T val, T& integerPart)`: stores the integral part through reference and returns fractional part.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline std::pair<T, T> ModF( T val ) noexcept;

template<FloatingPointType T>
constexpr inline T ModF( T val, T* integerPart ) noexcept;

template<FloatingPointType T>
constexpr inline T ModF( T val, T& integerPart ) noexcept;
```

## Behavior

- For a finite `val`, the function returns or writes the integral part and returns the fractional part such that:
  - `val == integerPart + fractionalPart`.
  - `fractionalPart` has the same sign as `val` and its magnitude is less than 1.
- If `val` is zero, both parts are zero (sign preserved for signed zero when applicable).
- For `NaN` or infinities the result follows the semantics of the underlying OpenLibM implementation.
- All overloads are `constexpr` and `noexcept` and can be used in compile-time contexts.

## Notes

- Use `ModF` when you need to separate integer and fractional components for numerical algorithms, formatting, or range reduction.
- Prefer the pointer/reference overloads when you only need the fractional part as a return value.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <utility>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ModF;

    // pair overload
    auto p = ModF( 3.25 );
    std::cout << "ModF(3.25) -> integer=" << p.first << ", fractional=" << p.second << '\n';

    // pointer overload
    double intPart = 0.0;
    double frac = ModF( -1.75, &intPart );
    std::cout << "ModF(-1.75, &intPart) -> integer=" << intPart << ", fractional=" << frac << '\n';

    // reference overload
    float iref = 0.f;
    float fref = ModF( 0.125f, iref );
    std::cout << "ModF(0.125f, iref) -> integer=" << iref << ", fractional=" << fref << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr auto p = Harlinn::Math::ModF( 5.5 );
static_assert( p.first == 5.0 );
static_assert( p.second == 0.5 );

constexpr double ip = [](){ double i=0; Harlinn::Math::ModF( -2.25, &i ); return i; }();
static_assert( ip == -2.0 );
```

## See also

- `FRExp`: decomposes into normalized fraction and binary exponent.
- `Trunc`, `Floor`, `Ceil`, `Round`: other integer/fractional related utilities.


