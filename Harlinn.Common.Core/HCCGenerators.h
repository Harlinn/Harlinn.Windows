#pragma once
#ifndef HARLINN_COMMON_CORE_HCCGENERATORS_H_
#define HARLINN_COMMON_CORE_HCCGENERATORS_H_

#include "HCCDef.h"
#include "HCCString.h"


namespace Harlinn::Common::Core::Generators
{
    template<typename T>
        requires std::is_same_v<WideString,T>
    T Generate( size_t count, const std::wstring_view& source )
    {
        assert( source.size( ) > 0 );
        WideString result;
        result.SetLength( count );
        auto sourceLength = source.size( );
        auto* ptr = result.data( );
        for ( size_t i = 0; i < count; i++ )
        {
            wchar_t value = source[ i % sourceLength ];
            ptr[ i ] = value;
        }

        return result;
    }

    template<typename T>
        requires std::is_same_v<WideString, T>
    T Generate( size_t count, const wchar_t* source )
    {
        return Generate<WideString>( count, std::wstring_view( source ) );
    }


    template<typename T>
        requires std::is_same_v<AnsiString, T>
    T Generate( size_t count, const std::string_view& source )
    {
        assert( source.size( ) > 0 );
        AnsiString result;
        result.SetLength( count );
        auto sourceLength = source.size( );
        auto* ptr = result.data( );
        for ( size_t i = 0; i < count; i++ )
        {
            char value = source[ i % sourceLength ];
            ptr[ i ] = value;
        }

        return result;
    }

    template<typename T>
        requires std::is_same_v<AnsiString, T>
    T Generate( size_t count, const char* source )
    {
        return Generate<AnsiString>( count, std::string_view( source ) );
    }

    template<typename T>
        requires std::is_same_v<std::vector<Byte>, T>
    T Generate( size_t count, const std::string_view& source )
    {
        assert( source.size( ) > 0 );
        std::vector<Byte> result;
        result.resize( count );
        auto sourceLength = source.size( );
        auto* ptr = result.data( );
        for ( size_t i = 0; i < count; i++ )
        {
            char value = source[ i % sourceLength ];
            ptr[ i ] = value;
        }

        return result;
    }

    template<typename T>
        requires std::is_same_v<std::vector<Byte>, T>
    T Generate( size_t count, const char* source )
    {
        return Generate<std::vector<Byte>>( count, std::string_view( source ) );
    }



}


#endif
