# `TupleSimd::AbsY` and `TupleSimd::WithAbsY`

Summary:

This document describes the `AbsY` modification method and the `WithAbsY` non-modifying accessor of the `TupleSimd` template in `Harlinn::Math::VectorMath`.

## Declaration

- `void AbsY()` noexcept
- `TupleSimd WithAbsY() const noexcept`

## Description:

Both members operate on the second component (Y) of a `TupleSimd` instance. For a tuple value

\(t = (t_0, t_1, t_2, \dots, t_{n-1})\)

the effect of `AbsY` and `WithAbsY` is to replace the second component with its absolute value while leaving the other components unchanged:

\[\text{result} = (t_0, |t_1|, t_2, \dots, t_{n-1})\]

- `AbsY()` modifies the object in-place. It assigns the result back to the instance's `simd` member by calling the corresponding SIMD trait operation.
- `WithAbsY()` returns a new `TupleSimd` instance with the Y component replaced by its absolute value and leaves the original object unchanged.

Both functions are declared `noexcept` and implemented using the type's `Traits` helper via the `Traits::AbsY` operation, ensuring the operation is implemented efficiently using SIMD where available.

## Requirements:

- `TupleSimd` must provide a `Traits` type exposing an `AbsY` operation that accepts and returns the underlying SIMD register type.
- The `TupleSimd` specialization must have at least two components for the Y component to be meaningful. The implementation in the library is available for tuple sizes that include a second component.

## Complexity:

Constant time: the operation is performed on the underlying SIMD register and has O(1) cost per register lane.

## Exception safety:

`noexcept`: the operations do not throw.

## Example

```cpp
// Given a TupleSimd instance `t` representing (x, y, z, w)
// Modify in-place
t.AbsY(); // now t holds (x, |y|, z, w)

// Non-modifying version
auto t2 = t.WithAbsY(); // t is unchanged, t2 holds (x, |y|, z, w)
```

## See also

- `TupleSimd::AbsX` : absolute value of the X component
- `TupleSimd::WithAbsX` : non-modifying version for the X component
- `TupleSimd::AbsXY` : set both X and Y to their absolute values

