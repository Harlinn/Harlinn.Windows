#pragma once
#ifndef __HCCLMDBEX_H__
#define __HCCLMDBEX_H__
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

#include <HCCLMDB.h>
#include <HCCPersistent.h>
#include <HCCSync.h>

namespace Harlinn::Common::Core::LMDBEx
{
    class TableBase;
    class IndexInfo;
    class Index;
    template<typename PrimaryKeyT>
    class HashIndexInfo;
    template<typename PrimaryKeyT>
    class HashIndex;
    class TableInfo;
    class Table;
    class Session;
    class DatabaseBase;
    template <typename DatabaseT, typename SessionT>
    class SessionReference;

    using KeyFormat = Vector<Byte>;
    using ValueFormat = Vector<Byte>;


    /// <summary>
    /// TableInfoBase
    /// </summary>
    class TableInfoBase
    {
        AnsiString name_;
        KeyFormat keyFormat_;
        ValueFormat valueFormat_;
        LMDB::Database database_;
    public:
        TableInfoBase( const AnsiString& name, const LMDBEx::KeyFormat& keyFormat, const LMDBEx::ValueFormat& valueFormat )
            : name_( name ), keyFormat_( keyFormat ), valueFormat_( valueFormat )
        {
        }

        template<typename KFT, typename VFT>
            requires IsCoreTuple<KFT> && IsCoreTuple<VFT>
        TableInfoBase( const AnsiString& name, const KFT& keyFormat, const VFT& valueFormat )
            : name_( name ), 
              keyFormat_( reinterpret_cast<const Byte*>(&keyFormat), reinterpret_cast<const Byte*>( &keyFormat ) + sizeof(KFT) ),
              valueFormat_( reinterpret_cast<const Byte*>( &valueFormat ), reinterpret_cast<const Byte*>( &valueFormat ) + sizeof( VFT ) )
        { }

        virtual ~TableInfoBase( ) = default;

        bool HasIntegerKey( ) const
        {
            return Persistent::IsIntegerBasicTypeDescriptor( keyFormat_ );
        }

        virtual LMDB::DatabaseFlags DatabaseFlags( ) const
        {
            LMDB::DatabaseFlags result = LMDB::DatabaseFlags::None;
            if ( HasIntegerKey( ) )
            {
                result |= LMDB::DatabaseFlags::IntegerKey;
            }
            return result;
        }


        virtual void Initialize( LMDB::Transaction& transaction )
        {
            auto databaseFlags = this->DatabaseFlags( );
            database_ = transaction.OpenDatabase( name_.c_str( ), databaseFlags );
            if ( !database_.Value( ) )
            {
                databaseFlags |= LMDB::DatabaseFlags::Create;
                database_ = transaction.OpenDatabase( name_.c_str( ), databaseFlags );
            }
        }

        const AnsiString& Name( ) const noexcept
        {
            return name_;
        }
        const LMDBEx::KeyFormat& KeyFormat( ) const noexcept
        {
            return keyFormat_;
        }
        const LMDBEx::ValueFormat& ValueFormat( ) const noexcept
        {
            return valueFormat_;
        }
        LMDB::Database Database( ) const noexcept
        {
            return database_;
        }
    };

    /// <summary>
    /// TableBase
    /// </summary>
    class TableBase
    {
    protected:
        Session& session_;
        TableInfoBase* info_;
        LMDB::Database database_;
        LMDB::Cursor cursor_;
    protected:
        TableBase( Session& session, TableInfoBase* info )
            : session_( session ), info_( info ), database_( info->Database( ) )
        {
        }
        virtual ~TableBase( ) = default;
        LMDB::Transaction& Transaction( );
    public:
        LMDB::Cursor& Cursor( )
        {
            if ( cursor_.IsOpen( ) == false )
            {
                auto& transaction = Transaction( );
                cursor_ = transaction.OpenCursor( database_ );
            }
            return cursor_;
        }
        TableInfoBase* Info( ) const
        {
            return info_;
        }

