# IsZero

[Optimized basic math functions](Readme.md)/[Classification and comparison](ClassificationAndComparison.md)/`IsZero`

## Summary

`IsZero` tests whether a value represents zero.

- For floating-point types it checks the raw bit pattern to determine if the value is either `+0.0` or `-0.0` (both are treated as zero).
- For integer types it compares to `0`.

The function is `constexpr` and `noexcept`.

## Declarations

- Floating-point overload:

```cpp
template<FloatingPointType T>
constexpr inline bool IsZero(T x) noexcept;
```

- Integer overload:

```cpp
template<IntegerType T>
constexpr inline bool IsZero(T x) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- Floating-point overload: obtains the underlying unsigned integer representation via `std::bit_cast` and masks away the sign bit. If the remaining bits are zero the value is considered zero (this correctly classifies both `+0.0` and `-0.0` as zero). NaNs and infinities are not zero.
- Integer overload: returns `x == 0`.
- Works at compile time when operands are constant expressions.

## Notes

- Use `IsZero` when you need to detect exact zero including signed zero handling.
- Do not use `IsZero` to detect values "close to zero"; use an epsilon-based comparison instead.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <bit>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::IsZero;

    // integers
    int i1 = 0;
    int i2 = 1;
    std::cout << "int 0: " << IsZero(i1) << '\n'; // prints 1
    std::cout << "int 1: " << IsZero(i2) << '\n'; // prints 0

    // floating +0 and -0
    float pos = 0.0f;
    float neg = -0.0f;
    std::cout << "+0 is zero: " << IsZero(pos) << '\n'; // prints 1
    std::cout << "-0 is zero: " << IsZero(neg) << '\n'; // prints 1

    // NaN and infinity are not zero
    float nan = std::numeric_limits<float>::quiet_NaN();
    float inf = std::numeric_limits<float>::infinity();
    std::cout << "NaN is zero: " << IsZero(nan) << '\n'; // prints 0
    std::cout << "Inf is zero: " << IsZero(inf) << '\n'; // prints 0

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert(Harlinn::Math::IsZero(0));                // integer zero
static_assert(Harlinn::Math::IsZero(0.0f));             // floating +0
static_assert(Harlinn::Math::IsZero(-0.0f));            // floating -0
static_assert(!Harlinn::Math::IsZero(1.0f));            // non-zero float
```

## See also

- `IsSameValue`, `IsNaN` for related floating-point utilities.

