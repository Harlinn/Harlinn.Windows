#include "pch.h"

#include "MsSqlComplexDatabaseReaders.h"


namespace Barrelman::Databases::MsSql
{

    WideString ComplexAisMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  am.[Id], \r\n"
        L"  am.[EntityType], \r\n"
        L"  am.[RowVersion], \r\n"
        L"  am.[AisDevice], \r\n"
        L"  am.[ReceivedTimestamp], \r\n"
        L"  am.[MessageSequenceNumber], \r\n"
        L"  am.[Repeat], \r\n"
        L"  am.[Mmsi], \r\n"
        L"  atnrm.[NavigationalAidType], \r\n"
        L"  atnrm.[Name], \r\n"
        L"  atnrm.[PositionAccuracy], \r\n"
        L"  atnrm.[Longitude], \r\n"
        L"  atnrm.[Latitude], \r\n"
        L"  atnrm.[DimensionToBow], \r\n"
        L"  atnrm.[DimensionToStern], \r\n"
        L"  atnrm.[DimensionToPort], \r\n"
        L"  atnrm.[DimensionToStarboard], \r\n"
        L"  atnrm.[PositionFixType], \r\n"
        L"  atnrm.[Timestamp], \r\n"
        L"  atnrm.[OffPosition], \r\n"
        L"  atnrm.[RegionalReserved], \r\n"
        L"  atnrm.[Raim], \r\n"
        L"  atnrm.[VirtualAid], \r\n"
        L"  atnrm.[Assigned], \r\n"
        L"  atnrm.[Spare], \r\n"
        L"  atnrm.[NameExtension], \r\n"
        L"  aasrm.[SequenceNumber], \r\n"
        L"  aasrm.[DestinationMmsi], \r\n"
        L"  aasrm.[RetransmitFlag], \r\n"
        L"  aasrm.[Spare], \r\n"
        L"  aasrm.[Text], \r\n"
        L"  absrm.[Timestamp], \r\n"
        L"  absrm.[PositionAccuracy], \r\n"
        L"  absrm.[Longitude], \r\n"
        L"  absrm.[Latitude], \r\n"
        L"  absrm.[PositionFixType], \r\n"
        L"  absrm.[Spare], \r\n"
        L"  absrm.[Raim], \r\n"
        L"  absrm.[RadioStatus], \r\n"
        L"  abac.[Spare], \r\n"
        L"  abac.[SequenceNumber1], \r\n"
        L"  abac.[Mmsi1], \r\n"
        L"  abac.[SequenceNumber2], \r\n"
        L"  abac.[Mmsi2], \r\n"
        L"  abac.[SequenceNumber3], \r\n"
        L"  abac.[Mmsi3], \r\n"
        L"  abac.[SequenceNumber4], \r\n"
        L"  abac.[Mmsi4], \r\n"
        L"  abam.[SequenceNumber], \r\n"
        L"  abam.[DestinationMmsi], \r\n"
        L"  abam.[RetransmitFlag], \r\n"
        L"  abam.[Spare], \r\n"
        L"  abam.[DesignatedAreaCode], \r\n"
        L"  abam.[FunctionalId], \r\n"
        L"  abbm.[Spare], \r\n"
        L"  abbm.[DesignatedAreaCode], \r\n"
        L"  abbm.[FunctionalId], \r\n"
        L"  adlmm.[Spare], \r\n"
        L"  adlmm.[Offset1], \r\n"
        L"  adlmm.[ReservedSlots1], \r\n"
        L"  adlmm.[Timeout1], \r\n"
        L"  adlmm.[Increment1], \r\n"
        L"  adlmm.[Offset2], \r\n"
        L"  adlmm.[ReservedSlots2], \r\n"
        L"  adlmm.[Timeout2], \r\n"
        L"  adlmm.[Increment2], \r\n"
        L"  adlmm.[Offset3], \r\n"
        L"  adlmm.[ReservedSlots3], \r\n"
        L"  adlmm.[Timeout3], \r\n"
        L"  adlmm.[Increment3], \r\n"
        L"  adlmm.[Offset4], \r\n"
        L"  adlmm.[ReservedSlots4], \r\n"
        L"  adlmm.[Timeout4], \r\n"
        L"  adlmm.[Increment4], \r\n"
        L"  aecbprm.[Reserved], \r\n"
        L"  aecbprm.[SpeedOverGround], \r\n"
        L"  aecbprm.[PositionAccuracy], \r\n"
        L"  aecbprm.[Longitude], \r\n"
        L"  aecbprm.[Latitude], \r\n"
        L"  aecbprm.[CourseOverGround], \r\n"
        L"  aecbprm.[TrueHeading], \r\n"
        L"  aecbprm.[Timestamp], \r\n"
        L"  aecbprm.[RegionalReserved], \r\n"
        L"  aecbprm.[Name], \r\n"
        L"  aecbprm.[ShipType], \r\n"
        L"  aecbprm.[DimensionToBow], \r\n"
        L"  aecbprm.[DimensionToStern], \r\n"
        L"  aecbprm.[DimensionToPort], \r\n"
        L"  aecbprm.[DimensionToStarboard], \r\n"
        L"  aecbprm.[PositionFixType], \r\n"
        L"  aecbprm.[Raim], \r\n"
        L"  aecbprm.[DataTerminalReady], \r\n"
        L"  aecbprm.[Assigned], \r\n"
        L"  aecbprm.[Spare], \r\n"
        L"  aim.[InterrogatedMmsi], \r\n"
        L"  aim.[FirstMessageType], \r\n"
        L"  aim.[FirstSlotOffset], \r\n"
        L"  aim.[SecondMessageType], \r\n"
        L"  aim.[SecondSlotOffset], \r\n"
        L"  aim.[SecondStationInterrogationMmsi], \r\n"
        L"  aim.[SecondStationFirstMessageType], \r\n"
        L"  aim.[SecondStationFirstSlotOffset], \r\n"
        L"  aprcab.[NavigationStatus], \r\n"
        L"  aprcab.[RateOfTurn], \r\n"
        L"  aprcab.[SpeedOverGround], \r\n"
        L"  aprcab.[PositionAccuracy], \r\n"
        L"  aprcab.[Longitude], \r\n"
        L"  aprcab.[Latitude], \r\n"
        L"  aprcab.[CourseOverGround], \r\n"
        L"  aprcab.[TrueHeading], \r\n"
        L"  aprcab.[Timestamp], \r\n"
        L"  aprcab.[ManeuverIndicator], \r\n"
        L"  aprcab.[Spare], \r\n"
        L"  aprcab.[Raim], \r\n"
        L"  aprcab.[RadioStatus], \r\n"
        L"  aprflram.[PositionAccuracy], \r\n"
        L"  aprflram.[Raim], \r\n"
        L"  aprflram.[NavigationStatus], \r\n"
        L"  aprflram.[Longitude], \r\n"
        L"  aprflram.[Latitude], \r\n"
        L"  aprflram.[SpeedOverGround], \r\n"
        L"  aprflram.[CourseOverGround], \r\n"
        L"  aprflram.[GnssPositionStatus], \r\n"
        L"  aprflram.[Spare], \r\n"
        L"  asram.[Spare], \r\n"
        L"  asram.[SequenceNumber1], \r\n"
        L"  asram.[Mmsi1], \r\n"
        L"  asram.[SequenceNumber2], \r\n"
        L"  asram.[Mmsi2], \r\n"
        L"  asram.[SequenceNumber3], \r\n"
        L"  asram.[Mmsi3], \r\n"
        L"  asram.[SequenceNumber4], \r\n"
        L"  asram.[Mmsi4], \r\n"
        L"  ascbprm.[Reserved], \r\n"
        L"  ascbprm.[SpeedOverGround], \r\n"
        L"  ascbprm.[PositionAccuracy], \r\n"
        L"  ascbprm.[Longitude], \r\n"
        L"  ascbprm.[Latitude], \r\n"
        L"  ascbprm.[CourseOverGround], \r\n"
        L"  ascbprm.[TrueHeading], \r\n"
        L"  ascbprm.[Timestamp], \r\n"
        L"  ascbprm.[RegionalReserved], \r\n"
        L"  ascbprm.[IsCsUnit], \r\n"
        L"  ascbprm.[HasDisplay], \r\n"
        L"  ascbprm.[HasDscCapability], \r\n"
        L"  ascbprm.[Band], \r\n"
        L"  ascbprm.[CanAcceptMessage22], \r\n"
        L"  ascbprm.[Assigned], \r\n"
        L"  ascbprm.[Raim], \r\n"
        L"  ascbprm.[RadioStatus], \r\n"
        L"  assaprm.[Altitude], \r\n"
        L"  assaprm.[SpeedOverGround], \r\n"
        L"  assaprm.[PositionAccuracy], \r\n"
        L"  assaprm.[Longitude], \r\n"
        L"  assaprm.[Latitude], \r\n"
        L"  assaprm.[CourseOverGround], \r\n"
        L"  assaprm.[Timestamp], \r\n"
        L"  assaprm.[Reserved], \r\n"
        L"  assaprm.[DataTerminalReady], \r\n"
        L"  assaprm.[Spare], \r\n"
        L"  assaprm.[Assigned], \r\n"
        L"  assaprm.[Raim], \r\n"
        L"  assaprm.[RadioStatus], \r\n"
        L"  asavrdm.[AisVersion], \r\n"
        L"  asavrdm.[ImoNumber], \r\n"
        L"  asavrdm.[Callsign], \r\n"
        L"  asavrdm.[ShipName], \r\n"
        L"  asavrdm.[ShipType], \r\n"
        L"  asavrdm.[DimensionToBow], \r\n"
        L"  asavrdm.[DimensionToStern], \r\n"
        L"  asavrdm.[DimensionToPort], \r\n"
        L"  asavrdm.[DimensionToStarboard], \r\n"
        L"  asavrdm.[PositionFixType], \r\n"
        L"  asavrdm.[EstimatedTimeOfArrival], \r\n"
        L"  asavrdm.[Draught], \r\n"
        L"  asavrdm.[Destination], \r\n"
        L"  asavrdm.[DataTerminalReady], \r\n"
        L"  asavrdm.[Spare], \r\n"
        L"  asdrm.[PartNumber], \r\n"
        L"  asdrpa.[ShipName], \r\n"
        L"  asdrpa.[Spare], \r\n"
        L"  asdrpb.[ShipType], \r\n"
        L"  asdrpb.[VendorId], \r\n"
        L"  asdrpb.[UnitModelCode], \r\n"
        L"  asdrpb.[SerialNumber], \r\n"
        L"  asdrpb.[Callsign], \r\n"
        L"  asdrpb.[DimensionToBow], \r\n"
        L"  asdrpb.[DimensionToStern], \r\n"
        L"  asdrpb.[DimensionToPort], \r\n"
        L"  asdrpb.[DimensionToStarboard], \r\n"
        L"  asdrpb.[MothershipMmsi], \r\n"
        L"  asdrpb.[PositionFixType], \r\n"
        L"  asdrpb.[Spare], \r\n"
        L"  auadim.[Spare1], \r\n"
        L"  auadim.[DestinationMmsi], \r\n"
        L"  auadim.[Spare2], \r\n"
        L"  auadrm.[Datetime], \r\n"
        L"  auadrm.[PositionAccuracy], \r\n"
        L"  auadrm.[Longitude], \r\n"
        L"  auadrm.[Latitude], \r\n"
        L"  auadrm.[PositionFixType], \r\n"
        L"  auadrm.[Spare], \r\n"
        L"  auadrm.[Raim], \r\n"
        L"  auadrm.[RadioStatus], \r\n"
        L"  abam.[Data], \r\n"
        L"  abbm.[Data] \r\n"
        L"FROM [AisMessageView] am \r\n"
        L"  LEFT JOIN [AidToNavigationReportMessage] atnrm ON(am.[Id] = atnrm.[Id] ) \r\n"
        L"  LEFT JOIN [AisAddressedSafetyRelatedMessage] aasrm ON(am.[Id] = aasrm.[Id] ) \r\n"
        L"  LEFT JOIN [AisBaseStationReportMessage] absrm ON(am.[Id] = absrm.[Id] ) \r\n"
        L"  LEFT JOIN [AisBinaryAcknowledgeMessage] abac ON(am.[Id] = abac.[Id] ) \r\n"
        L"  LEFT JOIN [AisBinaryAddressedMessage] abam ON(am.[Id] = abam.[Id] ) \r\n"
        L"  LEFT JOIN [AisBinaryBroadcastMessage] abbm ON(am.[Id] = abbm.[Id] ) \r\n"
        L"  LEFT JOIN [AisDataLinkManagementMessage] adlmm ON(am.[Id] = adlmm.[Id] ) \r\n"
        L"  LEFT JOIN [AisExtendedClassBCsPositionReportMessage] aecbprm ON(am.[Id] = aecbprm.[Id] ) \r\n"
        L"  LEFT JOIN [AisInterrogationMessage] aim ON(am.[Id] = aim.[Id] ) \r\n"
        L"  LEFT JOIN [AisPositionReportClassAMessageBase] aprcab ON(am.[Id] = aprcab.[Id] ) \r\n"
        L"  LEFT JOIN [AisPositionReportClassAAssignedScheduleMessage] aprcasm ON(am.[Id] = aprcasm.[Id] ) \r\n"
        L"  LEFT JOIN [AisPositionReportClassAMessage] aprca ON(am.[Id] = aprca.[Id] ) \r\n"
        L"  LEFT JOIN [AisPositionReportClassAResponseToInterrogationMessage] aprcatim ON(am.[Id] = aprcatim.[Id] ) \r\n"
        L"  LEFT JOIN [AisPositionReportForLongRangeApplicationsMessage] aprflram ON(am.[Id] = aprflram.[Id] ) \r\n"
        L"  LEFT JOIN [AisSafetyRelatedAcknowledgmentMessage] asram ON(am.[Id] = asram.[Id] ) \r\n"
        L"  LEFT JOIN [AisStandardClassBCsPositionReportMessage] ascbprm ON(am.[Id] = ascbprm.[Id] ) \r\n"
        L"  LEFT JOIN [AisStandardSarAircraftPositionReportMessage] assaprm ON(am.[Id] = assaprm.[Id] ) \r\n"
        L"  LEFT JOIN [AisStaticAndVoyageRelatedDataMessage] asavrdm ON(am.[Id] = asavrdm.[Id] ) \r\n"
        L"  LEFT JOIN [AisStaticDataReportMessage] asdrm ON(am.[Id] = asdrm.[Id] ) \r\n"
        L"  LEFT JOIN [AisStaticDataReportPartAMessage] asdrpa ON(am.[Id] = asdrpa.[Id] ) \r\n"
        L"  LEFT JOIN [AisStaticDataReportPartBMessage] asdrpb ON(am.[Id] = asdrpb.[Id] ) \r\n"
        L"  LEFT JOIN [AisUtcAndDateInquiryMessage] auadim ON(am.[Id] = auadim.[Id] ) \r\n"
        L"  LEFT JOIN [AisUtcAndDateResponseMessage] auadrm ON(am.[Id] = auadrm.[Id] )";
    WideString ComplexAisMessageColumnData::BaseViewName = L"AisMessageView";
    WideString ComplexAisMessageColumnData::ViewAliasName = L"am";

