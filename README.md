# Harlinn.Windows

This repository contains a Visual Studio Solution currently containing 575 projects.

Most of the projects are open source projects that I have found useful at work, and a few are my own.

* [Overview](./Readme/Overview.md)
* [Build instructions](./Readme/Build.md)


## 3rd party libraries
This solution contains many useful C and C++ libraries that are located under the 3rdParty folder.

Header only libraries are contained within ''Static library (.lib)'' or shared files projects, everything else creates a dll.

All C++ code compiles using [/std:c++latest](https://docs.microsoft.com/en-us/cpp/build/reference/std-specify-language-standard-version?view=msvc-170) and [/Zc:__cplusplus](https://docs.microsoft.com/en-us/cpp/build/reference/zc-cplusplus?view=msvc-170)

### [abseil](https://abseil.io/)
**Version:** 20230125.3

**Description:**
> Abseil is an open source collection of C++ libraries drawn from the most fundamental pieces of Google’s 
> internal code-base. These libraries are the nuts-and-bolts that underpin almost everything Google runs. 
> Bits and pieces of these APIs are embedded in most of our open source projects, and Abseil aims to bring 
> them together into one comprehensive project. Abseil encompasses the most basic building blocks of Google’s 
> code-base: code that is production-tested and will be fully maintained for years to come.

**Projects:** 
- Harlinn.abseil
- Tests\\3rdParty\\abseil\\abseil_test

The abseil_test contains the unit tests for the Harlinn.abseil project

### [libaec - Adaptive Entropy Coding library](https://github.com/erget/libaec)
**Version:** master as of 2021.08.26

**Description:**
> Libaec provides fast lossless compression of 1 up to 32 bit wide signed or unsigned integers (samples). 

**Project:** Harlinn.aec



### [Alliance for Open Media - AV1 Codec Library](https://aomedia.googlesource.com/aom)
**Version:** 3.1.2 

**Description:**
> AV1 Codec Library

**Project:** Harlinn.aom


### [Armadillo: C++ Library for Linear Algebra & Scientific Computing](http://arma.sourceforge.net)
**Version:** 10.6.x

**Description:**
> Armadillo is a high quality linear algebra library (matrix maths) for the C++ language, aiming towards a good balance between speed and ease of use
>  
> Provides high-level syntax and functionality deliberately similar to Matlab
>  
> Useful for algorithm development directly in C++, or quick conversion of research code into production environments
>  
> Provides efficient classes for vectors, matrices and cubes; dense and sparse matrices are supported
>  
> Integer, floating point and complex numbers are supported
>  
> A sophisticated expression evaluator (based on template meta-programming) automatically combines several operations to increase speed and efficiency
>  
> Various matrix decompositions (eigen, SVD, QR, etc) are provided through integration with LAPACK, or one of its high performance drop-in replacements (eg. MKL or OpenBLAS)
>  
> Can automatically use OpenMP multi-threading (parallelisation) to speed up computationally expensive operations
>  
> Distributed under the permissive Apache 2.0 license, useful for both open-source and proprietary (closed-source) software
>  
> Can be used for machine learning, pattern recognition, computer vision, signal processing, bioinformatics, statistics, finance, etc

**Project:** Harlinn.armadillo

### [Open Asset Import Library (assimp)](https://github.com/assimp/assimp)
**Version:** 5.2.5

**Description:**
> Open Asset Import Library is a library to load various 3d file formats into a 
> shared, in-memory format. It supports more than 40 file formats for import and 
> a growing selection of file formats for export.

**Project:** Harlinn.assimp


### [cpp-base64](https://github.com/ReneNyffenegger/cpp-base64)
**Version:** 2.0.rc8

**Description:**
> Base64 encoding and decoding with c++.

**Project:** Harlinn.base64

### [binlog](https://github.com/morganstanley/binlog)
**Version:** master/head as of 7th. of October 2023.

**Description:**
> A high performance C++ log library to produce structured binary logs.

**Project:** Harlinn.Binlog


### [BoringSSL](https://boringssl.googlesource.com/boringssl/)
**Version:** master as of 2021.09.20

**Description:**
> BoringSSL is a fork of OpenSSL that is designed to meet Google's needs.

**Projects:** 
- Harlinn.boringssl
- Tests\\3rdParty\\boringssl\\crypto_test
- Tests\\3rdParty\\boringssl\\ssl_test

### [Brotli](https://github.com/google/brotli)
**Version:** master as of 2021.08.04

**Description:**
> Brotli is a generic-purpose lossless compression algorithm that compresses data using a combination of a modern variant 
> of the LZ77 algorithm, Huffman coding and 2nd order context modeling, with a compression ratio comparable to the best 
> currently available general-purpose compression methods. It is similar in speed with deflate but offers more dense compression.

**Project:** Harlinn.brotli

### [Bullet Physics SDK](https://github.com/bulletphysics/bullet3)
**Version:** 3.21

**Description:**
> Real-time collision detection and multi-physics simulation for VR, games, visual effects, robotics, machine learning etc.

**Project:** Harlinn.bullet

### [Inverse Kinematics](http://www.math.ucsd.edu/~sbuss/ResearchWeb/ikmethods/index.html)
**Version:** from bullet 3.21

**Description:**
> Selectively Damped Least Squares for Inverse Kinematics.

**Project:** Harlinn.BussIK

### [bzip2](https://gitlab.com/bzip2/bzip2/)
**Version:** 1.0.8

**Description:**
> bzip2 is a freely available, patent free (see below), high-quality data compressor. It typically 
> compresses files to within 10% to 15% of the best available techniques (the PPM family of statistical 
> compressors), whilst being around twice as fast at compression and six times faster at decompression.

**Project:** Harlinn.bzip2

### [c-ares is a C library for asynchronous DNS requests (including name resolves)](https://c-ares.org/)
**Version:** 1.17.0

**Description:**
> c-ares is a C library for asynchronous DNS requests (including name resolves)

**Project:** Harlinn.c-ares

### [CFITSIO - A FITS File Subroutine Library](https://heasarc.gsfc.nasa.gov/fitsio/)
**Version:** 4.0.0

**Description:**
> CFITSIO is a library of C and Fortran subroutines for reading and writing data files in FITS 
> (Flexible Image Transport System) data format. CFITSIO provides simple high-level routines for 
> reading and writing FITS files that insulate the programmer from the internal complexities of 
> the FITS format. CFITSIO also provides many advanced features for manipulating and filtering 
> the information in FITS files.

**Project:** Harlinn.cfitsio

### [Advanced DXTn texture compression library](https://github.com/BinomialLLC/crunch)
**Version:** 1.04

**Description:**
> crnlib is a lossy texture compression library for developers that ship content using the DXT1/5/N 
> or 3DC compressed color/normal map/cubemap mipmapped texture formats.
>
> It can compress mipmapped 2D textures, normal maps, and cubemaps to approx. 1-1.25 bits/texel, and 
> normal maps to 1.75-2 bits/texel. The actual bitrate depends on the complexity of the texture itself, 
> the specified quality factor/target bitrate, and ultimately on the desired quality needed for a 
> particular texture.

**Project:** Harlinn.crnlib

### [clsocket](https://github.com/DFHack/clsocket)
**Version:** 1.41.1

**Description:**
> Provides a mechanism for writing cross platform socket code. This library was originally written 
> to only support blocking TCP sockets. Over the years it has been extended to support UDP and RAW 
> sockets as well.

**Project:** Harlinn.clsocket

### [crossguid](https://github.com/graeme-hill/crossguid)
**Version:** 0.2.2

**Description:**
> CrossGuid is a minimal, cross platform, C++ GUID library. It uses the best native GUID/UUID generator 
> on the given platform and has a generic class for parsing, stringifying, and comparing IDs. The guid 
> generation technique is determined by your platform.

**Project:** Harlinn.crossguid

### [libcurl - the multiprotocol file transfer library](https://curl.se/libcurl/)
**Version:** 7.78.0

**Description:**
> libcurl is a free and easy-to-use client-side URL transfer library, supporting DICT, FILE, FTP, FTPS, 
> GOPHER, GOPHERS, HTTP, HTTPS, IMAP, IMAPS, LDAP, LDAPS, MQTT, POP3, POP3S, RTMP, RTMPS, RTSP, SCP, 
> SFTP, SMB, SMBS, SMTP, SMTPS, TELNET and TFTP. libcurl supports SSL certificates, HTTP POST, HTTP PUT, 
> FTP uploading, HTTP form based upload, proxies, HTTP/2, HTTP/3, cookies, user+password authentication 
> (Basic, Digest, NTLM, Negotiate, Kerberos), file transfer resume, http proxy tunneling and more!

**Project:** Harlinn.curl

### [D3D12 Memory Allocator](https://github.com/GPUOpen-LibrariesAndSDKs/D3D12MemoryAllocator)
**Version:** 2.0.0-development (2021-07-26)

**Description:**
> Easy to integrate memory allocation library for Direct3D 12

**Project:** Harlinn.d3d12allocator

### [libdeflate](https://github.com/ebiggers/libdeflate)
**Version:** 1.8

**Description:**
> libdeflate is a library for fast, whole-buffer DEFLATE-based compression and decompression

**Project:** Harlinn.deflate

### [DirectXMesh geometry processing library](https://github.com/microsoft/DirectXMesh)
**Version:** June 2023

**Description:**
> This package contains DirectXMesh, a shared source library for performing various 
> geometry content processing operations including generating normals and tangent frames, 
> triangle adjacency computations, vertex cache optimization, and meshlet generation.

**Project:** Harlinn.DirectXMesh

### [DirectXTex texture processing library](https://github.com/microsoft/DirectXTex)
**Version:** June 2023

**Description:**
> This package contains DirectXTex, a shared source library for reading and writing .DDS files, 
> and performing various texture content processing operations including resizing, format 
> conversion, mip-map generation, block compression for Direct3D runtime texture resources, and 
> height-map to normal-map conversion. This library makes use of the Windows Image Component (WIC) 
> APIs. It also includes .TGA and .HDR readers and writers since these image file formats are commonly 
> used for texture content processing pipelines, but are not currently supported by a built-in WIC codec.

**Project:** Harlinn.DirectXTex


### [Adobe Digital Negative (DNG) SDK](https://helpx.adobe.com/camera-raw/digital-negative.html)
**Version:** 1.5.1

**Description:**
> The DNG SDK provides support for reading and writing DNG files as well as for converting DNG 
> data to a format that is easily displayed or processed by imaging applications.

**Project:** Harlinn.dngsdk

### [Effcee](https://github.com/google/effcee)
**Version:** main as of 2021.09.27

**Description:**
> Effcee is a C++ library for stateful pattern matching of strings, inspired by LLVM's FileCheck command.

**Project:** Harlinn.effcee

### [Eigen](https://eigen.tuxfamily.org/)
**Version:** 3.4.0

**Description:**
> Eigen is a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.

**Project:** Harlinn.Eigen

### [ENet](https://github.com/lsalzman/enet)
**Version:** 1.3.17

**Description:**
> ENet's purpose is to provide a relatively thin, simple and robust network communication layer on top of UDP 
> (User Datagram Protocol).The primary feature it provides is optional reliable, in-order delivery of packets.

**Project:** Harlinn.enet


### [Expat](https://github.com/libexpat/libexpat)
**Version:** 2.4.1

**Description:**
> This is Expat, a C library for parsing XML, started by James Clark in 1997. Expat is a stream-oriented 
> XML parser. This means that you register handlers with the parser before starting the parse. These 
> handlers are called when the parser discovers the associated structures in the document being parsed. 
> A start tag is an example of the kind of structures for which you may register handlers.

**Project:** Harlinn.expat

### [FlatBuffers](https://google.github.io/flatbuffers/)
**Version:** 2.0.0

**Description:**
> FlatBuffers is an efficient cross platform serialization library for C++, 
> C#, C, Go, Java, Kotlin, JavaScript, Lobster, Lua, TypeScript, PHP, Python, 
> Rust and Swift. It was originally created at Google for game development 
> and other performance-critical applications.

**Project:** Harlinn.flatbuffers


### [Freetype](https://freetype.org/)
**Version:** 2.11.0

**Description:**
> FreeType is a freely available software library to render fonts.
> 
> It is written in C, designed to be small, efficient, highly customizable, and portable while capable of 
> producing high-quality output (glyph images) of most vector and bitmap font formats.

**Project:** Harlinn.freetype

### [GDAL - Geospatial Data Abstraction Library](https://gdal.org/)
**Version:** 3.4.0

**Description:**
> GDAL is a translator library for raster and vector geospatial data formats that is released under an 
> X/MIT style Open Source License by the Open Source Geospatial Foundation. As a library, it presents a 
> single raster abstract data model and single vector abstract data model to the calling application for 
> all supported formats.

**Project:** Harlinn.gdal

### [GeographicLib](https://github.com/geographiclib/geographiclib)
**Version:** 2.2

**Description:**
> GeographicLib is a small C++ library for 
> * geodesic and rhumb line calculations;
> * conversions between geographic, UTM, UPS, MGRS, geocentric, and local cartesian coordinates;
> * gravity (e.g., EGM2008) and geomagnetic field (e.g., WMM2020) calculations.

**Project:** Harlinn.geographiclib


### [GEOS - coordinate transformation software library](https://libgeos.org/)
**Version:** 3.10.0dev

**Description:**
> GEOS is a C/C++ library for spatial computational geometry of the sort generally used by “geographic information systems” software.

**Project:** Harlinn.geos

### [Google gflags](https://github.com/gflags/gflags)
**Version:** 2.2.2

**Description:**
> Gflags, the commandline flags library used within Google, differs from other libraries, 
> such as getopt(), in that flag definitions can be scattered around the source code, and 
> not just listed in one place such as main(). In practice, this means that a single source-code 
> file will define and use flags that are meaningful to that file. Any application that links 
> in that file will get the flags, and the gflags library will automatically handle that 
> flag appropriately.
> 
> There's significant gain in flexibility, and ease of code reuse, due to this technique.

**Project:** Harlinn.gflags

### [Giflib](https://sourceforge.net/projects/giflib/)
**Version:** 5.2.1

**Description:**
> giflib is a library for reading and writing gif images.

**Project:** Harlinn.gif

### [Glad](https://glad.dav1d.de/)
**Version:** generated by glad 0.1.35 on Sun Dec 26 15:01:04 2021

**Description:**
> GLSC2, OpenGL, OpenGL ES loader generated by glad 0.1.35 on Sun Dec 26 15:01:04 2021
> using the [Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs](https://glad.dav1d.de/).

**Project:** Harlinn.glad


### [GLFW - multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop](https://www.glfw.org/)
**Version:** 3.3.4 

**Description:**
> GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on 
> the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving 
> input and events.

**Project:** Harlinn.glfw

### [gRPC](https://grpc.io/)
**Version:** 1.41.1 

**Description:**
> gRPC is a modern open source high performance Remote Procedure Call (RPC) framework that can run 
> in any environment. It can efficiently connect services in and across data centers with pluggable 
> support for load balancing, tracing, health checking and authentication. It is also applicable in 
> last mile of distributed computing to connect devices, mobile applications and browsers to backend 
> services.

**Projects:**
- Harlinn.grpc
- Harlinn.grpc-compiler
- Tools\\3rdParty\\grpc\\gen_hpack_tables
- Tools\\3rdParty\\grpc\\grpc_cpp_plugin
- Tools\\3rdParty\\grpc\\grpc_csharp_plugin
- Tools\\3rdParty\\grpc\\grpc_node_plugin
- Tools\\3rdParty\\grpc\\grpc_objective_c_plugin
- Tools\\3rdParty\\grpc\\grpc_php_plugin
- Tools\\3rdParty\\grpc\\grpc_python_plugin
- Tools\\3rdParty\\grpc\\grpc_ruby_plugin
- Tests\\3rdParty\\gRPC\\core\address_utils\\grpc_test_core_address_utils_parse_address_test
- Tests\\3rdParty\\gRPC\\core\address_utils\\grpc_test_core_address_utils_parse_address_with_named_scope_id_test
- Tests\\3rdParty\\gRPC\\core\address_utils\\grpc_test_core_address_utils_sockaddr_utils_test
- Tests\\3rdParty\\gRPC\\core\avl\\grpc_test_avl_avl_test
- Tests\\3rdParty\\gRPC\\core\backoff\\grpc_test_backoff_backoff_test
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_badreq
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_bad_streaming_id
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_connection_prefix
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_duplicate_header
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_headers
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_head_of_line_blocking
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_initial_settings_frame
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_large_metadata
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_out_of_bounds
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_server_registered_method
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_simple_request
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_unknown_frame
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_window_overflow
- Tests\\3rdParty\\gRPC\\core\bad_connection\\grpc_test_bad_connection_close_fd_test
- Tests\\3rdParty\\gRPC\\core\bad_ssl\\grpc_test_bad_ssl_alpn_server_test
- Tests\\3rdParty\\gRPC\\core\bad_ssl\\grpc_test_bad_ssl_bad_ssl_test
- Tests\\3rdParty\\gRPC\\core\bad_ssl\\grpc_test_bad_ssl_cert_server_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_channel_channel_args_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_channel_channel_stack_builder_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_channel_channel_stack_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_channel_channel_trace_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_core_channelz_registry_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_core_channelz_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_core_channel_status_util_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_core_minimal_stack_is_minimal_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\grpc_test_core_client_channel_certificate_provider_registry_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\grpc_test_core_client_channel_retry_throttle_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\grpc_test_core_client_channel_service_config_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\resolvers\dns_resolver_connectivity_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\resolvers\dns_resolver_cooldown_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\resolvers\grpc_test_dns_resolver_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\resolvers\grpc_test_fake_resolver_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\resolvers\grpc_test_sockaddr_resolver_test
- Tests\\3rdParty\\gRPC\\core\compression\\grpc_test_core_compression_algorithm_test
- Tests\\3rdParty\\gRPC\\core\compression\\grpc_test_core_compression_compression_test
- Tests\\3rdParty\\gRPC\\core\compression\\grpc_test_core_compression_message_compress_test
- Tests\\3rdParty\\gRPC\\core\compression\\grpc_test_core_compression_stream_compression_test
- Tests\\3rdParty\\gRPC\\core\config\\grpc_test_core_config_core_configuration_test
- Tests\\3rdParty\\gRPC\\core\debug\\grpc_test_core_debug_stats_test
- Tests\\3rdParty\\gRPC\\core\event_engine\\grpc_test_core_event_engine_endpoint_config_test
- Tests\\3rdParty\\gRPC\\core\fling\\fling_client
- Tests\\3rdParty\\gRPC\\core\fling\\fling_server
- Tests\\3rdParty\\gRPC\\core\fling\\grpc_test_core_fling_fling_stream_test
- Tests\\3rdParty\\gRPC\\core\fling\\grpc_test_core_fling_fling_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_alloc_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_arena_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_cpu_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_env_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_log_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_murmur_hash_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_spinlock_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_string_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_sync_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_time_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_tls_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_useful_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_bitset_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_capture_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_dual_ref_counted_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_examine_stack_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_fork_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_global_config_env_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_global_config_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_host_port_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_manual_constructor_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_match_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_mpscq_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_orphanable_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_overload_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_ref_counted_ptr_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_ref_counted_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_status_helper_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_stat_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_table_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_thd_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_time_util_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_combiner_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_endpoint_pair_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_error_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_grpc_ipv6_loopback_available_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_load_file_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_mpmcqueue_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_pollset_windows_starvation_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_resolve_address_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_resource_quota_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_threadpool_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_timer_heap_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_timer_list_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_time_averaged_stats_test
- Tests\\3rdParty\\gRPC\\grpc_test_core_util


### [libgta - Generic Tagged Arrays](https://marlam.de/gta/)
**Version:** 1.2.1

**Description:**
> Libgta, a library that reads and writes GTA files.

**Project:** Harlinn.gta

### [GoogleTest](https://github.com/google/googletest)
**Version:** 1.13.0

**Description:**
> GoogleTest is Google’s C++ testing and mocking framework.

**Project:** Harlinn.gtest

### [gwen](https://github.com/garrynewman/GWEN)
**Version:** from bullet 3.21

**Description:**
> a C++ GUI library

**Project:** Harlinn.gwen

### [HarfBuzz, a text shaping library](https://github.com/harfbuzz/harfbuzz)
**Version:** 3.0.0

**Description:**
> HarfBuzz is a text shaping library. Using the HarfBuzz library allows programs to convert a sequence 
> of Unicode input into properly formatted and positioned glyph output—for any writing system and language.

**Project:** Harlinn.harfbuzz

### [HDF](https://github.com/HDFGroup/hdf4)
**Version:** 4.2.15 

**Description:**
> The Hierarchical Data Format, or HDF, is a multiobject file format for sharing scientific 
> data in a distributed environment. HDF was created at the National Center for Supercomputing 
> Applications, and is now developed and maintained by The HDF Group, to serve the needs of 
> diverse groups of scientists working on projects in various fields

**Project:** Harlinn.hdf4

### [HDF5](https://github.com/HDFGroup/hdf5)
**Version:** 1.12.1

**Description:**
> The HDF Group is the developer of HDF5®, a high-performance software library and data format 
> that has been adopted across multiple industries and has become a de facto standard in scientific 
> and research communities.

**Project:** Harlinn.hdf5

### [Highway](https://github.com/google/highway)
**Version:** 0.14.2

**Description:**
> Highway is a C++ library for SIMD (Single Instruction, Multiple Data), i.e. applying the same 
> operation to multiple 'lanes' using a single CPU instruction.

**Project:** Harlinn.highway

### [Imath](https://github.com/AcademySoftwareFoundation/Imath)
**Version:** master as of 2021.08.18

**Description:**
> Imath is a basic, light-weight, and efficient C++ representation of 2D and 3D vectors and 
> matrices and other simple but useful mathematical objects, functions, and data types common 
> in computer graphics applications, including the “half” 16-bit floating-point type.

**Project:** Harlinn.imath

### [Dear ImGui](https://github.com/ocornut/imgui) and [ImPlot](https://github.com/epezent/implot)
**Dear ImGui Version:** 1.89.7
**ImPlot Version:** 0.15

**Description:**
Packages Dear ImGui and ImPlot as a single dll. 

**Description 'Dear ImGui':**
> Dear ImGui is a bloat-free graphical user interface library for C++. It outputs optimized 
> vertex buffers that you can render anytime in your 3D-pipeline enabled application.

**Description 'ImPlot':**
> ImPlot is an immediate mode, GPU accelerated plotting library for Dear ImGui. It aims to 
> provide a first-class API that ImGui fans will love. ImPlot is well suited for visualizing 
> program data in real-time or creating interactive plots, and requires minimal code to integrate.

**Project:** Harlinn.ImGui

### [JasPer Image Processing/Coding Tool Kit](https://github.com/jasper-software/jasper)
**Version:** 2.0.33

**Description:**
> JasPer Image Processing/Coding Tool Kit

**Project:** Harlinn.jasper

### [The Independent JPEG Group's JPEG software](https://www.ijg.org)
**Version:** 9d

**Description:**
> IJG is an informal group that writes and distributes a widely used free library for JPEG image compression.

**Project:** Harlinn.jpeg

### [libjpeg-turbo](http://libjpeg-turbo.org)
**Version:** 2.1.1

**Description:**
> libjpeg-turbo is a JPEG image codec that uses SIMD instructions (MMX, SSE2, AVX2, Neon, AltiVec) to accelerate 
> baseline JPEG compression and decompression on x86, x86-64, Arm, and PowerPC systems, as well as progressive 
> JPEG compression on x86 and x86-64 systems. On such systems, libjpeg-turbo is generally 2-6x as fast as libjpeg, 
> all else being equal. On other types of systems, libjpeg-turbo can still outperform libjpeg by a significant 
> amount, by virtue of its highly-optimized Huffman coding routines. In many cases, the performance of 
> libjpeg-turbo rivals that of proprietary high-speed JPEG codecs.
>
> libjpeg-turbo implements both the traditional libjpeg API as well as the less powerful but more straightforward 
> TurboJPEG API. libjpeg-turbo also features colorspace extensions that allow it to compress from/decompress to 
> 32-bit and big-endian pixel buffers (RGBX, XBGR, etc.), as well as a full-featured Java interface.

**Project:** Harlinn.jpeg-turbo

### [JSON-C - A JSON implementation in C](https://github.com/json-c/json-c)
**Version:** master as of 2021.08.01 

**Description:**
> A JSON implementation in C.

**Project:** Harlinn.json-c

### [JsonCpp](https://github.com/open-source-parsers/jsoncpp)
**Version:** 1.9.4

**Description:**
> JsonCpp is a C++ library that allows manipulating JSON values, including serialization and deserialization 
> to and from strings. It can also preserve existing comment in unserialization/serialization steps, making 
> it a convenient format to store user input files.

**Project:** Harlinn.jsoncpp

### [JPEG XL reference implementation](https://github.com/libjxl/libjxl)
**Version:** 0.5

**Description:**
> A reference implementation of JPEG XL (encoder and decoder), called libjxl.

**Project:** Harlinn.jxl

### [kml](https://github.com/libkml/libkml)
**Version:** 1.3.0

**Description:**
> This is Google's reference implementation of OGC KML 2.2. 

**Projects:**
- Harlinn.kmlbase
- Harlinn.kmlconvenience
- Harlinn.kmldom
- Harlinn.kmlengine
- Harlinn.kmlregionator
- Harlinn.kmlxsd

### [Little CMS](https://github.com/mm2/Little-CMS)
**Version:** 2.12

**Description:**
> Little CMS intends to be an OPEN SOURCE small-footprint color management engine, 
> with special focus on accuracy and performance. It uses the International Color 
> Consortium standard (ICC), which is the modern standard when regarding to color 
> management. The ICC specification is widely used and is referred to in many 
> International and other de-facto standards. It was approved as an International 
> Standard, ISO 15076-1, in 2005.

**Project:** Harlinn.lcms2

### [LERC - Limited Error Raster Compression](https://github.com/Esri/lerc)
**Version:** 3.0

**Description:**
> LERC is an open-source image or raster format which supports rapid encoding and 
> decoding for any pixel type (not just RGB or Byte).

**Project:** Harlinn.Lerc

### [libde265 - open h.265 codec implementation](https://github.com/strukturag/libde265)
**Version:** 1.0.8

**Description:**
> libde265 is an open source implementation of the h.265 video codec. It is written from 
> scratch and has a plain C API to enable a simple integration into other software.
> 
> libde265 supports WPP and tile-based multithreading and includes SSE optimizations. 
> The decoder includes all features of the Main profile and correctly decodes almost 
> all conformance streams

**Project:** Harlinn.libde265

### [libebml](https://github.com/Matroska-Org/libebml)
**Version:** 1.4.5 

**Description:**
> A C++ library to parse EBML files

**Project:** Harlinn.libebml

### [FLAC - Free Lossless Audio Codec](https://github.com/xiph/flac)
**Version:** 1.3.2 

**Description:**
> FLAC is an Open Source lossless audio codec

**Project:** Harlinn.libflac

### [libheif](https://github.com/strukturag/libheif)
**Version:** 1.12.0 

**Description:**
> libheif is an ISO/IEC 23008-12:2017 HEIF and AVIF (AV1 Image File Format) file format 
> decoder and encoder.
> 
> HEIF and AVIF are new image file formats employing HEVC (h.265) or AV1 image coding, 
> respectively, for the best compression ratios currently possible.

**Project:** Harlinn.libheif

### [liblzma](https://tukaani.org/)
**Version:** 5.2.5

**Description:**
> LZMA Utils is an attempt to provide LZMA compression to POSIX-like systems. The idea 
> is to have a gzip-like command line tool and a zlib-like library, which would make 
> it easy to adapt the new compression technology to existing applications.

**Project:** Harlinn.liblzma

### [libmysofa](https://github.com/hoene/libmysofa)
**Version:** 1.2.1

**Description:**
> This is a simple set of C functions to read AES SOFA files, if they contain HRTFs 
> stored according to the AES69-2015 standard.

**Project:** Harlinn.libmysofa

### [libogg](https://www.xiph.org/ogg)
**Version:** 1.3.5 

**Description:**
> Ogg is a multimedia container format, and the native file and stream format for the 
> Xiph.org multimedia codecs.

**Project:** Harlinn.libogg

### [libsodium](https://github.com/jedisct1/libsodium)
**Version:** 1.0.18

**Description:**
> Sodium is a new, easy-to-use software library for encryption, decryption, signatures, password hashing and more.

**Project:** Harlinn.libsodium

### [libSRTP](https://github.com/cisco/libsrtp)
**Version:** 2.5.0

**Description:**
> This package provides an implementation of the Secure Real-time Transport Protocol (SRTP), the Universal Security Transform (UST), and a supporting cryptographic kernel. 

**Project:** Harlinn.libSRTP


### [LIBSVM -- A Library for Support Vector Machines](http://www.csie.ntu.edu.tw/~cjlin/libsvm)
**Version:** 3.16

**Description:**
> LIBSVM is an integrated software for support vector classification, (C-SVC, nu-SVC), regression 
> (epsilon-SVR, nu-SVR) and distribution estimation (one-class SVM). It supports multi-class classification.

**Project:** Harlinn.libsvm

### [VMAF - Video Multi-Method Assessment Fusion](https://github.com/Netflix/vmaf)
**Version:** 2.2.0

**Description:**
> VMAF is a perceptual video quality assessment algorithm developed by Netflix. 

**Project:** Harlinn.libvmaf

### [Libxml2](http://xmlsoft.org/)
**Version:** 2.9.12

**Description:**
> Libxml2 is the XML C parser and toolkit developed for the Gnome project.

**Project:** Harlinn.libxml2

### [ZeroMQ](https://zeromq.org/)
**Version:** 4.3.4

**Description:**
> ZeroMQ (also known as ØMQ, 0MQ, or zmq) looks like an embeddable networking library but acts like 
> a concurrency framework. It gives you sockets that carry atomic messages across various transports 
> like in-process, inter-process, TCP, and multicast. You can connect sockets N-to-N with patterns 
> like fan-out, pub-sub, task distribution, and request-reply. It's fast enough to be the fabric for 
> clustered products. Its asynchronous I/O model gives you scalable multicore applications, built as 
> asynchronous message-processing tasks. It has a score of language APIs and runs on most operating systems.

**Project:** Harlinn.libzmq

### [LIVE555 Streaming Media](http://www.live555.com/liveMedia/)
**Version:** 2023.06.20

**Description:**
> This code forms a set of C++ libraries for multimedia streaming, using open standard protocols (RTP/RTCP, RTSP, SIP).

**Project:** Harlinn.live555


### [Lightning Memory-Mapped Database](https://symas.com/lmdb/)
**Version:** 0.9.70

**Description:**
> An ultra-fast, ultra-compact, crash-proof, key-value, embedded data store

**Project:** Harlinn.LMDB


### [LodePNG - PNG encoder and decoder in C and C++, without dependencies](http://lodev.org/lodepng)
**Version:** 20200215

**Description:**
> LodePNG is a PNG image decoder and encoder, all in one, no dependency or 
> linkage to zlib or libpng required.

**Project:** Harlinn.lodepng

### [Lua](https://www.lua.org/home.html)
**Version:** 5.4.3

**Description:**
> Lua is a powerful, efficient, lightweight, embeddable scripting language. It supports procedural 
> programming, object-oriented programming, functional programming, data-driven programming, and 
> data description.

**Project:** Harlinn.lua


### [LZ4 - Extremely fast compression](https://github.com/lz4/lz4)
**Version:** 1.9.3

**Description:**
> LZ4 is lossless compression algorithm, providing compression speed > 500 MB/s 
> per core, scalable with multi-cores CPU. It features an extremely fast decoder, 
> with speed in multiple GB/s per core, typically reaching RAM speed limits on 
> multi-core systems.

**Project:** Harlinn.lz4

### [LZMA SDK](https://www.7-zip.org/sdk.html)
**Version:** 21.03

**Description:**
> LZMA / LZMA2 are default and general compression methods of 7z format in the 
> 7-Zip program. LZMA provides a high compression ratio and fast decompression, 
> so it is very suitable for embedded applications. 

**Project:** Harlinn.lzma

### [Mesh Data Abstraction Library (MDAL)](https://github.com/lutraconsulting/MDAL)
**Version:** 0.8.1

**Description:**
> Mesh Data Abstraction Library.

**Project:** Harlinn.mdal

### [minizip](http://www.winimage.com/zLibDll/minizip.html)
**Version:** 1.1

**Description:**
> This package enables to extract files from a .zip archive file.

**Project:** Harlinn.minizip

### [Unidata NetCDF](https://github.com/Unidata/netcdf-c)
**Version:** TBD - this project is currently just a placeholder

**Project:** Harlinn.netcdf-c

### [JSON for Modern C++](https://github.com/nlohmann/json)
**Version:** develop as of 2021.08.16

**Description:**
> JSON for Modern C++

**Project:** Harlinn.nlohmann-json

### [NMEA0183](https://github.com/SammyB428/NMEA0183)

**Description:**
C++ class to parse NMEA0183 sentences

**Project:** Harlinn.NMEA0183

### [OpenAL Soft is an LGPL-licensed, cross-platform, software implementation of the OpenAL 3D audio API.](http://openal-soft.org)
**Version:** 1.21.1

**Description:**
> OpenAL Soft is an LGPL-licensed, cross-platform, software implementation of the OpenAL 3D audio API.
> 
> OpenAL provides capabilities for playing audio in a virtual 3D environment. Distance attenuation, 
> doppler shift, and directional sound emitters are among the features handled by the API.

**Project:** Harlinn.openal-soft

### [OpenCensus - A stats collection and distributed tracing framework](https://github.com/census-instrumentation/opencensus-cpp)
**Version:** 0.4.0

**Description:**
> OpenCensus is a toolkit for collecting application performance and behavior data. It currently includes an API for tracing and stats.

**Project:** Harlinn.opencensus

### [OpenEXR](https://github.com/AcademySoftwareFoundation/openexr)
**Version:** master as of 2021.08.18

**Description:**
> OpenEXR provides the specification and reference implementation of the EXR file format, the 
> professional-grade image storage format of the motion picture industry.
> 
> The purpose of EXR format is to accurately and efficiently represent high-dynamic-range 
> scene-linear image data and associated metadata, with strong support for multi-part, 
> multi-channel use cases.

**Projects:**
- Harlinn.iex
- Harlinn.ilmthread
- Harlinn.openexr
- Harlinn.openexrcore
- Harlinn.openexrutil

### [OpenFYBA](https://github.com/kartverket/fyba)
**Version:** 4.1.1 

**Description:**
> OpenFYBA is the source code release of the FYBA library, distributed by the 
> National Mapping Authority of Norway (Statens kartverk) to read and write 
> files in the National geodata standard format SOSI.

**Project:** Harlinn.openfyba

### [The Preview Image Extractor (PIEX)](https://github.com/google/piex)
**Version:** master as of 2021.09.24

**Description:**
> The Preview Image Extractor (PIEX) is designed to find and extract the largest JPEG 
> compressed preview image contained in a RAW file.

**Project:** Harlinn.piex

### [libpng](http://www.libpng.org/pub/png/libpng.html)
**Version:** 1.6.37

**Description:**
> libpng is the official PNG reference library. It supports almost all PNG features, 
> is extensible, and has been extensively tested for over 23 years.

**Project:** Harlinn.png

### [PROJ is a generic coordinate transformation software](https://proj.org/)
**Version:** 8.1.0

**Description:**
> PROJ is a generic coordinate transformation software that transforms geospatial 
> coordinates from one coordinate reference system (CRS) to another. This includes 
> cartographic projections as well as geodetic transformations. 

**Project:** Harlinn.proj

### [Protocol Buffers](https://developers.google.com/protocol-buffers)
**Version:** 3.17.3

**Description:**
> Protocol buffers are Google's language-neutral, platform-neutral, extensible 
> mechanism for serializing structured data – think XML, but smaller, faster, and 
> simpler. You define how you want your data to be structured once, then you can 
> use special generated source code to easily write and read your structured data 
> to and from a variety of data streams and using a variety of languages.

**Projects:** 
- Harlinn.protobuf
- Tools\\3rdParty\\protobuf\\protoc

### [pthreads4w](https://sourceforge.net/projects/pthreads4w/)
**Version:** 3.0.0

**Description:**
> Also known as "pthreads-win32", POSIX Threads for Windows implements a large subset 
> of the threads related API from the Single Unix Specification Version 3.
>
> Conformance and quality are high priorities of this mature library. Development began 
> in 1998 and has continued with numerous significant professional contributions.

**Project:** Harlinn.pthreads4w

### [Qpid Proton - The AMQP messaging toolkit](https://qpid.apache.org/proton/)
**Version:** 0.35.0

**Description:**
> Qpid Proton is a high-performance, lightweight messaging library. It can be used 
> in the widest range of messaging applications, including brokers, client libraries, 
> routers, bridges, proxies, and more. Proton makes it trivial to integrate with the 
> AMQP 1.0 ecosystem from any platform, environment, or language.

**Projects:**
- Harlinn.qpid-proton
- Harlinn.qpid-proton-cpp

### [RapidJSON](https://github.com/Tencent/rapidjson)
**Version:** master as of 2021.09.26

**Description:**
> A fast JSON parser/generator for C++ with both SAX/DOM style API.

**Project:** Harlinn.RapidJSON

### [RE2 - a regular expression library](https://github.com/google/re2)
**Version:** 2021-09-01

**Description:**
> RE2 was designed and implemented with an explicit goal of being able to 
> handle regular expressions from untrusted users without risk. One of its 
> primary guarantees is that the match time is linear in the length of the 
> input string. It was also written with production concerns in mind: the 
> parser, the compiler and the execution engines limit their memory usage by 
> working within a configurable budget – failing gracefully when exhausted – 
> and they avoid stack overflow by eschewing recursion.

**Project:** Harlinn.re2

### [RocksDB: A Persistent Key-Value Store for Flash and RAM Storage](https://github.com/facebook/rocksdb)
**Version:** 6.22.1

**Description:**
> RocksDB is a storage engine with key/value interface, where keys and values are arbitrary 
> byte streams. It is a C++ library. It was developed at Facebook based on LevelDB and provides 
> backwards-compatible support for LevelDB APIs.
> 
> RocksDB supports various storage hardware, with fast flash as the initial focus. It uses a 
> Log Structured Database Engine for storage, is written entirely in C++

**Project:** Harlinn.rocksdb

### [rtmidi](https://www.music.mcgill.ca/~gary/rtmidi/index.html)
**Version:** 5.0.0

**Description:**
> RtMidi is a set of C++ classes (RtMidiIn, RtMidiOut and API-specific classes) that provides a common 
> API (Application Programming Interface) for realtime MIDI input/output across Linux (ALSA & JACK), 
> Macintosh OS X (CoreMIDI & JACK), and Windows (Multimedia Library) operating systems. RtMidi significantly 
> simplifies the process of interacting with computer MIDI hardware and software.

**Project:** Harlinn.rtmidi

### [RtspServer](https://github.com/PHZ76/RtspServer)
**Version:** 1.0.0

**Description:**
> A RTSP server and pusher based on C++11

**Project:** Harlinn.RtspServer


### [Scintilla - a free source code editing component](https://www.scintilla.org/)
**Version:** 5.1.3

**Description:**
> Scintilla is a free source code editing component. It comes with complete source code and 
> a license that permits use in any free project or commercial product.
>
> As well as features found in standard text editing components, Scintilla includes features 
> especially useful when editing and debugging source code. These include support for syntax 
> styling, error indicators, code completion and call tips. The selection margin can contain 
> markers like those used in debuggers to indicate breakpoints and the current line. Styling 
> choices are more open than with many editors, allowing the use of proportional fonts, bold 
> and italics, multiple foreground and background colours and multiple fonts.

**Project:** Harlinn.scintilla

### [Simple DirectMedia Layer (SDL) Version 2.0](https://github.com/libsdl-org/SDL)
**Version:** 2.0.16 

**Description:**
> Simple DirectMedia Layer is a cross-platform development library designed to provide low 
> level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and 
> Direct3D.

**Project:** Harlinn.SDL2

### [Simple and Fast Multimedia Library](https://www.sfml-dev.org/)
**Version:** 2.5.1

**Description:**
> SFML provides a simple interface to the various components of your PC, to ease the 
> development of games and multimedia applications. It is composed of five modules: 
> system, window, graphics, audio and network.

**Projects:**
- Harlinn.sfml-audio
- Harlinn.sfml-graphics
- Harlinn.sfml-network
- Harlinn.sfml-system
- Harlinn.sfml-window

### [The sjpeg library](https://github.com/webmproject/sjpeg)
**Version:** master as of 2021.09.11

**Description:**
> sjpeg is a simple encoding library for encoding baseline JPEG files.

**Project:** Harlinn.sjpeg

### [skcms](https://skia.googlesource.com/skcms/)
**Version:** main as of 2021.09.12

**Description:**
Skia Color Management

**Project:** Harlinn.skcms

### [Skia - The 2D Graphics Library](https://skia.org/)
**Version:** 0.31

**Description:**
> Skia is an open source 2D graphics library which provides common APIs that work 
> across a variety of hardware and software platforms. It serves as the graphics 
> engine for Google Chrome and Chrome OS, Android, Flutter, Mozilla Firefox and 
> Firefox OS, and many other products.

**Projects:** 
- Harlinn.skia
- Tools\\3rdParty\\Skia\\skslc

### [Snappy - a compression/decompression library](https://github.com/google/snappy)
**Version:** master as of 2021.08.02

**Description:**
> Snappy is a compression/decompression library. It does not aim for maximum compression, 
> or compatibility with any other compression library; instead, it aims for very high 
> speeds and reasonable compression. For instance, compared to the fastest mode of zlib, 
> Snappy is an order of magnitude faster for most inputs, but the resulting compressed 
> files are anywhere from 20% to 100% bigger.

**Project:** Harlinn.snappy

### [sqlite3](https://www.sqlite.org/index.html)
**Version:** 3.36.0

**Description:**
> SQLite is a C-language library that implements a small, fast, self-contained, high-reliability, 
> full-featured, SQL database engine.

**Projects:** 
- Harlinn.SQLite3
- Tools\\3rdParty\\SQLite3\\sqlite3

### [Single-file public-domain/open source libraries with minimal dependencies (STB) ](https://github.com/nothings/single_file_libs)
**Version:** master as of 2021.09.10

**Description:**
> Small, easy-to-integrate, portable libraries which are usable from C and/or C++

**Project:** Harlinn.stb

### [SuperLU](https://portal.nersc.gov/project/sparse/superlu/)
**Version:** 5.2.2

**Description:**
> SuperLU is a general purpose library for the direct solution of large, sparse, nonsymmetric systems of linear equations.

**Project:** Harlinn.superlu

### [LibTIFF](https://libtiff.gitlab.io/libtiff/)
**Version:** 4.3.0 

**Description:**
> This software provides support for the Tag Image File Format (TIFF), a widely used format for storing image data.

**Project:** Harlinn.tiff

### [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
**Version:** master as of 2021.12.27

**Description:**
> Tiny but powerful single file wavefront obj loader written in C++03. No dependency 
> except for C++ STL. It can parse over 10M polygons with moderate memory and time.

**Project:** Harlinn.tinyobjloader

### [TinyXML-2](https://github.com/leethomason/tinyxml2)
**Version:** master as of 2021.06.07

**Description:**
> TinyXML-2 is a simple, small, efficient, C++ XML parser that can be easily integrated into other programs.

**Project:** Harlinn.tinyxml2

### [μpb: small, fast C protos](https://github.com/protocolbuffers/upb)
**Version:** master as of 2021.10.21

**Description:**
> μpb (often written 'upb') is a small protobuf implementation written in C.

**Projects:** 
- Harlinn.upb
- Tools\\3rdParty\\upb\\protoc-gen-upb
- Tools\\3rdParty\\upb\\protoc-gen-upbdefs

### [uriparser](https://github.com/uriparser/uriparser)
**Version:** 0.9.5

**Description:**
> uriparser is a strictly RFC 3986 compliant URI parsing and handling library written in C89 ("ANSI C").

**Project:** Harlinn.uriparser

### [libvorbis, libvorbisfile and libvorbisenc](https://github.com/xiph/vorbis)
**Version:** 1.3.7

**Description:**
> Vorbis is a general purpose audio and music encoding format contemporary to MPEG-4's AAC 
> and TwinVQ, the next generation beyond MPEG audio layer 3.

**Project:** Harlinn.utfcpp

### [utfcpp](https://github.com/nemtrif/utfcpp)
**Version:** 4.0.4

**Description:**
> UTF8-CPP: UTF-8 with C++ in a Portable Way.


**Project:** Harlinn.vorbis

### [Vulkan header files](https://github.com/KhronosGroup/Vulkan-Headers)
**Version:** main as of 2021.09.21

**Description:**
> Vulkan header files

**Project:** Harlinn.vulkan

### [Vulkan Memory Allocator](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)
**Version:** 2.3.0 

**Description:**
> The Vulkan® Memory Allocator (VMA) library provides a simple and easy to integrate API 
> to help you allocate memory for Vulkan® buffer and image storage.

**Project:** Harlinn.vulkanmemoryallocator

### [libwebm](https://chromium.googlesource.com/webm/libwebm/)
**Version:** main as of 2021.09.08

**Description:**
> The WebM Project is dedicated to developing a high-quality, open video format for the 
> web that's freely available to everyone.

**Project:** Harlinn.webm

### [WebP - An image format for the Web](https://developers.google.com/speed/webp)
**Version:** main as of 2021.09.08

**Description:**
> WebP is a modern image format that provides superior lossless and lossy compression for 
> images on the web. Using WebP, webmasters and web developers can create smaller, richer 
> images that make the web faster.

**Project:** Harlinn.webp

### [Xerces-C++ - a validating XML parser](http://xerces.apache.org/xerces-c/)
**Version:** 3.2.3 

**Description:**
> Xerces-C++ is a validating XML parser written in a portable subset of C++. 
> Xerces-C++ makes it easy to give your application the ability to read and 
> write XML data.

**Project:** Harlinn.xerces-c

### [XMP-Toolkit-SDK](https://github.com/adobe/XMP-Toolkit-SDK)
**Version:** 6.0.0

**Description:**
> The XMP Toolkit allows you to integrate XMP functionality into your product or solution. 

**Project:** Harlinn.xmptoolkitsdk

### [libyuv](https://chromium.googlesource.com/libyuv/libyuv/)
**Version:** main as of 2021-09-07

**Description:**
> libyuv is an open source project that includes YUV scaling and conversion functionality.

**Project:** Harlinn.yuv

### [zlib](http://zlib.net/)
**Version:** 1.2.11

**Description:**
> zlib is designed to be a free, general-purpose, legally unencumbered -- that is, not 
> covered by any patents -- lossless data-compression library for use on virtually any 
> computer hardware and operating system. 

**Project:** Harlinn.zlib

### [zlib-ng](https://github.com/zlib-ng/zlib-ng)
**Version:** develop as of 2021.05.08

**Description:**
> zlib data compression library for the next generation systems

**Project:** Harlinn.zlibng

### [Zstandard (zstd)](https://github.com/facebook/zstd)
**Version:** dev as of 2021.08.04

**Description:**
> Zstandard, or zstd as short version, is a fast lossless compression algorithm, targeting 
> real-time compression scenarios at zlib-level and better compression ratios.

**Project:** Harlinn.zstd

