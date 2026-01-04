# TupleSimd::Z and TupleSimd::z

This document describes the `Z` and `z` member functions of the `TupleSimd` template defined in `VectorMath.h`.

## Summary

- `Z()` : Returns a `TupleSimd` in which every element is the third (index 2) component of the original SIMD register.
- `z()` : Returns the scalar value of the third component (index 2) of the SIMD register.

Both members require that the `TupleSimd` `Size` is greater than 2 (i.e., the tuple contains at least three elements).

## Signatures

- `TupleSimd Z() const requires ( Size > 2 )`
- `value_type z() const requires ( Size > 2 )`

Here `value_type` is the scalar element type for the tuple and `Size` is the number of logical components in the tuple type.

## Semantics

Let the SIMD representation of a `TupleSimd` instance be

$$\mathrm{simd} = (s_0, s_1, s_2, s_3, \dots)$$

and let the logical tuple components be the first `Size` elements of `simd`:

$$v = (v_0, v_1, v_2, \dots, v_{\text{Size}-1})$$

where typically $v_i = s_i$ for $0 \le i < \text{Size}$.

- `Z()` returns a `TupleSimd` whose every element equals the original third component $v_2$:

$$Z(v) = (v_2, v_2, v_2, \dots, v_2)$$

The implementation uses `Traits::At<2>(simd)` to broadcast or extract the third component into a SIMD register and then `Traits::Trim(...)` to produce the returned `TupleSimd` with the correct logical size.

- `z()` extracts and returns the scalar third component:

$$z(v) = v_2$$

The implementation uses `Traits::Extract<2>(simd)` to obtain the scalar value.

## Preconditions and Constraints

- The tuple `Size` must be greater than 2 (the functions are constrained with `requires ( Size > 2 )`).
- The underlying `Traits` type must provide `At<2>` and `Extract<2>` implementations.

## Complexity

Both operations run in constant time by operating directly on the SIMD register:

- `Z()` is O(1) and typically maps to a small number of SIMD instructions: broadcast/permute plus masking/trim.
- `z()` is O(1) and typically maps to a SIMD extract or scalar read.

## Example usage

```cpp
using Vec3Simd = MyTuple3::Simd; // example type alias
Vec3Simd t = ...;              // a TupleSimd with Size == 3

// Broadcast the third component to all lanes
auto zBroadcast = t.Z(); // zBroadcast: (t.z, t.z, t.z)

// Extract the third component as a scalar
auto scalarZ = t.z();    // scalarZ == t.z
```

## Notes

- `Z()` is useful when you need a SIMD vector where every lane holds the third component, for example to perform component-wise operations using SIMD instructions.
- `z()` is useful when you need the raw scalar component for branching, logging, or scalar arithmetic.
- The concrete behavior depends on the `SIMD::Traits` specialization for the element type and capacity.

