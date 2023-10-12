#pragma once
#ifndef __HCCLOGGERLMDBSINKSTORAGE_H__
#define __HCCLOGGERLMDBSINKSTORAGE_H__

#include <HCCLMDBEx.h>
#include <HCCLogger.h>
#include <HCCLoggerBuffer.h>
#include <HCCLoggerTypes.h>
#include <HCCIOBufferStream.h>
#include <HCCBinaryReader.h>
#include <HCCBinaryWriter.h>


namespace Harlinn::Common::Core::Logging::Sinks::Storage
{
    class LogSiteIndex;
    class LogSiteTableInfo;
    class LogSiteTable;
    class LogDataTableInfo;
    class LogDataTable;
    class LogSession;
    class LogDatabaseOptions;
    class LogDatabase;

    /// <summary>
    /// LogSiteIndexInfo
    /// </summary>
    class LogSiteIndexInfo : public LMDBEx::HashIndexInfoT<LogSiteIndex,UInt64>
    {
    public:
        using Base = LMDBEx::HashIndexInfoT<LogSiteIndex, UInt64>;
    private:
        static constexpr auto keyFormat = Persistent::DescriptorType<UInt64>::value;
        static constexpr auto valueFormat = Persistent::DescriptorType<Vector<UInt64>>::value;
    public:
        LogSiteIndexInfo( const AnsiString& name )
            : Base( name, keyFormat, valueFormat )
        {
        }
    };

    /// <summary>
    /// LogSiteIndex
    /// </summary>
    class LogSiteIndex : public LMDBEx::HashIndex<UInt64>
    {
    public:
        using Base = LMDBEx::HashIndex<UInt64>;
        using InfoType = LogSiteIndexInfo;

        LogSiteIndex( LMDBEx::Session& session, LMDBEx::Table& table, LMDBEx::HashIndexInfo<UInt64>* info );

        using Base::Find;
        bool Find( UInt64 hashValue, LogSite* logLocation );
        bool Find( LogSite* logLocation )
        {
            LMDBEx::Session& session = Base::session_;
            auto& hasher = session.Hasher( );
            hasher.Reset( );
            logLocation->AddTo( hasher );
            UInt64 hashValue = hasher.Digest( );
            return Find( hashValue, logLocation );
        }
    };

    /// <summary>
    /// LogSiteTableInfo
    /// </summary>
    class LogSiteTableInfo : public LMDBEx::TableInfoT<LogSiteTable>
    {
    public:
        using Base = LMDBEx::TableInfoT<LogSiteTable>;
    private:
        static constexpr auto keyFormat = Persistent::DescriptorType<UInt64>::value;
        static constexpr auto valueFormat = Persistent::DescriptorType<UInt16, AnsiString, std::vector<Byte>, bool, size_t, UInt32, UInt32, AnsiString, AnsiString >::value;

        UInt64 maxId_ = 0;
    public:
        LogSiteTableInfo( const AnsiString& name )
            : Base( name, keyFormat, valueFormat )
        {
        }

        virtual void Initialize( LMDB::Transaction& transaction ) override
        {
            Base::Initialize( transaction );
            auto cursor = transaction.OpenCursor( Database( ) );
            if ( cursor.MoveLast( ) )
            {
                if ( cursor.IsPositioned( ) )
                {
                    LMDB::Value keyValue = cursor.Key( );
                    if ( keyValue.mv_size == sizeof( UInt64 ) )
                    {
                        maxId_ = *(UInt64*)keyValue.mv_data;
                    }
                }
            }
        }

        UInt64 NextId( ) noexcept
        {
            return std::bit_cast<UInt64>( InterlockedIncrement64( (Int64*)&maxId_ ) );
        }
    };

    /// <summary>
    /// LogSiteTable
    /// </summary>
    class LogSiteTable : public LMDBEx::Table
    {
        friend class LogSiteIndex;
    public:
        static constexpr size_t MaxValueSize = 4096;
        using Base = LMDBEx::Table;
        using InfoType = LogSiteTableInfo;

        using EncodingBufferType = ByteArray<MaxValueSize>;

    private:
        EncodingBufferType encodingBuffer_;
        LogSiteIndex* logSiteIndex_;
    public:
        LogSiteTable( LMDBEx::Session& session, LMDBEx::TableInfo* info )
            : Base( session, info )
        {
        }

        LogSiteIndex& Index( )
        {
            return *logSiteIndex_;
        }

        LogSiteTableInfo* Info( ) const
        {
            return static_cast<LogSiteTableInfo*>( Base::Info( ) );
        }

