using System;
using System.Diagnostics.CodeAnalysis;
using System.IO;

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;

using Harlinn.Common.Core.Net;
using Harlinn.Common.Core.Net.Data;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Harlinn.Common.Core.Net.IO;

using Barrelman.Data.Types;

namespace Barrelman.Data.Database
{
    public class ComplexAisMessageDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  am.[Id], \r\n" +
            "  am.[EntityType], \r\n" +
            "  am.[RowVersion], \r\n" +
            "  am.[AisDevice], \r\n" +
            "  am.[ReceivedTimestamp], \r\n" +
            "  am.[MessageSequenceNumber], \r\n" +
            "  am.[Repeat], \r\n" +
            "  am.[Mmsi], \r\n" +
            "  atnrm.[NavigationalAidType], \r\n" +
            "  atnrm.[Name], \r\n" +
            "  atnrm.[PositionAccuracy], \r\n" +
            "  atnrm.[Longitude], \r\n" +
            "  atnrm.[Latitude], \r\n" +
            "  atnrm.[DimensionToBow], \r\n" +
            "  atnrm.[DimensionToStern], \r\n" +
            "  atnrm.[DimensionToPort], \r\n" +
            "  atnrm.[DimensionToStarboard], \r\n" +
            "  atnrm.[PositionFixType], \r\n" +
            "  atnrm.[Timestamp], \r\n" +
            "  atnrm.[OffPosition], \r\n" +
            "  atnrm.[RegionalReserved], \r\n" +
            "  atnrm.[Raim], \r\n" +
            "  atnrm.[VirtualAid], \r\n" +
            "  atnrm.[Assigned], \r\n" +
            "  atnrm.[Spare], \r\n" +
            "  atnrm.[NameExtension], \r\n" +
            "  aasrm.[SequenceNumber], \r\n" +
            "  aasrm.[DestinationMmsi], \r\n" +
            "  aasrm.[RetransmitFlag], \r\n" +
            "  aasrm.[Spare], \r\n" +
            "  aasrm.[Text], \r\n" +
            "  absrm.[Timestamp], \r\n" +
            "  absrm.[PositionAccuracy], \r\n" +
            "  absrm.[Longitude], \r\n" +
            "  absrm.[Latitude], \r\n" +
            "  absrm.[PositionFixType], \r\n" +
            "  absrm.[Spare], \r\n" +
            "  absrm.[Raim], \r\n" +
            "  absrm.[RadioStatus], \r\n" +
            "  abac.[Spare], \r\n" +
            "  abac.[SequenceNumber1], \r\n" +
            "  abac.[Mmsi1], \r\n" +
            "  abac.[SequenceNumber2], \r\n" +
            "  abac.[Mmsi2], \r\n" +
            "  abac.[SequenceNumber3], \r\n" +
            "  abac.[Mmsi3], \r\n" +
            "  abac.[SequenceNumber4], \r\n" +
            "  abac.[Mmsi4], \r\n" +
            "  abam.[SequenceNumber], \r\n" +
            "  abam.[DestinationMmsi], \r\n" +
            "  abam.[RetransmitFlag], \r\n" +
            "  abam.[Spare], \r\n" +
            "  abam.[DesignatedAreaCode], \r\n" +
            "  abam.[FunctionalId], \r\n" +
            "  abbm.[Spare], \r\n" +
            "  abbm.[DesignatedAreaCode], \r\n" +
            "  abbm.[FunctionalId], \r\n" +
            "  adlmm.[Spare], \r\n" +
            "  adlmm.[Offset1], \r\n" +
            "  adlmm.[ReservedSlots1], \r\n" +
            "  adlmm.[Timeout1], \r\n" +
            "  adlmm.[Increment1], \r\n" +
            "  adlmm.[Offset2], \r\n" +
            "  adlmm.[ReservedSlots2], \r\n" +
            "  adlmm.[Timeout2], \r\n" +
            "  adlmm.[Increment2], \r\n" +
            "  adlmm.[Offset3], \r\n" +
            "  adlmm.[ReservedSlots3], \r\n" +
            "  adlmm.[Timeout3], \r\n" +
            "  adlmm.[Increment3], \r\n" +
            "  adlmm.[Offset4], \r\n" +
            "  adlmm.[ReservedSlots4], \r\n" +
            "  adlmm.[Timeout4], \r\n" +
            "  adlmm.[Increment4], \r\n" +
            "  aecbprm.[Reserved], \r\n" +
            "  aecbprm.[SpeedOverGround], \r\n" +
            "  aecbprm.[PositionAccuracy], \r\n" +
            "  aecbprm.[Longitude], \r\n" +
            "  aecbprm.[Latitude], \r\n" +
            "  aecbprm.[CourseOverGround], \r\n" +
            "  aecbprm.[TrueHeading], \r\n" +
            "  aecbprm.[Timestamp], \r\n" +
            "  aecbprm.[RegionalReserved], \r\n" +
            "  aecbprm.[Name], \r\n" +
            "  aecbprm.[ShipType], \r\n" +
            "  aecbprm.[DimensionToBow], \r\n" +
            "  aecbprm.[DimensionToStern], \r\n" +
            "  aecbprm.[DimensionToPort], \r\n" +
            "  aecbprm.[DimensionToStarboard], \r\n" +
            "  aecbprm.[PositionFixType], \r\n" +
            "  aecbprm.[Raim], \r\n" +
            "  aecbprm.[DataTerminalReady], \r\n" +
            "  aecbprm.[Assigned], \r\n" +
            "  aecbprm.[Spare], \r\n" +
            "  aim.[InterrogatedMmsi], \r\n" +
            "  aim.[FirstMessageType], \r\n" +
            "  aim.[FirstSlotOffset], \r\n" +
            "  aim.[SecondMessageType], \r\n" +
            "  aim.[SecondSlotOffset], \r\n" +
            "  aim.[SecondStationInterrogationMmsi], \r\n" +
            "  aim.[SecondStationFirstMessageType], \r\n" +
            "  aim.[SecondStationFirstSlotOffset], \r\n" +
            "  aprcab.[NavigationStatus], \r\n" +
            "  aprcab.[RateOfTurn], \r\n" +
            "  aprcab.[SpeedOverGround], \r\n" +
            "  aprcab.[PositionAccuracy], \r\n" +
            "  aprcab.[Longitude], \r\n" +
            "  aprcab.[Latitude], \r\n" +
            "  aprcab.[CourseOverGround], \r\n" +
            "  aprcab.[TrueHeading], \r\n" +
            "  aprcab.[Timestamp], \r\n" +
            "  aprcab.[ManeuverIndicator], \r\n" +
            "  aprcab.[Spare], \r\n" +
            "  aprcab.[Raim], \r\n" +
            "  aprcab.[RadioStatus], \r\n" +
            "  aprflram.[PositionAccuracy], \r\n" +
            "  aprflram.[Raim], \r\n" +
            "  aprflram.[NavigationStatus], \r\n" +
            "  aprflram.[Longitude], \r\n" +
            "  aprflram.[Latitude], \r\n" +
            "  aprflram.[SpeedOverGround], \r\n" +
            "  aprflram.[CourseOverGround], \r\n" +
            "  aprflram.[GnssPositionStatus], \r\n" +
            "  aprflram.[Spare], \r\n" +
            "  asram.[Spare], \r\n" +
            "  asram.[SequenceNumber1], \r\n" +
            "  asram.[Mmsi1], \r\n" +
            "  asram.[SequenceNumber2], \r\n" +
            "  asram.[Mmsi2], \r\n" +
            "  asram.[SequenceNumber3], \r\n" +
            "  asram.[Mmsi3], \r\n" +
            "  asram.[SequenceNumber4], \r\n" +
            "  asram.[Mmsi4], \r\n" +
            "  ascbprm.[Reserved], \r\n" +
            "  ascbprm.[SpeedOverGround], \r\n" +
            "  ascbprm.[PositionAccuracy], \r\n" +
            "  ascbprm.[Longitude], \r\n" +
            "  ascbprm.[Latitude], \r\n" +
            "  ascbprm.[CourseOverGround], \r\n" +
            "  ascbprm.[TrueHeading], \r\n" +
            "  ascbprm.[Timestamp], \r\n" +
            "  ascbprm.[RegionalReserved], \r\n" +
            "  ascbprm.[IsCsUnit], \r\n" +
            "  ascbprm.[HasDisplay], \r\n" +
            "  ascbprm.[HasDscCapability], \r\n" +
            "  ascbprm.[Band], \r\n" +
            "  ascbprm.[CanAcceptMessage22], \r\n" +
            "  ascbprm.[Assigned], \r\n" +
            "  ascbprm.[Raim], \r\n" +
            "  ascbprm.[RadioStatus], \r\n" +
            "  assaprm.[Altitude], \r\n" +
            "  assaprm.[SpeedOverGround], \r\n" +
            "  assaprm.[PositionAccuracy], \r\n" +
            "  assaprm.[Longitude], \r\n" +
            "  assaprm.[Latitude], \r\n" +
            "  assaprm.[CourseOverGround], \r\n" +
            "  assaprm.[Timestamp], \r\n" +
            "  assaprm.[Reserved], \r\n" +
            "  assaprm.[DataTerminalReady], \r\n" +
            "  assaprm.[Spare], \r\n" +
            "  assaprm.[Assigned], \r\n" +
            "  assaprm.[Raim], \r\n" +
            "  assaprm.[RadioStatus], \r\n" +
            "  asavrdm.[AisVersion], \r\n" +
            "  asavrdm.[ImoNumber], \r\n" +
            "  asavrdm.[Callsign], \r\n" +
            "  asavrdm.[ShipName], \r\n" +
            "  asavrdm.[ShipType], \r\n" +
            "  asavrdm.[DimensionToBow], \r\n" +
            "  asavrdm.[DimensionToStern], \r\n" +
            "  asavrdm.[DimensionToPort], \r\n" +
            "  asavrdm.[DimensionToStarboard], \r\n" +
            "  asavrdm.[PositionFixType], \r\n" +
            "  asavrdm.[EstimatedTimeOfArrival], \r\n" +
            "  asavrdm.[Draught], \r\n" +
            "  asavrdm.[Destination], \r\n" +
            "  asavrdm.[DataTerminalReady], \r\n" +
            "  asavrdm.[Spare], \r\n" +
            "  asdrm.[PartNumber], \r\n" +
            "  asdrpa.[ShipName], \r\n" +
            "  asdrpa.[Spare], \r\n" +
            "  asdrpb.[ShipType], \r\n" +
            "  asdrpb.[VendorId], \r\n" +
            "  asdrpb.[UnitModelCode], \r\n" +
            "  asdrpb.[SerialNumber], \r\n" +
            "  asdrpb.[Callsign], \r\n" +
            "  asdrpb.[DimensionToBow], \r\n" +
            "  asdrpb.[DimensionToStern], \r\n" +
            "  asdrpb.[DimensionToPort], \r\n" +
            "  asdrpb.[DimensionToStarboard], \r\n" +
            "  asdrpb.[MothershipMmsi], \r\n" +
            "  asdrpb.[PositionFixType], \r\n" +
            "  asdrpb.[Spare], \r\n" +
            "  auadim.[Spare1], \r\n" +
            "  auadim.[DestinationMmsi], \r\n" +
            "  auadim.[Spare2], \r\n" +
            "  auadrm.[Datetime], \r\n" +
            "  auadrm.[PositionAccuracy], \r\n" +
            "  auadrm.[Longitude], \r\n" +
            "  auadrm.[Latitude], \r\n" +
            "  auadrm.[PositionFixType], \r\n" +
            "  auadrm.[Spare], \r\n" +
            "  auadrm.[Raim], \r\n" +
            "  auadrm.[RadioStatus], \r\n" +
            "  abam.[Data], \r\n" +
            "  abbm.[Data] \r\n" +
            "FROM [AisMessageView] am \r\n" +
            "  LEFT JOIN [AidToNavigationReportMessage] atnrm ON(am.[Id] = atnrm.[Id] ) \r\n" +
            "  LEFT JOIN [AisAddressedSafetyRelatedMessage] aasrm ON(am.[Id] = aasrm.[Id] ) \r\n" +
            "  LEFT JOIN [AisBaseStationReportMessage] absrm ON(am.[Id] = absrm.[Id] ) \r\n" +
            "  LEFT JOIN [AisBinaryAcknowledgeMessage] abac ON(am.[Id] = abac.[Id] ) \r\n" +
            "  LEFT JOIN [AisBinaryAddressedMessage] abam ON(am.[Id] = abam.[Id] ) \r\n" +
            "  LEFT JOIN [AisBinaryBroadcastMessage] abbm ON(am.[Id] = abbm.[Id] ) \r\n" +
            "  LEFT JOIN [AisDataLinkManagementMessage] adlmm ON(am.[Id] = adlmm.[Id] ) \r\n" +
            "  LEFT JOIN [AisExtendedClassBCsPositionReportMessage] aecbprm ON(am.[Id] = aecbprm.[Id] ) \r\n" +
            "  LEFT JOIN [AisInterrogationMessage] aim ON(am.[Id] = aim.[Id] ) \r\n" +
            "  LEFT JOIN [AisPositionReportClassAMessageBase] aprcab ON(am.[Id] = aprcab.[Id] ) \r\n" +
            "  LEFT JOIN [AisPositionReportClassAAssignedScheduleMessage] aprcasm ON(am.[Id] = aprcasm.[Id] ) \r\n" +
            "  LEFT JOIN [AisPositionReportClassAMessage] aprca ON(am.[Id] = aprca.[Id] ) \r\n" +
            "  LEFT JOIN [AisPositionReportClassAResponseToInterrogationMessage] aprcatim ON(am.[Id] = aprcatim.[Id] ) \r\n" +
            "  LEFT JOIN [AisPositionReportForLongRangeApplicationsMessage] aprflram ON(am.[Id] = aprflram.[Id] ) \r\n" +
            "  LEFT JOIN [AisSafetyRelatedAcknowledgmentMessage] asram ON(am.[Id] = asram.[Id] ) \r\n" +
            "  LEFT JOIN [AisStandardClassBCsPositionReportMessage] ascbprm ON(am.[Id] = ascbprm.[Id] ) \r\n" +
            "  LEFT JOIN [AisStandardSarAircraftPositionReportMessage] assaprm ON(am.[Id] = assaprm.[Id] ) \r\n" +
            "  LEFT JOIN [AisStaticAndVoyageRelatedDataMessage] asavrdm ON(am.[Id] = asavrdm.[Id] ) \r\n" +
            "  LEFT JOIN [AisStaticDataReportMessage] asdrm ON(am.[Id] = asdrm.[Id] ) \r\n" +
            "  LEFT JOIN [AisStaticDataReportPartAMessage] asdrpa ON(am.[Id] = asdrpa.[Id] ) \r\n" +
            "  LEFT JOIN [AisStaticDataReportPartBMessage] asdrpb ON(am.[Id] = asdrpb.[Id] ) \r\n" +
            "  LEFT JOIN [AisUtcAndDateInquiryMessage] auadim ON(am.[Id] = auadim.[Id] ) \r\n" +
            "  LEFT JOIN [AisUtcAndDateResponseMessage] auadrm ON(am.[Id] = auadrm.[Id] ) \r\n";

        public const string BaseViewName = "AisMessageView";
        public const string ViewAliasName = "am";

        public const int AM_ID_FIELD_ID = 0;
        public const int AM_KIND_FIELD_ID = 1;
        public const int AM_ROWVERSION_FIELD_ID = 2;
        public const int AM_AISDEVICE_FIELD_ID = 3;
        public const int AM_RECEIVEDTIMESTAMP_FIELD_ID = 4;
        public const int AM_MESSAGESEQUENCENUMBER_FIELD_ID = 5;
        public const int AM_REPEAT_FIELD_ID = 6;
        public const int AM_MMSI_FIELD_ID = 7;
        public const int ATNRM_NAVIGATIONALAIDTYPE_FIELD_ID = 8;
        public const int ATNRM_NAME_FIELD_ID = 9;
        public const int ATNRM_POSITIONACCURACY_FIELD_ID = 10;
        public const int ATNRM_LONGITUDE_FIELD_ID = 11;
        public const int ATNRM_LATITUDE_FIELD_ID = 12;
        public const int ATNRM_DIMENSIONTOBOW_FIELD_ID = 13;
        public const int ATNRM_DIMENSIONTOSTERN_FIELD_ID = 14;
        public const int ATNRM_DIMENSIONTOPORT_FIELD_ID = 15;
        public const int ATNRM_DIMENSIONTOSTARBOARD_FIELD_ID = 16;
        public const int ATNRM_POSITIONFIXTYPE_FIELD_ID = 17;
        public const int ATNRM_TIMESTAMP_FIELD_ID = 18;
        public const int ATNRM_OFFPOSITION_FIELD_ID = 19;
        public const int ATNRM_REGIONALRESERVED_FIELD_ID = 20;
        public const int ATNRM_RAIM_FIELD_ID = 21;
        public const int ATNRM_VIRTUALAID_FIELD_ID = 22;
        public const int ATNRM_ASSIGNED_FIELD_ID = 23;
        public const int ATNRM_SPARE_FIELD_ID = 24;
        public const int ATNRM_NAMEEXTENSION_FIELD_ID = 25;
        public const int AASRM_SEQUENCENUMBER_FIELD_ID = 26;
        public const int AASRM_DESTINATIONMMSI_FIELD_ID = 27;
        public const int AASRM_RETRANSMITFLAG_FIELD_ID = 28;
        public const int AASRM_SPARE_FIELD_ID = 29;
        public const int AASRM_TEXT_FIELD_ID = 30;
        public const int ABSRM_TIMESTAMP_FIELD_ID = 31;
        public const int ABSRM_POSITIONACCURACY_FIELD_ID = 32;
        public const int ABSRM_LONGITUDE_FIELD_ID = 33;
        public const int ABSRM_LATITUDE_FIELD_ID = 34;
        public const int ABSRM_POSITIONFIXTYPE_FIELD_ID = 35;
        public const int ABSRM_SPARE_FIELD_ID = 36;
        public const int ABSRM_RAIM_FIELD_ID = 37;
        public const int ABSRM_RADIOSTATUS_FIELD_ID = 38;
        public const int ABAC_SPARE_FIELD_ID = 39;
        public const int ABAC_SEQUENCENUMBER1_FIELD_ID = 40;
        public const int ABAC_MMSI1_FIELD_ID = 41;
        public const int ABAC_SEQUENCENUMBER2_FIELD_ID = 42;
        public const int ABAC_MMSI2_FIELD_ID = 43;
        public const int ABAC_SEQUENCENUMBER3_FIELD_ID = 44;
        public const int ABAC_MMSI3_FIELD_ID = 45;
        public const int ABAC_SEQUENCENUMBER4_FIELD_ID = 46;
        public const int ABAC_MMSI4_FIELD_ID = 47;
        public const int ABAM_SEQUENCENUMBER_FIELD_ID = 48;
        public const int ABAM_DESTINATIONMMSI_FIELD_ID = 49;
        public const int ABAM_RETRANSMITFLAG_FIELD_ID = 50;
        public const int ABAM_SPARE_FIELD_ID = 51;
        public const int ABAM_DESIGNATEDAREACODE_FIELD_ID = 52;
        public const int ABAM_FUNCTIONALID_FIELD_ID = 53;
        public const int ABBM_SPARE_FIELD_ID = 54;
        public const int ABBM_DESIGNATEDAREACODE_FIELD_ID = 55;
        public const int ABBM_FUNCTIONALID_FIELD_ID = 56;
        public const int ADLMM_SPARE_FIELD_ID = 57;
        public const int ADLMM_OFFSET1_FIELD_ID = 58;
        public const int ADLMM_RESERVEDSLOTS1_FIELD_ID = 59;
        public const int ADLMM_TIMEOUT1_FIELD_ID = 60;
        public const int ADLMM_INCREMENT1_FIELD_ID = 61;
        public const int ADLMM_OFFSET2_FIELD_ID = 62;
        public const int ADLMM_RESERVEDSLOTS2_FIELD_ID = 63;
        public const int ADLMM_TIMEOUT2_FIELD_ID = 64;
        public const int ADLMM_INCREMENT2_FIELD_ID = 65;
        public const int ADLMM_OFFSET3_FIELD_ID = 66;
        public const int ADLMM_RESERVEDSLOTS3_FIELD_ID = 67;
        public const int ADLMM_TIMEOUT3_FIELD_ID = 68;
        public const int ADLMM_INCREMENT3_FIELD_ID = 69;
        public const int ADLMM_OFFSET4_FIELD_ID = 70;
        public const int ADLMM_RESERVEDSLOTS4_FIELD_ID = 71;
        public const int ADLMM_TIMEOUT4_FIELD_ID = 72;
        public const int ADLMM_INCREMENT4_FIELD_ID = 73;
        public const int AECBPRM_RESERVED_FIELD_ID = 74;
        public const int AECBPRM_SPEEDOVERGROUND_FIELD_ID = 75;
        public const int AECBPRM_POSITIONACCURACY_FIELD_ID = 76;
        public const int AECBPRM_LONGITUDE_FIELD_ID = 77;
        public const int AECBPRM_LATITUDE_FIELD_ID = 78;
        public const int AECBPRM_COURSEOVERGROUND_FIELD_ID = 79;
        public const int AECBPRM_TRUEHEADING_FIELD_ID = 80;
        public const int AECBPRM_TIMESTAMP_FIELD_ID = 81;
        public const int AECBPRM_REGIONALRESERVED_FIELD_ID = 82;
        public const int AECBPRM_NAME_FIELD_ID = 83;
        public const int AECBPRM_SHIPTYPE_FIELD_ID = 84;
        public const int AECBPRM_DIMENSIONTOBOW_FIELD_ID = 85;
        public const int AECBPRM_DIMENSIONTOSTERN_FIELD_ID = 86;
        public const int AECBPRM_DIMENSIONTOPORT_FIELD_ID = 87;
        public const int AECBPRM_DIMENSIONTOSTARBOARD_FIELD_ID = 88;
        public const int AECBPRM_POSITIONFIXTYPE_FIELD_ID = 89;
        public const int AECBPRM_RAIM_FIELD_ID = 90;
        public const int AECBPRM_DATATERMINALREADY_FIELD_ID = 91;
        public const int AECBPRM_ASSIGNED_FIELD_ID = 92;
        public const int AECBPRM_SPARE_FIELD_ID = 93;
        public const int AIM_INTERROGATEDMMSI_FIELD_ID = 94;
        public const int AIM_FIRSTMESSAGETYPE_FIELD_ID = 95;
        public const int AIM_FIRSTSLOTOFFSET_FIELD_ID = 96;
        public const int AIM_SECONDMESSAGETYPE_FIELD_ID = 97;
        public const int AIM_SECONDSLOTOFFSET_FIELD_ID = 98;
        public const int AIM_SECONDSTATIONINTERROGATIONMMSI_FIELD_ID = 99;
        public const int AIM_SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID = 100;
        public const int AIM_SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID = 101;
        public const int APRCAB_NAVIGATIONSTATUS_FIELD_ID = 102;
        public const int APRCAB_RATEOFTURN_FIELD_ID = 103;
        public const int APRCAB_SPEEDOVERGROUND_FIELD_ID = 104;
        public const int APRCAB_POSITIONACCURACY_FIELD_ID = 105;
        public const int APRCAB_LONGITUDE_FIELD_ID = 106;
        public const int APRCAB_LATITUDE_FIELD_ID = 107;
        public const int APRCAB_COURSEOVERGROUND_FIELD_ID = 108;
        public const int APRCAB_TRUEHEADING_FIELD_ID = 109;
        public const int APRCAB_TIMESTAMP_FIELD_ID = 110;
        public const int APRCAB_MANEUVERINDICATOR_FIELD_ID = 111;
        public const int APRCAB_SPARE_FIELD_ID = 112;
        public const int APRCAB_RAIM_FIELD_ID = 113;
        public const int APRCAB_RADIOSTATUS_FIELD_ID = 114;
        public const int APRFLRAM_POSITIONACCURACY_FIELD_ID = 115;
        public const int APRFLRAM_RAIM_FIELD_ID = 116;
        public const int APRFLRAM_NAVIGATIONSTATUS_FIELD_ID = 117;
        public const int APRFLRAM_LONGITUDE_FIELD_ID = 118;
        public const int APRFLRAM_LATITUDE_FIELD_ID = 119;
        public const int APRFLRAM_SPEEDOVERGROUND_FIELD_ID = 120;
        public const int APRFLRAM_COURSEOVERGROUND_FIELD_ID = 121;
        public const int APRFLRAM_GNSSPOSITIONSTATUS_FIELD_ID = 122;
        public const int APRFLRAM_SPARE_FIELD_ID = 123;
        public const int ASRAM_SPARE_FIELD_ID = 124;
        public const int ASRAM_SEQUENCENUMBER1_FIELD_ID = 125;
        public const int ASRAM_MMSI1_FIELD_ID = 126;
        public const int ASRAM_SEQUENCENUMBER2_FIELD_ID = 127;
        public const int ASRAM_MMSI2_FIELD_ID = 128;
        public const int ASRAM_SEQUENCENUMBER3_FIELD_ID = 129;
        public const int ASRAM_MMSI3_FIELD_ID = 130;
        public const int ASRAM_SEQUENCENUMBER4_FIELD_ID = 131;
        public const int ASRAM_MMSI4_FIELD_ID = 132;
        public const int ASCBPRM_RESERVED_FIELD_ID = 133;
        public const int ASCBPRM_SPEEDOVERGROUND_FIELD_ID = 134;
        public const int ASCBPRM_POSITIONACCURACY_FIELD_ID = 135;
        public const int ASCBPRM_LONGITUDE_FIELD_ID = 136;
        public const int ASCBPRM_LATITUDE_FIELD_ID = 137;
        public const int ASCBPRM_COURSEOVERGROUND_FIELD_ID = 138;
        public const int ASCBPRM_TRUEHEADING_FIELD_ID = 139;
        public const int ASCBPRM_TIMESTAMP_FIELD_ID = 140;
        public const int ASCBPRM_REGIONALRESERVED_FIELD_ID = 141;
        public const int ASCBPRM_ISCSUNIT_FIELD_ID = 142;
        public const int ASCBPRM_HASDISPLAY_FIELD_ID = 143;
        public const int ASCBPRM_HASDSCCAPABILITY_FIELD_ID = 144;
        public const int ASCBPRM_BAND_FIELD_ID = 145;
        public const int ASCBPRM_CANACCEPTMESSAGE22_FIELD_ID = 146;
        public const int ASCBPRM_ASSIGNED_FIELD_ID = 147;
        public const int ASCBPRM_RAIM_FIELD_ID = 148;
        public const int ASCBPRM_RADIOSTATUS_FIELD_ID = 149;
        public const int ASSAPRM_ALTITUDE_FIELD_ID = 150;
        public const int ASSAPRM_SPEEDOVERGROUND_FIELD_ID = 151;
        public const int ASSAPRM_POSITIONACCURACY_FIELD_ID = 152;
        public const int ASSAPRM_LONGITUDE_FIELD_ID = 153;
        public const int ASSAPRM_LATITUDE_FIELD_ID = 154;
        public const int ASSAPRM_COURSEOVERGROUND_FIELD_ID = 155;
        public const int ASSAPRM_TIMESTAMP_FIELD_ID = 156;
        public const int ASSAPRM_RESERVED_FIELD_ID = 157;
        public const int ASSAPRM_DATATERMINALREADY_FIELD_ID = 158;
        public const int ASSAPRM_SPARE_FIELD_ID = 159;
        public const int ASSAPRM_ASSIGNED_FIELD_ID = 160;
        public const int ASSAPRM_RAIM_FIELD_ID = 161;
        public const int ASSAPRM_RADIOSTATUS_FIELD_ID = 162;
        public const int ASAVRDM_AISVERSION_FIELD_ID = 163;
        public const int ASAVRDM_IMONUMBER_FIELD_ID = 164;
        public const int ASAVRDM_CALLSIGN_FIELD_ID = 165;
        public const int ASAVRDM_SHIPNAME_FIELD_ID = 166;
        public const int ASAVRDM_SHIPTYPE_FIELD_ID = 167;
        public const int ASAVRDM_DIMENSIONTOBOW_FIELD_ID = 168;
        public const int ASAVRDM_DIMENSIONTOSTERN_FIELD_ID = 169;
        public const int ASAVRDM_DIMENSIONTOPORT_FIELD_ID = 170;
        public const int ASAVRDM_DIMENSIONTOSTARBOARD_FIELD_ID = 171;
        public const int ASAVRDM_POSITIONFIXTYPE_FIELD_ID = 172;
        public const int ASAVRDM_ESTIMATEDTIMEOFARRIVAL_FIELD_ID = 173;
        public const int ASAVRDM_DRAUGHT_FIELD_ID = 174;
        public const int ASAVRDM_DESTINATION_FIELD_ID = 175;
        public const int ASAVRDM_DATATERMINALREADY_FIELD_ID = 176;
        public const int ASAVRDM_SPARE_FIELD_ID = 177;
        public const int ASDRM_PARTNUMBER_FIELD_ID = 178;
        public const int ASDRPA_SHIPNAME_FIELD_ID = 179;
        public const int ASDRPA_SPARE_FIELD_ID = 180;
        public const int ASDRPB_SHIPTYPE_FIELD_ID = 181;
        public const int ASDRPB_VENDORID_FIELD_ID = 182;
        public const int ASDRPB_UNITMODELCODE_FIELD_ID = 183;
        public const int ASDRPB_SERIALNUMBER_FIELD_ID = 184;
        public const int ASDRPB_CALLSIGN_FIELD_ID = 185;
        public const int ASDRPB_DIMENSIONTOBOW_FIELD_ID = 186;
        public const int ASDRPB_DIMENSIONTOSTERN_FIELD_ID = 187;
        public const int ASDRPB_DIMENSIONTOPORT_FIELD_ID = 188;
        public const int ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID = 189;
        public const int ASDRPB_MOTHERSHIPMMSI_FIELD_ID = 190;
        public const int ASDRPB_POSITIONFIXTYPE_FIELD_ID = 191;
        public const int ASDRPB_SPARE_FIELD_ID = 192;
        public const int AUADIM_SPARE1_FIELD_ID = 193;
        public const int AUADIM_DESTINATIONMMSI_FIELD_ID = 194;
        public const int AUADIM_SPARE2_FIELD_ID = 195;
        public const int AUADRM_DATETIME_FIELD_ID = 196;
        public const int AUADRM_POSITIONACCURACY_FIELD_ID = 197;
        public const int AUADRM_LONGITUDE_FIELD_ID = 198;
        public const int AUADRM_LATITUDE_FIELD_ID = 199;
        public const int AUADRM_POSITIONFIXTYPE_FIELD_ID = 200;
        public const int AUADRM_SPARE_FIELD_ID = 201;
        public const int AUADRM_RAIM_FIELD_ID = 202;
        public const int AUADRM_RADIOSTATUS_FIELD_ID = 203;
        public const int ABAM_DATA_FIELD_ID = 204;
        public const int ABBM_DATA_FIELD_ID = 205;
        public ComplexAisMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( AM_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( AM_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( AM_ROWVERSION_FIELD_ID );
            }
        }
        public Guid AisDevice
        {
            get
            {
                return GetGuid( AM_AISDEVICE_FIELD_ID );
            }
        }
        public DateTime ReceivedTimestamp
        {
            get
            {
                return new DateTime( GetInt64( AM_RECEIVEDTIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public long MessageSequenceNumber
        {
            get
            {
                return GetInt64( AM_MESSAGESEQUENCENUMBER_FIELD_ID );
            }
        }
        public int Repeat
        {
            get
            {
                return GetInt32( AM_REPEAT_FIELD_ID );
            }
        }
        public Guid? Mmsi
        {
            get
            {
                return GetNullableGuid( AM_MMSI_FIELD_ID );
            }
        }
        public Types.NavigationalAidType AidToNavigationReportMessageNavigationalAidType
        {
            get
            {
                return GetEnum<Types.NavigationalAidType>( ATNRM_NAVIGATIONALAIDTYPE_FIELD_ID );
            }
        }
        public string AidToNavigationReportMessageName
        {
            get
            {
                return GetString( ATNRM_NAME_FIELD_ID );
            }
        }
        public Types.PositionAccuracy AidToNavigationReportMessagePositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( ATNRM_POSITIONACCURACY_FIELD_ID );
            }
        }
        public double AidToNavigationReportMessageLongitude
        {
            get
            {
                return GetDouble( ATNRM_LONGITUDE_FIELD_ID );
            }
        }
        public double AidToNavigationReportMessageLatitude
        {
            get
            {
                return GetDouble( ATNRM_LATITUDE_FIELD_ID );
            }
        }
        public int AidToNavigationReportMessageDimensionToBow
        {
            get
            {
                return GetInt32( ATNRM_DIMENSIONTOBOW_FIELD_ID );
            }
        }
        public int AidToNavigationReportMessageDimensionToStern
        {
            get
            {
                return GetInt32( ATNRM_DIMENSIONTOSTERN_FIELD_ID );
            }
        }
        public int AidToNavigationReportMessageDimensionToPort
        {
            get
            {
                return GetInt32( ATNRM_DIMENSIONTOPORT_FIELD_ID );
            }
        }
        public int AidToNavigationReportMessageDimensionToStarboard
        {
            get
            {
                return GetInt32( ATNRM_DIMENSIONTOSTARBOARD_FIELD_ID );
            }
        }
        public Types.PositionFixType AidToNavigationReportMessagePositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( ATNRM_POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public int AidToNavigationReportMessageTimestamp
        {
            get
            {
                return GetInt32( ATNRM_TIMESTAMP_FIELD_ID );
            }
        }
        public bool AidToNavigationReportMessageOffPosition
        {
            get
            {
                return GetBoolean( ATNRM_OFFPOSITION_FIELD_ID );
            }
        }
        public int AidToNavigationReportMessageRegionalReserved
        {
            get
            {
                return GetInt32( ATNRM_REGIONALRESERVED_FIELD_ID );
            }
        }
        public Types.Raim AidToNavigationReportMessageRaim
        {
            get
            {
                return GetEnum<Types.Raim>( ATNRM_RAIM_FIELD_ID );
            }
        }
        public bool AidToNavigationReportMessageVirtualAid
        {
            get
            {
                return GetBoolean( ATNRM_VIRTUALAID_FIELD_ID );
            }
        }
        public bool AidToNavigationReportMessageAssigned
        {
            get
            {
                return GetBoolean( ATNRM_ASSIGNED_FIELD_ID );
            }
        }
        public int AidToNavigationReportMessageSpare
        {
            get
            {
                return GetInt32( ATNRM_SPARE_FIELD_ID );
            }
        }
        public string AidToNavigationReportMessageNameExtension
        {
            get
            {
                return GetString( ATNRM_NAMEEXTENSION_FIELD_ID );
            }
        }
        public int AisAddressedSafetyRelatedMessageSequenceNumber
        {
            get
            {
                return GetInt32( AASRM_SEQUENCENUMBER_FIELD_ID );
            }
        }
        public Guid? AisAddressedSafetyRelatedMessageDestinationMmsi
        {
            get
            {
                return GetNullableGuid( AASRM_DESTINATIONMMSI_FIELD_ID );
            }
        }
        public bool AisAddressedSafetyRelatedMessageRetransmitFlag
        {
            get
            {
                return GetBoolean( AASRM_RETRANSMITFLAG_FIELD_ID );
            }
        }
        public int AisAddressedSafetyRelatedMessageSpare
        {
            get
            {
                return GetInt32( AASRM_SPARE_FIELD_ID );
            }
        }
        public string AisAddressedSafetyRelatedMessageText
        {
            get
            {
                return GetString( AASRM_TEXT_FIELD_ID );
            }
        }
        public DateTime AisBaseStationReportMessageTimestamp
        {
            get
            {
                return new DateTime( GetInt64( ABSRM_TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.PositionAccuracy AisBaseStationReportMessagePositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( ABSRM_POSITIONACCURACY_FIELD_ID );
            }
        }
        public double AisBaseStationReportMessageLongitude
        {
            get
            {
                return GetDouble( ABSRM_LONGITUDE_FIELD_ID );
            }
        }
        public double AisBaseStationReportMessageLatitude
        {
            get
            {
                return GetDouble( ABSRM_LATITUDE_FIELD_ID );
            }
        }
        public Types.PositionFixType AisBaseStationReportMessagePositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( ABSRM_POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public int AisBaseStationReportMessageSpare
        {
            get
            {
                return GetInt32( ABSRM_SPARE_FIELD_ID );
            }
        }
        public Types.Raim AisBaseStationReportMessageRaim
        {
            get
            {
                return GetEnum<Types.Raim>( ABSRM_RAIM_FIELD_ID );
            }
        }
        public int AisBaseStationReportMessageRadioStatus
        {
            get
            {
                return GetInt32( ABSRM_RADIOSTATUS_FIELD_ID );
            }
        }
        public int AisBinaryAcknowledgeMessageSpare
        {
            get
            {
                return GetInt32( ABAC_SPARE_FIELD_ID );
            }
        }
        public int AisBinaryAcknowledgeMessageSequenceNumber1
        {
            get
            {
                return GetInt32( ABAC_SEQUENCENUMBER1_FIELD_ID );
            }
        }
        public Guid? AisBinaryAcknowledgeMessageMmsi1
        {
            get
            {
                return GetNullableGuid( ABAC_MMSI1_FIELD_ID );
            }
        }
        public int? AisBinaryAcknowledgeMessageSequenceNumber2
        {
            get
            {
                return GetNullableInt32( ABAC_SEQUENCENUMBER2_FIELD_ID );
            }
        }
        public Guid? AisBinaryAcknowledgeMessageMmsi2
        {
            get
            {
                return GetNullableGuid( ABAC_MMSI2_FIELD_ID );
            }
        }
        public int? AisBinaryAcknowledgeMessageSequenceNumber3
        {
            get
            {
                return GetNullableInt32( ABAC_SEQUENCENUMBER3_FIELD_ID );
            }
        }
        public Guid? AisBinaryAcknowledgeMessageMmsi3
        {
            get
            {
                return GetNullableGuid( ABAC_MMSI3_FIELD_ID );
            }
        }
        public int? AisBinaryAcknowledgeMessageSequenceNumber4
        {
            get
            {
                return GetNullableInt32( ABAC_SEQUENCENUMBER4_FIELD_ID );
            }
        }
        public Guid? AisBinaryAcknowledgeMessageMmsi4
        {
            get
            {
                return GetNullableGuid( ABAC_MMSI4_FIELD_ID );
            }
        }
        public int AisBinaryAddressedMessageSequenceNumber
        {
            get
            {
                return GetInt32( ABAM_SEQUENCENUMBER_FIELD_ID );
            }
        }
        public Guid? AisBinaryAddressedMessageDestinationMmsi
        {
            get
            {
                return GetNullableGuid( ABAM_DESTINATIONMMSI_FIELD_ID );
            }
        }
        public bool AisBinaryAddressedMessageRetransmitFlag
        {
            get
            {
                return GetBoolean( ABAM_RETRANSMITFLAG_FIELD_ID );
            }
        }
        public int AisBinaryAddressedMessageSpare
        {
            get
            {
                return GetInt32( ABAM_SPARE_FIELD_ID );
            }
        }
        public int AisBinaryAddressedMessageDesignatedAreaCode
        {
            get
            {
                return GetInt32( ABAM_DESIGNATEDAREACODE_FIELD_ID );
            }
        }
        public int AisBinaryAddressedMessageFunctionalId
        {
            get
            {
                return GetInt32( ABAM_FUNCTIONALID_FIELD_ID );
            }
        }
        public string AisBinaryAddressedMessageData
        {
            get
            {
                return GetString( ABAM_DATA_FIELD_ID );
            }
        }
        public int AisBinaryBroadcastMessageSpare
        {
            get
            {
                return GetInt32( ABBM_SPARE_FIELD_ID );
            }
        }
        public int AisBinaryBroadcastMessageDesignatedAreaCode
        {
            get
            {
                return GetInt32( ABBM_DESIGNATEDAREACODE_FIELD_ID );
            }
        }
        public int AisBinaryBroadcastMessageFunctionalId
        {
            get
            {
                return GetInt32( ABBM_FUNCTIONALID_FIELD_ID );
            }
        }
        public string AisBinaryBroadcastMessageData
        {
            get
            {
                return GetString( ABBM_DATA_FIELD_ID );
            }
        }
        public int AisDataLinkManagementMessageSpare
        {
            get
            {
                return GetInt32( ADLMM_SPARE_FIELD_ID );
            }
        }
        public int AisDataLinkManagementMessageOffset1
        {
            get
            {
                return GetInt32( ADLMM_OFFSET1_FIELD_ID );
            }
        }
        public int AisDataLinkManagementMessageReservedSlots1
        {
            get
            {
                return GetInt32( ADLMM_RESERVEDSLOTS1_FIELD_ID );
            }
        }
        public int AisDataLinkManagementMessageTimeout1
        {
            get
            {
                return GetInt32( ADLMM_TIMEOUT1_FIELD_ID );
            }
        }
        public int AisDataLinkManagementMessageIncrement1
        {
            get
            {
                return GetInt32( ADLMM_INCREMENT1_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageOffset2
        {
            get
            {
                return GetNullableInt32( ADLMM_OFFSET2_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageReservedSlots2
        {
            get
            {
                return GetNullableInt32( ADLMM_RESERVEDSLOTS2_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageTimeout2
        {
            get
            {
                return GetNullableInt32( ADLMM_TIMEOUT2_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageIncrement2
        {
            get
            {
                return GetNullableInt32( ADLMM_INCREMENT2_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageOffset3
        {
            get
            {
                return GetNullableInt32( ADLMM_OFFSET3_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageReservedSlots3
        {
            get
            {
                return GetNullableInt32( ADLMM_RESERVEDSLOTS3_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageTimeout3
        {
            get
            {
                return GetNullableInt32( ADLMM_TIMEOUT3_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageIncrement3
        {
            get
            {
                return GetNullableInt32( ADLMM_INCREMENT3_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageOffset4
        {
            get
            {
                return GetNullableInt32( ADLMM_OFFSET4_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageReservedSlots4
        {
            get
            {
                return GetNullableInt32( ADLMM_RESERVEDSLOTS4_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageTimeout4
        {
            get
            {
                return GetNullableInt32( ADLMM_TIMEOUT4_FIELD_ID );
            }
        }
        public int? AisDataLinkManagementMessageIncrement4
        {
            get
            {
                return GetNullableInt32( ADLMM_INCREMENT4_FIELD_ID );
            }
        }
        public int AisExtendedClassBCsPositionReportMessageReserved
        {
            get
            {
                return GetInt32( AECBPRM_RESERVED_FIELD_ID );
            }
        }
        public double AisExtendedClassBCsPositionReportMessageSpeedOverGround
        {
            get
            {
                return GetDouble( AECBPRM_SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public Types.PositionAccuracy AisExtendedClassBCsPositionReportMessagePositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( AECBPRM_POSITIONACCURACY_FIELD_ID );
            }
        }
        public double AisExtendedClassBCsPositionReportMessageLongitude
        {
            get
            {
                return GetDouble( AECBPRM_LONGITUDE_FIELD_ID );
            }
        }
        public double AisExtendedClassBCsPositionReportMessageLatitude
        {
            get
            {
                return GetDouble( AECBPRM_LATITUDE_FIELD_ID );
            }
        }
        public double AisExtendedClassBCsPositionReportMessageCourseOverGround
        {
            get
            {
                return GetDouble( AECBPRM_COURSEOVERGROUND_FIELD_ID );
            }
        }
        public int? AisExtendedClassBCsPositionReportMessageTrueHeading
        {
            get
            {
                return GetNullableInt32( AECBPRM_TRUEHEADING_FIELD_ID );
            }
        }
        public int AisExtendedClassBCsPositionReportMessageTimestamp
        {
            get
            {
                return GetInt32( AECBPRM_TIMESTAMP_FIELD_ID );
            }
        }
        public int AisExtendedClassBCsPositionReportMessageRegionalReserved
        {
            get
            {
                return GetInt32( AECBPRM_REGIONALRESERVED_FIELD_ID );
            }
        }
        public Guid? AisExtendedClassBCsPositionReportMessageName
        {
            get
            {
                return GetNullableGuid( AECBPRM_NAME_FIELD_ID );
            }
        }
        public Types.ShipType AisExtendedClassBCsPositionReportMessageShipType
        {
            get
            {
                return GetEnum<Types.ShipType>( AECBPRM_SHIPTYPE_FIELD_ID );
            }
        }
        public int AisExtendedClassBCsPositionReportMessageDimensionToBow
        {
            get
            {
                return GetInt32( AECBPRM_DIMENSIONTOBOW_FIELD_ID );
            }
        }
        public int AisExtendedClassBCsPositionReportMessageDimensionToStern
        {
            get
            {
                return GetInt32( AECBPRM_DIMENSIONTOSTERN_FIELD_ID );
            }
        }
        public int AisExtendedClassBCsPositionReportMessageDimensionToPort
        {
            get
            {
                return GetInt32( AECBPRM_DIMENSIONTOPORT_FIELD_ID );
            }
        }
        public int AisExtendedClassBCsPositionReportMessageDimensionToStarboard
        {
            get
            {
                return GetInt32( AECBPRM_DIMENSIONTOSTARBOARD_FIELD_ID );
            }
        }
        public Types.PositionFixType AisExtendedClassBCsPositionReportMessagePositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( AECBPRM_POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public Types.Raim AisExtendedClassBCsPositionReportMessageRaim
        {
            get
            {
                return GetEnum<Types.Raim>( AECBPRM_RAIM_FIELD_ID );
            }
        }
        public bool AisExtendedClassBCsPositionReportMessageDataTerminalReady
        {
            get
            {
                return GetBoolean( AECBPRM_DATATERMINALREADY_FIELD_ID );
            }
        }
        public bool AisExtendedClassBCsPositionReportMessageAssigned
        {
            get
            {
                return GetBoolean( AECBPRM_ASSIGNED_FIELD_ID );
            }
        }
        public int AisExtendedClassBCsPositionReportMessageSpare
        {
            get
            {
                return GetInt32( AECBPRM_SPARE_FIELD_ID );
            }
        }
        public Guid? AisInterrogationMessageInterrogatedMmsi
        {
            get
            {
                return GetNullableGuid( AIM_INTERROGATEDMMSI_FIELD_ID );
            }
        }
        public Types.AisMessageType AisInterrogationMessageFirstMessageType
        {
            get
            {
                return GetEnum<Types.AisMessageType>( AIM_FIRSTMESSAGETYPE_FIELD_ID );
            }
        }
        public int AisInterrogationMessageFirstSlotOffset
        {
            get
            {
                return GetInt32( AIM_FIRSTSLOTOFFSET_FIELD_ID );
            }
        }
        public Types.AisMessageType? AisInterrogationMessageSecondMessageType
        {
            get
            {
                return GetNullableEnum<Types.AisMessageType>( AIM_SECONDMESSAGETYPE_FIELD_ID );
            }
        }
        public int? AisInterrogationMessageSecondSlotOffset
        {
            get
            {
                return GetNullableInt32( AIM_SECONDSLOTOFFSET_FIELD_ID );
            }
        }
        public Guid? AisInterrogationMessageSecondStationInterrogationMmsi
        {
            get
            {
                return GetNullableGuid( AIM_SECONDSTATIONINTERROGATIONMMSI_FIELD_ID );
            }
        }
        public Types.AisMessageType? AisInterrogationMessageSecondStationFirstMessageType
        {
            get
            {
                return GetNullableEnum<Types.AisMessageType>( AIM_SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID );
            }
        }
        public int? AisInterrogationMessageSecondStationFirstSlotOffset
        {
            get
            {
                return GetNullableInt32( AIM_SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID );
            }
        }
        public Types.NavigationStatus AisPositionReportClassAMessageBaseNavigationStatus
        {
            get
            {
                return GetEnum<Types.NavigationStatus>( APRCAB_NAVIGATIONSTATUS_FIELD_ID );
            }
        }
        public int? AisPositionReportClassAMessageBaseRateOfTurn
        {
            get
            {
                return GetNullableInt32( APRCAB_RATEOFTURN_FIELD_ID );
            }
        }
        public double AisPositionReportClassAMessageBaseSpeedOverGround
        {
            get
            {
                return GetDouble( APRCAB_SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public Types.PositionAccuracy AisPositionReportClassAMessageBasePositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( APRCAB_POSITIONACCURACY_FIELD_ID );
            }
        }
        public double AisPositionReportClassAMessageBaseLongitude
        {
            get
            {
                return GetDouble( APRCAB_LONGITUDE_FIELD_ID );
            }
        }
        public double AisPositionReportClassAMessageBaseLatitude
        {
            get
            {
                return GetDouble( APRCAB_LATITUDE_FIELD_ID );
            }
        }
        public double AisPositionReportClassAMessageBaseCourseOverGround
        {
            get
            {
                return GetDouble( APRCAB_COURSEOVERGROUND_FIELD_ID );
            }
        }
        public int? AisPositionReportClassAMessageBaseTrueHeading
        {
            get
            {
                return GetNullableInt32( APRCAB_TRUEHEADING_FIELD_ID );
            }
        }
        public int AisPositionReportClassAMessageBaseTimestamp
        {
            get
            {
                return GetInt32( APRCAB_TIMESTAMP_FIELD_ID );
            }
        }
        public Types.ManeuverIndicator AisPositionReportClassAMessageBaseManeuverIndicator
        {
            get
            {
                return GetEnum<Types.ManeuverIndicator>( APRCAB_MANEUVERINDICATOR_FIELD_ID );
            }
        }
        public int AisPositionReportClassAMessageBaseSpare
        {
            get
            {
                return GetInt32( APRCAB_SPARE_FIELD_ID );
            }
        }
        public Types.Raim AisPositionReportClassAMessageBaseRaim
        {
            get
            {
                return GetEnum<Types.Raim>( APRCAB_RAIM_FIELD_ID );
            }
        }
        public int AisPositionReportClassAMessageBaseRadioStatus
        {
            get
            {
                return GetInt32( APRCAB_RADIOSTATUS_FIELD_ID );
            }
        }
        public Types.PositionAccuracy AisPositionReportForLongRangeApplicationsMessagePositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( APRFLRAM_POSITIONACCURACY_FIELD_ID );
            }
        }
        public Types.Raim AisPositionReportForLongRangeApplicationsMessageRaim
        {
            get
            {
                return GetEnum<Types.Raim>( APRFLRAM_RAIM_FIELD_ID );
            }
        }
        public Types.NavigationStatus AisPositionReportForLongRangeApplicationsMessageNavigationStatus
        {
            get
            {
                return GetEnum<Types.NavigationStatus>( APRFLRAM_NAVIGATIONSTATUS_FIELD_ID );
            }
        }
        public double AisPositionReportForLongRangeApplicationsMessageLongitude
        {
            get
            {
                return GetDouble( APRFLRAM_LONGITUDE_FIELD_ID );
            }
        }
        public double AisPositionReportForLongRangeApplicationsMessageLatitude
        {
            get
            {
                return GetDouble( APRFLRAM_LATITUDE_FIELD_ID );
            }
        }
        public double AisPositionReportForLongRangeApplicationsMessageSpeedOverGround
        {
            get
            {
                return GetDouble( APRFLRAM_SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public double AisPositionReportForLongRangeApplicationsMessageCourseOverGround
        {
            get
            {
                return GetDouble( APRFLRAM_COURSEOVERGROUND_FIELD_ID );
            }
        }
        public Types.GnssPositionStatus AisPositionReportForLongRangeApplicationsMessageGnssPositionStatus
        {
            get
            {
                return GetEnum<Types.GnssPositionStatus>( APRFLRAM_GNSSPOSITIONSTATUS_FIELD_ID );
            }
        }
        public int AisPositionReportForLongRangeApplicationsMessageSpare
        {
            get
            {
                return GetInt32( APRFLRAM_SPARE_FIELD_ID );
            }
        }
        public int AisSafetyRelatedAcknowledgmentMessageSpare
        {
            get
            {
                return GetInt32( ASRAM_SPARE_FIELD_ID );
            }
        }
        public int AisSafetyRelatedAcknowledgmentMessageSequenceNumber1
        {
            get
            {
                return GetInt32( ASRAM_SEQUENCENUMBER1_FIELD_ID );
            }
        }
        public Guid? AisSafetyRelatedAcknowledgmentMessageMmsi1
        {
            get
            {
                return GetNullableGuid( ASRAM_MMSI1_FIELD_ID );
            }
        }
        public int? AisSafetyRelatedAcknowledgmentMessageSequenceNumber2
        {
            get
            {
                return GetNullableInt32( ASRAM_SEQUENCENUMBER2_FIELD_ID );
            }
        }
        public Guid? AisSafetyRelatedAcknowledgmentMessageMmsi2
        {
            get
            {
                return GetNullableGuid( ASRAM_MMSI2_FIELD_ID );
            }
        }
        public int? AisSafetyRelatedAcknowledgmentMessageSequenceNumber3
        {
            get
            {
                return GetNullableInt32( ASRAM_SEQUENCENUMBER3_FIELD_ID );
            }
        }
        public Guid? AisSafetyRelatedAcknowledgmentMessageMmsi3
        {
            get
            {
                return GetNullableGuid( ASRAM_MMSI3_FIELD_ID );
            }
        }
        public int? AisSafetyRelatedAcknowledgmentMessageSequenceNumber4
        {
            get
            {
                return GetNullableInt32( ASRAM_SEQUENCENUMBER4_FIELD_ID );
            }
        }
        public Guid? AisSafetyRelatedAcknowledgmentMessageMmsi4
        {
            get
            {
                return GetNullableGuid( ASRAM_MMSI4_FIELD_ID );
            }
        }
        public int AisStandardClassBCsPositionReportMessageReserved
        {
            get
            {
                return GetInt32( ASCBPRM_RESERVED_FIELD_ID );
            }
        }
        public double AisStandardClassBCsPositionReportMessageSpeedOverGround
        {
            get
            {
                return GetDouble( ASCBPRM_SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public Types.PositionAccuracy AisStandardClassBCsPositionReportMessagePositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( ASCBPRM_POSITIONACCURACY_FIELD_ID );
            }
        }
        public double AisStandardClassBCsPositionReportMessageLongitude
        {
            get
            {
                return GetDouble( ASCBPRM_LONGITUDE_FIELD_ID );
            }
        }
        public double AisStandardClassBCsPositionReportMessageLatitude
        {
            get
            {
                return GetDouble( ASCBPRM_LATITUDE_FIELD_ID );
            }
        }
        public double AisStandardClassBCsPositionReportMessageCourseOverGround
        {
            get
            {
                return GetDouble( ASCBPRM_COURSEOVERGROUND_FIELD_ID );
            }
        }
        public int? AisStandardClassBCsPositionReportMessageTrueHeading
        {
            get
            {
                return GetNullableInt32( ASCBPRM_TRUEHEADING_FIELD_ID );
            }
        }
        public int AisStandardClassBCsPositionReportMessageTimestamp
        {
            get
            {
                return GetInt32( ASCBPRM_TIMESTAMP_FIELD_ID );
            }
        }
        public int AisStandardClassBCsPositionReportMessageRegionalReserved
        {
            get
            {
                return GetInt32( ASCBPRM_REGIONALRESERVED_FIELD_ID );
            }
        }
        public bool AisStandardClassBCsPositionReportMessageIsCsUnit
        {
            get
            {
                return GetBoolean( ASCBPRM_ISCSUNIT_FIELD_ID );
            }
        }
        public bool AisStandardClassBCsPositionReportMessageHasDisplay
        {
            get
            {
                return GetBoolean( ASCBPRM_HASDISPLAY_FIELD_ID );
            }
        }
        public bool AisStandardClassBCsPositionReportMessageHasDscCapability
        {
            get
            {
                return GetBoolean( ASCBPRM_HASDSCCAPABILITY_FIELD_ID );
            }
        }
        public bool AisStandardClassBCsPositionReportMessageBand
        {
            get
            {
                return GetBoolean( ASCBPRM_BAND_FIELD_ID );
            }
        }
        public bool AisStandardClassBCsPositionReportMessageCanAcceptMessage22
        {
            get
            {
                return GetBoolean( ASCBPRM_CANACCEPTMESSAGE22_FIELD_ID );
            }
        }
        public bool AisStandardClassBCsPositionReportMessageAssigned
        {
            get
            {
                return GetBoolean( ASCBPRM_ASSIGNED_FIELD_ID );
            }
        }
        public Types.Raim AisStandardClassBCsPositionReportMessageRaim
        {
            get
            {
                return GetEnum<Types.Raim>( ASCBPRM_RAIM_FIELD_ID );
            }
        }
        public int AisStandardClassBCsPositionReportMessageRadioStatus
        {
            get
            {
                return GetInt32( ASCBPRM_RADIOSTATUS_FIELD_ID );
            }
        }
        public int AisStandardSarAircraftPositionReportMessageAltitude
        {
            get
            {
                return GetInt32( ASSAPRM_ALTITUDE_FIELD_ID );
            }
        }
        public int AisStandardSarAircraftPositionReportMessageSpeedOverGround
        {
            get
            {
                return GetInt32( ASSAPRM_SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public Types.PositionAccuracy AisStandardSarAircraftPositionReportMessagePositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( ASSAPRM_POSITIONACCURACY_FIELD_ID );
            }
        }
        public double AisStandardSarAircraftPositionReportMessageLongitude
        {
            get
            {
                return GetDouble( ASSAPRM_LONGITUDE_FIELD_ID );
            }
        }
        public double AisStandardSarAircraftPositionReportMessageLatitude
        {
            get
            {
                return GetDouble( ASSAPRM_LATITUDE_FIELD_ID );
            }
        }
        public double AisStandardSarAircraftPositionReportMessageCourseOverGround
        {
            get
            {
                return GetDouble( ASSAPRM_COURSEOVERGROUND_FIELD_ID );
            }
        }
        public int AisStandardSarAircraftPositionReportMessageTimestamp
        {
            get
            {
                return GetInt32( ASSAPRM_TIMESTAMP_FIELD_ID );
            }
        }
        public int AisStandardSarAircraftPositionReportMessageReserved
        {
            get
            {
                return GetInt32( ASSAPRM_RESERVED_FIELD_ID );
            }
        }
        public bool AisStandardSarAircraftPositionReportMessageDataTerminalReady
        {
            get
            {
                return GetBoolean( ASSAPRM_DATATERMINALREADY_FIELD_ID );
            }
        }
        public int AisStandardSarAircraftPositionReportMessageSpare
        {
            get
            {
                return GetInt32( ASSAPRM_SPARE_FIELD_ID );
            }
        }
        public bool AisStandardSarAircraftPositionReportMessageAssigned
        {
            get
            {
                return GetBoolean( ASSAPRM_ASSIGNED_FIELD_ID );
            }
        }
        public Types.Raim AisStandardSarAircraftPositionReportMessageRaim
        {
            get
            {
                return GetEnum<Types.Raim>( ASSAPRM_RAIM_FIELD_ID );
            }
        }
        public int AisStandardSarAircraftPositionReportMessageRadioStatus
        {
            get
            {
                return GetInt32( ASSAPRM_RADIOSTATUS_FIELD_ID );
            }
        }
        public int AisStaticAndVoyageRelatedDataMessageAisVersion
        {
            get
            {
                return GetInt32( ASAVRDM_AISVERSION_FIELD_ID );
            }
        }
        public Guid? AisStaticAndVoyageRelatedDataMessageImoNumber
        {
            get
            {
                return GetNullableGuid( ASAVRDM_IMONUMBER_FIELD_ID );
            }
        }
        public Guid? AisStaticAndVoyageRelatedDataMessageCallsign
        {
            get
            {
                return GetNullableGuid( ASAVRDM_CALLSIGN_FIELD_ID );
            }
        }
        public Guid? AisStaticAndVoyageRelatedDataMessageShipName
        {
            get
            {
                return GetNullableGuid( ASAVRDM_SHIPNAME_FIELD_ID );
            }
        }
        public Types.ShipType AisStaticAndVoyageRelatedDataMessageShipType
        {
            get
            {
                return GetEnum<Types.ShipType>( ASAVRDM_SHIPTYPE_FIELD_ID );
            }
        }
        public int AisStaticAndVoyageRelatedDataMessageDimensionToBow
        {
            get
            {
                return GetInt32( ASAVRDM_DIMENSIONTOBOW_FIELD_ID );
            }
        }
        public int AisStaticAndVoyageRelatedDataMessageDimensionToStern
        {
            get
            {
                return GetInt32( ASAVRDM_DIMENSIONTOSTERN_FIELD_ID );
            }
        }
        public int AisStaticAndVoyageRelatedDataMessageDimensionToPort
        {
            get
            {
                return GetInt32( ASAVRDM_DIMENSIONTOPORT_FIELD_ID );
            }
        }
        public int AisStaticAndVoyageRelatedDataMessageDimensionToStarboard
        {
            get
            {
                return GetInt32( ASAVRDM_DIMENSIONTOSTARBOARD_FIELD_ID );
            }
        }
        public Types.PositionFixType AisStaticAndVoyageRelatedDataMessagePositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( ASAVRDM_POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public DateTime? AisStaticAndVoyageRelatedDataMessageEstimatedTimeOfArrival
        {
            get
            {
                var v = GetNullableInt64( ASAVRDM_ESTIMATEDTIMEOFARRIVAL_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
        public double AisStaticAndVoyageRelatedDataMessageDraught
        {
            get
            {
                return GetDouble( ASAVRDM_DRAUGHT_FIELD_ID );
            }
        }
        public string AisStaticAndVoyageRelatedDataMessageDestination
        {
            get
            {
                return GetString( ASAVRDM_DESTINATION_FIELD_ID );
            }
        }
        public bool AisStaticAndVoyageRelatedDataMessageDataTerminalReady
        {
            get
            {
                return GetBoolean( ASAVRDM_DATATERMINALREADY_FIELD_ID );
            }
        }
        public int AisStaticAndVoyageRelatedDataMessageSpare
        {
            get
            {
                return GetInt32( ASAVRDM_SPARE_FIELD_ID );
            }
        }
        public int AisStaticDataReportMessagePartNumber
        {
            get
            {
                return GetInt32( ASDRM_PARTNUMBER_FIELD_ID );
            }
        }
        public Guid? AisStaticDataReportPartAMessageShipName
        {
            get
            {
                return GetNullableGuid( ASDRPA_SHIPNAME_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartAMessageSpare
        {
            get
            {
                return GetInt32( ASDRPA_SPARE_FIELD_ID );
            }
        }
        public Types.ShipType AisStaticDataReportPartBMessageShipType
        {
            get
            {
                return GetEnum<Types.ShipType>( ASDRPB_SHIPTYPE_FIELD_ID );
            }
        }
        public string AisStaticDataReportPartBMessageVendorId
        {
            get
            {
                return GetString( ASDRPB_VENDORID_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageUnitModelCode
        {
            get
            {
                return GetInt32( ASDRPB_UNITMODELCODE_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageSerialNumber
        {
            get
            {
                return GetInt32( ASDRPB_SERIALNUMBER_FIELD_ID );
            }
        }
        public Guid? AisStaticDataReportPartBMessageCallsign
        {
            get
            {
                return GetNullableGuid( ASDRPB_CALLSIGN_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageDimensionToBow
        {
            get
            {
                return GetInt32( ASDRPB_DIMENSIONTOBOW_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageDimensionToStern
        {
            get
            {
                return GetInt32( ASDRPB_DIMENSIONTOSTERN_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageDimensionToPort
        {
            get
            {
                return GetInt32( ASDRPB_DIMENSIONTOPORT_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageDimensionToStarboard
        {
            get
            {
                return GetInt32( ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID );
            }
        }
        public Guid? AisStaticDataReportPartBMessageMothershipMmsi
        {
            get
            {
                return GetNullableGuid( ASDRPB_MOTHERSHIPMMSI_FIELD_ID );
            }
        }
        public Types.PositionFixType AisStaticDataReportPartBMessagePositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( ASDRPB_POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageSpare
        {
            get
            {
                return GetInt32( ASDRPB_SPARE_FIELD_ID );
            }
        }
        public int AisUtcAndDateInquiryMessageSpare1
        {
            get
            {
                return GetInt32( AUADIM_SPARE1_FIELD_ID );
            }
        }
        public Guid? AisUtcAndDateInquiryMessageDestinationMmsi
        {
            get
            {
                return GetNullableGuid( AUADIM_DESTINATIONMMSI_FIELD_ID );
            }
        }
        public int AisUtcAndDateInquiryMessageSpare2
        {
            get
            {
                return GetInt32( AUADIM_SPARE2_FIELD_ID );
            }
        }
        public DateTime AisUtcAndDateResponseMessageDatetime
        {
            get
            {
                return new DateTime( GetInt64( AUADRM_DATETIME_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.PositionAccuracy AisUtcAndDateResponseMessagePositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( AUADRM_POSITIONACCURACY_FIELD_ID );
            }
        }
        public double AisUtcAndDateResponseMessageLongitude
        {
            get
            {
                return GetDouble( AUADRM_LONGITUDE_FIELD_ID );
            }
        }
        public double AisUtcAndDateResponseMessageLatitude
        {
            get
            {
                return GetDouble( AUADRM_LATITUDE_FIELD_ID );
            }
        }
        public Types.PositionFixType AisUtcAndDateResponseMessagePositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( AUADRM_POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public int AisUtcAndDateResponseMessageSpare
        {
            get
            {
                return GetInt32( AUADRM_SPARE_FIELD_ID );
            }
        }
        public Types.Raim AisUtcAndDateResponseMessageRaim
        {
            get
            {
                return GetEnum<Types.Raim>( AUADRM_RAIM_FIELD_ID );
            }
        }
        public int AisUtcAndDateResponseMessageRadioStatus
        {
            get
            {
                return GetInt32( AUADRM_RADIOSTATUS_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.AidToNavigationReportMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AidToNavigationReportMessageNavigationalAidType );
                    destination.Write( AidToNavigationReportMessageName );
                    destination.Write( AidToNavigationReportMessagePositionAccuracy );
                    destination.Write( AidToNavigationReportMessageLongitude );
                    destination.Write( AidToNavigationReportMessageLatitude );
                    destination.Write( AidToNavigationReportMessageDimensionToBow );
                    destination.Write( AidToNavigationReportMessageDimensionToStern );
                    destination.Write( AidToNavigationReportMessageDimensionToPort );
                    destination.Write( AidToNavigationReportMessageDimensionToStarboard );
                    destination.Write( AidToNavigationReportMessagePositionFixType );
                    destination.Write( AidToNavigationReportMessageTimestamp );
                    destination.Write( AidToNavigationReportMessageOffPosition );
                    destination.Write( AidToNavigationReportMessageRegionalReserved );
                    destination.Write( AidToNavigationReportMessageRaim );
                    destination.Write( AidToNavigationReportMessageVirtualAid );
                    destination.Write( AidToNavigationReportMessageAssigned );
                    destination.Write( AidToNavigationReportMessageSpare );
                    destination.Write( AidToNavigationReportMessageNameExtension );
                }
                break;
                case Types.Kind.AisAddressedSafetyRelatedMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisAddressedSafetyRelatedMessageSequenceNumber );
                    destination.Write( AisAddressedSafetyRelatedMessageDestinationMmsi );
                    destination.Write( AisAddressedSafetyRelatedMessageRetransmitFlag );
                    destination.Write( AisAddressedSafetyRelatedMessageSpare );
                    destination.Write( AisAddressedSafetyRelatedMessageText );
                }
                break;
                case Types.Kind.AisBaseStationReportMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisBaseStationReportMessageTimestamp );
                    destination.Write( AisBaseStationReportMessagePositionAccuracy );
                    destination.Write( AisBaseStationReportMessageLongitude );
                    destination.Write( AisBaseStationReportMessageLatitude );
                    destination.Write( AisBaseStationReportMessagePositionFixType );
                    destination.Write( AisBaseStationReportMessageSpare );
                    destination.Write( AisBaseStationReportMessageRaim );
                    destination.Write( AisBaseStationReportMessageRadioStatus );
                }
                break;
                case Types.Kind.AisBinaryAcknowledgeMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisBinaryAcknowledgeMessageSpare );
                    destination.Write( AisBinaryAcknowledgeMessageSequenceNumber1 );
                    destination.Write( AisBinaryAcknowledgeMessageMmsi1 );
                    destination.Write( AisBinaryAcknowledgeMessageSequenceNumber2 );
                    destination.Write( AisBinaryAcknowledgeMessageMmsi2 );
                    destination.Write( AisBinaryAcknowledgeMessageSequenceNumber3 );
                    destination.Write( AisBinaryAcknowledgeMessageMmsi3 );
                    destination.Write( AisBinaryAcknowledgeMessageSequenceNumber4 );
                    destination.Write( AisBinaryAcknowledgeMessageMmsi4 );
                }
                break;
                case Types.Kind.AisBinaryAddressedMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisBinaryAddressedMessageSequenceNumber );
                    destination.Write( AisBinaryAddressedMessageDestinationMmsi );
                    destination.Write( AisBinaryAddressedMessageRetransmitFlag );
                    destination.Write( AisBinaryAddressedMessageSpare );
                    destination.Write( AisBinaryAddressedMessageDesignatedAreaCode );
                    destination.Write( AisBinaryAddressedMessageFunctionalId );
                    destination.Write( AisBinaryAddressedMessageData );
                }
                break;
                case Types.Kind.AisBinaryBroadcastMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisBinaryBroadcastMessageSpare );
                    destination.Write( AisBinaryBroadcastMessageDesignatedAreaCode );
                    destination.Write( AisBinaryBroadcastMessageFunctionalId );
                    destination.Write( AisBinaryBroadcastMessageData );
                }
                break;
                case Types.Kind.AisDataLinkManagementMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisDataLinkManagementMessageSpare );
                    destination.Write( AisDataLinkManagementMessageOffset1 );
                    destination.Write( AisDataLinkManagementMessageReservedSlots1 );
                    destination.Write( AisDataLinkManagementMessageTimeout1 );
                    destination.Write( AisDataLinkManagementMessageIncrement1 );
                    destination.Write( AisDataLinkManagementMessageOffset2 );
                    destination.Write( AisDataLinkManagementMessageReservedSlots2 );
                    destination.Write( AisDataLinkManagementMessageTimeout2 );
                    destination.Write( AisDataLinkManagementMessageIncrement2 );
                    destination.Write( AisDataLinkManagementMessageOffset3 );
                    destination.Write( AisDataLinkManagementMessageReservedSlots3 );
                    destination.Write( AisDataLinkManagementMessageTimeout3 );
                    destination.Write( AisDataLinkManagementMessageIncrement3 );
                    destination.Write( AisDataLinkManagementMessageOffset4 );
                    destination.Write( AisDataLinkManagementMessageReservedSlots4 );
                    destination.Write( AisDataLinkManagementMessageTimeout4 );
                    destination.Write( AisDataLinkManagementMessageIncrement4 );
                }
                break;
                case Types.Kind.AisExtendedClassBCsPositionReportMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisExtendedClassBCsPositionReportMessageReserved );
                    destination.Write( AisExtendedClassBCsPositionReportMessageSpeedOverGround );
                    destination.Write( AisExtendedClassBCsPositionReportMessagePositionAccuracy );
                    destination.Write( AisExtendedClassBCsPositionReportMessageLongitude );
                    destination.Write( AisExtendedClassBCsPositionReportMessageLatitude );
                    destination.Write( AisExtendedClassBCsPositionReportMessageCourseOverGround );
                    destination.Write( AisExtendedClassBCsPositionReportMessageTrueHeading );
                    destination.Write( AisExtendedClassBCsPositionReportMessageTimestamp );
                    destination.Write( AisExtendedClassBCsPositionReportMessageRegionalReserved );
                    destination.Write( AisExtendedClassBCsPositionReportMessageName );
                    destination.Write( AisExtendedClassBCsPositionReportMessageShipType );
                    destination.Write( AisExtendedClassBCsPositionReportMessageDimensionToBow );
                    destination.Write( AisExtendedClassBCsPositionReportMessageDimensionToStern );
                    destination.Write( AisExtendedClassBCsPositionReportMessageDimensionToPort );
                    destination.Write( AisExtendedClassBCsPositionReportMessageDimensionToStarboard );
                    destination.Write( AisExtendedClassBCsPositionReportMessagePositionFixType );
                    destination.Write( AisExtendedClassBCsPositionReportMessageRaim );
                    destination.Write( AisExtendedClassBCsPositionReportMessageDataTerminalReady );
                    destination.Write( AisExtendedClassBCsPositionReportMessageAssigned );
                    destination.Write( AisExtendedClassBCsPositionReportMessageSpare );
                }
                break;
                case Types.Kind.AisInterrogationMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisInterrogationMessageInterrogatedMmsi );
                    destination.Write( AisInterrogationMessageFirstMessageType );
                    destination.Write( AisInterrogationMessageFirstSlotOffset );
                    destination.Write( AisInterrogationMessageSecondMessageType );
                    destination.Write( AisInterrogationMessageSecondSlotOffset );
                    destination.Write( AisInterrogationMessageSecondStationInterrogationMmsi );
                    destination.Write( AisInterrogationMessageSecondStationFirstMessageType );
                    destination.Write( AisInterrogationMessageSecondStationFirstSlotOffset );
                }
                break;
                case Types.Kind.AisPositionReportClassAAssignedScheduleMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisPositionReportClassAMessageBaseNavigationStatus );
                    destination.Write( AisPositionReportClassAMessageBaseRateOfTurn );
                    destination.Write( AisPositionReportClassAMessageBaseSpeedOverGround );
                    destination.Write( AisPositionReportClassAMessageBasePositionAccuracy );
                    destination.Write( AisPositionReportClassAMessageBaseLongitude );
                    destination.Write( AisPositionReportClassAMessageBaseLatitude );
                    destination.Write( AisPositionReportClassAMessageBaseCourseOverGround );
                    destination.Write( AisPositionReportClassAMessageBaseTrueHeading );
                    destination.Write( AisPositionReportClassAMessageBaseTimestamp );
                    destination.Write( AisPositionReportClassAMessageBaseManeuverIndicator );
                    destination.Write( AisPositionReportClassAMessageBaseSpare );
                    destination.Write( AisPositionReportClassAMessageBaseRaim );
                    destination.Write( AisPositionReportClassAMessageBaseRadioStatus );
                }
                break;
                case Types.Kind.AisPositionReportClassAMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisPositionReportClassAMessageBaseNavigationStatus );
                    destination.Write( AisPositionReportClassAMessageBaseRateOfTurn );
                    destination.Write( AisPositionReportClassAMessageBaseSpeedOverGround );
                    destination.Write( AisPositionReportClassAMessageBasePositionAccuracy );
                    destination.Write( AisPositionReportClassAMessageBaseLongitude );
                    destination.Write( AisPositionReportClassAMessageBaseLatitude );
                    destination.Write( AisPositionReportClassAMessageBaseCourseOverGround );
                    destination.Write( AisPositionReportClassAMessageBaseTrueHeading );
                    destination.Write( AisPositionReportClassAMessageBaseTimestamp );
                    destination.Write( AisPositionReportClassAMessageBaseManeuverIndicator );
                    destination.Write( AisPositionReportClassAMessageBaseSpare );
                    destination.Write( AisPositionReportClassAMessageBaseRaim );
                    destination.Write( AisPositionReportClassAMessageBaseRadioStatus );
                }
                break;
                case Types.Kind.AisPositionReportClassAResponseToInterrogationMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisPositionReportClassAMessageBaseNavigationStatus );
                    destination.Write( AisPositionReportClassAMessageBaseRateOfTurn );
                    destination.Write( AisPositionReportClassAMessageBaseSpeedOverGround );
                    destination.Write( AisPositionReportClassAMessageBasePositionAccuracy );
                    destination.Write( AisPositionReportClassAMessageBaseLongitude );
                    destination.Write( AisPositionReportClassAMessageBaseLatitude );
                    destination.Write( AisPositionReportClassAMessageBaseCourseOverGround );
                    destination.Write( AisPositionReportClassAMessageBaseTrueHeading );
                    destination.Write( AisPositionReportClassAMessageBaseTimestamp );
                    destination.Write( AisPositionReportClassAMessageBaseManeuverIndicator );
                    destination.Write( AisPositionReportClassAMessageBaseSpare );
                    destination.Write( AisPositionReportClassAMessageBaseRaim );
                    destination.Write( AisPositionReportClassAMessageBaseRadioStatus );
                }
                break;
                case Types.Kind.AisPositionReportForLongRangeApplicationsMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisPositionReportForLongRangeApplicationsMessagePositionAccuracy );
                    destination.Write( AisPositionReportForLongRangeApplicationsMessageRaim );
                    destination.Write( AisPositionReportForLongRangeApplicationsMessageNavigationStatus );
                    destination.Write( AisPositionReportForLongRangeApplicationsMessageLongitude );
                    destination.Write( AisPositionReportForLongRangeApplicationsMessageLatitude );
                    destination.Write( AisPositionReportForLongRangeApplicationsMessageSpeedOverGround );
                    destination.Write( AisPositionReportForLongRangeApplicationsMessageCourseOverGround );
                    destination.Write( AisPositionReportForLongRangeApplicationsMessageGnssPositionStatus );
                    destination.Write( AisPositionReportForLongRangeApplicationsMessageSpare );
                }
                break;
                case Types.Kind.AisSafetyRelatedAcknowledgmentMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisSafetyRelatedAcknowledgmentMessageSpare );
                    destination.Write( AisSafetyRelatedAcknowledgmentMessageSequenceNumber1 );
                    destination.Write( AisSafetyRelatedAcknowledgmentMessageMmsi1 );
                    destination.Write( AisSafetyRelatedAcknowledgmentMessageSequenceNumber2 );
                    destination.Write( AisSafetyRelatedAcknowledgmentMessageMmsi2 );
                    destination.Write( AisSafetyRelatedAcknowledgmentMessageSequenceNumber3 );
                    destination.Write( AisSafetyRelatedAcknowledgmentMessageMmsi3 );
                    destination.Write( AisSafetyRelatedAcknowledgmentMessageSequenceNumber4 );
                    destination.Write( AisSafetyRelatedAcknowledgmentMessageMmsi4 );
                }
                break;
                case Types.Kind.AisStandardClassBCsPositionReportMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisStandardClassBCsPositionReportMessageReserved );
                    destination.Write( AisStandardClassBCsPositionReportMessageSpeedOverGround );
                    destination.Write( AisStandardClassBCsPositionReportMessagePositionAccuracy );
                    destination.Write( AisStandardClassBCsPositionReportMessageLongitude );
                    destination.Write( AisStandardClassBCsPositionReportMessageLatitude );
                    destination.Write( AisStandardClassBCsPositionReportMessageCourseOverGround );
                    destination.Write( AisStandardClassBCsPositionReportMessageTrueHeading );
                    destination.Write( AisStandardClassBCsPositionReportMessageTimestamp );
                    destination.Write( AisStandardClassBCsPositionReportMessageRegionalReserved );
                    destination.Write( AisStandardClassBCsPositionReportMessageIsCsUnit );
                    destination.Write( AisStandardClassBCsPositionReportMessageHasDisplay );
                    destination.Write( AisStandardClassBCsPositionReportMessageHasDscCapability );
                    destination.Write( AisStandardClassBCsPositionReportMessageBand );
                    destination.Write( AisStandardClassBCsPositionReportMessageCanAcceptMessage22 );
                    destination.Write( AisStandardClassBCsPositionReportMessageAssigned );
                    destination.Write( AisStandardClassBCsPositionReportMessageRaim );
                    destination.Write( AisStandardClassBCsPositionReportMessageRadioStatus );
                }
                break;
                case Types.Kind.AisStandardSarAircraftPositionReportMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisStandardSarAircraftPositionReportMessageAltitude );
                    destination.Write( AisStandardSarAircraftPositionReportMessageSpeedOverGround );
                    destination.Write( AisStandardSarAircraftPositionReportMessagePositionAccuracy );
                    destination.Write( AisStandardSarAircraftPositionReportMessageLongitude );
                    destination.Write( AisStandardSarAircraftPositionReportMessageLatitude );
                    destination.Write( AisStandardSarAircraftPositionReportMessageCourseOverGround );
                    destination.Write( AisStandardSarAircraftPositionReportMessageTimestamp );
                    destination.Write( AisStandardSarAircraftPositionReportMessageReserved );
                    destination.Write( AisStandardSarAircraftPositionReportMessageDataTerminalReady );
                    destination.Write( AisStandardSarAircraftPositionReportMessageSpare );
                    destination.Write( AisStandardSarAircraftPositionReportMessageAssigned );
                    destination.Write( AisStandardSarAircraftPositionReportMessageRaim );
                    destination.Write( AisStandardSarAircraftPositionReportMessageRadioStatus );
                }
                break;
                case Types.Kind.AisStaticAndVoyageRelatedDataMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageAisVersion );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageImoNumber );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageCallsign );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageShipName );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageShipType );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageDimensionToBow );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageDimensionToStern );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageDimensionToPort );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageDimensionToStarboard );
                    destination.Write( AisStaticAndVoyageRelatedDataMessagePositionFixType );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageEstimatedTimeOfArrival );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageDraught );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageDestination );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageDataTerminalReady );
                    destination.Write( AisStaticAndVoyageRelatedDataMessageSpare );
                }
                break;
                case Types.Kind.AisStaticDataReportMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisStaticDataReportMessagePartNumber );
                }
                break;
                case Types.Kind.AisStaticDataReportPartAMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisStaticDataReportMessagePartNumber );
                    destination.Write( AisStaticDataReportPartAMessageShipName );
                    destination.Write( AisStaticDataReportPartAMessageSpare );
                }
                break;
                case Types.Kind.AisStaticDataReportPartBMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisStaticDataReportMessagePartNumber );
                    destination.Write( AisStaticDataReportPartBMessageShipType );
                    destination.Write( AisStaticDataReportPartBMessageVendorId );
                    destination.Write( AisStaticDataReportPartBMessageUnitModelCode );
                    destination.Write( AisStaticDataReportPartBMessageSerialNumber );
                    destination.Write( AisStaticDataReportPartBMessageCallsign );
                    destination.Write( AisStaticDataReportPartBMessageDimensionToBow );
                    destination.Write( AisStaticDataReportPartBMessageDimensionToStern );
                    destination.Write( AisStaticDataReportPartBMessageDimensionToPort );
                    destination.Write( AisStaticDataReportPartBMessageDimensionToStarboard );
                    destination.Write( AisStaticDataReportPartBMessageMothershipMmsi );
                    destination.Write( AisStaticDataReportPartBMessagePositionFixType );
                    destination.Write( AisStaticDataReportPartBMessageSpare );
                }
                break;
                case Types.Kind.AisUtcAndDateInquiryMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisUtcAndDateInquiryMessageSpare1 );
                    destination.Write( AisUtcAndDateInquiryMessageDestinationMmsi );
                    destination.Write( AisUtcAndDateInquiryMessageSpare2 );
                }
                break;
                case Types.Kind.AisUtcAndDateResponseMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( AisUtcAndDateResponseMessageDatetime );
                    destination.Write( AisUtcAndDateResponseMessagePositionAccuracy );
                    destination.Write( AisUtcAndDateResponseMessageLongitude );
                    destination.Write( AisUtcAndDateResponseMessageLatitude );
                    destination.Write( AisUtcAndDateResponseMessagePositionFixType );
                    destination.Write( AisUtcAndDateResponseMessageSpare );
                    destination.Write( AisUtcAndDateResponseMessageRaim );
                    destination.Write( AisUtcAndDateResponseMessageRadioStatus );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public AisMessageObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.AidToNavigationReportMessage:
                {
                    return new AidToNavigationReportMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AidToNavigationReportMessageNavigationalAidType, AidToNavigationReportMessageName, AidToNavigationReportMessagePositionAccuracy, AidToNavigationReportMessageLongitude, AidToNavigationReportMessageLatitude, AidToNavigationReportMessageDimensionToBow, AidToNavigationReportMessageDimensionToStern, AidToNavigationReportMessageDimensionToPort, AidToNavigationReportMessageDimensionToStarboard, AidToNavigationReportMessagePositionFixType, AidToNavigationReportMessageTimestamp, AidToNavigationReportMessageOffPosition, AidToNavigationReportMessageRegionalReserved, AidToNavigationReportMessageRaim, AidToNavigationReportMessageVirtualAid, AidToNavigationReportMessageAssigned, AidToNavigationReportMessageSpare, AidToNavigationReportMessageNameExtension );
                }
                case Types.Kind.AisAddressedSafetyRelatedMessage:
                {
                    return new AisAddressedSafetyRelatedMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisAddressedSafetyRelatedMessageSequenceNumber, AisAddressedSafetyRelatedMessageDestinationMmsi, AisAddressedSafetyRelatedMessageRetransmitFlag, AisAddressedSafetyRelatedMessageSpare, AisAddressedSafetyRelatedMessageText );
                }
                case Types.Kind.AisBaseStationReportMessage:
                {
                    return new AisBaseStationReportMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisBaseStationReportMessageTimestamp, AisBaseStationReportMessagePositionAccuracy, AisBaseStationReportMessageLongitude, AisBaseStationReportMessageLatitude, AisBaseStationReportMessagePositionFixType, AisBaseStationReportMessageSpare, AisBaseStationReportMessageRaim, AisBaseStationReportMessageRadioStatus );
                }
                case Types.Kind.AisBinaryAcknowledgeMessage:
                {
                    return new AisBinaryAcknowledgeMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisBinaryAcknowledgeMessageSpare, AisBinaryAcknowledgeMessageSequenceNumber1, AisBinaryAcknowledgeMessageMmsi1, AisBinaryAcknowledgeMessageSequenceNumber2, AisBinaryAcknowledgeMessageMmsi2, AisBinaryAcknowledgeMessageSequenceNumber3, AisBinaryAcknowledgeMessageMmsi3, AisBinaryAcknowledgeMessageSequenceNumber4, AisBinaryAcknowledgeMessageMmsi4 );
                }
                case Types.Kind.AisBinaryAddressedMessage:
                {
                    return new AisBinaryAddressedMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisBinaryAddressedMessageSequenceNumber, AisBinaryAddressedMessageDestinationMmsi, AisBinaryAddressedMessageRetransmitFlag, AisBinaryAddressedMessageSpare, AisBinaryAddressedMessageDesignatedAreaCode, AisBinaryAddressedMessageFunctionalId, AisBinaryAddressedMessageData );
                }
                case Types.Kind.AisBinaryBroadcastMessage:
                {
                    return new AisBinaryBroadcastMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisBinaryBroadcastMessageSpare, AisBinaryBroadcastMessageDesignatedAreaCode, AisBinaryBroadcastMessageFunctionalId, AisBinaryBroadcastMessageData );
                }
                case Types.Kind.AisDataLinkManagementMessage:
                {
                    return new AisDataLinkManagementMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisDataLinkManagementMessageSpare, AisDataLinkManagementMessageOffset1, AisDataLinkManagementMessageReservedSlots1, AisDataLinkManagementMessageTimeout1, AisDataLinkManagementMessageIncrement1, AisDataLinkManagementMessageOffset2, AisDataLinkManagementMessageReservedSlots2, AisDataLinkManagementMessageTimeout2, AisDataLinkManagementMessageIncrement2, AisDataLinkManagementMessageOffset3, AisDataLinkManagementMessageReservedSlots3, AisDataLinkManagementMessageTimeout3, AisDataLinkManagementMessageIncrement3, AisDataLinkManagementMessageOffset4, AisDataLinkManagementMessageReservedSlots4, AisDataLinkManagementMessageTimeout4, AisDataLinkManagementMessageIncrement4 );
                }
                case Types.Kind.AisExtendedClassBCsPositionReportMessage:
                {
                    return new AisExtendedClassBCsPositionReportMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisExtendedClassBCsPositionReportMessageReserved, AisExtendedClassBCsPositionReportMessageSpeedOverGround, AisExtendedClassBCsPositionReportMessagePositionAccuracy, AisExtendedClassBCsPositionReportMessageLongitude, AisExtendedClassBCsPositionReportMessageLatitude, AisExtendedClassBCsPositionReportMessageCourseOverGround, AisExtendedClassBCsPositionReportMessageTrueHeading, AisExtendedClassBCsPositionReportMessageTimestamp, AisExtendedClassBCsPositionReportMessageRegionalReserved, AisExtendedClassBCsPositionReportMessageName, AisExtendedClassBCsPositionReportMessageShipType, AisExtendedClassBCsPositionReportMessageDimensionToBow, AisExtendedClassBCsPositionReportMessageDimensionToStern, AisExtendedClassBCsPositionReportMessageDimensionToPort, AisExtendedClassBCsPositionReportMessageDimensionToStarboard, AisExtendedClassBCsPositionReportMessagePositionFixType, AisExtendedClassBCsPositionReportMessageRaim, AisExtendedClassBCsPositionReportMessageDataTerminalReady, AisExtendedClassBCsPositionReportMessageAssigned, AisExtendedClassBCsPositionReportMessageSpare );
                }
                case Types.Kind.AisInterrogationMessage:
                {
                    return new AisInterrogationMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisInterrogationMessageInterrogatedMmsi, AisInterrogationMessageFirstMessageType, AisInterrogationMessageFirstSlotOffset, AisInterrogationMessageSecondMessageType, AisInterrogationMessageSecondSlotOffset, AisInterrogationMessageSecondStationInterrogationMmsi, AisInterrogationMessageSecondStationFirstMessageType, AisInterrogationMessageSecondStationFirstSlotOffset );
                }
                case Types.Kind.AisPositionReportClassAAssignedScheduleMessage:
                {
                    return new AisPositionReportClassAAssignedScheduleMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisPositionReportClassAMessageBaseNavigationStatus, AisPositionReportClassAMessageBaseRateOfTurn, AisPositionReportClassAMessageBaseSpeedOverGround, AisPositionReportClassAMessageBasePositionAccuracy, AisPositionReportClassAMessageBaseLongitude, AisPositionReportClassAMessageBaseLatitude, AisPositionReportClassAMessageBaseCourseOverGround, AisPositionReportClassAMessageBaseTrueHeading, AisPositionReportClassAMessageBaseTimestamp, AisPositionReportClassAMessageBaseManeuverIndicator, AisPositionReportClassAMessageBaseSpare, AisPositionReportClassAMessageBaseRaim, AisPositionReportClassAMessageBaseRadioStatus );
                }
                case Types.Kind.AisPositionReportClassAMessage:
                {
                    return new AisPositionReportClassAMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisPositionReportClassAMessageBaseNavigationStatus, AisPositionReportClassAMessageBaseRateOfTurn, AisPositionReportClassAMessageBaseSpeedOverGround, AisPositionReportClassAMessageBasePositionAccuracy, AisPositionReportClassAMessageBaseLongitude, AisPositionReportClassAMessageBaseLatitude, AisPositionReportClassAMessageBaseCourseOverGround, AisPositionReportClassAMessageBaseTrueHeading, AisPositionReportClassAMessageBaseTimestamp, AisPositionReportClassAMessageBaseManeuverIndicator, AisPositionReportClassAMessageBaseSpare, AisPositionReportClassAMessageBaseRaim, AisPositionReportClassAMessageBaseRadioStatus );
                }
                case Types.Kind.AisPositionReportClassAResponseToInterrogationMessage:
                {
                    return new AisPositionReportClassAResponseToInterrogationMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisPositionReportClassAMessageBaseNavigationStatus, AisPositionReportClassAMessageBaseRateOfTurn, AisPositionReportClassAMessageBaseSpeedOverGround, AisPositionReportClassAMessageBasePositionAccuracy, AisPositionReportClassAMessageBaseLongitude, AisPositionReportClassAMessageBaseLatitude, AisPositionReportClassAMessageBaseCourseOverGround, AisPositionReportClassAMessageBaseTrueHeading, AisPositionReportClassAMessageBaseTimestamp, AisPositionReportClassAMessageBaseManeuverIndicator, AisPositionReportClassAMessageBaseSpare, AisPositionReportClassAMessageBaseRaim, AisPositionReportClassAMessageBaseRadioStatus );
                }
                case Types.Kind.AisPositionReportForLongRangeApplicationsMessage:
                {
                    return new AisPositionReportForLongRangeApplicationsMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisPositionReportForLongRangeApplicationsMessagePositionAccuracy, AisPositionReportForLongRangeApplicationsMessageRaim, AisPositionReportForLongRangeApplicationsMessageNavigationStatus, AisPositionReportForLongRangeApplicationsMessageLongitude, AisPositionReportForLongRangeApplicationsMessageLatitude, AisPositionReportForLongRangeApplicationsMessageSpeedOverGround, AisPositionReportForLongRangeApplicationsMessageCourseOverGround, AisPositionReportForLongRangeApplicationsMessageGnssPositionStatus, AisPositionReportForLongRangeApplicationsMessageSpare );
                }
                case Types.Kind.AisSafetyRelatedAcknowledgmentMessage:
                {
                    return new AisSafetyRelatedAcknowledgmentMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisSafetyRelatedAcknowledgmentMessageSpare, AisSafetyRelatedAcknowledgmentMessageSequenceNumber1, AisSafetyRelatedAcknowledgmentMessageMmsi1, AisSafetyRelatedAcknowledgmentMessageSequenceNumber2, AisSafetyRelatedAcknowledgmentMessageMmsi2, AisSafetyRelatedAcknowledgmentMessageSequenceNumber3, AisSafetyRelatedAcknowledgmentMessageMmsi3, AisSafetyRelatedAcknowledgmentMessageSequenceNumber4, AisSafetyRelatedAcknowledgmentMessageMmsi4 );
                }
                case Types.Kind.AisStandardClassBCsPositionReportMessage:
                {
                    return new AisStandardClassBCsPositionReportMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisStandardClassBCsPositionReportMessageReserved, AisStandardClassBCsPositionReportMessageSpeedOverGround, AisStandardClassBCsPositionReportMessagePositionAccuracy, AisStandardClassBCsPositionReportMessageLongitude, AisStandardClassBCsPositionReportMessageLatitude, AisStandardClassBCsPositionReportMessageCourseOverGround, AisStandardClassBCsPositionReportMessageTrueHeading, AisStandardClassBCsPositionReportMessageTimestamp, AisStandardClassBCsPositionReportMessageRegionalReserved, AisStandardClassBCsPositionReportMessageIsCsUnit, AisStandardClassBCsPositionReportMessageHasDisplay, AisStandardClassBCsPositionReportMessageHasDscCapability, AisStandardClassBCsPositionReportMessageBand, AisStandardClassBCsPositionReportMessageCanAcceptMessage22, AisStandardClassBCsPositionReportMessageAssigned, AisStandardClassBCsPositionReportMessageRaim, AisStandardClassBCsPositionReportMessageRadioStatus );
                }
                case Types.Kind.AisStandardSarAircraftPositionReportMessage:
                {
                    return new AisStandardSarAircraftPositionReportMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisStandardSarAircraftPositionReportMessageAltitude, AisStandardSarAircraftPositionReportMessageSpeedOverGround, AisStandardSarAircraftPositionReportMessagePositionAccuracy, AisStandardSarAircraftPositionReportMessageLongitude, AisStandardSarAircraftPositionReportMessageLatitude, AisStandardSarAircraftPositionReportMessageCourseOverGround, AisStandardSarAircraftPositionReportMessageTimestamp, AisStandardSarAircraftPositionReportMessageReserved, AisStandardSarAircraftPositionReportMessageDataTerminalReady, AisStandardSarAircraftPositionReportMessageSpare, AisStandardSarAircraftPositionReportMessageAssigned, AisStandardSarAircraftPositionReportMessageRaim, AisStandardSarAircraftPositionReportMessageRadioStatus );
                }
                case Types.Kind.AisStaticAndVoyageRelatedDataMessage:
                {
                    return new AisStaticAndVoyageRelatedDataMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisStaticAndVoyageRelatedDataMessageAisVersion, AisStaticAndVoyageRelatedDataMessageImoNumber, AisStaticAndVoyageRelatedDataMessageCallsign, AisStaticAndVoyageRelatedDataMessageShipName, AisStaticAndVoyageRelatedDataMessageShipType, AisStaticAndVoyageRelatedDataMessageDimensionToBow, AisStaticAndVoyageRelatedDataMessageDimensionToStern, AisStaticAndVoyageRelatedDataMessageDimensionToPort, AisStaticAndVoyageRelatedDataMessageDimensionToStarboard, AisStaticAndVoyageRelatedDataMessagePositionFixType, AisStaticAndVoyageRelatedDataMessageEstimatedTimeOfArrival, AisStaticAndVoyageRelatedDataMessageDraught, AisStaticAndVoyageRelatedDataMessageDestination, AisStaticAndVoyageRelatedDataMessageDataTerminalReady, AisStaticAndVoyageRelatedDataMessageSpare );
                }
                case Types.Kind.AisStaticDataReportMessage:
                {
                    return new AisStaticDataReportMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisStaticDataReportMessagePartNumber );
                }
                case Types.Kind.AisStaticDataReportPartAMessage:
                {
                    return new AisStaticDataReportPartAMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisStaticDataReportMessagePartNumber, AisStaticDataReportPartAMessageShipName, AisStaticDataReportPartAMessageSpare );
                }
                case Types.Kind.AisStaticDataReportPartBMessage:
                {
                    return new AisStaticDataReportPartBMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisStaticDataReportMessagePartNumber, AisStaticDataReportPartBMessageShipType, AisStaticDataReportPartBMessageVendorId, AisStaticDataReportPartBMessageUnitModelCode, AisStaticDataReportPartBMessageSerialNumber, AisStaticDataReportPartBMessageCallsign, AisStaticDataReportPartBMessageDimensionToBow, AisStaticDataReportPartBMessageDimensionToStern, AisStaticDataReportPartBMessageDimensionToPort, AisStaticDataReportPartBMessageDimensionToStarboard, AisStaticDataReportPartBMessageMothershipMmsi, AisStaticDataReportPartBMessagePositionFixType, AisStaticDataReportPartBMessageSpare );
                }
                case Types.Kind.AisUtcAndDateInquiryMessage:
                {
                    return new AisUtcAndDateInquiryMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisUtcAndDateInquiryMessageSpare1, AisUtcAndDateInquiryMessageDestinationMmsi, AisUtcAndDateInquiryMessageSpare2 );
                }
                case Types.Kind.AisUtcAndDateResponseMessage:
                {
                    return new AisUtcAndDateResponseMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, AisUtcAndDateResponseMessageDatetime, AisUtcAndDateResponseMessagePositionAccuracy, AisUtcAndDateResponseMessageLongitude, AisUtcAndDateResponseMessageLatitude, AisUtcAndDateResponseMessagePositionFixType, AisUtcAndDateResponseMessageSpare, AisUtcAndDateResponseMessageRaim, AisUtcAndDateResponseMessageRadioStatus );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexAisPositionReportClassAMessageBaseDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  aprcab.[Id], \r\n" +
            "  aprcab.[EntityType], \r\n" +
            "  aprcab.[RowVersion], \r\n" +
            "  aprcab.[AisDevice], \r\n" +
            "  aprcab.[ReceivedTimestamp], \r\n" +
            "  aprcab.[MessageSequenceNumber], \r\n" +
            "  aprcab.[Repeat], \r\n" +
            "  aprcab.[Mmsi], \r\n" +
            "  aprcab.[NavigationStatus], \r\n" +
            "  aprcab.[RateOfTurn], \r\n" +
            "  aprcab.[SpeedOverGround], \r\n" +
            "  aprcab.[PositionAccuracy], \r\n" +
            "  aprcab.[Longitude], \r\n" +
            "  aprcab.[Latitude], \r\n" +
            "  aprcab.[CourseOverGround], \r\n" +
            "  aprcab.[TrueHeading], \r\n" +
            "  aprcab.[Timestamp], \r\n" +
            "  aprcab.[ManeuverIndicator], \r\n" +
            "  aprcab.[Spare], \r\n" +
            "  aprcab.[Raim], \r\n" +
            "  aprcab.[RadioStatus] \r\n" +
            "FROM [AisPositionReportClassAMessageBaseView] aprcab \r\n" +
            "  LEFT JOIN [AisPositionReportClassAAssignedScheduleMessage] aprcasm ON(aprcab.[Id] = aprcasm.[Id] ) \r\n" +
            "  LEFT JOIN [AisPositionReportClassAMessage] aprca ON(aprcab.[Id] = aprca.[Id] ) \r\n" +
            "  LEFT JOIN [AisPositionReportClassAResponseToInterrogationMessage] aprcatim ON(aprcab.[Id] = aprcatim.[Id] ) \r\n";

        public const string BaseViewName = "AisPositionReportClassAMessageBaseView";
        public const string ViewAliasName = "aprcab";

        public const int APRCAB_ID_FIELD_ID = 0;
        public const int APRCAB_KIND_FIELD_ID = 1;
        public const int APRCAB_ROWVERSION_FIELD_ID = 2;
        public const int APRCAB_AISDEVICE_FIELD_ID = 3;
        public const int APRCAB_RECEIVEDTIMESTAMP_FIELD_ID = 4;
        public const int APRCAB_MESSAGESEQUENCENUMBER_FIELD_ID = 5;
        public const int APRCAB_REPEAT_FIELD_ID = 6;
        public const int APRCAB_MMSI_FIELD_ID = 7;
        public const int APRCAB_NAVIGATIONSTATUS_FIELD_ID = 8;
        public const int APRCAB_RATEOFTURN_FIELD_ID = 9;
        public const int APRCAB_SPEEDOVERGROUND_FIELD_ID = 10;
        public const int APRCAB_POSITIONACCURACY_FIELD_ID = 11;
        public const int APRCAB_LONGITUDE_FIELD_ID = 12;
        public const int APRCAB_LATITUDE_FIELD_ID = 13;
        public const int APRCAB_COURSEOVERGROUND_FIELD_ID = 14;
        public const int APRCAB_TRUEHEADING_FIELD_ID = 15;
        public const int APRCAB_TIMESTAMP_FIELD_ID = 16;
        public const int APRCAB_MANEUVERINDICATOR_FIELD_ID = 17;
        public const int APRCAB_SPARE_FIELD_ID = 18;
        public const int APRCAB_RAIM_FIELD_ID = 19;
        public const int APRCAB_RADIOSTATUS_FIELD_ID = 20;
        public ComplexAisPositionReportClassAMessageBaseDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( APRCAB_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( APRCAB_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( APRCAB_ROWVERSION_FIELD_ID );
            }
        }
        public Guid AisDevice
        {
            get
            {
                return GetGuid( APRCAB_AISDEVICE_FIELD_ID );
            }
        }
        public DateTime ReceivedTimestamp
        {
            get
            {
                return new DateTime( GetInt64( APRCAB_RECEIVEDTIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public long MessageSequenceNumber
        {
            get
            {
                return GetInt64( APRCAB_MESSAGESEQUENCENUMBER_FIELD_ID );
            }
        }
        public int Repeat
        {
            get
            {
                return GetInt32( APRCAB_REPEAT_FIELD_ID );
            }
        }
        public Guid? Mmsi
        {
            get
            {
                return GetNullableGuid( APRCAB_MMSI_FIELD_ID );
            }
        }
        public Types.NavigationStatus NavigationStatus
        {
            get
            {
                return GetEnum<Types.NavigationStatus>( APRCAB_NAVIGATIONSTATUS_FIELD_ID );
            }
        }
        public int? RateOfTurn
        {
            get
            {
                return GetNullableInt32( APRCAB_RATEOFTURN_FIELD_ID );
            }
        }
        public double SpeedOverGround
        {
            get
            {
                return GetDouble( APRCAB_SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( APRCAB_POSITIONACCURACY_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( APRCAB_LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( APRCAB_LATITUDE_FIELD_ID );
            }
        }
        public double CourseOverGround
        {
            get
            {
                return GetDouble( APRCAB_COURSEOVERGROUND_FIELD_ID );
            }
        }
        public int? TrueHeading
        {
            get
            {
                return GetNullableInt32( APRCAB_TRUEHEADING_FIELD_ID );
            }
        }
        public int Timestamp
        {
            get
            {
                return GetInt32( APRCAB_TIMESTAMP_FIELD_ID );
            }
        }
        public Types.ManeuverIndicator ManeuverIndicator
        {
            get
            {
                return GetEnum<Types.ManeuverIndicator>( APRCAB_MANEUVERINDICATOR_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( APRCAB_SPARE_FIELD_ID );
            }
        }
        public Types.Raim Raim
        {
            get
            {
                return GetEnum<Types.Raim>( APRCAB_RAIM_FIELD_ID );
            }
        }
        public int RadioStatus
        {
            get
            {
                return GetInt32( APRCAB_RADIOSTATUS_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.AisPositionReportClassAAssignedScheduleMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( NavigationStatus );
                    destination.Write( RateOfTurn );
                    destination.Write( SpeedOverGround );
                    destination.Write( PositionAccuracy );
                    destination.Write( Longitude );
                    destination.Write( Latitude );
                    destination.Write( CourseOverGround );
                    destination.Write( TrueHeading );
                    destination.Write( Timestamp );
                    destination.Write( ManeuverIndicator );
                    destination.Write( Spare );
                    destination.Write( Raim );
                    destination.Write( RadioStatus );
                }
                break;
                case Types.Kind.AisPositionReportClassAMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( NavigationStatus );
                    destination.Write( RateOfTurn );
                    destination.Write( SpeedOverGround );
                    destination.Write( PositionAccuracy );
                    destination.Write( Longitude );
                    destination.Write( Latitude );
                    destination.Write( CourseOverGround );
                    destination.Write( TrueHeading );
                    destination.Write( Timestamp );
                    destination.Write( ManeuverIndicator );
                    destination.Write( Spare );
                    destination.Write( Raim );
                    destination.Write( RadioStatus );
                }
                break;
                case Types.Kind.AisPositionReportClassAResponseToInterrogationMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( NavigationStatus );
                    destination.Write( RateOfTurn );
                    destination.Write( SpeedOverGround );
                    destination.Write( PositionAccuracy );
                    destination.Write( Longitude );
                    destination.Write( Latitude );
                    destination.Write( CourseOverGround );
                    destination.Write( TrueHeading );
                    destination.Write( Timestamp );
                    destination.Write( ManeuverIndicator );
                    destination.Write( Spare );
                    destination.Write( Raim );
                    destination.Write( RadioStatus );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public AisPositionReportClassAMessageBaseObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.AisPositionReportClassAAssignedScheduleMessage:
                {
                    return new AisPositionReportClassAAssignedScheduleMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, NavigationStatus, RateOfTurn, SpeedOverGround, PositionAccuracy, Longitude, Latitude, CourseOverGround, TrueHeading, Timestamp, ManeuverIndicator, Spare, Raim, RadioStatus );
                }
                case Types.Kind.AisPositionReportClassAMessage:
                {
                    return new AisPositionReportClassAMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, NavigationStatus, RateOfTurn, SpeedOverGround, PositionAccuracy, Longitude, Latitude, CourseOverGround, TrueHeading, Timestamp, ManeuverIndicator, Spare, Raim, RadioStatus );
                }
                case Types.Kind.AisPositionReportClassAResponseToInterrogationMessage:
                {
                    return new AisPositionReportClassAResponseToInterrogationMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, NavigationStatus, RateOfTurn, SpeedOverGround, PositionAccuracy, Longitude, Latitude, CourseOverGround, TrueHeading, Timestamp, ManeuverIndicator, Spare, Raim, RadioStatus );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexAisStaticDataReportMessageDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  asdrm.[Id], \r\n" +
            "  asdrm.[EntityType], \r\n" +
            "  asdrm.[RowVersion], \r\n" +
            "  asdrm.[AisDevice], \r\n" +
            "  asdrm.[ReceivedTimestamp], \r\n" +
            "  asdrm.[MessageSequenceNumber], \r\n" +
            "  asdrm.[Repeat], \r\n" +
            "  asdrm.[Mmsi], \r\n" +
            "  asdrm.[PartNumber], \r\n" +
            "  asdrpa.[ShipName], \r\n" +
            "  asdrpa.[Spare], \r\n" +
            "  asdrpb.[ShipType], \r\n" +
            "  asdrpb.[VendorId], \r\n" +
            "  asdrpb.[UnitModelCode], \r\n" +
            "  asdrpb.[SerialNumber], \r\n" +
            "  asdrpb.[Callsign], \r\n" +
            "  asdrpb.[DimensionToBow], \r\n" +
            "  asdrpb.[DimensionToStern], \r\n" +
            "  asdrpb.[DimensionToPort], \r\n" +
            "  asdrpb.[DimensionToStarboard], \r\n" +
            "  asdrpb.[MothershipMmsi], \r\n" +
            "  asdrpb.[PositionFixType], \r\n" +
            "  asdrpb.[Spare] \r\n" +
            "FROM [AisStaticDataReportMessageView] asdrm \r\n" +
            "  LEFT JOIN [AisStaticDataReportPartAMessage] asdrpa ON(asdrm.[Id] = asdrpa.[Id] ) \r\n" +
            "  LEFT JOIN [AisStaticDataReportPartBMessage] asdrpb ON(asdrm.[Id] = asdrpb.[Id] ) \r\n";

        public const string BaseViewName = "AisStaticDataReportMessageView";
        public const string ViewAliasName = "asdrm";

        public const int ASDRM_ID_FIELD_ID = 0;
        public const int ASDRM_KIND_FIELD_ID = 1;
        public const int ASDRM_ROWVERSION_FIELD_ID = 2;
        public const int ASDRM_AISDEVICE_FIELD_ID = 3;
        public const int ASDRM_RECEIVEDTIMESTAMP_FIELD_ID = 4;
        public const int ASDRM_MESSAGESEQUENCENUMBER_FIELD_ID = 5;
        public const int ASDRM_REPEAT_FIELD_ID = 6;
        public const int ASDRM_MMSI_FIELD_ID = 7;
        public const int ASDRM_PARTNUMBER_FIELD_ID = 8;
        public const int ASDRPA_SHIPNAME_FIELD_ID = 9;
        public const int ASDRPA_SPARE_FIELD_ID = 10;
        public const int ASDRPB_SHIPTYPE_FIELD_ID = 11;
        public const int ASDRPB_VENDORID_FIELD_ID = 12;
        public const int ASDRPB_UNITMODELCODE_FIELD_ID = 13;
        public const int ASDRPB_SERIALNUMBER_FIELD_ID = 14;
        public const int ASDRPB_CALLSIGN_FIELD_ID = 15;
        public const int ASDRPB_DIMENSIONTOBOW_FIELD_ID = 16;
        public const int ASDRPB_DIMENSIONTOSTERN_FIELD_ID = 17;
        public const int ASDRPB_DIMENSIONTOPORT_FIELD_ID = 18;
        public const int ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID = 19;
        public const int ASDRPB_MOTHERSHIPMMSI_FIELD_ID = 20;
        public const int ASDRPB_POSITIONFIXTYPE_FIELD_ID = 21;
        public const int ASDRPB_SPARE_FIELD_ID = 22;
        public ComplexAisStaticDataReportMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ASDRM_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( ASDRM_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ASDRM_ROWVERSION_FIELD_ID );
            }
        }
        public Guid AisDevice
        {
            get
            {
                return GetGuid( ASDRM_AISDEVICE_FIELD_ID );
            }
        }
        public DateTime ReceivedTimestamp
        {
            get
            {
                return new DateTime( GetInt64( ASDRM_RECEIVEDTIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public long MessageSequenceNumber
        {
            get
            {
                return GetInt64( ASDRM_MESSAGESEQUENCENUMBER_FIELD_ID );
            }
        }
        public int Repeat
        {
            get
            {
                return GetInt32( ASDRM_REPEAT_FIELD_ID );
            }
        }
        public Guid? Mmsi
        {
            get
            {
                return GetNullableGuid( ASDRM_MMSI_FIELD_ID );
            }
        }
        public int PartNumber
        {
            get
            {
                return GetInt32( ASDRM_PARTNUMBER_FIELD_ID );
            }
        }
        public Guid? AisStaticDataReportPartAMessageShipName
        {
            get
            {
                return GetNullableGuid( ASDRPA_SHIPNAME_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartAMessageSpare
        {
            get
            {
                return GetInt32( ASDRPA_SPARE_FIELD_ID );
            }
        }
        public Types.ShipType AisStaticDataReportPartBMessageShipType
        {
            get
            {
                return GetEnum<Types.ShipType>( ASDRPB_SHIPTYPE_FIELD_ID );
            }
        }
        public string AisStaticDataReportPartBMessageVendorId
        {
            get
            {
                return GetString( ASDRPB_VENDORID_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageUnitModelCode
        {
            get
            {
                return GetInt32( ASDRPB_UNITMODELCODE_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageSerialNumber
        {
            get
            {
                return GetInt32( ASDRPB_SERIALNUMBER_FIELD_ID );
            }
        }
        public Guid? AisStaticDataReportPartBMessageCallsign
        {
            get
            {
                return GetNullableGuid( ASDRPB_CALLSIGN_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageDimensionToBow
        {
            get
            {
                return GetInt32( ASDRPB_DIMENSIONTOBOW_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageDimensionToStern
        {
            get
            {
                return GetInt32( ASDRPB_DIMENSIONTOSTERN_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageDimensionToPort
        {
            get
            {
                return GetInt32( ASDRPB_DIMENSIONTOPORT_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageDimensionToStarboard
        {
            get
            {
                return GetInt32( ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID );
            }
        }
        public Guid? AisStaticDataReportPartBMessageMothershipMmsi
        {
            get
            {
                return GetNullableGuid( ASDRPB_MOTHERSHIPMMSI_FIELD_ID );
            }
        }
        public Types.PositionFixType AisStaticDataReportPartBMessagePositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( ASDRPB_POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public int AisStaticDataReportPartBMessageSpare
        {
            get
            {
                return GetInt32( ASDRPB_SPARE_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.AisStaticDataReportMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( PartNumber );
                }
                break;
                case Types.Kind.AisStaticDataReportPartAMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( PartNumber );
                    destination.Write( AisStaticDataReportPartAMessageShipName );
                    destination.Write( AisStaticDataReportPartAMessageSpare );
                }
                break;
                case Types.Kind.AisStaticDataReportPartBMessage:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisDevice );
                    destination.Write( ReceivedTimestamp );
                    destination.Write( MessageSequenceNumber );
                    destination.Write( Repeat );
                    destination.Write( Mmsi );
                    destination.Write( PartNumber );
                    destination.Write( AisStaticDataReportPartBMessageShipType );
                    destination.Write( AisStaticDataReportPartBMessageVendorId );
                    destination.Write( AisStaticDataReportPartBMessageUnitModelCode );
                    destination.Write( AisStaticDataReportPartBMessageSerialNumber );
                    destination.Write( AisStaticDataReportPartBMessageCallsign );
                    destination.Write( AisStaticDataReportPartBMessageDimensionToBow );
                    destination.Write( AisStaticDataReportPartBMessageDimensionToStern );
                    destination.Write( AisStaticDataReportPartBMessageDimensionToPort );
                    destination.Write( AisStaticDataReportPartBMessageDimensionToStarboard );
                    destination.Write( AisStaticDataReportPartBMessageMothershipMmsi );
                    destination.Write( AisStaticDataReportPartBMessagePositionFixType );
                    destination.Write( AisStaticDataReportPartBMessageSpare );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public AisStaticDataReportMessageObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.AisStaticDataReportMessage:
                {
                    return new AisStaticDataReportMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, PartNumber );
                }
                case Types.Kind.AisStaticDataReportPartAMessage:
                {
                    return new AisStaticDataReportPartAMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, PartNumber, AisStaticDataReportPartAMessageShipName, AisStaticDataReportPartAMessageSpare );
                }
                case Types.Kind.AisStaticDataReportPartBMessage:
                {
                    return new AisStaticDataReportPartBMessageObject( ObjectState.Stored, Id, RowVersion, AisDevice, ReceivedTimestamp, MessageSequenceNumber, Repeat, Mmsi, PartNumber, AisStaticDataReportPartBMessageShipType, AisStaticDataReportPartBMessageVendorId, AisStaticDataReportPartBMessageUnitModelCode, AisStaticDataReportPartBMessageSerialNumber, AisStaticDataReportPartBMessageCallsign, AisStaticDataReportPartBMessageDimensionToBow, AisStaticDataReportPartBMessageDimensionToStern, AisStaticDataReportPartBMessageDimensionToPort, AisStaticDataReportPartBMessageDimensionToStarboard, AisStaticDataReportPartBMessageMothershipMmsi, AisStaticDataReportPartBMessagePositionFixType, AisStaticDataReportPartBMessageSpare );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexCameraCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  cc.[Id], \r\n" +
            "  cc.[EntityType], \r\n" +
            "  cc.[RowVersion], \r\n" +
            "  cc.[Camera], \r\n" +
            "  cc.[Timestamp], \r\n" +
            "  cc.[DeviceCommandSourceType], \r\n" +
            "  cc.[DeviceCommandSourceId], \r\n" +
            "  cc.[Reply], \r\n" +
            "  ccam.[PositionPanTiltMode], \r\n" +
            "  ccam.[PanAngle], \r\n" +
            "  ccam.[TiltAngle], \r\n" +
            "  ccam.[PositionFocalLengthMode], \r\n" +
            "  ccam.[FocalLength], \r\n" +
            "  ccam.[SpeedPanTiltMode], \r\n" +
            "  ccam.[PanSpeed], \r\n" +
            "  ccam.[TiltSpeed], \r\n" +
            "  ccam.[SpeedFocalLengthMode], \r\n" +
            "  ccam.[ZoomSpeed], \r\n" +
            "  ccaptz.[X], \r\n" +
            "  ccaptz.[Y], \r\n" +
            "  ccaptz.[Z], \r\n" +
            "  cccm.[Normalized], \r\n" +
            "  cccm.[PanVelocity], \r\n" +
            "  cccm.[TiltVelocity], \r\n" +
            "  cccm.[ZoomVelocity], \r\n" +
            "  cccm.[Duration], \r\n" +
            "  ccgm.[Latitude], \r\n" +
            "  ccgm.[Longitude], \r\n" +
            "  ccgm.[Altitude], \r\n" +
            "  ccgm.[ViewportWidth], \r\n" +
            "  ccgm.[ViewportHeight], \r\n" +
            "  ccrm.[Normalized], \r\n" +
            "  ccrm.[PanAngle], \r\n" +
            "  ccrm.[TiltAngle], \r\n" +
            "  ccrm.[FocalLength], \r\n" +
            "  ccrm.[PanSpeed], \r\n" +
            "  ccrm.[TiltSpeed], \r\n" +
            "  ccrm.[ZoomSpeed], \r\n" +
            "  ccsaf.[Enabled], \r\n" +
            "  ccsbaw.[Enabled], \r\n" +
            "  ccsf.[TrackId], \r\n" +
            "  ccsf.[Reason], \r\n" +
            "  ccsirl.[Enabled], \r\n" +
            "  cwa.[Enabled], \r\n" +
            "  cwi.[Enabled], \r\n" +
            "  ccs.[PanTilt], \r\n" +
            "  ccs.[Zoom] \r\n" +
            "FROM [CameraCommandView] cc \r\n" +
            "  LEFT JOIN [CameraCommandAbsoluteMove] ccam ON(cc.[Id] = ccam.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandAdjustPanTiltZoom] ccaptz ON(cc.[Id] = ccaptz.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandContinuousMove] cccm ON(cc.[Id] = cccm.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandGeoMove] ccgm ON(cc.[Id] = ccgm.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandRelativeMove] ccrm ON(cc.[Id] = ccrm.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandReleasePTZOwnership] crlp ON(cc.[Id] = crlp.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandRequestPTZOwnership] crqp ON(cc.[Id] = crqp.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetAutoFocus] ccsaf ON(cc.[Id] = ccsaf.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetBlackAndWhite] ccsbaw ON(cc.[Id] = ccsbaw.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetFollowed] ccsf ON(cc.[Id] = ccsf.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetInfraRedLamp] ccsirl ON(cc.[Id] = ccsirl.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetWasher] cwa ON(cc.[Id] = cwa.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetWiper] cwi ON(cc.[Id] = cwi.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandStop] ccs ON(cc.[Id] = ccs.[Id] ) \r\n";

        public const string BaseViewName = "CameraCommandView";
        public const string ViewAliasName = "cc";

        public const int CC_ID_FIELD_ID = 0;
        public const int CC_KIND_FIELD_ID = 1;
        public const int CC_ROWVERSION_FIELD_ID = 2;
        public const int CC_CAMERA_FIELD_ID = 3;
        public const int CC_TIMESTAMP_FIELD_ID = 4;
        public const int CC_DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        public const int CC_DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        public const int CC_REPLY_FIELD_ID = 7;
        public const int CCAM_POSITIONPANTILTMODE_FIELD_ID = 8;
        public const int CCAM_PANANGLE_FIELD_ID = 9;
        public const int CCAM_TILTANGLE_FIELD_ID = 10;
        public const int CCAM_POSITIONFOCALLENGTHMODE_FIELD_ID = 11;
        public const int CCAM_FOCALLENGTH_FIELD_ID = 12;
        public const int CCAM_SPEEDPANTILTMODE_FIELD_ID = 13;
        public const int CCAM_PANSPEED_FIELD_ID = 14;
        public const int CCAM_TILTSPEED_FIELD_ID = 15;
        public const int CCAM_SPEEDFOCALLENGTHMODE_FIELD_ID = 16;
        public const int CCAM_ZOOMSPEED_FIELD_ID = 17;
        public const int CCAPTZ_X_FIELD_ID = 18;
        public const int CCAPTZ_Y_FIELD_ID = 19;
        public const int CCAPTZ_Z_FIELD_ID = 20;
        public const int CCCM_NORMALIZED_FIELD_ID = 21;
        public const int CCCM_PANVELOCITY_FIELD_ID = 22;
        public const int CCCM_TILTVELOCITY_FIELD_ID = 23;
        public const int CCCM_ZOOMVELOCITY_FIELD_ID = 24;
        public const int CCCM_DURATION_FIELD_ID = 25;
        public const int CCGM_LATITUDE_FIELD_ID = 26;
        public const int CCGM_LONGITUDE_FIELD_ID = 27;
        public const int CCGM_ALTITUDE_FIELD_ID = 28;
        public const int CCGM_VIEWPORTWIDTH_FIELD_ID = 29;
        public const int CCGM_VIEWPORTHEIGHT_FIELD_ID = 30;
        public const int CCRM_NORMALIZED_FIELD_ID = 31;
        public const int CCRM_PANANGLE_FIELD_ID = 32;
        public const int CCRM_TILTANGLE_FIELD_ID = 33;
        public const int CCRM_FOCALLENGTH_FIELD_ID = 34;
        public const int CCRM_PANSPEED_FIELD_ID = 35;
        public const int CCRM_TILTSPEED_FIELD_ID = 36;
        public const int CCRM_ZOOMSPEED_FIELD_ID = 37;
        public const int CCSAF_ENABLED_FIELD_ID = 38;
        public const int CCSBAW_ENABLED_FIELD_ID = 39;
        public const int CCSF_TRACKID_FIELD_ID = 40;
        public const int CCSF_REASON_FIELD_ID = 41;
        public const int CCSIRL_ENABLED_FIELD_ID = 42;
        public const int CWA_ENABLED_FIELD_ID = 43;
        public const int CWI_ENABLED_FIELD_ID = 44;
        public const int CCS_PANTILT_FIELD_ID = 45;
        public const int CCS_ZOOM_FIELD_ID = 46;
        public ComplexCameraCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( CC_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( CC_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( CC_ROWVERSION_FIELD_ID );
            }
        }
        public Guid Camera
        {
            get
            {
                return GetGuid( CC_CAMERA_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( CC_TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( CC_DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( CC_DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid? Reply
        {
            get
            {
                return GetNullableGuid( CC_REPLY_FIELD_ID );
            }
        }
        public Types.CameraPanTiltMode CameraCommandAbsoluteMovePositionPanTiltMode
        {
            get
            {
                return GetEnum<Types.CameraPanTiltMode>( CCAM_POSITIONPANTILTMODE_FIELD_ID );
            }
        }
        public double? CameraCommandAbsoluteMovePanAngle
        {
            get
            {
                return GetNullableDouble( CCAM_PANANGLE_FIELD_ID );
            }
        }
        public double? CameraCommandAbsoluteMoveTiltAngle
        {
            get
            {
                return GetNullableDouble( CCAM_TILTANGLE_FIELD_ID );
            }
        }
        public Types.CameraFocalLengthMode CameraCommandAbsoluteMovePositionFocalLengthMode
        {
            get
            {
                return GetEnum<Types.CameraFocalLengthMode>( CCAM_POSITIONFOCALLENGTHMODE_FIELD_ID );
            }
        }
        public double? CameraCommandAbsoluteMoveFocalLength
        {
            get
            {
                return GetNullableDouble( CCAM_FOCALLENGTH_FIELD_ID );
            }
        }
        public Types.CameraPanTiltMode CameraCommandAbsoluteMoveSpeedPanTiltMode
        {
            get
            {
                return GetEnum<Types.CameraPanTiltMode>( CCAM_SPEEDPANTILTMODE_FIELD_ID );
            }
        }
        public double? CameraCommandAbsoluteMovePanSpeed
        {
            get
            {
                return GetNullableDouble( CCAM_PANSPEED_FIELD_ID );
            }
        }
        public double? CameraCommandAbsoluteMoveTiltSpeed
        {
            get
            {
                return GetNullableDouble( CCAM_TILTSPEED_FIELD_ID );
            }
        }
        public Types.CameraFocalLengthMode CameraCommandAbsoluteMoveSpeedFocalLengthMode
        {
            get
            {
                return GetEnum<Types.CameraFocalLengthMode>( CCAM_SPEEDFOCALLENGTHMODE_FIELD_ID );
            }
        }
        public double? CameraCommandAbsoluteMoveZoomSpeed
        {
            get
            {
                return GetNullableDouble( CCAM_ZOOMSPEED_FIELD_ID );
            }
        }
        public double? CameraCommandAdjustPanTiltZoomX
        {
            get
            {
                return GetNullableDouble( CCAPTZ_X_FIELD_ID );
            }
        }
        public double? CameraCommandAdjustPanTiltZoomY
        {
            get
            {
                return GetNullableDouble( CCAPTZ_Y_FIELD_ID );
            }
        }
        public double? CameraCommandAdjustPanTiltZoomZ
        {
            get
            {
                return GetNullableDouble( CCAPTZ_Z_FIELD_ID );
            }
        }
        public bool CameraCommandContinuousMoveNormalized
        {
            get
            {
                return GetBoolean( CCCM_NORMALIZED_FIELD_ID );
            }
        }
        public double? CameraCommandContinuousMovePanVelocity
        {
            get
            {
                return GetNullableDouble( CCCM_PANVELOCITY_FIELD_ID );
            }
        }
        public double? CameraCommandContinuousMoveTiltVelocity
        {
            get
            {
                return GetNullableDouble( CCCM_TILTVELOCITY_FIELD_ID );
            }
        }
        public double? CameraCommandContinuousMoveZoomVelocity
        {
            get
            {
                return GetNullableDouble( CCCM_ZOOMVELOCITY_FIELD_ID );
            }
        }
        public TimeSpan? CameraCommandContinuousMoveDuration
        {
            get
            {
                var v = GetNullableInt64( CCCM_DURATION_FIELD_ID );
                if( v is long value )
                {
                    return new TimeSpan( value );
                }
                return null;
            }
        }
        public double CameraCommandGeoMoveLatitude
        {
            get
            {
                return GetDouble( CCGM_LATITUDE_FIELD_ID );
            }
        }
        public double CameraCommandGeoMoveLongitude
        {
            get
            {
                return GetDouble( CCGM_LONGITUDE_FIELD_ID );
            }
        }
        public double? CameraCommandGeoMoveAltitude
        {
            get
            {
                return GetNullableDouble( CCGM_ALTITUDE_FIELD_ID );
            }
        }
        public double? CameraCommandGeoMoveViewportWidth
        {
            get
            {
                return GetNullableDouble( CCGM_VIEWPORTWIDTH_FIELD_ID );
            }
        }
        public double? CameraCommandGeoMoveViewportHeight
        {
            get
            {
                return GetNullableDouble( CCGM_VIEWPORTHEIGHT_FIELD_ID );
            }
        }
        public bool CameraCommandRelativeMoveNormalized
        {
            get
            {
                return GetBoolean( CCRM_NORMALIZED_FIELD_ID );
            }
        }
        public double? CameraCommandRelativeMovePanAngle
        {
            get
            {
                return GetNullableDouble( CCRM_PANANGLE_FIELD_ID );
            }
        }
        public double? CameraCommandRelativeMoveTiltAngle
        {
            get
            {
                return GetNullableDouble( CCRM_TILTANGLE_FIELD_ID );
            }
        }
        public double? CameraCommandRelativeMoveFocalLength
        {
            get
            {
                return GetNullableDouble( CCRM_FOCALLENGTH_FIELD_ID );
            }
        }
        public double? CameraCommandRelativeMovePanSpeed
        {
            get
            {
                return GetNullableDouble( CCRM_PANSPEED_FIELD_ID );
            }
        }
        public double? CameraCommandRelativeMoveTiltSpeed
        {
            get
            {
                return GetNullableDouble( CCRM_TILTSPEED_FIELD_ID );
            }
        }
        public double? CameraCommandRelativeMoveZoomSpeed
        {
            get
            {
                return GetNullableDouble( CCRM_ZOOMSPEED_FIELD_ID );
            }
        }
        public bool CameraCommandSetAutoFocusEnabled
        {
            get
            {
                return GetBoolean( CCSAF_ENABLED_FIELD_ID );
            }
        }
        public bool CameraCommandSetBlackAndWhiteEnabled
        {
            get
            {
                return GetBoolean( CCSBAW_ENABLED_FIELD_ID );
            }
        }
        public Guid CameraCommandSetFollowedTrackId
        {
            get
            {
                return GetGuid( CCSF_TRACKID_FIELD_ID );
            }
        }
        public Types.CameraFollowReason CameraCommandSetFollowedReason
        {
            get
            {
                return GetEnum<Types.CameraFollowReason>( CCSF_REASON_FIELD_ID );
            }
        }
        public bool CameraCommandSetInfraRedLampEnabled
        {
            get
            {
                return GetBoolean( CCSIRL_ENABLED_FIELD_ID );
            }
        }
        public bool CameraCommandSetWasherEnabled
        {
            get
            {
                return GetBoolean( CWA_ENABLED_FIELD_ID );
            }
        }
        public bool CameraCommandSetWiperEnabled
        {
            get
            {
                return GetBoolean( CWI_ENABLED_FIELD_ID );
            }
        }
        public bool CameraCommandStopPanTilt
        {
            get
            {
                return GetBoolean( CCS_PANTILT_FIELD_ID );
            }
        }
        public bool CameraCommandStopZoom
        {
            get
            {
                return GetBoolean( CCS_ZOOM_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.CameraCommand:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                }
                break;
                case Types.Kind.CameraCommandAbsoluteMove:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandAbsoluteMovePositionPanTiltMode );
                    destination.Write( CameraCommandAbsoluteMovePanAngle );
                    destination.Write( CameraCommandAbsoluteMoveTiltAngle );
                    destination.Write( CameraCommandAbsoluteMovePositionFocalLengthMode );
                    destination.Write( CameraCommandAbsoluteMoveFocalLength );
                    destination.Write( CameraCommandAbsoluteMoveSpeedPanTiltMode );
                    destination.Write( CameraCommandAbsoluteMovePanSpeed );
                    destination.Write( CameraCommandAbsoluteMoveTiltSpeed );
                    destination.Write( CameraCommandAbsoluteMoveSpeedFocalLengthMode );
                    destination.Write( CameraCommandAbsoluteMoveZoomSpeed );
                }
                break;
                case Types.Kind.CameraCommandAdjustPanTiltZoom:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandAdjustPanTiltZoomX );
                    destination.Write( CameraCommandAdjustPanTiltZoomY );
                    destination.Write( CameraCommandAdjustPanTiltZoomZ );
                }
                break;
                case Types.Kind.CameraCommandContinuousMove:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandContinuousMoveNormalized );
                    destination.Write( CameraCommandContinuousMovePanVelocity );
                    destination.Write( CameraCommandContinuousMoveTiltVelocity );
                    destination.Write( CameraCommandContinuousMoveZoomVelocity );
                    destination.Write( CameraCommandContinuousMoveDuration );
                }
                break;
                case Types.Kind.CameraCommandGeoMove:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandGeoMoveLatitude );
                    destination.Write( CameraCommandGeoMoveLongitude );
                    destination.Write( CameraCommandGeoMoveAltitude );
                    destination.Write( CameraCommandGeoMoveViewportWidth );
                    destination.Write( CameraCommandGeoMoveViewportHeight );
                }
                break;
                case Types.Kind.CameraCommandRelativeMove:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandRelativeMoveNormalized );
                    destination.Write( CameraCommandRelativeMovePanAngle );
                    destination.Write( CameraCommandRelativeMoveTiltAngle );
                    destination.Write( CameraCommandRelativeMoveFocalLength );
                    destination.Write( CameraCommandRelativeMovePanSpeed );
                    destination.Write( CameraCommandRelativeMoveTiltSpeed );
                    destination.Write( CameraCommandRelativeMoveZoomSpeed );
                }
                break;
                case Types.Kind.CameraCommandReleasePTZOwnership:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                }
                break;
                case Types.Kind.CameraCommandRequestPTZOwnership:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                }
                break;
                case Types.Kind.CameraCommandSetAutoFocus:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandSetAutoFocusEnabled );
                }
                break;
                case Types.Kind.CameraCommandSetBlackAndWhite:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandSetBlackAndWhiteEnabled );
                }
                break;
                case Types.Kind.CameraCommandSetFollowed:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandSetFollowedTrackId );
                    destination.Write( CameraCommandSetFollowedReason );
                }
                break;
                case Types.Kind.CameraCommandSetInfraRedLamp:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandSetInfraRedLampEnabled );
                }
                break;
                case Types.Kind.CameraCommandSetWasher:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandSetWasherEnabled );
                }
                break;
                case Types.Kind.CameraCommandSetWiper:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandSetWiperEnabled );
                }
                break;
                case Types.Kind.CameraCommandStop:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Camera );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                    destination.Write( CameraCommandStopPanTilt );
                    destination.Write( CameraCommandStopZoom );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public CameraCommandObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.CameraCommand:
                {
                    return new CameraCommandObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply );
                }
                case Types.Kind.CameraCommandAbsoluteMove:
                {
                    return new CameraCommandAbsoluteMoveObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandAbsoluteMovePositionPanTiltMode, CameraCommandAbsoluteMovePanAngle, CameraCommandAbsoluteMoveTiltAngle, CameraCommandAbsoluteMovePositionFocalLengthMode, CameraCommandAbsoluteMoveFocalLength, CameraCommandAbsoluteMoveSpeedPanTiltMode, CameraCommandAbsoluteMovePanSpeed, CameraCommandAbsoluteMoveTiltSpeed, CameraCommandAbsoluteMoveSpeedFocalLengthMode, CameraCommandAbsoluteMoveZoomSpeed );
                }
                case Types.Kind.CameraCommandAdjustPanTiltZoom:
                {
                    return new CameraCommandAdjustPanTiltZoomObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandAdjustPanTiltZoomX, CameraCommandAdjustPanTiltZoomY, CameraCommandAdjustPanTiltZoomZ );
                }
                case Types.Kind.CameraCommandContinuousMove:
                {
                    return new CameraCommandContinuousMoveObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandContinuousMoveNormalized, CameraCommandContinuousMovePanVelocity, CameraCommandContinuousMoveTiltVelocity, CameraCommandContinuousMoveZoomVelocity, CameraCommandContinuousMoveDuration );
                }
                case Types.Kind.CameraCommandGeoMove:
                {
                    return new CameraCommandGeoMoveObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandGeoMoveLatitude, CameraCommandGeoMoveLongitude, CameraCommandGeoMoveAltitude, CameraCommandGeoMoveViewportWidth, CameraCommandGeoMoveViewportHeight );
                }
                case Types.Kind.CameraCommandRelativeMove:
                {
                    return new CameraCommandRelativeMoveObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandRelativeMoveNormalized, CameraCommandRelativeMovePanAngle, CameraCommandRelativeMoveTiltAngle, CameraCommandRelativeMoveFocalLength, CameraCommandRelativeMovePanSpeed, CameraCommandRelativeMoveTiltSpeed, CameraCommandRelativeMoveZoomSpeed );
                }
                case Types.Kind.CameraCommandReleasePTZOwnership:
                {
                    return new CameraCommandReleasePTZOwnershipObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply );
                }
                case Types.Kind.CameraCommandRequestPTZOwnership:
                {
                    return new CameraCommandRequestPTZOwnershipObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply );
                }
                case Types.Kind.CameraCommandSetAutoFocus:
                {
                    return new CameraCommandSetAutoFocusObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandSetAutoFocusEnabled );
                }
                case Types.Kind.CameraCommandSetBlackAndWhite:
                {
                    return new CameraCommandSetBlackAndWhiteObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandSetBlackAndWhiteEnabled );
                }
                case Types.Kind.CameraCommandSetFollowed:
                {
                    return new CameraCommandSetFollowedObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandSetFollowedTrackId, CameraCommandSetFollowedReason );
                }
                case Types.Kind.CameraCommandSetInfraRedLamp:
                {
                    return new CameraCommandSetInfraRedLampObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandSetInfraRedLampEnabled );
                }
                case Types.Kind.CameraCommandSetWasher:
                {
                    return new CameraCommandSetWasherObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandSetWasherEnabled );
                }
                case Types.Kind.CameraCommandSetWiper:
                {
                    return new CameraCommandSetWiperObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandSetWiperEnabled );
                }
                case Types.Kind.CameraCommandStop:
                {
                    return new CameraCommandStopObject( ObjectState.Stored, Id, RowVersion, Camera, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply, CameraCommandStopPanTilt, CameraCommandStopZoom );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexCatalogElementDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ce.[Id], \r\n" +
            "  ce.[EntityType], \r\n" +
            "  ce.[RowVersion], \r\n" +
            "  ce.[Catalog], \r\n" +
            "  ce.[Name], \r\n" +
            "  e.[ElementType] \r\n" +
            "FROM [CatalogElementView] ce \r\n" +
            "  LEFT JOIN [Catalog] c ON(ce.[Id] = c.[Id] ) \r\n" +
            "  LEFT JOIN [Element] e ON(ce.[Id] = e.[Id] ) \r\n";

        public const string BaseViewName = "CatalogElementView";
        public const string ViewAliasName = "ce";

        public const int CE_ID_FIELD_ID = 0;
        public const int CE_KIND_FIELD_ID = 1;
        public const int CE_ROWVERSION_FIELD_ID = 2;
        public const int CE_CATALOG_FIELD_ID = 3;
        public const int CE_NAME_FIELD_ID = 4;
        public const int E_ELEMENTTYPE_FIELD_ID = 5;
        public ComplexCatalogElementDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( CE_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( CE_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( CE_ROWVERSION_FIELD_ID );
            }
        }
        public Guid? Catalog
        {
            get
            {
                return GetNullableGuid( CE_CATALOG_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( CE_NAME_FIELD_ID );
            }
        }
        public Guid? ElementElementType
        {
            get
            {
                return GetNullableGuid( E_ELEMENTTYPE_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.Catalog:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                }
                break;
                case Types.Kind.Element:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( ElementElementType );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public CatalogElementObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.Catalog:
                {
                    return new CatalogObject( ObjectState.Stored, Id, RowVersion, Catalog, Name );
                }
                case Types.Kind.Element:
                {
                    return new ElementObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, ElementElementType );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexIdentityDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  i.[Id], \r\n" +
            "  i.[EntityType], \r\n" +
            "  i.[RowVersion], \r\n" +
            "  c.[Identifier], \r\n" +
            "  imon.[Identifier], \r\n" +
            "  mmsi.[Identifier], \r\n" +
            "  n.[Text] \r\n" +
            "FROM [IdentityView] i \r\n" +
            "  LEFT JOIN [Callsign] c ON(i.[Id] = c.[Id] ) \r\n" +
            "  LEFT JOIN [InternationalMaritimeOrganizationNumber] imon ON(i.[Id] = imon.[Id] ) \r\n" +
            "  LEFT JOIN [MaritimeMobileServiceIdentity] mmsi ON(i.[Id] = mmsi.[Id] ) \r\n" +
            "  LEFT JOIN [Name] n ON(i.[Id] = n.[Id] ) \r\n";

        public const string BaseViewName = "IdentityView";
        public const string ViewAliasName = "i";

        public const int I_ID_FIELD_ID = 0;
        public const int I_KIND_FIELD_ID = 1;
        public const int I_ROWVERSION_FIELD_ID = 2;
        public const int C_IDENTIFIER_FIELD_ID = 3;
        public const int IMON_IDENTIFIER_FIELD_ID = 4;
        public const int MMSI_IDENTIFIER_FIELD_ID = 5;
        public const int N_TEXT_FIELD_ID = 6;
        public ComplexIdentityDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( I_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( I_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( I_ROWVERSION_FIELD_ID );
            }
        }
        public string CallsignIdentifier
        {
            get
            {
                return GetString( C_IDENTIFIER_FIELD_ID );
            }
        }
        public long InternationalMaritimeOrganizationNumberIdentifier
        {
            get
            {
                return GetInt64( IMON_IDENTIFIER_FIELD_ID );
            }
        }
        public long MaritimeMobileServiceIdentityIdentifier
        {
            get
            {
                return GetInt64( MMSI_IDENTIFIER_FIELD_ID );
            }
        }
        public string NameText
        {
            get
            {
                return GetString( N_TEXT_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.Callsign:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( CallsignIdentifier );
                }
                break;
                case Types.Kind.InternationalMaritimeOrganizationNumber:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( InternationalMaritimeOrganizationNumberIdentifier );
                }
                break;
                case Types.Kind.MaritimeMobileServiceIdentity:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( MaritimeMobileServiceIdentityIdentifier );
                }
                break;
                case Types.Kind.Name:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( NameText );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public IdentityObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.Callsign:
                {
                    return new CallsignObject( ObjectState.Stored, Id, RowVersion, CallsignIdentifier );
                }
                case Types.Kind.InternationalMaritimeOrganizationNumber:
                {
                    return new InternationalMaritimeOrganizationNumberObject( ObjectState.Stored, Id, RowVersion, InternationalMaritimeOrganizationNumberIdentifier );
                }
                case Types.Kind.MaritimeMobileServiceIdentity:
                {
                    return new MaritimeMobileServiceIdentityObject( ObjectState.Stored, Id, RowVersion, MaritimeMobileServiceIdentityIdentifier );
                }
                case Types.Kind.Name:
                {
                    return new NameObject( ObjectState.Stored, Id, RowVersion, NameText );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexItemDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  i.[Id], \r\n" +
            "  i.[EntityType], \r\n" +
            "  i.[RowVersion], \r\n" +
            "  bs.[Name], \r\n" +
            "  bs.[Type], \r\n" +
            "  d.[Host], \r\n" +
            "  d.[Name], \r\n" +
            "  d.[EnabledTimeseries], \r\n" +
            "  g.[LatitudeTimeseries], \r\n" +
            "  g.[LongitudeTimeseries], \r\n" +
            "  g.[AltitudeTimeseries], \r\n" +
            "  gd.[HeadingTrueNorthTimeseries], \r\n" +
            "  gd.[HeadingMagneticNorthTimeseries], \r\n" +
            "  gd.[PitchTimeseries], \r\n" +
            "  gd.[RateOfTurnTimeseries], \r\n" +
            "  gd.[RollTimeseries], \r\n" +
            "  gd.[CourseTimeseries], \r\n" +
            "  gd.[SpeedTimeseries], \r\n" +
            "  gd.[GNSSDevice], \r\n" +
            "  rdo.[Radar], \r\n" +
            "  rdo.[PressureTimeseries], \r\n" +
            "  rdo.[TemperatureTimeseries], \r\n" +
            "  rdo.[DewPointTimeseries], \r\n" +
            "  rdo.[StatusTimeseries], \r\n" +
            "  rd.[SaveSettingsTimeseries], \r\n" +
            "  rd.[PowerOnTimeseries], \r\n" +
            "  rd.[TrackingOnTimeseries], \r\n" +
            "  rd.[RadarPulseTimeseries], \r\n" +
            "  rd.[TuningTimeseries], \r\n" +
            "  rd.[BlankSector1Timeseries], \r\n" +
            "  rd.[Sector1StartTimeseries], \r\n" +
            "  rd.[Sector1EndTimeseries], \r\n" +
            "  rd.[BlankSector2Timeseries], \r\n" +
            "  rd.[Sector2StartTimeseries], \r\n" +
            "  rd.[Sector2EndTimeseries], \r\n" +
            "  rd.[EnableAutomaticFrequencyControlTimeseries], \r\n" +
            "  rd.[AzimuthOffsetTimeseries], \r\n" +
            "  rd.[EnableSensitivityTimeControlTimeseries], \r\n" +
            "  rd.[AutomaticSensitivityTimeControlTimeseries], \r\n" +
            "  rd.[SensitivityTimeControlLevelTimeseries], \r\n" +
            "  rd.[EnableFastTimeConstantTimeseries], \r\n" +
            "  rd.[FastTimeConstantLevelTimeseries], \r\n" +
            "  rd.[FastTimeConstantModeTimeseries], \r\n" +
            "  rd.[LatitudeTimeseries], \r\n" +
            "  rd.[LongitudeTimeseries], \r\n" +
            "  rd.[Radome], \r\n" +
            "  rd.[GNSSDevice], \r\n" +
            "  wsd.[BarometricPressureTimeseries], \r\n" +
            "  wsd.[AirTemperatureTimeseries], \r\n" +
            "  wsd.[WaterTemperatureTimeseries], \r\n" +
            "  wsd.[RelativeHumidityTimeseries], \r\n" +
            "  wsd.[AbsoluteHumidityTimeseries], \r\n" +
            "  wsd.[DewPointTimeseries], \r\n" +
            "  wsd.[WindDirectionTimeseries], \r\n" +
            "  wsd.[WindSpeedTimeseries], \r\n" +
            "  wsd.[Gyro], \r\n" +
            "  f.[Name], \r\n" +
            "  f.[Type], \r\n" +
            "  f.[Longitude], \r\n" +
            "  f.[Latitude], \r\n" +
            "  f.[Altitude], \r\n" +
            "  a.[Name], \r\n" +
            "  a.[Type], \r\n" +
            "  aatn.[Name], \r\n" +
            "  aatn.[MMSI], \r\n" +
            "  aatn.[NavigationalAidType], \r\n" +
            "  aatn.[Position], \r\n" +
            "  aatn.[IsVirtual], \r\n" +
            "  aatn.[ToBow], \r\n" +
            "  aatn.[ToStern], \r\n" +
            "  aatn.[ToPort], \r\n" +
            "  aatn.[ToStarboard], \r\n" +
            "  aatn.[OffPositionTimeseries], \r\n" +
            "  v.[Name], \r\n" +
            "  v.[Type], \r\n" +
            "  vsl.[Name], \r\n" +
            "  vsl.[Type], \r\n" +
            "  vsl.[ToBow], \r\n" +
            "  vsl.[ToStern], \r\n" +
            "  vsl.[ToPort], \r\n" +
            "  vsl.[ToStarboard], \r\n" +
            "  vsl.[DraughtTimeseries], \r\n" +
            "  vsl.[PersonsOnBoardTimeseries], \r\n" +
            "  d.[Description] \r\n" +
            "FROM [ItemView] i \r\n" +
            "  LEFT JOIN [BaseStation] bs ON(i.[Id] = bs.[Id] ) \r\n" +
            "  LEFT JOIN [Device] d ON(i.[Id] = d.[Id] ) \r\n" +
            "  LEFT JOIN [CameraDevice] cd ON(i.[Id] = cd.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSDevice] g ON(i.[Id] = g.[Id] ) \r\n" +
            "  LEFT JOIN [GyroDevice] gd ON(i.[Id] = gd.[Id] ) \r\n" +
            "  LEFT JOIN [LineInputDevice] lid ON(i.[Id] = lid.[Id] ) \r\n" +
            "  LEFT JOIN [OilSpillDetectorDevice] osdd ON(i.[Id] = osdd.[Id] ) \r\n" +
            "  LEFT JOIN [RadioDevice] rdi ON(i.[Id] = rdi.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeDevice] rdo ON(i.[Id] = rdo.[Id] ) \r\n" +
            "  LEFT JOIN [TrackerDevice] td ON(i.[Id] = td.[Id] ) \r\n" +
            "  LEFT JOIN [AisDevice] ad ON(i.[Id] = ad.[Id] ) \r\n" +
            "  LEFT JOIN [RadarDevice] rd ON(i.[Id] = rd.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationDevice] wsd ON(i.[Id] = wsd.[Id] ) \r\n" +
            "  LEFT JOIN [Facility] f ON(i.[Id] = f.[Id] ) \r\n" +
            "  LEFT JOIN [TrackableItem] ti ON(i.[Id] = ti.[Id] ) \r\n" +
            "  LEFT JOIN [Aircraft] a ON(i.[Id] = a.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigation] aatn ON(i.[Id] = aatn.[Id] ) \r\n" +
            "  LEFT JOIN [Vehicle] v ON(i.[Id] = v.[Id] ) \r\n" +
            "  LEFT JOIN [Vessel] vsl ON(i.[Id] = vsl.[Id] ) \r\n";

        public const string BaseViewName = "ItemView";
        public const string ViewAliasName = "i";

        public const int I_ID_FIELD_ID = 0;
        public const int I_KIND_FIELD_ID = 1;
        public const int I_ROWVERSION_FIELD_ID = 2;
        public const int BS_NAME_FIELD_ID = 3;
        public const int BS_TYPE_FIELD_ID = 4;
        public const int D_HOST_FIELD_ID = 5;
        public const int D_NAME_FIELD_ID = 6;
        public const int D_ENABLEDTIMESERIES_FIELD_ID = 7;
        public const int G_LATITUDETIMESERIES_FIELD_ID = 8;
        public const int G_LONGITUDETIMESERIES_FIELD_ID = 9;
        public const int G_ALTITUDETIMESERIES_FIELD_ID = 10;
        public const int GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID = 11;
        public const int GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID = 12;
        public const int GD_PITCHTIMESERIES_FIELD_ID = 13;
        public const int GD_RATEOFTURNTIMESERIES_FIELD_ID = 14;
        public const int GD_ROLLTIMESERIES_FIELD_ID = 15;
        public const int GD_COURSETIMESERIES_FIELD_ID = 16;
        public const int GD_SPEEDTIMESERIES_FIELD_ID = 17;
        public const int GD_GNSSDEVICE_FIELD_ID = 18;
        public const int RDO_RADAR_FIELD_ID = 19;
        public const int RDO_PRESSURETIMESERIES_FIELD_ID = 20;
        public const int RDO_TEMPERATURETIMESERIES_FIELD_ID = 21;
        public const int RDO_DEWPOINTTIMESERIES_FIELD_ID = 22;
        public const int RDO_STATUSTIMESERIES_FIELD_ID = 23;
        public const int RD_SAVESETTINGSTIMESERIES_FIELD_ID = 24;
        public const int RD_POWERONTIMESERIES_FIELD_ID = 25;
        public const int RD_TRACKINGONTIMESERIES_FIELD_ID = 26;
        public const int RD_RADARPULSETIMESERIES_FIELD_ID = 27;
        public const int RD_TUNINGTIMESERIES_FIELD_ID = 28;
        public const int RD_BLANKSECTOR1TIMESERIES_FIELD_ID = 29;
        public const int RD_SECTOR1STARTTIMESERIES_FIELD_ID = 30;
        public const int RD_SECTOR1ENDTIMESERIES_FIELD_ID = 31;
        public const int RD_BLANKSECTOR2TIMESERIES_FIELD_ID = 32;
        public const int RD_SECTOR2STARTTIMESERIES_FIELD_ID = 33;
        public const int RD_SECTOR2ENDTIMESERIES_FIELD_ID = 34;
        public const int RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 35;
        public const int RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID = 36;
        public const int RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 37;
        public const int RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 38;
        public const int RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 39;
        public const int RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 40;
        public const int RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 41;
        public const int RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 42;
        public const int RD_LATITUDETIMESERIES_FIELD_ID = 43;
        public const int RD_LONGITUDETIMESERIES_FIELD_ID = 44;
        public const int RD_RADOME_FIELD_ID = 45;
        public const int RD_GNSSDEVICE_FIELD_ID = 46;
        public const int WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID = 47;
        public const int WSD_AIRTEMPERATURETIMESERIES_FIELD_ID = 48;
        public const int WSD_WATERTEMPERATURETIMESERIES_FIELD_ID = 49;
        public const int WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID = 50;
        public const int WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID = 51;
        public const int WSD_DEWPOINTTIMESERIES_FIELD_ID = 52;
        public const int WSD_WINDDIRECTIONTIMESERIES_FIELD_ID = 53;
        public const int WSD_WINDSPEEDTIMESERIES_FIELD_ID = 54;
        public const int WSD_GYRO_FIELD_ID = 55;
        public const int F_NAME_FIELD_ID = 56;
        public const int F_TYPE_FIELD_ID = 57;
        public const int F_LONGITUDE_FIELD_ID = 58;
        public const int F_LATITUDE_FIELD_ID = 59;
        public const int F_ALTITUDE_FIELD_ID = 60;
        public const int A_NAME_FIELD_ID = 61;
        public const int A_TYPE_FIELD_ID = 62;
        public const int AATN_NAME_FIELD_ID = 63;
        public const int AATN_MMSI_FIELD_ID = 64;
        public const int AATN_NAVIGATIONALAIDTYPE_FIELD_ID = 65;
        public const int AATN_POSITION_FIELD_ID = 66;
        public const int AATN_ISVIRTUAL_FIELD_ID = 67;
        public const int AATN_TOBOW_FIELD_ID = 68;
        public const int AATN_TOSTERN_FIELD_ID = 69;
        public const int AATN_TOPORT_FIELD_ID = 70;
        public const int AATN_TOSTARBOARD_FIELD_ID = 71;
        public const int AATN_OFFPOSITIONTIMESERIES_FIELD_ID = 72;
        public const int V_NAME_FIELD_ID = 73;
        public const int V_TYPE_FIELD_ID = 74;
        public const int VSL_NAME_FIELD_ID = 75;
        public const int VSL_TYPE_FIELD_ID = 76;
        public const int VSL_TOBOW_FIELD_ID = 77;
        public const int VSL_TOSTERN_FIELD_ID = 78;
        public const int VSL_TOPORT_FIELD_ID = 79;
        public const int VSL_TOSTARBOARD_FIELD_ID = 80;
        public const int VSL_DRAUGHTTIMESERIES_FIELD_ID = 81;
        public const int VSL_PERSONSONBOARDTIMESERIES_FIELD_ID = 82;
        public const int D_DESCRIPTION_FIELD_ID = 83;
        public ComplexItemDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( I_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( I_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( I_ROWVERSION_FIELD_ID );
            }
        }
        public string BaseStationName
        {
            get
            {
                return GetString( BS_NAME_FIELD_ID );
            }
        }
        public Guid? BaseStationType
        {
            get
            {
                return GetNullableGuid( BS_TYPE_FIELD_ID );
            }
        }
        public Guid DeviceHost
        {
            get
            {
                return GetGuid( D_HOST_FIELD_ID );
            }
        }
        public string DeviceName
        {
            get
            {
                return GetString( D_NAME_FIELD_ID );
            }
        }
        public string DeviceDescription
        {
            get
            {
                return GetString( D_DESCRIPTION_FIELD_ID );
            }
        }
        public Guid? DeviceEnabledTimeseries
        {
            get
            {
                return GetNullableGuid( D_ENABLEDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GNSSDeviceLatitudeTimeseries
        {
            get
            {
                return GetNullableGuid( G_LATITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? GNSSDeviceLongitudeTimeseries
        {
            get
            {
                return GetNullableGuid( G_LONGITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? GNSSDeviceAltitudeTimeseries
        {
            get
            {
                return GetNullableGuid( G_ALTITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceHeadingTrueNorthTimeseries
        {
            get
            {
                return GetNullableGuid( GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceHeadingMagneticNorthTimeseries
        {
            get
            {
                return GetNullableGuid( GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDevicePitchTimeseries
        {
            get
            {
                return GetNullableGuid( GD_PITCHTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceRateOfTurnTimeseries
        {
            get
            {
                return GetNullableGuid( GD_RATEOFTURNTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceRollTimeseries
        {
            get
            {
                return GetNullableGuid( GD_ROLLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceCourseTimeseries
        {
            get
            {
                return GetNullableGuid( GD_COURSETIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceSpeedTimeseries
        {
            get
            {
                return GetNullableGuid( GD_SPEEDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceGNSSDevice
        {
            get
            {
                return GetNullableGuid( GD_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? RadomeDeviceRadar
        {
            get
            {
                return GetNullableGuid( RDO_RADAR_FIELD_ID );
            }
        }
        public Guid? RadomeDevicePressureTimeseries
        {
            get
            {
                return GetNullableGuid( RDO_PRESSURETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadomeDeviceTemperatureTimeseries
        {
            get
            {
                return GetNullableGuid( RDO_TEMPERATURETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadomeDeviceDewPointTimeseries
        {
            get
            {
                return GetNullableGuid( RDO_DEWPOINTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadomeDeviceStatusTimeseries
        {
            get
            {
                return GetNullableGuid( RDO_STATUSTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSaveSettingsTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SAVESETTINGSTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDevicePowerOnTimeseries
        {
            get
            {
                return GetNullableGuid( RD_POWERONTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceTrackingOnTimeseries
        {
            get
            {
                return GetNullableGuid( RD_TRACKINGONTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceRadarPulseTimeseries
        {
            get
            {
                return GetNullableGuid( RD_RADARPULSETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceTuningTimeseries
        {
            get
            {
                return GetNullableGuid( RD_TUNINGTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceBlankSector1Timeseries
        {
            get
            {
                return GetNullableGuid( RD_BLANKSECTOR1TIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector1StartTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR1STARTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector1EndTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR1ENDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceBlankSector2Timeseries
        {
            get
            {
                return GetNullableGuid( RD_BLANKSECTOR2TIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector2StartTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR2STARTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector2EndTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR2ENDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceEnableAutomaticFrequencyControlTimeseries
        {
            get
            {
                return GetNullableGuid( RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceAzimuthOffsetTimeseries
        {
            get
            {
                return GetNullableGuid( RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceEnableSensitivityTimeControlTimeseries
        {
            get
            {
                return GetNullableGuid( RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceAutomaticSensitivityTimeControlTimeseries
        {
            get
            {
                return GetNullableGuid( RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSensitivityTimeControlLevelTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceEnableFastTimeConstantTimeseries
        {
            get
            {
                return GetNullableGuid( RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceFastTimeConstantLevelTimeseries
        {
            get
            {
                return GetNullableGuid( RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceFastTimeConstantModeTimeseries
        {
            get
            {
                return GetNullableGuid( RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceLatitudeTimeseries
        {
            get
            {
                return GetNullableGuid( RD_LATITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceLongitudeTimeseries
        {
            get
            {
                return GetNullableGuid( RD_LONGITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceRadome
        {
            get
            {
                return GetNullableGuid( RD_RADOME_FIELD_ID );
            }
        }
        public Guid? RadarDeviceGNSSDevice
        {
            get
            {
                return GetNullableGuid( RD_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceBarometricPressureTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceAirTemperatureTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_AIRTEMPERATURETIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceWaterTemperatureTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_WATERTEMPERATURETIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceRelativeHumidityTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceAbsoluteHumidityTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceDewPointTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_DEWPOINTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceWindDirectionTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_WINDDIRECTIONTIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceWindSpeedTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_WINDSPEEDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceGyro
        {
            get
            {
                return GetNullableGuid( WSD_GYRO_FIELD_ID );
            }
        }
        public string FacilityName
        {
            get
            {
                return GetString( F_NAME_FIELD_ID );
            }
        }
        public Guid? FacilityType
        {
            get
            {
                return GetNullableGuid( F_TYPE_FIELD_ID );
            }
        }
        public double FacilityLongitude
        {
            get
            {
                return GetDouble( F_LONGITUDE_FIELD_ID );
            }
        }
        public double FacilityLatitude
        {
            get
            {
                return GetDouble( F_LATITUDE_FIELD_ID );
            }
        }
        public double FacilityAltitude
        {
            get
            {
                return GetDouble( F_ALTITUDE_FIELD_ID );
            }
        }
        public string AircraftName
        {
            get
            {
                return GetString( A_NAME_FIELD_ID );
            }
        }
        public Guid? AircraftType
        {
            get
            {
                return GetNullableGuid( A_TYPE_FIELD_ID );
            }
        }
        public string AisAidToNavigationName
        {
            get
            {
                return GetString( AATN_NAME_FIELD_ID );
            }
        }
        public Guid? AisAidToNavigationMMSI
        {
            get
            {
                return GetNullableGuid( AATN_MMSI_FIELD_ID );
            }
        }
        public Types.NavigationalAidType AisAidToNavigationNavigationalAidType
        {
            get
            {
                return GetEnum<Types.NavigationalAidType>( AATN_NAVIGATIONALAIDTYPE_FIELD_ID );
            }
        }
        public Guid? AisAidToNavigationPosition
        {
            get
            {
                return GetNullableGuid( AATN_POSITION_FIELD_ID );
            }
        }
        public bool AisAidToNavigationIsVirtual
        {
            get
            {
                return GetBoolean( AATN_ISVIRTUAL_FIELD_ID );
            }
        }
        public int AisAidToNavigationToBow
        {
            get
            {
                return GetInt32( AATN_TOBOW_FIELD_ID );
            }
        }
        public int AisAidToNavigationToStern
        {
            get
            {
                return GetInt32( AATN_TOSTERN_FIELD_ID );
            }
        }
        public int AisAidToNavigationToPort
        {
            get
            {
                return GetInt32( AATN_TOPORT_FIELD_ID );
            }
        }
        public int AisAidToNavigationToStarboard
        {
            get
            {
                return GetInt32( AATN_TOSTARBOARD_FIELD_ID );
            }
        }
        public Guid? AisAidToNavigationOffPositionTimeseries
        {
            get
            {
                return GetNullableGuid( AATN_OFFPOSITIONTIMESERIES_FIELD_ID );
            }
        }
        public string VehicleName
        {
            get
            {
                return GetString( V_NAME_FIELD_ID );
            }
        }
        public Guid? VehicleType
        {
            get
            {
                return GetNullableGuid( V_TYPE_FIELD_ID );
            }
        }
        public string VesselName
        {
            get
            {
                return GetString( VSL_NAME_FIELD_ID );
            }
        }
        public Guid? VesselType
        {
            get
            {
                return GetNullableGuid( VSL_TYPE_FIELD_ID );
            }
        }
        public int VesselToBow
        {
            get
            {
                return GetInt32( VSL_TOBOW_FIELD_ID );
            }
        }
        public int VesselToStern
        {
            get
            {
                return GetInt32( VSL_TOSTERN_FIELD_ID );
            }
        }
        public int VesselToPort
        {
            get
            {
                return GetInt32( VSL_TOPORT_FIELD_ID );
            }
        }
        public int VesselToStarboard
        {
            get
            {
                return GetInt32( VSL_TOSTARBOARD_FIELD_ID );
            }
        }
        public Guid? VesselDraughtTimeseries
        {
            get
            {
                return GetNullableGuid( VSL_DRAUGHTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? VesselPersonsOnBoardTimeseries
        {
            get
            {
                return GetNullableGuid( VSL_PERSONSONBOARDTIMESERIES_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BaseStation:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( BaseStationName );
                    destination.Write( BaseStationType );
                }
                break;
                case Types.Kind.CameraDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( DeviceHost );
                    destination.Write( DeviceName );
                    destination.Write( DeviceDescription );
                    destination.Write( DeviceEnabledTimeseries );
                }
                break;
                case Types.Kind.GNSSDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( DeviceHost );
                    destination.Write( DeviceName );
                    destination.Write( DeviceDescription );
                    destination.Write( DeviceEnabledTimeseries );
                    destination.Write( GNSSDeviceLatitudeTimeseries );
                    destination.Write( GNSSDeviceLongitudeTimeseries );
                    destination.Write( GNSSDeviceAltitudeTimeseries );
                }
                break;
                case Types.Kind.GyroDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( DeviceHost );
                    destination.Write( DeviceName );
                    destination.Write( DeviceDescription );
                    destination.Write( DeviceEnabledTimeseries );
                    destination.Write( GyroDeviceHeadingTrueNorthTimeseries );
                    destination.Write( GyroDeviceHeadingMagneticNorthTimeseries );
                    destination.Write( GyroDevicePitchTimeseries );
                    destination.Write( GyroDeviceRateOfTurnTimeseries );
                    destination.Write( GyroDeviceRollTimeseries );
                    destination.Write( GyroDeviceCourseTimeseries );
                    destination.Write( GyroDeviceSpeedTimeseries );
                    destination.Write( GyroDeviceGNSSDevice );
                }
                break;
                case Types.Kind.LineInputDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( DeviceHost );
                    destination.Write( DeviceName );
                    destination.Write( DeviceDescription );
                    destination.Write( DeviceEnabledTimeseries );
                }
                break;
                case Types.Kind.OilSpillDetectorDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( DeviceHost );
                    destination.Write( DeviceName );
                    destination.Write( DeviceDescription );
                    destination.Write( DeviceEnabledTimeseries );
                }
                break;
                case Types.Kind.RadioDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( DeviceHost );
                    destination.Write( DeviceName );
                    destination.Write( DeviceDescription );
                    destination.Write( DeviceEnabledTimeseries );
                }
                break;
                case Types.Kind.RadomeDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( DeviceHost );
                    destination.Write( DeviceName );
                    destination.Write( DeviceDescription );
                    destination.Write( DeviceEnabledTimeseries );
                    destination.Write( RadomeDeviceRadar );
                    destination.Write( RadomeDevicePressureTimeseries );
                    destination.Write( RadomeDeviceTemperatureTimeseries );
                    destination.Write( RadomeDeviceDewPointTimeseries );
                    destination.Write( RadomeDeviceStatusTimeseries );
                }
                break;
                case Types.Kind.AisDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( DeviceHost );
                    destination.Write( DeviceName );
                    destination.Write( DeviceDescription );
                    destination.Write( DeviceEnabledTimeseries );
                }
                break;
                case Types.Kind.RadarDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( DeviceHost );
                    destination.Write( DeviceName );
                    destination.Write( DeviceDescription );
                    destination.Write( DeviceEnabledTimeseries );
                    destination.Write( RadarDeviceSaveSettingsTimeseries );
                    destination.Write( RadarDevicePowerOnTimeseries );
                    destination.Write( RadarDeviceTrackingOnTimeseries );
                    destination.Write( RadarDeviceRadarPulseTimeseries );
                    destination.Write( RadarDeviceTuningTimeseries );
                    destination.Write( RadarDeviceBlankSector1Timeseries );
                    destination.Write( RadarDeviceSector1StartTimeseries );
                    destination.Write( RadarDeviceSector1EndTimeseries );
                    destination.Write( RadarDeviceBlankSector2Timeseries );
                    destination.Write( RadarDeviceSector2StartTimeseries );
                    destination.Write( RadarDeviceSector2EndTimeseries );
                    destination.Write( RadarDeviceEnableAutomaticFrequencyControlTimeseries );
                    destination.Write( RadarDeviceAzimuthOffsetTimeseries );
                    destination.Write( RadarDeviceEnableSensitivityTimeControlTimeseries );
                    destination.Write( RadarDeviceAutomaticSensitivityTimeControlTimeseries );
                    destination.Write( RadarDeviceSensitivityTimeControlLevelTimeseries );
                    destination.Write( RadarDeviceEnableFastTimeConstantTimeseries );
                    destination.Write( RadarDeviceFastTimeConstantLevelTimeseries );
                    destination.Write( RadarDeviceFastTimeConstantModeTimeseries );
                    destination.Write( RadarDeviceLatitudeTimeseries );
                    destination.Write( RadarDeviceLongitudeTimeseries );
                    destination.Write( RadarDeviceRadome );
                    destination.Write( RadarDeviceGNSSDevice );
                }
                break;
                case Types.Kind.WeatherStationDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( DeviceHost );
                    destination.Write( DeviceName );
                    destination.Write( DeviceDescription );
                    destination.Write( DeviceEnabledTimeseries );
                    destination.Write( WeatherStationDeviceBarometricPressureTimeseries );
                    destination.Write( WeatherStationDeviceAirTemperatureTimeseries );
                    destination.Write( WeatherStationDeviceWaterTemperatureTimeseries );
                    destination.Write( WeatherStationDeviceRelativeHumidityTimeseries );
                    destination.Write( WeatherStationDeviceAbsoluteHumidityTimeseries );
                    destination.Write( WeatherStationDeviceDewPointTimeseries );
                    destination.Write( WeatherStationDeviceWindDirectionTimeseries );
                    destination.Write( WeatherStationDeviceWindSpeedTimeseries );
                    destination.Write( WeatherStationDeviceGyro );
                }
                break;
                case Types.Kind.Facility:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( FacilityName );
                    destination.Write( FacilityType );
                    destination.Write( FacilityLongitude );
                    destination.Write( FacilityLatitude );
                    destination.Write( FacilityAltitude );
                }
                break;
                case Types.Kind.Aircraft:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AircraftName );
                    destination.Write( AircraftType );
                }
                break;
                case Types.Kind.AisAidToNavigation:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisAidToNavigationName );
                    destination.Write( AisAidToNavigationMMSI );
                    destination.Write( AisAidToNavigationNavigationalAidType );
                    destination.Write( AisAidToNavigationPosition );
                    destination.Write( AisAidToNavigationIsVirtual );
                    destination.Write( AisAidToNavigationToBow );
                    destination.Write( AisAidToNavigationToStern );
                    destination.Write( AisAidToNavigationToPort );
                    destination.Write( AisAidToNavigationToStarboard );
                    destination.Write( AisAidToNavigationOffPositionTimeseries );
                }
                break;
                case Types.Kind.Vehicle:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( VehicleName );
                    destination.Write( VehicleType );
                }
                break;
                case Types.Kind.Vessel:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( VesselName );
                    destination.Write( VesselType );
                    destination.Write( VesselToBow );
                    destination.Write( VesselToStern );
                    destination.Write( VesselToPort );
                    destination.Write( VesselToStarboard );
                    destination.Write( VesselDraughtTimeseries );
                    destination.Write( VesselPersonsOnBoardTimeseries );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public ItemObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BaseStation:
                {
                    return new BaseStationObject( ObjectState.Stored, Id, RowVersion, BaseStationName, BaseStationType );
                }
                case Types.Kind.CameraDevice:
                {
                    return new CameraDeviceObject( ObjectState.Stored, Id, RowVersion, DeviceHost, DeviceName, DeviceDescription, DeviceEnabledTimeseries );
                }
                case Types.Kind.GNSSDevice:
                {
                    return new GNSSDeviceObject( ObjectState.Stored, Id, RowVersion, DeviceHost, DeviceName, DeviceDescription, DeviceEnabledTimeseries, GNSSDeviceLatitudeTimeseries, GNSSDeviceLongitudeTimeseries, GNSSDeviceAltitudeTimeseries );
                }
                case Types.Kind.GyroDevice:
                {
                    return new GyroDeviceObject( ObjectState.Stored, Id, RowVersion, DeviceHost, DeviceName, DeviceDescription, DeviceEnabledTimeseries, GyroDeviceHeadingTrueNorthTimeseries, GyroDeviceHeadingMagneticNorthTimeseries, GyroDevicePitchTimeseries, GyroDeviceRateOfTurnTimeseries, GyroDeviceRollTimeseries, GyroDeviceCourseTimeseries, GyroDeviceSpeedTimeseries, GyroDeviceGNSSDevice );
                }
                case Types.Kind.LineInputDevice:
                {
                    return new LineInputDeviceObject( ObjectState.Stored, Id, RowVersion, DeviceHost, DeviceName, DeviceDescription, DeviceEnabledTimeseries );
                }
                case Types.Kind.OilSpillDetectorDevice:
                {
                    return new OilSpillDetectorDeviceObject( ObjectState.Stored, Id, RowVersion, DeviceHost, DeviceName, DeviceDescription, DeviceEnabledTimeseries );
                }
                case Types.Kind.RadioDevice:
                {
                    return new RadioDeviceObject( ObjectState.Stored, Id, RowVersion, DeviceHost, DeviceName, DeviceDescription, DeviceEnabledTimeseries );
                }
                case Types.Kind.RadomeDevice:
                {
                    return new RadomeDeviceObject( ObjectState.Stored, Id, RowVersion, DeviceHost, DeviceName, DeviceDescription, DeviceEnabledTimeseries, RadomeDeviceRadar, RadomeDevicePressureTimeseries, RadomeDeviceTemperatureTimeseries, RadomeDeviceDewPointTimeseries, RadomeDeviceStatusTimeseries );
                }
                case Types.Kind.AisDevice:
                {
                    return new AisDeviceObject( ObjectState.Stored, Id, RowVersion, DeviceHost, DeviceName, DeviceDescription, DeviceEnabledTimeseries );
                }
                case Types.Kind.RadarDevice:
                {
                    return new RadarDeviceObject( ObjectState.Stored, Id, RowVersion, DeviceHost, DeviceName, DeviceDescription, DeviceEnabledTimeseries, RadarDeviceSaveSettingsTimeseries, RadarDevicePowerOnTimeseries, RadarDeviceTrackingOnTimeseries, RadarDeviceRadarPulseTimeseries, RadarDeviceTuningTimeseries, RadarDeviceBlankSector1Timeseries, RadarDeviceSector1StartTimeseries, RadarDeviceSector1EndTimeseries, RadarDeviceBlankSector2Timeseries, RadarDeviceSector2StartTimeseries, RadarDeviceSector2EndTimeseries, RadarDeviceEnableAutomaticFrequencyControlTimeseries, RadarDeviceAzimuthOffsetTimeseries, RadarDeviceEnableSensitivityTimeControlTimeseries, RadarDeviceAutomaticSensitivityTimeControlTimeseries, RadarDeviceSensitivityTimeControlLevelTimeseries, RadarDeviceEnableFastTimeConstantTimeseries, RadarDeviceFastTimeConstantLevelTimeseries, RadarDeviceFastTimeConstantModeTimeseries, RadarDeviceLatitudeTimeseries, RadarDeviceLongitudeTimeseries, RadarDeviceRadome, RadarDeviceGNSSDevice );
                }
                case Types.Kind.WeatherStationDevice:
                {
                    return new WeatherStationDeviceObject( ObjectState.Stored, Id, RowVersion, DeviceHost, DeviceName, DeviceDescription, DeviceEnabledTimeseries, WeatherStationDeviceBarometricPressureTimeseries, WeatherStationDeviceAirTemperatureTimeseries, WeatherStationDeviceWaterTemperatureTimeseries, WeatherStationDeviceRelativeHumidityTimeseries, WeatherStationDeviceAbsoluteHumidityTimeseries, WeatherStationDeviceDewPointTimeseries, WeatherStationDeviceWindDirectionTimeseries, WeatherStationDeviceWindSpeedTimeseries, WeatherStationDeviceGyro );
                }
                case Types.Kind.Facility:
                {
                    return new FacilityObject( ObjectState.Stored, Id, RowVersion, FacilityName, FacilityType, FacilityLongitude, FacilityLatitude, FacilityAltitude );
                }
                case Types.Kind.Aircraft:
                {
                    return new AircraftObject( ObjectState.Stored, Id, RowVersion, AircraftName, AircraftType );
                }
                case Types.Kind.AisAidToNavigation:
                {
                    return new AisAidToNavigationObject( ObjectState.Stored, Id, RowVersion, AisAidToNavigationName, AisAidToNavigationMMSI, AisAidToNavigationNavigationalAidType, AisAidToNavigationPosition, AisAidToNavigationIsVirtual, AisAidToNavigationToBow, AisAidToNavigationToStern, AisAidToNavigationToPort, AisAidToNavigationToStarboard, AisAidToNavigationOffPositionTimeseries );
                }
                case Types.Kind.Vehicle:
                {
                    return new VehicleObject( ObjectState.Stored, Id, RowVersion, VehicleName, VehicleType );
                }
                case Types.Kind.Vessel:
                {
                    return new VesselObject( ObjectState.Stored, Id, RowVersion, VesselName, VesselType, VesselToBow, VesselToStern, VesselToPort, VesselToStarboard, VesselDraughtTimeseries, VesselPersonsOnBoardTimeseries );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexDeviceDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  d.[Id], \r\n" +
            "  d.[EntityType], \r\n" +
            "  d.[RowVersion], \r\n" +
            "  d.[Host], \r\n" +
            "  d.[Name], \r\n" +
            "  d.[EnabledTimeseries], \r\n" +
            "  g.[LatitudeTimeseries], \r\n" +
            "  g.[LongitudeTimeseries], \r\n" +
            "  g.[AltitudeTimeseries], \r\n" +
            "  gd.[HeadingTrueNorthTimeseries], \r\n" +
            "  gd.[HeadingMagneticNorthTimeseries], \r\n" +
            "  gd.[PitchTimeseries], \r\n" +
            "  gd.[RateOfTurnTimeseries], \r\n" +
            "  gd.[RollTimeseries], \r\n" +
            "  gd.[CourseTimeseries], \r\n" +
            "  gd.[SpeedTimeseries], \r\n" +
            "  gd.[GNSSDevice], \r\n" +
            "  rdo.[Radar], \r\n" +
            "  rdo.[PressureTimeseries], \r\n" +
            "  rdo.[TemperatureTimeseries], \r\n" +
            "  rdo.[DewPointTimeseries], \r\n" +
            "  rdo.[StatusTimeseries], \r\n" +
            "  rd.[SaveSettingsTimeseries], \r\n" +
            "  rd.[PowerOnTimeseries], \r\n" +
            "  rd.[TrackingOnTimeseries], \r\n" +
            "  rd.[RadarPulseTimeseries], \r\n" +
            "  rd.[TuningTimeseries], \r\n" +
            "  rd.[BlankSector1Timeseries], \r\n" +
            "  rd.[Sector1StartTimeseries], \r\n" +
            "  rd.[Sector1EndTimeseries], \r\n" +
            "  rd.[BlankSector2Timeseries], \r\n" +
            "  rd.[Sector2StartTimeseries], \r\n" +
            "  rd.[Sector2EndTimeseries], \r\n" +
            "  rd.[EnableAutomaticFrequencyControlTimeseries], \r\n" +
            "  rd.[AzimuthOffsetTimeseries], \r\n" +
            "  rd.[EnableSensitivityTimeControlTimeseries], \r\n" +
            "  rd.[AutomaticSensitivityTimeControlTimeseries], \r\n" +
            "  rd.[SensitivityTimeControlLevelTimeseries], \r\n" +
            "  rd.[EnableFastTimeConstantTimeseries], \r\n" +
            "  rd.[FastTimeConstantLevelTimeseries], \r\n" +
            "  rd.[FastTimeConstantModeTimeseries], \r\n" +
            "  rd.[LatitudeTimeseries], \r\n" +
            "  rd.[LongitudeTimeseries], \r\n" +
            "  rd.[Radome], \r\n" +
            "  rd.[GNSSDevice], \r\n" +
            "  wsd.[BarometricPressureTimeseries], \r\n" +
            "  wsd.[AirTemperatureTimeseries], \r\n" +
            "  wsd.[WaterTemperatureTimeseries], \r\n" +
            "  wsd.[RelativeHumidityTimeseries], \r\n" +
            "  wsd.[AbsoluteHumidityTimeseries], \r\n" +
            "  wsd.[DewPointTimeseries], \r\n" +
            "  wsd.[WindDirectionTimeseries], \r\n" +
            "  wsd.[WindSpeedTimeseries], \r\n" +
            "  wsd.[Gyro], \r\n" +
            "  d.[Description] \r\n" +
            "FROM [DeviceView] d \r\n" +
            "  LEFT JOIN [CameraDevice] cd ON(d.[Id] = cd.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSDevice] g ON(d.[Id] = g.[Id] ) \r\n" +
            "  LEFT JOIN [GyroDevice] gd ON(d.[Id] = gd.[Id] ) \r\n" +
            "  LEFT JOIN [LineInputDevice] lid ON(d.[Id] = lid.[Id] ) \r\n" +
            "  LEFT JOIN [OilSpillDetectorDevice] osdd ON(d.[Id] = osdd.[Id] ) \r\n" +
            "  LEFT JOIN [RadioDevice] rdi ON(d.[Id] = rdi.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeDevice] rdo ON(d.[Id] = rdo.[Id] ) \r\n" +
            "  LEFT JOIN [TrackerDevice] td ON(d.[Id] = td.[Id] ) \r\n" +
            "  LEFT JOIN [AisDevice] ad ON(d.[Id] = ad.[Id] ) \r\n" +
            "  LEFT JOIN [RadarDevice] rd ON(d.[Id] = rd.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationDevice] wsd ON(d.[Id] = wsd.[Id] ) \r\n";

        public const string BaseViewName = "DeviceView";
        public const string ViewAliasName = "d";

        public const int D_ID_FIELD_ID = 0;
        public const int D_KIND_FIELD_ID = 1;
        public const int D_ROWVERSION_FIELD_ID = 2;
        public const int D_HOST_FIELD_ID = 3;
        public const int D_NAME_FIELD_ID = 4;
        public const int D_ENABLEDTIMESERIES_FIELD_ID = 5;
        public const int G_LATITUDETIMESERIES_FIELD_ID = 6;
        public const int G_LONGITUDETIMESERIES_FIELD_ID = 7;
        public const int G_ALTITUDETIMESERIES_FIELD_ID = 8;
        public const int GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID = 9;
        public const int GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID = 10;
        public const int GD_PITCHTIMESERIES_FIELD_ID = 11;
        public const int GD_RATEOFTURNTIMESERIES_FIELD_ID = 12;
        public const int GD_ROLLTIMESERIES_FIELD_ID = 13;
        public const int GD_COURSETIMESERIES_FIELD_ID = 14;
        public const int GD_SPEEDTIMESERIES_FIELD_ID = 15;
        public const int GD_GNSSDEVICE_FIELD_ID = 16;
        public const int RDO_RADAR_FIELD_ID = 17;
        public const int RDO_PRESSURETIMESERIES_FIELD_ID = 18;
        public const int RDO_TEMPERATURETIMESERIES_FIELD_ID = 19;
        public const int RDO_DEWPOINTTIMESERIES_FIELD_ID = 20;
        public const int RDO_STATUSTIMESERIES_FIELD_ID = 21;
        public const int RD_SAVESETTINGSTIMESERIES_FIELD_ID = 22;
        public const int RD_POWERONTIMESERIES_FIELD_ID = 23;
        public const int RD_TRACKINGONTIMESERIES_FIELD_ID = 24;
        public const int RD_RADARPULSETIMESERIES_FIELD_ID = 25;
        public const int RD_TUNINGTIMESERIES_FIELD_ID = 26;
        public const int RD_BLANKSECTOR1TIMESERIES_FIELD_ID = 27;
        public const int RD_SECTOR1STARTTIMESERIES_FIELD_ID = 28;
        public const int RD_SECTOR1ENDTIMESERIES_FIELD_ID = 29;
        public const int RD_BLANKSECTOR2TIMESERIES_FIELD_ID = 30;
        public const int RD_SECTOR2STARTTIMESERIES_FIELD_ID = 31;
        public const int RD_SECTOR2ENDTIMESERIES_FIELD_ID = 32;
        public const int RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 33;
        public const int RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID = 34;
        public const int RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 35;
        public const int RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 36;
        public const int RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 37;
        public const int RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 38;
        public const int RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 39;
        public const int RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 40;
        public const int RD_LATITUDETIMESERIES_FIELD_ID = 41;
        public const int RD_LONGITUDETIMESERIES_FIELD_ID = 42;
        public const int RD_RADOME_FIELD_ID = 43;
        public const int RD_GNSSDEVICE_FIELD_ID = 44;
        public const int WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID = 45;
        public const int WSD_AIRTEMPERATURETIMESERIES_FIELD_ID = 46;
        public const int WSD_WATERTEMPERATURETIMESERIES_FIELD_ID = 47;
        public const int WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID = 48;
        public const int WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID = 49;
        public const int WSD_DEWPOINTTIMESERIES_FIELD_ID = 50;
        public const int WSD_WINDDIRECTIONTIMESERIES_FIELD_ID = 51;
        public const int WSD_WINDSPEEDTIMESERIES_FIELD_ID = 52;
        public const int WSD_GYRO_FIELD_ID = 53;
        public const int D_DESCRIPTION_FIELD_ID = 54;
        public ComplexDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( D_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( D_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( D_ROWVERSION_FIELD_ID );
            }
        }
        public Guid Host
        {
            get
            {
                return GetGuid( D_HOST_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( D_NAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( D_DESCRIPTION_FIELD_ID );
            }
        }
        public Guid? EnabledTimeseries
        {
            get
            {
                return GetNullableGuid( D_ENABLEDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GNSSDeviceLatitudeTimeseries
        {
            get
            {
                return GetNullableGuid( G_LATITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? GNSSDeviceLongitudeTimeseries
        {
            get
            {
                return GetNullableGuid( G_LONGITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? GNSSDeviceAltitudeTimeseries
        {
            get
            {
                return GetNullableGuid( G_ALTITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceHeadingTrueNorthTimeseries
        {
            get
            {
                return GetNullableGuid( GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceHeadingMagneticNorthTimeseries
        {
            get
            {
                return GetNullableGuid( GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDevicePitchTimeseries
        {
            get
            {
                return GetNullableGuid( GD_PITCHTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceRateOfTurnTimeseries
        {
            get
            {
                return GetNullableGuid( GD_RATEOFTURNTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceRollTimeseries
        {
            get
            {
                return GetNullableGuid( GD_ROLLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceCourseTimeseries
        {
            get
            {
                return GetNullableGuid( GD_COURSETIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceSpeedTimeseries
        {
            get
            {
                return GetNullableGuid( GD_SPEEDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? GyroDeviceGNSSDevice
        {
            get
            {
                return GetNullableGuid( GD_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? RadomeDeviceRadar
        {
            get
            {
                return GetNullableGuid( RDO_RADAR_FIELD_ID );
            }
        }
        public Guid? RadomeDevicePressureTimeseries
        {
            get
            {
                return GetNullableGuid( RDO_PRESSURETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadomeDeviceTemperatureTimeseries
        {
            get
            {
                return GetNullableGuid( RDO_TEMPERATURETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadomeDeviceDewPointTimeseries
        {
            get
            {
                return GetNullableGuid( RDO_DEWPOINTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadomeDeviceStatusTimeseries
        {
            get
            {
                return GetNullableGuid( RDO_STATUSTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSaveSettingsTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SAVESETTINGSTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDevicePowerOnTimeseries
        {
            get
            {
                return GetNullableGuid( RD_POWERONTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceTrackingOnTimeseries
        {
            get
            {
                return GetNullableGuid( RD_TRACKINGONTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceRadarPulseTimeseries
        {
            get
            {
                return GetNullableGuid( RD_RADARPULSETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceTuningTimeseries
        {
            get
            {
                return GetNullableGuid( RD_TUNINGTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceBlankSector1Timeseries
        {
            get
            {
                return GetNullableGuid( RD_BLANKSECTOR1TIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector1StartTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR1STARTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector1EndTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR1ENDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceBlankSector2Timeseries
        {
            get
            {
                return GetNullableGuid( RD_BLANKSECTOR2TIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector2StartTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR2STARTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector2EndTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR2ENDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceEnableAutomaticFrequencyControlTimeseries
        {
            get
            {
                return GetNullableGuid( RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceAzimuthOffsetTimeseries
        {
            get
            {
                return GetNullableGuid( RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceEnableSensitivityTimeControlTimeseries
        {
            get
            {
                return GetNullableGuid( RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceAutomaticSensitivityTimeControlTimeseries
        {
            get
            {
                return GetNullableGuid( RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSensitivityTimeControlLevelTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceEnableFastTimeConstantTimeseries
        {
            get
            {
                return GetNullableGuid( RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceFastTimeConstantLevelTimeseries
        {
            get
            {
                return GetNullableGuid( RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceFastTimeConstantModeTimeseries
        {
            get
            {
                return GetNullableGuid( RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceLatitudeTimeseries
        {
            get
            {
                return GetNullableGuid( RD_LATITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceLongitudeTimeseries
        {
            get
            {
                return GetNullableGuid( RD_LONGITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceRadome
        {
            get
            {
                return GetNullableGuid( RD_RADOME_FIELD_ID );
            }
        }
        public Guid? RadarDeviceGNSSDevice
        {
            get
            {
                return GetNullableGuid( RD_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceBarometricPressureTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceAirTemperatureTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_AIRTEMPERATURETIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceWaterTemperatureTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_WATERTEMPERATURETIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceRelativeHumidityTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceAbsoluteHumidityTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceDewPointTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_DEWPOINTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceWindDirectionTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_WINDDIRECTIONTIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceWindSpeedTimeseries
        {
            get
            {
                return GetNullableGuid( WSD_WINDSPEEDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? WeatherStationDeviceGyro
        {
            get
            {
                return GetNullableGuid( WSD_GYRO_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.CameraDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                }
                break;
                case Types.Kind.GNSSDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                    destination.Write( GNSSDeviceLatitudeTimeseries );
                    destination.Write( GNSSDeviceLongitudeTimeseries );
                    destination.Write( GNSSDeviceAltitudeTimeseries );
                }
                break;
                case Types.Kind.GyroDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                    destination.Write( GyroDeviceHeadingTrueNorthTimeseries );
                    destination.Write( GyroDeviceHeadingMagneticNorthTimeseries );
                    destination.Write( GyroDevicePitchTimeseries );
                    destination.Write( GyroDeviceRateOfTurnTimeseries );
                    destination.Write( GyroDeviceRollTimeseries );
                    destination.Write( GyroDeviceCourseTimeseries );
                    destination.Write( GyroDeviceSpeedTimeseries );
                    destination.Write( GyroDeviceGNSSDevice );
                }
                break;
                case Types.Kind.LineInputDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                }
                break;
                case Types.Kind.OilSpillDetectorDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                }
                break;
                case Types.Kind.RadioDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                }
                break;
                case Types.Kind.RadomeDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                    destination.Write( RadomeDeviceRadar );
                    destination.Write( RadomeDevicePressureTimeseries );
                    destination.Write( RadomeDeviceTemperatureTimeseries );
                    destination.Write( RadomeDeviceDewPointTimeseries );
                    destination.Write( RadomeDeviceStatusTimeseries );
                }
                break;
                case Types.Kind.AisDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                }
                break;
                case Types.Kind.RadarDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                    destination.Write( RadarDeviceSaveSettingsTimeseries );
                    destination.Write( RadarDevicePowerOnTimeseries );
                    destination.Write( RadarDeviceTrackingOnTimeseries );
                    destination.Write( RadarDeviceRadarPulseTimeseries );
                    destination.Write( RadarDeviceTuningTimeseries );
                    destination.Write( RadarDeviceBlankSector1Timeseries );
                    destination.Write( RadarDeviceSector1StartTimeseries );
                    destination.Write( RadarDeviceSector1EndTimeseries );
                    destination.Write( RadarDeviceBlankSector2Timeseries );
                    destination.Write( RadarDeviceSector2StartTimeseries );
                    destination.Write( RadarDeviceSector2EndTimeseries );
                    destination.Write( RadarDeviceEnableAutomaticFrequencyControlTimeseries );
                    destination.Write( RadarDeviceAzimuthOffsetTimeseries );
                    destination.Write( RadarDeviceEnableSensitivityTimeControlTimeseries );
                    destination.Write( RadarDeviceAutomaticSensitivityTimeControlTimeseries );
                    destination.Write( RadarDeviceSensitivityTimeControlLevelTimeseries );
                    destination.Write( RadarDeviceEnableFastTimeConstantTimeseries );
                    destination.Write( RadarDeviceFastTimeConstantLevelTimeseries );
                    destination.Write( RadarDeviceFastTimeConstantModeTimeseries );
                    destination.Write( RadarDeviceLatitudeTimeseries );
                    destination.Write( RadarDeviceLongitudeTimeseries );
                    destination.Write( RadarDeviceRadome );
                    destination.Write( RadarDeviceGNSSDevice );
                }
                break;
                case Types.Kind.WeatherStationDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                    destination.Write( WeatherStationDeviceBarometricPressureTimeseries );
                    destination.Write( WeatherStationDeviceAirTemperatureTimeseries );
                    destination.Write( WeatherStationDeviceWaterTemperatureTimeseries );
                    destination.Write( WeatherStationDeviceRelativeHumidityTimeseries );
                    destination.Write( WeatherStationDeviceAbsoluteHumidityTimeseries );
                    destination.Write( WeatherStationDeviceDewPointTimeseries );
                    destination.Write( WeatherStationDeviceWindDirectionTimeseries );
                    destination.Write( WeatherStationDeviceWindSpeedTimeseries );
                    destination.Write( WeatherStationDeviceGyro );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public DeviceObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.CameraDevice:
                {
                    return new CameraDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries );
                }
                case Types.Kind.GNSSDevice:
                {
                    return new GNSSDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries, GNSSDeviceLatitudeTimeseries, GNSSDeviceLongitudeTimeseries, GNSSDeviceAltitudeTimeseries );
                }
                case Types.Kind.GyroDevice:
                {
                    return new GyroDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries, GyroDeviceHeadingTrueNorthTimeseries, GyroDeviceHeadingMagneticNorthTimeseries, GyroDevicePitchTimeseries, GyroDeviceRateOfTurnTimeseries, GyroDeviceRollTimeseries, GyroDeviceCourseTimeseries, GyroDeviceSpeedTimeseries, GyroDeviceGNSSDevice );
                }
                case Types.Kind.LineInputDevice:
                {
                    return new LineInputDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries );
                }
                case Types.Kind.OilSpillDetectorDevice:
                {
                    return new OilSpillDetectorDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries );
                }
                case Types.Kind.RadioDevice:
                {
                    return new RadioDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries );
                }
                case Types.Kind.RadomeDevice:
                {
                    return new RadomeDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries, RadomeDeviceRadar, RadomeDevicePressureTimeseries, RadomeDeviceTemperatureTimeseries, RadomeDeviceDewPointTimeseries, RadomeDeviceStatusTimeseries );
                }
                case Types.Kind.AisDevice:
                {
                    return new AisDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries );
                }
                case Types.Kind.RadarDevice:
                {
                    return new RadarDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries, RadarDeviceSaveSettingsTimeseries, RadarDevicePowerOnTimeseries, RadarDeviceTrackingOnTimeseries, RadarDeviceRadarPulseTimeseries, RadarDeviceTuningTimeseries, RadarDeviceBlankSector1Timeseries, RadarDeviceSector1StartTimeseries, RadarDeviceSector1EndTimeseries, RadarDeviceBlankSector2Timeseries, RadarDeviceSector2StartTimeseries, RadarDeviceSector2EndTimeseries, RadarDeviceEnableAutomaticFrequencyControlTimeseries, RadarDeviceAzimuthOffsetTimeseries, RadarDeviceEnableSensitivityTimeControlTimeseries, RadarDeviceAutomaticSensitivityTimeControlTimeseries, RadarDeviceSensitivityTimeControlLevelTimeseries, RadarDeviceEnableFastTimeConstantTimeseries, RadarDeviceFastTimeConstantLevelTimeseries, RadarDeviceFastTimeConstantModeTimeseries, RadarDeviceLatitudeTimeseries, RadarDeviceLongitudeTimeseries, RadarDeviceRadome, RadarDeviceGNSSDevice );
                }
                case Types.Kind.WeatherStationDevice:
                {
                    return new WeatherStationDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries, WeatherStationDeviceBarometricPressureTimeseries, WeatherStationDeviceAirTemperatureTimeseries, WeatherStationDeviceWaterTemperatureTimeseries, WeatherStationDeviceRelativeHumidityTimeseries, WeatherStationDeviceAbsoluteHumidityTimeseries, WeatherStationDeviceDewPointTimeseries, WeatherStationDeviceWindDirectionTimeseries, WeatherStationDeviceWindSpeedTimeseries, WeatherStationDeviceGyro );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexTrackerDeviceDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  td.[Id], \r\n" +
            "  td.[EntityType], \r\n" +
            "  td.[RowVersion], \r\n" +
            "  td.[Host], \r\n" +
            "  td.[Name], \r\n" +
            "  td.[EnabledTimeseries], \r\n" +
            "  rd.[SaveSettingsTimeseries], \r\n" +
            "  rd.[PowerOnTimeseries], \r\n" +
            "  rd.[TrackingOnTimeseries], \r\n" +
            "  rd.[RadarPulseTimeseries], \r\n" +
            "  rd.[TuningTimeseries], \r\n" +
            "  rd.[BlankSector1Timeseries], \r\n" +
            "  rd.[Sector1StartTimeseries], \r\n" +
            "  rd.[Sector1EndTimeseries], \r\n" +
            "  rd.[BlankSector2Timeseries], \r\n" +
            "  rd.[Sector2StartTimeseries], \r\n" +
            "  rd.[Sector2EndTimeseries], \r\n" +
            "  rd.[EnableAutomaticFrequencyControlTimeseries], \r\n" +
            "  rd.[AzimuthOffsetTimeseries], \r\n" +
            "  rd.[EnableSensitivityTimeControlTimeseries], \r\n" +
            "  rd.[AutomaticSensitivityTimeControlTimeseries], \r\n" +
            "  rd.[SensitivityTimeControlLevelTimeseries], \r\n" +
            "  rd.[EnableFastTimeConstantTimeseries], \r\n" +
            "  rd.[FastTimeConstantLevelTimeseries], \r\n" +
            "  rd.[FastTimeConstantModeTimeseries], \r\n" +
            "  rd.[LatitudeTimeseries], \r\n" +
            "  rd.[LongitudeTimeseries], \r\n" +
            "  rd.[Radome], \r\n" +
            "  rd.[GNSSDevice], \r\n" +
            "  td.[Description] \r\n" +
            "FROM [TrackerDeviceView] td \r\n" +
            "  LEFT JOIN [AisDevice] ad ON(td.[Id] = ad.[Id] ) \r\n" +
            "  LEFT JOIN [RadarDevice] rd ON(td.[Id] = rd.[Id] ) \r\n";

        public const string BaseViewName = "TrackerDeviceView";
        public const string ViewAliasName = "td";

        public const int TD_ID_FIELD_ID = 0;
        public const int TD_KIND_FIELD_ID = 1;
        public const int TD_ROWVERSION_FIELD_ID = 2;
        public const int TD_HOST_FIELD_ID = 3;
        public const int TD_NAME_FIELD_ID = 4;
        public const int TD_ENABLEDTIMESERIES_FIELD_ID = 5;
        public const int RD_SAVESETTINGSTIMESERIES_FIELD_ID = 6;
        public const int RD_POWERONTIMESERIES_FIELD_ID = 7;
        public const int RD_TRACKINGONTIMESERIES_FIELD_ID = 8;
        public const int RD_RADARPULSETIMESERIES_FIELD_ID = 9;
        public const int RD_TUNINGTIMESERIES_FIELD_ID = 10;
        public const int RD_BLANKSECTOR1TIMESERIES_FIELD_ID = 11;
        public const int RD_SECTOR1STARTTIMESERIES_FIELD_ID = 12;
        public const int RD_SECTOR1ENDTIMESERIES_FIELD_ID = 13;
        public const int RD_BLANKSECTOR2TIMESERIES_FIELD_ID = 14;
        public const int RD_SECTOR2STARTTIMESERIES_FIELD_ID = 15;
        public const int RD_SECTOR2ENDTIMESERIES_FIELD_ID = 16;
        public const int RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 17;
        public const int RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID = 18;
        public const int RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 19;
        public const int RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 20;
        public const int RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 21;
        public const int RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 22;
        public const int RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 23;
        public const int RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 24;
        public const int RD_LATITUDETIMESERIES_FIELD_ID = 25;
        public const int RD_LONGITUDETIMESERIES_FIELD_ID = 26;
        public const int RD_RADOME_FIELD_ID = 27;
        public const int RD_GNSSDEVICE_FIELD_ID = 28;
        public const int TD_DESCRIPTION_FIELD_ID = 29;
        public ComplexTrackerDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( TD_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( TD_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( TD_ROWVERSION_FIELD_ID );
            }
        }
        public Guid Host
        {
            get
            {
                return GetGuid( TD_HOST_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( TD_NAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( TD_DESCRIPTION_FIELD_ID );
            }
        }
        public Guid? EnabledTimeseries
        {
            get
            {
                return GetNullableGuid( TD_ENABLEDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSaveSettingsTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SAVESETTINGSTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDevicePowerOnTimeseries
        {
            get
            {
                return GetNullableGuid( RD_POWERONTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceTrackingOnTimeseries
        {
            get
            {
                return GetNullableGuid( RD_TRACKINGONTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceRadarPulseTimeseries
        {
            get
            {
                return GetNullableGuid( RD_RADARPULSETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceTuningTimeseries
        {
            get
            {
                return GetNullableGuid( RD_TUNINGTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceBlankSector1Timeseries
        {
            get
            {
                return GetNullableGuid( RD_BLANKSECTOR1TIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector1StartTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR1STARTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector1EndTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR1ENDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceBlankSector2Timeseries
        {
            get
            {
                return GetNullableGuid( RD_BLANKSECTOR2TIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector2StartTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR2STARTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSector2EndTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SECTOR2ENDTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceEnableAutomaticFrequencyControlTimeseries
        {
            get
            {
                return GetNullableGuid( RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceAzimuthOffsetTimeseries
        {
            get
            {
                return GetNullableGuid( RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceEnableSensitivityTimeControlTimeseries
        {
            get
            {
                return GetNullableGuid( RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceAutomaticSensitivityTimeControlTimeseries
        {
            get
            {
                return GetNullableGuid( RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceSensitivityTimeControlLevelTimeseries
        {
            get
            {
                return GetNullableGuid( RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceEnableFastTimeConstantTimeseries
        {
            get
            {
                return GetNullableGuid( RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceFastTimeConstantLevelTimeseries
        {
            get
            {
                return GetNullableGuid( RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceFastTimeConstantModeTimeseries
        {
            get
            {
                return GetNullableGuid( RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceLatitudeTimeseries
        {
            get
            {
                return GetNullableGuid( RD_LATITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceLongitudeTimeseries
        {
            get
            {
                return GetNullableGuid( RD_LONGITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? RadarDeviceRadome
        {
            get
            {
                return GetNullableGuid( RD_RADOME_FIELD_ID );
            }
        }
        public Guid? RadarDeviceGNSSDevice
        {
            get
            {
                return GetNullableGuid( RD_GNSSDEVICE_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.AisDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                }
                break;
                case Types.Kind.RadarDevice:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Host );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( EnabledTimeseries );
                    destination.Write( RadarDeviceSaveSettingsTimeseries );
                    destination.Write( RadarDevicePowerOnTimeseries );
                    destination.Write( RadarDeviceTrackingOnTimeseries );
                    destination.Write( RadarDeviceRadarPulseTimeseries );
                    destination.Write( RadarDeviceTuningTimeseries );
                    destination.Write( RadarDeviceBlankSector1Timeseries );
                    destination.Write( RadarDeviceSector1StartTimeseries );
                    destination.Write( RadarDeviceSector1EndTimeseries );
                    destination.Write( RadarDeviceBlankSector2Timeseries );
                    destination.Write( RadarDeviceSector2StartTimeseries );
                    destination.Write( RadarDeviceSector2EndTimeseries );
                    destination.Write( RadarDeviceEnableAutomaticFrequencyControlTimeseries );
                    destination.Write( RadarDeviceAzimuthOffsetTimeseries );
                    destination.Write( RadarDeviceEnableSensitivityTimeControlTimeseries );
                    destination.Write( RadarDeviceAutomaticSensitivityTimeControlTimeseries );
                    destination.Write( RadarDeviceSensitivityTimeControlLevelTimeseries );
                    destination.Write( RadarDeviceEnableFastTimeConstantTimeseries );
                    destination.Write( RadarDeviceFastTimeConstantLevelTimeseries );
                    destination.Write( RadarDeviceFastTimeConstantModeTimeseries );
                    destination.Write( RadarDeviceLatitudeTimeseries );
                    destination.Write( RadarDeviceLongitudeTimeseries );
                    destination.Write( RadarDeviceRadome );
                    destination.Write( RadarDeviceGNSSDevice );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public TrackerDeviceObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.AisDevice:
                {
                    return new AisDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries );
                }
                case Types.Kind.RadarDevice:
                {
                    return new RadarDeviceObject( ObjectState.Stored, Id, RowVersion, Host, Name, Description, EnabledTimeseries, RadarDeviceSaveSettingsTimeseries, RadarDevicePowerOnTimeseries, RadarDeviceTrackingOnTimeseries, RadarDeviceRadarPulseTimeseries, RadarDeviceTuningTimeseries, RadarDeviceBlankSector1Timeseries, RadarDeviceSector1StartTimeseries, RadarDeviceSector1EndTimeseries, RadarDeviceBlankSector2Timeseries, RadarDeviceSector2StartTimeseries, RadarDeviceSector2EndTimeseries, RadarDeviceEnableAutomaticFrequencyControlTimeseries, RadarDeviceAzimuthOffsetTimeseries, RadarDeviceEnableSensitivityTimeControlTimeseries, RadarDeviceAutomaticSensitivityTimeControlTimeseries, RadarDeviceSensitivityTimeControlLevelTimeseries, RadarDeviceEnableFastTimeConstantTimeseries, RadarDeviceFastTimeConstantLevelTimeseries, RadarDeviceFastTimeConstantModeTimeseries, RadarDeviceLatitudeTimeseries, RadarDeviceLongitudeTimeseries, RadarDeviceRadome, RadarDeviceGNSSDevice );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexTrackableItemDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ti.[Id], \r\n" +
            "  ti.[EntityType], \r\n" +
            "  ti.[RowVersion], \r\n" +
            "  a.[Name], \r\n" +
            "  a.[Type], \r\n" +
            "  aatn.[Name], \r\n" +
            "  aatn.[MMSI], \r\n" +
            "  aatn.[NavigationalAidType], \r\n" +
            "  aatn.[Position], \r\n" +
            "  aatn.[IsVirtual], \r\n" +
            "  aatn.[ToBow], \r\n" +
            "  aatn.[ToStern], \r\n" +
            "  aatn.[ToPort], \r\n" +
            "  aatn.[ToStarboard], \r\n" +
            "  aatn.[OffPositionTimeseries], \r\n" +
            "  v.[Name], \r\n" +
            "  v.[Type], \r\n" +
            "  vsl.[Name], \r\n" +
            "  vsl.[Type], \r\n" +
            "  vsl.[ToBow], \r\n" +
            "  vsl.[ToStern], \r\n" +
            "  vsl.[ToPort], \r\n" +
            "  vsl.[ToStarboard], \r\n" +
            "  vsl.[DraughtTimeseries], \r\n" +
            "  vsl.[PersonsOnBoardTimeseries] \r\n" +
            "FROM [TrackableItemView] ti \r\n" +
            "  LEFT JOIN [Aircraft] a ON(ti.[Id] = a.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigation] aatn ON(ti.[Id] = aatn.[Id] ) \r\n" +
            "  LEFT JOIN [Vehicle] v ON(ti.[Id] = v.[Id] ) \r\n" +
            "  LEFT JOIN [Vessel] vsl ON(ti.[Id] = vsl.[Id] ) \r\n";

        public const string BaseViewName = "TrackableItemView";
        public const string ViewAliasName = "ti";

        public const int TI_ID_FIELD_ID = 0;
        public const int TI_KIND_FIELD_ID = 1;
        public const int TI_ROWVERSION_FIELD_ID = 2;
        public const int A_NAME_FIELD_ID = 3;
        public const int A_TYPE_FIELD_ID = 4;
        public const int AATN_NAME_FIELD_ID = 5;
        public const int AATN_MMSI_FIELD_ID = 6;
        public const int AATN_NAVIGATIONALAIDTYPE_FIELD_ID = 7;
        public const int AATN_POSITION_FIELD_ID = 8;
        public const int AATN_ISVIRTUAL_FIELD_ID = 9;
        public const int AATN_TOBOW_FIELD_ID = 10;
        public const int AATN_TOSTERN_FIELD_ID = 11;
        public const int AATN_TOPORT_FIELD_ID = 12;
        public const int AATN_TOSTARBOARD_FIELD_ID = 13;
        public const int AATN_OFFPOSITIONTIMESERIES_FIELD_ID = 14;
        public const int V_NAME_FIELD_ID = 15;
        public const int V_TYPE_FIELD_ID = 16;
        public const int VSL_NAME_FIELD_ID = 17;
        public const int VSL_TYPE_FIELD_ID = 18;
        public const int VSL_TOBOW_FIELD_ID = 19;
        public const int VSL_TOSTERN_FIELD_ID = 20;
        public const int VSL_TOPORT_FIELD_ID = 21;
        public const int VSL_TOSTARBOARD_FIELD_ID = 22;
        public const int VSL_DRAUGHTTIMESERIES_FIELD_ID = 23;
        public const int VSL_PERSONSONBOARDTIMESERIES_FIELD_ID = 24;
        public ComplexTrackableItemDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( TI_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( TI_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( TI_ROWVERSION_FIELD_ID );
            }
        }
        public string AircraftName
        {
            get
            {
                return GetString( A_NAME_FIELD_ID );
            }
        }
        public Guid? AircraftType
        {
            get
            {
                return GetNullableGuid( A_TYPE_FIELD_ID );
            }
        }
        public string AisAidToNavigationName
        {
            get
            {
                return GetString( AATN_NAME_FIELD_ID );
            }
        }
        public Guid? AisAidToNavigationMMSI
        {
            get
            {
                return GetNullableGuid( AATN_MMSI_FIELD_ID );
            }
        }
        public Types.NavigationalAidType AisAidToNavigationNavigationalAidType
        {
            get
            {
                return GetEnum<Types.NavigationalAidType>( AATN_NAVIGATIONALAIDTYPE_FIELD_ID );
            }
        }
        public Guid? AisAidToNavigationPosition
        {
            get
            {
                return GetNullableGuid( AATN_POSITION_FIELD_ID );
            }
        }
        public bool AisAidToNavigationIsVirtual
        {
            get
            {
                return GetBoolean( AATN_ISVIRTUAL_FIELD_ID );
            }
        }
        public int AisAidToNavigationToBow
        {
            get
            {
                return GetInt32( AATN_TOBOW_FIELD_ID );
            }
        }
        public int AisAidToNavigationToStern
        {
            get
            {
                return GetInt32( AATN_TOSTERN_FIELD_ID );
            }
        }
        public int AisAidToNavigationToPort
        {
            get
            {
                return GetInt32( AATN_TOPORT_FIELD_ID );
            }
        }
        public int AisAidToNavigationToStarboard
        {
            get
            {
                return GetInt32( AATN_TOSTARBOARD_FIELD_ID );
            }
        }
        public Guid? AisAidToNavigationOffPositionTimeseries
        {
            get
            {
                return GetNullableGuid( AATN_OFFPOSITIONTIMESERIES_FIELD_ID );
            }
        }
        public string VehicleName
        {
            get
            {
                return GetString( V_NAME_FIELD_ID );
            }
        }
        public Guid? VehicleType
        {
            get
            {
                return GetNullableGuid( V_TYPE_FIELD_ID );
            }
        }
        public string VesselName
        {
            get
            {
                return GetString( VSL_NAME_FIELD_ID );
            }
        }
        public Guid? VesselType
        {
            get
            {
                return GetNullableGuid( VSL_TYPE_FIELD_ID );
            }
        }
        public int VesselToBow
        {
            get
            {
                return GetInt32( VSL_TOBOW_FIELD_ID );
            }
        }
        public int VesselToStern
        {
            get
            {
                return GetInt32( VSL_TOSTERN_FIELD_ID );
            }
        }
        public int VesselToPort
        {
            get
            {
                return GetInt32( VSL_TOPORT_FIELD_ID );
            }
        }
        public int VesselToStarboard
        {
            get
            {
                return GetInt32( VSL_TOSTARBOARD_FIELD_ID );
            }
        }
        public Guid? VesselDraughtTimeseries
        {
            get
            {
                return GetNullableGuid( VSL_DRAUGHTTIMESERIES_FIELD_ID );
            }
        }
        public Guid? VesselPersonsOnBoardTimeseries
        {
            get
            {
                return GetNullableGuid( VSL_PERSONSONBOARDTIMESERIES_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.Aircraft:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AircraftName );
                    destination.Write( AircraftType );
                }
                break;
                case Types.Kind.AisAidToNavigation:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( AisAidToNavigationName );
                    destination.Write( AisAidToNavigationMMSI );
                    destination.Write( AisAidToNavigationNavigationalAidType );
                    destination.Write( AisAidToNavigationPosition );
                    destination.Write( AisAidToNavigationIsVirtual );
                    destination.Write( AisAidToNavigationToBow );
                    destination.Write( AisAidToNavigationToStern );
                    destination.Write( AisAidToNavigationToPort );
                    destination.Write( AisAidToNavigationToStarboard );
                    destination.Write( AisAidToNavigationOffPositionTimeseries );
                }
                break;
                case Types.Kind.Vehicle:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( VehicleName );
                    destination.Write( VehicleType );
                }
                break;
                case Types.Kind.Vessel:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( VesselName );
                    destination.Write( VesselType );
                    destination.Write( VesselToBow );
                    destination.Write( VesselToStern );
                    destination.Write( VesselToPort );
                    destination.Write( VesselToStarboard );
                    destination.Write( VesselDraughtTimeseries );
                    destination.Write( VesselPersonsOnBoardTimeseries );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public TrackableItemObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.Aircraft:
                {
                    return new AircraftObject( ObjectState.Stored, Id, RowVersion, AircraftName, AircraftType );
                }
                case Types.Kind.AisAidToNavigation:
                {
                    return new AisAidToNavigationObject( ObjectState.Stored, Id, RowVersion, AisAidToNavigationName, AisAidToNavigationMMSI, AisAidToNavigationNavigationalAidType, AisAidToNavigationPosition, AisAidToNavigationIsVirtual, AisAidToNavigationToBow, AisAidToNavigationToStern, AisAidToNavigationToPort, AisAidToNavigationToStarboard, AisAidToNavigationOffPositionTimeseries );
                }
                case Types.Kind.Vehicle:
                {
                    return new VehicleObject( ObjectState.Stored, Id, RowVersion, VehicleName, VehicleType );
                }
                case Types.Kind.Vessel:
                {
                    return new VesselObject( ObjectState.Stored, Id, RowVersion, VesselName, VesselType, VesselToBow, VesselToStern, VesselToPort, VesselToStarboard, VesselDraughtTimeseries, VesselPersonsOnBoardTimeseries );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexNamespaceElementDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ne.[Id], \r\n" +
            "  ne.[EntityType], \r\n" +
            "  ne.[RowVersion], \r\n" +
            "  ne.[Namespace], \r\n" +
            "  ne.[Name], \r\n" +
            "  ne.[Description] \r\n" +
            "FROM [NamespaceElementView] ne \r\n" +
            "  LEFT JOIN [ElementType] et ON(ne.[Id] = et.[Id] ) \r\n" +
            "  LEFT JOIN [Namespace] n ON(ne.[Id] = n.[Id] ) \r\n";

        public const string BaseViewName = "NamespaceElementView";
        public const string ViewAliasName = "ne";

        public const int NE_ID_FIELD_ID = 0;
        public const int NE_KIND_FIELD_ID = 1;
        public const int NE_ROWVERSION_FIELD_ID = 2;
        public const int NE_NAMESPACE_FIELD_ID = 3;
        public const int NE_NAME_FIELD_ID = 4;
        public const int NE_DESCRIPTION_FIELD_ID = 5;
        public ComplexNamespaceElementDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( NE_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( NE_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( NE_ROWVERSION_FIELD_ID );
            }
        }
        public Guid Namespace
        {
            get
            {
                return GetGuid( NE_NAMESPACE_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NE_NAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( NE_DESCRIPTION_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.ElementType:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Namespace );
                    destination.Write( Name );
                    destination.Write( Description );
                }
                break;
                case Types.Kind.Namespace:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Namespace );
                    destination.Write( Name );
                    destination.Write( Description );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public NamespaceElementObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.ElementType:
                {
                    return new ElementTypeObject( ObjectState.Stored, Id, RowVersion, Namespace, Name, Description );
                }
                case Types.Kind.Namespace:
                {
                    return new NamespaceObject( ObjectState.Stored, Id, RowVersion, Namespace, Name, Description );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexPropertyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  p.[Id], \r\n" +
            "  p.[EntityType], \r\n" +
            "  p.[RowVersion], \r\n" +
            "  p.[Element], \r\n" +
            "  p.[Definition], \r\n" +
            "  bop.[Value], \r\n" +
            "  byp.[Value], \r\n" +
            "  dtp.[Value], \r\n" +
            "  dp.[Value], \r\n" +
            "  gp.[Value], \r\n" +
            "  i16p.[Value], \r\n" +
            "  i32p.[Value], \r\n" +
            "  i64p.[Value], \r\n" +
            "  rp.[Value], \r\n" +
            "  sp.[Value], \r\n" +
            "  sip.[Value], \r\n" +
            "  stp.[Value], \r\n" +
            "  btp.[Timeseries], \r\n" +
            "  botp.[Timeseries], \r\n" +
            "  bytp.[Timeseries], \r\n" +
            "  dttp.[Timeseries], \r\n" +
            "  dotp.[Timeseries], \r\n" +
            "  gtp.[Timeseries], \r\n" +
            "  i16tp.[Timeseries], \r\n" +
            "  i32tp.[Timeseries], \r\n" +
            "  i64tp.[Timeseries], \r\n" +
            "  rtp.[Timeseries], \r\n" +
            "  sbtp.[Timeseries], \r\n" +
            "  sitp.[Timeseries], \r\n" +
            "  sttp.[Timeseries], \r\n" +
            "  tstp.[Timeseries], \r\n" +
            "  u16tp.[Timeseries], \r\n" +
            "  u32tp.[Timeseries], \r\n" +
            "  u64tp.[Timeseries], \r\n" +
            "  tsp.[Value], \r\n" +
            "  u16p.[Value], \r\n" +
            "  u32p.[Value], \r\n" +
            "  u64p.[Value], \r\n" +
            "  bp.[Value] \r\n" +
            "FROM [PropertyView] p \r\n" +
            "  LEFT JOIN [BinaryProperty] bp ON(p.[Id] = bp.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanProperty] bop ON(p.[Id] = bop.[Id] ) \r\n" +
            "  LEFT JOIN [ByteProperty] byp ON(p.[Id] = byp.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeProperty] dtp ON(p.[Id] = dtp.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleProperty] dp ON(p.[Id] = dp.[Id] ) \r\n" +
            "  LEFT JOIN [GuidProperty] gp ON(p.[Id] = gp.[Id] ) \r\n" +
            "  LEFT JOIN [Int16Property] i16p ON(p.[Id] = i16p.[Id] ) \r\n" +
            "  LEFT JOIN [Int32Property] i32p ON(p.[Id] = i32p.[Id] ) \r\n" +
            "  LEFT JOIN [Int64Property] i64p ON(p.[Id] = i64p.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceProperty] rp ON(p.[Id] = rp.[Id] ) \r\n" +
            "  LEFT JOIN [SByteProperty] sp ON(p.[Id] = sp.[Id] ) \r\n" +
            "  LEFT JOIN [SingleProperty] sip ON(p.[Id] = sip.[Id] ) \r\n" +
            "  LEFT JOIN [StringProperty] stp ON(p.[Id] = stp.[Id] ) \r\n" +
            "  LEFT JOIN [TimeseriesProperty] tp ON(p.[Id] = tp.[Id] ) \r\n" +
            "  LEFT JOIN [BinaryTimeseriesProperty] btp ON(p.[Id] = btp.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseriesProperty] botp ON(p.[Id] = botp.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseriesProperty] bytp ON(p.[Id] = bytp.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseriesProperty] dttp ON(p.[Id] = dttp.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseriesProperty] dotp ON(p.[Id] = dotp.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseriesProperty] gtp ON(p.[Id] = gtp.[Id] ) \r\n" +
            "  LEFT JOIN [Int16TimeseriesProperty] i16tp ON(p.[Id] = i16tp.[Id] ) \r\n" +
            "  LEFT JOIN [Int32TimeseriesProperty] i32tp ON(p.[Id] = i32tp.[Id] ) \r\n" +
            "  LEFT JOIN [Int64TimeseriesProperty] i64tp ON(p.[Id] = i64tp.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseriesProperty] rtp ON(p.[Id] = rtp.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseriesProperty] sbtp ON(p.[Id] = sbtp.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseriesProperty] sitp ON(p.[Id] = sitp.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseriesProperty] sttp ON(p.[Id] = sttp.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseriesProperty] tstp ON(p.[Id] = tstp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16TimeseriesProperty] u16tp ON(p.[Id] = u16tp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32TimeseriesProperty] u32tp ON(p.[Id] = u32tp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64TimeseriesProperty] u64tp ON(p.[Id] = u64tp.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanProperty] tsp ON(p.[Id] = tsp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16Property] u16p ON(p.[Id] = u16p.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32Property] u32p ON(p.[Id] = u32p.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64Property] u64p ON(p.[Id] = u64p.[Id] ) \r\n";

        public const string BaseViewName = "PropertyView";
        public const string ViewAliasName = "p";

        public const int P_ID_FIELD_ID = 0;
        public const int P_KIND_FIELD_ID = 1;
        public const int P_ROWVERSION_FIELD_ID = 2;
        public const int P_ELEMENT_FIELD_ID = 3;
        public const int P_DEFINITION_FIELD_ID = 4;
        public const int BOP_VALUE_FIELD_ID = 5;
        public const int BYP_VALUE_FIELD_ID = 6;
        public const int DTP_VALUE_FIELD_ID = 7;
        public const int DP_VALUE_FIELD_ID = 8;
        public const int GP_VALUE_FIELD_ID = 9;
        public const int I16P_VALUE_FIELD_ID = 10;
        public const int I32P_VALUE_FIELD_ID = 11;
        public const int I64P_VALUE_FIELD_ID = 12;
        public const int RP_VALUE_FIELD_ID = 13;
        public const int SP_VALUE_FIELD_ID = 14;
        public const int SIP_VALUE_FIELD_ID = 15;
        public const int STP_VALUE_FIELD_ID = 16;
        public const int BTP_TIMESERIES_FIELD_ID = 17;
        public const int BOTP_TIMESERIES_FIELD_ID = 18;
        public const int BYTP_TIMESERIES_FIELD_ID = 19;
        public const int DTTP_TIMESERIES_FIELD_ID = 20;
        public const int DOTP_TIMESERIES_FIELD_ID = 21;
        public const int GTP_TIMESERIES_FIELD_ID = 22;
        public const int I16TP_TIMESERIES_FIELD_ID = 23;
        public const int I32TP_TIMESERIES_FIELD_ID = 24;
        public const int I64TP_TIMESERIES_FIELD_ID = 25;
        public const int RTP_TIMESERIES_FIELD_ID = 26;
        public const int SBTP_TIMESERIES_FIELD_ID = 27;
        public const int SITP_TIMESERIES_FIELD_ID = 28;
        public const int STTP_TIMESERIES_FIELD_ID = 29;
        public const int TSTP_TIMESERIES_FIELD_ID = 30;
        public const int U16TP_TIMESERIES_FIELD_ID = 31;
        public const int U32TP_TIMESERIES_FIELD_ID = 32;
        public const int U64TP_TIMESERIES_FIELD_ID = 33;
        public const int TSP_VALUE_FIELD_ID = 34;
        public const int U16P_VALUE_FIELD_ID = 35;
        public const int U32P_VALUE_FIELD_ID = 36;
        public const int U64P_VALUE_FIELD_ID = 37;
        public const int BP_VALUE_FIELD_ID = 38;
        public ComplexPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( P_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( P_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( P_ROWVERSION_FIELD_ID );
            }
        }
        public Guid Element
        {
            get
            {
                return GetGuid( P_ELEMENT_FIELD_ID );
            }
        }
        public Guid Definition
        {
            get
            {
                return GetGuid( P_DEFINITION_FIELD_ID );
            }
        }
        public byte[] BinaryPropertyValue
        {
            get
            {
                return GetBytes( BP_VALUE_FIELD_ID );
            }
        }
        public bool BooleanPropertyValue
        {
            get
            {
                return GetBoolean( BOP_VALUE_FIELD_ID );
            }
        }
        public byte BytePropertyValue
        {
            get
            {
                return GetByte( BYP_VALUE_FIELD_ID );
            }
        }
        public DateTime DateTimePropertyValue
        {
            get
            {
                return new DateTime( GetInt64( DTP_VALUE_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double DoublePropertyValue
        {
            get
            {
                return GetDouble( DP_VALUE_FIELD_ID );
            }
        }
        public Guid GuidPropertyValue
        {
            get
            {
                return GetGuid( GP_VALUE_FIELD_ID );
            }
        }
        public short Int16PropertyValue
        {
            get
            {
                return GetInt16( I16P_VALUE_FIELD_ID );
            }
        }
        public int Int32PropertyValue
        {
            get
            {
                return GetInt32( I32P_VALUE_FIELD_ID );
            }
        }
        public long Int64PropertyValue
        {
            get
            {
                return GetInt64( I64P_VALUE_FIELD_ID );
            }
        }
        public Guid? ReferencePropertyValue
        {
            get
            {
                return GetNullableGuid( RP_VALUE_FIELD_ID );
            }
        }
        public sbyte SBytePropertyValue
        {
            get
            {
                return GetSByte( SP_VALUE_FIELD_ID );
            }
        }
        public float SinglePropertyValue
        {
            get
            {
                return GetFloat( SIP_VALUE_FIELD_ID );
            }
        }
        public string StringPropertyValue
        {
            get
            {
                return GetString( STP_VALUE_FIELD_ID );
            }
        }
        public Guid? BinaryTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( BTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? BooleanTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( BOTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? ByteTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( BYTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? DateTimeTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( DTTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? DoubleTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( DOTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? GuidTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( GTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? Int16TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( I16TP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? Int32TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( I32TP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? Int64TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( I64TP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? ReferenceTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( RTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? SByteTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( SBTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? SingleTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( SITP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? StringTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( STTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? TimeSpanTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( TSTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? UInt16TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( U16TP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? UInt32TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( U32TP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? UInt64TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( U64TP_TIMESERIES_FIELD_ID );
            }
        }
        public TimeSpan TimeSpanPropertyValue
        {
            get
            {
                return new TimeSpan( GetInt64( TSP_VALUE_FIELD_ID ) );
            }
        }
        public ushort UInt16PropertyValue
        {
            get
            {
                return GetUInt16( U16P_VALUE_FIELD_ID );
            }
        }
        public uint UInt32PropertyValue
        {
            get
            {
                return GetUInt32( U32P_VALUE_FIELD_ID );
            }
        }
        public long UInt64PropertyValue
        {
            get
            {
                return GetInt64( U64P_VALUE_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.WriteArray( BinaryPropertyValue );
                }
                break;
                case Types.Kind.BooleanProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( BooleanPropertyValue );
                }
                break;
                case Types.Kind.ByteProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( BytePropertyValue );
                }
                break;
                case Types.Kind.DateTimeProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( DateTimePropertyValue );
                }
                break;
                case Types.Kind.DoubleProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( DoublePropertyValue );
                }
                break;
                case Types.Kind.GuidProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( GuidPropertyValue );
                }
                break;
                case Types.Kind.Int16Property:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( Int16PropertyValue );
                }
                break;
                case Types.Kind.Int32Property:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( Int32PropertyValue );
                }
                break;
                case Types.Kind.Int64Property:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( Int64PropertyValue );
                }
                break;
                case Types.Kind.ReferenceProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( ReferencePropertyValue );
                }
                break;
                case Types.Kind.SByteProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( SBytePropertyValue );
                }
                break;
                case Types.Kind.SingleProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( SinglePropertyValue );
                }
                break;
                case Types.Kind.StringProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( StringPropertyValue );
                }
                break;
                case Types.Kind.BinaryTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( BinaryTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.BooleanTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( BooleanTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.ByteTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( ByteTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.DateTimeTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( DateTimeTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.DoubleTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( DoubleTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.GuidTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( GuidTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.Int16TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( Int16TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.Int32TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( Int32TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.Int64TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( Int64TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.ReferenceTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( ReferenceTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.SByteTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( SByteTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.SingleTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( SingleTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.StringTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( StringTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.TimeSpanTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( TimeSpanTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.UInt16TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( UInt16TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.UInt32TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( UInt32TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.UInt64TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( UInt64TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.TimeSpanProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( TimeSpanPropertyValue );
                }
                break;
                case Types.Kind.UInt16Property:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( UInt16PropertyValue );
                }
                break;
                case Types.Kind.UInt32Property:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( UInt32PropertyValue );
                }
                break;
                case Types.Kind.UInt64Property:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( UInt64PropertyValue );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public PropertyObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryProperty:
                {
                    return new BinaryPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, BinaryPropertyValue );
                }
                case Types.Kind.BooleanProperty:
                {
                    return new BooleanPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, BooleanPropertyValue );
                }
                case Types.Kind.ByteProperty:
                {
                    return new BytePropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, BytePropertyValue );
                }
                case Types.Kind.DateTimeProperty:
                {
                    return new DateTimePropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, DateTimePropertyValue );
                }
                case Types.Kind.DoubleProperty:
                {
                    return new DoublePropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, DoublePropertyValue );
                }
                case Types.Kind.GuidProperty:
                {
                    return new GuidPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, GuidPropertyValue );
                }
                case Types.Kind.Int16Property:
                {
                    return new Int16PropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, Int16PropertyValue );
                }
                case Types.Kind.Int32Property:
                {
                    return new Int32PropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, Int32PropertyValue );
                }
                case Types.Kind.Int64Property:
                {
                    return new Int64PropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, Int64PropertyValue );
                }
                case Types.Kind.ReferenceProperty:
                {
                    return new ReferencePropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, ReferencePropertyValue );
                }
                case Types.Kind.SByteProperty:
                {
                    return new SBytePropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, SBytePropertyValue );
                }
                case Types.Kind.SingleProperty:
                {
                    return new SinglePropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, SinglePropertyValue );
                }
                case Types.Kind.StringProperty:
                {
                    return new StringPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, StringPropertyValue );
                }
                case Types.Kind.BinaryTimeseriesProperty:
                {
                    return new BinaryTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, BinaryTimeseriesPropertyTimeseries );
                }
                case Types.Kind.BooleanTimeseriesProperty:
                {
                    return new BooleanTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, BooleanTimeseriesPropertyTimeseries );
                }
                case Types.Kind.ByteTimeseriesProperty:
                {
                    return new ByteTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, ByteTimeseriesPropertyTimeseries );
                }
                case Types.Kind.DateTimeTimeseriesProperty:
                {
                    return new DateTimeTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, DateTimeTimeseriesPropertyTimeseries );
                }
                case Types.Kind.DoubleTimeseriesProperty:
                {
                    return new DoubleTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, DoubleTimeseriesPropertyTimeseries );
                }
                case Types.Kind.GuidTimeseriesProperty:
                {
                    return new GuidTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, GuidTimeseriesPropertyTimeseries );
                }
                case Types.Kind.Int16TimeseriesProperty:
                {
                    return new Int16TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, Int16TimeseriesPropertyTimeseries );
                }
                case Types.Kind.Int32TimeseriesProperty:
                {
                    return new Int32TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, Int32TimeseriesPropertyTimeseries );
                }
                case Types.Kind.Int64TimeseriesProperty:
                {
                    return new Int64TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, Int64TimeseriesPropertyTimeseries );
                }
                case Types.Kind.ReferenceTimeseriesProperty:
                {
                    return new ReferenceTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, ReferenceTimeseriesPropertyTimeseries );
                }
                case Types.Kind.SByteTimeseriesProperty:
                {
                    return new SByteTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, SByteTimeseriesPropertyTimeseries );
                }
                case Types.Kind.SingleTimeseriesProperty:
                {
                    return new SingleTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, SingleTimeseriesPropertyTimeseries );
                }
                case Types.Kind.StringTimeseriesProperty:
                {
                    return new StringTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, StringTimeseriesPropertyTimeseries );
                }
                case Types.Kind.TimeSpanTimeseriesProperty:
                {
                    return new TimeSpanTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, TimeSpanTimeseriesPropertyTimeseries );
                }
                case Types.Kind.UInt16TimeseriesProperty:
                {
                    return new UInt16TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, UInt16TimeseriesPropertyTimeseries );
                }
                case Types.Kind.UInt32TimeseriesProperty:
                {
                    return new UInt32TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, UInt32TimeseriesPropertyTimeseries );
                }
                case Types.Kind.UInt64TimeseriesProperty:
                {
                    return new UInt64TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, UInt64TimeseriesPropertyTimeseries );
                }
                case Types.Kind.TimeSpanProperty:
                {
                    return new TimeSpanPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, TimeSpanPropertyValue );
                }
                case Types.Kind.UInt16Property:
                {
                    return new UInt16PropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, UInt16PropertyValue );
                }
                case Types.Kind.UInt32Property:
                {
                    return new UInt32PropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, UInt32PropertyValue );
                }
                case Types.Kind.UInt64Property:
                {
                    return new UInt64PropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, UInt64PropertyValue );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexTimeseriesPropertyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tp.[Id], \r\n" +
            "  tp.[EntityType], \r\n" +
            "  tp.[RowVersion], \r\n" +
            "  tp.[Element], \r\n" +
            "  tp.[Definition], \r\n" +
            "  btp.[Timeseries], \r\n" +
            "  botp.[Timeseries], \r\n" +
            "  bytp.[Timeseries], \r\n" +
            "  dttp.[Timeseries], \r\n" +
            "  dotp.[Timeseries], \r\n" +
            "  gtp.[Timeseries], \r\n" +
            "  i16tp.[Timeseries], \r\n" +
            "  i32tp.[Timeseries], \r\n" +
            "  i64tp.[Timeseries], \r\n" +
            "  rtp.[Timeseries], \r\n" +
            "  sbtp.[Timeseries], \r\n" +
            "  sitp.[Timeseries], \r\n" +
            "  sttp.[Timeseries], \r\n" +
            "  tstp.[Timeseries], \r\n" +
            "  u16tp.[Timeseries], \r\n" +
            "  u32tp.[Timeseries], \r\n" +
            "  u64tp.[Timeseries] \r\n" +
            "FROM [TimeseriesPropertyView] tp \r\n" +
            "  LEFT JOIN [BinaryTimeseriesProperty] btp ON(tp.[Id] = btp.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseriesProperty] botp ON(tp.[Id] = botp.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseriesProperty] bytp ON(tp.[Id] = bytp.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseriesProperty] dttp ON(tp.[Id] = dttp.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseriesProperty] dotp ON(tp.[Id] = dotp.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseriesProperty] gtp ON(tp.[Id] = gtp.[Id] ) \r\n" +
            "  LEFT JOIN [Int16TimeseriesProperty] i16tp ON(tp.[Id] = i16tp.[Id] ) \r\n" +
            "  LEFT JOIN [Int32TimeseriesProperty] i32tp ON(tp.[Id] = i32tp.[Id] ) \r\n" +
            "  LEFT JOIN [Int64TimeseriesProperty] i64tp ON(tp.[Id] = i64tp.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseriesProperty] rtp ON(tp.[Id] = rtp.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseriesProperty] sbtp ON(tp.[Id] = sbtp.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseriesProperty] sitp ON(tp.[Id] = sitp.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseriesProperty] sttp ON(tp.[Id] = sttp.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseriesProperty] tstp ON(tp.[Id] = tstp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16TimeseriesProperty] u16tp ON(tp.[Id] = u16tp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32TimeseriesProperty] u32tp ON(tp.[Id] = u32tp.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64TimeseriesProperty] u64tp ON(tp.[Id] = u64tp.[Id] ) \r\n";

        public const string BaseViewName = "TimeseriesPropertyView";
        public const string ViewAliasName = "tp";

        public const int TP_ID_FIELD_ID = 0;
        public const int TP_KIND_FIELD_ID = 1;
        public const int TP_ROWVERSION_FIELD_ID = 2;
        public const int TP_ELEMENT_FIELD_ID = 3;
        public const int TP_DEFINITION_FIELD_ID = 4;
        public const int BTP_TIMESERIES_FIELD_ID = 5;
        public const int BOTP_TIMESERIES_FIELD_ID = 6;
        public const int BYTP_TIMESERIES_FIELD_ID = 7;
        public const int DTTP_TIMESERIES_FIELD_ID = 8;
        public const int DOTP_TIMESERIES_FIELD_ID = 9;
        public const int GTP_TIMESERIES_FIELD_ID = 10;
        public const int I16TP_TIMESERIES_FIELD_ID = 11;
        public const int I32TP_TIMESERIES_FIELD_ID = 12;
        public const int I64TP_TIMESERIES_FIELD_ID = 13;
        public const int RTP_TIMESERIES_FIELD_ID = 14;
        public const int SBTP_TIMESERIES_FIELD_ID = 15;
        public const int SITP_TIMESERIES_FIELD_ID = 16;
        public const int STTP_TIMESERIES_FIELD_ID = 17;
        public const int TSTP_TIMESERIES_FIELD_ID = 18;
        public const int U16TP_TIMESERIES_FIELD_ID = 19;
        public const int U32TP_TIMESERIES_FIELD_ID = 20;
        public const int U64TP_TIMESERIES_FIELD_ID = 21;
        public ComplexTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( TP_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( TP_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( TP_ROWVERSION_FIELD_ID );
            }
        }
        public Guid Element
        {
            get
            {
                return GetGuid( TP_ELEMENT_FIELD_ID );
            }
        }
        public Guid Definition
        {
            get
            {
                return GetGuid( TP_DEFINITION_FIELD_ID );
            }
        }
        public Guid? BinaryTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( BTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? BooleanTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( BOTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? ByteTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( BYTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? DateTimeTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( DTTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? DoubleTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( DOTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? GuidTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( GTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? Int16TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( I16TP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? Int32TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( I32TP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? Int64TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( I64TP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? ReferenceTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( RTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? SByteTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( SBTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? SingleTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( SITP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? StringTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( STTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? TimeSpanTimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( TSTP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? UInt16TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( U16TP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? UInt32TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( U32TP_TIMESERIES_FIELD_ID );
            }
        }
        public Guid? UInt64TimeseriesPropertyTimeseries
        {
            get
            {
                return GetNullableGuid( U64TP_TIMESERIES_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( BinaryTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.BooleanTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( BooleanTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.ByteTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( ByteTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.DateTimeTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( DateTimeTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.DoubleTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( DoubleTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.GuidTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( GuidTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.Int16TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( Int16TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.Int32TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( Int32TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.Int64TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( Int64TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.ReferenceTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( ReferenceTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.SByteTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( SByteTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.SingleTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( SingleTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.StringTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( StringTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.TimeSpanTimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( TimeSpanTimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.UInt16TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( UInt16TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.UInt32TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( UInt32TimeseriesPropertyTimeseries );
                }
                break;
                case Types.Kind.UInt64TimeseriesProperty:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Element );
                    destination.Write( Definition );
                    destination.Write( UInt64TimeseriesPropertyTimeseries );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public TimeseriesPropertyObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryTimeseriesProperty:
                {
                    return new BinaryTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, BinaryTimeseriesPropertyTimeseries );
                }
                case Types.Kind.BooleanTimeseriesProperty:
                {
                    return new BooleanTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, BooleanTimeseriesPropertyTimeseries );
                }
                case Types.Kind.ByteTimeseriesProperty:
                {
                    return new ByteTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, ByteTimeseriesPropertyTimeseries );
                }
                case Types.Kind.DateTimeTimeseriesProperty:
                {
                    return new DateTimeTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, DateTimeTimeseriesPropertyTimeseries );
                }
                case Types.Kind.DoubleTimeseriesProperty:
                {
                    return new DoubleTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, DoubleTimeseriesPropertyTimeseries );
                }
                case Types.Kind.GuidTimeseriesProperty:
                {
                    return new GuidTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, GuidTimeseriesPropertyTimeseries );
                }
                case Types.Kind.Int16TimeseriesProperty:
                {
                    return new Int16TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, Int16TimeseriesPropertyTimeseries );
                }
                case Types.Kind.Int32TimeseriesProperty:
                {
                    return new Int32TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, Int32TimeseriesPropertyTimeseries );
                }
                case Types.Kind.Int64TimeseriesProperty:
                {
                    return new Int64TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, Int64TimeseriesPropertyTimeseries );
                }
                case Types.Kind.ReferenceTimeseriesProperty:
                {
                    return new ReferenceTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, ReferenceTimeseriesPropertyTimeseries );
                }
                case Types.Kind.SByteTimeseriesProperty:
                {
                    return new SByteTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, SByteTimeseriesPropertyTimeseries );
                }
                case Types.Kind.SingleTimeseriesProperty:
                {
                    return new SingleTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, SingleTimeseriesPropertyTimeseries );
                }
                case Types.Kind.StringTimeseriesProperty:
                {
                    return new StringTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, StringTimeseriesPropertyTimeseries );
                }
                case Types.Kind.TimeSpanTimeseriesProperty:
                {
                    return new TimeSpanTimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, TimeSpanTimeseriesPropertyTimeseries );
                }
                case Types.Kind.UInt16TimeseriesProperty:
                {
                    return new UInt16TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, UInt16TimeseriesPropertyTimeseries );
                }
                case Types.Kind.UInt32TimeseriesProperty:
                {
                    return new UInt32TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, UInt32TimeseriesPropertyTimeseries );
                }
                case Types.Kind.UInt64TimeseriesProperty:
                {
                    return new UInt64TimeseriesPropertyObject( ObjectState.Stored, Id, RowVersion, Element, Definition, UInt64TimeseriesPropertyTimeseries );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexPropertyDefinitionDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  pd.[Id], \r\n" +
            "  pd.[EntityType], \r\n" +
            "  pd.[RowVersion], \r\n" +
            "  pd.[ElementType], \r\n" +
            "  pd.[Name], \r\n" +
            "  bopd.[DefaultValue], \r\n" +
            "  bypd.[DefaultValue], \r\n" +
            "  bypd.[MinValue], \r\n" +
            "  bypd.[MaxValue], \r\n" +
            "  dtpd.[DefaultValue], \r\n" +
            "  dtpd.[MinValue], \r\n" +
            "  dtpd.[MaxValue], \r\n" +
            "  dpd.[DefaultValue], \r\n" +
            "  dpd.[MinValue], \r\n" +
            "  dpd.[MaxValue], \r\n" +
            "  gpd.[DefaultValue], \r\n" +
            "  i16pd.[DefaultValue], \r\n" +
            "  i16pd.[MinValue], \r\n" +
            "  i16pd.[MaxValue], \r\n" +
            "  i32pd.[DefaultValue], \r\n" +
            "  i32pd.[MinValue], \r\n" +
            "  i32pd.[MaxValue], \r\n" +
            "  i64pd.[DefaultValue], \r\n" +
            "  i64pd.[MinValue], \r\n" +
            "  i64pd.[MaxValue], \r\n" +
            "  rpd.[DefaultValue], \r\n" +
            "  rpd.[ReferencedElementType], \r\n" +
            "  sbpd.[DefaultValue], \r\n" +
            "  sbpd.[MinValue], \r\n" +
            "  sbpd.[MaxValue], \r\n" +
            "  sipd.[DefaultValue], \r\n" +
            "  sipd.[MinValue], \r\n" +
            "  sipd.[MaxValue], \r\n" +
            "  stpd.[DefaultValue], \r\n" +
            "  stpd.[Pattern], \r\n" +
            "  bytpd.[MinValue], \r\n" +
            "  bytpd.[MaxValue], \r\n" +
            "  dttpd.[MinValue], \r\n" +
            "  dttpd.[MaxValue], \r\n" +
            "  dotpd.[MinValue], \r\n" +
            "  dotpd.[MaxValue], \r\n" +
            "  i16tpd.[MinValue], \r\n" +
            "  i16tpd.[MaxValue], \r\n" +
            "  i32tpd.[MinValue], \r\n" +
            "  i32tpd.[MaxValue], \r\n" +
            "  i64tpd.[MinValue], \r\n" +
            "  i64tpd.[MaxValue], \r\n" +
            "  rtpd.[ReferencedElementType], \r\n" +
            "  sbtpd.[MinValue], \r\n" +
            "  sbtpd.[MaxValue], \r\n" +
            "  sitpd.[MinValue], \r\n" +
            "  sitpd.[MaxValue], \r\n" +
            "  sttpd.[Pattern], \r\n" +
            "  tstpd.[MinValue], \r\n" +
            "  tstpd.[MaxValue], \r\n" +
            "  u16tpd.[MinValue], \r\n" +
            "  u16tpd.[MaxValue], \r\n" +
            "  u32tpd.[MinValue], \r\n" +
            "  u32tpd.[MaxValue], \r\n" +
            "  u64tpd.[MinValue], \r\n" +
            "  u64tpd.[MaxValue], \r\n" +
            "  tspd.[DefaultValue], \r\n" +
            "  tspd.[MinValue], \r\n" +
            "  tspd.[MaxValue], \r\n" +
            "  u16pd.[DefaultValue], \r\n" +
            "  u16pd.[MinValue], \r\n" +
            "  u16pd.[MaxValue], \r\n" +
            "  u32pd.[DefaultValue], \r\n" +
            "  u32pd.[MinValue], \r\n" +
            "  u32pd.[MaxValue], \r\n" +
            "  u64pd.[DefaultValue], \r\n" +
            "  u64pd.[MinValue], \r\n" +
            "  u64pd.[MaxValue], \r\n" +
            "  pd.[Description], \r\n" +
            "  bpd.[DefaultValue] \r\n" +
            "FROM [PropertyDefinitionView] pd \r\n" +
            "  LEFT JOIN [BinaryPropertyDefinition] bpd ON(pd.[Id] = bpd.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanPropertyDefinition] bopd ON(pd.[Id] = bopd.[Id] ) \r\n" +
            "  LEFT JOIN [BytePropertyDefinition] bypd ON(pd.[Id] = bypd.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimePropertyDefinition] dtpd ON(pd.[Id] = dtpd.[Id] ) \r\n" +
            "  LEFT JOIN [DoublePropertyDefinition] dpd ON(pd.[Id] = dpd.[Id] ) \r\n" +
            "  LEFT JOIN [GuidPropertyDefinition] gpd ON(pd.[Id] = gpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int16PropertyDefinition] i16pd ON(pd.[Id] = i16pd.[Id] ) \r\n" +
            "  LEFT JOIN [Int32PropertyDefinition] i32pd ON(pd.[Id] = i32pd.[Id] ) \r\n" +
            "  LEFT JOIN [Int64PropertyDefinition] i64pd ON(pd.[Id] = i64pd.[Id] ) \r\n" +
            "  LEFT JOIN [ReferencePropertyDefinition] rpd ON(pd.[Id] = rpd.[Id] ) \r\n" +
            "  LEFT JOIN [SBytePropertyDefinition] sbpd ON(pd.[Id] = sbpd.[Id] ) \r\n" +
            "  LEFT JOIN [SinglePropertyDefinition] sipd ON(pd.[Id] = sipd.[Id] ) \r\n" +
            "  LEFT JOIN [StringPropertyDefinition] stpd ON(pd.[Id] = stpd.[Id] ) \r\n" +
            "  LEFT JOIN [TimeseriesPropertyDefinition] tpd ON(pd.[Id] = tpd.[Id] ) \r\n" +
            "  LEFT JOIN [BinaryTimeseriesPropertyDefinition] btpd ON(pd.[Id] = btpd.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseriesPropertyDefinition] botpd ON(pd.[Id] = botpd.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseriesPropertyDefinition] bytpd ON(pd.[Id] = bytpd.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseriesPropertyDefinition] dttpd ON(pd.[Id] = dttpd.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseriesPropertyDefinition] dotpd ON(pd.[Id] = dotpd.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseriesPropertyDefinition] gtpd ON(pd.[Id] = gtpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int16TimeseriesPropertyDefinition] i16tpd ON(pd.[Id] = i16tpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int32TimeseriesPropertyDefinition] i32tpd ON(pd.[Id] = i32tpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int64TimeseriesPropertyDefinition] i64tpd ON(pd.[Id] = i64tpd.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseriesPropertyDefinition] rtpd ON(pd.[Id] = rtpd.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseriesPropertyDefinition] sbtpd ON(pd.[Id] = sbtpd.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseriesPropertyDefinition] sitpd ON(pd.[Id] = sitpd.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseriesPropertyDefinition] sttpd ON(pd.[Id] = sttpd.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseriesPropertyDefinition] tstpd ON(pd.[Id] = tstpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16TimeseriesPropertyDefinition] u16tpd ON(pd.[Id] = u16tpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32TimeseriesPropertyDefinition] u32tpd ON(pd.[Id] = u32tpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64TimeseriesPropertyDefinition] u64tpd ON(pd.[Id] = u64tpd.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanPropertyDefinition] tspd ON(pd.[Id] = tspd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16PropertyDefinition] u16pd ON(pd.[Id] = u16pd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32PropertyDefinition] u32pd ON(pd.[Id] = u32pd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64PropertyDefinition] u64pd ON(pd.[Id] = u64pd.[Id] ) \r\n";

        public const string BaseViewName = "PropertyDefinitionView";
        public const string ViewAliasName = "pd";

        public const int PD_ID_FIELD_ID = 0;
        public const int PD_KIND_FIELD_ID = 1;
        public const int PD_ROWVERSION_FIELD_ID = 2;
        public const int PD_ELEMENTTYPE_FIELD_ID = 3;
        public const int PD_NAME_FIELD_ID = 4;
        public const int BOPD_DEFAULTVALUE_FIELD_ID = 5;
        public const int BYPD_DEFAULTVALUE_FIELD_ID = 6;
        public const int BYPD_MINVALUE_FIELD_ID = 7;
        public const int BYPD_MAXVALUE_FIELD_ID = 8;
        public const int DTPD_DEFAULTVALUE_FIELD_ID = 9;
        public const int DTPD_MINVALUE_FIELD_ID = 10;
        public const int DTPD_MAXVALUE_FIELD_ID = 11;
        public const int DPD_DEFAULTVALUE_FIELD_ID = 12;
        public const int DPD_MINVALUE_FIELD_ID = 13;
        public const int DPD_MAXVALUE_FIELD_ID = 14;
        public const int GPD_DEFAULTVALUE_FIELD_ID = 15;
        public const int I16PD_DEFAULTVALUE_FIELD_ID = 16;
        public const int I16PD_MINVALUE_FIELD_ID = 17;
        public const int I16PD_MAXVALUE_FIELD_ID = 18;
        public const int I32PD_DEFAULTVALUE_FIELD_ID = 19;
        public const int I32PD_MINVALUE_FIELD_ID = 20;
        public const int I32PD_MAXVALUE_FIELD_ID = 21;
        public const int I64PD_DEFAULTVALUE_FIELD_ID = 22;
        public const int I64PD_MINVALUE_FIELD_ID = 23;
        public const int I64PD_MAXVALUE_FIELD_ID = 24;
        public const int RPD_DEFAULTVALUE_FIELD_ID = 25;
        public const int RPD_REFERENCEDELEMENTTYPE_FIELD_ID = 26;
        public const int SBPD_DEFAULTVALUE_FIELD_ID = 27;
        public const int SBPD_MINVALUE_FIELD_ID = 28;
        public const int SBPD_MAXVALUE_FIELD_ID = 29;
        public const int SIPD_DEFAULTVALUE_FIELD_ID = 30;
        public const int SIPD_MINVALUE_FIELD_ID = 31;
        public const int SIPD_MAXVALUE_FIELD_ID = 32;
        public const int STPD_DEFAULTVALUE_FIELD_ID = 33;
        public const int STPD_PATTERN_FIELD_ID = 34;
        public const int BYTPD_MINVALUE_FIELD_ID = 35;
        public const int BYTPD_MAXVALUE_FIELD_ID = 36;
        public const int DTTPD_MINVALUE_FIELD_ID = 37;
        public const int DTTPD_MAXVALUE_FIELD_ID = 38;
        public const int DOTPD_MINVALUE_FIELD_ID = 39;
        public const int DOTPD_MAXVALUE_FIELD_ID = 40;
        public const int I16TPD_MINVALUE_FIELD_ID = 41;
        public const int I16TPD_MAXVALUE_FIELD_ID = 42;
        public const int I32TPD_MINVALUE_FIELD_ID = 43;
        public const int I32TPD_MAXVALUE_FIELD_ID = 44;
        public const int I64TPD_MINVALUE_FIELD_ID = 45;
        public const int I64TPD_MAXVALUE_FIELD_ID = 46;
        public const int RTPD_REFERENCEDELEMENTTYPE_FIELD_ID = 47;
        public const int SBTPD_MINVALUE_FIELD_ID = 48;
        public const int SBTPD_MAXVALUE_FIELD_ID = 49;
        public const int SITPD_MINVALUE_FIELD_ID = 50;
        public const int SITPD_MAXVALUE_FIELD_ID = 51;
        public const int STTPD_PATTERN_FIELD_ID = 52;
        public const int TSTPD_MINVALUE_FIELD_ID = 53;
        public const int TSTPD_MAXVALUE_FIELD_ID = 54;
        public const int U16TPD_MINVALUE_FIELD_ID = 55;
        public const int U16TPD_MAXVALUE_FIELD_ID = 56;
        public const int U32TPD_MINVALUE_FIELD_ID = 57;
        public const int U32TPD_MAXVALUE_FIELD_ID = 58;
        public const int U64TPD_MINVALUE_FIELD_ID = 59;
        public const int U64TPD_MAXVALUE_FIELD_ID = 60;
        public const int TSPD_DEFAULTVALUE_FIELD_ID = 61;
        public const int TSPD_MINVALUE_FIELD_ID = 62;
        public const int TSPD_MAXVALUE_FIELD_ID = 63;
        public const int U16PD_DEFAULTVALUE_FIELD_ID = 64;
        public const int U16PD_MINVALUE_FIELD_ID = 65;
        public const int U16PD_MAXVALUE_FIELD_ID = 66;
        public const int U32PD_DEFAULTVALUE_FIELD_ID = 67;
        public const int U32PD_MINVALUE_FIELD_ID = 68;
        public const int U32PD_MAXVALUE_FIELD_ID = 69;
        public const int U64PD_DEFAULTVALUE_FIELD_ID = 70;
        public const int U64PD_MINVALUE_FIELD_ID = 71;
        public const int U64PD_MAXVALUE_FIELD_ID = 72;
        public const int PD_DESCRIPTION_FIELD_ID = 73;
        public const int BPD_DEFAULTVALUE_FIELD_ID = 74;
        public ComplexPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( PD_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( PD_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( PD_ROWVERSION_FIELD_ID );
            }
        }
        public Guid ElementType
        {
            get
            {
                return GetGuid( PD_ELEMENTTYPE_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( PD_NAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( PD_DESCRIPTION_FIELD_ID );
            }
        }
        public byte[] BinaryPropertyDefinitionDefaultValue
        {
            get
            {
                return GetBytes( BPD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public bool BooleanPropertyDefinitionDefaultValue
        {
            get
            {
                return GetBoolean( BOPD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public byte BytePropertyDefinitionDefaultValue
        {
            get
            {
                return GetByte( BYPD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public byte BytePropertyDefinitionMinValue
        {
            get
            {
                return GetByte( BYPD_MINVALUE_FIELD_ID );
            }
        }
        public byte BytePropertyDefinitionMaxValue
        {
            get
            {
                return GetByte( BYPD_MAXVALUE_FIELD_ID );
            }
        }
        public string DateTimePropertyDefinitionDefaultValue
        {
            get
            {
                return GetString( DTPD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public string DateTimePropertyDefinitionMinValue
        {
            get
            {
                return GetString( DTPD_MINVALUE_FIELD_ID );
            }
        }
        public string DateTimePropertyDefinitionMaxValue
        {
            get
            {
                return GetString( DTPD_MAXVALUE_FIELD_ID );
            }
        }
        public double DoublePropertyDefinitionDefaultValue
        {
            get
            {
                return GetDouble( DPD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public double DoublePropertyDefinitionMinValue
        {
            get
            {
                return GetDouble( DPD_MINVALUE_FIELD_ID );
            }
        }
        public double DoublePropertyDefinitionMaxValue
        {
            get
            {
                return GetDouble( DPD_MAXVALUE_FIELD_ID );
            }
        }
        public Guid GuidPropertyDefinitionDefaultValue
        {
            get
            {
                return GetGuid( GPD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public short Int16PropertyDefinitionDefaultValue
        {
            get
            {
                return GetInt16( I16PD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public short Int16PropertyDefinitionMinValue
        {
            get
            {
                return GetInt16( I16PD_MINVALUE_FIELD_ID );
            }
        }
        public short Int16PropertyDefinitionMaxValue
        {
            get
            {
                return GetInt16( I16PD_MAXVALUE_FIELD_ID );
            }
        }
        public int Int32PropertyDefinitionDefaultValue
        {
            get
            {
                return GetInt32( I32PD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public int Int32PropertyDefinitionMinValue
        {
            get
            {
                return GetInt32( I32PD_MINVALUE_FIELD_ID );
            }
        }
        public int Int32PropertyDefinitionMaxValue
        {
            get
            {
                return GetInt32( I32PD_MAXVALUE_FIELD_ID );
            }
        }
        public long Int64PropertyDefinitionDefaultValue
        {
            get
            {
                return GetInt64( I64PD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public long Int64PropertyDefinitionMinValue
        {
            get
            {
                return GetInt64( I64PD_MINVALUE_FIELD_ID );
            }
        }
        public long Int64PropertyDefinitionMaxValue
        {
            get
            {
                return GetInt64( I64PD_MAXVALUE_FIELD_ID );
            }
        }
        public Guid? ReferencePropertyDefinitionDefaultValue
        {
            get
            {
                return GetNullableGuid( RPD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public Guid? ReferencePropertyDefinitionReferencedElementType
        {
            get
            {
                return GetNullableGuid( RPD_REFERENCEDELEMENTTYPE_FIELD_ID );
            }
        }
        public sbyte SBytePropertyDefinitionDefaultValue
        {
            get
            {
                return GetSByte( SBPD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public sbyte SBytePropertyDefinitionMinValue
        {
            get
            {
                return GetSByte( SBPD_MINVALUE_FIELD_ID );
            }
        }
        public sbyte SBytePropertyDefinitionMaxValue
        {
            get
            {
                return GetSByte( SBPD_MAXVALUE_FIELD_ID );
            }
        }
        public float SinglePropertyDefinitionDefaultValue
        {
            get
            {
                return GetFloat( SIPD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public float SinglePropertyDefinitionMinValue
        {
            get
            {
                return GetFloat( SIPD_MINVALUE_FIELD_ID );
            }
        }
        public float SinglePropertyDefinitionMaxValue
        {
            get
            {
                return GetFloat( SIPD_MAXVALUE_FIELD_ID );
            }
        }
        public string StringPropertyDefinitionDefaultValue
        {
            get
            {
                return GetString( STPD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public string StringPropertyDefinitionPattern
        {
            get
            {
                return GetString( STPD_PATTERN_FIELD_ID );
            }
        }
        public byte ByteTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetByte( BYTPD_MINVALUE_FIELD_ID );
            }
        }
        public byte ByteTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetByte( BYTPD_MAXVALUE_FIELD_ID );
            }
        }
        public string DateTimeTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetString( DTTPD_MINVALUE_FIELD_ID );
            }
        }
        public string DateTimeTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetString( DTTPD_MAXVALUE_FIELD_ID );
            }
        }
        public double DoubleTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetDouble( DOTPD_MINVALUE_FIELD_ID );
            }
        }
        public double DoubleTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetDouble( DOTPD_MAXVALUE_FIELD_ID );
            }
        }
        public short Int16TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetInt16( I16TPD_MINVALUE_FIELD_ID );
            }
        }
        public short Int16TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetInt16( I16TPD_MAXVALUE_FIELD_ID );
            }
        }
        public int Int32TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetInt32( I32TPD_MINVALUE_FIELD_ID );
            }
        }
        public int Int32TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetInt32( I32TPD_MAXVALUE_FIELD_ID );
            }
        }
        public long Int64TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetInt64( I64TPD_MINVALUE_FIELD_ID );
            }
        }
        public long Int64TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetInt64( I64TPD_MAXVALUE_FIELD_ID );
            }
        }
        public Guid? ReferenceTimeseriesPropertyDefinitionReferencedElementType
        {
            get
            {
                return GetNullableGuid( RTPD_REFERENCEDELEMENTTYPE_FIELD_ID );
            }
        }
        public sbyte SByteTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetSByte( SBTPD_MINVALUE_FIELD_ID );
            }
        }
        public sbyte SByteTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetSByte( SBTPD_MAXVALUE_FIELD_ID );
            }
        }
        public float SingleTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetFloat( SITPD_MINVALUE_FIELD_ID );
            }
        }
        public float SingleTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetFloat( SITPD_MAXVALUE_FIELD_ID );
            }
        }
        public string StringTimeseriesPropertyDefinitionPattern
        {
            get
            {
                return GetString( STTPD_PATTERN_FIELD_ID );
            }
        }
        public TimeSpan TimeSpanTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return new TimeSpan( GetInt64( TSTPD_MINVALUE_FIELD_ID ) );
            }
        }
        public TimeSpan TimeSpanTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return new TimeSpan( GetInt64( TSTPD_MAXVALUE_FIELD_ID ) );
            }
        }
        public ushort UInt16TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetUInt16( U16TPD_MINVALUE_FIELD_ID );
            }
        }
        public ushort UInt16TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetUInt16( U16TPD_MAXVALUE_FIELD_ID );
            }
        }
        public uint UInt32TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetUInt32( U32TPD_MINVALUE_FIELD_ID );
            }
        }
        public uint UInt32TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetUInt32( U32TPD_MAXVALUE_FIELD_ID );
            }
        }
        public long UInt64TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetInt64( U64TPD_MINVALUE_FIELD_ID );
            }
        }
        public long UInt64TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetInt64( U64TPD_MAXVALUE_FIELD_ID );
            }
        }
        public TimeSpan TimeSpanPropertyDefinitionDefaultValue
        {
            get
            {
                return new TimeSpan( GetInt64( TSPD_DEFAULTVALUE_FIELD_ID ) );
            }
        }
        public TimeSpan TimeSpanPropertyDefinitionMinValue
        {
            get
            {
                return new TimeSpan( GetInt64( TSPD_MINVALUE_FIELD_ID ) );
            }
        }
        public TimeSpan TimeSpanPropertyDefinitionMaxValue
        {
            get
            {
                return new TimeSpan( GetInt64( TSPD_MAXVALUE_FIELD_ID ) );
            }
        }
        public ushort UInt16PropertyDefinitionDefaultValue
        {
            get
            {
                return GetUInt16( U16PD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public ushort UInt16PropertyDefinitionMinValue
        {
            get
            {
                return GetUInt16( U16PD_MINVALUE_FIELD_ID );
            }
        }
        public ushort UInt16PropertyDefinitionMaxValue
        {
            get
            {
                return GetUInt16( U16PD_MAXVALUE_FIELD_ID );
            }
        }
        public uint UInt32PropertyDefinitionDefaultValue
        {
            get
            {
                return GetUInt32( U32PD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public uint UInt32PropertyDefinitionMinValue
        {
            get
            {
                return GetUInt32( U32PD_MINVALUE_FIELD_ID );
            }
        }
        public uint UInt32PropertyDefinitionMaxValue
        {
            get
            {
                return GetUInt32( U32PD_MAXVALUE_FIELD_ID );
            }
        }
        public long UInt64PropertyDefinitionDefaultValue
        {
            get
            {
                return GetInt64( U64PD_DEFAULTVALUE_FIELD_ID );
            }
        }
        public long UInt64PropertyDefinitionMinValue
        {
            get
            {
                return GetInt64( U64PD_MINVALUE_FIELD_ID );
            }
        }
        public long UInt64PropertyDefinitionMaxValue
        {
            get
            {
                return GetInt64( U64PD_MAXVALUE_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.WriteArray( BinaryPropertyDefinitionDefaultValue );
                }
                break;
                case Types.Kind.BooleanPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( BooleanPropertyDefinitionDefaultValue );
                }
                break;
                case Types.Kind.BytePropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( BytePropertyDefinitionDefaultValue );
                    destination.Write( BytePropertyDefinitionMinValue );
                    destination.Write( BytePropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.DateTimePropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( DateTimePropertyDefinitionDefaultValue );
                    destination.Write( DateTimePropertyDefinitionMinValue );
                    destination.Write( DateTimePropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.DoublePropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( DoublePropertyDefinitionDefaultValue );
                    destination.Write( DoublePropertyDefinitionMinValue );
                    destination.Write( DoublePropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.GuidPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( GuidPropertyDefinitionDefaultValue );
                }
                break;
                case Types.Kind.Int16PropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( Int16PropertyDefinitionDefaultValue );
                    destination.Write( Int16PropertyDefinitionMinValue );
                    destination.Write( Int16PropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.Int32PropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( Int32PropertyDefinitionDefaultValue );
                    destination.Write( Int32PropertyDefinitionMinValue );
                    destination.Write( Int32PropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.Int64PropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( Int64PropertyDefinitionDefaultValue );
                    destination.Write( Int64PropertyDefinitionMinValue );
                    destination.Write( Int64PropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.ReferencePropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( ReferencePropertyDefinitionDefaultValue );
                    destination.Write( ReferencePropertyDefinitionReferencedElementType );
                }
                break;
                case Types.Kind.SBytePropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( SBytePropertyDefinitionDefaultValue );
                    destination.Write( SBytePropertyDefinitionMinValue );
                    destination.Write( SBytePropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.SinglePropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( SinglePropertyDefinitionDefaultValue );
                    destination.Write( SinglePropertyDefinitionMinValue );
                    destination.Write( SinglePropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.StringPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( StringPropertyDefinitionDefaultValue );
                    destination.Write( StringPropertyDefinitionPattern );
                }
                break;
                case Types.Kind.BinaryTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                }
                break;
                case Types.Kind.BooleanTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                }
                break;
                case Types.Kind.ByteTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( ByteTimeseriesPropertyDefinitionMinValue );
                    destination.Write( ByteTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.DateTimeTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( DateTimeTimeseriesPropertyDefinitionMinValue );
                    destination.Write( DateTimeTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.DoubleTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( DoubleTimeseriesPropertyDefinitionMinValue );
                    destination.Write( DoubleTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.GuidTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                }
                break;
                case Types.Kind.Int16TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( Int16TimeseriesPropertyDefinitionMinValue );
                    destination.Write( Int16TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.Int32TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( Int32TimeseriesPropertyDefinitionMinValue );
                    destination.Write( Int32TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.Int64TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( Int64TimeseriesPropertyDefinitionMinValue );
                    destination.Write( Int64TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.ReferenceTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( ReferenceTimeseriesPropertyDefinitionReferencedElementType );
                }
                break;
                case Types.Kind.SByteTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( SByteTimeseriesPropertyDefinitionMinValue );
                    destination.Write( SByteTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.SingleTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( SingleTimeseriesPropertyDefinitionMinValue );
                    destination.Write( SingleTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.StringTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( StringTimeseriesPropertyDefinitionPattern );
                }
                break;
                case Types.Kind.TimeSpanTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( TimeSpanTimeseriesPropertyDefinitionMinValue );
                    destination.Write( TimeSpanTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.UInt16TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( UInt16TimeseriesPropertyDefinitionMinValue );
                    destination.Write( UInt16TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.UInt32TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( UInt32TimeseriesPropertyDefinitionMinValue );
                    destination.Write( UInt32TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.UInt64TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( UInt64TimeseriesPropertyDefinitionMinValue );
                    destination.Write( UInt64TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.TimeSpanPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( TimeSpanPropertyDefinitionDefaultValue );
                    destination.Write( TimeSpanPropertyDefinitionMinValue );
                    destination.Write( TimeSpanPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.UInt16PropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( UInt16PropertyDefinitionDefaultValue );
                    destination.Write( UInt16PropertyDefinitionMinValue );
                    destination.Write( UInt16PropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.UInt32PropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( UInt32PropertyDefinitionDefaultValue );
                    destination.Write( UInt32PropertyDefinitionMinValue );
                    destination.Write( UInt32PropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.UInt64PropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( UInt64PropertyDefinitionDefaultValue );
                    destination.Write( UInt64PropertyDefinitionMinValue );
                    destination.Write( UInt64PropertyDefinitionMaxValue );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public PropertyDefinitionObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryPropertyDefinition:
                {
                    return new BinaryPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, BinaryPropertyDefinitionDefaultValue );
                }
                case Types.Kind.BooleanPropertyDefinition:
                {
                    return new BooleanPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, BooleanPropertyDefinitionDefaultValue );
                }
                case Types.Kind.BytePropertyDefinition:
                {
                    return new BytePropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, BytePropertyDefinitionDefaultValue, BytePropertyDefinitionMinValue, BytePropertyDefinitionMaxValue );
                }
                case Types.Kind.DateTimePropertyDefinition:
                {
                    return new DateTimePropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, DateTimePropertyDefinitionDefaultValue, DateTimePropertyDefinitionMinValue, DateTimePropertyDefinitionMaxValue );
                }
                case Types.Kind.DoublePropertyDefinition:
                {
                    return new DoublePropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, DoublePropertyDefinitionDefaultValue, DoublePropertyDefinitionMinValue, DoublePropertyDefinitionMaxValue );
                }
                case Types.Kind.GuidPropertyDefinition:
                {
                    return new GuidPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, GuidPropertyDefinitionDefaultValue );
                }
                case Types.Kind.Int16PropertyDefinition:
                {
                    return new Int16PropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, Int16PropertyDefinitionDefaultValue, Int16PropertyDefinitionMinValue, Int16PropertyDefinitionMaxValue );
                }
                case Types.Kind.Int32PropertyDefinition:
                {
                    return new Int32PropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, Int32PropertyDefinitionDefaultValue, Int32PropertyDefinitionMinValue, Int32PropertyDefinitionMaxValue );
                }
                case Types.Kind.Int64PropertyDefinition:
                {
                    return new Int64PropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, Int64PropertyDefinitionDefaultValue, Int64PropertyDefinitionMinValue, Int64PropertyDefinitionMaxValue );
                }
                case Types.Kind.ReferencePropertyDefinition:
                {
                    return new ReferencePropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, ReferencePropertyDefinitionDefaultValue, ReferencePropertyDefinitionReferencedElementType );
                }
                case Types.Kind.SBytePropertyDefinition:
                {
                    return new SBytePropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, SBytePropertyDefinitionDefaultValue, SBytePropertyDefinitionMinValue, SBytePropertyDefinitionMaxValue );
                }
                case Types.Kind.SinglePropertyDefinition:
                {
                    return new SinglePropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, SinglePropertyDefinitionDefaultValue, SinglePropertyDefinitionMinValue, SinglePropertyDefinitionMaxValue );
                }
                case Types.Kind.StringPropertyDefinition:
                {
                    return new StringPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, StringPropertyDefinitionDefaultValue, StringPropertyDefinitionPattern );
                }
                case Types.Kind.BinaryTimeseriesPropertyDefinition:
                {
                    return new BinaryTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description );
                }
                case Types.Kind.BooleanTimeseriesPropertyDefinition:
                {
                    return new BooleanTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description );
                }
                case Types.Kind.ByteTimeseriesPropertyDefinition:
                {
                    return new ByteTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, ByteTimeseriesPropertyDefinitionMinValue, ByteTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.DateTimeTimeseriesPropertyDefinition:
                {
                    return new DateTimeTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, DateTimeTimeseriesPropertyDefinitionMinValue, DateTimeTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.DoubleTimeseriesPropertyDefinition:
                {
                    return new DoubleTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, DoubleTimeseriesPropertyDefinitionMinValue, DoubleTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.GuidTimeseriesPropertyDefinition:
                {
                    return new GuidTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description );
                }
                case Types.Kind.Int16TimeseriesPropertyDefinition:
                {
                    return new Int16TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, Int16TimeseriesPropertyDefinitionMinValue, Int16TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.Int32TimeseriesPropertyDefinition:
                {
                    return new Int32TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, Int32TimeseriesPropertyDefinitionMinValue, Int32TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.Int64TimeseriesPropertyDefinition:
                {
                    return new Int64TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, Int64TimeseriesPropertyDefinitionMinValue, Int64TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.ReferenceTimeseriesPropertyDefinition:
                {
                    return new ReferenceTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, ReferenceTimeseriesPropertyDefinitionReferencedElementType );
                }
                case Types.Kind.SByteTimeseriesPropertyDefinition:
                {
                    return new SByteTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, SByteTimeseriesPropertyDefinitionMinValue, SByteTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.SingleTimeseriesPropertyDefinition:
                {
                    return new SingleTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, SingleTimeseriesPropertyDefinitionMinValue, SingleTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.StringTimeseriesPropertyDefinition:
                {
                    return new StringTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, StringTimeseriesPropertyDefinitionPattern );
                }
                case Types.Kind.TimeSpanTimeseriesPropertyDefinition:
                {
                    return new TimeSpanTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, TimeSpanTimeseriesPropertyDefinitionMinValue, TimeSpanTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.UInt16TimeseriesPropertyDefinition:
                {
                    return new UInt16TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, UInt16TimeseriesPropertyDefinitionMinValue, UInt16TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.UInt32TimeseriesPropertyDefinition:
                {
                    return new UInt32TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, UInt32TimeseriesPropertyDefinitionMinValue, UInt32TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.UInt64TimeseriesPropertyDefinition:
                {
                    return new UInt64TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, UInt64TimeseriesPropertyDefinitionMinValue, UInt64TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.TimeSpanPropertyDefinition:
                {
                    return new TimeSpanPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, TimeSpanPropertyDefinitionDefaultValue, TimeSpanPropertyDefinitionMinValue, TimeSpanPropertyDefinitionMaxValue );
                }
                case Types.Kind.UInt16PropertyDefinition:
                {
                    return new UInt16PropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, UInt16PropertyDefinitionDefaultValue, UInt16PropertyDefinitionMinValue, UInt16PropertyDefinitionMaxValue );
                }
                case Types.Kind.UInt32PropertyDefinition:
                {
                    return new UInt32PropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, UInt32PropertyDefinitionDefaultValue, UInt32PropertyDefinitionMinValue, UInt32PropertyDefinitionMaxValue );
                }
                case Types.Kind.UInt64PropertyDefinition:
                {
                    return new UInt64PropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, UInt64PropertyDefinitionDefaultValue, UInt64PropertyDefinitionMinValue, UInt64PropertyDefinitionMaxValue );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexTimeseriesPropertyDefinitionDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tpd.[Id], \r\n" +
            "  tpd.[EntityType], \r\n" +
            "  tpd.[RowVersion], \r\n" +
            "  tpd.[ElementType], \r\n" +
            "  tpd.[Name], \r\n" +
            "  bytpd.[MinValue], \r\n" +
            "  bytpd.[MaxValue], \r\n" +
            "  dttpd.[MinValue], \r\n" +
            "  dttpd.[MaxValue], \r\n" +
            "  dotpd.[MinValue], \r\n" +
            "  dotpd.[MaxValue], \r\n" +
            "  i16tpd.[MinValue], \r\n" +
            "  i16tpd.[MaxValue], \r\n" +
            "  i32tpd.[MinValue], \r\n" +
            "  i32tpd.[MaxValue], \r\n" +
            "  i64tpd.[MinValue], \r\n" +
            "  i64tpd.[MaxValue], \r\n" +
            "  rtpd.[ReferencedElementType], \r\n" +
            "  sbtpd.[MinValue], \r\n" +
            "  sbtpd.[MaxValue], \r\n" +
            "  sitpd.[MinValue], \r\n" +
            "  sitpd.[MaxValue], \r\n" +
            "  sttpd.[Pattern], \r\n" +
            "  tstpd.[MinValue], \r\n" +
            "  tstpd.[MaxValue], \r\n" +
            "  u16tpd.[MinValue], \r\n" +
            "  u16tpd.[MaxValue], \r\n" +
            "  u32tpd.[MinValue], \r\n" +
            "  u32tpd.[MaxValue], \r\n" +
            "  u64tpd.[MinValue], \r\n" +
            "  u64tpd.[MaxValue], \r\n" +
            "  tpd.[Description] \r\n" +
            "FROM [TimeseriesPropertyDefinitionView] tpd \r\n" +
            "  LEFT JOIN [BinaryTimeseriesPropertyDefinition] btpd ON(tpd.[Id] = btpd.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseriesPropertyDefinition] botpd ON(tpd.[Id] = botpd.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseriesPropertyDefinition] bytpd ON(tpd.[Id] = bytpd.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseriesPropertyDefinition] dttpd ON(tpd.[Id] = dttpd.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseriesPropertyDefinition] dotpd ON(tpd.[Id] = dotpd.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseriesPropertyDefinition] gtpd ON(tpd.[Id] = gtpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int16TimeseriesPropertyDefinition] i16tpd ON(tpd.[Id] = i16tpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int32TimeseriesPropertyDefinition] i32tpd ON(tpd.[Id] = i32tpd.[Id] ) \r\n" +
            "  LEFT JOIN [Int64TimeseriesPropertyDefinition] i64tpd ON(tpd.[Id] = i64tpd.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseriesPropertyDefinition] rtpd ON(tpd.[Id] = rtpd.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseriesPropertyDefinition] sbtpd ON(tpd.[Id] = sbtpd.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseriesPropertyDefinition] sitpd ON(tpd.[Id] = sitpd.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseriesPropertyDefinition] sttpd ON(tpd.[Id] = sttpd.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseriesPropertyDefinition] tstpd ON(tpd.[Id] = tstpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16TimeseriesPropertyDefinition] u16tpd ON(tpd.[Id] = u16tpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32TimeseriesPropertyDefinition] u32tpd ON(tpd.[Id] = u32tpd.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64TimeseriesPropertyDefinition] u64tpd ON(tpd.[Id] = u64tpd.[Id] ) \r\n";

        public const string BaseViewName = "TimeseriesPropertyDefinitionView";
        public const string ViewAliasName = "tpd";

        public const int TPD_ID_FIELD_ID = 0;
        public const int TPD_KIND_FIELD_ID = 1;
        public const int TPD_ROWVERSION_FIELD_ID = 2;
        public const int TPD_ELEMENTTYPE_FIELD_ID = 3;
        public const int TPD_NAME_FIELD_ID = 4;
        public const int BYTPD_MINVALUE_FIELD_ID = 5;
        public const int BYTPD_MAXVALUE_FIELD_ID = 6;
        public const int DTTPD_MINVALUE_FIELD_ID = 7;
        public const int DTTPD_MAXVALUE_FIELD_ID = 8;
        public const int DOTPD_MINVALUE_FIELD_ID = 9;
        public const int DOTPD_MAXVALUE_FIELD_ID = 10;
        public const int I16TPD_MINVALUE_FIELD_ID = 11;
        public const int I16TPD_MAXVALUE_FIELD_ID = 12;
        public const int I32TPD_MINVALUE_FIELD_ID = 13;
        public const int I32TPD_MAXVALUE_FIELD_ID = 14;
        public const int I64TPD_MINVALUE_FIELD_ID = 15;
        public const int I64TPD_MAXVALUE_FIELD_ID = 16;
        public const int RTPD_REFERENCEDELEMENTTYPE_FIELD_ID = 17;
        public const int SBTPD_MINVALUE_FIELD_ID = 18;
        public const int SBTPD_MAXVALUE_FIELD_ID = 19;
        public const int SITPD_MINVALUE_FIELD_ID = 20;
        public const int SITPD_MAXVALUE_FIELD_ID = 21;
        public const int STTPD_PATTERN_FIELD_ID = 22;
        public const int TSTPD_MINVALUE_FIELD_ID = 23;
        public const int TSTPD_MAXVALUE_FIELD_ID = 24;
        public const int U16TPD_MINVALUE_FIELD_ID = 25;
        public const int U16TPD_MAXVALUE_FIELD_ID = 26;
        public const int U32TPD_MINVALUE_FIELD_ID = 27;
        public const int U32TPD_MAXVALUE_FIELD_ID = 28;
        public const int U64TPD_MINVALUE_FIELD_ID = 29;
        public const int U64TPD_MAXVALUE_FIELD_ID = 30;
        public const int TPD_DESCRIPTION_FIELD_ID = 31;
        public ComplexTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( TPD_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( TPD_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( TPD_ROWVERSION_FIELD_ID );
            }
        }
        public Guid ElementType
        {
            get
            {
                return GetGuid( TPD_ELEMENTTYPE_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( TPD_NAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( TPD_DESCRIPTION_FIELD_ID );
            }
        }
        public byte ByteTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetByte( BYTPD_MINVALUE_FIELD_ID );
            }
        }
        public byte ByteTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetByte( BYTPD_MAXVALUE_FIELD_ID );
            }
        }
        public string DateTimeTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetString( DTTPD_MINVALUE_FIELD_ID );
            }
        }
        public string DateTimeTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetString( DTTPD_MAXVALUE_FIELD_ID );
            }
        }
        public double DoubleTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetDouble( DOTPD_MINVALUE_FIELD_ID );
            }
        }
        public double DoubleTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetDouble( DOTPD_MAXVALUE_FIELD_ID );
            }
        }
        public short Int16TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetInt16( I16TPD_MINVALUE_FIELD_ID );
            }
        }
        public short Int16TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetInt16( I16TPD_MAXVALUE_FIELD_ID );
            }
        }
        public int Int32TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetInt32( I32TPD_MINVALUE_FIELD_ID );
            }
        }
        public int Int32TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetInt32( I32TPD_MAXVALUE_FIELD_ID );
            }
        }
        public long Int64TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetInt64( I64TPD_MINVALUE_FIELD_ID );
            }
        }
        public long Int64TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetInt64( I64TPD_MAXVALUE_FIELD_ID );
            }
        }
        public Guid? ReferenceTimeseriesPropertyDefinitionReferencedElementType
        {
            get
            {
                return GetNullableGuid( RTPD_REFERENCEDELEMENTTYPE_FIELD_ID );
            }
        }
        public sbyte SByteTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetSByte( SBTPD_MINVALUE_FIELD_ID );
            }
        }
        public sbyte SByteTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetSByte( SBTPD_MAXVALUE_FIELD_ID );
            }
        }
        public float SingleTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetFloat( SITPD_MINVALUE_FIELD_ID );
            }
        }
        public float SingleTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetFloat( SITPD_MAXVALUE_FIELD_ID );
            }
        }
        public string StringTimeseriesPropertyDefinitionPattern
        {
            get
            {
                return GetString( STTPD_PATTERN_FIELD_ID );
            }
        }
        public TimeSpan TimeSpanTimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return new TimeSpan( GetInt64( TSTPD_MINVALUE_FIELD_ID ) );
            }
        }
        public TimeSpan TimeSpanTimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return new TimeSpan( GetInt64( TSTPD_MAXVALUE_FIELD_ID ) );
            }
        }
        public ushort UInt16TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetUInt16( U16TPD_MINVALUE_FIELD_ID );
            }
        }
        public ushort UInt16TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetUInt16( U16TPD_MAXVALUE_FIELD_ID );
            }
        }
        public uint UInt32TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetUInt32( U32TPD_MINVALUE_FIELD_ID );
            }
        }
        public uint UInt32TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetUInt32( U32TPD_MAXVALUE_FIELD_ID );
            }
        }
        public long UInt64TimeseriesPropertyDefinitionMinValue
        {
            get
            {
                return GetInt64( U64TPD_MINVALUE_FIELD_ID );
            }
        }
        public long UInt64TimeseriesPropertyDefinitionMaxValue
        {
            get
            {
                return GetInt64( U64TPD_MAXVALUE_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                }
                break;
                case Types.Kind.BooleanTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                }
                break;
                case Types.Kind.ByteTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( ByteTimeseriesPropertyDefinitionMinValue );
                    destination.Write( ByteTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.DateTimeTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( DateTimeTimeseriesPropertyDefinitionMinValue );
                    destination.Write( DateTimeTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.DoubleTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( DoubleTimeseriesPropertyDefinitionMinValue );
                    destination.Write( DoubleTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.GuidTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                }
                break;
                case Types.Kind.Int16TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( Int16TimeseriesPropertyDefinitionMinValue );
                    destination.Write( Int16TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.Int32TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( Int32TimeseriesPropertyDefinitionMinValue );
                    destination.Write( Int32TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.Int64TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( Int64TimeseriesPropertyDefinitionMinValue );
                    destination.Write( Int64TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.ReferenceTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( ReferenceTimeseriesPropertyDefinitionReferencedElementType );
                }
                break;
                case Types.Kind.SByteTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( SByteTimeseriesPropertyDefinitionMinValue );
                    destination.Write( SByteTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.SingleTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( SingleTimeseriesPropertyDefinitionMinValue );
                    destination.Write( SingleTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.StringTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( StringTimeseriesPropertyDefinitionPattern );
                }
                break;
                case Types.Kind.TimeSpanTimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( TimeSpanTimeseriesPropertyDefinitionMinValue );
                    destination.Write( TimeSpanTimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.UInt16TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( UInt16TimeseriesPropertyDefinitionMinValue );
                    destination.Write( UInt16TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.UInt32TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( UInt32TimeseriesPropertyDefinitionMinValue );
                    destination.Write( UInt32TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                case Types.Kind.UInt64TimeseriesPropertyDefinition:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( ElementType );
                    destination.Write( Name );
                    destination.Write( Description );
                    destination.Write( UInt64TimeseriesPropertyDefinitionMinValue );
                    destination.Write( UInt64TimeseriesPropertyDefinitionMaxValue );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public TimeseriesPropertyDefinitionObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryTimeseriesPropertyDefinition:
                {
                    return new BinaryTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description );
                }
                case Types.Kind.BooleanTimeseriesPropertyDefinition:
                {
                    return new BooleanTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description );
                }
                case Types.Kind.ByteTimeseriesPropertyDefinition:
                {
                    return new ByteTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, ByteTimeseriesPropertyDefinitionMinValue, ByteTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.DateTimeTimeseriesPropertyDefinition:
                {
                    return new DateTimeTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, DateTimeTimeseriesPropertyDefinitionMinValue, DateTimeTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.DoubleTimeseriesPropertyDefinition:
                {
                    return new DoubleTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, DoubleTimeseriesPropertyDefinitionMinValue, DoubleTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.GuidTimeseriesPropertyDefinition:
                {
                    return new GuidTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description );
                }
                case Types.Kind.Int16TimeseriesPropertyDefinition:
                {
                    return new Int16TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, Int16TimeseriesPropertyDefinitionMinValue, Int16TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.Int32TimeseriesPropertyDefinition:
                {
                    return new Int32TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, Int32TimeseriesPropertyDefinitionMinValue, Int32TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.Int64TimeseriesPropertyDefinition:
                {
                    return new Int64TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, Int64TimeseriesPropertyDefinitionMinValue, Int64TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.ReferenceTimeseriesPropertyDefinition:
                {
                    return new ReferenceTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, ReferenceTimeseriesPropertyDefinitionReferencedElementType );
                }
                case Types.Kind.SByteTimeseriesPropertyDefinition:
                {
                    return new SByteTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, SByteTimeseriesPropertyDefinitionMinValue, SByteTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.SingleTimeseriesPropertyDefinition:
                {
                    return new SingleTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, SingleTimeseriesPropertyDefinitionMinValue, SingleTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.StringTimeseriesPropertyDefinition:
                {
                    return new StringTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, StringTimeseriesPropertyDefinitionPattern );
                }
                case Types.Kind.TimeSpanTimeseriesPropertyDefinition:
                {
                    return new TimeSpanTimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, TimeSpanTimeseriesPropertyDefinitionMinValue, TimeSpanTimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.UInt16TimeseriesPropertyDefinition:
                {
                    return new UInt16TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, UInt16TimeseriesPropertyDefinitionMinValue, UInt16TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.UInt32TimeseriesPropertyDefinition:
                {
                    return new UInt32TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, UInt32TimeseriesPropertyDefinitionMinValue, UInt32TimeseriesPropertyDefinitionMaxValue );
                }
                case Types.Kind.UInt64TimeseriesPropertyDefinition:
                {
                    return new UInt64TimeseriesPropertyDefinitionObject( ObjectState.Stored, Id, RowVersion, ElementType, Name, Description, UInt64TimeseriesPropertyDefinitionMinValue, UInt64TimeseriesPropertyDefinitionMaxValue );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexRadarCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[EntityType], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radar], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[DeviceCommandSourceType], \r\n" +
            "  rc.[DeviceCommandSourceId], \r\n" +
            "  rc.[Reply] \r\n" +
            "FROM [RadarCommandView] rc \r\n" +
            "  LEFT JOIN [RadarCommandGetStatus] rcgs ON(rc.[Id] = rcgs.[Id] ) \r\n";

        public const string BaseViewName = "RadarCommandView";
        public const string ViewAliasName = "rc";

        public const int RC_ID_FIELD_ID = 0;
        public const int RC_KIND_FIELD_ID = 1;
        public const int RC_ROWVERSION_FIELD_ID = 2;
        public const int RC_RADAR_FIELD_ID = 3;
        public const int RC_TIMESTAMP_FIELD_ID = 4;
        public const int RC_DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        public const int RC_DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        public const int RC_REPLY_FIELD_ID = 7;
        public ComplexRadarCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( RC_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( RC_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( RC_ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radar
        {
            get
            {
                return GetGuid( RC_RADAR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( RC_TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( RC_DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( RC_DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid? Reply
        {
            get
            {
                return GetNullableGuid( RC_REPLY_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.RadarCommand:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Radar );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                }
                break;
                case Types.Kind.RadarCommandGetStatus:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Radar );
                    destination.Write( Timestamp );
                    destination.Write( DeviceCommandSourceType );
                    destination.Write( DeviceCommandSourceId );
                    destination.Write( Reply );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public RadarCommandObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.RadarCommand:
                {
                    return new RadarCommandObject( ObjectState.Stored, Id, RowVersion, Radar, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply );
                }
                case Types.Kind.RadarCommandGetStatus:
                {
                    return new RadarCommandGetStatusObject( ObjectState.Stored, Id, RowVersion, Radar, Timestamp, DeviceCommandSourceType, DeviceCommandSourceId, Reply );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexRadarCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rcr.[Id], \r\n" +
            "  rcr.[EntityType], \r\n" +
            "  rcr.[RowVersion], \r\n" +
            "  rcr.[Radar], \r\n" +
            "  rcr.[Timestamp], \r\n" +
            "  rcr.[Command], \r\n" +
            "  rcr.[Status], \r\n" +
            "  rcrgs.[AzimuthCount], \r\n" +
            "  rcrgs.[TriggerCount], \r\n" +
            "  rcrgs.[RotationCount], \r\n" +
            "  rcrgs.[Pulse], \r\n" +
            "  rcrgs.[Tx], \r\n" +
            "  rcr.[Message] \r\n" +
            "FROM [RadarCommandReplyView] rcr \r\n" +
            "  LEFT JOIN [RadarCommandReplyGetStatus] rcrgs ON(rcr.[Id] = rcrgs.[Id] ) \r\n";

        public const string BaseViewName = "RadarCommandReplyView";
        public const string ViewAliasName = "rcr";

        public const int RCR_ID_FIELD_ID = 0;
        public const int RCR_KIND_FIELD_ID = 1;
        public const int RCR_ROWVERSION_FIELD_ID = 2;
        public const int RCR_RADAR_FIELD_ID = 3;
        public const int RCR_TIMESTAMP_FIELD_ID = 4;
        public const int RCR_COMMAND_FIELD_ID = 5;
        public const int RCR_STATUS_FIELD_ID = 6;
        public const int RCRGS_AZIMUTHCOUNT_FIELD_ID = 7;
        public const int RCRGS_TRIGGERCOUNT_FIELD_ID = 8;
        public const int RCRGS_ROTATIONCOUNT_FIELD_ID = 9;
        public const int RCRGS_PULSE_FIELD_ID = 10;
        public const int RCRGS_TX_FIELD_ID = 11;
        public const int RCR_MESSAGE_FIELD_ID = 12;
        public ComplexRadarCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( RCR_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( RCR_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( RCR_ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radar
        {
            get
            {
                return GetGuid( RCR_RADAR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( RCR_TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid? Command
        {
            get
            {
                return GetNullableGuid( RCR_COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( RCR_STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( RCR_MESSAGE_FIELD_ID );
            }
        }
        public int RadarCommandReplyGetStatusAzimuthCount
        {
            get
            {
                return GetInt32( RCRGS_AZIMUTHCOUNT_FIELD_ID );
            }
        }
        public int RadarCommandReplyGetStatusTriggerCount
        {
            get
            {
                return GetInt32( RCRGS_TRIGGERCOUNT_FIELD_ID );
            }
        }
        public TimeSpan RadarCommandReplyGetStatusRotationCount
        {
            get
            {
                return new TimeSpan( GetInt64( RCRGS_ROTATIONCOUNT_FIELD_ID ) );
            }
        }
        public Types.RadarPulse RadarCommandReplyGetStatusPulse
        {
            get
            {
                return GetEnum<Types.RadarPulse>( RCRGS_PULSE_FIELD_ID );
            }
        }
        public bool RadarCommandReplyGetStatusTx
        {
            get
            {
                return GetBoolean( RCRGS_TX_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.RadarCommandReply:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Radar );
                    destination.Write( Timestamp );
                    destination.Write( Command );
                    destination.Write( Status );
                    destination.Write( Message );
                }
                break;
                case Types.Kind.RadarCommandReplyGetStatus:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Radar );
                    destination.Write( Timestamp );
                    destination.Write( Command );
                    destination.Write( Status );
                    destination.Write( Message );
                    destination.Write( RadarCommandReplyGetStatusAzimuthCount );
                    destination.Write( RadarCommandReplyGetStatusTriggerCount );
                    destination.Write( RadarCommandReplyGetStatusRotationCount );
                    destination.Write( RadarCommandReplyGetStatusPulse );
                    destination.Write( RadarCommandReplyGetStatusTx );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public RadarCommandReplyObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.RadarCommandReply:
                {
                    return new RadarCommandReplyObject( ObjectState.Stored, Id, RowVersion, Radar, Timestamp, Command, Status, Message );
                }
                case Types.Kind.RadarCommandReplyGetStatus:
                {
                    return new RadarCommandReplyGetStatusObject( ObjectState.Stored, Id, RowVersion, Radar, Timestamp, Command, Status, Message, RadarCommandReplyGetStatusAzimuthCount, RadarCommandReplyGetStatusTriggerCount, RadarCommandReplyGetStatusRotationCount, RadarCommandReplyGetStatusPulse, RadarCommandReplyGetStatusTx );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexSecurityIdentifierDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  si.[Id], \r\n" +
            "  si.[EntityType], \r\n" +
            "  si.[RowVersion], \r\n" +
            "  si.[Domain], \r\n" +
            "  si.[Identity], \r\n" +
            "  sr.[Name], \r\n" +
            "  si.[Description] \r\n" +
            "FROM [SecurityIdentifierView] si \r\n" +
            "  LEFT JOIN [SecurityLogin] sl ON(si.[Id] = sl.[Id] ) \r\n" +
            "  LEFT JOIN [SecurityRole] sr ON(si.[Id] = sr.[Id] ) \r\n";

        public const string BaseViewName = "SecurityIdentifierView";
        public const string ViewAliasName = "si";

        public const int SI_ID_FIELD_ID = 0;
        public const int SI_KIND_FIELD_ID = 1;
        public const int SI_ROWVERSION_FIELD_ID = 2;
        public const int SI_DOMAIN_FIELD_ID = 3;
        public const int SI_IDENTITY_FIELD_ID = 4;
        public const int SR_NAME_FIELD_ID = 5;
        public const int SI_DESCRIPTION_FIELD_ID = 6;
        public ComplexSecurityIdentifierDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( SI_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( SI_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( SI_ROWVERSION_FIELD_ID );
            }
        }
        public Guid Domain
        {
            get
            {
                return GetGuid( SI_DOMAIN_FIELD_ID );
            }
        }
        public string Identity
        {
            get
            {
                return GetString( SI_IDENTITY_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( SI_DESCRIPTION_FIELD_ID );
            }
        }
        public string SecurityRoleName
        {
            get
            {
                return GetString( SR_NAME_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.SecurityLogin:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Domain );
                    destination.Write( Identity );
                    destination.Write( Description );
                }
                break;
                case Types.Kind.SecurityRole:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Domain );
                    destination.Write( Identity );
                    destination.Write( Description );
                    destination.Write( SecurityRoleName );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public SecurityIdentifierObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.SecurityLogin:
                {
                    return new SecurityLoginObject( ObjectState.Stored, Id, RowVersion, Domain, Identity, Description );
                }
                case Types.Kind.SecurityRole:
                {
                    return new SecurityRoleObject( ObjectState.Stored, Id, RowVersion, Domain, Identity, Description, SecurityRoleName );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexTimeseriesCatalogElementDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tce.[Id], \r\n" +
            "  tce.[EntityType], \r\n" +
            "  tce.[RowVersion], \r\n" +
            "  tce.[Catalog], \r\n" +
            "  tce.[Name], \r\n" +
            "  t.[MaxRetention], \r\n" +
            "  aatnopt.[AidToNavigation], \r\n" +
            "  det.[Device], \r\n" +
            "  mpset.[ProxySession], \r\n" +
            "  mset.[Service], \r\n" +
            "  rastct.[Radar], \r\n" +
            "  rbs1t.[Radar], \r\n" +
            "  rbs2t.[Radar], \r\n" +
            "  reafct.[Radar], \r\n" +
            "  reftct.[Radar], \r\n" +
            "  restct.[Radar], \r\n" +
            "  rpot.[Radar], \r\n" +
            "  rsst.[Radar], \r\n" +
            "  rtt.[Radar], \r\n" +
            "  gats.[GNSSDevice], \r\n" +
            "  glats.[GNSSDevice], \r\n" +
            "  glots.[GNSSDevice], \r\n" +
            "  gct.[GyroDevice], \r\n" +
            "  ghmnt.[GyroDevice], \r\n" +
            "  ghtnt.[GyroDevice], \r\n" +
            "  gpt.[GyroDevice], \r\n" +
            "  grott.[GyroDevice], \r\n" +
            "  grt.[GyroDevice], \r\n" +
            "  gst.[GyroDevice], \r\n" +
            "  rlats.[Radar], \r\n" +
            "  rlots.[Radar], \r\n" +
            "  rdpt.[Radome], \r\n" +
            "  rpt.[Radome], \r\n" +
            "  rtets.[Radome], \r\n" +
            "  vdt.[Vessel], \r\n" +
            "  vlats.[View], \r\n" +
            "  vlots.[View], \r\n" +
            "  vzlt.[View], \r\n" +
            "  wsaht.[WeatherStation], \r\n" +
            "  wsatt.[WeatherStation], \r\n" +
            "  wsbpt.[WeatherStation], \r\n" +
            "  wsdpt.[WeatherStation], \r\n" +
            "  wsrht.[WeatherStation], \r\n" +
            "  wswtt.[WeatherStation], \r\n" +
            "  wswdt.[WeatherStation], \r\n" +
            "  wswst.[WeatherStation], \r\n" +
            "  aatnpt.[AidToNavigation], \r\n" +
            "  raot.[Radar], \r\n" +
            "  rftclt.[Radar], \r\n" +
            "  rftcmt.[Radar], \r\n" +
            "  rapts.[Radar], \r\n" +
            "  rs1et.[Radar], \r\n" +
            "  rs1st.[Radar], \r\n" +
            "  rs2et.[Radar], \r\n" +
            "  rs2st.[Radar], \r\n" +
            "  rstclt.[Radar], \r\n" +
            "  ratuts.[Radar], \r\n" +
            "  vpobt.[Vessel], \r\n" +
            "  rst.[Radome] \r\n" +
            "FROM [TimeseriesCatalogElementView] tce \r\n" +
            "  LEFT JOIN [Timeseries] t ON(tce.[Id] = t.[Id] ) \r\n" +
            "  LEFT JOIN [BinaryTimeseries] bt ON(tce.[Id] = bt.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseries] bots ON(tce.[Id] = bots.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigationOffPositionTimeseries] aatnopt ON(tce.[Id] = aatnopt.[Id] ) \r\n" +
            "  LEFT JOIN [DeviceEnabledTimeseries] det ON(tce.[Id] = det.[Id] ) \r\n" +
            "  LEFT JOIN [MediaProxySessionEnabledTimeseries] mpset ON(tce.[Id] = mpset.[Id] ) \r\n" +
            "  LEFT JOIN [MediaServiceEnabledTimeseries] mset ON(tce.[Id] = mset.[Id] ) \r\n" +
            "  LEFT JOIN [RadarAutomaticSensitivityTimeControlTimeseries] rastct ON(tce.[Id] = rastct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector1Timeseries] rbs1t ON(tce.[Id] = rbs1t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector2Timeseries] rbs2t ON(tce.[Id] = rbs2t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableAutomaticFrequencyControlTimeseries] reafct ON(tce.[Id] = reafct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableFastTimeConstantTimeseries] reftct ON(tce.[Id] = reftct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableSensitivityTimeControlTimeseries] restct ON(tce.[Id] = restct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPowerOnTimeseries] rpot ON(tce.[Id] = rpot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSaveSettingsTimeseries] rsst ON(tce.[Id] = rsst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTrackingTimeseries] rtt ON(tce.[Id] = rtt.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseries] byts ON(tce.[Id] = byts.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseries] dtt ON(tce.[Id] = dtt.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseries] dt ON(tce.[Id] = dt.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSAltitudeTimeseries] gats ON(tce.[Id] = gats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLatitudeTimeseries] glats ON(tce.[Id] = glats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLongitudeTimeseries] glots ON(tce.[Id] = glots.[Id] ) \r\n" +
            "  LEFT JOIN [GyroCourseTimeseries] gct ON(tce.[Id] = gct.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingMagneticNorthTimeseries] ghmnt ON(tce.[Id] = ghmnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingTrueNorthTimeseries] ghtnt ON(tce.[Id] = ghtnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroPitchTimeseries] gpt ON(tce.[Id] = gpt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRateOfTurnTimeseries] grott ON(tce.[Id] = grott.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRollTimeseries] grt ON(tce.[Id] = grt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroSpeedTimeseries] gst ON(tce.[Id] = gst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLatitudeTimeseries] rlats ON(tce.[Id] = rlats.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLongitudeTimeseries] rlots ON(tce.[Id] = rlots.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeDewPointTimeseries] rdpt ON(tce.[Id] = rdpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomePressureTimeseries] rpt ON(tce.[Id] = rpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeTemperatureTimeseries] rtets ON(tce.[Id] = rtets.[Id] ) \r\n" +
            "  LEFT JOIN [VesselDraughtTimeseries] vdt ON(tce.[Id] = vdt.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLatitudeTimeseries] vlats ON(tce.[Id] = vlats.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLongitudeTimeseries] vlots ON(tce.[Id] = vlots.[Id] ) \r\n" +
            "  LEFT JOIN [ViewZoomLevelTimeseries] vzlt ON(tce.[Id] = vzlt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAbsoluteHumidityTimeseries] wsaht ON(tce.[Id] = wsaht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAirTemperatureTimeseries] wsatt ON(tce.[Id] = wsatt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationBarometricPressureTimeseries] wsbpt ON(tce.[Id] = wsbpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationDewPointTimeseries] wsdpt ON(tce.[Id] = wsdpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationRelativeHumidityTimeseries] wsrht ON(tce.[Id] = wsrht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWaterTemperatureTimeseries] wswtt ON(tce.[Id] = wswtt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindDirectionTimeseries] wswdt ON(tce.[Id] = wswdt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindSpeedTimeseries] wswst ON(tce.[Id] = wswst.[Id] ) \r\n" +
            "  LEFT JOIN [GeoPosition2DTimeseries] gp2d ON(tce.[Id] = gp2d.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigationPositionTimeseries] aatnpt ON(tce.[Id] = aatnpt.[Id] ) \r\n" +
            "  LEFT JOIN [GeoPosition3DTimeseries] gp3d ON(tce.[Id] = gp3d.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseries] gt ON(tce.[Id] = gt.[Id] ) \r\n" +
            "  LEFT JOIN [Int16Timeseries] i16t ON(tce.[Id] = i16t.[Id] ) \r\n" +
            "  LEFT JOIN [Int32Timeseries] i32t ON(tce.[Id] = i32t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarAzimuthOffsetTimeseries] raot ON(tce.[Id] = raot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantLevelTimeseries] rftclt ON(tce.[Id] = rftclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantModeTimeseries] rftcmt ON(tce.[Id] = rftcmt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPulseTimeseries] rapts ON(tce.[Id] = rapts.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1EndTimeseries] rs1et ON(tce.[Id] = rs1et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1StartTimeseries] rs1st ON(tce.[Id] = rs1st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2EndTimeseries] rs2et ON(tce.[Id] = rs2et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2StartTimeseries] rs2st ON(tce.[Id] = rs2st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSensitivityTimeControlLevelTimeseries] rstclt ON(tce.[Id] = rstclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTuningTimeseries] ratuts ON(tce.[Id] = ratuts.[Id] ) \r\n" +
            "  LEFT JOIN [VesselPersonsOnBoardTimeseries] vpobt ON(tce.[Id] = vpobt.[Id] ) \r\n" +
            "  LEFT JOIN [Int64Timeseries] i64t ON(tce.[Id] = i64t.[Id] ) \r\n" +
            "  LEFT JOIN [Position2DTimeseries] p2d ON(tce.[Id] = p2d.[Id] ) \r\n" +
            "  LEFT JOIN [Position3DTimeseries] p3d ON(tce.[Id] = p3d.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseries] rt ON(tce.[Id] = rt.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseries] st ON(tce.[Id] = st.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseries] sits ON(tce.[Id] = sits.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseries] stts ON(tce.[Id] = stts.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseries] tst ON(tce.[Id] = tst.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16Timeseries] u16t ON(tce.[Id] = u16t.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32Timeseries] u32t ON(tce.[Id] = u32t.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeStatusTimeseries] rst ON(tce.[Id] = rst.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64Timeseries] u64t ON(tce.[Id] = u64t.[Id] ) \r\n" +
            "  LEFT JOIN [TimeseriesCatalog] tc ON(tce.[Id] = tc.[Id] ) \r\n";

        public const string BaseViewName = "TimeseriesCatalogElementView";
        public const string ViewAliasName = "tce";

        public const int TCE_ID_FIELD_ID = 0;
        public const int TCE_KIND_FIELD_ID = 1;
        public const int TCE_ROWVERSION_FIELD_ID = 2;
        public const int TCE_CATALOG_FIELD_ID = 3;
        public const int TCE_NAME_FIELD_ID = 4;
        public const int T_MAXRETENTION_FIELD_ID = 5;
        public const int AATNOPT_AIDTONAVIGATION_FIELD_ID = 6;
        public const int DET_DEVICE_FIELD_ID = 7;
        public const int MPSET_PROXYSESSION_FIELD_ID = 8;
        public const int MSET_SERVICE_FIELD_ID = 9;
        public const int RASTCT_RADAR_FIELD_ID = 10;
        public const int RBS1T_RADAR_FIELD_ID = 11;
        public const int RBS2T_RADAR_FIELD_ID = 12;
        public const int REAFCT_RADAR_FIELD_ID = 13;
        public const int REFTCT_RADAR_FIELD_ID = 14;
        public const int RESTCT_RADAR_FIELD_ID = 15;
        public const int RPOT_RADAR_FIELD_ID = 16;
        public const int RSST_RADAR_FIELD_ID = 17;
        public const int RTT_RADAR_FIELD_ID = 18;
        public const int GATS_GNSSDEVICE_FIELD_ID = 19;
        public const int GLATS_GNSSDEVICE_FIELD_ID = 20;
        public const int GLOTS_GNSSDEVICE_FIELD_ID = 21;
        public const int GCT_GYRODEVICE_FIELD_ID = 22;
        public const int GHMNT_GYRODEVICE_FIELD_ID = 23;
        public const int GHTNT_GYRODEVICE_FIELD_ID = 24;
        public const int GPT_GYRODEVICE_FIELD_ID = 25;
        public const int GROTT_GYRODEVICE_FIELD_ID = 26;
        public const int GRT_GYRODEVICE_FIELD_ID = 27;
        public const int GST_GYRODEVICE_FIELD_ID = 28;
        public const int RLATS_RADAR_FIELD_ID = 29;
        public const int RLOTS_RADAR_FIELD_ID = 30;
        public const int RDPT_RADOME_FIELD_ID = 31;
        public const int RPT_RADOME_FIELD_ID = 32;
        public const int RTETS_RADOME_FIELD_ID = 33;
        public const int VDT_VESSEL_FIELD_ID = 34;
        public const int VLATS_VIEW_FIELD_ID = 35;
        public const int VLOTS_VIEW_FIELD_ID = 36;
        public const int VZLT_VIEW_FIELD_ID = 37;
        public const int WSAHT_WEATHERSTATION_FIELD_ID = 38;
        public const int WSATT_WEATHERSTATION_FIELD_ID = 39;
        public const int WSBPT_WEATHERSTATION_FIELD_ID = 40;
        public const int WSDPT_WEATHERSTATION_FIELD_ID = 41;
        public const int WSRHT_WEATHERSTATION_FIELD_ID = 42;
        public const int WSWTT_WEATHERSTATION_FIELD_ID = 43;
        public const int WSWDT_WEATHERSTATION_FIELD_ID = 44;
        public const int WSWST_WEATHERSTATION_FIELD_ID = 45;
        public const int AATNPT_AIDTONAVIGATION_FIELD_ID = 46;
        public const int RAOT_RADAR_FIELD_ID = 47;
        public const int RFTCLT_RADAR_FIELD_ID = 48;
        public const int RFTCMT_RADAR_FIELD_ID = 49;
        public const int RAPTS_RADAR_FIELD_ID = 50;
        public const int RS1ET_RADAR_FIELD_ID = 51;
        public const int RS1ST_RADAR_FIELD_ID = 52;
        public const int RS2ET_RADAR_FIELD_ID = 53;
        public const int RS2ST_RADAR_FIELD_ID = 54;
        public const int RSTCLT_RADAR_FIELD_ID = 55;
        public const int RATUTS_RADAR_FIELD_ID = 56;
        public const int VPOBT_VESSEL_FIELD_ID = 57;
        public const int RST_RADOME_FIELD_ID = 58;
        public ComplexTimeseriesCatalogElementDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( TCE_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( TCE_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( TCE_ROWVERSION_FIELD_ID );
            }
        }
        public Guid? Catalog
        {
            get
            {
                return GetNullableGuid( TCE_CATALOG_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( TCE_NAME_FIELD_ID );
            }
        }
        public TimeSpan TimeseriesMaxRetention
        {
            get
            {
                return new TimeSpan( GetInt64( T_MAXRETENTION_FIELD_ID ) );
            }
        }
        public Guid? AisAidToNavigationOffPositionTimeseriesAidToNavigation
        {
            get
            {
                return GetNullableGuid( AATNOPT_AIDTONAVIGATION_FIELD_ID );
            }
        }
        public Guid? DeviceEnabledTimeseriesDevice
        {
            get
            {
                return GetNullableGuid( DET_DEVICE_FIELD_ID );
            }
        }
        public Guid? MediaProxySessionEnabledTimeseriesProxySession
        {
            get
            {
                return GetNullableGuid( MPSET_PROXYSESSION_FIELD_ID );
            }
        }
        public Guid? MediaServiceEnabledTimeseriesService
        {
            get
            {
                return GetNullableGuid( MSET_SERVICE_FIELD_ID );
            }
        }
        public Guid? RadarAutomaticSensitivityTimeControlTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RASTCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarBlankSector1TimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RBS1T_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarBlankSector2TimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RBS2T_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarEnableAutomaticFrequencyControlTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( REAFCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarEnableFastTimeConstantTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( REFTCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarEnableSensitivityTimeControlTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RESTCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarPowerOnTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RPOT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSaveSettingsTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RSST_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarTrackingTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RTT_RADAR_FIELD_ID );
            }
        }
        public Guid? GNSSAltitudeTimeseriesGNSSDevice
        {
            get
            {
                return GetNullableGuid( GATS_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? GNSSLatitudeTimeseriesGNSSDevice
        {
            get
            {
                return GetNullableGuid( GLATS_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? GNSSLongitudeTimeseriesGNSSDevice
        {
            get
            {
                return GetNullableGuid( GLOTS_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? GyroCourseTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GCT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroHeadingMagneticNorthTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GHMNT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroHeadingTrueNorthTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GHTNT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroPitchTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GPT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroRateOfTurnTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GROTT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroRollTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GRT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroSpeedTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GST_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? RadarLatitudeTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RLATS_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarLongitudeTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RLOTS_RADAR_FIELD_ID );
            }
        }
        public Guid? RadomeDewPointTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RDPT_RADOME_FIELD_ID );
            }
        }
        public Guid? RadomePressureTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RPT_RADOME_FIELD_ID );
            }
        }
        public Guid? RadomeTemperatureTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RTETS_RADOME_FIELD_ID );
            }
        }
        public Guid? VesselDraughtTimeseriesVessel
        {
            get
            {
                return GetNullableGuid( VDT_VESSEL_FIELD_ID );
            }
        }
        public Guid? ViewLatitudeTimeseriesView
        {
            get
            {
                return GetNullableGuid( VLATS_VIEW_FIELD_ID );
            }
        }
        public Guid? ViewLongitudeTimeseriesView
        {
            get
            {
                return GetNullableGuid( VLOTS_VIEW_FIELD_ID );
            }
        }
        public Guid? ViewZoomLevelTimeseriesView
        {
            get
            {
                return GetNullableGuid( VZLT_VIEW_FIELD_ID );
            }
        }
        public Guid? WeatherStationAbsoluteHumidityTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSAHT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationAirTemperatureTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSATT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationBarometricPressureTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSBPT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationDewPointTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSDPT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationRelativeHumidityTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSRHT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationWaterTemperatureTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSWTT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationWindDirectionTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSWDT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationWindSpeedTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSWST_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? AisAidToNavigationPositionTimeseriesAidToNavigation
        {
            get
            {
                return GetNullableGuid( AATNPT_AIDTONAVIGATION_FIELD_ID );
            }
        }
        public Guid? RadarAzimuthOffsetTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RAOT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarFastTimeConstantLevelTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RFTCLT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarFastTimeConstantModeTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RFTCMT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarPulseTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RAPTS_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector1EndTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS1ET_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector1StartTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS1ST_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector2EndTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS2ET_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector2StartTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS2ST_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSensitivityTimeControlLevelTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RSTCLT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarTuningTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RATUTS_RADAR_FIELD_ID );
            }
        }
        public Guid? VesselPersonsOnBoardTimeseriesVessel
        {
            get
            {
                return GetNullableGuid( VPOBT_VESSEL_FIELD_ID );
            }
        }
        public Guid? RadomeStatusTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RST_RADOME_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.BooleanTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.AisAidToNavigationOffPositionTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( AisAidToNavigationOffPositionTimeseriesAidToNavigation );
                }
                break;
                case Types.Kind.DeviceEnabledTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( DeviceEnabledTimeseriesDevice );
                }
                break;
                case Types.Kind.MediaProxySessionEnabledTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( MediaProxySessionEnabledTimeseriesProxySession );
                }
                break;
                case Types.Kind.MediaServiceEnabledTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( MediaServiceEnabledTimeseriesService );
                }
                break;
                case Types.Kind.RadarAutomaticSensitivityTimeControlTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarAutomaticSensitivityTimeControlTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarBlankSector1Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarBlankSector1TimeseriesRadar );
                }
                break;
                case Types.Kind.RadarBlankSector2Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarBlankSector2TimeseriesRadar );
                }
                break;
                case Types.Kind.RadarEnableAutomaticFrequencyControlTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarEnableAutomaticFrequencyControlTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarEnableFastTimeConstantTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarEnableFastTimeConstantTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarEnableSensitivityTimeControlTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarEnableSensitivityTimeControlTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarPowerOnTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarPowerOnTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSaveSettingsTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarSaveSettingsTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarTrackingTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarTrackingTimeseriesRadar );
                }
                break;
                case Types.Kind.ByteTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.DateTimeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.DoubleTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.GNSSAltitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( GNSSAltitudeTimeseriesGNSSDevice );
                }
                break;
                case Types.Kind.GNSSLatitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( GNSSLatitudeTimeseriesGNSSDevice );
                }
                break;
                case Types.Kind.GNSSLongitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( GNSSLongitudeTimeseriesGNSSDevice );
                }
                break;
                case Types.Kind.GyroCourseTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( GyroCourseTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroHeadingMagneticNorthTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( GyroHeadingMagneticNorthTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroHeadingTrueNorthTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( GyroHeadingTrueNorthTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroPitchTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( GyroPitchTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroRateOfTurnTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( GyroRateOfTurnTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroRollTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( GyroRollTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroSpeedTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( GyroSpeedTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.RadarLatitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarLatitudeTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarLongitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarLongitudeTimeseriesRadar );
                }
                break;
                case Types.Kind.RadomeDewPointTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadomeDewPointTimeseriesRadome );
                }
                break;
                case Types.Kind.RadomePressureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadomePressureTimeseriesRadome );
                }
                break;
                case Types.Kind.RadomeTemperatureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadomeTemperatureTimeseriesRadome );
                }
                break;
                case Types.Kind.VesselDraughtTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( VesselDraughtTimeseriesVessel );
                }
                break;
                case Types.Kind.ViewLatitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( ViewLatitudeTimeseriesView );
                }
                break;
                case Types.Kind.ViewLongitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( ViewLongitudeTimeseriesView );
                }
                break;
                case Types.Kind.ViewZoomLevelTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( ViewZoomLevelTimeseriesView );
                }
                break;
                case Types.Kind.WeatherStationAbsoluteHumidityTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( WeatherStationAbsoluteHumidityTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationAirTemperatureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( WeatherStationAirTemperatureTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationBarometricPressureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( WeatherStationBarometricPressureTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationDewPointTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( WeatherStationDewPointTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationRelativeHumidityTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( WeatherStationRelativeHumidityTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationWaterTemperatureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( WeatherStationWaterTemperatureTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationWindDirectionTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( WeatherStationWindDirectionTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationWindSpeedTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( WeatherStationWindSpeedTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.GeoPosition2DTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.AisAidToNavigationPositionTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( AisAidToNavigationPositionTimeseriesAidToNavigation );
                }
                break;
                case Types.Kind.GeoPosition3DTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.GuidTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.Int16Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.Int32Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.RadarAzimuthOffsetTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarAzimuthOffsetTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarFastTimeConstantLevelTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarFastTimeConstantLevelTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarFastTimeConstantModeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarFastTimeConstantModeTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarPulseTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarPulseTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector1EndTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarSector1EndTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector1StartTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarSector1StartTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector2EndTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarSector2EndTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector2StartTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarSector2StartTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSensitivityTimeControlLevelTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarSensitivityTimeControlLevelTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarTuningTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadarTuningTimeseriesRadar );
                }
                break;
                case Types.Kind.VesselPersonsOnBoardTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( VesselPersonsOnBoardTimeseriesVessel );
                }
                break;
                case Types.Kind.Int64Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.Position2DTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.Position3DTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.ReferenceTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.SByteTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.SingleTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.StringTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.TimeSpanTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.UInt16Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.UInt32Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.RadomeStatusTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                    destination.Write( RadomeStatusTimeseriesRadome );
                }
                break;
                case Types.Kind.UInt64Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( TimeseriesMaxRetention );
                }
                break;
                case Types.Kind.TimeseriesCatalog:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public TimeseriesCatalogElementObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryTimeseries:
                {
                    return new BinaryTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.BooleanTimeseries:
                {
                    return new BooleanTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.AisAidToNavigationOffPositionTimeseries:
                {
                    return new AisAidToNavigationOffPositionTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, AisAidToNavigationOffPositionTimeseriesAidToNavigation );
                }
                case Types.Kind.DeviceEnabledTimeseries:
                {
                    return new DeviceEnabledTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, DeviceEnabledTimeseriesDevice );
                }
                case Types.Kind.MediaProxySessionEnabledTimeseries:
                {
                    return new MediaProxySessionEnabledTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, MediaProxySessionEnabledTimeseriesProxySession );
                }
                case Types.Kind.MediaServiceEnabledTimeseries:
                {
                    return new MediaServiceEnabledTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, MediaServiceEnabledTimeseriesService );
                }
                case Types.Kind.RadarAutomaticSensitivityTimeControlTimeseries:
                {
                    return new RadarAutomaticSensitivityTimeControlTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarAutomaticSensitivityTimeControlTimeseriesRadar );
                }
                case Types.Kind.RadarBlankSector1Timeseries:
                {
                    return new RadarBlankSector1TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarBlankSector1TimeseriesRadar );
                }
                case Types.Kind.RadarBlankSector2Timeseries:
                {
                    return new RadarBlankSector2TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarBlankSector2TimeseriesRadar );
                }
                case Types.Kind.RadarEnableAutomaticFrequencyControlTimeseries:
                {
                    return new RadarEnableAutomaticFrequencyControlTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarEnableAutomaticFrequencyControlTimeseriesRadar );
                }
                case Types.Kind.RadarEnableFastTimeConstantTimeseries:
                {
                    return new RadarEnableFastTimeConstantTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarEnableFastTimeConstantTimeseriesRadar );
                }
                case Types.Kind.RadarEnableSensitivityTimeControlTimeseries:
                {
                    return new RadarEnableSensitivityTimeControlTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarEnableSensitivityTimeControlTimeseriesRadar );
                }
                case Types.Kind.RadarPowerOnTimeseries:
                {
                    return new RadarPowerOnTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarPowerOnTimeseriesRadar );
                }
                case Types.Kind.RadarSaveSettingsTimeseries:
                {
                    return new RadarSaveSettingsTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarSaveSettingsTimeseriesRadar );
                }
                case Types.Kind.RadarTrackingTimeseries:
                {
                    return new RadarTrackingTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarTrackingTimeseriesRadar );
                }
                case Types.Kind.ByteTimeseries:
                {
                    return new ByteTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.DateTimeTimeseries:
                {
                    return new DateTimeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.DoubleTimeseries:
                {
                    return new DoubleTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.GNSSAltitudeTimeseries:
                {
                    return new GNSSAltitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, GNSSAltitudeTimeseriesGNSSDevice );
                }
                case Types.Kind.GNSSLatitudeTimeseries:
                {
                    return new GNSSLatitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, GNSSLatitudeTimeseriesGNSSDevice );
                }
                case Types.Kind.GNSSLongitudeTimeseries:
                {
                    return new GNSSLongitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, GNSSLongitudeTimeseriesGNSSDevice );
                }
                case Types.Kind.GyroCourseTimeseries:
                {
                    return new GyroCourseTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, GyroCourseTimeseriesGyroDevice );
                }
                case Types.Kind.GyroHeadingMagneticNorthTimeseries:
                {
                    return new GyroHeadingMagneticNorthTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, GyroHeadingMagneticNorthTimeseriesGyroDevice );
                }
                case Types.Kind.GyroHeadingTrueNorthTimeseries:
                {
                    return new GyroHeadingTrueNorthTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, GyroHeadingTrueNorthTimeseriesGyroDevice );
                }
                case Types.Kind.GyroPitchTimeseries:
                {
                    return new GyroPitchTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, GyroPitchTimeseriesGyroDevice );
                }
                case Types.Kind.GyroRateOfTurnTimeseries:
                {
                    return new GyroRateOfTurnTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, GyroRateOfTurnTimeseriesGyroDevice );
                }
                case Types.Kind.GyroRollTimeseries:
                {
                    return new GyroRollTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, GyroRollTimeseriesGyroDevice );
                }
                case Types.Kind.GyroSpeedTimeseries:
                {
                    return new GyroSpeedTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, GyroSpeedTimeseriesGyroDevice );
                }
                case Types.Kind.RadarLatitudeTimeseries:
                {
                    return new RadarLatitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarLatitudeTimeseriesRadar );
                }
                case Types.Kind.RadarLongitudeTimeseries:
                {
                    return new RadarLongitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarLongitudeTimeseriesRadar );
                }
                case Types.Kind.RadomeDewPointTimeseries:
                {
                    return new RadomeDewPointTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadomeDewPointTimeseriesRadome );
                }
                case Types.Kind.RadomePressureTimeseries:
                {
                    return new RadomePressureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadomePressureTimeseriesRadome );
                }
                case Types.Kind.RadomeTemperatureTimeseries:
                {
                    return new RadomeTemperatureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadomeTemperatureTimeseriesRadome );
                }
                case Types.Kind.VesselDraughtTimeseries:
                {
                    return new VesselDraughtTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, VesselDraughtTimeseriesVessel );
                }
                case Types.Kind.ViewLatitudeTimeseries:
                {
                    return new ViewLatitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, ViewLatitudeTimeseriesView );
                }
                case Types.Kind.ViewLongitudeTimeseries:
                {
                    return new ViewLongitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, ViewLongitudeTimeseriesView );
                }
                case Types.Kind.ViewZoomLevelTimeseries:
                {
                    return new ViewZoomLevelTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, ViewZoomLevelTimeseriesView );
                }
                case Types.Kind.WeatherStationAbsoluteHumidityTimeseries:
                {
                    return new WeatherStationAbsoluteHumidityTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, WeatherStationAbsoluteHumidityTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationAirTemperatureTimeseries:
                {
                    return new WeatherStationAirTemperatureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, WeatherStationAirTemperatureTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationBarometricPressureTimeseries:
                {
                    return new WeatherStationBarometricPressureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, WeatherStationBarometricPressureTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationDewPointTimeseries:
                {
                    return new WeatherStationDewPointTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, WeatherStationDewPointTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationRelativeHumidityTimeseries:
                {
                    return new WeatherStationRelativeHumidityTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, WeatherStationRelativeHumidityTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationWaterTemperatureTimeseries:
                {
                    return new WeatherStationWaterTemperatureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, WeatherStationWaterTemperatureTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationWindDirectionTimeseries:
                {
                    return new WeatherStationWindDirectionTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, WeatherStationWindDirectionTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationWindSpeedTimeseries:
                {
                    return new WeatherStationWindSpeedTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, WeatherStationWindSpeedTimeseriesWeatherStation );
                }
                case Types.Kind.GeoPosition2DTimeseries:
                {
                    return new GeoPosition2DTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.AisAidToNavigationPositionTimeseries:
                {
                    return new AisAidToNavigationPositionTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, AisAidToNavigationPositionTimeseriesAidToNavigation );
                }
                case Types.Kind.GeoPosition3DTimeseries:
                {
                    return new GeoPosition3DTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.GuidTimeseries:
                {
                    return new GuidTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.Int16Timeseries:
                {
                    return new Int16TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.Int32Timeseries:
                {
                    return new Int32TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.RadarAzimuthOffsetTimeseries:
                {
                    return new RadarAzimuthOffsetTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarAzimuthOffsetTimeseriesRadar );
                }
                case Types.Kind.RadarFastTimeConstantLevelTimeseries:
                {
                    return new RadarFastTimeConstantLevelTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarFastTimeConstantLevelTimeseriesRadar );
                }
                case Types.Kind.RadarFastTimeConstantModeTimeseries:
                {
                    return new RadarFastTimeConstantModeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarFastTimeConstantModeTimeseriesRadar );
                }
                case Types.Kind.RadarPulseTimeseries:
                {
                    return new RadarPulseTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarPulseTimeseriesRadar );
                }
                case Types.Kind.RadarSector1EndTimeseries:
                {
                    return new RadarSector1EndTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarSector1EndTimeseriesRadar );
                }
                case Types.Kind.RadarSector1StartTimeseries:
                {
                    return new RadarSector1StartTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarSector1StartTimeseriesRadar );
                }
                case Types.Kind.RadarSector2EndTimeseries:
                {
                    return new RadarSector2EndTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarSector2EndTimeseriesRadar );
                }
                case Types.Kind.RadarSector2StartTimeseries:
                {
                    return new RadarSector2StartTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarSector2StartTimeseriesRadar );
                }
                case Types.Kind.RadarSensitivityTimeControlLevelTimeseries:
                {
                    return new RadarSensitivityTimeControlLevelTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarSensitivityTimeControlLevelTimeseriesRadar );
                }
                case Types.Kind.RadarTuningTimeseries:
                {
                    return new RadarTuningTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadarTuningTimeseriesRadar );
                }
                case Types.Kind.VesselPersonsOnBoardTimeseries:
                {
                    return new VesselPersonsOnBoardTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, VesselPersonsOnBoardTimeseriesVessel );
                }
                case Types.Kind.Int64Timeseries:
                {
                    return new Int64TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.Position2DTimeseries:
                {
                    return new Position2DTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.Position3DTimeseries:
                {
                    return new Position3DTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.ReferenceTimeseries:
                {
                    return new ReferenceTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.SByteTimeseries:
                {
                    return new SByteTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.SingleTimeseries:
                {
                    return new SingleTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.StringTimeseries:
                {
                    return new StringTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.TimeSpanTimeseries:
                {
                    return new TimeSpanTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.UInt16Timeseries:
                {
                    return new UInt16TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.UInt32Timeseries:
                {
                    return new UInt32TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.RadomeStatusTimeseries:
                {
                    return new RadomeStatusTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention, RadomeStatusTimeseriesRadome );
                }
                case Types.Kind.UInt64Timeseries:
                {
                    return new UInt64TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, TimeseriesMaxRetention );
                }
                case Types.Kind.TimeseriesCatalog:
                {
                    return new TimeseriesCatalogObject( ObjectState.Stored, Id, RowVersion, Catalog, Name );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexTimeseriesDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  t.[Id], \r\n" +
            "  t.[EntityType], \r\n" +
            "  t.[RowVersion], \r\n" +
            "  t.[Catalog], \r\n" +
            "  t.[Name], \r\n" +
            "  t.[MaxRetention], \r\n" +
            "  aatnopt.[AidToNavigation], \r\n" +
            "  det.[Device], \r\n" +
            "  mpset.[ProxySession], \r\n" +
            "  mset.[Service], \r\n" +
            "  rastct.[Radar], \r\n" +
            "  rbs1t.[Radar], \r\n" +
            "  rbs2t.[Radar], \r\n" +
            "  reafct.[Radar], \r\n" +
            "  reftct.[Radar], \r\n" +
            "  restct.[Radar], \r\n" +
            "  rpot.[Radar], \r\n" +
            "  rsst.[Radar], \r\n" +
            "  rtt.[Radar], \r\n" +
            "  gats.[GNSSDevice], \r\n" +
            "  glats.[GNSSDevice], \r\n" +
            "  glots.[GNSSDevice], \r\n" +
            "  gct.[GyroDevice], \r\n" +
            "  ghmnt.[GyroDevice], \r\n" +
            "  ghtnt.[GyroDevice], \r\n" +
            "  gpt.[GyroDevice], \r\n" +
            "  grott.[GyroDevice], \r\n" +
            "  grt.[GyroDevice], \r\n" +
            "  gst.[GyroDevice], \r\n" +
            "  rlats.[Radar], \r\n" +
            "  rlots.[Radar], \r\n" +
            "  rdpt.[Radome], \r\n" +
            "  rpt.[Radome], \r\n" +
            "  rtets.[Radome], \r\n" +
            "  vdt.[Vessel], \r\n" +
            "  vlats.[View], \r\n" +
            "  vlots.[View], \r\n" +
            "  vzlt.[View], \r\n" +
            "  wsaht.[WeatherStation], \r\n" +
            "  wsatt.[WeatherStation], \r\n" +
            "  wsbpt.[WeatherStation], \r\n" +
            "  wsdpt.[WeatherStation], \r\n" +
            "  wsrht.[WeatherStation], \r\n" +
            "  wswtt.[WeatherStation], \r\n" +
            "  wswdt.[WeatherStation], \r\n" +
            "  wswst.[WeatherStation], \r\n" +
            "  aatnpt.[AidToNavigation], \r\n" +
            "  raot.[Radar], \r\n" +
            "  rftclt.[Radar], \r\n" +
            "  rftcmt.[Radar], \r\n" +
            "  rapts.[Radar], \r\n" +
            "  rs1et.[Radar], \r\n" +
            "  rs1st.[Radar], \r\n" +
            "  rs2et.[Radar], \r\n" +
            "  rs2st.[Radar], \r\n" +
            "  rstclt.[Radar], \r\n" +
            "  ratuts.[Radar], \r\n" +
            "  vpobt.[Vessel], \r\n" +
            "  rst.[Radome] \r\n" +
            "FROM [TimeseriesView] t \r\n" +
            "  LEFT JOIN [BinaryTimeseries] bt ON(t.[Id] = bt.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseries] bots ON(t.[Id] = bots.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigationOffPositionTimeseries] aatnopt ON(t.[Id] = aatnopt.[Id] ) \r\n" +
            "  LEFT JOIN [DeviceEnabledTimeseries] det ON(t.[Id] = det.[Id] ) \r\n" +
            "  LEFT JOIN [MediaProxySessionEnabledTimeseries] mpset ON(t.[Id] = mpset.[Id] ) \r\n" +
            "  LEFT JOIN [MediaServiceEnabledTimeseries] mset ON(t.[Id] = mset.[Id] ) \r\n" +
            "  LEFT JOIN [RadarAutomaticSensitivityTimeControlTimeseries] rastct ON(t.[Id] = rastct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector1Timeseries] rbs1t ON(t.[Id] = rbs1t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector2Timeseries] rbs2t ON(t.[Id] = rbs2t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableAutomaticFrequencyControlTimeseries] reafct ON(t.[Id] = reafct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableFastTimeConstantTimeseries] reftct ON(t.[Id] = reftct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableSensitivityTimeControlTimeseries] restct ON(t.[Id] = restct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPowerOnTimeseries] rpot ON(t.[Id] = rpot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSaveSettingsTimeseries] rsst ON(t.[Id] = rsst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTrackingTimeseries] rtt ON(t.[Id] = rtt.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseries] byts ON(t.[Id] = byts.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseries] dtt ON(t.[Id] = dtt.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseries] dt ON(t.[Id] = dt.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSAltitudeTimeseries] gats ON(t.[Id] = gats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLatitudeTimeseries] glats ON(t.[Id] = glats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLongitudeTimeseries] glots ON(t.[Id] = glots.[Id] ) \r\n" +
            "  LEFT JOIN [GyroCourseTimeseries] gct ON(t.[Id] = gct.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingMagneticNorthTimeseries] ghmnt ON(t.[Id] = ghmnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingTrueNorthTimeseries] ghtnt ON(t.[Id] = ghtnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroPitchTimeseries] gpt ON(t.[Id] = gpt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRateOfTurnTimeseries] grott ON(t.[Id] = grott.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRollTimeseries] grt ON(t.[Id] = grt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroSpeedTimeseries] gst ON(t.[Id] = gst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLatitudeTimeseries] rlats ON(t.[Id] = rlats.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLongitudeTimeseries] rlots ON(t.[Id] = rlots.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeDewPointTimeseries] rdpt ON(t.[Id] = rdpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomePressureTimeseries] rpt ON(t.[Id] = rpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeTemperatureTimeseries] rtets ON(t.[Id] = rtets.[Id] ) \r\n" +
            "  LEFT JOIN [VesselDraughtTimeseries] vdt ON(t.[Id] = vdt.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLatitudeTimeseries] vlats ON(t.[Id] = vlats.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLongitudeTimeseries] vlots ON(t.[Id] = vlots.[Id] ) \r\n" +
            "  LEFT JOIN [ViewZoomLevelTimeseries] vzlt ON(t.[Id] = vzlt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAbsoluteHumidityTimeseries] wsaht ON(t.[Id] = wsaht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAirTemperatureTimeseries] wsatt ON(t.[Id] = wsatt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationBarometricPressureTimeseries] wsbpt ON(t.[Id] = wsbpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationDewPointTimeseries] wsdpt ON(t.[Id] = wsdpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationRelativeHumidityTimeseries] wsrht ON(t.[Id] = wsrht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWaterTemperatureTimeseries] wswtt ON(t.[Id] = wswtt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindDirectionTimeseries] wswdt ON(t.[Id] = wswdt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindSpeedTimeseries] wswst ON(t.[Id] = wswst.[Id] ) \r\n" +
            "  LEFT JOIN [GeoPosition2DTimeseries] gp2d ON(t.[Id] = gp2d.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigationPositionTimeseries] aatnpt ON(t.[Id] = aatnpt.[Id] ) \r\n" +
            "  LEFT JOIN [GeoPosition3DTimeseries] gp3d ON(t.[Id] = gp3d.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseries] gt ON(t.[Id] = gt.[Id] ) \r\n" +
            "  LEFT JOIN [Int16Timeseries] i16t ON(t.[Id] = i16t.[Id] ) \r\n" +
            "  LEFT JOIN [Int32Timeseries] i32t ON(t.[Id] = i32t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarAzimuthOffsetTimeseries] raot ON(t.[Id] = raot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantLevelTimeseries] rftclt ON(t.[Id] = rftclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantModeTimeseries] rftcmt ON(t.[Id] = rftcmt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPulseTimeseries] rapts ON(t.[Id] = rapts.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1EndTimeseries] rs1et ON(t.[Id] = rs1et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1StartTimeseries] rs1st ON(t.[Id] = rs1st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2EndTimeseries] rs2et ON(t.[Id] = rs2et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2StartTimeseries] rs2st ON(t.[Id] = rs2st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSensitivityTimeControlLevelTimeseries] rstclt ON(t.[Id] = rstclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTuningTimeseries] ratuts ON(t.[Id] = ratuts.[Id] ) \r\n" +
            "  LEFT JOIN [VesselPersonsOnBoardTimeseries] vpobt ON(t.[Id] = vpobt.[Id] ) \r\n" +
            "  LEFT JOIN [Int64Timeseries] i64t ON(t.[Id] = i64t.[Id] ) \r\n" +
            "  LEFT JOIN [Position2DTimeseries] p2d ON(t.[Id] = p2d.[Id] ) \r\n" +
            "  LEFT JOIN [Position3DTimeseries] p3d ON(t.[Id] = p3d.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseries] rt ON(t.[Id] = rt.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseries] st ON(t.[Id] = st.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseries] sits ON(t.[Id] = sits.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseries] stts ON(t.[Id] = stts.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseries] tst ON(t.[Id] = tst.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16Timeseries] u16t ON(t.[Id] = u16t.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32Timeseries] u32t ON(t.[Id] = u32t.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeStatusTimeseries] rst ON(t.[Id] = rst.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64Timeseries] u64t ON(t.[Id] = u64t.[Id] ) \r\n";

        public const string BaseViewName = "TimeseriesView";
        public const string ViewAliasName = "t";

        public const int T_ID_FIELD_ID = 0;
        public const int T_KIND_FIELD_ID = 1;
        public const int T_ROWVERSION_FIELD_ID = 2;
        public const int T_CATALOG_FIELD_ID = 3;
        public const int T_NAME_FIELD_ID = 4;
        public const int T_MAXRETENTION_FIELD_ID = 5;
        public const int AATNOPT_AIDTONAVIGATION_FIELD_ID = 6;
        public const int DET_DEVICE_FIELD_ID = 7;
        public const int MPSET_PROXYSESSION_FIELD_ID = 8;
        public const int MSET_SERVICE_FIELD_ID = 9;
        public const int RASTCT_RADAR_FIELD_ID = 10;
        public const int RBS1T_RADAR_FIELD_ID = 11;
        public const int RBS2T_RADAR_FIELD_ID = 12;
        public const int REAFCT_RADAR_FIELD_ID = 13;
        public const int REFTCT_RADAR_FIELD_ID = 14;
        public const int RESTCT_RADAR_FIELD_ID = 15;
        public const int RPOT_RADAR_FIELD_ID = 16;
        public const int RSST_RADAR_FIELD_ID = 17;
        public const int RTT_RADAR_FIELD_ID = 18;
        public const int GATS_GNSSDEVICE_FIELD_ID = 19;
        public const int GLATS_GNSSDEVICE_FIELD_ID = 20;
        public const int GLOTS_GNSSDEVICE_FIELD_ID = 21;
        public const int GCT_GYRODEVICE_FIELD_ID = 22;
        public const int GHMNT_GYRODEVICE_FIELD_ID = 23;
        public const int GHTNT_GYRODEVICE_FIELD_ID = 24;
        public const int GPT_GYRODEVICE_FIELD_ID = 25;
        public const int GROTT_GYRODEVICE_FIELD_ID = 26;
        public const int GRT_GYRODEVICE_FIELD_ID = 27;
        public const int GST_GYRODEVICE_FIELD_ID = 28;
        public const int RLATS_RADAR_FIELD_ID = 29;
        public const int RLOTS_RADAR_FIELD_ID = 30;
        public const int RDPT_RADOME_FIELD_ID = 31;
        public const int RPT_RADOME_FIELD_ID = 32;
        public const int RTETS_RADOME_FIELD_ID = 33;
        public const int VDT_VESSEL_FIELD_ID = 34;
        public const int VLATS_VIEW_FIELD_ID = 35;
        public const int VLOTS_VIEW_FIELD_ID = 36;
        public const int VZLT_VIEW_FIELD_ID = 37;
        public const int WSAHT_WEATHERSTATION_FIELD_ID = 38;
        public const int WSATT_WEATHERSTATION_FIELD_ID = 39;
        public const int WSBPT_WEATHERSTATION_FIELD_ID = 40;
        public const int WSDPT_WEATHERSTATION_FIELD_ID = 41;
        public const int WSRHT_WEATHERSTATION_FIELD_ID = 42;
        public const int WSWTT_WEATHERSTATION_FIELD_ID = 43;
        public const int WSWDT_WEATHERSTATION_FIELD_ID = 44;
        public const int WSWST_WEATHERSTATION_FIELD_ID = 45;
        public const int AATNPT_AIDTONAVIGATION_FIELD_ID = 46;
        public const int RAOT_RADAR_FIELD_ID = 47;
        public const int RFTCLT_RADAR_FIELD_ID = 48;
        public const int RFTCMT_RADAR_FIELD_ID = 49;
        public const int RAPTS_RADAR_FIELD_ID = 50;
        public const int RS1ET_RADAR_FIELD_ID = 51;
        public const int RS1ST_RADAR_FIELD_ID = 52;
        public const int RS2ET_RADAR_FIELD_ID = 53;
        public const int RS2ST_RADAR_FIELD_ID = 54;
        public const int RSTCLT_RADAR_FIELD_ID = 55;
        public const int RATUTS_RADAR_FIELD_ID = 56;
        public const int VPOBT_VESSEL_FIELD_ID = 57;
        public const int RST_RADOME_FIELD_ID = 58;
        public ComplexTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( T_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( T_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( T_ROWVERSION_FIELD_ID );
            }
        }
        public Guid? Catalog
        {
            get
            {
                return GetNullableGuid( T_CATALOG_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( T_NAME_FIELD_ID );
            }
        }
        public TimeSpan MaxRetention
        {
            get
            {
                return new TimeSpan( GetInt64( T_MAXRETENTION_FIELD_ID ) );
            }
        }
        public Guid? AisAidToNavigationOffPositionTimeseriesAidToNavigation
        {
            get
            {
                return GetNullableGuid( AATNOPT_AIDTONAVIGATION_FIELD_ID );
            }
        }
        public Guid? DeviceEnabledTimeseriesDevice
        {
            get
            {
                return GetNullableGuid( DET_DEVICE_FIELD_ID );
            }
        }
        public Guid? MediaProxySessionEnabledTimeseriesProxySession
        {
            get
            {
                return GetNullableGuid( MPSET_PROXYSESSION_FIELD_ID );
            }
        }
        public Guid? MediaServiceEnabledTimeseriesService
        {
            get
            {
                return GetNullableGuid( MSET_SERVICE_FIELD_ID );
            }
        }
        public Guid? RadarAutomaticSensitivityTimeControlTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RASTCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarBlankSector1TimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RBS1T_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarBlankSector2TimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RBS2T_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarEnableAutomaticFrequencyControlTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( REAFCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarEnableFastTimeConstantTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( REFTCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarEnableSensitivityTimeControlTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RESTCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarPowerOnTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RPOT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSaveSettingsTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RSST_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarTrackingTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RTT_RADAR_FIELD_ID );
            }
        }
        public Guid? GNSSAltitudeTimeseriesGNSSDevice
        {
            get
            {
                return GetNullableGuid( GATS_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? GNSSLatitudeTimeseriesGNSSDevice
        {
            get
            {
                return GetNullableGuid( GLATS_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? GNSSLongitudeTimeseriesGNSSDevice
        {
            get
            {
                return GetNullableGuid( GLOTS_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? GyroCourseTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GCT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroHeadingMagneticNorthTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GHMNT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroHeadingTrueNorthTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GHTNT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroPitchTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GPT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroRateOfTurnTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GROTT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroRollTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GRT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroSpeedTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GST_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? RadarLatitudeTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RLATS_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarLongitudeTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RLOTS_RADAR_FIELD_ID );
            }
        }
        public Guid? RadomeDewPointTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RDPT_RADOME_FIELD_ID );
            }
        }
        public Guid? RadomePressureTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RPT_RADOME_FIELD_ID );
            }
        }
        public Guid? RadomeTemperatureTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RTETS_RADOME_FIELD_ID );
            }
        }
        public Guid? VesselDraughtTimeseriesVessel
        {
            get
            {
                return GetNullableGuid( VDT_VESSEL_FIELD_ID );
            }
        }
        public Guid? ViewLatitudeTimeseriesView
        {
            get
            {
                return GetNullableGuid( VLATS_VIEW_FIELD_ID );
            }
        }
        public Guid? ViewLongitudeTimeseriesView
        {
            get
            {
                return GetNullableGuid( VLOTS_VIEW_FIELD_ID );
            }
        }
        public Guid? ViewZoomLevelTimeseriesView
        {
            get
            {
                return GetNullableGuid( VZLT_VIEW_FIELD_ID );
            }
        }
        public Guid? WeatherStationAbsoluteHumidityTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSAHT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationAirTemperatureTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSATT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationBarometricPressureTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSBPT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationDewPointTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSDPT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationRelativeHumidityTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSRHT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationWaterTemperatureTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSWTT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationWindDirectionTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSWDT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationWindSpeedTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSWST_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? AisAidToNavigationPositionTimeseriesAidToNavigation
        {
            get
            {
                return GetNullableGuid( AATNPT_AIDTONAVIGATION_FIELD_ID );
            }
        }
        public Guid? RadarAzimuthOffsetTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RAOT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarFastTimeConstantLevelTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RFTCLT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarFastTimeConstantModeTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RFTCMT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarPulseTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RAPTS_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector1EndTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS1ET_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector1StartTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS1ST_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector2EndTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS2ET_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector2StartTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS2ST_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSensitivityTimeControlLevelTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RSTCLT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarTuningTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RATUTS_RADAR_FIELD_ID );
            }
        }
        public Guid? VesselPersonsOnBoardTimeseriesVessel
        {
            get
            {
                return GetNullableGuid( VPOBT_VESSEL_FIELD_ID );
            }
        }
        public Guid? RadomeStatusTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RST_RADOME_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.BooleanTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.AisAidToNavigationOffPositionTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( AisAidToNavigationOffPositionTimeseriesAidToNavigation );
                }
                break;
                case Types.Kind.DeviceEnabledTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( DeviceEnabledTimeseriesDevice );
                }
                break;
                case Types.Kind.MediaProxySessionEnabledTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( MediaProxySessionEnabledTimeseriesProxySession );
                }
                break;
                case Types.Kind.MediaServiceEnabledTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( MediaServiceEnabledTimeseriesService );
                }
                break;
                case Types.Kind.RadarAutomaticSensitivityTimeControlTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarAutomaticSensitivityTimeControlTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarBlankSector1Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarBlankSector1TimeseriesRadar );
                }
                break;
                case Types.Kind.RadarBlankSector2Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarBlankSector2TimeseriesRadar );
                }
                break;
                case Types.Kind.RadarEnableAutomaticFrequencyControlTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarEnableAutomaticFrequencyControlTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarEnableFastTimeConstantTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarEnableFastTimeConstantTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarEnableSensitivityTimeControlTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarEnableSensitivityTimeControlTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarPowerOnTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarPowerOnTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSaveSettingsTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSaveSettingsTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarTrackingTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarTrackingTimeseriesRadar );
                }
                break;
                case Types.Kind.ByteTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.DateTimeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.DoubleTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.GNSSAltitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GNSSAltitudeTimeseriesGNSSDevice );
                }
                break;
                case Types.Kind.GNSSLatitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GNSSLatitudeTimeseriesGNSSDevice );
                }
                break;
                case Types.Kind.GNSSLongitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GNSSLongitudeTimeseriesGNSSDevice );
                }
                break;
                case Types.Kind.GyroCourseTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroCourseTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroHeadingMagneticNorthTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroHeadingMagneticNorthTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroHeadingTrueNorthTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroHeadingTrueNorthTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroPitchTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroPitchTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroRateOfTurnTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroRateOfTurnTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroRollTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroRollTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroSpeedTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroSpeedTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.RadarLatitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarLatitudeTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarLongitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarLongitudeTimeseriesRadar );
                }
                break;
                case Types.Kind.RadomeDewPointTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadomeDewPointTimeseriesRadome );
                }
                break;
                case Types.Kind.RadomePressureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadomePressureTimeseriesRadome );
                }
                break;
                case Types.Kind.RadomeTemperatureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadomeTemperatureTimeseriesRadome );
                }
                break;
                case Types.Kind.VesselDraughtTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( VesselDraughtTimeseriesVessel );
                }
                break;
                case Types.Kind.ViewLatitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( ViewLatitudeTimeseriesView );
                }
                break;
                case Types.Kind.ViewLongitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( ViewLongitudeTimeseriesView );
                }
                break;
                case Types.Kind.ViewZoomLevelTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( ViewZoomLevelTimeseriesView );
                }
                break;
                case Types.Kind.WeatherStationAbsoluteHumidityTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationAbsoluteHumidityTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationAirTemperatureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationAirTemperatureTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationBarometricPressureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationBarometricPressureTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationDewPointTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationDewPointTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationRelativeHumidityTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationRelativeHumidityTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationWaterTemperatureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationWaterTemperatureTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationWindDirectionTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationWindDirectionTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationWindSpeedTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationWindSpeedTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.GeoPosition2DTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.AisAidToNavigationPositionTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( AisAidToNavigationPositionTimeseriesAidToNavigation );
                }
                break;
                case Types.Kind.GeoPosition3DTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.GuidTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.Int16Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.Int32Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.RadarAzimuthOffsetTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarAzimuthOffsetTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarFastTimeConstantLevelTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarFastTimeConstantLevelTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarFastTimeConstantModeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarFastTimeConstantModeTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarPulseTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarPulseTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector1EndTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSector1EndTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector1StartTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSector1StartTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector2EndTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSector2EndTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector2StartTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSector2StartTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSensitivityTimeControlLevelTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSensitivityTimeControlLevelTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarTuningTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarTuningTimeseriesRadar );
                }
                break;
                case Types.Kind.VesselPersonsOnBoardTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( VesselPersonsOnBoardTimeseriesVessel );
                }
                break;
                case Types.Kind.Int64Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.Position2DTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.Position3DTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.ReferenceTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.SByteTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.SingleTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.StringTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.TimeSpanTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.UInt16Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.UInt32Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.RadomeStatusTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadomeStatusTimeseriesRadome );
                }
                break;
                case Types.Kind.UInt64Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public TimeseriesObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BinaryTimeseries:
                {
                    return new BinaryTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.BooleanTimeseries:
                {
                    return new BooleanTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.AisAidToNavigationOffPositionTimeseries:
                {
                    return new AisAidToNavigationOffPositionTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, AisAidToNavigationOffPositionTimeseriesAidToNavigation );
                }
                case Types.Kind.DeviceEnabledTimeseries:
                {
                    return new DeviceEnabledTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, DeviceEnabledTimeseriesDevice );
                }
                case Types.Kind.MediaProxySessionEnabledTimeseries:
                {
                    return new MediaProxySessionEnabledTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, MediaProxySessionEnabledTimeseriesProxySession );
                }
                case Types.Kind.MediaServiceEnabledTimeseries:
                {
                    return new MediaServiceEnabledTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, MediaServiceEnabledTimeseriesService );
                }
                case Types.Kind.RadarAutomaticSensitivityTimeControlTimeseries:
                {
                    return new RadarAutomaticSensitivityTimeControlTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarAutomaticSensitivityTimeControlTimeseriesRadar );
                }
                case Types.Kind.RadarBlankSector1Timeseries:
                {
                    return new RadarBlankSector1TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarBlankSector1TimeseriesRadar );
                }
                case Types.Kind.RadarBlankSector2Timeseries:
                {
                    return new RadarBlankSector2TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarBlankSector2TimeseriesRadar );
                }
                case Types.Kind.RadarEnableAutomaticFrequencyControlTimeseries:
                {
                    return new RadarEnableAutomaticFrequencyControlTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarEnableAutomaticFrequencyControlTimeseriesRadar );
                }
                case Types.Kind.RadarEnableFastTimeConstantTimeseries:
                {
                    return new RadarEnableFastTimeConstantTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarEnableFastTimeConstantTimeseriesRadar );
                }
                case Types.Kind.RadarEnableSensitivityTimeControlTimeseries:
                {
                    return new RadarEnableSensitivityTimeControlTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarEnableSensitivityTimeControlTimeseriesRadar );
                }
                case Types.Kind.RadarPowerOnTimeseries:
                {
                    return new RadarPowerOnTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarPowerOnTimeseriesRadar );
                }
                case Types.Kind.RadarSaveSettingsTimeseries:
                {
                    return new RadarSaveSettingsTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSaveSettingsTimeseriesRadar );
                }
                case Types.Kind.RadarTrackingTimeseries:
                {
                    return new RadarTrackingTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarTrackingTimeseriesRadar );
                }
                case Types.Kind.ByteTimeseries:
                {
                    return new ByteTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.DateTimeTimeseries:
                {
                    return new DateTimeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.DoubleTimeseries:
                {
                    return new DoubleTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.GNSSAltitudeTimeseries:
                {
                    return new GNSSAltitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GNSSAltitudeTimeseriesGNSSDevice );
                }
                case Types.Kind.GNSSLatitudeTimeseries:
                {
                    return new GNSSLatitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GNSSLatitudeTimeseriesGNSSDevice );
                }
                case Types.Kind.GNSSLongitudeTimeseries:
                {
                    return new GNSSLongitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GNSSLongitudeTimeseriesGNSSDevice );
                }
                case Types.Kind.GyroCourseTimeseries:
                {
                    return new GyroCourseTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroCourseTimeseriesGyroDevice );
                }
                case Types.Kind.GyroHeadingMagneticNorthTimeseries:
                {
                    return new GyroHeadingMagneticNorthTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroHeadingMagneticNorthTimeseriesGyroDevice );
                }
                case Types.Kind.GyroHeadingTrueNorthTimeseries:
                {
                    return new GyroHeadingTrueNorthTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroHeadingTrueNorthTimeseriesGyroDevice );
                }
                case Types.Kind.GyroPitchTimeseries:
                {
                    return new GyroPitchTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroPitchTimeseriesGyroDevice );
                }
                case Types.Kind.GyroRateOfTurnTimeseries:
                {
                    return new GyroRateOfTurnTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroRateOfTurnTimeseriesGyroDevice );
                }
                case Types.Kind.GyroRollTimeseries:
                {
                    return new GyroRollTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroRollTimeseriesGyroDevice );
                }
                case Types.Kind.GyroSpeedTimeseries:
                {
                    return new GyroSpeedTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroSpeedTimeseriesGyroDevice );
                }
                case Types.Kind.RadarLatitudeTimeseries:
                {
                    return new RadarLatitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarLatitudeTimeseriesRadar );
                }
                case Types.Kind.RadarLongitudeTimeseries:
                {
                    return new RadarLongitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarLongitudeTimeseriesRadar );
                }
                case Types.Kind.RadomeDewPointTimeseries:
                {
                    return new RadomeDewPointTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadomeDewPointTimeseriesRadome );
                }
                case Types.Kind.RadomePressureTimeseries:
                {
                    return new RadomePressureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadomePressureTimeseriesRadome );
                }
                case Types.Kind.RadomeTemperatureTimeseries:
                {
                    return new RadomeTemperatureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadomeTemperatureTimeseriesRadome );
                }
                case Types.Kind.VesselDraughtTimeseries:
                {
                    return new VesselDraughtTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, VesselDraughtTimeseriesVessel );
                }
                case Types.Kind.ViewLatitudeTimeseries:
                {
                    return new ViewLatitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, ViewLatitudeTimeseriesView );
                }
                case Types.Kind.ViewLongitudeTimeseries:
                {
                    return new ViewLongitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, ViewLongitudeTimeseriesView );
                }
                case Types.Kind.ViewZoomLevelTimeseries:
                {
                    return new ViewZoomLevelTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, ViewZoomLevelTimeseriesView );
                }
                case Types.Kind.WeatherStationAbsoluteHumidityTimeseries:
                {
                    return new WeatherStationAbsoluteHumidityTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationAbsoluteHumidityTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationAirTemperatureTimeseries:
                {
                    return new WeatherStationAirTemperatureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationAirTemperatureTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationBarometricPressureTimeseries:
                {
                    return new WeatherStationBarometricPressureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationBarometricPressureTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationDewPointTimeseries:
                {
                    return new WeatherStationDewPointTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationDewPointTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationRelativeHumidityTimeseries:
                {
                    return new WeatherStationRelativeHumidityTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationRelativeHumidityTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationWaterTemperatureTimeseries:
                {
                    return new WeatherStationWaterTemperatureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationWaterTemperatureTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationWindDirectionTimeseries:
                {
                    return new WeatherStationWindDirectionTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationWindDirectionTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationWindSpeedTimeseries:
                {
                    return new WeatherStationWindSpeedTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationWindSpeedTimeseriesWeatherStation );
                }
                case Types.Kind.GeoPosition2DTimeseries:
                {
                    return new GeoPosition2DTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.AisAidToNavigationPositionTimeseries:
                {
                    return new AisAidToNavigationPositionTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, AisAidToNavigationPositionTimeseriesAidToNavigation );
                }
                case Types.Kind.GeoPosition3DTimeseries:
                {
                    return new GeoPosition3DTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.GuidTimeseries:
                {
                    return new GuidTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.Int16Timeseries:
                {
                    return new Int16TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.Int32Timeseries:
                {
                    return new Int32TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.RadarAzimuthOffsetTimeseries:
                {
                    return new RadarAzimuthOffsetTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarAzimuthOffsetTimeseriesRadar );
                }
                case Types.Kind.RadarFastTimeConstantLevelTimeseries:
                {
                    return new RadarFastTimeConstantLevelTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarFastTimeConstantLevelTimeseriesRadar );
                }
                case Types.Kind.RadarFastTimeConstantModeTimeseries:
                {
                    return new RadarFastTimeConstantModeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarFastTimeConstantModeTimeseriesRadar );
                }
                case Types.Kind.RadarPulseTimeseries:
                {
                    return new RadarPulseTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarPulseTimeseriesRadar );
                }
                case Types.Kind.RadarSector1EndTimeseries:
                {
                    return new RadarSector1EndTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSector1EndTimeseriesRadar );
                }
                case Types.Kind.RadarSector1StartTimeseries:
                {
                    return new RadarSector1StartTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSector1StartTimeseriesRadar );
                }
                case Types.Kind.RadarSector2EndTimeseries:
                {
                    return new RadarSector2EndTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSector2EndTimeseriesRadar );
                }
                case Types.Kind.RadarSector2StartTimeseries:
                {
                    return new RadarSector2StartTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSector2StartTimeseriesRadar );
                }
                case Types.Kind.RadarSensitivityTimeControlLevelTimeseries:
                {
                    return new RadarSensitivityTimeControlLevelTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSensitivityTimeControlLevelTimeseriesRadar );
                }
                case Types.Kind.RadarTuningTimeseries:
                {
                    return new RadarTuningTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarTuningTimeseriesRadar );
                }
                case Types.Kind.VesselPersonsOnBoardTimeseries:
                {
                    return new VesselPersonsOnBoardTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, VesselPersonsOnBoardTimeseriesVessel );
                }
                case Types.Kind.Int64Timeseries:
                {
                    return new Int64TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.Position2DTimeseries:
                {
                    return new Position2DTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.Position3DTimeseries:
                {
                    return new Position3DTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.ReferenceTimeseries:
                {
                    return new ReferenceTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.SByteTimeseries:
                {
                    return new SByteTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.SingleTimeseries:
                {
                    return new SingleTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.StringTimeseries:
                {
                    return new StringTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.TimeSpanTimeseries:
                {
                    return new TimeSpanTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.UInt16Timeseries:
                {
                    return new UInt16TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.UInt32Timeseries:
                {
                    return new UInt32TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.RadomeStatusTimeseries:
                {
                    return new RadomeStatusTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadomeStatusTimeseriesRadome );
                }
                case Types.Kind.UInt64Timeseries:
                {
                    return new UInt64TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexBooleanTimeseriesDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  bots.[Id], \r\n" +
            "  bots.[EntityType], \r\n" +
            "  bots.[RowVersion], \r\n" +
            "  bots.[Catalog], \r\n" +
            "  bots.[Name], \r\n" +
            "  bots.[MaxRetention], \r\n" +
            "  aatnopt.[AidToNavigation], \r\n" +
            "  det.[Device], \r\n" +
            "  mpset.[ProxySession], \r\n" +
            "  mset.[Service], \r\n" +
            "  rastct.[Radar], \r\n" +
            "  rbs1t.[Radar], \r\n" +
            "  rbs2t.[Radar], \r\n" +
            "  reafct.[Radar], \r\n" +
            "  reftct.[Radar], \r\n" +
            "  restct.[Radar], \r\n" +
            "  rpot.[Radar], \r\n" +
            "  rsst.[Radar], \r\n" +
            "  rtt.[Radar] \r\n" +
            "FROM [BooleanTimeseriesView] bots \r\n" +
            "  LEFT JOIN [AisAidToNavigationOffPositionTimeseries] aatnopt ON(bots.[Id] = aatnopt.[Id] ) \r\n" +
            "  LEFT JOIN [DeviceEnabledTimeseries] det ON(bots.[Id] = det.[Id] ) \r\n" +
            "  LEFT JOIN [MediaProxySessionEnabledTimeseries] mpset ON(bots.[Id] = mpset.[Id] ) \r\n" +
            "  LEFT JOIN [MediaServiceEnabledTimeseries] mset ON(bots.[Id] = mset.[Id] ) \r\n" +
            "  LEFT JOIN [RadarAutomaticSensitivityTimeControlTimeseries] rastct ON(bots.[Id] = rastct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector1Timeseries] rbs1t ON(bots.[Id] = rbs1t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector2Timeseries] rbs2t ON(bots.[Id] = rbs2t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableAutomaticFrequencyControlTimeseries] reafct ON(bots.[Id] = reafct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableFastTimeConstantTimeseries] reftct ON(bots.[Id] = reftct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableSensitivityTimeControlTimeseries] restct ON(bots.[Id] = restct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPowerOnTimeseries] rpot ON(bots.[Id] = rpot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSaveSettingsTimeseries] rsst ON(bots.[Id] = rsst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTrackingTimeseries] rtt ON(bots.[Id] = rtt.[Id] ) \r\n";

        public const string BaseViewName = "BooleanTimeseriesView";
        public const string ViewAliasName = "bots";

        public const int BOTS_ID_FIELD_ID = 0;
        public const int BOTS_KIND_FIELD_ID = 1;
        public const int BOTS_ROWVERSION_FIELD_ID = 2;
        public const int BOTS_CATALOG_FIELD_ID = 3;
        public const int BOTS_NAME_FIELD_ID = 4;
        public const int BOTS_MAXRETENTION_FIELD_ID = 5;
        public const int AATNOPT_AIDTONAVIGATION_FIELD_ID = 6;
        public const int DET_DEVICE_FIELD_ID = 7;
        public const int MPSET_PROXYSESSION_FIELD_ID = 8;
        public const int MSET_SERVICE_FIELD_ID = 9;
        public const int RASTCT_RADAR_FIELD_ID = 10;
        public const int RBS1T_RADAR_FIELD_ID = 11;
        public const int RBS2T_RADAR_FIELD_ID = 12;
        public const int REAFCT_RADAR_FIELD_ID = 13;
        public const int REFTCT_RADAR_FIELD_ID = 14;
        public const int RESTCT_RADAR_FIELD_ID = 15;
        public const int RPOT_RADAR_FIELD_ID = 16;
        public const int RSST_RADAR_FIELD_ID = 17;
        public const int RTT_RADAR_FIELD_ID = 18;
        public ComplexBooleanTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( BOTS_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( BOTS_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( BOTS_ROWVERSION_FIELD_ID );
            }
        }
        public Guid? Catalog
        {
            get
            {
                return GetNullableGuid( BOTS_CATALOG_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( BOTS_NAME_FIELD_ID );
            }
        }
        public TimeSpan MaxRetention
        {
            get
            {
                return new TimeSpan( GetInt64( BOTS_MAXRETENTION_FIELD_ID ) );
            }
        }
        public Guid? AisAidToNavigationOffPositionTimeseriesAidToNavigation
        {
            get
            {
                return GetNullableGuid( AATNOPT_AIDTONAVIGATION_FIELD_ID );
            }
        }
        public Guid? DeviceEnabledTimeseriesDevice
        {
            get
            {
                return GetNullableGuid( DET_DEVICE_FIELD_ID );
            }
        }
        public Guid? MediaProxySessionEnabledTimeseriesProxySession
        {
            get
            {
                return GetNullableGuid( MPSET_PROXYSESSION_FIELD_ID );
            }
        }
        public Guid? MediaServiceEnabledTimeseriesService
        {
            get
            {
                return GetNullableGuid( MSET_SERVICE_FIELD_ID );
            }
        }
        public Guid? RadarAutomaticSensitivityTimeControlTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RASTCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarBlankSector1TimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RBS1T_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarBlankSector2TimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RBS2T_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarEnableAutomaticFrequencyControlTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( REAFCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarEnableFastTimeConstantTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( REFTCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarEnableSensitivityTimeControlTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RESTCT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarPowerOnTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RPOT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSaveSettingsTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RSST_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarTrackingTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RTT_RADAR_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BooleanTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.AisAidToNavigationOffPositionTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( AisAidToNavigationOffPositionTimeseriesAidToNavigation );
                }
                break;
                case Types.Kind.DeviceEnabledTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( DeviceEnabledTimeseriesDevice );
                }
                break;
                case Types.Kind.MediaProxySessionEnabledTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( MediaProxySessionEnabledTimeseriesProxySession );
                }
                break;
                case Types.Kind.MediaServiceEnabledTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( MediaServiceEnabledTimeseriesService );
                }
                break;
                case Types.Kind.RadarAutomaticSensitivityTimeControlTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarAutomaticSensitivityTimeControlTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarBlankSector1Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarBlankSector1TimeseriesRadar );
                }
                break;
                case Types.Kind.RadarBlankSector2Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarBlankSector2TimeseriesRadar );
                }
                break;
                case Types.Kind.RadarEnableAutomaticFrequencyControlTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarEnableAutomaticFrequencyControlTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarEnableFastTimeConstantTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarEnableFastTimeConstantTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarEnableSensitivityTimeControlTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarEnableSensitivityTimeControlTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarPowerOnTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarPowerOnTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSaveSettingsTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSaveSettingsTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarTrackingTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarTrackingTimeseriesRadar );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public BooleanTimeseriesObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.BooleanTimeseries:
                {
                    return new BooleanTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.AisAidToNavigationOffPositionTimeseries:
                {
                    return new AisAidToNavigationOffPositionTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, AisAidToNavigationOffPositionTimeseriesAidToNavigation );
                }
                case Types.Kind.DeviceEnabledTimeseries:
                {
                    return new DeviceEnabledTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, DeviceEnabledTimeseriesDevice );
                }
                case Types.Kind.MediaProxySessionEnabledTimeseries:
                {
                    return new MediaProxySessionEnabledTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, MediaProxySessionEnabledTimeseriesProxySession );
                }
                case Types.Kind.MediaServiceEnabledTimeseries:
                {
                    return new MediaServiceEnabledTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, MediaServiceEnabledTimeseriesService );
                }
                case Types.Kind.RadarAutomaticSensitivityTimeControlTimeseries:
                {
                    return new RadarAutomaticSensitivityTimeControlTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarAutomaticSensitivityTimeControlTimeseriesRadar );
                }
                case Types.Kind.RadarBlankSector1Timeseries:
                {
                    return new RadarBlankSector1TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarBlankSector1TimeseriesRadar );
                }
                case Types.Kind.RadarBlankSector2Timeseries:
                {
                    return new RadarBlankSector2TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarBlankSector2TimeseriesRadar );
                }
                case Types.Kind.RadarEnableAutomaticFrequencyControlTimeseries:
                {
                    return new RadarEnableAutomaticFrequencyControlTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarEnableAutomaticFrequencyControlTimeseriesRadar );
                }
                case Types.Kind.RadarEnableFastTimeConstantTimeseries:
                {
                    return new RadarEnableFastTimeConstantTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarEnableFastTimeConstantTimeseriesRadar );
                }
                case Types.Kind.RadarEnableSensitivityTimeControlTimeseries:
                {
                    return new RadarEnableSensitivityTimeControlTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarEnableSensitivityTimeControlTimeseriesRadar );
                }
                case Types.Kind.RadarPowerOnTimeseries:
                {
                    return new RadarPowerOnTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarPowerOnTimeseriesRadar );
                }
                case Types.Kind.RadarSaveSettingsTimeseries:
                {
                    return new RadarSaveSettingsTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSaveSettingsTimeseriesRadar );
                }
                case Types.Kind.RadarTrackingTimeseries:
                {
                    return new RadarTrackingTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarTrackingTimeseriesRadar );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexDoubleTimeseriesDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  dt.[Id], \r\n" +
            "  dt.[EntityType], \r\n" +
            "  dt.[RowVersion], \r\n" +
            "  dt.[Catalog], \r\n" +
            "  dt.[Name], \r\n" +
            "  dt.[MaxRetention], \r\n" +
            "  gats.[GNSSDevice], \r\n" +
            "  glats.[GNSSDevice], \r\n" +
            "  glots.[GNSSDevice], \r\n" +
            "  gct.[GyroDevice], \r\n" +
            "  ghmnt.[GyroDevice], \r\n" +
            "  ghtnt.[GyroDevice], \r\n" +
            "  gpt.[GyroDevice], \r\n" +
            "  grott.[GyroDevice], \r\n" +
            "  grt.[GyroDevice], \r\n" +
            "  gst.[GyroDevice], \r\n" +
            "  rlats.[Radar], \r\n" +
            "  rlots.[Radar], \r\n" +
            "  rdpt.[Radome], \r\n" +
            "  rpt.[Radome], \r\n" +
            "  rtets.[Radome], \r\n" +
            "  vdt.[Vessel], \r\n" +
            "  vlats.[View], \r\n" +
            "  vlots.[View], \r\n" +
            "  vzlt.[View], \r\n" +
            "  wsaht.[WeatherStation], \r\n" +
            "  wsatt.[WeatherStation], \r\n" +
            "  wsbpt.[WeatherStation], \r\n" +
            "  wsdpt.[WeatherStation], \r\n" +
            "  wsrht.[WeatherStation], \r\n" +
            "  wswtt.[WeatherStation], \r\n" +
            "  wswdt.[WeatherStation], \r\n" +
            "  wswst.[WeatherStation] \r\n" +
            "FROM [DoubleTimeseriesView] dt \r\n" +
            "  LEFT JOIN [GNSSAltitudeTimeseries] gats ON(dt.[Id] = gats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLatitudeTimeseries] glats ON(dt.[Id] = glats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLongitudeTimeseries] glots ON(dt.[Id] = glots.[Id] ) \r\n" +
            "  LEFT JOIN [GyroCourseTimeseries] gct ON(dt.[Id] = gct.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingMagneticNorthTimeseries] ghmnt ON(dt.[Id] = ghmnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingTrueNorthTimeseries] ghtnt ON(dt.[Id] = ghtnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroPitchTimeseries] gpt ON(dt.[Id] = gpt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRateOfTurnTimeseries] grott ON(dt.[Id] = grott.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRollTimeseries] grt ON(dt.[Id] = grt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroSpeedTimeseries] gst ON(dt.[Id] = gst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLatitudeTimeseries] rlats ON(dt.[Id] = rlats.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLongitudeTimeseries] rlots ON(dt.[Id] = rlots.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeDewPointTimeseries] rdpt ON(dt.[Id] = rdpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomePressureTimeseries] rpt ON(dt.[Id] = rpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeTemperatureTimeseries] rtets ON(dt.[Id] = rtets.[Id] ) \r\n" +
            "  LEFT JOIN [VesselDraughtTimeseries] vdt ON(dt.[Id] = vdt.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLatitudeTimeseries] vlats ON(dt.[Id] = vlats.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLongitudeTimeseries] vlots ON(dt.[Id] = vlots.[Id] ) \r\n" +
            "  LEFT JOIN [ViewZoomLevelTimeseries] vzlt ON(dt.[Id] = vzlt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAbsoluteHumidityTimeseries] wsaht ON(dt.[Id] = wsaht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAirTemperatureTimeseries] wsatt ON(dt.[Id] = wsatt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationBarometricPressureTimeseries] wsbpt ON(dt.[Id] = wsbpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationDewPointTimeseries] wsdpt ON(dt.[Id] = wsdpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationRelativeHumidityTimeseries] wsrht ON(dt.[Id] = wsrht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWaterTemperatureTimeseries] wswtt ON(dt.[Id] = wswtt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindDirectionTimeseries] wswdt ON(dt.[Id] = wswdt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindSpeedTimeseries] wswst ON(dt.[Id] = wswst.[Id] ) \r\n";

        public const string BaseViewName = "DoubleTimeseriesView";
        public const string ViewAliasName = "dt";

        public const int DT_ID_FIELD_ID = 0;
        public const int DT_KIND_FIELD_ID = 1;
        public const int DT_ROWVERSION_FIELD_ID = 2;
        public const int DT_CATALOG_FIELD_ID = 3;
        public const int DT_NAME_FIELD_ID = 4;
        public const int DT_MAXRETENTION_FIELD_ID = 5;
        public const int GATS_GNSSDEVICE_FIELD_ID = 6;
        public const int GLATS_GNSSDEVICE_FIELD_ID = 7;
        public const int GLOTS_GNSSDEVICE_FIELD_ID = 8;
        public const int GCT_GYRODEVICE_FIELD_ID = 9;
        public const int GHMNT_GYRODEVICE_FIELD_ID = 10;
        public const int GHTNT_GYRODEVICE_FIELD_ID = 11;
        public const int GPT_GYRODEVICE_FIELD_ID = 12;
        public const int GROTT_GYRODEVICE_FIELD_ID = 13;
        public const int GRT_GYRODEVICE_FIELD_ID = 14;
        public const int GST_GYRODEVICE_FIELD_ID = 15;
        public const int RLATS_RADAR_FIELD_ID = 16;
        public const int RLOTS_RADAR_FIELD_ID = 17;
        public const int RDPT_RADOME_FIELD_ID = 18;
        public const int RPT_RADOME_FIELD_ID = 19;
        public const int RTETS_RADOME_FIELD_ID = 20;
        public const int VDT_VESSEL_FIELD_ID = 21;
        public const int VLATS_VIEW_FIELD_ID = 22;
        public const int VLOTS_VIEW_FIELD_ID = 23;
        public const int VZLT_VIEW_FIELD_ID = 24;
        public const int WSAHT_WEATHERSTATION_FIELD_ID = 25;
        public const int WSATT_WEATHERSTATION_FIELD_ID = 26;
        public const int WSBPT_WEATHERSTATION_FIELD_ID = 27;
        public const int WSDPT_WEATHERSTATION_FIELD_ID = 28;
        public const int WSRHT_WEATHERSTATION_FIELD_ID = 29;
        public const int WSWTT_WEATHERSTATION_FIELD_ID = 30;
        public const int WSWDT_WEATHERSTATION_FIELD_ID = 31;
        public const int WSWST_WEATHERSTATION_FIELD_ID = 32;
        public ComplexDoubleTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( DT_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( DT_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( DT_ROWVERSION_FIELD_ID );
            }
        }
        public Guid? Catalog
        {
            get
            {
                return GetNullableGuid( DT_CATALOG_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( DT_NAME_FIELD_ID );
            }
        }
        public TimeSpan MaxRetention
        {
            get
            {
                return new TimeSpan( GetInt64( DT_MAXRETENTION_FIELD_ID ) );
            }
        }
        public Guid? GNSSAltitudeTimeseriesGNSSDevice
        {
            get
            {
                return GetNullableGuid( GATS_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? GNSSLatitudeTimeseriesGNSSDevice
        {
            get
            {
                return GetNullableGuid( GLATS_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? GNSSLongitudeTimeseriesGNSSDevice
        {
            get
            {
                return GetNullableGuid( GLOTS_GNSSDEVICE_FIELD_ID );
            }
        }
        public Guid? GyroCourseTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GCT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroHeadingMagneticNorthTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GHMNT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroHeadingTrueNorthTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GHTNT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroPitchTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GPT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroRateOfTurnTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GROTT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroRollTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GRT_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? GyroSpeedTimeseriesGyroDevice
        {
            get
            {
                return GetNullableGuid( GST_GYRODEVICE_FIELD_ID );
            }
        }
        public Guid? RadarLatitudeTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RLATS_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarLongitudeTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RLOTS_RADAR_FIELD_ID );
            }
        }
        public Guid? RadomeDewPointTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RDPT_RADOME_FIELD_ID );
            }
        }
        public Guid? RadomePressureTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RPT_RADOME_FIELD_ID );
            }
        }
        public Guid? RadomeTemperatureTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RTETS_RADOME_FIELD_ID );
            }
        }
        public Guid? VesselDraughtTimeseriesVessel
        {
            get
            {
                return GetNullableGuid( VDT_VESSEL_FIELD_ID );
            }
        }
        public Guid? ViewLatitudeTimeseriesView
        {
            get
            {
                return GetNullableGuid( VLATS_VIEW_FIELD_ID );
            }
        }
        public Guid? ViewLongitudeTimeseriesView
        {
            get
            {
                return GetNullableGuid( VLOTS_VIEW_FIELD_ID );
            }
        }
        public Guid? ViewZoomLevelTimeseriesView
        {
            get
            {
                return GetNullableGuid( VZLT_VIEW_FIELD_ID );
            }
        }
        public Guid? WeatherStationAbsoluteHumidityTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSAHT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationAirTemperatureTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSATT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationBarometricPressureTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSBPT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationDewPointTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSDPT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationRelativeHumidityTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSRHT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationWaterTemperatureTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSWTT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationWindDirectionTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSWDT_WEATHERSTATION_FIELD_ID );
            }
        }
        public Guid? WeatherStationWindSpeedTimeseriesWeatherStation
        {
            get
            {
                return GetNullableGuid( WSWST_WEATHERSTATION_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.DoubleTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.GNSSAltitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GNSSAltitudeTimeseriesGNSSDevice );
                }
                break;
                case Types.Kind.GNSSLatitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GNSSLatitudeTimeseriesGNSSDevice );
                }
                break;
                case Types.Kind.GNSSLongitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GNSSLongitudeTimeseriesGNSSDevice );
                }
                break;
                case Types.Kind.GyroCourseTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroCourseTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroHeadingMagneticNorthTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroHeadingMagneticNorthTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroHeadingTrueNorthTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroHeadingTrueNorthTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroPitchTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroPitchTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroRateOfTurnTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroRateOfTurnTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroRollTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroRollTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.GyroSpeedTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( GyroSpeedTimeseriesGyroDevice );
                }
                break;
                case Types.Kind.RadarLatitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarLatitudeTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarLongitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarLongitudeTimeseriesRadar );
                }
                break;
                case Types.Kind.RadomeDewPointTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadomeDewPointTimeseriesRadome );
                }
                break;
                case Types.Kind.RadomePressureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadomePressureTimeseriesRadome );
                }
                break;
                case Types.Kind.RadomeTemperatureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadomeTemperatureTimeseriesRadome );
                }
                break;
                case Types.Kind.VesselDraughtTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( VesselDraughtTimeseriesVessel );
                }
                break;
                case Types.Kind.ViewLatitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( ViewLatitudeTimeseriesView );
                }
                break;
                case Types.Kind.ViewLongitudeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( ViewLongitudeTimeseriesView );
                }
                break;
                case Types.Kind.ViewZoomLevelTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( ViewZoomLevelTimeseriesView );
                }
                break;
                case Types.Kind.WeatherStationAbsoluteHumidityTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationAbsoluteHumidityTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationAirTemperatureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationAirTemperatureTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationBarometricPressureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationBarometricPressureTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationDewPointTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationDewPointTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationRelativeHumidityTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationRelativeHumidityTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationWaterTemperatureTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationWaterTemperatureTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationWindDirectionTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationWindDirectionTimeseriesWeatherStation );
                }
                break;
                case Types.Kind.WeatherStationWindSpeedTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( WeatherStationWindSpeedTimeseriesWeatherStation );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public DoubleTimeseriesObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.DoubleTimeseries:
                {
                    return new DoubleTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.GNSSAltitudeTimeseries:
                {
                    return new GNSSAltitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GNSSAltitudeTimeseriesGNSSDevice );
                }
                case Types.Kind.GNSSLatitudeTimeseries:
                {
                    return new GNSSLatitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GNSSLatitudeTimeseriesGNSSDevice );
                }
                case Types.Kind.GNSSLongitudeTimeseries:
                {
                    return new GNSSLongitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GNSSLongitudeTimeseriesGNSSDevice );
                }
                case Types.Kind.GyroCourseTimeseries:
                {
                    return new GyroCourseTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroCourseTimeseriesGyroDevice );
                }
                case Types.Kind.GyroHeadingMagneticNorthTimeseries:
                {
                    return new GyroHeadingMagneticNorthTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroHeadingMagneticNorthTimeseriesGyroDevice );
                }
                case Types.Kind.GyroHeadingTrueNorthTimeseries:
                {
                    return new GyroHeadingTrueNorthTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroHeadingTrueNorthTimeseriesGyroDevice );
                }
                case Types.Kind.GyroPitchTimeseries:
                {
                    return new GyroPitchTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroPitchTimeseriesGyroDevice );
                }
                case Types.Kind.GyroRateOfTurnTimeseries:
                {
                    return new GyroRateOfTurnTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroRateOfTurnTimeseriesGyroDevice );
                }
                case Types.Kind.GyroRollTimeseries:
                {
                    return new GyroRollTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroRollTimeseriesGyroDevice );
                }
                case Types.Kind.GyroSpeedTimeseries:
                {
                    return new GyroSpeedTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, GyroSpeedTimeseriesGyroDevice );
                }
                case Types.Kind.RadarLatitudeTimeseries:
                {
                    return new RadarLatitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarLatitudeTimeseriesRadar );
                }
                case Types.Kind.RadarLongitudeTimeseries:
                {
                    return new RadarLongitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarLongitudeTimeseriesRadar );
                }
                case Types.Kind.RadomeDewPointTimeseries:
                {
                    return new RadomeDewPointTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadomeDewPointTimeseriesRadome );
                }
                case Types.Kind.RadomePressureTimeseries:
                {
                    return new RadomePressureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadomePressureTimeseriesRadome );
                }
                case Types.Kind.RadomeTemperatureTimeseries:
                {
                    return new RadomeTemperatureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadomeTemperatureTimeseriesRadome );
                }
                case Types.Kind.VesselDraughtTimeseries:
                {
                    return new VesselDraughtTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, VesselDraughtTimeseriesVessel );
                }
                case Types.Kind.ViewLatitudeTimeseries:
                {
                    return new ViewLatitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, ViewLatitudeTimeseriesView );
                }
                case Types.Kind.ViewLongitudeTimeseries:
                {
                    return new ViewLongitudeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, ViewLongitudeTimeseriesView );
                }
                case Types.Kind.ViewZoomLevelTimeseries:
                {
                    return new ViewZoomLevelTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, ViewZoomLevelTimeseriesView );
                }
                case Types.Kind.WeatherStationAbsoluteHumidityTimeseries:
                {
                    return new WeatherStationAbsoluteHumidityTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationAbsoluteHumidityTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationAirTemperatureTimeseries:
                {
                    return new WeatherStationAirTemperatureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationAirTemperatureTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationBarometricPressureTimeseries:
                {
                    return new WeatherStationBarometricPressureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationBarometricPressureTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationDewPointTimeseries:
                {
                    return new WeatherStationDewPointTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationDewPointTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationRelativeHumidityTimeseries:
                {
                    return new WeatherStationRelativeHumidityTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationRelativeHumidityTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationWaterTemperatureTimeseries:
                {
                    return new WeatherStationWaterTemperatureTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationWaterTemperatureTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationWindDirectionTimeseries:
                {
                    return new WeatherStationWindDirectionTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationWindDirectionTimeseriesWeatherStation );
                }
                case Types.Kind.WeatherStationWindSpeedTimeseries:
                {
                    return new WeatherStationWindSpeedTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, WeatherStationWindSpeedTimeseriesWeatherStation );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexGeoPosition2DTimeseriesDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  gp2d.[Id], \r\n" +
            "  gp2d.[EntityType], \r\n" +
            "  gp2d.[RowVersion], \r\n" +
            "  gp2d.[Catalog], \r\n" +
            "  gp2d.[Name], \r\n" +
            "  gp2d.[MaxRetention], \r\n" +
            "  aatnpt.[AidToNavigation] \r\n" +
            "FROM [GeoPosition2DTimeseriesView] gp2d \r\n" +
            "  LEFT JOIN [AisAidToNavigationPositionTimeseries] aatnpt ON(gp2d.[Id] = aatnpt.[Id] ) \r\n";

        public const string BaseViewName = "GeoPosition2DTimeseriesView";
        public const string ViewAliasName = "gp2d";

        public const int GP2D_ID_FIELD_ID = 0;
        public const int GP2D_KIND_FIELD_ID = 1;
        public const int GP2D_ROWVERSION_FIELD_ID = 2;
        public const int GP2D_CATALOG_FIELD_ID = 3;
        public const int GP2D_NAME_FIELD_ID = 4;
        public const int GP2D_MAXRETENTION_FIELD_ID = 5;
        public const int AATNPT_AIDTONAVIGATION_FIELD_ID = 6;
        public ComplexGeoPosition2DTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( GP2D_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( GP2D_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( GP2D_ROWVERSION_FIELD_ID );
            }
        }
        public Guid? Catalog
        {
            get
            {
                return GetNullableGuid( GP2D_CATALOG_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( GP2D_NAME_FIELD_ID );
            }
        }
        public TimeSpan MaxRetention
        {
            get
            {
                return new TimeSpan( GetInt64( GP2D_MAXRETENTION_FIELD_ID ) );
            }
        }
        public Guid? AisAidToNavigationPositionTimeseriesAidToNavigation
        {
            get
            {
                return GetNullableGuid( AATNPT_AIDTONAVIGATION_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.GeoPosition2DTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.AisAidToNavigationPositionTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( AisAidToNavigationPositionTimeseriesAidToNavigation );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public GeoPosition2DTimeseriesObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.GeoPosition2DTimeseries:
                {
                    return new GeoPosition2DTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.AisAidToNavigationPositionTimeseries:
                {
                    return new AisAidToNavigationPositionTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, AisAidToNavigationPositionTimeseriesAidToNavigation );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexInt32TimeseriesDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  i32t.[Id], \r\n" +
            "  i32t.[EntityType], \r\n" +
            "  i32t.[RowVersion], \r\n" +
            "  i32t.[Catalog], \r\n" +
            "  i32t.[Name], \r\n" +
            "  i32t.[MaxRetention], \r\n" +
            "  raot.[Radar], \r\n" +
            "  rftclt.[Radar], \r\n" +
            "  rftcmt.[Radar], \r\n" +
            "  rapts.[Radar], \r\n" +
            "  rs1et.[Radar], \r\n" +
            "  rs1st.[Radar], \r\n" +
            "  rs2et.[Radar], \r\n" +
            "  rs2st.[Radar], \r\n" +
            "  rstclt.[Radar], \r\n" +
            "  ratuts.[Radar], \r\n" +
            "  vpobt.[Vessel] \r\n" +
            "FROM [Int32TimeseriesView] i32t \r\n" +
            "  LEFT JOIN [RadarAzimuthOffsetTimeseries] raot ON(i32t.[Id] = raot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantLevelTimeseries] rftclt ON(i32t.[Id] = rftclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantModeTimeseries] rftcmt ON(i32t.[Id] = rftcmt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPulseTimeseries] rapts ON(i32t.[Id] = rapts.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1EndTimeseries] rs1et ON(i32t.[Id] = rs1et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1StartTimeseries] rs1st ON(i32t.[Id] = rs1st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2EndTimeseries] rs2et ON(i32t.[Id] = rs2et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2StartTimeseries] rs2st ON(i32t.[Id] = rs2st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSensitivityTimeControlLevelTimeseries] rstclt ON(i32t.[Id] = rstclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTuningTimeseries] ratuts ON(i32t.[Id] = ratuts.[Id] ) \r\n" +
            "  LEFT JOIN [VesselPersonsOnBoardTimeseries] vpobt ON(i32t.[Id] = vpobt.[Id] ) \r\n";

        public const string BaseViewName = "Int32TimeseriesView";
        public const string ViewAliasName = "i32t";

        public const int I32T_ID_FIELD_ID = 0;
        public const int I32T_KIND_FIELD_ID = 1;
        public const int I32T_ROWVERSION_FIELD_ID = 2;
        public const int I32T_CATALOG_FIELD_ID = 3;
        public const int I32T_NAME_FIELD_ID = 4;
        public const int I32T_MAXRETENTION_FIELD_ID = 5;
        public const int RAOT_RADAR_FIELD_ID = 6;
        public const int RFTCLT_RADAR_FIELD_ID = 7;
        public const int RFTCMT_RADAR_FIELD_ID = 8;
        public const int RAPTS_RADAR_FIELD_ID = 9;
        public const int RS1ET_RADAR_FIELD_ID = 10;
        public const int RS1ST_RADAR_FIELD_ID = 11;
        public const int RS2ET_RADAR_FIELD_ID = 12;
        public const int RS2ST_RADAR_FIELD_ID = 13;
        public const int RSTCLT_RADAR_FIELD_ID = 14;
        public const int RATUTS_RADAR_FIELD_ID = 15;
        public const int VPOBT_VESSEL_FIELD_ID = 16;
        public ComplexInt32TimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( I32T_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( I32T_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( I32T_ROWVERSION_FIELD_ID );
            }
        }
        public Guid? Catalog
        {
            get
            {
                return GetNullableGuid( I32T_CATALOG_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( I32T_NAME_FIELD_ID );
            }
        }
        public TimeSpan MaxRetention
        {
            get
            {
                return new TimeSpan( GetInt64( I32T_MAXRETENTION_FIELD_ID ) );
            }
        }
        public Guid? RadarAzimuthOffsetTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RAOT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarFastTimeConstantLevelTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RFTCLT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarFastTimeConstantModeTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RFTCMT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarPulseTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RAPTS_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector1EndTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS1ET_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector1StartTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS1ST_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector2EndTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS2ET_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSector2StartTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RS2ST_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarSensitivityTimeControlLevelTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RSTCLT_RADAR_FIELD_ID );
            }
        }
        public Guid? RadarTuningTimeseriesRadar
        {
            get
            {
                return GetNullableGuid( RATUTS_RADAR_FIELD_ID );
            }
        }
        public Guid? VesselPersonsOnBoardTimeseriesVessel
        {
            get
            {
                return GetNullableGuid( VPOBT_VESSEL_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.Int32Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.RadarAzimuthOffsetTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarAzimuthOffsetTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarFastTimeConstantLevelTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarFastTimeConstantLevelTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarFastTimeConstantModeTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarFastTimeConstantModeTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarPulseTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarPulseTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector1EndTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSector1EndTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector1StartTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSector1StartTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector2EndTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSector2EndTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSector2StartTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSector2StartTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarSensitivityTimeControlLevelTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarSensitivityTimeControlLevelTimeseriesRadar );
                }
                break;
                case Types.Kind.RadarTuningTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadarTuningTimeseriesRadar );
                }
                break;
                case Types.Kind.VesselPersonsOnBoardTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( VesselPersonsOnBoardTimeseriesVessel );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public Int32TimeseriesObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.Int32Timeseries:
                {
                    return new Int32TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.RadarAzimuthOffsetTimeseries:
                {
                    return new RadarAzimuthOffsetTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarAzimuthOffsetTimeseriesRadar );
                }
                case Types.Kind.RadarFastTimeConstantLevelTimeseries:
                {
                    return new RadarFastTimeConstantLevelTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarFastTimeConstantLevelTimeseriesRadar );
                }
                case Types.Kind.RadarFastTimeConstantModeTimeseries:
                {
                    return new RadarFastTimeConstantModeTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarFastTimeConstantModeTimeseriesRadar );
                }
                case Types.Kind.RadarPulseTimeseries:
                {
                    return new RadarPulseTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarPulseTimeseriesRadar );
                }
                case Types.Kind.RadarSector1EndTimeseries:
                {
                    return new RadarSector1EndTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSector1EndTimeseriesRadar );
                }
                case Types.Kind.RadarSector1StartTimeseries:
                {
                    return new RadarSector1StartTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSector1StartTimeseriesRadar );
                }
                case Types.Kind.RadarSector2EndTimeseries:
                {
                    return new RadarSector2EndTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSector2EndTimeseriesRadar );
                }
                case Types.Kind.RadarSector2StartTimeseries:
                {
                    return new RadarSector2StartTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSector2StartTimeseriesRadar );
                }
                case Types.Kind.RadarSensitivityTimeControlLevelTimeseries:
                {
                    return new RadarSensitivityTimeControlLevelTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarSensitivityTimeControlLevelTimeseriesRadar );
                }
                case Types.Kind.RadarTuningTimeseries:
                {
                    return new RadarTuningTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadarTuningTimeseriesRadar );
                }
                case Types.Kind.VesselPersonsOnBoardTimeseries:
                {
                    return new VesselPersonsOnBoardTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, VesselPersonsOnBoardTimeseriesVessel );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexUInt32TimeseriesDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  u32t.[Id], \r\n" +
            "  u32t.[EntityType], \r\n" +
            "  u32t.[RowVersion], \r\n" +
            "  u32t.[Catalog], \r\n" +
            "  u32t.[Name], \r\n" +
            "  u32t.[MaxRetention], \r\n" +
            "  rst.[Radome] \r\n" +
            "FROM [UInt32TimeseriesView] u32t \r\n" +
            "  LEFT JOIN [RadomeStatusTimeseries] rst ON(u32t.[Id] = rst.[Id] ) \r\n";

        public const string BaseViewName = "UInt32TimeseriesView";
        public const string ViewAliasName = "u32t";

        public const int U32T_ID_FIELD_ID = 0;
        public const int U32T_KIND_FIELD_ID = 1;
        public const int U32T_ROWVERSION_FIELD_ID = 2;
        public const int U32T_CATALOG_FIELD_ID = 3;
        public const int U32T_NAME_FIELD_ID = 4;
        public const int U32T_MAXRETENTION_FIELD_ID = 5;
        public const int RST_RADOME_FIELD_ID = 6;
        public ComplexUInt32TimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( U32T_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( U32T_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( U32T_ROWVERSION_FIELD_ID );
            }
        }
        public Guid? Catalog
        {
            get
            {
                return GetNullableGuid( U32T_CATALOG_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( U32T_NAME_FIELD_ID );
            }
        }
        public TimeSpan MaxRetention
        {
            get
            {
                return new TimeSpan( GetInt64( U32T_MAXRETENTION_FIELD_ID ) );
            }
        }
        public Guid? RadomeStatusTimeseriesRadome
        {
            get
            {
                return GetNullableGuid( RST_RADOME_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.UInt32Timeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                }
                break;
                case Types.Kind.RadomeStatusTimeseries:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Catalog );
                    destination.Write( Name );
                    destination.Write( MaxRetention );
                    destination.Write( RadomeStatusTimeseriesRadome );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public UInt32TimeseriesObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.UInt32Timeseries:
                {
                    return new UInt32TimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention );
                }
                case Types.Kind.RadomeStatusTimeseries:
                {
                    return new RadomeStatusTimeseriesObject( ObjectState.Stored, Id, RowVersion, Catalog, Name, MaxRetention, RadomeStatusTimeseriesRadome );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexTrackBaseDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tb.[Id], \r\n" +
            "  tb.[EntityType], \r\n" +
            "  tb.[RowVersion], \r\n" +
            "  tb.[Tracker], \r\n" +
            "  tb.[TrackNumber], \r\n" +
            "  tb.[Timestamp] \r\n" +
            "FROM [TrackBaseView] tb \r\n" +
            "  LEFT JOIN [Track] t ON(tb.[Id] = t.[Id] ) \r\n" +
            "  LEFT JOIN [Track3D] t3d ON(tb.[Id] = t3d.[Id] ) \r\n";

        public const string BaseViewName = "TrackBaseView";
        public const string ViewAliasName = "tb";

        public const int TB_ID_FIELD_ID = 0;
        public const int TB_KIND_FIELD_ID = 1;
        public const int TB_ROWVERSION_FIELD_ID = 2;
        public const int TB_TRACKER_FIELD_ID = 3;
        public const int TB_TRACKNUMBER_FIELD_ID = 4;
        public const int TB_TIMESTAMP_FIELD_ID = 5;
        public ComplexTrackBaseDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( TB_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( TB_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( TB_ROWVERSION_FIELD_ID );
            }
        }
        public Guid Tracker
        {
            get
            {
                return GetGuid( TB_TRACKER_FIELD_ID );
            }
        }
        public long TrackNumber
        {
            get
            {
                return GetInt64( TB_TRACKNUMBER_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TB_TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.Track:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Tracker );
                    destination.Write( TrackNumber );
                    destination.Write( Timestamp );
                }
                break;
                case Types.Kind.Track3D:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Tracker );
                    destination.Write( TrackNumber );
                    destination.Write( Timestamp );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public TrackBaseObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.Track:
                {
                    return new TrackObject( ObjectState.Stored, Id, RowVersion, Tracker, TrackNumber, Timestamp );
                }
                case Types.Kind.Track3D:
                {
                    return new Track3DObject( ObjectState.Stored, Id, RowVersion, Tracker, TrackNumber, Timestamp );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

    public class ComplexZoneDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  z.[Id], \r\n" +
            "  z.[EntityType], \r\n" +
            "  z.[RowVersion], \r\n" +
            "  z.[Name], \r\n" +
            "  z.[Longitude], \r\n" +
            "  z.[Latitude], \r\n" +
            "  z.[AlarmType], \r\n" +
            "  z.[AlarmTime], \r\n" +
            "  z.[RadarTrackMinimumLifetime], \r\n" +
            "  z.[Speed], \r\n" +
            "  z.[StrokeColor], \r\n" +
            "  z.[FillColor], \r\n" +
            "  cz.[Radius], \r\n" +
            "  pz.[Polygon] \r\n" +
            "FROM [ZoneView] z \r\n" +
            "  LEFT JOIN [CircularZone] cz ON(z.[Id] = cz.[Id] ) \r\n" +
            "  LEFT JOIN [PolygonZone] pz ON(z.[Id] = pz.[Id] ) \r\n";

        public const string BaseViewName = "ZoneView";
        public const string ViewAliasName = "z";

        public const int Z_ID_FIELD_ID = 0;
        public const int Z_KIND_FIELD_ID = 1;
        public const int Z_ROWVERSION_FIELD_ID = 2;
        public const int Z_NAME_FIELD_ID = 3;
        public const int Z_LONGITUDE_FIELD_ID = 4;
        public const int Z_LATITUDE_FIELD_ID = 5;
        public const int Z_ALARMTYPE_FIELD_ID = 6;
        public const int Z_ALARMTIME_FIELD_ID = 7;
        public const int Z_RADARTRACKMINIMUMLIFETIME_FIELD_ID = 8;
        public const int Z_SPEED_FIELD_ID = 9;
        public const int Z_STROKECOLOR_FIELD_ID = 10;
        public const int Z_FILLCOLOR_FIELD_ID = 11;
        public const int CZ_RADIUS_FIELD_ID = 12;
        public const int PZ_POLYGON_FIELD_ID = 13;
        public ComplexZoneDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( Z_ID_FIELD_ID );
            }
        }
        public Types.Kind Kind
        {
            get
            {
                return (Types.Kind)GetInt32( Z_KIND_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( Z_ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( Z_NAME_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( Z_LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( Z_LATITUDE_FIELD_ID );
            }
        }
        public Types.ZoneAlarmType AlarmType
        {
            get
            {
                return GetEnum<Types.ZoneAlarmType>( Z_ALARMTYPE_FIELD_ID );
            }
        }
        public TimeSpan AlarmTime
        {
            get
            {
                return new TimeSpan( GetInt64( Z_ALARMTIME_FIELD_ID ) );
            }
        }
        public TimeSpan RadarTrackMinimumLifetime
        {
            get
            {
                return new TimeSpan( GetInt64( Z_RADARTRACKMINIMUMLIFETIME_FIELD_ID ) );
            }
        }
        public double Speed
        {
            get
            {
                return GetDouble( Z_SPEED_FIELD_ID );
            }
        }
        public uint StrokeColor
        {
            get
            {
                return GetUInt32( Z_STROKECOLOR_FIELD_ID );
            }
        }
        public uint FillColor
        {
            get
            {
                return GetUInt32( Z_FILLCOLOR_FIELD_ID );
            }
        }
        public double CircularZoneRadius
        {
            get
            {
                return GetDouble( CZ_RADIUS_FIELD_ID );
            }
        }
        public byte[] PolygonZonePolygon
        {
            get
            {
                return GetBytes( PZ_POLYGON_FIELD_ID );
            }
        }
        public void WriteTo([DisallowNull] BinaryWriter destination )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.CircularZone:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Name );
                    destination.Write( Longitude );
                    destination.Write( Latitude );
                    destination.Write( AlarmType );
                    destination.Write( AlarmTime );
                    destination.Write( RadarTrackMinimumLifetime );
                    destination.Write( Speed );
                    destination.Write( StrokeColor );
                    destination.Write( FillColor );
                    destination.Write( CircularZoneRadius );
                }
                break;
                case Types.Kind.PolygonZone:
                {
                    destination.Write( kind );
                    destination.Write( ObjectState.Stored );
                    destination.Write( Id );
                    destination.Write( RowVersion );
                    destination.Write( Name );
                    destination.Write( Longitude );
                    destination.Write( Latitude );
                    destination.Write( AlarmType );
                    destination.Write( AlarmTime );
                    destination.Write( RadarTrackMinimumLifetime );
                    destination.Write( Speed );
                    destination.Write( StrokeColor );
                    destination.Write( FillColor );
                    destination.WriteArray( PolygonZonePolygon );
                }
                break;
                default:
                {
                    var exc = new Exception( $"Cannot perform serialization for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )
        {
            while ( Read( ) )
            {
                destination.Write( true );
                WriteTo( destination );
            }
            destination.Write( false );
        }

        public ZoneObject GetDataObject( )
        {
            var kind = Kind;
            switch(kind)
            {
                case Types.Kind.CircularZone:
                {
                    return new CircularZoneObject( ObjectState.Stored, Id, RowVersion, Name, Longitude, Latitude, AlarmType, AlarmTime, RadarTrackMinimumLifetime, Speed, StrokeColor, FillColor, CircularZoneRadius );
                }
                case Types.Kind.PolygonZone:
                {
                    return new PolygonZoneObject( ObjectState.Stored, Id, RowVersion, Name, Longitude, Latitude, AlarmType, AlarmTime, RadarTrackMinimumLifetime, Speed, StrokeColor, FillColor, PolygonZonePolygon );
                }
                default:
                {
                    var exc = new Exception( $"Cannot create an object for kind={kind}." );
                    LogException( exc );
                    throw exc;
                }
            }
        }

    }

}
