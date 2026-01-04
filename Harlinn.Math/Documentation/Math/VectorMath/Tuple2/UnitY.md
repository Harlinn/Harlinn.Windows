# `Tuple2::UnitY`

Description:

The `UnitY` static member function of the `Tuple2` template returns the 2-dimensional unit vector pointing in the positive Y direction. For a `Tuple2` of scalar type \(s\), the returned vector is

$$\begin{bmatrix}0 \\ 1\end{bmatrix}$$

or equivalently the ordered pair \((0, 1)\).

C++ context:

The `UnitY` function is declared inside the `Tuple2` template class defined as:

```cpp
template<class DerivedT, ArithmeticType T>
class Tuple2 : public Internal::TupleBase
```

and the in-class signature is:

```cpp
static DerivedType UnitY() noexcept;
```

Full qualified signatures (declaration and an equivalent out-of-class definition form):

```cpp
// In-class declaration
template<class DerivedT, ArithmeticType T>
static DerivedType Tuple2<DerivedT, T>::UnitY() noexcept;

// Equivalent explicit out-of-class definition form
template<class DerivedT, ArithmeticType T>
DerivedType Tuple2<DerivedT, T>::UnitY() noexcept
{
    return DerivedType( static_cast<T>(0), static_cast<T>(1) );
}
```

Mathematical note:

For a tuple of dimension \(n\) with \(n = 2\) this returns the canonical basis vector along the Y axis:

$$e_y = (0, 1)$$

so that

$$ (e_y)_i = \begin{cases}1 & i = 2 \\ 0 & i \neq 2 \end{cases} $$

Usage examples:

```cpp
// Using a concrete derived type, for example Vector<float,2> alias Vector2f
auto v = Vector2f::UnitY(); // v == (0.0f, 1.0f)

// Using a custom derived type alias
using MyVec = Tuple2<MyDerived, float>;
auto u = MyVec::UnitY();
```

Notes:

- The returned type is the `DerivedType` of the `Tuple2` instantiation. This makes `UnitY` usable on both tuple types and concrete specializations that derive from `Tuple2`.
- `UnitY` performs a direct construction of the derived type with the first component set to 0 and the second component set to 1.

See also:

- `Tuple2::UnitX()`
- `Tuple2::One()`
- `TupleSimd` helpers for SIMD-backed equivalents