        UInt64 NextId( ) noexcept
        {
            return Info( )->NextId( );
        }

        bool Find( LogSite* logSite )
        {
            if ( logSite->Id( ) == 0 )
            {
                auto& index = Index( );
                return index.Find( logSite );
            }
            else
            {
                return Find( logSite->Id( ) );
            }
        }

    private:
        UInt64 HashValue( const LogSite* logSite )
        {
            LMDBEx::Session& session = Base::session_;
            auto& hasher = session.Hasher( );
            hasher.Reset( );
            logSite->AddTo( hasher );
            UInt64 hashValue = hasher.Digest( );
            return hashValue;
        }

        size_t Encode( const LogSite* logSite )
        {
            IO::BufferStream stream( encodingBuffer_.data( ), encodingBuffer_.size( ) );
            IO::BinaryWriter writer( stream );

            logSite->WriteData( writer );
            size_t encodingSize = static_cast<UInt64>( stream.Position( ) );
            return encodingSize;
        }

        void InsertEncoded( UInt64 hashValue, size_t encodingSize, const UInt64& key )
        {
            LMDB::Value keyValue( key );
            LMDB::Value dataValue;
            dataValue.mv_data = encodingBuffer_.data( );
            dataValue.mv_size = encodingSize;
            auto& cursor = Base::Cursor( );
            cursor.Write( keyValue, dataValue );

            auto& index = Index( );
            index.Add( hashValue, key );
        }

    public:

        bool Initialize( LogSite* logSite )
        {
            if ( logSite )
            {
                if ( logSite->Id( ) == 0 )
                {
                    auto hashValue = HashValue( logSite );
                    size_t encodingSize = Encode( logSite );

                    auto& index = Index( );

                    auto found = index.Find( hashValue, encodingBuffer_.data( ), encodingSize );
                    if ( found )
                    {
                        UInt64 key;
                        ReadKey( key );
                        logSite->SetId( key );
                    }
                    else
                    {
                        UInt64 key = NextId( );
                        logSite->SetId( key );
                        InsertEncoded( hashValue, encodingSize, key );
                        return true;
                    }
                }
            }
            return false;
        }


        void Insert( Logging::Level level, const char* message, const Byte* argumentsDescriptor, size_t argumentsDescriptorSize, bool isFixedSize, size_t fixedSize, UInt32 line, UInt32 column, const char* file, const char* function )
        {
            LogSite logSite( level, message, argumentsDescriptor, argumentsDescriptorSize, isFixedSize, fixedSize, line, column, file, function );
            LMDBEx::Session& session = Base::session_;
            auto& hasher = session.Hasher( );
            hasher.Reset( );
            logSite.AddTo( hasher );
            UInt64 hashValue = hasher.Digest( );

            IO::BufferStream stream( encodingBuffer_.data( ), encodingBuffer_.size( ) );
            IO::BinaryWriter writer( stream );

            logSite.WriteData( writer );
            size_t encodingSize = static_cast<UInt64>( stream.Position( ) );

            auto& index = Index( );

            UInt64 key = NextId( );
            LMDB::Value keyValue( key );
            LMDB::Value dataValue;
            dataValue.mv_data = encodingBuffer_.data( );
            dataValue.mv_size = encodingSize;
            auto& cursor = Cursor( );
            cursor.Write( keyValue, dataValue );
            index.Add( hashValue, key );
        }

        bool Find( Logging::Level level, const char* message, const Byte* argumentsDescriptor, size_t argumentsDescriptorSize, bool isFixedSize, size_t fixedSize, UInt32 line, UInt32 column, const char* file, const char* function )
        {
            LogSite logSite( level, message, argumentsDescriptor, argumentsDescriptorSize, isFixedSize, fixedSize, line, column, file, function );
            return Find( &logSite );
        }

        bool Find( UInt64 primaryKey )
        {
            auto& cursor = Cursor( );
            LMDB::Value key( primaryKey );
            return cursor.SetKey( key );
        }
        bool IsEqual( const Byte* encodedLogLocation, size_t size )
        {
            auto& cursor = Cursor( );
            auto value = cursor.Value( );
            return value.mv_size == size &&
                memcmp( encodedLogLocation, value.mv_data, size ) == 0;

        }

        bool ReadKey( UInt64& key )
        {
            auto& cursor = Cursor( );
            if ( cursor.IsPositioned( ) )
            {

                auto keyData = cursor.Key( );
                if ( keyData.mv_size )
                {
                    key = *(UInt64*)keyData.mv_data;
                    return true;
                }
            }
            return false;
        }


