# Rad2Deg

[Optimized basic math functions](Readme.md)/[Trigonometric functions](TrigonometricFunctions.md)/`Rad2Deg`

## Summary

`Rad2Deg` converts an angle in radians to degrees.

The function is `constexpr` and `noexcept` and accepts any floating-point type supported by the library.

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Rad2Deg(T angleInRadians) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

`Rad2Deg` multiplies the input by the constant factor `180.0 / M_PI` (computed as the appropriate floating type) and returns the resulting angle in degrees.

Because the function is `constexpr` it can be used in compile-time expressions.

## Notes

- Use `Rad2Deg` when you need a type-safe, constexpr-capable conversion that preserves the input floating-point type.
- For single-precision inputs the conversion is performed in `float` precision; for `double` inputs it is performed in `double` precision.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Rad2Deg;

    float radF = Harlinn::Math::Constants<float>::Pi; // pi radians
    float degF = Rad2Deg(radF);
    std::cout << radF << " radians = " << degF << " degrees\n"; // prints 3.14159 radians = 180 degrees

    double radD = Harlinn::Math::Constants<double>::PiOver2; // pi/2 radians
    double degD = Rad2Deg(radD);
    std::cout << radD << " radians = " << degD << " degrees\n"; // prints 1.5708 radians = 90 degrees

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert(Harlinn::Math::Rad2Deg(0.0) == 0.0);
static_assert(Harlinn::Math::Rad2Deg(Harlinn::Math::Constants<double>::Pi) == 180.0);
static_assert(Harlinn::Math::Rad2Deg(Harlinn::Math::Constants<float>::PiOver2) == 90.0f);
```

## See also

- `Deg2Rad` for the reverse conversion.

---

Created for the Harlinn.Math library documentation.
