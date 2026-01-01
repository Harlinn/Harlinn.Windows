# Cbrt

[Optimized basic math functions](Readme.md)/[Power and root finding functions](PowerFunctions.md)/`Cbrt`

## Summary

`Cbrt` computes the cube root of a floating-point value. The function is `constexpr` and `noexcept`, and supports evaluation in constant-evaluation contexts as well as efficient runtime execution.

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T Cbrt(T x) noexcept;
```

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Behavior

- When evaluated in a constant-evaluation context (`consteval`) the implementation calls the library's constexpr helpers (`Internal::OpenLibM::cbrtf` for `float`, `Internal::OpenLibM::cbrt` for `double`).
- At runtime:
  - For `float` the implementation currently calls `Math::Internal::OpenLibM::cbrtf`.
  - For `double` the runtime implementation uses a fast platform-aware path (SSE helper) to compute the cube root.
- The function adheres to IEEE-754 semantics: it preserves sign for negative inputs (i.e. `Cbrt(-8.0)` returns `-2.0`) and propagates NaN/infinity according to the underlying math implementation.

## Notes

- Use `Cbrt` when you need a constexpr-capable cube-root function that behaves consistently between compile-time and runtime.
- For most inputs the runtime path provides performance comparable to standard library implementations while enabling constexpr evaluation when required.

## Examples

Runtime example (prints results):

```cpp
#include <iostream>
#include <iomanip>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Cbrt;

    double d = 27.0;
    std::cout << std::setprecision(17);
    std::cout << "Cbrt(27.0) = " << Cbrt(d) << " (expected 3)\n";

    float f = -8.0f;
    std::cout << "Cbrt(-8.0f) = " << Cbrt(f) << " (expected -2)\n";

    float nan = std::numeric_limits<float>::quiet_NaN();
    std::cout << "Cbrt(NaN) = " << Cbrt(nan) << " (NaN expected)\n";

    return 0;
}
```

Compile-time example using `static_assert`:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::Cbrt( 27.0 ) == 3.0 );
static_assert( Harlinn::Math::Cbrt( -8.0f ) == -2.0f );
```

## See also

- `Sqrt`, `ReciprocalSqrt` for related root operations.