        bool Read( Types::LogSiteData& logSite )
        {
            auto& cursor = Cursor( );
            if ( cursor.IsPositioned( ) )
            {
                auto keyData = cursor.Key( );
                if ( keyData.mv_size )
                {
                    UInt64 key = *(UInt64*)keyData.mv_data;
                    logSite.SetId( key );
                    auto value = cursor.Value( );
                    if ( value.mv_size )
                    {
                        IO::BufferStream stream( reinterpret_cast<Byte*>( value.mv_data ), value.mv_size );
                        IO::BinaryReader reader( stream );
                        
                        logSite.ReadData( reader );
                        return true;
                    }
                }
            }
            return false;
        }

    };

    inline LogSiteIndex::LogSiteIndex( LMDBEx::Session& session, LMDBEx::Table& table, LMDBEx::HashIndexInfo<UInt64>* info )
        : Base( session, table, info )
    {
        static_cast<LogSiteTable&>( table ).logSiteIndex_ = this;
    }


    inline bool LogSiteIndex::Find( UInt64 hashValue, LogSite* logSite )
    {
        LogSiteTable& table = static_cast<LogSiteTable&>( Table( ) );
        auto& encodingBuffer = table.encodingBuffer_;

        IO::BufferStream stream( encodingBuffer.data( ), encodingBuffer.size( ) );
        IO::BinaryWriter writer( stream );
        
        logSite->Write( writer );
        size_t encodingSize = static_cast<UInt64>( stream.Position( ) );
        return Base::Find( hashValue, encodingBuffer.data( ), encodingSize );
    }



    /// <summary>
    /// LogHashIndexInfoT
    /// </summary>
    template< typename LogIndexT, typename PrimaryKeyT, typename KeyFormatT, typename ValueFormatT >
    class LogHashIndexInfoT : public LMDBEx::HashIndexInfoT<LogIndexT, PrimaryKeyT>
    {
    public:
        using Base = LMDBEx::HashIndexInfoT<LogIndexT, PrimaryKeyT>;
    private:
        static constexpr auto keyFormat = KeyFormatT::value;
        static constexpr auto valueFormat = ValueFormatT::value;
    public:
        LogHashIndexInfoT( const AnsiString& name )
            : Base( name, keyFormat, valueFormat )
        {
        }
    };


    /// <summary>
    /// LogHashIndexT
    /// </summary>
    template<typename TableT,typename PrimaryKeyT, typename KeyFormatT, typename ValueFormatT>
    class LogHashIndexT : public LMDBEx::HashIndex<PrimaryKeyT>
    {
    public:
        using Base = LMDBEx::HashIndex<Guid>;
        using InfoType = LogHashIndexInfoT<LogHashIndexT, PrimaryKeyT, KeyFormatT, ValueFormatT >;
        using TableType = TableT;
        using DataType = typename TableT::DataType;

        LogHashIndexT( LMDBEx::Session& session, LMDBEx::Table& table, LMDBEx::IndexInfo* info )
            : Base( session, table, info )
        {
            static_cast<TableT&>( table ).index_ = this;
        }


        TableType& PrimaryTable( )
        {
            return static_cast<TableType&>( Base::Table( ) );
        }


        using Base::Find;
        bool Find( UInt64 hashValue, DataType* dataObject )
        {
            auto& table = PrimaryTable( );
            auto& encodingBuffer = table.encodingBuffer_;
            size_t encodingSize = table.Encode( dataObject );

            return Base::Find( hashValue, encodingBuffer.data( ), encodingSize );
        }
        bool Find( DataType* dataObject )
        {
            auto& table = PrimaryTable( );
            UInt64 hashValue = table.HashValue( dataObject );
            return Find( hashValue, dataObject );
        }
    };


    /// <summary>
    /// LogTableT
    /// </summary>
    template<typename InfoT>
    class LogTableT : public LMDBEx::Table
    {
        friend class LogComputerIndex;
        template<typename TableT, typename PrimaryKeyT, typename KeyFormatT, typename ValueFormatT>
        friend class LogHashIndexT;
    public:
        using Base = LMDBEx::Table;

        using InfoType = InfoT;
        using IndexType = typename InfoType::IndexType;
        using PrimaryKeyType = typename InfoType::PrimaryKeyType;
        using DataType = typename InfoType::DataType;
        static constexpr size_t MaxValueSize = InfoType::MaxValueEncodingSize;
        using ValueEncodingBufferType = ByteArray<MaxValueSize>;
    private:
        ValueEncodingBufferType valueEncodingBuffer_;
        IndexType* index_;
    public:
        LogTableT( LMDBEx::Session& session, LMDBEx::TableInfo* info )
            : Base( session, info )
        {
        }

