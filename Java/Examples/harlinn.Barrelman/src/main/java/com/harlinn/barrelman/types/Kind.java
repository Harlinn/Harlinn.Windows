package com.harlinn.barrelman.types;

public class Kind {
    public final static int Unknown = 0;
    public final static int AircraftType = 10000;
    public final static int AisDeviceCommand = 10100;
    public final static int AisDeviceCommandReply = 10200;
    public final static int AisDeviceConfiguration = 10300;
    public final static int AisDeviceRawMessage = 10400;
    public final static int AisDeviceRawSentence = 10500;
    public final static int AisMessage = 10600;
    public final static int AidToNavigationReportMessage = 10700;
    public final static int AisAddressedSafetyRelatedMessage = 10800;
    public final static int AisBaseStationReportMessage = 10900;
    public final static int AisBinaryAcknowledgeMessage = 11000;
    public final static int AisBinaryAddressedMessage = 11100;
    public final static int AisBinaryBroadcastMessage = 11200;
    public final static int AisDataLinkManagementMessage = 11300;
    public final static int AisExtendedClassBCsPositionReportMessage = 11400;
    public final static int AisInterrogationMessage = 11500;
    public final static int AisPositionReportClassAMessageBase = 11600;
    public final static int AisPositionReportClassAAssignedScheduleMessage = 11700;
    public final static int AisPositionReportClassAMessage = 11800;
    public final static int AisPositionReportClassAResponseToInterrogationMessage = 11900;
    public final static int AisPositionReportForLongRangeApplicationsMessage = 12000;
    public final static int AisSafetyRelatedAcknowledgmentMessage = 12100;
    public final static int AisStandardClassBCsPositionReportMessage = 12200;
    public final static int AisStandardSarAircraftPositionReportMessage = 12300;
    public final static int AisStaticAndVoyageRelatedDataMessage = 12400;
    public final static int AisStaticDataReportMessage = 12500;
    public final static int AisStaticDataReportPartAMessage = 12600;
    public final static int AisStaticDataReportPartBMessage = 12700;
    public final static int AisUtcAndDateInquiryMessage = 12800;
    public final static int AisUtcAndDateResponseMessage = 12900;
    public final static int AlarmStateChange = 13000;
    public final static int BaseStationType = 13100;
    public final static int BinaryTimeseriesValue = 13200;
    public final static int Bookmark = 13300;
    public final static int BooleanTimeseriesValue = 13400;
    public final static int ByteTimeseriesValue = 13500;
    public final static int CameraCommand = 13600;
    public final static int CameraCommandAbsoluteMove = 13700;
    public final static int CameraCommandAdjustPanTiltZoom = 13800;
    public final static int CameraCommandContinuousMove = 13900;
    public final static int CameraCommandGeoMove = 14000;
    public final static int CameraCommandRelativeMove = 14100;
    public final static int CameraCommandReleasePTZOwnership = 14200;
    public final static int CameraCommandRequestPTZOwnership = 14300;
    public final static int CameraCommandSetAutoFocus = 14400;
    public final static int CameraCommandSetBlackAndWhite = 14500;
    public final static int CameraCommandSetFollowed = 14600;
    public final static int CameraCommandSetInfraRedLamp = 14700;
    public final static int CameraCommandSetWasher = 14800;
    public final static int CameraCommandSetWiper = 14900;
    public final static int CameraCommandStop = 15000;
    public final static int CameraCommandReply = 15100;
    public final static int CameraConfiguration = 15200;
    public final static int CameraPanCalibration = 15300;
    public final static int CameraPanCalibrationValue = 15400;
    public final static int CameraStatus = 15500;
    public final static int CameraTiltCalibration = 15600;
    public final static int CameraTiltCalibrationValue = 15700;
    public final static int CameraZoomCalibration = 15800;
    public final static int CameraZoomCalibrationValue = 15900;
    public final static int CatalogElement = 16000;
    public final static int Catalog = 16100;
    public final static int Element = 16200;
    public final static int CollectionInfo = 16300;
    public final static int Country = 16400;
    public final static int CursorInfo = 16500;
    public final static int DateTimeTimeseriesValue = 16600;
    public final static int DeviceHost = 16700;
    public final static int DeviceHostConfiguration = 16800;
    public final static int DoubleTimeseriesValue = 16900;
    public final static int FacilityType = 17000;
    public final static int GeoPosition2DTimeseriesValue = 17100;
    public final static int GeoPosition3DTimeseriesValue = 17200;
    public final static int GNSSDeviceCommand = 17300;
    public final static int GNSSDeviceCommandReply = 17400;
    public final static int GNSSDeviceConfiguration = 17500;
    public final static int GuidTimeseriesValue = 17600;
    public final static int GyroDeviceCommand = 17700;
    public final static int GyroDeviceCommandReply = 17800;
    public final static int GyroDeviceConfiguration = 17900;
    public final static int Identity = 18000;
    public final static int Callsign = 18100;
    public final static int InternationalMaritimeOrganizationNumber = 18200;
    public final static int MaritimeMobileServiceIdentity = 18300;
    public final static int Name = 18400;
    public final static int Int16TimeseriesValue = 18500;
    public final static int Int32TimeseriesValue = 18600;
    public final static int Int64TimeseriesValue = 18700;
    public final static int Item = 18800;
    public final static int BaseStation = 18900;
    public final static int Device = 19000;
    public final static int CameraDevice = 19100;
    public final static int GNSSDevice = 19200;
    public final static int GyroDevice = 19300;
    public final static int LineInputDevice = 19400;
    public final static int OilSpillDetectorDevice = 19500;
    public final static int RadioDevice = 19600;
    public final static int RadomeDevice = 19700;
    public final static int TrackerDevice = 19800;
    public final static int AisDevice = 19900;
    public final static int RadarDevice = 20000;
    public final static int WeatherStationDevice = 20100;
    public final static int Facility = 20200;
    public final static int TrackableItem = 20300;
    public final static int Aircraft = 20400;
    public final static int AisAidToNavigation = 20500;
    public final static int Vehicle = 20600;
    public final static int Vessel = 20700;
    public final static int ItemIdentityLink = 20800;
    public final static int ItemParentChildLink = 20900;
    public final static int LineInputDeviceCommand = 21000;
    public final static int LineInputDeviceCommandReply = 21100;
    public final static int LineInputDeviceConfiguration = 21200;
    public final static int LineInputMessageRouting = 21300;
    public final static int LineInputMessageRoutingDestination = 21400;
    public final static int LineInputWhiteListEntry = 21500;
    public final static int LogApplication = 21600;
    public final static int LogApplicationConfiguration = 21700;
    public final static int LogHost = 21800;
    public final static int LogHostConfiguration = 21900;
    public final static int LogLocation = 22000;
    public final static int LogProcess = 22100;
    public final static int LogRecord = 22200;
    public final static int LogThread = 22300;
    public final static int LogTraceEntry = 22400;
    public final static int MapElement = 22500;
    public final static int MapInfo = 22600;
    public final static int MapServiceOptions = 22700;
    public final static int MaritimeIdentificationDigits = 22800;
    public final static int MediaProxySession = 22900;
    public final static int MediaProxySessionFile = 23000;
    public final static int MediaProxySessionOptions = 23100;
    public final static int MediaService = 23200;
    public final static int MediaServiceOptions = 23300;
    public final static int NamespaceElement = 23400;
    public final static int ElementType = 23500;
    public final static int Namespace = 23600;
    public final static int OilSpill = 23700;
    public final static int OilSpillDetectorCommand = 23800;
    public final static int OilSpillDetectorCommandReply = 23900;
    public final static int OilSpillDetectorConfiguration = 24000;
    public final static int Position2DTimeseriesValue = 24100;
    public final static int Position3DTimeseriesValue = 24200;
    public final static int ProcessTrackValueResult = 24300;
    public final static int Property = 24400;
    public final static int BinaryProperty = 24500;
    public final static int BooleanProperty = 24600;
    public final static int ByteProperty = 24700;
    public final static int DateTimeProperty = 24800;
    public final static int DoubleProperty = 24900;
    public final static int GuidProperty = 25000;
    public final static int Int16Property = 25100;
    public final static int Int32Property = 25200;
    public final static int Int64Property = 25300;
    public final static int ReferenceProperty = 25400;
    public final static int SByteProperty = 25500;
    public final static int SingleProperty = 25600;
    public final static int StringProperty = 25700;
    public final static int TimeseriesProperty = 25800;
    public final static int BinaryTimeseriesProperty = 25900;
    public final static int BooleanTimeseriesProperty = 26000;
    public final static int ByteTimeseriesProperty = 26100;
    public final static int DateTimeTimeseriesProperty = 26200;
    public final static int DoubleTimeseriesProperty = 26300;
    public final static int GuidTimeseriesProperty = 26400;
    public final static int Int16TimeseriesProperty = 26500;
    public final static int Int32TimeseriesProperty = 26600;
    public final static int Int64TimeseriesProperty = 26700;
    public final static int ReferenceTimeseriesProperty = 26800;
    public final static int SByteTimeseriesProperty = 26900;
    public final static int SingleTimeseriesProperty = 27000;
    public final static int StringTimeseriesProperty = 27100;
    public final static int TimeSpanTimeseriesProperty = 27200;
    public final static int UInt16TimeseriesProperty = 27300;
    public final static int UInt32TimeseriesProperty = 27400;
    public final static int UInt64TimeseriesProperty = 27500;
    public final static int TimeSpanProperty = 27600;
    public final static int UInt16Property = 27700;
    public final static int UInt32Property = 27800;
    public final static int UInt64Property = 27900;
    public final static int PropertyDefinition = 28000;
    public final static int BinaryPropertyDefinition = 28100;
    public final static int BooleanPropertyDefinition = 28200;
    public final static int BytePropertyDefinition = 28300;
    public final static int DateTimePropertyDefinition = 28400;
    public final static int DoublePropertyDefinition = 28500;
    public final static int GuidPropertyDefinition = 28600;
    public final static int Int16PropertyDefinition = 28700;
    public final static int Int32PropertyDefinition = 28800;
    public final static int Int64PropertyDefinition = 28900;
    public final static int ReferencePropertyDefinition = 29000;
    public final static int SBytePropertyDefinition = 29100;
    public final static int SinglePropertyDefinition = 29200;
    public final static int StringPropertyDefinition = 29300;
    public final static int TimeseriesPropertyDefinition = 29400;
    public final static int BinaryTimeseriesPropertyDefinition = 29500;
    public final static int BooleanTimeseriesPropertyDefinition = 29600;
    public final static int ByteTimeseriesPropertyDefinition = 29700;
    public final static int DateTimeTimeseriesPropertyDefinition = 29800;
    public final static int DoubleTimeseriesPropertyDefinition = 29900;
    public final static int GuidTimeseriesPropertyDefinition = 30000;
    public final static int Int16TimeseriesPropertyDefinition = 30100;
    public final static int Int32TimeseriesPropertyDefinition = 30200;
    public final static int Int64TimeseriesPropertyDefinition = 30300;
    public final static int ReferenceTimeseriesPropertyDefinition = 30400;
    public final static int SByteTimeseriesPropertyDefinition = 30500;
    public final static int SingleTimeseriesPropertyDefinition = 30600;
    public final static int StringTimeseriesPropertyDefinition = 30700;
    public final static int TimeSpanTimeseriesPropertyDefinition = 30800;
    public final static int UInt16TimeseriesPropertyDefinition = 30900;
    public final static int UInt32TimeseriesPropertyDefinition = 31000;
    public final static int UInt64TimeseriesPropertyDefinition = 31100;
    public final static int TimeSpanPropertyDefinition = 31200;
    public final static int UInt16PropertyDefinition = 31300;
    public final static int UInt32PropertyDefinition = 31400;
    public final static int UInt64PropertyDefinition = 31500;
    public final static int RadarAlarmStatus = 31600;
    public final static int RadarCommand = 31700;
    public final static int RadarCommandGetStatus = 31800;
    public final static int RadarCommandReply = 31900;
    public final static int RadarCommandReplyGetStatus = 32000;
    public final static int RadarConfiguration = 32100;
    public final static int RadarImage = 32200;
    public final static int RadarRawTrackTable = 32300;
    public final static int RadarStatus = 32400;
    public final static int RadioCommand = 32500;
    public final static int RadioCommandReply = 32600;
    public final static int RadioConfiguration = 32700;
    public final static int RadomeCommand = 32800;
    public final static int RadomeCommandReply = 32900;
    public final static int RadomeConfiguration = 33000;
    public final static int ReferenceTimeseriesValue = 33100;
    public final static int SByteTimeseriesValue = 33200;
    public final static int SecurityDomain = 33300;
    public final static int SecurityIdentifier = 33400;
    public final static int SecurityLogin = 33500;
    public final static int SecurityRole = 33600;
    public final static int SecurityIdentifierRoleLink = 33700;
    public final static int SecurityLoginSession = 33800;
    public final static int SecurityPermission = 33900;
    public final static int SingleTimeseriesValue = 34000;
    public final static int StringTimeseriesValue = 34100;
    public final static int TimeseriesCatalogElement = 34200;
    public final static int Timeseries = 34300;
    public final static int BinaryTimeseries = 34400;
    public final static int BooleanTimeseries = 34500;
    public final static int AisAidToNavigationOffPositionTimeseries = 34600;
    public final static int DeviceEnabledTimeseries = 34700;
    public final static int RadarAutomaticSensitivityTimeControlTimeseries = 34800;
    public final static int RadarBlankSector1Timeseries = 34900;
    public final static int RadarBlankSector2Timeseries = 35000;
    public final static int RadarEnableAutomaticFrequencyControlTimeseries = 35100;
    public final static int RadarEnableFastTimeConstantTimeseries = 35200;
    public final static int RadarEnableSensitivityTimeControlTimeseries = 35300;
    public final static int RadarPowerOnTimeseries = 35400;
    public final static int RadarSaveSettingsTimeseries = 35500;
    public final static int RadarTrackingTimeseries = 35600;
    public final static int MediaProxySessionEnabledTimeseries = 35700;
    public final static int MediaServiceEnabledTimeseries = 35800;
    public final static int ByteTimeseries = 35900;
    public final static int DateTimeTimeseries = 36000;
    public final static int DoubleTimeseries = 36100;
    public final static int GNSSAltitudeTimeseries = 36200;
    public final static int GNSSLatitudeTimeseries = 36300;
    public final static int GNSSLongitudeTimeseries = 36400;
    public final static int GyroCourseTimeseries = 36500;
    public final static int GyroHeadingMagneticNorthTimeseries = 36600;
    public final static int GyroHeadingTrueNorthTimeseries = 36700;
    public final static int GyroPitchTimeseries = 36800;
    public final static int GyroRateOfTurnTimeseries = 36900;
    public final static int GyroRollTimeseries = 37000;
    public final static int GyroSpeedTimeseries = 37100;
    public final static int RadarLatitudeTimeseries = 37200;
    public final static int RadarLongitudeTimeseries = 37300;
    public final static int RadomeDewPointTimeseries = 37400;
    public final static int RadomePressureTimeseries = 37500;
    public final static int RadomeTemperatureTimeseries = 37600;
    public final static int VesselDraughtTimeseries = 37700;
    public final static int ViewLatitudeTimeseries = 37800;
    public final static int ViewLongitudeTimeseries = 37900;
    public final static int ViewZoomLevelTimeseries = 38000;
    public final static int WeatherStationAbsoluteHumidityTimeseries = 38100;
    public final static int WeatherStationAirTemperatureTimeseries = 38200;
    public final static int WeatherStationBarometricPressureTimeseries = 38300;
    public final static int WeatherStationDewPointTimeseries = 38400;
    public final static int WeatherStationRelativeHumidityTimeseries = 38500;
    public final static int WeatherStationWaterTemperatureTimeseries = 38600;
    public final static int WeatherStationWindDirectionTimeseries = 38700;
    public final static int WeatherStationWindSpeedTimeseries = 38800;
    public final static int GeoPosition2DTimeseries = 38900;
    public final static int AisAidToNavigationPositionTimeseries = 39000;
    public final static int GeoPosition3DTimeseries = 39100;
    public final static int GuidTimeseries = 39200;
    public final static int Int16Timeseries = 39300;
    public final static int Int32Timeseries = 39400;
    public final static int RadarAzimuthOffsetTimeseries = 39500;
    public final static int RadarFastTimeConstantLevelTimeseries = 39600;
    public final static int RadarFastTimeConstantModeTimeseries = 39700;
    public final static int RadarPulseTimeseries = 39800;
    public final static int RadarSector1EndTimeseries = 39900;
    public final static int RadarSector1StartTimeseries = 40000;
    public final static int RadarSector2EndTimeseries = 40100;
    public final static int RadarSector2StartTimeseries = 40200;
    public final static int RadarSensitivityTimeControlLevelTimeseries = 40300;
    public final static int RadarTuningTimeseries = 40400;
    public final static int VesselPersonsOnBoardTimeseries = 40500;
    public final static int Int64Timeseries = 40600;
    public final static int Position2DTimeseries = 40700;
    public final static int Position3DTimeseries = 40800;
    public final static int ReferenceTimeseries = 40900;
    public final static int SByteTimeseries = 41000;
    public final static int SingleTimeseries = 41100;
    public final static int StringTimeseries = 41200;
    public final static int TimeSpanTimeseries = 41300;
    public final static int UInt16Timeseries = 41400;
    public final static int UInt32Timeseries = 41500;
    public final static int RadomeStatusTimeseries = 41600;
    public final static int UInt64Timeseries = 41700;
    public final static int TimeseriesCatalog = 41800;
    public final static int TimeseriesInfo = 41900;
    public final static int TimeSpanTimeseriesValue = 42000;
    public final static int TrackableItemTrackLink = 42100;
    public final static int TrackBase = 42200;
    public final static int Track = 42300;
    public final static int Track3D = 42400;
    public final static int TrackerFilterParameters = 42500;
    public final static int TrackerFilterParametersConfiguration = 42600;
    public final static int TrackInfo = 42700;
    public final static int TrackingServiceOptions = 42800;
    public final static int TrackLink = 42900;
    public final static int TrackValue = 43000;
    public final static int TrackValue3D = 43100;
    public final static int UInt16TimeseriesValue = 43200;
    public final static int UInt32TimeseriesValue = 43300;
    public final static int UInt64TimeseriesValue = 43400;
    public final static int VehicleType = 43500;
    public final static int VesselType = 43600;
    public final static int View = 43700;
    public final static int ViewCameraLink = 43800;
    public final static int ViewTrackerLink = 43900;
    public final static int WeatherStationCommand = 44000;
    public final static int WeatherStationCommandReply = 44100;
    public final static int WeatherStationConfiguration = 44200;
    public final static int Zone = 44300;
    public final static int CircularZone = 44400;
    public final static int PolygonZone = 44500;
    public final static int ZoneExceptions = 44600;
    public final static int ZoneExceptionsVesselLink = 44700;
    public final static int ZoneTrackAlarm = 44800;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case AircraftType:
    	        return "AircraftType";
    	    case AisDeviceCommand:
    	        return "AisDeviceCommand";
    	    case AisDeviceCommandReply:
    	        return "AisDeviceCommandReply";
    	    case AisDeviceConfiguration:
    	        return "AisDeviceConfiguration";
    	    case AisDeviceRawMessage:
    	        return "AisDeviceRawMessage";
    	    case AisDeviceRawSentence:
    	        return "AisDeviceRawSentence";
    	    case AisMessage:
    	        return "AisMessage";
    	    case AidToNavigationReportMessage:
    	        return "AidToNavigationReportMessage";
    	    case AisAddressedSafetyRelatedMessage:
    	        return "AisAddressedSafetyRelatedMessage";
    	    case AisBaseStationReportMessage:
    	        return "AisBaseStationReportMessage";
    	    case AisBinaryAcknowledgeMessage:
    	        return "AisBinaryAcknowledgeMessage";
    	    case AisBinaryAddressedMessage:
    	        return "AisBinaryAddressedMessage";
    	    case AisBinaryBroadcastMessage:
    	        return "AisBinaryBroadcastMessage";
    	    case AisDataLinkManagementMessage:
    	        return "AisDataLinkManagementMessage";
    	    case AisExtendedClassBCsPositionReportMessage:
    	        return "AisExtendedClassBCsPositionReportMessage";
    	    case AisInterrogationMessage:
    	        return "AisInterrogationMessage";
    	    case AisPositionReportClassAMessageBase:
    	        return "AisPositionReportClassAMessageBase";
    	    case AisPositionReportClassAAssignedScheduleMessage:
    	        return "AisPositionReportClassAAssignedScheduleMessage";
    	    case AisPositionReportClassAMessage:
    	        return "AisPositionReportClassAMessage";
    	    case AisPositionReportClassAResponseToInterrogationMessage:
    	        return "AisPositionReportClassAResponseToInterrogationMessage";
    	    case AisPositionReportForLongRangeApplicationsMessage:
    	        return "AisPositionReportForLongRangeApplicationsMessage";
    	    case AisSafetyRelatedAcknowledgmentMessage:
    	        return "AisSafetyRelatedAcknowledgmentMessage";
    	    case AisStandardClassBCsPositionReportMessage:
    	        return "AisStandardClassBCsPositionReportMessage";
    	    case AisStandardSarAircraftPositionReportMessage:
    	        return "AisStandardSarAircraftPositionReportMessage";
    	    case AisStaticAndVoyageRelatedDataMessage:
    	        return "AisStaticAndVoyageRelatedDataMessage";
    	    case AisStaticDataReportMessage:
    	        return "AisStaticDataReportMessage";
    	    case AisStaticDataReportPartAMessage:
    	        return "AisStaticDataReportPartAMessage";
    	    case AisStaticDataReportPartBMessage:
    	        return "AisStaticDataReportPartBMessage";
    	    case AisUtcAndDateInquiryMessage:
    	        return "AisUtcAndDateInquiryMessage";
    	    case AisUtcAndDateResponseMessage:
    	        return "AisUtcAndDateResponseMessage";
    	    case AlarmStateChange:
    	        return "AlarmStateChange";
    	    case BaseStationType:
    	        return "BaseStationType";
    	    case BinaryTimeseriesValue:
    	        return "BinaryTimeseriesValue";
    	    case Bookmark:
    	        return "Bookmark";
    	    case BooleanTimeseriesValue:
    	        return "BooleanTimeseriesValue";
    	    case ByteTimeseriesValue:
    	        return "ByteTimeseriesValue";
    	    case CameraCommand:
    	        return "CameraCommand";
    	    case CameraCommandAbsoluteMove:
    	        return "CameraCommandAbsoluteMove";
    	    case CameraCommandAdjustPanTiltZoom:
    	        return "CameraCommandAdjustPanTiltZoom";
    	    case CameraCommandContinuousMove:
    	        return "CameraCommandContinuousMove";
    	    case CameraCommandGeoMove:
    	        return "CameraCommandGeoMove";
    	    case CameraCommandRelativeMove:
    	        return "CameraCommandRelativeMove";
    	    case CameraCommandReleasePTZOwnership:
    	        return "CameraCommandReleasePTZOwnership";
    	    case CameraCommandRequestPTZOwnership:
    	        return "CameraCommandRequestPTZOwnership";
    	    case CameraCommandSetAutoFocus:
    	        return "CameraCommandSetAutoFocus";
    	    case CameraCommandSetBlackAndWhite:
    	        return "CameraCommandSetBlackAndWhite";
    	    case CameraCommandSetFollowed:
    	        return "CameraCommandSetFollowed";
    	    case CameraCommandSetInfraRedLamp:
    	        return "CameraCommandSetInfraRedLamp";
    	    case CameraCommandSetWasher:
    	        return "CameraCommandSetWasher";
    	    case CameraCommandSetWiper:
    	        return "CameraCommandSetWiper";
    	    case CameraCommandStop:
    	        return "CameraCommandStop";
    	    case CameraCommandReply:
    	        return "CameraCommandReply";
    	    case CameraConfiguration:
    	        return "CameraConfiguration";
    	    case CameraPanCalibration:
    	        return "CameraPanCalibration";
    	    case CameraPanCalibrationValue:
    	        return "CameraPanCalibrationValue";
    	    case CameraStatus:
    	        return "CameraStatus";
    	    case CameraTiltCalibration:
    	        return "CameraTiltCalibration";
    	    case CameraTiltCalibrationValue:
    	        return "CameraTiltCalibrationValue";
    	    case CameraZoomCalibration:
    	        return "CameraZoomCalibration";
    	    case CameraZoomCalibrationValue:
    	        return "CameraZoomCalibrationValue";
    	    case CatalogElement:
    	        return "CatalogElement";
    	    case Catalog:
    	        return "Catalog";
    	    case Element:
    	        return "Element";
    	    case CollectionInfo:
    	        return "CollectionInfo";
    	    case Country:
    	        return "Country";
    	    case CursorInfo:
    	        return "CursorInfo";
    	    case DateTimeTimeseriesValue:
    	        return "DateTimeTimeseriesValue";
    	    case DeviceHost:
    	        return "DeviceHost";
    	    case DeviceHostConfiguration:
    	        return "DeviceHostConfiguration";
    	    case DoubleTimeseriesValue:
    	        return "DoubleTimeseriesValue";
    	    case FacilityType:
    	        return "FacilityType";
    	    case GeoPosition2DTimeseriesValue:
    	        return "GeoPosition2DTimeseriesValue";
    	    case GeoPosition3DTimeseriesValue:
    	        return "GeoPosition3DTimeseriesValue";
    	    case GNSSDeviceCommand:
    	        return "GNSSDeviceCommand";
    	    case GNSSDeviceCommandReply:
    	        return "GNSSDeviceCommandReply";
    	    case GNSSDeviceConfiguration:
    	        return "GNSSDeviceConfiguration";
    	    case GuidTimeseriesValue:
    	        return "GuidTimeseriesValue";
    	    case GyroDeviceCommand:
    	        return "GyroDeviceCommand";
    	    case GyroDeviceCommandReply:
    	        return "GyroDeviceCommandReply";
    	    case GyroDeviceConfiguration:
    	        return "GyroDeviceConfiguration";
    	    case Identity:
    	        return "Identity";
    	    case Callsign:
    	        return "Callsign";
    	    case InternationalMaritimeOrganizationNumber:
    	        return "InternationalMaritimeOrganizationNumber";
    	    case MaritimeMobileServiceIdentity:
    	        return "MaritimeMobileServiceIdentity";
    	    case Name:
    	        return "Name";
    	    case Int16TimeseriesValue:
    	        return "Int16TimeseriesValue";
    	    case Int32TimeseriesValue:
    	        return "Int32TimeseriesValue";
    	    case Int64TimeseriesValue:
    	        return "Int64TimeseriesValue";
    	    case Item:
    	        return "Item";
    	    case BaseStation:
    	        return "BaseStation";
    	    case Device:
    	        return "Device";
    	    case CameraDevice:
    	        return "CameraDevice";
    	    case GNSSDevice:
    	        return "GNSSDevice";
    	    case GyroDevice:
    	        return "GyroDevice";
    	    case LineInputDevice:
    	        return "LineInputDevice";
    	    case OilSpillDetectorDevice:
    	        return "OilSpillDetectorDevice";
    	    case RadioDevice:
    	        return "RadioDevice";
    	    case RadomeDevice:
    	        return "RadomeDevice";
    	    case TrackerDevice:
    	        return "TrackerDevice";
    	    case AisDevice:
    	        return "AisDevice";
    	    case RadarDevice:
    	        return "RadarDevice";
    	    case WeatherStationDevice:
    	        return "WeatherStationDevice";
    	    case Facility:
    	        return "Facility";
    	    case TrackableItem:
    	        return "TrackableItem";
    	    case Aircraft:
    	        return "Aircraft";
    	    case AisAidToNavigation:
    	        return "AisAidToNavigation";
    	    case Vehicle:
    	        return "Vehicle";
    	    case Vessel:
    	        return "Vessel";
    	    case ItemIdentityLink:
    	        return "ItemIdentityLink";
    	    case ItemParentChildLink:
    	        return "ItemParentChildLink";
    	    case LineInputDeviceCommand:
    	        return "LineInputDeviceCommand";
    	    case LineInputDeviceCommandReply:
    	        return "LineInputDeviceCommandReply";
    	    case LineInputDeviceConfiguration:
    	        return "LineInputDeviceConfiguration";
    	    case LineInputMessageRouting:
    	        return "LineInputMessageRouting";
    	    case LineInputMessageRoutingDestination:
    	        return "LineInputMessageRoutingDestination";
    	    case LineInputWhiteListEntry:
    	        return "LineInputWhiteListEntry";
    	    case LogApplication:
    	        return "LogApplication";
    	    case LogApplicationConfiguration:
    	        return "LogApplicationConfiguration";
    	    case LogHost:
    	        return "LogHost";
    	    case LogHostConfiguration:
    	        return "LogHostConfiguration";
    	    case LogLocation:
    	        return "LogLocation";
    	    case LogProcess:
    	        return "LogProcess";
    	    case LogRecord:
    	        return "LogRecord";
    	    case LogThread:
    	        return "LogThread";
    	    case LogTraceEntry:
    	        return "LogTraceEntry";
    	    case MapElement:
    	        return "MapElement";
    	    case MapInfo:
    	        return "MapInfo";
    	    case MapServiceOptions:
    	        return "MapServiceOptions";
    	    case MaritimeIdentificationDigits:
    	        return "MaritimeIdentificationDigits";
    	    case MediaProxySession:
    	        return "MediaProxySession";
    	    case MediaProxySessionFile:
    	        return "MediaProxySessionFile";
    	    case MediaProxySessionOptions:
    	        return "MediaProxySessionOptions";
    	    case MediaService:
    	        return "MediaService";
    	    case MediaServiceOptions:
    	        return "MediaServiceOptions";
    	    case NamespaceElement:
    	        return "NamespaceElement";
    	    case ElementType:
    	        return "ElementType";
    	    case Namespace:
    	        return "Namespace";
    	    case OilSpill:
    	        return "OilSpill";
    	    case OilSpillDetectorCommand:
    	        return "OilSpillDetectorCommand";
    	    case OilSpillDetectorCommandReply:
    	        return "OilSpillDetectorCommandReply";
    	    case OilSpillDetectorConfiguration:
    	        return "OilSpillDetectorConfiguration";
    	    case Position2DTimeseriesValue:
    	        return "Position2DTimeseriesValue";
    	    case Position3DTimeseriesValue:
    	        return "Position3DTimeseriesValue";
    	    case ProcessTrackValueResult:
    	        return "ProcessTrackValueResult";
    	    case Property:
    	        return "Property";
    	    case BinaryProperty:
    	        return "BinaryProperty";
    	    case BooleanProperty:
    	        return "BooleanProperty";
    	    case ByteProperty:
    	        return "ByteProperty";
    	    case DateTimeProperty:
    	        return "DateTimeProperty";
    	    case DoubleProperty:
    	        return "DoubleProperty";
    	    case GuidProperty:
    	        return "GuidProperty";
    	    case Int16Property:
    	        return "Int16Property";
    	    case Int32Property:
    	        return "Int32Property";
    	    case Int64Property:
    	        return "Int64Property";
    	    case ReferenceProperty:
    	        return "ReferenceProperty";
    	    case SByteProperty:
    	        return "SByteProperty";
    	    case SingleProperty:
    	        return "SingleProperty";
    	    case StringProperty:
    	        return "StringProperty";
    	    case TimeseriesProperty:
    	        return "TimeseriesProperty";
    	    case BinaryTimeseriesProperty:
    	        return "BinaryTimeseriesProperty";
    	    case BooleanTimeseriesProperty:
    	        return "BooleanTimeseriesProperty";
    	    case ByteTimeseriesProperty:
    	        return "ByteTimeseriesProperty";
    	    case DateTimeTimeseriesProperty:
    	        return "DateTimeTimeseriesProperty";
    	    case DoubleTimeseriesProperty:
    	        return "DoubleTimeseriesProperty";
    	    case GuidTimeseriesProperty:
    	        return "GuidTimeseriesProperty";
    	    case Int16TimeseriesProperty:
    	        return "Int16TimeseriesProperty";
    	    case Int32TimeseriesProperty:
    	        return "Int32TimeseriesProperty";
    	    case Int64TimeseriesProperty:
    	        return "Int64TimeseriesProperty";
    	    case ReferenceTimeseriesProperty:
    	        return "ReferenceTimeseriesProperty";
    	    case SByteTimeseriesProperty:
    	        return "SByteTimeseriesProperty";
    	    case SingleTimeseriesProperty:
    	        return "SingleTimeseriesProperty";
    	    case StringTimeseriesProperty:
    	        return "StringTimeseriesProperty";
    	    case TimeSpanTimeseriesProperty:
    	        return "TimeSpanTimeseriesProperty";
    	    case UInt16TimeseriesProperty:
    	        return "UInt16TimeseriesProperty";
    	    case UInt32TimeseriesProperty:
    	        return "UInt32TimeseriesProperty";
    	    case UInt64TimeseriesProperty:
    	        return "UInt64TimeseriesProperty";
    	    case TimeSpanProperty:
    	        return "TimeSpanProperty";
    	    case UInt16Property:
    	        return "UInt16Property";
    	    case UInt32Property:
    	        return "UInt32Property";
    	    case UInt64Property:
    	        return "UInt64Property";
    	    case PropertyDefinition:
    	        return "PropertyDefinition";
    	    case BinaryPropertyDefinition:
    	        return "BinaryPropertyDefinition";
    	    case BooleanPropertyDefinition:
    	        return "BooleanPropertyDefinition";
    	    case BytePropertyDefinition:
    	        return "BytePropertyDefinition";
    	    case DateTimePropertyDefinition:
    	        return "DateTimePropertyDefinition";
    	    case DoublePropertyDefinition:
    	        return "DoublePropertyDefinition";
    	    case GuidPropertyDefinition:
    	        return "GuidPropertyDefinition";
    	    case Int16PropertyDefinition:
    	        return "Int16PropertyDefinition";
    	    case Int32PropertyDefinition:
    	        return "Int32PropertyDefinition";
    	    case Int64PropertyDefinition:
    	        return "Int64PropertyDefinition";
    	    case ReferencePropertyDefinition:
    	        return "ReferencePropertyDefinition";
    	    case SBytePropertyDefinition:
    	        return "SBytePropertyDefinition";
    	    case SinglePropertyDefinition:
    	        return "SinglePropertyDefinition";
    	    case StringPropertyDefinition:
    	        return "StringPropertyDefinition";
    	    case TimeseriesPropertyDefinition:
    	        return "TimeseriesPropertyDefinition";
    	    case BinaryTimeseriesPropertyDefinition:
    	        return "BinaryTimeseriesPropertyDefinition";
    	    case BooleanTimeseriesPropertyDefinition:
    	        return "BooleanTimeseriesPropertyDefinition";
    	    case ByteTimeseriesPropertyDefinition:
    	        return "ByteTimeseriesPropertyDefinition";
    	    case DateTimeTimeseriesPropertyDefinition:
    	        return "DateTimeTimeseriesPropertyDefinition";
    	    case DoubleTimeseriesPropertyDefinition:
    	        return "DoubleTimeseriesPropertyDefinition";
    	    case GuidTimeseriesPropertyDefinition:
    	        return "GuidTimeseriesPropertyDefinition";
    	    case Int16TimeseriesPropertyDefinition:
    	        return "Int16TimeseriesPropertyDefinition";
    	    case Int32TimeseriesPropertyDefinition:
    	        return "Int32TimeseriesPropertyDefinition";
    	    case Int64TimeseriesPropertyDefinition:
    	        return "Int64TimeseriesPropertyDefinition";
    	    case ReferenceTimeseriesPropertyDefinition:
    	        return "ReferenceTimeseriesPropertyDefinition";
    	    case SByteTimeseriesPropertyDefinition:
    	        return "SByteTimeseriesPropertyDefinition";
    	    case SingleTimeseriesPropertyDefinition:
    	        return "SingleTimeseriesPropertyDefinition";
    	    case StringTimeseriesPropertyDefinition:
    	        return "StringTimeseriesPropertyDefinition";
    	    case TimeSpanTimeseriesPropertyDefinition:
    	        return "TimeSpanTimeseriesPropertyDefinition";
    	    case UInt16TimeseriesPropertyDefinition:
    	        return "UInt16TimeseriesPropertyDefinition";
    	    case UInt32TimeseriesPropertyDefinition:
    	        return "UInt32TimeseriesPropertyDefinition";
    	    case UInt64TimeseriesPropertyDefinition:
    	        return "UInt64TimeseriesPropertyDefinition";
    	    case TimeSpanPropertyDefinition:
    	        return "TimeSpanPropertyDefinition";
    	    case UInt16PropertyDefinition:
    	        return "UInt16PropertyDefinition";
    	    case UInt32PropertyDefinition:
    	        return "UInt32PropertyDefinition";
    	    case UInt64PropertyDefinition:
    	        return "UInt64PropertyDefinition";
    	    case RadarAlarmStatus:
    	        return "RadarAlarmStatus";
    	    case RadarCommand:
    	        return "RadarCommand";
    	    case RadarCommandGetStatus:
    	        return "RadarCommandGetStatus";
    	    case RadarCommandReply:
    	        return "RadarCommandReply";
    	    case RadarCommandReplyGetStatus:
    	        return "RadarCommandReplyGetStatus";
    	    case RadarConfiguration:
    	        return "RadarConfiguration";
    	    case RadarImage:
    	        return "RadarImage";
    	    case RadarRawTrackTable:
    	        return "RadarRawTrackTable";
    	    case RadarStatus:
    	        return "RadarStatus";
    	    case RadioCommand:
    	        return "RadioCommand";
    	    case RadioCommandReply:
    	        return "RadioCommandReply";
    	    case RadioConfiguration:
    	        return "RadioConfiguration";
    	    case RadomeCommand:
    	        return "RadomeCommand";
    	    case RadomeCommandReply:
    	        return "RadomeCommandReply";
    	    case RadomeConfiguration:
    	        return "RadomeConfiguration";
    	    case ReferenceTimeseriesValue:
    	        return "ReferenceTimeseriesValue";
    	    case SByteTimeseriesValue:
    	        return "SByteTimeseriesValue";
    	    case SecurityDomain:
    	        return "SecurityDomain";
    	    case SecurityIdentifier:
    	        return "SecurityIdentifier";
    	    case SecurityLogin:
    	        return "SecurityLogin";
    	    case SecurityRole:
    	        return "SecurityRole";
    	    case SecurityIdentifierRoleLink:
    	        return "SecurityIdentifierRoleLink";
    	    case SecurityLoginSession:
    	        return "SecurityLoginSession";
    	    case SecurityPermission:
    	        return "SecurityPermission";
    	    case SingleTimeseriesValue:
    	        return "SingleTimeseriesValue";
    	    case StringTimeseriesValue:
    	        return "StringTimeseriesValue";
    	    case TimeseriesCatalogElement:
    	        return "TimeseriesCatalogElement";
    	    case Timeseries:
    	        return "Timeseries";
    	    case BinaryTimeseries:
    	        return "BinaryTimeseries";
    	    case BooleanTimeseries:
    	        return "BooleanTimeseries";
    	    case AisAidToNavigationOffPositionTimeseries:
    	        return "AisAidToNavigationOffPositionTimeseries";
    	    case DeviceEnabledTimeseries:
    	        return "DeviceEnabledTimeseries";
    	    case RadarAutomaticSensitivityTimeControlTimeseries:
    	        return "RadarAutomaticSensitivityTimeControlTimeseries";
    	    case RadarBlankSector1Timeseries:
    	        return "RadarBlankSector1Timeseries";
    	    case RadarBlankSector2Timeseries:
    	        return "RadarBlankSector2Timeseries";
    	    case RadarEnableAutomaticFrequencyControlTimeseries:
    	        return "RadarEnableAutomaticFrequencyControlTimeseries";
    	    case RadarEnableFastTimeConstantTimeseries:
    	        return "RadarEnableFastTimeConstantTimeseries";
    	    case RadarEnableSensitivityTimeControlTimeseries:
    	        return "RadarEnableSensitivityTimeControlTimeseries";
    	    case RadarPowerOnTimeseries:
    	        return "RadarPowerOnTimeseries";
    	    case RadarSaveSettingsTimeseries:
    	        return "RadarSaveSettingsTimeseries";
    	    case RadarTrackingTimeseries:
    	        return "RadarTrackingTimeseries";
    	    case MediaProxySessionEnabledTimeseries:
    	        return "MediaProxySessionEnabledTimeseries";
    	    case MediaServiceEnabledTimeseries:
    	        return "MediaServiceEnabledTimeseries";
    	    case ByteTimeseries:
    	        return "ByteTimeseries";
    	    case DateTimeTimeseries:
    	        return "DateTimeTimeseries";
    	    case DoubleTimeseries:
    	        return "DoubleTimeseries";
    	    case GNSSAltitudeTimeseries:
    	        return "GNSSAltitudeTimeseries";
    	    case GNSSLatitudeTimeseries:
    	        return "GNSSLatitudeTimeseries";
    	    case GNSSLongitudeTimeseries:
    	        return "GNSSLongitudeTimeseries";
    	    case GyroCourseTimeseries:
    	        return "GyroCourseTimeseries";
    	    case GyroHeadingMagneticNorthTimeseries:
    	        return "GyroHeadingMagneticNorthTimeseries";
    	    case GyroHeadingTrueNorthTimeseries:
    	        return "GyroHeadingTrueNorthTimeseries";
    	    case GyroPitchTimeseries:
    	        return "GyroPitchTimeseries";
    	    case GyroRateOfTurnTimeseries:
    	        return "GyroRateOfTurnTimeseries";
    	    case GyroRollTimeseries:
    	        return "GyroRollTimeseries";
    	    case GyroSpeedTimeseries:
    	        return "GyroSpeedTimeseries";
    	    case RadarLatitudeTimeseries:
    	        return "RadarLatitudeTimeseries";
    	    case RadarLongitudeTimeseries:
    	        return "RadarLongitudeTimeseries";
    	    case RadomeDewPointTimeseries:
    	        return "RadomeDewPointTimeseries";
    	    case RadomePressureTimeseries:
    	        return "RadomePressureTimeseries";
    	    case RadomeTemperatureTimeseries:
    	        return "RadomeTemperatureTimeseries";
    	    case VesselDraughtTimeseries:
    	        return "VesselDraughtTimeseries";
    	    case ViewLatitudeTimeseries:
    	        return "ViewLatitudeTimeseries";
    	    case ViewLongitudeTimeseries:
    	        return "ViewLongitudeTimeseries";
    	    case ViewZoomLevelTimeseries:
    	        return "ViewZoomLevelTimeseries";
    	    case WeatherStationAbsoluteHumidityTimeseries:
    	        return "WeatherStationAbsoluteHumidityTimeseries";
    	    case WeatherStationAirTemperatureTimeseries:
    	        return "WeatherStationAirTemperatureTimeseries";
    	    case WeatherStationBarometricPressureTimeseries:
    	        return "WeatherStationBarometricPressureTimeseries";
    	    case WeatherStationDewPointTimeseries:
    	        return "WeatherStationDewPointTimeseries";
    	    case WeatherStationRelativeHumidityTimeseries:
    	        return "WeatherStationRelativeHumidityTimeseries";
    	    case WeatherStationWaterTemperatureTimeseries:
    	        return "WeatherStationWaterTemperatureTimeseries";
    	    case WeatherStationWindDirectionTimeseries:
    	        return "WeatherStationWindDirectionTimeseries";
    	    case WeatherStationWindSpeedTimeseries:
    	        return "WeatherStationWindSpeedTimeseries";
    	    case GeoPosition2DTimeseries:
    	        return "GeoPosition2DTimeseries";
    	    case AisAidToNavigationPositionTimeseries:
    	        return "AisAidToNavigationPositionTimeseries";
    	    case GeoPosition3DTimeseries:
    	        return "GeoPosition3DTimeseries";
    	    case GuidTimeseries:
    	        return "GuidTimeseries";
    	    case Int16Timeseries:
    	        return "Int16Timeseries";
    	    case Int32Timeseries:
    	        return "Int32Timeseries";
    	    case RadarAzimuthOffsetTimeseries:
    	        return "RadarAzimuthOffsetTimeseries";
    	    case RadarFastTimeConstantLevelTimeseries:
    	        return "RadarFastTimeConstantLevelTimeseries";
    	    case RadarFastTimeConstantModeTimeseries:
    	        return "RadarFastTimeConstantModeTimeseries";
    	    case RadarPulseTimeseries:
    	        return "RadarPulseTimeseries";
    	    case RadarSector1EndTimeseries:
    	        return "RadarSector1EndTimeseries";
    	    case RadarSector1StartTimeseries:
    	        return "RadarSector1StartTimeseries";
    	    case RadarSector2EndTimeseries:
    	        return "RadarSector2EndTimeseries";
    	    case RadarSector2StartTimeseries:
    	        return "RadarSector2StartTimeseries";
    	    case RadarSensitivityTimeControlLevelTimeseries:
    	        return "RadarSensitivityTimeControlLevelTimeseries";
    	    case RadarTuningTimeseries:
    	        return "RadarTuningTimeseries";
    	    case VesselPersonsOnBoardTimeseries:
    	        return "VesselPersonsOnBoardTimeseries";
    	    case Int64Timeseries:
    	        return "Int64Timeseries";
    	    case Position2DTimeseries:
    	        return "Position2DTimeseries";
    	    case Position3DTimeseries:
    	        return "Position3DTimeseries";
    	    case ReferenceTimeseries:
    	        return "ReferenceTimeseries";
    	    case SByteTimeseries:
    	        return "SByteTimeseries";
    	    case SingleTimeseries:
    	        return "SingleTimeseries";
    	    case StringTimeseries:
    	        return "StringTimeseries";
    	    case TimeSpanTimeseries:
    	        return "TimeSpanTimeseries";
    	    case UInt16Timeseries:
    	        return "UInt16Timeseries";
    	    case UInt32Timeseries:
    	        return "UInt32Timeseries";
    	    case RadomeStatusTimeseries:
    	        return "RadomeStatusTimeseries";
    	    case UInt64Timeseries:
    	        return "UInt64Timeseries";
    	    case TimeseriesCatalog:
    	        return "TimeseriesCatalog";
    	    case TimeseriesInfo:
    	        return "TimeseriesInfo";
    	    case TimeSpanTimeseriesValue:
    	        return "TimeSpanTimeseriesValue";
    	    case TrackableItemTrackLink:
    	        return "TrackableItemTrackLink";
    	    case TrackBase:
    	        return "TrackBase";
    	    case Track:
    	        return "Track";
    	    case Track3D:
    	        return "Track3D";
    	    case TrackerFilterParameters:
    	        return "TrackerFilterParameters";
    	    case TrackerFilterParametersConfiguration:
    	        return "TrackerFilterParametersConfiguration";
    	    case TrackInfo:
    	        return "TrackInfo";
    	    case TrackingServiceOptions:
    	        return "TrackingServiceOptions";
    	    case TrackLink:
    	        return "TrackLink";
    	    case TrackValue:
    	        return "TrackValue";
    	    case TrackValue3D:
    	        return "TrackValue3D";
    	    case UInt16TimeseriesValue:
    	        return "UInt16TimeseriesValue";
    	    case UInt32TimeseriesValue:
    	        return "UInt32TimeseriesValue";
    	    case UInt64TimeseriesValue:
    	        return "UInt64TimeseriesValue";
    	    case VehicleType:
    	        return "VehicleType";
    	    case VesselType:
    	        return "VesselType";
    	    case View:
    	        return "View";
    	    case ViewCameraLink:
    	        return "ViewCameraLink";
    	    case ViewTrackerLink:
    	        return "ViewTrackerLink";
    	    case WeatherStationCommand:
    	        return "WeatherStationCommand";
    	    case WeatherStationCommandReply:
    	        return "WeatherStationCommandReply";
    	    case WeatherStationConfiguration:
    	        return "WeatherStationConfiguration";
    	    case Zone:
    	        return "Zone";
    	    case CircularZone:
    	        return "CircularZone";
    	    case PolygonZone:
    	        return "PolygonZone";
    	    case ZoneExceptions:
    	        return "ZoneExceptions";
    	    case ZoneExceptionsVesselLink:
    	        return "ZoneExceptionsVesselLink";
    	    case ZoneTrackAlarm:
    	        return "ZoneTrackAlarm";
    	    default:
    	        return "Unknown(" + Integer.toUnsignedString(value, 10) + ")";
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "AircraftType":
    	        return AircraftType;
    	    case "AisDeviceCommand":
    	        return AisDeviceCommand;
    	    case "AisDeviceCommandReply":
    	        return AisDeviceCommandReply;
    	    case "AisDeviceConfiguration":
    	        return AisDeviceConfiguration;
    	    case "AisDeviceRawMessage":
    	        return AisDeviceRawMessage;
    	    case "AisDeviceRawSentence":
    	        return AisDeviceRawSentence;
    	    case "AisMessage":
    	        return AisMessage;
    	    case "AidToNavigationReportMessage":
    	        return AidToNavigationReportMessage;
    	    case "AisAddressedSafetyRelatedMessage":
    	        return AisAddressedSafetyRelatedMessage;
    	    case "AisBaseStationReportMessage":
    	        return AisBaseStationReportMessage;
    	    case "AisBinaryAcknowledgeMessage":
    	        return AisBinaryAcknowledgeMessage;
    	    case "AisBinaryAddressedMessage":
    	        return AisBinaryAddressedMessage;
    	    case "AisBinaryBroadcastMessage":
    	        return AisBinaryBroadcastMessage;
    	    case "AisDataLinkManagementMessage":
    	        return AisDataLinkManagementMessage;
    	    case "AisExtendedClassBCsPositionReportMessage":
    	        return AisExtendedClassBCsPositionReportMessage;
    	    case "AisInterrogationMessage":
    	        return AisInterrogationMessage;
    	    case "AisPositionReportClassAMessageBase":
    	        return AisPositionReportClassAMessageBase;
    	    case "AisPositionReportClassAAssignedScheduleMessage":
    	        return AisPositionReportClassAAssignedScheduleMessage;
    	    case "AisPositionReportClassAMessage":
    	        return AisPositionReportClassAMessage;
    	    case "AisPositionReportClassAResponseToInterrogationMessage":
    	        return AisPositionReportClassAResponseToInterrogationMessage;
    	    case "AisPositionReportForLongRangeApplicationsMessage":
    	        return AisPositionReportForLongRangeApplicationsMessage;
    	    case "AisSafetyRelatedAcknowledgmentMessage":
    	        return AisSafetyRelatedAcknowledgmentMessage;
    	    case "AisStandardClassBCsPositionReportMessage":
    	        return AisStandardClassBCsPositionReportMessage;
    	    case "AisStandardSarAircraftPositionReportMessage":
    	        return AisStandardSarAircraftPositionReportMessage;
    	    case "AisStaticAndVoyageRelatedDataMessage":
    	        return AisStaticAndVoyageRelatedDataMessage;
    	    case "AisStaticDataReportMessage":
    	        return AisStaticDataReportMessage;
    	    case "AisStaticDataReportPartAMessage":
    	        return AisStaticDataReportPartAMessage;
    	    case "AisStaticDataReportPartBMessage":
    	        return AisStaticDataReportPartBMessage;
    	    case "AisUtcAndDateInquiryMessage":
    	        return AisUtcAndDateInquiryMessage;
    	    case "AisUtcAndDateResponseMessage":
    	        return AisUtcAndDateResponseMessage;
    	    case "AlarmStateChange":
    	        return AlarmStateChange;
    	    case "BaseStationType":
    	        return BaseStationType;
    	    case "BinaryTimeseriesValue":
    	        return BinaryTimeseriesValue;
    	    case "Bookmark":
    	        return Bookmark;
    	    case "BooleanTimeseriesValue":
    	        return BooleanTimeseriesValue;
    	    case "ByteTimeseriesValue":
    	        return ByteTimeseriesValue;
    	    case "CameraCommand":
    	        return CameraCommand;
    	    case "CameraCommandAbsoluteMove":
    	        return CameraCommandAbsoluteMove;
    	    case "CameraCommandAdjustPanTiltZoom":
    	        return CameraCommandAdjustPanTiltZoom;
    	    case "CameraCommandContinuousMove":
    	        return CameraCommandContinuousMove;
    	    case "CameraCommandGeoMove":
    	        return CameraCommandGeoMove;
    	    case "CameraCommandRelativeMove":
    	        return CameraCommandRelativeMove;
    	    case "CameraCommandReleasePTZOwnership":
    	        return CameraCommandReleasePTZOwnership;
    	    case "CameraCommandRequestPTZOwnership":
    	        return CameraCommandRequestPTZOwnership;
    	    case "CameraCommandSetAutoFocus":
    	        return CameraCommandSetAutoFocus;
    	    case "CameraCommandSetBlackAndWhite":
    	        return CameraCommandSetBlackAndWhite;
    	    case "CameraCommandSetFollowed":
    	        return CameraCommandSetFollowed;
    	    case "CameraCommandSetInfraRedLamp":
    	        return CameraCommandSetInfraRedLamp;
    	    case "CameraCommandSetWasher":
    	        return CameraCommandSetWasher;
    	    case "CameraCommandSetWiper":
    	        return CameraCommandSetWiper;
    	    case "CameraCommandStop":
    	        return CameraCommandStop;
    	    case "CameraCommandReply":
    	        return CameraCommandReply;
    	    case "CameraConfiguration":
    	        return CameraConfiguration;
    	    case "CameraPanCalibration":
    	        return CameraPanCalibration;
    	    case "CameraPanCalibrationValue":
    	        return CameraPanCalibrationValue;
    	    case "CameraStatus":
    	        return CameraStatus;
    	    case "CameraTiltCalibration":
    	        return CameraTiltCalibration;
    	    case "CameraTiltCalibrationValue":
    	        return CameraTiltCalibrationValue;
    	    case "CameraZoomCalibration":
    	        return CameraZoomCalibration;
    	    case "CameraZoomCalibrationValue":
    	        return CameraZoomCalibrationValue;
    	    case "CatalogElement":
    	        return CatalogElement;
    	    case "Catalog":
    	        return Catalog;
    	    case "Element":
    	        return Element;
    	    case "CollectionInfo":
    	        return CollectionInfo;
    	    case "Country":
    	        return Country;
    	    case "CursorInfo":
    	        return CursorInfo;
    	    case "DateTimeTimeseriesValue":
    	        return DateTimeTimeseriesValue;
    	    case "DeviceHost":
    	        return DeviceHost;
    	    case "DeviceHostConfiguration":
    	        return DeviceHostConfiguration;
    	    case "DoubleTimeseriesValue":
    	        return DoubleTimeseriesValue;
    	    case "FacilityType":
    	        return FacilityType;
    	    case "GeoPosition2DTimeseriesValue":
    	        return GeoPosition2DTimeseriesValue;
    	    case "GeoPosition3DTimeseriesValue":
    	        return GeoPosition3DTimeseriesValue;
    	    case "GNSSDeviceCommand":
    	        return GNSSDeviceCommand;
    	    case "GNSSDeviceCommandReply":
    	        return GNSSDeviceCommandReply;
    	    case "GNSSDeviceConfiguration":
    	        return GNSSDeviceConfiguration;
    	    case "GuidTimeseriesValue":
    	        return GuidTimeseriesValue;
    	    case "GyroDeviceCommand":
    	        return GyroDeviceCommand;
    	    case "GyroDeviceCommandReply":
    	        return GyroDeviceCommandReply;
    	    case "GyroDeviceConfiguration":
    	        return GyroDeviceConfiguration;
    	    case "Identity":
    	        return Identity;
    	    case "Callsign":
    	        return Callsign;
    	    case "InternationalMaritimeOrganizationNumber":
    	        return InternationalMaritimeOrganizationNumber;
    	    case "MaritimeMobileServiceIdentity":
    	        return MaritimeMobileServiceIdentity;
    	    case "Name":
    	        return Name;
    	    case "Int16TimeseriesValue":
    	        return Int16TimeseriesValue;
    	    case "Int32TimeseriesValue":
    	        return Int32TimeseriesValue;
    	    case "Int64TimeseriesValue":
    	        return Int64TimeseriesValue;
    	    case "Item":
    	        return Item;
    	    case "BaseStation":
    	        return BaseStation;
    	    case "Device":
    	        return Device;
    	    case "CameraDevice":
    	        return CameraDevice;
    	    case "GNSSDevice":
    	        return GNSSDevice;
    	    case "GyroDevice":
    	        return GyroDevice;
    	    case "LineInputDevice":
    	        return LineInputDevice;
    	    case "OilSpillDetectorDevice":
    	        return OilSpillDetectorDevice;
    	    case "RadioDevice":
    	        return RadioDevice;
    	    case "RadomeDevice":
    	        return RadomeDevice;
    	    case "TrackerDevice":
    	        return TrackerDevice;
    	    case "AisDevice":
    	        return AisDevice;
    	    case "RadarDevice":
    	        return RadarDevice;
    	    case "WeatherStationDevice":
    	        return WeatherStationDevice;
    	    case "Facility":
    	        return Facility;
    	    case "TrackableItem":
    	        return TrackableItem;
    	    case "Aircraft":
    	        return Aircraft;
    	    case "AisAidToNavigation":
    	        return AisAidToNavigation;
    	    case "Vehicle":
    	        return Vehicle;
    	    case "Vessel":
    	        return Vessel;
    	    case "ItemIdentityLink":
    	        return ItemIdentityLink;
    	    case "ItemParentChildLink":
    	        return ItemParentChildLink;
    	    case "LineInputDeviceCommand":
    	        return LineInputDeviceCommand;
    	    case "LineInputDeviceCommandReply":
    	        return LineInputDeviceCommandReply;
    	    case "LineInputDeviceConfiguration":
    	        return LineInputDeviceConfiguration;
    	    case "LineInputMessageRouting":
    	        return LineInputMessageRouting;
    	    case "LineInputMessageRoutingDestination":
    	        return LineInputMessageRoutingDestination;
    	    case "LineInputWhiteListEntry":
    	        return LineInputWhiteListEntry;
    	    case "LogApplication":
    	        return LogApplication;
    	    case "LogApplicationConfiguration":
    	        return LogApplicationConfiguration;
    	    case "LogHost":
    	        return LogHost;
    	    case "LogHostConfiguration":
    	        return LogHostConfiguration;
    	    case "LogLocation":
    	        return LogLocation;
    	    case "LogProcess":
    	        return LogProcess;
    	    case "LogRecord":
    	        return LogRecord;
    	    case "LogThread":
    	        return LogThread;
    	    case "LogTraceEntry":
    	        return LogTraceEntry;
    	    case "MapElement":
    	        return MapElement;
    	    case "MapInfo":
    	        return MapInfo;
    	    case "MapServiceOptions":
    	        return MapServiceOptions;
    	    case "MaritimeIdentificationDigits":
    	        return MaritimeIdentificationDigits;
    	    case "MediaProxySession":
    	        return MediaProxySession;
    	    case "MediaProxySessionFile":
    	        return MediaProxySessionFile;
    	    case "MediaProxySessionOptions":
    	        return MediaProxySessionOptions;
    	    case "MediaService":
    	        return MediaService;
    	    case "MediaServiceOptions":
    	        return MediaServiceOptions;
    	    case "NamespaceElement":
    	        return NamespaceElement;
    	    case "ElementType":
    	        return ElementType;
    	    case "Namespace":
    	        return Namespace;
    	    case "OilSpill":
    	        return OilSpill;
    	    case "OilSpillDetectorCommand":
    	        return OilSpillDetectorCommand;
    	    case "OilSpillDetectorCommandReply":
    	        return OilSpillDetectorCommandReply;
    	    case "OilSpillDetectorConfiguration":
    	        return OilSpillDetectorConfiguration;
    	    case "Position2DTimeseriesValue":
    	        return Position2DTimeseriesValue;
    	    case "Position3DTimeseriesValue":
    	        return Position3DTimeseriesValue;
    	    case "ProcessTrackValueResult":
    	        return ProcessTrackValueResult;
    	    case "Property":
    	        return Property;
    	    case "BinaryProperty":
    	        return BinaryProperty;
    	    case "BooleanProperty":
    	        return BooleanProperty;
    	    case "ByteProperty":
    	        return ByteProperty;
    	    case "DateTimeProperty":
    	        return DateTimeProperty;
    	    case "DoubleProperty":
    	        return DoubleProperty;
    	    case "GuidProperty":
    	        return GuidProperty;
    	    case "Int16Property":
    	        return Int16Property;
    	    case "Int32Property":
    	        return Int32Property;
    	    case "Int64Property":
    	        return Int64Property;
    	    case "ReferenceProperty":
    	        return ReferenceProperty;
    	    case "SByteProperty":
    	        return SByteProperty;
    	    case "SingleProperty":
    	        return SingleProperty;
    	    case "StringProperty":
    	        return StringProperty;
    	    case "TimeseriesProperty":
    	        return TimeseriesProperty;
    	    case "BinaryTimeseriesProperty":
    	        return BinaryTimeseriesProperty;
    	    case "BooleanTimeseriesProperty":
    	        return BooleanTimeseriesProperty;
    	    case "ByteTimeseriesProperty":
    	        return ByteTimeseriesProperty;
    	    case "DateTimeTimeseriesProperty":
    	        return DateTimeTimeseriesProperty;
    	    case "DoubleTimeseriesProperty":
    	        return DoubleTimeseriesProperty;
    	    case "GuidTimeseriesProperty":
    	        return GuidTimeseriesProperty;
    	    case "Int16TimeseriesProperty":
    	        return Int16TimeseriesProperty;
    	    case "Int32TimeseriesProperty":
    	        return Int32TimeseriesProperty;
    	    case "Int64TimeseriesProperty":
    	        return Int64TimeseriesProperty;
    	    case "ReferenceTimeseriesProperty":
    	        return ReferenceTimeseriesProperty;
    	    case "SByteTimeseriesProperty":
    	        return SByteTimeseriesProperty;
    	    case "SingleTimeseriesProperty":
    	        return SingleTimeseriesProperty;
    	    case "StringTimeseriesProperty":
    	        return StringTimeseriesProperty;
    	    case "TimeSpanTimeseriesProperty":
    	        return TimeSpanTimeseriesProperty;
    	    case "UInt16TimeseriesProperty":
    	        return UInt16TimeseriesProperty;
    	    case "UInt32TimeseriesProperty":
    	        return UInt32TimeseriesProperty;
    	    case "UInt64TimeseriesProperty":
    	        return UInt64TimeseriesProperty;
    	    case "TimeSpanProperty":
    	        return TimeSpanProperty;
    	    case "UInt16Property":
    	        return UInt16Property;
    	    case "UInt32Property":
    	        return UInt32Property;
    	    case "UInt64Property":
    	        return UInt64Property;
    	    case "PropertyDefinition":
    	        return PropertyDefinition;
    	    case "BinaryPropertyDefinition":
    	        return BinaryPropertyDefinition;
    	    case "BooleanPropertyDefinition":
    	        return BooleanPropertyDefinition;
    	    case "BytePropertyDefinition":
    	        return BytePropertyDefinition;
    	    case "DateTimePropertyDefinition":
    	        return DateTimePropertyDefinition;
    	    case "DoublePropertyDefinition":
    	        return DoublePropertyDefinition;
    	    case "GuidPropertyDefinition":
    	        return GuidPropertyDefinition;
    	    case "Int16PropertyDefinition":
    	        return Int16PropertyDefinition;
    	    case "Int32PropertyDefinition":
    	        return Int32PropertyDefinition;
    	    case "Int64PropertyDefinition":
    	        return Int64PropertyDefinition;
    	    case "ReferencePropertyDefinition":
    	        return ReferencePropertyDefinition;
    	    case "SBytePropertyDefinition":
    	        return SBytePropertyDefinition;
    	    case "SinglePropertyDefinition":
    	        return SinglePropertyDefinition;
    	    case "StringPropertyDefinition":
    	        return StringPropertyDefinition;
    	    case "TimeseriesPropertyDefinition":
    	        return TimeseriesPropertyDefinition;
    	    case "BinaryTimeseriesPropertyDefinition":
    	        return BinaryTimeseriesPropertyDefinition;
    	    case "BooleanTimeseriesPropertyDefinition":
    	        return BooleanTimeseriesPropertyDefinition;
    	    case "ByteTimeseriesPropertyDefinition":
    	        return ByteTimeseriesPropertyDefinition;
    	    case "DateTimeTimeseriesPropertyDefinition":
    	        return DateTimeTimeseriesPropertyDefinition;
    	    case "DoubleTimeseriesPropertyDefinition":
    	        return DoubleTimeseriesPropertyDefinition;
    	    case "GuidTimeseriesPropertyDefinition":
    	        return GuidTimeseriesPropertyDefinition;
    	    case "Int16TimeseriesPropertyDefinition":
    	        return Int16TimeseriesPropertyDefinition;
    	    case "Int32TimeseriesPropertyDefinition":
    	        return Int32TimeseriesPropertyDefinition;
    	    case "Int64TimeseriesPropertyDefinition":
    	        return Int64TimeseriesPropertyDefinition;
    	    case "ReferenceTimeseriesPropertyDefinition":
    	        return ReferenceTimeseriesPropertyDefinition;
    	    case "SByteTimeseriesPropertyDefinition":
    	        return SByteTimeseriesPropertyDefinition;
    	    case "SingleTimeseriesPropertyDefinition":
    	        return SingleTimeseriesPropertyDefinition;
    	    case "StringTimeseriesPropertyDefinition":
    	        return StringTimeseriesPropertyDefinition;
    	    case "TimeSpanTimeseriesPropertyDefinition":
    	        return TimeSpanTimeseriesPropertyDefinition;
    	    case "UInt16TimeseriesPropertyDefinition":
    	        return UInt16TimeseriesPropertyDefinition;
    	    case "UInt32TimeseriesPropertyDefinition":
    	        return UInt32TimeseriesPropertyDefinition;
    	    case "UInt64TimeseriesPropertyDefinition":
    	        return UInt64TimeseriesPropertyDefinition;
    	    case "TimeSpanPropertyDefinition":
    	        return TimeSpanPropertyDefinition;
    	    case "UInt16PropertyDefinition":
    	        return UInt16PropertyDefinition;
    	    case "UInt32PropertyDefinition":
    	        return UInt32PropertyDefinition;
    	    case "UInt64PropertyDefinition":
    	        return UInt64PropertyDefinition;
    	    case "RadarAlarmStatus":
    	        return RadarAlarmStatus;
    	    case "RadarCommand":
    	        return RadarCommand;
    	    case "RadarCommandGetStatus":
    	        return RadarCommandGetStatus;
    	    case "RadarCommandReply":
    	        return RadarCommandReply;
    	    case "RadarCommandReplyGetStatus":
    	        return RadarCommandReplyGetStatus;
    	    case "RadarConfiguration":
    	        return RadarConfiguration;
    	    case "RadarImage":
    	        return RadarImage;
    	    case "RadarRawTrackTable":
    	        return RadarRawTrackTable;
    	    case "RadarStatus":
    	        return RadarStatus;
    	    case "RadioCommand":
    	        return RadioCommand;
    	    case "RadioCommandReply":
    	        return RadioCommandReply;
    	    case "RadioConfiguration":
    	        return RadioConfiguration;
    	    case "RadomeCommand":
    	        return RadomeCommand;
    	    case "RadomeCommandReply":
    	        return RadomeCommandReply;
    	    case "RadomeConfiguration":
    	        return RadomeConfiguration;
    	    case "ReferenceTimeseriesValue":
    	        return ReferenceTimeseriesValue;
    	    case "SByteTimeseriesValue":
    	        return SByteTimeseriesValue;
    	    case "SecurityDomain":
    	        return SecurityDomain;
    	    case "SecurityIdentifier":
    	        return SecurityIdentifier;
    	    case "SecurityLogin":
    	        return SecurityLogin;
    	    case "SecurityRole":
    	        return SecurityRole;
    	    case "SecurityIdentifierRoleLink":
    	        return SecurityIdentifierRoleLink;
    	    case "SecurityLoginSession":
    	        return SecurityLoginSession;
    	    case "SecurityPermission":
    	        return SecurityPermission;
    	    case "SingleTimeseriesValue":
    	        return SingleTimeseriesValue;
    	    case "StringTimeseriesValue":
    	        return StringTimeseriesValue;
    	    case "TimeseriesCatalogElement":
    	        return TimeseriesCatalogElement;
    	    case "Timeseries":
    	        return Timeseries;
    	    case "BinaryTimeseries":
    	        return BinaryTimeseries;
    	    case "BooleanTimeseries":
    	        return BooleanTimeseries;
    	    case "AisAidToNavigationOffPositionTimeseries":
    	        return AisAidToNavigationOffPositionTimeseries;
    	    case "DeviceEnabledTimeseries":
    	        return DeviceEnabledTimeseries;
    	    case "RadarAutomaticSensitivityTimeControlTimeseries":
    	        return RadarAutomaticSensitivityTimeControlTimeseries;
    	    case "RadarBlankSector1Timeseries":
    	        return RadarBlankSector1Timeseries;
    	    case "RadarBlankSector2Timeseries":
    	        return RadarBlankSector2Timeseries;
    	    case "RadarEnableAutomaticFrequencyControlTimeseries":
    	        return RadarEnableAutomaticFrequencyControlTimeseries;
    	    case "RadarEnableFastTimeConstantTimeseries":
    	        return RadarEnableFastTimeConstantTimeseries;
    	    case "RadarEnableSensitivityTimeControlTimeseries":
    	        return RadarEnableSensitivityTimeControlTimeseries;
    	    case "RadarPowerOnTimeseries":
    	        return RadarPowerOnTimeseries;
    	    case "RadarSaveSettingsTimeseries":
    	        return RadarSaveSettingsTimeseries;
    	    case "RadarTrackingTimeseries":
    	        return RadarTrackingTimeseries;
    	    case "MediaProxySessionEnabledTimeseries":
    	        return MediaProxySessionEnabledTimeseries;
    	    case "MediaServiceEnabledTimeseries":
    	        return MediaServiceEnabledTimeseries;
    	    case "ByteTimeseries":
    	        return ByteTimeseries;
    	    case "DateTimeTimeseries":
    	        return DateTimeTimeseries;
    	    case "DoubleTimeseries":
    	        return DoubleTimeseries;
    	    case "GNSSAltitudeTimeseries":
    	        return GNSSAltitudeTimeseries;
    	    case "GNSSLatitudeTimeseries":
    	        return GNSSLatitudeTimeseries;
    	    case "GNSSLongitudeTimeseries":
    	        return GNSSLongitudeTimeseries;
    	    case "GyroCourseTimeseries":
    	        return GyroCourseTimeseries;
    	    case "GyroHeadingMagneticNorthTimeseries":
    	        return GyroHeadingMagneticNorthTimeseries;
    	    case "GyroHeadingTrueNorthTimeseries":
    	        return GyroHeadingTrueNorthTimeseries;
    	    case "GyroPitchTimeseries":
    	        return GyroPitchTimeseries;
    	    case "GyroRateOfTurnTimeseries":
    	        return GyroRateOfTurnTimeseries;
    	    case "GyroRollTimeseries":
    	        return GyroRollTimeseries;
    	    case "GyroSpeedTimeseries":
    	        return GyroSpeedTimeseries;
    	    case "RadarLatitudeTimeseries":
    	        return RadarLatitudeTimeseries;
    	    case "RadarLongitudeTimeseries":
    	        return RadarLongitudeTimeseries;
    	    case "RadomeDewPointTimeseries":
    	        return RadomeDewPointTimeseries;
    	    case "RadomePressureTimeseries":
    	        return RadomePressureTimeseries;
    	    case "RadomeTemperatureTimeseries":
    	        return RadomeTemperatureTimeseries;
    	    case "VesselDraughtTimeseries":
    	        return VesselDraughtTimeseries;
    	    case "ViewLatitudeTimeseries":
    	        return ViewLatitudeTimeseries;
    	    case "ViewLongitudeTimeseries":
    	        return ViewLongitudeTimeseries;
    	    case "ViewZoomLevelTimeseries":
    	        return ViewZoomLevelTimeseries;
    	    case "WeatherStationAbsoluteHumidityTimeseries":
    	        return WeatherStationAbsoluteHumidityTimeseries;
    	    case "WeatherStationAirTemperatureTimeseries":
    	        return WeatherStationAirTemperatureTimeseries;
    	    case "WeatherStationBarometricPressureTimeseries":
    	        return WeatherStationBarometricPressureTimeseries;
    	    case "WeatherStationDewPointTimeseries":
    	        return WeatherStationDewPointTimeseries;
    	    case "WeatherStationRelativeHumidityTimeseries":
    	        return WeatherStationRelativeHumidityTimeseries;
    	    case "WeatherStationWaterTemperatureTimeseries":
    	        return WeatherStationWaterTemperatureTimeseries;
    	    case "WeatherStationWindDirectionTimeseries":
    	        return WeatherStationWindDirectionTimeseries;
    	    case "WeatherStationWindSpeedTimeseries":
    	        return WeatherStationWindSpeedTimeseries;
    	    case "GeoPosition2DTimeseries":
    	        return GeoPosition2DTimeseries;
    	    case "AisAidToNavigationPositionTimeseries":
    	        return AisAidToNavigationPositionTimeseries;
    	    case "GeoPosition3DTimeseries":
    	        return GeoPosition3DTimeseries;
    	    case "GuidTimeseries":
    	        return GuidTimeseries;
    	    case "Int16Timeseries":
    	        return Int16Timeseries;
    	    case "Int32Timeseries":
    	        return Int32Timeseries;
    	    case "RadarAzimuthOffsetTimeseries":
    	        return RadarAzimuthOffsetTimeseries;
    	    case "RadarFastTimeConstantLevelTimeseries":
    	        return RadarFastTimeConstantLevelTimeseries;
    	    case "RadarFastTimeConstantModeTimeseries":
    	        return RadarFastTimeConstantModeTimeseries;
    	    case "RadarPulseTimeseries":
    	        return RadarPulseTimeseries;
    	    case "RadarSector1EndTimeseries":
    	        return RadarSector1EndTimeseries;
    	    case "RadarSector1StartTimeseries":
    	        return RadarSector1StartTimeseries;
    	    case "RadarSector2EndTimeseries":
    	        return RadarSector2EndTimeseries;
    	    case "RadarSector2StartTimeseries":
    	        return RadarSector2StartTimeseries;
    	    case "RadarSensitivityTimeControlLevelTimeseries":
    	        return RadarSensitivityTimeControlLevelTimeseries;
    	    case "RadarTuningTimeseries":
    	        return RadarTuningTimeseries;
    	    case "VesselPersonsOnBoardTimeseries":
    	        return VesselPersonsOnBoardTimeseries;
    	    case "Int64Timeseries":
    	        return Int64Timeseries;
    	    case "Position2DTimeseries":
    	        return Position2DTimeseries;
    	    case "Position3DTimeseries":
    	        return Position3DTimeseries;
    	    case "ReferenceTimeseries":
    	        return ReferenceTimeseries;
    	    case "SByteTimeseries":
    	        return SByteTimeseries;
    	    case "SingleTimeseries":
    	        return SingleTimeseries;
    	    case "StringTimeseries":
    	        return StringTimeseries;
    	    case "TimeSpanTimeseries":
    	        return TimeSpanTimeseries;
    	    case "UInt16Timeseries":
    	        return UInt16Timeseries;
    	    case "UInt32Timeseries":
    	        return UInt32Timeseries;
    	    case "RadomeStatusTimeseries":
    	        return RadomeStatusTimeseries;
    	    case "UInt64Timeseries":
    	        return UInt64Timeseries;
    	    case "TimeseriesCatalog":
    	        return TimeseriesCatalog;
    	    case "TimeseriesInfo":
    	        return TimeseriesInfo;
    	    case "TimeSpanTimeseriesValue":
    	        return TimeSpanTimeseriesValue;
    	    case "TrackableItemTrackLink":
    	        return TrackableItemTrackLink;
    	    case "TrackBase":
    	        return TrackBase;
    	    case "Track":
    	        return Track;
    	    case "Track3D":
    	        return Track3D;
    	    case "TrackerFilterParameters":
    	        return TrackerFilterParameters;
    	    case "TrackerFilterParametersConfiguration":
    	        return TrackerFilterParametersConfiguration;
    	    case "TrackInfo":
    	        return TrackInfo;
    	    case "TrackingServiceOptions":
    	        return TrackingServiceOptions;
    	    case "TrackLink":
    	        return TrackLink;
    	    case "TrackValue":
    	        return TrackValue;
    	    case "TrackValue3D":
    	        return TrackValue3D;
    	    case "UInt16TimeseriesValue":
    	        return UInt16TimeseriesValue;
    	    case "UInt32TimeseriesValue":
    	        return UInt32TimeseriesValue;
    	    case "UInt64TimeseriesValue":
    	        return UInt64TimeseriesValue;
    	    case "VehicleType":
    	        return VehicleType;
    	    case "VesselType":
    	        return VesselType;
    	    case "View":
    	        return View;
    	    case "ViewCameraLink":
    	        return ViewCameraLink;
    	    case "ViewTrackerLink":
    	        return ViewTrackerLink;
    	    case "WeatherStationCommand":
    	        return WeatherStationCommand;
    	    case "WeatherStationCommandReply":
    	        return WeatherStationCommandReply;
    	    case "WeatherStationConfiguration":
    	        return WeatherStationConfiguration;
    	    case "Zone":
    	        return Zone;
    	    case "CircularZone":
    	        return CircularZone;
    	    case "PolygonZone":
    	        return PolygonZone;
    	    case "ZoneExceptions":
    	        return ZoneExceptions;
    	    case "ZoneExceptionsVesselLink":
    	        return ZoneExceptionsVesselLink;
    	    case "ZoneTrackAlarm":
    	        return ZoneTrackAlarm;
    	    default:
    	        return Unknown;
    	}
    }

}

