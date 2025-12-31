# IsNormal

## Summary

`IsNormal` tests whether a value (or any of several values) is a normal floating-point number. A normal value is finite, non-zero, and not subnormal (denormal).

Overloads exist for integer and floating-point types and a variadic template to test multiple values.

## Declaration

```cpp
// integer overload
template<IntegerType T>
constexpr inline bool IsNormal(T val) noexcept;

// floating-point overload
template<FloatingPointType T>
constexpr inline bool IsNormal(T val) noexcept;

// variadic overload
template<ArithmeticType T, ArithmeticType ... Args>
constexpr inline bool IsNormal(T val, Args ... args) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- For integer types `IsNormal` returns `true` for all non-zero values (integers are considered "normal" except zero).
- For floating-point types the function returns `true` only when the value is normal (not zero, not subnormal, not infinite, and not NaN).
- The implementation delegates to the library's constexpr-capable helpers (`Internal::OpenLibM::isnormal`) so it can be used in compile-time contexts.
- The variadic overload returns `true` only if all provided arguments are normal; it short-circuits and returns `false` if any argument is not normal.

## Notes

- Use `IsNormal` to detect values that have full precision (not denormalized) when numerical stability matters.
- To test for finiteness or NaN/infinity specifically, use `IsFinite`, `IsNaN`, or `IsInf`.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::IsNormal;

    double normal = 3.14159;
    double zero = 0.0;
    double subnormal = std::numeric_limits<double>::denorm_min();
    double inf = std::numeric_limits<double>::infinity();

    std::cout << std::boolalpha;
    std::cout << "IsNormal(3.14159) = " << IsNormal(normal) << '\n'; // true
    std::cout << "IsNormal(0.0) = " << IsNormal(zero) << '\n';        // false
    std::cout << "IsNormal(denorm_min) = " << IsNormal(subnormal) << '\n'; // false
    std::cout << "IsNormal(+inf) = " << IsNormal(inf) << '\n';         // false

    // Variadic: all must be normal
    std::cout << "IsNormal(3.14, 2.0) = " << IsNormal(3.14, 2.0) << '\n';

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::IsNormal( 1.0 ) );
static_assert( !Harlinn::Math::IsNormal( 0.0 ) );
// For denormals a constexpr denormal value is required to assert false at compile time
```

## See also

- `IsFinite`, `IsNaN`, `IsInf`, `IsZero` — related predicates for floating-point classification.

---

Created for the Harlinn.Math library documentation.
