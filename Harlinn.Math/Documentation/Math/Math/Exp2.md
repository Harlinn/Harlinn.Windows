# Exp2

## Summary

`Exp2` computes 2 raised to the power `x`, i.e. 2^x, for floating-point inputs. The function is `constexpr`-friendly and uses the library's `OpenLibM` helpers for consistent compile-time and runtime semantics.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Exp2( T x ) noexcept;
```

## Behavior

- Returns 2^x computed in a numerically stable manner.
- For `float` the implementation calls `Math::Internal::OpenLibM::exp2f`, and for `double` it calls `Math::Internal::OpenLibM::exp2` in `consteval` contexts. At runtime specialized SIMD or standard library helpers may be used for performance while preserving semantics.
- Special values follow IEEE rules: `Exp2(+inf) = +inf`, `Exp2(-inf) = 0`, and `Exp2(NaN) = NaN`.
- The function is `constexpr` and `noexcept` where applicable.

## Notes

- Use `Exp2` when you need exact powers of two or when converting binary exponents to floating-point values.
- For integer exponents consider using `ScaleBN` or bit-manipulation helpers when exact scaling by radix powers is required.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Exp2;

    double a = 3.0;
    double b = -2.0;
    float  c = 0.5f;

    std::cout << std::setprecision(8);
    std::cout << "Exp2(3.0) = " << Exp2( a ) << '\n';    // 8.0
    std::cout << "Exp2(-2.0) = " << Exp2( b ) << '\n';   // 0.25
    std::cout << "Exp2(0.5f) = " << Exp2( c ) << '\n';   // sqrt(2) (~1.4142136)

    // Large exponent -> infinity
    std::cout << "Exp2(1024) is infinite: " << std::isinf( Exp2( 1024.0 ) ) << '\n';

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

constexpr double r1 = Harlinn::Math::Exp2( 4.0 );
static_assert( r1 == 16.0 );

constexpr float r2 = Harlinn::Math::Exp2( 0.5f ); // sqrt(2)
static_assert( r2 > 1.41421f && r2 < 1.41422f );
```

## See also

- `Exp`, `Exp10`, `ExpM1` — related exponential helpers.
- `ScaleBN` — scale by powers of the floating-point radix (typically 2) using integer exponents.

---

Created for the Harlinn.Math library documentation.
