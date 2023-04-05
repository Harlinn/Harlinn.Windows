#pragma once
#ifndef HARLINN_GRPC_COMPILER_GRPC_COMPILER_EXPORT_H_
#define HARLINN_GRPC_COMPILER_GRPC_COMPILER_EXPORT_H_

#ifdef BUILDING_HARLINN_GRPC_COMPILER
#define GRPC_COMPILER_EXPORT __declspec(dllexport)
#else
#define GRPC_COMPILER_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.grpc-compiler.lib")
#endif


#endif
