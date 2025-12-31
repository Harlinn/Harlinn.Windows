# FastLog2

## Summary

`FastLog2` computes an efficient base-2 logarithm for floating-point values. It is a thin wrapper around `Log2` intended for use where a semantic alias clarifies intent (e.g., performance-sensitive code paths that conceptually use a "fast" base-2 logarithm implementation).

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T FastLog2( T x );
```

## Behavior

- Returns the base-2 logarithm of `x` using the library's `Log2` implementation.
- When available, `Log2` delegates to constexpr-capable implementations, enabling compile-time evaluation for constant inputs.
- Designed as a clear alias for code that expects a fast base-2 logarithm routine; it does not change numerical behavior compared to `Log2`.

## Notes

- For constant expressions `x`, `FastLog2` can be evaluated at compile time.
- For non-constant runtime values the implementation forwards to the underlying `Log2` which uses optimized math library routines.
- `FastLog2` does not perform domain checks beyond those of `Log2`; passing non-positive values will produce the same results/behavior as `Log2` (typically NaN or -inf depending on the input).

## Example

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::FastLog2;

    double v = 16.0;
    double r = FastLog2( v );
    std::cout << "FastLog2(" << v << ") = " << r << '\n'; // prints 4

    v = 10.0;
    std::cout << "FastLog2(" << v << ") = " << FastLog2( v ) << '\n';

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

constexpr double c = Harlinn::Math::FastLog2( 8.0 );
static_assert( c == 3.0 );
```

## See also

- `Log2` — the underlying base-2 logarithm implementation.
- `Log` / `Log10` — other logarithm helpers.
- `FastExp` — companion fast exponential approximation.

---

Created for the Harlinn.Math library documentation.
