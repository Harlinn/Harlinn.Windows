# ILogB

## Summary

`ILogB` extracts the unbiased exponent from a floating-point value and returns it as a signed integer. This is equivalent to `ilogb`/`ilogbf` from the C math library and is `constexpr`-friendly via the library's `OpenLibM` helpers.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline int ILogB( T x ) noexcept;
```

## Behavior

- Returns the unbiased integral exponent `e` such that for a normalized finite non-zero `x` we have `x = m * 2^e` with `m` in the appropriate normalized range.
- For zero, the result is implementation-defined by the underlying `OpenLibM` but typically returns `FP_ILOGB0` (a large negative value) or raises a domain error in some implementations. The Harlinn.Math implementation delegates to `Math::Internal::OpenLibM::ilogb`/`ilogbf`.
- For infinite `x` returns `INT_MAX` (or the value defined by the underlying `ilogb` implementation).
- For NaN input returns `INT_MAX` or the `ilogb`-defined result for NaN.
- The function is `constexpr` where the underlying helpers are `consteval` capable and is `noexcept`.

## Notes

- Use `ILogB` when you need the exponent as an integer for bit-level manipulation, scaling decisions, or classification logic.
- If you need the exponent as a floating point use `LogB` which returns a floating-point exponent.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::ILogB;

    double v1 = 8.0;       // 8.0 == 1.0 * 2^3
    double v2 = 0.15625;   // 0.15625 == 1.25 * 2^-3

    std::cout << "ILogB(8.0) = " << ILogB( v1 ) << '\n';     // Expected 3
    std::cout << "ILogB(0.15625) = " << ILogB( v2 ) << '\n'; // Expected -3

    double inf = std::numeric_limits<double>::infinity();
    std::cout << "ILogB(inf) = " << ILogB( inf ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly when supported):

```cpp
#include "Harlinn/Math/Math.h"

constexpr int e1 = Harlinn::Math::ILogB( 8.0 );
static_assert( e1 == 3 );

constexpr int e2 = Harlinn::Math::ILogB( 0.125f ); // 0.125 == 2^-3
static_assert( e2 == -3 );
```

## See also

- `LogB` — returns the exponent as a floating-point value.
- `FRExp` / `frexp` — decompose value into mantissa and exponent.

---

Created for the Harlinn.Math library documentation.
