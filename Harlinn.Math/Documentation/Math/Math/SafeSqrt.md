# SafeSqrt

## Summary

`SafeSqrt` computes the square root of a floating-point value while guarding against negative inputs. The function returns the square root of `max(0, x)`, ensuring a real non-negative result instead of NaN for negative arguments. It is `constexpr` and works with the library's `Sqrt` helper.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T SafeSqrt( T x );
```

## Behavior

- If `x >= 0` returns `Sqrt(x)`.
- If `x < 0` returns `Sqrt(0)` (i.e. `0`), avoiding NaN results from `std::sqrt` on negative inputs.
- It uses `Sqrt` internally and thus benefits from the library's `constexpr` and platform-specific implementations.
- The function is suitable for use in compile-time contexts where `Sqrt` is `constexpr`.

## Notes

- `SafeSqrt` is useful in numerical code where negative values can appear due to rounding or limited precision but a real-valued square root is desired (for example when computing lengths or magnitudes with small negative roundoff).
- It intentionally maps negative inputs to `0.0` rather than signaling an error; call sites that require detection of invalid inputs should check `x` before calling.

## Example

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SafeSqrt;

    double a = 4.0;
    double b = -1.0; // negative due to roundoff or invalid data

    std::cout << "SafeSqrt(4.0) = " << SafeSqrt( a ) << '\n'; // 2.0
    std::cout << "SafeSqrt(-1.0) = " << SafeSqrt( b ) << " (maps negative to 0)" << '\n'; // 0.0

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s1 = Harlinn::Math::SafeSqrt( 9.0 );
static_assert( s1 == 3.0 );

constexpr double s2 = Harlinn::Math::SafeSqrt( -2.0 );
static_assert( s2 == 0.0 );
```

## See also

- `Sqrt` — the library square-root helper used by `SafeSqrt`.
- `SafeSqrt` usage is common when computing magnitudes, lengths, or when protecting against small negative roundoff errors.

---

Created for the Harlinn.Math library documentation.
