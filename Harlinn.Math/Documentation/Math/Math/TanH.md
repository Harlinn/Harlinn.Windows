# TanH

[Optimized basic math functions](Readme.md)/[Hyperbolic functions](HyperbolicFunctions.md)/`TanH`

## Summary

`TanH` computes the hyperbolic tangent (`tanh`) of a floating-point value. The function is `constexpr`-friendly in constant-evaluation contexts and delegates to the library's `OpenLibM` helpers for consistent behavior across platforms.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T TanH( T x ) noexcept;
```

## Behavior

- Returns the hyperbolic tangent of `x`, i.e. `(e^x - e^-x) / (e^x + e^-x)`.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::tanhf`.
- For `double` the implementation uses `Math::Internal::OpenLibM::tanh` in const-evaluation contexts and `std::tanh` at runtime when appropriate.
- Follows IEEE semantics for special values: `TanH(NaN) = NaN`, `TanH(+inf) = 1`, `TanH(-inf) = -1`.
- The function is `noexcept` and usable in `constexpr` contexts when the underlying helpers are constexpr-capable.

## Notes

- `TanH` is dimensionless and quickly approaches �1 for large |x|.
- Use `TanH` when modeling sigmoid-like activations or when working with hyperbolic function identities.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::TanH;

    double a = 0.0;
    double b = 1.0;
    double c = -2.0;

    std::cout << "TanH(0) = " << TanH( a ) << '\n';      // 0
    std::cout << "TanH(1) = " << TanH( b ) << '\n';      // ~0.761594
    std::cout << "TanH(-2) = " << TanH( c ) << '\n';     // ~-0.964027

    double inf = std::numeric_limits<double>::infinity();
    std::cout << "TanH(inf) = " << TanH( inf ) << '\n';  // 1
    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double t0 = Harlinn::Math::TanH( 0.0 );
static_assert( t0 == 0.0 );

constexpr double t1 = Harlinn::Math::TanH( 1.0 );
static_assert( t1 > 0.761594 && t1 < 0.761596 );
```

## See also

- `SinH`, `CosH`, `ASinH`, `ACosH` : related hyperbolic functions.
- `Exp`, `Log` : helpers used in hyperbolic computations.

