#include "pch.h"

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

#include <pbrto/util/NewRng.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewColor.h>
#include <pbrto/util/NewColorSpace.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewSpectrum.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Util::Test;

using Float = pbrto::Float;

BOOST_FIXTURE_TEST_SUITE( NewColorTests, LocalFixture )

// --run_test=NewColorTests/RGBColorSpaceRGBXYZTest1
BOOST_AUTO_TEST_CASE( RGBColorSpaceRGBXYZTest1 )
{
    for ( const pbrto::RGBColorSpace& cs :
        { *pbrto::RGBColorSpace::ACES2065_1, *pbrto::RGBColorSpace::Rec2020, *pbrto::RGBColorSpace::sRGB } )
    {
        pbrto::XYZ xyz = cs.ToXYZ( { 1, 1, 1 } );
        pbrto::RGB rgb = cs.ToRGB( xyz );
        BOOST_CHECK_LT( std::abs( 1 - rgb[ 0 ] ), 1e-4 );
        BOOST_CHECK_LT( std::abs( 1 - rgb[ 1 ] ), 1e-4 );
        BOOST_CHECK_LT( std::abs( 1 - rgb[ 2 ] ), 1e-4 );
    }
}

// --run_test=NewColorTests/RGBColorSpacesRGBTest1
BOOST_AUTO_TEST_CASE( RGBColorSpacesRGBTest1 )
{
    const pbrto::RGBColorSpace& sRGB = *pbrto::RGBColorSpace::sRGB;

    // Make sure the matrix values are sensible by throwing the x, y, and z
    // basis vectors at it to pull out columns.
    pbrto::RGB rgb = sRGB.ToRGB( { 1, 0, 0 } );
    BOOST_CHECK_LT( std::abs( 3.2406 - rgb[ 0 ] ), 1e-3 );
    BOOST_CHECK_LT( std::abs( -.9689 - rgb[ 1 ] ), 1e-3 );
    BOOST_CHECK_LT( std::abs( .0557 - rgb[ 2 ] ), 1e-3 );

    rgb = sRGB.ToRGB( { 0, 1, 0 } );
    BOOST_CHECK_LT( std::abs( -1.5372 - rgb[ 0 ] ), 1e-3 );
    BOOST_CHECK_LT( std::abs( 1.8758 - rgb[ 1 ] ), 1e-3 );
    BOOST_CHECK_LT( std::abs( -.2040 - rgb[ 2 ] ), 1e-3 );

    rgb = sRGB.ToRGB( { 0, 0, 1 } );
    BOOST_CHECK_LT( std::abs( -.4986 - rgb[ 0 ] ), 1e-3 );
    BOOST_CHECK_LT( std::abs( .0415 - rgb[ 1 ] ), 1e-3 );
    BOOST_CHECK_LT( std::abs( 1.0570 - rgb[ 2 ] ), 1e-3 );
}

// --run_test=NewColorTests/RGBColorSpaceStdIllumWhitesRGBTest1
BOOST_AUTO_TEST_CASE( RGBColorSpaceStdIllumWhitesRGBTest1 )
{
    pbrto::XYZ xyz = pbrto::SpectrumToXYZ( &pbrto::RGBColorSpace::sRGB->illuminant );
    pbrto::RGB rgb = pbrto::RGBColorSpace::sRGB->ToRGB( xyz );
    BOOST_CHECK_GE( rgb.r, .99 );
    BOOST_CHECK_LE( rgb.r, 1.01 );
    BOOST_CHECK_GE( rgb.g, .99 );
    BOOST_CHECK_LE( rgb.g, 1.01 );
    BOOST_CHECK_GE( rgb.b, .99 );
    BOOST_CHECK_LE( rgb.b, 1.01 );
}

// --run_test=NewColorTests/RGBColorSpaceStdIllumWhiteRec2020Test1
BOOST_AUTO_TEST_CASE( RGBColorSpaceStdIllumWhiteRec2020Test1 )
{
    pbrto::XYZ xyz = pbrto::SpectrumToXYZ( &pbrto::RGBColorSpace::Rec2020->illuminant );
    pbrto::RGB rgb = pbrto::RGBColorSpace::Rec2020->ToRGB( xyz );
    BOOST_CHECK_GE( rgb.r, .99 );
    BOOST_CHECK_LE( rgb.r, 1.01 );
    BOOST_CHECK_GE( rgb.g, .99 );
    BOOST_CHECK_LE( rgb.g, 1.01 );
    BOOST_CHECK_GE( rgb.b, .99 );
    BOOST_CHECK_LE( rgb.b, 1.01 );
}

