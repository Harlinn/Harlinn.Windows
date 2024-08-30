#pragma once
#ifndef DATABASE_COMPLEXDATABASEREADERS_H_
#define DATABASE_COMPLEXDATABASEREADERS_H_

#include "DatabaseReaders.h"


namespace Barrelman::Database
{
    using namespace Harlinn;
    using namespace Harlinn::ODBC;
    using namespace Harlinn::Common::Core;

    class ComplexAisMessageColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid aisDevice_;
        DateTime receivedTimestamp_;
        Int64 messageSequenceNumber_ = 0;
        Int32 repeat_ = 0;
        Guid mmsi_;
        DBEnum<Data::NavigationalAidType> atnrmNavigationalAidType_;
        FixedDBWideString<100> atnrmName_;
        DBEnum<Data::PositionAccuracy> atnrmPositionAccuracy_;
        DBDouble atnrmLongitude_;
        DBDouble atnrmLatitude_;
        DBInt32 atnrmDimensionToBow_;
        DBInt32 atnrmDimensionToStern_;
        DBInt32 atnrmDimensionToPort_;
        DBInt32 atnrmDimensionToStarboard_;
        DBEnum<Data::PositionFixType> atnrmPositionFixType_;
        DBInt32 atnrmTimestamp_;
        DBBoolean atnrmOffPosition_;
        DBInt32 atnrmRegionalReserved_;
        DBEnum<Data::Raim> atnrmRaim_;
        DBBoolean atnrmVirtualAid_;
        DBBoolean atnrmAssigned_;
        DBInt32 atnrmSpare_;
        FixedDBWideString<100> atnrmNameExtension_;
        DBInt32 aasrmSequenceNumber_;
        DBGuid aasrmDestinationMmsi_;
        DBBoolean aasrmRetransmitFlag_;
        DBInt32 aasrmSpare_;
        FixedDBWideString<100> aasrmText_;
        DBDateTime absrmTimestamp_;
        DBEnum<Data::PositionAccuracy> absrmPositionAccuracy_;
        DBDouble absrmLongitude_;
        DBDouble absrmLatitude_;
        DBEnum<Data::PositionFixType> absrmPositionFixType_;
        DBInt32 absrmSpare_;
        DBEnum<Data::Raim> absrmRaim_;
        DBInt32 absrmRadioStatus_;
        DBInt32 abacSpare_;
        DBInt32 abacSequenceNumber1_;
        DBGuid abacMmsi1_;
        DBInt32 abacSequenceNumber2_;
        DBGuid abacMmsi2_;
        DBInt32 abacSequenceNumber3_;
        DBGuid abacMmsi3_;
        DBInt32 abacSequenceNumber4_;
        DBGuid abacMmsi4_;
        DBInt32 abamSequenceNumber_;
        DBGuid abamDestinationMmsi_;
        DBBoolean abamRetransmitFlag_;
        DBInt32 abamSpare_;
        DBInt32 abamDesignatedAreaCode_;
        DBInt32 abamFunctionalId_;
        DBWideString abamData_;
        DBInt32 abbmSpare_;
        DBInt32 abbmDesignatedAreaCode_;
        DBInt32 abbmFunctionalId_;
        DBWideString abbmData_;
        DBInt32 adlmmSpare_;
        DBInt32 adlmmOffset1_;
        DBInt32 adlmmReservedSlots1_;
        DBInt32 adlmmTimeout1_;
        DBInt32 adlmmIncrement1_;
        DBInt32 adlmmOffset2_;
        DBInt32 adlmmReservedSlots2_;
        DBInt32 adlmmTimeout2_;
        DBInt32 adlmmIncrement2_;
        DBInt32 adlmmOffset3_;
        DBInt32 adlmmReservedSlots3_;
        DBInt32 adlmmTimeout3_;
        DBInt32 adlmmIncrement3_;
        DBInt32 adlmmOffset4_;
        DBInt32 adlmmReservedSlots4_;
        DBInt32 adlmmTimeout4_;
        DBInt32 adlmmIncrement4_;
        DBInt32 aecbprmReserved_;
        DBDouble aecbprmSpeedOverGround_;
        DBEnum<Data::PositionAccuracy> aecbprmPositionAccuracy_;
        DBDouble aecbprmLongitude_;
        DBDouble aecbprmLatitude_;
        DBDouble aecbprmCourseOverGround_;
        DBInt32 aecbprmTrueHeading_;
        DBInt32 aecbprmTimestamp_;
        DBInt32 aecbprmRegionalReserved_;
        DBGuid aecbprmName_;
        DBEnum<Data::ShipType> aecbprmShipType_;
        DBInt32 aecbprmDimensionToBow_;
        DBInt32 aecbprmDimensionToStern_;
        DBInt32 aecbprmDimensionToPort_;
        DBInt32 aecbprmDimensionToStarboard_;
        DBEnum<Data::PositionFixType> aecbprmPositionFixType_;
        DBEnum<Data::Raim> aecbprmRaim_;
        DBBoolean aecbprmDataTerminalReady_;
        DBBoolean aecbprmAssigned_;
        DBInt32 aecbprmSpare_;
        DBGuid aimInterrogatedMmsi_;
        DBEnum<Data::AisMessageType> aimFirstMessageType_;
        DBInt32 aimFirstSlotOffset_;
        DBEnum<Data::AisMessageType> aimSecondMessageType_;
        DBInt32 aimSecondSlotOffset_;
        DBGuid aimSecondStationInterrogationMmsi_;
        DBEnum<Data::AisMessageType> aimSecondStationFirstMessageType_;
        DBInt32 aimSecondStationFirstSlotOffset_;
        DBEnum<Data::NavigationStatus> aprcabNavigationStatus_;
        DBInt32 aprcabRateOfTurn_;
        DBDouble aprcabSpeedOverGround_;
        DBEnum<Data::PositionAccuracy> aprcabPositionAccuracy_;
        DBDouble aprcabLongitude_;
        DBDouble aprcabLatitude_;
        DBDouble aprcabCourseOverGround_;
        DBInt32 aprcabTrueHeading_;
        DBInt32 aprcabTimestamp_;
        DBEnum<Data::ManeuverIndicator> aprcabManeuverIndicator_;
        DBInt32 aprcabSpare_;
        DBEnum<Data::Raim> aprcabRaim_;
        DBInt32 aprcabRadioStatus_;
        DBEnum<Data::PositionAccuracy> aprflramPositionAccuracy_;
        DBEnum<Data::Raim> aprflramRaim_;
        DBEnum<Data::NavigationStatus> aprflramNavigationStatus_;
        DBDouble aprflramLongitude_;
        DBDouble aprflramLatitude_;
        DBDouble aprflramSpeedOverGround_;
        DBDouble aprflramCourseOverGround_;
        DBEnum<Data::GnssPositionStatus> aprflramGnssPositionStatus_;
        DBInt32 aprflramSpare_;
        DBInt32 asramSpare_;
        DBInt32 asramSequenceNumber1_;
        DBGuid asramMmsi1_;
        DBInt32 asramSequenceNumber2_;
        DBGuid asramMmsi2_;
        DBInt32 asramSequenceNumber3_;
        DBGuid asramMmsi3_;
        DBInt32 asramSequenceNumber4_;
        DBGuid asramMmsi4_;
        DBInt32 ascbprmReserved_;
        DBDouble ascbprmSpeedOverGround_;
        DBEnum<Data::PositionAccuracy> ascbprmPositionAccuracy_;
        DBDouble ascbprmLongitude_;
        DBDouble ascbprmLatitude_;
        DBDouble ascbprmCourseOverGround_;
        DBInt32 ascbprmTrueHeading_;
        DBInt32 ascbprmTimestamp_;
        DBInt32 ascbprmRegionalReserved_;
        DBBoolean ascbprmIsCsUnit_;
        DBBoolean ascbprmHasDisplay_;
        DBBoolean ascbprmHasDscCapability_;
        DBBoolean ascbprmBand_;
        DBBoolean ascbprmCanAcceptMessage22_;
        DBBoolean ascbprmAssigned_;
        DBEnum<Data::Raim> ascbprmRaim_;
        DBInt32 ascbprmRadioStatus_;
        DBInt32 assaprmAltitude_;
        DBInt32 assaprmSpeedOverGround_;
        DBEnum<Data::PositionAccuracy> assaprmPositionAccuracy_;
        DBDouble assaprmLongitude_;
        DBDouble assaprmLatitude_;
        DBDouble assaprmCourseOverGround_;
        DBInt32 assaprmTimestamp_;
        DBInt32 assaprmReserved_;
        DBBoolean assaprmDataTerminalReady_;
        DBInt32 assaprmSpare_;
        DBBoolean assaprmAssigned_;
        DBEnum<Data::Raim> assaprmRaim_;
        DBInt32 assaprmRadioStatus_;
        DBInt32 asavrdmAisVersion_;
        DBGuid asavrdmImoNumber_;
        DBGuid asavrdmCallsign_;
        DBGuid asavrdmShipName_;
        DBEnum<Data::ShipType> asavrdmShipType_;
        DBInt32 asavrdmDimensionToBow_;
        DBInt32 asavrdmDimensionToStern_;
        DBInt32 asavrdmDimensionToPort_;
        DBInt32 asavrdmDimensionToStarboard_;
        DBEnum<Data::PositionFixType> asavrdmPositionFixType_;
        DBDateTime asavrdmEstimatedTimeOfArrival_;
        DBDouble asavrdmDraught_;
        FixedDBWideString<100> asavrdmDestination_;
        DBBoolean asavrdmDataTerminalReady_;
        DBInt32 asavrdmSpare_;
        DBInt32 asdrmPartNumber_;
        DBGuid asdrpaShipName_;
        DBInt32 asdrpaSpare_;
        DBEnum<Data::ShipType> asdrpbShipType_;
        FixedDBWideString<100> asdrpbVendorId_;
        DBInt32 asdrpbUnitModelCode_;
        DBInt32 asdrpbSerialNumber_;
        DBGuid asdrpbCallsign_;
        DBInt32 asdrpbDimensionToBow_;
        DBInt32 asdrpbDimensionToStern_;
        DBInt32 asdrpbDimensionToPort_;
        DBInt32 asdrpbDimensionToStarboard_;
        DBGuid asdrpbMothershipMmsi_;
        DBEnum<Data::PositionFixType> asdrpbPositionFixType_;
        DBInt32 asdrpbSpare_;
        DBInt32 auadimSpare1_;
        DBInt32 auadimDestinationMmsi_;
        DBInt32 auadimSpare2_;
        DBDateTime auadrmDatetime_;
        DBEnum<Data::PositionAccuracy> auadrmPositionAccuracy_;
        DBDouble auadrmLongitude_;
        DBDouble auadrmLatitude_;
        DBEnum<Data::PositionFixType> auadrmPositionFixType_;
        DBInt32 auadrmSpare_;
        DBEnum<Data::Raim> auadrmRaim_;
        DBInt32 auadrmRadioStatus_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT AM_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT AM_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT AM_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT AM_AISDEVICE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT AM_RECEIVEDTIMESTAMP_FIELD_ID = 5;
        static constexpr SQLUSMALLINT AM_MESSAGESEQUENCENUMBER_FIELD_ID = 6;
        static constexpr SQLUSMALLINT AM_REPEAT_FIELD_ID = 7;
        static constexpr SQLUSMALLINT AM_MMSI_FIELD_ID = 8;
        static constexpr SQLUSMALLINT ATNRM_NAVIGATIONALAIDTYPE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT ATNRM_NAME_FIELD_ID = 10;
        static constexpr SQLUSMALLINT ATNRM_POSITIONACCURACY_FIELD_ID = 11;
        static constexpr SQLUSMALLINT ATNRM_LONGITUDE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT ATNRM_LATITUDE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT ATNRM_DIMENSIONTOBOW_FIELD_ID = 14;
        static constexpr SQLUSMALLINT ATNRM_DIMENSIONTOSTERN_FIELD_ID = 15;
        static constexpr SQLUSMALLINT ATNRM_DIMENSIONTOPORT_FIELD_ID = 16;
        static constexpr SQLUSMALLINT ATNRM_DIMENSIONTOSTARBOARD_FIELD_ID = 17;
        static constexpr SQLUSMALLINT ATNRM_POSITIONFIXTYPE_FIELD_ID = 18;
        static constexpr SQLUSMALLINT ATNRM_TIMESTAMP_FIELD_ID = 19;
        static constexpr SQLUSMALLINT ATNRM_OFFPOSITION_FIELD_ID = 20;
        static constexpr SQLUSMALLINT ATNRM_REGIONALRESERVED_FIELD_ID = 21;
        static constexpr SQLUSMALLINT ATNRM_RAIM_FIELD_ID = 22;
        static constexpr SQLUSMALLINT ATNRM_VIRTUALAID_FIELD_ID = 23;
        static constexpr SQLUSMALLINT ATNRM_ASSIGNED_FIELD_ID = 24;
        static constexpr SQLUSMALLINT ATNRM_SPARE_FIELD_ID = 25;
        static constexpr SQLUSMALLINT ATNRM_NAMEEXTENSION_FIELD_ID = 26;
        static constexpr SQLUSMALLINT AASRM_SEQUENCENUMBER_FIELD_ID = 27;
        static constexpr SQLUSMALLINT AASRM_DESTINATIONMMSI_FIELD_ID = 28;
        static constexpr SQLUSMALLINT AASRM_RETRANSMITFLAG_FIELD_ID = 29;
        static constexpr SQLUSMALLINT AASRM_SPARE_FIELD_ID = 30;
        static constexpr SQLUSMALLINT AASRM_TEXT_FIELD_ID = 31;
        static constexpr SQLUSMALLINT ABSRM_TIMESTAMP_FIELD_ID = 32;
        static constexpr SQLUSMALLINT ABSRM_POSITIONACCURACY_FIELD_ID = 33;
        static constexpr SQLUSMALLINT ABSRM_LONGITUDE_FIELD_ID = 34;
        static constexpr SQLUSMALLINT ABSRM_LATITUDE_FIELD_ID = 35;
        static constexpr SQLUSMALLINT ABSRM_POSITIONFIXTYPE_FIELD_ID = 36;
        static constexpr SQLUSMALLINT ABSRM_SPARE_FIELD_ID = 37;
        static constexpr SQLUSMALLINT ABSRM_RAIM_FIELD_ID = 38;
        static constexpr SQLUSMALLINT ABSRM_RADIOSTATUS_FIELD_ID = 39;
        static constexpr SQLUSMALLINT ABAC_SPARE_FIELD_ID = 40;
        static constexpr SQLUSMALLINT ABAC_SEQUENCENUMBER1_FIELD_ID = 41;
        static constexpr SQLUSMALLINT ABAC_MMSI1_FIELD_ID = 42;
        static constexpr SQLUSMALLINT ABAC_SEQUENCENUMBER2_FIELD_ID = 43;
        static constexpr SQLUSMALLINT ABAC_MMSI2_FIELD_ID = 44;
        static constexpr SQLUSMALLINT ABAC_SEQUENCENUMBER3_FIELD_ID = 45;
        static constexpr SQLUSMALLINT ABAC_MMSI3_FIELD_ID = 46;
        static constexpr SQLUSMALLINT ABAC_SEQUENCENUMBER4_FIELD_ID = 47;
        static constexpr SQLUSMALLINT ABAC_MMSI4_FIELD_ID = 48;
        static constexpr SQLUSMALLINT ABAM_SEQUENCENUMBER_FIELD_ID = 49;
        static constexpr SQLUSMALLINT ABAM_DESTINATIONMMSI_FIELD_ID = 50;
        static constexpr SQLUSMALLINT ABAM_RETRANSMITFLAG_FIELD_ID = 51;
        static constexpr SQLUSMALLINT ABAM_SPARE_FIELD_ID = 52;
        static constexpr SQLUSMALLINT ABAM_DESIGNATEDAREACODE_FIELD_ID = 53;
        static constexpr SQLUSMALLINT ABAM_FUNCTIONALID_FIELD_ID = 54;
        static constexpr SQLUSMALLINT ABBM_SPARE_FIELD_ID = 55;
        static constexpr SQLUSMALLINT ABBM_DESIGNATEDAREACODE_FIELD_ID = 56;
        static constexpr SQLUSMALLINT ABBM_FUNCTIONALID_FIELD_ID = 57;
        static constexpr SQLUSMALLINT ADLMM_SPARE_FIELD_ID = 58;
        static constexpr SQLUSMALLINT ADLMM_OFFSET1_FIELD_ID = 59;
        static constexpr SQLUSMALLINT ADLMM_RESERVEDSLOTS1_FIELD_ID = 60;
        static constexpr SQLUSMALLINT ADLMM_TIMEOUT1_FIELD_ID = 61;
        static constexpr SQLUSMALLINT ADLMM_INCREMENT1_FIELD_ID = 62;
        static constexpr SQLUSMALLINT ADLMM_OFFSET2_FIELD_ID = 63;
        static constexpr SQLUSMALLINT ADLMM_RESERVEDSLOTS2_FIELD_ID = 64;
        static constexpr SQLUSMALLINT ADLMM_TIMEOUT2_FIELD_ID = 65;
        static constexpr SQLUSMALLINT ADLMM_INCREMENT2_FIELD_ID = 66;
        static constexpr SQLUSMALLINT ADLMM_OFFSET3_FIELD_ID = 67;
        static constexpr SQLUSMALLINT ADLMM_RESERVEDSLOTS3_FIELD_ID = 68;
        static constexpr SQLUSMALLINT ADLMM_TIMEOUT3_FIELD_ID = 69;
        static constexpr SQLUSMALLINT ADLMM_INCREMENT3_FIELD_ID = 70;
        static constexpr SQLUSMALLINT ADLMM_OFFSET4_FIELD_ID = 71;
        static constexpr SQLUSMALLINT ADLMM_RESERVEDSLOTS4_FIELD_ID = 72;
        static constexpr SQLUSMALLINT ADLMM_TIMEOUT4_FIELD_ID = 73;
        static constexpr SQLUSMALLINT ADLMM_INCREMENT4_FIELD_ID = 74;
        static constexpr SQLUSMALLINT AECBPRM_RESERVED_FIELD_ID = 75;
        static constexpr SQLUSMALLINT AECBPRM_SPEEDOVERGROUND_FIELD_ID = 76;
        static constexpr SQLUSMALLINT AECBPRM_POSITIONACCURACY_FIELD_ID = 77;
        static constexpr SQLUSMALLINT AECBPRM_LONGITUDE_FIELD_ID = 78;
        static constexpr SQLUSMALLINT AECBPRM_LATITUDE_FIELD_ID = 79;
        static constexpr SQLUSMALLINT AECBPRM_COURSEOVERGROUND_FIELD_ID = 80;
        static constexpr SQLUSMALLINT AECBPRM_TRUEHEADING_FIELD_ID = 81;
        static constexpr SQLUSMALLINT AECBPRM_TIMESTAMP_FIELD_ID = 82;
        static constexpr SQLUSMALLINT AECBPRM_REGIONALRESERVED_FIELD_ID = 83;
        static constexpr SQLUSMALLINT AECBPRM_NAME_FIELD_ID = 84;
        static constexpr SQLUSMALLINT AECBPRM_SHIPTYPE_FIELD_ID = 85;
        static constexpr SQLUSMALLINT AECBPRM_DIMENSIONTOBOW_FIELD_ID = 86;
        static constexpr SQLUSMALLINT AECBPRM_DIMENSIONTOSTERN_FIELD_ID = 87;
        static constexpr SQLUSMALLINT AECBPRM_DIMENSIONTOPORT_FIELD_ID = 88;
        static constexpr SQLUSMALLINT AECBPRM_DIMENSIONTOSTARBOARD_FIELD_ID = 89;
        static constexpr SQLUSMALLINT AECBPRM_POSITIONFIXTYPE_FIELD_ID = 90;
        static constexpr SQLUSMALLINT AECBPRM_RAIM_FIELD_ID = 91;
        static constexpr SQLUSMALLINT AECBPRM_DATATERMINALREADY_FIELD_ID = 92;
        static constexpr SQLUSMALLINT AECBPRM_ASSIGNED_FIELD_ID = 93;
        static constexpr SQLUSMALLINT AECBPRM_SPARE_FIELD_ID = 94;
        static constexpr SQLUSMALLINT AIM_INTERROGATEDMMSI_FIELD_ID = 95;
        static constexpr SQLUSMALLINT AIM_FIRSTMESSAGETYPE_FIELD_ID = 96;
        static constexpr SQLUSMALLINT AIM_FIRSTSLOTOFFSET_FIELD_ID = 97;
        static constexpr SQLUSMALLINT AIM_SECONDMESSAGETYPE_FIELD_ID = 98;
        static constexpr SQLUSMALLINT AIM_SECONDSLOTOFFSET_FIELD_ID = 99;
        static constexpr SQLUSMALLINT AIM_SECONDSTATIONINTERROGATIONMMSI_FIELD_ID = 100;
        static constexpr SQLUSMALLINT AIM_SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID = 101;
        static constexpr SQLUSMALLINT AIM_SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID = 102;
        static constexpr SQLUSMALLINT APRCAB_NAVIGATIONSTATUS_FIELD_ID = 103;
        static constexpr SQLUSMALLINT APRCAB_RATEOFTURN_FIELD_ID = 104;
        static constexpr SQLUSMALLINT APRCAB_SPEEDOVERGROUND_FIELD_ID = 105;
        static constexpr SQLUSMALLINT APRCAB_POSITIONACCURACY_FIELD_ID = 106;
        static constexpr SQLUSMALLINT APRCAB_LONGITUDE_FIELD_ID = 107;
        static constexpr SQLUSMALLINT APRCAB_LATITUDE_FIELD_ID = 108;
        static constexpr SQLUSMALLINT APRCAB_COURSEOVERGROUND_FIELD_ID = 109;
        static constexpr SQLUSMALLINT APRCAB_TRUEHEADING_FIELD_ID = 110;
        static constexpr SQLUSMALLINT APRCAB_TIMESTAMP_FIELD_ID = 111;
        static constexpr SQLUSMALLINT APRCAB_MANEUVERINDICATOR_FIELD_ID = 112;
        static constexpr SQLUSMALLINT APRCAB_SPARE_FIELD_ID = 113;
        static constexpr SQLUSMALLINT APRCAB_RAIM_FIELD_ID = 114;
        static constexpr SQLUSMALLINT APRCAB_RADIOSTATUS_FIELD_ID = 115;
        static constexpr SQLUSMALLINT APRFLRAM_POSITIONACCURACY_FIELD_ID = 116;
        static constexpr SQLUSMALLINT APRFLRAM_RAIM_FIELD_ID = 117;
        static constexpr SQLUSMALLINT APRFLRAM_NAVIGATIONSTATUS_FIELD_ID = 118;
        static constexpr SQLUSMALLINT APRFLRAM_LONGITUDE_FIELD_ID = 119;
        static constexpr SQLUSMALLINT APRFLRAM_LATITUDE_FIELD_ID = 120;
        static constexpr SQLUSMALLINT APRFLRAM_SPEEDOVERGROUND_FIELD_ID = 121;
        static constexpr SQLUSMALLINT APRFLRAM_COURSEOVERGROUND_FIELD_ID = 122;
        static constexpr SQLUSMALLINT APRFLRAM_GNSSPOSITIONSTATUS_FIELD_ID = 123;
        static constexpr SQLUSMALLINT APRFLRAM_SPARE_FIELD_ID = 124;
        static constexpr SQLUSMALLINT ASRAM_SPARE_FIELD_ID = 125;
        static constexpr SQLUSMALLINT ASRAM_SEQUENCENUMBER1_FIELD_ID = 126;
        static constexpr SQLUSMALLINT ASRAM_MMSI1_FIELD_ID = 127;
        static constexpr SQLUSMALLINT ASRAM_SEQUENCENUMBER2_FIELD_ID = 128;
        static constexpr SQLUSMALLINT ASRAM_MMSI2_FIELD_ID = 129;
        static constexpr SQLUSMALLINT ASRAM_SEQUENCENUMBER3_FIELD_ID = 130;
        static constexpr SQLUSMALLINT ASRAM_MMSI3_FIELD_ID = 131;
        static constexpr SQLUSMALLINT ASRAM_SEQUENCENUMBER4_FIELD_ID = 132;
        static constexpr SQLUSMALLINT ASRAM_MMSI4_FIELD_ID = 133;
        static constexpr SQLUSMALLINT ASCBPRM_RESERVED_FIELD_ID = 134;
        static constexpr SQLUSMALLINT ASCBPRM_SPEEDOVERGROUND_FIELD_ID = 135;
        static constexpr SQLUSMALLINT ASCBPRM_POSITIONACCURACY_FIELD_ID = 136;
        static constexpr SQLUSMALLINT ASCBPRM_LONGITUDE_FIELD_ID = 137;
        static constexpr SQLUSMALLINT ASCBPRM_LATITUDE_FIELD_ID = 138;
        static constexpr SQLUSMALLINT ASCBPRM_COURSEOVERGROUND_FIELD_ID = 139;
        static constexpr SQLUSMALLINT ASCBPRM_TRUEHEADING_FIELD_ID = 140;
        static constexpr SQLUSMALLINT ASCBPRM_TIMESTAMP_FIELD_ID = 141;
        static constexpr SQLUSMALLINT ASCBPRM_REGIONALRESERVED_FIELD_ID = 142;
        static constexpr SQLUSMALLINT ASCBPRM_ISCSUNIT_FIELD_ID = 143;
        static constexpr SQLUSMALLINT ASCBPRM_HASDISPLAY_FIELD_ID = 144;
        static constexpr SQLUSMALLINT ASCBPRM_HASDSCCAPABILITY_FIELD_ID = 145;
        static constexpr SQLUSMALLINT ASCBPRM_BAND_FIELD_ID = 146;
        static constexpr SQLUSMALLINT ASCBPRM_CANACCEPTMESSAGE22_FIELD_ID = 147;
        static constexpr SQLUSMALLINT ASCBPRM_ASSIGNED_FIELD_ID = 148;
        static constexpr SQLUSMALLINT ASCBPRM_RAIM_FIELD_ID = 149;
        static constexpr SQLUSMALLINT ASCBPRM_RADIOSTATUS_FIELD_ID = 150;
        static constexpr SQLUSMALLINT ASSAPRM_ALTITUDE_FIELD_ID = 151;
        static constexpr SQLUSMALLINT ASSAPRM_SPEEDOVERGROUND_FIELD_ID = 152;
        static constexpr SQLUSMALLINT ASSAPRM_POSITIONACCURACY_FIELD_ID = 153;
        static constexpr SQLUSMALLINT ASSAPRM_LONGITUDE_FIELD_ID = 154;
        static constexpr SQLUSMALLINT ASSAPRM_LATITUDE_FIELD_ID = 155;
        static constexpr SQLUSMALLINT ASSAPRM_COURSEOVERGROUND_FIELD_ID = 156;
        static constexpr SQLUSMALLINT ASSAPRM_TIMESTAMP_FIELD_ID = 157;
        static constexpr SQLUSMALLINT ASSAPRM_RESERVED_FIELD_ID = 158;
        static constexpr SQLUSMALLINT ASSAPRM_DATATERMINALREADY_FIELD_ID = 159;
        static constexpr SQLUSMALLINT ASSAPRM_SPARE_FIELD_ID = 160;
        static constexpr SQLUSMALLINT ASSAPRM_ASSIGNED_FIELD_ID = 161;
        static constexpr SQLUSMALLINT ASSAPRM_RAIM_FIELD_ID = 162;
        static constexpr SQLUSMALLINT ASSAPRM_RADIOSTATUS_FIELD_ID = 163;
        static constexpr SQLUSMALLINT ASAVRDM_AISVERSION_FIELD_ID = 164;
        static constexpr SQLUSMALLINT ASAVRDM_IMONUMBER_FIELD_ID = 165;
        static constexpr SQLUSMALLINT ASAVRDM_CALLSIGN_FIELD_ID = 166;
        static constexpr SQLUSMALLINT ASAVRDM_SHIPNAME_FIELD_ID = 167;
        static constexpr SQLUSMALLINT ASAVRDM_SHIPTYPE_FIELD_ID = 168;
        static constexpr SQLUSMALLINT ASAVRDM_DIMENSIONTOBOW_FIELD_ID = 169;
        static constexpr SQLUSMALLINT ASAVRDM_DIMENSIONTOSTERN_FIELD_ID = 170;
        static constexpr SQLUSMALLINT ASAVRDM_DIMENSIONTOPORT_FIELD_ID = 171;
        static constexpr SQLUSMALLINT ASAVRDM_DIMENSIONTOSTARBOARD_FIELD_ID = 172;
        static constexpr SQLUSMALLINT ASAVRDM_POSITIONFIXTYPE_FIELD_ID = 173;
        static constexpr SQLUSMALLINT ASAVRDM_ESTIMATEDTIMEOFARRIVAL_FIELD_ID = 174;
        static constexpr SQLUSMALLINT ASAVRDM_DRAUGHT_FIELD_ID = 175;
        static constexpr SQLUSMALLINT ASAVRDM_DESTINATION_FIELD_ID = 176;
        static constexpr SQLUSMALLINT ASAVRDM_DATATERMINALREADY_FIELD_ID = 177;
        static constexpr SQLUSMALLINT ASAVRDM_SPARE_FIELD_ID = 178;
        static constexpr SQLUSMALLINT ASDRM_PARTNUMBER_FIELD_ID = 179;
        static constexpr SQLUSMALLINT ASDRPA_SHIPNAME_FIELD_ID = 180;
        static constexpr SQLUSMALLINT ASDRPA_SPARE_FIELD_ID = 181;
        static constexpr SQLUSMALLINT ASDRPB_SHIPTYPE_FIELD_ID = 182;
        static constexpr SQLUSMALLINT ASDRPB_VENDORID_FIELD_ID = 183;
        static constexpr SQLUSMALLINT ASDRPB_UNITMODELCODE_FIELD_ID = 184;
        static constexpr SQLUSMALLINT ASDRPB_SERIALNUMBER_FIELD_ID = 185;
        static constexpr SQLUSMALLINT ASDRPB_CALLSIGN_FIELD_ID = 186;
        static constexpr SQLUSMALLINT ASDRPB_DIMENSIONTOBOW_FIELD_ID = 187;
        static constexpr SQLUSMALLINT ASDRPB_DIMENSIONTOSTERN_FIELD_ID = 188;
        static constexpr SQLUSMALLINT ASDRPB_DIMENSIONTOPORT_FIELD_ID = 189;
        static constexpr SQLUSMALLINT ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID = 190;
        static constexpr SQLUSMALLINT ASDRPB_MOTHERSHIPMMSI_FIELD_ID = 191;
        static constexpr SQLUSMALLINT ASDRPB_POSITIONFIXTYPE_FIELD_ID = 192;
        static constexpr SQLUSMALLINT ASDRPB_SPARE_FIELD_ID = 193;
        static constexpr SQLUSMALLINT AUADIM_SPARE1_FIELD_ID = 194;
        static constexpr SQLUSMALLINT AUADIM_DESTINATIONMMSI_FIELD_ID = 195;
        static constexpr SQLUSMALLINT AUADIM_SPARE2_FIELD_ID = 196;
        static constexpr SQLUSMALLINT AUADRM_DATETIME_FIELD_ID = 197;
        static constexpr SQLUSMALLINT AUADRM_POSITIONACCURACY_FIELD_ID = 198;
        static constexpr SQLUSMALLINT AUADRM_LONGITUDE_FIELD_ID = 199;
        static constexpr SQLUSMALLINT AUADRM_LATITUDE_FIELD_ID = 200;
        static constexpr SQLUSMALLINT AUADRM_POSITIONFIXTYPE_FIELD_ID = 201;
        static constexpr SQLUSMALLINT AUADRM_SPARE_FIELD_ID = 202;
        static constexpr SQLUSMALLINT AUADRM_RAIM_FIELD_ID = 203;
        static constexpr SQLUSMALLINT AUADRM_RADIOSTATUS_FIELD_ID = 204;
        static constexpr SQLUSMALLINT ABAM_DATA_FIELD_ID = 205;
        static constexpr SQLUSMALLINT ABBM_DATA_FIELD_ID = 206;

        ComplexAisMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& AisDevice( ) const
        {
            return aisDevice_;
        }
        const DateTime& ReceivedTimestamp( ) const
        {
            return receivedTimestamp_;
        }
        Int64 MessageSequenceNumber( ) const
        {
            return messageSequenceNumber_;
        }
        Int32 Repeat( ) const
        {
            return repeat_;
        }
        const Guid& Mmsi( ) const
        {
            return mmsi_;
        }
        DBEnum<Data::NavigationalAidType> AidToNavigationReportMessageNavigationalAidType( ) const
        {
            return atnrmNavigationalAidType_;
        }
        const FixedDBWideString<100>& AidToNavigationReportMessageName( ) const
        {
            return atnrmName_;
        }
        DBEnum<Data::PositionAccuracy> AidToNavigationReportMessagePositionAccuracy( ) const
        {
            return atnrmPositionAccuracy_;
        }
        DBDouble AidToNavigationReportMessageLongitude( ) const
        {
            return atnrmLongitude_;
        }
        DBDouble AidToNavigationReportMessageLatitude( ) const
        {
            return atnrmLatitude_;
        }
        DBInt32 AidToNavigationReportMessageDimensionToBow( ) const
        {
            return atnrmDimensionToBow_;
        }
        DBInt32 AidToNavigationReportMessageDimensionToStern( ) const
        {
            return atnrmDimensionToStern_;
        }
        DBInt32 AidToNavigationReportMessageDimensionToPort( ) const
        {
            return atnrmDimensionToPort_;
        }
        DBInt32 AidToNavigationReportMessageDimensionToStarboard( ) const
        {
            return atnrmDimensionToStarboard_;
        }
        DBEnum<Data::PositionFixType> AidToNavigationReportMessagePositionFixType( ) const
        {
            return atnrmPositionFixType_;
        }
        DBInt32 AidToNavigationReportMessageTimestamp( ) const
        {
            return atnrmTimestamp_;
        }
        DBBoolean AidToNavigationReportMessageOffPosition( ) const
        {
            return atnrmOffPosition_;
        }
        DBInt32 AidToNavigationReportMessageRegionalReserved( ) const
        {
            return atnrmRegionalReserved_;
        }
        DBEnum<Data::Raim> AidToNavigationReportMessageRaim( ) const
        {
            return atnrmRaim_;
        }
        DBBoolean AidToNavigationReportMessageVirtualAid( ) const
        {
            return atnrmVirtualAid_;
        }
        DBBoolean AidToNavigationReportMessageAssigned( ) const
        {
            return atnrmAssigned_;
        }
        DBInt32 AidToNavigationReportMessageSpare( ) const
        {
            return atnrmSpare_;
        }
        const FixedDBWideString<100>& AidToNavigationReportMessageNameExtension( ) const
        {
            return atnrmNameExtension_;
        }
        DBInt32 AisAddressedSafetyRelatedMessageSequenceNumber( ) const
        {
            return aasrmSequenceNumber_;
        }
        const DBGuid& AisAddressedSafetyRelatedMessageDestinationMmsi( ) const
        {
            return aasrmDestinationMmsi_;
        }
        DBBoolean AisAddressedSafetyRelatedMessageRetransmitFlag( ) const
        {
            return aasrmRetransmitFlag_;
        }
        DBInt32 AisAddressedSafetyRelatedMessageSpare( ) const
        {
            return aasrmSpare_;
        }
        const FixedDBWideString<100>& AisAddressedSafetyRelatedMessageText( ) const
        {
            return aasrmText_;
        }
        const DBDateTime& AisBaseStationReportMessageTimestamp( ) const
        {
            return absrmTimestamp_;
        }
        DBEnum<Data::PositionAccuracy> AisBaseStationReportMessagePositionAccuracy( ) const
        {
            return absrmPositionAccuracy_;
        }
        DBDouble AisBaseStationReportMessageLongitude( ) const
        {
            return absrmLongitude_;
        }
        DBDouble AisBaseStationReportMessageLatitude( ) const
        {
            return absrmLatitude_;
        }
        DBEnum<Data::PositionFixType> AisBaseStationReportMessagePositionFixType( ) const
        {
            return absrmPositionFixType_;
        }
        DBInt32 AisBaseStationReportMessageSpare( ) const
        {
            return absrmSpare_;
        }
        DBEnum<Data::Raim> AisBaseStationReportMessageRaim( ) const
        {
            return absrmRaim_;
        }
        DBInt32 AisBaseStationReportMessageRadioStatus( ) const
        {
            return absrmRadioStatus_;
        }
        DBInt32 AisBinaryAcknowledgeMessageSpare( ) const
        {
            return abacSpare_;
        }
        DBInt32 AisBinaryAcknowledgeMessageSequenceNumber1( ) const
        {
            return abacSequenceNumber1_;
        }
        const DBGuid& AisBinaryAcknowledgeMessageMmsi1( ) const
        {
            return abacMmsi1_;
        }
        DBInt32 AisBinaryAcknowledgeMessageSequenceNumber2( ) const
        {
            return abacSequenceNumber2_;
        }
        const DBGuid& AisBinaryAcknowledgeMessageMmsi2( ) const
        {
            return abacMmsi2_;
        }
        DBInt32 AisBinaryAcknowledgeMessageSequenceNumber3( ) const
        {
            return abacSequenceNumber3_;
        }
        const DBGuid& AisBinaryAcknowledgeMessageMmsi3( ) const
        {
            return abacMmsi3_;
        }
        DBInt32 AisBinaryAcknowledgeMessageSequenceNumber4( ) const
        {
            return abacSequenceNumber4_;
        }
        const DBGuid& AisBinaryAcknowledgeMessageMmsi4( ) const
        {
            return abacMmsi4_;
        }
        DBInt32 AisBinaryAddressedMessageSequenceNumber( ) const
        {
            return abamSequenceNumber_;
        }
        const DBGuid& AisBinaryAddressedMessageDestinationMmsi( ) const
        {
            return abamDestinationMmsi_;
        }
        DBBoolean AisBinaryAddressedMessageRetransmitFlag( ) const
        {
            return abamRetransmitFlag_;
        }
        DBInt32 AisBinaryAddressedMessageSpare( ) const
        {
            return abamSpare_;
        }
        DBInt32 AisBinaryAddressedMessageDesignatedAreaCode( ) const
        {
            return abamDesignatedAreaCode_;
        }
        DBInt32 AisBinaryAddressedMessageFunctionalId( ) const
        {
            return abamFunctionalId_;
        }
        const DBWideString& AisBinaryAddressedMessageData( ) const
        {
            return abamData_;
        }
        DBInt32 AisBinaryBroadcastMessageSpare( ) const
        {
            return abbmSpare_;
        }
        DBInt32 AisBinaryBroadcastMessageDesignatedAreaCode( ) const
        {
            return abbmDesignatedAreaCode_;
        }
        DBInt32 AisBinaryBroadcastMessageFunctionalId( ) const
        {
            return abbmFunctionalId_;
        }
        const DBWideString& AisBinaryBroadcastMessageData( ) const
        {
            return abbmData_;
        }
        DBInt32 AisDataLinkManagementMessageSpare( ) const
        {
            return adlmmSpare_;
        }
        DBInt32 AisDataLinkManagementMessageOffset1( ) const
        {
            return adlmmOffset1_;
        }
        DBInt32 AisDataLinkManagementMessageReservedSlots1( ) const
        {
            return adlmmReservedSlots1_;
        }
        DBInt32 AisDataLinkManagementMessageTimeout1( ) const
        {
            return adlmmTimeout1_;
        }
        DBInt32 AisDataLinkManagementMessageIncrement1( ) const
        {
            return adlmmIncrement1_;
        }
        DBInt32 AisDataLinkManagementMessageOffset2( ) const
        {
            return adlmmOffset2_;
        }
        DBInt32 AisDataLinkManagementMessageReservedSlots2( ) const
        {
            return adlmmReservedSlots2_;
        }
        DBInt32 AisDataLinkManagementMessageTimeout2( ) const
        {
            return adlmmTimeout2_;
        }
        DBInt32 AisDataLinkManagementMessageIncrement2( ) const
        {
            return adlmmIncrement2_;
        }
        DBInt32 AisDataLinkManagementMessageOffset3( ) const
        {
            return adlmmOffset3_;
        }
        DBInt32 AisDataLinkManagementMessageReservedSlots3( ) const
        {
            return adlmmReservedSlots3_;
        }
        DBInt32 AisDataLinkManagementMessageTimeout3( ) const
        {
            return adlmmTimeout3_;
        }
        DBInt32 AisDataLinkManagementMessageIncrement3( ) const
        {
            return adlmmIncrement3_;
        }
        DBInt32 AisDataLinkManagementMessageOffset4( ) const
        {
            return adlmmOffset4_;
        }
        DBInt32 AisDataLinkManagementMessageReservedSlots4( ) const
        {
            return adlmmReservedSlots4_;
        }
        DBInt32 AisDataLinkManagementMessageTimeout4( ) const
        {
            return adlmmTimeout4_;
        }
        DBInt32 AisDataLinkManagementMessageIncrement4( ) const
        {
            return adlmmIncrement4_;
        }
        DBInt32 AisExtendedClassBCsPositionReportMessageReserved( ) const
        {
            return aecbprmReserved_;
        }
        DBDouble AisExtendedClassBCsPositionReportMessageSpeedOverGround( ) const
        {
            return aecbprmSpeedOverGround_;
        }
        DBEnum<Data::PositionAccuracy> AisExtendedClassBCsPositionReportMessagePositionAccuracy( ) const
        {
            return aecbprmPositionAccuracy_;
        }
        DBDouble AisExtendedClassBCsPositionReportMessageLongitude( ) const
        {
            return aecbprmLongitude_;
        }
        DBDouble AisExtendedClassBCsPositionReportMessageLatitude( ) const
        {
            return aecbprmLatitude_;
        }
        DBDouble AisExtendedClassBCsPositionReportMessageCourseOverGround( ) const
        {
            return aecbprmCourseOverGround_;
        }
        DBInt32 AisExtendedClassBCsPositionReportMessageTrueHeading( ) const
        {
            return aecbprmTrueHeading_;
        }
        DBInt32 AisExtendedClassBCsPositionReportMessageTimestamp( ) const
        {
            return aecbprmTimestamp_;
        }
        DBInt32 AisExtendedClassBCsPositionReportMessageRegionalReserved( ) const
        {
            return aecbprmRegionalReserved_;
        }
        const DBGuid& AisExtendedClassBCsPositionReportMessageName( ) const
        {
            return aecbprmName_;
        }
        DBEnum<Data::ShipType> AisExtendedClassBCsPositionReportMessageShipType( ) const
        {
            return aecbprmShipType_;
        }
        DBInt32 AisExtendedClassBCsPositionReportMessageDimensionToBow( ) const
        {
            return aecbprmDimensionToBow_;
        }
        DBInt32 AisExtendedClassBCsPositionReportMessageDimensionToStern( ) const
        {
            return aecbprmDimensionToStern_;
        }
        DBInt32 AisExtendedClassBCsPositionReportMessageDimensionToPort( ) const
        {
            return aecbprmDimensionToPort_;
        }
        DBInt32 AisExtendedClassBCsPositionReportMessageDimensionToStarboard( ) const
        {
            return aecbprmDimensionToStarboard_;
        }
        DBEnum<Data::PositionFixType> AisExtendedClassBCsPositionReportMessagePositionFixType( ) const
        {
            return aecbprmPositionFixType_;
        }
        DBEnum<Data::Raim> AisExtendedClassBCsPositionReportMessageRaim( ) const
        {
            return aecbprmRaim_;
        }
        DBBoolean AisExtendedClassBCsPositionReportMessageDataTerminalReady( ) const
        {
            return aecbprmDataTerminalReady_;
        }
        DBBoolean AisExtendedClassBCsPositionReportMessageAssigned( ) const
        {
            return aecbprmAssigned_;
        }
        DBInt32 AisExtendedClassBCsPositionReportMessageSpare( ) const
        {
            return aecbprmSpare_;
        }
        const DBGuid& AisInterrogationMessageInterrogatedMmsi( ) const
        {
            return aimInterrogatedMmsi_;
        }
        DBEnum<Data::AisMessageType> AisInterrogationMessageFirstMessageType( ) const
        {
            return aimFirstMessageType_;
        }
        DBInt32 AisInterrogationMessageFirstSlotOffset( ) const
        {
            return aimFirstSlotOffset_;
        }
        DBEnum<Data::AisMessageType> AisInterrogationMessageSecondMessageType( ) const
        {
            return aimSecondMessageType_;
        }
        DBInt32 AisInterrogationMessageSecondSlotOffset( ) const
        {
            return aimSecondSlotOffset_;
        }
        const DBGuid& AisInterrogationMessageSecondStationInterrogationMmsi( ) const
        {
            return aimSecondStationInterrogationMmsi_;
        }
        DBEnum<Data::AisMessageType> AisInterrogationMessageSecondStationFirstMessageType( ) const
        {
            return aimSecondStationFirstMessageType_;
        }
        DBInt32 AisInterrogationMessageSecondStationFirstSlotOffset( ) const
        {
            return aimSecondStationFirstSlotOffset_;
        }
        DBEnum<Data::NavigationStatus> AisPositionReportClassAMessageBaseNavigationStatus( ) const
        {
            return aprcabNavigationStatus_;
        }
        DBInt32 AisPositionReportClassAMessageBaseRateOfTurn( ) const
        {
            return aprcabRateOfTurn_;
        }
        DBDouble AisPositionReportClassAMessageBaseSpeedOverGround( ) const
        {
            return aprcabSpeedOverGround_;
        }
        DBEnum<Data::PositionAccuracy> AisPositionReportClassAMessageBasePositionAccuracy( ) const
        {
            return aprcabPositionAccuracy_;
        }
        DBDouble AisPositionReportClassAMessageBaseLongitude( ) const
        {
            return aprcabLongitude_;
        }
        DBDouble AisPositionReportClassAMessageBaseLatitude( ) const
        {
            return aprcabLatitude_;
        }
        DBDouble AisPositionReportClassAMessageBaseCourseOverGround( ) const
        {
            return aprcabCourseOverGround_;
        }
        DBInt32 AisPositionReportClassAMessageBaseTrueHeading( ) const
        {
            return aprcabTrueHeading_;
        }
        DBInt32 AisPositionReportClassAMessageBaseTimestamp( ) const
        {
            return aprcabTimestamp_;
        }
        DBEnum<Data::ManeuverIndicator> AisPositionReportClassAMessageBaseManeuverIndicator( ) const
        {
            return aprcabManeuverIndicator_;
        }
        DBInt32 AisPositionReportClassAMessageBaseSpare( ) const
        {
            return aprcabSpare_;
        }
        DBEnum<Data::Raim> AisPositionReportClassAMessageBaseRaim( ) const
        {
            return aprcabRaim_;
        }
        DBInt32 AisPositionReportClassAMessageBaseRadioStatus( ) const
        {
            return aprcabRadioStatus_;
        }
        DBEnum<Data::PositionAccuracy> AisPositionReportForLongRangeApplicationsMessagePositionAccuracy( ) const
        {
            return aprflramPositionAccuracy_;
        }
        DBEnum<Data::Raim> AisPositionReportForLongRangeApplicationsMessageRaim( ) const
        {
            return aprflramRaim_;
        }
        DBEnum<Data::NavigationStatus> AisPositionReportForLongRangeApplicationsMessageNavigationStatus( ) const
        {
            return aprflramNavigationStatus_;
        }
        DBDouble AisPositionReportForLongRangeApplicationsMessageLongitude( ) const
        {
            return aprflramLongitude_;
        }
        DBDouble AisPositionReportForLongRangeApplicationsMessageLatitude( ) const
        {
            return aprflramLatitude_;
        }
        DBDouble AisPositionReportForLongRangeApplicationsMessageSpeedOverGround( ) const
        {
            return aprflramSpeedOverGround_;
        }
        DBDouble AisPositionReportForLongRangeApplicationsMessageCourseOverGround( ) const
        {
            return aprflramCourseOverGround_;
        }
        DBEnum<Data::GnssPositionStatus> AisPositionReportForLongRangeApplicationsMessageGnssPositionStatus( ) const
        {
            return aprflramGnssPositionStatus_;
        }
        DBInt32 AisPositionReportForLongRangeApplicationsMessageSpare( ) const
        {
            return aprflramSpare_;
        }
        DBInt32 AisSafetyRelatedAcknowledgmentMessageSpare( ) const
        {
            return asramSpare_;
        }
        DBInt32 AisSafetyRelatedAcknowledgmentMessageSequenceNumber1( ) const
        {
            return asramSequenceNumber1_;
        }
        const DBGuid& AisSafetyRelatedAcknowledgmentMessageMmsi1( ) const
        {
            return asramMmsi1_;
        }
        DBInt32 AisSafetyRelatedAcknowledgmentMessageSequenceNumber2( ) const
        {
            return asramSequenceNumber2_;
        }
        const DBGuid& AisSafetyRelatedAcknowledgmentMessageMmsi2( ) const
        {
            return asramMmsi2_;
        }
        DBInt32 AisSafetyRelatedAcknowledgmentMessageSequenceNumber3( ) const
        {
            return asramSequenceNumber3_;
        }
        const DBGuid& AisSafetyRelatedAcknowledgmentMessageMmsi3( ) const
        {
            return asramMmsi3_;
        }
        DBInt32 AisSafetyRelatedAcknowledgmentMessageSequenceNumber4( ) const
        {
            return asramSequenceNumber4_;
        }
        const DBGuid& AisSafetyRelatedAcknowledgmentMessageMmsi4( ) const
        {
            return asramMmsi4_;
        }
        DBInt32 AisStandardClassBCsPositionReportMessageReserved( ) const
        {
            return ascbprmReserved_;
        }
        DBDouble AisStandardClassBCsPositionReportMessageSpeedOverGround( ) const
        {
            return ascbprmSpeedOverGround_;
        }
        DBEnum<Data::PositionAccuracy> AisStandardClassBCsPositionReportMessagePositionAccuracy( ) const
        {
            return ascbprmPositionAccuracy_;
        }
        DBDouble AisStandardClassBCsPositionReportMessageLongitude( ) const
        {
            return ascbprmLongitude_;
        }
        DBDouble AisStandardClassBCsPositionReportMessageLatitude( ) const
        {
            return ascbprmLatitude_;
        }
        DBDouble AisStandardClassBCsPositionReportMessageCourseOverGround( ) const
        {
            return ascbprmCourseOverGround_;
        }
        DBInt32 AisStandardClassBCsPositionReportMessageTrueHeading( ) const
        {
            return ascbprmTrueHeading_;
        }
        DBInt32 AisStandardClassBCsPositionReportMessageTimestamp( ) const
        {
            return ascbprmTimestamp_;
        }
        DBInt32 AisStandardClassBCsPositionReportMessageRegionalReserved( ) const
        {
            return ascbprmRegionalReserved_;
        }
        DBBoolean AisStandardClassBCsPositionReportMessageIsCsUnit( ) const
        {
            return ascbprmIsCsUnit_;
        }
        DBBoolean AisStandardClassBCsPositionReportMessageHasDisplay( ) const
        {
            return ascbprmHasDisplay_;
        }
        DBBoolean AisStandardClassBCsPositionReportMessageHasDscCapability( ) const
        {
            return ascbprmHasDscCapability_;
        }
        DBBoolean AisStandardClassBCsPositionReportMessageBand( ) const
        {
            return ascbprmBand_;
        }
        DBBoolean AisStandardClassBCsPositionReportMessageCanAcceptMessage22( ) const
        {
            return ascbprmCanAcceptMessage22_;
        }
        DBBoolean AisStandardClassBCsPositionReportMessageAssigned( ) const
        {
            return ascbprmAssigned_;
        }
        DBEnum<Data::Raim> AisStandardClassBCsPositionReportMessageRaim( ) const
        {
            return ascbprmRaim_;
        }
        DBInt32 AisStandardClassBCsPositionReportMessageRadioStatus( ) const
        {
            return ascbprmRadioStatus_;
        }
        DBInt32 AisStandardSarAircraftPositionReportMessageAltitude( ) const
        {
            return assaprmAltitude_;
        }
        DBInt32 AisStandardSarAircraftPositionReportMessageSpeedOverGround( ) const
        {
            return assaprmSpeedOverGround_;
        }
        DBEnum<Data::PositionAccuracy> AisStandardSarAircraftPositionReportMessagePositionAccuracy( ) const
        {
            return assaprmPositionAccuracy_;
        }
        DBDouble AisStandardSarAircraftPositionReportMessageLongitude( ) const
        {
            return assaprmLongitude_;
        }
        DBDouble AisStandardSarAircraftPositionReportMessageLatitude( ) const
        {
            return assaprmLatitude_;
        }
        DBDouble AisStandardSarAircraftPositionReportMessageCourseOverGround( ) const
        {
            return assaprmCourseOverGround_;
        }
        DBInt32 AisStandardSarAircraftPositionReportMessageTimestamp( ) const
        {
            return assaprmTimestamp_;
        }
        DBInt32 AisStandardSarAircraftPositionReportMessageReserved( ) const
        {
            return assaprmReserved_;
        }
        DBBoolean AisStandardSarAircraftPositionReportMessageDataTerminalReady( ) const
        {
            return assaprmDataTerminalReady_;
        }
        DBInt32 AisStandardSarAircraftPositionReportMessageSpare( ) const
        {
            return assaprmSpare_;
        }
        DBBoolean AisStandardSarAircraftPositionReportMessageAssigned( ) const
        {
            return assaprmAssigned_;
        }
        DBEnum<Data::Raim> AisStandardSarAircraftPositionReportMessageRaim( ) const
        {
            return assaprmRaim_;
        }
        DBInt32 AisStandardSarAircraftPositionReportMessageRadioStatus( ) const
        {
            return assaprmRadioStatus_;
        }
        DBInt32 AisStaticAndVoyageRelatedDataMessageAisVersion( ) const
        {
            return asavrdmAisVersion_;
        }
        const DBGuid& AisStaticAndVoyageRelatedDataMessageImoNumber( ) const
        {
            return asavrdmImoNumber_;
        }
        const DBGuid& AisStaticAndVoyageRelatedDataMessageCallsign( ) const
        {
            return asavrdmCallsign_;
        }
        const DBGuid& AisStaticAndVoyageRelatedDataMessageShipName( ) const
        {
            return asavrdmShipName_;
        }
        DBEnum<Data::ShipType> AisStaticAndVoyageRelatedDataMessageShipType( ) const
        {
            return asavrdmShipType_;
        }
        DBInt32 AisStaticAndVoyageRelatedDataMessageDimensionToBow( ) const
        {
            return asavrdmDimensionToBow_;
        }
        DBInt32 AisStaticAndVoyageRelatedDataMessageDimensionToStern( ) const
        {
            return asavrdmDimensionToStern_;
        }
        DBInt32 AisStaticAndVoyageRelatedDataMessageDimensionToPort( ) const
        {
            return asavrdmDimensionToPort_;
        }
        DBInt32 AisStaticAndVoyageRelatedDataMessageDimensionToStarboard( ) const
        {
            return asavrdmDimensionToStarboard_;
        }
        DBEnum<Data::PositionFixType> AisStaticAndVoyageRelatedDataMessagePositionFixType( ) const
        {
            return asavrdmPositionFixType_;
        }
        const DBDateTime& AisStaticAndVoyageRelatedDataMessageEstimatedTimeOfArrival( ) const
        {
            return asavrdmEstimatedTimeOfArrival_;
        }
        DBDouble AisStaticAndVoyageRelatedDataMessageDraught( ) const
        {
            return asavrdmDraught_;
        }
        const FixedDBWideString<100>& AisStaticAndVoyageRelatedDataMessageDestination( ) const
        {
            return asavrdmDestination_;
        }
        DBBoolean AisStaticAndVoyageRelatedDataMessageDataTerminalReady( ) const
        {
            return asavrdmDataTerminalReady_;
        }
        DBInt32 AisStaticAndVoyageRelatedDataMessageSpare( ) const
        {
            return asavrdmSpare_;
        }
        DBInt32 AisStaticDataReportMessagePartNumber( ) const
        {
            return asdrmPartNumber_;
        }
        const DBGuid& AisStaticDataReportPartAMessageShipName( ) const
        {
            return asdrpaShipName_;
        }
        DBInt32 AisStaticDataReportPartAMessageSpare( ) const
        {
            return asdrpaSpare_;
        }
        DBEnum<Data::ShipType> AisStaticDataReportPartBMessageShipType( ) const
        {
            return asdrpbShipType_;
        }
        const FixedDBWideString<100>& AisStaticDataReportPartBMessageVendorId( ) const
        {
            return asdrpbVendorId_;
        }
        DBInt32 AisStaticDataReportPartBMessageUnitModelCode( ) const
        {
            return asdrpbUnitModelCode_;
        }
        DBInt32 AisStaticDataReportPartBMessageSerialNumber( ) const
        {
            return asdrpbSerialNumber_;
        }
        const DBGuid& AisStaticDataReportPartBMessageCallsign( ) const
        {
            return asdrpbCallsign_;
        }
        DBInt32 AisStaticDataReportPartBMessageDimensionToBow( ) const
        {
            return asdrpbDimensionToBow_;
        }
        DBInt32 AisStaticDataReportPartBMessageDimensionToStern( ) const
        {
            return asdrpbDimensionToStern_;
        }
        DBInt32 AisStaticDataReportPartBMessageDimensionToPort( ) const
        {
            return asdrpbDimensionToPort_;
        }
        DBInt32 AisStaticDataReportPartBMessageDimensionToStarboard( ) const
        {
            return asdrpbDimensionToStarboard_;
        }
        const DBGuid& AisStaticDataReportPartBMessageMothershipMmsi( ) const
        {
            return asdrpbMothershipMmsi_;
        }
        DBEnum<Data::PositionFixType> AisStaticDataReportPartBMessagePositionFixType( ) const
        {
            return asdrpbPositionFixType_;
        }
        DBInt32 AisStaticDataReportPartBMessageSpare( ) const
        {
            return asdrpbSpare_;
        }
        DBInt32 AisUtcAndDateInquiryMessageSpare1( ) const
        {
            return auadimSpare1_;
        }
        DBInt32 AisUtcAndDateInquiryMessageDestinationMmsi( ) const
        {
            return auadimDestinationMmsi_;
        }
        DBInt32 AisUtcAndDateInquiryMessageSpare2( ) const
        {
            return auadimSpare2_;
        }
        const DBDateTime& AisUtcAndDateResponseMessageDatetime( ) const
        {
            return auadrmDatetime_;
        }
        DBEnum<Data::PositionAccuracy> AisUtcAndDateResponseMessagePositionAccuracy( ) const
        {
            return auadrmPositionAccuracy_;
        }
        DBDouble AisUtcAndDateResponseMessageLongitude( ) const
        {
            return auadrmLongitude_;
        }
        DBDouble AisUtcAndDateResponseMessageLatitude( ) const
        {
            return auadrmLatitude_;
        }
        DBEnum<Data::PositionFixType> AisUtcAndDateResponseMessagePositionFixType( ) const
        {
            return auadrmPositionFixType_;
        }
        DBInt32 AisUtcAndDateResponseMessageSpare( ) const
        {
            return auadrmSpare_;
        }
        DBEnum<Data::Raim> AisUtcAndDateResponseMessageRaim( ) const
        {
            return auadrmRaim_;
        }
        DBInt32 AisUtcAndDateResponseMessageRadioStatus( ) const
        {
            return auadrmRadioStatus_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, aisDevice_);
            WriteColumnValue( destination, receivedTimestamp_);
            WriteColumnValue( destination, messageSequenceNumber_);
            WriteColumnValue( destination, repeat_);
            WriteColumnValue( destination, mmsi_);
            switch( kind_ )
            {
                case Data::Kind::AidToNavigationReportMessage:
                {
                    WriteColumnValue( destination, atnrmNavigationalAidType_);
                    WriteColumnValue( destination, atnrmName_);
                    WriteColumnValue( destination, atnrmPositionAccuracy_);
                    WriteColumnValue( destination, atnrmLongitude_);
                    WriteColumnValue( destination, atnrmLatitude_);
                    WriteColumnValue( destination, atnrmDimensionToBow_);
                    WriteColumnValue( destination, atnrmDimensionToStern_);
                    WriteColumnValue( destination, atnrmDimensionToPort_);
                    WriteColumnValue( destination, atnrmDimensionToStarboard_);
                    WriteColumnValue( destination, atnrmPositionFixType_);
                    WriteColumnValue( destination, atnrmTimestamp_);
                    WriteColumnValue( destination, atnrmOffPosition_);
                    WriteColumnValue( destination, atnrmRegionalReserved_);
                    WriteColumnValue( destination, atnrmRaim_);
                    WriteColumnValue( destination, atnrmVirtualAid_);
                    WriteColumnValue( destination, atnrmAssigned_);
                    WriteColumnValue( destination, atnrmSpare_);
                    WriteColumnValue( destination, atnrmNameExtension_);
                }
                break;
                case Data::Kind::AisAddressedSafetyRelatedMessage:
                {
                    WriteColumnValue( destination, aasrmSequenceNumber_);
                    WriteColumnValue( destination, aasrmDestinationMmsi_);
                    WriteColumnValue( destination, aasrmRetransmitFlag_);
                    WriteColumnValue( destination, aasrmSpare_);
                    WriteColumnValue( destination, aasrmText_);
                }
                break;
                case Data::Kind::AisBaseStationReportMessage:
                {
                    WriteColumnValue( destination, absrmTimestamp_);
                    WriteColumnValue( destination, absrmPositionAccuracy_);
                    WriteColumnValue( destination, absrmLongitude_);
                    WriteColumnValue( destination, absrmLatitude_);
                    WriteColumnValue( destination, absrmPositionFixType_);
                    WriteColumnValue( destination, absrmSpare_);
                    WriteColumnValue( destination, absrmRaim_);
                    WriteColumnValue( destination, absrmRadioStatus_);
                }
                break;
                case Data::Kind::AisBinaryAcknowledgeMessage:
                {
                    WriteColumnValue( destination, abacSpare_);
                    WriteColumnValue( destination, abacSequenceNumber1_);
                    WriteColumnValue( destination, abacMmsi1_);
                    WriteColumnValue( destination, abacSequenceNumber2_);
                    WriteColumnValue( destination, abacMmsi2_);
                    WriteColumnValue( destination, abacSequenceNumber3_);
                    WriteColumnValue( destination, abacMmsi3_);
                    WriteColumnValue( destination, abacSequenceNumber4_);
                    WriteColumnValue( destination, abacMmsi4_);
                }
                break;
                case Data::Kind::AisBinaryAddressedMessage:
                {
                    WriteColumnValue( destination, abamSequenceNumber_);
                    WriteColumnValue( destination, abamDestinationMmsi_);
                    WriteColumnValue( destination, abamRetransmitFlag_);
                    WriteColumnValue( destination, abamSpare_);
                    WriteColumnValue( destination, abamDesignatedAreaCode_);
                    WriteColumnValue( destination, abamFunctionalId_);
                    WriteColumnValue( destination, abamData_);
                }
                break;
                case Data::Kind::AisBinaryBroadcastMessage:
                {
                    WriteColumnValue( destination, abbmSpare_);
                    WriteColumnValue( destination, abbmDesignatedAreaCode_);
                    WriteColumnValue( destination, abbmFunctionalId_);
                    WriteColumnValue( destination, abbmData_);
                }
                break;
                case Data::Kind::AisDataLinkManagementMessage:
                {
                    WriteColumnValue( destination, adlmmSpare_);
                    WriteColumnValue( destination, adlmmOffset1_);
                    WriteColumnValue( destination, adlmmReservedSlots1_);
                    WriteColumnValue( destination, adlmmTimeout1_);
                    WriteColumnValue( destination, adlmmIncrement1_);
                    WriteColumnValue( destination, adlmmOffset2_);
                    WriteColumnValue( destination, adlmmReservedSlots2_);
                    WriteColumnValue( destination, adlmmTimeout2_);
                    WriteColumnValue( destination, adlmmIncrement2_);
                    WriteColumnValue( destination, adlmmOffset3_);
                    WriteColumnValue( destination, adlmmReservedSlots3_);
                    WriteColumnValue( destination, adlmmTimeout3_);
                    WriteColumnValue( destination, adlmmIncrement3_);
                    WriteColumnValue( destination, adlmmOffset4_);
                    WriteColumnValue( destination, adlmmReservedSlots4_);
                    WriteColumnValue( destination, adlmmTimeout4_);
                    WriteColumnValue( destination, adlmmIncrement4_);
                }
                break;
                case Data::Kind::AisExtendedClassBCsPositionReportMessage:
                {
                    WriteColumnValue( destination, aecbprmReserved_);
                    WriteColumnValue( destination, aecbprmSpeedOverGround_);
                    WriteColumnValue( destination, aecbprmPositionAccuracy_);
                    WriteColumnValue( destination, aecbprmLongitude_);
                    WriteColumnValue( destination, aecbprmLatitude_);
                    WriteColumnValue( destination, aecbprmCourseOverGround_);
                    WriteColumnValue( destination, aecbprmTrueHeading_);
                    WriteColumnValue( destination, aecbprmTimestamp_);
                    WriteColumnValue( destination, aecbprmRegionalReserved_);
                    WriteColumnValue( destination, aecbprmName_);
                    WriteColumnValue( destination, aecbprmShipType_);
                    WriteColumnValue( destination, aecbprmDimensionToBow_);
                    WriteColumnValue( destination, aecbprmDimensionToStern_);
                    WriteColumnValue( destination, aecbprmDimensionToPort_);
                    WriteColumnValue( destination, aecbprmDimensionToStarboard_);
                    WriteColumnValue( destination, aecbprmPositionFixType_);
                    WriteColumnValue( destination, aecbprmRaim_);
                    WriteColumnValue( destination, aecbprmDataTerminalReady_);
                    WriteColumnValue( destination, aecbprmAssigned_);
                    WriteColumnValue( destination, aecbprmSpare_);
                }
                break;
                case Data::Kind::AisInterrogationMessage:
                {
                    WriteColumnValue( destination, aimInterrogatedMmsi_);
                    WriteColumnValue( destination, aimFirstMessageType_);
                    WriteColumnValue( destination, aimFirstSlotOffset_);
                    WriteColumnValue( destination, aimSecondMessageType_);
                    WriteColumnValue( destination, aimSecondSlotOffset_);
                    WriteColumnValue( destination, aimSecondStationInterrogationMmsi_);
                    WriteColumnValue( destination, aimSecondStationFirstMessageType_);
                    WriteColumnValue( destination, aimSecondStationFirstSlotOffset_);
                }
                break;
                case Data::Kind::AisPositionReportClassAAssignedScheduleMessage:
                {
                    WriteColumnValue( destination, aprcabNavigationStatus_);
                    WriteColumnValue( destination, aprcabRateOfTurn_);
                    WriteColumnValue( destination, aprcabSpeedOverGround_);
                    WriteColumnValue( destination, aprcabPositionAccuracy_);
                    WriteColumnValue( destination, aprcabLongitude_);
                    WriteColumnValue( destination, aprcabLatitude_);
                    WriteColumnValue( destination, aprcabCourseOverGround_);
                    WriteColumnValue( destination, aprcabTrueHeading_);
                    WriteColumnValue( destination, aprcabTimestamp_);
                    WriteColumnValue( destination, aprcabManeuverIndicator_);
                    WriteColumnValue( destination, aprcabSpare_);
                    WriteColumnValue( destination, aprcabRaim_);
                    WriteColumnValue( destination, aprcabRadioStatus_);
                }
                break;
                case Data::Kind::AisPositionReportClassAMessage:
                {
                    WriteColumnValue( destination, aprcabNavigationStatus_);
                    WriteColumnValue( destination, aprcabRateOfTurn_);
                    WriteColumnValue( destination, aprcabSpeedOverGround_);
                    WriteColumnValue( destination, aprcabPositionAccuracy_);
                    WriteColumnValue( destination, aprcabLongitude_);
                    WriteColumnValue( destination, aprcabLatitude_);
                    WriteColumnValue( destination, aprcabCourseOverGround_);
                    WriteColumnValue( destination, aprcabTrueHeading_);
                    WriteColumnValue( destination, aprcabTimestamp_);
                    WriteColumnValue( destination, aprcabManeuverIndicator_);
                    WriteColumnValue( destination, aprcabSpare_);
                    WriteColumnValue( destination, aprcabRaim_);
                    WriteColumnValue( destination, aprcabRadioStatus_);
                }
                break;
                case Data::Kind::AisPositionReportClassAResponseToInterrogationMessage:
                {
                    WriteColumnValue( destination, aprcabNavigationStatus_);
                    WriteColumnValue( destination, aprcabRateOfTurn_);
                    WriteColumnValue( destination, aprcabSpeedOverGround_);
                    WriteColumnValue( destination, aprcabPositionAccuracy_);
                    WriteColumnValue( destination, aprcabLongitude_);
                    WriteColumnValue( destination, aprcabLatitude_);
                    WriteColumnValue( destination, aprcabCourseOverGround_);
                    WriteColumnValue( destination, aprcabTrueHeading_);
                    WriteColumnValue( destination, aprcabTimestamp_);
                    WriteColumnValue( destination, aprcabManeuverIndicator_);
                    WriteColumnValue( destination, aprcabSpare_);
                    WriteColumnValue( destination, aprcabRaim_);
                    WriteColumnValue( destination, aprcabRadioStatus_);
                }
                break;
                case Data::Kind::AisPositionReportForLongRangeApplicationsMessage:
                {
                    WriteColumnValue( destination, aprflramPositionAccuracy_);
                    WriteColumnValue( destination, aprflramRaim_);
                    WriteColumnValue( destination, aprflramNavigationStatus_);
                    WriteColumnValue( destination, aprflramLongitude_);
                    WriteColumnValue( destination, aprflramLatitude_);
                    WriteColumnValue( destination, aprflramSpeedOverGround_);
                    WriteColumnValue( destination, aprflramCourseOverGround_);
                    WriteColumnValue( destination, aprflramGnssPositionStatus_);
                    WriteColumnValue( destination, aprflramSpare_);
                }
                break;
                case Data::Kind::AisSafetyRelatedAcknowledgmentMessage:
                {
                    WriteColumnValue( destination, asramSpare_);
                    WriteColumnValue( destination, asramSequenceNumber1_);
                    WriteColumnValue( destination, asramMmsi1_);
                    WriteColumnValue( destination, asramSequenceNumber2_);
                    WriteColumnValue( destination, asramMmsi2_);
                    WriteColumnValue( destination, asramSequenceNumber3_);
                    WriteColumnValue( destination, asramMmsi3_);
                    WriteColumnValue( destination, asramSequenceNumber4_);
                    WriteColumnValue( destination, asramMmsi4_);
                }
                break;
                case Data::Kind::AisStandardClassBCsPositionReportMessage:
                {
                    WriteColumnValue( destination, ascbprmReserved_);
                    WriteColumnValue( destination, ascbprmSpeedOverGround_);
                    WriteColumnValue( destination, ascbprmPositionAccuracy_);
                    WriteColumnValue( destination, ascbprmLongitude_);
                    WriteColumnValue( destination, ascbprmLatitude_);
                    WriteColumnValue( destination, ascbprmCourseOverGround_);
                    WriteColumnValue( destination, ascbprmTrueHeading_);
                    WriteColumnValue( destination, ascbprmTimestamp_);
                    WriteColumnValue( destination, ascbprmRegionalReserved_);
                    WriteColumnValue( destination, ascbprmIsCsUnit_);
                    WriteColumnValue( destination, ascbprmHasDisplay_);
                    WriteColumnValue( destination, ascbprmHasDscCapability_);
                    WriteColumnValue( destination, ascbprmBand_);
                    WriteColumnValue( destination, ascbprmCanAcceptMessage22_);
                    WriteColumnValue( destination, ascbprmAssigned_);
                    WriteColumnValue( destination, ascbprmRaim_);
                    WriteColumnValue( destination, ascbprmRadioStatus_);
                }
                break;
                case Data::Kind::AisStandardSarAircraftPositionReportMessage:
                {
                    WriteColumnValue( destination, assaprmAltitude_);
                    WriteColumnValue( destination, assaprmSpeedOverGround_);
                    WriteColumnValue( destination, assaprmPositionAccuracy_);
                    WriteColumnValue( destination, assaprmLongitude_);
                    WriteColumnValue( destination, assaprmLatitude_);
                    WriteColumnValue( destination, assaprmCourseOverGround_);
                    WriteColumnValue( destination, assaprmTimestamp_);
                    WriteColumnValue( destination, assaprmReserved_);
                    WriteColumnValue( destination, assaprmDataTerminalReady_);
                    WriteColumnValue( destination, assaprmSpare_);
                    WriteColumnValue( destination, assaprmAssigned_);
                    WriteColumnValue( destination, assaprmRaim_);
                    WriteColumnValue( destination, assaprmRadioStatus_);
                }
                break;
                case Data::Kind::AisStaticAndVoyageRelatedDataMessage:
                {
                    WriteColumnValue( destination, asavrdmAisVersion_);
                    WriteColumnValue( destination, asavrdmImoNumber_);
                    WriteColumnValue( destination, asavrdmCallsign_);
                    WriteColumnValue( destination, asavrdmShipName_);
                    WriteColumnValue( destination, asavrdmShipType_);
                    WriteColumnValue( destination, asavrdmDimensionToBow_);
                    WriteColumnValue( destination, asavrdmDimensionToStern_);
                    WriteColumnValue( destination, asavrdmDimensionToPort_);
                    WriteColumnValue( destination, asavrdmDimensionToStarboard_);
                    WriteColumnValue( destination, asavrdmPositionFixType_);
                    WriteColumnValue( destination, asavrdmEstimatedTimeOfArrival_);
                    WriteColumnValue( destination, asavrdmDraught_);
                    WriteColumnValue( destination, asavrdmDestination_);
                    WriteColumnValue( destination, asavrdmDataTerminalReady_);
                    WriteColumnValue( destination, asavrdmSpare_);
                }
                break;
                case Data::Kind::AisStaticDataReportMessage:
                {
                    WriteColumnValue( destination, asdrmPartNumber_);
                }
                break;
                case Data::Kind::AisStaticDataReportPartAMessage:
                {
                    WriteColumnValue( destination, asdrmPartNumber_);
                    WriteColumnValue( destination, asdrpaShipName_);
                    WriteColumnValue( destination, asdrpaSpare_);
                }
                break;
                case Data::Kind::AisStaticDataReportPartBMessage:
                {
                    WriteColumnValue( destination, asdrmPartNumber_);
                    WriteColumnValue( destination, asdrpbShipType_);
                    WriteColumnValue( destination, asdrpbVendorId_);
                    WriteColumnValue( destination, asdrpbUnitModelCode_);
                    WriteColumnValue( destination, asdrpbSerialNumber_);
                    WriteColumnValue( destination, asdrpbCallsign_);
                    WriteColumnValue( destination, asdrpbDimensionToBow_);
                    WriteColumnValue( destination, asdrpbDimensionToStern_);
                    WriteColumnValue( destination, asdrpbDimensionToPort_);
                    WriteColumnValue( destination, asdrpbDimensionToStarboard_);
                    WriteColumnValue( destination, asdrpbMothershipMmsi_);
                    WriteColumnValue( destination, asdrpbPositionFixType_);
                    WriteColumnValue( destination, asdrpbSpare_);
                }
                break;
                case Data::Kind::AisUtcAndDateInquiryMessage:
                {
                    WriteColumnValue( destination, auadimSpare1_);
                    WriteColumnValue( destination, auadimDestinationMmsi_);
                    WriteColumnValue( destination, auadimSpare2_);
                }
                break;
                case Data::Kind::AisUtcAndDateResponseMessage:
                {
                    WriteColumnValue( destination, auadrmDatetime_);
                    WriteColumnValue( destination, auadrmPositionAccuracy_);
                    WriteColumnValue( destination, auadrmLongitude_);
                    WriteColumnValue( destination, auadrmLatitude_);
                    WriteColumnValue( destination, auadrmPositionFixType_);
                    WriteColumnValue( destination, auadrmSpare_);
                    WriteColumnValue( destination, auadrmRaim_);
                    WriteColumnValue( destination, auadrmRadioStatus_);
                }
                break;
            }
        }
    };

    using ComplexAisMessageDataReader = SimpleColumnDataReader<ComplexAisMessageColumnData>;

    class ComplexAisPositionReportClassAMessageBaseColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid aisDevice_;
        DateTime receivedTimestamp_;
        Int64 messageSequenceNumber_ = 0;
        Int32 repeat_ = 0;
        Guid mmsi_;
        Data::NavigationStatus navigationStatus_ = Data::NavigationStatus::UnderWayUsingEngine;
        DBInt32 rateOfTurn_;
        double speedOverGround_ = 0.0;
        Data::PositionAccuracy positionAccuracy_ = Data::PositionAccuracy::Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double courseOverGround_ = 0.0;
        DBInt32 trueHeading_;
        Int32 timestamp_ = 0;
        Data::ManeuverIndicator maneuverIndicator_ = Data::ManeuverIndicator::NotAvailable;
        Int32 spare_ = 0;
        Data::Raim raim_ = Data::Raim::NotInUse;
        Int32 radioStatus_ = 0;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT APRCAB_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT APRCAB_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT APRCAB_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT APRCAB_AISDEVICE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT APRCAB_RECEIVEDTIMESTAMP_FIELD_ID = 5;
        static constexpr SQLUSMALLINT APRCAB_MESSAGESEQUENCENUMBER_FIELD_ID = 6;
        static constexpr SQLUSMALLINT APRCAB_REPEAT_FIELD_ID = 7;
        static constexpr SQLUSMALLINT APRCAB_MMSI_FIELD_ID = 8;
        static constexpr SQLUSMALLINT APRCAB_NAVIGATIONSTATUS_FIELD_ID = 9;
        static constexpr SQLUSMALLINT APRCAB_RATEOFTURN_FIELD_ID = 10;
        static constexpr SQLUSMALLINT APRCAB_SPEEDOVERGROUND_FIELD_ID = 11;
        static constexpr SQLUSMALLINT APRCAB_POSITIONACCURACY_FIELD_ID = 12;
        static constexpr SQLUSMALLINT APRCAB_LONGITUDE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT APRCAB_LATITUDE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT APRCAB_COURSEOVERGROUND_FIELD_ID = 15;
        static constexpr SQLUSMALLINT APRCAB_TRUEHEADING_FIELD_ID = 16;
        static constexpr SQLUSMALLINT APRCAB_TIMESTAMP_FIELD_ID = 17;
        static constexpr SQLUSMALLINT APRCAB_MANEUVERINDICATOR_FIELD_ID = 18;
        static constexpr SQLUSMALLINT APRCAB_SPARE_FIELD_ID = 19;
        static constexpr SQLUSMALLINT APRCAB_RAIM_FIELD_ID = 20;
        static constexpr SQLUSMALLINT APRCAB_RADIOSTATUS_FIELD_ID = 21;

        ComplexAisPositionReportClassAMessageBaseColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& AisDevice( ) const
        {
            return aisDevice_;
        }
        const DateTime& ReceivedTimestamp( ) const
        {
            return receivedTimestamp_;
        }
        Int64 MessageSequenceNumber( ) const
        {
            return messageSequenceNumber_;
        }
        Int32 Repeat( ) const
        {
            return repeat_;
        }
        const Guid& Mmsi( ) const
        {
            return mmsi_;
        }
        Data::NavigationStatus NavigationStatus( ) const
        {
            return navigationStatus_;
        }
        DBInt32 RateOfTurn( ) const
        {
            return rateOfTurn_;
        }
        double SpeedOverGround( ) const
        {
            return speedOverGround_;
        }
        Data::PositionAccuracy PositionAccuracy( ) const
        {
            return positionAccuracy_;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        double CourseOverGround( ) const
        {
            return courseOverGround_;
        }
        DBInt32 TrueHeading( ) const
        {
            return trueHeading_;
        }
        Int32 Timestamp( ) const
        {
            return timestamp_;
        }
        Data::ManeuverIndicator ManeuverIndicator( ) const
        {
            return maneuverIndicator_;
        }
        Int32 Spare( ) const
        {
            return spare_;
        }
        Data::Raim Raim( ) const
        {
            return raim_;
        }
        Int32 RadioStatus( ) const
        {
            return radioStatus_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, aisDevice_);
            WriteColumnValue( destination, receivedTimestamp_);
            WriteColumnValue( destination, messageSequenceNumber_);
            WriteColumnValue( destination, repeat_);
            WriteColumnValue( destination, mmsi_);
            WriteColumnValue( destination, navigationStatus_);
            WriteColumnValue( destination, rateOfTurn_);
            WriteColumnValue( destination, speedOverGround_);
            WriteColumnValue( destination, positionAccuracy_);
            WriteColumnValue( destination, longitude_);
            WriteColumnValue( destination, latitude_);
            WriteColumnValue( destination, courseOverGround_);
            WriteColumnValue( destination, trueHeading_);
            WriteColumnValue( destination, timestamp_);
            WriteColumnValue( destination, maneuverIndicator_);
            WriteColumnValue( destination, spare_);
            WriteColumnValue( destination, raim_);
            WriteColumnValue( destination, radioStatus_);
        }
    };

    using ComplexAisPositionReportClassAMessageBaseDataReader = SimpleColumnDataReader<ComplexAisPositionReportClassAMessageBaseColumnData>;

    class ComplexAisStaticDataReportMessageColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid aisDevice_;
        DateTime receivedTimestamp_;
        Int64 messageSequenceNumber_ = 0;
        Int32 repeat_ = 0;
        Guid mmsi_;
        Int32 partNumber_ = 0;
        DBGuid asdrpaShipName_;
        DBInt32 asdrpaSpare_;
        DBEnum<Data::ShipType> asdrpbShipType_;
        FixedDBWideString<100> asdrpbVendorId_;
        DBInt32 asdrpbUnitModelCode_;
        DBInt32 asdrpbSerialNumber_;
        DBGuid asdrpbCallsign_;
        DBInt32 asdrpbDimensionToBow_;
        DBInt32 asdrpbDimensionToStern_;
        DBInt32 asdrpbDimensionToPort_;
        DBInt32 asdrpbDimensionToStarboard_;
        DBGuid asdrpbMothershipMmsi_;
        DBEnum<Data::PositionFixType> asdrpbPositionFixType_;
        DBInt32 asdrpbSpare_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT ASDRM_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ASDRM_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT ASDRM_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT ASDRM_AISDEVICE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT ASDRM_RECEIVEDTIMESTAMP_FIELD_ID = 5;
        static constexpr SQLUSMALLINT ASDRM_MESSAGESEQUENCENUMBER_FIELD_ID = 6;
        static constexpr SQLUSMALLINT ASDRM_REPEAT_FIELD_ID = 7;
        static constexpr SQLUSMALLINT ASDRM_MMSI_FIELD_ID = 8;
        static constexpr SQLUSMALLINT ASDRM_PARTNUMBER_FIELD_ID = 9;
        static constexpr SQLUSMALLINT ASDRPA_SHIPNAME_FIELD_ID = 10;
        static constexpr SQLUSMALLINT ASDRPA_SPARE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT ASDRPB_SHIPTYPE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT ASDRPB_VENDORID_FIELD_ID = 13;
        static constexpr SQLUSMALLINT ASDRPB_UNITMODELCODE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT ASDRPB_SERIALNUMBER_FIELD_ID = 15;
        static constexpr SQLUSMALLINT ASDRPB_CALLSIGN_FIELD_ID = 16;
        static constexpr SQLUSMALLINT ASDRPB_DIMENSIONTOBOW_FIELD_ID = 17;
        static constexpr SQLUSMALLINT ASDRPB_DIMENSIONTOSTERN_FIELD_ID = 18;
        static constexpr SQLUSMALLINT ASDRPB_DIMENSIONTOPORT_FIELD_ID = 19;
        static constexpr SQLUSMALLINT ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID = 20;
        static constexpr SQLUSMALLINT ASDRPB_MOTHERSHIPMMSI_FIELD_ID = 21;
        static constexpr SQLUSMALLINT ASDRPB_POSITIONFIXTYPE_FIELD_ID = 22;
        static constexpr SQLUSMALLINT ASDRPB_SPARE_FIELD_ID = 23;

        ComplexAisStaticDataReportMessageColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& AisDevice( ) const
        {
            return aisDevice_;
        }
        const DateTime& ReceivedTimestamp( ) const
        {
            return receivedTimestamp_;
        }
        Int64 MessageSequenceNumber( ) const
        {
            return messageSequenceNumber_;
        }
        Int32 Repeat( ) const
        {
            return repeat_;
        }
        const Guid& Mmsi( ) const
        {
            return mmsi_;
        }
        Int32 PartNumber( ) const
        {
            return partNumber_;
        }
        const DBGuid& AisStaticDataReportPartAMessageShipName( ) const
        {
            return asdrpaShipName_;
        }
        DBInt32 AisStaticDataReportPartAMessageSpare( ) const
        {
            return asdrpaSpare_;
        }
        DBEnum<Data::ShipType> AisStaticDataReportPartBMessageShipType( ) const
        {
            return asdrpbShipType_;
        }
        const FixedDBWideString<100>& AisStaticDataReportPartBMessageVendorId( ) const
        {
            return asdrpbVendorId_;
        }
        DBInt32 AisStaticDataReportPartBMessageUnitModelCode( ) const
        {
            return asdrpbUnitModelCode_;
        }
        DBInt32 AisStaticDataReportPartBMessageSerialNumber( ) const
        {
            return asdrpbSerialNumber_;
        }
        const DBGuid& AisStaticDataReportPartBMessageCallsign( ) const
        {
            return asdrpbCallsign_;
        }
        DBInt32 AisStaticDataReportPartBMessageDimensionToBow( ) const
        {
            return asdrpbDimensionToBow_;
        }
        DBInt32 AisStaticDataReportPartBMessageDimensionToStern( ) const
        {
            return asdrpbDimensionToStern_;
        }
        DBInt32 AisStaticDataReportPartBMessageDimensionToPort( ) const
        {
            return asdrpbDimensionToPort_;
        }
        DBInt32 AisStaticDataReportPartBMessageDimensionToStarboard( ) const
        {
            return asdrpbDimensionToStarboard_;
        }
        const DBGuid& AisStaticDataReportPartBMessageMothershipMmsi( ) const
        {
            return asdrpbMothershipMmsi_;
        }
        DBEnum<Data::PositionFixType> AisStaticDataReportPartBMessagePositionFixType( ) const
        {
            return asdrpbPositionFixType_;
        }
        DBInt32 AisStaticDataReportPartBMessageSpare( ) const
        {
            return asdrpbSpare_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, aisDevice_);
            WriteColumnValue( destination, receivedTimestamp_);
            WriteColumnValue( destination, messageSequenceNumber_);
            WriteColumnValue( destination, repeat_);
            WriteColumnValue( destination, mmsi_);
            WriteColumnValue( destination, partNumber_);
            switch( kind_ )
            {
                case Data::Kind::AisStaticDataReportPartAMessage:
                {
                    WriteColumnValue( destination, asdrpaShipName_);
                    WriteColumnValue( destination, asdrpaSpare_);
                }
                break;
                case Data::Kind::AisStaticDataReportPartBMessage:
                {
                    WriteColumnValue( destination, asdrpbShipType_);
                    WriteColumnValue( destination, asdrpbVendorId_);
                    WriteColumnValue( destination, asdrpbUnitModelCode_);
                    WriteColumnValue( destination, asdrpbSerialNumber_);
                    WriteColumnValue( destination, asdrpbCallsign_);
                    WriteColumnValue( destination, asdrpbDimensionToBow_);
                    WriteColumnValue( destination, asdrpbDimensionToStern_);
                    WriteColumnValue( destination, asdrpbDimensionToPort_);
                    WriteColumnValue( destination, asdrpbDimensionToStarboard_);
                    WriteColumnValue( destination, asdrpbMothershipMmsi_);
                    WriteColumnValue( destination, asdrpbPositionFixType_);
                    WriteColumnValue( destination, asdrpbSpare_);
                }
                break;
            }
        }
    };

    using ComplexAisStaticDataReportMessageDataReader = SimpleColumnDataReader<ComplexAisStaticDataReportMessageColumnData>;

    class ComplexCameraCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
        DBEnum<Data::CameraPanTiltMode> ccamPositionPanTiltMode_;
        DBDouble ccamPanAngle_;
        DBDouble ccamTiltAngle_;
        DBEnum<Data::CameraFocalLengthMode> ccamPositionFocalLengthMode_;
        DBDouble ccamFocalLength_;
        DBEnum<Data::CameraPanTiltMode> ccamSpeedPanTiltMode_;
        DBDouble ccamPanSpeed_;
        DBDouble ccamTiltSpeed_;
        DBEnum<Data::CameraFocalLengthMode> ccamSpeedFocalLengthMode_;
        DBDouble ccamZoomSpeed_;
        DBDouble ccaptzX_;
        DBDouble ccaptzY_;
        DBDouble ccaptzZ_;
        DBBoolean cccmNormalized_;
        DBDouble cccmPanVelocity_;
        DBDouble cccmTiltVelocity_;
        DBDouble cccmZoomVelocity_;
        DBTimeSpan cccmDuration_;
        DBDouble ccgmLatitude_;
        DBDouble ccgmLongitude_;
        DBDouble ccgmAltitude_;
        DBDouble ccgmViewportWidth_;
        DBDouble ccgmViewportHeight_;
        DBBoolean ccrmNormalized_;
        DBDouble ccrmPanAngle_;
        DBDouble ccrmTiltAngle_;
        DBDouble ccrmFocalLength_;
        DBDouble ccrmPanSpeed_;
        DBDouble ccrmTiltSpeed_;
        DBDouble ccrmZoomSpeed_;
        DBBoolean ccsafEnabled_;
        DBBoolean ccsbawEnabled_;
        DBGuid ccsfTrackId_;
        DBEnum<Data::CameraFollowReason> ccsfReason_;
        DBBoolean ccsirlEnabled_;
        DBBoolean cwaEnabled_;
        DBBoolean cwiEnabled_;
        DBBoolean ccsPanTilt_;
        DBBoolean ccsZoom_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT CC_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT CC_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT CC_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT CC_CAMERA_FIELD_ID = 4;
        static constexpr SQLUSMALLINT CC_TIMESTAMP_FIELD_ID = 5;
        static constexpr SQLUSMALLINT CC_DEVICECOMMANDSOURCETYPE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT CC_DEVICECOMMANDSOURCEID_FIELD_ID = 7;
        static constexpr SQLUSMALLINT CC_REPLY_FIELD_ID = 8;
        static constexpr SQLUSMALLINT CCAM_POSITIONPANTILTMODE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT CCAM_PANANGLE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT CCAM_TILTANGLE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT CCAM_POSITIONFOCALLENGTHMODE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT CCAM_FOCALLENGTH_FIELD_ID = 13;
        static constexpr SQLUSMALLINT CCAM_SPEEDPANTILTMODE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT CCAM_PANSPEED_FIELD_ID = 15;
        static constexpr SQLUSMALLINT CCAM_TILTSPEED_FIELD_ID = 16;
        static constexpr SQLUSMALLINT CCAM_SPEEDFOCALLENGTHMODE_FIELD_ID = 17;
        static constexpr SQLUSMALLINT CCAM_ZOOMSPEED_FIELD_ID = 18;
        static constexpr SQLUSMALLINT CCAPTZ_X_FIELD_ID = 19;
        static constexpr SQLUSMALLINT CCAPTZ_Y_FIELD_ID = 20;
        static constexpr SQLUSMALLINT CCAPTZ_Z_FIELD_ID = 21;
        static constexpr SQLUSMALLINT CCCM_NORMALIZED_FIELD_ID = 22;
        static constexpr SQLUSMALLINT CCCM_PANVELOCITY_FIELD_ID = 23;
        static constexpr SQLUSMALLINT CCCM_TILTVELOCITY_FIELD_ID = 24;
        static constexpr SQLUSMALLINT CCCM_ZOOMVELOCITY_FIELD_ID = 25;
        static constexpr SQLUSMALLINT CCCM_DURATION_FIELD_ID = 26;
        static constexpr SQLUSMALLINT CCGM_LATITUDE_FIELD_ID = 27;
        static constexpr SQLUSMALLINT CCGM_LONGITUDE_FIELD_ID = 28;
        static constexpr SQLUSMALLINT CCGM_ALTITUDE_FIELD_ID = 29;
        static constexpr SQLUSMALLINT CCGM_VIEWPORTWIDTH_FIELD_ID = 30;
        static constexpr SQLUSMALLINT CCGM_VIEWPORTHEIGHT_FIELD_ID = 31;
        static constexpr SQLUSMALLINT CCRM_NORMALIZED_FIELD_ID = 32;
        static constexpr SQLUSMALLINT CCRM_PANANGLE_FIELD_ID = 33;
        static constexpr SQLUSMALLINT CCRM_TILTANGLE_FIELD_ID = 34;
        static constexpr SQLUSMALLINT CCRM_FOCALLENGTH_FIELD_ID = 35;
        static constexpr SQLUSMALLINT CCRM_PANSPEED_FIELD_ID = 36;
        static constexpr SQLUSMALLINT CCRM_TILTSPEED_FIELD_ID = 37;
        static constexpr SQLUSMALLINT CCRM_ZOOMSPEED_FIELD_ID = 38;
        static constexpr SQLUSMALLINT CCSAF_ENABLED_FIELD_ID = 39;
        static constexpr SQLUSMALLINT CCSBAW_ENABLED_FIELD_ID = 40;
        static constexpr SQLUSMALLINT CCSF_TRACKID_FIELD_ID = 41;
        static constexpr SQLUSMALLINT CCSF_REASON_FIELD_ID = 42;
        static constexpr SQLUSMALLINT CCSIRL_ENABLED_FIELD_ID = 43;
        static constexpr SQLUSMALLINT CWA_ENABLED_FIELD_ID = 44;
        static constexpr SQLUSMALLINT CWI_ENABLED_FIELD_ID = 45;
        static constexpr SQLUSMALLINT CCS_PANTILT_FIELD_ID = 46;
        static constexpr SQLUSMALLINT CCS_ZOOM_FIELD_ID = 47;

        ComplexCameraCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Camera( ) const
        {
            return camera_;
        }
        const DateTime& Timestamp( ) const
        {
            return timestamp_;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        const Guid& DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        const Guid& Reply( ) const
        {
            return reply_;
        }
        DBEnum<Data::CameraPanTiltMode> CameraCommandAbsoluteMovePositionPanTiltMode( ) const
        {
            return ccamPositionPanTiltMode_;
        }
        DBDouble CameraCommandAbsoluteMovePanAngle( ) const
        {
            return ccamPanAngle_;
        }
        DBDouble CameraCommandAbsoluteMoveTiltAngle( ) const
        {
            return ccamTiltAngle_;
        }
        DBEnum<Data::CameraFocalLengthMode> CameraCommandAbsoluteMovePositionFocalLengthMode( ) const
        {
            return ccamPositionFocalLengthMode_;
        }
        DBDouble CameraCommandAbsoluteMoveFocalLength( ) const
        {
            return ccamFocalLength_;
        }
        DBEnum<Data::CameraPanTiltMode> CameraCommandAbsoluteMoveSpeedPanTiltMode( ) const
        {
            return ccamSpeedPanTiltMode_;
        }
        DBDouble CameraCommandAbsoluteMovePanSpeed( ) const
        {
            return ccamPanSpeed_;
        }
        DBDouble CameraCommandAbsoluteMoveTiltSpeed( ) const
        {
            return ccamTiltSpeed_;
        }
        DBEnum<Data::CameraFocalLengthMode> CameraCommandAbsoluteMoveSpeedFocalLengthMode( ) const
        {
            return ccamSpeedFocalLengthMode_;
        }
        DBDouble CameraCommandAbsoluteMoveZoomSpeed( ) const
        {
            return ccamZoomSpeed_;
        }
        DBDouble CameraCommandAdjustPanTiltZoomX( ) const
        {
            return ccaptzX_;
        }
        DBDouble CameraCommandAdjustPanTiltZoomY( ) const
        {
            return ccaptzY_;
        }
        DBDouble CameraCommandAdjustPanTiltZoomZ( ) const
        {
            return ccaptzZ_;
        }
        DBBoolean CameraCommandContinuousMoveNormalized( ) const
        {
            return cccmNormalized_;
        }
        DBDouble CameraCommandContinuousMovePanVelocity( ) const
        {
            return cccmPanVelocity_;
        }
        DBDouble CameraCommandContinuousMoveTiltVelocity( ) const
        {
            return cccmTiltVelocity_;
        }
        DBDouble CameraCommandContinuousMoveZoomVelocity( ) const
        {
            return cccmZoomVelocity_;
        }
        const DBTimeSpan& CameraCommandContinuousMoveDuration( ) const
        {
            return cccmDuration_;
        }
        DBDouble CameraCommandGeoMoveLatitude( ) const
        {
            return ccgmLatitude_;
        }
        DBDouble CameraCommandGeoMoveLongitude( ) const
        {
            return ccgmLongitude_;
        }
        DBDouble CameraCommandGeoMoveAltitude( ) const
        {
            return ccgmAltitude_;
        }
        DBDouble CameraCommandGeoMoveViewportWidth( ) const
        {
            return ccgmViewportWidth_;
        }
        DBDouble CameraCommandGeoMoveViewportHeight( ) const
        {
            return ccgmViewportHeight_;
        }
        DBBoolean CameraCommandRelativeMoveNormalized( ) const
        {
            return ccrmNormalized_;
        }
        DBDouble CameraCommandRelativeMovePanAngle( ) const
        {
            return ccrmPanAngle_;
        }
        DBDouble CameraCommandRelativeMoveTiltAngle( ) const
        {
            return ccrmTiltAngle_;
        }
        DBDouble CameraCommandRelativeMoveFocalLength( ) const
        {
            return ccrmFocalLength_;
        }
        DBDouble CameraCommandRelativeMovePanSpeed( ) const
        {
            return ccrmPanSpeed_;
        }
        DBDouble CameraCommandRelativeMoveTiltSpeed( ) const
        {
            return ccrmTiltSpeed_;
        }
        DBDouble CameraCommandRelativeMoveZoomSpeed( ) const
        {
            return ccrmZoomSpeed_;
        }
        DBBoolean CameraCommandSetAutoFocusEnabled( ) const
        {
            return ccsafEnabled_;
        }
        DBBoolean CameraCommandSetBlackAndWhiteEnabled( ) const
        {
            return ccsbawEnabled_;
        }
        const DBGuid& CameraCommandSetFollowedTrackId( ) const
        {
            return ccsfTrackId_;
        }
        DBEnum<Data::CameraFollowReason> CameraCommandSetFollowedReason( ) const
        {
            return ccsfReason_;
        }
        DBBoolean CameraCommandSetInfraRedLampEnabled( ) const
        {
            return ccsirlEnabled_;
        }
        DBBoolean CameraCommandSetWasherEnabled( ) const
        {
            return cwaEnabled_;
        }
        DBBoolean CameraCommandSetWiperEnabled( ) const
        {
            return cwiEnabled_;
        }
        DBBoolean CameraCommandStopPanTilt( ) const
        {
            return ccsPanTilt_;
        }
        DBBoolean CameraCommandStopZoom( ) const
        {
            return ccsZoom_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, camera_);
            WriteColumnValue( destination, timestamp_);
            WriteColumnValue( destination, deviceCommandSourceType_);
            WriteColumnValue( destination, deviceCommandSourceId_);
            WriteColumnValue( destination, reply_);
            switch( kind_ )
            {
                case Data::Kind::CameraCommandAbsoluteMove:
                {
                    WriteColumnValue( destination, ccamPositionPanTiltMode_);
                    WriteColumnValue( destination, ccamPanAngle_);
                    WriteColumnValue( destination, ccamTiltAngle_);
                    WriteColumnValue( destination, ccamPositionFocalLengthMode_);
                    WriteColumnValue( destination, ccamFocalLength_);
                    WriteColumnValue( destination, ccamSpeedPanTiltMode_);
                    WriteColumnValue( destination, ccamPanSpeed_);
                    WriteColumnValue( destination, ccamTiltSpeed_);
                    WriteColumnValue( destination, ccamSpeedFocalLengthMode_);
                    WriteColumnValue( destination, ccamZoomSpeed_);
                }
                break;
                case Data::Kind::CameraCommandAdjustPanTiltZoom:
                {
                    WriteColumnValue( destination, ccaptzX_);
                    WriteColumnValue( destination, ccaptzY_);
                    WriteColumnValue( destination, ccaptzZ_);
                }
                break;
                case Data::Kind::CameraCommandContinuousMove:
                {
                    WriteColumnValue( destination, cccmNormalized_);
                    WriteColumnValue( destination, cccmPanVelocity_);
                    WriteColumnValue( destination, cccmTiltVelocity_);
                    WriteColumnValue( destination, cccmZoomVelocity_);
                    WriteColumnValue( destination, cccmDuration_);
                }
                break;
                case Data::Kind::CameraCommandGeoMove:
                {
                    WriteColumnValue( destination, ccgmLatitude_);
                    WriteColumnValue( destination, ccgmLongitude_);
                    WriteColumnValue( destination, ccgmAltitude_);
                    WriteColumnValue( destination, ccgmViewportWidth_);
                    WriteColumnValue( destination, ccgmViewportHeight_);
                }
                break;
                case Data::Kind::CameraCommandRelativeMove:
                {
                    WriteColumnValue( destination, ccrmNormalized_);
                    WriteColumnValue( destination, ccrmPanAngle_);
                    WriteColumnValue( destination, ccrmTiltAngle_);
                    WriteColumnValue( destination, ccrmFocalLength_);
                    WriteColumnValue( destination, ccrmPanSpeed_);
                    WriteColumnValue( destination, ccrmTiltSpeed_);
                    WriteColumnValue( destination, ccrmZoomSpeed_);
                }
                break;
                case Data::Kind::CameraCommandSetAutoFocus:
                {
                    WriteColumnValue( destination, ccsafEnabled_);
                }
                break;
                case Data::Kind::CameraCommandSetBlackAndWhite:
                {
                    WriteColumnValue( destination, ccsbawEnabled_);
                }
                break;
                case Data::Kind::CameraCommandSetFollowed:
                {
                    WriteColumnValue( destination, ccsfTrackId_);
                    WriteColumnValue( destination, ccsfReason_);
                }
                break;
                case Data::Kind::CameraCommandSetInfraRedLamp:
                {
                    WriteColumnValue( destination, ccsirlEnabled_);
                }
                break;
                case Data::Kind::CameraCommandSetWasher:
                {
                    WriteColumnValue( destination, cwaEnabled_);
                }
                break;
                case Data::Kind::CameraCommandSetWiper:
                {
                    WriteColumnValue( destination, cwiEnabled_);
                }
                break;
                case Data::Kind::CameraCommandStop:
                {
                    WriteColumnValue( destination, ccsPanTilt_);
                    WriteColumnValue( destination, ccsZoom_);
                }
                break;
            }
        }
    };

    using ComplexCameraCommandDataReader = SimpleColumnDataReader<ComplexCameraCommandColumnData>;

    class ComplexCatalogElementColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid catalog_;
        FixedDBWideString<127> name_;
        DBGuid eElementType_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT CE_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT CE_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT CE_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT CE_CATALOG_FIELD_ID = 4;
        static constexpr SQLUSMALLINT CE_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT E_ELEMENTTYPE_FIELD_ID = 6;

        ComplexCatalogElementColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Catalog( ) const
        {
            return catalog_;
        }
        const FixedDBWideString<127>& Name( ) const
        {
            return name_;
        }
        const DBGuid& ElementElementType( ) const
        {
            return eElementType_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, catalog_);
            WriteColumnValue( destination, name_);
            switch( kind_ )
            {
                case Data::Kind::Element:
                {
                    WriteColumnValue( destination, eElementType_);
                }
                break;
            }
        }
    };

    using ComplexCatalogElementDataReader = SimpleColumnDataReader<ComplexCatalogElementColumnData>;

    class ComplexIdentityColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        FixedDBWideString<127> cIdentifier_;
        DBInt64 imonIdentifier_;
        DBInt64 mmsiIdentifier_;
        FixedDBWideString<100> nText_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT I_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT I_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT I_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT C_IDENTIFIER_FIELD_ID = 4;
        static constexpr SQLUSMALLINT IMON_IDENTIFIER_FIELD_ID = 5;
        static constexpr SQLUSMALLINT MMSI_IDENTIFIER_FIELD_ID = 6;
        static constexpr SQLUSMALLINT N_TEXT_FIELD_ID = 7;

        ComplexIdentityColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const FixedDBWideString<127>& CallsignIdentifier( ) const
        {
            return cIdentifier_;
        }
        DBInt64 InternationalMaritimeOrganizationNumberIdentifier( ) const
        {
            return imonIdentifier_;
        }
        DBInt64 MaritimeMobileServiceIdentityIdentifier( ) const
        {
            return mmsiIdentifier_;
        }
        const FixedDBWideString<100>& NameText( ) const
        {
            return nText_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            switch( kind_ )
            {
                case Data::Kind::Callsign:
                {
                    WriteColumnValue( destination, cIdentifier_);
                }
                break;
                case Data::Kind::InternationalMaritimeOrganizationNumber:
                {
                    WriteColumnValue( destination, imonIdentifier_);
                }
                break;
                case Data::Kind::MaritimeMobileServiceIdentity:
                {
                    WriteColumnValue( destination, mmsiIdentifier_);
                }
                break;
                case Data::Kind::Name:
                {
                    WriteColumnValue( destination, nText_);
                }
                break;
            }
        }
    };

    using ComplexIdentityDataReader = SimpleColumnDataReader<ComplexIdentityColumnData>;

    class ComplexItemColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        FixedDBWideString<127> bsName_;
        DBGuid bsType_;
        DBGuid dHost_;
        FixedDBWideString<127> dName_;
        DBWideString dDescription_;
        DBGuid dEnabledTimeseries_;
        DBGuid gLatitudeTimeseries_;
        DBGuid gLongitudeTimeseries_;
        DBGuid gAltitudeTimeseries_;
        DBGuid gdHeadingTrueNorthTimeseries_;
        DBGuid gdHeadingMagneticNorthTimeseries_;
        DBGuid gdPitchTimeseries_;
        DBGuid gdRateOfTurnTimeseries_;
        DBGuid gdRollTimeseries_;
        DBGuid gdCourseTimeseries_;
        DBGuid gdSpeedTimeseries_;
        DBGuid gdGNSSDevice_;
        DBGuid rdoRadar_;
        DBGuid rdoPressureTimeseries_;
        DBGuid rdoTemperatureTimeseries_;
        DBGuid rdoDewPointTimeseries_;
        DBGuid rdoStatusTimeseries_;
        DBGuid rdSaveSettingsTimeseries_;
        DBGuid rdPowerOnTimeseries_;
        DBGuid rdTrackingOnTimeseries_;
        DBGuid rdRadarPulseTimeseries_;
        DBGuid rdTuningTimeseries_;
        DBGuid rdBlankSector1Timeseries_;
        DBGuid rdSector1StartTimeseries_;
        DBGuid rdSector1EndTimeseries_;
        DBGuid rdBlankSector2Timeseries_;
        DBGuid rdSector2StartTimeseries_;
        DBGuid rdSector2EndTimeseries_;
        DBGuid rdEnableAutomaticFrequencyControlTimeseries_;
        DBGuid rdAzimuthOffsetTimeseries_;
        DBGuid rdEnableSensitivityTimeControlTimeseries_;
        DBGuid rdAutomaticSensitivityTimeControlTimeseries_;
        DBGuid rdSensitivityTimeControlLevelTimeseries_;
        DBGuid rdEnableFastTimeConstantTimeseries_;
        DBGuid rdFastTimeConstantLevelTimeseries_;
        DBGuid rdFastTimeConstantModeTimeseries_;
        DBGuid rdLatitudeTimeseries_;
        DBGuid rdLongitudeTimeseries_;
        DBGuid rdRadome_;
        DBGuid rdGNSSDevice_;
        DBGuid wsdBarometricPressureTimeseries_;
        DBGuid wsdAirTemperatureTimeseries_;
        DBGuid wsdWaterTemperatureTimeseries_;
        DBGuid wsdRelativeHumidityTimeseries_;
        DBGuid wsdAbsoluteHumidityTimeseries_;
        DBGuid wsdDewPointTimeseries_;
        DBGuid wsdWindDirectionTimeseries_;
        DBGuid wsdWindSpeedTimeseries_;
        DBGuid wsdGyro_;
        FixedDBWideString<127> fName_;
        DBGuid fType_;
        DBDouble fLongitude_;
        DBDouble fLatitude_;
        DBDouble fAltitude_;
        FixedDBWideString<127> aName_;
        DBGuid aType_;
        FixedDBWideString<127> aatnName_;
        DBGuid aatnMMSI_;
        DBEnum<Data::NavigationalAidType> aatnNavigationalAidType_;
        DBGuid aatnPosition_;
        DBBoolean aatnIsVirtual_;
        DBInt32 aatnToBow_;
        DBInt32 aatnToStern_;
        DBInt32 aatnToPort_;
        DBInt32 aatnToStarboard_;
        DBGuid aatnOffPositionTimeseries_;
        FixedDBWideString<127> vName_;
        DBGuid vType_;
        FixedDBWideString<127> vslName_;
        DBGuid vslType_;
        DBInt32 vslToBow_;
        DBInt32 vslToStern_;
        DBInt32 vslToPort_;
        DBInt32 vslToStarboard_;
        DBGuid vslDraughtTimeseries_;
        DBGuid vslPersonsOnBoardTimeseries_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT I_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT I_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT I_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT BS_NAME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT BS_TYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT D_HOST_FIELD_ID = 6;
        static constexpr SQLUSMALLINT D_NAME_FIELD_ID = 7;
        static constexpr SQLUSMALLINT D_ENABLEDTIMESERIES_FIELD_ID = 8;
        static constexpr SQLUSMALLINT G_LATITUDETIMESERIES_FIELD_ID = 9;
        static constexpr SQLUSMALLINT G_LONGITUDETIMESERIES_FIELD_ID = 10;
        static constexpr SQLUSMALLINT G_ALTITUDETIMESERIES_FIELD_ID = 11;
        static constexpr SQLUSMALLINT GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID = 12;
        static constexpr SQLUSMALLINT GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID = 13;
        static constexpr SQLUSMALLINT GD_PITCHTIMESERIES_FIELD_ID = 14;
        static constexpr SQLUSMALLINT GD_RATEOFTURNTIMESERIES_FIELD_ID = 15;
        static constexpr SQLUSMALLINT GD_ROLLTIMESERIES_FIELD_ID = 16;
        static constexpr SQLUSMALLINT GD_COURSETIMESERIES_FIELD_ID = 17;
        static constexpr SQLUSMALLINT GD_SPEEDTIMESERIES_FIELD_ID = 18;
        static constexpr SQLUSMALLINT GD_GNSSDEVICE_FIELD_ID = 19;
        static constexpr SQLUSMALLINT RDO_RADAR_FIELD_ID = 20;
        static constexpr SQLUSMALLINT RDO_PRESSURETIMESERIES_FIELD_ID = 21;
        static constexpr SQLUSMALLINT RDO_TEMPERATURETIMESERIES_FIELD_ID = 22;
        static constexpr SQLUSMALLINT RDO_DEWPOINTTIMESERIES_FIELD_ID = 23;
        static constexpr SQLUSMALLINT RDO_STATUSTIMESERIES_FIELD_ID = 24;
        static constexpr SQLUSMALLINT RD_SAVESETTINGSTIMESERIES_FIELD_ID = 25;
        static constexpr SQLUSMALLINT RD_POWERONTIMESERIES_FIELD_ID = 26;
        static constexpr SQLUSMALLINT RD_TRACKINGONTIMESERIES_FIELD_ID = 27;
        static constexpr SQLUSMALLINT RD_RADARPULSETIMESERIES_FIELD_ID = 28;
        static constexpr SQLUSMALLINT RD_TUNINGTIMESERIES_FIELD_ID = 29;
        static constexpr SQLUSMALLINT RD_BLANKSECTOR1TIMESERIES_FIELD_ID = 30;
        static constexpr SQLUSMALLINT RD_SECTOR1STARTTIMESERIES_FIELD_ID = 31;
        static constexpr SQLUSMALLINT RD_SECTOR1ENDTIMESERIES_FIELD_ID = 32;
        static constexpr SQLUSMALLINT RD_BLANKSECTOR2TIMESERIES_FIELD_ID = 33;
        static constexpr SQLUSMALLINT RD_SECTOR2STARTTIMESERIES_FIELD_ID = 34;
        static constexpr SQLUSMALLINT RD_SECTOR2ENDTIMESERIES_FIELD_ID = 35;
        static constexpr SQLUSMALLINT RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 36;
        static constexpr SQLUSMALLINT RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID = 37;
        static constexpr SQLUSMALLINT RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 38;
        static constexpr SQLUSMALLINT RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 39;
        static constexpr SQLUSMALLINT RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 40;
        static constexpr SQLUSMALLINT RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 41;
        static constexpr SQLUSMALLINT RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 42;
        static constexpr SQLUSMALLINT RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 43;
        static constexpr SQLUSMALLINT RD_LATITUDETIMESERIES_FIELD_ID = 44;
        static constexpr SQLUSMALLINT RD_LONGITUDETIMESERIES_FIELD_ID = 45;
        static constexpr SQLUSMALLINT RD_RADOME_FIELD_ID = 46;
        static constexpr SQLUSMALLINT RD_GNSSDEVICE_FIELD_ID = 47;
        static constexpr SQLUSMALLINT WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID = 48;
        static constexpr SQLUSMALLINT WSD_AIRTEMPERATURETIMESERIES_FIELD_ID = 49;
        static constexpr SQLUSMALLINT WSD_WATERTEMPERATURETIMESERIES_FIELD_ID = 50;
        static constexpr SQLUSMALLINT WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID = 51;
        static constexpr SQLUSMALLINT WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID = 52;
        static constexpr SQLUSMALLINT WSD_DEWPOINTTIMESERIES_FIELD_ID = 53;
        static constexpr SQLUSMALLINT WSD_WINDDIRECTIONTIMESERIES_FIELD_ID = 54;
        static constexpr SQLUSMALLINT WSD_WINDSPEEDTIMESERIES_FIELD_ID = 55;
        static constexpr SQLUSMALLINT WSD_GYRO_FIELD_ID = 56;
        static constexpr SQLUSMALLINT F_NAME_FIELD_ID = 57;
        static constexpr SQLUSMALLINT F_TYPE_FIELD_ID = 58;
        static constexpr SQLUSMALLINT F_LONGITUDE_FIELD_ID = 59;
        static constexpr SQLUSMALLINT F_LATITUDE_FIELD_ID = 60;
        static constexpr SQLUSMALLINT F_ALTITUDE_FIELD_ID = 61;
        static constexpr SQLUSMALLINT A_NAME_FIELD_ID = 62;
        static constexpr SQLUSMALLINT A_TYPE_FIELD_ID = 63;
        static constexpr SQLUSMALLINT AATN_NAME_FIELD_ID = 64;
        static constexpr SQLUSMALLINT AATN_MMSI_FIELD_ID = 65;
        static constexpr SQLUSMALLINT AATN_NAVIGATIONALAIDTYPE_FIELD_ID = 66;
        static constexpr SQLUSMALLINT AATN_POSITION_FIELD_ID = 67;
        static constexpr SQLUSMALLINT AATN_ISVIRTUAL_FIELD_ID = 68;
        static constexpr SQLUSMALLINT AATN_TOBOW_FIELD_ID = 69;
        static constexpr SQLUSMALLINT AATN_TOSTERN_FIELD_ID = 70;
        static constexpr SQLUSMALLINT AATN_TOPORT_FIELD_ID = 71;
        static constexpr SQLUSMALLINT AATN_TOSTARBOARD_FIELD_ID = 72;
        static constexpr SQLUSMALLINT AATN_OFFPOSITIONTIMESERIES_FIELD_ID = 73;
        static constexpr SQLUSMALLINT V_NAME_FIELD_ID = 74;
        static constexpr SQLUSMALLINT V_TYPE_FIELD_ID = 75;
        static constexpr SQLUSMALLINT VSL_NAME_FIELD_ID = 76;
        static constexpr SQLUSMALLINT VSL_TYPE_FIELD_ID = 77;
        static constexpr SQLUSMALLINT VSL_TOBOW_FIELD_ID = 78;
        static constexpr SQLUSMALLINT VSL_TOSTERN_FIELD_ID = 79;
        static constexpr SQLUSMALLINT VSL_TOPORT_FIELD_ID = 80;
        static constexpr SQLUSMALLINT VSL_TOSTARBOARD_FIELD_ID = 81;
        static constexpr SQLUSMALLINT VSL_DRAUGHTTIMESERIES_FIELD_ID = 82;
        static constexpr SQLUSMALLINT VSL_PERSONSONBOARDTIMESERIES_FIELD_ID = 83;
        static constexpr SQLUSMALLINT D_DESCRIPTION_FIELD_ID = 84;

        ComplexItemColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const FixedDBWideString<127>& BaseStationName( ) const
        {
            return bsName_;
        }
        const DBGuid& BaseStationType( ) const
        {
            return bsType_;
        }
        const DBGuid& DeviceHost( ) const
        {
            return dHost_;
        }
        const FixedDBWideString<127>& DeviceName( ) const
        {
            return dName_;
        }
        const DBWideString& DeviceDescription( ) const
        {
            return dDescription_;
        }
        const DBGuid& DeviceEnabledTimeseries( ) const
        {
            return dEnabledTimeseries_;
        }
        const DBGuid& GNSSDeviceLatitudeTimeseries( ) const
        {
            return gLatitudeTimeseries_;
        }
        const DBGuid& GNSSDeviceLongitudeTimeseries( ) const
        {
            return gLongitudeTimeseries_;
        }
        const DBGuid& GNSSDeviceAltitudeTimeseries( ) const
        {
            return gAltitudeTimeseries_;
        }
        const DBGuid& GyroDeviceHeadingTrueNorthTimeseries( ) const
        {
            return gdHeadingTrueNorthTimeseries_;
        }
        const DBGuid& GyroDeviceHeadingMagneticNorthTimeseries( ) const
        {
            return gdHeadingMagneticNorthTimeseries_;
        }
        const DBGuid& GyroDevicePitchTimeseries( ) const
        {
            return gdPitchTimeseries_;
        }
        const DBGuid& GyroDeviceRateOfTurnTimeseries( ) const
        {
            return gdRateOfTurnTimeseries_;
        }
        const DBGuid& GyroDeviceRollTimeseries( ) const
        {
            return gdRollTimeseries_;
        }
        const DBGuid& GyroDeviceCourseTimeseries( ) const
        {
            return gdCourseTimeseries_;
        }
        const DBGuid& GyroDeviceSpeedTimeseries( ) const
        {
            return gdSpeedTimeseries_;
        }
        const DBGuid& GyroDeviceGNSSDevice( ) const
        {
            return gdGNSSDevice_;
        }
        const DBGuid& RadomeDeviceRadar( ) const
        {
            return rdoRadar_;
        }
        const DBGuid& RadomeDevicePressureTimeseries( ) const
        {
            return rdoPressureTimeseries_;
        }
        const DBGuid& RadomeDeviceTemperatureTimeseries( ) const
        {
            return rdoTemperatureTimeseries_;
        }
        const DBGuid& RadomeDeviceDewPointTimeseries( ) const
        {
            return rdoDewPointTimeseries_;
        }
        const DBGuid& RadomeDeviceStatusTimeseries( ) const
        {
            return rdoStatusTimeseries_;
        }
        const DBGuid& RadarDeviceSaveSettingsTimeseries( ) const
        {
            return rdSaveSettingsTimeseries_;
        }
        const DBGuid& RadarDevicePowerOnTimeseries( ) const
        {
            return rdPowerOnTimeseries_;
        }
        const DBGuid& RadarDeviceTrackingOnTimeseries( ) const
        {
            return rdTrackingOnTimeseries_;
        }
        const DBGuid& RadarDeviceRadarPulseTimeseries( ) const
        {
            return rdRadarPulseTimeseries_;
        }
        const DBGuid& RadarDeviceTuningTimeseries( ) const
        {
            return rdTuningTimeseries_;
        }
        const DBGuid& RadarDeviceBlankSector1Timeseries( ) const
        {
            return rdBlankSector1Timeseries_;
        }
        const DBGuid& RadarDeviceSector1StartTimeseries( ) const
        {
            return rdSector1StartTimeseries_;
        }
        const DBGuid& RadarDeviceSector1EndTimeseries( ) const
        {
            return rdSector1EndTimeseries_;
        }
        const DBGuid& RadarDeviceBlankSector2Timeseries( ) const
        {
            return rdBlankSector2Timeseries_;
        }
        const DBGuid& RadarDeviceSector2StartTimeseries( ) const
        {
            return rdSector2StartTimeseries_;
        }
        const DBGuid& RadarDeviceSector2EndTimeseries( ) const
        {
            return rdSector2EndTimeseries_;
        }
        const DBGuid& RadarDeviceEnableAutomaticFrequencyControlTimeseries( ) const
        {
            return rdEnableAutomaticFrequencyControlTimeseries_;
        }
        const DBGuid& RadarDeviceAzimuthOffsetTimeseries( ) const
        {
            return rdAzimuthOffsetTimeseries_;
        }
        const DBGuid& RadarDeviceEnableSensitivityTimeControlTimeseries( ) const
        {
            return rdEnableSensitivityTimeControlTimeseries_;
        }
        const DBGuid& RadarDeviceAutomaticSensitivityTimeControlTimeseries( ) const
        {
            return rdAutomaticSensitivityTimeControlTimeseries_;
        }
        const DBGuid& RadarDeviceSensitivityTimeControlLevelTimeseries( ) const
        {
            return rdSensitivityTimeControlLevelTimeseries_;
        }
        const DBGuid& RadarDeviceEnableFastTimeConstantTimeseries( ) const
        {
            return rdEnableFastTimeConstantTimeseries_;
        }
        const DBGuid& RadarDeviceFastTimeConstantLevelTimeseries( ) const
        {
            return rdFastTimeConstantLevelTimeseries_;
        }
        const DBGuid& RadarDeviceFastTimeConstantModeTimeseries( ) const
        {
            return rdFastTimeConstantModeTimeseries_;
        }
        const DBGuid& RadarDeviceLatitudeTimeseries( ) const
        {
            return rdLatitudeTimeseries_;
        }
        const DBGuid& RadarDeviceLongitudeTimeseries( ) const
        {
            return rdLongitudeTimeseries_;
        }
        const DBGuid& RadarDeviceRadome( ) const
        {
            return rdRadome_;
        }
        const DBGuid& RadarDeviceGNSSDevice( ) const
        {
            return rdGNSSDevice_;
        }
        const DBGuid& WeatherStationDeviceBarometricPressureTimeseries( ) const
        {
            return wsdBarometricPressureTimeseries_;
        }
        const DBGuid& WeatherStationDeviceAirTemperatureTimeseries( ) const
        {
            return wsdAirTemperatureTimeseries_;
        }
        const DBGuid& WeatherStationDeviceWaterTemperatureTimeseries( ) const
        {
            return wsdWaterTemperatureTimeseries_;
        }
        const DBGuid& WeatherStationDeviceRelativeHumidityTimeseries( ) const
        {
            return wsdRelativeHumidityTimeseries_;
        }
        const DBGuid& WeatherStationDeviceAbsoluteHumidityTimeseries( ) const
        {
            return wsdAbsoluteHumidityTimeseries_;
        }
        const DBGuid& WeatherStationDeviceDewPointTimeseries( ) const
        {
            return wsdDewPointTimeseries_;
        }
        const DBGuid& WeatherStationDeviceWindDirectionTimeseries( ) const
        {
            return wsdWindDirectionTimeseries_;
        }
        const DBGuid& WeatherStationDeviceWindSpeedTimeseries( ) const
        {
            return wsdWindSpeedTimeseries_;
        }
        const DBGuid& WeatherStationDeviceGyro( ) const
        {
            return wsdGyro_;
        }
        const FixedDBWideString<127>& FacilityName( ) const
        {
            return fName_;
        }
        const DBGuid& FacilityType( ) const
        {
            return fType_;
        }
        DBDouble FacilityLongitude( ) const
        {
            return fLongitude_;
        }
        DBDouble FacilityLatitude( ) const
        {
            return fLatitude_;
        }
        DBDouble FacilityAltitude( ) const
        {
            return fAltitude_;
        }
        const FixedDBWideString<127>& AircraftName( ) const
        {
            return aName_;
        }
        const DBGuid& AircraftType( ) const
        {
            return aType_;
        }
        const FixedDBWideString<127>& AisAidToNavigationName( ) const
        {
            return aatnName_;
        }
        const DBGuid& AisAidToNavigationMMSI( ) const
        {
            return aatnMMSI_;
        }
        DBEnum<Data::NavigationalAidType> AisAidToNavigationNavigationalAidType( ) const
        {
            return aatnNavigationalAidType_;
        }
        const DBGuid& AisAidToNavigationPosition( ) const
        {
            return aatnPosition_;
        }
        DBBoolean AisAidToNavigationIsVirtual( ) const
        {
            return aatnIsVirtual_;
        }
        DBInt32 AisAidToNavigationToBow( ) const
        {
            return aatnToBow_;
        }
        DBInt32 AisAidToNavigationToStern( ) const
        {
            return aatnToStern_;
        }
        DBInt32 AisAidToNavigationToPort( ) const
        {
            return aatnToPort_;
        }
        DBInt32 AisAidToNavigationToStarboard( ) const
        {
            return aatnToStarboard_;
        }
        const DBGuid& AisAidToNavigationOffPositionTimeseries( ) const
        {
            return aatnOffPositionTimeseries_;
        }
        const FixedDBWideString<127>& VehicleName( ) const
        {
            return vName_;
        }
        const DBGuid& VehicleType( ) const
        {
            return vType_;
        }
        const FixedDBWideString<127>& VesselName( ) const
        {
            return vslName_;
        }
        const DBGuid& VesselType( ) const
        {
            return vslType_;
        }
        DBInt32 VesselToBow( ) const
        {
            return vslToBow_;
        }
        DBInt32 VesselToStern( ) const
        {
            return vslToStern_;
        }
        DBInt32 VesselToPort( ) const
        {
            return vslToPort_;
        }
        DBInt32 VesselToStarboard( ) const
        {
            return vslToStarboard_;
        }
        const DBGuid& VesselDraughtTimeseries( ) const
        {
            return vslDraughtTimeseries_;
        }
        const DBGuid& VesselPersonsOnBoardTimeseries( ) const
        {
            return vslPersonsOnBoardTimeseries_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            switch( kind_ )
            {
                case Data::Kind::BaseStation:
                {
                    WriteColumnValue( destination, bsName_);
                    WriteColumnValue( destination, bsType_);
                }
                break;
                case Data::Kind::CameraDevice:
                {
                    WriteColumnValue( destination, dHost_);
                    WriteColumnValue( destination, dName_);
                    WriteColumnValue( destination, dDescription_);
                    WriteColumnValue( destination, dEnabledTimeseries_);
                }
                break;
                case Data::Kind::GNSSDevice:
                {
                    WriteColumnValue( destination, dHost_);
                    WriteColumnValue( destination, dName_);
                    WriteColumnValue( destination, dDescription_);
                    WriteColumnValue( destination, dEnabledTimeseries_);
                    WriteColumnValue( destination, gLatitudeTimeseries_);
                    WriteColumnValue( destination, gLongitudeTimeseries_);
                    WriteColumnValue( destination, gAltitudeTimeseries_);
                }
                break;
                case Data::Kind::GyroDevice:
                {
                    WriteColumnValue( destination, dHost_);
                    WriteColumnValue( destination, dName_);
                    WriteColumnValue( destination, dDescription_);
                    WriteColumnValue( destination, dEnabledTimeseries_);
                    WriteColumnValue( destination, gdHeadingTrueNorthTimeseries_);
                    WriteColumnValue( destination, gdHeadingMagneticNorthTimeseries_);
                    WriteColumnValue( destination, gdPitchTimeseries_);
                    WriteColumnValue( destination, gdRateOfTurnTimeseries_);
                    WriteColumnValue( destination, gdRollTimeseries_);
                    WriteColumnValue( destination, gdCourseTimeseries_);
                    WriteColumnValue( destination, gdSpeedTimeseries_);
                    WriteColumnValue( destination, gdGNSSDevice_);
                }
                break;
                case Data::Kind::LineInputDevice:
                {
                    WriteColumnValue( destination, dHost_);
                    WriteColumnValue( destination, dName_);
                    WriteColumnValue( destination, dDescription_);
                    WriteColumnValue( destination, dEnabledTimeseries_);
                }
                break;
                case Data::Kind::OilSpillDetectorDevice:
                {
                    WriteColumnValue( destination, dHost_);
                    WriteColumnValue( destination, dName_);
                    WriteColumnValue( destination, dDescription_);
                    WriteColumnValue( destination, dEnabledTimeseries_);
                }
                break;
                case Data::Kind::RadioDevice:
                {
                    WriteColumnValue( destination, dHost_);
                    WriteColumnValue( destination, dName_);
                    WriteColumnValue( destination, dDescription_);
                    WriteColumnValue( destination, dEnabledTimeseries_);
                }
                break;
                case Data::Kind::RadomeDevice:
                {
                    WriteColumnValue( destination, dHost_);
                    WriteColumnValue( destination, dName_);
                    WriteColumnValue( destination, dDescription_);
                    WriteColumnValue( destination, dEnabledTimeseries_);
                    WriteColumnValue( destination, rdoRadar_);
                    WriteColumnValue( destination, rdoPressureTimeseries_);
                    WriteColumnValue( destination, rdoTemperatureTimeseries_);
                    WriteColumnValue( destination, rdoDewPointTimeseries_);
                    WriteColumnValue( destination, rdoStatusTimeseries_);
                }
                break;
                case Data::Kind::AisDevice:
                {
                    WriteColumnValue( destination, dHost_);
                    WriteColumnValue( destination, dName_);
                    WriteColumnValue( destination, dDescription_);
                    WriteColumnValue( destination, dEnabledTimeseries_);
                }
                break;
                case Data::Kind::RadarDevice:
                {
                    WriteColumnValue( destination, dHost_);
                    WriteColumnValue( destination, dName_);
                    WriteColumnValue( destination, dDescription_);
                    WriteColumnValue( destination, dEnabledTimeseries_);
                    WriteColumnValue( destination, rdSaveSettingsTimeseries_);
                    WriteColumnValue( destination, rdPowerOnTimeseries_);
                    WriteColumnValue( destination, rdTrackingOnTimeseries_);
                    WriteColumnValue( destination, rdRadarPulseTimeseries_);
                    WriteColumnValue( destination, rdTuningTimeseries_);
                    WriteColumnValue( destination, rdBlankSector1Timeseries_);
                    WriteColumnValue( destination, rdSector1StartTimeseries_);
                    WriteColumnValue( destination, rdSector1EndTimeseries_);
                    WriteColumnValue( destination, rdBlankSector2Timeseries_);
                    WriteColumnValue( destination, rdSector2StartTimeseries_);
                    WriteColumnValue( destination, rdSector2EndTimeseries_);
                    WriteColumnValue( destination, rdEnableAutomaticFrequencyControlTimeseries_);
                    WriteColumnValue( destination, rdAzimuthOffsetTimeseries_);
                    WriteColumnValue( destination, rdEnableSensitivityTimeControlTimeseries_);
                    WriteColumnValue( destination, rdAutomaticSensitivityTimeControlTimeseries_);
                    WriteColumnValue( destination, rdSensitivityTimeControlLevelTimeseries_);
                    WriteColumnValue( destination, rdEnableFastTimeConstantTimeseries_);
                    WriteColumnValue( destination, rdFastTimeConstantLevelTimeseries_);
                    WriteColumnValue( destination, rdFastTimeConstantModeTimeseries_);
                    WriteColumnValue( destination, rdLatitudeTimeseries_);
                    WriteColumnValue( destination, rdLongitudeTimeseries_);
                    WriteColumnValue( destination, rdRadome_);
                    WriteColumnValue( destination, rdGNSSDevice_);
                }
                break;
                case Data::Kind::WeatherStationDevice:
                {
                    WriteColumnValue( destination, dHost_);
                    WriteColumnValue( destination, dName_);
                    WriteColumnValue( destination, dDescription_);
                    WriteColumnValue( destination, dEnabledTimeseries_);
                    WriteColumnValue( destination, wsdBarometricPressureTimeseries_);
                    WriteColumnValue( destination, wsdAirTemperatureTimeseries_);
                    WriteColumnValue( destination, wsdWaterTemperatureTimeseries_);
                    WriteColumnValue( destination, wsdRelativeHumidityTimeseries_);
                    WriteColumnValue( destination, wsdAbsoluteHumidityTimeseries_);
                    WriteColumnValue( destination, wsdDewPointTimeseries_);
                    WriteColumnValue( destination, wsdWindDirectionTimeseries_);
                    WriteColumnValue( destination, wsdWindSpeedTimeseries_);
                    WriteColumnValue( destination, wsdGyro_);
                }
                break;
                case Data::Kind::Facility:
                {
                    WriteColumnValue( destination, fName_);
                    WriteColumnValue( destination, fType_);
                    WriteColumnValue( destination, fLongitude_);
                    WriteColumnValue( destination, fLatitude_);
                    WriteColumnValue( destination, fAltitude_);
                }
                break;
                case Data::Kind::Aircraft:
                {
                    WriteColumnValue( destination, aName_);
                    WriteColumnValue( destination, aType_);
                }
                break;
                case Data::Kind::AisAidToNavigation:
                {
                    WriteColumnValue( destination, aatnName_);
                    WriteColumnValue( destination, aatnMMSI_);
                    WriteColumnValue( destination, aatnNavigationalAidType_);
                    WriteColumnValue( destination, aatnPosition_);
                    WriteColumnValue( destination, aatnIsVirtual_);
                    WriteColumnValue( destination, aatnToBow_);
                    WriteColumnValue( destination, aatnToStern_);
                    WriteColumnValue( destination, aatnToPort_);
                    WriteColumnValue( destination, aatnToStarboard_);
                    WriteColumnValue( destination, aatnOffPositionTimeseries_);
                }
                break;
                case Data::Kind::Vehicle:
                {
                    WriteColumnValue( destination, vName_);
                    WriteColumnValue( destination, vType_);
                }
                break;
                case Data::Kind::Vessel:
                {
                    WriteColumnValue( destination, vslName_);
                    WriteColumnValue( destination, vslType_);
                    WriteColumnValue( destination, vslToBow_);
                    WriteColumnValue( destination, vslToStern_);
                    WriteColumnValue( destination, vslToPort_);
                    WriteColumnValue( destination, vslToStarboard_);
                    WriteColumnValue( destination, vslDraughtTimeseries_);
                    WriteColumnValue( destination, vslPersonsOnBoardTimeseries_);
                }
                break;
            }
        }
    };

    using ComplexItemDataReader = SimpleColumnDataReader<ComplexItemColumnData>;

    class ComplexDeviceColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid host_;
        FixedDBWideString<127> name_;
        WideString description_;
        SQLLEN descriptionLength_ = SQL_NULL_DATA;
        Guid enabledTimeseries_;
        DBGuid gLatitudeTimeseries_;
        DBGuid gLongitudeTimeseries_;
        DBGuid gAltitudeTimeseries_;
        DBGuid gdHeadingTrueNorthTimeseries_;
        DBGuid gdHeadingMagneticNorthTimeseries_;
        DBGuid gdPitchTimeseries_;
        DBGuid gdRateOfTurnTimeseries_;
        DBGuid gdRollTimeseries_;
        DBGuid gdCourseTimeseries_;
        DBGuid gdSpeedTimeseries_;
        DBGuid gdGNSSDevice_;
        DBGuid rdoRadar_;
        DBGuid rdoPressureTimeseries_;
        DBGuid rdoTemperatureTimeseries_;
        DBGuid rdoDewPointTimeseries_;
        DBGuid rdoStatusTimeseries_;
        DBGuid rdSaveSettingsTimeseries_;
        DBGuid rdPowerOnTimeseries_;
        DBGuid rdTrackingOnTimeseries_;
        DBGuid rdRadarPulseTimeseries_;
        DBGuid rdTuningTimeseries_;
        DBGuid rdBlankSector1Timeseries_;
        DBGuid rdSector1StartTimeseries_;
        DBGuid rdSector1EndTimeseries_;
        DBGuid rdBlankSector2Timeseries_;
        DBGuid rdSector2StartTimeseries_;
        DBGuid rdSector2EndTimeseries_;
        DBGuid rdEnableAutomaticFrequencyControlTimeseries_;
        DBGuid rdAzimuthOffsetTimeseries_;
        DBGuid rdEnableSensitivityTimeControlTimeseries_;
        DBGuid rdAutomaticSensitivityTimeControlTimeseries_;
        DBGuid rdSensitivityTimeControlLevelTimeseries_;
        DBGuid rdEnableFastTimeConstantTimeseries_;
        DBGuid rdFastTimeConstantLevelTimeseries_;
        DBGuid rdFastTimeConstantModeTimeseries_;
        DBGuid rdLatitudeTimeseries_;
        DBGuid rdLongitudeTimeseries_;
        DBGuid rdRadome_;
        DBGuid rdGNSSDevice_;
        DBGuid wsdBarometricPressureTimeseries_;
        DBGuid wsdAirTemperatureTimeseries_;
        DBGuid wsdWaterTemperatureTimeseries_;
        DBGuid wsdRelativeHumidityTimeseries_;
        DBGuid wsdAbsoluteHumidityTimeseries_;
        DBGuid wsdDewPointTimeseries_;
        DBGuid wsdWindDirectionTimeseries_;
        DBGuid wsdWindSpeedTimeseries_;
        DBGuid wsdGyro_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT D_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT D_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT D_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT D_HOST_FIELD_ID = 4;
        static constexpr SQLUSMALLINT D_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT D_ENABLEDTIMESERIES_FIELD_ID = 6;
        static constexpr SQLUSMALLINT G_LATITUDETIMESERIES_FIELD_ID = 7;
        static constexpr SQLUSMALLINT G_LONGITUDETIMESERIES_FIELD_ID = 8;
        static constexpr SQLUSMALLINT G_ALTITUDETIMESERIES_FIELD_ID = 9;
        static constexpr SQLUSMALLINT GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID = 10;
        static constexpr SQLUSMALLINT GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID = 11;
        static constexpr SQLUSMALLINT GD_PITCHTIMESERIES_FIELD_ID = 12;
        static constexpr SQLUSMALLINT GD_RATEOFTURNTIMESERIES_FIELD_ID = 13;
        static constexpr SQLUSMALLINT GD_ROLLTIMESERIES_FIELD_ID = 14;
        static constexpr SQLUSMALLINT GD_COURSETIMESERIES_FIELD_ID = 15;
        static constexpr SQLUSMALLINT GD_SPEEDTIMESERIES_FIELD_ID = 16;
        static constexpr SQLUSMALLINT GD_GNSSDEVICE_FIELD_ID = 17;
        static constexpr SQLUSMALLINT RDO_RADAR_FIELD_ID = 18;
        static constexpr SQLUSMALLINT RDO_PRESSURETIMESERIES_FIELD_ID = 19;
        static constexpr SQLUSMALLINT RDO_TEMPERATURETIMESERIES_FIELD_ID = 20;
        static constexpr SQLUSMALLINT RDO_DEWPOINTTIMESERIES_FIELD_ID = 21;
        static constexpr SQLUSMALLINT RDO_STATUSTIMESERIES_FIELD_ID = 22;
        static constexpr SQLUSMALLINT RD_SAVESETTINGSTIMESERIES_FIELD_ID = 23;
        static constexpr SQLUSMALLINT RD_POWERONTIMESERIES_FIELD_ID = 24;
        static constexpr SQLUSMALLINT RD_TRACKINGONTIMESERIES_FIELD_ID = 25;
        static constexpr SQLUSMALLINT RD_RADARPULSETIMESERIES_FIELD_ID = 26;
        static constexpr SQLUSMALLINT RD_TUNINGTIMESERIES_FIELD_ID = 27;
        static constexpr SQLUSMALLINT RD_BLANKSECTOR1TIMESERIES_FIELD_ID = 28;
        static constexpr SQLUSMALLINT RD_SECTOR1STARTTIMESERIES_FIELD_ID = 29;
        static constexpr SQLUSMALLINT RD_SECTOR1ENDTIMESERIES_FIELD_ID = 30;
        static constexpr SQLUSMALLINT RD_BLANKSECTOR2TIMESERIES_FIELD_ID = 31;
        static constexpr SQLUSMALLINT RD_SECTOR2STARTTIMESERIES_FIELD_ID = 32;
        static constexpr SQLUSMALLINT RD_SECTOR2ENDTIMESERIES_FIELD_ID = 33;
        static constexpr SQLUSMALLINT RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 34;
        static constexpr SQLUSMALLINT RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID = 35;
        static constexpr SQLUSMALLINT RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 36;
        static constexpr SQLUSMALLINT RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 37;
        static constexpr SQLUSMALLINT RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 38;
        static constexpr SQLUSMALLINT RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 39;
        static constexpr SQLUSMALLINT RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 40;
        static constexpr SQLUSMALLINT RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 41;
        static constexpr SQLUSMALLINT RD_LATITUDETIMESERIES_FIELD_ID = 42;
        static constexpr SQLUSMALLINT RD_LONGITUDETIMESERIES_FIELD_ID = 43;
        static constexpr SQLUSMALLINT RD_RADOME_FIELD_ID = 44;
        static constexpr SQLUSMALLINT RD_GNSSDEVICE_FIELD_ID = 45;
        static constexpr SQLUSMALLINT WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID = 46;
        static constexpr SQLUSMALLINT WSD_AIRTEMPERATURETIMESERIES_FIELD_ID = 47;
        static constexpr SQLUSMALLINT WSD_WATERTEMPERATURETIMESERIES_FIELD_ID = 48;
        static constexpr SQLUSMALLINT WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID = 49;
        static constexpr SQLUSMALLINT WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID = 50;
        static constexpr SQLUSMALLINT WSD_DEWPOINTTIMESERIES_FIELD_ID = 51;
        static constexpr SQLUSMALLINT WSD_WINDDIRECTIONTIMESERIES_FIELD_ID = 52;
        static constexpr SQLUSMALLINT WSD_WINDSPEEDTIMESERIES_FIELD_ID = 53;
        static constexpr SQLUSMALLINT WSD_GYRO_FIELD_ID = 54;
        static constexpr SQLUSMALLINT D_DESCRIPTION_FIELD_ID = 55;

        ComplexDeviceColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Host( ) const
        {
            return host_;
        }
        const FixedDBWideString<127>& Name( ) const
        {
            return name_;
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        const Guid& EnabledTimeseries( ) const
        {
            return enabledTimeseries_;
        }
        const DBGuid& GNSSDeviceLatitudeTimeseries( ) const
        {
            return gLatitudeTimeseries_;
        }
        const DBGuid& GNSSDeviceLongitudeTimeseries( ) const
        {
            return gLongitudeTimeseries_;
        }
        const DBGuid& GNSSDeviceAltitudeTimeseries( ) const
        {
            return gAltitudeTimeseries_;
        }
        const DBGuid& GyroDeviceHeadingTrueNorthTimeseries( ) const
        {
            return gdHeadingTrueNorthTimeseries_;
        }
        const DBGuid& GyroDeviceHeadingMagneticNorthTimeseries( ) const
        {
            return gdHeadingMagneticNorthTimeseries_;
        }
        const DBGuid& GyroDevicePitchTimeseries( ) const
        {
            return gdPitchTimeseries_;
        }
        const DBGuid& GyroDeviceRateOfTurnTimeseries( ) const
        {
            return gdRateOfTurnTimeseries_;
        }
        const DBGuid& GyroDeviceRollTimeseries( ) const
        {
            return gdRollTimeseries_;
        }
        const DBGuid& GyroDeviceCourseTimeseries( ) const
        {
            return gdCourseTimeseries_;
        }
        const DBGuid& GyroDeviceSpeedTimeseries( ) const
        {
            return gdSpeedTimeseries_;
        }
        const DBGuid& GyroDeviceGNSSDevice( ) const
        {
            return gdGNSSDevice_;
        }
        const DBGuid& RadomeDeviceRadar( ) const
        {
            return rdoRadar_;
        }
        const DBGuid& RadomeDevicePressureTimeseries( ) const
        {
            return rdoPressureTimeseries_;
        }
        const DBGuid& RadomeDeviceTemperatureTimeseries( ) const
        {
            return rdoTemperatureTimeseries_;
        }
        const DBGuid& RadomeDeviceDewPointTimeseries( ) const
        {
            return rdoDewPointTimeseries_;
        }
        const DBGuid& RadomeDeviceStatusTimeseries( ) const
        {
            return rdoStatusTimeseries_;
        }
        const DBGuid& RadarDeviceSaveSettingsTimeseries( ) const
        {
            return rdSaveSettingsTimeseries_;
        }
        const DBGuid& RadarDevicePowerOnTimeseries( ) const
        {
            return rdPowerOnTimeseries_;
        }
        const DBGuid& RadarDeviceTrackingOnTimeseries( ) const
        {
            return rdTrackingOnTimeseries_;
        }
        const DBGuid& RadarDeviceRadarPulseTimeseries( ) const
        {
            return rdRadarPulseTimeseries_;
        }
        const DBGuid& RadarDeviceTuningTimeseries( ) const
        {
            return rdTuningTimeseries_;
        }
        const DBGuid& RadarDeviceBlankSector1Timeseries( ) const
        {
            return rdBlankSector1Timeseries_;
        }
        const DBGuid& RadarDeviceSector1StartTimeseries( ) const
        {
            return rdSector1StartTimeseries_;
        }
        const DBGuid& RadarDeviceSector1EndTimeseries( ) const
        {
            return rdSector1EndTimeseries_;
        }
        const DBGuid& RadarDeviceBlankSector2Timeseries( ) const
        {
            return rdBlankSector2Timeseries_;
        }
        const DBGuid& RadarDeviceSector2StartTimeseries( ) const
        {
            return rdSector2StartTimeseries_;
        }
        const DBGuid& RadarDeviceSector2EndTimeseries( ) const
        {
            return rdSector2EndTimeseries_;
        }
        const DBGuid& RadarDeviceEnableAutomaticFrequencyControlTimeseries( ) const
        {
            return rdEnableAutomaticFrequencyControlTimeseries_;
        }
        const DBGuid& RadarDeviceAzimuthOffsetTimeseries( ) const
        {
            return rdAzimuthOffsetTimeseries_;
        }
        const DBGuid& RadarDeviceEnableSensitivityTimeControlTimeseries( ) const
        {
            return rdEnableSensitivityTimeControlTimeseries_;
        }
        const DBGuid& RadarDeviceAutomaticSensitivityTimeControlTimeseries( ) const
        {
            return rdAutomaticSensitivityTimeControlTimeseries_;
        }
        const DBGuid& RadarDeviceSensitivityTimeControlLevelTimeseries( ) const
        {
            return rdSensitivityTimeControlLevelTimeseries_;
        }
        const DBGuid& RadarDeviceEnableFastTimeConstantTimeseries( ) const
        {
            return rdEnableFastTimeConstantTimeseries_;
        }
        const DBGuid& RadarDeviceFastTimeConstantLevelTimeseries( ) const
        {
            return rdFastTimeConstantLevelTimeseries_;
        }
        const DBGuid& RadarDeviceFastTimeConstantModeTimeseries( ) const
        {
            return rdFastTimeConstantModeTimeseries_;
        }
        const DBGuid& RadarDeviceLatitudeTimeseries( ) const
        {
            return rdLatitudeTimeseries_;
        }
        const DBGuid& RadarDeviceLongitudeTimeseries( ) const
        {
            return rdLongitudeTimeseries_;
        }
        const DBGuid& RadarDeviceRadome( ) const
        {
            return rdRadome_;
        }
        const DBGuid& RadarDeviceGNSSDevice( ) const
        {
            return rdGNSSDevice_;
        }
        const DBGuid& WeatherStationDeviceBarometricPressureTimeseries( ) const
        {
            return wsdBarometricPressureTimeseries_;
        }
        const DBGuid& WeatherStationDeviceAirTemperatureTimeseries( ) const
        {
            return wsdAirTemperatureTimeseries_;
        }
        const DBGuid& WeatherStationDeviceWaterTemperatureTimeseries( ) const
        {
            return wsdWaterTemperatureTimeseries_;
        }
        const DBGuid& WeatherStationDeviceRelativeHumidityTimeseries( ) const
        {
            return wsdRelativeHumidityTimeseries_;
        }
        const DBGuid& WeatherStationDeviceAbsoluteHumidityTimeseries( ) const
        {
            return wsdAbsoluteHumidityTimeseries_;
        }
        const DBGuid& WeatherStationDeviceDewPointTimeseries( ) const
        {
            return wsdDewPointTimeseries_;
        }
        const DBGuid& WeatherStationDeviceWindDirectionTimeseries( ) const
        {
            return wsdWindDirectionTimeseries_;
        }
        const DBGuid& WeatherStationDeviceWindSpeedTimeseries( ) const
        {
            return wsdWindSpeedTimeseries_;
        }
        const DBGuid& WeatherStationDeviceGyro( ) const
        {
            return wsdGyro_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, host_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, description_);
            WriteColumnValue( destination, enabledTimeseries_);
            switch( kind_ )
            {
                case Data::Kind::GNSSDevice:
                {
                    WriteColumnValue( destination, gLatitudeTimeseries_);
                    WriteColumnValue( destination, gLongitudeTimeseries_);
                    WriteColumnValue( destination, gAltitudeTimeseries_);
                }
                break;
                case Data::Kind::GyroDevice:
                {
                    WriteColumnValue( destination, gdHeadingTrueNorthTimeseries_);
                    WriteColumnValue( destination, gdHeadingMagneticNorthTimeseries_);
                    WriteColumnValue( destination, gdPitchTimeseries_);
                    WriteColumnValue( destination, gdRateOfTurnTimeseries_);
                    WriteColumnValue( destination, gdRollTimeseries_);
                    WriteColumnValue( destination, gdCourseTimeseries_);
                    WriteColumnValue( destination, gdSpeedTimeseries_);
                    WriteColumnValue( destination, gdGNSSDevice_);
                }
                break;
                case Data::Kind::RadomeDevice:
                {
                    WriteColumnValue( destination, rdoRadar_);
                    WriteColumnValue( destination, rdoPressureTimeseries_);
                    WriteColumnValue( destination, rdoTemperatureTimeseries_);
                    WriteColumnValue( destination, rdoDewPointTimeseries_);
                    WriteColumnValue( destination, rdoStatusTimeseries_);
                }
                break;
                case Data::Kind::RadarDevice:
                {
                    WriteColumnValue( destination, rdSaveSettingsTimeseries_);
                    WriteColumnValue( destination, rdPowerOnTimeseries_);
                    WriteColumnValue( destination, rdTrackingOnTimeseries_);
                    WriteColumnValue( destination, rdRadarPulseTimeseries_);
                    WriteColumnValue( destination, rdTuningTimeseries_);
                    WriteColumnValue( destination, rdBlankSector1Timeseries_);
                    WriteColumnValue( destination, rdSector1StartTimeseries_);
                    WriteColumnValue( destination, rdSector1EndTimeseries_);
                    WriteColumnValue( destination, rdBlankSector2Timeseries_);
                    WriteColumnValue( destination, rdSector2StartTimeseries_);
                    WriteColumnValue( destination, rdSector2EndTimeseries_);
                    WriteColumnValue( destination, rdEnableAutomaticFrequencyControlTimeseries_);
                    WriteColumnValue( destination, rdAzimuthOffsetTimeseries_);
                    WriteColumnValue( destination, rdEnableSensitivityTimeControlTimeseries_);
                    WriteColumnValue( destination, rdAutomaticSensitivityTimeControlTimeseries_);
                    WriteColumnValue( destination, rdSensitivityTimeControlLevelTimeseries_);
                    WriteColumnValue( destination, rdEnableFastTimeConstantTimeseries_);
                    WriteColumnValue( destination, rdFastTimeConstantLevelTimeseries_);
                    WriteColumnValue( destination, rdFastTimeConstantModeTimeseries_);
                    WriteColumnValue( destination, rdLatitudeTimeseries_);
                    WriteColumnValue( destination, rdLongitudeTimeseries_);
                    WriteColumnValue( destination, rdRadome_);
                    WriteColumnValue( destination, rdGNSSDevice_);
                }
                break;
                case Data::Kind::WeatherStationDevice:
                {
                    WriteColumnValue( destination, wsdBarometricPressureTimeseries_);
                    WriteColumnValue( destination, wsdAirTemperatureTimeseries_);
                    WriteColumnValue( destination, wsdWaterTemperatureTimeseries_);
                    WriteColumnValue( destination, wsdRelativeHumidityTimeseries_);
                    WriteColumnValue( destination, wsdAbsoluteHumidityTimeseries_);
                    WriteColumnValue( destination, wsdDewPointTimeseries_);
                    WriteColumnValue( destination, wsdWindDirectionTimeseries_);
                    WriteColumnValue( destination, wsdWindSpeedTimeseries_);
                    WriteColumnValue( destination, wsdGyro_);
                }
                break;
            }
        }
    };

    using ComplexDeviceDataReader = SimpleColumnDataReader<ComplexDeviceColumnData>;

    class ComplexTrackerDeviceColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid host_;
        FixedDBWideString<127> name_;
        WideString description_;
        SQLLEN descriptionLength_ = SQL_NULL_DATA;
        Guid enabledTimeseries_;
        DBGuid rdSaveSettingsTimeseries_;
        DBGuid rdPowerOnTimeseries_;
        DBGuid rdTrackingOnTimeseries_;
        DBGuid rdRadarPulseTimeseries_;
        DBGuid rdTuningTimeseries_;
        DBGuid rdBlankSector1Timeseries_;
        DBGuid rdSector1StartTimeseries_;
        DBGuid rdSector1EndTimeseries_;
        DBGuid rdBlankSector2Timeseries_;
        DBGuid rdSector2StartTimeseries_;
        DBGuid rdSector2EndTimeseries_;
        DBGuid rdEnableAutomaticFrequencyControlTimeseries_;
        DBGuid rdAzimuthOffsetTimeseries_;
        DBGuid rdEnableSensitivityTimeControlTimeseries_;
        DBGuid rdAutomaticSensitivityTimeControlTimeseries_;
        DBGuid rdSensitivityTimeControlLevelTimeseries_;
        DBGuid rdEnableFastTimeConstantTimeseries_;
        DBGuid rdFastTimeConstantLevelTimeseries_;
        DBGuid rdFastTimeConstantModeTimeseries_;
        DBGuid rdLatitudeTimeseries_;
        DBGuid rdLongitudeTimeseries_;
        DBGuid rdRadome_;
        DBGuid rdGNSSDevice_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT TD_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TD_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TD_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TD_HOST_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TD_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT TD_ENABLEDTIMESERIES_FIELD_ID = 6;
        static constexpr SQLUSMALLINT RD_SAVESETTINGSTIMESERIES_FIELD_ID = 7;
        static constexpr SQLUSMALLINT RD_POWERONTIMESERIES_FIELD_ID = 8;
        static constexpr SQLUSMALLINT RD_TRACKINGONTIMESERIES_FIELD_ID = 9;
        static constexpr SQLUSMALLINT RD_RADARPULSETIMESERIES_FIELD_ID = 10;
        static constexpr SQLUSMALLINT RD_TUNINGTIMESERIES_FIELD_ID = 11;
        static constexpr SQLUSMALLINT RD_BLANKSECTOR1TIMESERIES_FIELD_ID = 12;
        static constexpr SQLUSMALLINT RD_SECTOR1STARTTIMESERIES_FIELD_ID = 13;
        static constexpr SQLUSMALLINT RD_SECTOR1ENDTIMESERIES_FIELD_ID = 14;
        static constexpr SQLUSMALLINT RD_BLANKSECTOR2TIMESERIES_FIELD_ID = 15;
        static constexpr SQLUSMALLINT RD_SECTOR2STARTTIMESERIES_FIELD_ID = 16;
        static constexpr SQLUSMALLINT RD_SECTOR2ENDTIMESERIES_FIELD_ID = 17;
        static constexpr SQLUSMALLINT RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 18;
        static constexpr SQLUSMALLINT RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID = 19;
        static constexpr SQLUSMALLINT RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 20;
        static constexpr SQLUSMALLINT RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 21;
        static constexpr SQLUSMALLINT RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 22;
        static constexpr SQLUSMALLINT RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 23;
        static constexpr SQLUSMALLINT RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 24;
        static constexpr SQLUSMALLINT RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 25;
        static constexpr SQLUSMALLINT RD_LATITUDETIMESERIES_FIELD_ID = 26;
        static constexpr SQLUSMALLINT RD_LONGITUDETIMESERIES_FIELD_ID = 27;
        static constexpr SQLUSMALLINT RD_RADOME_FIELD_ID = 28;
        static constexpr SQLUSMALLINT RD_GNSSDEVICE_FIELD_ID = 29;
        static constexpr SQLUSMALLINT TD_DESCRIPTION_FIELD_ID = 30;

        ComplexTrackerDeviceColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Host( ) const
        {
            return host_;
        }
        const FixedDBWideString<127>& Name( ) const
        {
            return name_;
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        const Guid& EnabledTimeseries( ) const
        {
            return enabledTimeseries_;
        }
        const DBGuid& RadarDeviceSaveSettingsTimeseries( ) const
        {
            return rdSaveSettingsTimeseries_;
        }
        const DBGuid& RadarDevicePowerOnTimeseries( ) const
        {
            return rdPowerOnTimeseries_;
        }
        const DBGuid& RadarDeviceTrackingOnTimeseries( ) const
        {
            return rdTrackingOnTimeseries_;
        }
        const DBGuid& RadarDeviceRadarPulseTimeseries( ) const
        {
            return rdRadarPulseTimeseries_;
        }
        const DBGuid& RadarDeviceTuningTimeseries( ) const
        {
            return rdTuningTimeseries_;
        }
        const DBGuid& RadarDeviceBlankSector1Timeseries( ) const
        {
            return rdBlankSector1Timeseries_;
        }
        const DBGuid& RadarDeviceSector1StartTimeseries( ) const
        {
            return rdSector1StartTimeseries_;
        }
        const DBGuid& RadarDeviceSector1EndTimeseries( ) const
        {
            return rdSector1EndTimeseries_;
        }
        const DBGuid& RadarDeviceBlankSector2Timeseries( ) const
        {
            return rdBlankSector2Timeseries_;
        }
        const DBGuid& RadarDeviceSector2StartTimeseries( ) const
        {
            return rdSector2StartTimeseries_;
        }
        const DBGuid& RadarDeviceSector2EndTimeseries( ) const
        {
            return rdSector2EndTimeseries_;
        }
        const DBGuid& RadarDeviceEnableAutomaticFrequencyControlTimeseries( ) const
        {
            return rdEnableAutomaticFrequencyControlTimeseries_;
        }
        const DBGuid& RadarDeviceAzimuthOffsetTimeseries( ) const
        {
            return rdAzimuthOffsetTimeseries_;
        }
        const DBGuid& RadarDeviceEnableSensitivityTimeControlTimeseries( ) const
        {
            return rdEnableSensitivityTimeControlTimeseries_;
        }
        const DBGuid& RadarDeviceAutomaticSensitivityTimeControlTimeseries( ) const
        {
            return rdAutomaticSensitivityTimeControlTimeseries_;
        }
        const DBGuid& RadarDeviceSensitivityTimeControlLevelTimeseries( ) const
        {
            return rdSensitivityTimeControlLevelTimeseries_;
        }
        const DBGuid& RadarDeviceEnableFastTimeConstantTimeseries( ) const
        {
            return rdEnableFastTimeConstantTimeseries_;
        }
        const DBGuid& RadarDeviceFastTimeConstantLevelTimeseries( ) const
        {
            return rdFastTimeConstantLevelTimeseries_;
        }
        const DBGuid& RadarDeviceFastTimeConstantModeTimeseries( ) const
        {
            return rdFastTimeConstantModeTimeseries_;
        }
        const DBGuid& RadarDeviceLatitudeTimeseries( ) const
        {
            return rdLatitudeTimeseries_;
        }
        const DBGuid& RadarDeviceLongitudeTimeseries( ) const
        {
            return rdLongitudeTimeseries_;
        }
        const DBGuid& RadarDeviceRadome( ) const
        {
            return rdRadome_;
        }
        const DBGuid& RadarDeviceGNSSDevice( ) const
        {
            return rdGNSSDevice_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, host_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, description_);
            WriteColumnValue( destination, enabledTimeseries_);
            switch( kind_ )
            {
                case Data::Kind::RadarDevice:
                {
                    WriteColumnValue( destination, rdSaveSettingsTimeseries_);
                    WriteColumnValue( destination, rdPowerOnTimeseries_);
                    WriteColumnValue( destination, rdTrackingOnTimeseries_);
                    WriteColumnValue( destination, rdRadarPulseTimeseries_);
                    WriteColumnValue( destination, rdTuningTimeseries_);
                    WriteColumnValue( destination, rdBlankSector1Timeseries_);
                    WriteColumnValue( destination, rdSector1StartTimeseries_);
                    WriteColumnValue( destination, rdSector1EndTimeseries_);
                    WriteColumnValue( destination, rdBlankSector2Timeseries_);
                    WriteColumnValue( destination, rdSector2StartTimeseries_);
                    WriteColumnValue( destination, rdSector2EndTimeseries_);
                    WriteColumnValue( destination, rdEnableAutomaticFrequencyControlTimeseries_);
                    WriteColumnValue( destination, rdAzimuthOffsetTimeseries_);
                    WriteColumnValue( destination, rdEnableSensitivityTimeControlTimeseries_);
                    WriteColumnValue( destination, rdAutomaticSensitivityTimeControlTimeseries_);
                    WriteColumnValue( destination, rdSensitivityTimeControlLevelTimeseries_);
                    WriteColumnValue( destination, rdEnableFastTimeConstantTimeseries_);
                    WriteColumnValue( destination, rdFastTimeConstantLevelTimeseries_);
                    WriteColumnValue( destination, rdFastTimeConstantModeTimeseries_);
                    WriteColumnValue( destination, rdLatitudeTimeseries_);
                    WriteColumnValue( destination, rdLongitudeTimeseries_);
                    WriteColumnValue( destination, rdRadome_);
                    WriteColumnValue( destination, rdGNSSDevice_);
                }
                break;
            }
        }
    };

    using ComplexTrackerDeviceDataReader = SimpleColumnDataReader<ComplexTrackerDeviceColumnData>;

    class ComplexTrackableItemColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        FixedDBWideString<127> aName_;
        DBGuid aType_;
        FixedDBWideString<127> aatnName_;
        DBGuid aatnMMSI_;
        DBEnum<Data::NavigationalAidType> aatnNavigationalAidType_;
        DBGuid aatnPosition_;
        DBBoolean aatnIsVirtual_;
        DBInt32 aatnToBow_;
        DBInt32 aatnToStern_;
        DBInt32 aatnToPort_;
        DBInt32 aatnToStarboard_;
        DBGuid aatnOffPositionTimeseries_;
        FixedDBWideString<127> vName_;
        DBGuid vType_;
        FixedDBWideString<127> vslName_;
        DBGuid vslType_;
        DBInt32 vslToBow_;
        DBInt32 vslToStern_;
        DBInt32 vslToPort_;
        DBInt32 vslToStarboard_;
        DBGuid vslDraughtTimeseries_;
        DBGuid vslPersonsOnBoardTimeseries_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT TI_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TI_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TI_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT A_NAME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT A_TYPE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT AATN_NAME_FIELD_ID = 6;
        static constexpr SQLUSMALLINT AATN_MMSI_FIELD_ID = 7;
        static constexpr SQLUSMALLINT AATN_NAVIGATIONALAIDTYPE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT AATN_POSITION_FIELD_ID = 9;
        static constexpr SQLUSMALLINT AATN_ISVIRTUAL_FIELD_ID = 10;
        static constexpr SQLUSMALLINT AATN_TOBOW_FIELD_ID = 11;
        static constexpr SQLUSMALLINT AATN_TOSTERN_FIELD_ID = 12;
        static constexpr SQLUSMALLINT AATN_TOPORT_FIELD_ID = 13;
        static constexpr SQLUSMALLINT AATN_TOSTARBOARD_FIELD_ID = 14;
        static constexpr SQLUSMALLINT AATN_OFFPOSITIONTIMESERIES_FIELD_ID = 15;
        static constexpr SQLUSMALLINT V_NAME_FIELD_ID = 16;
        static constexpr SQLUSMALLINT V_TYPE_FIELD_ID = 17;
        static constexpr SQLUSMALLINT VSL_NAME_FIELD_ID = 18;
        static constexpr SQLUSMALLINT VSL_TYPE_FIELD_ID = 19;
        static constexpr SQLUSMALLINT VSL_TOBOW_FIELD_ID = 20;
        static constexpr SQLUSMALLINT VSL_TOSTERN_FIELD_ID = 21;
        static constexpr SQLUSMALLINT VSL_TOPORT_FIELD_ID = 22;
        static constexpr SQLUSMALLINT VSL_TOSTARBOARD_FIELD_ID = 23;
        static constexpr SQLUSMALLINT VSL_DRAUGHTTIMESERIES_FIELD_ID = 24;
        static constexpr SQLUSMALLINT VSL_PERSONSONBOARDTIMESERIES_FIELD_ID = 25;

        ComplexTrackableItemColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const FixedDBWideString<127>& AircraftName( ) const
        {
            return aName_;
        }
        const DBGuid& AircraftType( ) const
        {
            return aType_;
        }
        const FixedDBWideString<127>& AisAidToNavigationName( ) const
        {
            return aatnName_;
        }
        const DBGuid& AisAidToNavigationMMSI( ) const
        {
            return aatnMMSI_;
        }
        DBEnum<Data::NavigationalAidType> AisAidToNavigationNavigationalAidType( ) const
        {
            return aatnNavigationalAidType_;
        }
        const DBGuid& AisAidToNavigationPosition( ) const
        {
            return aatnPosition_;
        }
        DBBoolean AisAidToNavigationIsVirtual( ) const
        {
            return aatnIsVirtual_;
        }
        DBInt32 AisAidToNavigationToBow( ) const
        {
            return aatnToBow_;
        }
        DBInt32 AisAidToNavigationToStern( ) const
        {
            return aatnToStern_;
        }
        DBInt32 AisAidToNavigationToPort( ) const
        {
            return aatnToPort_;
        }
        DBInt32 AisAidToNavigationToStarboard( ) const
        {
            return aatnToStarboard_;
        }
        const DBGuid& AisAidToNavigationOffPositionTimeseries( ) const
        {
            return aatnOffPositionTimeseries_;
        }
        const FixedDBWideString<127>& VehicleName( ) const
        {
            return vName_;
        }
        const DBGuid& VehicleType( ) const
        {
            return vType_;
        }
        const FixedDBWideString<127>& VesselName( ) const
        {
            return vslName_;
        }
        const DBGuid& VesselType( ) const
        {
            return vslType_;
        }
        DBInt32 VesselToBow( ) const
        {
            return vslToBow_;
        }
        DBInt32 VesselToStern( ) const
        {
            return vslToStern_;
        }
        DBInt32 VesselToPort( ) const
        {
            return vslToPort_;
        }
        DBInt32 VesselToStarboard( ) const
        {
            return vslToStarboard_;
        }
        const DBGuid& VesselDraughtTimeseries( ) const
        {
            return vslDraughtTimeseries_;
        }
        const DBGuid& VesselPersonsOnBoardTimeseries( ) const
        {
            return vslPersonsOnBoardTimeseries_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            switch( kind_ )
            {
                case Data::Kind::Aircraft:
                {
                    WriteColumnValue( destination, aName_);
                    WriteColumnValue( destination, aType_);
                }
                break;
                case Data::Kind::AisAidToNavigation:
                {
                    WriteColumnValue( destination, aatnName_);
                    WriteColumnValue( destination, aatnMMSI_);
                    WriteColumnValue( destination, aatnNavigationalAidType_);
                    WriteColumnValue( destination, aatnPosition_);
                    WriteColumnValue( destination, aatnIsVirtual_);
                    WriteColumnValue( destination, aatnToBow_);
                    WriteColumnValue( destination, aatnToStern_);
                    WriteColumnValue( destination, aatnToPort_);
                    WriteColumnValue( destination, aatnToStarboard_);
                    WriteColumnValue( destination, aatnOffPositionTimeseries_);
                }
                break;
                case Data::Kind::Vehicle:
                {
                    WriteColumnValue( destination, vName_);
                    WriteColumnValue( destination, vType_);
                }
                break;
                case Data::Kind::Vessel:
                {
                    WriteColumnValue( destination, vslName_);
                    WriteColumnValue( destination, vslType_);
                    WriteColumnValue( destination, vslToBow_);
                    WriteColumnValue( destination, vslToStern_);
                    WriteColumnValue( destination, vslToPort_);
                    WriteColumnValue( destination, vslToStarboard_);
                    WriteColumnValue( destination, vslDraughtTimeseries_);
                    WriteColumnValue( destination, vslPersonsOnBoardTimeseries_);
                }
                break;
            }
        }
    };

    using ComplexTrackableItemDataReader = SimpleColumnDataReader<ComplexTrackableItemColumnData>;

    class ComplexNamespaceElementColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid namespace_;
        FixedDBWideString<127> name_;
        WideString description_;
        SQLLEN descriptionLength_ = SQL_NULL_DATA;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT NE_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT NE_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT NE_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT NE_NAMESPACE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT NE_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT NE_DESCRIPTION_FIELD_ID = 6;

        ComplexNamespaceElementColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Namespace( ) const
        {
            return namespace_;
        }
        const FixedDBWideString<127>& Name( ) const
        {
            return name_;
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, namespace_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, description_);
        }
    };

    using ComplexNamespaceElementDataReader = SimpleColumnDataReader<ComplexNamespaceElementColumnData>;

    class ComplexPropertyColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid element_;
        Guid definition_;
        DBBinary bpValue_;
        DBBoolean bopValue_;
        DBByte bypValue_;
        DBDateTime dtpValue_;
        DBDouble dpValue_;
        DBGuid gpValue_;
        DBInt16 i16pValue_;
        DBInt32 i32pValue_;
        DBInt64 i64pValue_;
        DBGuid rpValue_;
        DBSByte spValue_;
        DBSingle sipValue_;
        FixedDBWideString<100> stpValue_;
        DBGuid btpTimeseries_;
        DBGuid botpTimeseries_;
        DBGuid bytpTimeseries_;
        DBGuid dttpTimeseries_;
        DBGuid dotpTimeseries_;
        DBGuid gtpTimeseries_;
        DBGuid i16tpTimeseries_;
        DBGuid i32tpTimeseries_;
        DBGuid i64tpTimeseries_;
        DBGuid rtpTimeseries_;
        DBGuid sbtpTimeseries_;
        DBGuid sitpTimeseries_;
        DBGuid sttpTimeseries_;
        DBGuid tstpTimeseries_;
        DBGuid u16tpTimeseries_;
        DBGuid u32tpTimeseries_;
        DBGuid u64tpTimeseries_;
        DBTimeSpan tspValue_;
        DBUInt16 u16pValue_;
        DBUInt32 u32pValue_;
        DBInt64 u64pValue_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT P_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT P_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT P_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT P_ELEMENT_FIELD_ID = 4;
        static constexpr SQLUSMALLINT P_DEFINITION_FIELD_ID = 5;
        static constexpr SQLUSMALLINT BOP_VALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT BYP_VALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT DTP_VALUE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT DP_VALUE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT GP_VALUE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT I16P_VALUE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT I32P_VALUE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT I64P_VALUE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT RP_VALUE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT SP_VALUE_FIELD_ID = 15;
        static constexpr SQLUSMALLINT SIP_VALUE_FIELD_ID = 16;
        static constexpr SQLUSMALLINT STP_VALUE_FIELD_ID = 17;
        static constexpr SQLUSMALLINT BTP_TIMESERIES_FIELD_ID = 18;
        static constexpr SQLUSMALLINT BOTP_TIMESERIES_FIELD_ID = 19;
        static constexpr SQLUSMALLINT BYTP_TIMESERIES_FIELD_ID = 20;
        static constexpr SQLUSMALLINT DTTP_TIMESERIES_FIELD_ID = 21;
        static constexpr SQLUSMALLINT DOTP_TIMESERIES_FIELD_ID = 22;
        static constexpr SQLUSMALLINT GTP_TIMESERIES_FIELD_ID = 23;
        static constexpr SQLUSMALLINT I16TP_TIMESERIES_FIELD_ID = 24;
        static constexpr SQLUSMALLINT I32TP_TIMESERIES_FIELD_ID = 25;
        static constexpr SQLUSMALLINT I64TP_TIMESERIES_FIELD_ID = 26;
        static constexpr SQLUSMALLINT RTP_TIMESERIES_FIELD_ID = 27;
        static constexpr SQLUSMALLINT SBTP_TIMESERIES_FIELD_ID = 28;
        static constexpr SQLUSMALLINT SITP_TIMESERIES_FIELD_ID = 29;
        static constexpr SQLUSMALLINT STTP_TIMESERIES_FIELD_ID = 30;
        static constexpr SQLUSMALLINT TSTP_TIMESERIES_FIELD_ID = 31;
        static constexpr SQLUSMALLINT U16TP_TIMESERIES_FIELD_ID = 32;
        static constexpr SQLUSMALLINT U32TP_TIMESERIES_FIELD_ID = 33;
        static constexpr SQLUSMALLINT U64TP_TIMESERIES_FIELD_ID = 34;
        static constexpr SQLUSMALLINT TSP_VALUE_FIELD_ID = 35;
        static constexpr SQLUSMALLINT U16P_VALUE_FIELD_ID = 36;
        static constexpr SQLUSMALLINT U32P_VALUE_FIELD_ID = 37;
        static constexpr SQLUSMALLINT U64P_VALUE_FIELD_ID = 38;
        static constexpr SQLUSMALLINT BP_VALUE_FIELD_ID = 39;

        ComplexPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Element( ) const
        {
            return element_;
        }
        const Guid& Definition( ) const
        {
            return definition_;
        }
        const DBBinary& BinaryPropertyValue( ) const
        {
            return bpValue_;
        }
        DBBoolean BooleanPropertyValue( ) const
        {
            return bopValue_;
        }
        DBByte BytePropertyValue( ) const
        {
            return bypValue_;
        }
        const DBDateTime& DateTimePropertyValue( ) const
        {
            return dtpValue_;
        }
        DBDouble DoublePropertyValue( ) const
        {
            return dpValue_;
        }
        const DBGuid& GuidPropertyValue( ) const
        {
            return gpValue_;
        }
        DBInt16 Int16PropertyValue( ) const
        {
            return i16pValue_;
        }
        DBInt32 Int32PropertyValue( ) const
        {
            return i32pValue_;
        }
        DBInt64 Int64PropertyValue( ) const
        {
            return i64pValue_;
        }
        const DBGuid& ReferencePropertyValue( ) const
        {
            return rpValue_;
        }
        DBSByte SBytePropertyValue( ) const
        {
            return spValue_;
        }
        DBSingle SinglePropertyValue( ) const
        {
            return sipValue_;
        }
        const FixedDBWideString<100>& StringPropertyValue( ) const
        {
            return stpValue_;
        }
        const DBGuid& BinaryTimeseriesPropertyTimeseries( ) const
        {
            return btpTimeseries_;
        }
        const DBGuid& BooleanTimeseriesPropertyTimeseries( ) const
        {
            return botpTimeseries_;
        }
        const DBGuid& ByteTimeseriesPropertyTimeseries( ) const
        {
            return bytpTimeseries_;
        }
        const DBGuid& DateTimeTimeseriesPropertyTimeseries( ) const
        {
            return dttpTimeseries_;
        }
        const DBGuid& DoubleTimeseriesPropertyTimeseries( ) const
        {
            return dotpTimeseries_;
        }
        const DBGuid& GuidTimeseriesPropertyTimeseries( ) const
        {
            return gtpTimeseries_;
        }
        const DBGuid& Int16TimeseriesPropertyTimeseries( ) const
        {
            return i16tpTimeseries_;
        }
        const DBGuid& Int32TimeseriesPropertyTimeseries( ) const
        {
            return i32tpTimeseries_;
        }
        const DBGuid& Int64TimeseriesPropertyTimeseries( ) const
        {
            return i64tpTimeseries_;
        }
        const DBGuid& ReferenceTimeseriesPropertyTimeseries( ) const
        {
            return rtpTimeseries_;
        }
        const DBGuid& SByteTimeseriesPropertyTimeseries( ) const
        {
            return sbtpTimeseries_;
        }
        const DBGuid& SingleTimeseriesPropertyTimeseries( ) const
        {
            return sitpTimeseries_;
        }
        const DBGuid& StringTimeseriesPropertyTimeseries( ) const
        {
            return sttpTimeseries_;
        }
        const DBGuid& TimeSpanTimeseriesPropertyTimeseries( ) const
        {
            return tstpTimeseries_;
        }
        const DBGuid& UInt16TimeseriesPropertyTimeseries( ) const
        {
            return u16tpTimeseries_;
        }
        const DBGuid& UInt32TimeseriesPropertyTimeseries( ) const
        {
            return u32tpTimeseries_;
        }
        const DBGuid& UInt64TimeseriesPropertyTimeseries( ) const
        {
            return u64tpTimeseries_;
        }
        const DBTimeSpan& TimeSpanPropertyValue( ) const
        {
            return tspValue_;
        }
        DBUInt16 UInt16PropertyValue( ) const
        {
            return u16pValue_;
        }
        DBUInt32 UInt32PropertyValue( ) const
        {
            return u32pValue_;
        }
        DBInt64 UInt64PropertyValue( ) const
        {
            return u64pValue_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, element_);
            WriteColumnValue( destination, definition_);
            switch( kind_ )
            {
                case Data::Kind::BinaryProperty:
                {
                    WriteColumnValue( destination, bpValue_);
                }
                break;
                case Data::Kind::BooleanProperty:
                {
                    WriteColumnValue( destination, bopValue_);
                }
                break;
                case Data::Kind::ByteProperty:
                {
                    WriteColumnValue( destination, bypValue_);
                }
                break;
                case Data::Kind::DateTimeProperty:
                {
                    WriteColumnValue( destination, dtpValue_);
                }
                break;
                case Data::Kind::DoubleProperty:
                {
                    WriteColumnValue( destination, dpValue_);
                }
                break;
                case Data::Kind::GuidProperty:
                {
                    WriteColumnValue( destination, gpValue_);
                }
                break;
                case Data::Kind::Int16Property:
                {
                    WriteColumnValue( destination, i16pValue_);
                }
                break;
                case Data::Kind::Int32Property:
                {
                    WriteColumnValue( destination, i32pValue_);
                }
                break;
                case Data::Kind::Int64Property:
                {
                    WriteColumnValue( destination, i64pValue_);
                }
                break;
                case Data::Kind::ReferenceProperty:
                {
                    WriteColumnValue( destination, rpValue_);
                }
                break;
                case Data::Kind::SByteProperty:
                {
                    WriteColumnValue( destination, spValue_);
                }
                break;
                case Data::Kind::SingleProperty:
                {
                    WriteColumnValue( destination, sipValue_);
                }
                break;
                case Data::Kind::StringProperty:
                {
                    WriteColumnValue( destination, stpValue_);
                }
                break;
                case Data::Kind::BinaryTimeseriesProperty:
                {
                    WriteColumnValue( destination, btpTimeseries_);
                }
                break;
                case Data::Kind::BooleanTimeseriesProperty:
                {
                    WriteColumnValue( destination, botpTimeseries_);
                }
                break;
                case Data::Kind::ByteTimeseriesProperty:
                {
                    WriteColumnValue( destination, bytpTimeseries_);
                }
                break;
                case Data::Kind::DateTimeTimeseriesProperty:
                {
                    WriteColumnValue( destination, dttpTimeseries_);
                }
                break;
                case Data::Kind::DoubleTimeseriesProperty:
                {
                    WriteColumnValue( destination, dotpTimeseries_);
                }
                break;
                case Data::Kind::GuidTimeseriesProperty:
                {
                    WriteColumnValue( destination, gtpTimeseries_);
                }
                break;
                case Data::Kind::Int16TimeseriesProperty:
                {
                    WriteColumnValue( destination, i16tpTimeseries_);
                }
                break;
                case Data::Kind::Int32TimeseriesProperty:
                {
                    WriteColumnValue( destination, i32tpTimeseries_);
                }
                break;
                case Data::Kind::Int64TimeseriesProperty:
                {
                    WriteColumnValue( destination, i64tpTimeseries_);
                }
                break;
                case Data::Kind::ReferenceTimeseriesProperty:
                {
                    WriteColumnValue( destination, rtpTimeseries_);
                }
                break;
                case Data::Kind::SByteTimeseriesProperty:
                {
                    WriteColumnValue( destination, sbtpTimeseries_);
                }
                break;
                case Data::Kind::SingleTimeseriesProperty:
                {
                    WriteColumnValue( destination, sitpTimeseries_);
                }
                break;
                case Data::Kind::StringTimeseriesProperty:
                {
                    WriteColumnValue( destination, sttpTimeseries_);
                }
                break;
                case Data::Kind::TimeSpanTimeseriesProperty:
                {
                    WriteColumnValue( destination, tstpTimeseries_);
                }
                break;
                case Data::Kind::UInt16TimeseriesProperty:
                {
                    WriteColumnValue( destination, u16tpTimeseries_);
                }
                break;
                case Data::Kind::UInt32TimeseriesProperty:
                {
                    WriteColumnValue( destination, u32tpTimeseries_);
                }
                break;
                case Data::Kind::UInt64TimeseriesProperty:
                {
                    WriteColumnValue( destination, u64tpTimeseries_);
                }
                break;
                case Data::Kind::TimeSpanProperty:
                {
                    WriteColumnValue( destination, tspValue_);
                }
                break;
                case Data::Kind::UInt16Property:
                {
                    WriteColumnValue( destination, u16pValue_);
                }
                break;
                case Data::Kind::UInt32Property:
                {
                    WriteColumnValue( destination, u32pValue_);
                }
                break;
                case Data::Kind::UInt64Property:
                {
                    WriteColumnValue( destination, u64pValue_);
                }
                break;
            }
        }
    };

    using ComplexPropertyDataReader = SimpleColumnDataReader<ComplexPropertyColumnData>;

    class ComplexTimeseriesPropertyColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid element_;
        Guid definition_;
        DBGuid btpTimeseries_;
        DBGuid botpTimeseries_;
        DBGuid bytpTimeseries_;
        DBGuid dttpTimeseries_;
        DBGuid dotpTimeseries_;
        DBGuid gtpTimeseries_;
        DBGuid i16tpTimeseries_;
        DBGuid i32tpTimeseries_;
        DBGuid i64tpTimeseries_;
        DBGuid rtpTimeseries_;
        DBGuid sbtpTimeseries_;
        DBGuid sitpTimeseries_;
        DBGuid sttpTimeseries_;
        DBGuid tstpTimeseries_;
        DBGuid u16tpTimeseries_;
        DBGuid u32tpTimeseries_;
        DBGuid u64tpTimeseries_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT TP_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TP_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TP_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TP_ELEMENT_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TP_DEFINITION_FIELD_ID = 5;
        static constexpr SQLUSMALLINT BTP_TIMESERIES_FIELD_ID = 6;
        static constexpr SQLUSMALLINT BOTP_TIMESERIES_FIELD_ID = 7;
        static constexpr SQLUSMALLINT BYTP_TIMESERIES_FIELD_ID = 8;
        static constexpr SQLUSMALLINT DTTP_TIMESERIES_FIELD_ID = 9;
        static constexpr SQLUSMALLINT DOTP_TIMESERIES_FIELD_ID = 10;
        static constexpr SQLUSMALLINT GTP_TIMESERIES_FIELD_ID = 11;
        static constexpr SQLUSMALLINT I16TP_TIMESERIES_FIELD_ID = 12;
        static constexpr SQLUSMALLINT I32TP_TIMESERIES_FIELD_ID = 13;
        static constexpr SQLUSMALLINT I64TP_TIMESERIES_FIELD_ID = 14;
        static constexpr SQLUSMALLINT RTP_TIMESERIES_FIELD_ID = 15;
        static constexpr SQLUSMALLINT SBTP_TIMESERIES_FIELD_ID = 16;
        static constexpr SQLUSMALLINT SITP_TIMESERIES_FIELD_ID = 17;
        static constexpr SQLUSMALLINT STTP_TIMESERIES_FIELD_ID = 18;
        static constexpr SQLUSMALLINT TSTP_TIMESERIES_FIELD_ID = 19;
        static constexpr SQLUSMALLINT U16TP_TIMESERIES_FIELD_ID = 20;
        static constexpr SQLUSMALLINT U32TP_TIMESERIES_FIELD_ID = 21;
        static constexpr SQLUSMALLINT U64TP_TIMESERIES_FIELD_ID = 22;

        ComplexTimeseriesPropertyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Element( ) const
        {
            return element_;
        }
        const Guid& Definition( ) const
        {
            return definition_;
        }
        const DBGuid& BinaryTimeseriesPropertyTimeseries( ) const
        {
            return btpTimeseries_;
        }
        const DBGuid& BooleanTimeseriesPropertyTimeseries( ) const
        {
            return botpTimeseries_;
        }
        const DBGuid& ByteTimeseriesPropertyTimeseries( ) const
        {
            return bytpTimeseries_;
        }
        const DBGuid& DateTimeTimeseriesPropertyTimeseries( ) const
        {
            return dttpTimeseries_;
        }
        const DBGuid& DoubleTimeseriesPropertyTimeseries( ) const
        {
            return dotpTimeseries_;
        }
        const DBGuid& GuidTimeseriesPropertyTimeseries( ) const
        {
            return gtpTimeseries_;
        }
        const DBGuid& Int16TimeseriesPropertyTimeseries( ) const
        {
            return i16tpTimeseries_;
        }
        const DBGuid& Int32TimeseriesPropertyTimeseries( ) const
        {
            return i32tpTimeseries_;
        }
        const DBGuid& Int64TimeseriesPropertyTimeseries( ) const
        {
            return i64tpTimeseries_;
        }
        const DBGuid& ReferenceTimeseriesPropertyTimeseries( ) const
        {
            return rtpTimeseries_;
        }
        const DBGuid& SByteTimeseriesPropertyTimeseries( ) const
        {
            return sbtpTimeseries_;
        }
        const DBGuid& SingleTimeseriesPropertyTimeseries( ) const
        {
            return sitpTimeseries_;
        }
        const DBGuid& StringTimeseriesPropertyTimeseries( ) const
        {
            return sttpTimeseries_;
        }
        const DBGuid& TimeSpanTimeseriesPropertyTimeseries( ) const
        {
            return tstpTimeseries_;
        }
        const DBGuid& UInt16TimeseriesPropertyTimeseries( ) const
        {
            return u16tpTimeseries_;
        }
        const DBGuid& UInt32TimeseriesPropertyTimeseries( ) const
        {
            return u32tpTimeseries_;
        }
        const DBGuid& UInt64TimeseriesPropertyTimeseries( ) const
        {
            return u64tpTimeseries_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, element_);
            WriteColumnValue( destination, definition_);
            switch( kind_ )
            {
                case Data::Kind::BinaryTimeseriesProperty:
                {
                    WriteColumnValue( destination, btpTimeseries_);
                }
                break;
                case Data::Kind::BooleanTimeseriesProperty:
                {
                    WriteColumnValue( destination, botpTimeseries_);
                }
                break;
                case Data::Kind::ByteTimeseriesProperty:
                {
                    WriteColumnValue( destination, bytpTimeseries_);
                }
                break;
                case Data::Kind::DateTimeTimeseriesProperty:
                {
                    WriteColumnValue( destination, dttpTimeseries_);
                }
                break;
                case Data::Kind::DoubleTimeseriesProperty:
                {
                    WriteColumnValue( destination, dotpTimeseries_);
                }
                break;
                case Data::Kind::GuidTimeseriesProperty:
                {
                    WriteColumnValue( destination, gtpTimeseries_);
                }
                break;
                case Data::Kind::Int16TimeseriesProperty:
                {
                    WriteColumnValue( destination, i16tpTimeseries_);
                }
                break;
                case Data::Kind::Int32TimeseriesProperty:
                {
                    WriteColumnValue( destination, i32tpTimeseries_);
                }
                break;
                case Data::Kind::Int64TimeseriesProperty:
                {
                    WriteColumnValue( destination, i64tpTimeseries_);
                }
                break;
                case Data::Kind::ReferenceTimeseriesProperty:
                {
                    WriteColumnValue( destination, rtpTimeseries_);
                }
                break;
                case Data::Kind::SByteTimeseriesProperty:
                {
                    WriteColumnValue( destination, sbtpTimeseries_);
                }
                break;
                case Data::Kind::SingleTimeseriesProperty:
                {
                    WriteColumnValue( destination, sitpTimeseries_);
                }
                break;
                case Data::Kind::StringTimeseriesProperty:
                {
                    WriteColumnValue( destination, sttpTimeseries_);
                }
                break;
                case Data::Kind::TimeSpanTimeseriesProperty:
                {
                    WriteColumnValue( destination, tstpTimeseries_);
                }
                break;
                case Data::Kind::UInt16TimeseriesProperty:
                {
                    WriteColumnValue( destination, u16tpTimeseries_);
                }
                break;
                case Data::Kind::UInt32TimeseriesProperty:
                {
                    WriteColumnValue( destination, u32tpTimeseries_);
                }
                break;
                case Data::Kind::UInt64TimeseriesProperty:
                {
                    WriteColumnValue( destination, u64tpTimeseries_);
                }
                break;
            }
        }
    };

    using ComplexTimeseriesPropertyDataReader = SimpleColumnDataReader<ComplexTimeseriesPropertyColumnData>;

    class ComplexPropertyDefinitionColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid elementType_;
        FixedDBWideString<127> name_;
        WideString description_;
        SQLLEN descriptionLength_ = SQL_NULL_DATA;
        DBBinary bpdDefaultValue_;
        DBBoolean bopdDefaultValue_;
        DBByte bypdDefaultValue_;
        DBByte bypdMinValue_;
        DBByte bypdMaxValue_;
        FixedDBWideString<100> dtpdDefaultValue_;
        FixedDBWideString<100> dtpdMinValue_;
        FixedDBWideString<100> dtpdMaxValue_;
        DBDouble dpdDefaultValue_;
        DBDouble dpdMinValue_;
        DBDouble dpdMaxValue_;
        DBGuid gpdDefaultValue_;
        DBInt16 i16pdDefaultValue_;
        DBInt16 i16pdMinValue_;
        DBInt16 i16pdMaxValue_;
        DBInt32 i32pdDefaultValue_;
        DBInt32 i32pdMinValue_;
        DBInt32 i32pdMaxValue_;
        DBInt64 i64pdDefaultValue_;
        DBInt64 i64pdMinValue_;
        DBInt64 i64pdMaxValue_;
        DBGuid rpdDefaultValue_;
        DBGuid rpdReferencedElementType_;
        DBSByte sbpdDefaultValue_;
        DBSByte sbpdMinValue_;
        DBSByte sbpdMaxValue_;
        DBSingle sipdDefaultValue_;
        DBSingle sipdMinValue_;
        DBSingle sipdMaxValue_;
        FixedDBWideString<100> stpdDefaultValue_;
        FixedDBWideString<100> stpdPattern_;
        DBByte bytpdMinValue_;
        DBByte bytpdMaxValue_;
        FixedDBWideString<100> dttpdMinValue_;
        FixedDBWideString<100> dttpdMaxValue_;
        DBDouble dotpdMinValue_;
        DBDouble dotpdMaxValue_;
        DBInt16 i16tpdMinValue_;
        DBInt16 i16tpdMaxValue_;
        DBInt32 i32tpdMinValue_;
        DBInt32 i32tpdMaxValue_;
        DBInt64 i64tpdMinValue_;
        DBInt64 i64tpdMaxValue_;
        DBGuid rtpdReferencedElementType_;
        DBSByte sbtpdMinValue_;
        DBSByte sbtpdMaxValue_;
        DBSingle sitpdMinValue_;
        DBSingle sitpdMaxValue_;
        FixedDBWideString<100> sttpdPattern_;
        DBTimeSpan tstpdMinValue_;
        DBTimeSpan tstpdMaxValue_;
        DBUInt16 u16tpdMinValue_;
        DBUInt16 u16tpdMaxValue_;
        DBUInt32 u32tpdMinValue_;
        DBUInt32 u32tpdMaxValue_;
        DBInt64 u64tpdMinValue_;
        DBInt64 u64tpdMaxValue_;
        DBTimeSpan tspdDefaultValue_;
        DBTimeSpan tspdMinValue_;
        DBTimeSpan tspdMaxValue_;
        DBUInt16 u16pdDefaultValue_;
        DBUInt16 u16pdMinValue_;
        DBUInt16 u16pdMaxValue_;
        DBUInt32 u32pdDefaultValue_;
        DBUInt32 u32pdMinValue_;
        DBUInt32 u32pdMaxValue_;
        DBInt64 u64pdDefaultValue_;
        DBInt64 u64pdMinValue_;
        DBInt64 u64pdMaxValue_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT PD_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT PD_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT PD_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT PD_ELEMENTTYPE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT PD_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT BOPD_DEFAULTVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT BYPD_DEFAULTVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT BYPD_MINVALUE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT BYPD_MAXVALUE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT DTPD_DEFAULTVALUE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT DTPD_MINVALUE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT DTPD_MAXVALUE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT DPD_DEFAULTVALUE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT DPD_MINVALUE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT DPD_MAXVALUE_FIELD_ID = 15;
        static constexpr SQLUSMALLINT GPD_DEFAULTVALUE_FIELD_ID = 16;
        static constexpr SQLUSMALLINT I16PD_DEFAULTVALUE_FIELD_ID = 17;
        static constexpr SQLUSMALLINT I16PD_MINVALUE_FIELD_ID = 18;
        static constexpr SQLUSMALLINT I16PD_MAXVALUE_FIELD_ID = 19;
        static constexpr SQLUSMALLINT I32PD_DEFAULTVALUE_FIELD_ID = 20;
        static constexpr SQLUSMALLINT I32PD_MINVALUE_FIELD_ID = 21;
        static constexpr SQLUSMALLINT I32PD_MAXVALUE_FIELD_ID = 22;
        static constexpr SQLUSMALLINT I64PD_DEFAULTVALUE_FIELD_ID = 23;
        static constexpr SQLUSMALLINT I64PD_MINVALUE_FIELD_ID = 24;
        static constexpr SQLUSMALLINT I64PD_MAXVALUE_FIELD_ID = 25;
        static constexpr SQLUSMALLINT RPD_DEFAULTVALUE_FIELD_ID = 26;
        static constexpr SQLUSMALLINT RPD_REFERENCEDELEMENTTYPE_FIELD_ID = 27;
        static constexpr SQLUSMALLINT SBPD_DEFAULTVALUE_FIELD_ID = 28;
        static constexpr SQLUSMALLINT SBPD_MINVALUE_FIELD_ID = 29;
        static constexpr SQLUSMALLINT SBPD_MAXVALUE_FIELD_ID = 30;
        static constexpr SQLUSMALLINT SIPD_DEFAULTVALUE_FIELD_ID = 31;
        static constexpr SQLUSMALLINT SIPD_MINVALUE_FIELD_ID = 32;
        static constexpr SQLUSMALLINT SIPD_MAXVALUE_FIELD_ID = 33;
        static constexpr SQLUSMALLINT STPD_DEFAULTVALUE_FIELD_ID = 34;
        static constexpr SQLUSMALLINT STPD_PATTERN_FIELD_ID = 35;
        static constexpr SQLUSMALLINT BYTPD_MINVALUE_FIELD_ID = 36;
        static constexpr SQLUSMALLINT BYTPD_MAXVALUE_FIELD_ID = 37;
        static constexpr SQLUSMALLINT DTTPD_MINVALUE_FIELD_ID = 38;
        static constexpr SQLUSMALLINT DTTPD_MAXVALUE_FIELD_ID = 39;
        static constexpr SQLUSMALLINT DOTPD_MINVALUE_FIELD_ID = 40;
        static constexpr SQLUSMALLINT DOTPD_MAXVALUE_FIELD_ID = 41;
        static constexpr SQLUSMALLINT I16TPD_MINVALUE_FIELD_ID = 42;
        static constexpr SQLUSMALLINT I16TPD_MAXVALUE_FIELD_ID = 43;
        static constexpr SQLUSMALLINT I32TPD_MINVALUE_FIELD_ID = 44;
        static constexpr SQLUSMALLINT I32TPD_MAXVALUE_FIELD_ID = 45;
        static constexpr SQLUSMALLINT I64TPD_MINVALUE_FIELD_ID = 46;
        static constexpr SQLUSMALLINT I64TPD_MAXVALUE_FIELD_ID = 47;
        static constexpr SQLUSMALLINT RTPD_REFERENCEDELEMENTTYPE_FIELD_ID = 48;
        static constexpr SQLUSMALLINT SBTPD_MINVALUE_FIELD_ID = 49;
        static constexpr SQLUSMALLINT SBTPD_MAXVALUE_FIELD_ID = 50;
        static constexpr SQLUSMALLINT SITPD_MINVALUE_FIELD_ID = 51;
        static constexpr SQLUSMALLINT SITPD_MAXVALUE_FIELD_ID = 52;
        static constexpr SQLUSMALLINT STTPD_PATTERN_FIELD_ID = 53;
        static constexpr SQLUSMALLINT TSTPD_MINVALUE_FIELD_ID = 54;
        static constexpr SQLUSMALLINT TSTPD_MAXVALUE_FIELD_ID = 55;
        static constexpr SQLUSMALLINT U16TPD_MINVALUE_FIELD_ID = 56;
        static constexpr SQLUSMALLINT U16TPD_MAXVALUE_FIELD_ID = 57;
        static constexpr SQLUSMALLINT U32TPD_MINVALUE_FIELD_ID = 58;
        static constexpr SQLUSMALLINT U32TPD_MAXVALUE_FIELD_ID = 59;
        static constexpr SQLUSMALLINT U64TPD_MINVALUE_FIELD_ID = 60;
        static constexpr SQLUSMALLINT U64TPD_MAXVALUE_FIELD_ID = 61;
        static constexpr SQLUSMALLINT TSPD_DEFAULTVALUE_FIELD_ID = 62;
        static constexpr SQLUSMALLINT TSPD_MINVALUE_FIELD_ID = 63;
        static constexpr SQLUSMALLINT TSPD_MAXVALUE_FIELD_ID = 64;
        static constexpr SQLUSMALLINT U16PD_DEFAULTVALUE_FIELD_ID = 65;
        static constexpr SQLUSMALLINT U16PD_MINVALUE_FIELD_ID = 66;
        static constexpr SQLUSMALLINT U16PD_MAXVALUE_FIELD_ID = 67;
        static constexpr SQLUSMALLINT U32PD_DEFAULTVALUE_FIELD_ID = 68;
        static constexpr SQLUSMALLINT U32PD_MINVALUE_FIELD_ID = 69;
        static constexpr SQLUSMALLINT U32PD_MAXVALUE_FIELD_ID = 70;
        static constexpr SQLUSMALLINT U64PD_DEFAULTVALUE_FIELD_ID = 71;
        static constexpr SQLUSMALLINT U64PD_MINVALUE_FIELD_ID = 72;
        static constexpr SQLUSMALLINT U64PD_MAXVALUE_FIELD_ID = 73;
        static constexpr SQLUSMALLINT PD_DESCRIPTION_FIELD_ID = 74;
        static constexpr SQLUSMALLINT BPD_DEFAULTVALUE_FIELD_ID = 75;

        ComplexPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& ElementType( ) const
        {
            return elementType_;
        }
        const FixedDBWideString<127>& Name( ) const
        {
            return name_;
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        const DBBinary& BinaryPropertyDefinitionDefaultValue( ) const
        {
            return bpdDefaultValue_;
        }
        DBBoolean BooleanPropertyDefinitionDefaultValue( ) const
        {
            return bopdDefaultValue_;
        }
        DBByte BytePropertyDefinitionDefaultValue( ) const
        {
            return bypdDefaultValue_;
        }
        DBByte BytePropertyDefinitionMinValue( ) const
        {
            return bypdMinValue_;
        }
        DBByte BytePropertyDefinitionMaxValue( ) const
        {
            return bypdMaxValue_;
        }
        const FixedDBWideString<100>& DateTimePropertyDefinitionDefaultValue( ) const
        {
            return dtpdDefaultValue_;
        }
        const FixedDBWideString<100>& DateTimePropertyDefinitionMinValue( ) const
        {
            return dtpdMinValue_;
        }
        const FixedDBWideString<100>& DateTimePropertyDefinitionMaxValue( ) const
        {
            return dtpdMaxValue_;
        }
        DBDouble DoublePropertyDefinitionDefaultValue( ) const
        {
            return dpdDefaultValue_;
        }
        DBDouble DoublePropertyDefinitionMinValue( ) const
        {
            return dpdMinValue_;
        }
        DBDouble DoublePropertyDefinitionMaxValue( ) const
        {
            return dpdMaxValue_;
        }
        const DBGuid& GuidPropertyDefinitionDefaultValue( ) const
        {
            return gpdDefaultValue_;
        }
        DBInt16 Int16PropertyDefinitionDefaultValue( ) const
        {
            return i16pdDefaultValue_;
        }
        DBInt16 Int16PropertyDefinitionMinValue( ) const
        {
            return i16pdMinValue_;
        }
        DBInt16 Int16PropertyDefinitionMaxValue( ) const
        {
            return i16pdMaxValue_;
        }
        DBInt32 Int32PropertyDefinitionDefaultValue( ) const
        {
            return i32pdDefaultValue_;
        }
        DBInt32 Int32PropertyDefinitionMinValue( ) const
        {
            return i32pdMinValue_;
        }
        DBInt32 Int32PropertyDefinitionMaxValue( ) const
        {
            return i32pdMaxValue_;
        }
        DBInt64 Int64PropertyDefinitionDefaultValue( ) const
        {
            return i64pdDefaultValue_;
        }
        DBInt64 Int64PropertyDefinitionMinValue( ) const
        {
            return i64pdMinValue_;
        }
        DBInt64 Int64PropertyDefinitionMaxValue( ) const
        {
            return i64pdMaxValue_;
        }
        const DBGuid& ReferencePropertyDefinitionDefaultValue( ) const
        {
            return rpdDefaultValue_;
        }
        const DBGuid& ReferencePropertyDefinitionReferencedElementType( ) const
        {
            return rpdReferencedElementType_;
        }
        DBSByte SBytePropertyDefinitionDefaultValue( ) const
        {
            return sbpdDefaultValue_;
        }
        DBSByte SBytePropertyDefinitionMinValue( ) const
        {
            return sbpdMinValue_;
        }
        DBSByte SBytePropertyDefinitionMaxValue( ) const
        {
            return sbpdMaxValue_;
        }
        DBSingle SinglePropertyDefinitionDefaultValue( ) const
        {
            return sipdDefaultValue_;
        }
        DBSingle SinglePropertyDefinitionMinValue( ) const
        {
            return sipdMinValue_;
        }
        DBSingle SinglePropertyDefinitionMaxValue( ) const
        {
            return sipdMaxValue_;
        }
        const FixedDBWideString<100>& StringPropertyDefinitionDefaultValue( ) const
        {
            return stpdDefaultValue_;
        }
        const FixedDBWideString<100>& StringPropertyDefinitionPattern( ) const
        {
            return stpdPattern_;
        }
        DBByte ByteTimeseriesPropertyDefinitionMinValue( ) const
        {
            return bytpdMinValue_;
        }
        DBByte ByteTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return bytpdMaxValue_;
        }
        const FixedDBWideString<100>& DateTimeTimeseriesPropertyDefinitionMinValue( ) const
        {
            return dttpdMinValue_;
        }
        const FixedDBWideString<100>& DateTimeTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return dttpdMaxValue_;
        }
        DBDouble DoubleTimeseriesPropertyDefinitionMinValue( ) const
        {
            return dotpdMinValue_;
        }
        DBDouble DoubleTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return dotpdMaxValue_;
        }
        DBInt16 Int16TimeseriesPropertyDefinitionMinValue( ) const
        {
            return i16tpdMinValue_;
        }
        DBInt16 Int16TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return i16tpdMaxValue_;
        }
        DBInt32 Int32TimeseriesPropertyDefinitionMinValue( ) const
        {
            return i32tpdMinValue_;
        }
        DBInt32 Int32TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return i32tpdMaxValue_;
        }
        DBInt64 Int64TimeseriesPropertyDefinitionMinValue( ) const
        {
            return i64tpdMinValue_;
        }
        DBInt64 Int64TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return i64tpdMaxValue_;
        }
        const DBGuid& ReferenceTimeseriesPropertyDefinitionReferencedElementType( ) const
        {
            return rtpdReferencedElementType_;
        }
        DBSByte SByteTimeseriesPropertyDefinitionMinValue( ) const
        {
            return sbtpdMinValue_;
        }
        DBSByte SByteTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return sbtpdMaxValue_;
        }
        DBSingle SingleTimeseriesPropertyDefinitionMinValue( ) const
        {
            return sitpdMinValue_;
        }
        DBSingle SingleTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return sitpdMaxValue_;
        }
        const FixedDBWideString<100>& StringTimeseriesPropertyDefinitionPattern( ) const
        {
            return sttpdPattern_;
        }
        const DBTimeSpan& TimeSpanTimeseriesPropertyDefinitionMinValue( ) const
        {
            return tstpdMinValue_;
        }
        const DBTimeSpan& TimeSpanTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return tstpdMaxValue_;
        }
        DBUInt16 UInt16TimeseriesPropertyDefinitionMinValue( ) const
        {
            return u16tpdMinValue_;
        }
        DBUInt16 UInt16TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return u16tpdMaxValue_;
        }
        DBUInt32 UInt32TimeseriesPropertyDefinitionMinValue( ) const
        {
            return u32tpdMinValue_;
        }
        DBUInt32 UInt32TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return u32tpdMaxValue_;
        }
        DBInt64 UInt64TimeseriesPropertyDefinitionMinValue( ) const
        {
            return u64tpdMinValue_;
        }
        DBInt64 UInt64TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return u64tpdMaxValue_;
        }
        const DBTimeSpan& TimeSpanPropertyDefinitionDefaultValue( ) const
        {
            return tspdDefaultValue_;
        }
        const DBTimeSpan& TimeSpanPropertyDefinitionMinValue( ) const
        {
            return tspdMinValue_;
        }
        const DBTimeSpan& TimeSpanPropertyDefinitionMaxValue( ) const
        {
            return tspdMaxValue_;
        }
        DBUInt16 UInt16PropertyDefinitionDefaultValue( ) const
        {
            return u16pdDefaultValue_;
        }
        DBUInt16 UInt16PropertyDefinitionMinValue( ) const
        {
            return u16pdMinValue_;
        }
        DBUInt16 UInt16PropertyDefinitionMaxValue( ) const
        {
            return u16pdMaxValue_;
        }
        DBUInt32 UInt32PropertyDefinitionDefaultValue( ) const
        {
            return u32pdDefaultValue_;
        }
        DBUInt32 UInt32PropertyDefinitionMinValue( ) const
        {
            return u32pdMinValue_;
        }
        DBUInt32 UInt32PropertyDefinitionMaxValue( ) const
        {
            return u32pdMaxValue_;
        }
        DBInt64 UInt64PropertyDefinitionDefaultValue( ) const
        {
            return u64pdDefaultValue_;
        }
        DBInt64 UInt64PropertyDefinitionMinValue( ) const
        {
            return u64pdMinValue_;
        }
        DBInt64 UInt64PropertyDefinitionMaxValue( ) const
        {
            return u64pdMaxValue_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, elementType_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, description_);
            switch( kind_ )
            {
                case Data::Kind::BinaryPropertyDefinition:
                {
                    WriteColumnValue( destination, bpdDefaultValue_);
                }
                break;
                case Data::Kind::BooleanPropertyDefinition:
                {
                    WriteColumnValue( destination, bopdDefaultValue_);
                }
                break;
                case Data::Kind::BytePropertyDefinition:
                {
                    WriteColumnValue( destination, bypdDefaultValue_);
                    WriteColumnValue( destination, bypdMinValue_);
                    WriteColumnValue( destination, bypdMaxValue_);
                }
                break;
                case Data::Kind::DateTimePropertyDefinition:
                {
                    WriteColumnValue( destination, dtpdDefaultValue_);
                    WriteColumnValue( destination, dtpdMinValue_);
                    WriteColumnValue( destination, dtpdMaxValue_);
                }
                break;
                case Data::Kind::DoublePropertyDefinition:
                {
                    WriteColumnValue( destination, dpdDefaultValue_);
                    WriteColumnValue( destination, dpdMinValue_);
                    WriteColumnValue( destination, dpdMaxValue_);
                }
                break;
                case Data::Kind::GuidPropertyDefinition:
                {
                    WriteColumnValue( destination, gpdDefaultValue_);
                }
                break;
                case Data::Kind::Int16PropertyDefinition:
                {
                    WriteColumnValue( destination, i16pdDefaultValue_);
                    WriteColumnValue( destination, i16pdMinValue_);
                    WriteColumnValue( destination, i16pdMaxValue_);
                }
                break;
                case Data::Kind::Int32PropertyDefinition:
                {
                    WriteColumnValue( destination, i32pdDefaultValue_);
                    WriteColumnValue( destination, i32pdMinValue_);
                    WriteColumnValue( destination, i32pdMaxValue_);
                }
                break;
                case Data::Kind::Int64PropertyDefinition:
                {
                    WriteColumnValue( destination, i64pdDefaultValue_);
                    WriteColumnValue( destination, i64pdMinValue_);
                    WriteColumnValue( destination, i64pdMaxValue_);
                }
                break;
                case Data::Kind::ReferencePropertyDefinition:
                {
                    WriteColumnValue( destination, rpdDefaultValue_);
                    WriteColumnValue( destination, rpdReferencedElementType_);
                }
                break;
                case Data::Kind::SBytePropertyDefinition:
                {
                    WriteColumnValue( destination, sbpdDefaultValue_);
                    WriteColumnValue( destination, sbpdMinValue_);
                    WriteColumnValue( destination, sbpdMaxValue_);
                }
                break;
                case Data::Kind::SinglePropertyDefinition:
                {
                    WriteColumnValue( destination, sipdDefaultValue_);
                    WriteColumnValue( destination, sipdMinValue_);
                    WriteColumnValue( destination, sipdMaxValue_);
                }
                break;
                case Data::Kind::StringPropertyDefinition:
                {
                    WriteColumnValue( destination, stpdDefaultValue_);
                    WriteColumnValue( destination, stpdPattern_);
                }
                break;
                case Data::Kind::ByteTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, bytpdMinValue_);
                    WriteColumnValue( destination, bytpdMaxValue_);
                }
                break;
                case Data::Kind::DateTimeTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, dttpdMinValue_);
                    WriteColumnValue( destination, dttpdMaxValue_);
                }
                break;
                case Data::Kind::DoubleTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, dotpdMinValue_);
                    WriteColumnValue( destination, dotpdMaxValue_);
                }
                break;
                case Data::Kind::Int16TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, i16tpdMinValue_);
                    WriteColumnValue( destination, i16tpdMaxValue_);
                }
                break;
                case Data::Kind::Int32TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, i32tpdMinValue_);
                    WriteColumnValue( destination, i32tpdMaxValue_);
                }
                break;
                case Data::Kind::Int64TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, i64tpdMinValue_);
                    WriteColumnValue( destination, i64tpdMaxValue_);
                }
                break;
                case Data::Kind::ReferenceTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, rtpdReferencedElementType_);
                }
                break;
                case Data::Kind::SByteTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, sbtpdMinValue_);
                    WriteColumnValue( destination, sbtpdMaxValue_);
                }
                break;
                case Data::Kind::SingleTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, sitpdMinValue_);
                    WriteColumnValue( destination, sitpdMaxValue_);
                }
                break;
                case Data::Kind::StringTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, sttpdPattern_);
                }
                break;
                case Data::Kind::TimeSpanTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, tstpdMinValue_);
                    WriteColumnValue( destination, tstpdMaxValue_);
                }
                break;
                case Data::Kind::UInt16TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, u16tpdMinValue_);
                    WriteColumnValue( destination, u16tpdMaxValue_);
                }
                break;
                case Data::Kind::UInt32TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, u32tpdMinValue_);
                    WriteColumnValue( destination, u32tpdMaxValue_);
                }
                break;
                case Data::Kind::UInt64TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, u64tpdMinValue_);
                    WriteColumnValue( destination, u64tpdMaxValue_);
                }
                break;
                case Data::Kind::TimeSpanPropertyDefinition:
                {
                    WriteColumnValue( destination, tspdDefaultValue_);
                    WriteColumnValue( destination, tspdMinValue_);
                    WriteColumnValue( destination, tspdMaxValue_);
                }
                break;
                case Data::Kind::UInt16PropertyDefinition:
                {
                    WriteColumnValue( destination, u16pdDefaultValue_);
                    WriteColumnValue( destination, u16pdMinValue_);
                    WriteColumnValue( destination, u16pdMaxValue_);
                }
                break;
                case Data::Kind::UInt32PropertyDefinition:
                {
                    WriteColumnValue( destination, u32pdDefaultValue_);
                    WriteColumnValue( destination, u32pdMinValue_);
                    WriteColumnValue( destination, u32pdMaxValue_);
                }
                break;
                case Data::Kind::UInt64PropertyDefinition:
                {
                    WriteColumnValue( destination, u64pdDefaultValue_);
                    WriteColumnValue( destination, u64pdMinValue_);
                    WriteColumnValue( destination, u64pdMaxValue_);
                }
                break;
            }
        }
    };

    using ComplexPropertyDefinitionDataReader = SimpleColumnDataReader<ComplexPropertyDefinitionColumnData>;

    class ComplexTimeseriesPropertyDefinitionColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid elementType_;
        FixedDBWideString<127> name_;
        WideString description_;
        SQLLEN descriptionLength_ = SQL_NULL_DATA;
        DBByte bytpdMinValue_;
        DBByte bytpdMaxValue_;
        FixedDBWideString<100> dttpdMinValue_;
        FixedDBWideString<100> dttpdMaxValue_;
        DBDouble dotpdMinValue_;
        DBDouble dotpdMaxValue_;
        DBInt16 i16tpdMinValue_;
        DBInt16 i16tpdMaxValue_;
        DBInt32 i32tpdMinValue_;
        DBInt32 i32tpdMaxValue_;
        DBInt64 i64tpdMinValue_;
        DBInt64 i64tpdMaxValue_;
        DBGuid rtpdReferencedElementType_;
        DBSByte sbtpdMinValue_;
        DBSByte sbtpdMaxValue_;
        DBSingle sitpdMinValue_;
        DBSingle sitpdMaxValue_;
        FixedDBWideString<100> sttpdPattern_;
        DBTimeSpan tstpdMinValue_;
        DBTimeSpan tstpdMaxValue_;
        DBUInt16 u16tpdMinValue_;
        DBUInt16 u16tpdMaxValue_;
        DBUInt32 u32tpdMinValue_;
        DBUInt32 u32tpdMaxValue_;
        DBInt64 u64tpdMinValue_;
        DBInt64 u64tpdMaxValue_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT TPD_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TPD_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TPD_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TPD_ELEMENTTYPE_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TPD_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT BYTPD_MINVALUE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT BYTPD_MAXVALUE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT DTTPD_MINVALUE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT DTTPD_MAXVALUE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT DOTPD_MINVALUE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT DOTPD_MAXVALUE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT I16TPD_MINVALUE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT I16TPD_MAXVALUE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT I32TPD_MINVALUE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT I32TPD_MAXVALUE_FIELD_ID = 15;
        static constexpr SQLUSMALLINT I64TPD_MINVALUE_FIELD_ID = 16;
        static constexpr SQLUSMALLINT I64TPD_MAXVALUE_FIELD_ID = 17;
        static constexpr SQLUSMALLINT RTPD_REFERENCEDELEMENTTYPE_FIELD_ID = 18;
        static constexpr SQLUSMALLINT SBTPD_MINVALUE_FIELD_ID = 19;
        static constexpr SQLUSMALLINT SBTPD_MAXVALUE_FIELD_ID = 20;
        static constexpr SQLUSMALLINT SITPD_MINVALUE_FIELD_ID = 21;
        static constexpr SQLUSMALLINT SITPD_MAXVALUE_FIELD_ID = 22;
        static constexpr SQLUSMALLINT STTPD_PATTERN_FIELD_ID = 23;
        static constexpr SQLUSMALLINT TSTPD_MINVALUE_FIELD_ID = 24;
        static constexpr SQLUSMALLINT TSTPD_MAXVALUE_FIELD_ID = 25;
        static constexpr SQLUSMALLINT U16TPD_MINVALUE_FIELD_ID = 26;
        static constexpr SQLUSMALLINT U16TPD_MAXVALUE_FIELD_ID = 27;
        static constexpr SQLUSMALLINT U32TPD_MINVALUE_FIELD_ID = 28;
        static constexpr SQLUSMALLINT U32TPD_MAXVALUE_FIELD_ID = 29;
        static constexpr SQLUSMALLINT U64TPD_MINVALUE_FIELD_ID = 30;
        static constexpr SQLUSMALLINT U64TPD_MAXVALUE_FIELD_ID = 31;
        static constexpr SQLUSMALLINT TPD_DESCRIPTION_FIELD_ID = 32;

        ComplexTimeseriesPropertyDefinitionColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& ElementType( ) const
        {
            return elementType_;
        }
        const FixedDBWideString<127>& Name( ) const
        {
            return name_;
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        DBByte ByteTimeseriesPropertyDefinitionMinValue( ) const
        {
            return bytpdMinValue_;
        }
        DBByte ByteTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return bytpdMaxValue_;
        }
        const FixedDBWideString<100>& DateTimeTimeseriesPropertyDefinitionMinValue( ) const
        {
            return dttpdMinValue_;
        }
        const FixedDBWideString<100>& DateTimeTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return dttpdMaxValue_;
        }
        DBDouble DoubleTimeseriesPropertyDefinitionMinValue( ) const
        {
            return dotpdMinValue_;
        }
        DBDouble DoubleTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return dotpdMaxValue_;
        }
        DBInt16 Int16TimeseriesPropertyDefinitionMinValue( ) const
        {
            return i16tpdMinValue_;
        }
        DBInt16 Int16TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return i16tpdMaxValue_;
        }
        DBInt32 Int32TimeseriesPropertyDefinitionMinValue( ) const
        {
            return i32tpdMinValue_;
        }
        DBInt32 Int32TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return i32tpdMaxValue_;
        }
        DBInt64 Int64TimeseriesPropertyDefinitionMinValue( ) const
        {
            return i64tpdMinValue_;
        }
        DBInt64 Int64TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return i64tpdMaxValue_;
        }
        const DBGuid& ReferenceTimeseriesPropertyDefinitionReferencedElementType( ) const
        {
            return rtpdReferencedElementType_;
        }
        DBSByte SByteTimeseriesPropertyDefinitionMinValue( ) const
        {
            return sbtpdMinValue_;
        }
        DBSByte SByteTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return sbtpdMaxValue_;
        }
        DBSingle SingleTimeseriesPropertyDefinitionMinValue( ) const
        {
            return sitpdMinValue_;
        }
        DBSingle SingleTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return sitpdMaxValue_;
        }
        const FixedDBWideString<100>& StringTimeseriesPropertyDefinitionPattern( ) const
        {
            return sttpdPattern_;
        }
        const DBTimeSpan& TimeSpanTimeseriesPropertyDefinitionMinValue( ) const
        {
            return tstpdMinValue_;
        }
        const DBTimeSpan& TimeSpanTimeseriesPropertyDefinitionMaxValue( ) const
        {
            return tstpdMaxValue_;
        }
        DBUInt16 UInt16TimeseriesPropertyDefinitionMinValue( ) const
        {
            return u16tpdMinValue_;
        }
        DBUInt16 UInt16TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return u16tpdMaxValue_;
        }
        DBUInt32 UInt32TimeseriesPropertyDefinitionMinValue( ) const
        {
            return u32tpdMinValue_;
        }
        DBUInt32 UInt32TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return u32tpdMaxValue_;
        }
        DBInt64 UInt64TimeseriesPropertyDefinitionMinValue( ) const
        {
            return u64tpdMinValue_;
        }
        DBInt64 UInt64TimeseriesPropertyDefinitionMaxValue( ) const
        {
            return u64tpdMaxValue_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, elementType_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, description_);
            switch( kind_ )
            {
                case Data::Kind::ByteTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, bytpdMinValue_);
                    WriteColumnValue( destination, bytpdMaxValue_);
                }
                break;
                case Data::Kind::DateTimeTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, dttpdMinValue_);
                    WriteColumnValue( destination, dttpdMaxValue_);
                }
                break;
                case Data::Kind::DoubleTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, dotpdMinValue_);
                    WriteColumnValue( destination, dotpdMaxValue_);
                }
                break;
                case Data::Kind::Int16TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, i16tpdMinValue_);
                    WriteColumnValue( destination, i16tpdMaxValue_);
                }
                break;
                case Data::Kind::Int32TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, i32tpdMinValue_);
                    WriteColumnValue( destination, i32tpdMaxValue_);
                }
                break;
                case Data::Kind::Int64TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, i64tpdMinValue_);
                    WriteColumnValue( destination, i64tpdMaxValue_);
                }
                break;
                case Data::Kind::ReferenceTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, rtpdReferencedElementType_);
                }
                break;
                case Data::Kind::SByteTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, sbtpdMinValue_);
                    WriteColumnValue( destination, sbtpdMaxValue_);
                }
                break;
                case Data::Kind::SingleTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, sitpdMinValue_);
                    WriteColumnValue( destination, sitpdMaxValue_);
                }
                break;
                case Data::Kind::StringTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, sttpdPattern_);
                }
                break;
                case Data::Kind::TimeSpanTimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, tstpdMinValue_);
                    WriteColumnValue( destination, tstpdMaxValue_);
                }
                break;
                case Data::Kind::UInt16TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, u16tpdMinValue_);
                    WriteColumnValue( destination, u16tpdMaxValue_);
                }
                break;
                case Data::Kind::UInt32TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, u32tpdMinValue_);
                    WriteColumnValue( destination, u32tpdMaxValue_);
                }
                break;
                case Data::Kind::UInt64TimeseriesPropertyDefinition:
                {
                    WriteColumnValue( destination, u64tpdMinValue_);
                    WriteColumnValue( destination, u64tpdMaxValue_);
                }
                break;
            }
        }
    };

    using ComplexTimeseriesPropertyDefinitionDataReader = SimpleColumnDataReader<ComplexTimeseriesPropertyDefinitionColumnData>;

    class ComplexRadarCommandColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Data::DeviceCommandSourceType deviceCommandSourceType_ = Data::DeviceCommandSourceType::Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT RC_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT RC_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT RC_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT RC_RADAR_FIELD_ID = 4;
        static constexpr SQLUSMALLINT RC_TIMESTAMP_FIELD_ID = 5;
        static constexpr SQLUSMALLINT RC_DEVICECOMMANDSOURCETYPE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT RC_DEVICECOMMANDSOURCEID_FIELD_ID = 7;
        static constexpr SQLUSMALLINT RC_REPLY_FIELD_ID = 8;

        ComplexRadarCommandColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Radar( ) const
        {
            return radar_;
        }
        const DateTime& Timestamp( ) const
        {
            return timestamp_;
        }
        Data::DeviceCommandSourceType DeviceCommandSourceType( ) const
        {
            return deviceCommandSourceType_;
        }
        const Guid& DeviceCommandSourceId( ) const
        {
            return deviceCommandSourceId_;
        }
        const Guid& Reply( ) const
        {
            return reply_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, radar_);
            WriteColumnValue( destination, timestamp_);
            WriteColumnValue( destination, deviceCommandSourceType_);
            WriteColumnValue( destination, deviceCommandSourceId_);
            WriteColumnValue( destination, reply_);
        }
    };

    using ComplexRadarCommandDataReader = SimpleColumnDataReader<ComplexRadarCommandColumnData>;

    class ComplexRadarCommandReplyColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Guid command_;
        Data::DeviceCommandReplyStatus status_ = Data::DeviceCommandReplyStatus::Unknown;
        WideString message_;
        SQLLEN messageLength_ = SQL_NULL_DATA;
        DBInt32 rcrgsAzimuthCount_;
        DBInt32 rcrgsTriggerCount_;
        DBTimeSpan rcrgsRotationCount_;
        DBEnum<Data::RadarPulse> rcrgsPulse_;
        DBBoolean rcrgsTx_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT RCR_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT RCR_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT RCR_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT RCR_RADAR_FIELD_ID = 4;
        static constexpr SQLUSMALLINT RCR_TIMESTAMP_FIELD_ID = 5;
        static constexpr SQLUSMALLINT RCR_COMMAND_FIELD_ID = 6;
        static constexpr SQLUSMALLINT RCR_STATUS_FIELD_ID = 7;
        static constexpr SQLUSMALLINT RCRGS_AZIMUTHCOUNT_FIELD_ID = 8;
        static constexpr SQLUSMALLINT RCRGS_TRIGGERCOUNT_FIELD_ID = 9;
        static constexpr SQLUSMALLINT RCRGS_ROTATIONCOUNT_FIELD_ID = 10;
        static constexpr SQLUSMALLINT RCRGS_PULSE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT RCRGS_TX_FIELD_ID = 12;
        static constexpr SQLUSMALLINT RCR_MESSAGE_FIELD_ID = 13;

        ComplexRadarCommandReplyColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Radar( ) const
        {
            return radar_;
        }
        const DateTime& Timestamp( ) const
        {
            return timestamp_;
        }
        const Guid& Command( ) const
        {
            return command_;
        }
        Data::DeviceCommandReplyStatus Status( ) const
        {
            return status_;
        }
        const WideString& Message( ) const
        {
            return message_;
        }
        DBInt32 RadarCommandReplyGetStatusAzimuthCount( ) const
        {
            return rcrgsAzimuthCount_;
        }
        DBInt32 RadarCommandReplyGetStatusTriggerCount( ) const
        {
            return rcrgsTriggerCount_;
        }
        const DBTimeSpan& RadarCommandReplyGetStatusRotationCount( ) const
        {
            return rcrgsRotationCount_;
        }
        DBEnum<Data::RadarPulse> RadarCommandReplyGetStatusPulse( ) const
        {
            return rcrgsPulse_;
        }
        DBBoolean RadarCommandReplyGetStatusTx( ) const
        {
            return rcrgsTx_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, radar_);
            WriteColumnValue( destination, timestamp_);
            WriteColumnValue( destination, command_);
            WriteColumnValue( destination, status_);
            WriteColumnValue( destination, message_);
            switch( kind_ )
            {
                case Data::Kind::RadarCommandReplyGetStatus:
                {
                    WriteColumnValue( destination, rcrgsAzimuthCount_);
                    WriteColumnValue( destination, rcrgsTriggerCount_);
                    WriteColumnValue( destination, rcrgsRotationCount_);
                    WriteColumnValue( destination, rcrgsPulse_);
                    WriteColumnValue( destination, rcrgsTx_);
                }
                break;
            }
        }
    };

    using ComplexRadarCommandReplyDataReader = SimpleColumnDataReader<ComplexRadarCommandReplyColumnData>;

    class ComplexSecurityIdentifierColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid domain_;
        FixedDBWideString<255> identity_;
        WideString description_;
        SQLLEN descriptionLength_ = SQL_NULL_DATA;
        FixedDBWideString<127> srName_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT SI_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT SI_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT SI_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT SI_DOMAIN_FIELD_ID = 4;
        static constexpr SQLUSMALLINT SI_IDENTITY_FIELD_ID = 5;
        static constexpr SQLUSMALLINT SR_NAME_FIELD_ID = 6;
        static constexpr SQLUSMALLINT SI_DESCRIPTION_FIELD_ID = 7;

        ComplexSecurityIdentifierColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Domain( ) const
        {
            return domain_;
        }
        const FixedDBWideString<255>& Identity( ) const
        {
            return identity_;
        }
        const WideString& Description( ) const
        {
            return description_;
        }
        const FixedDBWideString<127>& SecurityRoleName( ) const
        {
            return srName_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, domain_);
            WriteColumnValue( destination, identity_);
            WriteColumnValue( destination, description_);
            switch( kind_ )
            {
                case Data::Kind::SecurityRole:
                {
                    WriteColumnValue( destination, srName_);
                }
                break;
            }
        }
    };

    using ComplexSecurityIdentifierDataReader = SimpleColumnDataReader<ComplexSecurityIdentifierColumnData>;

    class ComplexTimeseriesCatalogElementColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid catalog_;
        FixedDBWideString<100> name_;
        DBTimeSpan tMaxRetention_;
        DBGuid aatnoptAidToNavigation_;
        DBGuid detDevice_;
        DBGuid mpsetProxySession_;
        DBGuid msetService_;
        DBGuid rastctRadar_;
        DBGuid rbs1tRadar_;
        DBGuid rbs2tRadar_;
        DBGuid reafctRadar_;
        DBGuid reftctRadar_;
        DBGuid restctRadar_;
        DBGuid rpotRadar_;
        DBGuid rsstRadar_;
        DBGuid rttRadar_;
        DBGuid gatsGNSSDevice_;
        DBGuid glatsGNSSDevice_;
        DBGuid glotsGNSSDevice_;
        DBGuid gctGyroDevice_;
        DBGuid ghmntGyroDevice_;
        DBGuid ghtntGyroDevice_;
        DBGuid gptGyroDevice_;
        DBGuid grottGyroDevice_;
        DBGuid grtGyroDevice_;
        DBGuid gstGyroDevice_;
        DBGuid rlatsRadar_;
        DBGuid rlotsRadar_;
        DBGuid rdptRadome_;
        DBGuid rptRadome_;
        DBGuid rtetsRadome_;
        DBGuid vdtVessel_;
        DBGuid vlatsView_;
        DBGuid vlotsView_;
        DBGuid vzltView_;
        DBGuid wsahtWeatherStation_;
        DBGuid wsattWeatherStation_;
        DBGuid wsbptWeatherStation_;
        DBGuid wsdptWeatherStation_;
        DBGuid wsrhtWeatherStation_;
        DBGuid wswttWeatherStation_;
        DBGuid wswdtWeatherStation_;
        DBGuid wswstWeatherStation_;
        DBGuid aatnptAidToNavigation_;
        DBGuid raotRadar_;
        DBGuid rftcltRadar_;
        DBGuid rftcmtRadar_;
        DBGuid raptsRadar_;
        DBGuid rs1etRadar_;
        DBGuid rs1stRadar_;
        DBGuid rs2etRadar_;
        DBGuid rs2stRadar_;
        DBGuid rstcltRadar_;
        DBGuid ratutsRadar_;
        DBGuid vpobtVessel_;
        DBGuid rstRadome_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT TCE_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TCE_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TCE_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TCE_CATALOG_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TCE_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT T_MAXRETENTION_FIELD_ID = 6;
        static constexpr SQLUSMALLINT AATNOPT_AIDTONAVIGATION_FIELD_ID = 7;
        static constexpr SQLUSMALLINT DET_DEVICE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT MPSET_PROXYSESSION_FIELD_ID = 9;
        static constexpr SQLUSMALLINT MSET_SERVICE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT RASTCT_RADAR_FIELD_ID = 11;
        static constexpr SQLUSMALLINT RBS1T_RADAR_FIELD_ID = 12;
        static constexpr SQLUSMALLINT RBS2T_RADAR_FIELD_ID = 13;
        static constexpr SQLUSMALLINT REAFCT_RADAR_FIELD_ID = 14;
        static constexpr SQLUSMALLINT REFTCT_RADAR_FIELD_ID = 15;
        static constexpr SQLUSMALLINT RESTCT_RADAR_FIELD_ID = 16;
        static constexpr SQLUSMALLINT RPOT_RADAR_FIELD_ID = 17;
        static constexpr SQLUSMALLINT RSST_RADAR_FIELD_ID = 18;
        static constexpr SQLUSMALLINT RTT_RADAR_FIELD_ID = 19;
        static constexpr SQLUSMALLINT GATS_GNSSDEVICE_FIELD_ID = 20;
        static constexpr SQLUSMALLINT GLATS_GNSSDEVICE_FIELD_ID = 21;
        static constexpr SQLUSMALLINT GLOTS_GNSSDEVICE_FIELD_ID = 22;
        static constexpr SQLUSMALLINT GCT_GYRODEVICE_FIELD_ID = 23;
        static constexpr SQLUSMALLINT GHMNT_GYRODEVICE_FIELD_ID = 24;
        static constexpr SQLUSMALLINT GHTNT_GYRODEVICE_FIELD_ID = 25;
        static constexpr SQLUSMALLINT GPT_GYRODEVICE_FIELD_ID = 26;
        static constexpr SQLUSMALLINT GROTT_GYRODEVICE_FIELD_ID = 27;
        static constexpr SQLUSMALLINT GRT_GYRODEVICE_FIELD_ID = 28;
        static constexpr SQLUSMALLINT GST_GYRODEVICE_FIELD_ID = 29;
        static constexpr SQLUSMALLINT RLATS_RADAR_FIELD_ID = 30;
        static constexpr SQLUSMALLINT RLOTS_RADAR_FIELD_ID = 31;
        static constexpr SQLUSMALLINT RDPT_RADOME_FIELD_ID = 32;
        static constexpr SQLUSMALLINT RPT_RADOME_FIELD_ID = 33;
        static constexpr SQLUSMALLINT RTETS_RADOME_FIELD_ID = 34;
        static constexpr SQLUSMALLINT VDT_VESSEL_FIELD_ID = 35;
        static constexpr SQLUSMALLINT VLATS_VIEW_FIELD_ID = 36;
        static constexpr SQLUSMALLINT VLOTS_VIEW_FIELD_ID = 37;
        static constexpr SQLUSMALLINT VZLT_VIEW_FIELD_ID = 38;
        static constexpr SQLUSMALLINT WSAHT_WEATHERSTATION_FIELD_ID = 39;
        static constexpr SQLUSMALLINT WSATT_WEATHERSTATION_FIELD_ID = 40;
        static constexpr SQLUSMALLINT WSBPT_WEATHERSTATION_FIELD_ID = 41;
        static constexpr SQLUSMALLINT WSDPT_WEATHERSTATION_FIELD_ID = 42;
        static constexpr SQLUSMALLINT WSRHT_WEATHERSTATION_FIELD_ID = 43;
        static constexpr SQLUSMALLINT WSWTT_WEATHERSTATION_FIELD_ID = 44;
        static constexpr SQLUSMALLINT WSWDT_WEATHERSTATION_FIELD_ID = 45;
        static constexpr SQLUSMALLINT WSWST_WEATHERSTATION_FIELD_ID = 46;
        static constexpr SQLUSMALLINT AATNPT_AIDTONAVIGATION_FIELD_ID = 47;
        static constexpr SQLUSMALLINT RAOT_RADAR_FIELD_ID = 48;
        static constexpr SQLUSMALLINT RFTCLT_RADAR_FIELD_ID = 49;
        static constexpr SQLUSMALLINT RFTCMT_RADAR_FIELD_ID = 50;
        static constexpr SQLUSMALLINT RAPTS_RADAR_FIELD_ID = 51;
        static constexpr SQLUSMALLINT RS1ET_RADAR_FIELD_ID = 52;
        static constexpr SQLUSMALLINT RS1ST_RADAR_FIELD_ID = 53;
        static constexpr SQLUSMALLINT RS2ET_RADAR_FIELD_ID = 54;
        static constexpr SQLUSMALLINT RS2ST_RADAR_FIELD_ID = 55;
        static constexpr SQLUSMALLINT RSTCLT_RADAR_FIELD_ID = 56;
        static constexpr SQLUSMALLINT RATUTS_RADAR_FIELD_ID = 57;
        static constexpr SQLUSMALLINT VPOBT_VESSEL_FIELD_ID = 58;
        static constexpr SQLUSMALLINT RST_RADOME_FIELD_ID = 59;

        ComplexTimeseriesCatalogElementColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Catalog( ) const
        {
            return catalog_;
        }
        const FixedDBWideString<100>& Name( ) const
        {
            return name_;
        }
        const DBTimeSpan& TimeseriesMaxRetention( ) const
        {
            return tMaxRetention_;
        }
        const DBGuid& AisAidToNavigationOffPositionTimeseriesAidToNavigation( ) const
        {
            return aatnoptAidToNavigation_;
        }
        const DBGuid& DeviceEnabledTimeseriesDevice( ) const
        {
            return detDevice_;
        }
        const DBGuid& MediaProxySessionEnabledTimeseriesProxySession( ) const
        {
            return mpsetProxySession_;
        }
        const DBGuid& MediaServiceEnabledTimeseriesService( ) const
        {
            return msetService_;
        }
        const DBGuid& RadarAutomaticSensitivityTimeControlTimeseriesRadar( ) const
        {
            return rastctRadar_;
        }
        const DBGuid& RadarBlankSector1TimeseriesRadar( ) const
        {
            return rbs1tRadar_;
        }
        const DBGuid& RadarBlankSector2TimeseriesRadar( ) const
        {
            return rbs2tRadar_;
        }
        const DBGuid& RadarEnableAutomaticFrequencyControlTimeseriesRadar( ) const
        {
            return reafctRadar_;
        }
        const DBGuid& RadarEnableFastTimeConstantTimeseriesRadar( ) const
        {
            return reftctRadar_;
        }
        const DBGuid& RadarEnableSensitivityTimeControlTimeseriesRadar( ) const
        {
            return restctRadar_;
        }
        const DBGuid& RadarPowerOnTimeseriesRadar( ) const
        {
            return rpotRadar_;
        }
        const DBGuid& RadarSaveSettingsTimeseriesRadar( ) const
        {
            return rsstRadar_;
        }
        const DBGuid& RadarTrackingTimeseriesRadar( ) const
        {
            return rttRadar_;
        }
        const DBGuid& GNSSAltitudeTimeseriesGNSSDevice( ) const
        {
            return gatsGNSSDevice_;
        }
        const DBGuid& GNSSLatitudeTimeseriesGNSSDevice( ) const
        {
            return glatsGNSSDevice_;
        }
        const DBGuid& GNSSLongitudeTimeseriesGNSSDevice( ) const
        {
            return glotsGNSSDevice_;
        }
        const DBGuid& GyroCourseTimeseriesGyroDevice( ) const
        {
            return gctGyroDevice_;
        }
        const DBGuid& GyroHeadingMagneticNorthTimeseriesGyroDevice( ) const
        {
            return ghmntGyroDevice_;
        }
        const DBGuid& GyroHeadingTrueNorthTimeseriesGyroDevice( ) const
        {
            return ghtntGyroDevice_;
        }
        const DBGuid& GyroPitchTimeseriesGyroDevice( ) const
        {
            return gptGyroDevice_;
        }
        const DBGuid& GyroRateOfTurnTimeseriesGyroDevice( ) const
        {
            return grottGyroDevice_;
        }
        const DBGuid& GyroRollTimeseriesGyroDevice( ) const
        {
            return grtGyroDevice_;
        }
        const DBGuid& GyroSpeedTimeseriesGyroDevice( ) const
        {
            return gstGyroDevice_;
        }
        const DBGuid& RadarLatitudeTimeseriesRadar( ) const
        {
            return rlatsRadar_;
        }
        const DBGuid& RadarLongitudeTimeseriesRadar( ) const
        {
            return rlotsRadar_;
        }
        const DBGuid& RadomeDewPointTimeseriesRadome( ) const
        {
            return rdptRadome_;
        }
        const DBGuid& RadomePressureTimeseriesRadome( ) const
        {
            return rptRadome_;
        }
        const DBGuid& RadomeTemperatureTimeseriesRadome( ) const
        {
            return rtetsRadome_;
        }
        const DBGuid& VesselDraughtTimeseriesVessel( ) const
        {
            return vdtVessel_;
        }
        const DBGuid& ViewLatitudeTimeseriesView( ) const
        {
            return vlatsView_;
        }
        const DBGuid& ViewLongitudeTimeseriesView( ) const
        {
            return vlotsView_;
        }
        const DBGuid& ViewZoomLevelTimeseriesView( ) const
        {
            return vzltView_;
        }
        const DBGuid& WeatherStationAbsoluteHumidityTimeseriesWeatherStation( ) const
        {
            return wsahtWeatherStation_;
        }
        const DBGuid& WeatherStationAirTemperatureTimeseriesWeatherStation( ) const
        {
            return wsattWeatherStation_;
        }
        const DBGuid& WeatherStationBarometricPressureTimeseriesWeatherStation( ) const
        {
            return wsbptWeatherStation_;
        }
        const DBGuid& WeatherStationDewPointTimeseriesWeatherStation( ) const
        {
            return wsdptWeatherStation_;
        }
        const DBGuid& WeatherStationRelativeHumidityTimeseriesWeatherStation( ) const
        {
            return wsrhtWeatherStation_;
        }
        const DBGuid& WeatherStationWaterTemperatureTimeseriesWeatherStation( ) const
        {
            return wswttWeatherStation_;
        }
        const DBGuid& WeatherStationWindDirectionTimeseriesWeatherStation( ) const
        {
            return wswdtWeatherStation_;
        }
        const DBGuid& WeatherStationWindSpeedTimeseriesWeatherStation( ) const
        {
            return wswstWeatherStation_;
        }
        const DBGuid& AisAidToNavigationPositionTimeseriesAidToNavigation( ) const
        {
            return aatnptAidToNavigation_;
        }
        const DBGuid& RadarAzimuthOffsetTimeseriesRadar( ) const
        {
            return raotRadar_;
        }
        const DBGuid& RadarFastTimeConstantLevelTimeseriesRadar( ) const
        {
            return rftcltRadar_;
        }
        const DBGuid& RadarFastTimeConstantModeTimeseriesRadar( ) const
        {
            return rftcmtRadar_;
        }
        const DBGuid& RadarPulseTimeseriesRadar( ) const
        {
            return raptsRadar_;
        }
        const DBGuid& RadarSector1EndTimeseriesRadar( ) const
        {
            return rs1etRadar_;
        }
        const DBGuid& RadarSector1StartTimeseriesRadar( ) const
        {
            return rs1stRadar_;
        }
        const DBGuid& RadarSector2EndTimeseriesRadar( ) const
        {
            return rs2etRadar_;
        }
        const DBGuid& RadarSector2StartTimeseriesRadar( ) const
        {
            return rs2stRadar_;
        }
        const DBGuid& RadarSensitivityTimeControlLevelTimeseriesRadar( ) const
        {
            return rstcltRadar_;
        }
        const DBGuid& RadarTuningTimeseriesRadar( ) const
        {
            return ratutsRadar_;
        }
        const DBGuid& VesselPersonsOnBoardTimeseriesVessel( ) const
        {
            return vpobtVessel_;
        }
        const DBGuid& RadomeStatusTimeseriesRadome( ) const
        {
            return rstRadome_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, catalog_);
            WriteColumnValue( destination, name_);
            switch( kind_ )
            {
                case Data::Kind::BinaryTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::BooleanTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::AisAidToNavigationOffPositionTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, aatnoptAidToNavigation_);
                }
                break;
                case Data::Kind::DeviceEnabledTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, detDevice_);
                }
                break;
                case Data::Kind::MediaProxySessionEnabledTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, mpsetProxySession_);
                }
                break;
                case Data::Kind::MediaServiceEnabledTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, msetService_);
                }
                break;
                case Data::Kind::RadarAutomaticSensitivityTimeControlTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rastctRadar_);
                }
                break;
                case Data::Kind::RadarBlankSector1Timeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rbs1tRadar_);
                }
                break;
                case Data::Kind::RadarBlankSector2Timeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rbs2tRadar_);
                }
                break;
                case Data::Kind::RadarEnableAutomaticFrequencyControlTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, reafctRadar_);
                }
                break;
                case Data::Kind::RadarEnableFastTimeConstantTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, reftctRadar_);
                }
                break;
                case Data::Kind::RadarEnableSensitivityTimeControlTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, restctRadar_);
                }
                break;
                case Data::Kind::RadarPowerOnTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rpotRadar_);
                }
                break;
                case Data::Kind::RadarSaveSettingsTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rsstRadar_);
                }
                break;
                case Data::Kind::RadarTrackingTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rttRadar_);
                }
                break;
                case Data::Kind::ByteTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::DateTimeTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::DoubleTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::GNSSAltitudeTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, gatsGNSSDevice_);
                }
                break;
                case Data::Kind::GNSSLatitudeTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, glatsGNSSDevice_);
                }
                break;
                case Data::Kind::GNSSLongitudeTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, glotsGNSSDevice_);
                }
                break;
                case Data::Kind::GyroCourseTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, gctGyroDevice_);
                }
                break;
                case Data::Kind::GyroHeadingMagneticNorthTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, ghmntGyroDevice_);
                }
                break;
                case Data::Kind::GyroHeadingTrueNorthTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, ghtntGyroDevice_);
                }
                break;
                case Data::Kind::GyroPitchTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, gptGyroDevice_);
                }
                break;
                case Data::Kind::GyroRateOfTurnTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, grottGyroDevice_);
                }
                break;
                case Data::Kind::GyroRollTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, grtGyroDevice_);
                }
                break;
                case Data::Kind::GyroSpeedTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, gstGyroDevice_);
                }
                break;
                case Data::Kind::RadarLatitudeTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rlatsRadar_);
                }
                break;
                case Data::Kind::RadarLongitudeTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rlotsRadar_);
                }
                break;
                case Data::Kind::RadomeDewPointTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rdptRadome_);
                }
                break;
                case Data::Kind::RadomePressureTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rptRadome_);
                }
                break;
                case Data::Kind::RadomeTemperatureTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rtetsRadome_);
                }
                break;
                case Data::Kind::VesselDraughtTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, vdtVessel_);
                }
                break;
                case Data::Kind::ViewLatitudeTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, vlatsView_);
                }
                break;
                case Data::Kind::ViewLongitudeTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, vlotsView_);
                }
                break;
                case Data::Kind::ViewZoomLevelTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, vzltView_);
                }
                break;
                case Data::Kind::WeatherStationAbsoluteHumidityTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, wsahtWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationAirTemperatureTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, wsattWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationBarometricPressureTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, wsbptWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationDewPointTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, wsdptWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationRelativeHumidityTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, wsrhtWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationWaterTemperatureTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, wswttWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationWindDirectionTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, wswdtWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationWindSpeedTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, wswstWeatherStation_);
                }
                break;
                case Data::Kind::GeoPosition2DTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::AisAidToNavigationPositionTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, aatnptAidToNavigation_);
                }
                break;
                case Data::Kind::GeoPosition3DTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::GuidTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::Int16Timeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::Int32Timeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::RadarAzimuthOffsetTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, raotRadar_);
                }
                break;
                case Data::Kind::RadarFastTimeConstantLevelTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rftcltRadar_);
                }
                break;
                case Data::Kind::RadarFastTimeConstantModeTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rftcmtRadar_);
                }
                break;
                case Data::Kind::RadarPulseTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, raptsRadar_);
                }
                break;
                case Data::Kind::RadarSector1EndTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rs1etRadar_);
                }
                break;
                case Data::Kind::RadarSector1StartTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rs1stRadar_);
                }
                break;
                case Data::Kind::RadarSector2EndTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rs2etRadar_);
                }
                break;
                case Data::Kind::RadarSector2StartTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rs2stRadar_);
                }
                break;
                case Data::Kind::RadarSensitivityTimeControlLevelTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rstcltRadar_);
                }
                break;
                case Data::Kind::RadarTuningTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, ratutsRadar_);
                }
                break;
                case Data::Kind::VesselPersonsOnBoardTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, vpobtVessel_);
                }
                break;
                case Data::Kind::Int64Timeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::Position2DTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::Position3DTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::ReferenceTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::SByteTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::SingleTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::StringTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::TimeSpanTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::UInt16Timeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::UInt32Timeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
                case Data::Kind::RadomeStatusTimeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                    WriteColumnValue( destination, rstRadome_);
                }
                break;
                case Data::Kind::UInt64Timeseries:
                {
                    WriteColumnValue( destination, tMaxRetention_);
                }
                break;
            }
        }
    };

    using ComplexTimeseriesCatalogElementDataReader = SimpleColumnDataReader<ComplexTimeseriesCatalogElementColumnData>;

    class ComplexTimeseriesColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid catalog_;
        FixedDBWideString<100> name_;
        TimeSpan maxRetention_;
        DBGuid aatnoptAidToNavigation_;
        DBGuid detDevice_;
        DBGuid mpsetProxySession_;
        DBGuid msetService_;
        DBGuid rastctRadar_;
        DBGuid rbs1tRadar_;
        DBGuid rbs2tRadar_;
        DBGuid reafctRadar_;
        DBGuid reftctRadar_;
        DBGuid restctRadar_;
        DBGuid rpotRadar_;
        DBGuid rsstRadar_;
        DBGuid rttRadar_;
        DBGuid gatsGNSSDevice_;
        DBGuid glatsGNSSDevice_;
        DBGuid glotsGNSSDevice_;
        DBGuid gctGyroDevice_;
        DBGuid ghmntGyroDevice_;
        DBGuid ghtntGyroDevice_;
        DBGuid gptGyroDevice_;
        DBGuid grottGyroDevice_;
        DBGuid grtGyroDevice_;
        DBGuid gstGyroDevice_;
        DBGuid rlatsRadar_;
        DBGuid rlotsRadar_;
        DBGuid rdptRadome_;
        DBGuid rptRadome_;
        DBGuid rtetsRadome_;
        DBGuid vdtVessel_;
        DBGuid vlatsView_;
        DBGuid vlotsView_;
        DBGuid vzltView_;
        DBGuid wsahtWeatherStation_;
        DBGuid wsattWeatherStation_;
        DBGuid wsbptWeatherStation_;
        DBGuid wsdptWeatherStation_;
        DBGuid wsrhtWeatherStation_;
        DBGuid wswttWeatherStation_;
        DBGuid wswdtWeatherStation_;
        DBGuid wswstWeatherStation_;
        DBGuid aatnptAidToNavigation_;
        DBGuid raotRadar_;
        DBGuid rftcltRadar_;
        DBGuid rftcmtRadar_;
        DBGuid raptsRadar_;
        DBGuid rs1etRadar_;
        DBGuid rs1stRadar_;
        DBGuid rs2etRadar_;
        DBGuid rs2stRadar_;
        DBGuid rstcltRadar_;
        DBGuid ratutsRadar_;
        DBGuid vpobtVessel_;
        DBGuid rstRadome_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT T_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT T_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT T_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT T_CATALOG_FIELD_ID = 4;
        static constexpr SQLUSMALLINT T_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT T_MAXRETENTION_FIELD_ID = 6;
        static constexpr SQLUSMALLINT AATNOPT_AIDTONAVIGATION_FIELD_ID = 7;
        static constexpr SQLUSMALLINT DET_DEVICE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT MPSET_PROXYSESSION_FIELD_ID = 9;
        static constexpr SQLUSMALLINT MSET_SERVICE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT RASTCT_RADAR_FIELD_ID = 11;
        static constexpr SQLUSMALLINT RBS1T_RADAR_FIELD_ID = 12;
        static constexpr SQLUSMALLINT RBS2T_RADAR_FIELD_ID = 13;
        static constexpr SQLUSMALLINT REAFCT_RADAR_FIELD_ID = 14;
        static constexpr SQLUSMALLINT REFTCT_RADAR_FIELD_ID = 15;
        static constexpr SQLUSMALLINT RESTCT_RADAR_FIELD_ID = 16;
        static constexpr SQLUSMALLINT RPOT_RADAR_FIELD_ID = 17;
        static constexpr SQLUSMALLINT RSST_RADAR_FIELD_ID = 18;
        static constexpr SQLUSMALLINT RTT_RADAR_FIELD_ID = 19;
        static constexpr SQLUSMALLINT GATS_GNSSDEVICE_FIELD_ID = 20;
        static constexpr SQLUSMALLINT GLATS_GNSSDEVICE_FIELD_ID = 21;
        static constexpr SQLUSMALLINT GLOTS_GNSSDEVICE_FIELD_ID = 22;
        static constexpr SQLUSMALLINT GCT_GYRODEVICE_FIELD_ID = 23;
        static constexpr SQLUSMALLINT GHMNT_GYRODEVICE_FIELD_ID = 24;
        static constexpr SQLUSMALLINT GHTNT_GYRODEVICE_FIELD_ID = 25;
        static constexpr SQLUSMALLINT GPT_GYRODEVICE_FIELD_ID = 26;
        static constexpr SQLUSMALLINT GROTT_GYRODEVICE_FIELD_ID = 27;
        static constexpr SQLUSMALLINT GRT_GYRODEVICE_FIELD_ID = 28;
        static constexpr SQLUSMALLINT GST_GYRODEVICE_FIELD_ID = 29;
        static constexpr SQLUSMALLINT RLATS_RADAR_FIELD_ID = 30;
        static constexpr SQLUSMALLINT RLOTS_RADAR_FIELD_ID = 31;
        static constexpr SQLUSMALLINT RDPT_RADOME_FIELD_ID = 32;
        static constexpr SQLUSMALLINT RPT_RADOME_FIELD_ID = 33;
        static constexpr SQLUSMALLINT RTETS_RADOME_FIELD_ID = 34;
        static constexpr SQLUSMALLINT VDT_VESSEL_FIELD_ID = 35;
        static constexpr SQLUSMALLINT VLATS_VIEW_FIELD_ID = 36;
        static constexpr SQLUSMALLINT VLOTS_VIEW_FIELD_ID = 37;
        static constexpr SQLUSMALLINT VZLT_VIEW_FIELD_ID = 38;
        static constexpr SQLUSMALLINT WSAHT_WEATHERSTATION_FIELD_ID = 39;
        static constexpr SQLUSMALLINT WSATT_WEATHERSTATION_FIELD_ID = 40;
        static constexpr SQLUSMALLINT WSBPT_WEATHERSTATION_FIELD_ID = 41;
        static constexpr SQLUSMALLINT WSDPT_WEATHERSTATION_FIELD_ID = 42;
        static constexpr SQLUSMALLINT WSRHT_WEATHERSTATION_FIELD_ID = 43;
        static constexpr SQLUSMALLINT WSWTT_WEATHERSTATION_FIELD_ID = 44;
        static constexpr SQLUSMALLINT WSWDT_WEATHERSTATION_FIELD_ID = 45;
        static constexpr SQLUSMALLINT WSWST_WEATHERSTATION_FIELD_ID = 46;
        static constexpr SQLUSMALLINT AATNPT_AIDTONAVIGATION_FIELD_ID = 47;
        static constexpr SQLUSMALLINT RAOT_RADAR_FIELD_ID = 48;
        static constexpr SQLUSMALLINT RFTCLT_RADAR_FIELD_ID = 49;
        static constexpr SQLUSMALLINT RFTCMT_RADAR_FIELD_ID = 50;
        static constexpr SQLUSMALLINT RAPTS_RADAR_FIELD_ID = 51;
        static constexpr SQLUSMALLINT RS1ET_RADAR_FIELD_ID = 52;
        static constexpr SQLUSMALLINT RS1ST_RADAR_FIELD_ID = 53;
        static constexpr SQLUSMALLINT RS2ET_RADAR_FIELD_ID = 54;
        static constexpr SQLUSMALLINT RS2ST_RADAR_FIELD_ID = 55;
        static constexpr SQLUSMALLINT RSTCLT_RADAR_FIELD_ID = 56;
        static constexpr SQLUSMALLINT RATUTS_RADAR_FIELD_ID = 57;
        static constexpr SQLUSMALLINT VPOBT_VESSEL_FIELD_ID = 58;
        static constexpr SQLUSMALLINT RST_RADOME_FIELD_ID = 59;

        ComplexTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Catalog( ) const
        {
            return catalog_;
        }
        const FixedDBWideString<100>& Name( ) const
        {
            return name_;
        }
        const TimeSpan& MaxRetention( ) const
        {
            return maxRetention_;
        }
        const DBGuid& AisAidToNavigationOffPositionTimeseriesAidToNavigation( ) const
        {
            return aatnoptAidToNavigation_;
        }
        const DBGuid& DeviceEnabledTimeseriesDevice( ) const
        {
            return detDevice_;
        }
        const DBGuid& MediaProxySessionEnabledTimeseriesProxySession( ) const
        {
            return mpsetProxySession_;
        }
        const DBGuid& MediaServiceEnabledTimeseriesService( ) const
        {
            return msetService_;
        }
        const DBGuid& RadarAutomaticSensitivityTimeControlTimeseriesRadar( ) const
        {
            return rastctRadar_;
        }
        const DBGuid& RadarBlankSector1TimeseriesRadar( ) const
        {
            return rbs1tRadar_;
        }
        const DBGuid& RadarBlankSector2TimeseriesRadar( ) const
        {
            return rbs2tRadar_;
        }
        const DBGuid& RadarEnableAutomaticFrequencyControlTimeseriesRadar( ) const
        {
            return reafctRadar_;
        }
        const DBGuid& RadarEnableFastTimeConstantTimeseriesRadar( ) const
        {
            return reftctRadar_;
        }
        const DBGuid& RadarEnableSensitivityTimeControlTimeseriesRadar( ) const
        {
            return restctRadar_;
        }
        const DBGuid& RadarPowerOnTimeseriesRadar( ) const
        {
            return rpotRadar_;
        }
        const DBGuid& RadarSaveSettingsTimeseriesRadar( ) const
        {
            return rsstRadar_;
        }
        const DBGuid& RadarTrackingTimeseriesRadar( ) const
        {
            return rttRadar_;
        }
        const DBGuid& GNSSAltitudeTimeseriesGNSSDevice( ) const
        {
            return gatsGNSSDevice_;
        }
        const DBGuid& GNSSLatitudeTimeseriesGNSSDevice( ) const
        {
            return glatsGNSSDevice_;
        }
        const DBGuid& GNSSLongitudeTimeseriesGNSSDevice( ) const
        {
            return glotsGNSSDevice_;
        }
        const DBGuid& GyroCourseTimeseriesGyroDevice( ) const
        {
            return gctGyroDevice_;
        }
        const DBGuid& GyroHeadingMagneticNorthTimeseriesGyroDevice( ) const
        {
            return ghmntGyroDevice_;
        }
        const DBGuid& GyroHeadingTrueNorthTimeseriesGyroDevice( ) const
        {
            return ghtntGyroDevice_;
        }
        const DBGuid& GyroPitchTimeseriesGyroDevice( ) const
        {
            return gptGyroDevice_;
        }
        const DBGuid& GyroRateOfTurnTimeseriesGyroDevice( ) const
        {
            return grottGyroDevice_;
        }
        const DBGuid& GyroRollTimeseriesGyroDevice( ) const
        {
            return grtGyroDevice_;
        }
        const DBGuid& GyroSpeedTimeseriesGyroDevice( ) const
        {
            return gstGyroDevice_;
        }
        const DBGuid& RadarLatitudeTimeseriesRadar( ) const
        {
            return rlatsRadar_;
        }
        const DBGuid& RadarLongitudeTimeseriesRadar( ) const
        {
            return rlotsRadar_;
        }
        const DBGuid& RadomeDewPointTimeseriesRadome( ) const
        {
            return rdptRadome_;
        }
        const DBGuid& RadomePressureTimeseriesRadome( ) const
        {
            return rptRadome_;
        }
        const DBGuid& RadomeTemperatureTimeseriesRadome( ) const
        {
            return rtetsRadome_;
        }
        const DBGuid& VesselDraughtTimeseriesVessel( ) const
        {
            return vdtVessel_;
        }
        const DBGuid& ViewLatitudeTimeseriesView( ) const
        {
            return vlatsView_;
        }
        const DBGuid& ViewLongitudeTimeseriesView( ) const
        {
            return vlotsView_;
        }
        const DBGuid& ViewZoomLevelTimeseriesView( ) const
        {
            return vzltView_;
        }
        const DBGuid& WeatherStationAbsoluteHumidityTimeseriesWeatherStation( ) const
        {
            return wsahtWeatherStation_;
        }
        const DBGuid& WeatherStationAirTemperatureTimeseriesWeatherStation( ) const
        {
            return wsattWeatherStation_;
        }
        const DBGuid& WeatherStationBarometricPressureTimeseriesWeatherStation( ) const
        {
            return wsbptWeatherStation_;
        }
        const DBGuid& WeatherStationDewPointTimeseriesWeatherStation( ) const
        {
            return wsdptWeatherStation_;
        }
        const DBGuid& WeatherStationRelativeHumidityTimeseriesWeatherStation( ) const
        {
            return wsrhtWeatherStation_;
        }
        const DBGuid& WeatherStationWaterTemperatureTimeseriesWeatherStation( ) const
        {
            return wswttWeatherStation_;
        }
        const DBGuid& WeatherStationWindDirectionTimeseriesWeatherStation( ) const
        {
            return wswdtWeatherStation_;
        }
        const DBGuid& WeatherStationWindSpeedTimeseriesWeatherStation( ) const
        {
            return wswstWeatherStation_;
        }
        const DBGuid& AisAidToNavigationPositionTimeseriesAidToNavigation( ) const
        {
            return aatnptAidToNavigation_;
        }
        const DBGuid& RadarAzimuthOffsetTimeseriesRadar( ) const
        {
            return raotRadar_;
        }
        const DBGuid& RadarFastTimeConstantLevelTimeseriesRadar( ) const
        {
            return rftcltRadar_;
        }
        const DBGuid& RadarFastTimeConstantModeTimeseriesRadar( ) const
        {
            return rftcmtRadar_;
        }
        const DBGuid& RadarPulseTimeseriesRadar( ) const
        {
            return raptsRadar_;
        }
        const DBGuid& RadarSector1EndTimeseriesRadar( ) const
        {
            return rs1etRadar_;
        }
        const DBGuid& RadarSector1StartTimeseriesRadar( ) const
        {
            return rs1stRadar_;
        }
        const DBGuid& RadarSector2EndTimeseriesRadar( ) const
        {
            return rs2etRadar_;
        }
        const DBGuid& RadarSector2StartTimeseriesRadar( ) const
        {
            return rs2stRadar_;
        }
        const DBGuid& RadarSensitivityTimeControlLevelTimeseriesRadar( ) const
        {
            return rstcltRadar_;
        }
        const DBGuid& RadarTuningTimeseriesRadar( ) const
        {
            return ratutsRadar_;
        }
        const DBGuid& VesselPersonsOnBoardTimeseriesVessel( ) const
        {
            return vpobtVessel_;
        }
        const DBGuid& RadomeStatusTimeseriesRadome( ) const
        {
            return rstRadome_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, catalog_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, maxRetention_);
            switch( kind_ )
            {
                case Data::Kind::AisAidToNavigationOffPositionTimeseries:
                {
                    WriteColumnValue( destination, aatnoptAidToNavigation_);
                }
                break;
                case Data::Kind::DeviceEnabledTimeseries:
                {
                    WriteColumnValue( destination, detDevice_);
                }
                break;
                case Data::Kind::MediaProxySessionEnabledTimeseries:
                {
                    WriteColumnValue( destination, mpsetProxySession_);
                }
                break;
                case Data::Kind::MediaServiceEnabledTimeseries:
                {
                    WriteColumnValue( destination, msetService_);
                }
                break;
                case Data::Kind::RadarAutomaticSensitivityTimeControlTimeseries:
                {
                    WriteColumnValue( destination, rastctRadar_);
                }
                break;
                case Data::Kind::RadarBlankSector1Timeseries:
                {
                    WriteColumnValue( destination, rbs1tRadar_);
                }
                break;
                case Data::Kind::RadarBlankSector2Timeseries:
                {
                    WriteColumnValue( destination, rbs2tRadar_);
                }
                break;
                case Data::Kind::RadarEnableAutomaticFrequencyControlTimeseries:
                {
                    WriteColumnValue( destination, reafctRadar_);
                }
                break;
                case Data::Kind::RadarEnableFastTimeConstantTimeseries:
                {
                    WriteColumnValue( destination, reftctRadar_);
                }
                break;
                case Data::Kind::RadarEnableSensitivityTimeControlTimeseries:
                {
                    WriteColumnValue( destination, restctRadar_);
                }
                break;
                case Data::Kind::RadarPowerOnTimeseries:
                {
                    WriteColumnValue( destination, rpotRadar_);
                }
                break;
                case Data::Kind::RadarSaveSettingsTimeseries:
                {
                    WriteColumnValue( destination, rsstRadar_);
                }
                break;
                case Data::Kind::RadarTrackingTimeseries:
                {
                    WriteColumnValue( destination, rttRadar_);
                }
                break;
                case Data::Kind::GNSSAltitudeTimeseries:
                {
                    WriteColumnValue( destination, gatsGNSSDevice_);
                }
                break;
                case Data::Kind::GNSSLatitudeTimeseries:
                {
                    WriteColumnValue( destination, glatsGNSSDevice_);
                }
                break;
                case Data::Kind::GNSSLongitudeTimeseries:
                {
                    WriteColumnValue( destination, glotsGNSSDevice_);
                }
                break;
                case Data::Kind::GyroCourseTimeseries:
                {
                    WriteColumnValue( destination, gctGyroDevice_);
                }
                break;
                case Data::Kind::GyroHeadingMagneticNorthTimeseries:
                {
                    WriteColumnValue( destination, ghmntGyroDevice_);
                }
                break;
                case Data::Kind::GyroHeadingTrueNorthTimeseries:
                {
                    WriteColumnValue( destination, ghtntGyroDevice_);
                }
                break;
                case Data::Kind::GyroPitchTimeseries:
                {
                    WriteColumnValue( destination, gptGyroDevice_);
                }
                break;
                case Data::Kind::GyroRateOfTurnTimeseries:
                {
                    WriteColumnValue( destination, grottGyroDevice_);
                }
                break;
                case Data::Kind::GyroRollTimeseries:
                {
                    WriteColumnValue( destination, grtGyroDevice_);
                }
                break;
                case Data::Kind::GyroSpeedTimeseries:
                {
                    WriteColumnValue( destination, gstGyroDevice_);
                }
                break;
                case Data::Kind::RadarLatitudeTimeseries:
                {
                    WriteColumnValue( destination, rlatsRadar_);
                }
                break;
                case Data::Kind::RadarLongitudeTimeseries:
                {
                    WriteColumnValue( destination, rlotsRadar_);
                }
                break;
                case Data::Kind::RadomeDewPointTimeseries:
                {
                    WriteColumnValue( destination, rdptRadome_);
                }
                break;
                case Data::Kind::RadomePressureTimeseries:
                {
                    WriteColumnValue( destination, rptRadome_);
                }
                break;
                case Data::Kind::RadomeTemperatureTimeseries:
                {
                    WriteColumnValue( destination, rtetsRadome_);
                }
                break;
                case Data::Kind::VesselDraughtTimeseries:
                {
                    WriteColumnValue( destination, vdtVessel_);
                }
                break;
                case Data::Kind::ViewLatitudeTimeseries:
                {
                    WriteColumnValue( destination, vlatsView_);
                }
                break;
                case Data::Kind::ViewLongitudeTimeseries:
                {
                    WriteColumnValue( destination, vlotsView_);
                }
                break;
                case Data::Kind::ViewZoomLevelTimeseries:
                {
                    WriteColumnValue( destination, vzltView_);
                }
                break;
                case Data::Kind::WeatherStationAbsoluteHumidityTimeseries:
                {
                    WriteColumnValue( destination, wsahtWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationAirTemperatureTimeseries:
                {
                    WriteColumnValue( destination, wsattWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationBarometricPressureTimeseries:
                {
                    WriteColumnValue( destination, wsbptWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationDewPointTimeseries:
                {
                    WriteColumnValue( destination, wsdptWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationRelativeHumidityTimeseries:
                {
                    WriteColumnValue( destination, wsrhtWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationWaterTemperatureTimeseries:
                {
                    WriteColumnValue( destination, wswttWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationWindDirectionTimeseries:
                {
                    WriteColumnValue( destination, wswdtWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationWindSpeedTimeseries:
                {
                    WriteColumnValue( destination, wswstWeatherStation_);
                }
                break;
                case Data::Kind::AisAidToNavigationPositionTimeseries:
                {
                    WriteColumnValue( destination, aatnptAidToNavigation_);
                }
                break;
                case Data::Kind::RadarAzimuthOffsetTimeseries:
                {
                    WriteColumnValue( destination, raotRadar_);
                }
                break;
                case Data::Kind::RadarFastTimeConstantLevelTimeseries:
                {
                    WriteColumnValue( destination, rftcltRadar_);
                }
                break;
                case Data::Kind::RadarFastTimeConstantModeTimeseries:
                {
                    WriteColumnValue( destination, rftcmtRadar_);
                }
                break;
                case Data::Kind::RadarPulseTimeseries:
                {
                    WriteColumnValue( destination, raptsRadar_);
                }
                break;
                case Data::Kind::RadarSector1EndTimeseries:
                {
                    WriteColumnValue( destination, rs1etRadar_);
                }
                break;
                case Data::Kind::RadarSector1StartTimeseries:
                {
                    WriteColumnValue( destination, rs1stRadar_);
                }
                break;
                case Data::Kind::RadarSector2EndTimeseries:
                {
                    WriteColumnValue( destination, rs2etRadar_);
                }
                break;
                case Data::Kind::RadarSector2StartTimeseries:
                {
                    WriteColumnValue( destination, rs2stRadar_);
                }
                break;
                case Data::Kind::RadarSensitivityTimeControlLevelTimeseries:
                {
                    WriteColumnValue( destination, rstcltRadar_);
                }
                break;
                case Data::Kind::RadarTuningTimeseries:
                {
                    WriteColumnValue( destination, ratutsRadar_);
                }
                break;
                case Data::Kind::VesselPersonsOnBoardTimeseries:
                {
                    WriteColumnValue( destination, vpobtVessel_);
                }
                break;
                case Data::Kind::RadomeStatusTimeseries:
                {
                    WriteColumnValue( destination, rstRadome_);
                }
                break;
            }
        }
    };

    using ComplexTimeseriesDataReader = SimpleColumnDataReader<ComplexTimeseriesColumnData>;

    class ComplexBooleanTimeseriesColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid catalog_;
        FixedDBWideString<100> name_;
        TimeSpan maxRetention_;
        DBGuid aatnoptAidToNavigation_;
        DBGuid detDevice_;
        DBGuid mpsetProxySession_;
        DBGuid msetService_;
        DBGuid rastctRadar_;
        DBGuid rbs1tRadar_;
        DBGuid rbs2tRadar_;
        DBGuid reafctRadar_;
        DBGuid reftctRadar_;
        DBGuid restctRadar_;
        DBGuid rpotRadar_;
        DBGuid rsstRadar_;
        DBGuid rttRadar_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT BOTS_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT BOTS_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT BOTS_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT BOTS_CATALOG_FIELD_ID = 4;
        static constexpr SQLUSMALLINT BOTS_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT BOTS_MAXRETENTION_FIELD_ID = 6;
        static constexpr SQLUSMALLINT AATNOPT_AIDTONAVIGATION_FIELD_ID = 7;
        static constexpr SQLUSMALLINT DET_DEVICE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT MPSET_PROXYSESSION_FIELD_ID = 9;
        static constexpr SQLUSMALLINT MSET_SERVICE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT RASTCT_RADAR_FIELD_ID = 11;
        static constexpr SQLUSMALLINT RBS1T_RADAR_FIELD_ID = 12;
        static constexpr SQLUSMALLINT RBS2T_RADAR_FIELD_ID = 13;
        static constexpr SQLUSMALLINT REAFCT_RADAR_FIELD_ID = 14;
        static constexpr SQLUSMALLINT REFTCT_RADAR_FIELD_ID = 15;
        static constexpr SQLUSMALLINT RESTCT_RADAR_FIELD_ID = 16;
        static constexpr SQLUSMALLINT RPOT_RADAR_FIELD_ID = 17;
        static constexpr SQLUSMALLINT RSST_RADAR_FIELD_ID = 18;
        static constexpr SQLUSMALLINT RTT_RADAR_FIELD_ID = 19;

        ComplexBooleanTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Catalog( ) const
        {
            return catalog_;
        }
        const FixedDBWideString<100>& Name( ) const
        {
            return name_;
        }
        const TimeSpan& MaxRetention( ) const
        {
            return maxRetention_;
        }
        const DBGuid& AisAidToNavigationOffPositionTimeseriesAidToNavigation( ) const
        {
            return aatnoptAidToNavigation_;
        }
        const DBGuid& DeviceEnabledTimeseriesDevice( ) const
        {
            return detDevice_;
        }
        const DBGuid& MediaProxySessionEnabledTimeseriesProxySession( ) const
        {
            return mpsetProxySession_;
        }
        const DBGuid& MediaServiceEnabledTimeseriesService( ) const
        {
            return msetService_;
        }
        const DBGuid& RadarAutomaticSensitivityTimeControlTimeseriesRadar( ) const
        {
            return rastctRadar_;
        }
        const DBGuid& RadarBlankSector1TimeseriesRadar( ) const
        {
            return rbs1tRadar_;
        }
        const DBGuid& RadarBlankSector2TimeseriesRadar( ) const
        {
            return rbs2tRadar_;
        }
        const DBGuid& RadarEnableAutomaticFrequencyControlTimeseriesRadar( ) const
        {
            return reafctRadar_;
        }
        const DBGuid& RadarEnableFastTimeConstantTimeseriesRadar( ) const
        {
            return reftctRadar_;
        }
        const DBGuid& RadarEnableSensitivityTimeControlTimeseriesRadar( ) const
        {
            return restctRadar_;
        }
        const DBGuid& RadarPowerOnTimeseriesRadar( ) const
        {
            return rpotRadar_;
        }
        const DBGuid& RadarSaveSettingsTimeseriesRadar( ) const
        {
            return rsstRadar_;
        }
        const DBGuid& RadarTrackingTimeseriesRadar( ) const
        {
            return rttRadar_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, catalog_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, maxRetention_);
            switch( kind_ )
            {
                case Data::Kind::AisAidToNavigationOffPositionTimeseries:
                {
                    WriteColumnValue( destination, aatnoptAidToNavigation_);
                }
                break;
                case Data::Kind::DeviceEnabledTimeseries:
                {
                    WriteColumnValue( destination, detDevice_);
                }
                break;
                case Data::Kind::MediaProxySessionEnabledTimeseries:
                {
                    WriteColumnValue( destination, mpsetProxySession_);
                }
                break;
                case Data::Kind::MediaServiceEnabledTimeseries:
                {
                    WriteColumnValue( destination, msetService_);
                }
                break;
                case Data::Kind::RadarAutomaticSensitivityTimeControlTimeseries:
                {
                    WriteColumnValue( destination, rastctRadar_);
                }
                break;
                case Data::Kind::RadarBlankSector1Timeseries:
                {
                    WriteColumnValue( destination, rbs1tRadar_);
                }
                break;
                case Data::Kind::RadarBlankSector2Timeseries:
                {
                    WriteColumnValue( destination, rbs2tRadar_);
                }
                break;
                case Data::Kind::RadarEnableAutomaticFrequencyControlTimeseries:
                {
                    WriteColumnValue( destination, reafctRadar_);
                }
                break;
                case Data::Kind::RadarEnableFastTimeConstantTimeseries:
                {
                    WriteColumnValue( destination, reftctRadar_);
                }
                break;
                case Data::Kind::RadarEnableSensitivityTimeControlTimeseries:
                {
                    WriteColumnValue( destination, restctRadar_);
                }
                break;
                case Data::Kind::RadarPowerOnTimeseries:
                {
                    WriteColumnValue( destination, rpotRadar_);
                }
                break;
                case Data::Kind::RadarSaveSettingsTimeseries:
                {
                    WriteColumnValue( destination, rsstRadar_);
                }
                break;
                case Data::Kind::RadarTrackingTimeseries:
                {
                    WriteColumnValue( destination, rttRadar_);
                }
                break;
            }
        }
    };

    using ComplexBooleanTimeseriesDataReader = SimpleColumnDataReader<ComplexBooleanTimeseriesColumnData>;

    class ComplexDoubleTimeseriesColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid catalog_;
        FixedDBWideString<100> name_;
        TimeSpan maxRetention_;
        DBGuid gatsGNSSDevice_;
        DBGuid glatsGNSSDevice_;
        DBGuid glotsGNSSDevice_;
        DBGuid gctGyroDevice_;
        DBGuid ghmntGyroDevice_;
        DBGuid ghtntGyroDevice_;
        DBGuid gptGyroDevice_;
        DBGuid grottGyroDevice_;
        DBGuid grtGyroDevice_;
        DBGuid gstGyroDevice_;
        DBGuid rlatsRadar_;
        DBGuid rlotsRadar_;
        DBGuid rdptRadome_;
        DBGuid rptRadome_;
        DBGuid rtetsRadome_;
        DBGuid vdtVessel_;
        DBGuid vlatsView_;
        DBGuid vlotsView_;
        DBGuid vzltView_;
        DBGuid wsahtWeatherStation_;
        DBGuid wsattWeatherStation_;
        DBGuid wsbptWeatherStation_;
        DBGuid wsdptWeatherStation_;
        DBGuid wsrhtWeatherStation_;
        DBGuid wswttWeatherStation_;
        DBGuid wswdtWeatherStation_;
        DBGuid wswstWeatherStation_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT DT_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT DT_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT DT_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT DT_CATALOG_FIELD_ID = 4;
        static constexpr SQLUSMALLINT DT_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT DT_MAXRETENTION_FIELD_ID = 6;
        static constexpr SQLUSMALLINT GATS_GNSSDEVICE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT GLATS_GNSSDEVICE_FIELD_ID = 8;
        static constexpr SQLUSMALLINT GLOTS_GNSSDEVICE_FIELD_ID = 9;
        static constexpr SQLUSMALLINT GCT_GYRODEVICE_FIELD_ID = 10;
        static constexpr SQLUSMALLINT GHMNT_GYRODEVICE_FIELD_ID = 11;
        static constexpr SQLUSMALLINT GHTNT_GYRODEVICE_FIELD_ID = 12;
        static constexpr SQLUSMALLINT GPT_GYRODEVICE_FIELD_ID = 13;
        static constexpr SQLUSMALLINT GROTT_GYRODEVICE_FIELD_ID = 14;
        static constexpr SQLUSMALLINT GRT_GYRODEVICE_FIELD_ID = 15;
        static constexpr SQLUSMALLINT GST_GYRODEVICE_FIELD_ID = 16;
        static constexpr SQLUSMALLINT RLATS_RADAR_FIELD_ID = 17;
        static constexpr SQLUSMALLINT RLOTS_RADAR_FIELD_ID = 18;
        static constexpr SQLUSMALLINT RDPT_RADOME_FIELD_ID = 19;
        static constexpr SQLUSMALLINT RPT_RADOME_FIELD_ID = 20;
        static constexpr SQLUSMALLINT RTETS_RADOME_FIELD_ID = 21;
        static constexpr SQLUSMALLINT VDT_VESSEL_FIELD_ID = 22;
        static constexpr SQLUSMALLINT VLATS_VIEW_FIELD_ID = 23;
        static constexpr SQLUSMALLINT VLOTS_VIEW_FIELD_ID = 24;
        static constexpr SQLUSMALLINT VZLT_VIEW_FIELD_ID = 25;
        static constexpr SQLUSMALLINT WSAHT_WEATHERSTATION_FIELD_ID = 26;
        static constexpr SQLUSMALLINT WSATT_WEATHERSTATION_FIELD_ID = 27;
        static constexpr SQLUSMALLINT WSBPT_WEATHERSTATION_FIELD_ID = 28;
        static constexpr SQLUSMALLINT WSDPT_WEATHERSTATION_FIELD_ID = 29;
        static constexpr SQLUSMALLINT WSRHT_WEATHERSTATION_FIELD_ID = 30;
        static constexpr SQLUSMALLINT WSWTT_WEATHERSTATION_FIELD_ID = 31;
        static constexpr SQLUSMALLINT WSWDT_WEATHERSTATION_FIELD_ID = 32;
        static constexpr SQLUSMALLINT WSWST_WEATHERSTATION_FIELD_ID = 33;

        ComplexDoubleTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Catalog( ) const
        {
            return catalog_;
        }
        const FixedDBWideString<100>& Name( ) const
        {
            return name_;
        }
        const TimeSpan& MaxRetention( ) const
        {
            return maxRetention_;
        }
        const DBGuid& GNSSAltitudeTimeseriesGNSSDevice( ) const
        {
            return gatsGNSSDevice_;
        }
        const DBGuid& GNSSLatitudeTimeseriesGNSSDevice( ) const
        {
            return glatsGNSSDevice_;
        }
        const DBGuid& GNSSLongitudeTimeseriesGNSSDevice( ) const
        {
            return glotsGNSSDevice_;
        }
        const DBGuid& GyroCourseTimeseriesGyroDevice( ) const
        {
            return gctGyroDevice_;
        }
        const DBGuid& GyroHeadingMagneticNorthTimeseriesGyroDevice( ) const
        {
            return ghmntGyroDevice_;
        }
        const DBGuid& GyroHeadingTrueNorthTimeseriesGyroDevice( ) const
        {
            return ghtntGyroDevice_;
        }
        const DBGuid& GyroPitchTimeseriesGyroDevice( ) const
        {
            return gptGyroDevice_;
        }
        const DBGuid& GyroRateOfTurnTimeseriesGyroDevice( ) const
        {
            return grottGyroDevice_;
        }
        const DBGuid& GyroRollTimeseriesGyroDevice( ) const
        {
            return grtGyroDevice_;
        }
        const DBGuid& GyroSpeedTimeseriesGyroDevice( ) const
        {
            return gstGyroDevice_;
        }
        const DBGuid& RadarLatitudeTimeseriesRadar( ) const
        {
            return rlatsRadar_;
        }
        const DBGuid& RadarLongitudeTimeseriesRadar( ) const
        {
            return rlotsRadar_;
        }
        const DBGuid& RadomeDewPointTimeseriesRadome( ) const
        {
            return rdptRadome_;
        }
        const DBGuid& RadomePressureTimeseriesRadome( ) const
        {
            return rptRadome_;
        }
        const DBGuid& RadomeTemperatureTimeseriesRadome( ) const
        {
            return rtetsRadome_;
        }
        const DBGuid& VesselDraughtTimeseriesVessel( ) const
        {
            return vdtVessel_;
        }
        const DBGuid& ViewLatitudeTimeseriesView( ) const
        {
            return vlatsView_;
        }
        const DBGuid& ViewLongitudeTimeseriesView( ) const
        {
            return vlotsView_;
        }
        const DBGuid& ViewZoomLevelTimeseriesView( ) const
        {
            return vzltView_;
        }
        const DBGuid& WeatherStationAbsoluteHumidityTimeseriesWeatherStation( ) const
        {
            return wsahtWeatherStation_;
        }
        const DBGuid& WeatherStationAirTemperatureTimeseriesWeatherStation( ) const
        {
            return wsattWeatherStation_;
        }
        const DBGuid& WeatherStationBarometricPressureTimeseriesWeatherStation( ) const
        {
            return wsbptWeatherStation_;
        }
        const DBGuid& WeatherStationDewPointTimeseriesWeatherStation( ) const
        {
            return wsdptWeatherStation_;
        }
        const DBGuid& WeatherStationRelativeHumidityTimeseriesWeatherStation( ) const
        {
            return wsrhtWeatherStation_;
        }
        const DBGuid& WeatherStationWaterTemperatureTimeseriesWeatherStation( ) const
        {
            return wswttWeatherStation_;
        }
        const DBGuid& WeatherStationWindDirectionTimeseriesWeatherStation( ) const
        {
            return wswdtWeatherStation_;
        }
        const DBGuid& WeatherStationWindSpeedTimeseriesWeatherStation( ) const
        {
            return wswstWeatherStation_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, catalog_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, maxRetention_);
            switch( kind_ )
            {
                case Data::Kind::GNSSAltitudeTimeseries:
                {
                    WriteColumnValue( destination, gatsGNSSDevice_);
                }
                break;
                case Data::Kind::GNSSLatitudeTimeseries:
                {
                    WriteColumnValue( destination, glatsGNSSDevice_);
                }
                break;
                case Data::Kind::GNSSLongitudeTimeseries:
                {
                    WriteColumnValue( destination, glotsGNSSDevice_);
                }
                break;
                case Data::Kind::GyroCourseTimeseries:
                {
                    WriteColumnValue( destination, gctGyroDevice_);
                }
                break;
                case Data::Kind::GyroHeadingMagneticNorthTimeseries:
                {
                    WriteColumnValue( destination, ghmntGyroDevice_);
                }
                break;
                case Data::Kind::GyroHeadingTrueNorthTimeseries:
                {
                    WriteColumnValue( destination, ghtntGyroDevice_);
                }
                break;
                case Data::Kind::GyroPitchTimeseries:
                {
                    WriteColumnValue( destination, gptGyroDevice_);
                }
                break;
                case Data::Kind::GyroRateOfTurnTimeseries:
                {
                    WriteColumnValue( destination, grottGyroDevice_);
                }
                break;
                case Data::Kind::GyroRollTimeseries:
                {
                    WriteColumnValue( destination, grtGyroDevice_);
                }
                break;
                case Data::Kind::GyroSpeedTimeseries:
                {
                    WriteColumnValue( destination, gstGyroDevice_);
                }
                break;
                case Data::Kind::RadarLatitudeTimeseries:
                {
                    WriteColumnValue( destination, rlatsRadar_);
                }
                break;
                case Data::Kind::RadarLongitudeTimeseries:
                {
                    WriteColumnValue( destination, rlotsRadar_);
                }
                break;
                case Data::Kind::RadomeDewPointTimeseries:
                {
                    WriteColumnValue( destination, rdptRadome_);
                }
                break;
                case Data::Kind::RadomePressureTimeseries:
                {
                    WriteColumnValue( destination, rptRadome_);
                }
                break;
                case Data::Kind::RadomeTemperatureTimeseries:
                {
                    WriteColumnValue( destination, rtetsRadome_);
                }
                break;
                case Data::Kind::VesselDraughtTimeseries:
                {
                    WriteColumnValue( destination, vdtVessel_);
                }
                break;
                case Data::Kind::ViewLatitudeTimeseries:
                {
                    WriteColumnValue( destination, vlatsView_);
                }
                break;
                case Data::Kind::ViewLongitudeTimeseries:
                {
                    WriteColumnValue( destination, vlotsView_);
                }
                break;
                case Data::Kind::ViewZoomLevelTimeseries:
                {
                    WriteColumnValue( destination, vzltView_);
                }
                break;
                case Data::Kind::WeatherStationAbsoluteHumidityTimeseries:
                {
                    WriteColumnValue( destination, wsahtWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationAirTemperatureTimeseries:
                {
                    WriteColumnValue( destination, wsattWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationBarometricPressureTimeseries:
                {
                    WriteColumnValue( destination, wsbptWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationDewPointTimeseries:
                {
                    WriteColumnValue( destination, wsdptWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationRelativeHumidityTimeseries:
                {
                    WriteColumnValue( destination, wsrhtWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationWaterTemperatureTimeseries:
                {
                    WriteColumnValue( destination, wswttWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationWindDirectionTimeseries:
                {
                    WriteColumnValue( destination, wswdtWeatherStation_);
                }
                break;
                case Data::Kind::WeatherStationWindSpeedTimeseries:
                {
                    WriteColumnValue( destination, wswstWeatherStation_);
                }
                break;
            }
        }
    };

    using ComplexDoubleTimeseriesDataReader = SimpleColumnDataReader<ComplexDoubleTimeseriesColumnData>;

    class ComplexGeoPosition2DTimeseriesColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid catalog_;
        FixedDBWideString<100> name_;
        TimeSpan maxRetention_;
        DBGuid aatnptAidToNavigation_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT GP2D_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT GP2D_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT GP2D_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT GP2D_CATALOG_FIELD_ID = 4;
        static constexpr SQLUSMALLINT GP2D_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT GP2D_MAXRETENTION_FIELD_ID = 6;
        static constexpr SQLUSMALLINT AATNPT_AIDTONAVIGATION_FIELD_ID = 7;

        ComplexGeoPosition2DTimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Catalog( ) const
        {
            return catalog_;
        }
        const FixedDBWideString<100>& Name( ) const
        {
            return name_;
        }
        const TimeSpan& MaxRetention( ) const
        {
            return maxRetention_;
        }
        const DBGuid& AisAidToNavigationPositionTimeseriesAidToNavigation( ) const
        {
            return aatnptAidToNavigation_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, catalog_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, maxRetention_);
            switch( kind_ )
            {
                case Data::Kind::AisAidToNavigationPositionTimeseries:
                {
                    WriteColumnValue( destination, aatnptAidToNavigation_);
                }
                break;
            }
        }
    };

    using ComplexGeoPosition2DTimeseriesDataReader = SimpleColumnDataReader<ComplexGeoPosition2DTimeseriesColumnData>;

    class ComplexInt32TimeseriesColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid catalog_;
        FixedDBWideString<100> name_;
        TimeSpan maxRetention_;
        DBGuid raotRadar_;
        DBGuid rftcltRadar_;
        DBGuid rftcmtRadar_;
        DBGuid raptsRadar_;
        DBGuid rs1etRadar_;
        DBGuid rs1stRadar_;
        DBGuid rs2etRadar_;
        DBGuid rs2stRadar_;
        DBGuid rstcltRadar_;
        DBGuid ratutsRadar_;
        DBGuid vpobtVessel_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT I32T_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT I32T_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT I32T_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT I32T_CATALOG_FIELD_ID = 4;
        static constexpr SQLUSMALLINT I32T_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT I32T_MAXRETENTION_FIELD_ID = 6;
        static constexpr SQLUSMALLINT RAOT_RADAR_FIELD_ID = 7;
        static constexpr SQLUSMALLINT RFTCLT_RADAR_FIELD_ID = 8;
        static constexpr SQLUSMALLINT RFTCMT_RADAR_FIELD_ID = 9;
        static constexpr SQLUSMALLINT RAPTS_RADAR_FIELD_ID = 10;
        static constexpr SQLUSMALLINT RS1ET_RADAR_FIELD_ID = 11;
        static constexpr SQLUSMALLINT RS1ST_RADAR_FIELD_ID = 12;
        static constexpr SQLUSMALLINT RS2ET_RADAR_FIELD_ID = 13;
        static constexpr SQLUSMALLINT RS2ST_RADAR_FIELD_ID = 14;
        static constexpr SQLUSMALLINT RSTCLT_RADAR_FIELD_ID = 15;
        static constexpr SQLUSMALLINT RATUTS_RADAR_FIELD_ID = 16;
        static constexpr SQLUSMALLINT VPOBT_VESSEL_FIELD_ID = 17;

        ComplexInt32TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Catalog( ) const
        {
            return catalog_;
        }
        const FixedDBWideString<100>& Name( ) const
        {
            return name_;
        }
        const TimeSpan& MaxRetention( ) const
        {
            return maxRetention_;
        }
        const DBGuid& RadarAzimuthOffsetTimeseriesRadar( ) const
        {
            return raotRadar_;
        }
        const DBGuid& RadarFastTimeConstantLevelTimeseriesRadar( ) const
        {
            return rftcltRadar_;
        }
        const DBGuid& RadarFastTimeConstantModeTimeseriesRadar( ) const
        {
            return rftcmtRadar_;
        }
        const DBGuid& RadarPulseTimeseriesRadar( ) const
        {
            return raptsRadar_;
        }
        const DBGuid& RadarSector1EndTimeseriesRadar( ) const
        {
            return rs1etRadar_;
        }
        const DBGuid& RadarSector1StartTimeseriesRadar( ) const
        {
            return rs1stRadar_;
        }
        const DBGuid& RadarSector2EndTimeseriesRadar( ) const
        {
            return rs2etRadar_;
        }
        const DBGuid& RadarSector2StartTimeseriesRadar( ) const
        {
            return rs2stRadar_;
        }
        const DBGuid& RadarSensitivityTimeControlLevelTimeseriesRadar( ) const
        {
            return rstcltRadar_;
        }
        const DBGuid& RadarTuningTimeseriesRadar( ) const
        {
            return ratutsRadar_;
        }
        const DBGuid& VesselPersonsOnBoardTimeseriesVessel( ) const
        {
            return vpobtVessel_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, catalog_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, maxRetention_);
            switch( kind_ )
            {
                case Data::Kind::RadarAzimuthOffsetTimeseries:
                {
                    WriteColumnValue( destination, raotRadar_);
                }
                break;
                case Data::Kind::RadarFastTimeConstantLevelTimeseries:
                {
                    WriteColumnValue( destination, rftcltRadar_);
                }
                break;
                case Data::Kind::RadarFastTimeConstantModeTimeseries:
                {
                    WriteColumnValue( destination, rftcmtRadar_);
                }
                break;
                case Data::Kind::RadarPulseTimeseries:
                {
                    WriteColumnValue( destination, raptsRadar_);
                }
                break;
                case Data::Kind::RadarSector1EndTimeseries:
                {
                    WriteColumnValue( destination, rs1etRadar_);
                }
                break;
                case Data::Kind::RadarSector1StartTimeseries:
                {
                    WriteColumnValue( destination, rs1stRadar_);
                }
                break;
                case Data::Kind::RadarSector2EndTimeseries:
                {
                    WriteColumnValue( destination, rs2etRadar_);
                }
                break;
                case Data::Kind::RadarSector2StartTimeseries:
                {
                    WriteColumnValue( destination, rs2stRadar_);
                }
                break;
                case Data::Kind::RadarSensitivityTimeControlLevelTimeseries:
                {
                    WriteColumnValue( destination, rstcltRadar_);
                }
                break;
                case Data::Kind::RadarTuningTimeseries:
                {
                    WriteColumnValue( destination, ratutsRadar_);
                }
                break;
                case Data::Kind::VesselPersonsOnBoardTimeseries:
                {
                    WriteColumnValue( destination, vpobtVessel_);
                }
                break;
            }
        }
    };

    using ComplexInt32TimeseriesDataReader = SimpleColumnDataReader<ComplexInt32TimeseriesColumnData>;

    class ComplexUInt32TimeseriesColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid catalog_;
        FixedDBWideString<100> name_;
        TimeSpan maxRetention_;
        DBGuid rstRadome_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT U32T_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT U32T_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT U32T_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT U32T_CATALOG_FIELD_ID = 4;
        static constexpr SQLUSMALLINT U32T_NAME_FIELD_ID = 5;
        static constexpr SQLUSMALLINT U32T_MAXRETENTION_FIELD_ID = 6;
        static constexpr SQLUSMALLINT RST_RADOME_FIELD_ID = 7;

        ComplexUInt32TimeseriesColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Catalog( ) const
        {
            return catalog_;
        }
        const FixedDBWideString<100>& Name( ) const
        {
            return name_;
        }
        const TimeSpan& MaxRetention( ) const
        {
            return maxRetention_;
        }
        const DBGuid& RadomeStatusTimeseriesRadome( ) const
        {
            return rstRadome_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, catalog_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, maxRetention_);
            switch( kind_ )
            {
                case Data::Kind::RadomeStatusTimeseries:
                {
                    WriteColumnValue( destination, rstRadome_);
                }
                break;
            }
        }
    };

    using ComplexUInt32TimeseriesDataReader = SimpleColumnDataReader<ComplexUInt32TimeseriesColumnData>;

    class ComplexTrackBaseColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        Guid tracker_;
        Int64 trackNumber_ = 0;
        DateTime timestamp_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT TB_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TB_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT TB_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT TB_TRACKER_FIELD_ID = 4;
        static constexpr SQLUSMALLINT TB_TRACKNUMBER_FIELD_ID = 5;
        static constexpr SQLUSMALLINT TB_TIMESTAMP_FIELD_ID = 6;

        ComplexTrackBaseColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const Guid& Tracker( ) const
        {
            return tracker_;
        }
        Int64 TrackNumber( ) const
        {
            return trackNumber_;
        }
        const DateTime& Timestamp( ) const
        {
            return timestamp_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, tracker_);
            WriteColumnValue( destination, trackNumber_);
            WriteColumnValue( destination, timestamp_);
        }
    };

    using ComplexTrackBaseDataReader = SimpleColumnDataReader<ComplexTrackBaseColumnData>;

    class ComplexZoneColumnData : public BaseColumnData
    {
        Guid id_;
        Data::Kind kind_ = Data::Kind::Unknown;
        Int64 rowVersion_ = 0;
        FixedDBWideString<127> name_;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        Data::ZoneAlarmType alarmType_ = Data::ZoneAlarmType::None;
        TimeSpan alarmTime_;
        TimeSpan radarTrackMinimumLifetime_;
        double speed_ = 0.0;
        UInt32 strokeColor_ = 0;
        UInt32 fillColor_ = 0;
        DBDouble czRadius_;
        DBBinary pzPolygon_;
    public:
        using Base = BaseColumnData;

        static BARRELMAN_EXPORT WideString BaseQuery;
        static BARRELMAN_EXPORT WideString BaseViewName;
        static BARRELMAN_EXPORT WideString ViewAliasName;

        static constexpr SQLUSMALLINT Z_ID_FIELD_ID = 1;
        static constexpr SQLUSMALLINT Z_KIND_FIELD_ID = 1;
        static constexpr SQLUSMALLINT Z_ROWVERSION_FIELD_ID = 3;
        static constexpr SQLUSMALLINT Z_NAME_FIELD_ID = 4;
        static constexpr SQLUSMALLINT Z_LONGITUDE_FIELD_ID = 5;
        static constexpr SQLUSMALLINT Z_LATITUDE_FIELD_ID = 6;
        static constexpr SQLUSMALLINT Z_ALARMTYPE_FIELD_ID = 7;
        static constexpr SQLUSMALLINT Z_ALARMTIME_FIELD_ID = 8;
        static constexpr SQLUSMALLINT Z_RADARTRACKMINIMUMLIFETIME_FIELD_ID = 9;
        static constexpr SQLUSMALLINT Z_SPEED_FIELD_ID = 10;
        static constexpr SQLUSMALLINT Z_STROKECOLOR_FIELD_ID = 11;
        static constexpr SQLUSMALLINT Z_FILLCOLOR_FIELD_ID = 12;
        static constexpr SQLUSMALLINT CZ_RADIUS_FIELD_ID = 13;
        static constexpr SQLUSMALLINT PZ_POLYGON_FIELD_ID = 14;

        ComplexZoneColumnData( ) = default;

        virtual Kind GetKind() const override
        {
            return kind_;
        }

        BARRELMAN_EXPORT void BindColumns( const ODBC::Statement& statement );

        BARRELMAN_EXPORT void ReadUnboundData( const ODBC::Statement& statement );
        const Guid& Id( ) const
        {
            return id_;
        }
        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        const FixedDBWideString<127>& Name( ) const
        {
            return name_;
        }
        double Longitude( ) const
        {
            return longitude_;
        }
        double Latitude( ) const
        {
            return latitude_;
        }
        Data::ZoneAlarmType AlarmType( ) const
        {
            return alarmType_;
        }
        const TimeSpan& AlarmTime( ) const
        {
            return alarmTime_;
        }
        const TimeSpan& RadarTrackMinimumLifetime( ) const
        {
            return radarTrackMinimumLifetime_;
        }
        double Speed( ) const
        {
            return speed_;
        }
        UInt32 StrokeColor( ) const
        {
            return strokeColor_;
        }
        UInt32 FillColor( ) const
        {
            return fillColor_;
        }
        DBDouble CircularZoneRadius( ) const
        {
            return czRadius_;
        }
        const DBBinary& PolygonZonePolygon( ) const
        {
            return pzPolygon_;
        }
        template<IO::StreamWriter StreamT>
        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const
        {
            WriteColumnValue( destination, kind_);
            WriteColumnValue( destination, id_);
            WriteColumnValue( destination, rowVersion_);
            WriteColumnValue( destination, name_);
            WriteColumnValue( destination, longitude_);
            WriteColumnValue( destination, latitude_);
            WriteColumnValue( destination, alarmType_);
            WriteColumnValue( destination, alarmTime_);
            WriteColumnValue( destination, radarTrackMinimumLifetime_);
            WriteColumnValue( destination, speed_);
            WriteColumnValue( destination, strokeColor_);
            WriteColumnValue( destination, fillColor_);
            switch( kind_ )
            {
                case Data::Kind::CircularZone:
                {
                    WriteColumnValue( destination, czRadius_);
                }
                break;
                case Data::Kind::PolygonZone:
                {
                    WriteColumnValue( destination, pzPolygon_);
                }
                break;
            }
        }
    };

    using ComplexZoneDataReader = SimpleColumnDataReader<ComplexZoneColumnData>;

}
#endif