        IndexType& Index( )
        {
            return *index_;
        }

        InfoType& Info( ) const
        {
            return *static_cast<InfoType*>( Base::Info( ) );
        }


        bool Find( const PrimaryKeyType& primaryKey )
        {
            auto& cursor = Base::Cursor( );
            LMDB::Value key( primaryKey );
            return cursor.SetKey( key );
        }

        bool ReadKey( PrimaryKeyType& key )
        {
            auto& cursor = Base::Cursor( );
            if ( cursor.IsPositioned( ) )
            {

                auto keyData = cursor.Key( );
                if ( keyData.mv_size )
                {
                    if constexpr ( IsBasicType<PrimaryKeyType> )
                    {
                        key = *(PrimaryKeyType*)keyData.mv_data;
                        ByteSwap( key );
                    }
                    else
                    {
                        static constexpr bool isBasicType = IsBasicType<PrimaryKeyType>;
                        static_assert( isBasicType, "Primary key is not a basic type" );
                    }
                    return true;
                }
            }
            return false;
        }

        bool ReadValue( DataType& dataObject )
        {
            auto& cursor = Base::Cursor( );
            if ( cursor.IsPositioned( ) )
            {
                auto valueData = cursor.Value( );
                if ( valueData.mv_size )
                {
                    IO::BufferStream stream( (Byte*)valueData.mv_data, valueData.mv_size );
                    IO::BinaryReader reader( stream );

                    dataObject.Read( reader );
                    return true;
                }
            }
            return false;
        }


        bool Find( DataType& dataObject )
        {
            if ( HasValidKey( &dataObject ) )
            {
                auto found = Find( dataObject.Id( ) );
                if ( found )
                {
                    return true;
                }
            }

        }



    private:
        UInt64 HashValue( const DataType* dataObject )
        {
            LMDBEx::Session& session = Base::session_;
            auto& hasher = session.Hasher( );
            hasher.Reset( );
            dataObject->AddTo( hasher );
            UInt64 hashValue = hasher.Digest( );
            return hashValue;
        }
        size_t Encode( const DataType* dataObject )
        {
            IO::BufferStream stream( valueEncodingBuffer_.data( ), valueEncodingBuffer_.size( ) );
            IO::BinaryWriter writer( stream );

            dataObject->WriteData( writer );
            size_t encodingSize = static_cast<UInt64>( stream.Position( ) );
            return encodingSize;
        }

        void InsertEncoded( UInt64 hashValue, size_t encodingSize, const PrimaryKeyType& key )
        {
            LMDB::Value keyValue( key );
            LMDB::Value dataValue;
            dataValue.mv_data = valueEncodingBuffer_.data( );
            dataValue.mv_size = encodingSize;
            auto& cursor = Base::Cursor( );
            cursor.Write( keyValue, dataValue );

            auto& index = Index( );
            index.Add( hashValue, key );
        }

        bool HasValidKey( DataType* dataObject )
        {
            return InfoType::HasValidKey( dataObject );
        }
        void NewKey( DataType* dataObject )
        {
            auto& info = Info( );
            info.NewKey( dataObject );
        }


    public:

        void Update( DataType* dataObject )
        {
            if ( dataObject )
            {
                
            }
#ifdef _DEBUG
            else
            {
                printf( "Missing dataObject in %s, file:%s, line:%d\n", __FUNCTION__, __FILE__, __LINE__ );
            }
#endif
        }



        bool Insert( DataType* dataObject )
        {
            if ( dataObject )
            {
                auto& key = dataObject->Id( );

                if ( HasValidKey( dataObject ) == false )
                {
                    NewKey( dataObject );
                }
                else
                {
                    if ( Find( key ) )
                    {
                        return false;
                    }
                }
                UInt64 hashValue = HashValue( dataObject );
                size_t encodingSize = Encode( dataObject );
                auto& index = Index( );
                auto found = index.Find( hashValue, valueEncodingBuffer_.data( ), encodingSize );
                if ( found )
                {
                    return false;
                }
                InsertEncoded( hashValue, encodingSize, key );
                return true;
            }
#ifdef _DEBUG
            else
            {
                printf( "Missing dataObject in %s, file:%s, line:%d\n", __FUNCTION__, __FILE__, __LINE__ );
            }
#endif
            return false;
        }

