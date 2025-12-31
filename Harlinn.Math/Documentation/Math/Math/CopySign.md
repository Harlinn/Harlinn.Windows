# CopySign

## Summary

`CopySign` returns a floating-point value composed from the magnitude of the first argument and the sign of the second argument. It preserves signed zero and NaN semantics according to the library's internal helpers and is `constexpr`-friendly.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declarations

```cpp
template<FloatingPointType T>
constexpr inline T CopySign( T magnitude, T signValue ) noexcept;
```

## Behavior

- In constant-evaluation contexts the function delegates to `Math::Internal::CopySignImpl<T>` to guarantee well-defined `constexpr` behavior across platforms.
- At runtime the implementation uses platform-provided `copysign` functions for `float` via `Internal::OpenLibM::copysignf` and the internal implementation for other floating types where appropriate.
- The result has the magnitude (absolute value) of `magnitude` and the sign bit of `signValue`.
- Signed zeros and NaNs are handled consistently: copying the sign to/from zero preserves signed zero, and copying a sign to NaN produces a NaN with the requested sign bit as implemented by the library.

## Notes

- `CopySign` is useful when you need to construct a value with a specific sign while retaining some magnitude, for example when adjusting directions or producing results with sign information derived from another value.
- For integer types, use arithmetic operations or bit casts when appropriate; `CopySign` is defined for floating-point types only.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::CopySign;

    double mag = 3.5;
    double neg = -1.0;
    double pos = 1.0;
    double negZero = -0.0;
    double posZero = 0.0;

    std::cout << "CopySign(3.5, -1.0) = " << CopySign( mag, neg ) << '\n';   // -3.5
    std::cout << "CopySign(3.5, 1.0) = " << CopySign( mag, pos ) << '\n';    // 3.5

    // Signed zero preservation
    std::cout << "CopySign(0.0, -0.0) = " << CopySign( posZero, negZero ) << '\n'; // -0.0

    // NaN sign: preserves magnitude (NaN) and copies sign from signValue
    double qnan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "CopySign(NaN, -1.0) is NaN: " << std::isnan( CopySign( qnan, neg ) ) << '\n';

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

constexpr double a = 2.5;
constexpr double b = -0.0;
constexpr double c = Harlinn::Math::CopySign( a, b );
static_assert( std::signbit( c ) ); // c has negative sign bit
static_assert( std::abs( c ) == a );
```

## See also

- `SignBit`, `CopySign` is often used with `SignBit`, `NextUp`, and `NextDown` for fine-grained control over floating-point sign behavior.

---

Created for the Harlinn.Math library documentation.
