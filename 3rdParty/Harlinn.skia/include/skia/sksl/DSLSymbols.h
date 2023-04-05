/*
 * Copyright 2021 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_DSL_SYMBOLS
#define SKSL_DSL_SYMBOLS

#include <skia/core/SkStringView.h>
#include <skia/private/SkSLString.h>
#include <skia/sksl/DSLExpression.h>

#include <memory>

namespace SkSL {

class SymbolTable;

namespace dsl {

class DSLVar;

// This header provides methods for manually managing symbol tables in DSL code. They should not be
// used by normal hand-written DSL code, where we rely on C++ to manage symbols, but are instead
// needed when DSL objects are being constructed programmatically (as in DSLParser).

/**
 * Pushes a new symbol table onto the symbol table stack.
 */
SK_API void PushSymbolTable();

/**
 * Pops the top symbol table from the stack. As symbol tables are shared pointers, this will only
 * destroy the symbol table if it was never attached to anything (e.g. passed into a Block
 * constructor).
 */
SK_API void PopSymbolTable();

/**
 * Returns the current symbol table. Outside of SkSL itself, this is an opaque pointer, used only
 * for passing it to DSL methods that require it.
 */
SK_API std::shared_ptr<SymbolTable> CurrentSymbolTable();

/**
 * Returns an expression referring to the named symbol.
 */
SK_API DSLPossibleExpression Symbol(skstd::string_view name, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns true if the name refers to a type (user or built-in) in the current symbol table.
 */
SK_API bool IsType(skstd::string_view name);

/**
 * Returns true if the name refers to a builtin type.
 */
SK_API bool IsBuiltinType(skstd::string_view name);

/**
 * Adds a variable to the current symbol table.
 */
SK_API void AddToSymbolTable(DSLVarBase& var, PositionInfo pos = PositionInfo::Capture());

} // namespace dsl

} // namespace SkSL

#endif
