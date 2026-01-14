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
        /// <summary>
        /// Size of the usable data buffer in a block.
        /// </summary>
        /// <remarks>
        /// Calculated as the global BlockSize minus the space required for the
        /// two pointer fields used for linking blocks. This value describes
        /// how many bytes of payload each block can hold.
        /// </remarks>
        static constexpr size_t DataSize = BlockSize - 2 * sizeof( Block* );
    private:
        Block* next_;
        Block* previous_;
        Byte data_[ DataSize ];
    public:

        Block( const Block& other ) = delete;
        Block( Block&& other ) = delete;
        Block& operator = ( const Block& other ) = delete;
        Block& operator = ( Block&& other ) = delete;

        /// <summary>
        /// Allocate a new block and return a pointer to it.
        /// </summary>
        /// <returns>Pointer to the allocated block. Ownership is transferred to the caller.</returns>
        /// <remarks>
        /// The allocated block has its linkage pointers uninitialized.
        /// Caller is responsible for linking the block into a BlockManager and
        /// eventually calling <see cref="Free"/> to release it.
        /// </remarks>
        /// <exception cref="SystemException">When allocation or OS error occurs.</exception>
        HCC_EXPORT static Block* Allocate( );
        /// <summary>
        /// Allocate a new block and set its previous pointer.
        /// </summary>
        /// <param name="previous">Pointer to the previous block; may be nullptr.</param>
        /// <returns>Pointer to the allocated block. Ownership is transferred to the caller.</returns>
        /// <remarks>
        /// The returned block's previous pointer will be set to <paramref name="previous"/>.
        /// This helper is useful when appending a block to an existing list.
        /// </remarks>
        /// <exception cref="SystemException">When allocation or OS error occurs.</exception>
        HCC_EXPORT static Block* Allocate( Block* previous );
        /// <summary>
        /// Allocate a new block and set both its next and previous pointers.
        /// </summary>
        /// <param name="next">Pointer to the next block; may be nullptr.</param>
        /// <param name="previous">Pointer to the previous block; may be nullptr.</param>
        /// <returns>Pointer to the allocated block. Ownership is transferred to the caller.</returns>
        /// <remarks>
        /// The returned block's linkage pointers will be initialized as provided.
        /// Use this overload when inserting a block between existing blocks.
        /// </remarks>
        /// <exception cref="SystemException">When allocation or OS error occurs.</exception>
        HCC_EXPORT static Block* Allocate( Block* next, Block* previous );
        /// <summary>
        /// Free a previously allocated block.
        /// </summary>
        /// <param name="block">Pointer to the block to free. May be nullptr.</param>
        /// <remarks>
        /// This function releases resources associated with <paramref name="block"/>.
        /// After calling <see cref="Free"/>, the pointer must not be accessed.
        /// </remarks>
        /// <exception cref="SystemException">When deallocation or OS error occurs.</exception>
        HCC_EXPORT static void Free( Block* block );

        /// <summary>
        /// Get the next block in the linked list.
        /// </summary>
        /// <returns>Pointer to the next block, or nullptr if this is the tail.</returns>
        constexpr Block* Next( ) const noexcept
        {
            return next_;
        }

        /// <summary>
        /// Set the next block pointer.
        /// </summary>
        /// <param name="next">Pointer to the block that should follow this block.</param>
        /// <remarks>
        /// This does not update the newly set next block's previous pointer.
        /// Caller must maintain list invariants when linking blocks.
        /// </remarks>
        void SetNext( Block* next ) noexcept
        {
            next_ = next;
        }


        /// <summary>
        /// Get the previous block in the linked list.
        /// </summary>
        /// <returns>Pointer to the previous block, or nullptr if this is the head.</returns>
        constexpr Block* Previous( ) const noexcept
        {
            return previous_;
        }

        /// <summary>
        /// Set the previous block pointer.
        /// </summary>
        /// <param name="previous">Pointer to the block that should precede this block.</param>
        /// <remarks>
        /// This does not update the newly set previous block's next pointer.
        /// Caller must maintain list invariants when linking blocks.
        /// </remarks>
        void SetPrevious( Block* previous ) noexcept
        {
            previous_ = previous;
        }

        /// <summary>
        /// Append a block after this block.
        /// </summary>
        /// <param name="newNext">Block to append as the next block. Must not be nullptr.</param>
        /// <remarks>
        /// The appended block's previous pointer will be set to this block and this
        /// block's next pointer will be set to <paramref name="newNext"/>.
        /// Caller must ensure that <paramref name="newNext"/> is not already part of another list
        /// or that its previous linkage is intentionally overwritten.
        /// </remarks>
        void Append( Block* newNext ) noexcept
        {
            newNext->previous_ = this;
            next_ = newNext;
        }

        /// <summary>
        /// Prepend a block before this block.
        /// </summary>
        /// <param name="newPrevious">Block to prepend as the previous block. Must not be nullptr.</param>
        /// <remarks>
        /// The prepended block's next pointer will be set to this block and this
        /// block's previous pointer will be set to <paramref name="newPrevious"/>.
        /// Caller must ensure that <paramref name="newPrevious"/> is not already part of another list
        /// or that its next linkage is intentionally overwritten.
        /// </remarks>
        void Prepend( Block* newPrevious ) noexcept
        {
            newPrevious->next_ = this;
            previous_ = newPrevious;
        }

        /// <summary>
        /// Get a const pointer to the block's data buffer.
        /// </summary>
        /// <returns>Pointer to the block data (read-only).</returns>
        constexpr const Byte* data( ) const noexcept
        {
            return data_;
        }

        /// <summary>
        /// Get a pointer to the block's data buffer.
        /// </summary>
        /// <returns>Pointer to the block data (read/write).</returns>
        Byte* data( ) noexcept
        {
            return data_;
        }

    };



    /// <summary>
    /// Bidirectional iterator for traversing blocks managed by a block manager.
    /// </summary>
    /// <typeparam name="BlockManagerType">Type of the block manager that owns the blocks. Must provide `Head()` and `Tail()` member functions.</typeparam>
    /// <typeparam name="BlockType">Type of the block elements iterated over (typically `Block` or `const Block`).</typeparam>
    /// <remarks>
    /// The iterator models a bidirectional iterator over the linked list of blocks.
    /// Increment and decrement operations advance the iterator by following the block
    /// linkage pointers. Dereferencing the iterator yields a reference to the underlying
    /// block object. Iterators become invalid if the underlying block list is modified
    /// (blocks inserted or removed) in a way that affects the current position.
    /// Not thread-safe: concurrent modifications to the block manager must be synchronized
    /// by the caller.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// // Iterate from head to tail:
    /// for ( auto it = blockManager.begin(); it != blockManager.end(); ++it )
    /// {
    ///     Block& b = *it;
    ///     // use b
    /// }
    /// </code>
    /// </example>
    template<typename BlockManagerType, typename BlockType >
    class BlockIterator
    {
    public:
        /// <summary>
        /// Element type yielded by the iterator.
        /// </summary>
        using value_type = BlockType;
        /// <summary>
        /// Difference type for the iterator.
        /// </summary>
        using difference_type = std::ptrdiff_t;
        /// <summary>
        /// Pointer type for the iterator.
        /// </summary>
        using pointer = BlockType*;
        /// <summary>
        /// Reference type for the iterator.
        /// </summary>
        using reference = BlockType&;
        /// <summary>
        /// Iterator category tag (bidirectional).
        /// </summary>
        using iterator_category = std::bidirectional_iterator_tag;
    private:
        BlockManagerType& blockManager_;
        pointer current_;
    public:
        /// <summary>
        /// Construct an iterator associated with a block manager and positioned at the end (null).
        /// </summary>
        /// <param name="blockManager">Reference to the block manager the iterator will traverse.</param>
        /// <remarks>
        /// The constructed iterator's `current_` is initialized to nullptr which corresponds
        /// to the `end()` iterator for the manager.
        /// </remarks>
        constexpr BlockIterator( BlockManagerType& blockManager ) noexcept
            : blockManager_( blockManager ), current_( nullptr )
        { }

        /// <summary>
        /// Construct an iterator associated with a block manager and positioned at a given block.
        /// </summary>
        /// <param name="blockManager">Reference to the block manager the iterator will traverse.</param>
        /// <param name="current">Pointer to the current block (may be nullptr to represent end()).</param>
        constexpr BlockIterator( BlockManagerType& blockManager, pointer current ) noexcept
            : blockManager_( blockManager ), current_( current )
        { }

        /// <summary>
        /// Compare two iterators for equality.
        /// </summary>
        /// <param name="other">Other iterator to compare with.</param>
        /// <returns>True if both iterators point to the same block (including both being end()); otherwise false.</returns>
        constexpr bool operator == ( const BlockIterator& other ) const noexcept
        {
            return current_ == other.current_;
        }

        /// <summary>
        /// Compare two iterators for inequality.
        /// </summary>
        /// <param name="other">Other iterator to compare with.</param>
        /// <returns>True if the iterators point to different blocks; otherwise false.</returns>
        constexpr bool operator != ( const BlockIterator& other ) const noexcept
        {
            return current_ != other.current_;
        }

        /// <summary>
        /// Dereference the iterator to obtain a reference to the current block.
        /// </summary>
        /// <returns>Reference to the current block.</returns>
        /// <remarks>
        /// Precondition: `current_` must not be nullptr. Behavior is undefined if dereferenced
        /// when iterator equals `end()`.
        /// </remarks>
        constexpr reference operator*( ) const noexcept
        {
            return *current_;
        }

        /// <summary>
        /// Pre-increment: advance the iterator to the next block.
        /// </summary>
        /// <returns>Reference to the advanced iterator.</returns>
        /// <remarks>
        /// If the iterator is at end (current_ == nullptr) this operation has no effect.
        /// Complexity: O(1).
        /// </remarks>
        BlockIterator& operator++( ) noexcept
        {
            if ( current_ )
            {
                current_ = (pointer)current_->Next( );
            }
            return *this;
        }

        /// <summary>
        /// Post-increment: advance the iterator to the next block, returning the previous value.
        /// </summary>
        /// <param name="unused">Int parameter distinguishing post-increment overload.</param>
        /// <returns>Iterator value prior to increment.</returns>
        /// <remarks>
        /// If the iterator is at end (current_ == nullptr) this operation returns an iterator
        /// equal to end() and has no effect on the iterator state.
        /// Complexity: O(1) (makes a shallow copy).
        /// </remarks>
        BlockIterator operator++( int ) noexcept
        {
            BlockIterator result( blockManager_, current_ );
            if ( current_ )
            {
                current_ = (pointer)current_->Next( );
            }
            return result;
        }

        /// <summary>
        /// Pre-decrement: move the iterator to the previous block.
        /// </summary>
        /// <returns>Reference to the decremented iterator.</returns>
        /// <remarks>
        /// If the iterator is at end (current_ == nullptr) the iterator is moved to the tail
        /// of the associated block manager. Complexity: O(1).
        /// </remarks>
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

        /// <summary>
        /// Post-decrement: move the iterator to the previous block, returning the previous value.
        /// </summary>
        /// <param name="unused">Int parameter distinguishing post-decrement overload.</param>
        /// <returns>Iterator value prior to decrement.</returns>
        /// <remarks>
        /// If the iterator is at end (current_ == nullptr) the iterator is moved to the tail
        /// of the associated block manager and the returned iterator is the previous end().
        /// Complexity: O(1).
        /// </remarks>
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



    /// <summary>
    /// Manages a doubly-linked list of `Block` objects and provides iteration helpers.
    /// </summary>
    /// <remarks>
    /// `BlockManager` owns the `Block` objects appended to it and frees them when the manager
    /// is cleared or destroyed. The manager provides simple append semantics and exposes
    /// bidirectional iterators via `begin()`/`end()` and `cbegin()`/`cend()`.
    /// The class is not copyable but is movable. Thread-safety: callers must synchronize
    /// concurrent access to the manager.
    /// </remarks>
    class BlockManager
    {
        Block* head_;
        Block* tail_;
        size_t size_;
    public:
        /// <summary>
        /// Iterator type for traversing `Block` elements.
        /// </summary>
        using iterator = BlockIterator<BlockManager, Block>;
        /// <summary>
        /// Const iterator type for traversing `Block` elements.
        /// </summary>
        using const_iterator = BlockIterator<const BlockManager, const Block>;


        /// <summary>
        /// Construct an empty `BlockManager`.
        /// </summary>
        /// <remarks>
        /// The constructed manager contains no blocks and has size zero.
        /// </remarks>
        constexpr BlockManager( ) noexcept
            : head_( nullptr ), tail_( nullptr ), size_( 0 )
        { }

        /// <summary>
        /// Copy construction is deleted.
        /// </summary>
        BlockManager( const BlockManager& other ) = delete;
        /// <summary>
        /// Copy assignment is deleted.
        /// </summary>
        BlockManager& operator = ( const BlockManager& other ) = delete;

        /// <summary>
        /// Move-construct a `BlockManager` transferring ownership of blocks.
        /// </summary>
        /// <param name="other">The source manager whose resources will be moved from.</param>
        /// <remarks>
        /// After the move, `other` will be empty and have size zero.
        /// Complexity: O(1).
        /// </remarks>
        constexpr BlockManager( BlockManager&& other ) noexcept
            : head_( other.head_ ), tail_( other.tail_ ), size_( other.size_ )
        {
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }


        /// <summary>
        /// Move-assign a `BlockManager` transferring ownership of blocks.
        /// </summary>
        /// <param name="other">The source manager whose resources will be moved from.</param>
        /// <returns>Reference to this instance after assignment.</returns>
        /// <remarks>
        /// Any existing blocks owned by this instance will be cleared before taking ownership
        /// from `other`. After the operation `other` will be empty.
        /// Complexity: O(n) to clear existing blocks where n is current size.
        /// </remarks>
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
            return *this;
        }

        /// <summary>
        /// Destructor - releases all managed blocks.
        /// </summary>
        /// <remarks>
        /// Calls `Clear()` to free all blocks owned by the manager.
        /// </remarks>
        ~BlockManager( )
        {
            Clear( );
        }

        /// <summary>
        /// Clear the manager and free all blocks owned by it.
        /// </summary>
        /// <remarks>
        /// After calling `Clear()`, the manager will be empty and its size will be zero.
        /// This operation frees each `Block` by calling `Block::Free`.
        /// </remarks>
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


        /// <summary>
        /// Append an existing block to the manager.
        /// </summary>
        /// <param name="block">Pointer to the block to append. Ownership is transferred to the manager.</param>
        /// <remarks>
        /// Caller transfers ownership of `block` to the manager. The function updates
        /// manager's head/tail pointers and increments the size.
        /// Precondition: `block` must not be part of another list unless the caller
        /// intentionally overwrites its previous/next pointers.
        /// </remarks>
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

        /// <summary>
        /// Truncate the block manager to contain at most `newCount` blocks.
        /// </summary>
        /// <param name="newCount">Number of blocks to keep; if zero the manager is cleared.</param>
        /// <remarks>
        /// Frees blocks from the tail until the manager contains `newCount` blocks.
        /// This is an O(k) operation where k is the number of blocks removed.
        /// </remarks>
        void Truncate( size_t newCount )
        {
            if ( newCount == 0 )
            {
                Clear( );
                return;
            }
            if ( newCount >= size_ )
            {
                return;
            }

            // Find the new tail by walking from the head (newCount >= 1)
            Block* newTail = head_;
            for ( size_t i = 1; i < newCount; ++i )
            {
                newTail = newTail->Next( );
            }

            // Free all blocks after newTail
            Block* toFree = newTail->Next( );
            while ( toFree )
            {
                Block* next = toFree->Next( );
                Block::Free( toFree );
                toFree = next;
            }

            // Set new tail and adjust size
            newTail->SetNext( nullptr );
            tail_ = newTail;
            size_ = newCount;
        }

        /// <summary>
        /// Get the head (first) block in the manager.
        /// </summary>
        /// <returns>Pointer to the head block, or nullptr if the manager is empty.</returns>
        constexpr Block* Head( ) const noexcept
        {
            return head_;
        }

        /// <summary>
        /// Get the tail (last) block in the manager.
        /// </summary>
        /// <returns>Pointer to the tail block, or nullptr if the manager is empty.</returns>
        constexpr Block* Tail( ) const noexcept
        {
            return tail_;
        }

        /// <summary>
        /// Allocate a new block, append it to the manager and return it.
        /// </summary>
        /// <returns>Pointer to the newly allocated block. Ownership is transferred to the caller and the manager.</returns>
        /// <exception cref="SystemException">When block allocation or OS error occurs.</exception>
        /// <remarks>
        /// This calls `Block::Allocate()` to create the block and then appends it to this manager.
        /// </remarks>
        Block* Append( )
        {
            auto* result = Block::Allocate( );
            Append( result );
            return result;
        }


        /// <summary>
        /// Get the number of blocks currently stored in the manager.
        /// </summary>
        /// <returns>The count of blocks managed by this instance.</returns>
        constexpr size_t size( ) const noexcept
        {
            return size_;
        }

        /// <summary>
        /// Determine whether the manager currently has no blocks.
        /// </summary>
        /// <returns>True if the manager is empty; otherwise false.</returns>
        constexpr bool empty( ) const noexcept
        {
            return size_ == 0;
        }


        /// <summary>
        /// Get an iterator to the first block.
        /// </summary>
        /// <returns>An iterator positioned at the head block; equals `end()` if empty.</returns>
        constexpr iterator begin( ) noexcept
        {
            iterator result( *this, head_ );
            return result;
        }

        /// <summary>
        /// Get an iterator representing one-past-the-last block.
        /// </summary>
        /// <returns>An iterator equal to `end()` for the manager.</returns>
        constexpr iterator end( ) noexcept
        {
            iterator result( *this );
            return result;
        }

        /// <summary>
        /// Get a const iterator to the first block.
        /// </summary>
        /// <returns>A const_iterator positioned at the head block; equals `cend()` if empty.</returns>
        constexpr const_iterator cbegin( ) const noexcept
        {
            const_iterator result( *this, head_ );
            return result;
        }

        /// <summary>
        /// Get a const iterator representing one-past-the-last block.
        /// </summary>
        /// <returns>A const_iterator equal to `cend()` for the manager.</returns>
        constexpr const_iterator cend( ) const noexcept
        {
            const_iterator result( *this );
            return result;
        }

        /// <summary>
        /// Get a const iterator to the first block (alias for `cbegin()`).
        /// </summary>
        /// <returns>A const_iterator positioned at the head block.</returns>
        constexpr const_iterator begin( ) const noexcept
        {
            return cbegin( );
        }
        /// <summary>
        /// Get a const iterator representing one-past-the-last block (alias for `cend()`).
        /// </summary>
        /// <returns>A const_iterator equal to `cend()` for the manager.</returns>
        constexpr const_iterator end( ) const noexcept
        {
            return cend( );
        }
    };




    class Stream
    {
    public:
        using SeekOrigin = Harlinn::Common::Core::IO::SeekOrigin;

        static constexpr size_t BlockDataSize = Block::DataSize;
        static_assert( BlockDataSize != 0 );

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
            : currentBlock_( nullptr ), currentNumber_( 0 ), currentOffset_( 0 ), lastBlockSize_( 0 )
        { }

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
        /// <summary>
        /// Convert the stream contents into a container of element type compatible with byte representation.
        /// </summary>
        /// <typeparam name="T">
        /// Container type to convert to. The type must provide a public typedef `value_type`,
        /// a `resize(size_t)` method and contiguous storage accessible through `data()` (e.g. `std::vector<Byte>`,
        /// `AnsiString`, `WideString`, or any repository `StringLike` type).
        /// </typeparam>
        /// <returns>
        /// A container of type <typeparamref name="T"/> containing the stream bytes. The container size
        /// will be ceil(size()/sizeof(value_type)).
        /// </returns>
        /// <remarks>
        /// The function reads the logical stream size (the number of valid bytes stored) and copies bytes from
        /// the block list into the returned container. For non-tail blocks the full `Block::DataSize` bytes are copied;
        /// for the tail block only `lastBlockSize_` bytes are copied. If the stream is empty an appropriately sized
        /// but empty container is returned. This function is not thread-safe and must be called with external
        /// synchronization if the stream is concurrently modified. The function uses `std::memcpy` to copy bytes
        /// into the destination storage; it does not perform encoding conversions — use the typed conversion helpers
        /// for string types.</remarks>
        /// <exception cref="SystemException">When allocation or OS error occurs during container resizing or operations.</exception>

        template<typename T>
        T ConvertTo( ) const
        {
            T result;
            const auto count = size( );
            if ( count == 0 )
            {
                return result;
            }

            using value_type = typename T::value_type;
            constexpr size_t elemSize = sizeof( value_type );

            // Allocate enough elements to hold 'count' bytes.
            // Use ceil(count/elemSize) to avoid writing into a zero-sized buffer.
            const size_t elementCount = ( count + elemSize - 1 ) / elemSize;
            result.resize( elementCount );

            auto destPtr = reinterpret_cast<Byte*>( result.data( ) );
            size_t copied = 0;

            auto head = blockManager_.Head( );
            auto tail = blockManager_.Tail( );

            // Walk blocks and copy only the valid bytes (Block::DataSize for non-tail blocks,
            // lastBlockSize_ for the tail). Stop when we've copied 'count' bytes.
            while ( head && copied < count )
            {
                const size_t blockBytes = ( head != tail ) ? Block::DataSize : lastBlockSize_;
                if ( blockBytes )
                {
                    const size_t toCopy = std::min( blockBytes, count - copied );
                    std::memcpy( destPtr + copied, head->data( ), toCopy );
                    copied += toCopy;
                }
                if ( head == tail )
                {
                    break;
                }
                head = head->Next( );
            }

#ifdef _DEBUG
            assert( copied == count );
#endif

            return result;
        }
    public:
        /// <summary>
        /// Convert the stream contents to a byte vector.
        /// </summary>
        /// <returns>A `std::vector<Byte>` containing the stream's bytes in order from the stream start to end.</returns>
        /// <remarks>
        /// Uses `ConvertTo<std::vector<Byte>>()` internally. The returned vector's size equals `size()`.
        /// The operation performs an allocation proportional to the stream size and copies the stream bytes into
        /// the returned vector. Not thread-safe: caller must synchronize concurrent modifications to the stream.
        /// </remarks>
        std::vector<Byte> ToBytes( ) const
        {
            return ConvertTo<std::vector<Byte>>( );
        }

        /// <summary>
        /// Convert the stream contents to an `AnsiString`.
        /// </summary>
        /// <returns>An `AnsiString` containing the stream bytes. Interpretation is raw byte-to-char mapping for the
        /// repository's `AnsiString` type; no additional encoding conversion is performed.</returns>
        /// <remarks>
        /// Uses `ConvertTo<AnsiString>()` internally. The returned string's length in characters corresponds to the
        /// number of bytes in the stream (i.e. `size()`). Use `ToWideString()` when a UTF-16 / wide character representation
        /// is required after an explicit encoding conversion step by the caller.
        /// </remarks>
        AnsiString ToAnsiString( ) const
        {
            return ConvertTo<AnsiString>( );
        }

        /// <summary>
        /// Convert the stream contents to a `WideString`.
        /// </summary>
        /// <returns>A `WideString` containing the stream bytes reinterpreted as wide character storage for the repository's
        /// `WideString` type. No automatic encoding conversion is performed.</returns>
        /// <remarks>
        /// Uses `ConvertTo<WideString>()` internally. The caller is responsible for ensuring that interpreting bytes
        /// as wide characters is meaningful for their use case. For explicit encoding conversions prefer repository
        /// conversion helpers before or after obtaining the `WideString`.
        /// </remarks>
        WideString ToWideString( ) const
        {
            return ConvertTo<WideString>( );
        }

        /// <summary>
        /// Convert the stream contents to an arbitrary string-like container type.
        /// </summary>
        /// <typeparam name="T">String-like type satisfying the `StringLike` concept in the repository. Must provide
        /// `value_type`, `resize(size_t)` and `data()` members.</typeparam>
        /// <returns>An instance of `T` containing the stream bytes. The container length corresponds to `size()`.</returns>
        /// <remarks>
        /// This template forwards to `ConvertTo<T>()`. Ensure the chosen `T` semantically matches how you want to
        /// interpret the raw stream bytes. This operation is not thread-safe and performs allocations and copies
        /// proportional to the stream size.
        /// </remarks>
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
        /// <summary>
        /// Set the current stream position.
        /// </summary>
        /// <param name="position">
        /// New position in bytes from the stream start. Negative or zero 
        /// values move to the stream start.
        /// </param>
        /// <remarks>
        /// Optimized seek: chooses the nearest traversal origin (current, head or tail) to minimize pointer walks
        /// in the internal block linked list. If position is beyond current size the stream is expanded via SetSize.
        /// This function is not thread-safe; caller must synchronize concurrent modifications.
        /// </remarks>
        void SetPosition( long long position )
        {
            // Handle negative and zero positions explicitly to avoid casting negative to size_t.
            if ( position <= 0 )
            {
                MoveBegin( );
                return;
            }

            const size_t newPosition = static_cast<size_t>( position );
            const size_t sz = size( );

            // If newPosition is at or beyond end, grow if necessary and move to end.
            if ( newPosition >= sz )
            {
                if ( newPosition > sz )
                {
                    // SetSize accepts long long; pass original position to preserve semantics.
                    SetSize( position );
                }

                // Move to tail and set position to end-of-stream offset.
                if ( blockManager_.size( ) )
                {
                    currentBlock_ = blockManager_.Tail( );
                    currentNumber_ = blockManager_.size( ) - 1;
                    currentOffset_ = lastBlockSize_;
                }
                else
                {
                    // empty stream
                    currentBlock_ = nullptr;
                    currentNumber_ = 0;
                    currentOffset_ = 0;
                }
                return;
            }

            // newPosition < sz: compute target block and offset.
            const size_t targetSegment = newPosition / BlockDataSize;
            const size_t targetOffset = newPosition % BlockDataSize;

            const size_t numberOfBlocks = blockManager_.size( );
            if ( numberOfBlocks == 0 )
            {
                // Shouldn't happen because newPosition < sz implies blocks exist, but be defensive.
                MoveBegin( );
                return;
            }

            const size_t tailIndex = numberOfBlocks - 1;

            // Determine best starting point (head=0, current=currentNumber_, tail=tailIndex)
            size_t startIndex = currentBlock_ ? currentNumber_ : 0;

            auto abs_diff = [ ]( size_t a, size_t b ) noexcept -> size_t
            {
                return ( a > b ) ? ( a - b ) : ( b - a );
            };

            const size_t distFromCurrent = currentBlock_ ? abs_diff( startIndex, targetSegment ) : SIZE_MAX;
            const size_t distFromHead = abs_diff( 0, targetSegment );
            const size_t distFromTail = abs_diff( tailIndex, targetSegment );

            // Start from the nearest origin and traverse
            if ( distFromCurrent <= distFromHead && distFromCurrent <= distFromTail )
            {
                // start from current position
                if ( targetSegment == startIndex )
                {
                    currentOffset_ = targetOffset;
                    return;
                }
                if ( targetSegment > startIndex )
                {
                    while ( currentNumber_ < targetSegment )
                    {
                        MoveNext( );
                    }
                }
                else
                {
                    while ( currentNumber_ > targetSegment )
                    {
                        MovePrevious( );
                    }
                }
                currentOffset_ = targetOffset;
                return;
            }
            else if ( distFromHead <= distFromTail )
            {
                // start from head
                currentBlock_ = blockManager_.Head( );
                currentNumber_ = 0;
                currentOffset_ = 0;
                while ( currentNumber_ < targetSegment )
                {
                    MoveNext( );
                }
                currentOffset_ = targetOffset;
                return;
            }
            else
            {
                // start from tail
                currentBlock_ = blockManager_.Tail( );
                currentNumber_ = tailIndex;
                // Move backwards until reaching targetSegment
                while ( currentNumber_ > targetSegment )
                {
                    MovePrevious( );
                }
                currentOffset_ = targetOffset;
                return;
            }
        }


        constexpr size_t size( ) const noexcept
        {
            const size_t numberOfBlocks = blockManager_.size( );
            if ( numberOfBlocks == 0 )
            {
                return 0;
            }

            const size_t blocksMinusOne = numberOfBlocks - 1;
            const size_t maxSize = static_cast<size_t>( -1 );

            const size_t maxBlocksProduct = ( maxSize - lastBlockSize_ ) / BlockDataSize;
            if ( blocksMinusOne > maxBlocksProduct )
            {
                return maxSize;
            }
            return ( blocksMinusOne * BlockDataSize ) + lastBlockSize_;
        }
        constexpr long long Size( ) const noexcept
        {
            return static_cast<long long>( size( ) );
        }
        /// <summary>
        /// Set the logical size of the stream in bytes.
        /// </summary>
        /// <param name="newSize">New size in bytes. Negative values are treated as zero. Growing the stream
        /// will append blocks as needed; shrinking is supported and will free trailing blocks and clamp the current position.</param>
        /// <remarks>
        /// This implementation:
        /// - Validates and clamps the incoming size to fit in `size_t`.
        /// - Computes the number of blocks required as `ceil(newSize / BlockDataSize)` and only appends
        ///   the difference between current and required blocks (no reallocation/copies) in the grow case.
        /// - When shrinking, frees trailing blocks beyond the required count and clamps the current position.
        /// - Ensures `lastBlockSize_` is set to `BlockDataSize` for exact multiples of `BlockDataSize`,
        ///   and to 0 for an empty stream.
        /// - Is defensive against overflow.
        /// Thread-safety: callers must synchronize concurrent access to the stream.
        /// </remarks>
        void SetSize( long long newSize )
        {
            if ( newSize < 0 )
            {
                newSize = 0;
            }

            // Clamp to size_t range to avoid narrowing undefined behaviour when casting.
            const unsigned long long maxSizeT = static_cast<unsigned long long>( std::numeric_limits<size_t>::max( ) );
            if ( static_cast<unsigned long long>( newSize ) > maxSizeT )
            {
                newSize = static_cast<long long>( maxSizeT );
            }

            const size_t requestedSize = static_cast<size_t>( newSize );

            const long long currentSizeLL = Size( );
            if ( static_cast<unsigned long long>( currentSizeLL ) == static_cast<unsigned long long>( requestedSize ) )
            {
                // No change required.
                return;
            }

            if ( currentSizeLL < newSize )
            {
                // Grow case.
                // requiredBlocks = ceil(requestedSize / BlockDataSize)
                const size_t requiredBlocks = requestedSize ? ( ( requestedSize + BlockDataSize - 1 ) / BlockDataSize ) : 0;

                // Compute last block size: for non-zero requestedSize,
                // lastSize = requestedSize % BlockDataSize; if 0 => full block => BlockDataSize
                size_t lastSize = 0;
                if ( requestedSize )
                {
                    lastSize = requestedSize % BlockDataSize;
                    if ( lastSize == 0 )
                    {
                        lastSize = BlockDataSize;
                    }
                }

                const size_t currentBlocks = blockManager_.size( );

                // Append only necessary blocks.
                if ( currentBlocks < requiredBlocks )
                {
                    for ( size_t i = currentBlocks; i < requiredBlocks; ++i )
                    {
                        blockManager_.Append( );
                    }
                }

                lastBlockSize_ = lastSize;

#ifdef _DEBUG
                // Sanity checks
                if ( requiredBlocks == 0 )
                {
                    assert( lastBlockSize_ == 0 );
                }
                else
                {
                    assert( lastBlockSize_ >= 1 && lastBlockSize_ <= BlockDataSize );
                    assert( blockManager_.size( ) >= requiredBlocks );
                }
#endif
            }
            else
            {
                // Shrink case (implemented)
                const size_t requiredBlocks = requestedSize ? ( ( requestedSize + BlockDataSize - 1 ) / BlockDataSize ) : 0;

                // Compute last block size for the requested size
                size_t lastSize = 0;
                if ( requestedSize )
                {
                    lastSize = requestedSize % BlockDataSize;
                    if ( lastSize == 0 )
                    {
                        lastSize = BlockDataSize;
                    }
                }

                const size_t currentBlocks = blockManager_.size( );

                if ( requiredBlocks == 0 )
                {
                    // Free all blocks
                    blockManager_.Clear( );
                }
                else if ( requiredBlocks < currentBlocks )
                {
                    // Truncate the block list to requiredBlocks
                    blockManager_.Truncate( requiredBlocks );
                }

                // Update last block size
                lastBlockSize_ = lastSize;

                // Clamp current position if it is beyond new size.
                const size_t newSizePos = requestedSize;
                const size_t curPos = position( );

                if ( newSizePos == 0 )
                {
                    currentBlock_ = nullptr;
                    currentNumber_ = 0;
                    currentOffset_ = 0;
                }
                else
                {
                    if ( curPos > newSizePos )
                    {
                        // Move to end (requestedSize)
                        SetPosition( static_cast<long long>( newSizePos ) );
                    }
                    else
                    {
                        // Ensure current block references remain valid after truncation:
                        const size_t blocksNow = blockManager_.size( );
                        if ( blocksNow == 0 )
                        {
                            currentBlock_ = nullptr;
                            currentNumber_ = 0;
                            currentOffset_ = 0;
                        }
                        else if ( currentBlock_ && currentNumber_ >= blocksNow )
                        {
                            // Position at end
                            MoveEnd( );
                            // If currentOffset_ is larger than lastBlockSize_, clamp it
                            if ( currentOffset_ > lastBlockSize_ )
                            {
                                currentOffset_ = lastBlockSize_;
                            }
                        }
                        else if ( currentBlock_ && currentNumber_ == blocksNow - 1 )
                        {
                            // We're in the tail; ensure offset not beyond new last block size
                            if ( currentOffset_ > lastBlockSize_ )
                            {
                                currentOffset_ = lastBlockSize_;
                            }
                        }
                    }
                }

#ifdef _DEBUG
                // Sanity checks
                if ( requiredBlocks == 0 )
                {
                    assert( lastBlockSize_ == 0 );
                    assert( blockManager_.size( ) == 0 );
                }
                else
                {
                    assert( lastBlockSize_ >= 1 && lastBlockSize_ <= BlockDataSize );
                    assert( blockManager_.size( ) == requiredBlocks );
                }
#endif
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
        { }
        long long Read( void* buffer, size_t numberOfBytesToRead )
        {
            // Defensive fast-paths
            if ( buffer == nullptr || numberOfBytesToRead == 0 )
            {
                return 0;
            }
            if ( currentBlock_ == nullptr )
            {
                return 0;
            }

#ifdef _DEBUG
            assert( buffer != nullptr );
#endif

            Byte* writePtr = reinterpret_cast<Byte*>( buffer );
            const Byte* writeStart = writePtr;
            size_t remaining = numberOfBytesToRead;

            Block* tail = blockManager_.Tail( );

            // If we're not in the tail block, copy current block remainder (full-size blocks)
            if ( currentBlock_ != tail )
            {
                // bytes remaining in current (non-tail) block
                const size_t curRemaining = BlockDataSize - currentOffset_;
                if ( curRemaining )
                {
                    const size_t toCopy = std::min( remaining, curRemaining );
                    std::memcpy( writePtr, currentBlock_->data( ) + currentOffset_, toCopy );
                    writePtr += toCopy;
                    remaining -= toCopy;
                    currentOffset_ += toCopy;

                    if ( remaining == 0 )
                    {
                        return static_cast<long long>( writePtr - writeStart );
                    }
                }

                // Traverse and copy from subsequent blocks (handle tail size correctly)
                while ( remaining && currentBlock_ != tail )
                {
                    if ( !MoveNext( ) )
                    {
                        // No further block available
                        break;
                    }

                    const size_t blockCapacity = ( currentBlock_ == tail ) ? lastBlockSize_ : BlockDataSize;
                    if ( blockCapacity == 0 )
                    {
                        // Nothing valid to read from this block; stop.
                        break;
                    }

                    const size_t toCopy = std::min( remaining, blockCapacity );
                    std::memcpy( writePtr, currentBlock_->data( ), toCopy );
                    writePtr += toCopy;
                    remaining -= toCopy;

                    // Set offset within current block to the number of bytes read.
                    currentOffset_ = toCopy;

                    // If we moved into the tail block, do not attempt to read beyond its lastBlockSize_.
                    if ( currentBlock_ == tail )
                    {
                        break;
                    }
                }

                return static_cast<long long>( writePtr - writeStart );
            }
            else
            {
                // We're already in the tail block: only read up to lastBlockSize_ - currentOffset_
                const size_t tailRemaining = ( lastBlockSize_ > currentOffset_ ) ? ( lastBlockSize_ - currentOffset_ ) : 0;
                const size_t toCopy = std::min( remaining, tailRemaining );
                if ( toCopy )
                {
                    std::memcpy( writePtr, currentBlock_->data( ) + currentOffset_, toCopy );
                    currentOffset_ += toCopy;
                }
                return static_cast<long long>( toCopy );
            }
        }


        long long Write( const void* buffer, size_t numberOfBytesToWrite )
        {
            // Fast no-op
            if ( numberOfBytesToWrite == 0 )
            {
                return 0;
            }

#ifdef _DEBUG
            // Defensive debug check to catch incorrect callers early.
            assert( buffer != nullptr );
#endif

            const Byte* src = reinterpret_cast<const Byte*>( buffer );
            size_t remaining = numberOfBytesToWrite;

            // Fast path: we're positioned at the tail block and can append directly.
            Block* tail = blockManager_.Tail( );
            if ( tail && currentBlock_ == tail )
            {
                const size_t spaceInTail = BlockDataSize - currentOffset_;
                if ( remaining <= spaceInTail )
                {
                    // Entire write fits in current tail block
                    auto* dest = currentBlock_->data( ) + currentOffset_;
                    std::memcpy( dest, src, remaining );
                    currentOffset_ += remaining;
                    lastBlockSize_ = std::max( lastBlockSize_, currentOffset_ );
                    return static_cast<long long>( numberOfBytesToWrite );
                }

                // Fill remaining space in tail, then append full/partial blocks for the rest.
                if ( spaceInTail )
                {
                    auto* dest = currentBlock_->data( ) + currentOffset_;
                    std::memcpy( dest, src, spaceInTail );
                    src += spaceInTail;
                    remaining -= spaceInTail;
                    currentOffset_ = BlockDataSize;
                    lastBlockSize_ = BlockDataSize;
                }

                // Append remaining bytes into new blocks
                const size_t appended = AppendBlocks( src, remaining );
                // AppendBlocks returns number of bytes written (original requested count)
                return static_cast<long long>( ( numberOfBytesToWrite - remaining ) + appended );
            }

            // If we have a current block but are not at tail: overwrite existing bytes up to stream size,
            // then append any remaining bytes.
            if ( currentBlock_ )
            {
                const size_t pos = position( );
                const size_t sz = size( );

                // Defensive: if pos > sz for any reason, treat overwriteMax as 0.
                const size_t overwriteMax = ( pos <= sz ) ? ( sz - pos ) : 0u;

                const size_t toOverwrite = std::min( remaining, overwriteMax );
                if ( toOverwrite )
                {
                    Overwrite( src, toOverwrite );
                    src += toOverwrite;
                    remaining -= toOverwrite;
                }

                if ( remaining )
                {
                    // After overwriting, append the rest.
                    const size_t appended = AppendBlocks( src, remaining );
                    return static_cast<long long>( toOverwrite + appended );
                }

                return static_cast<long long>( toOverwrite );
            }

            // No current block: append blocks (stream empty or cursor uninitialized).
            const size_t appended = AppendBlocks( src, remaining );
            return static_cast<long long>( appended );
        }

        long long Seek( long long offset, SeekOrigin seekOrigin )
        {
            // Helpers to safely convert unsigned sizes to signed long long with clamping.
            auto toLongLongClamped = [ ]( size_t u ) noexcept -> long long
            {
                if ( u > static_cast<size_t>( LLONG_MAX ) )
                {
                    return LLONG_MAX;
                }
                return static_cast<long long>( u );
            };
            auto safeAdd = [ ]( long long a, long long b ) noexcept -> long long
            {
                if ( b > 0 && a > LLONG_MAX - b ) return LLONG_MAX;
                if ( b < 0 && a < LLONG_MIN - b ) return LLONG_MIN;
                return a + b;
            };

            long long newPosition = 0;

            switch ( seekOrigin )
            {
                case SeekOrigin::StartOfFile:
                    // negative or zero => begin; positive => that offset
                    newPosition = ( offset > 0 ) ? offset : 0;
                    break;

                case SeekOrigin::CurrentPosition:
                {
                    const long long currentPosLL = toLongLongClamped( position( ) );
                    newPosition = safeAdd( currentPosLL, offset );
                    break;
                }

                case SeekOrigin::EndOfFile:
                {
                    const long long sizeLL = toLongLongClamped( size( ) );
                    newPosition = safeAdd( sizeLL, offset );
                    break;
                }
            }

            // Normalize negatives to zero (seek before begin => begin).
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
            if ( currentBlock_ == nullptr || buffer == nullptr || numberOfBytesToWrite == 0 )
            {
                return;
            }

            const Byte* src = buffer;
            size_t remaining = numberOfBytesToWrite;

            // Copy into current block up to its remaining capacity
            const size_t curRemaining = CurrentBlockRemaining( );
            if ( remaining <= curRemaining )
            {
                auto* dest = currentBlock_->data( ) + currentOffset_;
                std::memcpy( dest, src, remaining );
                currentOffset_ += remaining;
                return;
            }

            // Fill remainder of current block, could be zero
            if ( curRemaining )
            {
                auto* dest = currentBlock_->data( ) + currentOffset_;
                std::memcpy( dest, src, curRemaining );
                src += curRemaining;
                remaining -= curRemaining;
                // move offset to end-of-block (MoveNext will reset offset to 0)
                currentOffset_ += curRemaining;
            }

            // Cache tail pointer, must not write beyond the tail block's valid bytes
            Block* tail = blockManager_.Tail( );

            // Traverse forward and overwrite existing blocks, including the tail up to its valid size.
            while ( remaining && currentBlock_ != tail )
            {
                // Move to next block; MoveNext sets currentOffset_ = 0 and increments currentNumber_ on success
                if ( !MoveNext( ) )
                {
                    // No next block available; nothing more to overwrite
                    break;
                }

                // Determine how many bytes we may write into the block we just moved to
                const size_t blockCapacity = ( currentBlock_ == tail ) ? lastBlockSize_ : BlockDataSize;
                if ( blockCapacity == 0 )
                {
                    // Nothing valid to overwrite in this block, so stop.
                    break;
                }

                const size_t toCopy = std::min( remaining, blockCapacity );
                auto* dest = currentBlock_->data( );
                std::memcpy( dest, src, toCopy );

                // Set currentOffset_ to the position after the bytes we wrote into this block
                currentOffset_ = toCopy;

                src += toCopy;
                remaining -= toCopy;

                // If we've reached tail, we must not write beyond lastBlockSize_, so stop
                if ( currentBlock_ == tail )
                {
                    break;
                }
            }
        }

        size_t AppendBlocks( const Byte* buffer, size_t numberOfBytesToWrite )
        {
            if ( buffer == nullptr || numberOfBytesToWrite == 0 )
            {
                return 0;
            }

            const Byte* src = buffer;
            const size_t originalCount = numberOfBytesToWrite;

            const size_t fullBlocks = numberOfBytesToWrite / BlockDataSize;
            const size_t remaining = numberOfBytesToWrite % BlockDataSize;

            Block* lastAppended = nullptr;

            // Append and fill full blocks
            for ( size_t i = 0; i < fullBlocks; ++i )
            {
                Block* block = blockManager_.Append( );
                std::memcpy( block->data( ), src, BlockDataSize );
                src += BlockDataSize;
                lastAppended = block;
            }

            // Append and fill trailing partial block, if any
            if ( remaining )
            {
                Block* block = blockManager_.Append( );
                std::memcpy( block->data( ), src, remaining );
                src += remaining;
                lastAppended = block;
                currentBlock_ = block;
                currentOffset_ = remaining;
                lastBlockSize_ = remaining;
            }
            else
            {
                // No partial trailing block, last block appended, if any, is full.
                if ( lastAppended )
                {
                    currentBlock_ = lastAppended;
                    currentOffset_ = BlockDataSize;
                    lastBlockSize_ = BlockDataSize;
                }
            }

            const size_t blocksNow = blockManager_.size( );
            if ( blocksNow )
            {
                currentNumber_ = blocksNow - 1;
            }
            return originalCount;
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
                    currentNumber_++;
                    // entering a fresh block, position at its beginning
                    currentOffset_ = 0;
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
                    currentNumber_--;
                    // position at the end of the previous block.
                    // If the previous block is the tail, use lastBlockSize_, otherwise full BlockDataSize.
                    const size_t blockSize = ( currentBlock_ == blockManager_.Tail( ) ) ? lastBlockSize_ : BlockDataSize;
                    currentOffset_ = blockSize;
                    return true;
                }
            }
            return false;
        }

        void MoveBegin( )
        {
            currentBlock_ = blockManager_.Head( );
            currentNumber_ = 0;
            currentOffset_ = 0;
        }

        void MoveEnd( )
        {
            if ( blockManager_.size( ) )
            {
                currentBlock_ = blockManager_.Tail( );
                currentNumber_ = blockManager_.size( ) - 1;
                currentOffset_ = lastBlockSize_;
            }
            else
            {
                currentBlock_ = nullptr;
                currentNumber_ = 0;
                currentOffset_ = 0;
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