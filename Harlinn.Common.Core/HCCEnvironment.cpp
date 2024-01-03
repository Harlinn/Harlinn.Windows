/*
   Copyright 2024 Espen Harlinn

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

#include "pch.h"
#include <HCCEnvironment.h>
#include <HCCException.h>
#include <HCCLogging.h>
#include <HCCGuid.h>

#pragma comment( lib, "Secur32.lib")

namespace Harlinn::Common::Core::Environment
{
    WideString UserName( UserNameFormat nameFormat )
    {
        wchar_t buffer[MAX_PATH + 1];
        DWORD bufferLength = sizeof( buffer )/sizeof(wchar_t);
        auto rc = GetUserNameExW( static_cast<EXTENDED_NAME_FORMAT>( nameFormat ), buffer, &bufferLength );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return WideString( buffer, static_cast<size_t>( bufferLength ) );
    }

    WideString ComputerName( ComputerNameFormat nameFormat )
    {
        wchar_t buffer[MAX_PATH + 1];
        DWORD bufferLength = sizeof( buffer )/sizeof( wchar_t );
        auto rc = GetComputerNameExW( static_cast<COMPUTER_NAME_FORMAT>( nameFormat ), buffer, &bufferLength );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return WideString( buffer, static_cast<size_t>( bufferLength ) );
    }

    WideString DomainName( )
    {
        WideString result;
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
        WideString guidAsString;
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


    WideString EnvironmentVariable( const wchar_t* environmentVariableName )
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
            WideString s;
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
            return WideString(buffer, static_cast<size_t>( rc ) );
        }
    }
    AnsiString EnvironmentVariable( const char* environmentVariableName )
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
            AnsiString s;
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
            return AnsiString( buffer, static_cast<size_t>( rc ) );
        }
    }

    WideString Expand( const wchar_t* str )
    {
        constexpr size_t bufferSize = 512;
        wchar_t buffer[ bufferSize ];
        size_t len = ExpandEnvironmentStringsW( str, buffer, static_cast<DWORD>(bufferSize) );
        if ( !len )
        {
            ThrowLastOSError( );
        }
        if ( len > bufferSize )
        {
            WideString result;
            result.SetLength( len - 1 );
            len = ExpandEnvironmentStringsW( str, buffer, static_cast< DWORD >( len ) );
            if ( !len )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        else
        {
            WideString result(buffer, len - 1);
            return result;
        }
    }

    WideString Where( const wchar_t* fileName )
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
            return WideString( );
        }

        return buffer;
    }

    AnsiString Where( const char* fileName )
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
            return {};
        }
        return buffer;
    }

    WideString Where( const wchar_t* path, const wchar_t* fileName )
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
            return WideString( );
        }

        return buffer;
    }
    AnsiString Where( const char* path, const char* fileName )
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
            return {};
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
        return IsUserInteractive( ) == false;
    }

    bool IsUserInteractive( )
    {
        bool result = false;

        HWINSTA processWindowStation = GetProcessWindowStation( );
        if ( processWindowStation != nullptr )
        {
            USEROBJECTFLAGS uof = { 0 };
            auto rc = GetUserObjectInformationW( processWindowStation, UOI_FLAGS, &uof, sizeof( USEROBJECTFLAGS ), NULL );
            if ( !rc )
            {
                ThrowLastOSError( );
            }

            if ( uof.dwFlags & WSF_VISIBLE )
            {
                result = true;
            }
        }
        return result;
    }


    size_t ProcessorCount( )
    {
        SYSTEM_INFO systemInfo;
        GetSystemInfo( &systemInfo );
        return systemInfo.dwNumberOfProcessors;
    }

}