        bool InsertIfNotExist( DataType* dataObject )
        {
            if ( dataObject )
            {
                if ( InfoType::HasValidKey( dataObject ) == false )
                {
                    UInt64 hashValue = HashValue( dataObject );
                    size_t encodingSize = Encode( dataObject );

                    auto& index = Index( );

                    auto found = index.Find( hashValue, valueEncodingBuffer_.data( ), encodingSize );
                    if ( found )
                    {
                        PrimaryKeyType key{};
                        ReadKey( key );
                        dataObject->SetId( key );
                    }
                    else
                    {
                        Guid key = Guid::NewGuid( );
                        dataObject->SetId( key );
                        InsertEncoded( hashValue, encodingSize, key );
                        return true;
                    }
                }
            }
#ifdef _DEBUG
            else
            {
                printf( "Missing computerInfo in %s, file:%s, line:%d\n", __FUNCTION__, __FILE__, __LINE__ );
            }
#endif

            return false;
        }

    };


    /// <summary>
    /// LogTableInfoT
    /// </summary>
    template<typename DataT, typename PrimaryKeyT, typename ValueFormatT, size_t maxKeyEncodingSize = 128, size_t maxValueEncodingSize = 4096>
    class LogTableInfoT : public LMDBEx::TableInfoT<LogTableT<LogTableInfoT<DataT, PrimaryKeyT, ValueFormatT, maxKeyEncodingSize, maxValueEncodingSize>>>
    {
    public:
        using DataType = DataT;
        static constexpr size_t MaxKeyEncodingSize = maxKeyEncodingSize;
        static constexpr size_t MaxValueEncodingSize = maxValueEncodingSize;
        using PrimaryKeyType = PrimaryKeyT;
        using IndexKeyFormatType = typename Persistent::DescriptorType<UInt64>;
        using IndexValueFormatTtype = typename Persistent::DescriptorType<Vector<PrimaryKeyT>>;
        using KeyFormatType = typename Persistent::DescriptorType<PrimaryKeyT>;
        using ValueFormatType = ValueFormatT;


        using TableType = LogTableT<LogTableInfoT<DataT, PrimaryKeyT, ValueFormatT, maxValueEncodingSize>>;
        
        using Base = LMDBEx::TableInfoT<LogTableT<LogTableInfoT<DataT, PrimaryKeyT, ValueFormatT, maxKeyEncodingSize, maxValueEncodingSize>>>;
        using IndexType = LogHashIndexT<TableType, PrimaryKeyType, IndexKeyFormatType, IndexValueFormatTtype>;
        using IndexInfoType = typename IndexType::InfoType;
    private:
        static constexpr auto keyFormat = KeyFormatType::value;
        static constexpr auto valueFormat = ValueFormatType::value;
    public:
        LogTableInfoT( const AnsiString& name )
            : Base( name, keyFormat, valueFormat )
        {
        }

        static bool HasValidKey( const DataType* dataObject )
        {
            return dataObject->Id( ).IsEmpty( ) == false;
        }

        void NewKey( DataType* dataObject )
        {
            dataObject->SetId( Guid::NewGuid() );
        }

    };






    /// <summary>
    /// LogDataTableInfo
    /// </summary>
    class LogDataTableInfo : public LMDBEx::TableInfoT<LogDataTable>
    {
    public:
        using Base = LMDBEx::TableInfoT<LogDataTable>;
    private:
        static constexpr auto keyFormat = Persistent::DescriptorType<Guid, DateTime>::value;
        static constexpr auto valueFormat = Persistent::DescriptorType<std::vector<Byte>>::value;
    public:
        LogDataTableInfo( const AnsiString& name )
            : Base( name, keyFormat, valueFormat )
        {
        }
#define USE_MEMCMP_ENCODING 1
        virtual void Initialize( LMDB::Transaction& transaction ) override
        {
            Base::Initialize( transaction );
#ifndef USE_MEMCMP_ENCODING
            transaction.SetCompare( Database( ), []( const MDB_val* first, const MDB_val* second )->int
            {
                const BackendBuffer* firstKey = (const BackendBuffer*)first->mv_data;
                const BackendBuffer* secondKey = (const BackendBuffer*)second->mv_data;
                return firstKey->CompareTo( *secondKey );
            } );
#endif

        }
    };

    /// <summary>
    /// LogDataTable
    /// </summary>
    class LogDataTable : public LMDBEx::Table
    {
    public:
        using Base = LMDBEx::Table;
        
        static constexpr size_t KeyEncodingSize = sizeof( Internal::BufferKey );
        using KeyEncodingBufferType = ByteArray<KeyEncodingSize>;
    private:
        KeyEncodingBufferType keyEncodingBuffer_;
    public:
        LogDataTable( LMDBEx::Session& session, LMDBEx::TableInfo* info )
            : Base( session, info )
        {
        }


