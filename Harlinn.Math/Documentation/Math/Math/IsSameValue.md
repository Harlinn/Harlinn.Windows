# IsSameValue

[Optimized basic math functions](Readme.md)/[Classification and comparison](ClassificationAndComparison.md)/`IsSameValue`

## Summary

`IsSameValue` tests whether two values are exactly the same at the binary level.

- For floating-point types it compares the underlying bit patterns (so `+0.0f` vs `-0.0f` are different; NaN payload/sign is considered).
- For integer types it compares values with `==`.

The function is `constexpr` and `noexcept` and intended for cases where exact binary equivalence is required (testing, serialization checks, etc.).

## Declarations

- Floating-point overload:

```cpp
template<FloatingPointType T>
constexpr inline bool IsSameValue(T first, T second) noexcept;
```

- Integer overload:

```cpp
template<IntegerType T>
constexpr inline bool IsSameValue(T first, T second) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- Floating-point overload: uses `std::bit_cast` to compare the raw representation (`Int32` for `float`, `Int64` for `double`). Returns `true` only if the bit patterns match exactly.
- Integer overload: returns `first == second`.
- Works at compile time when operands are constant expressions.

## Notes

- Use `IsSameValue` when you need exact binary-equality (including sign bit and NaN payload handling).
- Do not use `IsSameValue` for numerical equality with tolerance; use epsilon comparisons for approximate equality.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <bit>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::IsSameValue;

    // integers
    int a = 42;
    int b = 42;
    std::cout << "int equal: " << IsSameValue(a, b) << '\n'; // prints 1

    // floating exact equal
    float f1 = 1.0f;
    float f2 = 1.0f;
    std::cout << "float equal: " << IsSameValue(f1, f2) << '\n'; // prints 1

    // +0.0 vs -0.0: bitwise different
    float posZero = 0.0f;
    float negZero = -0.0f;
    std::cout << "+0 == -0 (IsSameValue): " << IsSameValue(posZero, negZero) << '\n'; // prints 0

    // NaNs: payload matters (example with two different NaN bit patterns)
    float nan1 = std::bit_cast<float>(0x7fc00000u); // quiet NaN, payload 0
    float nan2 = std::bit_cast<float>(0x7fc00001u); // quiet NaN, different payload
    std::cout << "both arenan (std::isnan): " << std::isnan(nan1) << ", " << std::isnan(nan2) << '\n';
    std::cout << "NaNs bitwise equal (IsSameValue): " << IsSameValue(nan1, nan2) << '\n'; // prints 0

    // identical NaNs (same bit pattern)
    float nanSameA = std::bit_cast<float>(0x7fc00000u);
    float nanSameB = std::bit_cast<float>(0x7fc00000u);
    std::cout << "NaNs identical bitwise: " << IsSameValue(nanSameA, nanSameB) << '\n'; // prints 1

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert(Harlinn::Math::IsSameValue(1, 1));               // integers OK at compile time
static_assert(Harlinn::Math::IsSameValue(1.0f, 1.0f));         // floats can be constexpr-compared
static_assert(!Harlinn::Math::IsSameValue(0.0f, -0.0f));       // bitwise different
```

## See also

- `IsZero`, `IsNaN` in the same header for related floating-point utilities.
