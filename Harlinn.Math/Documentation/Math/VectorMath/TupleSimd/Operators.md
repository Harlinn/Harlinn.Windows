# `TupleSimd` Operators

This document enumerates and explains the operators provided for `TupleSimd<TupleT>` in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

Notation:
- `TupleSimd` refers to `TupleSimd<TupleT>`.
- `value_type` refers to `TupleT::value_type`.
- `Size` denotes `TupleT::Size`.
- `SIMDType` refers to `TupleT::Traits::SIMDType`.

All arithmetic and comparison operations delegate to `TupleT::Traits` to ensure correct, optimized implementations across architectures.

## Unary operators

- `TupleSimd operator+() const noexcept` : Returns a copy of the operand.
- `TupleSimd operator-() const noexcept` : Returns the element-wise negation. Implemented via `Traits::Negate`.
- `TupleSimd operator~() const noexcept` : For integer-backed `TupleSimd` types performs bitwise NOT via `Traits::Not`.

Example:
```cpp
auto a = TupleSimd<MyVec3>(1.0f, -2.0f, 3.0f);
auto neg = -a; // [-1, 2, -3]
```

## Binary arithmetic operators (element-wise)

- `TupleSimd operator+(TupleSimd lhs, TupleSimd rhs) noexcept` : element-wise addition via `Traits::Add`.
- `TupleSimd operator-(TupleSimd lhs, TupleSimd rhs) noexcept` : element-wise subtraction via `Traits::Sub`.
- `TupleSimd operator*(TupleSimd lhs, TupleSimd rhs) noexcept` : element-wise multiplication via `Traits::Mul`.
- `TupleSimd operator/(TupleSimd lhs, TupleSimd rhs) noexcept` : element-wise division via `Traits::Div`.

These operators are commutative where appropriate for the element type.

## Scalar arithmetic operators

- `TupleSimd operator+(TupleSimd lhs, value_type s) noexcept` : add scalar to each lane.
- `TupleSimd operator+(value_type s, TupleSimd rhs) noexcept` : add scalar to each lane.
- `TupleSimd operator-(TupleSimd lhs, value_type s) noexcept` : subtract scalar from each lane.
- `TupleSimd operator*(TupleSimd lhs, value_type s) noexcept` : multiply each lane by scalar.
- `TupleSimd operator*(value_type s, TupleSimd rhs) noexcept` : multiply each lane by scalar.
- `TupleSimd operator/(TupleSimd lhs, value_type s) noexcept` : divide each lane by scalar.

Implementation uses `Traits::Add`, `Traits::Mul`, etc. with `Traits::Set(s)` or `Traits::Fill` to create scalar vectors.

Example:
```cpp
auto p = TupleSimd<Vector2f>(2.0f, 3.0f);
auto scaled = p * 2.0f; // [4.0f, 6.0f]
```

## Compound assignment operators

- `TupleSimd& operator+=(TupleSimd const& other) noexcept` : lane-wise add and assign.
- `TupleSimd& operator-=(TupleSimd const& other) noexcept` : lane-wise subtract and assign.
- `TupleSimd& operator*=(TupleSimd const& other) noexcept` : lane-wise multiply and assign.
- `TupleSimd& operator/=(TupleSimd const& other) noexcept` : lane-wise divide and assign.

Scalar variants are also provided:
- `TupleSimd& operator+=(value_type s) noexcept` and similar for `-=` `*=` `/=`.

These mutate the left-hand `simd` register using `Traits` operations.

## Comparison operators (element-wise)

Comparisons produce mask-style results represented by `TupleSimd` with boolean-like lanes (implementation-specific mask representation):

- `auto operator==(TupleSimd const& a, TupleSimd const& b) noexcept` : element-wise equal via `Traits::Equal`.
- `auto operator!=(TupleSimd const& a, TupleSimd const& b) noexcept` : element-wise not-equal via `Traits::NotEqual`.
- `auto operator<(TupleSimd const& a, TupleSimd const& b) noexcept` : element-wise less-than via `Traits::Less`.
- `auto operator<=(TupleSimd const& a, TupleSimd const& b) noexcept` : element-wise less-or-equal via `Traits::LessOrEqual`.
- `auto operator>(TupleSimd const& a, TupleSimd const& b) noexcept` : element-wise greater-than via `Traits::Greater`.
- `auto operator>=(TupleSimd const& a, TupleSimd const& b) noexcept` : element-wise greater-or-equal via `Traits::GreaterOrEqual`.

