#include "pch.h"

#include "MsSqlSimpleDatabaseReaders.h"


namespace Barrelman::Databases::MsSql
{

    WideString AircraftTypeColumnData::BaseQuery = L"SELECT \r\n"
        L"  at.[Id], \r\n"
        L"  at.[RowVersion], \r\n"
        L"  at.[Name] \r\n"
        L"FROM [AircraftTypeView] at \r\n";
    WideString AircraftTypeColumnData::BaseViewName = L"AircraftTypeView";
    WideString AircraftTypeColumnData::ViewAliasName = L"at";

    WideString AisDeviceCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  adc.[Id], \r\n"
        L"  adc.[RowVersion], \r\n"
        L"  adc.[AisDevice], \r\n"
        L"  adc.[Timestamp], \r\n"
        L"  adc.[DeviceCommandSourceType], \r\n"
        L"  adc.[DeviceCommandSourceId], \r\n"
        L"  adc.[Reply] \r\n"
        L"FROM [AisDeviceCommandView] adc \r\n";
    WideString AisDeviceCommandColumnData::BaseViewName = L"AisDeviceCommandView";
    WideString AisDeviceCommandColumnData::ViewAliasName = L"adc";

    WideString AisDeviceCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  adcr.[Id], \r\n"
        L"  adcr.[RowVersion], \r\n"
        L"  adcr.[AisDevice], \r\n"
        L"  adcr.[Timestamp], \r\n"
        L"  adcr.[Command], \r\n"
        L"  adcr.[Status], \r\n"
        L"  adcr.[Message] \r\n"
        L"FROM [AisDeviceCommandReplyView] adcr \r\n";
    WideString AisDeviceCommandReplyColumnData::BaseViewName = L"AisDeviceCommandReplyView";
    WideString AisDeviceCommandReplyColumnData::ViewAliasName = L"adcr";

    WideString AisDeviceConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  adc.[Id], \r\n"
        L"  adc.[RowVersion], \r\n"
        L"  adc.[AisDevice], \r\n"
        L"  adc.[Timestamp], \r\n"
        L"  adc.[Filter], \r\n"
        L"  adc.[NorthWestLatitude], \r\n"
        L"  adc.[NorthWestLongitude], \r\n"
        L"  adc.[SouthEastLatitude], \r\n"
        L"  adc.[SouthEastLongitude], \r\n"
        L"  adc.[ComPort], \r\n"
        L"  adc.[BaudRate], \r\n"
        L"  adc.[IPAddress], \r\n"
        L"  adc.[Port], \r\n"
        L"  adc.[UdpPort], \r\n"
        L"  adc.[Authenticate], \r\n"
        L"  adc.[UserName], \r\n"
        L"  adc.[Password], \r\n"
        L"  adc.[AuthenticationURL], \r\n"
        L"  adc.[ConnectionType], \r\n"
        L"  adc.[SourceUpdateRate], \r\n"
        L"  adc.[ConfigurationURL], \r\n"
        L"  adc.[StoreReceivedSentences] \r\n"
        L"FROM [AisDeviceConfigurationView] adc \r\n";
    WideString AisDeviceConfigurationColumnData::BaseViewName = L"AisDeviceConfigurationView";
    WideString AisDeviceConfigurationColumnData::ViewAliasName = L"adc";

    WideString AisDeviceRawMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  adrm.[Id], \r\n"
        L"  adrm.[RowVersion], \r\n"
        L"  adrm.[AisDevice], \r\n"
        L"  adrm.[Timestamp], \r\n"
        L"  adrm.[IsSent], \r\n"
        L"  adrm.[Message] \r\n"
        L"FROM [AisDeviceRawMessageView] adrm \r\n";
    WideString AisDeviceRawMessageColumnData::BaseViewName = L"AisDeviceRawMessageView";
    WideString AisDeviceRawMessageColumnData::ViewAliasName = L"adrm";

    WideString AisDeviceRawSentenceColumnData::BaseQuery = L"SELECT \r\n"
        L"  adrs.[Id], \r\n"
        L"  adrs.[RowVersion], \r\n"
        L"  adrs.[AisDevice], \r\n"
        L"  adrs.[Timestamp], \r\n"
        L"  adrs.[Sentence] \r\n"
        L"FROM [AisDeviceRawSentenceView] adrs \r\n";
    WideString AisDeviceRawSentenceColumnData::BaseViewName = L"AisDeviceRawSentenceView";
    WideString AisDeviceRawSentenceColumnData::ViewAliasName = L"adrs";

    WideString AisMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  am.[Id], \r\n"
        L"  am.[EntityType], \r\n"
        L"  am.[RowVersion], \r\n"
        L"  am.[AisDevice], \r\n"
        L"  am.[ReceivedTimestamp], \r\n"
        L"  am.[MessageSequenceNumber], \r\n"
        L"  am.[Repeat], \r\n"
        L"  am.[Mmsi] \r\n"
        L"FROM [AisMessageView] am \r\n";
    WideString AisMessageColumnData::BaseViewName = L"AisMessageView";
    WideString AisMessageColumnData::ViewAliasName = L"am";

    WideString AidToNavigationReportMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  atnrm.[Id], \r\n"
        L"  atnrm.[EntityType], \r\n"
        L"  atnrm.[RowVersion], \r\n"
        L"  atnrm.[AisDevice], \r\n"
        L"  atnrm.[ReceivedTimestamp], \r\n"
        L"  atnrm.[MessageSequenceNumber], \r\n"
        L"  atnrm.[Repeat], \r\n"
        L"  atnrm.[Mmsi], \r\n"
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
        L"  atnrm.[NameExtension] \r\n"
        L"FROM [AidToNavigationReportMessageView] atnrm \r\n";
    WideString AidToNavigationReportMessageColumnData::BaseViewName = L"AidToNavigationReportMessageView";
    WideString AidToNavigationReportMessageColumnData::ViewAliasName = L"atnrm";

    WideString AisAddressedSafetyRelatedMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  aasrm.[Id], \r\n"
        L"  aasrm.[EntityType], \r\n"
        L"  aasrm.[RowVersion], \r\n"
        L"  aasrm.[AisDevice], \r\n"
        L"  aasrm.[ReceivedTimestamp], \r\n"
        L"  aasrm.[MessageSequenceNumber], \r\n"
        L"  aasrm.[Repeat], \r\n"
        L"  aasrm.[Mmsi], \r\n"
        L"  aasrm.[SequenceNumber], \r\n"
        L"  aasrm.[DestinationMmsi], \r\n"
        L"  aasrm.[RetransmitFlag], \r\n"
        L"  aasrm.[Spare], \r\n"
        L"  aasrm.[Text] \r\n"
        L"FROM [AisAddressedSafetyRelatedMessageView] aasrm \r\n";
    WideString AisAddressedSafetyRelatedMessageColumnData::BaseViewName = L"AisAddressedSafetyRelatedMessageView";
    WideString AisAddressedSafetyRelatedMessageColumnData::ViewAliasName = L"aasrm";

    WideString AisBaseStationReportMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  absrm.[Id], \r\n"
        L"  absrm.[EntityType], \r\n"
        L"  absrm.[RowVersion], \r\n"
        L"  absrm.[AisDevice], \r\n"
        L"  absrm.[ReceivedTimestamp], \r\n"
        L"  absrm.[MessageSequenceNumber], \r\n"
        L"  absrm.[Repeat], \r\n"
        L"  absrm.[Mmsi], \r\n"
        L"  absrm.[Timestamp], \r\n"
        L"  absrm.[PositionAccuracy], \r\n"
        L"  absrm.[Longitude], \r\n"
        L"  absrm.[Latitude], \r\n"
        L"  absrm.[PositionFixType], \r\n"
        L"  absrm.[Spare], \r\n"
        L"  absrm.[Raim], \r\n"
        L"  absrm.[RadioStatus] \r\n"
        L"FROM [AisBaseStationReportMessageView] absrm \r\n";
    WideString AisBaseStationReportMessageColumnData::BaseViewName = L"AisBaseStationReportMessageView";
    WideString AisBaseStationReportMessageColumnData::ViewAliasName = L"absrm";

    WideString AisBinaryAcknowledgeMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  abac.[Id], \r\n"
        L"  abac.[EntityType], \r\n"
        L"  abac.[RowVersion], \r\n"
        L"  abac.[AisDevice], \r\n"
        L"  abac.[ReceivedTimestamp], \r\n"
        L"  abac.[MessageSequenceNumber], \r\n"
        L"  abac.[Repeat], \r\n"
        L"  abac.[Mmsi], \r\n"
        L"  abac.[Spare], \r\n"
        L"  abac.[SequenceNumber1], \r\n"
        L"  abac.[Mmsi1], \r\n"
        L"  abac.[SequenceNumber2], \r\n"
        L"  abac.[Mmsi2], \r\n"
        L"  abac.[SequenceNumber3], \r\n"
        L"  abac.[Mmsi3], \r\n"
        L"  abac.[SequenceNumber4], \r\n"
        L"  abac.[Mmsi4] \r\n"
        L"FROM [AisBinaryAcknowledgeMessageView] abac \r\n";
    WideString AisBinaryAcknowledgeMessageColumnData::BaseViewName = L"AisBinaryAcknowledgeMessageView";
    WideString AisBinaryAcknowledgeMessageColumnData::ViewAliasName = L"abac";

    WideString AisBinaryAddressedMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  abam.[Id], \r\n"
        L"  abam.[EntityType], \r\n"
        L"  abam.[RowVersion], \r\n"
        L"  abam.[AisDevice], \r\n"
        L"  abam.[ReceivedTimestamp], \r\n"
        L"  abam.[MessageSequenceNumber], \r\n"
        L"  abam.[Repeat], \r\n"
        L"  abam.[Mmsi], \r\n"
        L"  abam.[SequenceNumber], \r\n"
        L"  abam.[DestinationMmsi], \r\n"
        L"  abam.[RetransmitFlag], \r\n"
        L"  abam.[Spare], \r\n"
        L"  abam.[DesignatedAreaCode], \r\n"
        L"  abam.[FunctionalId], \r\n"
        L"  abam.[Data] \r\n"
        L"FROM [AisBinaryAddressedMessageView] abam \r\n";
    WideString AisBinaryAddressedMessageColumnData::BaseViewName = L"AisBinaryAddressedMessageView";
    WideString AisBinaryAddressedMessageColumnData::ViewAliasName = L"abam";

    WideString AisBinaryBroadcastMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  abbm.[Id], \r\n"
        L"  abbm.[EntityType], \r\n"
        L"  abbm.[RowVersion], \r\n"
        L"  abbm.[AisDevice], \r\n"
        L"  abbm.[ReceivedTimestamp], \r\n"
        L"  abbm.[MessageSequenceNumber], \r\n"
        L"  abbm.[Repeat], \r\n"
        L"  abbm.[Mmsi], \r\n"
        L"  abbm.[Spare], \r\n"
        L"  abbm.[DesignatedAreaCode], \r\n"
        L"  abbm.[FunctionalId], \r\n"
        L"  abbm.[Data] \r\n"
        L"FROM [AisBinaryBroadcastMessageView] abbm \r\n";
    WideString AisBinaryBroadcastMessageColumnData::BaseViewName = L"AisBinaryBroadcastMessageView";
    WideString AisBinaryBroadcastMessageColumnData::ViewAliasName = L"abbm";

    WideString AisDataLinkManagementMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  adlmm.[Id], \r\n"
        L"  adlmm.[EntityType], \r\n"
        L"  adlmm.[RowVersion], \r\n"
        L"  adlmm.[AisDevice], \r\n"
        L"  adlmm.[ReceivedTimestamp], \r\n"
        L"  adlmm.[MessageSequenceNumber], \r\n"
        L"  adlmm.[Repeat], \r\n"
        L"  adlmm.[Mmsi], \r\n"
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
        L"  adlmm.[Increment4] \r\n"
        L"FROM [AisDataLinkManagementMessageView] adlmm \r\n";
    WideString AisDataLinkManagementMessageColumnData::BaseViewName = L"AisDataLinkManagementMessageView";
    WideString AisDataLinkManagementMessageColumnData::ViewAliasName = L"adlmm";

    WideString AisExtendedClassBCsPositionReportMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  aecbprm.[Id], \r\n"
        L"  aecbprm.[EntityType], \r\n"
        L"  aecbprm.[RowVersion], \r\n"
        L"  aecbprm.[AisDevice], \r\n"
        L"  aecbprm.[ReceivedTimestamp], \r\n"
        L"  aecbprm.[MessageSequenceNumber], \r\n"
        L"  aecbprm.[Repeat], \r\n"
        L"  aecbprm.[Mmsi], \r\n"
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
        L"  aecbprm.[Spare] \r\n"
        L"FROM [AisExtendedClassBCsPositionReportMessageView] aecbprm \r\n";
    WideString AisExtendedClassBCsPositionReportMessageColumnData::BaseViewName = L"AisExtendedClassBCsPositionReportMessageView";
    WideString AisExtendedClassBCsPositionReportMessageColumnData::ViewAliasName = L"aecbprm";

    WideString AisInterrogationMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  aim.[Id], \r\n"
        L"  aim.[EntityType], \r\n"
        L"  aim.[RowVersion], \r\n"
        L"  aim.[AisDevice], \r\n"
        L"  aim.[ReceivedTimestamp], \r\n"
        L"  aim.[MessageSequenceNumber], \r\n"
        L"  aim.[Repeat], \r\n"
        L"  aim.[Mmsi], \r\n"
        L"  aim.[InterrogatedMmsi], \r\n"
        L"  aim.[FirstMessageType], \r\n"
        L"  aim.[FirstSlotOffset], \r\n"
        L"  aim.[SecondMessageType], \r\n"
        L"  aim.[SecondSlotOffset], \r\n"
        L"  aim.[SecondStationInterrogationMmsi], \r\n"
        L"  aim.[SecondStationFirstMessageType], \r\n"
        L"  aim.[SecondStationFirstSlotOffset] \r\n"
        L"FROM [AisInterrogationMessageView] aim \r\n";
    WideString AisInterrogationMessageColumnData::BaseViewName = L"AisInterrogationMessageView";
    WideString AisInterrogationMessageColumnData::ViewAliasName = L"aim";

    WideString AisPositionReportClassAMessageBaseColumnData::BaseQuery = L"SELECT \r\n"
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
        L"FROM [AisPositionReportClassAMessageBaseView] aprcab \r\n";
    WideString AisPositionReportClassAMessageBaseColumnData::BaseViewName = L"AisPositionReportClassAMessageBaseView";
    WideString AisPositionReportClassAMessageBaseColumnData::ViewAliasName = L"aprcab";

    WideString AisPositionReportClassAAssignedScheduleMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  aprcasm.[Id], \r\n"
        L"  aprcasm.[EntityType], \r\n"
        L"  aprcasm.[RowVersion], \r\n"
        L"  aprcasm.[AisDevice], \r\n"
        L"  aprcasm.[ReceivedTimestamp], \r\n"
        L"  aprcasm.[MessageSequenceNumber], \r\n"
        L"  aprcasm.[Repeat], \r\n"
        L"  aprcasm.[Mmsi], \r\n"
        L"  aprcasm.[NavigationStatus], \r\n"
        L"  aprcasm.[RateOfTurn], \r\n"
        L"  aprcasm.[SpeedOverGround], \r\n"
        L"  aprcasm.[PositionAccuracy], \r\n"
        L"  aprcasm.[Longitude], \r\n"
        L"  aprcasm.[Latitude], \r\n"
        L"  aprcasm.[CourseOverGround], \r\n"
        L"  aprcasm.[TrueHeading], \r\n"
        L"  aprcasm.[Timestamp], \r\n"
        L"  aprcasm.[ManeuverIndicator], \r\n"
        L"  aprcasm.[Spare], \r\n"
        L"  aprcasm.[Raim], \r\n"
        L"  aprcasm.[RadioStatus] \r\n"
        L"FROM [AisPositionReportClassAAssignedScheduleMessageView] aprcasm \r\n";
    WideString AisPositionReportClassAAssignedScheduleMessageColumnData::BaseViewName = L"AisPositionReportClassAAssignedScheduleMessageView";
    WideString AisPositionReportClassAAssignedScheduleMessageColumnData::ViewAliasName = L"aprcasm";

    WideString AisPositionReportClassAMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  aprca.[Id], \r\n"
        L"  aprca.[EntityType], \r\n"
        L"  aprca.[RowVersion], \r\n"
        L"  aprca.[AisDevice], \r\n"
        L"  aprca.[ReceivedTimestamp], \r\n"
        L"  aprca.[MessageSequenceNumber], \r\n"
        L"  aprca.[Repeat], \r\n"
        L"  aprca.[Mmsi], \r\n"
        L"  aprca.[NavigationStatus], \r\n"
        L"  aprca.[RateOfTurn], \r\n"
        L"  aprca.[SpeedOverGround], \r\n"
        L"  aprca.[PositionAccuracy], \r\n"
        L"  aprca.[Longitude], \r\n"
        L"  aprca.[Latitude], \r\n"
        L"  aprca.[CourseOverGround], \r\n"
        L"  aprca.[TrueHeading], \r\n"
        L"  aprca.[Timestamp], \r\n"
        L"  aprca.[ManeuverIndicator], \r\n"
        L"  aprca.[Spare], \r\n"
        L"  aprca.[Raim], \r\n"
        L"  aprca.[RadioStatus] \r\n"
        L"FROM [AisPositionReportClassAMessageView] aprca \r\n";
    WideString AisPositionReportClassAMessageColumnData::BaseViewName = L"AisPositionReportClassAMessageView";
    WideString AisPositionReportClassAMessageColumnData::ViewAliasName = L"aprca";

    WideString AisPositionReportClassAResponseToInterrogationMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  aprcatim.[Id], \r\n"
        L"  aprcatim.[EntityType], \r\n"
        L"  aprcatim.[RowVersion], \r\n"
        L"  aprcatim.[AisDevice], \r\n"
        L"  aprcatim.[ReceivedTimestamp], \r\n"
        L"  aprcatim.[MessageSequenceNumber], \r\n"
        L"  aprcatim.[Repeat], \r\n"
        L"  aprcatim.[Mmsi], \r\n"
        L"  aprcatim.[NavigationStatus], \r\n"
        L"  aprcatim.[RateOfTurn], \r\n"
        L"  aprcatim.[SpeedOverGround], \r\n"
        L"  aprcatim.[PositionAccuracy], \r\n"
        L"  aprcatim.[Longitude], \r\n"
        L"  aprcatim.[Latitude], \r\n"
        L"  aprcatim.[CourseOverGround], \r\n"
        L"  aprcatim.[TrueHeading], \r\n"
        L"  aprcatim.[Timestamp], \r\n"
        L"  aprcatim.[ManeuverIndicator], \r\n"
        L"  aprcatim.[Spare], \r\n"
        L"  aprcatim.[Raim], \r\n"
        L"  aprcatim.[RadioStatus] \r\n"
        L"FROM [AisPositionReportClassAResponseToInterrogationMessageView] aprcatim \r\n";
    WideString AisPositionReportClassAResponseToInterrogationMessageColumnData::BaseViewName = L"AisPositionReportClassAResponseToInterrogationMessageView";
    WideString AisPositionReportClassAResponseToInterrogationMessageColumnData::ViewAliasName = L"aprcatim";

    WideString AisPositionReportForLongRangeApplicationsMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  aprflram.[Id], \r\n"
        L"  aprflram.[EntityType], \r\n"
        L"  aprflram.[RowVersion], \r\n"
        L"  aprflram.[AisDevice], \r\n"
        L"  aprflram.[ReceivedTimestamp], \r\n"
        L"  aprflram.[MessageSequenceNumber], \r\n"
        L"  aprflram.[Repeat], \r\n"
        L"  aprflram.[Mmsi], \r\n"
        L"  aprflram.[PositionAccuracy], \r\n"
        L"  aprflram.[Raim], \r\n"
        L"  aprflram.[NavigationStatus], \r\n"
        L"  aprflram.[Longitude], \r\n"
        L"  aprflram.[Latitude], \r\n"
        L"  aprflram.[SpeedOverGround], \r\n"
        L"  aprflram.[CourseOverGround], \r\n"
        L"  aprflram.[GnssPositionStatus], \r\n"
        L"  aprflram.[Spare] \r\n"
        L"FROM [AisPositionReportForLongRangeApplicationsMessageView] aprflram \r\n";
    WideString AisPositionReportForLongRangeApplicationsMessageColumnData::BaseViewName = L"AisPositionReportForLongRangeApplicationsMessageView";
    WideString AisPositionReportForLongRangeApplicationsMessageColumnData::ViewAliasName = L"aprflram";

    WideString AisSafetyRelatedAcknowledgmentMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  asram.[Id], \r\n"
        L"  asram.[EntityType], \r\n"
        L"  asram.[RowVersion], \r\n"
        L"  asram.[AisDevice], \r\n"
        L"  asram.[ReceivedTimestamp], \r\n"
        L"  asram.[MessageSequenceNumber], \r\n"
        L"  asram.[Repeat], \r\n"
        L"  asram.[Mmsi], \r\n"
        L"  asram.[Spare], \r\n"
        L"  asram.[SequenceNumber1], \r\n"
        L"  asram.[Mmsi1], \r\n"
        L"  asram.[SequenceNumber2], \r\n"
        L"  asram.[Mmsi2], \r\n"
        L"  asram.[SequenceNumber3], \r\n"
        L"  asram.[Mmsi3], \r\n"
        L"  asram.[SequenceNumber4], \r\n"
        L"  asram.[Mmsi4] \r\n"
        L"FROM [AisSafetyRelatedAcknowledgmentMessageView] asram \r\n";
    WideString AisSafetyRelatedAcknowledgmentMessageColumnData::BaseViewName = L"AisSafetyRelatedAcknowledgmentMessageView";
    WideString AisSafetyRelatedAcknowledgmentMessageColumnData::ViewAliasName = L"asram";

    WideString AisStandardClassBCsPositionReportMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  ascbprm.[Id], \r\n"
        L"  ascbprm.[EntityType], \r\n"
        L"  ascbprm.[RowVersion], \r\n"
        L"  ascbprm.[AisDevice], \r\n"
        L"  ascbprm.[ReceivedTimestamp], \r\n"
        L"  ascbprm.[MessageSequenceNumber], \r\n"
        L"  ascbprm.[Repeat], \r\n"
        L"  ascbprm.[Mmsi], \r\n"
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
        L"  ascbprm.[RadioStatus] \r\n"
        L"FROM [AisStandardClassBCsPositionReportMessageView] ascbprm \r\n";
    WideString AisStandardClassBCsPositionReportMessageColumnData::BaseViewName = L"AisStandardClassBCsPositionReportMessageView";
    WideString AisStandardClassBCsPositionReportMessageColumnData::ViewAliasName = L"ascbprm";

    WideString AisStandardSarAircraftPositionReportMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  assaprm.[Id], \r\n"
        L"  assaprm.[EntityType], \r\n"
        L"  assaprm.[RowVersion], \r\n"
        L"  assaprm.[AisDevice], \r\n"
        L"  assaprm.[ReceivedTimestamp], \r\n"
        L"  assaprm.[MessageSequenceNumber], \r\n"
        L"  assaprm.[Repeat], \r\n"
        L"  assaprm.[Mmsi], \r\n"
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
        L"  assaprm.[RadioStatus] \r\n"
        L"FROM [AisStandardSarAircraftPositionReportMessageView] assaprm \r\n";
    WideString AisStandardSarAircraftPositionReportMessageColumnData::BaseViewName = L"AisStandardSarAircraftPositionReportMessageView";
    WideString AisStandardSarAircraftPositionReportMessageColumnData::ViewAliasName = L"assaprm";

    WideString AisStaticAndVoyageRelatedDataMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  asavrdm.[Id], \r\n"
        L"  asavrdm.[EntityType], \r\n"
        L"  asavrdm.[RowVersion], \r\n"
        L"  asavrdm.[AisDevice], \r\n"
        L"  asavrdm.[ReceivedTimestamp], \r\n"
        L"  asavrdm.[MessageSequenceNumber], \r\n"
        L"  asavrdm.[Repeat], \r\n"
        L"  asavrdm.[Mmsi], \r\n"
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
        L"  asavrdm.[Spare] \r\n"
        L"FROM [AisStaticAndVoyageRelatedDataMessageView] asavrdm \r\n";
    WideString AisStaticAndVoyageRelatedDataMessageColumnData::BaseViewName = L"AisStaticAndVoyageRelatedDataMessageView";
    WideString AisStaticAndVoyageRelatedDataMessageColumnData::ViewAliasName = L"asavrdm";

    WideString AisStaticDataReportMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  asdrm.[Id], \r\n"
        L"  asdrm.[EntityType], \r\n"
        L"  asdrm.[RowVersion], \r\n"
        L"  asdrm.[AisDevice], \r\n"
        L"  asdrm.[ReceivedTimestamp], \r\n"
        L"  asdrm.[MessageSequenceNumber], \r\n"
        L"  asdrm.[Repeat], \r\n"
        L"  asdrm.[Mmsi], \r\n"
        L"  asdrm.[PartNumber] \r\n"
        L"FROM [AisStaticDataReportMessageView] asdrm \r\n";
    WideString AisStaticDataReportMessageColumnData::BaseViewName = L"AisStaticDataReportMessageView";
    WideString AisStaticDataReportMessageColumnData::ViewAliasName = L"asdrm";

    WideString AisStaticDataReportPartAMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  asdrpa.[Id], \r\n"
        L"  asdrpa.[EntityType], \r\n"
        L"  asdrpa.[RowVersion], \r\n"
        L"  asdrpa.[AisDevice], \r\n"
        L"  asdrpa.[ReceivedTimestamp], \r\n"
        L"  asdrpa.[MessageSequenceNumber], \r\n"
        L"  asdrpa.[Repeat], \r\n"
        L"  asdrpa.[Mmsi], \r\n"
        L"  asdrpa.[PartNumber], \r\n"
        L"  asdrpa.[ShipName], \r\n"
        L"  asdrpa.[Spare] \r\n"
        L"FROM [AisStaticDataReportPartAMessageView] asdrpa \r\n";
    WideString AisStaticDataReportPartAMessageColumnData::BaseViewName = L"AisStaticDataReportPartAMessageView";
    WideString AisStaticDataReportPartAMessageColumnData::ViewAliasName = L"asdrpa";

    WideString AisStaticDataReportPartBMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  asdrpb.[Id], \r\n"
        L"  asdrpb.[EntityType], \r\n"
        L"  asdrpb.[RowVersion], \r\n"
        L"  asdrpb.[AisDevice], \r\n"
        L"  asdrpb.[ReceivedTimestamp], \r\n"
        L"  asdrpb.[MessageSequenceNumber], \r\n"
        L"  asdrpb.[Repeat], \r\n"
        L"  asdrpb.[Mmsi], \r\n"
        L"  asdrpb.[PartNumber], \r\n"
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
        L"FROM [AisStaticDataReportPartBMessageView] asdrpb \r\n";
    WideString AisStaticDataReportPartBMessageColumnData::BaseViewName = L"AisStaticDataReportPartBMessageView";
    WideString AisStaticDataReportPartBMessageColumnData::ViewAliasName = L"asdrpb";

    WideString AisUtcAndDateInquiryMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  auadim.[Id], \r\n"
        L"  auadim.[EntityType], \r\n"
        L"  auadim.[RowVersion], \r\n"
        L"  auadim.[AisDevice], \r\n"
        L"  auadim.[ReceivedTimestamp], \r\n"
        L"  auadim.[MessageSequenceNumber], \r\n"
        L"  auadim.[Repeat], \r\n"
        L"  auadim.[Mmsi], \r\n"
        L"  auadim.[Spare1], \r\n"
        L"  auadim.[DestinationMmsi], \r\n"
        L"  auadim.[Spare2] \r\n"
        L"FROM [AisUtcAndDateInquiryMessageView] auadim \r\n";
    WideString AisUtcAndDateInquiryMessageColumnData::BaseViewName = L"AisUtcAndDateInquiryMessageView";
    WideString AisUtcAndDateInquiryMessageColumnData::ViewAliasName = L"auadim";

    WideString AisUtcAndDateResponseMessageColumnData::BaseQuery = L"SELECT \r\n"
        L"  auadrm.[Id], \r\n"
        L"  auadrm.[EntityType], \r\n"
        L"  auadrm.[RowVersion], \r\n"
        L"  auadrm.[AisDevice], \r\n"
        L"  auadrm.[ReceivedTimestamp], \r\n"
        L"  auadrm.[MessageSequenceNumber], \r\n"
        L"  auadrm.[Repeat], \r\n"
        L"  auadrm.[Mmsi], \r\n"
        L"  auadrm.[Datetime], \r\n"
        L"  auadrm.[PositionAccuracy], \r\n"
        L"  auadrm.[Longitude], \r\n"
        L"  auadrm.[Latitude], \r\n"
        L"  auadrm.[PositionFixType], \r\n"
        L"  auadrm.[Spare], \r\n"
        L"  auadrm.[Raim], \r\n"
        L"  auadrm.[RadioStatus] \r\n"
        L"FROM [AisUtcAndDateResponseMessageView] auadrm \r\n";
    WideString AisUtcAndDateResponseMessageColumnData::BaseViewName = L"AisUtcAndDateResponseMessageView";
    WideString AisUtcAndDateResponseMessageColumnData::ViewAliasName = L"auadrm";

    WideString AlarmStateChangeColumnData::BaseQuery = L"SELECT \r\n"
        L"  asc.[Id], \r\n"
        L"  asc.[RowVersion], \r\n"
        L"  asc.[Alarm], \r\n"
        L"  asc.[Timestamp], \r\n"
        L"  asc.[State] \r\n"
        L"FROM [AlarmStateChangeView] asc \r\n";
    WideString AlarmStateChangeColumnData::BaseViewName = L"AlarmStateChangeView";
    WideString AlarmStateChangeColumnData::ViewAliasName = L"asc";

    WideString BaseStationTypeColumnData::BaseQuery = L"SELECT \r\n"
        L"  bst.[Id], \r\n"
        L"  bst.[RowVersion], \r\n"
        L"  bst.[Name] \r\n"
        L"FROM [BaseStationTypeView] bst \r\n";
    WideString BaseStationTypeColumnData::BaseViewName = L"BaseStationTypeView";
    WideString BaseStationTypeColumnData::ViewAliasName = L"bst";

