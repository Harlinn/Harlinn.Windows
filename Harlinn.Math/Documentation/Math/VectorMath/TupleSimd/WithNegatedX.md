# `TupleSimd::WithNegatedX()`

Location: `Harlinn.Math\include\Harlinn\Math\VectorMath.h`

## Signature

`TupleSimd WithNegatedX() const noexcept`

## Description

Returns a new `TupleSimd` where the first component (X) is negated and all other components are unchanged. The operation is performed using the underlying `Traits::NegateX` SIMD implementation, so it is a branchless, constant-time SIMD operation on the packed components.

## Semantics (math notation)

Let the tuple represented by the SIMD register be

$$\mathbf{t} = (t_0, t_1, \dots, t_{n-1})$$

then `WithNegatedX()` returns

$$\mathbf{t}' = (-t_0, t_1, \dots, t_{n-1}).$$

For example, for a 4-component SIMD tuple:

$$(x, y, z, w) \mapsto (-x, y, z, w).$$

## Complexity

Constant time O(1) with respect to the tuple arity. The implementation uses SIMD intrinsics via the `Traits` layer to negate only the X lane.

## Behavior and notes

- The method is `const` and has no side effects; it returns a new `TupleSimd` instance.
- NaN and Inf values in the components are propagated according to IEEE floating point semantics; negation only flips the sign bit of the X component.
- The operation works for any `TupleSimd` `Size` supported by the `Traits` implementation.

## Example

```cpp
using Vec3Simd = Math::Vector<float,3>::Simd;

Vec3Simd v = /* ... */;
Vec3Simd r = v.WithNegatedX();
// r now holds the same components as v except the X component is negated
```

## Related members

- `SetX(...)` : set X from a value or SIMD source
- `NegateX()` : negates X in place
- `WithAbsX()` : returns a copy with the X component replaced by its absolute value

