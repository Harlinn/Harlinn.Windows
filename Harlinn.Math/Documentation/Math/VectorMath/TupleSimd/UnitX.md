# `TupleSimd::UnitX()`

Category: `Harlinn::Math::TupleSimd` API reference

Source: `Harlinn.Math/include/Harlinn/Math/VectorMath.h`

## Purpose

Returns a `TupleSimd` value representing the unit vector along the X axis. The result has its first component equal to 1 and all remaining components equal to 0. In mathematical notation for a vector of size $n$:

\[ e_x = (1, 0, 0, \dots, 0) \]

This function is provided as a `static` member of the `TupleSimd<TupleT>` template and is intended as a convenient factory for creating the X-axis unit vector in SIMD form.

## C++ declaration

The function is declared inside the `TupleSimd` template as:

```cpp
static TupleSimd UnitX() noexcept
```

For context the surrounding template header is:

```cpp
template<typename TupleT>
class alignas( TupleT::Traits::AlignAs ) TupleSimd : public Internal::TupleSimdBase
{
public:
    using TupleType = TupleT;
    using Traits = typename TupleType::Traits;
    using value_type = typename Traits::Type;
    static constexpr size_type Size = TupleType::Size;

    // ...

    static TupleSimd UnitX() noexcept
    {
        return TupleSimd( Traits::Set( static_cast< value_type >( 1 ) ) );
    }

    // ...
};
```

## Behavior

- Returns a `TupleSimd` whose first component (X) is `1` and whose other components are `0`.
- The function is marked `noexcept` and does not allocate memory.
- It constructs the unit vector by calling `Traits::Set(1)` which sets the SIMD register so that the X lane is 1 and the remaining lanes are zeroed according to the `Traits` implementation.

## Mathematical note

If the tuple size is $n$, the returned vector corresponds to the standard basis vector $e_x \in \mathbb{R}^n$ with components:

\[ (e_x)_i = \begin{cases} 1 & i = 1 \\ 0 & i = 2,\dots,n \end{cases} \]

## Example usage

```cpp
using Vec3Simd = MyTuple3::Simd; // example: TupleSimd specialization
auto ux = Vec3Simd::UnitX();
// ux is (1, 0, 0) in SIMD representation
```

## See also

- `TupleSimd::UnitY()`
- `TupleSimd::UnitZ()`
- `TupleSimd::One()`
- `TupleSimd::Zero()`


(Generated documentation for the `UnitX` member function of `TupleSimd`.)