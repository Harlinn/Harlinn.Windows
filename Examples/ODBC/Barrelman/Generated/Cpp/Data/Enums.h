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
        DoubleTimeseriesValue = 16900,
        FacilityType = 17000,
        GeoPosition2DTimeseriesValue = 17100,
        GeoPosition3DTimeseriesValue = 17200,
        GNSSDeviceCommand = 17300,
        GNSSDeviceCommandReply = 17400,
        GNSSDeviceConfiguration = 17500,
        GuidTimeseriesValue = 17600,
        GyroDeviceCommand = 17700,
        GyroDeviceCommandReply = 17800,
        GyroDeviceConfiguration = 17900,
        Identity = 18000,
        Callsign = 18100,
        InternationalMaritimeOrganizationNumber = 18200,
        MaritimeMobileServiceIdentity = 18300,
        Name = 18400,
        Int16TimeseriesValue = 18500,
        Int32TimeseriesValue = 18600,
        Int64TimeseriesValue = 18700,
        Item = 18800,
        BaseStation = 18900,
        Device = 19000,
        Camera = 19100,
        GNSSDevice = 19200,
        GyroDevice = 19300,
        LineInputDevice = 19400,
        OilspillDetector = 19500,
        Radio = 19600,
        Radome = 19700,
        Tracker = 19800,
        AisTransceiver = 19900,
        Radar = 20000,
        WeatherStation = 20100,
        Facility = 20200,
        TrackableItem = 20300,
        Aircraft = 20400,
        AisAidToNavigation = 20500,
        Vehicle = 20600,
        Vessel = 20700,
        ItemIdentityLink = 20800,
        ItemParentChildLink = 20900,
        LineInputDeviceCommand = 21000,
        LineInputDeviceCommandReply = 21100,
        LineInputDeviceConfiguration = 21200,
        LineInputMessageRouting = 21300,
        LineInputMessageRoutingDestination = 21400,
        LineInputWhiteListEntry = 21500,
        LogApplication = 21600,
        LogApplicationConfiguration = 21700,
        LogHost = 21800,
        LogHostConfiguration = 21900,
        LogLocation = 22000,
        LogProcess = 22100,
        LogRecord = 22200,
        LogThread = 22300,
        LogTraceEntry = 22400,
        MapElement = 22500,
        MapInfo = 22600,
        MapServiceOptions = 22700,
        MaritimeIdentificationDigits = 22800,
        MediaProxySession = 22900,
        MediaProxySessionFile = 23000,
        MediaProxySessionOptions = 23100,
        MediaService = 23200,
        MediaServiceOptions = 23300,
        NamespaceElement = 23400,
        ElementType = 23500,
        Namespace = 23600,
        Oilspill = 23700,
        OilspillDetectorCommand = 23800,
        OilspillDetectorCommandReply = 23900,
        OilspillDetectorConfiguration = 24000,
        Position2DTimeseriesValue = 24100,
        Position3DTimeseriesValue = 24200,
        ProcessTrackValueResult = 24300,
        Property = 24400,
        BinaryProperty = 24500,
        BooleanProperty = 24600,
        ByteProperty = 24700,
        DateTimeProperty = 24800,
        DoubleProperty = 24900,
        GuidProperty = 25000,
        Int16Property = 25100,
        Int32Property = 25200,
        Int64Property = 25300,
        ReferenceProperty = 25400,
        SByteProperty = 25500,
        SingleProperty = 25600,
        StringProperty = 25700,
        TimeseriesProperty = 25800,
        BinaryTimeseriesProperty = 25900,
        BooleanTimeseriesProperty = 26000,
        ByteTimeseriesProperty = 26100,
        DateTimeTimeseriesProperty = 26200,
        DoubleTimeseriesProperty = 26300,
        GuidTimeseriesProperty = 26400,
        Int16TimeseriesProperty = 26500,
        Int32TimeseriesProperty = 26600,
        Int64TimeseriesProperty = 26700,
        ReferenceTimeseriesProperty = 26800,
        SByteTimeseriesProperty = 26900,
        SingleTimeseriesProperty = 27000,
        StringTimeseriesProperty = 27100,
        TimeSpanTimeseriesProperty = 27200,
        UInt16TimeseriesProperty = 27300,
        UInt32TimeseriesProperty = 27400,
        UInt64TimeseriesProperty = 27500,
        TimeSpanProperty = 27600,
        UInt16Property = 27700,
        UInt32Property = 27800,
        UInt64Property = 27900,
        PropertyDefinition = 28000,
        BinaryPropertyDefinition = 28100,
        BooleanPropertyDefinition = 28200,
        BytePropertyDefinition = 28300,
        DateTimePropertyDefinition = 28400,
        DoublePropertyDefinition = 28500,
        GuidPropertyDefinition = 28600,
        Int16PropertyDefinition = 28700,
        Int32PropertyDefinition = 28800,
        Int64PropertyDefinition = 28900,
        ReferencePropertyDefinition = 29000,
        SBytePropertyDefinition = 29100,
        SinglePropertyDefinition = 29200,
        StringPropertyDefinition = 29300,
        TimeseriesPropertyDefinition = 29400,
        BinaryTimeseriesPropertyDefinition = 29500,
        BooleanTimeseriesPropertyDefinition = 29600,
        ByteTimeseriesPropertyDefinition = 29700,
        DateTimeTimeseriesPropertyDefinition = 29800,
        DoubleTimeseriesPropertyDefinition = 29900,
        GuidTimeseriesPropertyDefinition = 30000,
        Int16TimeseriesPropertyDefinition = 30100,
        Int32TimeseriesPropertyDefinition = 30200,
        Int64TimeseriesPropertyDefinition = 30300,
        ReferenceTimeseriesPropertyDefinition = 30400,
        SByteTimeseriesPropertyDefinition = 30500,
        SingleTimeseriesPropertyDefinition = 30600,
        StringTimeseriesPropertyDefinition = 30700,
        TimeSpanTimeseriesPropertyDefinition = 30800,
        UInt16TimeseriesPropertyDefinition = 30900,
        UInt32TimeseriesPropertyDefinition = 31000,
        UInt64TimeseriesPropertyDefinition = 31100,
        TimeSpanPropertyDefinition = 31200,
        UInt16PropertyDefinition = 31300,
        UInt32PropertyDefinition = 31400,
        UInt64PropertyDefinition = 31500,
        RadarAlarmStatus = 31600,
        RadarCommand = 31700,
        RadarCommandGetStatus = 31800,
        RadarCommandReply = 31900,
        RadarCommandReplyGetStatus = 32000,
        RadarConfiguration = 32100,
        RadarImage = 32200,
        RadarRawTrackTable = 32300,
        RadarStatus = 32400,
        RadioCommand = 32500,
        RadioCommandReply = 32600,
        RadioConfiguration = 32700,
        RadomeCommand = 32800,
        RadomeCommandReply = 32900,
        RadomeConfiguration = 33000,
        ReferenceTimeseriesValue = 33100,
        SByteTimeseriesValue = 33200,
        SecurityDomain = 33300,
        SecurityIdentifier = 33400,
        SecurityLogin = 33500,
        SecurityRole = 33600,
        SecurityIdentifierRoleLink = 33700,
        SecurityLoginSession = 33800,
        SecurityPermission = 33900,
        SingleTimeseriesValue = 34000,
        StringTimeseriesValue = 34100,
        TimeseriesCatalogElement = 34200,
        Timeseries = 34300,
        BinaryTimeseries = 34400,
        BooleanTimeseries = 34500,
        AisAidToNavigationOffPositionTimeseries = 34600,
        DeviceEnabledTimeseries = 34700,
        RadarAutomaticSensitivityTimeControlTimeseries = 34800,
        RadarBlankSector1Timeseries = 34900,
        RadarBlankSector2Timeseries = 35000,
        RadarEnableAutomaticFrequencyControlTimeseries = 35100,
        RadarEnableFastTimeConstantTimeseries = 35200,
        RadarEnableSensitivityTimeControlTimeseries = 35300,
        RadarPowerOnTimeseries = 35400,
        RadarSaveSettingsTimeseries = 35500,
        RadarTrackingTimeseries = 35600,
        MediaProxySessionEnabledTimeseries = 35700,
        MediaServiceEnabledTimeseries = 35800,
        ByteTimeseries = 35900,
        DateTimeTimeseries = 36000,
        DoubleTimeseries = 36100,
        GNSSAltitudeTimeseries = 36200,
        GNSSLatitudeTimeseries = 36300,
        GNSSLongitudeTimeseries = 36400,
        GyroCourseTimeseries = 36500,
        GyroHeadingMagneticNorthTimeseries = 36600,
        GyroHeadingTrueNorthTimeseries = 36700,
        GyroPitchTimeseries = 36800,
        GyroRateOfTurnTimeseries = 36900,
        GyroRollTimeseries = 37000,
        GyroSpeedTimeseries = 37100,
        RadarLatitudeTimeseries = 37200,
        RadarLongitudeTimeseries = 37300,
        RadomeDewPointTimeseries = 37400,
        RadomePressureTimeseries = 37500,
        RadomeTemperatureTimeseries = 37600,
        VesselDraughtTimeseries = 37700,
        ViewLatitudeTimeseries = 37800,
        ViewLongitudeTimeseries = 37900,
        ViewZoomLevelTimeseries = 38000,
        WeatherStationAbsoluteHumidityTimeseries = 38100,
        WeatherStationAirTemperatureTimeseries = 38200,
        WeatherStationBarometricPressureTimeseries = 38300,
        WeatherStationDewPointTimeseries = 38400,
        WeatherStationRelativeHumidityTimeseries = 38500,
        WeatherStationWaterTemperatureTimeseries = 38600,
        WeatherStationWindDirectionTimeseries = 38700,
        WeatherStationWindSpeedTimeseries = 38800,
        GeoPosition2DTimeseries = 38900,
        AisAidToNavigationPositionTimeseries = 39000,
        GeoPosition3DTimeseries = 39100,
        GuidTimeseries = 39200,
        Int16Timeseries = 39300,
        Int32Timeseries = 39400,
        RadarAzimuthOffsetTimeseries = 39500,
        RadarFastTimeConstantLevelTimeseries = 39600,
        RadarFastTimeConstantModeTimeseries = 39700,
        RadarPulseTimeseries = 39800,
        RadarSector1EndTimeseries = 39900,
        RadarSector1StartTimeseries = 40000,
        RadarSector2EndTimeseries = 40100,
        RadarSector2StartTimeseries = 40200,
        RadarSensitivityTimeControlLevelTimeseries = 40300,
        RadarTuningTimeseries = 40400,
        VesselPersonsOnBoardTimeseries = 40500,
        Int64Timeseries = 40600,
        Position2DTimeseries = 40700,
        Position3DTimeseries = 40800,
        ReferenceTimeseries = 40900,
        SByteTimeseries = 41000,
        SingleTimeseries = 41100,
        StringTimeseries = 41200,
        TimeSpanTimeseries = 41300,
        UInt16Timeseries = 41400,
        UInt32Timeseries = 41500,
        RadomeStatusTimeseries = 41600,
        UInt64Timeseries = 41700,
        TimeseriesCatalog = 41800,
        TimeseriesInfo = 41900,
        TimeSpanTimeseriesValue = 42000,
        TrackableItemTrackLink = 42100,
        TrackBase = 42200,
        Track = 42300,
        Track3D = 42400,
        TrackerFilterParameters = 42500,
        TrackerFilterParametersConfiguration = 42600,
        TrackInfo = 42700,
        TrackingServiceOptions = 42800,
        TrackLink = 42900,
        TrackValue = 43000,
        TrackValue3D = 43100,
        UInt16TimeseriesValue = 43200,
        UInt32TimeseriesValue = 43300,
        UInt64TimeseriesValue = 43400,
        VehicleType = 43500,
        VesselType = 43600,
        View = 43700,
        ViewCameraLink = 43800,
        ViewTrackerLink = 43900,
        WeatherStationCommand = 44000,
        WeatherStationCommandReply = 44100,
        WeatherStationConfiguration = 44200,
        Zone = 44300,
        CircularZone = 44400,
        PolygonZone = 44500,
        ZoneExceptions = 44600,
        ZoneExceptionsVesselLink = 44700,
        ZoneTrackAlarm = 44800
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
