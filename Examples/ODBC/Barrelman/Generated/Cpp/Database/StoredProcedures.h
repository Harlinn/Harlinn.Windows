#pragma once
#ifndef DATABASE_STOREDPROCEDURES_H_
#define DATABASE_STOREDPROCEDURES_H_

#include <HODBC.h>
#include <HCCData.h>
#include "Data/DataTypes.h"


namespace Barrelman::Database
{
    using namespace Harlinn;
    using namespace Harlinn::ODBC;
    using namespace Harlinn::Common::Core;

    BARRELMAN_EXPORT void InsertAircraftType( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void UpdateAircraftType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void DeleteAircraftType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT void UpdateAisDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT void DeleteAisDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void UpdateAisDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void DeleteAisDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, FixedDBWideString<127> userName, FixedDBWideString<127> password, double latitude, double longitude, FixedDBWideString<127> aisProviderLoginURL, FixedDBWideString<32> comPort, Int32 baudRate, bool filterByArea, double upperLeftCornerLatitude, double upperLeftCornerLongitude, double bottomRightCornerLatitude, double bottomRightCornerLongitude, FixedDBWideString<127> aisProviderIPAddress, Int32 aisProviderPort, bool useLogin, Int32 aisProviderLoginPort, bool canSendAISMessage, const WideString& textMessageHeader, const WideString& urls, Int32 udpPort, Data::AisDeviceConnectionType connectionType, bool enableRefreshAidToNavigationIn30sec, bool enableAidToNavigationFromFile, const WideString& aidToNavigationHeader, bool sendingMMSI, Int32 sourceUpdateRate, bool enableRefreshStayingStillTargetIn30sec, const WideString& excludeSendAisBaseStation, const WideString& excludeSendAisA, bool enableSendBaseStationAlarms, FixedDBWideString<127> aisWebConfig, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages );
    BARRELMAN_EXPORT void UpdateAisDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, FixedDBWideString<127> userName, FixedDBWideString<127> password, double latitude, double longitude, FixedDBWideString<127> aisProviderLoginURL, FixedDBWideString<32> comPort, Int32 baudRate, bool filterByArea, double upperLeftCornerLatitude, double upperLeftCornerLongitude, double bottomRightCornerLatitude, double bottomRightCornerLongitude, FixedDBWideString<127> aisProviderIPAddress, Int32 aisProviderPort, bool useLogin, Int32 aisProviderLoginPort, bool canSendAISMessage, const WideString& textMessageHeader, const WideString& urls, Int32 udpPort, Data::AisDeviceConnectionType connectionType, bool enableRefreshAidToNavigationIn30sec, bool enableAidToNavigationFromFile, const WideString& aidToNavigationHeader, bool sendingMMSI, Int32 sourceUpdateRate, bool enableRefreshStayingStillTargetIn30sec, const WideString& excludeSendAisBaseStation, const WideString& excludeSendAisA, bool enableSendBaseStationAlarms, FixedDBWideString<127> aisWebConfig, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages );
    BARRELMAN_EXPORT void DeleteAisDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisDeviceRawMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, bool isSent, FixedDBWideString<100> message );
    BARRELMAN_EXPORT void UpdateAisDeviceRawMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, bool isSent, FixedDBWideString<100> message );
    BARRELMAN_EXPORT void DeleteAisDeviceRawMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisDeviceRawSentence( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, const WideString& sentence );
    BARRELMAN_EXPORT void UpdateAisDeviceRawSentence( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, const WideString& sentence );
    BARRELMAN_EXPORT void DeleteAisDeviceRawSentence( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAidToNavigationReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationalAidType navigationalAidType, FixedDBWideString<100> name, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Int32 timestamp, bool offPosition, Int32 regionalReserved, Data::Raim raim, bool virtualAid, bool assigned, Int32 spare, FixedDBWideString<100> nameExtension );
    BARRELMAN_EXPORT void UpdateAidToNavigationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationalAidType navigationalAidType, FixedDBWideString<100> name, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Int32 timestamp, bool offPosition, Int32 regionalReserved, Data::Raim raim, bool virtualAid, bool assigned, Int32 spare, FixedDBWideString<100> nameExtension );
    BARRELMAN_EXPORT void DeleteAidToNavigationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, FixedDBWideString<100> text );
    BARRELMAN_EXPORT void UpdateAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, FixedDBWideString<100> text );
    BARRELMAN_EXPORT void DeleteAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisBaseStationReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& timestamp, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void UpdateAisBaseStationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& timestamp, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void DeleteAisBaseStationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 );
    BARRELMAN_EXPORT void UpdateAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 );
    BARRELMAN_EXPORT void DeleteAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisBinaryAddressedMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data );
    BARRELMAN_EXPORT void UpdateAisBinaryAddressedMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 sequenceNumber, const Guid& destinationMmsi, bool retransmitFlag, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data );
    BARRELMAN_EXPORT void DeleteAisBinaryAddressedMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisBinaryBroadcastMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data );
    BARRELMAN_EXPORT void UpdateAisBinaryBroadcastMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data );
    BARRELMAN_EXPORT void DeleteAisBinaryBroadcastMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisDataLinkManagementMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 offset1, Int32 reservedSlots1, Int32 timeout1, Int32 increment1, const DBInt32& offset2, const DBInt32& reservedSlots2, const DBInt32& timeout2, const DBInt32& increment2, const DBInt32& offset3, const DBInt32& reservedSlots3, const DBInt32& timeout3, const DBInt32& increment3, const DBInt32& offset4, const DBInt32& reservedSlots4, const DBInt32& timeout4, const DBInt32& increment4 );
    BARRELMAN_EXPORT void UpdateAisDataLinkManagementMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 offset1, Int32 reservedSlots1, Int32 timeout1, Int32 increment1, const DBInt32& offset2, const DBInt32& reservedSlots2, const DBInt32& timeout2, const DBInt32& increment2, const DBInt32& offset3, const DBInt32& reservedSlots3, const DBInt32& timeout3, const DBInt32& increment3, const DBInt32& offset4, const DBInt32& reservedSlots4, const DBInt32& timeout4, const DBInt32& increment4 );
    BARRELMAN_EXPORT void DeleteAisDataLinkManagementMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, const Guid& name, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Data::Raim raim, bool dataTerminalReady, bool assigned, Int32 spare );
    BARRELMAN_EXPORT void UpdateAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, const Guid& name, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, Data::Raim raim, bool dataTerminalReady, bool assigned, Int32 spare );
    BARRELMAN_EXPORT void DeleteAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisInterrogationMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const Guid& interrogatedMmsi, Data::AisMessageType firstMessageType, Int32 firstSlotOffset, const DBEnum<Data::AisMessageType>& secondMessageType, const DBInt32& secondSlotOffset, const DBGuid& secondStationInterrogationMmsi, const DBEnum<Data::AisMessageType>& secondStationFirstMessageType, const DBInt32& secondStationFirstSlotOffset );
    BARRELMAN_EXPORT void UpdateAisInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const Guid& interrogatedMmsi, Data::AisMessageType firstMessageType, Int32 firstSlotOffset, const DBEnum<Data::AisMessageType>& secondMessageType, const DBInt32& secondSlotOffset, const DBGuid& secondStationInterrogationMmsi, const DBEnum<Data::AisMessageType>& secondStationFirstMessageType, const DBInt32& secondStationFirstSlotOffset );
    BARRELMAN_EXPORT void DeleteAisInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void UpdateAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void DeleteAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisPositionReportClassAMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void UpdateAisPositionReportClassAMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void DeleteAisPositionReportClassAMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void UpdateAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Data::ManeuverIndicator maneuverIndicator, Int32 spare, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void DeleteAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::PositionAccuracy positionAccuracy, Data::Raim raim, Data::NavigationStatus navigationStatus, double longitude, double latitude, double speedOverGround, double courseOverGround, Data::GnssPositionStatus gnssPositionStatus, Int32 spare );
    BARRELMAN_EXPORT void UpdateAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Data::PositionAccuracy positionAccuracy, Data::Raim raim, Data::NavigationStatus navigationStatus, double longitude, double latitude, double speedOverGround, double courseOverGround, Data::GnssPositionStatus gnssPositionStatus, Int32 spare );
    BARRELMAN_EXPORT void DeleteAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 );
    BARRELMAN_EXPORT void UpdateAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare, Int32 sequenceNumber1, const Guid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 );
    BARRELMAN_EXPORT void DeleteAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, bool isCsUnit, bool hasDisplay, bool hasDscCapability, bool band, bool canAcceptMessage22, bool assigned, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void UpdateAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 reserved, double speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, bool isCsUnit, bool hasDisplay, bool hasDscCapability, bool band, bool canAcceptMessage22, bool assigned, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void DeleteAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 altitude, Int32 speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, Int32 timestamp, Int32 reserved, bool dataTerminalReady, Int32 spare, bool assigned, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void UpdateAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 altitude, Int32 speedOverGround, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, Int32 timestamp, Int32 reserved, bool dataTerminalReady, Int32 spare, bool assigned, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void DeleteAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 aisVersion, const Guid& imoNumber, const Guid& callsign, const Guid& shipName, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, const DBDateTime& estimatedTimeOfArrival, double draught, FixedDBWideString<100> destination, bool dataTerminalReady, Int32 spare );
    BARRELMAN_EXPORT void UpdateAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 aisVersion, const Guid& imoNumber, const Guid& callsign, const Guid& shipName, Data::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Data::PositionFixType positionFixType, const DBDateTime& estimatedTimeOfArrival, double draught, FixedDBWideString<100> destination, bool dataTerminalReady, Int32 spare );
    BARRELMAN_EXPORT void DeleteAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisStaticDataReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber );
    BARRELMAN_EXPORT void UpdateAisStaticDataReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber );
    BARRELMAN_EXPORT void DeleteAisStaticDataReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisStaticDataReportPartAMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, const Guid& shipName, Int32 spare );
    BARRELMAN_EXPORT void UpdateAisStaticDataReportPartAMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, const Guid& shipName, Int32 spare );
    BARRELMAN_EXPORT void DeleteAisStaticDataReportPartAMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisStaticDataReportPartBMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, Data::ShipType shipType, FixedDBWideString<100> vendorId, Int32 unitModelCode, Int32 serialNumber, const Guid& callsign, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, const DBGuid& mothershipMmsi, Data::PositionFixType positionFixType, Int32 spare );
    BARRELMAN_EXPORT void UpdateAisStaticDataReportPartBMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 partNumber, Data::ShipType shipType, FixedDBWideString<100> vendorId, Int32 unitModelCode, Int32 serialNumber, const Guid& callsign, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, const DBGuid& mothershipMmsi, Data::PositionFixType positionFixType, Int32 spare );
    BARRELMAN_EXPORT void DeleteAisStaticDataReportPartBMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare1, Int32 destinationMmsi, Int32 spare2 );
    BARRELMAN_EXPORT void UpdateAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, Int32 spare1, Int32 destinationMmsi, Int32 spare2 );
    BARRELMAN_EXPORT void DeleteAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisUtcAndDateResponseMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& datetime, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void UpdateAisUtcAndDateResponseMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const Guid& mmsi, const DateTime& datetime, Data::PositionAccuracy positionAccuracy, double longitude, double latitude, Data::PositionFixType positionFixType, Int32 spare, Data::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT void DeleteAisUtcAndDateResponseMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAlarmStateChange( const ODBC::Connection& connection, Guid& id, const Guid& alarm, const DateTime& timestamp, Data::AlarmState state );
    BARRELMAN_EXPORT void UpdateAlarmStateChange( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& alarm, const DateTime& timestamp, Data::AlarmState state );
    BARRELMAN_EXPORT void DeleteAlarmStateChange( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBaseStationType( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void UpdateBaseStationType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void DeleteBaseStationType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBinaryTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const Binary& value );
    BARRELMAN_EXPORT void UpdateBinaryTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const Binary& value );
    BARRELMAN_EXPORT void DeleteBinaryTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBookmark( const ODBC::Connection& connection, Guid& id, const Guid& view, FixedDBWideString<100> name, const DBDateTime& timestamp, double latitude, double longitude, double zoomLevel );
    BARRELMAN_EXPORT void UpdateBookmark( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, FixedDBWideString<100> name, const DBDateTime& timestamp, double latitude, double longitude, double zoomLevel );
    BARRELMAN_EXPORT void DeleteBookmark( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBooleanTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBBoolean & value );
    BARRELMAN_EXPORT void UpdateBooleanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBBoolean & value );
    BARRELMAN_EXPORT void DeleteBooleanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertByteTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBByte& value );
    BARRELMAN_EXPORT void UpdateByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBByte& value );
    BARRELMAN_EXPORT void DeleteByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommand( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateCameraCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteCameraCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandAbsoluteMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, Data::CameraPanTiltMode positionPanTiltMode, const DBDouble& panAngle, const DBDouble& tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, const DBDouble& focalLength, Data::CameraPanTiltMode speedPanTiltMode, const DBDouble& panSpeed, const DBDouble& tiltSpeed, Data::CameraFocalLengthMode speedFocalLengthMode, const DBDouble& zoomSpeed );
    BARRELMAN_EXPORT void UpdateCameraCommandAbsoluteMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, Data::CameraPanTiltMode positionPanTiltMode, const DBDouble& panAngle, const DBDouble& tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, const DBDouble& focalLength, Data::CameraPanTiltMode speedPanTiltMode, const DBDouble& panSpeed, const DBDouble& tiltSpeed, Data::CameraFocalLengthMode speedFocalLengthMode, const DBDouble& zoomSpeed );
    BARRELMAN_EXPORT void DeleteCameraCommandAbsoluteMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const DBDouble& x, const DBDouble& y, const DBDouble& z );
    BARRELMAN_EXPORT void UpdateCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const DBDouble& x, const DBDouble& y, const DBDouble& z );
    BARRELMAN_EXPORT void DeleteCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandContinuousMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panVelocity, const DBDouble& tiltVelocity, const DBDouble& zoomVelocity, const DBTimeSpan& duration );
    BARRELMAN_EXPORT void UpdateCameraCommandContinuousMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panVelocity, const DBDouble& tiltVelocity, const DBDouble& zoomVelocity, const DBTimeSpan& duration );
    BARRELMAN_EXPORT void DeleteCameraCommandContinuousMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandGeoMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, double latitude, double longitude, const DBDouble& altitude, const DBDouble& viewportWidth, const DBDouble& viewportHeight );
    BARRELMAN_EXPORT void UpdateCameraCommandGeoMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, double latitude, double longitude, const DBDouble& altitude, const DBDouble& viewportWidth, const DBDouble& viewportHeight );
    BARRELMAN_EXPORT void DeleteCameraCommandGeoMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandRelativeMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panAngle, const DBDouble& tiltAngle, const DBDouble& focalLength, const DBDouble& panSpeed, const DBDouble& tiltSpeed, const DBDouble& zoomSpeed );
    BARRELMAN_EXPORT void UpdateCameraCommandRelativeMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool normalized, const DBDouble& panAngle, const DBDouble& tiltAngle, const DBDouble& focalLength, const DBDouble& panSpeed, const DBDouble& tiltSpeed, const DBDouble& zoomSpeed );
    BARRELMAN_EXPORT void DeleteCameraCommandRelativeMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandSetAutoFocus( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled );
    BARRELMAN_EXPORT void UpdateCameraCommandSetAutoFocus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled );
    BARRELMAN_EXPORT void DeleteCameraCommandSetAutoFocus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled );
    BARRELMAN_EXPORT void UpdateCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled );
    BARRELMAN_EXPORT void DeleteCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandSetFollowed( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const Guid& trackId, Data::CameraFollowReason reason );
    BARRELMAN_EXPORT void UpdateCameraCommandSetFollowed( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, const Guid& trackId, Data::CameraFollowReason reason );
    BARRELMAN_EXPORT void DeleteCameraCommandSetFollowed( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled );
    BARRELMAN_EXPORT void UpdateCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled );
    BARRELMAN_EXPORT void DeleteCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandSetWasher( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled );
    BARRELMAN_EXPORT void UpdateCameraCommandSetWasher( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled );
    BARRELMAN_EXPORT void DeleteCameraCommandSetWasher( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandSetWiper( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled );
    BARRELMAN_EXPORT void UpdateCameraCommandSetWiper( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool enabled );
    BARRELMAN_EXPORT void DeleteCameraCommandSetWiper( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandStop( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool panTilt, bool zoom );
    BARRELMAN_EXPORT void UpdateCameraCommandStop( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply, bool panTilt, bool zoom );
    BARRELMAN_EXPORT void DeleteCameraCommandStop( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, double panAngle, double tiltAngle, double focalLength );
    BARRELMAN_EXPORT void UpdateCameraCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, double panAngle, double tiltAngle, double focalLength );
    BARRELMAN_EXPORT void DeleteCameraCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Data::CameraControlProtocol cameraControlProtocol, FixedDBWideString<127> cameraAddress, Int32 cameraPort, FixedDBWideString<127> cameraControlAddress, Int32 cameraControlPort, FixedDBWideString<127> cameraUserName, FixedDBWideString<127> cameraPassword, bool useRtspUriOverride, FixedDBWideString<127> rtspUriOverride, double latitude, double longitude, double altitude, bool useRelativePosition, double azimuthFromGPS, double distanceFromGPS, Data::CameraPanTiltMode panTiltMode, double minTiltAngle, double maxTiltAngle, double minTiltScaleAngle, double maxTiltScaleAngle, bool useReverseTiltAngle, bool useReverseNormalizedTiltAngle, double minTiltVelocity, double maxTiltVelocity, double minTiltSpeed, double maxTiltSpeed, double minPanAngle, double maxPanAngle, double minPanScaleAngle, double maxPanScaleAngle, bool useReversePanAngle, bool useReverseNormalizedPanAngle, double minPanVelocity, double maxPanVelocity, double minPanSpeed, double maxPanSpeed, Data::CameraFocalLengthMode focalLengthMode, double minFocalLength, double maxFocalLength, double minFocalLengthScale, double maxFocalLengthScale, double minZoomVelocity, double maxZoomVelocity, double minZoomSpeed, double maxZoomSpeed, double imageSensorWidth, double imageSensorHeight, double homePanAngle, double homeTiltAngle, double homeFocalLength, double panOffset, double tiltOffset, double aimAltitude, double minimumTargetWidth, const TimeSpan& targetLockTimeout, const TimeSpan& updateStatusInterval, const TimeSpan& readTimeout, const TimeSpan& moveCommandStatusDelay, FixedDBWideString<127> ptzProfileName, FixedDBWideString<127> ptzConfigurationToken, FixedDBWideString<127> videoSourceToken );
    BARRELMAN_EXPORT void UpdateCameraConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Data::CameraControlProtocol cameraControlProtocol, FixedDBWideString<127> cameraAddress, Int32 cameraPort, FixedDBWideString<127> cameraControlAddress, Int32 cameraControlPort, FixedDBWideString<127> cameraUserName, FixedDBWideString<127> cameraPassword, bool useRtspUriOverride, FixedDBWideString<127> rtspUriOverride, double latitude, double longitude, double altitude, bool useRelativePosition, double azimuthFromGPS, double distanceFromGPS, Data::CameraPanTiltMode panTiltMode, double minTiltAngle, double maxTiltAngle, double minTiltScaleAngle, double maxTiltScaleAngle, bool useReverseTiltAngle, bool useReverseNormalizedTiltAngle, double minTiltVelocity, double maxTiltVelocity, double minTiltSpeed, double maxTiltSpeed, double minPanAngle, double maxPanAngle, double minPanScaleAngle, double maxPanScaleAngle, bool useReversePanAngle, bool useReverseNormalizedPanAngle, double minPanVelocity, double maxPanVelocity, double minPanSpeed, double maxPanSpeed, Data::CameraFocalLengthMode focalLengthMode, double minFocalLength, double maxFocalLength, double minFocalLengthScale, double maxFocalLengthScale, double minZoomVelocity, double maxZoomVelocity, double minZoomSpeed, double maxZoomSpeed, double imageSensorWidth, double imageSensorHeight, double homePanAngle, double homeTiltAngle, double homeFocalLength, double panOffset, double tiltOffset, double aimAltitude, double minimumTargetWidth, const TimeSpan& targetLockTimeout, const TimeSpan& updateStatusInterval, const TimeSpan& readTimeout, const TimeSpan& moveCommandStatusDelay, FixedDBWideString<127> ptzProfileName, FixedDBWideString<127> ptzConfigurationToken, FixedDBWideString<127> videoSourceToken );
    BARRELMAN_EXPORT void DeleteCameraConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraPanCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT void UpdateCameraPanCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT void DeleteCameraPanCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraPanCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& panCalibration, double panAngle, double panOffset );
    BARRELMAN_EXPORT void UpdateCameraPanCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& panCalibration, double panAngle, double panOffset );
    BARRELMAN_EXPORT void DeleteCameraPanCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraStatus( const ODBC::Connection& connection, Guid& id, const Guid& camera, const Guid& track, const DateTime& timestamp, Data::CameraPanTiltMode positionPanTiltMode, double panAngle, double tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, double focalLength, Data::CameraMoveStatus panTiltMoveStatus, Data::CameraMoveStatus zoomMoveStatus, Data::CameraPanTiltMode velocityPanTiltMode, const DBDouble& panVelocity, const DBDouble& tiltVelocity, Data::CameraFocalLengthMode velocityFocalLengthMode, const DBDouble& zoomVelocity, Data::CameraFeatures activeFeatures, const WideString& error );
    BARRELMAN_EXPORT void UpdateCameraStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const Guid& track, const DateTime& timestamp, Data::CameraPanTiltMode positionPanTiltMode, double panAngle, double tiltAngle, Data::CameraFocalLengthMode positionFocalLengthMode, double focalLength, Data::CameraMoveStatus panTiltMoveStatus, Data::CameraMoveStatus zoomMoveStatus, Data::CameraPanTiltMode velocityPanTiltMode, const DBDouble& panVelocity, const DBDouble& tiltVelocity, Data::CameraFocalLengthMode velocityFocalLengthMode, const DBDouble& zoomVelocity, Data::CameraFeatures activeFeatures, const WideString& error );
    BARRELMAN_EXPORT void DeleteCameraStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraTiltCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT void UpdateCameraTiltCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT void DeleteCameraTiltCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraTiltCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& tiltCalibration, double panAngle, double tiltOffset );
    BARRELMAN_EXPORT void UpdateCameraTiltCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tiltCalibration, double panAngle, double tiltOffset );
    BARRELMAN_EXPORT void DeleteCameraTiltCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraZoomCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT void UpdateCameraZoomCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT void DeleteCameraZoomCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraZoomCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& zoomCalibration, double focalLength, double focalLengthOffset );
    BARRELMAN_EXPORT void UpdateCameraZoomCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zoomCalibration, double focalLength, double focalLengthOffset );
    BARRELMAN_EXPORT void DeleteCameraZoomCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCatalog( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void UpdateCatalog( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void DeleteCatalog( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertElement( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<127> name, const Guid& elementType );
    BARRELMAN_EXPORT void UpdateElement( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<127> name, const Guid& elementType );
    BARRELMAN_EXPORT void DeleteElement( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCollectionInfo( const ODBC::Connection& connection, Guid& id, Int64 count );
    BARRELMAN_EXPORT void UpdateCollectionInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 count );
    BARRELMAN_EXPORT void DeleteCollectionInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCountry( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, Int32 code, FixedDBWideString<2> alpha2, FixedDBWideString<3> alpha3 );
    BARRELMAN_EXPORT void UpdateCountry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, Int32 code, FixedDBWideString<2> alpha2, FixedDBWideString<3> alpha3 );
    BARRELMAN_EXPORT void DeleteCountry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCursorInfo( const ODBC::Connection& connection, Guid& id, Int32 typeCode );
    BARRELMAN_EXPORT void UpdateCursorInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 typeCode );
    BARRELMAN_EXPORT void DeleteCursorInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDateTimeTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDateTime& value );
    BARRELMAN_EXPORT void UpdateDateTimeTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDateTime& value );
    BARRELMAN_EXPORT void DeleteDateTimeTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDeviceHost( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void UpdateDeviceHost( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void DeleteDeviceHost( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDeviceHostConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& host, const DateTime& timestamp, FixedDBWideString<127> hostname, Int32 port, FixedDBWideString<100> queueName );
    BARRELMAN_EXPORT void UpdateDeviceHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const DateTime& timestamp, FixedDBWideString<127> hostname, Int32 port, FixedDBWideString<100> queueName );
    BARRELMAN_EXPORT void DeleteDeviceHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDoubleTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& value );
    BARRELMAN_EXPORT void UpdateDoubleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& value );
    BARRELMAN_EXPORT void DeleteDoubleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertFacilityType( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void UpdateFacilityType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void DeleteFacilityType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude );
    BARRELMAN_EXPORT void UpdateGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude );
    BARRELMAN_EXPORT void DeleteGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude, const DBDouble& altitude );
    BARRELMAN_EXPORT void UpdateGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude, const DBDouble& altitude );
    BARRELMAN_EXPORT void DeleteGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGNSSDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateGNSSDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteGNSSDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGNSSDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void UpdateGNSSDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void DeleteGNSSDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGNSSDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, double defaultLatitude, double defaultLongitude, double defaultAltitude, double latitudeOffset, double longitudeOffset, double altitudeOffset );
    BARRELMAN_EXPORT void UpdateGNSSDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, double defaultLatitude, double defaultLongitude, double defaultAltitude, double latitudeOffset, double longitudeOffset, double altitudeOffset );
    BARRELMAN_EXPORT void DeleteGNSSDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGuidTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBGuid& value );
    BARRELMAN_EXPORT void UpdateGuidTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBGuid& value );
    BARRELMAN_EXPORT void DeleteGuidTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateGyroDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteGyroDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void UpdateGyroDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void DeleteGyroDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, double defaultHeadingTrueNorth, double defaultMagneticTrueNorth, double headingTrueNorthOffset, double headingMagneticNorthOffset, FixedDBWideString<64> pitchTransducerName, FixedDBWideString<64> rollTransducerName );
    BARRELMAN_EXPORT void UpdateGyroDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, double defaultHeadingTrueNorth, double defaultMagneticTrueNorth, double headingTrueNorthOffset, double headingMagneticNorthOffset, FixedDBWideString<64> pitchTransducerName, FixedDBWideString<64> rollTransducerName );
    BARRELMAN_EXPORT void DeleteGyroDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCallsign( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> identifier );
    BARRELMAN_EXPORT void UpdateCallsign( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> identifier );
    BARRELMAN_EXPORT void DeleteCallsign( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, Guid& id, Int64 identifier );
    BARRELMAN_EXPORT void UpdateInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 identifier );
    BARRELMAN_EXPORT void DeleteInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMaritimeMobileServiceIdentity( const ODBC::Connection& connection, Guid& id, Int64 identifier );
    BARRELMAN_EXPORT void UpdateMaritimeMobileServiceIdentity( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 identifier );
    BARRELMAN_EXPORT void DeleteMaritimeMobileServiceIdentity( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertName( const ODBC::Connection& connection, Guid& id, FixedDBWideString<100> text );
    BARRELMAN_EXPORT void UpdateName( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<100> text );
    BARRELMAN_EXPORT void DeleteName( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt16TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt16& value );
    BARRELMAN_EXPORT void UpdateInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt16& value );
    BARRELMAN_EXPORT void DeleteInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt32TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt32& value );
    BARRELMAN_EXPORT void UpdateInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt32& value );
    BARRELMAN_EXPORT void DeleteInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt64TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value );
    BARRELMAN_EXPORT void UpdateInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value );
    BARRELMAN_EXPORT void DeleteInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBaseStation( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& type );
    BARRELMAN_EXPORT void UpdateBaseStation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& type );
    BARRELMAN_EXPORT void DeleteBaseStation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCameraDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void UpdateCameraDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void DeleteCameraDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGNSSDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& altitudeTimeseries );
    BARRELMAN_EXPORT void UpdateGNSSDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& altitudeTimeseries );
    BARRELMAN_EXPORT void DeleteGNSSDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& headingTrueNorthTimeseries, const Guid& headingMagneticNorthTimeseries, const Guid& pitchTimeseries, const Guid& rateOfTurnTimeseries, const Guid& rollTimeseries, const Guid& courseTimeseries, const Guid& speedTimeseries, const Guid& gNSSDevice );
    BARRELMAN_EXPORT void UpdateGyroDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& headingTrueNorthTimeseries, const Guid& headingMagneticNorthTimeseries, const Guid& pitchTimeseries, const Guid& rateOfTurnTimeseries, const Guid& rollTimeseries, const Guid& courseTimeseries, const Guid& speedTimeseries, const Guid& gNSSDevice );
    BARRELMAN_EXPORT void DeleteGyroDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLineInputDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void UpdateLineInputDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void DeleteLineInputDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertOilSpillDetectorDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void UpdateOilSpillDetectorDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void DeleteOilSpillDetectorDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadioDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void UpdateRadioDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void DeleteRadioDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadomeDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const DBGuid& radar, const Guid& pressureTimeseries, const Guid& temperatureTimeseries, const Guid& dewPointTimeseries, const Guid& statusTimeseries );
    BARRELMAN_EXPORT void UpdateRadomeDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const DBGuid& radar, const Guid& pressureTimeseries, const Guid& temperatureTimeseries, const Guid& dewPointTimeseries, const Guid& statusTimeseries );
    BARRELMAN_EXPORT void DeleteRadomeDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void UpdateAisDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void DeleteAisDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& saveSettingsTimeseries, const Guid& powerOnTimeseries, const Guid& trackingOnTimeseries, const Guid& radarPulseTimeseries, const Guid& tuningTimeseries, const Guid& blankSector1Timeseries, const Guid& sector1StartTimeseries, const Guid& sector1EndTimeseries, const Guid& blankSector2Timeseries, const Guid& sector2StartTimeseries, const Guid& sector2EndTimeseries, const Guid& enableAutomaticFrequencyControlTimeseries, const Guid& azimuthOffsetTimeseries, const Guid& enableSensitivityTimeControlTimeseries, const Guid& automaticSensitivityTimeControlTimeseries, const Guid& sensitivityTimeControlLevelTimeseries, const Guid& enableFastTimeConstantTimeseries, const Guid& fastTimeConstantLevelTimeseries, const Guid& fastTimeConstantModeTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const DBGuid& radome, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT void UpdateRadarDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& saveSettingsTimeseries, const Guid& powerOnTimeseries, const Guid& trackingOnTimeseries, const Guid& radarPulseTimeseries, const Guid& tuningTimeseries, const Guid& blankSector1Timeseries, const Guid& sector1StartTimeseries, const Guid& sector1EndTimeseries, const Guid& blankSector2Timeseries, const Guid& sector2StartTimeseries, const Guid& sector2EndTimeseries, const Guid& enableAutomaticFrequencyControlTimeseries, const Guid& azimuthOffsetTimeseries, const Guid& enableSensitivityTimeControlTimeseries, const Guid& automaticSensitivityTimeControlTimeseries, const Guid& sensitivityTimeControlLevelTimeseries, const Guid& enableFastTimeConstantTimeseries, const Guid& fastTimeConstantLevelTimeseries, const Guid& fastTimeConstantModeTimeseries, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const DBGuid& radome, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT void DeleteRadarDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& barometricPressureTimeseries, const Guid& airTemperatureTimeseries, const Guid& waterTemperatureTimeseries, const Guid& relativeHumidityTimeseries, const Guid& absoluteHumidityTimeseries, const Guid& dewPointTimeseries, const Guid& windDirectionTimeseries, const Guid& windSpeedTimeseries, const Guid& gyro );
    BARRELMAN_EXPORT void UpdateWeatherStationDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, FixedDBWideString<127> name, const WideString& description, const Guid& enabledTimeseries, const Guid& barometricPressureTimeseries, const Guid& airTemperatureTimeseries, const Guid& waterTemperatureTimeseries, const Guid& relativeHumidityTimeseries, const Guid& absoluteHumidityTimeseries, const Guid& dewPointTimeseries, const Guid& windDirectionTimeseries, const Guid& windSpeedTimeseries, const Guid& gyro );
    BARRELMAN_EXPORT void DeleteWeatherStationDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertFacility( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& type, double longitude, double latitude, double altitude );
    BARRELMAN_EXPORT void UpdateFacility( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& type, double longitude, double latitude, double altitude );
    BARRELMAN_EXPORT void DeleteFacility( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAircraft( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& type );
    BARRELMAN_EXPORT void UpdateAircraft( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& type );
    BARRELMAN_EXPORT void DeleteAircraft( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisAidToNavigation( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& mMSI, Data::NavigationalAidType navigationalAidType, const Guid& position, bool isVirtual, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& offPositionTimeseries );
    BARRELMAN_EXPORT void UpdateAisAidToNavigation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& mMSI, Data::NavigationalAidType navigationalAidType, const Guid& position, bool isVirtual, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& offPositionTimeseries );
    BARRELMAN_EXPORT void DeleteAisAidToNavigation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertVehicle( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& type );
    BARRELMAN_EXPORT void UpdateVehicle( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& type );
    BARRELMAN_EXPORT void DeleteVehicle( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertVessel( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& type, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& draughtTimeseries, const Guid& personsOnBoardTimeseries );
    BARRELMAN_EXPORT void UpdateVessel( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& type, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const Guid& draughtTimeseries, const Guid& personsOnBoardTimeseries );
    BARRELMAN_EXPORT void DeleteVessel( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertItemIdentityLink( const ODBC::Connection& connection, Guid& id, const Guid& item, const Guid& identity, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void UpdateItemIdentityLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, const Guid& identity, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void DeleteItemIdentityLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertItemParentChildLink( const ODBC::Connection& connection, Guid& id, const Guid& parent, const Guid& child, const DateTime& timestamp );
    BARRELMAN_EXPORT void UpdateItemParentChildLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& parent, const Guid& child, const DateTime& timestamp );
    BARRELMAN_EXPORT void DeleteItemParentChildLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLineInputDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateLineInputDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteLineInputDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLineInputDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void UpdateLineInputDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void DeleteLineInputDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLineInputDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages, bool nMEA, bool strictNMEA, Data::LineInputDeviceConnectionType connectionType, Int32 udpReceivePort, FixedDBWideString<100> udpSendHostname, Int32 udpSendPort, FixedDBWideString<100> tcpHostname, Int32 tcpPort, bool useHttpLogin, FixedDBWideString<100> loginHostname, Int32 loginPort, FixedDBWideString<100> userName, FixedDBWideString<100> password, FixedDBWideString<100> comPort, Int32 baudRate, Int32 dataBits, bool discardNull, bool dtrEnable, Data::Handshake handshake, FixedDBWideString<100> newLine, Data::Parity parity, Byte parityReplace, Int32 readBufferSize, const TimeSpan& readTimeout, Int32 receivedBytesThreshold, bool rtsEnable, Data::StopBits stopBits, Int32 writeBufferSize, const TimeSpan& writeTimeout, FixedDBWideString<100> pairedComPort );
    BARRELMAN_EXPORT void UpdateLineInputDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages, bool nMEA, bool strictNMEA, Data::LineInputDeviceConnectionType connectionType, Int32 udpReceivePort, FixedDBWideString<100> udpSendHostname, Int32 udpSendPort, FixedDBWideString<100> tcpHostname, Int32 tcpPort, bool useHttpLogin, FixedDBWideString<100> loginHostname, Int32 loginPort, FixedDBWideString<100> userName, FixedDBWideString<100> password, FixedDBWideString<100> comPort, Int32 baudRate, Int32 dataBits, bool discardNull, bool dtrEnable, Data::Handshake handshake, FixedDBWideString<100> newLine, Data::Parity parity, Byte parityReplace, Int32 readBufferSize, const TimeSpan& readTimeout, Int32 receivedBytesThreshold, bool rtsEnable, Data::StopBits stopBits, Int32 writeBufferSize, const TimeSpan& writeTimeout, FixedDBWideString<100> pairedComPort );
    BARRELMAN_EXPORT void DeleteLineInputDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLineInputMessageRouting( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, FixedDBWideString<100> type );
    BARRELMAN_EXPORT void UpdateLineInputMessageRouting( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, FixedDBWideString<100> type );
    BARRELMAN_EXPORT void DeleteLineInputMessageRouting( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLineInputMessageRoutingDestination( const ODBC::Connection& connection, Guid& id, const Guid& routing, const Guid& listener );
    BARRELMAN_EXPORT void UpdateLineInputMessageRoutingDestination( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& routing, const Guid& listener );
    BARRELMAN_EXPORT void DeleteLineInputMessageRoutingDestination( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLineInputWhiteListEntry( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, FixedDBWideString<128> hostName, Int32 port );
    BARRELMAN_EXPORT void UpdateLineInputWhiteListEntry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, FixedDBWideString<128> hostName, Int32 port );
    BARRELMAN_EXPORT void DeleteLineInputWhiteListEntry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLogApplication( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void UpdateLogApplication( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void DeleteLogApplication( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLogApplicationConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& application, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency );
    BARRELMAN_EXPORT void UpdateLogApplicationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& application, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency );
    BARRELMAN_EXPORT void DeleteLogApplicationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLogHost( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> computerName, const WideString& description );
    BARRELMAN_EXPORT void UpdateLogHost( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> computerName, const WideString& description );
    BARRELMAN_EXPORT void DeleteLogHost( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLogHostConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& host, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency );
    BARRELMAN_EXPORT void UpdateLogHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency );
    BARRELMAN_EXPORT void DeleteLogHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLogLocation( const ODBC::Connection& connection, Guid& id, FixedDBWideString<260> fileName, Int32 lineNumber, const WideString& namespace__, const WideString& className, FixedDBWideString<255> methodName );
    BARRELMAN_EXPORT void UpdateLogLocation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<260> fileName, Int32 lineNumber, const WideString& namespace__, const WideString& className, FixedDBWideString<255> methodName );
    BARRELMAN_EXPORT void DeleteLogLocation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLogProcess( const ODBC::Connection& connection, Guid& id, const Guid& application, const Guid& host, const DateTime& started, const DBDateTime& stopped, Int64 processId, const WideString& path, FixedDBWideString<127> identity );
    BARRELMAN_EXPORT void UpdateLogProcess( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& application, const Guid& host, const DateTime& started, const DBDateTime& stopped, Int64 processId, const WideString& path, FixedDBWideString<127> identity );
    BARRELMAN_EXPORT void DeleteLogProcess( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLogRecord( const ODBC::Connection& connection, Guid& id, const Guid& thread, Int64 sequenceNumber, Data::LogLevel level, const DateTime& timestamp, Int32 depth, const Guid& location, const WideString& message, const WideString& exceptionString, const Binary& propertiesData );
    BARRELMAN_EXPORT void UpdateLogRecord( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& thread, Int64 sequenceNumber, Data::LogLevel level, const DateTime& timestamp, Int32 depth, const Guid& location, const WideString& message, const WideString& exceptionString, const Binary& propertiesData );
    BARRELMAN_EXPORT void DeleteLogRecord( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLogThread( const ODBC::Connection& connection, Guid& id, const Guid& process, const DateTime& started, const DBDateTime& stopped, Int64 threadId, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void UpdateLogThread( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& process, const DateTime& started, const DBDateTime& stopped, Int64 threadId, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void DeleteLogThread( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertLogTraceEntry( const ODBC::Connection& connection, Guid& id, const Guid& thread, Int64 sequenceNumber, const Guid& location, Int32 depth, const DateTime& entered, const DBDateTime& ended );
    BARRELMAN_EXPORT void UpdateLogTraceEntry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& thread, Int64 sequenceNumber, const Guid& location, Int32 depth, const DateTime& entered, const DBDateTime& ended );
    BARRELMAN_EXPORT void DeleteLogTraceEntry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMapElement( const ODBC::Connection& connection, Guid& id, const Guid& item, Data::MapElementType elementType, double latitude, double longitude, double angle, double left, double top, double width, double height, FixedDBWideString<100> label, const Binary& data );
    BARRELMAN_EXPORT void UpdateMapElement( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, Data::MapElementType elementType, double latitude, double longitude, double angle, double left, double top, double width, double height, FixedDBWideString<100> label, const Binary& data );
    BARRELMAN_EXPORT void DeleteMapElement( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMapInfo( const ODBC::Connection& connection, Guid& id, Int32 scale, double latitude, double longitude, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, const Binary& image );
    BARRELMAN_EXPORT void UpdateMapInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 scale, double latitude, double longitude, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, const Binary& image );
    BARRELMAN_EXPORT void DeleteMapInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMapServiceOptions( const ODBC::Connection& connection, Guid& id, const DateTime& timestamp, FixedDBWideString<127> ipAddress, Int32 port, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY );
    BARRELMAN_EXPORT void UpdateMapServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DateTime& timestamp, FixedDBWideString<127> ipAddress, Int32 port, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY );
    BARRELMAN_EXPORT void DeleteMapServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMaritimeIdentificationDigits( const ODBC::Connection& connection, Guid& id, Int32 code, const Guid& country );
    BARRELMAN_EXPORT void UpdateMaritimeIdentificationDigits( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 code, const Guid& country );
    BARRELMAN_EXPORT void DeleteMaritimeIdentificationDigits( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMediaProxySession( const ODBC::Connection& connection, Guid& id, const Guid& service, FixedDBWideString<128> name, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void UpdateMediaProxySession( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& service, FixedDBWideString<128> name, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void DeleteMediaProxySession( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMediaProxySessionFile( const ODBC::Connection& connection, Guid& id, const Guid& proxySession, const DateTime& timestamp, FixedDBWideString<100> streamName );
    BARRELMAN_EXPORT void UpdateMediaProxySessionFile( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& proxySession, const DateTime& timestamp, FixedDBWideString<100> streamName );
    BARRELMAN_EXPORT void DeleteMediaProxySessionFile( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMediaProxySessionOptions( const ODBC::Connection& connection, Guid& id, const Guid& proxySession, const DateTime& timestamp, FixedDBWideString<255> sourceStreamUrl, FixedDBWideString<255> streamName, Data::MediaProxySessionMode mode, Int32 tunnelOverHTTPPortNumber, FixedDBWideString<128> username, FixedDBWideString<128> password, Int32 recorderPortNumber, Data::MediaProxySessionType sessionType, const TimeSpan& maxFileTime, const TimeSpan& maxFileRetention, FixedDBWideString<260> videoDirectory );
    BARRELMAN_EXPORT void UpdateMediaProxySessionOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& proxySession, const DateTime& timestamp, FixedDBWideString<255> sourceStreamUrl, FixedDBWideString<255> streamName, Data::MediaProxySessionMode mode, Int32 tunnelOverHTTPPortNumber, FixedDBWideString<128> username, FixedDBWideString<128> password, Int32 recorderPortNumber, Data::MediaProxySessionType sessionType, const TimeSpan& maxFileTime, const TimeSpan& maxFileRetention, FixedDBWideString<260> videoDirectory );
    BARRELMAN_EXPORT void DeleteMediaProxySessionOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMediaService( const ODBC::Connection& connection, Guid& id, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void UpdateMediaService( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& enabledTimeseries );
    BARRELMAN_EXPORT void DeleteMediaService( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMediaServiceOptions( const ODBC::Connection& connection, Guid& id, const Guid& mediaService, const DateTime& timestamp, Int32 rtspPortNumber, Int32 httpPortNumber );
    BARRELMAN_EXPORT void UpdateMediaServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& mediaService, const DateTime& timestamp, Int32 rtspPortNumber, Int32 httpPortNumber );
    BARRELMAN_EXPORT void DeleteMediaServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertElementType( const ODBC::Connection& connection, Guid& id, const Guid& namespace__, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void UpdateElementType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& namespace__, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void DeleteElementType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertNamespace( const ODBC::Connection& connection, Guid& id, const Guid& namespace__, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void UpdateNamespace( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& namespace__, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void DeleteNamespace( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertOilSpill( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, double oilArea, const Binary& shape, const Binary& bSI, const Binary& oil, const Binary& trace );
    BARRELMAN_EXPORT void UpdateOilSpill( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, double oilArea, const Binary& shape, const Binary& bSI, const Binary& oil, const Binary& trace );
    BARRELMAN_EXPORT void DeleteOilSpill( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertOilSpillDetectorCommand( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateOilSpillDetectorCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteOilSpillDetectorCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertOilSpillDetectorCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void UpdateOilSpillDetectorCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void DeleteOilSpillDetectorCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertOilSpillDetectorConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, double range, double startAngle, double endAngle, double startRange, double endRange, Int32 updateRate, const TimeSpan& statusSendTime, bool drawBorder, const Binary& colors, bool sendToServer, FixedDBWideString<100> directory, bool transparentWater, bool savePictures, bool sendAsTarget, bool writeLog, FixedDBWideString<100> targetFilePrefix, const Guid& targetMMSI, double latitude, double longitude, bool testSourceEnabled, FixedDBWideString<100> proxyServer, bool useProxyServer );
    BARRELMAN_EXPORT void UpdateOilSpillDetectorConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, double range, double startAngle, double endAngle, double startRange, double endRange, Int32 updateRate, const TimeSpan& statusSendTime, bool drawBorder, const Binary& colors, bool sendToServer, FixedDBWideString<100> directory, bool transparentWater, bool savePictures, bool sendAsTarget, bool writeLog, FixedDBWideString<100> targetFilePrefix, const Guid& targetMMSI, double latitude, double longitude, bool testSourceEnabled, FixedDBWideString<100> proxyServer, bool useProxyServer );
    BARRELMAN_EXPORT void DeleteOilSpillDetectorConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertPosition2DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y );
    BARRELMAN_EXPORT void UpdatePosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y );
    BARRELMAN_EXPORT void DeletePosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertPosition3DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y, const DBDouble& z );
    BARRELMAN_EXPORT void UpdatePosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y, const DBDouble& z );
    BARRELMAN_EXPORT void DeletePosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertProcessTrackValueResult( const ODBC::Connection& connection, Guid& id, bool createdNewTrack, const Guid& trackId );
    BARRELMAN_EXPORT void UpdateProcessTrackValueResult( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, bool createdNewTrack, const Guid& trackId );
    BARRELMAN_EXPORT void DeleteProcessTrackValueResult( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBinaryProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Binary& value );
    BARRELMAN_EXPORT void UpdateBinaryProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Binary& value );
    BARRELMAN_EXPORT void DeleteBinaryProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBooleanProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, bool value );
    BARRELMAN_EXPORT void UpdateBooleanProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, bool value );
    BARRELMAN_EXPORT void DeleteBooleanProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertByteProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Byte value );
    BARRELMAN_EXPORT void UpdateByteProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Byte value );
    BARRELMAN_EXPORT void DeleteByteProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDateTimeProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DateTime& value );
    BARRELMAN_EXPORT void UpdateDateTimeProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DateTime& value );
    BARRELMAN_EXPORT void DeleteDateTimeProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDoubleProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, double value );
    BARRELMAN_EXPORT void UpdateDoubleProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, double value );
    BARRELMAN_EXPORT void DeleteDoubleProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGuidProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& value );
    BARRELMAN_EXPORT void UpdateGuidProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& value );
    BARRELMAN_EXPORT void DeleteGuidProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt16Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int16 value );
    BARRELMAN_EXPORT void UpdateInt16Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int16 value );
    BARRELMAN_EXPORT void DeleteInt16Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt32Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int32 value );
    BARRELMAN_EXPORT void UpdateInt32Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int32 value );
    BARRELMAN_EXPORT void DeleteInt32Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt64Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int64 value );
    BARRELMAN_EXPORT void UpdateInt64Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int64 value );
    BARRELMAN_EXPORT void DeleteInt64Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertReferenceProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& value );
    BARRELMAN_EXPORT void UpdateReferenceProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& value );
    BARRELMAN_EXPORT void DeleteReferenceProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSByteProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, SByte value );
    BARRELMAN_EXPORT void UpdateSByteProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, SByte value );
    BARRELMAN_EXPORT void DeleteSByteProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSingleProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, float value );
    BARRELMAN_EXPORT void UpdateSingleProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, float value );
    BARRELMAN_EXPORT void DeleteSingleProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertStringProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, FixedDBWideString<100> value );
    BARRELMAN_EXPORT void UpdateStringProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, FixedDBWideString<100> value );
    BARRELMAN_EXPORT void DeleteStringProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBinaryTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateBinaryTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteBinaryTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBooleanTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateBooleanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteBooleanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertByteTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDateTimeTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateDateTimeTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteDateTimeTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDoubleTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateDoubleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteDoubleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGuidTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateGuidTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteGuidTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt16TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt32TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt64TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertReferenceTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateReferenceTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteReferenceTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSByteTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateSByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteSByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSingleTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateSingleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteSingleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertStringTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateStringTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteStringTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTimeSpanTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateTimeSpanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteTimeSpanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt16TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateUInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteUInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt32TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateUInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteUInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt64TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void UpdateUInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& timeseries );
    BARRELMAN_EXPORT void DeleteUInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTimeSpanProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const TimeSpan& value );
    BARRELMAN_EXPORT void UpdateTimeSpanProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const TimeSpan& value );
    BARRELMAN_EXPORT void DeleteTimeSpanProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt16Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, UInt16 value );
    BARRELMAN_EXPORT void UpdateUInt16Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, UInt16 value );
    BARRELMAN_EXPORT void DeleteUInt16Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt32Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, UInt32 value );
    BARRELMAN_EXPORT void UpdateUInt32Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, UInt32 value );
    BARRELMAN_EXPORT void DeleteUInt32Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt64Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int64 value );
    BARRELMAN_EXPORT void UpdateUInt64Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int64 value );
    BARRELMAN_EXPORT void DeleteUInt64Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBinaryPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Binary& defaultValue );
    BARRELMAN_EXPORT void UpdateBinaryPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Binary& defaultValue );
    BARRELMAN_EXPORT void DeleteBinaryPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBooleanPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, bool defaultValue );
    BARRELMAN_EXPORT void UpdateBooleanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, bool defaultValue );
    BARRELMAN_EXPORT void DeleteBooleanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBytePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Byte defaultValue, Byte minValue, Byte maxValue );
    BARRELMAN_EXPORT void UpdateBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Byte defaultValue, Byte minValue, Byte maxValue );
    BARRELMAN_EXPORT void DeleteBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDateTimePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> defaultValue, FixedDBWideString<100> minValue, FixedDBWideString<100> maxValue );
    BARRELMAN_EXPORT void UpdateDateTimePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> defaultValue, FixedDBWideString<100> minValue, FixedDBWideString<100> maxValue );
    BARRELMAN_EXPORT void DeleteDateTimePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDoublePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, double defaultValue, double minValue, double maxValue );
    BARRELMAN_EXPORT void UpdateDoublePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, double defaultValue, double minValue, double maxValue );
    BARRELMAN_EXPORT void DeleteDoublePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGuidPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& defaultValue );
    BARRELMAN_EXPORT void UpdateGuidPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& defaultValue );
    BARRELMAN_EXPORT void DeleteGuidPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt16PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int16 defaultValue, Int16 minValue, Int16 maxValue );
    BARRELMAN_EXPORT void UpdateInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int16 defaultValue, Int16 minValue, Int16 maxValue );
    BARRELMAN_EXPORT void DeleteInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt32PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int32 defaultValue, Int32 minValue, Int32 maxValue );
    BARRELMAN_EXPORT void UpdateInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int32 defaultValue, Int32 minValue, Int32 maxValue );
    BARRELMAN_EXPORT void DeleteInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt64PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT void UpdateInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT void DeleteInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertReferencePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& defaultValue, const Guid& referencedElementType );
    BARRELMAN_EXPORT void UpdateReferencePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& defaultValue, const Guid& referencedElementType );
    BARRELMAN_EXPORT void DeleteReferencePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSBytePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, SByte defaultValue, SByte minValue, SByte maxValue );
    BARRELMAN_EXPORT void UpdateSBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, SByte defaultValue, SByte minValue, SByte maxValue );
    BARRELMAN_EXPORT void DeleteSBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSinglePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, float defaultValue, float minValue, float maxValue );
    BARRELMAN_EXPORT void UpdateSinglePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, float defaultValue, float minValue, float maxValue );
    BARRELMAN_EXPORT void DeleteSinglePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertStringPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> defaultValue, FixedDBWideString<100> pattern );
    BARRELMAN_EXPORT void UpdateStringPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> defaultValue, FixedDBWideString<100> pattern );
    BARRELMAN_EXPORT void DeleteStringPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void UpdateBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void DeleteBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void UpdateBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void DeleteBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Byte minValue, Byte maxValue );
    BARRELMAN_EXPORT void UpdateByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Byte minValue, Byte maxValue );
    BARRELMAN_EXPORT void DeleteByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> minValue, FixedDBWideString<100> maxValue );
    BARRELMAN_EXPORT void UpdateDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> minValue, FixedDBWideString<100> maxValue );
    BARRELMAN_EXPORT void DeleteDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, double minValue, double maxValue );
    BARRELMAN_EXPORT void UpdateDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, double minValue, double maxValue );
    BARRELMAN_EXPORT void DeleteDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void UpdateGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void DeleteGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int16 minValue, Int16 maxValue );
    BARRELMAN_EXPORT void UpdateInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int16 minValue, Int16 maxValue );
    BARRELMAN_EXPORT void DeleteInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int32 minValue, Int32 maxValue );
    BARRELMAN_EXPORT void UpdateInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int32 minValue, Int32 maxValue );
    BARRELMAN_EXPORT void DeleteInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT void UpdateInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT void DeleteInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& referencedElementType );
    BARRELMAN_EXPORT void UpdateReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const Guid& referencedElementType );
    BARRELMAN_EXPORT void DeleteReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, SByte minValue, SByte maxValue );
    BARRELMAN_EXPORT void UpdateSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, SByte minValue, SByte maxValue );
    BARRELMAN_EXPORT void DeleteSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, float minValue, float maxValue );
    BARRELMAN_EXPORT void UpdateSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, float minValue, float maxValue );
    BARRELMAN_EXPORT void DeleteSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> pattern );
    BARRELMAN_EXPORT void UpdateStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, FixedDBWideString<100> pattern );
    BARRELMAN_EXPORT void DeleteStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const TimeSpan& minValue, const TimeSpan& maxValue );
    BARRELMAN_EXPORT void UpdateTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const TimeSpan& minValue, const TimeSpan& maxValue );
    BARRELMAN_EXPORT void DeleteTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt16 minValue, UInt16 maxValue );
    BARRELMAN_EXPORT void UpdateUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt16 minValue, UInt16 maxValue );
    BARRELMAN_EXPORT void DeleteUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt32 minValue, UInt32 maxValue );
    BARRELMAN_EXPORT void UpdateUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt32 minValue, UInt32 maxValue );
    BARRELMAN_EXPORT void DeleteUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT void UpdateUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT void DeleteUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTimeSpanPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const TimeSpan& defaultValue, const TimeSpan& minValue, const TimeSpan& maxValue );
    BARRELMAN_EXPORT void UpdateTimeSpanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, const TimeSpan& defaultValue, const TimeSpan& minValue, const TimeSpan& maxValue );
    BARRELMAN_EXPORT void DeleteTimeSpanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt16PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt16 defaultValue, UInt16 minValue, UInt16 maxValue );
    BARRELMAN_EXPORT void UpdateUInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt16 defaultValue, UInt16 minValue, UInt16 maxValue );
    BARRELMAN_EXPORT void DeleteUInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt32PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt32 defaultValue, UInt32 minValue, UInt32 maxValue );
    BARRELMAN_EXPORT void UpdateUInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, UInt32 defaultValue, UInt32 minValue, UInt32 maxValue );
    BARRELMAN_EXPORT void DeleteUInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt64PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT void UpdateUInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, FixedDBWideString<127> name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT void DeleteUInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarAlarmStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Data::AlarmState type );
    BARRELMAN_EXPORT void UpdateRadarAlarmStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Data::AlarmState type );
    BARRELMAN_EXPORT void DeleteRadarAlarmStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarCommand( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateRadarCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteRadarCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarCommandGetStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateRadarCommandGetStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteRadarCommandGetStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void UpdateRadarCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void DeleteRadarCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarCommandReplyGetStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationCount, Data::RadarPulse pulse, bool tx );
    BARRELMAN_EXPORT void UpdateRadarCommandReplyGetStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationCount, Data::RadarPulse pulse, bool tx );
    BARRELMAN_EXPORT void DeleteRadarCommandReplyGetStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 radarProtocolVersion, FixedDBWideString<100> radarIPAddress, Int32 radarPort, Int32 radarConfigurationPort, const TimeSpan& skipMagicTimeout, const TimeSpan& readTimeout, const TimeSpan& synchronizationInterval, Int32 targetsRefreshRate, Int32 range, Int32 sectorCount, Int32 sectorOffset, UInt32 imageColor, const DBUInt32& imageSubstitutionColor, UInt32 transparentColor, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY, Data::RadarImageType radarImageType, UInt32 trackColor, UInt32 vectorColor, bool enableNmea, FixedDBWideString<100> nmeaReceiverIPAddress, Int32 nmeaReceiverPort, FixedDBWideString<100> nmeaReceiverSourceId );
    BARRELMAN_EXPORT void UpdateRadarConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 radarProtocolVersion, FixedDBWideString<100> radarIPAddress, Int32 radarPort, Int32 radarConfigurationPort, const TimeSpan& skipMagicTimeout, const TimeSpan& readTimeout, const TimeSpan& synchronizationInterval, Int32 targetsRefreshRate, Int32 range, Int32 sectorCount, Int32 sectorOffset, UInt32 imageColor, const DBUInt32& imageSubstitutionColor, UInt32 transparentColor, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY, Data::RadarImageType radarImageType, UInt32 trackColor, UInt32 vectorColor, bool enableNmea, FixedDBWideString<100> nmeaReceiverIPAddress, Int32 nmeaReceiverPort, FixedDBWideString<100> nmeaReceiverSourceId );
    BARRELMAN_EXPORT void DeleteRadarConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarImage( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, UInt32 depth, Int32 resolution, Int32 range, const Binary& image );
    BARRELMAN_EXPORT void UpdateRadarImage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, UInt32 depth, Int32 resolution, Int32 range, const Binary& image );
    BARRELMAN_EXPORT void DeleteRadarImage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarRawTrackTable( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 count, const Binary& table );
    BARRELMAN_EXPORT void UpdateRadarRawTrackTable( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 count, const Binary& table );
    BARRELMAN_EXPORT void DeleteRadarRawTrackTable( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationTime, Data::RadarPulse pulse, bool tx, bool tracking );
    BARRELMAN_EXPORT void UpdateRadarStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationTime, Data::RadarPulse pulse, bool tx, bool tracking );
    BARRELMAN_EXPORT void DeleteRadarStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadioCommand( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateRadioCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteRadioCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadioCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void UpdateRadioCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void DeleteRadioCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadioConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, double longitude, double latitude, FixedDBWideString<100> playbackUrl, FixedDBWideString<100> radioIPAddress, Int32 radioPort, FixedDBWideString<100> ed137IPAddress, Int32 ed137Port );
    BARRELMAN_EXPORT void UpdateRadioConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, double longitude, double latitude, FixedDBWideString<100> playbackUrl, FixedDBWideString<100> radioIPAddress, Int32 radioPort, FixedDBWideString<100> ed137IPAddress, Int32 ed137Port );
    BARRELMAN_EXPORT void DeleteRadioConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadomeCommand( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateRadomeCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteRadomeCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadomeCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void UpdateRadomeCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void DeleteRadomeCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadomeConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, const TimeSpan& interval, double lowPressureLimit, double highPressureLimit, double lowTemperatureLimit, double highTemperatureLimit );
    BARRELMAN_EXPORT void UpdateRadomeConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, const TimeSpan& interval, double lowPressureLimit, double highPressureLimit, double lowTemperatureLimit, double highTemperatureLimit );
    BARRELMAN_EXPORT void DeleteRadomeConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertReferenceTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const Guid& value );
    BARRELMAN_EXPORT void UpdateReferenceTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const Guid& value );
    BARRELMAN_EXPORT void DeleteReferenceTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSByteTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBSByte& value );
    BARRELMAN_EXPORT void UpdateSByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBSByte& value );
    BARRELMAN_EXPORT void DeleteSByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSecurityDomain( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void UpdateSecurityDomain( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const WideString& description );
    BARRELMAN_EXPORT void DeleteSecurityDomain( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSecurityLogin( const ODBC::Connection& connection, Guid& id, const Guid& domain, FixedDBWideString<255> identity, const WideString& description );
    BARRELMAN_EXPORT void UpdateSecurityLogin( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& domain, FixedDBWideString<255> identity, const WideString& description );
    BARRELMAN_EXPORT void DeleteSecurityLogin( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSecurityRole( const ODBC::Connection& connection, Guid& id, const Guid& domain, FixedDBWideString<255> identity, const WideString& description, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void UpdateSecurityRole( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& domain, FixedDBWideString<255> identity, const WideString& description, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void DeleteSecurityRole( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSecurityIdentifierRoleLink( const ODBC::Connection& connection, Guid& id, const Guid& member, const Guid& role, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void UpdateSecurityIdentifierRoleLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& member, const Guid& role, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void DeleteSecurityIdentifierRoleLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSecurityLoginSession( const ODBC::Connection& connection, Guid& id, const Guid& login, const DateTime& fromTime, const DBDateTime& throughTime, const Guid& clientSession, FixedDBWideString<260> notificationQueueName, FixedDBWideString<260> messageQueueName );
    BARRELMAN_EXPORT void UpdateSecurityLoginSession( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& login, const DateTime& fromTime, const DBDateTime& throughTime, const Guid& clientSession, FixedDBWideString<260> notificationQueueName, FixedDBWideString<260> messageQueueName );
    BARRELMAN_EXPORT void DeleteSecurityLoginSession( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSecurityPermission( const ODBC::Connection& connection, Guid& id, const Guid& identifier, const DateTime& timestamp, Int32 typeCode, bool canCreate, bool canRead, bool canUpdate, bool canDelete );
    BARRELMAN_EXPORT void UpdateSecurityPermission( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& identifier, const DateTime& timestamp, Int32 typeCode, bool canCreate, bool canRead, bool canUpdate, bool canDelete );
    BARRELMAN_EXPORT void DeleteSecurityPermission( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSingleTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBSingle& value );
    BARRELMAN_EXPORT void UpdateSingleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBSingle& value );
    BARRELMAN_EXPORT void DeleteSingleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertStringTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const WideString& value );
    BARRELMAN_EXPORT void UpdateStringTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const WideString& value );
    BARRELMAN_EXPORT void DeleteStringTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBinaryTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateBinaryTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteBinaryTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertBooleanTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateBooleanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteBooleanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& aidToNavigation );
    BARRELMAN_EXPORT void UpdateAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& aidToNavigation );
    BARRELMAN_EXPORT void DeleteAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDeviceEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& device );
    BARRELMAN_EXPORT void UpdateDeviceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& device );
    BARRELMAN_EXPORT void DeleteDeviceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarBlankSector1Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarBlankSector1Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarBlankSector1Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarBlankSector2Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarBlankSector2Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarBlankSector2Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarPowerOnTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarPowerOnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarPowerOnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarSaveSettingsTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarSaveSettingsTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarSaveSettingsTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarTrackingTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarTrackingTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarTrackingTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& proxySession );
    BARRELMAN_EXPORT void UpdateMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& proxySession );
    BARRELMAN_EXPORT void DeleteMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertMediaServiceEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& service );
    BARRELMAN_EXPORT void UpdateMediaServiceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& service );
    BARRELMAN_EXPORT void DeleteMediaServiceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertByteTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDateTimeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateDateTimeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteDateTimeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertDoubleTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateDoubleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteDoubleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGNSSAltitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice );
    BARRELMAN_EXPORT void UpdateGNSSAltitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice );
    BARRELMAN_EXPORT void DeleteGNSSAltitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGNSSLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice );
    BARRELMAN_EXPORT void UpdateGNSSLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice );
    BARRELMAN_EXPORT void DeleteGNSSLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGNSSLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice );
    BARRELMAN_EXPORT void UpdateGNSSLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gNSSDevice );
    BARRELMAN_EXPORT void DeleteGNSSLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroCourseTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void UpdateGyroCourseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void DeleteGyroCourseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void UpdateGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void DeleteGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void UpdateGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void DeleteGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroPitchTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void UpdateGyroPitchTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void DeleteGyroPitchTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroRateOfTurnTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void UpdateGyroRateOfTurnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void DeleteGyroRateOfTurnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroRollTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void UpdateGyroRollTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void DeleteGyroRollTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGyroSpeedTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void UpdateGyroSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& gyroDevice );
    BARRELMAN_EXPORT void DeleteGyroSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadomeDewPointTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome );
    BARRELMAN_EXPORT void UpdateRadomeDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome );
    BARRELMAN_EXPORT void DeleteRadomeDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadomePressureTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome );
    BARRELMAN_EXPORT void UpdateRadomePressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome );
    BARRELMAN_EXPORT void DeleteRadomePressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadomeTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome );
    BARRELMAN_EXPORT void UpdateRadomeTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome );
    BARRELMAN_EXPORT void DeleteRadomeTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertVesselDraughtTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& vessel );
    BARRELMAN_EXPORT void UpdateVesselDraughtTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& vessel );
    BARRELMAN_EXPORT void DeleteVesselDraughtTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertViewLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view );
    BARRELMAN_EXPORT void UpdateViewLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view );
    BARRELMAN_EXPORT void DeleteViewLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertViewLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view );
    BARRELMAN_EXPORT void UpdateViewLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view );
    BARRELMAN_EXPORT void DeleteViewLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertViewZoomLevelTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view );
    BARRELMAN_EXPORT void UpdateViewZoomLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& view );
    BARRELMAN_EXPORT void DeleteViewZoomLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void UpdateWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void DeleteWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void UpdateWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void DeleteWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void UpdateWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void DeleteWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationDewPointTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void UpdateWeatherStationDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void DeleteWeatherStationDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void UpdateWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void DeleteWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void UpdateWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void DeleteWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void UpdateWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void DeleteWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void UpdateWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& weatherStation );
    BARRELMAN_EXPORT void DeleteWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGeoPosition2DTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateGeoPosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteGeoPosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& aidToNavigation );
    BARRELMAN_EXPORT void UpdateAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& aidToNavigation );
    BARRELMAN_EXPORT void DeleteAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGeoPosition3DTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateGeoPosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteGeoPosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertGuidTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateGuidTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteGuidTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt16Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt32Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarPulseTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarPulseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarPulseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarSector1EndTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarSector1EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarSector1EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarSector1StartTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarSector1StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarSector1StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarSector2EndTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarSector2EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarSector2EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarSector2StartTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarSector2StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarSector2StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadarTuningTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void UpdateRadarTuningTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radar );
    BARRELMAN_EXPORT void DeleteRadarTuningTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& vessel );
    BARRELMAN_EXPORT void UpdateVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& vessel );
    BARRELMAN_EXPORT void DeleteVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertInt64Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertPosition2DTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdatePosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeletePosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertPosition3DTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdatePosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeletePosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertReferenceTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateReferenceTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteReferenceTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSByteTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateSByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteSByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertSingleTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateSingleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteSingleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertStringTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateStringTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteStringTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTimeSpanTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateTimeSpanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteTimeSpanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt16Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateUInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteUInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt32Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateUInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteUInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertRadomeStatusTimeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome );
    BARRELMAN_EXPORT void UpdateRadomeStatusTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention, const Guid& radome );
    BARRELMAN_EXPORT void DeleteRadomeStatusTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt64Timeseries( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void UpdateUInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT void DeleteUInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTimeseriesCatalog( const ODBC::Connection& connection, Guid& id, const Guid& catalog, FixedDBWideString<100> name );
    BARRELMAN_EXPORT void UpdateTimeseriesCatalog( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& catalog, FixedDBWideString<100> name );
    BARRELMAN_EXPORT void DeleteTimeseriesCatalog( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTimeseriesInfo( const ODBC::Connection& connection, Guid& id, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count );
    BARRELMAN_EXPORT void UpdateTimeseriesInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count );
    BARRELMAN_EXPORT void DeleteTimeseriesInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTimeSpanTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBTimeSpan& value );
    BARRELMAN_EXPORT void UpdateTimeSpanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBTimeSpan& value );
    BARRELMAN_EXPORT void DeleteTimeSpanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTrackableItemTrackLink( const ODBC::Connection& connection, Guid& id, const Guid& item, const Guid& track, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void UpdateTrackableItemTrackLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, const Guid& track, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void DeleteTrackableItemTrackLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTrack( const ODBC::Connection& connection, Guid& id, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp );
    BARRELMAN_EXPORT void UpdateTrack( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp );
    BARRELMAN_EXPORT void DeleteTrack( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTrack3D( const ODBC::Connection& connection, Guid& id, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp );
    BARRELMAN_EXPORT void UpdateTrack3D( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp );
    BARRELMAN_EXPORT void DeleteTrack3D( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTrackerFilterParameters( const ODBC::Connection& connection, Guid& id, const Guid& tracker, FixedDBWideString<100> name );
    BARRELMAN_EXPORT void UpdateTrackerFilterParameters( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, FixedDBWideString<100> name );
    BARRELMAN_EXPORT void DeleteTrackerFilterParameters( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTrackerFilterParametersConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& parameters, const DateTime& timestamp, bool useNaivePredictor, Int32 numberOfPoints, Int32 windowSize, Int32 stabilizeCount, Int32 maxBadPoints, Data::TrackerFilterModelType modelType, double sigmaR, double sigmaAcc, double tauVel, double tauAcc, double deltaRMin, double deltaVMax, double deltaAMax );
    BARRELMAN_EXPORT void UpdateTrackerFilterParametersConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& parameters, const DateTime& timestamp, bool useNaivePredictor, Int32 numberOfPoints, Int32 windowSize, Int32 stabilizeCount, Int32 maxBadPoints, Data::TrackerFilterModelType modelType, double sigmaR, double sigmaAcc, double tauVel, double tauAcc, double deltaRMin, double deltaVMax, double deltaAMax );
    BARRELMAN_EXPORT void DeleteTrackerFilterParametersConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTrackInfo( const ODBC::Connection& connection, Guid& id, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count, const DBDouble& northWestLatitude, const DBDouble& northWestLongitude, const DBDouble& southEastLatitude, const DBDouble& southEastLongitude );
    BARRELMAN_EXPORT void UpdateTrackInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count, const DBDouble& northWestLatitude, const DBDouble& northWestLongitude, const DBDouble& southEastLatitude, const DBDouble& southEastLongitude );
    BARRELMAN_EXPORT void DeleteTrackInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTrackingServiceOptions( const ODBC::Connection& connection, Guid& id, const DateTime& timestamp, const TimeSpan& timerInterval, const TimeSpan& maxAgeOfCurrentTrackValue, double falseThreshold, double distanceThreshold, double distanceUnmergeThreshold, Int64 unmergeLatency, bool kalmanFiltering, double maxCourseDeviation, double maxSpeedDeviation, double minimumSpeedThreshold );
    BARRELMAN_EXPORT void UpdateTrackingServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DateTime& timestamp, const TimeSpan& timerInterval, const TimeSpan& maxAgeOfCurrentTrackValue, double falseThreshold, double distanceThreshold, double distanceUnmergeThreshold, Int64 unmergeLatency, bool kalmanFiltering, double maxCourseDeviation, double maxSpeedDeviation, double minimumSpeedThreshold );
    BARRELMAN_EXPORT void DeleteTrackingServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTrackLink( const ODBC::Connection& connection, Guid& id, const Guid& primary, const Guid& secondary, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void UpdateTrackLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& primary, const Guid& secondary, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void DeleteTrackLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTrackValue( const ODBC::Connection& connection, Guid& id, const Guid& track, const DateTime& timestamp, Data::TrackFlags flags, Data::TrackStatus status, double latitude, double longitude, double speed, double course, double heading );
    BARRELMAN_EXPORT void UpdateTrackValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const DateTime& timestamp, Data::TrackFlags flags, Data::TrackStatus status, double latitude, double longitude, double speed, double course, double heading );
    BARRELMAN_EXPORT void DeleteTrackValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertTrackValue3D( const ODBC::Connection& connection, Guid& id, const Guid& track, const DateTime& timestamp, Data::TrackFlags3D flags, UInt32 status, double latitude, double longitude, double altitude, double speed, double course, double rateOfClimb );
    BARRELMAN_EXPORT void UpdateTrackValue3D( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const DateTime& timestamp, Data::TrackFlags3D flags, UInt32 status, double latitude, double longitude, double altitude, double speed, double course, double rateOfClimb );
    BARRELMAN_EXPORT void DeleteTrackValue3D( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt16TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBUInt16& value );
    BARRELMAN_EXPORT void UpdateUInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBUInt16& value );
    BARRELMAN_EXPORT void DeleteUInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt32TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBUInt32& value );
    BARRELMAN_EXPORT void UpdateUInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBUInt32& value );
    BARRELMAN_EXPORT void DeleteUInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertUInt64TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value );
    BARRELMAN_EXPORT void UpdateUInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value );
    BARRELMAN_EXPORT void DeleteUInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertVehicleType( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void UpdateVehicleType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name );
    BARRELMAN_EXPORT void DeleteVehicleType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertVesselType( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, Int32 code );
    BARRELMAN_EXPORT void UpdateVesselType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, Int32 code );
    BARRELMAN_EXPORT void DeleteVesselType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertView( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& zoomLevelTimeseries );
    BARRELMAN_EXPORT void UpdateView( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, const Guid& latitudeTimeseries, const Guid& longitudeTimeseries, const Guid& zoomLevelTimeseries );
    BARRELMAN_EXPORT void DeleteView( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertViewCameraLink( const ODBC::Connection& connection, Guid& id, const Guid& view, const Guid& camera, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void UpdateViewCameraLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, const Guid& camera, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void DeleteViewCameraLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertViewTrackerLink( const ODBC::Connection& connection, Guid& id, const Guid& view, const Guid& tracker, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void UpdateViewTrackerLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, const Guid& tracker, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT void DeleteViewTrackerLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationCommand( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void UpdateWeatherStationCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, Data::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const Guid& reply );
    BARRELMAN_EXPORT void DeleteWeatherStationCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void UpdateWeatherStationCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, const Guid& command, Data::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT void DeleteWeatherStationCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertWeatherStationConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, const TimeSpan& noDataTimeOut, const TimeSpan& sendInterval, double latitude, double longitude, double gyroOffset, bool enableAveraging, const TimeSpan& averagingInterval );
    BARRELMAN_EXPORT void UpdateWeatherStationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, const TimeSpan& noDataTimeOut, const TimeSpan& sendInterval, double latitude, double longitude, double gyroOffset, bool enableAveraging, const TimeSpan& averagingInterval );
    BARRELMAN_EXPORT void DeleteWeatherStationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertCircularZone( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, double radius );
    BARRELMAN_EXPORT void UpdateCircularZone( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, double radius );
    BARRELMAN_EXPORT void DeleteCircularZone( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertPolygonZone( const ODBC::Connection& connection, Guid& id, FixedDBWideString<127> name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, const Binary& polygon );
    BARRELMAN_EXPORT void UpdatePolygonZone( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, FixedDBWideString<127> name, double longitude, double latitude, Data::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, const Binary& polygon );
    BARRELMAN_EXPORT void DeletePolygonZone( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertZoneExceptions( const ODBC::Connection& connection, Guid& id, const Guid& zone, const DateTime& timestamp );
    BARRELMAN_EXPORT void UpdateZoneExceptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zone, const DateTime& timestamp );
    BARRELMAN_EXPORT void DeleteZoneExceptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertZoneExceptionsVesselLink( const ODBC::Connection& connection, Guid& id, const Guid& zoneExceptions, const Guid& vessel );
    BARRELMAN_EXPORT void UpdateZoneExceptionsVesselLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zoneExceptions, const Guid& vessel );
    BARRELMAN_EXPORT void DeleteZoneExceptionsVesselLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT void InsertZoneTrackAlarm( const ODBC::Connection& connection, Guid& id, const Guid& track, const Guid& zone, const Guid& radarTrack, const DateTime& timestamp, double latitude, double longitude, double speed, const DBDouble& course, const DBDouble& heading, double enterLatitude, double enterLongitude, const DBDouble& leaveLatitude, const DBDouble& leaveLongitude );
    BARRELMAN_EXPORT void UpdateZoneTrackAlarm( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const Guid& zone, const Guid& radarTrack, const DateTime& timestamp, double latitude, double longitude, double speed, const DBDouble& course, const DBDouble& heading, double enterLatitude, double enterLongitude, const DBDouble& leaveLatitude, const DBDouble& leaveLongitude );
    BARRELMAN_EXPORT void DeleteZoneTrackAlarm( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

}
#endif
