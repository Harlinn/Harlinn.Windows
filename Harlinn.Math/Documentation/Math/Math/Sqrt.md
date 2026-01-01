# Sqrt

[Optimized basic math functions](Readme.md)/[Power and root finding functions](PowerFunctions.md)/`Sqrt`

## Summary

`Sqrt` computes the square root of a floating-point value and is `constexpr` and `noexcept`.

- For constant-evaluated contexts (`consteval`) it uses the library's constexpr implementations in `Internal::OpenLibM` so `Sqrt` can be used in compile-time expressions.
- At runtime it dispatches to efficient platform implementations (single-precision calls `sqrtf`, double-precision uses a fast SSE/standard implementation).

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Sqrt(T x) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- Returns the square root of `x`.
- When evaluated in a constant evaluation context the implementation is fully constexpr (via `Internal::OpenLibM::sqrtf` / `Internal::OpenLibM::sqrt`).
- At runtime the implementation provides performance comparable to `std::sqrt` while retaining IEEE-754 semantics.
- For negative inputs the behavior follows the underlying math implementation (for real-valued `Sqrt` it will normally return NaN for negative inputs).

## Notes

- Use `Sqrt` when you need a constexpr-capable square root that matches the library's other numeric helpers.
- For integer types prefer casting to the desired floating-point type before calling.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Sqrt;

    double d = 2.0;
    std::cout << "Sqrt(2.0) = " << std::setprecision(17) << Sqrt(d) << '\n';

    float f = 9.0f;
    std::cout << "Sqrt(9.0f) = " << Sqrt(f) << '\n';

    float neg = -1.0f;
    std::cout << "Sqrt(-1.0f) = " << Sqrt(neg) << " (NaN expected)" << '\n';

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::Sqrt( 0.0 ) == 0.0 );
static_assert( Harlinn::Math::Sqrt( 1.0f ) == 1.0f );
// Verify constexpr evaluation yields expected relation
static_assert( Harlinn::Math::Sqrt( 4.0 ) == 2.0 );
```

## See also

- `ReciprocalSqrt`, `SafeSqrt` for related square-root helpers.