    WideString BinaryTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  btv.[Id], \r\n"
        L"  btv.[RowVersion], \r\n"
        L"  btv.[Timeseries], \r\n"
        L"  btv.[Timestamp], \r\n"
        L"  btv.[Value] \r\n"
        L"FROM [BinaryTimeseriesValueView] btv \r\n";
    WideString BinaryTimeseriesValueColumnData::BaseViewName = L"BinaryTimeseriesValueView";
    WideString BinaryTimeseriesValueColumnData::ViewAliasName = L"btv";

    WideString BookmarkColumnData::BaseQuery = L"SELECT \r\n"
        L"  b.[Id], \r\n"
        L"  b.[RowVersion], \r\n"
        L"  b.[View], \r\n"
        L"  b.[Name], \r\n"
        L"  b.[Timestamp], \r\n"
        L"  b.[Latitude], \r\n"
        L"  b.[Longitude], \r\n"
        L"  b.[ZoomLevel] \r\n"
        L"FROM [BookmarkView] b \r\n";
    WideString BookmarkColumnData::BaseViewName = L"BookmarkView";
    WideString BookmarkColumnData::ViewAliasName = L"b";

    WideString BooleanTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  btv.[Id], \r\n"
        L"  btv.[RowVersion], \r\n"
        L"  btv.[Timeseries], \r\n"
        L"  btv.[Timestamp], \r\n"
        L"  btv.[Value] \r\n"
        L"FROM [BooleanTimeseriesValueView] btv \r\n";
    WideString BooleanTimeseriesValueColumnData::BaseViewName = L"BooleanTimeseriesValueView";
    WideString BooleanTimeseriesValueColumnData::ViewAliasName = L"btv";

    WideString ByteTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  btv.[Id], \r\n"
        L"  btv.[RowVersion], \r\n"
        L"  btv.[Timeseries], \r\n"
        L"  btv.[Timestamp], \r\n"
        L"  btv.[Value] \r\n"
        L"FROM [ByteTimeseriesValueView] btv \r\n";
    WideString ByteTimeseriesValueColumnData::BaseViewName = L"ByteTimeseriesValueView";
    WideString ByteTimeseriesValueColumnData::ViewAliasName = L"btv";

    WideString CameraCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  cc.[Id], \r\n"
        L"  cc.[EntityType], \r\n"
        L"  cc.[RowVersion], \r\n"
        L"  cc.[Camera], \r\n"
        L"  cc.[Timestamp], \r\n"
        L"  cc.[DeviceCommandSourceType], \r\n"
        L"  cc.[DeviceCommandSourceId], \r\n"
        L"  cc.[Reply] \r\n"
        L"FROM [CameraCommandView] cc \r\n";
    WideString CameraCommandColumnData::BaseViewName = L"CameraCommandView";
    WideString CameraCommandColumnData::ViewAliasName = L"cc";

    WideString CameraCommandAbsoluteMoveColumnData::BaseQuery = L"SELECT \r\n"
        L"  ccam.[Id], \r\n"
        L"  ccam.[EntityType], \r\n"
        L"  ccam.[RowVersion], \r\n"
        L"  ccam.[Camera], \r\n"
        L"  ccam.[Timestamp], \r\n"
        L"  ccam.[DeviceCommandSourceType], \r\n"
        L"  ccam.[DeviceCommandSourceId], \r\n"
        L"  ccam.[Reply], \r\n"
        L"  ccam.[PositionPanTiltMode], \r\n"
        L"  ccam.[PanAngle], \r\n"
        L"  ccam.[TiltAngle], \r\n"
        L"  ccam.[PositionFocalLengthMode], \r\n"
        L"  ccam.[FocalLength], \r\n"
        L"  ccam.[SpeedPanTiltMode], \r\n"
        L"  ccam.[PanSpeed], \r\n"
        L"  ccam.[TiltSpeed], \r\n"
        L"  ccam.[SpeedFocalLengthMode], \r\n"
        L"  ccam.[ZoomSpeed] \r\n"
        L"FROM [CameraCommandAbsoluteMoveView] ccam \r\n";
    WideString CameraCommandAbsoluteMoveColumnData::BaseViewName = L"CameraCommandAbsoluteMoveView";
    WideString CameraCommandAbsoluteMoveColumnData::ViewAliasName = L"ccam";

    WideString CameraCommandAdjustPanTiltZoomColumnData::BaseQuery = L"SELECT \r\n"
        L"  ccaptz.[Id], \r\n"
        L"  ccaptz.[EntityType], \r\n"
        L"  ccaptz.[RowVersion], \r\n"
        L"  ccaptz.[Camera], \r\n"
        L"  ccaptz.[Timestamp], \r\n"
        L"  ccaptz.[DeviceCommandSourceType], \r\n"
        L"  ccaptz.[DeviceCommandSourceId], \r\n"
        L"  ccaptz.[Reply], \r\n"
        L"  ccaptz.[X], \r\n"
        L"  ccaptz.[Y], \r\n"
        L"  ccaptz.[Z] \r\n"
        L"FROM [CameraCommandAdjustPanTiltZoomView] ccaptz \r\n";
    WideString CameraCommandAdjustPanTiltZoomColumnData::BaseViewName = L"CameraCommandAdjustPanTiltZoomView";
    WideString CameraCommandAdjustPanTiltZoomColumnData::ViewAliasName = L"ccaptz";

    WideString CameraCommandContinuousMoveColumnData::BaseQuery = L"SELECT \r\n"
        L"  cccm.[Id], \r\n"
        L"  cccm.[EntityType], \r\n"
        L"  cccm.[RowVersion], \r\n"
        L"  cccm.[Camera], \r\n"
        L"  cccm.[Timestamp], \r\n"
        L"  cccm.[DeviceCommandSourceType], \r\n"
        L"  cccm.[DeviceCommandSourceId], \r\n"
        L"  cccm.[Reply], \r\n"
        L"  cccm.[Normalized], \r\n"
        L"  cccm.[PanVelocity], \r\n"
        L"  cccm.[TiltVelocity], \r\n"
        L"  cccm.[ZoomVelocity], \r\n"
        L"  cccm.[Duration] \r\n"
        L"FROM [CameraCommandContinuousMoveView] cccm \r\n";
    WideString CameraCommandContinuousMoveColumnData::BaseViewName = L"CameraCommandContinuousMoveView";
    WideString CameraCommandContinuousMoveColumnData::ViewAliasName = L"cccm";

    WideString CameraCommandGeoMoveColumnData::BaseQuery = L"SELECT \r\n"
        L"  ccgm.[Id], \r\n"
        L"  ccgm.[EntityType], \r\n"
        L"  ccgm.[RowVersion], \r\n"
        L"  ccgm.[Camera], \r\n"
        L"  ccgm.[Timestamp], \r\n"
        L"  ccgm.[DeviceCommandSourceType], \r\n"
        L"  ccgm.[DeviceCommandSourceId], \r\n"
        L"  ccgm.[Reply], \r\n"
        L"  ccgm.[Latitude], \r\n"
        L"  ccgm.[Longitude], \r\n"
        L"  ccgm.[Altitude], \r\n"
        L"  ccgm.[ViewportWidth], \r\n"
        L"  ccgm.[ViewportHeight] \r\n"
        L"FROM [CameraCommandGeoMoveView] ccgm \r\n";
    WideString CameraCommandGeoMoveColumnData::BaseViewName = L"CameraCommandGeoMoveView";
    WideString CameraCommandGeoMoveColumnData::ViewAliasName = L"ccgm";

    WideString CameraCommandRelativeMoveColumnData::BaseQuery = L"SELECT \r\n"
        L"  ccrm.[Id], \r\n"
        L"  ccrm.[EntityType], \r\n"
        L"  ccrm.[RowVersion], \r\n"
        L"  ccrm.[Camera], \r\n"
        L"  ccrm.[Timestamp], \r\n"
        L"  ccrm.[DeviceCommandSourceType], \r\n"
        L"  ccrm.[DeviceCommandSourceId], \r\n"
        L"  ccrm.[Reply], \r\n"
        L"  ccrm.[Normalized], \r\n"
        L"  ccrm.[PanAngle], \r\n"
        L"  ccrm.[TiltAngle], \r\n"
        L"  ccrm.[FocalLength], \r\n"
        L"  ccrm.[PanSpeed], \r\n"
        L"  ccrm.[TiltSpeed], \r\n"
        L"  ccrm.[ZoomSpeed] \r\n"
        L"FROM [CameraCommandRelativeMoveView] ccrm \r\n";
    WideString CameraCommandRelativeMoveColumnData::BaseViewName = L"CameraCommandRelativeMoveView";
    WideString CameraCommandRelativeMoveColumnData::ViewAliasName = L"ccrm";

    WideString CameraCommandReleasePTZOwnershipColumnData::BaseQuery = L"SELECT \r\n"
        L"  crlp.[Id], \r\n"
        L"  crlp.[EntityType], \r\n"
        L"  crlp.[RowVersion], \r\n"
        L"  crlp.[Camera], \r\n"
        L"  crlp.[Timestamp], \r\n"
        L"  crlp.[DeviceCommandSourceType], \r\n"
        L"  crlp.[DeviceCommandSourceId], \r\n"
        L"  crlp.[Reply] \r\n"
        L"FROM [CameraCommandReleasePTZOwnershipView] crlp \r\n";
    WideString CameraCommandReleasePTZOwnershipColumnData::BaseViewName = L"CameraCommandReleasePTZOwnershipView";
    WideString CameraCommandReleasePTZOwnershipColumnData::ViewAliasName = L"crlp";

    WideString CameraCommandRequestPTZOwnershipColumnData::BaseQuery = L"SELECT \r\n"
        L"  crqp.[Id], \r\n"
        L"  crqp.[EntityType], \r\n"
        L"  crqp.[RowVersion], \r\n"
        L"  crqp.[Camera], \r\n"
        L"  crqp.[Timestamp], \r\n"
        L"  crqp.[DeviceCommandSourceType], \r\n"
        L"  crqp.[DeviceCommandSourceId], \r\n"
        L"  crqp.[Reply] \r\n"
        L"FROM [CameraCommandRequestPTZOwnershipView] crqp \r\n";
    WideString CameraCommandRequestPTZOwnershipColumnData::BaseViewName = L"CameraCommandRequestPTZOwnershipView";
    WideString CameraCommandRequestPTZOwnershipColumnData::ViewAliasName = L"crqp";

    WideString CameraCommandSetAutoFocusColumnData::BaseQuery = L"SELECT \r\n"
        L"  ccsaf.[Id], \r\n"
        L"  ccsaf.[EntityType], \r\n"
        L"  ccsaf.[RowVersion], \r\n"
        L"  ccsaf.[Camera], \r\n"
        L"  ccsaf.[Timestamp], \r\n"
        L"  ccsaf.[DeviceCommandSourceType], \r\n"
        L"  ccsaf.[DeviceCommandSourceId], \r\n"
        L"  ccsaf.[Reply], \r\n"
        L"  ccsaf.[Enabled] \r\n"
        L"FROM [CameraCommandSetAutoFocusView] ccsaf \r\n";
    WideString CameraCommandSetAutoFocusColumnData::BaseViewName = L"CameraCommandSetAutoFocusView";
    WideString CameraCommandSetAutoFocusColumnData::ViewAliasName = L"ccsaf";

    WideString CameraCommandSetBlackAndWhiteColumnData::BaseQuery = L"SELECT \r\n"
        L"  ccsbaw.[Id], \r\n"
        L"  ccsbaw.[EntityType], \r\n"
        L"  ccsbaw.[RowVersion], \r\n"
        L"  ccsbaw.[Camera], \r\n"
        L"  ccsbaw.[Timestamp], \r\n"
        L"  ccsbaw.[DeviceCommandSourceType], \r\n"
        L"  ccsbaw.[DeviceCommandSourceId], \r\n"
        L"  ccsbaw.[Reply], \r\n"
        L"  ccsbaw.[Enabled] \r\n"
        L"FROM [CameraCommandSetBlackAndWhiteView] ccsbaw \r\n";
    WideString CameraCommandSetBlackAndWhiteColumnData::BaseViewName = L"CameraCommandSetBlackAndWhiteView";
    WideString CameraCommandSetBlackAndWhiteColumnData::ViewAliasName = L"ccsbaw";

    WideString CameraCommandSetFollowedColumnData::BaseQuery = L"SELECT \r\n"
        L"  ccsf.[Id], \r\n"
        L"  ccsf.[EntityType], \r\n"
        L"  ccsf.[RowVersion], \r\n"
        L"  ccsf.[Camera], \r\n"
        L"  ccsf.[Timestamp], \r\n"
        L"  ccsf.[DeviceCommandSourceType], \r\n"
        L"  ccsf.[DeviceCommandSourceId], \r\n"
        L"  ccsf.[Reply], \r\n"
        L"  ccsf.[TrackId], \r\n"
        L"  ccsf.[Reason] \r\n"
        L"FROM [CameraCommandSetFollowedView] ccsf \r\n";
    WideString CameraCommandSetFollowedColumnData::BaseViewName = L"CameraCommandSetFollowedView";
    WideString CameraCommandSetFollowedColumnData::ViewAliasName = L"ccsf";

    WideString CameraCommandSetInfraRedLampColumnData::BaseQuery = L"SELECT \r\n"
        L"  ccsirl.[Id], \r\n"
        L"  ccsirl.[EntityType], \r\n"
        L"  ccsirl.[RowVersion], \r\n"
        L"  ccsirl.[Camera], \r\n"
        L"  ccsirl.[Timestamp], \r\n"
        L"  ccsirl.[DeviceCommandSourceType], \r\n"
        L"  ccsirl.[DeviceCommandSourceId], \r\n"
        L"  ccsirl.[Reply], \r\n"
        L"  ccsirl.[Enabled] \r\n"
        L"FROM [CameraCommandSetInfraRedLampView] ccsirl \r\n";
    WideString CameraCommandSetInfraRedLampColumnData::BaseViewName = L"CameraCommandSetInfraRedLampView";
    WideString CameraCommandSetInfraRedLampColumnData::ViewAliasName = L"ccsirl";

    WideString CameraCommandSetWasherColumnData::BaseQuery = L"SELECT \r\n"
        L"  cwa.[Id], \r\n"
        L"  cwa.[EntityType], \r\n"
        L"  cwa.[RowVersion], \r\n"
        L"  cwa.[Camera], \r\n"
        L"  cwa.[Timestamp], \r\n"
        L"  cwa.[DeviceCommandSourceType], \r\n"
        L"  cwa.[DeviceCommandSourceId], \r\n"
        L"  cwa.[Reply], \r\n"
        L"  cwa.[Enabled] \r\n"
        L"FROM [CameraCommandSetWasherView] cwa \r\n";
    WideString CameraCommandSetWasherColumnData::BaseViewName = L"CameraCommandSetWasherView";
    WideString CameraCommandSetWasherColumnData::ViewAliasName = L"cwa";

    WideString CameraCommandSetWiperColumnData::BaseQuery = L"SELECT \r\n"
        L"  cwi.[Id], \r\n"
        L"  cwi.[EntityType], \r\n"
        L"  cwi.[RowVersion], \r\n"
        L"  cwi.[Camera], \r\n"
        L"  cwi.[Timestamp], \r\n"
        L"  cwi.[DeviceCommandSourceType], \r\n"
        L"  cwi.[DeviceCommandSourceId], \r\n"
        L"  cwi.[Reply], \r\n"
        L"  cwi.[Enabled] \r\n"
        L"FROM [CameraCommandSetWiperView] cwi \r\n";
    WideString CameraCommandSetWiperColumnData::BaseViewName = L"CameraCommandSetWiperView";
    WideString CameraCommandSetWiperColumnData::ViewAliasName = L"cwi";

    WideString CameraCommandStopColumnData::BaseQuery = L"SELECT \r\n"
        L"  ccs.[Id], \r\n"
        L"  ccs.[EntityType], \r\n"
        L"  ccs.[RowVersion], \r\n"
        L"  ccs.[Camera], \r\n"
        L"  ccs.[Timestamp], \r\n"
        L"  ccs.[DeviceCommandSourceType], \r\n"
        L"  ccs.[DeviceCommandSourceId], \r\n"
        L"  ccs.[Reply], \r\n"
        L"  ccs.[PanTilt], \r\n"
        L"  ccs.[Zoom] \r\n"
        L"FROM [CameraCommandStopView] ccs \r\n";
    WideString CameraCommandStopColumnData::BaseViewName = L"CameraCommandStopView";
    WideString CameraCommandStopColumnData::ViewAliasName = L"ccs";

    WideString CameraCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  ccr.[Id], \r\n"
        L"  ccr.[RowVersion], \r\n"
        L"  ccr.[Camera], \r\n"
        L"  ccr.[Timestamp], \r\n"
        L"  ccr.[Command], \r\n"
        L"  ccr.[Status], \r\n"
        L"  ccr.[PanAngle], \r\n"
        L"  ccr.[TiltAngle], \r\n"
        L"  ccr.[FocalLength], \r\n"
        L"  ccr.[Message] \r\n"
        L"FROM [CameraCommandReplyView] ccr \r\n";
    WideString CameraCommandReplyColumnData::BaseViewName = L"CameraCommandReplyView";
    WideString CameraCommandReplyColumnData::ViewAliasName = L"ccr";

    WideString CameraConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  cc.[Id], \r\n"
        L"  cc.[RowVersion], \r\n"
        L"  cc.[Camera], \r\n"
        L"  cc.[Timestamp], \r\n"
        L"  cc.[CameraControlProtocol], \r\n"
        L"  cc.[CameraURL], \r\n"
        L"  cc.[ConfigurationURL], \r\n"
        L"  cc.[UserName], \r\n"
        L"  cc.[Password], \r\n"
        L"  cc.[UseRtspUriOverride], \r\n"
        L"  cc.[RtspUriOverride], \r\n"
        L"  cc.[Latitude], \r\n"
        L"  cc.[Longitude], \r\n"
        L"  cc.[Altitude], \r\n"
        L"  cc.[UseRelativePosition], \r\n"
        L"  cc.[PanTiltMode], \r\n"
        L"  cc.[MinTiltAngle], \r\n"
        L"  cc.[MaxTiltAngle], \r\n"
        L"  cc.[MinTiltScaleAngle], \r\n"
        L"  cc.[MaxTiltScaleAngle], \r\n"
        L"  cc.[UseReverseTiltAngle], \r\n"
        L"  cc.[UseReverseNormalizedTiltAngle], \r\n"
        L"  cc.[MinTiltVelocity], \r\n"
        L"  cc.[MaxTiltVelocity], \r\n"
        L"  cc.[MinTiltSpeed], \r\n"
        L"  cc.[MaxTiltSpeed], \r\n"
        L"  cc.[MinPanAngle], \r\n"
        L"  cc.[MaxPanAngle], \r\n"
        L"  cc.[MinPanScaleAngle], \r\n"
        L"  cc.[MaxPanScaleAngle], \r\n"
        L"  cc.[UseReversePanAngle], \r\n"
        L"  cc.[UseReverseNormalizedPanAngle], \r\n"
        L"  cc.[MinPanVelocity], \r\n"
        L"  cc.[MaxPanVelocity], \r\n"
        L"  cc.[MinPanSpeed], \r\n"
        L"  cc.[MaxPanSpeed], \r\n"
        L"  cc.[FocalLengthMode], \r\n"
        L"  cc.[MinFocalLength], \r\n"
        L"  cc.[MaxFocalLength], \r\n"
        L"  cc.[MinFocalLengthScale], \r\n"
        L"  cc.[MaxFocalLengthScale], \r\n"
        L"  cc.[MinZoomVelocity], \r\n"
        L"  cc.[MaxZoomVelocity], \r\n"
        L"  cc.[MinZoomSpeed], \r\n"
        L"  cc.[MaxZoomSpeed], \r\n"
        L"  cc.[ImageSensorWidth], \r\n"
        L"  cc.[ImageSensorHeight], \r\n"
        L"  cc.[HomePanAngle], \r\n"
        L"  cc.[HomeTiltAngle], \r\n"
        L"  cc.[HomeFocalLength], \r\n"
        L"  cc.[PanOffset], \r\n"
        L"  cc.[TiltOffset], \r\n"
        L"  cc.[AimAltitude], \r\n"
        L"  cc.[MinimumTargetWidth], \r\n"
        L"  cc.[TargetLockTimeout], \r\n"
        L"  cc.[UpdateStatusInterval], \r\n"
        L"  cc.[ReadTimeout], \r\n"
        L"  cc.[MoveCommandStatusDelay], \r\n"
        L"  cc.[PtzProfileName], \r\n"
        L"  cc.[PtzConfigurationToken], \r\n"
        L"  cc.[VideoSourceToken] \r\n"
        L"FROM [CameraConfigurationView] cc \r\n";
    WideString CameraConfigurationColumnData::BaseViewName = L"CameraConfigurationView";
    WideString CameraConfigurationColumnData::ViewAliasName = L"cc";

    WideString CameraPanCalibrationColumnData::BaseQuery = L"SELECT \r\n"
        L"  cpc.[Id], \r\n"
        L"  cpc.[RowVersion], \r\n"
        L"  cpc.[Camera], \r\n"
        L"  cpc.[Timestamp] \r\n"
        L"FROM [CameraPanCalibrationView] cpc \r\n";
    WideString CameraPanCalibrationColumnData::BaseViewName = L"CameraPanCalibrationView";
    WideString CameraPanCalibrationColumnData::ViewAliasName = L"cpc";

    WideString CameraPanCalibrationValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  cpcv.[Id], \r\n"
        L"  cpcv.[RowVersion], \r\n"
        L"  cpcv.[PanCalibration], \r\n"
        L"  cpcv.[PanAngle], \r\n"
        L"  cpcv.[PanOffset] \r\n"
        L"FROM [CameraPanCalibrationValueView] cpcv \r\n";
    WideString CameraPanCalibrationValueColumnData::BaseViewName = L"CameraPanCalibrationValueView";
    WideString CameraPanCalibrationValueColumnData::ViewAliasName = L"cpcv";

    WideString CameraStatusColumnData::BaseQuery = L"SELECT \r\n"
        L"  cs.[Id], \r\n"
        L"  cs.[RowVersion], \r\n"
        L"  cs.[Camera], \r\n"
        L"  cs.[Track], \r\n"
        L"  cs.[Timestamp], \r\n"
        L"  cs.[PositionPanTiltMode], \r\n"
        L"  cs.[PanAngle], \r\n"
        L"  cs.[TiltAngle], \r\n"
        L"  cs.[PositionFocalLengthMode], \r\n"
        L"  cs.[FocalLength], \r\n"
        L"  cs.[PanTiltMoveStatus], \r\n"
        L"  cs.[ZoomMoveStatus], \r\n"
        L"  cs.[VelocityPanTiltMode], \r\n"
        L"  cs.[PanVelocity], \r\n"
        L"  cs.[TiltVelocity], \r\n"
        L"  cs.[VelocityFocalLengthMode], \r\n"
        L"  cs.[ZoomVelocity], \r\n"
        L"  cs.[ActiveFeatures], \r\n"
        L"  cs.[Error] \r\n"
        L"FROM [CameraStatusView] cs \r\n";
    WideString CameraStatusColumnData::BaseViewName = L"CameraStatusView";
    WideString CameraStatusColumnData::ViewAliasName = L"cs";

    WideString CameraTiltCalibrationColumnData::BaseQuery = L"SELECT \r\n"
        L"  ctc.[Id], \r\n"
        L"  ctc.[RowVersion], \r\n"
        L"  ctc.[Camera], \r\n"
        L"  ctc.[Timestamp] \r\n"
        L"FROM [CameraTiltCalibrationView] ctc \r\n";
    WideString CameraTiltCalibrationColumnData::BaseViewName = L"CameraTiltCalibrationView";
    WideString CameraTiltCalibrationColumnData::ViewAliasName = L"ctc";

    WideString CameraTiltCalibrationValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  ctcv.[Id], \r\n"
        L"  ctcv.[RowVersion], \r\n"
        L"  ctcv.[TiltCalibration], \r\n"
        L"  ctcv.[PanAngle], \r\n"
        L"  ctcv.[TiltOffset] \r\n"
        L"FROM [CameraTiltCalibrationValueView] ctcv \r\n";
    WideString CameraTiltCalibrationValueColumnData::BaseViewName = L"CameraTiltCalibrationValueView";
    WideString CameraTiltCalibrationValueColumnData::ViewAliasName = L"ctcv";

    WideString CameraZoomCalibrationColumnData::BaseQuery = L"SELECT \r\n"
        L"  czc.[Id], \r\n"
        L"  czc.[RowVersion], \r\n"
        L"  czc.[Camera], \r\n"
        L"  czc.[Timestamp] \r\n"
        L"FROM [CameraZoomCalibrationView] czc \r\n";
    WideString CameraZoomCalibrationColumnData::BaseViewName = L"CameraZoomCalibrationView";
    WideString CameraZoomCalibrationColumnData::ViewAliasName = L"czc";

    WideString CameraZoomCalibrationValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  czcv.[Id], \r\n"
        L"  czcv.[RowVersion], \r\n"
        L"  czcv.[ZoomCalibration], \r\n"
        L"  czcv.[FocalLength], \r\n"
        L"  czcv.[FocalLengthOffset] \r\n"
        L"FROM [CameraZoomCalibrationValueView] czcv \r\n";
    WideString CameraZoomCalibrationValueColumnData::BaseViewName = L"CameraZoomCalibrationValueView";
    WideString CameraZoomCalibrationValueColumnData::ViewAliasName = L"czcv";

    WideString CatalogElementColumnData::BaseQuery = L"SELECT \r\n"
        L"  ce.[Id], \r\n"
        L"  ce.[EntityType], \r\n"
        L"  ce.[RowVersion], \r\n"
        L"  ce.[Catalog], \r\n"
        L"  ce.[Name] \r\n"
        L"FROM [CatalogElementView] ce \r\n";
    WideString CatalogElementColumnData::BaseViewName = L"CatalogElementView";
    WideString CatalogElementColumnData::ViewAliasName = L"ce";

    WideString CatalogColumnData::BaseQuery = L"SELECT \r\n"
        L"  c.[Id], \r\n"
        L"  c.[EntityType], \r\n"
        L"  c.[RowVersion], \r\n"
        L"  c.[Catalog], \r\n"
        L"  c.[Name] \r\n"
        L"FROM [CatalogView] c \r\n";
    WideString CatalogColumnData::BaseViewName = L"CatalogView";
    WideString CatalogColumnData::ViewAliasName = L"c";

    WideString ElementColumnData::BaseQuery = L"SELECT \r\n"
        L"  e.[Id], \r\n"
        L"  e.[EntityType], \r\n"
        L"  e.[RowVersion], \r\n"
        L"  e.[Catalog], \r\n"
        L"  e.[Name], \r\n"
        L"  e.[ElementType] \r\n"
        L"FROM [ElementView] e \r\n";
    WideString ElementColumnData::BaseViewName = L"ElementView";
    WideString ElementColumnData::ViewAliasName = L"e";

    WideString CollectionInfoColumnData::BaseQuery = L"SELECT \r\n"
        L"  ci.[Id], \r\n"
        L"  ci.[RowVersion], \r\n"
        L"  ci.[Count] \r\n"
        L"FROM [CollectionInfoView] ci \r\n";
    WideString CollectionInfoColumnData::BaseViewName = L"CollectionInfoView";
    WideString CollectionInfoColumnData::ViewAliasName = L"ci";

    WideString CountryColumnData::BaseQuery = L"SELECT \r\n"
        L"  c.[Id], \r\n"
        L"  c.[RowVersion], \r\n"
        L"  c.[Name], \r\n"
        L"  c.[Code], \r\n"
        L"  c.[Alpha2], \r\n"
        L"  c.[Alpha3] \r\n"
        L"FROM [CountryView] c \r\n";
    WideString CountryColumnData::BaseViewName = L"CountryView";
    WideString CountryColumnData::ViewAliasName = L"c";

    WideString CursorInfoColumnData::BaseQuery = L"SELECT \r\n"
        L"  ci.[Id], \r\n"
        L"  ci.[RowVersion], \r\n"
        L"  ci.[TypeCode] \r\n"
        L"FROM [CursorInfoView] ci \r\n";
    WideString CursorInfoColumnData::BaseViewName = L"CursorInfoView";
    WideString CursorInfoColumnData::ViewAliasName = L"ci";

    WideString DateTimeTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  dttv.[Id], \r\n"
        L"  dttv.[RowVersion], \r\n"
        L"  dttv.[Timeseries], \r\n"
        L"  dttv.[Timestamp], \r\n"
        L"  dttv.[Value] \r\n"
        L"FROM [DateTimeTimeseriesValueView] dttv \r\n";
    WideString DateTimeTimeseriesValueColumnData::BaseViewName = L"DateTimeTimeseriesValueView";
    WideString DateTimeTimeseriesValueColumnData::ViewAliasName = L"dttv";

    WideString DeviceHostColumnData::BaseQuery = L"SELECT \r\n"
        L"  dh.[Id], \r\n"
        L"  dh.[RowVersion], \r\n"
        L"  dh.[Name] \r\n"
        L"FROM [DeviceHostView] dh \r\n";
    WideString DeviceHostColumnData::BaseViewName = L"DeviceHostView";
    WideString DeviceHostColumnData::ViewAliasName = L"dh";

    WideString DeviceHostConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  dhc.[Id], \r\n"
        L"  dhc.[RowVersion], \r\n"
        L"  dhc.[Host], \r\n"
        L"  dhc.[Timestamp], \r\n"
        L"  dhc.[Hostname], \r\n"
        L"  dhc.[Port], \r\n"
        L"  dhc.[QueueName] \r\n"
        L"FROM [DeviceHostConfigurationView] dhc \r\n";
    WideString DeviceHostConfigurationColumnData::BaseViewName = L"DeviceHostConfigurationView";
    WideString DeviceHostConfigurationColumnData::ViewAliasName = L"dhc";

    WideString DoubleTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  dtv.[Id], \r\n"
        L"  dtv.[RowVersion], \r\n"
        L"  dtv.[Timeseries], \r\n"
        L"  dtv.[Timestamp], \r\n"
        L"  dtv.[Value] \r\n"
        L"FROM [DoubleTimeseriesValueView] dtv \r\n";
    WideString DoubleTimeseriesValueColumnData::BaseViewName = L"DoubleTimeseriesValueView";
    WideString DoubleTimeseriesValueColumnData::ViewAliasName = L"dtv";

