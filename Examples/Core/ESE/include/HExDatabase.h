#pragma once
#ifndef __HEXSENSORDATABASE_H__
#define __HEXSENSORDATABASE_H__
#include <HCCEse.h>
#include <HExTypes.h>

namespace Harlinn::Common::Core::Examples
{
    template<typename DerivedT>
    class OwnedTable : public Ese::Table
    {
    public:
        using Base = Ese::Table;

        static constexpr char IdColumnName[] = "Id";
        static constexpr char OwnerColumnName[] = "Owner";
        static constexpr char NameColumnName[] = "Name";
    protected:
        JET_COLUMNID idColumnId_ = 0;
        JET_COLUMNID ownerColumnId_ = 0;
        JET_COLUMNID nameColumnId_ = 0;
    public:
        constexpr OwnedTable( ) noexcept
        {
        }

        OwnedTable( JET_SESID sessionId, JET_TABLEID tableId )
            : Base( sessionId, tableId )
        {
        }
    public:
        void OnTableCreated( )
        {
            Base::OnTableCreated( );

            idColumnId_ = AddGuid( IdColumnName );
            ownerColumnId_ = AddGuid( OwnerColumnName );
            nameColumnId_ = AddText( NameColumnName );

            CreateIndex( DerivedT::PrimaryIndexName, Ese::IndexFlags::Primary, "+Id\0", 5 );
            CreateIndex( DerivedT::OwnerAndNameIndexName, Ese::IndexFlags::Unique, "+Owner\0+Name\0", 14 );
#ifdef _DEBUG
            SetCurrentIndex( DerivedT::OwnerAndNameIndexName );
#endif
            SetCurrentIndex( DerivedT::PrimaryIndexName );
        }

        void OnTableOpened( )
        {
            Base::OnTableOpened( );

            idColumnId_ = GetColumnId( IdColumnName );
            ownerColumnId_ = GetColumnId( OwnerColumnName );
            nameColumnId_ = GetColumnId( NameColumnName );

            SetCurrentIndex( DerivedT::PrimaryIndexName );
        }

        Guid Id( ) const
        {
            Guid result;
            Read( idColumnId_, result );
            return result;
        }
        void SetId( const Guid& id ) const
        {
            SetColumn( idColumnId_, id );
        }

        Guid Owner( ) const
        {
            Guid result;
            Read( ownerColumnId_, result );
            return result;
        }
        void SetOwner( const Guid& id ) const
        {
            SetColumn( ownerColumnId_, id );
        }

        std::string Name( ) const
        {
            std::string result;
            Read( nameColumnId_, result );
            return result;
        }
        void SetName( const std::string& name ) const
        {
            SetColumn( nameColumnId_, name );
        }


        bool MoveTo( const Guid& ownerId, const char* name ) const
        {
            SetCurrentIndex( DerivedT::OwnerAndNameIndexName );
            MakeKey( ownerId, Ese::KeyFlags::NewKey );
            MakeKey( name );
            auto rc = Seek( Ese::SeekFlags::Equal );
            return rc >= Ese::Result::Success;
        }

        bool MoveToFirstChild( const Guid& ownerId ) const
        {
            SetCurrentIndex( DerivedT::OwnerAndNameIndexName );
            MakeKey( ownerId, Ese::KeyFlags::NewKey );
            MakeKey( "" );
            auto rc = Seek( Ese::SeekFlags::GreaterOrEqual );
            return rc >= Ese::Result::Success && Owner() == ownerId;
        }


        bool MoveTo( const Guid& ownerId, const std::string& name ) const
        {
            return MoveTo( ownerId, name.c_str( ) );
        }

        bool MoveTo( const Guid& id ) const
        {
            MakeKey( id, Ese::KeyFlags::NewKey );
            auto rc = Seek( Ese::SeekFlags::Equal );
            return rc >= Ese::Result::Success;
        }

