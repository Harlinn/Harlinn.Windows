# `Tuple2` Operators

This document enumerates and documents the operator overloads provided for the `Tuple2<DerivedT, T>` template implemented in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

Notation:
- `DerivedT` is the CRTP-derived type.
- `value_type` is the element type `T`.
- `Tuple2` refers to the concrete derived type (`DerivedT`).
- `Size = 2` for `Tuple2`.

All signatures below show the typical form used in the header. Exact `constexpr`, `noexcept` and `requires` annotations may vary in the source; the shown signatures reflect the conceptual API.

## Unary operators

- Positive operator : returns a copy

```cpp
constexpr DerivedT operator+() const noexcept;
```

- Negation operator : element-wise negation

```cpp
constexpr DerivedT operator-() const noexcept;
```

Semantics:
- `+v` returns a copy of `v`.
- `-v` returns a tuple where each component is negated: if \(v=(x,y)\) then \(-v = (-x, -y)\).

## Binary arithmetic operators (vector-vector)

These are typically implemented as free functions that call the corresponding compound assignment member operators.

- Addition

```cpp
constexpr DerivedT operator+(const DerivedT& lhs, const DerivedT& rhs) noexcept;
```

- Subtraction

```cpp
constexpr DerivedT operator-(const DerivedT& lhs, const DerivedT& rhs) noexcept;
```

- Elementwise multiplication

```cpp
constexpr DerivedT operator*(const DerivedT& lhs, const DerivedT& rhs) noexcept;
```

- Elementwise division

```cpp
constexpr DerivedT operator/(const DerivedT& lhs, const DerivedT& rhs) noexcept;
```

Semantics:
- All operators apply per-component. For example for addition:

\[(x_1, y_1) + (x_2, y_2) = (x_1 + x_2,\; y_1 + y_2)\]

## Binary arithmetic operators (vector-scalar and scalar-vector)

Overloads support scalar values on either side. The scalar type is convertible to `value_type`.

- Vector plus scalar

```cpp
constexpr DerivedT operator+(const DerivedT& v, value_type s) noexcept;
constexpr DerivedT operator+(value_type s, const DerivedT& v) noexcept;
```

- Vector minus scalar

```cpp
constexpr DerivedT operator-(const DerivedT& v, value_type s) noexcept;
```

- Vector times scalar

```cpp
constexpr DerivedT operator*(const DerivedT& v, value_type s) noexcept;
constexpr DerivedT operator*(value_type s, const DerivedT& v) noexcept;
```

- Vector divided by scalar

```cpp
constexpr DerivedT operator/(const DerivedT& v, value_type s) noexcept;
```

Semantics:
- Scalar operations are broadcast to both components. For example:

\[(x, y) * s = (x s,\; y s)\]

## Compound assignment operators

These mutate the left-hand side in place and return a reference to it.

- Add and assign

```cpp
DerivedT& operator+=(const DerivedT& rhs) noexcept;
DerivedT& operator+=(value_type s) noexcept;
```

- Subtract and assign

```cpp
DerivedT& operator-=(const DerivedT& rhs) noexcept;
DerivedT& operator-=(value_type s) noexcept;
```

- Multiply and assign

```cpp
DerivedT& operator*=(const DerivedT& rhs) noexcept;
DerivedT& operator*=(value_type s) noexcept;
```

- Divide and assign

```cpp
DerivedT& operator/=(const DerivedT& rhs) noexcept;
DerivedT& operator/=(value_type s) noexcept;
```

Notes:
- Compound assignment implementations commonly delegate to `ToSimd()` and `TupleSimd` arithmetic for high performance.

## Comparison operators

- Equality

```cpp
constexpr bool operator==(const DerivedT& lhs, const DerivedT& rhs) noexcept;
```

- Inequality

```cpp
constexpr bool operator!=(const DerivedT& lhs, const DerivedT& rhs) noexcept;
```

Semantics:
- `==` returns true when both components compare equal. The implementation may use SIMD `Traits::AllEqual` when available.
- `!=` returns the negation of `==`.

## Element access

- Index operator

```cpp
value_type& operator[](std::size_t index) noexcept;
constexpr value_type operator[](std::size_t index) const noexcept;
```

Semantics:
- Index 0 maps to `x`, index 1 maps to `y`. Behavior for out-of-range index may be undefined or assert in debug builds depending on the header configuration.

## Stream operator

- Output to `std::ostream` for debugging convenience

```cpp
std::ostream& operator<<(std::ostream& os, const DerivedT& v);
```

Semantics:
- Produces a readable representation such as `(x, y)`.

## Interop with SIMD (`TupleSimd`)

`Tuple2` integrates with the SIMD wrapper via conversion functions rather than operators. For completeness the key signatures are:

```cpp
typename DerivedT::Simd ToSimd() const noexcept; // member: convert structural tuple to SIMD form
DerivedT(const typename DerivedT::Simd& simd) noexcept; // constructor from SIMD form
```

Note:
- Many operator implementations in `VectorMath.h` use `ToSimd()` internally and perform arithmetic using `TupleSimd` primitives for optimal performance.

## Common mathematical helpers implemented as free functions

These are not C++ operator overloads but are commonly used together with `Tuple2`.

- Dot product

```cpp
constexpr value_type Dot(const DerivedT& a, const DerivedT& b) noexcept;
```

Mathematical definition:

\[ \text{Dot}(a,b) = a_x b_x + a_y b_y \]

- 2D cross product (scalar z-component)

```cpp
constexpr value_type CrossZ(const DerivedT& a, const DerivedT& b) noexcept;
```

Mathematical definition:

\[ \text{CrossZ}(a,b) = a_x b_y - a_y b_x \]

- Length and normalization

```cpp
value_type Length(const DerivedT& v) noexcept;
DerivedT Normalize(const DerivedT& v) noexcept; // returns zero or handles zero-length safely as the API defines
```

Mathematical definitions:

\[ \|v\| = \sqrt{v_x^2 + v_y^2} \]

\[ \text{Normalize}(v) = \frac{v}{\|v\|} \quad\text{if }\|v\| \ne 0. \]

## Examples

```cpp
Vector2f a(1.0f, 2.0f);
Vector2f b(3.0f, 4.0f);

// arithmetic
auto c = a + b; // (4, 6)
a += b;         // a becomes (4, 6)

// scalar ops
a = a * 0.5f;  // scale both components

// dot
float d = Dot(a, b);

// cross z
float cz = CrossZ(a, b);
```

## Notes and guarantees

- Operators aim for predictable value semantics and are implemented to interoperate efficiently with the `TupleSimd` SIMD primitives in `VectorMath.h`.
- Floating point comparisons use exact equality in `operator==` and `operator!=` unless the codebase provides alternative approximate-equality helpers.
- For maximum performance in tight loops prefer converting to `Simd` form once and using SIMD operations rather than repeated operator overloads that may construct temporaries.

For exact line-level signatures and `requires` constraints consult `Harlinn.Math/include/Harlinn/Math/VectorMath.h` near the `Tuple2` declaration.