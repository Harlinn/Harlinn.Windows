/*
 * Copyright 2020 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_DSL_CORE
#define SKSL_DSL_CORE

#include <skia/private/SkSLProgramKind.h>
#include <skia/private/SkTArray.h>
#include <skia/sksl/DSLBlock.h>
#include <skia/sksl/DSLCase.h>
#include <skia/sksl/DSLExpression.h>
#include <skia/sksl/DSLFunction.h>
#include <skia/sksl/DSLStatement.h>
#include <skia/sksl/DSLType.h>
#include <skia/sksl/DSLVar.h>
#include <skia/sksl/DSLWrapper.h>
#include <skia/sksl/SkSLErrorReporter.h>

namespace SkSL {

class Compiler;
struct Program;
struct ProgramSettings;

namespace dsl {

// When users import the DSL namespace via `using namespace SkSL::dsl`, we want the SwizzleComponent
// Type enum to come into scope as well, so `Swizzle(var, X, Y, ONE)` can work as expected.
// `namespace SkSL::SwizzleComponent` contains only an `enum Type`; this `using namespace` directive
// shouldn't pollute the SkSL::dsl namespace with anything else.
using namespace SkSL::SwizzleComponent;

/**
 * Starts DSL output on the current thread using the specified compiler. This must be called
 * prior to any other DSL functions.
 */
SK_API void Start(SkSL::Compiler* compiler, SkSL::ProgramKind kind = SkSL::ProgramKind::kFragment);

SK_API void Start(SkSL::Compiler* compiler, SkSL::ProgramKind kind, const SkSL::ProgramSettings& settings);

/**
 * Signals the end of DSL output. This must be called sometime between a call to Start() and the
 * termination of the thread.
 */
SK_API void End();

/**
 * Returns all global elements (functions and global variables) as a self-contained Program. The
 * optional source string is retained as the program's source. DSL programs do not normally have
 * sources, but when a DSL program is produced from parsed program text (as in DSLParser), it may be
 * important to retain it so that any skstd::string_views derived from it remain valid.
 */
SK_API std::unique_ptr<SkSL::Program> ReleaseProgram(std::unique_ptr<SkSL::String> source = nullptr);

/**
 * Returns the ErrorReporter which will be notified of any errors that occur during DSL calls. The
 * default error reporter aborts on any error.
 */
SK_API ErrorReporter& GetErrorReporter();

/**
 * Installs an ErrorReporter which will be notified of any errors that occur during DSL calls.
 */
SK_API void SetErrorReporter(ErrorReporter* errorReporter);

SK_API DSLGlobalVar sk_FragColor();

SK_API DSLGlobalVar sk_FragCoord();

SK_API DSLExpression sk_Position();

/**
 * #extension <name> : enable
 */
SK_API void AddExtension(skstd::string_view name, PositionInfo pos = PositionInfo::Capture());

/**
 * break;
 */
SK_API DSLStatement Break(PositionInfo pos = PositionInfo::Capture());

/**
 * continue;
 */
SK_API DSLStatement Continue(PositionInfo pos = PositionInfo::Capture());

/**
 * Adds a modifiers declaration to the current program.
 */
SK_API void Declare(const DSLModifiers& modifiers, PositionInfo pos = PositionInfo::Capture());

/**
 * Creates a local variable declaration statement.
 */
SK_API DSLStatement Declare(DSLVar& var, PositionInfo pos = PositionInfo::Capture());

/**
 * Creates a local variable declaration statement containing multiple variables.
 */
SK_API DSLStatement Declare(SkTArray<DSLVar>& vars, PositionInfo pos = PositionInfo::Capture());

/**
 * Declares a global variable.
 */
SK_API void Declare(DSLGlobalVar& var, PositionInfo pos = PositionInfo::Capture());

/**
 * Declares a set of global variables.
 */
SK_API void Declare(SkTArray<DSLGlobalVar>& vars, PositionInfo pos = PositionInfo::Capture());

/**
 * default: statements
 */
template<class... Statements>
DSLCase Default(Statements... statements) {
    return DSLCase(DSLExpression(), std::move(statements)...);
}

/**
 * discard;
 */
SK_API DSLStatement Discard(PositionInfo pos = PositionInfo::Capture());

/**
 * do stmt; while (test);
 */
SK_API DSLStatement Do(DSLStatement stmt, DSLExpression test, PositionInfo pos = PositionInfo::Capture());

/**
 * for (initializer; test; next) stmt;
 */
SK_API DSLStatement For(DSLStatement initializer, DSLExpression test, DSLExpression next,
                 DSLStatement stmt, PositionInfo pos = PositionInfo::Capture());

/**
 * if (test) ifTrue; [else ifFalse;]
 */
SK_API DSLStatement If(DSLExpression test, DSLStatement ifTrue, DSLStatement ifFalse = DSLStatement(),
                PositionInfo pos = PositionInfo::Capture());