        bool FilterByOwner( const Guid& ownerId ) const
        {
            SetCurrentIndex( DerivedT::OwnerAndNameIndexName );
            MakeKey( ownerId, Ese::KeyFlags::NewKey );
            MakeKey( "" );
            auto rc = Seek( Ese::SeekFlags::GreaterOrEqual );
            if ( rc >= Ese::Result::Success && Owner() == ownerId )
            {
                MakeKey( ownerId, Ese::KeyFlags::NewKey | Ese::KeyFlags::FullColumnEndLimit );
                SetIndexRange( Ese::IndexRengeFlags::Inclusive | Ese::IndexRengeFlags::UpperLimit );
                return true;
            }
            return false;
        }

        size_t Count( ) const
        {
            SetSequential( );
            size_t result = 0;
            if ( MoveFirst( ) )
            {
                do
                {
                    result++;
                } while ( MoveNext() );
            }
            return result;
        }

    };

    class SensorTable : public OwnedTable<SensorTable>
    {
    public:
        using Base = OwnedTable<SensorTable>;

        static constexpr char TableName[] = "Sensor";
        static constexpr char PrimaryIndexName[] = "SensorIdx";
        static constexpr char OwnerAndNameIndexName[] = "SONIdx";
    public:
        constexpr SensorTable( ) noexcept
        {
        }
        SensorTable( JET_SESID sessionId, JET_TABLEID tableId )
            : Base( sessionId, tableId )
        {
        }

        using Base::Read;
        void Read( Sensor& sensor ) const
        {
            Read( idColumnId_, sensor.Id );
            Read( ownerColumnId_, sensor.Owner );
            Read( nameColumnId_, sensor.Name );
        }

        void ReplaceSensor( const Sensor& sensor ) const
        {
            Replace( );
            SetColumn( ownerColumnId_, sensor.Owner );
            SetColumn( nameColumnId_, sensor.Name );
            Update( );
        }

        void InsertSensor( const Sensor& sensor ) const
        {
            Insert( );
            SetColumn( idColumnId_, sensor.Id );
            SetColumn( ownerColumnId_, sensor.Owner );
            SetColumn( nameColumnId_, sensor.Name );
            Update( );
        }

        bool Write( const Sensor& sensor ) const
        {
            if ( MoveTo( sensor.Id ) )
            {
                ReplaceSensor( sensor );
                return false;
            }
            else
            {
                InsertSensor( sensor );
                return true;
            }
        }

        void GetSensors( std::vector<Sensor>& sensors ) const
        {
            sensors.clear( );
            if ( MoveFirst( ) )
            {
                do
                {
                    Read( sensors.emplace_back( ) );
                } while ( MoveNext( ) );
            }
        }
        void GetSensors(const Guid& assetId, std::vector<Sensor>& sensors ) const
        {
            sensors.clear( );
            if ( FilterByOwner( assetId ) )
            {
                do
                {
                    Read( sensors.emplace_back( ) );
                } while ( MoveNext( ) );
            }
            SetCurrentIndex( PrimaryIndexName );
        }


    };


    class CatalogItemTable : public OwnedTable<CatalogItemTable>
    {
    public:
        using Base = OwnedTable<CatalogItemTable>;

        static constexpr char TypeColumnName[] = "Type";
        static constexpr char TableName[] = "CatalogItem";
        static constexpr char PrimaryIndexName[] = "CatalogItemIdx";
        static constexpr char OwnerAndNameIndexName[] = "CONIdx";
    protected:
        JET_COLUMNID typeColumnId_ = 0;
    public:
        constexpr CatalogItemTable( ) noexcept
        {
        }
        CatalogItemTable( JET_SESID sessionId, JET_TABLEID tableId )
            : Base( sessionId, tableId )
        {
        }

        void OnTableCreated( )
        {
            Base::OnTableCreated( );
            typeColumnId_ = AddInt16( TypeColumnName );
        }

        void OnTableOpened( )
        {
            Base::OnTableOpened( );
            typeColumnId_ = GetColumnId( TypeColumnName );
        }