    WideString FacilityTypeColumnData::BaseQuery = L"SELECT \r\n"
        L"  ft.[Id], \r\n"
        L"  ft.[RowVersion], \r\n"
        L"  ft.[Name] \r\n"
        L"FROM [FacilityTypeView] ft \r\n";
    WideString FacilityTypeColumnData::BaseViewName = L"FacilityTypeView";
    WideString FacilityTypeColumnData::ViewAliasName = L"ft";

    WideString GeoPosition2DTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  gp2dv.[Id], \r\n"
        L"  gp2dv.[RowVersion], \r\n"
        L"  gp2dv.[Timeseries], \r\n"
        L"  gp2dv.[Timestamp], \r\n"
        L"  gp2dv.[Latitude], \r\n"
        L"  gp2dv.[Longitude] \r\n"
        L"FROM [GeoPosition2DTimeseriesValueView] gp2dv \r\n";
    WideString GeoPosition2DTimeseriesValueColumnData::BaseViewName = L"GeoPosition2DTimeseriesValueView";
    WideString GeoPosition2DTimeseriesValueColumnData::ViewAliasName = L"gp2dv";

    WideString GeoPosition3DTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  gp3dv.[Id], \r\n"
        L"  gp3dv.[RowVersion], \r\n"
        L"  gp3dv.[Timeseries], \r\n"
        L"  gp3dv.[Timestamp], \r\n"
        L"  gp3dv.[Latitude], \r\n"
        L"  gp3dv.[Longitude], \r\n"
        L"  gp3dv.[Altitude] \r\n"
        L"FROM [GeoPosition3DTimeseriesValueView] gp3dv \r\n";
    WideString GeoPosition3DTimeseriesValueColumnData::BaseViewName = L"GeoPosition3DTimeseriesValueView";
    WideString GeoPosition3DTimeseriesValueColumnData::ViewAliasName = L"gp3dv";

    WideString GNSSDeviceCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  gc.[Id], \r\n"
        L"  gc.[RowVersion], \r\n"
        L"  gc.[GNSSDevice], \r\n"
        L"  gc.[Timestamp], \r\n"
        L"  gc.[DeviceCommandSourceType], \r\n"
        L"  gc.[DeviceCommandSourceId], \r\n"
        L"  gc.[Reply] \r\n"
        L"FROM [GNSSDeviceCommandView] gc \r\n";
    WideString GNSSDeviceCommandColumnData::BaseViewName = L"GNSSDeviceCommandView";
    WideString GNSSDeviceCommandColumnData::ViewAliasName = L"gc";

    WideString GNSSDeviceCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  gcr.[Id], \r\n"
        L"  gcr.[RowVersion], \r\n"
        L"  gcr.[GNSSDevice], \r\n"
        L"  gcr.[Timestamp], \r\n"
        L"  gcr.[Command], \r\n"
        L"  gcr.[Status], \r\n"
        L"  gcr.[Message] \r\n"
        L"FROM [GNSSDeviceCommandReplyView] gcr \r\n";
    WideString GNSSDeviceCommandReplyColumnData::BaseViewName = L"GNSSDeviceCommandReplyView";
    WideString GNSSDeviceCommandReplyColumnData::ViewAliasName = L"gcr";

    WideString GNSSDeviceConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  gc.[Id], \r\n"
        L"  gc.[RowVersion], \r\n"
        L"  gc.[GNSSDevice], \r\n"
        L"  gc.[Timestamp], \r\n"
        L"  gc.[DefaultLatitude], \r\n"
        L"  gc.[DefaultLongitude], \r\n"
        L"  gc.[DefaultAltitude], \r\n"
        L"  gc.[LatitudeOffset], \r\n"
        L"  gc.[LongitudeOffset], \r\n"
        L"  gc.[AltitudeOffset] \r\n"
        L"FROM [GNSSDeviceConfigurationView] gc \r\n";
    WideString GNSSDeviceConfigurationColumnData::BaseViewName = L"GNSSDeviceConfigurationView";
    WideString GNSSDeviceConfigurationColumnData::ViewAliasName = L"gc";

    WideString GuidTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  gtv.[Id], \r\n"
        L"  gtv.[RowVersion], \r\n"
        L"  gtv.[Timeseries], \r\n"
        L"  gtv.[Timestamp], \r\n"
        L"  gtv.[Value] \r\n"
        L"FROM [GuidTimeseriesValueView] gtv \r\n";
    WideString GuidTimeseriesValueColumnData::BaseViewName = L"GuidTimeseriesValueView";
    WideString GuidTimeseriesValueColumnData::ViewAliasName = L"gtv";

    WideString GyroDeviceCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  gdc.[Id], \r\n"
        L"  gdc.[RowVersion], \r\n"
        L"  gdc.[GyroDevice], \r\n"
        L"  gdc.[Timestamp], \r\n"
        L"  gdc.[DeviceCommandSourceType], \r\n"
        L"  gdc.[DeviceCommandSourceId], \r\n"
        L"  gdc.[Reply] \r\n"
        L"FROM [GyroDeviceCommandView] gdc \r\n";
    WideString GyroDeviceCommandColumnData::BaseViewName = L"GyroDeviceCommandView";
    WideString GyroDeviceCommandColumnData::ViewAliasName = L"gdc";

    WideString GyroDeviceCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  gdcr.[Id], \r\n"
        L"  gdcr.[RowVersion], \r\n"
        L"  gdcr.[GyroDevice], \r\n"
        L"  gdcr.[Timestamp], \r\n"
        L"  gdcr.[Command], \r\n"
        L"  gdcr.[Status], \r\n"
        L"  gdcr.[Message] \r\n"
        L"FROM [GyroDeviceCommandReplyView] gdcr \r\n";
    WideString GyroDeviceCommandReplyColumnData::BaseViewName = L"GyroDeviceCommandReplyView";
    WideString GyroDeviceCommandReplyColumnData::ViewAliasName = L"gdcr";

    WideString GyroDeviceConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  gdc.[Id], \r\n"
        L"  gdc.[RowVersion], \r\n"
        L"  gdc.[GyroDevice], \r\n"
        L"  gdc.[Timestamp], \r\n"
        L"  gdc.[DefaultHeadingTrueNorth], \r\n"
        L"  gdc.[DefaultMagneticTrueNorth], \r\n"
        L"  gdc.[HeadingTrueNorthOffset], \r\n"
        L"  gdc.[HeadingMagneticNorthOffset], \r\n"
        L"  gdc.[PitchTransducerName], \r\n"
        L"  gdc.[RollTransducerName] \r\n"
        L"FROM [GyroDeviceConfigurationView] gdc \r\n";
    WideString GyroDeviceConfigurationColumnData::BaseViewName = L"GyroDeviceConfigurationView";
    WideString GyroDeviceConfigurationColumnData::ViewAliasName = L"gdc";

    WideString IdentityColumnData::BaseQuery = L"SELECT \r\n"
        L"  i.[Id], \r\n"
        L"  i.[EntityType], \r\n"
        L"  i.[RowVersion] \r\n"
        L"FROM [IdentityView] i \r\n";
    WideString IdentityColumnData::BaseViewName = L"IdentityView";
    WideString IdentityColumnData::ViewAliasName = L"i";

    WideString CallsignColumnData::BaseQuery = L"SELECT \r\n"
        L"  c.[Id], \r\n"
        L"  c.[EntityType], \r\n"
        L"  c.[RowVersion], \r\n"
        L"  c.[Identifier] \r\n"
        L"FROM [CallsignView] c \r\n";
    WideString CallsignColumnData::BaseViewName = L"CallsignView";
    WideString CallsignColumnData::ViewAliasName = L"c";

    WideString InternationalMaritimeOrganizationNumberColumnData::BaseQuery = L"SELECT \r\n"
        L"  imon.[Id], \r\n"
        L"  imon.[EntityType], \r\n"
        L"  imon.[RowVersion], \r\n"
        L"  imon.[Identifier] \r\n"
        L"FROM [InternationalMaritimeOrganizationNumberView] imon \r\n";
    WideString InternationalMaritimeOrganizationNumberColumnData::BaseViewName = L"InternationalMaritimeOrganizationNumberView";
    WideString InternationalMaritimeOrganizationNumberColumnData::ViewAliasName = L"imon";

    WideString MaritimeMobileServiceIdentityColumnData::BaseQuery = L"SELECT \r\n"
        L"  mmsi.[Id], \r\n"
        L"  mmsi.[EntityType], \r\n"
        L"  mmsi.[RowVersion], \r\n"
        L"  mmsi.[Identifier] \r\n"
        L"FROM [MaritimeMobileServiceIdentityView] mmsi \r\n";
    WideString MaritimeMobileServiceIdentityColumnData::BaseViewName = L"MaritimeMobileServiceIdentityView";
    WideString MaritimeMobileServiceIdentityColumnData::ViewAliasName = L"mmsi";

    WideString NameColumnData::BaseQuery = L"SELECT \r\n"
        L"  n.[Id], \r\n"
        L"  n.[EntityType], \r\n"
        L"  n.[RowVersion], \r\n"
        L"  n.[Text] \r\n"
        L"FROM [NameView] n \r\n";
    WideString NameColumnData::BaseViewName = L"NameView";
    WideString NameColumnData::ViewAliasName = L"n";

    WideString Int16TimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  i16tv.[Id], \r\n"
        L"  i16tv.[RowVersion], \r\n"
        L"  i16tv.[Timeseries], \r\n"
        L"  i16tv.[Timestamp], \r\n"
        L"  i16tv.[Value] \r\n"
        L"FROM [Int16TimeseriesValueView] i16tv \r\n";
    WideString Int16TimeseriesValueColumnData::BaseViewName = L"Int16TimeseriesValueView";
    WideString Int16TimeseriesValueColumnData::ViewAliasName = L"i16tv";

    WideString Int32TimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  i32tv.[Id], \r\n"
        L"  i32tv.[RowVersion], \r\n"
        L"  i32tv.[Timeseries], \r\n"
        L"  i32tv.[Timestamp], \r\n"
        L"  i32tv.[Value] \r\n"
        L"FROM [Int32TimeseriesValueView] i32tv \r\n";
    WideString Int32TimeseriesValueColumnData::BaseViewName = L"Int32TimeseriesValueView";
    WideString Int32TimeseriesValueColumnData::ViewAliasName = L"i32tv";

    WideString Int64TimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  i64tv.[Id], \r\n"
        L"  i64tv.[RowVersion], \r\n"
        L"  i64tv.[Timeseries], \r\n"
        L"  i64tv.[Timestamp], \r\n"
        L"  i64tv.[Value] \r\n"
        L"FROM [Int64TimeseriesValueView] i64tv \r\n";
    WideString Int64TimeseriesValueColumnData::BaseViewName = L"Int64TimeseriesValueView";
    WideString Int64TimeseriesValueColumnData::ViewAliasName = L"i64tv";

    WideString ItemColumnData::BaseQuery = L"SELECT \r\n"
        L"  i.[Id], \r\n"
        L"  i.[EntityType], \r\n"
        L"  i.[RowVersion] \r\n"
        L"FROM [ItemView] i \r\n";
    WideString ItemColumnData::BaseViewName = L"ItemView";
    WideString ItemColumnData::ViewAliasName = L"i";

    WideString BaseStationColumnData::BaseQuery = L"SELECT \r\n"
        L"  bs.[Id], \r\n"
        L"  bs.[EntityType], \r\n"
        L"  bs.[RowVersion], \r\n"
        L"  bs.[Name], \r\n"
        L"  bs.[Type] \r\n"
        L"FROM [BaseStationView] bs \r\n";
    WideString BaseStationColumnData::BaseViewName = L"BaseStationView";
    WideString BaseStationColumnData::ViewAliasName = L"bs";

    WideString DeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  d.[Id], \r\n"
        L"  d.[EntityType], \r\n"
        L"  d.[RowVersion], \r\n"
        L"  d.[Host], \r\n"
        L"  d.[Name], \r\n"
        L"  d.[EnabledTimeseries], \r\n"
        L"  d.[Description] \r\n"
        L"FROM [DeviceView] d \r\n";
    WideString DeviceColumnData::BaseViewName = L"DeviceView";
    WideString DeviceColumnData::ViewAliasName = L"d";

    WideString CameraDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  cd.[Id], \r\n"
        L"  cd.[EntityType], \r\n"
        L"  cd.[RowVersion], \r\n"
        L"  cd.[Host], \r\n"
        L"  cd.[Name], \r\n"
        L"  cd.[EnabledTimeseries], \r\n"
        L"  cd.[Description] \r\n"
        L"FROM [CameraDeviceView] cd \r\n";
    WideString CameraDeviceColumnData::BaseViewName = L"CameraDeviceView";
    WideString CameraDeviceColumnData::ViewAliasName = L"cd";

    WideString GNSSDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  g.[Id], \r\n"
        L"  g.[EntityType], \r\n"
        L"  g.[RowVersion], \r\n"
        L"  g.[Host], \r\n"
        L"  g.[Name], \r\n"
        L"  g.[EnabledTimeseries], \r\n"
        L"  g.[LatitudeTimeseries], \r\n"
        L"  g.[LongitudeTimeseries], \r\n"
        L"  g.[AltitudeTimeseries], \r\n"
        L"  g.[Description] \r\n"
        L"FROM [GNSSDeviceView] g \r\n";
    WideString GNSSDeviceColumnData::BaseViewName = L"GNSSDeviceView";
    WideString GNSSDeviceColumnData::ViewAliasName = L"g";

    WideString GyroDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  gd.[Id], \r\n"
        L"  gd.[EntityType], \r\n"
        L"  gd.[RowVersion], \r\n"
        L"  gd.[Host], \r\n"
        L"  gd.[Name], \r\n"
        L"  gd.[EnabledTimeseries], \r\n"
        L"  gd.[HeadingTrueNorthTimeseries], \r\n"
        L"  gd.[HeadingMagneticNorthTimeseries], \r\n"
        L"  gd.[PitchTimeseries], \r\n"
        L"  gd.[RateOfTurnTimeseries], \r\n"
        L"  gd.[RollTimeseries], \r\n"
        L"  gd.[CourseTimeseries], \r\n"
        L"  gd.[SpeedTimeseries], \r\n"
        L"  gd.[GNSSDevice], \r\n"
        L"  gd.[Description] \r\n"
        L"FROM [GyroDeviceView] gd \r\n";
    WideString GyroDeviceColumnData::BaseViewName = L"GyroDeviceView";
    WideString GyroDeviceColumnData::ViewAliasName = L"gd";

    WideString LineInputDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  lid.[Id], \r\n"
        L"  lid.[EntityType], \r\n"
        L"  lid.[RowVersion], \r\n"
        L"  lid.[Host], \r\n"
        L"  lid.[Name], \r\n"
        L"  lid.[EnabledTimeseries], \r\n"
        L"  lid.[Description] \r\n"
        L"FROM [LineInputDeviceView] lid \r\n";
    WideString LineInputDeviceColumnData::BaseViewName = L"LineInputDeviceView";
    WideString LineInputDeviceColumnData::ViewAliasName = L"lid";

    WideString OilSpillDetectorDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  osdd.[Id], \r\n"
        L"  osdd.[EntityType], \r\n"
        L"  osdd.[RowVersion], \r\n"
        L"  osdd.[Host], \r\n"
        L"  osdd.[Name], \r\n"
        L"  osdd.[EnabledTimeseries], \r\n"
        L"  osdd.[Description] \r\n"
        L"FROM [OilSpillDetectorDeviceView] osdd \r\n";
    WideString OilSpillDetectorDeviceColumnData::BaseViewName = L"OilSpillDetectorDeviceView";
    WideString OilSpillDetectorDeviceColumnData::ViewAliasName = L"osdd";

    WideString RadioDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  rdi.[Id], \r\n"
        L"  rdi.[EntityType], \r\n"
        L"  rdi.[RowVersion], \r\n"
        L"  rdi.[Host], \r\n"
        L"  rdi.[Name], \r\n"
        L"  rdi.[EnabledTimeseries], \r\n"
        L"  rdi.[Description] \r\n"
        L"FROM [RadioDeviceView] rdi \r\n";
    WideString RadioDeviceColumnData::BaseViewName = L"RadioDeviceView";
    WideString RadioDeviceColumnData::ViewAliasName = L"rdi";

    WideString RadomeDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  rdo.[Id], \r\n"
        L"  rdo.[EntityType], \r\n"
        L"  rdo.[RowVersion], \r\n"
        L"  rdo.[Host], \r\n"
        L"  rdo.[Name], \r\n"
        L"  rdo.[EnabledTimeseries], \r\n"
        L"  rdo.[Radar], \r\n"
        L"  rdo.[PressureTimeseries], \r\n"
        L"  rdo.[TemperatureTimeseries], \r\n"
        L"  rdo.[DewPointTimeseries], \r\n"
        L"  rdo.[StatusTimeseries], \r\n"
        L"  rdo.[Description] \r\n"
        L"FROM [RadomeDeviceView] rdo \r\n";
    WideString RadomeDeviceColumnData::BaseViewName = L"RadomeDeviceView";
    WideString RadomeDeviceColumnData::ViewAliasName = L"rdo";

    WideString TrackerDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  td.[Id], \r\n"
        L"  td.[EntityType], \r\n"
        L"  td.[RowVersion], \r\n"
        L"  td.[Host], \r\n"
        L"  td.[Name], \r\n"
        L"  td.[EnabledTimeseries], \r\n"
        L"  td.[Description] \r\n"
        L"FROM [TrackerDeviceView] td \r\n";
    WideString TrackerDeviceColumnData::BaseViewName = L"TrackerDeviceView";
    WideString TrackerDeviceColumnData::ViewAliasName = L"td";

    WideString AisDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  ad.[Id], \r\n"
        L"  ad.[EntityType], \r\n"
        L"  ad.[RowVersion], \r\n"
        L"  ad.[Host], \r\n"
        L"  ad.[Name], \r\n"
        L"  ad.[EnabledTimeseries], \r\n"
        L"  ad.[Description] \r\n"
        L"FROM [AisDeviceView] ad \r\n";
    WideString AisDeviceColumnData::BaseViewName = L"AisDeviceView";
    WideString AisDeviceColumnData::ViewAliasName = L"ad";

    WideString RadarDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  rd.[Id], \r\n"
        L"  rd.[EntityType], \r\n"
        L"  rd.[RowVersion], \r\n"
        L"  rd.[Host], \r\n"
        L"  rd.[Name], \r\n"
        L"  rd.[EnabledTimeseries], \r\n"
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
        L"  rd.[Description] \r\n"
        L"FROM [RadarDeviceView] rd \r\n";
    WideString RadarDeviceColumnData::BaseViewName = L"RadarDeviceView";
    WideString RadarDeviceColumnData::ViewAliasName = L"rd";

    WideString WeatherStationDeviceColumnData::BaseQuery = L"SELECT \r\n"
        L"  wsd.[Id], \r\n"
        L"  wsd.[EntityType], \r\n"
        L"  wsd.[RowVersion], \r\n"
        L"  wsd.[Host], \r\n"
        L"  wsd.[Name], \r\n"
        L"  wsd.[EnabledTimeseries], \r\n"
        L"  wsd.[BarometricPressureTimeseries], \r\n"
        L"  wsd.[AirTemperatureTimeseries], \r\n"
        L"  wsd.[WaterTemperatureTimeseries], \r\n"
        L"  wsd.[RelativeHumidityTimeseries], \r\n"
        L"  wsd.[AbsoluteHumidityTimeseries], \r\n"
        L"  wsd.[DewPointTimeseries], \r\n"
        L"  wsd.[WindDirectionTimeseries], \r\n"
        L"  wsd.[WindSpeedTimeseries], \r\n"
        L"  wsd.[Gyro], \r\n"
        L"  wsd.[Description] \r\n"
        L"FROM [WeatherStationDeviceView] wsd \r\n";
    WideString WeatherStationDeviceColumnData::BaseViewName = L"WeatherStationDeviceView";
    WideString WeatherStationDeviceColumnData::ViewAliasName = L"wsd";

    WideString FacilityColumnData::BaseQuery = L"SELECT \r\n"
        L"  f.[Id], \r\n"
        L"  f.[EntityType], \r\n"
        L"  f.[RowVersion], \r\n"
        L"  f.[Name], \r\n"
        L"  f.[Type], \r\n"
        L"  f.[Longitude], \r\n"
        L"  f.[Latitude], \r\n"
        L"  f.[Altitude] \r\n"
        L"FROM [FacilityView] f \r\n";
    WideString FacilityColumnData::BaseViewName = L"FacilityView";
    WideString FacilityColumnData::ViewAliasName = L"f";

    WideString TrackableItemColumnData::BaseQuery = L"SELECT \r\n"
        L"  ti.[Id], \r\n"
        L"  ti.[EntityType], \r\n"
        L"  ti.[RowVersion] \r\n"
        L"FROM [TrackableItemView] ti \r\n";
    WideString TrackableItemColumnData::BaseViewName = L"TrackableItemView";
    WideString TrackableItemColumnData::ViewAliasName = L"ti";

    WideString AircraftColumnData::BaseQuery = L"SELECT \r\n"
        L"  a.[Id], \r\n"
        L"  a.[EntityType], \r\n"
        L"  a.[RowVersion], \r\n"
        L"  a.[Name], \r\n"
        L"  a.[Type] \r\n"
        L"FROM [AircraftView] a \r\n";
    WideString AircraftColumnData::BaseViewName = L"AircraftView";
    WideString AircraftColumnData::ViewAliasName = L"a";

    WideString AisAidToNavigationColumnData::BaseQuery = L"SELECT \r\n"
        L"  aatn.[Id], \r\n"
        L"  aatn.[EntityType], \r\n"
        L"  aatn.[RowVersion], \r\n"
        L"  aatn.[Name], \r\n"
        L"  aatn.[MMSI], \r\n"
        L"  aatn.[NavigationalAidType], \r\n"
        L"  aatn.[Position], \r\n"
        L"  aatn.[IsVirtual], \r\n"
        L"  aatn.[ToBow], \r\n"
        L"  aatn.[ToStern], \r\n"
        L"  aatn.[ToPort], \r\n"
        L"  aatn.[ToStarboard], \r\n"
        L"  aatn.[OffPositionTimeseries] \r\n"
        L"FROM [AisAidToNavigationView] aatn \r\n";
    WideString AisAidToNavigationColumnData::BaseViewName = L"AisAidToNavigationView";
    WideString AisAidToNavigationColumnData::ViewAliasName = L"aatn";

    WideString VehicleColumnData::BaseQuery = L"SELECT \r\n"
        L"  v.[Id], \r\n"
        L"  v.[EntityType], \r\n"
        L"  v.[RowVersion], \r\n"
        L"  v.[Name], \r\n"
        L"  v.[Type] \r\n"
        L"FROM [VehicleView] v \r\n";
    WideString VehicleColumnData::BaseViewName = L"VehicleView";
    WideString VehicleColumnData::ViewAliasName = L"v";

    WideString VesselColumnData::BaseQuery = L"SELECT \r\n"
        L"  vsl.[Id], \r\n"
        L"  vsl.[EntityType], \r\n"
        L"  vsl.[RowVersion], \r\n"
        L"  vsl.[Name], \r\n"
        L"  vsl.[Type], \r\n"
        L"  vsl.[ToBow], \r\n"
        L"  vsl.[ToStern], \r\n"
        L"  vsl.[ToPort], \r\n"
        L"  vsl.[ToStarboard], \r\n"
        L"  vsl.[DraughtTimeseries], \r\n"
        L"  vsl.[PersonsOnBoardTimeseries] \r\n"
        L"FROM [VesselView] vsl \r\n";
    WideString VesselColumnData::BaseViewName = L"VesselView";
    WideString VesselColumnData::ViewAliasName = L"vsl";

    WideString ItemIdentityLinkColumnData::BaseQuery = L"SELECT \r\n"
        L"  iil.[Id], \r\n"
        L"  iil.[RowVersion], \r\n"
        L"  iil.[Item], \r\n"
        L"  iil.[Identity], \r\n"
        L"  iil.[Start], \r\n"
        L"  iil.[End] \r\n"
        L"FROM [ItemIdentityLinkView] iil \r\n";
    WideString ItemIdentityLinkColumnData::BaseViewName = L"ItemIdentityLinkView";
    WideString ItemIdentityLinkColumnData::ViewAliasName = L"iil";

    WideString ItemParentChildLinkColumnData::BaseQuery = L"SELECT \r\n"
        L"  ipcl.[Id], \r\n"
        L"  ipcl.[RowVersion], \r\n"
        L"  ipcl.[Parent], \r\n"
        L"  ipcl.[Child], \r\n"
        L"  ipcl.[Timestamp] \r\n"
        L"FROM [ItemParentChildLinkView] ipcl \r\n";
    WideString ItemParentChildLinkColumnData::BaseViewName = L"ItemParentChildLinkView";
    WideString ItemParentChildLinkColumnData::ViewAliasName = L"ipcl";

    WideString LineInputDeviceCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  lidc.[Id], \r\n"
        L"  lidc.[RowVersion], \r\n"
        L"  lidc.[LineInputDevice], \r\n"
        L"  lidc.[Timestamp], \r\n"
        L"  lidc.[DeviceCommandSourceType], \r\n"
        L"  lidc.[DeviceCommandSourceId], \r\n"
        L"  lidc.[Reply] \r\n"
        L"FROM [LineInputDeviceCommandView] lidc \r\n";
    WideString LineInputDeviceCommandColumnData::BaseViewName = L"LineInputDeviceCommandView";
    WideString LineInputDeviceCommandColumnData::ViewAliasName = L"lidc";

    WideString LineInputDeviceCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  lidcr.[Id], \r\n"
        L"  lidcr.[RowVersion], \r\n"
        L"  lidcr.[LineInputDevice], \r\n"
        L"  lidcr.[Timestamp], \r\n"
        L"  lidcr.[Command], \r\n"
        L"  lidcr.[Status], \r\n"
        L"  lidcr.[Message] \r\n"
        L"FROM [LineInputDeviceCommandReplyView] lidcr \r\n";
    WideString LineInputDeviceCommandReplyColumnData::BaseViewName = L"LineInputDeviceCommandReplyView";
    WideString LineInputDeviceCommandReplyColumnData::ViewAliasName = L"lidcr";

    WideString LineInputDeviceConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  lidc.[Id], \r\n"
        L"  lidc.[RowVersion], \r\n"
        L"  lidc.[LineInputDevice], \r\n"
        L"  lidc.[Timestamp], \r\n"
        L"  lidc.[StoreReceivedSentences], \r\n"
        L"  lidc.[StoreSentMessages], \r\n"
        L"  lidc.[StoreUnsentMessages], \r\n"
        L"  lidc.[NMEA], \r\n"
        L"  lidc.[StrictNMEA], \r\n"
        L"  lidc.[ConnectionType], \r\n"
        L"  lidc.[UdpReceivePort], \r\n"
        L"  lidc.[UdpSendHostname], \r\n"
        L"  lidc.[UdpSendPort], \r\n"
        L"  lidc.[TcpHostname], \r\n"
        L"  lidc.[TcpPort], \r\n"
        L"  lidc.[UseHttpLogin], \r\n"
        L"  lidc.[LoginHostname], \r\n"
        L"  lidc.[LoginPort], \r\n"
        L"  lidc.[UserName], \r\n"
        L"  lidc.[Password], \r\n"
        L"  lidc.[ComPort], \r\n"
        L"  lidc.[BaudRate], \r\n"
        L"  lidc.[DataBits], \r\n"
        L"  lidc.[DiscardNull], \r\n"
        L"  lidc.[DtrEnable], \r\n"
        L"  lidc.[Handshake], \r\n"
        L"  lidc.[NewLine], \r\n"
        L"  lidc.[Parity], \r\n"
        L"  lidc.[ParityReplace], \r\n"
        L"  lidc.[ReadBufferSize], \r\n"
        L"  lidc.[ReadTimeout], \r\n"
        L"  lidc.[ReceivedBytesThreshold], \r\n"
        L"  lidc.[RtsEnable], \r\n"
        L"  lidc.[StopBits], \r\n"
        L"  lidc.[WriteBufferSize], \r\n"
        L"  lidc.[WriteTimeout], \r\n"
        L"  lidc.[PairedComPort] \r\n"
        L"FROM [LineInputDeviceConfigurationView] lidc \r\n";
    WideString LineInputDeviceConfigurationColumnData::BaseViewName = L"LineInputDeviceConfigurationView";
    WideString LineInputDeviceConfigurationColumnData::ViewAliasName = L"lidc";

    WideString LineInputMessageRoutingColumnData::BaseQuery = L"SELECT \r\n"
        L"  limr.[Id], \r\n"
        L"  limr.[RowVersion], \r\n"
        L"  limr.[LineInputDevice], \r\n"
        L"  limr.[Type] \r\n"
        L"FROM [LineInputMessageRoutingView] limr \r\n";
    WideString LineInputMessageRoutingColumnData::BaseViewName = L"LineInputMessageRoutingView";
    WideString LineInputMessageRoutingColumnData::ViewAliasName = L"limr";

    WideString LineInputMessageRoutingDestinationColumnData::BaseQuery = L"SELECT \r\n"
        L"  limrd.[Id], \r\n"
        L"  limrd.[RowVersion], \r\n"
        L"  limrd.[Routing], \r\n"
        L"  limrd.[Listener] \r\n"
        L"FROM [LineInputMessageRoutingDestinationView] limrd \r\n";
    WideString LineInputMessageRoutingDestinationColumnData::BaseViewName = L"LineInputMessageRoutingDestinationView";
    WideString LineInputMessageRoutingDestinationColumnData::ViewAliasName = L"limrd";

    WideString LineInputWhiteListEntryColumnData::BaseQuery = L"SELECT \r\n"
        L"  liwle.[Id], \r\n"
        L"  liwle.[RowVersion], \r\n"
        L"  liwle.[LineInputDevice], \r\n"
        L"  liwle.[HostName], \r\n"
        L"  liwle.[Port] \r\n"
        L"FROM [LineInputWhiteListEntryView] liwle \r\n";
    WideString LineInputWhiteListEntryColumnData::BaseViewName = L"LineInputWhiteListEntryView";
    WideString LineInputWhiteListEntryColumnData::ViewAliasName = L"liwle";

    WideString LogApplicationColumnData::BaseQuery = L"SELECT \r\n"
        L"  la.[Id], \r\n"
        L"  la.[RowVersion], \r\n"
        L"  la.[Name], \r\n"
        L"  la.[Description] \r\n"
        L"FROM [LogApplicationView] la \r\n";
    WideString LogApplicationColumnData::BaseViewName = L"LogApplicationView";
    WideString LogApplicationColumnData::ViewAliasName = L"la";

