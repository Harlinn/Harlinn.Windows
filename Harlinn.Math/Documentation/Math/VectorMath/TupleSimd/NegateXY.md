# `TupleSimd::NegateXY` and `TupleSimd::WithNegatedXY`

This document describes the `NegateXY` and `WithNegatedXY` member functions of the `TupleSimd` template defined in `include/Harlinn/Math/VectorMath.h`.

## Purpose

Both functions perform a component-wise negation of the first two components (X and Y) of the SIMD-backed tuple representation while leaving the remaining components unchanged.

Let the tuple represented by a `TupleSimd` instance be

\(v = (x, y, z, w)\)

then after applying the operation the components become

\(v' = (-x, -y, z, w)\).

For lower dimensional tuples the same rule applies to the existing components. For example for a 2-component tuple:

\(v = (x, y)\) becomes \(v' = (-x, -y)\).

## Function signatures

- `void NegateXY()`

  - Description: Mutates the calling `TupleSimd` instance so that its X and Y components are negated.
  - Exception safety: `noexcept` (implementation delegates to `Traits::NegateXY` which is noexcept in practice).
  - Complexity: constant time; implemented using a single SIMD operation provided by the `Traits` implementation.

- `TupleSimd WithNegatedXY() const noexcept`

  - Description: Returns a copy of the calling `TupleSimd` instance with X and Y components negated; the original instance is unchanged.
  - Return: a new `TupleSimd` value containing the result.
  - Exception safety: `noexcept`.
  - Complexity: constant time; implemented by calling `Traits::NegateXY` and returning the result.

## Semantics and remarks

- Both functions operate on the underlying SIMD register `simd` and call `Traits::NegateXY(simd)`.
- Only the first two components are affected; higher components (Z, W, etc.) are preserved.
- The functions are intended for performance: the negation is performed in a branchless, vectorized manner via the platform-specific `Traits` implementation.
- `WithNegatedXY` is useful when an immutable style is preferred, or when chaining operations without mutating the original value.

## Example usage

```cpp
// Assume Vector3f::Simd or a similar TupleSimd instance 't'
auto t = Vector3f::Simd( 1.0f, 2.0f, 3.0f );

// Mutating form
t.NegateXY( );
// now t represents (-1.0f, -2.0f, 3.0f)

// Non-mutating form
auto t2 = Vector3f::Simd( 1.0f, 2.0f, 3.0f );
auto t3 = t2.WithNegatedXY( );
// t2 is unchanged; t3 represents (-1.0f, -2.0f, 3.0f)
```

## Implementation note

Both members are thin wrappers over `Traits::NegateXY` defined for the concrete SIMD `Traits` type. This keeps the API independent from the underlying SIMD register type while providing an efficient vectorized implementation.

