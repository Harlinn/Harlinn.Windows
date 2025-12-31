# IsInf

## Summary

`IsInf` determines whether a value (or any of several values) is positive or negative infinity.

Overloads are provided for integer and floating-point types as well as a variadic template to test multiple values.

## Declaration

```cpp
// integer overload
template<IntegerType T>
constexpr inline bool IsInf(T val) noexcept;

// floating-point overload
template<FloatingPointType T>
constexpr inline bool IsInf(T val) noexcept;

// variadic overload
template<ArithmeticType T, ArithmeticType ... Args>
constexpr inline bool IsInf(T val, Args ... args) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- For integer types `IsInf` always returns `false` because integer types cannot represent infinity.
- For floating-point types:
  - In constant-evaluation contexts the implementation uses the library's bit-level helpers to detect infinity (`Internal::IsInfImpl`).
  - At runtime it normally forwards to `std::isinf` for `double`; for `float` it may use the internal bit-based check for performance and constexpr consistency.
- The variadic overload returns `true` if any of the provided arguments is infinite; otherwise it returns `false`.

## Notes

- Use `IsInf` when you need a constexpr-capable, type-generic infinity check that works uniformly for single and multiple arguments.
- Positive and negative infinity both yield `true`.

## Examples

Runtime example:

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::IsInf;

    double posInf = std::numeric_limits<double>::infinity();
    double negInf = -std::numeric_limits<double>::infinity();
    float finiteF = 3.14f;
    int i = 123;

    std::cout << std::boolalpha;
    std::cout << "IsInf(posInf) = " << IsInf(posInf) << '\n'; // true
    std::cout << "IsInf(negInf) = " << IsInf(negInf) << '\n'; // true
    std::cout << "IsInf(finiteF) = " << IsInf(finiteF) << '\n'; // false
    std::cout << "IsInf(i) = " << IsInf(i) << " (integers are never infinite)\n";

    // Variadic: returns true if any argument is infinite
    std::cout << "IsInf(finiteF, posInf, i) = " << IsInf(finiteF, posInf, i) << '\n'; // true

    return 0;
}
```

Compile-time example (constexpr-friendly):

```cpp
#include "Harlinn/Math/Math.h"

static_assert(!Harlinn::Math::IsInf( 0 )); // integer -> false
static_assert(!Harlinn::Math::IsInf( 1.0 )); // finite double -> false
constexpr double myInf = Harlinn::Math::Constants<double>::Infinity;
static_assert( Harlinn::Math::IsInf( myInf ) );
```

## See also

- `IsNaN`, `IsFinite` — related predicates for special floating-point values.

---

Created for the Harlinn.Math library documentation.
