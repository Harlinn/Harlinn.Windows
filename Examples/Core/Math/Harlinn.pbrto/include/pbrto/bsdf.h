/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef PBRT_BSDF_H
#define PBRT_BSDF_H

#include <pbrto/pbrt.h>

#include <pbrto/bxdfs.h>
#include <pbrto/interaction.h>
#include <pbrto/util/memory.h>
#include <pbrto/util/pstd.h>
#include <pbrto/util/vecmath.h>

namespace pbrt {

// BSDF Definition
class BSDF {
  public:
    // BSDF Public Methods
    BSDF() = default;
    PBRT_CPU_GPU
    BSDF(Normal3f ns, Vector3f dpdus, BxDF bxdf)
        : bxdf(bxdf), shadingFrame(Frame::FromXZ(Normalize(dpdus), Vector3f(ns))) {}

    PBRT_CPU_GPU
    operator bool() const { return (bool)bxdf; }
    PBRT_CPU_GPU
    BxDFFlags Flags() const { return bxdf.Flags(); }

    PBRT_CPU_GPU
    Vector3f RenderToLocal(Vector3f v) const { return shadingFrame.ToLocal(v); }
    PBRT_CPU_GPU
    Vector3f LocalToRender(Vector3f v) const { return shadingFrame.FromLocal(v); }

    PBRT_CPU_GPU
    SampledSpectrum f(Vector3f woRender, Vector3f wiRender,
                      TransportMode mode = TransportMode::Radiance) const {
        Vector3f wi = RenderToLocal(wiRender), wo = RenderToLocal(woRender);
        if (wo.z == 0)
            return {};
        return bxdf.f(wo, wi, mode);
    }

    template <typename BxDF>
    PBRT_CPU_GPU SampledSpectrum f(Vector3f woRender, Vector3f wiRender,
                                   TransportMode mode = TransportMode::Radiance) const {
        Vector3f wi = RenderToLocal(wiRender), wo = RenderToLocal(woRender);
        if (wo.z == 0)
            return {};
        const BxDF *specificBxDF = bxdf.CastOrNullptr<BxDF>();
        return specificBxDF->f(wo, wi, mode);
    }

    PBRT_CPU_GPU
    pstd::optional<BSDFSample> Sample_f(
        Vector3f woRender, Float u, Point2f u2,
        TransportMode mode = TransportMode::Radiance,
        BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All) const {
        Vector3f wo = RenderToLocal(woRender);
        if (wo.z == 0 || !(bxdf.Flags() & sampleFlags))
            return {};
        // Sample _bxdf_ and return _BSDFSample_
        pstd::optional<BSDFSample> bs = bxdf.Sample_f(wo, u, u2, mode, sampleFlags);
        if (bs)
            DCHECK_GE(bs->pdf, 0);
        if (!bs || !bs->f || bs->pdf == 0 || bs->wi.z == 0)
            return {};
        PBRT_DBG("For wo = (%f, %f, %f), ns %f %f %f sampled f = %f %f %f %f, pdf = %f, "
                 "ratio[0] = %f wi = (%f, %f, %f)\n",
                 wo.x, wo.y, wo.z, shadingFrame.z.x, shadingFrame.z.y, shadingFrame.z.z,
                 bs->f[0], bs->f[1], bs->f[2], bs->f[3], bs->pdf,
                 (bs->pdf > 0) ? (bs->f[0] / bs->pdf) : 0, bs->wi.x, bs->wi.y, bs->wi.z);
        bs->wi = LocalToRender(bs->wi);
        return bs;
    }

    PBRT_CPU_GPU
    Float PDF(Vector3f woRender, Vector3f wiRender,
              TransportMode mode = TransportMode::Radiance,
              BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All) const {
        Vector3f wo = RenderToLocal(woRender), wi = RenderToLocal(wiRender);
        if (wo.z == 0)
            return 0;
        return bxdf.PDF(wo, wi, mode, sampleFlags);
    }

    template <typename BxDF>
    PBRT_CPU_GPU pstd::optional<BSDFSample> Sample_f(
        Vector3f woRender, Float u, Point2f u2,
        TransportMode mode = TransportMode::Radiance,
        BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All) const {
        Vector3f wo = RenderToLocal(woRender);
        if (wo.z == 0)
            return {};

        const BxDF *specificBxDF = bxdf.Cast<BxDF>();
        if (!(specificBxDF->Flags() & sampleFlags))
            return {};

        pstd::optional<BSDFSample> bs =
            specificBxDF->Sample_f(wo, u, u2, mode, sampleFlags);
        if (!bs || !bs->f || bs->pdf == 0 || bs->wi.z == 0)
            return {};
        DCHECK_GT(bs->pdf, 0);

        PBRT_DBG("For wo = (%f, %f, %f) ns %f %f %f sampled f = %f %f %f %f, pdf = %f, "
                 "ratio[0] = %f wi = (%f, %f, %f)\n",
                 wo.x, wo.y, wo.z, shadingFrame.z.x, shadingFrame.z.y, shadingFrame.z.z,
                 bs->f[0], bs->f[1], bs->f[2], bs->f[3], bs->pdf,
                 (bs->pdf > 0) ? (bs->f[0] / bs->pdf) : 0, bs->wi.x, bs->wi.y, bs->wi.z);

        bs->wi = LocalToRender(bs->wi);

        return bs;
    }

    template <typename BxDF>
    PBRT_CPU_GPU Float
    PDF(Vector3f woRender, Vector3f wiRender,
        TransportMode mode = TransportMode::Radiance,
        BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All) const {
        Vector3f wo = RenderToLocal(woRender), wi = RenderToLocal(wiRender);
        if (wo.z == 0)
            return 0;
        const BxDF *specificBxDF = bxdf.Cast<BxDF>();
        return specificBxDF->PDF(wo, wi, mode, sampleFlags);
    }

    std::string ToString() const;

    PBRT_CPU_GPU
    SampledSpectrum rho(pstd::span<const Point2f> u1, pstd::span<const Float> uc,
                        pstd::span<const Point2f> u2) const {
        return bxdf.rho(u1, uc, u2);
    }
    PBRT_CPU_GPU
    SampledSpectrum rho(Vector3f woRender, pstd::span<const Float> uc,
                        pstd::span<const Point2f> u) const {
        Vector3f wo = RenderToLocal(woRender);
        return bxdf.rho(wo, uc, u);
    }

    PBRT_CPU_GPU
    void Regularize() { bxdf.Regularize(); }

  private:
    // BSDF Private Members
    BxDF bxdf;
    Frame shadingFrame;
};

}  // namespace pbrt

#endif  // PBRT_BSDF_H
