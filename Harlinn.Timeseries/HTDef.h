#pragma once
#ifndef __HTDEF_H__
#define __HTDEF_H__

#include <HCCDef.h>
#include <HCCException.h>
#include <HCCBinaryReader.h>
#include <HCCBinaryWriter.h>
#include <HCCPersistent.h>


#ifdef BUILDING_HARLINN_TIMESERIES
#define HT_EXPORT __declspec(dllexport)
#define HT_TEMPLATE_EXPORT __declspec(dllexport)
#define HT_TEMPLATE_EXPORT_DECL
#else
#define HT_EXPORT __declspec(dllimport)
#define HT_TEMPLATE_EXPORT __declspec(dllimport)
#define HT_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.Timeseries.lib")
#endif

#ifdef _DEBUG
#define HT_INLINE_DECL HT_EXPORT
#define HT_INLINE 
#else
#define HT_INLINE_DECL 
#define HT_INLINE inline
#endif

namespace Harlinn::Common::Core
{
}
namespace Harlinn::Timeseries
{
    using namespace Harlinn::Common::Core;
}


#endif
