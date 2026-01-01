# FindInterval

Description

`FindInterval` finds the largest index `i` in the range \([0, sz-2]\) for which a user-supplied boolean predicate `pred(i)` is true. This function is suitable for locating an interval in a sorted array (for example, to find `i` such that `edges[i] <= x < edges[i+1]`) using a binary-search style predicate without exposing the search logic.

Mathematical specification

If we denote the predicate by \(P(i)\), then `FindInterval` returns

$$
\text{FindInterval}(sz, P) = \max\{i \in [0, sz-2]\;:\;P(i) = \text{true}\},
$$

with the convention that the result is clamped to the interval \([0, sz-2]\) if the predicate is always false or always true.

Function signature (C++)

```cpp
template<typename Predicate>
constexpr inline size_t FindInterval( size_t sz, const Predicate& pred )
```

Parameters

- `sz`: the size parameter (typically the number of points in a sorted array; the function searches indices from `0` to `sz-2`).
- `pred`: a callable taking a single `size_t` index and returning a `bool`.

Return value

Returns the largest index `i` in the range `[0, sz-2]` such that `pred(i)` is `true`. The return value is always in the closed range `[0, sz-2]`.

Complexity

The implementation uses a binary-search like algorithm and runs in O(log sz) predicate evaluations.

Usage notes

- Typical usage is to pass the size of a sorted `edges` array of length `n` and a predicate that compares the query value to the breakpoints. The function then returns an index `i` such that `edges[i]` is the lower bound of the interval containing the query (except at boundaries).
- For arrays of length `n`, valid returned indices are in `[0, n-2]`. When searching outside the range of the breakpoints, the caller should handle the boundary cases appropriately.

Example

Find the index `i` such that `edges[i] <= x < edges[i+1]` for a sorted vector `edges` of length `n >= 2`:

```cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include "Harlinn/Math/Math.h"

int main()
{
    using namespace Harlinn::Math;

    // Sorted breakpoints (edges) of length n
    std::vector<double> edges{ 0.0, 1.5, 3.0, 4.2, 10.0 };
    double x = 2.7; // query value

    size_t n = edges.size();
    if ( n < 2 )
    {
        std::cerr << "edges must contain at least two points\n";
        return 1;
    }

    // Predicate: true when edges[i] <= x
    auto pred = [&]( size_t i ) { return edges[i] <= x; };

    size_t idx = FindInterval( n, pred );

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "x = " << x << " is in interval [" << edges[idx] << ", " << edges[idx+1] << ") at index i=" << idx << "\n";

    return 0;
}
```

Example behavior

- With `edges = {0.0, 1.5, 3.0, 4.2, 10.0}` and `x = 2.7`, the predicate is true for indices `0` and `1` and false for `2` and above, so `FindInterval` returns `1` (the largest index with `edges[i] <= x`).
- If `x` is less than `edges[0]`, the predicate is false for all indices and the function returns `0` (clamped). If `x` is greater or equal to `edges[n-1]`, the predicate is true for all indices and the function returns `n-2` (clamped).

See also

- Binary-search style helpers and usage patterns in `Harlinn::Math` utility functions.
