# `TupleSimd::SetZ`

Summary:

This page documents the `SetZ` member functions on the `TupleSimd<TupleT>` template (defined in `include/Harlinn/Math/VectorMath.h`). `SetZ` assigns the third component (z) of the underlying SIMD register while keeping other components unchanged.

Requirements:

- The `SetZ` overloads are available only when the `TupleSimd` `Size > 2` (that is, for tuples with at least three components).
- All overloads are `noexcept` in the implementation and use the `TupleT::Traits` helper functions to perform the operation efficiently.

Signatures:

- `void SetZ( SIMDType src ) requires ( Size > 2 )`
- `void SetZ( const TupleSimd& src ) requires ( Size > 2 )`
- `void SetZ( const value_type value ) requires ( Size > 2 )`

Behavior:

Let the SIMD register of the current `TupleSimd` instance be represented as

\[ s = (s_0, s_1, s_2, s_3, \dots ) \]

and the provided `src` SIMD register be

\[ r = (r_0, r_1, r_2, r_3, \dots ) \].

The `SetZ` operation replaces the third component of `s` (the component conventionally named `z`) with the corresponding component from the source, leaving the other components unchanged. Using 0-based indexing the assignment is:

\[ s_2 \leftarrow r_2 \]

Overloads explained:

- `SetZ( SIMDType src )`:
  - Directly updates the SIMD register by permuting and combining `simd` and `src` via the corresponding `Traits::Permute` implementation. This is the lowest-level and most efficient overload for SIMD-aware callers.

- `SetZ( const TupleSimd& src )`:
  - Convenience overload that extracts the underlying `SIMDType` from `src` and calls the `SIMDType` overload. Effectively identical to calling `SetZ( src.simd )`.

- `SetZ( const value_type value )`:
  - Broadcasts `value` to a SIMD register where the value occupies the lanes intended for the `z` component, then calls the SIMD overload to update only the third component. Effectively it performs:

  \[ s_2 \leftarrow \text{value} \]

Notes and implementation details:

- The implementation relies on `TupleT::Traits` to perform lane extraction and permutation. The concrete permutation used (for example `Traits::Permute<0, 1, 6, 3>(simd, src)` in the source) is chosen to leave other lanes intact while replacing the z lane.

- Because `TupleSimd` is a thin wrapper around a SIMD register, `SetZ` is implemented in a branchless manner and is suitable for hot math loops.

- Use `SetZ` when you need to modify only the z component without performing a full load/store of the whole tuple.

Examples:

Assume `TupleSimd` is instantiated for a 4-lane float tuple and `t` is a `TupleSimd` representing `(x, y, z, w)`:

```cpp
// set z from another TupleSimd
TupleSimd t, s; // t = (x, y, z, w), s = (x2, y2, z2, w2)
t.SetZ( s ); // t becomes (x, y, z2, w)

// set z from scalar
float newZ = 3.14f;
t.SetZ( newZ ); // t becomes (x, y, 3.14f, w)
```

See also:

- `TupleSimd::SetX` and `TupleSimd::SetY` for analogous operations on other components.
- `TupleSimd::SetXYZ` for assigning multiple components at once.

File reference:

- Implementation: `include/Harlinn/Math/VectorMath.h` (search for `SetZ` within `TupleSimd`).

