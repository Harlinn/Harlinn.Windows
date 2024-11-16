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
#include <HCCIO.h>
#include <HCCIOCompletionPort.h>
#include <HCCLogging.h>
#include <HCCException.h>
#include <HCCString.h>
#include <HCCMemory.h>

namespace Harlinn::Common::Core::IO
{
    namespace
    {
        wchar_t TrimEndChars[] = { 0x9, 0xA, 0xB, 0xC, 0xD, 0x20, 0x85, 0xA0 };

        wchar_t RealInvalidPathChars[] = { '\"', '<', '>', '|', '\0', 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

        wchar_t InvalidFileNameChars[] = { '\"', '<', '>', '|', '\0', 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, ':', '*', '?', '\\', '/' };


        inline void CheckInvalidPathChars( const WideString& path )
        {
            for ( auto c : path )
            {
                if ( c == '\"' || c == '<' || c == '>' || c == '|' || c < 32 )
                {
                    throw ArgumentException( "Invalid path character" );
                }
            }
        }
    }

    // -----------------------------------------------------------------
    // Path
    // -----------------------------------------------------------------


    size_t Path::CommonPrefix( const wchar_t* path1, const wchar_t* path2, wchar_t* commonPrefix )
    {
        size_t length = 0;
        LPWSTR pathIter1 = const_cast<LPWSTR>( path1 );
        LPWSTR pathIter2 = const_cast<LPWSTR>( path2 );


        if ( commonPrefix )
        {
            *commonPrefix = '\0';
        }

        if ( !path1 || !path2 )
            return 0;

        // Handle roots first 
        if ( IsUNC( path1 ) )
        {
            if ( !IsUNC( path2 ) )
            {
                return 0;
            }
            pathIter1 += 2;
            pathIter2 += 2;
        }
        else if ( IsUNC( path2 ) )
        {
            // We already know that file1 is not UNC 
            return 0;
        }
        do
        {
            // Update length 
            if ( ( !*pathIter1 || *pathIter1 == '\\' ) && ( !*pathIter2 || *pathIter2 == '\\' ) )
            {
                // Common to this point 
                length = pathIter1 - path1;
            }


            // Strings differ at this point 
            if ( !*pathIter1 || ( CharLowerW( static_cast<LPWSTR>( pathIter1 ) ) != CharLowerW( static_cast<LPWSTR>( pathIter2 ) ) ) )
                break;

            pathIter1++;
            pathIter2++;
        } while ( 1 );

        if ( length == 2 )
        {
            // Feature/Bug compatible with Win32 
            length++;
        }

        if ( length && commonPrefix )
        {
            memcpy( commonPrefix, path1, length * sizeof( WCHAR ) );
            commonPrefix[length] = '\0';
        }
        return length;
    }






