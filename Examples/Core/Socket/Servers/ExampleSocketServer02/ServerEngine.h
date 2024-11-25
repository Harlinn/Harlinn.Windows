#pragma once
#ifndef __SERVERENGINE_H__
#define __SERVERENGINE_H__

#include <HCCThread.h>
#include <HCCIOContext.h>
#include <HCCSocketServer.h>
#include <HCCGuid.h>
#include <HCCBinaryReader.h>
#include <HCCBinaryWriter.h>
#include <HCCMemory.h>

#include <HExEngine.h>
#include <boost/container/flat_map.hpp>

namespace Harlinn::Common::Core::Examples
{
    using namespace Harlinn::Common::Core;
    using namespace Harlinn::Common::Core::IO::Sockets;
    



    class ServerEngine;
    class ServerSession : public SessionT<ServerEngine>
    {
    public:
        using Base = SessionT<ServerEngine>;
        std::unique_ptr<CriticalSection> criticalSection_;
    public:
        ServerSession( ServerEngine& engine, Int64 id, bool createDatabase )
            : Base( engine, id, createDatabase ), criticalSection_( std::make_unique<CriticalSection>() )
        {
        }

        ~ServerSession( )
        {
            printf( "Session destroyed\n" );
        }

        void lock( ) const
        {
            criticalSection_->Enter( );
            auto& eseSession = EseSession( );
            UInt64 context = (UInt64)this;
            eseSession.SetContext( context );
            printf( "Set context: %llu\n", context );

        }

        void unlock( ) const
        {
            auto& eseSession = EseSession( );
            eseSession.ResetContext( );
            criticalSection_->Leave( );
            UInt64 context = (UInt64)this;
            printf( "Reset context: %llu\n", context );
        }

        void Close( )
        {
            std::unique_lock lock( *criticalSection_ );
            auto ciriticalSection = std::move( criticalSection_ );
            Base::Close( );
        }
    };

    class ServerEngine : public EngineT<ServerEngine, ServerSession>
    {
    public:
        using Base = EngineT<ServerEngine, ServerSession>;
    public:
        ServerEngine( const EngineOptions& options, const char* instanceName )
            : Base( options, instanceName )
        {
        }
    };


    enum class RequestReplyType : byte
    {
        Unknown = 0,
        CreateSession,
        CloseSession,
        Fault,
        GetCatalogItem,
        GetCatalogItems,
        GetAllCatalogItems,
        CreateOrRetrieveCatalog,
        CreateOrRetrieveAsset,
        DeleteCatalogItem,
        GetSensor,
        GetSensors,
        GetAllSensors,
        CreateOrRetrieveSensor,
        DeleteSensor,
        GetSensorPoints,
        GetAllSensorPoints,
        StoreSensorValue,
        StoreSensorPoints,
        ReplaceSensorPoints,
        GetAllSensorValues,
        SendSensorPoints,
        SendJSON
    };