    WideString LogApplicationConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  lac.[Id], \r\n"
        L"  lac.[RowVersion], \r\n"
        L"  lac.[Application], \r\n"
        L"  lac.[Timestamp], \r\n"
        L"  lac.[Finest], \r\n"
        L"  lac.[Finer], \r\n"
        L"  lac.[Fine], \r\n"
        L"  lac.[Info], \r\n"
        L"  lac.[Notice], \r\n"
        L"  lac.[Warn], \r\n"
        L"  lac.[Error], \r\n"
        L"  lac.[Severe], \r\n"
        L"  lac.[Critical], \r\n"
        L"  lac.[Alert], \r\n"
        L"  lac.[Fatal], \r\n"
        L"  lac.[Emergency] \r\n"
        L"FROM [LogApplicationConfigurationView] lac \r\n";
    WideString LogApplicationConfigurationColumnData::BaseViewName = L"LogApplicationConfigurationView";
    WideString LogApplicationConfigurationColumnData::ViewAliasName = L"lac";

    WideString LogHostColumnData::BaseQuery = L"SELECT \r\n"
        L"  lh.[Id], \r\n"
        L"  lh.[RowVersion], \r\n"
        L"  lh.[ComputerName], \r\n"
        L"  lh.[Description] \r\n"
        L"FROM [LogHostView] lh \r\n";
    WideString LogHostColumnData::BaseViewName = L"LogHostView";
    WideString LogHostColumnData::ViewAliasName = L"lh";

    WideString LogHostConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  lhc.[Id], \r\n"
        L"  lhc.[RowVersion], \r\n"
        L"  lhc.[Host], \r\n"
        L"  lhc.[Timestamp], \r\n"
        L"  lhc.[Finest], \r\n"
        L"  lhc.[Finer], \r\n"
        L"  lhc.[Fine], \r\n"
        L"  lhc.[Info], \r\n"
        L"  lhc.[Notice], \r\n"
        L"  lhc.[Warn], \r\n"
        L"  lhc.[Error], \r\n"
        L"  lhc.[Severe], \r\n"
        L"  lhc.[Critical], \r\n"
        L"  lhc.[Alert], \r\n"
        L"  lhc.[Fatal], \r\n"
        L"  lhc.[Emergency] \r\n"
        L"FROM [LogHostConfigurationView] lhc \r\n";
    WideString LogHostConfigurationColumnData::BaseViewName = L"LogHostConfigurationView";
    WideString LogHostConfigurationColumnData::ViewAliasName = L"lhc";

    WideString LogLocationColumnData::BaseQuery = L"SELECT \r\n"
        L"  ll.[Id], \r\n"
        L"  ll.[RowVersion], \r\n"
        L"  ll.[FileName], \r\n"
        L"  ll.[LineNumber], \r\n"
        L"  ll.[MethodName], \r\n"
        L"  ll.[Namespace], \r\n"
        L"  ll.[ClassName] \r\n"
        L"FROM [LogLocationView] ll \r\n";
    WideString LogLocationColumnData::BaseViewName = L"LogLocationView";
    WideString LogLocationColumnData::ViewAliasName = L"ll";

    WideString LogProcessColumnData::BaseQuery = L"SELECT \r\n"
        L"  lp.[Id], \r\n"
        L"  lp.[RowVersion], \r\n"
        L"  lp.[Application], \r\n"
        L"  lp.[Host], \r\n"
        L"  lp.[Started], \r\n"
        L"  lp.[Stopped], \r\n"
        L"  lp.[ProcessId], \r\n"
        L"  lp.[Identity], \r\n"
        L"  lp.[Path] \r\n"
        L"FROM [LogProcessView] lp \r\n";
    WideString LogProcessColumnData::BaseViewName = L"LogProcessView";
    WideString LogProcessColumnData::ViewAliasName = L"lp";

    WideString LogRecordColumnData::BaseQuery = L"SELECT \r\n"
        L"  lr.[Id], \r\n"
        L"  lr.[RowVersion], \r\n"
        L"  lr.[Thread], \r\n"
        L"  lr.[SequenceNumber], \r\n"
        L"  lr.[Level], \r\n"
        L"  lr.[Timestamp], \r\n"
        L"  lr.[Depth], \r\n"
        L"  lr.[Location], \r\n"
        L"  lr.[Message], \r\n"
        L"  lr.[ExceptionString], \r\n"
        L"  lr.[PropertiesData] \r\n"
        L"FROM [LogRecordView] lr \r\n";
    WideString LogRecordColumnData::BaseViewName = L"LogRecordView";
    WideString LogRecordColumnData::ViewAliasName = L"lr";

    WideString LogThreadColumnData::BaseQuery = L"SELECT \r\n"
        L"  lt.[Id], \r\n"
        L"  lt.[RowVersion], \r\n"
        L"  lt.[Process], \r\n"
        L"  lt.[Started], \r\n"
        L"  lt.[Stopped], \r\n"
        L"  lt.[ThreadId], \r\n"
        L"  lt.[Name] \r\n"
        L"FROM [LogThreadView] lt \r\n";
    WideString LogThreadColumnData::BaseViewName = L"LogThreadView";
    WideString LogThreadColumnData::ViewAliasName = L"lt";

    WideString LogTraceEntryColumnData::BaseQuery = L"SELECT \r\n"
        L"  lte.[Id], \r\n"
        L"  lte.[RowVersion], \r\n"
        L"  lte.[Thread], \r\n"
        L"  lte.[SequenceNumber], \r\n"
        L"  lte.[Location], \r\n"
        L"  lte.[Depth], \r\n"
        L"  lte.[Entered], \r\n"
        L"  lte.[Ended] \r\n"
        L"FROM [LogTraceEntryView] lte \r\n";
    WideString LogTraceEntryColumnData::BaseViewName = L"LogTraceEntryView";
    WideString LogTraceEntryColumnData::ViewAliasName = L"lte";

    WideString MapElementColumnData::BaseQuery = L"SELECT \r\n"
        L"  me.[Id], \r\n"
        L"  me.[RowVersion], \r\n"
        L"  me.[Item], \r\n"
        L"  me.[ElementType], \r\n"
        L"  me.[Latitude], \r\n"
        L"  me.[Longitude], \r\n"
        L"  me.[Angle], \r\n"
        L"  me.[Left], \r\n"
        L"  me.[Top], \r\n"
        L"  me.[Width], \r\n"
        L"  me.[Height], \r\n"
        L"  me.[Label], \r\n"
        L"  me.[Data] \r\n"
        L"FROM [MapElementView] me \r\n";
    WideString MapElementColumnData::BaseViewName = L"MapElementView";
    WideString MapElementColumnData::ViewAliasName = L"me";

    WideString MapInfoColumnData::BaseQuery = L"SELECT \r\n"
        L"  mi.[Id], \r\n"
        L"  mi.[RowVersion], \r\n"
        L"  mi.[Scale], \r\n"
        L"  mi.[Latitude], \r\n"
        L"  mi.[Longitude], \r\n"
        L"  mi.[NorthWestLatitude], \r\n"
        L"  mi.[NorthWestLongitude], \r\n"
        L"  mi.[SouthEastLatitude], \r\n"
        L"  mi.[SouthEastLongitude], \r\n"
        L"  mi.[Image] \r\n"
        L"FROM [MapInfoView] mi \r\n";
    WideString MapInfoColumnData::BaseViewName = L"MapInfoView";
    WideString MapInfoColumnData::ViewAliasName = L"mi";

    WideString MapServiceOptionsColumnData::BaseQuery = L"SELECT \r\n"
        L"  mso.[Id], \r\n"
        L"  mso.[RowVersion], \r\n"
        L"  mso.[Timestamp], \r\n"
        L"  mso.[IpAddress], \r\n"
        L"  mso.[Port], \r\n"
        L"  mso.[ImageScaleFactorX], \r\n"
        L"  mso.[ImageOffsetX], \r\n"
        L"  mso.[ImageScaleFactorY], \r\n"
        L"  mso.[ImageOffsetY] \r\n"
        L"FROM [MapServiceOptionsView] mso \r\n";
    WideString MapServiceOptionsColumnData::BaseViewName = L"MapServiceOptionsView";
    WideString MapServiceOptionsColumnData::ViewAliasName = L"mso";

    WideString MaritimeIdentificationDigitsColumnData::BaseQuery = L"SELECT \r\n"
        L"  mid.[Id], \r\n"
        L"  mid.[RowVersion], \r\n"
        L"  mid.[Code], \r\n"
        L"  mid.[Country] \r\n"
        L"FROM [MaritimeIdentificationDigitsView] mid \r\n";
    WideString MaritimeIdentificationDigitsColumnData::BaseViewName = L"MaritimeIdentificationDigitsView";
    WideString MaritimeIdentificationDigitsColumnData::ViewAliasName = L"mid";

    WideString MediaProxySessionColumnData::BaseQuery = L"SELECT \r\n"
        L"  mps.[Id], \r\n"
        L"  mps.[RowVersion], \r\n"
        L"  mps.[Service], \r\n"
        L"  mps.[Name], \r\n"
        L"  mps.[EnabledTimeseries] \r\n"
        L"FROM [MediaProxySessionView] mps \r\n";
    WideString MediaProxySessionColumnData::BaseViewName = L"MediaProxySessionView";
    WideString MediaProxySessionColumnData::ViewAliasName = L"mps";

    WideString MediaProxySessionFileColumnData::BaseQuery = L"SELECT \r\n"
        L"  mpsf.[Id], \r\n"
        L"  mpsf.[RowVersion], \r\n"
        L"  mpsf.[ProxySession], \r\n"
        L"  mpsf.[Timestamp], \r\n"
        L"  mpsf.[StreamName] \r\n"
        L"FROM [MediaProxySessionFileView] mpsf \r\n";
    WideString MediaProxySessionFileColumnData::BaseViewName = L"MediaProxySessionFileView";
    WideString MediaProxySessionFileColumnData::ViewAliasName = L"mpsf";

    WideString MediaProxySessionOptionsColumnData::BaseQuery = L"SELECT \r\n"
        L"  mpso.[Id], \r\n"
        L"  mpso.[RowVersion], \r\n"
        L"  mpso.[ProxySession], \r\n"
        L"  mpso.[Timestamp], \r\n"
        L"  mpso.[SourceStreamUrl], \r\n"
        L"  mpso.[StreamName], \r\n"
        L"  mpso.[Mode], \r\n"
        L"  mpso.[TunnelOverHTTPPortNumber], \r\n"
        L"  mpso.[Username], \r\n"
        L"  mpso.[Password], \r\n"
        L"  mpso.[RecorderPortNumber], \r\n"
        L"  mpso.[SessionType], \r\n"
        L"  mpso.[MaxFileTime], \r\n"
        L"  mpso.[MaxFileRetention], \r\n"
        L"  mpso.[VideoDirectory] \r\n"
        L"FROM [MediaProxySessionOptionsView] mpso \r\n";
    WideString MediaProxySessionOptionsColumnData::BaseViewName = L"MediaProxySessionOptionsView";
    WideString MediaProxySessionOptionsColumnData::ViewAliasName = L"mpso";

    WideString MediaServiceColumnData::BaseQuery = L"SELECT \r\n"
        L"  ms.[Id], \r\n"
        L"  ms.[RowVersion], \r\n"
        L"  ms.[EnabledTimeseries] \r\n"
        L"FROM [MediaServiceView] ms \r\n";
    WideString MediaServiceColumnData::BaseViewName = L"MediaServiceView";
    WideString MediaServiceColumnData::ViewAliasName = L"ms";

    WideString MediaServiceOptionsColumnData::BaseQuery = L"SELECT \r\n"
        L"  mso.[Id], \r\n"
        L"  mso.[RowVersion], \r\n"
        L"  mso.[MediaService], \r\n"
        L"  mso.[Timestamp], \r\n"
        L"  mso.[RtspPortNumber], \r\n"
        L"  mso.[HttpPortNumber] \r\n"
        L"FROM [MediaServiceOptionsView] mso \r\n";
    WideString MediaServiceOptionsColumnData::BaseViewName = L"MediaServiceOptionsView";
    WideString MediaServiceOptionsColumnData::ViewAliasName = L"mso";

    WideString NamespaceElementColumnData::BaseQuery = L"SELECT \r\n"
        L"  ne.[Id], \r\n"
        L"  ne.[EntityType], \r\n"
        L"  ne.[RowVersion], \r\n"
        L"  ne.[Namespace], \r\n"
        L"  ne.[Name], \r\n"
        L"  ne.[Description] \r\n"
        L"FROM [NamespaceElementView] ne \r\n";
    WideString NamespaceElementColumnData::BaseViewName = L"NamespaceElementView";
    WideString NamespaceElementColumnData::ViewAliasName = L"ne";

    WideString ElementTypeColumnData::BaseQuery = L"SELECT \r\n"
        L"  et.[Id], \r\n"
        L"  et.[EntityType], \r\n"
        L"  et.[RowVersion], \r\n"
        L"  et.[Namespace], \r\n"
        L"  et.[Name], \r\n"
        L"  et.[Description] \r\n"
        L"FROM [ElementTypeView] et \r\n";
    WideString ElementTypeColumnData::BaseViewName = L"ElementTypeView";
    WideString ElementTypeColumnData::ViewAliasName = L"et";

    WideString NamespaceColumnData::BaseQuery = L"SELECT \r\n"
        L"  n.[Id], \r\n"
        L"  n.[EntityType], \r\n"
        L"  n.[RowVersion], \r\n"
        L"  n.[Namespace], \r\n"
        L"  n.[Name], \r\n"
        L"  n.[Description] \r\n"
        L"FROM [NamespaceView] n \r\n";
    WideString NamespaceColumnData::BaseViewName = L"NamespaceView";
    WideString NamespaceColumnData::ViewAliasName = L"n";

    WideString OilSpillColumnData::BaseQuery = L"SELECT \r\n"
        L"  os.[Id], \r\n"
        L"  os.[RowVersion], \r\n"
        L"  os.[OilSpillDetector], \r\n"
        L"  os.[Timestamp], \r\n"
        L"  os.[OilArea], \r\n"
        L"  os.[Shape], \r\n"
        L"  os.[BSI], \r\n"
        L"  os.[Oil], \r\n"
        L"  os.[Trace] \r\n"
        L"FROM [OilSpillView] os \r\n";
    WideString OilSpillColumnData::BaseViewName = L"OilSpillView";
    WideString OilSpillColumnData::ViewAliasName = L"os";

    WideString OilSpillDetectorCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  osdc.[Id], \r\n"
        L"  osdc.[RowVersion], \r\n"
        L"  osdc.[OilSpillDetector], \r\n"
        L"  osdc.[Timestamp], \r\n"
        L"  osdc.[DeviceCommandSourceType], \r\n"
        L"  osdc.[DeviceCommandSourceId], \r\n"
        L"  osdc.[Reply] \r\n"
        L"FROM [OilSpillDetectorCommandView] osdc \r\n";
    WideString OilSpillDetectorCommandColumnData::BaseViewName = L"OilSpillDetectorCommandView";
    WideString OilSpillDetectorCommandColumnData::ViewAliasName = L"osdc";

    WideString OilSpillDetectorCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  osdcr.[Id], \r\n"
        L"  osdcr.[RowVersion], \r\n"
        L"  osdcr.[OilSpillDetector], \r\n"
        L"  osdcr.[Timestamp], \r\n"
        L"  osdcr.[Command], \r\n"
        L"  osdcr.[Status], \r\n"
        L"  osdcr.[Message] \r\n"
        L"FROM [OilSpillDetectorCommandReplyView] osdcr \r\n";
    WideString OilSpillDetectorCommandReplyColumnData::BaseViewName = L"OilSpillDetectorCommandReplyView";
    WideString OilSpillDetectorCommandReplyColumnData::ViewAliasName = L"osdcr";

    WideString OilSpillDetectorConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  osdc.[Id], \r\n"
        L"  osdc.[RowVersion], \r\n"
        L"  osdc.[OilSpillDetector], \r\n"
        L"  osdc.[Timestamp], \r\n"
        L"  osdc.[Range], \r\n"
        L"  osdc.[StartAngle], \r\n"
        L"  osdc.[EndAngle], \r\n"
        L"  osdc.[StartRange], \r\n"
        L"  osdc.[EndRange], \r\n"
        L"  osdc.[UpdateRate], \r\n"
        L"  osdc.[StatusSendTime], \r\n"
        L"  osdc.[DrawBorder], \r\n"
        L"  osdc.[SendToServer], \r\n"
        L"  osdc.[Directory], \r\n"
        L"  osdc.[TransparentWater], \r\n"
        L"  osdc.[SavePictures], \r\n"
        L"  osdc.[SendAsTarget], \r\n"
        L"  osdc.[WriteLog], \r\n"
        L"  osdc.[TargetFilePrefix], \r\n"
        L"  osdc.[TargetMMSI], \r\n"
        L"  osdc.[Latitude], \r\n"
        L"  osdc.[Longitude], \r\n"
        L"  osdc.[TestSourceEnabled], \r\n"
        L"  osdc.[ProxyServer], \r\n"
        L"  osdc.[UseProxyServer], \r\n"
        L"  osdc.[Colors] \r\n"
        L"FROM [OilSpillDetectorConfigurationView] osdc \r\n";
    WideString OilSpillDetectorConfigurationColumnData::BaseViewName = L"OilSpillDetectorConfigurationView";
    WideString OilSpillDetectorConfigurationColumnData::ViewAliasName = L"osdc";

    WideString Position2DTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  p2dv.[Id], \r\n"
        L"  p2dv.[RowVersion], \r\n"
        L"  p2dv.[Timeseries], \r\n"
        L"  p2dv.[Timestamp], \r\n"
        L"  p2dv.[X], \r\n"
        L"  p2dv.[Y] \r\n"
        L"FROM [Position2DTimeseriesValueView] p2dv \r\n";
    WideString Position2DTimeseriesValueColumnData::BaseViewName = L"Position2DTimeseriesValueView";
    WideString Position2DTimeseriesValueColumnData::ViewAliasName = L"p2dv";

    WideString Position3DTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  p3dv.[Id], \r\n"
        L"  p3dv.[RowVersion], \r\n"
        L"  p3dv.[Timeseries], \r\n"
        L"  p3dv.[Timestamp], \r\n"
        L"  p3dv.[X], \r\n"
        L"  p3dv.[Y], \r\n"
        L"  p3dv.[Z] \r\n"
        L"FROM [Position3DTimeseriesValueView] p3dv \r\n";
    WideString Position3DTimeseriesValueColumnData::BaseViewName = L"Position3DTimeseriesValueView";
    WideString Position3DTimeseriesValueColumnData::ViewAliasName = L"p3dv";

    WideString ProcessTrackValueResultColumnData::BaseQuery = L"SELECT \r\n"
        L"  ptvr.[Id], \r\n"
        L"  ptvr.[RowVersion], \r\n"
        L"  ptvr.[CreatedNewTrack], \r\n"
        L"  ptvr.[TrackId] \r\n"
        L"FROM [ProcessTrackValueResultView] ptvr \r\n";
    WideString ProcessTrackValueResultColumnData::BaseViewName = L"ProcessTrackValueResultView";
    WideString ProcessTrackValueResultColumnData::ViewAliasName = L"ptvr";

    WideString PropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  p.[Id], \r\n"
        L"  p.[EntityType], \r\n"
        L"  p.[RowVersion], \r\n"
        L"  p.[Element], \r\n"
        L"  p.[Definition] \r\n"
        L"FROM [PropertyView] p \r\n";
    WideString PropertyColumnData::BaseViewName = L"PropertyView";
    WideString PropertyColumnData::ViewAliasName = L"p";

    WideString BinaryPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  bp.[Id], \r\n"
        L"  bp.[EntityType], \r\n"
        L"  bp.[RowVersion], \r\n"
        L"  bp.[Element], \r\n"
        L"  bp.[Definition], \r\n"
        L"  bp.[Value] \r\n"
        L"FROM [BinaryPropertyView] bp \r\n";
    WideString BinaryPropertyColumnData::BaseViewName = L"BinaryPropertyView";
    WideString BinaryPropertyColumnData::ViewAliasName = L"bp";

    WideString BooleanPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  bop.[Id], \r\n"
        L"  bop.[EntityType], \r\n"
        L"  bop.[RowVersion], \r\n"
        L"  bop.[Element], \r\n"
        L"  bop.[Definition], \r\n"
        L"  bop.[Value] \r\n"
        L"FROM [BooleanPropertyView] bop \r\n";
    WideString BooleanPropertyColumnData::BaseViewName = L"BooleanPropertyView";
    WideString BooleanPropertyColumnData::ViewAliasName = L"bop";

    WideString BytePropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  byp.[Id], \r\n"
        L"  byp.[EntityType], \r\n"
        L"  byp.[RowVersion], \r\n"
        L"  byp.[Element], \r\n"
        L"  byp.[Definition], \r\n"
        L"  byp.[Value] \r\n"
        L"FROM [BytePropertyView] byp \r\n";
    WideString BytePropertyColumnData::BaseViewName = L"BytePropertyView";
    WideString BytePropertyColumnData::ViewAliasName = L"byp";

    WideString DateTimePropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  dtp.[Id], \r\n"
        L"  dtp.[EntityType], \r\n"
        L"  dtp.[RowVersion], \r\n"
        L"  dtp.[Element], \r\n"
        L"  dtp.[Definition], \r\n"
        L"  dtp.[Value] \r\n"
        L"FROM [DateTimePropertyView] dtp \r\n";
    WideString DateTimePropertyColumnData::BaseViewName = L"DateTimePropertyView";
    WideString DateTimePropertyColumnData::ViewAliasName = L"dtp";

    WideString DoublePropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  dp.[Id], \r\n"
        L"  dp.[EntityType], \r\n"
        L"  dp.[RowVersion], \r\n"
        L"  dp.[Element], \r\n"
        L"  dp.[Definition], \r\n"
        L"  dp.[Value] \r\n"
        L"FROM [DoublePropertyView] dp \r\n";
    WideString DoublePropertyColumnData::BaseViewName = L"DoublePropertyView";
    WideString DoublePropertyColumnData::ViewAliasName = L"dp";

    WideString GuidPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  gp.[Id], \r\n"
        L"  gp.[EntityType], \r\n"
        L"  gp.[RowVersion], \r\n"
        L"  gp.[Element], \r\n"
        L"  gp.[Definition], \r\n"
        L"  gp.[Value] \r\n"
        L"FROM [GuidPropertyView] gp \r\n";
    WideString GuidPropertyColumnData::BaseViewName = L"GuidPropertyView";
    WideString GuidPropertyColumnData::ViewAliasName = L"gp";

    WideString Int16PropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  i16p.[Id], \r\n"
        L"  i16p.[EntityType], \r\n"
        L"  i16p.[RowVersion], \r\n"
        L"  i16p.[Element], \r\n"
        L"  i16p.[Definition], \r\n"
        L"  i16p.[Value] \r\n"
        L"FROM [Int16PropertyView] i16p \r\n";
    WideString Int16PropertyColumnData::BaseViewName = L"Int16PropertyView";
    WideString Int16PropertyColumnData::ViewAliasName = L"i16p";

    WideString Int32PropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  i32p.[Id], \r\n"
        L"  i32p.[EntityType], \r\n"
        L"  i32p.[RowVersion], \r\n"
        L"  i32p.[Element], \r\n"
        L"  i32p.[Definition], \r\n"
        L"  i32p.[Value] \r\n"
        L"FROM [Int32PropertyView] i32p \r\n";
    WideString Int32PropertyColumnData::BaseViewName = L"Int32PropertyView";
    WideString Int32PropertyColumnData::ViewAliasName = L"i32p";

    WideString Int64PropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  i64p.[Id], \r\n"
        L"  i64p.[EntityType], \r\n"
        L"  i64p.[RowVersion], \r\n"
        L"  i64p.[Element], \r\n"
        L"  i64p.[Definition], \r\n"
        L"  i64p.[Value] \r\n"
        L"FROM [Int64PropertyView] i64p \r\n";
    WideString Int64PropertyColumnData::BaseViewName = L"Int64PropertyView";
    WideString Int64PropertyColumnData::ViewAliasName = L"i64p";

    WideString ReferencePropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  rp.[Id], \r\n"
        L"  rp.[EntityType], \r\n"
        L"  rp.[RowVersion], \r\n"
        L"  rp.[Element], \r\n"
        L"  rp.[Definition], \r\n"
        L"  rp.[Value] \r\n"
        L"FROM [ReferencePropertyView] rp \r\n";
    WideString ReferencePropertyColumnData::BaseViewName = L"ReferencePropertyView";
    WideString ReferencePropertyColumnData::ViewAliasName = L"rp";

    WideString SBytePropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  sp.[Id], \r\n"
        L"  sp.[EntityType], \r\n"
        L"  sp.[RowVersion], \r\n"
        L"  sp.[Element], \r\n"
        L"  sp.[Definition], \r\n"
        L"  sp.[Value] \r\n"
        L"FROM [SBytePropertyView] sp \r\n";
    WideString SBytePropertyColumnData::BaseViewName = L"SBytePropertyView";
    WideString SBytePropertyColumnData::ViewAliasName = L"sp";

    WideString SinglePropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  sip.[Id], \r\n"
        L"  sip.[EntityType], \r\n"
        L"  sip.[RowVersion], \r\n"
        L"  sip.[Element], \r\n"
        L"  sip.[Definition], \r\n"
        L"  sip.[Value] \r\n"
        L"FROM [SinglePropertyView] sip \r\n";
    WideString SinglePropertyColumnData::BaseViewName = L"SinglePropertyView";
    WideString SinglePropertyColumnData::ViewAliasName = L"sip";

    WideString StringPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  stp.[Id], \r\n"
        L"  stp.[EntityType], \r\n"
        L"  stp.[RowVersion], \r\n"
        L"  stp.[Element], \r\n"
        L"  stp.[Definition], \r\n"
        L"  stp.[Value] \r\n"
        L"FROM [StringPropertyView] stp \r\n";
    WideString StringPropertyColumnData::BaseViewName = L"StringPropertyView";
    WideString StringPropertyColumnData::ViewAliasName = L"stp";

    WideString TimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  tp.[Id], \r\n"
        L"  tp.[EntityType], \r\n"
        L"  tp.[RowVersion], \r\n"
        L"  tp.[Element], \r\n"
        L"  tp.[Definition] \r\n"
        L"FROM [TimeseriesPropertyView] tp \r\n";
    WideString TimeseriesPropertyColumnData::BaseViewName = L"TimeseriesPropertyView";
    WideString TimeseriesPropertyColumnData::ViewAliasName = L"tp";

    WideString BinaryTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  btp.[Id], \r\n"
        L"  btp.[EntityType], \r\n"
        L"  btp.[RowVersion], \r\n"
        L"  btp.[Element], \r\n"
        L"  btp.[Definition], \r\n"
        L"  btp.[Timeseries] \r\n"
        L"FROM [BinaryTimeseriesPropertyView] btp \r\n";
    WideString BinaryTimeseriesPropertyColumnData::BaseViewName = L"BinaryTimeseriesPropertyView";
    WideString BinaryTimeseriesPropertyColumnData::ViewAliasName = L"btp";

    WideString BooleanTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  botp.[Id], \r\n"
        L"  botp.[EntityType], \r\n"
        L"  botp.[RowVersion], \r\n"
        L"  botp.[Element], \r\n"
        L"  botp.[Definition], \r\n"
        L"  botp.[Timeseries] \r\n"
        L"FROM [BooleanTimeseriesPropertyView] botp \r\n";
    WideString BooleanTimeseriesPropertyColumnData::BaseViewName = L"BooleanTimeseriesPropertyView";
    WideString BooleanTimeseriesPropertyColumnData::ViewAliasName = L"botp";

    WideString ByteTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  bytp.[Id], \r\n"
        L"  bytp.[EntityType], \r\n"
        L"  bytp.[RowVersion], \r\n"
        L"  bytp.[Element], \r\n"
        L"  bytp.[Definition], \r\n"
        L"  bytp.[Timeseries] \r\n"
        L"FROM [ByteTimeseriesPropertyView] bytp \r\n";
    WideString ByteTimeseriesPropertyColumnData::BaseViewName = L"ByteTimeseriesPropertyView";
    WideString ByteTimeseriesPropertyColumnData::ViewAliasName = L"bytp";

    WideString DateTimeTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  dttp.[Id], \r\n"
        L"  dttp.[EntityType], \r\n"
        L"  dttp.[RowVersion], \r\n"
        L"  dttp.[Element], \r\n"
        L"  dttp.[Definition], \r\n"
        L"  dttp.[Timeseries] \r\n"
        L"FROM [DateTimeTimeseriesPropertyView] dttp \r\n";
    WideString DateTimeTimeseriesPropertyColumnData::BaseViewName = L"DateTimeTimeseriesPropertyView";
    WideString DateTimeTimeseriesPropertyColumnData::ViewAliasName = L"dttp";

    WideString DoubleTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  dotp.[Id], \r\n"
        L"  dotp.[EntityType], \r\n"
        L"  dotp.[RowVersion], \r\n"
        L"  dotp.[Element], \r\n"
        L"  dotp.[Definition], \r\n"
        L"  dotp.[Timeseries] \r\n"
        L"FROM [DoubleTimeseriesPropertyView] dotp \r\n";
    WideString DoubleTimeseriesPropertyColumnData::BaseViewName = L"DoubleTimeseriesPropertyView";
    WideString DoubleTimeseriesPropertyColumnData::ViewAliasName = L"dotp";

    WideString GuidTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  gtp.[Id], \r\n"
        L"  gtp.[EntityType], \r\n"
        L"  gtp.[RowVersion], \r\n"
        L"  gtp.[Element], \r\n"
        L"  gtp.[Definition], \r\n"
        L"  gtp.[Timeseries] \r\n"
        L"FROM [GuidTimeseriesPropertyView] gtp \r\n";
    WideString GuidTimeseriesPropertyColumnData::BaseViewName = L"GuidTimeseriesPropertyView";
    WideString GuidTimeseriesPropertyColumnData::ViewAliasName = L"gtp";