    // -----------------------------------------------------------------
    // File
    // -----------------------------------------------------------------
    namespace
    {
        bool ExistsLockedOrShared( const wchar_t* path )
        {
            WIN32_FIND_DATAW FindData;
            HANDLE hFind;
            bool result = false;
            // Either the file is locked/share_exclusive or we got an access denied 
            hFind = FindFirstFileW( path, &FindData );
            if ( hFind != INVALID_HANDLE_VALUE )
            {
                FindClose( hFind );
                result = ( FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == 0;
            }
            return result;
        }
        bool ExistsLockedOrShared( const char* path )
        {
            WIN32_FIND_DATAA FindData;
            HANDLE hFind;
            bool result = false;
            // Either the file is locked/share_exclusive or we got an access denied 
            hFind = FindFirstFileA( path, &FindData );
            if ( hFind != INVALID_HANDLE_VALUE )
            {
                FindClose( hFind );
                result = ( FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == 0;
            }
            return result;
        }
    }

    void File::Delete( const wchar_t* filePath )
    {
        auto rc = DeleteFileW( filePath );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
    }

    void File::Delete( const char* filePath )
    {
        auto rc = DeleteFileA( filePath );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
    }


    bool File::DeleteIfExist( const wchar_t* filePath )
    {
        auto rc = DeleteFileW( filePath );
        if ( !rc )
        {
            auto errorCode = GetLastError( );
            if ( errorCode == ERROR_FILE_NOT_FOUND )
            {
                return false;
            }
            ThrowLastOSError( );
        }
        return true;
    }

    bool File::DeleteIfExist( const char* filePath )
    {
        auto rc = DeleteFileA( filePath );
        if ( !rc )
        {
            auto errorCode = GetLastError( );
            if ( errorCode == ERROR_FILE_NOT_FOUND )
            {
                return false;
            }
            ThrowLastOSError( );
        }
        return true;
    }


    bool File::Exist( const wchar_t* path )
    {
        if ( path && path[0] )
        {
            auto attrs = GetFileAttributesW( path );
            if ( attrs != INVALID_FILE_ATTRIBUTES )
            {
                if ( ( attrs & FILE_ATTRIBUTE_DIRECTORY ) == 0 )
                {
                    return true;
                }
            }
            else
            {
                auto lastError = GetLastError( );
                if ( ( lastError != ERROR_FILE_NOT_FOUND ) &&
                    ( lastError != ERROR_PATH_NOT_FOUND ) &&
                    ( lastError != ERROR_INVALID_NAME ) )
                {
                    return ExistsLockedOrShared( path );
                }

            }
        }
        return false;
    }

    bool File::Exist( const char* path )
    {
        if ( path && path[0] )
        {
            auto attrs = GetFileAttributesA( path );
            if ( attrs != INVALID_FILE_ATTRIBUTES )
            {
                if ( ( attrs & FILE_ATTRIBUTE_DIRECTORY ) == 0 )
                {
                    return true;
                }
            }
            else
            {
                auto lastError = GetLastError( );
                if ( ( lastError != ERROR_FILE_NOT_FOUND ) &&
                    ( lastError != ERROR_PATH_NOT_FOUND ) &&
                    ( lastError != ERROR_INVALID_NAME ) )
                {
                    return ExistsLockedOrShared( path );
                }

            }
        }
        return false;
    }


    UInt64 File::Size( const wchar_t* path )
    {
        WIN32_FILE_ATTRIBUTE_DATA attributeData;
        auto rc = GetFileAttributesExW( path, GetFileExInfoStandard, &attributeData );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return (static_cast<UInt64>( attributeData.nFileSizeHigh ) << 32 ) + static_cast<UInt64>( attributeData.nFileSizeLow );
    }
    UInt64 File::Size( const char* path )
    {
        WIN32_FILE_ATTRIBUTE_DATA attributeData;
        auto rc = GetFileAttributesExA( path, GetFileExInfoStandard, &attributeData );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return ( static_cast<UInt64>( attributeData.nFileSizeHigh ) << 32 ) + static_cast<UInt64>( attributeData.nFileSizeLow );
    }

    


    bool File::Search( const WideString& directoryPath, const WideString& filename, bool recurseSubdirectories, WideString& result )
    {
        if ( directoryPath.empty( ) == false )
        {
            if ( directoryPath.ends_with( L'\\' ) || directoryPath.ends_with( L'/' ) )
            {
                auto searchPattern = directoryPath + L"*";
                WIN32_FIND_DATAW findData{};
                auto findHandle = FindFirstFileW( searchPattern.c_str( ), &findData );
                if ( findHandle == INVALID_HANDLE_VALUE )
                {
                    auto error = GetLastError( );
                    if ( error != ERROR_FILE_NOT_FOUND )
                    {
                        ThrowOSError( error );
                    }
                    return false;
                }
                do
                {
                    if ( (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 )
                    {
                        if ( _wcsnicmp( findData.cFileName, filename.c_str( ), filename.length( ) ) == 0 )
                        {
                            result = directoryPath + findData.cFileName;
                            FindClose( findHandle );
                            return true;
                        }
                    }
                    else if( recurseSubdirectories )
                    {
                        auto subdirectoryPath = directoryPath + findData.cFileName + L"\\";
                        if ( Search( subdirectoryPath, filename, recurseSubdirectories, result ) )
                        {
                            FindClose( findHandle );
                            return true;
                        }
                    }
                } while ( FindNextFileW( findHandle, &findData ) );
                auto error = GetLastError( );
                if ( error != ERROR_FILE_NOT_FOUND )
                {
                    ThrowOSError( error );
                }
                FindClose( findHandle );
                return false;
            }
            else
            {
                return Search( directoryPath + L"\\", filename, recurseSubdirectories, result );
            }
        }
        else
        {
            return Search( Directory::Current( ), filename, recurseSubdirectories, result );
        }
    }
    bool File::Search( const AnsiString& directoryPath, const AnsiString& filename, bool recurseSubdirectories, AnsiString& result )
    {
        if ( directoryPath.empty( ) == false )
        {
            if ( directoryPath.ends_with( '\\' ) || directoryPath.ends_with( '/' ) )
            {
                auto searchPattern = directoryPath + "*";
                WIN32_FIND_DATAA findData{};
                auto findHandle = FindFirstFileA( searchPattern.c_str( ), &findData );
                if ( findHandle == INVALID_HANDLE_VALUE )
                {
                    auto error = GetLastError( );
                    if ( error != ERROR_FILE_NOT_FOUND )
                    {
                        ThrowOSError( error );
                    }
                    return false;
                }
                do
                {
                    if ( (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 )
                    {
                        if ( _strnicmp( findData.cFileName, filename.c_str( ), filename.length( ) ) == 0 )
                        {
                            result = directoryPath + findData.cFileName;
                            FindClose( findHandle );
                            return true;
                        }
                    }
                    else if ( recurseSubdirectories )
                    {
                        auto subdirectoryPath = directoryPath + findData.cFileName + "\\";
                        if ( Search( subdirectoryPath, filename, recurseSubdirectories, result ) )
                        {
                            FindClose( findHandle );
                            return true;
                        }
                    }
                } while ( FindNextFileA( findHandle, &findData ) );
                auto error = GetLastError( );
                if ( error != ERROR_FILE_NOT_FOUND )
                {
                    ThrowOSError( error );
                }
                FindClose( findHandle );
                return false;
            }
            else
            {
                return Search( directoryPath + "\\", filename, recurseSubdirectories, result );
            }
        }
        else
        {
            return Search( Directory::CurrentA( ), filename, recurseSubdirectories, result );
        }
    }


    void File::ReadAllLines( const AnsiString& filePath, std::vector<AnsiString>& destination )
    {
        destination.clear( );
        ReadAndAppendAllLinesTo( filePath, destination );
    }

    void File::ReadAndAppendAllLinesTo( const AnsiString& filePath, std::vector<AnsiString>& destination )
    {
        FileStream fileStream( filePath.c_str( ), FileAccess::Read, FileShare::Read, nullptr, FileMode::Open, FileAttributes::Normal, FileOptions::Default );
        fileStream.ReadFile( destination );
    }

    void File::WriteAllLines( const AnsiString& filePath, const std::vector<AnsiString>& contents )
    {
        FileStream fileStream( filePath.c_str( ), FileAccess::ReadWrite, FileShare::None, nullptr, FileMode::OpenOrCreate, FileAttributes::Normal, FileOptions::SequentialScan );
        fileStream.SetSize( 0 );
        fileStream.WriteFile( contents );
    }

    void File::ReadAllText( const AnsiString& filePath, AnsiString& destination )
    {
        destination.clear( );
        ReadAndAppendAllTextTo( filePath, destination );
    }

    void File::ReadAndAppendAllTextTo( const AnsiString& filePath, AnsiString& destination )
    {
        FileStream fileStream( filePath.c_str( ), FileAccess::Read, FileShare::Read, nullptr, FileMode::Open, FileAttributes::Normal, FileOptions::Default );
        fileStream.ReadFile( destination );
    }
    void File::ReadAndAppendAllTextTo( const WideString& filePath, AnsiString& destination )
    {
        FileStream fileStream( filePath.c_str( ), FileAccess::Read, FileShare::Read, nullptr, FileMode::Open, FileAttributes::Normal, FileOptions::Default );
        fileStream.ReadFile( destination );
    }

    void File::ReadAndAppendAllBytesTo( const AnsiString& filePath, std::vector<Byte>& destination )
    {
        FileStream fileStream( filePath.c_str( ), FileAccess::Read, FileShare::Read, nullptr, FileMode::Open, FileAttributes::Normal, FileOptions::Default );
        fileStream.ReadFile( destination );
    }

    void File::ReadAndAppendAllBytesTo( const WideString& filePath, std::vector<Byte>& destination )
    {
        FileStream fileStream( filePath.c_str( ), FileAccess::Read, FileShare::Read, nullptr, FileMode::Open, FileAttributes::Normal, FileOptions::Default );
        fileStream.ReadFile( destination );
    }


    void File::WriteAllText( const AnsiString& filePath, const AnsiString& contents )
    {
        FileStream fileStream( filePath.c_str( ), FileAccess::ReadWrite, FileShare::None, nullptr, FileMode::OpenOrCreate, FileAttributes::Normal, FileOptions::SequentialScan );
        fileStream.SetSize( 0 );
        fileStream.Write( contents.data(), contents.size() );
    }
    void File::WriteAllText( const WideString& filePath, const AnsiString& contents )
    {
        FileStream fileStream( filePath.c_str( ), FileAccess::ReadWrite, FileShare::None, nullptr, FileMode::OpenOrCreate, FileAttributes::Normal, FileOptions::SequentialScan );
        fileStream.SetSize( 0 );
        fileStream.Write( contents.data( ), contents.size( ) );
    }
    void File::WriteAllBytes( const AnsiString& filePath, const std::vector<Byte>& contents )
    {
        FileStream fileStream( filePath.c_str( ), FileAccess::ReadWrite, FileShare::None, nullptr, FileMode::OpenOrCreate, FileAttributes::Normal, FileOptions::SequentialScan );
        fileStream.SetSize( 0 );
        fileStream.Write( contents.data( ), contents.size( ) );
    }
    void File::WriteAllBytes( const WideString& filePath, const std::vector<Byte>& contents )
    {
        FileStream fileStream( filePath.c_str( ), FileAccess::ReadWrite, FileShare::None, nullptr, FileMode::OpenOrCreate, FileAttributes::Normal, FileOptions::SequentialScan );
        fileStream.SetSize( 0 );
        fileStream.Write( contents.data( ), contents.size( ) );
    }

    WideString File::GetExecutableW( )
    {
        wchar_t buffer[ (2*MAX_PATH) + 1 ] = { 0, };
        GetModuleFileNameW( nullptr, buffer, sizeof( buffer ) / sizeof( wchar_t ) );
        return WideString(buffer);
    }
    AnsiString File::GetExecutableA( )
    {
        return ToAnsiString( GetExecutableW( ) );
    }




    // -----------------------------------------------------------------
    // Directory
    // -----------------------------------------------------------------
    WideString Directory::GetTemporary()
    {
        wchar_t buffer[MAX_PATH + 2] = {};
        auto rc = GetTempPathW(MAX_PATH + 1, buffer);
        return WideString(buffer, static_cast<size_t>(rc));
    }

    AnsiString Directory::GetTemporaryA()
    {
        char buffer[MAX_PATH + 2] = {};
        auto rc = GetTempPathA(MAX_PATH + 1, buffer);
        return AnsiString(buffer, static_cast<size_t>(rc));
    }


    WideString Directory::GetExecutableDirectoryW( )
    {
        wchar_t buffer[MAX_PATH + 1] = { 0, };
        GetModuleFileNameW( nullptr, buffer, sizeof( buffer ) / sizeof( wchar_t ) );
        return Path::GetParentDirectory( buffer );
    }
    AnsiString Directory::GetExecutableDirectoryA( )
    {
        return ToAnsiString( GetExecutableDirectoryW( ) );
    }

    WideString Directory::Current( )
    {
        wchar_t buffer[MAX_PATH + 1] = { 0, };
        auto length = ::GetCurrentDirectoryW( sizeof( buffer ) / sizeof( wchar_t ), buffer );
        if ( length == 0 )
        {
            ThrowLastOSError( );
        }
        if ( length > ( sizeof( buffer ) / sizeof( wchar_t ) ) )
        {
            WideString result;
            result.resize( length - 1 );
            length = ::GetCurrentDirectoryW( length, result.data( ) );
            if ( length == 0 )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        else
        {
            WideString result( buffer, length );
            return result;
        }
    }
    AnsiString Directory::CurrentA( )
    {
        char buffer[MAX_PATH + 1] = { 0, };
        auto length = ::GetCurrentDirectoryA( sizeof( buffer ), buffer );
        if ( length == 0 )
        {
            ThrowLastOSError( );
        }
        if ( length > sizeof( buffer ) )
        {
            AnsiString result;
            result.resize( length - 1 );
            length = ::GetCurrentDirectoryA( length, result.data( ) );
            if ( length == 0 )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        else
        {
            AnsiString result( buffer, length );
            return result;
        }
    }


    bool Directory::Exist( const wchar_t* path )
    {
        if ( path )
        {
            auto attrs = GetFileAttributesW( path );
            if ( attrs != INVALID_FILE_ATTRIBUTES )
            {
                if ( ( attrs & FILE_ATTRIBUTE_DIRECTORY ) != 0 )
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool Directory::Exist( const char* path )
    {
        if ( path )
        {
            auto attrs = GetFileAttributesA( path );
            if ( attrs != INVALID_FILE_ATTRIBUTES )
            {
                if ( ( attrs & FILE_ATTRIBUTE_DIRECTORY ) != 0 )
                {
                    return true;
                }
            }
        }
        return false;
    }


    void Directory::Create( const wchar_t* directoryPath )
    {
        auto rc = SHCreateDirectoryExW( 0, directoryPath, nullptr );
        if ( rc != ERROR_SUCCESS && rc != ERROR_ALREADY_EXISTS )
        {
            ThrowOSError( rc );
        }
    }
    void Directory::Create( const char* directoryPath )
    {
        auto rc = SHCreateDirectoryExA( 0, directoryPath, nullptr );
        if ( rc != ERROR_SUCCESS && rc != ERROR_ALREADY_EXISTS )
        {
            ThrowOSError( rc );
        }
    }
    // -----------------------------------------------------------------
    // FileStream
    // -----------------------------------------------------------------

    HANDLE FileStream::Create( LPCWSTR fileName, FileAccess fileAccess, FileShare fileShare, LPSECURITY_ATTRIBUTES lpSecurityAttributes, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions )
    {
        DWORD creationDisposition = 0;
        if ( fileMode != FileMode::Append )
        {
            creationDisposition = DWORD( fileMode );
        }
        else
        {
            creationDisposition = DWORD( FileMode::OpenOrCreate );
        }
        DWORD access = DWORD( fileAccess );
        if ( access & FILE_READ_ACCESS )
        {
            access |= GENERIC_READ;
        }
        if ( access & FILE_WRITE_ACCESS )
        {
            access |= GENERIC_WRITE;
        }

        DWORD flagsAndAttributes = DWORD( attributes ) | DWORD( fileOptions );
        HANDLE result = ::CreateFileW( fileName,
            access,
            DWORD( fileShare ), 
            lpSecurityAttributes, 
            creationDisposition, 
            flagsAndAttributes, nullptr );

        if ( result == INVALID_HANDLE_VALUE )
        {
            ThrowLastOSError( );
        }

        if ( fileMode == FileMode::Append )
        {
            LARGE_INTEGER liDistanceToMove;
            liDistanceToMove.QuadPart = 0;
            if ( SetFilePointerEx( result, liDistanceToMove, nullptr, FILE_END ) == 0 )
            {
                CloseHandle( result );
                result = INVALID_HANDLE_VALUE;
                ThrowLastOSError( );
            }
        }
        return result;
    }
    HANDLE FileStream::Create( LPCSTR fileName, FileAccess fileAccess, FileShare fileShare, LPSECURITY_ATTRIBUTES lpSecurityAttributes, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions )
    {
        DWORD creationDisposition = 0;
        if ( fileMode != FileMode::Append )
        {
            creationDisposition = DWORD( fileMode );
        }
        else
        {
            creationDisposition = DWORD( FileMode::OpenOrCreate );
        }
        DWORD access = DWORD( fileAccess );
        if ( access & FILE_READ_ACCESS )
        {
            access |= GENERIC_READ;
        }
        if ( access & FILE_WRITE_ACCESS )
        {
            access |= GENERIC_WRITE;
        }

        DWORD flagsAndAttributes = DWORD( attributes ) | DWORD( fileOptions );
        HANDLE result = ::CreateFileA( fileName,
            access,
            DWORD( fileShare ),
            lpSecurityAttributes,
            creationDisposition,
            flagsAndAttributes, nullptr );

        if ( result == INVALID_HANDLE_VALUE )
        {
            ThrowLastOSError( );
        }

        if ( fileMode == FileMode::Append )
        {
            LARGE_INTEGER liDistanceToMove;
            liDistanceToMove.QuadPart = 0;
            if ( SetFilePointerEx( result, liDistanceToMove, nullptr, FILE_END ) == 0 )
            {
                CloseHandle( result );
                result = INVALID_HANDLE_VALUE;
                ThrowLastOSError( );
            }
        }

        return result;
    }

    void FileStream::ReadFile( std::vector<AnsiString>& destination ) const
    {
        auto fileSize = Size( );
        if ( fileSize )
        {
            FileMapping fileMapping( Handle( ), PageFlags::Readonly, SectionFlags::None, 0 );
            FileMapping::View view( fileMapping, FileMap::Read, 0, fileSize );
            view.AppendTo( destination );
        }
    }
    void FileStream::ReadFile( AnsiString& destination ) const
    {
        auto fileSize = Size( );
        if ( fileSize )
        {
            FileMapping fileMapping( Handle( ), PageFlags::Readonly, SectionFlags::None, 0 );
            FileMapping::View view( fileMapping, FileMap::Read, 0, fileSize );
            view.AppendTo( destination );
        }
    }
    void FileStream::ReadFile( std::vector<Byte>& destination ) const
    {
        auto fileSize = Size( );
        if ( fileSize )
        {
            FileMapping fileMapping( Handle( ), PageFlags::Readonly, SectionFlags::None, 0 );
            FileMapping::View view( fileMapping, FileMap::Read, 0, fileSize );
            view.AppendTo( destination );
        }
    }

    void FileStream::WriteFile( const std::vector<AnsiString>& contents ) const
    {
        Seek( 0, SeekOrigin::StartOfFile );
        SetSize( 0 );
        static char eol[] = { '\r','\n' };
        WriteBuffer<FileStream> writeBuffer( *this );
        for ( const auto& line : contents )
        {
            writeBuffer.Write( line.c_str( ), line.size( ) );
            writeBuffer.Write( eol, 2 );
        }
        writeBuffer.Flush( );
    }

    void FileStream::WriteFile( const AnsiString& contents ) const
    {
        Seek( 0, SeekOrigin::StartOfFile );
        SetSize( 0 );
        Write( contents.c_str(), contents.size() );
    }

    void FileStream::WriteFile( const std::vector<Byte>& contents ) const
    {
        Seek( 0, SeekOrigin::StartOfFile );
        SetSize( 0 );
        Write( contents.data( ), contents.size( ) );
    }


    // -----------------------------------------------------------------
    // IOCompletionPort
    // -----------------------------------------------------------------
    IOCompletionPort::IOCompletionPort( DWORD numberOfConcurrentThreads )
        : handle_( INVALID_HANDLE_VALUE )
    {
        auto handle = CreateIoCompletionPort( INVALID_HANDLE_VALUE, nullptr, 0, numberOfConcurrentThreads );
        if ( handle == nullptr )
        {
            ThrowLastOSError( );
        }
        handle_ = handle;
    }


    void IOCompletionPort::Bind( HANDLE iohandle, void* data ) const
    {
        auto handle = CreateIoCompletionPort( iohandle, handle_, reinterpret_cast<ULONG_PTR>( data ), 0 );
        if ( handle == nullptr )
        {
            ThrowLastOSError( );
        }
    }

    void IOCompletionPort::Post( DWORD numberOfBytesTransferred, void* data, OVERLAPPED* overlapped ) const
    {
        auto rc = PostQueuedCompletionStatus( handle_, numberOfBytesTransferred, reinterpret_cast<ULONG_PTR>( data ), overlapped );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
    }

    bool IOCompletionPort::Dequeue( Message& message, DWORD timeoutInMillis ) const
    {
        auto rc = GetQueuedCompletionStatus( handle_, &message.numberOfBytesTransferred_, reinterpret_cast<PULONG_PTR>( &message.data_ ), &message.overlapped_, timeoutInMillis );
        if ( !rc )
        {
            auto err = GetLastError( );
            if ( err == ERROR_ABANDONED_WAIT_0 )
            {
                return false;
            }
            else if ( err == ERROR_OPERATION_ABORTED )
            {
                return true;
            }
            else
            {
                auto errorMessage = FormatError( err );
                wprintf( L"IOCompletionPort::Dequeue:Error %d %s\n", err, errorMessage.c_str( ) );
                return false;
            }
        }
        return true;
    }


    IOCompletionPort::Message IOCompletionPort::Dequeue( DWORD timeoutInMillis ) const
    {
        Message result{};
        auto rc = GetQueuedCompletionStatus( handle_, &result.numberOfBytesTransferred_, reinterpret_cast<PULONG_PTR>( &result.data_ ), &result.overlapped_, timeoutInMillis );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return result;
    }



}
