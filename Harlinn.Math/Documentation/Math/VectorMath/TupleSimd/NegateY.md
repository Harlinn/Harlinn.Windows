# `TupleSimd::NegateY` and `TupleSimd::WithNegatedY`

This page documents the `NegateY` member functions implemented on the `TupleSimd` template in `Harlinn.Math\include\Harlinn\Math\VectorMath.h`.

## Summary

- `NegateY` modifies the object in place by negating the second component (the Y component) of the underlying SIMD register.
- `WithNegatedY` returns a copy with the Y component negated and leaves the original object unchanged.

In mathematical terms, for a SIMD tuple value vector \(v\) with components \(v = (x, y, z, w)\) the operations perform:

- `NegateY`: \(y \mapsto -y\) and other components remain the same.
- `WithNegatedY`: returns \((x, -y, z, w)\) when applied to \(v\).

If the tuple size is less than 2 then the Y component does not exist; in the library code the Y accessor methods are defined for tuple types that provide a second element.

## Prototypes

- `void NegateY()`
  - Modifies `this` by negating the second component of `simd` via the underlying `Traits::NegateY` implementation.
  - noexcept: the implementation calls `Traits` operations that are declared `noexcept` in the SIMD traits.

- `TupleSimd WithNegatedY() const noexcept`
  - Returns a new `TupleSimd` whose Y component is the negation of the current Y component. Original object is unchanged.

## Behavior and semantics

- Both functions operate on the internal `simd` register using the corresponding `Traits` helpers (`NegateY` or equivalent). The operation is branchless and relies on SIMD intrinsics for performance.
- `NegateY` mutates the object and is useful when an in-place update is desired.
- `WithNegatedY` is useful for functional style code where a new value is needed without changing the original.

## Complexity

Both operations are constant time: O(1) with respect to the tuple size. They execute a small number of SIMD operations.

## Example

```cpp
// Given a TupleSimd instance t
auto t2 = t.WithNegatedY(); // t2 has Y negated; t is unchanged

t.NegateY(); // t now has its Y component negated in place
```

## Notes

- These methods rely on the SIMD `Traits` for correct behavior across different value types and SIMD widths.
- The semantics are independent of the specific SIMD width: the Y component is the second logical component of the tuple representation.

References: implementation in `Harlinn.Math\include\Harlinn\Math\VectorMath.h` under the `TupleSimd` class.
