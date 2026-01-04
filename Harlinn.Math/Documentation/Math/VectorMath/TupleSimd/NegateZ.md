# `TupleSimd::NegateZ` and `TupleSimd::WithNegatedZ`

This document describes the `NegateZ` and `WithNegatedZ` member functions of the `TupleSimd` template in `VectorMath.h`.

## Summary

- `NegateZ()` : Mutates the current `TupleSimd` instance by negating the third component (the Z component) of its internal SIMD register.
- `WithNegatedZ()` : Returns a new `TupleSimd` object that is a copy of the original but with the Z component negated; the original object is not modified.

Both operations rely on the underlying `Traits::NegateZ` implementation and operate on the SIMD representation stored in the `simd` member.

## Requirements

- These functions are only valid when `TupleSimd::Size > 2` (that is, the tuple must have a Z component).
- They require that the `TupleT::Traits` type provides the `NegateZ` operation acting on the SIMD register type.

## Signatures (conceptual)

- `void NegateZ()` : In-place negate of Z component.
- `TupleSimd WithNegatedZ() const` : Returns a copy with Z negated.

(Exact signatures in the header use the `TupleSimd` template and may include `requires (Size > 2)` constraints.)

## Semantics

Let the SIMD-held tuple be represented by the ordered components

\(\mathbf{v} = (x, y, z, w, \dots)\)

where only the first `Size` components are considered. The two functions behave as follows:

- `NegateZ()` : updates `simd` so that

\[\mathbf{v} \leftarrow (x, y, -z, w, \dots)\]

- `WithNegatedZ()` : returns a new `TupleSimd` representing

\[\mathbf{v'} = (x, y, -z, w, \dots)\]

and leaves the original `TupleSimd` unchanged.

## Complexity

Both operations perform a single SIMD register operation via `Traits::NegateZ`, so they are constant time with respect to the tuple size: \(O(1)\).

## Example (usage)

Assume `T` is a `TupleSimd` specialization with `Size = 3` and element type `float`.

```cpp
T t = /* ... */;          // t holds (x, y, z)
T copy = t.WithNegatedZ(); // copy holds (x, y, -z); t unchanged
t.NegateZ();               // t now holds (x, y, -z)
```

Mathematically: if \(t = (x, y, z)\) then after `NegateZ()` or for the result of `WithNegatedZ()` you get \((x, y, -z)\).

## Notes

- Implementation detail: both functions delegate to `Traits::NegateZ`, so behavior and performance depend on the `Traits` implementation for the active element type and SIMD width.
- These methods are typically used when component-wise sign changes are needed while keeping other components intact.


<!-- End of documentation -->