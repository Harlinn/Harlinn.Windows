# RemQuo

## Summary

`RemQuo` computes the IEEE-style remainder of the division `x / y` and additionally returns an integer `quo` that contains information about the quotient. It delegates to the library's `OpenLibM` helpers and follows the semantics of the C standard `remquo` function.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<FloatingPointType T>
constexpr inline T RemQuo( T x, T y, int* quo ) noexcept;
```

## Behavior

- Computes the IEEE remainder r = x - n*y, where n is the nearest integer to x / y (ties to even). The returned remainder lies in the interval [-|y|/2, |y|/2].
- Additionally stores an integer in `*quo` giving information about the quotient. The value stored in `quo` encodes the sign of the quotient and at least the lowest three bits of the quotient; these bits are sufficient to determine the octant of the result within a period.
- For `float` the implementation delegates to `Math::Internal::OpenLibM::remquof`; for `double` it delegates to `Math::Internal::OpenLibM::remquo`.
- The function is `noexcept` and follows the underlying `OpenLibM` semantics for special values (NaN, infinities, signed zeros).

## Notes

- `RemQuo` differs from `Remainder` by providing extra quotient information in `quo`. Use `RemQuo` when both the remainder and some bits of the quotient are needed (e.g., for trigonometric argument reduction where knowing the quadrant/octant is helpful).
- The exact contents beyond the low bits of `quo` are implementation-defined; only the sign and at least the three least-significant bits are guaranteed useful.

## Example

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::RemQuo;

    double x = 10.0;
    double y = 3.0;
    int quo = 0;

    double r = RemQuo( x, y, &quo );

    std::cout << "x = " << x << ", y = " << y << '\n';
    std::cout << "Remainder (remquo) = " << r << '\n';
    std::cout << "quo = " << quo << " (sign indicates sign of quotient; low bits contain quotient bits)" << '\n';

    // Use quo low bits to determine octant or parity if needed
    int lowBits = quo & 0x7; // at least 3 low bits are provided
    std::cout << "quo low 3 bits = " << lowBits << '\n';

    return 0;
}
```

## See also

- `Remainder` — IEEE remainder without returning quotient bits.
- `FMod`, `Mod` — floating-point remainder using truncation toward zero.

---

Created for the Harlinn.Math library documentation.
