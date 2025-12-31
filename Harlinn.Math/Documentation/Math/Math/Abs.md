# Abs

## Summary

`Abs` computes the absolute value of its argument. The library provides overloads for signed and unsigned integers, floating-point types, and also `FastAbs` variants that use bit-level or branchless implementations for performance.

- For signed integers `Abs` returns the absolute value (undefined if the result cannot be represented in the type).
- For unsigned integers `Abs` simply returns the value unchanged.
- For floating-point types `Abs` is `constexpr`-friendly and uses internal helpers in `consteval` contexts; at runtime it delegates to optimized implementations (`std::fabsf`, `Internal::OpenLibM::fabs`, or bit manipulations for `FastAbs`).

## Declarations

```cpp
template<SignedIntegerType T>
constexpr inline T Abs(T val) noexcept;

template<UnsignedIntegerType T>
constexpr inline T Abs(T val) noexcept;

template<FloatingPointType T>
constexpr inline T Abs(T val) noexcept;

template<UnsignedIntegerType T>
constexpr inline T FastAbs(T val) noexcept;

template<SignedIntegerType T>
constexpr inline T FastAbs(T val) noexcept;

template<FloatingPointType T>
constexpr inline T FastAbs(T val) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- Integer `Abs`:
  - Signed integers: returns the absolute value; behavior is undefined if the negated value cannot be represented (e.g. `Abs(INT_MIN)`).
  - Unsigned integers: returns the argument unchanged.
- Floating-point `Abs`:
  - In `consteval` contexts the implementation uses `Internal::AbsImpl` which is bit-based and constexpr-capable.
  - At runtime `float` uses `std::fabsf` and `double` uses internal helpers for predictable semantics and performance.
- `FastAbs` variants:
  - For integers `FastAbs` uses a branchless algorithm.
  - For floating-point types `FastAbs` uses bit masking to clear the sign bit, which is faster than library calls but behaves the same for non-NaN/Inf values.

## Notes

- Prefer `FastAbs` when you need the fastest possible absolute-value calculation and you are aware of corner cases (NaNs keep their sign bit semantics in IEEE representation).
- For safety with signed integers, ensure inputs are within a range where negation is representable (avoid `INT_MIN` for a 2's complement signed integer type).

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Abs;
    using Harlinn::Math::FastAbs;

    int si = -42;
    unsigned ui = 42u;
    float f = -3.14f;
    double d = -2.718281828459045;

    std::cout << "Abs(int) = " << Abs(si) << '\n';           // 42
    std::cout << "Abs(unsigned) = " << Abs(ui) << '\n';     // 42
    std::cout << "Abs(float) = " << Abs(f) << '\n';         // 3.14
    std::cout << "FastAbs(float) = " << FastAbs(f) << '\n'; // 3.14
    std::cout << "Abs(double) = " << Abs(d) << '\n';        // 2.71828...

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::Abs( -1 ) == 1 );
static_assert( Harlinn::Math::Abs( 0u ) == 0u );
static_assert( Harlinn::Math::Abs( -1.0f ) == 1.0f );

// For signed integers beware of INT_MIN: behavior is undefined
```

## See also

- `FastAbs`, `SignBit`, `CopySign` for related bit-level operations.

---

Created for the Harlinn.Math library documentation.
