/*
 * Copyright 2021 Google LLC.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_DSLPARSER
#define SKSL_DSLPARSER

#include <memory>
#include <unordered_map>
#include <skia/core/SkStringView.h>
#include <skia/private/SkSLProgramKind.h>
#include <skia/private/SkTOptional.h>
#include <skia/sksl/DSL.h>
#include <skia/sksl/DSLSymbols.h>
#include "src/sksl/SkSLLexer.h"
#include "src/sksl/ir/SkSLProgram.h"

namespace SkSL {

class ErrorReporter;
struct Modifiers;
struct ParsedModule;
class SymbolTable;

/**
 * Consumes .sksl text and invokes DSL functions to instantiate the program.
 */
class DSLParser {
public:
    enum class LayoutToken {
        LOCATION,
        OFFSET,
        BINDING,
        INDEX,
        SET,
        BUILTIN,
        INPUT_ATTACHMENT_INDEX,
        ORIGIN_UPPER_LEFT,
        OVERRIDE_COVERAGE,
        EARLY_FRAGMENT_TESTS,
        BLEND_SUPPORT_ALL_EQUATIONS,
        PUSH_CONSTANT,
        MARKER,
        WHEN,
        KEY,
        TRACKED,
        SRGB_UNPREMUL,
        CTYPE,
        SKPMCOLOR4F,
        SKV4,
        SKRECT,
        SKIRECT,
        SKPMCOLOR,
        SKM44,
        BOOL,
        INT,
        FLOAT,
    };

    SK_API DSLParser(Compiler* compiler, const ProgramSettings& settings, ProgramKind kind,
              String text);

    SK_API std::unique_ptr<Program> program();

    SK_API SkSL::LoadedModule moduleInheritingFrom(SkSL::ParsedModule baseModule);

    SK_API skstd::string_view text(Token token);

    SK_API PositionInfo position(Token token);

    SK_API PositionInfo position(int line);

private:
    SK_API static void InitLayoutMap();

    /**
     * Return the next token, including whitespace tokens, from the parse stream.
     */
    SK_API Token nextRawToken();

    /**
     * Return the next non-whitespace token from the parse stream.
     */
    SK_API Token nextToken();

    /**
     * Push a token back onto the parse stream, so that it is the next one read. Only a single level
     * of pushback is supported (that is, it is an error to call pushback() twice in a row without
     * an intervening nextToken()).
     */
    SK_API void pushback(Token t);

    /**
     * Returns the next non-whitespace token without consuming it from the stream.
     */
    SK_API Token peek();

    /**
     * Checks to see if the next token is of the specified type. If so, stores it in result (if
     * result is non-null) and returns true. Otherwise, pushes it back and returns false.
     */
    SK_API bool checkNext(Token::Kind kind, Token* result = nullptr);

    /**
     * Reads the next non-whitespace token and generates an error if it is not the expected type.
     * The 'expected' string is part of the error message, which reads:
     *
     * "expected <expected>, but found '<actual text>'"
     *
     * If 'result' is non-null, it is set to point to the token that was read.
     * Returns true if the read token was as expected, false otherwise.
     */
    SK_API bool expect(Token::Kind kind, const char* expected, Token* result = nullptr);
    SK_API bool expect(Token::Kind kind, String expected, Token* result = nullptr);

    /**
     * Behaves like expect(TK_IDENTIFIER), but also verifies that identifier is not a type.
     * If the token was actually a type, generates an error message of the form:
     *
     * "expected an identifier, but found type 'float2'"
     */
    SK_API bool expectIdentifier(Token* result);

    SK_API void error(Token token, String msg);
    SK_API void error(int line, String msg);

    SymbolTable& symbols() {
        return *dsl::CurrentSymbolTable();
    }

    // these functions parse individual grammar rules from the current parse position; you probably
    // don't need to call any of these outside of the parser. The function declarations in the .cpp
    // file have comments describing the grammar rules.

    SK_API void declarations();

    SK_API SKSL_INT arraySize();

    SK_API void directive();

    SK_API bool declaration();

    SK_API bool functionDeclarationEnd(const dsl::DSLModifiers& modifiers,
                                dsl::DSLType type,
                                const Token& name);

    struct VarDeclarationsPrefix {
        PositionInfo fPosition;
        dsl::DSLModifiers fModifiers;
        dsl::DSLType fType = dsl::DSLType(dsl::kVoid_Type);
        Token fName;
    };

    SK_API bool varDeclarationsPrefix(VarDeclarationsPrefix* prefixData);

    SK_API dsl::DSLStatement varDeclarationsOrExpressionStatement();

    SK_API dsl::DSLStatement varDeclarations();

    SK_API skstd::optional<dsl::DSLType> structDeclaration();

    SK_API SkTArray<dsl::DSLGlobalVar> structVarDeclaration(const dsl::DSLModifiers& modifiers);

    SK_API bool parseArrayDimensions(int line, dsl::DSLType* type);

    SK_API bool parseInitializer(int line, dsl::DSLExpression* initializer);

    SK_API void globalVarDeclarationEnd(PositionInfo position, const dsl::DSLModifiers& mods,
            dsl::DSLType baseType, skstd::string_view name);

    SK_API dsl::DSLStatement localVarDeclarationEnd(PositionInfo position, const dsl::DSLModifiers& mods,
            dsl::DSLType baseType, skstd::string_view name);

    SK_API skstd::optional<dsl::DSLWrapper<dsl::DSLParameter>> parameter();

    SK_API int layoutInt();