Mask results can be used with `Select` and reduction helpers `Any`, `All`.

Example:
```cpp
auto m = (a < b); // mask-like TupleSimd where lane i is true if a_i < b_i
if ( Any(m) ) { /* at least one lane is true */ }
```

## Logical and bitwise operators on masks

For mask or integer types the following are available:
- `mask & mask` : lane-wise AND via `Traits::And`.
- `mask | mask` : lane-wise OR via `Traits::Or`.
- `mask ^ mask` : lane-wise XOR via `Traits::Xor`.
- `~mask` : lane-wise NOT via `Traits::Not`.

These operate on the internal mask representation returned by comparison operators.

## Reduction and boolean conversions

- `explicit operator bool() const noexcept` : returns true if any lane is non-zero. Implemented via `Traits::AnyNotEqual( simd, Traits::Zero() )`.
- `bool Any(TupleSimd const& m) noexcept` : returns true if any lane of mask `m` is true.
- `bool All(TupleSimd const& m) noexcept` : returns true if all lanes of mask `m` are true.

These provide branchless, SIMD-friendly predicates.

## Element extraction and lane broadcasters

Operators and accessors that act like operators:
- `value_type operator[](size_t i) const` : extracts lane `i` using `Traits::Extract` or `Traits::GetLane`.
- `TupleSimd X() const noexcept` : broadcast lane 0 across all lanes via `Traits::BroadcastLane<0>`.
- `TupleSimd Y() const noexcept` : broadcast lane 1 across all lanes via `Traits::BroadcastLane<1>`.

The bracket operator may be provided as a member function rather than an overloaded operator in some implementations. Use `.x()`, `.y()`, `.z()` for typed extraction where available.

## Select and conditional operators

- `TupleSimd Select(TupleSimd const& mask, TupleSimd const& trueValue, TupleSimd const& falseValue) noexcept` : returns per-lane selection `mask ? trueValue : falseValue` implemented via `Traits::Select`.

This provides an alternative to branching for per-lane conditional logic.

## Common higher-level operators implemented as free functions

Although not necessarily C++ operator overloads, the following are provided as idiomatic operations on `TupleSimd`:

- `Dot(a, b)` : scalar or SIMD dot product depending on overloads. For vector `\mathbf{a}` and `\mathbf{b}` the dot product is
  \[ \mathbf{a} \cdot \mathbf{b} = \sum_{i=0}^{Size-1} a_i b_i. \]
- `Cross(a, b)` : 3D cross product producing a `TupleSimd` for `Size \ge 3`.
- `Normalize(v)` : returns `v / \|v\|` element-wise where \(\|v\| = \sqrt{v \cdot v}\).
- `Reflect(v, n)` : returns the reflection of `v` about the normal `n` using the formula
  \[ r = v - 2 (v \cdot n) n. \]

These free functions use the underlying arithmetic operators and `Traits::HSum`, `Traits::Dot` and related primitives.

## Examples

2D midpoint using operators:
```cpp
auto a = TupleSimd<Vector2f>(1.0f, 2.0f);
auto b = TupleSimd<Vector2f>(5.0f, 6.0f);
auto mid = (a + b) * 0.5f; // midpoint
```

3D reflection using `Dot` and arithmetic operators:
```cpp
Vector3f v(0.0f, -1.0f, -1.0f);
Vector3f n = Normalize(Vector3f(0.0f, 0.0f, 1.0f));
auto vSimd = v.ToSimd();
auto nSimd = n.ToSimd();

// scalar dot then construct or use SIMD dot helpers
float d = Dot(vSimd, nSimd).x();
auto reflected = vSimd - nSimd * (2.0f * d);
```

## Notes and guarantees

- All operators are implemented to be branchless and to leverage `Traits` SIMD primitives for performance.
- Overflow, NaN, and Inf follow the semantics of the underlying `value_type` and `Traits` operations.
- Where operations require trimming to logical `Size` (for example when operating on wider registers), `Traits::Trim` or `TupleSimd::Trim` is used to maintain invariants.

For precise operator signatures and template constraints consult `Harlinn.Math/include/Harlinn/Math/VectorMath.h` around the `TupleSimd` definition.