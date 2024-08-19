#pragma once
#ifndef DATA_ENUMS_H_
#define DATA_ENUMS_H_

#include <HCCDef.h>

namespace Barrelman::Data
{
    using namespace Harlinn::Common::Core;

    enum class Kind : Int32
    {
        Unknown = 0,
        AircraftType = 10000,
        AisMessage = 10100,
        AidToNavigationReportMessage = 10200,
        AisAddressedSafetyRelatedMessage = 10300,
        AisBaseStationReportMessage = 10400,
        AisBinaryAcknowledgeMessage = 10500,
        AisBinaryAddressedMessage = 10600,
        AisBinaryBroadcastMessage = 10700,
        AisDataLinkManagementMessage = 10800,
        AisExtendedClassBCsPositionReportMessage = 10900,
        AisInterrogationMessage = 11000,
        AisPositionReportClassAMessageBase = 11100,
        AisPositionReportClassAAssignedScheduleMessage = 11200,
        AisPositionReportClassAMessage = 11300,
        AisPositionReportClassAResponseToInterrogationMessage = 11400,
        AisPositionReportForLongRangeApplicationsMessage = 11500,
        AisSafetyRelatedAcknowledgmentMessage = 11600,
        AisStandardClassBCsPositionReportMessage = 11700,
        AisStandardSarAircraftPositionReportMessage = 11800,
        AisStaticAndVoyageRelatedDataMessage = 11900,
        AisStaticDataReportMessage = 12000,
        AisStaticDataReportPartAMessage = 12100,
        AisStaticDataReportPartBMessage = 12200,
        AisUtcAndDateInquiryMessage = 12300,
        AisUtcAndDateResponseMessage = 12400,
        AisTransceiverCommand = 12500,
        AisTransceiverCommandReply = 12600,
        AisTransceiverConfiguration = 12700,
        AisTransceiverRawMessage = 12800,
        AisTransceiverRawSentence = 12900,
        AlarmStateChange = 13000,
        BaseStationType = 13100,
        BinaryTimeseriesValue = 13200,
        Bookmark = 13300,
        BooleanTimeseriesValue = 13400,
        ByteTimeseriesValue = 13500,
        CameraCommand = 13600,
        CameraCommandAbsoluteMove = 13700,
        CameraCommandAdjustPanTiltZoom = 13800,
        CameraCommandContinuousMove = 13900,
        CameraCommandGeoMove = 14000,
        CameraCommandRelativeMove = 14100,
        CameraCommandReleasePTZOwnership = 14200,
        CameraCommandRequestPTZOwnership = 14300,
        CameraCommandSetAutoFocus = 14400,
        CameraCommandSetBlackAndWhite = 14500,
        CameraCommandSetFollowed = 14600,
        CameraCommandSetInfraRedLamp = 14700,
        CameraCommandSetWasher = 14800,
        CameraCommandSetWiper = 14900,
        CameraCommandStop = 15000,
        CameraCommandReply = 15100,
        CameraConfiguration = 15200,
        CameraPanCalibration = 15300,
        CameraPanCalibrationValue = 15400,
        CameraStatus = 15500,
        CameraTiltCalibration = 15600,
        CameraTiltCalibrationValue = 15700,
        CameraZoomCalibration = 15800,
        CameraZoomCalibrationValue = 15900,
        CatalogElement = 16000,
        Catalog = 16100,
        Element = 16200,
        CollectionInfo = 16300,
        Country = 16400,
        CursorInfo = 16500,
        DateTimeTimeseriesValue = 16600,
        DeviceHost = 16700,
        DeviceHostConfiguration = 16800,
        DeviceType = 16900,
        AisTransceiverType = 17000,
        CameraType = 17100,
        GNSSDeviceType = 17200,
        GyroDeviceType = 17300,
        LineInputDeviceType = 17400,
        OilspillDetectorType = 17500,
        RadarType = 17600,
        RadioType = 17700,
        RadomeType = 17800,
        WeatherStationType = 17900,
        DoubleTimeseriesValue = 18000,
        FacilityType = 18100,
        GeoPosition2DTimeseriesValue = 18200,
        GeoPosition3DTimeseriesValue = 18300,
        GNSSDeviceCommand = 18400,
        GNSSDeviceCommandReply = 18500,
        GNSSDeviceConfiguration = 18600,
        GuidTimeseriesValue = 18700,
        GyroDeviceCommand = 18800,
        GyroDeviceCommandReply = 18900,
        GyroDeviceConfiguration = 19000,
        Identity = 19100,
        Callsign = 19200,
        InternationalMaritimeOrganizationNumber = 19300,
        MaritimeMobileServiceIdentity = 19400,
        Name = 19500,
        Int16TimeseriesValue = 19600,
        Int32TimeseriesValue = 19700,
        Int64TimeseriesValue = 19800,
        Item = 19900,
        BaseStation = 20000,
        Device = 20100,
        Camera = 20200,
        GNSSDevice = 20300,
        GyroDevice = 20400,
        LineInputDevice = 20500,
        OilspillDetector = 20600,
        Radio = 20700,
        Radome = 20800,
        Tracker = 20900,
        AisTransceiver = 21000,
        Radar = 21100,
        WeatherStation = 21200,
        Facility = 21300,
        TrackableItem = 21400,
        Aircraft = 21500,
        AisAidToNavigation = 21600,
        Vehicle = 21700,
        Vessel = 21800,
        ItemIdentityLink = 21900,
        ItemParentChildLink = 22000,
        LineInputDeviceCommand = 22100,
        LineInputDeviceCommandReply = 22200,
        LineInputDeviceConfiguration = 22300,
        LineInputMessageRouting = 22400,
        LineInputMessageRoutingDestination = 22500,
        LineInputWhiteListEntry = 22600,
        LogApplication = 22700,
        LogApplicationConfiguration = 22800,
        LogHost = 22900,
        LogHostConfiguration = 23000,
        LogLocation = 23100,
        LogProcess = 23200,
        LogRecord = 23300,
        LogThread = 23400,
        LogTraceEntry = 23500,
        MapElement = 23600,
        MapInfo = 23700,
        MapServiceOptions = 23800,
        MaritimeIdentificationDigits = 23900,
        MediaProxySession = 24000,
        MediaProxySessionFile = 24100,
        MediaProxySessionOptions = 24200,
        MediaService = 24300,
        MediaServiceOptions = 24400,
        NamespaceElement = 24500,
        ElementType = 24600,
        Namespace = 24700,
        Oilspill = 24800,
        OilspillDetectorCommand = 24900,
        OilspillDetectorCommandReply = 25000,
        OilspillDetectorConfiguration = 25100,
        Position2DTimeseriesValue = 25200,
        Position3DTimeseriesValue = 25300,
        ProcessTrackValueResult = 25400,
        Property = 25500,
        BinaryProperty = 25600,
        BooleanProperty = 25700,
        ByteProperty = 25800,
        DateTimeProperty = 25900,
        DoubleProperty = 26000,
        GuidProperty = 26100,
        Int16Property = 26200,
        Int32Property = 26300,
        Int64Property = 26400,
        ReferenceProperty = 26500,
        SByteProperty = 26600,
        SingleProperty = 26700,
        StringProperty = 26800,
        TimeseriesProperty = 26900,
        BinaryTimeseriesProperty = 27000,
        BooleanTimeseriesProperty = 27100,
        ByteTimeseriesProperty = 27200,
        DateTimeTimeseriesProperty = 27300,
        DoubleTimeseriesProperty = 27400,
        GuidTimeseriesProperty = 27500,
        Int16TimeseriesProperty = 27600,
        Int32TimeseriesProperty = 27700,
        Int64TimeseriesProperty = 27800,
        ReferenceTimeseriesProperty = 27900,
        SByteTimeseriesProperty = 28000,
        SingleTimeseriesProperty = 28100,
        StringTimeseriesProperty = 28200,
        TimeSpanTimeseriesProperty = 28300,
        UInt16TimeseriesProperty = 28400,
        UInt32TimeseriesProperty = 28500,
        UInt64TimeseriesProperty = 28600,
        TimeSpanProperty = 28700,
        UInt16Property = 28800,
        UInt32Property = 28900,
        UInt64Property = 29000,
        PropertyDefinition = 29100,
        BinaryPropertyDefinition = 29200,
        BooleanPropertyDefinition = 29300,
        BytePropertyDefinition = 29400,
        DateTimePropertyDefinition = 29500,
        DoublePropertyDefinition = 29600,
        GuidPropertyDefinition = 29700,
        Int16PropertyDefinition = 29800,
        Int32PropertyDefinition = 29900,
        Int64PropertyDefinition = 30000,
        ReferencePropertyDefinition = 30100,
        SBytePropertyDefinition = 30200,
        SinglePropertyDefinition = 30300,
        StringPropertyDefinition = 30400,
        TimeseriesPropertyDefinition = 30500,
        BinaryTimeseriesPropertyDefinition = 30600,
        BooleanTimeseriesPropertyDefinition = 30700,
        ByteTimeseriesPropertyDefinition = 30800,
        DateTimeTimeseriesPropertyDefinition = 30900,
        DoubleTimeseriesPropertyDefinition = 31000,
        GuidTimeseriesPropertyDefinition = 31100,
        Int16TimeseriesPropertyDefinition = 31200,
        Int32TimeseriesPropertyDefinition = 31300,
        Int64TimeseriesPropertyDefinition = 31400,
        ReferenceTimeseriesPropertyDefinition = 31500,
        SByteTimeseriesPropertyDefinition = 31600,
        SingleTimeseriesPropertyDefinition = 31700,
        StringTimeseriesPropertyDefinition = 31800,
        TimeSpanTimeseriesPropertyDefinition = 31900,
        UInt16TimeseriesPropertyDefinition = 32000,
        UInt32TimeseriesPropertyDefinition = 32100,
        UInt64TimeseriesPropertyDefinition = 32200,
        TimeSpanPropertyDefinition = 32300,
        UInt16PropertyDefinition = 32400,
        UInt32PropertyDefinition = 32500,
        UInt64PropertyDefinition = 32600,
        RadarAlarmStatus = 32700,
        RadarCommand = 32800,
        RadarCommandGetStatus = 32900,
        RadarCommandReply = 33000,
        RadarCommandReplyGetStatus = 33100,
        RadarConfiguration = 33200,
        RadarImage = 33300,
        RadarRawTrackTable = 33400,
        RadarStatus = 33500,
        RadioCommand = 33600,
        RadioCommandReply = 33700,
        RadioConfiguration = 33800,
        RadomeCommand = 33900,
        RadomeCommandReply = 34000,
        RadomeConfiguration = 34100,
        ReferenceTimeseriesValue = 34200,
        SByteTimeseriesValue = 34300,
        SecurityDomain = 34400,
        SecurityIdentifier = 34500,
        SecurityLogin = 34600,
        SecurityRole = 34700,
        SecurityIdentifierRoleLink = 34800,
        SecurityLoginSession = 34900,
        SecurityPermission = 35000,
        SingleTimeseriesValue = 35100,
        StringTimeseriesValue = 35200,
        TimeseriesCatalogElement = 35300,
        Timeseries = 35400,
        BinaryTimeseries = 35500,
        BooleanTimeseries = 35600,
        AisAidToNavigationOffPositionTimeseries = 35700,
        DeviceEnabledTimeseries = 35800,
        RadarAutomaticSensitivityTimeControlTimeseries = 35900,
        RadarBlankSector1Timeseries = 36000,
        RadarBlankSector2Timeseries = 36100,
        RadarEnableAutomaticFrequencyControlTimeseries = 36200,
        RadarEnableFastTimeConstantTimeseries = 36300,
        RadarEnableSensitivityTimeControlTimeseries = 36400,
        RadarPowerOnTimeseries = 36500,
        RadarSaveSettingsTimeseries = 36600,
        RadarTrackingTimeseries = 36700,
        MediaProxySessionEnabledTimeseries = 36800,
        MediaServiceEnabledTimeseries = 36900,
        ByteTimeseries = 37000,
        DateTimeTimeseries = 37100,
        DoubleTimeseries = 37200,
        GNSSAltitudeTimeseries = 37300,
        GNSSLatitudeTimeseries = 37400,
        GNSSLongitudeTimeseries = 37500,
        GyroCourseTimeseries = 37600,
        GyroHeadingMagneticNorthTimeseries = 37700,
        GyroHeadingTrueNorthTimeseries = 37800,
        GyroPitchTimeseries = 37900,
        GyroRateOfTurnTimeseries = 38000,
        GyroRollTimeseries = 38100,
        GyroSpeedTimeseries = 38200,
        RadarLatitudeTimeseries = 38300,
        RadarLongitudeTimeseries = 38400,
        RadomeDewPointTimeseries = 38500,
        RadomePressureTimeseries = 38600,
        RadomeTemperatureTimeseries = 38700,
        VesselDraughtTimeseries = 38800,
        ViewLatitudeTimeseries = 38900,
        ViewLongitudeTimeseries = 39000,
        ViewZoomLevelTimeseries = 39100,
        WeatherStationAbsoluteHumidityTimeseries = 39200,
        WeatherStationAirTemperatureTimeseries = 39300,
        WeatherStationBarometricPressureTimeseries = 39400,
        WeatherStationDewPointTimeseries = 39500,
        WeatherStationRelativeHumidityTimeseries = 39600,
        WeatherStationWaterTemperatureTimeseries = 39700,
        WeatherStationWindDirectionTimeseries = 39800,
        WeatherStationWindSpeedTimeseries = 39900,
        GeoPosition2DTimeseries = 40000,
        AisAidToNavigationPositionTimeseries = 40100,
        GeoPosition3DTimeseries = 40200,
        GuidTimeseries = 40300,
        Int16Timeseries = 40400,
        Int32Timeseries = 40500,
        RadarAzimuthOffsetTimeseries = 40600,
        RadarFastTimeConstantLevelTimeseries = 40700,
        RadarFastTimeConstantModeTimeseries = 40800,
        RadarPulseTimeseries = 40900,
        RadarSector1EndTimeseries = 41000,
        RadarSector1StartTimeseries = 41100,
        RadarSector2EndTimeseries = 41200,
        RadarSector2StartTimeseries = 41300,
        RadarSensitivityTimeControlLevelTimeseries = 41400,
        RadarTuningTimeseries = 41500,
        VesselPersonsOnBoardTimeseries = 41600,
        Int64Timeseries = 41700,
        Position2DTimeseries = 41800,
        Position3DTimeseries = 41900,
        ReferenceTimeseries = 42000,
        SByteTimeseries = 42100,
        SingleTimeseries = 42200,
        StringTimeseries = 42300,
        TimeSpanTimeseries = 42400,
        UInt16Timeseries = 42500,
        UInt32Timeseries = 42600,
        RadomeStatusTimeseries = 42700,
        UInt64Timeseries = 42800,
        TimeseriesCatalog = 42900,
        TimeseriesInfo = 43000,
        TimeSpanTimeseriesValue = 43100,
        TrackableItemTrackLink = 43200,
        TrackBase = 43300,
        Track = 43400,
        Track3D = 43500,
        TrackerFilterParameters = 43600,
        TrackerFilterParametersConfiguration = 43700,
        TrackInfo = 43800,
        TrackingServiceOptions = 43900,
        TrackLink = 44000,
        TrackValue = 44100,
        TrackValue3D = 44200,
        UInt16TimeseriesValue = 44300,
        UInt32TimeseriesValue = 44400,
        UInt64TimeseriesValue = 44500,
        VehicleType = 44600,
        VesselType = 44700,
        View = 44800,
        ViewCameraLink = 44900,
        ViewTrackerLink = 45000,
        WeatherStationCommand = 45100,
        WeatherStationCommandReply = 45200,
        WeatherStationConfiguration = 45300,
        Zone = 45400,
        CircularZone = 45500,
        PolygonZone = 45600,
        ZoneExceptions = 45700,
        ZoneExceptionsVesselLink = 45800,
        ZoneTrackAlarm = 45900
    };

