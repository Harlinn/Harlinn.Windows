#include "pch.h"
#include <HCCEnvironment.h>
#include <HCCException.h>
#include <HCCLogging.h>
#include <HCCGuid.h>



#pragma comment( lib, "Secur32.lib")

namespace Harlinn::Common::Core::Environment
{
    std::wstring UserName( UserNameFormat nameFormat )
    {
        wchar_t buffer[MAX_PATH + 1];
        DWORD bufferLength = sizeof( buffer )/sizeof(wchar_t);
        auto rc = GetUserNameExW( static_cast<EXTENDED_NAME_FORMAT>( nameFormat ), buffer, &bufferLength );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return std::wstring( buffer, static_cast<size_t>( bufferLength ) );
    }

    std::wstring ComputerName( ComputerNameFormat nameFormat )
    {
        wchar_t buffer[MAX_PATH + 1];
        DWORD bufferLength = sizeof( buffer )/sizeof( wchar_t );
        auto rc = GetComputerNameExW( static_cast<COMPUTER_NAME_FORMAT>( nameFormat ), buffer, &bufferLength );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return std::wstring( buffer, static_cast<size_t>( bufferLength ) );
    }

    std::wstring DomainName( )
    {
        std::wstring result;
        LPWSTR	nameBuffer = nullptr;

        NETSETUP_JOIN_STATUS BufferType;

        NET_API_STATUS rc = NetGetJoinInformation( NULL, &nameBuffer, &BufferType );
        if ( rc == NERR_Success )
        {
            switch ( BufferType )
            {
                case NetSetupWorkgroupName:
                case NetSetupDomainName:
                    result = nameBuffer;
                    break;
            }
            NetApiBufferFree( nameBuffer );
        }
        return result;
    }

    Guid MachineGuid( )
    {
        std::wstring guidAsString;
        const wchar_t* keyName = L"SOFTWARE\\Microsoft\\Cryptography";
        const wchar_t* valueName = L"MachineGuid";
        HKEY keyHandle = nullptr;
        auto rc = RegOpenKeyExW( HKEY_LOCAL_MACHINE, keyName, 0, KEY_READ, &keyHandle );
        if ( rc == ERROR_SUCCESS )
        {
            wchar_t buffer[64];
            DWORD bufferSize = sizeof( buffer );
            rc = RegQueryValueExW( keyHandle, valueName, 0, NULL, (LPBYTE)buffer, &bufferSize );
            if ( rc == ERROR_SUCCESS )
            {
                guidAsString = buffer;
            }
            RegCloseKey( keyHandle );
        }
        if ( guidAsString.length( ) )
        {
            guidAsString.insert( guidAsString.begin( ), L'{' );
            guidAsString.insert( guidAsString.end( ), L'}' );
            return Guid( guidAsString );
        }
        else
        {
            return Guid( );
        }
    }


    std::wstring EnvironmentVariable( const wchar_t* environmentVariableName )
    {
        wchar_t buffer[MAX_PATH + 1];
        constexpr DWORD bufferLength = sizeof( buffer )/sizeof( wchar_t );
        auto rc = GetEnvironmentVariableW( environmentVariableName, buffer, bufferLength );
        if ( !rc )
        {
            auto err = GetLastError( );
            if ( err != ERROR_ENVVAR_NOT_FOUND )
            {
                ThrowOSError( err );
            }
        }
        if ( rc > MAX_PATH + 1 )
        {
            std::wstring s;
            s.resize( rc - 1 );
            rc = GetEnvironmentVariableW( environmentVariableName, s.data(), rc );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return s;
        }
        else
        {
            return std::wstring(buffer, static_cast<size_t>( rc ) );
        }
    }
    std::string EnvironmentVariable( const char* environmentVariableName )
    {
        char buffer[MAX_PATH + 1];
        constexpr DWORD bufferLength = sizeof( buffer ) / sizeof( wchar_t );
        auto rc = GetEnvironmentVariableA( environmentVariableName, buffer, bufferLength );
        if ( !rc )
        {
            auto err = GetLastError( );
            if ( err != ERROR_ENVVAR_NOT_FOUND )
            {
                ThrowOSError( err );
            }
        }
        if ( rc > MAX_PATH + 1 )
        {
            std::string s;
            s.resize( rc - 1 );
            rc = GetEnvironmentVariableA( environmentVariableName, s.data( ), rc );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return s;
        }
        else
        {
            return std::string( buffer, static_cast<size_t>( rc ) );
        }
    }

    std::wstring Where( const wchar_t* fileName )
    {
        wchar_t buffer[2048] = { 0, };
        constexpr DWORD bufferSize = sizeof( buffer ) / sizeof( wchar_t );
        wchar_t* filePart = nullptr;
        auto rc = SearchPathW( nullptr, fileName, nullptr, bufferSize, buffer, &filePart );
        if ( !rc )
        {
            auto lastError = GetLastError( );
            if ( lastError != ERROR_FILE_NOT_FOUND )
            {
                ThrowOSError( lastError );
            }
            return std::wstring( );
        }

        return buffer;
    }

