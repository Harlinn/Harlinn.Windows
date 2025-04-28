# PBRTO

PBRTO is the main demo/example for my [Fast Linear Algebra Classes for Games and Graphics](https://harlinn.github.io/Cpp/Cpp/Math/FastLinearAlgebra.html).

This app runs my modified version of [pbrt](https://github.com/mmp/pbrt-v4) when 
executed with the `--new` command line option. Without the `--new` option the app 
executes the original [pbrt](https://github.com/mmp/pbrt-v4) CPU based rendering machinery, slightly modified to
allow compilation with `/std:c++latest`.

Rolling the original [pbrt](https://github.com/mmp/pbrt-v4) CPU based rendering machinery, and my modified version of this machinery,
into a single app makes it easier to verify that my modifications works as expected while exercising functionality provided by
the [Harlinn.Common.Core](https://harlinn.github.io/Cpp/Harlinn.Windows/Harlinn.Common.Core/Harlinn.Common.Core.html) library.

## PBRT

Most of my testing is performed using [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt), 
which, originally, rendered in 627.9 seconds using the release build of pbrt, 
built using an unmodified cmake generated Visual Studio 2022 solution.

Changing the build options of the cmake generated Visual Studio 2022 solution by:

- enabling AVX2 instructions
- whole program optimization 
- any suitable inline expansion
- No SDL
- enabling intrinsic functions 
 
improved the performance of pbrt, rendering 
[kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt) in 590.5 seconds.

## PBRTO 

pbrto renders [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt) in 478.7 
seconds without the `--new` command line option, demonstrating that significant performance gains can be achieved using
appropriate build options, including `/std:c++latest`.

With the `--new` command line option pbrto renders [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt)
in 379.4 seconds. This executes my modified version of the pbrt CPU based rendering machinery.

Integrating the functionality
provided by [`HCCMath.h`](https://github.com/Harlinn/Harlinn.Windows/blob/master/Harlinn.Common.Core/HCCMath.h) and 
[`HCCVectorMath.h`](https://github.com/Harlinn/Harlinn.Windows/blob/master/Harlinn.Common.Core/HCCVectorMath.h) into
the rendering machinery provided by [pbrt](https://github.com/mmp/pbrt-v4) is a great way to determine how well
my library actually works when it's integrated with an existing code base.