    enum class AisMessageType : Int32
    {
        PositionReportClassA = 1,
        PositionReportClassAAssignedSchedule = 2,
        PositionReportClassAResponseToInterrogation = 3,
        BaseStationReport = 4,
        StaticAndVoyageRelatedData = 5,
        BinaryAddressedMessage = 6,
        BinaryAcknowledge = 7,
        BinaryBroadcastMessage = 8,
        StandardSarAircraftPositionReport = 9,
        UtcAndDateInquiry = 10,
        UtcAndDateResponse = 11,
        AddressedSafetyRelatedMessage = 12,
        SafetyRelatedAcknowledgment = 13,
        SafetyRelatedBroadcastMessage = 14,
        Interrogation = 15,
        AssignmentModeCommand = 16,
        DgnssBinaryBroadcastMessage = 17,
        StandardClassBCsPositionReport = 18,
        ExtendedClassBCsPositionReport = 19,
        DataLinkManagement = 20,
        AidToNavigationReport = 21,
        ChannelManagement = 22,
        GroupAssignmentCommand = 23,
        StaticDataReport = 24,
        SingleSlotBinaryMessage = 25,
        MultipleSlotBinaryMessageWithCommunicationsState = 26,
        PositionReportForLongRangeApplications = 27
    };

    enum class AisTransceiverConnectionType : Int32
    {
        Unknown = 0,
        TCP = 1,
        UDP = 2,
        SerialPort = 3
    };

