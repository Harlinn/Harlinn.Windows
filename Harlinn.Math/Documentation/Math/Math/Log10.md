# Log10

## Summary

`Log10` computes the common (base-10) logarithm of a floating-point value, returning the value y such that `10^y = x`. The function is `constexpr`-friendly and delegates to the library's `OpenLibM` helpers for consistent compile-time and runtime semantics.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Log10( T x ) noexcept;
```

## Behavior

- Returns the base-10 logarithm `log10(x)` of the input `x`.
- In constant-evaluation contexts the implementation calls `Math::Internal::OpenLibM::log10`/`log10f` to provide constexpr-capable and platform-consistent behavior.
- Special values follow IEEE rules:
  - `Log10(+inf) = +inf`
  - `Log10(1) = 0`
  - `Log10(0) = -inf`
  - `Log10(x < 0) = NaN`
  - `Log10(NaN) = NaN`
- The function is `noexcept`.

## Notes

- Use `Log10` when you need a constexpr-capable common logarithm with consistent semantics across compile-time and runtime.
- For logarithms in other bases use `Log`, `Log2` or compute via `Log(x) / Log(base)` when necessary.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Log10;

    double x1 = 1.0;
    double x2 = 1000.0;
    double x3 = 0.01;
    double x4 = 0.0;

    std::cout << "Log10(1.0) = " << Log10( x1 ) << '\n';      // 0
    std::cout << "Log10(1000.0) = " << Log10( x2 ) << '\n';   // 3
    std::cout << "Log10(0.01) = " << Log10( x3 ) << '\n';     // -2
    std::cout << "Log10(0.0) = " << Log10( x4 ) << '\n';      // -inf

    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "Log10(NaN) is NaN: " << std::isnan( Log10( qnan ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double zero = Harlinn::Math::Log10( 1.0 );
static_assert( zero == 0.0 );

constexpr double three = Harlinn::Math::Log10( 1000.0 );
static_assert( three == 3.0 );
```

## See also

- `Log`, `Log2`, `Log1P` — related logarithm helpers.
- `Exp10` — computes 10^x.

---

Created for the Harlinn.Math library documentation.
