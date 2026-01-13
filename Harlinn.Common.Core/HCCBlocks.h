#pragma once
#ifndef __HCCBLOCKS_H__
#define __HCCBLOCKS_H__
/*
   Copyright 2024-2026 Espen Harlinn

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

#include <HCCDef.h>
#include <HCCException.h>
#include <HCCLogging.h>

#include <HCCIO.h>

namespace Harlinn::Common::Core::IO::Blocks
{
    constexpr size_t BlockSize = 32 * 1024;
    constexpr size_t CacheSize = 10000;

    class Block
    {
    public:
        static constexpr size_t DataSize = BlockSize - 2 * sizeof( Block* );
    private:
        Block* next_;
        Block* previous_;
        Byte data_[DataSize];
    public:

        Block( const Block& other ) = delete;
        Block( Block&& other ) = delete;
        Block& operator = ( const Block& other ) = delete;
        Block& operator = ( Block&& other ) = delete;

        HCC_EXPORT static Block* Allocate( );
        HCC_EXPORT static Block* Allocate( Block* previous );
        HCC_EXPORT static Block* Allocate( Block* next, Block* previous );
        HCC_EXPORT static void Free( Block* block );

        constexpr Block* Next( ) const noexcept
        {
            return next_;
        }

        void SetNext( Block* next ) noexcept
        {
            next_ = next;
        }


        constexpr Block* Previous( ) const noexcept
        {
            return previous_;
        }

        void SetPrevious( Block* previous ) noexcept
        {
            previous_ = previous;
        }

        void Append( Block* newNext ) noexcept
        {
            newNext->previous_ = this;
            next_ = newNext;
        }

        void Prepend( Block* newPrevious ) noexcept
        {
            newPrevious->next_ = this;
            previous_ = newPrevious;
        }

        constexpr const Byte* data( ) const noexcept
        {
            return data_;
        }

        Byte* data( ) noexcept
        {
            return data_;
        }

    };



    template<typename BlockManagerType, typename BlockType >
    class BlockIterator
    {
    public:
        using value_type = BlockType;
        using difference_type = std::ptrdiff_t;
        using pointer = BlockType*;
        using reference = BlockType&;
        using iterator_category = std::bidirectional_iterator_tag;
    private:
        BlockManagerType& blockManager_;
        pointer current_;
    public:
        constexpr BlockIterator( BlockManagerType& blockManager ) noexcept
            : blockManager_( blockManager ), current_( nullptr )
        {
        }

        constexpr BlockIterator( BlockManagerType& blockManager, pointer current ) noexcept
            : blockManager_( blockManager ), current_( current )
        {
        }

        constexpr bool operator == ( const BlockIterator& other ) const noexcept
        {
            return current_ == other.current_;
        }

        constexpr bool operator != ( const BlockIterator& other ) const noexcept
        {
            return current_ != other.current_;
        }

        constexpr reference operator*( ) const noexcept
        {
            return *current_;
        }

        BlockIterator& operator++( ) noexcept
        {
            if ( current_ )
            {
                current_ = (pointer)current_->Next( );
            }
            return *this;
        }

        BlockIterator operator++( int ) noexcept
        {
            BlockIterator result( blockManager_, current_ );
            if ( current_ )
            {
                current_ = (pointer)current_->Next( );
            }
            return result;
        }

        BlockIterator& operator--( ) noexcept
        {
            if ( current_ )
            {
                current_ = (pointer)current_->Previous( );
            }
            else
            {
                current_ = (pointer)blockManager_.Tail( );
            }
            return *this;
        }

        BlockIterator operator--( int ) noexcept
        {
            BlockIterator result( blockManager_, current_ );
            if ( current_ )
            {
                current_ = (pointer)current_->Previous( );
            }
            else
            {
                current_ = (pointer)blockManager_.Tail( );
            }
            return result;
        }


    };



    class BlockManager
    {
        Block* head_;
        Block* tail_;
        size_t size_;
    public:
        using iterator = BlockIterator<BlockManager, Block>;
        using const_iterator = BlockIterator<const BlockManager, const Block>;


        constexpr BlockManager( ) noexcept
            : head_( nullptr ), tail_( nullptr ), size_( 0 )
        {
        }

        BlockManager( const BlockManager& other ) = delete;
        BlockManager& operator = ( const BlockManager& other ) = delete;

        constexpr BlockManager( BlockManager&& other ) noexcept
            : head_( other.head_ ), tail_( other.tail_ ), size_( other.size_ )
        {
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }


        BlockManager& operator = ( BlockManager&& other ) noexcept
        {
            if ( this != &other )
            {
                Clear( );
                head_ = other.head_;
                tail_ = other.tail_;
                size_ = other.size_;

                other.head_ = nullptr;
                other.tail_ = nullptr;
                other.size_ = 0;
            }
        }

        ~BlockManager( )
        {
            Clear( );
        }

        void Clear( )
        {
            auto* ptr = head_;
            while ( ptr )
            {
                auto* tmp = ptr;
                ptr = ptr->Next( );
                Block::Free( tmp );
            }
            head_ = nullptr;
            tail_ = nullptr;
            size_ = 0;
        }


        void Append( Block* block )
        {
            if ( !head_ )
            {
                head_ = block;
                tail_ = block;
            }
            else
            {
                tail_->Append( block );
                tail_ = block;
            }
            size_++;
        }

        constexpr Block* Head( ) const noexcept
        {
            return head_;
        }

        constexpr Block* Tail( ) const noexcept
        {
            return tail_;
        }

        Block* Append( )
        {
            auto* result = Block::Allocate( );
            Append( result );
            return result;
        }


        constexpr size_t size( ) const noexcept
        {
            return size_;
        }

        constexpr bool empty( ) const noexcept
        {
            return size_ == 0;
        }


        constexpr iterator begin( ) noexcept
        {
            iterator result( *this, head_ );
            return result;
        }

        constexpr iterator end( ) noexcept
        {
            iterator result( *this );
            return result;
        }

        constexpr const_iterator cbegin( ) const noexcept
        {
            const_iterator result( *this, head_ );
            return result;
        }

        constexpr const_iterator cend( ) const noexcept
        {
            const_iterator result( *this );
            return result;
        }

        constexpr const_iterator begin( ) const noexcept
        {
            return cbegin( );
        }
        constexpr const_iterator end( ) const noexcept
        {
            return cend();
        }
    };




    class Stream 
    {
    public:
        using SeekOrigin = Harlinn::Common::Core::IO::SeekOrigin;

        static constexpr size_t BlockDataSize = Block::DataSize;
    private:
        BlockManager blockManager_;
        // Points to the current block
        Block* currentBlock_;
        // 0 based offset of the current block in the block list
        size_t currentNumber_;
        // offset in current block for the current position
        size_t currentOffset_;
        // The size of the last block, all other blocks are full, 
        // containing 'BlockDataSize' bytes of data
        size_t lastBlockSize_;
    public:
        constexpr Stream( ) noexcept
            : currentBlock_( nullptr ), currentNumber_(0), currentOffset_( 0 ), lastBlockSize_( 0 )
        {
        }

        void Clear( )
        {
            blockManager_.Clear( );
            currentBlock_ = nullptr; 
            currentNumber_ = 0; 
            currentOffset_ = 0; 
            lastBlockSize_ = 0;
        }


        Stream( const Stream& other ) = delete;
        Stream& operator = ( const Stream& other ) = delete;

        Stream( Stream&& other ) = delete;
        Stream& operator = ( Stream&& other ) = delete;

        BlockManager& Blocks( )
        {
            return blockManager_;
        }
        size_t LastBlockSize( ) const
        {
            return lastBlockSize_;
        }

    private:
        template<typename T>
        T ConvertTo( ) const
        {
            T result;
            auto count = size( );
            if ( count )
            {
                auto elementCount = count / sizeof( typename T::value_type );
                result.resize( elementCount );
                auto destPtr = reinterpret_cast<Byte*>(result.data( ));
                size_t copied = 0;
                auto head = blockManager_.Head( );
                auto tail = blockManager_.Tail( );

                while ( head != tail )
                {
                    memcpy( destPtr + copied, head->data( ), Block::DataSize );
                    copied += Block::DataSize;
                    head = head->Next( );
                }
                if ( lastBlockSize_ )
                {
                    memcpy( destPtr + copied, head->data( ), lastBlockSize_ );
#ifdef _DEBUG
                    copied += lastBlockSize_;
#endif
                }
#ifdef _DEBUG
                assert( copied == count );
#endif
            }

            return result;
        }
    public:
        std::vector<Byte> ToBytes( ) const
        {
            return ConvertTo<std::vector<Byte>>( );
        }

        AnsiString ToAnsiString( ) const
        {
            return ConvertTo<AnsiString>( );
        }

        WideString ToWideString( ) const
        {
            return ConvertTo<WideString>( );
        }

        template<StringLike T>
        T ToString( ) const
        {
            return ConvertTo<T>( );
        }



        constexpr size_t position( ) const noexcept
        {
            return ( currentNumber_ * BlockDataSize ) + currentOffset_;
        }

        constexpr long long Position( ) const noexcept
        {
            return static_cast<long long>( position( ) );
        }
        void SetPosition( long long position )
        {
            if ( position <= 0 )
            {
                MoveBegin( );
            }
            auto newPosition = static_cast<size_t>( position );
            auto siz = size( );
            if ( newPosition < siz )
            {
                const auto segment = newPosition / BlockDataSize;
                const auto offset = newPosition % BlockDataSize;
                const auto numberOfBlocks = blockManager_.size( );

                if ( segment == currentNumber_ )
                {
                    currentOffset_ = offset;
                }
                else if ( segment > currentNumber_ )
                {
                    while ( currentNumber_ < segment )
                    {
                        MoveNext( );
                    }
                    currentOffset_ = offset;
                }
                else
                {
                    MoveBegin( );
                    while ( currentNumber_ < segment )
                    {
                        MoveNext( );
                    }
                    currentOffset_ = offset;
                }
            }
            else
            {
                if ( newPosition > siz )
                {
                    SetSize( position );
                }
                MoveEnd( );
            }


        }


        constexpr size_t size( ) const noexcept
        {
            auto numberOfBlocks = blockManager_.size( );
            if ( numberOfBlocks )
            {
                return static_cast<long long>( ( ( numberOfBlocks - 1 ) * BlockDataSize ) + lastBlockSize_ );
            }
            else
            {
                return 0;
            }
        }
        constexpr long long Size( ) const noexcept
        {
            return static_cast<long long>( size( ) );
        }
        void SetSize( long long size ) 
        {
            if ( size < 0 )
            {
                size = 0;
            }
            auto currentSize = Size( );
            if ( currentSize < size )
            {
                auto segments = static_cast<size_t>( size ) / BlockDataSize;
                auto offset = static_cast<size_t>( size ) % BlockDataSize;
                auto numberOfBlocks = blockManager_.size( );
                for ( size_t i = numberOfBlocks; i <= segments; ++i )
                {
                    blockManager_.Append( );
                }
                lastBlockSize_ = offset;
            }
            else if ( currentSize > size )
            {
                HCC_THROW( NotImplementedException, L"Shrinking not implemented" );
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

        constexpr void Flush( ) const noexcept
        {
        }
        long long Read( void* buffer, size_t numberOfBytesToRead )
        {
            if ( currentBlock_ )
            {
                auto tail = blockManager_.Tail( );
                if ( currentBlock_ != tail )
                {
                    auto remaining = BlockDataSize - currentOffset_;
                    if ( numberOfBytesToRead <= remaining )
                    {
                        auto* source = currentBlock_->data( ) + currentOffset_;
                        memcpy( buffer, source, numberOfBytesToRead );
                        currentOffset_ += numberOfBytesToRead;
                        return static_cast<long long>( numberOfBytesToRead );
                    }
                    else
                    {
                        Byte* bytes = (Byte*)buffer;
                        if ( remaining )
                        {
                            auto* source = currentBlock_->data( ) + currentOffset_;
                            memcpy( bytes, source, remaining );
                            bytes += remaining;
                            numberOfBytesToRead -= remaining;
                        }
                        while ( currentBlock_ != tail && numberOfBytesToRead )
                        {
                            MoveNext( );

                            size_t numberOfBytesToCopy = std::min( numberOfBytesToRead, BlockDataSize );
                            auto* source = currentBlock_->data( );
                            memcpy( bytes, source, numberOfBytesToCopy );
                            currentOffset_ += numberOfBytesToCopy;
                            bytes += numberOfBytesToCopy;
                            numberOfBytesToRead -= numberOfBytesToCopy;
                        }
                        return static_cast<long long>(bytes - ((Byte*)buffer));
                    }
                }
                else
                {
                    auto remaining = lastBlockSize_ - currentOffset_;
                    auto count = std::min( remaining, numberOfBytesToRead );
                    auto* source = currentBlock_->data( ) + currentOffset_;
                    memcpy( buffer, source, count );
                    currentOffset_ += count;
                    return static_cast<long long>(count);
                }
            }
            else
            {
                return 0;
            }
        }


        long long Write( const void* buffer, size_t numberOfBytesToWrite )
        {
            if ( numberOfBytesToWrite )
            {
                auto tail = blockManager_.Tail( );
                if ( tail && currentBlock_ == tail )
                {
                    if ( ( currentOffset_ + numberOfBytesToWrite ) <= BlockDataSize )
                    {
                        auto* dest = currentBlock_->data( ) + currentOffset_;
                        memcpy( dest, buffer, numberOfBytesToWrite );
                        currentOffset_ += numberOfBytesToWrite;
                        lastBlockSize_ = std::max( lastBlockSize_, currentOffset_);
                        return numberOfBytesToWrite;
                    }
                    else 
                    {
                        auto remaining = BlockDataSize - currentOffset_;
                        const Byte* bytes = (const Byte*)buffer;
                        auto* dest = currentBlock_->data( ) + currentOffset_;
                        memcpy( dest, buffer, remaining );
                        currentOffset_ = BlockDataSize;
                        lastBlockSize_ = BlockDataSize;

                        numberOfBytesToWrite -= remaining;
                        bytes += remaining;

                        bytes += AppendBlocks( bytes, numberOfBytesToWrite );

                        return bytes - ( (Byte*)buffer );
                    }
                }
                else if( currentBlock_ )
                {
                    auto pos = position( );
                    auto sz = size( );
                    auto overwriteMax = sz - pos;
                    if ( numberOfBytesToWrite <= overwriteMax )
                    {
                        Overwrite( ( Byte* )buffer, numberOfBytesToWrite );
                    }
                    else
                    {
                        Overwrite( (Byte*)buffer, overwriteMax );
                        Write( ((Byte*)buffer) + overwriteMax, numberOfBytesToWrite - overwriteMax );
                    }
                    return numberOfBytesToWrite;
                }
                
                else
                {
                    return AppendBlocks( (Byte*)buffer, numberOfBytesToWrite );
                }
            }
            else
            {
                return 0;
            }
        }

        long long Seek( long long offset, SeekOrigin seekOrigin )
        {
            long long newPosition = 0;
            size_t currentPosition = position( );
            switch ( seekOrigin )
            {
                case SeekOrigin::StartOfFile:
                    if ( offset > 0 )
                    {
                        newPosition = offset;
                    }
                    break;
                case SeekOrigin::CurrentPosition:
                    newPosition = currentPosition + offset;
                    break;
                case SeekOrigin::EndOfFile:
                    newPosition = size( ) + offset;
                    break;
            }
            if ( newPosition < 0 )
            {
                newPosition = 0;
            }
            SetPosition( newPosition );
            return newPosition;
        }

    private:
        void Overwrite( const Byte* buffer, size_t numberOfBytesToWrite )
        {
            if ( currentBlock_ )
            {
                auto currentBlockRemaining = CurrentBlockRemaining( );
                if ( numberOfBytesToWrite <= currentBlockRemaining )
                {
                    auto* dest = currentBlock_->data( ) + currentOffset_;
                    memcpy( dest, buffer, numberOfBytesToWrite );
                    currentOffset_ += numberOfBytesToWrite;
                }
                else
                {
                    const Byte* bytesBegin = (Byte*)buffer;
                    const Byte* bytes = bytesBegin;

                    if ( currentBlockRemaining )
                    {
                        auto* dest = currentBlock_->data( ) + currentOffset_;
                        memcpy( dest, bytes, currentBlockRemaining );
                        currentOffset_ += currentBlockRemaining;
                        bytes += currentBlockRemaining;
                        numberOfBytesToWrite -= currentBlockRemaining;
                    }
                    auto tail = blockManager_.Tail( );
                    while ( currentBlock_ != tail && numberOfBytesToWrite )
                    {
                        MoveNext( );

                        size_t numberOfBytesToCopy = std::min( numberOfBytesToWrite, BlockDataSize );
                        auto* dest = currentBlock_->data( );
                        memcpy( dest, bytes, numberOfBytesToCopy );
                        currentOffset_ += numberOfBytesToCopy;
                        bytes += numberOfBytesToCopy;
                        numberOfBytesToWrite -= numberOfBytesToCopy;
                    }
                }
            }
        }
        size_t AppendBlocks( const Byte* buffer, size_t numberOfBytesToWrite )
        {
            const Byte* bytes = buffer;

            size_t fullBlocks = numberOfBytesToWrite / BlockDataSize;
            size_t remaining = numberOfBytesToWrite % BlockDataSize;

            if ( fullBlocks )
            {
                Block* block = nullptr;
                while ( fullBlocks )
                {
                    block = blockManager_.Append( );
                    memcpy( block->data( ), bytes, BlockDataSize );
                    fullBlocks--;
                    bytes += BlockDataSize;
                }
                currentBlock_ = block;
            }
            if ( remaining )
            {
                Block* block = blockManager_.Append( );
                memcpy( block->data( ), bytes, remaining );
                currentBlock_ = block;
                currentOffset_ = remaining;
                lastBlockSize_ = remaining;
                bytes += remaining;
            }
            else
            {
                currentOffset_ = BlockDataSize;
                lastBlockSize_ = BlockDataSize;
            }
            currentNumber_ = blockManager_.size( ) - 1;
            return bytes - buffer;
        }
        long long Append( const void* buffer, size_t numberOfBytesToWrite )
        {
            return 0;
        }


        size_t CurrentBlockRemaining( ) const
        {
            size_t blockSize = currentBlock_ == blockManager_.Tail( ) ? lastBlockSize_ : BlockDataSize;
#ifdef _DEBUG
            if ( currentOffset_ > blockSize )
            {
                HCC_THROW( Core::InvalidOperationException, "currentOffset_ > blockSize" );
            }
#endif
            return blockSize - currentOffset_;
        }


        bool MoveNext( )
        {
            if ( currentBlock_ )
            {
                auto next = currentBlock_->Next( );
                if ( next )
                {
                    currentBlock_ = next;
                    currentOffset_ = 0;
                    currentNumber_++;
                    return true;
                }
            }
            return false;
        }

        bool MovePrevious( )
        {
            if ( currentBlock_ )
            {
                auto previous = currentBlock_->Previous( );
                if ( previous )
                {
                    currentBlock_ = previous;
                    currentOffset_ = BlockDataSize;
                    currentNumber_--;
                    return true;
                }
            }
            return false;
        }

        void MoveBegin( )
        {
            currentBlock_ = blockManager_.Head( );
            currentOffset_ = 0;
            currentNumber_ = 0;
        }

        void MoveEnd( )
        {
            currentBlock_ = blockManager_.Head( );
            if ( blockManager_.size( ) )
            {
                currentOffset_ = lastBlockSize_;
                currentNumber_ = blockManager_.size( ) - 1;
            }
            else
            {
                currentOffset_ = 0;
                currentNumber_ = 0;
            }
        }



    public:


    };

    static_assert( Harlinn::Common::Core::IO::StreamReader<Stream> );
    static_assert( Harlinn::Common::Core::IO::StreamWriter<Stream> );
    static_assert( Harlinn::Common::Core::IO::StreamSeek<Stream> );
    static_assert( Harlinn::Common::Core::IO::StreamPosition<Stream> );
    static_assert( Harlinn::Common::Core::IO::StreamSize<Stream> );
    static_assert( Harlinn::Common::Core::IO::StreamFlush<Stream> );
    static_assert( Harlinn::Common::Core::IO::StreamFeatureTests<Stream> );
    static_assert( Harlinn::Common::Core::IO::Stream<Stream> );


}

#endif