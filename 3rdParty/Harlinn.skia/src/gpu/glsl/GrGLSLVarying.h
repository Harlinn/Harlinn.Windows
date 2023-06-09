/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrGLSLVarying_DEFINED
#define GrGLSLVarying_DEFINED

#include <skia/private/GrTypesPriv.h>
#include "src/core/SkTBlockList.h"
#include "src/gpu/GrShaderVar.h"
#include "src/gpu/glsl/GrGLSLProgramDataManager.h"

class GrGeometryProcessor;
class GrGLSLProgramBuilder;

#ifdef SK_DEBUG
static bool is_matrix(GrSLType type) {
    switch (type) {
        case kFloat2x2_GrSLType:
        case kFloat3x3_GrSLType:
        case kFloat4x4_GrSLType:
        case kHalf2x2_GrSLType:
        case kHalf3x3_GrSLType:
        case kHalf4x4_GrSLType:
            return true;
        default:
            return false;
    }
}
#endif

class GrGLSLVarying {
public:
    enum class Scope {
        kVertToFrag,
        kVertToGeo,
        kGeoToFrag
    };

    GrGLSLVarying() = default;
    GrGLSLVarying(GrSLType type, Scope scope = Scope::kVertToFrag)
        : fType(type)
        , fScope(scope) {
        // Metal doesn't support varying matrices, so we disallow them everywhere for consistency
        SkASSERT(!is_matrix(type));
    }

    void reset(GrSLType type, Scope scope = Scope::kVertToFrag) {
        // Metal doesn't support varying matrices, so we disallow them everywhere for consistency
        SkASSERT(!is_matrix(type));
        *this = GrGLSLVarying();
        fType = type;
        fScope = scope;
    }

    GrSLType type() const { return fType; }
    Scope scope() const { return fScope; }
    bool isInVertexShader() const { return Scope::kGeoToFrag != fScope; }
    bool isInFragmentShader() const { return Scope::kVertToGeo != fScope; }

    const char* vsOut() const { SkASSERT(this->isInVertexShader()); return fVsOut; }
    const char* fsIn() const { SkASSERT(this->isInFragmentShader()); return fFsIn; }

    GrShaderVar vsOutVar() const {
        SkASSERT(this->isInVertexShader());
        return GrShaderVar(this->vsOut(), fType, GrShaderVar::TypeModifier::Out);
    }

    GrShaderVar fsInVar() const {
        SkASSERT(this->isInFragmentShader());
        return GrShaderVar(this->fsIn(), fType, GrShaderVar::TypeModifier::In);
    }

private:
    GrSLType fType = kVoid_GrSLType;
    Scope fScope = Scope::kVertToFrag;
    const char* fVsOut = nullptr;
    const char* fFsIn = nullptr;

    friend class GrGLSLVaryingHandler;
};

static constexpr int kVaryingsPerBlock = 8;

class GrGLSLVaryingHandler {
public:
    explicit GrGLSLVaryingHandler(GrGLSLProgramBuilder* program)
        : fVaryings(kVaryingsPerBlock)
        , fVertexInputs(kVaryingsPerBlock)
        , fVertexOutputs(kVaryingsPerBlock)
        , fFragInputs(kVaryingsPerBlock)
        , fFragOutputs(kVaryingsPerBlock)
        , fProgramBuilder(program)
        , fDefaultInterpolationModifier(nullptr) {}

    virtual ~GrGLSLVaryingHandler() {}

    /**
     * Notifies the varying handler that this shader will never emit geometry in perspective and
     * therefore does not require perspective-correct interpolation. When supported, this allows
     * varyings to use the "noperspective" keyword, which means the GPU can use cheaper math for
     * interpolation.
     */
    SK_API void setNoPerspective();

    enum class Interpolation {
        kInterpolated,
        kCanBeFlat, // Use "flat" if it will be faster.
        kMustBeFlat // Use "flat" even if it is known to be slow.
    };

    /**
     * addVarying allows fine grained control for setting up varyings between stages. Calling this
     * function will make sure all necessary decls are setup for the client. The client however is
     * responsible for setting up all shader code (e.g "vOut = vIn;") If you just need to take an
     * attribute and pass it through to an output value in a fragment shader, use
     * addPassThroughAttribute.
     * TODO convert most uses of addVarying to addPassThroughAttribute
     */
    SK_API void addVarying(const char* name, GrGLSLVarying* varying,
                    Interpolation = Interpolation::kInterpolated);

    /**
     * The GP can use these calls to pass a vertex shader variable directly to 'output' in the
     * fragment shader. Though this adds code to vertex and fragment stages, 'output' is expected to
     * be defined in the fragment shader before the call is made.
     * TODO it might be nicer behavior to have a flag to declare output inside these calls
     */
    SK_API void addPassThroughAttribute(const GrShaderVar& vsVar,
                                 const char* output,
                                 Interpolation = Interpolation::kInterpolated);

    SK_API void emitAttributes(const GrGeometryProcessor&);

    // This should be called once all attributes and varyings have been added to the
    // GrGLSLVaryingHanlder and before getting/adding any of the declarations to the shaders.
    SK_API void finalize();

    SK_API void getVertexDecls(SkString* inputDecls, SkString* outputDecls) const;
    SK_API void getFragDecls(SkString* inputDecls, SkString* outputDecls) const;

protected:
    struct VaryingInfo {
        GrSLType         fType;
        bool             fIsFlat;
        SkString         fVsOut;
        GrShaderFlags    fVisibility;
    };

    typedef SkTBlockList<VaryingInfo> VaryingList;
    typedef SkTBlockList<GrShaderVar> VarArray;

    VaryingList    fVaryings;
    VarArray       fVertexInputs;
    VarArray       fVertexOutputs;
    VarArray       fFragInputs;
    VarArray       fFragOutputs;

    // This is not owned by the class
    GrGLSLProgramBuilder* fProgramBuilder;

private:
    SK_API void addAttribute(const GrShaderVar& var);

    virtual void onFinalize() = 0;

    // helper function for get*Decls
    SK_API void appendDecls(const VarArray& vars, SkString* out) const;

    const char* fDefaultInterpolationModifier;

    friend class GrGLSLProgramBuilder;
};

#endif
