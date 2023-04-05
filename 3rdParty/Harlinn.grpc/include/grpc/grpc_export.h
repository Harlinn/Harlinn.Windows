#pragma once
#ifndef HARLINN_GRPC_GRPC_EXPORT_H_
#define HARLINN_GRPC_GRPC_EXPORT_H_

#ifdef BUILDING_HARLINN_GRPC
 #ifndef GPRAPI
  #define GPRAPI __declspec(dllexport)
 #endif
 #ifndef GRPC_EXPORT
  #define GRPC_EXPORT __declspec(dllexport)
 #endif
 #ifndef GRPCAPI
  #define GRPCAPI GPRAPI
 #endif
#else
 #ifndef GRPC_EXPORT
  #define GRPC_EXPORT __declspec(dllimport)
 #endif
 #pragma comment(lib,"Harlinn.grpc.lib")
#endif


#endif
