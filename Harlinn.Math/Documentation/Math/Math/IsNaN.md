# IsNaN

[Optimized basic math functions](Readme.md)/[Classification and comparison](ClassificationAndComparison.md)/`IsNaN`

## Summary

`IsNaN` tests whether a value (or any of several values) is a not-a-number (NaN) value.

The library provides overloads for integer and floating-point types and a variadic template to test multiple values.

## Declaration

```cpp
// integer overload
template<IntegerType T>
constexpr inline bool IsNaN(T val) noexcept;

// floating-point overload
template<FloatingPointType T>
constexpr inline bool IsNaN(T val) noexcept;

// variadic overload
template<ArithmeticType T, ArithmeticType ... Args>
constexpr inline bool IsNaN(T val, Args ... args) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- For integer types `IsNaN` always returns `false` because integers cannot represent NaN.
- For floating-point types:
  - In constant-evaluation contexts (`consteval`) the implementation uses the library's bit-level helpers to determine NaN without invoking runtime library functions.
  - At runtime it typically forwards to `std::isnan` (except where the internal implementation is used for `float`/`double` in consteval paths).
- The variadic overload returns `true` if any of the provided arguments is NaN; otherwise it returns `false`.

## Notes

- Use `IsNaN` when you need a constexpr-capable, type-generic NaN test that works uniformly for single and multiple arguments.
- Prefer calling with floating-point arguments; integer arguments are allowed and will always yield `false` (or be skipped by the variadic evaluation).

## Examples

Runtime example:

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::IsNaN;

    double d = std::numeric_limits<double>::quiet_NaN();
    float f = 1.0f / 0.0f; // +inf, not NaN
    int i = 42;

    std::cout << std::boolalpha;
    std::cout << "IsNaN(d) = " << IsNaN(d) << '\n'; // true
    std::cout << "IsNaN(f) = " << IsNaN(f) << " (false for infinity)\n";
    std::cout << "IsNaN(i) = " << IsNaN(i) << " (integers are never NaN)\n";

    // Variadic: returns true if any argument is NaN
    std::cout << "IsNaN(d, f, i) = " << IsNaN(d, f, i) << '\n'; // true

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

static_assert(!Harlinn::Math::IsNaN( 0 ));            // integer -> false
static_assert(!Harlinn::Math::IsNaN( 1.0 ));          // finite double -> false
// Note: static constexpr NaN value required for a true static_assert on NaN checks
constexpr double myNaN = Harlinn::Math::Constants<double>::NaN;
static_assert( Harlinn::Math::IsNaN( myNaN ) );
```

## See also

- `IsInf`, `IsFinite`: checks for infinity and finiteness.
