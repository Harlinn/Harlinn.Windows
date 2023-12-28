# Build instructions
Please note: This solution is for 64-bit builds only.

The provided code has been tried and tested on Windows 11 and Windows 2019 server.
 
## Requirements
To build the solution you need:
- [Visual Studio 17.8.2](https://visualstudio.microsoft.com/vs/) Ensure that you have installed support for .Net 6, 64-bit C++ development and 64-bit python development. 
- [boost c++ libraries](https://www.boost.org/)
- [nasm](https://www.nasm.us/) 
- [yasm](https://yasm.tortall.net/)
- [ICU4C](https://icu.unicode.org/)
- [julia](https://julialang.org/) version 1.9
- [Oracle OCI](https://www.oracle.com/downloads/)
- [Intel® oneAPI Base Toolkit](https://software.intel.com/content/www/us/en/develop/tools/oneapi/base-toolkit/download.html)
- [WinFlexBison - Flex and Bison for Microsoft Windows](https://github.com/lexxmark/winflexbison)
- [swig](http://www.swig.org/)
- [perl](https://www.perl.org/)
- [OpenSSL](https://www.openssl.org/)
- [nVidia CUDA toolkit](https://developer.nvidia.com/cuda-toolkit)

Make sure you install 64-bit binaries, libraries and headers.


Before building you need to set a few environment variables:
- **BOOST_ROOT** must point to the root of your boost C++ installation
- **HCC_TEST_DATA_ROOT** must point to a folder where the 
  test programs can create sub folders used by the test 
  and example programs for the LMDB and ESE databases. 
  Make sure you have about 40GB of available free space 
  for the databases. 
- **ICU4C_HOME** must point to the root of your ICU4C installation
- **JULIA_HOME** must point to the root of your Julia installation.
- **ORACLE_HOME** must point to the root of your Oracle installation.
- **HCC_HOME** must point to the directory containing Harlinn.Windows.sln.
- **PROJ_LIB** must point to ***%HCC_HOME%**\\Share\\proj*
- **GDAL_DATA** must point to ***%HCC_HOME%**\\Share\\gdal*
- **OPENSSL_HOME** must point to the root of your openssl 3.x installation, which is the directory containing the bin, include and lib directories.

The PATH environment variable must be updated to reference:
- **%BOOST_ROOT%**\stage\lib
- **%ICU4C_HOME%**\bin64 
- **%JULIA_HOME%**\bin
- **%ORACLE_HOME%**\bin
- The directory containing yasm.exe
- The directory containing nasm.exe
- The directory containing perl.exe
- The directory containing flex.exe
- The directory containing bison.exe
- The directory containing swig.exe
- The directory containing the MKL redistributable dlls


## Command line for building the boost libraries
After downloading the boost libraries, you need to build boost using the following commands:
```
bootstrap

b2 -j8 address-model=64 threading=multi variant=debug link=shared --build-type=complete cxxstd=latest cflags=/arch:AVX2 cflags=/fsanitize=address cflags=/sdl stage

b2 -j8 address-model=64 threading=multi variant=release link=shared --build-type=complete cxxstd=latest cflags=/arch:AVX2 stage
```
The first invocation of b2 performs a debug build of the boost libraries as dlls with the 
address sanitizer and sdl enabled, while the second performs a dll release build.   

## Make sure x64 is selected in the *Solution Platforms* drop-down in Visual Studio
Make sure you compile for x64 by selecting x64 from the solution platforms drop-down 
in Visual Studio, and if you plan to test the code on a system that does not support 
AVX2, you need to change the **Enable Enhanced Instruction Set** setting under 
**C/C++ ⇒ Code Generation** to a value suitable for your system.
 
## .Net 6.0 support
The [.Net 6.0](https://dotnet.microsoft.com/download/dotnet/6.0) SDK, or newer, is 
required to build the C# code.

## Julia support
If you want to build the Harlinn.Julia library you need to have a 64-bit version of
[Julia](https://julialang.org/) installed on your computer. The **JULIA_HOME** environment
variable must point to the root of your Julia installation.

## Oracle 
### Oracle authentication
You need to manually copy *$(SolutionDir)Tests\Harlinn.OCI.Tests\Harlinn.OCI.Tests.xml** 
into both the *$(SolutionDir)x64\Debug* folder and the *$(SolutionDir)x64\Release* folder.
You also need to edit this file before copying to provide Oracle login information for 
the Harlinn.OCI.Tests project.

### Oracle Call Interface (OCI) support
If you want to build Harlinn.OCI, Harlinn.OCI.Tests and related the examples you need
a 64-bit [Oracle](https://www.oracle.com/database/technologies/oracle19c-windows-downloads.html) 
installation that includes the oracle C based OCI API. The build expects the **ORACLE_HOME** 
environment variable to point to the root of your oracle installation.

Before running the unit tests in Harlinn.OCI.Tests you need to create the tables
defined in *$(SolutionDir)Tests\Harlinn.OCI.Tests\SQL\TestTables.sql* 



