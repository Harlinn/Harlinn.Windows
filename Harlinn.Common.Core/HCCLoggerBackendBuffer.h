#pragma once
#ifndef __HCCLOGGERBACKENDBUFFER_H__
#define __HCCLOGGERBACKENDBUFFER_H__

#include <HCCDef.h>
#include <HCCMemory.h>
#include <HCCDateTime.h>
#include <HCCGuid.h>

namespace Harlinn::Common::Core::Logging
{
    class LogSite;
    class BackendStream;
    class Backend;
    class BackendBufferManager;
#pragma pack(push,1)
    struct BackendStreamRecordHeader
    {
        /// <summary>
        /// size of record, excluding the size of Size itself.
        /// </summary>
        UInt32 Size;
        union
        {
            const LogSite* Site;
            UInt64 SiteId;
        };
        /// <summary>
        /// value returned by __rdtsc( )
        /// </summary>
        UInt64 Time;
    };


    class BackendBufferKey
    {
        Guid processId_;
        DateTime timeStamp_;
        UInt32 threadId_ = 0;
        UInt64 sequenceNumber_ = 0;
    public:
        BackendBufferKey()
        { }

        BackendBufferKey( const Guid& processId, const DateTime& timeStamp, UInt32 threadId, UInt64 sequenceNumber )
            : processId_( processId ), timeStamp_( timeStamp ), threadId_( threadId ), sequenceNumber_( sequenceNumber )
        {
        }

        void Assign( const Guid& processId, const DateTime& timeStamp, UInt32 threadId, UInt64 sequenceNumber )
        {
            processId_ = processId;
            timeStamp_ = timeStamp;
            threadId_ = threadId;
            sequenceNumber_ = sequenceNumber;
        }

        auto operator<=>( const BackendBufferKey& ) const = default;

        template<typename ReaderT>
        void Read( ReaderT& reader )
        {
            reader.Read( processId_ );
            reader.Read( timeStamp_ );
            reader.Read( threadId_ );
            reader.Read( sequenceNumber_ );
        }

        template<typename WriterT>
        void Write( WriterT& writer )
        {
            writer.Write( processId_ );
            writer.Write( timeStamp_ );
            writer.Write( threadId_ );
            writer.Write( sequenceNumber_ );
        }

        constexpr const Guid& ProcessId( ) const noexcept
        {
            return processId_;
        }
        constexpr void SetProcessId( const Guid& processId ) noexcept
        {
            processId_ = processId;
        }
        constexpr const DateTime& TimeStamp( ) const noexcept
        {
            return timeStamp_;
        }
        constexpr void SetTimeStamp( const DateTime& timeStamp ) noexcept
        {
            timeStamp_ = timeStamp;
        }
        constexpr UInt32 ThreadId( ) const noexcept
        {
            return threadId_;
        }
        constexpr void SetThreadId(UInt32 threadId ) noexcept
        {
            threadId_ = threadId;
        }
        constexpr UInt64 SequenceNumber( ) const noexcept
        {
            return sequenceNumber_;
        }
        constexpr void SetSequenceNumber( UInt64 sequenceNumber ) noexcept
        {
            sequenceNumber_ = sequenceNumber;
        }


    };
#pragma pack(pop)

    class BackendBuffer : public OVERLAPPED
    {
        friend class BackendStream;
    public:
        static constexpr size_t MaximumSize = 64 * 1024;
        using RecordHeader = BackendStreamRecordHeader;
        using PrimaryKeyType = BackendBufferKey;
    private:
        Int64 referenceCount_ = 1;
        BackendBufferManager* manager_;
        bool recordHeadersHasPointers_ = true;

        PrimaryKeyType primaryKey_;

        size_t size_ = 0;
        UInt64 recordCount_;
        UInt64 timeStampCounter_;
        
        std::array<Byte, MaximumSize> data_;
    public:
        BackendBuffer( BackendBufferManager* manager, UInt32 threadId, UInt64 sequenceNumber )
            : OVERLAPPED{}, manager_( manager ), primaryKey_(Guid( ), DateTime::UtcNow( ), threadId, sequenceNumber ), recordCount_(0), timeStampCounter_( __rdtsc( ) )
        { }

        BackendBuffer( BackendBufferManager* manager, const Guid& processId, UInt32 threadId, UInt64 sequenceNumber )
            : OVERLAPPED{}, manager_( manager ), primaryKey_( processId, DateTime::UtcNow( ), threadId, sequenceNumber ), recordCount_( 0 ), timeStampCounter_( __rdtsc( ) )
        { }


        Int64 AddRef( ) noexcept
        {
            return InterlockedIncrement64( &referenceCount_ );
        }
        
        Int64 Release( ) noexcept;

        size_t StorageSize( ) const noexcept
        {
            return ( ( (const Byte*)&data_ ) - ( (const Byte*)&size_ ) ) + size_;
        }

        const Byte* Storage( ) const noexcept
        {
            return (const Byte*)&size_;
        }
        Byte* Storage( ) noexcept
        {
            return (Byte*)&size_;
        }


