# signum

## Summary

`signum` returns the sign of a value.

- For `bool` or unsigned integer types it returns `0` or `1` of the same type.
- For signed integer types it returns `-1`, `0` or `1` of the same type.
- For floating-point types it returns `-1.0`, `0.0` or `1.0` of the same floating type and is implemented using bit-level checks so it is constexpr and handles signed zero correctly.

The functions are `constexpr` and `noexcept`.

## Declarations

- Unsigned integer or `bool`:

```cpp
template<UnsignedIntegerOrBooleanType T>
constexpr inline T signum(T val) noexcept;
```

- Signed integer:

```cpp
template<SignedIntegerType T>
constexpr inline T signum(T val) noexcept;
```

- Floating point:

```cpp
template<FloatingPointType T>
constexpr inline T signum(T val) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- Unsigned / bool overload: returns `static_cast<T>(val != 0 ? 1 : 0)`.
- Signed integer overload: returns `-1` if `val < 0`, `1` if `val > 0`, otherwise `0`.
- Floating-point overload: inspects the raw bit pattern via `std::bit_cast` to determine magnitude and sign. It returns `0.0` for both `+0.0` and `-0.0`, `1.0` when magnitude is nonzero and sign bit is clear, and `-1.0` when magnitude is nonzero and sign bit is set. This avoids calling branchy math functions and is `constexpr`.

## Notes

- Use `signum` when you need the sign as the same type as the input and want constexpr / bit-exact behavior for floating-point values.
- For floating-point inputs this does not distinguish NaN; NaN has nonzero fraction bits and will be treated as nonzero and its sign bit (if any) determines the returned sign.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <bit>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::signum;

    // bool and unsigned
    bool b = true;
    unsigned u = 5;
    std::cout << "signum(bool true): " << signum(b) << '\n';            // prints 1
    std::cout << "signum(unsigned 5): " << signum(u) << '\n';         // prints 1

    // signed integers
    int i1 = -10;
    int i2 = 0;
    int i3 = 42;
    std::cout << "signum(-10): " << signum(i1) << '\n';               // prints -1
    std::cout << "signum(0): " << signum(i2) << '\n';                 // prints 0
    std::cout << "signum(42): " << signum(i3) << '\n';                // prints 1

    // floating point
    float fpos = 3.14f;
    float fneg = -2.5f;
    float fzero = 0.0f;
    float fnegzero = -0.0f;
    std::cout << "signum(3.14f): " << signum(fpos) << '\n';          // prints 1
    std::cout << "signum(-2.5f): " << signum(fneg) << '\n';          // prints -1
    std::cout << "signum(+0.0f): " << signum(fzero) << '\n';         // prints 0
    std::cout << "signum(-0.0f): " << signum(fnegzero) << '\n';      // prints 0

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert(Harlinn::Math::signum(true) == true);
static_assert(Harlinn::Math::signum<unsigned>(0u) == 0u);
static_assert(Harlinn::Math::signum<int>(-5) == -1);
static_assert(Harlinn::Math::signum<int>(0) == 0);
static_assert(Harlinn::Math::signum<float>(1.0f) == 1.0f);
static_assert(Harlinn::Math::signum<float>(-0.0f) == 0.0f);
```

## See also

- `IsZero`, `IsSameValue` for related utilities.

---

Created for the Harlinn.Math library documentation.
