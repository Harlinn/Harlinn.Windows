# TupleSimd::Backward

This document describes the `Backward` member function of the `TupleSimd` template defined in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

## Purpose

`Backward` returns a `TupleSimd` representing the backward direction vector. In the project's coordinate convention, "backward" corresponds to the positive X axis. Mathematically:

\[ \mathbf{b} = (1, 0, 0) \]

The returned value is constructed using the SIMD `Traits::Set(...)` helper so the components are placed directly into the underlying SIMD register.

## Full C++ signature

The function appears in the `TupleSimd<TupleT>` template and has the following signature:

```cpp
static TupleSimd Backward() noexcept requires ( Size >= 3 )
```

If shown in a minimal class context it looks like:

```cpp
template<typename TupleT>
class TupleSimd
{
public:
    using value_type = typename TupleT::Traits::Type;
    static constexpr size_t Size = TupleT::Size;

    static TupleSimd Backward() noexcept requires ( Size >= 3 );
};
```

## Behavior and details

- Constraints: The function is only available when `Size >= 3` (it requires the tuple to have at least 3 components).
- Exception safety: `noexcept` — the function does not throw.
- Implementation: the function constructs a SIMD register with components set so that the first component is `1` and the remaining first three components are the usual axis components. In code it uses `Traits::Set( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) )` and initializes a `TupleSimd` with that SIMD value.
- Return: a `TupleSimd` whose `simd` member represents the vector \((1,0,0,\ldots)\) (first three components are meaningful for the `Size >= 3` case).

## Related functions

- `TupleSimd::Forward() noexcept requires ( Size >= 3 )` : returns \((-1,0,0)\).
- `TupleSimd::UnitX()` / `TupleSimd::UnitY()` / `TupleSimd::UnitZ()` : axis unit vectors.

## Example usage

```cpp
using VecSimd = SomeTuple::Simd; // e.g. a TupleSimd specialization
auto back = VecSimd::Backward();
// back is a TupleSimd with value (1, 0, 0)
```

## Notes

- The exact returned type is `TupleSimd<TupleT>` where `TupleT` is the tuple type used to instantiate `TupleSimd`.
- The implementation uses the `Traits` of `TupleT` so the returned SIMD register matches the element type and SIMD layout of the tuple specialization.

References: `Harlinn.Math/include/Harlinn/Math/VectorMath.h` (search for `Backward()` in `TupleSimd`).