        void Insert( const Internal::Buffer* logBuffer )
        {
            /*
            auto count = logBuffer->RecordCount( );
            if ( count )
            {
                TranslateSitesToIds( logBuffer );
                auto& id = logBuffer->LoggerId( );
                auto bufferSize = logBuffer->ByteSize( );
                auto firstRecord = logBuffer->First( );
                auto firstRecordTimestamp = logBuffer->ToDateTime( firstRecord->Time( ) );
                auto bufferNumber = logBuffer->BufferNumber( );
#ifdef USE_MEMCMP_ENCODING
                NoSql::Writer writer( keyEncodingBuffer_.data( ) );
                writer.Write( id );
                writer.Write( firstRecordTimestamp );
                writer.Write( bufferNumber );
                LMDB::Value keyValue( (const void*)keyEncodingBuffer_.data( ), KeyEncodingSize );
#else                
                LogBufferKey key( id, firstRecordTimestamp, bufferNumber );
                LMDB::Value keyValue( key );
#endif

                LMDB::Value dataValue( (const void*)logBuffer, bufferSize );

                auto& cursor = Cursor( );
                cursor.Write( keyValue, dataValue );
            }
            */
        }
        const Internal::Buffer* Value( )
        {
            /*
            auto& cursor = Cursor( );
            auto value = cursor.Value( );
            return (const LogBuffer*)value.mv_data;
            */
            return nullptr;
        }

        Internal::BufferKey Key( )
        {

            auto& cursor = Cursor( );
            auto value = cursor.Key( );
#ifdef USE_MEMCMP_ENCODING
            Internal::BufferKey result;
            IO::BufferStream stream( (Byte*)value.mv_data, value.mv_size );
            IO::BinaryReader< IO::BufferStream, true> reader( stream );
            result.Read( reader );
            return result;
#else
            auto* ptr = (BackendBufferKey*)value.mv_data;
            return *ptr;
#endif
        }


    };

    using LogComputerTableInfo = LogTableInfoT
        <
            Types::ComputerInfo,Guid,
            Persistent::DescriptorType<Guid, WideString, WideString>
        >;
    using LogComputerTable = LogComputerTableInfo::TableType;
    using LogComputerIndexInfo = LogComputerTableInfo::IndexInfoType;


    using LogUserTableInfo = LogTableInfoT
        <
            Types::UserInfo, Guid,
            Persistent::DescriptorType<Guid, WideString, WideString>
        >;
    using LogUserTable = LogUserTableInfo::TableType;
    using LogUserIndexInfo = LogUserTableInfo::IndexInfoType;

    using LogExecutableTableInfo = LogTableInfoT
        <
            Types::ExecutableInfo, Guid,
            Persistent::DescriptorType<Guid, WideString>
        >;
    using LogExecutableTable = LogExecutableTableInfo::TableType;
    using LogExecutableIndexInfo = LogExecutableTableInfo::IndexInfoType;

    using LogConfigurationFileTableInfo = LogTableInfoT
        <
            Types::ConfigurationFileInfo, Guid,
            Persistent::DescriptorType<Guid, WideString, WideString>
        >;
    using LogConfigurationFileTable = LogConfigurationFileTableInfo::TableType;
    using LogConfigurationFileIndexInfo = LogConfigurationFileTableInfo::IndexInfoType;

    using LogWindowsVersionTableInfo = LogTableInfoT
        <
            Types::WindowsVersionInfo, Guid,
            Persistent::DescriptorType<Guid, DateTime, Guid, UInt32, UInt32, UInt32, UInt32, WideString, UInt16, UInt16, UInt16, Byte>
        >;
    using LogWindowsVersionTable = LogWindowsVersionTableInfo::TableType;
    using LogWindowsVersionIndexInfo = LogWindowsVersionTableInfo::IndexInfoType;

    using LogProcessTableInfo = LogTableInfoT
        <
            Types::ProcessInfo, Guid,
            Persistent::DescriptorType<Guid, WideString, WideString>
        >;
    using LogProcessTable = LogProcessTableInfo::TableType;
    using LogProcessIndexInfo = LogProcessTableInfo::IndexInfoType;

    /// <summary>
    /// LogSession
    /// </summary>
    class LogSession : public LMDBEx::Session
    {
    public:
        using Base = LMDBEx::Session;
    private:
        LogSiteTable* logSiteTable_ = nullptr;
        LogComputerTable* logComputerTable_ = nullptr;
        LogUserTable* logUserTable_ = nullptr;
        LogConfigurationFileTable* logConfigurationFileTable_ = nullptr;
        LogExecutableTable* logExecutableTable_ = nullptr;
        LogWindowsVersionTable* logWindowsVersionTable_ = nullptr;
        LogProcessTable* logProcessTable_ = nullptr;
        LogDataTable* logDataTable_ = nullptr;
    public:
        LogSession( LMDBEx::DatabaseBase& database, const Guid& sessionId, LMDB::TransactionFlags transactionFlags = LMDB::TransactionFlags::None );