        CatalogItemType ItemType( ) const
        {
            Int16 result;
            Read( typeColumnId_, result );
            return static_cast<CatalogItemType>( result );
        }
        void SetItemType( CatalogItemType itemType ) const
        {
            SetColumn( typeColumnId_, static_cast<Int16>(itemType) );
        }


        using Base::Read;
    private:
        void Read( CatalogItemBase& catalogItem ) const
        {
            Read( idColumnId_, catalogItem.Id );
            Read( ownerColumnId_, catalogItem.Owner );
            Read( nameColumnId_, catalogItem.Name );
        }
    public:


        void Read( CatalogItem& catalogItem ) const
        {
            auto itemType = ItemType( );
            if ( itemType == CatalogItemType::Asset )
            {
                Asset asset;
                Read( asset );
                catalogItem = asset;
            }
            else
            {
                Catalog catalog;
                Read( catalog );
                catalogItem = catalog;
            }
        }

        void ReplaceItem( CatalogItemType expectedCatalogItemType, const CatalogItemBase& catalogItem ) const
        {
            auto itemType = ItemType( );
            if ( itemType != expectedCatalogItemType )
            {
                throw std::exception( "Type does not match" );
            }
            Replace( );
            SetOwner( catalogItem.Owner );
            SetName( catalogItem.Name );
            Update( );
        }

        void ReplaceItem( const CatalogItem& catalogItem ) const
        {
            if ( catalogItem.index( ) )
            {
                const Asset& asset = std::get<Asset>( catalogItem );
                ReplaceItem( CatalogItemType::Asset, asset );
            }
            else
            {
                const Catalog& catalog = std::get<Catalog>( catalogItem );
                ReplaceItem( CatalogItemType::Catalog, catalog );
            }
        }

        void InsertItem( CatalogItemBase& catalogItem ) const
        {
            Insert( );
            SetId( catalogItem.Id );
            SetItemType( catalogItem.Type );
            SetOwner( catalogItem.Owner );
            SetName( catalogItem.Name );
            Update( );
        }
        void InsertItem( const CatalogItem& catalogItem ) const
        {
            if ( catalogItem.index( ) )
            {
                const Asset& asset = std::get<Asset>( catalogItem );
                InsertItem( asset );
            }
            else
            {
                const Catalog& catalog = std::get<Catalog>( catalogItem );
                InsertItem( catalog );
            }
        }
        static Guid IdOf( const CatalogItem& catalogItem )
        {
            if ( catalogItem.index( ) )
            {
                const Asset& asset = std::get<Asset>( catalogItem );
                return asset.Id;
            }
            else
            {
                const Catalog& catalog = std::get<Catalog>( catalogItem );
                return catalog.Id;
            }
        }


        bool Write( const CatalogItem& catalogItem ) const
        {
            auto id = IdOf( catalogItem );
            if ( MoveTo( id ) )
            {
                ReplaceItem( catalogItem );
                return false;
            }
            else
            {
                InsertItem( catalogItem );
                return true;
            }
        }
    private:
        template<typename T>
        T CreateOrRetriveItem( const Guid& owningCatalogId, const std::string& name ) const
        {
            if ( MoveTo( owningCatalogId, name ) )
            {
                T catalogItem;
                Read( catalogItem );
                SetCurrentIndex( PrimaryIndexName );
                return catalogItem;
            }
            else
            {
                T catalogItem;
                catalogItem.Id = Guid::NewGuid( );
                catalogItem.Owner = owningCatalogId;
                catalogItem.Name = name;
                InsertItem( catalogItem );
                SetCurrentIndex( PrimaryIndexName );
                return catalogItem;
            }
        }
    public:
        Catalog CreateOrRetrieveCatalog( const Guid& owningCatalogId, const std::string& name ) const
        { 
            return CreateOrRetriveItem<Catalog>( owningCatalogId, name );
        }
        Asset CreateOrRetrieveAsset( const Guid& owningCatalogId, const std::string& name ) const
        {
            return CreateOrRetriveItem<Asset>( owningCatalogId, name );
        }