// --run_test=NewColorTests/RGBColorSpaceStdIllumWhiteACES2065_1Test1
BOOST_AUTO_TEST_CASE( RGBColorSpaceStdIllumWhiteACES2065_1Test1 )
{
    pbrto::XYZ xyz = pbrto::SpectrumToXYZ( &pbrto::RGBColorSpace::ACES2065_1->illuminant );
    pbrto::RGB rgb = pbrto::RGBColorSpace::ACES2065_1->ToRGB( xyz );
    BOOST_CHECK_GE( rgb.r, .99 );
    BOOST_CHECK_LE( rgb.r, 1.01 );
    BOOST_CHECK_GE( rgb.g, .99 );
    BOOST_CHECK_LE( rgb.g, 1.01 );
    BOOST_CHECK_GE( rgb.b, .99 );
    BOOST_CHECK_LE( rgb.b, 1.01 );
}


// --run_test=NewColorTests/RGBUnboundedSpectrumMaxValueTest1
BOOST_AUTO_TEST_CASE( RGBUnboundedSpectrumMaxValueTest1 )
{
    pbrto::RNG rng;
    for ( const auto& cs : { *pbrto::RGBColorSpace::sRGB, *pbrto::RGBColorSpace::Rec2020, *pbrto::RGBColorSpace::ACES2065_1 } )
    {
        for ( int i = 0; i < 100; ++i )
        {
            pbrto::RGB rgb( rng.Uniform<Float>( ), rng.Uniform<Float>( ), rng.Uniform<Float>( ) );
            rgb *= 10.f;
            pbrto::RGBUnboundedSpectrum rs( cs, rgb );

            pbrto::Float m = rs.MaxValue( );
            pbrto::Float sm = 0;
            for ( pbrto::Float lambda = 360; lambda <= 830; lambda += 1. / 16. )
                sm = std::max( sm, rs( lambda ) );
            BOOST_CHECK_LT( std::abs( ( sm - m ) / sm ), 1e-4 );
        }
    }
}

// --run_test=NewColorTests/RGBAlbedoSpectrumMaxValueTest1
BOOST_AUTO_TEST_CASE( RGBAlbedoSpectrumMaxValueTest1 )
{
    pbrto::RNG rng;
    for ( const auto& cs :
        { *pbrto::RGBColorSpace::sRGB, *pbrto::RGBColorSpace::Rec2020, *pbrto::RGBColorSpace::ACES2065_1 } )
    {
        for ( int i = 0; i < 100; ++i )
        {
            pbrto::RGB rgb( rng.Uniform<Float>( ), rng.Uniform<Float>( ), rng.Uniform<Float>( ) );
            pbrto::RGBAlbedoSpectrum rs( cs, rgb );

            Float m = rs.MaxValue( );
            Float sm = 0;
            for ( Float lambda = 360; lambda <= 830; lambda += 1. / 16. )
                sm = std::max( sm, rs( lambda ) );
            BOOST_CHECK_LT( std::abs( ( sm - m ) / sm ), 1e-4 );
        }
    }
}

// --run_test=NewColorTests/RGBAlbedoSpectrumRoundTripsRGBTest1
BOOST_AUTO_TEST_CASE( RGBAlbedoSpectrumRoundTripsRGBTest1 )
{
    pbrto::RNG rng;
    const pbrto::RGBColorSpace& cs = *pbrto::RGBColorSpace::sRGB;

    for ( int i = 0; i < 100; ++i )
    {
        pbrto::RGB rgb( rng.Uniform<Float>( ), rng.Uniform<Float>( ), rng.Uniform<Float>( ) );
        pbrto::RGBAlbedoSpectrum rs( cs, rgb );

        pbrto::DenselySampledSpectrum rsIllum = pbrto::DenselySampledSpectrum::SampleFunction( [ & ]( Float lambda ) { return rs( lambda ) * cs.illuminant( lambda ); } );
        pbrto::XYZ xyz = SpectrumToXYZ( &rsIllum );
        pbrto::RGB rgb2 = cs.ToRGB( xyz );

        // Some error comes from the fact that piecewise linear (at 5nm)
        // CIE curves were used for the optimization while we use piecewise
        // linear at 1nm spacing converted to 1nm constant / densely
        // sampled.
        Float eps = .01;
        BOOST_CHECK_LT( std::abs( rgb.r - rgb2.r ), eps );
        BOOST_CHECK_LT( std::abs( rgb.g - rgb2.g ), eps );
        BOOST_CHECK_LT( std::abs( rgb.b - rgb2.b ), eps );
    }
}

