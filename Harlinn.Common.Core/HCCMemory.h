#pragma once
#ifndef __HCCMEMORY_H__
#define __HCCMEMORY_H__
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

#include <HCCLinkedList.h>
#include <HCCString.h>
#include <HCCSync.h>

namespace Harlinn::Common::Core
{
    namespace Security
    {
        class SecurityAttributes;
    }


    enum class PageFlags : DWORD
    {
        /// <summary>
        /// Disables all access to the committed region of pages. An attempt to read 
        /// from, write to, or execute the committed region results in an access violation.
        /// This flag is not supported by the CreateFileMapping function.
        /// </summary>
        NoAccess = PAGE_NOACCESS,
        /// <summary>
        /// Enables read-only access to the committed region of pages. An attempt to write 
        /// to the committed region results in an access violation. If Data Execution 
        /// Prevention is enabled, an attempt to execute code in the committed region 
        /// results in an access violation.
        /// </summary>
        Readonly = PAGE_READONLY,
        /// <summary>
        /// </summary>
        ReadWrite = PAGE_READWRITE,
        /// <summary>
        /// </summary>
        WriteCopy = PAGE_WRITECOPY,
        /// <summary>
        /// Enables execute access to the committed region of pages. An attempt to write 
        /// to the committed region results in an access violation.
        /// This flag is not supported by the CreateFileMapping function.
        /// </summary>
        Execute = PAGE_EXECUTE,
        /// <summary>
        /// Enables execute or read-only access to the committed region of pages. 
        /// An attempt to write to the committed region results in an access violation.
        /// </summary>
        ExecuteRead = PAGE_EXECUTE_READ,
        /// <summary>
        /// Enables execute, read-only, or read/write access to the committed region of pages.
        /// </summary>
        ExecuteReadWrite = PAGE_EXECUTE_READWRITE,
        /// <summary>
        /// Enables execute, read-only, or copy-on-write access to a mapped view of a 
        /// file mapping object. An attempt to write to a committed copy-on-write 
        /// page results in a private copy of the page being made for the process. 
        /// The private page is marked as ExecuteReadWrite, and the change is written 
        /// to the new page.
        /// This flag is not supported by the VirtualAlloc or VirtualAllocEx functions.
        /// </summary>
        ExecuteWriteCopy = PAGE_EXECUTE_WRITECOPY,
        /// <summary>
        /// Pages in the region become guard pages. Any attempt to access a guard page 
        /// causes the system to raise a STATUS_GUARD_PAGE_VIOLATION exception and turn 
        /// off the guard page status. Guard pages thus act as a one-time access alarm. 
        /// When an access attempt leads the system to turn off guard page status, 
        /// the underlying page protection takes over.
        /// If a guard page exception occurs during a system service, the service typically 
        /// returns a failure status indicator.
        /// This value cannot be used with NoAccess.
        /// This flag is not supported by the CreateFileMapping function.
        /// </summary>
        Guard = PAGE_GUARD,
        /// <summary>
        /// Sets all pages to be non-cachable. Applications should not use this attribute 
        /// except when explicitly required for a device. Using the interlocked functions 
        /// with memory that is mapped with SEC_NOCACHE can result in an 
        /// EXCEPTION_ILLEGAL_INSTRUCTION exception.
        /// The NoCache flag cannot be used with the Guard, NoAccess, or WriteCombine flags.
        /// The NoCache flag can be used only when allocating private memory with the 
        /// VirtualAlloc, VirtualAllocEx, or VirtualAllocExNuma functions.
        /// To enable non-cached memory access for shared memory, specify the SEC_NOCACHE flag when calling the CreateFileMapping function.
        /// </summary>
        NoCache = PAGE_NOCACHE,
        /// <summary>
        /// Sets all pages to be write-combined. 
        /// Applications should not use this attribute except when explicitly required for a device.Using the interlocked functions with memory that is mapped as write - combined can result in an EXCEPTION_ILLEGAL_INSTRUCTION exception.
        /// The PAGE_WRITECOMBINE flag cannot be specified with the PAGE_NOACCESS, PAGE_GUARD, and PAGE_NOCACHE flags.
        /// The PAGE_WRITECOMBINE flag can be used only when allocating private memory with the VirtualAlloc, VirtualAllocEx, or VirtualAllocExNuma functions.To enable write - combined memory access for shared memory, specify the SEC_WRITECOMBINE flag when calling the CreateFileMapping function.
        /// </summary>
        WriteCombine = PAGE_WRITECOMBINE
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( PageFlags, DWORD );

