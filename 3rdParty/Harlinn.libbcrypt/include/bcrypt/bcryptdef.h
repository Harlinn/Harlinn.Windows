#pragma once
#ifndef HARLINN_WINDOWS_LIBBCRYPT_BCRYPTDEF_H_
#define HARLINN_WINDOWS_LIBBCRYPT_BCRYPTDEF_H_

#ifdef BUILDING_HARLINN_WINDOWS_LIBBCRYPT
#define HW_LIBBCRYPT_EXPORT __declspec(dllexport)
#define HW_LIBBCRYPT_TEMPLATE_EXPORT __declspec(dllexport)
#define HW_LIBBCRYPT_TEMPLATE_EXPORT_DECL
#else
#define HW_LIBBCRYPT_EXPORT __declspec(dllimport)
#define HW_LIBBCRYPT_TEMPLATE_EXPORT __declspec(dllimport)
#define HW_LIBBCRYPT_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.libbcrypt.lib")
#endif


#endif
