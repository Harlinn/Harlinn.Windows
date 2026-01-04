# `TupleSimd::UnitY()`

Description:

The `UnitY` static member function of the `TupleSimd` template returns a SIMD-packed tuple where the second component (the Y component) is set to 1 and all other components are set to 0. This represents the unit basis vector along the Y axis.

C++ context:

- Template enclosing type: `template<typename TupleT> class TupleSimd`
- Exact member function signature as implemented in `VectorMath.h`:

```cpp
static TupleSimd UnitY( ) noexcept
```

Notes on dimensionality:

- For a 2-component tuple (Size = 2) the returned vector corresponds to $e_{y} = (0, 1)$.
- For a 3-component tuple (Size = 3) the returned vector corresponds to $e_{y} = (0, 1, 0)$.
- For a 4-component tuple (Size = 4) the returned vector corresponds to $e_{y} = (0, 1, 0, 0)$.
- In general for a tuple with Size = $n$ the returned vector is $e_{y} = (0, 1, 0, \dots, 0)$ where the second component equals 1 and all other components equal 0.

Mathematical definition:

Let $n$ be the tuple size and index components starting at 1. The returned vector $e_y \in \mathbb{R}^{n}$ is

$$
e_y = (0, 1, 0, \dots, 0)
$$

so that

$$
(e_y)_i = \begin{cases}
1 & i = 2 \\
0 & i \neq 2
\end{cases}
$$

Implementation detail (remark):

The implementation constructs the SIMD register using `Traits::Set(...)` so that the resulting SIMD value places the 1.0 value into the Y slot and zeroes elsewhere. The header implementation uses the `value_type` for casting: `Traits::Set( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ) )`.

Examples:

```cpp
// Using the provided typedefs
using Math::Vector3f;

// Create a TupleSimd instance representing unit Y in 3D
Vector3f::Simd up = Vector3f::Simd::UnitY();

// Convert back to tuple if needed
Vector3f v = up.Values(); // v is (0.0f, 1.0f, 0.0f)

// Use as a SIMD value directly
auto ymask = up; // SIMD-packed unit Y
```

Return value:

- Type: `TupleSimd` (the same instantiation of the template)
- Semantics: a SIMD vector whose second component is 1 and all other components are 0

Exceptions and noexcept:

- The function is declared `noexcept`. It does not throw exceptions.

See also:

- `TupleSimd::UnitX()` for the unit basis vector along X.
- `TupleSimd::UnitZ()` for the unit basis vector along Z: when available for Size >= 3.
- `TupleSimd::UnitW()` for the unit basis vector along W: when available for Size >= 4.
