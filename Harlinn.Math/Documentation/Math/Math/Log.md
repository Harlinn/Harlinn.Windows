# Log

[Optimized basic math functions](Readme.md)/[Exponential functions](ExponentialFunctions.md)/`Log`

## Summary

`Log` computes the natural (base-e) logarithm of a floating-point value. The function is `constexpr`-friendly and delegates to the library's `OpenLibM` helpers for well-defined behavior in both compile-time and runtime contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Log( T x ) noexcept;
```

## Behavior

- Returns the natural logarithm ln(x) of the input `x`.
- In constant-evaluation contexts the implementation calls `Math::Internal::OpenLibM::log`/`logf` to provide constexpr-capable and platform-consistent behavior.
- For runtime evaluation the same internal helpers are used ensuring consistent semantics; results follow IEEE rules for special values:
  - `Log(+inf) = +inf`
  - `Log(1) = 0`
  - `Log(0) = -inf` (with sign handling)
  - `Log(x < 0) = NaN`
  - `Log(NaN) = NaN`
- The function is `noexcept`.

## Notes

- Use `Log` when you need a constexpr-capable and numerically consistent natural logarithm across compile-time and runtime.
- For logarithms with other bases, use `Log2`, `Log10`, or compute via `Log(x) / Log(base)` as appropriate.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Log;

    double x1 = 1.0;
    double x2 = std::exp( 2.0 );
    double x3 = 0.0;
    double x4 = -1.0;

    std::cout << "Log(1.0) = " << Log( x1 ) << '\n';          // 0
    std::cout << "Log(e^2) = " << Log( x2 ) << '\n';         // ~2
    std::cout << "Log(0.0) = " << Log( x3 ) << '\n';         // -inf
    std::cout << "Log(-1.0) is NaN: " << std::isnan( Log( x4 ) ) << '\n';

    // Propagation of NaN
    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "Log(NaN) is NaN: " << std::isnan( Log( qnan ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double one = Harlinn::Math::Log( 1.0 );
static_assert( one == 0.0 );

constexpr double two = Harlinn::Math::Log( Harlinn::Math::Exp( 2.0 ) );
static_assert( two > 1.999999 && two < 2.000001 );
```

## See also

- `Log2`, `Log10` � logarithms with bases 2 and 10.
- `Exp`, `ExpM1` � exponential helpers related to logarithms.

---

Created for the Harlinn.Math library documentation.
