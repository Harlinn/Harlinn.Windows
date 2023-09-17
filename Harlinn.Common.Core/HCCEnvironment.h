#pragma once
#ifndef __HCCENVIRONMENT_H__
#define __HCCENVIRONMENT_H__

#include <HCCDef.h>
#include <HCCString.h>
#include <HCCDateTime.h>

#pragma comment(lib,"Netapi32.lib")
#pragma comment(lib,"Ntdsapi.lib")

namespace Harlinn::Common::Core::Security
{
    class SecurityId;
}

namespace Harlinn::Common::Core::Environment
{
    
    enum class UserNameFormat
    {
        // unknown name type
        Unknown = NameUnknown,

        // CN=John Doe, OU=Software, OU=Engineering, O=Widget, C=US
        FullyQualifiedDN = NameFullyQualifiedDN,

        /// <summary>
        /// Example: Engineering\JohnDoe
        /// </summary>
        SamCompatible = NameSamCompatible,

        // Probably "John Doe" but could be something else.  I.e. The
        // display name is not necessarily the defining RDN.
        Display = NameDisplay,


        // String-ized GUID as returned by IIDFromString().
        // eg: {4fa050f0-f561-11cf-bdd9-00aa003a77b6}
        UniqueId = NameUniqueId,

        // engineering.widget.com/software/John Doe
        Canonical = NameCanonical,

        // someone@example.com
        UserPrincipal = NameUserPrincipal,

        // Same as NameCanonical except that rightmost '/' is
        // replaced with '\n' - even in domain-only case.
        // eg: engineering.widget.com/software\nJohn Doe
        CanonicalEx = NameCanonicalEx,

        // www/srv.engineering.com/engineering.com
        ServicePrincipal = NameServicePrincipal,

        // DNS domain name + SAM username
        // eg: engineering.widget.com\JohnDoe
        DnsDomain = NameDnsDomain,

        GivenName = NameGivenName,
        Surname = NameSurname
    };

    HCC_EXPORT WideString UserName( UserNameFormat nameFormat );

    enum class ComputerNameFormat
    {
        NetBIOS = ComputerNameNetBIOS,
        DnsHostname = ComputerNameDnsHostname,
        DnsDomain = ComputerNameDnsDomain,
        DnsFullyQualified = ComputerNameDnsFullyQualified,
        PhysicalNetBIOS = ComputerNamePhysicalNetBIOS,
        PhysicalDnsHostname = ComputerNamePhysicalDnsHostname,
        PhysicalDnsDomain = ComputerNamePhysicalDnsDomain,
        PhysicalDnsFullyQualified = ComputerNamePhysicalDnsFullyQualified
    };

    HCC_EXPORT WideString ComputerName( ComputerNameFormat nameFormat );
    HCC_EXPORT WideString DomainName( );
    HCC_EXPORT Guid MachineGuid( );

    HCC_EXPORT WideString EnvironmentVariable( const wchar_t* environmentVariableName );
    HCC_EXPORT AnsiString EnvironmentVariable( const char* environmentVariableName );

    HCC_EXPORT WideString Expand( const wchar_t* str );
    template<SimpleWideStringLike StringT>
    WideString Expand( const StringT& str )
    {
        return Expand( str.c_str( ) );
    }

    template<typename T>
    requires IsStdOptional<T> && std::is_same_v<WideString, typename T::value_type>
    T Expand( const T& strOpt )
    {
        if ( strOpt )
        {
            return Expand( strOpt.value( ) );
        }
        return strOpt;
    }

    HCC_EXPORT WideString Where( const wchar_t* fileName );
    HCC_EXPORT AnsiString Where( const char* fileName );

    inline WideString Where( const WideString& fileName )
    {
        return Where( fileName.c_str() );
    }
    inline AnsiString Where( const AnsiString& fileName )
    {
        return Where( fileName.c_str( ) );
    }