    public:
        TableBase( const TableBase& other ) = delete;
        TableBase( TableBase&& other ) noexcept = delete;
        TableBase& operator = ( const TableBase& other ) = delete;
        TableBase& operator = ( TableBase&& other ) noexcept = delete;

        virtual void Reset( )
        {
            cursor_.Close( );
        }

        bool Search( const LMDB::Value& key )
        {
            auto& cursor = Cursor( );
            return cursor.Search( key );
        }
        template<LMDB::ValueType T>
        bool Search( const T& key )
        {
            LMDB::Value kv( key );
            return Search( kv );
        }

        bool MoveTo( const LMDB::Value& key )
        {
            auto& cursor = Cursor( );
            return cursor.MoveTo( key );
        }
        template<LMDB::ValueType T>
        bool MoveTo( const T& key )
        {
            LMDB::Value kv( key );
            return MoveTo( kv );
        }


        bool MoveFirst( )
        {
            auto& cursor = Cursor( );
            return cursor.MoveFirst( );
        }

        bool MoveFirstDup( )
        {
            auto& cursor = Cursor( );
            return cursor.MoveFirstDup( );
        }

        bool MoveNext( )
        {
            auto& cursor = Cursor( );
            return cursor.MoveNext( );
        }

        bool MoveNextDup( )
        {
            auto& cursor = Cursor( );
            return cursor.MoveNextDup( );
        }

        bool MoveNextNoDup( )
        {
            auto& cursor = Cursor( );
            return cursor.MoveNextNoDup( );
        }

        bool MoveNextMultiple( )
        {
            auto& cursor = Cursor( );
            return cursor.MoveNextMultiple( );
        }

        bool MoveLast( )
        {
            auto& cursor = Cursor( );
            return cursor.MoveLast( );
        }

        bool MoveLastDup( )
        {
            auto& cursor = Cursor( );
            return cursor.MoveLastDup( );
        }

        bool MovePrevious( )
        {
            auto& cursor = Cursor( );
            return cursor.MoveLastDup( );
        }
        bool MovePreviousDup( )
        {
            auto& cursor = Cursor( );
            return cursor.MovePreviousDup( );
        }

        bool MovePreviousNoDup( )
        {
            auto& cursor = Cursor( );
            return cursor.MovePreviousNoDup( );
        }

        bool MovePreviousMultiple( )
        {
            auto& cursor = Cursor( );
            return cursor.MovePreviousMultiple( );
        }

    };


    /// <summary>
    /// IndexInfo
    /// </summary>
    class IndexInfo : public TableInfoBase
    {
    public:
        using Base = TableInfoBase;

        IndexInfo( const AnsiString& name, const LMDBEx::KeyFormat& keyFormat, const LMDBEx::ValueFormat& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }

        template<typename KFT, typename VFT>
            requires IsCoreTuple<KFT> && IsCoreTuple<VFT>
        IndexInfo( const AnsiString& name, const KFT& keyFormat, const VFT& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }


        virtual std::unique_ptr<Index> CreateIndex( Session& session, Table& table );

    };

    /// <summary>
    /// Index
    /// </summary>
    class Index : public TableBase
    {
    public:
        using Base = TableBase;
    private:
        Table& table_;
    public:
        Index( Session& session, Table& table, IndexInfo* info )
            : Base( session, info ), table_( table )
        {
        }

        Table& Table( )
        {
            return table_;
        }

    };

    inline std::unique_ptr<Index> IndexInfo::CreateIndex( Session& session, Table& table )
    {
        return std::make_unique<Index>( session, table, this );
    }


    template<typename T>
    class KeyBuffer : public boost::container::small_vector<T, 4>
    {
    public:
        using Base = boost::container::small_vector<T, 4>;
        using value_type = typename Base::value_type;

        using Base::push_back;
        using Base::insert;
        using Base::erase;
        using Base::begin;
        using Base::end;
        using Base::clear;

        KeyBuffer( )
        {
        }