        bool GetItem( const Guid& itemId, CatalogItem& result ) const
        {
            if ( MoveTo( itemId ) )
            {
                Read( result );
                return true;
            }
            else
            {
                return false;
            }
        }


        void GetItems( std::vector<CatalogItem>& result ) const
        {
            result.clear( );
            if ( MoveFirst( ) )
            {
                do
                {
                    Read( result.emplace_back( ) );
                } while ( MoveNext( ) );
            }
        }

        

        void GetItems(const Guid& catalogId, std::vector<CatalogItem>& result ) const
        {
            result.clear( );
            if ( FilterByOwner( catalogId ) )
            {
                do
                {
                    Read( result.emplace_back( ) );
                } while ( MoveNext( ) );
            }
            SetCurrentIndex( PrimaryIndexName );
        }

        


    };



    class SensorValueTable : public Ese::Table
    {
    public:
        using Base = Ese::Table;

        static constexpr char TableName[] = "SV";
        static constexpr char PrimaryIndexName[] = "ISV";
        static constexpr char SensorColumnName[] = "S";
        static constexpr char TimestampColumnName[] = "T";
        static constexpr char FlagsColumnName[] = "F";
        static constexpr char ValueColumnName[] = "V";
    private:
        JET_COLUMNID sensorColumnId_ = 0;
        JET_COLUMNID timestampColumnId_ = 0;
        JET_COLUMNID flagsColumnId_ = 0;
        JET_COLUMNID valueColumnId_ = 0;
    public:
        constexpr SensorValueTable( ) noexcept
        {
        }

        SensorValueTable( JET_SESID sessionId, JET_TABLEID tableId )
            : Base( sessionId, tableId )
        {
            
        }
    public:
        void OnTableCreated( )
        {
            Base::OnTableCreated( );
            sensorColumnId_ = AddGuid( SensorColumnName );
            timestampColumnId_ = AddInt64( TimestampColumnName );
            flagsColumnId_ = AddUInt64( FlagsColumnName );
            valueColumnId_ = AddDouble( ValueColumnName );
            CreateIndex( PrimaryIndexName, Ese::IndexFlags::Primary, "+S\0+T\0", 7 );
        }

        void OnTableOpened( )
        {
            Base::OnTableOpened( );
            sensorColumnId_ = GetColumnId( SensorColumnName );
            timestampColumnId_ = GetColumnId( TimestampColumnName );
            flagsColumnId_ = GetColumnId( FlagsColumnName );
            valueColumnId_ = GetColumnId( ValueColumnName );

            SetCurrentIndex( PrimaryIndexName );
        }
    public:
        Guid Sensor( ) const
        {
            Guid result;
            Read( sensorColumnId_, result );
            return result;
        }
        void SetSensor( const Guid& sensorId ) const
        {
            SetColumn( sensorColumnId_, sensorId );
        }

        DateTime Timestamp( ) const
        {
            Int64 result;
            Read( timestampColumnId_, result );
            return DateTime(result);
        }
        void SetTimestamp( const DateTime& timestamp ) const
        {
            SetColumn( timestampColumnId_, timestamp.Ticks() );
        }

        UInt64 Flags( ) const
        {
            UInt64 result;
            Read( flagsColumnId_, result );
            return result;
        }
        void SetFlags( UInt64 flags ) const
        {
            SetColumn( flagsColumnId_, flags );
        }

        double Value( ) const
        {
            double result;
            Read( valueColumnId_, result );
            return result;
        }
        void SetValue( double value ) const
        {
            SetColumn( valueColumnId_, value );
        }

        using Base::Read;
        void Read( SensorValue& value ) const
        {
            Read( sensorColumnId_, value.Sensor );
            Int64 timestamp = 0;
            Read( timestampColumnId_, timestamp );
            value.Timestamp = DateTime( timestamp );
            Read( flagsColumnId_, value.Flags );
            Read( valueColumnId_, value.Value );
        }

