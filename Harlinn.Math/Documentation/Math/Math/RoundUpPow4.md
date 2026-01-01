# RoundUpPow4

Description

`RoundUpPow4` rounds an integer value up to the next power of four. If the input is already an exact power of four the same value is returned. The function is a thin wrapper over integer-log helpers and bit operations.

Mathematical definition

For a positive integer \(v\), `RoundUpPow4` returns the smallest power of four not less than \(v\):

$$
\operatorname{RoundUpPow4}(v)=4^{\lceil\log_4 v\rceil}\,,\quad v\ge 1
$$

If \(v\) is already a power of four then

$$
\operatorname{RoundUpPow4}(v)=v
$$

Implementation notes

- The library implements the function as:

```cpp
template <typename T>
constexpr inline T RoundUpPow4( T v )
{
    return IsPowerOf4( v ) ? v : ( 1 << ( 2 * ( 1 + Log4Int( v ) ) ) );
}
```

- `Log4Int(v)` returns the integer part of the base-4 logarithm (equivalently floor(log_4 v)).
- The implementation uses bit shifting to compute powers of four efficiently.
- For values that exceed the representable range of the target type the result may overflow; callers should validate inputs when overflow must be avoided.

Examples

Basic usage with signed integers:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;

    int values[] = {1, 2, 3, 4, 5, 15, 16, 17, 63, 64, 65, 1000};
    for ( int v : values )
    {
        std::cout << "v=" << v << " -> RoundUpPow4(v)=" << RoundUpPow4( v ) << '\n';
    }
    return 0;
}
```

Expected output (approximate):

```
v=1 -> RoundUpPow4(v)=1
v=2 -> RoundUpPow4(v)=4
v=3 -> RoundUpPow4(v)=4
v=4 -> RoundUpPow4(v)=4
v=5 -> RoundUpPow4(v)=16
v=15 -> RoundUpPow4(v)=16
v=16 -> RoundUpPow4(v)=16
v=17 -> RoundUpPow4(v)=64
v=63 -> RoundUpPow4(v)=64
v=64 -> RoundUpPow4(v)=64
v=65 -> RoundUpPow4(v)=256
v=1000 -> RoundUpPow4(v)=1024
```

See also

- `RoundUpPow2` — round up to next power of two
- `IsPowerOf4` — test whether a value is an exact power of four
- `Log4Int` — integer base-4 logarithm helper
