# `TupleSimd::SetY`

This document describes the `SetY` member functions of the `TupleSimd` template defined in `Harlinn.Math\include\Harlinn\Math\VectorMath.h`.

Summary: `SetY` updates the second component (Y) of the internal SIMD register of a `TupleSimd` instance from either a SIMD value, another `TupleSimd`, or a scalar value.

## Prototypes

- `void SetY( SIMDType src );`
- `void SetY( const TupleSimd& src );`
- `void SetY( const value_type value );`

Notes:
- `SIMDType` is the underlying SIMD register type provided by `TupleT::Traits::SIMDType`.
- `value_type` is `TupleT::Traits::Type`.
- These overloads are applicable for tuple sizes where a Y component exists: i.e., `Size >= 2`.

## Semantics

Let the current SIMD register of the object be represented as a vector

\[ V = [x,\; y,\; z,\; w] \]

(components beyond the tuple size may be ignored depending on `Size` and `Traits`). The `SetY` operations update the second component `y` only, leaving the other components unchanged.

- `SetY(SIMDType src)`

  Sets the Y component of `V` to the second lane of `src` while preserving the other lanes. In effect:

  \[ V_{new} = [x,\; s_{1},\; z,\; w] \]

  where `s_{1}` denotes the second element of the SIMD register `src`.

- `SetY(const TupleSimd& src)`

  Equivalent to `SetY(src.simd)`.

  If `src` corresponds to tuple values \(S = [s_0, s_1, s_2, s_3]\) then the operation produces:

  \[ V_{new} = [x,\; s_{1},\; z,\; w] \]

- `SetY(const value_type value)`

  Sets the Y component of `V` to `value`. This overload constructs a SIMD value filled with `value` and then uses the same lane extraction as above. The result is:

  \[ V_{new} = [x,\; value,\; z,\; w] \]

## Implementation details (notes)

- The implementation uses a `Traits::Permute` operation to replace only the Y lane while leaving other lanes unchanged. The permute invocation in the source is `Traits::Permute<0, 5, 2, 3>( simd, src )` where indices refer to lanes selected from the two input registers. This produces the semantics described above.

- The scalar overload uses a `Traits::Fill<Size>( value )` helper to make a SIMD value where all lanes contain `value`, and then extracts the needed lane for assignment.

## Complexity

All overloads execute in constant time: O(1). The operations are implemented with a small fixed number of SIMD instructions.

## Thread safety

`SetY` mutates the SIMD member of the `TupleSimd` instance. It is not thread-safe with respect to concurrent mutation of the same object. Concurrent reads may race with a concurrent call to `SetY` and produce undefined results unless externally synchronized.

## Examples

Pseudo-code usage:

```cpp
TupleSimd<MyTuple> t;           // current simd: [x, y, z, w]
TupleSimd<MyTuple> s;           // source simd:  [s0, s1, s2, s3]

// set Y from another TupleSimd
t.SetY( s );                    // t becomes [x, s1, z, w]

// set Y from an SIMD register
MyTuple::SIMDType srcSimd = ...;
t.SetY( srcSimd );              // t becomes [x, srcSimd[1], z, w]

// set Y from a scalar
t.SetY( 3.14f );                // t becomes [x, 3.14f, z, w]
```

## See also

- `TupleSimd::SetX` : similar API for the X lane.
- `TupleSimd::SetZ` : similar API for the Z lane; available when `Size > 2`.
- `TupleSimd::SetW` : similar API for the W lane; available when `Size > 3`.

## Source reference

Defined in: `Harlinn.Math\include\Harlinn\Math\VectorMath.h` : class template `TupleSimd< TupleT >` (member functions `SetY`).
