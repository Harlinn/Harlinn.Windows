#include "pch.h"

#include "StoredProcedures.h"


namespace Barrelman::Database
{

    BARRELMAN_EXPORT void InsertAircraftType( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.ExecDirect( L"{ CALL [AircraftTypeInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAircraftType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::Output );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.ExecDirect( L"{ CALL [AircraftTypeUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAircraftType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AircraftTypeDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, reply );
        statement.ExecDirect( L"{ CALL [AisDeviceCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, reply );
        statement.ExecDirect( L"{ CALL [AisDeviceCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisDeviceCommandDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.ExecDirect( L"{ CALL [AisDeviceCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.ExecDirect( L"{ CALL [AisDeviceCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisDeviceCommandReplyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, FixedDBWideString<127> userName, FixedDBWideString<127> password, double latitude, double longitude, FixedDBWideString<127> aisProviderLoginURL, FixedDBWideString<32> comPort, Int32 baudRate, bool filterByArea, double upperLeftCornerLatitude, double upperLeftCornerLongitude, double bottomRightCornerLatitude, double bottomRightCornerLongitude, FixedDBWideString<127> aisProviderIPAddress, Int32 aisProviderPort, bool useLogin, Int32 aisProviderLoginPort, bool canSendAISMessage, const WideString& textMessageHeader, const WideString& urls, Int32 udpPort, Data::AisDeviceConnectionType connectionType, bool enableRefreshAidToNavigationIn30sec, bool enableAidToNavigationFromFile, const WideString& aidToNavigationHeader, bool sendingMMSI, Int32 sourceUpdateRate, bool enableRefreshStayingStillTargetIn30sec, const WideString& excludeSendAisBaseStation, const WideString& excludeSendAisA, bool enableSendBaseStationAlarms, FixedDBWideString<127> aisWebConfig, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindFixedDBWideStringParameter( 4, userName );
        statement.BindFixedDBWideStringParameter( 5, password );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindDoubleParameter( 7, &longitude );
        statement.BindFixedDBWideStringParameter( 8, aisProviderLoginURL );
        statement.BindFixedDBWideStringParameter( 9, comPort );
        statement.BindInt32Parameter( 10, &baudRate );
        statement.BindBooleanParameter( 11, &filterByArea );
        statement.BindDoubleParameter( 12, &upperLeftCornerLatitude );
        statement.BindDoubleParameter( 13, &upperLeftCornerLongitude );
        statement.BindDoubleParameter( 14, &bottomRightCornerLatitude );
        statement.BindDoubleParameter( 15, &bottomRightCornerLongitude );
        statement.BindFixedDBWideStringParameter( 16, aisProviderIPAddress );
        statement.BindInt32Parameter( 17, &aisProviderPort );
        statement.BindBooleanParameter( 18, &useLogin );
        statement.BindInt32Parameter( 19, &aisProviderLoginPort );
        statement.BindBooleanParameter( 20, &canSendAISMessage );
        statement.BindWideStringParameter( 21, textMessageHeader );
        statement.BindWideStringParameter( 22, urls );
        statement.BindInt32Parameter( 23, &udpPort );
        statement.BindEnumParameter( 24, &connectionType );
        statement.BindBooleanParameter( 25, &enableRefreshAidToNavigationIn30sec );
        statement.BindBooleanParameter( 26, &enableAidToNavigationFromFile );
        statement.BindWideStringParameter( 27, aidToNavigationHeader );
        statement.BindBooleanParameter( 28, &sendingMMSI );
        statement.BindInt32Parameter( 29, &sourceUpdateRate );
        statement.BindBooleanParameter( 30, &enableRefreshStayingStillTargetIn30sec );
        statement.BindWideStringParameter( 31, excludeSendAisBaseStation );
        statement.BindWideStringParameter( 32, excludeSendAisA );
        statement.BindBooleanParameter( 33, &enableSendBaseStationAlarms );
        statement.BindFixedDBWideStringParameter( 34, aisWebConfig );
        statement.BindBooleanParameter( 35, &storeReceivedSentences );
        statement.BindBooleanParameter( 36, &storeSentMessages );
        statement.BindBooleanParameter( 37, &storeUnsentMessages );
        statement.ExecDirect( L"{ CALL [AisDeviceConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, FixedDBWideString<127> userName, FixedDBWideString<127> password, double latitude, double longitude, FixedDBWideString<127> aisProviderLoginURL, FixedDBWideString<32> comPort, Int32 baudRate, bool filterByArea, double upperLeftCornerLatitude, double upperLeftCornerLongitude, double bottomRightCornerLatitude, double bottomRightCornerLongitude, FixedDBWideString<127> aisProviderIPAddress, Int32 aisProviderPort, bool useLogin, Int32 aisProviderLoginPort, bool canSendAISMessage, const WideString& textMessageHeader, const WideString& urls, Int32 udpPort, Data::AisDeviceConnectionType connectionType, bool enableRefreshAidToNavigationIn30sec, bool enableAidToNavigationFromFile, const WideString& aidToNavigationHeader, bool sendingMMSI, Int32 sourceUpdateRate, bool enableRefreshStayingStillTargetIn30sec, const WideString& excludeSendAisBaseStation, const WideString& excludeSendAisA, bool enableSendBaseStationAlarms, FixedDBWideString<127> aisWebConfig, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindFixedDBWideStringParameter( 5, userName );
        statement.BindFixedDBWideStringParameter( 6, password );
        statement.BindDoubleParameter( 7, &latitude );
        statement.BindDoubleParameter( 8, &longitude );
        statement.BindFixedDBWideStringParameter( 9, aisProviderLoginURL );
        statement.BindFixedDBWideStringParameter( 10, comPort );
        statement.BindInt32Parameter( 11, &baudRate );
        statement.BindBooleanParameter( 12, &filterByArea );
        statement.BindDoubleParameter( 13, &upperLeftCornerLatitude );
        statement.BindDoubleParameter( 14, &upperLeftCornerLongitude );
        statement.BindDoubleParameter( 15, &bottomRightCornerLatitude );
        statement.BindDoubleParameter( 16, &bottomRightCornerLongitude );
        statement.BindFixedDBWideStringParameter( 17, aisProviderIPAddress );
        statement.BindInt32Parameter( 18, &aisProviderPort );
        statement.BindBooleanParameter( 19, &useLogin );
        statement.BindInt32Parameter( 20, &aisProviderLoginPort );
        statement.BindBooleanParameter( 21, &canSendAISMessage );
        statement.BindWideStringParameter( 22, textMessageHeader );
        statement.BindWideStringParameter( 23, urls );
        statement.BindInt32Parameter( 24, &udpPort );
        statement.BindEnumParameter( 25, &connectionType );
        statement.BindBooleanParameter( 26, &enableRefreshAidToNavigationIn30sec );
        statement.BindBooleanParameter( 27, &enableAidToNavigationFromFile );
        statement.BindWideStringParameter( 28, aidToNavigationHeader );
        statement.BindBooleanParameter( 29, &sendingMMSI );
        statement.BindInt32Parameter( 30, &sourceUpdateRate );
        statement.BindBooleanParameter( 31, &enableRefreshStayingStillTargetIn30sec );
        statement.BindWideStringParameter( 32, excludeSendAisBaseStation );
        statement.BindWideStringParameter( 33, excludeSendAisA );
        statement.BindBooleanParameter( 34, &enableSendBaseStationAlarms );
        statement.BindFixedDBWideStringParameter( 35, aisWebConfig );
        statement.BindBooleanParameter( 36, &storeReceivedSentences );
        statement.BindBooleanParameter( 37, &storeSentMessages );
        statement.BindBooleanParameter( 38, &storeUnsentMessages );
        statement.ExecDirect( L"{ CALL [AisDeviceConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisDeviceConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisDeviceRawMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, bool isSent, FixedDBWideString<100> message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindBooleanParameter( 4, &isSent );
        statement.BindFixedDBWideStringParameter( 5, message );
        statement.ExecDirect( L"{ CALL [AisDeviceRawMessageInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisDeviceRawMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, bool isSent, FixedDBWideString<100> message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindBooleanParameter( 5, &isSent );
        statement.BindFixedDBWideStringParameter( 6, message );
        statement.ExecDirect( L"{ CALL [AisDeviceRawMessageUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisDeviceRawMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisDeviceRawMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisDeviceRawSentence( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, const WideString& sentence )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindWideStringParameter( 4, sentence );
        statement.ExecDirect( L"{ CALL [AisDeviceRawSentenceInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisDeviceRawSentence( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, const WideString& sentence )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindWideStringParameter( 5, sentence );
        statement.ExecDirect( L"{ CALL [AisDeviceRawSentenceUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisDeviceRawSentence( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisDeviceRawSentenceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAidToNavigationReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationalAidType navigationalAidType, FixedDBWideString<100> name, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Int32 timestamp, bool offPosition, Int32 regionalReserved, Data::Raim raim, bool virtualAid, bool assigned, Int32 spare, FixedDBWideString<100> nameExtension )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindEnumParameter( 7, &navigationalAidType );
        statement.BindFixedDBWideStringParameter( 8, name );
        statement.BindEnumParameter( 9, &positionAccuracy );
        statement.BindDoubleParameter( 10, &longitude );
        statement.BindDoubleParameter( 11, &latitude );
        statement.BindInt32Parameter( 12, &dimensionToBow );
        statement.BindInt32Parameter( 13, &dimensionToStern );
        statement.BindInt32Parameter( 14, &dimensionToPort );
        statement.BindInt32Parameter( 15, &dimensionToStarboard );
        statement.BindEnumParameter( 16, &positionFixType );
        statement.BindInt32Parameter( 17, &timestamp );
        statement.BindBooleanParameter( 18, &offPosition );
        statement.BindInt32Parameter( 19, &regionalReserved );
        statement.BindEnumParameter( 20, &raim );
        statement.BindBooleanParameter( 21, &virtualAid );
        statement.BindBooleanParameter( 22, &assigned );
        statement.BindInt32Parameter( 23, &spare );
        statement.BindFixedDBWideStringParameter( 24, nameExtension );
        statement.ExecDirect( L"{ CALL [AidToNavigationReportMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAidToNavigationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationalAidType navigationalAidType, FixedDBWideString<100> name, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Int32 timestamp, bool offPosition, Int32 regionalReserved, Data::Raim raim, bool virtualAid, bool assigned, Int32 spare, FixedDBWideString<100> nameExtension )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindEnumParameter( 8, &navigationalAidType );
        statement.BindFixedDBWideStringParameter( 9, name );
        statement.BindEnumParameter( 10, &positionAccuracy );
        statement.BindDoubleParameter( 11, &longitude );
        statement.BindDoubleParameter( 12, &latitude );
        statement.BindInt32Parameter( 13, &dimensionToBow );
        statement.BindInt32Parameter( 14, &dimensionToStern );
        statement.BindInt32Parameter( 15, &dimensionToPort );
        statement.BindInt32Parameter( 16, &dimensionToStarboard );
        statement.BindEnumParameter( 17, &positionFixType );
        statement.BindInt32Parameter( 18, &timestamp );
        statement.BindBooleanParameter( 19, &offPosition );
        statement.BindInt32Parameter( 20, &regionalReserved );
        statement.BindEnumParameter( 21, &raim );
        statement.BindBooleanParameter( 22, &virtualAid );
        statement.BindBooleanParameter( 23, &assigned );
        statement.BindInt32Parameter( 24, &spare );
        statement.BindFixedDBWideStringParameter( 25, nameExtension );
        statement.ExecDirect( L"{ CALL [AidToNavigationReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAidToNavigationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AidToNavigationReportMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, FixedDBWideString<100> text )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &sequenceNumber );
        statement.BindGuidParameter( 8, &destinationMmsi );
        statement.BindBooleanParameter( 9, &retransmitFlag );
        statement.BindInt32Parameter( 10, &spare );
        statement.BindFixedDBWideStringParameter( 11, text );
        statement.ExecDirect( L"{ CALL [AisAddressedSafetyRelatedMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, FixedDBWideString<100> text )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &sequenceNumber );
        statement.BindGuidParameter( 9, &destinationMmsi );
        statement.BindBooleanParameter( 10, &retransmitFlag );
        statement.BindInt32Parameter( 11, &spare );
        statement.BindFixedDBWideStringParameter( 12, text );
        statement.ExecDirect( L"{ CALL [AisAddressedSafetyRelatedMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisAddressedSafetyRelatedMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisBaseStationReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& timestamp, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindDateTimeParameter( 7, timestamp );
        statement.BindEnumParameter( 8, &positionAccuracy );
        statement.BindDoubleParameter( 9, &longitude );
        statement.BindDoubleParameter( 10, &latitude );
        statement.BindEnumParameter( 11, &positionFixType );
        statement.BindInt32Parameter( 12, &spare );
        statement.BindEnumParameter( 13, &raim );
        statement.BindInt32Parameter( 14, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisBaseStationReportMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisBaseStationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& timestamp, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindDateTimeParameter( 8, timestamp );
        statement.BindEnumParameter( 9, &positionAccuracy );
        statement.BindDoubleParameter( 10, &longitude );
        statement.BindDoubleParameter( 11, &latitude );
        statement.BindEnumParameter( 12, &positionFixType );
        statement.BindInt32Parameter( 13, &spare );
        statement.BindEnumParameter( 14, &raim );
        statement.BindInt32Parameter( 15, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisBaseStationReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisBaseStationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisBaseStationReportMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &spare );
        statement.BindInt32Parameter( 8, &sequenceNumber1 );
        statement.BindGuidParameter( 9, &mmsi1 );
        statement.BindInt32Parameter( 10, sequenceNumber2 );
        statement.BindGuidParameter( 11, mmsi2 );
        statement.BindInt32Parameter( 12, sequenceNumber3 );
        statement.BindGuidParameter( 13, mmsi3 );
        statement.BindInt32Parameter( 14, sequenceNumber4 );
        statement.BindGuidParameter( 15, mmsi4 );
        statement.ExecDirect( L"{ CALL [AisBinaryAcknowledgeMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &spare );
        statement.BindInt32Parameter( 9, &sequenceNumber1 );
        statement.BindGuidParameter( 10, &mmsi1 );
        statement.BindInt32Parameter( 11, sequenceNumber2 );
        statement.BindGuidParameter( 12, mmsi2 );
        statement.BindInt32Parameter( 13, sequenceNumber3 );
        statement.BindGuidParameter( 14, mmsi3 );
        statement.BindInt32Parameter( 15, sequenceNumber4 );
        statement.BindGuidParameter( 16, mmsi4 );
        statement.ExecDirect( L"{ CALL [AisBinaryAcknowledgeMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisBinaryAcknowledgeMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisBinaryAddressedMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &sequenceNumber );
        statement.BindGuidParameter( 8, &destinationMmsi );
        statement.BindBooleanParameter( 9, &retransmitFlag );
        statement.BindInt32Parameter( 10, &spare );
        statement.BindInt32Parameter( 11, &designatedAreaCode );
        statement.BindInt32Parameter( 12, &functionalId );
        statement.BindWideStringParameter( 13, data );
        statement.ExecDirect( L"{ CALL [AisBinaryAddressedMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisBinaryAddressedMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &sequenceNumber );
        statement.BindGuidParameter( 9, &destinationMmsi );
        statement.BindBooleanParameter( 10, &retransmitFlag );
        statement.BindInt32Parameter( 11, &spare );
        statement.BindInt32Parameter( 12, &designatedAreaCode );
        statement.BindInt32Parameter( 13, &functionalId );
        statement.BindWideStringParameter( 14, data );
        statement.ExecDirect( L"{ CALL [AisBinaryAddressedMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisBinaryAddressedMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisBinaryAddressedMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisBinaryBroadcastMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &spare );
        statement.BindInt32Parameter( 8, &designatedAreaCode );
        statement.BindInt32Parameter( 9, &functionalId );
        statement.BindWideStringParameter( 10, data );
        statement.ExecDirect( L"{ CALL [AisBinaryBroadcastMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisBinaryBroadcastMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &spare );
        statement.BindInt32Parameter( 9, &designatedAreaCode );
        statement.BindInt32Parameter( 10, &functionalId );
        statement.BindWideStringParameter( 11, data );
        statement.ExecDirect( L"{ CALL [AisBinaryBroadcastMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisBinaryBroadcastMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisBinaryBroadcastMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisDataLinkManagementMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 offset1, Int32 reservedSlots1, Int32 timeout1, Int32 increment1, const DBInt32& offset2, const DBInt32& reservedSlots2, const DBInt32& timeout2, const DBInt32& increment2, const DBInt32& offset3, const DBInt32& reservedSlots3, const DBInt32& timeout3, const DBInt32& increment3, const DBInt32& offset4, const DBInt32& reservedSlots4, const DBInt32& timeout4, const DBInt32& increment4 )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &spare );
        statement.BindInt32Parameter( 8, &offset1 );
        statement.BindInt32Parameter( 9, &reservedSlots1 );
        statement.BindInt32Parameter( 10, &timeout1 );
        statement.BindInt32Parameter( 11, &increment1 );
        statement.BindInt32Parameter( 12, offset2 );
        statement.BindInt32Parameter( 13, reservedSlots2 );
        statement.BindInt32Parameter( 14, timeout2 );
        statement.BindInt32Parameter( 15, increment2 );
        statement.BindInt32Parameter( 16, offset3 );
        statement.BindInt32Parameter( 17, reservedSlots3 );
        statement.BindInt32Parameter( 18, timeout3 );
        statement.BindInt32Parameter( 19, increment3 );
        statement.BindInt32Parameter( 20, offset4 );
        statement.BindInt32Parameter( 21, reservedSlots4 );
        statement.BindInt32Parameter( 22, timeout4 );
        statement.BindInt32Parameter( 23, increment4 );
        statement.ExecDirect( L"{ CALL [AisDataLinkManagementMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisDataLinkManagementMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 offset1, Int32 reservedSlots1, Int32 timeout1, Int32 increment1, const DBInt32& offset2, const DBInt32& reservedSlots2, const DBInt32& timeout2, const DBInt32& increment2, const DBInt32& offset3, const DBInt32& reservedSlots3, const DBInt32& timeout3, const DBInt32& increment3, const DBInt32& offset4, const DBInt32& reservedSlots4, const DBInt32& timeout4, const DBInt32& increment4 )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &spare );
        statement.BindInt32Parameter( 9, &offset1 );
        statement.BindInt32Parameter( 10, &reservedSlots1 );
        statement.BindInt32Parameter( 11, &timeout1 );
        statement.BindInt32Parameter( 12, &increment1 );
        statement.BindInt32Parameter( 13, offset2 );
        statement.BindInt32Parameter( 14, reservedSlots2 );
        statement.BindInt32Parameter( 15, timeout2 );
        statement.BindInt32Parameter( 16, increment2 );
        statement.BindInt32Parameter( 17, offset3 );
        statement.BindInt32Parameter( 18, reservedSlots3 );
        statement.BindInt32Parameter( 19, timeout3 );
        statement.BindInt32Parameter( 20, increment3 );
        statement.BindInt32Parameter( 21, offset4 );
        statement.BindInt32Parameter( 22, reservedSlots4 );
        statement.BindInt32Parameter( 23, timeout4 );
        statement.BindInt32Parameter( 24, increment4 );
        statement.ExecDirect( L"{ CALL [AisDataLinkManagementMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisDataLinkManagementMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisDataLinkManagementMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, const Guid& name, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Data::Raim raim, bool dataTerminalReady, bool assigned, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &reserved );
        statement.BindDoubleParameter( 8, &speedOverGround );
        statement.BindEnumParameter( 9, &positionAccuracy );
        statement.BindDoubleParameter( 10, &longitude );
        statement.BindDoubleParameter( 11, &latitude );
        statement.BindDoubleParameter( 12, &courseOverGround );
        statement.BindInt32Parameter( 13, trueHeading );
        statement.BindInt32Parameter( 14, &timestamp );
        statement.BindInt32Parameter( 15, &regionalReserved );
        statement.BindGuidParameter( 16, &name );
        statement.BindEnumParameter( 17, &shipType );
        statement.BindInt32Parameter( 18, &dimensionToBow );
        statement.BindInt32Parameter( 19, &dimensionToStern );
        statement.BindInt32Parameter( 20, &dimensionToPort );
        statement.BindInt32Parameter( 21, &dimensionToStarboard );
        statement.BindEnumParameter( 22, &positionFixType );
        statement.BindEnumParameter( 23, &raim );
        statement.BindBooleanParameter( 24, &dataTerminalReady );
        statement.BindBooleanParameter( 25, &assigned );
        statement.BindInt32Parameter( 26, &spare );
        statement.ExecDirect( L"{ CALL [AisExtendedClassBCsPositionReportMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, const Guid& name, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Data::Raim raim, bool dataTerminalReady, bool assigned, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &reserved );
        statement.BindDoubleParameter( 9, &speedOverGround );
        statement.BindEnumParameter( 10, &positionAccuracy );
        statement.BindDoubleParameter( 11, &longitude );
        statement.BindDoubleParameter( 12, &latitude );
        statement.BindDoubleParameter( 13, &courseOverGround );
        statement.BindInt32Parameter( 14, trueHeading );
        statement.BindInt32Parameter( 15, &timestamp );
        statement.BindInt32Parameter( 16, &regionalReserved );
        statement.BindGuidParameter( 17, &name );
        statement.BindEnumParameter( 18, &shipType );
        statement.BindInt32Parameter( 19, &dimensionToBow );
        statement.BindInt32Parameter( 20, &dimensionToStern );
        statement.BindInt32Parameter( 21, &dimensionToPort );
        statement.BindInt32Parameter( 22, &dimensionToStarboard );
        statement.BindEnumParameter( 23, &positionFixType );
        statement.BindEnumParameter( 24, &raim );
        statement.BindBooleanParameter( 25, &dataTerminalReady );
        statement.BindBooleanParameter( 26, &assigned );
        statement.BindInt32Parameter( 27, &spare );
        statement.ExecDirect( L"{ CALL [AisExtendedClassBCsPositionReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisExtendedClassBCsPositionReportMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisInterrogationMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const Guid& interrogatedMmsi, Data::AisMessageType firstMessageType, Int32 firstSlotOffset, const DBEnum<Data::AisMessageType>& secondMessageType, const DBInt32& secondSlotOffset, const DBGuid& secondStationInterrogationMmsi, const DBEnum<Data::AisMessageType>& secondStationFirstMessageType, const DBInt32& secondStationFirstSlotOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindGuidParameter( 7, &interrogatedMmsi );
        statement.BindEnumParameter( 8, &firstMessageType );
        statement.BindInt32Parameter( 9, &firstSlotOffset );
        statement.BindEnumParameter( 10, secondMessageType );
        statement.BindInt32Parameter( 11, secondSlotOffset );
        statement.BindGuidParameter( 12, secondStationInterrogationMmsi );
        statement.BindEnumParameter( 13, secondStationFirstMessageType );
        statement.BindInt32Parameter( 14, secondStationFirstSlotOffset );
        statement.ExecDirect( L"{ CALL [AisInterrogationMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const Guid& interrogatedMmsi, Data::AisMessageType firstMessageType, Int32 firstSlotOffset, const DBEnum<Data::AisMessageType>& secondMessageType, const DBInt32& secondSlotOffset, const DBGuid& secondStationInterrogationMmsi, const DBEnum<Data::AisMessageType>& secondStationFirstMessageType, const DBInt32& secondStationFirstSlotOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindGuidParameter( 8, &interrogatedMmsi );
        statement.BindEnumParameter( 9, &firstMessageType );
        statement.BindInt32Parameter( 10, &firstSlotOffset );
        statement.BindEnumParameter( 11, secondMessageType );
        statement.BindInt32Parameter( 12, secondSlotOffset );
        statement.BindGuidParameter( 13, secondStationInterrogationMmsi );
        statement.BindEnumParameter( 14, secondStationFirstMessageType );
        statement.BindInt32Parameter( 15, secondStationFirstSlotOffset );
        statement.ExecDirect( L"{ CALL [AisInterrogationMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisInterrogationMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindEnumParameter( 7, &navigationStatus );
        statement.BindInt32Parameter( 8, rateOfTurn );
        statement.BindDoubleParameter( 9, &speedOverGround );
        statement.BindEnumParameter( 10, &positionAccuracy );
        statement.BindDoubleParameter( 11, &longitude );
        statement.BindDoubleParameter( 12, &latitude );
        statement.BindDoubleParameter( 13, &courseOverGround );
        statement.BindInt32Parameter( 14, trueHeading );
        statement.BindInt32Parameter( 15, &timestamp );
        statement.BindEnumParameter( 16, &maneuverIndicator );
        statement.BindInt32Parameter( 17, &spare );
        statement.BindEnumParameter( 18, &raim );
        statement.BindInt32Parameter( 19, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisPositionReportClassAAssignedScheduleMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindEnumParameter( 8, &navigationStatus );
        statement.BindInt32Parameter( 9, rateOfTurn );
        statement.BindDoubleParameter( 10, &speedOverGround );
        statement.BindEnumParameter( 11, &positionAccuracy );
        statement.BindDoubleParameter( 12, &longitude );
        statement.BindDoubleParameter( 13, &latitude );
        statement.BindDoubleParameter( 14, &courseOverGround );
        statement.BindInt32Parameter( 15, trueHeading );
        statement.BindInt32Parameter( 16, &timestamp );
        statement.BindEnumParameter( 17, &maneuverIndicator );
        statement.BindInt32Parameter( 18, &spare );
        statement.BindEnumParameter( 19, &raim );
        statement.BindInt32Parameter( 20, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisPositionReportClassAAssignedScheduleMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisPositionReportClassAAssignedScheduleMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisPositionReportClassAMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindEnumParameter( 7, &navigationStatus );
        statement.BindInt32Parameter( 8, rateOfTurn );
        statement.BindDoubleParameter( 9, &speedOverGround );
        statement.BindEnumParameter( 10, &positionAccuracy );
        statement.BindDoubleParameter( 11, &longitude );
        statement.BindDoubleParameter( 12, &latitude );
        statement.BindDoubleParameter( 13, &courseOverGround );
        statement.BindInt32Parameter( 14, trueHeading );
        statement.BindInt32Parameter( 15, &timestamp );
        statement.BindEnumParameter( 16, &maneuverIndicator );
        statement.BindInt32Parameter( 17, &spare );
        statement.BindEnumParameter( 18, &raim );
        statement.BindInt32Parameter( 19, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisPositionReportClassAMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisPositionReportClassAMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindEnumParameter( 8, &navigationStatus );
        statement.BindInt32Parameter( 9, rateOfTurn );
        statement.BindDoubleParameter( 10, &speedOverGround );
        statement.BindEnumParameter( 11, &positionAccuracy );
        statement.BindDoubleParameter( 12, &longitude );
        statement.BindDoubleParameter( 13, &latitude );
        statement.BindDoubleParameter( 14, &courseOverGround );
        statement.BindInt32Parameter( 15, trueHeading );
        statement.BindInt32Parameter( 16, &timestamp );
        statement.BindEnumParameter( 17, &maneuverIndicator );
        statement.BindInt32Parameter( 18, &spare );
        statement.BindEnumParameter( 19, &raim );
        statement.BindInt32Parameter( 20, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisPositionReportClassAMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisPositionReportClassAMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisPositionReportClassAMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindEnumParameter( 7, &navigationStatus );
        statement.BindInt32Parameter( 8, rateOfTurn );
        statement.BindDoubleParameter( 9, &speedOverGround );
        statement.BindEnumParameter( 10, &positionAccuracy );
        statement.BindDoubleParameter( 11, &longitude );
        statement.BindDoubleParameter( 12, &latitude );
        statement.BindDoubleParameter( 13, &courseOverGround );
        statement.BindInt32Parameter( 14, trueHeading );
        statement.BindInt32Parameter( 15, &timestamp );
        statement.BindEnumParameter( 16, &maneuverIndicator );
        statement.BindInt32Parameter( 17, &spare );
        statement.BindEnumParameter( 18, &raim );
        statement.BindInt32Parameter( 19, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisPositionReportClassAResponseToInterrogationMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindEnumParameter( 8, &navigationStatus );
        statement.BindInt32Parameter( 9, rateOfTurn );
        statement.BindDoubleParameter( 10, &speedOverGround );
        statement.BindEnumParameter( 11, &positionAccuracy );
        statement.BindDoubleParameter( 12, &longitude );
        statement.BindDoubleParameter( 13, &latitude );
        statement.BindDoubleParameter( 14, &courseOverGround );
        statement.BindInt32Parameter( 15, trueHeading );
        statement.BindInt32Parameter( 16, &timestamp );
        statement.BindEnumParameter( 17, &maneuverIndicator );
        statement.BindInt32Parameter( 18, &spare );
        statement.BindEnumParameter( 19, &raim );
        statement.BindInt32Parameter( 20, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisPositionReportClassAResponseToInterrogationMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisPositionReportClassAResponseToInterrogationMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::PositionAccuracy positionAccuracy, Data::Raim raim, Data::NavigationStatus navigationStatus, double longitude, double latitude, double speedOverGround, double courseOverGround, Data::GnssPositionStatus gnssPositionStatus, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindEnumParameter( 7, &positionAccuracy );
        statement.BindEnumParameter( 8, &raim );
        statement.BindEnumParameter( 9, &navigationStatus );
        statement.BindDoubleParameter( 10, &longitude );
        statement.BindDoubleParameter( 11, &latitude );
        statement.BindDoubleParameter( 12, &speedOverGround );
        statement.BindDoubleParameter( 13, &courseOverGround );
        statement.BindEnumParameter( 14, &gnssPositionStatus );
        statement.BindInt32Parameter( 15, &spare );
        statement.ExecDirect( L"{ CALL [AisPositionReportForLongRangeApplicationsMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::PositionAccuracy positionAccuracy, Data::Raim raim, Data::NavigationStatus navigationStatus, double longitude, double latitude, double speedOverGround, double courseOverGround, Data::GnssPositionStatus gnssPositionStatus, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindEnumParameter( 8, &positionAccuracy );
        statement.BindEnumParameter( 9, &raim );
        statement.BindEnumParameter( 10, &navigationStatus );
        statement.BindDoubleParameter( 11, &longitude );
        statement.BindDoubleParameter( 12, &latitude );
        statement.BindDoubleParameter( 13, &speedOverGround );
        statement.BindDoubleParameter( 14, &courseOverGround );
        statement.BindEnumParameter( 15, &gnssPositionStatus );
        statement.BindInt32Parameter( 16, &spare );
        statement.ExecDirect( L"{ CALL [AisPositionReportForLongRangeApplicationsMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisPositionReportForLongRangeApplicationsMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &spare );
        statement.BindInt32Parameter( 8, &sequenceNumber1 );
        statement.BindGuidParameter( 9, &mmsi1 );
        statement.BindInt32Parameter( 10, sequenceNumber2 );
        statement.BindGuidParameter( 11, mmsi2 );
        statement.BindInt32Parameter( 12, sequenceNumber3 );
        statement.BindGuidParameter( 13, mmsi3 );
        statement.BindInt32Parameter( 14, sequenceNumber4 );
        statement.BindGuidParameter( 15, mmsi4 );
        statement.ExecDirect( L"{ CALL [AisSafetyRelatedAcknowledgmentMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &spare );
        statement.BindInt32Parameter( 9, &sequenceNumber1 );
        statement.BindGuidParameter( 10, &mmsi1 );
        statement.BindInt32Parameter( 11, sequenceNumber2 );
        statement.BindGuidParameter( 12, mmsi2 );
        statement.BindInt32Parameter( 13, sequenceNumber3 );
        statement.BindGuidParameter( 14, mmsi3 );
        statement.BindInt32Parameter( 15, sequenceNumber4 );
        statement.BindGuidParameter( 16, mmsi4 );
        statement.ExecDirect( L"{ CALL [AisSafetyRelatedAcknowledgmentMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisSafetyRelatedAcknowledgmentMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, bool isCsUnit, bool hasDisplay, bool hasDscCapability, bool band, bool canAcceptMessage22, bool assigned, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &reserved );
        statement.BindDoubleParameter( 8, &speedOverGround );
        statement.BindEnumParameter( 9, &positionAccuracy );
        statement.BindDoubleParameter( 10, &longitude );
        statement.BindDoubleParameter( 11, &latitude );
        statement.BindDoubleParameter( 12, &courseOverGround );
        statement.BindInt32Parameter( 13, trueHeading );
        statement.BindInt32Parameter( 14, &timestamp );
        statement.BindInt32Parameter( 15, &regionalReserved );
        statement.BindBooleanParameter( 16, &isCsUnit );
        statement.BindBooleanParameter( 17, &hasDisplay );
        statement.BindBooleanParameter( 18, &hasDscCapability );
        statement.BindBooleanParameter( 19, &band );
        statement.BindBooleanParameter( 20, &canAcceptMessage22 );
        statement.BindBooleanParameter( 21, &assigned );
        statement.BindEnumParameter( 22, &raim );
        statement.BindInt32Parameter( 23, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisStandardClassBCsPositionReportMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, bool isCsUnit, bool hasDisplay, bool hasDscCapability, bool band, bool canAcceptMessage22, bool assigned, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &reserved );
        statement.BindDoubleParameter( 9, &speedOverGround );
        statement.BindEnumParameter( 10, &positionAccuracy );
        statement.BindDoubleParameter( 11, &longitude );
        statement.BindDoubleParameter( 12, &latitude );
        statement.BindDoubleParameter( 13, &courseOverGround );
        statement.BindInt32Parameter( 14, trueHeading );
        statement.BindInt32Parameter( 15, &timestamp );
        statement.BindInt32Parameter( 16, &regionalReserved );
        statement.BindBooleanParameter( 17, &isCsUnit );
        statement.BindBooleanParameter( 18, &hasDisplay );
        statement.BindBooleanParameter( 19, &hasDscCapability );
        statement.BindBooleanParameter( 20, &band );
        statement.BindBooleanParameter( 21, &canAcceptMessage22 );
        statement.BindBooleanParameter( 22, &assigned );
        statement.BindEnumParameter( 23, &raim );
        statement.BindInt32Parameter( 24, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisStandardClassBCsPositionReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisStandardClassBCsPositionReportMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 altitude, Int32 speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, Int32 timestamp, Int32 reserved, bool dataTerminalReady, Int32 spare, bool assigned, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &altitude );
        statement.BindInt32Parameter( 8, &speedOverGround );
        statement.BindEnumParameter( 9, &positionAccuracy );
        statement.BindDoubleParameter( 10, &longitude );
        statement.BindDoubleParameter( 11, &latitude );
        statement.BindDoubleParameter( 12, &courseOverGround );
        statement.BindInt32Parameter( 13, &timestamp );
        statement.BindInt32Parameter( 14, &reserved );
        statement.BindBooleanParameter( 15, &dataTerminalReady );
        statement.BindInt32Parameter( 16, &spare );
        statement.BindBooleanParameter( 17, &assigned );
        statement.BindEnumParameter( 18, &raim );
        statement.BindInt32Parameter( 19, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisStandardSarAircraftPositionReportMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 altitude, Int32 speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, Int32 timestamp, Int32 reserved, bool dataTerminalReady, Int32 spare, bool assigned, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &altitude );
        statement.BindInt32Parameter( 9, &speedOverGround );
        statement.BindEnumParameter( 10, &positionAccuracy );
        statement.BindDoubleParameter( 11, &longitude );
        statement.BindDoubleParameter( 12, &latitude );
        statement.BindDoubleParameter( 13, &courseOverGround );
        statement.BindInt32Parameter( 14, &timestamp );
        statement.BindInt32Parameter( 15, &reserved );
        statement.BindBooleanParameter( 16, &dataTerminalReady );
        statement.BindInt32Parameter( 17, &spare );
        statement.BindBooleanParameter( 18, &assigned );
        statement.BindEnumParameter( 19, &raim );
        statement.BindInt32Parameter( 20, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisStandardSarAircraftPositionReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisStandardSarAircraftPositionReportMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 aisVersion, const Guid& imoNumber, const Guid& callsign, const Guid& shipName, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, const DBDateTime& estimatedTimeOfArrival, double draught, FixedDBWideString<100> destination, bool dataTerminalReady, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &aisVersion );
        statement.BindGuidParameter( 8, &imoNumber );
        statement.BindGuidParameter( 9, &callsign );
        statement.BindGuidParameter( 10, &shipName );
        statement.BindEnumParameter( 11, &shipType );
        statement.BindInt32Parameter( 12, &dimensionToBow );
        statement.BindInt32Parameter( 13, &dimensionToStern );
        statement.BindInt32Parameter( 14, &dimensionToPort );
        statement.BindInt32Parameter( 15, &dimensionToStarboard );
        statement.BindEnumParameter( 16, &positionFixType );
        statement.BindDateTimeParameter( 17, estimatedTimeOfArrival );
        statement.BindDoubleParameter( 18, &draught );
        statement.BindFixedDBWideStringParameter( 19, destination );
        statement.BindBooleanParameter( 20, &dataTerminalReady );
        statement.BindInt32Parameter( 21, &spare );
        statement.ExecDirect( L"{ CALL [AisStaticAndVoyageRelatedDataMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 aisVersion, const Guid& imoNumber, const Guid& callsign, const Guid& shipName, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, const DBDateTime& estimatedTimeOfArrival, double draught, FixedDBWideString<100> destination, bool dataTerminalReady, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &aisVersion );
        statement.BindGuidParameter( 9, &imoNumber );
        statement.BindGuidParameter( 10, &callsign );
        statement.BindGuidParameter( 11, &shipName );
        statement.BindEnumParameter( 12, &shipType );
        statement.BindInt32Parameter( 13, &dimensionToBow );
        statement.BindInt32Parameter( 14, &dimensionToStern );
        statement.BindInt32Parameter( 15, &dimensionToPort );
        statement.BindInt32Parameter( 16, &dimensionToStarboard );
        statement.BindEnumParameter( 17, &positionFixType );
        statement.BindDateTimeParameter( 18, estimatedTimeOfArrival );
        statement.BindDoubleParameter( 19, &draught );
        statement.BindFixedDBWideStringParameter( 20, destination );
        statement.BindBooleanParameter( 21, &dataTerminalReady );
        statement.BindInt32Parameter( 22, &spare );
        statement.ExecDirect( L"{ CALL [AisStaticAndVoyageRelatedDataMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisStaticAndVoyageRelatedDataMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisStaticDataReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &partNumber );
        statement.ExecDirect( L"{ CALL [AisStaticDataReportMessageInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisStaticDataReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &partNumber );
        statement.ExecDirect( L"{ CALL [AisStaticDataReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisStaticDataReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisStaticDataReportMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisStaticDataReportPartAMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, const Guid& shipName, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &partNumber );
        statement.BindGuidParameter( 8, &shipName );
        statement.BindInt32Parameter( 9, &spare );
        statement.ExecDirect( L"{ CALL [AisStaticDataReportPartAMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisStaticDataReportPartAMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, const Guid& shipName, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &partNumber );
        statement.BindGuidParameter( 9, &shipName );
        statement.BindInt32Parameter( 10, &spare );
        statement.ExecDirect( L"{ CALL [AisStaticDataReportPartAMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisStaticDataReportPartAMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisStaticDataReportPartAMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisStaticDataReportPartBMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, Data::ShipType shipType, FixedDBWideString<100> vendorId, Int32 unitModelCode, Int32 serialNumber, const Guid& callsign, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, const DBGuid& mothershipMmsi, Data::PositionFixType positionFixType, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &partNumber );
        statement.BindEnumParameter( 8, &shipType );
        statement.BindFixedDBWideStringParameter( 9, vendorId );
        statement.BindInt32Parameter( 10, &unitModelCode );
        statement.BindInt32Parameter( 11, &serialNumber );
        statement.BindGuidParameter( 12, &callsign );
        statement.BindInt32Parameter( 13, &dimensionToBow );
        statement.BindInt32Parameter( 14, &dimensionToStern );
        statement.BindInt32Parameter( 15, &dimensionToPort );
        statement.BindInt32Parameter( 16, &dimensionToStarboard );
        statement.BindGuidParameter( 17, mothershipMmsi );
        statement.BindEnumParameter( 18, &positionFixType );
        statement.BindInt32Parameter( 19, &spare );
        statement.ExecDirect( L"{ CALL [AisStaticDataReportPartBMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisStaticDataReportPartBMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, Data::ShipType shipType, FixedDBWideString<100> vendorId, Int32 unitModelCode, Int32 serialNumber, const Guid& callsign, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, const DBGuid& mothershipMmsi, Data::PositionFixType positionFixType, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &partNumber );
        statement.BindEnumParameter( 9, &shipType );
        statement.BindFixedDBWideStringParameter( 10, vendorId );
        statement.BindInt32Parameter( 11, &unitModelCode );
        statement.BindInt32Parameter( 12, &serialNumber );
        statement.BindGuidParameter( 13, &callsign );
        statement.BindInt32Parameter( 14, &dimensionToBow );
        statement.BindInt32Parameter( 15, &dimensionToStern );
        statement.BindInt32Parameter( 16, &dimensionToPort );
        statement.BindInt32Parameter( 17, &dimensionToStarboard );
        statement.BindGuidParameter( 18, mothershipMmsi );
        statement.BindEnumParameter( 19, &positionFixType );
        statement.BindInt32Parameter( 20, &spare );
        statement.ExecDirect( L"{ CALL [AisStaticDataReportPartBMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisStaticDataReportPartBMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisStaticDataReportPartBMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare1, Int32 destinationMmsi, Int32 spare2 )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &spare1 );
        statement.BindInt32Parameter( 8, &destinationMmsi );
        statement.BindInt32Parameter( 9, &spare2 );
        statement.ExecDirect( L"{ CALL [AisUtcAndDateInquiryMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare1, Int32 destinationMmsi, Int32 spare2 )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &spare1 );
        statement.BindInt32Parameter( 9, &destinationMmsi );
        statement.BindInt32Parameter( 10, &spare2 );
        statement.ExecDirect( L"{ CALL [AisUtcAndDateInquiryMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisUtcAndDateInquiryMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisUtcAndDateResponseMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& datetime, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindDateTimeParameter( 7, datetime );
        statement.BindEnumParameter( 8, &positionAccuracy );
        statement.BindDoubleParameter( 9, &longitude );
        statement.BindDoubleParameter( 10, &latitude );
        statement.BindEnumParameter( 11, &positionFixType );
        statement.BindInt32Parameter( 12, &spare );
        statement.BindEnumParameter( 13, &raim );
        statement.BindInt32Parameter( 14, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisUtcAndDateResponseMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisUtcAndDateResponseMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& datetime, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindDateTimeParameter( 8, datetime );
        statement.BindEnumParameter( 9, &positionAccuracy );
        statement.BindDoubleParameter( 10, &longitude );
        statement.BindDoubleParameter( 11, &latitude );
        statement.BindEnumParameter( 12, &positionFixType );
        statement.BindInt32Parameter( 13, &spare );
        statement.BindEnumParameter( 14, &raim );
        statement.BindInt32Parameter( 15, &radioStatus );
        statement.ExecDirect( L"{ CALL [AisUtcAndDateResponseMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisUtcAndDateResponseMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisUtcAndDateResponseMessageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAlarmStateChange( const ODBC::Connection& connection, Guid& id, const Guid& alarm, const DateTime& timestamp, Data::AlarmState state )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &alarm );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &state );
        statement.ExecDirect( L"{ CALL [AlarmStateChangeInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAlarmStateChange( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& alarm, const DateTime& timestamp, Data::AlarmState state )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &alarm );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &state );
        statement.ExecDirect( L"{ CALL [AlarmStateChangeUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAlarmStateChange( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AlarmStateChangeDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBaseStationType( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.ExecDirect( L"{ CALL [BaseStationTypeInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBaseStationType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.ExecDirect( L"{ CALL [BaseStationTypeUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBaseStationType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BaseStationTypeDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBinaryTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const Binary& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindBinaryParameter( 4, value );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBinaryTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const Binary& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindBinaryParameter( 5, value );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBinaryTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBookmark( const ODBC::Connection& connection, Guid& id, const Guid& view, FixedDBWideString<100> name, const DBDateTime& timestamp, double latitude, double longitude, double zoomLevel )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &view );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &latitude );
        statement.BindDoubleParameter( 6, &longitude );
        statement.BindDoubleParameter( 7, &zoomLevel );
        statement.ExecDirect( L"{ CALL [BookmarkInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBookmark( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, FixedDBWideString<100> name, const DBDateTime& timestamp, double latitude, double longitude, double zoomLevel )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &view );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindDoubleParameter( 7, &longitude );
        statement.BindDoubleParameter( 8, &zoomLevel );
        statement.ExecDirect( L"{ CALL [BookmarkUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBookmark( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BookmarkDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBooleanTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBBoolean & value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindBooleanParameter( 4, value );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBooleanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBBoolean & value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindBooleanParameter( 5, value );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBooleanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertByteTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBByte& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindByteParameter( 4, value );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBByte& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindByteParameter( 5, value );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommand( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [CameraCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [CameraCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandAbsoluteMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, Data::CameraPanTiltMode positionPanTiltMode, const DBDouble& panAngle, const DBDouble& tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, const DBDouble& focalLength, Data::CameraPanTiltMode speedPanTiltMode, const DBDouble& panSpeed, const DBDouble& tiltSpeed, Data::CameraFocalLengthMode speedFocalLengthMode, const DBDouble& zoomSpeed )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindEnumParameter( 7, &positionPanTiltMode );
        statement.BindDoubleParameter( 8, panAngle );
        statement.BindDoubleParameter( 9, tiltAngle );
        statement.BindEnumParameter( 10, &positionFocalLengthMode );
        statement.BindDoubleParameter( 11, focalLength );
        statement.BindEnumParameter( 12, &speedPanTiltMode );
        statement.BindDoubleParameter( 13, panSpeed );
        statement.BindDoubleParameter( 14, tiltSpeed );
        statement.BindEnumParameter( 15, &speedFocalLengthMode );
        statement.BindDoubleParameter( 16, zoomSpeed );
        statement.ExecDirect( L"{ CALL [CameraCommandAbsoluteMoveInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandAbsoluteMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, Data::CameraPanTiltMode positionPanTiltMode, const DBDouble& panAngle, const DBDouble& tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, const DBDouble& focalLength, Data::CameraPanTiltMode speedPanTiltMode, const DBDouble& panSpeed, const DBDouble& tiltSpeed, Data::CameraFocalLengthMode speedFocalLengthMode, const DBDouble& zoomSpeed )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindEnumParameter( 8, &positionPanTiltMode );
        statement.BindDoubleParameter( 9, panAngle );
        statement.BindDoubleParameter( 10, tiltAngle );
        statement.BindEnumParameter( 11, &positionFocalLengthMode );
        statement.BindDoubleParameter( 12, focalLength );
        statement.BindEnumParameter( 13, &speedPanTiltMode );
        statement.BindDoubleParameter( 14, panSpeed );
        statement.BindDoubleParameter( 15, tiltSpeed );
        statement.BindEnumParameter( 16, &speedFocalLengthMode );
        statement.BindDoubleParameter( 17, zoomSpeed );
        statement.ExecDirect( L"{ CALL [CameraCommandAbsoluteMoveUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandAbsoluteMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandAbsoluteMoveDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const DBDouble& x, const DBDouble& y, const DBDouble& z )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindDoubleParameter( 7, x );
        statement.BindDoubleParameter( 8, y );
        statement.BindDoubleParameter( 9, z );
        statement.ExecDirect( L"{ CALL [CameraCommandAdjustPanTiltZoomInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const DBDouble& x, const DBDouble& y, const DBDouble& z )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindDoubleParameter( 8, x );
        statement.BindDoubleParameter( 9, y );
        statement.BindDoubleParameter( 10, z );
        statement.ExecDirect( L"{ CALL [CameraCommandAdjustPanTiltZoomUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandAdjustPanTiltZoomDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandContinuousMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panVelocity, const DBDouble& tiltVelocity, const DBDouble& zoomVelocity, const DBTimeSpan& duration )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &normalized );
        statement.BindDoubleParameter( 8, panVelocity );
        statement.BindDoubleParameter( 9, tiltVelocity );
        statement.BindDoubleParameter( 10, zoomVelocity );
        statement.BindTimeSpanParameter( 11, duration );
        statement.ExecDirect( L"{ CALL [CameraCommandContinuousMoveInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandContinuousMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panVelocity, const DBDouble& tiltVelocity, const DBDouble& zoomVelocity, const DBTimeSpan& duration )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &normalized );
        statement.BindDoubleParameter( 9, panVelocity );
        statement.BindDoubleParameter( 10, tiltVelocity );
        statement.BindDoubleParameter( 11, zoomVelocity );
        statement.BindTimeSpanParameter( 12, duration );
        statement.ExecDirect( L"{ CALL [CameraCommandContinuousMoveUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandContinuousMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandContinuousMoveDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandGeoMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, double latitude, double longitude, const DBDouble& altitude, const DBDouble& viewportWidth, const DBDouble& viewportHeight )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindDoubleParameter( 7, &latitude );
        statement.BindDoubleParameter( 8, &longitude );
        statement.BindDoubleParameter( 9, altitude );
        statement.BindDoubleParameter( 10, viewportWidth );
        statement.BindDoubleParameter( 11, viewportHeight );
        statement.ExecDirect( L"{ CALL [CameraCommandGeoMoveInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandGeoMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, double latitude, double longitude, const DBDouble& altitude, const DBDouble& viewportWidth, const DBDouble& viewportHeight )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindDoubleParameter( 8, &latitude );
        statement.BindDoubleParameter( 9, &longitude );
        statement.BindDoubleParameter( 10, altitude );
        statement.BindDoubleParameter( 11, viewportWidth );
        statement.BindDoubleParameter( 12, viewportHeight );
        statement.ExecDirect( L"{ CALL [CameraCommandGeoMoveUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandGeoMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandGeoMoveDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandRelativeMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panAngle, const DBDouble& tiltAngle, const DBDouble& focalLength, const DBDouble& panSpeed, const DBDouble& tiltSpeed, const DBDouble& zoomSpeed )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &normalized );
        statement.BindDoubleParameter( 8, panAngle );
        statement.BindDoubleParameter( 9, tiltAngle );
        statement.BindDoubleParameter( 10, focalLength );
        statement.BindDoubleParameter( 11, panSpeed );
        statement.BindDoubleParameter( 12, tiltSpeed );
        statement.BindDoubleParameter( 13, zoomSpeed );
        statement.ExecDirect( L"{ CALL [CameraCommandRelativeMoveInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandRelativeMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panAngle, const DBDouble& tiltAngle, const DBDouble& focalLength, const DBDouble& panSpeed, const DBDouble& tiltSpeed, const DBDouble& zoomSpeed )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &normalized );
        statement.BindDoubleParameter( 9, panAngle );
        statement.BindDoubleParameter( 10, tiltAngle );
        statement.BindDoubleParameter( 11, focalLength );
        statement.BindDoubleParameter( 12, panSpeed );
        statement.BindDoubleParameter( 13, tiltSpeed );
        statement.BindDoubleParameter( 14, zoomSpeed );
        statement.ExecDirect( L"{ CALL [CameraCommandRelativeMoveUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandRelativeMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandRelativeMoveDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [CameraCommandReleasePTZOwnershipInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [CameraCommandReleasePTZOwnershipUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandReleasePTZOwnershipDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [CameraCommandRequestPTZOwnershipInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [CameraCommandRequestPTZOwnershipUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandRequestPTZOwnershipDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandSetAutoFocus( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &enabled );
        statement.ExecDirect( L"{ CALL [CameraCommandSetAutoFocusInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandSetAutoFocus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &enabled );
        statement.ExecDirect( L"{ CALL [CameraCommandSetAutoFocusUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandSetAutoFocus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandSetAutoFocusDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &enabled );
        statement.ExecDirect( L"{ CALL [CameraCommandSetBlackAndWhiteInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &enabled );
        statement.ExecDirect( L"{ CALL [CameraCommandSetBlackAndWhiteUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandSetBlackAndWhiteDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandSetFollowed( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const Guid& trackId, Data::CameraFollowReason reason )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindGuidParameter( 7, &trackId );
        statement.BindEnumParameter( 8, &reason );
        statement.ExecDirect( L"{ CALL [CameraCommandSetFollowedInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandSetFollowed( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const Guid& trackId, Data::CameraFollowReason reason )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindGuidParameter( 8, &trackId );
        statement.BindEnumParameter( 9, &reason );
        statement.ExecDirect( L"{ CALL [CameraCommandSetFollowedUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandSetFollowed( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandSetFollowedDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &enabled );
        statement.ExecDirect( L"{ CALL [CameraCommandSetInfraRedLampInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &enabled );
        statement.ExecDirect( L"{ CALL [CameraCommandSetInfraRedLampUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandSetInfraRedLampDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandSetWasher( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &enabled );
        statement.ExecDirect( L"{ CALL [CameraCommandSetWasherInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandSetWasher( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &enabled );
        statement.ExecDirect( L"{ CALL [CameraCommandSetWasherUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandSetWasher( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandSetWasherDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandSetWiper( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &enabled );
        statement.ExecDirect( L"{ CALL [CameraCommandSetWiperInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandSetWiper( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &enabled );
        statement.ExecDirect( L"{ CALL [CameraCommandSetWiperUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandSetWiper( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandSetWiperDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandStop( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool panTilt, bool zoom )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &panTilt );
        statement.BindBooleanParameter( 8, &zoom );
        statement.ExecDirect( L"{ CALL [CameraCommandStopInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandStop( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool panTilt, bool zoom )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &panTilt );
        statement.BindBooleanParameter( 9, &zoom );
        statement.ExecDirect( L"{ CALL [CameraCommandStopUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandStop( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandStopDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, double panAngle, double tiltAngle, double focalLength )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.BindDoubleParameter( 7, &panAngle );
        statement.BindDoubleParameter( 8, &tiltAngle );
        statement.BindDoubleParameter( 9, &focalLength );
        statement.ExecDirect( L"{ CALL [CameraCommandReplyInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, double panAngle, double tiltAngle, double focalLength )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.BindDoubleParameter( 8, &panAngle );
        statement.BindDoubleParameter( 9, &tiltAngle );
        statement.BindDoubleParameter( 10, &focalLength );
        statement.ExecDirect( L"{ CALL [CameraCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraCommandReplyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::CameraControlProtocol cameraControlProtocol, FixedDBWideString<127> cameraAddress, Int32 cameraPort, FixedDBWideString<127> cameraControlAddress, Int32 cameraControlPort, FixedDBWideString<127> cameraUserName, FixedDBWideString<127> cameraPassword, bool useRtspUriOverride, FixedDBWideString<127> rtspUriOverride, double latitude, double longitude, double altitude, bool useRelativePosition, double azimuthFromGPS, double distanceFromGPS, Data::CameraPanTiltMode panTiltMode, double minTiltAngle, double maxTiltAngle, double minTiltScaleAngle, double maxTiltScaleAngle, bool useReverseTiltAngle, bool useReverseNormalizedTiltAngle, double minTiltVelocity, double maxTiltVelocity, double minTiltSpeed, double maxTiltSpeed, double minPanAngle, double maxPanAngle, double minPanScaleAngle, double maxPanScaleAngle, bool useReversePanAngle, bool useReverseNormalizedPanAngle, double minPanVelocity, double maxPanVelocity, double minPanSpeed, double maxPanSpeed, Data::CameraFocalLengthMode focalLengthMode, double minFocalLength, double maxFocalLength, double minFocalLengthScale, double maxFocalLengthScale, double minZoomVelocity, double maxZoomVelocity, double minZoomSpeed, double maxZoomSpeed, double imageSensorWidth, double imageSensorHeight, double homePanAngle, double homeTiltAngle, double homeFocalLength, double panOffset, double tiltOffset, double aimAltitude, double minimumTargetWidth, const TimeSpan& targetLockTimeout, const TimeSpan& updateStatusInterval, const TimeSpan& readTimeout, const TimeSpan& moveCommandStatusDelay, FixedDBWideString<127> ptzProfileName, FixedDBWideString<127> ptzConfigurationToken, FixedDBWideString<127> videoSourceToken )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &cameraControlProtocol );
        statement.BindFixedDBWideStringParameter( 5, cameraAddress );
        statement.BindInt32Parameter( 6, &cameraPort );
        statement.BindFixedDBWideStringParameter( 7, cameraControlAddress );
        statement.BindInt32Parameter( 8, &cameraControlPort );
        statement.BindFixedDBWideStringParameter( 9, cameraUserName );
        statement.BindFixedDBWideStringParameter( 10, cameraPassword );
        statement.BindBooleanParameter( 11, &useRtspUriOverride );
        statement.BindFixedDBWideStringParameter( 12, rtspUriOverride );
        statement.BindDoubleParameter( 13, &latitude );
        statement.BindDoubleParameter( 14, &longitude );
        statement.BindDoubleParameter( 15, &altitude );
        statement.BindBooleanParameter( 16, &useRelativePosition );
        statement.BindDoubleParameter( 17, &azimuthFromGPS );
        statement.BindDoubleParameter( 18, &distanceFromGPS );
        statement.BindEnumParameter( 19, &panTiltMode );
        statement.BindDoubleParameter( 20, &minTiltAngle );
        statement.BindDoubleParameter( 21, &maxTiltAngle );
        statement.BindDoubleParameter( 22, &minTiltScaleAngle );
        statement.BindDoubleParameter( 23, &maxTiltScaleAngle );
        statement.BindBooleanParameter( 24, &useReverseTiltAngle );
        statement.BindBooleanParameter( 25, &useReverseNormalizedTiltAngle );
        statement.BindDoubleParameter( 26, &minTiltVelocity );
        statement.BindDoubleParameter( 27, &maxTiltVelocity );
        statement.BindDoubleParameter( 28, &minTiltSpeed );
        statement.BindDoubleParameter( 29, &maxTiltSpeed );
        statement.BindDoubleParameter( 30, &minPanAngle );
        statement.BindDoubleParameter( 31, &maxPanAngle );
        statement.BindDoubleParameter( 32, &minPanScaleAngle );
        statement.BindDoubleParameter( 33, &maxPanScaleAngle );
        statement.BindBooleanParameter( 34, &useReversePanAngle );
        statement.BindBooleanParameter( 35, &useReverseNormalizedPanAngle );
        statement.BindDoubleParameter( 36, &minPanVelocity );
        statement.BindDoubleParameter( 37, &maxPanVelocity );
        statement.BindDoubleParameter( 38, &minPanSpeed );
        statement.BindDoubleParameter( 39, &maxPanSpeed );
        statement.BindEnumParameter( 40, &focalLengthMode );
        statement.BindDoubleParameter( 41, &minFocalLength );
        statement.BindDoubleParameter( 42, &maxFocalLength );
        statement.BindDoubleParameter( 43, &minFocalLengthScale );
        statement.BindDoubleParameter( 44, &maxFocalLengthScale );
        statement.BindDoubleParameter( 45, &minZoomVelocity );
        statement.BindDoubleParameter( 46, &maxZoomVelocity );
        statement.BindDoubleParameter( 47, &minZoomSpeed );
        statement.BindDoubleParameter( 48, &maxZoomSpeed );
        statement.BindDoubleParameter( 49, &imageSensorWidth );
        statement.BindDoubleParameter( 50, &imageSensorHeight );
        statement.BindDoubleParameter( 51, &homePanAngle );
        statement.BindDoubleParameter( 52, &homeTiltAngle );
        statement.BindDoubleParameter( 53, &homeFocalLength );
        statement.BindDoubleParameter( 54, &panOffset );
        statement.BindDoubleParameter( 55, &tiltOffset );
        statement.BindDoubleParameter( 56, &aimAltitude );
        statement.BindDoubleParameter( 57, &minimumTargetWidth );
        statement.BindTimeSpanParameter( 58, targetLockTimeout );
        statement.BindTimeSpanParameter( 59, updateStatusInterval );
        statement.BindTimeSpanParameter( 60, readTimeout );
        statement.BindTimeSpanParameter( 61, moveCommandStatusDelay );
        statement.BindFixedDBWideStringParameter( 62, ptzProfileName );
        statement.BindFixedDBWideStringParameter( 63, ptzConfigurationToken );
        statement.BindFixedDBWideStringParameter( 64, videoSourceToken );
        statement.ExecDirect( L"{ CALL [CameraConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::CameraControlProtocol cameraControlProtocol, FixedDBWideString<127> cameraAddress, Int32 cameraPort, FixedDBWideString<127> cameraControlAddress, Int32 cameraControlPort, FixedDBWideString<127> cameraUserName, FixedDBWideString<127> cameraPassword, bool useRtspUriOverride, FixedDBWideString<127> rtspUriOverride, double latitude, double longitude, double altitude, bool useRelativePosition, double azimuthFromGPS, double distanceFromGPS, Data::CameraPanTiltMode panTiltMode, double minTiltAngle, double maxTiltAngle, double minTiltScaleAngle, double maxTiltScaleAngle, bool useReverseTiltAngle, bool useReverseNormalizedTiltAngle, double minTiltVelocity, double maxTiltVelocity, double minTiltSpeed, double maxTiltSpeed, double minPanAngle, double maxPanAngle, double minPanScaleAngle, double maxPanScaleAngle, bool useReversePanAngle, bool useReverseNormalizedPanAngle, double minPanVelocity, double maxPanVelocity, double minPanSpeed, double maxPanSpeed, Data::CameraFocalLengthMode focalLengthMode, double minFocalLength, double maxFocalLength, double minFocalLengthScale, double maxFocalLengthScale, double minZoomVelocity, double maxZoomVelocity, double minZoomSpeed, double maxZoomSpeed, double imageSensorWidth, double imageSensorHeight, double homePanAngle, double homeTiltAngle, double homeFocalLength, double panOffset, double tiltOffset, double aimAltitude, double minimumTargetWidth, const TimeSpan& targetLockTimeout, const TimeSpan& updateStatusInterval, const TimeSpan& readTimeout, const TimeSpan& moveCommandStatusDelay, FixedDBWideString<127> ptzProfileName, FixedDBWideString<127> ptzConfigurationToken, FixedDBWideString<127> videoSourceToken )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &cameraControlProtocol );
        statement.BindFixedDBWideStringParameter( 6, cameraAddress );
        statement.BindInt32Parameter( 7, &cameraPort );
        statement.BindFixedDBWideStringParameter( 8, cameraControlAddress );
        statement.BindInt32Parameter( 9, &cameraControlPort );
        statement.BindFixedDBWideStringParameter( 10, cameraUserName );
        statement.BindFixedDBWideStringParameter( 11, cameraPassword );
        statement.BindBooleanParameter( 12, &useRtspUriOverride );
        statement.BindFixedDBWideStringParameter( 13, rtspUriOverride );
        statement.BindDoubleParameter( 14, &latitude );
        statement.BindDoubleParameter( 15, &longitude );
        statement.BindDoubleParameter( 16, &altitude );
        statement.BindBooleanParameter( 17, &useRelativePosition );
        statement.BindDoubleParameter( 18, &azimuthFromGPS );
        statement.BindDoubleParameter( 19, &distanceFromGPS );
        statement.BindEnumParameter( 20, &panTiltMode );
        statement.BindDoubleParameter( 21, &minTiltAngle );
        statement.BindDoubleParameter( 22, &maxTiltAngle );
        statement.BindDoubleParameter( 23, &minTiltScaleAngle );
        statement.BindDoubleParameter( 24, &maxTiltScaleAngle );
        statement.BindBooleanParameter( 25, &useReverseTiltAngle );
        statement.BindBooleanParameter( 26, &useReverseNormalizedTiltAngle );
        statement.BindDoubleParameter( 27, &minTiltVelocity );
        statement.BindDoubleParameter( 28, &maxTiltVelocity );
        statement.BindDoubleParameter( 29, &minTiltSpeed );
        statement.BindDoubleParameter( 30, &maxTiltSpeed );
        statement.BindDoubleParameter( 31, &minPanAngle );
        statement.BindDoubleParameter( 32, &maxPanAngle );
        statement.BindDoubleParameter( 33, &minPanScaleAngle );
        statement.BindDoubleParameter( 34, &maxPanScaleAngle );
        statement.BindBooleanParameter( 35, &useReversePanAngle );
        statement.BindBooleanParameter( 36, &useReverseNormalizedPanAngle );
        statement.BindDoubleParameter( 37, &minPanVelocity );
        statement.BindDoubleParameter( 38, &maxPanVelocity );
        statement.BindDoubleParameter( 39, &minPanSpeed );
        statement.BindDoubleParameter( 40, &maxPanSpeed );
        statement.BindEnumParameter( 41, &focalLengthMode );
        statement.BindDoubleParameter( 42, &minFocalLength );
        statement.BindDoubleParameter( 43, &maxFocalLength );
        statement.BindDoubleParameter( 44, &minFocalLengthScale );
        statement.BindDoubleParameter( 45, &maxFocalLengthScale );
        statement.BindDoubleParameter( 46, &minZoomVelocity );
        statement.BindDoubleParameter( 47, &maxZoomVelocity );
        statement.BindDoubleParameter( 48, &minZoomSpeed );
        statement.BindDoubleParameter( 49, &maxZoomSpeed );
        statement.BindDoubleParameter( 50, &imageSensorWidth );
        statement.BindDoubleParameter( 51, &imageSensorHeight );
        statement.BindDoubleParameter( 52, &homePanAngle );
        statement.BindDoubleParameter( 53, &homeTiltAngle );
        statement.BindDoubleParameter( 54, &homeFocalLength );
        statement.BindDoubleParameter( 55, &panOffset );
        statement.BindDoubleParameter( 56, &tiltOffset );
        statement.BindDoubleParameter( 57, &aimAltitude );
        statement.BindDoubleParameter( 58, &minimumTargetWidth );
        statement.BindTimeSpanParameter( 59, targetLockTimeout );
        statement.BindTimeSpanParameter( 60, updateStatusInterval );
        statement.BindTimeSpanParameter( 61, readTimeout );
        statement.BindTimeSpanParameter( 62, moveCommandStatusDelay );
        statement.BindFixedDBWideStringParameter( 63, ptzProfileName );
        statement.BindFixedDBWideStringParameter( 64, ptzConfigurationToken );
        statement.BindFixedDBWideStringParameter( 65, videoSourceToken );
        statement.ExecDirect( L"{ CALL [CameraConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraPanCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.ExecDirect( L"{ CALL [CameraPanCalibrationInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraPanCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.ExecDirect( L"{ CALL [CameraPanCalibrationUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraPanCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraPanCalibrationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraPanCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& panCalibration, double panAngle, double panOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &panCalibration );
        statement.BindDoubleParameter( 3, &panAngle );
        statement.BindDoubleParameter( 4, &panOffset );
        statement.ExecDirect( L"{ CALL [CameraPanCalibrationValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraPanCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& panCalibration, double panAngle, double panOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &panCalibration );
        statement.BindDoubleParameter( 4, &panAngle );
        statement.BindDoubleParameter( 5, &panOffset );
        statement.ExecDirect( L"{ CALL [CameraPanCalibrationValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraPanCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraPanCalibrationValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraStatus( const ODBC::Connection& connection, Guid& id, const Guid& camera, const Guid& track, const DateTime& timestamp, Data::CameraPanTiltMode positionPanTiltMode, double panAngle, double tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, double focalLength, Data::CameraMoveStatus panTiltMoveStatus, Data::CameraMoveStatus zoomMoveStatus, Data::CameraPanTiltMode velocityPanTiltMode, const DBDouble& panVelocity, const DBDouble& tiltVelocity, Data::CameraFocalLengthMode velocityFocalLengthMode, const DBDouble& zoomVelocity, Data::CameraFeatures activeFeatures, const WideString& error )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindGuidParameter( 3, &track );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &positionPanTiltMode );
        statement.BindDoubleParameter( 6, &panAngle );
        statement.BindDoubleParameter( 7, &tiltAngle );
        statement.BindEnumParameter( 8, &positionFocalLengthMode );
        statement.BindDoubleParameter( 9, &focalLength );
        statement.BindEnumParameter( 10, &panTiltMoveStatus );
        statement.BindEnumParameter( 11, &zoomMoveStatus );
        statement.BindEnumParameter( 12, &velocityPanTiltMode );
        statement.BindDoubleParameter( 13, panVelocity );
        statement.BindDoubleParameter( 14, tiltVelocity );
        statement.BindEnumParameter( 15, &velocityFocalLengthMode );
        statement.BindDoubleParameter( 16, zoomVelocity );
        statement.BindEnumParameter( 17, &activeFeatures );
        statement.BindWideStringParameter( 18, error );
        statement.ExecDirect( L"{ CALL [CameraStatusInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const Guid& track, const DateTime& timestamp, Data::CameraPanTiltMode positionPanTiltMode, double panAngle, double tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, double focalLength, Data::CameraMoveStatus panTiltMoveStatus, Data::CameraMoveStatus zoomMoveStatus, Data::CameraPanTiltMode velocityPanTiltMode, const DBDouble& panVelocity, const DBDouble& tiltVelocity, Data::CameraFocalLengthMode velocityFocalLengthMode, const DBDouble& zoomVelocity, Data::CameraFeatures activeFeatures, const WideString& error )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindGuidParameter( 4, &track );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.BindEnumParameter( 6, &positionPanTiltMode );
        statement.BindDoubleParameter( 7, &panAngle );
        statement.BindDoubleParameter( 8, &tiltAngle );
        statement.BindEnumParameter( 9, &positionFocalLengthMode );
        statement.BindDoubleParameter( 10, &focalLength );
        statement.BindEnumParameter( 11, &panTiltMoveStatus );
        statement.BindEnumParameter( 12, &zoomMoveStatus );
        statement.BindEnumParameter( 13, &velocityPanTiltMode );
        statement.BindDoubleParameter( 14, panVelocity );
        statement.BindDoubleParameter( 15, tiltVelocity );
        statement.BindEnumParameter( 16, &velocityFocalLengthMode );
        statement.BindDoubleParameter( 17, zoomVelocity );
        statement.BindEnumParameter( 18, &activeFeatures );
        statement.BindWideStringParameter( 19, error );
        statement.ExecDirect( L"{ CALL [CameraStatusUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraStatusDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraTiltCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.ExecDirect( L"{ CALL [CameraTiltCalibrationInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraTiltCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.ExecDirect( L"{ CALL [CameraTiltCalibrationUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraTiltCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraTiltCalibrationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraTiltCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& tiltCalibration, double panAngle, double tiltOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &tiltCalibration );
        statement.BindDoubleParameter( 3, &panAngle );
        statement.BindDoubleParameter( 4, &tiltOffset );
        statement.ExecDirect( L"{ CALL [CameraTiltCalibrationValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraTiltCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tiltCalibration, double panAngle, double tiltOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &tiltCalibration );
        statement.BindDoubleParameter( 4, &panAngle );
        statement.BindDoubleParameter( 5, &tiltOffset );
        statement.ExecDirect( L"{ CALL [CameraTiltCalibrationValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraTiltCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraTiltCalibrationValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraZoomCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.ExecDirect( L"{ CALL [CameraZoomCalibrationInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraZoomCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.ExecDirect( L"{ CALL [CameraZoomCalibrationUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraZoomCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraZoomCalibrationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraZoomCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& zoomCalibration, double focalLength, double focalLengthOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &zoomCalibration );
        statement.BindDoubleParameter( 3, &focalLength );
        statement.BindDoubleParameter( 4, &focalLengthOffset );
        statement.ExecDirect( L"{ CALL [CameraZoomCalibrationValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraZoomCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zoomCalibration, double focalLength, double focalLengthOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &zoomCalibration );
        statement.BindDoubleParameter( 4, &focalLength );
        statement.BindDoubleParameter( 5, &focalLengthOffset );
        statement.ExecDirect( L"{ CALL [CameraZoomCalibrationValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraZoomCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraZoomCalibrationValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCatalog( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.ExecDirect( L"{ CALL [CatalogInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCatalog( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.ExecDirect( L"{ CALL [CatalogUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCatalog( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CatalogDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertElement( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<127> name, const Guid& elementType )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &elementType );
        statement.ExecDirect( L"{ CALL [ElementInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateElement( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<127> name, const Guid& elementType )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindGuidParameter( 5, &elementType );
        statement.ExecDirect( L"{ CALL [ElementUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteElement( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ElementDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCollectionInfo( const ODBC::Connection& connection, Guid& id, Int64 count )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &count );
        statement.ExecDirect( L"{ CALL [CollectionInfoInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCollectionInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 count )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindInt64Parameter( 3, &count );
        statement.ExecDirect( L"{ CALL [CollectionInfoUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCollectionInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CollectionInfoDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCountry( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, Int32 code, FixedDBWideString<2> alpha2, FixedDBWideString<3> alpha3 )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindInt32Parameter( 3, &code );
        statement.BindFixedDBWideStringParameter( 4, alpha2 );
        statement.BindFixedDBWideStringParameter( 5, alpha3 );
        statement.ExecDirect( L"{ CALL [CountryInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCountry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, Int32 code, FixedDBWideString<2> alpha2, FixedDBWideString<3> alpha3 )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindInt32Parameter( 4, &code );
        statement.BindFixedDBWideStringParameter( 5, alpha2 );
        statement.BindFixedDBWideStringParameter( 6, alpha3 );
        statement.ExecDirect( L"{ CALL [CountryUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCountry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CountryDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCursorInfo( const ODBC::Connection& connection, Guid& id, Int32 typeCode )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt32Parameter( 2, &typeCode );
        statement.ExecDirect( L"{ CALL [CursorInfoInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCursorInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 typeCode )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindInt32Parameter( 3, &typeCode );
        statement.ExecDirect( L"{ CALL [CursorInfoUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCursorInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CursorInfoDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDateTimeTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDateTime& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDateTimeParameter( 4, value );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDateTimeTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDateTime& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDateTimeParameter( 5, value );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDateTimeTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDeviceHost( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.ExecDirect( L"{ CALL [DeviceHostInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDeviceHost( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.ExecDirect( L"{ CALL [DeviceHostUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDeviceHost( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DeviceHostDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDeviceHostConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& host, const DateTime& timestamp, FixedDBWideString<127> hostname, Int32 port, FixedDBWideString<100> queueName )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindFixedDBWideStringParameter( 4, hostname );
        statement.BindInt32Parameter( 5, &port );
        statement.BindFixedDBWideStringParameter( 6, queueName );
        statement.ExecDirect( L"{ CALL [DeviceHostConfigurationInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDeviceHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const DateTime& timestamp, FixedDBWideString<127> hostname, Int32 port, FixedDBWideString<100> queueName )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindFixedDBWideStringParameter( 5, hostname );
        statement.BindInt32Parameter( 6, &port );
        statement.BindFixedDBWideStringParameter( 7, queueName );
        statement.ExecDirect( L"{ CALL [DeviceHostConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDeviceHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DeviceHostConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDoubleTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, value );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDoubleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, value );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDoubleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertFacilityType( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.ExecDirect( L"{ CALL [FacilityTypeInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateFacilityType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.ExecDirect( L"{ CALL [FacilityTypeUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteFacilityType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [FacilityTypeDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, latitude );
        statement.BindDoubleParameter( 5, longitude );
        statement.ExecDirect( L"{ CALL [GeoPosition2DTimeseriesValueInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, latitude );
        statement.BindDoubleParameter( 6, longitude );
        statement.ExecDirect( L"{ CALL [GeoPosition2DTimeseriesValueUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GeoPosition2DTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude, const DBDouble& altitude )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, latitude );
        statement.BindDoubleParameter( 5, longitude );
        statement.BindDoubleParameter( 6, altitude );
        statement.ExecDirect( L"{ CALL [GeoPosition3DTimeseriesValueInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude, const DBDouble& altitude )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, latitude );
        statement.BindDoubleParameter( 6, longitude );
        statement.BindDoubleParameter( 7, altitude );
        statement.ExecDirect( L"{ CALL [GeoPosition3DTimeseriesValueUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GeoPosition3DTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGNSSDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gNSSDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [GNSSDeviceCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGNSSDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &gNSSDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [GNSSDeviceCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGNSSDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GNSSDeviceCommandDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGNSSDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gNSSDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.ExecDirect( L"{ CALL [GNSSDeviceCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGNSSDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &gNSSDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.ExecDirect( L"{ CALL [GNSSDeviceCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGNSSDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GNSSDeviceCommandReplyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGNSSDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, double defaultLatitude, double defaultLongitude, double defaultAltitude, double latitudeOffset, double longitudeOffset, double altitudeOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gNSSDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, &defaultLatitude );
        statement.BindDoubleParameter( 5, &defaultLongitude );
        statement.BindDoubleParameter( 6, &defaultAltitude );
        statement.BindDoubleParameter( 7, &latitudeOffset );
        statement.BindDoubleParameter( 8, &longitudeOffset );
        statement.BindDoubleParameter( 9, &altitudeOffset );
        statement.ExecDirect( L"{ CALL [GNSSDeviceConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGNSSDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, double defaultLatitude, double defaultLongitude, double defaultAltitude, double latitudeOffset, double longitudeOffset, double altitudeOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &gNSSDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &defaultLatitude );
        statement.BindDoubleParameter( 6, &defaultLongitude );
        statement.BindDoubleParameter( 7, &defaultAltitude );
        statement.BindDoubleParameter( 8, &latitudeOffset );
        statement.BindDoubleParameter( 9, &longitudeOffset );
        statement.BindDoubleParameter( 10, &altitudeOffset );
        statement.ExecDirect( L"{ CALL [GNSSDeviceConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGNSSDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GNSSDeviceConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGuidTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBGuid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, value );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGuidTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBGuid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, value );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGuidTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gyroDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [GyroDeviceCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &gyroDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [GyroDeviceCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroDeviceCommandDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gyroDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.ExecDirect( L"{ CALL [GyroDeviceCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &gyroDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.ExecDirect( L"{ CALL [GyroDeviceCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroDeviceCommandReplyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, double defaultHeadingTrueNorth, double defaultMagneticTrueNorth, double headingTrueNorthOffset, double headingMagneticNorthOffset, FixedDBWideString<64> pitchTransducerName, FixedDBWideString<64> rollTransducerName )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gyroDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, &defaultHeadingTrueNorth );
        statement.BindDoubleParameter( 5, &defaultMagneticTrueNorth );
        statement.BindDoubleParameter( 6, &headingTrueNorthOffset );
        statement.BindDoubleParameter( 7, &headingMagneticNorthOffset );
        statement.BindFixedDBWideStringParameter( 8, pitchTransducerName );
        statement.BindFixedDBWideStringParameter( 9, rollTransducerName );
        statement.ExecDirect( L"{ CALL [GyroDeviceConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, double defaultHeadingTrueNorth, double defaultMagneticTrueNorth, double headingTrueNorthOffset, double headingMagneticNorthOffset, FixedDBWideString<64> pitchTransducerName, FixedDBWideString<64> rollTransducerName )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &gyroDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &defaultHeadingTrueNorth );
        statement.BindDoubleParameter( 6, &defaultMagneticTrueNorth );
        statement.BindDoubleParameter( 7, &headingTrueNorthOffset );
        statement.BindDoubleParameter( 8, &headingMagneticNorthOffset );
        statement.BindFixedDBWideStringParameter( 9, pitchTransducerName );
        statement.BindFixedDBWideStringParameter( 10, rollTransducerName );
        statement.ExecDirect( L"{ CALL [GyroDeviceConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroDeviceConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCallsign( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, identifier );
        statement.ExecDirect( L"{ CALL [CallsignInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCallsign( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, identifier );
        statement.ExecDirect( L"{ CALL [CallsignUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCallsign( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CallsignDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, Guid& id, Int64 identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &identifier );
        statement.ExecDirect( L"{ CALL [InternationalMaritimeOrganizationNumberInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindInt64Parameter( 3, &identifier );
        statement.ExecDirect( L"{ CALL [InternationalMaritimeOrganizationNumberUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [InternationalMaritimeOrganizationNumberDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMaritimeMobileServiceIdentity( const ODBC::Connection& connection, Guid& id, Int64 identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &identifier );
        statement.ExecDirect( L"{ CALL [MaritimeMobileServiceIdentityInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMaritimeMobileServiceIdentity( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindInt64Parameter( 3, &identifier );
        statement.ExecDirect( L"{ CALL [MaritimeMobileServiceIdentityUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMaritimeMobileServiceIdentity( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MaritimeMobileServiceIdentityDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertName( const ODBC::Connection& connection, Guid& id, FixedDBWideString<100> text )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, text );
        statement.ExecDirect( L"{ CALL [NameInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateName( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<100> text )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, text );
        statement.ExecDirect( L"{ CALL [NameUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteName( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [NameDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt16TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt16& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt16Parameter( 4, value );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt16& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt16Parameter( 5, value );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt32TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt32& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, value );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt32& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, value );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt64TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt64Parameter( 4, value );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt64Parameter( 5, value );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBaseStation( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &type );
        statement.ExecDirect( L"{ CALL [BaseStationInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBaseStation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &type );
        statement.ExecDirect( L"{ CALL [BaseStationUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBaseStation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BaseStationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCameraDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [CameraDeviceInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCameraDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [CameraDeviceUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCameraDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CameraDeviceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGNSSDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& altitudeTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.BindGuidParameter( 6, &latitudeTimeseries );
        statement.BindGuidParameter( 7, &longitudeTimeseries );
        statement.BindGuidParameter( 8, &altitudeTimeseries );
        statement.ExecDirect( L"{ CALL [GNSSDeviceInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGNSSDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& altitudeTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.BindGuidParameter( 7, &latitudeTimeseries );
        statement.BindGuidParameter( 8, &longitudeTimeseries );
        statement.BindGuidParameter( 9, &altitudeTimeseries );
        statement.ExecDirect( L"{ CALL [GNSSDeviceUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGNSSDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GNSSDeviceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& headingTrueNorthTimeseries, const Guid& headingMagneticNorthTimeseries, const Guid& pitchTimeseries, const Guid& rateOfTurnTimeseries, const Guid& rollTimeseries, const Guid& courseTimeseries, const Guid& speedTimeseries, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.BindGuidParameter( 6, &headingTrueNorthTimeseries );
        statement.BindGuidParameter( 7, &headingMagneticNorthTimeseries );
        statement.BindGuidParameter( 8, &pitchTimeseries );
        statement.BindGuidParameter( 9, &rateOfTurnTimeseries );
        statement.BindGuidParameter( 10, &rollTimeseries );
        statement.BindGuidParameter( 11, &courseTimeseries );
        statement.BindGuidParameter( 12, &speedTimeseries );
        statement.BindGuidParameter( 13, &gNSSDevice );
        statement.ExecDirect( L"{ CALL [GyroDeviceInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& headingTrueNorthTimeseries, const Guid& headingMagneticNorthTimeseries, const Guid& pitchTimeseries, const Guid& rateOfTurnTimeseries, const Guid& rollTimeseries, const Guid& courseTimeseries, const Guid& speedTimeseries, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.BindGuidParameter( 7, &headingTrueNorthTimeseries );
        statement.BindGuidParameter( 8, &headingMagneticNorthTimeseries );
        statement.BindGuidParameter( 9, &pitchTimeseries );
        statement.BindGuidParameter( 10, &rateOfTurnTimeseries );
        statement.BindGuidParameter( 11, &rollTimeseries );
        statement.BindGuidParameter( 12, &courseTimeseries );
        statement.BindGuidParameter( 13, &speedTimeseries );
        statement.BindGuidParameter( 14, &gNSSDevice );
        statement.ExecDirect( L"{ CALL [GyroDeviceUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroDeviceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLineInputDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [LineInputDeviceInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLineInputDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [LineInputDeviceUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLineInputDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LineInputDeviceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertOilSpillDetectorDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorDeviceInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateOilSpillDetectorDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorDeviceUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteOilSpillDetectorDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorDeviceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadioDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [RadioDeviceInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadioDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [RadioDeviceUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadioDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadioDeviceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadomeDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const DBGuid& radar, const Guid& pressureTimeseries, const Guid& temperatureTimeseries, const Guid& dewPointTimeseries, const Guid& statusTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.BindGuidParameter( 6, radar );
        statement.BindGuidParameter( 7, &pressureTimeseries );
        statement.BindGuidParameter( 8, &temperatureTimeseries );
        statement.BindGuidParameter( 9, &dewPointTimeseries );
        statement.BindGuidParameter( 10, &statusTimeseries );
        statement.ExecDirect( L"{ CALL [RadomeDeviceInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadomeDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const DBGuid& radar, const Guid& pressureTimeseries, const Guid& temperatureTimeseries, const Guid& dewPointTimeseries, const Guid& statusTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.BindGuidParameter( 7, radar );
        statement.BindGuidParameter( 8, &pressureTimeseries );
        statement.BindGuidParameter( 9, &temperatureTimeseries );
        statement.BindGuidParameter( 10, &dewPointTimeseries );
        statement.BindGuidParameter( 11, &statusTimeseries );
        statement.ExecDirect( L"{ CALL [RadomeDeviceUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadomeDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadomeDeviceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [AisDeviceInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [AisDeviceUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisDeviceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& saveSettingsTimeseries, const Guid& powerOnTimeseries, const Guid& trackingOnTimeseries, const Guid& radarPulseTimeseries, const Guid& tuningTimeseries, const Guid& blankSector1Timeseries, const Guid& sector1StartTimeseries, const Guid& sector1EndTimeseries, const Guid& blankSector2Timeseries, const Guid& sector2StartTimeseries, const Guid& sector2EndTimeseries, const Guid& enableAutomaticFrequencyControlTimeseries, const Guid& azimuthOffsetTimeseries, const Guid& enableSensitivityTimeControlTimeseries, const Guid& automaticSensitivityTimeControlTimeseries, const Guid& sensitivityTimeControlLevelTimeseries, const Guid& enableFastTimeConstantTimeseries, const Guid& fastTimeConstantLevelTimeseries, const Guid& fastTimeConstantModeTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const DBGuid& radome, const DBGuid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.BindGuidParameter( 6, &saveSettingsTimeseries );
        statement.BindGuidParameter( 7, &powerOnTimeseries );
        statement.BindGuidParameter( 8, &trackingOnTimeseries );
        statement.BindGuidParameter( 9, &radarPulseTimeseries );
        statement.BindGuidParameter( 10, &tuningTimeseries );
        statement.BindGuidParameter( 11, &blankSector1Timeseries );
        statement.BindGuidParameter( 12, &sector1StartTimeseries );
        statement.BindGuidParameter( 13, &sector1EndTimeseries );
        statement.BindGuidParameter( 14, &blankSector2Timeseries );
        statement.BindGuidParameter( 15, &sector2StartTimeseries );
        statement.BindGuidParameter( 16, &sector2EndTimeseries );
        statement.BindGuidParameter( 17, &enableAutomaticFrequencyControlTimeseries );
        statement.BindGuidParameter( 18, &azimuthOffsetTimeseries );
        statement.BindGuidParameter( 19, &enableSensitivityTimeControlTimeseries );
        statement.BindGuidParameter( 20, &automaticSensitivityTimeControlTimeseries );
        statement.BindGuidParameter( 21, &sensitivityTimeControlLevelTimeseries );
        statement.BindGuidParameter( 22, &enableFastTimeConstantTimeseries );
        statement.BindGuidParameter( 23, &fastTimeConstantLevelTimeseries );
        statement.BindGuidParameter( 24, &fastTimeConstantModeTimeseries );
        statement.BindGuidParameter( 25, &latitudeTimeseries );
        statement.BindGuidParameter( 26, &longitudeTimeseries );
        statement.BindGuidParameter( 27, radome );
        statement.BindGuidParameter( 28, gNSSDevice );
        statement.ExecDirect( L"{ CALL [RadarDeviceInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& saveSettingsTimeseries, const Guid& powerOnTimeseries, const Guid& trackingOnTimeseries, const Guid& radarPulseTimeseries, const Guid& tuningTimeseries, const Guid& blankSector1Timeseries, const Guid& sector1StartTimeseries, const Guid& sector1EndTimeseries, const Guid& blankSector2Timeseries, const Guid& sector2StartTimeseries, const Guid& sector2EndTimeseries, const Guid& enableAutomaticFrequencyControlTimeseries, const Guid& azimuthOffsetTimeseries, const Guid& enableSensitivityTimeControlTimeseries, const Guid& automaticSensitivityTimeControlTimeseries, const Guid& sensitivityTimeControlLevelTimeseries, const Guid& enableFastTimeConstantTimeseries, const Guid& fastTimeConstantLevelTimeseries, const Guid& fastTimeConstantModeTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const DBGuid& radome, const DBGuid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.BindGuidParameter( 7, &saveSettingsTimeseries );
        statement.BindGuidParameter( 8, &powerOnTimeseries );
        statement.BindGuidParameter( 9, &trackingOnTimeseries );
        statement.BindGuidParameter( 10, &radarPulseTimeseries );
        statement.BindGuidParameter( 11, &tuningTimeseries );
        statement.BindGuidParameter( 12, &blankSector1Timeseries );
        statement.BindGuidParameter( 13, &sector1StartTimeseries );
        statement.BindGuidParameter( 14, &sector1EndTimeseries );
        statement.BindGuidParameter( 15, &blankSector2Timeseries );
        statement.BindGuidParameter( 16, &sector2StartTimeseries );
        statement.BindGuidParameter( 17, &sector2EndTimeseries );
        statement.BindGuidParameter( 18, &enableAutomaticFrequencyControlTimeseries );
        statement.BindGuidParameter( 19, &azimuthOffsetTimeseries );
        statement.BindGuidParameter( 20, &enableSensitivityTimeControlTimeseries );
        statement.BindGuidParameter( 21, &automaticSensitivityTimeControlTimeseries );
        statement.BindGuidParameter( 22, &sensitivityTimeControlLevelTimeseries );
        statement.BindGuidParameter( 23, &enableFastTimeConstantTimeseries );
        statement.BindGuidParameter( 24, &fastTimeConstantLevelTimeseries );
        statement.BindGuidParameter( 25, &fastTimeConstantModeTimeseries );
        statement.BindGuidParameter( 26, &latitudeTimeseries );
        statement.BindGuidParameter( 27, &longitudeTimeseries );
        statement.BindGuidParameter( 28, radome );
        statement.BindGuidParameter( 29, gNSSDevice );
        statement.ExecDirect( L"{ CALL [RadarDeviceUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarDeviceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& barometricPressureTimeseries, const Guid& airTemperatureTimeseries, const Guid& waterTemperatureTimeseries, const Guid& relativeHumidityTimeseries, const Guid& absoluteHumidityTimeseries, const Guid& dewPointTimeseries, const Guid& windDirectionTimeseries, const Guid& windSpeedTimeseries, const Guid& gyro )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.BindGuidParameter( 6, &barometricPressureTimeseries );
        statement.BindGuidParameter( 7, &airTemperatureTimeseries );
        statement.BindGuidParameter( 8, &waterTemperatureTimeseries );
        statement.BindGuidParameter( 9, &relativeHumidityTimeseries );
        statement.BindGuidParameter( 10, &absoluteHumidityTimeseries );
        statement.BindGuidParameter( 11, &dewPointTimeseries );
        statement.BindGuidParameter( 12, &windDirectionTimeseries );
        statement.BindGuidParameter( 13, &windSpeedTimeseries );
        statement.BindGuidParameter( 14, &gyro );
        statement.ExecDirect( L"{ CALL [WeatherStationDeviceInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& barometricPressureTimeseries, const Guid& airTemperatureTimeseries, const Guid& waterTemperatureTimeseries, const Guid& relativeHumidityTimeseries, const Guid& absoluteHumidityTimeseries, const Guid& dewPointTimeseries, const Guid& windDirectionTimeseries, const Guid& windSpeedTimeseries, const Guid& gyro )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.BindGuidParameter( 7, &barometricPressureTimeseries );
        statement.BindGuidParameter( 8, &airTemperatureTimeseries );
        statement.BindGuidParameter( 9, &waterTemperatureTimeseries );
        statement.BindGuidParameter( 10, &relativeHumidityTimeseries );
        statement.BindGuidParameter( 11, &absoluteHumidityTimeseries );
        statement.BindGuidParameter( 12, &dewPointTimeseries );
        statement.BindGuidParameter( 13, &windDirectionTimeseries );
        statement.BindGuidParameter( 14, &windSpeedTimeseries );
        statement.BindGuidParameter( 15, &gyro );
        statement.ExecDirect( L"{ CALL [WeatherStationDeviceUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationDeviceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertFacility( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& type, double longitude, double latitude, double altitude )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &type );
        statement.BindDoubleParameter( 4, &longitude );
        statement.BindDoubleParameter( 5, &latitude );
        statement.BindDoubleParameter( 6, &altitude );
        statement.ExecDirect( L"{ CALL [FacilityInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateFacility( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& type, double longitude, double latitude, double altitude )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &type );
        statement.BindDoubleParameter( 5, &longitude );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindDoubleParameter( 7, &altitude );
        statement.ExecDirect( L"{ CALL [FacilityUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteFacility( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [FacilityDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAircraft( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &type );
        statement.ExecDirect( L"{ CALL [AircraftInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAircraft( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &type );
        statement.ExecDirect( L"{ CALL [AircraftUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAircraft( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AircraftDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisAidToNavigation( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& mMSI, Data::NavigationalAidType navigationalAidType, const Guid& position, bool isVirtual, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& offPositionTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &mMSI );
        statement.BindEnumParameter( 4, &navigationalAidType );
        statement.BindGuidParameter( 5, &position );
        statement.BindBooleanParameter( 6, &isVirtual );
        statement.BindInt32Parameter( 7, &toBow );
        statement.BindInt32Parameter( 8, &toStern );
        statement.BindInt32Parameter( 9, &toPort );
        statement.BindInt32Parameter( 10, &toStarboard );
        statement.BindGuidParameter( 11, &offPositionTimeseries );
        statement.ExecDirect( L"{ CALL [AisAidToNavigationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisAidToNavigation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& mMSI, Data::NavigationalAidType navigationalAidType, const Guid& position, bool isVirtual, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& offPositionTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &mMSI );
        statement.BindEnumParameter( 5, &navigationalAidType );
        statement.BindGuidParameter( 6, &position );
        statement.BindBooleanParameter( 7, &isVirtual );
        statement.BindInt32Parameter( 8, &toBow );
        statement.BindInt32Parameter( 9, &toStern );
        statement.BindInt32Parameter( 10, &toPort );
        statement.BindInt32Parameter( 11, &toStarboard );
        statement.BindGuidParameter( 12, &offPositionTimeseries );
        statement.ExecDirect( L"{ CALL [AisAidToNavigationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisAidToNavigation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisAidToNavigationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertVehicle( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &type );
        statement.ExecDirect( L"{ CALL [VehicleInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateVehicle( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &type );
        statement.ExecDirect( L"{ CALL [VehicleUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteVehicle( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [VehicleDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertVessel( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& type, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& draughtTimeseries, const Guid& personsOnBoardTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &type );
        statement.BindInt32Parameter( 4, &toBow );
        statement.BindInt32Parameter( 5, &toStern );
        statement.BindInt32Parameter( 6, &toPort );
        statement.BindInt32Parameter( 7, &toStarboard );
        statement.BindGuidParameter( 8, &draughtTimeseries );
        statement.BindGuidParameter( 9, &personsOnBoardTimeseries );
        statement.ExecDirect( L"{ CALL [VesselInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateVessel( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& type, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& draughtTimeseries, const Guid& personsOnBoardTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &type );
        statement.BindInt32Parameter( 5, &toBow );
        statement.BindInt32Parameter( 6, &toStern );
        statement.BindInt32Parameter( 7, &toPort );
        statement.BindInt32Parameter( 8, &toStarboard );
        statement.BindGuidParameter( 9, &draughtTimeseries );
        statement.BindGuidParameter( 10, &personsOnBoardTimeseries );
        statement.ExecDirect( L"{ CALL [VesselUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteVessel( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [VesselDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertItemIdentityLink( const ODBC::Connection& connection, Guid& id, const Guid& item, const Guid& identity, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &item );
        statement.BindGuidParameter( 3, &identity );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.ExecDirect( L"{ CALL [ItemIdentityLinkInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateItemIdentityLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, const Guid& identity, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &item );
        statement.BindGuidParameter( 4, &identity );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.ExecDirect( L"{ CALL [ItemIdentityLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteItemIdentityLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ItemIdentityLinkDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertItemParentChildLink( const ODBC::Connection& connection, Guid& id, const Guid& parent, const Guid& child, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &parent );
        statement.BindGuidParameter( 3, &child );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.ExecDirect( L"{ CALL [ItemParentChildLinkInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateItemParentChildLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& parent, const Guid& child, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &parent );
        statement.BindGuidParameter( 4, &child );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.ExecDirect( L"{ CALL [ItemParentChildLinkUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteItemParentChildLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ItemParentChildLinkDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLineInputDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &lineInputDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [LineInputDeviceCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLineInputDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &lineInputDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [LineInputDeviceCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLineInputDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LineInputDeviceCommandDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLineInputDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &lineInputDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.ExecDirect( L"{ CALL [LineInputDeviceCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLineInputDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &lineInputDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.ExecDirect( L"{ CALL [LineInputDeviceCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLineInputDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LineInputDeviceCommandReplyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLineInputDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages, bool nMEA, bool strictNMEA, Data::LineInputDeviceConnectionType connectionType, Int32 udpReceivePort, FixedDBWideString<100> udpSendHostname, Int32 udpSendPort, FixedDBWideString<100> tcpHostname, Int32 tcpPort, bool useHttpLogin, FixedDBWideString<100> loginHostname, Int32 loginPort, FixedDBWideString<100> userName, FixedDBWideString<100> password, FixedDBWideString<100> comPort, Int32 baudRate, Int32 dataBits, bool discardNull, bool dtrEnable, Data::Handshake handshake, FixedDBWideString<100> newLine, Data::Parity parity, Byte parityReplace, Int32 readBufferSize, const TimeSpan& readTimeout, Int32 receivedBytesThreshold, bool rtsEnable, Data::StopBits stopBits, Int32 writeBufferSize, const TimeSpan& writeTimeout, FixedDBWideString<100> pairedComPort )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &lineInputDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindBooleanParameter( 4, &storeReceivedSentences );
        statement.BindBooleanParameter( 5, &storeSentMessages );
        statement.BindBooleanParameter( 6, &storeUnsentMessages );
        statement.BindBooleanParameter( 7, &nMEA );
        statement.BindBooleanParameter( 8, &strictNMEA );
        statement.BindEnumParameter( 9, &connectionType );
        statement.BindInt32Parameter( 10, &udpReceivePort );
        statement.BindFixedDBWideStringParameter( 11, udpSendHostname );
        statement.BindInt32Parameter( 12, &udpSendPort );
        statement.BindFixedDBWideStringParameter( 13, tcpHostname );
        statement.BindInt32Parameter( 14, &tcpPort );
        statement.BindBooleanParameter( 15, &useHttpLogin );
        statement.BindFixedDBWideStringParameter( 16, loginHostname );
        statement.BindInt32Parameter( 17, &loginPort );
        statement.BindFixedDBWideStringParameter( 18, userName );
        statement.BindFixedDBWideStringParameter( 19, password );
        statement.BindFixedDBWideStringParameter( 20, comPort );
        statement.BindInt32Parameter( 21, &baudRate );
        statement.BindInt32Parameter( 22, &dataBits );
        statement.BindBooleanParameter( 23, &discardNull );
        statement.BindBooleanParameter( 24, &dtrEnable );
        statement.BindEnumParameter( 25, &handshake );
        statement.BindFixedDBWideStringParameter( 26, newLine );
        statement.BindEnumParameter( 27, &parity );
        statement.BindByteParameter( 28, &parityReplace );
        statement.BindInt32Parameter( 29, &readBufferSize );
        statement.BindTimeSpanParameter( 30, readTimeout );
        statement.BindInt32Parameter( 31, &receivedBytesThreshold );
        statement.BindBooleanParameter( 32, &rtsEnable );
        statement.BindEnumParameter( 33, &stopBits );
        statement.BindInt32Parameter( 34, &writeBufferSize );
        statement.BindTimeSpanParameter( 35, writeTimeout );
        statement.BindFixedDBWideStringParameter( 36, pairedComPort );
        statement.ExecDirect( L"{ CALL [LineInputDeviceConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLineInputDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages, bool nMEA, bool strictNMEA, Data::LineInputDeviceConnectionType connectionType, Int32 udpReceivePort, FixedDBWideString<100> udpSendHostname, Int32 udpSendPort, FixedDBWideString<100> tcpHostname, Int32 tcpPort, bool useHttpLogin, FixedDBWideString<100> loginHostname, Int32 loginPort, FixedDBWideString<100> userName, FixedDBWideString<100> password, FixedDBWideString<100> comPort, Int32 baudRate, Int32 dataBits, bool discardNull, bool dtrEnable, Data::Handshake handshake, FixedDBWideString<100> newLine, Data::Parity parity, Byte parityReplace, Int32 readBufferSize, const TimeSpan& readTimeout, Int32 receivedBytesThreshold, bool rtsEnable, Data::StopBits stopBits, Int32 writeBufferSize, const TimeSpan& writeTimeout, FixedDBWideString<100> pairedComPort )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &lineInputDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindBooleanParameter( 5, &storeReceivedSentences );
        statement.BindBooleanParameter( 6, &storeSentMessages );
        statement.BindBooleanParameter( 7, &storeUnsentMessages );
        statement.BindBooleanParameter( 8, &nMEA );
        statement.BindBooleanParameter( 9, &strictNMEA );
        statement.BindEnumParameter( 10, &connectionType );
        statement.BindInt32Parameter( 11, &udpReceivePort );
        statement.BindFixedDBWideStringParameter( 12, udpSendHostname );
        statement.BindInt32Parameter( 13, &udpSendPort );
        statement.BindFixedDBWideStringParameter( 14, tcpHostname );
        statement.BindInt32Parameter( 15, &tcpPort );
        statement.BindBooleanParameter( 16, &useHttpLogin );
        statement.BindFixedDBWideStringParameter( 17, loginHostname );
        statement.BindInt32Parameter( 18, &loginPort );
        statement.BindFixedDBWideStringParameter( 19, userName );
        statement.BindFixedDBWideStringParameter( 20, password );
        statement.BindFixedDBWideStringParameter( 21, comPort );
        statement.BindInt32Parameter( 22, &baudRate );
        statement.BindInt32Parameter( 23, &dataBits );
        statement.BindBooleanParameter( 24, &discardNull );
        statement.BindBooleanParameter( 25, &dtrEnable );
        statement.BindEnumParameter( 26, &handshake );
        statement.BindFixedDBWideStringParameter( 27, newLine );
        statement.BindEnumParameter( 28, &parity );
        statement.BindByteParameter( 29, &parityReplace );
        statement.BindInt32Parameter( 30, &readBufferSize );
        statement.BindTimeSpanParameter( 31, readTimeout );
        statement.BindInt32Parameter( 32, &receivedBytesThreshold );
        statement.BindBooleanParameter( 33, &rtsEnable );
        statement.BindEnumParameter( 34, &stopBits );
        statement.BindInt32Parameter( 35, &writeBufferSize );
        statement.BindTimeSpanParameter( 36, writeTimeout );
        statement.BindFixedDBWideStringParameter( 37, pairedComPort );
        statement.ExecDirect( L"{ CALL [LineInputDeviceConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLineInputDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LineInputDeviceConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLineInputMessageRouting( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, FixedDBWideString<100> type )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &lineInputDevice );
        statement.BindFixedDBWideStringParameter( 3, type );
        statement.ExecDirect( L"{ CALL [LineInputMessageRoutingInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLineInputMessageRouting( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, FixedDBWideString<100> type )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &lineInputDevice );
        statement.BindFixedDBWideStringParameter( 4, type );
        statement.ExecDirect( L"{ CALL [LineInputMessageRoutingUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLineInputMessageRouting( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LineInputMessageRoutingDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLineInputMessageRoutingDestination( const ODBC::Connection& connection, Guid& id, const Guid& routing, const Guid& listener )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &routing );
        statement.BindGuidParameter( 3, &listener );
        statement.ExecDirect( L"{ CALL [LineInputMessageRoutingDestinationInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLineInputMessageRoutingDestination( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& routing, const Guid& listener )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &routing );
        statement.BindGuidParameter( 4, &listener );
        statement.ExecDirect( L"{ CALL [LineInputMessageRoutingDestinationUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLineInputMessageRoutingDestination( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LineInputMessageRoutingDestinationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLineInputWhiteListEntry( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, FixedDBWideString<128> hostName, Int32 port )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &lineInputDevice );
        statement.BindFixedDBWideStringParameter( 3, hostName );
        statement.BindInt32Parameter( 4, &port );
        statement.ExecDirect( L"{ CALL [LineInputWhiteListEntryInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLineInputWhiteListEntry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, FixedDBWideString<128> hostName, Int32 port )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &lineInputDevice );
        statement.BindFixedDBWideStringParameter( 4, hostName );
        statement.BindInt32Parameter( 5, &port );
        statement.ExecDirect( L"{ CALL [LineInputWhiteListEntryUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLineInputWhiteListEntry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LineInputWhiteListEntryDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLogApplication( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindWideStringParameter( 3, description );
        statement.ExecDirect( L"{ CALL [LogApplicationInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLogApplication( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.ExecDirect( L"{ CALL [LogApplicationUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLogApplication( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LogApplicationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLogApplicationConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& application, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &application );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindBooleanParameter( 4, &finest );
        statement.BindBooleanParameter( 5, &finer );
        statement.BindBooleanParameter( 6, &fine );
        statement.BindBooleanParameter( 7, &info );
        statement.BindBooleanParameter( 8, &notice );
        statement.BindBooleanParameter( 9, &warn );
        statement.BindBooleanParameter( 10, &error );
        statement.BindBooleanParameter( 11, &severe );
        statement.BindBooleanParameter( 12, &critical );
        statement.BindBooleanParameter( 13, &alert );
        statement.BindBooleanParameter( 14, &fatal );
        statement.BindBooleanParameter( 15, &emergency );
        statement.ExecDirect( L"{ CALL [LogApplicationConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLogApplicationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& application, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &application );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindBooleanParameter( 5, &finest );
        statement.BindBooleanParameter( 6, &finer );
        statement.BindBooleanParameter( 7, &fine );
        statement.BindBooleanParameter( 8, &info );
        statement.BindBooleanParameter( 9, &notice );
        statement.BindBooleanParameter( 10, &warn );
        statement.BindBooleanParameter( 11, &error );
        statement.BindBooleanParameter( 12, &severe );
        statement.BindBooleanParameter( 13, &critical );
        statement.BindBooleanParameter( 14, &alert );
        statement.BindBooleanParameter( 15, &fatal );
        statement.BindBooleanParameter( 16, &emergency );
        statement.ExecDirect( L"{ CALL [LogApplicationConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLogApplicationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LogApplicationConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLogHost( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> computerName, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, computerName );
        statement.BindWideStringParameter( 3, description );
        statement.ExecDirect( L"{ CALL [LogHostInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLogHost( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> computerName, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, computerName );
        statement.BindWideStringParameter( 4, description );
        statement.ExecDirect( L"{ CALL [LogHostUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLogHost( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LogHostDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLogHostConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& host, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindBooleanParameter( 4, &finest );
        statement.BindBooleanParameter( 5, &finer );
        statement.BindBooleanParameter( 6, &fine );
        statement.BindBooleanParameter( 7, &info );
        statement.BindBooleanParameter( 8, &notice );
        statement.BindBooleanParameter( 9, &warn );
        statement.BindBooleanParameter( 10, &error );
        statement.BindBooleanParameter( 11, &severe );
        statement.BindBooleanParameter( 12, &critical );
        statement.BindBooleanParameter( 13, &alert );
        statement.BindBooleanParameter( 14, &fatal );
        statement.BindBooleanParameter( 15, &emergency );
        statement.ExecDirect( L"{ CALL [LogHostConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLogHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &host );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindBooleanParameter( 5, &finest );
        statement.BindBooleanParameter( 6, &finer );
        statement.BindBooleanParameter( 7, &fine );
        statement.BindBooleanParameter( 8, &info );
        statement.BindBooleanParameter( 9, &notice );
        statement.BindBooleanParameter( 10, &warn );
        statement.BindBooleanParameter( 11, &error );
        statement.BindBooleanParameter( 12, &severe );
        statement.BindBooleanParameter( 13, &critical );
        statement.BindBooleanParameter( 14, &alert );
        statement.BindBooleanParameter( 15, &fatal );
        statement.BindBooleanParameter( 16, &emergency );
        statement.ExecDirect( L"{ CALL [LogHostConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLogHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LogHostConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLogLocation( const ODBC::Connection& connection, Guid& id, FixedDBWideString<260> fileName, Int32 lineNumber, const WideString& namespace__, const WideString& className, FixedDBWideString<255> methodName )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, fileName );
        statement.BindInt32Parameter( 3, &lineNumber );
        statement.BindWideStringParameter( 4, namespace__ );
        statement.BindWideStringParameter( 5, className );
        statement.BindFixedDBWideStringParameter( 6, methodName );
        statement.ExecDirect( L"{ CALL [LogLocationInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLogLocation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<260> fileName, Int32 lineNumber, const WideString& namespace__, const WideString& className, FixedDBWideString<255> methodName )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, fileName );
        statement.BindInt32Parameter( 4, &lineNumber );
        statement.BindWideStringParameter( 5, namespace__ );
        statement.BindWideStringParameter( 6, className );
        statement.BindFixedDBWideStringParameter( 7, methodName );
        statement.ExecDirect( L"{ CALL [LogLocationUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLogLocation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LogLocationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLogProcess( const ODBC::Connection& connection, Guid& id, const Guid& application, const Guid& host, const DateTime& started, const DBDateTime& stopped, Int64 processId, const WideString& path, FixedDBWideString<127> identity )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &application );
        statement.BindGuidParameter( 3, &host );
        statement.BindDateTimeParameter( 4, started );
        statement.BindDateTimeParameter( 5, stopped );
        statement.BindInt64Parameter( 6, &processId );
        statement.BindWideStringParameter( 7, path );
        statement.BindFixedDBWideStringParameter( 8, identity );
        statement.ExecDirect( L"{ CALL [LogProcessInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLogProcess( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& application, const Guid& host, const DateTime& started, const DBDateTime& stopped, Int64 processId, const WideString& path, FixedDBWideString<127> identity )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &application );
        statement.BindGuidParameter( 4, &host );
        statement.BindDateTimeParameter( 5, started );
        statement.BindDateTimeParameter( 6, stopped );
        statement.BindInt64Parameter( 7, &processId );
        statement.BindWideStringParameter( 8, path );
        statement.BindFixedDBWideStringParameter( 9, identity );
        statement.ExecDirect( L"{ CALL [LogProcessUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLogProcess( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LogProcessDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLogRecord( const ODBC::Connection& connection, Guid& id, const Guid& thread, Int64 sequenceNumber, Data::LogLevel level, const DateTime& timestamp, Int32 depth, const Guid& location, const WideString& message, const WideString& exceptionString, const Binary& propertiesData )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &thread );
        statement.BindInt64Parameter( 3, &sequenceNumber );
        statement.BindEnumParameter( 4, &level );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.BindInt32Parameter( 6, &depth );
        statement.BindGuidParameter( 7, &location );
        statement.BindWideStringParameter( 8, message );
        statement.BindWideStringParameter( 9, exceptionString );
        statement.BindBinaryParameter( 10, propertiesData );
        statement.ExecDirect( L"{ CALL [LogRecordInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLogRecord( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& thread, Int64 sequenceNumber, Data::LogLevel level, const DateTime& timestamp, Int32 depth, const Guid& location, const WideString& message, const WideString& exceptionString, const Binary& propertiesData )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &thread );
        statement.BindInt64Parameter( 4, &sequenceNumber );
        statement.BindEnumParameter( 5, &level );
        statement.BindDateTimeParameter( 6, timestamp );
        statement.BindInt32Parameter( 7, &depth );
        statement.BindGuidParameter( 8, &location );
        statement.BindWideStringParameter( 9, message );
        statement.BindWideStringParameter( 10, exceptionString );
        statement.BindBinaryParameter( 11, propertiesData );
        statement.ExecDirect( L"{ CALL [LogRecordUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLogRecord( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LogRecordDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLogThread( const ODBC::Connection& connection, Guid& id, const Guid& process, const DateTime& started, const DBDateTime& stopped, Int64 threadId, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &process );
        statement.BindDateTimeParameter( 3, started );
        statement.BindDateTimeParameter( 4, stopped );
        statement.BindInt64Parameter( 5, &threadId );
        statement.BindFixedDBWideStringParameter( 6, name );
        statement.ExecDirect( L"{ CALL [LogThreadInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLogThread( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& process, const DateTime& started, const DBDateTime& stopped, Int64 threadId, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &process );
        statement.BindDateTimeParameter( 4, started );
        statement.BindDateTimeParameter( 5, stopped );
        statement.BindInt64Parameter( 6, &threadId );
        statement.BindFixedDBWideStringParameter( 7, name );
        statement.ExecDirect( L"{ CALL [LogThreadUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLogThread( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LogThreadDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertLogTraceEntry( const ODBC::Connection& connection, Guid& id, const Guid& thread, Int64 sequenceNumber, const Guid& location, Int32 depth, const DateTime& entered, const DBDateTime& ended )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &thread );
        statement.BindInt64Parameter( 3, &sequenceNumber );
        statement.BindGuidParameter( 4, &location );
        statement.BindInt32Parameter( 5, &depth );
        statement.BindDateTimeParameter( 6, entered );
        statement.BindDateTimeParameter( 7, ended );
        statement.ExecDirect( L"{ CALL [LogTraceEntryInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateLogTraceEntry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& thread, Int64 sequenceNumber, const Guid& location, Int32 depth, const DateTime& entered, const DBDateTime& ended )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &thread );
        statement.BindInt64Parameter( 4, &sequenceNumber );
        statement.BindGuidParameter( 5, &location );
        statement.BindInt32Parameter( 6, &depth );
        statement.BindDateTimeParameter( 7, entered );
        statement.BindDateTimeParameter( 8, ended );
        statement.ExecDirect( L"{ CALL [LogTraceEntryUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteLogTraceEntry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [LogTraceEntryDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMapElement( const ODBC::Connection& connection, Guid& id, const Guid& item, Data::MapElementType elementType, double latitude, double longitude, double angle, double left, double top, double width, double height, FixedDBWideString<100> label, const Binary& data )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &item );
        statement.BindEnumParameter( 3, &elementType );
        statement.BindDoubleParameter( 4, &latitude );
        statement.BindDoubleParameter( 5, &longitude );
        statement.BindDoubleParameter( 6, &angle );
        statement.BindDoubleParameter( 7, &left );
        statement.BindDoubleParameter( 8, &top );
        statement.BindDoubleParameter( 9, &width );
        statement.BindDoubleParameter( 10, &height );
        statement.BindFixedDBWideStringParameter( 11, label );
        statement.BindBinaryParameter( 12, data );
        statement.ExecDirect( L"{ CALL [MapElementInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMapElement( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, Data::MapElementType elementType, double latitude, double longitude, double angle, double left, double top, double width, double height, FixedDBWideString<100> label, const Binary& data )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &item );
        statement.BindEnumParameter( 4, &elementType );
        statement.BindDoubleParameter( 5, &latitude );
        statement.BindDoubleParameter( 6, &longitude );
        statement.BindDoubleParameter( 7, &angle );
        statement.BindDoubleParameter( 8, &left );
        statement.BindDoubleParameter( 9, &top );
        statement.BindDoubleParameter( 10, &width );
        statement.BindDoubleParameter( 11, &height );
        statement.BindFixedDBWideStringParameter( 12, label );
        statement.BindBinaryParameter( 13, data );
        statement.ExecDirect( L"{ CALL [MapElementUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMapElement( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MapElementDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMapInfo( const ODBC::Connection& connection, Guid& id, Int32 scale, double latitude, double longitude, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, const Binary& image )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt32Parameter( 2, &scale );
        statement.BindDoubleParameter( 3, &latitude );
        statement.BindDoubleParameter( 4, &longitude );
        statement.BindDoubleParameter( 5, &northWestLatitude );
        statement.BindDoubleParameter( 6, &northWestLongitude );
        statement.BindDoubleParameter( 7, &southEastLatitude );
        statement.BindDoubleParameter( 8, &southEastLongitude );
        statement.BindBinaryParameter( 9, image );
        statement.ExecDirect( L"{ CALL [MapInfoInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMapInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 scale, double latitude, double longitude, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, const Binary& image )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindInt32Parameter( 3, &scale );
        statement.BindDoubleParameter( 4, &latitude );
        statement.BindDoubleParameter( 5, &longitude );
        statement.BindDoubleParameter( 6, &northWestLatitude );
        statement.BindDoubleParameter( 7, &northWestLongitude );
        statement.BindDoubleParameter( 8, &southEastLatitude );
        statement.BindDoubleParameter( 9, &southEastLongitude );
        statement.BindBinaryParameter( 10, image );
        statement.ExecDirect( L"{ CALL [MapInfoUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMapInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MapInfoDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMapServiceOptions( const ODBC::Connection& connection, Guid& id, const DateTime& timestamp, FixedDBWideString<127> ipAddress, Int32 port, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindDateTimeParameter( 2, timestamp );
        statement.BindFixedDBWideStringParameter( 3, ipAddress );
        statement.BindInt32Parameter( 4, &port );
        statement.BindDoubleParameter( 5, &imageScaleFactorX );
        statement.BindDoubleParameter( 6, &imageOffsetX );
        statement.BindDoubleParameter( 7, &imageScaleFactorY );
        statement.BindDoubleParameter( 8, &imageOffsetY );
        statement.ExecDirect( L"{ CALL [MapServiceOptionsInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMapServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DateTime& timestamp, FixedDBWideString<127> ipAddress, Int32 port, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindFixedDBWideStringParameter( 4, ipAddress );
        statement.BindInt32Parameter( 5, &port );
        statement.BindDoubleParameter( 6, &imageScaleFactorX );
        statement.BindDoubleParameter( 7, &imageOffsetX );
        statement.BindDoubleParameter( 8, &imageScaleFactorY );
        statement.BindDoubleParameter( 9, &imageOffsetY );
        statement.ExecDirect( L"{ CALL [MapServiceOptionsUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMapServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MapServiceOptionsDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMaritimeIdentificationDigits( const ODBC::Connection& connection, Guid& id, Int32 code, const Guid& country )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt32Parameter( 2, &code );
        statement.BindGuidParameter( 3, &country );
        statement.ExecDirect( L"{ CALL [MaritimeIdentificationDigitsInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMaritimeIdentificationDigits( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 code, const Guid& country )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindInt32Parameter( 3, &code );
        statement.BindGuidParameter( 4, &country );
        statement.ExecDirect( L"{ CALL [MaritimeIdentificationDigitsUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMaritimeIdentificationDigits( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MaritimeIdentificationDigitsDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMediaProxySession( const ODBC::Connection& connection, Guid& id, const Guid& service, FixedDBWideString<128> name, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &service );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [MediaProxySessionInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMediaProxySession( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& service, FixedDBWideString<128> name, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &service );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [MediaProxySessionUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMediaProxySession( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MediaProxySessionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMediaProxySessionFile( const ODBC::Connection& connection, Guid& id, const Guid& proxySession, const DateTime& timestamp, FixedDBWideString<100> streamName )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &proxySession );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindFixedDBWideStringParameter( 4, streamName );
        statement.ExecDirect( L"{ CALL [MediaProxySessionFileInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMediaProxySessionFile( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& proxySession, const DateTime& timestamp, FixedDBWideString<100> streamName )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &proxySession );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindFixedDBWideStringParameter( 5, streamName );
        statement.ExecDirect( L"{ CALL [MediaProxySessionFileUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMediaProxySessionFile( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MediaProxySessionFileDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMediaProxySessionOptions( const ODBC::Connection& connection, Guid& id, const Guid& proxySession, const DateTime& timestamp, FixedDBWideString<255> sourceStreamUrl, FixedDBWideString<255> streamName, Data::MediaProxySessionMode mode, Int32 tunnelOverHTTPPortNumber, FixedDBWideString<128> username, FixedDBWideString<128> password, Int32 recorderPortNumber, Data::MediaProxySessionType sessionType, const TimeSpan& maxFileTime, const TimeSpan& maxFileRetention, FixedDBWideString<260> videoDirectory )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &proxySession );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindFixedDBWideStringParameter( 4, sourceStreamUrl );
        statement.BindFixedDBWideStringParameter( 5, streamName );
        statement.BindEnumParameter( 6, &mode );
        statement.BindInt32Parameter( 7, &tunnelOverHTTPPortNumber );
        statement.BindFixedDBWideStringParameter( 8, username );
        statement.BindFixedDBWideStringParameter( 9, password );
        statement.BindInt32Parameter( 10, &recorderPortNumber );
        statement.BindEnumParameter( 11, &sessionType );
        statement.BindTimeSpanParameter( 12, maxFileTime );
        statement.BindTimeSpanParameter( 13, maxFileRetention );
        statement.BindFixedDBWideStringParameter( 14, videoDirectory );
        statement.ExecDirect( L"{ CALL [MediaProxySessionOptionsInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMediaProxySessionOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& proxySession, const DateTime& timestamp, FixedDBWideString<255> sourceStreamUrl, FixedDBWideString<255> streamName, Data::MediaProxySessionMode mode, Int32 tunnelOverHTTPPortNumber, FixedDBWideString<128> username, FixedDBWideString<128> password, Int32 recorderPortNumber, Data::MediaProxySessionType sessionType, const TimeSpan& maxFileTime, const TimeSpan& maxFileRetention, FixedDBWideString<260> videoDirectory )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &proxySession );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindFixedDBWideStringParameter( 5, sourceStreamUrl );
        statement.BindFixedDBWideStringParameter( 6, streamName );
        statement.BindEnumParameter( 7, &mode );
        statement.BindInt32Parameter( 8, &tunnelOverHTTPPortNumber );
        statement.BindFixedDBWideStringParameter( 9, username );
        statement.BindFixedDBWideStringParameter( 10, password );
        statement.BindInt32Parameter( 11, &recorderPortNumber );
        statement.BindEnumParameter( 12, &sessionType );
        statement.BindTimeSpanParameter( 13, maxFileTime );
        statement.BindTimeSpanParameter( 14, maxFileRetention );
        statement.BindFixedDBWideStringParameter( 15, videoDirectory );
        statement.ExecDirect( L"{ CALL [MediaProxySessionOptionsUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMediaProxySessionOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MediaProxySessionOptionsDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMediaService( const ODBC::Connection& connection, Guid& id, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [MediaServiceInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMediaService( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &enabledTimeseries );
        statement.ExecDirect( L"{ CALL [MediaServiceUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMediaService( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MediaServiceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMediaServiceOptions( const ODBC::Connection& connection, Guid& id, const Guid& mediaService, const DateTime& timestamp, Int32 rtspPortNumber, Int32 httpPortNumber )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &mediaService );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, &rtspPortNumber );
        statement.BindInt32Parameter( 5, &httpPortNumber );
        statement.ExecDirect( L"{ CALL [MediaServiceOptionsInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMediaServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& mediaService, const DateTime& timestamp, Int32 rtspPortNumber, Int32 httpPortNumber )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &mediaService );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, &rtspPortNumber );
        statement.BindInt32Parameter( 6, &httpPortNumber );
        statement.ExecDirect( L"{ CALL [MediaServiceOptionsUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMediaServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MediaServiceOptionsDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertElementType( const ODBC::Connection& connection, Guid& id, const Guid& namespace__, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &namespace__ );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.ExecDirect( L"{ CALL [ElementTypeInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateElementType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& namespace__, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &namespace__ );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.ExecDirect( L"{ CALL [ElementTypeUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteElementType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ElementTypeDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertNamespace( const ODBC::Connection& connection, Guid& id, const Guid& namespace__, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &namespace__ );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.ExecDirect( L"{ CALL [NamespaceInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateNamespace( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& namespace__, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &namespace__ );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.ExecDirect( L"{ CALL [NamespaceUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteNamespace( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [NamespaceDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertOilSpill( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, double oilArea, const Binary& shape, const Binary& bSI, const Binary& oil, const Binary& trace )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &oilSpillDetector );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, &oilArea );
        statement.BindBinaryParameter( 5, shape );
        statement.BindBinaryParameter( 6, bSI );
        statement.BindBinaryParameter( 7, oil );
        statement.BindBinaryParameter( 8, trace );
        statement.ExecDirect( L"{ CALL [OilSpillInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateOilSpill( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, double oilArea, const Binary& shape, const Binary& bSI, const Binary& oil, const Binary& trace )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &oilSpillDetector );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &oilArea );
        statement.BindBinaryParameter( 6, shape );
        statement.BindBinaryParameter( 7, bSI );
        statement.BindBinaryParameter( 8, oil );
        statement.BindBinaryParameter( 9, trace );
        statement.ExecDirect( L"{ CALL [OilSpillUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteOilSpill( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [OilSpillDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertOilSpillDetectorCommand( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &oilSpillDetector );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateOilSpillDetectorCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &oilSpillDetector );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteOilSpillDetectorCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorCommandDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertOilSpillDetectorCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &oilSpillDetector );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateOilSpillDetectorCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &oilSpillDetector );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteOilSpillDetectorCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorCommandReplyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertOilSpillDetectorConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, double range, double startAngle, double endAngle, double startRange, double endRange, Int32 updateRate, const TimeSpan& statusSendTime, bool drawBorder, const Binary& colors, bool sendToServer, FixedDBWideString<100> directory, bool transparentWater, bool savePictures, bool sendAsTarget, bool writeLog, FixedDBWideString<100> targetFilePrefix, const Guid& targetMMSI, double latitude, double longitude, bool testSourceEnabled, FixedDBWideString<100> proxyServer, bool useProxyServer )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &oilSpillDetector );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, &range );
        statement.BindDoubleParameter( 5, &startAngle );
        statement.BindDoubleParameter( 6, &endAngle );
        statement.BindDoubleParameter( 7, &startRange );
        statement.BindDoubleParameter( 8, &endRange );
        statement.BindInt32Parameter( 9, &updateRate );
        statement.BindTimeSpanParameter( 10, statusSendTime );
        statement.BindBooleanParameter( 11, &drawBorder );
        statement.BindBinaryParameter( 12, colors );
        statement.BindBooleanParameter( 13, &sendToServer );
        statement.BindFixedDBWideStringParameter( 14, directory );
        statement.BindBooleanParameter( 15, &transparentWater );
        statement.BindBooleanParameter( 16, &savePictures );
        statement.BindBooleanParameter( 17, &sendAsTarget );
        statement.BindBooleanParameter( 18, &writeLog );
        statement.BindFixedDBWideStringParameter( 19, targetFilePrefix );
        statement.BindGuidParameter( 20, &targetMMSI );
        statement.BindDoubleParameter( 21, &latitude );
        statement.BindDoubleParameter( 22, &longitude );
        statement.BindBooleanParameter( 23, &testSourceEnabled );
        statement.BindFixedDBWideStringParameter( 24, proxyServer );
        statement.BindBooleanParameter( 25, &useProxyServer );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateOilSpillDetectorConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, double range, double startAngle, double endAngle, double startRange, double endRange, Int32 updateRate, const TimeSpan& statusSendTime, bool drawBorder, const Binary& colors, bool sendToServer, FixedDBWideString<100> directory, bool transparentWater, bool savePictures, bool sendAsTarget, bool writeLog, FixedDBWideString<100> targetFilePrefix, const Guid& targetMMSI, double latitude, double longitude, bool testSourceEnabled, FixedDBWideString<100> proxyServer, bool useProxyServer )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &oilSpillDetector );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &range );
        statement.BindDoubleParameter( 6, &startAngle );
        statement.BindDoubleParameter( 7, &endAngle );
        statement.BindDoubleParameter( 8, &startRange );
        statement.BindDoubleParameter( 9, &endRange );
        statement.BindInt32Parameter( 10, &updateRate );
        statement.BindTimeSpanParameter( 11, statusSendTime );
        statement.BindBooleanParameter( 12, &drawBorder );
        statement.BindBinaryParameter( 13, colors );
        statement.BindBooleanParameter( 14, &sendToServer );
        statement.BindFixedDBWideStringParameter( 15, directory );
        statement.BindBooleanParameter( 16, &transparentWater );
        statement.BindBooleanParameter( 17, &savePictures );
        statement.BindBooleanParameter( 18, &sendAsTarget );
        statement.BindBooleanParameter( 19, &writeLog );
        statement.BindFixedDBWideStringParameter( 20, targetFilePrefix );
        statement.BindGuidParameter( 21, &targetMMSI );
        statement.BindDoubleParameter( 22, &latitude );
        statement.BindDoubleParameter( 23, &longitude );
        statement.BindBooleanParameter( 24, &testSourceEnabled );
        statement.BindFixedDBWideStringParameter( 25, proxyServer );
        statement.BindBooleanParameter( 26, &useProxyServer );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteOilSpillDetectorConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [OilSpillDetectorConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertPosition2DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, x );
        statement.BindDoubleParameter( 5, y );
        statement.ExecDirect( L"{ CALL [Position2DTimeseriesValueInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdatePosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, x );
        statement.BindDoubleParameter( 6, y );
        statement.ExecDirect( L"{ CALL [Position2DTimeseriesValueUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeletePosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Position2DTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertPosition3DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y, const DBDouble& z )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, x );
        statement.BindDoubleParameter( 5, y );
        statement.BindDoubleParameter( 6, z );
        statement.ExecDirect( L"{ CALL [Position3DTimeseriesValueInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdatePosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y, const DBDouble& z )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, x );
        statement.BindDoubleParameter( 6, y );
        statement.BindDoubleParameter( 7, z );
        statement.ExecDirect( L"{ CALL [Position3DTimeseriesValueUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeletePosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Position3DTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertProcessTrackValueResult( const ODBC::Connection& connection, Guid& id, bool createdNewTrack, const Guid& trackId )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindBooleanParameter( 2, &createdNewTrack );
        statement.BindGuidParameter( 3, &trackId );
        statement.ExecDirect( L"{ CALL [ProcessTrackValueResultInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateProcessTrackValueResult( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, bool createdNewTrack, const Guid& trackId )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindBooleanParameter( 3, &createdNewTrack );
        statement.BindGuidParameter( 4, &trackId );
        statement.ExecDirect( L"{ CALL [ProcessTrackValueResultUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteProcessTrackValueResult( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ProcessTrackValueResultDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBinaryProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Binary& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindBinaryParameter( 4, value );
        statement.ExecDirect( L"{ CALL [BinaryPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBinaryProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Binary& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindBinaryParameter( 5, value );
        statement.ExecDirect( L"{ CALL [BinaryPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBinaryProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BinaryPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBooleanProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, bool value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindBooleanParameter( 4, &value );
        statement.ExecDirect( L"{ CALL [BooleanPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBooleanProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, bool value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindBooleanParameter( 5, &value );
        statement.ExecDirect( L"{ CALL [BooleanPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBooleanProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BooleanPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertByteProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Byte value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindByteParameter( 4, &value );
        statement.ExecDirect( L"{ CALL [BytePropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateByteProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Byte value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindByteParameter( 5, &value );
        statement.ExecDirect( L"{ CALL [BytePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteByteProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BytePropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDateTimeProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DateTime& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindDateTimeParameter( 4, value );
        statement.ExecDirect( L"{ CALL [DateTimePropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDateTimeProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DateTime& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindDateTimeParameter( 5, value );
        statement.ExecDirect( L"{ CALL [DateTimePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDateTimeProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DateTimePropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDoubleProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, double value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindDoubleParameter( 4, &value );
        statement.ExecDirect( L"{ CALL [DoublePropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDoubleProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, double value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindDoubleParameter( 5, &value );
        statement.ExecDirect( L"{ CALL [DoublePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDoubleProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DoublePropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGuidProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &value );
        statement.ExecDirect( L"{ CALL [GuidPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGuidProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &value );
        statement.ExecDirect( L"{ CALL [GuidPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGuidProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GuidPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt16Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int16 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindInt16Parameter( 4, &value );
        statement.ExecDirect( L"{ CALL [Int16PropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt16Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int16 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindInt16Parameter( 5, &value );
        statement.ExecDirect( L"{ CALL [Int16PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt16Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int16PropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt32Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int32 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindInt32Parameter( 4, &value );
        statement.ExecDirect( L"{ CALL [Int32PropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt32Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int32 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindInt32Parameter( 5, &value );
        statement.ExecDirect( L"{ CALL [Int32PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt32Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int32PropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt64Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int64 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindInt64Parameter( 4, &value );
        statement.ExecDirect( L"{ CALL [Int64PropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt64Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int64 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindInt64Parameter( 5, &value );
        statement.ExecDirect( L"{ CALL [Int64PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt64Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int64PropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertReferenceProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &value );
        statement.ExecDirect( L"{ CALL [ReferencePropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateReferenceProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &value );
        statement.ExecDirect( L"{ CALL [ReferencePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteReferenceProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ReferencePropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSByteProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, SByte value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindSByteParameter( 4, &value );
        statement.ExecDirect( L"{ CALL [SBytePropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSByteProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, SByte value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindSByteParameter( 5, &value );
        statement.ExecDirect( L"{ CALL [SBytePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSByteProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SBytePropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSingleProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, float value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindSingleParameter( 4, &value );
        statement.ExecDirect( L"{ CALL [SinglePropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSingleProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, float value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindSingleParameter( 5, &value );
        statement.ExecDirect( L"{ CALL [SinglePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSingleProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SinglePropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertStringProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, FixedDBWideString<100> value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindFixedDBWideStringParameter( 4, value );
        statement.ExecDirect( L"{ CALL [StringPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateStringProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, FixedDBWideString<100> value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindFixedDBWideStringParameter( 5, value );
        statement.ExecDirect( L"{ CALL [StringPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteStringProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [StringPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBinaryTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBinaryTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBinaryTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBooleanTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBooleanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBooleanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertByteTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDateTimeTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDateTimeTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDateTimeTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDoubleTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDoubleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDoubleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGuidTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGuidTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGuidTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt16TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt32TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt64TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertReferenceTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateReferenceTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteReferenceTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSByteTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSingleTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSingleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSingleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertStringTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [StringTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateStringTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [StringTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteStringTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [StringTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTimeSpanTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTimeSpanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTimeSpanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt16TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt32TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt64TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTimeSpanProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const TimeSpan& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindTimeSpanParameter( 4, value );
        statement.ExecDirect( L"{ CALL [TimeSpanPropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTimeSpanProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const TimeSpan& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindTimeSpanParameter( 5, value );
        statement.ExecDirect( L"{ CALL [TimeSpanPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTimeSpanProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TimeSpanPropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt16Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, UInt16 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindUInt16Parameter( 4, &value );
        statement.ExecDirect( L"{ CALL [UInt16PropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt16Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, UInt16 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindUInt16Parameter( 5, &value );
        statement.ExecDirect( L"{ CALL [UInt16PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt16Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt16PropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt32Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, UInt32 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindUInt32Parameter( 4, &value );
        statement.ExecDirect( L"{ CALL [UInt32PropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt32Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, UInt32 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindUInt32Parameter( 5, &value );
        statement.ExecDirect( L"{ CALL [UInt32PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt32Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt32PropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt64Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int64 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindInt64Parameter( 4, &value );
        statement.ExecDirect( L"{ CALL [UInt64PropertyInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt64Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int64 value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindInt64Parameter( 5, &value );
        statement.ExecDirect( L"{ CALL [UInt64PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt64Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt64PropertyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBinaryPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Binary& defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindBinaryParameter( 5, defaultValue );
        statement.ExecDirect( L"{ CALL [BinaryPropertyDefinitionInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBinaryPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Binary& defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindBinaryParameter( 6, defaultValue );
        statement.ExecDirect( L"{ CALL [BinaryPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBinaryPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BinaryPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBooleanPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, bool defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindBooleanParameter( 5, &defaultValue );
        statement.ExecDirect( L"{ CALL [BooleanPropertyDefinitionInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBooleanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, bool defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindBooleanParameter( 6, &defaultValue );
        statement.ExecDirect( L"{ CALL [BooleanPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBooleanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BooleanPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBytePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Byte defaultValue, Byte minValue, Byte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindByteParameter( 5, &defaultValue );
        statement.BindByteParameter( 6, &minValue );
        statement.BindByteParameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [BytePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Byte defaultValue, Byte minValue, Byte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindByteParameter( 6, &defaultValue );
        statement.BindByteParameter( 7, &minValue );
        statement.BindByteParameter( 8, &maxValue );
        statement.ExecDirect( L"{ CALL [BytePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BytePropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDateTimePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> defaultValue, FixedDBWideString<100> minValue, FixedDBWideString<100> maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindFixedDBWideStringParameter( 5, defaultValue );
        statement.BindFixedDBWideStringParameter( 6, minValue );
        statement.BindFixedDBWideStringParameter( 7, maxValue );
        statement.ExecDirect( L"{ CALL [DateTimePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDateTimePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> defaultValue, FixedDBWideString<100> minValue, FixedDBWideString<100> maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindFixedDBWideStringParameter( 6, defaultValue );
        statement.BindFixedDBWideStringParameter( 7, minValue );
        statement.BindFixedDBWideStringParameter( 8, maxValue );
        statement.ExecDirect( L"{ CALL [DateTimePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDateTimePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DateTimePropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDoublePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, double defaultValue, double minValue, double maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindDoubleParameter( 5, &defaultValue );
        statement.BindDoubleParameter( 6, &minValue );
        statement.BindDoubleParameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [DoublePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDoublePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, double defaultValue, double minValue, double maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindDoubleParameter( 6, &defaultValue );
        statement.BindDoubleParameter( 7, &minValue );
        statement.BindDoubleParameter( 8, &maxValue );
        statement.ExecDirect( L"{ CALL [DoublePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDoublePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DoublePropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGuidPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &defaultValue );
        statement.ExecDirect( L"{ CALL [GuidPropertyDefinitionInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGuidPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &defaultValue );
        statement.ExecDirect( L"{ CALL [GuidPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGuidPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GuidPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt16PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int16 defaultValue, Int16 minValue, Int16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt16Parameter( 5, &defaultValue );
        statement.BindInt16Parameter( 6, &minValue );
        statement.BindInt16Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [Int16PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int16 defaultValue, Int16 minValue, Int16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt16Parameter( 6, &defaultValue );
        statement.BindInt16Parameter( 7, &minValue );
        statement.BindInt16Parameter( 8, &maxValue );
        statement.ExecDirect( L"{ CALL [Int16PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int16PropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt32PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int32 defaultValue, Int32 minValue, Int32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt32Parameter( 5, &defaultValue );
        statement.BindInt32Parameter( 6, &minValue );
        statement.BindInt32Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [Int32PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int32 defaultValue, Int32 minValue, Int32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt32Parameter( 6, &defaultValue );
        statement.BindInt32Parameter( 7, &minValue );
        statement.BindInt32Parameter( 8, &maxValue );
        statement.ExecDirect( L"{ CALL [Int32PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int32PropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt64PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt64Parameter( 5, &defaultValue );
        statement.BindInt64Parameter( 6, &minValue );
        statement.BindInt64Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [Int64PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt64Parameter( 6, &defaultValue );
        statement.BindInt64Parameter( 7, &minValue );
        statement.BindInt64Parameter( 8, &maxValue );
        statement.ExecDirect( L"{ CALL [Int64PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int64PropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertReferencePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& defaultValue, const Guid& referencedElementType )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &defaultValue );
        statement.BindGuidParameter( 6, &referencedElementType );
        statement.ExecDirect( L"{ CALL [ReferencePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateReferencePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& defaultValue, const Guid& referencedElementType )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &defaultValue );
        statement.BindGuidParameter( 7, &referencedElementType );
        statement.ExecDirect( L"{ CALL [ReferencePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteReferencePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ReferencePropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSBytePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, SByte defaultValue, SByte minValue, SByte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindSByteParameter( 5, &defaultValue );
        statement.BindSByteParameter( 6, &minValue );
        statement.BindSByteParameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [SBytePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, SByte defaultValue, SByte minValue, SByte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindSByteParameter( 6, &defaultValue );
        statement.BindSByteParameter( 7, &minValue );
        statement.BindSByteParameter( 8, &maxValue );
        statement.ExecDirect( L"{ CALL [SBytePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SBytePropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSinglePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, float defaultValue, float minValue, float maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindSingleParameter( 5, &defaultValue );
        statement.BindSingleParameter( 6, &minValue );
        statement.BindSingleParameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [SinglePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSinglePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, float defaultValue, float minValue, float maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindSingleParameter( 6, &defaultValue );
        statement.BindSingleParameter( 7, &minValue );
        statement.BindSingleParameter( 8, &maxValue );
        statement.ExecDirect( L"{ CALL [SinglePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSinglePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SinglePropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertStringPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> defaultValue, FixedDBWideString<100> pattern )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindFixedDBWideStringParameter( 5, defaultValue );
        statement.BindFixedDBWideStringParameter( 6, pattern );
        statement.ExecDirect( L"{ CALL [StringPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateStringPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> defaultValue, FixedDBWideString<100> pattern )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindFixedDBWideStringParameter( 6, defaultValue );
        statement.BindFixedDBWideStringParameter( 7, pattern );
        statement.ExecDirect( L"{ CALL [StringPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteStringPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [StringPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Byte minValue, Byte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindByteParameter( 5, &minValue );
        statement.BindByteParameter( 6, &maxValue );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Byte minValue, Byte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindByteParameter( 6, &minValue );
        statement.BindByteParameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> minValue, FixedDBWideString<100> maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindFixedDBWideStringParameter( 5, minValue );
        statement.BindFixedDBWideStringParameter( 6, maxValue );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> minValue, FixedDBWideString<100> maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindFixedDBWideStringParameter( 6, minValue );
        statement.BindFixedDBWideStringParameter( 7, maxValue );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, double minValue, double maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindDoubleParameter( 5, &minValue );
        statement.BindDoubleParameter( 6, &maxValue );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, double minValue, double maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindDoubleParameter( 6, &minValue );
        statement.BindDoubleParameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int16 minValue, Int16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt16Parameter( 5, &minValue );
        statement.BindInt16Parameter( 6, &maxValue );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int16 minValue, Int16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt16Parameter( 6, &minValue );
        statement.BindInt16Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int32 minValue, Int32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt32Parameter( 5, &minValue );
        statement.BindInt32Parameter( 6, &maxValue );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int32 minValue, Int32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt32Parameter( 6, &minValue );
        statement.BindInt32Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt64Parameter( 5, &minValue );
        statement.BindInt64Parameter( 6, &maxValue );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt64Parameter( 6, &minValue );
        statement.BindInt64Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& referencedElementType )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &referencedElementType );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& referencedElementType )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &referencedElementType );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, SByte minValue, SByte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindSByteParameter( 5, &minValue );
        statement.BindSByteParameter( 6, &maxValue );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, SByte minValue, SByte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindSByteParameter( 6, &minValue );
        statement.BindSByteParameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, float minValue, float maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindSingleParameter( 5, &minValue );
        statement.BindSingleParameter( 6, &maxValue );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, float minValue, float maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindSingleParameter( 6, &minValue );
        statement.BindSingleParameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> pattern )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindFixedDBWideStringParameter( 5, pattern );
        statement.ExecDirect( L"{ CALL [StringTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> pattern )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindFixedDBWideStringParameter( 6, pattern );
        statement.ExecDirect( L"{ CALL [StringTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [StringTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const TimeSpan& minValue, const TimeSpan& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindTimeSpanParameter( 5, minValue );
        statement.BindTimeSpanParameter( 6, maxValue );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const TimeSpan& minValue, const TimeSpan& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindTimeSpanParameter( 6, minValue );
        statement.BindTimeSpanParameter( 7, maxValue );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt16 minValue, UInt16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindUInt16Parameter( 5, &minValue );
        statement.BindUInt16Parameter( 6, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt16 minValue, UInt16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindUInt16Parameter( 6, &minValue );
        statement.BindUInt16Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt32 minValue, UInt32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindUInt32Parameter( 5, &minValue );
        statement.BindUInt32Parameter( 6, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt32 minValue, UInt32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindUInt32Parameter( 6, &minValue );
        statement.BindUInt32Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt64Parameter( 5, &minValue );
        statement.BindInt64Parameter( 6, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt64Parameter( 6, &minValue );
        statement.BindInt64Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTimeSpanPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const TimeSpan& defaultValue, const TimeSpan& minValue, const TimeSpan& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindTimeSpanParameter( 5, defaultValue );
        statement.BindTimeSpanParameter( 6, minValue );
        statement.BindTimeSpanParameter( 7, maxValue );
        statement.ExecDirect( L"{ CALL [TimeSpanPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTimeSpanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const TimeSpan& defaultValue, const TimeSpan& minValue, const TimeSpan& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindTimeSpanParameter( 6, defaultValue );
        statement.BindTimeSpanParameter( 7, minValue );
        statement.BindTimeSpanParameter( 8, maxValue );
        statement.ExecDirect( L"{ CALL [TimeSpanPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTimeSpanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TimeSpanPropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt16PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt16 defaultValue, UInt16 minValue, UInt16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindUInt16Parameter( 5, &defaultValue );
        statement.BindUInt16Parameter( 6, &minValue );
        statement.BindUInt16Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt16PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt16 defaultValue, UInt16 minValue, UInt16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindUInt16Parameter( 6, &defaultValue );
        statement.BindUInt16Parameter( 7, &minValue );
        statement.BindUInt16Parameter( 8, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt16PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt16PropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt32PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt32 defaultValue, UInt32 minValue, UInt32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindUInt32Parameter( 5, &defaultValue );
        statement.BindUInt32Parameter( 6, &minValue );
        statement.BindUInt32Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt32PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt32 defaultValue, UInt32 minValue, UInt32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindUInt32Parameter( 6, &defaultValue );
        statement.BindUInt32Parameter( 7, &minValue );
        statement.BindUInt32Parameter( 8, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt32PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt32PropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt64PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt64Parameter( 5, &defaultValue );
        statement.BindInt64Parameter( 6, &minValue );
        statement.BindInt64Parameter( 7, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt64PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt64Parameter( 6, &defaultValue );
        statement.BindInt64Parameter( 7, &minValue );
        statement.BindInt64Parameter( 8, &maxValue );
        statement.ExecDirect( L"{ CALL [UInt64PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt64PropertyDefinitionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarAlarmStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Data::AlarmState type )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &type );
        statement.ExecDirect( L"{ CALL [RadarAlarmStatusInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarAlarmStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Data::AlarmState type )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &type );
        statement.ExecDirect( L"{ CALL [RadarAlarmStatusUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarAlarmStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarAlarmStatusDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarCommand( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [RadarCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [RadarCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarCommandDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarCommandGetStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [RadarCommandGetStatusInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarCommandGetStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [RadarCommandGetStatusUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarCommandGetStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarCommandGetStatusDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.ExecDirect( L"{ CALL [RadarCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.ExecDirect( L"{ CALL [RadarCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarCommandReplyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarCommandReplyGetStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationCount, Data::RadarPulse pulse, bool tx )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.BindInt32Parameter( 7, &azimuthCount );
        statement.BindInt32Parameter( 8, &triggerCount );
        statement.BindTimeSpanParameter( 9, rotationCount );
        statement.BindEnumParameter( 10, &pulse );
        statement.BindBooleanParameter( 11, &tx );
        statement.ExecDirect( L"{ CALL [RadarCommandReplyGetStatusInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarCommandReplyGetStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationCount, Data::RadarPulse pulse, bool tx )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.BindInt32Parameter( 8, &azimuthCount );
        statement.BindInt32Parameter( 9, &triggerCount );
        statement.BindTimeSpanParameter( 10, rotationCount );
        statement.BindEnumParameter( 11, &pulse );
        statement.BindBooleanParameter( 12, &tx );
        statement.ExecDirect( L"{ CALL [RadarCommandReplyGetStatusUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarCommandReplyGetStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarCommandReplyGetStatusDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 radarProtocolVersion, FixedDBWideString<100> radarIPAddress, Int32 radarPort, Int32 radarConfigurationPort, const TimeSpan& skipMagicTimeout, const TimeSpan& readTimeout, const TimeSpan& synchronizationInterval, Int32 targetsRefreshRate, Int32 range, Int32 sectorCount, Int32 sectorOffset, UInt32 imageColor, const DBUInt32& imageSubstitutionColor, UInt32 transparentColor, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY, Data::RadarImageType radarImageType, UInt32 trackColor, UInt32 vectorColor, bool enableNmea, FixedDBWideString<100> nmeaReceiverIPAddress, Int32 nmeaReceiverPort, FixedDBWideString<100> nmeaReceiverSourceId )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, &radarProtocolVersion );
        statement.BindFixedDBWideStringParameter( 5, radarIPAddress );
        statement.BindInt32Parameter( 6, &radarPort );
        statement.BindInt32Parameter( 7, &radarConfigurationPort );
        statement.BindTimeSpanParameter( 8, skipMagicTimeout );
        statement.BindTimeSpanParameter( 9, readTimeout );
        statement.BindTimeSpanParameter( 10, synchronizationInterval );
        statement.BindInt32Parameter( 11, &targetsRefreshRate );
        statement.BindInt32Parameter( 12, &range );
        statement.BindInt32Parameter( 13, &sectorCount );
        statement.BindInt32Parameter( 14, &sectorOffset );
        statement.BindUInt32Parameter( 15, &imageColor );
        statement.BindUInt32Parameter( 16, imageSubstitutionColor );
        statement.BindUInt32Parameter( 17, &transparentColor );
        statement.BindDoubleParameter( 18, &imageScaleFactorX );
        statement.BindDoubleParameter( 19, &imageOffsetX );
        statement.BindDoubleParameter( 20, &imageScaleFactorY );
        statement.BindDoubleParameter( 21, &imageOffsetY );
        statement.BindEnumParameter( 22, &radarImageType );
        statement.BindUInt32Parameter( 23, &trackColor );
        statement.BindUInt32Parameter( 24, &vectorColor );
        statement.BindBooleanParameter( 25, &enableNmea );
        statement.BindFixedDBWideStringParameter( 26, nmeaReceiverIPAddress );
        statement.BindInt32Parameter( 27, &nmeaReceiverPort );
        statement.BindFixedDBWideStringParameter( 28, nmeaReceiverSourceId );
        statement.ExecDirect( L"{ CALL [RadarConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 radarProtocolVersion, FixedDBWideString<100> radarIPAddress, Int32 radarPort, Int32 radarConfigurationPort, const TimeSpan& skipMagicTimeout, const TimeSpan& readTimeout, const TimeSpan& synchronizationInterval, Int32 targetsRefreshRate, Int32 range, Int32 sectorCount, Int32 sectorOffset, UInt32 imageColor, const DBUInt32& imageSubstitutionColor, UInt32 transparentColor, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY, Data::RadarImageType radarImageType, UInt32 trackColor, UInt32 vectorColor, bool enableNmea, FixedDBWideString<100> nmeaReceiverIPAddress, Int32 nmeaReceiverPort, FixedDBWideString<100> nmeaReceiverSourceId )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, &radarProtocolVersion );
        statement.BindFixedDBWideStringParameter( 6, radarIPAddress );
        statement.BindInt32Parameter( 7, &radarPort );
        statement.BindInt32Parameter( 8, &radarConfigurationPort );
        statement.BindTimeSpanParameter( 9, skipMagicTimeout );
        statement.BindTimeSpanParameter( 10, readTimeout );
        statement.BindTimeSpanParameter( 11, synchronizationInterval );
        statement.BindInt32Parameter( 12, &targetsRefreshRate );
        statement.BindInt32Parameter( 13, &range );
        statement.BindInt32Parameter( 14, &sectorCount );
        statement.BindInt32Parameter( 15, &sectorOffset );
        statement.BindUInt32Parameter( 16, &imageColor );
        statement.BindUInt32Parameter( 17, imageSubstitutionColor );
        statement.BindUInt32Parameter( 18, &transparentColor );
        statement.BindDoubleParameter( 19, &imageScaleFactorX );
        statement.BindDoubleParameter( 20, &imageOffsetX );
        statement.BindDoubleParameter( 21, &imageScaleFactorY );
        statement.BindDoubleParameter( 22, &imageOffsetY );
        statement.BindEnumParameter( 23, &radarImageType );
        statement.BindUInt32Parameter( 24, &trackColor );
        statement.BindUInt32Parameter( 25, &vectorColor );
        statement.BindBooleanParameter( 26, &enableNmea );
        statement.BindFixedDBWideStringParameter( 27, nmeaReceiverIPAddress );
        statement.BindInt32Parameter( 28, &nmeaReceiverPort );
        statement.BindFixedDBWideStringParameter( 29, nmeaReceiverSourceId );
        statement.ExecDirect( L"{ CALL [RadarConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarImage( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, UInt32 depth, Int32 resolution, Int32 range, const Binary& image )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindUInt32Parameter( 4, &depth );
        statement.BindInt32Parameter( 5, &resolution );
        statement.BindInt32Parameter( 6, &range );
        statement.BindBinaryParameter( 7, image );
        statement.ExecDirect( L"{ CALL [RadarImageInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarImage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, UInt32 depth, Int32 resolution, Int32 range, const Binary& image )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindUInt32Parameter( 5, &depth );
        statement.BindInt32Parameter( 6, &resolution );
        statement.BindInt32Parameter( 7, &range );
        statement.BindBinaryParameter( 8, image );
        statement.ExecDirect( L"{ CALL [RadarImageUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarImage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarImageDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarRawTrackTable( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 count, const Binary& table )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, &count );
        statement.BindBinaryParameter( 5, table );
        statement.ExecDirect( L"{ CALL [RadarRawTrackTableInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarRawTrackTable( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 count, const Binary& table )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, &count );
        statement.BindBinaryParameter( 6, table );
        statement.ExecDirect( L"{ CALL [RadarRawTrackTableUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarRawTrackTable( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarRawTrackTableDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationTime, Data::RadarPulse pulse, bool tx, bool tracking )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, &azimuthCount );
        statement.BindInt32Parameter( 5, &triggerCount );
        statement.BindTimeSpanParameter( 6, rotationTime );
        statement.BindEnumParameter( 7, &pulse );
        statement.BindBooleanParameter( 8, &tx );
        statement.BindBooleanParameter( 9, &tracking );
        statement.ExecDirect( L"{ CALL [RadarStatusInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationTime, Data::RadarPulse pulse, bool tx, bool tracking )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, &azimuthCount );
        statement.BindInt32Parameter( 6, &triggerCount );
        statement.BindTimeSpanParameter( 7, rotationTime );
        statement.BindEnumParameter( 8, &pulse );
        statement.BindBooleanParameter( 9, &tx );
        statement.BindBooleanParameter( 10, &tracking );
        statement.ExecDirect( L"{ CALL [RadarStatusUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarStatusDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadioCommand( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radio );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [RadioCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadioCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radio );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [RadioCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadioCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadioCommandDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadioCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radio );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.ExecDirect( L"{ CALL [RadioCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadioCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radio );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.ExecDirect( L"{ CALL [RadioCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadioCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadioCommandReplyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadioConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, double longitude, double latitude, FixedDBWideString<100> playbackUrl, FixedDBWideString<100> radioIPAddress, Int32 radioPort, FixedDBWideString<100> ed137IPAddress, Int32 ed137Port )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radio );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, &longitude );
        statement.BindDoubleParameter( 5, &latitude );
        statement.BindFixedDBWideStringParameter( 6, playbackUrl );
        statement.BindFixedDBWideStringParameter( 7, radioIPAddress );
        statement.BindInt32Parameter( 8, &radioPort );
        statement.BindFixedDBWideStringParameter( 9, ed137IPAddress );
        statement.BindInt32Parameter( 10, &ed137Port );
        statement.ExecDirect( L"{ CALL [RadioConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadioConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, double longitude, double latitude, FixedDBWideString<100> playbackUrl, FixedDBWideString<100> radioIPAddress, Int32 radioPort, FixedDBWideString<100> ed137IPAddress, Int32 ed137Port )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radio );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &longitude );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindFixedDBWideStringParameter( 7, playbackUrl );
        statement.BindFixedDBWideStringParameter( 8, radioIPAddress );
        statement.BindInt32Parameter( 9, &radioPort );
        statement.BindFixedDBWideStringParameter( 10, ed137IPAddress );
        statement.BindInt32Parameter( 11, &ed137Port );
        statement.ExecDirect( L"{ CALL [RadioConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadioConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadioConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadomeCommand( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radome );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [RadomeCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadomeCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radome );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [RadomeCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadomeCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadomeCommandDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadomeCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radome );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.ExecDirect( L"{ CALL [RadomeCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadomeCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radome );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.ExecDirect( L"{ CALL [RadomeCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadomeCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadomeCommandReplyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadomeConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, const TimeSpan& interval, double lowPressureLimit, double highPressureLimit, double lowTemperatureLimit, double highTemperatureLimit )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radome );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindTimeSpanParameter( 4, interval );
        statement.BindDoubleParameter( 5, &lowPressureLimit );
        statement.BindDoubleParameter( 6, &highPressureLimit );
        statement.BindDoubleParameter( 7, &lowTemperatureLimit );
        statement.BindDoubleParameter( 8, &highTemperatureLimit );
        statement.ExecDirect( L"{ CALL [RadomeConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadomeConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, const TimeSpan& interval, double lowPressureLimit, double highPressureLimit, double lowTemperatureLimit, double highTemperatureLimit )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &radome );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindTimeSpanParameter( 5, interval );
        statement.BindDoubleParameter( 6, &lowPressureLimit );
        statement.BindDoubleParameter( 7, &highPressureLimit );
        statement.BindDoubleParameter( 8, &lowTemperatureLimit );
        statement.BindDoubleParameter( 9, &highTemperatureLimit );
        statement.ExecDirect( L"{ CALL [RadomeConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadomeConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadomeConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertReferenceTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &value );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateReferenceTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &value );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteReferenceTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSByteTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBSByte& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindSByteParameter( 4, value );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBSByte& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindSByteParameter( 5, value );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSecurityDomain( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindWideStringParameter( 3, description );
        statement.ExecDirect( L"{ CALL [SecurityDomainInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSecurityDomain( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.ExecDirect( L"{ CALL [SecurityDomainUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSecurityDomain( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SecurityDomainDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSecurityLogin( const ODBC::Connection& connection, Guid& id, const Guid& domain, FixedDBWideString<255> identity, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &domain );
        statement.BindFixedDBWideStringParameter( 3, identity );
        statement.BindWideStringParameter( 4, description );
        statement.ExecDirect( L"{ CALL [SecurityLoginInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSecurityLogin( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& domain, FixedDBWideString<255> identity, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &domain );
        statement.BindFixedDBWideStringParameter( 4, identity );
        statement.BindWideStringParameter( 5, description );
        statement.ExecDirect( L"{ CALL [SecurityLoginUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSecurityLogin( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SecurityLoginDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSecurityRole( const ODBC::Connection& connection, Guid& id, const Guid& domain, FixedDBWideString<255> identity, const WideString& description, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &domain );
        statement.BindFixedDBWideStringParameter( 3, identity );
        statement.BindWideStringParameter( 4, description );
        statement.BindFixedDBWideStringParameter( 5, name );
        statement.ExecDirect( L"{ CALL [SecurityRoleInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSecurityRole( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& domain, FixedDBWideString<255> identity, const WideString& description, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &domain );
        statement.BindFixedDBWideStringParameter( 4, identity );
        statement.BindWideStringParameter( 5, description );
        statement.BindFixedDBWideStringParameter( 6, name );
        statement.ExecDirect( L"{ CALL [SecurityRoleUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSecurityRole( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SecurityRoleDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSecurityIdentifierRoleLink( const ODBC::Connection& connection, Guid& id, const Guid& member, const Guid& role, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &member );
        statement.BindGuidParameter( 3, &role );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.ExecDirect( L"{ CALL [SecurityIdentifierRoleLinkInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSecurityIdentifierRoleLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& member, const Guid& role, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &member );
        statement.BindGuidParameter( 4, &role );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.ExecDirect( L"{ CALL [SecurityIdentifierRoleLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSecurityIdentifierRoleLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SecurityIdentifierRoleLinkDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSecurityLoginSession( const ODBC::Connection& connection, Guid& id, const Guid& login, const DateTime& fromTime, const DBDateTime& throughTime, const Guid& clientSession, FixedDBWideString<260> notificationQueueName, FixedDBWideString<260> messageQueueName )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &login );
        statement.BindDateTimeParameter( 3, fromTime );
        statement.BindDateTimeParameter( 4, throughTime );
        statement.BindGuidParameter( 5, &clientSession );
        statement.BindFixedDBWideStringParameter( 6, notificationQueueName );
        statement.BindFixedDBWideStringParameter( 7, messageQueueName );
        statement.ExecDirect( L"{ CALL [SecurityLoginSessionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSecurityLoginSession( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& login, const DateTime& fromTime, const DBDateTime& throughTime, const Guid& clientSession, FixedDBWideString<260> notificationQueueName, FixedDBWideString<260> messageQueueName )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &login );
        statement.BindDateTimeParameter( 4, fromTime );
        statement.BindDateTimeParameter( 5, throughTime );
        statement.BindGuidParameter( 6, &clientSession );
        statement.BindFixedDBWideStringParameter( 7, notificationQueueName );
        statement.BindFixedDBWideStringParameter( 8, messageQueueName );
        statement.ExecDirect( L"{ CALL [SecurityLoginSessionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSecurityLoginSession( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SecurityLoginSessionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSecurityPermission( const ODBC::Connection& connection, Guid& id, const Guid& identifier, const DateTime& timestamp, Int32 typeCode, bool canCreate, bool canRead, bool canUpdate, bool canDelete )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &identifier );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, &typeCode );
        statement.BindBooleanParameter( 5, &canCreate );
        statement.BindBooleanParameter( 6, &canRead );
        statement.BindBooleanParameter( 7, &canUpdate );
        statement.BindBooleanParameter( 8, &canDelete );
        statement.ExecDirect( L"{ CALL [SecurityPermissionInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSecurityPermission( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& identifier, const DateTime& timestamp, Int32 typeCode, bool canCreate, bool canRead, bool canUpdate, bool canDelete )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &identifier );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, &typeCode );
        statement.BindBooleanParameter( 6, &canCreate );
        statement.BindBooleanParameter( 7, &canRead );
        statement.BindBooleanParameter( 8, &canUpdate );
        statement.BindBooleanParameter( 9, &canDelete );
        statement.ExecDirect( L"{ CALL [SecurityPermissionUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSecurityPermission( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SecurityPermissionDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSingleTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBSingle& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindSingleParameter( 4, value );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSingleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBSingle& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindSingleParameter( 5, value );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSingleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertStringTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const WideString& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindWideStringParameter( 4, value );
        statement.ExecDirect( L"{ CALL [StringTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateStringTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const WideString& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindWideStringParameter( 5, value );
        statement.ExecDirect( L"{ CALL [StringTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteStringTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [StringTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBinaryTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBinaryTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBinaryTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BinaryTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertBooleanTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateBooleanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteBooleanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [BooleanTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& aidToNavigation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &aidToNavigation );
        statement.ExecDirect( L"{ CALL [AisAidToNavigationOffPositionTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& aidToNavigation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &aidToNavigation );
        statement.ExecDirect( L"{ CALL [AisAidToNavigationOffPositionTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisAidToNavigationOffPositionTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDeviceEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& device )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &device );
        statement.ExecDirect( L"{ CALL [DeviceEnabledTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDeviceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& device )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &device );
        statement.ExecDirect( L"{ CALL [DeviceEnabledTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDeviceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DeviceEnabledTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarAutomaticSensitivityTimeControlTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarAutomaticSensitivityTimeControlTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarAutomaticSensitivityTimeControlTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarBlankSector1Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarBlankSector1TimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarBlankSector1Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarBlankSector1TimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarBlankSector1Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarBlankSector1TimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarBlankSector2Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarBlankSector2TimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarBlankSector2Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarBlankSector2TimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarBlankSector2Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarBlankSector2TimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarEnableAutomaticFrequencyControlTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarEnableAutomaticFrequencyControlTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarEnableAutomaticFrequencyControlTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarEnableFastTimeConstantTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarEnableFastTimeConstantTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarEnableFastTimeConstantTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarEnableSensitivityTimeControlTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarEnableSensitivityTimeControlTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarEnableSensitivityTimeControlTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarPowerOnTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarPowerOnTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarPowerOnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarPowerOnTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarPowerOnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarPowerOnTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarSaveSettingsTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarSaveSettingsTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarSaveSettingsTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarSaveSettingsTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarSaveSettingsTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarSaveSettingsTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarTrackingTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarTrackingTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarTrackingTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarTrackingTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarTrackingTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarTrackingTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& proxySession )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &proxySession );
        statement.ExecDirect( L"{ CALL [MediaProxySessionEnabledTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& proxySession )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &proxySession );
        statement.ExecDirect( L"{ CALL [MediaProxySessionEnabledTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MediaProxySessionEnabledTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertMediaServiceEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& service )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &service );
        statement.ExecDirect( L"{ CALL [MediaServiceEnabledTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateMediaServiceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& service )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &service );
        statement.ExecDirect( L"{ CALL [MediaServiceEnabledTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteMediaServiceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [MediaServiceEnabledTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertByteTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ByteTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDateTimeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDateTimeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDateTimeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DateTimeTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertDoubleTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateDoubleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteDoubleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [DoubleTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGNSSAltitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gNSSDevice );
        statement.ExecDirect( L"{ CALL [GNSSAltitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGNSSAltitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gNSSDevice );
        statement.ExecDirect( L"{ CALL [GNSSAltitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGNSSAltitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GNSSAltitudeTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGNSSLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gNSSDevice );
        statement.ExecDirect( L"{ CALL [GNSSLatitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGNSSLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gNSSDevice );
        statement.ExecDirect( L"{ CALL [GNSSLatitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGNSSLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GNSSLatitudeTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGNSSLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gNSSDevice );
        statement.ExecDirect( L"{ CALL [GNSSLongitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGNSSLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gNSSDevice );
        statement.ExecDirect( L"{ CALL [GNSSLongitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGNSSLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GNSSLongitudeTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroCourseTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroCourseTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroCourseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroCourseTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroCourseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroCourseTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroHeadingMagneticNorthTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroHeadingMagneticNorthTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroHeadingMagneticNorthTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroHeadingTrueNorthTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroHeadingTrueNorthTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroHeadingTrueNorthTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroPitchTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroPitchTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroPitchTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroPitchTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroPitchTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroPitchTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroRateOfTurnTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroRateOfTurnTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroRateOfTurnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroRateOfTurnTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroRateOfTurnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroRateOfTurnTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroRollTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroRollTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroRollTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroRollTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroRollTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroRollTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGyroSpeedTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroSpeedTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGyroSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.ExecDirect( L"{ CALL [GyroSpeedTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGyroSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GyroSpeedTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarLatitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarLatitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarLatitudeTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarLongitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarLongitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarLongitudeTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadomeDewPointTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radome );
        statement.ExecDirect( L"{ CALL [RadomeDewPointTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadomeDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radome );
        statement.ExecDirect( L"{ CALL [RadomeDewPointTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadomeDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadomeDewPointTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadomePressureTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radome );
        statement.ExecDirect( L"{ CALL [RadomePressureTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadomePressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radome );
        statement.ExecDirect( L"{ CALL [RadomePressureTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadomePressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadomePressureTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadomeTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radome );
        statement.ExecDirect( L"{ CALL [RadomeTemperatureTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadomeTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radome );
        statement.ExecDirect( L"{ CALL [RadomeTemperatureTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadomeTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadomeTemperatureTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertVesselDraughtTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &vessel );
        statement.ExecDirect( L"{ CALL [VesselDraughtTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateVesselDraughtTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &vessel );
        statement.ExecDirect( L"{ CALL [VesselDraughtTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteVesselDraughtTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [VesselDraughtTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertViewLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &view );
        statement.ExecDirect( L"{ CALL [ViewLatitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateViewLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &view );
        statement.ExecDirect( L"{ CALL [ViewLatitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteViewLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ViewLatitudeTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertViewLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &view );
        statement.ExecDirect( L"{ CALL [ViewLongitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateViewLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &view );
        statement.ExecDirect( L"{ CALL [ViewLongitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteViewLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ViewLongitudeTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertViewZoomLevelTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &view );
        statement.ExecDirect( L"{ CALL [ViewZoomLevelTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateViewZoomLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &view );
        statement.ExecDirect( L"{ CALL [ViewZoomLevelTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteViewZoomLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ViewZoomLevelTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationAbsoluteHumidityTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationAbsoluteHumidityTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationAbsoluteHumidityTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationAirTemperatureTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationAirTemperatureTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationAirTemperatureTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationBarometricPressureTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationBarometricPressureTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationBarometricPressureTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationDewPointTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationDewPointTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationDewPointTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationDewPointTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationRelativeHumidityTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationRelativeHumidityTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationRelativeHumidityTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationWaterTemperatureTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationWaterTemperatureTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationWaterTemperatureTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationWindDirectionTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationWindDirectionTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationWindDirectionTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationWindSpeedTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.ExecDirect( L"{ CALL [WeatherStationWindSpeedTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationWindSpeedTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGeoPosition2DTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [GeoPosition2DTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGeoPosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [GeoPosition2DTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGeoPosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GeoPosition2DTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& aidToNavigation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &aidToNavigation );
        statement.ExecDirect( L"{ CALL [AisAidToNavigationPositionTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& aidToNavigation )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &aidToNavigation );
        statement.ExecDirect( L"{ CALL [AisAidToNavigationPositionTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [AisAidToNavigationPositionTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGeoPosition3DTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [GeoPosition3DTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGeoPosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [GeoPosition3DTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGeoPosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GeoPosition3DTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertGuidTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateGuidTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteGuidTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [GuidTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt16Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int16TimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt32Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int32TimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarAzimuthOffsetTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarAzimuthOffsetTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarAzimuthOffsetTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarFastTimeConstantLevelTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarFastTimeConstantLevelTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarFastTimeConstantLevelTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarFastTimeConstantModeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarFastTimeConstantModeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarFastTimeConstantModeTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarPulseTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarPulseTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarPulseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarPulseTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarPulseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarPulseTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarSector1EndTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarSector1EndTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarSector1EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarSector1EndTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarSector1EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarSector1EndTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarSector1StartTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarSector1StartTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarSector1StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarSector1StartTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarSector1StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarSector1StartTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarSector2EndTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarSector2EndTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarSector2EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarSector2EndTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarSector2EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarSector2EndTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarSector2StartTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarSector2StartTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarSector2StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarSector2StartTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarSector2StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarSector2StartTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarSensitivityTimeControlLevelTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarSensitivityTimeControlLevelTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarSensitivityTimeControlLevelTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadarTuningTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.ExecDirect( L"{ CALL [RadarTuningTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadarTuningTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.ExecDirect( L"{ CALL [RadarTuningTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadarTuningTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadarTuningTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &vessel );
        statement.ExecDirect( L"{ CALL [VesselPersonsOnBoardTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &vessel );
        statement.ExecDirect( L"{ CALL [VesselPersonsOnBoardTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [VesselPersonsOnBoardTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertInt64Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Int64TimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertPosition2DTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [Position2DTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdatePosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [Position2DTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeletePosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Position2DTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertPosition3DTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [Position3DTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdatePosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [Position3DTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeletePosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Position3DTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertReferenceTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateReferenceTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteReferenceTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ReferenceTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSByteTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SByteTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertSingleTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateSingleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteSingleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [SingleTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertStringTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [StringTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateStringTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [StringTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteStringTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [StringTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTimeSpanTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTimeSpanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTimeSpanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt16Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt32Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertRadomeStatusTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radome );
        statement.ExecDirect( L"{ CALL [RadomeStatusTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateRadomeStatusTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radome );
        statement.ExecDirect( L"{ CALL [RadomeStatusTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteRadomeStatusTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [RadomeStatusTimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt64Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTimeseriesCatalog( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.ExecDirect( L"{ CALL [TimeseriesCatalogInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTimeseriesCatalog( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.ExecDirect( L"{ CALL [TimeseriesCatalogUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTimeseriesCatalog( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TimeseriesCatalogDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTimeseriesInfo( const ODBC::Connection& connection, Guid& id, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindDateTimeParameter( 2, firstTimestamp );
        statement.BindDateTimeParameter( 3, lastTimestamp );
        statement.BindInt64Parameter( 4, &count );
        statement.ExecDirect( L"{ CALL [TimeseriesInfoInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTimeseriesInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindDateTimeParameter( 3, firstTimestamp );
        statement.BindDateTimeParameter( 4, lastTimestamp );
        statement.BindInt64Parameter( 5, &count );
        statement.ExecDirect( L"{ CALL [TimeseriesInfoUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTimeseriesInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TimeseriesInfoDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTimeSpanTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBTimeSpan& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindTimeSpanParameter( 4, value );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTimeSpanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBTimeSpan& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindTimeSpanParameter( 5, value );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTimeSpanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TimeSpanTimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTrackableItemTrackLink( const ODBC::Connection& connection, Guid& id, const Guid& item, const Guid& track, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &item );
        statement.BindGuidParameter( 3, &track );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.ExecDirect( L"{ CALL [TrackableItemTrackLinkInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTrackableItemTrackLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, const Guid& track, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &item );
        statement.BindGuidParameter( 4, &track );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.ExecDirect( L"{ CALL [TrackableItemTrackLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTrackableItemTrackLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TrackableItemTrackLinkDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTrack( const ODBC::Connection& connection, Guid& id, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &tracker );
        statement.BindInt64Parameter( 3, &trackNumber );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.ExecDirect( L"{ CALL [TrackInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTrack( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &tracker );
        statement.BindInt64Parameter( 4, &trackNumber );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.ExecDirect( L"{ CALL [TrackUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTrack( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TrackDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTrack3D( const ODBC::Connection& connection, Guid& id, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &tracker );
        statement.BindInt64Parameter( 3, &trackNumber );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.ExecDirect( L"{ CALL [Track3DInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTrack3D( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &tracker );
        statement.BindInt64Parameter( 4, &trackNumber );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.ExecDirect( L"{ CALL [Track3DUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTrack3D( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [Track3DDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTrackerFilterParameters( const ODBC::Connection& connection, Guid& id, const Guid& tracker, FixedDBWideString<100> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &tracker );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.ExecDirect( L"{ CALL [TrackerFilterParametersInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTrackerFilterParameters( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, FixedDBWideString<100> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &tracker );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.ExecDirect( L"{ CALL [TrackerFilterParametersUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTrackerFilterParameters( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TrackerFilterParametersDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTrackerFilterParametersConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& parameters, const DateTime& timestamp, bool useNaivePredictor, Int32 numberOfPoints, Int32 windowSize, Int32 stabilizeCount, Int32 maxBadPoints, Data::TrackerFilterModelType modelType, double sigmaR, double sigmaAcc, double tauVel, double tauAcc, double deltaRMin, double deltaVMax, double deltaAMax )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &parameters );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindBooleanParameter( 4, &useNaivePredictor );
        statement.BindInt32Parameter( 5, &numberOfPoints );
        statement.BindInt32Parameter( 6, &windowSize );
        statement.BindInt32Parameter( 7, &stabilizeCount );
        statement.BindInt32Parameter( 8, &maxBadPoints );
        statement.BindEnumParameter( 9, &modelType );
        statement.BindDoubleParameter( 10, &sigmaR );
        statement.BindDoubleParameter( 11, &sigmaAcc );
        statement.BindDoubleParameter( 12, &tauVel );
        statement.BindDoubleParameter( 13, &tauAcc );
        statement.BindDoubleParameter( 14, &deltaRMin );
        statement.BindDoubleParameter( 15, &deltaVMax );
        statement.BindDoubleParameter( 16, &deltaAMax );
        statement.ExecDirect( L"{ CALL [TrackerFilterParametersConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTrackerFilterParametersConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& parameters, const DateTime& timestamp, bool useNaivePredictor, Int32 numberOfPoints, Int32 windowSize, Int32 stabilizeCount, Int32 maxBadPoints, Data::TrackerFilterModelType modelType, double sigmaR, double sigmaAcc, double tauVel, double tauAcc, double deltaRMin, double deltaVMax, double deltaAMax )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &parameters );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindBooleanParameter( 5, &useNaivePredictor );
        statement.BindInt32Parameter( 6, &numberOfPoints );
        statement.BindInt32Parameter( 7, &windowSize );
        statement.BindInt32Parameter( 8, &stabilizeCount );
        statement.BindInt32Parameter( 9, &maxBadPoints );
        statement.BindEnumParameter( 10, &modelType );
        statement.BindDoubleParameter( 11, &sigmaR );
        statement.BindDoubleParameter( 12, &sigmaAcc );
        statement.BindDoubleParameter( 13, &tauVel );
        statement.BindDoubleParameter( 14, &tauAcc );
        statement.BindDoubleParameter( 15, &deltaRMin );
        statement.BindDoubleParameter( 16, &deltaVMax );
        statement.BindDoubleParameter( 17, &deltaAMax );
        statement.ExecDirect( L"{ CALL [TrackerFilterParametersConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTrackerFilterParametersConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TrackerFilterParametersConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTrackInfo( const ODBC::Connection& connection, Guid& id, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count, const DBDouble& northWestLatitude, const DBDouble& northWestLongitude, const DBDouble& southEastLatitude, const DBDouble& southEastLongitude )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindDateTimeParameter( 2, firstTimestamp );
        statement.BindDateTimeParameter( 3, lastTimestamp );
        statement.BindInt64Parameter( 4, &count );
        statement.BindDoubleParameter( 5, northWestLatitude );
        statement.BindDoubleParameter( 6, northWestLongitude );
        statement.BindDoubleParameter( 7, southEastLatitude );
        statement.BindDoubleParameter( 8, southEastLongitude );
        statement.ExecDirect( L"{ CALL [TrackInfoInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTrackInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count, const DBDouble& northWestLatitude, const DBDouble& northWestLongitude, const DBDouble& southEastLatitude, const DBDouble& southEastLongitude )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindDateTimeParameter( 3, firstTimestamp );
        statement.BindDateTimeParameter( 4, lastTimestamp );
        statement.BindInt64Parameter( 5, &count );
        statement.BindDoubleParameter( 6, northWestLatitude );
        statement.BindDoubleParameter( 7, northWestLongitude );
        statement.BindDoubleParameter( 8, southEastLatitude );
        statement.BindDoubleParameter( 9, southEastLongitude );
        statement.ExecDirect( L"{ CALL [TrackInfoUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTrackInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TrackInfoDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTrackingServiceOptions( const ODBC::Connection& connection, Guid& id, const DateTime& timestamp, const TimeSpan& timerInterval, const TimeSpan& maxAgeOfCurrentTrackValue, double falseThreshold, double distanceThreshold, double distanceUnmergeThreshold, Int64 unmergeLatency, bool kalmanFiltering, double maxCourseDeviation, double maxSpeedDeviation, double minimumSpeedThreshold )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindDateTimeParameter( 2, timestamp );
        statement.BindTimeSpanParameter( 3, timerInterval );
        statement.BindTimeSpanParameter( 4, maxAgeOfCurrentTrackValue );
        statement.BindDoubleParameter( 5, &falseThreshold );
        statement.BindDoubleParameter( 6, &distanceThreshold );
        statement.BindDoubleParameter( 7, &distanceUnmergeThreshold );
        statement.BindInt64Parameter( 8, &unmergeLatency );
        statement.BindBooleanParameter( 9, &kalmanFiltering );
        statement.BindDoubleParameter( 10, &maxCourseDeviation );
        statement.BindDoubleParameter( 11, &maxSpeedDeviation );
        statement.BindDoubleParameter( 12, &minimumSpeedThreshold );
        statement.ExecDirect( L"{ CALL [TrackingServiceOptionsInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTrackingServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DateTime& timestamp, const TimeSpan& timerInterval, const TimeSpan& maxAgeOfCurrentTrackValue, double falseThreshold, double distanceThreshold, double distanceUnmergeThreshold, Int64 unmergeLatency, bool kalmanFiltering, double maxCourseDeviation, double maxSpeedDeviation, double minimumSpeedThreshold )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindTimeSpanParameter( 4, timerInterval );
        statement.BindTimeSpanParameter( 5, maxAgeOfCurrentTrackValue );
        statement.BindDoubleParameter( 6, &falseThreshold );
        statement.BindDoubleParameter( 7, &distanceThreshold );
        statement.BindDoubleParameter( 8, &distanceUnmergeThreshold );
        statement.BindInt64Parameter( 9, &unmergeLatency );
        statement.BindBooleanParameter( 10, &kalmanFiltering );
        statement.BindDoubleParameter( 11, &maxCourseDeviation );
        statement.BindDoubleParameter( 12, &maxSpeedDeviation );
        statement.BindDoubleParameter( 13, &minimumSpeedThreshold );
        statement.ExecDirect( L"{ CALL [TrackingServiceOptionsUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTrackingServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TrackingServiceOptionsDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTrackLink( const ODBC::Connection& connection, Guid& id, const Guid& primary, const Guid& secondary, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &primary );
        statement.BindGuidParameter( 3, &secondary );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.ExecDirect( L"{ CALL [TrackLinkInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTrackLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& primary, const Guid& secondary, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &primary );
        statement.BindGuidParameter( 4, &secondary );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.ExecDirect( L"{ CALL [TrackLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTrackLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TrackLinkDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTrackValue( const ODBC::Connection& connection, Guid& id, const Guid& track, const DateTime& timestamp, Data::TrackFlags flags, Data::TrackStatus status, double latitude, double longitude, double speed, double course, double heading )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &track );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &flags );
        statement.BindEnumParameter( 5, &status );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindDoubleParameter( 7, &longitude );
        statement.BindDoubleParameter( 8, &speed );
        statement.BindDoubleParameter( 9, &course );
        statement.BindDoubleParameter( 10, &heading );
        statement.ExecDirect( L"{ CALL [TrackValueInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTrackValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const DateTime& timestamp, Data::TrackFlags flags, Data::TrackStatus status, double latitude, double longitude, double speed, double course, double heading )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &track );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &flags );
        statement.BindEnumParameter( 6, &status );
        statement.BindDoubleParameter( 7, &latitude );
        statement.BindDoubleParameter( 8, &longitude );
        statement.BindDoubleParameter( 9, &speed );
        statement.BindDoubleParameter( 10, &course );
        statement.BindDoubleParameter( 11, &heading );
        statement.ExecDirect( L"{ CALL [TrackValueUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTrackValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TrackValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertTrackValue3D( const ODBC::Connection& connection, Guid& id, const Guid& track, const DateTime& timestamp, Data::TrackFlags3D flags, UInt32 status, double latitude, double longitude, double altitude, double speed, double course, double rateOfClimb )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &track );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &flags );
        statement.BindUInt32Parameter( 5, &status );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindDoubleParameter( 7, &longitude );
        statement.BindDoubleParameter( 8, &altitude );
        statement.BindDoubleParameter( 9, &speed );
        statement.BindDoubleParameter( 10, &course );
        statement.BindDoubleParameter( 11, &rateOfClimb );
        statement.ExecDirect( L"{ CALL [TrackValue3DInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateTrackValue3D( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const DateTime& timestamp, Data::TrackFlags3D flags, UInt32 status, double latitude, double longitude, double altitude, double speed, double course, double rateOfClimb )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &track );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &flags );
        statement.BindUInt32Parameter( 6, &status );
        statement.BindDoubleParameter( 7, &latitude );
        statement.BindDoubleParameter( 8, &longitude );
        statement.BindDoubleParameter( 9, &altitude );
        statement.BindDoubleParameter( 10, &speed );
        statement.BindDoubleParameter( 11, &course );
        statement.BindDoubleParameter( 12, &rateOfClimb );
        statement.ExecDirect( L"{ CALL [TrackValue3DUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteTrackValue3D( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [TrackValue3DDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt16TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBUInt16& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindUInt16Parameter( 4, value );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBUInt16& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindUInt16Parameter( 5, value );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt16TimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt32TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBUInt32& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindUInt32Parameter( 4, value );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBUInt32& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindUInt32Parameter( 5, value );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt32TimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertUInt64TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt64Parameter( 4, value );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateUInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt64Parameter( 5, value );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteUInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [UInt64TimeseriesValueDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertVehicleType( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.ExecDirect( L"{ CALL [VehicleTypeInsert]( ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateVehicleType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.ExecDirect( L"{ CALL [VehicleTypeUpdate]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteVehicleType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [VehicleTypeDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertVesselType( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, Int32 code )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindInt32Parameter( 3, &code );
        statement.ExecDirect( L"{ CALL [VesselTypeInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateVesselType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, Int32 code )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindInt32Parameter( 4, &code );
        statement.ExecDirect( L"{ CALL [VesselTypeUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteVesselType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [VesselTypeDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertView( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& zoomLevelTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &latitudeTimeseries );
        statement.BindGuidParameter( 4, &longitudeTimeseries );
        statement.BindGuidParameter( 5, &zoomLevelTimeseries );
        statement.ExecDirect( L"{ CALL [ViewInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateView( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& zoomLevelTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &latitudeTimeseries );
        statement.BindGuidParameter( 5, &longitudeTimeseries );
        statement.BindGuidParameter( 6, &zoomLevelTimeseries );
        statement.ExecDirect( L"{ CALL [ViewUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteView( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ViewDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertViewCameraLink( const ODBC::Connection& connection, Guid& id, const Guid& view, const Guid& camera, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &view );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.ExecDirect( L"{ CALL [ViewCameraLinkInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateViewCameraLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, const Guid& camera, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &view );
        statement.BindGuidParameter( 4, &camera );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.ExecDirect( L"{ CALL [ViewCameraLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteViewCameraLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ViewCameraLinkDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertViewTrackerLink( const ODBC::Connection& connection, Guid& id, const Guid& view, const Guid& tracker, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &view );
        statement.BindGuidParameter( 3, &tracker );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.ExecDirect( L"{ CALL [ViewTrackerLinkInsert]( ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateViewTrackerLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, const Guid& tracker, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &view );
        statement.BindGuidParameter( 4, &tracker );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.ExecDirect( L"{ CALL [ViewTrackerLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteViewTrackerLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ViewTrackerLinkDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationCommand( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &weatherStation );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.ExecDirect( L"{ CALL [WeatherStationCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &weatherStation );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.ExecDirect( L"{ CALL [WeatherStationCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationCommandDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &weatherStation );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.ExecDirect( L"{ CALL [WeatherStationCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &weatherStation );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.ExecDirect( L"{ CALL [WeatherStationCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationCommandReplyDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertWeatherStationConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, const TimeSpan& noDataTimeOut, const TimeSpan& sendInterval, double latitude, double longitude, double gyroOffset, bool enableAveraging, const TimeSpan& averagingInterval )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &weatherStation );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindTimeSpanParameter( 4, noDataTimeOut );
        statement.BindTimeSpanParameter( 5, sendInterval );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindDoubleParameter( 7, &longitude );
        statement.BindDoubleParameter( 8, &gyroOffset );
        statement.BindBooleanParameter( 9, &enableAveraging );
        statement.BindTimeSpanParameter( 10, averagingInterval );
        statement.ExecDirect( L"{ CALL [WeatherStationConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateWeatherStationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, const TimeSpan& noDataTimeOut, const TimeSpan& sendInterval, double latitude, double longitude, double gyroOffset, bool enableAveraging, const TimeSpan& averagingInterval )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &weatherStation );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindTimeSpanParameter( 5, noDataTimeOut );
        statement.BindTimeSpanParameter( 6, sendInterval );
        statement.BindDoubleParameter( 7, &latitude );
        statement.BindDoubleParameter( 8, &longitude );
        statement.BindDoubleParameter( 9, &gyroOffset );
        statement.BindBooleanParameter( 10, &enableAveraging );
        statement.BindTimeSpanParameter( 11, averagingInterval );
        statement.ExecDirect( L"{ CALL [WeatherStationConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteWeatherStationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [WeatherStationConfigurationDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertCircularZone( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, double radius )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindDoubleParameter( 3, &longitude );
        statement.BindDoubleParameter( 4, &latitude );
        statement.BindEnumParameter( 5, &alarmType );
        statement.BindTimeSpanParameter( 6, alarmTime );
        statement.BindTimeSpanParameter( 7, radarTrackMinimumLifetime );
        statement.BindDoubleParameter( 8, &speed );
        statement.BindUInt32Parameter( 9, &strokeColor );
        statement.BindUInt32Parameter( 10, &fillColor );
        statement.BindDoubleParameter( 11, &radius );
        statement.ExecDirect( L"{ CALL [CircularZoneInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateCircularZone( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, double radius )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindDoubleParameter( 4, &longitude );
        statement.BindDoubleParameter( 5, &latitude );
        statement.BindEnumParameter( 6, &alarmType );
        statement.BindTimeSpanParameter( 7, alarmTime );
        statement.BindTimeSpanParameter( 8, radarTrackMinimumLifetime );
        statement.BindDoubleParameter( 9, &speed );
        statement.BindUInt32Parameter( 10, &strokeColor );
        statement.BindUInt32Parameter( 11, &fillColor );
        statement.BindDoubleParameter( 12, &radius );
        statement.ExecDirect( L"{ CALL [CircularZoneUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteCircularZone( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [CircularZoneDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertPolygonZone( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, const Binary& polygon )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindDoubleParameter( 3, &longitude );
        statement.BindDoubleParameter( 4, &latitude );
        statement.BindEnumParameter( 5, &alarmType );
        statement.BindTimeSpanParameter( 6, alarmTime );
        statement.BindTimeSpanParameter( 7, radarTrackMinimumLifetime );
        statement.BindDoubleParameter( 8, &speed );
        statement.BindUInt32Parameter( 9, &strokeColor );
        statement.BindUInt32Parameter( 10, &fillColor );
        statement.BindBinaryParameter( 11, polygon );
        statement.ExecDirect( L"{ CALL [PolygonZoneInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdatePolygonZone( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, const Binary& polygon )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindDoubleParameter( 4, &longitude );
        statement.BindDoubleParameter( 5, &latitude );
        statement.BindEnumParameter( 6, &alarmType );
        statement.BindTimeSpanParameter( 7, alarmTime );
        statement.BindTimeSpanParameter( 8, radarTrackMinimumLifetime );
        statement.BindDoubleParameter( 9, &speed );
        statement.BindUInt32Parameter( 10, &strokeColor );
        statement.BindUInt32Parameter( 11, &fillColor );
        statement.BindBinaryParameter( 12, polygon );
        statement.ExecDirect( L"{ CALL [PolygonZoneUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeletePolygonZone( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [PolygonZoneDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertZoneExceptions( const ODBC::Connection& connection, Guid& id, const Guid& zone, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &zone );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.ExecDirect( L"{ CALL [ZoneExceptionsInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateZoneExceptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zone, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &zone );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.ExecDirect( L"{ CALL [ZoneExceptionsUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteZoneExceptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ZoneExceptionsDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertZoneExceptionsVesselLink( const ODBC::Connection& connection, Guid& id, const Guid& zoneExceptions, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &zoneExceptions );
        statement.BindGuidParameter( 3, &vessel );
        statement.ExecDirect( L"{ CALL [ZoneExceptionsVesselLinkInsert]( ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateZoneExceptionsVesselLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zoneExceptions, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &zoneExceptions );
        statement.BindGuidParameter( 4, &vessel );
        statement.ExecDirect( L"{ CALL [ZoneExceptionsVesselLinkUpdate]( ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteZoneExceptionsVesselLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ZoneExceptionsVesselLinkDelete]( ?, ? ) }" );
    }

    BARRELMAN_EXPORT void InsertZoneTrackAlarm( const ODBC::Connection& connection, Guid& id, const Guid& track, const Guid& zone, const Guid& radarTrack, const DateTime& timestamp, double latitude, double longitude, double speed, const DBDouble& course, const DBDouble& heading, double enterLatitude, double enterLongitude, const DBDouble& leaveLatitude, const DBDouble& leaveLongitude )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &track );
        statement.BindGuidParameter( 3, &zone );
        statement.BindGuidParameter( 4, &radarTrack );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindDoubleParameter( 7, &longitude );
        statement.BindDoubleParameter( 8, &speed );
        statement.BindDoubleParameter( 9, course );
        statement.BindDoubleParameter( 10, heading );
        statement.BindDoubleParameter( 11, &enterLatitude );
        statement.BindDoubleParameter( 12, &enterLongitude );
        statement.BindDoubleParameter( 13, leaveLatitude );
        statement.BindDoubleParameter( 14, leaveLongitude );
        statement.ExecDirect( L"{ CALL [ZoneTrackAlarmInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void UpdateZoneTrackAlarm( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const Guid& zone, const Guid& radarTrack, const DateTime& timestamp, double latitude, double longitude, double speed, const DBDouble& course, const DBDouble& heading, double enterLatitude, double enterLongitude, const DBDouble& leaveLatitude, const DBDouble& leaveLongitude )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion, ODBC::ParameterDirection::InputOutput );
        statement.BindGuidParameter( 3, &track );
        statement.BindGuidParameter( 4, &zone );
        statement.BindGuidParameter( 5, &radarTrack );
        statement.BindDateTimeParameter( 6, timestamp );
        statement.BindDoubleParameter( 7, &latitude );
        statement.BindDoubleParameter( 8, &longitude );
        statement.BindDoubleParameter( 9, &speed );
        statement.BindDoubleParameter( 10, course );
        statement.BindDoubleParameter( 11, heading );
        statement.BindDoubleParameter( 12, &enterLatitude );
        statement.BindDoubleParameter( 13, &enterLongitude );
        statement.BindDoubleParameter( 14, leaveLatitude );
        statement.BindDoubleParameter( 15, leaveLongitude );
        statement.ExecDirect( L"{ CALL [ZoneTrackAlarmUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
    }
    BARRELMAN_EXPORT void DeleteZoneTrackAlarm( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.ExecDirect( L"{ CALL [ZoneTrackAlarmDelete]( ?, ? ) }" );
    }

}
