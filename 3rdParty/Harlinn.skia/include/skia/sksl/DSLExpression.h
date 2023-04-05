/*
 * Copyright 2020 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_DSL_EXPRESSION
#define SKSL_DSL_EXPRESSION

#include <skia/core/SkStringView.h>
#include <skia/core/SkTypes.h>
#include <skia/private/SkTArray.h>
#include <skia/sksl/DSLWrapper.h>
#include <skia/sksl/SkSLErrorReporter.h>

#include <cstdint>
#include <memory>

#if defined(__has_cpp_attribute) && __has_cpp_attribute(clang::reinitializes)
#define SK_CLANG_REINITIALIZES [[clang::reinitializes]]
#else
#define SK_CLANG_REINITIALIZES
#endif

namespace SkSL {

class Expression;
class Type;

namespace dsl {

class DSLPossibleExpression;
class DSLStatement;
class DSLType;
class DSLVarBase;

/**
 * Represents an expression such as 'cos(x)' or 'a + b'.
 */
class DSLExpression {
public:
    DSLExpression(const DSLExpression&) = delete;

    SK_API DSLExpression(DSLExpression&&);

    SK_API DSLExpression();

    /**
     * Creates an expression representing a literal float.
     */
    SK_API DSLExpression(float value, PositionInfo pos = PositionInfo::Capture());

    /**
     * Creates an expression representing a literal float.
     */
    DSLExpression(double value, PositionInfo pos = PositionInfo::Capture())
        : DSLExpression((float) value) {}

    /**
     * Creates an expression representing a literal int.
     */
    SK_API DSLExpression(int value, PositionInfo pos = PositionInfo::Capture());

    /**
     * Creates an expression representing a literal int.
     */
    SK_API DSLExpression(int64_t value, PositionInfo pos = PositionInfo::Capture());

    /**
     * Creates an expression representing a literal uint.
     */
    SK_API DSLExpression(unsigned int value, PositionInfo pos = PositionInfo::Capture());

    /**
     * Creates an expression representing a literal bool.
     */
    SK_API DSLExpression(bool value, PositionInfo pos = PositionInfo::Capture());

