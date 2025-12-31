# SinH

## Summary

`SinH` computes the hyperbolic sine (sinh) of a floating-point value. The function is `constexpr`-friendly in constant-evaluation contexts and delegates to the library's `OpenLibM` helpers for consistent behavior.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T SinH( T x ) noexcept;
```

## Behavior

- Returns the hyperbolic sine of `x`, i.e. `(e^x - e^-x)/2`.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::sinhf`.
- For `double` the implementation uses the `OpenLibM` helpers in const-evaluation contexts and `std::sinh` at runtime when appropriate.
- Special values follow the underlying helpers' semantics (NaN/infinity propagation) and the function is `noexcept`.

## Notes

- Use `SinH` for hyperbolic sine computations when you want consistent constexpr-capable behavior across compile-time and runtime.
- For large |x| the result grows approximately as 0.5 * exp(|x|).

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SinH;

    double v1 = 0.0; // sinh(0) == 0
    double v2 = 1.0; // sinh(1)
    double v3 = -2.0; // sinh(-2)

    std::cout << "SinH(0) = " << SinH( v1 ) << '\n';
    std::cout << "SinH(1) = " << SinH( v2 ) << '\n';
    std::cout << "SinH(-2) = " << SinH( v3 ) << '\n';

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

constexpr double s0 = Harlinn::Math::SinH( 0.0 );
static_assert( s0 == 0.0 );

constexpr double s1 = Harlinn::Math::SinH( 1.0 );
static_assert( s1 > 1.175 && s1 < 1.177 ); // ~1.175201193
```

## See also

- `CosH`, `TanH`, `ASinH` — related hyperbolic functions.
- `Exp`, `ExpM1` — exponential helpers used for hyperbolic computations.

---

Created for the Harlinn.Math library documentation.
