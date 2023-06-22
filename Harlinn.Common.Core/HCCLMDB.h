#pragma once
#ifndef __HCCLMDB_H__
#define __HCCLMDB_H__

#include <HCCDef.h>
#include <HCCException.h>
#include <HCCString.h>
#include <lmdb.h>

namespace Harlinn::Common::Core::LMDB
{
    template<typename T>
    concept ValueType = (std::is_arithmetic_v<T> ||
        std::is_standard_layout_v<T>) && std::is_base_of_v<MDB_val,T> == false;

    enum class EnvironmentFlags : unsigned int
    {
        None = 0,
        /// <summary>
        /// use a fixed address for the mmap region. This flag must be specified
        /// when creating the environment, and is stored persistently in the environment.
        /// If successful, the memory map will always reside at the same virtual address
        /// and pointers used to reference data items in the database will be constant
        /// across multiple invocations. This option may not always work, depending on
        /// how the operating system has allocated memory to shared libraries and other uses.
        /// The feature is highly experimental.
        /// </summary>
        FixedMap = MDB_FIXEDMAP,
        /// <summary>
        /// By default, LMDB creates its environment in a directory whose
        /// pathname is given in \b path, and creates its data and lock files
        /// under that directory. With this option, \b path is used as-is for
        /// the database main data file. The database lock file is the \b path
        /// with "-lock" appended.
        /// </summary>
        NoSubDir = MDB_NOSUBDIR,
        /// <summary>
        /// 
        /// </summary>
        NoSync = MDB_NOSYNC,
        /// <summary>
        /// Open the environment in read-only mode. No write operations will be
        /// allowed. LMDB will still modify the lock file - except on read-only
        /// filesystems, where LMDB does not use locks.
        /// </summary>
        ReadOnly = MDB_RDONLY,
        // don't fsync metapage after commit 
        NoMetaSync = MDB_NOMETASYNC,
        // use writable mmap 
        WriteMemMap = MDB_WRITEMAP,
        // use asynchronous msync when #MDB_WRITEMAP is used 
        MapAsync = MDB_MAPASYNC,
        // tie reader locktable slots to #MDB_txn objects instead of to threads 
        NoTLS = MDB_NOTLS,
        // don't do any locking, caller must manage their own locks 
        NoLock = MDB_NOLOCK,
        // don't do readahead (no effect on Windows) 
        NoReadAhead = MDB_NORDAHEAD,
        // don't initialize malloc'd memory before writing to datafile 
        NoMemInit = MDB_NOMEMINIT,
        // use the previous snapshot rather than the latest one 
        PrevSnapshot = MDB_PREVSNAPSHOT
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( EnvironmentFlags, unsigned int );


    enum class TransactionFlags : unsigned int
    {
        None = 0,
        // don't fsync after commit 
        NoSync = MDB_NOSYNC,
        // read only 
        ReadOnly = MDB_RDONLY,
        // don't fsync metapage after commit 
        NoMetaSync = MDB_NOMETASYNC,
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TransactionFlags, unsigned int );


    enum class DatabaseFlags : unsigned int
    {
        None = 0,
        /// <summary>
        /// Keys are strings to be compared in reverse order, from the end
        /// of the strings to the beginning. By default, Keys are treated as strings and
        /// compared from beginning to end.
        /// </summary>
        ReverseKey = MDB_REVERSEKEY,
        /// <summary>
        /// Duplicate keys may be used in the database. (Or, from another perspective,
        /// keys may have multiple data items, stored in sorted order.) By default
        /// keys must be unique and may have only a single data item.
        /// </summary>
        DupSort = MDB_DUPSORT,
        /// <summary>
        /// Keys are binary integers in native byte order, either unsigned int
        /// or size_t, and will be sorted as such.
        /// (lmdb expects 32-bit int <= size_t <= 32/64-bit mdb_size_t.)
        /// The keys must all be of the same size.
        /// </summary>
        IntegerKey = MDB_INTEGERKEY,
        /// <summary>
        /// This flag may only be used in combination with #MDB_DUPSORT. This option
        /// tells the library that the data items for this database are all the same
        /// size, which allows further optimizations in storage and retrieval. When
        /// all data items are the same size, the #MDB_GET_MULTIPLE, #MDB_NEXT_MULTIPLE
        /// and #MDB_PREV_MULTIPLE cursor operations may be used to retrieve multiple
        /// items at once.
        /// </summary>
        DupFixed = MDB_DUPFIXED,
        /// <summary>
        /// This option specifies that duplicate data items are binary integers,
        /// </summary>
        IntegerDup = MDB_INTEGERDUP,
        /// <summary>
        /// This option specifies that duplicate data items should be compared as
        /// strings in reverse order.
        /// </summary>
        Reversedup = MDB_REVERSEDUP,
        /// <summary>
        /// Create the named database if it doesn't exist. This option is not
        /// allowed in a read-only transaction or a read-only environment.
        /// </summary>
        Create = MDB_CREATE
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DatabaseFlags, unsigned int );

    enum class WriteFlags : unsigned int
    {
        None = 0,
        // For put: Don't write if the key already exists. 
        NoOverwrite = MDB_NOOVERWRITE,
        // Only for #MDB_DUPSORT<br>
        // For put: don't write if the key and data pair already exist.<br>
        // For mdb_cursor_del: remove all duplicate data items.
        NuDuplicates = MDB_NODUPDATA,
        // For mdb_cursor_put: overwrite the current key/data pair 
        Current = MDB_CURRENT,
        // For put: Just reserve space for data, don't copy it. Return a
        // pointer to the reserved space.
        Reserve = MDB_RESERVE,
        // Data is being appended, don't split full pages.
        Append = MDB_APPEND,
        // Duplicate data is being appended, don't split full pages. 
        AppendDuplicate = MDB_APPENDDUP,
        // Store multiple data items in one call. Only for #MDB_DUPFIXED. 
        Multiple = MDB_MULTIPLE
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( WriteFlags, unsigned int );

