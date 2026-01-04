# `Tuple2` vector-like API compatibility with `std::vector`

This document describes the member functions provided by the `Tuple2<DerivedT, T>` template that are conceptually compatible with portions of the `std::vector` container API. The goal is to show how `Tuple2` instances interoperate with the C++ standard library, ranges and algorithms.

Notes:
- `value_type` denotes the scalar element type `T` used by the `Tuple2` specialization.
- `DerivedT` denotes the CRTP-derived concrete type.
- `Size = 2` for `Tuple2`.

The `Tuple2` class provides a small subset of the sequence-like API that makes it convenient to use `Tuple2` objects with STL algorithms and the Ranges library.

## Common member functions and signatures

The following signatures are the typical members exposed by `Tuple2` in `VectorMath.h`.

```cpp
// element access
value_type& operator[](std::size_t index) noexcept;
constexpr value_type operator[](std::size_t index) const noexcept;
value_type& at(std::size_t index);                    // bounds-checked
const value_type& at(std::size_t index) const;        // bounds-checked

// front and back (for 2-element tuple front() == x, back() == y)
value_type& front() noexcept;
const value_type& front() const noexcept;
value_type& back() noexcept;
const value_type& back() const noexcept;

// data pointer
value_type* data() noexcept;
const value_type* data() const noexcept;

// size and capacity-like query
constexpr std::size_t size() const noexcept;          // returns 2
constexpr bool empty() const noexcept;                // returns false for Tuple2

// iterators (pointer-based)
value_type* begin() noexcept;
const value_type* begin() const noexcept;
value_type* end() noexcept;
const value_type* end() const noexcept;

// cbegin/cend/rbegin/rend can be provided via standard patterns using begin/end
// conversion to SIMD form
DerivedT::Simd ToSimd() const noexcept;               // convert to SIMD wrapper
operator DerivedT::Simd() const noexcept;             // implicit conversion to Simd
```

Notes on semantics:
- `size()` returns `2` and is `constexpr` so it can be used in compile-time contexts.
- `data()` returns a pointer suitable for interoperability with C APIs or `std::span`.
- `begin()` and `end()` return pointer iterators so `Tuple2` can be used with range-based for loops and algorithms requiring iterator pairs.

## Math and sequence relationship

`Tuple2` represents the 2D vector \((x, y)\). Many algorithms operate on the tuple as a 2-element sequence while mathematical helpers treat it as a geometric vector. For example the Euclidean norm is

\[
\|v\| = \sqrt{x^2 + y^2}
\]

This mathematical expression works naturally with the sequence API by using `data()` or `begin()` when applying standard algorithms.

## Examples demonstrating integration with the C++ standard library

Example 1: Using `std::ranges` and `std::ranges::views` to compute vector lengths from a container of `Tuple2` objects

```cpp
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cmath>

using Vector2f = Math::Vector<float,2>;

std::vector<Vector2f> points = { {1.0f, 2.0f}, {3.0f, 4.0f}, {0.0f, -1.0f} };

// create a view that projects each Tuple2 to its Euclidean length
auto lengths_view = points | std::ranges::views::transform([](auto const& p) {
    // use element access; p.x and p.y or p[0], p[1] are both fine
    return std::sqrt( p.x * p.x + p.y * p.y );
});

// consume the view into a vector
std::vector<float> lengths;
std::ranges::copy(lengths_view, std::back_inserter(lengths));

// lengths now contains { sqrt(5), 5.0, 1.0 }
```

Example 2: Using `std::transform` to translate points by a velocity vector

```cpp
#include <vector>
#include <algorithm>

using Vector2f = Math::Vector<float,2>;

Vector2f translation( 1.5f, -2.0f );
std::vector<Vector2f> pts = { {0.0f,0.0f}, {1.0f,1.0f} };

std::transform( pts.begin(), pts.end(), pts.begin(), [&](Vector2f const& p) {
    return p + translation; // operator+ is defined for Tuple2 derived types
});

// pts now contain translated positions
```

Example 3: Using `std::sort` with a custom comparator that uses `x` component

```cpp
#include <vector>
#include <algorithm>

using Vector2f = Math::Vector<float,2>;

std::vector<Vector2f> pts = { {1.0f,2.0f}, { -1.0f, 0.0f }, { 0.5f, -0.2f } };

std::sort( pts.begin(), pts.end(), [](auto const& a, auto const& b){
    return a.x < b.x; // compare by x coordinate
});
```

Example 4: Using `std::accumulate` to compute the centroid of a point set

```cpp
#include <numeric>
#include <vector>

using Vector2f = Math::Vector<float,2>;

std::vector<Vector2f> pts = { {0.0f,0.0f}, {2.0f,0.0f}, {0.0f,2.0f} };

Vector2f sum = std::accumulate( pts.begin(), pts.end(), Vector2f(0.0f, 0.0f), [](auto const& acc, auto const& p){
    return acc + p; // relies on operator+
});

Vector2f centroid = sum / static_cast<float>( pts.size() );
```

Example 5: Interop via `data()` and `std::span` for APIs expecting contiguous storage

```cpp
#include <span>

using Vector2f = Math::Vector<float,2>;

Vector2f p(1.0f, 2.0f);
std::span<float, 2> sp( p.data() ); // refers to the tuple's internal storage
// call a C-style API that expects float[2]
// c_api_process_point( sp.data() );
```

Example 6: Using `std::ranges::for_each` to mutate components

```cpp
#include <ranges>
#include <algorithm>

std::vector<Vector2f> pts = { {1,2}, {3,4} };

std::ranges::for_each( pts, [](Vector2f & p){
    // normalize in-place using element access
    float len = std::sqrt( p.x * p.x + p.y * p.y );
    if ( len != 0.0f ) {
        p.x /= len;
        p.y /= len;
    }
});
```

## Practical notes and guidance

- `Tuple2` intentionally provides pointer iterators via `begin()` and `end()` so it can be used by generic algorithms that accept iterator ranges.
- For hot inner loops prefer converting to SIMD with `ToSimd()` and using the `TupleSimd` math primitives. Use the sequence-like API for interoperability and glue code.
- Bounds-checked access `at()` is available for safer code paths that require diagnostics.

## Summary

`Tuple2` provides a compact, sequence-like API that integrates well with the C++ standard library. The small set of container-like members makes it straightforward to use `Tuple2` with ranges and algorithms while retaining the mathematical semantics expected of a 2D vector.

