#pragma once
#ifndef DATA_DATATYPES_H_
#define DATA_DATATYPES_H_

#include "Data/Enums.h"
#include <HODBC.h>


namespace Barrelman::Data
{
    using namespace Harlinn;
    using namespace Harlinn::ODBC;
    using namespace Harlinn::Common::Core;

    class BaseColumnData
    {
    public:
        virtual ~BaseColumnData( ) = default;
        virtual Kind GetKind() const = 0;
    protected:
        static void ThrowBoundsExceededException( )
        {
            throw Exception( L"Bounds exceeded." );
        }
        template<size_t N>
        static void Assign( const WideString& str, std::array<wchar_t, N>& destination, SQLLEN& lengthOrNullIndicator )
        {
            auto strLength = str.Length( );
            if ( strLength > N - 1 )
            {
                ThrowBoundsExceededException( );
            }
            wmemcpy_s( destination.data( ), N, str.data( ), strLength );
            lengthOrNullIndicator = static_cast< SQLLEN >( strLength );
        }
        static void Assign( const WideString& str, WideString& destination, SQLLEN& lengthOrNullIndicator )
        {
            auto strLength = str.Length( );
            destination = str;
            lengthOrNullIndicator = static_cast< SQLLEN >( strLength );
        }
        template<size_t N>
        static void Assign( const std::vector<Byte>& data, std::array<Byte, N>& destination, SQLLEN& lengthOrNullIndicator )
        {
            auto dataLength = data.size( );
            if ( dataLength > N )
            {
                ThrowBoundsExceededException( );
            }
            memcpy_s( destination.data( ), N, data.data( ), dataLength );
            lengthOrNullIndicator = static_cast< SQLLEN >( dataLength );
        }
        static void Assign( const std::vector<Byte>& data, std::vector<Byte>& destination, SQLLEN& lengthOrNullIndicator )
        {
            auto dataLength = data.size( );
            destination = data;
            lengthOrNullIndicator = static_cast< SQLLEN >( dataLength );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, bool* value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindBooleanColumn( fieldId, reinterpret_cast< Byte* >( value ), lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, SByte * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindSByteColumn( fieldId, value, lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Byte * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindByteColumn( fieldId, value, lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Int16 * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindInt16Column( fieldId, value, lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, UInt16 * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindUInt16Column( fieldId, value, lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Int32 * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindInt32Column( fieldId, value, lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, UInt32 * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindUInt32Column( fieldId, value, lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Int64 * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindInt64Column( fieldId, value, lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, UInt64 * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindUInt64Column( fieldId, value, lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, float* value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindSingleColumn( fieldId, value, lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, double* value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindDoubleColumn( fieldId, value, lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Currency * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( value ), lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, DateTime * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( value ), lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, TimeSpan * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( value ), lengthOrNullIndicator );
        }
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Guid * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindGuidColumn( fieldId, value, lengthOrNullIndicator );
        }
        template<typename T>
            requires std::is_enum_v<T>
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, T * value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            using IntegerType = std::underlying_type_t<T>;
            Bind( statement, fieldId, reinterpret_cast< IntegerType* >( value ), lengthOrNullIndicator );
        }
        template<size_t N>
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, std::array<wchar_t, N>*value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindColumn( fieldId, NativeType::WideChar, value->data( ), static_cast< SQLLEN >( N * sizeof( wchar_t ) ), lengthOrNullIndicator );
        }
        template<size_t N>
        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, std::array<Byte, N>*value, SQLLEN * lengthOrNullIndicator = nullptr )
        {
            statement.BindColumn( fieldId, NativeType::Binary, value->data( ), static_cast< SQLLEN >( N ), lengthOrNullIndicator );
        }
    };

    class AircraftTypeColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name]";
        static constexpr std::wstring_view ViewName = L"AircraftTypeView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;

        AircraftTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AircraftType;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class AisMessageColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid aisTransceiver_;
        DateTime receivedTimestamp_;
        Int64 messageSequenceNumber_ = 0;
        Int32 repeat_ = 0;
        Guid mmsi_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi]";
        static constexpr std::wstring_view ViewName = L"AisMessageView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT AISTRANSCEIVER_FIELD_ID = 3;
        static constexpr SQLUSMALLINT RECEIVEDTIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT MESSAGESEQUENCENUMBER_FIELD_ID = 5;
        static constexpr SQLUSMALLINT REPEAT_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MMSI_FIELD_ID = 7;

        AisMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisMessage;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid AisTransceiver( ) const
        {
            return aisTransceiver_;
        }
        void SetAisTransceiver( const Guid& aisTransceiver )
        {
            aisTransceiver_ = aisTransceiver;
        }
        DateTime ReceivedTimestamp( ) const
        {
            return receivedTimestamp_;
        }
        void SetReceivedTimestamp( const DateTime& receivedTimestamp )
        {
            receivedTimestamp_ = receivedTimestamp;
        }
        Int64 MessageSequenceNumber( ) const
        {
            return messageSequenceNumber_;
        }
        void SetMessageSequenceNumber( Int64 messageSequenceNumber )
        {
            messageSequenceNumber_ = messageSequenceNumber;
        }
        Int32 Repeat( ) const
        {
            return repeat_;
        }
        void SetRepeat( Int32 repeat )
        {
            repeat_ = repeat;
        }
        Guid Mmsi( ) const
        {
            return mmsi_;
        }
        void SetMmsi( const Guid& mmsi )
        {
            mmsi_ = mmsi;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, AISTRANSCEIVER_FIELD_ID, &aisTransceiver_);
            Bind(statement, RECEIVEDTIMESTAMP_FIELD_ID, &receivedTimestamp_);
            Bind(statement, MESSAGESEQUENCENUMBER_FIELD_ID, &messageSequenceNumber_);
            Bind(statement, REPEAT_FIELD_ID, &repeat_);
            Bind(statement, MMSI_FIELD_ID, &mmsi_);
        }

    };

    class AidToNavigationReportMessageColumnData : public AisMessageColumnData
    {
        Data::NavigationalAidType navigationalAidType_ = Data::NavigationalAidType::NotSpecified;
        std::array<wchar_t,101> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Data::PositionAccuracy positionAccuracy_ = Data::PositionAccuracy::Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        Int32 dimensionToBow_ = 0;
        Int32 dimensionToStern_ = 0;
        Int32 dimensionToPort_ = 0;
        Int32 dimensionToStarboard_ = 0;
        Data::PositionFixType positionFixType_ = Data::PositionFixType::Undefined1;
        Int32 timestamp_ = 0;
        bool offPosition_ = false;
        Int32 regionalReserved_ = 0;
        Data::Raim raim_ = Data::Raim::NotInUse;
        bool virtualAid_ = false;
        bool assigned_ = false;
        Int32 spare_ = 0;
        std::array<wchar_t,101> nameExtension_ = {};
        SQLLEN nameExtensionLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[NavigationalAidType],[Name],[PositionAccuracy],[Longitude],[Latitude],[DimensionToBow],[DimensionToStern],[DimensionToPort],[DimensionToStarboard],[PositionFixType],[Timestamp],[OffPosition],[RegionalReserved],[Raim],[VirtualAid],[Assigned],[Spare],[NameExtension]";
        static constexpr std::wstring_view ViewName = L"AidToNavigationReportMessageView";

        static constexpr SQLUSMALLINT NAVIGATIONALAIDTYPE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 9;
        static constexpr SQLUSMALLINT POSITIONACCURACY_FIELD_ID = 10;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT DIMENSIONTOBOW_FIELD_ID = 13;
        static constexpr SQLUSMALLINT DIMENSIONTOSTERN_FIELD_ID = 14;
        static constexpr SQLUSMALLINT DIMENSIONTOPORT_FIELD_ID = 15;
        static constexpr SQLUSMALLINT DIMENSIONTOSTARBOARD_FIELD_ID = 16;
        static constexpr SQLUSMALLINT POSITIONFIXTYPE_FIELD_ID = 17;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 18;
        static constexpr SQLUSMALLINT OFFPOSITION_FIELD_ID = 19;
        static constexpr SQLUSMALLINT REGIONALRESERVED_FIELD_ID = 20;
        static constexpr SQLUSMALLINT RAIM_FIELD_ID = 21;
        static constexpr SQLUSMALLINT VIRTUALAID_FIELD_ID = 22;
        static constexpr SQLUSMALLINT ASSIGNED_FIELD_ID = 23;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 24;
        static constexpr SQLUSMALLINT NAMEEXTENSION_FIELD_ID = 25;

        AidToNavigationReportMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AidToNavigationReportMessage;
        }

        Data::NavigationalAidType NavigationalAidType( ) const
        {
            return navigationalAidType_;
        }
        void SetNavigationalAidType( Data::NavigationalAidType navigationalAidType )
        {
            navigationalAidType_ = navigationalAidType;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Data::PositionAccuracy PositionAccuracy( ) const
        {
            return positionAccuracy_;
        }
        void SetPositionAccuracy( Data::PositionAccuracy positionAccuracy )
        {
            positionAccuracy_ = positionAccuracy;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        Int32 DimensionToBow( ) const
        {
            return dimensionToBow_;
        }
        void SetDimensionToBow( Int32 dimensionToBow )
        {
            dimensionToBow_ = dimensionToBow;
        }
        Int32 DimensionToStern( ) const
        {
            return dimensionToStern_;
        }
        void SetDimensionToStern( Int32 dimensionToStern )
        {
            dimensionToStern_ = dimensionToStern;
        }
        Int32 DimensionToPort( ) const
        {
            return dimensionToPort_;
        }
        void SetDimensionToPort( Int32 dimensionToPort )
        {
            dimensionToPort_ = dimensionToPort;
        }
        Int32 DimensionToStarboard( ) const
        {
            return dimensionToStarboard_;
        }
        void SetDimensionToStarboard( Int32 dimensionToStarboard )
        {
            dimensionToStarboard_ = dimensionToStarboard;
        }
        Data::PositionFixType PositionFixType( ) const
        {
            return positionFixType_;
        }
        void SetPositionFixType( Data::PositionFixType positionFixType )
        {
            positionFixType_ = positionFixType;
        }
        Int32 Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( Int32 timestamp )
        {
            timestamp_ = timestamp;
        }
        bool OffPosition( ) const
        {
            return offPosition_;
        }
        void SetOffPosition( bool offPosition )
        {
            offPosition_ = offPosition;
        }
        Int32 RegionalReserved( ) const
        {
            return regionalReserved_;
        }
        void SetRegionalReserved( Int32 regionalReserved )
        {
            regionalReserved_ = regionalReserved;
        }
        Data::Raim Raim( ) const
        {
            return raim_;
        }
        void SetRaim( Data::Raim raim )
        {
            raim_ = raim;
        }
        bool VirtualAid( ) const
        {
            return virtualAid_;
        }
        void SetVirtualAid( bool virtualAid )
        {
            virtualAid_ = virtualAid;
        }
        bool Assigned( ) const
        {
            return assigned_;
        }
        void SetAssigned( bool assigned )
        {
            assigned_ = assigned;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        std::wstring_view NameExtension( ) const
        {
            if(nameExtensionLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(nameExtension_.data(),static_cast<size_t>( nameExtensionLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetNameExtension( const WideString& nameExtension )
        {
            Assign(nameExtension, nameExtension_, nameExtensionLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAVIGATIONALAIDTYPE_FIELD_ID, &navigationalAidType_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, POSITIONACCURACY_FIELD_ID, &positionAccuracy_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, DIMENSIONTOBOW_FIELD_ID, &dimensionToBow_);
            Bind(statement, DIMENSIONTOSTERN_FIELD_ID, &dimensionToStern_);
            Bind(statement, DIMENSIONTOPORT_FIELD_ID, &dimensionToPort_);
            Bind(statement, DIMENSIONTOSTARBOARD_FIELD_ID, &dimensionToStarboard_);
            Bind(statement, POSITIONFIXTYPE_FIELD_ID, &positionFixType_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, OFFPOSITION_FIELD_ID, &offPosition_);
            Bind(statement, REGIONALRESERVED_FIELD_ID, &regionalReserved_);
            Bind(statement, RAIM_FIELD_ID, &raim_);
            Bind(statement, VIRTUALAID_FIELD_ID, &virtualAid_);
            Bind(statement, ASSIGNED_FIELD_ID, &assigned_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, NAMEEXTENSION_FIELD_ID, &nameExtension_, &nameExtensionLengthOrNullIndicator_);
        }

    };

    class AisAddressedSafetyRelatedMessageColumnData : public AisMessageColumnData
    {
        Int32 sequenceNumber_ = 0;
        Guid destinationMmsi_;
        bool retransmitFlag_ = false;
        Int32 spare_ = 0;
        std::array<wchar_t,101> text_ = {};
        SQLLEN textLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[SequenceNumber],[DestinationMmsi],[RetransmitFlag],[Spare],[Text]";
        static constexpr std::wstring_view ViewName = L"AisAddressedSafetyRelatedMessageView";

        static constexpr SQLUSMALLINT SEQUENCENUMBER_FIELD_ID = 8;
        static constexpr SQLUSMALLINT DESTINATIONMMSI_FIELD_ID = 9;
        static constexpr SQLUSMALLINT RETRANSMITFLAG_FIELD_ID = 10;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT TEXT_FIELD_ID = 12;

        AisAddressedSafetyRelatedMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisAddressedSafetyRelatedMessage;
        }

        Int32 SequenceNumber( ) const
        {
            return sequenceNumber_;
        }
        void SetSequenceNumber( Int32 sequenceNumber )
        {
            sequenceNumber_ = sequenceNumber;
        }
        Guid DestinationMmsi( ) const
        {
            return destinationMmsi_;
        }
        void SetDestinationMmsi( const Guid& destinationMmsi )
        {
            destinationMmsi_ = destinationMmsi;
        }
        bool RetransmitFlag( ) const
        {
            return retransmitFlag_;
        }
        void SetRetransmitFlag( bool retransmitFlag )
        {
            retransmitFlag_ = retransmitFlag;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        std::wstring_view Text( ) const
        {
            if(textLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(text_.data(),static_cast<size_t>( textLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetText( const WideString& text )
        {
            Assign(text, text_, textLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, SEQUENCENUMBER_FIELD_ID, &sequenceNumber_);
            Bind(statement, DESTINATIONMMSI_FIELD_ID, &destinationMmsi_);
            Bind(statement, RETRANSMITFLAG_FIELD_ID, &retransmitFlag_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, TEXT_FIELD_ID, &text_, &textLengthOrNullIndicator_);
        }

    };

    class AisBaseStationReportMessageColumnData : public AisMessageColumnData
    {
        DateTime timestamp_;
        Data::PositionAccuracy positionAccuracy_ = Data::PositionAccuracy::Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        Data::PositionFixType positionFixType_ = Data::PositionFixType::Undefined1;
        Int32 spare_ = 0;
        Data::Raim raim_ = Data::Raim::NotInUse;
        Int32 radioStatus_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[Timestamp],[PositionAccuracy],[Longitude],[Latitude],[PositionFixType],[Spare],[Raim],[RadioStatus]";
        static constexpr std::wstring_view ViewName = L"AisBaseStationReportMessageView";

        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 8;
        static constexpr SQLUSMALLINT POSITIONACCURACY_FIELD_ID = 9;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT POSITIONFIXTYPE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT RAIM_FIELD_ID = 14;
        static constexpr SQLUSMALLINT RADIOSTATUS_FIELD_ID = 15;

        AisBaseStationReportMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisBaseStationReportMessage;
        }

        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::PositionAccuracy PositionAccuracy( ) const
        {
            return positionAccuracy_;
        }
        void SetPositionAccuracy( Data::PositionAccuracy positionAccuracy )
        {
            positionAccuracy_ = positionAccuracy;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        Data::PositionFixType PositionFixType( ) const
        {
            return positionFixType_;
        }
        void SetPositionFixType( Data::PositionFixType positionFixType )
        {
            positionFixType_ = positionFixType;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        Data::Raim Raim( ) const
        {
            return raim_;
        }
        void SetRaim( Data::Raim raim )
        {
            raim_ = raim;
        }
        Int32 RadioStatus( ) const
        {
            return radioStatus_;
        }
        void SetRadioStatus( Int32 radioStatus )
        {
            radioStatus_ = radioStatus;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, POSITIONACCURACY_FIELD_ID, &positionAccuracy_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, POSITIONFIXTYPE_FIELD_ID, &positionFixType_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, RAIM_FIELD_ID, &raim_);
            Bind(statement, RADIOSTATUS_FIELD_ID, &radioStatus_);
        }

    };

    class AisBinaryAcknowledgeMessageColumnData : public AisMessageColumnData
    {
        Int32 spare_ = 0;
        Int32 sequenceNumber1_ = 0;
        Guid mmsi1_;
        Int32 sequenceNumber2_ = 0;
        Guid mmsi2_;
        Int32 sequenceNumber3_ = 0;
        Guid mmsi3_;
        Int32 sequenceNumber4_ = 0;
        Guid mmsi4_;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[Spare],[SequenceNumber1],[Mmsi1],[SequenceNumber2],[Mmsi2],[SequenceNumber3],[Mmsi3],[SequenceNumber4],[Mmsi4]";
        static constexpr std::wstring_view ViewName = L"AisBinaryAcknowledgeMessageView";

        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SEQUENCENUMBER1_FIELD_ID = 9;
        static constexpr SQLUSMALLINT MMSI1_FIELD_ID = 10;
        static constexpr SQLUSMALLINT SEQUENCENUMBER2_FIELD_ID = 11;
        static constexpr SQLUSMALLINT MMSI2_FIELD_ID = 12;
        static constexpr SQLUSMALLINT SEQUENCENUMBER3_FIELD_ID = 13;
        static constexpr SQLUSMALLINT MMSI3_FIELD_ID = 14;
        static constexpr SQLUSMALLINT SEQUENCENUMBER4_FIELD_ID = 15;
        static constexpr SQLUSMALLINT MMSI4_FIELD_ID = 16;

        AisBinaryAcknowledgeMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisBinaryAcknowledgeMessage;
        }

        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        Int32 SequenceNumber1( ) const
        {
            return sequenceNumber1_;
        }
        void SetSequenceNumber1( Int32 sequenceNumber1 )
        {
            sequenceNumber1_ = sequenceNumber1;
        }
        Guid Mmsi1( ) const
        {
            return mmsi1_;
        }
        void SetMmsi1( const Guid& mmsi1 )
        {
            mmsi1_ = mmsi1;
        }
        Int32 SequenceNumber2( ) const
        {
            return sequenceNumber2_;
        }
        void SetSequenceNumber2( Int32 sequenceNumber2 )
        {
            sequenceNumber2_ = sequenceNumber2;
        }
        Guid Mmsi2( ) const
        {
            return mmsi2_;
        }
        void SetMmsi2( const Guid& mmsi2 )
        {
            mmsi2_ = mmsi2;
        }
        Int32 SequenceNumber3( ) const
        {
            return sequenceNumber3_;
        }
        void SetSequenceNumber3( Int32 sequenceNumber3 )
        {
            sequenceNumber3_ = sequenceNumber3;
        }
        Guid Mmsi3( ) const
        {
            return mmsi3_;
        }
        void SetMmsi3( const Guid& mmsi3 )
        {
            mmsi3_ = mmsi3;
        }
        Int32 SequenceNumber4( ) const
        {
            return sequenceNumber4_;
        }
        void SetSequenceNumber4( Int32 sequenceNumber4 )
        {
            sequenceNumber4_ = sequenceNumber4;
        }
        Guid Mmsi4( ) const
        {
            return mmsi4_;
        }
        void SetMmsi4( const Guid& mmsi4 )
        {
            mmsi4_ = mmsi4;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, SEQUENCENUMBER1_FIELD_ID, &sequenceNumber1_);
            Bind(statement, MMSI1_FIELD_ID, &mmsi1_);
            Bind(statement, SEQUENCENUMBER2_FIELD_ID, &sequenceNumber2_);
            Bind(statement, MMSI2_FIELD_ID, &mmsi2_);
            Bind(statement, SEQUENCENUMBER3_FIELD_ID, &sequenceNumber3_);
            Bind(statement, MMSI3_FIELD_ID, &mmsi3_);
            Bind(statement, SEQUENCENUMBER4_FIELD_ID, &sequenceNumber4_);
            Bind(statement, MMSI4_FIELD_ID, &mmsi4_);
        }

    };

    class AisBinaryAddressedMessageColumnData : public AisMessageColumnData
    {
        Int32 sequenceNumber_ = 0;
        Guid destinationMmsi_;
        bool retransmitFlag_ = false;
        Int32 spare_ = 0;
        Int32 designatedAreaCode_ = 0;
        Int32 functionalId_ = 0;
        WideString data_;
        SQLLEN dataLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[SequenceNumber],[DestinationMmsi],[RetransmitFlag],[Spare],[DesignatedAreaCode],[FunctionalId],[Data]";
        static constexpr std::wstring_view ViewName = L"AisBinaryAddressedMessageView";

        static constexpr SQLUSMALLINT SEQUENCENUMBER_FIELD_ID = 8;
        static constexpr SQLUSMALLINT DESTINATIONMMSI_FIELD_ID = 9;
        static constexpr SQLUSMALLINT RETRANSMITFLAG_FIELD_ID = 10;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT DESIGNATEDAREACODE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT FUNCTIONALID_FIELD_ID = 13;
        static constexpr SQLUSMALLINT DATA_FIELD_ID = 14;

        AisBinaryAddressedMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisBinaryAddressedMessage;
        }

        Int32 SequenceNumber( ) const
        {
            return sequenceNumber_;
        }
        void SetSequenceNumber( Int32 sequenceNumber )
        {
            sequenceNumber_ = sequenceNumber;
        }
        Guid DestinationMmsi( ) const
        {
            return destinationMmsi_;
        }
        void SetDestinationMmsi( const Guid& destinationMmsi )
        {
            destinationMmsi_ = destinationMmsi;
        }
        bool RetransmitFlag( ) const
        {
            return retransmitFlag_;
        }
        void SetRetransmitFlag( bool retransmitFlag )
        {
            retransmitFlag_ = retransmitFlag;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        Int32 DesignatedAreaCode( ) const
        {
            return designatedAreaCode_;
        }
        void SetDesignatedAreaCode( Int32 designatedAreaCode )
        {
            designatedAreaCode_ = designatedAreaCode;
        }
        Int32 FunctionalId( ) const
        {
            return functionalId_;
        }
        void SetFunctionalId( Int32 functionalId )
        {
            functionalId_ = functionalId;
        }
        const WideString& Data( ) const
        {
            return data_;
        }
        void SetData( const WideString& data )
        {
            Assign(data, data_, dataLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, SEQUENCENUMBER_FIELD_ID, &sequenceNumber_);
            Bind(statement, DESTINATIONMMSI_FIELD_ID, &destinationMmsi_);
            Bind(statement, RETRANSMITFLAG_FIELD_ID, &retransmitFlag_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, DESIGNATEDAREACODE_FIELD_ID, &designatedAreaCode_);
            Bind(statement, FUNCTIONALID_FIELD_ID, &functionalId_);
        }

    };

    class AisBinaryBroadcastMessageColumnData : public AisMessageColumnData
    {
        Int32 spare_ = 0;
        Int32 designatedAreaCode_ = 0;
        Int32 functionalId_ = 0;
        WideString data_;
        SQLLEN dataLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[Spare],[DesignatedAreaCode],[FunctionalId],[Data]";
        static constexpr std::wstring_view ViewName = L"AisBinaryBroadcastMessageView";

        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT DESIGNATEDAREACODE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT FUNCTIONALID_FIELD_ID = 10;
        static constexpr SQLUSMALLINT DATA_FIELD_ID = 11;

        AisBinaryBroadcastMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisBinaryBroadcastMessage;
        }

        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        Int32 DesignatedAreaCode( ) const
        {
            return designatedAreaCode_;
        }
        void SetDesignatedAreaCode( Int32 designatedAreaCode )
        {
            designatedAreaCode_ = designatedAreaCode;
        }
        Int32 FunctionalId( ) const
        {
            return functionalId_;
        }
        void SetFunctionalId( Int32 functionalId )
        {
            functionalId_ = functionalId;
        }
        const WideString& Data( ) const
        {
            return data_;
        }
        void SetData( const WideString& data )
        {
            Assign(data, data_, dataLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, DESIGNATEDAREACODE_FIELD_ID, &designatedAreaCode_);
            Bind(statement, FUNCTIONALID_FIELD_ID, &functionalId_);
        }

    };

    class AisDataLinkManagementMessageColumnData : public AisMessageColumnData
    {
        Int32 spare_ = 0;
        Int32 offset1_ = 0;
        Int32 reservedSlots1_ = 0;
        Int32 timeout1_ = 0;
        Int32 increment1_ = 0;
        Int32 offset2_ = 0;
        Int32 reservedSlots2_ = 0;
        Int32 timeout2_ = 0;
        Int32 increment2_ = 0;
        Int32 offset3_ = 0;
        Int32 reservedSlots3_ = 0;
        Int32 timeout3_ = 0;
        Int32 increment3_ = 0;
        Int32 offset4_ = 0;
        Int32 reservedSlots4_ = 0;
        Int32 timeout4_ = 0;
        Int32 increment4_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[Spare],[Offset1],[ReservedSlots1],[Timeout1],[Increment1],[Offset2],[ReservedSlots2],[Timeout2],[Increment2],[Offset3],[ReservedSlots3],[Timeout3],[Increment3],[Offset4],[ReservedSlots4],[Timeout4],[Increment4]";
        static constexpr std::wstring_view ViewName = L"AisDataLinkManagementMessageView";

        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT OFFSET1_FIELD_ID = 9;
        static constexpr SQLUSMALLINT RESERVEDSLOTS1_FIELD_ID = 10;
        static constexpr SQLUSMALLINT TIMEOUT1_FIELD_ID = 11;
        static constexpr SQLUSMALLINT INCREMENT1_FIELD_ID = 12;
        static constexpr SQLUSMALLINT OFFSET2_FIELD_ID = 13;
        static constexpr SQLUSMALLINT RESERVEDSLOTS2_FIELD_ID = 14;
        static constexpr SQLUSMALLINT TIMEOUT2_FIELD_ID = 15;
        static constexpr SQLUSMALLINT INCREMENT2_FIELD_ID = 16;
        static constexpr SQLUSMALLINT OFFSET3_FIELD_ID = 17;
        static constexpr SQLUSMALLINT RESERVEDSLOTS3_FIELD_ID = 18;
        static constexpr SQLUSMALLINT TIMEOUT3_FIELD_ID = 19;
        static constexpr SQLUSMALLINT INCREMENT3_FIELD_ID = 20;
        static constexpr SQLUSMALLINT OFFSET4_FIELD_ID = 21;
        static constexpr SQLUSMALLINT RESERVEDSLOTS4_FIELD_ID = 22;
        static constexpr SQLUSMALLINT TIMEOUT4_FIELD_ID = 23;
        static constexpr SQLUSMALLINT INCREMENT4_FIELD_ID = 24;

        AisDataLinkManagementMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisDataLinkManagementMessage;
        }

        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        Int32 Offset1( ) const
        {
            return offset1_;
        }
        void SetOffset1( Int32 offset1 )
        {
            offset1_ = offset1;
        }
        Int32 ReservedSlots1( ) const
        {
            return reservedSlots1_;
        }
        void SetReservedSlots1( Int32 reservedSlots1 )
        {
            reservedSlots1_ = reservedSlots1;
        }
        Int32 Timeout1( ) const
        {
            return timeout1_;
        }
        void SetTimeout1( Int32 timeout1 )
        {
            timeout1_ = timeout1;
        }
        Int32 Increment1( ) const
        {
            return increment1_;
        }
        void SetIncrement1( Int32 increment1 )
        {
            increment1_ = increment1;
        }
        Int32 Offset2( ) const
        {
            return offset2_;
        }
        void SetOffset2( Int32 offset2 )
        {
            offset2_ = offset2;
        }
        Int32 ReservedSlots2( ) const
        {
            return reservedSlots2_;
        }
        void SetReservedSlots2( Int32 reservedSlots2 )
        {
            reservedSlots2_ = reservedSlots2;
        }
        Int32 Timeout2( ) const
        {
            return timeout2_;
        }
        void SetTimeout2( Int32 timeout2 )
        {
            timeout2_ = timeout2;
        }
        Int32 Increment2( ) const
        {
            return increment2_;
        }
        void SetIncrement2( Int32 increment2 )
        {
            increment2_ = increment2;
        }
        Int32 Offset3( ) const
        {
            return offset3_;
        }
        void SetOffset3( Int32 offset3 )
        {
            offset3_ = offset3;
        }
        Int32 ReservedSlots3( ) const
        {
            return reservedSlots3_;
        }
        void SetReservedSlots3( Int32 reservedSlots3 )
        {
            reservedSlots3_ = reservedSlots3;
        }
        Int32 Timeout3( ) const
        {
            return timeout3_;
        }
        void SetTimeout3( Int32 timeout3 )
        {
            timeout3_ = timeout3;
        }
        Int32 Increment3( ) const
        {
            return increment3_;
        }
        void SetIncrement3( Int32 increment3 )
        {
            increment3_ = increment3;
        }
        Int32 Offset4( ) const
        {
            return offset4_;
        }
        void SetOffset4( Int32 offset4 )
        {
            offset4_ = offset4;
        }
        Int32 ReservedSlots4( ) const
        {
            return reservedSlots4_;
        }
        void SetReservedSlots4( Int32 reservedSlots4 )
        {
            reservedSlots4_ = reservedSlots4;
        }
        Int32 Timeout4( ) const
        {
            return timeout4_;
        }
        void SetTimeout4( Int32 timeout4 )
        {
            timeout4_ = timeout4;
        }
        Int32 Increment4( ) const
        {
            return increment4_;
        }
        void SetIncrement4( Int32 increment4 )
        {
            increment4_ = increment4;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, OFFSET1_FIELD_ID, &offset1_);
            Bind(statement, RESERVEDSLOTS1_FIELD_ID, &reservedSlots1_);
            Bind(statement, TIMEOUT1_FIELD_ID, &timeout1_);
            Bind(statement, INCREMENT1_FIELD_ID, &increment1_);
            Bind(statement, OFFSET2_FIELD_ID, &offset2_);
            Bind(statement, RESERVEDSLOTS2_FIELD_ID, &reservedSlots2_);
            Bind(statement, TIMEOUT2_FIELD_ID, &timeout2_);
            Bind(statement, INCREMENT2_FIELD_ID, &increment2_);
            Bind(statement, OFFSET3_FIELD_ID, &offset3_);
            Bind(statement, RESERVEDSLOTS3_FIELD_ID, &reservedSlots3_);
            Bind(statement, TIMEOUT3_FIELD_ID, &timeout3_);
            Bind(statement, INCREMENT3_FIELD_ID, &increment3_);
            Bind(statement, OFFSET4_FIELD_ID, &offset4_);
            Bind(statement, RESERVEDSLOTS4_FIELD_ID, &reservedSlots4_);
            Bind(statement, TIMEOUT4_FIELD_ID, &timeout4_);
            Bind(statement, INCREMENT4_FIELD_ID, &increment4_);
        }

    };

    class AisExtendedClassBCsPositionReportMessageColumnData : public AisMessageColumnData
    {
        Int32 reserved_ = 0;
        double speedOverGround_ = 0.0;
        Data::PositionAccuracy positionAccuracy_ = Data::PositionAccuracy::Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double courseOverGround_ = 0.0;
        Int32 trueHeading_ = 0;
        SQLLEN trueHeadingNullIndicator_ = SQL_NULL_DATA;
        Int32 timestamp_ = 0;
        Int32 regionalReserved_ = 0;
        Guid name_;
        Data::ShipType shipType_ = Data::ShipType::NotAvailable;
        Int32 dimensionToBow_ = 0;
        Int32 dimensionToStern_ = 0;
        Int32 dimensionToPort_ = 0;
        Int32 dimensionToStarboard_ = 0;
        Data::PositionFixType positionFixType_ = Data::PositionFixType::Undefined1;
        Data::Raim raim_ = Data::Raim::NotInUse;
        bool dataTerminalReady_ = false;
        bool assigned_ = false;
        Int32 spare_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[Reserved],[SpeedOverGround],[PositionAccuracy],[Longitude],[Latitude],[CourseOverGround],[TrueHeading],[Timestamp],[RegionalReserved],[Name],[ShipType],[DimensionToBow],[DimensionToStern],[DimensionToPort],[DimensionToStarboard],[PositionFixType],[Raim],[DataTerminalReady],[Assigned],[Spare]";
        static constexpr std::wstring_view ViewName = L"AisExtendedClassBCsPositionReportMessageView";

        static constexpr SQLUSMALLINT RESERVED_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SPEEDOVERGROUND_FIELD_ID = 9;
        static constexpr SQLUSMALLINT POSITIONACCURACY_FIELD_ID = 10;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT COURSEOVERGROUND_FIELD_ID = 13;
        static constexpr SQLUSMALLINT TRUEHEADING_FIELD_ID = 14;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 15;
        static constexpr SQLUSMALLINT REGIONALRESERVED_FIELD_ID = 16;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 17;
        static constexpr SQLUSMALLINT SHIPTYPE_FIELD_ID = 18;
        static constexpr SQLUSMALLINT DIMENSIONTOBOW_FIELD_ID = 19;
        static constexpr SQLUSMALLINT DIMENSIONTOSTERN_FIELD_ID = 20;
        static constexpr SQLUSMALLINT DIMENSIONTOPORT_FIELD_ID = 21;
        static constexpr SQLUSMALLINT DIMENSIONTOSTARBOARD_FIELD_ID = 22;
        static constexpr SQLUSMALLINT POSITIONFIXTYPE_FIELD_ID = 23;
        static constexpr SQLUSMALLINT RAIM_FIELD_ID = 24;
        static constexpr SQLUSMALLINT DATATERMINALREADY_FIELD_ID = 25;
        static constexpr SQLUSMALLINT ASSIGNED_FIELD_ID = 26;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 27;

        AisExtendedClassBCsPositionReportMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisExtendedClassBCsPositionReportMessage;
        }

        Int32 Reserved( ) const
        {
            return reserved_;
        }
        void SetReserved( Int32 reserved )
        {
            reserved_ = reserved;
        }
        double SpeedOverGround( ) const
        {
            return speedOverGround_;
        }
        void SetSpeedOverGround( double speedOverGround )
        {
            speedOverGround_ = speedOverGround;
        }
        Data::PositionAccuracy PositionAccuracy( ) const
        {
            return positionAccuracy_;
        }
        void SetPositionAccuracy( Data::PositionAccuracy positionAccuracy )
        {
            positionAccuracy_ = positionAccuracy;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double CourseOverGround( ) const
        {
            return courseOverGround_;
        }
        void SetCourseOverGround( double courseOverGround )
        {
            courseOverGround_ = courseOverGround;
        }
        Int32 TrueHeading( ) const
        {
            return trueHeading_;
        }
        void SetTrueHeading( Int32 trueHeading )
        {
            trueHeading_ = trueHeading;
        }
        Int32 Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( Int32 timestamp )
        {
            timestamp_ = timestamp;
        }
        Int32 RegionalReserved( ) const
        {
            return regionalReserved_;
        }
        void SetRegionalReserved( Int32 regionalReserved )
        {
            regionalReserved_ = regionalReserved;
        }
        Guid Name( ) const
        {
            return name_;
        }
        void SetName( const Guid& name )
        {
            name_ = name;
        }
        Data::ShipType ShipType( ) const
        {
            return shipType_;
        }
        void SetShipType( Data::ShipType shipType )
        {
            shipType_ = shipType;
        }
        Int32 DimensionToBow( ) const
        {
            return dimensionToBow_;
        }
        void SetDimensionToBow( Int32 dimensionToBow )
        {
            dimensionToBow_ = dimensionToBow;
        }
        Int32 DimensionToStern( ) const
        {
            return dimensionToStern_;
        }
        void SetDimensionToStern( Int32 dimensionToStern )
        {
            dimensionToStern_ = dimensionToStern;
        }
        Int32 DimensionToPort( ) const
        {
            return dimensionToPort_;
        }
        void SetDimensionToPort( Int32 dimensionToPort )
        {
            dimensionToPort_ = dimensionToPort;
        }
        Int32 DimensionToStarboard( ) const
        {
            return dimensionToStarboard_;
        }
        void SetDimensionToStarboard( Int32 dimensionToStarboard )
        {
            dimensionToStarboard_ = dimensionToStarboard;
        }
        Data::PositionFixType PositionFixType( ) const
        {
            return positionFixType_;
        }
        void SetPositionFixType( Data::PositionFixType positionFixType )
        {
            positionFixType_ = positionFixType;
        }
        Data::Raim Raim( ) const
        {
            return raim_;
        }
        void SetRaim( Data::Raim raim )
        {
            raim_ = raim;
        }
        bool DataTerminalReady( ) const
        {
            return dataTerminalReady_;
        }
        void SetDataTerminalReady( bool dataTerminalReady )
        {
            dataTerminalReady_ = dataTerminalReady;
        }
        bool Assigned( ) const
        {
            return assigned_;
        }
        void SetAssigned( bool assigned )
        {
            assigned_ = assigned;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RESERVED_FIELD_ID, &reserved_);
            Bind(statement, SPEEDOVERGROUND_FIELD_ID, &speedOverGround_);
            Bind(statement, POSITIONACCURACY_FIELD_ID, &positionAccuracy_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, COURSEOVERGROUND_FIELD_ID, &courseOverGround_);
            Bind(statement, TRUEHEADING_FIELD_ID, &trueHeading_, &trueHeadingNullIndicator_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, REGIONALRESERVED_FIELD_ID, &regionalReserved_);
            Bind(statement, NAME_FIELD_ID, &name_);
            Bind(statement, SHIPTYPE_FIELD_ID, &shipType_);
            Bind(statement, DIMENSIONTOBOW_FIELD_ID, &dimensionToBow_);
            Bind(statement, DIMENSIONTOSTERN_FIELD_ID, &dimensionToStern_);
            Bind(statement, DIMENSIONTOPORT_FIELD_ID, &dimensionToPort_);
            Bind(statement, DIMENSIONTOSTARBOARD_FIELD_ID, &dimensionToStarboard_);
            Bind(statement, POSITIONFIXTYPE_FIELD_ID, &positionFixType_);
            Bind(statement, RAIM_FIELD_ID, &raim_);
            Bind(statement, DATATERMINALREADY_FIELD_ID, &dataTerminalReady_);
            Bind(statement, ASSIGNED_FIELD_ID, &assigned_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
        }

    };

    class AisInterrogationMessageColumnData : public AisMessageColumnData
    {
        Guid interrogatedMmsi_;
        Data::AisMessageType firstMessageType_ = Data::AisMessageType::PositionReportClassA;
        Int32 firstSlotOffset_ = 0;
        Data::AisMessageType secondMessageType_ = Data::AisMessageType::PositionReportClassA;
        SQLLEN secondMessageTypeNullIndicator_ = SQL_NULL_DATA;
        Int32 secondSlotOffset_ = 0;
        SQLLEN secondSlotOffsetNullIndicator_ = SQL_NULL_DATA;
        Guid secondStationInterrogationMmsi_;
        Data::AisMessageType secondStationFirstMessageType_ = Data::AisMessageType::PositionReportClassA;
        SQLLEN secondStationFirstMessageTypeNullIndicator_ = SQL_NULL_DATA;
        Int32 secondStationFirstSlotOffset_ = 0;
        SQLLEN secondStationFirstSlotOffsetNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[InterrogatedMmsi],[FirstMessageType],[FirstSlotOffset],[SecondMessageType],[SecondSlotOffset],[SecondStationInterrogationMmsi],[SecondStationFirstMessageType],[SecondStationFirstSlotOffset]";
        static constexpr std::wstring_view ViewName = L"AisInterrogationMessageView";

        static constexpr SQLUSMALLINT INTERROGATEDMMSI_FIELD_ID = 8;
        static constexpr SQLUSMALLINT FIRSTMESSAGETYPE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT FIRSTSLOTOFFSET_FIELD_ID = 10;
        static constexpr SQLUSMALLINT SECONDMESSAGETYPE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT SECONDSLOTOFFSET_FIELD_ID = 12;
        static constexpr SQLUSMALLINT SECONDSTATIONINTERROGATIONMMSI_FIELD_ID = 13;
        static constexpr SQLUSMALLINT SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID = 15;

        AisInterrogationMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisInterrogationMessage;
        }

        Guid InterrogatedMmsi( ) const
        {
            return interrogatedMmsi_;
        }
        void SetInterrogatedMmsi( const Guid& interrogatedMmsi )
        {
            interrogatedMmsi_ = interrogatedMmsi;
        }
        Data::AisMessageType FirstMessageType( ) const
        {
            return firstMessageType_;
        }
        void SetFirstMessageType( Data::AisMessageType firstMessageType )
        {
            firstMessageType_ = firstMessageType;
        }
        Int32 FirstSlotOffset( ) const
        {
            return firstSlotOffset_;
        }
        void SetFirstSlotOffset( Int32 firstSlotOffset )
        {
            firstSlotOffset_ = firstSlotOffset;
        }
        Data::AisMessageType SecondMessageType( ) const
        {
            return secondMessageType_;
        }
        void SetSecondMessageType( Data::AisMessageType secondMessageType )
        {
            secondMessageType_ = secondMessageType;
        }
        Int32 SecondSlotOffset( ) const
        {
            return secondSlotOffset_;
        }
        void SetSecondSlotOffset( Int32 secondSlotOffset )
        {
            secondSlotOffset_ = secondSlotOffset;
        }
        Guid SecondStationInterrogationMmsi( ) const
        {
            return secondStationInterrogationMmsi_;
        }
        void SetSecondStationInterrogationMmsi( const Guid& secondStationInterrogationMmsi )
        {
            secondStationInterrogationMmsi_ = secondStationInterrogationMmsi;
        }
        Data::AisMessageType SecondStationFirstMessageType( ) const
        {
            return secondStationFirstMessageType_;
        }
        void SetSecondStationFirstMessageType( Data::AisMessageType secondStationFirstMessageType )
        {
            secondStationFirstMessageType_ = secondStationFirstMessageType;
        }
        Int32 SecondStationFirstSlotOffset( ) const
        {
            return secondStationFirstSlotOffset_;
        }
        void SetSecondStationFirstSlotOffset( Int32 secondStationFirstSlotOffset )
        {
            secondStationFirstSlotOffset_ = secondStationFirstSlotOffset;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, INTERROGATEDMMSI_FIELD_ID, &interrogatedMmsi_);
            Bind(statement, FIRSTMESSAGETYPE_FIELD_ID, &firstMessageType_);
            Bind(statement, FIRSTSLOTOFFSET_FIELD_ID, &firstSlotOffset_);
            Bind(statement, SECONDMESSAGETYPE_FIELD_ID, &secondMessageType_, &secondMessageTypeNullIndicator_);
            Bind(statement, SECONDSLOTOFFSET_FIELD_ID, &secondSlotOffset_, &secondSlotOffsetNullIndicator_);
            Bind(statement, SECONDSTATIONINTERROGATIONMMSI_FIELD_ID, &secondStationInterrogationMmsi_);
            Bind(statement, SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID, &secondStationFirstMessageType_, &secondStationFirstMessageTypeNullIndicator_);
            Bind(statement, SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID, &secondStationFirstSlotOffset_, &secondStationFirstSlotOffsetNullIndicator_);
        }

    };

    class AisPositionReportClassAMessageBaseColumnData : public AisMessageColumnData
    {
        Data::NavigationStatus navigationStatus_ = Data::NavigationStatus::UnderWayUsingEngine;
        Int32 rateOfTurn_ = 0;
        SQLLEN rateOfTurnNullIndicator_ = SQL_NULL_DATA;
        double speedOverGround_ = 0.0;
        Data::PositionAccuracy positionAccuracy_ = Data::PositionAccuracy::Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double courseOverGround_ = 0.0;
        Int32 trueHeading_ = 0;
        SQLLEN trueHeadingNullIndicator_ = SQL_NULL_DATA;
        Int32 timestamp_ = 0;
        Data::ManeuverIndicator maneuverIndicator_ = Data::ManeuverIndicator::NotAvailable;
        Int32 spare_ = 0;
        Data::Raim raim_ = Data::Raim::NotInUse;
        Int32 radioStatus_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[NavigationStatus],[RateOfTurn],[SpeedOverGround],[PositionAccuracy],[Longitude],[Latitude],[CourseOverGround],[TrueHeading],[Timestamp],[ManeuverIndicator],[Spare],[Raim],[RadioStatus]";
        static constexpr std::wstring_view ViewName = L"AisPositionReportClassAMessageBaseView";

        static constexpr SQLUSMALLINT NAVIGATIONSTATUS_FIELD_ID = 8;
        static constexpr SQLUSMALLINT RATEOFTURN_FIELD_ID = 9;
        static constexpr SQLUSMALLINT SPEEDOVERGROUND_FIELD_ID = 10;
        static constexpr SQLUSMALLINT POSITIONACCURACY_FIELD_ID = 11;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT COURSEOVERGROUND_FIELD_ID = 14;
        static constexpr SQLUSMALLINT TRUEHEADING_FIELD_ID = 15;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 16;
        static constexpr SQLUSMALLINT MANEUVERINDICATOR_FIELD_ID = 17;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 18;
        static constexpr SQLUSMALLINT RAIM_FIELD_ID = 19;
        static constexpr SQLUSMALLINT RADIOSTATUS_FIELD_ID = 20;

        AisPositionReportClassAMessageBaseColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisPositionReportClassAMessageBase;
        }

        Data::NavigationStatus NavigationStatus( ) const
        {
            return navigationStatus_;
        }
        void SetNavigationStatus( Data::NavigationStatus navigationStatus )
        {
            navigationStatus_ = navigationStatus;
        }
        Int32 RateOfTurn( ) const
        {
            return rateOfTurn_;
        }
        void SetRateOfTurn( Int32 rateOfTurn )
        {
            rateOfTurn_ = rateOfTurn;
        }
        double SpeedOverGround( ) const
        {
            return speedOverGround_;
        }
        void SetSpeedOverGround( double speedOverGround )
        {
            speedOverGround_ = speedOverGround;
        }
        Data::PositionAccuracy PositionAccuracy( ) const
        {
            return positionAccuracy_;
        }
        void SetPositionAccuracy( Data::PositionAccuracy positionAccuracy )
        {
            positionAccuracy_ = positionAccuracy;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double CourseOverGround( ) const
        {
            return courseOverGround_;
        }
        void SetCourseOverGround( double courseOverGround )
        {
            courseOverGround_ = courseOverGround;
        }
        Int32 TrueHeading( ) const
        {
            return trueHeading_;
        }
        void SetTrueHeading( Int32 trueHeading )
        {
            trueHeading_ = trueHeading;
        }
        Int32 Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( Int32 timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::ManeuverIndicator ManeuverIndicator( ) const
        {
            return maneuverIndicator_;
        }
        void SetManeuverIndicator( Data::ManeuverIndicator maneuverIndicator )
        {
            maneuverIndicator_ = maneuverIndicator;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        Data::Raim Raim( ) const
        {
            return raim_;
        }
        void SetRaim( Data::Raim raim )
        {
            raim_ = raim;
        }
        Int32 RadioStatus( ) const
        {
            return radioStatus_;
        }
        void SetRadioStatus( Int32 radioStatus )
        {
            radioStatus_ = radioStatus;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAVIGATIONSTATUS_FIELD_ID, &navigationStatus_);
            Bind(statement, RATEOFTURN_FIELD_ID, &rateOfTurn_, &rateOfTurnNullIndicator_);
            Bind(statement, SPEEDOVERGROUND_FIELD_ID, &speedOverGround_);
            Bind(statement, POSITIONACCURACY_FIELD_ID, &positionAccuracy_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, COURSEOVERGROUND_FIELD_ID, &courseOverGround_);
            Bind(statement, TRUEHEADING_FIELD_ID, &trueHeading_, &trueHeadingNullIndicator_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, MANEUVERINDICATOR_FIELD_ID, &maneuverIndicator_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, RAIM_FIELD_ID, &raim_);
            Bind(statement, RADIOSTATUS_FIELD_ID, &radioStatus_);
        }

    };

    class AisPositionReportClassAAssignedScheduleMessageColumnData : public AisPositionReportClassAMessageBaseColumnData
    {
    public:
        using Base = AisPositionReportClassAMessageBaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[NavigationStatus],[RateOfTurn],[SpeedOverGround],[PositionAccuracy],[Longitude],[Latitude],[CourseOverGround],[TrueHeading],[Timestamp],[ManeuverIndicator],[Spare],[Raim],[RadioStatus]";
        static constexpr std::wstring_view ViewName = L"AisPositionReportClassAAssignedScheduleMessageView";

        AisPositionReportClassAAssignedScheduleMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisPositionReportClassAAssignedScheduleMessage;
        }

    };

    class AisPositionReportClassAMessageColumnData : public AisPositionReportClassAMessageBaseColumnData
    {
    public:
        using Base = AisPositionReportClassAMessageBaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[NavigationStatus],[RateOfTurn],[SpeedOverGround],[PositionAccuracy],[Longitude],[Latitude],[CourseOverGround],[TrueHeading],[Timestamp],[ManeuverIndicator],[Spare],[Raim],[RadioStatus]";
        static constexpr std::wstring_view ViewName = L"AisPositionReportClassAMessageView";

        AisPositionReportClassAMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisPositionReportClassAMessage;
        }

    };

    class AisPositionReportClassAResponseToInterrogationMessageColumnData : public AisPositionReportClassAMessageBaseColumnData
    {
    public:
        using Base = AisPositionReportClassAMessageBaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[NavigationStatus],[RateOfTurn],[SpeedOverGround],[PositionAccuracy],[Longitude],[Latitude],[CourseOverGround],[TrueHeading],[Timestamp],[ManeuverIndicator],[Spare],[Raim],[RadioStatus]";
        static constexpr std::wstring_view ViewName = L"AisPositionReportClassAResponseToInterrogationMessageView";

        AisPositionReportClassAResponseToInterrogationMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisPositionReportClassAResponseToInterrogationMessage;
        }

    };

    class AisPositionReportForLongRangeApplicationsMessageColumnData : public AisMessageColumnData
    {
        Data::PositionAccuracy positionAccuracy_ = Data::PositionAccuracy::Low;
        Data::Raim raim_ = Data::Raim::NotInUse;
        Data::NavigationStatus navigationStatus_ = Data::NavigationStatus::UnderWayUsingEngine;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double speedOverGround_ = 0.0;
        double courseOverGround_ = 0.0;
        Data::GnssPositionStatus gnssPositionStatus_ = Data::GnssPositionStatus::CurrentGnssPosition;
        Int32 spare_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[PositionAccuracy],[Raim],[NavigationStatus],[Longitude],[Latitude],[SpeedOverGround],[CourseOverGround],[GnssPositionStatus],[Spare]";
        static constexpr std::wstring_view ViewName = L"AisPositionReportForLongRangeApplicationsMessageView";

        static constexpr SQLUSMALLINT POSITIONACCURACY_FIELD_ID = 8;
        static constexpr SQLUSMALLINT RAIM_FIELD_ID = 9;
        static constexpr SQLUSMALLINT NAVIGATIONSTATUS_FIELD_ID = 10;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT SPEEDOVERGROUND_FIELD_ID = 13;
        static constexpr SQLUSMALLINT COURSEOVERGROUND_FIELD_ID = 14;
        static constexpr SQLUSMALLINT GNSSPOSITIONSTATUS_FIELD_ID = 15;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 16;

        AisPositionReportForLongRangeApplicationsMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisPositionReportForLongRangeApplicationsMessage;
        }

        Data::PositionAccuracy PositionAccuracy( ) const
        {
            return positionAccuracy_;
        }
        void SetPositionAccuracy( Data::PositionAccuracy positionAccuracy )
        {
            positionAccuracy_ = positionAccuracy;
        }
        Data::Raim Raim( ) const
        {
            return raim_;
        }
        void SetRaim( Data::Raim raim )
        {
            raim_ = raim;
        }
        Data::NavigationStatus NavigationStatus( ) const
        {
            return navigationStatus_;
        }
        void SetNavigationStatus( Data::NavigationStatus navigationStatus )
        {
            navigationStatus_ = navigationStatus;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double SpeedOverGround( ) const
        {
            return speedOverGround_;
        }
        void SetSpeedOverGround( double speedOverGround )
        {
            speedOverGround_ = speedOverGround;
        }
        double CourseOverGround( ) const
        {
            return courseOverGround_;
        }
        void SetCourseOverGround( double courseOverGround )
        {
            courseOverGround_ = courseOverGround;
        }
        Data::GnssPositionStatus GnssPositionStatus( ) const
        {
            return gnssPositionStatus_;
        }
        void SetGnssPositionStatus( Data::GnssPositionStatus gnssPositionStatus )
        {
            gnssPositionStatus_ = gnssPositionStatus;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, POSITIONACCURACY_FIELD_ID, &positionAccuracy_);
            Bind(statement, RAIM_FIELD_ID, &raim_);
            Bind(statement, NAVIGATIONSTATUS_FIELD_ID, &navigationStatus_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, SPEEDOVERGROUND_FIELD_ID, &speedOverGround_);
            Bind(statement, COURSEOVERGROUND_FIELD_ID, &courseOverGround_);
            Bind(statement, GNSSPOSITIONSTATUS_FIELD_ID, &gnssPositionStatus_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
        }

    };

    class AisSafetyRelatedAcknowledgmentMessageColumnData : public AisMessageColumnData
    {
        Int32 spare_ = 0;
        Int32 sequenceNumber1_ = 0;
        Guid mmsi1_;
        Int32 sequenceNumber2_ = 0;
        Guid mmsi2_;
        Int32 sequenceNumber3_ = 0;
        Guid mmsi3_;
        Int32 sequenceNumber4_ = 0;
        Guid mmsi4_;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[Spare],[SequenceNumber1],[Mmsi1],[SequenceNumber2],[Mmsi2],[SequenceNumber3],[Mmsi3],[SequenceNumber4],[Mmsi4]";
        static constexpr std::wstring_view ViewName = L"AisSafetyRelatedAcknowledgmentMessageView";

        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SEQUENCENUMBER1_FIELD_ID = 9;
        static constexpr SQLUSMALLINT MMSI1_FIELD_ID = 10;
        static constexpr SQLUSMALLINT SEQUENCENUMBER2_FIELD_ID = 11;
        static constexpr SQLUSMALLINT MMSI2_FIELD_ID = 12;
        static constexpr SQLUSMALLINT SEQUENCENUMBER3_FIELD_ID = 13;
        static constexpr SQLUSMALLINT MMSI3_FIELD_ID = 14;
        static constexpr SQLUSMALLINT SEQUENCENUMBER4_FIELD_ID = 15;
        static constexpr SQLUSMALLINT MMSI4_FIELD_ID = 16;

        AisSafetyRelatedAcknowledgmentMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisSafetyRelatedAcknowledgmentMessage;
        }

        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        Int32 SequenceNumber1( ) const
        {
            return sequenceNumber1_;
        }
        void SetSequenceNumber1( Int32 sequenceNumber1 )
        {
            sequenceNumber1_ = sequenceNumber1;
        }
        Guid Mmsi1( ) const
        {
            return mmsi1_;
        }
        void SetMmsi1( const Guid& mmsi1 )
        {
            mmsi1_ = mmsi1;
        }
        Int32 SequenceNumber2( ) const
        {
            return sequenceNumber2_;
        }
        void SetSequenceNumber2( Int32 sequenceNumber2 )
        {
            sequenceNumber2_ = sequenceNumber2;
        }
        Guid Mmsi2( ) const
        {
            return mmsi2_;
        }
        void SetMmsi2( const Guid& mmsi2 )
        {
            mmsi2_ = mmsi2;
        }
        Int32 SequenceNumber3( ) const
        {
            return sequenceNumber3_;
        }
        void SetSequenceNumber3( Int32 sequenceNumber3 )
        {
            sequenceNumber3_ = sequenceNumber3;
        }
        Guid Mmsi3( ) const
        {
            return mmsi3_;
        }
        void SetMmsi3( const Guid& mmsi3 )
        {
            mmsi3_ = mmsi3;
        }
        Int32 SequenceNumber4( ) const
        {
            return sequenceNumber4_;
        }
        void SetSequenceNumber4( Int32 sequenceNumber4 )
        {
            sequenceNumber4_ = sequenceNumber4;
        }
        Guid Mmsi4( ) const
        {
            return mmsi4_;
        }
        void SetMmsi4( const Guid& mmsi4 )
        {
            mmsi4_ = mmsi4;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, SEQUENCENUMBER1_FIELD_ID, &sequenceNumber1_);
            Bind(statement, MMSI1_FIELD_ID, &mmsi1_);
            Bind(statement, SEQUENCENUMBER2_FIELD_ID, &sequenceNumber2_);
            Bind(statement, MMSI2_FIELD_ID, &mmsi2_);
            Bind(statement, SEQUENCENUMBER3_FIELD_ID, &sequenceNumber3_);
            Bind(statement, MMSI3_FIELD_ID, &mmsi3_);
            Bind(statement, SEQUENCENUMBER4_FIELD_ID, &sequenceNumber4_);
            Bind(statement, MMSI4_FIELD_ID, &mmsi4_);
        }

    };

    class AisStandardClassBCsPositionReportMessageColumnData : public AisMessageColumnData
    {
        Int32 reserved_ = 0;
        double speedOverGround_ = 0.0;
        Data::PositionAccuracy positionAccuracy_ = Data::PositionAccuracy::Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double courseOverGround_ = 0.0;
        Int32 trueHeading_ = 0;
        SQLLEN trueHeadingNullIndicator_ = SQL_NULL_DATA;
        Int32 timestamp_ = 0;
        Int32 regionalReserved_ = 0;
        bool isCsUnit_ = false;
        bool hasDisplay_ = false;
        bool hasDscCapability_ = false;
        bool band_ = false;
        bool canAcceptMessage22_ = false;
        bool assigned_ = false;
        Data::Raim raim_ = Data::Raim::NotInUse;
        Int32 radioStatus_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[Reserved],[SpeedOverGround],[PositionAccuracy],[Longitude],[Latitude],[CourseOverGround],[TrueHeading],[Timestamp],[RegionalReserved],[IsCsUnit],[HasDisplay],[HasDscCapability],[Band],[CanAcceptMessage22],[Assigned],[Raim],[RadioStatus]";
        static constexpr std::wstring_view ViewName = L"AisStandardClassBCsPositionReportMessageView";

        static constexpr SQLUSMALLINT RESERVED_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SPEEDOVERGROUND_FIELD_ID = 9;
        static constexpr SQLUSMALLINT POSITIONACCURACY_FIELD_ID = 10;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT COURSEOVERGROUND_FIELD_ID = 13;
        static constexpr SQLUSMALLINT TRUEHEADING_FIELD_ID = 14;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 15;
        static constexpr SQLUSMALLINT REGIONALRESERVED_FIELD_ID = 16;
        static constexpr SQLUSMALLINT ISCSUNIT_FIELD_ID = 17;
        static constexpr SQLUSMALLINT HASDISPLAY_FIELD_ID = 18;
        static constexpr SQLUSMALLINT HASDSCCAPABILITY_FIELD_ID = 19;
        static constexpr SQLUSMALLINT BAND_FIELD_ID = 20;
        static constexpr SQLUSMALLINT CANACCEPTMESSAGE22_FIELD_ID = 21;
        static constexpr SQLUSMALLINT ASSIGNED_FIELD_ID = 22;
        static constexpr SQLUSMALLINT RAIM_FIELD_ID = 23;
        static constexpr SQLUSMALLINT RADIOSTATUS_FIELD_ID = 24;

        AisStandardClassBCsPositionReportMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisStandardClassBCsPositionReportMessage;
        }

        Int32 Reserved( ) const
        {
            return reserved_;
        }
        void SetReserved( Int32 reserved )
        {
            reserved_ = reserved;
        }
        double SpeedOverGround( ) const
        {
            return speedOverGround_;
        }
        void SetSpeedOverGround( double speedOverGround )
        {
            speedOverGround_ = speedOverGround;
        }
        Data::PositionAccuracy PositionAccuracy( ) const
        {
            return positionAccuracy_;
        }
        void SetPositionAccuracy( Data::PositionAccuracy positionAccuracy )
        {
            positionAccuracy_ = positionAccuracy;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double CourseOverGround( ) const
        {
            return courseOverGround_;
        }
        void SetCourseOverGround( double courseOverGround )
        {
            courseOverGround_ = courseOverGround;
        }
        Int32 TrueHeading( ) const
        {
            return trueHeading_;
        }
        void SetTrueHeading( Int32 trueHeading )
        {
            trueHeading_ = trueHeading;
        }
        Int32 Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( Int32 timestamp )
        {
            timestamp_ = timestamp;
        }
        Int32 RegionalReserved( ) const
        {
            return regionalReserved_;
        }
        void SetRegionalReserved( Int32 regionalReserved )
        {
            regionalReserved_ = regionalReserved;
        }
        bool IsCsUnit( ) const
        {
            return isCsUnit_;
        }
        void SetIsCsUnit( bool isCsUnit )
        {
            isCsUnit_ = isCsUnit;
        }
        bool HasDisplay( ) const
        {
            return hasDisplay_;
        }
        void SetHasDisplay( bool hasDisplay )
        {
            hasDisplay_ = hasDisplay;
        }
        bool HasDscCapability( ) const
        {
            return hasDscCapability_;
        }
        void SetHasDscCapability( bool hasDscCapability )
        {
            hasDscCapability_ = hasDscCapability;
        }
        bool Band( ) const
        {
            return band_;
        }
        void SetBand( bool band )
        {
            band_ = band;
        }
        bool CanAcceptMessage22( ) const
        {
            return canAcceptMessage22_;
        }
        void SetCanAcceptMessage22( bool canAcceptMessage22 )
        {
            canAcceptMessage22_ = canAcceptMessage22;
        }
        bool Assigned( ) const
        {
            return assigned_;
        }
        void SetAssigned( bool assigned )
        {
            assigned_ = assigned;
        }
        Data::Raim Raim( ) const
        {
            return raim_;
        }
        void SetRaim( Data::Raim raim )
        {
            raim_ = raim;
        }
        Int32 RadioStatus( ) const
        {
            return radioStatus_;
        }
        void SetRadioStatus( Int32 radioStatus )
        {
            radioStatus_ = radioStatus;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RESERVED_FIELD_ID, &reserved_);
            Bind(statement, SPEEDOVERGROUND_FIELD_ID, &speedOverGround_);
            Bind(statement, POSITIONACCURACY_FIELD_ID, &positionAccuracy_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, COURSEOVERGROUND_FIELD_ID, &courseOverGround_);
            Bind(statement, TRUEHEADING_FIELD_ID, &trueHeading_, &trueHeadingNullIndicator_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, REGIONALRESERVED_FIELD_ID, &regionalReserved_);
            Bind(statement, ISCSUNIT_FIELD_ID, &isCsUnit_);
            Bind(statement, HASDISPLAY_FIELD_ID, &hasDisplay_);
            Bind(statement, HASDSCCAPABILITY_FIELD_ID, &hasDscCapability_);
            Bind(statement, BAND_FIELD_ID, &band_);
            Bind(statement, CANACCEPTMESSAGE22_FIELD_ID, &canAcceptMessage22_);
            Bind(statement, ASSIGNED_FIELD_ID, &assigned_);
            Bind(statement, RAIM_FIELD_ID, &raim_);
            Bind(statement, RADIOSTATUS_FIELD_ID, &radioStatus_);
        }

    };

    class AisStandardSarAircraftPositionReportMessageColumnData : public AisMessageColumnData
    {
        Int32 altitude_ = 0;
        Int32 speedOverGround_ = 0;
        Data::PositionAccuracy positionAccuracy_ = Data::PositionAccuracy::Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double courseOverGround_ = 0.0;
        Int32 timestamp_ = 0;
        Int32 reserved_ = 0;
        bool dataTerminalReady_ = false;
        Int32 spare_ = 0;
        bool assigned_ = false;
        Data::Raim raim_ = Data::Raim::NotInUse;
        Int32 radioStatus_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[Altitude],[SpeedOverGround],[PositionAccuracy],[Longitude],[Latitude],[CourseOverGround],[Timestamp],[Reserved],[DataTerminalReady],[Spare],[Assigned],[Raim],[RadioStatus]";
        static constexpr std::wstring_view ViewName = L"AisStandardSarAircraftPositionReportMessageView";

        static constexpr SQLUSMALLINT ALTITUDE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SPEEDOVERGROUND_FIELD_ID = 9;
        static constexpr SQLUSMALLINT POSITIONACCURACY_FIELD_ID = 10;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT COURSEOVERGROUND_FIELD_ID = 13;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 14;
        static constexpr SQLUSMALLINT RESERVED_FIELD_ID = 15;
        static constexpr SQLUSMALLINT DATATERMINALREADY_FIELD_ID = 16;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 17;
        static constexpr SQLUSMALLINT ASSIGNED_FIELD_ID = 18;
        static constexpr SQLUSMALLINT RAIM_FIELD_ID = 19;
        static constexpr SQLUSMALLINT RADIOSTATUS_FIELD_ID = 20;

        AisStandardSarAircraftPositionReportMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisStandardSarAircraftPositionReportMessage;
        }

        Int32 Altitude( ) const
        {
            return altitude_;
        }
        void SetAltitude( Int32 altitude )
        {
            altitude_ = altitude;
        }
        Int32 SpeedOverGround( ) const
        {
            return speedOverGround_;
        }
        void SetSpeedOverGround( Int32 speedOverGround )
        {
            speedOverGround_ = speedOverGround;
        }
        Data::PositionAccuracy PositionAccuracy( ) const
        {
            return positionAccuracy_;
        }
        void SetPositionAccuracy( Data::PositionAccuracy positionAccuracy )
        {
            positionAccuracy_ = positionAccuracy;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double CourseOverGround( ) const
        {
            return courseOverGround_;
        }
        void SetCourseOverGround( double courseOverGround )
        {
            courseOverGround_ = courseOverGround;
        }
        Int32 Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( Int32 timestamp )
        {
            timestamp_ = timestamp;
        }
        Int32 Reserved( ) const
        {
            return reserved_;
        }
        void SetReserved( Int32 reserved )
        {
            reserved_ = reserved;
        }
        bool DataTerminalReady( ) const
        {
            return dataTerminalReady_;
        }
        void SetDataTerminalReady( bool dataTerminalReady )
        {
            dataTerminalReady_ = dataTerminalReady;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        bool Assigned( ) const
        {
            return assigned_;
        }
        void SetAssigned( bool assigned )
        {
            assigned_ = assigned;
        }
        Data::Raim Raim( ) const
        {
            return raim_;
        }
        void SetRaim( Data::Raim raim )
        {
            raim_ = raim;
        }
        Int32 RadioStatus( ) const
        {
            return radioStatus_;
        }
        void SetRadioStatus( Int32 radioStatus )
        {
            radioStatus_ = radioStatus;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, ALTITUDE_FIELD_ID, &altitude_);
            Bind(statement, SPEEDOVERGROUND_FIELD_ID, &speedOverGround_);
            Bind(statement, POSITIONACCURACY_FIELD_ID, &positionAccuracy_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, COURSEOVERGROUND_FIELD_ID, &courseOverGround_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, RESERVED_FIELD_ID, &reserved_);
            Bind(statement, DATATERMINALREADY_FIELD_ID, &dataTerminalReady_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, ASSIGNED_FIELD_ID, &assigned_);
            Bind(statement, RAIM_FIELD_ID, &raim_);
            Bind(statement, RADIOSTATUS_FIELD_ID, &radioStatus_);
        }

    };

    class AisStaticAndVoyageRelatedDataMessageColumnData : public AisMessageColumnData
    {
        Int32 aisVersion_ = 0;
        Guid imoNumber_;
        Guid callsign_;
        Guid shipName_;
        Data::ShipType shipType_ = Data::ShipType::NotAvailable;
        Int32 dimensionToBow_ = 0;
        Int32 dimensionToStern_ = 0;
        Int32 dimensionToPort_ = 0;
        Int32 dimensionToStarboard_ = 0;
        Data::PositionFixType positionFixType_ = Data::PositionFixType::Undefined1;
        DateTime estimatedTimeOfArrival_;
        SQLLEN estimatedTimeOfArrivalNullIndicator_ = SQL_NULL_DATA;
        double draught_ = 0.0;
        std::array<wchar_t,101> destination_ = {};
        SQLLEN destinationLengthOrNullIndicator_ = SQL_NULL_DATA;
        bool dataTerminalReady_ = false;
        Int32 spare_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[AisVersion],[ImoNumber],[Callsign],[ShipName],[ShipType],[DimensionToBow],[DimensionToStern],[DimensionToPort],[DimensionToStarboard],[PositionFixType],[EstimatedTimeOfArrival],[Draught],[Destination],[DataTerminalReady],[Spare]";
        static constexpr std::wstring_view ViewName = L"AisStaticAndVoyageRelatedDataMessageView";

        static constexpr SQLUSMALLINT AISVERSION_FIELD_ID = 8;
        static constexpr SQLUSMALLINT IMONUMBER_FIELD_ID = 9;
        static constexpr SQLUSMALLINT CALLSIGN_FIELD_ID = 10;
        static constexpr SQLUSMALLINT SHIPNAME_FIELD_ID = 11;
        static constexpr SQLUSMALLINT SHIPTYPE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT DIMENSIONTOBOW_FIELD_ID = 13;
        static constexpr SQLUSMALLINT DIMENSIONTOSTERN_FIELD_ID = 14;
        static constexpr SQLUSMALLINT DIMENSIONTOPORT_FIELD_ID = 15;
        static constexpr SQLUSMALLINT DIMENSIONTOSTARBOARD_FIELD_ID = 16;
        static constexpr SQLUSMALLINT POSITIONFIXTYPE_FIELD_ID = 17;
        static constexpr SQLUSMALLINT ESTIMATEDTIMEOFARRIVAL_FIELD_ID = 18;
        static constexpr SQLUSMALLINT DRAUGHT_FIELD_ID = 19;
        static constexpr SQLUSMALLINT DESTINATION_FIELD_ID = 20;
        static constexpr SQLUSMALLINT DATATERMINALREADY_FIELD_ID = 21;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 22;

        AisStaticAndVoyageRelatedDataMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisStaticAndVoyageRelatedDataMessage;
        }

        Int32 AisVersion( ) const
        {
            return aisVersion_;
        }
        void SetAisVersion( Int32 aisVersion )
        {
            aisVersion_ = aisVersion;
        }
        Guid ImoNumber( ) const
        {
            return imoNumber_;
        }
        void SetImoNumber( const Guid& imoNumber )
        {
            imoNumber_ = imoNumber;
        }
        Guid Callsign( ) const
        {
            return callsign_;
        }
        void SetCallsign( const Guid& callsign )
        {
            callsign_ = callsign;
        }
        Guid ShipName( ) const
        {
            return shipName_;
        }
        void SetShipName( const Guid& shipName )
        {
            shipName_ = shipName;
        }
        Data::ShipType ShipType( ) const
        {
            return shipType_;
        }
        void SetShipType( Data::ShipType shipType )
        {
            shipType_ = shipType;
        }
        Int32 DimensionToBow( ) const
        {
            return dimensionToBow_;
        }
        void SetDimensionToBow( Int32 dimensionToBow )
        {
            dimensionToBow_ = dimensionToBow;
        }
        Int32 DimensionToStern( ) const
        {
            return dimensionToStern_;
        }
        void SetDimensionToStern( Int32 dimensionToStern )
        {
            dimensionToStern_ = dimensionToStern;
        }
        Int32 DimensionToPort( ) const
        {
            return dimensionToPort_;
        }
        void SetDimensionToPort( Int32 dimensionToPort )
        {
            dimensionToPort_ = dimensionToPort;
        }
        Int32 DimensionToStarboard( ) const
        {
            return dimensionToStarboard_;
        }
        void SetDimensionToStarboard( Int32 dimensionToStarboard )
        {
            dimensionToStarboard_ = dimensionToStarboard;
        }
        Data::PositionFixType PositionFixType( ) const
        {
            return positionFixType_;
        }
        void SetPositionFixType( Data::PositionFixType positionFixType )
        {
            positionFixType_ = positionFixType;
        }
        DateTime EstimatedTimeOfArrival( ) const
        {
            return estimatedTimeOfArrival_;
        }
        void SetEstimatedTimeOfArrival( const DateTime& estimatedTimeOfArrival )
        {
            estimatedTimeOfArrival_ = estimatedTimeOfArrival;
        }
        double Draught( ) const
        {
            return draught_;
        }
        void SetDraught( double draught )
        {
            draught_ = draught;
        }
        std::wstring_view Destination( ) const
        {
            if(destinationLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(destination_.data(),static_cast<size_t>( destinationLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetDestination( const WideString& destination )
        {
            Assign(destination, destination_, destinationLengthOrNullIndicator_);
        }
        bool DataTerminalReady( ) const
        {
            return dataTerminalReady_;
        }
        void SetDataTerminalReady( bool dataTerminalReady )
        {
            dataTerminalReady_ = dataTerminalReady;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, AISVERSION_FIELD_ID, &aisVersion_);
            Bind(statement, IMONUMBER_FIELD_ID, &imoNumber_);
            Bind(statement, CALLSIGN_FIELD_ID, &callsign_);
            Bind(statement, SHIPNAME_FIELD_ID, &shipName_);
            Bind(statement, SHIPTYPE_FIELD_ID, &shipType_);
            Bind(statement, DIMENSIONTOBOW_FIELD_ID, &dimensionToBow_);
            Bind(statement, DIMENSIONTOSTERN_FIELD_ID, &dimensionToStern_);
            Bind(statement, DIMENSIONTOPORT_FIELD_ID, &dimensionToPort_);
            Bind(statement, DIMENSIONTOSTARBOARD_FIELD_ID, &dimensionToStarboard_);
            Bind(statement, POSITIONFIXTYPE_FIELD_ID, &positionFixType_);
            Bind(statement, ESTIMATEDTIMEOFARRIVAL_FIELD_ID, &estimatedTimeOfArrival_, &estimatedTimeOfArrivalNullIndicator_);
            Bind(statement, DRAUGHT_FIELD_ID, &draught_);
            Bind(statement, DESTINATION_FIELD_ID, &destination_, &destinationLengthOrNullIndicator_);
            Bind(statement, DATATERMINALREADY_FIELD_ID, &dataTerminalReady_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
        }

    };

    class AisStaticDataReportMessageColumnData : public AisMessageColumnData
    {
        Int32 partNumber_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[PartNumber]";
        static constexpr std::wstring_view ViewName = L"AisStaticDataReportMessageView";

        static constexpr SQLUSMALLINT PARTNUMBER_FIELD_ID = 8;

        AisStaticDataReportMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisStaticDataReportMessage;
        }

        Int32 PartNumber( ) const
        {
            return partNumber_;
        }
        void SetPartNumber( Int32 partNumber )
        {
            partNumber_ = partNumber;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, PARTNUMBER_FIELD_ID, &partNumber_);
        }

    };

    class AisStaticDataReportPartAMessageColumnData : public AisStaticDataReportMessageColumnData
    {
        Guid shipName_;
        Int32 spare_ = 0;
    public:
        using Base = AisStaticDataReportMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[PartNumber],[ShipName],[Spare]";
        static constexpr std::wstring_view ViewName = L"AisStaticDataReportPartAMessageView";

        static constexpr SQLUSMALLINT SHIPNAME_FIELD_ID = 9;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 10;

        AisStaticDataReportPartAMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisStaticDataReportPartAMessage;
        }

        Guid ShipName( ) const
        {
            return shipName_;
        }
        void SetShipName( const Guid& shipName )
        {
            shipName_ = shipName;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, SHIPNAME_FIELD_ID, &shipName_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
        }

    };

    class AisStaticDataReportPartBMessageColumnData : public AisStaticDataReportMessageColumnData
    {
        Data::ShipType shipType_ = Data::ShipType::NotAvailable;
        std::array<wchar_t,101> vendorId_ = {};
        SQLLEN vendorIdLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 unitModelCode_ = 0;
        Int32 serialNumber_ = 0;
        Guid callsign_;
        Int32 dimensionToBow_ = 0;
        Int32 dimensionToStern_ = 0;
        Int32 dimensionToPort_ = 0;
        Int32 dimensionToStarboard_ = 0;
        Guid mothershipMmsi_;
        Data::PositionFixType positionFixType_ = Data::PositionFixType::Undefined1;
        Int32 spare_ = 0;
    public:
        using Base = AisStaticDataReportMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[PartNumber],[ShipType],[VendorId],[UnitModelCode],[SerialNumber],[Callsign],[DimensionToBow],[DimensionToStern],[DimensionToPort],[DimensionToStarboard],[MothershipMmsi],[PositionFixType],[Spare]";
        static constexpr std::wstring_view ViewName = L"AisStaticDataReportPartBMessageView";

        static constexpr SQLUSMALLINT SHIPTYPE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT VENDORID_FIELD_ID = 10;
        static constexpr SQLUSMALLINT UNITMODELCODE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT SERIALNUMBER_FIELD_ID = 12;
        static constexpr SQLUSMALLINT CALLSIGN_FIELD_ID = 13;
        static constexpr SQLUSMALLINT DIMENSIONTOBOW_FIELD_ID = 14;
        static constexpr SQLUSMALLINT DIMENSIONTOSTERN_FIELD_ID = 15;
        static constexpr SQLUSMALLINT DIMENSIONTOPORT_FIELD_ID = 16;
        static constexpr SQLUSMALLINT DIMENSIONTOSTARBOARD_FIELD_ID = 17;
        static constexpr SQLUSMALLINT MOTHERSHIPMMSI_FIELD_ID = 18;
        static constexpr SQLUSMALLINT POSITIONFIXTYPE_FIELD_ID = 19;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 20;

        AisStaticDataReportPartBMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisStaticDataReportPartBMessage;
        }

        Data::ShipType ShipType( ) const
        {
            return shipType_;
        }
        void SetShipType( Data::ShipType shipType )
        {
            shipType_ = shipType;
        }
        std::wstring_view VendorId( ) const
        {
            if(vendorIdLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(vendorId_.data(),static_cast<size_t>( vendorIdLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetVendorId( const WideString& vendorId )
        {
            Assign(vendorId, vendorId_, vendorIdLengthOrNullIndicator_);
        }
        Int32 UnitModelCode( ) const
        {
            return unitModelCode_;
        }
        void SetUnitModelCode( Int32 unitModelCode )
        {
            unitModelCode_ = unitModelCode;
        }
        Int32 SerialNumber( ) const
        {
            return serialNumber_;
        }
        void SetSerialNumber( Int32 serialNumber )
        {
            serialNumber_ = serialNumber;
        }
        Guid Callsign( ) const
        {
            return callsign_;
        }
        void SetCallsign( const Guid& callsign )
        {
            callsign_ = callsign;
        }
        Int32 DimensionToBow( ) const
        {
            return dimensionToBow_;
        }
        void SetDimensionToBow( Int32 dimensionToBow )
        {
            dimensionToBow_ = dimensionToBow;
        }
        Int32 DimensionToStern( ) const
        {
            return dimensionToStern_;
        }
        void SetDimensionToStern( Int32 dimensionToStern )
        {
            dimensionToStern_ = dimensionToStern;
        }
        Int32 DimensionToPort( ) const
        {
            return dimensionToPort_;
        }
        void SetDimensionToPort( Int32 dimensionToPort )
        {
            dimensionToPort_ = dimensionToPort;
        }
        Int32 DimensionToStarboard( ) const
        {
            return dimensionToStarboard_;
        }
        void SetDimensionToStarboard( Int32 dimensionToStarboard )
        {
            dimensionToStarboard_ = dimensionToStarboard;
        }
        Guid MothershipMmsi( ) const
        {
            return mothershipMmsi_;
        }
        void SetMothershipMmsi( const Guid& mothershipMmsi )
        {
            mothershipMmsi_ = mothershipMmsi;
        }
        Data::PositionFixType PositionFixType( ) const
        {
            return positionFixType_;
        }
        void SetPositionFixType( Data::PositionFixType positionFixType )
        {
            positionFixType_ = positionFixType;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, SHIPTYPE_FIELD_ID, &shipType_);
            Bind(statement, VENDORID_FIELD_ID, &vendorId_, &vendorIdLengthOrNullIndicator_);
            Bind(statement, UNITMODELCODE_FIELD_ID, &unitModelCode_);
            Bind(statement, SERIALNUMBER_FIELD_ID, &serialNumber_);
            Bind(statement, CALLSIGN_FIELD_ID, &callsign_);
            Bind(statement, DIMENSIONTOBOW_FIELD_ID, &dimensionToBow_);
            Bind(statement, DIMENSIONTOSTERN_FIELD_ID, &dimensionToStern_);
            Bind(statement, DIMENSIONTOPORT_FIELD_ID, &dimensionToPort_);
            Bind(statement, DIMENSIONTOSTARBOARD_FIELD_ID, &dimensionToStarboard_);
            Bind(statement, MOTHERSHIPMMSI_FIELD_ID, &mothershipMmsi_);
            Bind(statement, POSITIONFIXTYPE_FIELD_ID, &positionFixType_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
        }

    };

    class AisUtcAndDateInquiryMessageColumnData : public AisMessageColumnData
    {
        Int32 spare1_ = 0;
        Int32 destinationMmsi_ = 0;
        Int32 spare2_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[Spare1],[DestinationMmsi],[Spare2]";
        static constexpr std::wstring_view ViewName = L"AisUtcAndDateInquiryMessageView";

        static constexpr SQLUSMALLINT SPARE1_FIELD_ID = 8;
        static constexpr SQLUSMALLINT DESTINATIONMMSI_FIELD_ID = 9;
        static constexpr SQLUSMALLINT SPARE2_FIELD_ID = 10;

        AisUtcAndDateInquiryMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisUtcAndDateInquiryMessage;
        }

        Int32 Spare1( ) const
        {
            return spare1_;
        }
        void SetSpare1( Int32 spare1 )
        {
            spare1_ = spare1;
        }
        Int32 DestinationMmsi( ) const
        {
            return destinationMmsi_;
        }
        void SetDestinationMmsi( Int32 destinationMmsi )
        {
            destinationMmsi_ = destinationMmsi;
        }
        Int32 Spare2( ) const
        {
            return spare2_;
        }
        void SetSpare2( Int32 spare2 )
        {
            spare2_ = spare2;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, SPARE1_FIELD_ID, &spare1_);
            Bind(statement, DESTINATIONMMSI_FIELD_ID, &destinationMmsi_);
            Bind(statement, SPARE2_FIELD_ID, &spare2_);
        }

    };

    class AisUtcAndDateResponseMessageColumnData : public AisMessageColumnData
    {
        DateTime datetime_;
        Data::PositionAccuracy positionAccuracy_ = Data::PositionAccuracy::Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        Data::PositionFixType positionFixType_ = Data::PositionFixType::Undefined1;
        Int32 spare_ = 0;
        Data::Raim raim_ = Data::Raim::NotInUse;
        Int32 radioStatus_ = 0;
    public:
        using Base = AisMessageColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[ReceivedTimestamp],[MessageSequenceNumber],[Repeat],[Mmsi],[Datetime],[PositionAccuracy],[Longitude],[Latitude],[PositionFixType],[Spare],[Raim],[RadioStatus]";
        static constexpr std::wstring_view ViewName = L"AisUtcAndDateResponseMessageView";

        static constexpr SQLUSMALLINT DATETIME_FIELD_ID = 8;
        static constexpr SQLUSMALLINT POSITIONACCURACY_FIELD_ID = 9;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT POSITIONFIXTYPE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT SPARE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT RAIM_FIELD_ID = 14;
        static constexpr SQLUSMALLINT RADIOSTATUS_FIELD_ID = 15;

        AisUtcAndDateResponseMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisUtcAndDateResponseMessage;
        }

        DateTime Datetime( ) const
        {
            return datetime_;
        }
        void SetDatetime( const DateTime& datetime )
        {
            datetime_ = datetime;
        }
        Data::PositionAccuracy PositionAccuracy( ) const
        {
            return positionAccuracy_;
        }
        void SetPositionAccuracy( Data::PositionAccuracy positionAccuracy )
        {
            positionAccuracy_ = positionAccuracy;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        Data::PositionFixType PositionFixType( ) const
        {
            return positionFixType_;
        }
        void SetPositionFixType( Data::PositionFixType positionFixType )
        {
            positionFixType_ = positionFixType;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        void SetSpare( Int32 spare )
        {
            spare_ = spare;
        }
        Data::Raim Raim( ) const
        {
            return raim_;
        }
        void SetRaim( Data::Raim raim )
        {
            raim_ = raim;
        }
        Int32 RadioStatus( ) const
        {
            return radioStatus_;
        }
        void SetRadioStatus( Int32 radioStatus )
        {
            radioStatus_ = radioStatus;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DATETIME_FIELD_ID, &datetime_);
            Bind(statement, POSITIONACCURACY_FIELD_ID, &positionAccuracy_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, POSITIONFIXTYPE_FIELD_ID, &positionFixType_);
            Bind(statement, SPARE_FIELD_ID, &spare_);
            Bind(statement, RAIM_FIELD_ID, &raim_);
            Bind(statement, RADIOSTATUS_FIELD_ID, &radioStatus_);
        }

    };

    class AisTransceiverCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid aisTransceiver_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"AisTransceiverCommandView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT AISTRANSCEIVER_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REPLY_FIELD_ID = 7;

        AisTransceiverCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisTransceiverCommand;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid AisTransceiver( ) const
        {
            return aisTransceiver_;
        }
        void SetAisTransceiver( const Guid& aisTransceiver )
        {
            aisTransceiver_ = aisTransceiver;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        void SetDeviceCommandSourceType( Data::DeviceCommandSourceType deviceCommandSourceType )
        {
            deviceCommandSourceType_ = deviceCommandSourceType;
        }
        Guid DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        void SetDeviceCommandSourceId( const Guid& deviceCommandSourceId )
        {
            deviceCommandSourceId_ = deviceCommandSourceId;
        }
        Guid Reply( ) const
        {
            return reply_;
        }
        void SetReply( const Guid& reply )
        {
            reply_ = reply;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, AISTRANSCEIVER_FIELD_ID, &aisTransceiver_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEVICECOMMANDSOURCETYPE_FIELD_ID, &deviceCommandSourceType_);
            Bind(statement, DEVICECOMMANDSOURCEID_FIELD_ID, &deviceCommandSourceId_);
            Bind(statement, REPLY_FIELD_ID, &reply_);
        }

    };

    class AisTransceiverCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid aisTransceiver_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[Timestamp],[Command],[Status],[Message]";
        static constexpr std::wstring_view ViewName = L"AisTransceiverCommandReplyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT AISTRANSCEIVER_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COMMAND_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 7;

        AisTransceiverCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisTransceiverCommandReply;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid AisTransceiver( ) const
        {
            return aisTransceiver_;
        }
        void SetAisTransceiver( const Guid& aisTransceiver )
        {
            aisTransceiver_ = aisTransceiver;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Command( ) const
        {
            return command_;
        }
        void SetCommand( const Guid& command )
        {
            command_ = command;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::DeviceCommandReplyStatus status )
        {
            status_ = status;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, AISTRANSCEIVER_FIELD_ID, &aisTransceiver_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COMMAND_FIELD_ID, &command_);
            Bind(statement, STATUS_FIELD_ID, &status_);
        }

    };

    class AisTransceiverConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid aisTransceiver_;
        DateTime timestamp_;
        std::array<wchar_t,128> userName_ = {};
        SQLLEN userNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,128> password_ = {};
        SQLLEN passwordLengthOrNullIndicator_ = SQL_NULL_DATA;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        std::array<wchar_t,128> aisProviderLoginURL_ = {};
        SQLLEN aisProviderLoginURLLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,33> comPort_ = {};
        SQLLEN comPortLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 baudRate_ = 0;
        bool filterByArea_ = false;
        double upperLeftCornerLatitude_ = 0.0;
        double upperLeftCornerLongitude_ = 0.0;
        double bottomRightCornerLatitude_ = 0.0;
        double bottomRightCornerLongitude_ = 0.0;
        std::array<wchar_t,128> aisProviderIPAddress_ = {};
        SQLLEN aisProviderIPAddressLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 aisProviderPort_ = 0;
        bool useLogin_ = false;
        Int32 aisProviderLoginPort_ = 0;
        bool canSendAISMessage_ = false;
        WideString textMessageHeader_;
        SQLLEN textMessageHeaderLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString urls_;
        SQLLEN urlsLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 udpPort_ = 0;
        Data::AisTransceiverConnectionType connectionType_ = Data::AisTransceiverConnectionType::Unknown;
        bool enableRefreshAidToNavigationIn30sec_ = false;
        bool enableAidToNavigationFromFile_ = false;
        WideString aidToNavigationHeader_;
        SQLLEN aidToNavigationHeaderLengthOrNullIndicator_ = SQL_NULL_DATA;
        bool sendingMMSI_ = false;
        Int32 sourceUpdateRate_ = 0;
        bool enableRefreshStayingStillTargetIn30sec_ = false;
        WideString excludeSendAisBaseStation_;
        SQLLEN excludeSendAisBaseStationLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString excludeSendAisA_;
        SQLLEN excludeSendAisALengthOrNullIndicator_ = SQL_NULL_DATA;
        bool enableSendBaseStationAlarms_ = false;
        std::array<wchar_t,128> aisWebConfig_ = {};
        SQLLEN aisWebConfigLengthOrNullIndicator_ = SQL_NULL_DATA;
        bool enableBaseStation600_ = false;
        std::array<wchar_t,128> baseStation600IPAddress_ = {};
        SQLLEN baseStation600IPAddressLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 baseStation600Port_ = 0;
        Int32 esdInputCount_ = 0;
        bool storeReceivedSentences_ = false;
        bool storeSentMessages_ = false;
        bool storeUnsentMessages_ = false;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[Timestamp],[UserName],[Password],[Latitude],[Longitude],[AisProviderLoginURL],[ComPort],[BaudRate],[FilterByArea],[UpperLeftCornerLatitude],[UpperLeftCornerLongitude],[BottomRightCornerLatitude],[BottomRightCornerLongitude],[AisProviderIPAddress],[AisProviderPort],[UseLogin],[AisProviderLoginPort],[CanSendAISMessage],[UdpPort],[ConnectionType],[EnableRefreshAidToNavigationIn30sec],[EnableAidToNavigationFromFile],[SendingMMSI],[SourceUpdateRate],[EnableRefreshStayingStillTargetIn30sec],[EnableSendBaseStationAlarms],[AisWebConfig],[EnableBaseStation600],[BaseStation600IPAddress],[BaseStation600Port],[EsdInputCount],[StoreReceivedSentences],[StoreSentMessages],[StoreUnsentMessages],[TextMessageHeader],[Urls],[AidToNavigationHeader],[ExcludeSendAisBaseStation],[ExcludeSendAisA]";
        static constexpr std::wstring_view ViewName = L"AisTransceiverConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT AISTRANSCEIVER_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT USERNAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT PASSWORD_FIELD_ID = 6;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT AISPROVIDERLOGINURL_FIELD_ID = 9;
        static constexpr SQLUSMALLINT COMPORT_FIELD_ID = 10;
        static constexpr SQLUSMALLINT BAUDRATE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT FILTERBYAREA_FIELD_ID = 12;
        static constexpr SQLUSMALLINT UPPERLEFTCORNERLATITUDE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT UPPERLEFTCORNERLONGITUDE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT BOTTOMRIGHTCORNERLATITUDE_FIELD_ID = 15;
        static constexpr SQLUSMALLINT BOTTOMRIGHTCORNERLONGITUDE_FIELD_ID = 16;
        static constexpr SQLUSMALLINT AISPROVIDERIPADDRESS_FIELD_ID = 17;
        static constexpr SQLUSMALLINT AISPROVIDERPORT_FIELD_ID = 18;
        static constexpr SQLUSMALLINT USELOGIN_FIELD_ID = 19;
        static constexpr SQLUSMALLINT AISPROVIDERLOGINPORT_FIELD_ID = 20;
        static constexpr SQLUSMALLINT CANSENDAISMESSAGE_FIELD_ID = 21;
        static constexpr SQLUSMALLINT UDPPORT_FIELD_ID = 22;
        static constexpr SQLUSMALLINT CONNECTIONTYPE_FIELD_ID = 23;
        static constexpr SQLUSMALLINT ENABLEREFRESHAIDTONAVIGATIONIN30SEC_FIELD_ID = 24;
        static constexpr SQLUSMALLINT ENABLEAIDTONAVIGATIONFROMFILE_FIELD_ID = 25;
        static constexpr SQLUSMALLINT SENDINGMMSI_FIELD_ID = 26;
        static constexpr SQLUSMALLINT SOURCEUPDATERATE_FIELD_ID = 27;
        static constexpr SQLUSMALLINT ENABLEREFRESHSTAYINGSTILLTARGETIN30SEC_FIELD_ID = 28;
        static constexpr SQLUSMALLINT ENABLESENDBASESTATIONALARMS_FIELD_ID = 29;
        static constexpr SQLUSMALLINT AISWEBCONFIG_FIELD_ID = 30;
        static constexpr SQLUSMALLINT ENABLEBASESTATION600_FIELD_ID = 31;
        static constexpr SQLUSMALLINT BASESTATION600IPADDRESS_FIELD_ID = 32;
        static constexpr SQLUSMALLINT BASESTATION600PORT_FIELD_ID = 33;
        static constexpr SQLUSMALLINT ESDINPUTCOUNT_FIELD_ID = 34;
        static constexpr SQLUSMALLINT STORERECEIVEDSENTENCES_FIELD_ID = 35;
        static constexpr SQLUSMALLINT STORESENTMESSAGES_FIELD_ID = 36;
        static constexpr SQLUSMALLINT STOREUNSENTMESSAGES_FIELD_ID = 37;
        static constexpr SQLUSMALLINT TEXTMESSAGEHEADER_FIELD_ID = 38;
        static constexpr SQLUSMALLINT URLS_FIELD_ID = 39;
        static constexpr SQLUSMALLINT AIDTONAVIGATIONHEADER_FIELD_ID = 40;
        static constexpr SQLUSMALLINT EXCLUDESENDAISBASESTATION_FIELD_ID = 41;
        static constexpr SQLUSMALLINT EXCLUDESENDAISA_FIELD_ID = 42;

        AisTransceiverConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisTransceiverConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid AisTransceiver( ) const
        {
            return aisTransceiver_;
        }
        void SetAisTransceiver( const Guid& aisTransceiver )
        {
            aisTransceiver_ = aisTransceiver;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        std::wstring_view UserName( ) const
        {
            if(userNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(userName_.data(),static_cast<size_t>( userNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetUserName( const WideString& userName )
        {
            Assign(userName, userName_, userNameLengthOrNullIndicator_);
        }
        std::wstring_view Password( ) const
        {
            if(passwordLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(password_.data(),static_cast<size_t>( passwordLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPassword( const WideString& password )
        {
            Assign(password, password_, passwordLengthOrNullIndicator_);
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        std::wstring_view AisProviderLoginURL( ) const
        {
            if(aisProviderLoginURLLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(aisProviderLoginURL_.data(),static_cast<size_t>( aisProviderLoginURLLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetAisProviderLoginURL( const WideString& aisProviderLoginURL )
        {
            Assign(aisProviderLoginURL, aisProviderLoginURL_, aisProviderLoginURLLengthOrNullIndicator_);
        }
        std::wstring_view ComPort( ) const
        {
            if(comPortLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(comPort_.data(),static_cast<size_t>( comPortLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetComPort( const WideString& comPort )
        {
            Assign(comPort, comPort_, comPortLengthOrNullIndicator_);
        }
        Int32 BaudRate( ) const
        {
            return baudRate_;
        }
        void SetBaudRate( Int32 baudRate )
        {
            baudRate_ = baudRate;
        }
        bool FilterByArea( ) const
        {
            return filterByArea_;
        }
        void SetFilterByArea( bool filterByArea )
        {
            filterByArea_ = filterByArea;
        }
        double UpperLeftCornerLatitude( ) const
        {
            return upperLeftCornerLatitude_;
        }
        void SetUpperLeftCornerLatitude( double upperLeftCornerLatitude )
        {
            upperLeftCornerLatitude_ = upperLeftCornerLatitude;
        }
        double UpperLeftCornerLongitude( ) const
        {
            return upperLeftCornerLongitude_;
        }
        void SetUpperLeftCornerLongitude( double upperLeftCornerLongitude )
        {
            upperLeftCornerLongitude_ = upperLeftCornerLongitude;
        }
        double BottomRightCornerLatitude( ) const
        {
            return bottomRightCornerLatitude_;
        }
        void SetBottomRightCornerLatitude( double bottomRightCornerLatitude )
        {
            bottomRightCornerLatitude_ = bottomRightCornerLatitude;
        }
        double BottomRightCornerLongitude( ) const
        {
            return bottomRightCornerLongitude_;
        }
        void SetBottomRightCornerLongitude( double bottomRightCornerLongitude )
        {
            bottomRightCornerLongitude_ = bottomRightCornerLongitude;
        }
        std::wstring_view AisProviderIPAddress( ) const
        {
            if(aisProviderIPAddressLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(aisProviderIPAddress_.data(),static_cast<size_t>( aisProviderIPAddressLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetAisProviderIPAddress( const WideString& aisProviderIPAddress )
        {
            Assign(aisProviderIPAddress, aisProviderIPAddress_, aisProviderIPAddressLengthOrNullIndicator_);
        }
        Int32 AisProviderPort( ) const
        {
            return aisProviderPort_;
        }
        void SetAisProviderPort( Int32 aisProviderPort )
        {
            aisProviderPort_ = aisProviderPort;
        }
        bool UseLogin( ) const
        {
            return useLogin_;
        }
        void SetUseLogin( bool useLogin )
        {
            useLogin_ = useLogin;
        }
        Int32 AisProviderLoginPort( ) const
        {
            return aisProviderLoginPort_;
        }
        void SetAisProviderLoginPort( Int32 aisProviderLoginPort )
        {
            aisProviderLoginPort_ = aisProviderLoginPort;
        }
        bool CanSendAISMessage( ) const
        {
            return canSendAISMessage_;
        }
        void SetCanSendAISMessage( bool canSendAISMessage )
        {
            canSendAISMessage_ = canSendAISMessage;
        }
        const WideString& TextMessageHeader( ) const
        {
            return textMessageHeader_;
        }
        void SetTextMessageHeader( const WideString& textMessageHeader )
        {
            Assign(textMessageHeader, textMessageHeader_, textMessageHeaderLengthOrNullIndicator_);
        }
        const WideString& Urls( ) const
        {
            return urls_;
        }
        void SetUrls( const WideString& urls )
        {
            Assign(urls, urls_, urlsLengthOrNullIndicator_);
        }
        Int32 UdpPort( ) const
        {
            return udpPort_;
        }
        void SetUdpPort( Int32 udpPort )
        {
            udpPort_ = udpPort;
        }
        Data::AisTransceiverConnectionType ConnectionType( ) const
        {
            return connectionType_;
        }
        void SetConnectionType( Data::AisTransceiverConnectionType connectionType )
        {
            connectionType_ = connectionType;
        }
        bool EnableRefreshAidToNavigationIn30sec( ) const
        {
            return enableRefreshAidToNavigationIn30sec_;
        }
        void SetEnableRefreshAidToNavigationIn30sec( bool enableRefreshAidToNavigationIn30sec )
        {
            enableRefreshAidToNavigationIn30sec_ = enableRefreshAidToNavigationIn30sec;
        }
        bool EnableAidToNavigationFromFile( ) const
        {
            return enableAidToNavigationFromFile_;
        }
        void SetEnableAidToNavigationFromFile( bool enableAidToNavigationFromFile )
        {
            enableAidToNavigationFromFile_ = enableAidToNavigationFromFile;
        }
        const WideString& AidToNavigationHeader( ) const
        {
            return aidToNavigationHeader_;
        }
        void SetAidToNavigationHeader( const WideString& aidToNavigationHeader )
        {
            Assign(aidToNavigationHeader, aidToNavigationHeader_, aidToNavigationHeaderLengthOrNullIndicator_);
        }
        bool SendingMMSI( ) const
        {
            return sendingMMSI_;
        }
        void SetSendingMMSI( bool sendingMMSI )
        {
            sendingMMSI_ = sendingMMSI;
        }
        Int32 SourceUpdateRate( ) const
        {
            return sourceUpdateRate_;
        }
        void SetSourceUpdateRate( Int32 sourceUpdateRate )
        {
            sourceUpdateRate_ = sourceUpdateRate;
        }
        bool EnableRefreshStayingStillTargetIn30sec( ) const
        {
            return enableRefreshStayingStillTargetIn30sec_;
        }
        void SetEnableRefreshStayingStillTargetIn30sec( bool enableRefreshStayingStillTargetIn30sec )
        {
            enableRefreshStayingStillTargetIn30sec_ = enableRefreshStayingStillTargetIn30sec;
        }
        const WideString& ExcludeSendAisBaseStation( ) const
        {
            return excludeSendAisBaseStation_;
        }
        void SetExcludeSendAisBaseStation( const WideString& excludeSendAisBaseStation )
        {
            Assign(excludeSendAisBaseStation, excludeSendAisBaseStation_, excludeSendAisBaseStationLengthOrNullIndicator_);
        }
        const WideString& ExcludeSendAisA( ) const
        {
            return excludeSendAisA_;
        }
        void SetExcludeSendAisA( const WideString& excludeSendAisA )
        {
            Assign(excludeSendAisA, excludeSendAisA_, excludeSendAisALengthOrNullIndicator_);
        }
        bool EnableSendBaseStationAlarms( ) const
        {
            return enableSendBaseStationAlarms_;
        }
        void SetEnableSendBaseStationAlarms( bool enableSendBaseStationAlarms )
        {
            enableSendBaseStationAlarms_ = enableSendBaseStationAlarms;
        }
        std::wstring_view AisWebConfig( ) const
        {
            if(aisWebConfigLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(aisWebConfig_.data(),static_cast<size_t>( aisWebConfigLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetAisWebConfig( const WideString& aisWebConfig )
        {
            Assign(aisWebConfig, aisWebConfig_, aisWebConfigLengthOrNullIndicator_);
        }
        bool EnableBaseStation600( ) const
        {
            return enableBaseStation600_;
        }
        void SetEnableBaseStation600( bool enableBaseStation600 )
        {
            enableBaseStation600_ = enableBaseStation600;
        }
        std::wstring_view BaseStation600IPAddress( ) const
        {
            if(baseStation600IPAddressLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(baseStation600IPAddress_.data(),static_cast<size_t>( baseStation600IPAddressLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetBaseStation600IPAddress( const WideString& baseStation600IPAddress )
        {
            Assign(baseStation600IPAddress, baseStation600IPAddress_, baseStation600IPAddressLengthOrNullIndicator_);
        }
        Int32 BaseStation600Port( ) const
        {
            return baseStation600Port_;
        }
        void SetBaseStation600Port( Int32 baseStation600Port )
        {
            baseStation600Port_ = baseStation600Port;
        }
        Int32 EsdInputCount( ) const
        {
            return esdInputCount_;
        }
        void SetEsdInputCount( Int32 esdInputCount )
        {
            esdInputCount_ = esdInputCount;
        }
        bool StoreReceivedSentences( ) const
        {
            return storeReceivedSentences_;
        }
        void SetStoreReceivedSentences( bool storeReceivedSentences )
        {
            storeReceivedSentences_ = storeReceivedSentences;
        }
        bool StoreSentMessages( ) const
        {
            return storeSentMessages_;
        }
        void SetStoreSentMessages( bool storeSentMessages )
        {
            storeSentMessages_ = storeSentMessages;
        }
        bool StoreUnsentMessages( ) const
        {
            return storeUnsentMessages_;
        }
        void SetStoreUnsentMessages( bool storeUnsentMessages )
        {
            storeUnsentMessages_ = storeUnsentMessages;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, AISTRANSCEIVER_FIELD_ID, &aisTransceiver_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, USERNAME_FIELD_ID, &userName_, &userNameLengthOrNullIndicator_);
            Bind(statement, PASSWORD_FIELD_ID, &password_, &passwordLengthOrNullIndicator_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, AISPROVIDERLOGINURL_FIELD_ID, &aisProviderLoginURL_, &aisProviderLoginURLLengthOrNullIndicator_);
            Bind(statement, COMPORT_FIELD_ID, &comPort_, &comPortLengthOrNullIndicator_);
            Bind(statement, BAUDRATE_FIELD_ID, &baudRate_);
            Bind(statement, FILTERBYAREA_FIELD_ID, &filterByArea_);
            Bind(statement, UPPERLEFTCORNERLATITUDE_FIELD_ID, &upperLeftCornerLatitude_);
            Bind(statement, UPPERLEFTCORNERLONGITUDE_FIELD_ID, &upperLeftCornerLongitude_);
            Bind(statement, BOTTOMRIGHTCORNERLATITUDE_FIELD_ID, &bottomRightCornerLatitude_);
            Bind(statement, BOTTOMRIGHTCORNERLONGITUDE_FIELD_ID, &bottomRightCornerLongitude_);
            Bind(statement, AISPROVIDERIPADDRESS_FIELD_ID, &aisProviderIPAddress_, &aisProviderIPAddressLengthOrNullIndicator_);
            Bind(statement, AISPROVIDERPORT_FIELD_ID, &aisProviderPort_);
            Bind(statement, USELOGIN_FIELD_ID, &useLogin_);
            Bind(statement, AISPROVIDERLOGINPORT_FIELD_ID, &aisProviderLoginPort_);
            Bind(statement, CANSENDAISMESSAGE_FIELD_ID, &canSendAISMessage_);
            Bind(statement, UDPPORT_FIELD_ID, &udpPort_);
            Bind(statement, CONNECTIONTYPE_FIELD_ID, &connectionType_);
            Bind(statement, ENABLEREFRESHAIDTONAVIGATIONIN30SEC_FIELD_ID, &enableRefreshAidToNavigationIn30sec_);
            Bind(statement, ENABLEAIDTONAVIGATIONFROMFILE_FIELD_ID, &enableAidToNavigationFromFile_);
            Bind(statement, SENDINGMMSI_FIELD_ID, &sendingMMSI_);
            Bind(statement, SOURCEUPDATERATE_FIELD_ID, &sourceUpdateRate_);
            Bind(statement, ENABLEREFRESHSTAYINGSTILLTARGETIN30SEC_FIELD_ID, &enableRefreshStayingStillTargetIn30sec_);
            Bind(statement, ENABLESENDBASESTATIONALARMS_FIELD_ID, &enableSendBaseStationAlarms_);
            Bind(statement, AISWEBCONFIG_FIELD_ID, &aisWebConfig_, &aisWebConfigLengthOrNullIndicator_);
            Bind(statement, ENABLEBASESTATION600_FIELD_ID, &enableBaseStation600_);
            Bind(statement, BASESTATION600IPADDRESS_FIELD_ID, &baseStation600IPAddress_, &baseStation600IPAddressLengthOrNullIndicator_);
            Bind(statement, BASESTATION600PORT_FIELD_ID, &baseStation600Port_);
            Bind(statement, ESDINPUTCOUNT_FIELD_ID, &esdInputCount_);
            Bind(statement, STORERECEIVEDSENTENCES_FIELD_ID, &storeReceivedSentences_);
            Bind(statement, STORESENTMESSAGES_FIELD_ID, &storeSentMessages_);
            Bind(statement, STOREUNSENTMESSAGES_FIELD_ID, &storeUnsentMessages_);
        }

    };

    class AisTransceiverRawMessageColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid aisTransceiver_;
        DateTime timestamp_;
        bool isSent_ = false;
        std::array<wchar_t,101> message_ = {};
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[Timestamp],[IsSent],[Message]";
        static constexpr std::wstring_view ViewName = L"AisTransceiverRawMessageView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT AISTRANSCEIVER_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT ISSENT_FIELD_ID = 5;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 6;

        AisTransceiverRawMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisTransceiverRawMessage;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid AisTransceiver( ) const
        {
            return aisTransceiver_;
        }
        void SetAisTransceiver( const Guid& aisTransceiver )
        {
            aisTransceiver_ = aisTransceiver;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        bool IsSent( ) const
        {
            return isSent_;
        }
        void SetIsSent( bool isSent )
        {
            isSent_ = isSent;
        }
        std::wstring_view Message( ) const
        {
            if(messageLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(message_.data(),static_cast<size_t>( messageLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, AISTRANSCEIVER_FIELD_ID, &aisTransceiver_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, ISSENT_FIELD_ID, &isSent_);
            Bind(statement, MESSAGE_FIELD_ID, &message_, &messageLengthOrNullIndicator_);
        }

    };

    class AisTransceiverRawSentenceColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid aisTransceiver_;
        DateTime timestamp_;
        WideString sentence_;
        SQLLEN sentenceLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AisTransceiver],[Timestamp],[Sentence]";
        static constexpr std::wstring_view ViewName = L"AisTransceiverRawSentenceView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT AISTRANSCEIVER_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT SENTENCE_FIELD_ID = 5;

        AisTransceiverRawSentenceColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisTransceiverRawSentence;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid AisTransceiver( ) const
        {
            return aisTransceiver_;
        }
        void SetAisTransceiver( const Guid& aisTransceiver )
        {
            aisTransceiver_ = aisTransceiver;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        const WideString& Sentence( ) const
        {
            return sentence_;
        }
        void SetSentence( const WideString& sentence )
        {
            Assign(sentence, sentence_, sentenceLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, AISTRANSCEIVER_FIELD_ID, &aisTransceiver_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
        }

    };

    class AlarmStateChangeColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid alarm_;
        DateTime timestamp_;
        Data::AlarmState state_ = Data::AlarmState::Unknown;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Alarm],[Timestamp],[State]";
        static constexpr std::wstring_view ViewName = L"AlarmStateChangeView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ALARM_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT STATE_FIELD_ID = 5;

        AlarmStateChangeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AlarmStateChange;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Alarm( ) const
        {
            return alarm_;
        }
        void SetAlarm( const Guid& alarm )
        {
            alarm_ = alarm;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::AlarmState State( ) const
        {
            return state_;
        }
        void SetState( Data::AlarmState state )
        {
            state_ = state;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ALARM_FIELD_ID, &alarm_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, STATE_FIELD_ID, &state_);
        }

    };

    class BaseStationTypeColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name]";
        static constexpr std::wstring_view ViewName = L"BaseStationTypeView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;

        BaseStationTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BaseStationType;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class BinaryTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        std::vector<Byte> value_;
        SQLLEN valueLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"BinaryTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        BinaryTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BinaryTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        const std::vector<Byte>& Value( ) const
        {
            return value_;
        }
        void SetValue( const std::vector<Byte>& value )
        {
            Assign(value, value_, valueLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
        }

    };

    class BookmarkColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid view_;
        std::array<wchar_t,101> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        DateTime timestamp_;
        SQLLEN timestampNullIndicator_ = SQL_NULL_DATA;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double zoomLevel_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[View],[Name],[Timestamp],[Latitude],[Longitude],[ZoomLevel]";
        static constexpr std::wstring_view ViewName = L"BookmarkView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT VIEW_FIELD_ID = 3;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 5;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT ZOOMLEVEL_FIELD_ID = 8;

        BookmarkColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Bookmark;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid View( ) const
        {
            return view_;
        }
        void SetView( const Guid& view )
        {
            view_ = view;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double ZoomLevel( ) const
        {
            return zoomLevel_;
        }
        void SetZoomLevel( double zoomLevel )
        {
            zoomLevel_ = zoomLevel;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, VIEW_FIELD_ID, &view_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_, &timestampNullIndicator_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, ZOOMLEVEL_FIELD_ID, &zoomLevel_);
        }

    };

    class BooleanTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        bool value_ = false;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"BooleanTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        BooleanTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BooleanTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        bool Value( ) const
        {
            return value_;
        }
        void SetValue( bool value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class ByteTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        Byte value_ = 0;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"ByteTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        ByteTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ByteTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Byte Value( ) const
        {
            return value_;
        }
        void SetValue( Byte value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class CameraCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"CameraCommandView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CAMERA_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REPLY_FIELD_ID = 7;

        CameraCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommand;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Camera( ) const
        {
            return camera_;
        }
        void SetCamera( const Guid& camera )
        {
            camera_ = camera;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        void SetDeviceCommandSourceType( Data::DeviceCommandSourceType deviceCommandSourceType )
        {
            deviceCommandSourceType_ = deviceCommandSourceType;
        }
        Guid DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        void SetDeviceCommandSourceId( const Guid& deviceCommandSourceId )
        {
            deviceCommandSourceId_ = deviceCommandSourceId;
        }
        Guid Reply( ) const
        {
            return reply_;
        }
        void SetReply( const Guid& reply )
        {
            reply_ = reply;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CAMERA_FIELD_ID, &camera_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEVICECOMMANDSOURCETYPE_FIELD_ID, &deviceCommandSourceType_);
            Bind(statement, DEVICECOMMANDSOURCEID_FIELD_ID, &deviceCommandSourceId_);
            Bind(statement, REPLY_FIELD_ID, &reply_);
        }

    };

    class CameraCommandAbsoluteMoveColumnData : public CameraCommandColumnData
    {
        Data::CameraPanTiltMode positionPanTiltMode_ = Data::CameraPanTiltMode::Unknown;
        double panAngle_ = 0.0;
        SQLLEN panAngleNullIndicator_ = SQL_NULL_DATA;
        double tiltAngle_ = 0.0;
        SQLLEN tiltAngleNullIndicator_ = SQL_NULL_DATA;
        Data::CameraFocalLengthMode positionFocalLengthMode_ = Data::CameraFocalLengthMode::Unknown;
        double focalLength_ = 0.0;
        SQLLEN focalLengthNullIndicator_ = SQL_NULL_DATA;
        Data::CameraPanTiltMode speedPanTiltMode_ = Data::CameraPanTiltMode::Unknown;
        double panSpeed_ = 0.0;
        SQLLEN panSpeedNullIndicator_ = SQL_NULL_DATA;
        double tiltSpeed_ = 0.0;
        SQLLEN tiltSpeedNullIndicator_ = SQL_NULL_DATA;
        Data::CameraFocalLengthMode speedFocalLengthMode_ = Data::CameraFocalLengthMode::Unknown;
        double zoomSpeed_ = 0.0;
        SQLLEN zoomSpeedNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[PositionPanTiltMode],[PanAngle],[TiltAngle],[PositionFocalLengthMode],[FocalLength],[SpeedPanTiltMode],[PanSpeed],[TiltSpeed],[SpeedFocalLengthMode],[ZoomSpeed]";
        static constexpr std::wstring_view ViewName = L"CameraCommandAbsoluteMoveView";

        static constexpr SQLUSMALLINT POSITIONPANTILTMODE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT PANANGLE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT TILTANGLE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT POSITIONFOCALLENGTHMODE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT FOCALLENGTH_FIELD_ID = 12;
        static constexpr SQLUSMALLINT SPEEDPANTILTMODE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT PANSPEED_FIELD_ID = 14;
        static constexpr SQLUSMALLINT TILTSPEED_FIELD_ID = 15;
        static constexpr SQLUSMALLINT SPEEDFOCALLENGTHMODE_FIELD_ID = 16;
        static constexpr SQLUSMALLINT ZOOMSPEED_FIELD_ID = 17;

        CameraCommandAbsoluteMoveColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandAbsoluteMove;
        }

        Data::CameraPanTiltMode PositionPanTiltMode( ) const
        {
            return positionPanTiltMode_;
        }
        void SetPositionPanTiltMode( Data::CameraPanTiltMode positionPanTiltMode )
        {
            positionPanTiltMode_ = positionPanTiltMode;
        }
        double PanAngle( ) const
        {
            return panAngle_;
        }
        void SetPanAngle( double panAngle )
        {
            panAngle_ = panAngle;
        }
        double TiltAngle( ) const
        {
            return tiltAngle_;
        }
        void SetTiltAngle( double tiltAngle )
        {
            tiltAngle_ = tiltAngle;
        }
        Data::CameraFocalLengthMode PositionFocalLengthMode( ) const
        {
            return positionFocalLengthMode_;
        }
        void SetPositionFocalLengthMode( Data::CameraFocalLengthMode positionFocalLengthMode )
        {
            positionFocalLengthMode_ = positionFocalLengthMode;
        }
        double FocalLength( ) const
        {
            return focalLength_;
        }
        void SetFocalLength( double focalLength )
        {
            focalLength_ = focalLength;
        }
        Data::CameraPanTiltMode SpeedPanTiltMode( ) const
        {
            return speedPanTiltMode_;
        }
        void SetSpeedPanTiltMode( Data::CameraPanTiltMode speedPanTiltMode )
        {
            speedPanTiltMode_ = speedPanTiltMode;
        }
        double PanSpeed( ) const
        {
            return panSpeed_;
        }
        void SetPanSpeed( double panSpeed )
        {
            panSpeed_ = panSpeed;
        }
        double TiltSpeed( ) const
        {
            return tiltSpeed_;
        }
        void SetTiltSpeed( double tiltSpeed )
        {
            tiltSpeed_ = tiltSpeed;
        }
        Data::CameraFocalLengthMode SpeedFocalLengthMode( ) const
        {
            return speedFocalLengthMode_;
        }
        void SetSpeedFocalLengthMode( Data::CameraFocalLengthMode speedFocalLengthMode )
        {
            speedFocalLengthMode_ = speedFocalLengthMode;
        }
        double ZoomSpeed( ) const
        {
            return zoomSpeed_;
        }
        void SetZoomSpeed( double zoomSpeed )
        {
            zoomSpeed_ = zoomSpeed;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, POSITIONPANTILTMODE_FIELD_ID, &positionPanTiltMode_);
            Bind(statement, PANANGLE_FIELD_ID, &panAngle_, &panAngleNullIndicator_);
            Bind(statement, TILTANGLE_FIELD_ID, &tiltAngle_, &tiltAngleNullIndicator_);
            Bind(statement, POSITIONFOCALLENGTHMODE_FIELD_ID, &positionFocalLengthMode_);
            Bind(statement, FOCALLENGTH_FIELD_ID, &focalLength_, &focalLengthNullIndicator_);
            Bind(statement, SPEEDPANTILTMODE_FIELD_ID, &speedPanTiltMode_);
            Bind(statement, PANSPEED_FIELD_ID, &panSpeed_, &panSpeedNullIndicator_);
            Bind(statement, TILTSPEED_FIELD_ID, &tiltSpeed_, &tiltSpeedNullIndicator_);
            Bind(statement, SPEEDFOCALLENGTHMODE_FIELD_ID, &speedFocalLengthMode_);
            Bind(statement, ZOOMSPEED_FIELD_ID, &zoomSpeed_, &zoomSpeedNullIndicator_);
        }

    };

    class CameraCommandAdjustPanTiltZoomColumnData : public CameraCommandColumnData
    {
        double x_ = 0.0;
        SQLLEN xNullIndicator_ = SQL_NULL_DATA;
        double y_ = 0.0;
        SQLLEN yNullIndicator_ = SQL_NULL_DATA;
        double z_ = 0.0;
        SQLLEN zNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[X],[Y],[Z]";
        static constexpr std::wstring_view ViewName = L"CameraCommandAdjustPanTiltZoomView";

        static constexpr SQLUSMALLINT X_FIELD_ID = 8;
        static constexpr SQLUSMALLINT Y_FIELD_ID = 9;
        static constexpr SQLUSMALLINT Z_FIELD_ID = 10;

        CameraCommandAdjustPanTiltZoomColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandAdjustPanTiltZoom;
        }

        double X( ) const
        {
            return x_;
        }
        void SetX( double x )
        {
            x_ = x;
        }
        double Y( ) const
        {
            return y_;
        }
        void SetY( double y )
        {
            y_ = y;
        }
        double Z( ) const
        {
            return z_;
        }
        void SetZ( double z )
        {
            z_ = z;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, X_FIELD_ID, &x_, &xNullIndicator_);
            Bind(statement, Y_FIELD_ID, &y_, &yNullIndicator_);
            Bind(statement, Z_FIELD_ID, &z_, &zNullIndicator_);
        }

    };

    class CameraCommandContinuousMoveColumnData : public CameraCommandColumnData
    {
        bool normalized_ = false;
        double panVelocity_ = 0.0;
        SQLLEN panVelocityNullIndicator_ = SQL_NULL_DATA;
        double tiltVelocity_ = 0.0;
        SQLLEN tiltVelocityNullIndicator_ = SQL_NULL_DATA;
        double zoomVelocity_ = 0.0;
        SQLLEN zoomVelocityNullIndicator_ = SQL_NULL_DATA;
        TimeSpan duration_;
        SQLLEN durationNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[Normalized],[PanVelocity],[TiltVelocity],[ZoomVelocity],[Duration]";
        static constexpr std::wstring_view ViewName = L"CameraCommandContinuousMoveView";

        static constexpr SQLUSMALLINT NORMALIZED_FIELD_ID = 8;
        static constexpr SQLUSMALLINT PANVELOCITY_FIELD_ID = 9;
        static constexpr SQLUSMALLINT TILTVELOCITY_FIELD_ID = 10;
        static constexpr SQLUSMALLINT ZOOMVELOCITY_FIELD_ID = 11;
        static constexpr SQLUSMALLINT DURATION_FIELD_ID = 12;

        CameraCommandContinuousMoveColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandContinuousMove;
        }

        bool Normalized( ) const
        {
            return normalized_;
        }
        void SetNormalized( bool normalized )
        {
            normalized_ = normalized;
        }
        double PanVelocity( ) const
        {
            return panVelocity_;
        }
        void SetPanVelocity( double panVelocity )
        {
            panVelocity_ = panVelocity;
        }
        double TiltVelocity( ) const
        {
            return tiltVelocity_;
        }
        void SetTiltVelocity( double tiltVelocity )
        {
            tiltVelocity_ = tiltVelocity;
        }
        double ZoomVelocity( ) const
        {
            return zoomVelocity_;
        }
        void SetZoomVelocity( double zoomVelocity )
        {
            zoomVelocity_ = zoomVelocity;
        }
        TimeSpan Duration( ) const
        {
            return duration_;
        }
        void SetDuration( const TimeSpan& duration )
        {
            duration_ = duration;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NORMALIZED_FIELD_ID, &normalized_);
            Bind(statement, PANVELOCITY_FIELD_ID, &panVelocity_, &panVelocityNullIndicator_);
            Bind(statement, TILTVELOCITY_FIELD_ID, &tiltVelocity_, &tiltVelocityNullIndicator_);
            Bind(statement, ZOOMVELOCITY_FIELD_ID, &zoomVelocity_, &zoomVelocityNullIndicator_);
            Bind(statement, DURATION_FIELD_ID, &duration_, &durationNullIndicator_);
        }

    };

    class CameraCommandGeoMoveColumnData : public CameraCommandColumnData
    {
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double altitude_ = 0.0;
        SQLLEN altitudeNullIndicator_ = SQL_NULL_DATA;
        double viewportWidth_ = 0.0;
        SQLLEN viewportWidthNullIndicator_ = SQL_NULL_DATA;
        double viewportHeight_ = 0.0;
        SQLLEN viewportHeightNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[Latitude],[Longitude],[Altitude],[ViewportWidth],[ViewportHeight]";
        static constexpr std::wstring_view ViewName = L"CameraCommandGeoMoveView";

        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT ALTITUDE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT VIEWPORTWIDTH_FIELD_ID = 11;
        static constexpr SQLUSMALLINT VIEWPORTHEIGHT_FIELD_ID = 12;

        CameraCommandGeoMoveColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandGeoMove;
        }

        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Altitude( ) const
        {
            return altitude_;
        }
        void SetAltitude( double altitude )
        {
            altitude_ = altitude;
        }
        double ViewportWidth( ) const
        {
            return viewportWidth_;
        }
        void SetViewportWidth( double viewportWidth )
        {
            viewportWidth_ = viewportWidth;
        }
        double ViewportHeight( ) const
        {
            return viewportHeight_;
        }
        void SetViewportHeight( double viewportHeight )
        {
            viewportHeight_ = viewportHeight;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, ALTITUDE_FIELD_ID, &altitude_, &altitudeNullIndicator_);
            Bind(statement, VIEWPORTWIDTH_FIELD_ID, &viewportWidth_, &viewportWidthNullIndicator_);
            Bind(statement, VIEWPORTHEIGHT_FIELD_ID, &viewportHeight_, &viewportHeightNullIndicator_);
        }

    };

    class CameraCommandRelativeMoveColumnData : public CameraCommandColumnData
    {
        bool normalized_ = false;
        double panAngle_ = 0.0;
        SQLLEN panAngleNullIndicator_ = SQL_NULL_DATA;
        double tiltAngle_ = 0.0;
        SQLLEN tiltAngleNullIndicator_ = SQL_NULL_DATA;
        double focalLength_ = 0.0;
        SQLLEN focalLengthNullIndicator_ = SQL_NULL_DATA;
        double panSpeed_ = 0.0;
        SQLLEN panSpeedNullIndicator_ = SQL_NULL_DATA;
        double tiltSpeed_ = 0.0;
        SQLLEN tiltSpeedNullIndicator_ = SQL_NULL_DATA;
        double zoomSpeed_ = 0.0;
        SQLLEN zoomSpeedNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[Normalized],[PanAngle],[TiltAngle],[FocalLength],[PanSpeed],[TiltSpeed],[ZoomSpeed]";
        static constexpr std::wstring_view ViewName = L"CameraCommandRelativeMoveView";

        static constexpr SQLUSMALLINT NORMALIZED_FIELD_ID = 8;
        static constexpr SQLUSMALLINT PANANGLE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT TILTANGLE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT FOCALLENGTH_FIELD_ID = 11;
        static constexpr SQLUSMALLINT PANSPEED_FIELD_ID = 12;
        static constexpr SQLUSMALLINT TILTSPEED_FIELD_ID = 13;
        static constexpr SQLUSMALLINT ZOOMSPEED_FIELD_ID = 14;

        CameraCommandRelativeMoveColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandRelativeMove;
        }

        bool Normalized( ) const
        {
            return normalized_;
        }
        void SetNormalized( bool normalized )
        {
            normalized_ = normalized;
        }
        double PanAngle( ) const
        {
            return panAngle_;
        }
        void SetPanAngle( double panAngle )
        {
            panAngle_ = panAngle;
        }
        double TiltAngle( ) const
        {
            return tiltAngle_;
        }
        void SetTiltAngle( double tiltAngle )
        {
            tiltAngle_ = tiltAngle;
        }
        double FocalLength( ) const
        {
            return focalLength_;
        }
        void SetFocalLength( double focalLength )
        {
            focalLength_ = focalLength;
        }
        double PanSpeed( ) const
        {
            return panSpeed_;
        }
        void SetPanSpeed( double panSpeed )
        {
            panSpeed_ = panSpeed;
        }
        double TiltSpeed( ) const
        {
            return tiltSpeed_;
        }
        void SetTiltSpeed( double tiltSpeed )
        {
            tiltSpeed_ = tiltSpeed;
        }
        double ZoomSpeed( ) const
        {
            return zoomSpeed_;
        }
        void SetZoomSpeed( double zoomSpeed )
        {
            zoomSpeed_ = zoomSpeed;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NORMALIZED_FIELD_ID, &normalized_);
            Bind(statement, PANANGLE_FIELD_ID, &panAngle_, &panAngleNullIndicator_);
            Bind(statement, TILTANGLE_FIELD_ID, &tiltAngle_, &tiltAngleNullIndicator_);
            Bind(statement, FOCALLENGTH_FIELD_ID, &focalLength_, &focalLengthNullIndicator_);
            Bind(statement, PANSPEED_FIELD_ID, &panSpeed_, &panSpeedNullIndicator_);
            Bind(statement, TILTSPEED_FIELD_ID, &tiltSpeed_, &tiltSpeedNullIndicator_);
            Bind(statement, ZOOMSPEED_FIELD_ID, &zoomSpeed_, &zoomSpeedNullIndicator_);
        }

    };

    class CameraCommandReleasePTZOwnershipColumnData : public CameraCommandColumnData
    {
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"CameraCommandReleasePTZOwnershipView";

        CameraCommandReleasePTZOwnershipColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandReleasePTZOwnership;
        }

    };

    class CameraCommandRequestPTZOwnershipColumnData : public CameraCommandColumnData
    {
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"CameraCommandRequestPTZOwnershipView";

        CameraCommandRequestPTZOwnershipColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandRequestPTZOwnership;
        }

    };

    class CameraCommandSetAutoFocusColumnData : public CameraCommandColumnData
    {
        bool enabled_ = false;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[Enabled]";
        static constexpr std::wstring_view ViewName = L"CameraCommandSetAutoFocusView";

        static constexpr SQLUSMALLINT ENABLED_FIELD_ID = 8;

        CameraCommandSetAutoFocusColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandSetAutoFocus;
        }

        bool Enabled( ) const
        {
            return enabled_;
        }
        void SetEnabled( bool enabled )
        {
            enabled_ = enabled;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, ENABLED_FIELD_ID, &enabled_);
        }

    };

    class CameraCommandSetBlackAndWhiteColumnData : public CameraCommandColumnData
    {
        bool enabled_ = false;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[Enabled]";
        static constexpr std::wstring_view ViewName = L"CameraCommandSetBlackAndWhiteView";

        static constexpr SQLUSMALLINT ENABLED_FIELD_ID = 8;

        CameraCommandSetBlackAndWhiteColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandSetBlackAndWhite;
        }

        bool Enabled( ) const
        {
            return enabled_;
        }
        void SetEnabled( bool enabled )
        {
            enabled_ = enabled;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, ENABLED_FIELD_ID, &enabled_);
        }

    };

    class CameraCommandSetFollowedColumnData : public CameraCommandColumnData
    {
        Guid trackId_;
        Data::CameraFollowReason reason_ = Data::CameraFollowReason::Alarm;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[TrackId],[Reason]";
        static constexpr std::wstring_view ViewName = L"CameraCommandSetFollowedView";

        static constexpr SQLUSMALLINT TRACKID_FIELD_ID = 8;
        static constexpr SQLUSMALLINT REASON_FIELD_ID = 9;

        CameraCommandSetFollowedColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandSetFollowed;
        }

        Guid TrackId( ) const
        {
            return trackId_;
        }
        void SetTrackId( const Guid& trackId )
        {
            trackId_ = trackId;
        }
        Data::CameraFollowReason Reason( ) const
        {
            return reason_;
        }
        void SetReason( Data::CameraFollowReason reason )
        {
            reason_ = reason;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TRACKID_FIELD_ID, &trackId_);
            Bind(statement, REASON_FIELD_ID, &reason_);
        }

    };

    class CameraCommandSetInfraRedLampColumnData : public CameraCommandColumnData
    {
        bool enabled_ = false;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[Enabled]";
        static constexpr std::wstring_view ViewName = L"CameraCommandSetInfraRedLampView";

        static constexpr SQLUSMALLINT ENABLED_FIELD_ID = 8;

        CameraCommandSetInfraRedLampColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandSetInfraRedLamp;
        }

        bool Enabled( ) const
        {
            return enabled_;
        }
        void SetEnabled( bool enabled )
        {
            enabled_ = enabled;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, ENABLED_FIELD_ID, &enabled_);
        }

    };

    class CameraCommandSetWasherColumnData : public CameraCommandColumnData
    {
        bool enabled_ = false;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[Enabled]";
        static constexpr std::wstring_view ViewName = L"CameraCommandSetWasherView";

        static constexpr SQLUSMALLINT ENABLED_FIELD_ID = 8;

        CameraCommandSetWasherColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandSetWasher;
        }

        bool Enabled( ) const
        {
            return enabled_;
        }
        void SetEnabled( bool enabled )
        {
            enabled_ = enabled;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, ENABLED_FIELD_ID, &enabled_);
        }

    };

    class CameraCommandSetWiperColumnData : public CameraCommandColumnData
    {
        bool enabled_ = false;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[Enabled]";
        static constexpr std::wstring_view ViewName = L"CameraCommandSetWiperView";

        static constexpr SQLUSMALLINT ENABLED_FIELD_ID = 8;

        CameraCommandSetWiperColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandSetWiper;
        }

        bool Enabled( ) const
        {
            return enabled_;
        }
        void SetEnabled( bool enabled )
        {
            enabled_ = enabled;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, ENABLED_FIELD_ID, &enabled_);
        }

    };

    class CameraCommandStopColumnData : public CameraCommandColumnData
    {
        bool panTilt_ = false;
        bool zoom_ = false;
    public:
        using Base = CameraCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply],[PanTilt],[Zoom]";
        static constexpr std::wstring_view ViewName = L"CameraCommandStopView";

        static constexpr SQLUSMALLINT PANTILT_FIELD_ID = 8;
        static constexpr SQLUSMALLINT ZOOM_FIELD_ID = 9;

        CameraCommandStopColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandStop;
        }

        bool PanTilt( ) const
        {
            return panTilt_;
        }
        void SetPanTilt( bool panTilt )
        {
            panTilt_ = panTilt;
        }
        bool Zoom( ) const
        {
            return zoom_;
        }
        void SetZoom( bool zoom )
        {
            zoom_ = zoom;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, PANTILT_FIELD_ID, &panTilt_);
            Bind(statement, ZOOM_FIELD_ID, &zoom_);
        }

    };

    class CameraCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
        double panAngle_ = 0.0;
        double tiltAngle_ = 0.0;
        double focalLength_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[Command],[Status],[PanAngle],[TiltAngle],[FocalLength],[Message]";
        static constexpr std::wstring_view ViewName = L"CameraCommandReplyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CAMERA_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COMMAND_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT PANANGLE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT TILTANGLE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT FOCALLENGTH_FIELD_ID = 9;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 10;

        CameraCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraCommandReply;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Camera( ) const
        {
            return camera_;
        }
        void SetCamera( const Guid& camera )
        {
            camera_ = camera;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Command( ) const
        {
            return command_;
        }
        void SetCommand( const Guid& command )
        {
            command_ = command;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::DeviceCommandReplyStatus status )
        {
            status_ = status;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        double PanAngle( ) const
        {
            return panAngle_;
        }
        void SetPanAngle( double panAngle )
        {
            panAngle_ = panAngle;
        }
        double TiltAngle( ) const
        {
            return tiltAngle_;
        }
        void SetTiltAngle( double tiltAngle )
        {
            tiltAngle_ = tiltAngle;
        }
        double FocalLength( ) const
        {
            return focalLength_;
        }
        void SetFocalLength( double focalLength )
        {
            focalLength_ = focalLength;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CAMERA_FIELD_ID, &camera_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COMMAND_FIELD_ID, &command_);
            Bind(statement, STATUS_FIELD_ID, &status_);
            Bind(statement, PANANGLE_FIELD_ID, &panAngle_);
            Bind(statement, TILTANGLE_FIELD_ID, &tiltAngle_);
            Bind(statement, FOCALLENGTH_FIELD_ID, &focalLength_);
        }

    };

    class CameraConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
        Data::CameraControlProtocol cameraControlProtocol_ = Data::CameraControlProtocol::Unknown;
        std::array<wchar_t,128> cameraAddress_ = {};
        SQLLEN cameraAddressLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 cameraPort_ = 0;
        std::array<wchar_t,128> cameraControlAddress_ = {};
        SQLLEN cameraControlAddressLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 cameraControlPort_ = 0;
        std::array<wchar_t,128> cameraUserName_ = {};
        SQLLEN cameraUserNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,128> cameraPassword_ = {};
        SQLLEN cameraPasswordLengthOrNullIndicator_ = SQL_NULL_DATA;
        bool useRtspUriOverride_ = false;
        std::array<wchar_t,128> rtspUriOverride_ = {};
        SQLLEN rtspUriOverrideLengthOrNullIndicator_ = SQL_NULL_DATA;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double altitude_ = 0.0;
        bool useRelativePosition_ = false;
        double azimuthFromGPS_ = 0.0;
        double distanceFromGPS_ = 0.0;
        Data::CameraPanTiltMode panTiltMode_ = Data::CameraPanTiltMode::Unknown;
        double minTiltAngle_ = 0.0;
        double maxTiltAngle_ = 0.0;
        double minTiltScaleAngle_ = 0.0;
        double maxTiltScaleAngle_ = 0.0;
        bool useReverseTiltAngle_ = false;
        bool useReverseNormalizedTiltAngle_ = false;
        double minTiltVelocity_ = 0.0;
        double maxTiltVelocity_ = 0.0;
        double minTiltSpeed_ = 0.0;
        double maxTiltSpeed_ = 0.0;
        double minPanAngle_ = 0.0;
        double maxPanAngle_ = 0.0;
        double minPanScaleAngle_ = 0.0;
        double maxPanScaleAngle_ = 0.0;
        bool useReversePanAngle_ = false;
        bool useReverseNormalizedPanAngle_ = false;
        double minPanVelocity_ = 0.0;
        double maxPanVelocity_ = 0.0;
        double minPanSpeed_ = 0.0;
        double maxPanSpeed_ = 0.0;
        Data::CameraFocalLengthMode focalLengthMode_ = Data::CameraFocalLengthMode::Unknown;
        double minFocalLength_ = 0.0;
        double maxFocalLength_ = 0.0;
        double minFocalLengthScale_ = 0.0;
        double maxFocalLengthScale_ = 0.0;
        double minZoomVelocity_ = 0.0;
        double maxZoomVelocity_ = 0.0;
        double minZoomSpeed_ = 0.0;
        double maxZoomSpeed_ = 0.0;
        double imageSensorWidth_ = 0.0;
        double imageSensorHeight_ = 0.0;
        double homePanAngle_ = 0.0;
        double homeTiltAngle_ = 0.0;
        double homeFocalLength_ = 0.0;
        double panOffset_ = 0.0;
        double tiltOffset_ = 0.0;
        double aimAltitude_ = 0.0;
        double minimumTargetWidth_ = 0.0;
        TimeSpan targetLockTimeout_;
        TimeSpan updateStatusInterval_;
        TimeSpan readTimeout_;
        TimeSpan moveCommandStatusDelay_;
        std::array<wchar_t,128> ptzProfileName_ = {};
        SQLLEN ptzProfileNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,128> ptzConfigurationToken_ = {};
        SQLLEN ptzConfigurationTokenLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,128> videoSourceToken_ = {};
        SQLLEN videoSourceTokenLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp],[CameraControlProtocol],[CameraAddress],[CameraPort],[CameraControlAddress],[CameraControlPort],[CameraUserName],[CameraPassword],[UseRtspUriOverride],[RtspUriOverride],[Latitude],[Longitude],[Altitude],[UseRelativePosition],[AzimuthFromGPS],[DistanceFromGPS],[PanTiltMode],[MinTiltAngle],[MaxTiltAngle],[MinTiltScaleAngle],[MaxTiltScaleAngle],[UseReverseTiltAngle],[UseReverseNormalizedTiltAngle],[MinTiltVelocity],[MaxTiltVelocity],[MinTiltSpeed],[MaxTiltSpeed],[MinPanAngle],[MaxPanAngle],[MinPanScaleAngle],[MaxPanScaleAngle],[UseReversePanAngle],[UseReverseNormalizedPanAngle],[MinPanVelocity],[MaxPanVelocity],[MinPanSpeed],[MaxPanSpeed],[FocalLengthMode],[MinFocalLength],[MaxFocalLength],[MinFocalLengthScale],[MaxFocalLengthScale],[MinZoomVelocity],[MaxZoomVelocity],[MinZoomSpeed],[MaxZoomSpeed],[ImageSensorWidth],[ImageSensorHeight],[HomePanAngle],[HomeTiltAngle],[HomeFocalLength],[PanOffset],[TiltOffset],[AimAltitude],[MinimumTargetWidth],[TargetLockTimeout],[UpdateStatusInterval],[ReadTimeout],[MoveCommandStatusDelay],[PtzProfileName],[PtzConfigurationToken],[VideoSourceToken]";
        static constexpr std::wstring_view ViewName = L"CameraConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CAMERA_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT CAMERACONTROLPROTOCOL_FIELD_ID = 5;
        static constexpr SQLUSMALLINT CAMERAADDRESS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT CAMERAPORT_FIELD_ID = 7;
        static constexpr SQLUSMALLINT CAMERACONTROLADDRESS_FIELD_ID = 8;
        static constexpr SQLUSMALLINT CAMERACONTROLPORT_FIELD_ID = 9;
        static constexpr SQLUSMALLINT CAMERAUSERNAME_FIELD_ID = 10;
        static constexpr SQLUSMALLINT CAMERAPASSWORD_FIELD_ID = 11;
        static constexpr SQLUSMALLINT USERTSPURIOVERRIDE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT RTSPURIOVERRIDE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 15;
        static constexpr SQLUSMALLINT ALTITUDE_FIELD_ID = 16;
        static constexpr SQLUSMALLINT USERELATIVEPOSITION_FIELD_ID = 17;
        static constexpr SQLUSMALLINT AZIMUTHFROMGPS_FIELD_ID = 18;
        static constexpr SQLUSMALLINT DISTANCEFROMGPS_FIELD_ID = 19;
        static constexpr SQLUSMALLINT PANTILTMODE_FIELD_ID = 20;
        static constexpr SQLUSMALLINT MINTILTANGLE_FIELD_ID = 21;
        static constexpr SQLUSMALLINT MAXTILTANGLE_FIELD_ID = 22;
        static constexpr SQLUSMALLINT MINTILTSCALEANGLE_FIELD_ID = 23;
        static constexpr SQLUSMALLINT MAXTILTSCALEANGLE_FIELD_ID = 24;
        static constexpr SQLUSMALLINT USEREVERSETILTANGLE_FIELD_ID = 25;
        static constexpr SQLUSMALLINT USEREVERSENORMALIZEDTILTANGLE_FIELD_ID = 26;
        static constexpr SQLUSMALLINT MINTILTVELOCITY_FIELD_ID = 27;
        static constexpr SQLUSMALLINT MAXTILTVELOCITY_FIELD_ID = 28;
        static constexpr SQLUSMALLINT MINTILTSPEED_FIELD_ID = 29;
        static constexpr SQLUSMALLINT MAXTILTSPEED_FIELD_ID = 30;
        static constexpr SQLUSMALLINT MINPANANGLE_FIELD_ID = 31;
        static constexpr SQLUSMALLINT MAXPANANGLE_FIELD_ID = 32;
        static constexpr SQLUSMALLINT MINPANSCALEANGLE_FIELD_ID = 33;
        static constexpr SQLUSMALLINT MAXPANSCALEANGLE_FIELD_ID = 34;
        static constexpr SQLUSMALLINT USEREVERSEPANANGLE_FIELD_ID = 35;
        static constexpr SQLUSMALLINT USEREVERSENORMALIZEDPANANGLE_FIELD_ID = 36;
        static constexpr SQLUSMALLINT MINPANVELOCITY_FIELD_ID = 37;
        static constexpr SQLUSMALLINT MAXPANVELOCITY_FIELD_ID = 38;
        static constexpr SQLUSMALLINT MINPANSPEED_FIELD_ID = 39;
        static constexpr SQLUSMALLINT MAXPANSPEED_FIELD_ID = 40;
        static constexpr SQLUSMALLINT FOCALLENGTHMODE_FIELD_ID = 41;
        static constexpr SQLUSMALLINT MINFOCALLENGTH_FIELD_ID = 42;
        static constexpr SQLUSMALLINT MAXFOCALLENGTH_FIELD_ID = 43;
        static constexpr SQLUSMALLINT MINFOCALLENGTHSCALE_FIELD_ID = 44;
        static constexpr SQLUSMALLINT MAXFOCALLENGTHSCALE_FIELD_ID = 45;
        static constexpr SQLUSMALLINT MINZOOMVELOCITY_FIELD_ID = 46;
        static constexpr SQLUSMALLINT MAXZOOMVELOCITY_FIELD_ID = 47;
        static constexpr SQLUSMALLINT MINZOOMSPEED_FIELD_ID = 48;
        static constexpr SQLUSMALLINT MAXZOOMSPEED_FIELD_ID = 49;
        static constexpr SQLUSMALLINT IMAGESENSORWIDTH_FIELD_ID = 50;
        static constexpr SQLUSMALLINT IMAGESENSORHEIGHT_FIELD_ID = 51;
        static constexpr SQLUSMALLINT HOMEPANANGLE_FIELD_ID = 52;
        static constexpr SQLUSMALLINT HOMETILTANGLE_FIELD_ID = 53;
        static constexpr SQLUSMALLINT HOMEFOCALLENGTH_FIELD_ID = 54;
        static constexpr SQLUSMALLINT PANOFFSET_FIELD_ID = 55;
        static constexpr SQLUSMALLINT TILTOFFSET_FIELD_ID = 56;
        static constexpr SQLUSMALLINT AIMALTITUDE_FIELD_ID = 57;
        static constexpr SQLUSMALLINT MINIMUMTARGETWIDTH_FIELD_ID = 58;
        static constexpr SQLUSMALLINT TARGETLOCKTIMEOUT_FIELD_ID = 59;
        static constexpr SQLUSMALLINT UPDATESTATUSINTERVAL_FIELD_ID = 60;
        static constexpr SQLUSMALLINT READTIMEOUT_FIELD_ID = 61;
        static constexpr SQLUSMALLINT MOVECOMMANDSTATUSDELAY_FIELD_ID = 62;
        static constexpr SQLUSMALLINT PTZPROFILENAME_FIELD_ID = 63;
        static constexpr SQLUSMALLINT PTZCONFIGURATIONTOKEN_FIELD_ID = 64;
        static constexpr SQLUSMALLINT VIDEOSOURCETOKEN_FIELD_ID = 65;

        CameraConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Camera( ) const
        {
            return camera_;
        }
        void SetCamera( const Guid& camera )
        {
            camera_ = camera;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::CameraControlProtocol CameraControlProtocol( ) const
        {
            return cameraControlProtocol_;
        }
        void SetCameraControlProtocol( Data::CameraControlProtocol cameraControlProtocol )
        {
            cameraControlProtocol_ = cameraControlProtocol;
        }
        std::wstring_view CameraAddress( ) const
        {
            if(cameraAddressLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(cameraAddress_.data(),static_cast<size_t>( cameraAddressLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetCameraAddress( const WideString& cameraAddress )
        {
            Assign(cameraAddress, cameraAddress_, cameraAddressLengthOrNullIndicator_);
        }
        Int32 CameraPort( ) const
        {
            return cameraPort_;
        }
        void SetCameraPort( Int32 cameraPort )
        {
            cameraPort_ = cameraPort;
        }
        std::wstring_view CameraControlAddress( ) const
        {
            if(cameraControlAddressLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(cameraControlAddress_.data(),static_cast<size_t>( cameraControlAddressLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetCameraControlAddress( const WideString& cameraControlAddress )
        {
            Assign(cameraControlAddress, cameraControlAddress_, cameraControlAddressLengthOrNullIndicator_);
        }
        Int32 CameraControlPort( ) const
        {
            return cameraControlPort_;
        }
        void SetCameraControlPort( Int32 cameraControlPort )
        {
            cameraControlPort_ = cameraControlPort;
        }
        std::wstring_view CameraUserName( ) const
        {
            if(cameraUserNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(cameraUserName_.data(),static_cast<size_t>( cameraUserNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetCameraUserName( const WideString& cameraUserName )
        {
            Assign(cameraUserName, cameraUserName_, cameraUserNameLengthOrNullIndicator_);
        }
        std::wstring_view CameraPassword( ) const
        {
            if(cameraPasswordLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(cameraPassword_.data(),static_cast<size_t>( cameraPasswordLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetCameraPassword( const WideString& cameraPassword )
        {
            Assign(cameraPassword, cameraPassword_, cameraPasswordLengthOrNullIndicator_);
        }
        bool UseRtspUriOverride( ) const
        {
            return useRtspUriOverride_;
        }
        void SetUseRtspUriOverride( bool useRtspUriOverride )
        {
            useRtspUriOverride_ = useRtspUriOverride;
        }
        std::wstring_view RtspUriOverride( ) const
        {
            if(rtspUriOverrideLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(rtspUriOverride_.data(),static_cast<size_t>( rtspUriOverrideLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetRtspUriOverride( const WideString& rtspUriOverride )
        {
            Assign(rtspUriOverride, rtspUriOverride_, rtspUriOverrideLengthOrNullIndicator_);
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Altitude( ) const
        {
            return altitude_;
        }
        void SetAltitude( double altitude )
        {
            altitude_ = altitude;
        }
        bool UseRelativePosition( ) const
        {
            return useRelativePosition_;
        }
        void SetUseRelativePosition( bool useRelativePosition )
        {
            useRelativePosition_ = useRelativePosition;
        }
        double AzimuthFromGPS( ) const
        {
            return azimuthFromGPS_;
        }
        void SetAzimuthFromGPS( double azimuthFromGPS )
        {
            azimuthFromGPS_ = azimuthFromGPS;
        }
        double DistanceFromGPS( ) const
        {
            return distanceFromGPS_;
        }
        void SetDistanceFromGPS( double distanceFromGPS )
        {
            distanceFromGPS_ = distanceFromGPS;
        }
        Data::CameraPanTiltMode PanTiltMode( ) const
        {
            return panTiltMode_;
        }
        void SetPanTiltMode( Data::CameraPanTiltMode panTiltMode )
        {
            panTiltMode_ = panTiltMode;
        }
        double MinTiltAngle( ) const
        {
            return minTiltAngle_;
        }
        void SetMinTiltAngle( double minTiltAngle )
        {
            minTiltAngle_ = minTiltAngle;
        }
        double MaxTiltAngle( ) const
        {
            return maxTiltAngle_;
        }
        void SetMaxTiltAngle( double maxTiltAngle )
        {
            maxTiltAngle_ = maxTiltAngle;
        }
        double MinTiltScaleAngle( ) const
        {
            return minTiltScaleAngle_;
        }
        void SetMinTiltScaleAngle( double minTiltScaleAngle )
        {
            minTiltScaleAngle_ = minTiltScaleAngle;
        }
        double MaxTiltScaleAngle( ) const
        {
            return maxTiltScaleAngle_;
        }
        void SetMaxTiltScaleAngle( double maxTiltScaleAngle )
        {
            maxTiltScaleAngle_ = maxTiltScaleAngle;
        }
        bool UseReverseTiltAngle( ) const
        {
            return useReverseTiltAngle_;
        }
        void SetUseReverseTiltAngle( bool useReverseTiltAngle )
        {
            useReverseTiltAngle_ = useReverseTiltAngle;
        }
        bool UseReverseNormalizedTiltAngle( ) const
        {
            return useReverseNormalizedTiltAngle_;
        }
        void SetUseReverseNormalizedTiltAngle( bool useReverseNormalizedTiltAngle )
        {
            useReverseNormalizedTiltAngle_ = useReverseNormalizedTiltAngle;
        }
        double MinTiltVelocity( ) const
        {
            return minTiltVelocity_;
        }
        void SetMinTiltVelocity( double minTiltVelocity )
        {
            minTiltVelocity_ = minTiltVelocity;
        }
        double MaxTiltVelocity( ) const
        {
            return maxTiltVelocity_;
        }
        void SetMaxTiltVelocity( double maxTiltVelocity )
        {
            maxTiltVelocity_ = maxTiltVelocity;
        }
        double MinTiltSpeed( ) const
        {
            return minTiltSpeed_;
        }
        void SetMinTiltSpeed( double minTiltSpeed )
        {
            minTiltSpeed_ = minTiltSpeed;
        }
        double MaxTiltSpeed( ) const
        {
            return maxTiltSpeed_;
        }
        void SetMaxTiltSpeed( double maxTiltSpeed )
        {
            maxTiltSpeed_ = maxTiltSpeed;
        }
        double MinPanAngle( ) const
        {
            return minPanAngle_;
        }
        void SetMinPanAngle( double minPanAngle )
        {
            minPanAngle_ = minPanAngle;
        }
        double MaxPanAngle( ) const
        {
            return maxPanAngle_;
        }
        void SetMaxPanAngle( double maxPanAngle )
        {
            maxPanAngle_ = maxPanAngle;
        }
        double MinPanScaleAngle( ) const
        {
            return minPanScaleAngle_;
        }
        void SetMinPanScaleAngle( double minPanScaleAngle )
        {
            minPanScaleAngle_ = minPanScaleAngle;
        }
        double MaxPanScaleAngle( ) const
        {
            return maxPanScaleAngle_;
        }
        void SetMaxPanScaleAngle( double maxPanScaleAngle )
        {
            maxPanScaleAngle_ = maxPanScaleAngle;
        }
        bool UseReversePanAngle( ) const
        {
            return useReversePanAngle_;
        }
        void SetUseReversePanAngle( bool useReversePanAngle )
        {
            useReversePanAngle_ = useReversePanAngle;
        }
        bool UseReverseNormalizedPanAngle( ) const
        {
            return useReverseNormalizedPanAngle_;
        }
        void SetUseReverseNormalizedPanAngle( bool useReverseNormalizedPanAngle )
        {
            useReverseNormalizedPanAngle_ = useReverseNormalizedPanAngle;
        }
        double MinPanVelocity( ) const
        {
            return minPanVelocity_;
        }
        void SetMinPanVelocity( double minPanVelocity )
        {
            minPanVelocity_ = minPanVelocity;
        }
        double MaxPanVelocity( ) const
        {
            return maxPanVelocity_;
        }
        void SetMaxPanVelocity( double maxPanVelocity )
        {
            maxPanVelocity_ = maxPanVelocity;
        }
        double MinPanSpeed( ) const
        {
            return minPanSpeed_;
        }
        void SetMinPanSpeed( double minPanSpeed )
        {
            minPanSpeed_ = minPanSpeed;
        }
        double MaxPanSpeed( ) const
        {
            return maxPanSpeed_;
        }
        void SetMaxPanSpeed( double maxPanSpeed )
        {
            maxPanSpeed_ = maxPanSpeed;
        }
        Data::CameraFocalLengthMode FocalLengthMode( ) const
        {
            return focalLengthMode_;
        }
        void SetFocalLengthMode( Data::CameraFocalLengthMode focalLengthMode )
        {
            focalLengthMode_ = focalLengthMode;
        }
        double MinFocalLength( ) const
        {
            return minFocalLength_;
        }
        void SetMinFocalLength( double minFocalLength )
        {
            minFocalLength_ = minFocalLength;
        }
        double MaxFocalLength( ) const
        {
            return maxFocalLength_;
        }
        void SetMaxFocalLength( double maxFocalLength )
        {
            maxFocalLength_ = maxFocalLength;
        }
        double MinFocalLengthScale( ) const
        {
            return minFocalLengthScale_;
        }
        void SetMinFocalLengthScale( double minFocalLengthScale )
        {
            minFocalLengthScale_ = minFocalLengthScale;
        }
        double MaxFocalLengthScale( ) const
        {
            return maxFocalLengthScale_;
        }
        void SetMaxFocalLengthScale( double maxFocalLengthScale )
        {
            maxFocalLengthScale_ = maxFocalLengthScale;
        }
        double MinZoomVelocity( ) const
        {
            return minZoomVelocity_;
        }
        void SetMinZoomVelocity( double minZoomVelocity )
        {
            minZoomVelocity_ = minZoomVelocity;
        }
        double MaxZoomVelocity( ) const
        {
            return maxZoomVelocity_;
        }
        void SetMaxZoomVelocity( double maxZoomVelocity )
        {
            maxZoomVelocity_ = maxZoomVelocity;
        }
        double MinZoomSpeed( ) const
        {
            return minZoomSpeed_;
        }
        void SetMinZoomSpeed( double minZoomSpeed )
        {
            minZoomSpeed_ = minZoomSpeed;
        }
        double MaxZoomSpeed( ) const
        {
            return maxZoomSpeed_;
        }
        void SetMaxZoomSpeed( double maxZoomSpeed )
        {
            maxZoomSpeed_ = maxZoomSpeed;
        }
        double ImageSensorWidth( ) const
        {
            return imageSensorWidth_;
        }
        void SetImageSensorWidth( double imageSensorWidth )
        {
            imageSensorWidth_ = imageSensorWidth;
        }
        double ImageSensorHeight( ) const
        {
            return imageSensorHeight_;
        }
        void SetImageSensorHeight( double imageSensorHeight )
        {
            imageSensorHeight_ = imageSensorHeight;
        }
        double HomePanAngle( ) const
        {
            return homePanAngle_;
        }
        void SetHomePanAngle( double homePanAngle )
        {
            homePanAngle_ = homePanAngle;
        }
        double HomeTiltAngle( ) const
        {
            return homeTiltAngle_;
        }
        void SetHomeTiltAngle( double homeTiltAngle )
        {
            homeTiltAngle_ = homeTiltAngle;
        }
        double HomeFocalLength( ) const
        {
            return homeFocalLength_;
        }
        void SetHomeFocalLength( double homeFocalLength )
        {
            homeFocalLength_ = homeFocalLength;
        }
        double PanOffset( ) const
        {
            return panOffset_;
        }
        void SetPanOffset( double panOffset )
        {
            panOffset_ = panOffset;
        }
        double TiltOffset( ) const
        {
            return tiltOffset_;
        }
        void SetTiltOffset( double tiltOffset )
        {
            tiltOffset_ = tiltOffset;
        }
        double AimAltitude( ) const
        {
            return aimAltitude_;
        }
        void SetAimAltitude( double aimAltitude )
        {
            aimAltitude_ = aimAltitude;
        }
        double MinimumTargetWidth( ) const
        {
            return minimumTargetWidth_;
        }
        void SetMinimumTargetWidth( double minimumTargetWidth )
        {
            minimumTargetWidth_ = minimumTargetWidth;
        }
        TimeSpan TargetLockTimeout( ) const
        {
            return targetLockTimeout_;
        }
        void SetTargetLockTimeout( const TimeSpan& targetLockTimeout )
        {
            targetLockTimeout_ = targetLockTimeout;
        }
        TimeSpan UpdateStatusInterval( ) const
        {
            return updateStatusInterval_;
        }
        void SetUpdateStatusInterval( const TimeSpan& updateStatusInterval )
        {
            updateStatusInterval_ = updateStatusInterval;
        }
        TimeSpan ReadTimeout( ) const
        {
            return readTimeout_;
        }
        void SetReadTimeout( const TimeSpan& readTimeout )
        {
            readTimeout_ = readTimeout;
        }
        TimeSpan MoveCommandStatusDelay( ) const
        {
            return moveCommandStatusDelay_;
        }
        void SetMoveCommandStatusDelay( const TimeSpan& moveCommandStatusDelay )
        {
            moveCommandStatusDelay_ = moveCommandStatusDelay;
        }
        std::wstring_view PtzProfileName( ) const
        {
            if(ptzProfileNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(ptzProfileName_.data(),static_cast<size_t>( ptzProfileNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPtzProfileName( const WideString& ptzProfileName )
        {
            Assign(ptzProfileName, ptzProfileName_, ptzProfileNameLengthOrNullIndicator_);
        }
        std::wstring_view PtzConfigurationToken( ) const
        {
            if(ptzConfigurationTokenLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(ptzConfigurationToken_.data(),static_cast<size_t>( ptzConfigurationTokenLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPtzConfigurationToken( const WideString& ptzConfigurationToken )
        {
            Assign(ptzConfigurationToken, ptzConfigurationToken_, ptzConfigurationTokenLengthOrNullIndicator_);
        }
        std::wstring_view VideoSourceToken( ) const
        {
            if(videoSourceTokenLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(videoSourceToken_.data(),static_cast<size_t>( videoSourceTokenLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetVideoSourceToken( const WideString& videoSourceToken )
        {
            Assign(videoSourceToken, videoSourceToken_, videoSourceTokenLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CAMERA_FIELD_ID, &camera_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, CAMERACONTROLPROTOCOL_FIELD_ID, &cameraControlProtocol_);
            Bind(statement, CAMERAADDRESS_FIELD_ID, &cameraAddress_, &cameraAddressLengthOrNullIndicator_);
            Bind(statement, CAMERAPORT_FIELD_ID, &cameraPort_);
            Bind(statement, CAMERACONTROLADDRESS_FIELD_ID, &cameraControlAddress_, &cameraControlAddressLengthOrNullIndicator_);
            Bind(statement, CAMERACONTROLPORT_FIELD_ID, &cameraControlPort_);
            Bind(statement, CAMERAUSERNAME_FIELD_ID, &cameraUserName_, &cameraUserNameLengthOrNullIndicator_);
            Bind(statement, CAMERAPASSWORD_FIELD_ID, &cameraPassword_, &cameraPasswordLengthOrNullIndicator_);
            Bind(statement, USERTSPURIOVERRIDE_FIELD_ID, &useRtspUriOverride_);
            Bind(statement, RTSPURIOVERRIDE_FIELD_ID, &rtspUriOverride_, &rtspUriOverrideLengthOrNullIndicator_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, ALTITUDE_FIELD_ID, &altitude_);
            Bind(statement, USERELATIVEPOSITION_FIELD_ID, &useRelativePosition_);
            Bind(statement, AZIMUTHFROMGPS_FIELD_ID, &azimuthFromGPS_);
            Bind(statement, DISTANCEFROMGPS_FIELD_ID, &distanceFromGPS_);
            Bind(statement, PANTILTMODE_FIELD_ID, &panTiltMode_);
            Bind(statement, MINTILTANGLE_FIELD_ID, &minTiltAngle_);
            Bind(statement, MAXTILTANGLE_FIELD_ID, &maxTiltAngle_);
            Bind(statement, MINTILTSCALEANGLE_FIELD_ID, &minTiltScaleAngle_);
            Bind(statement, MAXTILTSCALEANGLE_FIELD_ID, &maxTiltScaleAngle_);
            Bind(statement, USEREVERSETILTANGLE_FIELD_ID, &useReverseTiltAngle_);
            Bind(statement, USEREVERSENORMALIZEDTILTANGLE_FIELD_ID, &useReverseNormalizedTiltAngle_);
            Bind(statement, MINTILTVELOCITY_FIELD_ID, &minTiltVelocity_);
            Bind(statement, MAXTILTVELOCITY_FIELD_ID, &maxTiltVelocity_);
            Bind(statement, MINTILTSPEED_FIELD_ID, &minTiltSpeed_);
            Bind(statement, MAXTILTSPEED_FIELD_ID, &maxTiltSpeed_);
            Bind(statement, MINPANANGLE_FIELD_ID, &minPanAngle_);
            Bind(statement, MAXPANANGLE_FIELD_ID, &maxPanAngle_);
            Bind(statement, MINPANSCALEANGLE_FIELD_ID, &minPanScaleAngle_);
            Bind(statement, MAXPANSCALEANGLE_FIELD_ID, &maxPanScaleAngle_);
            Bind(statement, USEREVERSEPANANGLE_FIELD_ID, &useReversePanAngle_);
            Bind(statement, USEREVERSENORMALIZEDPANANGLE_FIELD_ID, &useReverseNormalizedPanAngle_);
            Bind(statement, MINPANVELOCITY_FIELD_ID, &minPanVelocity_);
            Bind(statement, MAXPANVELOCITY_FIELD_ID, &maxPanVelocity_);
            Bind(statement, MINPANSPEED_FIELD_ID, &minPanSpeed_);
            Bind(statement, MAXPANSPEED_FIELD_ID, &maxPanSpeed_);
            Bind(statement, FOCALLENGTHMODE_FIELD_ID, &focalLengthMode_);
            Bind(statement, MINFOCALLENGTH_FIELD_ID, &minFocalLength_);
            Bind(statement, MAXFOCALLENGTH_FIELD_ID, &maxFocalLength_);
            Bind(statement, MINFOCALLENGTHSCALE_FIELD_ID, &minFocalLengthScale_);
            Bind(statement, MAXFOCALLENGTHSCALE_FIELD_ID, &maxFocalLengthScale_);
            Bind(statement, MINZOOMVELOCITY_FIELD_ID, &minZoomVelocity_);
            Bind(statement, MAXZOOMVELOCITY_FIELD_ID, &maxZoomVelocity_);
            Bind(statement, MINZOOMSPEED_FIELD_ID, &minZoomSpeed_);
            Bind(statement, MAXZOOMSPEED_FIELD_ID, &maxZoomSpeed_);
            Bind(statement, IMAGESENSORWIDTH_FIELD_ID, &imageSensorWidth_);
            Bind(statement, IMAGESENSORHEIGHT_FIELD_ID, &imageSensorHeight_);
            Bind(statement, HOMEPANANGLE_FIELD_ID, &homePanAngle_);
            Bind(statement, HOMETILTANGLE_FIELD_ID, &homeTiltAngle_);
            Bind(statement, HOMEFOCALLENGTH_FIELD_ID, &homeFocalLength_);
            Bind(statement, PANOFFSET_FIELD_ID, &panOffset_);
            Bind(statement, TILTOFFSET_FIELD_ID, &tiltOffset_);
            Bind(statement, AIMALTITUDE_FIELD_ID, &aimAltitude_);
            Bind(statement, MINIMUMTARGETWIDTH_FIELD_ID, &minimumTargetWidth_);
            Bind(statement, TARGETLOCKTIMEOUT_FIELD_ID, &targetLockTimeout_);
            Bind(statement, UPDATESTATUSINTERVAL_FIELD_ID, &updateStatusInterval_);
            Bind(statement, READTIMEOUT_FIELD_ID, &readTimeout_);
            Bind(statement, MOVECOMMANDSTATUSDELAY_FIELD_ID, &moveCommandStatusDelay_);
            Bind(statement, PTZPROFILENAME_FIELD_ID, &ptzProfileName_, &ptzProfileNameLengthOrNullIndicator_);
            Bind(statement, PTZCONFIGURATIONTOKEN_FIELD_ID, &ptzConfigurationToken_, &ptzConfigurationTokenLengthOrNullIndicator_);
            Bind(statement, VIDEOSOURCETOKEN_FIELD_ID, &videoSourceToken_, &videoSourceTokenLengthOrNullIndicator_);
        }

    };

    class CameraPanCalibrationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp]";
        static constexpr std::wstring_view ViewName = L"CameraPanCalibrationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CAMERA_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;

        CameraPanCalibrationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraPanCalibration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Camera( ) const
        {
            return camera_;
        }
        void SetCamera( const Guid& camera )
        {
            camera_ = camera;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CAMERA_FIELD_ID, &camera_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
        }

    };

    class CameraPanCalibrationValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid panCalibration_;
        double panAngle_ = 0.0;
        double panOffset_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[PanCalibration],[PanAngle],[PanOffset]";
        static constexpr std::wstring_view ViewName = L"CameraPanCalibrationValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT PANCALIBRATION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT PANANGLE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT PANOFFSET_FIELD_ID = 5;

        CameraPanCalibrationValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraPanCalibrationValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid PanCalibration( ) const
        {
            return panCalibration_;
        }
        void SetPanCalibration( const Guid& panCalibration )
        {
            panCalibration_ = panCalibration;
        }
        double PanAngle( ) const
        {
            return panAngle_;
        }
        void SetPanAngle( double panAngle )
        {
            panAngle_ = panAngle;
        }
        double PanOffset( ) const
        {
            return panOffset_;
        }
        void SetPanOffset( double panOffset )
        {
            panOffset_ = panOffset;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, PANCALIBRATION_FIELD_ID, &panCalibration_);
            Bind(statement, PANANGLE_FIELD_ID, &panAngle_);
            Bind(statement, PANOFFSET_FIELD_ID, &panOffset_);
        }

    };

    class CameraStatusColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid camera_;
        Guid track_;
        DateTime timestamp_;
        Data::CameraPanTiltMode positionPanTiltMode_ = Data::CameraPanTiltMode::Unknown;
        double panAngle_ = 0.0;
        double tiltAngle_ = 0.0;
        Data::CameraFocalLengthMode positionFocalLengthMode_ = Data::CameraFocalLengthMode::Unknown;
        double focalLength_ = 0.0;
        Data::CameraMoveStatus panTiltMoveStatus_ = Data::CameraMoveStatus::Unknown;
        Data::CameraMoveStatus zoomMoveStatus_ = Data::CameraMoveStatus::Unknown;
        Data::CameraPanTiltMode velocityPanTiltMode_ = Data::CameraPanTiltMode::Unknown;
        double panVelocity_ = 0.0;
        SQLLEN panVelocityNullIndicator_ = SQL_NULL_DATA;
        double tiltVelocity_ = 0.0;
        SQLLEN tiltVelocityNullIndicator_ = SQL_NULL_DATA;
        Data::CameraFocalLengthMode velocityFocalLengthMode_ = Data::CameraFocalLengthMode::Unknown;
        double zoomVelocity_ = 0.0;
        SQLLEN zoomVelocityNullIndicator_ = SQL_NULL_DATA;
        Data::CameraFeatures activeFeatures_ = Data::CameraFeatures::None;
        WideString error_;
        SQLLEN errorLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Track],[Timestamp],[PositionPanTiltMode],[PanAngle],[TiltAngle],[PositionFocalLengthMode],[FocalLength],[PanTiltMoveStatus],[ZoomMoveStatus],[VelocityPanTiltMode],[PanVelocity],[TiltVelocity],[VelocityFocalLengthMode],[ZoomVelocity],[ActiveFeatures],[Error]";
        static constexpr std::wstring_view ViewName = L"CameraStatusView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CAMERA_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TRACK_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 5;
        static constexpr SQLUSMALLINT POSITIONPANTILTMODE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT PANANGLE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT TILTANGLE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT POSITIONFOCALLENGTHMODE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT FOCALLENGTH_FIELD_ID = 10;
        static constexpr SQLUSMALLINT PANTILTMOVESTATUS_FIELD_ID = 11;
        static constexpr SQLUSMALLINT ZOOMMOVESTATUS_FIELD_ID = 12;
        static constexpr SQLUSMALLINT VELOCITYPANTILTMODE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT PANVELOCITY_FIELD_ID = 14;
        static constexpr SQLUSMALLINT TILTVELOCITY_FIELD_ID = 15;
        static constexpr SQLUSMALLINT VELOCITYFOCALLENGTHMODE_FIELD_ID = 16;
        static constexpr SQLUSMALLINT ZOOMVELOCITY_FIELD_ID = 17;
        static constexpr SQLUSMALLINT ACTIVEFEATURES_FIELD_ID = 18;
        static constexpr SQLUSMALLINT ERROR_FIELD_ID = 19;

        CameraStatusColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraStatus;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Camera( ) const
        {
            return camera_;
        }
        void SetCamera( const Guid& camera )
        {
            camera_ = camera;
        }
        Guid Track( ) const
        {
            return track_;
        }
        void SetTrack( const Guid& track )
        {
            track_ = track;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::CameraPanTiltMode PositionPanTiltMode( ) const
        {
            return positionPanTiltMode_;
        }
        void SetPositionPanTiltMode( Data::CameraPanTiltMode positionPanTiltMode )
        {
            positionPanTiltMode_ = positionPanTiltMode;
        }
        double PanAngle( ) const
        {
            return panAngle_;
        }
        void SetPanAngle( double panAngle )
        {
            panAngle_ = panAngle;
        }
        double TiltAngle( ) const
        {
            return tiltAngle_;
        }
        void SetTiltAngle( double tiltAngle )
        {
            tiltAngle_ = tiltAngle;
        }
        Data::CameraFocalLengthMode PositionFocalLengthMode( ) const
        {
            return positionFocalLengthMode_;
        }
        void SetPositionFocalLengthMode( Data::CameraFocalLengthMode positionFocalLengthMode )
        {
            positionFocalLengthMode_ = positionFocalLengthMode;
        }
        double FocalLength( ) const
        {
            return focalLength_;
        }
        void SetFocalLength( double focalLength )
        {
            focalLength_ = focalLength;
        }
        Data::CameraMoveStatus PanTiltMoveStatus( ) const
        {
            return panTiltMoveStatus_;
        }
        void SetPanTiltMoveStatus( Data::CameraMoveStatus panTiltMoveStatus )
        {
            panTiltMoveStatus_ = panTiltMoveStatus;
        }
        Data::CameraMoveStatus ZoomMoveStatus( ) const
        {
            return zoomMoveStatus_;
        }
        void SetZoomMoveStatus( Data::CameraMoveStatus zoomMoveStatus )
        {
            zoomMoveStatus_ = zoomMoveStatus;
        }
        Data::CameraPanTiltMode VelocityPanTiltMode( ) const
        {
            return velocityPanTiltMode_;
        }
        void SetVelocityPanTiltMode( Data::CameraPanTiltMode velocityPanTiltMode )
        {
            velocityPanTiltMode_ = velocityPanTiltMode;
        }
        double PanVelocity( ) const
        {
            return panVelocity_;
        }
        void SetPanVelocity( double panVelocity )
        {
            panVelocity_ = panVelocity;
        }
        double TiltVelocity( ) const
        {
            return tiltVelocity_;
        }
        void SetTiltVelocity( double tiltVelocity )
        {
            tiltVelocity_ = tiltVelocity;
        }
        Data::CameraFocalLengthMode VelocityFocalLengthMode( ) const
        {
            return velocityFocalLengthMode_;
        }
        void SetVelocityFocalLengthMode( Data::CameraFocalLengthMode velocityFocalLengthMode )
        {
            velocityFocalLengthMode_ = velocityFocalLengthMode;
        }
        double ZoomVelocity( ) const
        {
            return zoomVelocity_;
        }
        void SetZoomVelocity( double zoomVelocity )
        {
            zoomVelocity_ = zoomVelocity;
        }
        Data::CameraFeatures ActiveFeatures( ) const
        {
            return activeFeatures_;
        }
        void SetActiveFeatures( Data::CameraFeatures activeFeatures )
        {
            activeFeatures_ = activeFeatures;
        }
        const WideString& Error( ) const
        {
            return error_;
        }
        void SetError( const WideString& error )
        {
            Assign(error, error_, errorLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CAMERA_FIELD_ID, &camera_);
            Bind(statement, TRACK_FIELD_ID, &track_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, POSITIONPANTILTMODE_FIELD_ID, &positionPanTiltMode_);
            Bind(statement, PANANGLE_FIELD_ID, &panAngle_);
            Bind(statement, TILTANGLE_FIELD_ID, &tiltAngle_);
            Bind(statement, POSITIONFOCALLENGTHMODE_FIELD_ID, &positionFocalLengthMode_);
            Bind(statement, FOCALLENGTH_FIELD_ID, &focalLength_);
            Bind(statement, PANTILTMOVESTATUS_FIELD_ID, &panTiltMoveStatus_);
            Bind(statement, ZOOMMOVESTATUS_FIELD_ID, &zoomMoveStatus_);
            Bind(statement, VELOCITYPANTILTMODE_FIELD_ID, &velocityPanTiltMode_);
            Bind(statement, PANVELOCITY_FIELD_ID, &panVelocity_, &panVelocityNullIndicator_);
            Bind(statement, TILTVELOCITY_FIELD_ID, &tiltVelocity_, &tiltVelocityNullIndicator_);
            Bind(statement, VELOCITYFOCALLENGTHMODE_FIELD_ID, &velocityFocalLengthMode_);
            Bind(statement, ZOOMVELOCITY_FIELD_ID, &zoomVelocity_, &zoomVelocityNullIndicator_);
            Bind(statement, ACTIVEFEATURES_FIELD_ID, &activeFeatures_);
        }

    };

    class CameraTiltCalibrationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp]";
        static constexpr std::wstring_view ViewName = L"CameraTiltCalibrationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CAMERA_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;

        CameraTiltCalibrationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraTiltCalibration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Camera( ) const
        {
            return camera_;
        }
        void SetCamera( const Guid& camera )
        {
            camera_ = camera;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CAMERA_FIELD_ID, &camera_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
        }

    };

    class CameraTiltCalibrationValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid tiltCalibration_;
        double panAngle_ = 0.0;
        double tiltOffset_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[TiltCalibration],[PanAngle],[TiltOffset]";
        static constexpr std::wstring_view ViewName = L"CameraTiltCalibrationValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TILTCALIBRATION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT PANANGLE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TILTOFFSET_FIELD_ID = 5;

        CameraTiltCalibrationValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraTiltCalibrationValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid TiltCalibration( ) const
        {
            return tiltCalibration_;
        }
        void SetTiltCalibration( const Guid& tiltCalibration )
        {
            tiltCalibration_ = tiltCalibration;
        }
        double PanAngle( ) const
        {
            return panAngle_;
        }
        void SetPanAngle( double panAngle )
        {
            panAngle_ = panAngle;
        }
        double TiltOffset( ) const
        {
            return tiltOffset_;
        }
        void SetTiltOffset( double tiltOffset )
        {
            tiltOffset_ = tiltOffset;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TILTCALIBRATION_FIELD_ID, &tiltCalibration_);
            Bind(statement, PANANGLE_FIELD_ID, &panAngle_);
            Bind(statement, TILTOFFSET_FIELD_ID, &tiltOffset_);
        }

    };

    class CameraZoomCalibrationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Camera],[Timestamp]";
        static constexpr std::wstring_view ViewName = L"CameraZoomCalibrationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CAMERA_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;

        CameraZoomCalibrationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraZoomCalibration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Camera( ) const
        {
            return camera_;
        }
        void SetCamera( const Guid& camera )
        {
            camera_ = camera;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CAMERA_FIELD_ID, &camera_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
        }

    };

    class CameraZoomCalibrationValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid zoomCalibration_;
        double focalLength_ = 0.0;
        double focalLengthOffset_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ZoomCalibration],[FocalLength],[FocalLengthOffset]";
        static constexpr std::wstring_view ViewName = L"CameraZoomCalibrationValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ZOOMCALIBRATION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT FOCALLENGTH_FIELD_ID = 4;
        static constexpr SQLUSMALLINT FOCALLENGTHOFFSET_FIELD_ID = 5;

        CameraZoomCalibrationValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraZoomCalibrationValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid ZoomCalibration( ) const
        {
            return zoomCalibration_;
        }
        void SetZoomCalibration( const Guid& zoomCalibration )
        {
            zoomCalibration_ = zoomCalibration;
        }
        double FocalLength( ) const
        {
            return focalLength_;
        }
        void SetFocalLength( double focalLength )
        {
            focalLength_ = focalLength;
        }
        double FocalLengthOffset( ) const
        {
            return focalLengthOffset_;
        }
        void SetFocalLengthOffset( double focalLengthOffset )
        {
            focalLengthOffset_ = focalLengthOffset;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ZOOMCALIBRATION_FIELD_ID, &zoomCalibration_);
            Bind(statement, FOCALLENGTH_FIELD_ID, &focalLength_);
            Bind(statement, FOCALLENGTHOFFSET_FIELD_ID, &focalLengthOffset_);
        }

    };

    class CatalogElementColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid catalog_;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name]";
        static constexpr std::wstring_view ViewName = L"CatalogElementView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CATALOG_FIELD_ID = 3;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 4;

        CatalogElementColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CatalogElement;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Catalog( ) const
        {
            return catalog_;
        }
        void SetCatalog( const Guid& catalog )
        {
            catalog_ = catalog;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CATALOG_FIELD_ID, &catalog_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class CatalogColumnData : public CatalogElementColumnData
    {
    public:
        using Base = CatalogElementColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name]";
        static constexpr std::wstring_view ViewName = L"CatalogView";

        CatalogColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Catalog;
        }

    };

    class ElementColumnData : public CatalogElementColumnData
    {
        Guid elementType_;
    public:
        using Base = CatalogElementColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[ElementType]";
        static constexpr std::wstring_view ViewName = L"ElementView";

        static constexpr SQLUSMALLINT ELEMENTTYPE_FIELD_ID = 5;

        ElementColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Element;
        }

        Guid ElementType( ) const
        {
            return elementType_;
        }
        void SetElementType( const Guid& elementType )
        {
            elementType_ = elementType;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, ELEMENTTYPE_FIELD_ID, &elementType_);
        }

    };

    class CollectionInfoColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Int64 count_ = 0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Count]";
        static constexpr std::wstring_view ViewName = L"CollectionInfoView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT COUNT_FIELD_ID = 3;

        CollectionInfoColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CollectionInfo;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Int64 Count( ) const
        {
            return count_;
        }
        void SetCount( Int64 count )
        {
            count_ = count;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, COUNT_FIELD_ID, &count_);
        }

    };

    class CountryColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 code_ = 0;
        std::array<wchar_t,3> alpha2_ = {};
        SQLLEN alpha2LengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,4> alpha3_ = {};
        SQLLEN alpha3LengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Code],[Alpha2],[Alpha3]";
        static constexpr std::wstring_view ViewName = L"CountryView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT CODE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT ALPHA2_FIELD_ID = 5;
        static constexpr SQLUSMALLINT ALPHA3_FIELD_ID = 6;

        CountryColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Country;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Int32 Code( ) const
        {
            return code_;
        }
        void SetCode( Int32 code )
        {
            code_ = code;
        }
        std::wstring_view Alpha2( ) const
        {
            if(alpha2LengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(alpha2_.data(),static_cast<size_t>( alpha2LengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetAlpha2( const WideString& alpha2 )
        {
            Assign(alpha2, alpha2_, alpha2LengthOrNullIndicator_);
        }
        std::wstring_view Alpha3( ) const
        {
            if(alpha3LengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(alpha3_.data(),static_cast<size_t>( alpha3LengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetAlpha3( const WideString& alpha3 )
        {
            Assign(alpha3, alpha3_, alpha3LengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, CODE_FIELD_ID, &code_);
            Bind(statement, ALPHA2_FIELD_ID, &alpha2_, &alpha2LengthOrNullIndicator_);
            Bind(statement, ALPHA3_FIELD_ID, &alpha3_, &alpha3LengthOrNullIndicator_);
        }

    };

    class CursorInfoColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Int32 typeCode_ = 0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[TypeCode]";
        static constexpr std::wstring_view ViewName = L"CursorInfoView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TYPECODE_FIELD_ID = 3;

        CursorInfoColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CursorInfo;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Int32 TypeCode( ) const
        {
            return typeCode_;
        }
        void SetTypeCode( Int32 typeCode )
        {
            typeCode_ = typeCode;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TYPECODE_FIELD_ID, &typeCode_);
        }

    };

    class DateTimeTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        DateTime value_;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"DateTimeTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        DateTimeTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DateTimeTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        DateTime Value( ) const
        {
            return value_;
        }
        void SetValue( const DateTime& value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class DeviceHostColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name]";
        static constexpr std::wstring_view ViewName = L"DeviceHostView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;

        DeviceHostColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DeviceHost;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class DeviceHostConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid host_;
        DateTime timestamp_;
        std::array<wchar_t,128> hostname_ = {};
        SQLLEN hostnameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 port_ = 0;
        std::array<wchar_t,101> queueName_ = {};
        SQLLEN queueNameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Timestamp],[Hostname],[Port],[QueueName]";
        static constexpr std::wstring_view ViewName = L"DeviceHostConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT HOST_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT HOSTNAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT PORT_FIELD_ID = 6;
        static constexpr SQLUSMALLINT QUEUENAME_FIELD_ID = 7;

        DeviceHostConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DeviceHostConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Host( ) const
        {
            return host_;
        }
        void SetHost( const Guid& host )
        {
            host_ = host;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        std::wstring_view Hostname( ) const
        {
            if(hostnameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(hostname_.data(),static_cast<size_t>( hostnameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetHostname( const WideString& hostname )
        {
            Assign(hostname, hostname_, hostnameLengthOrNullIndicator_);
        }
        Int32 Port( ) const
        {
            return port_;
        }
        void SetPort( Int32 port )
        {
            port_ = port;
        }
        std::wstring_view QueueName( ) const
        {
            if(queueNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(queueName_.data(),static_cast<size_t>( queueNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetQueueName( const WideString& queueName )
        {
            Assign(queueName, queueName_, queueNameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, HOST_FIELD_ID, &host_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, HOSTNAME_FIELD_ID, &hostname_, &hostnameLengthOrNullIndicator_);
            Bind(statement, PORT_FIELD_ID, &port_);
            Bind(statement, QUEUENAME_FIELD_ID, &queueName_, &queueNameLengthOrNullIndicator_);
        }

    };

    class DeviceTypeColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,101> assemblyName_ = {};
        SQLLEN assemblyNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,101> className_ = {};
        SQLLEN classNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,101> proxyAssemblyName_ = {};
        SQLLEN proxyAssemblyNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,101> proxyClassName_ = {};
        SQLLEN proxyClassNameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName]";
        static constexpr std::wstring_view ViewName = L"DeviceTypeView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ASSEMBLYNAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT CLASSNAME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT PROXYASSEMBLYNAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT PROXYCLASSNAME_FIELD_ID = 6;

        DeviceTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DeviceType;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view AssemblyName( ) const
        {
            if(assemblyNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(assemblyName_.data(),static_cast<size_t>( assemblyNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetAssemblyName( const WideString& assemblyName )
        {
            Assign(assemblyName, assemblyName_, assemblyNameLengthOrNullIndicator_);
        }
        std::wstring_view ClassName( ) const
        {
            if(classNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(className_.data(),static_cast<size_t>( classNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetClassName( const WideString& className )
        {
            Assign(className, className_, classNameLengthOrNullIndicator_);
        }
        std::wstring_view ProxyAssemblyName( ) const
        {
            if(proxyAssemblyNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(proxyAssemblyName_.data(),static_cast<size_t>( proxyAssemblyNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetProxyAssemblyName( const WideString& proxyAssemblyName )
        {
            Assign(proxyAssemblyName, proxyAssemblyName_, proxyAssemblyNameLengthOrNullIndicator_);
        }
        std::wstring_view ProxyClassName( ) const
        {
            if(proxyClassNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(proxyClassName_.data(),static_cast<size_t>( proxyClassNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetProxyClassName( const WideString& proxyClassName )
        {
            Assign(proxyClassName, proxyClassName_, proxyClassNameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ASSEMBLYNAME_FIELD_ID, &assemblyName_, &assemblyNameLengthOrNullIndicator_);
            Bind(statement, CLASSNAME_FIELD_ID, &className_, &classNameLengthOrNullIndicator_);
            Bind(statement, PROXYASSEMBLYNAME_FIELD_ID, &proxyAssemblyName_, &proxyAssemblyNameLengthOrNullIndicator_);
            Bind(statement, PROXYCLASSNAME_FIELD_ID, &proxyClassName_, &proxyClassNameLengthOrNullIndicator_);
        }

    };

    class AisTransceiverTypeColumnData : public DeviceTypeColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = DeviceTypeColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName],[Name]";
        static constexpr std::wstring_view ViewName = L"AisTransceiverTypeView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;

        AisTransceiverTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisTransceiverType;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class CameraTypeColumnData : public DeviceTypeColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Data::CameraFeatures cameraFeatures_ = Data::CameraFeatures::None;
    public:
        using Base = DeviceTypeColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName],[Name],[CameraFeatures]";
        static constexpr std::wstring_view ViewName = L"CameraTypeView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;
        static constexpr SQLUSMALLINT CAMERAFEATURES_FIELD_ID = 8;

        CameraTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CameraType;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Data::CameraFeatures CameraFeatures( ) const
        {
            return cameraFeatures_;
        }
        void SetCameraFeatures( Data::CameraFeatures cameraFeatures )
        {
            cameraFeatures_ = cameraFeatures;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, CAMERAFEATURES_FIELD_ID, &cameraFeatures_);
        }

    };

    class GNSSDeviceTypeColumnData : public DeviceTypeColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = DeviceTypeColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName],[Name]";
        static constexpr std::wstring_view ViewName = L"GNSSDeviceTypeView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;

        GNSSDeviceTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GNSSDeviceType;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class GyroDeviceTypeColumnData : public DeviceTypeColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = DeviceTypeColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName],[Name]";
        static constexpr std::wstring_view ViewName = L"GyroDeviceTypeView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;

        GyroDeviceTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroDeviceType;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class LineInputDeviceTypeColumnData : public DeviceTypeColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = DeviceTypeColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName],[Name]";
        static constexpr std::wstring_view ViewName = L"LineInputDeviceTypeView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;

        LineInputDeviceTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LineInputDeviceType;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class OilspillDetectorTypeColumnData : public DeviceTypeColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = DeviceTypeColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName],[Name]";
        static constexpr std::wstring_view ViewName = L"OilspillDetectorTypeView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;

        OilspillDetectorTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::OilspillDetectorType;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class RadarTypeColumnData : public DeviceTypeColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 pulseShortMinusValue_ = 0;
        SQLLEN pulseShortMinusValueNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,51> pulseShortMinusDisplayText_ = {};
        SQLLEN pulseShortMinusDisplayTextLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 pulseShortValue_ = 0;
        SQLLEN pulseShortValueNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,51> pulseShortDisplayText_ = {};
        SQLLEN pulseShortDisplayTextLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 pulseShortPlusValue_ = 0;
        SQLLEN pulseShortPlusValueNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,51> pulseShortPlusDisplayText_ = {};
        SQLLEN pulseShortPlusDisplayTextLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 pulseMediumMinusValue_ = 0;
        SQLLEN pulseMediumMinusValueNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,51> pulseMediumMinusDisplayText_ = {};
        SQLLEN pulseMediumMinusDisplayTextLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 pulseMediumValue_ = 0;
        SQLLEN pulseMediumValueNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,51> pulseMediumDisplayText_ = {};
        SQLLEN pulseMediumDisplayTextLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 pulseMediumPlusValue_ = 0;
        SQLLEN pulseMediumPlusValueNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,51> pulseMediumPlusDisplayText_ = {};
        SQLLEN pulseMediumPlusDisplayTextLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 pulseLongMinusValue_ = 0;
        SQLLEN pulseLongMinusValueNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,51> pulseLongMinusDisplayText_ = {};
        SQLLEN pulseLongMinusDisplayTextLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 pulseLongValue_ = 0;
        SQLLEN pulseLongValueNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,51> pulseLongDisplayText_ = {};
        SQLLEN pulseLongDisplayTextLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 pulseLongPlusValue_ = 0;
        SQLLEN pulseLongPlusValueNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,51> pulseLongPlusDisplayText_ = {};
        SQLLEN pulseLongPlusDisplayTextLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = DeviceTypeColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName],[Name],[PulseShortMinusValue],[PulseShortMinusDisplayText],[PulseShortValue],[PulseShortDisplayText],[PulseShortPlusValue],[PulseShortPlusDisplayText],[PulseMediumMinusValue],[PulseMediumMinusDisplayText],[PulseMediumValue],[PulseMediumDisplayText],[PulseMediumPlusValue],[PulseMediumPlusDisplayText],[PulseLongMinusValue],[PulseLongMinusDisplayText],[PulseLongValue],[PulseLongDisplayText],[PulseLongPlusValue],[PulseLongPlusDisplayText]";
        static constexpr std::wstring_view ViewName = L"RadarTypeView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;
        static constexpr SQLUSMALLINT PULSESHORTMINUSVALUE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT PULSESHORTMINUSDISPLAYTEXT_FIELD_ID = 9;
        static constexpr SQLUSMALLINT PULSESHORTVALUE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT PULSESHORTDISPLAYTEXT_FIELD_ID = 11;
        static constexpr SQLUSMALLINT PULSESHORTPLUSVALUE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT PULSESHORTPLUSDISPLAYTEXT_FIELD_ID = 13;
        static constexpr SQLUSMALLINT PULSEMEDIUMMINUSVALUE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT PULSEMEDIUMMINUSDISPLAYTEXT_FIELD_ID = 15;
        static constexpr SQLUSMALLINT PULSEMEDIUMVALUE_FIELD_ID = 16;
        static constexpr SQLUSMALLINT PULSEMEDIUMDISPLAYTEXT_FIELD_ID = 17;
        static constexpr SQLUSMALLINT PULSEMEDIUMPLUSVALUE_FIELD_ID = 18;
        static constexpr SQLUSMALLINT PULSEMEDIUMPLUSDISPLAYTEXT_FIELD_ID = 19;
        static constexpr SQLUSMALLINT PULSELONGMINUSVALUE_FIELD_ID = 20;
        static constexpr SQLUSMALLINT PULSELONGMINUSDISPLAYTEXT_FIELD_ID = 21;
        static constexpr SQLUSMALLINT PULSELONGVALUE_FIELD_ID = 22;
        static constexpr SQLUSMALLINT PULSELONGDISPLAYTEXT_FIELD_ID = 23;
        static constexpr SQLUSMALLINT PULSELONGPLUSVALUE_FIELD_ID = 24;
        static constexpr SQLUSMALLINT PULSELONGPLUSDISPLAYTEXT_FIELD_ID = 25;

        RadarTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarType;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Int32 PulseShortMinusValue( ) const
        {
            return pulseShortMinusValue_;
        }
        void SetPulseShortMinusValue( Int32 pulseShortMinusValue )
        {
            pulseShortMinusValue_ = pulseShortMinusValue;
        }
        std::wstring_view PulseShortMinusDisplayText( ) const
        {
            if(pulseShortMinusDisplayTextLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pulseShortMinusDisplayText_.data(),static_cast<size_t>( pulseShortMinusDisplayTextLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPulseShortMinusDisplayText( const WideString& pulseShortMinusDisplayText )
        {
            Assign(pulseShortMinusDisplayText, pulseShortMinusDisplayText_, pulseShortMinusDisplayTextLengthOrNullIndicator_);
        }
        Int32 PulseShortValue( ) const
        {
            return pulseShortValue_;
        }
        void SetPulseShortValue( Int32 pulseShortValue )
        {
            pulseShortValue_ = pulseShortValue;
        }
        std::wstring_view PulseShortDisplayText( ) const
        {
            if(pulseShortDisplayTextLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pulseShortDisplayText_.data(),static_cast<size_t>( pulseShortDisplayTextLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPulseShortDisplayText( const WideString& pulseShortDisplayText )
        {
            Assign(pulseShortDisplayText, pulseShortDisplayText_, pulseShortDisplayTextLengthOrNullIndicator_);
        }
        Int32 PulseShortPlusValue( ) const
        {
            return pulseShortPlusValue_;
        }
        void SetPulseShortPlusValue( Int32 pulseShortPlusValue )
        {
            pulseShortPlusValue_ = pulseShortPlusValue;
        }
        std::wstring_view PulseShortPlusDisplayText( ) const
        {
            if(pulseShortPlusDisplayTextLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pulseShortPlusDisplayText_.data(),static_cast<size_t>( pulseShortPlusDisplayTextLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPulseShortPlusDisplayText( const WideString& pulseShortPlusDisplayText )
        {
            Assign(pulseShortPlusDisplayText, pulseShortPlusDisplayText_, pulseShortPlusDisplayTextLengthOrNullIndicator_);
        }
        Int32 PulseMediumMinusValue( ) const
        {
            return pulseMediumMinusValue_;
        }
        void SetPulseMediumMinusValue( Int32 pulseMediumMinusValue )
        {
            pulseMediumMinusValue_ = pulseMediumMinusValue;
        }
        std::wstring_view PulseMediumMinusDisplayText( ) const
        {
            if(pulseMediumMinusDisplayTextLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pulseMediumMinusDisplayText_.data(),static_cast<size_t>( pulseMediumMinusDisplayTextLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPulseMediumMinusDisplayText( const WideString& pulseMediumMinusDisplayText )
        {
            Assign(pulseMediumMinusDisplayText, pulseMediumMinusDisplayText_, pulseMediumMinusDisplayTextLengthOrNullIndicator_);
        }
        Int32 PulseMediumValue( ) const
        {
            return pulseMediumValue_;
        }
        void SetPulseMediumValue( Int32 pulseMediumValue )
        {
            pulseMediumValue_ = pulseMediumValue;
        }
        std::wstring_view PulseMediumDisplayText( ) const
        {
            if(pulseMediumDisplayTextLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pulseMediumDisplayText_.data(),static_cast<size_t>( pulseMediumDisplayTextLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPulseMediumDisplayText( const WideString& pulseMediumDisplayText )
        {
            Assign(pulseMediumDisplayText, pulseMediumDisplayText_, pulseMediumDisplayTextLengthOrNullIndicator_);
        }
        Int32 PulseMediumPlusValue( ) const
        {
            return pulseMediumPlusValue_;
        }
        void SetPulseMediumPlusValue( Int32 pulseMediumPlusValue )
        {
            pulseMediumPlusValue_ = pulseMediumPlusValue;
        }
        std::wstring_view PulseMediumPlusDisplayText( ) const
        {
            if(pulseMediumPlusDisplayTextLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pulseMediumPlusDisplayText_.data(),static_cast<size_t>( pulseMediumPlusDisplayTextLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPulseMediumPlusDisplayText( const WideString& pulseMediumPlusDisplayText )
        {
            Assign(pulseMediumPlusDisplayText, pulseMediumPlusDisplayText_, pulseMediumPlusDisplayTextLengthOrNullIndicator_);
        }
        Int32 PulseLongMinusValue( ) const
        {
            return pulseLongMinusValue_;
        }
        void SetPulseLongMinusValue( Int32 pulseLongMinusValue )
        {
            pulseLongMinusValue_ = pulseLongMinusValue;
        }
        std::wstring_view PulseLongMinusDisplayText( ) const
        {
            if(pulseLongMinusDisplayTextLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pulseLongMinusDisplayText_.data(),static_cast<size_t>( pulseLongMinusDisplayTextLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPulseLongMinusDisplayText( const WideString& pulseLongMinusDisplayText )
        {
            Assign(pulseLongMinusDisplayText, pulseLongMinusDisplayText_, pulseLongMinusDisplayTextLengthOrNullIndicator_);
        }
        Int32 PulseLongValue( ) const
        {
            return pulseLongValue_;
        }
        void SetPulseLongValue( Int32 pulseLongValue )
        {
            pulseLongValue_ = pulseLongValue;
        }
        std::wstring_view PulseLongDisplayText( ) const
        {
            if(pulseLongDisplayTextLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pulseLongDisplayText_.data(),static_cast<size_t>( pulseLongDisplayTextLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPulseLongDisplayText( const WideString& pulseLongDisplayText )
        {
            Assign(pulseLongDisplayText, pulseLongDisplayText_, pulseLongDisplayTextLengthOrNullIndicator_);
        }
        Int32 PulseLongPlusValue( ) const
        {
            return pulseLongPlusValue_;
        }
        void SetPulseLongPlusValue( Int32 pulseLongPlusValue )
        {
            pulseLongPlusValue_ = pulseLongPlusValue;
        }
        std::wstring_view PulseLongPlusDisplayText( ) const
        {
            if(pulseLongPlusDisplayTextLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pulseLongPlusDisplayText_.data(),static_cast<size_t>( pulseLongPlusDisplayTextLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPulseLongPlusDisplayText( const WideString& pulseLongPlusDisplayText )
        {
            Assign(pulseLongPlusDisplayText, pulseLongPlusDisplayText_, pulseLongPlusDisplayTextLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, PULSESHORTMINUSVALUE_FIELD_ID, &pulseShortMinusValue_, &pulseShortMinusValueNullIndicator_);
            Bind(statement, PULSESHORTMINUSDISPLAYTEXT_FIELD_ID, &pulseShortMinusDisplayText_, &pulseShortMinusDisplayTextLengthOrNullIndicator_);
            Bind(statement, PULSESHORTVALUE_FIELD_ID, &pulseShortValue_, &pulseShortValueNullIndicator_);
            Bind(statement, PULSESHORTDISPLAYTEXT_FIELD_ID, &pulseShortDisplayText_, &pulseShortDisplayTextLengthOrNullIndicator_);
            Bind(statement, PULSESHORTPLUSVALUE_FIELD_ID, &pulseShortPlusValue_, &pulseShortPlusValueNullIndicator_);
            Bind(statement, PULSESHORTPLUSDISPLAYTEXT_FIELD_ID, &pulseShortPlusDisplayText_, &pulseShortPlusDisplayTextLengthOrNullIndicator_);
            Bind(statement, PULSEMEDIUMMINUSVALUE_FIELD_ID, &pulseMediumMinusValue_, &pulseMediumMinusValueNullIndicator_);
            Bind(statement, PULSEMEDIUMMINUSDISPLAYTEXT_FIELD_ID, &pulseMediumMinusDisplayText_, &pulseMediumMinusDisplayTextLengthOrNullIndicator_);
            Bind(statement, PULSEMEDIUMVALUE_FIELD_ID, &pulseMediumValue_, &pulseMediumValueNullIndicator_);
            Bind(statement, PULSEMEDIUMDISPLAYTEXT_FIELD_ID, &pulseMediumDisplayText_, &pulseMediumDisplayTextLengthOrNullIndicator_);
            Bind(statement, PULSEMEDIUMPLUSVALUE_FIELD_ID, &pulseMediumPlusValue_, &pulseMediumPlusValueNullIndicator_);
            Bind(statement, PULSEMEDIUMPLUSDISPLAYTEXT_FIELD_ID, &pulseMediumPlusDisplayText_, &pulseMediumPlusDisplayTextLengthOrNullIndicator_);
            Bind(statement, PULSELONGMINUSVALUE_FIELD_ID, &pulseLongMinusValue_, &pulseLongMinusValueNullIndicator_);
            Bind(statement, PULSELONGMINUSDISPLAYTEXT_FIELD_ID, &pulseLongMinusDisplayText_, &pulseLongMinusDisplayTextLengthOrNullIndicator_);
            Bind(statement, PULSELONGVALUE_FIELD_ID, &pulseLongValue_, &pulseLongValueNullIndicator_);
            Bind(statement, PULSELONGDISPLAYTEXT_FIELD_ID, &pulseLongDisplayText_, &pulseLongDisplayTextLengthOrNullIndicator_);
            Bind(statement, PULSELONGPLUSVALUE_FIELD_ID, &pulseLongPlusValue_, &pulseLongPlusValueNullIndicator_);
            Bind(statement, PULSELONGPLUSDISPLAYTEXT_FIELD_ID, &pulseLongPlusDisplayText_, &pulseLongPlusDisplayTextLengthOrNullIndicator_);
        }

    };

    class RadioTypeColumnData : public DeviceTypeColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = DeviceTypeColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName],[Name]";
        static constexpr std::wstring_view ViewName = L"RadioTypeView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;

        RadioTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadioType;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class RadomeTypeColumnData : public DeviceTypeColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = DeviceTypeColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName],[Name]";
        static constexpr std::wstring_view ViewName = L"RadomeTypeView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;

        RadomeTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadomeType;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class WeatherStationTypeColumnData : public DeviceTypeColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = DeviceTypeColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[AssemblyName],[ClassName],[ProxyAssemblyName],[ProxyClassName],[Name]";
        static constexpr std::wstring_view ViewName = L"WeatherStationTypeView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;

        WeatherStationTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationType;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class DoubleTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        double value_ = 0.0;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"DoubleTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        DoubleTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DoubleTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double Value( ) const
        {
            return value_;
        }
        void SetValue( double value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class FacilityTypeColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name]";
        static constexpr std::wstring_view ViewName = L"FacilityTypeView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;

        FacilityTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::FacilityType;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class GeoPosition2DTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        double latitude_ = 0.0;
        SQLLEN latitudeNullIndicator_ = SQL_NULL_DATA;
        double longitude_ = 0.0;
        SQLLEN longitudeNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Latitude],[Longitude]";
        static constexpr std::wstring_view ViewName = L"GeoPosition2DTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 6;

        GeoPosition2DTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GeoPosition2DTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_, &latitudeNullIndicator_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_, &longitudeNullIndicator_);
        }

    };

    class GeoPosition3DTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        double latitude_ = 0.0;
        SQLLEN latitudeNullIndicator_ = SQL_NULL_DATA;
        double longitude_ = 0.0;
        SQLLEN longitudeNullIndicator_ = SQL_NULL_DATA;
        double altitude_ = 0.0;
        SQLLEN altitudeNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Latitude],[Longitude],[Altitude]";
        static constexpr std::wstring_view ViewName = L"GeoPosition3DTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT ALTITUDE_FIELD_ID = 7;

        GeoPosition3DTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GeoPosition3DTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Altitude( ) const
        {
            return altitude_;
        }
        void SetAltitude( double altitude )
        {
            altitude_ = altitude;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_, &latitudeNullIndicator_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_, &longitudeNullIndicator_);
            Bind(statement, ALTITUDE_FIELD_ID, &altitude_, &altitudeNullIndicator_);
        }

    };

    class GNSSDeviceCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid gNSSDevice_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[GNSSDevice],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"GNSSDeviceCommandView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT GNSSDEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REPLY_FIELD_ID = 7;

        GNSSDeviceCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GNSSDeviceCommand;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid GNSSDevice( ) const
        {
            return gNSSDevice_;
        }
        void SetGNSSDevice( const Guid& gNSSDevice )
        {
            gNSSDevice_ = gNSSDevice;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        void SetDeviceCommandSourceType( Data::DeviceCommandSourceType deviceCommandSourceType )
        {
            deviceCommandSourceType_ = deviceCommandSourceType;
        }
        Guid DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        void SetDeviceCommandSourceId( const Guid& deviceCommandSourceId )
        {
            deviceCommandSourceId_ = deviceCommandSourceId;
        }
        Guid Reply( ) const
        {
            return reply_;
        }
        void SetReply( const Guid& reply )
        {
            reply_ = reply;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, GNSSDEVICE_FIELD_ID, &gNSSDevice_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEVICECOMMANDSOURCETYPE_FIELD_ID, &deviceCommandSourceType_);
            Bind(statement, DEVICECOMMANDSOURCEID_FIELD_ID, &deviceCommandSourceId_);
            Bind(statement, REPLY_FIELD_ID, &reply_);
        }

    };

    class GNSSDeviceCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid gNSSDevice_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[GNSSDevice],[Timestamp],[Command],[Status],[Message]";
        static constexpr std::wstring_view ViewName = L"GNSSDeviceCommandReplyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT GNSSDEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COMMAND_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 7;

        GNSSDeviceCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GNSSDeviceCommandReply;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid GNSSDevice( ) const
        {
            return gNSSDevice_;
        }
        void SetGNSSDevice( const Guid& gNSSDevice )
        {
            gNSSDevice_ = gNSSDevice;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Command( ) const
        {
            return command_;
        }
        void SetCommand( const Guid& command )
        {
            command_ = command;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::DeviceCommandReplyStatus status )
        {
            status_ = status;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, GNSSDEVICE_FIELD_ID, &gNSSDevice_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COMMAND_FIELD_ID, &command_);
            Bind(statement, STATUS_FIELD_ID, &status_);
        }

    };

    class GNSSDeviceConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid gNSSDevice_;
        DateTime timestamp_;
        double defaultLatitude_ = 0.0;
        double defaultLongitude_ = 0.0;
        double defaultAltitude_ = 0.0;
        double latitudeOffset_ = 0.0;
        double longitudeOffset_ = 0.0;
        double altitudeOffset_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[GNSSDevice],[Timestamp],[DefaultLatitude],[DefaultLongitude],[DefaultAltitude],[LatitudeOffset],[LongitudeOffset],[AltitudeOffset]";
        static constexpr std::wstring_view ViewName = L"GNSSDeviceConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT GNSSDEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEFAULTLATITUDE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEFAULTLONGITUDE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT DEFAULTALTITUDE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT LATITUDEOFFSET_FIELD_ID = 8;
        static constexpr SQLUSMALLINT LONGITUDEOFFSET_FIELD_ID = 9;
        static constexpr SQLUSMALLINT ALTITUDEOFFSET_FIELD_ID = 10;

        GNSSDeviceConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GNSSDeviceConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid GNSSDevice( ) const
        {
            return gNSSDevice_;
        }
        void SetGNSSDevice( const Guid& gNSSDevice )
        {
            gNSSDevice_ = gNSSDevice;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double DefaultLatitude( ) const
        {
            return defaultLatitude_;
        }
        void SetDefaultLatitude( double defaultLatitude )
        {
            defaultLatitude_ = defaultLatitude;
        }
        double DefaultLongitude( ) const
        {
            return defaultLongitude_;
        }
        void SetDefaultLongitude( double defaultLongitude )
        {
            defaultLongitude_ = defaultLongitude;
        }
        double DefaultAltitude( ) const
        {
            return defaultAltitude_;
        }
        void SetDefaultAltitude( double defaultAltitude )
        {
            defaultAltitude_ = defaultAltitude;
        }
        double LatitudeOffset( ) const
        {
            return latitudeOffset_;
        }
        void SetLatitudeOffset( double latitudeOffset )
        {
            latitudeOffset_ = latitudeOffset;
        }
        double LongitudeOffset( ) const
        {
            return longitudeOffset_;
        }
        void SetLongitudeOffset( double longitudeOffset )
        {
            longitudeOffset_ = longitudeOffset;
        }
        double AltitudeOffset( ) const
        {
            return altitudeOffset_;
        }
        void SetAltitudeOffset( double altitudeOffset )
        {
            altitudeOffset_ = altitudeOffset;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, GNSSDEVICE_FIELD_ID, &gNSSDevice_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEFAULTLATITUDE_FIELD_ID, &defaultLatitude_);
            Bind(statement, DEFAULTLONGITUDE_FIELD_ID, &defaultLongitude_);
            Bind(statement, DEFAULTALTITUDE_FIELD_ID, &defaultAltitude_);
            Bind(statement, LATITUDEOFFSET_FIELD_ID, &latitudeOffset_);
            Bind(statement, LONGITUDEOFFSET_FIELD_ID, &longitudeOffset_);
            Bind(statement, ALTITUDEOFFSET_FIELD_ID, &altitudeOffset_);
        }

    };

    class GuidTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        Guid value_;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"GuidTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        GuidTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GuidTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Value( ) const
        {
            return value_;
        }
        void SetValue( const Guid& value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class GyroDeviceCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid gyroDevice_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[GyroDevice],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"GyroDeviceCommandView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT GYRODEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REPLY_FIELD_ID = 7;

        GyroDeviceCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroDeviceCommand;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid GyroDevice( ) const
        {
            return gyroDevice_;
        }
        void SetGyroDevice( const Guid& gyroDevice )
        {
            gyroDevice_ = gyroDevice;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        void SetDeviceCommandSourceType( Data::DeviceCommandSourceType deviceCommandSourceType )
        {
            deviceCommandSourceType_ = deviceCommandSourceType;
        }
        Guid DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        void SetDeviceCommandSourceId( const Guid& deviceCommandSourceId )
        {
            deviceCommandSourceId_ = deviceCommandSourceId;
        }
        Guid Reply( ) const
        {
            return reply_;
        }
        void SetReply( const Guid& reply )
        {
            reply_ = reply;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, GYRODEVICE_FIELD_ID, &gyroDevice_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEVICECOMMANDSOURCETYPE_FIELD_ID, &deviceCommandSourceType_);
            Bind(statement, DEVICECOMMANDSOURCEID_FIELD_ID, &deviceCommandSourceId_);
            Bind(statement, REPLY_FIELD_ID, &reply_);
        }

    };

    class GyroDeviceCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid gyroDevice_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[GyroDevice],[Timestamp],[Command],[Status],[Message]";
        static constexpr std::wstring_view ViewName = L"GyroDeviceCommandReplyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT GYRODEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COMMAND_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 7;

        GyroDeviceCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroDeviceCommandReply;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid GyroDevice( ) const
        {
            return gyroDevice_;
        }
        void SetGyroDevice( const Guid& gyroDevice )
        {
            gyroDevice_ = gyroDevice;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Command( ) const
        {
            return command_;
        }
        void SetCommand( const Guid& command )
        {
            command_ = command;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::DeviceCommandReplyStatus status )
        {
            status_ = status;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, GYRODEVICE_FIELD_ID, &gyroDevice_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COMMAND_FIELD_ID, &command_);
            Bind(statement, STATUS_FIELD_ID, &status_);
        }

    };

    class GyroDeviceConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid gyroDevice_;
        DateTime timestamp_;
        double defaultHeadingTrueNorth_ = 0.0;
        double defaultMagneticTrueNorth_ = 0.0;
        double headingTrueNorthOffset_ = 0.0;
        double headingMagneticNorthOffset_ = 0.0;
        std::array<wchar_t,65> pitchTransducerName_ = {};
        SQLLEN pitchTransducerNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,65> rollTransducerName_ = {};
        SQLLEN rollTransducerNameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[GyroDevice],[Timestamp],[DefaultHeadingTrueNorth],[DefaultMagneticTrueNorth],[HeadingTrueNorthOffset],[HeadingMagneticNorthOffset],[PitchTransducerName],[RollTransducerName]";
        static constexpr std::wstring_view ViewName = L"GyroDeviceConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT GYRODEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEFAULTHEADINGTRUENORTH_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEFAULTMAGNETICTRUENORTH_FIELD_ID = 6;
        static constexpr SQLUSMALLINT HEADINGTRUENORTHOFFSET_FIELD_ID = 7;
        static constexpr SQLUSMALLINT HEADINGMAGNETICNORTHOFFSET_FIELD_ID = 8;
        static constexpr SQLUSMALLINT PITCHTRANSDUCERNAME_FIELD_ID = 9;
        static constexpr SQLUSMALLINT ROLLTRANSDUCERNAME_FIELD_ID = 10;

        GyroDeviceConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroDeviceConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid GyroDevice( ) const
        {
            return gyroDevice_;
        }
        void SetGyroDevice( const Guid& gyroDevice )
        {
            gyroDevice_ = gyroDevice;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double DefaultHeadingTrueNorth( ) const
        {
            return defaultHeadingTrueNorth_;
        }
        void SetDefaultHeadingTrueNorth( double defaultHeadingTrueNorth )
        {
            defaultHeadingTrueNorth_ = defaultHeadingTrueNorth;
        }
        double DefaultMagneticTrueNorth( ) const
        {
            return defaultMagneticTrueNorth_;
        }
        void SetDefaultMagneticTrueNorth( double defaultMagneticTrueNorth )
        {
            defaultMagneticTrueNorth_ = defaultMagneticTrueNorth;
        }
        double HeadingTrueNorthOffset( ) const
        {
            return headingTrueNorthOffset_;
        }
        void SetHeadingTrueNorthOffset( double headingTrueNorthOffset )
        {
            headingTrueNorthOffset_ = headingTrueNorthOffset;
        }
        double HeadingMagneticNorthOffset( ) const
        {
            return headingMagneticNorthOffset_;
        }
        void SetHeadingMagneticNorthOffset( double headingMagneticNorthOffset )
        {
            headingMagneticNorthOffset_ = headingMagneticNorthOffset;
        }
        std::wstring_view PitchTransducerName( ) const
        {
            if(pitchTransducerNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pitchTransducerName_.data(),static_cast<size_t>( pitchTransducerNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPitchTransducerName( const WideString& pitchTransducerName )
        {
            Assign(pitchTransducerName, pitchTransducerName_, pitchTransducerNameLengthOrNullIndicator_);
        }
        std::wstring_view RollTransducerName( ) const
        {
            if(rollTransducerNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(rollTransducerName_.data(),static_cast<size_t>( rollTransducerNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetRollTransducerName( const WideString& rollTransducerName )
        {
            Assign(rollTransducerName, rollTransducerName_, rollTransducerNameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, GYRODEVICE_FIELD_ID, &gyroDevice_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEFAULTHEADINGTRUENORTH_FIELD_ID, &defaultHeadingTrueNorth_);
            Bind(statement, DEFAULTMAGNETICTRUENORTH_FIELD_ID, &defaultMagneticTrueNorth_);
            Bind(statement, HEADINGTRUENORTHOFFSET_FIELD_ID, &headingTrueNorthOffset_);
            Bind(statement, HEADINGMAGNETICNORTHOFFSET_FIELD_ID, &headingMagneticNorthOffset_);
            Bind(statement, PITCHTRANSDUCERNAME_FIELD_ID, &pitchTransducerName_, &pitchTransducerNameLengthOrNullIndicator_);
            Bind(statement, ROLLTRANSDUCERNAME_FIELD_ID, &rollTransducerName_, &rollTransducerNameLengthOrNullIndicator_);
        }

    };

    class IdentityColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion]";
        static constexpr std::wstring_view ViewName = L"IdentityView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;

        IdentityColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Identity;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
        }

    };

    class CallsignColumnData : public IdentityColumnData
    {
        std::array<wchar_t,128> identifier_ = {};
        SQLLEN identifierLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = IdentityColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Identifier]";
        static constexpr std::wstring_view ViewName = L"CallsignView";

        static constexpr SQLUSMALLINT IDENTIFIER_FIELD_ID = 3;

        CallsignColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Callsign;
        }

        std::wstring_view Identifier( ) const
        {
            if(identifierLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(identifier_.data(),static_cast<size_t>( identifierLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetIdentifier( const WideString& identifier )
        {
            Assign(identifier, identifier_, identifierLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, IDENTIFIER_FIELD_ID, &identifier_, &identifierLengthOrNullIndicator_);
        }

    };

    class InternationalMaritimeOrganizationNumberColumnData : public IdentityColumnData
    {
        Int64 identifier_ = 0;
    public:
        using Base = IdentityColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Identifier]";
        static constexpr std::wstring_view ViewName = L"InternationalMaritimeOrganizationNumberView";

        static constexpr SQLUSMALLINT IDENTIFIER_FIELD_ID = 3;

        InternationalMaritimeOrganizationNumberColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::InternationalMaritimeOrganizationNumber;
        }

        Int64 Identifier( ) const
        {
            return identifier_;
        }
        void SetIdentifier( Int64 identifier )
        {
            identifier_ = identifier;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, IDENTIFIER_FIELD_ID, &identifier_);
        }

    };

    class MaritimeMobileServiceIdentityColumnData : public IdentityColumnData
    {
        Int64 identifier_ = 0;
    public:
        using Base = IdentityColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Identifier]";
        static constexpr std::wstring_view ViewName = L"MaritimeMobileServiceIdentityView";

        static constexpr SQLUSMALLINT IDENTIFIER_FIELD_ID = 3;

        MaritimeMobileServiceIdentityColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MaritimeMobileServiceIdentity;
        }

        Int64 Identifier( ) const
        {
            return identifier_;
        }
        void SetIdentifier( Int64 identifier )
        {
            identifier_ = identifier;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, IDENTIFIER_FIELD_ID, &identifier_);
        }

    };

    class NameColumnData : public IdentityColumnData
    {
        std::array<wchar_t,101> text_ = {};
        SQLLEN textLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = IdentityColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Text]";
        static constexpr std::wstring_view ViewName = L"NameView";

        static constexpr SQLUSMALLINT TEXT_FIELD_ID = 3;

        NameColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Name;
        }

        std::wstring_view Text( ) const
        {
            if(textLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(text_.data(),static_cast<size_t>( textLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetText( const WideString& text )
        {
            Assign(text, text_, textLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TEXT_FIELD_ID, &text_, &textLengthOrNullIndicator_);
        }

    };

    class Int16TimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        Int16 value_ = 0;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"Int16TimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        Int16TimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int16TimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Int16 Value( ) const
        {
            return value_;
        }
        void SetValue( Int16 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class Int32TimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        Int32 value_ = 0;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"Int32TimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        Int32TimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int32TimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Int32 Value( ) const
        {
            return value_;
        }
        void SetValue( Int32 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class Int64TimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        Int64 value_ = 0;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"Int64TimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        Int64TimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int64TimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Int64 Value( ) const
        {
            return value_;
        }
        void SetValue( Int64 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class ItemColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion]";
        static constexpr std::wstring_view ViewName = L"ItemView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;

        ItemColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Item;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
        }

    };

    class BaseStationColumnData : public ItemColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Guid type_;
    public:
        using Base = ItemColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Type]";
        static constexpr std::wstring_view ViewName = L"BaseStationView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 4;

        BaseStationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BaseStation;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, TYPE_FIELD_ID, &type_);
        }

    };

    class DeviceColumnData : public ItemColumnData
    {
        Guid host_;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString description_;
        SQLLEN descriptionLengthOrNullIndicator_ = SQL_NULL_DATA;
        Guid enabledTimeseries_;
    public:
        using Base = ItemColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Description]";
        static constexpr std::wstring_view ViewName = L"DeviceView";

        static constexpr SQLUSMALLINT HOST_FIELD_ID = 3;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT ENABLEDTIMESERIES_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DESCRIPTION_FIELD_ID = 6;

        DeviceColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Device;
        }

        Guid Host( ) const
        {
            return host_;
        }
        void SetHost( const Guid& host )
        {
            host_ = host;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        void SetDescription( const WideString& description )
        {
            Assign(description, description_, descriptionLengthOrNullIndicator_);
        }
        Guid EnabledTimeseries( ) const
        {
            return enabledTimeseries_;
        }
        void SetEnabledTimeseries( const Guid& enabledTimeseries )
        {
            enabledTimeseries_ = enabledTimeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, HOST_FIELD_ID, &host_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, ENABLEDTIMESERIES_FIELD_ID, &enabledTimeseries_);
        }

    };

    class CameraColumnData : public DeviceColumnData
    {
        Guid type_;
    public:
        using Base = DeviceColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Type],[Description]";
        static constexpr std::wstring_view ViewName = L"CameraView";

        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 7;

        CameraColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Camera;
        }

        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TYPE_FIELD_ID, &type_);
        }

    };

    class GNSSDeviceColumnData : public DeviceColumnData
    {
        Guid type_;
        Guid latitudeTimeseries_;
        Guid longitudeTimeseries_;
        Guid altitudeTimeseries_;
    public:
        using Base = DeviceColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Type],[LatitudeTimeseries],[LongitudeTimeseries],[AltitudeTimeseries],[Description]";
        static constexpr std::wstring_view ViewName = L"GNSSDeviceView";

        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT LATITUDETIMESERIES_FIELD_ID = 8;
        static constexpr SQLUSMALLINT LONGITUDETIMESERIES_FIELD_ID = 9;
        static constexpr SQLUSMALLINT ALTITUDETIMESERIES_FIELD_ID = 10;

        GNSSDeviceColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GNSSDevice;
        }

        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        Guid LatitudeTimeseries( ) const
        {
            return latitudeTimeseries_;
        }
        void SetLatitudeTimeseries( const Guid& latitudeTimeseries )
        {
            latitudeTimeseries_ = latitudeTimeseries;
        }
        Guid LongitudeTimeseries( ) const
        {
            return longitudeTimeseries_;
        }
        void SetLongitudeTimeseries( const Guid& longitudeTimeseries )
        {
            longitudeTimeseries_ = longitudeTimeseries;
        }
        Guid AltitudeTimeseries( ) const
        {
            return altitudeTimeseries_;
        }
        void SetAltitudeTimeseries( const Guid& altitudeTimeseries )
        {
            altitudeTimeseries_ = altitudeTimeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TYPE_FIELD_ID, &type_);
            Bind(statement, LATITUDETIMESERIES_FIELD_ID, &latitudeTimeseries_);
            Bind(statement, LONGITUDETIMESERIES_FIELD_ID, &longitudeTimeseries_);
            Bind(statement, ALTITUDETIMESERIES_FIELD_ID, &altitudeTimeseries_);
        }

    };

    class GyroDeviceColumnData : public DeviceColumnData
    {
        Guid type_;
        Guid headingTrueNorthTimeseries_;
        Guid headingMagneticNorthTimeseries_;
        Guid pitchTimeseries_;
        Guid rateOfTurnTimeseries_;
        Guid rollTimeseries_;
        Guid courseTimeseries_;
        Guid speedTimeseries_;
        Guid gNSSDevice_;
    public:
        using Base = DeviceColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Type],[HeadingTrueNorthTimeseries],[HeadingMagneticNorthTimeseries],[PitchTimeseries],[RateOfTurnTimeseries],[RollTimeseries],[CourseTimeseries],[SpeedTimeseries],[GNSSDevice],[Description]";
        static constexpr std::wstring_view ViewName = L"GyroDeviceView";

        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT HEADINGTRUENORTHTIMESERIES_FIELD_ID = 8;
        static constexpr SQLUSMALLINT HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID = 9;
        static constexpr SQLUSMALLINT PITCHTIMESERIES_FIELD_ID = 10;
        static constexpr SQLUSMALLINT RATEOFTURNTIMESERIES_FIELD_ID = 11;
        static constexpr SQLUSMALLINT ROLLTIMESERIES_FIELD_ID = 12;
        static constexpr SQLUSMALLINT COURSETIMESERIES_FIELD_ID = 13;
        static constexpr SQLUSMALLINT SPEEDTIMESERIES_FIELD_ID = 14;
        static constexpr SQLUSMALLINT GNSSDEVICE_FIELD_ID = 15;

        GyroDeviceColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroDevice;
        }

        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        Guid HeadingTrueNorthTimeseries( ) const
        {
            return headingTrueNorthTimeseries_;
        }
        void SetHeadingTrueNorthTimeseries( const Guid& headingTrueNorthTimeseries )
        {
            headingTrueNorthTimeseries_ = headingTrueNorthTimeseries;
        }
        Guid HeadingMagneticNorthTimeseries( ) const
        {
            return headingMagneticNorthTimeseries_;
        }
        void SetHeadingMagneticNorthTimeseries( const Guid& headingMagneticNorthTimeseries )
        {
            headingMagneticNorthTimeseries_ = headingMagneticNorthTimeseries;
        }
        Guid PitchTimeseries( ) const
        {
            return pitchTimeseries_;
        }
        void SetPitchTimeseries( const Guid& pitchTimeseries )
        {
            pitchTimeseries_ = pitchTimeseries;
        }
        Guid RateOfTurnTimeseries( ) const
        {
            return rateOfTurnTimeseries_;
        }
        void SetRateOfTurnTimeseries( const Guid& rateOfTurnTimeseries )
        {
            rateOfTurnTimeseries_ = rateOfTurnTimeseries;
        }
        Guid RollTimeseries( ) const
        {
            return rollTimeseries_;
        }
        void SetRollTimeseries( const Guid& rollTimeseries )
        {
            rollTimeseries_ = rollTimeseries;
        }
        Guid CourseTimeseries( ) const
        {
            return courseTimeseries_;
        }
        void SetCourseTimeseries( const Guid& courseTimeseries )
        {
            courseTimeseries_ = courseTimeseries;
        }
        Guid SpeedTimeseries( ) const
        {
            return speedTimeseries_;
        }
        void SetSpeedTimeseries( const Guid& speedTimeseries )
        {
            speedTimeseries_ = speedTimeseries;
        }
        Guid GNSSDevice( ) const
        {
            return gNSSDevice_;
        }
        void SetGNSSDevice( const Guid& gNSSDevice )
        {
            gNSSDevice_ = gNSSDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TYPE_FIELD_ID, &type_);
            Bind(statement, HEADINGTRUENORTHTIMESERIES_FIELD_ID, &headingTrueNorthTimeseries_);
            Bind(statement, HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID, &headingMagneticNorthTimeseries_);
            Bind(statement, PITCHTIMESERIES_FIELD_ID, &pitchTimeseries_);
            Bind(statement, RATEOFTURNTIMESERIES_FIELD_ID, &rateOfTurnTimeseries_);
            Bind(statement, ROLLTIMESERIES_FIELD_ID, &rollTimeseries_);
            Bind(statement, COURSETIMESERIES_FIELD_ID, &courseTimeseries_);
            Bind(statement, SPEEDTIMESERIES_FIELD_ID, &speedTimeseries_);
            Bind(statement, GNSSDEVICE_FIELD_ID, &gNSSDevice_);
        }

    };

    class LineInputDeviceColumnData : public DeviceColumnData
    {
        Guid type_;
    public:
        using Base = DeviceColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Type],[Description]";
        static constexpr std::wstring_view ViewName = L"LineInputDeviceView";

        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 7;

        LineInputDeviceColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LineInputDevice;
        }

        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TYPE_FIELD_ID, &type_);
        }

    };

    class OilspillDetectorColumnData : public DeviceColumnData
    {
        Guid type_;
    public:
        using Base = DeviceColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Type],[Description]";
        static constexpr std::wstring_view ViewName = L"OilspillDetectorView";

        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 7;

        OilspillDetectorColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::OilspillDetector;
        }

        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TYPE_FIELD_ID, &type_);
        }

    };

    class RadioColumnData : public DeviceColumnData
    {
        Guid type_;
    public:
        using Base = DeviceColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Type],[Description]";
        static constexpr std::wstring_view ViewName = L"RadioView";

        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 7;

        RadioColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Radio;
        }

        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TYPE_FIELD_ID, &type_);
        }

    };

    class RadomeColumnData : public DeviceColumnData
    {
        Guid type_;
        Guid radar_;
        Guid pressureTimeseries_;
        Guid temperatureTimeseries_;
        Guid dewPointTimeseries_;
        Guid statusTimeseries_;
    public:
        using Base = DeviceColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Type],[Radar],[PressureTimeseries],[TemperatureTimeseries],[DewPointTimeseries],[StatusTimeseries],[Description]";
        static constexpr std::wstring_view ViewName = L"RadomeView";

        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 8;
        static constexpr SQLUSMALLINT PRESSURETIMESERIES_FIELD_ID = 9;
        static constexpr SQLUSMALLINT TEMPERATURETIMESERIES_FIELD_ID = 10;
        static constexpr SQLUSMALLINT DEWPOINTTIMESERIES_FIELD_ID = 11;
        static constexpr SQLUSMALLINT STATUSTIMESERIES_FIELD_ID = 12;

        RadomeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Radome;
        }

        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        Guid PressureTimeseries( ) const
        {
            return pressureTimeseries_;
        }
        void SetPressureTimeseries( const Guid& pressureTimeseries )
        {
            pressureTimeseries_ = pressureTimeseries;
        }
        Guid TemperatureTimeseries( ) const
        {
            return temperatureTimeseries_;
        }
        void SetTemperatureTimeseries( const Guid& temperatureTimeseries )
        {
            temperatureTimeseries_ = temperatureTimeseries;
        }
        Guid DewPointTimeseries( ) const
        {
            return dewPointTimeseries_;
        }
        void SetDewPointTimeseries( const Guid& dewPointTimeseries )
        {
            dewPointTimeseries_ = dewPointTimeseries;
        }
        Guid StatusTimeseries( ) const
        {
            return statusTimeseries_;
        }
        void SetStatusTimeseries( const Guid& statusTimeseries )
        {
            statusTimeseries_ = statusTimeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TYPE_FIELD_ID, &type_);
            Bind(statement, RADAR_FIELD_ID, &radar_);
            Bind(statement, PRESSURETIMESERIES_FIELD_ID, &pressureTimeseries_);
            Bind(statement, TEMPERATURETIMESERIES_FIELD_ID, &temperatureTimeseries_);
            Bind(statement, DEWPOINTTIMESERIES_FIELD_ID, &dewPointTimeseries_);
            Bind(statement, STATUSTIMESERIES_FIELD_ID, &statusTimeseries_);
        }

    };

    class TrackerColumnData : public DeviceColumnData
    {
    public:
        using Base = DeviceColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Description]";
        static constexpr std::wstring_view ViewName = L"TrackerView";

        TrackerColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Tracker;
        }

    };

    class AisTransceiverColumnData : public TrackerColumnData
    {
        Guid type_;
    public:
        using Base = TrackerColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Type],[Description]";
        static constexpr std::wstring_view ViewName = L"AisTransceiverView";

        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 7;

        AisTransceiverColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisTransceiver;
        }

        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TYPE_FIELD_ID, &type_);
        }

    };

    class RadarColumnData : public TrackerColumnData
    {
        Guid type_;
        Guid saveSettingsTimeseries_;
        Guid powerOnTimeseries_;
        Guid trackingOnTimeseries_;
        Guid radarPulseTimeseries_;
        Guid tuningTimeseries_;
        Guid blankSector1Timeseries_;
        Guid sector1StartTimeseries_;
        Guid sector1EndTimeseries_;
        Guid blankSector2Timeseries_;
        Guid sector2StartTimeseries_;
        Guid sector2EndTimeseries_;
        Guid enableAutomaticFrequencyControlTimeseries_;
        Guid azimuthOffsetTimeseries_;
        Guid enableSensitivityTimeControlTimeseries_;
        Guid automaticSensitivityTimeControlTimeseries_;
        Guid sensitivityTimeControlLevelTimeseries_;
        Guid enableFastTimeConstantTimeseries_;
        Guid fastTimeConstantLevelTimeseries_;
        Guid fastTimeConstantModeTimeseries_;
        Guid latitudeTimeseries_;
        Guid longitudeTimeseries_;
        Guid radome_;
        Guid gNSSDevice_;
    public:
        using Base = TrackerColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Type],[SaveSettingsTimeseries],[PowerOnTimeseries],[TrackingOnTimeseries],[RadarPulseTimeseries],[TuningTimeseries],[BlankSector1Timeseries],[Sector1StartTimeseries],[Sector1EndTimeseries],[BlankSector2Timeseries],[Sector2StartTimeseries],[Sector2EndTimeseries],[EnableAutomaticFrequencyControlTimeseries],[AzimuthOffsetTimeseries],[EnableSensitivityTimeControlTimeseries],[AutomaticSensitivityTimeControlTimeseries],[SensitivityTimeControlLevelTimeseries],[EnableFastTimeConstantTimeseries],[FastTimeConstantLevelTimeseries],[FastTimeConstantModeTimeseries],[LatitudeTimeseries],[LongitudeTimeseries],[Radome],[GNSSDevice],[Description]";
        static constexpr std::wstring_view ViewName = L"RadarView";

        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT SAVESETTINGSTIMESERIES_FIELD_ID = 8;
        static constexpr SQLUSMALLINT POWERONTIMESERIES_FIELD_ID = 9;
        static constexpr SQLUSMALLINT TRACKINGONTIMESERIES_FIELD_ID = 10;
        static constexpr SQLUSMALLINT RADARPULSETIMESERIES_FIELD_ID = 11;
        static constexpr SQLUSMALLINT TUNINGTIMESERIES_FIELD_ID = 12;
        static constexpr SQLUSMALLINT BLANKSECTOR1TIMESERIES_FIELD_ID = 13;
        static constexpr SQLUSMALLINT SECTOR1STARTTIMESERIES_FIELD_ID = 14;
        static constexpr SQLUSMALLINT SECTOR1ENDTIMESERIES_FIELD_ID = 15;
        static constexpr SQLUSMALLINT BLANKSECTOR2TIMESERIES_FIELD_ID = 16;
        static constexpr SQLUSMALLINT SECTOR2STARTTIMESERIES_FIELD_ID = 17;
        static constexpr SQLUSMALLINT SECTOR2ENDTIMESERIES_FIELD_ID = 18;
        static constexpr SQLUSMALLINT ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 19;
        static constexpr SQLUSMALLINT AZIMUTHOFFSETTIMESERIES_FIELD_ID = 20;
        static constexpr SQLUSMALLINT ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 21;
        static constexpr SQLUSMALLINT AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 22;
        static constexpr SQLUSMALLINT SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 23;
        static constexpr SQLUSMALLINT ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 24;
        static constexpr SQLUSMALLINT FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 25;
        static constexpr SQLUSMALLINT FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 26;
        static constexpr SQLUSMALLINT LATITUDETIMESERIES_FIELD_ID = 27;
        static constexpr SQLUSMALLINT LONGITUDETIMESERIES_FIELD_ID = 28;
        static constexpr SQLUSMALLINT RADOME_FIELD_ID = 29;
        static constexpr SQLUSMALLINT GNSSDEVICE_FIELD_ID = 30;

        RadarColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Radar;
        }

        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        Guid SaveSettingsTimeseries( ) const
        {
            return saveSettingsTimeseries_;
        }
        void SetSaveSettingsTimeseries( const Guid& saveSettingsTimeseries )
        {
            saveSettingsTimeseries_ = saveSettingsTimeseries;
        }
        Guid PowerOnTimeseries( ) const
        {
            return powerOnTimeseries_;
        }
        void SetPowerOnTimeseries( const Guid& powerOnTimeseries )
        {
            powerOnTimeseries_ = powerOnTimeseries;
        }
        Guid TrackingOnTimeseries( ) const
        {
            return trackingOnTimeseries_;
        }
        void SetTrackingOnTimeseries( const Guid& trackingOnTimeseries )
        {
            trackingOnTimeseries_ = trackingOnTimeseries;
        }
        Guid RadarPulseTimeseries( ) const
        {
            return radarPulseTimeseries_;
        }
        void SetRadarPulseTimeseries( const Guid& radarPulseTimeseries )
        {
            radarPulseTimeseries_ = radarPulseTimeseries;
        }
        Guid TuningTimeseries( ) const
        {
            return tuningTimeseries_;
        }
        void SetTuningTimeseries( const Guid& tuningTimeseries )
        {
            tuningTimeseries_ = tuningTimeseries;
        }
        Guid BlankSector1Timeseries( ) const
        {
            return blankSector1Timeseries_;
        }
        void SetBlankSector1Timeseries( const Guid& blankSector1Timeseries )
        {
            blankSector1Timeseries_ = blankSector1Timeseries;
        }
        Guid Sector1StartTimeseries( ) const
        {
            return sector1StartTimeseries_;
        }
        void SetSector1StartTimeseries( const Guid& sector1StartTimeseries )
        {
            sector1StartTimeseries_ = sector1StartTimeseries;
        }
        Guid Sector1EndTimeseries( ) const
        {
            return sector1EndTimeseries_;
        }
        void SetSector1EndTimeseries( const Guid& sector1EndTimeseries )
        {
            sector1EndTimeseries_ = sector1EndTimeseries;
        }
        Guid BlankSector2Timeseries( ) const
        {
            return blankSector2Timeseries_;
        }
        void SetBlankSector2Timeseries( const Guid& blankSector2Timeseries )
        {
            blankSector2Timeseries_ = blankSector2Timeseries;
        }
        Guid Sector2StartTimeseries( ) const
        {
            return sector2StartTimeseries_;
        }
        void SetSector2StartTimeseries( const Guid& sector2StartTimeseries )
        {
            sector2StartTimeseries_ = sector2StartTimeseries;
        }
        Guid Sector2EndTimeseries( ) const
        {
            return sector2EndTimeseries_;
        }
        void SetSector2EndTimeseries( const Guid& sector2EndTimeseries )
        {
            sector2EndTimeseries_ = sector2EndTimeseries;
        }
        Guid EnableAutomaticFrequencyControlTimeseries( ) const
        {
            return enableAutomaticFrequencyControlTimeseries_;
        }
        void SetEnableAutomaticFrequencyControlTimeseries( const Guid& enableAutomaticFrequencyControlTimeseries )
        {
            enableAutomaticFrequencyControlTimeseries_ = enableAutomaticFrequencyControlTimeseries;
        }
        Guid AzimuthOffsetTimeseries( ) const
        {
            return azimuthOffsetTimeseries_;
        }
        void SetAzimuthOffsetTimeseries( const Guid& azimuthOffsetTimeseries )
        {
            azimuthOffsetTimeseries_ = azimuthOffsetTimeseries;
        }
        Guid EnableSensitivityTimeControlTimeseries( ) const
        {
            return enableSensitivityTimeControlTimeseries_;
        }
        void SetEnableSensitivityTimeControlTimeseries( const Guid& enableSensitivityTimeControlTimeseries )
        {
            enableSensitivityTimeControlTimeseries_ = enableSensitivityTimeControlTimeseries;
        }
        Guid AutomaticSensitivityTimeControlTimeseries( ) const
        {
            return automaticSensitivityTimeControlTimeseries_;
        }
        void SetAutomaticSensitivityTimeControlTimeseries( const Guid& automaticSensitivityTimeControlTimeseries )
        {
            automaticSensitivityTimeControlTimeseries_ = automaticSensitivityTimeControlTimeseries;
        }
        Guid SensitivityTimeControlLevelTimeseries( ) const
        {
            return sensitivityTimeControlLevelTimeseries_;
        }
        void SetSensitivityTimeControlLevelTimeseries( const Guid& sensitivityTimeControlLevelTimeseries )
        {
            sensitivityTimeControlLevelTimeseries_ = sensitivityTimeControlLevelTimeseries;
        }
        Guid EnableFastTimeConstantTimeseries( ) const
        {
            return enableFastTimeConstantTimeseries_;
        }
        void SetEnableFastTimeConstantTimeseries( const Guid& enableFastTimeConstantTimeseries )
        {
            enableFastTimeConstantTimeseries_ = enableFastTimeConstantTimeseries;
        }
        Guid FastTimeConstantLevelTimeseries( ) const
        {
            return fastTimeConstantLevelTimeseries_;
        }
        void SetFastTimeConstantLevelTimeseries( const Guid& fastTimeConstantLevelTimeseries )
        {
            fastTimeConstantLevelTimeseries_ = fastTimeConstantLevelTimeseries;
        }
        Guid FastTimeConstantModeTimeseries( ) const
        {
            return fastTimeConstantModeTimeseries_;
        }
        void SetFastTimeConstantModeTimeseries( const Guid& fastTimeConstantModeTimeseries )
        {
            fastTimeConstantModeTimeseries_ = fastTimeConstantModeTimeseries;
        }
        Guid LatitudeTimeseries( ) const
        {
            return latitudeTimeseries_;
        }
        void SetLatitudeTimeseries( const Guid& latitudeTimeseries )
        {
            latitudeTimeseries_ = latitudeTimeseries;
        }
        Guid LongitudeTimeseries( ) const
        {
            return longitudeTimeseries_;
        }
        void SetLongitudeTimeseries( const Guid& longitudeTimeseries )
        {
            longitudeTimeseries_ = longitudeTimeseries;
        }
        Guid Radome( ) const
        {
            return radome_;
        }
        void SetRadome( const Guid& radome )
        {
            radome_ = radome;
        }
        Guid GNSSDevice( ) const
        {
            return gNSSDevice_;
        }
        void SetGNSSDevice( const Guid& gNSSDevice )
        {
            gNSSDevice_ = gNSSDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TYPE_FIELD_ID, &type_);
            Bind(statement, SAVESETTINGSTIMESERIES_FIELD_ID, &saveSettingsTimeseries_);
            Bind(statement, POWERONTIMESERIES_FIELD_ID, &powerOnTimeseries_);
            Bind(statement, TRACKINGONTIMESERIES_FIELD_ID, &trackingOnTimeseries_);
            Bind(statement, RADARPULSETIMESERIES_FIELD_ID, &radarPulseTimeseries_);
            Bind(statement, TUNINGTIMESERIES_FIELD_ID, &tuningTimeseries_);
            Bind(statement, BLANKSECTOR1TIMESERIES_FIELD_ID, &blankSector1Timeseries_);
            Bind(statement, SECTOR1STARTTIMESERIES_FIELD_ID, &sector1StartTimeseries_);
            Bind(statement, SECTOR1ENDTIMESERIES_FIELD_ID, &sector1EndTimeseries_);
            Bind(statement, BLANKSECTOR2TIMESERIES_FIELD_ID, &blankSector2Timeseries_);
            Bind(statement, SECTOR2STARTTIMESERIES_FIELD_ID, &sector2StartTimeseries_);
            Bind(statement, SECTOR2ENDTIMESERIES_FIELD_ID, &sector2EndTimeseries_);
            Bind(statement, ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID, &enableAutomaticFrequencyControlTimeseries_);
            Bind(statement, AZIMUTHOFFSETTIMESERIES_FIELD_ID, &azimuthOffsetTimeseries_);
            Bind(statement, ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID, &enableSensitivityTimeControlTimeseries_);
            Bind(statement, AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID, &automaticSensitivityTimeControlTimeseries_);
            Bind(statement, SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID, &sensitivityTimeControlLevelTimeseries_);
            Bind(statement, ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID, &enableFastTimeConstantTimeseries_);
            Bind(statement, FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID, &fastTimeConstantLevelTimeseries_);
            Bind(statement, FASTTIMECONSTANTMODETIMESERIES_FIELD_ID, &fastTimeConstantModeTimeseries_);
            Bind(statement, LATITUDETIMESERIES_FIELD_ID, &latitudeTimeseries_);
            Bind(statement, LONGITUDETIMESERIES_FIELD_ID, &longitudeTimeseries_);
            Bind(statement, RADOME_FIELD_ID, &radome_);
            Bind(statement, GNSSDEVICE_FIELD_ID, &gNSSDevice_);
        }

    };

    class WeatherStationColumnData : public DeviceColumnData
    {
        Guid type_;
        Guid barometricPressureTimeseries_;
        Guid airTemperatureTimeseries_;
        Guid waterTemperatureTimeseries_;
        Guid relativeHumidityTimeseries_;
        Guid absoluteHumidityTimeseries_;
        Guid dewPointTimeseries_;
        Guid windDirectionTimeseries_;
        Guid windSpeedTimeseries_;
        Guid gyro_;
    public:
        using Base = DeviceColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Name],[EnabledTimeseries],[Type],[BarometricPressureTimeseries],[AirTemperatureTimeseries],[WaterTemperatureTimeseries],[RelativeHumidityTimeseries],[AbsoluteHumidityTimeseries],[DewPointTimeseries],[WindDirectionTimeseries],[WindSpeedTimeseries],[Gyro],[Description]";
        static constexpr std::wstring_view ViewName = L"WeatherStationView";

        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT BAROMETRICPRESSURETIMESERIES_FIELD_ID = 8;
        static constexpr SQLUSMALLINT AIRTEMPERATURETIMESERIES_FIELD_ID = 9;
        static constexpr SQLUSMALLINT WATERTEMPERATURETIMESERIES_FIELD_ID = 10;
        static constexpr SQLUSMALLINT RELATIVEHUMIDITYTIMESERIES_FIELD_ID = 11;
        static constexpr SQLUSMALLINT ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID = 12;
        static constexpr SQLUSMALLINT DEWPOINTTIMESERIES_FIELD_ID = 13;
        static constexpr SQLUSMALLINT WINDDIRECTIONTIMESERIES_FIELD_ID = 14;
        static constexpr SQLUSMALLINT WINDSPEEDTIMESERIES_FIELD_ID = 15;
        static constexpr SQLUSMALLINT GYRO_FIELD_ID = 16;

        WeatherStationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStation;
        }

        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        Guid BarometricPressureTimeseries( ) const
        {
            return barometricPressureTimeseries_;
        }
        void SetBarometricPressureTimeseries( const Guid& barometricPressureTimeseries )
        {
            barometricPressureTimeseries_ = barometricPressureTimeseries;
        }
        Guid AirTemperatureTimeseries( ) const
        {
            return airTemperatureTimeseries_;
        }
        void SetAirTemperatureTimeseries( const Guid& airTemperatureTimeseries )
        {
            airTemperatureTimeseries_ = airTemperatureTimeseries;
        }
        Guid WaterTemperatureTimeseries( ) const
        {
            return waterTemperatureTimeseries_;
        }
        void SetWaterTemperatureTimeseries( const Guid& waterTemperatureTimeseries )
        {
            waterTemperatureTimeseries_ = waterTemperatureTimeseries;
        }
        Guid RelativeHumidityTimeseries( ) const
        {
            return relativeHumidityTimeseries_;
        }
        void SetRelativeHumidityTimeseries( const Guid& relativeHumidityTimeseries )
        {
            relativeHumidityTimeseries_ = relativeHumidityTimeseries;
        }
        Guid AbsoluteHumidityTimeseries( ) const
        {
            return absoluteHumidityTimeseries_;
        }
        void SetAbsoluteHumidityTimeseries( const Guid& absoluteHumidityTimeseries )
        {
            absoluteHumidityTimeseries_ = absoluteHumidityTimeseries;
        }
        Guid DewPointTimeseries( ) const
        {
            return dewPointTimeseries_;
        }
        void SetDewPointTimeseries( const Guid& dewPointTimeseries )
        {
            dewPointTimeseries_ = dewPointTimeseries;
        }
        Guid WindDirectionTimeseries( ) const
        {
            return windDirectionTimeseries_;
        }
        void SetWindDirectionTimeseries( const Guid& windDirectionTimeseries )
        {
            windDirectionTimeseries_ = windDirectionTimeseries;
        }
        Guid WindSpeedTimeseries( ) const
        {
            return windSpeedTimeseries_;
        }
        void SetWindSpeedTimeseries( const Guid& windSpeedTimeseries )
        {
            windSpeedTimeseries_ = windSpeedTimeseries;
        }
        Guid Gyro( ) const
        {
            return gyro_;
        }
        void SetGyro( const Guid& gyro )
        {
            gyro_ = gyro;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TYPE_FIELD_ID, &type_);
            Bind(statement, BAROMETRICPRESSURETIMESERIES_FIELD_ID, &barometricPressureTimeseries_);
            Bind(statement, AIRTEMPERATURETIMESERIES_FIELD_ID, &airTemperatureTimeseries_);
            Bind(statement, WATERTEMPERATURETIMESERIES_FIELD_ID, &waterTemperatureTimeseries_);
            Bind(statement, RELATIVEHUMIDITYTIMESERIES_FIELD_ID, &relativeHumidityTimeseries_);
            Bind(statement, ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID, &absoluteHumidityTimeseries_);
            Bind(statement, DEWPOINTTIMESERIES_FIELD_ID, &dewPointTimeseries_);
            Bind(statement, WINDDIRECTIONTIMESERIES_FIELD_ID, &windDirectionTimeseries_);
            Bind(statement, WINDSPEEDTIMESERIES_FIELD_ID, &windSpeedTimeseries_);
            Bind(statement, GYRO_FIELD_ID, &gyro_);
        }

    };

    class FacilityColumnData : public ItemColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Guid type_;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double altitude_ = 0.0;
    public:
        using Base = ItemColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Type],[Longitude],[Latitude],[Altitude]";
        static constexpr std::wstring_view ViewName = L"FacilityView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT ALTITUDE_FIELD_ID = 7;

        FacilityColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Facility;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Altitude( ) const
        {
            return altitude_;
        }
        void SetAltitude( double altitude )
        {
            altitude_ = altitude;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, TYPE_FIELD_ID, &type_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, ALTITUDE_FIELD_ID, &altitude_);
        }

    };

    class TrackableItemColumnData : public ItemColumnData
    {
    public:
        using Base = ItemColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion]";
        static constexpr std::wstring_view ViewName = L"TrackableItemView";

        TrackableItemColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TrackableItem;
        }

    };

    class AircraftColumnData : public TrackableItemColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Guid type_;
    public:
        using Base = TrackableItemColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Type]";
        static constexpr std::wstring_view ViewName = L"AircraftView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 4;

        AircraftColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Aircraft;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, TYPE_FIELD_ID, &type_);
        }

    };

    class AisAidToNavigationColumnData : public TrackableItemColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Guid mMSI_;
        Data::NavigationalAidType navigationalAidType_ = Data::NavigationalAidType::NotSpecified;
        Guid position_;
        bool isVirtual_ = false;
        Int32 toBow_ = 0;
        Int32 toStern_ = 0;
        Int32 toPort_ = 0;
        Int32 toStarboard_ = 0;
        Guid offPositionTimeseries_;
    public:
        using Base = TrackableItemColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[MMSI],[NavigationalAidType],[Position],[IsVirtual],[ToBow],[ToStern],[ToPort],[ToStarboard],[OffPositionTimeseries]";
        static constexpr std::wstring_view ViewName = L"AisAidToNavigationView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT MMSI_FIELD_ID = 4;
        static constexpr SQLUSMALLINT NAVIGATIONALAIDTYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT POSITION_FIELD_ID = 6;
        static constexpr SQLUSMALLINT ISVIRTUAL_FIELD_ID = 7;
        static constexpr SQLUSMALLINT TOBOW_FIELD_ID = 8;
        static constexpr SQLUSMALLINT TOSTERN_FIELD_ID = 9;
        static constexpr SQLUSMALLINT TOPORT_FIELD_ID = 10;
        static constexpr SQLUSMALLINT TOSTARBOARD_FIELD_ID = 11;
        static constexpr SQLUSMALLINT OFFPOSITIONTIMESERIES_FIELD_ID = 12;

        AisAidToNavigationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisAidToNavigation;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Guid MMSI( ) const
        {
            return mMSI_;
        }
        void SetMMSI( const Guid& mMSI )
        {
            mMSI_ = mMSI;
        }
        Data::NavigationalAidType NavigationalAidType( ) const
        {
            return navigationalAidType_;
        }
        void SetNavigationalAidType( Data::NavigationalAidType navigationalAidType )
        {
            navigationalAidType_ = navigationalAidType;
        }
        Guid Position( ) const
        {
            return position_;
        }
        void SetPosition( const Guid& position )
        {
            position_ = position;
        }
        bool IsVirtual( ) const
        {
            return isVirtual_;
        }
        void SetIsVirtual( bool isVirtual )
        {
            isVirtual_ = isVirtual;
        }
        Int32 ToBow( ) const
        {
            return toBow_;
        }
        void SetToBow( Int32 toBow )
        {
            toBow_ = toBow;
        }
        Int32 ToStern( ) const
        {
            return toStern_;
        }
        void SetToStern( Int32 toStern )
        {
            toStern_ = toStern;
        }
        Int32 ToPort( ) const
        {
            return toPort_;
        }
        void SetToPort( Int32 toPort )
        {
            toPort_ = toPort;
        }
        Int32 ToStarboard( ) const
        {
            return toStarboard_;
        }
        void SetToStarboard( Int32 toStarboard )
        {
            toStarboard_ = toStarboard;
        }
        Guid OffPositionTimeseries( ) const
        {
            return offPositionTimeseries_;
        }
        void SetOffPositionTimeseries( const Guid& offPositionTimeseries )
        {
            offPositionTimeseries_ = offPositionTimeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, MMSI_FIELD_ID, &mMSI_);
            Bind(statement, NAVIGATIONALAIDTYPE_FIELD_ID, &navigationalAidType_);
            Bind(statement, POSITION_FIELD_ID, &position_);
            Bind(statement, ISVIRTUAL_FIELD_ID, &isVirtual_);
            Bind(statement, TOBOW_FIELD_ID, &toBow_);
            Bind(statement, TOSTERN_FIELD_ID, &toStern_);
            Bind(statement, TOPORT_FIELD_ID, &toPort_);
            Bind(statement, TOSTARBOARD_FIELD_ID, &toStarboard_);
            Bind(statement, OFFPOSITIONTIMESERIES_FIELD_ID, &offPositionTimeseries_);
        }

    };

    class VehicleColumnData : public TrackableItemColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Guid type_;
    public:
        using Base = TrackableItemColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Type]";
        static constexpr std::wstring_view ViewName = L"VehicleView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 4;

        VehicleColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Vehicle;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, TYPE_FIELD_ID, &type_);
        }

    };

    class VesselColumnData : public TrackableItemColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Guid type_;
        Int32 toBow_ = 0;
        Int32 toStern_ = 0;
        Int32 toPort_ = 0;
        Int32 toStarboard_ = 0;
        Guid draughtTimeseries_;
        Guid personsOnBoardTimeseries_;
    public:
        using Base = TrackableItemColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Type],[ToBow],[ToStern],[ToPort],[ToStarboard],[DraughtTimeseries],[PersonsOnBoardTimeseries]";
        static constexpr std::wstring_view ViewName = L"VesselView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TOBOW_FIELD_ID = 5;
        static constexpr SQLUSMALLINT TOSTERN_FIELD_ID = 6;
        static constexpr SQLUSMALLINT TOPORT_FIELD_ID = 7;
        static constexpr SQLUSMALLINT TOSTARBOARD_FIELD_ID = 8;
        static constexpr SQLUSMALLINT DRAUGHTTIMESERIES_FIELD_ID = 9;
        static constexpr SQLUSMALLINT PERSONSONBOARDTIMESERIES_FIELD_ID = 10;

        VesselColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Vessel;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Guid Type( ) const
        {
            return type_;
        }
        void SetType( const Guid& type )
        {
            type_ = type;
        }
        Int32 ToBow( ) const
        {
            return toBow_;
        }
        void SetToBow( Int32 toBow )
        {
            toBow_ = toBow;
        }
        Int32 ToStern( ) const
        {
            return toStern_;
        }
        void SetToStern( Int32 toStern )
        {
            toStern_ = toStern;
        }
        Int32 ToPort( ) const
        {
            return toPort_;
        }
        void SetToPort( Int32 toPort )
        {
            toPort_ = toPort;
        }
        Int32 ToStarboard( ) const
        {
            return toStarboard_;
        }
        void SetToStarboard( Int32 toStarboard )
        {
            toStarboard_ = toStarboard;
        }
        Guid DraughtTimeseries( ) const
        {
            return draughtTimeseries_;
        }
        void SetDraughtTimeseries( const Guid& draughtTimeseries )
        {
            draughtTimeseries_ = draughtTimeseries;
        }
        Guid PersonsOnBoardTimeseries( ) const
        {
            return personsOnBoardTimeseries_;
        }
        void SetPersonsOnBoardTimeseries( const Guid& personsOnBoardTimeseries )
        {
            personsOnBoardTimeseries_ = personsOnBoardTimeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, TYPE_FIELD_ID, &type_);
            Bind(statement, TOBOW_FIELD_ID, &toBow_);
            Bind(statement, TOSTERN_FIELD_ID, &toStern_);
            Bind(statement, TOPORT_FIELD_ID, &toPort_);
            Bind(statement, TOSTARBOARD_FIELD_ID, &toStarboard_);
            Bind(statement, DRAUGHTTIMESERIES_FIELD_ID, &draughtTimeseries_);
            Bind(statement, PERSONSONBOARDTIMESERIES_FIELD_ID, &personsOnBoardTimeseries_);
        }

    };

    class ItemIdentityLinkColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid item_;
        Guid identity_;
        DateTime start_;
        DateTime end_;
        SQLLEN endNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Item],[Identity],[Start],[End]";
        static constexpr std::wstring_view ViewName = L"ItemIdentityLinkView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ITEM_FIELD_ID = 3;
        static constexpr SQLUSMALLINT IDENTITY_FIELD_ID = 4;
        static constexpr SQLUSMALLINT START_FIELD_ID = 5;
        static constexpr SQLUSMALLINT END_FIELD_ID = 6;

        ItemIdentityLinkColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ItemIdentityLink;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Item( ) const
        {
            return item_;
        }
        void SetItem( const Guid& item )
        {
            item_ = item;
        }
        Guid Identity( ) const
        {
            return identity_;
        }
        void SetIdentity( const Guid& identity )
        {
            identity_ = identity;
        }
        DateTime Start( ) const
        {
            return start_;
        }
        void SetStart( const DateTime& start )
        {
            start_ = start;
        }
        DateTime End( ) const
        {
            return end_;
        }
        void SetEnd( const DateTime& end )
        {
            end_ = end;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ITEM_FIELD_ID, &item_);
            Bind(statement, IDENTITY_FIELD_ID, &identity_);
            Bind(statement, START_FIELD_ID, &start_);
            Bind(statement, END_FIELD_ID, &end_, &endNullIndicator_);
        }

    };

    class ItemParentChildLinkColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid parent_;
        Guid child_;
        DateTime timestamp_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Parent],[Child],[Timestamp]";
        static constexpr std::wstring_view ViewName = L"ItemParentChildLinkView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT PARENT_FIELD_ID = 3;
        static constexpr SQLUSMALLINT CHILD_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 5;

        ItemParentChildLinkColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ItemParentChildLink;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Parent( ) const
        {
            return parent_;
        }
        void SetParent( const Guid& parent )
        {
            parent_ = parent;
        }
        Guid Child( ) const
        {
            return child_;
        }
        void SetChild( const Guid& child )
        {
            child_ = child;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, PARENT_FIELD_ID, &parent_);
            Bind(statement, CHILD_FIELD_ID, &child_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
        }

    };

    class LineInputDeviceCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid lineInputDevice_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[LineInputDevice],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"LineInputDeviceCommandView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT LINEINPUTDEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REPLY_FIELD_ID = 7;

        LineInputDeviceCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LineInputDeviceCommand;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid LineInputDevice( ) const
        {
            return lineInputDevice_;
        }
        void SetLineInputDevice( const Guid& lineInputDevice )
        {
            lineInputDevice_ = lineInputDevice;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        void SetDeviceCommandSourceType( Data::DeviceCommandSourceType deviceCommandSourceType )
        {
            deviceCommandSourceType_ = deviceCommandSourceType;
        }
        Guid DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        void SetDeviceCommandSourceId( const Guid& deviceCommandSourceId )
        {
            deviceCommandSourceId_ = deviceCommandSourceId;
        }
        Guid Reply( ) const
        {
            return reply_;
        }
        void SetReply( const Guid& reply )
        {
            reply_ = reply;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, LINEINPUTDEVICE_FIELD_ID, &lineInputDevice_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEVICECOMMANDSOURCETYPE_FIELD_ID, &deviceCommandSourceType_);
            Bind(statement, DEVICECOMMANDSOURCEID_FIELD_ID, &deviceCommandSourceId_);
            Bind(statement, REPLY_FIELD_ID, &reply_);
        }

    };

    class LineInputDeviceCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid lineInputDevice_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[LineInputDevice],[Timestamp],[Command],[Status],[Message]";
        static constexpr std::wstring_view ViewName = L"LineInputDeviceCommandReplyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT LINEINPUTDEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COMMAND_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 7;

        LineInputDeviceCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LineInputDeviceCommandReply;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid LineInputDevice( ) const
        {
            return lineInputDevice_;
        }
        void SetLineInputDevice( const Guid& lineInputDevice )
        {
            lineInputDevice_ = lineInputDevice;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Command( ) const
        {
            return command_;
        }
        void SetCommand( const Guid& command )
        {
            command_ = command;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::DeviceCommandReplyStatus status )
        {
            status_ = status;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, LINEINPUTDEVICE_FIELD_ID, &lineInputDevice_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COMMAND_FIELD_ID, &command_);
            Bind(statement, STATUS_FIELD_ID, &status_);
        }

    };

    class LineInputDeviceConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid lineInputDevice_;
        DateTime timestamp_;
        bool storeReceivedSentences_ = false;
        bool storeSentMessages_ = false;
        bool storeUnsentMessages_ = false;
        bool nMEA_ = false;
        bool strictNMEA_ = false;
        Data::LineInputDeviceConnectionType connectionType_ = Data::LineInputDeviceConnectionType::Unknown;
        Int32 udpReceivePort_ = 0;
        std::array<wchar_t,101> udpSendHostname_ = {};
        SQLLEN udpSendHostnameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 udpSendPort_ = 0;
        std::array<wchar_t,101> tcpHostname_ = {};
        SQLLEN tcpHostnameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 tcpPort_ = 0;
        bool useHttpLogin_ = false;
        std::array<wchar_t,101> loginHostname_ = {};
        SQLLEN loginHostnameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 loginPort_ = 0;
        std::array<wchar_t,101> userName_ = {};
        SQLLEN userNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,101> password_ = {};
        SQLLEN passwordLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,101> comPort_ = {};
        SQLLEN comPortLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 baudRate_ = 0;
        Int32 dataBits_ = 0;
        bool discardNull_ = false;
        bool dtrEnable_ = false;
        Data::Handshake handshake_ = Data::Handshake::None;
        std::array<wchar_t,101> newLine_ = {};
        SQLLEN newLineLengthOrNullIndicator_ = SQL_NULL_DATA;
        Data::Parity parity_ = Data::Parity::None;
        Byte parityReplace_ = 0;
        Int32 readBufferSize_ = 0;
        TimeSpan readTimeout_;
        Int32 receivedBytesThreshold_ = 0;
        bool rtsEnable_ = false;
        Data::StopBits stopBits_ = Data::StopBits::None;
        Int32 writeBufferSize_ = 0;
        TimeSpan writeTimeout_;
        std::array<wchar_t,101> pairedComPort_ = {};
        SQLLEN pairedComPortLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[LineInputDevice],[Timestamp],[StoreReceivedSentences],[StoreSentMessages],[StoreUnsentMessages],[NMEA],[StrictNMEA],[ConnectionType],[UdpReceivePort],[UdpSendHostname],[UdpSendPort],[TcpHostname],[TcpPort],[UseHttpLogin],[LoginHostname],[LoginPort],[UserName],[Password],[ComPort],[BaudRate],[DataBits],[DiscardNull],[DtrEnable],[Handshake],[NewLine],[Parity],[ParityReplace],[ReadBufferSize],[ReadTimeout],[ReceivedBytesThreshold],[RtsEnable],[StopBits],[WriteBufferSize],[WriteTimeout],[PairedComPort]";
        static constexpr std::wstring_view ViewName = L"LineInputDeviceConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT LINEINPUTDEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT STORERECEIVEDSENTENCES_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STORESENTMESSAGES_FIELD_ID = 6;
        static constexpr SQLUSMALLINT STOREUNSENTMESSAGES_FIELD_ID = 7;
        static constexpr SQLUSMALLINT NMEA_FIELD_ID = 8;
        static constexpr SQLUSMALLINT STRICTNMEA_FIELD_ID = 9;
        static constexpr SQLUSMALLINT CONNECTIONTYPE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT UDPRECEIVEPORT_FIELD_ID = 11;
        static constexpr SQLUSMALLINT UDPSENDHOSTNAME_FIELD_ID = 12;
        static constexpr SQLUSMALLINT UDPSENDPORT_FIELD_ID = 13;
        static constexpr SQLUSMALLINT TCPHOSTNAME_FIELD_ID = 14;
        static constexpr SQLUSMALLINT TCPPORT_FIELD_ID = 15;
        static constexpr SQLUSMALLINT USEHTTPLOGIN_FIELD_ID = 16;
        static constexpr SQLUSMALLINT LOGINHOSTNAME_FIELD_ID = 17;
        static constexpr SQLUSMALLINT LOGINPORT_FIELD_ID = 18;
        static constexpr SQLUSMALLINT USERNAME_FIELD_ID = 19;
        static constexpr SQLUSMALLINT PASSWORD_FIELD_ID = 20;
        static constexpr SQLUSMALLINT COMPORT_FIELD_ID = 21;
        static constexpr SQLUSMALLINT BAUDRATE_FIELD_ID = 22;
        static constexpr SQLUSMALLINT DATABITS_FIELD_ID = 23;
        static constexpr SQLUSMALLINT DISCARDNULL_FIELD_ID = 24;
        static constexpr SQLUSMALLINT DTRENABLE_FIELD_ID = 25;
        static constexpr SQLUSMALLINT HANDSHAKE_FIELD_ID = 26;
        static constexpr SQLUSMALLINT NEWLINE_FIELD_ID = 27;
        static constexpr SQLUSMALLINT PARITY_FIELD_ID = 28;
        static constexpr SQLUSMALLINT PARITYREPLACE_FIELD_ID = 29;
        static constexpr SQLUSMALLINT READBUFFERSIZE_FIELD_ID = 30;
        static constexpr SQLUSMALLINT READTIMEOUT_FIELD_ID = 31;
        static constexpr SQLUSMALLINT RECEIVEDBYTESTHRESHOLD_FIELD_ID = 32;
        static constexpr SQLUSMALLINT RTSENABLE_FIELD_ID = 33;
        static constexpr SQLUSMALLINT STOPBITS_FIELD_ID = 34;
        static constexpr SQLUSMALLINT WRITEBUFFERSIZE_FIELD_ID = 35;
        static constexpr SQLUSMALLINT WRITETIMEOUT_FIELD_ID = 36;
        static constexpr SQLUSMALLINT PAIREDCOMPORT_FIELD_ID = 37;

        LineInputDeviceConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LineInputDeviceConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid LineInputDevice( ) const
        {
            return lineInputDevice_;
        }
        void SetLineInputDevice( const Guid& lineInputDevice )
        {
            lineInputDevice_ = lineInputDevice;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        bool StoreReceivedSentences( ) const
        {
            return storeReceivedSentences_;
        }
        void SetStoreReceivedSentences( bool storeReceivedSentences )
        {
            storeReceivedSentences_ = storeReceivedSentences;
        }
        bool StoreSentMessages( ) const
        {
            return storeSentMessages_;
        }
        void SetStoreSentMessages( bool storeSentMessages )
        {
            storeSentMessages_ = storeSentMessages;
        }
        bool StoreUnsentMessages( ) const
        {
            return storeUnsentMessages_;
        }
        void SetStoreUnsentMessages( bool storeUnsentMessages )
        {
            storeUnsentMessages_ = storeUnsentMessages;
        }
        bool NMEA( ) const
        {
            return nMEA_;
        }
        void SetNMEA( bool nMEA )
        {
            nMEA_ = nMEA;
        }
        bool StrictNMEA( ) const
        {
            return strictNMEA_;
        }
        void SetStrictNMEA( bool strictNMEA )
        {
            strictNMEA_ = strictNMEA;
        }
        Data::LineInputDeviceConnectionType ConnectionType( ) const
        {
            return connectionType_;
        }
        void SetConnectionType( Data::LineInputDeviceConnectionType connectionType )
        {
            connectionType_ = connectionType;
        }
        Int32 UdpReceivePort( ) const
        {
            return udpReceivePort_;
        }
        void SetUdpReceivePort( Int32 udpReceivePort )
        {
            udpReceivePort_ = udpReceivePort;
        }
        std::wstring_view UdpSendHostname( ) const
        {
            if(udpSendHostnameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(udpSendHostname_.data(),static_cast<size_t>( udpSendHostnameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetUdpSendHostname( const WideString& udpSendHostname )
        {
            Assign(udpSendHostname, udpSendHostname_, udpSendHostnameLengthOrNullIndicator_);
        }
        Int32 UdpSendPort( ) const
        {
            return udpSendPort_;
        }
        void SetUdpSendPort( Int32 udpSendPort )
        {
            udpSendPort_ = udpSendPort;
        }
        std::wstring_view TcpHostname( ) const
        {
            if(tcpHostnameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(tcpHostname_.data(),static_cast<size_t>( tcpHostnameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetTcpHostname( const WideString& tcpHostname )
        {
            Assign(tcpHostname, tcpHostname_, tcpHostnameLengthOrNullIndicator_);
        }
        Int32 TcpPort( ) const
        {
            return tcpPort_;
        }
        void SetTcpPort( Int32 tcpPort )
        {
            tcpPort_ = tcpPort;
        }
        bool UseHttpLogin( ) const
        {
            return useHttpLogin_;
        }
        void SetUseHttpLogin( bool useHttpLogin )
        {
            useHttpLogin_ = useHttpLogin;
        }
        std::wstring_view LoginHostname( ) const
        {
            if(loginHostnameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(loginHostname_.data(),static_cast<size_t>( loginHostnameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetLoginHostname( const WideString& loginHostname )
        {
            Assign(loginHostname, loginHostname_, loginHostnameLengthOrNullIndicator_);
        }
        Int32 LoginPort( ) const
        {
            return loginPort_;
        }
        void SetLoginPort( Int32 loginPort )
        {
            loginPort_ = loginPort;
        }
        std::wstring_view UserName( ) const
        {
            if(userNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(userName_.data(),static_cast<size_t>( userNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetUserName( const WideString& userName )
        {
            Assign(userName, userName_, userNameLengthOrNullIndicator_);
        }
        std::wstring_view Password( ) const
        {
            if(passwordLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(password_.data(),static_cast<size_t>( passwordLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPassword( const WideString& password )
        {
            Assign(password, password_, passwordLengthOrNullIndicator_);
        }
        std::wstring_view ComPort( ) const
        {
            if(comPortLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(comPort_.data(),static_cast<size_t>( comPortLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetComPort( const WideString& comPort )
        {
            Assign(comPort, comPort_, comPortLengthOrNullIndicator_);
        }
        Int32 BaudRate( ) const
        {
            return baudRate_;
        }
        void SetBaudRate( Int32 baudRate )
        {
            baudRate_ = baudRate;
        }
        Int32 DataBits( ) const
        {
            return dataBits_;
        }
        void SetDataBits( Int32 dataBits )
        {
            dataBits_ = dataBits;
        }
        bool DiscardNull( ) const
        {
            return discardNull_;
        }
        void SetDiscardNull( bool discardNull )
        {
            discardNull_ = discardNull;
        }
        bool DtrEnable( ) const
        {
            return dtrEnable_;
        }
        void SetDtrEnable( bool dtrEnable )
        {
            dtrEnable_ = dtrEnable;
        }
        Data::Handshake Handshake( ) const
        {
            return handshake_;
        }
        void SetHandshake( Data::Handshake handshake )
        {
            handshake_ = handshake;
        }
        std::wstring_view NewLine( ) const
        {
            if(newLineLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(newLine_.data(),static_cast<size_t>( newLineLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetNewLine( const WideString& newLine )
        {
            Assign(newLine, newLine_, newLineLengthOrNullIndicator_);
        }
        Data::Parity Parity( ) const
        {
            return parity_;
        }
        void SetParity( Data::Parity parity )
        {
            parity_ = parity;
        }
        Byte ParityReplace( ) const
        {
            return parityReplace_;
        }
        void SetParityReplace( Byte parityReplace )
        {
            parityReplace_ = parityReplace;
        }
        Int32 ReadBufferSize( ) const
        {
            return readBufferSize_;
        }
        void SetReadBufferSize( Int32 readBufferSize )
        {
            readBufferSize_ = readBufferSize;
        }
        TimeSpan ReadTimeout( ) const
        {
            return readTimeout_;
        }
        void SetReadTimeout( const TimeSpan& readTimeout )
        {
            readTimeout_ = readTimeout;
        }
        Int32 ReceivedBytesThreshold( ) const
        {
            return receivedBytesThreshold_;
        }
        void SetReceivedBytesThreshold( Int32 receivedBytesThreshold )
        {
            receivedBytesThreshold_ = receivedBytesThreshold;
        }
        bool RtsEnable( ) const
        {
            return rtsEnable_;
        }
        void SetRtsEnable( bool rtsEnable )
        {
            rtsEnable_ = rtsEnable;
        }
        Data::StopBits StopBits( ) const
        {
            return stopBits_;
        }
        void SetStopBits( Data::StopBits stopBits )
        {
            stopBits_ = stopBits;
        }
        Int32 WriteBufferSize( ) const
        {
            return writeBufferSize_;
        }
        void SetWriteBufferSize( Int32 writeBufferSize )
        {
            writeBufferSize_ = writeBufferSize;
        }
        TimeSpan WriteTimeout( ) const
        {
            return writeTimeout_;
        }
        void SetWriteTimeout( const TimeSpan& writeTimeout )
        {
            writeTimeout_ = writeTimeout;
        }
        std::wstring_view PairedComPort( ) const
        {
            if(pairedComPortLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pairedComPort_.data(),static_cast<size_t>( pairedComPortLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPairedComPort( const WideString& pairedComPort )
        {
            Assign(pairedComPort, pairedComPort_, pairedComPortLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, LINEINPUTDEVICE_FIELD_ID, &lineInputDevice_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, STORERECEIVEDSENTENCES_FIELD_ID, &storeReceivedSentences_);
            Bind(statement, STORESENTMESSAGES_FIELD_ID, &storeSentMessages_);
            Bind(statement, STOREUNSENTMESSAGES_FIELD_ID, &storeUnsentMessages_);
            Bind(statement, NMEA_FIELD_ID, &nMEA_);
            Bind(statement, STRICTNMEA_FIELD_ID, &strictNMEA_);
            Bind(statement, CONNECTIONTYPE_FIELD_ID, &connectionType_);
            Bind(statement, UDPRECEIVEPORT_FIELD_ID, &udpReceivePort_);
            Bind(statement, UDPSENDHOSTNAME_FIELD_ID, &udpSendHostname_, &udpSendHostnameLengthOrNullIndicator_);
            Bind(statement, UDPSENDPORT_FIELD_ID, &udpSendPort_);
            Bind(statement, TCPHOSTNAME_FIELD_ID, &tcpHostname_, &tcpHostnameLengthOrNullIndicator_);
            Bind(statement, TCPPORT_FIELD_ID, &tcpPort_);
            Bind(statement, USEHTTPLOGIN_FIELD_ID, &useHttpLogin_);
            Bind(statement, LOGINHOSTNAME_FIELD_ID, &loginHostname_, &loginHostnameLengthOrNullIndicator_);
            Bind(statement, LOGINPORT_FIELD_ID, &loginPort_);
            Bind(statement, USERNAME_FIELD_ID, &userName_, &userNameLengthOrNullIndicator_);
            Bind(statement, PASSWORD_FIELD_ID, &password_, &passwordLengthOrNullIndicator_);
            Bind(statement, COMPORT_FIELD_ID, &comPort_, &comPortLengthOrNullIndicator_);
            Bind(statement, BAUDRATE_FIELD_ID, &baudRate_);
            Bind(statement, DATABITS_FIELD_ID, &dataBits_);
            Bind(statement, DISCARDNULL_FIELD_ID, &discardNull_);
            Bind(statement, DTRENABLE_FIELD_ID, &dtrEnable_);
            Bind(statement, HANDSHAKE_FIELD_ID, &handshake_);
            Bind(statement, NEWLINE_FIELD_ID, &newLine_, &newLineLengthOrNullIndicator_);
            Bind(statement, PARITY_FIELD_ID, &parity_);
            Bind(statement, PARITYREPLACE_FIELD_ID, &parityReplace_);
            Bind(statement, READBUFFERSIZE_FIELD_ID, &readBufferSize_);
            Bind(statement, READTIMEOUT_FIELD_ID, &readTimeout_);
            Bind(statement, RECEIVEDBYTESTHRESHOLD_FIELD_ID, &receivedBytesThreshold_);
            Bind(statement, RTSENABLE_FIELD_ID, &rtsEnable_);
            Bind(statement, STOPBITS_FIELD_ID, &stopBits_);
            Bind(statement, WRITEBUFFERSIZE_FIELD_ID, &writeBufferSize_);
            Bind(statement, WRITETIMEOUT_FIELD_ID, &writeTimeout_);
            Bind(statement, PAIREDCOMPORT_FIELD_ID, &pairedComPort_, &pairedComPortLengthOrNullIndicator_);
        }

    };

    class LineInputMessageRoutingColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid lineInputDevice_;
        std::array<wchar_t,101> type_ = {};
        SQLLEN typeLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[LineInputDevice],[Type]";
        static constexpr std::wstring_view ViewName = L"LineInputMessageRoutingView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT LINEINPUTDEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 4;

        LineInputMessageRoutingColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LineInputMessageRouting;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid LineInputDevice( ) const
        {
            return lineInputDevice_;
        }
        void SetLineInputDevice( const Guid& lineInputDevice )
        {
            lineInputDevice_ = lineInputDevice;
        }
        std::wstring_view Type( ) const
        {
            if(typeLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(type_.data(),static_cast<size_t>( typeLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetType( const WideString& type )
        {
            Assign(type, type_, typeLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, LINEINPUTDEVICE_FIELD_ID, &lineInputDevice_);
            Bind(statement, TYPE_FIELD_ID, &type_, &typeLengthOrNullIndicator_);
        }

    };

    class LineInputMessageRoutingDestinationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid routing_;
        Guid listener_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Routing],[Listener]";
        static constexpr std::wstring_view ViewName = L"LineInputMessageRoutingDestinationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ROUTING_FIELD_ID = 3;
        static constexpr SQLUSMALLINT LISTENER_FIELD_ID = 4;

        LineInputMessageRoutingDestinationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LineInputMessageRoutingDestination;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Routing( ) const
        {
            return routing_;
        }
        void SetRouting( const Guid& routing )
        {
            routing_ = routing;
        }
        Guid Listener( ) const
        {
            return listener_;
        }
        void SetListener( const Guid& listener )
        {
            listener_ = listener;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ROUTING_FIELD_ID, &routing_);
            Bind(statement, LISTENER_FIELD_ID, &listener_);
        }

    };

    class LineInputWhiteListEntryColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid lineInputDevice_;
        std::array<wchar_t,129> hostName_ = {};
        SQLLEN hostNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 port_ = 0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[LineInputDevice],[HostName],[Port]";
        static constexpr std::wstring_view ViewName = L"LineInputWhiteListEntryView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT LINEINPUTDEVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT HOSTNAME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT PORT_FIELD_ID = 5;

        LineInputWhiteListEntryColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LineInputWhiteListEntry;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid LineInputDevice( ) const
        {
            return lineInputDevice_;
        }
        void SetLineInputDevice( const Guid& lineInputDevice )
        {
            lineInputDevice_ = lineInputDevice;
        }
        std::wstring_view HostName( ) const
        {
            if(hostNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(hostName_.data(),static_cast<size_t>( hostNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetHostName( const WideString& hostName )
        {
            Assign(hostName, hostName_, hostNameLengthOrNullIndicator_);
        }
        Int32 Port( ) const
        {
            return port_;
        }
        void SetPort( Int32 port )
        {
            port_ = port;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, LINEINPUTDEVICE_FIELD_ID, &lineInputDevice_);
            Bind(statement, HOSTNAME_FIELD_ID, &hostName_, &hostNameLengthOrNullIndicator_);
            Bind(statement, PORT_FIELD_ID, &port_);
        }

    };

    class LogApplicationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString description_;
        SQLLEN descriptionLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"LogApplicationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT DESCRIPTION_FIELD_ID = 4;

        LogApplicationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LogApplication;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        void SetDescription( const WideString& description )
        {
            Assign(description, description_, descriptionLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class LogApplicationConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid application_;
        DateTime timestamp_;
        bool finest_ = false;
        bool finer_ = false;
        bool fine_ = false;
        bool info_ = false;
        bool notice_ = false;
        bool warn_ = false;
        bool error_ = false;
        bool severe_ = false;
        bool critical_ = false;
        bool alert_ = false;
        bool fatal_ = false;
        bool emergency_ = false;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Application],[Timestamp],[Finest],[Finer],[Fine],[Info],[Notice],[Warn],[Error],[Severe],[Critical],[Alert],[Fatal],[Emergency]";
        static constexpr std::wstring_view ViewName = L"LogApplicationConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT APPLICATION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT FINEST_FIELD_ID = 5;
        static constexpr SQLUSMALLINT FINER_FIELD_ID = 6;
        static constexpr SQLUSMALLINT FINE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT INFO_FIELD_ID = 8;
        static constexpr SQLUSMALLINT NOTICE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT WARN_FIELD_ID = 10;
        static constexpr SQLUSMALLINT ERROR_FIELD_ID = 11;
        static constexpr SQLUSMALLINT SEVERE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT CRITICAL_FIELD_ID = 13;
        static constexpr SQLUSMALLINT ALERT_FIELD_ID = 14;
        static constexpr SQLUSMALLINT FATAL_FIELD_ID = 15;
        static constexpr SQLUSMALLINT EMERGENCY_FIELD_ID = 16;

        LogApplicationConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LogApplicationConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Application( ) const
        {
            return application_;
        }
        void SetApplication( const Guid& application )
        {
            application_ = application;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        bool Finest( ) const
        {
            return finest_;
        }
        void SetFinest( bool finest )
        {
            finest_ = finest;
        }
        bool Finer( ) const
        {
            return finer_;
        }
        void SetFiner( bool finer )
        {
            finer_ = finer;
        }
        bool Fine( ) const
        {
            return fine_;
        }
        void SetFine( bool fine )
        {
            fine_ = fine;
        }
        bool Info( ) const
        {
            return info_;
        }
        void SetInfo( bool info )
        {
            info_ = info;
        }
        bool Notice( ) const
        {
            return notice_;
        }
        void SetNotice( bool notice )
        {
            notice_ = notice;
        }
        bool Warn( ) const
        {
            return warn_;
        }
        void SetWarn( bool warn )
        {
            warn_ = warn;
        }
        bool Error( ) const
        {
            return error_;
        }
        void SetError( bool error )
        {
            error_ = error;
        }
        bool Severe( ) const
        {
            return severe_;
        }
        void SetSevere( bool severe )
        {
            severe_ = severe;
        }
        bool Critical( ) const
        {
            return critical_;
        }
        void SetCritical( bool critical )
        {
            critical_ = critical;
        }
        bool Alert( ) const
        {
            return alert_;
        }
        void SetAlert( bool alert )
        {
            alert_ = alert;
        }
        bool Fatal( ) const
        {
            return fatal_;
        }
        void SetFatal( bool fatal )
        {
            fatal_ = fatal;
        }
        bool Emergency( ) const
        {
            return emergency_;
        }
        void SetEmergency( bool emergency )
        {
            emergency_ = emergency;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, APPLICATION_FIELD_ID, &application_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, FINEST_FIELD_ID, &finest_);
            Bind(statement, FINER_FIELD_ID, &finer_);
            Bind(statement, FINE_FIELD_ID, &fine_);
            Bind(statement, INFO_FIELD_ID, &info_);
            Bind(statement, NOTICE_FIELD_ID, &notice_);
            Bind(statement, WARN_FIELD_ID, &warn_);
            Bind(statement, ERROR_FIELD_ID, &error_);
            Bind(statement, SEVERE_FIELD_ID, &severe_);
            Bind(statement, CRITICAL_FIELD_ID, &critical_);
            Bind(statement, ALERT_FIELD_ID, &alert_);
            Bind(statement, FATAL_FIELD_ID, &fatal_);
            Bind(statement, EMERGENCY_FIELD_ID, &emergency_);
        }

    };

    class LogHostColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> computerName_ = {};
        SQLLEN computerNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString description_;
        SQLLEN descriptionLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ComputerName],[Description]";
        static constexpr std::wstring_view ViewName = L"LogHostView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT COMPUTERNAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT DESCRIPTION_FIELD_ID = 4;

        LogHostColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LogHost;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view ComputerName( ) const
        {
            if(computerNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(computerName_.data(),static_cast<size_t>( computerNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetComputerName( const WideString& computerName )
        {
            Assign(computerName, computerName_, computerNameLengthOrNullIndicator_);
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        void SetDescription( const WideString& description )
        {
            Assign(description, description_, descriptionLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, COMPUTERNAME_FIELD_ID, &computerName_, &computerNameLengthOrNullIndicator_);
        }

    };

    class LogHostConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid host_;
        DateTime timestamp_;
        bool finest_ = false;
        bool finer_ = false;
        bool fine_ = false;
        bool info_ = false;
        bool notice_ = false;
        bool warn_ = false;
        bool error_ = false;
        bool severe_ = false;
        bool critical_ = false;
        bool alert_ = false;
        bool fatal_ = false;
        bool emergency_ = false;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Host],[Timestamp],[Finest],[Finer],[Fine],[Info],[Notice],[Warn],[Error],[Severe],[Critical],[Alert],[Fatal],[Emergency]";
        static constexpr std::wstring_view ViewName = L"LogHostConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT HOST_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT FINEST_FIELD_ID = 5;
        static constexpr SQLUSMALLINT FINER_FIELD_ID = 6;
        static constexpr SQLUSMALLINT FINE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT INFO_FIELD_ID = 8;
        static constexpr SQLUSMALLINT NOTICE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT WARN_FIELD_ID = 10;
        static constexpr SQLUSMALLINT ERROR_FIELD_ID = 11;
        static constexpr SQLUSMALLINT SEVERE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT CRITICAL_FIELD_ID = 13;
        static constexpr SQLUSMALLINT ALERT_FIELD_ID = 14;
        static constexpr SQLUSMALLINT FATAL_FIELD_ID = 15;
        static constexpr SQLUSMALLINT EMERGENCY_FIELD_ID = 16;

        LogHostConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LogHostConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Host( ) const
        {
            return host_;
        }
        void SetHost( const Guid& host )
        {
            host_ = host;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        bool Finest( ) const
        {
            return finest_;
        }
        void SetFinest( bool finest )
        {
            finest_ = finest;
        }
        bool Finer( ) const
        {
            return finer_;
        }
        void SetFiner( bool finer )
        {
            finer_ = finer;
        }
        bool Fine( ) const
        {
            return fine_;
        }
        void SetFine( bool fine )
        {
            fine_ = fine;
        }
        bool Info( ) const
        {
            return info_;
        }
        void SetInfo( bool info )
        {
            info_ = info;
        }
        bool Notice( ) const
        {
            return notice_;
        }
        void SetNotice( bool notice )
        {
            notice_ = notice;
        }
        bool Warn( ) const
        {
            return warn_;
        }
        void SetWarn( bool warn )
        {
            warn_ = warn;
        }
        bool Error( ) const
        {
            return error_;
        }
        void SetError( bool error )
        {
            error_ = error;
        }
        bool Severe( ) const
        {
            return severe_;
        }
        void SetSevere( bool severe )
        {
            severe_ = severe;
        }
        bool Critical( ) const
        {
            return critical_;
        }
        void SetCritical( bool critical )
        {
            critical_ = critical;
        }
        bool Alert( ) const
        {
            return alert_;
        }
        void SetAlert( bool alert )
        {
            alert_ = alert;
        }
        bool Fatal( ) const
        {
            return fatal_;
        }
        void SetFatal( bool fatal )
        {
            fatal_ = fatal;
        }
        bool Emergency( ) const
        {
            return emergency_;
        }
        void SetEmergency( bool emergency )
        {
            emergency_ = emergency;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, HOST_FIELD_ID, &host_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, FINEST_FIELD_ID, &finest_);
            Bind(statement, FINER_FIELD_ID, &finer_);
            Bind(statement, FINE_FIELD_ID, &fine_);
            Bind(statement, INFO_FIELD_ID, &info_);
            Bind(statement, NOTICE_FIELD_ID, &notice_);
            Bind(statement, WARN_FIELD_ID, &warn_);
            Bind(statement, ERROR_FIELD_ID, &error_);
            Bind(statement, SEVERE_FIELD_ID, &severe_);
            Bind(statement, CRITICAL_FIELD_ID, &critical_);
            Bind(statement, ALERT_FIELD_ID, &alert_);
            Bind(statement, FATAL_FIELD_ID, &fatal_);
            Bind(statement, EMERGENCY_FIELD_ID, &emergency_);
        }

    };

    class LogLocationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,261> fileName_ = {};
        SQLLEN fileNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 lineNumber_ = 0;
        WideString namespace_;
        SQLLEN namespaceLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString className_;
        SQLLEN classNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,256> methodName_ = {};
        SQLLEN methodNameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[FileName],[LineNumber],[MethodName],[Namespace],[ClassName]";
        static constexpr std::wstring_view ViewName = L"LogLocationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT FILENAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT LINENUMBER_FIELD_ID = 4;
        static constexpr SQLUSMALLINT METHODNAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT NAMESPACE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT CLASSNAME_FIELD_ID = 7;

        LogLocationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LogLocation;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view FileName( ) const
        {
            if(fileNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(fileName_.data(),static_cast<size_t>( fileNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetFileName( const WideString& fileName )
        {
            Assign(fileName, fileName_, fileNameLengthOrNullIndicator_);
        }
        Int32 LineNumber( ) const
        {
            return lineNumber_;
        }
        void SetLineNumber( Int32 lineNumber )
        {
            lineNumber_ = lineNumber;
        }
        const WideString& Namespace( ) const
        {
            return namespace_;
        }
        void SetNamespace( const WideString& namespace__ )
        {
            Assign(namespace__, namespace_, namespaceLengthOrNullIndicator_);
        }
        const WideString& ClassName( ) const
        {
            return className_;
        }
        void SetClassName( const WideString& className )
        {
            Assign(className, className_, classNameLengthOrNullIndicator_);
        }
        std::wstring_view MethodName( ) const
        {
            if(methodNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(methodName_.data(),static_cast<size_t>( methodNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetMethodName( const WideString& methodName )
        {
            Assign(methodName, methodName_, methodNameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, FILENAME_FIELD_ID, &fileName_, &fileNameLengthOrNullIndicator_);
            Bind(statement, LINENUMBER_FIELD_ID, &lineNumber_);
            Bind(statement, METHODNAME_FIELD_ID, &methodName_, &methodNameLengthOrNullIndicator_);
        }

    };

    class LogProcessColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid application_;
        Guid host_;
        DateTime started_;
        DateTime stopped_;
        SQLLEN stoppedNullIndicator_ = SQL_NULL_DATA;
        Int64 processId_ = 0;
        WideString path_;
        SQLLEN pathLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,128> identity_ = {};
        SQLLEN identityLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Application],[Host],[Started],[Stopped],[ProcessId],[Identity],[Path]";
        static constexpr std::wstring_view ViewName = L"LogProcessView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT APPLICATION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT HOST_FIELD_ID = 4;
        static constexpr SQLUSMALLINT STARTED_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STOPPED_FIELD_ID = 6;
        static constexpr SQLUSMALLINT PROCESSID_FIELD_ID = 7;
        static constexpr SQLUSMALLINT IDENTITY_FIELD_ID = 8;
        static constexpr SQLUSMALLINT PATH_FIELD_ID = 9;

        LogProcessColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LogProcess;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Application( ) const
        {
            return application_;
        }
        void SetApplication( const Guid& application )
        {
            application_ = application;
        }
        Guid Host( ) const
        {
            return host_;
        }
        void SetHost( const Guid& host )
        {
            host_ = host;
        }
        DateTime Started( ) const
        {
            return started_;
        }
        void SetStarted( const DateTime& started )
        {
            started_ = started;
        }
        DateTime Stopped( ) const
        {
            return stopped_;
        }
        void SetStopped( const DateTime& stopped )
        {
            stopped_ = stopped;
        }
        Int64 ProcessId( ) const
        {
            return processId_;
        }
        void SetProcessId( Int64 processId )
        {
            processId_ = processId;
        }
        const WideString& Path( ) const
        {
            return path_;
        }
        void SetPath( const WideString& path )
        {
            Assign(path, path_, pathLengthOrNullIndicator_);
        }
        std::wstring_view Identity( ) const
        {
            if(identityLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(identity_.data(),static_cast<size_t>( identityLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetIdentity( const WideString& identity )
        {
            Assign(identity, identity_, identityLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, APPLICATION_FIELD_ID, &application_);
            Bind(statement, HOST_FIELD_ID, &host_);
            Bind(statement, STARTED_FIELD_ID, &started_);
            Bind(statement, STOPPED_FIELD_ID, &stopped_, &stoppedNullIndicator_);
            Bind(statement, PROCESSID_FIELD_ID, &processId_);
            Bind(statement, IDENTITY_FIELD_ID, &identity_, &identityLengthOrNullIndicator_);
        }

    };

    class LogRecordColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid thread_;
        Int64 sequenceNumber_ = 0;
        Data::LogLevel level_ = Data::LogLevel::Unknown;
        DateTime timestamp_;
        Int32 depth_ = 0;
        Guid location_;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString exceptionString_;
        SQLLEN exceptionStringLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::vector<Byte> propertiesData_;
        SQLLEN propertiesDataLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Thread],[SequenceNumber],[Level],[Timestamp],[Depth],[Location],[Message],[ExceptionString],[PropertiesData]";
        static constexpr std::wstring_view ViewName = L"LogRecordView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT THREAD_FIELD_ID = 3;
        static constexpr SQLUSMALLINT SEQUENCENUMBER_FIELD_ID = 4;
        static constexpr SQLUSMALLINT LEVEL_FIELD_ID = 5;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 6;
        static constexpr SQLUSMALLINT DEPTH_FIELD_ID = 7;
        static constexpr SQLUSMALLINT LOCATION_FIELD_ID = 8;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT EXCEPTIONSTRING_FIELD_ID = 10;
        static constexpr SQLUSMALLINT PROPERTIESDATA_FIELD_ID = 11;

        LogRecordColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LogRecord;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Thread( ) const
        {
            return thread_;
        }
        void SetThread( const Guid& thread )
        {
            thread_ = thread;
        }
        Int64 SequenceNumber( ) const
        {
            return sequenceNumber_;
        }
        void SetSequenceNumber( Int64 sequenceNumber )
        {
            sequenceNumber_ = sequenceNumber;
        }
        Data::LogLevel Level( ) const
        {
            return level_;
        }
        void SetLevel( Data::LogLevel level )
        {
            level_ = level;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Int32 Depth( ) const
        {
            return depth_;
        }
        void SetDepth( Int32 depth )
        {
            depth_ = depth;
        }
        Guid Location( ) const
        {
            return location_;
        }
        void SetLocation( const Guid& location )
        {
            location_ = location;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        const WideString& ExceptionString( ) const
        {
            return exceptionString_;
        }
        void SetExceptionString( const WideString& exceptionString )
        {
            Assign(exceptionString, exceptionString_, exceptionStringLengthOrNullIndicator_);
        }
        const std::vector<Byte>& PropertiesData( ) const
        {
            return propertiesData_;
        }
        void SetPropertiesData( const std::vector<Byte>& propertiesData )
        {
            Assign(propertiesData, propertiesData_, propertiesDataLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, THREAD_FIELD_ID, &thread_);
            Bind(statement, SEQUENCENUMBER_FIELD_ID, &sequenceNumber_);
            Bind(statement, LEVEL_FIELD_ID, &level_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEPTH_FIELD_ID, &depth_);
            Bind(statement, LOCATION_FIELD_ID, &location_);
        }

    };

    class LogThreadColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid process_;
        DateTime started_;
        DateTime stopped_;
        SQLLEN stoppedNullIndicator_ = SQL_NULL_DATA;
        Int64 threadId_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Process],[Started],[Stopped],[ThreadId],[Name]";
        static constexpr std::wstring_view ViewName = L"LogThreadView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT PROCESS_FIELD_ID = 3;
        static constexpr SQLUSMALLINT STARTED_FIELD_ID = 4;
        static constexpr SQLUSMALLINT STOPPED_FIELD_ID = 5;
        static constexpr SQLUSMALLINT THREADID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 7;

        LogThreadColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LogThread;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Process( ) const
        {
            return process_;
        }
        void SetProcess( const Guid& process )
        {
            process_ = process;
        }
        DateTime Started( ) const
        {
            return started_;
        }
        void SetStarted( const DateTime& started )
        {
            started_ = started;
        }
        DateTime Stopped( ) const
        {
            return stopped_;
        }
        void SetStopped( const DateTime& stopped )
        {
            stopped_ = stopped;
        }
        Int64 ThreadId( ) const
        {
            return threadId_;
        }
        void SetThreadId( Int64 threadId )
        {
            threadId_ = threadId;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, PROCESS_FIELD_ID, &process_);
            Bind(statement, STARTED_FIELD_ID, &started_);
            Bind(statement, STOPPED_FIELD_ID, &stopped_, &stoppedNullIndicator_);
            Bind(statement, THREADID_FIELD_ID, &threadId_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class LogTraceEntryColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid thread_;
        Int64 sequenceNumber_ = 0;
        Guid location_;
        Int32 depth_ = 0;
        DateTime entered_;
        DateTime ended_;
        SQLLEN endedNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Thread],[SequenceNumber],[Location],[Depth],[Entered],[Ended]";
        static constexpr std::wstring_view ViewName = L"LogTraceEntryView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT THREAD_FIELD_ID = 3;
        static constexpr SQLUSMALLINT SEQUENCENUMBER_FIELD_ID = 4;
        static constexpr SQLUSMALLINT LOCATION_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEPTH_FIELD_ID = 6;
        static constexpr SQLUSMALLINT ENTERED_FIELD_ID = 7;
        static constexpr SQLUSMALLINT ENDED_FIELD_ID = 8;

        LogTraceEntryColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::LogTraceEntry;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Thread( ) const
        {
            return thread_;
        }
        void SetThread( const Guid& thread )
        {
            thread_ = thread;
        }
        Int64 SequenceNumber( ) const
        {
            return sequenceNumber_;
        }
        void SetSequenceNumber( Int64 sequenceNumber )
        {
            sequenceNumber_ = sequenceNumber;
        }
        Guid Location( ) const
        {
            return location_;
        }
        void SetLocation( const Guid& location )
        {
            location_ = location;
        }
        Int32 Depth( ) const
        {
            return depth_;
        }
        void SetDepth( Int32 depth )
        {
            depth_ = depth;
        }
        DateTime Entered( ) const
        {
            return entered_;
        }
        void SetEntered( const DateTime& entered )
        {
            entered_ = entered;
        }
        DateTime Ended( ) const
        {
            return ended_;
        }
        void SetEnded( const DateTime& ended )
        {
            ended_ = ended;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, THREAD_FIELD_ID, &thread_);
            Bind(statement, SEQUENCENUMBER_FIELD_ID, &sequenceNumber_);
            Bind(statement, LOCATION_FIELD_ID, &location_);
            Bind(statement, DEPTH_FIELD_ID, &depth_);
            Bind(statement, ENTERED_FIELD_ID, &entered_);
            Bind(statement, ENDED_FIELD_ID, &ended_, &endedNullIndicator_);
        }

    };

    class MapElementColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid item_;
        Data::MapElementType elementType_ = Data::MapElementType::Unknown;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double angle_ = 0.0;
        double left_ = 0.0;
        double top_ = 0.0;
        double width_ = 0.0;
        double height_ = 0.0;
        std::array<wchar_t,101> label_ = {};
        SQLLEN labelLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::vector<Byte> data_;
        SQLLEN dataLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Item],[ElementType],[Latitude],[Longitude],[Angle],[Left],[Top],[Width],[Height],[Label],[Data]";
        static constexpr std::wstring_view ViewName = L"MapElementView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ITEM_FIELD_ID = 3;
        static constexpr SQLUSMALLINT ELEMENTTYPE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT ANGLE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT LEFT_FIELD_ID = 8;
        static constexpr SQLUSMALLINT TOP_FIELD_ID = 9;
        static constexpr SQLUSMALLINT WIDTH_FIELD_ID = 10;
        static constexpr SQLUSMALLINT HEIGHT_FIELD_ID = 11;
        static constexpr SQLUSMALLINT LABEL_FIELD_ID = 12;
        static constexpr SQLUSMALLINT DATA_FIELD_ID = 13;

        MapElementColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MapElement;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Item( ) const
        {
            return item_;
        }
        void SetItem( const Guid& item )
        {
            item_ = item;
        }
        Data::MapElementType ElementType( ) const
        {
            return elementType_;
        }
        void SetElementType( Data::MapElementType elementType )
        {
            elementType_ = elementType;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Angle( ) const
        {
            return angle_;
        }
        void SetAngle( double angle )
        {
            angle_ = angle;
        }
        double Left( ) const
        {
            return left_;
        }
        void SetLeft( double left )
        {
            left_ = left;
        }
        double Top( ) const
        {
            return top_;
        }
        void SetTop( double top )
        {
            top_ = top;
        }
        double Width( ) const
        {
            return width_;
        }
        void SetWidth( double width )
        {
            width_ = width;
        }
        double Height( ) const
        {
            return height_;
        }
        void SetHeight( double height )
        {
            height_ = height;
        }
        std::wstring_view Label( ) const
        {
            if(labelLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(label_.data(),static_cast<size_t>( labelLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetLabel( const WideString& label )
        {
            Assign(label, label_, labelLengthOrNullIndicator_);
        }
        const std::vector<Byte>& Data( ) const
        {
            return data_;
        }
        void SetData( const std::vector<Byte>& data )
        {
            Assign(data, data_, dataLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ITEM_FIELD_ID, &item_);
            Bind(statement, ELEMENTTYPE_FIELD_ID, &elementType_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, ANGLE_FIELD_ID, &angle_);
            Bind(statement, LEFT_FIELD_ID, &left_);
            Bind(statement, TOP_FIELD_ID, &top_);
            Bind(statement, WIDTH_FIELD_ID, &width_);
            Bind(statement, HEIGHT_FIELD_ID, &height_);
            Bind(statement, LABEL_FIELD_ID, &label_, &labelLengthOrNullIndicator_);
        }

    };

    class MapInfoColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Int32 scale_ = 0;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double northWestLatitude_ = 0.0;
        double northWestLongitude_ = 0.0;
        double southEastLatitude_ = 0.0;
        double southEastLongitude_ = 0.0;
        std::vector<Byte> image_;
        SQLLEN imageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Scale],[Latitude],[Longitude],[NorthWestLatitude],[NorthWestLongitude],[SouthEastLatitude],[SouthEastLongitude],[Image]";
        static constexpr std::wstring_view ViewName = L"MapInfoView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT SCALE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT NORTHWESTLATITUDE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT NORTHWESTLONGITUDE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT SOUTHEASTLATITUDE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SOUTHEASTLONGITUDE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT IMAGE_FIELD_ID = 10;

        MapInfoColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MapInfo;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Int32 Scale( ) const
        {
            return scale_;
        }
        void SetScale( Int32 scale )
        {
            scale_ = scale;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double NorthWestLatitude( ) const
        {
            return northWestLatitude_;
        }
        void SetNorthWestLatitude( double northWestLatitude )
        {
            northWestLatitude_ = northWestLatitude;
        }
        double NorthWestLongitude( ) const
        {
            return northWestLongitude_;
        }
        void SetNorthWestLongitude( double northWestLongitude )
        {
            northWestLongitude_ = northWestLongitude;
        }
        double SouthEastLatitude( ) const
        {
            return southEastLatitude_;
        }
        void SetSouthEastLatitude( double southEastLatitude )
        {
            southEastLatitude_ = southEastLatitude;
        }
        double SouthEastLongitude( ) const
        {
            return southEastLongitude_;
        }
        void SetSouthEastLongitude( double southEastLongitude )
        {
            southEastLongitude_ = southEastLongitude;
        }
        const std::vector<Byte>& Image( ) const
        {
            return image_;
        }
        void SetImage( const std::vector<Byte>& image )
        {
            Assign(image, image_, imageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, SCALE_FIELD_ID, &scale_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, NORTHWESTLATITUDE_FIELD_ID, &northWestLatitude_);
            Bind(statement, NORTHWESTLONGITUDE_FIELD_ID, &northWestLongitude_);
            Bind(statement, SOUTHEASTLATITUDE_FIELD_ID, &southEastLatitude_);
            Bind(statement, SOUTHEASTLONGITUDE_FIELD_ID, &southEastLongitude_);
        }

    };

    class MapServiceOptionsColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        DateTime timestamp_;
        std::array<wchar_t,128> ipAddress_ = {};
        SQLLEN ipAddressLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 port_ = 0;
        double imageScaleFactorX_ = 0.0;
        double imageOffsetX_ = 0.0;
        double imageScaleFactorY_ = 0.0;
        double imageOffsetY_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timestamp],[IpAddress],[Port],[ImageScaleFactorX],[ImageOffsetX],[ImageScaleFactorY],[ImageOffsetY]";
        static constexpr std::wstring_view ViewName = L"MapServiceOptionsView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 3;
        static constexpr SQLUSMALLINT IPADDRESS_FIELD_ID = 4;
        static constexpr SQLUSMALLINT PORT_FIELD_ID = 5;
        static constexpr SQLUSMALLINT IMAGESCALEFACTORX_FIELD_ID = 6;
        static constexpr SQLUSMALLINT IMAGEOFFSETX_FIELD_ID = 7;
        static constexpr SQLUSMALLINT IMAGESCALEFACTORY_FIELD_ID = 8;
        static constexpr SQLUSMALLINT IMAGEOFFSETY_FIELD_ID = 9;

        MapServiceOptionsColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MapServiceOptions;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        std::wstring_view IpAddress( ) const
        {
            if(ipAddressLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(ipAddress_.data(),static_cast<size_t>( ipAddressLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetIpAddress( const WideString& ipAddress )
        {
            Assign(ipAddress, ipAddress_, ipAddressLengthOrNullIndicator_);
        }
        Int32 Port( ) const
        {
            return port_;
        }
        void SetPort( Int32 port )
        {
            port_ = port;
        }
        double ImageScaleFactorX( ) const
        {
            return imageScaleFactorX_;
        }
        void SetImageScaleFactorX( double imageScaleFactorX )
        {
            imageScaleFactorX_ = imageScaleFactorX;
        }
        double ImageOffsetX( ) const
        {
            return imageOffsetX_;
        }
        void SetImageOffsetX( double imageOffsetX )
        {
            imageOffsetX_ = imageOffsetX;
        }
        double ImageScaleFactorY( ) const
        {
            return imageScaleFactorY_;
        }
        void SetImageScaleFactorY( double imageScaleFactorY )
        {
            imageScaleFactorY_ = imageScaleFactorY;
        }
        double ImageOffsetY( ) const
        {
            return imageOffsetY_;
        }
        void SetImageOffsetY( double imageOffsetY )
        {
            imageOffsetY_ = imageOffsetY;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, IPADDRESS_FIELD_ID, &ipAddress_, &ipAddressLengthOrNullIndicator_);
            Bind(statement, PORT_FIELD_ID, &port_);
            Bind(statement, IMAGESCALEFACTORX_FIELD_ID, &imageScaleFactorX_);
            Bind(statement, IMAGEOFFSETX_FIELD_ID, &imageOffsetX_);
            Bind(statement, IMAGESCALEFACTORY_FIELD_ID, &imageScaleFactorY_);
            Bind(statement, IMAGEOFFSETY_FIELD_ID, &imageOffsetY_);
        }

    };

    class MaritimeIdentificationDigitsColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Int32 code_ = 0;
        Guid country_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Code],[Country]";
        static constexpr std::wstring_view ViewName = L"MaritimeIdentificationDigitsView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CODE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT COUNTRY_FIELD_ID = 4;

        MaritimeIdentificationDigitsColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MaritimeIdentificationDigits;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Int32 Code( ) const
        {
            return code_;
        }
        void SetCode( Int32 code )
        {
            code_ = code;
        }
        Guid Country( ) const
        {
            return country_;
        }
        void SetCountry( const Guid& country )
        {
            country_ = country;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CODE_FIELD_ID, &code_);
            Bind(statement, COUNTRY_FIELD_ID, &country_);
        }

    };

    class MediaProxySessionColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid service_;
        std::array<wchar_t,129> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Guid enabledTimeseries_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Service],[Name],[EnabledTimeseries]";
        static constexpr std::wstring_view ViewName = L"MediaProxySessionView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT SERVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT ENABLEDTIMESERIES_FIELD_ID = 5;

        MediaProxySessionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MediaProxySession;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Service( ) const
        {
            return service_;
        }
        void SetService( const Guid& service )
        {
            service_ = service;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Guid EnabledTimeseries( ) const
        {
            return enabledTimeseries_;
        }
        void SetEnabledTimeseries( const Guid& enabledTimeseries )
        {
            enabledTimeseries_ = enabledTimeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, SERVICE_FIELD_ID, &service_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, ENABLEDTIMESERIES_FIELD_ID, &enabledTimeseries_);
        }

    };

    class MediaProxySessionFileColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid proxySession_;
        DateTime timestamp_;
        std::array<wchar_t,101> streamName_ = {};
        SQLLEN streamNameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ProxySession],[Timestamp],[StreamName]";
        static constexpr std::wstring_view ViewName = L"MediaProxySessionFileView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT PROXYSESSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT STREAMNAME_FIELD_ID = 5;

        MediaProxySessionFileColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MediaProxySessionFile;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid ProxySession( ) const
        {
            return proxySession_;
        }
        void SetProxySession( const Guid& proxySession )
        {
            proxySession_ = proxySession;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        std::wstring_view StreamName( ) const
        {
            if(streamNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(streamName_.data(),static_cast<size_t>( streamNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetStreamName( const WideString& streamName )
        {
            Assign(streamName, streamName_, streamNameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, PROXYSESSION_FIELD_ID, &proxySession_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, STREAMNAME_FIELD_ID, &streamName_, &streamNameLengthOrNullIndicator_);
        }

    };

    class MediaProxySessionOptionsColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid proxySession_;
        DateTime timestamp_;
        std::array<wchar_t,256> sourceStreamUrl_ = {};
        SQLLEN sourceStreamUrlLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,256> streamName_ = {};
        SQLLEN streamNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Data::MediaProxySessionMode mode_ = Data::MediaProxySessionMode::Unknown;
        Int32 tunnelOverHTTPPortNumber_ = 0;
        std::array<wchar_t,129> username_ = {};
        SQLLEN usernameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,129> password_ = {};
        SQLLEN passwordLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 recorderPortNumber_ = 0;
        Data::MediaProxySessionType sessionType_ = Data::MediaProxySessionType::Unknown;
        TimeSpan maxFileTime_;
        TimeSpan maxFileRetention_;
        std::array<wchar_t,261> videoDirectory_ = {};
        SQLLEN videoDirectoryLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ProxySession],[Timestamp],[SourceStreamUrl],[StreamName],[Mode],[TunnelOverHTTPPortNumber],[Username],[Password],[RecorderPortNumber],[SessionType],[MaxFileTime],[MaxFileRetention],[VideoDirectory]";
        static constexpr std::wstring_view ViewName = L"MediaProxySessionOptionsView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT PROXYSESSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT SOURCESTREAMURL_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STREAMNAME_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MODE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT TUNNELOVERHTTPPORTNUMBER_FIELD_ID = 8;
        static constexpr SQLUSMALLINT USERNAME_FIELD_ID = 9;
        static constexpr SQLUSMALLINT PASSWORD_FIELD_ID = 10;
        static constexpr SQLUSMALLINT RECORDERPORTNUMBER_FIELD_ID = 11;
        static constexpr SQLUSMALLINT SESSIONTYPE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT MAXFILETIME_FIELD_ID = 13;
        static constexpr SQLUSMALLINT MAXFILERETENTION_FIELD_ID = 14;
        static constexpr SQLUSMALLINT VIDEODIRECTORY_FIELD_ID = 15;

        MediaProxySessionOptionsColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MediaProxySessionOptions;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid ProxySession( ) const
        {
            return proxySession_;
        }
        void SetProxySession( const Guid& proxySession )
        {
            proxySession_ = proxySession;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        std::wstring_view SourceStreamUrl( ) const
        {
            if(sourceStreamUrlLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(sourceStreamUrl_.data(),static_cast<size_t>( sourceStreamUrlLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetSourceStreamUrl( const WideString& sourceStreamUrl )
        {
            Assign(sourceStreamUrl, sourceStreamUrl_, sourceStreamUrlLengthOrNullIndicator_);
        }
        std::wstring_view StreamName( ) const
        {
            if(streamNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(streamName_.data(),static_cast<size_t>( streamNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetStreamName( const WideString& streamName )
        {
            Assign(streamName, streamName_, streamNameLengthOrNullIndicator_);
        }
        Data::MediaProxySessionMode Mode( ) const
        {
            return mode_;
        }
        void SetMode( Data::MediaProxySessionMode mode )
        {
            mode_ = mode;
        }
        Int32 TunnelOverHTTPPortNumber( ) const
        {
            return tunnelOverHTTPPortNumber_;
        }
        void SetTunnelOverHTTPPortNumber( Int32 tunnelOverHTTPPortNumber )
        {
            tunnelOverHTTPPortNumber_ = tunnelOverHTTPPortNumber;
        }
        std::wstring_view Username( ) const
        {
            if(usernameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(username_.data(),static_cast<size_t>( usernameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetUsername( const WideString& username )
        {
            Assign(username, username_, usernameLengthOrNullIndicator_);
        }
        std::wstring_view Password( ) const
        {
            if(passwordLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(password_.data(),static_cast<size_t>( passwordLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPassword( const WideString& password )
        {
            Assign(password, password_, passwordLengthOrNullIndicator_);
        }
        Int32 RecorderPortNumber( ) const
        {
            return recorderPortNumber_;
        }
        void SetRecorderPortNumber( Int32 recorderPortNumber )
        {
            recorderPortNumber_ = recorderPortNumber;
        }
        Data::MediaProxySessionType SessionType( ) const
        {
            return sessionType_;
        }
        void SetSessionType( Data::MediaProxySessionType sessionType )
        {
            sessionType_ = sessionType;
        }
        TimeSpan MaxFileTime( ) const
        {
            return maxFileTime_;
        }
        void SetMaxFileTime( const TimeSpan& maxFileTime )
        {
            maxFileTime_ = maxFileTime;
        }
        TimeSpan MaxFileRetention( ) const
        {
            return maxFileRetention_;
        }
        void SetMaxFileRetention( const TimeSpan& maxFileRetention )
        {
            maxFileRetention_ = maxFileRetention;
        }
        std::wstring_view VideoDirectory( ) const
        {
            if(videoDirectoryLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(videoDirectory_.data(),static_cast<size_t>( videoDirectoryLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetVideoDirectory( const WideString& videoDirectory )
        {
            Assign(videoDirectory, videoDirectory_, videoDirectoryLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, PROXYSESSION_FIELD_ID, &proxySession_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, SOURCESTREAMURL_FIELD_ID, &sourceStreamUrl_, &sourceStreamUrlLengthOrNullIndicator_);
            Bind(statement, STREAMNAME_FIELD_ID, &streamName_, &streamNameLengthOrNullIndicator_);
            Bind(statement, MODE_FIELD_ID, &mode_);
            Bind(statement, TUNNELOVERHTTPPORTNUMBER_FIELD_ID, &tunnelOverHTTPPortNumber_);
            Bind(statement, USERNAME_FIELD_ID, &username_, &usernameLengthOrNullIndicator_);
            Bind(statement, PASSWORD_FIELD_ID, &password_, &passwordLengthOrNullIndicator_);
            Bind(statement, RECORDERPORTNUMBER_FIELD_ID, &recorderPortNumber_);
            Bind(statement, SESSIONTYPE_FIELD_ID, &sessionType_);
            Bind(statement, MAXFILETIME_FIELD_ID, &maxFileTime_);
            Bind(statement, MAXFILERETENTION_FIELD_ID, &maxFileRetention_);
            Bind(statement, VIDEODIRECTORY_FIELD_ID, &videoDirectory_, &videoDirectoryLengthOrNullIndicator_);
        }

    };

    class MediaServiceColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid enabledTimeseries_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[EnabledTimeseries]";
        static constexpr std::wstring_view ViewName = L"MediaServiceView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ENABLEDTIMESERIES_FIELD_ID = 3;

        MediaServiceColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MediaService;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid EnabledTimeseries( ) const
        {
            return enabledTimeseries_;
        }
        void SetEnabledTimeseries( const Guid& enabledTimeseries )
        {
            enabledTimeseries_ = enabledTimeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ENABLEDTIMESERIES_FIELD_ID, &enabledTimeseries_);
        }

    };

    class MediaServiceOptionsColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid mediaService_;
        DateTime timestamp_;
        Int32 rtspPortNumber_ = 0;
        Int32 httpPortNumber_ = 0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[MediaService],[Timestamp],[RtspPortNumber],[HttpPortNumber]";
        static constexpr std::wstring_view ViewName = L"MediaServiceOptionsView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT MEDIASERVICE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT RTSPPORTNUMBER_FIELD_ID = 5;
        static constexpr SQLUSMALLINT HTTPPORTNUMBER_FIELD_ID = 6;

        MediaServiceOptionsColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MediaServiceOptions;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid MediaService( ) const
        {
            return mediaService_;
        }
        void SetMediaService( const Guid& mediaService )
        {
            mediaService_ = mediaService;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Int32 RtspPortNumber( ) const
        {
            return rtspPortNumber_;
        }
        void SetRtspPortNumber( Int32 rtspPortNumber )
        {
            rtspPortNumber_ = rtspPortNumber;
        }
        Int32 HttpPortNumber( ) const
        {
            return httpPortNumber_;
        }
        void SetHttpPortNumber( Int32 httpPortNumber )
        {
            httpPortNumber_ = httpPortNumber;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, MEDIASERVICE_FIELD_ID, &mediaService_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, RTSPPORTNUMBER_FIELD_ID, &rtspPortNumber_);
            Bind(statement, HTTPPORTNUMBER_FIELD_ID, &httpPortNumber_);
        }

    };

    class NamespaceElementColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid namespace_;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString description_;
        SQLLEN descriptionLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Namespace],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"NamespaceElementView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAMESPACE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DESCRIPTION_FIELD_ID = 5;

        NamespaceElementColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::NamespaceElement;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Namespace( ) const
        {
            return namespace_;
        }
        void SetNamespace( const Guid& namespace__ )
        {
            namespace_ = namespace__;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        void SetDescription( const WideString& description )
        {
            Assign(description, description_, descriptionLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAMESPACE_FIELD_ID, &namespace_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class ElementTypeColumnData : public NamespaceElementColumnData
    {
    public:
        using Base = NamespaceElementColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Namespace],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"ElementTypeView";

        ElementTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ElementType;
        }

    };

    class NamespaceColumnData : public NamespaceElementColumnData
    {
    public:
        using Base = NamespaceElementColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Namespace],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"NamespaceView";

        NamespaceColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Namespace;
        }

    };

    class OilspillColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid oilSpillDetector_;
        DateTime timestamp_;
        double oilArea_ = 0.0;
        std::vector<Byte> shape_;
        SQLLEN shapeLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::vector<Byte> bSI_;
        SQLLEN bSILengthOrNullIndicator_ = SQL_NULL_DATA;
        std::vector<Byte> oil_;
        SQLLEN oilLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::vector<Byte> trace_;
        SQLLEN traceLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[OilSpillDetector],[Timestamp],[OilArea],[Shape],[BSI],[Oil],[Trace]";
        static constexpr std::wstring_view ViewName = L"OilspillView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT OILSPILLDETECTOR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT OILAREA_FIELD_ID = 5;
        static constexpr SQLUSMALLINT SHAPE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT BSI_FIELD_ID = 7;
        static constexpr SQLUSMALLINT OIL_FIELD_ID = 8;
        static constexpr SQLUSMALLINT TRACE_FIELD_ID = 9;

        OilspillColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Oilspill;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid OilSpillDetector( ) const
        {
            return oilSpillDetector_;
        }
        void SetOilSpillDetector( const Guid& oilSpillDetector )
        {
            oilSpillDetector_ = oilSpillDetector;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double OilArea( ) const
        {
            return oilArea_;
        }
        void SetOilArea( double oilArea )
        {
            oilArea_ = oilArea;
        }
        const std::vector<Byte>& Shape( ) const
        {
            return shape_;
        }
        void SetShape( const std::vector<Byte>& shape )
        {
            Assign(shape, shape_, shapeLengthOrNullIndicator_);
        }
        const std::vector<Byte>& BSI( ) const
        {
            return bSI_;
        }
        void SetBSI( const std::vector<Byte>& bSI )
        {
            Assign(bSI, bSI_, bSILengthOrNullIndicator_);
        }
        const std::vector<Byte>& Oil( ) const
        {
            return oil_;
        }
        void SetOil( const std::vector<Byte>& oil )
        {
            Assign(oil, oil_, oilLengthOrNullIndicator_);
        }
        const std::vector<Byte>& Trace( ) const
        {
            return trace_;
        }
        void SetTrace( const std::vector<Byte>& trace )
        {
            Assign(trace, trace_, traceLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, OILSPILLDETECTOR_FIELD_ID, &oilSpillDetector_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, OILAREA_FIELD_ID, &oilArea_);
        }

    };

    class OilspillDetectorCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid oilSpillDetector_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[OilSpillDetector],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"OilspillDetectorCommandView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT OILSPILLDETECTOR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REPLY_FIELD_ID = 7;

        OilspillDetectorCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::OilspillDetectorCommand;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid OilSpillDetector( ) const
        {
            return oilSpillDetector_;
        }
        void SetOilSpillDetector( const Guid& oilSpillDetector )
        {
            oilSpillDetector_ = oilSpillDetector;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        void SetDeviceCommandSourceType( Data::DeviceCommandSourceType deviceCommandSourceType )
        {
            deviceCommandSourceType_ = deviceCommandSourceType;
        }
        Guid DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        void SetDeviceCommandSourceId( const Guid& deviceCommandSourceId )
        {
            deviceCommandSourceId_ = deviceCommandSourceId;
        }
        Guid Reply( ) const
        {
            return reply_;
        }
        void SetReply( const Guid& reply )
        {
            reply_ = reply;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, OILSPILLDETECTOR_FIELD_ID, &oilSpillDetector_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEVICECOMMANDSOURCETYPE_FIELD_ID, &deviceCommandSourceType_);
            Bind(statement, DEVICECOMMANDSOURCEID_FIELD_ID, &deviceCommandSourceId_);
            Bind(statement, REPLY_FIELD_ID, &reply_);
        }

    };

    class OilspillDetectorCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid oilSpillDetector_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[OilSpillDetector],[Timestamp],[Command],[Status],[Message]";
        static constexpr std::wstring_view ViewName = L"OilspillDetectorCommandReplyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT OILSPILLDETECTOR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COMMAND_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 7;

        OilspillDetectorCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::OilspillDetectorCommandReply;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid OilSpillDetector( ) const
        {
            return oilSpillDetector_;
        }
        void SetOilSpillDetector( const Guid& oilSpillDetector )
        {
            oilSpillDetector_ = oilSpillDetector;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Command( ) const
        {
            return command_;
        }
        void SetCommand( const Guid& command )
        {
            command_ = command;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::DeviceCommandReplyStatus status )
        {
            status_ = status;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, OILSPILLDETECTOR_FIELD_ID, &oilSpillDetector_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COMMAND_FIELD_ID, &command_);
            Bind(statement, STATUS_FIELD_ID, &status_);
        }

    };

    class OilspillDetectorConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid oilSpillDetector_;
        DateTime timestamp_;
        double range_ = 0.0;
        double startAngle_ = 0.0;
        double endAngle_ = 0.0;
        double startRange_ = 0.0;
        double endRange_ = 0.0;
        Int32 updateRate_ = 0;
        TimeSpan statusSendTime_;
        bool drawBorder_ = false;
        std::vector<Byte> colors_;
        SQLLEN colorsLengthOrNullIndicator_ = SQL_NULL_DATA;
        bool sendToServer_ = false;
        std::array<wchar_t,101> directory_ = {};
        SQLLEN directoryLengthOrNullIndicator_ = SQL_NULL_DATA;
        bool transparentWater_ = false;
        bool savePictures_ = false;
        bool sendAsTarget_ = false;
        bool writeLog_ = false;
        std::array<wchar_t,101> targetFilePrefix_ = {};
        SQLLEN targetFilePrefixLengthOrNullIndicator_ = SQL_NULL_DATA;
        Guid targetMMSI_;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        bool testSourceEnabled_ = false;
        std::array<wchar_t,101> proxyServer_ = {};
        SQLLEN proxyServerLengthOrNullIndicator_ = SQL_NULL_DATA;
        bool useProxyServer_ = false;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[OilSpillDetector],[Timestamp],[Range],[StartAngle],[EndAngle],[StartRange],[EndRange],[UpdateRate],[StatusSendTime],[DrawBorder],[SendToServer],[Directory],[TransparentWater],[SavePictures],[SendAsTarget],[WriteLog],[TargetFilePrefix],[TargetMMSI],[Latitude],[Longitude],[TestSourceEnabled],[ProxyServer],[UseProxyServer],[Colors]";
        static constexpr std::wstring_view ViewName = L"OilspillDetectorConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT OILSPILLDETECTOR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT RANGE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STARTANGLE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT ENDANGLE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT STARTRANGE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT ENDRANGE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT UPDATERATE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT STATUSSENDTIME_FIELD_ID = 11;
        static constexpr SQLUSMALLINT DRAWBORDER_FIELD_ID = 12;
        static constexpr SQLUSMALLINT SENDTOSERVER_FIELD_ID = 13;
        static constexpr SQLUSMALLINT DIRECTORY_FIELD_ID = 14;
        static constexpr SQLUSMALLINT TRANSPARENTWATER_FIELD_ID = 15;
        static constexpr SQLUSMALLINT SAVEPICTURES_FIELD_ID = 16;
        static constexpr SQLUSMALLINT SENDASTARGET_FIELD_ID = 17;
        static constexpr SQLUSMALLINT WRITELOG_FIELD_ID = 18;
        static constexpr SQLUSMALLINT TARGETFILEPREFIX_FIELD_ID = 19;
        static constexpr SQLUSMALLINT TARGETMMSI_FIELD_ID = 20;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 21;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 22;
        static constexpr SQLUSMALLINT TESTSOURCEENABLED_FIELD_ID = 23;
        static constexpr SQLUSMALLINT PROXYSERVER_FIELD_ID = 24;
        static constexpr SQLUSMALLINT USEPROXYSERVER_FIELD_ID = 25;
        static constexpr SQLUSMALLINT COLORS_FIELD_ID = 26;

        OilspillDetectorConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::OilspillDetectorConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid OilSpillDetector( ) const
        {
            return oilSpillDetector_;
        }
        void SetOilSpillDetector( const Guid& oilSpillDetector )
        {
            oilSpillDetector_ = oilSpillDetector;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double Range( ) const
        {
            return range_;
        }
        void SetRange( double range )
        {
            range_ = range;
        }
        double StartAngle( ) const
        {
            return startAngle_;
        }
        void SetStartAngle( double startAngle )
        {
            startAngle_ = startAngle;
        }
        double EndAngle( ) const
        {
            return endAngle_;
        }
        void SetEndAngle( double endAngle )
        {
            endAngle_ = endAngle;
        }
        double StartRange( ) const
        {
            return startRange_;
        }
        void SetStartRange( double startRange )
        {
            startRange_ = startRange;
        }
        double EndRange( ) const
        {
            return endRange_;
        }
        void SetEndRange( double endRange )
        {
            endRange_ = endRange;
        }
        Int32 UpdateRate( ) const
        {
            return updateRate_;
        }
        void SetUpdateRate( Int32 updateRate )
        {
            updateRate_ = updateRate;
        }
        TimeSpan StatusSendTime( ) const
        {
            return statusSendTime_;
        }
        void SetStatusSendTime( const TimeSpan& statusSendTime )
        {
            statusSendTime_ = statusSendTime;
        }
        bool DrawBorder( ) const
        {
            return drawBorder_;
        }
        void SetDrawBorder( bool drawBorder )
        {
            drawBorder_ = drawBorder;
        }
        const std::vector<Byte>& Colors( ) const
        {
            return colors_;
        }
        void SetColors( const std::vector<Byte>& colors )
        {
            Assign(colors, colors_, colorsLengthOrNullIndicator_);
        }
        bool SendToServer( ) const
        {
            return sendToServer_;
        }
        void SetSendToServer( bool sendToServer )
        {
            sendToServer_ = sendToServer;
        }
        std::wstring_view Directory( ) const
        {
            if(directoryLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(directory_.data(),static_cast<size_t>( directoryLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetDirectory( const WideString& directory )
        {
            Assign(directory, directory_, directoryLengthOrNullIndicator_);
        }
        bool TransparentWater( ) const
        {
            return transparentWater_;
        }
        void SetTransparentWater( bool transparentWater )
        {
            transparentWater_ = transparentWater;
        }
        bool SavePictures( ) const
        {
            return savePictures_;
        }
        void SetSavePictures( bool savePictures )
        {
            savePictures_ = savePictures;
        }
        bool SendAsTarget( ) const
        {
            return sendAsTarget_;
        }
        void SetSendAsTarget( bool sendAsTarget )
        {
            sendAsTarget_ = sendAsTarget;
        }
        bool WriteLog( ) const
        {
            return writeLog_;
        }
        void SetWriteLog( bool writeLog )
        {
            writeLog_ = writeLog;
        }
        std::wstring_view TargetFilePrefix( ) const
        {
            if(targetFilePrefixLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(targetFilePrefix_.data(),static_cast<size_t>( targetFilePrefixLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetTargetFilePrefix( const WideString& targetFilePrefix )
        {
            Assign(targetFilePrefix, targetFilePrefix_, targetFilePrefixLengthOrNullIndicator_);
        }
        Guid TargetMMSI( ) const
        {
            return targetMMSI_;
        }
        void SetTargetMMSI( const Guid& targetMMSI )
        {
            targetMMSI_ = targetMMSI;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        bool TestSourceEnabled( ) const
        {
            return testSourceEnabled_;
        }
        void SetTestSourceEnabled( bool testSourceEnabled )
        {
            testSourceEnabled_ = testSourceEnabled;
        }
        std::wstring_view ProxyServer( ) const
        {
            if(proxyServerLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(proxyServer_.data(),static_cast<size_t>( proxyServerLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetProxyServer( const WideString& proxyServer )
        {
            Assign(proxyServer, proxyServer_, proxyServerLengthOrNullIndicator_);
        }
        bool UseProxyServer( ) const
        {
            return useProxyServer_;
        }
        void SetUseProxyServer( bool useProxyServer )
        {
            useProxyServer_ = useProxyServer;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, OILSPILLDETECTOR_FIELD_ID, &oilSpillDetector_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, RANGE_FIELD_ID, &range_);
            Bind(statement, STARTANGLE_FIELD_ID, &startAngle_);
            Bind(statement, ENDANGLE_FIELD_ID, &endAngle_);
            Bind(statement, STARTRANGE_FIELD_ID, &startRange_);
            Bind(statement, ENDRANGE_FIELD_ID, &endRange_);
            Bind(statement, UPDATERATE_FIELD_ID, &updateRate_);
            Bind(statement, STATUSSENDTIME_FIELD_ID, &statusSendTime_);
            Bind(statement, DRAWBORDER_FIELD_ID, &drawBorder_);
            Bind(statement, SENDTOSERVER_FIELD_ID, &sendToServer_);
            Bind(statement, DIRECTORY_FIELD_ID, &directory_, &directoryLengthOrNullIndicator_);
            Bind(statement, TRANSPARENTWATER_FIELD_ID, &transparentWater_);
            Bind(statement, SAVEPICTURES_FIELD_ID, &savePictures_);
            Bind(statement, SENDASTARGET_FIELD_ID, &sendAsTarget_);
            Bind(statement, WRITELOG_FIELD_ID, &writeLog_);
            Bind(statement, TARGETFILEPREFIX_FIELD_ID, &targetFilePrefix_, &targetFilePrefixLengthOrNullIndicator_);
            Bind(statement, TARGETMMSI_FIELD_ID, &targetMMSI_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, TESTSOURCEENABLED_FIELD_ID, &testSourceEnabled_);
            Bind(statement, PROXYSERVER_FIELD_ID, &proxyServer_, &proxyServerLengthOrNullIndicator_);
            Bind(statement, USEPROXYSERVER_FIELD_ID, &useProxyServer_);
        }

    };

    class Position2DTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        double x_ = 0.0;
        SQLLEN xNullIndicator_ = SQL_NULL_DATA;
        double y_ = 0.0;
        SQLLEN yNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[X],[Y]";
        static constexpr std::wstring_view ViewName = L"Position2DTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT X_FIELD_ID = 5;
        static constexpr SQLUSMALLINT Y_FIELD_ID = 6;

        Position2DTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Position2DTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double X( ) const
        {
            return x_;
        }
        void SetX( double x )
        {
            x_ = x;
        }
        double Y( ) const
        {
            return y_;
        }
        void SetY( double y )
        {
            y_ = y;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, X_FIELD_ID, &x_, &xNullIndicator_);
            Bind(statement, Y_FIELD_ID, &y_, &yNullIndicator_);
        }

    };

    class Position3DTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        double x_ = 0.0;
        SQLLEN xNullIndicator_ = SQL_NULL_DATA;
        double y_ = 0.0;
        SQLLEN yNullIndicator_ = SQL_NULL_DATA;
        double z_ = 0.0;
        SQLLEN zNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[X],[Y],[Z]";
        static constexpr std::wstring_view ViewName = L"Position3DTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT X_FIELD_ID = 5;
        static constexpr SQLUSMALLINT Y_FIELD_ID = 6;
        static constexpr SQLUSMALLINT Z_FIELD_ID = 7;

        Position3DTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Position3DTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double X( ) const
        {
            return x_;
        }
        void SetX( double x )
        {
            x_ = x;
        }
        double Y( ) const
        {
            return y_;
        }
        void SetY( double y )
        {
            y_ = y;
        }
        double Z( ) const
        {
            return z_;
        }
        void SetZ( double z )
        {
            z_ = z;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, X_FIELD_ID, &x_, &xNullIndicator_);
            Bind(statement, Y_FIELD_ID, &y_, &yNullIndicator_);
            Bind(statement, Z_FIELD_ID, &z_, &zNullIndicator_);
        }

    };

    class ProcessTrackValueResultColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        bool createdNewTrack_ = false;
        Guid trackId_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[CreatedNewTrack],[TrackId]";
        static constexpr std::wstring_view ViewName = L"ProcessTrackValueResultView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CREATEDNEWTRACK_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TRACKID_FIELD_ID = 4;

        ProcessTrackValueResultColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ProcessTrackValueResult;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        bool CreatedNewTrack( ) const
        {
            return createdNewTrack_;
        }
        void SetCreatedNewTrack( bool createdNewTrack )
        {
            createdNewTrack_ = createdNewTrack;
        }
        Guid TrackId( ) const
        {
            return trackId_;
        }
        void SetTrackId( const Guid& trackId )
        {
            trackId_ = trackId;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CREATEDNEWTRACK_FIELD_ID, &createdNewTrack_);
            Bind(statement, TRACKID_FIELD_ID, &trackId_);
        }

    };

    class PropertyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid element_;
        Guid definition_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition]";
        static constexpr std::wstring_view ViewName = L"PropertyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ELEMENT_FIELD_ID = 3;
        static constexpr SQLUSMALLINT DEFINITION_FIELD_ID = 4;

        PropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Property;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Element( ) const
        {
            return element_;
        }
        void SetElement( const Guid& element )
        {
            element_ = element;
        }
        Guid Definition( ) const
        {
            return definition_;
        }
        void SetDefinition( const Guid& definition )
        {
            definition_ = definition;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ELEMENT_FIELD_ID, &element_);
            Bind(statement, DEFINITION_FIELD_ID, &definition_);
        }

    };

    class BinaryPropertyColumnData : public PropertyColumnData
    {
        std::vector<Byte> value_;
        SQLLEN valueLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"BinaryPropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        BinaryPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BinaryProperty;
        }

        const std::vector<Byte>& Value( ) const
        {
            return value_;
        }
        void SetValue( const std::vector<Byte>& value )
        {
            Assign(value, value_, valueLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

        }

    };

    class BooleanPropertyColumnData : public PropertyColumnData
    {
        bool value_ = false;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"BooleanPropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        BooleanPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BooleanProperty;
        }

        bool Value( ) const
        {
            return value_;
        }
        void SetValue( bool value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class BytePropertyColumnData : public PropertyColumnData
    {
        Byte value_ = 0;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"BytePropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        BytePropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ByteProperty;
        }

        Byte Value( ) const
        {
            return value_;
        }
        void SetValue( Byte value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class DateTimePropertyColumnData : public PropertyColumnData
    {
        DateTime value_;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"DateTimePropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        DateTimePropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DateTimeProperty;
        }

        DateTime Value( ) const
        {
            return value_;
        }
        void SetValue( const DateTime& value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class DoublePropertyColumnData : public PropertyColumnData
    {
        double value_ = 0.0;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"DoublePropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        DoublePropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DoubleProperty;
        }

        double Value( ) const
        {
            return value_;
        }
        void SetValue( double value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class GuidPropertyColumnData : public PropertyColumnData
    {
        Guid value_;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"GuidPropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        GuidPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GuidProperty;
        }

        Guid Value( ) const
        {
            return value_;
        }
        void SetValue( const Guid& value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class Int16PropertyColumnData : public PropertyColumnData
    {
        Int16 value_ = 0;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"Int16PropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        Int16PropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int16Property;
        }

        Int16 Value( ) const
        {
            return value_;
        }
        void SetValue( Int16 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class Int32PropertyColumnData : public PropertyColumnData
    {
        Int32 value_ = 0;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"Int32PropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        Int32PropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int32Property;
        }

        Int32 Value( ) const
        {
            return value_;
        }
        void SetValue( Int32 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class Int64PropertyColumnData : public PropertyColumnData
    {
        Int64 value_ = 0;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"Int64PropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        Int64PropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int64Property;
        }

        Int64 Value( ) const
        {
            return value_;
        }
        void SetValue( Int64 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class ReferencePropertyColumnData : public PropertyColumnData
    {
        Guid value_;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"ReferencePropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        ReferencePropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ReferenceProperty;
        }

        Guid Value( ) const
        {
            return value_;
        }
        void SetValue( const Guid& value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class SBytePropertyColumnData : public PropertyColumnData
    {
        SByte value_ = 0;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"SBytePropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        SBytePropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SByteProperty;
        }

        SByte Value( ) const
        {
            return value_;
        }
        void SetValue( SByte value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class SinglePropertyColumnData : public PropertyColumnData
    {
        float value_ = 0.0f;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"SinglePropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        SinglePropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SingleProperty;
        }

        float Value( ) const
        {
            return value_;
        }
        void SetValue( float value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class StringPropertyColumnData : public PropertyColumnData
    {
        std::array<wchar_t,101> value_ = {};
        SQLLEN valueLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"StringPropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        StringPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::StringProperty;
        }

        std::wstring_view Value( ) const
        {
            if(valueLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(value_.data(),static_cast<size_t>( valueLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetValue( const WideString& value )
        {
            Assign(value, value_, valueLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_, &valueLengthOrNullIndicator_);
        }

    };

    class TimeseriesPropertyColumnData : public PropertyColumnData
    {
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition]";
        static constexpr std::wstring_view ViewName = L"TimeseriesPropertyView";

        TimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeseriesProperty;
        }

    };

    class BinaryTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"BinaryTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        BinaryTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BinaryTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class BooleanTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"BooleanTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        BooleanTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BooleanTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class ByteTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"ByteTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        ByteTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ByteTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class DateTimeTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"DateTimeTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        DateTimeTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DateTimeTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class DoubleTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"DoubleTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        DoubleTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DoubleTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class GuidTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"GuidTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        GuidTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GuidTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class Int16TimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"Int16TimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        Int16TimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int16TimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class Int32TimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"Int32TimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        Int32TimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int32TimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class Int64TimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"Int64TimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        Int64TimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int64TimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class ReferenceTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"ReferenceTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        ReferenceTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ReferenceTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class SByteTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"SByteTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        SByteTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SByteTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class SingleTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"SingleTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        SingleTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SingleTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class StringTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"StringTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        StringTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::StringTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class TimeSpanTimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"TimeSpanTimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        TimeSpanTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeSpanTimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class UInt16TimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"UInt16TimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        UInt16TimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt16TimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class UInt32TimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"UInt32TimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        UInt32TimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt32TimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class UInt64TimeseriesPropertyColumnData : public TimeseriesPropertyColumnData
    {
        Guid timeseries_;
    public:
        using Base = TimeseriesPropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Timeseries]";
        static constexpr std::wstring_view ViewName = L"UInt64TimeseriesPropertyView";

        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 5;

        UInt64TimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt64TimeseriesProperty;
        }

        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
        }

    };

    class TimeSpanPropertyColumnData : public PropertyColumnData
    {
        TimeSpan value_;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"TimeSpanPropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        TimeSpanPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeSpanProperty;
        }

        TimeSpan Value( ) const
        {
            return value_;
        }
        void SetValue( const TimeSpan& value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class UInt16PropertyColumnData : public PropertyColumnData
    {
        UInt16 value_ = 0;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"UInt16PropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        UInt16PropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt16Property;
        }

        UInt16 Value( ) const
        {
            return value_;
        }
        void SetValue( UInt16 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class UInt32PropertyColumnData : public PropertyColumnData
    {
        UInt32 value_ = 0;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"UInt32PropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        UInt32PropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt32Property;
        }

        UInt32 Value( ) const
        {
            return value_;
        }
        void SetValue( UInt32 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class UInt64PropertyColumnData : public PropertyColumnData
    {
        Int64 value_ = 0;
    public:
        using Base = PropertyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Element],[Definition],[Value]";
        static constexpr std::wstring_view ViewName = L"UInt64PropertyView";

        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        UInt64PropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt64Property;
        }

        Int64 Value( ) const
        {
            return value_;
        }
        void SetValue( Int64 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class PropertyDefinitionColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid elementType_;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString description_;
        SQLLEN descriptionLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"PropertyDefinitionView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ELEMENTTYPE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DESCRIPTION_FIELD_ID = 5;

        PropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::PropertyDefinition;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid ElementType( ) const
        {
            return elementType_;
        }
        void SetElementType( const Guid& elementType )
        {
            elementType_ = elementType;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        void SetDescription( const WideString& description )
        {
            Assign(description, description_, descriptionLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ELEMENTTYPE_FIELD_ID, &elementType_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class BinaryPropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        std::vector<Byte> defaultValue_;
        SQLLEN defaultValueLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[Description],[DefaultValue]";
        static constexpr std::wstring_view ViewName = L"BinaryPropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;

        BinaryPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BinaryPropertyDefinition;
        }

        const std::vector<Byte>& DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( const std::vector<Byte>& defaultValue )
        {
            Assign(defaultValue, defaultValue_, defaultValueLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

        }

    };

    class BooleanPropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        bool defaultValue_ = false;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[Description]";
        static constexpr std::wstring_view ViewName = L"BooleanPropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;

        BooleanPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BooleanPropertyDefinition;
        }

        bool DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( bool defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
        }

    };

    class BytePropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        Byte defaultValue_ = 0;
        Byte minValue_ = 0;
        Byte maxValue_ = 0;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"BytePropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        BytePropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BytePropertyDefinition;
        }

        Byte DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( Byte defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        Byte MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( Byte minValue )
        {
            minValue_ = minValue;
        }
        Byte MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( Byte maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class DateTimePropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        std::array<wchar_t,101> defaultValue_ = {};
        SQLLEN defaultValueLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,101> minValue_ = {};
        SQLLEN minValueLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,101> maxValue_ = {};
        SQLLEN maxValueLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"DateTimePropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        DateTimePropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DateTimePropertyDefinition;
        }

        std::wstring_view DefaultValue( ) const
        {
            if(defaultValueLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(defaultValue_.data(),static_cast<size_t>( defaultValueLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetDefaultValue( const WideString& defaultValue )
        {
            Assign(defaultValue, defaultValue_, defaultValueLengthOrNullIndicator_);
        }
        std::wstring_view MinValue( ) const
        {
            if(minValueLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(minValue_.data(),static_cast<size_t>( minValueLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetMinValue( const WideString& minValue )
        {
            Assign(minValue, minValue_, minValueLengthOrNullIndicator_);
        }
        std::wstring_view MaxValue( ) const
        {
            if(maxValueLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(maxValue_.data(),static_cast<size_t>( maxValueLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetMaxValue( const WideString& maxValue )
        {
            Assign(maxValue, maxValue_, maxValueLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_, &defaultValueLengthOrNullIndicator_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_, &minValueLengthOrNullIndicator_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_, &maxValueLengthOrNullIndicator_);
        }

    };

    class DoublePropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        double defaultValue_ = 0.0;
        double minValue_ = 0.0;
        double maxValue_ = 0.0;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"DoublePropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        DoublePropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DoublePropertyDefinition;
        }

        double DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( double defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        double MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( double minValue )
        {
            minValue_ = minValue;
        }
        double MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( double maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class GuidPropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        Guid defaultValue_;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[Description]";
        static constexpr std::wstring_view ViewName = L"GuidPropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;

        GuidPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GuidPropertyDefinition;
        }

        Guid DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( const Guid& defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
        }

    };

    class Int16PropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        Int16 defaultValue_ = 0;
        Int16 minValue_ = 0;
        Int16 maxValue_ = 0;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"Int16PropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        Int16PropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int16PropertyDefinition;
        }

        Int16 DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( Int16 defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        Int16 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( Int16 minValue )
        {
            minValue_ = minValue;
        }
        Int16 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( Int16 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class Int32PropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        Int32 defaultValue_ = 0;
        Int32 minValue_ = 0;
        Int32 maxValue_ = 0;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"Int32PropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        Int32PropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int32PropertyDefinition;
        }

        Int32 DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( Int32 defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        Int32 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( Int32 minValue )
        {
            minValue_ = minValue;
        }
        Int32 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( Int32 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class Int64PropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        Int64 defaultValue_ = 0;
        Int64 minValue_ = 0;
        Int64 maxValue_ = 0;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"Int64PropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        Int64PropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int64PropertyDefinition;
        }

        Int64 DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( Int64 defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        Int64 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( Int64 minValue )
        {
            minValue_ = minValue;
        }
        Int64 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( Int64 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class ReferencePropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        Guid defaultValue_;
        Guid referencedElementType_;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[ReferencedElementType],[Description]";
        static constexpr std::wstring_view ViewName = L"ReferencePropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REFERENCEDELEMENTTYPE_FIELD_ID = 7;

        ReferencePropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ReferencePropertyDefinition;
        }

        Guid DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( const Guid& defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        Guid ReferencedElementType( ) const
        {
            return referencedElementType_;
        }
        void SetReferencedElementType( const Guid& referencedElementType )
        {
            referencedElementType_ = referencedElementType;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, REFERENCEDELEMENTTYPE_FIELD_ID, &referencedElementType_);
        }

    };

    class SBytePropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        SByte defaultValue_ = 0;
        SByte minValue_ = 0;
        SByte maxValue_ = 0;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"SBytePropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        SBytePropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SBytePropertyDefinition;
        }

        SByte DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( SByte defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        SByte MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( SByte minValue )
        {
            minValue_ = minValue;
        }
        SByte MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( SByte maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class SinglePropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        float defaultValue_ = 0.0f;
        float minValue_ = 0.0f;
        float maxValue_ = 0.0f;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"SinglePropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        SinglePropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SinglePropertyDefinition;
        }

        float DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( float defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        float MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( float minValue )
        {
            minValue_ = minValue;
        }
        float MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( float maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class StringPropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        std::array<wchar_t,101> defaultValue_ = {};
        SQLLEN defaultValueLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,101> pattern_ = {};
        SQLLEN patternLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[Pattern],[Description]";
        static constexpr std::wstring_view ViewName = L"StringPropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT PATTERN_FIELD_ID = 7;

        StringPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::StringPropertyDefinition;
        }

        std::wstring_view DefaultValue( ) const
        {
            if(defaultValueLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(defaultValue_.data(),static_cast<size_t>( defaultValueLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetDefaultValue( const WideString& defaultValue )
        {
            Assign(defaultValue, defaultValue_, defaultValueLengthOrNullIndicator_);
        }
        std::wstring_view Pattern( ) const
        {
            if(patternLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pattern_.data(),static_cast<size_t>( patternLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPattern( const WideString& pattern )
        {
            Assign(pattern, pattern_, patternLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_, &defaultValueLengthOrNullIndicator_);
            Bind(statement, PATTERN_FIELD_ID, &pattern_, &patternLengthOrNullIndicator_);
        }

    };

    class TimeseriesPropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"TimeseriesPropertyDefinitionView";

        TimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeseriesPropertyDefinition;
        }

    };

    class BinaryTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"BinaryTimeseriesPropertyDefinitionView";

        BinaryTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BinaryTimeseriesPropertyDefinition;
        }

    };

    class BooleanTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"BooleanTimeseriesPropertyDefinitionView";

        BooleanTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BooleanTimeseriesPropertyDefinition;
        }

    };

    class ByteTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        Byte minValue_ = 0;
        Byte maxValue_ = 0;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"ByteTimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        ByteTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ByteTimeseriesPropertyDefinition;
        }

        Byte MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( Byte minValue )
        {
            minValue_ = minValue;
        }
        Byte MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( Byte maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class DateTimeTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        std::array<wchar_t,101> minValue_ = {};
        SQLLEN minValueLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,101> maxValue_ = {};
        SQLLEN maxValueLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"DateTimeTimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        DateTimeTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DateTimeTimeseriesPropertyDefinition;
        }

        std::wstring_view MinValue( ) const
        {
            if(minValueLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(minValue_.data(),static_cast<size_t>( minValueLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetMinValue( const WideString& minValue )
        {
            Assign(minValue, minValue_, minValueLengthOrNullIndicator_);
        }
        std::wstring_view MaxValue( ) const
        {
            if(maxValueLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(maxValue_.data(),static_cast<size_t>( maxValueLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetMaxValue( const WideString& maxValue )
        {
            Assign(maxValue, maxValue_, maxValueLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_, &minValueLengthOrNullIndicator_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_, &maxValueLengthOrNullIndicator_);
        }

    };

    class DoubleTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        double minValue_ = 0.0;
        double maxValue_ = 0.0;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"DoubleTimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        DoubleTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DoubleTimeseriesPropertyDefinition;
        }

        double MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( double minValue )
        {
            minValue_ = minValue;
        }
        double MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( double maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class GuidTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"GuidTimeseriesPropertyDefinitionView";

        GuidTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GuidTimeseriesPropertyDefinition;
        }

    };

    class Int16TimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        Int16 minValue_ = 0;
        Int16 maxValue_ = 0;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"Int16TimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        Int16TimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int16TimeseriesPropertyDefinition;
        }

        Int16 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( Int16 minValue )
        {
            minValue_ = minValue;
        }
        Int16 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( Int16 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class Int32TimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        Int32 minValue_ = 0;
        Int32 maxValue_ = 0;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"Int32TimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        Int32TimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int32TimeseriesPropertyDefinition;
        }

        Int32 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( Int32 minValue )
        {
            minValue_ = minValue;
        }
        Int32 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( Int32 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class Int64TimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        Int64 minValue_ = 0;
        Int64 maxValue_ = 0;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"Int64TimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        Int64TimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int64TimeseriesPropertyDefinition;
        }

        Int64 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( Int64 minValue )
        {
            minValue_ = minValue;
        }
        Int64 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( Int64 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class ReferenceTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        Guid referencedElementType_;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[ReferencedElementType],[Description]";
        static constexpr std::wstring_view ViewName = L"ReferenceTimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT REFERENCEDELEMENTTYPE_FIELD_ID = 6;

        ReferenceTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ReferenceTimeseriesPropertyDefinition;
        }

        Guid ReferencedElementType( ) const
        {
            return referencedElementType_;
        }
        void SetReferencedElementType( const Guid& referencedElementType )
        {
            referencedElementType_ = referencedElementType;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, REFERENCEDELEMENTTYPE_FIELD_ID, &referencedElementType_);
        }

    };

    class SByteTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        SByte minValue_ = 0;
        SByte maxValue_ = 0;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"SByteTimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        SByteTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SByteTimeseriesPropertyDefinition;
        }

        SByte MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( SByte minValue )
        {
            minValue_ = minValue;
        }
        SByte MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( SByte maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class SingleTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        float minValue_ = 0.0f;
        float maxValue_ = 0.0f;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"SingleTimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        SingleTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SingleTimeseriesPropertyDefinition;
        }

        float MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( float minValue )
        {
            minValue_ = minValue;
        }
        float MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( float maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class StringTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        std::array<wchar_t,101> pattern_ = {};
        SQLLEN patternLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[Pattern],[Description]";
        static constexpr std::wstring_view ViewName = L"StringTimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT PATTERN_FIELD_ID = 6;

        StringTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::StringTimeseriesPropertyDefinition;
        }

        std::wstring_view Pattern( ) const
        {
            if(patternLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(pattern_.data(),static_cast<size_t>( patternLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPattern( const WideString& pattern )
        {
            Assign(pattern, pattern_, patternLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, PATTERN_FIELD_ID, &pattern_, &patternLengthOrNullIndicator_);
        }

    };

    class TimeSpanTimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        TimeSpan minValue_;
        TimeSpan maxValue_;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"TimeSpanTimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        TimeSpanTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeSpanTimeseriesPropertyDefinition;
        }

        TimeSpan MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( const TimeSpan& minValue )
        {
            minValue_ = minValue;
        }
        TimeSpan MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( const TimeSpan& maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class UInt16TimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        UInt16 minValue_ = 0;
        UInt16 maxValue_ = 0;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"UInt16TimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        UInt16TimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt16TimeseriesPropertyDefinition;
        }

        UInt16 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( UInt16 minValue )
        {
            minValue_ = minValue;
        }
        UInt16 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( UInt16 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class UInt32TimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        UInt32 minValue_ = 0;
        UInt32 maxValue_ = 0;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"UInt32TimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        UInt32TimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt32TimeseriesPropertyDefinition;
        }

        UInt32 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( UInt32 minValue )
        {
            minValue_ = minValue;
        }
        UInt32 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( UInt32 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class UInt64TimeseriesPropertyDefinitionColumnData : public TimeseriesPropertyDefinitionColumnData
    {
        Int64 minValue_ = 0;
        Int64 maxValue_ = 0;
    public:
        using Base = TimeseriesPropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"UInt64TimeseriesPropertyDefinitionView";

        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 7;

        UInt64TimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt64TimeseriesPropertyDefinition;
        }

        Int64 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( Int64 minValue )
        {
            minValue_ = minValue;
        }
        Int64 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( Int64 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class TimeSpanPropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        TimeSpan defaultValue_;
        TimeSpan minValue_;
        TimeSpan maxValue_;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"TimeSpanPropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        TimeSpanPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeSpanPropertyDefinition;
        }

        TimeSpan DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( const TimeSpan& defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        TimeSpan MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( const TimeSpan& minValue )
        {
            minValue_ = minValue;
        }
        TimeSpan MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( const TimeSpan& maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class UInt16PropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        UInt16 defaultValue_ = 0;
        UInt16 minValue_ = 0;
        UInt16 maxValue_ = 0;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"UInt16PropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        UInt16PropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt16PropertyDefinition;
        }

        UInt16 DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( UInt16 defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        UInt16 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( UInt16 minValue )
        {
            minValue_ = minValue;
        }
        UInt16 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( UInt16 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class UInt32PropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        UInt32 defaultValue_ = 0;
        UInt32 minValue_ = 0;
        UInt32 maxValue_ = 0;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"UInt32PropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        UInt32PropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt32PropertyDefinition;
        }

        UInt32 DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( UInt32 defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        UInt32 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( UInt32 minValue )
        {
            minValue_ = minValue;
        }
        UInt32 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( UInt32 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class UInt64PropertyDefinitionColumnData : public PropertyDefinitionColumnData
    {
        Int64 defaultValue_ = 0;
        Int64 minValue_ = 0;
        Int64 maxValue_ = 0;
    public:
        using Base = PropertyDefinitionColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ElementType],[Name],[DefaultValue],[MinValue],[MaxValue],[Description]";
        static constexpr std::wstring_view ViewName = L"UInt64PropertyDefinitionView";

        static constexpr SQLUSMALLINT DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MINVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MAXVALUE_FIELD_ID = 8;

        UInt64PropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt64PropertyDefinition;
        }

        Int64 DefaultValue( ) const
        {
            return defaultValue_;
        }
        void SetDefaultValue( Int64 defaultValue )
        {
            defaultValue_ = defaultValue;
        }
        Int64 MinValue( ) const
        {
            return minValue_;
        }
        void SetMinValue( Int64 minValue )
        {
            minValue_ = minValue;
        }
        Int64 MaxValue( ) const
        {
            return maxValue_;
        }
        void SetMaxValue( Int64 maxValue )
        {
            maxValue_ = maxValue;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEFAULTVALUE_FIELD_ID, &defaultValue_);
            Bind(statement, MINVALUE_FIELD_ID, &minValue_);
            Bind(statement, MAXVALUE_FIELD_ID, &maxValue_);
        }

    };

    class RadarAlarmStatusColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Data::AlarmState type_ = Data::AlarmState::Unknown;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radar],[Timestamp],[Type]";
        static constexpr std::wstring_view ViewName = L"RadarAlarmStatusView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TYPE_FIELD_ID = 5;

        RadarAlarmStatusColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarAlarmStatus;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::AlarmState Type( ) const
        {
            return type_;
        }
        void SetType( Data::AlarmState type )
        {
            type_ = type;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADAR_FIELD_ID, &radar_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, TYPE_FIELD_ID, &type_);
        }

    };

    class RadarCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radar],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"RadarCommandView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REPLY_FIELD_ID = 7;

        RadarCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarCommand;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        void SetDeviceCommandSourceType( Data::DeviceCommandSourceType deviceCommandSourceType )
        {
            deviceCommandSourceType_ = deviceCommandSourceType;
        }
        Guid DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        void SetDeviceCommandSourceId( const Guid& deviceCommandSourceId )
        {
            deviceCommandSourceId_ = deviceCommandSourceId;
        }
        Guid Reply( ) const
        {
            return reply_;
        }
        void SetReply( const Guid& reply )
        {
            reply_ = reply;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADAR_FIELD_ID, &radar_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEVICECOMMANDSOURCETYPE_FIELD_ID, &deviceCommandSourceType_);
            Bind(statement, DEVICECOMMANDSOURCEID_FIELD_ID, &deviceCommandSourceId_);
            Bind(statement, REPLY_FIELD_ID, &reply_);
        }

    };

    class RadarCommandGetStatusColumnData : public RadarCommandColumnData
    {
    public:
        using Base = RadarCommandColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radar],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"RadarCommandGetStatusView";

        RadarCommandGetStatusColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarCommandGetStatus;
        }

    };

    class RadarCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radar],[Timestamp],[Command],[Status],[Message]";
        static constexpr std::wstring_view ViewName = L"RadarCommandReplyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COMMAND_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 7;

        RadarCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarCommandReply;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Command( ) const
        {
            return command_;
        }
        void SetCommand( const Guid& command )
        {
            command_ = command;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::DeviceCommandReplyStatus status )
        {
            status_ = status;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADAR_FIELD_ID, &radar_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COMMAND_FIELD_ID, &command_);
            Bind(statement, STATUS_FIELD_ID, &status_);
        }

    };

    class RadarCommandReplyGetStatusColumnData : public RadarCommandReplyColumnData
    {
        Int32 azimuthCount_ = 0;
        Int32 triggerCount_ = 0;
        TimeSpan rotationCount_;
        Data::RadarPulse pulse_ = Data::RadarPulse::Short;
        bool tx_ = false;
    public:
        using Base = RadarCommandReplyColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radar],[Timestamp],[Command],[Status],[AzimuthCount],[TriggerCount],[RotationCount],[Pulse],[Tx],[Message]";
        static constexpr std::wstring_view ViewName = L"RadarCommandReplyGetStatusView";

        static constexpr SQLUSMALLINT AZIMUTHCOUNT_FIELD_ID = 8;
        static constexpr SQLUSMALLINT TRIGGERCOUNT_FIELD_ID = 9;
        static constexpr SQLUSMALLINT ROTATIONCOUNT_FIELD_ID = 10;
        static constexpr SQLUSMALLINT PULSE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT TX_FIELD_ID = 12;

        RadarCommandReplyGetStatusColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarCommandReplyGetStatus;
        }

        Int32 AzimuthCount( ) const
        {
            return azimuthCount_;
        }
        void SetAzimuthCount( Int32 azimuthCount )
        {
            azimuthCount_ = azimuthCount;
        }
        Int32 TriggerCount( ) const
        {
            return triggerCount_;
        }
        void SetTriggerCount( Int32 triggerCount )
        {
            triggerCount_ = triggerCount;
        }
        TimeSpan RotationCount( ) const
        {
            return rotationCount_;
        }
        void SetRotationCount( const TimeSpan& rotationCount )
        {
            rotationCount_ = rotationCount;
        }
        Data::RadarPulse Pulse( ) const
        {
            return pulse_;
        }
        void SetPulse( Data::RadarPulse pulse )
        {
            pulse_ = pulse;
        }
        bool Tx( ) const
        {
            return tx_;
        }
        void SetTx( bool tx )
        {
            tx_ = tx;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, AZIMUTHCOUNT_FIELD_ID, &azimuthCount_);
            Bind(statement, TRIGGERCOUNT_FIELD_ID, &triggerCount_);
            Bind(statement, ROTATIONCOUNT_FIELD_ID, &rotationCount_);
            Bind(statement, PULSE_FIELD_ID, &pulse_);
            Bind(statement, TX_FIELD_ID, &tx_);
        }

    };

    class RadarConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Int32 radarProtocolVersion_ = 0;
        std::array<wchar_t,101> radarIPAddress_ = {};
        SQLLEN radarIPAddressLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 radarPort_ = 0;
        Int32 radarConfigurationPort_ = 0;
        TimeSpan skipMagicTimeout_;
        TimeSpan readTimeout_;
        TimeSpan synchronizationInterval_;
        Int32 targetsRefreshRate_ = 0;
        Int32 range_ = 0;
        Int32 sectorCount_ = 0;
        Int32 sectorOffset_ = 0;
        UInt32 imageColor_ = 0;
        UInt32 imageSubstitutionColor_ = 0;
        SQLLEN imageSubstitutionColorNullIndicator_ = SQL_NULL_DATA;
        UInt32 transparentColor_ = 0;
        double imageScaleFactorX_ = 0.0;
        double imageOffsetX_ = 0.0;
        double imageScaleFactorY_ = 0.0;
        double imageOffsetY_ = 0.0;
        Data::RadarImageType radarImageType_ = Data::RadarImageType::MaskedProcessed;
        UInt32 trackColor_ = 0;
        UInt32 vectorColor_ = 0;
        bool enableNmea_ = false;
        std::array<wchar_t,101> nmeaReceiverIPAddress_ = {};
        SQLLEN nmeaReceiverIPAddressLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 nmeaReceiverPort_ = 0;
        std::array<wchar_t,101> nmeaReceiverSourceId_ = {};
        SQLLEN nmeaReceiverSourceIdLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radar],[Timestamp],[RadarProtocolVersion],[RadarIPAddress],[RadarPort],[RadarConfigurationPort],[SkipMagicTimeout],[ReadTimeout],[SynchronizationInterval],[TargetsRefreshRate],[Range],[SectorCount],[SectorOffset],[ImageColor],[ImageSubstitutionColor],[TransparentColor],[ImageScaleFactorX],[ImageOffsetX],[ImageScaleFactorY],[ImageOffsetY],[RadarImageType],[TrackColor],[VectorColor],[EnableNmea],[NmeaReceiverIPAddress],[NmeaReceiverPort],[NmeaReceiverSourceId]";
        static constexpr std::wstring_view ViewName = L"RadarConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT RADARPROTOCOLVERSION_FIELD_ID = 5;
        static constexpr SQLUSMALLINT RADARIPADDRESS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT RADARPORT_FIELD_ID = 7;
        static constexpr SQLUSMALLINT RADARCONFIGURATIONPORT_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SKIPMAGICTIMEOUT_FIELD_ID = 9;
        static constexpr SQLUSMALLINT READTIMEOUT_FIELD_ID = 10;
        static constexpr SQLUSMALLINT SYNCHRONIZATIONINTERVAL_FIELD_ID = 11;
        static constexpr SQLUSMALLINT TARGETSREFRESHRATE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT RANGE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT SECTORCOUNT_FIELD_ID = 14;
        static constexpr SQLUSMALLINT SECTOROFFSET_FIELD_ID = 15;
        static constexpr SQLUSMALLINT IMAGECOLOR_FIELD_ID = 16;
        static constexpr SQLUSMALLINT IMAGESUBSTITUTIONCOLOR_FIELD_ID = 17;
        static constexpr SQLUSMALLINT TRANSPARENTCOLOR_FIELD_ID = 18;
        static constexpr SQLUSMALLINT IMAGESCALEFACTORX_FIELD_ID = 19;
        static constexpr SQLUSMALLINT IMAGEOFFSETX_FIELD_ID = 20;
        static constexpr SQLUSMALLINT IMAGESCALEFACTORY_FIELD_ID = 21;
        static constexpr SQLUSMALLINT IMAGEOFFSETY_FIELD_ID = 22;
        static constexpr SQLUSMALLINT RADARIMAGETYPE_FIELD_ID = 23;
        static constexpr SQLUSMALLINT TRACKCOLOR_FIELD_ID = 24;
        static constexpr SQLUSMALLINT VECTORCOLOR_FIELD_ID = 25;
        static constexpr SQLUSMALLINT ENABLENMEA_FIELD_ID = 26;
        static constexpr SQLUSMALLINT NMEARECEIVERIPADDRESS_FIELD_ID = 27;
        static constexpr SQLUSMALLINT NMEARECEIVERPORT_FIELD_ID = 28;
        static constexpr SQLUSMALLINT NMEARECEIVERSOURCEID_FIELD_ID = 29;

        RadarConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Int32 RadarProtocolVersion( ) const
        {
            return radarProtocolVersion_;
        }
        void SetRadarProtocolVersion( Int32 radarProtocolVersion )
        {
            radarProtocolVersion_ = radarProtocolVersion;
        }
        std::wstring_view RadarIPAddress( ) const
        {
            if(radarIPAddressLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(radarIPAddress_.data(),static_cast<size_t>( radarIPAddressLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetRadarIPAddress( const WideString& radarIPAddress )
        {
            Assign(radarIPAddress, radarIPAddress_, radarIPAddressLengthOrNullIndicator_);
        }
        Int32 RadarPort( ) const
        {
            return radarPort_;
        }
        void SetRadarPort( Int32 radarPort )
        {
            radarPort_ = radarPort;
        }
        Int32 RadarConfigurationPort( ) const
        {
            return radarConfigurationPort_;
        }
        void SetRadarConfigurationPort( Int32 radarConfigurationPort )
        {
            radarConfigurationPort_ = radarConfigurationPort;
        }
        TimeSpan SkipMagicTimeout( ) const
        {
            return skipMagicTimeout_;
        }
        void SetSkipMagicTimeout( const TimeSpan& skipMagicTimeout )
        {
            skipMagicTimeout_ = skipMagicTimeout;
        }
        TimeSpan ReadTimeout( ) const
        {
            return readTimeout_;
        }
        void SetReadTimeout( const TimeSpan& readTimeout )
        {
            readTimeout_ = readTimeout;
        }
        TimeSpan SynchronizationInterval( ) const
        {
            return synchronizationInterval_;
        }
        void SetSynchronizationInterval( const TimeSpan& synchronizationInterval )
        {
            synchronizationInterval_ = synchronizationInterval;
        }
        Int32 TargetsRefreshRate( ) const
        {
            return targetsRefreshRate_;
        }
        void SetTargetsRefreshRate( Int32 targetsRefreshRate )
        {
            targetsRefreshRate_ = targetsRefreshRate;
        }
        Int32 Range( ) const
        {
            return range_;
        }
        void SetRange( Int32 range )
        {
            range_ = range;
        }
        Int32 SectorCount( ) const
        {
            return sectorCount_;
        }
        void SetSectorCount( Int32 sectorCount )
        {
            sectorCount_ = sectorCount;
        }
        Int32 SectorOffset( ) const
        {
            return sectorOffset_;
        }
        void SetSectorOffset( Int32 sectorOffset )
        {
            sectorOffset_ = sectorOffset;
        }
        UInt32 ImageColor( ) const
        {
            return imageColor_;
        }
        void SetImageColor( UInt32 imageColor )
        {
            imageColor_ = imageColor;
        }
        UInt32 ImageSubstitutionColor( ) const
        {
            return imageSubstitutionColor_;
        }
        void SetImageSubstitutionColor( UInt32 imageSubstitutionColor )
        {
            imageSubstitutionColor_ = imageSubstitutionColor;
        }
        UInt32 TransparentColor( ) const
        {
            return transparentColor_;
        }
        void SetTransparentColor( UInt32 transparentColor )
        {
            transparentColor_ = transparentColor;
        }
        double ImageScaleFactorX( ) const
        {
            return imageScaleFactorX_;
        }
        void SetImageScaleFactorX( double imageScaleFactorX )
        {
            imageScaleFactorX_ = imageScaleFactorX;
        }
        double ImageOffsetX( ) const
        {
            return imageOffsetX_;
        }
        void SetImageOffsetX( double imageOffsetX )
        {
            imageOffsetX_ = imageOffsetX;
        }
        double ImageScaleFactorY( ) const
        {
            return imageScaleFactorY_;
        }
        void SetImageScaleFactorY( double imageScaleFactorY )
        {
            imageScaleFactorY_ = imageScaleFactorY;
        }
        double ImageOffsetY( ) const
        {
            return imageOffsetY_;
        }
        void SetImageOffsetY( double imageOffsetY )
        {
            imageOffsetY_ = imageOffsetY;
        }
        Data::RadarImageType RadarImageType( ) const
        {
            return radarImageType_;
        }
        void SetRadarImageType( Data::RadarImageType radarImageType )
        {
            radarImageType_ = radarImageType;
        }
        UInt32 TrackColor( ) const
        {
            return trackColor_;
        }
        void SetTrackColor( UInt32 trackColor )
        {
            trackColor_ = trackColor;
        }
        UInt32 VectorColor( ) const
        {
            return vectorColor_;
        }
        void SetVectorColor( UInt32 vectorColor )
        {
            vectorColor_ = vectorColor;
        }
        bool EnableNmea( ) const
        {
            return enableNmea_;
        }
        void SetEnableNmea( bool enableNmea )
        {
            enableNmea_ = enableNmea;
        }
        std::wstring_view NmeaReceiverIPAddress( ) const
        {
            if(nmeaReceiverIPAddressLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(nmeaReceiverIPAddress_.data(),static_cast<size_t>( nmeaReceiverIPAddressLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetNmeaReceiverIPAddress( const WideString& nmeaReceiverIPAddress )
        {
            Assign(nmeaReceiverIPAddress, nmeaReceiverIPAddress_, nmeaReceiverIPAddressLengthOrNullIndicator_);
        }
        Int32 NmeaReceiverPort( ) const
        {
            return nmeaReceiverPort_;
        }
        void SetNmeaReceiverPort( Int32 nmeaReceiverPort )
        {
            nmeaReceiverPort_ = nmeaReceiverPort;
        }
        std::wstring_view NmeaReceiverSourceId( ) const
        {
            if(nmeaReceiverSourceIdLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(nmeaReceiverSourceId_.data(),static_cast<size_t>( nmeaReceiverSourceIdLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetNmeaReceiverSourceId( const WideString& nmeaReceiverSourceId )
        {
            Assign(nmeaReceiverSourceId, nmeaReceiverSourceId_, nmeaReceiverSourceIdLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADAR_FIELD_ID, &radar_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, RADARPROTOCOLVERSION_FIELD_ID, &radarProtocolVersion_);
            Bind(statement, RADARIPADDRESS_FIELD_ID, &radarIPAddress_, &radarIPAddressLengthOrNullIndicator_);
            Bind(statement, RADARPORT_FIELD_ID, &radarPort_);
            Bind(statement, RADARCONFIGURATIONPORT_FIELD_ID, &radarConfigurationPort_);
            Bind(statement, SKIPMAGICTIMEOUT_FIELD_ID, &skipMagicTimeout_);
            Bind(statement, READTIMEOUT_FIELD_ID, &readTimeout_);
            Bind(statement, SYNCHRONIZATIONINTERVAL_FIELD_ID, &synchronizationInterval_);
            Bind(statement, TARGETSREFRESHRATE_FIELD_ID, &targetsRefreshRate_);
            Bind(statement, RANGE_FIELD_ID, &range_);
            Bind(statement, SECTORCOUNT_FIELD_ID, &sectorCount_);
            Bind(statement, SECTOROFFSET_FIELD_ID, &sectorOffset_);
            Bind(statement, IMAGECOLOR_FIELD_ID, &imageColor_);
            Bind(statement, IMAGESUBSTITUTIONCOLOR_FIELD_ID, &imageSubstitutionColor_, &imageSubstitutionColorNullIndicator_);
            Bind(statement, TRANSPARENTCOLOR_FIELD_ID, &transparentColor_);
            Bind(statement, IMAGESCALEFACTORX_FIELD_ID, &imageScaleFactorX_);
            Bind(statement, IMAGEOFFSETX_FIELD_ID, &imageOffsetX_);
            Bind(statement, IMAGESCALEFACTORY_FIELD_ID, &imageScaleFactorY_);
            Bind(statement, IMAGEOFFSETY_FIELD_ID, &imageOffsetY_);
            Bind(statement, RADARIMAGETYPE_FIELD_ID, &radarImageType_);
            Bind(statement, TRACKCOLOR_FIELD_ID, &trackColor_);
            Bind(statement, VECTORCOLOR_FIELD_ID, &vectorColor_);
            Bind(statement, ENABLENMEA_FIELD_ID, &enableNmea_);
            Bind(statement, NMEARECEIVERIPADDRESS_FIELD_ID, &nmeaReceiverIPAddress_, &nmeaReceiverIPAddressLengthOrNullIndicator_);
            Bind(statement, NMEARECEIVERPORT_FIELD_ID, &nmeaReceiverPort_);
            Bind(statement, NMEARECEIVERSOURCEID_FIELD_ID, &nmeaReceiverSourceId_, &nmeaReceiverSourceIdLengthOrNullIndicator_);
        }

    };

    class RadarImageColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        UInt32 depth_ = 0;
        Int32 resolution_ = 0;
        Int32 range_ = 0;
        std::vector<Byte> image_;
        SQLLEN imageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radar],[Timestamp],[Depth],[Resolution],[Range],[Image]";
        static constexpr std::wstring_view ViewName = L"RadarImageView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEPTH_FIELD_ID = 5;
        static constexpr SQLUSMALLINT RESOLUTION_FIELD_ID = 6;
        static constexpr SQLUSMALLINT RANGE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT IMAGE_FIELD_ID = 8;

        RadarImageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarImage;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        UInt32 Depth( ) const
        {
            return depth_;
        }
        void SetDepth( UInt32 depth )
        {
            depth_ = depth;
        }
        Int32 Resolution( ) const
        {
            return resolution_;
        }
        void SetResolution( Int32 resolution )
        {
            resolution_ = resolution;
        }
        Int32 Range( ) const
        {
            return range_;
        }
        void SetRange( Int32 range )
        {
            range_ = range;
        }
        const std::vector<Byte>& Image( ) const
        {
            return image_;
        }
        void SetImage( const std::vector<Byte>& image )
        {
            Assign(image, image_, imageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADAR_FIELD_ID, &radar_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEPTH_FIELD_ID, &depth_);
            Bind(statement, RESOLUTION_FIELD_ID, &resolution_);
            Bind(statement, RANGE_FIELD_ID, &range_);
        }

    };

    class RadarRawTrackTableColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Int32 count_ = 0;
        std::vector<Byte> table_;
        SQLLEN tableLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radar],[Timestamp],[Count],[Table]";
        static constexpr std::wstring_view ViewName = L"RadarRawTrackTableView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COUNT_FIELD_ID = 5;
        static constexpr SQLUSMALLINT TABLE_FIELD_ID = 6;

        RadarRawTrackTableColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarRawTrackTable;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Int32 Count( ) const
        {
            return count_;
        }
        void SetCount( Int32 count )
        {
            count_ = count;
        }
        const std::vector<Byte>& Table( ) const
        {
            return table_;
        }
        void SetTable( const std::vector<Byte>& table )
        {
            Assign(table, table_, tableLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADAR_FIELD_ID, &radar_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COUNT_FIELD_ID, &count_);
        }

    };

    class RadarStatusColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Int32 azimuthCount_ = 0;
        Int32 triggerCount_ = 0;
        TimeSpan rotationTime_;
        Data::RadarPulse pulse_ = Data::RadarPulse::Short;
        bool tx_ = false;
        bool tracking_ = false;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radar],[Timestamp],[AzimuthCount],[TriggerCount],[RotationTime],[Pulse],[Tx],[Tracking]";
        static constexpr std::wstring_view ViewName = L"RadarStatusView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT AZIMUTHCOUNT_FIELD_ID = 5;
        static constexpr SQLUSMALLINT TRIGGERCOUNT_FIELD_ID = 6;
        static constexpr SQLUSMALLINT ROTATIONTIME_FIELD_ID = 7;
        static constexpr SQLUSMALLINT PULSE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT TX_FIELD_ID = 9;
        static constexpr SQLUSMALLINT TRACKING_FIELD_ID = 10;

        RadarStatusColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarStatus;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Int32 AzimuthCount( ) const
        {
            return azimuthCount_;
        }
        void SetAzimuthCount( Int32 azimuthCount )
        {
            azimuthCount_ = azimuthCount;
        }
        Int32 TriggerCount( ) const
        {
            return triggerCount_;
        }
        void SetTriggerCount( Int32 triggerCount )
        {
            triggerCount_ = triggerCount;
        }
        TimeSpan RotationTime( ) const
        {
            return rotationTime_;
        }
        void SetRotationTime( const TimeSpan& rotationTime )
        {
            rotationTime_ = rotationTime;
        }
        Data::RadarPulse Pulse( ) const
        {
            return pulse_;
        }
        void SetPulse( Data::RadarPulse pulse )
        {
            pulse_ = pulse;
        }
        bool Tx( ) const
        {
            return tx_;
        }
        void SetTx( bool tx )
        {
            tx_ = tx;
        }
        bool Tracking( ) const
        {
            return tracking_;
        }
        void SetTracking( bool tracking )
        {
            tracking_ = tracking;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADAR_FIELD_ID, &radar_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, AZIMUTHCOUNT_FIELD_ID, &azimuthCount_);
            Bind(statement, TRIGGERCOUNT_FIELD_ID, &triggerCount_);
            Bind(statement, ROTATIONTIME_FIELD_ID, &rotationTime_);
            Bind(statement, PULSE_FIELD_ID, &pulse_);
            Bind(statement, TX_FIELD_ID, &tx_);
            Bind(statement, TRACKING_FIELD_ID, &tracking_);
        }

    };

    class RadioCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radio_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radio],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"RadioCommandView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADIO_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REPLY_FIELD_ID = 7;

        RadioCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadioCommand;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radio( ) const
        {
            return radio_;
        }
        void SetRadio( const Guid& radio )
        {
            radio_ = radio;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        void SetDeviceCommandSourceType( Data::DeviceCommandSourceType deviceCommandSourceType )
        {
            deviceCommandSourceType_ = deviceCommandSourceType;
        }
        Guid DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        void SetDeviceCommandSourceId( const Guid& deviceCommandSourceId )
        {
            deviceCommandSourceId_ = deviceCommandSourceId;
        }
        Guid Reply( ) const
        {
            return reply_;
        }
        void SetReply( const Guid& reply )
        {
            reply_ = reply;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADIO_FIELD_ID, &radio_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEVICECOMMANDSOURCETYPE_FIELD_ID, &deviceCommandSourceType_);
            Bind(statement, DEVICECOMMANDSOURCEID_FIELD_ID, &deviceCommandSourceId_);
            Bind(statement, REPLY_FIELD_ID, &reply_);
        }

    };

    class RadioCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radio_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radio],[Timestamp],[Command],[Status],[Message]";
        static constexpr std::wstring_view ViewName = L"RadioCommandReplyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADIO_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COMMAND_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 7;

        RadioCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadioCommandReply;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radio( ) const
        {
            return radio_;
        }
        void SetRadio( const Guid& radio )
        {
            radio_ = radio;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Command( ) const
        {
            return command_;
        }
        void SetCommand( const Guid& command )
        {
            command_ = command;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::DeviceCommandReplyStatus status )
        {
            status_ = status;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADIO_FIELD_ID, &radio_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COMMAND_FIELD_ID, &command_);
            Bind(statement, STATUS_FIELD_ID, &status_);
        }

    };

    class RadioConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radio_;
        DateTime timestamp_;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        std::array<wchar_t,101> playbackUrl_ = {};
        SQLLEN playbackUrlLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,101> radioIPAddress_ = {};
        SQLLEN radioIPAddressLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 radioPort_ = 0;
        std::array<wchar_t,101> ed137IPAddress_ = {};
        SQLLEN ed137IPAddressLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 ed137Port_ = 0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radio],[Timestamp],[Longitude],[Latitude],[PlaybackUrl],[RadioIPAddress],[RadioPort],[Ed137IPAddress],[Ed137Port]";
        static constexpr std::wstring_view ViewName = L"RadioConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADIO_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT PLAYBACKURL_FIELD_ID = 7;
        static constexpr SQLUSMALLINT RADIOIPADDRESS_FIELD_ID = 8;
        static constexpr SQLUSMALLINT RADIOPORT_FIELD_ID = 9;
        static constexpr SQLUSMALLINT ED137IPADDRESS_FIELD_ID = 10;
        static constexpr SQLUSMALLINT ED137PORT_FIELD_ID = 11;

        RadioConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadioConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radio( ) const
        {
            return radio_;
        }
        void SetRadio( const Guid& radio )
        {
            radio_ = radio;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        std::wstring_view PlaybackUrl( ) const
        {
            if(playbackUrlLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(playbackUrl_.data(),static_cast<size_t>( playbackUrlLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetPlaybackUrl( const WideString& playbackUrl )
        {
            Assign(playbackUrl, playbackUrl_, playbackUrlLengthOrNullIndicator_);
        }
        std::wstring_view RadioIPAddress( ) const
        {
            if(radioIPAddressLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(radioIPAddress_.data(),static_cast<size_t>( radioIPAddressLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetRadioIPAddress( const WideString& radioIPAddress )
        {
            Assign(radioIPAddress, radioIPAddress_, radioIPAddressLengthOrNullIndicator_);
        }
        Int32 RadioPort( ) const
        {
            return radioPort_;
        }
        void SetRadioPort( Int32 radioPort )
        {
            radioPort_ = radioPort;
        }
        std::wstring_view Ed137IPAddress( ) const
        {
            if(ed137IPAddressLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(ed137IPAddress_.data(),static_cast<size_t>( ed137IPAddressLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetEd137IPAddress( const WideString& ed137IPAddress )
        {
            Assign(ed137IPAddress, ed137IPAddress_, ed137IPAddressLengthOrNullIndicator_);
        }
        Int32 Ed137Port( ) const
        {
            return ed137Port_;
        }
        void SetEd137Port( Int32 ed137Port )
        {
            ed137Port_ = ed137Port;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADIO_FIELD_ID, &radio_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, PLAYBACKURL_FIELD_ID, &playbackUrl_, &playbackUrlLengthOrNullIndicator_);
            Bind(statement, RADIOIPADDRESS_FIELD_ID, &radioIPAddress_, &radioIPAddressLengthOrNullIndicator_);
            Bind(statement, RADIOPORT_FIELD_ID, &radioPort_);
            Bind(statement, ED137IPADDRESS_FIELD_ID, &ed137IPAddress_, &ed137IPAddressLengthOrNullIndicator_);
            Bind(statement, ED137PORT_FIELD_ID, &ed137Port_);
        }

    };

    class RadomeCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radome_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radome],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"RadomeCommandView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADOME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REPLY_FIELD_ID = 7;

        RadomeCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadomeCommand;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radome( ) const
        {
            return radome_;
        }
        void SetRadome( const Guid& radome )
        {
            radome_ = radome;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        void SetDeviceCommandSourceType( Data::DeviceCommandSourceType deviceCommandSourceType )
        {
            deviceCommandSourceType_ = deviceCommandSourceType;
        }
        Guid DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        void SetDeviceCommandSourceId( const Guid& deviceCommandSourceId )
        {
            deviceCommandSourceId_ = deviceCommandSourceId;
        }
        Guid Reply( ) const
        {
            return reply_;
        }
        void SetReply( const Guid& reply )
        {
            reply_ = reply;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADOME_FIELD_ID, &radome_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEVICECOMMANDSOURCETYPE_FIELD_ID, &deviceCommandSourceType_);
            Bind(statement, DEVICECOMMANDSOURCEID_FIELD_ID, &deviceCommandSourceId_);
            Bind(statement, REPLY_FIELD_ID, &reply_);
        }

    };

    class RadomeCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radome_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radome],[Timestamp],[Command],[Status],[Message]";
        static constexpr std::wstring_view ViewName = L"RadomeCommandReplyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADOME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COMMAND_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 7;

        RadomeCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadomeCommandReply;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radome( ) const
        {
            return radome_;
        }
        void SetRadome( const Guid& radome )
        {
            radome_ = radome;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Command( ) const
        {
            return command_;
        }
        void SetCommand( const Guid& command )
        {
            command_ = command;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::DeviceCommandReplyStatus status )
        {
            status_ = status;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADOME_FIELD_ID, &radome_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COMMAND_FIELD_ID, &command_);
            Bind(statement, STATUS_FIELD_ID, &status_);
        }

    };

    class RadomeConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid radome_;
        DateTime timestamp_;
        TimeSpan interval_;
        double lowPressureLimit_ = 0.0;
        double highPressureLimit_ = 0.0;
        double lowTemperatureLimit_ = 0.0;
        double highTemperatureLimit_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Radome],[Timestamp],[Interval],[LowPressureLimit],[HighPressureLimit],[LowTemperatureLimit],[HighTemperatureLimit]";
        static constexpr std::wstring_view ViewName = L"RadomeConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT RADOME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT INTERVAL_FIELD_ID = 5;
        static constexpr SQLUSMALLINT LOWPRESSURELIMIT_FIELD_ID = 6;
        static constexpr SQLUSMALLINT HIGHPRESSURELIMIT_FIELD_ID = 7;
        static constexpr SQLUSMALLINT LOWTEMPERATURELIMIT_FIELD_ID = 8;
        static constexpr SQLUSMALLINT HIGHTEMPERATURELIMIT_FIELD_ID = 9;

        RadomeConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadomeConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Radome( ) const
        {
            return radome_;
        }
        void SetRadome( const Guid& radome )
        {
            radome_ = radome;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        TimeSpan Interval( ) const
        {
            return interval_;
        }
        void SetInterval( const TimeSpan& interval )
        {
            interval_ = interval;
        }
        double LowPressureLimit( ) const
        {
            return lowPressureLimit_;
        }
        void SetLowPressureLimit( double lowPressureLimit )
        {
            lowPressureLimit_ = lowPressureLimit;
        }
        double HighPressureLimit( ) const
        {
            return highPressureLimit_;
        }
        void SetHighPressureLimit( double highPressureLimit )
        {
            highPressureLimit_ = highPressureLimit;
        }
        double LowTemperatureLimit( ) const
        {
            return lowTemperatureLimit_;
        }
        void SetLowTemperatureLimit( double lowTemperatureLimit )
        {
            lowTemperatureLimit_ = lowTemperatureLimit;
        }
        double HighTemperatureLimit( ) const
        {
            return highTemperatureLimit_;
        }
        void SetHighTemperatureLimit( double highTemperatureLimit )
        {
            highTemperatureLimit_ = highTemperatureLimit;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, RADOME_FIELD_ID, &radome_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, INTERVAL_FIELD_ID, &interval_);
            Bind(statement, LOWPRESSURELIMIT_FIELD_ID, &lowPressureLimit_);
            Bind(statement, HIGHPRESSURELIMIT_FIELD_ID, &highPressureLimit_);
            Bind(statement, LOWTEMPERATURELIMIT_FIELD_ID, &lowTemperatureLimit_);
            Bind(statement, HIGHTEMPERATURELIMIT_FIELD_ID, &highTemperatureLimit_);
        }

    };

    class ReferenceTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        Guid value_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"ReferenceTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        ReferenceTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ReferenceTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Value( ) const
        {
            return value_;
        }
        void SetValue( const Guid& value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_);
        }

    };

    class SByteTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        SByte value_ = 0;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"SByteTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        SByteTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SByteTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        SByte Value( ) const
        {
            return value_;
        }
        void SetValue( SByte value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class SecurityDomainColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString description_;
        SQLLEN descriptionLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"SecurityDomainView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT DESCRIPTION_FIELD_ID = 4;

        SecurityDomainColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SecurityDomain;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        void SetDescription( const WideString& description )
        {
            Assign(description, description_, descriptionLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class SecurityIdentifierColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid domain_;
        std::array<wchar_t,256> identity_ = {};
        SQLLEN identityLengthOrNullIndicator_ = SQL_NULL_DATA;
        WideString description_;
        SQLLEN descriptionLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Domain],[Identity],[Description]";
        static constexpr std::wstring_view ViewName = L"SecurityIdentifierView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT DOMAIN_FIELD_ID = 3;
        static constexpr SQLUSMALLINT IDENTITY_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DESCRIPTION_FIELD_ID = 5;

        SecurityIdentifierColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SecurityIdentifier;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Domain( ) const
        {
            return domain_;
        }
        void SetDomain( const Guid& domain )
        {
            domain_ = domain;
        }
        std::wstring_view Identity( ) const
        {
            if(identityLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(identity_.data(),static_cast<size_t>( identityLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetIdentity( const WideString& identity )
        {
            Assign(identity, identity_, identityLengthOrNullIndicator_);
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        void SetDescription( const WideString& description )
        {
            Assign(description, description_, descriptionLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, DOMAIN_FIELD_ID, &domain_);
            Bind(statement, IDENTITY_FIELD_ID, &identity_, &identityLengthOrNullIndicator_);
        }

    };

    class SecurityLoginColumnData : public SecurityIdentifierColumnData
    {
    public:
        using Base = SecurityIdentifierColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Domain],[Identity],[Description]";
        static constexpr std::wstring_view ViewName = L"SecurityLoginView";

        SecurityLoginColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SecurityLogin;
        }

    };

    class SecurityRoleColumnData : public SecurityIdentifierColumnData
    {
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = SecurityIdentifierColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Domain],[Identity],[Name],[Description]";
        static constexpr std::wstring_view ViewName = L"SecurityRoleView";

        static constexpr SQLUSMALLINT NAME_FIELD_ID = 6;

        SecurityRoleColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SecurityRole;
        }

        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class SecurityIdentifierRoleLinkColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid member_;
        Guid role_;
        DateTime start_;
        DateTime end_;
        SQLLEN endNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Member],[Role],[Start],[End]";
        static constexpr std::wstring_view ViewName = L"SecurityIdentifierRoleLinkView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT MEMBER_FIELD_ID = 3;
        static constexpr SQLUSMALLINT ROLE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT START_FIELD_ID = 5;
        static constexpr SQLUSMALLINT END_FIELD_ID = 6;

        SecurityIdentifierRoleLinkColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SecurityIdentifierRoleLink;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Member( ) const
        {
            return member_;
        }
        void SetMember( const Guid& member )
        {
            member_ = member;
        }
        Guid Role( ) const
        {
            return role_;
        }
        void SetRole( const Guid& role )
        {
            role_ = role;
        }
        DateTime Start( ) const
        {
            return start_;
        }
        void SetStart( const DateTime& start )
        {
            start_ = start;
        }
        DateTime End( ) const
        {
            return end_;
        }
        void SetEnd( const DateTime& end )
        {
            end_ = end;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, MEMBER_FIELD_ID, &member_);
            Bind(statement, ROLE_FIELD_ID, &role_);
            Bind(statement, START_FIELD_ID, &start_);
            Bind(statement, END_FIELD_ID, &end_, &endNullIndicator_);
        }

    };

    class SecurityLoginSessionColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid login_;
        DateTime fromTime_;
        DateTime throughTime_;
        SQLLEN throughTimeNullIndicator_ = SQL_NULL_DATA;
        Guid clientSession_;
        std::array<wchar_t,261> notificationQueueName_ = {};
        SQLLEN notificationQueueNameLengthOrNullIndicator_ = SQL_NULL_DATA;
        std::array<wchar_t,261> messageQueueName_ = {};
        SQLLEN messageQueueNameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Login],[FromTime],[ThroughTime],[ClientSession],[NotificationQueueName],[MessageQueueName]";
        static constexpr std::wstring_view ViewName = L"SecurityLoginSessionView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT LOGIN_FIELD_ID = 3;
        static constexpr SQLUSMALLINT FROMTIME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT THROUGHTIME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT CLIENTSESSION_FIELD_ID = 6;
        static constexpr SQLUSMALLINT NOTIFICATIONQUEUENAME_FIELD_ID = 7;
        static constexpr SQLUSMALLINT MESSAGEQUEUENAME_FIELD_ID = 8;

        SecurityLoginSessionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SecurityLoginSession;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Login( ) const
        {
            return login_;
        }
        void SetLogin( const Guid& login )
        {
            login_ = login;
        }
        DateTime FromTime( ) const
        {
            return fromTime_;
        }
        void SetFromTime( const DateTime& fromTime )
        {
            fromTime_ = fromTime;
        }
        DateTime ThroughTime( ) const
        {
            return throughTime_;
        }
        void SetThroughTime( const DateTime& throughTime )
        {
            throughTime_ = throughTime;
        }
        Guid ClientSession( ) const
        {
            return clientSession_;
        }
        void SetClientSession( const Guid& clientSession )
        {
            clientSession_ = clientSession;
        }
        std::wstring_view NotificationQueueName( ) const
        {
            if(notificationQueueNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(notificationQueueName_.data(),static_cast<size_t>( notificationQueueNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetNotificationQueueName( const WideString& notificationQueueName )
        {
            Assign(notificationQueueName, notificationQueueName_, notificationQueueNameLengthOrNullIndicator_);
        }
        std::wstring_view MessageQueueName( ) const
        {
            if(messageQueueNameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(messageQueueName_.data(),static_cast<size_t>( messageQueueNameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetMessageQueueName( const WideString& messageQueueName )
        {
            Assign(messageQueueName, messageQueueName_, messageQueueNameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, LOGIN_FIELD_ID, &login_);
            Bind(statement, FROMTIME_FIELD_ID, &fromTime_);
            Bind(statement, THROUGHTIME_FIELD_ID, &throughTime_, &throughTimeNullIndicator_);
            Bind(statement, CLIENTSESSION_FIELD_ID, &clientSession_);
            Bind(statement, NOTIFICATIONQUEUENAME_FIELD_ID, &notificationQueueName_, &notificationQueueNameLengthOrNullIndicator_);
            Bind(statement, MESSAGEQUEUENAME_FIELD_ID, &messageQueueName_, &messageQueueNameLengthOrNullIndicator_);
        }

    };

    class SecurityPermissionColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid identifier_;
        DateTime timestamp_;
        Int32 typeCode_ = 0;
        bool canCreate_ = false;
        bool canRead_ = false;
        bool canUpdate_ = false;
        bool canDelete_ = false;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Identifier],[Timestamp],[TypeCode],[CanCreate],[CanRead],[CanUpdate],[CanDelete]";
        static constexpr std::wstring_view ViewName = L"SecurityPermissionView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT IDENTIFIER_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TYPECODE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT CANCREATE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT CANREAD_FIELD_ID = 7;
        static constexpr SQLUSMALLINT CANUPDATE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT CANDELETE_FIELD_ID = 9;

        SecurityPermissionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SecurityPermission;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Identifier( ) const
        {
            return identifier_;
        }
        void SetIdentifier( const Guid& identifier )
        {
            identifier_ = identifier;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Int32 TypeCode( ) const
        {
            return typeCode_;
        }
        void SetTypeCode( Int32 typeCode )
        {
            typeCode_ = typeCode;
        }
        bool CanCreate( ) const
        {
            return canCreate_;
        }
        void SetCanCreate( bool canCreate )
        {
            canCreate_ = canCreate;
        }
        bool CanRead( ) const
        {
            return canRead_;
        }
        void SetCanRead( bool canRead )
        {
            canRead_ = canRead;
        }
        bool CanUpdate( ) const
        {
            return canUpdate_;
        }
        void SetCanUpdate( bool canUpdate )
        {
            canUpdate_ = canUpdate;
        }
        bool CanDelete( ) const
        {
            return canDelete_;
        }
        void SetCanDelete( bool canDelete )
        {
            canDelete_ = canDelete;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, IDENTIFIER_FIELD_ID, &identifier_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, TYPECODE_FIELD_ID, &typeCode_);
            Bind(statement, CANCREATE_FIELD_ID, &canCreate_);
            Bind(statement, CANREAD_FIELD_ID, &canRead_);
            Bind(statement, CANUPDATE_FIELD_ID, &canUpdate_);
            Bind(statement, CANDELETE_FIELD_ID, &canDelete_);
        }

    };

    class SingleTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        float value_ = 0.0f;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"SingleTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        SingleTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SingleTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        float Value( ) const
        {
            return value_;
        }
        void SetValue( float value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class StringTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        WideString value_;
        SQLLEN valueLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"StringTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        StringTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::StringTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        const WideString& Value( ) const
        {
            return value_;
        }
        void SetValue( const WideString& value )
        {
            Assign(value, value_, valueLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
        }

    };

    class TimeseriesCatalogElementColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid catalog_;
        std::array<wchar_t,101> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name]";
        static constexpr std::wstring_view ViewName = L"TimeseriesCatalogElementView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT CATALOG_FIELD_ID = 3;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 4;

        TimeseriesCatalogElementColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeseriesCatalogElement;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Catalog( ) const
        {
            return catalog_;
        }
        void SetCatalog( const Guid& catalog )
        {
            catalog_ = catalog;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, CATALOG_FIELD_ID, &catalog_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class TimeseriesColumnData : public TimeseriesCatalogElementColumnData
    {
        TimeSpan maxRetention_;
    public:
        using Base = TimeseriesCatalogElementColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"TimeseriesView";

        static constexpr SQLUSMALLINT MAXRETENTION_FIELD_ID = 5;

        TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Timeseries;
        }

        TimeSpan MaxRetention( ) const
        {
            return maxRetention_;
        }
        void SetMaxRetention( const TimeSpan& maxRetention )
        {
            maxRetention_ = maxRetention;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, MAXRETENTION_FIELD_ID, &maxRetention_);
        }

    };

    class BinaryTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"BinaryTimeseriesView";

        BinaryTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BinaryTimeseries;
        }

    };

    class BooleanTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"BooleanTimeseriesView";

        BooleanTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::BooleanTimeseries;
        }

    };

    class AisAidToNavigationOffPositionTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid aidToNavigation_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[AidToNavigation]";
        static constexpr std::wstring_view ViewName = L"AisAidToNavigationOffPositionTimeseriesView";

        static constexpr SQLUSMALLINT AIDTONAVIGATION_FIELD_ID = 6;

        AisAidToNavigationOffPositionTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisAidToNavigationOffPositionTimeseries;
        }

        Guid AidToNavigation( ) const
        {
            return aidToNavigation_;
        }
        void SetAidToNavigation( const Guid& aidToNavigation )
        {
            aidToNavigation_ = aidToNavigation;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, AIDTONAVIGATION_FIELD_ID, &aidToNavigation_);
        }

    };

    class DeviceEnabledTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid device_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Device]";
        static constexpr std::wstring_view ViewName = L"DeviceEnabledTimeseriesView";

        static constexpr SQLUSMALLINT DEVICE_FIELD_ID = 6;

        DeviceEnabledTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DeviceEnabledTimeseries;
        }

        Guid Device( ) const
        {
            return device_;
        }
        void SetDevice( const Guid& device )
        {
            device_ = device;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, DEVICE_FIELD_ID, &device_);
        }

    };

    class RadarAutomaticSensitivityTimeControlTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarAutomaticSensitivityTimeControlTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarAutomaticSensitivityTimeControlTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarAutomaticSensitivityTimeControlTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarBlankSector1TimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarBlankSector1TimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarBlankSector1TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarBlankSector1Timeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarBlankSector2TimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarBlankSector2TimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarBlankSector2TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarBlankSector2Timeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarEnableAutomaticFrequencyControlTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarEnableAutomaticFrequencyControlTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarEnableAutomaticFrequencyControlTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarEnableAutomaticFrequencyControlTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarEnableFastTimeConstantTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarEnableFastTimeConstantTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarEnableFastTimeConstantTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarEnableFastTimeConstantTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarEnableSensitivityTimeControlTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarEnableSensitivityTimeControlTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarEnableSensitivityTimeControlTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarEnableSensitivityTimeControlTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarPowerOnTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarPowerOnTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarPowerOnTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarPowerOnTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarSaveSettingsTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarSaveSettingsTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarSaveSettingsTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarSaveSettingsTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarTrackingTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarTrackingTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarTrackingTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarTrackingTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class MediaProxySessionEnabledTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid proxySession_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[ProxySession]";
        static constexpr std::wstring_view ViewName = L"MediaProxySessionEnabledTimeseriesView";

        static constexpr SQLUSMALLINT PROXYSESSION_FIELD_ID = 6;

        MediaProxySessionEnabledTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MediaProxySessionEnabledTimeseries;
        }

        Guid ProxySession( ) const
        {
            return proxySession_;
        }
        void SetProxySession( const Guid& proxySession )
        {
            proxySession_ = proxySession;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, PROXYSESSION_FIELD_ID, &proxySession_);
        }

    };

    class MediaServiceEnabledTimeseriesColumnData : public BooleanTimeseriesColumnData
    {
        Guid service_;
    public:
        using Base = BooleanTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Service]";
        static constexpr std::wstring_view ViewName = L"MediaServiceEnabledTimeseriesView";

        static constexpr SQLUSMALLINT SERVICE_FIELD_ID = 6;

        MediaServiceEnabledTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::MediaServiceEnabledTimeseries;
        }

        Guid Service( ) const
        {
            return service_;
        }
        void SetService( const Guid& service )
        {
            service_ = service;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, SERVICE_FIELD_ID, &service_);
        }

    };

    class ByteTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"ByteTimeseriesView";

        ByteTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ByteTimeseries;
        }

    };

    class DateTimeTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"DateTimeTimeseriesView";

        DateTimeTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DateTimeTimeseries;
        }

    };

    class DoubleTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"DoubleTimeseriesView";

        DoubleTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::DoubleTimeseries;
        }

    };

    class GNSSAltitudeTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid gNSSDevice_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[GNSSDevice]";
        static constexpr std::wstring_view ViewName = L"GNSSAltitudeTimeseriesView";

        static constexpr SQLUSMALLINT GNSSDEVICE_FIELD_ID = 6;

        GNSSAltitudeTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GNSSAltitudeTimeseries;
        }

        Guid GNSSDevice( ) const
        {
            return gNSSDevice_;
        }
        void SetGNSSDevice( const Guid& gNSSDevice )
        {
            gNSSDevice_ = gNSSDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, GNSSDEVICE_FIELD_ID, &gNSSDevice_);
        }

    };

    class GNSSLatitudeTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid gNSSDevice_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[GNSSDevice]";
        static constexpr std::wstring_view ViewName = L"GNSSLatitudeTimeseriesView";

        static constexpr SQLUSMALLINT GNSSDEVICE_FIELD_ID = 6;

        GNSSLatitudeTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GNSSLatitudeTimeseries;
        }

        Guid GNSSDevice( ) const
        {
            return gNSSDevice_;
        }
        void SetGNSSDevice( const Guid& gNSSDevice )
        {
            gNSSDevice_ = gNSSDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, GNSSDEVICE_FIELD_ID, &gNSSDevice_);
        }

    };

    class GNSSLongitudeTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid gNSSDevice_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[GNSSDevice]";
        static constexpr std::wstring_view ViewName = L"GNSSLongitudeTimeseriesView";

        static constexpr SQLUSMALLINT GNSSDEVICE_FIELD_ID = 6;

        GNSSLongitudeTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GNSSLongitudeTimeseries;
        }

        Guid GNSSDevice( ) const
        {
            return gNSSDevice_;
        }
        void SetGNSSDevice( const Guid& gNSSDevice )
        {
            gNSSDevice_ = gNSSDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, GNSSDEVICE_FIELD_ID, &gNSSDevice_);
        }

    };

    class GyroCourseTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid gyroDevice_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[GyroDevice]";
        static constexpr std::wstring_view ViewName = L"GyroCourseTimeseriesView";

        static constexpr SQLUSMALLINT GYRODEVICE_FIELD_ID = 6;

        GyroCourseTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroCourseTimeseries;
        }

        Guid GyroDevice( ) const
        {
            return gyroDevice_;
        }
        void SetGyroDevice( const Guid& gyroDevice )
        {
            gyroDevice_ = gyroDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, GYRODEVICE_FIELD_ID, &gyroDevice_);
        }

    };

    class GyroHeadingMagneticNorthTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid gyroDevice_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[GyroDevice]";
        static constexpr std::wstring_view ViewName = L"GyroHeadingMagneticNorthTimeseriesView";

        static constexpr SQLUSMALLINT GYRODEVICE_FIELD_ID = 6;

        GyroHeadingMagneticNorthTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroHeadingMagneticNorthTimeseries;
        }

        Guid GyroDevice( ) const
        {
            return gyroDevice_;
        }
        void SetGyroDevice( const Guid& gyroDevice )
        {
            gyroDevice_ = gyroDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, GYRODEVICE_FIELD_ID, &gyroDevice_);
        }

    };

    class GyroHeadingTrueNorthTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid gyroDevice_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[GyroDevice]";
        static constexpr std::wstring_view ViewName = L"GyroHeadingTrueNorthTimeseriesView";

        static constexpr SQLUSMALLINT GYRODEVICE_FIELD_ID = 6;

        GyroHeadingTrueNorthTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroHeadingTrueNorthTimeseries;
        }

        Guid GyroDevice( ) const
        {
            return gyroDevice_;
        }
        void SetGyroDevice( const Guid& gyroDevice )
        {
            gyroDevice_ = gyroDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, GYRODEVICE_FIELD_ID, &gyroDevice_);
        }

    };

    class GyroPitchTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid gyroDevice_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[GyroDevice]";
        static constexpr std::wstring_view ViewName = L"GyroPitchTimeseriesView";

        static constexpr SQLUSMALLINT GYRODEVICE_FIELD_ID = 6;

        GyroPitchTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroPitchTimeseries;
        }

        Guid GyroDevice( ) const
        {
            return gyroDevice_;
        }
        void SetGyroDevice( const Guid& gyroDevice )
        {
            gyroDevice_ = gyroDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, GYRODEVICE_FIELD_ID, &gyroDevice_);
        }

    };

    class GyroRateOfTurnTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid gyroDevice_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[GyroDevice]";
        static constexpr std::wstring_view ViewName = L"GyroRateOfTurnTimeseriesView";

        static constexpr SQLUSMALLINT GYRODEVICE_FIELD_ID = 6;

        GyroRateOfTurnTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroRateOfTurnTimeseries;
        }

        Guid GyroDevice( ) const
        {
            return gyroDevice_;
        }
        void SetGyroDevice( const Guid& gyroDevice )
        {
            gyroDevice_ = gyroDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, GYRODEVICE_FIELD_ID, &gyroDevice_);
        }

    };

    class GyroRollTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid gyroDevice_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[GyroDevice]";
        static constexpr std::wstring_view ViewName = L"GyroRollTimeseriesView";

        static constexpr SQLUSMALLINT GYRODEVICE_FIELD_ID = 6;

        GyroRollTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroRollTimeseries;
        }

        Guid GyroDevice( ) const
        {
            return gyroDevice_;
        }
        void SetGyroDevice( const Guid& gyroDevice )
        {
            gyroDevice_ = gyroDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, GYRODEVICE_FIELD_ID, &gyroDevice_);
        }

    };

    class GyroSpeedTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid gyroDevice_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[GyroDevice]";
        static constexpr std::wstring_view ViewName = L"GyroSpeedTimeseriesView";

        static constexpr SQLUSMALLINT GYRODEVICE_FIELD_ID = 6;

        GyroSpeedTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GyroSpeedTimeseries;
        }

        Guid GyroDevice( ) const
        {
            return gyroDevice_;
        }
        void SetGyroDevice( const Guid& gyroDevice )
        {
            gyroDevice_ = gyroDevice;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, GYRODEVICE_FIELD_ID, &gyroDevice_);
        }

    };

    class RadarLatitudeTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarLatitudeTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarLatitudeTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarLatitudeTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarLongitudeTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarLongitudeTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarLongitudeTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarLongitudeTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadomeDewPointTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid radome_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radome]";
        static constexpr std::wstring_view ViewName = L"RadomeDewPointTimeseriesView";

        static constexpr SQLUSMALLINT RADOME_FIELD_ID = 6;

        RadomeDewPointTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadomeDewPointTimeseries;
        }

        Guid Radome( ) const
        {
            return radome_;
        }
        void SetRadome( const Guid& radome )
        {
            radome_ = radome;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADOME_FIELD_ID, &radome_);
        }

    };

    class RadomePressureTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid radome_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radome]";
        static constexpr std::wstring_view ViewName = L"RadomePressureTimeseriesView";

        static constexpr SQLUSMALLINT RADOME_FIELD_ID = 6;

        RadomePressureTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadomePressureTimeseries;
        }

        Guid Radome( ) const
        {
            return radome_;
        }
        void SetRadome( const Guid& radome )
        {
            radome_ = radome;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADOME_FIELD_ID, &radome_);
        }

    };

    class RadomeTemperatureTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid radome_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radome]";
        static constexpr std::wstring_view ViewName = L"RadomeTemperatureTimeseriesView";

        static constexpr SQLUSMALLINT RADOME_FIELD_ID = 6;

        RadomeTemperatureTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadomeTemperatureTimeseries;
        }

        Guid Radome( ) const
        {
            return radome_;
        }
        void SetRadome( const Guid& radome )
        {
            radome_ = radome;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADOME_FIELD_ID, &radome_);
        }

    };

    class VesselDraughtTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid vessel_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Vessel]";
        static constexpr std::wstring_view ViewName = L"VesselDraughtTimeseriesView";

        static constexpr SQLUSMALLINT VESSEL_FIELD_ID = 6;

        VesselDraughtTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::VesselDraughtTimeseries;
        }

        Guid Vessel( ) const
        {
            return vessel_;
        }
        void SetVessel( const Guid& vessel )
        {
            vessel_ = vessel;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VESSEL_FIELD_ID, &vessel_);
        }

    };

    class ViewLatitudeTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid view_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[View]";
        static constexpr std::wstring_view ViewName = L"ViewLatitudeTimeseriesView";

        static constexpr SQLUSMALLINT VIEW_FIELD_ID = 6;

        ViewLatitudeTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ViewLatitudeTimeseries;
        }

        Guid View( ) const
        {
            return view_;
        }
        void SetView( const Guid& view )
        {
            view_ = view;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VIEW_FIELD_ID, &view_);
        }

    };

    class ViewLongitudeTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid view_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[View]";
        static constexpr std::wstring_view ViewName = L"ViewLongitudeTimeseriesView";

        static constexpr SQLUSMALLINT VIEW_FIELD_ID = 6;

        ViewLongitudeTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ViewLongitudeTimeseries;
        }

        Guid View( ) const
        {
            return view_;
        }
        void SetView( const Guid& view )
        {
            view_ = view;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VIEW_FIELD_ID, &view_);
        }

    };

    class ViewZoomLevelTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid view_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[View]";
        static constexpr std::wstring_view ViewName = L"ViewZoomLevelTimeseriesView";

        static constexpr SQLUSMALLINT VIEW_FIELD_ID = 6;

        ViewZoomLevelTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ViewZoomLevelTimeseries;
        }

        Guid View( ) const
        {
            return view_;
        }
        void SetView( const Guid& view )
        {
            view_ = view;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VIEW_FIELD_ID, &view_);
        }

    };

    class WeatherStationAbsoluteHumidityTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid weatherStation_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[WeatherStation]";
        static constexpr std::wstring_view ViewName = L"WeatherStationAbsoluteHumidityTimeseriesView";

        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 6;

        WeatherStationAbsoluteHumidityTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationAbsoluteHumidityTimeseries;
        }

        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
        }

    };

    class WeatherStationAirTemperatureTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid weatherStation_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[WeatherStation]";
        static constexpr std::wstring_view ViewName = L"WeatherStationAirTemperatureTimeseriesView";

        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 6;

        WeatherStationAirTemperatureTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationAirTemperatureTimeseries;
        }

        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
        }

    };

    class WeatherStationBarometricPressureTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid weatherStation_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[WeatherStation]";
        static constexpr std::wstring_view ViewName = L"WeatherStationBarometricPressureTimeseriesView";

        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 6;

        WeatherStationBarometricPressureTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationBarometricPressureTimeseries;
        }

        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
        }

    };

    class WeatherStationDewPointTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid weatherStation_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[WeatherStation]";
        static constexpr std::wstring_view ViewName = L"WeatherStationDewPointTimeseriesView";

        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 6;

        WeatherStationDewPointTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationDewPointTimeseries;
        }

        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
        }

    };

    class WeatherStationRelativeHumidityTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid weatherStation_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[WeatherStation]";
        static constexpr std::wstring_view ViewName = L"WeatherStationRelativeHumidityTimeseriesView";

        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 6;

        WeatherStationRelativeHumidityTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationRelativeHumidityTimeseries;
        }

        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
        }

    };

    class WeatherStationWaterTemperatureTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid weatherStation_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[WeatherStation]";
        static constexpr std::wstring_view ViewName = L"WeatherStationWaterTemperatureTimeseriesView";

        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 6;

        WeatherStationWaterTemperatureTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationWaterTemperatureTimeseries;
        }

        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
        }

    };

    class WeatherStationWindDirectionTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid weatherStation_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[WeatherStation]";
        static constexpr std::wstring_view ViewName = L"WeatherStationWindDirectionTimeseriesView";

        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 6;

        WeatherStationWindDirectionTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationWindDirectionTimeseries;
        }

        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
        }

    };

    class WeatherStationWindSpeedTimeseriesColumnData : public DoubleTimeseriesColumnData
    {
        Guid weatherStation_;
    public:
        using Base = DoubleTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[WeatherStation]";
        static constexpr std::wstring_view ViewName = L"WeatherStationWindSpeedTimeseriesView";

        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 6;

        WeatherStationWindSpeedTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationWindSpeedTimeseries;
        }

        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
        }

    };

    class GeoPosition2DTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"GeoPosition2DTimeseriesView";

        GeoPosition2DTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GeoPosition2DTimeseries;
        }

    };

    class AisAidToNavigationPositionTimeseriesColumnData : public GeoPosition2DTimeseriesColumnData
    {
        Guid aidToNavigation_;
    public:
        using Base = GeoPosition2DTimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[AidToNavigation]";
        static constexpr std::wstring_view ViewName = L"AisAidToNavigationPositionTimeseriesView";

        static constexpr SQLUSMALLINT AIDTONAVIGATION_FIELD_ID = 6;

        AisAidToNavigationPositionTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::AisAidToNavigationPositionTimeseries;
        }

        Guid AidToNavigation( ) const
        {
            return aidToNavigation_;
        }
        void SetAidToNavigation( const Guid& aidToNavigation )
        {
            aidToNavigation_ = aidToNavigation;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, AIDTONAVIGATION_FIELD_ID, &aidToNavigation_);
        }

    };

    class GeoPosition3DTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"GeoPosition3DTimeseriesView";

        GeoPosition3DTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GeoPosition3DTimeseries;
        }

    };

    class GuidTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"GuidTimeseriesView";

        GuidTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::GuidTimeseries;
        }

    };

    class Int16TimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"Int16TimeseriesView";

        Int16TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int16Timeseries;
        }

    };

    class Int32TimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"Int32TimeseriesView";

        Int32TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int32Timeseries;
        }

    };

    class RadarAzimuthOffsetTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarAzimuthOffsetTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarAzimuthOffsetTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarAzimuthOffsetTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarFastTimeConstantLevelTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarFastTimeConstantLevelTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarFastTimeConstantLevelTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarFastTimeConstantLevelTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarFastTimeConstantModeTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarFastTimeConstantModeTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarFastTimeConstantModeTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarFastTimeConstantModeTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarPulseTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarPulseTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarPulseTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarPulseTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarSector1EndTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarSector1EndTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarSector1EndTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarSector1EndTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarSector1StartTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarSector1StartTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarSector1StartTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarSector1StartTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarSector2EndTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarSector2EndTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarSector2EndTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarSector2EndTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarSector2StartTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarSector2StartTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarSector2StartTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarSector2StartTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarSensitivityTimeControlLevelTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarSensitivityTimeControlLevelTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarSensitivityTimeControlLevelTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarSensitivityTimeControlLevelTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class RadarTuningTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid radar_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radar]";
        static constexpr std::wstring_view ViewName = L"RadarTuningTimeseriesView";

        static constexpr SQLUSMALLINT RADAR_FIELD_ID = 6;

        RadarTuningTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadarTuningTimeseries;
        }

        Guid Radar( ) const
        {
            return radar_;
        }
        void SetRadar( const Guid& radar )
        {
            radar_ = radar;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADAR_FIELD_ID, &radar_);
        }

    };

    class VesselPersonsOnBoardTimeseriesColumnData : public Int32TimeseriesColumnData
    {
        Guid vessel_;
    public:
        using Base = Int32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Vessel]";
        static constexpr std::wstring_view ViewName = L"VesselPersonsOnBoardTimeseriesView";

        static constexpr SQLUSMALLINT VESSEL_FIELD_ID = 6;

        VesselPersonsOnBoardTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::VesselPersonsOnBoardTimeseries;
        }

        Guid Vessel( ) const
        {
            return vessel_;
        }
        void SetVessel( const Guid& vessel )
        {
            vessel_ = vessel;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, VESSEL_FIELD_ID, &vessel_);
        }

    };

    class Int64TimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"Int64TimeseriesView";

        Int64TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Int64Timeseries;
        }

    };

    class Position2DTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"Position2DTimeseriesView";

        Position2DTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Position2DTimeseries;
        }

    };

    class Position3DTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"Position3DTimeseriesView";

        Position3DTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Position3DTimeseries;
        }

    };

    class ReferenceTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"ReferenceTimeseriesView";

        ReferenceTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ReferenceTimeseries;
        }

    };

    class SByteTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"SByteTimeseriesView";

        SByteTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SByteTimeseries;
        }

    };

    class SingleTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"SingleTimeseriesView";

        SingleTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::SingleTimeseries;
        }

    };

    class StringTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"StringTimeseriesView";

        StringTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::StringTimeseries;
        }

    };

    class TimeSpanTimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"TimeSpanTimeseriesView";

        TimeSpanTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeSpanTimeseries;
        }

    };

    class UInt16TimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"UInt16TimeseriesView";

        UInt16TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt16Timeseries;
        }

    };

    class UInt32TimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"UInt32TimeseriesView";

        UInt32TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt32Timeseries;
        }

    };

    class RadomeStatusTimeseriesColumnData : public UInt32TimeseriesColumnData
    {
        Guid radome_;
    public:
        using Base = UInt32TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention],[Radome]";
        static constexpr std::wstring_view ViewName = L"RadomeStatusTimeseriesView";

        static constexpr SQLUSMALLINT RADOME_FIELD_ID = 6;

        RadomeStatusTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::RadomeStatusTimeseries;
        }

        Guid Radome( ) const
        {
            return radome_;
        }
        void SetRadome( const Guid& radome )
        {
            radome_ = radome;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADOME_FIELD_ID, &radome_);
        }

    };

    class UInt64TimeseriesColumnData : public TimeseriesColumnData
    {
    public:
        using Base = TimeseriesColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name],[MaxRetention]";
        static constexpr std::wstring_view ViewName = L"UInt64TimeseriesView";

        UInt64TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt64Timeseries;
        }

    };

    class TimeseriesCatalogColumnData : public TimeseriesCatalogElementColumnData
    {
    public:
        using Base = TimeseriesCatalogElementColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Catalog],[Name]";
        static constexpr std::wstring_view ViewName = L"TimeseriesCatalogView";

        TimeseriesCatalogColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeseriesCatalog;
        }

    };

    class TimeseriesInfoColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        DateTime firstTimestamp_;
        SQLLEN firstTimestampNullIndicator_ = SQL_NULL_DATA;
        DateTime lastTimestamp_;
        SQLLEN lastTimestampNullIndicator_ = SQL_NULL_DATA;
        Int64 count_ = 0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[FirstTimestamp],[LastTimestamp],[Count]";
        static constexpr std::wstring_view ViewName = L"TimeseriesInfoView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT FIRSTTIMESTAMP_FIELD_ID = 3;
        static constexpr SQLUSMALLINT LASTTIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COUNT_FIELD_ID = 5;

        TimeseriesInfoColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeseriesInfo;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        DateTime FirstTimestamp( ) const
        {
            return firstTimestamp_;
        }
        void SetFirstTimestamp( const DateTime& firstTimestamp )
        {
            firstTimestamp_ = firstTimestamp;
        }
        DateTime LastTimestamp( ) const
        {
            return lastTimestamp_;
        }
        void SetLastTimestamp( const DateTime& lastTimestamp )
        {
            lastTimestamp_ = lastTimestamp;
        }
        Int64 Count( ) const
        {
            return count_;
        }
        void SetCount( Int64 count )
        {
            count_ = count;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, FIRSTTIMESTAMP_FIELD_ID, &firstTimestamp_, &firstTimestampNullIndicator_);
            Bind(statement, LASTTIMESTAMP_FIELD_ID, &lastTimestamp_, &lastTimestampNullIndicator_);
            Bind(statement, COUNT_FIELD_ID, &count_);
        }

    };

    class TimeSpanTimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        TimeSpan value_;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"TimeSpanTimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        TimeSpanTimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TimeSpanTimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        TimeSpan Value( ) const
        {
            return value_;
        }
        void SetValue( const TimeSpan& value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class TrackableItemTrackLinkColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid item_;
        Guid track_;
        DateTime start_;
        DateTime end_;
        SQLLEN endNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Item],[Track],[Start],[End]";
        static constexpr std::wstring_view ViewName = L"TrackableItemTrackLinkView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ITEM_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TRACK_FIELD_ID = 4;
        static constexpr SQLUSMALLINT START_FIELD_ID = 5;
        static constexpr SQLUSMALLINT END_FIELD_ID = 6;

        TrackableItemTrackLinkColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TrackableItemTrackLink;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Item( ) const
        {
            return item_;
        }
        void SetItem( const Guid& item )
        {
            item_ = item;
        }
        Guid Track( ) const
        {
            return track_;
        }
        void SetTrack( const Guid& track )
        {
            track_ = track;
        }
        DateTime Start( ) const
        {
            return start_;
        }
        void SetStart( const DateTime& start )
        {
            start_ = start;
        }
        DateTime End( ) const
        {
            return end_;
        }
        void SetEnd( const DateTime& end )
        {
            end_ = end;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ITEM_FIELD_ID, &item_);
            Bind(statement, TRACK_FIELD_ID, &track_);
            Bind(statement, START_FIELD_ID, &start_);
            Bind(statement, END_FIELD_ID, &end_, &endNullIndicator_);
        }

    };

    class TrackBaseColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid tracker_;
        Int64 trackNumber_ = 0;
        DateTime timestamp_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Tracker],[TrackNumber],[Timestamp]";
        static constexpr std::wstring_view ViewName = L"TrackBaseView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TRACKER_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TRACKNUMBER_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 5;

        TrackBaseColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TrackBase;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Tracker( ) const
        {
            return tracker_;
        }
        void SetTracker( const Guid& tracker )
        {
            tracker_ = tracker;
        }
        Int64 TrackNumber( ) const
        {
            return trackNumber_;
        }
        void SetTrackNumber( Int64 trackNumber )
        {
            trackNumber_ = trackNumber;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TRACKER_FIELD_ID, &tracker_);
            Bind(statement, TRACKNUMBER_FIELD_ID, &trackNumber_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
        }

    };

    class TrackColumnData : public TrackBaseColumnData
    {
    public:
        using Base = TrackBaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Tracker],[TrackNumber],[Timestamp]";
        static constexpr std::wstring_view ViewName = L"TrackView";

        TrackColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Track;
        }

    };

    class Track3DColumnData : public TrackBaseColumnData
    {
    public:
        using Base = TrackBaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Tracker],[TrackNumber],[Timestamp]";
        static constexpr std::wstring_view ViewName = L"Track3DView";

        Track3DColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Track3D;
        }

    };

    class TrackerFilterParametersColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid tracker_;
        std::array<wchar_t,101> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Tracker],[Name]";
        static constexpr std::wstring_view ViewName = L"TrackerFilterParametersView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TRACKER_FIELD_ID = 3;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 4;

        TrackerFilterParametersColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TrackerFilterParameters;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Tracker( ) const
        {
            return tracker_;
        }
        void SetTracker( const Guid& tracker )
        {
            tracker_ = tracker;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TRACKER_FIELD_ID, &tracker_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class TrackerFilterParametersConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid parameters_;
        DateTime timestamp_;
        bool useNaivePredictor_ = false;
        Int32 numberOfPoints_ = 0;
        Int32 windowSize_ = 0;
        Int32 stabilizeCount_ = 0;
        Int32 maxBadPoints_ = 0;
        Data::TrackerFilterModelType modelType_ = Data::TrackerFilterModelType::Unknown;
        double sigmaR_ = 0.0;
        double sigmaAcc_ = 0.0;
        double tauVel_ = 0.0;
        double tauAcc_ = 0.0;
        double deltaRMin_ = 0.0;
        double deltaVMax_ = 0.0;
        double deltaAMax_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Parameters],[Timestamp],[UseNaivePredictor],[NumberOfPoints],[WindowSize],[StabilizeCount],[MaxBadPoints],[ModelType],[SigmaR],[SigmaAcc],[TauVel],[TauAcc],[DeltaRMin],[DeltaVMax],[DeltaAMax]";
        static constexpr std::wstring_view ViewName = L"TrackerFilterParametersConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT PARAMETERS_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT USENAIVEPREDICTOR_FIELD_ID = 5;
        static constexpr SQLUSMALLINT NUMBEROFPOINTS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT WINDOWSIZE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT STABILIZECOUNT_FIELD_ID = 8;
        static constexpr SQLUSMALLINT MAXBADPOINTS_FIELD_ID = 9;
        static constexpr SQLUSMALLINT MODELTYPE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT SIGMAR_FIELD_ID = 11;
        static constexpr SQLUSMALLINT SIGMAACC_FIELD_ID = 12;
        static constexpr SQLUSMALLINT TAUVEL_FIELD_ID = 13;
        static constexpr SQLUSMALLINT TAUACC_FIELD_ID = 14;
        static constexpr SQLUSMALLINT DELTARMIN_FIELD_ID = 15;
        static constexpr SQLUSMALLINT DELTAVMAX_FIELD_ID = 16;
        static constexpr SQLUSMALLINT DELTAAMAX_FIELD_ID = 17;

        TrackerFilterParametersConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TrackerFilterParametersConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Parameters( ) const
        {
            return parameters_;
        }
        void SetParameters( const Guid& parameters )
        {
            parameters_ = parameters;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        bool UseNaivePredictor( ) const
        {
            return useNaivePredictor_;
        }
        void SetUseNaivePredictor( bool useNaivePredictor )
        {
            useNaivePredictor_ = useNaivePredictor;
        }
        Int32 NumberOfPoints( ) const
        {
            return numberOfPoints_;
        }
        void SetNumberOfPoints( Int32 numberOfPoints )
        {
            numberOfPoints_ = numberOfPoints;
        }
        Int32 WindowSize( ) const
        {
            return windowSize_;
        }
        void SetWindowSize( Int32 windowSize )
        {
            windowSize_ = windowSize;
        }
        Int32 StabilizeCount( ) const
        {
            return stabilizeCount_;
        }
        void SetStabilizeCount( Int32 stabilizeCount )
        {
            stabilizeCount_ = stabilizeCount;
        }
        Int32 MaxBadPoints( ) const
        {
            return maxBadPoints_;
        }
        void SetMaxBadPoints( Int32 maxBadPoints )
        {
            maxBadPoints_ = maxBadPoints;
        }
        Data::TrackerFilterModelType ModelType( ) const
        {
            return modelType_;
        }
        void SetModelType( Data::TrackerFilterModelType modelType )
        {
            modelType_ = modelType;
        }
        double SigmaR( ) const
        {
            return sigmaR_;
        }
        void SetSigmaR( double sigmaR )
        {
            sigmaR_ = sigmaR;
        }
        double SigmaAcc( ) const
        {
            return sigmaAcc_;
        }
        void SetSigmaAcc( double sigmaAcc )
        {
            sigmaAcc_ = sigmaAcc;
        }
        double TauVel( ) const
        {
            return tauVel_;
        }
        void SetTauVel( double tauVel )
        {
            tauVel_ = tauVel;
        }
        double TauAcc( ) const
        {
            return tauAcc_;
        }
        void SetTauAcc( double tauAcc )
        {
            tauAcc_ = tauAcc;
        }
        double DeltaRMin( ) const
        {
            return deltaRMin_;
        }
        void SetDeltaRMin( double deltaRMin )
        {
            deltaRMin_ = deltaRMin;
        }
        double DeltaVMax( ) const
        {
            return deltaVMax_;
        }
        void SetDeltaVMax( double deltaVMax )
        {
            deltaVMax_ = deltaVMax;
        }
        double DeltaAMax( ) const
        {
            return deltaAMax_;
        }
        void SetDeltaAMax( double deltaAMax )
        {
            deltaAMax_ = deltaAMax;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, PARAMETERS_FIELD_ID, &parameters_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, USENAIVEPREDICTOR_FIELD_ID, &useNaivePredictor_);
            Bind(statement, NUMBEROFPOINTS_FIELD_ID, &numberOfPoints_);
            Bind(statement, WINDOWSIZE_FIELD_ID, &windowSize_);
            Bind(statement, STABILIZECOUNT_FIELD_ID, &stabilizeCount_);
            Bind(statement, MAXBADPOINTS_FIELD_ID, &maxBadPoints_);
            Bind(statement, MODELTYPE_FIELD_ID, &modelType_);
            Bind(statement, SIGMAR_FIELD_ID, &sigmaR_);
            Bind(statement, SIGMAACC_FIELD_ID, &sigmaAcc_);
            Bind(statement, TAUVEL_FIELD_ID, &tauVel_);
            Bind(statement, TAUACC_FIELD_ID, &tauAcc_);
            Bind(statement, DELTARMIN_FIELD_ID, &deltaRMin_);
            Bind(statement, DELTAVMAX_FIELD_ID, &deltaVMax_);
            Bind(statement, DELTAAMAX_FIELD_ID, &deltaAMax_);
        }

    };

    class TrackInfoColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        DateTime firstTimestamp_;
        SQLLEN firstTimestampNullIndicator_ = SQL_NULL_DATA;
        DateTime lastTimestamp_;
        SQLLEN lastTimestampNullIndicator_ = SQL_NULL_DATA;
        Int64 count_ = 0;
        double northWestLatitude_ = 0.0;
        SQLLEN northWestLatitudeNullIndicator_ = SQL_NULL_DATA;
        double northWestLongitude_ = 0.0;
        SQLLEN northWestLongitudeNullIndicator_ = SQL_NULL_DATA;
        double southEastLatitude_ = 0.0;
        SQLLEN southEastLatitudeNullIndicator_ = SQL_NULL_DATA;
        double southEastLongitude_ = 0.0;
        SQLLEN southEastLongitudeNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[FirstTimestamp],[LastTimestamp],[Count],[NorthWestLatitude],[NorthWestLongitude],[SouthEastLatitude],[SouthEastLongitude]";
        static constexpr std::wstring_view ViewName = L"TrackInfoView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT FIRSTTIMESTAMP_FIELD_ID = 3;
        static constexpr SQLUSMALLINT LASTTIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COUNT_FIELD_ID = 5;
        static constexpr SQLUSMALLINT NORTHWESTLATITUDE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT NORTHWESTLONGITUDE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT SOUTHEASTLATITUDE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SOUTHEASTLONGITUDE_FIELD_ID = 9;

        TrackInfoColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TrackInfo;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        DateTime FirstTimestamp( ) const
        {
            return firstTimestamp_;
        }
        void SetFirstTimestamp( const DateTime& firstTimestamp )
        {
            firstTimestamp_ = firstTimestamp;
        }
        DateTime LastTimestamp( ) const
        {
            return lastTimestamp_;
        }
        void SetLastTimestamp( const DateTime& lastTimestamp )
        {
            lastTimestamp_ = lastTimestamp;
        }
        Int64 Count( ) const
        {
            return count_;
        }
        void SetCount( Int64 count )
        {
            count_ = count;
        }
        double NorthWestLatitude( ) const
        {
            return northWestLatitude_;
        }
        void SetNorthWestLatitude( double northWestLatitude )
        {
            northWestLatitude_ = northWestLatitude;
        }
        double NorthWestLongitude( ) const
        {
            return northWestLongitude_;
        }
        void SetNorthWestLongitude( double northWestLongitude )
        {
            northWestLongitude_ = northWestLongitude;
        }
        double SouthEastLatitude( ) const
        {
            return southEastLatitude_;
        }
        void SetSouthEastLatitude( double southEastLatitude )
        {
            southEastLatitude_ = southEastLatitude;
        }
        double SouthEastLongitude( ) const
        {
            return southEastLongitude_;
        }
        void SetSouthEastLongitude( double southEastLongitude )
        {
            southEastLongitude_ = southEastLongitude;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, FIRSTTIMESTAMP_FIELD_ID, &firstTimestamp_, &firstTimestampNullIndicator_);
            Bind(statement, LASTTIMESTAMP_FIELD_ID, &lastTimestamp_, &lastTimestampNullIndicator_);
            Bind(statement, COUNT_FIELD_ID, &count_);
            Bind(statement, NORTHWESTLATITUDE_FIELD_ID, &northWestLatitude_, &northWestLatitudeNullIndicator_);
            Bind(statement, NORTHWESTLONGITUDE_FIELD_ID, &northWestLongitude_, &northWestLongitudeNullIndicator_);
            Bind(statement, SOUTHEASTLATITUDE_FIELD_ID, &southEastLatitude_, &southEastLatitudeNullIndicator_);
            Bind(statement, SOUTHEASTLONGITUDE_FIELD_ID, &southEastLongitude_, &southEastLongitudeNullIndicator_);
        }

    };

    class TrackingServiceOptionsColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        DateTime timestamp_;
        TimeSpan timerInterval_;
        TimeSpan maxAgeOfCurrentTrackValue_;
        double falseThreshold_ = 0.0;
        double distanceThreshold_ = 0.0;
        double distanceUnmergeThreshold_ = 0.0;
        Int64 unmergeLatency_ = 0;
        bool kalmanFiltering_ = false;
        double maxCourseDeviation_ = 0.0;
        double maxSpeedDeviation_ = 0.0;
        double minimumSpeedThreshold_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timestamp],[TimerInterval],[MaxAgeOfCurrentTrackValue],[FalseThreshold],[DistanceThreshold],[DistanceUnmergeThreshold],[UnmergeLatency],[KalmanFiltering],[MaxCourseDeviation],[MaxSpeedDeviation],[MinimumSpeedThreshold]";
        static constexpr std::wstring_view ViewName = L"TrackingServiceOptionsView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMERINTERVAL_FIELD_ID = 4;
        static constexpr SQLUSMALLINT MAXAGEOFCURRENTTRACKVALUE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT FALSETHRESHOLD_FIELD_ID = 6;
        static constexpr SQLUSMALLINT DISTANCETHRESHOLD_FIELD_ID = 7;
        static constexpr SQLUSMALLINT DISTANCEUNMERGETHRESHOLD_FIELD_ID = 8;
        static constexpr SQLUSMALLINT UNMERGELATENCY_FIELD_ID = 9;
        static constexpr SQLUSMALLINT KALMANFILTERING_FIELD_ID = 10;
        static constexpr SQLUSMALLINT MAXCOURSEDEVIATION_FIELD_ID = 11;
        static constexpr SQLUSMALLINT MAXSPEEDDEVIATION_FIELD_ID = 12;
        static constexpr SQLUSMALLINT MINIMUMSPEEDTHRESHOLD_FIELD_ID = 13;

        TrackingServiceOptionsColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TrackingServiceOptions;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        TimeSpan TimerInterval( ) const
        {
            return timerInterval_;
        }
        void SetTimerInterval( const TimeSpan& timerInterval )
        {
            timerInterval_ = timerInterval;
        }
        TimeSpan MaxAgeOfCurrentTrackValue( ) const
        {
            return maxAgeOfCurrentTrackValue_;
        }
        void SetMaxAgeOfCurrentTrackValue( const TimeSpan& maxAgeOfCurrentTrackValue )
        {
            maxAgeOfCurrentTrackValue_ = maxAgeOfCurrentTrackValue;
        }
        double FalseThreshold( ) const
        {
            return falseThreshold_;
        }
        void SetFalseThreshold( double falseThreshold )
        {
            falseThreshold_ = falseThreshold;
        }
        double DistanceThreshold( ) const
        {
            return distanceThreshold_;
        }
        void SetDistanceThreshold( double distanceThreshold )
        {
            distanceThreshold_ = distanceThreshold;
        }
        double DistanceUnmergeThreshold( ) const
        {
            return distanceUnmergeThreshold_;
        }
        void SetDistanceUnmergeThreshold( double distanceUnmergeThreshold )
        {
            distanceUnmergeThreshold_ = distanceUnmergeThreshold;
        }
        Int64 UnmergeLatency( ) const
        {
            return unmergeLatency_;
        }
        void SetUnmergeLatency( Int64 unmergeLatency )
        {
            unmergeLatency_ = unmergeLatency;
        }
        bool KalmanFiltering( ) const
        {
            return kalmanFiltering_;
        }
        void SetKalmanFiltering( bool kalmanFiltering )
        {
            kalmanFiltering_ = kalmanFiltering;
        }
        double MaxCourseDeviation( ) const
        {
            return maxCourseDeviation_;
        }
        void SetMaxCourseDeviation( double maxCourseDeviation )
        {
            maxCourseDeviation_ = maxCourseDeviation;
        }
        double MaxSpeedDeviation( ) const
        {
            return maxSpeedDeviation_;
        }
        void SetMaxSpeedDeviation( double maxSpeedDeviation )
        {
            maxSpeedDeviation_ = maxSpeedDeviation;
        }
        double MinimumSpeedThreshold( ) const
        {
            return minimumSpeedThreshold_;
        }
        void SetMinimumSpeedThreshold( double minimumSpeedThreshold )
        {
            minimumSpeedThreshold_ = minimumSpeedThreshold;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, TIMERINTERVAL_FIELD_ID, &timerInterval_);
            Bind(statement, MAXAGEOFCURRENTTRACKVALUE_FIELD_ID, &maxAgeOfCurrentTrackValue_);
            Bind(statement, FALSETHRESHOLD_FIELD_ID, &falseThreshold_);
            Bind(statement, DISTANCETHRESHOLD_FIELD_ID, &distanceThreshold_);
            Bind(statement, DISTANCEUNMERGETHRESHOLD_FIELD_ID, &distanceUnmergeThreshold_);
            Bind(statement, UNMERGELATENCY_FIELD_ID, &unmergeLatency_);
            Bind(statement, KALMANFILTERING_FIELD_ID, &kalmanFiltering_);
            Bind(statement, MAXCOURSEDEVIATION_FIELD_ID, &maxCourseDeviation_);
            Bind(statement, MAXSPEEDDEVIATION_FIELD_ID, &maxSpeedDeviation_);
            Bind(statement, MINIMUMSPEEDTHRESHOLD_FIELD_ID, &minimumSpeedThreshold_);
        }

    };

    class TrackLinkColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid primary_;
        Guid secondary_;
        DateTime start_;
        DateTime end_;
        SQLLEN endNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Primary],[Secondary],[Start],[End]";
        static constexpr std::wstring_view ViewName = L"TrackLinkView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT PRIMARY_FIELD_ID = 3;
        static constexpr SQLUSMALLINT SECONDARY_FIELD_ID = 4;
        static constexpr SQLUSMALLINT START_FIELD_ID = 5;
        static constexpr SQLUSMALLINT END_FIELD_ID = 6;

        TrackLinkColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TrackLink;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Primary( ) const
        {
            return primary_;
        }
        void SetPrimary( const Guid& primary )
        {
            primary_ = primary;
        }
        Guid Secondary( ) const
        {
            return secondary_;
        }
        void SetSecondary( const Guid& secondary )
        {
            secondary_ = secondary;
        }
        DateTime Start( ) const
        {
            return start_;
        }
        void SetStart( const DateTime& start )
        {
            start_ = start;
        }
        DateTime End( ) const
        {
            return end_;
        }
        void SetEnd( const DateTime& end )
        {
            end_ = end;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, PRIMARY_FIELD_ID, &primary_);
            Bind(statement, SECONDARY_FIELD_ID, &secondary_);
            Bind(statement, START_FIELD_ID, &start_);
            Bind(statement, END_FIELD_ID, &end_, &endNullIndicator_);
        }

    };

    class TrackValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid track_;
        DateTime timestamp_;
        Data::TrackFlags flags_ = Data::TrackFlags::None;
        Data::TrackStatus status_ = Data::TrackStatus::Unknown;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double speed_ = 0.0;
        double course_ = 0.0;
        double heading_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Track],[Timestamp],[Flags],[Status],[Latitude],[Longitude],[Speed],[Course],[Heading]";
        static constexpr std::wstring_view ViewName = L"TrackValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TRACK_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT FLAGS_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SPEED_FIELD_ID = 9;
        static constexpr SQLUSMALLINT COURSE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT HEADING_FIELD_ID = 11;

        TrackValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TrackValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Track( ) const
        {
            return track_;
        }
        void SetTrack( const Guid& track )
        {
            track_ = track;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::TrackFlags Flags( ) const
        {
            return flags_;
        }
        void SetFlags( Data::TrackFlags flags )
        {
            flags_ = flags;
        }
        Data::TrackStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::TrackStatus status )
        {
            status_ = status;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Speed( ) const
        {
            return speed_;
        }
        void SetSpeed( double speed )
        {
            speed_ = speed;
        }
        double Course( ) const
        {
            return course_;
        }
        void SetCourse( double course )
        {
            course_ = course;
        }
        double Heading( ) const
        {
            return heading_;
        }
        void SetHeading( double heading )
        {
            heading_ = heading;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TRACK_FIELD_ID, &track_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, FLAGS_FIELD_ID, &flags_);
            Bind(statement, STATUS_FIELD_ID, &status_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, SPEED_FIELD_ID, &speed_);
            Bind(statement, COURSE_FIELD_ID, &course_);
            Bind(statement, HEADING_FIELD_ID, &heading_);
        }

    };

    class TrackValue3DColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid track_;
        DateTime timestamp_;
        Data::TrackFlags3D flags_ = Data::TrackFlags3D::None;
        UInt32 status_ = 0;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double altitude_ = 0.0;
        double speed_ = 0.0;
        double course_ = 0.0;
        double rateOfClimb_ = 0.0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Track],[Timestamp],[Flags],[Status],[Latitude],[Longitude],[Altitude],[Speed],[Course],[RateOfClimb]";
        static constexpr std::wstring_view ViewName = L"TrackValue3DView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TRACK_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT FLAGS_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT ALTITUDE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT SPEED_FIELD_ID = 10;
        static constexpr SQLUSMALLINT COURSE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT RATEOFCLIMB_FIELD_ID = 12;

        TrackValue3DColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::TrackValue3D;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Track( ) const
        {
            return track_;
        }
        void SetTrack( const Guid& track )
        {
            track_ = track;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::TrackFlags3D Flags( ) const
        {
            return flags_;
        }
        void SetFlags( Data::TrackFlags3D flags )
        {
            flags_ = flags;
        }
        UInt32 Status( ) const
        {
            return status_;
        }
        void SetStatus( UInt32 status )
        {
            status_ = status;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Altitude( ) const
        {
            return altitude_;
        }
        void SetAltitude( double altitude )
        {
            altitude_ = altitude;
        }
        double Speed( ) const
        {
            return speed_;
        }
        void SetSpeed( double speed )
        {
            speed_ = speed;
        }
        double Course( ) const
        {
            return course_;
        }
        void SetCourse( double course )
        {
            course_ = course;
        }
        double RateOfClimb( ) const
        {
            return rateOfClimb_;
        }
        void SetRateOfClimb( double rateOfClimb )
        {
            rateOfClimb_ = rateOfClimb;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TRACK_FIELD_ID, &track_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, FLAGS_FIELD_ID, &flags_);
            Bind(statement, STATUS_FIELD_ID, &status_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, ALTITUDE_FIELD_ID, &altitude_);
            Bind(statement, SPEED_FIELD_ID, &speed_);
            Bind(statement, COURSE_FIELD_ID, &course_);
            Bind(statement, RATEOFCLIMB_FIELD_ID, &rateOfClimb_);
        }

    };

    class UInt16TimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        UInt16 value_ = 0;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"UInt16TimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        UInt16TimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt16TimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        UInt16 Value( ) const
        {
            return value_;
        }
        void SetValue( UInt16 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class UInt32TimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        UInt32 value_ = 0;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"UInt32TimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        UInt32TimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt32TimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        UInt32 Value( ) const
        {
            return value_;
        }
        void SetValue( UInt32 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class UInt64TimeseriesValueColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        Int64 value_ = 0;
        SQLLEN valueNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Timeseries],[Timestamp],[Value]";
        static constexpr std::wstring_view ViewName = L"UInt64TimeseriesValueView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TIMESERIES_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT VALUE_FIELD_ID = 5;

        UInt64TimeseriesValueColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::UInt64TimeseriesValue;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Timeseries( ) const
        {
            return timeseries_;
        }
        void SetTimeseries( const Guid& timeseries )
        {
            timeseries_ = timeseries;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Int64 Value( ) const
        {
            return value_;
        }
        void SetValue( Int64 value )
        {
            value_ = value;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TIMESERIES_FIELD_ID, &timeseries_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, VALUE_FIELD_ID, &value_, &valueNullIndicator_);
        }

    };

    class VehicleTypeColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name]";
        static constexpr std::wstring_view ViewName = L"VehicleTypeView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;

        VehicleTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::VehicleType;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
        }

    };

    class VesselTypeColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Int32 code_ = 0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Code]";
        static constexpr std::wstring_view ViewName = L"VesselTypeView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT CODE_FIELD_ID = 4;

        VesselTypeColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::VesselType;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Int32 Code( ) const
        {
            return code_;
        }
        void SetCode( Int32 code )
        {
            code_ = code;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, CODE_FIELD_ID, &code_);
        }

    };

    class ViewColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        Guid latitudeTimeseries_;
        Guid longitudeTimeseries_;
        Guid zoomLevelTimeseries_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[LatitudeTimeseries],[LongitudeTimeseries],[ZoomLevelTimeseries]";
        static constexpr std::wstring_view ViewName = L"ViewView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT LATITUDETIMESERIES_FIELD_ID = 4;
        static constexpr SQLUSMALLINT LONGITUDETIMESERIES_FIELD_ID = 5;
        static constexpr SQLUSMALLINT ZOOMLEVELTIMESERIES_FIELD_ID = 6;

        ViewColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::View;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        Guid LatitudeTimeseries( ) const
        {
            return latitudeTimeseries_;
        }
        void SetLatitudeTimeseries( const Guid& latitudeTimeseries )
        {
            latitudeTimeseries_ = latitudeTimeseries;
        }
        Guid LongitudeTimeseries( ) const
        {
            return longitudeTimeseries_;
        }
        void SetLongitudeTimeseries( const Guid& longitudeTimeseries )
        {
            longitudeTimeseries_ = longitudeTimeseries;
        }
        Guid ZoomLevelTimeseries( ) const
        {
            return zoomLevelTimeseries_;
        }
        void SetZoomLevelTimeseries( const Guid& zoomLevelTimeseries )
        {
            zoomLevelTimeseries_ = zoomLevelTimeseries;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, LATITUDETIMESERIES_FIELD_ID, &latitudeTimeseries_);
            Bind(statement, LONGITUDETIMESERIES_FIELD_ID, &longitudeTimeseries_);
            Bind(statement, ZOOMLEVELTIMESERIES_FIELD_ID, &zoomLevelTimeseries_);
        }

    };

    class ViewCameraLinkColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid view_;
        Guid camera_;
        DateTime start_;
        DateTime end_;
        SQLLEN endNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[View],[Camera],[Start],[End]";
        static constexpr std::wstring_view ViewName = L"ViewCameraLinkView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT VIEW_FIELD_ID = 3;
        static constexpr SQLUSMALLINT CAMERA_FIELD_ID = 4;
        static constexpr SQLUSMALLINT START_FIELD_ID = 5;
        static constexpr SQLUSMALLINT END_FIELD_ID = 6;

        ViewCameraLinkColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ViewCameraLink;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid View( ) const
        {
            return view_;
        }
        void SetView( const Guid& view )
        {
            view_ = view;
        }
        Guid Camera( ) const
        {
            return camera_;
        }
        void SetCamera( const Guid& camera )
        {
            camera_ = camera;
        }
        DateTime Start( ) const
        {
            return start_;
        }
        void SetStart( const DateTime& start )
        {
            start_ = start;
        }
        DateTime End( ) const
        {
            return end_;
        }
        void SetEnd( const DateTime& end )
        {
            end_ = end;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, VIEW_FIELD_ID, &view_);
            Bind(statement, CAMERA_FIELD_ID, &camera_);
            Bind(statement, START_FIELD_ID, &start_);
            Bind(statement, END_FIELD_ID, &end_, &endNullIndicator_);
        }

    };

    class ViewTrackerLinkColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid view_;
        Guid tracker_;
        DateTime start_;
        DateTime end_;
        SQLLEN endNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[View],[Tracker],[Start],[End]";
        static constexpr std::wstring_view ViewName = L"ViewTrackerLinkView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT VIEW_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TRACKER_FIELD_ID = 4;
        static constexpr SQLUSMALLINT START_FIELD_ID = 5;
        static constexpr SQLUSMALLINT END_FIELD_ID = 6;

        ViewTrackerLinkColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ViewTrackerLink;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid View( ) const
        {
            return view_;
        }
        void SetView( const Guid& view )
        {
            view_ = view;
        }
        Guid Tracker( ) const
        {
            return tracker_;
        }
        void SetTracker( const Guid& tracker )
        {
            tracker_ = tracker;
        }
        DateTime Start( ) const
        {
            return start_;
        }
        void SetStart( const DateTime& start )
        {
            start_ = start;
        }
        DateTime End( ) const
        {
            return end_;
        }
        void SetEnd( const DateTime& end )
        {
            end_ = end;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, VIEW_FIELD_ID, &view_);
            Bind(statement, TRACKER_FIELD_ID, &tracker_);
            Bind(statement, START_FIELD_ID, &start_);
            Bind(statement, END_FIELD_ID, &end_, &endNullIndicator_);
        }

    };

    class WeatherStationCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid weatherStation_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[WeatherStation],[Timestamp],[DeviceCommandSourceType],[DeviceCommandSourceId],[Reply]";
        static constexpr std::wstring_view ViewName = L"WeatherStationCommandView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        static constexpr SQLUSMALLINT REPLY_FIELD_ID = 7;

        WeatherStationCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationCommand;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        void SetDeviceCommandSourceType( Data::DeviceCommandSourceType deviceCommandSourceType )
        {
            deviceCommandSourceType_ = deviceCommandSourceType;
        }
        Guid DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        void SetDeviceCommandSourceId( const Guid& deviceCommandSourceId )
        {
            deviceCommandSourceId_ = deviceCommandSourceId;
        }
        Guid Reply( ) const
        {
            return reply_;
        }
        void SetReply( const Guid& reply )
        {
            reply_ = reply;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, DEVICECOMMANDSOURCETYPE_FIELD_ID, &deviceCommandSourceType_);
            Bind(statement, DEVICECOMMANDSOURCEID_FIELD_ID, &deviceCommandSourceId_);
            Bind(statement, REPLY_FIELD_ID, &reply_);
        }

    };

    class WeatherStationCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid weatherStation_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[WeatherStation],[Timestamp],[Command],[Status],[Message]";
        static constexpr std::wstring_view ViewName = L"WeatherStationCommandReplyView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT COMMAND_FIELD_ID = 5;
        static constexpr SQLUSMALLINT STATUS_FIELD_ID = 6;
        static constexpr SQLUSMALLINT MESSAGE_FIELD_ID = 7;

        WeatherStationCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationCommandReply;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        Guid Command( ) const
        {
            return command_;
        }
        void SetCommand( const Guid& command )
        {
            command_ = command;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        void SetStatus( Data::DeviceCommandReplyStatus status )
        {
            status_ = status;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        void SetMessage( const WideString& message )
        {
            Assign(message, message_, messageLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, COMMAND_FIELD_ID, &command_);
            Bind(statement, STATUS_FIELD_ID, &status_);
        }

    };

    class WeatherStationConfigurationColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid weatherStation_;
        DateTime timestamp_;
        TimeSpan noDataTimeOut_;
        TimeSpan sendInterval_;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double gyroOffset_ = 0.0;
        bool enableAveraging_ = false;
        TimeSpan averagingInterval_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[WeatherStation],[Timestamp],[NoDataTimeOut],[SendInterval],[Latitude],[Longitude],[GyroOffset],[EnableAveraging],[AveragingInterval]";
        static constexpr std::wstring_view ViewName = L"WeatherStationConfigurationView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT WEATHERSTATION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;
        static constexpr SQLUSMALLINT NODATATIMEOUT_FIELD_ID = 5;
        static constexpr SQLUSMALLINT SENDINTERVAL_FIELD_ID = 6;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT GYROOFFSET_FIELD_ID = 9;
        static constexpr SQLUSMALLINT ENABLEAVERAGING_FIELD_ID = 10;
        static constexpr SQLUSMALLINT AVERAGINGINTERVAL_FIELD_ID = 11;

        WeatherStationConfigurationColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::WeatherStationConfiguration;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid WeatherStation( ) const
        {
            return weatherStation_;
        }
        void SetWeatherStation( const Guid& weatherStation )
        {
            weatherStation_ = weatherStation;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        TimeSpan NoDataTimeOut( ) const
        {
            return noDataTimeOut_;
        }
        void SetNoDataTimeOut( const TimeSpan& noDataTimeOut )
        {
            noDataTimeOut_ = noDataTimeOut;
        }
        TimeSpan SendInterval( ) const
        {
            return sendInterval_;
        }
        void SetSendInterval( const TimeSpan& sendInterval )
        {
            sendInterval_ = sendInterval;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double GyroOffset( ) const
        {
            return gyroOffset_;
        }
        void SetGyroOffset( double gyroOffset )
        {
            gyroOffset_ = gyroOffset;
        }
        bool EnableAveraging( ) const
        {
            return enableAveraging_;
        }
        void SetEnableAveraging( bool enableAveraging )
        {
            enableAveraging_ = enableAveraging;
        }
        TimeSpan AveragingInterval( ) const
        {
            return averagingInterval_;
        }
        void SetAveragingInterval( const TimeSpan& averagingInterval )
        {
            averagingInterval_ = averagingInterval;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, WEATHERSTATION_FIELD_ID, &weatherStation_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, NODATATIMEOUT_FIELD_ID, &noDataTimeOut_);
            Bind(statement, SENDINTERVAL_FIELD_ID, &sendInterval_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, GYROOFFSET_FIELD_ID, &gyroOffset_);
            Bind(statement, ENABLEAVERAGING_FIELD_ID, &enableAveraging_);
            Bind(statement, AVERAGINGINTERVAL_FIELD_ID, &averagingInterval_);
        }

    };

    class ZoneColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        std::array<wchar_t,128> name_ = {};
        SQLLEN nameLengthOrNullIndicator_ = SQL_NULL_DATA;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        Data::ZoneAlarmType alarmType_ = Data::ZoneAlarmType::None;
        TimeSpan alarmTime_;
        TimeSpan radarTrackMinimumLifetime_;
        double speed_ = 0.0;
        UInt32 strokeColor_ = 0;
        UInt32 fillColor_ = 0;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Longitude],[Latitude],[AlarmType],[AlarmTime],[RadarTrackMinimumLifetime],[Speed],[StrokeColor],[FillColor]";
        static constexpr std::wstring_view ViewName = L"ZoneView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT NAME_FIELD_ID = 3;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT ALARMTYPE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT ALARMTIME_FIELD_ID = 7;
        static constexpr SQLUSMALLINT RADARTRACKMINIMUMLIFETIME_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SPEED_FIELD_ID = 9;
        static constexpr SQLUSMALLINT STROKECOLOR_FIELD_ID = 10;
        static constexpr SQLUSMALLINT FILLCOLOR_FIELD_ID = 11;

        ZoneColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::Zone;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        std::wstring_view Name( ) const
        {
            if(nameLengthOrNullIndicator_ != SQL_NULL_DATA)
            {
                return std::wstring_view(name_.data(),static_cast<size_t>( nameLengthOrNullIndicator_ ));
            }
            return {};
        }
        void SetName( const WideString& name )
        {
            Assign(name, name_, nameLengthOrNullIndicator_);
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        Data::ZoneAlarmType AlarmType( ) const
        {
            return alarmType_;
        }
        void SetAlarmType( Data::ZoneAlarmType alarmType )
        {
            alarmType_ = alarmType;
        }
        TimeSpan AlarmTime( ) const
        {
            return alarmTime_;
        }
        void SetAlarmTime( const TimeSpan& alarmTime )
        {
            alarmTime_ = alarmTime;
        }
        TimeSpan RadarTrackMinimumLifetime( ) const
        {
            return radarTrackMinimumLifetime_;
        }
        void SetRadarTrackMinimumLifetime( const TimeSpan& radarTrackMinimumLifetime )
        {
            radarTrackMinimumLifetime_ = radarTrackMinimumLifetime;
        }
        double Speed( ) const
        {
            return speed_;
        }
        void SetSpeed( double speed )
        {
            speed_ = speed;
        }
        UInt32 StrokeColor( ) const
        {
            return strokeColor_;
        }
        void SetStrokeColor( UInt32 strokeColor )
        {
            strokeColor_ = strokeColor;
        }
        UInt32 FillColor( ) const
        {
            return fillColor_;
        }
        void SetFillColor( UInt32 fillColor )
        {
            fillColor_ = fillColor;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, NAME_FIELD_ID, &name_, &nameLengthOrNullIndicator_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, ALARMTYPE_FIELD_ID, &alarmType_);
            Bind(statement, ALARMTIME_FIELD_ID, &alarmTime_);
            Bind(statement, RADARTRACKMINIMUMLIFETIME_FIELD_ID, &radarTrackMinimumLifetime_);
            Bind(statement, SPEED_FIELD_ID, &speed_);
            Bind(statement, STROKECOLOR_FIELD_ID, &strokeColor_);
            Bind(statement, FILLCOLOR_FIELD_ID, &fillColor_);
        }

    };

    class CircularZoneColumnData : public ZoneColumnData
    {
        double radius_ = 0.0;
    public:
        using Base = ZoneColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Longitude],[Latitude],[AlarmType],[AlarmTime],[RadarTrackMinimumLifetime],[Speed],[StrokeColor],[FillColor],[Radius]";
        static constexpr std::wstring_view ViewName = L"CircularZoneView";

        static constexpr SQLUSMALLINT RADIUS_FIELD_ID = 12;

        CircularZoneColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::CircularZone;
        }

        double Radius( ) const
        {
            return radius_;
        }
        void SetRadius( double radius )
        {
            radius_ = radius;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

            Bind(statement, RADIUS_FIELD_ID, &radius_);
        }

    };

    class PolygonZoneColumnData : public ZoneColumnData
    {
        std::vector<Byte> polygon_;
        SQLLEN polygonLengthOrNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = ZoneColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Name],[Longitude],[Latitude],[AlarmType],[AlarmTime],[RadarTrackMinimumLifetime],[Speed],[StrokeColor],[FillColor],[Polygon]";
        static constexpr std::wstring_view ViewName = L"PolygonZoneView";

        static constexpr SQLUSMALLINT POLYGON_FIELD_ID = 12;

        PolygonZoneColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::PolygonZone;
        }

        const std::vector<Byte>& Polygon( ) const
        {
            return polygon_;
        }
        void SetPolygon( const std::vector<Byte>& polygon )
        {
            Assign(polygon, polygon_, polygonLengthOrNullIndicator_);
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Base::BindColumns( statement );

        }

    };

    class ZoneExceptionsColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid zone_;
        DateTime timestamp_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Zone],[Timestamp]";
        static constexpr std::wstring_view ViewName = L"ZoneExceptionsView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ZONE_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 4;

        ZoneExceptionsColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ZoneExceptions;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Zone( ) const
        {
            return zone_;
        }
        void SetZone( const Guid& zone )
        {
            zone_ = zone;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ZONE_FIELD_ID, &zone_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
        }

    };

    class ZoneExceptionsVesselLinkColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid zoneExceptions_;
        Guid vessel_;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[ZoneExceptions],[Vessel]";
        static constexpr std::wstring_view ViewName = L"ZoneExceptionsVesselLinkView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT ZONEEXCEPTIONS_FIELD_ID = 3;
        static constexpr SQLUSMALLINT VESSEL_FIELD_ID = 4;

        ZoneExceptionsVesselLinkColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ZoneExceptionsVesselLink;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid ZoneExceptions( ) const
        {
            return zoneExceptions_;
        }
        void SetZoneExceptions( const Guid& zoneExceptions )
        {
            zoneExceptions_ = zoneExceptions;
        }
        Guid Vessel( ) const
        {
            return vessel_;
        }
        void SetVessel( const Guid& vessel )
        {
            vessel_ = vessel;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, ZONEEXCEPTIONS_FIELD_ID, &zoneExceptions_);
            Bind(statement, VESSEL_FIELD_ID, &vessel_);
        }

    };

    class ZoneTrackAlarmColumnData : public BaseColumnData
    {
        Guid id_;
        Int64 rowVersion_ = 0;
        Guid track_;
        Guid zone_;
        Guid radarTrack_;
        DateTime timestamp_;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double speed_ = 0.0;
        double course_ = 0.0;
        SQLLEN courseNullIndicator_ = SQL_NULL_DATA;
        double heading_ = 0.0;
        SQLLEN headingNullIndicator_ = SQL_NULL_DATA;
        double enterLatitude_ = 0.0;
        double enterLongitude_ = 0.0;
        double leaveLatitude_ = 0.0;
        SQLLEN leaveLatitudeNullIndicator_ = SQL_NULL_DATA;
        double leaveLongitude_ = 0.0;
        SQLLEN leaveLongitudeNullIndicator_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static constexpr std::wstring_view FieldNames = L"[Id],[RowVersion],[Track],[Zone],[RadarTrack],[Timestamp],[Latitude],[Longitude],[Speed],[Course],[Heading],[EnterLatitude],[EnterLongitude],[LeaveLatitude],[LeaveLongitude]";
        static constexpr std::wstring_view ViewName = L"ZoneTrackAlarmView";

        static constexpr SQLUSMALLINT ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ROWVERSION_FIELD_ID = 2;
        static constexpr SQLUSMALLINT TRACK_FIELD_ID = 3;
        static constexpr SQLUSMALLINT ZONE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT RADARTRACK_FIELD_ID = 5;
        static constexpr SQLUSMALLINT TIMESTAMP_FIELD_ID = 6;
        static constexpr SQLUSMALLINT LATITUDE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT LONGITUDE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT SPEED_FIELD_ID = 9;
        static constexpr SQLUSMALLINT COURSE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT HEADING_FIELD_ID = 11;
        static constexpr SQLUSMALLINT ENTERLATITUDE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT ENTERLONGITUDE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT LEAVELATITUDE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT LEAVELONGITUDE_FIELD_ID = 15;

        ZoneTrackAlarmColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return Kind::ZoneTrackAlarm;
        }

        Guid Id( ) const
        {
            return id_;
        }
        void SetId( const Guid& id )
        {
            id_ = id;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }
        Guid Track( ) const
        {
            return track_;
        }
        void SetTrack( const Guid& track )
        {
            track_ = track;
        }
        Guid Zone( ) const
        {
            return zone_;
        }
        void SetZone( const Guid& zone )
        {
            zone_ = zone;
        }
        Guid RadarTrack( ) const
        {
            return radarTrack_;
        }
        void SetRadarTrack( const Guid& radarTrack )
        {
            radarTrack_ = radarTrack;
        }
        DateTime Timestamp( ) const
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        void SetLatitude( double latitude )
        {
            latitude_ = latitude;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        void SetLongitude( double longitude )
        {
            longitude_ = longitude;
        }
        double Speed( ) const
        {
            return speed_;
        }
        void SetSpeed( double speed )
        {
            speed_ = speed;
        }
        double Course( ) const
        {
            return course_;
        }
        void SetCourse( double course )
        {
            course_ = course;
        }
        double Heading( ) const
        {
            return heading_;
        }
        void SetHeading( double heading )
        {
            heading_ = heading;
        }
        double EnterLatitude( ) const
        {
            return enterLatitude_;
        }
        void SetEnterLatitude( double enterLatitude )
        {
            enterLatitude_ = enterLatitude;
        }
        double EnterLongitude( ) const
        {
            return enterLongitude_;
        }
        void SetEnterLongitude( double enterLongitude )
        {
            enterLongitude_ = enterLongitude;
        }
        double LeaveLatitude( ) const
        {
            return leaveLatitude_;
        }
        void SetLeaveLatitude( double leaveLatitude )
        {
            leaveLatitude_ = leaveLatitude;
        }
        double LeaveLongitude( ) const
        {
            return leaveLongitude_;
        }
        void SetLeaveLongitude( double leaveLongitude )
        {
            leaveLongitude_ = leaveLongitude;
        }
        void BindColumns( const ODBC::Statement& statement )
        {
            Bind(statement, ID_FIELD_ID, &id_);
            Bind(statement, ROWVERSION_FIELD_ID, &rowVersion_);
            Bind(statement, TRACK_FIELD_ID, &track_);
            Bind(statement, ZONE_FIELD_ID, &zone_);
            Bind(statement, RADARTRACK_FIELD_ID, &radarTrack_);
            Bind(statement, TIMESTAMP_FIELD_ID, &timestamp_);
            Bind(statement, LATITUDE_FIELD_ID, &latitude_);
            Bind(statement, LONGITUDE_FIELD_ID, &longitude_);
            Bind(statement, SPEED_FIELD_ID, &speed_);
            Bind(statement, COURSE_FIELD_ID, &course_, &courseNullIndicator_);
            Bind(statement, HEADING_FIELD_ID, &heading_, &headingNullIndicator_);
            Bind(statement, ENTERLATITUDE_FIELD_ID, &enterLatitude_);
            Bind(statement, ENTERLONGITUDE_FIELD_ID, &enterLongitude_);
            Bind(statement, LEAVELATITUDE_FIELD_ID, &leaveLatitude_, &leaveLatitudeNullIndicator_);
            Bind(statement, LEAVELONGITUDE_FIELD_ID, &leaveLongitude_, &leaveLongitudeNullIndicator_);
        }

    };

}
#endif
