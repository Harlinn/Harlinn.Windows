# Hypot

## Summary

`Hypot` computes the length of the Euclidean vector (i.e. the square root of the sum of squares) for two or three components in a numerically robust way that avoids undue overflow or underflow. The implementation is `constexpr`-friendly and uses library internal helpers for consistent behavior in constant-evaluation contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
template<FloatingPointType T>
constexpr inline T Hypot( T x, T y ) noexcept;

template<FloatingPointType T>
constexpr inline T Hypot( T x, T y, T z ) noexcept;
```

## Behavior

- `Hypot(x, y)` returns `sqrt(x*x + y*y)` computed in a way that reduces intermediate overflow/underflow.
- `Hypot(x, y, z)` returns `sqrt(x*x + y*y + z*z)` similarly robustly.
- In constant-evaluation contexts the function delegates to `Math::Internal::OpenLibM::FastHypot` (for two-argument case) or falls back to `Sqrt` of the sum of squares for three-argument case; at runtime SIMD helpers are used when available for performance.
- Special values are handled according to IEEE rules: NaNs and infinities propagate appropriately.

## Notes

- Prefer `Hypot` over manual `std::sqrt(x*x + y*y)` when inputs may be large or small to avoid incorrect intermediate results.
- Use the two-argument overload for 2D vector lengths and the three-argument overload for 3D vector lengths.
- The function is `constexpr` when the underlying operations are available at compile time.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Hypot;

    double x = 3.0;
    double y = 4.0;
    std::cout << "Hypot(3.0, 4.0) = " << Hypot( x, y ) << '\n'; // 5.0

    double a = 1.0, b = 2.0, c = 2.0;
    std::cout << "Hypot(1.0, 2.0, 2.0) = " << Hypot( a, b, c ) << '\n'; // sqrt(9) = 3.0

    // Robustness demonstration: very large inputs
    double large = 1e200;
    std::cout << "Hypot(large, large) = " << Hypot( large, large ) << '\n';

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

constexpr double r2 = Harlinn::Math::Hypot( 3.0, 4.0 );
static_assert( r2 == 5.0 );

constexpr double r3 = Harlinn::Math::Hypot( 1.0, 2.0, 2.0 );
static_assert( r3 == 3.0 );
```

## See also

- `Sqrt`, `Sqr`, `FastExp` — related numeric helpers.
- Use `Hypot` whenever computing Euclidean norms to improve numerical stability.

---

Created for the Harlinn.Math library documentation.
