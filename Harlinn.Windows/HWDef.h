#pragma once
#ifndef __HWDEF_H__
#define __HWDEF_H__

#include <HCCDef.h>
#include <HCCGuid.h>
#include <HCCCom.h>
#include <HCCDateTime.h>
#include <HCCString.h>
#include <HCCTraits.h>
#include <HCCMath.h>
#include <HCCSync.h>

#ifdef BUILDING_HARLINN_WINDOWS
#define HW_EXPORT __declspec(dllexport)
#define HW_TEMPLATE_EXPORT __declspec(dllexport)
#define HW_TEMPLATE_EXPORT_DECL
#else
#define HW_EXPORT __declspec(dllimport)
#define HW_TEMPLATE_EXPORT __declspec(dllimport)
#define HW_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.Windows.lib")
#endif

#ifdef _DEBUG
#define HW_INLINE_DECL HW_EXPORT
#define HW_INLINE 
#else
#define HW_INLINE_DECL 
#define HW_INLINE inline
#endif

namespace Harlinn::Common::Core
{
}
namespace Harlinn::Windows
{
    using namespace Harlinn::Common::Core;
}



#endif