    enum class AlarmState : Int32
    {
        Unknown = 0,
        Entering = 1,
        Raised = 2,
        Identified = 3,
        Acknowledged = 4,
        Leaving = 5,
        Cleared = 6,
        AutoCleared = 7
    };

    enum class CameraControlProtocol : Int32
    {
        Unknown = 0,
        ONVIF = 1
    };

    enum class CameraFeatures : Int32
    {
        None = 0,
        ColorMode = 1,
        Washer = 2,
        Wiper = 4,
        IRLamp = 8,
        AutoFocusControl = 16
    };

    enum class CameraFocalLengthMode : Int32
    {
        Unknown = 0,
        Normalized = 1,
        Millimeter = 2
    };

    enum class CameraFollowReason : Int32
    {
        Alarm = 0,
        User = 1
    };

    enum class CameraMoveStatus : Int32
    {
        Unknown = 0,
        Idle = 1,
        Moving = 2,
        MovingContinuously = 3
    };

    enum class CameraPanTiltMode : Int32
    {
        Unknown = 0,
        Normalized = 1,
        Angular = 2
    };

    enum class DeviceCommandReplyStatus : Int32
    {
        Unknown = 0,
        Ok = 1,
        NotImplemented = 2,
        Error = 3
    };

    enum class DeviceCommandSourceType : Int32
    {
        Unknown = 0,
        Session = 1,
        Device = 2,
        Source = 3
    };

