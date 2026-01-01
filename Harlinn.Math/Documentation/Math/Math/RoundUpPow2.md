# RoundUpPow2

Description

`RoundUpPow2` rounds an integer value up to the next power of two. If the input is already a power of two, the same value is returned. For non-positive inputs behavior depends on the overload: for signed types the result may be implementation-defined, callers should pass positive values when using the function.

Mathematical definition

For a positive integer \(v\), `RoundUpPow2(v)` returns the smallest power of two not less than \(v\):

$$
\operatorname{RoundUpPow2}(v) = 2^{\lceil \log_2 v \rceil}\,,\quad v \ge 1
$$

If \(v\) is already a power of two, then

$$
\operatorname{RoundUpPow2}(v) = v
$$

Function signatures (C++)

```cpp
constexpr inline Int32 RoundUpPow2( Int32 v );
constexpr inline Int64 RoundUpPow2( Int64 v );
```

Notes

- The function uses an efficient bit-manipulation helper `NextPowerOfTwo` to compute the result.
- For values larger than the largest representable power of two for the type, the result may overflow; callers should validate inputs if overflow must be avoided.

Examples

Basic usage with 32-bit integers:

```cpp
#include <iostream>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;

    int values[] = {1, 2, 3, 5, 16, 17, 31, 32, 33, 1000 };

    for ( int v : values )
    {
        std::cout << "v=" << v << " -> RoundUpPow2(v)=" << RoundUpPow2( v ) << '\n';
    }

    return 0;
}
```

Expected output (approximate):

```
v=1 -> RoundUpPow2(v)=1
v=2 -> RoundUpPow2(v)=2
v=3 -> RoundUpPow2(v)=4
v=5 -> RoundUpPow2(v)=8
v=16 -> RoundUpPow2(v)=16
v=17 -> RoundUpPow2(v)=32
v=31 -> RoundUpPow2(v)=32
v=32 -> RoundUpPow2(v)=32
v=33 -> RoundUpPow2(v)=64
v=1000 -> RoundUpPow2(v)=1024
```

See also

- `NextPowerOfTwo` — helper used by `RoundUpPow2`
- `RoundUpPow4` — rounds up to next power of 4