        void Read( SensorPoint& sensorPoint ) const
        {
            Int64 timestamp = 0;
            Read( timestampColumnId_, timestamp );
            sensorPoint.Timestamp = DateTime( timestamp );
            Read( flagsColumnId_, sensorPoint.Flags );
            Read( valueColumnId_, sensorPoint.Value );
        }

        void ReplaceValue( const SensorValue& value ) const
        {
            Replace( );
            SetColumn( flagsColumnId_, value.Flags );
            SetColumn( valueColumnId_, value.Value );
            Update( );
        }
        void InsertValue( const SensorValue& value ) const
        {
            Insert( );
            SetColumn( sensorColumnId_, value.Sensor );
            Int64 timestamp = value.Timestamp.Ticks( );
            SetColumn( timestampColumnId_, timestamp );
            SetColumn( flagsColumnId_, value.Flags );
            SetColumn( valueColumnId_, value.Value );
            Update( );
        }

        bool Write( const SensorValue& value ) const
        {
            if ( MoveTo( value.Sensor, value.Timestamp ) )
            {
                ReplaceValue( value );
                return false;
            }
            else
            {
                InsertValue( value );
                return true;
            }
        }

        void ReplaceValue( const SensorPoint& point ) const
        {
            Replace( );
            SetColumn( flagsColumnId_, point.Flags );
            SetColumn( valueColumnId_, point.Value );
            Update( );
        }
        void InsertValue( const Guid& sensorId, const SensorPoint& point ) const
        {
            Insert( );
            SetColumn( sensorColumnId_, sensorId );
            Int64 timestamp = point.Timestamp.Ticks( );
            SetColumn( timestampColumnId_, timestamp );
            SetColumn( flagsColumnId_, point.Flags );
            SetColumn( valueColumnId_, point.Value );
            Update( );
        }

        bool Write(const Guid& sensorId, const SensorPoint& point ) const
        {
            if ( MoveTo( sensorId, point.Timestamp ) )
            {
                ReplaceValue( point );
                return false;
            }
            else
            {
                InsertValue( sensorId, point );
                return true;
            }
        }


        bool MoveTo( const Guid& sensorId, const DateTime& timestamp, bool exactMatchRequired = true ) const
        {
            MakeKey( sensorId, Ese::KeyFlags::NewKey );
            MakeKey( timestamp.Ticks() );
            auto rc = Seek( exactMatchRequired? Ese::SeekFlags::Equal : Ese::SeekFlags::GreaterOrEqual );
            return rc >= Ese::Result::Success && Sensor() == sensorId;
        }


        bool Filter( const Guid& sensorId ) const
        {
            MakeKey( sensorId, Ese::KeyFlags::NewKey );
            auto rc = Seek( Ese::SeekFlags::GreaterOrEqual );
            if ( rc >= Ese::Result::Success && Sensor() == sensorId )
            {
                MakeKey( sensorId, Ese::KeyFlags::NewKey );
                MakeKey( DateTime::MaxValue( ).Ticks() );
                SetIndexRange( Ese::IndexRengeFlags::UpperLimit );
                return true;
            }
            else
            {
                return false;
            }
        }


        bool Filter( const Guid& sensorId, const DateTime& startTimestamp, const DateTime& endTimestamp ) const
        {
            MakeKey( sensorId, Ese::KeyFlags::NewKey );
            MakeKey( startTimestamp.Ticks() );
            auto rc = Seek( Ese::SeekFlags::LessOrEqual );
            if ( rc >= Ese::Result::Success && Sensor() == sensorId )
            {
                MakeKey( sensorId, Ese::KeyFlags::NewKey );
                MakeKey( endTimestamp.Ticks( ) );
                SetIndexRange( Ese::IndexRengeFlags::UpperLimit );
                return true;
            }
            else
            {
                return false;
            }
        }
    public:
        void GetSensorValues( std::vector<SensorValue>& sensorValues ) const
        {
            sensorValues.clear( );
            if ( MoveFirst( ) )
            {
                do
                {
                    Read( sensorValues.emplace_back( ) );
                } while ( MoveNext( ) );
            }
        }