    WideString Int16TimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  i16tp.[Id], \r\n"
        L"  i16tp.[EntityType], \r\n"
        L"  i16tp.[RowVersion], \r\n"
        L"  i16tp.[Element], \r\n"
        L"  i16tp.[Definition], \r\n"
        L"  i16tp.[Timeseries] \r\n"
        L"FROM [Int16TimeseriesPropertyView] i16tp \r\n";
    WideString Int16TimeseriesPropertyColumnData::BaseViewName = L"Int16TimeseriesPropertyView";
    WideString Int16TimeseriesPropertyColumnData::ViewAliasName = L"i16tp";

    WideString Int32TimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  i32tp.[Id], \r\n"
        L"  i32tp.[EntityType], \r\n"
        L"  i32tp.[RowVersion], \r\n"
        L"  i32tp.[Element], \r\n"
        L"  i32tp.[Definition], \r\n"
        L"  i32tp.[Timeseries] \r\n"
        L"FROM [Int32TimeseriesPropertyView] i32tp \r\n";
    WideString Int32TimeseriesPropertyColumnData::BaseViewName = L"Int32TimeseriesPropertyView";
    WideString Int32TimeseriesPropertyColumnData::ViewAliasName = L"i32tp";

    WideString Int64TimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  i64tp.[Id], \r\n"
        L"  i64tp.[EntityType], \r\n"
        L"  i64tp.[RowVersion], \r\n"
        L"  i64tp.[Element], \r\n"
        L"  i64tp.[Definition], \r\n"
        L"  i64tp.[Timeseries] \r\n"
        L"FROM [Int64TimeseriesPropertyView] i64tp \r\n";
    WideString Int64TimeseriesPropertyColumnData::BaseViewName = L"Int64TimeseriesPropertyView";
    WideString Int64TimeseriesPropertyColumnData::ViewAliasName = L"i64tp";

    WideString ReferenceTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  rtp.[Id], \r\n"
        L"  rtp.[EntityType], \r\n"
        L"  rtp.[RowVersion], \r\n"
        L"  rtp.[Element], \r\n"
        L"  rtp.[Definition], \r\n"
        L"  rtp.[Timeseries] \r\n"
        L"FROM [ReferenceTimeseriesPropertyView] rtp \r\n";
    WideString ReferenceTimeseriesPropertyColumnData::BaseViewName = L"ReferenceTimeseriesPropertyView";
    WideString ReferenceTimeseriesPropertyColumnData::ViewAliasName = L"rtp";

    WideString SByteTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  sbtp.[Id], \r\n"
        L"  sbtp.[EntityType], \r\n"
        L"  sbtp.[RowVersion], \r\n"
        L"  sbtp.[Element], \r\n"
        L"  sbtp.[Definition], \r\n"
        L"  sbtp.[Timeseries] \r\n"
        L"FROM [SByteTimeseriesPropertyView] sbtp \r\n";
    WideString SByteTimeseriesPropertyColumnData::BaseViewName = L"SByteTimeseriesPropertyView";
    WideString SByteTimeseriesPropertyColumnData::ViewAliasName = L"sbtp";

    WideString SingleTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  sitp.[Id], \r\n"
        L"  sitp.[EntityType], \r\n"
        L"  sitp.[RowVersion], \r\n"
        L"  sitp.[Element], \r\n"
        L"  sitp.[Definition], \r\n"
        L"  sitp.[Timeseries] \r\n"
        L"FROM [SingleTimeseriesPropertyView] sitp \r\n";
    WideString SingleTimeseriesPropertyColumnData::BaseViewName = L"SingleTimeseriesPropertyView";
    WideString SingleTimeseriesPropertyColumnData::ViewAliasName = L"sitp";

    WideString StringTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  sttp.[Id], \r\n"
        L"  sttp.[EntityType], \r\n"
        L"  sttp.[RowVersion], \r\n"
        L"  sttp.[Element], \r\n"
        L"  sttp.[Definition], \r\n"
        L"  sttp.[Timeseries] \r\n"
        L"FROM [StringTimeseriesPropertyView] sttp \r\n";
    WideString StringTimeseriesPropertyColumnData::BaseViewName = L"StringTimeseriesPropertyView";
    WideString StringTimeseriesPropertyColumnData::ViewAliasName = L"sttp";

    WideString TimeSpanTimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  tstp.[Id], \r\n"
        L"  tstp.[EntityType], \r\n"
        L"  tstp.[RowVersion], \r\n"
        L"  tstp.[Element], \r\n"
        L"  tstp.[Definition], \r\n"
        L"  tstp.[Timeseries] \r\n"
        L"FROM [TimeSpanTimeseriesPropertyView] tstp \r\n";
    WideString TimeSpanTimeseriesPropertyColumnData::BaseViewName = L"TimeSpanTimeseriesPropertyView";
    WideString TimeSpanTimeseriesPropertyColumnData::ViewAliasName = L"tstp";

    WideString UInt16TimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  u16tp.[Id], \r\n"
        L"  u16tp.[EntityType], \r\n"
        L"  u16tp.[RowVersion], \r\n"
        L"  u16tp.[Element], \r\n"
        L"  u16tp.[Definition], \r\n"
        L"  u16tp.[Timeseries] \r\n"
        L"FROM [UInt16TimeseriesPropertyView] u16tp \r\n";
    WideString UInt16TimeseriesPropertyColumnData::BaseViewName = L"UInt16TimeseriesPropertyView";
    WideString UInt16TimeseriesPropertyColumnData::ViewAliasName = L"u16tp";

    WideString UInt32TimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  u32tp.[Id], \r\n"
        L"  u32tp.[EntityType], \r\n"
        L"  u32tp.[RowVersion], \r\n"
        L"  u32tp.[Element], \r\n"
        L"  u32tp.[Definition], \r\n"
        L"  u32tp.[Timeseries] \r\n"
        L"FROM [UInt32TimeseriesPropertyView] u32tp \r\n";
    WideString UInt32TimeseriesPropertyColumnData::BaseViewName = L"UInt32TimeseriesPropertyView";
    WideString UInt32TimeseriesPropertyColumnData::ViewAliasName = L"u32tp";

    WideString UInt64TimeseriesPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  u64tp.[Id], \r\n"
        L"  u64tp.[EntityType], \r\n"
        L"  u64tp.[RowVersion], \r\n"
        L"  u64tp.[Element], \r\n"
        L"  u64tp.[Definition], \r\n"
        L"  u64tp.[Timeseries] \r\n"
        L"FROM [UInt64TimeseriesPropertyView] u64tp \r\n";
    WideString UInt64TimeseriesPropertyColumnData::BaseViewName = L"UInt64TimeseriesPropertyView";
    WideString UInt64TimeseriesPropertyColumnData::ViewAliasName = L"u64tp";

    WideString TimeSpanPropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  tsp.[Id], \r\n"
        L"  tsp.[EntityType], \r\n"
        L"  tsp.[RowVersion], \r\n"
        L"  tsp.[Element], \r\n"
        L"  tsp.[Definition], \r\n"
        L"  tsp.[Value] \r\n"
        L"FROM [TimeSpanPropertyView] tsp \r\n";
    WideString TimeSpanPropertyColumnData::BaseViewName = L"TimeSpanPropertyView";
    WideString TimeSpanPropertyColumnData::ViewAliasName = L"tsp";

    WideString UInt16PropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  u16p.[Id], \r\n"
        L"  u16p.[EntityType], \r\n"
        L"  u16p.[RowVersion], \r\n"
        L"  u16p.[Element], \r\n"
        L"  u16p.[Definition], \r\n"
        L"  u16p.[Value] \r\n"
        L"FROM [UInt16PropertyView] u16p \r\n";
    WideString UInt16PropertyColumnData::BaseViewName = L"UInt16PropertyView";
    WideString UInt16PropertyColumnData::ViewAliasName = L"u16p";

    WideString UInt32PropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  u32p.[Id], \r\n"
        L"  u32p.[EntityType], \r\n"
        L"  u32p.[RowVersion], \r\n"
        L"  u32p.[Element], \r\n"
        L"  u32p.[Definition], \r\n"
        L"  u32p.[Value] \r\n"
        L"FROM [UInt32PropertyView] u32p \r\n";
    WideString UInt32PropertyColumnData::BaseViewName = L"UInt32PropertyView";
    WideString UInt32PropertyColumnData::ViewAliasName = L"u32p";

    WideString UInt64PropertyColumnData::BaseQuery = L"SELECT \r\n"
        L"  u64p.[Id], \r\n"
        L"  u64p.[EntityType], \r\n"
        L"  u64p.[RowVersion], \r\n"
        L"  u64p.[Element], \r\n"
        L"  u64p.[Definition], \r\n"
        L"  u64p.[Value] \r\n"
        L"FROM [UInt64PropertyView] u64p \r\n";
    WideString UInt64PropertyColumnData::BaseViewName = L"UInt64PropertyView";
    WideString UInt64PropertyColumnData::ViewAliasName = L"u64p";

    WideString PropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  pd.[Id], \r\n"
        L"  pd.[EntityType], \r\n"
        L"  pd.[RowVersion], \r\n"
        L"  pd.[ElementType], \r\n"
        L"  pd.[Name], \r\n"
        L"  pd.[Description] \r\n"
        L"FROM [PropertyDefinitionView] pd \r\n";
    WideString PropertyDefinitionColumnData::BaseViewName = L"PropertyDefinitionView";
    WideString PropertyDefinitionColumnData::ViewAliasName = L"pd";

    WideString BinaryPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  bpd.[Id], \r\n"
        L"  bpd.[EntityType], \r\n"
        L"  bpd.[RowVersion], \r\n"
        L"  bpd.[ElementType], \r\n"
        L"  bpd.[Name], \r\n"
        L"  bpd.[Description], \r\n"
        L"  bpd.[DefaultValue] \r\n"
        L"FROM [BinaryPropertyDefinitionView] bpd \r\n";
    WideString BinaryPropertyDefinitionColumnData::BaseViewName = L"BinaryPropertyDefinitionView";
    WideString BinaryPropertyDefinitionColumnData::ViewAliasName = L"bpd";

    WideString BooleanPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  bopd.[Id], \r\n"
        L"  bopd.[EntityType], \r\n"
        L"  bopd.[RowVersion], \r\n"
        L"  bopd.[ElementType], \r\n"
        L"  bopd.[Name], \r\n"
        L"  bopd.[DefaultValue], \r\n"
        L"  bopd.[Description] \r\n"
        L"FROM [BooleanPropertyDefinitionView] bopd \r\n";
    WideString BooleanPropertyDefinitionColumnData::BaseViewName = L"BooleanPropertyDefinitionView";
    WideString BooleanPropertyDefinitionColumnData::ViewAliasName = L"bopd";

    WideString BytePropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  bypd.[Id], \r\n"
        L"  bypd.[EntityType], \r\n"
        L"  bypd.[RowVersion], \r\n"
        L"  bypd.[ElementType], \r\n"
        L"  bypd.[Name], \r\n"
        L"  bypd.[DefaultValue], \r\n"
        L"  bypd.[MinValue], \r\n"
        L"  bypd.[MaxValue], \r\n"
        L"  bypd.[Description] \r\n"
        L"FROM [BytePropertyDefinitionView] bypd \r\n";
    WideString BytePropertyDefinitionColumnData::BaseViewName = L"BytePropertyDefinitionView";
    WideString BytePropertyDefinitionColumnData::ViewAliasName = L"bypd";

    WideString DateTimePropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  dtpd.[Id], \r\n"
        L"  dtpd.[EntityType], \r\n"
        L"  dtpd.[RowVersion], \r\n"
        L"  dtpd.[ElementType], \r\n"
        L"  dtpd.[Name], \r\n"
        L"  dtpd.[DefaultValue], \r\n"
        L"  dtpd.[MinValue], \r\n"
        L"  dtpd.[MaxValue], \r\n"
        L"  dtpd.[Description] \r\n"
        L"FROM [DateTimePropertyDefinitionView] dtpd \r\n";
    WideString DateTimePropertyDefinitionColumnData::BaseViewName = L"DateTimePropertyDefinitionView";
    WideString DateTimePropertyDefinitionColumnData::ViewAliasName = L"dtpd";

    WideString DoublePropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  dpd.[Id], \r\n"
        L"  dpd.[EntityType], \r\n"
        L"  dpd.[RowVersion], \r\n"
        L"  dpd.[ElementType], \r\n"
        L"  dpd.[Name], \r\n"
        L"  dpd.[DefaultValue], \r\n"
        L"  dpd.[MinValue], \r\n"
        L"  dpd.[MaxValue], \r\n"
        L"  dpd.[Description] \r\n"
        L"FROM [DoublePropertyDefinitionView] dpd \r\n";
    WideString DoublePropertyDefinitionColumnData::BaseViewName = L"DoublePropertyDefinitionView";
    WideString DoublePropertyDefinitionColumnData::ViewAliasName = L"dpd";

    WideString GuidPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  gpd.[Id], \r\n"
        L"  gpd.[EntityType], \r\n"
        L"  gpd.[RowVersion], \r\n"
        L"  gpd.[ElementType], \r\n"
        L"  gpd.[Name], \r\n"
        L"  gpd.[DefaultValue], \r\n"
        L"  gpd.[Description] \r\n"
        L"FROM [GuidPropertyDefinitionView] gpd \r\n";
    WideString GuidPropertyDefinitionColumnData::BaseViewName = L"GuidPropertyDefinitionView";
    WideString GuidPropertyDefinitionColumnData::ViewAliasName = L"gpd";

    WideString Int16PropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  i16pd.[Id], \r\n"
        L"  i16pd.[EntityType], \r\n"
        L"  i16pd.[RowVersion], \r\n"
        L"  i16pd.[ElementType], \r\n"
        L"  i16pd.[Name], \r\n"
        L"  i16pd.[DefaultValue], \r\n"
        L"  i16pd.[MinValue], \r\n"
        L"  i16pd.[MaxValue], \r\n"
        L"  i16pd.[Description] \r\n"
        L"FROM [Int16PropertyDefinitionView] i16pd \r\n";
    WideString Int16PropertyDefinitionColumnData::BaseViewName = L"Int16PropertyDefinitionView";
    WideString Int16PropertyDefinitionColumnData::ViewAliasName = L"i16pd";

    WideString Int32PropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  i32pd.[Id], \r\n"
        L"  i32pd.[EntityType], \r\n"
        L"  i32pd.[RowVersion], \r\n"
        L"  i32pd.[ElementType], \r\n"
        L"  i32pd.[Name], \r\n"
        L"  i32pd.[DefaultValue], \r\n"
        L"  i32pd.[MinValue], \r\n"
        L"  i32pd.[MaxValue], \r\n"
        L"  i32pd.[Description] \r\n"
        L"FROM [Int32PropertyDefinitionView] i32pd \r\n";
    WideString Int32PropertyDefinitionColumnData::BaseViewName = L"Int32PropertyDefinitionView";
    WideString Int32PropertyDefinitionColumnData::ViewAliasName = L"i32pd";

    WideString Int64PropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  i64pd.[Id], \r\n"
        L"  i64pd.[EntityType], \r\n"
        L"  i64pd.[RowVersion], \r\n"
        L"  i64pd.[ElementType], \r\n"
        L"  i64pd.[Name], \r\n"
        L"  i64pd.[DefaultValue], \r\n"
        L"  i64pd.[MinValue], \r\n"
        L"  i64pd.[MaxValue], \r\n"
        L"  i64pd.[Description] \r\n"
        L"FROM [Int64PropertyDefinitionView] i64pd \r\n";
    WideString Int64PropertyDefinitionColumnData::BaseViewName = L"Int64PropertyDefinitionView";
    WideString Int64PropertyDefinitionColumnData::ViewAliasName = L"i64pd";

    WideString ReferencePropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  rpd.[Id], \r\n"
        L"  rpd.[EntityType], \r\n"
        L"  rpd.[RowVersion], \r\n"
        L"  rpd.[ElementType], \r\n"
        L"  rpd.[Name], \r\n"
        L"  rpd.[DefaultValue], \r\n"
        L"  rpd.[ReferencedElementType], \r\n"
        L"  rpd.[Description] \r\n"
        L"FROM [ReferencePropertyDefinitionView] rpd \r\n";
    WideString ReferencePropertyDefinitionColumnData::BaseViewName = L"ReferencePropertyDefinitionView";
    WideString ReferencePropertyDefinitionColumnData::ViewAliasName = L"rpd";

    WideString SBytePropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  sbpd.[Id], \r\n"
        L"  sbpd.[EntityType], \r\n"
        L"  sbpd.[RowVersion], \r\n"
        L"  sbpd.[ElementType], \r\n"
        L"  sbpd.[Name], \r\n"
        L"  sbpd.[DefaultValue], \r\n"
        L"  sbpd.[MinValue], \r\n"
        L"  sbpd.[MaxValue], \r\n"
        L"  sbpd.[Description] \r\n"
        L"FROM [SBytePropertyDefinitionView] sbpd \r\n";
    WideString SBytePropertyDefinitionColumnData::BaseViewName = L"SBytePropertyDefinitionView";
    WideString SBytePropertyDefinitionColumnData::ViewAliasName = L"sbpd";

    WideString SinglePropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  sipd.[Id], \r\n"
        L"  sipd.[EntityType], \r\n"
        L"  sipd.[RowVersion], \r\n"
        L"  sipd.[ElementType], \r\n"
        L"  sipd.[Name], \r\n"
        L"  sipd.[DefaultValue], \r\n"
        L"  sipd.[MinValue], \r\n"
        L"  sipd.[MaxValue], \r\n"
        L"  sipd.[Description] \r\n"
        L"FROM [SinglePropertyDefinitionView] sipd \r\n";
    WideString SinglePropertyDefinitionColumnData::BaseViewName = L"SinglePropertyDefinitionView";
    WideString SinglePropertyDefinitionColumnData::ViewAliasName = L"sipd";

    WideString StringPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  stpd.[Id], \r\n"
        L"  stpd.[EntityType], \r\n"
        L"  stpd.[RowVersion], \r\n"
        L"  stpd.[ElementType], \r\n"
        L"  stpd.[Name], \r\n"
        L"  stpd.[DefaultValue], \r\n"
        L"  stpd.[Pattern], \r\n"
        L"  stpd.[Description] \r\n"
        L"FROM [StringPropertyDefinitionView] stpd \r\n";
    WideString StringPropertyDefinitionColumnData::BaseViewName = L"StringPropertyDefinitionView";
    WideString StringPropertyDefinitionColumnData::ViewAliasName = L"stpd";

    WideString TimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  tpd.[Id], \r\n"
        L"  tpd.[EntityType], \r\n"
        L"  tpd.[RowVersion], \r\n"
        L"  tpd.[ElementType], \r\n"
        L"  tpd.[Name], \r\n"
        L"  tpd.[Description] \r\n"
        L"FROM [TimeseriesPropertyDefinitionView] tpd \r\n";
    WideString TimeseriesPropertyDefinitionColumnData::BaseViewName = L"TimeseriesPropertyDefinitionView";
    WideString TimeseriesPropertyDefinitionColumnData::ViewAliasName = L"tpd";

    WideString BinaryTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  btpd.[Id], \r\n"
        L"  btpd.[EntityType], \r\n"
        L"  btpd.[RowVersion], \r\n"
        L"  btpd.[ElementType], \r\n"
        L"  btpd.[Name], \r\n"
        L"  btpd.[Description] \r\n"
        L"FROM [BinaryTimeseriesPropertyDefinitionView] btpd \r\n";
    WideString BinaryTimeseriesPropertyDefinitionColumnData::BaseViewName = L"BinaryTimeseriesPropertyDefinitionView";
    WideString BinaryTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"btpd";

    WideString BooleanTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  botpd.[Id], \r\n"
        L"  botpd.[EntityType], \r\n"
        L"  botpd.[RowVersion], \r\n"
        L"  botpd.[ElementType], \r\n"
        L"  botpd.[Name], \r\n"
        L"  botpd.[Description] \r\n"
        L"FROM [BooleanTimeseriesPropertyDefinitionView] botpd \r\n";
    WideString BooleanTimeseriesPropertyDefinitionColumnData::BaseViewName = L"BooleanTimeseriesPropertyDefinitionView";
    WideString BooleanTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"botpd";

    WideString ByteTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  bytpd.[Id], \r\n"
        L"  bytpd.[EntityType], \r\n"
        L"  bytpd.[RowVersion], \r\n"
        L"  bytpd.[ElementType], \r\n"
        L"  bytpd.[Name], \r\n"
        L"  bytpd.[MinValue], \r\n"
        L"  bytpd.[MaxValue], \r\n"
        L"  bytpd.[Description] \r\n"
        L"FROM [ByteTimeseriesPropertyDefinitionView] bytpd \r\n";
    WideString ByteTimeseriesPropertyDefinitionColumnData::BaseViewName = L"ByteTimeseriesPropertyDefinitionView";
    WideString ByteTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"bytpd";

    WideString DateTimeTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  dttpd.[Id], \r\n"
        L"  dttpd.[EntityType], \r\n"
        L"  dttpd.[RowVersion], \r\n"
        L"  dttpd.[ElementType], \r\n"
        L"  dttpd.[Name], \r\n"
        L"  dttpd.[MinValue], \r\n"
        L"  dttpd.[MaxValue], \r\n"
        L"  dttpd.[Description] \r\n"
        L"FROM [DateTimeTimeseriesPropertyDefinitionView] dttpd \r\n";
    WideString DateTimeTimeseriesPropertyDefinitionColumnData::BaseViewName = L"DateTimeTimeseriesPropertyDefinitionView";
    WideString DateTimeTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"dttpd";

    WideString DoubleTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  dotpd.[Id], \r\n"
        L"  dotpd.[EntityType], \r\n"
        L"  dotpd.[RowVersion], \r\n"
        L"  dotpd.[ElementType], \r\n"
        L"  dotpd.[Name], \r\n"
        L"  dotpd.[MinValue], \r\n"
        L"  dotpd.[MaxValue], \r\n"
        L"  dotpd.[Description] \r\n"
        L"FROM [DoubleTimeseriesPropertyDefinitionView] dotpd \r\n";
    WideString DoubleTimeseriesPropertyDefinitionColumnData::BaseViewName = L"DoubleTimeseriesPropertyDefinitionView";
    WideString DoubleTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"dotpd";

    WideString GuidTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  gtpd.[Id], \r\n"
        L"  gtpd.[EntityType], \r\n"
        L"  gtpd.[RowVersion], \r\n"
        L"  gtpd.[ElementType], \r\n"
        L"  gtpd.[Name], \r\n"
        L"  gtpd.[Description] \r\n"
        L"FROM [GuidTimeseriesPropertyDefinitionView] gtpd \r\n";
    WideString GuidTimeseriesPropertyDefinitionColumnData::BaseViewName = L"GuidTimeseriesPropertyDefinitionView";
    WideString GuidTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"gtpd";

    WideString Int16TimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  i16tpd.[Id], \r\n"
        L"  i16tpd.[EntityType], \r\n"
        L"  i16tpd.[RowVersion], \r\n"
        L"  i16tpd.[ElementType], \r\n"
        L"  i16tpd.[Name], \r\n"
        L"  i16tpd.[MinValue], \r\n"
        L"  i16tpd.[MaxValue], \r\n"
        L"  i16tpd.[Description] \r\n"
        L"FROM [Int16TimeseriesPropertyDefinitionView] i16tpd \r\n";
    WideString Int16TimeseriesPropertyDefinitionColumnData::BaseViewName = L"Int16TimeseriesPropertyDefinitionView";
    WideString Int16TimeseriesPropertyDefinitionColumnData::ViewAliasName = L"i16tpd";

    WideString Int32TimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  i32tpd.[Id], \r\n"
        L"  i32tpd.[EntityType], \r\n"
        L"  i32tpd.[RowVersion], \r\n"
        L"  i32tpd.[ElementType], \r\n"
        L"  i32tpd.[Name], \r\n"
        L"  i32tpd.[MinValue], \r\n"
        L"  i32tpd.[MaxValue], \r\n"
        L"  i32tpd.[Description] \r\n"
        L"FROM [Int32TimeseriesPropertyDefinitionView] i32tpd \r\n";
    WideString Int32TimeseriesPropertyDefinitionColumnData::BaseViewName = L"Int32TimeseriesPropertyDefinitionView";
    WideString Int32TimeseriesPropertyDefinitionColumnData::ViewAliasName = L"i32tpd";

    WideString Int64TimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  i64tpd.[Id], \r\n"
        L"  i64tpd.[EntityType], \r\n"
        L"  i64tpd.[RowVersion], \r\n"
        L"  i64tpd.[ElementType], \r\n"
        L"  i64tpd.[Name], \r\n"
        L"  i64tpd.[MinValue], \r\n"
        L"  i64tpd.[MaxValue], \r\n"
        L"  i64tpd.[Description] \r\n"
        L"FROM [Int64TimeseriesPropertyDefinitionView] i64tpd \r\n";
    WideString Int64TimeseriesPropertyDefinitionColumnData::BaseViewName = L"Int64TimeseriesPropertyDefinitionView";
    WideString Int64TimeseriesPropertyDefinitionColumnData::ViewAliasName = L"i64tpd";

    WideString ReferenceTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  rtpd.[Id], \r\n"
        L"  rtpd.[EntityType], \r\n"
        L"  rtpd.[RowVersion], \r\n"
        L"  rtpd.[ElementType], \r\n"
        L"  rtpd.[Name], \r\n"
        L"  rtpd.[ReferencedElementType], \r\n"
        L"  rtpd.[Description] \r\n"
        L"FROM [ReferenceTimeseriesPropertyDefinitionView] rtpd \r\n";
    WideString ReferenceTimeseriesPropertyDefinitionColumnData::BaseViewName = L"ReferenceTimeseriesPropertyDefinitionView";
    WideString ReferenceTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"rtpd";

    WideString SByteTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  sbtpd.[Id], \r\n"
        L"  sbtpd.[EntityType], \r\n"
        L"  sbtpd.[RowVersion], \r\n"
        L"  sbtpd.[ElementType], \r\n"
        L"  sbtpd.[Name], \r\n"
        L"  sbtpd.[MinValue], \r\n"
        L"  sbtpd.[MaxValue], \r\n"
        L"  sbtpd.[Description] \r\n"
        L"FROM [SByteTimeseriesPropertyDefinitionView] sbtpd \r\n";
    WideString SByteTimeseriesPropertyDefinitionColumnData::BaseViewName = L"SByteTimeseriesPropertyDefinitionView";
    WideString SByteTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"sbtpd";

    WideString SingleTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  sitpd.[Id], \r\n"
        L"  sitpd.[EntityType], \r\n"
        L"  sitpd.[RowVersion], \r\n"
        L"  sitpd.[ElementType], \r\n"
        L"  sitpd.[Name], \r\n"
        L"  sitpd.[MinValue], \r\n"
        L"  sitpd.[MaxValue], \r\n"
        L"  sitpd.[Description] \r\n"
        L"FROM [SingleTimeseriesPropertyDefinitionView] sitpd \r\n";
    WideString SingleTimeseriesPropertyDefinitionColumnData::BaseViewName = L"SingleTimeseriesPropertyDefinitionView";
    WideString SingleTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"sitpd";

    WideString StringTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  sttpd.[Id], \r\n"
        L"  sttpd.[EntityType], \r\n"
        L"  sttpd.[RowVersion], \r\n"
        L"  sttpd.[ElementType], \r\n"
        L"  sttpd.[Name], \r\n"
        L"  sttpd.[Pattern], \r\n"
        L"  sttpd.[Description] \r\n"
        L"FROM [StringTimeseriesPropertyDefinitionView] sttpd \r\n";
    WideString StringTimeseriesPropertyDefinitionColumnData::BaseViewName = L"StringTimeseriesPropertyDefinitionView";
    WideString StringTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"sttpd";

    WideString TimeSpanTimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  tstpd.[Id], \r\n"
        L"  tstpd.[EntityType], \r\n"
        L"  tstpd.[RowVersion], \r\n"
        L"  tstpd.[ElementType], \r\n"
        L"  tstpd.[Name], \r\n"
        L"  tstpd.[MinValue], \r\n"
        L"  tstpd.[MaxValue], \r\n"
        L"  tstpd.[Description] \r\n"
        L"FROM [TimeSpanTimeseriesPropertyDefinitionView] tstpd \r\n";
    WideString TimeSpanTimeseriesPropertyDefinitionColumnData::BaseViewName = L"TimeSpanTimeseriesPropertyDefinitionView";
    WideString TimeSpanTimeseriesPropertyDefinitionColumnData::ViewAliasName = L"tstpd";

    WideString UInt16TimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  u16tpd.[Id], \r\n"
        L"  u16tpd.[EntityType], \r\n"
        L"  u16tpd.[RowVersion], \r\n"
        L"  u16tpd.[ElementType], \r\n"
        L"  u16tpd.[Name], \r\n"
        L"  u16tpd.[MinValue], \r\n"
        L"  u16tpd.[MaxValue], \r\n"
        L"  u16tpd.[Description] \r\n"
        L"FROM [UInt16TimeseriesPropertyDefinitionView] u16tpd \r\n";
    WideString UInt16TimeseriesPropertyDefinitionColumnData::BaseViewName = L"UInt16TimeseriesPropertyDefinitionView";
    WideString UInt16TimeseriesPropertyDefinitionColumnData::ViewAliasName = L"u16tpd";

    WideString UInt32TimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  u32tpd.[Id], \r\n"
        L"  u32tpd.[EntityType], \r\n"
        L"  u32tpd.[RowVersion], \r\n"
        L"  u32tpd.[ElementType], \r\n"
        L"  u32tpd.[Name], \r\n"
        L"  u32tpd.[MinValue], \r\n"
        L"  u32tpd.[MaxValue], \r\n"
        L"  u32tpd.[Description] \r\n"
        L"FROM [UInt32TimeseriesPropertyDefinitionView] u32tpd \r\n";
    WideString UInt32TimeseriesPropertyDefinitionColumnData::BaseViewName = L"UInt32TimeseriesPropertyDefinitionView";
    WideString UInt32TimeseriesPropertyDefinitionColumnData::ViewAliasName = L"u32tpd";

