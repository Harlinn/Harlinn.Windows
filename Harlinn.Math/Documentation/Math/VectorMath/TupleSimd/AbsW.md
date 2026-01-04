# `TupleSimd::AbsW` and `TupleSimd::WithAbsW`

This document describes the `AbsW` and `WithAbsW` member functions provided by the `TupleSimd` template in `VectorMath.h`.

## Summary

- `AbsW` : Mutates the `TupleSimd` instance by replacing the fourth component (W) with its absolute value while leaving the other components unchanged.
- `WithAbsW` : Returns a new `TupleSimd` with the fourth component set to its absolute value while leaving the original instance unchanged.

Both members are only available for `TupleSimd` instantiations that have `Size > 3` (that is, types with a W component).

## Requirements

- Template constraint: `requires ( Size > 3 )`.
- The implementation uses the underlying `Traits::AbsW` operation. For SIMD-backed implementations this maps to a per-component operation that computes the absolute value of the W lane without modifying X, Y and Z lanes.

## Function signatures

- `void AbsW()`: Mutates `this` so that its W component is replaced with `|w|`.

- `TupleSimd WithAbsW() const noexcept`: Returns a `TupleSimd` whose W component is `|w|`, leaving the original object untouched.

Example signatures from the header context (conceptual):

```cpp
void AbsW() requires ( Size > 3 );
TupleSimd WithAbsW() const noexcept requires ( Size > 3 );
```

## Semantics and behavior

Let a `TupleSimd` instance hold components `x`, `y`, `z` and `w` (the last component exists only when `Size >= 4`).

- `AbsW()` transforms the stored SIMD register so that the resulting component values are:

\[
\text{result} = (x, y, z, |w|)
\]

and then assigns this result back to the instance internal SIMD register.

- `WithAbsW()` returns a new `TupleSimd` equivalent to the instance with the W component replaced by its absolute value, i.e.:

\[
\text{returned} = (x, y, z, |w|)
\]

Both operations rely on `Traits::AbsW` to perform the work. For floating point lanes this will clear the sign bit of the W lane. For integer lanes the value will be transformed into its non-negative counterpart using the trait-provided operation.

## Complexity

Both operations are implemented as a single SIMD operation (via the `Traits` interface) followed by either an in-place assignment (`AbsW`) or a construction/return of the result (`WithAbsW`). The complexity is constant time in respect to the number of components.

## Example usage

```cpp
// Assume TupleSimd holds 4 components and ValueType is float
TupleSimd t( /* simd or values with w possibly negative */ );

// Mutating: set W to its absolute value
t.AbsW();

// Non-mutating: obtain a new tuple with absolute W
auto t2 = t.WithAbsW();
```

## Notes

- Both functions are implemented only when the `TupleSimd` specialization contains a W element: use them only with `Size >= 4`.
- The operations are branchless and rely on the platform-specific SIMD trait implementation for correctness and performance.

## See also

- `TupleSimd::WithAbsX` and `TupleSimd::WithAbsY` for analogous per-component absolute operations.
- `Traits::AbsW` for the trait-level implementation detail.

