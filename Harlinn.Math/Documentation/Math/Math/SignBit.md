# SignBit

## Summary

`SignBit` tests whether a value has a negative sign bit. Overloads exist for signed and unsigned integer types and for floating-point types. The function is `constexpr` and `noexcept` where applicable and is usable in compile-time contexts.

## Declarations

```cpp
template<SignedIntegerType T>
constexpr inline bool SignBit(T val) noexcept;

template<UnsignedIntegerType T>
constexpr inline bool SignBit(T val) noexcept;

template<FloatingPointType T>
constexpr inline bool SignBit(T val) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- For signed integer types, `SignBit` returns true if the integer is negative (i.e. the sign bit of the two's-complement representation is set).
- For unsigned integer types, `SignBit` always returns `false` because unsigned types do not have a sign bit.
- For floating-point types, `SignBit` inspects the IEEE-754 sign bit using bit-level operations and returns `true` for negative values (including `-0.0`) and `false` for non-negative values. It is `constexpr` and faster than `std::signbit` in many cases.

Notes:
- For floating-point NaNs the sign bit may be set; `SignBit` will reflect that sign bit.
- Use `SignBit` when you need a fast, bit-exact test for negativity that is valid in `consteval`/`constexpr` contexts.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::SignBit;

    int si = -42;
    unsigned ui = 42u;
    float fpos = 3.14f;
    float fneg = -3.14f;
    float pzero = 0.0f;
    float nzero = -0.0f;

    std::cout << std::boolalpha;
    std::cout << "SignBit(-42) = " << SignBit(si) << '\n';   // true
    std::cout << "SignBit(42u) = " << SignBit(ui) << '\n';   // false
    std::cout << "SignBit(3.14f) = " << SignBit(fpos) << '\n'; // false
    std::cout << "SignBit(-3.14f) = " << SignBit(fneg) << '\n';// true
    std::cout << "SignBit(+0.0f) = " << SignBit(pzero) << '\n';// false
    std::cout << "SignBit(-0.0f) = " << SignBit(nzero) << '\n';// true

    // NaN with sign bit set
    float nanneg = -std::numeric_limits<float>::quiet_NaN();
    std::cout << "SignBit(-NaN) = " << SignBit(nanneg) << '\n'; // true (sign bit preserved)

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::SignBit( -1 ) );
static_assert( !Harlinn::Math::SignBit( 1u ) );
static_assert( !Harlinn::Math::SignBit( 0.0 ) );
static_assert( Harlinn::Math::SignBit( -0.0 ) );
```

## See also

- `FastSignBit` (fast variant), `IsZero`, `IsNaN`, `CopySign` for related sign and classification utilities.

---

Created for the Harlinn.Math library documentation.
