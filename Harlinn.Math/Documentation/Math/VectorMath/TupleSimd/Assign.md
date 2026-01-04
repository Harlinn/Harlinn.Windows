# `TupleSimd::Assign` overloads

This document lists and explains all overloads of the `Assign` member function defined on the `TupleSimd` template in `VectorMath.h`.

Each overload updates the internal SIMD register `simd` of a `TupleSimd` instance. In the descriptions below `\text{simd}` denotes the SIMD register held by the `TupleSimd` instance and `\text{Traits}` refers to `TupleType::Traits` used by the `TupleSimd` specialization. Use of MathJax notation follows for concise specification of semantics.

---

## 1) `void Assign(const TupleSimd& other) noexcept`

Signature

```cpp
void Assign(const TupleSimd& other) noexcept;
```

Description

Assigns the SIMD register of `other` into this object. This is a direct copy of the SIMD representation.

Semantics

$$\text{simd} \leftarrow \text{other.simd}$$

Notes

- This operation is noexcept and has constant time complexity.

---

## 2) `void Assign(const value_type value) noexcept`

Signature

```cpp
void Assign(const value_type value) noexcept;
```

Description

Sets each of the first `Size` components of the SIMD register to `value` using the `Traits::Fill<Size>` helper.

Semantics

If the tuple has component count $n = \text{Size}$ and components are $v_i$, then

$$\forall i\in\{1,\dots,n\}: v_i \leftarrow \text{value}$$

In SIMD form this is

$$\text{simd} \leftarrow \text{Traits::Fill}_{n}(\text{value})$$

Notes

- This operation is noexcept and has constant time complexity.

---

## 3) `template<Math::TupleType T> requires std::is_same_v<Traits, typename T::Traits> void Assign(const T& other) noexcept`

Signature

```cpp
template<Math::TupleType T>
    requires std::is_same_v<Traits, typename T::Traits>
void Assign(const T& other) noexcept;
```

Description

Loads the component array of a tuple-type `other` into the SIMD register using `Traits::Load`. This overload requires that `other` uses the same `Traits` as the `TupleSimd` specialization.

Semantics

Let `other.values` be the contiguous array of components. Then

$$\text{simd} \leftarrow \text{Traits::Load}(\text{other.values})$$

Notes

- This operation is noexcept. Complexity depends on the cost of `Traits::Load` but is effectively constant for the small fixed sizes used (2, 3, 4, ...).
- This overload is chosen when providing the structural tuple form rather than an existing SIMD wrapper.

---

## 4) `void Assign(SIMDType values) noexcept`

Signature

```cpp
void Assign(SIMDType values) noexcept;
```

Description

Directly assigns the provided raw SIMD register `values` into the object.

Semantics

$$\text{simd} \leftarrow \text{values}$$

Notes

- This operation is noexcept and has constant time complexity.
- Use this overload when you already have a SIMD register prepared and want to set the `TupleSimd` content without further conversion.

---

## General remarks

- All overloads update only the internal SIMD register and do not perform additional normalization or trimming beyond what the underlying `Traits` operations implement.
- Overloads are provided to accept: another `TupleSimd`, a scalar value broadcasted to all components, a structural `Tuple` with matching `Traits`, and a raw SIMD register.

If you need examples of typical usage, or a short code fragment demonstrating each overload, I can add one to this document.