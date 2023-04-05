#pragma once
#ifndef HARLINN_GRPC_COMPILER_PLUGINS_H_
#define HARLINN_GRPC_COMPILER_PLUGINS_H_

#include "grpc/compiler/grpc_compiler_export.h"


GRPC_COMPILER_EXPORT int RunCppPlugin( int argc, char* argv[] );
GRPC_COMPILER_EXPORT int RunCSharpPlugin( int argc, char* argv[] );
GRPC_COMPILER_EXPORT int RunNodePlugin( int argc, char* argv[] );
GRPC_COMPILER_EXPORT int RunObjectiveCPlugin( int argc, char* argv[] );
GRPC_COMPILER_EXPORT int RunPHPPlugin( int argc, char* argv[] );
GRPC_COMPILER_EXPORT int RunPythonPlugin( int argc, char* argv[] );
GRPC_COMPILER_EXPORT int RunRubyPlugin( int argc, char* argv[] );


#endif
