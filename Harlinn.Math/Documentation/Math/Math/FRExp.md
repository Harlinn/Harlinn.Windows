# FRExp

[Optimized basic math functions](Readme.md)/[Floating point manipulation functions](FloatingPointManipulationFunctions.md)/`FRExp`

## Summary

`FRExp` decomposes a floating-point value into a normalized fraction and an integral power of two. It mirrors the behavior of the C `frexp` family but is `constexpr`-friendly and available for both `float` and `double` in the `Harlinn::Math` namespace.

There are three overloads:
- `std::pair<T,int> FRExp(T val)`: returns fraction in `.first` and exponent in `.second`.
- `T FRExp(T val, int* exp)`: stores exponent via pointer and returns fraction.
- `T FRExp(T val, int& exp)`: stores exponent via reference and returns fraction.

The returned fraction `f` and exponent `e` satisfy: value = f * 2^e, and `f` is in the interval (-1, -0.5] or [0.5, 1) for non-zero values. For zero both fraction and exponent are zero.

## Declaration

```cpp
// returns pair<fraction, exponent>
template<FloatingPointType T>
constexpr inline std::pair<T, int> FRExp(T val) noexcept;

// stores exponent via pointer and returns fraction
template<FloatingPointType T>
constexpr inline T FRExp(T val, int* exp) noexcept;

// stores exponent via reference and returns fraction
template<FloatingPointType T>
constexpr inline T FRExp(T val, int& exp) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- For non-zero finite `val`, the function returns a fraction `f` and exponent `e` such that `val == f * 2^e` and `|f|` is in [0.5, 1) (except for denormals where `f` may be subnormal while `e` is adjusted accordingly).
- If `val` is zero, both `f` and `e` are zero.
- For `NaN` and infinities behavior follows the underlying OpenLibM helpers used by the library.
- All overloads are `constexpr` and `noexcept` and can be used in compile-time contexts.

## Notes

- Use `FRExp` when you need the exponent and a normalized mantissa separately, for example in numerical algorithms, scaling, or range reduction.
- The implementation delegates to `Internal::OpenLibM::frexpf`/`frexp` for `float`/`double` respectively in consteval/constexpr contexts and matches standard semantics.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <utility>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::FRExp;

    // pair overload
    auto pd = FRExp( 8.0 ); // 8.0 = 0.5 * 2^4
    std::cout << "FRExp(8.0) -> fraction=" << pd.first << ", exponent=" << pd.second << '\n';

    // pointer overload
    int exp = 0;
    float frac = FRExp( 1.5f, &exp ); // 1.5f = 0.75 * 2^1
    std::cout << "FRExp(1.5f, &exp) -> fraction=" << frac << ", exponent=" << exp << '\n';

    // reference overload
    int e2 = 0;
    double f2 = FRExp( -0.125, e2 ); // -0.125 = -0.5 * 2^-2
    std::cout << "FRExp(-0.125, e2) -> fraction=" << f2 << ", exponent=" << e2 << '\n';

    // zero
    auto pz = FRExp( 0.0 );
    std::cout << "FRExp(0.0) -> fraction=" << pz.first << ", exponent=" << pz.second << '\n';

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

constexpr auto p = Harlinn::Math::FRExp( 8.0 );
static_assert( p.first == 0.5 );
static_assert( p.second == 4 );

constexpr int e = [](){ int ex=0; auto f = Harlinn::Math::FRExp( 1.5, &ex ); return ex; }();
static_assert( e == 1 );
```

## See also

- `LDExp` / `ScaleBN`: compose value from fraction and exponent.
- `FRExp` is complementary to `NextUp`/`NextDown` when examining representable ranges.

