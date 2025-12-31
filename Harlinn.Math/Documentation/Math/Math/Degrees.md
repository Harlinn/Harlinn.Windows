# Degrees

## Summary

`Degrees` converts an angle given in radians to degrees using the relation degrees = radians * 180 / ?. The function is `constexpr` and uses `Constants<T>::Pi` so it provides the correct precision for `float` and `double`.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Degrees( T rad );
```

## Behavior

- Returns the value of the angle in degrees corresponding to the input angle in radians.
- Uses `Constants<T>::Pi` for the value of ? appropriate to `T`.
- The function is `constexpr` and suitable for compile-time use.

## Notes

- Use `Degrees` when you need to convert radian values (e.g., results from `Sin`, `Cos`, `ATan2`) to degrees for display, configuration, or interfacing with APIs that expect degrees.
- For the inverse conversion see `Radians`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Degrees;

    double r1 = Harlinn::Math::Constants<double>::Pi; // pi radians
    double r2 = Harlinn::Math::Constants<double>::Pi / 4.0; // pi/4 radians

    std::cout << "Degrees(pi) = " << Degrees( r1 ) << '\n'; // ~180
    std::cout << "Degrees(pi/4) = " << Degrees( r2 ) << '\n'; // ~45

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double d180 = Harlinn::Math::Degrees( Harlinn::Math::Constants<double>::Pi );
static_assert( d180 == 180.0 );

constexpr float d45f = Harlinn::Math::Degrees( Harlinn::Math::Constants<float>::PiOver4 );
// pi/4 * 180/pi == 45
static_assert( d45f > 44.999f && d45f < 45.001f );
```

## See also

- `Radians` — converts degrees to radians.
- `Sin`, `Cos`, `Tan`, `ATan2` — trigonometric functions that use radians.

---

Created for the Harlinn.Math library documentation.
