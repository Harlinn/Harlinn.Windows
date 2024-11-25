#pragma once
#ifndef __HEXENGINE_H__
#define __HEXENGINE_H__
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


#include <HExDatabase.h>
#include <HCCSync.h>

namespace Harlinn::Common::Core::Examples
{
    
    //template<typename D, typename T >
    template<typename T >
    class SessionT
    {
    public:
        using EngineType = T;
    private:
        EngineType& engine_;
        Int64 id_;
        Ese::Session eseSession_;
        Database eseDatabase_;
    public:
        SessionT( EngineType& engine, Int64 id, bool createDatabase );

        ~SessionT( )
        {
            eseDatabase_.Close( );
            eseSession_.End( );
        }

        SessionT( const SessionT& other ) = delete;
        SessionT& operator = ( const SessionT& other ) = delete;

        SessionT( SessionT&& other ) = default;
        SessionT& operator = ( SessionT&& other ) = default;

        void Close( );

        constexpr Int64 Id( ) const noexcept
        {
            return id_;
        }

        const Ese::Session& EseSession( ) const noexcept
        {
            return eseSession_;
        }

        void Commit( )
        {
            eseSession_.CommitTransaction( Ese::TransactionFlags::WaitAll );
        }
        void Rollback( )
        {
            eseSession_.Rollback( );
        }

        


    private:
        const CatalogItemTable& CatalogItems( ) const
        {
            return eseDatabase_.CatalogItems( );
        }

        const SensorTable& Sensors( ) const
        {
            return eseDatabase_.Sensors( );
        }
        const SensorValueTable& Values( ) const
        {
            return eseDatabase_.Values( );
        }
    public:

        bool CreateOrRetrieveSensor( const Guid& assetId, const std::string& sensorName, Examples::Sensor& result ) const
        {
            if ( AssetExists( assetId ) )
            {
                auto& sensors = Sensors( );
                if ( sensors.MoveTo( assetId, sensorName ) )
                {
                    sensors.Read( result );
                    sensors.SetCurrentIndex( SensorTable::PrimaryIndexName );
                    return false;
                }
                else
                {
                    result.Id = Guid::NewGuid( );
                    result.Name = sensorName;
                    result.Owner = assetId;
                    sensors.InsertSensor( result );
                    sensors.SetCurrentIndex( SensorTable::PrimaryIndexName );
                    return true;
                }
            }
            else
            {
                throw std::exception( "Unknown asset id" );
            }
        }

        Sensor CreateOrRetrieveSensor( const Guid& assetId, const std::string& sensorName ) const
        {
            Sensor result;
            CreateOrRetrieveSensor( assetId, sensorName, result );
            return result;
        }

        bool GetSensor( const Guid& ownerId, const std::string& sensorName, Sensor& result ) const
        {
            auto& sensors = Sensors( );
            if ( sensors.MoveTo( ownerId, sensorName ) )
            {
                sensors.Read( result );
                sensors.SetCurrentIndex( SensorTable::PrimaryIndexName );
                return true;
            }
            sensors.SetCurrentIndex( SensorTable::PrimaryIndexName );
            return false;
        }
        bool GetSensor( const Guid& sensorId, Sensor& result ) const
        {
            auto& sensors = Sensors( );
            if ( sensors.MoveTo( sensorId ) )
            {
                sensors.Read( result );
                return true;
            }
            return false;
        }

        bool DeleteSensor( const Guid& ownerId, const std::string& sensorName ) const
        {
            auto& sensors = Sensors( );
            if ( sensors.MoveTo( ownerId, sensorName ) )
            {
                auto sensorId = sensors.Id( );
                auto& values = Values( );
                values.Delete( sensorId );
                sensors.Delete( );
                sensors.SetCurrentIndex( SensorTable::PrimaryIndexName );
                return true;
            }
            sensors.SetCurrentIndex( SensorTable::PrimaryIndexName );
            return false;
        }
        bool DeleteSensor( const Guid& sensorId ) const
        {
            auto& sensors = Sensors( );
            if ( sensors.MoveTo( sensorId ) )
            {
                auto& values = Values( );
                values.Delete( sensorId );
                sensors.Delete( );
                return true;
            }
            return false;
        }

        void GetSensors( std::vector<Sensor>& result ) const
        {
            auto& sensors = Sensors( );
            sensors.GetSensors( result );
        }

        void GetSensors(const Guid& assetId, std::vector<Sensor>& result ) const
        {
            auto& sensors = Sensors( );
            sensors.GetSensors( assetId, result );
        }


        bool SensorExists( const Guid& sensorId ) const
        {
            auto& sensors = Sensors( );
            return sensors.MoveTo( sensorId );
        }
        bool SensorExists( const Guid& ownerId, const std::string& sensorName ) const
        {
            auto& sensors = Sensors( );
            auto result = sensors.MoveTo( ownerId, sensorName );
            sensors.SetCurrentIndex( SensorTable::PrimaryIndexName );
            return result;
        }

