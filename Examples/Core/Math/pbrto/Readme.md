# PBRTO

PBRTO is the main demo/example for my [Fast Linear Algebra Classes for Games and Graphics](https://harlinn.github.io/Cpp/Cpp/Math/FastLinearAlgebra.html).

This app runs my modified version of [pbrt](https://github.com/mmp/pbrt-v4) when 
executed with the `--new` command line option. Without the `--new` option, the app 
executes the original [pbrt](https://github.com/mmp/pbrt-v4) CPU based rendering machinery.

The modified rendering machinery renders [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt) 
91 % faster than the original Visual Studio 2022 build of pbrt.

Rolling the original [pbrt](https://github.com/mmp/pbrt-v4) CPU based rendering machinery, and my modified version of this machinery,
into a single app; makes it easier to verify that my modifications works as expected while exercising functionality provided by
the [Harlinn.Common.Core](https://harlinn.github.io/Cpp/Harlinn.Windows/Harlinn.Common.Core/Harlinn.Common.Core.html) library.

Most of my testing is performed by rendering [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt)
using 4 threads for the rendering:

```
pbrto --new --nthreads 4 --outfile \pbrt\Pbrto1\Kroken\Kroken1.exr \pbrt\pbrt-v4-scenes\kroken\camera-1.pbrt
```
The resulting image contains a significant amount of noise, which is cleaned up by running:

```
imgtool denoise-optix \pbrt\Pbrto1\Kroken\Kroken1.exr --outfile \pbrt\Pbrto1\Kroken\DenoisedKroken1.exr
```
Creating the final result:

<img src="./Images/Kroken1.png" width="640"/>

Building `pbrto.exe`, `Harlinn.pbrto.dll` and `imgtool.exe`, requires that the [CUDA toolkit](https://developer.nvidia.com/cuda-toolkit)
and [OptiX](https://developer.nvidia.com/rtx/ray-tracing/optix) is installed. The projects 
expect that the environment variables:

- `CUDA_PATH` points to your CUDA installation folder.
- `OPTIX_HOME` points to the include folder for [OptiX](https://developer.nvidia.com/rtx/ray-tracing/optix).
- `OPTIX_LIB_DIR` points to the `lib` folder created by the cmake build of [OptiX](https://developer.nvidia.com/rtx/ray-tracing/optix).

Unlike [pbrt](https://github.com/mmp/pbrt-v4), pbrto does not offer the option to render on the GPU, 
[OptiX](https://developer.nvidia.com/rtx/ray-tracing/optix) is only used to implement the `denoise-optix` 
command for `imgtool.exe`.
 
Currently, even minor changes to `HCCMath.h`, `HCCSIMD.h` and `HCCVectorMath.h` tends to have a significant impact on the performance of `pbrto.exe`.

Like changing:

```C++
template<SimdType T>
constexpr typename T::SIMDType ToSimd( const T& v ) noexcept
{
    return v.simd;
}
```
into:

```C++
template<SimdType T>
constexpr typename T::SIMDType& ToSimd( const T& v ) noexcept
{
    return v.simd;
}
```

which may look inconspicuous, but actually increases the time it takes to render [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt)
by more than 10 seconds. 

The effort I've put into `pbrto.exe` and `Harlinn.pbrto.dll` is significant, and it has become
the tool I rely on to really determine when something actually improves the performance of my code or not.
This is why `Math::Exp` is implemented as:

```C++
template<SimdType T>
inline auto Exp( const T& v ) noexcept
{
    using Traits = typename T::Traits;
    using ResultType = Internal::MakeResultType<T>;
    return ResultType( Traits::Exp( v.simd ) );
}
```
and not:
```C++
template<SimdType T>
inline auto Exp( const T& v ) noexcept
{
    using Traits = typename T::Traits;
    using ResultType = Internal::MakeResultType<T>;
    using Tuple = typename T::TupleType;
    if constexpr ( T::Size == 2 )
    {
        Tuple t( v );
        return ResultType( Exp( t.x ), Exp( t.y ) );
    }
    else if constexpr ( T::Size == 3 )
    {
        Tuple t( v );
        return ResultType( Exp( t.x ), Exp( t.y ), Exp( t.z ) );
    }
    else if constexpr ( T::Size == 4 )
    {
        Tuple t( v );
        return ResultType( Exp( t.x ), Exp( t.y ), Exp( t.z ), Exp( t.w ) );
    }
    else
    {
        return ResultType( Traits::Exp( v.simd ) );
    }
}
```

even if the benchmarks:

```
BenchmarkMathVector3fExp                             3.62 ns         3.57 ns    179200000
BenchmarkMathVector3fSimdExp                         10.3 ns         10.5 ns     74666667
```
clearly indicates that the first implementation is significantly slower than the second one,
but using the second implementation slows down the rendering of [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt)
by 13 seconds. I'm fairly certain that the second implementation
will outperform the first in many apps, but for `pbrto` the first is clearly the winner. 

I've performed similar experiments with most of the vectorized math functions in `HCCVectorMath.h`,
and for `pbrto` the current mix of vectorized and scalar implementations seems to be the most 
performant one.

## PBRT

Originally pbrt rendered [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt) in 627.9 seconds using the release build of pbrt, 
built using an unmodified cmake generated Visual Studio 2022 solution.

Changing the build options of the cmake generated Visual Studio 2022 solution by:

- Enabling AVX2 instructions (/arch:AVX2)
- Enabling whole program optimization (/GL)
- any suitable inline expansion (/Ob2)
- No SDL (/sdl-)
- enabling intrinsic functions (/Oi) 
 
improved the performance of pbrt, rendering 
[kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt) in 590.5 seconds.

## PBRTO 

### Without `--new`:

pbrto renders [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt) in 457.3 
seconds without the `--new` command line option, demonstrating the significant performance gains achieved by using
appropriate build options, including `/std:c++latest`. Just switching to the most up-to-date C++ version 
gives a significant boost to the performance of the original code.

### With `--new`:

This executes my modified version of the pbrt CPU based rendering machinery.

With the `--new` command line option pbrto renders [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt)
in 320.8 seconds. 

### Notes about the new rendering machinery.

The new rendering machinery uses my [Fast Linear Algebra Classes for Games and Graphics](https://harlinn.github.io/Cpp/Cpp/Math/FastLinearAlgebra.html), 
showcasing their use, and benefits, when integrated with an existing, high performance, solution.

The new machinery is definitely still [pbrt](https://github.com/mmp/pbrt-v4), my changes are small, and incremental - only a
few classes have been fully reimplemented, while maintaining a high degree of compatibility with their original interface. 

The machinery reimplements the `Transform` class, using a transpose of the 4x4 matrix used by the original `Transform` 
implementation, placing translation fully in the 4<sup>th</sup> row of the matrix, instead of spreading it over 3 rows.

The transposed form is generally easier to work with, enabling efficient SIMD based implementations of 
most of the transformations performed by this class using functions implemented in `HCCVectorMath.h`.

The pbrto implementation of `Vector2<Float>`. `Vector3<Float>`, `Vector2<Int32>`, `Vector3<Int32>`,
`Point2<Float>`, `Point2<Int32>`, `Point3<Float>`, `Point3<Int32>`, `Normal3<Float>`, `Interval`,
`Quaternion`, `SquareMatrix<N>` comes from `HCCVectorMath.h`, with minor adaptations to their use 
inside pbrto.

Most of `SampledSpectrum` and related functions was reimplemented using SIMD::Traits<float,N>, so
`NSpectrumSamples` must be a multiple of 4. Setting `NSpectrumSamples` to 16 or 32 generates error messages 
during rendering, but still improves the quality of the images. 

Calls to most math functions from the standard library have been replaced by calls to their `Harlinn::Common::Core::Math` 
counterparts from `HCCMath.h`. `Math::SinCos` and `Math::Hypot` is used where applicable.

