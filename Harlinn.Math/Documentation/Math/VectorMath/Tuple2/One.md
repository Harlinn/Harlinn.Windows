# `Tuple2::One()`

This document describes the `One` static member function of the `Tuple2` template defined in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

## Purpose

The `One` function returns a `Tuple2`-derived object with each component set to 1. In mathematical notation the returned 2-component tuple is:

\(\mathbf{1} = (1, 1)\)

This is useful as a canonical constant vector for initialization, arithmetic identities and tests.

## Full C++ signatures

Declaration (inside the `Tuple2` template class):

```cpp
// Inside template<class DerivedT, ArithmeticType T>
static DerivedType One();
```

Fully qualified form (template header plus qualified return and function name):

```cpp
template<class DerivedT, ArithmeticType T>
static DerivedT Tuple2<DerivedT, T>::One();
```

Implementation (as found in `VectorMath.h`):

```cpp
static DerivedType One()
{
    return DerivedType( static_cast< value_type >( 1 ), static_cast< value_type >( 1 ) );
}
```

## Behavior

- The function constructs and returns a `DerivedType` instance whose two components are each set to the multiplicative identity 1.
- If `value_type` denotes the element type (floating point or integer), the components are constructed as `static_cast<value_type>(1)` to ensure correct typing.

In MathJax notation: If \(v = \text{Tuple2::One}()\) then

\[ v = (1, 1) \]

## Example usage

```cpp
// Assume MyVec is a type derived from Tuple2<MyVec, float>
MyVec ones = MyVec::One();
// ones.x == 1.0f
// ones.y == 1.0f
```

## Notes

- The `One` function is a simple factory for a constant vector of ones and does not perform any branching or runtime checks.
- Use this function where a vector of ones is needed in generic code to preserve element type and alignment.
