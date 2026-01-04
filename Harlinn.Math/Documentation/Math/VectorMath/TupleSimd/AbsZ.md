# `TupleSimd::AbsZ` and `TupleSimd::WithAbsZ`

## Overview

This document describes the behavior of the `AbsZ` and `WithAbsZ` member functions provided by the `TupleSimd` template (see `include/Harlinn/Math/VectorMath.h`). Both functions operate on the third component (Z) of the underlying SIMD register of a `TupleSimd` instance. Both functions require the `TupleSimd` specialization to have `Size > 2` (that is, the tuple must contain at least three components).

## Purpose

These functions compute the absolute value of the Z component of the SIMD vector.

- `AbsZ` updates the object in-place so that the Z component becomes its absolute value.
- `WithAbsZ` returns a new `TupleSimd` value where the Z component is replaced by its absolute value while the other components remain unchanged.

## Signatures

```cpp
void AbsZ( )           // member of TupleSimd; requires ( Size > 2 )
TupleSimd WithAbsZ() const noexcept  // member of TupleSimd; requires ( Size > 2 )
```

## Semantics

Let the SIMD register of a `TupleSimd` instance hold components \(x, y, z, w, ...\) (only the first `Size` components are meaningful). Denote the absolute value operator by vertical bars: \(|\cdot|\).

- `AbsZ()` transforms the SIMD register so that only the third component is replaced by its absolute value:

\[
(x, y, z, \ldots) \mapsto (x, y, |z|, \ldots)
\]

This operation modifies the instance itself.

- `WithAbsZ()` returns a new `TupleSimd` which has the same components as the original except that the third component is replaced by its absolute value:

\[
\text{WithAbsZ}(x, y, z, \ldots) = (x, y, |z|, \ldots)
\]

The original `TupleSimd` is not modified by `WithAbsZ()`.

## Implementation notes

- Both functions are implemented using the type's `Traits` helpers: `Traits::AbsZ(simd)` (or equivalent) to compute a SIMD value where only the Z lane has been absolute-valued.
- The `AbsZ()` overload typically assigns the result of the trait operation back into the member `simd`:

```cpp
simd = Traits::AbsZ(simd);
```

- The `WithAbsZ()` overload typically returns a `TupleSimd` constructed from the trait result, for example:

```cpp
return Traits::AbsZ(simd);
```

- Both functions are guarded by `requires ( Size > 2 )`, therefore they are only available for 3- and higher-component `TupleSimd` specializations.

## Example

Given a `TupleSimd` instance `t` with components `(1.0f, -2.0f, -3.5f, 0.0f)`: 

- Calling `t.AbsZ()` results in `t` holding `(1.0f, -2.0f, 3.5f, 0.0f)`.
- Calling `auto u = t.WithAbsZ()` returns a new `TupleSimd` `u` holding `(1.0f, -2.0f, 3.5f, 0.0f)` while `t` remains unchanged.

## Complexity

Both functions operate in constant time with respect to the tuple size since the underlying operation is a single SIMD operation that affects fixed lanes. They are implemented to be branchless and efficient on SIMD-capable platforms.

## Requirements

- Requires `TupleSimd` specialization with `Size > 2`.
- Requires the `Traits` type used by the `TupleSimd` to implement an `AbsZ` or equivalent operation.

## See also

- `TupleSimd::AbsX`, `TupleSimd::AbsY`, `TupleSimd::WithAbsX`, `TupleSimd::WithAbsY` for analogous operations on other components.
- `TupleSimd::WithNegatedZ` and `TupleSimd::NegateZ` for Z-component negation.