    enum class GnssPositionStatus : Int32
    {
        CurrentGnssPosition = 0,
        NotGnssPosition = 1
    };

    enum class Handshake : Int32
    {
        None = 0,
        XOnXOff = 1,
        RequestToSend = 2,
        RequestToSendXOnXOff = 3
    };

    enum class HeadingType : Int32
    {
        Unknown = 0,
        TrueNorth = 1,
        MagneticNorth = 2,
        Relative = 3
    };

    enum class LineInputDeviceConnectionType : Int32
    {
        Unknown = 0,
        TCP = 1,
        UDP = 2,
        SerialPort = 3
    };

    enum class LogLevel : Int32
    {
        Unknown = 0,
        Finest = 10000,
        Finer = 20000,
        Trace = 20000,
        Fine = 30000,
        Info = 40000,
        Notice = 50000,
        Warn = 60000,
        Error = 70000,
        Severe = 80000,
        Critical = 90000,
        Alert = 100000,
        Fatal = 110000,
        Emergency = 120000
    };

    enum class ManeuverIndicator : Int32
    {
        NotAvailable = 0,
        NoSpecialManeuver = 1,
        SpecialManeuver = 2
    };

    enum class MapElementType : Int32
    {
        Unknown = 0,
        Svg = 1,
        Png = 2,
        Jpeg = 3
    };

