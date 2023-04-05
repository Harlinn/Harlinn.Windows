#pragma once
#ifndef HARLINN_CLSOCKET_CLSOCKET_EXPORT_H_
#define HARLINN_CLSOCKET_CLSOCKET_EXPORT_H_

#ifdef BUILDING_HARLINN_CLSOCKET
#define CLSOCKET_EXPORT __declspec(dllexport)
#else
#define CLSOCKET_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.clsocket.lib")
#endif

#endif
