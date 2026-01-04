# TupleSimd::AbsXY and TupleSimd::WithAbsXY

This document describes the `AbsXY` and `WithAbsXY` member functions of the `TupleSimd` template defined in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

Both functions operate on the first two components of the underlying SIMD register and apply the absolute value operation to those components.

## C++ signatures

- `void AbsXY()`
- `TupleSimd WithAbsXY() const`

These appear as members of `TupleSimd<TupleT>` where `TupleT` is a type derived from `Tuple2`, `Tuple3`, or `Tuple4` and `TupleT::Traits` implements `AbsXY`.

## Semantics

Let a tuple value be represented by its components:

\[
v = (x, y, z, w, \ldots)
\]

`AbsXY()` mutates the object so that the first two components become their absolute values while the remaining components are left unchanged:

\[
\text{After } v.AbsXY():\quad v = (|x|, |y|, z, w, \ldots)
\]

`WithAbsXY()` returns a new `TupleSimd` instance with the first two components replaced by their absolute values while leaving the original object unchanged:

\[
u = v.WithAbsXY() \quad\Rightarrow\quad u = (|x|, |y|, z, w, \ldots)\quad\text{and}\quad v\ \text{is unchanged}
\]

Notes:
- The absolute value operation is the standard real absolute value: for a component value \(a\) the result is \(|a|\).
- These operations are most meaningful for floating point or signed integer element types. For unsigned element types the values are unchanged when applying absolute value.

## Requirements and constraints

- `TupleSimd` must have a `Traits` type that provides an `AbsXY` operation. In the implementation this is invoked as `Traits::AbsXY(simd)` where `simd` is the underlying SIMD register.
- The tuple must contain at least two components for an effect to be visible. For `TupleSimd` instantiated from a 2-component tuple the functions operate on both components. For larger tuples the first two components are affected and the rest are unchanged.

## Exception and concurrency

- `AbsXY()` is `noexcept` in the code base since it delegates to low level SIMD operations and does not allocate or throw.
- `WithAbsXY()` is effectively `noexcept` as it returns a new SIMD wrapper constructed from the result of the underlying `Traits` call.
- These functions operate on object state and are not thread safe if multiple threads mutate the same object concurrently. Use external synchronization when needed.

## Complexity and performance

- Both functions are constant time and implemented using SIMD primitives. Their cost is independent of the tuple dimension and is equivalent to a small fixed number of SIMD operations.
- `AbsXY()` performs the in place modification and avoids an allocation. `WithAbsXY()` creates and returns a new `TupleSimd` instance by value which is a small, efficient operation for SIMD wrapper types.

## Examples

Assume `TupleSimd` is instantiated for a 3-component float tuple type, for example `TupleSimd<MyVec3>`.

In-place absolute on x and y:

```cpp
Math::TupleSimd<MyVec3> t( /* constructed from simd or values */ );
t.AbsXY();
// now t.x == |old_x| and t.y == |old_y|
```

Create a copy with absolute x and y:

```cpp
Math::TupleSimd<MyVec3> t( /* ... */ );
auto tabs = t.WithAbsXY();
// tabs.x == |t.x|, tabs.y == |t.y|, t is unchanged
```

## Implementation notes

- The member implementations call into `Traits::AbsXY` which is expected to implement a branchless absolute operation on the SIMD register, typically by masking out the sign bit(s) for floating point values or using a per-lane absolute for integer values.
- For tuple types with `Size` greater than 2 the `Traits::AbsXY` implementation is required to leave other lanes unchanged.

## See also

- `TupleSimd::AbsX`, `TupleSimd::AbsY`, `TupleSimd::WithAbsX`, `TupleSimd::WithAbsY` for operations on individual components.
- `Math::Abs` and `Math::FastAbs` for componentwise absolute value helpers.