    enum class SectionFlags : DWORD
    {
        None = 0,
        PartitionOwnerHandle = SEC_PARTITION_OWNER_HANDLE,
        Pages64K = SEC_64K_PAGES,
        File = SEC_FILE,
        Image = SEC_IMAGE,
        ProtectedImage = SEC_PROTECTED_IMAGE,
        Reserve = SEC_RESERVE,
        Commit = SEC_COMMIT,
        NoCache = SEC_NOCACHE,
        WriteCombine = SEC_WRITECOMBINE,
        LargePages = SEC_LARGE_PAGES,
        ImageNoExecute = SEC_IMAGE_NO_EXECUTE
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( SectionFlags, DWORD );


    struct FixedSizeMemoryManagerStatistics
    {
        size_t FreeCount = 0;
        size_t MallocCalls = 0;
        size_t FreeCalls = 0;
        size_t AlignedMallocCalls = 0;
        size_t AlignedFreeCalls = 0;

        void Print( )
        {
            printf( "Free count=%zu, Malloc calls=%zu, Free calls=%zu, Aligned Malloc calls=%zu, Aligned Free calls=%zu\n", FreeCount, MallocCalls, FreeCalls, AlignedMallocCalls, AlignedFreeCalls );
        }
    };

    



    template<size_t blockSize, size_t maxFreeCount >
    class FixedSizeMemoryManager
    {
    public:
        using StatisticsType = FixedSizeMemoryManagerStatistics;
        static constexpr size_t BlockSize = blockSize;
        static constexpr size_t MaxFreeCount = maxFreeCount;
    private:
        InterlockedLinkedList freeList_;
        
        std::atomic_size_t freeCount_{};
        std::atomic_size_t mallocCalls_{};
        std::atomic_size_t freeCalls_{};
        std::atomic_size_t alignedMallocCalls_{};
        std::atomic_size_t alignedFreeCalls_{};

    public:
        FixedSizeMemoryManager( )
        {
        }

        FixedSizeMemoryManager( const FixedSizeMemoryManager& other ) = delete;
        FixedSizeMemoryManager( FixedSizeMemoryManager&& other ) = delete;

        FixedSizeMemoryManager& operator = ( const FixedSizeMemoryManager& other ) = delete;
        FixedSizeMemoryManager& operator = ( FixedSizeMemoryManager&& other ) = delete;


        ~FixedSizeMemoryManager( )
        {
            Reset( );
        }

        size_t FreeCount( ) const noexcept
        {
            return freeCount_;
        }
        size_t MallocCalls( ) const noexcept
        {
            return mallocCalls_;
        }
        size_t FreeCalls( ) const noexcept
        {
            return freeCalls_;
        }

        size_t AlignedMallocCalls( ) const noexcept
        {
            return alignedMallocCalls_;
        }
        size_t AlignedFreeCalls( ) const noexcept
        {
            return alignedFreeCalls_;
        }

        
        [[nodiscard]] StatisticsType Statistics( ) const noexcept
        {
            StatisticsType result
            {
                .FreeCount = FreeCount(),
                .MallocCalls = MallocCalls(),
                .FreeCalls = FreeCalls(),
                .AlignedMallocCalls = AlignedMallocCalls(),
                .AlignedFreeCalls = AlignedFreeCalls()
            };
            return result;
        }

        void PrintStatistics( )
        {
            auto freeCount = FreeCount( );
            auto mallocCalls = MallocCalls( );
            auto freeCalls = FreeCalls( );
            auto alignedMallocCalls = AlignedMallocCalls( );
            auto alignedFreeCalls = AlignedFreeCalls( );

            printf( "Free count=%zu, Malloc calls=%zu, Free calls=%zu, Aligned Malloc calls=%zu, Aligned Free calls=%zu\n", freeCount, mallocCalls, freeCalls, alignedMallocCalls, alignedFreeCalls );
        }
    private:
        void* AlignedMalloc( )
        {
            ++alignedMallocCalls_;
            return _aligned_malloc( BlockSize, MEMORY_ALLOCATION_ALIGNMENT );
        }
        void AlignedFree( void* ptr )
        {
            ++alignedFreeCalls_;
            _aligned_free( ptr );
        }
    public:

        void* Malloc( ) noexcept
        {
            ++mallocCalls_;
            void* result = freeList_.Pop( );
            if ( !result )
            {
                result = AlignedMalloc( );
            }
            else
            {
                --freeCount_;
            }
            return result;
        }

        void Free( void* ptr ) noexcept
        {
            ++freeCalls_;
            if ( ptr )
            {
                size_t freeCount = freeCount_;
                if ( freeCount >= MaxFreeCount )
                {
                    AlignedFree( ptr );
                }
                else
                {
                    auto* entry = ( InterlockedLinkedList::Entry* )ptr;
                    entry->Next = nullptr;
                    freeList_.Push( entry );
                    ++freeCount_;
                }
            }
            else
            {
                DebugBreak( );
            }
        }

        void Reset( ) noexcept
        {
            InterlockedLinkedList::Entry* entry = freeList_.Pop( );
            while ( entry )
            {
                AlignedFree( entry );
                --freeCount_;
                if ( !freeCount_ )
                {
                    break;
                }
                entry = freeList_.Pop( );
            } 
        }
    };


    class Allocator
    {
    public:
        HCC_EXPORT virtual ~Allocator( );
        virtual Byte* Allocate( size_t size ) = 0;
        virtual Byte* Reallocate( Byte* ptr, size_t size ) = 0;
        virtual void Free( Byte* ptr ) = 0;
    };


    class MallocAllocator : public Allocator
    {
    public:
        HCC_EXPORT virtual Byte* Allocate( size_t size ) override;
        HCC_EXPORT virtual Byte* Reallocate( Byte* ptr, size_t size ) override;
        HCC_EXPORT virtual void Free( Byte* ptr ) override;
    };


    enum class MemoryMappedFileRights : DWORD
    {
        // Maps to win32 FILE_MAP_XXX constants

        CopyOnWrite = FILE_MAP_COPY,
        Write = FILE_MAP_WRITE,
        Read = FILE_MAP_READ,
        Execute = FILE_MAP_EXECUTE,

        Delete = DELETE, 
        ReadPermissions = READ_CONTROL,
        ChangePermissions = WRITE_DAC,
        TakeOwnership = WRITE_OWNER,
        //Synchronize = SYNCHRONIZE, Not supported by memory mapped files

        ReadWrite = Read | Write,
        ReadExecute = Read | Execute,
        ReadWriteExecute = Read | Write | Execute,

        FullControl = CopyOnWrite | Read | Write | Execute | Delete | ReadPermissions | ChangePermissions | TakeOwnership,

        AccessSystemSecurity = ACCESS_SYSTEM_SECURITY, // Allow changes to SACL
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( MemoryMappedFileRights, DWORD );

    enum class MemoryMappedFileAccess : DWORD
    {
        ReadWrite = 0,
        Read,
        // Write is valid only when creating views and not when creating MemoryMappedFiles   
        Write,   
        CopyOnWrite,
        ReadExecute,
        ReadWriteExecute
    };
    
    namespace IO
    {
        enum class FileSystemRights : DWORD;
        enum class FileAccess : DWORD;
    }

    // This converts a MemoryMappedFileAccess to it's corresponding native PAGE_XXX value
    HCC_EXPORT PageFlags GetPageFlags( MemoryMappedFileAccess access );

    // This converts a MemoryMappedFileAccess to it's corresponding native PAGE_XXX value
    inline PageFlags GetPageAccess( MemoryMappedFileAccess access )
    {
        return GetPageFlags( access );
    }

    // This converts a MemoryMappedFileAccess to its corresponding FILE_MAP_XXX value
    HCC_EXPORT DWORD GetFileMapAccess( MemoryMappedFileAccess access );

    // This converts a MemoryMappedFileAccess to a FileSystemRights
    HCC_EXPORT IO::FileSystemRights GetFileSystemRights( MemoryMappedFileAccess access );

