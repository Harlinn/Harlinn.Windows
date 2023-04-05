#pragma once
#ifndef __HCCLOGGERLEVEL_H__
#define __HCCLOGGERLEVEL_H__

#include <HCCDef.h>

namespace Harlinn::Common::Core::Logging
{
    class Backend;

    enum class Level : UInt16
    {
        None = 0,
        Trace = 0x0010,
        Debug = 0x0020,
        Info = 0x0040,
        Notice = 0x0080,
        Warning = 0x0100,
        Error = 0x0200,
        Exception = 0x0800,
        Critical = 0x1000,
        Alert = 0x2000,
        Emergency = 0x4000,
        System = 0x8000,
        SystemStart = System | 0x0001,
        SystemStop = System | 0x0002,
        All = Trace | Debug | Info | Notice | Warning | Error | Exception | Critical | Alert | Emergency | System,
#ifdef _DEBUG
        Default = Trace | Debug | Info | Notice | Warning | Error | Exception | Critical | Alert | Emergency | System
#else
        Default = Info | Notice | Warning | Error | Exception | Critical | Alert | Emergency
#endif
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( Level, UInt16 );

}

#endif
