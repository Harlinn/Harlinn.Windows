#pragma once
#ifndef __HCCLOGGERLEVEL_H__
#define __HCCLOGGERLEVEL_H__

#include <HCCDef.h>
#include <HCCString.h>

namespace Harlinn::Common::Core::Logging
{

    enum class Level : UInt16
    {
        None = 0,
        Trace = 0x0008,
        Entering = Trace | 0x0001,
        Leaving = Trace | 0x0002,
        Verbose = 0x0010,
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
        All = Trace | Verbose | Debug | Info | Notice | Warning | Error | Exception | Critical | Alert | Emergency | System,
#ifdef _DEBUG
        Default = Trace | Verbose | Debug | Info | Notice | Warning | Error | Exception | Critical | Alert | Emergency | System
#else
        Default = Info | Notice | Warning | Error | Exception | Critical | Alert | Emergency
#endif
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( Level, UInt16 );


    template<WideStringLike StringT>
    HCC_TEMPLATE_EXPORT_DECL StringT ToString( Level level );
    template HCC_EXPORT WideString ToString<WideString>( Level level );
    template HCC_EXPORT std::wstring ToString<std::wstring>( Level level );
    


    template<AnsiStringLike StringT>
    HCC_TEMPLATE_EXPORT_DECL StringT ToString( Level level );
    template HCC_EXPORT AnsiString ToString<AnsiString>( Level level );
    template HCC_EXPORT std::string ToString<std::string>( Level level );


    HCC_EXPORT bool TryParse( const std::wstring_view& str, Level& result );
    HCC_EXPORT bool TryParse( const std::string_view& str, Level& result );

    template<StringLike StringT>
    inline bool TryParse( const StringT& str, Level& result )
    {
        using StringViewT = std::basic_string_view<typename StringT::value_type>;
        StringViewT stringView( str.c_str(), str.size() );
        return TryParse( stringView, result );
    }



    template< class CharT, class Traits >
    inline std::basic_ostream<CharT, Traits>& operator<<( std::basic_ostream<CharT, Traits>& outputStream, const Level& level )
    {
        using StringT = std::basic_string<CharT, Traits>;
        StringT levelStr = ToString<StringT>( level );
        outputStream << levelStr;
        return outputStream;
    }

    template <class CharT, class CharTraitsT>
    std::basic_istream<CharT, CharTraitsT>& operator >> ( std::basic_istream<CharT, CharTraitsT>& inputStream, Level& level )
    {
        using IStreamT = std::basic_istream<CharT, CharTraitsT>;
        using StringT = std::basic_string<CharT, CharTraitsT>;
        StringT levelStr;
        
        inputStream >> levelStr;
        if ( !TryParse( levelStr, level ) )
        {
            auto inputStreamState = inputStream.rdstate( );
            inputStreamState |= IStreamT::failbit;
            inputStream.setstate( inputStreamState );
        }
        return inputStream;
    }

    


}

#endif
