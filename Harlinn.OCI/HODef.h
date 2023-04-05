#pragma once
#ifndef __HODEF_H__
#define __HODEF_H__

#include <HCCDef.h>

#include <HCCDateTime.h>
#include <HCCString.h>
#include <HCCBlocks.h>
#include <HCCBinaryWriter.h>
#include <HCCConverters.h>
#include <HCCBitConverter.h>
#include <HCCSync.h>


#ifdef BUILDING_HARLINN_OCI
#define HO_EXPORT __declspec(dllexport)
#define HO_TEMPLATE_EXPORT __declspec(dllexport)
#define HO_TEMPLATE_EXPORT_DECL
#else
#define HO_EXPORT __declspec(dllimport)
#define HO_TEMPLATE_EXPORT __declspec(dllimport)
#define HO_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.OCI.lib")
#endif

#ifdef _DEBUG
#define HO_INLINE_DECL HO_EXPORT
#define HO_INLINE 
#else
#define HO_INLINE_DECL 
#define HO_INLINE inline
#endif

namespace Harlinn::Common::Core
{
}
namespace Harlinn::OCI
{
    using namespace Harlinn::Common::Core;
}


#endif
