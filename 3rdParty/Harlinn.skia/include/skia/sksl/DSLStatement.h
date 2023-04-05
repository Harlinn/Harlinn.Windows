/*
 * Copyright 2021 Google LLC.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_DSL_STATEMENT
#define SKSL_DSL_STATEMENT

#include <skia/core/SkString.h>
#include <skia/core/SkTypes.h>
#include <skia/private/SkSLStatement.h>
#include <skia/sksl/SkSLErrorReporter.h>

#include <memory>

class GrGLSLShaderBuilder;

namespace SkSL {

class Expression;
class Statement;

namespace dsl {

class DSLBlock;
class DSLExpression;
class DSLPossibleExpression;
class DSLPossibleStatement;
class DSLVar;

class DSLStatement {
public:
    SK_API DSLStatement();

    SK_API DSLStatement(DSLExpression expr);

    SK_API DSLStatement(DSLPossibleExpression expr, PositionInfo pos = PositionInfo::Capture());

    SK_API DSLStatement(DSLPossibleStatement stmt, PositionInfo pos = PositionInfo::Capture());

    SK_API DSLStatement(DSLBlock block);

    DSLStatement(DSLStatement&&) = default;

    SK_API DSLStatement(std::unique_ptr<SkSL::Statement> stmt);

    SK_API DSLStatement(std::unique_ptr<SkSL::Expression> expr);

    SK_API ~DSLStatement();

    DSLStatement& operator=(DSLStatement&& other) = default;

    bool hasValue() { return fStatement != nullptr; }

    std::unique_ptr<SkSL::Statement> release() {
        SkASSERT(this->hasValue());
        return std::move(fStatement);
    }

private:
    std::unique_ptr<SkSL::Statement> releaseIfPossible() {
        return std::move(fStatement);
    }

    std::unique_ptr<SkSL::Statement> fStatement;

    friend class DSLBlock;
    friend class DSLCore;
    friend class DSLExpression;
    friend class DSLPossibleStatement;
    friend class DSLWriter;
    SK_API friend DSLStatement operator,(DSLStatement left, DSLStatement right);
};

/**
 * Represents a Statement which may have failed and/or have pending errors to report. Converting a
 * PossibleStatement into a Statement requires PositionInfo so that any pending errors can be
 * reported at the correct position.
 *
 * PossibleStatement is used instead of Statement in situations where it is not possible to capture
 * the PositionInfo at the time of Statement construction.
 */
class DSLPossibleStatement {
public:
    SK_API DSLPossibleStatement(std::unique_ptr<SkSL::Statement> stmt);

    SK_API DSLPossibleStatement(DSLPossibleStatement&& other) = default;

    SK_API ~DSLPossibleStatement();

    bool hasValue() { return fStatement != nullptr; }

    std::unique_ptr<SkSL::Statement> release() {
        return DSLStatement(std::move(*this)).release();
    }

private:
    std::unique_ptr<SkSL::Statement> fStatement;

    friend class DSLStatement;
};

SK_API DSLStatement operator,(DSLStatement left, DSLStatement right);

} // namespace dsl

} // namespace SkSL

#endif