        KeyBuffer( void* buffer, size_t bufferSizeInBytes )
        {
            size_t count = bufferSizeInBytes / sizeof( value_type );
            const value_type* values = (const value_type*)buffer;
            for ( size_t i = 0; i < count; ++i )
            {
                push_back( values[i] );
            }
        }

        void Add( const value_type& value )
        {
            auto it = std::lower_bound( begin( ), end( ), value );
            if ( it != end( ) )
            {
                if ( *it != value )
                {
                    insert( it, value );
                }
            }
            else
            {
                push_back( value );
            }
        }
        bool Remove( const value_type& value )
        {
            auto it = std::lower_bound( begin( ), end( ), value );
            if ( it != end( ) )
            {
                erase( it );
                return true;
            }
            return false;
        }
        
        bool erase( const value_type& value )
        {
            return Remove( value );
        }
    };


    /// <summary>
    /// HashIndexInfo
    /// </summary>
    template<typename PrimaryKeyT>
    class HashIndexInfo : public IndexInfo
    {
    public:
        using Base = IndexInfo;

        HashIndexInfo( const AnsiString& name, LMDBEx::KeyFormat& keyFormat, const LMDBEx::ValueFormat& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }

        template<typename KFT, typename VFT>
            requires IsCoreTuple<KFT> && IsCoreTuple<VFT>
        HashIndexInfo( const AnsiString& name, const KFT& keyFormat, const VFT& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }

        virtual std::unique_ptr<Index> CreateIndex( Session& session, Table& table ) override;
    };

    /// <summary>
    /// HashIndex
    /// </summary>
    template<typename PrimaryKeyT>
    class HashIndex : public Index
    {
    public:
        using Base = Index;
        using PrimaryKeyType = PrimaryKeyT;
    private:
        KeyBuffer<PrimaryKeyType> referencedKeys_;
    public:

        HashIndex( Session& session, LMDBEx::Table& table, LMDBEx::IndexInfo* info )
            : Base( session, table, info )
        {
        }

        bool Find( UInt64 hashKey )
        {
            auto& cursor = Cursor( );
            LMDB::Value hashKeyValue( hashKey );
            return cursor.SetKey( hashKeyValue );
        }

        std::span<PrimaryKeyType> References( )
        {
            auto& cursor = Cursor( );
            LMDB::Value referencesValue = cursor.Value( );
            size_t count = referencesValue.mv_size / sizeof( PrimaryKeyType );
            return std::span<PrimaryKeyType>( (PrimaryKeyType*)referencesValue.mv_data, count );
        }

        bool Find( UInt64 hashKey, const Byte* encodedValue, size_t encodedSize );

        bool Add( UInt64 hashKey, const PrimaryKeyType& primaryKey )
        {
            auto& cursor = Cursor( );
            LMDB::Value hashKeyValue( hashKey );
            if ( cursor.SetKeyAndLoad( hashKeyValue ) )
            {
                LMDB::Value primaryKeysValue = cursor.Value( );
                size_t count = primaryKeysValue.mv_size / sizeof( PrimaryKeyType );
                if ( count )
                {
                    referencedKeys_.clear( );
                    const PrimaryKeyType* current = (const PrimaryKeyType*)primaryKeysValue.mv_data;
                    const PrimaryKeyType* end = current + count;
                    while ( current < end )
                    {
                        const PrimaryKeyType& value = *current;
                        if ( value == primaryKey )
                        {
                            return false;
                        }
                        referencedKeys_.emplace_back( value );
                        ++current;
                    }
                    auto it = std::ranges::lower_bound( referencedKeys_, primaryKey );
                    if ( it != referencedKeys_.end( ) )
                    {
                        referencedKeys_.insert( it, primaryKey );
                    }
                    else
                    {
                        referencedKeys_.emplace_back( primaryKey );
                    }
                    primaryKeysValue.mv_data = referencedKeys_.data( );
                    primaryKeysValue.mv_size = referencedKeys_.size( ) * sizeof( PrimaryKeyType );
                    cursor.Write( primaryKeysValue );
                    return true;
                }
            }
            LMDB::Value primaryKeyValue( primaryKey );
            cursor.Write( hashKeyValue, primaryKeyValue );
            return true;
        }

