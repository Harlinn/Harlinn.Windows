# Deg2Rad

[Optimized basic math functions](Readme.md)/[Trigonometric functions](TrigonometricFunctions.md)/`Deg2Rad`

## Summary

`Deg2Rad` converts an angle in degrees to radians.

The function is `constexpr` and `noexcept` and accepts any floating-point type supported by the library.

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Deg2Rad(T angleInDegrees) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

`Deg2Rad` multiplies the input by the constant factor `M_PI / 180.0` (computed as the appropriate floating type) and returns the resulting angle in radians.

Because the function is `constexpr` it can be used in compile-time expressions.

## Notes

- Use `Deg2Rad` when you need a type-safe, constexpr-capable conversion that preserves the input floating-point type.
- For single-precision inputs the conversion is performed in `float` precision; for `double` inputs it is performed in `double` precision.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Deg2Rad;

    float degF = 180.0f;
    float radF = Deg2Rad(degF);
    std::cout << degF << " degrees = " << radF << " radians\n"; // prints 180 degrees = 3.14159 radians

    double degD = 90.0;
    double radD = Deg2Rad(degD);
    std::cout << degD << " degrees = " << radD << " radians\n"; // prints 90 degrees = 1.5708 radians

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert(Harlinn::Math::Deg2Rad(0.0) == 0.0);
static_assert(Harlinn::Math::Deg2Rad(180.0) == Harlinn::Math::Constants<double>::Pi);
static_assert(Harlinn::Math::Deg2Rad(90.0f) == Harlinn::Math::Constants<float>::PiOver2);
```

## See also

- `Rad2Deg` for the reverse conversion.

---

Created for the Harlinn.Math library documentation.
