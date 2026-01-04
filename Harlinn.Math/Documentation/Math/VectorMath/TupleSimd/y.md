# `TupleSimd::Y()` and `TupleSimd::y()`

Source: `Harlinn.Math/include/Harlinn/Math/VectorMath.h`

This document describes the `Y` and `y` member functions of the `TupleSimd` template.

## Overview

Both functions access the second component (index 1) of a SIMD-backed tuple. They are intended for tuple types with at least two components (Size >= 2). Use `Y()` when you need a `TupleSimd` where every lane contains the value of the second component. Use `y()` when you need the scalar value of the second component.


## Signatures

- `TupleSimd Y() const`
- `value_type y() const`


## Behavior

Let `t` be a `TupleSimd` instance and denote its components as

\[
t = (t_0, t_1, t_2, \dots, t_{n-1})
\]

where `t_1` is the second component (index 1) and `n = Size`.

- `Y()` returns a `TupleSimd` in which each lane equals the second component of `t`. In MathJax notation:

\[
Y(t) = (t_1, t_1, \dots, t_1)\quad (\text{replicated across the SIMD lanes})
\]

Implementation detail: the function constructs the result by extracting the second lane from the internal SIMD register and using a `Trim`/replicate operation provided by the component `Traits` so the returned `TupleSimd` has the same `Size` and `Traits`.

- `y()` returns the scalar second component value:

\[
y(t) = t_1
\]

Implementation detail: the function uses `Traits::Extract<1>( simd )` to obtain the scalar value from the SIMD register.


## Requirements and notes

- These functions are meaningful only for tuple sizes with at least two components: `Size >= 2`.
- `Y()` is useful when subsequent SIMD operations expect a broadcasted vector with the second component replicated to all lanes.
- `y()` is useful for scalar code paths, logging, or when a single component is required.
- Both accessors are lightweight and implemented with the `TupleSimd` type's `Traits` to avoid unnecessary load/stores.


## Example usage

- Broadcast the second component for SIMD math:

```cpp
using TSimd = MyTuple::Simd; // a TupleSimd specialization
TSimd b = a.Y(); // b has the second component of a replicated in all lanes
```

- Read the scalar second component:

```cpp
auto scalarY = a.y(); // scalar value equal to the second component
```


## See also

- `TupleSimd::X()` and `TupleSimd::x()` for the first component
- `TupleSimd::Z()` and `TupleSimd::z()` for the third component when `Size > 2`

