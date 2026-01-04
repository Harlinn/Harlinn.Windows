# `TupleSimd::Zero`

Description:

`TupleSimd::Zero` is a static factory function that returns a `TupleSimd` instance with all components set to zero.

C++ signature:

```cpp
static TupleSimd Zero() noexcept;
```

Behavior:

- The returned object has its internal SIMD register initialized using `Traits::Zero()`.
- For a tuple of size `n` the returned value corresponds to the mathematical vector
  \[ \mathbf{v} = [0, 0, \dots, 0] \in \mathbb{R}^{n} \]
  where the numeric type depends on the `TupleT::Traits::Type`.

Semantics and guarantees:

- `noexcept`: the function is declared `noexcept` and does not throw exceptions.
- Complexity: constant time O(1). The operation constructs a `TupleSimd` from a single SIMD value and does not iterate over individual components.
- Interop: the returned `TupleSimd` can be converted to the corresponding tuple type by calling `Values()` or by constructing the tuple with the `TupleSimd` instance.

Examples:

- Use in generic code where a zero vector is needed:

```cpp
using VSimd = MyTuple::Simd; // e.g., TupleSimd<MyTuple>
VSimd z = VSimd::Zero();
// z now represents [0, 0, ..., 0]
```

- Converting to the tuple type:

```cpp
MyTuple t = VSimd::Zero().Values();
// t.values contains all zeros
```

Notes:

- `TupleSimd::Zero` is provided for convenience and performance: initializing via the SIMD trait allows the implementation to use an efficient, register-sized constant instead of setting components one-by-one.
- For small tuple sizes the resulting tuple or tuple-simd behaves as the mathematical zero vector in subsequent operations like addition, dot product and length computations.
