# `Tuple2::ToSimd`

This page documents the `ToSimd` member functions declared on the `Tuple2` template in `include/Harlinn/Math/VectorMath.h`.

## Location

`C++ header`: `Harlinn.Math/include/Harlinn/Math/VectorMath.h`

## Purpose

The `ToSimd` member returns a SIMD wrapper representation of the small tuple. The returned type is the `Simd` nested alias on the `Tuple2` instantiation and uses the type's `Traits` to load the underlying values into the SIMD register representation.

The conversion is efficient and intended for use by math kernels that operate on packed SIMD registers. Use `ToSimd` at API boundaries or when you need to perform SIMD operations through the `Traits` API.

## Function signatures

```cpp
Simd ToSimd() const noexcept;
operator Simd() const noexcept;
```

Both functions are `const` and `noexcept` and appear in the `Tuple2` template definition as members of the concrete derived `Tuple2` types.

### `Simd ToSimd() const noexcept;`

- Behavior: Returns a `Simd` instance constructed by loading the tuple's contiguous `values` via `Traits::Load`.
- Implementation sketch: `return Simd( Traits::Load( values ) );`
- Complexity: O(1) and implemented as a single SIMD load operation.
- Notes: The returned `Simd` type is `TupleSimd<DerivedType>` and uses `Tuple2::Traits` where `Traits = SIMD::Traits<value_type, 2>`.

### `operator Simd() const noexcept;`

- Behavior: Implicit conversion operator that delegates to `ToSimd()`.
- Implementation sketch: `return ToSimd();`
- Purpose: Allows a `Tuple2` to be passed to functions expecting the `Simd` form without an explicit call to `ToSimd()`.

## Example usage

```cpp
Tuple2<MyVec, float> t( 1.0f, 2.0f );
// explicit
auto s = t.ToSimd();
// implicit
MyVec::Simd s2 = t; // uses operator Simd()
```

## Mathematical note

If the tuple stores values \(v_0, v_1\) in `values`, then `ToSimd()` yields a SIMD register that represents the vector \([v_0, v_1]\) in the layout defined by `Traits::Load`.

Expressed in MathJax:

If values = \(\{v_0, v_1\}\) then

\[
\mathrm{ToSimd}(values) = \mathrm{Load}_{\text{Traits}}(v_0, v_1)
\]

## Remarks

- The conversion depends on the `Traits` specialization for the element type and arity (here arity = 2). The behaviour is consistent across SIMD and non-SIMD platforms by virtue of the `Traits` abstraction.
- Use the `Simd` representation for vectorized operations. Convert back to tuple form when materializing results for scalar code or storage.


© Harlinn.Math documentation
