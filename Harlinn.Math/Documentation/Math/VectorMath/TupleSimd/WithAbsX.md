# `TupleSimd::WithAbsX` and `TupleSimd::AbsX`

This document describes the `WithAbsX` and `AbsX` member functions on the `TupleSimd` template found in `Harlinn.Math\include\Harlinn\Math\VectorMath.h`.

## Summary

- `AbsX()` :mutates: the `TupleSimd` instance by replacing the first component with its absolute value while leaving the remaining components unchanged.
- `WithAbsX()` :returns: a new `TupleSimd` instance whose first component is the absolute value of the original first component and whose other components equal the original ones.

Both functions operate on the internal SIMD register `simd` using the corresponding `Traits` implementation: `Traits::AbsX`.

Both are noexcept and implemented in a branchless, SIMD-friendly way via the `Traits` abstraction.

## Signatures

- `void AbsX() noexcept`
- `TupleSimd WithAbsX() const noexcept`

(Shown as implemented in `TupleSimd`.)

## Behavior

Let the tuple represented by `this->simd` have components \( [x, y, z, w] \) (only the first `Size` components are meaningful for the instantiated `TupleSimd`).

- `AbsX()` updates `simd` so its first component becomes \( |x| \) and the remaining components remain the same.

- `WithAbsX()` returns a `TupleSimd` value whose first component is \( |x| \) and whose remaining components equal the original values.

In mathjax notation:

- If the original vector is \(v = [x, v_{2}, v_{3}, \dots] \) then:

  - After calling `AbsX()` the new vector is \([|x|, v_{2}, v_{3}, \dots]\).
  - `WithAbsX()` returns \([|x|, v_{2}, v_{3}, \dots]\) leaving the original `TupleSimd` unchanged.

## Complexity and Guarantees

- Time complexity: O(1) per SIMD register operation; the call delegates to the `Traits::AbsX` implementation which runs in constant time relative to the SIMD width.
- No allocations are performed.
- Both functions are `noexcept` and safe for use in performance-critical code.

## Examples

Assume `Vector3f::Simd` is the SIMD form of a 3-component float vector.

Call `WithAbsX`:

```cpp
Math::Vector3f::Simd s = /* some SIMD vector with components [-1.0f, 2.0f, -3.0f] */;
auto r = s.WithAbsX(); // r has components [1.0f, 2.0f, -3.0f]
```

Call `AbsX`:

```cpp
Math::Vector3f::Simd s = /* some SIMD vector with components [-1.0f, 2.0f, -3.0f] */;
s.AbsX(); // s now has components [1.0f, 2.0f, -3.0f]
```

## Notes

- The exact implementation of the absolute operation is provided by the `Traits` type for the instantiated element type and SIMD width. For floating point types the implementation will produce the absolute value in a branchless way using bitwise or arithmetic SIMD instructions; for integer types the behavior follows the corresponding `Traits::AbsX` semantics.
- `WithAbsX()` is useful when an immutable style is desired or when chaining operations that return new SIMD objects is preferred.

## Reference

Implementation location: `Harlinn.Math\include\Harlinn\Math\VectorMath.h` (`TupleSimd` definition).

Look for the following members in `TupleSimd`:

- `void AbsX()`
- `TupleSimd WithAbsX() const`

These call `Traits::AbsX(simd)` internally.
