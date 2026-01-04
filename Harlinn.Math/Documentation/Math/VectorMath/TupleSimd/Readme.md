# TupleSimd

This document describes the `TupleSimd<TupleT>` template implemented in `Harlinn.Math\include\Harlinn\Math\VectorMath.h`.

TupleSimd is a thin, high-performance wrapper around a SIMD register that represents the SIMD form of tuple types derived from `Tuple2`, `Tuple3`, and `Tuple4` (and related higher-capacity packs). It exposes per-component math implemented by `TupleT::Traits` and is intended for use in math kernels where minimizing loads/stores and keeping values in registers is important.

Contents

- Overview
- Requirements for `TupleT`
- Key operations and API
- Design and performance notes
- Safety and correctness
- Examples: common 2D graphics operations
- Examples: common 3D graphics operations


## Overview

`TupleSimd<TupleT>` holds a single SIMD register called `simd` and exposes operations implemented through `TupleT::Traits`.

The typical internal model is:

- `TupleT` is a tuple type (`Tuple2`/`Tuple3`/`Tuple4`) that defines `Traits`, `ArrayType`, `Size`, and `Simd`.
- `Traits` supplies low-level SIMD primitives: `SIMDType`, `Load`, `Store`, `Add`, `Sub`, `Mul`, `Div`, `Negate`, `Fill`, `Set`, `Extract`, `Permute`, `Trim`, `HSum`, `Dot`, and many more.

TupleSimd aims to make it straightforward to implement vectorized algorithms where you operate on packed components rather than repeated scalar fields.


## Requirements for `TupleT`

`TupleT` must provide:

- `using Traits = SIMD::Traits<...>`: a traits type that exposes the SIMD operations described above.
- `using ArrayType`: contiguous storage that `Traits::Load` and `Traits::Store` accept.
- `static constexpr size_t Size`: number of logical components used by the tuple (2, 3, 4, etc.).
- `using Simd = TupleSimd<TupleT>`: an alias back to the SIMD wrapper type.

Additionally `Traits` must expose: `Type`, `SIMDType`, `AlignAs`, `SIMDTypeCapacity`, and relevant math operations used by TupleSimd wrappers.


## Key operations and API

Construction and conversion

- Default constructs to zero: `TupleSimd()` -> `simd = Traits::Zero()`.
- Construct from raw SIMD register: `TupleSimd( SIMDType )`.
- Construct from `TupleT` or from `ArrayType` via `Traits::Load`.
- Scalar constructors for small arities: e.g., for `Size==3`, `TupleSimd(x,y,z)`.
- Implicit/explicit conversions between compatible `Simd` types are supported via constrained templates.
- `TupleType Values() const noexcept` materializes the structural `TupleT` from the SIMD register.

Accessors and per-component utilities

- `X()`, `Y()`, `Z()`, `W()` return a `TupleSimd` with the requested element broadcasted to all lanes.
- `x()`, `y()`, `z()`, `w()` extract a single element as the scalar `value_type`.
- `SetX`, `SetY`, `SetZ`, `SetW` accept `SIMDType`, another `TupleSimd`, or a scalar and update the corresponding lane.
- `WithAbsX()`, `WithNegatedY()`, `AbsXY()` produce new `TupleSimd` objects with lane-wise transformations computed branchlessly via `Traits`.

Arithmetic and comparison

- Operators `+ - * /` are defined between `TupleSimd`, between `TupleSimd` and scalar, and via free functions that accept tuple or SIMD types. All arithmetic delegates to `Traits::Add`, `Traits::Sub`, `Traits::Mul`, `Traits::Div`.
- Comparison helpers: `AnyLess`, `AllLess`, `AnyEqual`, `AllEqual`, `Select`, `IsNaN`, `IsInf` etc. return mask-style `TupleSimd` or boolean queries implemented through `Traits`.

Higher-level math

- Horizontal ops: `HSum`, `HProd`, `ScalarHSum`, `ScalarHProd`.
- Vector ops: `Dot`, `Cross`, `Length`, `Normalize`, `Reflect`, `Refract`.
- Element-wise math: `Sqrt`, `Exp`, `Log`, trig and hyperbolic functions.
- Utility operations: `Clamp`, `ClampLength`, `Lerp`, `EvaluatePolynomial`.

Interoperability

- Free functions in `Internal` provide `ToSimd`, `ToSimdType`, and `MakeResultType` to help write algorithms that accept either tuple or SIMD wrappers and produce the appropriate return type.


## Design and performance notes

- TupleSimd is a single-field wrapper around the SIMD register. It is intended to be passed by reference to avoid copies: copying SIMD wrappers may be cheap but passing by reference avoids unnecessary register spills in hot kernels.
- All operations call into `Traits` to ensure both correctness and that the best available instruction sequences are used on the target architecture.
- `Size` is used to `Trim` or `Fill` results when working with lane widths larger than the logical tuple arity.
- Many lane-specific operations are branchless and implemented using `Permute` and `Extract` helpers from `Traits`.


## Safety and correctness

- `HasNaN()` queries if any lane contains a NaN using `Traits::HasNaN`.
- `operator bool()` yields true if any lane is non-zero via `Traits::AnyNotEqual( simd, Traits::Zero() )`.
- For divisions, `Traits::FillDivisor<Size>(value)` may be used to set safe divisor lanes.
- Equality and near-equality helpers accept epsilon arguments and produce mask-style results or boolean aggregates.