        bool Remove( UInt64 hashValue, const PrimaryKeyType& primaryKey )
        {
            auto& cursor = Cursor( );
            LMDB::Value hashKey( hashValue );
            if ( cursor.SetKeyAndLoad( hashKey ) )
            {
                LMDB::Value primaryKeysValue = cursor.Value( );
                size_t count = primaryKeysValue.mv_size / sizeof( PrimaryKeyType );
                if ( count )
                {
                    bool result = false;
                    referencedKeys_.clear( );
                    const PrimaryKeyType* current = (const PrimaryKeyType*)primaryKeysValue.mv_data;
                    const PrimaryKeyType* end = current + count;
                    while ( current < end )
                    {
                        const PrimaryKeyType& value = *current;
                        if ( value != primaryKey )
                        {
                            referencedKeys_.emplace_back( value );
                        }
                        else
                        {
                            result = true;
                        }
                        ++current;
                    }
                    if ( result )
                    {
                        if ( referencedKeys_.size( ) )
                        {
                            primaryKeysValue.mv_data = referencedKeys_.data( );
                            primaryKeysValue.mv_size = referencedKeys_.size( ) * sizeof( PrimaryKeyType );
                            cursor.Write( primaryKeysValue );
                        }
                        else
                        {
                            cursor.Delete( );
                        }
                    }
                    return result;
                }
                else
                {
                    cursor.Delete( );
                }
            }
            return false;
        }
    };

    template<typename PrimaryKeyT>
    inline std::unique_ptr<Index> HashIndexInfo<PrimaryKeyT>::CreateIndex( Session& session, Table& table )
    {
        return std::make_unique<HashIndex<PrimaryKeyT>>( session, table, this );
    }

    /// <summary>
    /// TableInfo
    /// </summary>
    class TableInfo : public TableInfoBase
    {
        std::unordered_map<AnsiStringView, IndexInfo*> indexes_;
    public:
        using Base = TableInfoBase;

        TableInfo( const AnsiString& name, const LMDBEx::KeyFormat& keyFormat, const LMDBEx::ValueFormat& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }

        template<typename KFT, typename VFT>
            requires IsCoreTuple<KFT> && IsCoreTuple<VFT>
        TableInfo( const AnsiString& name, const KFT& keyFormat, const VFT& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }

        virtual std::unique_ptr<Table> CreateTable( Session& session );

        const std::unordered_map<AnsiStringView, IndexInfo*>& Indexes( ) const
        {
            return indexes_;
        }

        void Add( IndexInfo* index )
        {
            AnsiStringView name = index->Name( );
            indexes_.emplace( name, index );
        }

        virtual void Initialize( LMDB::Transaction& transaction ) override
        {
            Base::Initialize( transaction );
            for ( auto& entry : indexes_ )
            {
                entry.second->Initialize( transaction );
            }
        }

    };

    /// <summary>
    /// Table
    /// </summary>
    class Table : public TableBase
    {
    public:
        using Base = TableBase;
    private:
        std::unordered_map<AnsiStringView, std::unique_ptr<Index>> indexes_;
    protected:

    public:
        Table( Session& session, TableInfo* info )
            : Base( session, info )
        {
            auto& indexInfos = info->Indexes( );
            for ( auto& entry : indexInfos )
            {
                auto index = entry.second->CreateIndex( session, *this );
                indexes_.emplace( entry.first, std::move( index ) );
            }
        }

        virtual void Reset( ) override
        {
            Base::Reset( );
            for ( auto& entry : indexes_ )
            {
                entry.second->Reset( );
            }
        }




    };

