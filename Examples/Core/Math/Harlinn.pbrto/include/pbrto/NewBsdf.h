#pragma once
#ifndef PBRTO_NEWBSDF_H_
#define PBRTO_NEWBSDF_H_

/*
   Copyright 2024-2025 Espen Harlinn

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

#include <pbrto/NewPbrt.h>

#include <pbrto/NewBxdfs.h>
#include <pbrto/NewInteraction.h>
#include <pbrto/util/NewMemory.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewVecMath.h>

namespace pbrto
{

    // BSDF Definition
    class BSDF
    {
    public:
        // BSDF Public Methods
        BSDF( ) = default;
        BSDF( Normal3f ns, Vector3f dpdus, BxDF bxdf )
            : bxdf( bxdf ), shadingFrame( Frame::FromXZ( Normalize( dpdus ), Vector3f::Simd( ns ) ) )
        {
        }

        operator bool( ) const 
        { 
            return ( bool )bxdf; 
        }
        BxDFFlags Flags( ) const 
        { 
            return bxdf.Flags( ); 
        }

        Vector3f RenderToLocal( Vector3f v ) const 
        { 
            return shadingFrame.ToLocal( v ); 
        }
        Vector3f LocalToRender( Vector3f v ) const 
        { 
            return shadingFrame.FromLocal( v ); 
        }

        SampledSpectrum f( Vector3f woRender, Vector3f wiRender, TransportMode mode = TransportMode::Radiance ) const
        {
            Vector3f wi = RenderToLocal( wiRender ), wo = RenderToLocal( woRender );
            if ( wo.z == 0 )
                return {};
            return bxdf.f( wo, wi, mode );
        }

        template <typename BxDF>
        PBRT_CPU_GPU SampledSpectrum f( Vector3f woRender, Vector3f wiRender,
            TransportMode mode = TransportMode::Radiance ) const
        {
            Vector3f wi = RenderToLocal( wiRender ), wo = RenderToLocal( woRender );
            if ( wo.z == 0 )
                return {};
            const BxDF* specificBxDF = bxdf.CastOrNullptr<BxDF>( );
            return specificBxDF->f( wo, wi, mode );
        }

        PBRT_CPU_GPU
            pstdo::optional<BSDFSample> Sample_f(
                Vector3f woRender, Float u, Point2f u2,
                TransportMode mode = TransportMode::Radiance,
                BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            Vector3f wo = RenderToLocal( woRender );
            if ( wo.z == 0 || !( bxdf.Flags( ) & sampleFlags ) )
                return {};
            // Sample _bxdf_ and return _BSDFSample_
            pstdo::optional<BSDFSample> bs = bxdf.Sample_f( wo, u, u2, mode, sampleFlags );
            if ( bs )
                NDCHECK_GE( bs->pdf, 0 );
            if ( !bs || !bs->f || bs->pdf == 0 || bs->wi.z == 0 )
                return {};
            PBRT_DBG( "For wo = (%f, %f, %f), ns %f %f %f sampled f = %f %f %f %f, pdf = %f, "
                "ratio[0] = %f wi = (%f, %f, %f)\n",
                wo.x, wo.y, wo.z, shadingFrame.z.x, shadingFrame.z.y, shadingFrame.z.z,
                bs->f[ 0 ], bs->f[ 1 ], bs->f[ 2 ], bs->f[ 3 ], bs->pdf,
                ( bs->pdf > 0 ) ? ( bs->f[ 0 ] / bs->pdf ) : 0, bs->wi.x, bs->wi.y, bs->wi.z );
            bs->wi = LocalToRender( bs->wi );
            return bs;
        }

        PBRT_CPU_GPU
            Float PDF( Vector3f woRender, Vector3f wiRender,
                TransportMode mode = TransportMode::Radiance,
                BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            Vector3f wo = RenderToLocal( woRender ), wi = RenderToLocal( wiRender );
            if ( wo.z == 0 )
                return 0;
            return bxdf.PDF( wo, wi, mode, sampleFlags );
        }

        template <typename BxDF>
        PBRT_CPU_GPU pstdo::optional<BSDFSample> Sample_f(
            Vector3f woRender, Float u, Point2f u2,
            TransportMode mode = TransportMode::Radiance,
            BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            Vector3f wo = RenderToLocal( woRender );
            if ( wo.z == 0 )
                return {};

            const BxDF* specificBxDF = bxdf.Cast<BxDF>( );
            if ( !( specificBxDF->Flags( ) & sampleFlags ) )
                return {};

            pstdo::optional<BSDFSample> bs =
                specificBxDF->Sample_f( wo, u, u2, mode, sampleFlags );
            if ( !bs || !bs->f || bs->pdf == 0 || bs->wi.z == 0 )
                return {};
            NDCHECK_GT( bs->pdf, 0 );

            PBRT_DBG( "For wo = (%f, %f, %f) ns %f %f %f sampled f = %f %f %f %f, pdf = %f, "
                "ratio[0] = %f wi = (%f, %f, %f)\n",
                wo.x, wo.y, wo.z, shadingFrame.z.x, shadingFrame.z.y, shadingFrame.z.z,
                bs->f[ 0 ], bs->f[ 1 ], bs->f[ 2 ], bs->f[ 3 ], bs->pdf,
                ( bs->pdf > 0 ) ? ( bs->f[ 0 ] / bs->pdf ) : 0, bs->wi.x, bs->wi.y, bs->wi.z );

            bs->wi = LocalToRender( bs->wi );

            return bs;
        }

        template <typename BxDF>
        PBRT_CPU_GPU Float
            PDF( Vector3f woRender, Vector3f wiRender,
                TransportMode mode = TransportMode::Radiance,
                BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            Vector3f wo = RenderToLocal( woRender ), wi = RenderToLocal( wiRender );
            if ( wo.z == 0 )
                return 0;
            const BxDF* specificBxDF = bxdf.Cast<BxDF>( );
            return specificBxDF->PDF( wo, wi, mode, sampleFlags );
        }

        std::string ToString( ) const;

        PBRT_CPU_GPU
            SampledSpectrum rho( pstdo::span<const Point2f> u1, pstdo::span<const Float> uc,
                pstdo::span<const Point2f> u2 ) const
        {
            return bxdf.rho( u1, uc, u2 );
        }
        PBRT_CPU_GPU
            SampledSpectrum rho( Vector3f woRender, pstdo::span<const Float> uc,
                pstdo::span<const Point2f> u ) const
        {
            Vector3f wo = RenderToLocal( woRender );
            return bxdf.rho( wo, uc, u );
        }

        PBRT_CPU_GPU
            void Regularize( ) { bxdf.Regularize( ); }

    private:
        // BSDF Private Members
        BxDF bxdf;
        Frame shadingFrame;
    };

}


#endif
