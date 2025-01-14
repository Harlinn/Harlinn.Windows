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

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix4x4Add( benchmark::State& state )
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
BENCHMARK( BenchmarkPbrtSquareMatrix4x4Add );
#endif

static void BenchmarkSquareMatrix4x4Add( benchmark::State& state )
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
BENCHMARK( BenchmarkSquareMatrix4x4Add );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix3x3Add( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), 
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), 
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 + matrix2 );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix3x3Add );
#endif

static void BenchmarkSquareMatrix3x3Add( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 + matrix2 );
    }
}
BENCHMARK( BenchmarkSquareMatrix3x3Add );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix2x2Add( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ));
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 + matrix2 );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix2x2Add );
#endif

static void BenchmarkSquareMatrix2x2Add( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 + matrix2 );
    }
}
BENCHMARK( BenchmarkSquareMatrix2x2Add );


static void BenchmarkSquareMatrix4x4Sub( benchmark::State& state )
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
BENCHMARK( BenchmarkSquareMatrix4x4Sub );

static void BenchmarkSquareMatrix3x3Sub( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 - matrix2 );
    }
}
BENCHMARK( BenchmarkSquareMatrix3x3Sub );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix4x4Transpose( benchmark::State& state )
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

        benchmark::DoNotOptimize( pbrt::Transpose( matrix1 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix4x4Transpose );
#endif

static void BenchmarkSquareMatrix4x4Transpose( benchmark::State& state )
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

        benchmark::DoNotOptimize( Transpose( matrix1 ) );
    }
}
BENCHMARK( BenchmarkSquareMatrix4x4Transpose );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix3x3Transpose( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( pbrt::Transpose( matrix1 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix3x3Transpose );
#endif

static void BenchmarkSquareMatrix3x3Transpose( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), 
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), 
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( Transpose( matrix1 ) );
    }
}
BENCHMARK( BenchmarkSquareMatrix3x3Transpose );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix2x2Transpose( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( pbrt::Transpose( matrix1 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix2x2Transpose );
#endif

static void BenchmarkSquareMatrix2x2Transpose( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( Transpose( matrix1 ) );
    }
}
BENCHMARK( BenchmarkSquareMatrix2x2Transpose );



#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix4x4ScalarMultiply( benchmark::State& state )
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
BENCHMARK( BenchmarkPbrtSquareMatrix4x4ScalarMultiply );
#endif

static void BenchmarkSquareMatrix4x4ScalarMultiply( benchmark::State& state )
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
BENCHMARK( BenchmarkSquareMatrix4x4ScalarMultiply );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix3x3ScalarMultiply( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        auto value = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 * value );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix3x3ScalarMultiply );
#endif

static void BenchmarkSquareMatrix3x3ScalarMultiply( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        auto value = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 * value );
    }
}
BENCHMARK( BenchmarkSquareMatrix3x3ScalarMultiply );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix2x2ScalarMultiply( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        auto value = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 * value );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix2x2ScalarMultiply );
#endif

static void BenchmarkSquareMatrix2x2ScalarMultiply( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        auto value = FloatGenerator( );

        benchmark::DoNotOptimize( matrix1 * value );
    }
}
BENCHMARK( BenchmarkSquareMatrix2x2ScalarMultiply );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix4x4Multiply( benchmark::State& state )
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
BENCHMARK( BenchmarkPbrtSquareMatrix4x4Multiply );
#endif

static void BenchmarkSquareMatrix4x4Multiply( benchmark::State& state )
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
BENCHMARK( BenchmarkSquareMatrix4x4Multiply );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix3x3Multiply( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), 
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( ( matrix1 * matrix2 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix3x3Multiply );
#endif

static void BenchmarkSquareMatrix3x3Multiply( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( ( matrix1 * matrix2 ) );
    }
}
BENCHMARK( BenchmarkSquareMatrix3x3Multiply );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix2x2Multiply( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ));
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( ( matrix1 * matrix2 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix2x2Multiply );
#endif

static void BenchmarkSquareMatrix2x2Multiply( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );
    Matrix matrix2( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );
        matrix2[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( ( matrix1 * matrix2 ) );
    }
}
BENCHMARK( BenchmarkSquareMatrix2x2Multiply );


#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix4x4Determinant( benchmark::State& state )
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
BENCHMARK( BenchmarkPbrtSquareMatrix4x4Determinant );
#endif

static void BenchmarkXMMatrix4x4Determinant( benchmark::State& state )
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
BENCHMARK( BenchmarkXMMatrix4x4Determinant );

static void BenchmarkSquareMatrix4x4Determinant( benchmark::State& state )
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
BENCHMARK( BenchmarkSquareMatrix4x4Determinant );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix3x3Determinant( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), 
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), 
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( pbrt::Determinant( matrix1 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix3x3Determinant );
#endif

static void BenchmarkSquareMatrix3x3Determinant( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( Determinant( matrix1 ) );
    }
}
BENCHMARK( BenchmarkSquareMatrix3x3Determinant );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix2x2Determinant( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( pbrt::Determinant( matrix1 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix2x2Determinant );
#endif

static void BenchmarkSquareMatrix2x2Determinant( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( Determinant( matrix1 ) );
    }
}
BENCHMARK( BenchmarkSquareMatrix2x2Determinant );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix4x4Inverse( benchmark::State& state )
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
BENCHMARK( BenchmarkPbrtSquareMatrix4x4Inverse );
#endif

static void BenchmarkXMMatrix4x4Inverse( benchmark::State& state )
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
BENCHMARK( BenchmarkXMMatrix4x4Inverse );


static void BenchmarkSquareMatrix4x4Inverse( benchmark::State& state )
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
BENCHMARK( BenchmarkSquareMatrix4x4Inverse );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix3x3Inverse( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( pbrt::Inverse( matrix1 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix3x3Inverse );
#endif
static void BenchmarkSquareMatrix3x3Inverse( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 3>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( Inverse( matrix1.ToSimd( ) ) );
    }
}
BENCHMARK( BenchmarkSquareMatrix3x3Inverse );

#ifdef RUN_PBRT_BENCHMARKS
static void BenchmarkPbrtSquareMatrix2x2Inverse( benchmark::State& state )
{
    using Matrix = pbrt::SquareMatrix<2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( pbrt::Inverse( matrix1 ) );
    }
}
BENCHMARK( BenchmarkPbrtSquareMatrix2x2Inverse );
#endif

static void BenchmarkSquareMatrix2x2Inverse( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Matrix = Math::SquareMatrix<float, 2>;
    FloatGenerator.Reset( );

    Matrix matrix1( FloatGenerator( ), FloatGenerator( ),
        FloatGenerator( ), FloatGenerator( ) );

    for ( auto _ : state )
    {
        matrix1[ 0 ][ 0 ] = FloatGenerator( );

        benchmark::DoNotOptimize( Inverse( matrix1.ToSimd( ) ) );
    }
}
BENCHMARK( BenchmarkSquareMatrix2x2Inverse );





#endif