    // This converts a MemoryMappedFileAccess to a FileAccess.
    HCC_EXPORT IO::FileAccess GetFileAccess( MemoryMappedFileAccess access );


    enum class MemoryMappedFileOptions : DWORD
    {
        None = 0,
        DelayAllocatePages = 0x4000000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( MemoryMappedFileOptions, DWORD );


    enum class FileMap : DWORD
    {
        Read = FILE_MAP_READ,
        Write = FILE_MAP_WRITE,
        AllAccess = FILE_MAP_ALL_ACCESS,
        Execute = FILE_MAP_EXECUTE,
        Copy = FILE_MAP_COPY,
        Reserve = FILE_MAP_RESERVE,
        TargetsInvalid = FILE_MAP_TARGETS_INVALID,
        LargePages = FILE_MAP_LARGE_PAGES
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FileMap, DWORD );
    /// <summary>
    /// A file mapping is the association of a file's contents with a portion of the 
    /// virtual address space of a process.
    /// </summary>
    /// <remarks>
    /// The system creates a file mapping object (also known as a section object) to 
    /// maintain this association. A file view is the portion of virtual address space 
    /// that a process uses to access the file's contents. File mapping allows the 
    /// process to use both random input and output (I/O) and sequential I/O. It also 
    /// allows the process to work efficiently with a large data file, such as a database, 
    /// without having to map the whole file into memory. Multiple processes can also 
    /// use memory-mapped files to share data.
    /// </remarks>
    class FileMapping
    {
        HANDLE handle_;
    public:
        
        class View
        {
            Byte* begin_;
            Byte* end_;
        public:
            using iterator = Byte*;
            using const_iterator = const Byte*;

            using reference = Byte&;
            using const_reference = const Byte&;

            using size_type = size_t;

            HCC_EXPORT View( const FileMapping& fileMapping, FileMap fileMap, size_t offset, size_t numberOfBytesToMap );


            View( )
                : begin_(nullptr), end_( nullptr )
            { }


            View( const View& other ) = delete;
            View( View&& other ) noexcept
                : begin_( other.begin_ ), end_( other.end_ )
            {
                other.begin_ = nullptr;
                other.end_ = nullptr;
            }

            View& operator = ( const View& other ) = delete;
            View& operator = ( View&& other ) noexcept
            {
                if ( &other != this )
                {
                    Close( );
                    begin_ = other.begin_;
                    end_ = other.end_;
                    other.begin_ = nullptr;
                    other.end_ = nullptr;
                }
                return *this;
            }


            ~View( ) noexcept
            {
                Close( );
            }

            void Close( ) noexcept
            {
                if ( begin_ )
                {
                    UnmapViewOfFile( begin_ );
                    begin_ = nullptr;
                    end_ = nullptr;
                }
            }

            HCC_EXPORT void Flush( );
            HCC_EXPORT void Flush( size_t numberOfBytesToFlush );


            size_t size( ) const noexcept
            {
                return end_ - begin_;
            }

            iterator begin( ) noexcept
            {
                return begin_;
            }
            iterator end( ) noexcept
            {
                return end_;
            }

            const_iterator begin( ) const noexcept
            {
                return begin_;
            }
            const_iterator end( ) const noexcept
            {
                return end_;
            }
            const_iterator cbegin( ) const noexcept
            {
                return begin_;
            }
            const_iterator cend( ) const noexcept
            {
                return end_;
            }

            reference operator[]( size_type index ) noexcept
            {
                return begin_[index];
            }
            const_reference operator[]( size_type index ) const noexcept
            {
                return begin_[index];
            }

