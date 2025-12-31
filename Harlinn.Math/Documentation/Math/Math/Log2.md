# Log2

## Summary

`Log2` computes the binary (base-2) logarithm of a floating-point value, returning the value y such that `2^y = x`. The function is `constexpr`-friendly and delegates to the library's `OpenLibM` helpers for consistent behavior in both compile-time and runtime contexts.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Log2( T x ) noexcept;
```

## Behavior

- Returns the base-2 logarithm `log2(x)` of the input `x`.
- In constant-evaluation contexts the implementation calls `Math::Internal::OpenLibM::log2`/`log2f` to provide constexpr-capable and platform-consistent behavior.
- Special values follow IEEE rules:
  - `Log2(+inf) = +inf`
  - `Log2(1) = 0`
  - `Log2(0) = -inf`
  - `Log2(x < 0) = NaN`
  - `Log2(NaN) = NaN`
- The function is `noexcept`.

## Notes

- Use `Log2` when you need a constexpr-capable binary logarithm with consistent semantics across compile-time and runtime.
- For integer arguments consider using `Log2Int` for an integer approximation of the base-2 logarithm.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Log2;

    double x1 = 1.0;
    double x2 = 8.0;
    double x3 = 0.5;
    double x4 = 0.0;

    std::cout << "Log2(1.0) = " << Log2( x1 ) << '\n';      // 0
    std::cout << "Log2(8.0) = " << Log2( x2 ) << '\n';      // 3
    std::cout << "Log2(0.5) = " << Log2( x3 ) << '\n';      // -1
    std::cout << "Log2(0.0) = " << Log2( x4 ) << '\n';      // -inf

    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "Log2(NaN) is NaN: " << std::isnan( Log2( qnan ) ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double zero = Harlinn::Math::Log2( 1.0 );
static_assert( zero == 0.0 );

constexpr double three = Harlinn::Math::Log2( 8.0 );
static_assert( three == 3.0 );
```

## See also

- `Log`, `Log10`, `Log1P` — other logarithm helpers.
- `Log2Int` — integer base-2 logarithm helper.

---

Created for the Harlinn.Math library documentation.