    std::string Where( const char* fileName )
    { 
        char buffer[2048] = { 0, };
        constexpr DWORD bufferSize = sizeof( buffer );
        char* filePart = nullptr;
        auto rc = SearchPathA( nullptr, fileName, nullptr, bufferSize, buffer, &filePart );
        if ( !rc )
        {
            auto lastError = GetLastError( );
            if ( lastError != ERROR_FILE_NOT_FOUND )
            {
                ThrowOSError( lastError );
            }
            return std::string( );
        }
        return buffer;
    }

    std::wstring Where( const wchar_t* path, const wchar_t* fileName )
    {
        wchar_t buffer[2048] = { 0, };
        constexpr DWORD bufferSize = sizeof( buffer ) / sizeof( wchar_t );
        wchar_t* filePart = nullptr;
        auto rc = SearchPathW( path, fileName, nullptr, bufferSize, buffer, &filePart );
        if ( !rc )
        {
            auto lastError = GetLastError( );
            if ( lastError != ERROR_FILE_NOT_FOUND )
            {
                ThrowOSError( lastError );
            }
            return std::wstring( );
        }

        return buffer;
    }
    std::string Where( const char* path, const char* fileName )
    {
        char buffer[2048] = { 0, };
        constexpr DWORD bufferSize = sizeof( buffer );
        char* filePart = nullptr;
        auto rc = SearchPathA( path, fileName, nullptr, bufferSize, buffer, &filePart );
        if ( !rc )
        {
            auto lastError = GetLastError( );
            if ( lastError != ERROR_FILE_NOT_FOUND )
            {
                ThrowOSError( lastError );
            }
            return std::string( );
        }
        return buffer;
    }



    EnvironmentStrings::EnvironmentStrings( )
        : strings_( GetEnvironmentStringsW( ) )
    {

    }
    EnvironmentStrings::~EnvironmentStrings( )
    {
        if ( strings_ )
        {
            FreeEnvironmentStringsW( strings_ );
        }
    }

    bool IsComputerDomainJoined( )
    {
        static std::optional<bool> result;
        if ( result.has_value( ) == false ) [[unlikely]]
        {
            HANDLE handle = nullptr;
            auto rc = DsBindW( nullptr, nullptr, &handle );
            if ( rc == ERROR_SUCCESS )
            {
                DsUnBindW( &handle );
                result = true;
            }
            else
            {
                result = false;
            }
        }
        return result.value( );
    }



    ProcessEntries::ProcessEntries( )
    {
        auto snapshotHandle = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
        if ( snapshotHandle == INVALID_HANDLE_VALUE )
        {
            ThrowLastOSError( );
        }
        PROCESSENTRY32W pe32;
        pe32.dwSize = sizeof( PROCESSENTRY32 );

        if ( !Process32FirstW( snapshotHandle, &pe32 ) )
        {
            CloseHandle( snapshotHandle );
            ThrowLastOSError( );
        }
        else
        {
            do
            {
                ProcessEntry entry( pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.cntThreads, pe32.szExeFile );
                emplace( entry.ProcessId(), entry );
            } while( Process32Next( snapshotHandle, &pe32 ) );
        }

        CloseHandle( snapshotHandle );
    }

    bool ProcessEntries::IsChildOf( DWORD childProcessId, DWORD parentProcessId ) const
    {
        if ( !childProcessId )
        {
            HCC_THROW( ArgumentException, L"childProcessId" );
        }
        auto it = find( childProcessId );
        if ( it == end( ) )
        {
            HCC_THROW( ArgumentException, L"childProcessId" );
        }
        while ( it != end( ) )
        {
            if ( it->second.ParentProcessId( ) == parentProcessId )
            {
                return true;
            }
            it = find( it->second.ParentProcessId( ) );
        }
        return false;
    }

    bool ProcessEntries::IsChildOf( DWORD childProcessId, const wchar_t* parentExecutable ) const
    {
        if ( !childProcessId )
        {
            HCC_THROW( ArgumentException, L"childProcessId" );
        }
        if ( !parentExecutable || !parentExecutable[0] )
        {
            HCC_THROW( ArgumentException, L"parentExecutable" );
        }

        auto it = find( childProcessId );
        if ( it == end( ) )
        {
            HCC_THROW( ArgumentException, L"childProcessId" );
        }
        it = find( it->second.ParentProcessId( ) );
        while( it != end() )
        {
            if ( _wcsicmp( it->second.Executable( ), parentExecutable ) == 0 )
            {
                return true;
            }
            it = find( it->second.ParentProcessId( ) );
        }
        return false;
    }

    bool ProcessEntries::IsChildOf( DWORD parentProcessId ) const
    {
        DWORD currentProcessId = GetCurrentProcessId( );
        return IsChildOf( currentProcessId, parentProcessId );
    }

    bool ProcessEntries::IsChildOf( const wchar_t* parentExecutable ) const
    {
        DWORD currentProcessId = GetCurrentProcessId( );
        return IsChildOf( currentProcessId, parentExecutable );
    }

    bool IsService( )
    {
        ProcessEntries processEntries;
        auto result = processEntries.IsChildOf( L"services.exe" );
        return result;
    }

    size_t ProcessorCount( )
    {
        SYSTEM_INFO systemInfo;
        GetSystemInfo( &systemInfo );
        return systemInfo.dwNumberOfProcessors;
    }

}