    enum class CopyFlags : unsigned int
    {
        None = 0,
        // Compacting copy: Omit free space from copy, 
        // and renumber all pages sequentially.
        Compact = MDB_CP_COMPACT
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( CopyFlags, unsigned int );

    


    namespace Internal
    {
        [[noreturn]] inline void ThrowException( const char* function, int result )
        {
            auto error = mdb_strerror( static_cast<int>( result ) );
            auto message = Format( "{}: {}", function, error );
            throw Exception( static_cast<int>( result ), message );
        }
    }



    /// <summary>
    /// The Value class makes it a little easier 
    /// to initialize an MDB_val structure 
    /// </summary>
    class Value : public MDB_val
    {
    public:
        using Base = MDB_val;

        constexpr Value( ) noexcept
            : Base{}
        {
        }
        template<typename T>
        requires (!requires( T t )
        {
            { t.size( ) }->std::convertible_to<size_t>;
            { t.data( ) }->std::convertible_to<typename T::value_type*>;
        })
        explicit Value(const T& value )
            : Base{sizeof(T),const_cast<T*>(&value) }
        {
        }

        template<typename T>
            requires requires( T t )
            {
                { t.size( ) }->std::convertible_to<size_t>;
                { t.data( ) }->std::convertible_to<typename T::value_type*>;
            }
        explicit Value( const T& value )
            : Base{ value.size() * sizeof( typename T::value_type ),const_cast<typename T::value_type*>( value.data() ) }
        {

        }

        template<typename T>
            requires requires( T t )
            {
                { t.size( ) }->std::convertible_to<size_t>;
                { t.data( ) }->std::convertible_to<typename T::value_type*>;
            }
        explicit Value( const T& value, size_t count )
            : Base{ count * sizeof( typename T::value_type ),const_cast<typename T::value_type*>( value.data() ) }
        {

        }

        template<typename T>
            requires std::is_pointer_v<T>
        explicit Value( const T data, size_t count )
            : Base{ count * sizeof( std::remove_pointer_t<T> ), const_cast<std::remove_const_t<std::remove_pointer_t<T>>*>( data ) }
        {
        }

        explicit Value( const void* buffer, size_t bufferSize )
            : Base{ bufferSize, const_cast<void*>( buffer ) }
        {
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return mv_size && mv_data;
        }
        constexpr bool IsValid( ) const noexcept
        {
            return mv_size && mv_data;
        }

        size_t Hash( ) const noexcept
        {
            if ( mv_size && mv_data )
            {
                return XXH3_64bits( mv_data, mv_size );
            }
            else
            {
                return 0;
            }
        }

    };

    /// <summary>
    /// The state of the cursor
    /// </summary>
    enum class CursorState
    {
        /// <summary>
        /// The state of the cursor is unknown
        /// </summary>
        Unknown = 0,
        Open,
        Positioned,
        Loaded,
        Reset,
        Closed
    };

    class Database;
    class Transaction;
    /// <summary>
    /// Cursor objects provides functionality that can be used 
    /// to navigate, search and modify key/value pairs in the 
    /// database.
    /// </summary>
    class Cursor
    {
        MDB_cursor* cursor_;
        Transaction* transaction_;
        CursorState state_;
        LMDB::Value key_;
        LMDB::Value value_;
    public:
        constexpr Cursor( ) noexcept
            : cursor_(nullptr), transaction_(nullptr), state_( CursorState::Unknown )
        {
        }

        constexpr explicit Cursor( Transaction* transaction, MDB_cursor* cursor, CursorState state ) noexcept
            : cursor_( cursor ), transaction_( transaction ), state_( state )
        {
        }
        Cursor( const Cursor& other ) = delete;
        Cursor( Cursor&& other ) noexcept
            : cursor_( other.cursor_ ), transaction_( other.transaction_ ), state_( other.state_ ), key_( other.key_ ), value_( other.value_ )
        {
            other.cursor_ = nullptr;
            other.transaction_ = nullptr;
            other.state_ = CursorState::Unknown;
            other.key_ = {};
            other.value_ = {};
        }

        Cursor& operator = ( const Cursor& other ) = delete;
        Cursor& operator = ( Cursor&& other ) noexcept
        {
            if ( this != &other )
            {
                swap( other );
            }
            return *this;
        }

        constexpr bool IsOpen( ) const noexcept
        {
            return state_ == CursorState::Positioned || state_ == CursorState::Loaded || state_ == CursorState::Open;
        }

        /// <summary>
        /// Check if cursor is positioned on a record.
        /// </summary>
        /// <returns>true if cursor is positioned on a record</returns>
        constexpr bool IsPositioned( ) const noexcept
        {
            return state_ == CursorState::Positioned || state_ == CursorState::Loaded;
        }

        constexpr bool IsLoaded( ) const noexcept
        {
            return state_ == CursorState::Loaded;
        }


        ~Cursor( )
        {
            if ( cursor_ )
            {
                mdb_cursor_close( cursor_ );
            }
        }