    enum class MediaProxySessionMode : Int32
    {
        Unknown = 0,
        RTP = 1,
        RTPOverTCP = 2,
        RTPOverHTTP = 3
    };

    enum class MediaProxySessionType : Int32
    {
        Unknown = 0,
        ACCAudio = 1,
        AMRAudio = 2,
        AC3Audio = 3,
        MPEGAudio = 4,
        WAVAudio = 5,
        MPEG4Video = 6,
        H264Video = 7,
        H265Video = 8,
        MPEGVideo = 9,
        MPEGVideoWithAC3Audio = 10,
        MatroskaVideo = 11,
        Oggvideo = 12
    };

    enum class NavigationalAidType : Int32
    {
        NotSpecified = 0,
        ReferencePoint = 1,
        Racon = 2,
        FixedStuctureOffShore = 3,
        Spare = 4,
        LightWithoutSectors = 5,
        LightWithSectors = 6,
        LeadingLightFront = 7,
        LeadingLigthRear = 8,
        BeaconCardinalN = 9,
        BeaconCardinalE = 10,
        BeaconCardinalS = 11,
        BeaconCardinalW = 12,
        BeaconPortHand = 13,
        BeaconStarboardHand = 14,
        BeaconPreferredChannelPortHand = 15,
        BeaconPreferredChannelStarboardHand = 16,
        BeaconIsolatedDanger = 17,
        BeaconSafeWater = 18,
        BeaconSpecialMark = 19,
        CardinalMarkN = 20,
        CardinalMarkE = 21,
        CardinalMarkS = 22,
        CardinalMarkW = 23,
        PortHandMark = 24,
        StarboardHandMark = 25,
        PreferredChannelPortHand = 26,
        PreferredChannelStarboardHand = 27,
        IsolatedDanger = 28,
        SafeWater = 29,
        SpecialMark = 30,
        LightVessel = 31
    };

