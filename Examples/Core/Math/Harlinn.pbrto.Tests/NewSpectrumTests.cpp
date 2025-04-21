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

BOOST_FIXTURE_TEST_SUITE( NewSpectrumTests, LocalFixture )

// --run_test=NewSpectrumTests/SpectrumBlackbodyTest1
BOOST_AUTO_TEST_CASE( SpectrumBlackbodyTest1 )
{
    using Float = float;
    // Relative error.
    auto err = []( Float val, Float ref ) { return std::abs( val - ref ) / ref; };

    // Planck's law.
    // A few values via
    // http://www.spectralcalc.com/blackbody_calculator/blackbody.php
    // lambda, T, expected radiance
    Float v[ ][ 3 ] = {
        {483, 6000, 3.1849e13},
        {600, 6000, 2.86772e13},
        {500, 3700, 1.59845e12},
        {600, 4500, 7.46497e12},
    };
    int n = PBRT_ARRAYSIZE( v );
    for ( int i = 0; i < n; ++i )
    {
        Float lambda = v[ i ][ 0 ], T = v[ i ][ 1 ], LeExpected = v[ i ][ 2 ];
        BOOST_CHECK_LT( err( pbrto::Blackbody( lambda, T ), LeExpected ), .001 );
    }

    // Use Wien's displacement law to compute maximum wavelength for a few
    // temperatures, then confirm that the value returned by Blackbody() is
    // consistent with this.
    for ( Float T : {2700, 3000, 4500, 5600, 6000} )
    {
        Float lambdaMax = 2.8977721e-3 / T * 1e9;
        Float lambda[ 3 ] = { Float( .99 * lambdaMax ), lambdaMax, Float( 1.01 * lambdaMax ) };
        BOOST_CHECK_LT( pbrto::Blackbody( lambda[ 0 ], T ), pbrto::Blackbody( lambda[ 1 ], T ) );
        BOOST_CHECK_GT( pbrto::Blackbody( lambda[ 1 ], T ), pbrto::Blackbody( lambda[ 2 ], T ) );
    }
}

// --run_test=NewSpectrumTests/SpectrumXYZTest1
BOOST_AUTO_TEST_CASE( SpectrumXYZTest1 )
{
    using Float = float;
    {
        // Make sure the integral of all matching function sample values is
        // basically one in x, y, and z.
        Float xx = 0, yy = 0, zz = 0;
        for ( Float lambda = 360; lambda < 831; ++lambda )
        {
            xx += pbrto::Spectra::X( )( lambda );
            yy += pbrto::Spectra::Y( )( lambda );
            zz += pbrto::Spectra::Z( )( lambda );
        }
        static constexpr Float CIE_Y_integral = 106.856895;
        xx /= CIE_Y_integral;
        yy /= CIE_Y_integral;
        zz /= CIE_Y_integral;
        BOOST_CHECK_LT( std::abs( 1 - xx ), .005 );
        BOOST_CHECK_LT( std::abs( 1 - yy ), .005 );
        BOOST_CHECK_LT( std::abs( 1 - zz ), .005 );
    }
    {
        // Make sure the xyz of a constant spectrum are basically one.
        std::array<Float, 3> xyzSum = { 0 };
        int n = 100;
        for ( Float u : pbrto::Stratified1D( n ) )
        {
            pbrto::SampledWavelengths lambda = pbrto::SampledWavelengths::SampleUniform( u, 360, 830 );
            pbrto::XYZ xyz = pbrto::SampledSpectrum( 1. ).ToXYZ( lambda );
            for ( int c = 0; c < 3; ++c )
                xyzSum[ c ] += xyz[ c ];
        }
        for ( int c = 0; c < 3; ++c )
            xyzSum[ c ] /= n;

        BOOST_CHECK_LT( std::abs( 1 - xyzSum[ 0 ] ), .035 );
        BOOST_CHECK_LT( std::abs( 1 - xyzSum[ 1 ] ), .035 );
        BOOST_CHECK_LT( std::abs( 1 - xyzSum[ 2 ] ), .035 );
    }
}