        void Close( )
        {
            if ( cursor_ )
            {
                mdb_cursor_close( cursor_ );
                cursor_ = nullptr;
                state_ = CursorState::Closed;
            }
        }

        void swap( Cursor& other )
        {
            std::swap( cursor_, other.cursor_ );
            std::swap( transaction_, other.transaction_ );
            std::swap( state_, other.state_ );
            std::swap( key_, other.key_ );
            std::swap( value_, other.value_ );
        }

        Transaction* Transaction( ) const noexcept
        {
            return transaction_;
        }
    private:
        void RequireOpen( ) const
        {
            if ( IsOpen( ) == false )
            {
                throw Exception( "Cursor is not open" );
            }
        }
        void RequireValidKey( ) const
        {
            if ( key_.mv_size == 0 || key_.mv_data == nullptr )
            {
                throw Exception( "Invalid key" );
            }
        }
        void RequireValidValue( ) const
        {
            if ( value_.mv_size == 0 || value_.mv_data == nullptr )
            {
                throw Exception( "Invalid value" );
            }
        }
        void RequirePositioned( ) const
        {
            if ( IsPositioned() == false )
            {
                throw Exception( "Not positioned" );
            }
        }

        void RequireLoaded( ) const
        {
            if ( IsLoaded( ) == false )
            {
                throw Exception( "Not loaded" );
            }
        }


        void ResetKey( ) noexcept
        {
            key_.mv_size = 0;
            key_.mv_data = nullptr;
        }
        void ResetValue( ) noexcept
        {
            value_.mv_size = 0;
            value_.mv_data = nullptr;
        }
        void ResetKeyAndValue( ) noexcept
        {
            ResetKey( );
            ResetValue( );
        }