        bool GetSensorPoints( const Guid& sensorId, std::vector<SensorPoint>& sensorPoints ) const
        {
            if ( SensorExists( sensorId ) )
            {
                auto& values = Values( );
                values.GetSensorPoints( sensorId, sensorPoints );
                return true;
            }
            return false;
        }
        bool GetSensorPoints( const Guid& sensorId, const DateTime& startTimestamp, const DateTime& endTimestamp, std::vector<SensorPoint>& sensorPoints ) const
        {
            if ( SensorExists( sensorId ) )
            {
                auto& values = Values( );
                values.GetSensorPoints( sensorId, startTimestamp, endTimestamp, sensorPoints );
                return true;
            }
            return false;
        }
        bool GetSensorPoints( const Guid& sensorId, const DateTime& startTimestamp, std::vector<SensorPoint>& sensorPoints ) const
        {
            if ( SensorExists( sensorId ) )
            {
                auto& values = Values( );
                values.GetSensorPoints( sensorId, startTimestamp, sensorPoints );
                return true;
            }
            return false;
        }

        void GetSensorValues( std::vector<SensorValue>& sensorValues ) const
        {
            auto& values = Values( );
            values.GetSensorValues( sensorValues );
        }

        bool Write( const Guid& sensorId, const std::vector<SensorPoint>& sensorPoints ) const
        {
            if ( SensorExists( sensorId ) )
            {
                auto& values = Values( );
                values.Write( sensorId, sensorPoints );
                return true;
            }
            return false;
        }
        bool Write( const SensorValue& sensorValue ) const
        {
            if ( SensorExists( sensorValue.Sensor ) )
            {
                auto& values = Values( );
                values.Write( sensorValue );
                return true;
            }
            return false;
        }

        bool DeleteValues( const Guid& sensorId ) const
        {
            if ( SensorExists( sensorId ) )
            {
                auto& values = Values( );
                values.Delete( sensorId );
                return true;
            }
            return false;
        }

        bool DeleteValues( const Guid& sensorId, const DateTime& startTimestamp, const DateTime& endTimestamp = DateTime::MaxValue( ) ) const
        {
            if ( SensorExists( sensorId ) )
            {
                auto& values = Values( );
                values.Delete( sensorId, startTimestamp, endTimestamp );
                return true;
            }
            return false;
        }

        bool AssetExists( const Guid& assetId ) const
        {
            auto& catalogItems = CatalogItems( );
            if ( catalogItems.MoveTo( assetId ) )
            {
                return catalogItems.ItemType( ) == CatalogItemType::Asset;
            }
            return false;
        }
        bool CatalogExists( const Guid& catalogId ) const
        {
            auto& catalogItems = CatalogItems( );
            if ( catalogItems.MoveTo( catalogId ) )
            {
                return catalogItems.ItemType( ) == CatalogItemType::Catalog;
            }
            return false;
        }


        Catalog CreateOrRetrieveCatalog( const Guid& owningCatalogId, const std::string& name )
        {
            if ( owningCatalogId.empty( ) == false && CatalogExists( owningCatalogId ) == false )
            {
                throw std::exception( "Invalid catalog id" );
            }
            auto& catalogItems = CatalogItems( );
            return catalogItems.CreateOrRetrieveCatalog( owningCatalogId, name );
        }
        Asset CreateOrRetrieveAsset( const Guid& owningCatalogId, const std::string& name )
        {
            if ( CatalogExists( owningCatalogId ) == false )
            {
                throw std::exception( "Invalid catalog id" );
            }
            auto& catalogItems = CatalogItems( );
            return catalogItems.CreateOrRetrieveAsset( owningCatalogId, name );
        }

        bool GetCatalogItem( const Guid& itemId, CatalogItem& result ) const
        {
            auto& catalogItems = CatalogItems( );
            return catalogItems.GetItem( itemId, result );
        }

        void GetCatalogItems( std::vector<CatalogItem>& result ) const
        {
            auto& catalogItems = CatalogItems( );
            catalogItems.GetItems( result );
        }

        void GetCatalogItems( const Guid& owningCatalogId, std::vector<CatalogItem>& result ) const
        {
            auto& catalogItems = CatalogItems( );
            catalogItems.GetItems( owningCatalogId, result );
        }

        bool DeleteCatalogItem( const Guid& itemId ) const
        {
            auto& catalogItems = CatalogItems( );
            auto& sensors = Sensors( );
            auto& values = Values( );
            catalogItems.SetCurrentIndex( CatalogItemTable::PrimaryIndexName );
            if ( catalogItems.MoveTo( itemId ) )
            {
                auto itemType = catalogItems.ItemType( );
                switch ( itemType )
                {
                    case CatalogItemType::Catalog:
                    {
                        while ( catalogItems.MoveToFirstChild( itemId ) )
                        {
                            auto childId = catalogItems.Id( );
                            DeleteCatalogItem( childId );
                        }
                        catalogItems.SetCurrentIndex( CatalogItemTable::PrimaryIndexName );
                        if ( catalogItems.MoveTo( itemId ) )
                        {
                            catalogItems.Delete( );
                        }
                        return true;
                    }
                    break;
                    case CatalogItemType::Asset:
                    {
                        if ( sensors.FilterByOwner( itemId ) )
                        {
                            do
                            {
                                auto sensorId = sensors.Id( );
                                values.Delete( sensorId );
                                sensors.Delete( );
                            } while ( sensors.MoveNext() );
                        }
                        catalogItems.SetCurrentIndex( CatalogItemTable::PrimaryIndexName );
                        catalogItems.Delete( );
                        return true;
                    }
                    break;
                }
            }
            return false;
        }

