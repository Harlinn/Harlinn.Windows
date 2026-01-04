# `TupleSimd::AbsX` and `TupleSimd::WithAbsX`

Summary:

This document describes the `AbsX` mutating member function and the `WithAbsX` non-mutating member function of the `TupleSimd` template declared in `Harlinn.Math\include\Harlinn\Math\VectorMath.h`.

Both functions operate on the first component (x) of the SIMD tuple and compute the absolute value of that component. The remaining components are left unchanged.

Syntax:

- Mutating: `void AbsX()`
- Non-mutating: `TupleSimd WithAbsX() const`

Semantics:

Given a `TupleSimd` instance representing a vector of components \( (x, y, z, w, ... ) \) where only the first component is guaranteed to be present for all sizes, the two functions behave as follows:

- `AbsX()` : replace the first component by its absolute value in place:

\[
\text{AbsX}: (x, y, z, w, \dots) \mapsto (|x|, y, z, w, \dots)
\]

It mutates the object it is called on and returns `void`.

- `WithAbsX()` : return a new `TupleSimd` with the first component replaced by its absolute value, leaving the original object unchanged:

\[
\text{WithAbsX}(v) = (|x|, y, z, w, \dots)
\]

Return value:

- `AbsX()` : none (mutates `*this`).
- `WithAbsX()` : a `TupleSimd` instance with `x` replaced by `|x|`.

Usage examples:

```cpp
TupleSimd<MyTuple> t = /* ... */;
// mutate in place
t.AbsX();

// non-mutating
auto t2 = t.WithAbsX();
```

Implementation note:

Both functions delegate to the `Traits` implementation for the underlying SIMD type. Concretely inside `TupleSimd` they call `simd = Traits::AbsX(simd)` for `AbsX()` and `return Traits::AbsX(simd)` for `WithAbsX()`. The `Traits::AbsX` operation performs the absolute-value operation on the lane that corresponds to the x component while preserving other lanes.

Complexity:

Both operations run in O(1) time relative to the tuple size because they operate on a fixed SIMD register. The actual CPU cost depends on the underlying SIMD implementation in `Traits`.

Notes:

- These members are available for any `TupleSimd` instantiation regardless of `Size` so long as the underlying `Traits` type defines `AbsX` and related constants.
- The functions operate on the SIMD representation. For tuple types with `Size < SIMD width` the implementation ensures only the logical x lane is modified.

See also:

- `TupleSimd::AbsY`, `TupleSimd::AbsZ`, `TupleSimd::AbsW` (similar semantics for other components)
- `TupleSimd::WithNegatedX` and `TupleSimd::NegateX` (negation equivalents)
- `TupleT::ToSimd()` and `Internal::ToSimdType` for conversions between tuple and SIMD types

File: `Harlinn.Math\include\Harlinn\Math\VectorMath.h`