SK_API DSLGlobalVar InterfaceBlock(const DSLModifiers& modifiers,  skstd::string_view typeName,
                            SkTArray<DSLField> fields, skstd::string_view varName = "",
                            int arraySize = 0, PositionInfo pos = PositionInfo::Capture());

/**
 * return [value];
 */
SK_API DSLStatement Return(DSLExpression value = DSLExpression(),
                    PositionInfo pos = PositionInfo::Capture());

/**
 * test ? ifTrue : ifFalse
 */
SK_API DSLExpression Select(DSLExpression test, DSLExpression ifTrue, DSLExpression ifFalse,
                     PositionInfo info = PositionInfo::Capture());

SK_API DSLStatement StaticIf(DSLExpression test, DSLStatement ifTrue,
                      DSLStatement ifFalse = DSLStatement(),
                      PositionInfo pos = PositionInfo::Capture());

// Internal use only
SK_API DSLPossibleStatement PossibleStaticSwitch(DSLExpression value, SkTArray<DSLCase> cases);

SK_API DSLStatement StaticSwitch(DSLExpression value, SkTArray<DSLCase> cases,
                          PositionInfo info = PositionInfo::Capture());

/**
 * @switch (value) { cases }
 */
template<class... Cases>
DSLPossibleStatement StaticSwitch(DSLExpression value, Cases... cases) {
    SkTArray<DSLCase> caseArray;
    caseArray.reserve_back(sizeof...(cases));
    (caseArray.push_back(std::move(cases)), ...);
    return PossibleStaticSwitch(std::move(value), std::move(caseArray));
}

// Internal use only
SK_API DSLPossibleStatement PossibleSwitch(DSLExpression value, SkTArray<DSLCase> cases);

SK_API DSLStatement Switch(DSLExpression value, SkTArray<DSLCase> cases,
                    PositionInfo info = PositionInfo::Capture());

/**
 * switch (value) { cases }
 */
template<class... Cases>
DSLPossibleStatement Switch(DSLExpression value, Cases... cases) {
    SkTArray<DSLCase> caseArray;
    caseArray.reserve_back(sizeof...(cases));
    (caseArray.push_back(std::move(cases)), ...);
    return PossibleSwitch(std::move(value), std::move(caseArray));
}

/**
 * while (test) stmt;
 */
SK_API DSLStatement While(DSLExpression test, DSLStatement stmt,
                   PositionInfo info = PositionInfo::Capture());

/**
 * expression.xyz1
 */
SK_API DSLExpression Swizzle(DSLExpression base,
                      SkSL::SwizzleComponent::Type a,
                      PositionInfo pos = PositionInfo::Capture());

SK_API DSLExpression Swizzle(DSLExpression base,
                      SkSL::SwizzleComponent::Type a,
                      SkSL::SwizzleComponent::Type b,
                      PositionInfo pos = PositionInfo::Capture());

SK_API DSLExpression Swizzle(DSLExpression base,
                      SkSL::SwizzleComponent::Type a,
                      SkSL::SwizzleComponent::Type b,
                      SkSL::SwizzleComponent::Type c,
                      PositionInfo pos = PositionInfo::Capture());