    private:
        constexpr bool IsLoadingOperation( const MDB_cursor_op operation ) const noexcept
        {
            if ( operation == MDB_GET_BOTH ||
                operation == MDB_GET_BOTH_RANGE || 
                operation == MDB_GET_CURRENT ||
                operation == MDB_GET_MULTIPLE )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        void Load( )
        {
            RequirePositioned( );
            Exec( MDB_GET_CURRENT );
        }
    public:
        int Exec( MDB_cursor_op operation )
        {
            LMDB::Value* valuePtr = nullptr;
            RequireOpen( );
            if ( IsLoadingOperation( operation ) )
            {
                valuePtr = &value_;
            }
            auto rc = mdb_cursor_get( cursor_, &key_, &value_, operation );
            state_ = rc == MDB_SUCCESS ? ( valuePtr != nullptr ? CursorState::Loaded : CursorState::Positioned ) : CursorState::Open;
            if ( rc != MDB_SUCCESS )
            {
                ResetKeyAndValue( );
                if ( rc != MDB_NOTFOUND )
                {
                    if ( ( rc == EINVAL && operation == MDB_GET_CURRENT ) )
                    {
                        rc = 0;
                    }
                }
            }
            return rc;
        }
        int ExecAndLoad( MDB_cursor_op op )
        {
            RequireOpen( );
            auto rc = mdb_cursor_get( cursor_, &key_, &value_, op );
            state_ = rc == MDB_SUCCESS ? CursorState::Positioned : CursorState::Open;
            if ( rc != MDB_SUCCESS )
            {
                ResetKeyAndValue( );
                if ( rc != MDB_NOTFOUND )
                {
                    if ( ( rc == EINVAL && op == MDB_GET_CURRENT ) )
                    {
                        rc = 0;
                    }
                }
            }
            return rc;
        }

    public:

        /// <summary>
        /// Get the current key
        /// </summary>
        /// <returns>current key</returns>
        __forceinline const LMDB::Value& Key( ) const noexcept
        {
            return key_;
        }
        template<typename T>
        __forceinline const T& Key( ) const
        {
#ifdef _DEBUG
            if ( key_.mv_size )
            {
                return *( (const T*)key_.mv_data );
            }
            throw Exception( "Key not valid" );
#else
            return *( (const T*)key_.mv_data );
#endif
        }

        /// <summary>
        /// Position cursor at the specified key.
        /// </summary>
        /// <param name="key">key value</param>
        /// <returns>true if the a record was found</returns>
        bool SetKey( const LMDB::Value& key )
        {
            key_ = key;
            RequireValidKey( );
            Exec( MDB_SET_KEY );
            return IsPositioned( );
        }

        /// <summary>
        /// Position cursor at the specified key and load value.
        /// </summary>
        /// <param name="key">key value</param>
        /// <returns>true if the a record was found</returns>
        bool SetKeyAndLoad( const LMDB::Value& key )
        {
            key_ = key;
            RequireValidKey( );
            ExecAndLoad( MDB_SET_KEY );
            return IsPositioned( );
        }


        __forceinline const LMDB::Value& Value( ) noexcept
        {
            if ( IsLoaded( ) )
            {
                return value_;
            }
            else
            {
                Load( );
                return value_;
            }
        }

        template<typename T>
        __forceinline const T& Value( )
        {
            if ( IsLoaded( ) )
            {
#ifdef _DEBUG
                if ( value_.mv_size )
                {
                    return *( (const T*)value_.mv_data );
                }
                throw Exception( "Value not valid" );
#else
                return *( (const T*)value_.mv_data );
#endif
            }
            else
            {
                Load( );
#ifdef _DEBUG
                if ( value_.mv_size )
                {
                    return *( (const T*)value_.mv_data );
                }
                throw Exception( "Value not valid" );
#else
                return *( (const T*)value_.mv_data );
#endif
            }
        }

        /// <summary>
        /// Set the value at the current position of the cursor
        /// </summary>
        /// <param name="value"></param>
        /// <param name="writeFlags"></param>
        /// <returns></returns>
        bool SetValue( const LMDB::Value& value, WriteFlags writeFlags = WriteFlags::None )
        {
            return Write( value, writeFlags );
        }

        /// <summary>
        /// stores key/data pair into the database
        /// </summary>
        /// <param name="key">The key operated on</param>
        /// <param name="value">The data operated on</param>
        /// <param name="writeFlags">Options for this operation</param>
        /// <returns>return true if this was a new key in the database</returns>
        bool Write( const LMDB::Value& key, const LMDB::Value& value, WriteFlags writeFlags = WriteFlags::None )
        {
            key_ = key;
            value_ = value;
            RequireValidKey( );
            RequireValidValue( );
            auto rc = mdb_cursor_put( cursor_, &key_, &value_, static_cast<unsigned int>( writeFlags ) );
            if ( rc )
            {
                if ( rc == MDB_KEYEXIST )
                {
                    return false;
                }
                Internal::ThrowException( __func__, rc );
            }
            return true;
        }

        template<ValueType T1, ValueType T2>
        bool Write( const T1& key, const T2& value, WriteFlags writeFlags = WriteFlags::None )
        {
            LMDB::Value kv( key );
            LMDB::Value dv( value );
            return Write( kv, dv, writeFlags );
        }


        bool Write( const LMDB::Value& value, WriteFlags writeFlags = WriteFlags::None )
        {
            value_ = value;
            RequireValidKey( );
            RequireValidValue( );
            writeFlags |= WriteFlags::Current;
            auto rc = mdb_cursor_put( cursor_, &key_, &value_, static_cast<unsigned int>( writeFlags ) );
            if ( rc )
            {
                if ( rc == MDB_KEYEXIST )
                {
                    return false;
                }
                Internal::ThrowException( __func__, rc );
            }
            return true;
        }

        template<ValueType T>
        bool Write( const T& value, WriteFlags writeFlags = WriteFlags::None )
        {
            LMDB::Value dv( value );
            return Write( dv, writeFlags );
        }


        /// <summary>
        /// Position at first key greater than or equal to the specified key.
        /// </summary>
        /// <param name="key">key value</param>
        /// <returns>true if positoned on a record, false if no record satisfied the search</returns>
        bool Search( const LMDB::Value& key )
        {
            key_ = key;
            RequireValidKey( );
            Exec( MDB_SET_RANGE );
            return IsPositioned( );
        }
        template<ValueType T>
        bool Search( const T& key )
        {
            LMDB::Value kv( key );
            return Search( kv );
        }

        /// <summary>
        /// Position at first key greater than or equal to the specified key and load value.
        /// </summary>
        /// <param name="key">key value</param>
        /// <returns>true if positoned on a record, false if no record satisfied the search</returns>
        bool SearchAndLoad( const LMDB::Value& key )
        {
            key_ = key;
            RequireValidKey( );
            ExecAndLoad( MDB_SET_RANGE );
            return IsPositioned( );
        }
        template<ValueType T>
        bool SearchAndLoad( const T& key )
        {
            LMDB::Value kv( key );
            return SearchAndLoad( kv );
        }


        bool MoveTo( const LMDB::Value& key )
        {
            key_ = key;
            RequireValidKey( );
            Exec( MDB_SET );
            return IsPositioned( );
        }
        template<ValueType T>
        bool MoveTo(const T& key )
        {
            LMDB::Value kv( key );
            return MoveTo( kv );
        }

        bool MoveToAndLoad( const LMDB::Value& key )
        {
            key_ = key;
            RequireValidKey( );
            ExecAndLoad( MDB_SET );
            return IsPositioned( );
        }
        template<ValueType T>
        bool MoveToAndLoad( const T& key )
        {
            LMDB::Value kv( key );
            return MoveToAndLoad( kv );
        }



        /// <summary>
        /// Position at first key/data item
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MoveFirst( )
        {
            Exec( MDB_FIRST );
            return IsPositioned( );
        }

        /// <summary>
        /// Position at first data item of current key. Only for DatabaseFlags::DupSort
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MoveFirstDup( )
        {
            Exec( MDB_FIRST_DUP );
            return IsPositioned( );
        }
        /// <summary>
        /// Position at next data item
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MoveNext( )
        {
            Exec( MDB_NEXT );
            return IsPositioned( );
        }

        /// <summary>
        /// Position at next data item of current key. Only for DatabaseFlags::DupSort
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MoveNextDup( )
        {
            Exec( MDB_NEXT_DUP );
            return IsPositioned( );
        }
        /// <summary>
        /// Position at first data item of next key
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MoveNextNoDup( )
        {
            Exec( MDB_NEXT_NODUP );
            return IsPositioned( );
        }
        /// <summary>
        /// Return up to a page of duplicate data items
        /// from next cursor position.Move cursor to prepare
        /// for MoveNextMultiple( ).Only for DatabaseFlags::DupFixed
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MoveNextMultiple( )
        {
            
            Exec( MDB_NEXT_MULTIPLE );
            return IsPositioned( );
        }
        /// <summary>
        /// Position at last key/data item
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MoveLast( )
        {
            Exec( MDB_LAST );
            return IsPositioned( );
        }
        /// <summary>
        /// Position at last data item of current key. Only for DatabaseFlags::DupSort
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MoveLastDup( )
        {
            Exec( MDB_LAST_DUP );
            return IsPositioned( );
        }

        /// <summary>
        /// Position at previous data item
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MovePrevious( )
        {
            Exec( MDB_PREV );
            return IsPositioned( );
        }

        /// <summary>
        /// Position at previous data item of current key. Only for DatabaseFlags::DupSort
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MovePreviousDup( )
        {
            Exec( MDB_PREV_DUP );
            return IsPositioned( );
        }
        /// <summary>
        /// Position at last data item of previous key
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MovePreviousNoDup( )
        {
            Exec( MDB_PREV_NODUP );
            return IsPositioned( );
        }
        /// <summary>
        /// Position at previous page and return up to
        ////a page of duplicate data items.Only for DatabaseFlags::DupFixed
        /// </summary>
        /// <returns>true if positoned on a record</returns>
        bool MovePreviousMultiple( )
        {
            Exec( MDB_PREV_MULTIPLE );
            return IsPositioned( );
        }

        /// <summary>
        /// Delete current key/data pair
        /// </summary>
        /// <remarks>
        /// This function deletes the key/data pair to which the cursor refers.
        /// This does not invalidate the cursor, so operations such as MoveNext()
        /// can still be used on it.
        /// </remarks>
        /// <param name="noDupData">delete all of the data items for the current key.
        /// This flag may only be specified if the database was opened with DatabaseFlags::DupSort</param>
        void Delete( bool noDupData = false )
        {
            auto rc = mdb_cursor_del( cursor_, noDupData ? MDB_NODUPDATA : 0 );
            if ( rc )
            {
                Internal::ThrowException( __func__, rc );
            }
        }

        LMDB::Database Database( ) const;
    };

