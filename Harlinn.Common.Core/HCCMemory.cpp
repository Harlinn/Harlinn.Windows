#include "pch.h"
#include <HCCMemory.h>
#include <HCCSecurity.h>
#include <HCCException.h>
#include <HCCIO.h>
#include <HCCLogging.h>

namespace Harlinn::Common::Core
{
    Allocator::~Allocator( )
    {
    }

    Byte* MallocAllocator::Allocate( size_t size )
    {
        return static_cast<Byte*>( malloc( size ) );
    }
    Byte* MallocAllocator::Reallocate( Byte* ptr, size_t size )
    {
        return static_cast<Byte*>( realloc( ptr, size ) );
    }
    void MallocAllocator::Free( Byte* ptr )
    {
        free( ptr );
    }

    PageFlags GetPageFlags( MemoryMappedFileAccess access )
    {
        if ( access == MemoryMappedFileAccess::Read )
        {
            return PageFlags::Readonly;
        }
        else if ( access == MemoryMappedFileAccess::ReadWrite )
        {
            return PageFlags::ReadWrite;
        }
        else if ( access == MemoryMappedFileAccess::CopyOnWrite )
        {
            return PageFlags::WriteCopy;
        }
        else if ( access == MemoryMappedFileAccess::ReadExecute )
        {
            return PageFlags::ExecuteRead;
        }
        else if ( access == MemoryMappedFileAccess::ReadWriteExecute )
        {
            return PageFlags::ExecuteReadWrite;
        }

        // If we reached here, access was invalid.
        HCC_THROW( ArgumentOutOfRangeException, L"access" );
    }

    DWORD GetFileMapAccess( MemoryMappedFileAccess access )
    {

        if ( access == MemoryMappedFileAccess::Read )
        {
            return FILE_MAP_READ;
        }
        else if ( access == MemoryMappedFileAccess::Write )
        {
            return FILE_MAP_WRITE;
        }
        else if ( access == MemoryMappedFileAccess::ReadWrite )
        {
            return FILE_MAP_READ | FILE_MAP_WRITE;
        }
        else if ( access == MemoryMappedFileAccess::CopyOnWrite )
        {
            return FILE_MAP_COPY;
        }
        else if ( access == MemoryMappedFileAccess::ReadExecute )
        {
            return FILE_MAP_EXECUTE | FILE_MAP_READ;
        }
        else if ( access == MemoryMappedFileAccess::ReadWriteExecute )
        {
            return FILE_MAP_EXECUTE | FILE_MAP_READ | FILE_MAP_WRITE;
        }

        // If we reached here, access was invalid.
        HCC_THROW( ArgumentOutOfRangeException, L"access" );
    }

    IO::FileSystemRights GetFileSystemRights( MemoryMappedFileAccess access )
    {
        switch ( access )
        {
            case MemoryMappedFileAccess::Read:
            case MemoryMappedFileAccess::CopyOnWrite:
                return IO::FileSystemRights::ReadData;

            case MemoryMappedFileAccess::ReadWrite:
                return IO::FileSystemRights::ReadData | IO::FileSystemRights::WriteData;

            case MemoryMappedFileAccess::Write:
                return IO::FileSystemRights::WriteData;

            case MemoryMappedFileAccess::ReadExecute:
                return IO::FileSystemRights::ReadData | IO::FileSystemRights::ExecuteFile;

            case MemoryMappedFileAccess::ReadWriteExecute:
                return IO::FileSystemRights::ReadData | IO::FileSystemRights::WriteData | IO::FileSystemRights::ExecuteFile;

            default:
                // If we reached here, access was invalid.
                HCC_THROW( ArgumentOutOfRangeException, L"access" );
        }
    }


    // This converts a MemoryMappedFileAccess to a FileAccess. 
    IO::FileAccess GetFileAccess( MemoryMappedFileAccess access )
    {
        if ( access == MemoryMappedFileAccess::Read )
        {
            return IO::FileAccess::Read;
        }
        if ( access == MemoryMappedFileAccess::Write )
        {
            return IO::FileAccess::Write;
        }
        else if ( access == MemoryMappedFileAccess::ReadWrite )
        {
            return IO::FileAccess::ReadWrite;
        }
        else if ( access == MemoryMappedFileAccess::CopyOnWrite )
        {
            return IO::FileAccess::ReadWrite;
        }
        else if ( access == MemoryMappedFileAccess::ReadExecute )
        {
            return IO::FileAccess::Read;
        }
        else if ( access == MemoryMappedFileAccess::ReadWriteExecute )
        {
            return IO::FileAccess::ReadWrite;
        }

        // If we reached here, access was invalid.
        HCC_THROW( ArgumentOutOfRangeException, L"access" );
    }



