/*
 * Copyright 2020 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_DSL_TYPE
#define SKSL_DSL_TYPE

#include <skia/core/SkSpan.h>
#include <skia/private/SkSLString.h>
#include <skia/sksl/DSLExpression.h>
#include <skia/sksl/DSLModifiers.h>

#include <cstdint>

namespace SkSL {

class Type;

namespace dsl {

class DSLExpression;
class DSLField;
class DSLVarBase;

enum TypeConstant : uint8_t {
    kBool_Type,
    kBool2_Type,
    kBool3_Type,
    kBool4_Type,
    kHalf_Type,
    kHalf2_Type,
    kHalf3_Type,
    kHalf4_Type,
    kHalf2x2_Type,
    kHalf3x2_Type,
    kHalf4x2_Type,
    kHalf2x3_Type,
    kHalf3x3_Type,
    kHalf4x3_Type,
    kHalf2x4_Type,
    kHalf3x4_Type,
    kHalf4x4_Type,
    kFloat_Type,
    kFloat2_Type,
    kFloat3_Type,
    kFloat4_Type,
    kFragmentProcessor_Type,
    kFloat2x2_Type,
    kFloat3x2_Type,
    kFloat4x2_Type,
    kFloat2x3_Type,
    kFloat3x3_Type,
    kFloat4x3_Type,
    kFloat2x4_Type,
    kFloat3x4_Type,
    kFloat4x4_Type,
    kInt_Type,
    kInt2_Type,
    kInt3_Type,
    kInt4_Type,
    kShader_Type,
    kShort_Type,
    kShort2_Type,
    kShort3_Type,
    kShort4_Type,
    kUInt_Type,
    kUInt2_Type,
    kUInt3_Type,
    kUInt4_Type,
    kUShort_Type,
    kUShort2_Type,
    kUShort3_Type,
    kUShort4_Type,
    kVoid_Type,
    kPoison_Type,
};

class DSLType {
public:
    DSLType(TypeConstant tc)
        : fTypeConstant(tc) {}

    SK_API DSLType(const SkSL::Type* type);

    SK_API DSLType(skstd::string_view name);

    SK_API DSLType(skstd::string_view name,
            DSLModifiers* modifiers,
            PositionInfo pos = PositionInfo::Capture());

    /**
     * Returns true if this type is a bool.
     */
    SK_API bool isBoolean() const;

    /**
     * Returns true if this is a numeric scalar type.
     */
    SK_API bool isNumber() const;

    /**
     * Returns true if this is a floating-point scalar type (float or half).
     */
    SK_API bool isFloat() const;

    /**
     * Returns true if this is a signed scalar type (int or short).
     */
    SK_API bool isSigned() const;

    /**
     * Returns true if this is an unsigned scalar type (uint or ushort).
     */
    SK_API bool isUnsigned() const;

    /**
     * Returns true if this is a signed or unsigned integer.
     */
    SK_API bool isInteger() const;

    /**
     * Returns true if this is a scalar type.
     */
    SK_API bool isScalar() const;

    /**
     * Returns true if this is a vector type.
     */
    SK_API bool isVector() const;

    /**
     * Returns true if this is a matrix type.
     */
    SK_API bool isMatrix() const;

    /**
     * Returns true if this is a array type.
     */
    SK_API bool isArray() const;

    /**
     * Returns true if this is a struct type.
     */
    SK_API bool isStruct() const;

    /**
     * Returns true if this is a Skia object type (shader, colorFilter, blender).
     */
    SK_API bool isEffectChild() const;

    template<typename... Args>
    static DSLPossibleExpression Construct(DSLType type, DSLVarBase& var, Args&&... args) {
        DSLExpression argArray[] = {var, args...};
        return Construct(type, SkMakeSpan(argArray));
    }

    template<typename... Args>
    static DSLPossibleExpression Construct(DSLType type, DSLExpression expr, Args&&... args) {
        DSLExpression argArray[] = {std::move(expr), std::move(args)...};
        return Construct(type, SkMakeSpan(argArray));
    }

    SK_API static DSLPossibleExpression Construct(DSLType type, SkSpan<DSLExpression> argArray);

private:
    SK_API const SkSL::Type& skslType() const;

    const SkSL::Type* fSkSLType = nullptr;

    TypeConstant fTypeConstant = kPoison_Type;

    SK_API friend DSLType Array(const DSLType& base, int count, PositionInfo pos);
    SK_API friend DSLType Struct(skstd::string_view name, SkSpan<DSLField> fields, PositionInfo pos);
    friend class DSLCore;
    friend class DSLFunction;
    friend class DSLVarBase;
    friend class DSLWriter;
};

#define TYPE(T)                                                                                    \
    template<typename... Args>                                                                     \
    DSLExpression T(Args&&... args) {                                                              \
        return DSLType::Construct(k ## T ## _Type, std::forward<Args>(args)...);                   \
    }

#define VECTOR_TYPE(T)                                                                             \
    TYPE(T)                                                                                        \
    TYPE(T ## 2)                                                                                   \
    TYPE(T ## 3)                                                                                   \
    TYPE(T ## 4)

#define MATRIX_TYPE(T)                                                                             \
    TYPE(T ## 2x2)                                                                                 \
    TYPE(T ## 3x2)                                                                                 \
    TYPE(T ## 4x2)                                                                                 \
    TYPE(T ## 2x3)                                                                                 \
    TYPE(T ## 3x3)                                                                                 \
    TYPE(T ## 4x3)                                                                                 \
    TYPE(T ## 2x4)                                                                                 \
    TYPE(T ## 3x4)                                                                                 \
    TYPE(T ## 4x4)

VECTOR_TYPE(Bool)
VECTOR_TYPE(Float)
VECTOR_TYPE(Half)
VECTOR_TYPE(Int)
VECTOR_TYPE(UInt)
VECTOR_TYPE(Short)
VECTOR_TYPE(UShort)

MATRIX_TYPE(Float)
MATRIX_TYPE(Half)

#undef TYPE
#undef VECTOR_TYPE
#undef MATRIX_TYPE

SK_API DSLType Array(const DSLType& base, int count, PositionInfo pos = PositionInfo::Capture());

class DSLField {
public:
    DSLField(const DSLType type, skstd::string_view name,
             PositionInfo pos = PositionInfo::Capture())
        : DSLField(DSLModifiers(), type, name, pos) {}

    DSLField(const DSLModifiers& modifiers, const DSLType type, skstd::string_view name,
             PositionInfo pos = PositionInfo::Capture())
        : fModifiers(modifiers)
        , fType(type)
        , fName(name)
        , fPosition(pos) {}

private:
    DSLModifiers fModifiers;
    const DSLType fType;
    skstd::string_view fName;
    PositionInfo fPosition;

    friend class DSLCore;
    SK_API friend DSLType Struct(skstd::string_view name, SkSpan<DSLField> fields, PositionInfo pos);
};

SK_API DSLType Struct(skstd::string_view name, SkSpan<DSLField> fields,
               PositionInfo pos = PositionInfo::Capture());

template<typename... Field>
DSLType Struct(skstd::string_view name, Field... fields) {
    DSLField fieldTypes[] = {std::move(fields)...};
    return Struct(name, SkMakeSpan(fieldTypes), PositionInfo());
}

} // namespace dsl

} // namespace SkSL

#endif
