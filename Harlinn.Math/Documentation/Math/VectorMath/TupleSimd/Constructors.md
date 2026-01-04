# `TupleSimd` Constructors

This document lists and explains all constructors implemented for the `TupleSimd<TupleT>` template in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

Notes:
- `TupleT::Traits` is referred to as `Traits` in signatures below.
- `TupleT::SIMDType` is referred to as `SIMDType` in signatures below.
- `TupleT::value_type` is referred to as `value_type`.
- `Size` denotes `TupleT::Size`. Typical values: $\text{Size}=2,3,4,8$ depending on the tuple instantiation.

## 1. Default constructor

Signature:

`TupleSimd() noexcept`

Description:
- Initializes the internal SIMD register to zero using `Traits::Zero()`.
- Always noexcept.

Behavior:
- The created `TupleSimd` holds the zero vector: all components are zero.

## 2. Construct from raw SIMD register

Signature:

`TupleSimd(SIMDType values) noexcept`

Description:
- Construct from a raw SIMD register value.
- `values` is stored directly into the internal `simd` member.
- Always noexcept.

## 3. Copy / converting constructor from another SIMD wrapper type

Signature (compatible traits or identical):

`template<SimdType S>
requires std::is_same_v<Traits, typename S::Traits> ||
         (std::is_same_v<typename Traits::Type, typename S::Traits::Type> && (Size > S::Size))
TupleSimd(const S & other) noexcept`

Description:
- Constructs from another SIMD wrapper `S` when the `Traits` are identical, or when the underlying element type is the same and the destination `Size` is larger than the source `S::Size`.
- Copies the underlying SIMD register: `simd = other.simd`.
- Always noexcept.

Use case:
- Promote a smaller-simd vector to a larger `TupleSimd` of the same element type.

## 4. Truncating constructor from a larger SIMD wrapper

Signature (same element type and source larger than destination):

`template<SimdType S>
requires std::is_same_v<typename Traits::Type, typename S::Traits::Type> && (Size < S::Size)
TupleSimd(const S & other) noexcept`

Description:
- Constructs from a larger SIMD wrapper `S` that has the same underlying element type but `S::Size > Size`.
- Copies the source SIMD register and then clears or trims unused components according to `Size`.
- Implementation adjusts components explicitly for small sizes: e.g., if `Size < 4` the high lanes are zeroed using `Traits::SetZ`, `Traits::SetW` and similar helpers.
- Always noexcept.

Behavior:
- This constructor performs truncation of extra components and ensures the unused lanes are zeroed.

## 5. Construct from `TupleType` (load from tuple values)

Signature:

`TupleSimd(const TupleType & other) noexcept`

Description:
- Loads values from a tuple-type instance (for example a `Tuple2`, `Tuple3` or `Tuple4`) using `Traits::Load(other.values)` to initialize the SIMD register.
- Always noexcept.

Use case:
- Convert a structural tuple into its packed SIMD representation.

## 6. Construct from an array of values

Signature:

`TupleSimd(const ArrayType& values) noexcept`

Description:
- Loads values from a contiguous array representation `ArrayType` by calling `Traits::Load(values)`.
- Always noexcept.

Use case:
- Initialize `TupleSimd` directly from raw contiguous storage.

## 7. Component-wise scalar constructors (fixed arity)

These constructors initialize the first `Size` components from scalar arguments. The order used by `Traits::Set(...)` in the implementation is reversed relative to typical textual ordering in some cases: the implementation calls `Traits::Set` with the last argument first. The following overloads are provided with `requires` constraints that enable them only for the matching `Size`.

### Size = 2

Signature:

`TupleSimd(value_type x, value_type y) noexcept requires (Size == 2)`

Implementation detail:
- Internally: `simd( Traits::Set( y, x ) )`.
- Initializes lane 0 with `x` and lane 1 with `y` (via the trait `Set` ordering used by the library).

### Size = 3

Signature:

`TupleSimd(value_type x, value_type y, value_type z) noexcept requires (Size == 3)`

Implementation detail:
- Internally: `simd( Traits::Set( z, y, x ) )`.
- Initializes lane 0..2 with `x,y,z` respectively.

### Size = 4

Signature:

`TupleSimd(value_type x, value_type y, value_type z, value_type w) noexcept requires (Size == 4)`

Implementation detail:
- Internally: `simd( Traits::Set( w, z, y, x ) )`.
- Initializes lane 0..3 with `x,y,z,w` respectively.

## 8. Single-scalar explicit constructor (fill)

Signatures and requirements:

- `explicit TupleSimd(value_type x) noexcept requires (Size == 2)`
  : sets all first two lanes to `x` via `Traits::Set(x,x)`.

- `explicit TupleSimd(value_type x) noexcept requires (Size == 3)`
  : sets the first three lanes to `x` via `Traits::Set(x,x,x)`.

- `explicit TupleSimd(value_type x) noexcept requires (Size == 4)`
  : sets the first four lanes to `x` via `Traits::Set(x,x,x,x)`.

- `explicit TupleSimd(value_type x) noexcept requires (Size == 8)`
  : sets the first eight lanes to `x` via `Traits::Set(x,x,x,x,x,x,x,x)`.

Description:
- These overloads are explicit and fill all usable lanes of the SIMD register with the scalar `x`.
- Always noexcept.

## 9. Additional notes and invariants

- Many constructors are `noexcept` since they delegate to trait operations that are expected to be noexcept and to simple copies of registers.
- When constructing from other SIMD types the code enforces compatibility via `requires` constraints to avoid silent misinterpretation of data.
- For small `Size` values the implementation may explicitly call `Traits::SetZ` or `Traits::SetW` to zero higher lanes when truncating from a larger SIMD source.

## 10. Quick usage examples

```cpp
// Zero-initialized
TupleSimd<MyTuple> z;

// From raw SIMD register
TupleSimd<MyTuple> fromSimd( someSimdValue );

// From tuple
MyTuple t = MyTuple::UnitX();
TupleSimd<MyTuple> ts( t );

// Component-wise
TupleSimd<MyTuple2> ts2( 1.0f, 2.0f );

// Fill
TupleSimd<MyTuple4> tfill( 1.0f );
```

If you need inline references to the exact implementation lines, open `Harlinn.Math/include/Harlinn/Math/VectorMath.h` and search for `class TupleSimd` and its constructors.