// --run_test=NewColorTests/RGBAlbedoSpectrumRoundTripRec2020Test1
BOOST_AUTO_TEST_CASE( RGBAlbedoSpectrumRoundTripRec2020Test1 )
{
    pbrto::RNG rng;
    const pbrto::RGBColorSpace& cs = *pbrto::RGBColorSpace::Rec2020;

    for ( int i = 0; i < 100; ++i )
    {
        pbrto::RGB rgb( .1 + .7 * rng.Uniform<Float>( ), .1 + .7 * rng.Uniform<Float>( ), .1 + .7 * rng.Uniform<Float>( ) );
        pbrto::RGBAlbedoSpectrum rs( cs, rgb );

        pbrto::DenselySampledSpectrum rsIllum = pbrto::DenselySampledSpectrum::SampleFunction( [ & ]( Float lambda ) { return rs( lambda ) * cs.illuminant( lambda ); } );
        pbrto::XYZ xyz = SpectrumToXYZ( &rsIllum );
        pbrto::RGB rgb2 = cs.ToRGB( xyz );

        Float eps = .01;
        BOOST_CHECK_LT( std::abs( rgb.r - rgb2.r ), eps );
        BOOST_CHECK_LT( std::abs( rgb.g - rgb2.g ), eps );
        BOOST_CHECK_LT( std::abs( rgb.b - rgb2.b ), eps );
    }
}

// --run_test=NewColorTests/RGBAlbedoSpectrumRoundTripACESTest1
BOOST_AUTO_TEST_CASE( RGBAlbedoSpectrumRoundTripACESTest1 )
{
    pbrto::RNG rng;
    const pbrto::RGBColorSpace& cs = *pbrto::RGBColorSpace::ACES2065_1;

    for ( int i = 0; i < 100; ++i )
    {
        pbrto::RGB rgb( .3 + .4 * rng.Uniform<Float>( ), .3 + .4 * rng.Uniform<Float>( ), .3 + .4 * rng.Uniform<Float>( ) );
        pbrto::RGBAlbedoSpectrum rs( cs, rgb );

        pbrto::DenselySampledSpectrum rsIllum = pbrto::DenselySampledSpectrum::SampleFunction( [ & ]( Float lambda ) { return rs( lambda ) * cs.illuminant( lambda ); } );
        pbrto::XYZ xyz = SpectrumToXYZ( &rsIllum );
        pbrto::RGB rgb2 = cs.ToRGB( xyz );

        Float eps = .01;
        BOOST_CHECK_LT( std::abs( rgb.r - rgb2.r ), eps );
        BOOST_CHECK_LT( std::abs( rgb.g - rgb2.g ), eps );
        BOOST_CHECK_LT( std::abs( rgb.b - rgb2.b ), eps );
    }
}

// --run_test=NewColorTests/RGBIlluminantSpectrumRoundTripsRGBTest1
BOOST_AUTO_TEST_CASE( RGBIlluminantSpectrumRoundTripsRGBTest1 )
{
    pbrto::RNG rng;
    const pbrto::RGBColorSpace& cs = *pbrto::RGBColorSpace::sRGB;

    for ( int i = 0; i < 100; ++i )
    {
        pbrto::RGB rgb( rng.Uniform<Float>( ), rng.Uniform<Float>( ), rng.Uniform<Float>( ) );
        pbrto::RGBIlluminantSpectrum rs( cs, rgb );

        pbrto::DenselySampledSpectrum rsIllum = pbrto::DenselySampledSpectrum::SampleFunction([ & ]( Float lambda ) { return rs( lambda ); } );
        pbrto::XYZ xyz = SpectrumToXYZ( &rsIllum );
        pbrto::RGB rgb2 = cs.ToRGB( xyz );

        // Some error comes from the fact that piecewise linear (at 5nm)
        // CIE curves were used for the optimization while we use piecewise
        // linear at 1nm spacing converted to 1nm constant / densely
        // sampled.
        Float eps = .01;
        BOOST_CHECK_LT( std::abs( rgb.r - rgb2.r ), eps );
        BOOST_CHECK_LT( std::abs( rgb.g - rgb2.g ), eps );
        BOOST_CHECK_LT( std::abs( rgb.b - rgb2.b ), eps );
    }
}