    template<typename PrimaryKeyT>
    inline bool HashIndex<PrimaryKeyT>::Find( UInt64 hashKey, const Byte* encodedValue, size_t encodedSize )
    {
        auto& cursor = Cursor( );
        LMDB::Value key( hashKey );
        if ( cursor.SetKeyAndLoad( key ) )
        {
            auto values = cursor.Value( );
            size_t count = values.mv_size / sizeof( PrimaryKeyType );
            if ( count )
            {
                const PrimaryKeyType* current = (const PrimaryKeyType*)values.mv_data;
                const PrimaryKeyType* end = current + count;
                while ( current < end )
                {
                    auto& table = Table( );
                    auto& tableCursor = table.Cursor( );
                    const PrimaryKeyType& primaryKey = *current;
                    LMDB::Value tableKey( primaryKey );
                    if ( tableCursor.SetKeyAndLoad( tableKey ) )
                    {
                        LMDB::Value tableValue = tableCursor.Value( );
                        if ( tableValue.mv_size == encodedSize && memcmp( tableValue.mv_data, encodedValue, tableValue.mv_size ) == 0 )
                        {
                            return true;
                        }
                    }
                    current++;
                }
            }
        }
        return false;
    }


    inline std::unique_ptr<Table> TableInfo::CreateTable( Session& session )
    {
        return std::make_unique<Table>( session, this );
    }



    template<typename TableT>
    class TableInfoT : public TableInfo
    {
    public:
        using Base = TableInfo;
        using TableType = TableT;

        TableInfoT( const AnsiString& name, const LMDBEx::KeyFormat& keyFormat, const LMDBEx::ValueFormat& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }

        template<typename KFT, typename VFT>
            requires IsCoreTuple<KFT> && IsCoreTuple<VFT>
        TableInfoT( const AnsiString& name, const KFT& keyFormat, const VFT& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }


        virtual std::unique_ptr<Table> CreateTable( Session& session ) override
        {
            return std::make_unique<TableType>( session, this );
        }

    };

    template<typename IndexT>
    class IndexInfoT : public IndexInfo
    {
    public:
        using Base = IndexInfo;
        using IndexType = IndexT;

        IndexInfoT( const AnsiString& name, const LMDBEx::KeyFormat& keyFormat, const LMDBEx::ValueFormat& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }

        template<typename KFT, typename VFT>
            requires IsCoreTuple<KFT> && IsCoreTuple<VFT>
        IndexInfoT( const AnsiString& name, const KFT& keyFormat, const VFT& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }


        virtual std::unique_ptr<Index> CreateTable( Session& session, Table& table ) override
        {
            return std::make_unique<IndexType>( session, table, this );
        }

    };

    template<typename HashIndexT, typename PrimaryKeyT>
    class HashIndexInfoT : public HashIndexInfo<PrimaryKeyT>
    {
    public:
        using Base = HashIndexInfo<PrimaryKeyT>;
        using HashIndexType = HashIndexT;

        HashIndexInfoT( const AnsiString& name, const LMDBEx::KeyFormat& keyFormat, const LMDBEx::ValueFormat& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }

        template<typename KFT, typename VFT>
            requires IsCoreTuple<KFT> && IsCoreTuple<VFT>
        HashIndexInfoT( const AnsiString& name, const KFT& keyFormat, const VFT& valueFormat )
            : Base( name, keyFormat, valueFormat )
        {
        }


        virtual std::unique_ptr<Index> CreateIndex( Session& session, Table& table ) override
        {
            return std::make_unique<HashIndexType>( session, table, this );
        }

    };






    class Session
    {
        friend class TableBase;
        friend class DatabaseBase;

        DatabaseBase& database_;
        Guid sessionId_;
        LMDB::TransactionFlags transactionFlags_;
        LMDB::Transaction transaction_;
        std::unordered_map<AnsiStringView, std::unique_ptr<Table> > tables_;
        XXH64Hasher hasher_;
        Session* next_ = nullptr;
    public:
        Session( DatabaseBase& database, const Guid& sessionId, LMDB::TransactionFlags transactionFlags = LMDB::TransactionFlags::None );
        virtual ~Session( ) = default;
    protected:
        LMDB::Environment& Environment( );

