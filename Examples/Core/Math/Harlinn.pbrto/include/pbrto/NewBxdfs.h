#pragma once
#ifndef PBRTO_NEWBXDFS_H_
#define PBRTO_NEWBXDFS_H_

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

#include <pbrto/base/NewBxdf.h>
#include <pbrto/NewInteraction.h>
#include <pbrto/NewMedia.h>
#include <pbrto/NewOptions.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewMemory.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewScattering.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewTaggedptr.h>
#include <pbrto/util/NewVecMath.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <string>

namespace pbrto
{

    // DiffuseBxDF Definition
    class DiffuseBxDF
    {
    private:
        SampledSpectrum R;
    public:
        // DiffuseBxDF Public Methods
        DiffuseBxDF( ) = default;
        DiffuseBxDF( SampledSpectrum R ) 
            : R( R ) 
        { }

        SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const
        {
            if ( !SameHemisphere( wo, wi ) )
                return SampledSpectrum( 0.f );
            return R * InvPi;
        }

        pstdo::optional<BSDFSample> Sample_f( Vector3f wo, Float uc, Point2f u, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            if ( !( sampleFlags & BxDFReflTransFlags::Reflection ) )
                return {};
            // Sample cosine-weighted hemisphere to compute _wi_ and _pdf_
            Vector3f wi = SampleCosineHemisphere( u );
            if ( wo.z < 0 )
                wi.z *= -1;
            Float pdf = CosineHemispherePDF( AbsCosTheta( wi ) );

            return BSDFSample( R * InvPi, Vector3f::Simd( wi ), pdf, BxDFFlags::DiffuseReflection );
        }

        Float PDF( Vector3f wo, Vector3f wi, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            if ( !( sampleFlags & BxDFReflTransFlags::Reflection ) || !SameHemisphere( wo, wi ) )
                return 0;
            return CosineHemispherePDF( AbsCosTheta( wi ) );
        }

        static constexpr const char* Name( ) { return "DiffuseBxDF"; }

        std::string ToString( ) const;

        void Regularize( ) {}

        BxDFFlags Flags( ) const
        {
            return R ? BxDFFlags::DiffuseReflection : BxDFFlags::Unset;
        }

    
    };

    // DiffuseTransmissionBxDF Definition
    class DiffuseTransmissionBxDF
    {
        // DiffuseTransmissionBxDF Private Members
        SampledSpectrum R, T;
    public:
        // DiffuseTransmissionBxDF Public Methods
        DiffuseTransmissionBxDF( ) = default;
        DiffuseTransmissionBxDF( SampledSpectrum R, SampledSpectrum T ) : R( R ), T( T ) {}

        SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const
        {
            return SameHemisphere( wo, wi ) ? ( R * InvPi ) : ( T * InvPi );
        }

        pstdo::optional<BSDFSample> Sample_f(
                Vector3f wo, Float uc, Point2f u, TransportMode mode,
                BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            // Compute reflection and transmission probabilities for diffuse BSDF
            Float pr = R.MaxComponentValue( ), pt = T.MaxComponentValue( );
            if ( !( sampleFlags & BxDFReflTransFlags::Reflection ) )
                pr = 0;
            if ( !( sampleFlags & BxDFReflTransFlags::Transmission ) )
                pt = 0;
            if ( pr == 0 && pt == 0 )
                return {};

            // Randomly sample diffuse BSDF reflection or transmission
            if ( uc < pr / ( pr + pt ) )
            {
                // Sample diffuse BSDF reflection
                Vector3f wi = SampleCosineHemisphere( u );
                if ( wo.z < 0 )
                    wi.z *= -1;
                Float pdf = CosineHemispherePDF( AbsCosTheta( wi ) ) * pr / ( pr + pt );
                return BSDFSample( f( wo, wi, mode ), wi, pdf, BxDFFlags::DiffuseReflection );

            }
            else
            {
                // Sample diffuse BSDF transmission
                Vector3f wi = SampleCosineHemisphere( u );
                if ( wo.z > 0 )
                    wi.z *= -1;
                Float pdf = CosineHemispherePDF( AbsCosTheta( wi ) ) * pt / ( pr + pt );
                return BSDFSample( f( wo, wi, mode ), wi, pdf, BxDFFlags::DiffuseTransmission );
            }
        }

        Float PDF( Vector3f wo, Vector3f wi, TransportMode mode,
                BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            // Compute reflection and transmission probabilities for diffuse BSDF
            Float pr = R.MaxComponentValue( ), pt = T.MaxComponentValue( );
            if ( !( sampleFlags & BxDFReflTransFlags::Reflection ) )
                pr = 0;
            if ( !( sampleFlags & BxDFReflTransFlags::Transmission ) )
                pt = 0;
            if ( pr == 0 && pt == 0 )
                return {};

            if ( SameHemisphere( wo, wi ) )
                return pr / ( pr + pt ) * CosineHemispherePDF( AbsCosTheta( wi ) );
            else
                return pt / ( pr + pt ) * CosineHemispherePDF( AbsCosTheta( wi ) );
        }

        static constexpr const char* Name( ) { return "DiffuseTransmissionBxDF"; }

        std::string ToString( ) const;

        void Regularize( ) {}

        BxDFFlags Flags( ) const
        {
            return ( ( R ? BxDFFlags::DiffuseReflection : BxDFFlags::Unset ) |
                ( T ? BxDFFlags::DiffuseTransmission : BxDFFlags::Unset ) );
        }

    private:
        
    };

    // DielectricBxDF Definition
    class DielectricBxDF
    {
        // DielectricBxDF Private Members
        Float eta;
        TrowbridgeReitzDistribution mfDistrib;
    public:
        // DielectricBxDF Public Methods
        DielectricBxDF( ) = default;
        DielectricBxDF( Float eta, TrowbridgeReitzDistribution mfDistrib )
            : eta( eta ), mfDistrib( mfDistrib )
        {
        }

