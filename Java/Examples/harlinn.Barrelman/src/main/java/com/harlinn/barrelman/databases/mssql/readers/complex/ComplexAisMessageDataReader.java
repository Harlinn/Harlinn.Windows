/*
    Copyright 2024-2026 Espen Harlinn
 
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
package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexAisMessageDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
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

    public final static String BaseViewName = "AisMessageView";
    public final static String ViewAliasName = "am";

    public final static int AM_ID_FIELD_ID = 1;
    public final static int AM_KIND_FIELD_ID = 2;
    public final static int AM_ROWVERSION_FIELD_ID = 3;
    public final static int AM_AISDEVICE_FIELD_ID = 4;
    public final static int AM_RECEIVEDTIMESTAMP_FIELD_ID = 5;
    public final static int AM_MESSAGESEQUENCENUMBER_FIELD_ID = 6;
    public final static int AM_REPEAT_FIELD_ID = 7;
    public final static int AM_MMSI_FIELD_ID = 8;
    public final static int ATNRM_NAVIGATIONALAIDTYPE_FIELD_ID = 9;
    public final static int ATNRM_NAME_FIELD_ID = 10;
    public final static int ATNRM_POSITIONACCURACY_FIELD_ID = 11;
    public final static int ATNRM_LONGITUDE_FIELD_ID = 12;
    public final static int ATNRM_LATITUDE_FIELD_ID = 13;
    public final static int ATNRM_DIMENSIONTOBOW_FIELD_ID = 14;
    public final static int ATNRM_DIMENSIONTOSTERN_FIELD_ID = 15;
    public final static int ATNRM_DIMENSIONTOPORT_FIELD_ID = 16;
    public final static int ATNRM_DIMENSIONTOSTARBOARD_FIELD_ID = 17;
    public final static int ATNRM_POSITIONFIXTYPE_FIELD_ID = 18;
    public final static int ATNRM_TIMESTAMP_FIELD_ID = 19;
    public final static int ATNRM_OFFPOSITION_FIELD_ID = 20;
    public final static int ATNRM_REGIONALRESERVED_FIELD_ID = 21;
    public final static int ATNRM_RAIM_FIELD_ID = 22;
    public final static int ATNRM_VIRTUALAID_FIELD_ID = 23;
    public final static int ATNRM_ASSIGNED_FIELD_ID = 24;
    public final static int ATNRM_SPARE_FIELD_ID = 25;
    public final static int ATNRM_NAMEEXTENSION_FIELD_ID = 26;
    public final static int AASRM_SEQUENCENUMBER_FIELD_ID = 27;
    public final static int AASRM_DESTINATIONMMSI_FIELD_ID = 28;
    public final static int AASRM_RETRANSMITFLAG_FIELD_ID = 29;
    public final static int AASRM_SPARE_FIELD_ID = 30;
    public final static int AASRM_TEXT_FIELD_ID = 31;
    public final static int ABSRM_TIMESTAMP_FIELD_ID = 32;
    public final static int ABSRM_POSITIONACCURACY_FIELD_ID = 33;
    public final static int ABSRM_LONGITUDE_FIELD_ID = 34;
    public final static int ABSRM_LATITUDE_FIELD_ID = 35;
    public final static int ABSRM_POSITIONFIXTYPE_FIELD_ID = 36;
    public final static int ABSRM_SPARE_FIELD_ID = 37;
    public final static int ABSRM_RAIM_FIELD_ID = 38;
    public final static int ABSRM_RADIOSTATUS_FIELD_ID = 39;
    public final static int ABAC_SPARE_FIELD_ID = 40;
    public final static int ABAC_SEQUENCENUMBER1_FIELD_ID = 41;
    public final static int ABAC_MMSI1_FIELD_ID = 42;
    public final static int ABAC_SEQUENCENUMBER2_FIELD_ID = 43;
    public final static int ABAC_MMSI2_FIELD_ID = 44;
    public final static int ABAC_SEQUENCENUMBER3_FIELD_ID = 45;
    public final static int ABAC_MMSI3_FIELD_ID = 46;
    public final static int ABAC_SEQUENCENUMBER4_FIELD_ID = 47;
    public final static int ABAC_MMSI4_FIELD_ID = 48;
    public final static int ABAM_SEQUENCENUMBER_FIELD_ID = 49;
    public final static int ABAM_DESTINATIONMMSI_FIELD_ID = 50;
    public final static int ABAM_RETRANSMITFLAG_FIELD_ID = 51;
    public final static int ABAM_SPARE_FIELD_ID = 52;
    public final static int ABAM_DESIGNATEDAREACODE_FIELD_ID = 53;
    public final static int ABAM_FUNCTIONALID_FIELD_ID = 54;
    public final static int ABBM_SPARE_FIELD_ID = 55;
    public final static int ABBM_DESIGNATEDAREACODE_FIELD_ID = 56;
    public final static int ABBM_FUNCTIONALID_FIELD_ID = 57;
    public final static int ADLMM_SPARE_FIELD_ID = 58;
    public final static int ADLMM_OFFSET1_FIELD_ID = 59;
    public final static int ADLMM_RESERVEDSLOTS1_FIELD_ID = 60;
    public final static int ADLMM_TIMEOUT1_FIELD_ID = 61;
    public final static int ADLMM_INCREMENT1_FIELD_ID = 62;
    public final static int ADLMM_OFFSET2_FIELD_ID = 63;
    public final static int ADLMM_RESERVEDSLOTS2_FIELD_ID = 64;
    public final static int ADLMM_TIMEOUT2_FIELD_ID = 65;
    public final static int ADLMM_INCREMENT2_FIELD_ID = 66;
    public final static int ADLMM_OFFSET3_FIELD_ID = 67;
    public final static int ADLMM_RESERVEDSLOTS3_FIELD_ID = 68;
    public final static int ADLMM_TIMEOUT3_FIELD_ID = 69;
    public final static int ADLMM_INCREMENT3_FIELD_ID = 70;
    public final static int ADLMM_OFFSET4_FIELD_ID = 71;
    public final static int ADLMM_RESERVEDSLOTS4_FIELD_ID = 72;
    public final static int ADLMM_TIMEOUT4_FIELD_ID = 73;
    public final static int ADLMM_INCREMENT4_FIELD_ID = 74;
    public final static int AECBPRM_RESERVED_FIELD_ID = 75;
    public final static int AECBPRM_SPEEDOVERGROUND_FIELD_ID = 76;
    public final static int AECBPRM_POSITIONACCURACY_FIELD_ID = 77;
    public final static int AECBPRM_LONGITUDE_FIELD_ID = 78;
    public final static int AECBPRM_LATITUDE_FIELD_ID = 79;
    public final static int AECBPRM_COURSEOVERGROUND_FIELD_ID = 80;
    public final static int AECBPRM_TRUEHEADING_FIELD_ID = 81;
    public final static int AECBPRM_TIMESTAMP_FIELD_ID = 82;
    public final static int AECBPRM_REGIONALRESERVED_FIELD_ID = 83;
    public final static int AECBPRM_NAME_FIELD_ID = 84;
    public final static int AECBPRM_SHIPTYPE_FIELD_ID = 85;
    public final static int AECBPRM_DIMENSIONTOBOW_FIELD_ID = 86;
    public final static int AECBPRM_DIMENSIONTOSTERN_FIELD_ID = 87;
    public final static int AECBPRM_DIMENSIONTOPORT_FIELD_ID = 88;
    public final static int AECBPRM_DIMENSIONTOSTARBOARD_FIELD_ID = 89;
    public final static int AECBPRM_POSITIONFIXTYPE_FIELD_ID = 90;
    public final static int AECBPRM_RAIM_FIELD_ID = 91;
    public final static int AECBPRM_DATATERMINALREADY_FIELD_ID = 92;
    public final static int AECBPRM_ASSIGNED_FIELD_ID = 93;
    public final static int AECBPRM_SPARE_FIELD_ID = 94;
    public final static int AIM_INTERROGATEDMMSI_FIELD_ID = 95;
    public final static int AIM_FIRSTMESSAGETYPE_FIELD_ID = 96;
    public final static int AIM_FIRSTSLOTOFFSET_FIELD_ID = 97;
    public final static int AIM_SECONDMESSAGETYPE_FIELD_ID = 98;
    public final static int AIM_SECONDSLOTOFFSET_FIELD_ID = 99;
    public final static int AIM_SECONDSTATIONINTERROGATIONMMSI_FIELD_ID = 100;
    public final static int AIM_SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID = 101;
    public final static int AIM_SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID = 102;
    public final static int APRCAB_NAVIGATIONSTATUS_FIELD_ID = 103;
    public final static int APRCAB_RATEOFTURN_FIELD_ID = 104;
    public final static int APRCAB_SPEEDOVERGROUND_FIELD_ID = 105;
    public final static int APRCAB_POSITIONACCURACY_FIELD_ID = 106;
    public final static int APRCAB_LONGITUDE_FIELD_ID = 107;
    public final static int APRCAB_LATITUDE_FIELD_ID = 108;
    public final static int APRCAB_COURSEOVERGROUND_FIELD_ID = 109;
    public final static int APRCAB_TRUEHEADING_FIELD_ID = 110;
    public final static int APRCAB_TIMESTAMP_FIELD_ID = 111;
    public final static int APRCAB_MANEUVERINDICATOR_FIELD_ID = 112;
    public final static int APRCAB_SPARE_FIELD_ID = 113;
    public final static int APRCAB_RAIM_FIELD_ID = 114;
    public final static int APRCAB_RADIOSTATUS_FIELD_ID = 115;
    public final static int APRFLRAM_POSITIONACCURACY_FIELD_ID = 116;
    public final static int APRFLRAM_RAIM_FIELD_ID = 117;
    public final static int APRFLRAM_NAVIGATIONSTATUS_FIELD_ID = 118;
    public final static int APRFLRAM_LONGITUDE_FIELD_ID = 119;
    public final static int APRFLRAM_LATITUDE_FIELD_ID = 120;
    public final static int APRFLRAM_SPEEDOVERGROUND_FIELD_ID = 121;
    public final static int APRFLRAM_COURSEOVERGROUND_FIELD_ID = 122;
    public final static int APRFLRAM_GNSSPOSITIONSTATUS_FIELD_ID = 123;
    public final static int APRFLRAM_SPARE_FIELD_ID = 124;
    public final static int ASRAM_SPARE_FIELD_ID = 125;
    public final static int ASRAM_SEQUENCENUMBER1_FIELD_ID = 126;
    public final static int ASRAM_MMSI1_FIELD_ID = 127;
    public final static int ASRAM_SEQUENCENUMBER2_FIELD_ID = 128;
    public final static int ASRAM_MMSI2_FIELD_ID = 129;
    public final static int ASRAM_SEQUENCENUMBER3_FIELD_ID = 130;
    public final static int ASRAM_MMSI3_FIELD_ID = 131;
    public final static int ASRAM_SEQUENCENUMBER4_FIELD_ID = 132;
    public final static int ASRAM_MMSI4_FIELD_ID = 133;
    public final static int ASCBPRM_RESERVED_FIELD_ID = 134;
    public final static int ASCBPRM_SPEEDOVERGROUND_FIELD_ID = 135;
    public final static int ASCBPRM_POSITIONACCURACY_FIELD_ID = 136;
    public final static int ASCBPRM_LONGITUDE_FIELD_ID = 137;
    public final static int ASCBPRM_LATITUDE_FIELD_ID = 138;
    public final static int ASCBPRM_COURSEOVERGROUND_FIELD_ID = 139;
    public final static int ASCBPRM_TRUEHEADING_FIELD_ID = 140;
    public final static int ASCBPRM_TIMESTAMP_FIELD_ID = 141;
    public final static int ASCBPRM_REGIONALRESERVED_FIELD_ID = 142;
    public final static int ASCBPRM_ISCSUNIT_FIELD_ID = 143;
    public final static int ASCBPRM_HASDISPLAY_FIELD_ID = 144;
    public final static int ASCBPRM_HASDSCCAPABILITY_FIELD_ID = 145;
    public final static int ASCBPRM_BAND_FIELD_ID = 146;
    public final static int ASCBPRM_CANACCEPTMESSAGE22_FIELD_ID = 147;
    public final static int ASCBPRM_ASSIGNED_FIELD_ID = 148;
    public final static int ASCBPRM_RAIM_FIELD_ID = 149;
    public final static int ASCBPRM_RADIOSTATUS_FIELD_ID = 150;
    public final static int ASSAPRM_ALTITUDE_FIELD_ID = 151;
    public final static int ASSAPRM_SPEEDOVERGROUND_FIELD_ID = 152;
    public final static int ASSAPRM_POSITIONACCURACY_FIELD_ID = 153;
    public final static int ASSAPRM_LONGITUDE_FIELD_ID = 154;
    public final static int ASSAPRM_LATITUDE_FIELD_ID = 155;
    public final static int ASSAPRM_COURSEOVERGROUND_FIELD_ID = 156;
    public final static int ASSAPRM_TIMESTAMP_FIELD_ID = 157;
    public final static int ASSAPRM_RESERVED_FIELD_ID = 158;
    public final static int ASSAPRM_DATATERMINALREADY_FIELD_ID = 159;
    public final static int ASSAPRM_SPARE_FIELD_ID = 160;
    public final static int ASSAPRM_ASSIGNED_FIELD_ID = 161;
    public final static int ASSAPRM_RAIM_FIELD_ID = 162;
    public final static int ASSAPRM_RADIOSTATUS_FIELD_ID = 163;
    public final static int ASAVRDM_AISVERSION_FIELD_ID = 164;
    public final static int ASAVRDM_IMONUMBER_FIELD_ID = 165;
    public final static int ASAVRDM_CALLSIGN_FIELD_ID = 166;
    public final static int ASAVRDM_SHIPNAME_FIELD_ID = 167;
    public final static int ASAVRDM_SHIPTYPE_FIELD_ID = 168;
    public final static int ASAVRDM_DIMENSIONTOBOW_FIELD_ID = 169;
    public final static int ASAVRDM_DIMENSIONTOSTERN_FIELD_ID = 170;
    public final static int ASAVRDM_DIMENSIONTOPORT_FIELD_ID = 171;
    public final static int ASAVRDM_DIMENSIONTOSTARBOARD_FIELD_ID = 172;
    public final static int ASAVRDM_POSITIONFIXTYPE_FIELD_ID = 173;
    public final static int ASAVRDM_ESTIMATEDTIMEOFARRIVAL_FIELD_ID = 174;
    public final static int ASAVRDM_DRAUGHT_FIELD_ID = 175;
    public final static int ASAVRDM_DESTINATION_FIELD_ID = 176;
    public final static int ASAVRDM_DATATERMINALREADY_FIELD_ID = 177;
    public final static int ASAVRDM_SPARE_FIELD_ID = 178;
    public final static int ASDRM_PARTNUMBER_FIELD_ID = 179;
    public final static int ASDRPA_SHIPNAME_FIELD_ID = 180;
    public final static int ASDRPA_SPARE_FIELD_ID = 181;
    public final static int ASDRPB_SHIPTYPE_FIELD_ID = 182;
    public final static int ASDRPB_VENDORID_FIELD_ID = 183;
    public final static int ASDRPB_UNITMODELCODE_FIELD_ID = 184;
    public final static int ASDRPB_SERIALNUMBER_FIELD_ID = 185;
    public final static int ASDRPB_CALLSIGN_FIELD_ID = 186;
    public final static int ASDRPB_DIMENSIONTOBOW_FIELD_ID = 187;
    public final static int ASDRPB_DIMENSIONTOSTERN_FIELD_ID = 188;
    public final static int ASDRPB_DIMENSIONTOPORT_FIELD_ID = 189;
    public final static int ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID = 190;
    public final static int ASDRPB_MOTHERSHIPMMSI_FIELD_ID = 191;
    public final static int ASDRPB_POSITIONFIXTYPE_FIELD_ID = 192;
    public final static int ASDRPB_SPARE_FIELD_ID = 193;
    public final static int AUADIM_SPARE1_FIELD_ID = 194;
    public final static int AUADIM_DESTINATIONMMSI_FIELD_ID = 195;
    public final static int AUADIM_SPARE2_FIELD_ID = 196;
    public final static int AUADRM_DATETIME_FIELD_ID = 197;
    public final static int AUADRM_POSITIONACCURACY_FIELD_ID = 198;
    public final static int AUADRM_LONGITUDE_FIELD_ID = 199;
    public final static int AUADRM_LATITUDE_FIELD_ID = 200;
    public final static int AUADRM_POSITIONFIXTYPE_FIELD_ID = 201;
    public final static int AUADRM_SPARE_FIELD_ID = 202;
    public final static int AUADRM_RAIM_FIELD_ID = 203;
    public final static int AUADRM_RADIOSTATUS_FIELD_ID = 204;
    public final static int ABAM_DATA_FIELD_ID = 205;
    public final static int ABBM_DATA_FIELD_ID = 206;

    public ComplexAisMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( AM_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( AM_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( AM_ROWVERSION_FIELD_ID );
    }

    public Guid getAisDevice( ) throws SQLException {
        return getGuid( AM_AISDEVICE_FIELD_ID );
    }

    public DateTime getReceivedTimestamp( ) throws SQLException {
        return getDateTimeFromLong( AM_RECEIVEDTIMESTAMP_FIELD_ID );
    }

    public long getMessageSequenceNumber( ) throws SQLException {
        return getInt64( AM_MESSAGESEQUENCENUMBER_FIELD_ID );
    }

    public int getRepeat( ) throws SQLException {
        return getInt32( AM_REPEAT_FIELD_ID );
    }

    public Guid getMmsi( ) throws SQLException {
        return getNullableGuid( AM_MMSI_FIELD_ID );
    }

    public int getAidToNavigationReportMessageNavigationalAidType( ) throws SQLException {
        return getInt32( ATNRM_NAVIGATIONALAIDTYPE_FIELD_ID );
    }

    public String getAidToNavigationReportMessageName( ) throws SQLException {
        return getString( ATNRM_NAME_FIELD_ID );
    }

    public int getAidToNavigationReportMessagePositionAccuracy( ) throws SQLException {
        return getInt32( ATNRM_POSITIONACCURACY_FIELD_ID );
    }

    public double getAidToNavigationReportMessageLongitude( ) throws SQLException {
        return getDouble( ATNRM_LONGITUDE_FIELD_ID );
    }

    public double getAidToNavigationReportMessageLatitude( ) throws SQLException {
        return getDouble( ATNRM_LATITUDE_FIELD_ID );
    }

    public int getAidToNavigationReportMessageDimensionToBow( ) throws SQLException {
        return getInt32( ATNRM_DIMENSIONTOBOW_FIELD_ID );
    }

    public int getAidToNavigationReportMessageDimensionToStern( ) throws SQLException {
        return getInt32( ATNRM_DIMENSIONTOSTERN_FIELD_ID );
    }

    public int getAidToNavigationReportMessageDimensionToPort( ) throws SQLException {
        return getInt32( ATNRM_DIMENSIONTOPORT_FIELD_ID );
    }

    public int getAidToNavigationReportMessageDimensionToStarboard( ) throws SQLException {
        return getInt32( ATNRM_DIMENSIONTOSTARBOARD_FIELD_ID );
    }

    public int getAidToNavigationReportMessagePositionFixType( ) throws SQLException {
        return getInt32( ATNRM_POSITIONFIXTYPE_FIELD_ID );
    }

    public int getAidToNavigationReportMessageTimestamp( ) throws SQLException {
        return getInt32( ATNRM_TIMESTAMP_FIELD_ID );
    }

    public boolean getAidToNavigationReportMessageOffPosition( ) throws SQLException {
        return getBoolean( ATNRM_OFFPOSITION_FIELD_ID );
    }

    public int getAidToNavigationReportMessageRegionalReserved( ) throws SQLException {
        return getInt32( ATNRM_REGIONALRESERVED_FIELD_ID );
    }

    public int getAidToNavigationReportMessageRaim( ) throws SQLException {
        return getInt32( ATNRM_RAIM_FIELD_ID );
    }

    public boolean getAidToNavigationReportMessageVirtualAid( ) throws SQLException {
        return getBoolean( ATNRM_VIRTUALAID_FIELD_ID );
    }

    public boolean getAidToNavigationReportMessageAssigned( ) throws SQLException {
        return getBoolean( ATNRM_ASSIGNED_FIELD_ID );
    }

    public int getAidToNavigationReportMessageSpare( ) throws SQLException {
        return getInt32( ATNRM_SPARE_FIELD_ID );
    }

    public String getAidToNavigationReportMessageNameExtension( ) throws SQLException {
        return getString( ATNRM_NAMEEXTENSION_FIELD_ID );
    }

    public int getAisAddressedSafetyRelatedMessageSequenceNumber( ) throws SQLException {
        return getInt32( AASRM_SEQUENCENUMBER_FIELD_ID );
    }

    public Guid getAisAddressedSafetyRelatedMessageDestinationMmsi( ) throws SQLException {
        return getNullableGuid( AASRM_DESTINATIONMMSI_FIELD_ID );
    }

    public boolean getAisAddressedSafetyRelatedMessageRetransmitFlag( ) throws SQLException {
        return getBoolean( AASRM_RETRANSMITFLAG_FIELD_ID );
    }

    public int getAisAddressedSafetyRelatedMessageSpare( ) throws SQLException {
        return getInt32( AASRM_SPARE_FIELD_ID );
    }

    public String getAisAddressedSafetyRelatedMessageText( ) throws SQLException {
        return getString( AASRM_TEXT_FIELD_ID );
    }

    public DateTime getAisBaseStationReportMessageTimestamp( ) throws SQLException {
        return getDateTimeFromLong( ABSRM_TIMESTAMP_FIELD_ID );
    }

    public int getAisBaseStationReportMessagePositionAccuracy( ) throws SQLException {
        return getInt32( ABSRM_POSITIONACCURACY_FIELD_ID );
    }

    public double getAisBaseStationReportMessageLongitude( ) throws SQLException {
        return getDouble( ABSRM_LONGITUDE_FIELD_ID );
    }

    public double getAisBaseStationReportMessageLatitude( ) throws SQLException {
        return getDouble( ABSRM_LATITUDE_FIELD_ID );
    }

    public int getAisBaseStationReportMessagePositionFixType( ) throws SQLException {
        return getInt32( ABSRM_POSITIONFIXTYPE_FIELD_ID );
    }

    public int getAisBaseStationReportMessageSpare( ) throws SQLException {
        return getInt32( ABSRM_SPARE_FIELD_ID );
    }

    public int getAisBaseStationReportMessageRaim( ) throws SQLException {
        return getInt32( ABSRM_RAIM_FIELD_ID );
    }

    public int getAisBaseStationReportMessageRadioStatus( ) throws SQLException {
        return getInt32( ABSRM_RADIOSTATUS_FIELD_ID );
    }

    public int getAisBinaryAcknowledgeMessageSpare( ) throws SQLException {
        return getInt32( ABAC_SPARE_FIELD_ID );
    }

    public int getAisBinaryAcknowledgeMessageSequenceNumber1( ) throws SQLException {
        return getInt32( ABAC_SEQUENCENUMBER1_FIELD_ID );
    }

    public Guid getAisBinaryAcknowledgeMessageMmsi1( ) throws SQLException {
        return getNullableGuid( ABAC_MMSI1_FIELD_ID );
    }

    public Integer getAisBinaryAcknowledgeMessageSequenceNumber2( ) throws SQLException {
        return getNullableInt32( ABAC_SEQUENCENUMBER2_FIELD_ID );
    }

    public Guid getAisBinaryAcknowledgeMessageMmsi2( ) throws SQLException {
        return getNullableGuid( ABAC_MMSI2_FIELD_ID );
    }

    public Integer getAisBinaryAcknowledgeMessageSequenceNumber3( ) throws SQLException {
        return getNullableInt32( ABAC_SEQUENCENUMBER3_FIELD_ID );
    }

    public Guid getAisBinaryAcknowledgeMessageMmsi3( ) throws SQLException {
        return getNullableGuid( ABAC_MMSI3_FIELD_ID );
    }

    public Integer getAisBinaryAcknowledgeMessageSequenceNumber4( ) throws SQLException {
        return getNullableInt32( ABAC_SEQUENCENUMBER4_FIELD_ID );
    }

    public Guid getAisBinaryAcknowledgeMessageMmsi4( ) throws SQLException {
        return getNullableGuid( ABAC_MMSI4_FIELD_ID );
    }

    public int getAisBinaryAddressedMessageSequenceNumber( ) throws SQLException {
        return getInt32( ABAM_SEQUENCENUMBER_FIELD_ID );
    }

    public Guid getAisBinaryAddressedMessageDestinationMmsi( ) throws SQLException {
        return getNullableGuid( ABAM_DESTINATIONMMSI_FIELD_ID );
    }

    public boolean getAisBinaryAddressedMessageRetransmitFlag( ) throws SQLException {
        return getBoolean( ABAM_RETRANSMITFLAG_FIELD_ID );
    }

    public int getAisBinaryAddressedMessageSpare( ) throws SQLException {
        return getInt32( ABAM_SPARE_FIELD_ID );
    }

    public int getAisBinaryAddressedMessageDesignatedAreaCode( ) throws SQLException {
        return getInt32( ABAM_DESIGNATEDAREACODE_FIELD_ID );
    }

    public int getAisBinaryAddressedMessageFunctionalId( ) throws SQLException {
        return getInt32( ABAM_FUNCTIONALID_FIELD_ID );
    }

    public String getAisBinaryAddressedMessageData( ) throws SQLException {
        return getString( ABAM_DATA_FIELD_ID );
    }

    public int getAisBinaryBroadcastMessageSpare( ) throws SQLException {
        return getInt32( ABBM_SPARE_FIELD_ID );
    }

    public int getAisBinaryBroadcastMessageDesignatedAreaCode( ) throws SQLException {
        return getInt32( ABBM_DESIGNATEDAREACODE_FIELD_ID );
    }

    public int getAisBinaryBroadcastMessageFunctionalId( ) throws SQLException {
        return getInt32( ABBM_FUNCTIONALID_FIELD_ID );
    }

    public String getAisBinaryBroadcastMessageData( ) throws SQLException {
        return getString( ABBM_DATA_FIELD_ID );
    }

    public int getAisDataLinkManagementMessageSpare( ) throws SQLException {
        return getInt32( ADLMM_SPARE_FIELD_ID );
    }

    public int getAisDataLinkManagementMessageOffset1( ) throws SQLException {
        return getInt32( ADLMM_OFFSET1_FIELD_ID );
    }

    public int getAisDataLinkManagementMessageReservedSlots1( ) throws SQLException {
        return getInt32( ADLMM_RESERVEDSLOTS1_FIELD_ID );
    }

    public int getAisDataLinkManagementMessageTimeout1( ) throws SQLException {
        return getInt32( ADLMM_TIMEOUT1_FIELD_ID );
    }

    public int getAisDataLinkManagementMessageIncrement1( ) throws SQLException {
        return getInt32( ADLMM_INCREMENT1_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageOffset2( ) throws SQLException {
        return getNullableInt32( ADLMM_OFFSET2_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageReservedSlots2( ) throws SQLException {
        return getNullableInt32( ADLMM_RESERVEDSLOTS2_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageTimeout2( ) throws SQLException {
        return getNullableInt32( ADLMM_TIMEOUT2_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageIncrement2( ) throws SQLException {
        return getNullableInt32( ADLMM_INCREMENT2_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageOffset3( ) throws SQLException {
        return getNullableInt32( ADLMM_OFFSET3_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageReservedSlots3( ) throws SQLException {
        return getNullableInt32( ADLMM_RESERVEDSLOTS3_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageTimeout3( ) throws SQLException {
        return getNullableInt32( ADLMM_TIMEOUT3_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageIncrement3( ) throws SQLException {
        return getNullableInt32( ADLMM_INCREMENT3_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageOffset4( ) throws SQLException {
        return getNullableInt32( ADLMM_OFFSET4_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageReservedSlots4( ) throws SQLException {
        return getNullableInt32( ADLMM_RESERVEDSLOTS4_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageTimeout4( ) throws SQLException {
        return getNullableInt32( ADLMM_TIMEOUT4_FIELD_ID );
    }

    public Integer getAisDataLinkManagementMessageIncrement4( ) throws SQLException {
        return getNullableInt32( ADLMM_INCREMENT4_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessageReserved( ) throws SQLException {
        return getInt32( AECBPRM_RESERVED_FIELD_ID );
    }

    public double getAisExtendedClassBCsPositionReportMessageSpeedOverGround( ) throws SQLException {
        return getDouble( AECBPRM_SPEEDOVERGROUND_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessagePositionAccuracy( ) throws SQLException {
        return getInt32( AECBPRM_POSITIONACCURACY_FIELD_ID );
    }

    public double getAisExtendedClassBCsPositionReportMessageLongitude( ) throws SQLException {
        return getDouble( AECBPRM_LONGITUDE_FIELD_ID );
    }

    public double getAisExtendedClassBCsPositionReportMessageLatitude( ) throws SQLException {
        return getDouble( AECBPRM_LATITUDE_FIELD_ID );
    }

    public double getAisExtendedClassBCsPositionReportMessageCourseOverGround( ) throws SQLException {
        return getDouble( AECBPRM_COURSEOVERGROUND_FIELD_ID );
    }

    public Integer getAisExtendedClassBCsPositionReportMessageTrueHeading( ) throws SQLException {
        return getNullableInt32( AECBPRM_TRUEHEADING_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessageTimestamp( ) throws SQLException {
        return getInt32( AECBPRM_TIMESTAMP_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessageRegionalReserved( ) throws SQLException {
        return getInt32( AECBPRM_REGIONALRESERVED_FIELD_ID );
    }

    public Guid getAisExtendedClassBCsPositionReportMessageName( ) throws SQLException {
        return getNullableGuid( AECBPRM_NAME_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessageShipType( ) throws SQLException {
        return getInt32( AECBPRM_SHIPTYPE_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessageDimensionToBow( ) throws SQLException {
        return getInt32( AECBPRM_DIMENSIONTOBOW_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessageDimensionToStern( ) throws SQLException {
        return getInt32( AECBPRM_DIMENSIONTOSTERN_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessageDimensionToPort( ) throws SQLException {
        return getInt32( AECBPRM_DIMENSIONTOPORT_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessageDimensionToStarboard( ) throws SQLException {
        return getInt32( AECBPRM_DIMENSIONTOSTARBOARD_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessagePositionFixType( ) throws SQLException {
        return getInt32( AECBPRM_POSITIONFIXTYPE_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessageRaim( ) throws SQLException {
        return getInt32( AECBPRM_RAIM_FIELD_ID );
    }

    public boolean getAisExtendedClassBCsPositionReportMessageDataTerminalReady( ) throws SQLException {
        return getBoolean( AECBPRM_DATATERMINALREADY_FIELD_ID );
    }

    public boolean getAisExtendedClassBCsPositionReportMessageAssigned( ) throws SQLException {
        return getBoolean( AECBPRM_ASSIGNED_FIELD_ID );
    }

    public int getAisExtendedClassBCsPositionReportMessageSpare( ) throws SQLException {
        return getInt32( AECBPRM_SPARE_FIELD_ID );
    }

    public Guid getAisInterrogationMessageInterrogatedMmsi( ) throws SQLException {
        return getNullableGuid( AIM_INTERROGATEDMMSI_FIELD_ID );
    }

    public int getAisInterrogationMessageFirstMessageType( ) throws SQLException {
        return getInt32( AIM_FIRSTMESSAGETYPE_FIELD_ID );
    }

    public int getAisInterrogationMessageFirstSlotOffset( ) throws SQLException {
        return getInt32( AIM_FIRSTSLOTOFFSET_FIELD_ID );
    }

    public Integer getAisInterrogationMessageSecondMessageType( ) throws SQLException {
        return getNullableInt32( AIM_SECONDMESSAGETYPE_FIELD_ID );
    }

    public Integer getAisInterrogationMessageSecondSlotOffset( ) throws SQLException {
        return getNullableInt32( AIM_SECONDSLOTOFFSET_FIELD_ID );
    }

    public Guid getAisInterrogationMessageSecondStationInterrogationMmsi( ) throws SQLException {
        return getNullableGuid( AIM_SECONDSTATIONINTERROGATIONMMSI_FIELD_ID );
    }

    public Integer getAisInterrogationMessageSecondStationFirstMessageType( ) throws SQLException {
        return getNullableInt32( AIM_SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID );
    }

    public Integer getAisInterrogationMessageSecondStationFirstSlotOffset( ) throws SQLException {
        return getNullableInt32( AIM_SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID );
    }

    public int getAisPositionReportClassAMessageBaseNavigationStatus( ) throws SQLException {
        return getInt32( APRCAB_NAVIGATIONSTATUS_FIELD_ID );
    }

    public Integer getAisPositionReportClassAMessageBaseRateOfTurn( ) throws SQLException {
        return getNullableInt32( APRCAB_RATEOFTURN_FIELD_ID );
    }

    public double getAisPositionReportClassAMessageBaseSpeedOverGround( ) throws SQLException {
        return getDouble( APRCAB_SPEEDOVERGROUND_FIELD_ID );
    }

    public int getAisPositionReportClassAMessageBasePositionAccuracy( ) throws SQLException {
        return getInt32( APRCAB_POSITIONACCURACY_FIELD_ID );
    }

    public double getAisPositionReportClassAMessageBaseLongitude( ) throws SQLException {
        return getDouble( APRCAB_LONGITUDE_FIELD_ID );
    }

    public double getAisPositionReportClassAMessageBaseLatitude( ) throws SQLException {
        return getDouble( APRCAB_LATITUDE_FIELD_ID );
    }

    public double getAisPositionReportClassAMessageBaseCourseOverGround( ) throws SQLException {
        return getDouble( APRCAB_COURSEOVERGROUND_FIELD_ID );
    }

    public Integer getAisPositionReportClassAMessageBaseTrueHeading( ) throws SQLException {
        return getNullableInt32( APRCAB_TRUEHEADING_FIELD_ID );
    }

    public int getAisPositionReportClassAMessageBaseTimestamp( ) throws SQLException {
        return getInt32( APRCAB_TIMESTAMP_FIELD_ID );
    }

    public int getAisPositionReportClassAMessageBaseManeuverIndicator( ) throws SQLException {
        return getInt32( APRCAB_MANEUVERINDICATOR_FIELD_ID );
    }

    public int getAisPositionReportClassAMessageBaseSpare( ) throws SQLException {
        return getInt32( APRCAB_SPARE_FIELD_ID );
    }

    public int getAisPositionReportClassAMessageBaseRaim( ) throws SQLException {
        return getInt32( APRCAB_RAIM_FIELD_ID );
    }

    public int getAisPositionReportClassAMessageBaseRadioStatus( ) throws SQLException {
        return getInt32( APRCAB_RADIOSTATUS_FIELD_ID );
    }

    public int getAisPositionReportForLongRangeApplicationsMessagePositionAccuracy( ) throws SQLException {
        return getInt32( APRFLRAM_POSITIONACCURACY_FIELD_ID );
    }

    public int getAisPositionReportForLongRangeApplicationsMessageRaim( ) throws SQLException {
        return getInt32( APRFLRAM_RAIM_FIELD_ID );
    }

    public int getAisPositionReportForLongRangeApplicationsMessageNavigationStatus( ) throws SQLException {
        return getInt32( APRFLRAM_NAVIGATIONSTATUS_FIELD_ID );
    }

    public double getAisPositionReportForLongRangeApplicationsMessageLongitude( ) throws SQLException {
        return getDouble( APRFLRAM_LONGITUDE_FIELD_ID );
    }

    public double getAisPositionReportForLongRangeApplicationsMessageLatitude( ) throws SQLException {
        return getDouble( APRFLRAM_LATITUDE_FIELD_ID );
    }

    public double getAisPositionReportForLongRangeApplicationsMessageSpeedOverGround( ) throws SQLException {
        return getDouble( APRFLRAM_SPEEDOVERGROUND_FIELD_ID );
    }

    public double getAisPositionReportForLongRangeApplicationsMessageCourseOverGround( ) throws SQLException {
        return getDouble( APRFLRAM_COURSEOVERGROUND_FIELD_ID );
    }

    public int getAisPositionReportForLongRangeApplicationsMessageGnssPositionStatus( ) throws SQLException {
        return getInt32( APRFLRAM_GNSSPOSITIONSTATUS_FIELD_ID );
    }

    public int getAisPositionReportForLongRangeApplicationsMessageSpare( ) throws SQLException {
        return getInt32( APRFLRAM_SPARE_FIELD_ID );
    }

    public int getAisSafetyRelatedAcknowledgmentMessageSpare( ) throws SQLException {
        return getInt32( ASRAM_SPARE_FIELD_ID );
    }

    public int getAisSafetyRelatedAcknowledgmentMessageSequenceNumber1( ) throws SQLException {
        return getInt32( ASRAM_SEQUENCENUMBER1_FIELD_ID );
    }

    public Guid getAisSafetyRelatedAcknowledgmentMessageMmsi1( ) throws SQLException {
        return getNullableGuid( ASRAM_MMSI1_FIELD_ID );
    }

    public Integer getAisSafetyRelatedAcknowledgmentMessageSequenceNumber2( ) throws SQLException {
        return getNullableInt32( ASRAM_SEQUENCENUMBER2_FIELD_ID );
    }

    public Guid getAisSafetyRelatedAcknowledgmentMessageMmsi2( ) throws SQLException {
        return getNullableGuid( ASRAM_MMSI2_FIELD_ID );
    }

    public Integer getAisSafetyRelatedAcknowledgmentMessageSequenceNumber3( ) throws SQLException {
        return getNullableInt32( ASRAM_SEQUENCENUMBER3_FIELD_ID );
    }

    public Guid getAisSafetyRelatedAcknowledgmentMessageMmsi3( ) throws SQLException {
        return getNullableGuid( ASRAM_MMSI3_FIELD_ID );
    }

    public Integer getAisSafetyRelatedAcknowledgmentMessageSequenceNumber4( ) throws SQLException {
        return getNullableInt32( ASRAM_SEQUENCENUMBER4_FIELD_ID );
    }

    public Guid getAisSafetyRelatedAcknowledgmentMessageMmsi4( ) throws SQLException {
        return getNullableGuid( ASRAM_MMSI4_FIELD_ID );
    }

    public int getAisStandardClassBCsPositionReportMessageReserved( ) throws SQLException {
        return getInt32( ASCBPRM_RESERVED_FIELD_ID );
    }

    public double getAisStandardClassBCsPositionReportMessageSpeedOverGround( ) throws SQLException {
        return getDouble( ASCBPRM_SPEEDOVERGROUND_FIELD_ID );
    }

    public int getAisStandardClassBCsPositionReportMessagePositionAccuracy( ) throws SQLException {
        return getInt32( ASCBPRM_POSITIONACCURACY_FIELD_ID );
    }

    public double getAisStandardClassBCsPositionReportMessageLongitude( ) throws SQLException {
        return getDouble( ASCBPRM_LONGITUDE_FIELD_ID );
    }

    public double getAisStandardClassBCsPositionReportMessageLatitude( ) throws SQLException {
        return getDouble( ASCBPRM_LATITUDE_FIELD_ID );
    }

    public double getAisStandardClassBCsPositionReportMessageCourseOverGround( ) throws SQLException {
        return getDouble( ASCBPRM_COURSEOVERGROUND_FIELD_ID );
    }

    public Integer getAisStandardClassBCsPositionReportMessageTrueHeading( ) throws SQLException {
        return getNullableInt32( ASCBPRM_TRUEHEADING_FIELD_ID );
    }

    public int getAisStandardClassBCsPositionReportMessageTimestamp( ) throws SQLException {
        return getInt32( ASCBPRM_TIMESTAMP_FIELD_ID );
    }

    public int getAisStandardClassBCsPositionReportMessageRegionalReserved( ) throws SQLException {
        return getInt32( ASCBPRM_REGIONALRESERVED_FIELD_ID );
    }

    public boolean getAisStandardClassBCsPositionReportMessageIsCsUnit( ) throws SQLException {
        return getBoolean( ASCBPRM_ISCSUNIT_FIELD_ID );
    }

    public boolean getAisStandardClassBCsPositionReportMessageHasDisplay( ) throws SQLException {
        return getBoolean( ASCBPRM_HASDISPLAY_FIELD_ID );
    }

    public boolean getAisStandardClassBCsPositionReportMessageHasDscCapability( ) throws SQLException {
        return getBoolean( ASCBPRM_HASDSCCAPABILITY_FIELD_ID );
    }

    public boolean getAisStandardClassBCsPositionReportMessageBand( ) throws SQLException {
        return getBoolean( ASCBPRM_BAND_FIELD_ID );
    }

    public boolean getAisStandardClassBCsPositionReportMessageCanAcceptMessage22( ) throws SQLException {
        return getBoolean( ASCBPRM_CANACCEPTMESSAGE22_FIELD_ID );
    }

    public boolean getAisStandardClassBCsPositionReportMessageAssigned( ) throws SQLException {
        return getBoolean( ASCBPRM_ASSIGNED_FIELD_ID );
    }

    public int getAisStandardClassBCsPositionReportMessageRaim( ) throws SQLException {
        return getInt32( ASCBPRM_RAIM_FIELD_ID );
    }

    public int getAisStandardClassBCsPositionReportMessageRadioStatus( ) throws SQLException {
        return getInt32( ASCBPRM_RADIOSTATUS_FIELD_ID );
    }

    public int getAisStandardSarAircraftPositionReportMessageAltitude( ) throws SQLException {
        return getInt32( ASSAPRM_ALTITUDE_FIELD_ID );
    }

    public int getAisStandardSarAircraftPositionReportMessageSpeedOverGround( ) throws SQLException {
        return getInt32( ASSAPRM_SPEEDOVERGROUND_FIELD_ID );
    }

    public int getAisStandardSarAircraftPositionReportMessagePositionAccuracy( ) throws SQLException {
        return getInt32( ASSAPRM_POSITIONACCURACY_FIELD_ID );
    }

    public double getAisStandardSarAircraftPositionReportMessageLongitude( ) throws SQLException {
        return getDouble( ASSAPRM_LONGITUDE_FIELD_ID );
    }

    public double getAisStandardSarAircraftPositionReportMessageLatitude( ) throws SQLException {
        return getDouble( ASSAPRM_LATITUDE_FIELD_ID );
    }

    public double getAisStandardSarAircraftPositionReportMessageCourseOverGround( ) throws SQLException {
        return getDouble( ASSAPRM_COURSEOVERGROUND_FIELD_ID );
    }

    public int getAisStandardSarAircraftPositionReportMessageTimestamp( ) throws SQLException {
        return getInt32( ASSAPRM_TIMESTAMP_FIELD_ID );
    }

    public int getAisStandardSarAircraftPositionReportMessageReserved( ) throws SQLException {
        return getInt32( ASSAPRM_RESERVED_FIELD_ID );
    }

    public boolean getAisStandardSarAircraftPositionReportMessageDataTerminalReady( ) throws SQLException {
        return getBoolean( ASSAPRM_DATATERMINALREADY_FIELD_ID );
    }

    public int getAisStandardSarAircraftPositionReportMessageSpare( ) throws SQLException {
        return getInt32( ASSAPRM_SPARE_FIELD_ID );
    }

    public boolean getAisStandardSarAircraftPositionReportMessageAssigned( ) throws SQLException {
        return getBoolean( ASSAPRM_ASSIGNED_FIELD_ID );
    }

    public int getAisStandardSarAircraftPositionReportMessageRaim( ) throws SQLException {
        return getInt32( ASSAPRM_RAIM_FIELD_ID );
    }

    public int getAisStandardSarAircraftPositionReportMessageRadioStatus( ) throws SQLException {
        return getInt32( ASSAPRM_RADIOSTATUS_FIELD_ID );
    }

    public int getAisStaticAndVoyageRelatedDataMessageAisVersion( ) throws SQLException {
        return getInt32( ASAVRDM_AISVERSION_FIELD_ID );
    }

    public Guid getAisStaticAndVoyageRelatedDataMessageImoNumber( ) throws SQLException {
        return getNullableGuid( ASAVRDM_IMONUMBER_FIELD_ID );
    }

    public Guid getAisStaticAndVoyageRelatedDataMessageCallsign( ) throws SQLException {
        return getNullableGuid( ASAVRDM_CALLSIGN_FIELD_ID );
    }

    public Guid getAisStaticAndVoyageRelatedDataMessageShipName( ) throws SQLException {
        return getNullableGuid( ASAVRDM_SHIPNAME_FIELD_ID );
    }

    public int getAisStaticAndVoyageRelatedDataMessageShipType( ) throws SQLException {
        return getInt32( ASAVRDM_SHIPTYPE_FIELD_ID );
    }

    public int getAisStaticAndVoyageRelatedDataMessageDimensionToBow( ) throws SQLException {
        return getInt32( ASAVRDM_DIMENSIONTOBOW_FIELD_ID );
    }

    public int getAisStaticAndVoyageRelatedDataMessageDimensionToStern( ) throws SQLException {
        return getInt32( ASAVRDM_DIMENSIONTOSTERN_FIELD_ID );
    }

    public int getAisStaticAndVoyageRelatedDataMessageDimensionToPort( ) throws SQLException {
        return getInt32( ASAVRDM_DIMENSIONTOPORT_FIELD_ID );
    }

    public int getAisStaticAndVoyageRelatedDataMessageDimensionToStarboard( ) throws SQLException {
        return getInt32( ASAVRDM_DIMENSIONTOSTARBOARD_FIELD_ID );
    }

    public int getAisStaticAndVoyageRelatedDataMessagePositionFixType( ) throws SQLException {
        return getInt32( ASAVRDM_POSITIONFIXTYPE_FIELD_ID );
    }

    public DateTime getAisStaticAndVoyageRelatedDataMessageEstimatedTimeOfArrival( ) throws SQLException {
        return getNullableDateTimeFromLong( ASAVRDM_ESTIMATEDTIMEOFARRIVAL_FIELD_ID );
    }

    public double getAisStaticAndVoyageRelatedDataMessageDraught( ) throws SQLException {
        return getDouble( ASAVRDM_DRAUGHT_FIELD_ID );
    }

    public String getAisStaticAndVoyageRelatedDataMessageDestination( ) throws SQLException {
        return getString( ASAVRDM_DESTINATION_FIELD_ID );
    }

    public boolean getAisStaticAndVoyageRelatedDataMessageDataTerminalReady( ) throws SQLException {
        return getBoolean( ASAVRDM_DATATERMINALREADY_FIELD_ID );
    }

    public int getAisStaticAndVoyageRelatedDataMessageSpare( ) throws SQLException {
        return getInt32( ASAVRDM_SPARE_FIELD_ID );
    }

    public int getAisStaticDataReportMessagePartNumber( ) throws SQLException {
        return getInt32( ASDRM_PARTNUMBER_FIELD_ID );
    }

    public Guid getAisStaticDataReportPartAMessageShipName( ) throws SQLException {
        return getNullableGuid( ASDRPA_SHIPNAME_FIELD_ID );
    }

    public int getAisStaticDataReportPartAMessageSpare( ) throws SQLException {
        return getInt32( ASDRPA_SPARE_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageShipType( ) throws SQLException {
        return getInt32( ASDRPB_SHIPTYPE_FIELD_ID );
    }

    public String getAisStaticDataReportPartBMessageVendorId( ) throws SQLException {
        return getString( ASDRPB_VENDORID_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageUnitModelCode( ) throws SQLException {
        return getInt32( ASDRPB_UNITMODELCODE_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageSerialNumber( ) throws SQLException {
        return getInt32( ASDRPB_SERIALNUMBER_FIELD_ID );
    }

    public Guid getAisStaticDataReportPartBMessageCallsign( ) throws SQLException {
        return getNullableGuid( ASDRPB_CALLSIGN_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageDimensionToBow( ) throws SQLException {
        return getInt32( ASDRPB_DIMENSIONTOBOW_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageDimensionToStern( ) throws SQLException {
        return getInt32( ASDRPB_DIMENSIONTOSTERN_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageDimensionToPort( ) throws SQLException {
        return getInt32( ASDRPB_DIMENSIONTOPORT_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageDimensionToStarboard( ) throws SQLException {
        return getInt32( ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID );
    }

    public Guid getAisStaticDataReportPartBMessageMothershipMmsi( ) throws SQLException {
        return getNullableGuid( ASDRPB_MOTHERSHIPMMSI_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessagePositionFixType( ) throws SQLException {
        return getInt32( ASDRPB_POSITIONFIXTYPE_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageSpare( ) throws SQLException {
        return getInt32( ASDRPB_SPARE_FIELD_ID );
    }

    public int getAisUtcAndDateInquiryMessageSpare1( ) throws SQLException {
        return getInt32( AUADIM_SPARE1_FIELD_ID );
    }

    public Guid getAisUtcAndDateInquiryMessageDestinationMmsi( ) throws SQLException {
        return getNullableGuid( AUADIM_DESTINATIONMMSI_FIELD_ID );
    }

    public int getAisUtcAndDateInquiryMessageSpare2( ) throws SQLException {
        return getInt32( AUADIM_SPARE2_FIELD_ID );
    }

    public DateTime getAisUtcAndDateResponseMessageDatetime( ) throws SQLException {
        return getDateTimeFromLong( AUADRM_DATETIME_FIELD_ID );
    }

    public int getAisUtcAndDateResponseMessagePositionAccuracy( ) throws SQLException {
        return getInt32( AUADRM_POSITIONACCURACY_FIELD_ID );
    }

    public double getAisUtcAndDateResponseMessageLongitude( ) throws SQLException {
        return getDouble( AUADRM_LONGITUDE_FIELD_ID );
    }

    public double getAisUtcAndDateResponseMessageLatitude( ) throws SQLException {
        return getDouble( AUADRM_LATITUDE_FIELD_ID );
    }

    public int getAisUtcAndDateResponseMessagePositionFixType( ) throws SQLException {
        return getInt32( AUADRM_POSITIONFIXTYPE_FIELD_ID );
    }

    public int getAisUtcAndDateResponseMessageSpare( ) throws SQLException {
        return getInt32( AUADRM_SPARE_FIELD_ID );
    }

    public int getAisUtcAndDateResponseMessageRaim( ) throws SQLException {
        return getInt32( AUADRM_RAIM_FIELD_ID );
    }

    public int getAisUtcAndDateResponseMessageRadioStatus( ) throws SQLException {
        return getInt32( AUADRM_RADIOSTATUS_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.AidToNavigationReportMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAidToNavigationReportMessageNavigationalAidType( ) );
                destination.writeStringUtf8( getAidToNavigationReportMessageName( ) );
                destination.writeInt32( getAidToNavigationReportMessagePositionAccuracy( ) );
                destination.writeDouble( getAidToNavigationReportMessageLongitude( ) );
                destination.writeDouble( getAidToNavigationReportMessageLatitude( ) );
                destination.writeInt32( getAidToNavigationReportMessageDimensionToBow( ) );
                destination.writeInt32( getAidToNavigationReportMessageDimensionToStern( ) );
                destination.writeInt32( getAidToNavigationReportMessageDimensionToPort( ) );
                destination.writeInt32( getAidToNavigationReportMessageDimensionToStarboard( ) );
                destination.writeInt32( getAidToNavigationReportMessagePositionFixType( ) );
                destination.writeInt32( getAidToNavigationReportMessageTimestamp( ) );
                destination.writeBoolean( getAidToNavigationReportMessageOffPosition( ) );
                destination.writeInt32( getAidToNavigationReportMessageRegionalReserved( ) );
                destination.writeInt32( getAidToNavigationReportMessageRaim( ) );
                destination.writeBoolean( getAidToNavigationReportMessageVirtualAid( ) );
                destination.writeBoolean( getAidToNavigationReportMessageAssigned( ) );
                destination.writeInt32( getAidToNavigationReportMessageSpare( ) );
                destination.writeStringUtf8( getAidToNavigationReportMessageNameExtension( ) );
            }
            break;
            case Kind.AisAddressedSafetyRelatedMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisAddressedSafetyRelatedMessageSequenceNumber( ) );
                destination.writeNullableGuid( getAisAddressedSafetyRelatedMessageDestinationMmsi( ) );
                destination.writeBoolean( getAisAddressedSafetyRelatedMessageRetransmitFlag( ) );
                destination.writeInt32( getAisAddressedSafetyRelatedMessageSpare( ) );
                destination.writeStringUtf8( getAisAddressedSafetyRelatedMessageText( ) );
            }
            break;
            case Kind.AisBaseStationReportMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeDateTime( getAisBaseStationReportMessageTimestamp( ) );
                destination.writeInt32( getAisBaseStationReportMessagePositionAccuracy( ) );
                destination.writeDouble( getAisBaseStationReportMessageLongitude( ) );
                destination.writeDouble( getAisBaseStationReportMessageLatitude( ) );
                destination.writeInt32( getAisBaseStationReportMessagePositionFixType( ) );
                destination.writeInt32( getAisBaseStationReportMessageSpare( ) );
                destination.writeInt32( getAisBaseStationReportMessageRaim( ) );
                destination.writeInt32( getAisBaseStationReportMessageRadioStatus( ) );
            }
            break;
            case Kind.AisBinaryAcknowledgeMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisBinaryAcknowledgeMessageSpare( ) );
                destination.writeInt32( getAisBinaryAcknowledgeMessageSequenceNumber1( ) );
                destination.writeNullableGuid( getAisBinaryAcknowledgeMessageMmsi1( ) );
                destination.writeNullableInt32( getAisBinaryAcknowledgeMessageSequenceNumber2( ) );
                destination.writeNullableGuid( getAisBinaryAcknowledgeMessageMmsi2( ) );
                destination.writeNullableInt32( getAisBinaryAcknowledgeMessageSequenceNumber3( ) );
                destination.writeNullableGuid( getAisBinaryAcknowledgeMessageMmsi3( ) );
                destination.writeNullableInt32( getAisBinaryAcknowledgeMessageSequenceNumber4( ) );
                destination.writeNullableGuid( getAisBinaryAcknowledgeMessageMmsi4( ) );
            }
            break;
            case Kind.AisBinaryAddressedMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisBinaryAddressedMessageSequenceNumber( ) );
                destination.writeNullableGuid( getAisBinaryAddressedMessageDestinationMmsi( ) );
                destination.writeBoolean( getAisBinaryAddressedMessageRetransmitFlag( ) );
                destination.writeInt32( getAisBinaryAddressedMessageSpare( ) );
                destination.writeInt32( getAisBinaryAddressedMessageDesignatedAreaCode( ) );
                destination.writeInt32( getAisBinaryAddressedMessageFunctionalId( ) );
                destination.writeStringUtf8( getAisBinaryAddressedMessageData( ) );
            }
            break;
            case Kind.AisBinaryBroadcastMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisBinaryBroadcastMessageSpare( ) );
                destination.writeInt32( getAisBinaryBroadcastMessageDesignatedAreaCode( ) );
                destination.writeInt32( getAisBinaryBroadcastMessageFunctionalId( ) );
                destination.writeStringUtf8( getAisBinaryBroadcastMessageData( ) );
            }
            break;
            case Kind.AisDataLinkManagementMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisDataLinkManagementMessageSpare( ) );
                destination.writeInt32( getAisDataLinkManagementMessageOffset1( ) );
                destination.writeInt32( getAisDataLinkManagementMessageReservedSlots1( ) );
                destination.writeInt32( getAisDataLinkManagementMessageTimeout1( ) );
                destination.writeInt32( getAisDataLinkManagementMessageIncrement1( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageOffset2( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageReservedSlots2( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageTimeout2( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageIncrement2( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageOffset3( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageReservedSlots3( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageTimeout3( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageIncrement3( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageOffset4( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageReservedSlots4( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageTimeout4( ) );
                destination.writeNullableInt32( getAisDataLinkManagementMessageIncrement4( ) );
            }
            break;
            case Kind.AisExtendedClassBCsPositionReportMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessageReserved( ) );
                destination.writeDouble( getAisExtendedClassBCsPositionReportMessageSpeedOverGround( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessagePositionAccuracy( ) );
                destination.writeDouble( getAisExtendedClassBCsPositionReportMessageLongitude( ) );
                destination.writeDouble( getAisExtendedClassBCsPositionReportMessageLatitude( ) );
                destination.writeDouble( getAisExtendedClassBCsPositionReportMessageCourseOverGround( ) );
                destination.writeNullableInt32( getAisExtendedClassBCsPositionReportMessageTrueHeading( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessageTimestamp( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessageRegionalReserved( ) );
                destination.writeNullableGuid( getAisExtendedClassBCsPositionReportMessageName( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessageShipType( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessageDimensionToBow( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessageDimensionToStern( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessageDimensionToPort( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessageDimensionToStarboard( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessagePositionFixType( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessageRaim( ) );
                destination.writeBoolean( getAisExtendedClassBCsPositionReportMessageDataTerminalReady( ) );
                destination.writeBoolean( getAisExtendedClassBCsPositionReportMessageAssigned( ) );
                destination.writeInt32( getAisExtendedClassBCsPositionReportMessageSpare( ) );
            }
            break;
            case Kind.AisInterrogationMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeNullableGuid( getAisInterrogationMessageInterrogatedMmsi( ) );
                destination.writeInt32( getAisInterrogationMessageFirstMessageType( ) );
                destination.writeInt32( getAisInterrogationMessageFirstSlotOffset( ) );
                destination.writeNullableInt32( getAisInterrogationMessageSecondMessageType( ) );
                destination.writeNullableInt32( getAisInterrogationMessageSecondSlotOffset( ) );
                destination.writeNullableGuid( getAisInterrogationMessageSecondStationInterrogationMmsi( ) );
                destination.writeNullableInt32( getAisInterrogationMessageSecondStationFirstMessageType( ) );
                destination.writeNullableInt32( getAisInterrogationMessageSecondStationFirstSlotOffset( ) );
            }
            break;
            case Kind.AisPositionReportClassAAssignedScheduleMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseNavigationStatus( ) );
                destination.writeNullableInt32( getAisPositionReportClassAMessageBaseRateOfTurn( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseSpeedOverGround( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBasePositionAccuracy( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseLongitude( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseLatitude( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseCourseOverGround( ) );
                destination.writeNullableInt32( getAisPositionReportClassAMessageBaseTrueHeading( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseTimestamp( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseManeuverIndicator( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseSpare( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseRaim( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseRadioStatus( ) );
            }
            break;
            case Kind.AisPositionReportClassAMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseNavigationStatus( ) );
                destination.writeNullableInt32( getAisPositionReportClassAMessageBaseRateOfTurn( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseSpeedOverGround( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBasePositionAccuracy( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseLongitude( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseLatitude( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseCourseOverGround( ) );
                destination.writeNullableInt32( getAisPositionReportClassAMessageBaseTrueHeading( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseTimestamp( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseManeuverIndicator( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseSpare( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseRaim( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseRadioStatus( ) );
            }
            break;
            case Kind.AisPositionReportClassAResponseToInterrogationMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseNavigationStatus( ) );
                destination.writeNullableInt32( getAisPositionReportClassAMessageBaseRateOfTurn( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseSpeedOverGround( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBasePositionAccuracy( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseLongitude( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseLatitude( ) );
                destination.writeDouble( getAisPositionReportClassAMessageBaseCourseOverGround( ) );
                destination.writeNullableInt32( getAisPositionReportClassAMessageBaseTrueHeading( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseTimestamp( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseManeuverIndicator( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseSpare( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseRaim( ) );
                destination.writeInt32( getAisPositionReportClassAMessageBaseRadioStatus( ) );
            }
            break;
            case Kind.AisPositionReportForLongRangeApplicationsMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisPositionReportForLongRangeApplicationsMessagePositionAccuracy( ) );
                destination.writeInt32( getAisPositionReportForLongRangeApplicationsMessageRaim( ) );
                destination.writeInt32( getAisPositionReportForLongRangeApplicationsMessageNavigationStatus( ) );
                destination.writeDouble( getAisPositionReportForLongRangeApplicationsMessageLongitude( ) );
                destination.writeDouble( getAisPositionReportForLongRangeApplicationsMessageLatitude( ) );
                destination.writeDouble( getAisPositionReportForLongRangeApplicationsMessageSpeedOverGround( ) );
                destination.writeDouble( getAisPositionReportForLongRangeApplicationsMessageCourseOverGround( ) );
                destination.writeInt32( getAisPositionReportForLongRangeApplicationsMessageGnssPositionStatus( ) );
                destination.writeInt32( getAisPositionReportForLongRangeApplicationsMessageSpare( ) );
            }
            break;
            case Kind.AisSafetyRelatedAcknowledgmentMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisSafetyRelatedAcknowledgmentMessageSpare( ) );
                destination.writeInt32( getAisSafetyRelatedAcknowledgmentMessageSequenceNumber1( ) );
                destination.writeNullableGuid( getAisSafetyRelatedAcknowledgmentMessageMmsi1( ) );
                destination.writeNullableInt32( getAisSafetyRelatedAcknowledgmentMessageSequenceNumber2( ) );
                destination.writeNullableGuid( getAisSafetyRelatedAcknowledgmentMessageMmsi2( ) );
                destination.writeNullableInt32( getAisSafetyRelatedAcknowledgmentMessageSequenceNumber3( ) );
                destination.writeNullableGuid( getAisSafetyRelatedAcknowledgmentMessageMmsi3( ) );
                destination.writeNullableInt32( getAisSafetyRelatedAcknowledgmentMessageSequenceNumber4( ) );
                destination.writeNullableGuid( getAisSafetyRelatedAcknowledgmentMessageMmsi4( ) );
            }
            break;
            case Kind.AisStandardClassBCsPositionReportMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisStandardClassBCsPositionReportMessageReserved( ) );
                destination.writeDouble( getAisStandardClassBCsPositionReportMessageSpeedOverGround( ) );
                destination.writeInt32( getAisStandardClassBCsPositionReportMessagePositionAccuracy( ) );
                destination.writeDouble( getAisStandardClassBCsPositionReportMessageLongitude( ) );
                destination.writeDouble( getAisStandardClassBCsPositionReportMessageLatitude( ) );
                destination.writeDouble( getAisStandardClassBCsPositionReportMessageCourseOverGround( ) );
                destination.writeNullableInt32( getAisStandardClassBCsPositionReportMessageTrueHeading( ) );
                destination.writeInt32( getAisStandardClassBCsPositionReportMessageTimestamp( ) );
                destination.writeInt32( getAisStandardClassBCsPositionReportMessageRegionalReserved( ) );
                destination.writeBoolean( getAisStandardClassBCsPositionReportMessageIsCsUnit( ) );
                destination.writeBoolean( getAisStandardClassBCsPositionReportMessageHasDisplay( ) );
                destination.writeBoolean( getAisStandardClassBCsPositionReportMessageHasDscCapability( ) );
                destination.writeBoolean( getAisStandardClassBCsPositionReportMessageBand( ) );
                destination.writeBoolean( getAisStandardClassBCsPositionReportMessageCanAcceptMessage22( ) );
                destination.writeBoolean( getAisStandardClassBCsPositionReportMessageAssigned( ) );
                destination.writeInt32( getAisStandardClassBCsPositionReportMessageRaim( ) );
                destination.writeInt32( getAisStandardClassBCsPositionReportMessageRadioStatus( ) );
            }
            break;
            case Kind.AisStandardSarAircraftPositionReportMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisStandardSarAircraftPositionReportMessageAltitude( ) );
                destination.writeInt32( getAisStandardSarAircraftPositionReportMessageSpeedOverGround( ) );
                destination.writeInt32( getAisStandardSarAircraftPositionReportMessagePositionAccuracy( ) );
                destination.writeDouble( getAisStandardSarAircraftPositionReportMessageLongitude( ) );
                destination.writeDouble( getAisStandardSarAircraftPositionReportMessageLatitude( ) );
                destination.writeDouble( getAisStandardSarAircraftPositionReportMessageCourseOverGround( ) );
                destination.writeInt32( getAisStandardSarAircraftPositionReportMessageTimestamp( ) );
                destination.writeInt32( getAisStandardSarAircraftPositionReportMessageReserved( ) );
                destination.writeBoolean( getAisStandardSarAircraftPositionReportMessageDataTerminalReady( ) );
                destination.writeInt32( getAisStandardSarAircraftPositionReportMessageSpare( ) );
                destination.writeBoolean( getAisStandardSarAircraftPositionReportMessageAssigned( ) );
                destination.writeInt32( getAisStandardSarAircraftPositionReportMessageRaim( ) );
                destination.writeInt32( getAisStandardSarAircraftPositionReportMessageRadioStatus( ) );
            }
            break;
            case Kind.AisStaticAndVoyageRelatedDataMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisStaticAndVoyageRelatedDataMessageAisVersion( ) );
                destination.writeNullableGuid( getAisStaticAndVoyageRelatedDataMessageImoNumber( ) );
                destination.writeNullableGuid( getAisStaticAndVoyageRelatedDataMessageCallsign( ) );
                destination.writeNullableGuid( getAisStaticAndVoyageRelatedDataMessageShipName( ) );
                destination.writeInt32( getAisStaticAndVoyageRelatedDataMessageShipType( ) );
                destination.writeInt32( getAisStaticAndVoyageRelatedDataMessageDimensionToBow( ) );
                destination.writeInt32( getAisStaticAndVoyageRelatedDataMessageDimensionToStern( ) );
                destination.writeInt32( getAisStaticAndVoyageRelatedDataMessageDimensionToPort( ) );
                destination.writeInt32( getAisStaticAndVoyageRelatedDataMessageDimensionToStarboard( ) );
                destination.writeInt32( getAisStaticAndVoyageRelatedDataMessagePositionFixType( ) );
                destination.writeNullableDateTime( getAisStaticAndVoyageRelatedDataMessageEstimatedTimeOfArrival( ) );
                destination.writeDouble( getAisStaticAndVoyageRelatedDataMessageDraught( ) );
                destination.writeStringUtf8( getAisStaticAndVoyageRelatedDataMessageDestination( ) );
                destination.writeBoolean( getAisStaticAndVoyageRelatedDataMessageDataTerminalReady( ) );
                destination.writeInt32( getAisStaticAndVoyageRelatedDataMessageSpare( ) );
            }
            break;
            case Kind.AisStaticDataReportMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisStaticDataReportMessagePartNumber( ) );
            }
            break;
            case Kind.AisStaticDataReportPartAMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisStaticDataReportMessagePartNumber( ) );
                destination.writeNullableGuid( getAisStaticDataReportPartAMessageShipName( ) );
                destination.writeInt32( getAisStaticDataReportPartAMessageSpare( ) );
            }
            break;
            case Kind.AisStaticDataReportPartBMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisStaticDataReportMessagePartNumber( ) );
                destination.writeInt32( getAisStaticDataReportPartBMessageShipType( ) );
                destination.writeStringUtf8( getAisStaticDataReportPartBMessageVendorId( ) );
                destination.writeInt32( getAisStaticDataReportPartBMessageUnitModelCode( ) );
                destination.writeInt32( getAisStaticDataReportPartBMessageSerialNumber( ) );
                destination.writeNullableGuid( getAisStaticDataReportPartBMessageCallsign( ) );
                destination.writeInt32( getAisStaticDataReportPartBMessageDimensionToBow( ) );
                destination.writeInt32( getAisStaticDataReportPartBMessageDimensionToStern( ) );
                destination.writeInt32( getAisStaticDataReportPartBMessageDimensionToPort( ) );
                destination.writeInt32( getAisStaticDataReportPartBMessageDimensionToStarboard( ) );
                destination.writeNullableGuid( getAisStaticDataReportPartBMessageMothershipMmsi( ) );
                destination.writeInt32( getAisStaticDataReportPartBMessagePositionFixType( ) );
                destination.writeInt32( getAisStaticDataReportPartBMessageSpare( ) );
            }
            break;
            case Kind.AisUtcAndDateInquiryMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeInt32( getAisUtcAndDateInquiryMessageSpare1( ) );
                destination.writeNullableGuid( getAisUtcAndDateInquiryMessageDestinationMmsi( ) );
                destination.writeInt32( getAisUtcAndDateInquiryMessageSpare2( ) );
            }
            break;
            case Kind.AisUtcAndDateResponseMessage: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getAisDevice( ) );
                destination.writeDateTime( getReceivedTimestamp( ) );
                destination.writeInt64( getMessageSequenceNumber( ) );
                destination.writeInt32( getRepeat( ) );
                destination.writeNullableGuid( getMmsi( ) );
                destination.writeDateTime( getAisUtcAndDateResponseMessageDatetime( ) );
                destination.writeInt32( getAisUtcAndDateResponseMessagePositionAccuracy( ) );
                destination.writeDouble( getAisUtcAndDateResponseMessageLongitude( ) );
                destination.writeDouble( getAisUtcAndDateResponseMessageLatitude( ) );
                destination.writeInt32( getAisUtcAndDateResponseMessagePositionFixType( ) );
                destination.writeInt32( getAisUtcAndDateResponseMessageSpare( ) );
                destination.writeInt32( getAisUtcAndDateResponseMessageRaim( ) );
                destination.writeInt32( getAisUtcAndDateResponseMessageRadioStatus( ) );
            }
            break;
            default: {
                var exc = new SQLException( "Cannot perform serialization for kind=" + kind + "." );
                throw exc;
            }
        }
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public AisMessageObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.AidToNavigationReportMessage: {
                return new AidToNavigationReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAidToNavigationReportMessageNavigationalAidType( ), getAidToNavigationReportMessageName( ), getAidToNavigationReportMessagePositionAccuracy( ), getAidToNavigationReportMessageLongitude( ), getAidToNavigationReportMessageLatitude( ), getAidToNavigationReportMessageDimensionToBow( ), getAidToNavigationReportMessageDimensionToStern( ), getAidToNavigationReportMessageDimensionToPort( ), getAidToNavigationReportMessageDimensionToStarboard( ), getAidToNavigationReportMessagePositionFixType( ), getAidToNavigationReportMessageTimestamp( ), getAidToNavigationReportMessageOffPosition( ), getAidToNavigationReportMessageRegionalReserved( ), getAidToNavigationReportMessageRaim( ), getAidToNavigationReportMessageVirtualAid( ), getAidToNavigationReportMessageAssigned( ), getAidToNavigationReportMessageSpare( ), getAidToNavigationReportMessageNameExtension( ) );
            }
            case Kind.AisAddressedSafetyRelatedMessage: {
                return new AisAddressedSafetyRelatedMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisAddressedSafetyRelatedMessageSequenceNumber( ), getAisAddressedSafetyRelatedMessageDestinationMmsi( ), getAisAddressedSafetyRelatedMessageRetransmitFlag( ), getAisAddressedSafetyRelatedMessageSpare( ), getAisAddressedSafetyRelatedMessageText( ) );
            }
            case Kind.AisBaseStationReportMessage: {
                return new AisBaseStationReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisBaseStationReportMessageTimestamp( ), getAisBaseStationReportMessagePositionAccuracy( ), getAisBaseStationReportMessageLongitude( ), getAisBaseStationReportMessageLatitude( ), getAisBaseStationReportMessagePositionFixType( ), getAisBaseStationReportMessageSpare( ), getAisBaseStationReportMessageRaim( ), getAisBaseStationReportMessageRadioStatus( ) );
            }
            case Kind.AisBinaryAcknowledgeMessage: {
                return new AisBinaryAcknowledgeMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisBinaryAcknowledgeMessageSpare( ), getAisBinaryAcknowledgeMessageSequenceNumber1( ), getAisBinaryAcknowledgeMessageMmsi1( ), getAisBinaryAcknowledgeMessageSequenceNumber2( ), getAisBinaryAcknowledgeMessageMmsi2( ), getAisBinaryAcknowledgeMessageSequenceNumber3( ), getAisBinaryAcknowledgeMessageMmsi3( ), getAisBinaryAcknowledgeMessageSequenceNumber4( ), getAisBinaryAcknowledgeMessageMmsi4( ) );
            }
            case Kind.AisBinaryAddressedMessage: {
                return new AisBinaryAddressedMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisBinaryAddressedMessageSequenceNumber( ), getAisBinaryAddressedMessageDestinationMmsi( ), getAisBinaryAddressedMessageRetransmitFlag( ), getAisBinaryAddressedMessageSpare( ), getAisBinaryAddressedMessageDesignatedAreaCode( ), getAisBinaryAddressedMessageFunctionalId( ), getAisBinaryAddressedMessageData( ) );
            }
            case Kind.AisBinaryBroadcastMessage: {
                return new AisBinaryBroadcastMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisBinaryBroadcastMessageSpare( ), getAisBinaryBroadcastMessageDesignatedAreaCode( ), getAisBinaryBroadcastMessageFunctionalId( ), getAisBinaryBroadcastMessageData( ) );
            }
            case Kind.AisDataLinkManagementMessage: {
                return new AisDataLinkManagementMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisDataLinkManagementMessageSpare( ), getAisDataLinkManagementMessageOffset1( ), getAisDataLinkManagementMessageReservedSlots1( ), getAisDataLinkManagementMessageTimeout1( ), getAisDataLinkManagementMessageIncrement1( ), getAisDataLinkManagementMessageOffset2( ), getAisDataLinkManagementMessageReservedSlots2( ), getAisDataLinkManagementMessageTimeout2( ), getAisDataLinkManagementMessageIncrement2( ), getAisDataLinkManagementMessageOffset3( ), getAisDataLinkManagementMessageReservedSlots3( ), getAisDataLinkManagementMessageTimeout3( ), getAisDataLinkManagementMessageIncrement3( ), getAisDataLinkManagementMessageOffset4( ), getAisDataLinkManagementMessageReservedSlots4( ), getAisDataLinkManagementMessageTimeout4( ), getAisDataLinkManagementMessageIncrement4( ) );
            }
            case Kind.AisExtendedClassBCsPositionReportMessage: {
                return new AisExtendedClassBCsPositionReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisExtendedClassBCsPositionReportMessageReserved( ), getAisExtendedClassBCsPositionReportMessageSpeedOverGround( ), getAisExtendedClassBCsPositionReportMessagePositionAccuracy( ), getAisExtendedClassBCsPositionReportMessageLongitude( ), getAisExtendedClassBCsPositionReportMessageLatitude( ), getAisExtendedClassBCsPositionReportMessageCourseOverGround( ), getAisExtendedClassBCsPositionReportMessageTrueHeading( ), getAisExtendedClassBCsPositionReportMessageTimestamp( ), getAisExtendedClassBCsPositionReportMessageRegionalReserved( ), getAisExtendedClassBCsPositionReportMessageName( ), getAisExtendedClassBCsPositionReportMessageShipType( ), getAisExtendedClassBCsPositionReportMessageDimensionToBow( ), getAisExtendedClassBCsPositionReportMessageDimensionToStern( ), getAisExtendedClassBCsPositionReportMessageDimensionToPort( ), getAisExtendedClassBCsPositionReportMessageDimensionToStarboard( ), getAisExtendedClassBCsPositionReportMessagePositionFixType( ), getAisExtendedClassBCsPositionReportMessageRaim( ), getAisExtendedClassBCsPositionReportMessageDataTerminalReady( ), getAisExtendedClassBCsPositionReportMessageAssigned( ), getAisExtendedClassBCsPositionReportMessageSpare( ) );
            }
            case Kind.AisInterrogationMessage: {
                return new AisInterrogationMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisInterrogationMessageInterrogatedMmsi( ), getAisInterrogationMessageFirstMessageType( ), getAisInterrogationMessageFirstSlotOffset( ), getAisInterrogationMessageSecondMessageType( ), getAisInterrogationMessageSecondSlotOffset( ), getAisInterrogationMessageSecondStationInterrogationMmsi( ), getAisInterrogationMessageSecondStationFirstMessageType( ), getAisInterrogationMessageSecondStationFirstSlotOffset( ) );
            }
            case Kind.AisPositionReportClassAAssignedScheduleMessage: {
                return new AisPositionReportClassAAssignedScheduleMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisPositionReportClassAMessageBaseNavigationStatus( ), getAisPositionReportClassAMessageBaseRateOfTurn( ), getAisPositionReportClassAMessageBaseSpeedOverGround( ), getAisPositionReportClassAMessageBasePositionAccuracy( ), getAisPositionReportClassAMessageBaseLongitude( ), getAisPositionReportClassAMessageBaseLatitude( ), getAisPositionReportClassAMessageBaseCourseOverGround( ), getAisPositionReportClassAMessageBaseTrueHeading( ), getAisPositionReportClassAMessageBaseTimestamp( ), getAisPositionReportClassAMessageBaseManeuverIndicator( ), getAisPositionReportClassAMessageBaseSpare( ), getAisPositionReportClassAMessageBaseRaim( ), getAisPositionReportClassAMessageBaseRadioStatus( ) );
            }
            case Kind.AisPositionReportClassAMessage: {
                return new AisPositionReportClassAMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisPositionReportClassAMessageBaseNavigationStatus( ), getAisPositionReportClassAMessageBaseRateOfTurn( ), getAisPositionReportClassAMessageBaseSpeedOverGround( ), getAisPositionReportClassAMessageBasePositionAccuracy( ), getAisPositionReportClassAMessageBaseLongitude( ), getAisPositionReportClassAMessageBaseLatitude( ), getAisPositionReportClassAMessageBaseCourseOverGround( ), getAisPositionReportClassAMessageBaseTrueHeading( ), getAisPositionReportClassAMessageBaseTimestamp( ), getAisPositionReportClassAMessageBaseManeuverIndicator( ), getAisPositionReportClassAMessageBaseSpare( ), getAisPositionReportClassAMessageBaseRaim( ), getAisPositionReportClassAMessageBaseRadioStatus( ) );
            }
            case Kind.AisPositionReportClassAResponseToInterrogationMessage: {
                return new AisPositionReportClassAResponseToInterrogationMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisPositionReportClassAMessageBaseNavigationStatus( ), getAisPositionReportClassAMessageBaseRateOfTurn( ), getAisPositionReportClassAMessageBaseSpeedOverGround( ), getAisPositionReportClassAMessageBasePositionAccuracy( ), getAisPositionReportClassAMessageBaseLongitude( ), getAisPositionReportClassAMessageBaseLatitude( ), getAisPositionReportClassAMessageBaseCourseOverGround( ), getAisPositionReportClassAMessageBaseTrueHeading( ), getAisPositionReportClassAMessageBaseTimestamp( ), getAisPositionReportClassAMessageBaseManeuverIndicator( ), getAisPositionReportClassAMessageBaseSpare( ), getAisPositionReportClassAMessageBaseRaim( ), getAisPositionReportClassAMessageBaseRadioStatus( ) );
            }
            case Kind.AisPositionReportForLongRangeApplicationsMessage: {
                return new AisPositionReportForLongRangeApplicationsMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisPositionReportForLongRangeApplicationsMessagePositionAccuracy( ), getAisPositionReportForLongRangeApplicationsMessageRaim( ), getAisPositionReportForLongRangeApplicationsMessageNavigationStatus( ), getAisPositionReportForLongRangeApplicationsMessageLongitude( ), getAisPositionReportForLongRangeApplicationsMessageLatitude( ), getAisPositionReportForLongRangeApplicationsMessageSpeedOverGround( ), getAisPositionReportForLongRangeApplicationsMessageCourseOverGround( ), getAisPositionReportForLongRangeApplicationsMessageGnssPositionStatus( ), getAisPositionReportForLongRangeApplicationsMessageSpare( ) );
            }
            case Kind.AisSafetyRelatedAcknowledgmentMessage: {
                return new AisSafetyRelatedAcknowledgmentMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisSafetyRelatedAcknowledgmentMessageSpare( ), getAisSafetyRelatedAcknowledgmentMessageSequenceNumber1( ), getAisSafetyRelatedAcknowledgmentMessageMmsi1( ), getAisSafetyRelatedAcknowledgmentMessageSequenceNumber2( ), getAisSafetyRelatedAcknowledgmentMessageMmsi2( ), getAisSafetyRelatedAcknowledgmentMessageSequenceNumber3( ), getAisSafetyRelatedAcknowledgmentMessageMmsi3( ), getAisSafetyRelatedAcknowledgmentMessageSequenceNumber4( ), getAisSafetyRelatedAcknowledgmentMessageMmsi4( ) );
            }
            case Kind.AisStandardClassBCsPositionReportMessage: {
                return new AisStandardClassBCsPositionReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisStandardClassBCsPositionReportMessageReserved( ), getAisStandardClassBCsPositionReportMessageSpeedOverGround( ), getAisStandardClassBCsPositionReportMessagePositionAccuracy( ), getAisStandardClassBCsPositionReportMessageLongitude( ), getAisStandardClassBCsPositionReportMessageLatitude( ), getAisStandardClassBCsPositionReportMessageCourseOverGround( ), getAisStandardClassBCsPositionReportMessageTrueHeading( ), getAisStandardClassBCsPositionReportMessageTimestamp( ), getAisStandardClassBCsPositionReportMessageRegionalReserved( ), getAisStandardClassBCsPositionReportMessageIsCsUnit( ), getAisStandardClassBCsPositionReportMessageHasDisplay( ), getAisStandardClassBCsPositionReportMessageHasDscCapability( ), getAisStandardClassBCsPositionReportMessageBand( ), getAisStandardClassBCsPositionReportMessageCanAcceptMessage22( ), getAisStandardClassBCsPositionReportMessageAssigned( ), getAisStandardClassBCsPositionReportMessageRaim( ), getAisStandardClassBCsPositionReportMessageRadioStatus( ) );
            }
            case Kind.AisStandardSarAircraftPositionReportMessage: {
                return new AisStandardSarAircraftPositionReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisStandardSarAircraftPositionReportMessageAltitude( ), getAisStandardSarAircraftPositionReportMessageSpeedOverGround( ), getAisStandardSarAircraftPositionReportMessagePositionAccuracy( ), getAisStandardSarAircraftPositionReportMessageLongitude( ), getAisStandardSarAircraftPositionReportMessageLatitude( ), getAisStandardSarAircraftPositionReportMessageCourseOverGround( ), getAisStandardSarAircraftPositionReportMessageTimestamp( ), getAisStandardSarAircraftPositionReportMessageReserved( ), getAisStandardSarAircraftPositionReportMessageDataTerminalReady( ), getAisStandardSarAircraftPositionReportMessageSpare( ), getAisStandardSarAircraftPositionReportMessageAssigned( ), getAisStandardSarAircraftPositionReportMessageRaim( ), getAisStandardSarAircraftPositionReportMessageRadioStatus( ) );
            }
            case Kind.AisStaticAndVoyageRelatedDataMessage: {
                return new AisStaticAndVoyageRelatedDataMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisStaticAndVoyageRelatedDataMessageAisVersion( ), getAisStaticAndVoyageRelatedDataMessageImoNumber( ), getAisStaticAndVoyageRelatedDataMessageCallsign( ), getAisStaticAndVoyageRelatedDataMessageShipName( ), getAisStaticAndVoyageRelatedDataMessageShipType( ), getAisStaticAndVoyageRelatedDataMessageDimensionToBow( ), getAisStaticAndVoyageRelatedDataMessageDimensionToStern( ), getAisStaticAndVoyageRelatedDataMessageDimensionToPort( ), getAisStaticAndVoyageRelatedDataMessageDimensionToStarboard( ), getAisStaticAndVoyageRelatedDataMessagePositionFixType( ), getAisStaticAndVoyageRelatedDataMessageEstimatedTimeOfArrival( ), getAisStaticAndVoyageRelatedDataMessageDraught( ), getAisStaticAndVoyageRelatedDataMessageDestination( ), getAisStaticAndVoyageRelatedDataMessageDataTerminalReady( ), getAisStaticAndVoyageRelatedDataMessageSpare( ) );
            }
            case Kind.AisStaticDataReportMessage: {
                return new AisStaticDataReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisStaticDataReportMessagePartNumber( ) );
            }
            case Kind.AisStaticDataReportPartAMessage: {
                return new AisStaticDataReportPartAMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisStaticDataReportMessagePartNumber( ), getAisStaticDataReportPartAMessageShipName( ), getAisStaticDataReportPartAMessageSpare( ) );
            }
            case Kind.AisStaticDataReportPartBMessage: {
                return new AisStaticDataReportPartBMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisStaticDataReportMessagePartNumber( ), getAisStaticDataReportPartBMessageShipType( ), getAisStaticDataReportPartBMessageVendorId( ), getAisStaticDataReportPartBMessageUnitModelCode( ), getAisStaticDataReportPartBMessageSerialNumber( ), getAisStaticDataReportPartBMessageCallsign( ), getAisStaticDataReportPartBMessageDimensionToBow( ), getAisStaticDataReportPartBMessageDimensionToStern( ), getAisStaticDataReportPartBMessageDimensionToPort( ), getAisStaticDataReportPartBMessageDimensionToStarboard( ), getAisStaticDataReportPartBMessageMothershipMmsi( ), getAisStaticDataReportPartBMessagePositionFixType( ), getAisStaticDataReportPartBMessageSpare( ) );
            }
            case Kind.AisUtcAndDateInquiryMessage: {
                return new AisUtcAndDateInquiryMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisUtcAndDateInquiryMessageSpare1( ), getAisUtcAndDateInquiryMessageDestinationMmsi( ), getAisUtcAndDateInquiryMessageSpare2( ) );
            }
            case Kind.AisUtcAndDateResponseMessage: {
                return new AisUtcAndDateResponseMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisUtcAndDateResponseMessageDatetime( ), getAisUtcAndDateResponseMessagePositionAccuracy( ), getAisUtcAndDateResponseMessageLongitude( ), getAisUtcAndDateResponseMessageLatitude( ), getAisUtcAndDateResponseMessagePositionFixType( ), getAisUtcAndDateResponseMessageSpare( ), getAisUtcAndDateResponseMessageRaim( ), getAisUtcAndDateResponseMessageRadioStatus( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