    WideString UInt64TimeseriesPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  u64tpd.[Id], \r\n"
        L"  u64tpd.[EntityType], \r\n"
        L"  u64tpd.[RowVersion], \r\n"
        L"  u64tpd.[ElementType], \r\n"
        L"  u64tpd.[Name], \r\n"
        L"  u64tpd.[MinValue], \r\n"
        L"  u64tpd.[MaxValue], \r\n"
        L"  u64tpd.[Description] \r\n"
        L"FROM [UInt64TimeseriesPropertyDefinitionView] u64tpd \r\n";
    WideString UInt64TimeseriesPropertyDefinitionColumnData::BaseViewName = L"UInt64TimeseriesPropertyDefinitionView";
    WideString UInt64TimeseriesPropertyDefinitionColumnData::ViewAliasName = L"u64tpd";

    WideString TimeSpanPropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  tspd.[Id], \r\n"
        L"  tspd.[EntityType], \r\n"
        L"  tspd.[RowVersion], \r\n"
        L"  tspd.[ElementType], \r\n"
        L"  tspd.[Name], \r\n"
        L"  tspd.[DefaultValue], \r\n"
        L"  tspd.[MinValue], \r\n"
        L"  tspd.[MaxValue], \r\n"
        L"  tspd.[Description] \r\n"
        L"FROM [TimeSpanPropertyDefinitionView] tspd \r\n";
    WideString TimeSpanPropertyDefinitionColumnData::BaseViewName = L"TimeSpanPropertyDefinitionView";
    WideString TimeSpanPropertyDefinitionColumnData::ViewAliasName = L"tspd";

    WideString UInt16PropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  u16pd.[Id], \r\n"
        L"  u16pd.[EntityType], \r\n"
        L"  u16pd.[RowVersion], \r\n"
        L"  u16pd.[ElementType], \r\n"
        L"  u16pd.[Name], \r\n"
        L"  u16pd.[DefaultValue], \r\n"
        L"  u16pd.[MinValue], \r\n"
        L"  u16pd.[MaxValue], \r\n"
        L"  u16pd.[Description] \r\n"
        L"FROM [UInt16PropertyDefinitionView] u16pd \r\n";
    WideString UInt16PropertyDefinitionColumnData::BaseViewName = L"UInt16PropertyDefinitionView";
    WideString UInt16PropertyDefinitionColumnData::ViewAliasName = L"u16pd";

    WideString UInt32PropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  u32pd.[Id], \r\n"
        L"  u32pd.[EntityType], \r\n"
        L"  u32pd.[RowVersion], \r\n"
        L"  u32pd.[ElementType], \r\n"
        L"  u32pd.[Name], \r\n"
        L"  u32pd.[DefaultValue], \r\n"
        L"  u32pd.[MinValue], \r\n"
        L"  u32pd.[MaxValue], \r\n"
        L"  u32pd.[Description] \r\n"
        L"FROM [UInt32PropertyDefinitionView] u32pd \r\n";
    WideString UInt32PropertyDefinitionColumnData::BaseViewName = L"UInt32PropertyDefinitionView";
    WideString UInt32PropertyDefinitionColumnData::ViewAliasName = L"u32pd";

    WideString UInt64PropertyDefinitionColumnData::BaseQuery = L"SELECT \r\n"
        L"  u64pd.[Id], \r\n"
        L"  u64pd.[EntityType], \r\n"
        L"  u64pd.[RowVersion], \r\n"
        L"  u64pd.[ElementType], \r\n"
        L"  u64pd.[Name], \r\n"
        L"  u64pd.[DefaultValue], \r\n"
        L"  u64pd.[MinValue], \r\n"
        L"  u64pd.[MaxValue], \r\n"
        L"  u64pd.[Description] \r\n"
        L"FROM [UInt64PropertyDefinitionView] u64pd \r\n";
    WideString UInt64PropertyDefinitionColumnData::BaseViewName = L"UInt64PropertyDefinitionView";
    WideString UInt64PropertyDefinitionColumnData::ViewAliasName = L"u64pd";

    WideString RadarAlarmStatusColumnData::BaseQuery = L"SELECT \r\n"
        L"  ras.[Id], \r\n"
        L"  ras.[RowVersion], \r\n"
        L"  ras.[Radar], \r\n"
        L"  ras.[Timestamp], \r\n"
        L"  ras.[Type] \r\n"
        L"FROM [RadarAlarmStatusView] ras \r\n";
    WideString RadarAlarmStatusColumnData::BaseViewName = L"RadarAlarmStatusView";
    WideString RadarAlarmStatusColumnData::ViewAliasName = L"ras";

    WideString RadarCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  rc.[Id], \r\n"
        L"  rc.[EntityType], \r\n"
        L"  rc.[RowVersion], \r\n"
        L"  rc.[Radar], \r\n"
        L"  rc.[Timestamp], \r\n"
        L"  rc.[DeviceCommandSourceType], \r\n"
        L"  rc.[DeviceCommandSourceId], \r\n"
        L"  rc.[Reply] \r\n"
        L"FROM [RadarCommandView] rc \r\n";
    WideString RadarCommandColumnData::BaseViewName = L"RadarCommandView";
    WideString RadarCommandColumnData::ViewAliasName = L"rc";

    WideString RadarCommandGetStatusColumnData::BaseQuery = L"SELECT \r\n"
        L"  rcgs.[Id], \r\n"
        L"  rcgs.[EntityType], \r\n"
        L"  rcgs.[RowVersion], \r\n"
        L"  rcgs.[Radar], \r\n"
        L"  rcgs.[Timestamp], \r\n"
        L"  rcgs.[DeviceCommandSourceType], \r\n"
        L"  rcgs.[DeviceCommandSourceId], \r\n"
        L"  rcgs.[Reply] \r\n"
        L"FROM [RadarCommandGetStatusView] rcgs \r\n";
    WideString RadarCommandGetStatusColumnData::BaseViewName = L"RadarCommandGetStatusView";
    WideString RadarCommandGetStatusColumnData::ViewAliasName = L"rcgs";

    WideString RadarCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  rcr.[Id], \r\n"
        L"  rcr.[EntityType], \r\n"
        L"  rcr.[RowVersion], \r\n"
        L"  rcr.[Radar], \r\n"
        L"  rcr.[Timestamp], \r\n"
        L"  rcr.[Command], \r\n"
        L"  rcr.[Status], \r\n"
        L"  rcr.[Message] \r\n"
        L"FROM [RadarCommandReplyView] rcr \r\n";
    WideString RadarCommandReplyColumnData::BaseViewName = L"RadarCommandReplyView";
    WideString RadarCommandReplyColumnData::ViewAliasName = L"rcr";

    WideString RadarCommandReplyGetStatusColumnData::BaseQuery = L"SELECT \r\n"
        L"  rcrgs.[Id], \r\n"
        L"  rcrgs.[EntityType], \r\n"
        L"  rcrgs.[RowVersion], \r\n"
        L"  rcrgs.[Radar], \r\n"
        L"  rcrgs.[Timestamp], \r\n"
        L"  rcrgs.[Command], \r\n"
        L"  rcrgs.[Status], \r\n"
        L"  rcrgs.[AzimuthCount], \r\n"
        L"  rcrgs.[TriggerCount], \r\n"
        L"  rcrgs.[RotationCount], \r\n"
        L"  rcrgs.[Pulse], \r\n"
        L"  rcrgs.[Tx], \r\n"
        L"  rcrgs.[Message] \r\n"
        L"FROM [RadarCommandReplyGetStatusView] rcrgs \r\n";
    WideString RadarCommandReplyGetStatusColumnData::BaseViewName = L"RadarCommandReplyGetStatusView";
    WideString RadarCommandReplyGetStatusColumnData::ViewAliasName = L"rcrgs";

    WideString RadarConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  rc.[Id], \r\n"
        L"  rc.[RowVersion], \r\n"
        L"  rc.[Radar], \r\n"
        L"  rc.[Timestamp], \r\n"
        L"  rc.[RadarProtocolVersion], \r\n"
        L"  rc.[RadarIPAddress], \r\n"
        L"  rc.[RadarPort], \r\n"
        L"  rc.[RadarConfigurationPort], \r\n"
        L"  rc.[SkipMagicTimeout], \r\n"
        L"  rc.[ReadTimeout], \r\n"
        L"  rc.[SynchronizationInterval], \r\n"
        L"  rc.[TargetsRefreshRate], \r\n"
        L"  rc.[Range], \r\n"
        L"  rc.[SectorCount], \r\n"
        L"  rc.[SectorOffset], \r\n"
        L"  rc.[ImageColor], \r\n"
        L"  rc.[ImageSubstitutionColor], \r\n"
        L"  rc.[TransparentColor], \r\n"
        L"  rc.[ImageScaleFactorX], \r\n"
        L"  rc.[ImageOffsetX], \r\n"
        L"  rc.[ImageScaleFactorY], \r\n"
        L"  rc.[ImageOffsetY], \r\n"
        L"  rc.[RadarImageType], \r\n"
        L"  rc.[TrackColor], \r\n"
        L"  rc.[VectorColor], \r\n"
        L"  rc.[EnableNmea], \r\n"
        L"  rc.[NmeaReceiverIPAddress], \r\n"
        L"  rc.[NmeaReceiverPort], \r\n"
        L"  rc.[NmeaReceiverSourceId] \r\n"
        L"FROM [RadarConfigurationView] rc \r\n";
    WideString RadarConfigurationColumnData::BaseViewName = L"RadarConfigurationView";
    WideString RadarConfigurationColumnData::ViewAliasName = L"rc";

    WideString RadarImageColumnData::BaseQuery = L"SELECT \r\n"
        L"  ri.[Id], \r\n"
        L"  ri.[RowVersion], \r\n"
        L"  ri.[Radar], \r\n"
        L"  ri.[Timestamp], \r\n"
        L"  ri.[Depth], \r\n"
        L"  ri.[Resolution], \r\n"
        L"  ri.[Range], \r\n"
        L"  ri.[Image] \r\n"
        L"FROM [RadarImageView] ri \r\n";
    WideString RadarImageColumnData::BaseViewName = L"RadarImageView";
    WideString RadarImageColumnData::ViewAliasName = L"ri";

    WideString RadarRawTrackTableColumnData::BaseQuery = L"SELECT \r\n"
        L"  rrtt.[Id], \r\n"
        L"  rrtt.[RowVersion], \r\n"
        L"  rrtt.[Radar], \r\n"
        L"  rrtt.[Timestamp], \r\n"
        L"  rrtt.[Count], \r\n"
        L"  rrtt.[Table] \r\n"
        L"FROM [RadarRawTrackTableView] rrtt \r\n";
    WideString RadarRawTrackTableColumnData::BaseViewName = L"RadarRawTrackTableView";
    WideString RadarRawTrackTableColumnData::ViewAliasName = L"rrtt";

    WideString RadarStatusColumnData::BaseQuery = L"SELECT \r\n"
        L"  rs.[Id], \r\n"
        L"  rs.[RowVersion], \r\n"
        L"  rs.[Radar], \r\n"
        L"  rs.[Timestamp], \r\n"
        L"  rs.[AzimuthCount], \r\n"
        L"  rs.[TriggerCount], \r\n"
        L"  rs.[RotationTime], \r\n"
        L"  rs.[Pulse], \r\n"
        L"  rs.[Tx], \r\n"
        L"  rs.[Tracking] \r\n"
        L"FROM [RadarStatusView] rs \r\n";
    WideString RadarStatusColumnData::BaseViewName = L"RadarStatusView";
    WideString RadarStatusColumnData::ViewAliasName = L"rs";

    WideString RadioCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  rc.[Id], \r\n"
        L"  rc.[RowVersion], \r\n"
        L"  rc.[Radio], \r\n"
        L"  rc.[Timestamp], \r\n"
        L"  rc.[DeviceCommandSourceType], \r\n"
        L"  rc.[DeviceCommandSourceId], \r\n"
        L"  rc.[Reply] \r\n"
        L"FROM [RadioCommandView] rc \r\n";
    WideString RadioCommandColumnData::BaseViewName = L"RadioCommandView";
    WideString RadioCommandColumnData::ViewAliasName = L"rc";

    WideString RadioCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  rcr.[Id], \r\n"
        L"  rcr.[RowVersion], \r\n"
        L"  rcr.[Radio], \r\n"
        L"  rcr.[Timestamp], \r\n"
        L"  rcr.[Command], \r\n"
        L"  rcr.[Status], \r\n"
        L"  rcr.[Message] \r\n"
        L"FROM [RadioCommandReplyView] rcr \r\n";
    WideString RadioCommandReplyColumnData::BaseViewName = L"RadioCommandReplyView";
    WideString RadioCommandReplyColumnData::ViewAliasName = L"rcr";

    WideString RadioConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  rc.[Id], \r\n"
        L"  rc.[RowVersion], \r\n"
        L"  rc.[Radio], \r\n"
        L"  rc.[Timestamp], \r\n"
        L"  rc.[Longitude], \r\n"
        L"  rc.[Latitude], \r\n"
        L"  rc.[PlaybackUrl], \r\n"
        L"  rc.[RadioIPAddress], \r\n"
        L"  rc.[RadioPort], \r\n"
        L"  rc.[Ed137IPAddress], \r\n"
        L"  rc.[Ed137Port] \r\n"
        L"FROM [RadioConfigurationView] rc \r\n";
    WideString RadioConfigurationColumnData::BaseViewName = L"RadioConfigurationView";
    WideString RadioConfigurationColumnData::ViewAliasName = L"rc";

    WideString RadomeCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  rc.[Id], \r\n"
        L"  rc.[RowVersion], \r\n"
        L"  rc.[Radome], \r\n"
        L"  rc.[Timestamp], \r\n"
        L"  rc.[DeviceCommandSourceType], \r\n"
        L"  rc.[DeviceCommandSourceId], \r\n"
        L"  rc.[Reply] \r\n"
        L"FROM [RadomeCommandView] rc \r\n";
    WideString RadomeCommandColumnData::BaseViewName = L"RadomeCommandView";
    WideString RadomeCommandColumnData::ViewAliasName = L"rc";

    WideString RadomeCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  rcr.[Id], \r\n"
        L"  rcr.[RowVersion], \r\n"
        L"  rcr.[Radome], \r\n"
        L"  rcr.[Timestamp], \r\n"
        L"  rcr.[Command], \r\n"
        L"  rcr.[Status], \r\n"
        L"  rcr.[Message] \r\n"
        L"FROM [RadomeCommandReplyView] rcr \r\n";
    WideString RadomeCommandReplyColumnData::BaseViewName = L"RadomeCommandReplyView";
    WideString RadomeCommandReplyColumnData::ViewAliasName = L"rcr";

    WideString RadomeConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  rc.[Id], \r\n"
        L"  rc.[RowVersion], \r\n"
        L"  rc.[Radome], \r\n"
        L"  rc.[Timestamp], \r\n"
        L"  rc.[Interval], \r\n"
        L"  rc.[LowPressureLimit], \r\n"
        L"  rc.[HighPressureLimit], \r\n"
        L"  rc.[LowTemperatureLimit], \r\n"
        L"  rc.[HighTemperatureLimit] \r\n"
        L"FROM [RadomeConfigurationView] rc \r\n";
    WideString RadomeConfigurationColumnData::BaseViewName = L"RadomeConfigurationView";
    WideString RadomeConfigurationColumnData::ViewAliasName = L"rc";

    WideString ReferenceTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  rtv.[Id], \r\n"
        L"  rtv.[RowVersion], \r\n"
        L"  rtv.[Timeseries], \r\n"
        L"  rtv.[Timestamp], \r\n"
        L"  rtv.[Value] \r\n"
        L"FROM [ReferenceTimeseriesValueView] rtv \r\n";
    WideString ReferenceTimeseriesValueColumnData::BaseViewName = L"ReferenceTimeseriesValueView";
    WideString ReferenceTimeseriesValueColumnData::ViewAliasName = L"rtv";

    WideString SByteTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  stv.[Id], \r\n"
        L"  stv.[RowVersion], \r\n"
        L"  stv.[Timeseries], \r\n"
        L"  stv.[Timestamp], \r\n"
        L"  stv.[Value] \r\n"
        L"FROM [SByteTimeseriesValueView] stv \r\n";
    WideString SByteTimeseriesValueColumnData::BaseViewName = L"SByteTimeseriesValueView";
    WideString SByteTimeseriesValueColumnData::ViewAliasName = L"stv";

    WideString SecurityDomainColumnData::BaseQuery = L"SELECT \r\n"
        L"  sd.[Id], \r\n"
        L"  sd.[RowVersion], \r\n"
        L"  sd.[Name], \r\n"
        L"  sd.[Description] \r\n"
        L"FROM [SecurityDomainView] sd \r\n";
    WideString SecurityDomainColumnData::BaseViewName = L"SecurityDomainView";
    WideString SecurityDomainColumnData::ViewAliasName = L"sd";

    WideString SecurityIdentifierColumnData::BaseQuery = L"SELECT \r\n"
        L"  si.[Id], \r\n"
        L"  si.[EntityType], \r\n"
        L"  si.[RowVersion], \r\n"
        L"  si.[Domain], \r\n"
        L"  si.[Identity], \r\n"
        L"  si.[Description] \r\n"
        L"FROM [SecurityIdentifierView] si \r\n";
    WideString SecurityIdentifierColumnData::BaseViewName = L"SecurityIdentifierView";
    WideString SecurityIdentifierColumnData::ViewAliasName = L"si";

    WideString SecurityLoginColumnData::BaseQuery = L"SELECT \r\n"
        L"  sl.[Id], \r\n"
        L"  sl.[EntityType], \r\n"
        L"  sl.[RowVersion], \r\n"
        L"  sl.[Domain], \r\n"
        L"  sl.[Identity], \r\n"
        L"  sl.[Description] \r\n"
        L"FROM [SecurityLoginView] sl \r\n";
    WideString SecurityLoginColumnData::BaseViewName = L"SecurityLoginView";
    WideString SecurityLoginColumnData::ViewAliasName = L"sl";

    WideString SecurityRoleColumnData::BaseQuery = L"SELECT \r\n"
        L"  sr.[Id], \r\n"
        L"  sr.[EntityType], \r\n"
        L"  sr.[RowVersion], \r\n"
        L"  sr.[Domain], \r\n"
        L"  sr.[Identity], \r\n"
        L"  sr.[Name], \r\n"
        L"  sr.[Description] \r\n"
        L"FROM [SecurityRoleView] sr \r\n";
    WideString SecurityRoleColumnData::BaseViewName = L"SecurityRoleView";
    WideString SecurityRoleColumnData::ViewAliasName = L"sr";

    WideString SecurityIdentifierRoleLinkColumnData::BaseQuery = L"SELECT \r\n"
        L"  sirl.[Id], \r\n"
        L"  sirl.[RowVersion], \r\n"
        L"  sirl.[Member], \r\n"
        L"  sirl.[Role], \r\n"
        L"  sirl.[Start], \r\n"
        L"  sirl.[End] \r\n"
        L"FROM [SecurityIdentifierRoleLinkView] sirl \r\n";
    WideString SecurityIdentifierRoleLinkColumnData::BaseViewName = L"SecurityIdentifierRoleLinkView";
    WideString SecurityIdentifierRoleLinkColumnData::ViewAliasName = L"sirl";

    WideString SecurityLoginSessionColumnData::BaseQuery = L"SELECT \r\n"
        L"  sls.[Id], \r\n"
        L"  sls.[RowVersion], \r\n"
        L"  sls.[Login], \r\n"
        L"  sls.[FromTime], \r\n"
        L"  sls.[ThroughTime], \r\n"
        L"  sls.[ClientSession], \r\n"
        L"  sls.[NotificationQueueName], \r\n"
        L"  sls.[MessageQueueName] \r\n"
        L"FROM [SecurityLoginSessionView] sls \r\n";
    WideString SecurityLoginSessionColumnData::BaseViewName = L"SecurityLoginSessionView";
    WideString SecurityLoginSessionColumnData::ViewAliasName = L"sls";

    WideString SecurityPermissionColumnData::BaseQuery = L"SELECT \r\n"
        L"  sp.[Id], \r\n"
        L"  sp.[RowVersion], \r\n"
        L"  sp.[Identifier], \r\n"
        L"  sp.[Timestamp], \r\n"
        L"  sp.[TypeCode], \r\n"
        L"  sp.[CanCreate], \r\n"
        L"  sp.[CanRead], \r\n"
        L"  sp.[CanUpdate], \r\n"
        L"  sp.[CanDelete] \r\n"
        L"FROM [SecurityPermissionView] sp \r\n";
    WideString SecurityPermissionColumnData::BaseViewName = L"SecurityPermissionView";
    WideString SecurityPermissionColumnData::ViewAliasName = L"sp";

    WideString SingleTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  stv.[Id], \r\n"
        L"  stv.[RowVersion], \r\n"
        L"  stv.[Timeseries], \r\n"
        L"  stv.[Timestamp], \r\n"
        L"  stv.[Value] \r\n"
        L"FROM [SingleTimeseriesValueView] stv \r\n";
    WideString SingleTimeseriesValueColumnData::BaseViewName = L"SingleTimeseriesValueView";
    WideString SingleTimeseriesValueColumnData::ViewAliasName = L"stv";

    WideString StringTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  stv.[Id], \r\n"
        L"  stv.[RowVersion], \r\n"
        L"  stv.[Timeseries], \r\n"
        L"  stv.[Timestamp], \r\n"
        L"  stv.[Value] \r\n"
        L"FROM [StringTimeseriesValueView] stv \r\n";
    WideString StringTimeseriesValueColumnData::BaseViewName = L"StringTimeseriesValueView";
    WideString StringTimeseriesValueColumnData::ViewAliasName = L"stv";

    WideString TimeseriesCatalogElementColumnData::BaseQuery = L"SELECT \r\n"
        L"  tce.[Id], \r\n"
        L"  tce.[EntityType], \r\n"
        L"  tce.[RowVersion], \r\n"
        L"  tce.[Catalog], \r\n"
        L"  tce.[Name] \r\n"
        L"FROM [TimeseriesCatalogElementView] tce \r\n";
    WideString TimeseriesCatalogElementColumnData::BaseViewName = L"TimeseriesCatalogElementView";
    WideString TimeseriesCatalogElementColumnData::ViewAliasName = L"tce";

    WideString TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  t.[Id], \r\n"
        L"  t.[EntityType], \r\n"
        L"  t.[RowVersion], \r\n"
        L"  t.[Catalog], \r\n"
        L"  t.[Name], \r\n"
        L"  t.[MaxRetention] \r\n"
        L"FROM [TimeseriesView] t \r\n";
    WideString TimeseriesColumnData::BaseViewName = L"TimeseriesView";
    WideString TimeseriesColumnData::ViewAliasName = L"t";

    WideString BinaryTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  bt.[Id], \r\n"
        L"  bt.[EntityType], \r\n"
        L"  bt.[RowVersion], \r\n"
        L"  bt.[Catalog], \r\n"
        L"  bt.[Name], \r\n"
        L"  bt.[MaxRetention] \r\n"
        L"FROM [BinaryTimeseriesView] bt \r\n";
    WideString BinaryTimeseriesColumnData::BaseViewName = L"BinaryTimeseriesView";
    WideString BinaryTimeseriesColumnData::ViewAliasName = L"bt";

    WideString BooleanTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  bots.[Id], \r\n"
        L"  bots.[EntityType], \r\n"
        L"  bots.[RowVersion], \r\n"
        L"  bots.[Catalog], \r\n"
        L"  bots.[Name], \r\n"
        L"  bots.[MaxRetention] \r\n"
        L"FROM [BooleanTimeseriesView] bots \r\n";
    WideString BooleanTimeseriesColumnData::BaseViewName = L"BooleanTimeseriesView";
    WideString BooleanTimeseriesColumnData::ViewAliasName = L"bots";

    WideString AisAidToNavigationOffPositionTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  aatnopt.[Id], \r\n"
        L"  aatnopt.[EntityType], \r\n"
        L"  aatnopt.[RowVersion], \r\n"
        L"  aatnopt.[Catalog], \r\n"
        L"  aatnopt.[Name], \r\n"
        L"  aatnopt.[MaxRetention], \r\n"
        L"  aatnopt.[AidToNavigation] \r\n"
        L"FROM [AisAidToNavigationOffPositionTimeseriesView] aatnopt \r\n";
    WideString AisAidToNavigationOffPositionTimeseriesColumnData::BaseViewName = L"AisAidToNavigationOffPositionTimeseriesView";
    WideString AisAidToNavigationOffPositionTimeseriesColumnData::ViewAliasName = L"aatnopt";

    WideString DeviceEnabledTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  det.[Id], \r\n"
        L"  det.[EntityType], \r\n"
        L"  det.[RowVersion], \r\n"
        L"  det.[Catalog], \r\n"
        L"  det.[Name], \r\n"
        L"  det.[MaxRetention], \r\n"
        L"  det.[Device] \r\n"
        L"FROM [DeviceEnabledTimeseriesView] det \r\n";
    WideString DeviceEnabledTimeseriesColumnData::BaseViewName = L"DeviceEnabledTimeseriesView";
    WideString DeviceEnabledTimeseriesColumnData::ViewAliasName = L"det";

    WideString RadarAutomaticSensitivityTimeControlTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rastct.[Id], \r\n"
        L"  rastct.[EntityType], \r\n"
        L"  rastct.[RowVersion], \r\n"
        L"  rastct.[Catalog], \r\n"
        L"  rastct.[Name], \r\n"
        L"  rastct.[MaxRetention], \r\n"
        L"  rastct.[Radar] \r\n"
        L"FROM [RadarAutomaticSensitivityTimeControlTimeseriesView] rastct \r\n";
    WideString RadarAutomaticSensitivityTimeControlTimeseriesColumnData::BaseViewName = L"RadarAutomaticSensitivityTimeControlTimeseriesView";
    WideString RadarAutomaticSensitivityTimeControlTimeseriesColumnData::ViewAliasName = L"rastct";

    WideString RadarBlankSector1TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rbs1t.[Id], \r\n"
        L"  rbs1t.[EntityType], \r\n"
        L"  rbs1t.[RowVersion], \r\n"
        L"  rbs1t.[Catalog], \r\n"
        L"  rbs1t.[Name], \r\n"
        L"  rbs1t.[MaxRetention], \r\n"
        L"  rbs1t.[Radar] \r\n"
        L"FROM [RadarBlankSector1TimeseriesView] rbs1t \r\n";
    WideString RadarBlankSector1TimeseriesColumnData::BaseViewName = L"RadarBlankSector1TimeseriesView";
    WideString RadarBlankSector1TimeseriesColumnData::ViewAliasName = L"rbs1t";

    WideString RadarBlankSector2TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rbs2t.[Id], \r\n"
        L"  rbs2t.[EntityType], \r\n"
        L"  rbs2t.[RowVersion], \r\n"
        L"  rbs2t.[Catalog], \r\n"
        L"  rbs2t.[Name], \r\n"
        L"  rbs2t.[MaxRetention], \r\n"
        L"  rbs2t.[Radar] \r\n"
        L"FROM [RadarBlankSector2TimeseriesView] rbs2t \r\n";
    WideString RadarBlankSector2TimeseriesColumnData::BaseViewName = L"RadarBlankSector2TimeseriesView";
    WideString RadarBlankSector2TimeseriesColumnData::ViewAliasName = L"rbs2t";

    WideString RadarEnableAutomaticFrequencyControlTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  reafct.[Id], \r\n"
        L"  reafct.[EntityType], \r\n"
        L"  reafct.[RowVersion], \r\n"
        L"  reafct.[Catalog], \r\n"
        L"  reafct.[Name], \r\n"
        L"  reafct.[MaxRetention], \r\n"
        L"  reafct.[Radar] \r\n"
        L"FROM [RadarEnableAutomaticFrequencyControlTimeseriesView] reafct \r\n";
    WideString RadarEnableAutomaticFrequencyControlTimeseriesColumnData::BaseViewName = L"RadarEnableAutomaticFrequencyControlTimeseriesView";
    WideString RadarEnableAutomaticFrequencyControlTimeseriesColumnData::ViewAliasName = L"reafct";

    WideString RadarEnableFastTimeConstantTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  reftct.[Id], \r\n"
        L"  reftct.[EntityType], \r\n"
        L"  reftct.[RowVersion], \r\n"
        L"  reftct.[Catalog], \r\n"
        L"  reftct.[Name], \r\n"
        L"  reftct.[MaxRetention], \r\n"
        L"  reftct.[Radar] \r\n"
        L"FROM [RadarEnableFastTimeConstantTimeseriesView] reftct \r\n";
    WideString RadarEnableFastTimeConstantTimeseriesColumnData::BaseViewName = L"RadarEnableFastTimeConstantTimeseriesView";
    WideString RadarEnableFastTimeConstantTimeseriesColumnData::ViewAliasName = L"reftct";

    WideString RadarEnableSensitivityTimeControlTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  restct.[Id], \r\n"
        L"  restct.[EntityType], \r\n"
        L"  restct.[RowVersion], \r\n"
        L"  restct.[Catalog], \r\n"
        L"  restct.[Name], \r\n"
        L"  restct.[MaxRetention], \r\n"
        L"  restct.[Radar] \r\n"
        L"FROM [RadarEnableSensitivityTimeControlTimeseriesView] restct \r\n";
    WideString RadarEnableSensitivityTimeControlTimeseriesColumnData::BaseViewName = L"RadarEnableSensitivityTimeControlTimeseriesView";
    WideString RadarEnableSensitivityTimeControlTimeseriesColumnData::ViewAliasName = L"restct";

    WideString RadarPowerOnTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rpot.[Id], \r\n"
        L"  rpot.[EntityType], \r\n"
        L"  rpot.[RowVersion], \r\n"
        L"  rpot.[Catalog], \r\n"
        L"  rpot.[Name], \r\n"
        L"  rpot.[MaxRetention], \r\n"
        L"  rpot.[Radar] \r\n"
        L"FROM [RadarPowerOnTimeseriesView] rpot \r\n";
    WideString RadarPowerOnTimeseriesColumnData::BaseViewName = L"RadarPowerOnTimeseriesView";
    WideString RadarPowerOnTimeseriesColumnData::ViewAliasName = L"rpot";

    WideString RadarSaveSettingsTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rsst.[Id], \r\n"
        L"  rsst.[EntityType], \r\n"
        L"  rsst.[RowVersion], \r\n"
        L"  rsst.[Catalog], \r\n"
        L"  rsst.[Name], \r\n"
        L"  rsst.[MaxRetention], \r\n"
        L"  rsst.[Radar] \r\n"
        L"FROM [RadarSaveSettingsTimeseriesView] rsst \r\n";
    WideString RadarSaveSettingsTimeseriesColumnData::BaseViewName = L"RadarSaveSettingsTimeseriesView";
    WideString RadarSaveSettingsTimeseriesColumnData::ViewAliasName = L"rsst";