// --run_test=NewColorTests/RGBIlluminantSpectrumRoundTripRec2020Test1
BOOST_AUTO_TEST_CASE( RGBIlluminantSpectrumRoundTripRec2020Test1 )
{
    pbrto::RNG rng;
    const pbrto::RGBColorSpace& cs = *pbrto::RGBColorSpace::Rec2020;

    for ( int i = 0; i < 100; ++i )
    {
        pbrto::RGB rgb( .1 + .7 * rng.Uniform<Float>( ), .1 + .7 * rng.Uniform<Float>( ), .1 + .7 * rng.Uniform<Float>( ) );
        pbrto::RGBIlluminantSpectrum rs( cs, rgb );

        pbrto::DenselySampledSpectrum rsIllum = pbrto::DenselySampledSpectrum::SampleFunction( [ & ]( Float lambda ) { return rs( lambda ); } );
        pbrto::XYZ xyz = pbrto::SpectrumToXYZ( &rsIllum );
        pbrto::RGB rgb2 = cs.ToRGB( xyz );

        Float eps = .01;
        BOOST_CHECK_LT( std::abs( rgb.r - rgb2.r ), eps );
        BOOST_CHECK_LT( std::abs( rgb.g - rgb2.g ), eps );
        BOOST_CHECK_LT( std::abs( rgb.b - rgb2.b ), eps );
    }
}

// --run_test=NewColorTests/RGBIlluminantSpectrumRoundTripACESTest1
BOOST_AUTO_TEST_CASE( RGBIlluminantSpectrumRoundTripACESTest1 )
{
    pbrto::RNG rng;
    const pbrto::RGBColorSpace& cs = *pbrto::RGBColorSpace::ACES2065_1;

    for ( int i = 0; i < 100; ++i )
    {
        pbrto::RGB rgb( .3 + .4 * rng.Uniform<Float>( ), .3 + .4 * rng.Uniform<Float>( ), .3 + .4 * rng.Uniform<Float>( ) );
        pbrto::RGBIlluminantSpectrum rs( cs, rgb );

        pbrto::DenselySampledSpectrum rsIllum = pbrto::DenselySampledSpectrum::SampleFunction( [ & ]( Float lambda ) { return rs( lambda ); } );
        pbrto::XYZ xyz = pbrto::SpectrumToXYZ( &rsIllum );
        pbrto::RGB rgb2 = cs.ToRGB( xyz );

        Float eps = .01;
        BOOST_CHECK_LT( std::abs( rgb.r - rgb2.r ), eps );
        BOOST_CHECK_LT( std::abs( rgb.g - rgb2.g ), eps );
        BOOST_CHECK_LT( std::abs( rgb.b - rgb2.b ), eps );
    }
}

// --run_test=NewColorTests/sRGBConversionTest1
BOOST_AUTO_TEST_CASE( sRGBConversionTest1 )
{
    
    // Check the basic 8 bit values
    for ( int i = 0; i < 256; ++i )
    {
        Float x = pbrto::SRGBToLinear( i * ( 1.f / 255.f ) );
        Float y = pbrto::SRGB8ToLinear( i );
        BOOST_CHECK_LT( std::abs( x - y ), 1e-5 );
    }

    // Round trip to linear and back
    for ( int i = 0; i < 256; ++i )
    {
        Float x = pbrto::SRGBToLinear( i * ( 1.f / 255.f ) );
        Float y = pbrto::LinearToSRGB( x ) * 255.f;
        BOOST_CHECK_LT( std::abs( i - y ), 1e-4 );
    }

    // Round trip the other way
    for ( int i = 0; i < 256; ++i )
    {
        Float x = pbrto::LinearToSRGB( i * ( 1.f / 255.f ) );
        Float y = pbrto::SRGBToLinear( x ) * 255.f;
        BOOST_CHECK_LT( std::abs( i - y ), 3e-4 );
    }
}


BOOST_AUTO_TEST_SUITE_END( )