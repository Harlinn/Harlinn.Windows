# IsPowerOf4

Description

`IsPowerOf4` tests whether an integer value is an exact power of 4.

Mathematical definition

An integer \(v\) is a power of 4 if there exists an integer \(k \ge 0\) such that

$$
v = 4^{k}.
$$

Equivalently, in binary representation a (positive) power of 4 has exactly one bit set and that set-bit is at an even position (counting from 0).

Function signature (C++)

```cpp
template <typename T>
constexpr inline bool IsPowerOf4( T v )
```

Parameters

- `v`: an integral value to test. The function behaves as expected for signed and unsigned integer types; non-positive values are not powers of 4.

Return value

Returns `true` if `v` equals \(4^{k}\) for some integer \(k \ge 0\), otherwise returns `false`.

Properties and notes

- Domain: integer values.
- All valid powers of 4 are positive: \(1 = 4^0, 4 = 4^1, 16 = 4^2, \dots\).
- Zero and negative values are not powers of 4.
- A common bitwise test for powers of 4 uses two checks:
  1. Exactly one bit set: \((v \& (v-1)) == 0\).
  2. Set bit at even position: \((v \& 0x5555...5) != 0\) (mask with alternating 1 bits).

Example

Simple example demonstrating usage with signed integers:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;

    int values[] = { -1, 0, 1, 2, 4, 15, 16, 64, 100 };

    for ( int v : values )
    {
        std::cout << v << " -> " << ( IsPowerOf4( v ) ? "true" : "false" ) << '\n';
    }

    return 0;
}
```

Expected output (approximate):

```
-1 -> false
0 -> false
1 -> true
2 -> false
4 -> true
15 -> false
16 -> true
64 -> true
100 -> false
```

See also

- `Log2Int` � helpers for integer logarithms
- Bitwise techniques for power-of-two and power-of-four detection
