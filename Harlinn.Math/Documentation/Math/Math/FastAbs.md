# FastAbs

[Optimized basic math functions](Readme.md)/[Basic operations](BasicOperations.md)/`FastAbs`

## Summary

`FastAbs` computes the absolute value of its argument using fast, branchless or bit-level techniques. It provides overloads for unsigned and signed integers and for floating-point types. `FastAbs` is `constexpr` and `noexcept` where applicable, and is intended for performance-sensitive code paths where minimal branching or simple bit operations are desirable.

## Declarations

```cpp
template<UnsignedIntegerType T>
constexpr inline T FastAbs(T val) noexcept;

template<SignedIntegerType T>
constexpr inline T FastAbs(T val) noexcept;

template<FloatingPointType T>
constexpr inline T FastAbs(T val) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- Unsigned integers: returns the input unchanged.
- Signed integers: returns the absolute value using a branchless algorithm that avoids conditional branches. The implementation computes a sign mask by shifting the value and applies arithmetic operations to produce the absolute value.
- Floating-point types: clears the sign bit via `std::bit_cast` to the matching unsigned integer representation and back; this is a fast, branchless operation that produces the absolute value for all finite and infinite values. NaN payloads retain their bit-pattern except for the sign bit.

All overloads are usable in `constexpr` contexts.

## Notes

- For signed integers, be mindful of the usual two's-complement corner case: `FastAbs(INT_MIN)` is undefined behavior if the result cannot be represented by the return type. The branchless implementation does not guard against overflow.
- For floating-point values `FastAbs` is typically faster than calling library functions like `std::fabs` because it operates on the bit pattern directly.
- Use `FastAbs` in performance-sensitive inner loops where the semantics above are acceptable.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::FastAbs;

    int si = -42;
    unsigned ui = 42u;
    float f = -3.14f;
    double d = -2.718281828459045;

    std::cout << "FastAbs(int) = " << FastAbs(si) << '\n';           // 42
    std::cout << "FastAbs(unsigned) = " << FastAbs(ui) << '\n';     // 42
    std::cout << "FastAbs(float) = " << FastAbs(f) << '\n';         // 3.14
    std::cout << "FastAbs(double) = " << FastAbs(d) << '\n';        // 2.71828...

    // NaN handling: sign bit cleared but payload preserved
    float nanf = std::numeric_limits<float>::quiet_NaN();
    std::cout << "FastAbs(NaN) is NaN: " << std::boolalpha << std::isnan( FastAbs(nanf) ) << '\n';

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::FastAbs( 0u ) == 0u );
static_assert( Harlinn::Math::FastAbs( -1 ) == 1 );
static_assert( Harlinn::Math::FastAbs( -1.0f ) == 1.0f );

// Note: avoid asserting on INT_MIN since behaviour may be undefined
```

## See also

- `Abs`, `SignBit`, `CopySign` for related operations.

---

Created for the Harlinn.Math library documentation.
