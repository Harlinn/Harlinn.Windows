#pragma once
#ifndef __HCCLOGGERLEVEL_H__
#define __HCCLOGGERLEVEL_H__

#include <HCCDef.h>
#include <HCCConcepts.h>

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


    template<WideStringLike StringT>
    inline StringT ToString( Level level )
    {
        if ( level == Level::None )
        {
            return L"None";
        }
        else if ( level == Level::SystemStart )
        {
            return L"Start";
        }
        else if ( level == Level::SystemStop )
        {
            return L"Stop";
        }
        else
        {
            StringT result;
            int count = 0;
            if ( level & Level::Trace )
            {
                result = L"Trace";
                count++;
            }
            if ( level & Level::Debug )
            {
                result += count? L"|Debug" : L"Debug";
                count++;
            }
            if ( level & Level::Info )
            {
                result += count ? L"|Info" : L"Info";
                count++;
            }
            if ( level & Level::Notice )
            {
                result += count ? L"|Notice" : L"Notice";
                count++;
            }
            if ( level & Level::Warning )
            {
                result += count ? L"|Warning" : L"Warning";
                count++;
            }
            if ( level & Level::Error )
            {
                result += count ? L"|Error" : L"Error";
                count++;
            }
            if ( level & Level::Exception )
            {
                result += count ? L"|Exception" : L"Exception";
                count++;
            }
            if ( level & Level::Critical )
            {
                result += count ? L"|Critical" : L"Critical";
                count++;
            }
            if ( level & Level::Alert )
            {
                result += count ? L"|Alert" : L"Alert";
                count++;
            }
            if ( level & Level::Emergency )
            {
                result += count ? L"|Emergency" : L"Emergency";
                count++;
            }
            if ( level & Level::System )
            {
                result += count ? L"|System" : L"System";
                count++;
            }
            return result;
        }
    }

    template<AnsiStringLike StringT>
    inline StringT ToString( Level level )
    {
        if ( level == Level::None )
        {
            return "None";
        }
        else if ( level == Level::SystemStart )
        {
            return "Start";
        }
        else if ( level == Level::SystemStop )
        {
            return "Stop";
        }
        else
        {
            StringT result;
            int count = 0;
            if ( level & Level::Trace )
            {
                result = "Trace";
                count++;
            }
            if ( level & Level::Debug )
            {
                result += count ? "|Debug" : "Debug";
                count++;
            }
            if ( level & Level::Info )
            {
                result += count ? "|Info" : "Info";
                count++;
            }
            if ( level & Level::Notice )
            {
                result += count ? "|Notice" : "Notice";
                count++;
            }
            if ( level & Level::Warning )
            {
                result += count ? "|Warning" : "Warning";
                count++;
            }
            if ( level & Level::Error )
            {
                result += count ? "|Error" : "Error";
                count++;
            }
            if ( level & Level::Exception )
            {
                result += count ? "|Exception" : "Exception";
                count++;
            }
            if ( level & Level::Critical )
            {
                result += count ? "|Critical" : "Critical";
                count++;
            }
            if ( level & Level::Alert )
            {
                result += count ? "|Alert" : "Alert";
                count++;
            }
            if ( level & Level::Emergency )
            {
                result += count ? "|Emergency" : "Emergency";
                count++;
            }
            if ( level & Level::System )
            {
                result += count ? "|System" : "System";
                count++;
            }
            return result;
        }
    }


    inline bool TryParse( const std::wstring_view& str, Level& result)
    {
        if ( str == L"None" )
        {
            result = Level::None;
            return true;
        }
        else if ( str == L"Start" )
        {
            result = Level::SystemStart;
            return true;
        }
        else if ( str == L"Stop" )
        {
            result = Level::SystemStop;
            return true;
        }
        else
        {

        }
    }




    template< class CharT, class Traits >
    inline std::basic_ostream<CharT, Traits>& operator<<( std::basic_ostream<CharT, Traits>& os, const Level& level )
    {

        return os;
    }



    


}

#endif