        void GetSensorPoints( const Guid& sensorId, std::vector<SensorPoint>& sensorPoints ) const
        {
            sensorPoints.clear( );
            if ( Filter( sensorId ) )
            {
                do
                {
                    Read( sensorPoints.emplace_back() );
                } while ( MoveNext( ) );
            }
        }

        void GetSensorPoints( const Guid& sensorId, const DateTime& startTimestamp, const DateTime& endTimestamp, std::vector<SensorPoint>& sensorPoints ) const
        {
            /*
            sensorPoints.clear( );
            if ( MoveTo( sensorId, startTimestamp, false ) )
            {
                do
                {
                    Read( sensorPoints.emplace_back( ) );
                } while ( MoveNext( ) && Sensor() == sensorId && Timestamp() < endTimestamp );
            }
            */

            if ( Filter( sensorId, startTimestamp, endTimestamp ) )
            {
                do
                {
                    Read( sensorPoints.emplace_back( ) );
                } while ( MoveNext( ) );
            }
            
        }
        void GetSensorPoints( const Guid& sensorId, const DateTime& startTimestamp, std::vector<SensorPoint>& sensorPoints ) const
        {
            GetSensorPoints( sensorId, startTimestamp, DateTime::MaxValue( ), sensorPoints );
        }


        void Write( const Guid& sensorId, const std::vector<SensorPoint>& sensorPoints ) const
        {
            for ( const auto& sensorPoint : sensorPoints )
            {
                Write( sensorId, sensorPoint );
            }
        }

        using Base::Delete;
        void Delete( const Guid& sensorId ) const
        {
            if ( Filter( sensorId ) )
            {
                do
                {
                    Delete( );
                } while ( MoveNext() );
            }
        }
        void Delete( const Guid& sensorId, const DateTime& startTimestamp, const DateTime& endTimestamp = DateTime::MaxValue() ) const
        {
            if ( Filter( sensorId, startTimestamp, endTimestamp ) )
            {
                do
                {
                    Delete( );
                } while ( MoveNext( ) );
            }
        }

        size_t Count( ) const
        {
            SetSequential( );
            size_t result = 0;
            if ( MoveFirst( ) )
            {
                do
                {
                    result++;
                } while ( MoveNext( ) );
            }
            return result;
        }

    };

    

    class Database : public Ese::Database
    {
    public:
        using Base = Ese::Database;
    private:
        CatalogItemTable catalogItemTable_;
        SensorTable sensorTable_;
        SensorValueTable sensorValueTable_;
    public:
        constexpr Database( ) noexcept
        {
        }
        explicit Database( JET_SESID sessionId, JET_DBID database )
            : Base( sessionId, database )
        {
        }

        void OnDatabaseCreated( )
        {
            BeginTransaction( );
            catalogItemTable_ = CreateTable<CatalogItemTable>( CatalogItemTable::TableName );
            sensorTable_ = CreateTable<SensorTable>( SensorTable::TableName );
            sensorValueTable_ = CreateTable<SensorValueTable>( SensorValueTable::TableName );
            CommitTransaction( );
        }
        void OnDatabaseOpened( )
        {
            catalogItemTable_ = OpenTable<CatalogItemTable>( CatalogItemTable::TableName, Ese::OpenTableFlags::Updatable );
            sensorTable_ = OpenTable<SensorTable>( SensorTable::TableName, Ese::OpenTableFlags::Updatable );
            sensorValueTable_ = OpenTable<SensorValueTable>( SensorValueTable::TableName, Ese::OpenTableFlags::Updatable );
        }

        void Close( )
        {
            catalogItemTable_.Close( );
            sensorTable_.Close( );
            sensorValueTable_.Close( );
            Base::Close( );
        }

        const CatalogItemTable& CatalogItems( ) const
        {
            return catalogItemTable_;
        }

        const SensorTable& Sensors( ) const
        {
            return sensorTable_;
        }
        const SensorValueTable& Values( ) const
        {
            return sensorValueTable_;
        }

    
        
    };

}


#endif