            void AppendTo( std::vector<AnsiString>& strings ) const
            {
                auto start = begin( );
                auto ptr = start;

                while ( ptr < end_ )
                {
                    auto c = *ptr;
                    if ( c == '\r' )
                    {
#ifdef HCC_WITH_BASIC_STRING
                        AnsiString str( reinterpret_cast< const AnsiString::value_type* >( start ), static_cast<size_t>(ptr - start) );
                        strings.emplace_back( std::move( str ) );
#else
                        strings.emplace_back( start, ptr );
#endif
                        if ( ( ptr + 1 < end_ ) && *( ptr + 1 ) == '\n' )
                        {
                            ptr++;
                        }
                        start = ptr + 1;
                    }
                    else if ( c == '\n' )
                    {
#ifdef HCC_WITH_BASIC_STRING
                        AnsiString str( reinterpret_cast< const AnsiString::value_type* >( start ), static_cast< size_t >( ptr - start ) );
                        strings.emplace_back( std::move( str ) );
#else
                        strings.emplace_back( start, ptr );
#endif
                        start = ptr + 1;
                    }
                    ptr++;
                }
                if ( start < end_ )
                {
#ifdef HCC_WITH_BASIC_STRING
                    AnsiString str( reinterpret_cast< const AnsiString::value_type* >( start ), static_cast< size_t >( end( ) - start ) );
                    strings.emplace_back( std::move( str ) );
#else
                    strings.emplace_back( start, end( ) );
#endif
                }
            }

            void AppendTo( AnsiString& str ) const
            {
#ifdef HCC_WITH_BASIC_STRING
                str.append( reinterpret_cast< const AnsiString::value_type*>( begin( ) ), reinterpret_cast< const AnsiString::value_type* >( end( ) ) );
#else
                str.append( begin( ), end( ) );
#endif
            }

            void AppendTo( std::vector<Byte>& destination ) const
            {
                auto viewSize = size( );
                auto currentDestinationSize = destination.size( );
                auto newDestinationSize = currentDestinationSize + viewSize;
                destination.resize( newDestinationSize );
                memcpy( destination.data( ) + currentDestinationSize, begin( ), viewSize );
            }


        };

        constexpr FileMapping( )
            : handle_( nullptr )
        {
        }

        constexpr explicit FileMapping( HANDLE handleToFileMapping )
            : handle_( handleToFileMapping )
        {
        }


        HCC_EXPORT FileMapping( HANDLE fileHandle, const Security::SecurityAttributes& securityAttributes, PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const wchar_t* name );
        HCC_EXPORT FileMapping( HANDLE fileHandle, const Security::SecurityAttributes& securityAttributes, PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const char* name );
        HCC_EXPORT FileMapping( HANDLE fileHandle, PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const wchar_t* name = nullptr );
        HCC_EXPORT FileMapping( HANDLE fileHandle, PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const char* name );

        FileMapping( const Security::SecurityAttributes& securityAttributes, PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const wchar_t* name )
            : FileMapping( INVALID_HANDLE_VALUE, securityAttributes, pageFlags, sectionFlags, maximumSize, name )
        { 
        }
        FileMapping( const Security::SecurityAttributes& securityAttributes, PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const char* name )
            : FileMapping( INVALID_HANDLE_VALUE, securityAttributes, pageFlags, sectionFlags, maximumSize, name )
        {
        }
        FileMapping( PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize = 0, const wchar_t* name = nullptr)
            : FileMapping( INVALID_HANDLE_VALUE, pageFlags, sectionFlags, maximumSize, name )
        {
        }
        FileMapping( PageFlags pageFlags, SectionFlags sectionFlags, uint64_t maximumSize, const char* name )
            : FileMapping( INVALID_HANDLE_VALUE, pageFlags, sectionFlags, maximumSize, name )
        {
        }

        FileMapping( const FileMapping& other ) = delete;
        constexpr FileMapping( FileMapping&& other ) noexcept
            : handle_( other.handle_ )
        {
            other.handle_ = nullptr;
        }

        ~FileMapping( )
        {
            Close( );
        }


        FileMapping& operator = ( const FileMapping& other ) = delete;
        constexpr FileMapping& operator = ( FileMapping&& other ) noexcept
        {
            if ( &other != this )
            {
                Close( );
                handle_ = other.handle_;
                other.handle_ = nullptr;
            }
            return *this;
        }

        HANDLE Handle( ) const noexcept
        {
            return handle_;
        }


        void Close( ) noexcept
        {
            if ( handle_ != nullptr )
            {
                CloseHandle( handle_ );
                handle_ = nullptr;
            }
        }

        HCC_EXPORT static FileMapping Open( MemoryMappedFileRights desiredAccess, const wchar_t* name, bool inheritHandle = false );
        HCC_EXPORT static FileMapping Open( MemoryMappedFileRights desiredAccess, const char* name, bool inheritHandle = false );

    };


    


}
#endif
