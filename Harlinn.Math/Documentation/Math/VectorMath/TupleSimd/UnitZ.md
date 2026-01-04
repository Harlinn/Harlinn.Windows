# `TupleSimd::UnitZ()`

## C++ signature

```cpp
static TupleSimd UnitZ() noexcept requires ( Size >= 3 )
```

## Summary

Returns a `TupleSimd` value whose Z (third) component is 1 and all other components are 0.

## Mathematical description

For a 3-component tuple this returns the unit vector along the Z axis:

\[
\mathrm{UnitZ}_3 = (0,\; 0,\; 1)
\]

For a tuple of dimension \(N\) with \(N \ge 3\), the result equals the vector

\[
\mathrm{UnitZ}_N = (0,\; 0,\; 1,\; 0,\; \dots,\; 0)
\]

where the 1 is at index 2 (zero-based indexing).

## Behavior and requirements

: The function is `noexcept` and constrained with `requires ( Size >= 3 )` so it can only be instantiated for `TupleSimd` specializations with at least 3 components.

: The returned value is constructed using the underlying `Traits::Set(...)` helper and then trimmed/packed to the `TupleSimd` representation.

## Example usage

```cpp
using Vec3Simd = SomeTupleType::Simd; // example alias to a TupleSimd type with Size >= 3
auto z = Vec3Simd::UnitZ(); // z holds (0, 0, 1)
```

## Notes

: The function returns the canonical unit vector along the Z axis in the `TupleSimd` representation. It is intended for use in SIMD-aware math code where constructing unit-axis vectors cheaply is useful for swizzles, rotations, and other vector operations.