        LogSiteTable* GetLogSiteTable( );
        LogComputerTable* GetLogComputerTable( );
        LogUserTable* GetLogUserTable( );
        LogConfigurationFileTable* GetLogConfigurationFileTable( );
        LogExecutableTable* GetLogExecutableTable( );
        LogWindowsVersionTable* GetLogWindowsVersionTable( );
        LogProcessTable* GetLogProcessTable( );
        LogDataTable* GetLogDataTable( );

        bool InitializeLogSite( LogSite* logLocation )
        {
            auto* logLocationTable = GetLogSiteTable( );
            return logLocationTable->Initialize( logLocation );
        }

        void InsertLogSite( Logging::Level level, const char* message, const Byte* argumentsDescriptor, size_t argumentsDescriptorSize, bool isFixedSize, size_t fixedSize, UInt32 line, UInt32 column, const char* file, const char* function )
        {
            auto* logLocationTable = GetLogSiteTable( );
            logLocationTable->Insert( level, message, argumentsDescriptor, argumentsDescriptorSize, isFixedSize, fixedSize, line, column, file, function );
        }

        void InsertLogBuffer( const Internal::Buffer* logBuffer )
        {
            auto* logDataTable = GetLogDataTable( );
            logDataTable->Insert( logBuffer );
        }
    };




    /// <summary>
    /// LogDatabaseOptions
    /// </summary>
    class LogDatabaseOptions : public LMDBEx::DatabaseOptions
    {
    public:
        using Base = LMDBEx::DatabaseOptions;

        static constexpr char LogSiteTableName[] = "lst";
        static constexpr char LogSiteIndexName[] = "lsi";
        static constexpr char LogComputerTableName[] = "lct";
        static constexpr char LogComputerIndexName[] = "lci";
        static constexpr char LogUserTableName[] = "lut";
        static constexpr char LogUserIndexName[] = "lui";
        static constexpr char LogConfigurationFileTableName[] = "lcft";
        static constexpr char LogConfigurationFileIndexName[] = "lcfi";
        static constexpr char LogExecutableTableName[] = "let";
        static constexpr char LogExecutableIndexName[] = "lei";
        static constexpr char LogWindowsVersionTableName[] = "lwvt";
        static constexpr char LogWindowsVersionIndexName[] = "lwvi";
        static constexpr char LogProcessTableName[] = "lpt";
        static constexpr char LogProcessIndexName[] = "lpi";


        static constexpr char LogDataTableName[] = "ldt";

        LogDatabaseOptions( )
        {
            Initialize( );
        }

        LogDatabaseOptions( const AnsiString& databasePath, size_t memoryMapSize = LMDB::Environment::DefaultMemoryMapSize )
            : Base( databasePath, memoryMapSize )
        {
            Initialize( );
        }

        void Initialize( )
        {
            AddTable<LogSiteTableInfo>( LogSiteTableName );
            AddHashIndex<LogSiteIndexInfo>( LogSiteTableName, LogSiteIndexName );

            AddTable<LogComputerTableInfo>( LogComputerTableName );
            AddHashIndex<LogComputerIndexInfo>( LogComputerTableName, LogComputerIndexName );

            AddTable<LogUserTableInfo>( LogUserTableName );
            AddHashIndex<LogUserIndexInfo>( LogUserTableName, LogUserIndexName );

            AddTable<LogConfigurationFileTableInfo>( LogConfigurationFileTableName );
            AddHashIndex<LogConfigurationFileIndexInfo>( LogConfigurationFileTableName, LogConfigurationFileIndexName );

            AddTable<LogExecutableTableInfo>( LogExecutableTableName );
            AddHashIndex<LogExecutableIndexInfo>( LogExecutableTableName, LogExecutableIndexName );

            AddTable<LogWindowsVersionTableInfo>( LogWindowsVersionTableName );
            AddHashIndex<LogWindowsVersionIndexInfo>( LogWindowsVersionTableName, LogWindowsVersionIndexName );

            AddTable<LogProcessTableInfo>( LogProcessTableName );
            AddHashIndex<LogProcessIndexInfo>( LogProcessTableName, LogProcessIndexName );

            AddTable<LogDataTableInfo>( LogDataTableName );
        }
    };


