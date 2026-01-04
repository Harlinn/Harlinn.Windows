# `TupleSimd::One`

Purpose

This document describes the `One` static member function of the `TupleSimd< TupleT >` template defined in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

Synopsis

```cpp
// inside template<typename TupleT>
static TupleSimd One() noexcept;
```

Description

`TupleSimd::One()` returns a `TupleSimd` instance where each component is set to the multiplicative identity value `1` for the underlying `value_type` of `TupleT`.

If the tuple arity is \(n\) (accessible as `TupleT::Size`), the call is equivalent to returning the vector

\[
\mathbf{1}_n = (1, 1, \dots, 1) \in \mathbb{R}^n
\]

Implementation notes

- The function is `noexcept` and returns a `TupleSimd` constructed from `Traits::Fill<Size>(1)` where `Traits` is `TupleT::Traits`.
- The underlying implementation uses the SIMD `Fill` helper. Conceptually:

```text
return TupleSimd( Traits::Fill<Size>( static_cast< value_type >( 1 ) ) );
```

- Requirements: `TupleT` must define a nested `Traits` type exposing `Fill<k>(...)` and `Size` must be the tuple arity (commonly 2, 3, 4, or 8 for the library).

Semantics and examples

- For `TupleT::Size == 2` returning `One()` yields \((1, 1)\).
- For `TupleT::Size == 3` returning `One()` yields \((1, 1, 1)\).
- For `TupleT::Size == 4` returning `One()` yields \((1, 1, 1, 1)\).

Example usage

```cpp
using V3Simd = Vector<float, 3>::Simd; // TupleSimd specialization for a 3-vec of float
auto ones = V3Simd::One();
// ones now holds the SIMD value with all elements equal to 1.0f

// Convert back to tuple type for inspection
auto tuple = ones.Values(); // Tuple3<Vector<float,3>, float>
std::cout << tuple.ToString(); // prints something like "[1, 1, 1]"
```

Complexity

The operation is constant time in terms of the logical vector size because it uses a single SIMD fill operation. The cost is the cost of constructing the SIMD register with repeated value `1`.

Notes

- The returned `TupleSimd` is intended for use in SIMD pipelines. Use `Values()` or conversion to the associated `TupleT` when you need a structural tuple for API boundaries or serialization.
- The function creates values equal to the numeral `1` converted to the `value_type` of `TupleT`.

See also

- `TupleSimd::Zero()` for the zero vector.
- `TupleT::One()` on tuple types that provide structural equivalents.
