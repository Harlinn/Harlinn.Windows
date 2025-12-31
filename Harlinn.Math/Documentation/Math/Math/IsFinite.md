# IsFinite

## Summary

`IsFinite` determines whether a value (or any of several values) is a finite numeric value (not infinite and not NaN).

Overloads are provided for integer and floating-point types as well as a variadic template to test multiple values.

## Declaration

```cpp
// integer overload
template<IntegerType T>
constexpr inline bool IsFinite(T val) noexcept;

// floating-point overload
template<FloatingPointType T>
constexpr inline bool IsFinite(T val) noexcept;

// variadic overload
template<ArithmeticType T, ArithmeticType ... Args>
constexpr inline bool IsFinite(T val, Args ... args) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- For integer types `IsFinite` always returns `true` because integer types cannot represent infinity or NaN.
- For floating-point types the function returns `true` when the argument is a normal, subnormal or zero value, and `false` when the argument is `+/-infinity` or `NaN`.
- In constant-evaluation contexts the implementation uses the library's constexpr helpers (`Internal::OpenLibM::isfinite`) so the function can be used in `static_assert` and other compile-time checks.
- The variadic overload returns `true` only if all provided arguments are finite; it returns `false` if any argument is infinite or NaN.

## Notes

- Use `IsFinite` when you need a constexpr-capable, type-generic finiteness test that behaves consistently for `float` and `double` and for integer types.
- For checking specifically `NaN` or `Infinity` use `IsNaN` and `IsInf` respectively.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <limits>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::IsFinite;

    double finiteD = 3.14159;
    double infD = std::numeric_limits<double>::infinity();
    double nanD = std::numeric_limits<double>::quiet_NaN();
    int i = 42;

    std::cout << std::boolalpha;
    std::cout << "IsFinite(finiteD) = " << IsFinite(finiteD) << '\n'; // true
    std::cout << "IsFinite(+inf) = " << IsFinite(infD) << '\n';       // false
    std::cout << "IsFinite(NaN) = " << IsFinite(nanD) << '\n';        // false
    std::cout << "IsFinite(i) = " << IsFinite(i) << " (integers always finite)\n";

    // Variadic: returns false if any argument is not finite
    std::cout << "IsFinite(finiteD, i) = " << IsFinite(finiteD, i) << '\n'; // true
    std::cout << "IsFinite(finiteD, infD) = " << IsFinite(finiteD, infD) << '\n'; // false

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::IsFinite( 0 ) );                 // integer -> true
static_assert( Harlinn::Math::IsFinite( 1.0 ) );               // finite double -> true
constexpr double myInf = Harlinn::Math::Constants<double>::Infinity;
static_assert( !Harlinn::Math::IsFinite( myInf ) );            // compile-time infinity -> false
```

## See also

- `IsNaN`, `IsInf` — related predicates for special floating-point values.

---

Created for the Harlinn.Math library documentation.
