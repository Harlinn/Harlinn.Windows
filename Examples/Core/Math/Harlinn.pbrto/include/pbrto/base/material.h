// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef PBRT_BASE_MATERIAL_H
#define PBRT_BASE_MATERIAL_H

#include <pbrto/pbrt.h>

#include <pbrto/base/bssrdf.h>
#include <pbrto/base/texture.h>
#include <pbrto/util/taggedptr.h>

#include <map>
#include <string>

namespace pbrt {

struct MaterialEvalContext;

// Material Declarations
class CoatedDiffuseMaterial;
class CoatedConductorMaterial;
class ConductorMaterial;
class DielectricMaterial;
class DiffuseMaterial;
class DiffuseTransmissionMaterial;
class HairMaterial;
class MeasuredMaterial;
class SubsurfaceMaterial;
class ThinDielectricMaterial;
class MixMaterial;

// Material Definition
class Material
    : public TaggedPointer<  // Material Types
          CoatedDiffuseMaterial, CoatedConductorMaterial, ConductorMaterial,
          DielectricMaterial, DiffuseMaterial, DiffuseTransmissionMaterial, HairMaterial,
          MeasuredMaterial, SubsurfaceMaterial, ThinDielectricMaterial, MixMaterial

          > {
  public:
    // Material Interface
    using TaggedPointer::TaggedPointer;

    static Material Create(const std::string &name,
                           const TextureParameterDictionary &parameters, Image *normalMap,
                           /*const */ std::map<std::string, Material> &namedMaterials,
                           const FileLoc *loc, Allocator alloc);

    std::string ToString() const;

    template <typename TextureEvaluator>
    inline BSDF GetBSDF(TextureEvaluator texEval, MaterialEvalContext ctx,
                        SampledWavelengths &lambda, ScratchBuffer &buf) const;

    template <typename TextureEvaluator>
    inline BSSRDF GetBSSRDF(TextureEvaluator texEval, MaterialEvalContext ctx,
                            SampledWavelengths &lambda, ScratchBuffer &buf) const;

    template <typename TextureEvaluator>
    PBRT_CPU_GPU inline bool CanEvaluateTextures(TextureEvaluator texEval) const;

    PBRT_CPU_GPU inline const Image *GetNormalMap() const;

    PBRT_CPU_GPU inline FloatTexture GetDisplacement() const;

    PBRT_CPU_GPU inline bool HasSubsurfaceScattering() const;
};

}  // namespace pbrt

#endif  // PBRT_BASE_MATERIAL_H
