#pragma once
#ifndef __HCCIO_H__
#define __HCCIO_H__

#include <HCCDef.h>
#include <HCCIOBase.h>
#include <HCCIORequest.h>
#include <HCCSecurity.h>
#include <HCCLogging.h>
#include <HCCIOBufferStream.h>
#include <HCCReference.h>

namespace Harlinn::Common::Core::IO
{
    

    


    /// <summary>
    /// Creates a stream stored in memory.
    /// </summary>
    /// <remarks>
    /// MemoryStream allocates and releases memory using 
    /// CoTaskMemRealloc and CoTaskMemFree.
    /// </remarks>
    class MemoryStream
    {
        class Data : public ReferenceCountedBase<Data>
        {
        public:
            using Base = ReferenceCountedBase<Data>;
        private:
            bool ownsData_;
            size_t capacity_;
            size_t size_;
            Byte* data_;
            static const size_t CapacityDelta = 1024;
            static const size_t CapacityDelta2 = 128 * 1024 * 1024;

            static size_t allocationByteCount( size_t length )
            {
                if ( length )
                {
                    if ( length < ( 10 * CapacityDelta ) )
                    {
                        size_t bytesRequired = length;

                        size_t remainder = bytesRequired % CapacityDelta;
                        if ( remainder != 0 )
                        {
                            bytesRequired += CapacityDelta - remainder;
                        }
                        return bytesRequired;
                    }
                    else
                    {
                        size_t bytesRequired = length;

                        size_t remainder = bytesRequired % CapacityDelta2;
                        if ( remainder != 0 )
                        {
                            bytesRequired += CapacityDelta2 - remainder;
                        }
                        return bytesRequired;
                    }
                }
                return 0;
            }

        public:
            Data( )
                : ownsData_( true ), capacity_( 8192 ), size_( 0 ), data_( (Byte*)CoTaskMemAlloc( 8192 ) )
            { }
            Data( Byte* buffer, size_t bufferSize )
                : ownsData_( false ), capacity_( bufferSize ), size_( bufferSize ), data_( buffer )
            { }
            Data( Byte* buffer, size_t bufferSize, bool ownsData )
                : ownsData_( ownsData ), capacity_( bufferSize ), size_( bufferSize ), data_( buffer )
            { }
            ~Data( )
            {
                if ( ownsData_ && data_ )
                {
                    CoTaskMemFree( data_ );
                }
            }
            long long AddReference( ) noexcept
            {
                return Base::AddRef( );
            }

            constexpr const Byte* Buffer( ) const noexcept
            {
                return data_;
            }

            constexpr Byte* Buffer( ) noexcept
            {
                return data_;
            }

            Byte* Detach( )
            {
                if ( ownsData_ == false )
                {
                    throw Exception( "The buffer is not owned by the MemoryStream." );
                }
                Byte* result = data_;
                capacity_ = 0;
                size_ = 0;
                data_ = nullptr;
                return result;
            }

            constexpr bool OwnsData( ) const noexcept
            {
                return ownsData_;
            }

            constexpr long long Capacity( ) const noexcept
            {
                return static_cast<long long>( capacity_ );
            }
            void SetCapacity( long long size )
            {
                size_t newCapacity = static_cast<size_t>( size );
                if ( ( newCapacity == capacity_ ) || ( newCapacity < size_ ) )
                {
                    return;
                }
                if ( !ownsData_ )
                {
                    throw InvalidOperationException( "Buffer is read only" );
                }
                Byte* ptr = (Byte*)CoTaskMemRealloc( data_, newCapacity );
                if ( ptr == nullptr )
                {
                    throw OutOfMemoryException( );
                }
                data_ = ptr;
                capacity_ = newCapacity;
            }
            constexpr long long Size( ) const noexcept
            {
                return static_cast<long long>( size_ );
            }
            void SetSize( long long size )
            {
                size_t newSize = static_cast<size_t>( size );
                if ( newSize == size_ )
                {
                    return;
                }
                if ( newSize > capacity_ )
                {
                    size_t newCapacity = allocationByteCount( newSize );
                    SetCapacity( static_cast<long long>( newCapacity ) );
                }
                size_ = newSize;
            }
            long long Read( long long& position, void* buffer, size_t numberOfBytesToRead )
            {
                size_t currentPosition = static_cast<size_t>( position );
                if ( currentPosition < size_ )
                {
                    if ( currentPosition + numberOfBytesToRead > size_ )
                    {
                        numberOfBytesToRead = size_ - currentPosition;
                    }
                    memcpy( buffer, &data_[currentPosition], numberOfBytesToRead );
                    long long result = static_cast<long long>( numberOfBytesToRead );
                    position += result;
                    return result;
                }
                return 0;
            }
            long long Write( long long& position, const void* buffer, size_t numberOfBytesToWrite )
            {
                if ( numberOfBytesToWrite == 0 )
                {
                    return 0;
                }
                if ( !ownsData_ )
                {
                    throw InvalidOperationException( "Buffer is read only" );
                }
                size_t currentPosition = static_cast<size_t>( position );
                size_t sizeRequired = currentPosition + numberOfBytesToWrite;
                if ( sizeRequired > size_ )
                {
                    SetSize( static_cast<long long>( sizeRequired ) );
                }
                memcpy( &data_[currentPosition], buffer, numberOfBytesToWrite );
                long long result = static_cast<long long>( numberOfBytesToWrite );
                position += result;
                return result;
            }
            long long Seek( long long& position, long long offset, SeekOrigin seekOrigin )
            {
                long long newPosition = 0;
                size_t currentPosition = static_cast<size_t>( position );
                switch ( seekOrigin )
                {
                    case SeekOrigin::StartOfFile:
                        if ( offset > 0 )
                        {
                            newPosition = offset;
                        }
                        break;
                    case SeekOrigin::CurrentPosition:
                        newPosition = position + offset;
                        break;
                    case SeekOrigin::EndOfFile:
                        newPosition = size_ + offset;
                        break;
                }
                if ( newPosition < 0 )
                {
                    newPosition = 0;
                }
                if ( static_cast<size_t>( newPosition ) > size_ )
                {
                    SetSize( newPosition );
                }
                position = newPosition;
                return newPosition;
            }
        };

        mutable Data* data_;
        mutable long long position_;
    public:
        constexpr MemoryStream( ) noexcept
            : data_( nullptr ), position_( 0 )
        { }
        /// <summary>
        /// Constructs a MemoryStream that will use the argument buffer as storage for the
        /// stream data.
        /// </summary>
        /// <remarks>
        /// The MemoryStream will not take ownership of the buffer.
        /// </remarks>
        /// <param name="buffer">The buffer that will be used as storage for the stream</param>
        /// <param name="bufferSize">The size of the buffer</param>
        MemoryStream( Byte* buffer, size_t bufferSize )
            : data_( new Data( buffer, bufferSize ) ), position_( 0 )
        {
        }
        /// <summary>
        /// Constructs a MemoryStream that will use the argument buffer as storage for the
        /// stream data.
        /// </summary>
        /// <remarks>
        /// If the MemoryStream is supposed to take ownership of the buffer
        /// then it must be allocated using CoTaskMemRealloc or CoTaskMemAlloc.
        /// </remarks>
        /// <param name="buffer">The buffer that will be used as storage for the stream</param>
        /// <param name="bufferSize">The size of the buffer</param>
        /// <param name="ownsData">Set to true to transfer ownership of the buffer to the MemoryStream</param>
        MemoryStream( Byte* buffer, size_t bufferSize, bool ownsData )
            : data_( new Data( buffer, bufferSize, ownsData ) ), position_( 0 )
        {
        }
        MemoryStream( const MemoryStream& other )
            : data_( other.data_ ), position_( other.position_ )
        {
            if ( data_ )
            {
                data_->AddReference( );
            }
        }
        constexpr MemoryStream( MemoryStream&& other ) noexcept
            : data_( other.data_ ), position_( other.position_ )
        {
            other.data_ = nullptr;
        }


        ~MemoryStream( )
        {
            if ( data_ )
            {
                data_->Release( );
            }
        }

        MemoryStream& operator = ( const MemoryStream& other )
        {
            if ( data_ != other.data_ )
            {
                if ( data_ )
                {
                    data_->Release( );
                }
                data_ = other.data_;
                if ( data_ )
                {
                    data_->AddReference( );
                }
            }
            return *this;
        }
        MemoryStream& operator = ( MemoryStream&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            std::swap( position_, other.position_ );
            return *this;
        }

        constexpr void Flush( ) const noexcept
        { 
        }

        constexpr bool CanRead( ) const noexcept
        {
            return true;
        }
        constexpr bool CanSeek( ) const noexcept
        {
            return true;
        }
        constexpr bool CanTimeout( ) const noexcept
        {
            return false;
        }
        constexpr bool CanWrite( ) const noexcept
        {
            if ( data_ )
            {
                return data_->OwnsData( );
            }
            return true;
        }