    FileMapping::FileMapping( HANDLE fileHandle, const Security::SecurityAttributes& securityAttributes, PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const wchar_t* name )
        : handle_( nullptr )
    {
        DWORD flags = static_cast<DWORD>( pageFlags ) | static_cast<DWORD>( sectionFlags );
        DWORD maximumSizeHigh = maximumSize >> 32;
        DWORD maximumSizeLow = static_cast<DWORD>( maximumSize & 0xFFFFFFFF );
        auto handle = CreateFileMappingW( fileHandle, const_cast<Security::SecurityAttributes*>( &securityAttributes ), flags, maximumSizeHigh, maximumSizeLow, name );
        if ( handle == nullptr )
        {
            ThrowLastOSError( );
        }
        else
        {
            handle_ = handle;
        }
    }
    FileMapping::FileMapping( HANDLE fileHandle, const Security::SecurityAttributes& securityAttributes, PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const char* name )
        : handle_( nullptr )
    {
        DWORD flags = static_cast<DWORD>( pageFlags ) | static_cast<DWORD>( sectionFlags );
        DWORD maximumSizeHigh = maximumSize >> 32;
        DWORD maximumSizeLow = static_cast<DWORD>( maximumSize & 0xFFFFFFFF );
        auto handle = CreateFileMappingA( fileHandle, const_cast<Security::SecurityAttributes*>( &securityAttributes ), flags, maximumSizeHigh, maximumSizeLow, name );
        if ( handle == nullptr )
        {
            ThrowLastOSError( );
        }
        else
        {
            handle_ = handle;
        }
    }
    FileMapping::FileMapping( HANDLE fileHandle, PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const wchar_t* name )
        : handle_( nullptr )
    {
        DWORD flags = static_cast<DWORD>( pageFlags ) | static_cast<DWORD>( sectionFlags );
        DWORD maximumSizeHigh = maximumSize >> 32;
        DWORD maximumSizeLow = static_cast<DWORD>( maximumSize & 0xFFFFFFFF );
        auto handle = CreateFileMappingW( fileHandle, nullptr, flags, maximumSizeHigh, maximumSizeLow, name );
        if ( handle == nullptr )
        {
            ThrowLastOSError( );
        }
        else
        {
            handle_ = handle;
        }
    }
    FileMapping::FileMapping( HANDLE fileHandle, PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const char* name )
        : handle_( nullptr )
    {
        DWORD flags = static_cast<DWORD>( pageFlags ) | static_cast<DWORD>( sectionFlags );
        DWORD maximumSizeHigh = maximumSize >> 32;
        DWORD maximumSizeLow = static_cast<DWORD>( maximumSize & 0xFFFFFFFF );
        auto handle = CreateFileMappingA( fileHandle, nullptr, flags, maximumSizeHigh, maximumSizeLow, name );
        if ( handle == nullptr )
        {
            ThrowLastOSError( );
        }
        else
        {
            handle_ = handle;
        }
    }

    FileMapping::View::View( const FileMapping& fileMapping, FileMap fileMap, size_t offset, size_t numberOfBytesToMap )
        : begin_( nullptr ), end_( nullptr )
    {
        auto ptr = (Byte*)MapViewOfFile( fileMapping.Handle( ), static_cast<DWORD>( fileMap ), static_cast<DWORD>( offset >> 32 ), static_cast<DWORD>( offset ), numberOfBytesToMap );
        if ( ptr == nullptr )
        {
            ThrowLastOSError( );
        }
        if ( numberOfBytesToMap )
        {
            begin_ = ptr;
            end_ = ptr + numberOfBytesToMap;
        }
        else
        {
            MEMORY_BASIC_INFORMATION info{};
            auto rc = VirtualQuery( ptr, &info, sizeof( MEMORY_BASIC_INFORMATION ) );
            if ( rc == 0 )
            {
                auto errorCode = GetLastError( );
                (void)UnmapViewOfFile( ptr );
                ThrowOSError( errorCode );
            }
            else
            {
                begin_ = ptr;
                end_ = ptr + info.RegionSize;
            }
        }
    }


    void FileMapping::View::Flush( )
    {
        auto rc = FlushViewOfFile( begin_, 0 );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
    }

    void FileMapping::View::Flush( size_t numberOfBytesToFlush )
    {
        auto rc = FlushViewOfFile( begin_, numberOfBytesToFlush );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
    }

    FileMapping FileMapping::Open( MemoryMappedFileRights desiredAccess, const wchar_t* name, bool inheritHandle )
    {
        auto handle = OpenFileMappingW( static_cast<DWORD>( desiredAccess ), inheritHandle ? TRUE : FALSE, name );
        if ( handle == nullptr )
        {
            ThrowLastOSError( );
        }
        return FileMapping( handle );
    }
    FileMapping FileMapping::Open( MemoryMappedFileRights desiredAccess, const char* name, bool inheritHandle )
    {
        auto handle = OpenFileMappingA( static_cast<DWORD>( desiredAccess ), inheritHandle ? TRUE : FALSE, name );
        if ( handle == nullptr )
        {
            ThrowLastOSError( );
        }
        return FileMapping( handle );
    }


}