    enum class NavigationStatus : Int32
    {
        UnderWayUsingEngine = 0,
        AtAnchor = 1,
        NotUnderCommand = 2,
        RestrictedManeuverability = 3,
        ConstrainedByHerDraught = 4,
        Moored = 5,
        Aground = 6,
        EngagedInFishing = 7,
        UnderWaySailing = 8,
        ReservedForFutureAmendmentOfNavigationalStatusForHsc = 9,
        ReservedForFutureAmendmentOfNavigationalStatusForWig = 10,
        ReservedForFutureUse1 = 11,
        ReservedForFutureUse2 = 12,
        ReservedForFutureUse3 = 13,
        AisSartIsActive = 14,
        NotDefined = 15
    };

    enum class Parity : Int32
    {
        None = 0,
        Odd = 1,
        Even = 2,
        Mark = 3,
        Space = 4
    };

    enum class PositionAccuracy : Int32
    {
        Low = 0,
        High = 1
    };

    enum class PositionFixType : Int32
    {
        Undefined1 = 0,
        Gps = 1,
        Glonass = 2,
        CombinedGpsAndGlonass = 3,
        LoranC = 4,
        Chayka = 5,
        IntegratedNavigationSystem = 6,
        Surveyed = 7,
        Galileo = 8,
        Undefined2 = 15
    };

    enum class RadarImageType : Int32
    {
        MaskedProcessed = 0,
        FullRaw = 1,
        MaskedRaw = 2,
        VideoMask = 3,
        TrackMask = 4,
        SpillRaw = 5,
        SpillProcessed = 6,
        RawUnscanConverted = 7,
        NoTrackInitMask = 8
    };

    enum class RadarPulse : Int32
    {
        Short = 2,
        Medium = 1,
        Long = 0
    };

    enum class RadarStatusType : Int32
    {
        Off = 0,
        On = 1,
        Error = 2,
        NoData = 3
    };

    enum class RadomeStatus : Int32
    {
        None = 0,
        Overpressure = 1,
        Overridden = 2,
        Purging = 4,
        NormalOperation = 8,
        RadarPowerOff = 16
    };

    enum class Raim : Int32
    {
        NotInUse = 0,
        InUse = 1
    };

