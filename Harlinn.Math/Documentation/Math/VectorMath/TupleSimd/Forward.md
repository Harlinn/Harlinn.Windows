# `TupleSimd::Forward()`

This page documents the `Forward` static member of the `TupleSimd` template implemented in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

## Function signature

```cpp
static TupleSimd Forward( ) noexcept requires ( Size >= 3 )
```

## Summary

Returns a `TupleSimd` containing the unit vector that represents the forward direction for 3D tuples: the vector

\[
\mathbf{f} = (-1,\; 0,\; 0)
\]

The function is constrained to tuple SIMD types with at least 3 components: `Size >= 3`.

## Behavior

- No parameters
- Guaranteed `noexcept`
- Constraint: the member is only available when `TupleSimd::Size >= 3`.

The returned value is produced via the underlying `Traits::Set` call used by the SIMD traits in the implementation. The result is a SIMD-packed representation of the forward unit vector.

## Return value

- Type: `TupleSimd`
- Semantics: a SIMD tuple whose components correspond to the forward unit vector components listed above.

## Example usage

```cpp
using VecSimd = SomeTupleType::Simd; // where SomeTupleType::Size >= 3
auto f = VecSimd::Forward();
// f represents the forward unit vector: (-1, 0, 0)
```

## Notes

- The exact memory layout and lane ordering is governed by the `Traits` implementation for the chosen `TupleSimd` specialization. The documented component vector is the logical mathematical result.
- Use `TupleSimd::Forward()` when you need a SIMD-friendly representation of the forward direction in 3D math kernels.
