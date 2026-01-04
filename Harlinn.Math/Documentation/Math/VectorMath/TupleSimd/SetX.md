# `TupleSimd::SetX` Reference

This page documents the `SetX` member functions of the `TupleSimd` template in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

## Overview

`TupleSimd` stores a SIMD register `simd` that represents the components of a small fixed-size tuple. The `SetX` family of functions assign a new value to the first component (X) of the underlying SIMD register while leaving the remaining components unchanged.

Three overloads are provided:

- `void SetX( SIMDType src )` : Replace the X component of `simd` using the supplied SIMD value `src`.
- `void SetX( const TupleSimd& src )` : Replace the X component of `simd` using `src.simd`.
- `void SetX( const value_type value )` : Replace the X component of `simd` using the scalar `value`.

All overloads are noexcept and operate in constant time.

## Semantics

Let the current SIMD-backed tuple be $v$ with components $v_0, v_1, \dots, v_{n-1}$ and let the source value provide a component $s_0$ (either via `src` or `value`). After calling any `SetX` overload the resulting tuple $r$ satisfies:

- $r_0 = s_0$,
- $r_i = v_i$ for $i = 1, \dots, n-1$.

In other words, only the first element is updated. The operation can be expressed as:

$$
r = (s_0, v_1, v_2, \dots, v_{n-1})
$$

Implementation uses a permutation mask via the SIMD `Permute` operation to copy the intended component(s) from the source into the X lane while preserving the remaining lanes.

## Use Cases

- Update only the X component of a packed SIMD tuple while keeping the other components intact.
- Efficiently build a new SIMD tuple by combining an existing SIMD register and a scalar or another SIMD register.

## Examples

C++ usage examples:

```cpp
// Using a SIMD source
TupleSimd<MyTuple> t;        // current t.simd contains [t0, t1, t2, t3]
MyTuple::SIMDType src = /* some SIMD value */;
t.SetX(src);                // result: [src_x, t1, t2, t3]

// Using a TupleSimd source
TupleSimd<MyTuple> other;    // other.simd contains [o0, o1, o2, o3]
t.SetX(other);              // result: [o0, t1, t2, t3]

// Using a scalar value
t.SetX(1.5f);               // result: [1.5, t1, t2, t3]
```

## Complexity and Safety

- Time complexity: O(1).
- Exception safety: `noexcept` in the `TupleSimd` implementation.
- Behavior for NaN or Inf follows the underlying SIMD `Traits` semantics.

## Notes

- `SetX` does not normalize or otherwise change the other lanes. If you need to change multiple lanes consider `SetXYZ`, `SetXYZW` or constructing a new SIMD via `Traits::Set`.
- The exact permutation indices and bit-level behavior follow the `Traits::Permute` contract implemented for the selected element type and width.