#include "pch.h"

#include "StoredProcedures.h"


namespace Barrelman::Database
{

    BARRELMAN_EXPORT bool InsertAircraftType( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AircraftTypeInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAircraftType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AircraftTypeUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAircraftType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AircraftTypeDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceCommandDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceCommandReplyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, const FixedDBWideString<127>& userName, const FixedDBWideString<127>& password, double latitude, double longitude, const FixedDBWideString<127>& aisProviderLoginURL, const FixedDBWideString<32>& comPort, Int32 baudRate, bool filterByArea, double upperLeftCornerLatitude, double upperLeftCornerLongitude, double bottomRightCornerLatitude, double bottomRightCornerLongitude, const FixedDBWideString<127>& aisProviderIPAddress, Int32 aisProviderPort, bool useLogin, Int32 aisProviderLoginPort, bool canSendAISMessage, const WideString& textMessageHeader, const WideString& urls, Int32 udpPort, Data::AisDeviceConnectionType connectionType, bool enableRefreshAidToNavigationIn30sec, bool enableAidToNavigationFromFile, const WideString& aidToNavigationHeader, bool sendingMMSI, Int32 sourceUpdateRate, bool enableRefreshStayingStillTargetIn30sec, const WideString& excludeSendAisBaseStation, const WideString& excludeSendAisA, bool enableSendBaseStationAlarms, const FixedDBWideString<127>& aisWebConfig, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, const FixedDBWideString<127>& userName, const FixedDBWideString<127>& password, double latitude, double longitude, const FixedDBWideString<127>& aisProviderLoginURL, const FixedDBWideString<32>& comPort, Int32 baudRate, bool filterByArea, double upperLeftCornerLatitude, double upperLeftCornerLongitude, double bottomRightCornerLatitude, double bottomRightCornerLongitude, const FixedDBWideString<127>& aisProviderIPAddress, Int32 aisProviderPort, bool useLogin, Int32 aisProviderLoginPort, bool canSendAISMessage, const WideString& textMessageHeader, const WideString& urls, Int32 udpPort, Data::AisDeviceConnectionType connectionType, bool enableRefreshAidToNavigationIn30sec, bool enableAidToNavigationFromFile, const WideString& aidToNavigationHeader, bool sendingMMSI, Int32 sourceUpdateRate, bool enableRefreshStayingStillTargetIn30sec, const WideString& excludeSendAisBaseStation, const WideString& excludeSendAisA, bool enableSendBaseStationAlarms, const FixedDBWideString<127>& aisWebConfig, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisDeviceRawMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, bool isSent, const FixedDBWideString<127>& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceRawMessageInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindBooleanParameter( 4, &isSent );
        statement.BindFixedDBWideStringParameter( 5, message );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisDeviceRawMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, bool isSent, const FixedDBWideString<127>& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceRawMessageUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindBooleanParameter( 5, &isSent );
        statement.BindFixedDBWideStringParameter( 6, message );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisDeviceRawMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceRawMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisDeviceRawSentence( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, const WideString& sentence )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceRawSentenceInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindWideStringParameter( 4, sentence );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisDeviceRawSentence( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, const WideString& sentence )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceRawSentenceUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindWideStringParameter( 5, sentence );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisDeviceRawSentence( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceRawSentenceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAidToNavigationReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationalAidType navigationalAidType, const FixedDBWideString<127>& name, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Int32 timestamp, bool offPosition, Int32 regionalReserved, Data::Raim raim, bool virtualAid, bool assigned, Int32 spare, const FixedDBWideString<127>& nameExtension )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AidToNavigationReportMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAidToNavigationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationalAidType navigationalAidType, const FixedDBWideString<127>& name, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Int32 timestamp, bool offPosition, Int32 regionalReserved, Data::Raim raim, bool virtualAid, bool assigned, Int32 spare, const FixedDBWideString<127>& nameExtension )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AidToNavigationReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAidToNavigationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AidToNavigationReportMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, const FixedDBWideString<127>& text )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAddressedSafetyRelatedMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, const FixedDBWideString<127>& text )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAddressedSafetyRelatedMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAddressedSafetyRelatedMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisBaseStationReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& timestamp, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBaseStationReportMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisBaseStationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& timestamp, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBaseStationReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisBaseStationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBaseStationReportMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBinaryAcknowledgeMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBinaryAcknowledgeMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBinaryAcknowledgeMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisBinaryAddressedMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBinaryAddressedMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisBinaryAddressedMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBinaryAddressedMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisBinaryAddressedMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBinaryAddressedMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisBinaryBroadcastMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBinaryBroadcastMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisBinaryBroadcastMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBinaryBroadcastMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &spare );
        statement.BindInt32Parameter( 9, &designatedAreaCode );
        statement.BindInt32Parameter( 10, &functionalId );
        statement.BindWideStringParameter( 11, data );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisBinaryBroadcastMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisBinaryBroadcastMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisDataLinkManagementMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 offset1, Int32 reservedSlots1, Int32 timeout1, Int32 increment1, const DBInt32& offset2, const DBInt32& reservedSlots2, const DBInt32& timeout2, const DBInt32& increment2, const DBInt32& offset3, const DBInt32& reservedSlots3, const DBInt32& timeout3, const DBInt32& increment3, const DBInt32& offset4, const DBInt32& reservedSlots4, const DBInt32& timeout4, const DBInt32& increment4 )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDataLinkManagementMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisDataLinkManagementMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 offset1, Int32 reservedSlots1, Int32 timeout1, Int32 increment1, const DBInt32& offset2, const DBInt32& reservedSlots2, const DBInt32& timeout2, const DBInt32& increment2, const DBInt32& offset3, const DBInt32& reservedSlots3, const DBInt32& timeout3, const DBInt32& increment3, const DBInt32& offset4, const DBInt32& reservedSlots4, const DBInt32& timeout4, const DBInt32& increment4 )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDataLinkManagementMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisDataLinkManagementMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDataLinkManagementMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, const Guid& name, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Data::Raim raim, bool dataTerminalReady, bool assigned, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisExtendedClassBCsPositionReportMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, const Guid& name, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Data::Raim raim, bool dataTerminalReady, bool assigned, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisExtendedClassBCsPositionReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisExtendedClassBCsPositionReportMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisInterrogationMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const Guid& interrogatedMmsi, Data::AisMessageType firstMessageType, Int32 firstSlotOffset, const DBEnum<Data::AisMessageType>& secondMessageType, const DBInt32& secondSlotOffset, const DBGuid& secondStationInterrogationMmsi, const DBEnum<Data::AisMessageType>& secondStationFirstMessageType, const DBInt32& secondStationFirstSlotOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisInterrogationMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const Guid& interrogatedMmsi, Data::AisMessageType firstMessageType, Int32 firstSlotOffset, const DBEnum<Data::AisMessageType>& secondMessageType, const DBInt32& secondSlotOffset, const DBGuid& secondStationInterrogationMmsi, const DBEnum<Data::AisMessageType>& secondStationFirstMessageType, const DBInt32& secondStationFirstSlotOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisInterrogationMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisInterrogationMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportClassAAssignedScheduleMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportClassAAssignedScheduleMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportClassAAssignedScheduleMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisPositionReportClassAMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportClassAMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisPositionReportClassAMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportClassAMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisPositionReportClassAMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportClassAMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportClassAResponseToInterrogationMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportClassAResponseToInterrogationMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportClassAResponseToInterrogationMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::PositionAccuracy positionAccuracy, Data::Raim raim, Data::NavigationStatus navigationStatus, double longitude, double latitude, double speedOverGround, double courseOverGround, Data::GnssPositionStatus gnssPositionStatus, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportForLongRangeApplicationsMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::PositionAccuracy positionAccuracy, Data::Raim raim, Data::NavigationStatus navigationStatus, double longitude, double latitude, double speedOverGround, double courseOverGround, Data::GnssPositionStatus gnssPositionStatus, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportForLongRangeApplicationsMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisPositionReportForLongRangeApplicationsMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisSafetyRelatedAcknowledgmentMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisSafetyRelatedAcknowledgmentMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisSafetyRelatedAcknowledgmentMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, bool isCsUnit, bool hasDisplay, bool hasDscCapability, bool band, bool canAcceptMessage22, bool assigned, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStandardClassBCsPositionReportMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, bool isCsUnit, bool hasDisplay, bool hasDscCapability, bool band, bool canAcceptMessage22, bool assigned, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStandardClassBCsPositionReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStandardClassBCsPositionReportMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 altitude, Int32 speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, Int32 timestamp, Int32 reserved, bool dataTerminalReady, Int32 spare, bool assigned, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStandardSarAircraftPositionReportMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 altitude, Int32 speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, Int32 timestamp, Int32 reserved, bool dataTerminalReady, Int32 spare, bool assigned, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStandardSarAircraftPositionReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStandardSarAircraftPositionReportMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 aisVersion, const Guid& imoNumber, const Guid& callsign, const Guid& shipName, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, const DBDateTime& estimatedTimeOfArrival, double draught, const FixedDBWideString<127>& destination, bool dataTerminalReady, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticAndVoyageRelatedDataMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 aisVersion, const Guid& imoNumber, const Guid& callsign, const Guid& shipName, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, const DBDateTime& estimatedTimeOfArrival, double draught, const FixedDBWideString<127>& destination, bool dataTerminalReady, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticAndVoyageRelatedDataMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticAndVoyageRelatedDataMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisStaticDataReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticDataReportMessageInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &partNumber );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisStaticDataReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticDataReportMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &partNumber );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisStaticDataReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticDataReportMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisStaticDataReportPartAMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, const Guid& shipName, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticDataReportPartAMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &partNumber );
        statement.BindGuidParameter( 8, &shipName );
        statement.BindInt32Parameter( 9, &spare );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisStaticDataReportPartAMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, const Guid& shipName, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticDataReportPartAMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &partNumber );
        statement.BindGuidParameter( 9, &shipName );
        statement.BindInt32Parameter( 10, &spare );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisStaticDataReportPartAMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticDataReportPartAMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisStaticDataReportPartBMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, Data::ShipType shipType, const FixedDBWideString<127>& vendorId, Int32 unitModelCode, Int32 serialNumber, const Guid& callsign, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, const DBGuid& mothershipMmsi, Data::PositionFixType positionFixType, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticDataReportPartBMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisStaticDataReportPartBMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, Data::ShipType shipType, const FixedDBWideString<127>& vendorId, Int32 unitModelCode, Int32 serialNumber, const Guid& callsign, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, const DBGuid& mothershipMmsi, Data::PositionFixType positionFixType, Int32 spare )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticDataReportPartBMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisStaticDataReportPartBMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisStaticDataReportPartBMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare1, Int32 destinationMmsi, Int32 spare2 )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisUtcAndDateInquiryMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &aisDevice );
        statement.BindDateTimeParameter( 3, receivedTimestamp );
        statement.BindInt64Parameter( 4, &messageSequenceNumber );
        statement.BindInt32Parameter( 5, &repeat );
        statement.BindGuidParameter( 6, &mmsi );
        statement.BindInt32Parameter( 7, &spare1 );
        statement.BindInt32Parameter( 8, &destinationMmsi );
        statement.BindInt32Parameter( 9, &spare2 );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare1, Int32 destinationMmsi, Int32 spare2 )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisUtcAndDateInquiryMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &aisDevice );
        statement.BindDateTimeParameter( 4, receivedTimestamp );
        statement.BindInt64Parameter( 5, &messageSequenceNumber );
        statement.BindInt32Parameter( 6, &repeat );
        statement.BindGuidParameter( 7, &mmsi );
        statement.BindInt32Parameter( 8, &spare1 );
        statement.BindInt32Parameter( 9, &destinationMmsi );
        statement.BindInt32Parameter( 10, &spare2 );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisUtcAndDateInquiryMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisUtcAndDateResponseMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& datetime, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisUtcAndDateResponseMessageInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisUtcAndDateResponseMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& datetime, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisUtcAndDateResponseMessageUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisUtcAndDateResponseMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisUtcAndDateResponseMessageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAlarmStateChange( const ODBC::Connection& connection, Guid& id, const Guid& alarm, const DateTime& timestamp, Data::AlarmState state )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AlarmStateChangeInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &alarm );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &state );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAlarmStateChange( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& alarm, const DateTime& timestamp, Data::AlarmState state )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AlarmStateChangeUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &alarm );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &state );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAlarmStateChange( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AlarmStateChangeDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBaseStationType( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BaseStationTypeInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBaseStationType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BaseStationTypeUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBaseStationType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BaseStationTypeDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBinaryTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const Binary& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindBinaryParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBinaryTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const Binary& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindBinaryParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBinaryTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBookmark( const ODBC::Connection& connection, Guid& id, const Guid& view, const FixedDBWideString<127>& name, const DBDateTime& timestamp, double latitude, double longitude, double zoomLevel )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BookmarkInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &view );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &latitude );
        statement.BindDoubleParameter( 6, &longitude );
        statement.BindDoubleParameter( 7, &zoomLevel );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBookmark( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, const FixedDBWideString<127>& name, const DBDateTime& timestamp, double latitude, double longitude, double zoomLevel )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BookmarkUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &view );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindDoubleParameter( 7, &longitude );
        statement.BindDoubleParameter( 8, &zoomLevel );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBookmark( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BookmarkDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBooleanTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBBoolean & value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindBooleanParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBooleanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBBoolean & value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindBooleanParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBooleanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertByteTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBByte& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindByteParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBByte& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindByteParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommand( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandAbsoluteMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, Data::CameraPanTiltMode positionPanTiltMode, const DBDouble& panAngle, const DBDouble& tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, const DBDouble& focalLength, Data::CameraPanTiltMode speedPanTiltMode, const DBDouble& panSpeed, const DBDouble& tiltSpeed, Data::CameraFocalLengthMode speedFocalLengthMode, const DBDouble& zoomSpeed )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandAbsoluteMoveInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandAbsoluteMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, Data::CameraPanTiltMode positionPanTiltMode, const DBDouble& panAngle, const DBDouble& tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, const DBDouble& focalLength, Data::CameraPanTiltMode speedPanTiltMode, const DBDouble& panSpeed, const DBDouble& tiltSpeed, Data::CameraFocalLengthMode speedFocalLengthMode, const DBDouble& zoomSpeed )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandAbsoluteMoveUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandAbsoluteMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandAbsoluteMoveDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const DBDouble& x, const DBDouble& y, const DBDouble& z )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandAdjustPanTiltZoomInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindDoubleParameter( 7, x );
        statement.BindDoubleParameter( 8, y );
        statement.BindDoubleParameter( 9, z );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const DBDouble& x, const DBDouble& y, const DBDouble& z )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandAdjustPanTiltZoomUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindDoubleParameter( 8, x );
        statement.BindDoubleParameter( 9, y );
        statement.BindDoubleParameter( 10, z );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandAdjustPanTiltZoomDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandContinuousMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panVelocity, const DBDouble& tiltVelocity, const DBDouble& zoomVelocity, const DBTimeSpan& duration )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandContinuousMoveInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandContinuousMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panVelocity, const DBDouble& tiltVelocity, const DBDouble& zoomVelocity, const DBTimeSpan& duration )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandContinuousMoveUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandContinuousMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandContinuousMoveDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandGeoMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, double latitude, double longitude, const DBDouble& altitude, const DBDouble& viewportWidth, const DBDouble& viewportHeight )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandGeoMoveInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandGeoMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, double latitude, double longitude, const DBDouble& altitude, const DBDouble& viewportWidth, const DBDouble& viewportHeight )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandGeoMoveUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandGeoMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandGeoMoveDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandRelativeMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panAngle, const DBDouble& tiltAngle, const DBDouble& focalLength, const DBDouble& panSpeed, const DBDouble& tiltSpeed, const DBDouble& zoomSpeed )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandRelativeMoveInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandRelativeMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panAngle, const DBDouble& tiltAngle, const DBDouble& focalLength, const DBDouble& panSpeed, const DBDouble& tiltSpeed, const DBDouble& zoomSpeed )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandRelativeMoveUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandRelativeMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandRelativeMoveDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandReleasePTZOwnershipInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandReleasePTZOwnershipUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandReleasePTZOwnershipDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandRequestPTZOwnershipInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandRequestPTZOwnershipUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandRequestPTZOwnershipDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandSetAutoFocus( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetAutoFocusInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &enabled );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandSetAutoFocus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetAutoFocusUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &enabled );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandSetAutoFocus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetAutoFocusDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetBlackAndWhiteInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &enabled );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetBlackAndWhiteUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &enabled );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetBlackAndWhiteDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandSetFollowed( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const Guid& trackId, Data::CameraFollowReason reason )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetFollowedInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindGuidParameter( 7, &trackId );
        statement.BindEnumParameter( 8, &reason );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandSetFollowed( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const Guid& trackId, Data::CameraFollowReason reason )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetFollowedUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindGuidParameter( 8, &trackId );
        statement.BindEnumParameter( 9, &reason );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandSetFollowed( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetFollowedDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetInfraRedLampInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &enabled );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetInfraRedLampUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &enabled );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetInfraRedLampDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandSetWasher( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetWasherInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &enabled );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandSetWasher( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetWasherUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &enabled );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandSetWasher( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetWasherDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandSetWiper( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetWiperInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &enabled );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandSetWiper( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetWiperUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &enabled );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandSetWiper( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandSetWiperDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandStop( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool panTilt, bool zoom )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandStopInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.BindBooleanParameter( 7, &panTilt );
        statement.BindBooleanParameter( 8, &zoom );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandStop( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool panTilt, bool zoom )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandStopUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.BindBooleanParameter( 8, &panTilt );
        statement.BindBooleanParameter( 9, &zoom );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandStop( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandStopDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, double panAngle, double tiltAngle, double focalLength )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandReplyInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.BindDoubleParameter( 7, &panAngle );
        statement.BindDoubleParameter( 8, &tiltAngle );
        statement.BindDoubleParameter( 9, &focalLength );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, double panAngle, double tiltAngle, double focalLength )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.BindDoubleParameter( 8, &panAngle );
        statement.BindDoubleParameter( 9, &tiltAngle );
        statement.BindDoubleParameter( 10, &focalLength );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraCommandReplyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::CameraControlProtocol cameraControlProtocol, const FixedDBWideString<127>& cameraAddress, Int32 cameraPort, const FixedDBWideString<127>& cameraControlAddress, Int32 cameraControlPort, const FixedDBWideString<127>& cameraUserName, const FixedDBWideString<127>& cameraPassword, bool useRtspUriOverride, const FixedDBWideString<127>& rtspUriOverride, double latitude, double longitude, double altitude, bool useRelativePosition, double azimuthFromGPS, double distanceFromGPS, Data::CameraPanTiltMode panTiltMode, double minTiltAngle, double maxTiltAngle, double minTiltScaleAngle, double maxTiltScaleAngle, bool useReverseTiltAngle, bool useReverseNormalizedTiltAngle, double minTiltVelocity, double maxTiltVelocity, double minTiltSpeed, double maxTiltSpeed, double minPanAngle, double maxPanAngle, double minPanScaleAngle, double maxPanScaleAngle, bool useReversePanAngle, bool useReverseNormalizedPanAngle, double minPanVelocity, double maxPanVelocity, double minPanSpeed, double maxPanSpeed, Data::CameraFocalLengthMode focalLengthMode, double minFocalLength, double maxFocalLength, double minFocalLengthScale, double maxFocalLengthScale, double minZoomVelocity, double maxZoomVelocity, double minZoomSpeed, double maxZoomSpeed, double imageSensorWidth, double imageSensorHeight, double homePanAngle, double homeTiltAngle, double homeFocalLength, double panOffset, double tiltOffset, double aimAltitude, double minimumTargetWidth, const TimeSpan& targetLockTimeout, const TimeSpan& updateStatusInterval, const TimeSpan& readTimeout, const TimeSpan& moveCommandStatusDelay, const FixedDBWideString<127>& ptzProfileName, const FixedDBWideString<127>& ptzConfigurationToken, const FixedDBWideString<127>& videoSourceToken )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::CameraControlProtocol cameraControlProtocol, const FixedDBWideString<127>& cameraAddress, Int32 cameraPort, const FixedDBWideString<127>& cameraControlAddress, Int32 cameraControlPort, const FixedDBWideString<127>& cameraUserName, const FixedDBWideString<127>& cameraPassword, bool useRtspUriOverride, const FixedDBWideString<127>& rtspUriOverride, double latitude, double longitude, double altitude, bool useRelativePosition, double azimuthFromGPS, double distanceFromGPS, Data::CameraPanTiltMode panTiltMode, double minTiltAngle, double maxTiltAngle, double minTiltScaleAngle, double maxTiltScaleAngle, bool useReverseTiltAngle, bool useReverseNormalizedTiltAngle, double minTiltVelocity, double maxTiltVelocity, double minTiltSpeed, double maxTiltSpeed, double minPanAngle, double maxPanAngle, double minPanScaleAngle, double maxPanScaleAngle, bool useReversePanAngle, bool useReverseNormalizedPanAngle, double minPanVelocity, double maxPanVelocity, double minPanSpeed, double maxPanSpeed, Data::CameraFocalLengthMode focalLengthMode, double minFocalLength, double maxFocalLength, double minFocalLengthScale, double maxFocalLengthScale, double minZoomVelocity, double maxZoomVelocity, double minZoomSpeed, double maxZoomSpeed, double imageSensorWidth, double imageSensorHeight, double homePanAngle, double homeTiltAngle, double homeFocalLength, double panOffset, double tiltOffset, double aimAltitude, double minimumTargetWidth, const TimeSpan& targetLockTimeout, const TimeSpan& updateStatusInterval, const TimeSpan& readTimeout, const TimeSpan& moveCommandStatusDelay, const FixedDBWideString<127>& ptzProfileName, const FixedDBWideString<127>& ptzConfigurationToken, const FixedDBWideString<127>& videoSourceToken )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraPanCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraPanCalibrationInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraPanCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraPanCalibrationUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraPanCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraPanCalibrationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraPanCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& panCalibration, double panAngle, double panOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraPanCalibrationValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &panCalibration );
        statement.BindDoubleParameter( 3, &panAngle );
        statement.BindDoubleParameter( 4, &panOffset );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraPanCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& panCalibration, double panAngle, double panOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraPanCalibrationValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &panCalibration );
        statement.BindDoubleParameter( 4, &panAngle );
        statement.BindDoubleParameter( 5, &panOffset );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraPanCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraPanCalibrationValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraStatus( const ODBC::Connection& connection, Guid& id, const Guid& camera, const Guid& track, const DateTime& timestamp, Data::CameraPanTiltMode positionPanTiltMode, double panAngle, double tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, double focalLength, Data::CameraMoveStatus panTiltMoveStatus, Data::CameraMoveStatus zoomMoveStatus, Data::CameraPanTiltMode velocityPanTiltMode, const DBDouble& panVelocity, const DBDouble& tiltVelocity, Data::CameraFocalLengthMode velocityFocalLengthMode, const DBDouble& zoomVelocity, Data::CameraFeatures activeFeatures, const WideString& error )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraStatusInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const Guid& track, const DateTime& timestamp, Data::CameraPanTiltMode positionPanTiltMode, double panAngle, double tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, double focalLength, Data::CameraMoveStatus panTiltMoveStatus, Data::CameraMoveStatus zoomMoveStatus, Data::CameraPanTiltMode velocityPanTiltMode, const DBDouble& panVelocity, const DBDouble& tiltVelocity, Data::CameraFocalLengthMode velocityFocalLengthMode, const DBDouble& zoomVelocity, Data::CameraFeatures activeFeatures, const WideString& error )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraStatusUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraStatusDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraTiltCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraTiltCalibrationInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraTiltCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraTiltCalibrationUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraTiltCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraTiltCalibrationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraTiltCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& tiltCalibration, double panAngle, double tiltOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraTiltCalibrationValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &tiltCalibration );
        statement.BindDoubleParameter( 3, &panAngle );
        statement.BindDoubleParameter( 4, &tiltOffset );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraTiltCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tiltCalibration, double panAngle, double tiltOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraTiltCalibrationValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &tiltCalibration );
        statement.BindDoubleParameter( 4, &panAngle );
        statement.BindDoubleParameter( 5, &tiltOffset );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraTiltCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraTiltCalibrationValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraZoomCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraZoomCalibrationInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &camera );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraZoomCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraZoomCalibrationUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraZoomCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraZoomCalibrationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraZoomCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& zoomCalibration, double focalLength, double focalLengthOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraZoomCalibrationValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &zoomCalibration );
        statement.BindDoubleParameter( 3, &focalLength );
        statement.BindDoubleParameter( 4, &focalLengthOffset );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraZoomCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zoomCalibration, double focalLength, double focalLengthOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraZoomCalibrationValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &zoomCalibration );
        statement.BindDoubleParameter( 4, &focalLength );
        statement.BindDoubleParameter( 5, &focalLengthOffset );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraZoomCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraZoomCalibrationValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCatalog( const ODBC::Connection& connection, Guid& id, const Guid& catalog, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CatalogInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCatalog( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CatalogUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCatalog( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CatalogDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertElement( const ODBC::Connection& connection, Guid& id, const Guid& catalog, const FixedDBWideString<127>& name, const Guid& elementType )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ElementInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &elementType );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateElement( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, const FixedDBWideString<127>& name, const Guid& elementType )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ElementUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindGuidParameter( 5, &elementType );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteElement( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ElementDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCollectionInfo( const ODBC::Connection& connection, Guid& id, Int64 count )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CollectionInfoInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &count );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCollectionInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 count )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CollectionInfoUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindInt64Parameter( 3, &count );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCollectionInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CollectionInfoDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCountry( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, Int32 code, const FixedDBWideString<2>& alpha2, const FixedDBWideString<3>& alpha3 )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CountryInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindInt32Parameter( 3, &code );
        statement.BindFixedDBWideStringParameter( 4, alpha2 );
        statement.BindFixedDBWideStringParameter( 5, alpha3 );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCountry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, Int32 code, const FixedDBWideString<2>& alpha2, const FixedDBWideString<3>& alpha3 )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CountryUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindInt32Parameter( 4, &code );
        statement.BindFixedDBWideStringParameter( 5, alpha2 );
        statement.BindFixedDBWideStringParameter( 6, alpha3 );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCountry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CountryDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCursorInfo( const ODBC::Connection& connection, Guid& id, Int32 typeCode )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CursorInfoInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt32Parameter( 2, &typeCode );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCursorInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 typeCode )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CursorInfoUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindInt32Parameter( 3, &typeCode );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCursorInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CursorInfoDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDateTimeTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDateTime& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDateTimeParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDateTimeTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDateTime& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDateTimeParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDateTimeTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDeviceHost( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DeviceHostInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDeviceHost( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DeviceHostUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDeviceHost( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DeviceHostDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDeviceHostConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& host, const DateTime& timestamp, const FixedDBWideString<127>& hostname, Int32 port, const FixedDBWideString<127>& queueName )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DeviceHostConfigurationInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindFixedDBWideStringParameter( 4, hostname );
        statement.BindInt32Parameter( 5, &port );
        statement.BindFixedDBWideStringParameter( 6, queueName );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDeviceHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const DateTime& timestamp, const FixedDBWideString<127>& hostname, Int32 port, const FixedDBWideString<127>& queueName )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DeviceHostConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &host );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindFixedDBWideStringParameter( 5, hostname );
        statement.BindInt32Parameter( 6, &port );
        statement.BindFixedDBWideStringParameter( 7, queueName );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDeviceHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DeviceHostConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDoubleTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDoubleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDoubleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertFacilityType( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [FacilityTypeInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateFacilityType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [FacilityTypeUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteFacilityType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [FacilityTypeDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition2DTimeseriesValueInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, latitude );
        statement.BindDoubleParameter( 5, longitude );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition2DTimeseriesValueUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, latitude );
        statement.BindDoubleParameter( 6, longitude );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition2DTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude, const DBDouble& altitude )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition3DTimeseriesValueInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, latitude );
        statement.BindDoubleParameter( 5, longitude );
        statement.BindDoubleParameter( 6, altitude );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude, const DBDouble& altitude )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition3DTimeseriesValueUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, latitude );
        statement.BindDoubleParameter( 6, longitude );
        statement.BindDoubleParameter( 7, altitude );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition3DTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGNSSDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gNSSDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGNSSDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &gNSSDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGNSSDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceCommandDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGNSSDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gNSSDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGNSSDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &gNSSDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGNSSDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceCommandReplyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGNSSDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, double defaultLatitude, double defaultLongitude, double defaultAltitude, double latitudeOffset, double longitudeOffset, double altitudeOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gNSSDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, &defaultLatitude );
        statement.BindDoubleParameter( 5, &defaultLongitude );
        statement.BindDoubleParameter( 6, &defaultAltitude );
        statement.BindDoubleParameter( 7, &latitudeOffset );
        statement.BindDoubleParameter( 8, &longitudeOffset );
        statement.BindDoubleParameter( 9, &altitudeOffset );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGNSSDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, double defaultLatitude, double defaultLongitude, double defaultAltitude, double latitudeOffset, double longitudeOffset, double altitudeOffset )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &gNSSDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &defaultLatitude );
        statement.BindDoubleParameter( 6, &defaultLongitude );
        statement.BindDoubleParameter( 7, &defaultAltitude );
        statement.BindDoubleParameter( 8, &latitudeOffset );
        statement.BindDoubleParameter( 9, &longitudeOffset );
        statement.BindDoubleParameter( 10, &altitudeOffset );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGNSSDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGuidTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBGuid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGuidTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBGuid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGuidTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gyroDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &gyroDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceCommandDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gyroDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &gyroDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceCommandReplyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, double defaultHeadingTrueNorth, double defaultMagneticTrueNorth, double headingTrueNorthOffset, double headingMagneticNorthOffset, const FixedDBWideString<64>& pitchTransducerName, const FixedDBWideString<64>& rollTransducerName )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &gyroDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, &defaultHeadingTrueNorth );
        statement.BindDoubleParameter( 5, &defaultMagneticTrueNorth );
        statement.BindDoubleParameter( 6, &headingTrueNorthOffset );
        statement.BindDoubleParameter( 7, &headingMagneticNorthOffset );
        statement.BindFixedDBWideStringParameter( 8, pitchTransducerName );
        statement.BindFixedDBWideStringParameter( 9, rollTransducerName );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, double defaultHeadingTrueNorth, double defaultMagneticTrueNorth, double headingTrueNorthOffset, double headingMagneticNorthOffset, const FixedDBWideString<64>& pitchTransducerName, const FixedDBWideString<64>& rollTransducerName )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &gyroDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &defaultHeadingTrueNorth );
        statement.BindDoubleParameter( 6, &defaultMagneticTrueNorth );
        statement.BindDoubleParameter( 7, &headingTrueNorthOffset );
        statement.BindDoubleParameter( 8, &headingMagneticNorthOffset );
        statement.BindFixedDBWideStringParameter( 9, pitchTransducerName );
        statement.BindFixedDBWideStringParameter( 10, rollTransducerName );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCallsign( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CallsignInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, identifier );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCallsign( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CallsignUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, identifier );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCallsign( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CallsignDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, Guid& id, Int64 identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [InternationalMaritimeOrganizationNumberInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &identifier );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [InternationalMaritimeOrganizationNumberUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindInt64Parameter( 3, &identifier );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [InternationalMaritimeOrganizationNumberDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMaritimeMobileServiceIdentity( const ODBC::Connection& connection, Guid& id, Int64 identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MaritimeMobileServiceIdentityInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &identifier );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMaritimeMobileServiceIdentity( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 identifier )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MaritimeMobileServiceIdentityUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindInt64Parameter( 3, &identifier );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMaritimeMobileServiceIdentity( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MaritimeMobileServiceIdentityDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertName( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& text )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [NameInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, text );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateName( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& text )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [NameUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, text );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteName( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [NameDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt16TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt16& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt16Parameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt16& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt16Parameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt32TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt32& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt32& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt64TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt64Parameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt64Parameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBaseStation( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BaseStationInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &type );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBaseStation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BaseStationUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &type );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBaseStation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BaseStationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCameraDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraDeviceInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCameraDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraDeviceUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCameraDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CameraDeviceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGNSSDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& altitudeTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.BindGuidParameter( 6, &latitudeTimeseries );
        statement.BindGuidParameter( 7, &longitudeTimeseries );
        statement.BindGuidParameter( 8, &altitudeTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGNSSDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& altitudeTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.BindGuidParameter( 7, &latitudeTimeseries );
        statement.BindGuidParameter( 8, &longitudeTimeseries );
        statement.BindGuidParameter( 9, &altitudeTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGNSSDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSDeviceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries, const Guid& headingTrueNorthTimeseries, const Guid& headingMagneticNorthTimeseries, const Guid& pitchTimeseries, const Guid& rateOfTurnTimeseries, const Guid& rollTimeseries, const Guid& courseTimeseries, const Guid& speedTimeseries, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries, const Guid& headingTrueNorthTimeseries, const Guid& headingMagneticNorthTimeseries, const Guid& pitchTimeseries, const Guid& rateOfTurnTimeseries, const Guid& rollTimeseries, const Guid& courseTimeseries, const Guid& speedTimeseries, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroDeviceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLineInputDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLineInputDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLineInputDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertOilSpillDetectorDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorDeviceInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateOilSpillDetectorDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorDeviceUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteOilSpillDetectorDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorDeviceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadioDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioDeviceInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadioDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioDeviceUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadioDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioDeviceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadomeDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries, const DBGuid& radar, const Guid& pressureTimeseries, const Guid& temperatureTimeseries, const Guid& dewPointTimeseries, const Guid& statusTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeDeviceInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadomeDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries, const DBGuid& radar, const Guid& pressureTimeseries, const Guid& temperatureTimeseries, const Guid& dewPointTimeseries, const Guid& statusTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeDeviceUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.BindGuidParameter( 7, radar );
        statement.BindGuidParameter( 8, &pressureTimeseries );
        statement.BindGuidParameter( 9, &temperatureTimeseries );
        statement.BindGuidParameter( 10, &dewPointTimeseries );
        statement.BindGuidParameter( 11, &statusTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadomeDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeDeviceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &host );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &host );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisDeviceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries, const Guid& saveSettingsTimeseries, const Guid& powerOnTimeseries, const Guid& trackingOnTimeseries, const Guid& radarPulseTimeseries, const Guid& tuningTimeseries, const Guid& blankSector1Timeseries, const Guid& sector1StartTimeseries, const Guid& sector1EndTimeseries, const Guid& blankSector2Timeseries, const Guid& sector2StartTimeseries, const Guid& sector2EndTimeseries, const Guid& enableAutomaticFrequencyControlTimeseries, const Guid& azimuthOffsetTimeseries, const Guid& enableSensitivityTimeControlTimeseries, const Guid& automaticSensitivityTimeControlTimeseries, const Guid& sensitivityTimeControlLevelTimeseries, const Guid& enableFastTimeConstantTimeseries, const Guid& fastTimeConstantLevelTimeseries, const Guid& fastTimeConstantModeTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const DBGuid& radome, const DBGuid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarDeviceInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries, const Guid& saveSettingsTimeseries, const Guid& powerOnTimeseries, const Guid& trackingOnTimeseries, const Guid& radarPulseTimeseries, const Guid& tuningTimeseries, const Guid& blankSector1Timeseries, const Guid& sector1StartTimeseries, const Guid& sector1EndTimeseries, const Guid& blankSector2Timeseries, const Guid& sector2StartTimeseries, const Guid& sector2EndTimeseries, const Guid& enableAutomaticFrequencyControlTimeseries, const Guid& azimuthOffsetTimeseries, const Guid& enableSensitivityTimeControlTimeseries, const Guid& automaticSensitivityTimeControlTimeseries, const Guid& sensitivityTimeControlLevelTimeseries, const Guid& enableFastTimeConstantTimeseries, const Guid& fastTimeConstantLevelTimeseries, const Guid& fastTimeConstantModeTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const DBGuid& radome, const DBGuid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarDeviceUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarDeviceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries, const Guid& barometricPressureTimeseries, const Guid& airTemperatureTimeseries, const Guid& waterTemperatureTimeseries, const Guid& relativeHumidityTimeseries, const Guid& absoluteHumidityTimeseries, const Guid& dewPointTimeseries, const Guid& windDirectionTimeseries, const Guid& windSpeedTimeseries, const Guid& gyro )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationDeviceInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const Guid& enabledTimeseries, const Guid& barometricPressureTimeseries, const Guid& airTemperatureTimeseries, const Guid& waterTemperatureTimeseries, const Guid& relativeHumidityTimeseries, const Guid& absoluteHumidityTimeseries, const Guid& dewPointTimeseries, const Guid& windDirectionTimeseries, const Guid& windSpeedTimeseries, const Guid& gyro )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationDeviceUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationDeviceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertFacility( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const Guid& type, double longitude, double latitude, double altitude )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [FacilityInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &type );
        statement.BindDoubleParameter( 4, &longitude );
        statement.BindDoubleParameter( 5, &latitude );
        statement.BindDoubleParameter( 6, &altitude );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateFacility( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const Guid& type, double longitude, double latitude, double altitude )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [FacilityUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &type );
        statement.BindDoubleParameter( 5, &longitude );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindDoubleParameter( 7, &altitude );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteFacility( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [FacilityDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAircraft( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AircraftInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &type );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAircraft( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AircraftUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &type );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAircraft( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AircraftDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisAidToNavigation( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const Guid& mMSI, Data::NavigationalAidType navigationalAidType, const Guid& position, bool isVirtual, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& offPositionTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAidToNavigationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisAidToNavigation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const Guid& mMSI, Data::NavigationalAidType navigationalAidType, const Guid& position, bool isVirtual, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& offPositionTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAidToNavigationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisAidToNavigation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAidToNavigationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertVehicle( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VehicleInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &type );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateVehicle( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const Guid& type )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VehicleUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &type );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteVehicle( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VehicleDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertVessel( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const Guid& type, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& draughtTimeseries, const Guid& personsOnBoardTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &type );
        statement.BindInt32Parameter( 4, &toBow );
        statement.BindInt32Parameter( 5, &toStern );
        statement.BindInt32Parameter( 6, &toPort );
        statement.BindInt32Parameter( 7, &toStarboard );
        statement.BindGuidParameter( 8, &draughtTimeseries );
        statement.BindGuidParameter( 9, &personsOnBoardTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateVessel( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const Guid& type, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& draughtTimeseries, const Guid& personsOnBoardTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &type );
        statement.BindInt32Parameter( 5, &toBow );
        statement.BindInt32Parameter( 6, &toStern );
        statement.BindInt32Parameter( 7, &toPort );
        statement.BindInt32Parameter( 8, &toStarboard );
        statement.BindGuidParameter( 9, &draughtTimeseries );
        statement.BindGuidParameter( 10, &personsOnBoardTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteVessel( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertItemIdentityLink( const ODBC::Connection& connection, Guid& id, const Guid& item, const Guid& identity, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ItemIdentityLinkInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &item );
        statement.BindGuidParameter( 3, &identity );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateItemIdentityLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, const Guid& identity, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ItemIdentityLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &item );
        statement.BindGuidParameter( 4, &identity );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteItemIdentityLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ItemIdentityLinkDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertItemParentChildLink( const ODBC::Connection& connection, Guid& id, const Guid& parent, const Guid& child, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ItemParentChildLinkInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &parent );
        statement.BindGuidParameter( 3, &child );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateItemParentChildLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& parent, const Guid& child, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ItemParentChildLinkUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &parent );
        statement.BindGuidParameter( 4, &child );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteItemParentChildLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ItemParentChildLinkDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLineInputDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &lineInputDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLineInputDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &lineInputDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLineInputDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceCommandDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLineInputDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &lineInputDevice );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLineInputDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &lineInputDevice );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLineInputDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceCommandReplyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLineInputDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages, bool nMEA, bool strictNMEA, Data::LineInputDeviceConnectionType connectionType, Int32 udpReceivePort, const FixedDBWideString<127>& udpSendHostname, Int32 udpSendPort, const FixedDBWideString<127>& tcpHostname, Int32 tcpPort, bool useHttpLogin, const FixedDBWideString<127>& loginHostname, Int32 loginPort, const FixedDBWideString<127>& userName, const FixedDBWideString<127>& password, const FixedDBWideString<127>& comPort, Int32 baudRate, Int32 dataBits, bool discardNull, bool dtrEnable, Data::Handshake handshake, const FixedDBWideString<127>& newLine, Data::Parity parity, Byte parityReplace, Int32 readBufferSize, const TimeSpan& readTimeout, Int32 receivedBytesThreshold, bool rtsEnable, Data::StopBits stopBits, Int32 writeBufferSize, const TimeSpan& writeTimeout, const FixedDBWideString<127>& pairedComPort )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLineInputDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages, bool nMEA, bool strictNMEA, Data::LineInputDeviceConnectionType connectionType, Int32 udpReceivePort, const FixedDBWideString<127>& udpSendHostname, Int32 udpSendPort, const FixedDBWideString<127>& tcpHostname, Int32 tcpPort, bool useHttpLogin, const FixedDBWideString<127>& loginHostname, Int32 loginPort, const FixedDBWideString<127>& userName, const FixedDBWideString<127>& password, const FixedDBWideString<127>& comPort, Int32 baudRate, Int32 dataBits, bool discardNull, bool dtrEnable, Data::Handshake handshake, const FixedDBWideString<127>& newLine, Data::Parity parity, Byte parityReplace, Int32 readBufferSize, const TimeSpan& readTimeout, Int32 receivedBytesThreshold, bool rtsEnable, Data::StopBits stopBits, Int32 writeBufferSize, const TimeSpan& writeTimeout, const FixedDBWideString<127>& pairedComPort )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLineInputDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputDeviceConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLineInputMessageRouting( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const FixedDBWideString<127>& type )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputMessageRoutingInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &lineInputDevice );
        statement.BindFixedDBWideStringParameter( 3, type );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLineInputMessageRouting( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const FixedDBWideString<127>& type )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputMessageRoutingUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &lineInputDevice );
        statement.BindFixedDBWideStringParameter( 4, type );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLineInputMessageRouting( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputMessageRoutingDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLineInputMessageRoutingDestination( const ODBC::Connection& connection, Guid& id, const Guid& routing, const Guid& listener )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputMessageRoutingDestinationInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &routing );
        statement.BindGuidParameter( 3, &listener );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLineInputMessageRoutingDestination( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& routing, const Guid& listener )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputMessageRoutingDestinationUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &routing );
        statement.BindGuidParameter( 4, &listener );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLineInputMessageRoutingDestination( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputMessageRoutingDestinationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLineInputWhiteListEntry( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const FixedDBWideString<128>& hostName, Int32 port )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputWhiteListEntryInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &lineInputDevice );
        statement.BindFixedDBWideStringParameter( 3, hostName );
        statement.BindInt32Parameter( 4, &port );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLineInputWhiteListEntry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const FixedDBWideString<128>& hostName, Int32 port )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputWhiteListEntryUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &lineInputDevice );
        statement.BindFixedDBWideStringParameter( 4, hostName );
        statement.BindInt32Parameter( 5, &port );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLineInputWhiteListEntry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LineInputWhiteListEntryDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLogApplication( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogApplicationInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindWideStringParameter( 3, description );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLogApplication( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogApplicationUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLogApplication( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogApplicationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLogApplicationConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& application, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogApplicationConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLogApplicationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& application, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogApplicationConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLogApplicationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogApplicationConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLogHost( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& computerName, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogHostInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, computerName );
        statement.BindWideStringParameter( 3, description );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLogHost( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& computerName, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogHostUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, computerName );
        statement.BindWideStringParameter( 4, description );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLogHost( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogHostDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLogHostConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& host, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogHostConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLogHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogHostConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLogHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogHostConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLogLocation( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<260>& fileName, Int32 lineNumber, const WideString& namespace__, const WideString& className, const FixedDBWideString<255>& methodName )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogLocationInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, fileName );
        statement.BindInt32Parameter( 3, &lineNumber );
        statement.BindWideStringParameter( 4, namespace__ );
        statement.BindWideStringParameter( 5, className );
        statement.BindFixedDBWideStringParameter( 6, methodName );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLogLocation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<260>& fileName, Int32 lineNumber, const WideString& namespace__, const WideString& className, const FixedDBWideString<255>& methodName )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogLocationUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, fileName );
        statement.BindInt32Parameter( 4, &lineNumber );
        statement.BindWideStringParameter( 5, namespace__ );
        statement.BindWideStringParameter( 6, className );
        statement.BindFixedDBWideStringParameter( 7, methodName );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLogLocation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogLocationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLogProcess( const ODBC::Connection& connection, Guid& id, const Guid& application, const Guid& host, const DateTime& started, const DBDateTime& stopped, Int64 processId, const WideString& path, const FixedDBWideString<127>& identity )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogProcessInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &application );
        statement.BindGuidParameter( 3, &host );
        statement.BindDateTimeParameter( 4, started );
        statement.BindDateTimeParameter( 5, stopped );
        statement.BindInt64Parameter( 6, &processId );
        statement.BindWideStringParameter( 7, path );
        statement.BindFixedDBWideStringParameter( 8, identity );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLogProcess( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& application, const Guid& host, const DateTime& started, const DBDateTime& stopped, Int64 processId, const WideString& path, const FixedDBWideString<127>& identity )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogProcessUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &application );
        statement.BindGuidParameter( 4, &host );
        statement.BindDateTimeParameter( 5, started );
        statement.BindDateTimeParameter( 6, stopped );
        statement.BindInt64Parameter( 7, &processId );
        statement.BindWideStringParameter( 8, path );
        statement.BindFixedDBWideStringParameter( 9, identity );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLogProcess( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogProcessDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLogRecord( const ODBC::Connection& connection, Guid& id, const Guid& thread, Int64 sequenceNumber, Data::LogLevel level, const DateTime& timestamp, Int32 depth, const Guid& location, const WideString& message, const WideString& exceptionString, const Binary& propertiesData )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogRecordInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLogRecord( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& thread, Int64 sequenceNumber, Data::LogLevel level, const DateTime& timestamp, Int32 depth, const Guid& location, const WideString& message, const WideString& exceptionString, const Binary& propertiesData )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogRecordUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &thread );
        statement.BindInt64Parameter( 4, &sequenceNumber );
        statement.BindEnumParameter( 5, &level );
        statement.BindDateTimeParameter( 6, timestamp );
        statement.BindInt32Parameter( 7, &depth );
        statement.BindGuidParameter( 8, &location );
        statement.BindWideStringParameter( 9, message );
        statement.BindWideStringParameter( 10, exceptionString );
        statement.BindBinaryParameter( 11, propertiesData );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLogRecord( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogRecordDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLogThread( const ODBC::Connection& connection, Guid& id, const Guid& process, const DateTime& started, const DBDateTime& stopped, Int64 threadId, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogThreadInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &process );
        statement.BindDateTimeParameter( 3, started );
        statement.BindDateTimeParameter( 4, stopped );
        statement.BindInt64Parameter( 5, &threadId );
        statement.BindFixedDBWideStringParameter( 6, name );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLogThread( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& process, const DateTime& started, const DBDateTime& stopped, Int64 threadId, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogThreadUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &process );
        statement.BindDateTimeParameter( 4, started );
        statement.BindDateTimeParameter( 5, stopped );
        statement.BindInt64Parameter( 6, &threadId );
        statement.BindFixedDBWideStringParameter( 7, name );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLogThread( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogThreadDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertLogTraceEntry( const ODBC::Connection& connection, Guid& id, const Guid& thread, Int64 sequenceNumber, const Guid& location, Int32 depth, const DateTime& entered, const DBDateTime& ended )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogTraceEntryInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &thread );
        statement.BindInt64Parameter( 3, &sequenceNumber );
        statement.BindGuidParameter( 4, &location );
        statement.BindInt32Parameter( 5, &depth );
        statement.BindDateTimeParameter( 6, entered );
        statement.BindDateTimeParameter( 7, ended );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateLogTraceEntry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& thread, Int64 sequenceNumber, const Guid& location, Int32 depth, const DateTime& entered, const DBDateTime& ended )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogTraceEntryUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &thread );
        statement.BindInt64Parameter( 4, &sequenceNumber );
        statement.BindGuidParameter( 5, &location );
        statement.BindInt32Parameter( 6, &depth );
        statement.BindDateTimeParameter( 7, entered );
        statement.BindDateTimeParameter( 8, ended );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteLogTraceEntry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [LogTraceEntryDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMapElement( const ODBC::Connection& connection, Guid& id, const Guid& item, Data::MapElementType elementType, double latitude, double longitude, double angle, double left, double top, double width, double height, const FixedDBWideString<127>& label, const Binary& data )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MapElementInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMapElement( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, Data::MapElementType elementType, double latitude, double longitude, double angle, double left, double top, double width, double height, const FixedDBWideString<127>& label, const Binary& data )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MapElementUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMapElement( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MapElementDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMapInfo( const ODBC::Connection& connection, Guid& id, Int32 scale, double latitude, double longitude, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, const Binary& image )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MapInfoInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt32Parameter( 2, &scale );
        statement.BindDoubleParameter( 3, &latitude );
        statement.BindDoubleParameter( 4, &longitude );
        statement.BindDoubleParameter( 5, &northWestLatitude );
        statement.BindDoubleParameter( 6, &northWestLongitude );
        statement.BindDoubleParameter( 7, &southEastLatitude );
        statement.BindDoubleParameter( 8, &southEastLongitude );
        statement.BindBinaryParameter( 9, image );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMapInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 scale, double latitude, double longitude, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, const Binary& image )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MapInfoUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindInt32Parameter( 3, &scale );
        statement.BindDoubleParameter( 4, &latitude );
        statement.BindDoubleParameter( 5, &longitude );
        statement.BindDoubleParameter( 6, &northWestLatitude );
        statement.BindDoubleParameter( 7, &northWestLongitude );
        statement.BindDoubleParameter( 8, &southEastLatitude );
        statement.BindDoubleParameter( 9, &southEastLongitude );
        statement.BindBinaryParameter( 10, image );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMapInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MapInfoDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMapServiceOptions( const ODBC::Connection& connection, Guid& id, const DateTime& timestamp, const FixedDBWideString<127>& ipAddress, Int32 port, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MapServiceOptionsInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindDateTimeParameter( 2, timestamp );
        statement.BindFixedDBWideStringParameter( 3, ipAddress );
        statement.BindInt32Parameter( 4, &port );
        statement.BindDoubleParameter( 5, &imageScaleFactorX );
        statement.BindDoubleParameter( 6, &imageOffsetX );
        statement.BindDoubleParameter( 7, &imageScaleFactorY );
        statement.BindDoubleParameter( 8, &imageOffsetY );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMapServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DateTime& timestamp, const FixedDBWideString<127>& ipAddress, Int32 port, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MapServiceOptionsUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindFixedDBWideStringParameter( 4, ipAddress );
        statement.BindInt32Parameter( 5, &port );
        statement.BindDoubleParameter( 6, &imageScaleFactorX );
        statement.BindDoubleParameter( 7, &imageOffsetX );
        statement.BindDoubleParameter( 8, &imageScaleFactorY );
        statement.BindDoubleParameter( 9, &imageOffsetY );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMapServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MapServiceOptionsDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMaritimeIdentificationDigits( const ODBC::Connection& connection, Guid& id, Int32 code, const Guid& country )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MaritimeIdentificationDigitsInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt32Parameter( 2, &code );
        statement.BindGuidParameter( 3, &country );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMaritimeIdentificationDigits( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 code, const Guid& country )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MaritimeIdentificationDigitsUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindInt32Parameter( 3, &code );
        statement.BindGuidParameter( 4, &country );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMaritimeIdentificationDigits( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MaritimeIdentificationDigitsDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMediaProxySession( const ODBC::Connection& connection, Guid& id, const Guid& service, const FixedDBWideString<128>& name, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &service );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMediaProxySession( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& service, const FixedDBWideString<128>& name, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &service );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindGuidParameter( 5, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMediaProxySession( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMediaProxySessionFile( const ODBC::Connection& connection, Guid& id, const Guid& proxySession, const DateTime& timestamp, const FixedDBWideString<127>& streamName )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionFileInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &proxySession );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindFixedDBWideStringParameter( 4, streamName );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMediaProxySessionFile( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& proxySession, const DateTime& timestamp, const FixedDBWideString<127>& streamName )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionFileUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &proxySession );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindFixedDBWideStringParameter( 5, streamName );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMediaProxySessionFile( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionFileDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMediaProxySessionOptions( const ODBC::Connection& connection, Guid& id, const Guid& proxySession, const DateTime& timestamp, const FixedDBWideString<255>& sourceStreamUrl, const FixedDBWideString<255>& streamName, Data::MediaProxySessionMode mode, Int32 tunnelOverHTTPPortNumber, const FixedDBWideString<128>& username, const FixedDBWideString<128>& password, Int32 recorderPortNumber, Data::MediaProxySessionType sessionType, const TimeSpan& maxFileTime, const TimeSpan& maxFileRetention, const FixedDBWideString<260>& videoDirectory )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionOptionsInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMediaProxySessionOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& proxySession, const DateTime& timestamp, const FixedDBWideString<255>& sourceStreamUrl, const FixedDBWideString<255>& streamName, Data::MediaProxySessionMode mode, Int32 tunnelOverHTTPPortNumber, const FixedDBWideString<128>& username, const FixedDBWideString<128>& password, Int32 recorderPortNumber, Data::MediaProxySessionType sessionType, const TimeSpan& maxFileTime, const TimeSpan& maxFileRetention, const FixedDBWideString<260>& videoDirectory )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionOptionsUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMediaProxySessionOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionOptionsDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMediaService( const ODBC::Connection& connection, Guid& id, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaServiceInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMediaService( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& enabledTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaServiceUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &enabledTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMediaService( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaServiceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMediaServiceOptions( const ODBC::Connection& connection, Guid& id, const Guid& mediaService, const DateTime& timestamp, Int32 rtspPortNumber, Int32 httpPortNumber )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaServiceOptionsInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &mediaService );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, &rtspPortNumber );
        statement.BindInt32Parameter( 5, &httpPortNumber );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMediaServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& mediaService, const DateTime& timestamp, Int32 rtspPortNumber, Int32 httpPortNumber )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaServiceOptionsUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &mediaService );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, &rtspPortNumber );
        statement.BindInt32Parameter( 6, &httpPortNumber );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMediaServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaServiceOptionsDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertElementType( const ODBC::Connection& connection, Guid& id, const Guid& namespace__, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ElementTypeInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &namespace__ );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateElementType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& namespace__, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ElementTypeUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &namespace__ );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteElementType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ElementTypeDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertNamespace( const ODBC::Connection& connection, Guid& id, const Guid& namespace__, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [NamespaceInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &namespace__ );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateNamespace( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& namespace__, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [NamespaceUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &namespace__ );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteNamespace( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [NamespaceDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertOilSpill( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, double oilArea, const Binary& shape, const Binary& bSI, const Binary& oil, const Binary& trace )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &oilSpillDetector );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, &oilArea );
        statement.BindBinaryParameter( 5, shape );
        statement.BindBinaryParameter( 6, bSI );
        statement.BindBinaryParameter( 7, oil );
        statement.BindBinaryParameter( 8, trace );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateOilSpill( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, double oilArea, const Binary& shape, const Binary& bSI, const Binary& oil, const Binary& trace )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &oilSpillDetector );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &oilArea );
        statement.BindBinaryParameter( 6, shape );
        statement.BindBinaryParameter( 7, bSI );
        statement.BindBinaryParameter( 8, oil );
        statement.BindBinaryParameter( 9, trace );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteOilSpill( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertOilSpillDetectorCommand( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &oilSpillDetector );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateOilSpillDetectorCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &oilSpillDetector );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteOilSpillDetectorCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorCommandDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertOilSpillDetectorCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &oilSpillDetector );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateOilSpillDetectorCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &oilSpillDetector );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteOilSpillDetectorCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorCommandReplyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertOilSpillDetectorConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, double range, double startAngle, double endAngle, double startRange, double endRange, Int32 updateRate, const TimeSpan& statusSendTime, bool drawBorder, const Binary& colors, bool sendToServer, const FixedDBWideString<260>& directory, bool transparentWater, bool savePictures, bool sendAsTarget, bool writeLog, const FixedDBWideString<127>& targetFilePrefix, const Guid& targetMMSI, double latitude, double longitude, bool testSourceEnabled, const FixedDBWideString<127>& proxyServer, bool useProxyServer )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateOilSpillDetectorConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, double range, double startAngle, double endAngle, double startRange, double endRange, Int32 updateRate, const TimeSpan& statusSendTime, bool drawBorder, const Binary& colors, bool sendToServer, const FixedDBWideString<260>& directory, bool transparentWater, bool savePictures, bool sendAsTarget, bool writeLog, const FixedDBWideString<127>& targetFilePrefix, const Guid& targetMMSI, double latitude, double longitude, bool testSourceEnabled, const FixedDBWideString<127>& proxyServer, bool useProxyServer )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteOilSpillDetectorConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [OilSpillDetectorConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertPosition2DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position2DTimeseriesValueInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, x );
        statement.BindDoubleParameter( 5, y );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdatePosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position2DTimeseriesValueUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, x );
        statement.BindDoubleParameter( 6, y );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeletePosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position2DTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertPosition3DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y, const DBDouble& z )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position3DTimeseriesValueInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindDoubleParameter( 4, x );
        statement.BindDoubleParameter( 5, y );
        statement.BindDoubleParameter( 6, z );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdatePosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y, const DBDouble& z )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position3DTimeseriesValueUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, x );
        statement.BindDoubleParameter( 6, y );
        statement.BindDoubleParameter( 7, z );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeletePosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position3DTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertProcessTrackValueResult( const ODBC::Connection& connection, Guid& id, bool createdNewTrack, const Guid& trackId )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ProcessTrackValueResultInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindBooleanParameter( 2, &createdNewTrack );
        statement.BindGuidParameter( 3, &trackId );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateProcessTrackValueResult( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, bool createdNewTrack, const Guid& trackId )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ProcessTrackValueResultUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindBooleanParameter( 3, &createdNewTrack );
        statement.BindGuidParameter( 4, &trackId );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteProcessTrackValueResult( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ProcessTrackValueResultDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBinaryProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Binary& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindBinaryParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBinaryProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Binary& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindBinaryParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBinaryProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBooleanProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, bool value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindBooleanParameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBooleanProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, bool value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindBooleanParameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBooleanProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertByteProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Byte value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BytePropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindByteParameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateByteProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Byte value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BytePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindByteParameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteByteProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BytePropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDateTimeProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DateTime& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimePropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindDateTimeParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDateTimeProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DateTime& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindDateTimeParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDateTimeProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimePropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDoubleProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, double value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoublePropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindDoubleParameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDoubleProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, double value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoublePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindDoubleParameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDoubleProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoublePropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGuidProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGuidProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGuidProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt16Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int16 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16PropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindInt16Parameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt16Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int16 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindInt16Parameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt16Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16PropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt32Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int32 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32PropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindInt32Parameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt32Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int32 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindInt32Parameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt32Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32PropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt64Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int64 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64PropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindInt64Parameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt64Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int64 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindInt64Parameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt64Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64PropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertReferenceProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferencePropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateReferenceProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferencePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteReferenceProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferencePropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSByteProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, SByte value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SBytePropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindSByteParameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSByteProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, SByte value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SBytePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindSByteParameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSByteProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SBytePropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSingleProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, float value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SinglePropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindSingleParameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSingleProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, float value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SinglePropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindSingleParameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSingleProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SinglePropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertStringProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const FixedDBWideString<127>& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindFixedDBWideStringParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateStringProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const FixedDBWideString<127>& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindFixedDBWideStringParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteStringProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBinaryTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBinaryTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBinaryTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBooleanTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBooleanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBooleanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertByteTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDateTimeTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDateTimeTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDateTimeTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDoubleTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDoubleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDoubleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGuidTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGuidTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGuidTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt16TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt32TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt64TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertReferenceTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateReferenceTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteReferenceTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSByteTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSingleTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSingleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSingleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertStringTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateStringTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteStringTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTimeSpanTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTimeSpanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTimeSpanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt16TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt32TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt64TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindGuidParameter( 4, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindGuidParameter( 5, &timeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTimeSpanProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const TimeSpan& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanPropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindTimeSpanParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTimeSpanProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const TimeSpan& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanPropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindTimeSpanParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTimeSpanProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanPropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt16Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, UInt16 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16PropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindUInt16Parameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt16Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, UInt16 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindUInt16Parameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt16Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16PropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt32Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, UInt32 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32PropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindUInt32Parameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt32Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, UInt32 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindUInt32Parameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt32Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32PropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt64Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int64 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64PropertyInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &element );
        statement.BindGuidParameter( 3, &definition );
        statement.BindInt64Parameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt64Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int64 value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64PropertyUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &element );
        statement.BindGuidParameter( 4, &definition );
        statement.BindInt64Parameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt64Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64PropertyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBinaryPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Binary& defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryPropertyDefinitionInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindBinaryParameter( 5, defaultValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBinaryPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Binary& defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindBinaryParameter( 6, defaultValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBinaryPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBooleanPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, bool defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanPropertyDefinitionInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindBooleanParameter( 5, &defaultValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBooleanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, bool defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindBooleanParameter( 6, &defaultValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBooleanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBytePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Byte defaultValue, Byte minValue, Byte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BytePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindByteParameter( 5, &defaultValue );
        statement.BindByteParameter( 6, &minValue );
        statement.BindByteParameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Byte defaultValue, Byte minValue, Byte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BytePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindByteParameter( 6, &defaultValue );
        statement.BindByteParameter( 7, &minValue );
        statement.BindByteParameter( 8, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BytePropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDateTimePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& defaultValue, const FixedDBWideString<127>& minValue, const FixedDBWideString<127>& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindFixedDBWideStringParameter( 5, defaultValue );
        statement.BindFixedDBWideStringParameter( 6, minValue );
        statement.BindFixedDBWideStringParameter( 7, maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDateTimePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& defaultValue, const FixedDBWideString<127>& minValue, const FixedDBWideString<127>& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindFixedDBWideStringParameter( 6, defaultValue );
        statement.BindFixedDBWideStringParameter( 7, minValue );
        statement.BindFixedDBWideStringParameter( 8, maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDateTimePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimePropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDoublePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, double defaultValue, double minValue, double maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoublePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindDoubleParameter( 5, &defaultValue );
        statement.BindDoubleParameter( 6, &minValue );
        statement.BindDoubleParameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDoublePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, double defaultValue, double minValue, double maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoublePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindDoubleParameter( 6, &defaultValue );
        statement.BindDoubleParameter( 7, &minValue );
        statement.BindDoubleParameter( 8, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDoublePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoublePropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGuidPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Guid& defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidPropertyDefinitionInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &defaultValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGuidPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Guid& defaultValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &defaultValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGuidPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt16PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int16 defaultValue, Int16 minValue, Int16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt16Parameter( 5, &defaultValue );
        statement.BindInt16Parameter( 6, &minValue );
        statement.BindInt16Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int16 defaultValue, Int16 minValue, Int16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt16Parameter( 6, &defaultValue );
        statement.BindInt16Parameter( 7, &minValue );
        statement.BindInt16Parameter( 8, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16PropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt32PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int32 defaultValue, Int32 minValue, Int32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt32Parameter( 5, &defaultValue );
        statement.BindInt32Parameter( 6, &minValue );
        statement.BindInt32Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int32 defaultValue, Int32 minValue, Int32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt32Parameter( 6, &defaultValue );
        statement.BindInt32Parameter( 7, &minValue );
        statement.BindInt32Parameter( 8, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32PropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt64PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt64Parameter( 5, &defaultValue );
        statement.BindInt64Parameter( 6, &minValue );
        statement.BindInt64Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt64Parameter( 6, &defaultValue );
        statement.BindInt64Parameter( 7, &minValue );
        statement.BindInt64Parameter( 8, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64PropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertReferencePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Guid& defaultValue, const Guid& referencedElementType )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferencePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &defaultValue );
        statement.BindGuidParameter( 6, &referencedElementType );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateReferencePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Guid& defaultValue, const Guid& referencedElementType )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferencePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &defaultValue );
        statement.BindGuidParameter( 7, &referencedElementType );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteReferencePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferencePropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSBytePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, SByte defaultValue, SByte minValue, SByte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SBytePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindSByteParameter( 5, &defaultValue );
        statement.BindSByteParameter( 6, &minValue );
        statement.BindSByteParameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, SByte defaultValue, SByte minValue, SByte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SBytePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindSByteParameter( 6, &defaultValue );
        statement.BindSByteParameter( 7, &minValue );
        statement.BindSByteParameter( 8, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SBytePropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSinglePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, float defaultValue, float minValue, float maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SinglePropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindSingleParameter( 5, &defaultValue );
        statement.BindSingleParameter( 6, &minValue );
        statement.BindSingleParameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSinglePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, float defaultValue, float minValue, float maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SinglePropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindSingleParameter( 6, &defaultValue );
        statement.BindSingleParameter( 7, &minValue );
        statement.BindSingleParameter( 8, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSinglePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SinglePropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertStringPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& defaultValue, const FixedDBWideString<127>& pattern )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindFixedDBWideStringParameter( 5, defaultValue );
        statement.BindFixedDBWideStringParameter( 6, pattern );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateStringPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& defaultValue, const FixedDBWideString<127>& pattern )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindFixedDBWideStringParameter( 6, defaultValue );
        statement.BindFixedDBWideStringParameter( 7, pattern );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteStringPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Byte minValue, Byte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindByteParameter( 5, &minValue );
        statement.BindByteParameter( 6, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Byte minValue, Byte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindByteParameter( 6, &minValue );
        statement.BindByteParameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& minValue, const FixedDBWideString<127>& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindFixedDBWideStringParameter( 5, minValue );
        statement.BindFixedDBWideStringParameter( 6, maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& minValue, const FixedDBWideString<127>& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindFixedDBWideStringParameter( 6, minValue );
        statement.BindFixedDBWideStringParameter( 7, maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, double minValue, double maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindDoubleParameter( 5, &minValue );
        statement.BindDoubleParameter( 6, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, double minValue, double maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindDoubleParameter( 6, &minValue );
        statement.BindDoubleParameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int16 minValue, Int16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt16Parameter( 5, &minValue );
        statement.BindInt16Parameter( 6, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int16 minValue, Int16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt16Parameter( 6, &minValue );
        statement.BindInt16Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int32 minValue, Int32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt32Parameter( 5, &minValue );
        statement.BindInt32Parameter( 6, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int32 minValue, Int32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt32Parameter( 6, &minValue );
        statement.BindInt32Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt64Parameter( 5, &minValue );
        statement.BindInt64Parameter( 6, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt64Parameter( 6, &minValue );
        statement.BindInt64Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Guid& referencedElementType )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindGuidParameter( 5, &referencedElementType );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Guid& referencedElementType )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindGuidParameter( 6, &referencedElementType );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, SByte minValue, SByte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindSByteParameter( 5, &minValue );
        statement.BindSByteParameter( 6, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, SByte minValue, SByte maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindSByteParameter( 6, &minValue );
        statement.BindSByteParameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, float minValue, float maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindSingleParameter( 5, &minValue );
        statement.BindSingleParameter( 6, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, float minValue, float maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindSingleParameter( 6, &minValue );
        statement.BindSingleParameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& pattern )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindFixedDBWideStringParameter( 5, pattern );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& pattern )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindFixedDBWideStringParameter( 6, pattern );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const TimeSpan& minValue, const TimeSpan& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindTimeSpanParameter( 5, minValue );
        statement.BindTimeSpanParameter( 6, maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const TimeSpan& minValue, const TimeSpan& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindTimeSpanParameter( 6, minValue );
        statement.BindTimeSpanParameter( 7, maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt16 minValue, UInt16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindUInt16Parameter( 5, &minValue );
        statement.BindUInt16Parameter( 6, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt16 minValue, UInt16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindUInt16Parameter( 6, &minValue );
        statement.BindUInt16Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt32 minValue, UInt32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindUInt32Parameter( 5, &minValue );
        statement.BindUInt32Parameter( 6, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt32 minValue, UInt32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindUInt32Parameter( 6, &minValue );
        statement.BindUInt32Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt64Parameter( 5, &minValue );
        statement.BindInt64Parameter( 6, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt64Parameter( 6, &minValue );
        statement.BindInt64Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTimeSpanPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const TimeSpan& defaultValue, const TimeSpan& minValue, const TimeSpan& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanPropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindTimeSpanParameter( 5, defaultValue );
        statement.BindTimeSpanParameter( 6, minValue );
        statement.BindTimeSpanParameter( 7, maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTimeSpanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const TimeSpan& defaultValue, const TimeSpan& minValue, const TimeSpan& maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanPropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindTimeSpanParameter( 6, defaultValue );
        statement.BindTimeSpanParameter( 7, minValue );
        statement.BindTimeSpanParameter( 8, maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTimeSpanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanPropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt16PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt16 defaultValue, UInt16 minValue, UInt16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindUInt16Parameter( 5, &defaultValue );
        statement.BindUInt16Parameter( 6, &minValue );
        statement.BindUInt16Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt16 defaultValue, UInt16 minValue, UInt16 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindUInt16Parameter( 6, &defaultValue );
        statement.BindUInt16Parameter( 7, &minValue );
        statement.BindUInt16Parameter( 8, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16PropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt32PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt32 defaultValue, UInt32 minValue, UInt32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindUInt32Parameter( 5, &defaultValue );
        statement.BindUInt32Parameter( 6, &minValue );
        statement.BindUInt32Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt32 defaultValue, UInt32 minValue, UInt32 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindUInt32Parameter( 6, &defaultValue );
        statement.BindUInt32Parameter( 7, &minValue );
        statement.BindUInt32Parameter( 8, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32PropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt64PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64PropertyDefinitionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &elementType );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.BindInt64Parameter( 5, &defaultValue );
        statement.BindInt64Parameter( 6, &minValue );
        statement.BindInt64Parameter( 7, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64PropertyDefinitionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &elementType );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindWideStringParameter( 5, description );
        statement.BindInt64Parameter( 6, &defaultValue );
        statement.BindInt64Parameter( 7, &minValue );
        statement.BindInt64Parameter( 8, &maxValue );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64PropertyDefinitionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarAlarmStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Data::AlarmState type )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarAlarmStatusInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &type );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarAlarmStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Data::AlarmState type )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarAlarmStatusUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &type );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarAlarmStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarAlarmStatusDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarCommand( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarCommandGetStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandGetStatusInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarCommandGetStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandGetStatusUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarCommandGetStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandGetStatusDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandReplyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarCommandReplyGetStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationCount, Data::RadarPulse pulse, bool tx )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandReplyGetStatusInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarCommandReplyGetStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationCount, Data::RadarPulse pulse, bool tx )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandReplyGetStatusUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarCommandReplyGetStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarCommandReplyGetStatusDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 radarProtocolVersion, const FixedDBWideString<127>& radarIPAddress, Int32 radarPort, Int32 radarConfigurationPort, const TimeSpan& skipMagicTimeout, const TimeSpan& readTimeout, const TimeSpan& synchronizationInterval, Int32 targetsRefreshRate, Int32 range, Int32 sectorCount, Int32 sectorOffset, UInt32 imageColor, const DBUInt32& imageSubstitutionColor, UInt32 transparentColor, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY, Data::RadarImageType radarImageType, UInt32 trackColor, UInt32 vectorColor, bool enableNmea, const FixedDBWideString<127>& nmeaReceiverIPAddress, Int32 nmeaReceiverPort, const FixedDBWideString<127>& nmeaReceiverSourceId )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 radarProtocolVersion, const FixedDBWideString<127>& radarIPAddress, Int32 radarPort, Int32 radarConfigurationPort, const TimeSpan& skipMagicTimeout, const TimeSpan& readTimeout, const TimeSpan& synchronizationInterval, Int32 targetsRefreshRate, Int32 range, Int32 sectorCount, Int32 sectorOffset, UInt32 imageColor, const DBUInt32& imageSubstitutionColor, UInt32 transparentColor, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY, Data::RadarImageType radarImageType, UInt32 trackColor, UInt32 vectorColor, bool enableNmea, const FixedDBWideString<127>& nmeaReceiverIPAddress, Int32 nmeaReceiverPort, const FixedDBWideString<127>& nmeaReceiverSourceId )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarImage( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, UInt32 depth, Int32 resolution, Int32 range, const Binary& image )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarImageInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindUInt32Parameter( 4, &depth );
        statement.BindInt32Parameter( 5, &resolution );
        statement.BindInt32Parameter( 6, &range );
        statement.BindBinaryParameter( 7, image );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarImage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, UInt32 depth, Int32 resolution, Int32 range, const Binary& image )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarImageUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindUInt32Parameter( 5, &depth );
        statement.BindInt32Parameter( 6, &resolution );
        statement.BindInt32Parameter( 7, &range );
        statement.BindBinaryParameter( 8, image );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarImage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarImageDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarRawTrackTable( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 count, const Binary& table )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarRawTrackTableInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, &count );
        statement.BindBinaryParameter( 5, table );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarRawTrackTable( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 count, const Binary& table )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarRawTrackTableUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, &count );
        statement.BindBinaryParameter( 6, table );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarRawTrackTable( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarRawTrackTableDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationTime, Data::RadarPulse pulse, bool tx, bool tracking )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarStatusInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radar );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, &azimuthCount );
        statement.BindInt32Parameter( 5, &triggerCount );
        statement.BindTimeSpanParameter( 6, rotationTime );
        statement.BindEnumParameter( 7, &pulse );
        statement.BindBooleanParameter( 8, &tx );
        statement.BindBooleanParameter( 9, &tracking );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationTime, Data::RadarPulse pulse, bool tx, bool tracking )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarStatusUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radar );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, &azimuthCount );
        statement.BindInt32Parameter( 6, &triggerCount );
        statement.BindTimeSpanParameter( 7, rotationTime );
        statement.BindEnumParameter( 8, &pulse );
        statement.BindBooleanParameter( 9, &tx );
        statement.BindBooleanParameter( 10, &tracking );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarStatusDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadioCommand( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radio );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadioCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radio );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadioCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioCommandDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadioCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radio );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadioCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radio );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadioCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioCommandReplyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadioConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, double longitude, double latitude, const FixedDBWideString<127>& playbackUrl, const FixedDBWideString<127>& radioIPAddress, Int32 radioPort, const FixedDBWideString<127>& ed137IPAddress, Int32 ed137Port )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadioConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, double longitude, double latitude, const FixedDBWideString<127>& playbackUrl, const FixedDBWideString<127>& radioIPAddress, Int32 radioPort, const FixedDBWideString<127>& ed137IPAddress, Int32 ed137Port )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radio );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindDoubleParameter( 5, &longitude );
        statement.BindDoubleParameter( 6, &latitude );
        statement.BindFixedDBWideStringParameter( 7, playbackUrl );
        statement.BindFixedDBWideStringParameter( 8, radioIPAddress );
        statement.BindInt32Parameter( 9, &radioPort );
        statement.BindFixedDBWideStringParameter( 10, ed137IPAddress );
        statement.BindInt32Parameter( 11, &ed137Port );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadioConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadioConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadomeCommand( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radome );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadomeCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radome );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadomeCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeCommandDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadomeCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radome );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadomeCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radome );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadomeCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeCommandReplyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadomeConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, const TimeSpan& interval, double lowPressureLimit, double highPressureLimit, double lowTemperatureLimit, double highTemperatureLimit )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &radome );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindTimeSpanParameter( 4, interval );
        statement.BindDoubleParameter( 5, &lowPressureLimit );
        statement.BindDoubleParameter( 6, &highPressureLimit );
        statement.BindDoubleParameter( 7, &lowTemperatureLimit );
        statement.BindDoubleParameter( 8, &highTemperatureLimit );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadomeConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, const TimeSpan& interval, double lowPressureLimit, double highPressureLimit, double lowTemperatureLimit, double highTemperatureLimit )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &radome );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindTimeSpanParameter( 5, interval );
        statement.BindDoubleParameter( 6, &lowPressureLimit );
        statement.BindDoubleParameter( 7, &highPressureLimit );
        statement.BindDoubleParameter( 8, &lowTemperatureLimit );
        statement.BindDoubleParameter( 9, &highTemperatureLimit );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadomeConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertReferenceTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateReferenceTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const Guid& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteReferenceTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSByteTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBSByte& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindSByteParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBSByte& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindSByteParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSecurityDomain( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityDomainInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindWideStringParameter( 3, description );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSecurityDomain( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityDomainUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindWideStringParameter( 4, description );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSecurityDomain( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityDomainDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSecurityLogin( const ODBC::Connection& connection, Guid& id, const Guid& domain, const FixedDBWideString<255>& identity, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityLoginInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &domain );
        statement.BindFixedDBWideStringParameter( 3, identity );
        statement.BindWideStringParameter( 4, description );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSecurityLogin( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& domain, const FixedDBWideString<255>& identity, const WideString& description )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityLoginUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &domain );
        statement.BindFixedDBWideStringParameter( 4, identity );
        statement.BindWideStringParameter( 5, description );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSecurityLogin( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityLoginDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSecurityRole( const ODBC::Connection& connection, Guid& id, const Guid& domain, const FixedDBWideString<255>& identity, const WideString& description, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityRoleInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &domain );
        statement.BindFixedDBWideStringParameter( 3, identity );
        statement.BindWideStringParameter( 4, description );
        statement.BindFixedDBWideStringParameter( 5, name );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSecurityRole( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& domain, const FixedDBWideString<255>& identity, const WideString& description, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityRoleUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &domain );
        statement.BindFixedDBWideStringParameter( 4, identity );
        statement.BindWideStringParameter( 5, description );
        statement.BindFixedDBWideStringParameter( 6, name );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSecurityRole( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityRoleDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSecurityIdentifierRoleLink( const ODBC::Connection& connection, Guid& id, const Guid& member, const Guid& role, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityIdentifierRoleLinkInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &member );
        statement.BindGuidParameter( 3, &role );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSecurityIdentifierRoleLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& member, const Guid& role, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityIdentifierRoleLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &member );
        statement.BindGuidParameter( 4, &role );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSecurityIdentifierRoleLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityIdentifierRoleLinkDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSecurityLoginSession( const ODBC::Connection& connection, Guid& id, const Guid& login, const DateTime& fromTime, const DBDateTime& throughTime, const Guid& clientSession, const FixedDBWideString<260>& notificationQueueName, const FixedDBWideString<260>& messageQueueName )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityLoginSessionInsert]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &login );
        statement.BindDateTimeParameter( 3, fromTime );
        statement.BindDateTimeParameter( 4, throughTime );
        statement.BindGuidParameter( 5, &clientSession );
        statement.BindFixedDBWideStringParameter( 6, notificationQueueName );
        statement.BindFixedDBWideStringParameter( 7, messageQueueName );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSecurityLoginSession( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& login, const DateTime& fromTime, const DBDateTime& throughTime, const Guid& clientSession, const FixedDBWideString<260>& notificationQueueName, const FixedDBWideString<260>& messageQueueName )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityLoginSessionUpdate]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &login );
        statement.BindDateTimeParameter( 4, fromTime );
        statement.BindDateTimeParameter( 5, throughTime );
        statement.BindGuidParameter( 6, &clientSession );
        statement.BindFixedDBWideStringParameter( 7, notificationQueueName );
        statement.BindFixedDBWideStringParameter( 8, messageQueueName );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSecurityLoginSession( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityLoginSessionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSecurityPermission( const ODBC::Connection& connection, Guid& id, const Guid& identifier, const DateTime& timestamp, Int32 typeCode, bool canCreate, bool canRead, bool canUpdate, bool canDelete )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityPermissionInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &identifier );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt32Parameter( 4, &typeCode );
        statement.BindBooleanParameter( 5, &canCreate );
        statement.BindBooleanParameter( 6, &canRead );
        statement.BindBooleanParameter( 7, &canUpdate );
        statement.BindBooleanParameter( 8, &canDelete );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSecurityPermission( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& identifier, const DateTime& timestamp, Int32 typeCode, bool canCreate, bool canRead, bool canUpdate, bool canDelete )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityPermissionUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &identifier );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt32Parameter( 5, &typeCode );
        statement.BindBooleanParameter( 6, &canCreate );
        statement.BindBooleanParameter( 7, &canRead );
        statement.BindBooleanParameter( 8, &canUpdate );
        statement.BindBooleanParameter( 9, &canDelete );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSecurityPermission( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SecurityPermissionDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSingleTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBSingle& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindSingleParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSingleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBSingle& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindSingleParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSingleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertStringTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const WideString& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindWideStringParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateStringTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const WideString& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindWideStringParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteStringTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBinaryTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBinaryTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBinaryTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BinaryTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertBooleanTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateBooleanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteBooleanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [BooleanTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& aidToNavigation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAidToNavigationOffPositionTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &aidToNavigation );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& aidToNavigation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAidToNavigationOffPositionTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &aidToNavigation );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAidToNavigationOffPositionTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDeviceEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& device )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DeviceEnabledTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, device );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDeviceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& device )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DeviceEnabledTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, device );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDeviceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DeviceEnabledTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarAutomaticSensitivityTimeControlTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarAutomaticSensitivityTimeControlTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarAutomaticSensitivityTimeControlTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarBlankSector1Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarBlankSector1TimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarBlankSector1Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarBlankSector1TimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarBlankSector1Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarBlankSector1TimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarBlankSector2Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarBlankSector2TimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarBlankSector2Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarBlankSector2TimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarBlankSector2Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarBlankSector2TimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarEnableAutomaticFrequencyControlTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarEnableAutomaticFrequencyControlTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarEnableAutomaticFrequencyControlTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarEnableFastTimeConstantTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarEnableFastTimeConstantTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarEnableFastTimeConstantTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarEnableSensitivityTimeControlTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarEnableSensitivityTimeControlTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarEnableSensitivityTimeControlTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarPowerOnTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarPowerOnTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarPowerOnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarPowerOnTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarPowerOnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarPowerOnTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarSaveSettingsTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSaveSettingsTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarSaveSettingsTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSaveSettingsTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarSaveSettingsTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSaveSettingsTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarTrackingTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarTrackingTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarTrackingTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarTrackingTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarTrackingTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarTrackingTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& proxySession )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionEnabledTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &proxySession );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& proxySession )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionEnabledTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &proxySession );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaProxySessionEnabledTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertMediaServiceEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& service )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaServiceEnabledTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &service );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateMediaServiceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& service )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaServiceEnabledTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &service );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteMediaServiceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [MediaServiceEnabledTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertByteTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ByteTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDateTimeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDateTimeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDateTimeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DateTimeTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertDoubleTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateDoubleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteDoubleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [DoubleTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGNSSAltitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSAltitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gNSSDevice );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGNSSAltitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSAltitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gNSSDevice );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGNSSAltitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSAltitudeTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGNSSLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSLatitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gNSSDevice );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGNSSLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSLatitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gNSSDevice );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGNSSLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSLatitudeTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGNSSLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSLongitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gNSSDevice );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGNSSLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gNSSDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSLongitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gNSSDevice );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGNSSLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GNSSLongitudeTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroCourseTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroCourseTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroCourseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroCourseTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroCourseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroCourseTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroHeadingMagneticNorthTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroHeadingMagneticNorthTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroHeadingMagneticNorthTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroHeadingTrueNorthTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroHeadingTrueNorthTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroHeadingTrueNorthTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroPitchTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroPitchTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroPitchTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroPitchTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroPitchTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroPitchTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroRateOfTurnTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroRateOfTurnTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroRateOfTurnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroRateOfTurnTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroRateOfTurnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroRateOfTurnTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroRollTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroRollTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroRollTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroRollTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroRollTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroRollTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGyroSpeedTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroSpeedTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGyroSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& gyroDevice )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroSpeedTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &gyroDevice );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGyroSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GyroSpeedTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarLatitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarLatitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarLatitudeTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarLongitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarLongitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarLongitudeTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadomeDewPointTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeDewPointTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radome );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadomeDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeDewPointTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radome );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadomeDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeDewPointTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadomePressureTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomePressureTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radome );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadomePressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomePressureTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radome );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadomePressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomePressureTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadomeTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeTemperatureTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radome );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadomeTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeTemperatureTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radome );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadomeTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeTemperatureTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertVesselDraughtTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselDraughtTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &vessel );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateVesselDraughtTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselDraughtTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &vessel );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteVesselDraughtTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselDraughtTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertViewLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewLatitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &view );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateViewLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewLatitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &view );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteViewLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewLatitudeTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertViewLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewLongitudeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &view );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateViewLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewLongitudeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &view );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteViewLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewLongitudeTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertViewZoomLevelTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewZoomLevelTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &view );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateViewZoomLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& view )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewZoomLevelTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &view );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteViewZoomLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewZoomLevelTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationAbsoluteHumidityTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationAbsoluteHumidityTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationAbsoluteHumidityTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationAirTemperatureTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationAirTemperatureTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationAirTemperatureTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationBarometricPressureTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationBarometricPressureTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationBarometricPressureTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationDewPointTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationDewPointTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationDewPointTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationDewPointTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationRelativeHumidityTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationRelativeHumidityTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationRelativeHumidityTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationWaterTemperatureTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationWaterTemperatureTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationWaterTemperatureTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationWindDirectionTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationWindDirectionTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationWindDirectionTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationWindSpeedTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& weatherStation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationWindSpeedTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &weatherStation );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationWindSpeedTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGeoPosition2DTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition2DTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGeoPosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition2DTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGeoPosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition2DTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& aidToNavigation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAidToNavigationPositionTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &aidToNavigation );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& aidToNavigation )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAidToNavigationPositionTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &aidToNavigation );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [AisAidToNavigationPositionTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGeoPosition3DTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition3DTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGeoPosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition3DTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGeoPosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GeoPosition3DTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertGuidTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateGuidTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteGuidTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [GuidTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt16Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int16TimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt32Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int32TimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarAzimuthOffsetTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarAzimuthOffsetTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarAzimuthOffsetTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarFastTimeConstantLevelTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarFastTimeConstantLevelTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarFastTimeConstantLevelTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarFastTimeConstantModeTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarFastTimeConstantModeTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarFastTimeConstantModeTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarPulseTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarPulseTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarPulseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarPulseTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarPulseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarPulseTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarSector1EndTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector1EndTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarSector1EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector1EndTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarSector1EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector1EndTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarSector1StartTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector1StartTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarSector1StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector1StartTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarSector1StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector1StartTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarSector2EndTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector2EndTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarSector2EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector2EndTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarSector2EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector2EndTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarSector2StartTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector2StartTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarSector2StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector2StartTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarSector2StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSector2StartTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSensitivityTimeControlLevelTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSensitivityTimeControlLevelTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarSensitivityTimeControlLevelTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadarTuningTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarTuningTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadarTuningTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radar )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarTuningTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radar );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadarTuningTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadarTuningTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselPersonsOnBoardTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &vessel );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselPersonsOnBoardTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &vessel );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselPersonsOnBoardTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertInt64Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Int64TimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertPosition2DTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position2DTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdatePosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position2DTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeletePosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position2DTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertPosition3DTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position3DTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdatePosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position3DTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeletePosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Position3DTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertReferenceTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateReferenceTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteReferenceTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ReferenceTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSByteTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SByteTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertSingleTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateSingleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteSingleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [SingleTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertStringTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateStringTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteStringTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [StringTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTimeSpanTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTimeSpanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTimeSpanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt16Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt32Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertRadomeStatusTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeStatusTimeseriesInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.BindGuidParameter( 5, &radome );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateRadomeStatusTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const Guid& radome )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeStatusTimeseriesUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.BindGuidParameter( 6, &radome );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteRadomeStatusTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [RadomeStatusTimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt64Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindTimeSpanParameter( 4, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.BindTimeSpanParameter( 5, maxRetention );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTimeseriesCatalog( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeseriesCatalogInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, catalog );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTimeseriesCatalog( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeseriesCatalogUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, catalog );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTimeseriesCatalog( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeseriesCatalogDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTimeseriesInfo( const ODBC::Connection& connection, Guid& id, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeseriesInfoInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindDateTimeParameter( 2, firstTimestamp );
        statement.BindDateTimeParameter( 3, lastTimestamp );
        statement.BindInt64Parameter( 4, &count );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTimeseriesInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeseriesInfoUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindDateTimeParameter( 3, firstTimestamp );
        statement.BindDateTimeParameter( 4, lastTimestamp );
        statement.BindInt64Parameter( 5, &count );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTimeseriesInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeseriesInfoDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTimeSpanTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBTimeSpan& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindTimeSpanParameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTimeSpanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBTimeSpan& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindTimeSpanParameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTimeSpanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TimeSpanTimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTrackableItemTrackLink( const ODBC::Connection& connection, Guid& id, const Guid& item, const Guid& track, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackableItemTrackLinkInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &item );
        statement.BindGuidParameter( 3, &track );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTrackableItemTrackLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, const Guid& track, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackableItemTrackLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &item );
        statement.BindGuidParameter( 4, &track );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTrackableItemTrackLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackableItemTrackLinkDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTrack( const ODBC::Connection& connection, Guid& id, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &tracker );
        statement.BindInt64Parameter( 3, &trackNumber );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTrack( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &tracker );
        statement.BindInt64Parameter( 4, &trackNumber );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTrack( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTrack3D( const ODBC::Connection& connection, Guid& id, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Track3DInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &tracker );
        statement.BindInt64Parameter( 3, &trackNumber );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTrack3D( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Track3DUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &tracker );
        statement.BindInt64Parameter( 4, &trackNumber );
        statement.BindDateTimeParameter( 5, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTrack3D( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [Track3DDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTrackerFilterParameters( const ODBC::Connection& connection, Guid& id, const Guid& tracker, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackerFilterParametersInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &tracker );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTrackerFilterParameters( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackerFilterParametersUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &tracker );
        statement.BindFixedDBWideStringParameter( 4, name );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTrackerFilterParameters( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackerFilterParametersDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTrackerFilterParametersConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& parameters, const DateTime& timestamp, bool useNaivePredictor, Int32 numberOfPoints, Int32 windowSize, Int32 stabilizeCount, Int32 maxBadPoints, Data::TrackerFilterModelType modelType, double sigmaR, double sigmaAcc, double tauVel, double tauAcc, double deltaRMin, double deltaVMax, double deltaAMax )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackerFilterParametersConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTrackerFilterParametersConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& parameters, const DateTime& timestamp, bool useNaivePredictor, Int32 numberOfPoints, Int32 windowSize, Int32 stabilizeCount, Int32 maxBadPoints, Data::TrackerFilterModelType modelType, double sigmaR, double sigmaAcc, double tauVel, double tauAcc, double deltaRMin, double deltaVMax, double deltaAMax )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackerFilterParametersConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTrackerFilterParametersConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackerFilterParametersConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTrackInfo( const ODBC::Connection& connection, Guid& id, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count, const DBDouble& northWestLatitude, const DBDouble& northWestLongitude, const DBDouble& southEastLatitude, const DBDouble& southEastLongitude )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackInfoInsert]( ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindDateTimeParameter( 2, firstTimestamp );
        statement.BindDateTimeParameter( 3, lastTimestamp );
        statement.BindInt64Parameter( 4, &count );
        statement.BindDoubleParameter( 5, northWestLatitude );
        statement.BindDoubleParameter( 6, northWestLongitude );
        statement.BindDoubleParameter( 7, southEastLatitude );
        statement.BindDoubleParameter( 8, southEastLongitude );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTrackInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count, const DBDouble& northWestLatitude, const DBDouble& northWestLongitude, const DBDouble& southEastLatitude, const DBDouble& southEastLongitude )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackInfoUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindDateTimeParameter( 3, firstTimestamp );
        statement.BindDateTimeParameter( 4, lastTimestamp );
        statement.BindInt64Parameter( 5, &count );
        statement.BindDoubleParameter( 6, northWestLatitude );
        statement.BindDoubleParameter( 7, northWestLongitude );
        statement.BindDoubleParameter( 8, southEastLatitude );
        statement.BindDoubleParameter( 9, southEastLongitude );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTrackInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackInfoDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTrackingServiceOptions( const ODBC::Connection& connection, Guid& id, const DateTime& timestamp, const TimeSpan& timerInterval, const TimeSpan& maxAgeOfCurrentTrackValue, double falseThreshold, double distanceThreshold, double distanceUnmergeThreshold, Int64 unmergeLatency, bool kalmanFiltering, double maxCourseDeviation, double maxSpeedDeviation, double minimumSpeedThreshold )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackingServiceOptionsInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTrackingServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DateTime& timestamp, const TimeSpan& timerInterval, const TimeSpan& maxAgeOfCurrentTrackValue, double falseThreshold, double distanceThreshold, double distanceUnmergeThreshold, Int64 unmergeLatency, bool kalmanFiltering, double maxCourseDeviation, double maxSpeedDeviation, double minimumSpeedThreshold )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackingServiceOptionsUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTrackingServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackingServiceOptionsDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTrackLink( const ODBC::Connection& connection, Guid& id, const Guid& primary, const Guid& secondary, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackLinkInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &primary );
        statement.BindGuidParameter( 3, &secondary );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTrackLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& primary, const Guid& secondary, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &primary );
        statement.BindGuidParameter( 4, &secondary );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTrackLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackLinkDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTrackValue( const ODBC::Connection& connection, Guid& id, const Guid& track, const DateTime& timestamp, Data::TrackFlags flags, Data::TrackStatus status, double latitude, double longitude, double speed, double course, double heading )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackValueInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTrackValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const DateTime& timestamp, Data::TrackFlags flags, Data::TrackStatus status, double latitude, double longitude, double speed, double course, double heading )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackValueUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &track );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &flags );
        statement.BindEnumParameter( 6, &status );
        statement.BindDoubleParameter( 7, &latitude );
        statement.BindDoubleParameter( 8, &longitude );
        statement.BindDoubleParameter( 9, &speed );
        statement.BindDoubleParameter( 10, &course );
        statement.BindDoubleParameter( 11, &heading );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTrackValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertTrackValue3D( const ODBC::Connection& connection, Guid& id, const Guid& track, const DateTime& timestamp, Data::TrackFlags3D flags, UInt32 status, double latitude, double longitude, double altitude, double speed, double course, double rateOfClimb )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackValue3DInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateTrackValue3D( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const DateTime& timestamp, Data::TrackFlags3D flags, UInt32 status, double latitude, double longitude, double altitude, double speed, double course, double rateOfClimb )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackValue3DUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteTrackValue3D( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [TrackValue3DDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt16TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBUInt16& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindUInt16Parameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBUInt16& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindUInt16Parameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt16TimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt32TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBUInt32& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindUInt32Parameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBUInt32& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindUInt32Parameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt32TimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertUInt64TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesValueInsert]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &timeseries );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindInt64Parameter( 4, value );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateUInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesValueUpdate]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &timeseries );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindInt64Parameter( 5, value );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteUInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [UInt64TimeseriesValueDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertVehicleType( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VehicleTypeInsert]( ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateVehicleType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VehicleTypeUpdate]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteVehicleType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VehicleTypeDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertVesselType( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, Int32 code )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselTypeInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindInt32Parameter( 3, &code );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateVesselType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, Int32 code )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselTypeUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindInt32Parameter( 4, &code );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteVesselType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [VesselTypeDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertView( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& zoomLevelTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindFixedDBWideStringParameter( 2, name );
        statement.BindGuidParameter( 3, &latitudeTimeseries );
        statement.BindGuidParameter( 4, &longitudeTimeseries );
        statement.BindGuidParameter( 5, &zoomLevelTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateView( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& zoomLevelTimeseries )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindFixedDBWideStringParameter( 3, name );
        statement.BindGuidParameter( 4, &latitudeTimeseries );
        statement.BindGuidParameter( 5, &longitudeTimeseries );
        statement.BindGuidParameter( 6, &zoomLevelTimeseries );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteView( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertViewCameraLink( const ODBC::Connection& connection, Guid& id, const Guid& view, const Guid& camera, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewCameraLinkInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &view );
        statement.BindGuidParameter( 3, &camera );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateViewCameraLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, const Guid& camera, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewCameraLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &view );
        statement.BindGuidParameter( 4, &camera );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteViewCameraLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewCameraLinkDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertViewTrackerLink( const ODBC::Connection& connection, Guid& id, const Guid& view, const Guid& tracker, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewTrackerLinkInsert]( ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &view );
        statement.BindGuidParameter( 3, &tracker );
        statement.BindDateTimeParameter( 4, start );
        statement.BindDateTimeParameter( 5, end );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateViewTrackerLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, const Guid& tracker, const DateTime& start, const DBDateTime& end )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewTrackerLinkUpdate]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &view );
        statement.BindGuidParameter( 4, &tracker );
        statement.BindDateTimeParameter( 5, start );
        statement.BindDateTimeParameter( 6, end );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteViewTrackerLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ViewTrackerLinkDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationCommand( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationCommandInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &weatherStation );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindEnumParameter( 4, &deviceCommandSourceType );
        statement.BindGuidParameter( 5, &deviceCommandSourceId );
        statement.BindGuidParameter( 6, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationCommandUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &weatherStation );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindEnumParameter( 5, &deviceCommandSourceType );
        statement.BindGuidParameter( 6, &deviceCommandSourceId );
        statement.BindGuidParameter( 7, &reply );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationCommandDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationCommandReplyInsert]( ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &weatherStation );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.BindGuidParameter( 4, &command );
        statement.BindEnumParameter( 5, &status );
        statement.BindWideStringParameter( 6, message );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationCommandReplyUpdate]( ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &weatherStation );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindGuidParameter( 5, &command );
        statement.BindEnumParameter( 6, &status );
        statement.BindWideStringParameter( 7, message );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationCommandReplyDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertWeatherStationConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, const TimeSpan& noDataTimeOut, const TimeSpan& sendInterval, double latitude, double longitude, double gyroOffset, bool enableAveraging, const TimeSpan& averagingInterval )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationConfigurationInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateWeatherStationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, const TimeSpan& noDataTimeOut, const TimeSpan& sendInterval, double latitude, double longitude, double gyroOffset, bool enableAveraging, const TimeSpan& averagingInterval )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationConfigurationUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &weatherStation );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.BindTimeSpanParameter( 5, noDataTimeOut );
        statement.BindTimeSpanParameter( 6, sendInterval );
        statement.BindDoubleParameter( 7, &latitude );
        statement.BindDoubleParameter( 8, &longitude );
        statement.BindDoubleParameter( 9, &gyroOffset );
        statement.BindBooleanParameter( 10, &enableAveraging );
        statement.BindTimeSpanParameter( 11, averagingInterval );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteWeatherStationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [WeatherStationConfigurationDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertCircularZone( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, double radius )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CircularZoneInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateCircularZone( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, double radius )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CircularZoneUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteCircularZone( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [CircularZoneDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertPolygonZone( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, const Binary& polygon )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [PolygonZoneInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdatePolygonZone( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, const Binary& polygon )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [PolygonZoneUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeletePolygonZone( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [PolygonZoneDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertZoneExceptions( const ODBC::Connection& connection, Guid& id, const Guid& zone, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ZoneExceptionsInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &zone );
        statement.BindDateTimeParameter( 3, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateZoneExceptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zone, const DateTime& timestamp )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ZoneExceptionsUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &zone );
        statement.BindDateTimeParameter( 4, timestamp );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteZoneExceptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ZoneExceptionsDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertZoneExceptionsVesselLink( const ODBC::Connection& connection, Guid& id, const Guid& zoneExceptions, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ZoneExceptionsVesselLinkInsert]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindGuidParameter( 2, &zoneExceptions );
        statement.BindGuidParameter( 3, &vessel );
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateZoneExceptionsVesselLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zoneExceptions, const Guid& vessel )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ZoneExceptionsVesselLinkUpdate]( ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        statement.BindGuidParameter( 3, &zoneExceptions );
        statement.BindGuidParameter( 4, &vessel );
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteZoneExceptionsVesselLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ZoneExceptionsVesselLinkDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

    BARRELMAN_EXPORT bool InsertZoneTrackAlarm( const ODBC::Connection& connection, Guid& id, const Guid& track, const Guid& zone, const Guid& radarTrack, const DateTime& timestamp, double latitude, double longitude, double speed, const DBDouble& course, const DBDouble& heading, double enterLatitude, double enterLongitude, const DBDouble& leaveLatitude, const DBDouble& leaveLongitude )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ZoneTrackAlarmInsert]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
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
        statement.Execute( );
        SQLLEN numberOfRowsInserted = statement.RowCount( );
        return numberOfRowsInserted > 0;
    }
    BARRELMAN_EXPORT bool UpdateZoneTrackAlarm( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const Guid& zone, const Guid& radarTrack, const DateTime& timestamp, double latitude, double longitude, double speed, const DBDouble& course, const DBDouble& heading, double enterLatitude, double enterLongitude, const DBDouble& leaveLatitude, const DBDouble& leaveLongitude )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ZoneTrackAlarmUpdate]( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
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
        statement.Execute( );
        SQLLEN numberOfRowsUpdated = statement.RowCount( );
        if( numberOfRowsUpdated )
        {
            rowVersion++;
        }
        return numberOfRowsUpdated > 0;
    }
    BARRELMAN_EXPORT bool DeleteZoneTrackAlarm( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion )
    {
        auto statement = connection.CreateStatement( );
        statement.Prepare( L"{ CALL [ZoneTrackAlarmDelete]( ?, ?, ? ) }" );
        statement.BindGuidParameter( 1, &id );
        statement.BindInt64Parameter( 2, &rowVersion );
        Int32 numberOfObjectsDeleted = 0;
        statement.BindInt32Parameter( 3, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );
        statement.Execute( );
        SQLLEN numberOfRowsDeleted = statement.RowCount( );
        return numberOfRowsDeleted > 0;
    }

}