    WideString RadarTrackingTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rtt.[Id], \r\n"
        L"  rtt.[EntityType], \r\n"
        L"  rtt.[RowVersion], \r\n"
        L"  rtt.[Catalog], \r\n"
        L"  rtt.[Name], \r\n"
        L"  rtt.[MaxRetention], \r\n"
        L"  rtt.[Radar] \r\n"
        L"FROM [RadarTrackingTimeseriesView] rtt \r\n";
    WideString RadarTrackingTimeseriesColumnData::BaseViewName = L"RadarTrackingTimeseriesView";
    WideString RadarTrackingTimeseriesColumnData::ViewAliasName = L"rtt";

    WideString MediaProxySessionEnabledTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  mpset.[Id], \r\n"
        L"  mpset.[EntityType], \r\n"
        L"  mpset.[RowVersion], \r\n"
        L"  mpset.[Catalog], \r\n"
        L"  mpset.[Name], \r\n"
        L"  mpset.[MaxRetention], \r\n"
        L"  mpset.[ProxySession] \r\n"
        L"FROM [MediaProxySessionEnabledTimeseriesView] mpset \r\n";
    WideString MediaProxySessionEnabledTimeseriesColumnData::BaseViewName = L"MediaProxySessionEnabledTimeseriesView";
    WideString MediaProxySessionEnabledTimeseriesColumnData::ViewAliasName = L"mpset";

    WideString MediaServiceEnabledTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  mset.[Id], \r\n"
        L"  mset.[EntityType], \r\n"
        L"  mset.[RowVersion], \r\n"
        L"  mset.[Catalog], \r\n"
        L"  mset.[Name], \r\n"
        L"  mset.[MaxRetention], \r\n"
        L"  mset.[Service] \r\n"
        L"FROM [MediaServiceEnabledTimeseriesView] mset \r\n";
    WideString MediaServiceEnabledTimeseriesColumnData::BaseViewName = L"MediaServiceEnabledTimeseriesView";
    WideString MediaServiceEnabledTimeseriesColumnData::ViewAliasName = L"mset";

    WideString ByteTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  byts.[Id], \r\n"
        L"  byts.[EntityType], \r\n"
        L"  byts.[RowVersion], \r\n"
        L"  byts.[Catalog], \r\n"
        L"  byts.[Name], \r\n"
        L"  byts.[MaxRetention] \r\n"
        L"FROM [ByteTimeseriesView] byts \r\n";
    WideString ByteTimeseriesColumnData::BaseViewName = L"ByteTimeseriesView";
    WideString ByteTimeseriesColumnData::ViewAliasName = L"byts";

    WideString DateTimeTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  dtt.[Id], \r\n"
        L"  dtt.[EntityType], \r\n"
        L"  dtt.[RowVersion], \r\n"
        L"  dtt.[Catalog], \r\n"
        L"  dtt.[Name], \r\n"
        L"  dtt.[MaxRetention] \r\n"
        L"FROM [DateTimeTimeseriesView] dtt \r\n";
    WideString DateTimeTimeseriesColumnData::BaseViewName = L"DateTimeTimeseriesView";
    WideString DateTimeTimeseriesColumnData::ViewAliasName = L"dtt";

    WideString DoubleTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  dt.[Id], \r\n"
        L"  dt.[EntityType], \r\n"
        L"  dt.[RowVersion], \r\n"
        L"  dt.[Catalog], \r\n"
        L"  dt.[Name], \r\n"
        L"  dt.[MaxRetention] \r\n"
        L"FROM [DoubleTimeseriesView] dt \r\n";
    WideString DoubleTimeseriesColumnData::BaseViewName = L"DoubleTimeseriesView";
    WideString DoubleTimeseriesColumnData::ViewAliasName = L"dt";

    WideString GNSSAltitudeTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  gats.[Id], \r\n"
        L"  gats.[EntityType], \r\n"
        L"  gats.[RowVersion], \r\n"
        L"  gats.[Catalog], \r\n"
        L"  gats.[Name], \r\n"
        L"  gats.[MaxRetention], \r\n"
        L"  gats.[GNSSDevice] \r\n"
        L"FROM [GNSSAltitudeTimeseriesView] gats \r\n";
    WideString GNSSAltitudeTimeseriesColumnData::BaseViewName = L"GNSSAltitudeTimeseriesView";
    WideString GNSSAltitudeTimeseriesColumnData::ViewAliasName = L"gats";

    WideString GNSSLatitudeTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  glats.[Id], \r\n"
        L"  glats.[EntityType], \r\n"
        L"  glats.[RowVersion], \r\n"
        L"  glats.[Catalog], \r\n"
        L"  glats.[Name], \r\n"
        L"  glats.[MaxRetention], \r\n"
        L"  glats.[GNSSDevice] \r\n"
        L"FROM [GNSSLatitudeTimeseriesView] glats \r\n";
    WideString GNSSLatitudeTimeseriesColumnData::BaseViewName = L"GNSSLatitudeTimeseriesView";
    WideString GNSSLatitudeTimeseriesColumnData::ViewAliasName = L"glats";

    WideString GNSSLongitudeTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  glots.[Id], \r\n"
        L"  glots.[EntityType], \r\n"
        L"  glots.[RowVersion], \r\n"
        L"  glots.[Catalog], \r\n"
        L"  glots.[Name], \r\n"
        L"  glots.[MaxRetention], \r\n"
        L"  glots.[GNSSDevice] \r\n"
        L"FROM [GNSSLongitudeTimeseriesView] glots \r\n";
    WideString GNSSLongitudeTimeseriesColumnData::BaseViewName = L"GNSSLongitudeTimeseriesView";
    WideString GNSSLongitudeTimeseriesColumnData::ViewAliasName = L"glots";

    WideString GyroCourseTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  gct.[Id], \r\n"
        L"  gct.[EntityType], \r\n"
        L"  gct.[RowVersion], \r\n"
        L"  gct.[Catalog], \r\n"
        L"  gct.[Name], \r\n"
        L"  gct.[MaxRetention], \r\n"
        L"  gct.[GyroDevice] \r\n"
        L"FROM [GyroCourseTimeseriesView] gct \r\n";
    WideString GyroCourseTimeseriesColumnData::BaseViewName = L"GyroCourseTimeseriesView";
    WideString GyroCourseTimeseriesColumnData::ViewAliasName = L"gct";

    WideString GyroHeadingMagneticNorthTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  ghmnt.[Id], \r\n"
        L"  ghmnt.[EntityType], \r\n"
        L"  ghmnt.[RowVersion], \r\n"
        L"  ghmnt.[Catalog], \r\n"
        L"  ghmnt.[Name], \r\n"
        L"  ghmnt.[MaxRetention], \r\n"
        L"  ghmnt.[GyroDevice] \r\n"
        L"FROM [GyroHeadingMagneticNorthTimeseriesView] ghmnt \r\n";
    WideString GyroHeadingMagneticNorthTimeseriesColumnData::BaseViewName = L"GyroHeadingMagneticNorthTimeseriesView";
    WideString GyroHeadingMagneticNorthTimeseriesColumnData::ViewAliasName = L"ghmnt";

    WideString GyroHeadingTrueNorthTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  ghtnt.[Id], \r\n"
        L"  ghtnt.[EntityType], \r\n"
        L"  ghtnt.[RowVersion], \r\n"
        L"  ghtnt.[Catalog], \r\n"
        L"  ghtnt.[Name], \r\n"
        L"  ghtnt.[MaxRetention], \r\n"
        L"  ghtnt.[GyroDevice] \r\n"
        L"FROM [GyroHeadingTrueNorthTimeseriesView] ghtnt \r\n";
    WideString GyroHeadingTrueNorthTimeseriesColumnData::BaseViewName = L"GyroHeadingTrueNorthTimeseriesView";
    WideString GyroHeadingTrueNorthTimeseriesColumnData::ViewAliasName = L"ghtnt";

    WideString GyroPitchTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  gpt.[Id], \r\n"
        L"  gpt.[EntityType], \r\n"
        L"  gpt.[RowVersion], \r\n"
        L"  gpt.[Catalog], \r\n"
        L"  gpt.[Name], \r\n"
        L"  gpt.[MaxRetention], \r\n"
        L"  gpt.[GyroDevice] \r\n"
        L"FROM [GyroPitchTimeseriesView] gpt \r\n";
    WideString GyroPitchTimeseriesColumnData::BaseViewName = L"GyroPitchTimeseriesView";
    WideString GyroPitchTimeseriesColumnData::ViewAliasName = L"gpt";

    WideString GyroRateOfTurnTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  grott.[Id], \r\n"
        L"  grott.[EntityType], \r\n"
        L"  grott.[RowVersion], \r\n"
        L"  grott.[Catalog], \r\n"
        L"  grott.[Name], \r\n"
        L"  grott.[MaxRetention], \r\n"
        L"  grott.[GyroDevice] \r\n"
        L"FROM [GyroRateOfTurnTimeseriesView] grott \r\n";
    WideString GyroRateOfTurnTimeseriesColumnData::BaseViewName = L"GyroRateOfTurnTimeseriesView";
    WideString GyroRateOfTurnTimeseriesColumnData::ViewAliasName = L"grott";

    WideString GyroRollTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  grt.[Id], \r\n"
        L"  grt.[EntityType], \r\n"
        L"  grt.[RowVersion], \r\n"
        L"  grt.[Catalog], \r\n"
        L"  grt.[Name], \r\n"
        L"  grt.[MaxRetention], \r\n"
        L"  grt.[GyroDevice] \r\n"
        L"FROM [GyroRollTimeseriesView] grt \r\n";
    WideString GyroRollTimeseriesColumnData::BaseViewName = L"GyroRollTimeseriesView";
    WideString GyroRollTimeseriesColumnData::ViewAliasName = L"grt";

    WideString GyroSpeedTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  gst.[Id], \r\n"
        L"  gst.[EntityType], \r\n"
        L"  gst.[RowVersion], \r\n"
        L"  gst.[Catalog], \r\n"
        L"  gst.[Name], \r\n"
        L"  gst.[MaxRetention], \r\n"
        L"  gst.[GyroDevice] \r\n"
        L"FROM [GyroSpeedTimeseriesView] gst \r\n";
    WideString GyroSpeedTimeseriesColumnData::BaseViewName = L"GyroSpeedTimeseriesView";
    WideString GyroSpeedTimeseriesColumnData::ViewAliasName = L"gst";

    WideString RadarLatitudeTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rlats.[Id], \r\n"
        L"  rlats.[EntityType], \r\n"
        L"  rlats.[RowVersion], \r\n"
        L"  rlats.[Catalog], \r\n"
        L"  rlats.[Name], \r\n"
        L"  rlats.[MaxRetention], \r\n"
        L"  rlats.[Radar] \r\n"
        L"FROM [RadarLatitudeTimeseriesView] rlats \r\n";
    WideString RadarLatitudeTimeseriesColumnData::BaseViewName = L"RadarLatitudeTimeseriesView";
    WideString RadarLatitudeTimeseriesColumnData::ViewAliasName = L"rlats";

    WideString RadarLongitudeTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rlots.[Id], \r\n"
        L"  rlots.[EntityType], \r\n"
        L"  rlots.[RowVersion], \r\n"
        L"  rlots.[Catalog], \r\n"
        L"  rlots.[Name], \r\n"
        L"  rlots.[MaxRetention], \r\n"
        L"  rlots.[Radar] \r\n"
        L"FROM [RadarLongitudeTimeseriesView] rlots \r\n";
    WideString RadarLongitudeTimeseriesColumnData::BaseViewName = L"RadarLongitudeTimeseriesView";
    WideString RadarLongitudeTimeseriesColumnData::ViewAliasName = L"rlots";

    WideString RadomeDewPointTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rdpt.[Id], \r\n"
        L"  rdpt.[EntityType], \r\n"
        L"  rdpt.[RowVersion], \r\n"
        L"  rdpt.[Catalog], \r\n"
        L"  rdpt.[Name], \r\n"
        L"  rdpt.[MaxRetention], \r\n"
        L"  rdpt.[Radome] \r\n"
        L"FROM [RadomeDewPointTimeseriesView] rdpt \r\n";
    WideString RadomeDewPointTimeseriesColumnData::BaseViewName = L"RadomeDewPointTimeseriesView";
    WideString RadomeDewPointTimeseriesColumnData::ViewAliasName = L"rdpt";

    WideString RadomePressureTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rpt.[Id], \r\n"
        L"  rpt.[EntityType], \r\n"
        L"  rpt.[RowVersion], \r\n"
        L"  rpt.[Catalog], \r\n"
        L"  rpt.[Name], \r\n"
        L"  rpt.[MaxRetention], \r\n"
        L"  rpt.[Radome] \r\n"
        L"FROM [RadomePressureTimeseriesView] rpt \r\n";
    WideString RadomePressureTimeseriesColumnData::BaseViewName = L"RadomePressureTimeseriesView";
    WideString RadomePressureTimeseriesColumnData::ViewAliasName = L"rpt";

    WideString RadomeTemperatureTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rtets.[Id], \r\n"
        L"  rtets.[EntityType], \r\n"
        L"  rtets.[RowVersion], \r\n"
        L"  rtets.[Catalog], \r\n"
        L"  rtets.[Name], \r\n"
        L"  rtets.[MaxRetention], \r\n"
        L"  rtets.[Radome] \r\n"
        L"FROM [RadomeTemperatureTimeseriesView] rtets \r\n";
    WideString RadomeTemperatureTimeseriesColumnData::BaseViewName = L"RadomeTemperatureTimeseriesView";
    WideString RadomeTemperatureTimeseriesColumnData::ViewAliasName = L"rtets";

    WideString VesselDraughtTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  vdt.[Id], \r\n"
        L"  vdt.[EntityType], \r\n"
        L"  vdt.[RowVersion], \r\n"
        L"  vdt.[Catalog], \r\n"
        L"  vdt.[Name], \r\n"
        L"  vdt.[MaxRetention], \r\n"
        L"  vdt.[Vessel] \r\n"
        L"FROM [VesselDraughtTimeseriesView] vdt \r\n";
    WideString VesselDraughtTimeseriesColumnData::BaseViewName = L"VesselDraughtTimeseriesView";
    WideString VesselDraughtTimeseriesColumnData::ViewAliasName = L"vdt";

    WideString ViewLatitudeTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  vlats.[Id], \r\n"
        L"  vlats.[EntityType], \r\n"
        L"  vlats.[RowVersion], \r\n"
        L"  vlats.[Catalog], \r\n"
        L"  vlats.[Name], \r\n"
        L"  vlats.[MaxRetention], \r\n"
        L"  vlats.[View] \r\n"
        L"FROM [ViewLatitudeTimeseriesView] vlats \r\n";
    WideString ViewLatitudeTimeseriesColumnData::BaseViewName = L"ViewLatitudeTimeseriesView";
    WideString ViewLatitudeTimeseriesColumnData::ViewAliasName = L"vlats";

    WideString ViewLongitudeTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  vlots.[Id], \r\n"
        L"  vlots.[EntityType], \r\n"
        L"  vlots.[RowVersion], \r\n"
        L"  vlots.[Catalog], \r\n"
        L"  vlots.[Name], \r\n"
        L"  vlots.[MaxRetention], \r\n"
        L"  vlots.[View] \r\n"
        L"FROM [ViewLongitudeTimeseriesView] vlots \r\n";
    WideString ViewLongitudeTimeseriesColumnData::BaseViewName = L"ViewLongitudeTimeseriesView";
    WideString ViewLongitudeTimeseriesColumnData::ViewAliasName = L"vlots";

    WideString ViewZoomLevelTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  vzlt.[Id], \r\n"
        L"  vzlt.[EntityType], \r\n"
        L"  vzlt.[RowVersion], \r\n"
        L"  vzlt.[Catalog], \r\n"
        L"  vzlt.[Name], \r\n"
        L"  vzlt.[MaxRetention], \r\n"
        L"  vzlt.[View] \r\n"
        L"FROM [ViewZoomLevelTimeseriesView] vzlt \r\n";
    WideString ViewZoomLevelTimeseriesColumnData::BaseViewName = L"ViewZoomLevelTimeseriesView";
    WideString ViewZoomLevelTimeseriesColumnData::ViewAliasName = L"vzlt";

    WideString WeatherStationAbsoluteHumidityTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  wsaht.[Id], \r\n"
        L"  wsaht.[EntityType], \r\n"
        L"  wsaht.[RowVersion], \r\n"
        L"  wsaht.[Catalog], \r\n"
        L"  wsaht.[Name], \r\n"
        L"  wsaht.[MaxRetention], \r\n"
        L"  wsaht.[WeatherStation] \r\n"
        L"FROM [WeatherStationAbsoluteHumidityTimeseriesView] wsaht \r\n";
    WideString WeatherStationAbsoluteHumidityTimeseriesColumnData::BaseViewName = L"WeatherStationAbsoluteHumidityTimeseriesView";
    WideString WeatherStationAbsoluteHumidityTimeseriesColumnData::ViewAliasName = L"wsaht";

    WideString WeatherStationAirTemperatureTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  wsatt.[Id], \r\n"
        L"  wsatt.[EntityType], \r\n"
        L"  wsatt.[RowVersion], \r\n"
        L"  wsatt.[Catalog], \r\n"
        L"  wsatt.[Name], \r\n"
        L"  wsatt.[MaxRetention], \r\n"
        L"  wsatt.[WeatherStation] \r\n"
        L"FROM [WeatherStationAirTemperatureTimeseriesView] wsatt \r\n";
    WideString WeatherStationAirTemperatureTimeseriesColumnData::BaseViewName = L"WeatherStationAirTemperatureTimeseriesView";
    WideString WeatherStationAirTemperatureTimeseriesColumnData::ViewAliasName = L"wsatt";

    WideString WeatherStationBarometricPressureTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  wsbpt.[Id], \r\n"
        L"  wsbpt.[EntityType], \r\n"
        L"  wsbpt.[RowVersion], \r\n"
        L"  wsbpt.[Catalog], \r\n"
        L"  wsbpt.[Name], \r\n"
        L"  wsbpt.[MaxRetention], \r\n"
        L"  wsbpt.[WeatherStation] \r\n"
        L"FROM [WeatherStationBarometricPressureTimeseriesView] wsbpt \r\n";
    WideString WeatherStationBarometricPressureTimeseriesColumnData::BaseViewName = L"WeatherStationBarometricPressureTimeseriesView";
    WideString WeatherStationBarometricPressureTimeseriesColumnData::ViewAliasName = L"wsbpt";

    WideString WeatherStationDewPointTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  wsdpt.[Id], \r\n"
        L"  wsdpt.[EntityType], \r\n"
        L"  wsdpt.[RowVersion], \r\n"
        L"  wsdpt.[Catalog], \r\n"
        L"  wsdpt.[Name], \r\n"
        L"  wsdpt.[MaxRetention], \r\n"
        L"  wsdpt.[WeatherStation] \r\n"
        L"FROM [WeatherStationDewPointTimeseriesView] wsdpt \r\n";
    WideString WeatherStationDewPointTimeseriesColumnData::BaseViewName = L"WeatherStationDewPointTimeseriesView";
    WideString WeatherStationDewPointTimeseriesColumnData::ViewAliasName = L"wsdpt";

    WideString WeatherStationRelativeHumidityTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  wsrht.[Id], \r\n"
        L"  wsrht.[EntityType], \r\n"
        L"  wsrht.[RowVersion], \r\n"
        L"  wsrht.[Catalog], \r\n"
        L"  wsrht.[Name], \r\n"
        L"  wsrht.[MaxRetention], \r\n"
        L"  wsrht.[WeatherStation] \r\n"
        L"FROM [WeatherStationRelativeHumidityTimeseriesView] wsrht \r\n";
    WideString WeatherStationRelativeHumidityTimeseriesColumnData::BaseViewName = L"WeatherStationRelativeHumidityTimeseriesView";
    WideString WeatherStationRelativeHumidityTimeseriesColumnData::ViewAliasName = L"wsrht";

    WideString WeatherStationWaterTemperatureTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  wswtt.[Id], \r\n"
        L"  wswtt.[EntityType], \r\n"
        L"  wswtt.[RowVersion], \r\n"
        L"  wswtt.[Catalog], \r\n"
        L"  wswtt.[Name], \r\n"
        L"  wswtt.[MaxRetention], \r\n"
        L"  wswtt.[WeatherStation] \r\n"
        L"FROM [WeatherStationWaterTemperatureTimeseriesView] wswtt \r\n";
    WideString WeatherStationWaterTemperatureTimeseriesColumnData::BaseViewName = L"WeatherStationWaterTemperatureTimeseriesView";
    WideString WeatherStationWaterTemperatureTimeseriesColumnData::ViewAliasName = L"wswtt";

    WideString WeatherStationWindDirectionTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  wswdt.[Id], \r\n"
        L"  wswdt.[EntityType], \r\n"
        L"  wswdt.[RowVersion], \r\n"
        L"  wswdt.[Catalog], \r\n"
        L"  wswdt.[Name], \r\n"
        L"  wswdt.[MaxRetention], \r\n"
        L"  wswdt.[WeatherStation] \r\n"
        L"FROM [WeatherStationWindDirectionTimeseriesView] wswdt \r\n";
    WideString WeatherStationWindDirectionTimeseriesColumnData::BaseViewName = L"WeatherStationWindDirectionTimeseriesView";
    WideString WeatherStationWindDirectionTimeseriesColumnData::ViewAliasName = L"wswdt";

    WideString WeatherStationWindSpeedTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  wswst.[Id], \r\n"
        L"  wswst.[EntityType], \r\n"
        L"  wswst.[RowVersion], \r\n"
        L"  wswst.[Catalog], \r\n"
        L"  wswst.[Name], \r\n"
        L"  wswst.[MaxRetention], \r\n"
        L"  wswst.[WeatherStation] \r\n"
        L"FROM [WeatherStationWindSpeedTimeseriesView] wswst \r\n";
    WideString WeatherStationWindSpeedTimeseriesColumnData::BaseViewName = L"WeatherStationWindSpeedTimeseriesView";
    WideString WeatherStationWindSpeedTimeseriesColumnData::ViewAliasName = L"wswst";

    WideString GeoPosition2DTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  gp2d.[Id], \r\n"
        L"  gp2d.[EntityType], \r\n"
        L"  gp2d.[RowVersion], \r\n"
        L"  gp2d.[Catalog], \r\n"
        L"  gp2d.[Name], \r\n"
        L"  gp2d.[MaxRetention] \r\n"
        L"FROM [GeoPosition2DTimeseriesView] gp2d \r\n";
    WideString GeoPosition2DTimeseriesColumnData::BaseViewName = L"GeoPosition2DTimeseriesView";
    WideString GeoPosition2DTimeseriesColumnData::ViewAliasName = L"gp2d";

    WideString AisAidToNavigationPositionTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  aatnpt.[Id], \r\n"
        L"  aatnpt.[EntityType], \r\n"
        L"  aatnpt.[RowVersion], \r\n"
        L"  aatnpt.[Catalog], \r\n"
        L"  aatnpt.[Name], \r\n"
        L"  aatnpt.[MaxRetention], \r\n"
        L"  aatnpt.[AidToNavigation] \r\n"
        L"FROM [AisAidToNavigationPositionTimeseriesView] aatnpt \r\n";
    WideString AisAidToNavigationPositionTimeseriesColumnData::BaseViewName = L"AisAidToNavigationPositionTimeseriesView";
    WideString AisAidToNavigationPositionTimeseriesColumnData::ViewAliasName = L"aatnpt";

    WideString GeoPosition3DTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  gp3d.[Id], \r\n"
        L"  gp3d.[EntityType], \r\n"
        L"  gp3d.[RowVersion], \r\n"
        L"  gp3d.[Catalog], \r\n"
        L"  gp3d.[Name], \r\n"
        L"  gp3d.[MaxRetention] \r\n"
        L"FROM [GeoPosition3DTimeseriesView] gp3d \r\n";
    WideString GeoPosition3DTimeseriesColumnData::BaseViewName = L"GeoPosition3DTimeseriesView";
    WideString GeoPosition3DTimeseriesColumnData::ViewAliasName = L"gp3d";

    WideString GuidTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  gt.[Id], \r\n"
        L"  gt.[EntityType], \r\n"
        L"  gt.[RowVersion], \r\n"
        L"  gt.[Catalog], \r\n"
        L"  gt.[Name], \r\n"
        L"  gt.[MaxRetention] \r\n"
        L"FROM [GuidTimeseriesView] gt \r\n";
    WideString GuidTimeseriesColumnData::BaseViewName = L"GuidTimeseriesView";
    WideString GuidTimeseriesColumnData::ViewAliasName = L"gt";

    WideString Int16TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  i16t.[Id], \r\n"
        L"  i16t.[EntityType], \r\n"
        L"  i16t.[RowVersion], \r\n"
        L"  i16t.[Catalog], \r\n"
        L"  i16t.[Name], \r\n"
        L"  i16t.[MaxRetention] \r\n"
        L"FROM [Int16TimeseriesView] i16t \r\n";
    WideString Int16TimeseriesColumnData::BaseViewName = L"Int16TimeseriesView";
    WideString Int16TimeseriesColumnData::ViewAliasName = L"i16t";

    WideString Int32TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  i32t.[Id], \r\n"
        L"  i32t.[EntityType], \r\n"
        L"  i32t.[RowVersion], \r\n"
        L"  i32t.[Catalog], \r\n"
        L"  i32t.[Name], \r\n"
        L"  i32t.[MaxRetention] \r\n"
        L"FROM [Int32TimeseriesView] i32t \r\n";
    WideString Int32TimeseriesColumnData::BaseViewName = L"Int32TimeseriesView";
    WideString Int32TimeseriesColumnData::ViewAliasName = L"i32t";

    WideString RadarAzimuthOffsetTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  raot.[Id], \r\n"
        L"  raot.[EntityType], \r\n"
        L"  raot.[RowVersion], \r\n"
        L"  raot.[Catalog], \r\n"
        L"  raot.[Name], \r\n"
        L"  raot.[MaxRetention], \r\n"
        L"  raot.[Radar] \r\n"
        L"FROM [RadarAzimuthOffsetTimeseriesView] raot \r\n";
    WideString RadarAzimuthOffsetTimeseriesColumnData::BaseViewName = L"RadarAzimuthOffsetTimeseriesView";
    WideString RadarAzimuthOffsetTimeseriesColumnData::ViewAliasName = L"raot";

    WideString RadarFastTimeConstantLevelTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rftclt.[Id], \r\n"
        L"  rftclt.[EntityType], \r\n"
        L"  rftclt.[RowVersion], \r\n"
        L"  rftclt.[Catalog], \r\n"
        L"  rftclt.[Name], \r\n"
        L"  rftclt.[MaxRetention], \r\n"
        L"  rftclt.[Radar] \r\n"
        L"FROM [RadarFastTimeConstantLevelTimeseriesView] rftclt \r\n";
    WideString RadarFastTimeConstantLevelTimeseriesColumnData::BaseViewName = L"RadarFastTimeConstantLevelTimeseriesView";
    WideString RadarFastTimeConstantLevelTimeseriesColumnData::ViewAliasName = L"rftclt";

    WideString RadarFastTimeConstantModeTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rftcmt.[Id], \r\n"
        L"  rftcmt.[EntityType], \r\n"
        L"  rftcmt.[RowVersion], \r\n"
        L"  rftcmt.[Catalog], \r\n"
        L"  rftcmt.[Name], \r\n"
        L"  rftcmt.[MaxRetention], \r\n"
        L"  rftcmt.[Radar] \r\n"
        L"FROM [RadarFastTimeConstantModeTimeseriesView] rftcmt \r\n";
    WideString RadarFastTimeConstantModeTimeseriesColumnData::BaseViewName = L"RadarFastTimeConstantModeTimeseriesView";
    WideString RadarFastTimeConstantModeTimeseriesColumnData::ViewAliasName = L"rftcmt";

    WideString RadarPulseTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rapts.[Id], \r\n"
        L"  rapts.[EntityType], \r\n"
        L"  rapts.[RowVersion], \r\n"
        L"  rapts.[Catalog], \r\n"
        L"  rapts.[Name], \r\n"
        L"  rapts.[MaxRetention], \r\n"
        L"  rapts.[Radar] \r\n"
        L"FROM [RadarPulseTimeseriesView] rapts \r\n";
    WideString RadarPulseTimeseriesColumnData::BaseViewName = L"RadarPulseTimeseriesView";
    WideString RadarPulseTimeseriesColumnData::ViewAliasName = L"rapts";

    WideString RadarSector1EndTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rs1et.[Id], \r\n"
        L"  rs1et.[EntityType], \r\n"
        L"  rs1et.[RowVersion], \r\n"
        L"  rs1et.[Catalog], \r\n"
        L"  rs1et.[Name], \r\n"
        L"  rs1et.[MaxRetention], \r\n"
        L"  rs1et.[Radar] \r\n"
        L"FROM [RadarSector1EndTimeseriesView] rs1et \r\n";
    WideString RadarSector1EndTimeseriesColumnData::BaseViewName = L"RadarSector1EndTimeseriesView";
    WideString RadarSector1EndTimeseriesColumnData::ViewAliasName = L"rs1et";

    WideString RadarSector1StartTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rs1st.[Id], \r\n"
        L"  rs1st.[EntityType], \r\n"
        L"  rs1st.[RowVersion], \r\n"
        L"  rs1st.[Catalog], \r\n"
        L"  rs1st.[Name], \r\n"
        L"  rs1st.[MaxRetention], \r\n"
        L"  rs1st.[Radar] \r\n"
        L"FROM [RadarSector1StartTimeseriesView] rs1st \r\n";
    WideString RadarSector1StartTimeseriesColumnData::BaseViewName = L"RadarSector1StartTimeseriesView";
    WideString RadarSector1StartTimeseriesColumnData::ViewAliasName = L"rs1st";

    WideString RadarSector2EndTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rs2et.[Id], \r\n"
        L"  rs2et.[EntityType], \r\n"
        L"  rs2et.[RowVersion], \r\n"
        L"  rs2et.[Catalog], \r\n"
        L"  rs2et.[Name], \r\n"
        L"  rs2et.[MaxRetention], \r\n"
        L"  rs2et.[Radar] \r\n"
        L"FROM [RadarSector2EndTimeseriesView] rs2et \r\n";
    WideString RadarSector2EndTimeseriesColumnData::BaseViewName = L"RadarSector2EndTimeseriesView";
    WideString RadarSector2EndTimeseriesColumnData::ViewAliasName = L"rs2et";

