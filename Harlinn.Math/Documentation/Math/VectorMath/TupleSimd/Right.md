# `TupleSimd::Right()`

Namespace: `Harlinn::Math`

Header: `Harlinn.Math\include\Harlinn\Math\VectorMath.h`

## Synopsis

This page documents the `Right` static member function of the `TupleSimd<TupleT>` template. `Right()` constructs and returns the unit vector pointing to the right (positive X) in the tuple's logical coordinate space.

## Full C++ signature

`static TupleSimd Right( ) noexcept requires ( Size >= 3 )`

> Location: `template<typename TupleT> class TupleSimd` in `VectorMath.h`

## Description

`Right()` returns a `TupleSimd` whose first component is 1 and whose remaining used components are 0. The function is constrained to tuple specializations with `Size >= 3`. The function is `noexcept` and returns by value.

Internally the implementation constructs the result using the tuple traits. The canonical implementation is equivalent to:

```cpp
return TupleSimd( Traits::Set( static_cast< value_type >( 1 ) ) );
```

The `Traits::Set` call populates the underlying SIMD register so that the logical component 0 (X) is set to `1`, and the other logical components are set to `0` according to the trait ordering used by the library.

## Mathematical notation

For a tuple of dimension $n$ with $n \ge 3$, `Right()` returns the canonical basis vector

$$e_{x} = (1,\;0,\;0,\;0,\;\dots,\;0)$$

When the tuple uses three components this reduces to

$$e_{x} = (1,\;0,\;0).$$

When the tuple uses four components this reduces to

$$e_{x} = (1,\;0,\;0,\;0).$$

Indices use zero based indexing: the value `1` is placed at index `0` (the X component).

## Properties

- Preconditions: `Size >= 3`.
- Postconditions: returned `TupleSimd` has X component equal to `1` and other used components equal to `0`.
- Exception safety: `noexcept`.
- Complexity: constant time, O(1).

## Example usage

```cpp
// Assume a Tuple type `MyTuple` with Size >= 3 and corresponding TupleSimd alias MyTuple::Simd
using SimdT = MyTuple::Simd;
auto right = SimdT::Right();
// right now holds the SIMD representation of (1, 0, 0, ...)
```

## Implementation notes

- The exact bit layout and ordering in the SIMD register are determined by `TupleT::Traits`. `Traits::Set(...)` is the portable way in this library to initialize lane values in the order the library expects.
- `Right()` is intended as a convenience factory for the canonical unit vector along the X axis and is commonly used together with `Up()`, `Forward()`, and similar direction factories.

## See also

- `TupleSimd::UnitX()`
- `TupleSimd::Left()`
- `TupleSimd::Up()`
- `TupleSimd::Forward()`

Source: `Harlinn.Math\include\Harlinn\Math\VectorMath.h`