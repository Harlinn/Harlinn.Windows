#pragma once
/*
 * Copyright 2021 Google LLC.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_DSL_BLOCK
#define SKSL_DSL_BLOCK

#include <skia/private/SkSLDefines.h>
#include <skia/sksl/DSLExpression.h>
#include <skia/sksl/DSLStatement.h>

#include <memory>

namespace SkSL {

class Block;
class SymbolTable;

namespace dsl {

class DSLBlock {
public:
    template<class... Statements>
    DSLBlock(Statements... statements) {
        fStatements.reserve_back(sizeof...(statements));
        // in C++17, we could just do:
        // (fStatements.push_back(DSLStatement(statements.release()).release()), ...);
        int unused[] =
            {0,
            (static_cast<void>(fStatements.push_back(DSLStatement(statements.release()).release())),
             0)...};
        static_cast<void>(unused);
    }

    DSLBlock(DSLBlock&& other) = default;

    SK_API DSLBlock(SkSL::StatementArray statements, std::shared_ptr<SymbolTable> symbols = nullptr);

    SK_API DSLBlock(SkTArray<DSLStatement> statements, std::shared_ptr<SymbolTable> symbols = nullptr);

    SK_API ~DSLBlock();

    DSLBlock& operator=(DSLBlock&& other) {
        fStatements = std::move(other.fStatements);
        return *this;
    }

    SK_API void append(DSLStatement stmt);

    SK_API std::unique_ptr<SkSL::Block> release();

private:
    SkSL::StatementArray fStatements;
    std::shared_ptr<SkSL::SymbolTable> fSymbols;

    friend class DSLStatement;
    friend class DSLFunction;
};

} // namespace dsl

} // namespace SkSL

#endif