## Examples: common 2D graphics operations

The examples below use the public aliases `Vector2f = Vector<float,2>` and its `Simd` wrapper type. They assume `using namespace Harlinn::Math;`.

Note: code examples show idiomatic usage of `TupleSimd` via the `Simd` alias on tuple types.

1) 2D translation (applying a translation to an array of points in SIMD form):

```cpp
// Translate a point by a 2D translation vector
Vector2f::Simd translateSimd = Vector2f::Simd( 1.5f, -2.0f ); // broadcasted via Fill for Size==2
Vector2f::Simd pointSimd = Vector2f::Simd( Vector2f( 10.0f, 5.0f ) );

auto translated = pointSimd + translateSimd; // does per-lane addition in SIMD
Vector2f result = translated.Values();
// result: [11.5f, 3.0f]
```

2) 2D rotation about the origin: use a rotation matrix applied to a 2D vector expanded into SIMD lanes. For small arrays, convert to `Simd` and use element ops:

Let rotation by angle \(\theta\):

\[ R = \begin{bmatrix} \cos\theta & -\sin\theta \\ \sin\theta & \cos\theta \end{bmatrix} \]

```cpp
float theta = 0.78539816339f; // 45 degrees
Vector2f::Simd v( Vector2f( 1.0f, 0.0f ) );

// Compute cos and sin using SIMD trig through Traits
auto cs = Math::SinCos( v ); // for small cases use scalar trig then build simd
// Simpler: compute scalars and set
float c = std::cos( theta );
float s = std::sin( theta );

// Apply rotation in scalar lanes and construct a new Simd
Vector2f rotated( v.x() * c - v.y() * s, v.x() * s + v.y() * c );
// Or use Simd arithmetic if you have simd-packed cos/sin
```

3) 2D dot product and length:

```cpp
Vector2f a( 3.0f, 4.0f );
Vector2f b( 1.0f, 2.0f );

auto aSimd = a.ToSimd();
auto bSimd = b.ToSimd();

auto dotSimd = Math::Dot( aSimd, bSimd ); // returns SIMD wrapper containing horizontal dot
float dotScalar = dotSimd.x(); // or Traits::First( dotSimd.simd )

// length of a
float length = Math::ScalarLength( a ); // uses HSum and Sqrt via Traits
```


## Examples: common 3D graphics operations

These examples use `Vector3f = Vector<float,3>`; use `Vector3f::Simd` for SIMD form.

1) Cross product and normal computation

```cpp
Vector3f v1( 1.0f, 0.0f, 0.0f );
Vector3f v2( 0.0f, 1.0f, 0.0f );

auto n = Math::Cross( v1, v2 ); // returns Simd or TupleSimd for the cross
Vector3f normal = n.Values(); // should be [0, 0, 1]
```

2) Reflection of a direction vector about a normal

Mathematically if \(\mathbf{v}\) is the incident vector and \(\mathbf{n}\) is the surface normal normalized then

\[ \mathbf{r} = \mathbf{v} - 2 (\mathbf{v} \cdot \mathbf{n}) \mathbf{n} \]

```cpp
Vector3f dir( 0.0f, -1.0f, -1.0f );
Vector3f normal = Math::Normalize( Vector3f( 0.0f, 0.0f, 1.0f ) );

// Using Simd versions
auto dirSimd = dir.ToSimd();
auto nSimd = normal.ToSimd();

auto reflected = Math::Reflect( dirSimd, nSimd );
Vector3f reflectedVec = reflected.Values();
```

3) Normalizing many positions in a loop while staying in SIMD form

```cpp
// Given many Vector3f positions in an array, prefer to load groups into Simd and operate
std::vector<Vector3f> positions = ...;
for ( size_t i = 0; i < positions.size(); ++i )
{
    auto pSimd = positions[i].ToSimd();
    auto normSimd = Math::Normalize( pSimd );
    positions[i] = normSimd.Values();
}
```

4) Quaternion shortest-arc rotation example (using Quaternion Simd helper)

```cpp
// shortest arc between two directions
Vector3f a( 0.0f, 0.0f, 1.0f );
Vector3f b( 0.0f, 1.0f, 0.0f );

using Q = Quaternion<float>::Simd;
auto q = Q::ShortestArc( a.ToSimd(), b.ToSimd() );
// rotate a by q
auto rotated = Math::Rotate( a, q );
Vector3f rotatedVec = rotated.Values();
```


## Practical tips

- Prefer operating in `Simd` form inside hot loops: load once with `Traits::Load` or `TupleT::ToSimd()` then perform many operations, then `Values()` or `Traits::Store` only at boundaries.
- Use `Traits::Fill<Size>(value)` or `Traits::Set(...)` to produce lane-aligned constants.
- Use `Trim` whenever you reduce a wider SIMD register to the logical `Size` of the tuple.
- Prefer `Traits`-backed arithmetic to ensure portable and optimized implementations across architectures.


## References

See `Harlinn.Math\include\Harlinn\Math\VectorMath.h` for the full implementation and available member functions. The `TupleSimd` section documents the wrapper and the assortment of free functions that operate on both tuples and SIMD wrappers.



