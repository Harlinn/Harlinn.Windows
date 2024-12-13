/*
   Copyright 2024 Espen Harlinn

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

#include "BenchmarkUtils.h"
#include <pbrto/util/vecmath.h>

#ifdef RUN_SQUAREMATRIX_BENCHMARKS
namespace
{
    RandomGenerator<double, SampleCount> DoubleGenerator;
    RandomGenerator<float, SampleCount> FloatGenerator;
    RandomGenerator<double, SampleCount> DoubleAngleInDegreesGenerator( 0.0, 360.0 );
    RandomGenerator<float, SampleCount> FloatAngleInDegreesGenerator( 0.0f, 360.0f );
    RandomGenerator<double, SampleCount> DoubleAngleInRadiansGenerator( 0.0, M_PI * 2 );
    RandomGenerator<float, SampleCount> FloatAngleInRadiansGenerator( 0.0f, ( float )M_PI * 2 );

    RandomGenerator<double, SampleCount> DoubleZeroToOneGenerator( 0.0, 1.0 );
    RandomGenerator<float, SampleCount> FloatZeroToOneGenerator( 0.0f, 1.0f );

    RandomGenerator<double, SampleCount> DoubleMinusOneToOneGenerator( -1.0, 1.0 );
    RandomGenerator<float, SampleCount> FloatMinusOneToOneGenerator( -1.0f, 1.0f );
}

static void BenchmarkPbrtSquareMatrixAdd( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 + matrix2 );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrixAdd );

static void BenchmarkSquareMatrixAdd( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 + matrix2 );
    }
}
BENCHMARK( BenchmarkSquareMatrixAdd );

static void BenchmarkSquareMatrixSub( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 - matrix2 );
    }
}
BENCHMARK( BenchmarkSquareMatrixSub );

static void BenchmarkPbrtSquareMatrixScalarMultiply( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        auto value = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 * value );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrixScalarMultiply );

static void BenchmarkSquareMatrixScalarMultiply( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        auto value = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 * value );
    }
}
BENCHMARK( BenchmarkSquareMatrixScalarMultiply );

static void BenchmarkPbrtSquareMatrixMultiply( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( (matrix1 * matrix2) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrixMultiply );

static void BenchmarkSquareMatrixMultiply( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( ( matrix1 * matrix2 ) );
    }
}
BENCHMARK( BenchmarkSquareMatrixMultiply );

static void BenchmarkPbrtSquareMatrixDeterminant( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( pbrt::Determinant( matrix1 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrixDeterminant );

static void BenchmarkXMMatrixDeterminant( benchmark::State& state )
{
    using namespace DirectX;
    FloatGenerator.Reset( );

    XMFLOAT4X4 matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1._11 = FloatGenerator( );

        auto loadedMatrix = XMLoadFloat4x4( &matrix1 );

        benchmark::DoNotOptimize( XMMatrixDeterminant( loadedMatrix ) );
    }
}
BENCHMARK( BenchmarkXMMatrixDeterminant );

static void BenchmarkSquareMatrixDeterminant( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( Determinant( matrix1 ) );
    }
}
BENCHMARK( BenchmarkSquareMatrixDeterminant );

static void BenchmarkPbrtSquareMatrixInverse( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( pbrt::Inverse( matrix1 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrixInverse ); 

static void BenchmarkXMMatrixInverse( benchmark::State& state )
{
    using namespace DirectX;
    FloatGenerator.Reset( );

    XMFLOAT4X4 matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1._11 = FloatGenerator( );
        auto loadedMatrix = XMLoadFloat4x4( &matrix1 );

        benchmark::DoNotOptimize( XMMatrixInverse( nullptr, loadedMatrix ) );
    }
}
BENCHMARK( BenchmarkXMMatrixInverse );


static void BenchmarkSquareMatrixInverse( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 4>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( Inverse( matrix1.ToSimd() ) );
    }
}
BENCHMARK( BenchmarkSquareMatrixInverse );


#endif