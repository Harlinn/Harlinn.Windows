# `Tuple2` Constructors

This document lists and explains the constructors implemented for the `Tuple2<DerivedT, T>` template in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

Notes:
- `value_type` refers to `Tuple2::value_type` (the element type `T`).
- `ArrayType` refers to the contiguous storage type used by the tuple (provided by SIMD `Traits`).
- `TupleType` denotes the concrete derived type alias used with the `Tuple2` CRTP.

All signatures shown are the public constructors you will typically find for `Tuple2` specializations. Exact `noexcept` and `constexpr` qualifiers may vary by platform and header configuration, but the semantic behavior is described below.

## 1. Default constructor

```cpp
constexpr Tuple2() noexcept;
```

Description: Constructs a two-component tuple initialized to zero. The resulting tuple represents the vector

\[
(0, 0)
\]

Use: create an empty or zero-initialized 2D vector.

## 2. Copy constructor

```cpp
constexpr Tuple2(const Tuple2& other) noexcept;
```

Description: Copy constructs from another `Tuple2` of the same derived type and element type. Performs a member-wise copy of components.

## 3. Move constructor

```cpp
constexpr Tuple2(Tuple2&& other) noexcept;
```

Description: Move constructs from another `Tuple2`. For scalar element types this is equivalent to copy construction but provided for completeness and consistency with value semantics.

## 4. Scalar fill constructor

```cpp
explicit constexpr Tuple2(value_type v) noexcept;
```

Description: Initialize both components to the same scalar `v`. The tuple becomes

\[
(v, v)
\]

Use: quickly create uniform vectors or constants.

## 5. Component-wise constructor

```cpp
constexpr Tuple2(value_type x, value_type y) noexcept;
```

Description: Initialize the tuple with explicit components. The tuple becomes

\[
(x, y)
\]

Use: construct from two scalar components.

## 6. Construct from contiguous array storage

```cpp
constexpr Tuple2(const ArrayType& values) noexcept;
```

Description: Load components from a contiguous `ArrayType` (for example the internal array used by the tuple). This is typically used to interoperate with raw storage or APIs that expose arrays.

Semantics: `values[0]` maps to `x` and `values[1]` maps to `y`.

## 7. Construct from pointer to values

```cpp
constexpr Tuple2(const value_type* values) noexcept;
```

Description: Load components from a pointer to two consecutive `value_type` elements. Equivalent to constructing from `ArrayType` when the pointer references contiguous storage.

## 8. Construct from initializer list

```cpp
Tuple2(std::initializer_list<value_type> il);
```

Description: Construct from an initializer list. If the list has fewer than two elements missing components are zero-initialized; if it has more than two elements excess elements are ignored.

Use: convenient inline construction such as `Tuple2{1.0f, 2.0f}`.

## 9. Construct from another tuple-like type

```cpp
template<typename U>
constexpr Tuple2(const U& other) noexcept;
```

Description: Converting constructor that accepts other tuple-like or SIMD-backed types when the element type is convertible. This overload enables conversion from compatible `Tuple2` specializations, `TupleSimd` wrappers or other tuple types where `other.x` and `other.y` are accessible and convertible to `value_type`.

Semantics: extracts `other.x` and `other.y` and initializes the new tuple accordingly.

## 10. Construct from SIMD form

```cpp
constexpr Tuple2(const typename TupleType::Simd& simd) noexcept;
```

Description: Construct from the SIMD-packed representation (`TupleSimd`) of the same tuple type. This loads the scalar `x` and `y` components from the SIMD register into the structural tuple storage using the `Traits::Store` or equivalent helper.

Use: convert from SIMD-accelerated code back to the structural tuple for API boundaries or serialization.

## 11. Aggregates and aggregate initialization

Because `Tuple2` exposes a small `ArrayType` storage (and often a POD-like layout), you can use aggregate or brace initialization in many contexts. The available constructors determine whether aggregate initialization is used or explicit constructors are called.

## Example usages

```cpp
using Vector2f = Math::Vector<float,2>;

// default
Vector2f a; // (0, 0)

// component-wise
Vector2f b(1.0f, 2.0f); // (1, 2)

// fill
Vector2f c(3.0f); // (3, 3)

// from array
Vector2f d( std::array<float,2>{4.0f, 5.0f} ); // (4, 5)

// from initializer list
Vector2f e{6.0f, 7.0f}; // (6, 7)

// from SIMD form
auto s = b.ToSimd();
Vector2f f( s ); // convert back from SIMD to structural tuple
```

## Notes and guarantees

- Most constructors are `constexpr` and `noexcept` enabling use in compile-time contexts and performance-critical code.
- Converting constructors use `requires` or SFINAE in the header to restrict instantiation to types where element-wise conversion is valid. The documented template form above is the conceptual shape of those overloads.
- Construction from SIMD form relies on `TupleT::Traits::Store` or `Traits::Extract` helpers and preserves the logical component ordering expected by the library.

For exact line-level signatures and template constraints consult `Harlinn.Math/include/Harlinn/Math/VectorMath.h` around the `Tuple2` declaration.