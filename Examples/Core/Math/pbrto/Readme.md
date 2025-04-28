# PBRTO

This app runs my modified version of [pbrt](https://github.com/mmp/pbrt-v4) when 
executed with the `--new` command line option. Without the `--new` option the app 
executes the original [pbrt](https://github.com/mmp/pbrt-v4) CPU based rendering machinery, slightly modified to
allow compilation with `/std:c++latest`.

Most of my testing is performed using [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt), 
which, originally, rendered in 627.9 seconds using the release version of pbrt 
built using a cmake generated Visual Studio 2022 solution.

Changing the build options of the cmake generated Visual Studio 2022 solution by enabling AVX2 instructions, whole program 
optimization, any suitable inline expansion and intrinsic functions - improves the performance of pbrt, rendering 
[kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt) in 590.5 seconds.



pbrto renders [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt) in 478.7 
seconds without the `--new` command line option, demonstrating that significant performance gains can be achieved using
appropriate build options, including `/std:c++latest`.


With the `--new` command line option pbrto renders [kroken/camera-1.pbrt](https://github.com/mmp/pbrt-v4-scenes/blob/master/kroken/camera-1.pbrt)
in 379.4 seconds. This executes a modified version of the pbrt CPU based rendering machinery leveraging the functionality
provided by [`HCCMath.h`](https://github.com/Harlinn/Harlinn.Windows/blob/master/Harlinn.Common.Core/HCCMath.h) and 
[`HCCVectorMath.h`](https://github.com/Harlinn/Harlinn.Windows/blob/master/Harlinn.Common.Core/HCCVectorMath.h).

Rolling the original [pbrt](https://github.com/mmp/pbrt-v4) CPU based rendering machinery, and my modified version of the machinery,
into a single app makes it easier to verify that my modifications works as expected while exercising functionality provided by
my [Harlinn.Common.Core](https://harlinn.github.io/Cpp/Harlinn.Windows/Harlinn.Common.Core/Harlinn.Common.Core.html) library.  
