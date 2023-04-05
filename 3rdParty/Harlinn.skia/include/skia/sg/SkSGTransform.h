/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGTransform_DEFINED
#define SkSGTransform_DEFINED

#include "SkSGEffectNode.h"

class SkM44;
class SkMatrix;

namespace sksg {

/**
 * Transformations base class.
 */
class Transform : public Node {
public:
    // Compose T' = A x B
    SK_API static sk_sp<Transform> MakeConcat(sk_sp<Transform> a, sk_sp<Transform> b);

    // T' = Inv(T)
    SK_API static sk_sp<Transform> MakeInverse(sk_sp<Transform> t);

protected:
    SK_API Transform();

    virtual bool is44() const = 0;

    virtual SkMatrix asMatrix() const = 0;
    virtual SkM44    asM44   () const = 0;

private:
    friend class TransformPriv;

    using INHERITED = Node;
};

/**
 * Concrete, matrix-backed Transform.
 *
 * Supported instantiations: SkMatrix, SkM44.
 *
 * Sample use:
 *
 *   auto m33 = Matrix<SkMatrix>::Make(SkMatrix::I());
 *   ...
 *   m33->setMatrix(SkMatrix::Translate(10, 10));
 *
 */
template <typename T>
class Matrix final : public Transform {
public:
    template <typename = std::enable_if<std::is_same<T, SkMatrix>::value ||
                                        std::is_same<T, SkM44   >::value>>
    static sk_sp<Matrix> Make(const T& m) { return sk_sp<Matrix>(new Matrix(m)); }

    SG_ATTRIBUTE(Matrix, T, fMatrix)

protected:
    explicit Matrix(const T& m) : fMatrix(m) {}

    SkRect onRevalidate(InvalidationController*, const SkMatrix&) override {
        return SkRect::MakeEmpty();
    }

    bool is44() const override { return std::is_same<T, SkM44>::value; }

    SkMatrix asMatrix() const override;
    SkM44    asM44   () const override;

private:
    T fMatrix;

    using INHERITED = Transform;
};

/**
 * Concrete Effect node, binding a Transform to a RenderNode.
 */
class TransformEffect final : public EffectNode {
public:
    static sk_sp<TransformEffect> Make(sk_sp<RenderNode> child, sk_sp<Transform> transform) {
        return child && transform
            ? sk_sp<TransformEffect>(new TransformEffect(std::move(child), std::move(transform)))
            : nullptr;
    }

    static sk_sp<TransformEffect> Make(sk_sp<RenderNode> child, const SkMatrix& m) {
        return Make(std::move(child), Matrix<SkMatrix>::Make(m));
    }

    SK_API ~TransformEffect() override;

    const sk_sp<Transform>& getTransform() const { return fTransform; }

protected:
    SK_API void onRender(SkCanvas*, const RenderContext*) const override;
    SK_API const RenderNode* onNodeAt(const SkPoint&)     const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

private:
    SK_API TransformEffect(sk_sp<RenderNode>, sk_sp<Transform>);

    const sk_sp<Transform> fTransform;

    using INHERITED = EffectNode;
};

} // namespace sksg

#endif // SkSGTransform_DEFINED