        BxDFFlags Flags( ) const
        {
            BxDFFlags flags = ( eta == 1 ) ? BxDFFlags::Transmission
                : ( BxDFFlags::Reflection | BxDFFlags::Transmission );
            return flags |
                ( mfDistrib.EffectivelySmooth( ) ? BxDFFlags::Specular : BxDFFlags::Glossy );
        }

        pstdo::optional<BSDFSample> Sample_f( Vector3f wo, Float uc, Point2f u, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const;

        SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const;
        Float PDF( Vector3f wo, Vector3f wi, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const;

        static constexpr const char* Name( ) { return "DielectricBxDF"; }

        std::string ToString( ) const;

        void Regularize( ) { mfDistrib.Regularize( ); }

    };

    // ThinDielectricBxDF Definition
    class ThinDielectricBxDF
    {
        Float eta;
    public:
        // ThinDielectricBxDF Public Methods
        ThinDielectricBxDF( ) = default;
        ThinDielectricBxDF( Float eta ) : eta( eta ) {}

        SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const
        {
            return SampledSpectrum( 0 );
        }

        pstdo::optional<BSDFSample> Sample_f( Vector3f wo, Float uc, Point2f u, TransportMode mode, BxDFReflTransFlags sampleFlags ) const
        {
            Float R = FrDielectric( AbsCosTheta( wo ), eta ); 
            Float T = 1 - R;
            // Compute _R_ and _T_ accounting for scattering between interfaces
            if ( R < 1 )
            {
                R += Sqr( T ) * R / ( 1 - Sqr( R ) );
                T = 1 - R;
            }

            // Compute probabilities _pr_ and _pt_ for sampling reflection and transmission
            Float pr = R; 
            Float pt = T;
            if ( !( sampleFlags & BxDFReflTransFlags::Reflection ) )
                pr = 0;
            if ( !( sampleFlags & BxDFReflTransFlags::Transmission ) )
                pt = 0;
            if ( pr == 0 && pt == 0 )
                return {};

            if ( uc < pr / ( pr + pt ) )
            {
                // Sample perfect specular dielectric BRDF
                Vector3f wi( -wo.x, -wo.y, wo.z );
                SampledSpectrum fr( R / AbsCosTheta( wi ) );
                return BSDFSample( fr, wi, pr / ( pr + pt ), BxDFFlags::SpecularReflection );

            }
            else
            {
                // Sample perfect specular transmission at thin dielectric interface
                Vector3f wi = -wo;
                SampledSpectrum ft( T / AbsCosTheta( wi ) );
                return BSDFSample( ft, wi, pt / ( pr + pt ), BxDFFlags::SpecularTransmission );
            }
        }

        Float PDF( Vector3f wo, Vector3f wi, TransportMode mode, BxDFReflTransFlags sampleFlags ) const
        {
            return 0;
        }

        static constexpr const char* Name( ) { return "ThinDielectricBxDF"; }

        std::string ToString( ) const;

        void Regularize( )
        { /* TODO */
        }

        BxDFFlags Flags( ) const
        {
            return ( BxDFFlags::Reflection | BxDFFlags::Transmission | BxDFFlags::Specular );
        }
    };

    // ConductorBxDF Definition
    class ConductorBxDF
    {
        // ConductorBxDF Private Members
        TrowbridgeReitzDistribution mfDistrib;
        SampledSpectrum eta; 
        SampledSpectrum k;
    public:
        // ConductorBxDF Public Methods
        ConductorBxDF( ) = default;
        ConductorBxDF( const TrowbridgeReitzDistribution& mfDistrib, SampledSpectrum eta, SampledSpectrum k )
            : mfDistrib( mfDistrib ), eta( eta ), k( k )
        {
        }

        BxDFFlags Flags( ) const
        {
            return mfDistrib.EffectivelySmooth( ) ? BxDFFlags::SpecularReflection
                : BxDFFlags::GlossyReflection;
        }

        pstdo::optional<BSDFSample> Sample_f( Vector3f wo, Float uc, Point2f u, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            if ( !( sampleFlags & BxDFReflTransFlags::Reflection ) )
            {
                return {};
            }
            if ( mfDistrib.EffectivelySmooth( ) )
            {
                // Sample perfect specular conductor BRDF
                Vector3f wi( -wo.x, -wo.y, wo.z );
                SampledSpectrum f = FrComplex( AbsCosTheta( wi ), eta, k ) / AbsCosTheta( wi );
                return BSDFSample( f, wi, 1, BxDFFlags::SpecularReflection );
            }
            // Sample rough conductor BRDF
            // Sample microfacet normal $\wm$ and reflected direction $\wi$
            if ( wo.z == 0 )
            {
                return {};
            }
            Vector3f wm = mfDistrib.Sample_wm( wo, u );
            Vector3f wi = Reflect( wo, wm );
            if ( !SameHemisphere( wo, wi ) )
                return {};

            // Compute PDF of _wi_ for microfacet reflection
            Float pdf = mfDistrib.PDF( wo, wm ) / ( 4 * ScalarAbsDot( wo, wm ) );

            Float cosTheta_o = AbsCosTheta( wo ), cosTheta_i = AbsCosTheta( wi );
            if ( cosTheta_i == 0 || cosTheta_o == 0 )
                return {};
            // Evaluate Fresnel factor _F_ for conductor BRDF
            SampledSpectrum F = FrComplex( ScalarAbsDot( wo, wm ), eta, k );

            SampledSpectrum f =
                mfDistrib.D( wm ) * F * mfDistrib.G( wo, wi ) / ( 4 * cosTheta_i * cosTheta_o );
            return BSDFSample( f, wi, pdf, BxDFFlags::GlossyReflection );
        }

        SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const
        {
            if ( !SameHemisphere( wo, wi ) )
                return {};
            if ( mfDistrib.EffectivelySmooth( ) )
                return {};
            // Evaluate rough conductor BRDF
            // Compute cosines and $\wm$ for conductor BRDF
            Float cosTheta_o = AbsCosTheta( wo ), cosTheta_i = AbsCosTheta( wi );
            if ( cosTheta_i == 0 || cosTheta_o == 0 )
                return {};
            Vector3f::Simd wm = wi + wo;
            if ( ScalarLengthSquared( wm ) == 0 )
                return {};
            wm = Normalize( wm );

            // Evaluate Fresnel factor _F_ for conductor BRDF
            SampledSpectrum F = FrComplex( ScalarAbsDot( wo, wm ), eta, k );

            return mfDistrib.D( wm ) * F * mfDistrib.G( wo, wi ) / ( 4 * cosTheta_i * cosTheta_o );
        }

        Float PDF( Vector3f wo, Vector3f wi, TransportMode mode, BxDFReflTransFlags sampleFlags ) const
        {
            if ( !( sampleFlags & BxDFReflTransFlags::Reflection ) )
                return 0;
            if ( !SameHemisphere( wo, wi ) )
                return 0;
            if ( mfDistrib.EffectivelySmooth( ) )
                return 0;
            // Evaluate sampling PDF of rough conductor BRDF
            Vector3f wm = wo + wi;
            NCHECK_RARE( 1e-5f, ScalarLengthSquared( wm ) == 0 );
            if ( ScalarLengthSquared( wm ) == 0 )
                return 0;
            wm = FaceForward( ToVector3f( Normalize( wm ) ), Normal3f( 0, 0, 1 ) );
            return mfDistrib.PDF( wo, wm ) / ( 4 * ScalarAbsDot( wo, wm ) );
        }

        static constexpr const char* Name( ) 
        { 
            return "ConductorBxDF"; 
        }
        std::string ToString( ) const;

        void Regularize( ) 
        { 
            mfDistrib.Regularize( ); 
        }

    private:
        
    };

    // TopOrBottomBxDF Definition
    template <typename TopBxDF, typename BottomBxDF>
    class TopOrBottomBxDF
    {
        const TopBxDF* top = nullptr;
        const BottomBxDF* bottom = nullptr;
    public:
        // TopOrBottomBxDF Public Methods
        TopOrBottomBxDF( ) = default;
        TopOrBottomBxDF& operator=( const TopBxDF* t )
        {
            top = t;
            bottom = nullptr;
            return *this;
        }
        TopOrBottomBxDF& operator=( const BottomBxDF* b )
        {
            bottom = b;
            top = nullptr;
            return *this;
        }

        SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const
        {
            return top ? top->f( wo, wi, mode ) : bottom->f( wo, wi, mode );
        }

        pstdo::optional<BSDFSample> Sample_f( Vector3f wo, Float uc, Point2f u, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            return top ? top->Sample_f( wo, uc, u, mode, sampleFlags )
                : bottom->Sample_f( wo, uc, u, mode, sampleFlags );
        }

        Float PDF( Vector3f wo, Vector3f wi, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            return top ? top->PDF( wo, wi, mode, sampleFlags )
                : bottom->PDF( wo, wi, mode, sampleFlags );
        }

        BxDFFlags Flags( ) const 
        { 
            return top ? top->Flags( ) : bottom->Flags( ); 
        }
    };

    // LayeredBxDF Definition
    template <typename TopBxDF, typename BottomBxDF, bool twoSided>
    class LayeredBxDF
    {
    public:
        // LayeredBxDF Public Methods
        LayeredBxDF( ) = default;
        LayeredBxDF( TopBxDF top, BottomBxDF bottom, Float thickness, const SampledSpectrum& albedo, Float g, int maxDepth, int nSamples )
            : top( top ),
              bottom( bottom ),
              thickness( std::max( thickness, std::numeric_limits<Float>::min( ) ) ),
              g( g ),
              albedo( albedo ),
              maxDepth( maxDepth ),
              nSamples( nSamples )
        {
        }

        std::string ToString( ) const;

        void Regularize( )
        {
            top.Regularize( );
            bottom.Regularize( );
        }

        BxDFFlags Flags( ) const
        {
            BxDFFlags topFlags = top.Flags( ), bottomFlags = bottom.Flags( );
            NCHECK( IsTransmissive( topFlags ) ||
                IsTransmissive( bottomFlags ) );  // otherwise, why bother?

            BxDFFlags flags = BxDFFlags::Reflection;
            if ( IsSpecular( topFlags ) )
                flags = flags | BxDFFlags::Specular;

            if ( IsDiffuse( topFlags ) || IsDiffuse( bottomFlags ) || albedo )
                flags = flags | BxDFFlags::Diffuse;
            else if ( IsGlossy( topFlags ) || IsGlossy( bottomFlags ) )
                flags = flags | BxDFFlags::Glossy;

            if ( IsTransmissive( topFlags ) && IsTransmissive( bottomFlags ) )
                flags = flags | BxDFFlags::Transmission;

            return flags;
        }

        SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const
        {
            SampledSpectrum f( 0. );
            // Estimate _LayeredBxDF_ value _f_ using random sampling
            // Set _wo_ and _wi_ for layered BSDF evaluation
            if ( twoSided&& wo.z < 0 )
            {
                wo = -wo;
                wi = -wi;
            }

            // Determine entrance interface for layered BSDF
            TopOrBottomBxDF<TopBxDF, BottomBxDF> enterInterface;
            bool enteredTop = twoSided || wo.z > 0;
            if ( enteredTop )
                enterInterface = &top;
            else
                enterInterface = &bottom;

            // Determine exit interface and exit $z$ for layered BSDF
            TopOrBottomBxDF<TopBxDF, BottomBxDF> exitInterface, nonExitInterface;
            if ( SameHemisphere( wo, wi ) ^ enteredTop )
            {
                exitInterface = &bottom;
                nonExitInterface = &top;
            }
            else
            {
                exitInterface = &top;
                nonExitInterface = &bottom;
            }
            Float exitZ = ( SameHemisphere( wo, wi ) ^ enteredTop ) ? 0 : thickness;

            // Account for reflection at the entrance interface
            if ( SameHemisphere( wo, wi ) )
                f = nSamples * enterInterface.f( wo, wi, mode );

            // Declare _RNG_ for layered BSDF evaluation
            RNG rng( Hash( GetOptions( ).seed, wo ), Hash( wi ) );
            auto r = [ &rng ]( ) 
                {
                    return std::min<Float>( rng.Uniform<Float>( ), OneMinusEpsilon );
                };

            for ( int s = 0; s < nSamples; ++s )
            {
                // Sample random walk through layers to estimate BSDF value
                // Sample transmission direction through entrance interface
                Float uc = r( );
                pstdo::optional<BSDFSample> wos = enterInterface.Sample_f( wo, uc, Point2f( r( ), r( ) ), mode, BxDFReflTransFlags::Transmission );
                if ( !wos || !wos->f.AnyNotEqual( 0.f ) || wos->pdf == 0 || wos->wi.z( ) == 0 )
                {
                    continue;
                }
                // Sample BSDF for virtual light from _wi_
                uc = r( );
                pstdo::optional<BSDFSample> wis = exitInterface.Sample_f( wi, uc, Point2f( r( ), r( ) ), !mode, BxDFReflTransFlags::Transmission );
                if ( !wis || !wis->f.AnyNotEqual( 0.f ) || wis->pdf == 0 || wis->wi.z( ) == 0 )
                {
                    continue;
                }

                // Declare state for random walk through BSDF layers
                SampledSpectrum beta = wos->f * AbsCosTheta( wos->wi ) / wos->pdf;
                Float z = enteredTop ? thickness : 0;
                Vector3f::Simd w = wos->wi;
                auto wz = w.z( );
                HGPhaseFunction phase( g );

                for ( int depth = 0; depth < maxDepth; ++depth )
                {
                    // Sample next event for layered BSDF evaluation random walk
                    PBRT_DBG( "beta: %f %f %f %f, w: %f %f %f, f: %f %f %f %f\n", beta[ 0 ],
                        beta[ 1 ], beta[ 2 ], beta[ 3 ], w.x(), w.y( ), w.z( ), f[ 0 ], f[ 1 ], f[ 2 ],
                        f[ 3 ] );
                    // Possibly terminate layered BSDF random walk with Russian roulette
                    if ( depth > 3 && beta.MaxComponentValue( ) < 0.25f )
                    {
                        Float q = std::max<Float>( 0, 1 - beta.MaxComponentValue( ) );
                        if ( r( ) < q )
                            break;
                        beta /= 1 - q;
                        PBRT_DBG( "After RR with q = %f, beta: %f %f %f %f\n", q, beta[ 0 ],
                            beta[ 1 ], beta[ 2 ], beta[ 3 ] );
                    }

                    // Account for media between layers and possibly scatter
                    if ( !albedo )
                    {
                        // Advance to next layer boundary and update _beta_ for transmittance
                        z = ( z == thickness ) ? 0 : thickness;
                        beta *= Tr( thickness, w );

                    }
                    else
                    {
                        // Sample medium scattering for layered BSDF evaluation
                        Float sigma_t = 1;
                        Float dz = SampleExponential( r( ), sigma_t / std::abs( wz ) );
                        Float zp = wz > 0 ? ( z + dz ) : ( z - dz );
                        NDCHECK_RARE( 1e-5, z == zp );
                        if ( z == zp )
                            continue;
                        if ( 0 < zp && zp < thickness )
                        {
                            // Handle scattering event in layered BSDF medium
                            // Account for scattering through _exitInterface_ using _wis_
                            Float wt = 1;
                            if ( !IsSpecular( exitInterface.Flags( ) ) )
                            {
                                wt = PowerHeuristic( 1, wis->pdf, 1, phase.PDF( -w, -wis->wi ) );
                            }
                            f += beta * albedo * phase.p( -w, -wis->wi ) * wt * Tr( zp - exitZ, wis->wi ) * wis->f / wis->pdf;

                            // Sample phase function and update layered path state
                            Point2f u{ r( ), r( ) };
                            pstdo::optional<PhaseFunctionSample> ps = phase.Sample_p( -w, u );
                            if ( !ps || ps->pdf == 0 || ps->wi.z( ) == 0 )
                            {
                                continue;
                            }
                            beta *= albedo * ps->p / ps->pdf;
                            w = ps->wi;
                            z = zp;

                            // Possibly account for scattering through _exitInterface_
                            if ( ( ( z < exitZ && wz > 0 ) || ( z > exitZ && wz < 0 ) ) &&
                                !IsSpecular( exitInterface.Flags( ) ) )
                            {
                                // Account for scattering through _exitInterface_
                                SampledSpectrum fExit = exitInterface.f( -w, wi, mode );
                                if ( fExit )
                                {
                                    Float exitPDF = exitInterface.PDF(
                                        -w, wi, mode, BxDFReflTransFlags::Transmission );
                                    Float wt = PowerHeuristic( 1, ps->pdf, 1, exitPDF );
                                    f += beta * Tr( zp - exitZ, ps->wi ) * fExit * wt;
                                }
                            }

                            continue;
                        }
                        z = Clamp( zp, 0, thickness );
                    }

                    // Account for scattering at appropriate interface
                    if ( z == exitZ )
                    {
                        // Account for reflection at _exitInterface_
                        Float uc = r( );
                        pstdo::optional<BSDFSample> bs = exitInterface.Sample_f(
                            -w, uc, Point2f( r( ), r( ) ), mode, BxDFReflTransFlags::Reflection );
                        if ( !bs || !bs->f.AnyNotEqual( 0.f ) || bs->pdf == 0 || bs->wi.z( ) == 0 )
                            break;
                        beta *= bs->f * AbsCosTheta( bs->wi ) / bs->pdf;
                        w = bs->wi;

                    }
                    else
                    {
                        // Account for scattering at _nonExitInterface_
                        if ( !IsSpecular( nonExitInterface.Flags( ) ) )
                        {
                            // Add NEE contribution along presampled _wis_ direction
                            Float wt = 1;
                            if ( !IsSpecular( exitInterface.Flags( ) ) )
                                wt = PowerHeuristic( 1, wis->pdf, 1,
                                    nonExitInterface.PDF( -w, -wis->wi, mode ) );
                            f += beta * nonExitInterface.f( -w, -wis->wi, mode ) *
                                AbsCosTheta( wis->wi ) * wt * Tr( thickness, wis->wi ) * wis->f /
                                wis->pdf;
                        }
                        // Sample new direction using BSDF at _nonExitInterface_
                        Float uc = r( );
                        Point2f u( r( ), r( ) );
                        pstdo::optional<BSDFSample> bs = nonExitInterface.Sample_f(
                            -w, uc, u, mode, BxDFReflTransFlags::Reflection );
                        if ( !bs || !bs->f.AnyNotEqual( 0.f ) || bs->pdf == 0 || bs->wi.z() == 0 )
                            break;
                        beta *= bs->f * AbsCosTheta( bs->wi ) / bs->pdf;
                        w = bs->wi;

                        if ( !IsSpecular( exitInterface.Flags( ) ) )
                        {
                            // Add NEE contribution along direction from BSDF sample
                            SampledSpectrum fExit = exitInterface.f( -w, wi, mode );
                            if ( fExit )
                            {
                                Float wt = 1;
                                if ( !IsSpecular( nonExitInterface.Flags( ) ) )
                                {
                                    Float exitPDF = exitInterface.PDF(
                                        -w, wi, mode, BxDFReflTransFlags::Transmission );
                                    wt = PowerHeuristic( 1, bs->pdf, 1, exitPDF );
                                }
                                f += beta * Tr( thickness, bs->wi ) * fExit * wt;
                            }
                        }
                    }
                }
            }

            return f / nSamples;
        }

        pstdo::optional<BSDFSample> Sample_f( Vector3f wo, Float uc, Point2f u, TransportMode mode, BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            NCHECK( sampleFlags == BxDFReflTransFlags::All );  // for now
            // Set _wo_ for layered BSDF sampling
            bool flipWi = false;
            if ( twoSided&& wo.z < 0 )
            {
                wo = -wo;
                flipWi = true;
            }

            // Sample BSDF at entrance interface to get initial direction _w_
            bool enteredTop = twoSided || wo.z > 0;
            pstdo::optional<BSDFSample> bs =
                enteredTop ? top.Sample_f( wo, uc, u, mode ) : bottom.Sample_f( wo, uc, u, mode );
            if ( !bs || !bs->f.AnyNotEqual(0.f) || bs->pdf == 0 || bs->wi.z() == 0 )
                return {};
            if ( bs->IsReflection( ) )
            {
                if ( flipWi )
                    bs->wi = -bs->wi;
                bs->pdfIsProportional = true;
                return bs;
            }
            Vector3f::Simd w = bs->wi;
            auto wz = w.z( );
            bool specularPath = bs->IsSpecular( );

            // Declare _RNG_ for layered BSDF sampling
            RNG rng( Hash( GetOptions( ).seed, wo ), Hash( uc, u ) );
            auto r = [ &rng ]( ) 
                {
                    return std::min<Float>( rng.Uniform<Float>( ), OneMinusEpsilon );
                };

            // Declare common variables for layered BSDF sampling
            SampledSpectrum::Simd f = bs->f * AbsCosTheta( bs->wi );
            Float pdf = bs->pdf;
            Float z = enteredTop ? thickness : 0;
            HGPhaseFunction phase( g );

            for ( int depth = 0; depth < maxDepth; ++depth )
            {
                // Follow random walk through layers to sample layered BSDF
                // Possibly terminate layered BSDF sampling with Russian Roulette
                Float rrBeta = MaxComponentValue( f ) / pdf;
                if ( depth > 3 && rrBeta < 0.25f )
                {
                    Float q = std::max<Float>( 0, 1 - rrBeta );
                    if ( r( ) < q )
                        return {};
                    pdf *= 1 - q;
                }
                if ( wz == 0 )
                    return {};

                if ( albedo )
                {
                    // Sample potential scattering event in layered medium
                    Float sigma_t = 1;
                    Float dz = SampleExponential( r( ), sigma_t / AbsCosTheta( w ) );
                    Float zp = wz > 0 ? ( z + dz ) : ( z - dz );
                    NCHECK_RARE( 1e-5, zp == z );
                    if ( zp == z )
                        return {};
                    if ( 0 < zp && zp < thickness )
                    {
                        // Update path state for valid scattering event between interfaces
                        pstdo::optional<PhaseFunctionSample> ps = phase.Sample_p( -w, Point2f( r( ), r( ) ) );
                        if ( !ps || ps->pdf == 0 || ps->wi.z( ) == 0 )
                            return {};
                        f *= albedo * ps->p;
                        pdf *= ps->pdf;
                        specularPath = false;
                        w = ps->wi;
                        wz = w.z( );
                        z = zp;

                        continue;
                    }
                    z = Clamp( zp, 0, thickness );
                    if ( z == 0 )
                        NDCHECK_LT( wz, 0 );
                    else
                        NDCHECK_GT( wz, 0 );

                }
                else
                {
                    // Advance to the other layer interface
                    z = ( z == thickness ) ? 0 : thickness;
                    f *= Tr( thickness, w );
                }
                // Initialize _interface_ for current interface surface
#ifdef interface  // That's enough out of you, Windows.
#undef interface
#endif
                TopOrBottomBxDF<TopBxDF, BottomBxDF> interface;
                if ( z == 0 )
                    interface = &bottom;
                else
                    interface = &top;

                // Sample interface BSDF to determine new path direction
                Float uc = r( );
                Point2f u( r( ), r( ) );
                pstdo::optional<BSDFSample> bs = interface.Sample_f( -w, uc, u, mode );
                w = bs->wi;
                wz = w.z( );
                if ( !bs || !bs->f.AnyNotEqual( 0.f ) || bs->pdf == 0 || wz == 0 )
                    return {};
                f *= bs->f;
                pdf *= bs->pdf;
                specularPath &= bs->IsSpecular( );
                

                // Return _BSDFSample_ if path has left the layers
                if ( bs->IsTransmission( ) )
                {
                    BxDFFlags flags = SameHemisphere( Vector3f::Simd( wo ), w ) ? BxDFFlags::Reflection
                        : BxDFFlags::Transmission;
                    flags |= specularPath ? BxDFFlags::Specular : BxDFFlags::Glossy;
                    if ( flipWi )
                        w = -w;
                    return BSDFSample( f, w, pdf, flags, 1.f, true );
                }

                // Scale _f_ by cosine term after scattering at the interface
                f *= AbsCosTheta( bs->wi );
            }
            return {};
        }

        PBRT_CPU_GPU
            Float PDF( Vector3f wo, Vector3f wi, TransportMode mode,
                BxDFReflTransFlags sampleFlags = BxDFReflTransFlags::All ) const
        {
            NCHECK( sampleFlags == BxDFReflTransFlags::All );  // for now
            // Set _wo_ and _wi_ for layered BSDF evaluation
            if ( twoSided&& wo.z < 0 )
            {
                wo = -wo;
                wi = -wi;
            }

            // Declare _RNG_ for layered PDF evaluation
            RNG rng( Hash( GetOptions( ).seed, wi ), Hash( wo ) );
            auto r = [ &rng ]( ) {
                return std::min<Float>( rng.Uniform<Float>( ), OneMinusEpsilon );
                };

            // Update _pdfSum_ for reflection at the entrance layer
            bool enteredTop = twoSided || wo.z > 0;
            Float pdfSum = 0;
            if ( SameHemisphere( wo, wi ) )
            {
                auto reflFlag = BxDFReflTransFlags::Reflection;
                pdfSum += enteredTop ? nSamples * top.PDF( wo, wi, mode, reflFlag )
                    : nSamples * bottom.PDF( wo, wi, mode, reflFlag );
            }

            for ( int s = 0; s < nSamples; ++s )
            {
                // Evaluate layered BSDF PDF sample
                if ( SameHemisphere( wo, wi ) )
                {
                    // Evaluate TRT term for PDF estimate
                    TopOrBottomBxDF<TopBxDF, BottomBxDF> rInterface, tInterface;
                    if ( enteredTop )
                    {
                        rInterface = &bottom;
                        tInterface = &top;
                    }
                    else
                    {
                        rInterface = &top;
                        tInterface = &bottom;
                    }
                    // Sample _tInterface_ to get direction into the layers
                    auto trans = BxDFReflTransFlags::Transmission;
                    pstdo::optional<BSDFSample> wos, wis;
                    wos = tInterface.Sample_f( wo, r( ), { r( ), r( ) }, mode, trans );
                    wis = tInterface.Sample_f( wi, r( ), { r( ), r( ) }, !mode, trans );

                    // Update _pdfSum_ accounting for TRT scattering events
                    if ( wos && wos->f.AnyNotEqual(0.f) && wos->pdf > 0 && wis && wis->f.AnyNotEqual(0.f) && wis->pdf > 0 )
                    {
                        if ( !IsNonSpecular( tInterface.Flags( ) ) )
                            pdfSum += rInterface.PDF( -wos->wi, -wis->wi, mode );
                        else
                        {
                            // Use multiple importance sampling to estimate PDF product
                            pstdo::optional<BSDFSample> rs =
                                rInterface.Sample_f( -wos->wi, r( ), { r( ), r( ) }, mode );
                            if ( rs && rs->f.AnyNotEqual(0.f) && rs->pdf > 0 )
                            {
                                if ( !IsNonSpecular( rInterface.Flags( ) ) )
                                    pdfSum += tInterface.PDF( -rs->wi, wi, mode );
                                else
                                {
                                    // Compute MIS-weighted estimate of Equation
                                    // (\ref{eq:pdf-triple-canceled-one})
                                    Float rPDF = rInterface.PDF( -wos->wi, -wis->wi, mode );
                                    Float wt = PowerHeuristic( 1, wis->pdf, 1, rPDF );
                                    pdfSum += wt * rPDF;

                                    Float tPDF = tInterface.PDF( -rs->wi, wi, mode );
                                    wt = PowerHeuristic( 1, rs->pdf, 1, tPDF );
                                    pdfSum += wt * tPDF;
                                }
                            }
                        }
                    }

                }
                else
                {
                    // Evaluate TT term for PDF estimate
                    TopOrBottomBxDF<TopBxDF, BottomBxDF> toInterface, tiInterface;
                    if ( enteredTop )
                    {
                        toInterface = &top;
                        tiInterface = &bottom;
                    }
                    else
                    {
                        toInterface = &bottom;
                        tiInterface = &top;
                    }

                    Float uc = r( );
                    Point2f u( r( ), r( ) );
                    pstdo::optional<BSDFSample> wos = toInterface.Sample_f( wo, uc, u, mode );
                    if ( !wos || !wos->f.AnyNotEqual( 0.f ) || wos->pdf == 0 || wos->wi.z() == 0 ||
                        wos->IsReflection( ) )
                        continue;

                    uc = r( );
                    u = Point2f( r( ), r( ) );
                    pstdo::optional<BSDFSample> wis = tiInterface.Sample_f( wi, uc, u, !mode );
                    if ( !wis || !wis->f.AnyNotEqual(0.f) || wis->pdf == 0 || wis->wi.z( ) == 0 ||
                        wis->IsReflection( ) )
                        continue;

                    if ( IsSpecular( toInterface.Flags( ) ) )
                        pdfSum += tiInterface.PDF( -wos->wi, wi, mode );
                    else if ( IsSpecular( tiInterface.Flags( ) ) )
                        pdfSum += toInterface.PDF( wo, -wis->wi, mode );
                    else
                        pdfSum += ( toInterface.PDF( wo, -wis->wi, mode ) +
                            tiInterface.PDF( -wos->wi, wi, mode ) ) /
                        2;
                }
            }
            // Return mixture of PDF estimate and constant PDF
            return Lerp( 0.9f, 1 / ( 4 * Pi ), pdfSum / nSamples );
        }

    private:
        // LayeredBxDF Private Methods
        PBRT_CPU_GPU
            static Float Tr( Float dz, Vector3f w )
        {
            if ( std::abs( dz ) <= std::numeric_limits<Float>::min( ) )
                return 1;
            return FastExp( -std::abs( dz / w.z ) );
        }

        // LayeredBxDF Private Members
        TopBxDF top;
        BottomBxDF bottom;
        Float thickness, g;
        SampledSpectrum albedo;
        int maxDepth, nSamples;
    };

    // CoatedDiffuseBxDF Definition
    class CoatedDiffuseBxDF : public LayeredBxDF<DielectricBxDF, DiffuseBxDF, true>
    {
    public:
        // CoatedDiffuseBxDF Public Methods
        using LayeredBxDF::LayeredBxDF;
        PBRT_CPU_GPU
            static constexpr const char* Name( ) { return "CoatedDiffuseBxDF"; }
    };

    // CoatedConductorBxDF Definition
    class CoatedConductorBxDF : public LayeredBxDF<DielectricBxDF, ConductorBxDF, true>
    {
    public:
        // CoatedConductorBxDF Public Methods
        PBRT_CPU_GPU
            static constexpr const char* Name( ) { return "CoatedConductorBxDF"; }
        using LayeredBxDF::LayeredBxDF;
    };

    // HairBxDF Definition
    class HairBxDF
    {
    public:
        // HairBxDF Public Methods
        HairBxDF( ) = default;
        PBRT_CPU_GPU
            HairBxDF( Float h, Float eta, const SampledSpectrum& sigma_a, Float beta_m,
                Float beta_n, Float alpha );
        PBRT_CPU_GPU
            SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const;
        PBRT_CPU_GPU
            pstdo::optional<BSDFSample> Sample_f( Vector3f wo, Float uc, Point2f u,
                TransportMode mode,
                BxDFReflTransFlags sampleFlags ) const;
        PBRT_CPU_GPU
            Float PDF( Vector3f wo, Vector3f wi, TransportMode mode,
                BxDFReflTransFlags sampleFlags ) const;

        PBRT_CPU_GPU
            void Regularize( ) {}

        PBRT_CPU_GPU
            static constexpr const char* Name( ) { return "HairBxDF"; }
        std::string ToString( ) const;

        PBRT_CPU_GPU
            BxDFFlags Flags( ) const { return BxDFFlags::GlossyReflection; }

        PBRT_CPU_GPU
            static RGBUnboundedSpectrum SigmaAFromConcentration( Float ce, Float cp );
        PBRT_CPU_GPU
            static SampledSpectrum SigmaAFromReflectance( const SampledSpectrum& c, Float beta_n,
                const SampledWavelengths& lambda );

    private:
        // HairBxDF Constants
        static constexpr int pMax = 3;

        // HairBxDF Private Methods
        PBRT_CPU_GPU static Float Mp( Float cosTheta_i, Float cosTheta_o, Float sinTheta_i,
            Float sinTheta_o, Float v )
        {
            Float a = cosTheta_i * cosTheta_o / v, b = sinTheta_i * sinTheta_o / v;
            Float mp = ( v <= .1 )
                ? ( FastExp( LogI0( a ) - b - 1 / v + 0.6931f + Math::Log( 1 / ( 2 * v ) ) ) )
                : ( FastExp( -b ) * I0( a ) ) / ( std::sinh( 1 / v ) * 2 * v );
            NDCHECK( !IsInf( mp ) && !IsNaN( mp ) );
            return mp;
        }

        PBRT_CPU_GPU static pstdo::array<SampledSpectrum, pMax + 1> Ap( Float cosTheta_o,
            Float eta, Float h,
            SampledSpectrum T )
        {
            pstdo::array<SampledSpectrum, pMax + 1> ap;
            // Compute $p=0$ attenuation at initial cylinder intersection
            Float cosGamma_o = SafeSqrt( 1 - Sqr( h ) );
            Float cosTheta = cosTheta_o * cosGamma_o;
            Float f = FrDielectric( cosTheta, eta );
            ap[ 0 ] = SampledSpectrum( f );

            // Compute $p=1$ attenuation term
            ap[ 1 ] = Sqr( 1 - f ) * T;

            // Compute attenuation terms up to $p=_pMax_$
            for ( int p = 2; p < pMax; ++p )
                ap[ p ] = ap[ p - 1 ] * T * f;

            // Compute attenuation term accounting for remaining orders of scattering
            if ( SampledSpectrum( 1.f - T * f ) )
                ap[ pMax ] = ap[ pMax - 1 ] * f * T / ( 1.f - T * f );

            return ap;
        }

        PBRT_CPU_GPU static inline Float Phi( int p, Float gamma_o, Float gamma_t )
        {
            return 2 * p * gamma_t - 2 * gamma_o + p * Pi;
        }

        PBRT_CPU_GPU static inline Float Np( Float phi, int p, Float s, Float gamma_o,
            Float gamma_t )
        {
            Float dphi = phi - Phi( p, gamma_o, gamma_t );
            // Remap _dphi_ to $[-\pi,\pi]$
            while ( dphi > Pi )
                dphi -= 2 * Pi;
            while ( dphi < -Pi )
                dphi += 2 * Pi;

            return TrimmedLogistic( dphi, s, -Pi, Pi );
        }

        PBRT_CPU_GPU
            pstdo::array<Float, pMax + 1> ApPDF( Float cosTheta_o ) const;

        // HairBxDF Private Members
        Float h, eta;
        SampledSpectrum sigma_a;
        Float beta_m, beta_n;
        Float v[ pMax + 1 ];
        Float s;
        Float sin2kAlpha[ pMax ], cos2kAlpha[ pMax ];
    };

    // MeasuredBxDF Definition
    class MeasuredBxDF
    {
    public:
        // MeasuredBxDF Public Methods
        MeasuredBxDF( ) = default;
        PBRT_CPU_GPU
            MeasuredBxDF( const MeasuredBxDFData* brdf, const SampledWavelengths& lambda )
            : brdf( brdf ), lambda( lambda )
        {
        }

        static MeasuredBxDFData* BRDFDataFromFile( const std::string& filename,
            Allocator alloc );

        PBRT_CPU_GPU
            SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const;

        PBRT_CPU_GPU
            pstdo::optional<BSDFSample> Sample_f( Vector3f wo, Float uc, Point2f u,
                TransportMode mode,
                BxDFReflTransFlags sampleFlags ) const;
        PBRT_CPU_GPU
            Float PDF( Vector3f wo, Vector3f wi, TransportMode mode,
                BxDFReflTransFlags sampleFlags ) const;

        PBRT_CPU_GPU
            void Regularize( ) {}

        PBRT_CPU_GPU
            static constexpr const char* Name( ) { return "MeasuredBxDF"; }

        std::string ToString( ) const;

        PBRT_CPU_GPU
            BxDFFlags Flags( ) const { return ( BxDFFlags::Reflection | BxDFFlags::Glossy ); }

    private:
        // MeasuredBxDF Private Methods
        PBRT_CPU_GPU
            static Float theta2u( Float theta ) { return Math::Sqrt( theta * ( 2 / Pi ) ); }
        PBRT_CPU_GPU
            static Float phi2u( Float phi ) { return phi * ( 1 / ( 2 * Pi ) ) + .5f; }

        PBRT_CPU_GPU
            static Float u2theta( Float u ) { return Sqr( u ) * ( Pi / 2.f ); }
        PBRT_CPU_GPU
            static Float u2phi( Float u ) { return ( 2.f * u - 1.f ) * Pi; }

        // MeasuredBxDF Private Members
        const MeasuredBxDFData* brdf;
        SampledWavelengths lambda;
    };

    // NormalizedFresnelBxDF Definition
    class NormalizedFresnelBxDF
    {
    public:
        // NormalizedFresnelBxDF Public Methods
        NormalizedFresnelBxDF( ) = default;
        PBRT_CPU_GPU
            NormalizedFresnelBxDF( Float eta ) : eta( eta ) {}

        PBRT_CPU_GPU
            BSDFSample Sample_f( Vector3f wo, Float uc, Point2f u, TransportMode mode,
                BxDFReflTransFlags sampleFlags ) const
        {
            if ( !( sampleFlags & BxDFReflTransFlags::Reflection ) )
                return {};

            // Cosine-sample the hemisphere, flipping the direction if necessary
            Vector3f wi = SampleCosineHemisphere( u );
            if ( wo.z < 0 )
                wi.z *= -1;
            return BSDFSample( f( wo, wi, mode ), wi, PDF( wo, wi, mode, sampleFlags ),
                BxDFFlags::DiffuseReflection );
        }

        PBRT_CPU_GPU
            Float PDF( Vector3f wo, Vector3f wi, TransportMode mode,
                BxDFReflTransFlags sampleFlags ) const
        {
            if ( !( sampleFlags & BxDFReflTransFlags::Reflection ) )
                return 0;
            return SameHemisphere( wo, wi ) ? AbsCosTheta( wi ) * InvPi : 0;
        }

        PBRT_CPU_GPU
            void Regularize( ) {}

        PBRT_CPU_GPU
            static constexpr const char* Name( ) { return "NormalizedFresnelBxDF"; }

        std::string ToString( ) const;

        PBRT_CPU_GPU
            BxDFFlags Flags( ) const
        {
            return BxDFFlags( BxDFFlags::Reflection | BxDFFlags::Diffuse );
        }

        PBRT_CPU_GPU
            SampledSpectrum f( Vector3f wo, Vector3f wi, TransportMode mode ) const
        {
            if ( !SameHemisphere( wo, wi ) )
                return SampledSpectrum( 0.f );
            // Compute $\Sw$ factor for BSSRDF value
            Float c = 1 - 2 * FresnelMoment1( 1 / eta );
            SampledSpectrum f( ( 1 - FrDielectric( CosTheta( wi ), eta ) ) / ( c * Pi ) );

            // Update BSSRDF transmission term to account for adjoint light transport
            if ( mode == TransportMode::Radiance )
                f *= Sqr( eta );

            return f;
        }

    private:
        Float eta;
    };

    PBRT_CPU_GPU inline SampledSpectrum BxDF::f( Vector3f wo, Vector3f wi, TransportMode mode ) const
    {
        auto f = [ & ]( auto ptr ) -> SampledSpectrum { return ptr->f( wo, wi, mode ); };
        return Dispatch( f );
    }

    PBRT_CPU_GPU inline pstdo::optional<BSDFSample> BxDF::Sample_f( Vector3f wo, Float uc, Point2f u,
        TransportMode mode,
        BxDFReflTransFlags sampleFlags ) const
    {
        auto sample_f = [ & ]( auto ptr ) -> pstdo::optional<BSDFSample> {
            return ptr->Sample_f( wo, uc, u, mode, sampleFlags );
            };
        return Dispatch( sample_f );
    }

    PBRT_CPU_GPU inline Float BxDF::PDF( Vector3f wo, Vector3f wi, TransportMode mode,
        BxDFReflTransFlags sampleFlags ) const
    {
        auto pdf = [ & ]( auto ptr ) { return ptr->PDF( wo, wi, mode, sampleFlags ); };
        return Dispatch( pdf );
    }

    PBRT_CPU_GPU inline BxDFFlags BxDF::Flags( ) const
    {
        auto flags = [ & ]( auto ptr ) { return ptr->Flags( ); };
        return Dispatch( flags );
    }

    PBRT_CPU_GPU inline void BxDF::Regularize( )
    {
        auto regularize = [ & ]( auto ptr ) { ptr->Regularize( ); };
        return Dispatch( regularize );
    }

    extern template class LayeredBxDF<DielectricBxDF, DiffuseBxDF, true>;
    extern template class LayeredBxDF<DielectricBxDF, ConductorBxDF, true>;

}

#endif