    template <ValueType KT, ValueType VT>
    class TypedCursor : public Cursor
    {
    public:
        using Base = Cursor;
        using KeyType = KT;
        using ValueType = VT;
    public:
        constexpr TypedCursor( ) noexcept
            : Base( )
        {
        }

        constexpr explicit TypedCursor( LMDB::Transaction* transaction, MDB_cursor* cursor, CursorState state ) noexcept
            : Base( transaction, cursor, state )
        {
        }

        __forceinline const KeyType& Key( ) const
#ifndef _DEBUG
            noexcept
#endif
        {
            return Base::Key<KeyType>( );
        }

        bool SetKey( const KeyType& key )
        {
            return Base::SetKey( key );
        }


        __forceinline const ValueType& Value( )
#ifndef _DEBUG
            noexcept
#endif
        {
            return Base::Value<ValueType>( );
        }

        bool SetValue( const ValueType& Value, WriteFlags writeFlags = WriteFlags::None )
        {
            return Base::SetValue( Value, writeFlags );
        }

        bool Write( const ValueType& Value, WriteFlags writeFlags = WriteFlags::None )
        {
            return Base::Write( Value, writeFlags );
        }

        bool Write( const KeyType& key, const ValueType& Value, WriteFlags writeFlags = WriteFlags::None )
        {
            return Base::Write( key, Value, writeFlags );
        }

        bool Search( const KeyType& key )
        {
            return Base::Search( key );
        }

        bool MoveTo( const KeyType& key )
        {
            return Base::MoveTo( key );
        }
    };


    class Transaction;
    class Database 
    {
        MDB_dbi dbi_;
    public:
        constexpr Database( ) noexcept
            : dbi_(0)
        {
        }

        constexpr explicit Database( MDB_dbi dbi ) noexcept
            : dbi_( dbi )
        {
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return dbi_ != 0;
        }

        constexpr MDB_dbi Value( ) const noexcept
        {
            return dbi_;
        }
    };
    using Table = Database;

    inline LMDB::Database Cursor::Database( ) const
    {
        auto db = mdb_cursor_dbi( cursor_ );
        return LMDB::Database( db );
    }



    class Environment;
    class Transaction 
    {
        Environment* environment_;
        MDB_txn* txn_;
        bool ownsHandle_;
    public:
        constexpr Transaction( ) noexcept
            : environment_(nullptr), txn_(nullptr), ownsHandle_(false)
        {
        }

        constexpr explicit Transaction( Environment* environment, MDB_txn* txn, bool ownsHandle = true ) noexcept
            : environment_( environment ), txn_( txn ), ownsHandle_( ownsHandle )
        {
        }


        Transaction( const Transaction& other ) = delete;
        Transaction( Transaction&& other ) noexcept
            : environment_( other.environment_ ), txn_( other.txn_ ), ownsHandle_( other.ownsHandle_ )
        {
            other.environment_ = nullptr;
            other.txn_ = nullptr; 
            other.ownsHandle_ = false;
        }

        ~Transaction( )
        {
            Close( );
        }


        Transaction& operator = ( const Transaction& other ) = delete;
        Transaction& operator = ( Transaction&& other ) noexcept
        {
            if ( this != &other )
            {
                swap( other );
            }
            return *this;
        }


        constexpr explicit operator bool( ) const noexcept
        {
            return txn_ != nullptr;
        }

        void swap( Transaction& other ) noexcept
        {
            std::swap( environment_, other.environment_ );
            std::swap( txn_, other.txn_ );
            std::swap( ownsHandle_, other.ownsHandle_ );
        }

        constexpr MDB_txn* Value( ) const noexcept
        {
            return txn_;
        }

        /// <summary>
        /// This returns the identifier associated with this transaction.
        /// </summary>
        /// <remarks>
        /// For read-only transactions, this corresponds to the id of the 
        /// snapshot being read. Concurrent readers will frequently have the same 
        /// transaction ID
        /// </remarks>
        /// <returns>the identifier associated with this transaction</returns>
        size_t Id( ) const noexcept
        {
            return mdb_txn_id( txn_ );
        }


