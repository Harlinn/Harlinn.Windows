# `TupleSimd::HasNaN()`

This document describes the `HasNaN()` member function implemented for the `TupleSimd<TupleT>` template in `VectorMath.h`.

## Location

- Header: `Harlinn.Math/include/Harlinn/Math/VectorMath.h`
- Class: `TupleSimd<TupleT>`

## Signature

`bool HasNaN() const noexcept`

## Template constraints

- `TupleT` is a tuple type derived from `Tuple2`, `Tuple3`, or `Tuple4` and `TupleSimd<TupleT>` uses `TupleT::Traits`.

## Description

`HasNaN()` tests whether any component held in the internal SIMD register of the `TupleSimd` instance is a NaN (Not a Number).

The implementation delegates to the SIMD trait function `Traits::HasNaN(simd)` and therefore the actual test is performed on the underlying SIMD register representation.

Formally, for a tuple value with components \(v_0, v_1, \dots, v_{n-1}\) (where \(n = \mathrm{Size}\)), the function returns `true` iff:

\[
\exists\,i\in\{0,\dots,n-1\}\;:\;\mathrm{isnan}(v_i)
\]

Otherwise it returns `false`.

## Exception and noexcept guarantee

- The function is declared `noexcept` and does not throw exceptions.

## Complexity

- The check is performed using a SIMD trait operation on the contained SIMD register. Complexity is constant time relative to the SIMD width used by the Traits implementation.

## Notes

- Because the function relies on `Traits::HasNaN`, correctness depends on the trait implementation for the element type and SIMD width.
- For tuple sizes that are represented by fewer-than-full SIMD lanes, the trait is expected to treat inactive or padded lanes appropriately so that they do not produce false positive NaN results.

## Example

```cpp
using MyTupleSimd = MyTuple::Simd; // MyTuple is a Tuple2/3/4-derived type
MyTupleSimd t = /* construct or load values */;
if (t.HasNaN())
{
    // Handle invalid input
}
```

## Cross-reference

- See `TupleSimd::HasNaN()` implementation in `VectorMath.h` for the exact delegation to `Traits::HasNaN(simd)`.

