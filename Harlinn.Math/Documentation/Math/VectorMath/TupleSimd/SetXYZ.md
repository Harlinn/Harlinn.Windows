# `TupleSimd::SetXYZ`

This document describes the `SetXYZ` member functions of the `TupleSimd` template implemented in `include\Harlinn\Math\VectorMath.h`.

## Purpose

`SetXYZ` sets the first three components of a `TupleSimd` SIMD register from a source SIMD value, another `TupleSimd`, or three scalar values. The remaining components are preserved when applicable.

## Prototypes

- `void SetXYZ( SIMDType src ) requires ( Size > 2 )`
- `void SetXYZ( const TupleSimd& src ) requires ( Size > 2 )`
- `void SetXYZ( const value_type x, const value_type y, const value_type z ) requires ( Size > 2 )`

## Semantics

Let the SIMD-backed register of `this` be denoted by $\mathbf{s}$ and the source SIMD value be $\mathbf{r}$.

- `SetXYZ( SIMDType src )`:
  - Sets the first three components of $\mathbf{s}$ to the first three components of $\mathbf{r}$.
  - Leaves any remaining components of $\mathbf{s}$ unchanged.
  - The function requires `Size > 2` so that the tuple has at least three components.
  - Implementation uses a lane permute/insert operation via `Traits::Permute<0,1,2,7>( src, simd )` to place the three values into the SIMD register while preserving the other lanes.

- `SetXYZ( const TupleSimd& src )`:
  - Convenience overload that forwards to `SetXYZ( src.simd )`.
  - Requires `Size > 2` by the forwarded call.

- `SetXYZ( const value_type x, const value_type y, const value_type z )`:
  - Constructs an intermediate SIMD value from the three scalar components by calling `Traits::Set( z, y, x )` and forwards to `SetXYZ( SIMDType )`.
  - After the call, the first component equals `x`, the second equals `y`, and the third equals `z`.

In mathematical notation: if the result SIMD register after the operation is $\mathbf{s}'$ and the input triple is $(x, y, z)$, then

\[ s'_0 = x, \quad s'_1 = y, \quad s'_2 = z, \quad s'_i = s_i \text{ for } i \ge 3. \]

## Examples

- Replace X, Y and Z from another SIMD value `srcSimd`:

```
TupleSimd t;
t.SetXYZ( srcSimd );
```

- Replace X, Y and Z from another `TupleSimd` `other`:

```
TupleSimd t;
t.SetXYZ( other );
```

- Replace X, Y and Z from scalar values:

```
TupleSimd t;
t.SetXYZ( 1.0f, 2.0f, 3.0f );
```

## Complexity

All overloads run in constant time: O(1).

## Notes and safety

- The overloads are constrained with `requires ( Size > 2 )` to ensure a minimum of three components.
- The operation preserves lanes that are not part of X, Y and Z. This is important when the SIMD register contains extra packed values (for example when `Capacity` > `Size`).

## See also

- `SetX`, `SetY`, `SetZ`, `SetW`: related per-component setters implemented alongside `SetXYZ`.
- `WithAbsXY`, `WithNegatedXY`: utilities that create modified copies rather than mutating in place.