        void Close( ) noexcept
        {
            Abort( );
        }

        /// <summary>
        /// Abandon all the operations of the transaction instead of saving them.
        /// </summary>
        /// <remarks>
        /// The transaction handle is freed, and if this was a write transaction 
        /// then any open cursor will also be freed.
        /// If this was a read-only transaction, then the cursors can be renewed.
        /// In either case the cursors will now be unusable.
        /// </remarks>
        void Abort( ) noexcept
        {
            if ( txn_ )
            {
                mdb_txn_abort( Value( ) );
                txn_ = nullptr;
            }
        }

        /// <summary>
        /// Commit all the operations of a transaction into the database.
        /// </summary>
        /// <remarks>
        /// The transaction handle is freed. It and its cursors must not be reused.
        /// </remarks>
        void Commit( )
        {
            auto rc = mdb_txn_commit( txn_ );
            txn_ = nullptr;
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
        }

        /// <summary>
        /// Abort the transaction like Abort, but keeps the
        /// transaction handle.
        /// </summary>
        /// <returns></returns>
        void Reset( ) const noexcept
        {
            if ( txn_ )
            {
                mdb_txn_reset( Value( ) );
            }
        }

        /// <summary>
        /// Renew a read-only transaction.
        /// </summary>
        /// <remarks>
        /// This acquires a new reader lock for a transaction handle that had been
        /// released by Reset. It must be called before a reset transaction can be
        /// reused.
        /// </remarks>
        void Renew( ) const
        {
            auto rc = mdb_txn_renew( txn_ );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
        }

        /// <summary>
        /// Starts a nested transaction
        /// </summary>
        /// <param name="transactionFlags"></param>
        /// <returns></returns>
        Transaction BeginTransaction( TransactionFlags transactionFlags = TransactionFlags::None ) const;


        Database OpenDatabase( const char* name, DatabaseFlags databaseFlags = DatabaseFlags::None ) const
        {
            MDB_dbi dbi = 0;
            auto rc = mdb_dbi_open( Value( ), name, static_cast<unsigned int>( databaseFlags ),&dbi );
            if ( rc != MDB_SUCCESS )
            {
                if ( rc == MDB_NOTFOUND )
                {
                    return Database( );
                }
                Internal::ThrowException( __func__, rc );
            }
            return Database( dbi );
        }

        Database OpenDatabase( DatabaseFlags databaseFlags = DatabaseFlags::None ) const
        {
            return OpenDatabase( nullptr, databaseFlags );
        }


        /// <summary>
        /// Empties the specified database
        /// </summary>
        /// <param name="database">database to clear</param>
        void Truncate( const Database& database ) const
        {
            auto rc = mdb_drop( Value( ), database.Value( ), 0 );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
        }
        /// <summary>
        /// Deletes and closes the specified database
        /// </summary>
        /// <param name="database">database to delete</param>
        void Drop( const Database& database ) const
        {
            auto rc = mdb_drop( Value( ), database.Value( ), 1 );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
        }


        /// <summary>
        /// Store items into a database
        /// </summary>
        /// <param name="database">the target database</param>
        /// <param name="key">the key to store in the database</param>
        /// <param name="value">the value to store in the database</param>
        /// <param name="writeFlags">Options for this operation</param>
        /// <returns></returns>
        int Write( const Database& database, const MDB_val& key, const MDB_val& value, WriteFlags writeFlags = WriteFlags::None ) const
        {
            return mdb_put( Value( ), database.Value(), const_cast<MDB_val*>( &key ), const_cast<MDB_val*>( &value ), static_cast<unsigned int>( writeFlags ) );
        }
        int Write( const Database& database, const LMDB::Value& key, const LMDB::Value& value, WriteFlags writeFlags = WriteFlags::None ) const
        {
            return Write( database, static_cast<const MDB_val&>( key ), static_cast<const MDB_val&>( value ), writeFlags );
        }

        template<ValueType KT, ValueType VT>
        int Write( const Database& database, const KT& key, const VT& value, WriteFlags writeFlags = WriteFlags::None ) const
        {
            LMDB::Value kv( key );
            LMDB::Value dv( value );
            return Write( database, kv, dv, writeFlags );
        }



        Cursor OpenCursor( const Database& database ) const 
        {
            MDB_cursor* cursor = nullptr;
            auto rc = mdb_cursor_open( Value(), database.Value(), &cursor );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
            return Cursor( const_cast<Transaction*>(this), cursor,CursorState::Open );
        }

        template<ValueType KT, ValueType VT>
        TypedCursor<KT, VT> OpenCursor( const Database& database ) const
        {
            MDB_cursor* cursor = nullptr;
            auto rc = mdb_cursor_open( Value( ), database.Value( ), &cursor );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
            return TypedCursor<KT, VT>( const_cast<Transaction*>( this ), cursor, CursorState::Open );
        }

        /// <summary>
        /// Set a custom key comparison function for a database.
        /// </summary>
        /// <remarks>
        /// The comparison function is called whenever it is necessary to compare a
        /// key specified by the application with a key currently stored in the database.
        /// If no comparison function is specified, and no special key flags were specified
        /// with OpenDatabase, the keys are compared lexically, with shorter keys collating
        /// before longer keys.
        /// This function must be called before any data access functions are used,
        /// otherwise data corruption may occur. The same comparison function must be used by every
        /// program accessing the database, every time the database is used.
        /// </remarks>
        /// <param name="database">A database handle</param>
        /// <param name="cmp">The compare function</param>
        void SetCompare( const Database& database, MDB_cmp_func* cmp ) const
        {
            auto rc = mdb_set_compare( Value( ), database.Value( ), cmp );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
        }

