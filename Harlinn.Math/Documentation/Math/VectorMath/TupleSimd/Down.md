# `TupleSimd::Down`

## Overview

This document describes the `Down` member functions related to the `TupleSimd` template implemented in `Harlinn.Math/include/Harlinn/Math/VectorMath.h`.

The `Down` functions produce a unit vector representing the "down" direction. In a conventional right-handed 3D coordinate system this corresponds to the vector:

\[
(0, -1, 0)
\]

Use cases: constructing canonical direction vectors for geometric and graphics code, e.g., surface normals and orientation helpers.


## C++ function signatures

- `static TupleSimd Down() noexcept requires ( Size >= 3 )`

  (member of the `template<typename TupleT> class TupleSimd` specialization; returns a `TupleSimd` when the SIMD tuple size is at least 3)

- `static DerivedType Down() noexcept`

  (member of the `template<class DerivedT, ArithmeticType T> class Tuple3` specialization; returns a `Tuple3`-derived `DerivedType`)


## Behaviour and return values

- `TupleSimd::Down()`:
  - Requires: `Size >= 3`.
  - Returns: a `TupleSimd` instance representing the down direction. Conceptually the returned tuple is the vector

    \[
    (0, -1, 0)
    \]

  - Notes: The internal SIMD construction may use permutation/packing order specific to the library's `Traits::Set` ordering. The API semantics are that the second component (the Y component) is set to `-1` while the other primary axes are set to `0`.

- `Tuple3::Down()`:
  - Returns: a `DerivedType` with components `(0, -1, 0)`.
  - Full signature (in class scope): `static DerivedType Down() noexcept`.


## Example (conceptual)

- Calling `auto d = TupleSimd::Down();` yields a SIMD-backed tuple whose components correspond to the down direction; for a 3-component tuple this is equivalent to:

  \[
  d = (0, -1, 0)
  \]

- Calling `auto d3 = Vector<float,3>::Simd::Down();` or `Vector<float,3>::Down()` (via the `Tuple3`-derived static) yields the same canonical 3D down vector.


## Notes

- The functions are `noexcept` and constexpr-like in intent for static canonical vectors; they are inexpensive to call and intended for use as constants in algorithm implementations.
- This document focuses on the `Down` semantics: the API guarantees the logical result is the canonical down direction; low-level SIMD register ordering is an implementation detail.

