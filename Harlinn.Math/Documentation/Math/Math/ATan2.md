# ATan2

## Summary

`ATan2` computes the angle (in radians) whose tangent is `y/x`, using the signs of `y` and `x` to determine the correct quadrant. It is constexpr-friendly via the library's `OpenLibM` helpers and matches the semantics of `atan2`/`atan2f` from the C math library.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T ATan2( T y, T x ) noexcept;
```

## Behavior

- Returns the angle ? measured in radians between the positive x-axis and the point `(x, y)`.
- Range of return values is (-?, ?].
- Uses the signs of both `x` and `y` to place the result in the correct quadrant; for example, `ATan2(+y, -x)` yields an angle in the second quadrant.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::atan2f`; for `double` it delegates to `Math::Internal::OpenLibM::atan2` ensuring constexpr-capable behavior in constant-evaluation contexts.
- Special values follow IEEE and underlying library semantics: NaN inputs propagate NaN; infinities are handled per `atan2` rules.

## Notes

- The result is in radians. Use `Rad2Deg` to convert to degrees when needed.
- Prefer `ATan2` over the single-argument `ATan` when quadrant information is important (e.g. converting Cartesian coordinates to polar coordinates).

## Examples

Runtime example:

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ATan2;
    using Harlinn::Math::Rad2Deg;

    double y = 1.0;
    double x = -1.0;

    double angle = ATan2( y, x ); // ~ 3*pi/4
    std::cout << "ATan2(1, -1) = " << angle << " (radians)\n";
    std::cout << "ATan2(1, -1) = " << Rad2Deg( angle ) << " degrees\n"; // ~135

    // Handling special values
    double inf = std::numeric_limits<double>::infinity();
    std::cout << "ATan2(inf, 1) = " << ATan2( inf, 1.0 ) << '\n';
    std::cout << "ATan2(1, 0) = " << ATan2( 1.0, 0.0 ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = Harlinn::Math::ATan2( 1.0, -1.0 );
static_assert( a > Harlinn::Math::Constants<double>::Pi * 3.0 / 4.0 - 1e-12 );

constexpr double zeroAngle = Harlinn::Math::ATan2( 0.0, 1.0 );
static_assert( zeroAngle == 0.0 );
```

## See also

- `ATan`, `ATanH` — related inverse trigonometric functions.
- `Tan`, `Sin`, `Cos` — trigonometric functions.
- `Deg2Rad`, `Rad2Deg` — conversion helpers between degrees and radians.

---

Created for the Harlinn.Math library documentation.