        /// <summary>
        /// Returns a pointer to the internal buffer used to store the 
        /// data for the stream.
        /// </summary>
        /// <returns>Pointer to the data for the stream</returns>
        constexpr const Byte* Buffer( ) const noexcept
        {
            if ( data_ )
            {
                return data_->Buffer( );
            }
            return nullptr;
        }
        /// <summary>
        /// Returns a pointer to the internal buffer used to store the 
        /// data for the stream.
        /// </summary>
        /// <returns>Pointer to the data for the stream</returns>
        constexpr Byte* Buffer( ) noexcept
        {
            if ( data_ )
            {
                return data_->Buffer( );
            }
            return nullptr;
        }
        /// <summary>
        /// Releases ownership of the internal buffer to the caller.
        /// </summary>
        /// <remarks>
        /// If the MemoryStream owns the buffer, then Detach will 
        /// </remarks>
        /// <returns>the buffer</returns>
        [[nodiscard( "Call CoTaskMemFree to release the buffer returned by Detach" )]] Byte* Detach( )
        {
            if ( data_ )
            {
                return data_->Detach( );
            }
            return nullptr;
        }

        /// <summary>
        /// Gets the number of bytes allocated for this stream
        /// </summary>
        /// <returns>the number of bytes allocated for this stream</returns>
        long long Capacity( ) const
        {
            if ( data_ )
            {
                return data_->Capacity( );
            }
            return 0;
        }
        /// <summary>
        /// Sets the number of bytes allocated for this stream
        /// </summary>
        /// <remarks>
        /// This call will be ignored if the new capacity is less than 
        /// the current size of the MemoryStream.
        /// </remarks>
        /// <param name="size">the new size of the buffer</param>
        /// <returns>a reference to the MemoryStream</returns>
        void SetCapacity( long long size )
        {
            if ( !data_ )
            {
                data_ = new Data( );
            }
            data_->SetCapacity( size );
        }

        long long Position( ) const
        {
            return position_;
        }
        void SetPosition( long long position )
        {
            Seek( position, SeekOrigin::StartOfFile );
        }

        long long Size( ) const
        {
            if ( data_ )
            {
                return data_->Size( );
            }
            return 0;
        }
        void SetSize( long long size )
        {
            if ( !data_ )
            {
                data_ = new Data( );
            }
            data_->SetSize( size );
        }
        long long Read( void* buffer, size_t numberOfBytesToRead )
        {
            if ( data_ )
            {
                auto result = data_->Read( position_, buffer, numberOfBytesToRead );
                return result;
            }
            return 0;
        }
        long long Write( const void* buffer, size_t numberOfBytesToWrite )
        {
            if ( numberOfBytesToWrite )
            {
                if ( !data_ )
                {
                    data_ = new Data( );
                }
                auto result = data_->Write( position_, buffer, numberOfBytesToWrite );
                return result;
            }
            return 0;
        }
        long long Seek( long long offset, SeekOrigin seekOrigin )
        {
            if ( !data_ )
            {
                data_ = new Data( );
            }
            auto result = data_->Seek( position_, offset, seekOrigin );
            return result;
        }
    };

    static_assert( StreamReader<MemoryStream> );
    static_assert( StreamWriter<MemoryStream> );
    static_assert( StreamSeek<MemoryStream> );
    static_assert( StreamPosition<MemoryStream> );
    static_assert( StreamSize<MemoryStream> );
    static_assert( StreamFlush<MemoryStream> );
    static_assert( Stream<MemoryStream> );

    


    /// <summary>
    /// A stream wrapper for the IStream interface
    /// </summary>
    class IStreamStream
    {
        ::IStream* stream_;
    public:
        constexpr IStreamStream( ) noexcept
            : stream_( nullptr )
        { }

        IStreamStream( const IStreamStream& other ) = delete;
        constexpr IStreamStream( IStreamStream&& other ) noexcept
            : stream_( other.stream_ )
        {
            other.stream_ = nullptr;
        }


        constexpr IStreamStream( ::IStream* stream, bool addReference = true ) noexcept
            : stream_( stream )
        {
            if ( stream_ && addReference )
            {
                stream_->AddRef( );
            }
        }
        virtual ~IStreamStream( )
        {
            if ( stream_ )
            {
                stream_->Release( );
            }
        }

