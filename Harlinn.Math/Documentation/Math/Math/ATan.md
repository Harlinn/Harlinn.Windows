# ATan

## Summary

`ATan` computes the principal value of the arc tangent (inverse tangent). There are two overloads:
- `ATan(x)` — returns the principal value of the arc tangent of `x` in radians in the range (-pi/2, pi/2).
- `ATan(y, x)` — returns the angle (in radians) whose tangent is `y/x`, using the signs of `y` and `x` to determine the correct quadrant (equivalent to `atan2`).

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
template<FloatingPointType T>
constexpr inline T ATan( T x ) noexcept;

template<FloatingPointType T>
constexpr inline T ATan( T y, T x ) noexcept;
```

## Behavior

- `ATan(x)` returns the principal value of the inverse tangent of `x` in radians, in (-pi/2, pi/2).
- `ATan(y, x)` returns the angle between the positive x-axis and the point `(x, y)` (i.e. `atan2(y, x)` semantics), in (-pi, pi].
- For `float` the implementation delegates to `Math::Internal::OpenLibM::atanf` / `atan2f`.
- For `double` the implementation uses `Math::Internal::OpenLibM` helpers in const-evaluation contexts and `std::atan` / `std::atan2` at runtime where available.
- Special values follow IEEE rules: NaN inputs propagate NaN, infinities produce appropriate quadrant results per the underlying implementation.
- The functions are `constexpr`-friendly and `noexcept`.

## Notes

- Results are returned in radians. Use `Rad2Deg` to convert to degrees.
- Use the two-argument overload when quadrant information matters (e.g. converting Cartesian coordinates to polar angle).

## Examples

Runtime example:

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h"

int main()
{
    using Harlinn::Math::ATan;
    using Harlinn::Math::Deg2Rad;
    using Harlinn::Math::Rad2Deg;

    double v = 1.0; // tan(pi/4) == 1
    std::cout << "ATan(1.0) = " << ATan( v ) << " (radians)\n";
    std::cout << "ATan(1.0) = " << Rad2Deg( ATan( v ) ) << " degrees\n"; // ~45

    double y = 1.0, x = -1.0; // point in second quadrant
    std::cout << "ATan(y, x) for (1, -1) = " << ATan( y, x ) << " (radians)\n";
    std::cout << "ATan(y, x) for (1, -1) = " << Rad2Deg( ATan( y, x ) ) << " degrees\n"; // ~135

    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "ATan(NaN) is NaN: " << std::isnan( ATan( qnan ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = Harlinn::Math::ATan( 1.0 );
static_assert( a > Harlinn::Math::Constants<double>::Pi/4 - 1e-12 && a < Harlinn::Math::Constants<double>::Pi/4 + 1e-12 );

constexpr double ang = Harlinn::Math::ATan( 1.0, -1.0 ); // ~3*pi/4
static_assert( ang > Harlinn::Math::Constants<double>::Pi * 3.0 / 4.0 - 1e-12 );
```

## See also

- `Tan`, `Sin`, `Cos` — trigonometric functions.
- `ATan2` — alias-style name for the two-argument arc tangent.
- `Deg2Rad`, `Rad2Deg` — conversion helpers between degrees and radians.

---

Created for the Harlinn.Math library documentation.
