# Pow

## Summary

`Pow` computes `x` raised to the power `y` for floating-point inputs. It delegates to the library's `OpenLibM` helpers to provide consistent behavior in both constant-evaluation and runtime contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Pow( T x, T y ) noexcept;
```

## Behavior

- Returns x^y computed in a numerically sound manner.
- For constant evaluation the implementation uses `Math::Internal::OpenLibM::pow`/`powf` to provide compile-time semantics.
- At runtime it also delegates to the same internal helpers to ensure consistent results across platforms.
- Special values follow IEEE rules: results propagate NaN and infinities per the underlying `pow` semantics.
- The function is `constexpr`-friendly and `noexcept` where applicable.

## Notes

- Use `Pow` for general exponentiation with floating-point bases and exponents.
- For integer exponents and small integers prefer specialized routines (e.g. `FastPow` for compile-time known integer exponents) when performance or exactness is critical.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <cmath>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Pow;

    double a = 2.0;
    double b = 10.0;
    float  c = 0.5f;

    std::cout << "Pow(2.0, 10.0) = " << Pow( a, b ) << '\n';   // 1024
    std::cout << "Pow(9.0, 0.5) = " << Pow( 9.0, 0.5 ) << '\n'; // 3 (sqrt(9))
    std::cout << "Pow(2.0f, 0.5f) = " << Pow( 2.0f, c ) << '\n'; // sqrt(2)

    // Edge cases
    std::cout << "Pow(-1.0, 0.5) is NaN: " << std::isnan( Pow( -1.0, 0.5 ) ) << '\n';
    std::cout << "Pow(inf, 2) = " << Pow( std::numeric_limits<double>::infinity(), 2.0 ) << '\n';

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

constexpr double r1 = Harlinn::Math::Pow( 2.0, 10.0 );
static_assert( r1 == 1024.0 );

constexpr float r2 = Harlinn::Math::Pow( 9.0f, 0.5f ); // sqrt(9)
static_assert( r2 == 3.f );
```

## See also

- `FastPow` — exponentiation by squaring for compile-time known integer exponents.
- `Exp`, `Log` — related exponential and logarithmic helpers.

---

Created for the Harlinn.Math library documentation.
