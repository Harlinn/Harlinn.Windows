# Clamp

## Summary

`Clamp` constrains a value to lie within a specified inclusive range [minimumValue, maximumValue]. If the value is less than the minimum, the minimum is returned; if greater than the maximum, the maximum is returned; otherwise the original value is returned.

(Defined in `Harlinn::Math`, header: `Harlinn.Math\include\Harlinn\Math\Math.h`.)

## Declaration

```cpp
template<ArithmeticType T1, ArithmeticType T2, ArithmeticType T3>
constexpr inline T1 Clamp( T1 value, T2 minimumValue, T3 maximumValue ) noexcept;
```

## Behavior

- The function compares `value` to `minimumValue` and `maximumValue` after converting `minimumValue`/`maximumValue` to `T1` for comparison.
- If `value < static_cast<T1>(minimumValue)` the function returns `static_cast<T1>(minimumValue)`.
- If `static_cast<T1>(maximumValue) < value` the function returns `static_cast<T1>(maximumValue)`.
- Otherwise the original `value` is returned.
- The function is `constexpr` and `noexcept` when the underlying operations are.

## Notes

- `Clamp` requires that the `<` operator is defined for the involved types. Mixing types is supported via implicit/static casts but be mindful of narrowing or precision loss when converting values to `T1`.
- For floating-point inputs use `Clamp` when bounding values; for integer ranges prefer matching integer types to avoid implicit conversions.

## Examples

Runtime example:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h" // adjust include path as needed

int main()
{
    using Harlinn::Math::Clamp;

    double x = 3.7;
    std::cout << "Clamp(3.7, 0.0, 5.0) = " << Clamp( x, 0.0, 5.0 ) << '\n';   // 3.7
    std::cout << "Clamp(3.7, 4.0, 10.0) = " << Clamp( x, 4.0, 10.0 ) << '\n'; // 4.0
    std::cout << "Clamp(3.7, -1.0, 3.0) = " << Clamp( x, -1.0, 3.0 ) << '\n'; // 3.0

    int i = -5;
    std::cout << "Clamp(-5, 0, 10) = " << Clamp( i, 0, 10 ) << '\n'; // 0

    // Mixed types: return type follows first template parameter
    float f = 2.5f;
    std::cout << "Clamp(2.5f, 0, 2) = " << Clamp( f, 0, 2 ) << '\n'; // 2.0f (clamped and converted)

    return 0;
}
```

Compile-time example:

```cpp
#include "Harlinn/Math/Math.h"

static_assert( Harlinn::Math::Clamp( 5, 0, 10 ) == 5 );
static_assert( Harlinn::Math::Clamp( -1, 0, 10 ) == 0 );
constexpr double clamped = Harlinn::Math::Clamp( 3.14, 0.0, 3.0 );
static_assert( clamped == 3.0 );
```

## See also

- `Min`, `Max` — for single-sided comparisons.
- `Clamp` is often used with `Lerp`, `Clamp` + `Normalize`, and range-checking utilities.

---

Created for the Harlinn.Math library documentation.
