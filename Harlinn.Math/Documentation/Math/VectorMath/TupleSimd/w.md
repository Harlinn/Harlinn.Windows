# `TupleSimd::W()` and `TupleSimd::w()`

This document describes the `W()` and `w()` member functions of the `TupleSimd` template implemented in `include/Harlinn/Math/VectorMath.h`.

## Summary

- `W()`: Returns a `TupleSimd` whose every component is the fourth element (index 3) of the underlying SIMD register `simd`.
- `w()`: Returns the fourth scalar component (index 3) of `simd` as the `value_type`.

Both members are available only for `TupleSimd` instantiations where `Size > 3` (that is: the tuple holds at least 4 components).

## Signatures

- `TupleSimd W() const requires ( Size > 3 )`
- `value_type w() const requires ( Size > 3 )`

## Semantics

Let the underlying SIMD register hold components $c_0, c_1, c_2, c_3, \dots$ (only the first `Size` components are meaningful for the tuple).

- `W()` returns a `TupleSimd` with every lane set to $c_3$. In math notation:

  If the original SIMD register is $\mathbf{c} = (c_0, c_1, c_2, c_3, \dots)$ then

  $W(\mathbf{c}) = (c_3, c_3, c_3, c_3)$ (the returned `TupleSimd` has each lane equal to the fourth element).

  The implementation uses `Traits::Trim( Traits::At<3>( simd ) )` to build a SIMD value that replicates the fourth component across lanes and then returns that as a `TupleSimd`.

- `w()` extracts the scalar fourth component:

  $w(\mathbf{c}) = c_3$.

  The implementation uses `Traits::Extract<3>( simd )`.

## Preconditions and Constraints

- `Size > 3` is required. These members are constrained with `requires ( Size > 3 )` and will not participate in overload resolution for smaller tuples.
- The `Traits` type used by `TupleSimd` must provide `At<3>`, `Trim` and `Extract<3>` operations. This is satisfied by the SIMD `Traits` used throughout the `VectorMath` implementation.

## Complexity

Both operations are constant time: O(1). They operate on the SIMD register without per-element loops.

## Examples

Assume `T` is a `TupleSimd` instantiation with `Size >= 4` and `value_type = float`.

- `auto wx = t.W();`  // `wx` is a `TupleSimd` where every lane equals `t`'s fourth element
- `float w = t.w();`  // `w` is the scalar value of the fourth element

Example pseudocode reference using `Vector4f::Simd`:

```cpp
Vector4f::Simd vs = /* some SIMD value */;
Vector4f::Simd wrep = Traits::Trim( Traits::At<3>( vs.simd ) ); // internal behavior
float w = Traits::Extract<3>( vs.simd ); // scalar extract
```

## Related members

- `SetW(SIMDType src)` and `SetW(const value_type value)` : assign the fourth lane
- `X()`, `Y()`, `Z()`, `x()`, `y()`, `z()` : analogous accessors for other components

## Notes

- The returned `TupleSimd` from `W()` is typically used where a replicated fourth component is needed for vectorized operations such as swizzles, dot-products or masked computations.
- `W()` uses `Traits::Trim` to ensure the replicated value is in the proper `TupleSimd` form for the tuple size.