        LMDB::Transaction& Transaction( )
        {
            if ( !transaction_ )
            {
                auto& environment = Environment( );
                transaction_ = environment.BeginTransaction( transactionFlags_ );
            }
            return transaction_;
        }
        void Reset( )
        {
            for ( auto& entry : tables_ )
            {
                entry.second->Reset( );
            }
        }
    public:
        constexpr const Guid& Id( ) const noexcept
        {
            return sessionId_;
        }

        void Commit( )
        {
            Reset( );
            transaction_.Commit( );
        }
        void Rollback( )
        {
            Reset( );
            transaction_.Abort( );
        }

        XXH64Hasher& Hasher( )
        {
            return hasher_;
        }

        LMDBEx::Table* GetTable( const AnsiStringView& tableName )
        {
            auto it = tables_.find( tableName );
            if ( it != tables_.end( ) )
            {
                return it->second.get( );
            }
            else
            {
                return nullptr;
            }
        }

    };

    inline LMDB::Transaction& TableBase::Transaction( )
    {
        return session_.Transaction( );
    }



    class DatabaseOptions
    {
        AnsiString databasePath_;
        size_t memoryMapSize_ = LMDB::Environment::DefaultMemoryMapSize;
        std::unordered_map<AnsiStringView, std::unique_ptr< TableInfo > > tables_;
        std::unordered_map<AnsiStringView, std::unique_ptr< IndexInfo > > indexes_;
    public:
        DatabaseOptions( )
        {
        }

        DatabaseOptions( const AnsiString& databasePath, size_t memoryMapSize = LMDB::Environment::DefaultMemoryMapSize )
            : databasePath_( databasePath ), memoryMapSize_( memoryMapSize )
        {
        }

        UInt32 NumberOfTablesandIndexes( ) const
        {
            return static_cast<UInt32>( tables_.size( ) + indexes_.size( ) );
        }

        const AnsiString& DatabasePath( ) const noexcept
        {
            return databasePath_;
        }

        size_t MemoryMapSize( ) const noexcept
        {
            return memoryMapSize_;
        }

        const std::unordered_map<AnsiStringView, std::unique_ptr< TableInfo > >& Tables( ) const
        {
            return tables_;
        }
        const std::unordered_map<AnsiStringView, std::unique_ptr< IndexInfo > >& Indexes( ) const
        {
            return indexes_;
        }

        template<typename TableInfoType>
        TableInfoType* AddTable( const AnsiString& name )
        {
            std::unique_ptr<TableInfo> tableInfo = std::make_unique<TableInfoType>( name );
            AnsiStringView nameView = tableInfo->Name( );
            auto* result = static_cast<TableInfoType*>( tableInfo.get( ) );
            tables_.emplace( nameView, std::move( tableInfo ) );
            return result;
        }

        template<typename TableInfoType>
        TableInfoType* AddTable( const char* name )
        {
            return AddTable<TableInfoType>( AnsiString( name ) );
        }

        TableInfo* FindTable( const AnsiStringView& tableName ) const
        {
            auto it = tables_.find( tableName );
            if ( it != tables_.end( ) )
            {
                return it->second.get( );
            }
            else
            {
                return nullptr;
            }
        }

        template<typename IndexInfoType>
        IndexInfoType* AddIndex( const AnsiString& tableName, const AnsiString& name )
        {
            auto tableInfo = FindTable( tableName );
            if ( tableInfo )
            {
                std::unique_ptr<IndexInfo> indexInfo = std::make_unique<IndexInfoType>( name );
                AnsiStringView nameView = indexInfo->Name( );
                auto* result = static_cast<IndexInfoType*>( indexInfo.get( ) );
                tableInfo->Add( result );
                indexes_.emplace( nameView, std::move( indexInfo ) );
                return result;
            }
            return nullptr;
        }

