# Radians

## Summary

`Radians` converts an angle given in degrees to radians using the relation radians = degrees * ? / 180. The function is `constexpr` and works with the library's `Constants<T>::Pi` constant for correct precision for `float` and `double`.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Radians( T deg );
```

## Behavior

- Returns the value of the angle in radians corresponding to the input angle in degrees.
- Uses `Constants<T>::Pi` so that the conversion uses the appropriate value of ? for the floating-point type `T`.
- The function is `constexpr` and `noexcept`-safe in practice (performs only arithmetic and constant lookup), so it can be used in compile-time expressions.

## Notes

- This is a simple utility wrapper; use it wherever angle unit conversion to radians is needed (trigonometric calls, graphics transforms, physics simulations, etc.).
- For converting radians to degrees see `Degrees`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Radians;

    double deg1 = 180.0;
    double deg2 = 45.0;

    std::cout << "Radians(180) = " << Radians( deg1 ) << '\n'; // ~3.141592653589793
    std::cout << "Radians(45)  = " << Radians( deg2 ) << '\n'; // ~0.7853981633974483

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double r180 = Harlinn::Math::Radians( 180.0 );
static_assert( r180 > 3.1415926535897929 && r180 < 3.1415926535897931 );

constexpr float r45f = Harlinn::Math::Radians( 45.0f );
// pi/4 ~ 0.7853982f
static_assert( r45f > 0.7853981f && r45f < 0.7853983f );
```

## See also

- `Degrees` — converts radians to degrees.
- `Sin`, `Cos`, `Tan` — trigonometric functions that expect radians.

---

Created for the Harlinn.Math library documentation.
