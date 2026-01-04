# `TupleSimd::SetW`

This page documents the `SetW` member functions of the `TupleSimd` template in `VectorMath.h`.

## Purpose

`SetW` updates the W (fourth) component of a `TupleSimd` instance while preserving the X, Y and Z components. The functions apply only when the tuple size satisfies `Size > 3`.

## Overloads

1. `void SetW( SIMDType src )`

   - Requirements: `Size > 3`.
   - Description: Replace the W component of this `TupleSimd` with the W component extracted from `src` while keeping X, Y and Z unchanged.
   - Example: If before call the SIMD register represents the vector \(v = (x, y, z, w)\) and `src` contains \((a, b, c, d)\), then after `SetW(src)` the vector becomes
     \[ v' = (x, y, z, d) \]

2. `void SetW( const TupleSimd& src )`

   - Requirements: `Size > 3`.
   - Description: Convenience overload that copies the W component from another `TupleSimd` instance. Equivalent to calling `SetW( src.simd )`.
   - Example: If `t` is `(x, y, z, w)` and `s` is `(a, b, c, d)`, then `t.SetW( s )` yields
     \[ t = (x, y, z, d) \]

3. `void SetW( const value_type value )`

   - Requirements: `Size > 3`.
   - Description: Set the W component to a scalar `value` for all lanes used to derive the W component. Internally this uses `Traits::Fill<Size>( value )` and then sets W accordingly.
   - Example: With `t = (x, y, z, w)` and scalar `v`, `t.SetW( v )` yields
     \[ t = (x, y, z, v) \]

## Notes

- All overloads only affect the W component. X, Y and Z remain unchanged.
- These members are gated by the `requires ( Size > 3 )` constraint. They are intended for tuple sizes with a W component (for example, 4-element tuples).
- The implementation uses a `Permute` operation on the underlying SIMD representation to achieve the component replacement efficiently while avoiding scalar loads/stores when possible.

## Example usage

```cpp
// Assume TupleSimd<Vector4f> t, s; and float value;
// Replace W from another SIMD value
SIMDType srcSimd = /* some SIMD value with desired w */;
t.SetW( srcSimd );

// Replace W from another TupleSimd
t.SetW( s );

// Replace W using scalar
t.SetW( value );
```

## See also

- `TupleSimd::X`, `TupleSimd::Y`, `TupleSimd::Z` accessors and the `Permute` trait used for lane manipulation.
- `Traits::Fill`, `Traits::Permute` for details on how values and lanes are formed and rearranged.
