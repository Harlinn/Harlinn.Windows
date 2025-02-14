#pragma once
#ifndef HCCNETWORK_H_
#define HCCNETWORK_H_
/*
   Copyright 2024-2025 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "HCCString.h"
#include "HCCLib.h"

#pragma comment(lib, "ntdll.lib")

namespace Harlinn::Common::Core
{
    WideString ToWideString( const DL_EUI48* ethernetAddress )
    {
        if ( ethernetAddress )
        {
            wchar_t buffer[ 32 ];
            auto end = RtlEthernetAddressToStringW( ethernetAddress, buffer );
            if ( end )
            {
                size_t length = end - buffer;
                return WideString( buffer, length );
            }
        }
        return {};
    }
    AnsiString ToAnsiString( const DL_EUI48* ethernetAddress )
    {
        if ( ethernetAddress )
        {
            char buffer[ 32 ];
            auto end = RtlEthernetAddressToStringA( ethernetAddress, buffer );
            if ( end )
            {
                size_t length = end - buffer;
                return AnsiString( buffer, length );
            }
        }
        return {};
    }

    bool TryParse( const wchar_t* str, const wchar_t** end, DL_EUI48* ethernetAddress )
    {
        auto rc = RtlEthernetStringToAddressW( str, end, ethernetAddress );
        return rc == NO_ERROR;
    }

    bool TryParse( const wchar_t* str, DL_EUI48* ethernetAddress )
    {
        const wchar_t* end = nullptr;
        return TryParse( str, &end, ethernetAddress );
    }

    bool TryParse( const char* str, const char** end, DL_EUI48* ethernetAddress )
    {
        auto rc = RtlEthernetStringToAddressA( str, end, ethernetAddress );
        return rc == NO_ERROR;
    }

    bool TryParse( const char* str, DL_EUI48* ethernetAddress )
    {
        const char* end = nullptr;
        return TryParse( str, &end, ethernetAddress );
    }

    template<SimpleStringLike StringT>
    bool TryParse( const StringT& str, DL_EUI48* ethernetAddress )
    {
        return TryParse( str.c_str( ), ethernetAddress );
    }


    WideString ToWideString( const in_addr* addr )
    {
        if ( addr )
        {
            wchar_t buffer[ 32 ];
            auto end = RtlIpv4AddressToStringW( addr, buffer );
            if ( end )
            {
                size_t length = end - buffer;
                return WideString( buffer, length );
            }
        }
        return {};
    }

    AnsiString ToAnsiString( const in_addr* addr )
    {
        if ( addr )
        {
            char buffer[ 32 ];
            auto end = RtlIpv4AddressToStringA( addr, buffer );
            if ( end )
            {
                size_t length = end - buffer;
                return AnsiString( buffer, length );
            }
        }
        return {};
    }

    bool TryParse( const wchar_t* str, bool strict, const wchar_t** end, in_addr* addr )
    {
        auto rc = RtlIpv4StringToAddressW( str, strict, end, addr );
        return rc == NO_ERROR;
    }

    bool TryParse( const wchar_t* str, const wchar_t** end, in_addr* addr )
    {
        auto rc = RtlIpv4StringToAddressW( str, TRUE, end, addr );
        return rc == NO_ERROR;
    }

    bool TryParse( const wchar_t* str, in_addr* addr )
    {
        const wchar_t* end{};
        auto rc = RtlIpv4StringToAddressW( str, TRUE, &end, addr );
        return rc == NO_ERROR;
    }

    bool TryParse( const char* str, bool strict, const char** end, in_addr* addr )
    {
        auto rc = RtlIpv4StringToAddressA( str, strict, end, addr );
        return rc == NO_ERROR;
    }

    bool TryParse( const char* str, const char** end, in_addr* addr )
    {
        auto rc = RtlIpv4StringToAddressA( str, TRUE, end, addr );
        return rc == NO_ERROR;
    }

    bool TryParse( const char* str, in_addr* addr )
    {
        const char* end{};
        auto rc = RtlIpv4StringToAddressA( str, TRUE, &end, addr );
        return rc == NO_ERROR;
    }

    template<SimpleStringLike StringT>
    bool TryParse( const StringT& str, in_addr* addr )
    {
        return TryParse( str.c_str( ), addr );
    }

    template<SimpleStringLike StringT>
    bool TryParse( const StringT& str, typename StringT::size_type& end,in_addr* addr )
    {
        const typename StringT::value_type* endPtr = nullptr;
        if ( TryParse( str.c_str( ), &endPtr, addr ) )
        {
            end = static_cast< typename StringT::size_type >( endPtr - str.c_str( ) );
            return true;
        }
        return false;
    }


    WideString ToWideString( const in_addr* addr, UInt16 port )
    {
        if ( addr )
        {
            port = htons( port );
            wchar_t buffer[ 32 ];
            ULONG bufferLength = 32;
            auto rc = RtlIpv4AddressToStringExW( addr, port, buffer, &bufferLength );
            if ( rc == NO_ERROR )
            {
                return WideString( buffer, bufferLength );
            }
        }
        return {};
    }

    AnsiString ToAnsiString( const in_addr* addr, UInt16 port )
    {
        if ( addr )
        {
            port = htons( port );
            char buffer[ 32 ];
            ULONG bufferLength = 32;
            auto rc = RtlIpv4AddressToStringExA( addr, port, buffer, &bufferLength );
            if ( rc == NO_ERROR )
            {
                return AnsiString( buffer, bufferLength );
            }
        }
        return {};
    }

    WideString ToWideString( const in6_addr* addr,UInt32 scopeId, UInt16 port )
    {
        if ( addr )
        {
            port = htons( port );
            scopeId = htonl( scopeId );
            wchar_t buffer[ INET6_ADDRSTRLEN ];
            ULONG bufferLength = INET6_ADDRSTRLEN;
            auto rc = RtlIpv6AddressToStringExW( addr, port, scopeId, buffer, &bufferLength );
            if ( rc == NO_ERROR )
            {
                return WideString( buffer, bufferLength );
            }
        }
        return {};
    }

    AnsiString ToAnsiString( const in6_addr* addr, UInt32 scopeId, UInt16 port )
    {
        if ( addr )
        {
            port = htons( port );
            scopeId = htonl( scopeId );
            char buffer[ INET6_ADDRSTRLEN ];
            ULONG bufferLength = INET6_ADDRSTRLEN;
            auto rc = RtlIpv6AddressToStringExA( addr, port, scopeId, buffer, &bufferLength );
            if ( rc == NO_ERROR )
            {
                return AnsiString( buffer, bufferLength );
            }
        }
        return {};
    }
}

namespace Harlinn::Common::Core::Network
{
    class InterfaceInfo : public MIB_IF_ROW2
    {
    public:
        InterfaceInfo( ) = default;
    };

    class InterfaceTable
    {
    public:
        using value_type = InterfaceInfo;
        using size_type = size_t;
    private:
        PMIB_IF_TABLE2 table_ = nullptr;
    public:
        InterfaceTable( )
        {
            GetIfTable2( &table_ );
        }
        ~InterfaceTable( )
        {
            if ( table_ )
            {
                FreeMibTable( table_ );
            }
        }

        size_type size( ) const
        {
            return table_->NumEntries;
        }

        const InterfaceInfo* data( ) const
        {
            return static_cast< const InterfaceInfo* >( table_->Table );
        }

        const InterfaceInfo& operator[]( size_type index ) const
        {
            return static_cast< const InterfaceInfo& >(table_->Table[ index ]);
        }



    };

}


#endif
