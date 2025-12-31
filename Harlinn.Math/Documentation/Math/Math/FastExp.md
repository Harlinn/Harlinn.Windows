# FastExp

## Summary

`FastExp` returns a fast, efficient approximation of the exponential function `e^x` for `float` inputs. It is optimized for performance and uses a decomposition to base-2 followed by a low-degree polynomial approximation for the fractional part, then reconstructs the result by scaling. This makes it much faster than `std::exp` at the cost of some accuracy.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
constexpr inline float FastExp( float x );
```

## Behavior

- Approximates `e^x` by converting to a base-2 exponent: x' = x * log2(e).
- Splits x' into integer and fractional parts, evaluates a polynomial approximation for 2^fraction, and scales by 2^integer.
- Handles large positive and negative exponents by returning `Infinity` or `0` respectively when overflow/underflow thresholds are exceeded.
- The function is `constexpr` and can be evaluated at compile time for constant inputs.

## Accuracy and Performance Notes

- `FastExp` is intended for performance-sensitive code paths where a modest loss in accuracy is acceptable. It is not a replacement for `std::exp` in situations that require high numerical accuracy.
- For inputs that require strict IEEE-compliant results or maximum precision, use `std::exp` or a higher-accuracy math library implementation.

## Example

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::FastExp;

    float v1 = 1.0f; // e
    float v2 = -10.0f; // small
    float v3 = 10.0f; // large

    std::cout << "FastExp(1.0f) = " << FastExp( v1 ) << '\n';
    std::cout << "FastExp(-10.0f) = " << FastExp( v2 ) << '\n';
    std::cout << "FastExp(10.0f) = " << FastExp( v3 ) << '\n';

    // Compare with std::exp if desired (for testing)
    std::cout << "std::exp(1.0f) = " << std::exp( v1 ) << '\n';

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

// FastExp is constexpr; basic identity for x==0 should hold.
static_assert( Harlinn::Math::FastExp( 0.0f ) == 1.0f );
```

## See also

- `Exp` / `std::exp` — higher-accuracy exponential implementations.
- `FastLog2`, `Log2` — related base-2 logarithm helpers used in complementary transforms.

---

Created for the Harlinn.Math library documentation.
