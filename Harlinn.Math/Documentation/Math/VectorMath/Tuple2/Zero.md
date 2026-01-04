# `Tuple2::Zero`

Overview:

`Tuple2::Zero` returns a `Tuple2` derived object with all components set to zero. For a 2-dimensional tuple this corresponds to the vector

$$[0, 0]\,,$$

and more generally for `Tuple2<DerivedT, T>` it returns a `DerivedT` value with each component equal to `static_cast<T>(0)`.

C++ function signature:

```
// Declaration inside the class template
static DerivedType Zero( );
```

If expressed with the template parameters and fully qualified type names (as it appears in the class template declaration):

```
template<class DerivedT, ArithmeticType T>
static typename Tuple2<DerivedT, T>::DerivedType Tuple2<DerivedT, T>::Zero( );
```

Behavior:

- The function constructs and returns a `DerivedType` instance initialized with zero values for each component.
- For numeric type `T` the returned components are equal to $0$ expressed as `T` (i.e. `static_cast<T>(0)`).

Example usage:

```cpp
// Using a concrete derived type (e.g. Vector<float,2> inherits Tuple2)
auto v = Vector<float,2>::Zero(); // v == [0.0f, 0.0f]

// Using the template alias types
auto u = Math::Tuple2<MyTupleType, float>::Zero();
```

Return value:

- A `DerivedType` value with components all zero.

Notes:

- The function is a simple factory method useful for initializing values, comparisons, and algorithms that require an explicit zero vector.
- For SIMD-enabled types there is a corresponding SIMD-level `Zero` helper (for example `TupleSimd::Zero`) that returns a packed zero representation; `Tuple2::Zero` constructs the structural `Tuple2` form.

See also:

- `Tuple2::One`
- `TupleSimd::Zero`
- `Vector` aliases such as `Vector2f`, `Vector2d`