SK_API DSLExpression Swizzle(DSLExpression base,
                      SkSL::SwizzleComponent::Type a,
                      SkSL::SwizzleComponent::Type b,
                      SkSL::SwizzleComponent::Type c,
                      SkSL::SwizzleComponent::Type d,
                      PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the absolute value of x. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Abs(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns true if all of the components of boolean vector x are true.
 */
SK_API DSLExpression All(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns true if any of the components of boolean vector x are true.
 */
SK_API DSLExpression Any(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the arctangent of y over x. Operates componentwise on vectors.
 */
SK_API DSLExpression Atan(DSLExpression y_over_x, PositionInfo pos = PositionInfo::Capture());
SK_API DSLExpression Atan(DSLExpression y, DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns x rounded towards positive infinity. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Ceil(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns x clamped to between min and max. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Clamp(DSLExpression x, DSLExpression min, DSLExpression max,
                    PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the cosine of x. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Cos(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the cross product of x and y.
 */
SK_API DSLExpression Cross(DSLExpression x, DSLExpression y, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns x converted from radians to degrees. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Degrees(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the distance between x and y.
 */
SK_API DSLExpression Distance(DSLExpression x, DSLExpression y,
                       PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the dot product of x and y.
 */
SK_API DSLExpression Dot(DSLExpression x, DSLExpression y, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns a boolean vector indicating whether components of x are equal to the corresponding
 * components of y.
 */
SK_API DSLExpression Equal(DSLExpression x, DSLExpression y, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns e^x. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Exp(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns 2^x. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Exp2(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * If dot(i, nref) >= 0, returns n, otherwise returns -n.
 */
SK_API DSLExpression Faceforward(DSLExpression n, DSLExpression i, DSLExpression nref,
                          PositionInfo pos = PositionInfo::Capture());

/**
 * Returns x rounded towards negative infinity. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Floor(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the fractional part of x. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Fract(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns a boolean vector indicating whether components of x are greater than the corresponding
 * components of y.
 */
SK_API DSLExpression GreaterThan(DSLExpression x, DSLExpression y,
                          PositionInfo pos = PositionInfo::Capture());

/**
 * Returns a boolean vector indicating whether components of x are greater than or equal to the
 * corresponding components of y.
 */
SK_API DSLExpression GreaterThanEqual(DSLExpression x, DSLExpression y,
                               PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the 1/sqrt(x). If x is a vector, operates componentwise.
 */
SK_API DSLExpression Inversesqrt(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the inverse of the matrix x.
 */
SK_API DSLExpression Inverse(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the length of the vector x.
 */
SK_API DSLExpression Length(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns a boolean vector indicating whether components of x are less than the corresponding
 * components of y.
 */
SK_API DSLExpression LessThan(DSLExpression x, DSLExpression y,
                       PositionInfo pos = PositionInfo::Capture());

/**
 * Returns a boolean vector indicating whether components of x are less than or equal to the
 * corresponding components of y.
 */
SK_API DSLExpression LessThanEqual(DSLExpression x, DSLExpression y,
                            PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the log base e of x. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Log(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the log base 2 of x. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Log2(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the larger (closer to positive infinity) of x and y. If x is a vector, operates
 * componentwise. y may be either a vector of the same dimensions as x, or a scalar.
 */
SK_API DSLExpression Max(DSLExpression x, DSLExpression y, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the smaller (closer to negative infinity) of x and y. If x is a vector, operates
 * componentwise. y may be either a vector of the same dimensions as x, or a scalar.
 */
SK_API DSLExpression Min(DSLExpression x, DSLExpression y, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns a linear intepolation between x and y at position a, where a=0 results in x and a=1
 * results in y. If x and y are vectors, operates componentwise. a may be either a vector of the
 * same dimensions as x and y, or a scalar.
 */
SK_API DSLExpression Mix(DSLExpression x, DSLExpression y, DSLExpression a,
                  PositionInfo pos = PositionInfo::Capture());

/**
 * Returns x modulo y. If x is a vector, operates componentwise. y may be either a vector of the
 * same dimensions as x, or a scalar.
 */
SK_API DSLExpression Mod(DSLExpression x, DSLExpression y, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the vector x normalized to a length of 1.
 */
SK_API DSLExpression Normalize(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns a boolean vector indicating whether components of x are not equal to the corresponding
 * components of y.
 */
SK_API DSLExpression NotEqual(DSLExpression x, DSLExpression y,
                       PositionInfo pos = PositionInfo::Capture());

/**
 * Returns x raised to the power y. If x is a vector, operates componentwise. y may be either a
 * vector of the same dimensions as x, or a scalar.
 */
SK_API DSLExpression Pow(DSLExpression x, DSLExpression y, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns x converted from degrees to radians. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Radians(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns i reflected from a surface with normal n.
 */
SK_API DSLExpression Reflect(DSLExpression i, DSLExpression n, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns i refracted across a surface with normal n and ratio of indices of refraction eta.
 */
SK_API DSLExpression Refract(DSLExpression i, DSLExpression n, DSLExpression eta,
                      PositionInfo pos = PositionInfo::Capture());

/**
 * Returns x, rounded to the nearest integer. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Round(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns x clamped to the range [0, 1]. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Saturate(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns -1, 0, or 1 depending on whether x is negative, zero, or positive, respectively. If x is
 * a vector, operates componentwise.
 */
SK_API DSLExpression Sign(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the sine of x. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Sin(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns a smooth interpolation between 0 (at x=edge1) and 1 (at x=edge2). If x is a vector,
 * operates componentwise. edge1 and edge2 may either be both vectors of the same dimensions as x or
 * scalars.
 */
SK_API DSLExpression Smoothstep(DSLExpression edge1, DSLExpression edge2, DSLExpression x,
                         PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the square root of x. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Sqrt(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns 0 if x < edge or 1 if x >= edge. If x is a vector, operates componentwise. edge may be
 * either a vector of the same dimensions as x, or a scalar.
 */
SK_API DSLExpression Step(DSLExpression edge, DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns the tangent of x. If x is a vector, operates componentwise.
 */
SK_API DSLExpression Tan(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

/**
 * Returns x converted from premultipled to unpremultiplied alpha.
 */
SK_API DSLExpression Unpremul(DSLExpression x, PositionInfo pos = PositionInfo::Capture());

} // namespace dsl

} // namespace SkSL

#endif
