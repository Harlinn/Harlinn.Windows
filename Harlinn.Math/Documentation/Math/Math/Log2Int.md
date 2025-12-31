# Log2Int

## Summary

`Log2Int` returns the integer part (floor) of the base-2 logarithm of its argument. Several overloads exist to handle both floating-point and integer inputs. For floating-point inputs less than 1 the function returns a negative integer according to the integer part of the logarithm (e.g., `Log2Int(0.5f) == -1`). For integer inputs the function returns the index of the most-significant set bit (zero-based) — i.e., floor(log2(v)).

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
constexpr inline int Log2Int( float v );
constexpr inline int Log2Int( double v );
constexpr inline int Log2Int( UInt32 v );
constexpr inline int Log2Int( Int32 v );
constexpr inline int Log2Int( UInt64 v );
constexpr inline int Log2Int( Int64 v );
```

## Behavior

- Floating-point overloads:
  - If `v >= 1` returns floor(log2(v)) computed using the floating-point representation and helper functions.
  - If `v < 1` returns the negated result for `1/v` (effectively floor(log2(v)) which will be negative or zero).
  - Handles subnormal, infinite and NaN values according to underlying helpers (NaN/Inf behavior is implementation-defined by floating point helpers).
- Integer overloads:
  - Returns the index of the most-significant set bit (0-based) for positive integers.
  - For `0` the implementation returns `0` for the `UInt32` overload (and similar for signed operations that cast to unsigned first).

## Notes

- All overloads are `constexpr` where possible and can be used in compile-time contexts for constant expressions.
- For floating-point inputs the implementation uses bit-level inspection of the significand and exponent to determine the integer result efficiently.
- When passing negative integers the signed overloads reinterpret the value as unsigned when computing the index of the highest set bit.

## Examples

Runtime examples:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h"

int main()
{
    using Harlinn::Math::Log2Int;

    float f1 = 16.0f;
    std::cout << "Log2Int(16.0f) = " << Log2Int( f1 ) << '\n'; // prints 4

    double d = 10.0;
    std::cout << "Log2Int(10.0) = " << Log2Int( d ) << '\n'; // prints 3

    unsigned int u = 1023u;
    std::cout << "Log2Int(1023u) = " << Log2Int( u ) << '\n'; // prints 9

    unsigned int u2 = 1024u;
    std::cout << "Log2Int(1024u) = " << Log2Int( u2 ) << '\n'; // prints 10

    float small = 0.25f;
    std::cout << "Log2Int(0.25f) = " << Log2Int( small ) << '\n'; // prints -2

    return 0;
}
```

Compile-time examples:

```cpp
#include "Harlinn/Math/Math.h"

constexpr int a = Harlinn::Math::Log2Int( 8.0f ); // 3
static_assert( a == 3 );

constexpr int b = Harlinn::Math::Log2Int( 1u << 5 ); // 5
static_assert( b == 5 );
```

## See also

- `Log2` — returns the floating-point base-2 logarithm.
- `Log2Int` (other overloads) — integer and double overloads for different input types.
- `Common::Exponent` / `Common::Significand` — helpers used by the implementation.

---

Created for the Harlinn.Math library documentation.