        template<typename IndexInfoType>
        IndexInfoType* AddIndex( const char* tableName, const char* name )
        {
            return AddIndex<IndexInfoType>( AnsiString( tableName ), AnsiString( name ) );
        }


        template<typename HashIndexInfoType>
        HashIndexInfoType* AddHashIndex( const AnsiString& tableName, const AnsiString& name )
        {
            auto tableInfo = FindTable( tableName );
            if ( tableInfo )
            {
                std::unique_ptr<IndexInfo> indexInfo = std::make_unique<HashIndexInfoType>( name );
                AnsiStringView nameView = indexInfo->Name( );
                auto* result = static_cast<HashIndexInfoType*>( indexInfo.get( ) );
                tableInfo->Add( result );
                indexes_.emplace( nameView, std::move( indexInfo ) );
                return result;
            }
            return nullptr;
        }

        template<typename HashIndexInfoType>
        HashIndexInfoType* AddHashIndex( const char* tableName, const char* name )
        {
            return AddHashIndex<HashIndexInfoType>( AnsiString( tableName ), AnsiString( name ) );
        }

    };






    class DatabaseBase
    {
        friend class Session;
        template <typename DatabaseT, typename SessionT>
        friend class SessionReference;

        const DatabaseOptions& options_;
        LMDB::Environment environment_;
        CriticalSection criticalSection_;
        std::unordered_map<Guid, std::unique_ptr<Session> > sessions_;
        Session* firstFreeSession_ = nullptr;
    protected:

        DatabaseBase( const DatabaseOptions& options )
            : options_( options ), environment_( options.DatabasePath( ), options.MemoryMapSize( ), options.NumberOfTablesandIndexes( ) )
        {
            Initialize( );
        }
    public:
        ~DatabaseBase( )
        {
            if ( firstFreeSession_ )
            {
                auto current = firstFreeSession_;
                while ( current )
                {
                    auto tmp = current;
                    current = tmp->next_;
                    delete tmp;
                }
            }
            environment_.Close( );
        }
    private:
        void Initialize( )
        {
            auto transaction = environment_.BeginTransaction( );

            auto& tables = Tables( );
            for ( auto& entry : tables )
            {
                entry.second->Initialize( transaction );
            }

            transaction.Commit( );
        }
    public:
        const std::unordered_map<AnsiStringView, std::unique_ptr< TableInfo > >& Tables( ) const
        {
            return options_.Tables( );
        }
        const std::unordered_map<AnsiStringView, std::unique_ptr< IndexInfo > >& Indexes( ) const
        {
            return options_.Indexes( );
        }

    protected:
        template <typename SessionT>
        requires std::is_base_of_v<Session, SessionT>
            SessionT* CreateSession( Guid sessionId = Guid( ), LMDB::TransactionFlags transactionFlags = LMDB::TransactionFlags::None )
        {
            std::unique_lock lock( criticalSection_ );
            if ( sessionId.IsEmpty( ) )
            {
                sessionId = Guid::NewGuid( );
            }
            std::unique_ptr<SessionT> session;
            if ( firstFreeSession_ )
            {
                session = std::unique_ptr<SessionT>( (SessionT*)firstFreeSession_ );
                firstFreeSession_->sessionId_ = sessionId;
                firstFreeSession_->transactionFlags_ = transactionFlags;
                firstFreeSession_ = firstFreeSession_->next_;
            }
            else
            {
                session = std::make_unique<SessionT>( *this, sessionId, transactionFlags );
            }
            auto result = session.get( );
            sessions_.emplace( sessionId, std::move( session ) );
            return result;
        }

        template <typename SessionT>
        requires std::is_base_of_v<Session, SessionT>
            SessionT* SessionById( const Guid& sessionId ) const
        {
            std::unique_lock lock( criticalSection_ );
            auto it = sessions_.find( sessionId );
            if ( it != sessions_.end( ) )
            {
                return static_cast<SessionT*>( it->second.get( ) );
            }
            else
            {
                return nullptr;
            }
        }

