# `TupleSimd::UnitW()`

Namespace: `Harlinn::Math`

Header: `Harlinn.Math\include\Harlinn\Math\VectorMath.h`

## Synopsis

This page documents the `UnitW` member function provided by the `TupleSimd` template. `UnitW` returns a SIMD tuple where the fourth component is set to 1 and all other components are set to 0.

## Full C++ signature

`static TupleSimd UnitW( ) noexcept requires ( Size >= 4 )`

> Location: `template<typename TupleT> class TupleSimd` in `VectorMath.h`

## Description

`UnitW` constructs and returns a `TupleSimd` whose components correspond to the unit vector pointing along the fourth axis. In coordinate form the returned tuple is:

$$e_{w} = (0,\;0,\;0,\;1)$$

The function is only available when the `TupleSimd` specialization has `Size >= 4` (see the `requires` clause). It is `noexcept` and returns the result by value.

## Semantics

- Preconditions: `Size >= 4`.
- Postconditions: The returned `TupleSimd` has its fourth component equal to 1 and all other components equal to 0.
- Exception safety: `noexcept`.
- Complexity: constant time, O(1).

## Mathematical notation

Given a tuple of dimension $n$ with $n \ge 4$, `UnitW()` returns the canonical basis vector

$$e_w = (0,\;0,\;0,\;1,\;0,\;\dots,\;0)\,,\quad\text{with }1\text{ at index }3\text{ (zero-based indexing)}.$$ 

When the tuple represents only four components, this simplifies to $e_w = (0,0,0,1)$.

## Example usage

```cpp
// Assume a Tuple type `MyTuple` with Size >= 4 and corresponding TupleSimd type `MyTuple::Simd`.
using SimdT = MyTuple::Simd;
auto u = SimdT::UnitW();
// u now holds the SIMD representation of (0, 0, 0, 1)
```

Or when using one of the provided aliases in the library (for a 4-component float tuple):

```cpp
using Vec4Simd = Math::Vector4f::Simd; // example
auto unitW = Vec4Simd::UnitW();
```

## Notes

- The ordering of values in the underlying SIMD register is determined by the `Traits::Set` implementation used by the `TupleSimd` specialization. Conceptually `UnitW()` exposes the fourth-component unit vector as documented above.
- This function complements `UnitX()`, `UnitY()`, and `UnitZ()` which return the corresponding unit vectors for the other axes.

## See also

- `TupleSimd::UnitX()`
- `TupleSimd::UnitY()`
- `TupleSimd::UnitZ()`
- `Tuple4::UnitW()` (Tuple counterpart defined for tuple types)

