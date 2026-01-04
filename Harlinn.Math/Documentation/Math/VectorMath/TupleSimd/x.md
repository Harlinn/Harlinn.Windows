# `TupleSimd::X()` and `TupleSimd::x()`

This document describes the `X()` and `x()` member functions of the `TupleSimd<...>` template implemented in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

## Overview

`TupleSimd` is a thin wrapper around a SIMD register that represents a tuple of numeric components (for example 2, 3, or 4 components). The `X()` and `x()` members provide convenient access to the first component of the underlying SIMD register:

- `X()` returns a `TupleSimd` in which every component is the first element of the original SIMD register.
- `x()` returns the scalar value of the first component.

These operations are implemented via the `Traits` associated with the `TupleSimd` type. The `Traits` layer provides the platform-specific SIMD operations such as `Trim`, `At<0>`, and `Extract<0>`.

## Signatures

- `TupleSimd X() const;`
- `value_type x() const;`

Here `value_type` refers to `TupleT::Traits::Type` (the floating or integer type of the tuple components).

## Semantics

Given a `TupleSimd` instance `t` holding components

$$t = (t_0, t_1, \dots, t_{n-1})$$

`X()` returns a `TupleSimd` whose components are all equal to the first component of `t`:

$$X(t) = (t_0, t_0, \dots, t_0).$$

`x()` returns the scalar first component:

$$x(t) = t_0.$$

## Implementation details

The implementation in `VectorMath.h` uses `Traits::At<0>(simd)` to obtain a SIMD value that contains the first element replicated to all lanes, and `Traits::Trim(...)` to ensure the returned `TupleSimd` has the correct format/upper lanes for tuple sizes smaller than the SIMD register capacity. Concretely:

- `X()` calls `Traits::Trim( Traits::At<0>( simd ) )` and constructs a `TupleSimd` from that SIMD value.
- `x()` calls `Traits::Extract<0>( simd )` which returns the scalar stored in lane 0 of the SIMD register.

These rely on the `Traits` implementation for the concrete `value_type` and `Size` to implement `At<0>`, `Trim` and `Extract<0>` efficiently using the best available SIMD instructions on the platform.

## Complexity

Both operations are constant time, O(1), and are implemented using a small number of SIMD instructions. No memory allocations occur.

## Exception and noexcept guarantees

Both `X()` and `x()` are implemented as `noexcept`-style operations in the header and do not throw exceptions. They perform pure arithmetic and SIMD manipulation.

## Examples

Assume `t` is a `TupleSimd` representing a 3-component tuple with components `(1.f, 2.f, 3.f)`:

- `t.X()` yields `(1.f, 1.f, 1.f)`.
- `t.x()` yields `1.f`.

Code example (conceptual):

```
// Given a TupleSimd<Vector3f> t; where t holds (1.f, 2.f, 3.f)
auto allX = t.X(); // allX contains (1.f, 1.f, 1.f)
auto first = t.x(); // first == 1.f
```

## Notes and constraints

- The behavior is defined for `TupleSimd` specializations where the underlying `Traits` provide `At<0>`, `Trim` and `Extract<0>`.
- `X()` returns a `TupleSimd` with the same logical `Size` as the original type, but with each lane equal to the first lane of the original SIMD register.
- Use `X()` when you need a SIMD vector filled with the first component. Use `x()` when you only need the scalar first component.

## Related functions

- `Y()` and `y()` provide equivalent operations for the second component.
- `Z()` and `z()`, `W()` and `w()` are provided for higher indices when `Size > 2` or `Size > 3` respectively.


## Reference

See the implementation in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`:

- `TupleSimd::X()` : uses `Traits::Trim( Traits::At<0>( simd ) )` to construct the result.
- `TupleSimd::x()` : uses `Traits::Extract<0>( simd )` to return the scalar.

This document is intended to help users of the `TupleSimd` template understand the intended semantics and performance characteristics of `X()` and `x()`.