        template <typename SessionT>
        requires std::is_base_of_v<Session, SessionT>
            void ReleaseSession( SessionT* session )
        {
            std::unique_lock lock( criticalSection_ );
            const Guid& sessionId = session->Id( );
            auto it = sessions_.find( sessionId );

            if ( it != sessions_.end( ) )
            {
                session->Rollback( );
                auto sessionPtr = std::move( it->second );
                sessions_.erase( sessionId );
                sessionPtr->next_ = firstFreeSession_;
                firstFreeSession_ = sessionPtr.release( );
            }
        }



    };


    inline Session::Session( DatabaseBase& database, const Guid& sessionId, LMDB::TransactionFlags transactionFlags )
        : database_( database ), sessionId_( sessionId ), transactionFlags_( transactionFlags )
    {
        auto& tableInfos = database.Tables( );
        for ( auto& entry : tableInfos )
        {
            auto table = entry.second->CreateTable( *this );
            AnsiString name = entry.second->Name( );
            tables_.emplace( name, std::move( table ) );
        }
    }

    inline LMDB::Environment& Session::Environment( )
    {
        return database_.environment_;
    }

    template <typename DatabaseT, typename SessionT>
    class SessionReference
    {
    public:
        using DatabaseType = DatabaseT;
        using SessionType = SessionT;
    private:
        DatabaseType* database_;
        SessionType* session_;
    public:
        SessionReference( )
            : database_( nullptr ), session_( nullptr )
        {
        }

        SessionReference( DatabaseType* database, SessionType* session )
            : database_( database ), session_( session )
        {
        }

        SessionReference( const SessionReference& other ) = delete;
        constexpr SessionReference( SessionReference&& other ) noexcept
            : database_( other.database_ ), session_( other.session_ )
        {
            other.database_ = nullptr;
            other.session_ = nullptr;
        }

        ~SessionReference( )
        {
            Reset( );
        }

        void Reset( )
        {
            if ( database_ && session_ )
            {
                database_->ReleaseSession( session_ );
            }
            database_ = nullptr;
            session_ = nullptr;
        }


        SessionReference& operator = ( const SessionReference& other ) = delete;
        constexpr SessionReference& operator = ( SessionReference&& other ) noexcept
        {
            std::swap( database_, other.database_ );
            std::swap( session_, other.session_ );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return database_ && session_;
        }

        constexpr bool IsValid( ) const noexcept
        {
            return database_ && session_;
        }

        constexpr bool operator == ( nullptr_t ) const noexcept
        {
            return IsValid( ) == false;
        }
        constexpr bool operator != ( nullptr_t ) const noexcept
        {
            return IsValid( );
        }


        [[nodiscard]]
        std::add_lvalue_reference_t<SessionType> operator*( ) const noexcept
        {
            return *session_;
        }

        [[nodiscard]]
        SessionType* operator->( ) const noexcept
        {
            return session_;
        }

        [[nodiscard]]
        SessionType* get( ) const noexcept
        {
            return session_;
        }


    };

    template<typename SessionT>
    class Database : public DatabaseBase
    {
    public:
        using Base = DatabaseBase;
        using SessionType = SessionT;
        using SessionReferenceType = SessionReference< Database, SessionType>;

        Database( const DatabaseOptions& options )
            : Base( options )
        {
        }

        Database( const Database& other ) = delete;
        Database( Database&& other ) = delete;
        Database& operator = ( const Database& other ) = delete;
        Database& operator = ( Database&& other ) = delete;

        SessionReferenceType CreateSession( Guid sessionId = Guid( ), LMDB::TransactionFlags transactionFlags = LMDB::TransactionFlags::None )
        {
            auto* session = Base::CreateSession<SessionType>( sessionId, transactionFlags );
            return SessionReferenceType( this, session );
        }
        SessionType* SessionById( const Guid& sessionId ) const
        {
            return Base::SessionById<SessionType>( sessionId );
        }



    };



}

#endif