    enum class ShipType : Int32
    {
        NotAvailable = 0,
        WingInGround = 20,
        WingInGroundHazardousCategoryA = 21,
        WingInGroundHazardousCategoryB = 22,
        WingInGroundHazardousCategoryC = 23,
        WingInGroundHazardousCategoryD = 24,
        WingInGroundReserved1 = 25,
        WingInGroundReserved2 = 26,
        WingInGroundReserved3 = 27,
        WingInGroundReserved4 = 28,
        WingInGroundReserved5 = 29,
        Fishing = 30,
        Towing = 31,
        TowingLarge = 32,
        DredgingOrUnderwaterOps = 33,
        DivingOps = 34,
        MilitaryOps = 35,
        Sailing = 36,
        PleasureCraft = 37,
        Reserved1 = 38,
        Reserved2 = 39,
        HighSpeedCraft = 40,
        HighSpeedCraftHazardousCategoryA = 41,
        HighSpeedCraftHazardousCategoryB = 42,
        HighSpeedCraftHazardousCategoryC = 43,
        HighSpeedCraftHazardousCategoryD = 44,
        HighSpeedCraftReserved1 = 45,
        HighSpeedCraftReserved2 = 46,
        HighSpeedCraftReserved3 = 47,
        HighSpeedCraftReserved4 = 48,
        HighSpeedCraftNoAdditionalInformation = 49,
        PilotVessel = 50,
        SearchAndRescueVessel = 51,
        Tug = 52,
        PortTender = 53,
        AntiPollutionEquipment = 54,
        LawEnforcement = 55,
        SpareLocalVessel1 = 56,
        SpareLocalVessel2 = 57,
        MedicalTransport = 58,
        NonCombatantShip = 59,
        Passenger = 60,
        PassengerHazardousCategoryA = 61,
        PassengerHazardousCategoryB = 62,
        PassengerHazardousCategoryC = 63,
        PassengerHazardousCategoryD = 64,
        PassengerReserved1 = 65,
        PassengerReserved2 = 66,
        PassengerReserved3 = 67,
        PassengerReserved4 = 68,
        PassengerNoAdditionalInformation = 69,
        Cargo = 70,
        CargoHazardousCategoryA = 71,
        CargoHazardousCategoryB = 72,
        CargoHazardousCategoryC = 73,
        CargoHazardousCategoryD = 74,
        CargoReserved1 = 75,
        CargoReserved2 = 76,
        CargoReserved3 = 77,
        CargoReserved4 = 78,
        CargoNoAdditionalInformation = 79,
        Tanker = 80,
        TankerHazardousCategoryA = 81,
        TankerHazardousCategoryB = 82,
        TankerHazardousCategoryC = 83,
        TankerHazardousCategoryD = 84,
        TankerReserved1 = 85,
        TankerReserved2 = 86,
        TankerReserved3 = 87,
        TankerReserved4 = 88,
        TankerNoAdditionalInformation = 89,
        OtherType = 90,
        OtherTypeHazardousCategoryA = 91,
        OtherTypeHazardousCategoryB = 92,
        OtherTypeHazardousCategoryC = 93,
        OtherTypeHazardousCategoryD = 94,
        OtherTypeReserved1 = 95,
        OtherTypeReserved2 = 96,
        OtherTypeReserved3 = 97,
        OtherTypeReserved4 = 98,
        OtherTypeNoAdditionalInformation = 99
    };

    enum class StopBits : Int32
    {
        None = 0,
        One = 1,
        Two = 2,
        OnePointFive = 3
    };

    enum class TrackerFilterModelType : Int32
    {
        Unknown = 0,
        Damp1 = 1,
        Damp2 = 2
    };

    enum class TrackFlags : Int32
    {
        None = 0,
        Status = 1,
        Position = 2,
        Speed = 4,
        Course = 8,
        Heading = 16
    };

    enum class TrackFlags3D : Int32
    {
        None = 0,
        Status = 1,
        Position = 2,
        Speed = 4,
        Course = 8,
        RateOfClimb = 16
    };

    enum class TrackStatus : Int32
    {
        Unknown = 0,
        New = 1,
        Tracked = 2,
        NoPositionUpdate = 3,
        Lost = 4,
        Killed = 5,
        DIW = 6,
        UnderWayUsingEngine = 7,
        AtAnchor = 8,
        NotUnderCommand = 9,
        RestrictedManeuverability = 10,
        ConstrainedByDraught = 11,
        Moored = 12,
        Aground = 13,
        EngagedInFishing = 14,
        UnderWaySailing = 15,
        ReservedForFutureAmendmentOfNavigationalStatusForHSC = 16,
        ReservedForFutureAmendmentOfNavigationalStatusForWIG = 17,
        ReservedForFutureUse1 = 18,
        ReservedForFutureUse2 = 19,
        ReservedForFutureUse3 = 20,
        ReservedForFutureUse = 21,
        AisSartIsActive = 22,
        NotDefined = 23
    };

    enum class ZoneAlarmType : Int32
    {
        None = 0,
        Intrusion = 1,
        Speed = 2,
        Entered = 3,
        Exited = 4
    };

    enum class ZoneType : Int32
    {
        None = 0,
        Circular = 1,
        Polygon = 2
    };

}
#endif
