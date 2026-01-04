# `TupleSimd::NegateX` and `TupleSimd::WithNegatedX`

This document describes the behavior of the `NegateX` member function and the `WithNegatedX` accessor of the `TupleSimd<...>` template type implemented in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

## Summary

- `NegateX()` : mutates the object by negating the first component (x) of the underlying SIMD register. The other components remain unchanged.
- `WithNegatedX()` : returns a copy of the object where the first component is negated; the original object is not modified.

Both operations are implemented using the SIMD `Traits` for the tuple type. They delegate the actual per-lane negation to `Traits::NegateX` which operates on the SIMD register.

## Preconditions and Requirements

- The `TupleSimd` instantiation must provide a nested `Traits` type that exposes:
  - `SIMDType` : underlying SIMD register type
  - `NegateX( SIMDType )` : function that negates the X lane in the SIMD register

- The operations work for any `TupleSimd` specialization where the underlying `Traits` implement `NegateX`.

## Semantics

Let \(\mathbf{v}\) denote the tuple represented by the `TupleSimd` instance. For a 3-component tuple: \(\mathbf{v} = (x, y, z)\).

- `NegateX()` :

  It transforms \(\mathbf{v}\) in place to:

  \[\mathbf{v} \leftarrow (-x, y, z)\]

- `WithNegatedX()` :

  It returns a new `TupleSimd` value \(\mathbf{u}\) such that:

  \[\mathbf{u} = (-x, y, z)\]

  The original `TupleSimd` object remains unchanged.

These definitions generalize to other tuple sizes. For a general tuple of size \(n\) with components \((v_0, v_1, \dots, v_{n-1})\), the effect is:

\[(v_0, v_1, \dots, v_{n-1}) \mapsto (-v_0, v_1, \dots, v_{n-1})\]

## Complexity and Performance

- Both operations execute in constant time with respect to tuple size from the point of view of SIMD instructions: the call is implemented as a single SIMD lane permutation/bitwise operation provided by `Traits::NegateX`.
- They avoid per-component scalar loops by relying on the `Traits` SIMD primitives.

## Example Usage

```cpp
using Vec3Simd = MyTuple3::Simd; // example alias to a TupleSimd specialization

Vec3Simd v = /* constructed or loaded */;

// Mutating: negate x component in place
v.NegateX();

// Non-mutating: produce a copy with negated x
auto negated = v.WithNegatedX();
```

## Notes

- The precise implementation details and available optimizations depend on the concrete `Traits` type for the element type and tuple size.
- The operation does not change lane ordering or other components, it only flips the sign of the first lane.