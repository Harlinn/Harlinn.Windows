# `TupleSimd::Up()`

## Function signature

```cpp
// Member of: template<typename TupleT> class TupleSimd
static TupleSimd Up() noexcept requires ( Size >= 3 );
```

## Description

Returns the unit "up" vector for tuple types with at least three components. Conceptually this function yields the vector

$$\mathbf{u}_{\text{up}} = (0,\;1,\;0)$$

in the coordinate system used by the `Tuple`/`TupleSimd` types.

The function is `static` and `noexcept` and is constrained by the `requires ( Size >= 3 )` clause, so it is only available when the tuple size is three or greater.

## Semantics

- The operation is constant-time and returns a `TupleSimd` where the component corresponding to the Y-axis is set to one and the remaining components are set to zero.
- The returned object is a SIMD-backed representation constructed via the underlying `Traits::Set` helper.

## Return value

- Type: `TupleSimd`
- Value: the unit up vector; for example, for 3-component tuples the value is equivalent to $(0, 1, 0)$.

## Example usage

```cpp
using Vec3Simd = MyTuple::Simd; // example alias for a 3-component SIMD tuple type

// Obtain the up vector (Y unit)
auto upSimd = Vec3Simd::Up();

// Use with tuple values (non-SIMD) via conversion if needed
MyTuple upTuple = upSimd.Values();
```

## Notes

- This function is intended for math and graphics code that needs a canonical up direction.
- Because the implementation uses the `Traits` abstraction it adapts to the underlying SIMD type and element type for the `TupleT` template parameter.
- The function is only present when `Size >= 3`: use other helpers (`UnitX`, `UnitY`, `UnitZ`) for smaller or specific needs.

## Implementation reference

The implementation in `include/Harlinn/Math/VectorMath.h` is:

```cpp
static TupleSimd Up() noexcept requires ( Size >= 3 )
{
    return TupleSimd( Traits::Set( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ) ) );
}
```

(The implementation delegates to `Traits::Set` to construct the SIMD register used by the `TupleSimd` wrapper.)