        constexpr size_t size( ) const noexcept
        {
            return size_;
        }

        constexpr size_t FreeCapacity( ) const noexcept
        {
            return MaximumSize - size_;
        }

        constexpr bool HasCapacity( size_t requestedCapacity ) const noexcept
        {
            return requestedCapacity <= FreeCapacity( );
        }


        constexpr Byte* data( ) noexcept
        {
            return data_.data( );
        }
        constexpr const Byte* data( ) const noexcept
        {
            return data_.data( );
        }

        RecordHeader* First( ) noexcept
        {
            return (RecordHeader*)data_.data( );
        }
        const RecordHeader* First( ) const noexcept
        {
            return (RecordHeader*)data_.data( );
        }

        RecordHeader* Next( RecordHeader* current ) noexcept
        {
            size_t recordSize = current->Size;
            return ( RecordHeader* )(((Byte*)current ) + recordSize + sizeof( RecordHeader::Size ) );
        }
        const RecordHeader* Next( const RecordHeader* current ) const noexcept
        {
            size_t recordSize = current->Size;
            return (const RecordHeader*)( ( (Byte*)current ) + recordSize + sizeof( RecordHeader::Size ) );
        }

        constexpr bool RecordHeadersHasPointers( ) const noexcept
        {
            return recordHeadersHasPointers_;
        }
        constexpr void SetRecordHeadersHasPointers( bool recordHeadersHasPointers ) noexcept
        {
            recordHeadersHasPointers_ = recordHeadersHasPointers;
        }

        constexpr const PrimaryKeyType& PrimaryKey( ) const noexcept
        {
            return primaryKey_;
        }
        constexpr void SetPrimaryKey( const PrimaryKeyType& primaryKey ) noexcept
        {
            primaryKey_ = primaryKey;
        }

        constexpr const Guid& ProcessId( ) const noexcept
        {
            return primaryKey_.ProcessId();
        }
        constexpr void SetProcessId( const Guid& processId ) noexcept
        {
            primaryKey_.SetProcessId( processId );
        }
        constexpr const DateTime& TimeStamp( ) const noexcept
        {
            return primaryKey_.TimeStamp( );
        }
        constexpr void SetTimeStamp( const DateTime& timeStamp ) noexcept
        {
            primaryKey_.SetTimeStamp( timeStamp );
        }
        constexpr UInt32 ThreadId( ) const noexcept
        {
            return primaryKey_.ThreadId();
        }
        constexpr void SetThreadId( UInt32 threadId ) noexcept
        {
            primaryKey_.SetThreadId( threadId );
        }
        constexpr UInt64 SequenceNumber( ) const noexcept
        {
            return primaryKey_.SequenceNumber();
        }
        constexpr void SetSequenceNumber( UInt64 sequenceNumber ) noexcept
        {
            primaryKey_.SetSequenceNumber( sequenceNumber );
        }


        
        constexpr UInt64 RecordCount( ) const noexcept
        {
            return recordCount_;
        }

        constexpr void SetRecordCount( UInt64 recordCount ) noexcept
        {
            recordCount_ = recordCount;
        }

        Int64 Write( const void* buffer, size_t bufferSize )
        {
            memcpy( data_.data( ) + size_, buffer, bufferSize );
            size_ += bufferSize;
            return bufferSize;
        }

        void WriteRecordSize( size_t recordStartOffset, UInt32 recordSize )
        {
            *( (UInt32*)( data_.data( ) + recordStartOffset ) ) = recordSize;
        }
        
    private:
        void TakeStartOfRecordFrom( BackendBuffer* other, size_t startOfRecordOffset )
        {
            Byte* startOfRecord = other->data_.data( ) + startOfRecordOffset;
            size_t sizeOfRecordData = other->size_ - startOfRecordOffset;
            Write( startOfRecord, sizeOfRecordData );
            other->size_ = startOfRecordOffset;
        }

    };

    class BackendBufferManager
    {
    public:
        static constexpr size_t MaximumFreeBuffers = 32 * 1024;
    private:
        static constexpr size_t BlockSize = sizeof( BackendBuffer );
        using MemoryManager = FixedSizeMemoryManager<BlockSize, MaximumFreeBuffers>;
        MemoryManager memoryManager_;
        Backend* backend_;
    public:
        BackendBufferManager( Backend* backend )
            : backend_( backend )
        { }

        BackendBuffer* Allocate( UInt32 threadId, UInt64 sequenceNumber )
        {
            auto* mem = memoryManager_.Malloc( );
            return new ( mem ) BackendBuffer( this, threadId, sequenceNumber );
        }
        void Free( BackendBuffer* buffer )
        {
            memoryManager_.Free( buffer );
        }

        Backend* Backend( ) const noexcept
        {
            return backend_;
        }

    };


    inline Int64 BackendBuffer::Release( ) noexcept
    {
        auto result = InterlockedDecrement64( &referenceCount_ );
        if ( result == 0 )
        {
            manager_->Free( this );
        }
        return result;
    }

}

#endif