    inline LogSiteTable* LogSession::GetLogSiteTable( )
    {
        if ( logSiteTable_ == nullptr )
        {
            logSiteTable_ = static_cast<LogSiteTable*>( GetTable( LogDatabaseOptions::LogSiteTableName ) );
        }
        return logSiteTable_;
    }

    inline LogComputerTable* LogSession::GetLogComputerTable( )
    {
        if ( logComputerTable_ == nullptr )
        {
            logComputerTable_ = static_cast<LogComputerTable*>( GetTable( LogDatabaseOptions::LogComputerTableName ) );
        }
        return logComputerTable_;
    }
    inline LogUserTable* LogSession::GetLogUserTable( )
    {
        if ( logUserTable_ == nullptr )
        {
            logUserTable_ = static_cast<LogUserTable*>( GetTable( LogDatabaseOptions::LogUserTableName ) );
        }
        return logUserTable_;
    }
    inline LogConfigurationFileTable* LogSession::GetLogConfigurationFileTable( )
    {
        if ( logConfigurationFileTable_ == nullptr )
        {
            logConfigurationFileTable_ = static_cast<LogConfigurationFileTable*>( GetTable( LogDatabaseOptions::LogConfigurationFileTableName ) );
        }
        return logConfigurationFileTable_;
    }
    inline LogExecutableTable* LogSession::GetLogExecutableTable( )
    {
        if ( logExecutableTable_ == nullptr )
        {
            logExecutableTable_ = static_cast<LogExecutableTable*>( GetTable( LogDatabaseOptions::LogExecutableTableName ) );
        }
        return logExecutableTable_;
    }
    inline LogWindowsVersionTable* LogSession::GetLogWindowsVersionTable( )
    {
        if ( logWindowsVersionTable_ == nullptr )
        {
            logWindowsVersionTable_ = static_cast<LogWindowsVersionTable*>( GetTable( LogDatabaseOptions::LogWindowsVersionTableName ) );
        }
        return logWindowsVersionTable_;
    }
    inline LogProcessTable* LogSession::GetLogProcessTable( )
    {
        if ( logProcessTable_ == nullptr )
        {
            logProcessTable_ = static_cast<LogProcessTable*>( GetTable( LogDatabaseOptions::LogProcessTableName ) );
        }
        return logProcessTable_;
    }

    inline LogDataTable* LogSession::GetLogDataTable( )
    {
        if ( logDataTable_ == nullptr )
        {
            logDataTable_ = static_cast<LogDataTable*>( GetTable( LogDatabaseOptions::LogDataTableName ) );
        }
        return logDataTable_;
    }



    /// <summary>
    /// LogDatabase
    /// </summary>
    class LogDatabase : public LMDBEx::Database<LogSession>
    {
    public:
        using Base = LMDBEx::Database<LogSession>;
        LogDatabase( const LogDatabaseOptions& options )
            : Base( options )
        {
        }
    };

    inline LogSession::LogSession( LMDBEx::DatabaseBase& database, const Guid& sessionId, LMDB::TransactionFlags transactionFlags )
        : Base( database, sessionId, transactionFlags )
    {
    }

    


    class LogDatabaseStore 
    {
    public:
        
    private:
        LogDatabase logDatabase_;
        
        UInt64 logBufferCount_ = 0;
        UInt64 logRecordCount_ = 0;
        UInt64 logLocationCount_ = 0;
    public:
        LogDatabaseStore( const LogDatabaseOptions& options )
            : logDatabase_( options )
        {
        }

        LogDatabase& Database( )
        {
            return logDatabase_;
        }

        constexpr UInt64 LogBufferCount( ) const noexcept
        {
            return logBufferCount_;
        }
        constexpr UInt64 LogRecordCount( ) const noexcept
        {
            return logRecordCount_;
        }
        constexpr UInt64 LogLocationCount( ) const noexcept
        {
            return logLocationCount_;
        }


        void Process( Internal::Buffer* logBuffer ) noexcept
        {
            try
            {
                logBufferCount_++;
                auto count = logBuffer->RecordCount( );
                if ( count )
                {
                    logRecordCount_ += count;
                    auto session = logDatabase_.CreateSession( );
                    session->InsertLogBuffer( logBuffer );
                    session->Commit( );
                }
            }
            catch ( Exception& exception )
            {
                auto typeName = exception.TypeName( );
                auto message = exception.Message( );
                wprintf( L"Caught %s Exception in LogDatabaseStore::Process(...)\nMessage:%s\n", typeName.c_str( ), message.c_str( ) );
            }
        }

    };




    
}

#endif