        /// <summary>
        /// Set a custom data comparison function for a database opened 
        /// with the DatabaseFlags::DupSort flag.
        /// </summary>
        /// <remarks>
        /// This comparison function is called whenever it is necessary to compare a data
        /// item specified by the application with a data item currently stored in the database.
        /// This function only takes effect if the database was opened with the DatabaseFlags::DupSort flag.
        /// If no comparison function is specified, and no special key flags were specified
        /// for OpenDatabase the data items are compared lexically, with shorter items collating
        /// before longer items.
        /// This function must be called before any data access functions are used,
        /// otherwise data corruption may occur. The same comparison function must be used by every
        /// program accessing the database, every time the database is used.
        /// </remarks>
        /// <param name="database">A database handle</param>
        /// <param name="cmp">The compare function</param>
        void SetDupSort( const Database& database, MDB_cmp_func* cmp ) const
        {
            auto rc = mdb_set_dupsort( Value( ), database.Value( ), cmp );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
        }


        bool Delete( const Database& database, const MDB_val& key ) const
        {
            auto rc = mdb_del( txn_, database.Value( ), const_cast<MDB_val*>(&key), nullptr );
            if ( rc != MDB_SUCCESS && rc != MDB_NOTFOUND )
            {
                Internal::ThrowException( __func__, rc );
            }
            return rc != MDB_NOTFOUND;
        }
        template<ValueType KT>
        bool Delete( const Database& database, const KT& key ) const
        {
            LMDB::Value kv( key );
            return Delete( database, kv );
        }

        bool Delete( const Database& database, const MDB_val& key, const MDB_val& value ) const
        {
            auto rc = mdb_del( txn_, database.Value( ), const_cast<MDB_val*>( &key ), const_cast<MDB_val*>( &value ) );
            if ( rc != MDB_SUCCESS && rc != MDB_NOTFOUND )
            {
                Internal::ThrowException( __func__, rc );
            }
            return rc != MDB_NOTFOUND;
        }

        template<ValueType KT, ValueType VT>
        bool Delete( const Database& database, const KT& key, const VT& value ) const
        {
            LMDB::Value kv( key );
            LMDB::Value dv( value );
            return Delete( database, kv, dv );
        }



    };



    class Environment 
    {
        MDB_env* env_;
        bool ownsHandle_;
    public:
        static constexpr size_t DefaultMemoryMapSize = 10485760;

        constexpr Environment( ) noexcept
            : env_(nullptr), ownsHandle_(false)
        {
        }

        constexpr explicit Environment( MDB_env* env, bool ownsHandle = true ) noexcept
            : env_( env ), ownsHandle_( ownsHandle )
        {
        }

        

        /// <summary>
        /// Create and open an LMDB environment handle
        /// </summary>
        /// <param name="path">
        /// The directory in which the database files reside. 
        /// This directory must already existand be writable.</param>
        /// <param name="newMemoryMapSize">The size of the memory map to use for this environment</param>
        /// <param name="maxDatabases">The maximum number of named databases for the environment.</param>
        /// <param name="environmentFlags"></param>
        /// <returns></returns>
        explicit Environment( const char* path, 
            size_t newMemoryMapSize = DefaultMemoryMapSize,
            unsigned int maxDatabases = 0, 
            EnvironmentFlags environmentFlags = EnvironmentFlags::WriteMemMap )
        {
            MDB_env* env = nullptr;
            auto rc = mdb_env_create( &env );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
            env_ = env;
            ownsHandle_ = true;
            if ( maxDatabases )
            {
                SetMaxDatabases( maxDatabases );
            }
            SetMapSize( newMemoryMapSize );
            try
            {
                Open( path, environmentFlags );
            }
            catch ( ... )
            {
                mdb_env_close( env_ );
                env_ = nullptr;
                ownsHandle_ = false;
                throw;
            }
        }

        explicit Environment( const AnsiString& path, size_t newMemoryMapSize = DefaultMemoryMapSize, unsigned int maxDatabases = 0, EnvironmentFlags environmentFlags = EnvironmentFlags::WriteMemMap ) noexcept
            : Environment( path.c_str( ), newMemoryMapSize, maxDatabases, environmentFlags )
        {
        }


        Environment( const Environment& other ) = delete;
        Environment( Environment&& other ) noexcept
            : env_( other.env_ ), ownsHandle_( other.ownsHandle_ )
        {
            other.env_ = nullptr;
            other.ownsHandle_ = false;
        }


        ~Environment( )
        {
            Close( );
        }


        Environment& operator = ( const Environment& other ) = delete;
        Environment& operator = ( Environment&& other ) noexcept
        {
            if ( this != &other )
            {
                swap( other );
            }
            return *this;
        }

        constexpr void swap( Environment& other ) noexcept
        {
            std::swap( env_, other.env_ );
            std::swap( ownsHandle_, other.ownsHandle_ );
        }


        constexpr explicit operator bool( ) const noexcept
        {
            return env_ != nullptr;
        }


        constexpr MDB_env* Value( ) const noexcept
        {
            return env_;
        }

        static Environment Create( )
        {
            MDB_env* result = nullptr;
            auto rc = mdb_env_create( &result );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
            return Environment(result,true);
        }