    void ComplexAisMessageColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, AM_ID_FIELD_ID, id_ );
        Bind( statement, AM_KIND_FIELD_ID, kind_ );
        Bind( statement, AM_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, AM_AISDEVICE_FIELD_ID, aisDevice_ );
        Bind( statement, AM_RECEIVEDTIMESTAMP_FIELD_ID, receivedTimestamp_ );
        Bind( statement, AM_MESSAGESEQUENCENUMBER_FIELD_ID, messageSequenceNumber_ );
        Bind( statement, AM_REPEAT_FIELD_ID, repeat_ );
        Bind( statement, AM_MMSI_FIELD_ID, mmsi_ );
        Bind( statement, ATNRM_NAVIGATIONALAIDTYPE_FIELD_ID, atnrmNavigationalAidType_ );
        Bind( statement, ATNRM_NAME_FIELD_ID, atnrmName_ );
        Bind( statement, ATNRM_POSITIONACCURACY_FIELD_ID, atnrmPositionAccuracy_ );
        Bind( statement, ATNRM_LONGITUDE_FIELD_ID, atnrmLongitude_ );
        Bind( statement, ATNRM_LATITUDE_FIELD_ID, atnrmLatitude_ );
        Bind( statement, ATNRM_DIMENSIONTOBOW_FIELD_ID, atnrmDimensionToBow_ );
        Bind( statement, ATNRM_DIMENSIONTOSTERN_FIELD_ID, atnrmDimensionToStern_ );
        Bind( statement, ATNRM_DIMENSIONTOPORT_FIELD_ID, atnrmDimensionToPort_ );
        Bind( statement, ATNRM_DIMENSIONTOSTARBOARD_FIELD_ID, atnrmDimensionToStarboard_ );
        Bind( statement, ATNRM_POSITIONFIXTYPE_FIELD_ID, atnrmPositionFixType_ );
        Bind( statement, ATNRM_TIMESTAMP_FIELD_ID, atnrmTimestamp_ );
        Bind( statement, ATNRM_OFFPOSITION_FIELD_ID, atnrmOffPosition_ );
        Bind( statement, ATNRM_REGIONALRESERVED_FIELD_ID, atnrmRegionalReserved_ );
        Bind( statement, ATNRM_RAIM_FIELD_ID, atnrmRaim_ );
        Bind( statement, ATNRM_VIRTUALAID_FIELD_ID, atnrmVirtualAid_ );
        Bind( statement, ATNRM_ASSIGNED_FIELD_ID, atnrmAssigned_ );
        Bind( statement, ATNRM_SPARE_FIELD_ID, atnrmSpare_ );
        Bind( statement, ATNRM_NAMEEXTENSION_FIELD_ID, atnrmNameExtension_ );
        Bind( statement, AASRM_SEQUENCENUMBER_FIELD_ID, aasrmSequenceNumber_ );
        Bind( statement, AASRM_DESTINATIONMMSI_FIELD_ID, aasrmDestinationMmsi_ );
        Bind( statement, AASRM_RETRANSMITFLAG_FIELD_ID, aasrmRetransmitFlag_ );
        Bind( statement, AASRM_SPARE_FIELD_ID, aasrmSpare_ );
        Bind( statement, AASRM_TEXT_FIELD_ID, aasrmText_ );
        Bind( statement, ABSRM_TIMESTAMP_FIELD_ID, absrmTimestamp_ );
        Bind( statement, ABSRM_POSITIONACCURACY_FIELD_ID, absrmPositionAccuracy_ );
        Bind( statement, ABSRM_LONGITUDE_FIELD_ID, absrmLongitude_ );
        Bind( statement, ABSRM_LATITUDE_FIELD_ID, absrmLatitude_ );
        Bind( statement, ABSRM_POSITIONFIXTYPE_FIELD_ID, absrmPositionFixType_ );
        Bind( statement, ABSRM_SPARE_FIELD_ID, absrmSpare_ );
        Bind( statement, ABSRM_RAIM_FIELD_ID, absrmRaim_ );
        Bind( statement, ABSRM_RADIOSTATUS_FIELD_ID, absrmRadioStatus_ );
        Bind( statement, ABAC_SPARE_FIELD_ID, abacSpare_ );
        Bind( statement, ABAC_SEQUENCENUMBER1_FIELD_ID, abacSequenceNumber1_ );
        Bind( statement, ABAC_MMSI1_FIELD_ID, abacMmsi1_ );
        Bind( statement, ABAC_SEQUENCENUMBER2_FIELD_ID, abacSequenceNumber2_ );
        Bind( statement, ABAC_MMSI2_FIELD_ID, abacMmsi2_ );
        Bind( statement, ABAC_SEQUENCENUMBER3_FIELD_ID, abacSequenceNumber3_ );
        Bind( statement, ABAC_MMSI3_FIELD_ID, abacMmsi3_ );
        Bind( statement, ABAC_SEQUENCENUMBER4_FIELD_ID, abacSequenceNumber4_ );
        Bind( statement, ABAC_MMSI4_FIELD_ID, abacMmsi4_ );
        Bind( statement, ABAM_SEQUENCENUMBER_FIELD_ID, abamSequenceNumber_ );
        Bind( statement, ABAM_DESTINATIONMMSI_FIELD_ID, abamDestinationMmsi_ );
        Bind( statement, ABAM_RETRANSMITFLAG_FIELD_ID, abamRetransmitFlag_ );
        Bind( statement, ABAM_SPARE_FIELD_ID, abamSpare_ );
        Bind( statement, ABAM_DESIGNATEDAREACODE_FIELD_ID, abamDesignatedAreaCode_ );
        Bind( statement, ABAM_FUNCTIONALID_FIELD_ID, abamFunctionalId_ );
        Bind( statement, ABBM_SPARE_FIELD_ID, abbmSpare_ );
        Bind( statement, ABBM_DESIGNATEDAREACODE_FIELD_ID, abbmDesignatedAreaCode_ );
        Bind( statement, ABBM_FUNCTIONALID_FIELD_ID, abbmFunctionalId_ );
        Bind( statement, ADLMM_SPARE_FIELD_ID, adlmmSpare_ );
        Bind( statement, ADLMM_OFFSET1_FIELD_ID, adlmmOffset1_ );
        Bind( statement, ADLMM_RESERVEDSLOTS1_FIELD_ID, adlmmReservedSlots1_ );
        Bind( statement, ADLMM_TIMEOUT1_FIELD_ID, adlmmTimeout1_ );
        Bind( statement, ADLMM_INCREMENT1_FIELD_ID, adlmmIncrement1_ );
        Bind( statement, ADLMM_OFFSET2_FIELD_ID, adlmmOffset2_ );
        Bind( statement, ADLMM_RESERVEDSLOTS2_FIELD_ID, adlmmReservedSlots2_ );
        Bind( statement, ADLMM_TIMEOUT2_FIELD_ID, adlmmTimeout2_ );
        Bind( statement, ADLMM_INCREMENT2_FIELD_ID, adlmmIncrement2_ );
        Bind( statement, ADLMM_OFFSET3_FIELD_ID, adlmmOffset3_ );
        Bind( statement, ADLMM_RESERVEDSLOTS3_FIELD_ID, adlmmReservedSlots3_ );
        Bind( statement, ADLMM_TIMEOUT3_FIELD_ID, adlmmTimeout3_ );
        Bind( statement, ADLMM_INCREMENT3_FIELD_ID, adlmmIncrement3_ );
        Bind( statement, ADLMM_OFFSET4_FIELD_ID, adlmmOffset4_ );
        Bind( statement, ADLMM_RESERVEDSLOTS4_FIELD_ID, adlmmReservedSlots4_ );
        Bind( statement, ADLMM_TIMEOUT4_FIELD_ID, adlmmTimeout4_ );
        Bind( statement, ADLMM_INCREMENT4_FIELD_ID, adlmmIncrement4_ );
        Bind( statement, AECBPRM_RESERVED_FIELD_ID, aecbprmReserved_ );
        Bind( statement, AECBPRM_SPEEDOVERGROUND_FIELD_ID, aecbprmSpeedOverGround_ );
        Bind( statement, AECBPRM_POSITIONACCURACY_FIELD_ID, aecbprmPositionAccuracy_ );
        Bind( statement, AECBPRM_LONGITUDE_FIELD_ID, aecbprmLongitude_ );
        Bind( statement, AECBPRM_LATITUDE_FIELD_ID, aecbprmLatitude_ );
        Bind( statement, AECBPRM_COURSEOVERGROUND_FIELD_ID, aecbprmCourseOverGround_ );
        Bind( statement, AECBPRM_TRUEHEADING_FIELD_ID, aecbprmTrueHeading_ );
        Bind( statement, AECBPRM_TIMESTAMP_FIELD_ID, aecbprmTimestamp_ );
        Bind( statement, AECBPRM_REGIONALRESERVED_FIELD_ID, aecbprmRegionalReserved_ );
        Bind( statement, AECBPRM_NAME_FIELD_ID, aecbprmName_ );
        Bind( statement, AECBPRM_SHIPTYPE_FIELD_ID, aecbprmShipType_ );
        Bind( statement, AECBPRM_DIMENSIONTOBOW_FIELD_ID, aecbprmDimensionToBow_ );
        Bind( statement, AECBPRM_DIMENSIONTOSTERN_FIELD_ID, aecbprmDimensionToStern_ );
        Bind( statement, AECBPRM_DIMENSIONTOPORT_FIELD_ID, aecbprmDimensionToPort_ );
        Bind( statement, AECBPRM_DIMENSIONTOSTARBOARD_FIELD_ID, aecbprmDimensionToStarboard_ );
        Bind( statement, AECBPRM_POSITIONFIXTYPE_FIELD_ID, aecbprmPositionFixType_ );
        Bind( statement, AECBPRM_RAIM_FIELD_ID, aecbprmRaim_ );
        Bind( statement, AECBPRM_DATATERMINALREADY_FIELD_ID, aecbprmDataTerminalReady_ );
        Bind( statement, AECBPRM_ASSIGNED_FIELD_ID, aecbprmAssigned_ );
        Bind( statement, AECBPRM_SPARE_FIELD_ID, aecbprmSpare_ );
        Bind( statement, AIM_INTERROGATEDMMSI_FIELD_ID, aimInterrogatedMmsi_ );
        Bind( statement, AIM_FIRSTMESSAGETYPE_FIELD_ID, aimFirstMessageType_ );
        Bind( statement, AIM_FIRSTSLOTOFFSET_FIELD_ID, aimFirstSlotOffset_ );
        Bind( statement, AIM_SECONDMESSAGETYPE_FIELD_ID, aimSecondMessageType_ );
        Bind( statement, AIM_SECONDSLOTOFFSET_FIELD_ID, aimSecondSlotOffset_ );
        Bind( statement, AIM_SECONDSTATIONINTERROGATIONMMSI_FIELD_ID, aimSecondStationInterrogationMmsi_ );
        Bind( statement, AIM_SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID, aimSecondStationFirstMessageType_ );
        Bind( statement, AIM_SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID, aimSecondStationFirstSlotOffset_ );
        Bind( statement, APRCAB_NAVIGATIONSTATUS_FIELD_ID, aprcabNavigationStatus_ );
        Bind( statement, APRCAB_RATEOFTURN_FIELD_ID, aprcabRateOfTurn_ );
        Bind( statement, APRCAB_SPEEDOVERGROUND_FIELD_ID, aprcabSpeedOverGround_ );
        Bind( statement, APRCAB_POSITIONACCURACY_FIELD_ID, aprcabPositionAccuracy_ );
        Bind( statement, APRCAB_LONGITUDE_FIELD_ID, aprcabLongitude_ );
        Bind( statement, APRCAB_LATITUDE_FIELD_ID, aprcabLatitude_ );
        Bind( statement, APRCAB_COURSEOVERGROUND_FIELD_ID, aprcabCourseOverGround_ );
        Bind( statement, APRCAB_TRUEHEADING_FIELD_ID, aprcabTrueHeading_ );
        Bind( statement, APRCAB_TIMESTAMP_FIELD_ID, aprcabTimestamp_ );
        Bind( statement, APRCAB_MANEUVERINDICATOR_FIELD_ID, aprcabManeuverIndicator_ );
        Bind( statement, APRCAB_SPARE_FIELD_ID, aprcabSpare_ );
        Bind( statement, APRCAB_RAIM_FIELD_ID, aprcabRaim_ );
        Bind( statement, APRCAB_RADIOSTATUS_FIELD_ID, aprcabRadioStatus_ );
        Bind( statement, APRFLRAM_POSITIONACCURACY_FIELD_ID, aprflramPositionAccuracy_ );
        Bind( statement, APRFLRAM_RAIM_FIELD_ID, aprflramRaim_ );
        Bind( statement, APRFLRAM_NAVIGATIONSTATUS_FIELD_ID, aprflramNavigationStatus_ );
        Bind( statement, APRFLRAM_LONGITUDE_FIELD_ID, aprflramLongitude_ );
        Bind( statement, APRFLRAM_LATITUDE_FIELD_ID, aprflramLatitude_ );
        Bind( statement, APRFLRAM_SPEEDOVERGROUND_FIELD_ID, aprflramSpeedOverGround_ );
        Bind( statement, APRFLRAM_COURSEOVERGROUND_FIELD_ID, aprflramCourseOverGround_ );
        Bind( statement, APRFLRAM_GNSSPOSITIONSTATUS_FIELD_ID, aprflramGnssPositionStatus_ );
        Bind( statement, APRFLRAM_SPARE_FIELD_ID, aprflramSpare_ );
        Bind( statement, ASRAM_SPARE_FIELD_ID, asramSpare_ );
        Bind( statement, ASRAM_SEQUENCENUMBER1_FIELD_ID, asramSequenceNumber1_ );
        Bind( statement, ASRAM_MMSI1_FIELD_ID, asramMmsi1_ );
        Bind( statement, ASRAM_SEQUENCENUMBER2_FIELD_ID, asramSequenceNumber2_ );
        Bind( statement, ASRAM_MMSI2_FIELD_ID, asramMmsi2_ );
        Bind( statement, ASRAM_SEQUENCENUMBER3_FIELD_ID, asramSequenceNumber3_ );
        Bind( statement, ASRAM_MMSI3_FIELD_ID, asramMmsi3_ );
        Bind( statement, ASRAM_SEQUENCENUMBER4_FIELD_ID, asramSequenceNumber4_ );
        Bind( statement, ASRAM_MMSI4_FIELD_ID, asramMmsi4_ );
        Bind( statement, ASCBPRM_RESERVED_FIELD_ID, ascbprmReserved_ );
        Bind( statement, ASCBPRM_SPEEDOVERGROUND_FIELD_ID, ascbprmSpeedOverGround_ );
        Bind( statement, ASCBPRM_POSITIONACCURACY_FIELD_ID, ascbprmPositionAccuracy_ );
        Bind( statement, ASCBPRM_LONGITUDE_FIELD_ID, ascbprmLongitude_ );
        Bind( statement, ASCBPRM_LATITUDE_FIELD_ID, ascbprmLatitude_ );
        Bind( statement, ASCBPRM_COURSEOVERGROUND_FIELD_ID, ascbprmCourseOverGround_ );
        Bind( statement, ASCBPRM_TRUEHEADING_FIELD_ID, ascbprmTrueHeading_ );
        Bind( statement, ASCBPRM_TIMESTAMP_FIELD_ID, ascbprmTimestamp_ );
        Bind( statement, ASCBPRM_REGIONALRESERVED_FIELD_ID, ascbprmRegionalReserved_ );
        Bind( statement, ASCBPRM_ISCSUNIT_FIELD_ID, ascbprmIsCsUnit_ );
        Bind( statement, ASCBPRM_HASDISPLAY_FIELD_ID, ascbprmHasDisplay_ );
        Bind( statement, ASCBPRM_HASDSCCAPABILITY_FIELD_ID, ascbprmHasDscCapability_ );
        Bind( statement, ASCBPRM_BAND_FIELD_ID, ascbprmBand_ );
        Bind( statement, ASCBPRM_CANACCEPTMESSAGE22_FIELD_ID, ascbprmCanAcceptMessage22_ );
        Bind( statement, ASCBPRM_ASSIGNED_FIELD_ID, ascbprmAssigned_ );
        Bind( statement, ASCBPRM_RAIM_FIELD_ID, ascbprmRaim_ );
        Bind( statement, ASCBPRM_RADIOSTATUS_FIELD_ID, ascbprmRadioStatus_ );
        Bind( statement, ASSAPRM_ALTITUDE_FIELD_ID, assaprmAltitude_ );
        Bind( statement, ASSAPRM_SPEEDOVERGROUND_FIELD_ID, assaprmSpeedOverGround_ );
        Bind( statement, ASSAPRM_POSITIONACCURACY_FIELD_ID, assaprmPositionAccuracy_ );
        Bind( statement, ASSAPRM_LONGITUDE_FIELD_ID, assaprmLongitude_ );
        Bind( statement, ASSAPRM_LATITUDE_FIELD_ID, assaprmLatitude_ );
        Bind( statement, ASSAPRM_COURSEOVERGROUND_FIELD_ID, assaprmCourseOverGround_ );
        Bind( statement, ASSAPRM_TIMESTAMP_FIELD_ID, assaprmTimestamp_ );
        Bind( statement, ASSAPRM_RESERVED_FIELD_ID, assaprmReserved_ );
        Bind( statement, ASSAPRM_DATATERMINALREADY_FIELD_ID, assaprmDataTerminalReady_ );
        Bind( statement, ASSAPRM_SPARE_FIELD_ID, assaprmSpare_ );
        Bind( statement, ASSAPRM_ASSIGNED_FIELD_ID, assaprmAssigned_ );
        Bind( statement, ASSAPRM_RAIM_FIELD_ID, assaprmRaim_ );
        Bind( statement, ASSAPRM_RADIOSTATUS_FIELD_ID, assaprmRadioStatus_ );
        Bind( statement, ASAVRDM_AISVERSION_FIELD_ID, asavrdmAisVersion_ );
        Bind( statement, ASAVRDM_IMONUMBER_FIELD_ID, asavrdmImoNumber_ );
        Bind( statement, ASAVRDM_CALLSIGN_FIELD_ID, asavrdmCallsign_ );
        Bind( statement, ASAVRDM_SHIPNAME_FIELD_ID, asavrdmShipName_ );
        Bind( statement, ASAVRDM_SHIPTYPE_FIELD_ID, asavrdmShipType_ );
        Bind( statement, ASAVRDM_DIMENSIONTOBOW_FIELD_ID, asavrdmDimensionToBow_ );
        Bind( statement, ASAVRDM_DIMENSIONTOSTERN_FIELD_ID, asavrdmDimensionToStern_ );
        Bind( statement, ASAVRDM_DIMENSIONTOPORT_FIELD_ID, asavrdmDimensionToPort_ );
        Bind( statement, ASAVRDM_DIMENSIONTOSTARBOARD_FIELD_ID, asavrdmDimensionToStarboard_ );
        Bind( statement, ASAVRDM_POSITIONFIXTYPE_FIELD_ID, asavrdmPositionFixType_ );
        Bind( statement, ASAVRDM_ESTIMATEDTIMEOFARRIVAL_FIELD_ID, asavrdmEstimatedTimeOfArrival_ );
        Bind( statement, ASAVRDM_DRAUGHT_FIELD_ID, asavrdmDraught_ );
        Bind( statement, ASAVRDM_DESTINATION_FIELD_ID, asavrdmDestination_ );
        Bind( statement, ASAVRDM_DATATERMINALREADY_FIELD_ID, asavrdmDataTerminalReady_ );
        Bind( statement, ASAVRDM_SPARE_FIELD_ID, asavrdmSpare_ );
        Bind( statement, ASDRM_PARTNUMBER_FIELD_ID, asdrmPartNumber_ );
        Bind( statement, ASDRPA_SHIPNAME_FIELD_ID, asdrpaShipName_ );
        Bind( statement, ASDRPA_SPARE_FIELD_ID, asdrpaSpare_ );
        Bind( statement, ASDRPB_SHIPTYPE_FIELD_ID, asdrpbShipType_ );
        Bind( statement, ASDRPB_VENDORID_FIELD_ID, asdrpbVendorId_ );
        Bind( statement, ASDRPB_UNITMODELCODE_FIELD_ID, asdrpbUnitModelCode_ );
        Bind( statement, ASDRPB_SERIALNUMBER_FIELD_ID, asdrpbSerialNumber_ );
        Bind( statement, ASDRPB_CALLSIGN_FIELD_ID, asdrpbCallsign_ );
        Bind( statement, ASDRPB_DIMENSIONTOBOW_FIELD_ID, asdrpbDimensionToBow_ );
        Bind( statement, ASDRPB_DIMENSIONTOSTERN_FIELD_ID, asdrpbDimensionToStern_ );
        Bind( statement, ASDRPB_DIMENSIONTOPORT_FIELD_ID, asdrpbDimensionToPort_ );
        Bind( statement, ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID, asdrpbDimensionToStarboard_ );
        Bind( statement, ASDRPB_MOTHERSHIPMMSI_FIELD_ID, asdrpbMothershipMmsi_ );
        Bind( statement, ASDRPB_POSITIONFIXTYPE_FIELD_ID, asdrpbPositionFixType_ );
        Bind( statement, ASDRPB_SPARE_FIELD_ID, asdrpbSpare_ );
        Bind( statement, AUADIM_SPARE1_FIELD_ID, auadimSpare1_ );
        Bind( statement, AUADIM_DESTINATIONMMSI_FIELD_ID, auadimDestinationMmsi_ );
        Bind( statement, AUADIM_SPARE2_FIELD_ID, auadimSpare2_ );
        Bind( statement, AUADRM_DATETIME_FIELD_ID, auadrmDatetime_ );
        Bind( statement, AUADRM_POSITIONACCURACY_FIELD_ID, auadrmPositionAccuracy_ );
        Bind( statement, AUADRM_LONGITUDE_FIELD_ID, auadrmLongitude_ );
        Bind( statement, AUADRM_LATITUDE_FIELD_ID, auadrmLatitude_ );
        Bind( statement, AUADRM_POSITIONFIXTYPE_FIELD_ID, auadrmPositionFixType_ );
        Bind( statement, AUADRM_SPARE_FIELD_ID, auadrmSpare_ );
        Bind( statement, AUADRM_RAIM_FIELD_ID, auadrmRaim_ );
        Bind( statement, AUADRM_RADIOSTATUS_FIELD_ID, auadrmRadioStatus_ );
    }

    void ComplexAisMessageColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            abamData_ = statement.GetDBWideString(ABAM_DATA_FIELD_ID);
            abbmData_ = statement.GetDBWideString(ABBM_DATA_FIELD_ID);
    }

    WideString ComplexAisPositionReportClassAMessageBaseColumnData::BaseQuery = L"SELECT \r\n"
        L"  aprcab.[Id], \r\n"
        L"  aprcab.[EntityType], \r\n"
        L"  aprcab.[RowVersion], \r\n"
        L"  aprcab.[AisDevice], \r\n"
        L"  aprcab.[ReceivedTimestamp], \r\n"
        L"  aprcab.[MessageSequenceNumber], \r\n"
        L"  aprcab.[Repeat], \r\n"
        L"  aprcab.[Mmsi], \r\n"
        L"  aprcab.[NavigationStatus], \r\n"
        L"  aprcab.[RateOfTurn], \r\n"
        L"  aprcab.[SpeedOverGround], \r\n"
        L"  aprcab.[PositionAccuracy], \r\n"
        L"  aprcab.[Longitude], \r\n"
        L"  aprcab.[Latitude], \r\n"
        L"  aprcab.[CourseOverGround], \r\n"
        L"  aprcab.[TrueHeading], \r\n"
        L"  aprcab.[Timestamp], \r\n"
        L"  aprcab.[ManeuverIndicator], \r\n"
        L"  aprcab.[Spare], \r\n"
        L"  aprcab.[Raim], \r\n"
        L"  aprcab.[RadioStatus] \r\n"
        L"FROM [AisPositionReportClassAMessageBaseView] aprcab \r\n"
        L"  LEFT JOIN [AisPositionReportClassAAssignedScheduleMessage] aprcasm ON(aprcab.[Id] = aprcasm.[Id] ) \r\n"
        L"  LEFT JOIN [AisPositionReportClassAMessage] aprca ON(aprcab.[Id] = aprca.[Id] ) \r\n"
        L"  LEFT JOIN [AisPositionReportClassAResponseToInterrogationMessage] aprcatim ON(aprcab.[Id] = aprcatim.[Id] )";
    WideString ComplexAisPositionReportClassAMessageBaseColumnData::BaseViewName = L"AisPositionReportClassAMessageBaseView";
    WideString ComplexAisPositionReportClassAMessageBaseColumnData::ViewAliasName = L"aprcab";

    void ComplexAisPositionReportClassAMessageBaseColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, APRCAB_ID_FIELD_ID, id_ );
        Bind( statement, APRCAB_KIND_FIELD_ID, kind_ );
        Bind( statement, APRCAB_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, APRCAB_AISDEVICE_FIELD_ID, aisDevice_ );
        Bind( statement, APRCAB_RECEIVEDTIMESTAMP_FIELD_ID, receivedTimestamp_ );
        Bind( statement, APRCAB_MESSAGESEQUENCENUMBER_FIELD_ID, messageSequenceNumber_ );
        Bind( statement, APRCAB_REPEAT_FIELD_ID, repeat_ );
        Bind( statement, APRCAB_MMSI_FIELD_ID, mmsi_ );
        Bind( statement, APRCAB_NAVIGATIONSTATUS_FIELD_ID, navigationStatus_ );
        Bind( statement, APRCAB_RATEOFTURN_FIELD_ID, rateOfTurn_ );
        Bind( statement, APRCAB_SPEEDOVERGROUND_FIELD_ID, speedOverGround_ );
        Bind( statement, APRCAB_POSITIONACCURACY_FIELD_ID, positionAccuracy_ );
        Bind( statement, APRCAB_LONGITUDE_FIELD_ID, longitude_ );
        Bind( statement, APRCAB_LATITUDE_FIELD_ID, latitude_ );
        Bind( statement, APRCAB_COURSEOVERGROUND_FIELD_ID, courseOverGround_ );
        Bind( statement, APRCAB_TRUEHEADING_FIELD_ID, trueHeading_ );
        Bind( statement, APRCAB_TIMESTAMP_FIELD_ID, timestamp_ );
        Bind( statement, APRCAB_MANEUVERINDICATOR_FIELD_ID, maneuverIndicator_ );
        Bind( statement, APRCAB_SPARE_FIELD_ID, spare_ );
        Bind( statement, APRCAB_RAIM_FIELD_ID, raim_ );
        Bind( statement, APRCAB_RADIOSTATUS_FIELD_ID, radioStatus_ );
    }


    WideString ComplexAisStaticDataReportMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  asdrm.[Id], \r\n"
        L"  asdrm.[EntityType], \r\n"
        L"  asdrm.[RowVersion], \r\n"
        L"  asdrm.[AisDevice], \r\n"
        L"  asdrm.[ReceivedTimestamp], \r\n"
        L"  asdrm.[MessageSequenceNumber], \r\n"
        L"  asdrm.[Repeat], \r\n"
        L"  asdrm.[Mmsi], \r\n"
        L"  asdrm.[PartNumber], \r\n"
        L"  asdrpa.[ShipName], \r\n"
        L"  asdrpa.[Spare], \r\n"
        L"  asdrpb.[ShipType], \r\n"
        L"  asdrpb.[VendorId], \r\n"
        L"  asdrpb.[UnitModelCode], \r\n"
        L"  asdrpb.[SerialNumber], \r\n"
        L"  asdrpb.[Callsign], \r\n"
        L"  asdrpb.[DimensionToBow], \r\n"
        L"  asdrpb.[DimensionToStern], \r\n"
        L"  asdrpb.[DimensionToPort], \r\n"
        L"  asdrpb.[DimensionToStarboard], \r\n"
        L"  asdrpb.[MothershipMmsi], \r\n"
        L"  asdrpb.[PositionFixType], \r\n"
        L"  asdrpb.[Spare] \r\n"
        L"FROM [AisStaticDataReportMessageView] asdrm \r\n"
        L"  LEFT JOIN [AisStaticDataReportPartAMessage] asdrpa ON(asdrm.[Id] = asdrpa.[Id] ) \r\n"
        L"  LEFT JOIN [AisStaticDataReportPartBMessage] asdrpb ON(asdrm.[Id] = asdrpb.[Id] )";
    WideString ComplexAisStaticDataReportMessageColumnData::BaseViewName = L"AisStaticDataReportMessageView";
    WideString ComplexAisStaticDataReportMessageColumnData::ViewAliasName = L"asdrm";

    void ComplexAisStaticDataReportMessageColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, ASDRM_ID_FIELD_ID, id_ );
        Bind( statement, ASDRM_KIND_FIELD_ID, kind_ );
        Bind( statement, ASDRM_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, ASDRM_AISDEVICE_FIELD_ID, aisDevice_ );
        Bind( statement, ASDRM_RECEIVEDTIMESTAMP_FIELD_ID, receivedTimestamp_ );
        Bind( statement, ASDRM_MESSAGESEQUENCENUMBER_FIELD_ID, messageSequenceNumber_ );
        Bind( statement, ASDRM_REPEAT_FIELD_ID, repeat_ );
        Bind( statement, ASDRM_MMSI_FIELD_ID, mmsi_ );
        Bind( statement, ASDRM_PARTNUMBER_FIELD_ID, partNumber_ );
        Bind( statement, ASDRPA_SHIPNAME_FIELD_ID, asdrpaShipName_ );
        Bind( statement, ASDRPA_SPARE_FIELD_ID, asdrpaSpare_ );
        Bind( statement, ASDRPB_SHIPTYPE_FIELD_ID, asdrpbShipType_ );
        Bind( statement, ASDRPB_VENDORID_FIELD_ID, asdrpbVendorId_ );
        Bind( statement, ASDRPB_UNITMODELCODE_FIELD_ID, asdrpbUnitModelCode_ );
        Bind( statement, ASDRPB_SERIALNUMBER_FIELD_ID, asdrpbSerialNumber_ );
        Bind( statement, ASDRPB_CALLSIGN_FIELD_ID, asdrpbCallsign_ );
        Bind( statement, ASDRPB_DIMENSIONTOBOW_FIELD_ID, asdrpbDimensionToBow_ );
        Bind( statement, ASDRPB_DIMENSIONTOSTERN_FIELD_ID, asdrpbDimensionToStern_ );
        Bind( statement, ASDRPB_DIMENSIONTOPORT_FIELD_ID, asdrpbDimensionToPort_ );
        Bind( statement, ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID, asdrpbDimensionToStarboard_ );
        Bind( statement, ASDRPB_MOTHERSHIPMMSI_FIELD_ID, asdrpbMothershipMmsi_ );
        Bind( statement, ASDRPB_POSITIONFIXTYPE_FIELD_ID, asdrpbPositionFixType_ );
        Bind( statement, ASDRPB_SPARE_FIELD_ID, asdrpbSpare_ );
    }


    WideString ComplexCameraCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  cc.[Id], \r\n"
        L"  cc.[EntityType], \r\n"
        L"  cc.[RowVersion], \r\n"
        L"  cc.[Camera], \r\n"
        L"  cc.[Timestamp], \r\n"
        L"  cc.[DeviceCommandSourceType], \r\n"
        L"  cc.[DeviceCommandSourceId], \r\n"
        L"  cc.[Reply], \r\n"
        L"  ccam.[PositionPanTiltMode], \r\n"
        L"  ccam.[PanAngle], \r\n"
        L"  ccam.[TiltAngle], \r\n"
        L"  ccam.[PositionFocalLengthMode], \r\n"
        L"  ccam.[FocalLength], \r\n"
        L"  ccam.[SpeedPanTiltMode], \r\n"
        L"  ccam.[PanSpeed], \r\n"
        L"  ccam.[TiltSpeed], \r\n"
        L"  ccam.[SpeedFocalLengthMode], \r\n"
        L"  ccam.[ZoomSpeed], \r\n"
        L"  ccaptz.[X], \r\n"
        L"  ccaptz.[Y], \r\n"
        L"  ccaptz.[Z], \r\n"
        L"  cccm.[Normalized], \r\n"
        L"  cccm.[PanVelocity], \r\n"
        L"  cccm.[TiltVelocity], \r\n"
        L"  cccm.[ZoomVelocity], \r\n"
        L"  cccm.[Duration], \r\n"
        L"  ccgm.[Latitude], \r\n"
        L"  ccgm.[Longitude], \r\n"
        L"  ccgm.[Altitude], \r\n"
        L"  ccgm.[ViewportWidth], \r\n"
        L"  ccgm.[ViewportHeight], \r\n"
        L"  ccrm.[Normalized], \r\n"
        L"  ccrm.[PanAngle], \r\n"
        L"  ccrm.[TiltAngle], \r\n"
        L"  ccrm.[FocalLength], \r\n"
        L"  ccrm.[PanSpeed], \r\n"
        L"  ccrm.[TiltSpeed], \r\n"
        L"  ccrm.[ZoomSpeed], \r\n"
        L"  ccsaf.[Enabled], \r\n"
        L"  ccsbaw.[Enabled], \r\n"
        L"  ccsf.[TrackId], \r\n"
        L"  ccsf.[Reason], \r\n"
        L"  ccsirl.[Enabled], \r\n"
        L"  cwa.[Enabled], \r\n"
        L"  cwi.[Enabled], \r\n"
        L"  ccs.[PanTilt], \r\n"
        L"  ccs.[Zoom] \r\n"
        L"FROM [CameraCommandView] cc \r\n"
        L"  LEFT JOIN [CameraCommandAbsoluteMove] ccam ON(cc.[Id] = ccam.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandAdjustPanTiltZoom] ccaptz ON(cc.[Id] = ccaptz.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandContinuousMove] cccm ON(cc.[Id] = cccm.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandGeoMove] ccgm ON(cc.[Id] = ccgm.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandRelativeMove] ccrm ON(cc.[Id] = ccrm.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandReleasePTZOwnership] crlp ON(cc.[Id] = crlp.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandRequestPTZOwnership] crqp ON(cc.[Id] = crqp.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandSetAutoFocus] ccsaf ON(cc.[Id] = ccsaf.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandSetBlackAndWhite] ccsbaw ON(cc.[Id] = ccsbaw.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandSetFollowed] ccsf ON(cc.[Id] = ccsf.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandSetInfraRedLamp] ccsirl ON(cc.[Id] = ccsirl.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandSetWasher] cwa ON(cc.[Id] = cwa.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandSetWiper] cwi ON(cc.[Id] = cwi.[Id] ) \r\n"
        L"  LEFT JOIN [CameraCommandStop] ccs ON(cc.[Id] = ccs.[Id] )";
    WideString ComplexCameraCommandColumnData::BaseViewName = L"CameraCommandView";
    WideString ComplexCameraCommandColumnData::ViewAliasName = L"cc";

    void ComplexCameraCommandColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, CC_ID_FIELD_ID, id_ );
        Bind( statement, CC_KIND_FIELD_ID, kind_ );
        Bind( statement, CC_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, CC_CAMERA_FIELD_ID, camera_ );
        Bind( statement, CC_TIMESTAMP_FIELD_ID, timestamp_ );
        Bind( statement, CC_DEVICECOMMANDSOURCETYPE_FIELD_ID, deviceCommandSourceType_ );
        Bind( statement, CC_DEVICECOMMANDSOURCEID_FIELD_ID, deviceCommandSourceId_ );
        Bind( statement, CC_REPLY_FIELD_ID, reply_ );
        Bind( statement, CCAM_POSITIONPANTILTMODE_FIELD_ID, ccamPositionPanTiltMode_ );
        Bind( statement, CCAM_PANANGLE_FIELD_ID, ccamPanAngle_ );
        Bind( statement, CCAM_TILTANGLE_FIELD_ID, ccamTiltAngle_ );
        Bind( statement, CCAM_POSITIONFOCALLENGTHMODE_FIELD_ID, ccamPositionFocalLengthMode_ );
        Bind( statement, CCAM_FOCALLENGTH_FIELD_ID, ccamFocalLength_ );
        Bind( statement, CCAM_SPEEDPANTILTMODE_FIELD_ID, ccamSpeedPanTiltMode_ );
        Bind( statement, CCAM_PANSPEED_FIELD_ID, ccamPanSpeed_ );
        Bind( statement, CCAM_TILTSPEED_FIELD_ID, ccamTiltSpeed_ );
        Bind( statement, CCAM_SPEEDFOCALLENGTHMODE_FIELD_ID, ccamSpeedFocalLengthMode_ );
        Bind( statement, CCAM_ZOOMSPEED_FIELD_ID, ccamZoomSpeed_ );
        Bind( statement, CCAPTZ_X_FIELD_ID, ccaptzX_ );
        Bind( statement, CCAPTZ_Y_FIELD_ID, ccaptzY_ );
        Bind( statement, CCAPTZ_Z_FIELD_ID, ccaptzZ_ );
        Bind( statement, CCCM_NORMALIZED_FIELD_ID, cccmNormalized_ );
        Bind( statement, CCCM_PANVELOCITY_FIELD_ID, cccmPanVelocity_ );
        Bind( statement, CCCM_TILTVELOCITY_FIELD_ID, cccmTiltVelocity_ );
        Bind( statement, CCCM_ZOOMVELOCITY_FIELD_ID, cccmZoomVelocity_ );
        Bind( statement, CCCM_DURATION_FIELD_ID, cccmDuration_ );
        Bind( statement, CCGM_LATITUDE_FIELD_ID, ccgmLatitude_ );
        Bind( statement, CCGM_LONGITUDE_FIELD_ID, ccgmLongitude_ );
        Bind( statement, CCGM_ALTITUDE_FIELD_ID, ccgmAltitude_ );
        Bind( statement, CCGM_VIEWPORTWIDTH_FIELD_ID, ccgmViewportWidth_ );
        Bind( statement, CCGM_VIEWPORTHEIGHT_FIELD_ID, ccgmViewportHeight_ );
        Bind( statement, CCRM_NORMALIZED_FIELD_ID, ccrmNormalized_ );
        Bind( statement, CCRM_PANANGLE_FIELD_ID, ccrmPanAngle_ );
        Bind( statement, CCRM_TILTANGLE_FIELD_ID, ccrmTiltAngle_ );
        Bind( statement, CCRM_FOCALLENGTH_FIELD_ID, ccrmFocalLength_ );
        Bind( statement, CCRM_PANSPEED_FIELD_ID, ccrmPanSpeed_ );
        Bind( statement, CCRM_TILTSPEED_FIELD_ID, ccrmTiltSpeed_ );
        Bind( statement, CCRM_ZOOMSPEED_FIELD_ID, ccrmZoomSpeed_ );
        Bind( statement, CCSAF_ENABLED_FIELD_ID, ccsafEnabled_ );
        Bind( statement, CCSBAW_ENABLED_FIELD_ID, ccsbawEnabled_ );
        Bind( statement, CCSF_TRACKID_FIELD_ID, ccsfTrackId_ );
        Bind( statement, CCSF_REASON_FIELD_ID, ccsfReason_ );
        Bind( statement, CCSIRL_ENABLED_FIELD_ID, ccsirlEnabled_ );
        Bind( statement, CWA_ENABLED_FIELD_ID, cwaEnabled_ );
        Bind( statement, CWI_ENABLED_FIELD_ID, cwiEnabled_ );
        Bind( statement, CCS_PANTILT_FIELD_ID, ccsPanTilt_ );
        Bind( statement, CCS_ZOOM_FIELD_ID, ccsZoom_ );
    }


    WideString ComplexCatalogElementColumnData::BaseQuery = L"SELECT \r\n"
        L"  ce.[Id], \r\n"
        L"  ce.[EntityType], \r\n"
        L"  ce.[RowVersion], \r\n"
        L"  ce.[Catalog], \r\n"
        L"  ce.[Name], \r\n"
        L"  e.[ElementType] \r\n"
        L"FROM [CatalogElementView] ce \r\n"
        L"  LEFT JOIN [Catalog] c ON(ce.[Id] = c.[Id] ) \r\n"
        L"  LEFT JOIN [Element] e ON(ce.[Id] = e.[Id] )";
    WideString ComplexCatalogElementColumnData::BaseViewName = L"CatalogElementView";
    WideString ComplexCatalogElementColumnData::ViewAliasName = L"ce";

    void ComplexCatalogElementColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, CE_ID_FIELD_ID, id_ );
        Bind( statement, CE_KIND_FIELD_ID, kind_ );
        Bind( statement, CE_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, CE_CATALOG_FIELD_ID, catalog_ );
        Bind( statement, CE_NAME_FIELD_ID, name_ );
        Bind( statement, E_ELEMENTTYPE_FIELD_ID, eElementType_ );
    }


    WideString ComplexIdentityColumnData::BaseQuery = L"SELECT \r\n"
        L"  i.[Id], \r\n"
        L"  i.[EntityType], \r\n"
        L"  i.[RowVersion], \r\n"
        L"  c.[Identifier], \r\n"
        L"  imon.[Identifier], \r\n"
        L"  mmsi.[Identifier], \r\n"
        L"  n.[Text] \r\n"
        L"FROM [IdentityView] i \r\n"
        L"  LEFT JOIN [Callsign] c ON(i.[Id] = c.[Id] ) \r\n"
        L"  LEFT JOIN [InternationalMaritimeOrganizationNumber] imon ON(i.[Id] = imon.[Id] ) \r\n"
        L"  LEFT JOIN [MaritimeMobileServiceIdentity] mmsi ON(i.[Id] = mmsi.[Id] ) \r\n"
        L"  LEFT JOIN [Name] n ON(i.[Id] = n.[Id] )";
    WideString ComplexIdentityColumnData::BaseViewName = L"IdentityView";
    WideString ComplexIdentityColumnData::ViewAliasName = L"i";

    void ComplexIdentityColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, I_ID_FIELD_ID, id_ );
        Bind( statement, I_KIND_FIELD_ID, kind_ );
        Bind( statement, I_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, C_IDENTIFIER_FIELD_ID, cIdentifier_ );
        Bind( statement, IMON_IDENTIFIER_FIELD_ID, imonIdentifier_ );
        Bind( statement, MMSI_IDENTIFIER_FIELD_ID, mmsiIdentifier_ );
        Bind( statement, N_TEXT_FIELD_ID, nText_ );
    }


    WideString ComplexItemColumnData::BaseQuery = L"SELECT \r\n"
        L"  i.[Id], \r\n"
        L"  i.[EntityType], \r\n"
        L"  i.[RowVersion], \r\n"
        L"  bs.[Name], \r\n"
        L"  bs.[Type], \r\n"
        L"  d.[Host], \r\n"
        L"  d.[Name], \r\n"
        L"  d.[EnabledTimeseries], \r\n"
        L"  g.[LatitudeTimeseries], \r\n"
        L"  g.[LongitudeTimeseries], \r\n"
        L"  g.[AltitudeTimeseries], \r\n"
        L"  gd.[HeadingTrueNorthTimeseries], \r\n"
        L"  gd.[HeadingMagneticNorthTimeseries], \r\n"
        L"  gd.[PitchTimeseries], \r\n"
        L"  gd.[RateOfTurnTimeseries], \r\n"
        L"  gd.[RollTimeseries], \r\n"
        L"  gd.[CourseTimeseries], \r\n"
        L"  gd.[SpeedTimeseries], \r\n"
        L"  gd.[GNSSDevice], \r\n"
        L"  rdo.[Radar], \r\n"
        L"  rdo.[PressureTimeseries], \r\n"
        L"  rdo.[TemperatureTimeseries], \r\n"
        L"  rdo.[DewPointTimeseries], \r\n"
        L"  rdo.[StatusTimeseries], \r\n"
        L"  rd.[SaveSettingsTimeseries], \r\n"
        L"  rd.[PowerOnTimeseries], \r\n"
        L"  rd.[TrackingOnTimeseries], \r\n"
        L"  rd.[RadarPulseTimeseries], \r\n"
        L"  rd.[TuningTimeseries], \r\n"
        L"  rd.[BlankSector1Timeseries], \r\n"
        L"  rd.[Sector1StartTimeseries], \r\n"
        L"  rd.[Sector1EndTimeseries], \r\n"
        L"  rd.[BlankSector2Timeseries], \r\n"
        L"  rd.[Sector2StartTimeseries], \r\n"
        L"  rd.[Sector2EndTimeseries], \r\n"
        L"  rd.[EnableAutomaticFrequencyControlTimeseries], \r\n"
        L"  rd.[AzimuthOffsetTimeseries], \r\n"
        L"  rd.[EnableSensitivityTimeControlTimeseries], \r\n"
        L"  rd.[AutomaticSensitivityTimeControlTimeseries], \r\n"
        L"  rd.[SensitivityTimeControlLevelTimeseries], \r\n"
        L"  rd.[EnableFastTimeConstantTimeseries], \r\n"
        L"  rd.[FastTimeConstantLevelTimeseries], \r\n"
        L"  rd.[FastTimeConstantModeTimeseries], \r\n"
        L"  rd.[LatitudeTimeseries], \r\n"
        L"  rd.[LongitudeTimeseries], \r\n"
        L"  rd.[Radome], \r\n"
        L"  rd.[GNSSDevice], \r\n"
        L"  wsd.[BarometricPressureTimeseries], \r\n"
        L"  wsd.[AirTemperatureTimeseries], \r\n"
        L"  wsd.[WaterTemperatureTimeseries], \r\n"
        L"  wsd.[RelativeHumidityTimeseries], \r\n"
        L"  wsd.[AbsoluteHumidityTimeseries], \r\n"
        L"  wsd.[DewPointTimeseries], \r\n"
        L"  wsd.[WindDirectionTimeseries], \r\n"
        L"  wsd.[WindSpeedTimeseries], \r\n"
        L"  wsd.[Gyro], \r\n"
        L"  f.[Name], \r\n"
        L"  f.[Type], \r\n"
        L"  f.[Longitude], \r\n"
        L"  f.[Latitude], \r\n"
        L"  f.[Altitude], \r\n"
        L"  a.[Name], \r\n"
        L"  a.[Type], \r\n"
        L"  aatn.[Name], \r\n"
        L"  aatn.[MMSI], \r\n"
        L"  aatn.[NavigationalAidType], \r\n"
        L"  aatn.[Position], \r\n"
        L"  aatn.[IsVirtual], \r\n"
        L"  aatn.[ToBow], \r\n"
        L"  aatn.[ToStern], \r\n"
        L"  aatn.[ToPort], \r\n"
        L"  aatn.[ToStarboard], \r\n"
        L"  aatn.[OffPositionTimeseries], \r\n"
        L"  v.[Name], \r\n"
        L"  v.[Type], \r\n"
        L"  vsl.[Name], \r\n"
        L"  vsl.[Type], \r\n"
        L"  vsl.[ToBow], \r\n"
        L"  vsl.[ToStern], \r\n"
        L"  vsl.[ToPort], \r\n"
        L"  vsl.[ToStarboard], \r\n"
        L"  vsl.[DraughtTimeseries], \r\n"
        L"  vsl.[PersonsOnBoardTimeseries], \r\n"
        L"  d.[Description] \r\n"
        L"FROM [ItemView] i \r\n"
        L"  LEFT JOIN [BaseStation] bs ON(i.[Id] = bs.[Id] ) \r\n"
        L"  LEFT JOIN [Device] d ON(i.[Id] = d.[Id] ) \r\n"
        L"  LEFT JOIN [CameraDevice] cd ON(i.[Id] = cd.[Id] ) \r\n"
        L"  LEFT JOIN [GNSSDevice] g ON(i.[Id] = g.[Id] ) \r\n"
        L"  LEFT JOIN [GyroDevice] gd ON(i.[Id] = gd.[Id] ) \r\n"
        L"  LEFT JOIN [LineInputDevice] lid ON(i.[Id] = lid.[Id] ) \r\n"
        L"  LEFT JOIN [OilSpillDetectorDevice] osdd ON(i.[Id] = osdd.[Id] ) \r\n"
        L"  LEFT JOIN [RadioDevice] rdi ON(i.[Id] = rdi.[Id] ) \r\n"
        L"  LEFT JOIN [RadomeDevice] rdo ON(i.[Id] = rdo.[Id] ) \r\n"
        L"  LEFT JOIN [TrackerDevice] td ON(i.[Id] = td.[Id] ) \r\n"
        L"  LEFT JOIN [AisDevice] ad ON(i.[Id] = ad.[Id] ) \r\n"
        L"  LEFT JOIN [RadarDevice] rd ON(i.[Id] = rd.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationDevice] wsd ON(i.[Id] = wsd.[Id] ) \r\n"
        L"  LEFT JOIN [Facility] f ON(i.[Id] = f.[Id] ) \r\n"
        L"  LEFT JOIN [TrackableItem] ti ON(i.[Id] = ti.[Id] ) \r\n"
        L"  LEFT JOIN [Aircraft] a ON(i.[Id] = a.[Id] ) \r\n"
        L"  LEFT JOIN [AisAidToNavigation] aatn ON(i.[Id] = aatn.[Id] ) \r\n"
        L"  LEFT JOIN [Vehicle] v ON(i.[Id] = v.[Id] ) \r\n"
        L"  LEFT JOIN [Vessel] vsl ON(i.[Id] = vsl.[Id] )";
    WideString ComplexItemColumnData::BaseViewName = L"ItemView";
    WideString ComplexItemColumnData::ViewAliasName = L"i";

    void ComplexItemColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, I_ID_FIELD_ID, id_ );
        Bind( statement, I_KIND_FIELD_ID, kind_ );
        Bind( statement, I_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, BS_NAME_FIELD_ID, bsName_ );
        Bind( statement, BS_TYPE_FIELD_ID, bsType_ );
        Bind( statement, D_HOST_FIELD_ID, dHost_ );
        Bind( statement, D_NAME_FIELD_ID, dName_ );
        Bind( statement, D_ENABLEDTIMESERIES_FIELD_ID, dEnabledTimeseries_ );
        Bind( statement, G_LATITUDETIMESERIES_FIELD_ID, gLatitudeTimeseries_ );
        Bind( statement, G_LONGITUDETIMESERIES_FIELD_ID, gLongitudeTimeseries_ );
        Bind( statement, G_ALTITUDETIMESERIES_FIELD_ID, gAltitudeTimeseries_ );
        Bind( statement, GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID, gdHeadingTrueNorthTimeseries_ );
        Bind( statement, GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID, gdHeadingMagneticNorthTimeseries_ );
        Bind( statement, GD_PITCHTIMESERIES_FIELD_ID, gdPitchTimeseries_ );
        Bind( statement, GD_RATEOFTURNTIMESERIES_FIELD_ID, gdRateOfTurnTimeseries_ );
        Bind( statement, GD_ROLLTIMESERIES_FIELD_ID, gdRollTimeseries_ );
        Bind( statement, GD_COURSETIMESERIES_FIELD_ID, gdCourseTimeseries_ );
        Bind( statement, GD_SPEEDTIMESERIES_FIELD_ID, gdSpeedTimeseries_ );
        Bind( statement, GD_GNSSDEVICE_FIELD_ID, gdGNSSDevice_ );
        Bind( statement, RDO_RADAR_FIELD_ID, rdoRadar_ );
        Bind( statement, RDO_PRESSURETIMESERIES_FIELD_ID, rdoPressureTimeseries_ );
        Bind( statement, RDO_TEMPERATURETIMESERIES_FIELD_ID, rdoTemperatureTimeseries_ );
        Bind( statement, RDO_DEWPOINTTIMESERIES_FIELD_ID, rdoDewPointTimeseries_ );
        Bind( statement, RDO_STATUSTIMESERIES_FIELD_ID, rdoStatusTimeseries_ );
        Bind( statement, RD_SAVESETTINGSTIMESERIES_FIELD_ID, rdSaveSettingsTimeseries_ );
        Bind( statement, RD_POWERONTIMESERIES_FIELD_ID, rdPowerOnTimeseries_ );
        Bind( statement, RD_TRACKINGONTIMESERIES_FIELD_ID, rdTrackingOnTimeseries_ );
        Bind( statement, RD_RADARPULSETIMESERIES_FIELD_ID, rdRadarPulseTimeseries_ );
        Bind( statement, RD_TUNINGTIMESERIES_FIELD_ID, rdTuningTimeseries_ );
        Bind( statement, RD_BLANKSECTOR1TIMESERIES_FIELD_ID, rdBlankSector1Timeseries_ );
        Bind( statement, RD_SECTOR1STARTTIMESERIES_FIELD_ID, rdSector1StartTimeseries_ );
        Bind( statement, RD_SECTOR1ENDTIMESERIES_FIELD_ID, rdSector1EndTimeseries_ );
        Bind( statement, RD_BLANKSECTOR2TIMESERIES_FIELD_ID, rdBlankSector2Timeseries_ );
        Bind( statement, RD_SECTOR2STARTTIMESERIES_FIELD_ID, rdSector2StartTimeseries_ );
        Bind( statement, RD_SECTOR2ENDTIMESERIES_FIELD_ID, rdSector2EndTimeseries_ );
        Bind( statement, RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID, rdEnableAutomaticFrequencyControlTimeseries_ );
        Bind( statement, RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID, rdAzimuthOffsetTimeseries_ );
        Bind( statement, RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID, rdEnableSensitivityTimeControlTimeseries_ );
        Bind( statement, RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID, rdAutomaticSensitivityTimeControlTimeseries_ );
        Bind( statement, RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID, rdSensitivityTimeControlLevelTimeseries_ );
        Bind( statement, RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID, rdEnableFastTimeConstantTimeseries_ );
        Bind( statement, RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID, rdFastTimeConstantLevelTimeseries_ );
        Bind( statement, RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID, rdFastTimeConstantModeTimeseries_ );
        Bind( statement, RD_LATITUDETIMESERIES_FIELD_ID, rdLatitudeTimeseries_ );
        Bind( statement, RD_LONGITUDETIMESERIES_FIELD_ID, rdLongitudeTimeseries_ );
        Bind( statement, RD_RADOME_FIELD_ID, rdRadome_ );
        Bind( statement, RD_GNSSDEVICE_FIELD_ID, rdGNSSDevice_ );
        Bind( statement, WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID, wsdBarometricPressureTimeseries_ );
        Bind( statement, WSD_AIRTEMPERATURETIMESERIES_FIELD_ID, wsdAirTemperatureTimeseries_ );
        Bind( statement, WSD_WATERTEMPERATURETIMESERIES_FIELD_ID, wsdWaterTemperatureTimeseries_ );
        Bind( statement, WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID, wsdRelativeHumidityTimeseries_ );
        Bind( statement, WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID, wsdAbsoluteHumidityTimeseries_ );
        Bind( statement, WSD_DEWPOINTTIMESERIES_FIELD_ID, wsdDewPointTimeseries_ );
        Bind( statement, WSD_WINDDIRECTIONTIMESERIES_FIELD_ID, wsdWindDirectionTimeseries_ );
        Bind( statement, WSD_WINDSPEEDTIMESERIES_FIELD_ID, wsdWindSpeedTimeseries_ );
        Bind( statement, WSD_GYRO_FIELD_ID, wsdGyro_ );
        Bind( statement, F_NAME_FIELD_ID, fName_ );
        Bind( statement, F_TYPE_FIELD_ID, fType_ );
        Bind( statement, F_LONGITUDE_FIELD_ID, fLongitude_ );
        Bind( statement, F_LATITUDE_FIELD_ID, fLatitude_ );
        Bind( statement, F_ALTITUDE_FIELD_ID, fAltitude_ );
        Bind( statement, A_NAME_FIELD_ID, aName_ );
        Bind( statement, A_TYPE_FIELD_ID, aType_ );
        Bind( statement, AATN_NAME_FIELD_ID, aatnName_ );
        Bind( statement, AATN_MMSI_FIELD_ID, aatnMMSI_ );
        Bind( statement, AATN_NAVIGATIONALAIDTYPE_FIELD_ID, aatnNavigationalAidType_ );
        Bind( statement, AATN_POSITION_FIELD_ID, aatnPosition_ );
        Bind( statement, AATN_ISVIRTUAL_FIELD_ID, aatnIsVirtual_ );
        Bind( statement, AATN_TOBOW_FIELD_ID, aatnToBow_ );
        Bind( statement, AATN_TOSTERN_FIELD_ID, aatnToStern_ );
        Bind( statement, AATN_TOPORT_FIELD_ID, aatnToPort_ );
        Bind( statement, AATN_TOSTARBOARD_FIELD_ID, aatnToStarboard_ );
        Bind( statement, AATN_OFFPOSITIONTIMESERIES_FIELD_ID, aatnOffPositionTimeseries_ );
        Bind( statement, V_NAME_FIELD_ID, vName_ );
        Bind( statement, V_TYPE_FIELD_ID, vType_ );
        Bind( statement, VSL_NAME_FIELD_ID, vslName_ );
        Bind( statement, VSL_TYPE_FIELD_ID, vslType_ );
        Bind( statement, VSL_TOBOW_FIELD_ID, vslToBow_ );
        Bind( statement, VSL_TOSTERN_FIELD_ID, vslToStern_ );
        Bind( statement, VSL_TOPORT_FIELD_ID, vslToPort_ );
        Bind( statement, VSL_TOSTARBOARD_FIELD_ID, vslToStarboard_ );
        Bind( statement, VSL_DRAUGHTTIMESERIES_FIELD_ID, vslDraughtTimeseries_ );
        Bind( statement, VSL_PERSONSONBOARDTIMESERIES_FIELD_ID, vslPersonsOnBoardTimeseries_ );
    }

    void ComplexItemColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            dDescription_ = statement.GetDBWideString(D_DESCRIPTION_FIELD_ID);
    }

    WideString ComplexDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  d.[Id], \r\n"
        L"  d.[EntityType], \r\n"
        L"  d.[RowVersion], \r\n"
        L"  d.[Host], \r\n"
        L"  d.[Name], \r\n"
        L"  d.[EnabledTimeseries], \r\n"
        L"  g.[LatitudeTimeseries], \r\n"
        L"  g.[LongitudeTimeseries], \r\n"
        L"  g.[AltitudeTimeseries], \r\n"
        L"  gd.[HeadingTrueNorthTimeseries], \r\n"
        L"  gd.[HeadingMagneticNorthTimeseries], \r\n"
        L"  gd.[PitchTimeseries], \r\n"
        L"  gd.[RateOfTurnTimeseries], \r\n"
        L"  gd.[RollTimeseries], \r\n"
        L"  gd.[CourseTimeseries], \r\n"
        L"  gd.[SpeedTimeseries], \r\n"
        L"  gd.[GNSSDevice], \r\n"
        L"  rdo.[Radar], \r\n"
        L"  rdo.[PressureTimeseries], \r\n"
        L"  rdo.[TemperatureTimeseries], \r\n"
        L"  rdo.[DewPointTimeseries], \r\n"
        L"  rdo.[StatusTimeseries], \r\n"
        L"  rd.[SaveSettingsTimeseries], \r\n"
        L"  rd.[PowerOnTimeseries], \r\n"
        L"  rd.[TrackingOnTimeseries], \r\n"
        L"  rd.[RadarPulseTimeseries], \r\n"
        L"  rd.[TuningTimeseries], \r\n"
        L"  rd.[BlankSector1Timeseries], \r\n"
        L"  rd.[Sector1StartTimeseries], \r\n"
        L"  rd.[Sector1EndTimeseries], \r\n"
        L"  rd.[BlankSector2Timeseries], \r\n"
        L"  rd.[Sector2StartTimeseries], \r\n"
        L"  rd.[Sector2EndTimeseries], \r\n"
        L"  rd.[EnableAutomaticFrequencyControlTimeseries], \r\n"
        L"  rd.[AzimuthOffsetTimeseries], \r\n"
        L"  rd.[EnableSensitivityTimeControlTimeseries], \r\n"
        L"  rd.[AutomaticSensitivityTimeControlTimeseries], \r\n"
        L"  rd.[SensitivityTimeControlLevelTimeseries], \r\n"
        L"  rd.[EnableFastTimeConstantTimeseries], \r\n"
        L"  rd.[FastTimeConstantLevelTimeseries], \r\n"
        L"  rd.[FastTimeConstantModeTimeseries], \r\n"
        L"  rd.[LatitudeTimeseries], \r\n"
        L"  rd.[LongitudeTimeseries], \r\n"
        L"  rd.[Radome], \r\n"
        L"  rd.[GNSSDevice], \r\n"
        L"  wsd.[BarometricPressureTimeseries], \r\n"
        L"  wsd.[AirTemperatureTimeseries], \r\n"
        L"  wsd.[WaterTemperatureTimeseries], \r\n"
        L"  wsd.[RelativeHumidityTimeseries], \r\n"
        L"  wsd.[AbsoluteHumidityTimeseries], \r\n"
        L"  wsd.[DewPointTimeseries], \r\n"
        L"  wsd.[WindDirectionTimeseries], \r\n"
        L"  wsd.[WindSpeedTimeseries], \r\n"
        L"  wsd.[Gyro], \r\n"
        L"  d.[Description] \r\n"
        L"FROM [DeviceView] d \r\n"
        L"  LEFT JOIN [CameraDevice] cd ON(d.[Id] = cd.[Id] ) \r\n"
        L"  LEFT JOIN [GNSSDevice] g ON(d.[Id] = g.[Id] ) \r\n"
        L"  LEFT JOIN [GyroDevice] gd ON(d.[Id] = gd.[Id] ) \r\n"
        L"  LEFT JOIN [LineInputDevice] lid ON(d.[Id] = lid.[Id] ) \r\n"
        L"  LEFT JOIN [OilSpillDetectorDevice] osdd ON(d.[Id] = osdd.[Id] ) \r\n"
        L"  LEFT JOIN [RadioDevice] rdi ON(d.[Id] = rdi.[Id] ) \r\n"
        L"  LEFT JOIN [RadomeDevice] rdo ON(d.[Id] = rdo.[Id] ) \r\n"
        L"  LEFT JOIN [TrackerDevice] td ON(d.[Id] = td.[Id] ) \r\n"
        L"  LEFT JOIN [AisDevice] ad ON(d.[Id] = ad.[Id] ) \r\n"
        L"  LEFT JOIN [RadarDevice] rd ON(d.[Id] = rd.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationDevice] wsd ON(d.[Id] = wsd.[Id] )";
    WideString ComplexDeviceColumnData::BaseViewName = L"DeviceView";
    WideString ComplexDeviceColumnData::ViewAliasName = L"d";

    void ComplexDeviceColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, D_ID_FIELD_ID, id_ );
        Bind( statement, D_KIND_FIELD_ID, kind_ );
        Bind( statement, D_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, D_HOST_FIELD_ID, host_ );
        Bind( statement, D_NAME_FIELD_ID, name_ );
        Bind( statement, D_ENABLEDTIMESERIES_FIELD_ID, enabledTimeseries_ );
        Bind( statement, G_LATITUDETIMESERIES_FIELD_ID, gLatitudeTimeseries_ );
        Bind( statement, G_LONGITUDETIMESERIES_FIELD_ID, gLongitudeTimeseries_ );
        Bind( statement, G_ALTITUDETIMESERIES_FIELD_ID, gAltitudeTimeseries_ );
        Bind( statement, GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID, gdHeadingTrueNorthTimeseries_ );
        Bind( statement, GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID, gdHeadingMagneticNorthTimeseries_ );
        Bind( statement, GD_PITCHTIMESERIES_FIELD_ID, gdPitchTimeseries_ );
        Bind( statement, GD_RATEOFTURNTIMESERIES_FIELD_ID, gdRateOfTurnTimeseries_ );
        Bind( statement, GD_ROLLTIMESERIES_FIELD_ID, gdRollTimeseries_ );
        Bind( statement, GD_COURSETIMESERIES_FIELD_ID, gdCourseTimeseries_ );
        Bind( statement, GD_SPEEDTIMESERIES_FIELD_ID, gdSpeedTimeseries_ );
        Bind( statement, GD_GNSSDEVICE_FIELD_ID, gdGNSSDevice_ );
        Bind( statement, RDO_RADAR_FIELD_ID, rdoRadar_ );
        Bind( statement, RDO_PRESSURETIMESERIES_FIELD_ID, rdoPressureTimeseries_ );
        Bind( statement, RDO_TEMPERATURETIMESERIES_FIELD_ID, rdoTemperatureTimeseries_ );
        Bind( statement, RDO_DEWPOINTTIMESERIES_FIELD_ID, rdoDewPointTimeseries_ );
        Bind( statement, RDO_STATUSTIMESERIES_FIELD_ID, rdoStatusTimeseries_ );
        Bind( statement, RD_SAVESETTINGSTIMESERIES_FIELD_ID, rdSaveSettingsTimeseries_ );
        Bind( statement, RD_POWERONTIMESERIES_FIELD_ID, rdPowerOnTimeseries_ );
        Bind( statement, RD_TRACKINGONTIMESERIES_FIELD_ID, rdTrackingOnTimeseries_ );
        Bind( statement, RD_RADARPULSETIMESERIES_FIELD_ID, rdRadarPulseTimeseries_ );
        Bind( statement, RD_TUNINGTIMESERIES_FIELD_ID, rdTuningTimeseries_ );
        Bind( statement, RD_BLANKSECTOR1TIMESERIES_FIELD_ID, rdBlankSector1Timeseries_ );
        Bind( statement, RD_SECTOR1STARTTIMESERIES_FIELD_ID, rdSector1StartTimeseries_ );
        Bind( statement, RD_SECTOR1ENDTIMESERIES_FIELD_ID, rdSector1EndTimeseries_ );
        Bind( statement, RD_BLANKSECTOR2TIMESERIES_FIELD_ID, rdBlankSector2Timeseries_ );
        Bind( statement, RD_SECTOR2STARTTIMESERIES_FIELD_ID, rdSector2StartTimeseries_ );
        Bind( statement, RD_SECTOR2ENDTIMESERIES_FIELD_ID, rdSector2EndTimeseries_ );
        Bind( statement, RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID, rdEnableAutomaticFrequencyControlTimeseries_ );
        Bind( statement, RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID, rdAzimuthOffsetTimeseries_ );
        Bind( statement, RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID, rdEnableSensitivityTimeControlTimeseries_ );
        Bind( statement, RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID, rdAutomaticSensitivityTimeControlTimeseries_ );
        Bind( statement, RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID, rdSensitivityTimeControlLevelTimeseries_ );
        Bind( statement, RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID, rdEnableFastTimeConstantTimeseries_ );
        Bind( statement, RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID, rdFastTimeConstantLevelTimeseries_ );
        Bind( statement, RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID, rdFastTimeConstantModeTimeseries_ );
        Bind( statement, RD_LATITUDETIMESERIES_FIELD_ID, rdLatitudeTimeseries_ );
        Bind( statement, RD_LONGITUDETIMESERIES_FIELD_ID, rdLongitudeTimeseries_ );
        Bind( statement, RD_RADOME_FIELD_ID, rdRadome_ );
        Bind( statement, RD_GNSSDEVICE_FIELD_ID, rdGNSSDevice_ );
        Bind( statement, WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID, wsdBarometricPressureTimeseries_ );
        Bind( statement, WSD_AIRTEMPERATURETIMESERIES_FIELD_ID, wsdAirTemperatureTimeseries_ );
        Bind( statement, WSD_WATERTEMPERATURETIMESERIES_FIELD_ID, wsdWaterTemperatureTimeseries_ );
        Bind( statement, WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID, wsdRelativeHumidityTimeseries_ );
        Bind( statement, WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID, wsdAbsoluteHumidityTimeseries_ );
        Bind( statement, WSD_DEWPOINTTIMESERIES_FIELD_ID, wsdDewPointTimeseries_ );
        Bind( statement, WSD_WINDDIRECTIONTIMESERIES_FIELD_ID, wsdWindDirectionTimeseries_ );
        Bind( statement, WSD_WINDSPEEDTIMESERIES_FIELD_ID, wsdWindSpeedTimeseries_ );
        Bind( statement, WSD_GYRO_FIELD_ID, wsdGyro_ );
    }

    void ComplexDeviceColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            description_ = statement.GetWideString(D_DESCRIPTION_FIELD_ID);
    }

    WideString ComplexTrackerDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  td.[Id], \r\n"
        L"  td.[EntityType], \r\n"
        L"  td.[RowVersion], \r\n"
        L"  td.[Host], \r\n"
        L"  td.[Name], \r\n"
        L"  td.[EnabledTimeseries], \r\n"
        L"  rd.[SaveSettingsTimeseries], \r\n"
        L"  rd.[PowerOnTimeseries], \r\n"
        L"  rd.[TrackingOnTimeseries], \r\n"
        L"  rd.[RadarPulseTimeseries], \r\n"
        L"  rd.[TuningTimeseries], \r\n"
        L"  rd.[BlankSector1Timeseries], \r\n"
        L"  rd.[Sector1StartTimeseries], \r\n"
        L"  rd.[Sector1EndTimeseries], \r\n"
        L"  rd.[BlankSector2Timeseries], \r\n"
        L"  rd.[Sector2StartTimeseries], \r\n"
        L"  rd.[Sector2EndTimeseries], \r\n"
        L"  rd.[EnableAutomaticFrequencyControlTimeseries], \r\n"
        L"  rd.[AzimuthOffsetTimeseries], \r\n"
        L"  rd.[EnableSensitivityTimeControlTimeseries], \r\n"
        L"  rd.[AutomaticSensitivityTimeControlTimeseries], \r\n"
        L"  rd.[SensitivityTimeControlLevelTimeseries], \r\n"
        L"  rd.[EnableFastTimeConstantTimeseries], \r\n"
        L"  rd.[FastTimeConstantLevelTimeseries], \r\n"
        L"  rd.[FastTimeConstantModeTimeseries], \r\n"
        L"  rd.[LatitudeTimeseries], \r\n"
        L"  rd.[LongitudeTimeseries], \r\n"
        L"  rd.[Radome], \r\n"
        L"  rd.[GNSSDevice], \r\n"
        L"  td.[Description] \r\n"
        L"FROM [TrackerDeviceView] td \r\n"
        L"  LEFT JOIN [AisDevice] ad ON(td.[Id] = ad.[Id] ) \r\n"
        L"  LEFT JOIN [RadarDevice] rd ON(td.[Id] = rd.[Id] )";
    WideString ComplexTrackerDeviceColumnData::BaseViewName = L"TrackerDeviceView";
    WideString ComplexTrackerDeviceColumnData::ViewAliasName = L"td";

    void ComplexTrackerDeviceColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, TD_ID_FIELD_ID, id_ );
        Bind( statement, TD_KIND_FIELD_ID, kind_ );
        Bind( statement, TD_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, TD_HOST_FIELD_ID, host_ );
        Bind( statement, TD_NAME_FIELD_ID, name_ );
        Bind( statement, TD_ENABLEDTIMESERIES_FIELD_ID, enabledTimeseries_ );
        Bind( statement, RD_SAVESETTINGSTIMESERIES_FIELD_ID, rdSaveSettingsTimeseries_ );
        Bind( statement, RD_POWERONTIMESERIES_FIELD_ID, rdPowerOnTimeseries_ );
        Bind( statement, RD_TRACKINGONTIMESERIES_FIELD_ID, rdTrackingOnTimeseries_ );
        Bind( statement, RD_RADARPULSETIMESERIES_FIELD_ID, rdRadarPulseTimeseries_ );
        Bind( statement, RD_TUNINGTIMESERIES_FIELD_ID, rdTuningTimeseries_ );
        Bind( statement, RD_BLANKSECTOR1TIMESERIES_FIELD_ID, rdBlankSector1Timeseries_ );
        Bind( statement, RD_SECTOR1STARTTIMESERIES_FIELD_ID, rdSector1StartTimeseries_ );
        Bind( statement, RD_SECTOR1ENDTIMESERIES_FIELD_ID, rdSector1EndTimeseries_ );
        Bind( statement, RD_BLANKSECTOR2TIMESERIES_FIELD_ID, rdBlankSector2Timeseries_ );
        Bind( statement, RD_SECTOR2STARTTIMESERIES_FIELD_ID, rdSector2StartTimeseries_ );
        Bind( statement, RD_SECTOR2ENDTIMESERIES_FIELD_ID, rdSector2EndTimeseries_ );
        Bind( statement, RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID, rdEnableAutomaticFrequencyControlTimeseries_ );
        Bind( statement, RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID, rdAzimuthOffsetTimeseries_ );
        Bind( statement, RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID, rdEnableSensitivityTimeControlTimeseries_ );
        Bind( statement, RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID, rdAutomaticSensitivityTimeControlTimeseries_ );
        Bind( statement, RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID, rdSensitivityTimeControlLevelTimeseries_ );
        Bind( statement, RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID, rdEnableFastTimeConstantTimeseries_ );
        Bind( statement, RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID, rdFastTimeConstantLevelTimeseries_ );
        Bind( statement, RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID, rdFastTimeConstantModeTimeseries_ );
        Bind( statement, RD_LATITUDETIMESERIES_FIELD_ID, rdLatitudeTimeseries_ );
        Bind( statement, RD_LONGITUDETIMESERIES_FIELD_ID, rdLongitudeTimeseries_ );
        Bind( statement, RD_RADOME_FIELD_ID, rdRadome_ );
        Bind( statement, RD_GNSSDEVICE_FIELD_ID, rdGNSSDevice_ );
    }

    void ComplexTrackerDeviceColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            description_ = statement.GetWideString(TD_DESCRIPTION_FIELD_ID);
    }

    WideString ComplexTrackableItemColumnData::BaseQuery = L"SELECT \r\n"
        L"  ti.[Id], \r\n"
        L"  ti.[EntityType], \r\n"
        L"  ti.[RowVersion], \r\n"
        L"  a.[Name], \r\n"
        L"  a.[Type], \r\n"
        L"  aatn.[Name], \r\n"
        L"  aatn.[MMSI], \r\n"
        L"  aatn.[NavigationalAidType], \r\n"
        L"  aatn.[Position], \r\n"
        L"  aatn.[IsVirtual], \r\n"
        L"  aatn.[ToBow], \r\n"
        L"  aatn.[ToStern], \r\n"
        L"  aatn.[ToPort], \r\n"
        L"  aatn.[ToStarboard], \r\n"
        L"  aatn.[OffPositionTimeseries], \r\n"
        L"  v.[Name], \r\n"
        L"  v.[Type], \r\n"
        L"  vsl.[Name], \r\n"
        L"  vsl.[Type], \r\n"
        L"  vsl.[ToBow], \r\n"
        L"  vsl.[ToStern], \r\n"
        L"  vsl.[ToPort], \r\n"
        L"  vsl.[ToStarboard], \r\n"
        L"  vsl.[DraughtTimeseries], \r\n"
        L"  vsl.[PersonsOnBoardTimeseries] \r\n"
        L"FROM [TrackableItemView] ti \r\n"
        L"  LEFT JOIN [Aircraft] a ON(ti.[Id] = a.[Id] ) \r\n"
        L"  LEFT JOIN [AisAidToNavigation] aatn ON(ti.[Id] = aatn.[Id] ) \r\n"
        L"  LEFT JOIN [Vehicle] v ON(ti.[Id] = v.[Id] ) \r\n"
        L"  LEFT JOIN [Vessel] vsl ON(ti.[Id] = vsl.[Id] )";
    WideString ComplexTrackableItemColumnData::BaseViewName = L"TrackableItemView";
    WideString ComplexTrackableItemColumnData::ViewAliasName = L"ti";

    void ComplexTrackableItemColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, TI_ID_FIELD_ID, id_ );
        Bind( statement, TI_KIND_FIELD_ID, kind_ );
        Bind( statement, TI_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, A_NAME_FIELD_ID, aName_ );
        Bind( statement, A_TYPE_FIELD_ID, aType_ );
        Bind( statement, AATN_NAME_FIELD_ID, aatnName_ );
        Bind( statement, AATN_MMSI_FIELD_ID, aatnMMSI_ );
        Bind( statement, AATN_NAVIGATIONALAIDTYPE_FIELD_ID, aatnNavigationalAidType_ );
        Bind( statement, AATN_POSITION_FIELD_ID, aatnPosition_ );
        Bind( statement, AATN_ISVIRTUAL_FIELD_ID, aatnIsVirtual_ );
        Bind( statement, AATN_TOBOW_FIELD_ID, aatnToBow_ );
        Bind( statement, AATN_TOSTERN_FIELD_ID, aatnToStern_ );
        Bind( statement, AATN_TOPORT_FIELD_ID, aatnToPort_ );
        Bind( statement, AATN_TOSTARBOARD_FIELD_ID, aatnToStarboard_ );
        Bind( statement, AATN_OFFPOSITIONTIMESERIES_FIELD_ID, aatnOffPositionTimeseries_ );
        Bind( statement, V_NAME_FIELD_ID, vName_ );
        Bind( statement, V_TYPE_FIELD_ID, vType_ );
        Bind( statement, VSL_NAME_FIELD_ID, vslName_ );
        Bind( statement, VSL_TYPE_FIELD_ID, vslType_ );
        Bind( statement, VSL_TOBOW_FIELD_ID, vslToBow_ );
        Bind( statement, VSL_TOSTERN_FIELD_ID, vslToStern_ );
        Bind( statement, VSL_TOPORT_FIELD_ID, vslToPort_ );
        Bind( statement, VSL_TOSTARBOARD_FIELD_ID, vslToStarboard_ );
        Bind( statement, VSL_DRAUGHTTIMESERIES_FIELD_ID, vslDraughtTimeseries_ );
        Bind( statement, VSL_PERSONSONBOARDTIMESERIES_FIELD_ID, vslPersonsOnBoardTimeseries_ );
    }


    WideString ComplexNamespaceElementColumnData::BaseQuery = L"SELECT \r\n"
        L"  ne.[Id], \r\n"
        L"  ne.[EntityType], \r\n"
        L"  ne.[RowVersion], \r\n"
        L"  ne.[Namespace], \r\n"
        L"  ne.[Name], \r\n"
        L"  ne.[Description] \r\n"
        L"FROM [NamespaceElementView] ne \r\n"
        L"  LEFT JOIN [ElementType] et ON(ne.[Id] = et.[Id] ) \r\n"
        L"  LEFT JOIN [Namespace] n ON(ne.[Id] = n.[Id] )";
    WideString ComplexNamespaceElementColumnData::BaseViewName = L"NamespaceElementView";
    WideString ComplexNamespaceElementColumnData::ViewAliasName = L"ne";

    void ComplexNamespaceElementColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, NE_ID_FIELD_ID, id_ );
        Bind( statement, NE_KIND_FIELD_ID, kind_ );
        Bind( statement, NE_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, NE_NAMESPACE_FIELD_ID, namespace_ );
        Bind( statement, NE_NAME_FIELD_ID, name_ );
    }

    void ComplexNamespaceElementColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            description_ = statement.GetWideString(NE_DESCRIPTION_FIELD_ID);
    }

    WideString ComplexPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  p.[Id], \r\n"
        L"  p.[EntityType], \r\n"
        L"  p.[RowVersion], \r\n"
        L"  p.[Element], \r\n"
        L"  p.[Definition], \r\n"
        L"  bop.[Value], \r\n"
        L"  byp.[Value], \r\n"
        L"  dtp.[Value], \r\n"
        L"  dp.[Value], \r\n"
        L"  gp.[Value], \r\n"
        L"  i16p.[Value], \r\n"
        L"  i32p.[Value], \r\n"
        L"  i64p.[Value], \r\n"
        L"  rp.[Value], \r\n"
        L"  sp.[Value], \r\n"
        L"  sip.[Value], \r\n"
        L"  stp.[Value], \r\n"
        L"  btp.[Timeseries], \r\n"
        L"  botp.[Timeseries], \r\n"
        L"  bytp.[Timeseries], \r\n"
        L"  dttp.[Timeseries], \r\n"
        L"  dotp.[Timeseries], \r\n"
        L"  gtp.[Timeseries], \r\n"
        L"  i16tp.[Timeseries], \r\n"
        L"  i32tp.[Timeseries], \r\n"
        L"  i64tp.[Timeseries], \r\n"
        L"  rtp.[Timeseries], \r\n"
        L"  sbtp.[Timeseries], \r\n"
        L"  sitp.[Timeseries], \r\n"
        L"  sttp.[Timeseries], \r\n"
        L"  tstp.[Timeseries], \r\n"
        L"  u16tp.[Timeseries], \r\n"
        L"  u32tp.[Timeseries], \r\n"
        L"  u64tp.[Timeseries], \r\n"
        L"  tsp.[Value], \r\n"
        L"  u16p.[Value], \r\n"
        L"  u32p.[Value], \r\n"
        L"  u64p.[Value], \r\n"
        L"  bp.[Value] \r\n"
        L"FROM [PropertyView] p \r\n"
        L"  LEFT JOIN [BinaryProperty] bp ON(p.[Id] = bp.[Id] ) \r\n"
        L"  LEFT JOIN [BooleanProperty] bop ON(p.[Id] = bop.[Id] ) \r\n"
        L"  LEFT JOIN [ByteProperty] byp ON(p.[Id] = byp.[Id] ) \r\n"
        L"  LEFT JOIN [DateTimeProperty] dtp ON(p.[Id] = dtp.[Id] ) \r\n"
        L"  LEFT JOIN [DoubleProperty] dp ON(p.[Id] = dp.[Id] ) \r\n"
        L"  LEFT JOIN [GuidProperty] gp ON(p.[Id] = gp.[Id] ) \r\n"
        L"  LEFT JOIN [Int16Property] i16p ON(p.[Id] = i16p.[Id] ) \r\n"
        L"  LEFT JOIN [Int32Property] i32p ON(p.[Id] = i32p.[Id] ) \r\n"
        L"  LEFT JOIN [Int64Property] i64p ON(p.[Id] = i64p.[Id] ) \r\n"
        L"  LEFT JOIN [ReferenceProperty] rp ON(p.[Id] = rp.[Id] ) \r\n"
        L"  LEFT JOIN [SByteProperty] sp ON(p.[Id] = sp.[Id] ) \r\n"
        L"  LEFT JOIN [SingleProperty] sip ON(p.[Id] = sip.[Id] ) \r\n"
        L"  LEFT JOIN [StringProperty] stp ON(p.[Id] = stp.[Id] ) \r\n"
        L"  LEFT JOIN [TimeseriesProperty] tp ON(p.[Id] = tp.[Id] ) \r\n"
        L"  LEFT JOIN [BinaryTimeseriesProperty] btp ON(p.[Id] = btp.[Id] ) \r\n"
        L"  LEFT JOIN [BooleanTimeseriesProperty] botp ON(p.[Id] = botp.[Id] ) \r\n"
        L"  LEFT JOIN [ByteTimeseriesProperty] bytp ON(p.[Id] = bytp.[Id] ) \r\n"
        L"  LEFT JOIN [DateTimeTimeseriesProperty] dttp ON(p.[Id] = dttp.[Id] ) \r\n"
        L"  LEFT JOIN [DoubleTimeseriesProperty] dotp ON(p.[Id] = dotp.[Id] ) \r\n"
        L"  LEFT JOIN [GuidTimeseriesProperty] gtp ON(p.[Id] = gtp.[Id] ) \r\n"
        L"  LEFT JOIN [Int16TimeseriesProperty] i16tp ON(p.[Id] = i16tp.[Id] ) \r\n"
        L"  LEFT JOIN [Int32TimeseriesProperty] i32tp ON(p.[Id] = i32tp.[Id] ) \r\n"
        L"  LEFT JOIN [Int64TimeseriesProperty] i64tp ON(p.[Id] = i64tp.[Id] ) \r\n"
        L"  LEFT JOIN [ReferenceTimeseriesProperty] rtp ON(p.[Id] = rtp.[Id] ) \r\n"
        L"  LEFT JOIN [SByteTimeseriesProperty] sbtp ON(p.[Id] = sbtp.[Id] ) \r\n"
        L"  LEFT JOIN [SingleTimeseriesProperty] sitp ON(p.[Id] = sitp.[Id] ) \r\n"
        L"  LEFT JOIN [StringTimeseriesProperty] sttp ON(p.[Id] = sttp.[Id] ) \r\n"
        L"  LEFT JOIN [TimeSpanTimeseriesProperty] tstp ON(p.[Id] = tstp.[Id] ) \r\n"
        L"  LEFT JOIN [UInt16TimeseriesProperty] u16tp ON(p.[Id] = u16tp.[Id] ) \r\n"
        L"  LEFT JOIN [UInt32TimeseriesProperty] u32tp ON(p.[Id] = u32tp.[Id] ) \r\n"
        L"  LEFT JOIN [UInt64TimeseriesProperty] u64tp ON(p.[Id] = u64tp.[Id] ) \r\n"
        L"  LEFT JOIN [TimeSpanProperty] tsp ON(p.[Id] = tsp.[Id] ) \r\n"
        L"  LEFT JOIN [UInt16Property] u16p ON(p.[Id] = u16p.[Id] ) \r\n"
        L"  LEFT JOIN [UInt32Property] u32p ON(p.[Id] = u32p.[Id] ) \r\n"
        L"  LEFT JOIN [UInt64Property] u64p ON(p.[Id] = u64p.[Id] )";
    WideString ComplexPropertyColumnData::BaseViewName = L"PropertyView";
    WideString ComplexPropertyColumnData::ViewAliasName = L"p";

    void ComplexPropertyColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, P_ID_FIELD_ID, id_ );
        Bind( statement, P_KIND_FIELD_ID, kind_ );
        Bind( statement, P_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, P_ELEMENT_FIELD_ID, element_ );
        Bind( statement, P_DEFINITION_FIELD_ID, definition_ );
        Bind( statement, BOP_VALUE_FIELD_ID, bopValue_ );
        Bind( statement, BYP_VALUE_FIELD_ID, bypValue_ );
        Bind( statement, DTP_VALUE_FIELD_ID, dtpValue_ );
        Bind( statement, DP_VALUE_FIELD_ID, dpValue_ );
        Bind( statement, GP_VALUE_FIELD_ID, gpValue_ );
        Bind( statement, I16P_VALUE_FIELD_ID, i16pValue_ );
        Bind( statement, I32P_VALUE_FIELD_ID, i32pValue_ );
        Bind( statement, I64P_VALUE_FIELD_ID, i64pValue_ );
        Bind( statement, RP_VALUE_FIELD_ID, rpValue_ );
        Bind( statement, SP_VALUE_FIELD_ID, spValue_ );
        Bind( statement, SIP_VALUE_FIELD_ID, sipValue_ );
        Bind( statement, STP_VALUE_FIELD_ID, stpValue_ );
        Bind( statement, BTP_TIMESERIES_FIELD_ID, btpTimeseries_ );
        Bind( statement, BOTP_TIMESERIES_FIELD_ID, botpTimeseries_ );
        Bind( statement, BYTP_TIMESERIES_FIELD_ID, bytpTimeseries_ );
        Bind( statement, DTTP_TIMESERIES_FIELD_ID, dttpTimeseries_ );
        Bind( statement, DOTP_TIMESERIES_FIELD_ID, dotpTimeseries_ );
        Bind( statement, GTP_TIMESERIES_FIELD_ID, gtpTimeseries_ );
        Bind( statement, I16TP_TIMESERIES_FIELD_ID, i16tpTimeseries_ );
        Bind( statement, I32TP_TIMESERIES_FIELD_ID, i32tpTimeseries_ );
        Bind( statement, I64TP_TIMESERIES_FIELD_ID, i64tpTimeseries_ );
        Bind( statement, RTP_TIMESERIES_FIELD_ID, rtpTimeseries_ );
        Bind( statement, SBTP_TIMESERIES_FIELD_ID, sbtpTimeseries_ );
        Bind( statement, SITP_TIMESERIES_FIELD_ID, sitpTimeseries_ );
        Bind( statement, STTP_TIMESERIES_FIELD_ID, sttpTimeseries_ );
        Bind( statement, TSTP_TIMESERIES_FIELD_ID, tstpTimeseries_ );
        Bind( statement, U16TP_TIMESERIES_FIELD_ID, u16tpTimeseries_ );
        Bind( statement, U32TP_TIMESERIES_FIELD_ID, u32tpTimeseries_ );
        Bind( statement, U64TP_TIMESERIES_FIELD_ID, u64tpTimeseries_ );
        Bind( statement, TSP_VALUE_FIELD_ID, tspValue_ );
        Bind( statement, U16P_VALUE_FIELD_ID, u16pValue_ );
        Bind( statement, U32P_VALUE_FIELD_ID, u32pValue_ );
        Bind( statement, U64P_VALUE_FIELD_ID, u64pValue_ );
    }

    void ComplexPropertyColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            bpValue_ = statement.GetDBBinary(BP_VALUE_FIELD_ID);
    }

    WideString ComplexTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  tp.[Id], \r\n"
        L"  tp.[EntityType], \r\n"
        L"  tp.[RowVersion], \r\n"
        L"  tp.[Element], \r\n"
        L"  tp.[Definition], \r\n"
        L"  btp.[Timeseries], \r\n"
        L"  botp.[Timeseries], \r\n"
        L"  bytp.[Timeseries], \r\n"
        L"  dttp.[Timeseries], \r\n"
        L"  dotp.[Timeseries], \r\n"
        L"  gtp.[Timeseries], \r\n"
        L"  i16tp.[Timeseries], \r\n"
        L"  i32tp.[Timeseries], \r\n"
        L"  i64tp.[Timeseries], \r\n"
        L"  rtp.[Timeseries], \r\n"
        L"  sbtp.[Timeseries], \r\n"
        L"  sitp.[Timeseries], \r\n"
        L"  sttp.[Timeseries], \r\n"
        L"  tstp.[Timeseries], \r\n"
        L"  u16tp.[Timeseries], \r\n"
        L"  u32tp.[Timeseries], \r\n"
        L"  u64tp.[Timeseries] \r\n"
        L"FROM [TimeseriesPropertyView] tp \r\n"
        L"  LEFT JOIN [BinaryTimeseriesProperty] btp ON(tp.[Id] = btp.[Id] ) \r\n"
        L"  LEFT JOIN [BooleanTimeseriesProperty] botp ON(tp.[Id] = botp.[Id] ) \r\n"
        L"  LEFT JOIN [ByteTimeseriesProperty] bytp ON(tp.[Id] = bytp.[Id] ) \r\n"
        L"  LEFT JOIN [DateTimeTimeseriesProperty] dttp ON(tp.[Id] = dttp.[Id] ) \r\n"
        L"  LEFT JOIN [DoubleTimeseriesProperty] dotp ON(tp.[Id] = dotp.[Id] ) \r\n"
        L"  LEFT JOIN [GuidTimeseriesProperty] gtp ON(tp.[Id] = gtp.[Id] ) \r\n"
        L"  LEFT JOIN [Int16TimeseriesProperty] i16tp ON(tp.[Id] = i16tp.[Id] ) \r\n"
        L"  LEFT JOIN [Int32TimeseriesProperty] i32tp ON(tp.[Id] = i32tp.[Id] ) \r\n"
        L"  LEFT JOIN [Int64TimeseriesProperty] i64tp ON(tp.[Id] = i64tp.[Id] ) \r\n"
        L"  LEFT JOIN [ReferenceTimeseriesProperty] rtp ON(tp.[Id] = rtp.[Id] ) \r\n"
        L"  LEFT JOIN [SByteTimeseriesProperty] sbtp ON(tp.[Id] = sbtp.[Id] ) \r\n"
        L"  LEFT JOIN [SingleTimeseriesProperty] sitp ON(tp.[Id] = sitp.[Id] ) \r\n"
        L"  LEFT JOIN [StringTimeseriesProperty] sttp ON(tp.[Id] = sttp.[Id] ) \r\n"
        L"  LEFT JOIN [TimeSpanTimeseriesProperty] tstp ON(tp.[Id] = tstp.[Id] ) \r\n"
        L"  LEFT JOIN [UInt16TimeseriesProperty] u16tp ON(tp.[Id] = u16tp.[Id] ) \r\n"
        L"  LEFT JOIN [UInt32TimeseriesProperty] u32tp ON(tp.[Id] = u32tp.[Id] ) \r\n"
        L"  LEFT JOIN [UInt64TimeseriesProperty] u64tp ON(tp.[Id] = u64tp.[Id] )";
    WideString ComplexTimeseriesPropertyColumnData::BaseViewName = L"TimeseriesPropertyView";
    WideString ComplexTimeseriesPropertyColumnData::ViewAliasName = L"tp";

    void ComplexTimeseriesPropertyColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, TP_ID_FIELD_ID, id_ );
        Bind( statement, TP_KIND_FIELD_ID, kind_ );
        Bind( statement, TP_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, TP_ELEMENT_FIELD_ID, element_ );
        Bind( statement, TP_DEFINITION_FIELD_ID, definition_ );
        Bind( statement, BTP_TIMESERIES_FIELD_ID, btpTimeseries_ );
        Bind( statement, BOTP_TIMESERIES_FIELD_ID, botpTimeseries_ );
        Bind( statement, BYTP_TIMESERIES_FIELD_ID, bytpTimeseries_ );
        Bind( statement, DTTP_TIMESERIES_FIELD_ID, dttpTimeseries_ );
        Bind( statement, DOTP_TIMESERIES_FIELD_ID, dotpTimeseries_ );
        Bind( statement, GTP_TIMESERIES_FIELD_ID, gtpTimeseries_ );
        Bind( statement, I16TP_TIMESERIES_FIELD_ID, i16tpTimeseries_ );
        Bind( statement, I32TP_TIMESERIES_FIELD_ID, i32tpTimeseries_ );
        Bind( statement, I64TP_TIMESERIES_FIELD_ID, i64tpTimeseries_ );
        Bind( statement, RTP_TIMESERIES_FIELD_ID, rtpTimeseries_ );
        Bind( statement, SBTP_TIMESERIES_FIELD_ID, sbtpTimeseries_ );
        Bind( statement, SITP_TIMESERIES_FIELD_ID, sitpTimeseries_ );
        Bind( statement, STTP_TIMESERIES_FIELD_ID, sttpTimeseries_ );
        Bind( statement, TSTP_TIMESERIES_FIELD_ID, tstpTimeseries_ );
        Bind( statement, U16TP_TIMESERIES_FIELD_ID, u16tpTimeseries_ );
        Bind( statement, U32TP_TIMESERIES_FIELD_ID, u32tpTimeseries_ );
        Bind( statement, U64TP_TIMESERIES_FIELD_ID, u64tpTimeseries_ );
    }


    WideString ComplexPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  pd.[Id], \r\n"
        L"  pd.[EntityType], \r\n"
        L"  pd.[RowVersion], \r\n"
        L"  pd.[ElementType], \r\n"
        L"  pd.[Name], \r\n"
        L"  bopd.[DefaultValue], \r\n"
        L"  bypd.[DefaultValue], \r\n"
        L"  bypd.[MinValue], \r\n"
        L"  bypd.[MaxValue], \r\n"
        L"  dtpd.[DefaultValue], \r\n"
        L"  dtpd.[MinValue], \r\n"
        L"  dtpd.[MaxValue], \r\n"
        L"  dpd.[DefaultValue], \r\n"
        L"  dpd.[MinValue], \r\n"
        L"  dpd.[MaxValue], \r\n"
        L"  gpd.[DefaultValue], \r\n"
        L"  i16pd.[DefaultValue], \r\n"
        L"  i16pd.[MinValue], \r\n"
        L"  i16pd.[MaxValue], \r\n"
        L"  i32pd.[DefaultValue], \r\n"
        L"  i32pd.[MinValue], \r\n"
        L"  i32pd.[MaxValue], \r\n"
        L"  i64pd.[DefaultValue], \r\n"
        L"  i64pd.[MinValue], \r\n"
        L"  i64pd.[MaxValue], \r\n"
        L"  rpd.[DefaultValue], \r\n"
        L"  rpd.[ReferencedElementType], \r\n"
        L"  sbpd.[DefaultValue], \r\n"
        L"  sbpd.[MinValue], \r\n"
        L"  sbpd.[MaxValue], \r\n"
        L"  sipd.[DefaultValue], \r\n"
        L"  sipd.[MinValue], \r\n"
        L"  sipd.[MaxValue], \r\n"
        L"  stpd.[DefaultValue], \r\n"
        L"  stpd.[Pattern], \r\n"
        L"  bytpd.[MinValue], \r\n"
        L"  bytpd.[MaxValue], \r\n"
        L"  dttpd.[MinValue], \r\n"
        L"  dttpd.[MaxValue], \r\n"
        L"  dotpd.[MinValue], \r\n"
        L"  dotpd.[MaxValue], \r\n"
        L"  i16tpd.[MinValue], \r\n"
        L"  i16tpd.[MaxValue], \r\n"
        L"  i32tpd.[MinValue], \r\n"
        L"  i32tpd.[MaxValue], \r\n"
        L"  i64tpd.[MinValue], \r\n"
        L"  i64tpd.[MaxValue], \r\n"
        L"  rtpd.[ReferencedElementType], \r\n"
        L"  sbtpd.[MinValue], \r\n"
        L"  sbtpd.[MaxValue], \r\n"
        L"  sitpd.[MinValue], \r\n"
        L"  sitpd.[MaxValue], \r\n"
        L"  sttpd.[Pattern], \r\n"
        L"  tstpd.[MinValue], \r\n"
        L"  tstpd.[MaxValue], \r\n"
        L"  u16tpd.[MinValue], \r\n"
        L"  u16tpd.[MaxValue], \r\n"
        L"  u32tpd.[MinValue], \r\n"
        L"  u32tpd.[MaxValue], \r\n"
        L"  u64tpd.[MinValue], \r\n"
        L"  u64tpd.[MaxValue], \r\n"
        L"  tspd.[DefaultValue], \r\n"
        L"  tspd.[MinValue], \r\n"
        L"  tspd.[MaxValue], \r\n"
        L"  u16pd.[DefaultValue], \r\n"
        L"  u16pd.[MinValue], \r\n"
        L"  u16pd.[MaxValue], \r\n"
        L"  u32pd.[DefaultValue], \r\n"
        L"  u32pd.[MinValue], \r\n"
        L"  u32pd.[MaxValue], \r\n"
        L"  u64pd.[DefaultValue], \r\n"
        L"  u64pd.[MinValue], \r\n"
        L"  u64pd.[MaxValue], \r\n"
        L"  pd.[Description], \r\n"
        L"  bpd.[DefaultValue] \r\n"
        L"FROM [PropertyDefinitionView] pd \r\n"
        L"  LEFT JOIN [BinaryPropertyDefinition] bpd ON(pd.[Id] = bpd.[Id] ) \r\n"
        L"  LEFT JOIN [BooleanPropertyDefinition] bopd ON(pd.[Id] = bopd.[Id] ) \r\n"
        L"  LEFT JOIN [BytePropertyDefinition] bypd ON(pd.[Id] = bypd.[Id] ) \r\n"
        L"  LEFT JOIN [DateTimePropertyDefinition] dtpd ON(pd.[Id] = dtpd.[Id] ) \r\n"
        L"  LEFT JOIN [DoublePropertyDefinition] dpd ON(pd.[Id] = dpd.[Id] ) \r\n"
        L"  LEFT JOIN [GuidPropertyDefinition] gpd ON(pd.[Id] = gpd.[Id] ) \r\n"
        L"  LEFT JOIN [Int16PropertyDefinition] i16pd ON(pd.[Id] = i16pd.[Id] ) \r\n"
        L"  LEFT JOIN [Int32PropertyDefinition] i32pd ON(pd.[Id] = i32pd.[Id] ) \r\n"
        L"  LEFT JOIN [Int64PropertyDefinition] i64pd ON(pd.[Id] = i64pd.[Id] ) \r\n"
        L"  LEFT JOIN [ReferencePropertyDefinition] rpd ON(pd.[Id] = rpd.[Id] ) \r\n"
        L"  LEFT JOIN [SBytePropertyDefinition] sbpd ON(pd.[Id] = sbpd.[Id] ) \r\n"
        L"  LEFT JOIN [SinglePropertyDefinition] sipd ON(pd.[Id] = sipd.[Id] ) \r\n"
        L"  LEFT JOIN [StringPropertyDefinition] stpd ON(pd.[Id] = stpd.[Id] ) \r\n"
        L"  LEFT JOIN [TimeseriesPropertyDefinition] tpd ON(pd.[Id] = tpd.[Id] ) \r\n"
        L"  LEFT JOIN [BinaryTimeseriesPropertyDefinition] btpd ON(pd.[Id] = btpd.[Id] ) \r\n"
        L"  LEFT JOIN [BooleanTimeseriesPropertyDefinition] botpd ON(pd.[Id] = botpd.[Id] ) \r\n"
        L"  LEFT JOIN [ByteTimeseriesPropertyDefinition] bytpd ON(pd.[Id] = bytpd.[Id] ) \r\n"
        L"  LEFT JOIN [DateTimeTimeseriesPropertyDefinition] dttpd ON(pd.[Id] = dttpd.[Id] ) \r\n"
        L"  LEFT JOIN [DoubleTimeseriesPropertyDefinition] dotpd ON(pd.[Id] = dotpd.[Id] ) \r\n"
        L"  LEFT JOIN [GuidTimeseriesPropertyDefinition] gtpd ON(pd.[Id] = gtpd.[Id] ) \r\n"
        L"  LEFT JOIN [Int16TimeseriesPropertyDefinition] i16tpd ON(pd.[Id] = i16tpd.[Id] ) \r\n"
        L"  LEFT JOIN [Int32TimeseriesPropertyDefinition] i32tpd ON(pd.[Id] = i32tpd.[Id] ) \r\n"
        L"  LEFT JOIN [Int64TimeseriesPropertyDefinition] i64tpd ON(pd.[Id] = i64tpd.[Id] ) \r\n"
        L"  LEFT JOIN [ReferenceTimeseriesPropertyDefinition] rtpd ON(pd.[Id] = rtpd.[Id] ) \r\n"
        L"  LEFT JOIN [SByteTimeseriesPropertyDefinition] sbtpd ON(pd.[Id] = sbtpd.[Id] ) \r\n"
        L"  LEFT JOIN [SingleTimeseriesPropertyDefinition] sitpd ON(pd.[Id] = sitpd.[Id] ) \r\n"
        L"  LEFT JOIN [StringTimeseriesPropertyDefinition] sttpd ON(pd.[Id] = sttpd.[Id] ) \r\n"
        L"  LEFT JOIN [TimeSpanTimeseriesPropertyDefinition] tstpd ON(pd.[Id] = tstpd.[Id] ) \r\n"
        L"  LEFT JOIN [UInt16TimeseriesPropertyDefinition] u16tpd ON(pd.[Id] = u16tpd.[Id] ) \r\n"
        L"  LEFT JOIN [UInt32TimeseriesPropertyDefinition] u32tpd ON(pd.[Id] = u32tpd.[Id] ) \r\n"
        L"  LEFT JOIN [UInt64TimeseriesPropertyDefinition] u64tpd ON(pd.[Id] = u64tpd.[Id] ) \r\n"
        L"  LEFT JOIN [TimeSpanPropertyDefinition] tspd ON(pd.[Id] = tspd.[Id] ) \r\n"
        L"  LEFT JOIN [UInt16PropertyDefinition] u16pd ON(pd.[Id] = u16pd.[Id] ) \r\n"
        L"  LEFT JOIN [UInt32PropertyDefinition] u32pd ON(pd.[Id] = u32pd.[Id] ) \r\n"
        L"  LEFT JOIN [UInt64PropertyDefinition] u64pd ON(pd.[Id] = u64pd.[Id] )";
    WideString ComplexPropertyDefinitionColumnData::BaseViewName = L"PropertyDefinitionView";
    WideString ComplexPropertyDefinitionColumnData::ViewAliasName = L"pd";

    void ComplexPropertyDefinitionColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, PD_ID_FIELD_ID, id_ );
        Bind( statement, PD_KIND_FIELD_ID, kind_ );
        Bind( statement, PD_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, PD_ELEMENTTYPE_FIELD_ID, elementType_ );
        Bind( statement, PD_NAME_FIELD_ID, name_ );
        Bind( statement, BOPD_DEFAULTVALUE_FIELD_ID, bopdDefaultValue_ );
        Bind( statement, BYPD_DEFAULTVALUE_FIELD_ID, bypdDefaultValue_ );
        Bind( statement, BYPD_MINVALUE_FIELD_ID, bypdMinValue_ );
        Bind( statement, BYPD_MAXVALUE_FIELD_ID, bypdMaxValue_ );
        Bind( statement, DTPD_DEFAULTVALUE_FIELD_ID, dtpdDefaultValue_ );
        Bind( statement, DTPD_MINVALUE_FIELD_ID, dtpdMinValue_ );
        Bind( statement, DTPD_MAXVALUE_FIELD_ID, dtpdMaxValue_ );
        Bind( statement, DPD_DEFAULTVALUE_FIELD_ID, dpdDefaultValue_ );
        Bind( statement, DPD_MINVALUE_FIELD_ID, dpdMinValue_ );
        Bind( statement, DPD_MAXVALUE_FIELD_ID, dpdMaxValue_ );
        Bind( statement, GPD_DEFAULTVALUE_FIELD_ID, gpdDefaultValue_ );
        Bind( statement, I16PD_DEFAULTVALUE_FIELD_ID, i16pdDefaultValue_ );
        Bind( statement, I16PD_MINVALUE_FIELD_ID, i16pdMinValue_ );
        Bind( statement, I16PD_MAXVALUE_FIELD_ID, i16pdMaxValue_ );
        Bind( statement, I32PD_DEFAULTVALUE_FIELD_ID, i32pdDefaultValue_ );
        Bind( statement, I32PD_MINVALUE_FIELD_ID, i32pdMinValue_ );
        Bind( statement, I32PD_MAXVALUE_FIELD_ID, i32pdMaxValue_ );
        Bind( statement, I64PD_DEFAULTVALUE_FIELD_ID, i64pdDefaultValue_ );
        Bind( statement, I64PD_MINVALUE_FIELD_ID, i64pdMinValue_ );
        Bind( statement, I64PD_MAXVALUE_FIELD_ID, i64pdMaxValue_ );
        Bind( statement, RPD_DEFAULTVALUE_FIELD_ID, rpdDefaultValue_ );
        Bind( statement, RPD_REFERENCEDELEMENTTYPE_FIELD_ID, rpdReferencedElementType_ );
        Bind( statement, SBPD_DEFAULTVALUE_FIELD_ID, sbpdDefaultValue_ );
        Bind( statement, SBPD_MINVALUE_FIELD_ID, sbpdMinValue_ );
        Bind( statement, SBPD_MAXVALUE_FIELD_ID, sbpdMaxValue_ );
        Bind( statement, SIPD_DEFAULTVALUE_FIELD_ID, sipdDefaultValue_ );
        Bind( statement, SIPD_MINVALUE_FIELD_ID, sipdMinValue_ );
        Bind( statement, SIPD_MAXVALUE_FIELD_ID, sipdMaxValue_ );
        Bind( statement, STPD_DEFAULTVALUE_FIELD_ID, stpdDefaultValue_ );
        Bind( statement, STPD_PATTERN_FIELD_ID, stpdPattern_ );
        Bind( statement, BYTPD_MINVALUE_FIELD_ID, bytpdMinValue_ );
        Bind( statement, BYTPD_MAXVALUE_FIELD_ID, bytpdMaxValue_ );
        Bind( statement, DTTPD_MINVALUE_FIELD_ID, dttpdMinValue_ );
        Bind( statement, DTTPD_MAXVALUE_FIELD_ID, dttpdMaxValue_ );
        Bind( statement, DOTPD_MINVALUE_FIELD_ID, dotpdMinValue_ );
        Bind( statement, DOTPD_MAXVALUE_FIELD_ID, dotpdMaxValue_ );
        Bind( statement, I16TPD_MINVALUE_FIELD_ID, i16tpdMinValue_ );
        Bind( statement, I16TPD_MAXVALUE_FIELD_ID, i16tpdMaxValue_ );
        Bind( statement, I32TPD_MINVALUE_FIELD_ID, i32tpdMinValue_ );
        Bind( statement, I32TPD_MAXVALUE_FIELD_ID, i32tpdMaxValue_ );
        Bind( statement, I64TPD_MINVALUE_FIELD_ID, i64tpdMinValue_ );
        Bind( statement, I64TPD_MAXVALUE_FIELD_ID, i64tpdMaxValue_ );
        Bind( statement, RTPD_REFERENCEDELEMENTTYPE_FIELD_ID, rtpdReferencedElementType_ );
        Bind( statement, SBTPD_MINVALUE_FIELD_ID, sbtpdMinValue_ );
        Bind( statement, SBTPD_MAXVALUE_FIELD_ID, sbtpdMaxValue_ );
        Bind( statement, SITPD_MINVALUE_FIELD_ID, sitpdMinValue_ );
        Bind( statement, SITPD_MAXVALUE_FIELD_ID, sitpdMaxValue_ );
        Bind( statement, STTPD_PATTERN_FIELD_ID, sttpdPattern_ );
        Bind( statement, TSTPD_MINVALUE_FIELD_ID, tstpdMinValue_ );
        Bind( statement, TSTPD_MAXVALUE_FIELD_ID, tstpdMaxValue_ );
        Bind( statement, U16TPD_MINVALUE_FIELD_ID, u16tpdMinValue_ );
        Bind( statement, U16TPD_MAXVALUE_FIELD_ID, u16tpdMaxValue_ );
        Bind( statement, U32TPD_MINVALUE_FIELD_ID, u32tpdMinValue_ );
        Bind( statement, U32TPD_MAXVALUE_FIELD_ID, u32tpdMaxValue_ );
        Bind( statement, U64TPD_MINVALUE_FIELD_ID, u64tpdMinValue_ );
        Bind( statement, U64TPD_MAXVALUE_FIELD_ID, u64tpdMaxValue_ );
        Bind( statement, TSPD_DEFAULTVALUE_FIELD_ID, tspdDefaultValue_ );
        Bind( statement, TSPD_MINVALUE_FIELD_ID, tspdMinValue_ );
        Bind( statement, TSPD_MAXVALUE_FIELD_ID, tspdMaxValue_ );
        Bind( statement, U16PD_DEFAULTVALUE_FIELD_ID, u16pdDefaultValue_ );
        Bind( statement, U16PD_MINVALUE_FIELD_ID, u16pdMinValue_ );
        Bind( statement, U16PD_MAXVALUE_FIELD_ID, u16pdMaxValue_ );
        Bind( statement, U32PD_DEFAULTVALUE_FIELD_ID, u32pdDefaultValue_ );
        Bind( statement, U32PD_MINVALUE_FIELD_ID, u32pdMinValue_ );
        Bind( statement, U32PD_MAXVALUE_FIELD_ID, u32pdMaxValue_ );
        Bind( statement, U64PD_DEFAULTVALUE_FIELD_ID, u64pdDefaultValue_ );
        Bind( statement, U64PD_MINVALUE_FIELD_ID, u64pdMinValue_ );
        Bind( statement, U64PD_MAXVALUE_FIELD_ID, u64pdMaxValue_ );
    }

    void ComplexPropertyDefinitionColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            description_ = statement.GetWideString(PD_DESCRIPTION_FIELD_ID);
            bpdDefaultValue_ = statement.GetDBBinary(BPD_DEFAULTVALUE_FIELD_ID);
    }

    WideString ComplexTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  tpd.[Id], \r\n"
        L"  tpd.[EntityType], \r\n"
        L"  tpd.[RowVersion], \r\n"
        L"  tpd.[ElementType], \r\n"
        L"  tpd.[Name], \r\n"
        L"  bytpd.[MinValue], \r\n"
        L"  bytpd.[MaxValue], \r\n"
        L"  dttpd.[MinValue], \r\n"
        L"  dttpd.[MaxValue], \r\n"
        L"  dotpd.[MinValue], \r\n"
        L"  dotpd.[MaxValue], \r\n"
        L"  i16tpd.[MinValue], \r\n"
        L"  i16tpd.[MaxValue], \r\n"
        L"  i32tpd.[MinValue], \r\n"
        L"  i32tpd.[MaxValue], \r\n"
        L"  i64tpd.[MinValue], \r\n"
        L"  i64tpd.[MaxValue], \r\n"
        L"  rtpd.[ReferencedElementType], \r\n"
        L"  sbtpd.[MinValue], \r\n"
        L"  sbtpd.[MaxValue], \r\n"
        L"  sitpd.[MinValue], \r\n"
        L"  sitpd.[MaxValue], \r\n"
        L"  sttpd.[Pattern], \r\n"
        L"  tstpd.[MinValue], \r\n"
        L"  tstpd.[MaxValue], \r\n"
        L"  u16tpd.[MinValue], \r\n"
        L"  u16tpd.[MaxValue], \r\n"
        L"  u32tpd.[MinValue], \r\n"
        L"  u32tpd.[MaxValue], \r\n"
        L"  u64tpd.[MinValue], \r\n"
        L"  u64tpd.[MaxValue], \r\n"
        L"  tpd.[Description] \r\n"
        L"FROM [TimeseriesPropertyDefinitionView] tpd \r\n"
        L"  LEFT JOIN [BinaryTimeseriesPropertyDefinition] btpd ON(tpd.[Id] = btpd.[Id] ) \r\n"
        L"  LEFT JOIN [BooleanTimeseriesPropertyDefinition] botpd ON(tpd.[Id] = botpd.[Id] ) \r\n"
        L"  LEFT JOIN [ByteTimeseriesPropertyDefinition] bytpd ON(tpd.[Id] = bytpd.[Id] ) \r\n"
        L"  LEFT JOIN [DateTimeTimeseriesPropertyDefinition] dttpd ON(tpd.[Id] = dttpd.[Id] ) \r\n"
        L"  LEFT JOIN [DoubleTimeseriesPropertyDefinition] dotpd ON(tpd.[Id] = dotpd.[Id] ) \r\n"
        L"  LEFT JOIN [GuidTimeseriesPropertyDefinition] gtpd ON(tpd.[Id] = gtpd.[Id] ) \r\n"
        L"  LEFT JOIN [Int16TimeseriesPropertyDefinition] i16tpd ON(tpd.[Id] = i16tpd.[Id] ) \r\n"
        L"  LEFT JOIN [Int32TimeseriesPropertyDefinition] i32tpd ON(tpd.[Id] = i32tpd.[Id] ) \r\n"
        L"  LEFT JOIN [Int64TimeseriesPropertyDefinition] i64tpd ON(tpd.[Id] = i64tpd.[Id] ) \r\n"
        L"  LEFT JOIN [ReferenceTimeseriesPropertyDefinition] rtpd ON(tpd.[Id] = rtpd.[Id] ) \r\n"
        L"  LEFT JOIN [SByteTimeseriesPropertyDefinition] sbtpd ON(tpd.[Id] = sbtpd.[Id] ) \r\n"
        L"  LEFT JOIN [SingleTimeseriesPropertyDefinition] sitpd ON(tpd.[Id] = sitpd.[Id] ) \r\n"
        L"  LEFT JOIN [StringTimeseriesPropertyDefinition] sttpd ON(tpd.[Id] = sttpd.[Id] ) \r\n"
        L"  LEFT JOIN [TimeSpanTimeseriesPropertyDefinition] tstpd ON(tpd.[Id] = tstpd.[Id] ) \r\n"
        L"  LEFT JOIN [UInt16TimeseriesPropertyDefinition] u16tpd ON(tpd.[Id] = u16tpd.[Id] ) \r\n"
        L"  LEFT JOIN [UInt32TimeseriesPropertyDefinition] u32tpd ON(tpd.[Id] = u32tpd.[Id] ) \r\n"
        L"  LEFT JOIN [UInt64TimeseriesPropertyDefinition] u64tpd ON(tpd.[Id] = u64tpd.[Id] )";
    WideString ComplexTimeseriesPropertyDefinitionColumnData::BaseViewName = L"TimeseriesPropertyDefinitionView";
    WideString ComplexTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"tpd";

    void ComplexTimeseriesPropertyDefinitionColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, TPD_ID_FIELD_ID, id_ );
        Bind( statement, TPD_KIND_FIELD_ID, kind_ );
        Bind( statement, TPD_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, TPD_ELEMENTTYPE_FIELD_ID, elementType_ );
        Bind( statement, TPD_NAME_FIELD_ID, name_ );
        Bind( statement, BYTPD_MINVALUE_FIELD_ID, bytpdMinValue_ );
        Bind( statement, BYTPD_MAXVALUE_FIELD_ID, bytpdMaxValue_ );
        Bind( statement, DTTPD_MINVALUE_FIELD_ID, dttpdMinValue_ );
        Bind( statement, DTTPD_MAXVALUE_FIELD_ID, dttpdMaxValue_ );
        Bind( statement, DOTPD_MINVALUE_FIELD_ID, dotpdMinValue_ );
        Bind( statement, DOTPD_MAXVALUE_FIELD_ID, dotpdMaxValue_ );
        Bind( statement, I16TPD_MINVALUE_FIELD_ID, i16tpdMinValue_ );
        Bind( statement, I16TPD_MAXVALUE_FIELD_ID, i16tpdMaxValue_ );
        Bind( statement, I32TPD_MINVALUE_FIELD_ID, i32tpdMinValue_ );
        Bind( statement, I32TPD_MAXVALUE_FIELD_ID, i32tpdMaxValue_ );
        Bind( statement, I64TPD_MINVALUE_FIELD_ID, i64tpdMinValue_ );
        Bind( statement, I64TPD_MAXVALUE_FIELD_ID, i64tpdMaxValue_ );
        Bind( statement, RTPD_REFERENCEDELEMENTTYPE_FIELD_ID, rtpdReferencedElementType_ );
        Bind( statement, SBTPD_MINVALUE_FIELD_ID, sbtpdMinValue_ );
        Bind( statement, SBTPD_MAXVALUE_FIELD_ID, sbtpdMaxValue_ );
        Bind( statement, SITPD_MINVALUE_FIELD_ID, sitpdMinValue_ );
        Bind( statement, SITPD_MAXVALUE_FIELD_ID, sitpdMaxValue_ );
        Bind( statement, STTPD_PATTERN_FIELD_ID, sttpdPattern_ );
        Bind( statement, TSTPD_MINVALUE_FIELD_ID, tstpdMinValue_ );
        Bind( statement, TSTPD_MAXVALUE_FIELD_ID, tstpdMaxValue_ );
        Bind( statement, U16TPD_MINVALUE_FIELD_ID, u16tpdMinValue_ );
        Bind( statement, U16TPD_MAXVALUE_FIELD_ID, u16tpdMaxValue_ );
        Bind( statement, U32TPD_MINVALUE_FIELD_ID, u32tpdMinValue_ );
        Bind( statement, U32TPD_MAXVALUE_FIELD_ID, u32tpdMaxValue_ );
        Bind( statement, U64TPD_MINVALUE_FIELD_ID, u64tpdMinValue_ );
        Bind( statement, U64TPD_MAXVALUE_FIELD_ID, u64tpdMaxValue_ );
    }

    void ComplexTimeseriesPropertyDefinitionColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            description_ = statement.GetWideString(TPD_DESCRIPTION_FIELD_ID);
    }

    WideString ComplexRadarCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  rc.[Id], \r\n"
        L"  rc.[EntityType], \r\n"
        L"  rc.[RowVersion], \r\n"
        L"  rc.[Radar], \r\n"
        L"  rc.[Timestamp], \r\n"
        L"  rc.[DeviceCommandSourceType], \r\n"
        L"  rc.[DeviceCommandSourceId], \r\n"
        L"  rc.[Reply] \r\n"
        L"FROM [RadarCommandView] rc \r\n"
        L"  LEFT JOIN [RadarCommandGetStatus] rcgs ON(rc.[Id] = rcgs.[Id] )";
    WideString ComplexRadarCommandColumnData::BaseViewName = L"RadarCommandView";
    WideString ComplexRadarCommandColumnData::ViewAliasName = L"rc";

    void ComplexRadarCommandColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, RC_ID_FIELD_ID, id_ );
        Bind( statement, RC_KIND_FIELD_ID, kind_ );
        Bind( statement, RC_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, RC_RADAR_FIELD_ID, radar_ );
        Bind( statement, RC_TIMESTAMP_FIELD_ID, timestamp_ );
        Bind( statement, RC_DEVICECOMMANDSOURCETYPE_FIELD_ID, deviceCommandSourceType_ );
        Bind( statement, RC_DEVICECOMMANDSOURCEID_FIELD_ID, deviceCommandSourceId_ );
        Bind( statement, RC_REPLY_FIELD_ID, reply_ );
    }


    WideString ComplexRadarCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  rcr.[Id], \r\n"
        L"  rcr.[EntityType], \r\n"
        L"  rcr.[RowVersion], \r\n"
        L"  rcr.[Radar], \r\n"
        L"  rcr.[Timestamp], \r\n"
        L"  rcr.[Command], \r\n"
        L"  rcr.[Status], \r\n"
        L"  rcrgs.[AzimuthCount], \r\n"
        L"  rcrgs.[TriggerCount], \r\n"
        L"  rcrgs.[RotationCount], \r\n"
        L"  rcrgs.[Pulse], \r\n"
        L"  rcrgs.[Tx], \r\n"
        L"  rcr.[Message] \r\n"
        L"FROM [RadarCommandReplyView] rcr \r\n"
        L"  LEFT JOIN [RadarCommandReplyGetStatus] rcrgs ON(rcr.[Id] = rcrgs.[Id] )";
    WideString ComplexRadarCommandReplyColumnData::BaseViewName = L"RadarCommandReplyView";
    WideString ComplexRadarCommandReplyColumnData::ViewAliasName = L"rcr";

    void ComplexRadarCommandReplyColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, RCR_ID_FIELD_ID, id_ );
        Bind( statement, RCR_KIND_FIELD_ID, kind_ );
        Bind( statement, RCR_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, RCR_RADAR_FIELD_ID, radar_ );
        Bind( statement, RCR_TIMESTAMP_FIELD_ID, timestamp_ );
        Bind( statement, RCR_COMMAND_FIELD_ID, command_ );
        Bind( statement, RCR_STATUS_FIELD_ID, status_ );
        Bind( statement, RCRGS_AZIMUTHCOUNT_FIELD_ID, rcrgsAzimuthCount_ );
        Bind( statement, RCRGS_TRIGGERCOUNT_FIELD_ID, rcrgsTriggerCount_ );
        Bind( statement, RCRGS_ROTATIONCOUNT_FIELD_ID, rcrgsRotationCount_ );
        Bind( statement, RCRGS_PULSE_FIELD_ID, rcrgsPulse_ );
        Bind( statement, RCRGS_TX_FIELD_ID, rcrgsTx_ );
    }

    void ComplexRadarCommandReplyColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            message_ = statement.GetWideString(RCR_MESSAGE_FIELD_ID);
    }

    WideString ComplexSecurityIdentifierColumnData::BaseQuery = L"SELECT \r\n"
        L"  si.[Id], \r\n"
        L"  si.[EntityType], \r\n"
        L"  si.[RowVersion], \r\n"
        L"  si.[Domain], \r\n"
        L"  si.[Identity], \r\n"
        L"  sr.[Name], \r\n"
        L"  si.[Description] \r\n"
        L"FROM [SecurityIdentifierView] si \r\n"
        L"  LEFT JOIN [SecurityLogin] sl ON(si.[Id] = sl.[Id] ) \r\n"
        L"  LEFT JOIN [SecurityRole] sr ON(si.[Id] = sr.[Id] )";
    WideString ComplexSecurityIdentifierColumnData::BaseViewName = L"SecurityIdentifierView";
    WideString ComplexSecurityIdentifierColumnData::ViewAliasName = L"si";

    void ComplexSecurityIdentifierColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, SI_ID_FIELD_ID, id_ );
        Bind( statement, SI_KIND_FIELD_ID, kind_ );
        Bind( statement, SI_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, SI_DOMAIN_FIELD_ID, domain_ );
        Bind( statement, SI_IDENTITY_FIELD_ID, identity_ );
        Bind( statement, SR_NAME_FIELD_ID, srName_ );
    }

    void ComplexSecurityIdentifierColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            description_ = statement.GetWideString(SI_DESCRIPTION_FIELD_ID);
    }

    WideString ComplexTimeseriesCatalogElementColumnData::BaseQuery = L"SELECT \r\n"
        L"  tce.[Id], \r\n"
        L"  tce.[EntityType], \r\n"
        L"  tce.[RowVersion], \r\n"
        L"  tce.[Catalog], \r\n"
        L"  tce.[Name], \r\n"
        L"  t.[MaxRetention], \r\n"
        L"  aatnopt.[AidToNavigation], \r\n"
        L"  det.[Device], \r\n"
        L"  mpset.[ProxySession], \r\n"
        L"  mset.[Service], \r\n"
        L"  rastct.[Radar], \r\n"
        L"  rbs1t.[Radar], \r\n"
        L"  rbs2t.[Radar], \r\n"
        L"  reafct.[Radar], \r\n"
        L"  reftct.[Radar], \r\n"
        L"  restct.[Radar], \r\n"
        L"  rpot.[Radar], \r\n"
        L"  rsst.[Radar], \r\n"
        L"  rtt.[Radar], \r\n"
        L"  gats.[GNSSDevice], \r\n"
        L"  glats.[GNSSDevice], \r\n"
        L"  glots.[GNSSDevice], \r\n"
        L"  gct.[GyroDevice], \r\n"
        L"  ghmnt.[GyroDevice], \r\n"
        L"  ghtnt.[GyroDevice], \r\n"
        L"  gpt.[GyroDevice], \r\n"
        L"  grott.[GyroDevice], \r\n"
        L"  grt.[GyroDevice], \r\n"
        L"  gst.[GyroDevice], \r\n"
        L"  rlats.[Radar], \r\n"
        L"  rlots.[Radar], \r\n"
        L"  rdpt.[Radome], \r\n"
        L"  rpt.[Radome], \r\n"
        L"  rtets.[Radome], \r\n"
        L"  vdt.[Vessel], \r\n"
        L"  vlats.[View], \r\n"
        L"  vlots.[View], \r\n"
        L"  vzlt.[View], \r\n"
        L"  wsaht.[WeatherStation], \r\n"
        L"  wsatt.[WeatherStation], \r\n"
        L"  wsbpt.[WeatherStation], \r\n"
        L"  wsdpt.[WeatherStation], \r\n"
        L"  wsrht.[WeatherStation], \r\n"
        L"  wswtt.[WeatherStation], \r\n"
        L"  wswdt.[WeatherStation], \r\n"
        L"  wswst.[WeatherStation], \r\n"
        L"  aatnpt.[AidToNavigation], \r\n"
        L"  raot.[Radar], \r\n"
        L"  rftclt.[Radar], \r\n"
        L"  rftcmt.[Radar], \r\n"
        L"  rapts.[Radar], \r\n"
        L"  rs1et.[Radar], \r\n"
        L"  rs1st.[Radar], \r\n"
        L"  rs2et.[Radar], \r\n"
        L"  rs2st.[Radar], \r\n"
        L"  rstclt.[Radar], \r\n"
        L"  ratuts.[Radar], \r\n"
        L"  vpobt.[Vessel], \r\n"
        L"  rst.[Radome] \r\n"
        L"FROM [TimeseriesCatalogElementView] tce \r\n"
        L"  LEFT JOIN [Timeseries] t ON(tce.[Id] = t.[Id] ) \r\n"
        L"  LEFT JOIN [BinaryTimeseries] bt ON(tce.[Id] = bt.[Id] ) \r\n"
        L"  LEFT JOIN [BooleanTimeseries] bots ON(tce.[Id] = bots.[Id] ) \r\n"
        L"  LEFT JOIN [AisAidToNavigationOffPositionTimeseries] aatnopt ON(tce.[Id] = aatnopt.[Id] ) \r\n"
        L"  LEFT JOIN [DeviceEnabledTimeseries] det ON(tce.[Id] = det.[Id] ) \r\n"
        L"  LEFT JOIN [MediaProxySessionEnabledTimeseries] mpset ON(tce.[Id] = mpset.[Id] ) \r\n"
        L"  LEFT JOIN [MediaServiceEnabledTimeseries] mset ON(tce.[Id] = mset.[Id] ) \r\n"
        L"  LEFT JOIN [RadarAutomaticSensitivityTimeControlTimeseries] rastct ON(tce.[Id] = rastct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarBlankSector1Timeseries] rbs1t ON(tce.[Id] = rbs1t.[Id] ) \r\n"
        L"  LEFT JOIN [RadarBlankSector2Timeseries] rbs2t ON(tce.[Id] = rbs2t.[Id] ) \r\n"
        L"  LEFT JOIN [RadarEnableAutomaticFrequencyControlTimeseries] reafct ON(tce.[Id] = reafct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarEnableFastTimeConstantTimeseries] reftct ON(tce.[Id] = reftct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarEnableSensitivityTimeControlTimeseries] restct ON(tce.[Id] = restct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarPowerOnTimeseries] rpot ON(tce.[Id] = rpot.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSaveSettingsTimeseries] rsst ON(tce.[Id] = rsst.[Id] ) \r\n"
        L"  LEFT JOIN [RadarTrackingTimeseries] rtt ON(tce.[Id] = rtt.[Id] ) \r\n"
        L"  LEFT JOIN [ByteTimeseries] byts ON(tce.[Id] = byts.[Id] ) \r\n"
        L"  LEFT JOIN [DateTimeTimeseries] dtt ON(tce.[Id] = dtt.[Id] ) \r\n"
        L"  LEFT JOIN [DoubleTimeseries] dt ON(tce.[Id] = dt.[Id] ) \r\n"
        L"  LEFT JOIN [GNSSAltitudeTimeseries] gats ON(tce.[Id] = gats.[Id] ) \r\n"
        L"  LEFT JOIN [GNSSLatitudeTimeseries] glats ON(tce.[Id] = glats.[Id] ) \r\n"
        L"  LEFT JOIN [GNSSLongitudeTimeseries] glots ON(tce.[Id] = glots.[Id] ) \r\n"
        L"  LEFT JOIN [GyroCourseTimeseries] gct ON(tce.[Id] = gct.[Id] ) \r\n"
        L"  LEFT JOIN [GyroHeadingMagneticNorthTimeseries] ghmnt ON(tce.[Id] = ghmnt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroHeadingTrueNorthTimeseries] ghtnt ON(tce.[Id] = ghtnt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroPitchTimeseries] gpt ON(tce.[Id] = gpt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroRateOfTurnTimeseries] grott ON(tce.[Id] = grott.[Id] ) \r\n"
        L"  LEFT JOIN [GyroRollTimeseries] grt ON(tce.[Id] = grt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroSpeedTimeseries] gst ON(tce.[Id] = gst.[Id] ) \r\n"
        L"  LEFT JOIN [RadarLatitudeTimeseries] rlats ON(tce.[Id] = rlats.[Id] ) \r\n"
        L"  LEFT JOIN [RadarLongitudeTimeseries] rlots ON(tce.[Id] = rlots.[Id] ) \r\n"
        L"  LEFT JOIN [RadomeDewPointTimeseries] rdpt ON(tce.[Id] = rdpt.[Id] ) \r\n"
        L"  LEFT JOIN [RadomePressureTimeseries] rpt ON(tce.[Id] = rpt.[Id] ) \r\n"
        L"  LEFT JOIN [RadomeTemperatureTimeseries] rtets ON(tce.[Id] = rtets.[Id] ) \r\n"
        L"  LEFT JOIN [VesselDraughtTimeseries] vdt ON(tce.[Id] = vdt.[Id] ) \r\n"
        L"  LEFT JOIN [ViewLatitudeTimeseries] vlats ON(tce.[Id] = vlats.[Id] ) \r\n"
        L"  LEFT JOIN [ViewLongitudeTimeseries] vlots ON(tce.[Id] = vlots.[Id] ) \r\n"
        L"  LEFT JOIN [ViewZoomLevelTimeseries] vzlt ON(tce.[Id] = vzlt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationAbsoluteHumidityTimeseries] wsaht ON(tce.[Id] = wsaht.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationAirTemperatureTimeseries] wsatt ON(tce.[Id] = wsatt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationBarometricPressureTimeseries] wsbpt ON(tce.[Id] = wsbpt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationDewPointTimeseries] wsdpt ON(tce.[Id] = wsdpt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationRelativeHumidityTimeseries] wsrht ON(tce.[Id] = wsrht.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationWaterTemperatureTimeseries] wswtt ON(tce.[Id] = wswtt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationWindDirectionTimeseries] wswdt ON(tce.[Id] = wswdt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationWindSpeedTimeseries] wswst ON(tce.[Id] = wswst.[Id] ) \r\n"
        L"  LEFT JOIN [GeoPosition2DTimeseries] gp2d ON(tce.[Id] = gp2d.[Id] ) \r\n"
        L"  LEFT JOIN [AisAidToNavigationPositionTimeseries] aatnpt ON(tce.[Id] = aatnpt.[Id] ) \r\n"
        L"  LEFT JOIN [GeoPosition3DTimeseries] gp3d ON(tce.[Id] = gp3d.[Id] ) \r\n"
        L"  LEFT JOIN [GuidTimeseries] gt ON(tce.[Id] = gt.[Id] ) \r\n"
        L"  LEFT JOIN [Int16Timeseries] i16t ON(tce.[Id] = i16t.[Id] ) \r\n"
        L"  LEFT JOIN [Int32Timeseries] i32t ON(tce.[Id] = i32t.[Id] ) \r\n"
        L"  LEFT JOIN [RadarAzimuthOffsetTimeseries] raot ON(tce.[Id] = raot.[Id] ) \r\n"
        L"  LEFT JOIN [RadarFastTimeConstantLevelTimeseries] rftclt ON(tce.[Id] = rftclt.[Id] ) \r\n"
        L"  LEFT JOIN [RadarFastTimeConstantModeTimeseries] rftcmt ON(tce.[Id] = rftcmt.[Id] ) \r\n"
        L"  LEFT JOIN [RadarPulseTimeseries] rapts ON(tce.[Id] = rapts.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector1EndTimeseries] rs1et ON(tce.[Id] = rs1et.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector1StartTimeseries] rs1st ON(tce.[Id] = rs1st.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector2EndTimeseries] rs2et ON(tce.[Id] = rs2et.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector2StartTimeseries] rs2st ON(tce.[Id] = rs2st.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSensitivityTimeControlLevelTimeseries] rstclt ON(tce.[Id] = rstclt.[Id] ) \r\n"
        L"  LEFT JOIN [RadarTuningTimeseries] ratuts ON(tce.[Id] = ratuts.[Id] ) \r\n"
        L"  LEFT JOIN [VesselPersonsOnBoardTimeseries] vpobt ON(tce.[Id] = vpobt.[Id] ) \r\n"
        L"  LEFT JOIN [Int64Timeseries] i64t ON(tce.[Id] = i64t.[Id] ) \r\n"
        L"  LEFT JOIN [Position2DTimeseries] p2d ON(tce.[Id] = p2d.[Id] ) \r\n"
        L"  LEFT JOIN [Position3DTimeseries] p3d ON(tce.[Id] = p3d.[Id] ) \r\n"
        L"  LEFT JOIN [ReferenceTimeseries] rt ON(tce.[Id] = rt.[Id] ) \r\n"
        L"  LEFT JOIN [SByteTimeseries] st ON(tce.[Id] = st.[Id] ) \r\n"
        L"  LEFT JOIN [SingleTimeseries] sits ON(tce.[Id] = sits.[Id] ) \r\n"
        L"  LEFT JOIN [StringTimeseries] stts ON(tce.[Id] = stts.[Id] ) \r\n"
        L"  LEFT JOIN [TimeSpanTimeseries] tst ON(tce.[Id] = tst.[Id] ) \r\n"
        L"  LEFT JOIN [UInt16Timeseries] u16t ON(tce.[Id] = u16t.[Id] ) \r\n"
        L"  LEFT JOIN [UInt32Timeseries] u32t ON(tce.[Id] = u32t.[Id] ) \r\n"
        L"  LEFT JOIN [RadomeStatusTimeseries] rst ON(tce.[Id] = rst.[Id] ) \r\n"
        L"  LEFT JOIN [UInt64Timeseries] u64t ON(tce.[Id] = u64t.[Id] ) \r\n"
        L"  LEFT JOIN [TimeseriesCatalog] tc ON(tce.[Id] = tc.[Id] )";
    WideString ComplexTimeseriesCatalogElementColumnData::BaseViewName = L"TimeseriesCatalogElementView";
    WideString ComplexTimeseriesCatalogElementColumnData::ViewAliasName = L"tce";

    void ComplexTimeseriesCatalogElementColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, TCE_ID_FIELD_ID, id_ );
        Bind( statement, TCE_KIND_FIELD_ID, kind_ );
        Bind( statement, TCE_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, TCE_CATALOG_FIELD_ID, catalog_ );
        Bind( statement, TCE_NAME_FIELD_ID, name_ );
        Bind( statement, T_MAXRETENTION_FIELD_ID, tMaxRetention_ );
        Bind( statement, AATNOPT_AIDTONAVIGATION_FIELD_ID, aatnoptAidToNavigation_ );
        Bind( statement, DET_DEVICE_FIELD_ID, detDevice_ );
        Bind( statement, MPSET_PROXYSESSION_FIELD_ID, mpsetProxySession_ );
        Bind( statement, MSET_SERVICE_FIELD_ID, msetService_ );
        Bind( statement, RASTCT_RADAR_FIELD_ID, rastctRadar_ );
        Bind( statement, RBS1T_RADAR_FIELD_ID, rbs1tRadar_ );
        Bind( statement, RBS2T_RADAR_FIELD_ID, rbs2tRadar_ );
        Bind( statement, REAFCT_RADAR_FIELD_ID, reafctRadar_ );
        Bind( statement, REFTCT_RADAR_FIELD_ID, reftctRadar_ );
        Bind( statement, RESTCT_RADAR_FIELD_ID, restctRadar_ );
        Bind( statement, RPOT_RADAR_FIELD_ID, rpotRadar_ );
        Bind( statement, RSST_RADAR_FIELD_ID, rsstRadar_ );
        Bind( statement, RTT_RADAR_FIELD_ID, rttRadar_ );
        Bind( statement, GATS_GNSSDEVICE_FIELD_ID, gatsGNSSDevice_ );
        Bind( statement, GLATS_GNSSDEVICE_FIELD_ID, glatsGNSSDevice_ );
        Bind( statement, GLOTS_GNSSDEVICE_FIELD_ID, glotsGNSSDevice_ );
        Bind( statement, GCT_GYRODEVICE_FIELD_ID, gctGyroDevice_ );
        Bind( statement, GHMNT_GYRODEVICE_FIELD_ID, ghmntGyroDevice_ );
        Bind( statement, GHTNT_GYRODEVICE_FIELD_ID, ghtntGyroDevice_ );
        Bind( statement, GPT_GYRODEVICE_FIELD_ID, gptGyroDevice_ );
        Bind( statement, GROTT_GYRODEVICE_FIELD_ID, grottGyroDevice_ );
        Bind( statement, GRT_GYRODEVICE_FIELD_ID, grtGyroDevice_ );
        Bind( statement, GST_GYRODEVICE_FIELD_ID, gstGyroDevice_ );
        Bind( statement, RLATS_RADAR_FIELD_ID, rlatsRadar_ );
        Bind( statement, RLOTS_RADAR_FIELD_ID, rlotsRadar_ );
        Bind( statement, RDPT_RADOME_FIELD_ID, rdptRadome_ );
        Bind( statement, RPT_RADOME_FIELD_ID, rptRadome_ );
        Bind( statement, RTETS_RADOME_FIELD_ID, rtetsRadome_ );
        Bind( statement, VDT_VESSEL_FIELD_ID, vdtVessel_ );
        Bind( statement, VLATS_VIEW_FIELD_ID, vlatsView_ );
        Bind( statement, VLOTS_VIEW_FIELD_ID, vlotsView_ );
        Bind( statement, VZLT_VIEW_FIELD_ID, vzltView_ );
        Bind( statement, WSAHT_WEATHERSTATION_FIELD_ID, wsahtWeatherStation_ );
        Bind( statement, WSATT_WEATHERSTATION_FIELD_ID, wsattWeatherStation_ );
        Bind( statement, WSBPT_WEATHERSTATION_FIELD_ID, wsbptWeatherStation_ );
        Bind( statement, WSDPT_WEATHERSTATION_FIELD_ID, wsdptWeatherStation_ );
        Bind( statement, WSRHT_WEATHERSTATION_FIELD_ID, wsrhtWeatherStation_ );
        Bind( statement, WSWTT_WEATHERSTATION_FIELD_ID, wswttWeatherStation_ );
        Bind( statement, WSWDT_WEATHERSTATION_FIELD_ID, wswdtWeatherStation_ );
        Bind( statement, WSWST_WEATHERSTATION_FIELD_ID, wswstWeatherStation_ );
        Bind( statement, AATNPT_AIDTONAVIGATION_FIELD_ID, aatnptAidToNavigation_ );
        Bind( statement, RAOT_RADAR_FIELD_ID, raotRadar_ );
        Bind( statement, RFTCLT_RADAR_FIELD_ID, rftcltRadar_ );
        Bind( statement, RFTCMT_RADAR_FIELD_ID, rftcmtRadar_ );
        Bind( statement, RAPTS_RADAR_FIELD_ID, raptsRadar_ );
        Bind( statement, RS1ET_RADAR_FIELD_ID, rs1etRadar_ );
        Bind( statement, RS1ST_RADAR_FIELD_ID, rs1stRadar_ );
        Bind( statement, RS2ET_RADAR_FIELD_ID, rs2etRadar_ );
        Bind( statement, RS2ST_RADAR_FIELD_ID, rs2stRadar_ );
        Bind( statement, RSTCLT_RADAR_FIELD_ID, rstcltRadar_ );
        Bind( statement, RATUTS_RADAR_FIELD_ID, ratutsRadar_ );
        Bind( statement, VPOBT_VESSEL_FIELD_ID, vpobtVessel_ );
        Bind( statement, RST_RADOME_FIELD_ID, rstRadome_ );
    }


    WideString ComplexTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  t.[Id], \r\n"
        L"  t.[EntityType], \r\n"
        L"  t.[RowVersion], \r\n"
        L"  t.[Catalog], \r\n"
        L"  t.[Name], \r\n"
        L"  t.[MaxRetention], \r\n"
        L"  aatnopt.[AidToNavigation], \r\n"
        L"  det.[Device], \r\n"
        L"  mpset.[ProxySession], \r\n"
        L"  mset.[Service], \r\n"
        L"  rastct.[Radar], \r\n"
        L"  rbs1t.[Radar], \r\n"
        L"  rbs2t.[Radar], \r\n"
        L"  reafct.[Radar], \r\n"
        L"  reftct.[Radar], \r\n"
        L"  restct.[Radar], \r\n"
        L"  rpot.[Radar], \r\n"
        L"  rsst.[Radar], \r\n"
        L"  rtt.[Radar], \r\n"
        L"  gats.[GNSSDevice], \r\n"
        L"  glats.[GNSSDevice], \r\n"
        L"  glots.[GNSSDevice], \r\n"
        L"  gct.[GyroDevice], \r\n"
        L"  ghmnt.[GyroDevice], \r\n"
        L"  ghtnt.[GyroDevice], \r\n"
        L"  gpt.[GyroDevice], \r\n"
        L"  grott.[GyroDevice], \r\n"
        L"  grt.[GyroDevice], \r\n"
        L"  gst.[GyroDevice], \r\n"
        L"  rlats.[Radar], \r\n"
        L"  rlots.[Radar], \r\n"
        L"  rdpt.[Radome], \r\n"
        L"  rpt.[Radome], \r\n"
        L"  rtets.[Radome], \r\n"
        L"  vdt.[Vessel], \r\n"
        L"  vlats.[View], \r\n"
        L"  vlots.[View], \r\n"
        L"  vzlt.[View], \r\n"
        L"  wsaht.[WeatherStation], \r\n"
        L"  wsatt.[WeatherStation], \r\n"
        L"  wsbpt.[WeatherStation], \r\n"
        L"  wsdpt.[WeatherStation], \r\n"
        L"  wsrht.[WeatherStation], \r\n"
        L"  wswtt.[WeatherStation], \r\n"
        L"  wswdt.[WeatherStation], \r\n"
        L"  wswst.[WeatherStation], \r\n"
        L"  aatnpt.[AidToNavigation], \r\n"
        L"  raot.[Radar], \r\n"
        L"  rftclt.[Radar], \r\n"
        L"  rftcmt.[Radar], \r\n"
        L"  rapts.[Radar], \r\n"
        L"  rs1et.[Radar], \r\n"
        L"  rs1st.[Radar], \r\n"
        L"  rs2et.[Radar], \r\n"
        L"  rs2st.[Radar], \r\n"
        L"  rstclt.[Radar], \r\n"
        L"  ratuts.[Radar], \r\n"
        L"  vpobt.[Vessel], \r\n"
        L"  rst.[Radome] \r\n"
        L"FROM [TimeseriesView] t \r\n"
        L"  LEFT JOIN [BinaryTimeseries] bt ON(t.[Id] = bt.[Id] ) \r\n"
        L"  LEFT JOIN [BooleanTimeseries] bots ON(t.[Id] = bots.[Id] ) \r\n"
        L"  LEFT JOIN [AisAidToNavigationOffPositionTimeseries] aatnopt ON(t.[Id] = aatnopt.[Id] ) \r\n"
        L"  LEFT JOIN [DeviceEnabledTimeseries] det ON(t.[Id] = det.[Id] ) \r\n"
        L"  LEFT JOIN [MediaProxySessionEnabledTimeseries] mpset ON(t.[Id] = mpset.[Id] ) \r\n"
        L"  LEFT JOIN [MediaServiceEnabledTimeseries] mset ON(t.[Id] = mset.[Id] ) \r\n"
        L"  LEFT JOIN [RadarAutomaticSensitivityTimeControlTimeseries] rastct ON(t.[Id] = rastct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarBlankSector1Timeseries] rbs1t ON(t.[Id] = rbs1t.[Id] ) \r\n"
        L"  LEFT JOIN [RadarBlankSector2Timeseries] rbs2t ON(t.[Id] = rbs2t.[Id] ) \r\n"
        L"  LEFT JOIN [RadarEnableAutomaticFrequencyControlTimeseries] reafct ON(t.[Id] = reafct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarEnableFastTimeConstantTimeseries] reftct ON(t.[Id] = reftct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarEnableSensitivityTimeControlTimeseries] restct ON(t.[Id] = restct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarPowerOnTimeseries] rpot ON(t.[Id] = rpot.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSaveSettingsTimeseries] rsst ON(t.[Id] = rsst.[Id] ) \r\n"
        L"  LEFT JOIN [RadarTrackingTimeseries] rtt ON(t.[Id] = rtt.[Id] ) \r\n"
        L"  LEFT JOIN [ByteTimeseries] byts ON(t.[Id] = byts.[Id] ) \r\n"
        L"  LEFT JOIN [DateTimeTimeseries] dtt ON(t.[Id] = dtt.[Id] ) \r\n"
        L"  LEFT JOIN [DoubleTimeseries] dt ON(t.[Id] = dt.[Id] ) \r\n"
        L"  LEFT JOIN [GNSSAltitudeTimeseries] gats ON(t.[Id] = gats.[Id] ) \r\n"
        L"  LEFT JOIN [GNSSLatitudeTimeseries] glats ON(t.[Id] = glats.[Id] ) \r\n"
        L"  LEFT JOIN [GNSSLongitudeTimeseries] glots ON(t.[Id] = glots.[Id] ) \r\n"
        L"  LEFT JOIN [GyroCourseTimeseries] gct ON(t.[Id] = gct.[Id] ) \r\n"
        L"  LEFT JOIN [GyroHeadingMagneticNorthTimeseries] ghmnt ON(t.[Id] = ghmnt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroHeadingTrueNorthTimeseries] ghtnt ON(t.[Id] = ghtnt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroPitchTimeseries] gpt ON(t.[Id] = gpt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroRateOfTurnTimeseries] grott ON(t.[Id] = grott.[Id] ) \r\n"
        L"  LEFT JOIN [GyroRollTimeseries] grt ON(t.[Id] = grt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroSpeedTimeseries] gst ON(t.[Id] = gst.[Id] ) \r\n"
        L"  LEFT JOIN [RadarLatitudeTimeseries] rlats ON(t.[Id] = rlats.[Id] ) \r\n"
        L"  LEFT JOIN [RadarLongitudeTimeseries] rlots ON(t.[Id] = rlots.[Id] ) \r\n"
        L"  LEFT JOIN [RadomeDewPointTimeseries] rdpt ON(t.[Id] = rdpt.[Id] ) \r\n"
        L"  LEFT JOIN [RadomePressureTimeseries] rpt ON(t.[Id] = rpt.[Id] ) \r\n"
        L"  LEFT JOIN [RadomeTemperatureTimeseries] rtets ON(t.[Id] = rtets.[Id] ) \r\n"
        L"  LEFT JOIN [VesselDraughtTimeseries] vdt ON(t.[Id] = vdt.[Id] ) \r\n"
        L"  LEFT JOIN [ViewLatitudeTimeseries] vlats ON(t.[Id] = vlats.[Id] ) \r\n"
        L"  LEFT JOIN [ViewLongitudeTimeseries] vlots ON(t.[Id] = vlots.[Id] ) \r\n"
        L"  LEFT JOIN [ViewZoomLevelTimeseries] vzlt ON(t.[Id] = vzlt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationAbsoluteHumidityTimeseries] wsaht ON(t.[Id] = wsaht.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationAirTemperatureTimeseries] wsatt ON(t.[Id] = wsatt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationBarometricPressureTimeseries] wsbpt ON(t.[Id] = wsbpt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationDewPointTimeseries] wsdpt ON(t.[Id] = wsdpt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationRelativeHumidityTimeseries] wsrht ON(t.[Id] = wsrht.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationWaterTemperatureTimeseries] wswtt ON(t.[Id] = wswtt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationWindDirectionTimeseries] wswdt ON(t.[Id] = wswdt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationWindSpeedTimeseries] wswst ON(t.[Id] = wswst.[Id] ) \r\n"
        L"  LEFT JOIN [GeoPosition2DTimeseries] gp2d ON(t.[Id] = gp2d.[Id] ) \r\n"
        L"  LEFT JOIN [AisAidToNavigationPositionTimeseries] aatnpt ON(t.[Id] = aatnpt.[Id] ) \r\n"
        L"  LEFT JOIN [GeoPosition3DTimeseries] gp3d ON(t.[Id] = gp3d.[Id] ) \r\n"
        L"  LEFT JOIN [GuidTimeseries] gt ON(t.[Id] = gt.[Id] ) \r\n"
        L"  LEFT JOIN [Int16Timeseries] i16t ON(t.[Id] = i16t.[Id] ) \r\n"
        L"  LEFT JOIN [Int32Timeseries] i32t ON(t.[Id] = i32t.[Id] ) \r\n"
        L"  LEFT JOIN [RadarAzimuthOffsetTimeseries] raot ON(t.[Id] = raot.[Id] ) \r\n"
        L"  LEFT JOIN [RadarFastTimeConstantLevelTimeseries] rftclt ON(t.[Id] = rftclt.[Id] ) \r\n"
        L"  LEFT JOIN [RadarFastTimeConstantModeTimeseries] rftcmt ON(t.[Id] = rftcmt.[Id] ) \r\n"
        L"  LEFT JOIN [RadarPulseTimeseries] rapts ON(t.[Id] = rapts.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector1EndTimeseries] rs1et ON(t.[Id] = rs1et.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector1StartTimeseries] rs1st ON(t.[Id] = rs1st.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector2EndTimeseries] rs2et ON(t.[Id] = rs2et.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector2StartTimeseries] rs2st ON(t.[Id] = rs2st.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSensitivityTimeControlLevelTimeseries] rstclt ON(t.[Id] = rstclt.[Id] ) \r\n"
        L"  LEFT JOIN [RadarTuningTimeseries] ratuts ON(t.[Id] = ratuts.[Id] ) \r\n"
        L"  LEFT JOIN [VesselPersonsOnBoardTimeseries] vpobt ON(t.[Id] = vpobt.[Id] ) \r\n"
        L"  LEFT JOIN [Int64Timeseries] i64t ON(t.[Id] = i64t.[Id] ) \r\n"
        L"  LEFT JOIN [Position2DTimeseries] p2d ON(t.[Id] = p2d.[Id] ) \r\n"
        L"  LEFT JOIN [Position3DTimeseries] p3d ON(t.[Id] = p3d.[Id] ) \r\n"
        L"  LEFT JOIN [ReferenceTimeseries] rt ON(t.[Id] = rt.[Id] ) \r\n"
        L"  LEFT JOIN [SByteTimeseries] st ON(t.[Id] = st.[Id] ) \r\n"
        L"  LEFT JOIN [SingleTimeseries] sits ON(t.[Id] = sits.[Id] ) \r\n"
        L"  LEFT JOIN [StringTimeseries] stts ON(t.[Id] = stts.[Id] ) \r\n"
        L"  LEFT JOIN [TimeSpanTimeseries] tst ON(t.[Id] = tst.[Id] ) \r\n"
        L"  LEFT JOIN [UInt16Timeseries] u16t ON(t.[Id] = u16t.[Id] ) \r\n"
        L"  LEFT JOIN [UInt32Timeseries] u32t ON(t.[Id] = u32t.[Id] ) \r\n"
        L"  LEFT JOIN [RadomeStatusTimeseries] rst ON(t.[Id] = rst.[Id] ) \r\n"
        L"  LEFT JOIN [UInt64Timeseries] u64t ON(t.[Id] = u64t.[Id] )";
    WideString ComplexTimeseriesColumnData::BaseViewName = L"TimeseriesView";
    WideString ComplexTimeseriesColumnData::ViewAliasName = L"t";

    void ComplexTimeseriesColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, T_ID_FIELD_ID, id_ );
        Bind( statement, T_KIND_FIELD_ID, kind_ );
        Bind( statement, T_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, T_CATALOG_FIELD_ID, catalog_ );
        Bind( statement, T_NAME_FIELD_ID, name_ );
        Bind( statement, T_MAXRETENTION_FIELD_ID, maxRetention_ );
        Bind( statement, AATNOPT_AIDTONAVIGATION_FIELD_ID, aatnoptAidToNavigation_ );
        Bind( statement, DET_DEVICE_FIELD_ID, detDevice_ );
        Bind( statement, MPSET_PROXYSESSION_FIELD_ID, mpsetProxySession_ );
        Bind( statement, MSET_SERVICE_FIELD_ID, msetService_ );
        Bind( statement, RASTCT_RADAR_FIELD_ID, rastctRadar_ );
        Bind( statement, RBS1T_RADAR_FIELD_ID, rbs1tRadar_ );
        Bind( statement, RBS2T_RADAR_FIELD_ID, rbs2tRadar_ );
        Bind( statement, REAFCT_RADAR_FIELD_ID, reafctRadar_ );
        Bind( statement, REFTCT_RADAR_FIELD_ID, reftctRadar_ );
        Bind( statement, RESTCT_RADAR_FIELD_ID, restctRadar_ );
        Bind( statement, RPOT_RADAR_FIELD_ID, rpotRadar_ );
        Bind( statement, RSST_RADAR_FIELD_ID, rsstRadar_ );
        Bind( statement, RTT_RADAR_FIELD_ID, rttRadar_ );
        Bind( statement, GATS_GNSSDEVICE_FIELD_ID, gatsGNSSDevice_ );
        Bind( statement, GLATS_GNSSDEVICE_FIELD_ID, glatsGNSSDevice_ );
        Bind( statement, GLOTS_GNSSDEVICE_FIELD_ID, glotsGNSSDevice_ );
        Bind( statement, GCT_GYRODEVICE_FIELD_ID, gctGyroDevice_ );
        Bind( statement, GHMNT_GYRODEVICE_FIELD_ID, ghmntGyroDevice_ );
        Bind( statement, GHTNT_GYRODEVICE_FIELD_ID, ghtntGyroDevice_ );
        Bind( statement, GPT_GYRODEVICE_FIELD_ID, gptGyroDevice_ );
        Bind( statement, GROTT_GYRODEVICE_FIELD_ID, grottGyroDevice_ );
        Bind( statement, GRT_GYRODEVICE_FIELD_ID, grtGyroDevice_ );
        Bind( statement, GST_GYRODEVICE_FIELD_ID, gstGyroDevice_ );
        Bind( statement, RLATS_RADAR_FIELD_ID, rlatsRadar_ );
        Bind( statement, RLOTS_RADAR_FIELD_ID, rlotsRadar_ );
        Bind( statement, RDPT_RADOME_FIELD_ID, rdptRadome_ );
        Bind( statement, RPT_RADOME_FIELD_ID, rptRadome_ );
        Bind( statement, RTETS_RADOME_FIELD_ID, rtetsRadome_ );
        Bind( statement, VDT_VESSEL_FIELD_ID, vdtVessel_ );
        Bind( statement, VLATS_VIEW_FIELD_ID, vlatsView_ );
        Bind( statement, VLOTS_VIEW_FIELD_ID, vlotsView_ );
        Bind( statement, VZLT_VIEW_FIELD_ID, vzltView_ );
        Bind( statement, WSAHT_WEATHERSTATION_FIELD_ID, wsahtWeatherStation_ );
        Bind( statement, WSATT_WEATHERSTATION_FIELD_ID, wsattWeatherStation_ );
        Bind( statement, WSBPT_WEATHERSTATION_FIELD_ID, wsbptWeatherStation_ );
        Bind( statement, WSDPT_WEATHERSTATION_FIELD_ID, wsdptWeatherStation_ );
        Bind( statement, WSRHT_WEATHERSTATION_FIELD_ID, wsrhtWeatherStation_ );
        Bind( statement, WSWTT_WEATHERSTATION_FIELD_ID, wswttWeatherStation_ );
        Bind( statement, WSWDT_WEATHERSTATION_FIELD_ID, wswdtWeatherStation_ );
        Bind( statement, WSWST_WEATHERSTATION_FIELD_ID, wswstWeatherStation_ );
        Bind( statement, AATNPT_AIDTONAVIGATION_FIELD_ID, aatnptAidToNavigation_ );
        Bind( statement, RAOT_RADAR_FIELD_ID, raotRadar_ );
        Bind( statement, RFTCLT_RADAR_FIELD_ID, rftcltRadar_ );
        Bind( statement, RFTCMT_RADAR_FIELD_ID, rftcmtRadar_ );
        Bind( statement, RAPTS_RADAR_FIELD_ID, raptsRadar_ );
        Bind( statement, RS1ET_RADAR_FIELD_ID, rs1etRadar_ );
        Bind( statement, RS1ST_RADAR_FIELD_ID, rs1stRadar_ );
        Bind( statement, RS2ET_RADAR_FIELD_ID, rs2etRadar_ );
        Bind( statement, RS2ST_RADAR_FIELD_ID, rs2stRadar_ );
        Bind( statement, RSTCLT_RADAR_FIELD_ID, rstcltRadar_ );
        Bind( statement, RATUTS_RADAR_FIELD_ID, ratutsRadar_ );
        Bind( statement, VPOBT_VESSEL_FIELD_ID, vpobtVessel_ );
        Bind( statement, RST_RADOME_FIELD_ID, rstRadome_ );
    }


    WideString ComplexBooleanTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  bots.[Id], \r\n"
        L"  bots.[EntityType], \r\n"
        L"  bots.[RowVersion], \r\n"
        L"  bots.[Catalog], \r\n"
        L"  bots.[Name], \r\n"
        L"  bots.[MaxRetention], \r\n"
        L"  aatnopt.[AidToNavigation], \r\n"
        L"  det.[Device], \r\n"
        L"  mpset.[ProxySession], \r\n"
        L"  mset.[Service], \r\n"
        L"  rastct.[Radar], \r\n"
        L"  rbs1t.[Radar], \r\n"
        L"  rbs2t.[Radar], \r\n"
        L"  reafct.[Radar], \r\n"
        L"  reftct.[Radar], \r\n"
        L"  restct.[Radar], \r\n"
        L"  rpot.[Radar], \r\n"
        L"  rsst.[Radar], \r\n"
        L"  rtt.[Radar] \r\n"
        L"FROM [BooleanTimeseriesView] bots \r\n"
        L"  LEFT JOIN [AisAidToNavigationOffPositionTimeseries] aatnopt ON(bots.[Id] = aatnopt.[Id] ) \r\n"
        L"  LEFT JOIN [DeviceEnabledTimeseries] det ON(bots.[Id] = det.[Id] ) \r\n"
        L"  LEFT JOIN [MediaProxySessionEnabledTimeseries] mpset ON(bots.[Id] = mpset.[Id] ) \r\n"
        L"  LEFT JOIN [MediaServiceEnabledTimeseries] mset ON(bots.[Id] = mset.[Id] ) \r\n"
        L"  LEFT JOIN [RadarAutomaticSensitivityTimeControlTimeseries] rastct ON(bots.[Id] = rastct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarBlankSector1Timeseries] rbs1t ON(bots.[Id] = rbs1t.[Id] ) \r\n"
        L"  LEFT JOIN [RadarBlankSector2Timeseries] rbs2t ON(bots.[Id] = rbs2t.[Id] ) \r\n"
        L"  LEFT JOIN [RadarEnableAutomaticFrequencyControlTimeseries] reafct ON(bots.[Id] = reafct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarEnableFastTimeConstantTimeseries] reftct ON(bots.[Id] = reftct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarEnableSensitivityTimeControlTimeseries] restct ON(bots.[Id] = restct.[Id] ) \r\n"
        L"  LEFT JOIN [RadarPowerOnTimeseries] rpot ON(bots.[Id] = rpot.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSaveSettingsTimeseries] rsst ON(bots.[Id] = rsst.[Id] ) \r\n"
        L"  LEFT JOIN [RadarTrackingTimeseries] rtt ON(bots.[Id] = rtt.[Id] )";
    WideString ComplexBooleanTimeseriesColumnData::BaseViewName = L"BooleanTimeseriesView";
    WideString ComplexBooleanTimeseriesColumnData::ViewAliasName = L"bots";

    void ComplexBooleanTimeseriesColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, BOTS_ID_FIELD_ID, id_ );
        Bind( statement, BOTS_KIND_FIELD_ID, kind_ );
        Bind( statement, BOTS_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, BOTS_CATALOG_FIELD_ID, catalog_ );
        Bind( statement, BOTS_NAME_FIELD_ID, name_ );
        Bind( statement, BOTS_MAXRETENTION_FIELD_ID, maxRetention_ );
        Bind( statement, AATNOPT_AIDTONAVIGATION_FIELD_ID, aatnoptAidToNavigation_ );
        Bind( statement, DET_DEVICE_FIELD_ID, detDevice_ );
        Bind( statement, MPSET_PROXYSESSION_FIELD_ID, mpsetProxySession_ );
        Bind( statement, MSET_SERVICE_FIELD_ID, msetService_ );
        Bind( statement, RASTCT_RADAR_FIELD_ID, rastctRadar_ );
        Bind( statement, RBS1T_RADAR_FIELD_ID, rbs1tRadar_ );
        Bind( statement, RBS2T_RADAR_FIELD_ID, rbs2tRadar_ );
        Bind( statement, REAFCT_RADAR_FIELD_ID, reafctRadar_ );
        Bind( statement, REFTCT_RADAR_FIELD_ID, reftctRadar_ );
        Bind( statement, RESTCT_RADAR_FIELD_ID, restctRadar_ );
        Bind( statement, RPOT_RADAR_FIELD_ID, rpotRadar_ );
        Bind( statement, RSST_RADAR_FIELD_ID, rsstRadar_ );
        Bind( statement, RTT_RADAR_FIELD_ID, rttRadar_ );
    }


    WideString ComplexDoubleTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  dt.[Id], \r\n"
        L"  dt.[EntityType], \r\n"
        L"  dt.[RowVersion], \r\n"
        L"  dt.[Catalog], \r\n"
        L"  dt.[Name], \r\n"
        L"  dt.[MaxRetention], \r\n"
        L"  gats.[GNSSDevice], \r\n"
        L"  glats.[GNSSDevice], \r\n"
        L"  glots.[GNSSDevice], \r\n"
        L"  gct.[GyroDevice], \r\n"
        L"  ghmnt.[GyroDevice], \r\n"
        L"  ghtnt.[GyroDevice], \r\n"
        L"  gpt.[GyroDevice], \r\n"
        L"  grott.[GyroDevice], \r\n"
        L"  grt.[GyroDevice], \r\n"
        L"  gst.[GyroDevice], \r\n"
        L"  rlats.[Radar], \r\n"
        L"  rlots.[Radar], \r\n"
        L"  rdpt.[Radome], \r\n"
        L"  rpt.[Radome], \r\n"
        L"  rtets.[Radome], \r\n"
        L"  vdt.[Vessel], \r\n"
        L"  vlats.[View], \r\n"
        L"  vlots.[View], \r\n"
        L"  vzlt.[View], \r\n"
        L"  wsaht.[WeatherStation], \r\n"
        L"  wsatt.[WeatherStation], \r\n"
        L"  wsbpt.[WeatherStation], \r\n"
        L"  wsdpt.[WeatherStation], \r\n"
        L"  wsrht.[WeatherStation], \r\n"
        L"  wswtt.[WeatherStation], \r\n"
        L"  wswdt.[WeatherStation], \r\n"
        L"  wswst.[WeatherStation] \r\n"
        L"FROM [DoubleTimeseriesView] dt \r\n"
        L"  LEFT JOIN [GNSSAltitudeTimeseries] gats ON(dt.[Id] = gats.[Id] ) \r\n"
        L"  LEFT JOIN [GNSSLatitudeTimeseries] glats ON(dt.[Id] = glats.[Id] ) \r\n"
        L"  LEFT JOIN [GNSSLongitudeTimeseries] glots ON(dt.[Id] = glots.[Id] ) \r\n"
        L"  LEFT JOIN [GyroCourseTimeseries] gct ON(dt.[Id] = gct.[Id] ) \r\n"
        L"  LEFT JOIN [GyroHeadingMagneticNorthTimeseries] ghmnt ON(dt.[Id] = ghmnt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroHeadingTrueNorthTimeseries] ghtnt ON(dt.[Id] = ghtnt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroPitchTimeseries] gpt ON(dt.[Id] = gpt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroRateOfTurnTimeseries] grott ON(dt.[Id] = grott.[Id] ) \r\n"
        L"  LEFT JOIN [GyroRollTimeseries] grt ON(dt.[Id] = grt.[Id] ) \r\n"
        L"  LEFT JOIN [GyroSpeedTimeseries] gst ON(dt.[Id] = gst.[Id] ) \r\n"
        L"  LEFT JOIN [RadarLatitudeTimeseries] rlats ON(dt.[Id] = rlats.[Id] ) \r\n"
        L"  LEFT JOIN [RadarLongitudeTimeseries] rlots ON(dt.[Id] = rlots.[Id] ) \r\n"
        L"  LEFT JOIN [RadomeDewPointTimeseries] rdpt ON(dt.[Id] = rdpt.[Id] ) \r\n"
        L"  LEFT JOIN [RadomePressureTimeseries] rpt ON(dt.[Id] = rpt.[Id] ) \r\n"
        L"  LEFT JOIN [RadomeTemperatureTimeseries] rtets ON(dt.[Id] = rtets.[Id] ) \r\n"
        L"  LEFT JOIN [VesselDraughtTimeseries] vdt ON(dt.[Id] = vdt.[Id] ) \r\n"
        L"  LEFT JOIN [ViewLatitudeTimeseries] vlats ON(dt.[Id] = vlats.[Id] ) \r\n"
        L"  LEFT JOIN [ViewLongitudeTimeseries] vlots ON(dt.[Id] = vlots.[Id] ) \r\n"
        L"  LEFT JOIN [ViewZoomLevelTimeseries] vzlt ON(dt.[Id] = vzlt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationAbsoluteHumidityTimeseries] wsaht ON(dt.[Id] = wsaht.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationAirTemperatureTimeseries] wsatt ON(dt.[Id] = wsatt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationBarometricPressureTimeseries] wsbpt ON(dt.[Id] = wsbpt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationDewPointTimeseries] wsdpt ON(dt.[Id] = wsdpt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationRelativeHumidityTimeseries] wsrht ON(dt.[Id] = wsrht.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationWaterTemperatureTimeseries] wswtt ON(dt.[Id] = wswtt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationWindDirectionTimeseries] wswdt ON(dt.[Id] = wswdt.[Id] ) \r\n"
        L"  LEFT JOIN [WeatherStationWindSpeedTimeseries] wswst ON(dt.[Id] = wswst.[Id] )";
    WideString ComplexDoubleTimeseriesColumnData::BaseViewName = L"DoubleTimeseriesView";
    WideString ComplexDoubleTimeseriesColumnData::ViewAliasName = L"dt";

    void ComplexDoubleTimeseriesColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, DT_ID_FIELD_ID, id_ );
        Bind( statement, DT_KIND_FIELD_ID, kind_ );
        Bind( statement, DT_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, DT_CATALOG_FIELD_ID, catalog_ );
        Bind( statement, DT_NAME_FIELD_ID, name_ );
        Bind( statement, DT_MAXRETENTION_FIELD_ID, maxRetention_ );
        Bind( statement, GATS_GNSSDEVICE_FIELD_ID, gatsGNSSDevice_ );
        Bind( statement, GLATS_GNSSDEVICE_FIELD_ID, glatsGNSSDevice_ );
        Bind( statement, GLOTS_GNSSDEVICE_FIELD_ID, glotsGNSSDevice_ );
        Bind( statement, GCT_GYRODEVICE_FIELD_ID, gctGyroDevice_ );
        Bind( statement, GHMNT_GYRODEVICE_FIELD_ID, ghmntGyroDevice_ );
        Bind( statement, GHTNT_GYRODEVICE_FIELD_ID, ghtntGyroDevice_ );
        Bind( statement, GPT_GYRODEVICE_FIELD_ID, gptGyroDevice_ );
        Bind( statement, GROTT_GYRODEVICE_FIELD_ID, grottGyroDevice_ );
        Bind( statement, GRT_GYRODEVICE_FIELD_ID, grtGyroDevice_ );
        Bind( statement, GST_GYRODEVICE_FIELD_ID, gstGyroDevice_ );
        Bind( statement, RLATS_RADAR_FIELD_ID, rlatsRadar_ );
        Bind( statement, RLOTS_RADAR_FIELD_ID, rlotsRadar_ );
        Bind( statement, RDPT_RADOME_FIELD_ID, rdptRadome_ );
        Bind( statement, RPT_RADOME_FIELD_ID, rptRadome_ );
        Bind( statement, RTETS_RADOME_FIELD_ID, rtetsRadome_ );
        Bind( statement, VDT_VESSEL_FIELD_ID, vdtVessel_ );
        Bind( statement, VLATS_VIEW_FIELD_ID, vlatsView_ );
        Bind( statement, VLOTS_VIEW_FIELD_ID, vlotsView_ );
        Bind( statement, VZLT_VIEW_FIELD_ID, vzltView_ );
        Bind( statement, WSAHT_WEATHERSTATION_FIELD_ID, wsahtWeatherStation_ );
        Bind( statement, WSATT_WEATHERSTATION_FIELD_ID, wsattWeatherStation_ );
        Bind( statement, WSBPT_WEATHERSTATION_FIELD_ID, wsbptWeatherStation_ );
        Bind( statement, WSDPT_WEATHERSTATION_FIELD_ID, wsdptWeatherStation_ );
        Bind( statement, WSRHT_WEATHERSTATION_FIELD_ID, wsrhtWeatherStation_ );
        Bind( statement, WSWTT_WEATHERSTATION_FIELD_ID, wswttWeatherStation_ );
        Bind( statement, WSWDT_WEATHERSTATION_FIELD_ID, wswdtWeatherStation_ );
        Bind( statement, WSWST_WEATHERSTATION_FIELD_ID, wswstWeatherStation_ );
    }


    WideString ComplexGeoPosition2DTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  gp2d.[Id], \r\n"
        L"  gp2d.[EntityType], \r\n"
        L"  gp2d.[RowVersion], \r\n"
        L"  gp2d.[Catalog], \r\n"
        L"  gp2d.[Name], \r\n"
        L"  gp2d.[MaxRetention], \r\n"
        L"  aatnpt.[AidToNavigation] \r\n"
        L"FROM [GeoPosition2DTimeseriesView] gp2d \r\n"
        L"  LEFT JOIN [AisAidToNavigationPositionTimeseries] aatnpt ON(gp2d.[Id] = aatnpt.[Id] )";
    WideString ComplexGeoPosition2DTimeseriesColumnData::BaseViewName = L"GeoPosition2DTimeseriesView";
    WideString ComplexGeoPosition2DTimeseriesColumnData::ViewAliasName = L"gp2d";

    void ComplexGeoPosition2DTimeseriesColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, GP2D_ID_FIELD_ID, id_ );
        Bind( statement, GP2D_KIND_FIELD_ID, kind_ );
        Bind( statement, GP2D_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, GP2D_CATALOG_FIELD_ID, catalog_ );
        Bind( statement, GP2D_NAME_FIELD_ID, name_ );
        Bind( statement, GP2D_MAXRETENTION_FIELD_ID, maxRetention_ );
        Bind( statement, AATNPT_AIDTONAVIGATION_FIELD_ID, aatnptAidToNavigation_ );
    }


    WideString ComplexInt32TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  i32t.[Id], \r\n"
        L"  i32t.[EntityType], \r\n"
        L"  i32t.[RowVersion], \r\n"
        L"  i32t.[Catalog], \r\n"
        L"  i32t.[Name], \r\n"
        L"  i32t.[MaxRetention], \r\n"
        L"  raot.[Radar], \r\n"
        L"  rftclt.[Radar], \r\n"
        L"  rftcmt.[Radar], \r\n"
        L"  rapts.[Radar], \r\n"
        L"  rs1et.[Radar], \r\n"
        L"  rs1st.[Radar], \r\n"
        L"  rs2et.[Radar], \r\n"
        L"  rs2st.[Radar], \r\n"
        L"  rstclt.[Radar], \r\n"
        L"  ratuts.[Radar], \r\n"
        L"  vpobt.[Vessel] \r\n"
        L"FROM [Int32TimeseriesView] i32t \r\n"
        L"  LEFT JOIN [RadarAzimuthOffsetTimeseries] raot ON(i32t.[Id] = raot.[Id] ) \r\n"
        L"  LEFT JOIN [RadarFastTimeConstantLevelTimeseries] rftclt ON(i32t.[Id] = rftclt.[Id] ) \r\n"
        L"  LEFT JOIN [RadarFastTimeConstantModeTimeseries] rftcmt ON(i32t.[Id] = rftcmt.[Id] ) \r\n"
        L"  LEFT JOIN [RadarPulseTimeseries] rapts ON(i32t.[Id] = rapts.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector1EndTimeseries] rs1et ON(i32t.[Id] = rs1et.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector1StartTimeseries] rs1st ON(i32t.[Id] = rs1st.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector2EndTimeseries] rs2et ON(i32t.[Id] = rs2et.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSector2StartTimeseries] rs2st ON(i32t.[Id] = rs2st.[Id] ) \r\n"
        L"  LEFT JOIN [RadarSensitivityTimeControlLevelTimeseries] rstclt ON(i32t.[Id] = rstclt.[Id] ) \r\n"
        L"  LEFT JOIN [RadarTuningTimeseries] ratuts ON(i32t.[Id] = ratuts.[Id] ) \r\n"
        L"  LEFT JOIN [VesselPersonsOnBoardTimeseries] vpobt ON(i32t.[Id] = vpobt.[Id] )";
    WideString ComplexInt32TimeseriesColumnData::BaseViewName = L"Int32TimeseriesView";
    WideString ComplexInt32TimeseriesColumnData::ViewAliasName = L"i32t";

    void ComplexInt32TimeseriesColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, I32T_ID_FIELD_ID, id_ );
        Bind( statement, I32T_KIND_FIELD_ID, kind_ );
        Bind( statement, I32T_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, I32T_CATALOG_FIELD_ID, catalog_ );
        Bind( statement, I32T_NAME_FIELD_ID, name_ );
        Bind( statement, I32T_MAXRETENTION_FIELD_ID, maxRetention_ );
        Bind( statement, RAOT_RADAR_FIELD_ID, raotRadar_ );
        Bind( statement, RFTCLT_RADAR_FIELD_ID, rftcltRadar_ );
        Bind( statement, RFTCMT_RADAR_FIELD_ID, rftcmtRadar_ );
        Bind( statement, RAPTS_RADAR_FIELD_ID, raptsRadar_ );
        Bind( statement, RS1ET_RADAR_FIELD_ID, rs1etRadar_ );
        Bind( statement, RS1ST_RADAR_FIELD_ID, rs1stRadar_ );
        Bind( statement, RS2ET_RADAR_FIELD_ID, rs2etRadar_ );
        Bind( statement, RS2ST_RADAR_FIELD_ID, rs2stRadar_ );
        Bind( statement, RSTCLT_RADAR_FIELD_ID, rstcltRadar_ );
        Bind( statement, RATUTS_RADAR_FIELD_ID, ratutsRadar_ );
        Bind( statement, VPOBT_VESSEL_FIELD_ID, vpobtVessel_ );
    }


    WideString ComplexUInt32TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  u32t.[Id], \r\n"
        L"  u32t.[EntityType], \r\n"
        L"  u32t.[RowVersion], \r\n"
        L"  u32t.[Catalog], \r\n"
        L"  u32t.[Name], \r\n"
        L"  u32t.[MaxRetention], \r\n"
        L"  rst.[Radome] \r\n"
        L"FROM [UInt32TimeseriesView] u32t \r\n"
        L"  LEFT JOIN [RadomeStatusTimeseries] rst ON(u32t.[Id] = rst.[Id] )";
    WideString ComplexUInt32TimeseriesColumnData::BaseViewName = L"UInt32TimeseriesView";
    WideString ComplexUInt32TimeseriesColumnData::ViewAliasName = L"u32t";

    void ComplexUInt32TimeseriesColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, U32T_ID_FIELD_ID, id_ );
        Bind( statement, U32T_KIND_FIELD_ID, kind_ );
        Bind( statement, U32T_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, U32T_CATALOG_FIELD_ID, catalog_ );
        Bind( statement, U32T_NAME_FIELD_ID, name_ );
        Bind( statement, U32T_MAXRETENTION_FIELD_ID, maxRetention_ );
        Bind( statement, RST_RADOME_FIELD_ID, rstRadome_ );
    }


    WideString ComplexTrackBaseColumnData::BaseQuery = L"SELECT \r\n"
        L"  tb.[Id], \r\n"
        L"  tb.[EntityType], \r\n"
        L"  tb.[RowVersion], \r\n"
        L"  tb.[Tracker], \r\n"
        L"  tb.[TrackNumber], \r\n"
        L"  tb.[Timestamp] \r\n"
        L"FROM [TrackBaseView] tb \r\n"
        L"  LEFT JOIN [Track] t ON(tb.[Id] = t.[Id] ) \r\n"
        L"  LEFT JOIN [Track3D] t3d ON(tb.[Id] = t3d.[Id] )";
    WideString ComplexTrackBaseColumnData::BaseViewName = L"TrackBaseView";
    WideString ComplexTrackBaseColumnData::ViewAliasName = L"tb";

    void ComplexTrackBaseColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, TB_ID_FIELD_ID, id_ );
        Bind( statement, TB_KIND_FIELD_ID, kind_ );
        Bind( statement, TB_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, TB_TRACKER_FIELD_ID, tracker_ );
        Bind( statement, TB_TRACKNUMBER_FIELD_ID, trackNumber_ );
        Bind( statement, TB_TIMESTAMP_FIELD_ID, timestamp_ );
    }


    WideString ComplexZoneColumnData::BaseQuery = L"SELECT \r\n"
        L"  z.[Id], \r\n"
        L"  z.[EntityType], \r\n"
        L"  z.[RowVersion], \r\n"
        L"  z.[Name], \r\n"
        L"  z.[Longitude], \r\n"
        L"  z.[Latitude], \r\n"
        L"  z.[AlarmType], \r\n"
        L"  z.[AlarmTime], \r\n"
        L"  z.[RadarTrackMinimumLifetime], \r\n"
        L"  z.[Speed], \r\n"
        L"  z.[StrokeColor], \r\n"
        L"  z.[FillColor], \r\n"
        L"  cz.[Radius], \r\n"
        L"  pz.[Polygon] \r\n"
        L"FROM [ZoneView] z \r\n"
        L"  LEFT JOIN [CircularZone] cz ON(z.[Id] = cz.[Id] ) \r\n"
        L"  LEFT JOIN [PolygonZone] pz ON(z.[Id] = pz.[Id] )";
    WideString ComplexZoneColumnData::BaseViewName = L"ZoneView";
    WideString ComplexZoneColumnData::ViewAliasName = L"z";

    void ComplexZoneColumnData::BindColumns( const ODBC::Statement& statement )
    {
        Bind( statement, Z_ID_FIELD_ID, id_ );
        Bind( statement, Z_KIND_FIELD_ID, kind_ );
        Bind( statement, Z_ROWVERSION_FIELD_ID, rowVersion_ );
        Bind( statement, Z_NAME_FIELD_ID, name_ );
        Bind( statement, Z_LONGITUDE_FIELD_ID, longitude_ );
        Bind( statement, Z_LATITUDE_FIELD_ID, latitude_ );
        Bind( statement, Z_ALARMTYPE_FIELD_ID, alarmType_ );
        Bind( statement, Z_ALARMTIME_FIELD_ID, alarmTime_ );
        Bind( statement, Z_RADARTRACKMINIMUMLIFETIME_FIELD_ID, radarTrackMinimumLifetime_ );
        Bind( statement, Z_SPEED_FIELD_ID, speed_ );
        Bind( statement, Z_STROKECOLOR_FIELD_ID, strokeColor_ );
        Bind( statement, Z_FILLCOLOR_FIELD_ID, fillColor_ );
        Bind( statement, CZ_RADIUS_FIELD_ID, czRadius_ );
    }

    void ComplexZoneColumnData::ReadUnboundData( const ODBC::Statement& statement )
    {
            pzPolygon_ = statement.GetDBBinary(PZ_POLYGON_FIELD_ID);
    }

}