    class Protocol
    {
        ServerEngine& engine_;
    public:
        Protocol( ServerEngine* engine )
            : engine_( *engine )
        {
        }
    private:
        template<IO::StreamReader StreamT>
        static RequestReplyType ReadRequestType( IO::BinaryReader<StreamT>& requestReader )
        {
            return static_cast<RequestReplyType>( requestReader.Read<Byte>() );
        }
    public:

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        bool Process( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            bool result = true;
            auto requestType = ReadRequestType( requestReader );
            switch ( requestType )
            {
                case RequestReplyType::CreateSession:
                {
                    CreateSession( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::CloseSession:
                {
                    CloseSession( requestReader, replyWriter );
                    result = false;
                }
                break;
                case RequestReplyType::GetCatalogItem:
                {
                    GetCatalogItem( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::GetCatalogItems:
                {
                    GetCatalogItems( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::GetAllCatalogItems:
                {
                    GetAllCatalogItems( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::CreateOrRetrieveCatalog:
                {
                    CreateOrRetrieveCatalog( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::CreateOrRetrieveAsset:
                {
                    CreateOrRetrieveAsset( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::DeleteCatalogItem:
                {
                    DeleteCatalogItem( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::GetSensor:
                {
                    GetSensor( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::GetSensors:
                {
                    GetSensors( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::GetAllSensors:
                {
                    GetAllSensors( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::CreateOrRetrieveSensor:
                {
                    CreateOrRetrieveSensor( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::DeleteSensor:
                {
                    DeleteSensor( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::GetSensorPoints:
                {
                    GetSensorPoints( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::GetAllSensorPoints:
                {
                    GetAllSensorPoints( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::StoreSensorValue:
                {
                    StoreSensorValue( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::StoreSensorPoints:
                {
                    StoreSensorPoints( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::ReplaceSensorPoints:
                {
                    ReplaceSensorPoints( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::GetAllSensorValues:
                {
                    GetAllSensorValues( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::SendSensorPoints:
                {
                    SendSensorPoints( requestReader, replyWriter );
                }
                break;
                case RequestReplyType::SendJSON:
                {
                    SendJSON( requestReader, replyWriter );
                }
                break;
                default:
                    WideString message(L"Unknown function");
                    WriteFault( replyWriter, 0, 0, message );
                break;
            }
            return result;
        }
    private:
        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void CreateSession( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            auto session = engine_.CreateSession( );
            auto sessionId = session->Id( );
            printf( "Session %zu created.\n", sessionId );
            replyWriter.Write( static_cast<Byte>( RequestReplyType::CreateSession ) );
            replyWriter.Write( sessionId );
        }
        template<IO::StreamWriter StreamWriterT>
        void WriteFault( IO::BinaryWriter<StreamWriterT>& replyWriter, UInt64 sessionId, Int64 errorCode, const WideString& message )
        {
            wprintf( L"Fault in session %zu, Code: %lld, Message: %s\n", sessionId, errorCode, message.c_str() );
            replyWriter.Write( static_cast<Byte>( RequestReplyType::Fault ) );
            replyWriter.Write( sessionId );
            replyWriter.Write( errorCode );
            replyWriter.Write( message );
        }

        template<IO::StreamWriter StreamWriterT>
        void InvalidSession( IO::BinaryWriter<StreamWriterT>& replyWriter, UInt64 sessionId )
        {
            WriteFault( replyWriter, sessionId, 0 , WideString(L"Invalid session id") );
        }
        template<IO::StreamWriter StreamWriterT>
        void UnknownException( IO::BinaryWriter<StreamWriterT>& replyWriter, UInt64 sessionId )
        {
            WriteFault( replyWriter, sessionId, 0, WideString( L"Unknown exception" ) );
        }

        template<IO::StreamWriter StreamWriterT>
        void WriteFault( IO::BinaryWriter<StreamWriterT>& replyWriter, UInt64 sessionId, const Harlinn::Common::Core::Exception& exc )
        {
            auto message = exc.Message( );
            WriteFault( replyWriter, sessionId, exc.GetCode( ), message );
        }

        template<IO::StreamWriter StreamWriterT>
        void WriteFault( IO::BinaryWriter<StreamWriterT>& replyWriter, UInt64 sessionId, const std::exception& exc )
        {
            WideString message( WideString::From( exc.what( ) ) );
            WriteFault( replyWriter, sessionId, 0, message );
        }

        template<RequestReplyType requestReplyType, IO::StreamWriter StreamWriterT>
        static void WriteReplyHeader( IO::BinaryWriter<StreamWriterT>& writer, UInt64 sessionId, UInt64 requestId )
        {
            writer.Write( static_cast<Byte>( requestReplyType ) );
            writer.Write( sessionId );
            writer.Write( requestId );
        }

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void CloseSession( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::CloseSession;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                printf( "Closing session %zu\n", sessionId );
                session->Close( );
                printf( "Session %zu closed.\n", sessionId );
            }
            else
            {
                printf( "Attempted to close unknown session %zu\n", sessionId );
            }
            
            WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
        }

#define SERVERSESSION_TRY std::unique_lock lock( *session ); try

#define SERVERSESSION_CATCH() \
catch ( const Core::Exception& ex ) \
{ \
    WriteFault( replyWriter, sessionId, ex ); \
} \
catch ( const std::exception& exc ) \
{ \
    WriteFault( replyWriter, sessionId, exc ); \
} \
catch ( const ThreadAbortException& ) \
{ \
    throw; \
} \
catch ( ... ) \
{ \
    UnknownException( replyWriter, sessionId ); \
}

    private:
        template<IO::StreamWriter StreamWriterT>
        static void Write( IO::BinaryWriter<StreamWriterT>& writer, const CatalogItem& catalogItem )
        {
            if ( catalogItem.index( ) )
            {
                const auto& asset = std::get<Asset>( catalogItem );
                asset.Write( writer );
            }
            else
            {
                const auto& catalog = std::get<Catalog>( catalogItem );
                catalog.Write( writer );
            }
        }
        template<IO::StreamReader StreamReaderT>
        static void Read( IO::BinaryReader<StreamReaderT>& reader, CatalogItem& catalogItem )
        {
            auto catalogItemType = static_cast<CatalogItemType>( reader.Read<Int16>( ) );
            if ( catalogItemType == CatalogItemType::Catalog )
            {
                Catalog catalog;
                catalog.Read( reader );
                catalogItem = catalog;
            }
            else if ( catalogItemType == CatalogItemType::Asset )
            {
                Asset asset;
                asset.Read( reader );
                catalogItem = asset;
            }
        }
        template<IO::StreamReader StreamReaderT>
        std::pair<UInt64, UInt64> ReadSessionRequestHeader( IO::BinaryReader<StreamReaderT>& reader )
        {
            auto sessionId = reader.Read<UInt64>( );
            auto requestId = reader.Read<UInt64>( );
            return { sessionId, requestId };
        }
    public:

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void GetCatalogItem( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::GetCatalogItem;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto itemId = requestReader.Read<Guid>( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    CatalogItem catalogItem;
                    auto found = session->GetCatalogItem( itemId, catalogItem );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    replyWriter.Write( found );
                    if ( found )
                    {
                        Write( replyWriter, catalogItem );
                    }
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }
        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void GetCatalogItems( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::GetCatalogItems;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto ownerId = requestReader.Read<Guid>( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    std::vector<CatalogItem> catalogItems;
                    session->GetCatalogItems( ownerId, catalogItems );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    Int32 count = static_cast<Int32>( catalogItems.size( ) );
                    replyWriter.Write( count );
                    for ( const auto& item : catalogItems )
                    {
                        Write( replyWriter, item );
                    }
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }

        }
        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void GetAllCatalogItems( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::GetAllCatalogItems;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    std::vector<CatalogItem> catalogItems;
                    session->GetCatalogItems( catalogItems );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    Int32 count = static_cast<Int32>( catalogItems.size( ) );
                    replyWriter.Write( count );
                    for ( const auto& item : catalogItems )
                    {
                        Write( replyWriter, item );
                    }
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void CreateOrRetrieveCatalog( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::CreateOrRetrieveCatalog;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto ownerId = requestReader.Read<Guid>( );
            auto catalogName = requestReader.Read<std::string>( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    auto catalog = session->CreateOrRetrieveCatalog( ownerId, catalogName );
                    session->Commit( );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    catalog.Write( replyWriter );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void CreateOrRetrieveAsset( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::CreateOrRetrieveAsset;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto ownerId = requestReader.Read<Guid>( );
            auto assetName = requestReader.Read<std::string>( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    auto asset = session->CreateOrRetrieveAsset( ownerId, assetName );
                    session->Commit( );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    asset.Write( replyWriter );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void DeleteCatalogItem( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::DeleteCatalogItem;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto itemId = requestReader.Read<Guid>( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    auto deleted = session->DeleteCatalogItem( itemId );
                    session->Commit( );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    replyWriter.Write( deleted );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }
        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void GetSensor( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::GetSensor;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto sensorId = requestReader.Read<Guid>( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    Sensor sensor;
                    if ( session->GetSensor( sensorId, sensor ) )
                    {
                        WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                        replyWriter.Write( true );
                        sensor.Write( replyWriter );
                    }
                    else
                    {
                        WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                        replyWriter.Write( false );
                    }
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }
        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void GetSensors( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::GetSensors;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto assetId = requestReader.Read<Guid>( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    std::vector<Sensor> sensors;
                    session->GetSensors( assetId, sensors );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    Int32 count = static_cast<Int32>( sensors.size( ) );
                    replyWriter.Write( count );
                    for ( const auto& item : sensors )
                    {
                        item.Write( replyWriter );
                    }
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void GetAllSensors( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::GetAllSensors;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    std::vector<Sensor> sensors;
                    session->GetSensors( sensors );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    Int32 count = static_cast<Int32>( sensors.size( ) );
                    replyWriter.Write( count );
                    for ( const auto& item : sensors )
                    {
                        item.Write( replyWriter );
                    }
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void CreateOrRetrieveSensor( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::CreateOrRetrieveSensor;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto assetId = requestReader.Read<Guid>( );
            auto sensorName = requestReader.Read<std::string>( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    auto sensor = session->CreateOrRetrieveSensor( assetId, sensorName );
                    session->Commit( );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    sensor.Write( replyWriter );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }
        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void DeleteSensor( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::DeleteSensor;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto sensorId = requestReader.Read<Guid>( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    auto deleted = session->DeleteSensor( sensorId );
                    session->Commit( );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    replyWriter.Write( deleted );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }
        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void GetSensorPoints( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::GetSensorPoints;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto sensorId = requestReader.Read<Guid>( );
            DateTime intervalStart = requestReader.Read<DateTime>( );
            DateTime intervalEnd = requestReader.Read<DateTime>( );

            auto startString = intervalStart.ToAnsiString( );
            auto endString = intervalEnd.ToAnsiString( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    std::vector<SensorPoint> points;
                    points.reserve( 1'000'000 );
                    session->GetSensorPoints( sensorId, intervalStart, intervalEnd, points );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    Int32 count = static_cast<Int32>( points.size( ) );
                    replyWriter.Write( count );
                    replyWriter.Write( points.data( ), points.size( ) * sizeof( SensorPoint ) );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void GetAllSensorPoints( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::GetAllSensorPoints;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto sensorId = requestReader.Read<Guid>( );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    std::vector<SensorPoint> points;
                    points.reserve( 1'000'000 );
                    session->GetSensorPoints( sensorId, points );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    Int32 count = static_cast<Int32>( points.size( ) );
                    replyWriter.Write( count );
                    replyWriter.Write( points.data( ), points.size( ) * sizeof( SensorPoint ) );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }
        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void StoreSensorValue( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::StoreSensorValue;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            SensorValue sensorValue;
            sensorValue.Read( requestReader );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    session->Write( sensorValue );
                    session->Commit( );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }
        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void StoreSensorPoints( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::StoreSensorPoints;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto sensorId = requestReader.Read<Guid>( );
            auto count = static_cast<UInt64>(requestReader.Read<Int32>( ));
            std::vector<SensorPoint> points;
            points.resize( count );
            requestReader.Read( points.data( ), count * sizeof( SensorPoint ) );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    session->Write( sensorId, points );
                    session->Commit( );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }
        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void ReplaceSensorPoints( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::ReplaceSensorPoints;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto sensorId = requestReader.Read<Guid>( );
            DateTime intervalStart = requestReader.Read<DateTime>( );
            DateTime intervalEnd = requestReader.Read<DateTime>( );

            auto count = static_cast<UInt64>( requestReader.Read<Int32>( ) );
            std::vector<SensorPoint> points;
            points.resize( count );
            requestReader.Read( points.data( ), count * sizeof( SensorPoint ) );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                
                SERVERSESSION_TRY
                {
                    session->DeleteValues( sensorId,intervalStart,intervalEnd );
                    session->Write( sensorId, points );
                    session->Commit( );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void GetAllSensorValues( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::GetAllSensorValues;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );

            auto* session = engine_.FindSession( sessionId );
            if ( session )
            {
                SERVERSESSION_TRY
                {
                    std::vector<SensorValue> values;
                    values.reserve( 1'000'000 );
                    session->GetSensorValues( values );
                    WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
                    Int32 count = static_cast<Int32>( values.size( ) );
                    replyWriter.Write( count );
                    replyWriter.Write( values.data( ), values.size( ) * sizeof( SensorValue ) );
                }
                SERVERSESSION_CATCH( );
            }
            else
            {
                InvalidSession( replyWriter, sessionId );
            }
        }

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void SendSensorPoints( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::SendSensorPoints;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            auto sensorId = requestReader.Read<Guid>( );
            auto count = static_cast<UInt64>( requestReader.Read<Int32>( ) );
            std::vector<SensorPoint> points;
            points.resize( count );
            requestReader.Read( points.data( ), count * sizeof( SensorPoint ) );
            WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
        }

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        void SendJSON( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            constexpr RequestReplyType ReplyType = RequestReplyType::SendJSON;
            auto [sessionId, requestId] = ReadSessionRequestHeader( requestReader );
            
            auto json = requestReader.Read<WideString>( );

            WriteReplyHeader<ReplyType>( replyWriter, sessionId, requestId );
        }

    };


    



}



#endif