    SK_API skstd::string_view layoutIdentifier();

    SK_API dsl::DSLLayout layout();

    SK_API dsl::DSLModifiers modifiers();

    SK_API dsl::DSLStatement statement();

    SK_API skstd::optional<dsl::DSLType> type(dsl::DSLModifiers* modifiers);

    SK_API bool interfaceBlock(const dsl::DSLModifiers& mods);

    SK_API dsl::DSLStatement ifStatement();

    SK_API dsl::DSLStatement doStatement();

    SK_API dsl::DSLStatement whileStatement();

    SK_API dsl::DSLStatement forStatement();

    SK_API skstd::optional<dsl::DSLCase> switchCase();

    SK_API dsl::DSLStatement switchStatement();

    SK_API dsl::DSLStatement returnStatement();

    SK_API dsl::DSLStatement breakStatement();

    SK_API dsl::DSLStatement continueStatement();

    SK_API dsl::DSLStatement discardStatement();

    SK_API skstd::optional<dsl::DSLBlock> block();

    SK_API dsl::DSLStatement expressionStatement();

    SK_API dsl::DSLExpression expression();

    SK_API dsl::DSLExpression assignmentExpression();

    SK_API dsl::DSLExpression ternaryExpression();

    SK_API dsl::DSLExpression logicalOrExpression();

    SK_API dsl::DSLExpression logicalXorExpression();

    SK_API dsl::DSLExpression logicalAndExpression();

    SK_API dsl::DSLExpression bitwiseOrExpression();

    SK_API dsl::DSLExpression bitwiseXorExpression();

    SK_API dsl::DSLExpression bitwiseAndExpression();

    SK_API dsl::DSLExpression equalityExpression();

    SK_API dsl::DSLExpression relationalExpression();

    SK_API dsl::DSLExpression shiftExpression();

    SK_API dsl::DSLExpression additiveExpression();

    SK_API dsl::DSLExpression multiplicativeExpression();

    SK_API dsl::DSLExpression unaryExpression();

    SK_API dsl::DSLExpression postfixExpression();

    SK_API dsl::DSLExpression swizzle(int line, dsl::DSLExpression base, skstd::string_view swizzleMask);

    SK_API dsl::DSLExpression call(int line, dsl::DSLExpression base, ExpressionArray args);

    SK_API dsl::DSLExpression suffix(dsl::DSLExpression base);

    SK_API dsl::DSLExpression term();

    SK_API bool intLiteral(SKSL_INT* dest);

    SK_API bool floatLiteral(SKSL_FLOAT* dest);

    SK_API bool boolLiteral(bool* dest);

    SK_API bool identifier(skstd::string_view* dest);

    class Checkpoint {
    public:
        Checkpoint(DSLParser* p) : fParser(p) {
            fPushbackCheckpoint = fParser->fPushback;
            fLexerCheckpoint = fParser->fLexer.getCheckpoint();
            fOldErrorReporter = &dsl::GetErrorReporter();
            fOldEncounteredFatalError = fParser->fEncounteredFatalError;
            SkASSERT(fOldErrorReporter);
            dsl::SetErrorReporter(&fErrorReporter);
        }

        ~Checkpoint() {
            SkASSERTF(!fOldErrorReporter,
                      "Checkpoint was not accepted or rewound before destruction");
        }

        void accept() {
            this->restoreErrorReporter();
            // Parser errors should have been fatal, but we can encounter other errors like type
            // mismatches despite accepting the parse. Forward those messages to the actual error
            // handler now.
            fErrorReporter.forwardErrors();
        }

        void rewind() {
            this->restoreErrorReporter();
            fParser->fPushback = fPushbackCheckpoint;
            fParser->fLexer.rewindToCheckpoint(fLexerCheckpoint);
            fParser->fEncounteredFatalError = fOldEncounteredFatalError;
        }

    private:
        class ForwardingErrorReporter : public ErrorReporter {
        public:
            void handleError(skstd::string_view msg, PositionInfo pos) override {
                fErrors.push_back({String(msg), pos});
            }

            void forwardErrors() {
                for (Error& error : fErrors) {
                    dsl::GetErrorReporter().error(error.fMsg.c_str(), error.fPos);
                }
            }

        private:
            struct Error {
                String fMsg;
                PositionInfo fPos;
            };

            SkTArray<Error> fErrors;
        };

        void restoreErrorReporter() {
            SkASSERT(fOldErrorReporter);
            fErrorReporter.reportPendingErrors(PositionInfo());
            dsl::SetErrorReporter(fOldErrorReporter);
            fOldErrorReporter = nullptr;
        }

        DSLParser* fParser;
        Token fPushbackCheckpoint;
        SkSL::Lexer::Checkpoint fLexerCheckpoint;
        ForwardingErrorReporter fErrorReporter;
        ErrorReporter* fOldErrorReporter;
        bool fOldEncounteredFatalError;
    };

    static std::unordered_map<skstd::string_view, LayoutToken>* layoutTokens;

    Compiler& fCompiler;
    ProgramSettings fSettings;
    ErrorReporter* fErrorReporter;
    bool fEncounteredFatalError;
    ProgramKind fKind;
    std::unique_ptr<String> fText;
    Lexer fLexer;
    // current parse depth, used to enforce a recursion limit to try to keep us from overflowing the
    // stack on pathological inputs
    int fDepth = 0;
    Token fPushback;

    friend class AutoDSLDepth;
    friend class HCodeGenerator;
};

}  // namespace SkSL

#endif