// --run_test=NewSpectrumTests/SpectrumMaxValueTest1
BOOST_AUTO_TEST_CASE( SpectrumMaxValueTest1 )
{
    using Float = float;
    BOOST_CHECK_EQUAL( 2.5, pbrto::ConstantSpectrum( 2.5 ).MaxValue( ) );

    BOOST_CHECK_EQUAL( Float( 10.1 ),
        pbrto::PiecewiseLinearSpectrum(
            { Float( 300 ), Float( 380 ), Float( 510 ), Float( 662 ), Float( 700 ) },
            { Float( 1.5 ), Float( 2.6 ), Float( 10.1 ), Float( 5.3 ), Float( 7.7 ) } )
        .MaxValue( ) );

    BOOST_CHECK_GT( pbrto::BlackbodySpectrum( 5000 ).MaxValue( ), .9999 );
    BOOST_CHECK_LT( pbrto::BlackbodySpectrum( 5000 ).MaxValue( ), 1.0001 );

    pbrto::BlackbodySpectrum bb( 5000 );
    BOOST_CHECK_GT( pbrto::DenselySampledSpectrum( &bb ).MaxValue( ), .9999 );
    BOOST_CHECK_LT( pbrto::DenselySampledSpectrum( &bb ).MaxValue( ), 1.0001 );

    pbrto::RNG rng;
    for ( int i = 0; i < 20; ++i )
    {
        pbrto::RGB rgb( rng.Uniform<Float>( ), rng.Uniform<Float>( ), rng.Uniform<Float>( ) );
        pbrto::RGBAlbedoSpectrum sr( *pbrto::RGBColorSpace::sRGB, rgb );
        Float m = sr.MaxValue( ) * 1.00001f;
        for ( Float lambda = 360; lambda < 830; lambda += .92 )
            BOOST_CHECK_LE( sr( lambda ), m );

        pbrto::RGBUnboundedSpectrum su( *pbrto::RGBColorSpace::sRGB, 10 * rgb );
        m = su.MaxValue( ) * 1.00001f;
        for ( Float lambda = 360; lambda < 830; lambda += .92 )
            BOOST_CHECK_LE( su( lambda ), m );

        pbrto::RGBIlluminantSpectrum si( *pbrto::RGBColorSpace::sRGB, rgb );
        m = si.MaxValue( ) * 1.00001f;
        for ( Float lambda = 360; lambda < 830; lambda += .92 )
            BOOST_CHECK_LE( si( lambda ), m );
    }
}

// --run_test=NewSpectrumTests/SpectrumSamplingPdfYTest1
BOOST_AUTO_TEST_CASE( SpectrumSamplingPdfYTest1 )
{
    using Float = float;
    // Make sure we can integrate the y matching curve correctly
    Float ysum = 0;
    int n = 1000;
    for ( Float u : pbrto::Stratified1D( n ) )
    {
        Float lambda = pbrto::SampleVisibleWavelengths( u );
        Float pdf = pbrto::VisibleWavelengthsPDF( lambda );
        if ( pdf > 0 )
            ysum += pbrto::Spectra::Y( )( lambda ) / pdf;
    }
    Float yint = ysum / n;

    BOOST_CHECK_LT( std::abs( ( yint - pbrto::CIE_Y_integral ) / pbrto::CIE_Y_integral ), 1e-3 );
}

// --run_test=NewSpectrumTests/SpectrumSamplingPdfXYZTest1
BOOST_AUTO_TEST_CASE( SpectrumSamplingPdfXYZTest1 )
{
    using Float = float;
    // Make sure we can integrate the sum of the x+y+z matching curves correctly
    Float impSum = 0, unifSum = 0;
    int n = 10000;
    for ( Float u : pbrto::Stratified1D( n ) )
    {
        {
            // Uniform
            Float lambda = pbrto::Lerp2( u, pbrto::Lambda_min, pbrto::Lambda_max );
            Float pdf = 1. / ( pbrto::Lambda_max - pbrto::Lambda_min );
            unifSum +=
                ( pbrto::Spectra::X( )( lambda ) + pbrto::Spectra::Y( )( lambda ) + pbrto::Spectra::Z( )( lambda ) ) /
                pdf;
        }

        Float lambda = pbrto::SampleVisibleWavelengths( u );
        Float pdf = pbrto::VisibleWavelengthsPDF( lambda );
        if ( pdf > 0 )
            impSum +=
            ( pbrto::Spectra::X( )( lambda ) + pbrto::Spectra::Y( )( lambda ) + pbrto::Spectra::Z( )( lambda ) ) /
            pdf;
    }
    Float impInt = impSum / n, unifInt = unifSum / n;

    BOOST_CHECK_LT( std::abs( ( impInt - unifInt ) / unifInt ), 1e-3 );
}

BOOST_AUTO_TEST_SUITE_END( )