        void SetMapSize( size_t newMemoryMapSize ) const
        {
            auto rc = mdb_env_set_mapsize( Value( ), newMemoryMapSize );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
        }

        /// <summary>
        /// Set the maximum number of named databases for the environment.
        /// </summary>
        /// <param name="maxDatabases">the new maximum number of named databases</param>
        void SetMaxDatabases( unsigned int maxDatabases ) const
        {
            auto rc = mdb_env_set_maxdbs( Value( ), maxDatabases );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
        }


        /// <summary>
        /// Set the maximum number of threads/reader slots for the environment.
        /// </summary>
        /// <remarks>
        /// This defines the number of slots in the lock table that is used to 
        /// track readers in the the environment. The default is 126.
        /// Starting a read-only transaction normally ties a lock table slot to the
        /// current thread until the environment closes or the thread exits. If
        /// EnvironmentFlags::NoTLS is in use, BeginTransaction(...) instead ties 
        /// the slot to the transaction handle, until it or the environment is 
        /// destroyed.
        /// </remarks>
        /// <param name="readers">the new maximum number of threads/reader slots</param>
        void SetMaxReaders( unsigned int readers ) const
        {   
            auto rc = mdb_env_set_maxreaders( Value( ), readers );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
        }

        /// <summary>
        /// Get the maximum number of threads/reader slots for the environment.
        /// </summary>
        /// <returns>the maximum number of threads/reader slots</returns>
        unsigned int MaxReaders( ) const
        {
            unsigned int readers = 0;
            auto rc = mdb_env_get_maxreaders( Value( ), &readers );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
            return readers;
        }

        /// <summary>
        /// Open an environment handle.
        /// </summary>
        /// <param name="path">
        /// The directory in which the database files reside. 
        /// This directory must already exist and be writable.</param>
        /// <param name="environmentFlags">The options for this environment. </param>
        void Open( const char* path, EnvironmentFlags environmentFlags = EnvironmentFlags::WriteMemMap ) const
        {
            auto rc = mdb_env_open( Value(), path, static_cast<unsigned int>( environmentFlags ), 0 );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
        }


        /// <summary>
        /// Close the environment and release the memory map.
        /// </summary>
        /// <remarks>
        /// Only a single thread may call this function. All transactions, 
        /// and cursors must be closed before calling this function.
        /// </remarks>
        void Close( )
        {
            if ( env_ )
            {
                mdb_env_close( env_ );
                env_ = nullptr;
                ownsHandle_ = false;
            }
        }

        /// <summary>
        /// Create a new toplevel transaction for use with the environment.
        /// </summary>
        /// <remarks>
        /// The transaction may be discarded using Commit(), Close()/Abort() or Reset().
        /// A transaction and its cursors must only be used by a single thread, 
        /// and a thread can only have a single top-level transaction at a time.
        /// This does not apply to read-only transactions if the environment
        /// was opened with EnvironmentFlags::NoTLS.
        /// <remarks>
        /// <param name="transactionFlags"></param>
        /// <returns></returns>
        Transaction BeginTransaction( TransactionFlags transactionFlags = TransactionFlags::None ) const
        {
            MDB_txn* txn = nullptr;
            auto rc = mdb_txn_begin( Value( ), nullptr, static_cast<unsigned int>( transactionFlags ), &txn );
            if ( rc != MDB_SUCCESS )
            {
                Internal::ThrowException( __func__, rc );
            }
            return Transaction( const_cast<Environment*>(this), txn );
        }

        /// <summary>
        /// Close a database handle. Normally unnecessary.
        /// </summary>
        /// <remarks>
        /// Database handles should only be closed by a single thread, 
        /// and only if no other threads are going to reference the 
        /// database handle or one of its cursors any further. 
        /// Closing a database with an existing write transaction can 
        /// lead to database corruption.
        /// </remarks>
        /// <param name="database"></param>
        void CloseDatabase( Database& database ) const
        {
            if ( database.Value( ) )
            {
                mdb_dbi_close( Value( ), database.Value( ) );
            }
        }


        /// <summary>
        /// Return the LMDB library version information.
        /// </summary>
        /// <param name="major">major if non-NULL, the library major version number is copied here</param>
        /// <param name="minor">minor if non-NULL, the library minor version number is copied here</param>
        /// <param name="patch">patch if non-NULL, the library patch version number is copied here</param>
        /// <returns>The library version as a string</returns>
        static const char* Version( int* major, int* minor, int* patch )
        {
            return mdb_version( major, minor, patch );
        }

        /// <summary>
        /// Return a string describing a given error code.
        /// </summary>
        /// <param name="err">The error code</param>
        /// <returns>The description of the error</returns>
        static const char* StrError( int err )
        {
            return mdb_strerror( err );
        }
    };
                 
    inline Transaction Transaction::BeginTransaction( TransactionFlags transactionFlags ) const
    {
        MDB_txn* nestedTxn = nullptr;
        auto rc = mdb_txn_begin( environment_->Value( ), txn_, static_cast<unsigned int>( transactionFlags ), &nestedTxn );
        if ( rc != MDB_SUCCESS )
        {
            Internal::ThrowException( __func__, rc );
        }
        return Transaction( environment_, nestedTxn );
    }
}

namespace std
{
    template<> struct hash<Harlinn::Common::Core::LMDB::Database>
    {
        std::size_t operator()( const Harlinn::Common::Core::LMDB::Database& database ) const noexcept
        {
            static std::hash<unsigned int> hashCalc;
            return hashCalc( database.Value( ) );
        }
    };
}


#endif
