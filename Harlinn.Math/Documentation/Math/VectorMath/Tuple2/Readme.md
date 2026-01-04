# `Tuple2`

This document describes the `Tuple2` template implemented in `Harlinn.Math/include/Harlinn/Math/VectorMath.h` and shows common 2D graphics usage patterns and examples.

## Overview

`Tuple2<DerivedT, T>` is a minimal, small-vector abstraction that holds two numeric components and provides convenience operations for 2D math. Concrete types in the codebase derive from `Tuple2` (for example `Vector2f = Vector<float, 2>`). The implementation is designed to interoperate with the SIMD-backed `TupleSimd` helpers and the library math primitives.

`Tuple2` provides:

- storage for two values in a small array
- named accessors `x` and `y`
- construction from scalars, arrays and compatible SIMD types
- element access, iteration and utility functions such as `ToSimd()` and `HasNaN()`
- basic arithmetic assignment operators (`+=`, `-=`, `*=`, `/=`)

## Template signature

The template is declared as:

```cpp
template<class DerivedT, ArithmeticType T>
class Tuple2 : public Internal::TupleBase
```

`DerivedT` is the CRTP-derived concrete type and `T` is the numeric element type (for example `float` or `int`).

## Storage and members

`Tuple2` internally uses an `ArrayType` provided by the SIMD `Traits` for the element type and arity. The union exposes both the array and named members:

```cpp
union
{
    ArrayType values;
    struct { value_type x; value_type y; };
};
```

This layout allows efficient loading into SIMD registers while preserving convenient named access.

## Key constructors and conversions

- Default constructs to `(0, 0)`.
- `Tuple2(value_type v)` sets both components to the same value.
- `Tuple2(value_type xv, value_type yv)` constructs from separate components.
- `Tuple2(const ArrayType a)` constructs from a contiguous array.
- `Tuple2(const U& other)` can construct from other tuple or SIMD-compatible types where `Traits` match or implicit conversions are supported.

`ToSimd()` converts the `Tuple2` into its SIMD representation by loading the `values`.

## Provided operations

- Elementwise arithmetic with other `Tuple2` and SIMD types via operators and `ToSimd` interop.
- Equality comparisons with another tuple or SIMD object using `Traits::AllEqual`.
- Methods: `data()`, `begin()`, `end()`, `size()` and `ToString()` for debugging.
- Numeric utilities: `HasNaN()`, `IsFinite()`, `IsInfinite()`.

## Mathematical definitions

Length (Euclidean norm) of a 2D vector `(x, y)`:

$$
\text{length} = \sqrt{x^2 + y^2}
$$

Dot product of `a = (x_1, y_1)` and `b = (x_2, y_2)`:

$$
\text{dot}(a, b) = x_1 x_2 + y_1 y_2
$$

2D cross product (scalar z-component) often used for orientation tests:

$$
\text{cross}_z(a, b) = x_1 y_2 - y_1 x_2
$$

Rotation by an angle \(\theta\) uses the matrix:

$$
R(\theta) = \begin{bmatrix}
\cos\theta & -\sin\theta \\
\sin\theta & \cos\theta
\end{bmatrix}
$$

Applying `R(\theta)` to a point `(x, y)` gives:

$$
(x', y') = (x \cos\theta - y \sin\theta, x \sin\theta + y \cos\theta)
$$

All the above operations are directly representable using `Tuple2` or the library `Vector` specializations.

## Examples (C++)

The following examples use the concrete `Vector2f` type (an alias for `Vector<float, 2>`) which derives from `Tuple2`.

### 1. Vector addition and scaling

```cpp
using Vector2f = Math::Vector2f;

Vector2f a(1.0f, 2.0f);
Vector2f b(3.0f, 4.0f);

// elementwise add
Vector2f c = a + b; // (4.0f, 6.0f)

// scale
Vector2f d = c * 0.5f; // (2.0f, 3.0f)

// in-place
c += Vector2f(1.0f, -1.0f); // (5.0f, 5.0f)
```

### 2. Dot product and length

```cpp
// dot product
float dp = Math::ScalarDot(a.ToSimd(), b.ToSimd());
// or using Tuple2 helpers
float dp2 = a.x * b.x + a.y * b.y;

// length
float length = std::sqrt(a.x * a.x + a.y * a.y);
// normalize (careful with zero length)
if (length != 0.0f)
{
    Vector2f n = a / length; // normalized vector
}
```

### 3. Rotate a point around the origin

```cpp
float theta = 3.14159265f / 4.0f; // 45 degrees
float c = std::cos(theta);
float s = std::sin(theta);

Vector2f p(1.0f, 0.0f);

Vector2f rotated(
    p.x * c - p.y * s,
    p.x * s + p.y * c
);
// rotated approximately (0.7071f, 0.7071f)
```

This can also be written using the SIMD and `Traits` helpers for better performance in hot paths.

### 4. 2D orientation test using cross product z-component

Use the 2D scalar cross product to determine whether `b` is to the left or right of `a`:

```cpp
float crossZ = a.x * b.y - a.y * b.x;
if (crossZ > 0)
{
    // b is left of a
}
else if (crossZ < 0)
{
    // b is right of a
}
else
{
    // colinear
}
```

### 5. Project a point onto a line defined by p0->p1

Projection of point `p` onto line through `p0` and `p1`:

```cpp
Vector2f p0(0.0f, 0.0f);
Vector2f p1(1.0f, 1.0f);
Vector2f p(1.0f, 0.0f);

Vector2f line = p1 - p0;
float denom = line.x * line.x + line.y * line.y;
if (denom != 0.0f)
{
    float t = ((p.x - p0.x) * line.x + (p.y - p0.y) * line.y) / denom;
    Vector2f projection = p0 + line * t;
}
```

## Notes and performance

- `Tuple2` is intended to be small and efficient and is implemented to interoperate with the SIMD `Traits` in `VectorMath.h` for high-performance vector math.
- For performance-critical code, prefer using the `Simd` forms via `ToSimd()` and the library free functions that operate on SIMD types.
- The API preserves value semantics while enabling zero-cost conversions to SIMD-backed representations when available.

## See also

- `Vector<float, 2>` and its `Simd` companion `TupleSimd` for SIMD-accelerated operations
- SIMD `Traits` in the header for low-level primitive operations used by `Tuple2`