    /**
     * Creates an expression representing a variable reference.
     */
    SK_API DSLExpression(DSLVarBase& var, PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression(DSLVarBase&& var, PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression(DSLPossibleExpression expr, PositionInfo pos = PositionInfo::Capture());

    SK_API explicit DSLExpression(std::unique_ptr<SkSL::Expression> expression);

    SK_API static DSLExpression Poison(PositionInfo pos = PositionInfo::Capture());

    SK_API ~DSLExpression();

    SK_API DSLType type();

    /**
     * Overloads the '=' operator to create an SkSL assignment statement.
     */
    SK_API DSLPossibleExpression operator=(DSLExpression other);

    SK_API DSLExpression x(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression y(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression z(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression w(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression r(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression g(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression b(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression a(PositionInfo pos = PositionInfo::Capture());

    /**
     * Creates an SkSL struct field access expression.
     */
    SK_API DSLExpression field(skstd::string_view name, PositionInfo pos = PositionInfo::Capture());

    /**
     * Creates an SkSL array index expression.
     */
    SK_API DSLPossibleExpression operator[](DSLExpression index);

    SK_API DSLPossibleExpression operator()(SkTArray<DSLWrapper<DSLExpression>> args,
                                     PositionInfo pos = PositionInfo::Capture());

    SK_API DSLPossibleExpression operator()(ExpressionArray args,
                                     PositionInfo pos = PositionInfo::Capture());

    /**
     * Returns true if this object contains an expression. DSLExpressions which were created with
     * the empty constructor or which have already been release()ed do not have a value.
     * DSLExpressions created with errors are still considered to have a value (but contain poison).
     */
    bool hasValue() const {
        return fExpression != nullptr;
    }

    /**
     * Returns true if this object contains an expression which is not poison.
     */
    SK_API bool isValid() const;

    SK_API SK_CLANG_REINITIALIZES void swap(DSLExpression& other);

    /**
     * Invalidates this object and returns the SkSL expression it represents. It is an error to call
     * this on an invalid DSLExpression.
     */
    SK_API std::unique_ptr<SkSL::Expression> release();

private:
    /**
     * Calls release if this expression has a value, otherwise returns null.
     */
    SK_API std::unique_ptr<SkSL::Expression> releaseIfPossible();

    std::unique_ptr<SkSL::Expression> fExpression;

    friend DSLExpression SampleChild(int index, DSLExpression coords);

    friend class DSLCore;
    friend class DSLFunction;
    friend class DSLPossibleExpression;
    friend class DSLType;
    friend class DSLVarBase;
    friend class DSLWriter;
    template<typename T> friend class DSLWrapper;
};

SK_API DSLPossibleExpression operator+(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator+(DSLExpression expr);
SK_API DSLPossibleExpression operator+=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator-(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator-(DSLExpression expr);
SK_API DSLPossibleExpression operator-=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator*(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator*=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator/(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator/=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator%(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator%=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator<<(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator<<=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator>>(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator>>=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator&&(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator||(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator&(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator&=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator|(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator|=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator^(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator^=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression LogicalXor(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator,(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator,(DSLPossibleExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator,(DSLExpression left, DSLPossibleExpression right);
SK_API DSLPossibleExpression operator,(DSLPossibleExpression left, DSLPossibleExpression right);
SK_API DSLPossibleExpression operator==(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator!=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator>(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator<(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator>=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator<=(DSLExpression left, DSLExpression right);
SK_API DSLPossibleExpression operator!(DSLExpression expr);
SK_API DSLPossibleExpression operator~(DSLExpression expr);
SK_API DSLPossibleExpression operator++(DSLExpression expr);
SK_API DSLPossibleExpression operator++(DSLExpression expr, int);
SK_API DSLPossibleExpression operator--(DSLExpression expr);
SK_API DSLPossibleExpression operator--(DSLExpression expr, int);

/**
 * Represents an Expression which may have failed and/or have pending errors to report. Converting a
 * PossibleExpression into an Expression requires PositionInfo so that any pending errors can be
 * reported at the correct position.
 *
 * PossibleExpression is used instead of Expression in situations where it is not possible to
 * capture the PositionInfo at the time of Expression construction (notably in operator overloads,
 * where we cannot add default parameters).
 */
class DSLPossibleExpression {
public:
    SK_API DSLPossibleExpression(std::unique_ptr<SkSL::Expression> expression);

    SK_API DSLPossibleExpression(DSLPossibleExpression&& other);

    SK_API ~DSLPossibleExpression();

    bool valid() const {
        return fExpression != nullptr;
    }

    /**
     * Reports any pending errors at the specified position.
     */
    SK_API void reportErrors(PositionInfo pos);

    SK_API DSLType type();

    SK_API DSLExpression x(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression y(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression z(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression w(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression r(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression g(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression b(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression a(PositionInfo pos = PositionInfo::Capture());

    SK_API DSLExpression field(skstd::string_view name, PositionInfo pos = PositionInfo::Capture());

    SK_API DSLPossibleExpression operator=(DSLExpression expr);

    SK_API DSLPossibleExpression operator=(int expr);

    SK_API DSLPossibleExpression operator=(float expr);

    SK_API DSLPossibleExpression operator=(double expr);

    SK_API DSLPossibleExpression operator[](DSLExpression index);

    SK_API DSLPossibleExpression operator()(SkTArray<DSLWrapper<DSLExpression>> args,
                                     PositionInfo pos = PositionInfo::Capture());

    SK_API DSLPossibleExpression operator()(ExpressionArray args,
                                     PositionInfo pos = PositionInfo::Capture());

    SK_API DSLPossibleExpression operator++();

    SK_API DSLPossibleExpression operator++(int);

    SK_API DSLPossibleExpression operator--();

    SK_API DSLPossibleExpression operator--(int);

    SK_API std::unique_ptr<SkSL::Expression> release(PositionInfo pos = PositionInfo::Capture());

private:
    std::unique_ptr<SkSL::Expression> fExpression;

    friend class DSLExpression;
};

} // namespace dsl

} // namespace SkSL

#endif