    HCC_EXPORT WideString Where( const wchar_t* path, const wchar_t* fileName );
    inline WideString Where( const wchar_t* path, const WideString& fileName )
    {
        return Where( path, fileName.c_str() );
    }
    inline WideString Where( const WideString& path, const wchar_t* fileName )
    {
        return Where( path.c_str(), fileName );
    }
    inline WideString Where( const WideString& path, const WideString& fileName )
    {
        return Where( path.c_str( ), fileName );
    }
    HCC_EXPORT AnsiString Where( const char* path, const char* fileName );
    inline AnsiString Where( const char* path, const AnsiString& fileName )
    {
        return Where( path, fileName.c_str( ) );
    }
    inline AnsiString Where( const AnsiString& path, const char* fileName )
    {
        return Where( path.c_str( ), fileName );
    }
    inline AnsiString Where( const AnsiString& path, const AnsiString& fileName )
    {
        return Where( path.c_str( ), fileName );
    }

    class EnvironmentStrings
    {
        wchar_t* strings_;
    public:
        HCC_EXPORT EnvironmentStrings( );
        HCC_EXPORT ~EnvironmentStrings( );

        EnvironmentStrings( const EnvironmentStrings& other ) = delete;
        EnvironmentStrings( EnvironmentStrings&& other ) = delete;
        EnvironmentStrings& operator = ( const EnvironmentStrings& other ) = delete;
        EnvironmentStrings& operator = ( EnvironmentStrings&& other ) = delete;


        const wchar_t* data( ) const noexcept
        {
            return strings_;
        }

        size_t size( ) const noexcept
        {
            size_t result = 0;
            if ( strings_ )
            {
                auto* ptr = strings_;
                while ( *ptr )
                {
                    auto length = wcslen( ptr );
                    if ( length )
                    {
                        result++;
                        ptr += length + 1;
                    }
                }
            }
            return result;
        }

        const wchar_t* at( size_t index )
        {
            size_t current = 0;
            if ( strings_ )
            {
                auto* ptr = strings_;
                while ( *ptr )
                {
                    if ( current == index )
                    {
                        return ptr;
                    }
                    auto length = wcslen( ptr );
                    if ( length )
                    {
                        current++;
                        ptr += length + 1;
                    }
                }
            }
            return nullptr;
        }

    };

    class ProcessEntry
    {
        DWORD processId_;
        DWORD parentProcessId_;
        DWORD threadCount_;
        wchar_t executable_[MAX_PATH];
    public:
        ProcessEntry( )
            : processId_( 0 ), parentProcessId_( 0 ), threadCount_( 0 ), executable_{}
        {
        }

        ProcessEntry( DWORD processId, DWORD parentProcessId, DWORD threadCount, const wchar_t* executable )
            : processId_( processId ), parentProcessId_( parentProcessId ), threadCount_( threadCount ), executable_{}
        {
            wcscpy_s( executable_, executable );
            CharLowerW( executable_ );
        }

        DWORD ProcessId( ) const noexcept
        {
            return processId_;
        }
        DWORD ParentProcessId( ) const noexcept
        {
            return parentProcessId_;
        }
        DWORD ThreadCount( ) const noexcept
        {
            return threadCount_;
        }

        const wchar_t* Executable( ) const noexcept
        {
            return executable_;
        }

    };

    class ProcessEntries : public std::unordered_map<DWORD, ProcessEntry>
    {
    public:
        using MapType = std::unordered_map<DWORD, ProcessEntry>;
        using iterator = MapType::iterator;
        using const_iterator = MapType::const_iterator;
        using size_type = MapType::size_type;
    public:
        HCC_EXPORT ProcessEntries( );

        ProcessEntries( const ProcessEntries& other ) = delete;
        ProcessEntries( ProcessEntries&& other ) = delete;
        ProcessEntries& operator = ( const ProcessEntries& other ) = delete;
        ProcessEntries& operator = ( ProcessEntries&& other ) = delete;

        HCC_EXPORT bool IsChildOf( DWORD childProcessId, DWORD parentProcessId ) const;
        HCC_EXPORT bool IsChildOf( DWORD childProcessId, const wchar_t* parentExecutable ) const;
        HCC_EXPORT bool IsChildOf( DWORD parentProcessId ) const;
        HCC_EXPORT bool IsChildOf( const wchar_t* parentExecutable ) const;

    };

    class ModuleEntry
    {

    };

    class ModuleEntries
    {

    };




    HCC_EXPORT bool IsService( );
    HCC_EXPORT bool IsUserInteractive( );
    HCC_EXPORT size_t ProcessorCount( );


    




}

#endif