        size_t GetSensorCount( ) const
        {
            auto& sensors = Sensors( );
            return sensors.Count( );
        }

        size_t GetCatalogItemCount( ) const
        {
            auto& catalogItems = CatalogItems( );
            return catalogItems.Count( );
        }

        size_t GetSensorValueCount( ) const
        {
            auto& values = Values( );
            return values.Count( );
        }

        [[nodiscard]] Ese::Transaction StartTransaction( ) const
        {
            return eseSession_.StartTransaction( );
        }

        void BeginTransaction( ) const
        {
            eseSession_.BeginTransaction( );
        }

        void CommitTransaction( Ese::TransactionFlags flags = Ese::TransactionFlags::None ) const
        {
            eseSession_.CommitTransaction( flags );
        }


    };

    struct EngineOptions
    {
        std::string Database;
        std::string SystemPath;
        std::string LogFilePath;
        bool Create = false;
        bool Replace = false;
        bool Unsafe = false;
        bool RunTests = false;
        UInt16 Port = 42000;
    };


    template<typename D, typename T>
    class EngineT 
    {
    public:
        using SessionType = T;
        using DerivedType = D;
    private:
        template<typename T1>
        friend class SessionT;

        Core::CriticalSection criticalSection_;
        const EngineOptions& options_;
        Int64 sessionCounter_ = 0;
        Ese::Instance instance_;
        std::unordered_map<Int64, std::unique_ptr<SessionType> > sessions_;
    public:
        EngineT( const EngineOptions& options, const char* instanceName )
            : options_( options ), instance_( instanceName )
        {
            ProcessOptions( );
        }

        SessionType* CreateSession( )
        {
            std::lock_guard lockGuard( criticalSection_ );
            if ( sessions_.size( ) == 1 && sessionCounter_ == 0 )
            {
                ++sessionCounter_;
                auto result = sessions_[1].get();
                return result;
            }
            else
            {
                auto id = ++sessionCounter_;
                auto session = std::make_unique<SessionType>( static_cast<DerivedType&>(*this), id, false );
                auto result = session.get( );
                sessions_.emplace( id, std::move( session ) );
                return result;
            }
        }
        SessionType* FindSession( Int64 sessionId ) const
        {
            std::lock_guard lockGuard( criticalSection_ );
            if ( sessionId <= sessionCounter_ )
            {
                auto it = sessions_.find( sessionId );
                if ( it != sessions_.end( ) )
                {
                    return ( *it ).second.get( );
                }
            }
            return nullptr;
        }


    private:
        Ese::Instance& Instance( )
        {
            return instance_;
        }

        const EngineOptions& Options( ) const
        {
            return options_;
        }

        void ProcessOptions( )
        {
            instance_.SetCreatePathIfNotExist( );
            instance_.SetExceptionAction( Ese::ExceptionAction::None );
            instance_.SetSystemPath( options_.SystemPath );
            instance_.SetLogFilePath( options_.LogFilePath );
            instance_.SetMaxVersionPageCount( 262144 );

            if ( options_.Create )
            {
                auto session = std::make_unique<SessionType>( static_cast<DerivedType&>(*this), 1, true );
                sessions_.emplace( 1, std::move( session ) );
            }
        }

        void RemoveSession( Int64 sessionId )
        {
            sessions_.erase( sessionId );
        }

    };

    template<typename T >
    inline SessionT<T>::SessionT( EngineType& engine, Int64 id, bool createDatabase )
        : engine_( engine ), id_( id )
    {
        auto& instance = engine_.Instance( );
        auto& options = engine_.Options( );
        eseSession_ = instance.BeginSession( );

        if ( createDatabase )
        {
            Ese::CreateDatabaseFlags createDatabaseFlags = Ese::CreateDatabaseFlags::None;
            if ( options.Replace )
            {
                createDatabaseFlags |= Ese::CreateDatabaseFlags::OverwriteExisting;
            }
            if ( options.Unsafe )
            {
                createDatabaseFlags |= Ese::CreateDatabaseFlags::RecoveryOff | Ese::CreateDatabaseFlags::ShadowingOff;
            }
            eseDatabase_ = eseSession_.CreateDatabase<Database>( options.Database, createDatabaseFlags );
        }
        else
        {
            eseSession_.AttachDatabase( options.Database );
            eseDatabase_ = eseSession_.OpenDatabase<Database>( options.Database );
        }
    }

    template< typename T >
    inline void SessionT<T>::Close( )
    {
        eseDatabase_.Close( );
        eseSession_.End( );
        engine_.RemoveSession( id_ );
    }




}

#endif