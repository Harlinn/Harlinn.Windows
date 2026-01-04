# `Tuple2::UnitX`

Description:

The `UnitX` static member function of the `Tuple2` template returns the 2-dimensional unit vector pointing in the positive X direction. For a `Tuple2` of scalar type \(s\), the returned vector is

$$\begin{bmatrix}1 \\ 0\end{bmatrix}$$

or equivalently the ordered pair \((1, 0)\).

C++ context:

The `UnitX` function is declared inside the `Tuple2` template class defined as:

`template<class DerivedT, ArithmeticType T>`
`class Tuple2 : public Internal::TupleBase` 

and the in-class signature is:

`static DerivedType UnitX( )`

Full qualified signatures (declaration and an equivalent out-of-class definition form):

`// In-class declaration`
`template<class DerivedT, ArithmeticType T>
static DerivedT Tuple2<DerivedT, T>::UnitX()`

`// Equivalent explicit out-of-class definition form`
`template<class DerivedT, ArithmeticType T>
DerivedT Tuple2<DerivedT, T>::UnitX()
{
    return DerivedT( static_cast<T>(1), static_cast<T>(0) );
}

Usage examples:

- Using a concrete `Tuple2` derived type (for example the `Vector<float,2>` specialization accessible as `Vector2f`):

`auto u = Vector2f::UnitX(); // u == [1, 0]`

- Using a `Tuple2` type alias or a custom derived type:

`using MyVec = Tuple2<MyDerived, float>;`
`auto u = MyVec::UnitX();`

Notes:

- The returned type is the `DerivedType` of the `Tuple2` instantiation. This makes `UnitX` usable on both tuple types and concrete specializations that derive from `Tuple2`.
- `UnitX` performs a direct construction of the derived type with the first component set to 1 and the second component set to 0.