        IStreamStream& operator = ( const IStreamStream& other ) = delete;
        constexpr IStreamStream& operator = ( IStreamStream&& other ) noexcept
        {
            std::swap( stream_, other.stream_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return stream_ != nullptr;
        }


        constexpr ::IStream* BaseIStream( ) const noexcept
        {
            return stream_;
        }

        long long Position( ) const 
        {
            return const_cast<IStreamStream*>(this)->Seek( 0, SeekOrigin::CurrentPosition );
        }
        void SetPosition( long long position ) 
        {
            Seek( position, SeekOrigin::StartOfFile );
        }
        long long Size( ) const 
        {
            if ( stream_ )
            {
                STATSTG statstg;
                auto hr = stream_->Stat( &statstg, STATFLAG_NONAME );
                if ( FAILED( hr ) )
                {
                    CheckHRESULT( hr );
                }
                return static_cast<long long>( statstg.cbSize.QuadPart );
            }
            else
            {
                return 0;
            }
        }

        void SetSize( long long size )
        {
            ULARGE_INTEGER usize;
            usize.QuadPart = static_cast<unsigned long long>( size );
            auto hr = stream_->SetSize( usize );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void Flush( )
        {
            auto hr = stream_->Commit( STGC_DEFAULT );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        constexpr bool CanRead( ) const noexcept
        {
            return true;
        }
        // If CanSeek is false, Position, Seek, Length, and SetLength should throw.
        constexpr bool CanSeek( ) const noexcept
        {
            return true;
        }
        constexpr bool CanTimeout( ) const noexcept
        {
            return false;
        }
        constexpr bool CanWrite( ) const noexcept
        {
            return true;
        }

        long long Read( void* buffer, size_t numberOfBytesToRead ) 
        {
            ULONG bytesRead = 0;
            auto hr = stream_->Read( buffer, static_cast<ULONG>( numberOfBytesToRead ), &bytesRead );
            if ( FAILED( hr ) )
            {
                Core::CheckHRESULT( hr );
            }
            return bytesRead;
        }
        long long Write( const void* buffer, size_t numberOfBytesToWrite )
        {
            ULONG bytesWritten = 0;
            auto hr = stream_->Write( buffer, static_cast<ULONG>( numberOfBytesToWrite ), &bytesWritten );
            if ( FAILED( hr ) )
            {
                Core::CheckHRESULT( hr );
            }
            return bytesWritten;
        }
        long long Seek( long long offset, SeekOrigin seekOrigin )
        {
            ULARGE_INTEGER result;
            LARGE_INTEGER dst;
            dst.QuadPart = offset;
            auto hr = stream_->Seek( dst, static_cast<DWORD>( seekOrigin ), &result );
            if ( FAILED( hr ) )
            {
                Core::CheckHRESULT( hr );
            }
            return static_cast<long long>( result.QuadPart );
        }

        IStreamStream Clone( ) const
        {
            ::IStream* clone = nullptr;
            auto hr = stream_->Clone( &clone );
            if ( FAILED( hr ) )
            {
                Core::CheckHRESULT( hr );
            }
            IStreamStream result( clone, false );
            return result;
        }

    };

    static_assert( StreamReader<IStreamStream> );
    static_assert( StreamWriter<IStreamStream> );
    static_assert( StreamSeek<IStreamStream> );
    static_assert( StreamPosition<IStreamStream> );
    static_assert( StreamSize<IStreamStream> );
    static_assert( StreamFlush<IStreamStream> );
    static_assert( StreamClone<IStreamStream> );
    static_assert( StreamFeatureTests<IStreamStream> );
    static_assert( Stream<IStreamStream> );



    class IStreamMemoryStream : public IStreamStream
    {
        typedef IStreamStream Base;

        static ::IStream* CreateStream( )
        {
            ::IStream* istream = nullptr;
            auto hr = CreateStreamOnHGlobal( nullptr, TRUE, &istream );
            if ( FAILED( hr ) )
            {
                Core::CheckHRESULT( hr );
            }
            return istream;
        }
    public:
        IStreamMemoryStream( )
            : Base( CreateStream( ), false )
        { }
    };


    enum class FileAttributes : DWORD
    {
        Readonly = 0x00000001,
        Hidden = 0x00000002,
        System = 0x00000004,
        Directory = 0x00000010,
        Archive = 0x00000020,
        Device = 0x00000040,
        Normal = 0x00000080,
        Temporary = 0x00000100,
        SparseFile = 0x00000200,
        ReparsePoint = 0x00000400,
        Compressed = 0x00000800,
        Offline = 0x00001000,
        NotContentIndexed = 0x00002000,
        Encrypted = 0x00004000,
        IntegrityStream = 0x00008000,
        Virtual = 0x00010000,
        NoScrubData = 0x00020000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FileAttributes, DWORD );

    enum class FileAccess : DWORD
    {
        // Read access to the file. Data can be read from the file. Combine with Write
        // for read/write access.
        Read = FILE_READ_ACCESS,
        // Write access to the file. Data can be written to the file. Combine with Read
        // for read/write access.
        Write = FILE_WRITE_ACCESS,
        // Read and write access to the file. Data can be written to and read from the file.
        ReadWrite = FILE_READ_ACCESS | FILE_WRITE_ACCESS,
        // the right to append data to the file
        Append = FILE_APPEND_DATA,
        // The right to read extended file attributes
        ReadExtendedAttributes = FILE_READ_EA,
        // The right to write extended file attributes
        WriteExtendedAttributes = FILE_WRITE_EA,
        // The right to read file attributes
        ReadAttributes = FILE_READ_ATTRIBUTES,
        // The right to set file attributes
        WriteAttributes = FILE_WRITE_ATTRIBUTES,

        StandardRightsRead = STANDARD_RIGHTS_READ,
        StandardRightsWrite = STANDARD_RIGHTS_WRITE,
        Default = FILE_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FileAccess, DWORD );

    enum class FileMode : DWORD
    {
        // Specifies that the operating system should create a new file. 
        CreateNew = CREATE_NEW,
        // Specifies that the operating system should create a new file. If the file
        // already exists, it will be overwritten. 
        Create = CREATE_ALWAYS,
        // Specifies that the operating system should open an existing file. The ability
        // to open the file is dependent on the value specified by the FileAccess
        // enumeration.
        Open = OPEN_EXISTING,
        // Specifies that the operating system should open a file if it exists; otherwise,
        // a new file should be created. 
        OpenOrCreate = OPEN_ALWAYS,
        // Specifies that the operating system should open an existing file. When the
        // file is opened, it should be truncated so that its size is zero bytes.
        Truncate = TRUNCATE_EXISTING,
        // Opens the file if it exists and seeks to the end of the file, or creates
        // a new file.
        Append = 6,
        Default = OpenOrCreate
    };


    enum class FileShare : DWORD
    {
        // Declines sharing of the current file. Any request to open the file (by this
        // process or another process) will fail until the file is closed.
        None = 0,
        // Allows subsequent opening of the file for reading. If this flag is not specified,
        // any request to open the file for reading (by this process or another process)
        // will fail until the file is closed.
        Read = 1,
        // Allows subsequent opening of the file for writing. If this flag is not specified,
        // any request to open the file for writing (by this process or another process)
        // will fail until the file is closed.
        Write = 2,
        // Allows subsequent opening of the file for reading or writing. If this flag
        // is not specified, any request to open the file for reading or writing (by
        // this process or another process) will fail until the file is closed.
        ReadWrite = 3,
        // Allows subsequent deleting of a file.
        Delete = 4,
        // Makes the file handle inheritable by child processes. 
        Inheritable = 16,
        Default = None
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FileShare, DWORD );

    enum class FileOptions : DWORD
    {
        // Indicates that the system should write through any intermediate cache and
        // go directly to disk.
        WriteThrough = FILE_FLAG_WRITE_THROUGH,
        // Indicates no additional parameters.
        None = 0,
        // Indicates that a file is encrypted and can be decrypted only by using the
        // same user account used for encryption.
        Encrypted = 0x00004000,
        // Indicates that a file is automatically deleted when it is no longer in use.
        DeleteOnClose = FILE_FLAG_DELETE_ON_CLOSE,
        // Indicates that the file is to be accessed sequentially from beginning to
        // end. The system can use this as a hint to optimize file caching. If an application
        // moves the file pointer for random access, optimum caching may not occur;
        // however, correct operation is still guaranteed.
        SequentialScan = FILE_FLAG_SEQUENTIAL_SCAN,
        // Indicates that the file is accessed randomly. The system can use this as
        // a hint to optimize file caching.
        RandomAccess = FILE_FLAG_RANDOM_ACCESS,
        // Indicates that a file can be used for asynchronous reading and writing.
        Asynchronous = FILE_FLAG_OVERLAPPED,
        Default = FILE_FLAG_SEQUENTIAL_SCAN
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FileOptions, DWORD );

    enum class FileSystemRights : DWORD
    {
        // No None field - An ACE with the value 0 cannot grant nor deny.
        ReadData = 0x000001,
        ListDirectory = ReadData,     // For directories
        WriteData = 0x000002,
        CreateFiles = WriteData,    // For directories
        AppendData = 0x000004,
        CreateDirectories = AppendData,   // For directories
        ReadExtendedAttributes = 0x000008,
        WriteExtendedAttributes = 0x000010,
        ExecuteFile = 0x000020,     // For files
        Traverse = ExecuteFile,  // For directories
        // DeleteSubdirectoriesAndFiles only makes sense on directories, but 
        // the shell explicitly sets it for files in its UI.  So we'll include 
        // it in FullControl.
        DeleteSubdirectoriesAndFiles = 0x000040,
        ReadAttributes = 0x000080,
        WriteAttributes = 0x000100,
        Delete = 0x010000,
        ReadPermissions = 0x020000,
        ChangePermissions = 0x040000,
        TakeOwnership = 0x080000,
        // From the Core File Services team, CreateFile always requires 
        // SYNCHRONIZE access.  Very tricksy, CreateFile is.
        Synchronize = 0x100000,  // Can we wait on the handle?
        FullControl = 0x1F01FF,

        // These map to what Explorer sets, and are what most users want.
        // However, an ACL editor will also want to set the Synchronize
        // bit when allowing access, and exclude the synchronize bit when
        // denying access.
        Read = ReadData | ReadExtendedAttributes | ReadAttributes | ReadPermissions,
        ReadAndExecute = Read | ExecuteFile,
        Write = WriteData | AppendData | WriteExtendedAttributes | WriteAttributes,
        Modify = ReadAndExecute | Write | Delete,
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FileSystemRights, DWORD );

    template<typename StringT>
        requires IsStdBasicString<StringT>
    class FileSystemEntry
    {
    public:
        using StringType = StringT;
    private:
        StringType parentDirectory_;
        StringType name_;
        FileAttributes attributes_;
        DateTime creationTime_;
        DateTime lastAccessTime_;
        DateTime lastWriteTime_;

    public:
        FileSystemEntry( const StringType& parentDirectory, const StringType& name, FileAttributes attributes, const DateTime& creationTime, const DateTime& lastAccessTime, const DateTime& lastWriteTime )
            : parentDirectory_(parentDirectory), name_(name), attributes_(attributes),
            creationTime_(creationTime), lastAccessTime_(lastAccessTime), lastWriteTime_(lastWriteTime)
        { }


        constexpr const std::wstring& ParentDirectory( ) const noexcept
        {
            return parentDirectory_;
        }
        constexpr const std::wstring& Name( ) const noexcept
        {
            return name_;
        }

        constexpr FileAttributes Attributes( ) const noexcept
        {
            return attributes_;
        }

        constexpr DateTime CreationTime( ) const noexcept
        {
            return creationTime_;
        }
        constexpr DateTime LastAccessTime( ) const noexcept
        {
            return lastAccessTime_;
        }
        constexpr DateTime LastWriteTime( ) const noexcept
        {
            return lastWriteTime_;
        }

    };

    template<typename StringT>
        requires IsStdBasicString<StringT>
    using DirectoryInfo = FileSystemEntry<StringT>;

    template<typename StringT>
        requires IsStdBasicString<StringT>
    class FileInfo : public FileSystemEntry<StringT>
    {
    public:
        using StringType = StringT;
    private:
        long long fileSize_;
    public:
        typedef FileSystemEntry<StringT> Base;
        FileInfo( const StringType& parentDirectory, const StringType& name, FileAttributes attributes, const DateTime& creationTime, const DateTime& lastAccessTime, const DateTime& lastWriteTime, long long fileSize )
            : Base(parentDirectory, name, attributes, creationTime, lastAccessTime, lastWriteTime),
            fileSize_(fileSize)
        {
        }


        constexpr long long FileSize( ) const noexcept
        {
            return fileSize_;
        }

    };


    


    template<typename T>
        requires IsStdBasicString<T>
    class SplitPath
    {
    public:
        using string_type = T;
        using char_type = typename string_type::value_type;
    private:
        string_type drive_;
        string_type directory_;
        string_type name_;
        string_type extension_;
    public:


        SplitPath( const char_type* path )
        {
            char_type drive[_MAX_DRIVE + 1];
            char_type dir[_MAX_DIR + 1];
            char_type name[_MAX_FNAME + 1];
            char_type extension[_MAX_EXT + 1];

            if constexpr ( sizeof(char_type) == 2 )
            {
                _wsplitpath_s(path, drive, dir, name, extension);
            }
            else
            {
                _splitpath_s(path, drive, dir, name, extension);
                
            }
            if ( drive[0] )
            {
                drive_ = drive;
            }
            if ( dir[0] )
            {
                directory_ = dir;
            }
            if ( name[0] )
            {
                name_ = name;
            }
            if ( extension[0] )
            {
                extension_ = extension;
            }
        }

        SplitPath( const string_type& path )
            : SplitPath( path.c_str() )
        { }


        bool IsDriveValid( ) const noexcept
        {
            return drive_.empty( ) == false;
        }
        /// <summary>
        /// Returns drive letter followed by ':'
        /// </summary>
        const string_type& Drive( ) const noexcept
        {
            return drive_;
        }
        bool IsDirectoryValid( ) const noexcept
        {
            return directory_.empty( ) == false;
        }

        bool IsRootDirectory( ) const noexcept
        {
            if constexpr ( std::is_same_v<T, char> )
            {
                return IsDirectoryValid( ) && ( directory_ == "\\" || directory_ == "/" );
            }
            else
            {
                return IsDirectoryValid( ) && ( directory_ == L"\\" || directory_ == L"/" );
            }
        }

        /// <summary>
        /// Returns the directory path, including the trailing slash. 
        /// </summary>
        const string_type& Directory( ) const noexcept
        {
            return directory_;
        }

        /// <summary>
        /// Returns the directory path, without the trailing slash. 
        /// </summary>
        string_type DirectoryPath( ) const
        {
            if ( IsDriveValid( ) && IsDirectoryValid( ) )
            {
                return Drive( ) + Directory( );
            }
            else if ( IsDirectoryValid( ) )
            {
                return Directory( );
            }
            else if ( IsDriveValid( ) )
            {
                return Drive( );
            }
            else
            {
                return string_type( );
            }
        }


        bool IsNameValid( ) const noexcept
        {
            return name_.empty( ) == false;
        }

        /// <summary>
        /// Returns the base filename (no extension). 
        /// </summary>
        const string_type& Name( ) const noexcept
        {
            return name_;
        }

        bool IsExtensionValid( ) const noexcept
        {
            return extension_.empty( ) == false;
        }
        /// <summary>
        /// Returns the filename extension, including leading period (.).
        /// </summary>
        const string_type& Extension( ) const noexcept
        {
            return extension_;
        }
    };




    class Path
    {
    public:
        static constexpr wchar_t DirectorySeparatorChar = '\\';
        static constexpr wchar_t AltDirectorySeparatorChar = '/';
        static constexpr wchar_t VolumeSeparatorChar = ':';
        static constexpr wchar_t PathSeparator = ';';

        static constexpr int MaxPath = 260;
        static constexpr int MaxDirectoryLength = 255;

        
        template<typename StringT>
            requires (IsWideString<StringT> || IsAnsiString<StringT> || IsWideStringView<StringT> || IsAnsiStringView<StringT>)
        static bool IsDirectorySeparator(const StringT& str) noexcept
        {
            using StringType = std::remove_cvref_t<StringT>;
            using CharT = typename StringType::value_type;
            return str.length() == 1 && ((str[0] == static_cast<CharT>(DirectorySeparatorChar)) || (str[0] == static_cast<CharT>(AltDirectorySeparatorChar)));
        }

        template<typename StringT>
            requires (IsWideString<StringT> || IsAnsiString<StringT> || IsWideStringView<StringT> || IsAnsiStringView<StringT>)
        static bool EndsWithDirectorySeparator(const StringT& str) noexcept
        {
            using StringType = std::remove_cvref_t<StringT>;
            using CharT = typename StringType::value_type;
            if (str.length() > 0)
            {
                CharT last = str.back();
                return (last == static_cast<CharT>(DirectorySeparatorChar)) || (last == static_cast<CharT>(AltDirectorySeparatorChar));
            }
            return false;
        }
        template<typename StringT>
            requires (IsWideString<StringT> || IsAnsiString<StringT> || IsWideStringView<StringT> || IsAnsiStringView<StringT>)
        static bool StartsWithDirectorySeparator(const StringT& str) noexcept
        {
            using StringType = std::remove_cvref_t<StringT>;
            using CharT = typename StringType::value_type;
            if (str.length() > 0)
            {
                CharT first = str.front();
                return (first == static_cast<CharT>(DirectorySeparatorChar)) || (first == static_cast<CharT>(AltDirectorySeparatorChar));
            }
            return false;
        }



        HCC_EXPORT static std::wstring Append( const std::wstring& startOfPath, const std::wstring& remainingPath );
        HCC_EXPORT static std::string Append( const std::string& startOfPath, const std::string& remainingPath );

        HCC_EXPORT static std::wstring ChangeExtension( const std::wstring& path, const std::wstring& newExtension );
        HCC_EXPORT static std::wstring GetLongPathName( const std::wstring& path );
        HCC_EXPORT static std::wstring GetFullPathName( const std::wstring& path );
        HCC_EXPORT static std::wstring GetFullPathName( const std::wstring& path, std::wstring::size_type& indexOfFileName );

        HCC_EXPORT static std::string GetFullPathName(const std::string& path);
        HCC_EXPORT static std::string GetFullPathName(const std::string& path, std::string::size_type& indexOfFileName);

        HCC_EXPORT static std::string FullPath( const std::string& path );

        HCC_EXPORT static std::wstring GetParentDirectory( const wchar_t* path );
        static std::wstring GetParentDirectory( const std::wstring& path )
        {
            return GetParentDirectory( path.c_str() );
        }
        HCC_EXPORT static std::string GetParentDirectory( const char* path );
        static std::string GetParentDirectory( const std::string& path )
        {
            return GetParentDirectory( path.c_str( ) );
        }

        // Compares two paths to determine if they share a common prefix. 
        // A prefix is one of these types: "C:\\", ".", "..", "..\\"
        HCC_EXPORT static size_t CommonPrefix( const wchar_t* path1, const wchar_t* path2, wchar_t* commonPrefix = nullptr );


        // Searches a path and determines if it is relative
        HCC_EXPORT static bool IsRelative( const std::wstring& path );
        // Searches a path and determines if it is relative
        HCC_EXPORT static bool IsRelative( const wchar_t* path );

        // Determines whether a path string refers to the root of a volume
        HCC_EXPORT static bool IsRoot( const std::wstring& path );
        // Determines whether a path string refers to the root of a volume
        HCC_EXPORT static bool IsRoot( const wchar_t* path );

        // Determines if a path string is a valid Universal Naming 
        // Convention (UNC) path, as opposed to a path based on a drive letter
        HCC_EXPORT static bool IsUNC( const std::wstring& path );
        // Determines if a path string is a valid Universal Naming 
        // Convention (UNC) path, as opposed to a path based on a drive letter
        HCC_EXPORT static bool IsUNC( const wchar_t* path );
    };


    enum class FileAccessRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        /// <summary>
        /// The right to write data to the file.
        /// </summary>
        ReadData = FILE_READ_DATA,
        /// <summary>
        /// The right to write data to the file.
        /// </summary>
        WriteData = FILE_WRITE_DATA,
        /// <summary>
        /// The right to append data to the file. 
        /// </summary>
        /// <remarks>
        /// For local files, write operations will not overwrite 
        /// existing data if this flag is specified without 
        /// FileAccessRights::Write.
        /// </remarks>
        Append = FILE_APPEND_DATA,
        ReadExtendedAttributes = FILE_READ_EA,
        WriteExtendedAttributes = FILE_WRITE_EA,
        Execute = FILE_EXECUTE,
        /// <summary>
        /// The right to read file attributes.
        /// </summary>
        ReadAttributes = FILE_READ_ATTRIBUTES,
        WriteAttributes = FILE_WRITE_ATTRIBUTES,

        Read = ReadData | ReadExtendedAttributes | ReadAttributes | Synchronize | ReadPermissions,
        Write = WriteData | WriteExtendedAttributes | WriteAttributes | Synchronize | ReadPermissions,

        FullControl = FILE_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FileAccessRights, DWORD );


    /// <summary>
    /// The access mask for a file
    /// </summary>
    class FileAccessMask : public Security::AccessMaskT<FileAccessMask, FileAccessRights>
    {
    public:
        using Base = Security::AccessMaskT<FileAccessMask, FileAccessRights>;
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( FILE_GENERIC_READ ),
            static_cast<ACCESS_MASK>( FILE_GENERIC_WRITE ),
            static_cast<ACCESS_MASK>( FILE_GENERIC_EXECUTE ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( FileAccessRights::FullControl ) ) };



        constexpr FileAccessMask( ) noexcept
        {
        }
        constexpr explicit FileAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit FileAccessMask( FileAccessRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit FileAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit FileAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit FileAccessMask( const FileAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        explicit FileAccessMask( const FileAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit FileAccessMask( FileAccessRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit FileAccessMask( FileAccessRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }

        constexpr bool CanReadData( ) const noexcept
        {
            return Check<FileAccessRights::ReadData>( );
        }
        constexpr void SetReadData( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::ReadData>( value );
        }

        constexpr bool CanWriteData( ) const noexcept
        {
            return Check<FileAccessRights::WriteData>( );
        }
        constexpr void SetWriteData( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::WriteData>( value );
        }

        constexpr bool CanAppend( ) const noexcept
        {
            return Check<FileAccessRights::Append>( );
        }
        constexpr void SetAppend( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::Append>( value );
        }

        constexpr bool CanReadExtendedAttributes( ) const noexcept
        {
            return Check<FileAccessRights::ReadExtendedAttributes>( );
        }
        constexpr void SetReadExtendedAttributes( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::ReadExtendedAttributes>( value );
        }

        constexpr bool CanWriteExtendedAttributes( ) const noexcept
        {
            return Check<FileAccessRights::WriteExtendedAttributes>( );
        }
        constexpr void SetWriteExtendedAttributes( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::WriteExtendedAttributes>( value );
        }

        constexpr bool CanExecute( ) const noexcept
        {
            return Check<FileAccessRights::Execute>( );
        }
        constexpr void SetExecute( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::Execute>( value );
        }

        constexpr bool CanReadAttributes( ) const noexcept
        {
            return Check<FileAccessRights::ReadAttributes>( );
        }
        constexpr void SetReadAttributes( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::ReadAttributes>( value );
        }

        constexpr bool CanWriteAttributes( ) const noexcept
        {
            return Check<FileAccessRights::WriteAttributes>( );
        }
        constexpr void SetWriteAttributes( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::WriteAttributes>( value );
        }

        constexpr bool CanRead( ) const noexcept
        {
            return Check<FileAccessRights::Read>( );
        }
        constexpr void SetRead( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::Read>( value );
        }
        
        constexpr bool CanWrite( ) const noexcept
        {
            return Check<FileAccessRights::Write>( );
        }
        constexpr void SetWrite( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::Write>( value );
        }

        constexpr bool CanReadAndWrite( ) const noexcept
        {
            return Check<FileAccessRights::Read | FileAccessRights::Write>( );
        }
        constexpr void SetReadAndWrite( bool value = true ) noexcept
        {
            SetBitFlag<FileAccessRights::Read | FileAccessRights::Write>( value );
        }


    };

    enum class DirectoryAccessRights : DWORD
    {
        HCC_COMMON_CORE_SECURITY_BASE_ENUM_ACCESS_RIGHTS,
        /// <summary>
        /// The right to create a file in the directory
        /// </summary>
        AddFile = FILE_ADD_FILE,
        /// <summary>
        /// The right to create a subdirectory
        /// </summary>
        AddSubDirectory = FILE_ADD_SUBDIRECTORY,
        ReadExtendedAttributes = FILE_READ_EA,
        WriteExtendedAttributes = FILE_WRITE_EA,
        Traverse = FILE_TRAVERSE,
        DeleteChild = FILE_DELETE_CHILD,
        /// <summary>
        /// The right to read directory attributes.
        /// </summary>
        ReadAttributes = FILE_READ_ATTRIBUTES,
        WriteAttributes = FILE_WRITE_ATTRIBUTES,

        Read = Traverse | ReadExtendedAttributes | ReadAttributes | Synchronize | ReadPermissions,
        Write = AddFile | AddSubDirectory | DeleteChild |WriteExtendedAttributes | WriteAttributes | Synchronize | ReadPermissions,

        FullControl = FILE_ALL_ACCESS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DirectoryAccessRights, DWORD );

    /// <summary>
    /// The access mask for a directory
    /// </summary>
    class DirectoryAccessMask : public Security::AccessMaskT<DirectoryAccessMask, DirectoryAccessRights>
    {
    public:
        using Base = Security::AccessMaskT<DirectoryAccessMask, DirectoryAccessRights>;
        static constexpr const Security::GenericMapping Mapping{
            static_cast<ACCESS_MASK>( FILE_GENERIC_READ ),
            static_cast<ACCESS_MASK>( FILE_GENERIC_WRITE ),
            static_cast<ACCESS_MASK>( FILE_GENERIC_EXECUTE ),
            static_cast<ACCESS_MASK>( static_cast<ACCESS_MASK>( DirectoryAccessRights::FullControl ) ) };

        constexpr DirectoryAccessMask( ) noexcept
        {
        }
        constexpr explicit DirectoryAccessMask( ACCESS_MASK mask ) noexcept
            : Base( mask )
        {
        }

        constexpr explicit DirectoryAccessMask( DirectoryAccessRights rights ) noexcept
            : Base( rights )
        {
        }

        explicit DirectoryAccessMask( ACCESS_MASK mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }
        explicit DirectoryAccessMask( ACCESS_MASK mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask, genericMapping )
        {
        }

        explicit DirectoryAccessMask( const DirectoryAccessMask& mask, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }
        explicit DirectoryAccessMask( const DirectoryAccessMask& mask, const Security::GenericMapping& genericMapping ) noexcept
            : Base( mask.Value( ), genericMapping )
        {
        }

        explicit DirectoryAccessMask( DirectoryAccessRights rights, const GENERIC_MAPPING& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }
        explicit DirectoryAccessMask( DirectoryAccessRights rights, const Security::GenericMapping& genericMapping ) noexcept
            : Base( rights, genericMapping )
        {
        }

        constexpr bool CanAddFile( ) const noexcept
        {
            return Check<DirectoryAccessRights::AddFile>( );
        }
        constexpr void SetAddFile( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::AddFile>( value );
        }

        constexpr bool CanAddSubDirectory( ) const noexcept
        {
            return Check<DirectoryAccessRights::AddSubDirectory>( );
        }
        constexpr void SetAddSubDirectory( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::AddSubDirectory>( value );
        }

        constexpr bool CanReadExtendedAttributes( ) const noexcept
        {
            return Check<DirectoryAccessRights::ReadExtendedAttributes>( );
        }
        constexpr void SetReadExtendedAttributes( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::ReadExtendedAttributes>( value );
        }

        constexpr bool CanWriteExtendedAttributes( ) const noexcept
        {
            return Check<DirectoryAccessRights::WriteExtendedAttributes>( );
        }
        constexpr void SetWriteExtendedAttributes( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::WriteExtendedAttributes>( value );
        }

        constexpr bool CanTraverse( ) const noexcept
        {
            return Check<DirectoryAccessRights::Traverse>( );
        }
        constexpr void SetTraverse( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::Traverse>( value );
        }

        constexpr bool CanDeleteChild( ) const noexcept
        {
            return Check<DirectoryAccessRights::DeleteChild>( );
        }
        constexpr void SetDeleteChild( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::DeleteChild>( value );
        }

        constexpr bool CanReadAttributes( ) const noexcept
        {
            return Check<DirectoryAccessRights::ReadAttributes>( );
        }
        constexpr void SetReadAttributes( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::ReadAttributes>( value );
        }

        constexpr bool CanWriteAttributes( ) const noexcept
        {
            return Check<DirectoryAccessRights::WriteAttributes>( );
        }
        constexpr void SetWriteAttributes( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::WriteAttributes>( value );
        }


        constexpr bool CanRead( ) const noexcept
        {
            return Check<DirectoryAccessRights::Read>( );
        }
        constexpr void SetRead( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::Read>( value );
        }

        constexpr bool CanWrite( ) const noexcept
        {
            return Check<DirectoryAccessRights::Write>( );
        }
        constexpr void SetWrite( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::Write>( value );
        }

        constexpr bool CanReadAndWrite( ) const noexcept
        {
            return Check<DirectoryAccessRights::Read | DirectoryAccessRights::Write>( );
        }
        constexpr void SetReadAndWrite( bool value = true ) noexcept
        {
            SetBitFlag<DirectoryAccessRights::Read | DirectoryAccessRights::Write>( value );
        }

    };



    class File
    {
    public:
        template<typename StringT>
            requires (IsWideString<StringT> || IsAnsiString<StringT>)
        static std::remove_cvref_t<StringT> GetExecutableFilename()
        {
            using StringType = std::remove_cvref_t<StringT>;
            static constexpr bool IsWide = IsWideString<StringType>;
            using CharT = StringType::value_type;
            CharT buffer[MAX_PATH + 1] = { 0, };
            DWORD size = 0;
            if constexpr (IsWide)
            {
                size = GetModuleFileNameW(nullptr, buffer, sizeof(buffer) / sizeof(CharT));
            }
            else
            {
                size = GetModuleFileNameA(nullptr, buffer, sizeof(buffer) / sizeof(CharT));
            }
            if (size == 0)
            {
                ThrowLastOSError();
            }
            return StringType(buffer, static_cast<size_t>(size));
        }

        HCC_EXPORT static void Delete( const wchar_t* filePath );

        HCC_EXPORT static void Delete( const char* filePath );

        template<typename T>
            requires std::is_same_v<std::string,std::remove_cv_t<T>> || std::is_same_v<std::wstring, std::remove_cv_t<T>>
        static void Delete( const T& filePath )
        {
            Delete( filePath.c_str( ) );
        }

        HCC_EXPORT static bool DeleteIfExist( const wchar_t* filePath );
        HCC_EXPORT static bool DeleteIfExist( const char* filePath );

        template<typename T>
            requires std::is_same_v<std::string, std::remove_cv_t<T>> || std::is_same_v<std::wstring, std::remove_cv_t<T>>
        static bool DeleteIfExist( const T & filePath )
        {
            return DeleteIfExist( filePath.c_str( ) );
        }


        HCC_EXPORT static bool Exist( const std::wstring& filePath );
        HCC_EXPORT static bool Exist( const wchar_t* filePath );

        HCC_EXPORT static bool Exist( const std::string& filePath );
        HCC_EXPORT static bool Exist( const char* filePath );

        HCC_EXPORT static UInt64 Size( const wchar_t* filePath );
        HCC_EXPORT static UInt64 Size( const char* filePath );

        template<typename T>
            requires IsStdBasicString<T>
        static UInt64 Size( const T& filePath )
        {
            return Size( filePath.c_str() );
        }

        HCC_EXPORT static bool Search( const std::wstring& directoryPath, const std::wstring& filename, bool recurseSubdirectories, std::wstring& result );
        HCC_EXPORT static bool Search( const std::string& directoryPath, const std::string& filename, bool recurseSubdirectories, std::string& result );



        /// <summary>
        /// Opens a text file, reads all lines of the file, and then closes the file.
        /// </summary>
        HCC_EXPORT static void ReadAllLines( const std::string& filePath, std::vector<std::string>& destination );
        static std::vector<std::string> ReadAllLines( const std::string& filePath )
        {
            std::vector<std::string> result;
            ReadAndAppendAllLinesTo( filePath, result );
            return result;
        }

        HCC_EXPORT static void ReadAndAppendAllLinesTo( const std::string& filePath, std::vector<std::string>& destination );

        HCC_EXPORT static void WriteAllLines( const std::string& filePath, const std::vector<std::string>& contents );

        /// <summary>
        /// Opens a text file, and appends all lines of the file to the target, and then closes the file.
        /// </summary>
        HCC_EXPORT static void ReadAllText( const std::string& filePath, std::string& destination );

        static std::string ReadAllText( const std::string& filePath )
        {
            std::string result;
            ReadAndAppendAllTextTo( filePath, result );
            return result;
        }

        HCC_EXPORT static void ReadAndAppendAllTextTo( const std::string& filePath, std::string& destination );

        HCC_EXPORT static void WriteAllText( const std::string& filePath, const std::string& contents );


    };


    class Directory
    {
    public:
        /// <summary>
        /// Retrieves the path of the directory designated for temporary files.
        /// </summary>
        /// <remarks>
        /// The returned string ends with a backslash, for example, "C:\TEMP\".
        /// </remarks>
        /// <returns>The path of the directory designated for temporary files</returns>
        HCC_EXPORT static std::wstring GetTemporary();
        /// <summary>
        /// Retrieves the path of the directory designated for temporary files.
        /// </summary>
        /// <remarks>
        /// The returned string ends with a backslash, for example, "C:\TEMP\".
        /// </remarks>
        /// <returns>The path of the directory designated for temporary files</returns>
        HCC_EXPORT static std::string GetTemporaryA();

        /// <summary>
        /// Retrieves the path of the directory designated for temporary files.
        /// </summary>
        /// <remarks>
        /// The returned string ends with a backslash, for example, "C:\TEMP\".
        /// </remarks>
        /// <returns>The path of the directory designated for temporary files</returns>
        template<typename StringT>
            requires (IsWideString<StringT> || IsAnsiString<StringT>)
        static std::remove_cvref_t<StringT> GetTemporaryDirectory()
        {
            using StringType = std::remove_cvref_t<StringT>;
            static constexpr bool isWide = IsWideString<StringType>;
            using CharT = std::conditional_t<isWide, wchar_t, char>;
            CharT buffer[MAX_PATH + 2] = {};
            DWORD rc = 0;
            if constexpr (isWide)
            {
                rc = GetTempPathW(MAX_PATH + 1, buffer);
            }
            else
            {
                rc = GetTempPathA(MAX_PATH + 1, buffer);
            }
            return StringType(buffer, static_cast<size_t>(rc));
        }

        HCC_EXPORT static std::wstring GetExecutableDirectoryW( );
        HCC_EXPORT static std::string GetExecutableDirectoryA( );

        template<typename StringT>
            requires (IsWideString<StringT> || IsAnsiString<StringT>)
        static std::remove_cvref_t<StringT> GetExecutableDirectory()
        {
            using StringType = std::remove_cvref_t<StringT>;
            static constexpr bool isWide = IsWideString<StringType>;
            if constexpr (isWide)
            {
                return GetExecutableDirectoryW();
            }
            else
            {
                return GetExecutableDirectoryA();
            }
        }

        HCC_EXPORT static std::wstring Current( );
        HCC_EXPORT static std::string CurrentA( );
        HCC_EXPORT static bool Exist( const wchar_t* directoryPath );
        static bool Exist( const std::wstring& directoryPath )
        {
            return Exist( directoryPath.c_str() );
        }
        HCC_EXPORT static bool Exist( const char* directoryPath );
        static bool Exist( const std::string& directoryPath )
        {
            return Exist( directoryPath.c_str( ) );
        }

        HCC_EXPORT static void Create( const wchar_t* directoryPath );
        HCC_EXPORT static void Create( const char* directoryPath );
        static void Create( const std::wstring& directoryPath )
        {
            Create( directoryPath.c_str( ) );
        }
        static void Create( const std::string& directoryPath )
        {
            Create( directoryPath.c_str( ) );
        }

    };

    template<typename CharT>
    requires ( std::is_same_v<std::remove_cvref_t<CharT>, char> || std::is_same_v<std::remove_cvref_t<CharT>, wchar_t>)
    class FindData : public std::conditional_t< std::is_same_v<std::remove_cvref_t<CharT>, wchar_t>, WIN32_FIND_DATAW, WIN32_FIND_DATAA>
    {
    public:
        using CharType = std::remove_cvref_t<CharT>;
        using Base = std::conditional_t< std::is_same_v<CharType, wchar_t>, WIN32_FIND_DATAW, WIN32_FIND_DATAA>;

        constexpr FindData() noexcept
            : Base{}
        {
        }

        IO::FileAttributes Attributes() const
        {
            return static_cast<IO::FileAttributes>(Base::dwFileAttributes);
        }

        DateTime CreationTime() const
        {
            return DateTime::FromFileTime(Base::ftCreationTime);
        }

        DateTime LastAccessTime() const
        {
            return DateTime::FromFileTime(Base::ftLastAccessTime);
        }

        DateTime LastWriteTime() const
        {
            return DateTime::FromFileTime(Base::ftLastWriteTime);
        }

        UInt64 Size() const
        {
            return (static_cast<UInt64>(Base::nFileSizeHigh) << 32) + static_cast<UInt64>(Base::nFileSizeLow);
        }

        const CharType* FileName() const
        {
            return Base::cFileName;
        }

        const CharType* AlternateFileName() const
        {
            return Base::cAlternateFileName;
        }
    };

    template<typename StringT>
        requires IsStdBasicString<StringT>
    class FileSystemEntries
    {
    public:
        using StringType = std::remove_cvref_t<StringT>;
        using CharType = typename StringType::value_type;
        using FindDataType = FindData<CharType>;
        
        static constexpr bool IsWide = std::is_same_v<CharType, wchar_t>;
    private:
        StringType path_;
        StringType searchPattern_;
        HANDLE searchHandle_;
    protected:
        FindDataType data_;
    public:
        FileSystemEntries(const StringType& path, const StringType& searchPattern)
            : path_(path), searchPattern_(searchPattern), searchHandle_(INVALID_HANDLE_VALUE)
        {
            while (path_.empty() == false && (path_.back() == '\\' || path_.back() == '/'))
            {
                path_.resize(path_.length() - 1);
            }
            path_ = Path::GetFullPathName(path);
            
        }
        FileSystemEntries(const StringType& searchPattern)
            : searchPattern_(searchPattern), searchHandle_(INVALID_HANDLE_VALUE)
        {
            if constexpr (IsWide)
            {
                path_ = Directory::Current();
            }
            else
            {
                path_ = Directory::CurrentA();
            }
        }
        


        ~FileSystemEntries()
        {
            if (searchHandle_ != INVALID_HANDLE_VALUE)
            {
                FindClose(searchHandle_);
            }
        }

        void Reset()
        {
            if (searchHandle_ != INVALID_HANDLE_VALUE)
            {
                FindClose(searchHandle_);
                searchHandle_ = INVALID_HANDLE_VALUE;
            }
        }

        bool Read()
        {
            memset(&data_, 0, sizeof(FindDataType));
            if (searchHandle_ == INVALID_HANDLE_VALUE)
            {
                StringType s = path_;
                s += static_cast<CharType>('\\');
                s += searchPattern_;
                if constexpr (IsWide)
                {
                    searchHandle_ = FindFirstFileExW(s.c_str(), FindExInfoBasic, &data_, FindExSearchNameMatch, nullptr, 0);
                }
                else
                {
                    searchHandle_ = FindFirstFileExA(s.c_str(), FindExInfoBasic, &data_, FindExSearchNameMatch, nullptr, 0);
                }
                if (searchHandle_ == INVALID_HANDLE_VALUE)
                {
                    auto error = GetLastError();
                    if (error != ERROR_FILE_NOT_FOUND)
                    {
                        ThrowOSError(error);
                    }
                    else
                    {
                        return false;
                    }
                }
                return true;
            }
            else
            {
                BOOL rc;
                if constexpr (IsWide)
                {
                    rc = FindNextFileW(searchHandle_, &data_);
                }
                else
                {
                    rc = FindNextFileA(searchHandle_, &data_);
                }

                if (rc == 0)
                {
                    auto error = GetLastError();
                    if (error != ERROR_NO_MORE_FILES)
                    {
                        ThrowOSError(error);
                    }
                    else
                    {
                        return false;
                    }
                }
                return true;
            }
        }

        const CharType* Name() const noexcept
        {
            return data_.cFileName;
        }

        StringType FullPath() const
        {
            StringType result = path_;
            result += static_cast<CharType>('\\');
            result += data_.cFileName;
            return result;
        }

        const FindDataType& Data() const
        {
            return data_;
        }
    };

    template<typename CharT>
    requires (std::is_same_v<std::remove_cvref_t<CharT>,char> || std::is_same_v<std::remove_cvref_t<CharT>, wchar_t>)
    FileSystemEntries(const CharT* b, const CharT* e)->FileSystemEntries<std::basic_string<std::remove_cvref_t<CharT>>>;




    template <typename DerivedT, HANDLE InvalidHandleV = INVALID_HANDLE_VALUE>
    class SystemStream
    {

        HANDLE handle_;
    public:
        using DerivedType = DerivedT;
        static constexpr HANDLE InvalidHandleValue = InvalidHandleV;

        constexpr explicit SystemStream( ) noexcept
            : handle_( InvalidHandleValue )
        {
        }

        constexpr explicit SystemStream( HANDLE handle ) noexcept
            : handle_( handle )
        {
        }
        ~SystemStream( )
        {
            if ( handle_ != InvalidHandleValue )
            {
                CloseHandle( handle_ );
            }
        }

        SystemStream( const SystemStream& other ) = delete;
        SystemStream( SystemStream&& other ) noexcept
            : handle_( other.handle_ )
        {
            other.handle_ = InvalidHandleValue;
        }
        SystemStream( DerivedType&& other ) noexcept
            : handle_( other.handle_ )
        {
            other.handle_ = InvalidHandleValue;
        }

        SystemStream& operator = ( const SystemStream& other ) = delete;
        SystemStream& operator = ( SystemStream&& other ) noexcept
        {
            std::swap( handle_, other.handle_ );
            return *this;
        }
        SystemStream& operator = ( DerivedType&& other ) noexcept
        {
            std::swap( handle_, other.handle_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return handle_ != InvalidHandleValue;
        }

        constexpr HANDLE Handle( ) const
        {
            return handle_;
        }
    public:
        constexpr bool CanRead( ) const noexcept
        {
            return true;
        }
        constexpr bool CanSeek( ) const noexcept
        {
            return true;
        }
        constexpr bool CanTimeout( ) const noexcept
        {
            return true;
        }
        constexpr bool CanWrite( ) const noexcept
        {
            return true;
        }

        long long Position( ) const 
        {
            const DerivedType& self = static_cast<const DerivedType&>( *this  );
            return self.Seek( 0, SeekOrigin::CurrentPosition );
        }
        void SetPosition( long long position ) const
        {
            const DerivedType& self = static_cast<const DerivedType&>( *this );
            self.Seek( position, SeekOrigin::StartOfFile );
        }

        long long Size( ) const 
        {
            LARGE_INTEGER result;
            result.QuadPart = 0;
            if ( GetFileSizeEx( handle_, &result ) == 0 )
            {
                ThrowLastOSError( );
            }
            return result.QuadPart;
        }
        void SetSize( long long size ) const
        {
            long long currentPosition = this->Position( );
            long long newPosition = Seek( size, SeekOrigin::StartOfFile );
            SetEndOfFile( handle_ );
            if ( currentPosition < newPosition )
            {
                Seek( currentPosition, SeekOrigin::StartOfFile );
            }
        }

        void Flush( ) const
        {
            if ( FlushFileBuffers( handle_ ) == 0 )
            {
                ThrowLastOSError( );
            }
        }

        long long Read( void* buffer, size_t numberOfBytesToRead ) const
        {
            DWORD numberOfBytesRead = 0;
            if ( ReadFile( handle_, buffer, DWORD( numberOfBytesToRead ), &numberOfBytesRead, nullptr ) == 0 )
            {
                ThrowLastOSError( );
            }
            return numberOfBytesRead;
        }
        long long Write( const void* buffer, size_t numberOfBytesToWrite ) const
        {
            DWORD numberOfBytesWritten = 0;
            if ( WriteFile( handle_, buffer, DWORD( numberOfBytesToWrite ), &numberOfBytesWritten, nullptr ) == 0 )
            {
                ThrowLastOSError( );
            }
            return numberOfBytesWritten;
        }
        long long Seek( long long offset, SeekOrigin seekOrigin ) const
        {
            LARGE_INTEGER llOffset;
            llOffset.QuadPart = offset;
            LARGE_INTEGER llNewPosition;
            llNewPosition.QuadPart = 0;
            if ( SetFilePointerEx( handle_, llOffset, &llNewPosition, DWORD( seekOrigin ) ) == 0 )
            {
                ThrowLastOSError( );
            }
            return llNewPosition.QuadPart;
        }

        DWORD GetHandleInformation() const
        {
            DWORD result = 0;
            auto rc = ::GetHandleInformation(handle_, &result);
            if (!rc)
            {
                ThrowLastOSError();
            }
            return result;
        }


        bool CanClose() const
        {
            return (GetHandleInformation() & HANDLE_FLAG_PROTECT_FROM_CLOSE) != 0;
        }
        bool Inheritable() const
        {
            return (GetHandleInformation() & HANDLE_FLAG_INHERIT) != 0;
        }

        DerivedType Clone() const
        {
            auto currentProcessHandle = GetCurrentProcess();
            HANDLE duplicatedHandle = INVALID_HANDLE_VALUE;
            auto rc = DuplicateHandle(currentProcessHandle, handle_, currentProcessHandle, &duplicatedHandle, 0, Inheritable(), DUPLICATE_SAME_ACCESS);
            if (!rc)
            {
                ThrowLastOSError();
            }
            return DerivedType(duplicatedHandle);
        }


    };


    class FileStream : public SystemStream<FileStream>
    {
        HCC_EXPORT HANDLE Create( LPCWSTR fileName, FileAccess fileAccess, FileShare fileShare, LPSECURITY_ATTRIBUTES lpSecurityAttributes, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions );
        HCC_EXPORT HANDLE Create( LPCSTR fileName, FileAccess fileAccess, FileShare fileShare, LPSECURITY_ATTRIBUTES lpSecurityAttributes, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions );
    public:
        using Base = SystemStream<FileStream>;

        explicit FileStream( HANDLE handle )
            : Base( handle )
        { }
        FileStream( const std::wstring& fileName, FileAccess fileAccess, FileShare fileShare, LPSECURITY_ATTRIBUTES securityAttributes, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions )
            : Base( Create( fileName.c_str( ), fileAccess, fileShare, securityAttributes, fileMode, attributes, fileOptions ) )
        { }
        FileStream( const std::string& fileName, FileAccess fileAccess, FileShare fileShare, LPSECURITY_ATTRIBUTES securityAttributes, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions )
            : Base( Create( fileName.c_str( ), fileAccess, fileShare, securityAttributes, fileMode, attributes, fileOptions ) )
        { }
        FileStream( LPCWSTR fileName, FileAccess fileAccess, FileShare fileShare, LPSECURITY_ATTRIBUTES securityAttributes, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions )
            : Base( Create( fileName, fileAccess, fileShare, securityAttributes, fileMode, attributes, fileOptions ) )
        { }
        FileStream( LPCSTR fileName, FileAccess fileAccess, FileShare fileShare, LPSECURITY_ATTRIBUTES securityAttributes, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions )
            : Base( Create( fileName, fileAccess, fileShare, securityAttributes, fileMode, attributes, fileOptions ) )
        { }

        FileStream( const std::wstring& fileName )
            : Base( Create( fileName.c_str( ), FileAccess::Default, FileShare::Default, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( const std::string& fileName )
            : Base( Create( fileName.c_str( ), FileAccess::Default, FileShare::Default, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCWSTR fileName )
            : Base( Create( fileName, FileAccess::Default, FileShare::Default, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCSTR fileName )
            : Base( Create( fileName, FileAccess::Default, FileShare::Default, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }

        FileStream( const std::wstring& fileName, FileAccess fileAccess )
            : Base( Create( fileName.c_str( ), fileAccess, FileShare::Default, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( const std::string& fileName, FileAccess fileAccess )
            : Base( Create( fileName.c_str( ), fileAccess, FileShare::Default, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCWSTR fileName, FileAccess fileAccess )
            : Base( Create( fileName, fileAccess, FileShare::Default, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCSTR fileName, FileAccess fileAccess )
            : Base( Create( fileName, fileAccess, FileShare::Default, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }

        FileStream( const std::wstring& fileName, FileAccess fileAccess, FileShare fileShare )
            : Base( Create( fileName.c_str( ), fileAccess, fileShare, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( const std::string& fileName, FileAccess fileAccess, FileShare fileShare )
            : Base( Create( fileName.c_str( ), fileAccess, fileShare, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCWSTR fileName, FileAccess fileAccess, FileShare fileShare )
            : Base( Create( fileName, fileAccess, fileShare, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCSTR fileName, FileAccess fileAccess, FileShare fileShare )
            : Base( Create( fileName, fileAccess, fileShare, nullptr, FileMode::Default, FileAttributes::Normal, FileOptions::Default ) )
        { }

        FileStream( const std::wstring& fileName, FileAccess fileAccess, FileMode fileMode )
            : Base( Create( fileName.c_str( ), fileAccess, FileShare::Default, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( const std::string& fileName, FileAccess fileAccess, FileMode fileMode )
            : Base( Create( fileName.c_str( ), fileAccess, FileShare::Default, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCWSTR fileName, FileAccess fileAccess, FileMode fileMode )
            : Base( Create( fileName, fileAccess, FileShare::Default, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCSTR fileName, FileAccess fileAccess, FileMode fileMode )
            : Base( Create( fileName, fileAccess, FileShare::Default, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }

        FileStream( const std::wstring& fileName, FileAccess fileAccess, FileShare fileShare, FileMode fileMode )
            : Base( Create( fileName.c_str( ), fileAccess, fileShare, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( const std::string& fileName, FileAccess fileAccess, FileShare fileShare, FileMode fileMode )
            : Base( Create( fileName.c_str( ), fileAccess, fileShare, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCWSTR fileName, FileAccess fileAccess, FileShare fileShare, FileMode fileMode )
            : Base( Create( fileName, fileAccess, fileShare, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCSTR fileName, FileAccess fileAccess, FileShare fileShare, FileMode fileMode )
            : Base( Create( fileName, fileAccess, fileShare, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }

        FileStream( const std::wstring& fileName, FileShare fileShare, FileMode fileMode )
            : Base( Create( fileName.c_str( ), FileAccess::Default, fileShare, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( const std::string& fileName, FileShare fileShare, FileMode fileMode )
            : Base( Create( fileName.c_str( ), FileAccess::Default, fileShare, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCWSTR fileName, FileShare fileShare, FileMode fileMode )
            : Base( Create( fileName, FileAccess::Default, fileShare, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCSTR fileName, FileShare fileShare, FileMode fileMode )
            : Base( Create( fileName, FileAccess::Default, fileShare, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }

        FileStream( const std::wstring& fileName, FileMode fileMode )
            : Base( Create( fileName.c_str( ), FileAccess::Default, FileShare::Default, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( const std::string& fileName, FileMode fileMode )
            : Base( Create( fileName.c_str( ), FileAccess::Default, FileShare::Default, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCWSTR fileName, FileMode fileMode )
            : Base( Create( fileName, FileAccess::Default, FileShare::Default, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }
        FileStream( LPCSTR fileName, FileMode fileMode )
            : Base( Create( fileName, FileAccess::Default, FileShare::Default, nullptr, fileMode, FileAttributes::Normal, FileOptions::Default ) )
        { }


        FileStream( const std::wstring& fileName, FileAccess fileAccess, FileShare fileShare, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions )
            : Base( Create( fileName.c_str( ), fileAccess, fileShare, nullptr, fileMode, attributes, fileOptions ) )
        { }
        FileStream( const std::string& fileName, FileAccess fileAccess, FileShare fileShare, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions )
            : Base( Create( fileName.c_str( ), fileAccess, fileShare, nullptr, fileMode, attributes, fileOptions ) )
        { }
        FileStream( LPCWSTR fileName, FileAccess fileAccess, FileShare fileShare, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions )
            : Base( Create( fileName, fileAccess, fileShare, nullptr, fileMode, attributes, fileOptions ) )
        { }
        FileStream( LPCSTR fileName, FileAccess fileAccess, FileShare fileShare, FileMode fileMode, FileAttributes attributes, FileOptions fileOptions )
            : Base( Create( fileName, fileAccess, fileShare, nullptr, fileMode, attributes, fileOptions ) )
        { }

        /// <summary>
        /// Appends all lines of the file to the target destination
        /// </summary>
        HCC_EXPORT void ReadFile( std::vector<std::string>& destination ) const;

        /// <summary>
        /// Appends all lines of the file to the target destination
        /// </summary>
        HCC_EXPORT void ReadFile( std::string& destination ) const;

        HCC_EXPORT void WriteFile( const std::vector<std::string>& contents ) const;

        HCC_EXPORT void WriteFile( const std::string& contents ) const;


    };

    static_assert( StreamReader<FileStream> );
    static_assert( StreamWriter<FileStream> );
    static_assert( StreamSeek<FileStream> );
    static_assert( StreamPosition<FileStream> );
    static_assert( StreamSize<FileStream> );
    static_assert( StreamFlush<FileStream> );
    static_assert( StreamClone<FileStream> );
    static_assert( StreamFeatureTests<FileStream> );
    static_assert( Stream<FileStream> );

    template<StreamWriter StreamT, size_t bufferSize = 4096>
    class WriteBuffer
    {
        static constexpr size_t BufferSize = bufferSize;
        const StreamT& stream_;
        std::array<Byte, BufferSize> data_;
        size_t position_ = 0;
    public:
        WriteBuffer( const StreamT& stream )
            : stream_( stream )
        { }

        ~WriteBuffer( )
        {
            Flush( );
        }

        void Flush( )
        {
            if ( position_ )
            {
                stream_.Write( data_.data( ), position_ );
                position_ = 0;
            }
        }

        size_t Remaining( )
        {
            return BufferSize - position_;
        }

        long long Write( const void* buffer, size_t numberOfBytesToWrite ) 
        {
            auto remaining = Remaining( );
            if ( numberOfBytesToWrite <= remaining )
            {
                memcpy( data_.data( ) + position_, buffer, numberOfBytesToWrite );
                position_ += numberOfBytesToWrite;
            }
            else
            {
                auto bytesRemainingToWrite = numberOfBytesToWrite;
                const Byte* ptr = reinterpret_cast<const Byte*>( buffer );
                memcpy( data_.data( ) + position_, ptr, remaining );
                ptr += remaining;
                bytesRemainingToWrite -= remaining;
                Flush( );
                if ( bytesRemainingToWrite < BufferSize )
                {
                    memcpy( data_.data( ), ptr, bytesRemainingToWrite );
                    position_ = bytesRemainingToWrite;
                }
                else
                {
                    stream_.Write( ptr, bytesRemainingToWrite );
                }
            }
            return static_cast<long long>( numberOfBytesToWrite );
        }

    };







}


#endif