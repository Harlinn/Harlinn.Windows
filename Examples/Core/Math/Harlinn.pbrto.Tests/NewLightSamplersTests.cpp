#include "pch.h"

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

#include <pbrto/util/NewRng.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewColor.h>
#include <pbrto/util/NewColorSpace.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewSpectrum.h>

#include <pbrto/NewInteraction.h>
#include <pbrto/NewLights.h>
#include <pbrto/NewLightSamplers.h>
#include <pbrto/NewShapes.h>


using namespace Harlinn::Common::Core;
using namespace Harlinn::Util::Test;

BOOST_FIXTURE_TEST_SUITE( NewLightSamplersTests, LocalFixture )

// --run_test=NewLightSamplersTests/BVHLightSamplingOneSpotTest1
BOOST_AUTO_TEST_CASE( BVHLightSamplingOneSpotTest1 )
{
    using Float = pbrto::Float;
    using Transform = pbrto::Transform;
    using Light = pbrto::Light;
    using ConstantSpectrum = pbrto::ConstantSpectrum;
    using SpotLight = pbrto::SpotLight;
    using MediumInterface = pbrto::MediumInterface;
    using BVHLightSampler = pbrto::BVHLightSampler;
    using Allocator = pbrto::Allocator;
    using Point2f = pbrto::Point2f;
    using Point3f = pbrto::Point3f;
    using Vector3f = pbrto::Vector3f;
    using Interaction = pbrto::Interaction;
    using Medium = pbrto::Medium;
    using SampledWavelengths = pbrto::SampledWavelengths;
    using LightLiSample = pbrto::LightLiSample;
    using SampledLight = pbrto::SampledLight;

    Transform id;
    std::vector<Light> lights;
    ConstantSpectrum one( 1.f );
    lights.push_back( new SpotLight( id, MediumInterface( ), &one, 1.f /* scale */,
        45.f /* total width */, 44.f /* falloff start */ ) );
    BVHLightSampler distrib( lights, pbrto::Allocator( ) );

    pbrto::RNG rng;
    for ( int i = 0; i < 100; ++i )
    {
        // Random point in [-5, 5]
        Point3f p
        { 
            pbrto::Lerp2( rng.Uniform<Float>( ), -5, 5 ), 
            pbrto::Lerp2( rng.Uniform<Float>( ), -5, 5 ),
            pbrto::Lerp2( rng.Uniform<Float>( ), -5, 5 ) 
        };

        // Avoid possibly ambiguous cases right at the edge.
        Float angle = Math::Rad2Deg( std::acos( Math::Normalize( Vector3f( p ) ).z( ) ) );
        if ( 44.75f < angle && angle < 45.25f )
        {
            --i;
            continue;
        }

        Interaction in( p, 0., ( Medium ) nullptr );
        Point2f u{ rng.Uniform<pbrto::Float>( ), rng.Uniform<pbrto::Float>( ) };
        SampledWavelengths lambda = SampledWavelengths::SampleUniform( 0.5 );
        pstdo::optional<LightLiSample> ls = lights[ 0 ].SampleLi( in, u, lambda );

        pstdo::optional<SampledLight> sampledLight = distrib.Sample( in, rng.Uniform<Float>( ) );

        if ( !sampledLight )
        {
            BOOST_CHECK( false == ( bool )ls );
            continue;
        }
        else
            BOOST_CHECK( ( bool )ls );

        BOOST_CHECK_EQUAL( 1, sampledLight->p );
        BOOST_CHECK( sampledLight->light == lights[ 0 ] );
        BOOST_CHECK( ( bool )ls->L );
    }
}

BOOST_AUTO_TEST_SUITE_END( )