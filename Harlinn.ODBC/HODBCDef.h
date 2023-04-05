#pragma once
#ifndef __HODBCDEF_H__
#define __HODBCDEF_H__

#include <HCCDef.h>


#ifdef BUILDING_HARLINN_ODBC
#define HODBC_EXPORT __declspec(dllexport)
#define HODBC_TEMPLATE_EXPORT __declspec(dllexport)
#define HODBC_TEMPLATE_EXPORT_DECL
#else
#define HODBC_EXPORT __declspec(dllimport)
#define HODBC_TEMPLATE_EXPORT __declspec(dllimport)
#define HODBC_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.ODBC.lib")
#endif

#ifdef _DEBUG
#define HODBC_INLINE_DECL HODBC_EXPORT
#define HODBC_INLINE 
#else
#define HODBC_INLINE_DECL 
#define HODBC_INLINE inline
#endif

namespace Harlinn::Common::Core
{

}
namespace Harlinn::ODBC
{
    using namespace Harlinn::Common::Core;
}


#endif

