#pragma once
#ifndef DATABASE_STOREDPROCEDURES_H_
#define DATABASE_STOREDPROCEDURES_H_

#include <HODBC.h>
#include <HCCData.h>
#include "Types/DataTypes.h"


namespace Barrelman::Database
{
    using namespace Harlinn;
    using namespace Harlinn::ODBC;
    using namespace Harlinn::Common::Core;

    BARRELMAN_EXPORT bool InsertAircraftType( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool UpdateAircraftType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool DeleteAircraftType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateAisDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteAisDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool UpdateAisDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool DeleteAisDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, bool filter, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, const FixedDBWideString<32>& comPort, Int32 baudRate, const FixedDBWideString<127>& iPAddress, Int32 port, Int32 udpPort, bool authenticate, const FixedDBWideString<127>& userName, const FixedDBWideString<127>& password, const FixedDBWideString<127>& authenticationURL, Types::AisDeviceConnectionType connectionType, Int32 sourceUpdateRate, const FixedDBWideString<127>& configurationURL, bool storeReceivedSentences );
    BARRELMAN_EXPORT bool UpdateAisDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, bool filter, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, const FixedDBWideString<32>& comPort, Int32 baudRate, const FixedDBWideString<127>& iPAddress, Int32 port, Int32 udpPort, bool authenticate, const FixedDBWideString<127>& userName, const FixedDBWideString<127>& password, const FixedDBWideString<127>& authenticationURL, Types::AisDeviceConnectionType connectionType, Int32 sourceUpdateRate, const FixedDBWideString<127>& configurationURL, bool storeReceivedSentences );
    BARRELMAN_EXPORT bool DeleteAisDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisDeviceRawMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, bool isSent, const FixedDBWideString<127>& message );
    BARRELMAN_EXPORT bool UpdateAisDeviceRawMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, bool isSent, const FixedDBWideString<127>& message );
    BARRELMAN_EXPORT bool DeleteAisDeviceRawMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisDeviceRawSentence( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& timestamp, const WideString& sentence );
    BARRELMAN_EXPORT bool UpdateAisDeviceRawSentence( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& timestamp, const WideString& sentence );
    BARRELMAN_EXPORT bool DeleteAisDeviceRawSentence( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAidToNavigationReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Types::NavigationalAidType navigationalAidType, const FixedDBWideString<127>& name, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Types::PositionFixType positionFixType, Int32 timestamp, bool offPosition, Int32 regionalReserved, Types::Raim raim, bool virtualAid, bool assigned, Int32 spare, const FixedDBWideString<127>& nameExtension );
    BARRELMAN_EXPORT bool UpdateAidToNavigationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Types::NavigationalAidType navigationalAidType, const FixedDBWideString<127>& name, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Types::PositionFixType positionFixType, Int32 timestamp, bool offPosition, Int32 regionalReserved, Types::Raim raim, bool virtualAid, bool assigned, Int32 spare, const FixedDBWideString<127>& nameExtension );
    BARRELMAN_EXPORT bool DeleteAidToNavigationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 sequenceNumber, const DBGuid& destinationMmsi, bool retransmitFlag, Int32 spare, const FixedDBWideString<127>& text );
    BARRELMAN_EXPORT bool UpdateAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 sequenceNumber, const DBGuid& destinationMmsi, bool retransmitFlag, Int32 spare, const FixedDBWideString<127>& text );
    BARRELMAN_EXPORT bool DeleteAisAddressedSafetyRelatedMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisBaseStationReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, const DateTime& timestamp, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, Types::PositionFixType positionFixType, Int32 spare, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool UpdateAisBaseStationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, const DateTime& timestamp, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, Types::PositionFixType positionFixType, Int32 spare, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool DeleteAisBaseStationReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 spare, Int32 sequenceNumber1, const DBGuid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 );
    BARRELMAN_EXPORT bool UpdateAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 spare, Int32 sequenceNumber1, const DBGuid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 );
    BARRELMAN_EXPORT bool DeleteAisBinaryAcknowledgeMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisBinaryAddressedMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 sequenceNumber, const DBGuid& destinationMmsi, bool retransmitFlag, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data );
    BARRELMAN_EXPORT bool UpdateAisBinaryAddressedMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 sequenceNumber, const DBGuid& destinationMmsi, bool retransmitFlag, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data );
    BARRELMAN_EXPORT bool DeleteAisBinaryAddressedMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisBinaryBroadcastMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data );
    BARRELMAN_EXPORT bool UpdateAisBinaryBroadcastMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 spare, Int32 designatedAreaCode, Int32 functionalId, const WideString& data );
    BARRELMAN_EXPORT bool DeleteAisBinaryBroadcastMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisDataLinkManagementMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 spare, Int32 offset1, Int32 reservedSlots1, Int32 timeout1, Int32 increment1, const DBInt32& offset2, const DBInt32& reservedSlots2, const DBInt32& timeout2, const DBInt32& increment2, const DBInt32& offset3, const DBInt32& reservedSlots3, const DBInt32& timeout3, const DBInt32& increment3, const DBInt32& offset4, const DBInt32& reservedSlots4, const DBInt32& timeout4, const DBInt32& increment4 );
    BARRELMAN_EXPORT bool UpdateAisDataLinkManagementMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 spare, Int32 offset1, Int32 reservedSlots1, Int32 timeout1, Int32 increment1, const DBInt32& offset2, const DBInt32& reservedSlots2, const DBInt32& timeout2, const DBInt32& increment2, const DBInt32& offset3, const DBInt32& reservedSlots3, const DBInt32& timeout3, const DBInt32& increment3, const DBInt32& offset4, const DBInt32& reservedSlots4, const DBInt32& timeout4, const DBInt32& increment4 );
    BARRELMAN_EXPORT bool DeleteAisDataLinkManagementMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 reserved, double speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, const DBGuid& name, Types::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Types::PositionFixType positionFixType, Types::Raim raim, bool dataTerminalReady, bool assigned, Int32 spare );
    BARRELMAN_EXPORT bool UpdateAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 reserved, double speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, const DBGuid& name, Types::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Types::PositionFixType positionFixType, Types::Raim raim, bool dataTerminalReady, bool assigned, Int32 spare );
    BARRELMAN_EXPORT bool DeleteAisExtendedClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisInterrogationMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, const DBGuid& interrogatedMmsi, Types::AisMessageType firstMessageType, Int32 firstSlotOffset, const DBEnum<Types::AisMessageType>& secondMessageType, const DBInt32& secondSlotOffset, const DBGuid& secondStationInterrogationMmsi, const DBEnum<Types::AisMessageType>& secondStationFirstMessageType, const DBInt32& secondStationFirstSlotOffset );
    BARRELMAN_EXPORT bool UpdateAisInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, const DBGuid& interrogatedMmsi, Types::AisMessageType firstMessageType, Int32 firstSlotOffset, const DBEnum<Types::AisMessageType>& secondMessageType, const DBInt32& secondSlotOffset, const DBGuid& secondStationInterrogationMmsi, const DBEnum<Types::AisMessageType>& secondStationFirstMessageType, const DBInt32& secondStationFirstSlotOffset );
    BARRELMAN_EXPORT bool DeleteAisInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Types::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Types::ManeuverIndicator maneuverIndicator, Int32 spare, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool UpdateAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Types::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Types::ManeuverIndicator maneuverIndicator, Int32 spare, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool DeleteAisPositionReportClassAAssignedScheduleMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisPositionReportClassAMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Types::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Types::ManeuverIndicator maneuverIndicator, Int32 spare, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool UpdateAisPositionReportClassAMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Types::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Types::ManeuverIndicator maneuverIndicator, Int32 spare, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool DeleteAisPositionReportClassAMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Types::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Types::ManeuverIndicator maneuverIndicator, Int32 spare, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool UpdateAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Types::NavigationStatus navigationStatus, const DBInt32& rateOfTurn, double speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Types::ManeuverIndicator maneuverIndicator, Int32 spare, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool DeleteAisPositionReportClassAResponseToInterrogationMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Types::PositionAccuracy positionAccuracy, Types::Raim raim, Types::NavigationStatus navigationStatus, double longitude, double latitude, double speedOverGround, double courseOverGround, Types::GnssPositionStatus gnssPositionStatus, Int32 spare );
    BARRELMAN_EXPORT bool UpdateAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Types::PositionAccuracy positionAccuracy, Types::Raim raim, Types::NavigationStatus navigationStatus, double longitude, double latitude, double speedOverGround, double courseOverGround, Types::GnssPositionStatus gnssPositionStatus, Int32 spare );
    BARRELMAN_EXPORT bool DeleteAisPositionReportForLongRangeApplicationsMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 spare, Int32 sequenceNumber1, const DBGuid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 );
    BARRELMAN_EXPORT bool UpdateAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 spare, Int32 sequenceNumber1, const DBGuid& mmsi1, const DBInt32& sequenceNumber2, const DBGuid& mmsi2, const DBInt32& sequenceNumber3, const DBGuid& mmsi3, const DBInt32& sequenceNumber4, const DBGuid& mmsi4 );
    BARRELMAN_EXPORT bool DeleteAisSafetyRelatedAcknowledgmentMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 reserved, double speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, bool isCsUnit, bool hasDisplay, bool hasDscCapability, bool band, bool canAcceptMessage22, bool assigned, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool UpdateAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 reserved, double speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, const DBInt32& trueHeading, Int32 timestamp, Int32 regionalReserved, bool isCsUnit, bool hasDisplay, bool hasDscCapability, bool band, bool canAcceptMessage22, bool assigned, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool DeleteAisStandardClassBCsPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 altitude, Int32 speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, Int32 timestamp, Int32 reserved, bool dataTerminalReady, Int32 spare, bool assigned, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool UpdateAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 altitude, Int32 speedOverGround, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, double courseOverGround, Int32 timestamp, Int32 reserved, bool dataTerminalReady, Int32 spare, bool assigned, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool DeleteAisStandardSarAircraftPositionReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 aisVersion, const DBGuid& imoNumber, const DBGuid& callsign, const DBGuid& shipName, Types::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Types::PositionFixType positionFixType, const DBDateTime& estimatedTimeOfArrival, double draught, const FixedDBWideString<127>& destination, bool dataTerminalReady, Int32 spare );
    BARRELMAN_EXPORT bool UpdateAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 aisVersion, const DBGuid& imoNumber, const DBGuid& callsign, const DBGuid& shipName, Types::ShipType shipType, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, Types::PositionFixType positionFixType, const DBDateTime& estimatedTimeOfArrival, double draught, const FixedDBWideString<127>& destination, bool dataTerminalReady, Int32 spare );
    BARRELMAN_EXPORT bool DeleteAisStaticAndVoyageRelatedDataMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisStaticDataReportMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 partNumber );
    BARRELMAN_EXPORT bool UpdateAisStaticDataReportMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 partNumber );
    BARRELMAN_EXPORT bool DeleteAisStaticDataReportMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisStaticDataReportPartAMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 partNumber, const DBGuid& shipName, Int32 spare );
    BARRELMAN_EXPORT bool UpdateAisStaticDataReportPartAMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 partNumber, const DBGuid& shipName, Int32 spare );
    BARRELMAN_EXPORT bool DeleteAisStaticDataReportPartAMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisStaticDataReportPartBMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 partNumber, Types::ShipType shipType, const FixedDBWideString<127>& vendorId, Int32 unitModelCode, Int32 serialNumber, const DBGuid& callsign, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, const DBGuid& mothershipMmsi, Types::PositionFixType positionFixType, Int32 spare );
    BARRELMAN_EXPORT bool UpdateAisStaticDataReportPartBMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 partNumber, Types::ShipType shipType, const FixedDBWideString<127>& vendorId, Int32 unitModelCode, Int32 serialNumber, const DBGuid& callsign, Int32 dimensionToBow, Int32 dimensionToStern, Int32 dimensionToPort, Int32 dimensionToStarboard, const DBGuid& mothershipMmsi, Types::PositionFixType positionFixType, Int32 spare );
    BARRELMAN_EXPORT bool DeleteAisStaticDataReportPartBMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 spare1, const DBGuid& destinationMmsi, Int32 spare2 );
    BARRELMAN_EXPORT bool UpdateAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, Int32 spare1, const DBGuid& destinationMmsi, Int32 spare2 );
    BARRELMAN_EXPORT bool DeleteAisUtcAndDateInquiryMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisUtcAndDateResponseMessage( const ODBC::Connection& connection, Guid& id, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, const DateTime& datetime, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, Types::PositionFixType positionFixType, Int32 spare, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool UpdateAisUtcAndDateResponseMessage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& aisDevice, const DateTime& receivedTimestamp, Int64 messageSequenceNumber, Int32 repeat, const DBGuid& mmsi, const DateTime& datetime, Types::PositionAccuracy positionAccuracy, double longitude, double latitude, Types::PositionFixType positionFixType, Int32 spare, Types::Raim raim, Int32 radioStatus );
    BARRELMAN_EXPORT bool DeleteAisUtcAndDateResponseMessage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAlarmStateChange( const ODBC::Connection& connection, Guid& id, const Guid& alarm, const DateTime& timestamp, Types::AlarmState state );
    BARRELMAN_EXPORT bool UpdateAlarmStateChange( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& alarm, const DateTime& timestamp, Types::AlarmState state );
    BARRELMAN_EXPORT bool DeleteAlarmStateChange( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBaseStationType( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool UpdateBaseStationType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool DeleteBaseStationType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBinaryTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const Binary& value );
    BARRELMAN_EXPORT bool UpdateBinaryTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const Binary& value );
    BARRELMAN_EXPORT bool DeleteBinaryTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBookmark( const ODBC::Connection& connection, Guid& id, const Guid& view, const FixedDBWideString<127>& name, const DBDateTime& timestamp, double latitude, double longitude, double zoomLevel );
    BARRELMAN_EXPORT bool UpdateBookmark( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, const FixedDBWideString<127>& name, const DBDateTime& timestamp, double latitude, double longitude, double zoomLevel );
    BARRELMAN_EXPORT bool DeleteBookmark( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBooleanTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBBoolean & value );
    BARRELMAN_EXPORT bool UpdateBooleanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBBoolean & value );
    BARRELMAN_EXPORT bool DeleteBooleanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertByteTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBByte& value );
    BARRELMAN_EXPORT bool UpdateByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBByte& value );
    BARRELMAN_EXPORT bool DeleteByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommand( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateCameraCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteCameraCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandAbsoluteMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, Types::CameraPanTiltMode positionPanTiltMode, const DBDouble& panAngle, const DBDouble& tiltAngle, Types::CameraFocalLengthMode positionFocalLengthMode, const DBDouble& focalLength, Types::CameraPanTiltMode speedPanTiltMode, const DBDouble& panSpeed, const DBDouble& tiltSpeed, Types::CameraFocalLengthMode speedFocalLengthMode, const DBDouble& zoomSpeed );
    BARRELMAN_EXPORT bool UpdateCameraCommandAbsoluteMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, Types::CameraPanTiltMode positionPanTiltMode, const DBDouble& panAngle, const DBDouble& tiltAngle, Types::CameraFocalLengthMode positionFocalLengthMode, const DBDouble& focalLength, Types::CameraPanTiltMode speedPanTiltMode, const DBDouble& panSpeed, const DBDouble& tiltSpeed, Types::CameraFocalLengthMode speedFocalLengthMode, const DBDouble& zoomSpeed );
    BARRELMAN_EXPORT bool DeleteCameraCommandAbsoluteMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, const DBDouble& x, const DBDouble& y, const DBDouble& z );
    BARRELMAN_EXPORT bool UpdateCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, const DBDouble& x, const DBDouble& y, const DBDouble& z );
    BARRELMAN_EXPORT bool DeleteCameraCommandAdjustPanTiltZoom( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandContinuousMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool normalized, const DBDouble& panVelocity, const DBDouble& tiltVelocity, const DBDouble& zoomVelocity, const DBTimeSpan& duration );
    BARRELMAN_EXPORT bool UpdateCameraCommandContinuousMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool normalized, const DBDouble& panVelocity, const DBDouble& tiltVelocity, const DBDouble& zoomVelocity, const DBTimeSpan& duration );
    BARRELMAN_EXPORT bool DeleteCameraCommandContinuousMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandGeoMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, double latitude, double longitude, const DBDouble& altitude, const DBDouble& viewportWidth, const DBDouble& viewportHeight );
    BARRELMAN_EXPORT bool UpdateCameraCommandGeoMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, double latitude, double longitude, const DBDouble& altitude, const DBDouble& viewportWidth, const DBDouble& viewportHeight );
    BARRELMAN_EXPORT bool DeleteCameraCommandGeoMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandRelativeMove( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool normalized, const DBDouble& panAngle, const DBDouble& tiltAngle, const DBDouble& focalLength, const DBDouble& panSpeed, const DBDouble& tiltSpeed, const DBDouble& zoomSpeed );
    BARRELMAN_EXPORT bool UpdateCameraCommandRelativeMove( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool normalized, const DBDouble& panAngle, const DBDouble& tiltAngle, const DBDouble& focalLength, const DBDouble& panSpeed, const DBDouble& tiltSpeed, const DBDouble& zoomSpeed );
    BARRELMAN_EXPORT bool DeleteCameraCommandRelativeMove( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteCameraCommandReleasePTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteCameraCommandRequestPTZOwnership( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandSetAutoFocus( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool enabled );
    BARRELMAN_EXPORT bool UpdateCameraCommandSetAutoFocus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool enabled );
    BARRELMAN_EXPORT bool DeleteCameraCommandSetAutoFocus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool enabled );
    BARRELMAN_EXPORT bool UpdateCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool enabled );
    BARRELMAN_EXPORT bool DeleteCameraCommandSetBlackAndWhite( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandSetFollowed( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, const Guid& trackId, Types::CameraFollowReason reason );
    BARRELMAN_EXPORT bool UpdateCameraCommandSetFollowed( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, const Guid& trackId, Types::CameraFollowReason reason );
    BARRELMAN_EXPORT bool DeleteCameraCommandSetFollowed( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool enabled );
    BARRELMAN_EXPORT bool UpdateCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool enabled );
    BARRELMAN_EXPORT bool DeleteCameraCommandSetInfraRedLamp( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandSetWasher( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool enabled );
    BARRELMAN_EXPORT bool UpdateCameraCommandSetWasher( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool enabled );
    BARRELMAN_EXPORT bool DeleteCameraCommandSetWasher( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandSetWiper( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool enabled );
    BARRELMAN_EXPORT bool UpdateCameraCommandSetWiper( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool enabled );
    BARRELMAN_EXPORT bool DeleteCameraCommandSetWiper( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandStop( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool panTilt, bool zoom );
    BARRELMAN_EXPORT bool UpdateCameraCommandStop( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply, bool panTilt, bool zoom );
    BARRELMAN_EXPORT bool DeleteCameraCommandStop( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message, double panAngle, double tiltAngle, double focalLength );
    BARRELMAN_EXPORT bool UpdateCameraCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message, double panAngle, double tiltAngle, double focalLength );
    BARRELMAN_EXPORT bool DeleteCameraCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp, Types::CameraControlProtocol cameraControlProtocol, const FixedDBWideString<127>& cameraURL, const FixedDBWideString<127>& configurationURL, const FixedDBWideString<127>& userName, const FixedDBWideString<127>& password, bool useRtspUriOverride, const FixedDBWideString<127>& rtspUriOverride, double latitude, double longitude, double altitude, bool useRelativePosition, Types::CameraPanTiltMode panTiltMode, double minTiltAngle, double maxTiltAngle, double minTiltScaleAngle, double maxTiltScaleAngle, bool useReverseTiltAngle, bool useReverseNormalizedTiltAngle, double minTiltVelocity, double maxTiltVelocity, double minTiltSpeed, double maxTiltSpeed, double minPanAngle, double maxPanAngle, double minPanScaleAngle, double maxPanScaleAngle, bool useReversePanAngle, bool useReverseNormalizedPanAngle, double minPanVelocity, double maxPanVelocity, double minPanSpeed, double maxPanSpeed, Types::CameraFocalLengthMode focalLengthMode, double minFocalLength, double maxFocalLength, double minFocalLengthScale, double maxFocalLengthScale, double minZoomVelocity, double maxZoomVelocity, double minZoomSpeed, double maxZoomSpeed, double imageSensorWidth, double imageSensorHeight, double homePanAngle, double homeTiltAngle, double homeFocalLength, double panOffset, double tiltOffset, double aimAltitude, double minimumTargetWidth, const TimeSpan& targetLockTimeout, const TimeSpan& updateStatusInterval, const TimeSpan& readTimeout, const TimeSpan& moveCommandStatusDelay, const FixedDBWideString<127>& ptzProfileName, const FixedDBWideString<127>& ptzConfigurationToken, const FixedDBWideString<127>& videoSourceToken );
    BARRELMAN_EXPORT bool UpdateCameraConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp, Types::CameraControlProtocol cameraControlProtocol, const FixedDBWideString<127>& cameraURL, const FixedDBWideString<127>& configurationURL, const FixedDBWideString<127>& userName, const FixedDBWideString<127>& password, bool useRtspUriOverride, const FixedDBWideString<127>& rtspUriOverride, double latitude, double longitude, double altitude, bool useRelativePosition, Types::CameraPanTiltMode panTiltMode, double minTiltAngle, double maxTiltAngle, double minTiltScaleAngle, double maxTiltScaleAngle, bool useReverseTiltAngle, bool useReverseNormalizedTiltAngle, double minTiltVelocity, double maxTiltVelocity, double minTiltSpeed, double maxTiltSpeed, double minPanAngle, double maxPanAngle, double minPanScaleAngle, double maxPanScaleAngle, bool useReversePanAngle, bool useReverseNormalizedPanAngle, double minPanVelocity, double maxPanVelocity, double minPanSpeed, double maxPanSpeed, Types::CameraFocalLengthMode focalLengthMode, double minFocalLength, double maxFocalLength, double minFocalLengthScale, double maxFocalLengthScale, double minZoomVelocity, double maxZoomVelocity, double minZoomSpeed, double maxZoomSpeed, double imageSensorWidth, double imageSensorHeight, double homePanAngle, double homeTiltAngle, double homeFocalLength, double panOffset, double tiltOffset, double aimAltitude, double minimumTargetWidth, const TimeSpan& targetLockTimeout, const TimeSpan& updateStatusInterval, const TimeSpan& readTimeout, const TimeSpan& moveCommandStatusDelay, const FixedDBWideString<127>& ptzProfileName, const FixedDBWideString<127>& ptzConfigurationToken, const FixedDBWideString<127>& videoSourceToken );
    BARRELMAN_EXPORT bool DeleteCameraConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraPanCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT bool UpdateCameraPanCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT bool DeleteCameraPanCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraPanCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& panCalibration, double panAngle, double panOffset );
    BARRELMAN_EXPORT bool UpdateCameraPanCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& panCalibration, double panAngle, double panOffset );
    BARRELMAN_EXPORT bool DeleteCameraPanCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraStatus( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DBGuid& track, const DateTime& timestamp, Types::CameraPanTiltMode positionPanTiltMode, double panAngle, double tiltAngle, Types::CameraFocalLengthMode positionFocalLengthMode, double focalLength, Types::CameraMoveStatus panTiltMoveStatus, Types::CameraMoveStatus zoomMoveStatus, Types::CameraPanTiltMode velocityPanTiltMode, const DBDouble& panVelocity, const DBDouble& tiltVelocity, Types::CameraFocalLengthMode velocityFocalLengthMode, const DBDouble& zoomVelocity, Types::CameraFeatures activeFeatures, const WideString& error );
    BARRELMAN_EXPORT bool UpdateCameraStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DBGuid& track, const DateTime& timestamp, Types::CameraPanTiltMode positionPanTiltMode, double panAngle, double tiltAngle, Types::CameraFocalLengthMode positionFocalLengthMode, double focalLength, Types::CameraMoveStatus panTiltMoveStatus, Types::CameraMoveStatus zoomMoveStatus, Types::CameraPanTiltMode velocityPanTiltMode, const DBDouble& panVelocity, const DBDouble& tiltVelocity, Types::CameraFocalLengthMode velocityFocalLengthMode, const DBDouble& zoomVelocity, Types::CameraFeatures activeFeatures, const WideString& error );
    BARRELMAN_EXPORT bool DeleteCameraStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraTiltCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT bool UpdateCameraTiltCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT bool DeleteCameraTiltCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraTiltCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& tiltCalibration, double panAngle, double tiltOffset );
    BARRELMAN_EXPORT bool UpdateCameraTiltCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tiltCalibration, double panAngle, double tiltOffset );
    BARRELMAN_EXPORT bool DeleteCameraTiltCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraZoomCalibration( const ODBC::Connection& connection, Guid& id, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT bool UpdateCameraZoomCalibration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& camera, const DateTime& timestamp );
    BARRELMAN_EXPORT bool DeleteCameraZoomCalibration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraZoomCalibrationValue( const ODBC::Connection& connection, Guid& id, const Guid& zoomCalibration, double focalLength, double focalLengthOffset );
    BARRELMAN_EXPORT bool UpdateCameraZoomCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zoomCalibration, double focalLength, double focalLengthOffset );
    BARRELMAN_EXPORT bool DeleteCameraZoomCalibrationValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCatalog( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool UpdateCatalog( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool DeleteCatalog( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertElement( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const DBGuid& elementType );
    BARRELMAN_EXPORT bool UpdateElement( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const DBGuid& elementType );
    BARRELMAN_EXPORT bool DeleteElement( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCollectionInfo( const ODBC::Connection& connection, Guid& id, Int64 count );
    BARRELMAN_EXPORT bool UpdateCollectionInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 count );
    BARRELMAN_EXPORT bool DeleteCollectionInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCountry( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, Int32 code, const FixedDBWideString<2>& alpha2, const FixedDBWideString<3>& alpha3 );
    BARRELMAN_EXPORT bool UpdateCountry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, Int32 code, const FixedDBWideString<2>& alpha2, const FixedDBWideString<3>& alpha3 );
    BARRELMAN_EXPORT bool DeleteCountry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCursorInfo( const ODBC::Connection& connection, Guid& id, Int32 typeCode );
    BARRELMAN_EXPORT bool UpdateCursorInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 typeCode );
    BARRELMAN_EXPORT bool DeleteCursorInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDateTimeTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDateTime& value );
    BARRELMAN_EXPORT bool UpdateDateTimeTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDateTime& value );
    BARRELMAN_EXPORT bool DeleteDateTimeTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDeviceHost( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool UpdateDeviceHost( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool DeleteDeviceHost( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDeviceHostConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& host, const DateTime& timestamp, const FixedDBWideString<127>& hostname, Int32 port, const FixedDBWideString<127>& queueName );
    BARRELMAN_EXPORT bool UpdateDeviceHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const DateTime& timestamp, const FixedDBWideString<127>& hostname, Int32 port, const FixedDBWideString<127>& queueName );
    BARRELMAN_EXPORT bool DeleteDeviceHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDoubleTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& value );
    BARRELMAN_EXPORT bool UpdateDoubleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& value );
    BARRELMAN_EXPORT bool DeleteDoubleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertFacilityType( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool UpdateFacilityType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool DeleteFacilityType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude );
    BARRELMAN_EXPORT bool UpdateGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude );
    BARRELMAN_EXPORT bool DeleteGeoPosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude, const DBDouble& altitude );
    BARRELMAN_EXPORT bool UpdateGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& latitude, const DBDouble& longitude, const DBDouble& altitude );
    BARRELMAN_EXPORT bool DeleteGeoPosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGNSSDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateGNSSDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteGNSSDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGNSSDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool UpdateGNSSDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool DeleteGNSSDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGNSSDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& gNSSDevice, const DateTime& timestamp, double defaultLatitude, double defaultLongitude, double defaultAltitude, double latitudeOffset, double longitudeOffset, double altitudeOffset );
    BARRELMAN_EXPORT bool UpdateGNSSDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gNSSDevice, const DateTime& timestamp, double defaultLatitude, double defaultLongitude, double defaultAltitude, double latitudeOffset, double longitudeOffset, double altitudeOffset );
    BARRELMAN_EXPORT bool DeleteGNSSDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGuidTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBGuid& value );
    BARRELMAN_EXPORT bool UpdateGuidTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBGuid& value );
    BARRELMAN_EXPORT bool DeleteGuidTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateGyroDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteGyroDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool UpdateGyroDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool DeleteGyroDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& gyroDevice, const DateTime& timestamp, double defaultHeadingTrueNorth, double defaultMagneticTrueNorth, double headingTrueNorthOffset, double headingMagneticNorthOffset, const FixedDBWideString<64>& pitchTransducerName, const FixedDBWideString<64>& rollTransducerName );
    BARRELMAN_EXPORT bool UpdateGyroDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& gyroDevice, const DateTime& timestamp, double defaultHeadingTrueNorth, double defaultMagneticTrueNorth, double headingTrueNorthOffset, double headingMagneticNorthOffset, const FixedDBWideString<64>& pitchTransducerName, const FixedDBWideString<64>& rollTransducerName );
    BARRELMAN_EXPORT bool DeleteGyroDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCallsign( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& identifier );
    BARRELMAN_EXPORT bool UpdateCallsign( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& identifier );
    BARRELMAN_EXPORT bool DeleteCallsign( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, Guid& id, Int64 identifier );
    BARRELMAN_EXPORT bool UpdateInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 identifier );
    BARRELMAN_EXPORT bool DeleteInternationalMaritimeOrganizationNumber( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMaritimeMobileServiceIdentity( const ODBC::Connection& connection, Guid& id, Int64 identifier );
    BARRELMAN_EXPORT bool UpdateMaritimeMobileServiceIdentity( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int64 identifier );
    BARRELMAN_EXPORT bool DeleteMaritimeMobileServiceIdentity( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertName( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& text );
    BARRELMAN_EXPORT bool UpdateName( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& text );
    BARRELMAN_EXPORT bool DeleteName( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt16TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt16& value );
    BARRELMAN_EXPORT bool UpdateInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt16& value );
    BARRELMAN_EXPORT bool DeleteInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt32TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt32& value );
    BARRELMAN_EXPORT bool UpdateInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt32& value );
    BARRELMAN_EXPORT bool DeleteInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt64TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value );
    BARRELMAN_EXPORT bool UpdateInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value );
    BARRELMAN_EXPORT bool DeleteInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBaseStation( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const DBGuid& type );
    BARRELMAN_EXPORT bool UpdateBaseStation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const DBGuid& type );
    BARRELMAN_EXPORT bool DeleteBaseStation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCameraDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool UpdateCameraDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool DeleteCameraDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGNSSDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries, const DBGuid& latitudeTimeseries, const DBGuid& longitudeTimeseries, const DBGuid& altitudeTimeseries );
    BARRELMAN_EXPORT bool UpdateGNSSDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries, const DBGuid& latitudeTimeseries, const DBGuid& longitudeTimeseries, const DBGuid& altitudeTimeseries );
    BARRELMAN_EXPORT bool DeleteGNSSDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries, const DBGuid& headingTrueNorthTimeseries, const DBGuid& headingMagneticNorthTimeseries, const DBGuid& pitchTimeseries, const DBGuid& rateOfTurnTimeseries, const DBGuid& rollTimeseries, const DBGuid& courseTimeseries, const DBGuid& speedTimeseries, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT bool UpdateGyroDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries, const DBGuid& headingTrueNorthTimeseries, const DBGuid& headingMagneticNorthTimeseries, const DBGuid& pitchTimeseries, const DBGuid& rateOfTurnTimeseries, const DBGuid& rollTimeseries, const DBGuid& courseTimeseries, const DBGuid& speedTimeseries, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT bool DeleteGyroDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLineInputDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool UpdateLineInputDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool DeleteLineInputDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertOilSpillDetectorDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool UpdateOilSpillDetectorDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool DeleteOilSpillDetectorDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadioDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool UpdateRadioDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool DeleteRadioDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadomeDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries, const DBGuid& radar, const DBGuid& pressureTimeseries, const DBGuid& temperatureTimeseries, const DBGuid& dewPointTimeseries, const DBGuid& statusTimeseries );
    BARRELMAN_EXPORT bool UpdateRadomeDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries, const DBGuid& radar, const DBGuid& pressureTimeseries, const DBGuid& temperatureTimeseries, const DBGuid& dewPointTimeseries, const DBGuid& statusTimeseries );
    BARRELMAN_EXPORT bool DeleteRadomeDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool UpdateAisDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool DeleteAisDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries, const DBGuid& saveSettingsTimeseries, const DBGuid& powerOnTimeseries, const DBGuid& trackingOnTimeseries, const DBGuid& radarPulseTimeseries, const DBGuid& tuningTimeseries, const DBGuid& blankSector1Timeseries, const DBGuid& sector1StartTimeseries, const DBGuid& sector1EndTimeseries, const DBGuid& blankSector2Timeseries, const DBGuid& sector2StartTimeseries, const DBGuid& sector2EndTimeseries, const DBGuid& enableAutomaticFrequencyControlTimeseries, const DBGuid& azimuthOffsetTimeseries, const DBGuid& enableSensitivityTimeControlTimeseries, const DBGuid& automaticSensitivityTimeControlTimeseries, const DBGuid& sensitivityTimeControlLevelTimeseries, const DBGuid& enableFastTimeConstantTimeseries, const DBGuid& fastTimeConstantLevelTimeseries, const DBGuid& fastTimeConstantModeTimeseries, const DBGuid& latitudeTimeseries, const DBGuid& longitudeTimeseries, const DBGuid& radome, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT bool UpdateRadarDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries, const DBGuid& saveSettingsTimeseries, const DBGuid& powerOnTimeseries, const DBGuid& trackingOnTimeseries, const DBGuid& radarPulseTimeseries, const DBGuid& tuningTimeseries, const DBGuid& blankSector1Timeseries, const DBGuid& sector1StartTimeseries, const DBGuid& sector1EndTimeseries, const DBGuid& blankSector2Timeseries, const DBGuid& sector2StartTimeseries, const DBGuid& sector2EndTimeseries, const DBGuid& enableAutomaticFrequencyControlTimeseries, const DBGuid& azimuthOffsetTimeseries, const DBGuid& enableSensitivityTimeControlTimeseries, const DBGuid& automaticSensitivityTimeControlTimeseries, const DBGuid& sensitivityTimeControlLevelTimeseries, const DBGuid& enableFastTimeConstantTimeseries, const DBGuid& fastTimeConstantLevelTimeseries, const DBGuid& fastTimeConstantModeTimeseries, const DBGuid& latitudeTimeseries, const DBGuid& longitudeTimeseries, const DBGuid& radome, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT bool DeleteRadarDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationDevice( const ODBC::Connection& connection, Guid& id, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries, const DBGuid& barometricPressureTimeseries, const DBGuid& airTemperatureTimeseries, const DBGuid& waterTemperatureTimeseries, const DBGuid& relativeHumidityTimeseries, const DBGuid& absoluteHumidityTimeseries, const DBGuid& dewPointTimeseries, const DBGuid& windDirectionTimeseries, const DBGuid& windSpeedTimeseries, const DBGuid& gyro );
    BARRELMAN_EXPORT bool UpdateWeatherStationDevice( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& enabledTimeseries, const DBGuid& barometricPressureTimeseries, const DBGuid& airTemperatureTimeseries, const DBGuid& waterTemperatureTimeseries, const DBGuid& relativeHumidityTimeseries, const DBGuid& absoluteHumidityTimeseries, const DBGuid& dewPointTimeseries, const DBGuid& windDirectionTimeseries, const DBGuid& windSpeedTimeseries, const DBGuid& gyro );
    BARRELMAN_EXPORT bool DeleteWeatherStationDevice( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertFacility( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const DBGuid& type, double longitude, double latitude, double altitude );
    BARRELMAN_EXPORT bool UpdateFacility( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const DBGuid& type, double longitude, double latitude, double altitude );
    BARRELMAN_EXPORT bool DeleteFacility( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAircraft( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const DBGuid& type );
    BARRELMAN_EXPORT bool UpdateAircraft( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const DBGuid& type );
    BARRELMAN_EXPORT bool DeleteAircraft( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisAidToNavigation( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const DBGuid& mMSI, Types::NavigationalAidType navigationalAidType, const DBGuid& position, bool isVirtual, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const DBGuid& offPositionTimeseries );
    BARRELMAN_EXPORT bool UpdateAisAidToNavigation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const DBGuid& mMSI, Types::NavigationalAidType navigationalAidType, const DBGuid& position, bool isVirtual, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const DBGuid& offPositionTimeseries );
    BARRELMAN_EXPORT bool DeleteAisAidToNavigation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertVehicle( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const DBGuid& type );
    BARRELMAN_EXPORT bool UpdateVehicle( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const DBGuid& type );
    BARRELMAN_EXPORT bool DeleteVehicle( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertVessel( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const DBGuid& type, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const DBGuid& draughtTimeseries, const DBGuid& personsOnBoardTimeseries );
    BARRELMAN_EXPORT bool UpdateVessel( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const DBGuid& type, Int32 toBow, Int32 toStern, Int32 toPort, Int32 toStarboard, const DBGuid& draughtTimeseries, const DBGuid& personsOnBoardTimeseries );
    BARRELMAN_EXPORT bool DeleteVessel( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertItemIdentityLink( const ODBC::Connection& connection, Guid& id, const Guid& item, const Guid& identity, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool UpdateItemIdentityLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, const Guid& identity, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool DeleteItemIdentityLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertItemParentChildLink( const ODBC::Connection& connection, Guid& id, const Guid& parent, const Guid& child, const DateTime& timestamp );
    BARRELMAN_EXPORT bool UpdateItemParentChildLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& parent, const Guid& child, const DateTime& timestamp );
    BARRELMAN_EXPORT bool DeleteItemParentChildLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLineInputDeviceCommand( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateLineInputDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteLineInputDeviceCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLineInputDeviceCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool UpdateLineInputDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool DeleteLineInputDeviceCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLineInputDeviceConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const DateTime& timestamp, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages, bool nMEA, bool strictNMEA, Types::LineInputDeviceConnectionType connectionType, Int32 udpReceivePort, const FixedDBWideString<127>& udpSendHostname, Int32 udpSendPort, const FixedDBWideString<127>& tcpHostname, Int32 tcpPort, bool useHttpLogin, const FixedDBWideString<127>& loginHostname, Int32 loginPort, const FixedDBWideString<127>& userName, const FixedDBWideString<127>& password, const FixedDBWideString<127>& comPort, Int32 baudRate, Int32 dataBits, bool discardNull, bool dtrEnable, Types::Handshake handshake, const FixedDBWideString<127>& newLine, Types::Parity parity, Byte parityReplace, Int32 readBufferSize, const TimeSpan& readTimeout, Int32 receivedBytesThreshold, bool rtsEnable, Types::StopBits stopBits, Int32 writeBufferSize, const TimeSpan& writeTimeout, const FixedDBWideString<127>& pairedComPort );
    BARRELMAN_EXPORT bool UpdateLineInputDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const DateTime& timestamp, bool storeReceivedSentences, bool storeSentMessages, bool storeUnsentMessages, bool nMEA, bool strictNMEA, Types::LineInputDeviceConnectionType connectionType, Int32 udpReceivePort, const FixedDBWideString<127>& udpSendHostname, Int32 udpSendPort, const FixedDBWideString<127>& tcpHostname, Int32 tcpPort, bool useHttpLogin, const FixedDBWideString<127>& loginHostname, Int32 loginPort, const FixedDBWideString<127>& userName, const FixedDBWideString<127>& password, const FixedDBWideString<127>& comPort, Int32 baudRate, Int32 dataBits, bool discardNull, bool dtrEnable, Types::Handshake handshake, const FixedDBWideString<127>& newLine, Types::Parity parity, Byte parityReplace, Int32 readBufferSize, const TimeSpan& readTimeout, Int32 receivedBytesThreshold, bool rtsEnable, Types::StopBits stopBits, Int32 writeBufferSize, const TimeSpan& writeTimeout, const FixedDBWideString<127>& pairedComPort );
    BARRELMAN_EXPORT bool DeleteLineInputDeviceConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLineInputMessageRouting( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const FixedDBWideString<127>& type );
    BARRELMAN_EXPORT bool UpdateLineInputMessageRouting( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const FixedDBWideString<127>& type );
    BARRELMAN_EXPORT bool DeleteLineInputMessageRouting( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLineInputMessageRoutingDestination( const ODBC::Connection& connection, Guid& id, const Guid& routing, const DBGuid& listener );
    BARRELMAN_EXPORT bool UpdateLineInputMessageRoutingDestination( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& routing, const DBGuid& listener );
    BARRELMAN_EXPORT bool DeleteLineInputMessageRoutingDestination( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLineInputWhiteListEntry( const ODBC::Connection& connection, Guid& id, const Guid& lineInputDevice, const FixedDBWideString<128>& hostName, Int32 port );
    BARRELMAN_EXPORT bool UpdateLineInputWhiteListEntry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& lineInputDevice, const FixedDBWideString<128>& hostName, Int32 port );
    BARRELMAN_EXPORT bool DeleteLineInputWhiteListEntry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLogApplication( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool UpdateLogApplication( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool DeleteLogApplication( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLogApplicationConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& application, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency );
    BARRELMAN_EXPORT bool UpdateLogApplicationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& application, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency );
    BARRELMAN_EXPORT bool DeleteLogApplicationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLogHost( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& computerName, const WideString& description );
    BARRELMAN_EXPORT bool UpdateLogHost( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& computerName, const WideString& description );
    BARRELMAN_EXPORT bool DeleteLogHost( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLogHostConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& host, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency );
    BARRELMAN_EXPORT bool UpdateLogHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& host, const DateTime& timestamp, bool finest, bool finer, bool fine, bool info, bool notice, bool warn, bool error, bool severe, bool critical, bool alert, bool fatal, bool emergency );
    BARRELMAN_EXPORT bool DeleteLogHostConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLogLocation( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<260>& fileName, Int32 lineNumber, const WideString& namespace__, const WideString& className, const FixedDBWideString<255>& methodName );
    BARRELMAN_EXPORT bool UpdateLogLocation( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<260>& fileName, Int32 lineNumber, const WideString& namespace__, const WideString& className, const FixedDBWideString<255>& methodName );
    BARRELMAN_EXPORT bool DeleteLogLocation( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLogProcess( const ODBC::Connection& connection, Guid& id, const Guid& application, const DBGuid& host, const DateTime& started, const DBDateTime& stopped, Int64 processId, const WideString& path, const FixedDBWideString<127>& identity );
    BARRELMAN_EXPORT bool UpdateLogProcess( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& application, const DBGuid& host, const DateTime& started, const DBDateTime& stopped, Int64 processId, const WideString& path, const FixedDBWideString<127>& identity );
    BARRELMAN_EXPORT bool DeleteLogProcess( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLogRecord( const ODBC::Connection& connection, Guid& id, const Guid& thread, Int64 sequenceNumber, Types::LogLevel level, const DateTime& timestamp, Int32 depth, const Guid& location, const WideString& message, const WideString& exceptionString, const Binary& propertiesData );
    BARRELMAN_EXPORT bool UpdateLogRecord( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& thread, Int64 sequenceNumber, Types::LogLevel level, const DateTime& timestamp, Int32 depth, const Guid& location, const WideString& message, const WideString& exceptionString, const Binary& propertiesData );
    BARRELMAN_EXPORT bool DeleteLogRecord( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLogThread( const ODBC::Connection& connection, Guid& id, const Guid& process, const DateTime& started, const DBDateTime& stopped, Int64 threadId, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool UpdateLogThread( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& process, const DateTime& started, const DBDateTime& stopped, Int64 threadId, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool DeleteLogThread( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertLogTraceEntry( const ODBC::Connection& connection, Guid& id, const Guid& thread, Int64 sequenceNumber, const Guid& location, Int32 depth, const DateTime& entered, const DBDateTime& ended );
    BARRELMAN_EXPORT bool UpdateLogTraceEntry( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& thread, Int64 sequenceNumber, const Guid& location, Int32 depth, const DateTime& entered, const DBDateTime& ended );
    BARRELMAN_EXPORT bool DeleteLogTraceEntry( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMapElement( const ODBC::Connection& connection, Guid& id, const Guid& item, Types::MapElementType elementType, double latitude, double longitude, double angle, double left, double top, double width, double height, const FixedDBWideString<127>& label, const Binary& data );
    BARRELMAN_EXPORT bool UpdateMapElement( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, Types::MapElementType elementType, double latitude, double longitude, double angle, double left, double top, double width, double height, const FixedDBWideString<127>& label, const Binary& data );
    BARRELMAN_EXPORT bool DeleteMapElement( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMapInfo( const ODBC::Connection& connection, Guid& id, Int32 scale, double latitude, double longitude, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, const Binary& image );
    BARRELMAN_EXPORT bool UpdateMapInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 scale, double latitude, double longitude, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, const Binary& image );
    BARRELMAN_EXPORT bool DeleteMapInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMapServiceOptions( const ODBC::Connection& connection, Guid& id, const DateTime& timestamp, const FixedDBWideString<127>& ipAddress, Int32 port, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY );
    BARRELMAN_EXPORT bool UpdateMapServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DateTime& timestamp, const FixedDBWideString<127>& ipAddress, Int32 port, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY );
    BARRELMAN_EXPORT bool DeleteMapServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMaritimeIdentificationDigits( const ODBC::Connection& connection, Guid& id, Int32 code, const Guid& country );
    BARRELMAN_EXPORT bool UpdateMaritimeIdentificationDigits( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, Int32 code, const Guid& country );
    BARRELMAN_EXPORT bool DeleteMaritimeIdentificationDigits( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMediaProxySession( const ODBC::Connection& connection, Guid& id, const Guid& service, const FixedDBWideString<128>& name, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool UpdateMediaProxySession( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& service, const FixedDBWideString<128>& name, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool DeleteMediaProxySession( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMediaProxySessionFile( const ODBC::Connection& connection, Guid& id, const Guid& proxySession, const DateTime& timestamp, const FixedDBWideString<127>& streamName );
    BARRELMAN_EXPORT bool UpdateMediaProxySessionFile( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& proxySession, const DateTime& timestamp, const FixedDBWideString<127>& streamName );
    BARRELMAN_EXPORT bool DeleteMediaProxySessionFile( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMediaProxySessionOptions( const ODBC::Connection& connection, Guid& id, const Guid& proxySession, const DateTime& timestamp, const FixedDBWideString<255>& sourceStreamUrl, const FixedDBWideString<255>& streamName, Types::MediaProxySessionMode mode, Int32 tunnelOverHTTPPortNumber, const FixedDBWideString<128>& username, const FixedDBWideString<128>& password, Int32 recorderPortNumber, Types::MediaProxySessionType sessionType, const TimeSpan& maxFileTime, const TimeSpan& maxFileRetention, const FixedDBWideString<260>& videoDirectory );
    BARRELMAN_EXPORT bool UpdateMediaProxySessionOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& proxySession, const DateTime& timestamp, const FixedDBWideString<255>& sourceStreamUrl, const FixedDBWideString<255>& streamName, Types::MediaProxySessionMode mode, Int32 tunnelOverHTTPPortNumber, const FixedDBWideString<128>& username, const FixedDBWideString<128>& password, Int32 recorderPortNumber, Types::MediaProxySessionType sessionType, const TimeSpan& maxFileTime, const TimeSpan& maxFileRetention, const FixedDBWideString<260>& videoDirectory );
    BARRELMAN_EXPORT bool DeleteMediaProxySessionOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMediaService( const ODBC::Connection& connection, Guid& id, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool UpdateMediaService( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& enabledTimeseries );
    BARRELMAN_EXPORT bool DeleteMediaService( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMediaServiceOptions( const ODBC::Connection& connection, Guid& id, const Guid& mediaService, const DateTime& timestamp, Int32 rtspPortNumber, Int32 httpPortNumber );
    BARRELMAN_EXPORT bool UpdateMediaServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& mediaService, const DateTime& timestamp, Int32 rtspPortNumber, Int32 httpPortNumber );
    BARRELMAN_EXPORT bool DeleteMediaServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertElementType( const ODBC::Connection& connection, Guid& id, const Guid& namespace__, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool UpdateElementType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& namespace__, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool DeleteElementType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertNamespace( const ODBC::Connection& connection, Guid& id, const Guid& namespace__, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool UpdateNamespace( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& namespace__, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool DeleteNamespace( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertOilSpill( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, double oilArea, const Binary& shape, const Binary& bSI, const Binary& oil, const Binary& trace );
    BARRELMAN_EXPORT bool UpdateOilSpill( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, double oilArea, const Binary& shape, const Binary& bSI, const Binary& oil, const Binary& trace );
    BARRELMAN_EXPORT bool DeleteOilSpill( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertOilSpillDetectorCommand( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateOilSpillDetectorCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteOilSpillDetectorCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertOilSpillDetectorCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool UpdateOilSpillDetectorCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool DeleteOilSpillDetectorCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertOilSpillDetectorConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& oilSpillDetector, const DateTime& timestamp, double range, double startAngle, double endAngle, double startRange, double endRange, Int32 updateRate, const TimeSpan& statusSendTime, bool drawBorder, const Binary& colors, bool sendToServer, const FixedDBWideString<260>& directory, bool transparentWater, bool savePictures, bool sendAsTarget, bool writeLog, const FixedDBWideString<127>& targetFilePrefix, const DBGuid& targetMMSI, double latitude, double longitude, bool testSourceEnabled, const FixedDBWideString<127>& proxyServer, bool useProxyServer );
    BARRELMAN_EXPORT bool UpdateOilSpillDetectorConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& oilSpillDetector, const DateTime& timestamp, double range, double startAngle, double endAngle, double startRange, double endRange, Int32 updateRate, const TimeSpan& statusSendTime, bool drawBorder, const Binary& colors, bool sendToServer, const FixedDBWideString<260>& directory, bool transparentWater, bool savePictures, bool sendAsTarget, bool writeLog, const FixedDBWideString<127>& targetFilePrefix, const DBGuid& targetMMSI, double latitude, double longitude, bool testSourceEnabled, const FixedDBWideString<127>& proxyServer, bool useProxyServer );
    BARRELMAN_EXPORT bool DeleteOilSpillDetectorConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertPosition2DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y );
    BARRELMAN_EXPORT bool UpdatePosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y );
    BARRELMAN_EXPORT bool DeletePosition2DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertPosition3DTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y, const DBDouble& z );
    BARRELMAN_EXPORT bool UpdatePosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBDouble& x, const DBDouble& y, const DBDouble& z );
    BARRELMAN_EXPORT bool DeletePosition3DTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertProcessTrackValueResult( const ODBC::Connection& connection, Guid& id, bool createdNewTrack, const Guid& trackId );
    BARRELMAN_EXPORT bool UpdateProcessTrackValueResult( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, bool createdNewTrack, const Guid& trackId );
    BARRELMAN_EXPORT bool DeleteProcessTrackValueResult( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBinaryProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Binary& value );
    BARRELMAN_EXPORT bool UpdateBinaryProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Binary& value );
    BARRELMAN_EXPORT bool DeleteBinaryProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBooleanProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, bool value );
    BARRELMAN_EXPORT bool UpdateBooleanProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, bool value );
    BARRELMAN_EXPORT bool DeleteBooleanProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertByteProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Byte value );
    BARRELMAN_EXPORT bool UpdateByteProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Byte value );
    BARRELMAN_EXPORT bool DeleteByteProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDateTimeProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DateTime& value );
    BARRELMAN_EXPORT bool UpdateDateTimeProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DateTime& value );
    BARRELMAN_EXPORT bool DeleteDateTimeProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDoubleProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, double value );
    BARRELMAN_EXPORT bool UpdateDoubleProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, double value );
    BARRELMAN_EXPORT bool DeleteDoubleProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGuidProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const Guid& value );
    BARRELMAN_EXPORT bool UpdateGuidProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const Guid& value );
    BARRELMAN_EXPORT bool DeleteGuidProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt16Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int16 value );
    BARRELMAN_EXPORT bool UpdateInt16Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int16 value );
    BARRELMAN_EXPORT bool DeleteInt16Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt32Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int32 value );
    BARRELMAN_EXPORT bool UpdateInt32Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int32 value );
    BARRELMAN_EXPORT bool DeleteInt32Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt64Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int64 value );
    BARRELMAN_EXPORT bool UpdateInt64Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int64 value );
    BARRELMAN_EXPORT bool DeleteInt64Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertReferenceProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& value );
    BARRELMAN_EXPORT bool UpdateReferenceProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& value );
    BARRELMAN_EXPORT bool DeleteReferenceProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSByteProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, SByte value );
    BARRELMAN_EXPORT bool UpdateSByteProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, SByte value );
    BARRELMAN_EXPORT bool DeleteSByteProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSingleProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, float value );
    BARRELMAN_EXPORT bool UpdateSingleProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, float value );
    BARRELMAN_EXPORT bool DeleteSingleProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertStringProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const FixedDBWideString<127>& value );
    BARRELMAN_EXPORT bool UpdateStringProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const FixedDBWideString<127>& value );
    BARRELMAN_EXPORT bool DeleteStringProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBinaryTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateBinaryTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteBinaryTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBooleanTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateBooleanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteBooleanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertByteTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDateTimeTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateDateTimeTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteDateTimeTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDoubleTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateDoubleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteDoubleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGuidTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateGuidTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteGuidTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt16TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt32TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt64TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertReferenceTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateReferenceTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteReferenceTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSByteTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateSByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteSByteTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSingleTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateSingleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteSingleTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertStringTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateStringTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteStringTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTimeSpanTimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateTimeSpanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteTimeSpanTimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt16TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateUInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteUInt16TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt32TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateUInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteUInt32TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt64TimeseriesProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool UpdateUInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const DBGuid& timeseries );
    BARRELMAN_EXPORT bool DeleteUInt64TimeseriesProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTimeSpanProperty( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, const TimeSpan& value );
    BARRELMAN_EXPORT bool UpdateTimeSpanProperty( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, const TimeSpan& value );
    BARRELMAN_EXPORT bool DeleteTimeSpanProperty( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt16Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, UInt16 value );
    BARRELMAN_EXPORT bool UpdateUInt16Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, UInt16 value );
    BARRELMAN_EXPORT bool DeleteUInt16Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt32Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, UInt32 value );
    BARRELMAN_EXPORT bool UpdateUInt32Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, UInt32 value );
    BARRELMAN_EXPORT bool DeleteUInt32Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt64Property( const ODBC::Connection& connection, Guid& id, const Guid& element, const Guid& definition, Int64 value );
    BARRELMAN_EXPORT bool UpdateUInt64Property( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& element, const Guid& definition, Int64 value );
    BARRELMAN_EXPORT bool DeleteUInt64Property( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBinaryPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Binary& defaultValue );
    BARRELMAN_EXPORT bool UpdateBinaryPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Binary& defaultValue );
    BARRELMAN_EXPORT bool DeleteBinaryPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBooleanPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, bool defaultValue );
    BARRELMAN_EXPORT bool UpdateBooleanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, bool defaultValue );
    BARRELMAN_EXPORT bool DeleteBooleanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBytePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Byte defaultValue, Byte minValue, Byte maxValue );
    BARRELMAN_EXPORT bool UpdateBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Byte defaultValue, Byte minValue, Byte maxValue );
    BARRELMAN_EXPORT bool DeleteBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDateTimePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& defaultValue, const FixedDBWideString<127>& minValue, const FixedDBWideString<127>& maxValue );
    BARRELMAN_EXPORT bool UpdateDateTimePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& defaultValue, const FixedDBWideString<127>& minValue, const FixedDBWideString<127>& maxValue );
    BARRELMAN_EXPORT bool DeleteDateTimePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDoublePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, double defaultValue, double minValue, double maxValue );
    BARRELMAN_EXPORT bool UpdateDoublePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, double defaultValue, double minValue, double maxValue );
    BARRELMAN_EXPORT bool DeleteDoublePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGuidPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Guid& defaultValue );
    BARRELMAN_EXPORT bool UpdateGuidPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const Guid& defaultValue );
    BARRELMAN_EXPORT bool DeleteGuidPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt16PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int16 defaultValue, Int16 minValue, Int16 maxValue );
    BARRELMAN_EXPORT bool UpdateInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int16 defaultValue, Int16 minValue, Int16 maxValue );
    BARRELMAN_EXPORT bool DeleteInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt32PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int32 defaultValue, Int32 minValue, Int32 maxValue );
    BARRELMAN_EXPORT bool UpdateInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int32 defaultValue, Int32 minValue, Int32 maxValue );
    BARRELMAN_EXPORT bool DeleteInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt64PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT bool UpdateInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT bool DeleteInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertReferencePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& defaultValue, const DBGuid& referencedElementType );
    BARRELMAN_EXPORT bool UpdateReferencePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& defaultValue, const DBGuid& referencedElementType );
    BARRELMAN_EXPORT bool DeleteReferencePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSBytePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, SByte defaultValue, SByte minValue, SByte maxValue );
    BARRELMAN_EXPORT bool UpdateSBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, SByte defaultValue, SByte minValue, SByte maxValue );
    BARRELMAN_EXPORT bool DeleteSBytePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSinglePropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, float defaultValue, float minValue, float maxValue );
    BARRELMAN_EXPORT bool UpdateSinglePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, float defaultValue, float minValue, float maxValue );
    BARRELMAN_EXPORT bool DeleteSinglePropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertStringPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& defaultValue, const FixedDBWideString<127>& pattern );
    BARRELMAN_EXPORT bool UpdateStringPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& defaultValue, const FixedDBWideString<127>& pattern );
    BARRELMAN_EXPORT bool DeleteStringPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool UpdateBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool DeleteBinaryTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool UpdateBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool DeleteBooleanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Byte minValue, Byte maxValue );
    BARRELMAN_EXPORT bool UpdateByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Byte minValue, Byte maxValue );
    BARRELMAN_EXPORT bool DeleteByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& minValue, const FixedDBWideString<127>& maxValue );
    BARRELMAN_EXPORT bool UpdateDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& minValue, const FixedDBWideString<127>& maxValue );
    BARRELMAN_EXPORT bool DeleteDateTimeTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, double minValue, double maxValue );
    BARRELMAN_EXPORT bool UpdateDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, double minValue, double maxValue );
    BARRELMAN_EXPORT bool DeleteDoubleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool UpdateGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool DeleteGuidTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int16 minValue, Int16 maxValue );
    BARRELMAN_EXPORT bool UpdateInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int16 minValue, Int16 maxValue );
    BARRELMAN_EXPORT bool DeleteInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int32 minValue, Int32 maxValue );
    BARRELMAN_EXPORT bool UpdateInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int32 minValue, Int32 maxValue );
    BARRELMAN_EXPORT bool DeleteInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT bool UpdateInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT bool DeleteInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& referencedElementType );
    BARRELMAN_EXPORT bool UpdateReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const DBGuid& referencedElementType );
    BARRELMAN_EXPORT bool DeleteReferenceTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, SByte minValue, SByte maxValue );
    BARRELMAN_EXPORT bool UpdateSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, SByte minValue, SByte maxValue );
    BARRELMAN_EXPORT bool DeleteSByteTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, float minValue, float maxValue );
    BARRELMAN_EXPORT bool UpdateSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, float minValue, float maxValue );
    BARRELMAN_EXPORT bool DeleteSingleTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& pattern );
    BARRELMAN_EXPORT bool UpdateStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const FixedDBWideString<127>& pattern );
    BARRELMAN_EXPORT bool DeleteStringTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const TimeSpan& minValue, const TimeSpan& maxValue );
    BARRELMAN_EXPORT bool UpdateTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const TimeSpan& minValue, const TimeSpan& maxValue );
    BARRELMAN_EXPORT bool DeleteTimeSpanTimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt16 minValue, UInt16 maxValue );
    BARRELMAN_EXPORT bool UpdateUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt16 minValue, UInt16 maxValue );
    BARRELMAN_EXPORT bool DeleteUInt16TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt32 minValue, UInt32 maxValue );
    BARRELMAN_EXPORT bool UpdateUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt32 minValue, UInt32 maxValue );
    BARRELMAN_EXPORT bool DeleteUInt32TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT bool UpdateUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT bool DeleteUInt64TimeseriesPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTimeSpanPropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const TimeSpan& defaultValue, const TimeSpan& minValue, const TimeSpan& maxValue );
    BARRELMAN_EXPORT bool UpdateTimeSpanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, const TimeSpan& defaultValue, const TimeSpan& minValue, const TimeSpan& maxValue );
    BARRELMAN_EXPORT bool DeleteTimeSpanPropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt16PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt16 defaultValue, UInt16 minValue, UInt16 maxValue );
    BARRELMAN_EXPORT bool UpdateUInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt16 defaultValue, UInt16 minValue, UInt16 maxValue );
    BARRELMAN_EXPORT bool DeleteUInt16PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt32PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt32 defaultValue, UInt32 minValue, UInt32 maxValue );
    BARRELMAN_EXPORT bool UpdateUInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, UInt32 defaultValue, UInt32 minValue, UInt32 maxValue );
    BARRELMAN_EXPORT bool DeleteUInt32PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt64PropertyDefinition( const ODBC::Connection& connection, Guid& id, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT bool UpdateUInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& elementType, const FixedDBWideString<127>& name, const WideString& description, Int64 defaultValue, Int64 minValue, Int64 maxValue );
    BARRELMAN_EXPORT bool DeleteUInt64PropertyDefinition( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarAlarmStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Types::AlarmState type );
    BARRELMAN_EXPORT bool UpdateRadarAlarmStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Types::AlarmState type );
    BARRELMAN_EXPORT bool DeleteRadarAlarmStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarCommand( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateRadarCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteRadarCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarCommandGetStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateRadarCommandGetStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteRadarCommandGetStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool UpdateRadarCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool DeleteRadarCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarCommandReplyGetStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationCount, Types::RadarPulse pulse, bool tx );
    BARRELMAN_EXPORT bool UpdateRadarCommandReplyGetStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationCount, Types::RadarPulse pulse, bool tx );
    BARRELMAN_EXPORT bool DeleteRadarCommandReplyGetStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 radarProtocolVersion, const FixedDBWideString<127>& radarIPAddress, Int32 radarPort, Int32 radarConfigurationPort, const TimeSpan& skipMagicTimeout, const TimeSpan& readTimeout, const TimeSpan& synchronizationInterval, Int32 targetsRefreshRate, Int32 range, Int32 sectorCount, Int32 sectorOffset, UInt32 imageColor, const DBUInt32& imageSubstitutionColor, UInt32 transparentColor, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY, Types::RadarImageType radarImageType, UInt32 trackColor, UInt32 vectorColor, bool enableNmea, const FixedDBWideString<127>& nmeaReceiverIPAddress, Int32 nmeaReceiverPort, const FixedDBWideString<127>& nmeaReceiverSourceId );
    BARRELMAN_EXPORT bool UpdateRadarConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 radarProtocolVersion, const FixedDBWideString<127>& radarIPAddress, Int32 radarPort, Int32 radarConfigurationPort, const TimeSpan& skipMagicTimeout, const TimeSpan& readTimeout, const TimeSpan& synchronizationInterval, Int32 targetsRefreshRate, Int32 range, Int32 sectorCount, Int32 sectorOffset, UInt32 imageColor, const DBUInt32& imageSubstitutionColor, UInt32 transparentColor, double imageScaleFactorX, double imageOffsetX, double imageScaleFactorY, double imageOffsetY, Types::RadarImageType radarImageType, UInt32 trackColor, UInt32 vectorColor, bool enableNmea, const FixedDBWideString<127>& nmeaReceiverIPAddress, Int32 nmeaReceiverPort, const FixedDBWideString<127>& nmeaReceiverSourceId );
    BARRELMAN_EXPORT bool DeleteRadarConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarImage( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, UInt32 depth, Int32 resolution, Int32 range, const Binary& image );
    BARRELMAN_EXPORT bool UpdateRadarImage( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, UInt32 depth, Int32 resolution, Int32 range, const Binary& image );
    BARRELMAN_EXPORT bool DeleteRadarImage( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarRawTrackTable( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 count, const Binary& table );
    BARRELMAN_EXPORT bool UpdateRadarRawTrackTable( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 count, const Binary& table );
    BARRELMAN_EXPORT bool DeleteRadarRawTrackTable( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarStatus( const ODBC::Connection& connection, Guid& id, const Guid& radar, const DateTime& timestamp, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationTime, Types::RadarPulse pulse, bool tx, bool tracking );
    BARRELMAN_EXPORT bool UpdateRadarStatus( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radar, const DateTime& timestamp, Int32 azimuthCount, Int32 triggerCount, const TimeSpan& rotationTime, Types::RadarPulse pulse, bool tx, bool tracking );
    BARRELMAN_EXPORT bool DeleteRadarStatus( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadioCommand( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateRadioCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteRadioCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadioCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool UpdateRadioCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool DeleteRadioCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadioConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radio, const DateTime& timestamp, double longitude, double latitude, const FixedDBWideString<127>& playbackUrl, const FixedDBWideString<127>& radioIPAddress, Int32 radioPort, const FixedDBWideString<127>& ed137IPAddress, Int32 ed137Port );
    BARRELMAN_EXPORT bool UpdateRadioConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radio, const DateTime& timestamp, double longitude, double latitude, const FixedDBWideString<127>& playbackUrl, const FixedDBWideString<127>& radioIPAddress, Int32 radioPort, const FixedDBWideString<127>& ed137IPAddress, Int32 ed137Port );
    BARRELMAN_EXPORT bool DeleteRadioConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadomeCommand( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateRadomeCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteRadomeCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadomeCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool UpdateRadomeCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool DeleteRadomeCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadomeConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& radome, const DateTime& timestamp, const TimeSpan& interval, double lowPressureLimit, double highPressureLimit, double lowTemperatureLimit, double highTemperatureLimit );
    BARRELMAN_EXPORT bool UpdateRadomeConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& radome, const DateTime& timestamp, const TimeSpan& interval, double lowPressureLimit, double highPressureLimit, double lowTemperatureLimit, double highTemperatureLimit );
    BARRELMAN_EXPORT bool DeleteRadomeConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertReferenceTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const Guid& value );
    BARRELMAN_EXPORT bool UpdateReferenceTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const Guid& value );
    BARRELMAN_EXPORT bool DeleteReferenceTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSByteTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBSByte& value );
    BARRELMAN_EXPORT bool UpdateSByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBSByte& value );
    BARRELMAN_EXPORT bool DeleteSByteTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSecurityDomain( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool UpdateSecurityDomain( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const WideString& description );
    BARRELMAN_EXPORT bool DeleteSecurityDomain( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSecurityLogin( const ODBC::Connection& connection, Guid& id, const Guid& domain, const FixedDBWideString<255>& identity, const WideString& description );
    BARRELMAN_EXPORT bool UpdateSecurityLogin( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& domain, const FixedDBWideString<255>& identity, const WideString& description );
    BARRELMAN_EXPORT bool DeleteSecurityLogin( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSecurityRole( const ODBC::Connection& connection, Guid& id, const Guid& domain, const FixedDBWideString<255>& identity, const WideString& description, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool UpdateSecurityRole( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& domain, const FixedDBWideString<255>& identity, const WideString& description, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool DeleteSecurityRole( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSecurityIdentifierRoleLink( const ODBC::Connection& connection, Guid& id, const Guid& member, const Guid& role, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool UpdateSecurityIdentifierRoleLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& member, const Guid& role, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool DeleteSecurityIdentifierRoleLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSecurityLoginSession( const ODBC::Connection& connection, Guid& id, const Guid& login, const DateTime& fromTime, const DBDateTime& throughTime, const Guid& clientSession, const FixedDBWideString<260>& notificationQueueName, const FixedDBWideString<260>& messageQueueName );
    BARRELMAN_EXPORT bool UpdateSecurityLoginSession( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& login, const DateTime& fromTime, const DBDateTime& throughTime, const Guid& clientSession, const FixedDBWideString<260>& notificationQueueName, const FixedDBWideString<260>& messageQueueName );
    BARRELMAN_EXPORT bool DeleteSecurityLoginSession( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSecurityPermission( const ODBC::Connection& connection, Guid& id, const Guid& identifier, const DateTime& timestamp, Int32 typeCode, bool canCreate, bool canRead, bool canUpdate, bool canDelete );
    BARRELMAN_EXPORT bool UpdateSecurityPermission( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& identifier, const DateTime& timestamp, Int32 typeCode, bool canCreate, bool canRead, bool canUpdate, bool canDelete );
    BARRELMAN_EXPORT bool DeleteSecurityPermission( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSingleTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBSingle& value );
    BARRELMAN_EXPORT bool UpdateSingleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBSingle& value );
    BARRELMAN_EXPORT bool DeleteSingleTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertStringTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const WideString& value );
    BARRELMAN_EXPORT bool UpdateStringTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const WideString& value );
    BARRELMAN_EXPORT bool DeleteStringTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBinaryTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateBinaryTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteBinaryTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertBooleanTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateBooleanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteBooleanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& aidToNavigation );
    BARRELMAN_EXPORT bool UpdateAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& aidToNavigation );
    BARRELMAN_EXPORT bool DeleteAisAidToNavigationOffPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDeviceEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& device );
    BARRELMAN_EXPORT bool UpdateDeviceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& device );
    BARRELMAN_EXPORT bool DeleteDeviceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarAutomaticSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarBlankSector1Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarBlankSector1Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarBlankSector1Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarBlankSector2Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarBlankSector2Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarBlankSector2Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarEnableAutomaticFrequencyControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarEnableFastTimeConstantTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarEnableSensitivityTimeControlTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarPowerOnTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarPowerOnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarPowerOnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarSaveSettingsTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarSaveSettingsTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarSaveSettingsTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarTrackingTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarTrackingTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarTrackingTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& proxySession );
    BARRELMAN_EXPORT bool UpdateMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& proxySession );
    BARRELMAN_EXPORT bool DeleteMediaProxySessionEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertMediaServiceEnabledTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& service );
    BARRELMAN_EXPORT bool UpdateMediaServiceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& service );
    BARRELMAN_EXPORT bool DeleteMediaServiceEnabledTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertByteTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDateTimeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateDateTimeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteDateTimeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertDoubleTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateDoubleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteDoubleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGNSSAltitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT bool UpdateGNSSAltitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT bool DeleteGNSSAltitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGNSSLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT bool UpdateGNSSLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT bool DeleteGNSSLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGNSSLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT bool UpdateGNSSLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gNSSDevice );
    BARRELMAN_EXPORT bool DeleteGNSSLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroCourseTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool UpdateGyroCourseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool DeleteGyroCourseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool UpdateGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool DeleteGyroHeadingMagneticNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool UpdateGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool DeleteGyroHeadingTrueNorthTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroPitchTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool UpdateGyroPitchTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool DeleteGyroPitchTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroRateOfTurnTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool UpdateGyroRateOfTurnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool DeleteGyroRateOfTurnTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroRollTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool UpdateGyroRollTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool DeleteGyroRollTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGyroSpeedTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool UpdateGyroSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& gyroDevice );
    BARRELMAN_EXPORT bool DeleteGyroSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadomeDewPointTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radome );
    BARRELMAN_EXPORT bool UpdateRadomeDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radome );
    BARRELMAN_EXPORT bool DeleteRadomeDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadomePressureTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radome );
    BARRELMAN_EXPORT bool UpdateRadomePressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radome );
    BARRELMAN_EXPORT bool DeleteRadomePressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadomeTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radome );
    BARRELMAN_EXPORT bool UpdateRadomeTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radome );
    BARRELMAN_EXPORT bool DeleteRadomeTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertVesselDraughtTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& vessel );
    BARRELMAN_EXPORT bool UpdateVesselDraughtTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& vessel );
    BARRELMAN_EXPORT bool DeleteVesselDraughtTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertViewLatitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& view );
    BARRELMAN_EXPORT bool UpdateViewLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& view );
    BARRELMAN_EXPORT bool DeleteViewLatitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertViewLongitudeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& view );
    BARRELMAN_EXPORT bool UpdateViewLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& view );
    BARRELMAN_EXPORT bool DeleteViewLongitudeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertViewZoomLevelTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& view );
    BARRELMAN_EXPORT bool UpdateViewZoomLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& view );
    BARRELMAN_EXPORT bool DeleteViewZoomLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool UpdateWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool DeleteWeatherStationAbsoluteHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool UpdateWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool DeleteWeatherStationAirTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool UpdateWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool DeleteWeatherStationBarometricPressureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationDewPointTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool UpdateWeatherStationDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool DeleteWeatherStationDewPointTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool UpdateWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool DeleteWeatherStationRelativeHumidityTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool UpdateWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool DeleteWeatherStationWaterTemperatureTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool UpdateWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool DeleteWeatherStationWindDirectionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool UpdateWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& weatherStation );
    BARRELMAN_EXPORT bool DeleteWeatherStationWindSpeedTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGeoPosition2DTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateGeoPosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteGeoPosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& aidToNavigation );
    BARRELMAN_EXPORT bool UpdateAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& aidToNavigation );
    BARRELMAN_EXPORT bool DeleteAisAidToNavigationPositionTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGeoPosition3DTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateGeoPosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteGeoPosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertGuidTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateGuidTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteGuidTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt16Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt32Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarAzimuthOffsetTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarFastTimeConstantLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarFastTimeConstantModeTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarPulseTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarPulseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarPulseTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarSector1EndTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarSector1EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarSector1EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarSector1StartTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarSector1StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarSector1StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarSector2EndTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarSector2EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarSector2EndTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarSector2StartTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarSector2StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarSector2StartTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarSensitivityTimeControlLevelTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadarTuningTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool UpdateRadarTuningTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radar );
    BARRELMAN_EXPORT bool DeleteRadarTuningTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& vessel );
    BARRELMAN_EXPORT bool UpdateVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& vessel );
    BARRELMAN_EXPORT bool DeleteVesselPersonsOnBoardTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertInt64Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertPosition2DTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdatePosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeletePosition2DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertPosition3DTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdatePosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeletePosition3DTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertReferenceTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateReferenceTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteReferenceTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSByteTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateSByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteSByteTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertSingleTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateSingleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteSingleTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertStringTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateStringTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteStringTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTimeSpanTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateTimeSpanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteTimeSpanTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt16Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateUInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteUInt16Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt32Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateUInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteUInt32Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertRadomeStatusTimeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radome );
    BARRELMAN_EXPORT bool UpdateRadomeStatusTimeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention, const DBGuid& radome );
    BARRELMAN_EXPORT bool DeleteRadomeStatusTimeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt64Timeseries( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool UpdateUInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name, const TimeSpan& maxRetention );
    BARRELMAN_EXPORT bool DeleteUInt64Timeseries( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTimeseriesCatalog( const ODBC::Connection& connection, Guid& id, const DBGuid& catalog, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool UpdateTimeseriesCatalog( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBGuid& catalog, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool DeleteTimeseriesCatalog( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTimeseriesInfo( const ODBC::Connection& connection, Guid& id, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count );
    BARRELMAN_EXPORT bool UpdateTimeseriesInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count );
    BARRELMAN_EXPORT bool DeleteTimeseriesInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTimeSpanTimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBTimeSpan& value );
    BARRELMAN_EXPORT bool UpdateTimeSpanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBTimeSpan& value );
    BARRELMAN_EXPORT bool DeleteTimeSpanTimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTrackableItemTrackLink( const ODBC::Connection& connection, Guid& id, const Guid& item, const Guid& track, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool UpdateTrackableItemTrackLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& item, const Guid& track, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool DeleteTrackableItemTrackLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTrack( const ODBC::Connection& connection, Guid& id, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp );
    BARRELMAN_EXPORT bool UpdateTrack( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp );
    BARRELMAN_EXPORT bool DeleteTrack( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTrack3D( const ODBC::Connection& connection, Guid& id, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp );
    BARRELMAN_EXPORT bool UpdateTrack3D( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, Int64 trackNumber, const DateTime& timestamp );
    BARRELMAN_EXPORT bool DeleteTrack3D( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTrackerFilterParameters( const ODBC::Connection& connection, Guid& id, const Guid& tracker, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool UpdateTrackerFilterParameters( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& tracker, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool DeleteTrackerFilterParameters( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTrackerFilterParametersConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& parameters, const DateTime& timestamp, bool useNaivePredictor, Int32 numberOfPoints, Int32 windowSize, Int32 stabilizeCount, Int32 maxBadPoints, Types::TrackerFilterModelType modelType, double sigmaR, double sigmaAcc, double tauVel, double tauAcc, double deltaRMin, double deltaVMax, double deltaAMax );
    BARRELMAN_EXPORT bool UpdateTrackerFilterParametersConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& parameters, const DateTime& timestamp, bool useNaivePredictor, Int32 numberOfPoints, Int32 windowSize, Int32 stabilizeCount, Int32 maxBadPoints, Types::TrackerFilterModelType modelType, double sigmaR, double sigmaAcc, double tauVel, double tauAcc, double deltaRMin, double deltaVMax, double deltaAMax );
    BARRELMAN_EXPORT bool DeleteTrackerFilterParametersConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTrackInfo( const ODBC::Connection& connection, Guid& id, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count, const DBDouble& northWestLatitude, const DBDouble& northWestLongitude, const DBDouble& southEastLatitude, const DBDouble& southEastLongitude );
    BARRELMAN_EXPORT bool UpdateTrackInfo( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DBDateTime& firstTimestamp, const DBDateTime& lastTimestamp, Int64 count, const DBDouble& northWestLatitude, const DBDouble& northWestLongitude, const DBDouble& southEastLatitude, const DBDouble& southEastLongitude );
    BARRELMAN_EXPORT bool DeleteTrackInfo( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTrackingServiceOptions( const ODBC::Connection& connection, Guid& id, const DateTime& timestamp, const TimeSpan& timerInterval, const TimeSpan& maxAgeOfCurrentTrackValue, double falseThreshold, double distanceThreshold, double distanceUnmergeThreshold, Int64 unmergeLatency, bool kalmanFiltering, double maxCourseDeviation, double maxSpeedDeviation, double minimumSpeedThreshold );
    BARRELMAN_EXPORT bool UpdateTrackingServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const DateTime& timestamp, const TimeSpan& timerInterval, const TimeSpan& maxAgeOfCurrentTrackValue, double falseThreshold, double distanceThreshold, double distanceUnmergeThreshold, Int64 unmergeLatency, bool kalmanFiltering, double maxCourseDeviation, double maxSpeedDeviation, double minimumSpeedThreshold );
    BARRELMAN_EXPORT bool DeleteTrackingServiceOptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTrackLink( const ODBC::Connection& connection, Guid& id, const Guid& primary, const Guid& secondary, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool UpdateTrackLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& primary, const Guid& secondary, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool DeleteTrackLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTrackValue( const ODBC::Connection& connection, Guid& id, const Guid& track, const DateTime& timestamp, Types::TrackFlags flags, Types::TrackStatus status, double latitude, double longitude, double speed, double course, double heading );
    BARRELMAN_EXPORT bool UpdateTrackValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const DateTime& timestamp, Types::TrackFlags flags, Types::TrackStatus status, double latitude, double longitude, double speed, double course, double heading );
    BARRELMAN_EXPORT bool DeleteTrackValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertTrackValue3D( const ODBC::Connection& connection, Guid& id, const Guid& track, const DateTime& timestamp, Types::TrackFlags3D flags, UInt32 status, double latitude, double longitude, double altitude, double speed, double course, double rateOfClimb );
    BARRELMAN_EXPORT bool UpdateTrackValue3D( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const DateTime& timestamp, Types::TrackFlags3D flags, UInt32 status, double latitude, double longitude, double altitude, double speed, double course, double rateOfClimb );
    BARRELMAN_EXPORT bool DeleteTrackValue3D( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt16TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBUInt16& value );
    BARRELMAN_EXPORT bool UpdateUInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBUInt16& value );
    BARRELMAN_EXPORT bool DeleteUInt16TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt32TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBUInt32& value );
    BARRELMAN_EXPORT bool UpdateUInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBUInt32& value );
    BARRELMAN_EXPORT bool DeleteUInt32TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertUInt64TimeseriesValue( const ODBC::Connection& connection, Guid& id, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value );
    BARRELMAN_EXPORT bool UpdateUInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& timeseries, const DateTime& timestamp, const DBInt64& value );
    BARRELMAN_EXPORT bool DeleteUInt64TimeseriesValue( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertVehicleType( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool UpdateVehicleType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name );
    BARRELMAN_EXPORT bool DeleteVehicleType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertVesselType( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, Int32 code );
    BARRELMAN_EXPORT bool UpdateVesselType( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, Int32 code );
    BARRELMAN_EXPORT bool DeleteVesselType( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertView( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, const DBGuid& latitudeTimeseries, const DBGuid& longitudeTimeseries, const DBGuid& zoomLevelTimeseries );
    BARRELMAN_EXPORT bool UpdateView( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, const DBGuid& latitudeTimeseries, const DBGuid& longitudeTimeseries, const DBGuid& zoomLevelTimeseries );
    BARRELMAN_EXPORT bool DeleteView( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertViewCameraLink( const ODBC::Connection& connection, Guid& id, const Guid& view, const Guid& camera, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool UpdateViewCameraLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, const Guid& camera, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool DeleteViewCameraLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertViewTrackerLink( const ODBC::Connection& connection, Guid& id, const Guid& view, const Guid& tracker, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool UpdateViewTrackerLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& view, const Guid& tracker, const DateTime& start, const DBDateTime& end );
    BARRELMAN_EXPORT bool DeleteViewTrackerLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationCommand( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool UpdateWeatherStationCommand( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, Types::DeviceCommandSourceType deviceCommandSourceType, const Guid& deviceCommandSourceId, const DBGuid& reply );
    BARRELMAN_EXPORT bool DeleteWeatherStationCommand( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationCommandReply( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool UpdateWeatherStationCommandReply( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, const DBGuid& command, Types::DeviceCommandReplyStatus status, const WideString& message );
    BARRELMAN_EXPORT bool DeleteWeatherStationCommandReply( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertWeatherStationConfiguration( const ODBC::Connection& connection, Guid& id, const Guid& weatherStation, const DateTime& timestamp, const TimeSpan& noDataTimeOut, const TimeSpan& sendInterval, double latitude, double longitude, double gyroOffset, bool enableAveraging, const TimeSpan& averagingInterval );
    BARRELMAN_EXPORT bool UpdateWeatherStationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& weatherStation, const DateTime& timestamp, const TimeSpan& noDataTimeOut, const TimeSpan& sendInterval, double latitude, double longitude, double gyroOffset, bool enableAveraging, const TimeSpan& averagingInterval );
    BARRELMAN_EXPORT bool DeleteWeatherStationConfiguration( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertCircularZone( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, double longitude, double latitude, Types::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, double radius );
    BARRELMAN_EXPORT bool UpdateCircularZone( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, double longitude, double latitude, Types::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, double radius );
    BARRELMAN_EXPORT bool DeleteCircularZone( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertPolygonZone( const ODBC::Connection& connection, Guid& id, const FixedDBWideString<127>& name, double longitude, double latitude, Types::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, const Binary& polygon );
    BARRELMAN_EXPORT bool UpdatePolygonZone( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const FixedDBWideString<127>& name, double longitude, double latitude, Types::ZoneAlarmType alarmType, const TimeSpan& alarmTime, const TimeSpan& radarTrackMinimumLifetime, double speed, UInt32 strokeColor, UInt32 fillColor, const Binary& polygon );
    BARRELMAN_EXPORT bool DeletePolygonZone( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertZoneExceptions( const ODBC::Connection& connection, Guid& id, const Guid& zone, const DateTime& timestamp );
    BARRELMAN_EXPORT bool UpdateZoneExceptions( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zone, const DateTime& timestamp );
    BARRELMAN_EXPORT bool DeleteZoneExceptions( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertZoneExceptionsVesselLink( const ODBC::Connection& connection, Guid& id, const Guid& zoneExceptions, const Guid& vessel );
    BARRELMAN_EXPORT bool UpdateZoneExceptionsVesselLink( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& zoneExceptions, const Guid& vessel );
    BARRELMAN_EXPORT bool DeleteZoneExceptionsVesselLink( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

    BARRELMAN_EXPORT bool InsertZoneTrackAlarm( const ODBC::Connection& connection, Guid& id, const Guid& track, const Guid& zone, const DBGuid& radarTrack, const DateTime& timestamp, double latitude, double longitude, double speed, const DBDouble& course, const DBDouble& heading, double enterLatitude, double enterLongitude, const DBDouble& leaveLatitude, const DBDouble& leaveLongitude );
    BARRELMAN_EXPORT bool UpdateZoneTrackAlarm( const ODBC::Connection& connection, const Guid& id, Int64& rowVersion, const Guid& track, const Guid& zone, const DBGuid& radarTrack, const DateTime& timestamp, double latitude, double longitude, double speed, const DBDouble& course, const DBDouble& heading, double enterLatitude, double enterLongitude, const DBDouble& leaveLatitude, const DBDouble& leaveLongitude );
    BARRELMAN_EXPORT bool DeleteZoneTrackAlarm( const ODBC::Connection& connection, const Guid& id, Int64 rowVersion );

}
#endif