    WideString RadarSector2StartTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rs2st.[Id], \r\n"
        L"  rs2st.[EntityType], \r\n"
        L"  rs2st.[RowVersion], \r\n"
        L"  rs2st.[Catalog], \r\n"
        L"  rs2st.[Name], \r\n"
        L"  rs2st.[MaxRetention], \r\n"
        L"  rs2st.[Radar] \r\n"
        L"FROM [RadarSector2StartTimeseriesView] rs2st \r\n";
    WideString RadarSector2StartTimeseriesColumnData::BaseViewName = L"RadarSector2StartTimeseriesView";
    WideString RadarSector2StartTimeseriesColumnData::ViewAliasName = L"rs2st";

    WideString RadarSensitivityTimeControlLevelTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rstclt.[Id], \r\n"
        L"  rstclt.[EntityType], \r\n"
        L"  rstclt.[RowVersion], \r\n"
        L"  rstclt.[Catalog], \r\n"
        L"  rstclt.[Name], \r\n"
        L"  rstclt.[MaxRetention], \r\n"
        L"  rstclt.[Radar] \r\n"
        L"FROM [RadarSensitivityTimeControlLevelTimeseriesView] rstclt \r\n";
    WideString RadarSensitivityTimeControlLevelTimeseriesColumnData::BaseViewName = L"RadarSensitivityTimeControlLevelTimeseriesView";
    WideString RadarSensitivityTimeControlLevelTimeseriesColumnData::ViewAliasName = L"rstclt";

    WideString RadarTuningTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  ratuts.[Id], \r\n"
        L"  ratuts.[EntityType], \r\n"
        L"  ratuts.[RowVersion], \r\n"
        L"  ratuts.[Catalog], \r\n"
        L"  ratuts.[Name], \r\n"
        L"  ratuts.[MaxRetention], \r\n"
        L"  ratuts.[Radar] \r\n"
        L"FROM [RadarTuningTimeseriesView] ratuts \r\n";
    WideString RadarTuningTimeseriesColumnData::BaseViewName = L"RadarTuningTimeseriesView";
    WideString RadarTuningTimeseriesColumnData::ViewAliasName = L"ratuts";

    WideString VesselPersonsOnBoardTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  vpobt.[Id], \r\n"
        L"  vpobt.[EntityType], \r\n"
        L"  vpobt.[RowVersion], \r\n"
        L"  vpobt.[Catalog], \r\n"
        L"  vpobt.[Name], \r\n"
        L"  vpobt.[MaxRetention], \r\n"
        L"  vpobt.[Vessel] \r\n"
        L"FROM [VesselPersonsOnBoardTimeseriesView] vpobt \r\n";
    WideString VesselPersonsOnBoardTimeseriesColumnData::BaseViewName = L"VesselPersonsOnBoardTimeseriesView";
    WideString VesselPersonsOnBoardTimeseriesColumnData::ViewAliasName = L"vpobt";

    WideString Int64TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  i64t.[Id], \r\n"
        L"  i64t.[EntityType], \r\n"
        L"  i64t.[RowVersion], \r\n"
        L"  i64t.[Catalog], \r\n"
        L"  i64t.[Name], \r\n"
        L"  i64t.[MaxRetention] \r\n"
        L"FROM [Int64TimeseriesView] i64t \r\n";
    WideString Int64TimeseriesColumnData::BaseViewName = L"Int64TimeseriesView";
    WideString Int64TimeseriesColumnData::ViewAliasName = L"i64t";

    WideString Position2DTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  p2d.[Id], \r\n"
        L"  p2d.[EntityType], \r\n"
        L"  p2d.[RowVersion], \r\n"
        L"  p2d.[Catalog], \r\n"
        L"  p2d.[Name], \r\n"
        L"  p2d.[MaxRetention] \r\n"
        L"FROM [Position2DTimeseriesView] p2d \r\n";
    WideString Position2DTimeseriesColumnData::BaseViewName = L"Position2DTimeseriesView";
    WideString Position2DTimeseriesColumnData::ViewAliasName = L"p2d";

    WideString Position3DTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  p3d.[Id], \r\n"
        L"  p3d.[EntityType], \r\n"
        L"  p3d.[RowVersion], \r\n"
        L"  p3d.[Catalog], \r\n"
        L"  p3d.[Name], \r\n"
        L"  p3d.[MaxRetention] \r\n"
        L"FROM [Position3DTimeseriesView] p3d \r\n";
    WideString Position3DTimeseriesColumnData::BaseViewName = L"Position3DTimeseriesView";
    WideString Position3DTimeseriesColumnData::ViewAliasName = L"p3d";

    WideString ReferenceTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rt.[Id], \r\n"
        L"  rt.[EntityType], \r\n"
        L"  rt.[RowVersion], \r\n"
        L"  rt.[Catalog], \r\n"
        L"  rt.[Name], \r\n"
        L"  rt.[MaxRetention] \r\n"
        L"FROM [ReferenceTimeseriesView] rt \r\n";
    WideString ReferenceTimeseriesColumnData::BaseViewName = L"ReferenceTimeseriesView";
    WideString ReferenceTimeseriesColumnData::ViewAliasName = L"rt";

    WideString SByteTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  st.[Id], \r\n"
        L"  st.[EntityType], \r\n"
        L"  st.[RowVersion], \r\n"
        L"  st.[Catalog], \r\n"
        L"  st.[Name], \r\n"
        L"  st.[MaxRetention] \r\n"
        L"FROM [SByteTimeseriesView] st \r\n";
    WideString SByteTimeseriesColumnData::BaseViewName = L"SByteTimeseriesView";
    WideString SByteTimeseriesColumnData::ViewAliasName = L"st";

    WideString SingleTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  sits.[Id], \r\n"
        L"  sits.[EntityType], \r\n"
        L"  sits.[RowVersion], \r\n"
        L"  sits.[Catalog], \r\n"
        L"  sits.[Name], \r\n"
        L"  sits.[MaxRetention] \r\n"
        L"FROM [SingleTimeseriesView] sits \r\n";
    WideString SingleTimeseriesColumnData::BaseViewName = L"SingleTimeseriesView";
    WideString SingleTimeseriesColumnData::ViewAliasName = L"sits";

    WideString StringTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  stts.[Id], \r\n"
        L"  stts.[EntityType], \r\n"
        L"  stts.[RowVersion], \r\n"
        L"  stts.[Catalog], \r\n"
        L"  stts.[Name], \r\n"
        L"  stts.[MaxRetention] \r\n"
        L"FROM [StringTimeseriesView] stts \r\n";
    WideString StringTimeseriesColumnData::BaseViewName = L"StringTimeseriesView";
    WideString StringTimeseriesColumnData::ViewAliasName = L"stts";

    WideString TimeSpanTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  tst.[Id], \r\n"
        L"  tst.[EntityType], \r\n"
        L"  tst.[RowVersion], \r\n"
        L"  tst.[Catalog], \r\n"
        L"  tst.[Name], \r\n"
        L"  tst.[MaxRetention] \r\n"
        L"FROM [TimeSpanTimeseriesView] tst \r\n";
    WideString TimeSpanTimeseriesColumnData::BaseViewName = L"TimeSpanTimeseriesView";
    WideString TimeSpanTimeseriesColumnData::ViewAliasName = L"tst";

    WideString UInt16TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  u16t.[Id], \r\n"
        L"  u16t.[EntityType], \r\n"
        L"  u16t.[RowVersion], \r\n"
        L"  u16t.[Catalog], \r\n"
        L"  u16t.[Name], \r\n"
        L"  u16t.[MaxRetention] \r\n"
        L"FROM [UInt16TimeseriesView] u16t \r\n";
    WideString UInt16TimeseriesColumnData::BaseViewName = L"UInt16TimeseriesView";
    WideString UInt16TimeseriesColumnData::ViewAliasName = L"u16t";

    WideString UInt32TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  u32t.[Id], \r\n"
        L"  u32t.[EntityType], \r\n"
        L"  u32t.[RowVersion], \r\n"
        L"  u32t.[Catalog], \r\n"
        L"  u32t.[Name], \r\n"
        L"  u32t.[MaxRetention] \r\n"
        L"FROM [UInt32TimeseriesView] u32t \r\n";
    WideString UInt32TimeseriesColumnData::BaseViewName = L"UInt32TimeseriesView";
    WideString UInt32TimeseriesColumnData::ViewAliasName = L"u32t";

    WideString RadomeStatusTimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  rst.[Id], \r\n"
        L"  rst.[EntityType], \r\n"
        L"  rst.[RowVersion], \r\n"
        L"  rst.[Catalog], \r\n"
        L"  rst.[Name], \r\n"
        L"  rst.[MaxRetention], \r\n"
        L"  rst.[Radome] \r\n"
        L"FROM [RadomeStatusTimeseriesView] rst \r\n";
    WideString RadomeStatusTimeseriesColumnData::BaseViewName = L"RadomeStatusTimeseriesView";
    WideString RadomeStatusTimeseriesColumnData::ViewAliasName = L"rst";

    WideString UInt64TimeseriesColumnData::BaseQuery = L"SELECT \r\n"
        L"  u64t.[Id], \r\n"
        L"  u64t.[EntityType], \r\n"
        L"  u64t.[RowVersion], \r\n"
        L"  u64t.[Catalog], \r\n"
        L"  u64t.[Name], \r\n"
        L"  u64t.[MaxRetention] \r\n"
        L"FROM [UInt64TimeseriesView] u64t \r\n";
    WideString UInt64TimeseriesColumnData::BaseViewName = L"UInt64TimeseriesView";
    WideString UInt64TimeseriesColumnData::ViewAliasName = L"u64t";

    WideString TimeseriesCatalogColumnData::BaseQuery = L"SELECT \r\n"
        L"  tc.[Id], \r\n"
        L"  tc.[EntityType], \r\n"
        L"  tc.[RowVersion], \r\n"
        L"  tc.[Catalog], \r\n"
        L"  tc.[Name] \r\n"
        L"FROM [TimeseriesCatalogView] tc \r\n";
    WideString TimeseriesCatalogColumnData::BaseViewName = L"TimeseriesCatalogView";
    WideString TimeseriesCatalogColumnData::ViewAliasName = L"tc";

    WideString TimeseriesInfoColumnData::BaseQuery = L"SELECT \r\n"
        L"  ti.[Id], \r\n"
        L"  ti.[RowVersion], \r\n"
        L"  ti.[FirstTimestamp], \r\n"
        L"  ti.[LastTimestamp], \r\n"
        L"  ti.[Count] \r\n"
        L"FROM [TimeseriesInfoView] ti \r\n";
    WideString TimeseriesInfoColumnData::BaseViewName = L"TimeseriesInfoView";
    WideString TimeseriesInfoColumnData::ViewAliasName = L"ti";

    WideString TimeSpanTimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  tstv.[Id], \r\n"
        L"  tstv.[RowVersion], \r\n"
        L"  tstv.[Timeseries], \r\n"
        L"  tstv.[Timestamp], \r\n"
        L"  tstv.[Value] \r\n"
        L"FROM [TimeSpanTimeseriesValueView] tstv \r\n";
    WideString TimeSpanTimeseriesValueColumnData::BaseViewName = L"TimeSpanTimeseriesValueView";
    WideString TimeSpanTimeseriesValueColumnData::ViewAliasName = L"tstv";

    WideString TrackableItemTrackLinkColumnData::BaseQuery = L"SELECT \r\n"
        L"  titl.[Id], \r\n"
        L"  titl.[RowVersion], \r\n"
        L"  titl.[Item], \r\n"
        L"  titl.[Track], \r\n"
        L"  titl.[Start], \r\n"
        L"  titl.[End] \r\n"
        L"FROM [TrackableItemTrackLinkView] titl \r\n";
    WideString TrackableItemTrackLinkColumnData::BaseViewName = L"TrackableItemTrackLinkView";
    WideString TrackableItemTrackLinkColumnData::ViewAliasName = L"titl";

    WideString TrackBaseColumnData::BaseQuery = L"SELECT \r\n"
        L"  tb.[Id], \r\n"
        L"  tb.[EntityType], \r\n"
        L"  tb.[RowVersion], \r\n"
        L"  tb.[Tracker], \r\n"
        L"  tb.[TrackNumber], \r\n"
        L"  tb.[Timestamp] \r\n"
        L"FROM [TrackBaseView] tb \r\n";
    WideString TrackBaseColumnData::BaseViewName = L"TrackBaseView";
    WideString TrackBaseColumnData::ViewAliasName = L"tb";

    WideString TrackColumnData::BaseQuery = L"SELECT \r\n"
        L"  t.[Id], \r\n"
        L"  t.[EntityType], \r\n"
        L"  t.[RowVersion], \r\n"
        L"  t.[Tracker], \r\n"
        L"  t.[TrackNumber], \r\n"
        L"  t.[Timestamp] \r\n"
        L"FROM [TrackView] t \r\n";
    WideString TrackColumnData::BaseViewName = L"TrackView";
    WideString TrackColumnData::ViewAliasName = L"t";

    WideString Track3DColumnData::BaseQuery = L"SELECT \r\n"
        L"  t3d.[Id], \r\n"
        L"  t3d.[EntityType], \r\n"
        L"  t3d.[RowVersion], \r\n"
        L"  t3d.[Tracker], \r\n"
        L"  t3d.[TrackNumber], \r\n"
        L"  t3d.[Timestamp] \r\n"
        L"FROM [Track3DView] t3d \r\n";
    WideString Track3DColumnData::BaseViewName = L"Track3DView";
    WideString Track3DColumnData::ViewAliasName = L"t3d";

    WideString TrackerFilterParametersColumnData::BaseQuery = L"SELECT \r\n"
        L"  tfp.[Id], \r\n"
        L"  tfp.[RowVersion], \r\n"
        L"  tfp.[Tracker], \r\n"
        L"  tfp.[Name] \r\n"
        L"FROM [TrackerFilterParametersView] tfp \r\n";
    WideString TrackerFilterParametersColumnData::BaseViewName = L"TrackerFilterParametersView";
    WideString TrackerFilterParametersColumnData::ViewAliasName = L"tfp";

    WideString TrackerFilterParametersConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  tfpc.[Id], \r\n"
        L"  tfpc.[RowVersion], \r\n"
        L"  tfpc.[Parameters], \r\n"
        L"  tfpc.[Timestamp], \r\n"
        L"  tfpc.[UseNaivePredictor], \r\n"
        L"  tfpc.[NumberOfPoints], \r\n"
        L"  tfpc.[WindowSize], \r\n"
        L"  tfpc.[StabilizeCount], \r\n"
        L"  tfpc.[MaxBadPoints], \r\n"
        L"  tfpc.[ModelType], \r\n"
        L"  tfpc.[SigmaR], \r\n"
        L"  tfpc.[SigmaAcc], \r\n"
        L"  tfpc.[TauVel], \r\n"
        L"  tfpc.[TauAcc], \r\n"
        L"  tfpc.[DeltaRMin], \r\n"
        L"  tfpc.[DeltaVMax], \r\n"
        L"  tfpc.[DeltaAMax] \r\n"
        L"FROM [TrackerFilterParametersConfigurationView] tfpc \r\n";
    WideString TrackerFilterParametersConfigurationColumnData::BaseViewName = L"TrackerFilterParametersConfigurationView";
    WideString TrackerFilterParametersConfigurationColumnData::ViewAliasName = L"tfpc";

    WideString TrackInfoColumnData::BaseQuery = L"SELECT \r\n"
        L"  ti.[Id], \r\n"
        L"  ti.[RowVersion], \r\n"
        L"  ti.[FirstTimestamp], \r\n"
        L"  ti.[LastTimestamp], \r\n"
        L"  ti.[Count], \r\n"
        L"  ti.[NorthWestLatitude], \r\n"
        L"  ti.[NorthWestLongitude], \r\n"
        L"  ti.[SouthEastLatitude], \r\n"
        L"  ti.[SouthEastLongitude] \r\n"
        L"FROM [TrackInfoView] ti \r\n";
    WideString TrackInfoColumnData::BaseViewName = L"TrackInfoView";
    WideString TrackInfoColumnData::ViewAliasName = L"ti";

    WideString TrackingServiceOptionsColumnData::BaseQuery = L"SELECT \r\n"
        L"  tso.[Id], \r\n"
        L"  tso.[RowVersion], \r\n"
        L"  tso.[Timestamp], \r\n"
        L"  tso.[TimerInterval], \r\n"
        L"  tso.[MaxAgeOfCurrentTrackValue], \r\n"
        L"  tso.[FalseThreshold], \r\n"
        L"  tso.[DistanceThreshold], \r\n"
        L"  tso.[DistanceUnmergeThreshold], \r\n"
        L"  tso.[UnmergeLatency], \r\n"
        L"  tso.[KalmanFiltering], \r\n"
        L"  tso.[MaxCourseDeviation], \r\n"
        L"  tso.[MaxSpeedDeviation], \r\n"
        L"  tso.[MinimumSpeedThreshold] \r\n"
        L"FROM [TrackingServiceOptionsView] tso \r\n";
    WideString TrackingServiceOptionsColumnData::BaseViewName = L"TrackingServiceOptionsView";
    WideString TrackingServiceOptionsColumnData::ViewAliasName = L"tso";

    WideString TrackLinkColumnData::BaseQuery = L"SELECT \r\n"
        L"  tl.[Id], \r\n"
        L"  tl.[RowVersion], \r\n"
        L"  tl.[Primary], \r\n"
        L"  tl.[Secondary], \r\n"
        L"  tl.[Start], \r\n"
        L"  tl.[End] \r\n"
        L"FROM [TrackLinkView] tl \r\n";
    WideString TrackLinkColumnData::BaseViewName = L"TrackLinkView";
    WideString TrackLinkColumnData::ViewAliasName = L"tl";

    WideString TrackValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  tv.[Id], \r\n"
        L"  tv.[RowVersion], \r\n"
        L"  tv.[Track], \r\n"
        L"  tv.[Timestamp], \r\n"
        L"  tv.[Flags], \r\n"
        L"  tv.[Status], \r\n"
        L"  tv.[Latitude], \r\n"
        L"  tv.[Longitude], \r\n"
        L"  tv.[Speed], \r\n"
        L"  tv.[Course], \r\n"
        L"  tv.[Heading] \r\n"
        L"FROM [TrackValueView] tv \r\n";
    WideString TrackValueColumnData::BaseViewName = L"TrackValueView";
    WideString TrackValueColumnData::ViewAliasName = L"tv";

    WideString TrackValue3DColumnData::BaseQuery = L"SELECT \r\n"
        L"  tv3d.[Id], \r\n"
        L"  tv3d.[RowVersion], \r\n"
        L"  tv3d.[Track], \r\n"
        L"  tv3d.[Timestamp], \r\n"
        L"  tv3d.[Flags], \r\n"
        L"  tv3d.[Status], \r\n"
        L"  tv3d.[Latitude], \r\n"
        L"  tv3d.[Longitude], \r\n"
        L"  tv3d.[Altitude], \r\n"
        L"  tv3d.[Speed], \r\n"
        L"  tv3d.[Course], \r\n"
        L"  tv3d.[RateOfClimb] \r\n"
        L"FROM [TrackValue3DView] tv3d \r\n";
    WideString TrackValue3DColumnData::BaseViewName = L"TrackValue3DView";
    WideString TrackValue3DColumnData::ViewAliasName = L"tv3d";

    WideString UInt16TimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  u16tv.[Id], \r\n"
        L"  u16tv.[RowVersion], \r\n"
        L"  u16tv.[Timeseries], \r\n"
        L"  u16tv.[Timestamp], \r\n"
        L"  u16tv.[Value] \r\n"
        L"FROM [UInt16TimeseriesValueView] u16tv \r\n";
    WideString UInt16TimeseriesValueColumnData::BaseViewName = L"UInt16TimeseriesValueView";
    WideString UInt16TimeseriesValueColumnData::ViewAliasName = L"u16tv";

    WideString UInt32TimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  u32tv.[Id], \r\n"
        L"  u32tv.[RowVersion], \r\n"
        L"  u32tv.[Timeseries], \r\n"
        L"  u32tv.[Timestamp], \r\n"
        L"  u32tv.[Value] \r\n"
        L"FROM [UInt32TimeseriesValueView] u32tv \r\n";
    WideString UInt32TimeseriesValueColumnData::BaseViewName = L"UInt32TimeseriesValueView";
    WideString UInt32TimeseriesValueColumnData::ViewAliasName = L"u32tv";

    WideString UInt64TimeseriesValueColumnData::BaseQuery = L"SELECT \r\n"
        L"  u64tv.[Id], \r\n"
        L"  u64tv.[RowVersion], \r\n"
        L"  u64tv.[Timeseries], \r\n"
        L"  u64tv.[Timestamp], \r\n"
        L"  u64tv.[Value] \r\n"
        L"FROM [UInt64TimeseriesValueView] u64tv \r\n";
    WideString UInt64TimeseriesValueColumnData::BaseViewName = L"UInt64TimeseriesValueView";
    WideString UInt64TimeseriesValueColumnData::ViewAliasName = L"u64tv";

    WideString VehicleTypeColumnData::BaseQuery = L"SELECT \r\n"
        L"  vt.[Id], \r\n"
        L"  vt.[RowVersion], \r\n"
        L"  vt.[Name] \r\n"
        L"FROM [VehicleTypeView] vt \r\n";
    WideString VehicleTypeColumnData::BaseViewName = L"VehicleTypeView";
    WideString VehicleTypeColumnData::ViewAliasName = L"vt";

    WideString VesselTypeColumnData::BaseQuery = L"SELECT \r\n"
        L"  vt.[Id], \r\n"
        L"  vt.[RowVersion], \r\n"
        L"  vt.[Name], \r\n"
        L"  vt.[Code] \r\n"
        L"FROM [VesselTypeView] vt \r\n";
    WideString VesselTypeColumnData::BaseViewName = L"VesselTypeView";
    WideString VesselTypeColumnData::ViewAliasName = L"vt";

    WideString ViewColumnData::BaseQuery = L"SELECT \r\n"
        L"  v.[Id], \r\n"
        L"  v.[RowVersion], \r\n"
        L"  v.[Name], \r\n"
        L"  v.[LatitudeTimeseries], \r\n"
        L"  v.[LongitudeTimeseries], \r\n"
        L"  v.[ZoomLevelTimeseries] \r\n"
        L"FROM [ViewView] v \r\n";
    WideString ViewColumnData::BaseViewName = L"ViewView";
    WideString ViewColumnData::ViewAliasName = L"v";

    WideString ViewCameraLinkColumnData::BaseQuery = L"SELECT \r\n"
        L"  vcl.[Id], \r\n"
        L"  vcl.[RowVersion], \r\n"
        L"  vcl.[View], \r\n"
        L"  vcl.[Camera], \r\n"
        L"  vcl.[Start], \r\n"
        L"  vcl.[End] \r\n"
        L"FROM [ViewCameraLinkView] vcl \r\n";
    WideString ViewCameraLinkColumnData::BaseViewName = L"ViewCameraLinkView";
    WideString ViewCameraLinkColumnData::ViewAliasName = L"vcl";

    WideString ViewTrackerLinkColumnData::BaseQuery = L"SELECT \r\n"
        L"  vtl.[Id], \r\n"
        L"  vtl.[RowVersion], \r\n"
        L"  vtl.[View], \r\n"
        L"  vtl.[Tracker], \r\n"
        L"  vtl.[Start], \r\n"
        L"  vtl.[End] \r\n"
        L"FROM [ViewTrackerLinkView] vtl \r\n";
    WideString ViewTrackerLinkColumnData::BaseViewName = L"ViewTrackerLinkView";
    WideString ViewTrackerLinkColumnData::ViewAliasName = L"vtl";

    WideString WeatherStationCommandColumnData::BaseQuery = L"SELECT \r\n"
        L"  wsc.[Id], \r\n"
        L"  wsc.[RowVersion], \r\n"
        L"  wsc.[WeatherStation], \r\n"
        L"  wsc.[Timestamp], \r\n"
        L"  wsc.[DeviceCommandSourceType], \r\n"
        L"  wsc.[DeviceCommandSourceId], \r\n"
        L"  wsc.[Reply] \r\n"
        L"FROM [WeatherStationCommandView] wsc \r\n";
    WideString WeatherStationCommandColumnData::BaseViewName = L"WeatherStationCommandView";
    WideString WeatherStationCommandColumnData::ViewAliasName = L"wsc";

    WideString WeatherStationCommandReplyColumnData::BaseQuery = L"SELECT \r\n"
        L"  wscr.[Id], \r\n"
        L"  wscr.[RowVersion], \r\n"
        L"  wscr.[WeatherStation], \r\n"
        L"  wscr.[Timestamp], \r\n"
        L"  wscr.[Command], \r\n"
        L"  wscr.[Status], \r\n"
        L"  wscr.[Message] \r\n"
        L"FROM [WeatherStationCommandReplyView] wscr \r\n";
    WideString WeatherStationCommandReplyColumnData::BaseViewName = L"WeatherStationCommandReplyView";
    WideString WeatherStationCommandReplyColumnData::ViewAliasName = L"wscr";

    WideString WeatherStationConfigurationColumnData::BaseQuery = L"SELECT \r\n"
        L"  wsc.[Id], \r\n"
        L"  wsc.[RowVersion], \r\n"
        L"  wsc.[WeatherStation], \r\n"
        L"  wsc.[Timestamp], \r\n"
        L"  wsc.[NoDataTimeOut], \r\n"
        L"  wsc.[SendInterval], \r\n"
        L"  wsc.[Latitude], \r\n"
        L"  wsc.[Longitude], \r\n"
        L"  wsc.[GyroOffset], \r\n"
        L"  wsc.[EnableAveraging], \r\n"
        L"  wsc.[AveragingInterval] \r\n"
        L"FROM [WeatherStationConfigurationView] wsc \r\n";
    WideString WeatherStationConfigurationColumnData::BaseViewName = L"WeatherStationConfigurationView";
    WideString WeatherStationConfigurationColumnData::ViewAliasName = L"wsc";

    WideString ZoneColumnData::BaseQuery = L"SELECT \r\n"
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
        L"  z.[FillColor] \r\n"
        L"FROM [ZoneView] z \r\n";
    WideString ZoneColumnData::BaseViewName = L"ZoneView";
    WideString ZoneColumnData::ViewAliasName = L"z";

    WideString CircularZoneColumnData::BaseQuery = L"SELECT \r\n"
        L"  cz.[Id], \r\n"
        L"  cz.[EntityType], \r\n"
        L"  cz.[RowVersion], \r\n"
        L"  cz.[Name], \r\n"
        L"  cz.[Longitude], \r\n"
        L"  cz.[Latitude], \r\n"
        L"  cz.[AlarmType], \r\n"
        L"  cz.[AlarmTime], \r\n"
        L"  cz.[RadarTrackMinimumLifetime], \r\n"
        L"  cz.[Speed], \r\n"
        L"  cz.[StrokeColor], \r\n"
        L"  cz.[FillColor], \r\n"
        L"  cz.[Radius] \r\n"
        L"FROM [CircularZoneView] cz \r\n";
    WideString CircularZoneColumnData::BaseViewName = L"CircularZoneView";
    WideString CircularZoneColumnData::ViewAliasName = L"cz";

    WideString PolygonZoneColumnData::BaseQuery = L"SELECT \r\n"
        L"  pz.[Id], \r\n"
        L"  pz.[EntityType], \r\n"
        L"  pz.[RowVersion], \r\n"
        L"  pz.[Name], \r\n"
        L"  pz.[Longitude], \r\n"
        L"  pz.[Latitude], \r\n"
        L"  pz.[AlarmType], \r\n"
        L"  pz.[AlarmTime], \r\n"
        L"  pz.[RadarTrackMinimumLifetime], \r\n"
        L"  pz.[Speed], \r\n"
        L"  pz.[StrokeColor], \r\n"
        L"  pz.[FillColor], \r\n"
        L"  pz.[Polygon] \r\n"
        L"FROM [PolygonZoneView] pz \r\n";
    WideString PolygonZoneColumnData::BaseViewName = L"PolygonZoneView";
    WideString PolygonZoneColumnData::ViewAliasName = L"pz";

    WideString ZoneExceptionsColumnData::BaseQuery = L"SELECT \r\n"
        L"  ze.[Id], \r\n"
        L"  ze.[RowVersion], \r\n"
        L"  ze.[Zone], \r\n"
        L"  ze.[Timestamp] \r\n"
        L"FROM [ZoneExceptionsView] ze \r\n";
    WideString ZoneExceptionsColumnData::BaseViewName = L"ZoneExceptionsView";
    WideString ZoneExceptionsColumnData::ViewAliasName = L"ze";

    WideString ZoneExceptionsVesselLinkColumnData::BaseQuery = L"SELECT \r\n"
        L"  zevl.[Id], \r\n"
        L"  zevl.[RowVersion], \r\n"
        L"  zevl.[ZoneExceptions], \r\n"
        L"  zevl.[Vessel] \r\n"
        L"FROM [ZoneExceptionsVesselLinkView] zevl \r\n";
    WideString ZoneExceptionsVesselLinkColumnData::BaseViewName = L"ZoneExceptionsVesselLinkView";
    WideString ZoneExceptionsVesselLinkColumnData::ViewAliasName = L"zevl";

    WideString ZoneTrackAlarmColumnData::BaseQuery = L"SELECT \r\n"
        L"  zta.[Id], \r\n"
        L"  zta.[RowVersion], \r\n"
        L"  zta.[Track], \r\n"
        L"  zta.[Zone], \r\n"
        L"  zta.[RadarTrack], \r\n"
        L"  zta.[Timestamp], \r\n"
        L"  zta.[Latitude], \r\n"
        L"  zta.[Longitude], \r\n"
        L"  zta.[Speed], \r\n"
        L"  zta.[Course], \r\n"
        L"  zta.[Heading], \r\n"
        L"  zta.[EnterLatitude], \r\n"
        L"  zta.[EnterLongitude], \r\n"
        L"  zta.[LeaveLatitude], \r\n"
        L"  zta.[LeaveLongitude] \r\n"
        L"FROM [ZoneTrackAlarmView] zta \r\n";
    WideString ZoneTrackAlarmColumnData::BaseViewName = L"ZoneTrackAlarmView";
    WideString ZoneTrackAlarmColumnData::ViewAliasName = L"zta";

}
