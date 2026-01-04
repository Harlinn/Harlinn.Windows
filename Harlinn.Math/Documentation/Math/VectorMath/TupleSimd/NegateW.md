# `TupleSimd::NegateW` and `TupleSimd::WithNegatedW`

This document describes the `NegateW` and `WithNegatedW` member functions of the `TupleSimd` template defined in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

## Overview

Both functions operate on the fourth component (W) of a SIMD-backed tuple value. For a 4-component tuple represented as

\[
\mathbf{v} = (v_x, v_y, v_z, v_w),
\]

these functions produce a result where the first three components are unchanged and the W component is negated:

\[
\mathbf{v'} = (v_x, v_y, v_z, -v_w).
\]

The functions are only available when `TupleSimd::Size > 3` (that is, for types with at least 4 components).

## `NegateW`

- Declaration (conceptual):

`void NegateW() requires ( Size > 3 );`

- Behavior: Mutates the `TupleSimd` instance in place by negating only the W component while leaving X, Y and Z unchanged.

- Implementation detail: The method delegates to the SIMD traits implementation via `simd = Traits::NegateW(simd);` so the operation is performed using the underlying SIMD register and preserves any architecture-specific optimizations.

- Example:

```cpp
TupleSimd t; // holds (x, y, z, w)
t.NegateW(); // t now holds (x, y, z, -w)
```

- Complexity: O(1) work: single SIMD operation.

## `WithNegatedW`

- Declaration (conceptual):

`TupleSimd WithNegatedW() const requires ( Size > 3 );`

- Behavior: Returns a new `TupleSimd` value with the W component negated and the other components unchanged. The original object is not modified.

- Implementation detail: The method returns `Traits::NegateW(simd)` wrapped as a `TupleSimd` instance. The call uses the underlying SIMD traits so the result is computed using SIMD instructions when available.

- Example:

```cpp
TupleSimd t; // holds (x, y, z, w)
auto t2 = t.WithNegatedW(); // t remains (x, y, z, w)
                          // t2 holds (x, y, z, -w)
```

- Complexity: O(1) work: single SIMD operation and construction of the returned `TupleSimd`.

## Notes and considerations

- These functions rely on `Traits::NegateW` being defined for the tuple's `Traits` type. The effect and exact instruction sequence depend on the SIMD implementation for the underlying element type.

- For `TupleSimd` specializations with more than 4 elements (for example, packed formats), the operation negates the logical W element exposed by `TupleSimd::Size` and the corresponding lane in the SIMD register; higher lanes are not affected unless the SIMD `NegateW` implementation does so intentionally.

- Use `WithNegatedW` when an immutable-style operation is preferred and `NegateW` when in-place modification is desired for performance reasons.

## See also

- `TupleSimd::SetW`, `TupleSimd::AbsW`, `TupleSimd::WithAbsW` for related per-component operations in `VectorMath.h`.