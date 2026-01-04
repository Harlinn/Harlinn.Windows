# `TupleSimd::Left()`

Defined in: `Harlinn.Math/include/Harlinn/Math/VectorMath.h`

## Function signature

```cpp
static TupleSimd Left() noexcept requires ( Size >= 3 )
```

## Description

Returns a `TupleSimd` representing the unit vector pointing to the left direction for tuple/tuple-simd types with at least 3 components.

For a `TupleSimd` of element type \(t\) and size \(n\) (with \(n \ge 3\)) the resulting vector has components:

\[
\mathrm{Left} = (-1, 0, 0, 0, \dots, 0)
\]

where the first component is \(-1\) and the remaining components are \(0\).

The function is constrained to only participate in overload resolution when `Size >= 3` using a `requires` clause.

## noexcept

The function is declared `noexcept` and does not throw exceptions.

## Example

```cpp
// Using a 3-component TupleSimd (e.g. Vector::Simd for Vector<float,3>)
auto left = TupleSimd::Left(); // left simd holds (-1, 0, 0)
```

## Notes

- The implementation constructs the result by calling `TupleSimd( Traits::Set( static_cast< value_type >( -1 ) ) )`, i.e. it relies on the `Traits::Set` helper to place -1 in the X component and zeros elsewhere.
- Because the function is `static` it is a type-level convenience for producing canonical direction vectors.
