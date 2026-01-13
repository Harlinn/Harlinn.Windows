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
package com.harlinn.barrelman.types;

import java.util.List;
import java.util.ArrayList;
import com.harlinn.common.io.BinaryReader;
import com.harlinn.common.io.BinaryWriter;
import com.harlinn.common.types.AbstractDataObject;

public class DataObjectFactory implements com.harlinn.common.types.DataObjectFactory {
    public AbstractDataObject create( int kind ) {
        switch( kind ) {
            case Kind.AircraftType:
                return new AircraftTypeObject( );
            case Kind.AisDeviceCommand:
                return new AisDeviceCommandObject( );
            case Kind.AisDeviceCommandReply:
                return new AisDeviceCommandReplyObject( );
            case Kind.AisDeviceConfiguration:
                return new AisDeviceConfigurationObject( );
            case Kind.AisDeviceRawMessage:
                return new AisDeviceRawMessageObject( );
            case Kind.AisDeviceRawSentence:
                return new AisDeviceRawSentenceObject( );
            case Kind.AidToNavigationReportMessage:
                return new AidToNavigationReportMessageObject( );
            case Kind.AisAddressedSafetyRelatedMessage:
                return new AisAddressedSafetyRelatedMessageObject( );
            case Kind.AisBaseStationReportMessage:
                return new AisBaseStationReportMessageObject( );
            case Kind.AisBinaryAcknowledgeMessage:
                return new AisBinaryAcknowledgeMessageObject( );
            case Kind.AisBinaryAddressedMessage:
                return new AisBinaryAddressedMessageObject( );
            case Kind.AisBinaryBroadcastMessage:
                return new AisBinaryBroadcastMessageObject( );
            case Kind.AisDataLinkManagementMessage:
                return new AisDataLinkManagementMessageObject( );
            case Kind.AisExtendedClassBCsPositionReportMessage:
                return new AisExtendedClassBCsPositionReportMessageObject( );
            case Kind.AisInterrogationMessage:
                return new AisInterrogationMessageObject( );
            case Kind.AisPositionReportClassAAssignedScheduleMessage:
                return new AisPositionReportClassAAssignedScheduleMessageObject( );
            case Kind.AisPositionReportClassAMessage:
                return new AisPositionReportClassAMessageObject( );
            case Kind.AisPositionReportClassAResponseToInterrogationMessage:
                return new AisPositionReportClassAResponseToInterrogationMessageObject( );
            case Kind.AisPositionReportForLongRangeApplicationsMessage:
                return new AisPositionReportForLongRangeApplicationsMessageObject( );
            case Kind.AisSafetyRelatedAcknowledgmentMessage:
                return new AisSafetyRelatedAcknowledgmentMessageObject( );
            case Kind.AisStandardClassBCsPositionReportMessage:
                return new AisStandardClassBCsPositionReportMessageObject( );
            case Kind.AisStandardSarAircraftPositionReportMessage:
                return new AisStandardSarAircraftPositionReportMessageObject( );
            case Kind.AisStaticAndVoyageRelatedDataMessage:
                return new AisStaticAndVoyageRelatedDataMessageObject( );
            case Kind.AisStaticDataReportMessage:
                return new AisStaticDataReportMessageObject( );
            case Kind.AisStaticDataReportPartAMessage:
                return new AisStaticDataReportPartAMessageObject( );
            case Kind.AisStaticDataReportPartBMessage:
                return new AisStaticDataReportPartBMessageObject( );
            case Kind.AisUtcAndDateInquiryMessage:
                return new AisUtcAndDateInquiryMessageObject( );
            case Kind.AisUtcAndDateResponseMessage:
                return new AisUtcAndDateResponseMessageObject( );
            case Kind.AlarmStateChange:
                return new AlarmStateChangeObject( );
            case Kind.BaseStationType:
                return new BaseStationTypeObject( );
            case Kind.BinaryTimeseriesValue:
                return new BinaryTimeseriesValueObject( );
            case Kind.Bookmark:
                return new BookmarkObject( );
            case Kind.BooleanTimeseriesValue:
                return new BooleanTimeseriesValueObject( );
            case Kind.ByteTimeseriesValue:
                return new ByteTimeseriesValueObject( );
            case Kind.CameraCommand:
                return new CameraCommandObject( );
            case Kind.CameraCommandAbsoluteMove:
                return new CameraCommandAbsoluteMoveObject( );
            case Kind.CameraCommandAdjustPanTiltZoom:
                return new CameraCommandAdjustPanTiltZoomObject( );
            case Kind.CameraCommandContinuousMove:
                return new CameraCommandContinuousMoveObject( );
            case Kind.CameraCommandGeoMove:
                return new CameraCommandGeoMoveObject( );
            case Kind.CameraCommandRelativeMove:
                return new CameraCommandRelativeMoveObject( );
            case Kind.CameraCommandReleasePTZOwnership:
                return new CameraCommandReleasePTZOwnershipObject( );
            case Kind.CameraCommandRequestPTZOwnership:
                return new CameraCommandRequestPTZOwnershipObject( );
            case Kind.CameraCommandSetAutoFocus:
                return new CameraCommandSetAutoFocusObject( );
            case Kind.CameraCommandSetBlackAndWhite:
                return new CameraCommandSetBlackAndWhiteObject( );
            case Kind.CameraCommandSetFollowed:
                return new CameraCommandSetFollowedObject( );
            case Kind.CameraCommandSetInfraRedLamp:
                return new CameraCommandSetInfraRedLampObject( );
            case Kind.CameraCommandSetWasher:
                return new CameraCommandSetWasherObject( );
            case Kind.CameraCommandSetWiper:
                return new CameraCommandSetWiperObject( );
            case Kind.CameraCommandStop:
                return new CameraCommandStopObject( );
            case Kind.CameraCommandReply:
                return new CameraCommandReplyObject( );
            case Kind.CameraConfiguration:
                return new CameraConfigurationObject( );
            case Kind.CameraPanCalibration:
                return new CameraPanCalibrationObject( );
            case Kind.CameraPanCalibrationValue:
                return new CameraPanCalibrationValueObject( );
            case Kind.CameraStatus:
                return new CameraStatusObject( );
            case Kind.CameraTiltCalibration:
                return new CameraTiltCalibrationObject( );
            case Kind.CameraTiltCalibrationValue:
                return new CameraTiltCalibrationValueObject( );
            case Kind.CameraZoomCalibration:
                return new CameraZoomCalibrationObject( );
            case Kind.CameraZoomCalibrationValue:
                return new CameraZoomCalibrationValueObject( );
            case Kind.Catalog:
                return new CatalogObject( );
            case Kind.Element:
                return new ElementObject( );
            case Kind.CollectionInfo:
                return new CollectionInfoObject( );
            case Kind.Country:
                return new CountryObject( );
            case Kind.CursorInfo:
                return new CursorInfoObject( );
            case Kind.DateTimeTimeseriesValue:
                return new DateTimeTimeseriesValueObject( );
            case Kind.DeviceHost:
                return new DeviceHostObject( );
            case Kind.DeviceHostConfiguration:
                return new DeviceHostConfigurationObject( );
            case Kind.DoubleTimeseriesValue:
                return new DoubleTimeseriesValueObject( );
            case Kind.FacilityType:
                return new FacilityTypeObject( );
            case Kind.GeoPosition2DTimeseriesValue:
                return new GeoPosition2DTimeseriesValueObject( );
            case Kind.GeoPosition3DTimeseriesValue:
                return new GeoPosition3DTimeseriesValueObject( );
            case Kind.GNSSDeviceCommand:
                return new GNSSDeviceCommandObject( );
            case Kind.GNSSDeviceCommandReply:
                return new GNSSDeviceCommandReplyObject( );
            case Kind.GNSSDeviceConfiguration:
                return new GNSSDeviceConfigurationObject( );
            case Kind.GuidTimeseriesValue:
                return new GuidTimeseriesValueObject( );
            case Kind.GyroDeviceCommand:
                return new GyroDeviceCommandObject( );
            case Kind.GyroDeviceCommandReply:
                return new GyroDeviceCommandReplyObject( );
            case Kind.GyroDeviceConfiguration:
                return new GyroDeviceConfigurationObject( );
            case Kind.Callsign:
                return new CallsignObject( );
            case Kind.InternationalMaritimeOrganizationNumber:
                return new InternationalMaritimeOrganizationNumberObject( );
            case Kind.MaritimeMobileServiceIdentity:
                return new MaritimeMobileServiceIdentityObject( );
            case Kind.Name:
                return new NameObject( );
            case Kind.Int16TimeseriesValue:
                return new Int16TimeseriesValueObject( );
            case Kind.Int32TimeseriesValue:
                return new Int32TimeseriesValueObject( );
            case Kind.Int64TimeseriesValue:
                return new Int64TimeseriesValueObject( );
            case Kind.BaseStation:
                return new BaseStationObject( );
            case Kind.CameraDevice:
                return new CameraDeviceObject( );
            case Kind.GNSSDevice:
                return new GNSSDeviceObject( );
            case Kind.GyroDevice:
                return new GyroDeviceObject( );
            case Kind.LineInputDevice:
                return new LineInputDeviceObject( );
            case Kind.OilSpillDetectorDevice:
                return new OilSpillDetectorDeviceObject( );
            case Kind.RadioDevice:
                return new RadioDeviceObject( );
            case Kind.RadomeDevice:
                return new RadomeDeviceObject( );
            case Kind.AisDevice:
                return new AisDeviceObject( );
            case Kind.RadarDevice:
                return new RadarDeviceObject( );
            case Kind.WeatherStationDevice:
                return new WeatherStationDeviceObject( );
            case Kind.Facility:
                return new FacilityObject( );
            case Kind.Aircraft:
                return new AircraftObject( );
            case Kind.AisAidToNavigation:
                return new AisAidToNavigationObject( );
            case Kind.Vehicle:
                return new VehicleObject( );
            case Kind.Vessel:
                return new VesselObject( );
            case Kind.ItemIdentityLink:
                return new ItemIdentityLinkObject( );
            case Kind.ItemParentChildLink:
                return new ItemParentChildLinkObject( );
            case Kind.LineInputDeviceCommand:
                return new LineInputDeviceCommandObject( );
            case Kind.LineInputDeviceCommandReply:
                return new LineInputDeviceCommandReplyObject( );
            case Kind.LineInputDeviceConfiguration:
                return new LineInputDeviceConfigurationObject( );
            case Kind.LineInputMessageRouting:
                return new LineInputMessageRoutingObject( );
            case Kind.LineInputMessageRoutingDestination:
                return new LineInputMessageRoutingDestinationObject( );
            case Kind.LineInputWhiteListEntry:
                return new LineInputWhiteListEntryObject( );
            case Kind.LogApplication:
                return new LogApplicationObject( );
            case Kind.LogApplicationConfiguration:
                return new LogApplicationConfigurationObject( );
            case Kind.LogHost:
                return new LogHostObject( );
            case Kind.LogHostConfiguration:
                return new LogHostConfigurationObject( );
            case Kind.LogLocation:
                return new LogLocationObject( );
            case Kind.LogProcess:
                return new LogProcessObject( );
            case Kind.LogRecord:
                return new LogRecordObject( );
            case Kind.LogThread:
                return new LogThreadObject( );
            case Kind.LogTraceEntry:
                return new LogTraceEntryObject( );
            case Kind.MapElement:
                return new MapElementObject( );
            case Kind.MapInfo:
                return new MapInfoObject( );
            case Kind.MapServiceOptions:
                return new MapServiceOptionsObject( );
            case Kind.MaritimeIdentificationDigits:
                return new MaritimeIdentificationDigitsObject( );
            case Kind.MediaProxySession:
                return new MediaProxySessionObject( );
            case Kind.MediaProxySessionFile:
                return new MediaProxySessionFileObject( );
            case Kind.MediaProxySessionOptions:
                return new MediaProxySessionOptionsObject( );
            case Kind.MediaService:
                return new MediaServiceObject( );
            case Kind.MediaServiceOptions:
                return new MediaServiceOptionsObject( );
            case Kind.ElementType:
                return new ElementTypeObject( );
            case Kind.Namespace:
                return new NamespaceObject( );
            case Kind.OilSpill:
                return new OilSpillObject( );
            case Kind.OilSpillDetectorCommand:
                return new OilSpillDetectorCommandObject( );
            case Kind.OilSpillDetectorCommandReply:
                return new OilSpillDetectorCommandReplyObject( );
            case Kind.OilSpillDetectorConfiguration:
                return new OilSpillDetectorConfigurationObject( );
            case Kind.Position2DTimeseriesValue:
                return new Position2DTimeseriesValueObject( );
            case Kind.Position3DTimeseriesValue:
                return new Position3DTimeseriesValueObject( );
            case Kind.ProcessTrackValueResult:
                return new ProcessTrackValueResultObject( );
            case Kind.BinaryProperty:
                return new BinaryPropertyObject( );
            case Kind.BooleanProperty:
                return new BooleanPropertyObject( );
            case Kind.ByteProperty:
                return new BytePropertyObject( );
            case Kind.DateTimeProperty:
                return new DateTimePropertyObject( );
            case Kind.DoubleProperty:
                return new DoublePropertyObject( );
            case Kind.GuidProperty:
                return new GuidPropertyObject( );
            case Kind.Int16Property:
                return new Int16PropertyObject( );
            case Kind.Int32Property:
                return new Int32PropertyObject( );
            case Kind.Int64Property:
                return new Int64PropertyObject( );
            case Kind.ReferenceProperty:
                return new ReferencePropertyObject( );
            case Kind.SByteProperty:
                return new SBytePropertyObject( );
            case Kind.SingleProperty:
                return new SinglePropertyObject( );
            case Kind.StringProperty:
                return new StringPropertyObject( );
            case Kind.BinaryTimeseriesProperty:
                return new BinaryTimeseriesPropertyObject( );
            case Kind.BooleanTimeseriesProperty:
                return new BooleanTimeseriesPropertyObject( );
            case Kind.ByteTimeseriesProperty:
                return new ByteTimeseriesPropertyObject( );
            case Kind.DateTimeTimeseriesProperty:
                return new DateTimeTimeseriesPropertyObject( );
            case Kind.DoubleTimeseriesProperty:
                return new DoubleTimeseriesPropertyObject( );
            case Kind.GuidTimeseriesProperty:
                return new GuidTimeseriesPropertyObject( );
            case Kind.Int16TimeseriesProperty:
                return new Int16TimeseriesPropertyObject( );
            case Kind.Int32TimeseriesProperty:
                return new Int32TimeseriesPropertyObject( );
            case Kind.Int64TimeseriesProperty:
                return new Int64TimeseriesPropertyObject( );
            case Kind.ReferenceTimeseriesProperty:
                return new ReferenceTimeseriesPropertyObject( );
            case Kind.SByteTimeseriesProperty:
                return new SByteTimeseriesPropertyObject( );
            case Kind.SingleTimeseriesProperty:
                return new SingleTimeseriesPropertyObject( );
            case Kind.StringTimeseriesProperty:
                return new StringTimeseriesPropertyObject( );
            case Kind.TimeSpanTimeseriesProperty:
                return new TimeSpanTimeseriesPropertyObject( );
            case Kind.UInt16TimeseriesProperty:
                return new UInt16TimeseriesPropertyObject( );
            case Kind.UInt32TimeseriesProperty:
                return new UInt32TimeseriesPropertyObject( );
            case Kind.UInt64TimeseriesProperty:
                return new UInt64TimeseriesPropertyObject( );
            case Kind.TimeSpanProperty:
                return new TimeSpanPropertyObject( );
            case Kind.UInt16Property:
                return new UInt16PropertyObject( );
            case Kind.UInt32Property:
                return new UInt32PropertyObject( );
            case Kind.UInt64Property:
                return new UInt64PropertyObject( );
            case Kind.BinaryPropertyDefinition:
                return new BinaryPropertyDefinitionObject( );
            case Kind.BooleanPropertyDefinition:
                return new BooleanPropertyDefinitionObject( );
            case Kind.BytePropertyDefinition:
                return new BytePropertyDefinitionObject( );
            case Kind.DateTimePropertyDefinition:
                return new DateTimePropertyDefinitionObject( );
            case Kind.DoublePropertyDefinition:
                return new DoublePropertyDefinitionObject( );
            case Kind.GuidPropertyDefinition:
                return new GuidPropertyDefinitionObject( );
            case Kind.Int16PropertyDefinition:
                return new Int16PropertyDefinitionObject( );
            case Kind.Int32PropertyDefinition:
                return new Int32PropertyDefinitionObject( );
            case Kind.Int64PropertyDefinition:
                return new Int64PropertyDefinitionObject( );
            case Kind.ReferencePropertyDefinition:
                return new ReferencePropertyDefinitionObject( );
            case Kind.SBytePropertyDefinition:
                return new SBytePropertyDefinitionObject( );
            case Kind.SinglePropertyDefinition:
                return new SinglePropertyDefinitionObject( );
            case Kind.StringPropertyDefinition:
                return new StringPropertyDefinitionObject( );
            case Kind.BinaryTimeseriesPropertyDefinition:
                return new BinaryTimeseriesPropertyDefinitionObject( );
            case Kind.BooleanTimeseriesPropertyDefinition:
                return new BooleanTimeseriesPropertyDefinitionObject( );
            case Kind.ByteTimeseriesPropertyDefinition:
                return new ByteTimeseriesPropertyDefinitionObject( );
            case Kind.DateTimeTimeseriesPropertyDefinition:
                return new DateTimeTimeseriesPropertyDefinitionObject( );
            case Kind.DoubleTimeseriesPropertyDefinition:
                return new DoubleTimeseriesPropertyDefinitionObject( );
            case Kind.GuidTimeseriesPropertyDefinition:
                return new GuidTimeseriesPropertyDefinitionObject( );
            case Kind.Int16TimeseriesPropertyDefinition:
                return new Int16TimeseriesPropertyDefinitionObject( );
            case Kind.Int32TimeseriesPropertyDefinition:
                return new Int32TimeseriesPropertyDefinitionObject( );
            case Kind.Int64TimeseriesPropertyDefinition:
                return new Int64TimeseriesPropertyDefinitionObject( );
            case Kind.ReferenceTimeseriesPropertyDefinition:
                return new ReferenceTimeseriesPropertyDefinitionObject( );
            case Kind.SByteTimeseriesPropertyDefinition:
                return new SByteTimeseriesPropertyDefinitionObject( );
            case Kind.SingleTimeseriesPropertyDefinition:
                return new SingleTimeseriesPropertyDefinitionObject( );
            case Kind.StringTimeseriesPropertyDefinition:
                return new StringTimeseriesPropertyDefinitionObject( );
            case Kind.TimeSpanTimeseriesPropertyDefinition:
                return new TimeSpanTimeseriesPropertyDefinitionObject( );
            case Kind.UInt16TimeseriesPropertyDefinition:
                return new UInt16TimeseriesPropertyDefinitionObject( );
            case Kind.UInt32TimeseriesPropertyDefinition:
                return new UInt32TimeseriesPropertyDefinitionObject( );
            case Kind.UInt64TimeseriesPropertyDefinition:
                return new UInt64TimeseriesPropertyDefinitionObject( );
            case Kind.TimeSpanPropertyDefinition:
                return new TimeSpanPropertyDefinitionObject( );
            case Kind.UInt16PropertyDefinition:
                return new UInt16PropertyDefinitionObject( );
            case Kind.UInt32PropertyDefinition:
                return new UInt32PropertyDefinitionObject( );
            case Kind.UInt64PropertyDefinition:
                return new UInt64PropertyDefinitionObject( );
            case Kind.RadarAlarmStatus:
                return new RadarAlarmStatusObject( );
            case Kind.RadarCommand:
                return new RadarCommandObject( );
            case Kind.RadarCommandGetStatus:
                return new RadarCommandGetStatusObject( );
            case Kind.RadarCommandReply:
                return new RadarCommandReplyObject( );
            case Kind.RadarCommandReplyGetStatus:
                return new RadarCommandReplyGetStatusObject( );
            case Kind.RadarConfiguration:
                return new RadarConfigurationObject( );
            case Kind.RadarImage:
                return new RadarImageObject( );
            case Kind.RadarRawTrackTable:
                return new RadarRawTrackTableObject( );
            case Kind.RadarStatus:
                return new RadarStatusObject( );
            case Kind.RadioCommand:
                return new RadioCommandObject( );
            case Kind.RadioCommandReply:
                return new RadioCommandReplyObject( );
            case Kind.RadioConfiguration:
                return new RadioConfigurationObject( );
            case Kind.RadomeCommand:
                return new RadomeCommandObject( );
            case Kind.RadomeCommandReply:
                return new RadomeCommandReplyObject( );
            case Kind.RadomeConfiguration:
                return new RadomeConfigurationObject( );
            case Kind.ReferenceTimeseriesValue:
                return new ReferenceTimeseriesValueObject( );
            case Kind.SByteTimeseriesValue:
                return new SByteTimeseriesValueObject( );
            case Kind.SecurityDomain:
                return new SecurityDomainObject( );
            case Kind.SecurityLogin:
                return new SecurityLoginObject( );
            case Kind.SecurityRole:
                return new SecurityRoleObject( );
            case Kind.SecurityIdentifierRoleLink:
                return new SecurityIdentifierRoleLinkObject( );
            case Kind.SecurityLoginSession:
                return new SecurityLoginSessionObject( );
            case Kind.SecurityPermission:
                return new SecurityPermissionObject( );
            case Kind.SingleTimeseriesValue:
                return new SingleTimeseriesValueObject( );
            case Kind.StringTimeseriesValue:
                return new StringTimeseriesValueObject( );
            case Kind.BinaryTimeseries:
                return new BinaryTimeseriesObject( );
            case Kind.BooleanTimeseries:
                return new BooleanTimeseriesObject( );
            case Kind.AisAidToNavigationOffPositionTimeseries:
                return new AisAidToNavigationOffPositionTimeseriesObject( );
            case Kind.DeviceEnabledTimeseries:
                return new DeviceEnabledTimeseriesObject( );
            case Kind.RadarAutomaticSensitivityTimeControlTimeseries:
                return new RadarAutomaticSensitivityTimeControlTimeseriesObject( );
            case Kind.RadarBlankSector1Timeseries:
                return new RadarBlankSector1TimeseriesObject( );
            case Kind.RadarBlankSector2Timeseries:
                return new RadarBlankSector2TimeseriesObject( );
            case Kind.RadarEnableAutomaticFrequencyControlTimeseries:
                return new RadarEnableAutomaticFrequencyControlTimeseriesObject( );
            case Kind.RadarEnableFastTimeConstantTimeseries:
                return new RadarEnableFastTimeConstantTimeseriesObject( );
            case Kind.RadarEnableSensitivityTimeControlTimeseries:
                return new RadarEnableSensitivityTimeControlTimeseriesObject( );
            case Kind.RadarPowerOnTimeseries:
                return new RadarPowerOnTimeseriesObject( );
            case Kind.RadarSaveSettingsTimeseries:
                return new RadarSaveSettingsTimeseriesObject( );
            case Kind.RadarTrackingTimeseries:
                return new RadarTrackingTimeseriesObject( );
            case Kind.MediaProxySessionEnabledTimeseries:
                return new MediaProxySessionEnabledTimeseriesObject( );
            case Kind.MediaServiceEnabledTimeseries:
                return new MediaServiceEnabledTimeseriesObject( );
            case Kind.ByteTimeseries:
                return new ByteTimeseriesObject( );
            case Kind.DateTimeTimeseries:
                return new DateTimeTimeseriesObject( );
            case Kind.DoubleTimeseries:
                return new DoubleTimeseriesObject( );
            case Kind.GNSSAltitudeTimeseries:
                return new GNSSAltitudeTimeseriesObject( );
            case Kind.GNSSLatitudeTimeseries:
                return new GNSSLatitudeTimeseriesObject( );
            case Kind.GNSSLongitudeTimeseries:
                return new GNSSLongitudeTimeseriesObject( );
            case Kind.GyroCourseTimeseries:
                return new GyroCourseTimeseriesObject( );
            case Kind.GyroHeadingMagneticNorthTimeseries:
                return new GyroHeadingMagneticNorthTimeseriesObject( );
            case Kind.GyroHeadingTrueNorthTimeseries:
                return new GyroHeadingTrueNorthTimeseriesObject( );
            case Kind.GyroPitchTimeseries:
                return new GyroPitchTimeseriesObject( );
            case Kind.GyroRateOfTurnTimeseries:
                return new GyroRateOfTurnTimeseriesObject( );
            case Kind.GyroRollTimeseries:
                return new GyroRollTimeseriesObject( );
            case Kind.GyroSpeedTimeseries:
                return new GyroSpeedTimeseriesObject( );
            case Kind.RadarLatitudeTimeseries:
                return new RadarLatitudeTimeseriesObject( );
            case Kind.RadarLongitudeTimeseries:
                return new RadarLongitudeTimeseriesObject( );
            case Kind.RadomeDewPointTimeseries:
                return new RadomeDewPointTimeseriesObject( );
            case Kind.RadomePressureTimeseries:
                return new RadomePressureTimeseriesObject( );
            case Kind.RadomeTemperatureTimeseries:
                return new RadomeTemperatureTimeseriesObject( );
            case Kind.VesselDraughtTimeseries:
                return new VesselDraughtTimeseriesObject( );
            case Kind.ViewLatitudeTimeseries:
                return new ViewLatitudeTimeseriesObject( );
            case Kind.ViewLongitudeTimeseries:
                return new ViewLongitudeTimeseriesObject( );
            case Kind.ViewZoomLevelTimeseries:
                return new ViewZoomLevelTimeseriesObject( );
            case Kind.WeatherStationAbsoluteHumidityTimeseries:
                return new WeatherStationAbsoluteHumidityTimeseriesObject( );
            case Kind.WeatherStationAirTemperatureTimeseries:
                return new WeatherStationAirTemperatureTimeseriesObject( );
            case Kind.WeatherStationBarometricPressureTimeseries:
                return new WeatherStationBarometricPressureTimeseriesObject( );
            case Kind.WeatherStationDewPointTimeseries:
                return new WeatherStationDewPointTimeseriesObject( );
            case Kind.WeatherStationRelativeHumidityTimeseries:
                return new WeatherStationRelativeHumidityTimeseriesObject( );
            case Kind.WeatherStationWaterTemperatureTimeseries:
                return new WeatherStationWaterTemperatureTimeseriesObject( );
            case Kind.WeatherStationWindDirectionTimeseries:
                return new WeatherStationWindDirectionTimeseriesObject( );
            case Kind.WeatherStationWindSpeedTimeseries:
                return new WeatherStationWindSpeedTimeseriesObject( );
            case Kind.GeoPosition2DTimeseries:
                return new GeoPosition2DTimeseriesObject( );
            case Kind.AisAidToNavigationPositionTimeseries:
                return new AisAidToNavigationPositionTimeseriesObject( );
            case Kind.GeoPosition3DTimeseries:
                return new GeoPosition3DTimeseriesObject( );
            case Kind.GuidTimeseries:
                return new GuidTimeseriesObject( );
            case Kind.Int16Timeseries:
                return new Int16TimeseriesObject( );
            case Kind.Int32Timeseries:
                return new Int32TimeseriesObject( );
            case Kind.RadarAzimuthOffsetTimeseries:
                return new RadarAzimuthOffsetTimeseriesObject( );
            case Kind.RadarFastTimeConstantLevelTimeseries:
                return new RadarFastTimeConstantLevelTimeseriesObject( );
            case Kind.RadarFastTimeConstantModeTimeseries:
                return new RadarFastTimeConstantModeTimeseriesObject( );
            case Kind.RadarPulseTimeseries:
                return new RadarPulseTimeseriesObject( );
            case Kind.RadarSector1EndTimeseries:
                return new RadarSector1EndTimeseriesObject( );
            case Kind.RadarSector1StartTimeseries:
                return new RadarSector1StartTimeseriesObject( );
            case Kind.RadarSector2EndTimeseries:
                return new RadarSector2EndTimeseriesObject( );
            case Kind.RadarSector2StartTimeseries:
                return new RadarSector2StartTimeseriesObject( );
            case Kind.RadarSensitivityTimeControlLevelTimeseries:
                return new RadarSensitivityTimeControlLevelTimeseriesObject( );
            case Kind.RadarTuningTimeseries:
                return new RadarTuningTimeseriesObject( );
            case Kind.VesselPersonsOnBoardTimeseries:
                return new VesselPersonsOnBoardTimeseriesObject( );
            case Kind.Int64Timeseries:
                return new Int64TimeseriesObject( );
            case Kind.Position2DTimeseries:
                return new Position2DTimeseriesObject( );
            case Kind.Position3DTimeseries:
                return new Position3DTimeseriesObject( );
            case Kind.ReferenceTimeseries:
                return new ReferenceTimeseriesObject( );
            case Kind.SByteTimeseries:
                return new SByteTimeseriesObject( );
            case Kind.SingleTimeseries:
                return new SingleTimeseriesObject( );
            case Kind.StringTimeseries:
                return new StringTimeseriesObject( );
            case Kind.TimeSpanTimeseries:
                return new TimeSpanTimeseriesObject( );
            case Kind.UInt16Timeseries:
                return new UInt16TimeseriesObject( );
            case Kind.UInt32Timeseries:
                return new UInt32TimeseriesObject( );
            case Kind.RadomeStatusTimeseries:
                return new RadomeStatusTimeseriesObject( );
            case Kind.UInt64Timeseries:
                return new UInt64TimeseriesObject( );
            case Kind.TimeseriesCatalog:
                return new TimeseriesCatalogObject( );
            case Kind.TimeseriesInfo:
                return new TimeseriesInfoObject( );
            case Kind.TimeSpanTimeseriesValue:
                return new TimeSpanTimeseriesValueObject( );
            case Kind.TrackableItemTrackLink:
                return new TrackableItemTrackLinkObject( );
            case Kind.Track:
                return new TrackObject( );
            case Kind.Track3D:
                return new Track3DObject( );
            case Kind.TrackerFilterParameters:
                return new TrackerFilterParametersObject( );
            case Kind.TrackerFilterParametersConfiguration:
                return new TrackerFilterParametersConfigurationObject( );
            case Kind.TrackInfo:
                return new TrackInfoObject( );
            case Kind.TrackingServiceOptions:
                return new TrackingServiceOptionsObject( );
            case Kind.TrackLink:
                return new TrackLinkObject( );
            case Kind.TrackValue:
                return new TrackValueObject( );
            case Kind.TrackValue3D:
                return new TrackValue3DObject( );
            case Kind.UInt16TimeseriesValue:
                return new UInt16TimeseriesValueObject( );
            case Kind.UInt32TimeseriesValue:
                return new UInt32TimeseriesValueObject( );
            case Kind.UInt64TimeseriesValue:
                return new UInt64TimeseriesValueObject( );
            case Kind.VehicleType:
                return new VehicleTypeObject( );
            case Kind.VesselType:
                return new VesselTypeObject( );
            case Kind.View:
                return new ViewObject( );
            case Kind.ViewCameraLink:
                return new ViewCameraLinkObject( );
            case Kind.ViewTrackerLink:
                return new ViewTrackerLinkObject( );
            case Kind.WeatherStationCommand:
                return new WeatherStationCommandObject( );
            case Kind.WeatherStationCommandReply:
                return new WeatherStationCommandReplyObject( );
            case Kind.WeatherStationConfiguration:
                return new WeatherStationConfigurationObject( );
            case Kind.CircularZone:
                return new CircularZoneObject( );
            case Kind.PolygonZone:
                return new PolygonZoneObject( );
            case Kind.ZoneExceptions:
                return new ZoneExceptionsObject( );
            case Kind.ZoneExceptionsVesselLink:
                return new ZoneExceptionsVesselLinkObject( );
            case Kind.ZoneTrackAlarm:
                return new ZoneTrackAlarmObject( );
            default:
                throw new IllegalArgumentException( "Cannot create an object for kind:" + kind );
        }
    }
    public AbstractDataObject readFrom(BinaryReader source) {
        var kind = source.readInt32( );
        var result = create( kind );
        result.readFrom( source );
        return result;
    }
    public List<AbstractDataObject> readStreamFrom(BinaryReader source) {
        var result = new ArrayList<AbstractDataObject>( );
        while( source.readBoolean( ) ) {
            var dataObject = readFrom( source );
            result.add( dataObject );
        }
        return result;
    }
    public List<AbstractDataObject> readListFrom(BinaryReader source) {
        var count = source.readInt32( );
        var result = new ArrayList<AbstractDataObject>( count );
        for( int i = 0; i < count; i++ ) {
            var dataObject = readFrom( source );
            result.add( dataObject );
        }
        return result;
    }
}

