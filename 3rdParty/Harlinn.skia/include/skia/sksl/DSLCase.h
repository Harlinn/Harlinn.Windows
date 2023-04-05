#pragma once
/*
 * Copyright 2021 Google LLC.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_DSL_CASE
#define SKSL_DSL_CASE

#include <skia/private/SkSLDefines.h>
#include <skia/sksl/DSLExpression.h>
#include <skia/sksl/DSLStatement.h>

#include <memory>

namespace SkSL {

class Statement;

namespace dsl {

class DSLCase {
public:
    // An empty expression means 'default:'.
    template<class... Statements>
    DSLCase(DSLExpression value, Statements... statements)
        : fValue(std::move(value)) {
        fStatements.reserve_back(sizeof...(statements));
        // in C++17, we could just do:
        // (fStatements.push_back(DSLStatement(std::move(statements)).release()), ...);
        int unused[] =
          {0,
           (static_cast<void>(fStatements.push_back(DSLStatement(std::move(statements)).release())),
            0)...};
        static_cast<void>(unused);
    }

    SK_API DSLCase(DSLExpression value, SkTArray<DSLStatement> statements,
            PositionInfo info = PositionInfo::Capture());

    SK_API DSLCase(DSLExpression value, SkSL::StatementArray statements,
            PositionInfo info = PositionInfo::Capture());

    SK_API DSLCase(DSLCase&&);

    SK_API ~DSLCase();

    SK_API DSLCase& operator=(DSLCase&&);

    SK_API void append(DSLStatement stmt);

private:
    DSLExpression fValue;
    SkSL::StatementArray fStatements;
    PositionInfo fPosition;

    friend class DSLCore;

    template<class... Cases>
    friend DSLPossibleStatement Switch(DSLExpression value, Cases... cases);
};

} // namespace dsl

} // namespace SkSL

#endif
