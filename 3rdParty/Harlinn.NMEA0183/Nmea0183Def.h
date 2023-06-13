#pragma once
#ifndef HARLINN_3RDPARTY_NMEA0183DEF_H_
#define HARLINN_3RDPARTY_NMEA0183DEF_H_

#ifdef BUILDING_HARLINN_3RDPARTY_NMEA0183

#define NMEA0183_EXPORT __declspec(dllexport)
#define NMEA0183_TEMPLATE_EXPORT __declspec(dllexport)
#define NMEA0183_TEMPLATE_EXPORT_DECL

#else

#define NMEA0183_EXPORT __declspec(dllimport)
#define NMEA0183_TEMPLATE_EXPORT __declspec(dllimport)
#define NMEA0183_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.NMEA0183.lib")
#endif



#endif
