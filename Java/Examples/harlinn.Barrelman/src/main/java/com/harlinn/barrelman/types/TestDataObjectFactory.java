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

import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TestDataObjectFactory {

    public final static Guid AircraftTypePrimaryKey = new Guid(Kind.AircraftType,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisDeviceCommandPrimaryKey = new Guid(Kind.AisDeviceCommand,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisDeviceCommandReplyPrimaryKey = new Guid(Kind.AisDeviceCommandReply,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisDeviceConfigurationPrimaryKey = new Guid(Kind.AisDeviceConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisDeviceRawMessagePrimaryKey = new Guid(Kind.AisDeviceRawMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisDeviceRawSentencePrimaryKey = new Guid(Kind.AisDeviceRawSentence,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AidToNavigationReportMessagePrimaryKey = new Guid(Kind.AidToNavigationReportMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisAddressedSafetyRelatedMessagePrimaryKey = new Guid(Kind.AisAddressedSafetyRelatedMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisBaseStationReportMessagePrimaryKey = new Guid(Kind.AisBaseStationReportMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisBinaryAcknowledgeMessagePrimaryKey = new Guid(Kind.AisBinaryAcknowledgeMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisBinaryAddressedMessagePrimaryKey = new Guid(Kind.AisBinaryAddressedMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisBinaryBroadcastMessagePrimaryKey = new Guid(Kind.AisBinaryBroadcastMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisDataLinkManagementMessagePrimaryKey = new Guid(Kind.AisDataLinkManagementMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisExtendedClassBCsPositionReportMessagePrimaryKey = new Guid(Kind.AisExtendedClassBCsPositionReportMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisInterrogationMessagePrimaryKey = new Guid(Kind.AisInterrogationMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisPositionReportClassAAssignedScheduleMessagePrimaryKey = new Guid(Kind.AisPositionReportClassAAssignedScheduleMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisPositionReportClassAMessagePrimaryKey = new Guid(Kind.AisPositionReportClassAMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisPositionReportClassAResponseToInterrogationMessagePrimaryKey = new Guid(Kind.AisPositionReportClassAResponseToInterrogationMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisPositionReportForLongRangeApplicationsMessagePrimaryKey = new Guid(Kind.AisPositionReportForLongRangeApplicationsMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisSafetyRelatedAcknowledgmentMessagePrimaryKey = new Guid(Kind.AisSafetyRelatedAcknowledgmentMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisStandardClassBCsPositionReportMessagePrimaryKey = new Guid(Kind.AisStandardClassBCsPositionReportMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisStandardSarAircraftPositionReportMessagePrimaryKey = new Guid(Kind.AisStandardSarAircraftPositionReportMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisStaticAndVoyageRelatedDataMessagePrimaryKey = new Guid(Kind.AisStaticAndVoyageRelatedDataMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisStaticDataReportMessagePrimaryKey = new Guid(Kind.AisStaticDataReportMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisStaticDataReportPartAMessagePrimaryKey = new Guid(Kind.AisStaticDataReportPartAMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisStaticDataReportPartBMessagePrimaryKey = new Guid(Kind.AisStaticDataReportPartBMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisUtcAndDateInquiryMessagePrimaryKey = new Guid(Kind.AisUtcAndDateInquiryMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisUtcAndDateResponseMessagePrimaryKey = new Guid(Kind.AisUtcAndDateResponseMessage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AlarmStateChangePrimaryKey = new Guid(Kind.AlarmStateChange,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BaseStationTypePrimaryKey = new Guid(Kind.BaseStationType,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BinaryTimeseriesValuePrimaryKey = new Guid(Kind.BinaryTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BookmarkPrimaryKey = new Guid(Kind.Bookmark,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BooleanTimeseriesValuePrimaryKey = new Guid(Kind.BooleanTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ByteTimeseriesValuePrimaryKey = new Guid(Kind.ByteTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandPrimaryKey = new Guid(Kind.CameraCommand,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandAbsoluteMovePrimaryKey = new Guid(Kind.CameraCommandAbsoluteMove,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandAdjustPanTiltZoomPrimaryKey = new Guid(Kind.CameraCommandAdjustPanTiltZoom,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandContinuousMovePrimaryKey = new Guid(Kind.CameraCommandContinuousMove,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandGeoMovePrimaryKey = new Guid(Kind.CameraCommandGeoMove,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandRelativeMovePrimaryKey = new Guid(Kind.CameraCommandRelativeMove,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandReleasePTZOwnershipPrimaryKey = new Guid(Kind.CameraCommandReleasePTZOwnership,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandRequestPTZOwnershipPrimaryKey = new Guid(Kind.CameraCommandRequestPTZOwnership,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandSetAutoFocusPrimaryKey = new Guid(Kind.CameraCommandSetAutoFocus,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandSetBlackAndWhitePrimaryKey = new Guid(Kind.CameraCommandSetBlackAndWhite,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandSetFollowedPrimaryKey = new Guid(Kind.CameraCommandSetFollowed,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandSetInfraRedLampPrimaryKey = new Guid(Kind.CameraCommandSetInfraRedLamp,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandSetWasherPrimaryKey = new Guid(Kind.CameraCommandSetWasher,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandSetWiperPrimaryKey = new Guid(Kind.CameraCommandSetWiper,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandStopPrimaryKey = new Guid(Kind.CameraCommandStop,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraCommandReplyPrimaryKey = new Guid(Kind.CameraCommandReply,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraConfigurationPrimaryKey = new Guid(Kind.CameraConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraPanCalibrationPrimaryKey = new Guid(Kind.CameraPanCalibration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraPanCalibrationValuePrimaryKey = new Guid(Kind.CameraPanCalibrationValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraStatusPrimaryKey = new Guid(Kind.CameraStatus,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraTiltCalibrationPrimaryKey = new Guid(Kind.CameraTiltCalibration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraTiltCalibrationValuePrimaryKey = new Guid(Kind.CameraTiltCalibrationValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraZoomCalibrationPrimaryKey = new Guid(Kind.CameraZoomCalibration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraZoomCalibrationValuePrimaryKey = new Guid(Kind.CameraZoomCalibrationValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CatalogPrimaryKey = new Guid(Kind.Catalog,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ElementPrimaryKey = new Guid(Kind.Element,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CollectionInfoPrimaryKey = new Guid(Kind.CollectionInfo,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CountryPrimaryKey = new Guid(Kind.Country,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CursorInfoPrimaryKey = new Guid(Kind.CursorInfo,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DateTimeTimeseriesValuePrimaryKey = new Guid(Kind.DateTimeTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DeviceHostPrimaryKey = new Guid(Kind.DeviceHost,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DeviceHostConfigurationPrimaryKey = new Guid(Kind.DeviceHostConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DoubleTimeseriesValuePrimaryKey = new Guid(Kind.DoubleTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid FacilityTypePrimaryKey = new Guid(Kind.FacilityType,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GeoPosition2DTimeseriesValuePrimaryKey = new Guid(Kind.GeoPosition2DTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GeoPosition3DTimeseriesValuePrimaryKey = new Guid(Kind.GeoPosition3DTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GNSSDeviceCommandPrimaryKey = new Guid(Kind.GNSSDeviceCommand,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GNSSDeviceCommandReplyPrimaryKey = new Guid(Kind.GNSSDeviceCommandReply,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GNSSDeviceConfigurationPrimaryKey = new Guid(Kind.GNSSDeviceConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GuidTimeseriesValuePrimaryKey = new Guid(Kind.GuidTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroDeviceCommandPrimaryKey = new Guid(Kind.GyroDeviceCommand,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroDeviceCommandReplyPrimaryKey = new Guid(Kind.GyroDeviceCommandReply,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroDeviceConfigurationPrimaryKey = new Guid(Kind.GyroDeviceConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CallsignPrimaryKey = new Guid(Kind.Callsign,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid InternationalMaritimeOrganizationNumberPrimaryKey = new Guid(Kind.InternationalMaritimeOrganizationNumber,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MaritimeMobileServiceIdentityPrimaryKey = new Guid(Kind.MaritimeMobileServiceIdentity,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid NamePrimaryKey = new Guid(Kind.Name,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int16TimeseriesValuePrimaryKey = new Guid(Kind.Int16TimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int32TimeseriesValuePrimaryKey = new Guid(Kind.Int32TimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int64TimeseriesValuePrimaryKey = new Guid(Kind.Int64TimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BaseStationPrimaryKey = new Guid(Kind.BaseStation,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CameraDevicePrimaryKey = new Guid(Kind.CameraDevice,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GNSSDevicePrimaryKey = new Guid(Kind.GNSSDevice,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroDevicePrimaryKey = new Guid(Kind.GyroDevice,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LineInputDevicePrimaryKey = new Guid(Kind.LineInputDevice,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid OilSpillDetectorDevicePrimaryKey = new Guid(Kind.OilSpillDetectorDevice,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadioDevicePrimaryKey = new Guid(Kind.RadioDevice,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadomeDevicePrimaryKey = new Guid(Kind.RadomeDevice,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisDevicePrimaryKey = new Guid(Kind.AisDevice,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarDevicePrimaryKey = new Guid(Kind.RadarDevice,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationDevicePrimaryKey = new Guid(Kind.WeatherStationDevice,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid FacilityPrimaryKey = new Guid(Kind.Facility,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AircraftPrimaryKey = new Guid(Kind.Aircraft,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisAidToNavigationPrimaryKey = new Guid(Kind.AisAidToNavigation,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid VehiclePrimaryKey = new Guid(Kind.Vehicle,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid VesselPrimaryKey = new Guid(Kind.Vessel,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ItemIdentityLinkPrimaryKey = new Guid(Kind.ItemIdentityLink,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ItemParentChildLinkPrimaryKey = new Guid(Kind.ItemParentChildLink,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LineInputDeviceCommandPrimaryKey = new Guid(Kind.LineInputDeviceCommand,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LineInputDeviceCommandReplyPrimaryKey = new Guid(Kind.LineInputDeviceCommandReply,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LineInputDeviceConfigurationPrimaryKey = new Guid(Kind.LineInputDeviceConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LineInputMessageRoutingPrimaryKey = new Guid(Kind.LineInputMessageRouting,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LineInputMessageRoutingDestinationPrimaryKey = new Guid(Kind.LineInputMessageRoutingDestination,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LineInputWhiteListEntryPrimaryKey = new Guid(Kind.LineInputWhiteListEntry,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LogApplicationPrimaryKey = new Guid(Kind.LogApplication,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LogApplicationConfigurationPrimaryKey = new Guid(Kind.LogApplicationConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LogHostPrimaryKey = new Guid(Kind.LogHost,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LogHostConfigurationPrimaryKey = new Guid(Kind.LogHostConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LogLocationPrimaryKey = new Guid(Kind.LogLocation,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LogProcessPrimaryKey = new Guid(Kind.LogProcess,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LogRecordPrimaryKey = new Guid(Kind.LogRecord,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LogThreadPrimaryKey = new Guid(Kind.LogThread,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid LogTraceEntryPrimaryKey = new Guid(Kind.LogTraceEntry,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MapElementPrimaryKey = new Guid(Kind.MapElement,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MapInfoPrimaryKey = new Guid(Kind.MapInfo,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MapServiceOptionsPrimaryKey = new Guid(Kind.MapServiceOptions,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MaritimeIdentificationDigitsPrimaryKey = new Guid(Kind.MaritimeIdentificationDigits,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MediaProxySessionPrimaryKey = new Guid(Kind.MediaProxySession,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MediaProxySessionFilePrimaryKey = new Guid(Kind.MediaProxySessionFile,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MediaProxySessionOptionsPrimaryKey = new Guid(Kind.MediaProxySessionOptions,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MediaServicePrimaryKey = new Guid(Kind.MediaService,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MediaServiceOptionsPrimaryKey = new Guid(Kind.MediaServiceOptions,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ElementTypePrimaryKey = new Guid(Kind.ElementType,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid NamespacePrimaryKey = new Guid(Kind.Namespace,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid OilSpillPrimaryKey = new Guid(Kind.OilSpill,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid OilSpillDetectorCommandPrimaryKey = new Guid(Kind.OilSpillDetectorCommand,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid OilSpillDetectorCommandReplyPrimaryKey = new Guid(Kind.OilSpillDetectorCommandReply,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid OilSpillDetectorConfigurationPrimaryKey = new Guid(Kind.OilSpillDetectorConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Position2DTimeseriesValuePrimaryKey = new Guid(Kind.Position2DTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Position3DTimeseriesValuePrimaryKey = new Guid(Kind.Position3DTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ProcessTrackValueResultPrimaryKey = new Guid(Kind.ProcessTrackValueResult,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BinaryPropertyPrimaryKey = new Guid(Kind.BinaryProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BooleanPropertyPrimaryKey = new Guid(Kind.BooleanProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BytePropertyPrimaryKey = new Guid(Kind.ByteProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DateTimePropertyPrimaryKey = new Guid(Kind.DateTimeProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DoublePropertyPrimaryKey = new Guid(Kind.DoubleProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GuidPropertyPrimaryKey = new Guid(Kind.GuidProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int16PropertyPrimaryKey = new Guid(Kind.Int16Property,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int32PropertyPrimaryKey = new Guid(Kind.Int32Property,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int64PropertyPrimaryKey = new Guid(Kind.Int64Property,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ReferencePropertyPrimaryKey = new Guid(Kind.ReferenceProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SBytePropertyPrimaryKey = new Guid(Kind.SByteProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SinglePropertyPrimaryKey = new Guid(Kind.SingleProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid StringPropertyPrimaryKey = new Guid(Kind.StringProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BinaryTimeseriesPropertyPrimaryKey = new Guid(Kind.BinaryTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BooleanTimeseriesPropertyPrimaryKey = new Guid(Kind.BooleanTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ByteTimeseriesPropertyPrimaryKey = new Guid(Kind.ByteTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DateTimeTimeseriesPropertyPrimaryKey = new Guid(Kind.DateTimeTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DoubleTimeseriesPropertyPrimaryKey = new Guid(Kind.DoubleTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GuidTimeseriesPropertyPrimaryKey = new Guid(Kind.GuidTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int16TimeseriesPropertyPrimaryKey = new Guid(Kind.Int16TimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int32TimeseriesPropertyPrimaryKey = new Guid(Kind.Int32TimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int64TimeseriesPropertyPrimaryKey = new Guid(Kind.Int64TimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ReferenceTimeseriesPropertyPrimaryKey = new Guid(Kind.ReferenceTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SByteTimeseriesPropertyPrimaryKey = new Guid(Kind.SByteTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SingleTimeseriesPropertyPrimaryKey = new Guid(Kind.SingleTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid StringTimeseriesPropertyPrimaryKey = new Guid(Kind.StringTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TimeSpanTimeseriesPropertyPrimaryKey = new Guid(Kind.TimeSpanTimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt16TimeseriesPropertyPrimaryKey = new Guid(Kind.UInt16TimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt32TimeseriesPropertyPrimaryKey = new Guid(Kind.UInt32TimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt64TimeseriesPropertyPrimaryKey = new Guid(Kind.UInt64TimeseriesProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TimeSpanPropertyPrimaryKey = new Guid(Kind.TimeSpanProperty,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt16PropertyPrimaryKey = new Guid(Kind.UInt16Property,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt32PropertyPrimaryKey = new Guid(Kind.UInt32Property,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt64PropertyPrimaryKey = new Guid(Kind.UInt64Property,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BinaryPropertyDefinitionPrimaryKey = new Guid(Kind.BinaryPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BooleanPropertyDefinitionPrimaryKey = new Guid(Kind.BooleanPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BytePropertyDefinitionPrimaryKey = new Guid(Kind.BytePropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DateTimePropertyDefinitionPrimaryKey = new Guid(Kind.DateTimePropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DoublePropertyDefinitionPrimaryKey = new Guid(Kind.DoublePropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GuidPropertyDefinitionPrimaryKey = new Guid(Kind.GuidPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int16PropertyDefinitionPrimaryKey = new Guid(Kind.Int16PropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int32PropertyDefinitionPrimaryKey = new Guid(Kind.Int32PropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int64PropertyDefinitionPrimaryKey = new Guid(Kind.Int64PropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ReferencePropertyDefinitionPrimaryKey = new Guid(Kind.ReferencePropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SBytePropertyDefinitionPrimaryKey = new Guid(Kind.SBytePropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SinglePropertyDefinitionPrimaryKey = new Guid(Kind.SinglePropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid StringPropertyDefinitionPrimaryKey = new Guid(Kind.StringPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BinaryTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.BinaryTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BooleanTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.BooleanTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ByteTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.ByteTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DateTimeTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.DateTimeTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DoubleTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.DoubleTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GuidTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.GuidTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int16TimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.Int16TimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int32TimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.Int32TimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int64TimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.Int64TimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ReferenceTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.ReferenceTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SByteTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.SByteTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SingleTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.SingleTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid StringTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.StringTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TimeSpanTimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.TimeSpanTimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt16TimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.UInt16TimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt32TimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.UInt32TimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt64TimeseriesPropertyDefinitionPrimaryKey = new Guid(Kind.UInt64TimeseriesPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TimeSpanPropertyDefinitionPrimaryKey = new Guid(Kind.TimeSpanPropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt16PropertyDefinitionPrimaryKey = new Guid(Kind.UInt16PropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt32PropertyDefinitionPrimaryKey = new Guid(Kind.UInt32PropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt64PropertyDefinitionPrimaryKey = new Guid(Kind.UInt64PropertyDefinition,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarAlarmStatusPrimaryKey = new Guid(Kind.RadarAlarmStatus,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarCommandPrimaryKey = new Guid(Kind.RadarCommand,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarCommandGetStatusPrimaryKey = new Guid(Kind.RadarCommandGetStatus,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarCommandReplyPrimaryKey = new Guid(Kind.RadarCommandReply,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarCommandReplyGetStatusPrimaryKey = new Guid(Kind.RadarCommandReplyGetStatus,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarConfigurationPrimaryKey = new Guid(Kind.RadarConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarImagePrimaryKey = new Guid(Kind.RadarImage,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarRawTrackTablePrimaryKey = new Guid(Kind.RadarRawTrackTable,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarStatusPrimaryKey = new Guid(Kind.RadarStatus,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadioCommandPrimaryKey = new Guid(Kind.RadioCommand,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadioCommandReplyPrimaryKey = new Guid(Kind.RadioCommandReply,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadioConfigurationPrimaryKey = new Guid(Kind.RadioConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadomeCommandPrimaryKey = new Guid(Kind.RadomeCommand,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadomeCommandReplyPrimaryKey = new Guid(Kind.RadomeCommandReply,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadomeConfigurationPrimaryKey = new Guid(Kind.RadomeConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ReferenceTimeseriesValuePrimaryKey = new Guid(Kind.ReferenceTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SByteTimeseriesValuePrimaryKey = new Guid(Kind.SByteTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SecurityDomainPrimaryKey = new Guid(Kind.SecurityDomain,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SecurityLoginPrimaryKey = new Guid(Kind.SecurityLogin,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SecurityRolePrimaryKey = new Guid(Kind.SecurityRole,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SecurityIdentifierRoleLinkPrimaryKey = new Guid(Kind.SecurityIdentifierRoleLink,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SecurityLoginSessionPrimaryKey = new Guid(Kind.SecurityLoginSession,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SecurityPermissionPrimaryKey = new Guid(Kind.SecurityPermission,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SingleTimeseriesValuePrimaryKey = new Guid(Kind.SingleTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid StringTimeseriesValuePrimaryKey = new Guid(Kind.StringTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BinaryTimeseriesPrimaryKey = new Guid(Kind.BinaryTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid BooleanTimeseriesPrimaryKey = new Guid(Kind.BooleanTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisAidToNavigationOffPositionTimeseriesPrimaryKey = new Guid(Kind.AisAidToNavigationOffPositionTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DeviceEnabledTimeseriesPrimaryKey = new Guid(Kind.DeviceEnabledTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarAutomaticSensitivityTimeControlTimeseriesPrimaryKey = new Guid(Kind.RadarAutomaticSensitivityTimeControlTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarBlankSector1TimeseriesPrimaryKey = new Guid(Kind.RadarBlankSector1Timeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarBlankSector2TimeseriesPrimaryKey = new Guid(Kind.RadarBlankSector2Timeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarEnableAutomaticFrequencyControlTimeseriesPrimaryKey = new Guid(Kind.RadarEnableAutomaticFrequencyControlTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarEnableFastTimeConstantTimeseriesPrimaryKey = new Guid(Kind.RadarEnableFastTimeConstantTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarEnableSensitivityTimeControlTimeseriesPrimaryKey = new Guid(Kind.RadarEnableSensitivityTimeControlTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarPowerOnTimeseriesPrimaryKey = new Guid(Kind.RadarPowerOnTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarSaveSettingsTimeseriesPrimaryKey = new Guid(Kind.RadarSaveSettingsTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarTrackingTimeseriesPrimaryKey = new Guid(Kind.RadarTrackingTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MediaProxySessionEnabledTimeseriesPrimaryKey = new Guid(Kind.MediaProxySessionEnabledTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid MediaServiceEnabledTimeseriesPrimaryKey = new Guid(Kind.MediaServiceEnabledTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ByteTimeseriesPrimaryKey = new Guid(Kind.ByteTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DateTimeTimeseriesPrimaryKey = new Guid(Kind.DateTimeTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid DoubleTimeseriesPrimaryKey = new Guid(Kind.DoubleTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GNSSAltitudeTimeseriesPrimaryKey = new Guid(Kind.GNSSAltitudeTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GNSSLatitudeTimeseriesPrimaryKey = new Guid(Kind.GNSSLatitudeTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GNSSLongitudeTimeseriesPrimaryKey = new Guid(Kind.GNSSLongitudeTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroCourseTimeseriesPrimaryKey = new Guid(Kind.GyroCourseTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroHeadingMagneticNorthTimeseriesPrimaryKey = new Guid(Kind.GyroHeadingMagneticNorthTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroHeadingTrueNorthTimeseriesPrimaryKey = new Guid(Kind.GyroHeadingTrueNorthTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroPitchTimeseriesPrimaryKey = new Guid(Kind.GyroPitchTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroRateOfTurnTimeseriesPrimaryKey = new Guid(Kind.GyroRateOfTurnTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroRollTimeseriesPrimaryKey = new Guid(Kind.GyroRollTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GyroSpeedTimeseriesPrimaryKey = new Guid(Kind.GyroSpeedTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarLatitudeTimeseriesPrimaryKey = new Guid(Kind.RadarLatitudeTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarLongitudeTimeseriesPrimaryKey = new Guid(Kind.RadarLongitudeTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadomeDewPointTimeseriesPrimaryKey = new Guid(Kind.RadomeDewPointTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadomePressureTimeseriesPrimaryKey = new Guid(Kind.RadomePressureTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadomeTemperatureTimeseriesPrimaryKey = new Guid(Kind.RadomeTemperatureTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid VesselDraughtTimeseriesPrimaryKey = new Guid(Kind.VesselDraughtTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ViewLatitudeTimeseriesPrimaryKey = new Guid(Kind.ViewLatitudeTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ViewLongitudeTimeseriesPrimaryKey = new Guid(Kind.ViewLongitudeTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ViewZoomLevelTimeseriesPrimaryKey = new Guid(Kind.ViewZoomLevelTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationAbsoluteHumidityTimeseriesPrimaryKey = new Guid(Kind.WeatherStationAbsoluteHumidityTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationAirTemperatureTimeseriesPrimaryKey = new Guid(Kind.WeatherStationAirTemperatureTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationBarometricPressureTimeseriesPrimaryKey = new Guid(Kind.WeatherStationBarometricPressureTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationDewPointTimeseriesPrimaryKey = new Guid(Kind.WeatherStationDewPointTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationRelativeHumidityTimeseriesPrimaryKey = new Guid(Kind.WeatherStationRelativeHumidityTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationWaterTemperatureTimeseriesPrimaryKey = new Guid(Kind.WeatherStationWaterTemperatureTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationWindDirectionTimeseriesPrimaryKey = new Guid(Kind.WeatherStationWindDirectionTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationWindSpeedTimeseriesPrimaryKey = new Guid(Kind.WeatherStationWindSpeedTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GeoPosition2DTimeseriesPrimaryKey = new Guid(Kind.GeoPosition2DTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid AisAidToNavigationPositionTimeseriesPrimaryKey = new Guid(Kind.AisAidToNavigationPositionTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GeoPosition3DTimeseriesPrimaryKey = new Guid(Kind.GeoPosition3DTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid GuidTimeseriesPrimaryKey = new Guid(Kind.GuidTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int16TimeseriesPrimaryKey = new Guid(Kind.Int16Timeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int32TimeseriesPrimaryKey = new Guid(Kind.Int32Timeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarAzimuthOffsetTimeseriesPrimaryKey = new Guid(Kind.RadarAzimuthOffsetTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarFastTimeConstantLevelTimeseriesPrimaryKey = new Guid(Kind.RadarFastTimeConstantLevelTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarFastTimeConstantModeTimeseriesPrimaryKey = new Guid(Kind.RadarFastTimeConstantModeTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarPulseTimeseriesPrimaryKey = new Guid(Kind.RadarPulseTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarSector1EndTimeseriesPrimaryKey = new Guid(Kind.RadarSector1EndTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarSector1StartTimeseriesPrimaryKey = new Guid(Kind.RadarSector1StartTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarSector2EndTimeseriesPrimaryKey = new Guid(Kind.RadarSector2EndTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarSector2StartTimeseriesPrimaryKey = new Guid(Kind.RadarSector2StartTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarSensitivityTimeControlLevelTimeseriesPrimaryKey = new Guid(Kind.RadarSensitivityTimeControlLevelTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadarTuningTimeseriesPrimaryKey = new Guid(Kind.RadarTuningTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid VesselPersonsOnBoardTimeseriesPrimaryKey = new Guid(Kind.VesselPersonsOnBoardTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Int64TimeseriesPrimaryKey = new Guid(Kind.Int64Timeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Position2DTimeseriesPrimaryKey = new Guid(Kind.Position2DTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Position3DTimeseriesPrimaryKey = new Guid(Kind.Position3DTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ReferenceTimeseriesPrimaryKey = new Guid(Kind.ReferenceTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SByteTimeseriesPrimaryKey = new Guid(Kind.SByteTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid SingleTimeseriesPrimaryKey = new Guid(Kind.SingleTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid StringTimeseriesPrimaryKey = new Guid(Kind.StringTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TimeSpanTimeseriesPrimaryKey = new Guid(Kind.TimeSpanTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt16TimeseriesPrimaryKey = new Guid(Kind.UInt16Timeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt32TimeseriesPrimaryKey = new Guid(Kind.UInt32Timeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid RadomeStatusTimeseriesPrimaryKey = new Guid(Kind.RadomeStatusTimeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt64TimeseriesPrimaryKey = new Guid(Kind.UInt64Timeseries,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TimeseriesCatalogPrimaryKey = new Guid(Kind.TimeseriesCatalog,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TimeseriesInfoPrimaryKey = new Guid(Kind.TimeseriesInfo,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TimeSpanTimeseriesValuePrimaryKey = new Guid(Kind.TimeSpanTimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TrackableItemTrackLinkPrimaryKey = new Guid(Kind.TrackableItemTrackLink,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TrackPrimaryKey = new Guid(Kind.Track,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid Track3DPrimaryKey = new Guid(Kind.Track3D,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TrackerFilterParametersPrimaryKey = new Guid(Kind.TrackerFilterParameters,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TrackerFilterParametersConfigurationPrimaryKey = new Guid(Kind.TrackerFilterParametersConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TrackInfoPrimaryKey = new Guid(Kind.TrackInfo,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TrackingServiceOptionsPrimaryKey = new Guid(Kind.TrackingServiceOptions,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TrackLinkPrimaryKey = new Guid(Kind.TrackLink,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TrackValuePrimaryKey = new Guid(Kind.TrackValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid TrackValue3DPrimaryKey = new Guid(Kind.TrackValue3D,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt16TimeseriesValuePrimaryKey = new Guid(Kind.UInt16TimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt32TimeseriesValuePrimaryKey = new Guid(Kind.UInt32TimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid UInt64TimeseriesValuePrimaryKey = new Guid(Kind.UInt64TimeseriesValue,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid VehicleTypePrimaryKey = new Guid(Kind.VehicleType,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid VesselTypePrimaryKey = new Guid(Kind.VesselType,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ViewPrimaryKey = new Guid(Kind.View,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ViewCameraLinkPrimaryKey = new Guid(Kind.ViewCameraLink,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ViewTrackerLinkPrimaryKey = new Guid(Kind.ViewTrackerLink,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationCommandPrimaryKey = new Guid(Kind.WeatherStationCommand,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationCommandReplyPrimaryKey = new Guid(Kind.WeatherStationCommandReply,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid WeatherStationConfigurationPrimaryKey = new Guid(Kind.WeatherStationConfiguration,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid CircularZonePrimaryKey = new Guid(Kind.CircularZone,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid PolygonZonePrimaryKey = new Guid(Kind.PolygonZone,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ZoneExceptionsPrimaryKey = new Guid(Kind.ZoneExceptions,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ZoneExceptionsVesselLinkPrimaryKey = new Guid(Kind.ZoneExceptionsVesselLink,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);
    public final static Guid ZoneTrackAlarmPrimaryKey = new Guid(Kind.ZoneTrackAlarm,(short)0,(short)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0);

    private AircraftTypeObject _aircraftType = null;
    private AisDeviceCommandObject _aisDeviceCommand = null;
    private AisDeviceCommandReplyObject _aisDeviceCommandReply = null;
    private AisDeviceConfigurationObject _aisDeviceConfiguration = null;
    private AisDeviceRawMessageObject _aisDeviceRawMessage = null;
    private AisDeviceRawSentenceObject _aisDeviceRawSentence = null;
    private AidToNavigationReportMessageObject _aidToNavigationReportMessage = null;
    private AisAddressedSafetyRelatedMessageObject _aisAddressedSafetyRelatedMessage = null;
    private AisBaseStationReportMessageObject _aisBaseStationReportMessage = null;
    private AisBinaryAcknowledgeMessageObject _aisBinaryAcknowledgeMessage = null;
    private AisBinaryAddressedMessageObject _aisBinaryAddressedMessage = null;
    private AisBinaryBroadcastMessageObject _aisBinaryBroadcastMessage = null;
    private AisDataLinkManagementMessageObject _aisDataLinkManagementMessage = null;
    private AisExtendedClassBCsPositionReportMessageObject _aisExtendedClassBCsPositionReportMessage = null;
    private AisInterrogationMessageObject _aisInterrogationMessage = null;
    private AisPositionReportClassAAssignedScheduleMessageObject _aisPositionReportClassAAssignedScheduleMessage = null;
    private AisPositionReportClassAMessageObject _aisPositionReportClassAMessage = null;
    private AisPositionReportClassAResponseToInterrogationMessageObject _aisPositionReportClassAResponseToInterrogationMessage = null;
    private AisPositionReportForLongRangeApplicationsMessageObject _aisPositionReportForLongRangeApplicationsMessage = null;
    private AisSafetyRelatedAcknowledgmentMessageObject _aisSafetyRelatedAcknowledgmentMessage = null;
    private AisStandardClassBCsPositionReportMessageObject _aisStandardClassBCsPositionReportMessage = null;
    private AisStandardSarAircraftPositionReportMessageObject _aisStandardSarAircraftPositionReportMessage = null;
    private AisStaticAndVoyageRelatedDataMessageObject _aisStaticAndVoyageRelatedDataMessage = null;
    private AisStaticDataReportMessageObject _aisStaticDataReportMessage = null;
    private AisStaticDataReportPartAMessageObject _aisStaticDataReportPartAMessage = null;
    private AisStaticDataReportPartBMessageObject _aisStaticDataReportPartBMessage = null;
    private AisUtcAndDateInquiryMessageObject _aisUtcAndDateInquiryMessage = null;
    private AisUtcAndDateResponseMessageObject _aisUtcAndDateResponseMessage = null;
    private AlarmStateChangeObject _alarmStateChange = null;
    private BaseStationTypeObject _baseStationType = null;
    private BinaryTimeseriesValueObject _binaryTimeseriesValue = null;
    private BookmarkObject _bookmark = null;
    private BooleanTimeseriesValueObject _booleanTimeseriesValue = null;
    private ByteTimeseriesValueObject _byteTimeseriesValue = null;
    private CameraCommandObject _cameraCommand = null;
    private CameraCommandAbsoluteMoveObject _cameraCommandAbsoluteMove = null;
    private CameraCommandAdjustPanTiltZoomObject _cameraCommandAdjustPanTiltZoom = null;
    private CameraCommandContinuousMoveObject _cameraCommandContinuousMove = null;
    private CameraCommandGeoMoveObject _cameraCommandGeoMove = null;
    private CameraCommandRelativeMoveObject _cameraCommandRelativeMove = null;
    private CameraCommandReleasePTZOwnershipObject _cameraCommandReleasePTZOwnership = null;
    private CameraCommandRequestPTZOwnershipObject _cameraCommandRequestPTZOwnership = null;
    private CameraCommandSetAutoFocusObject _cameraCommandSetAutoFocus = null;
    private CameraCommandSetBlackAndWhiteObject _cameraCommandSetBlackAndWhite = null;
    private CameraCommandSetFollowedObject _cameraCommandSetFollowed = null;
    private CameraCommandSetInfraRedLampObject _cameraCommandSetInfraRedLamp = null;
    private CameraCommandSetWasherObject _cameraCommandSetWasher = null;
    private CameraCommandSetWiperObject _cameraCommandSetWiper = null;
    private CameraCommandStopObject _cameraCommandStop = null;
    private CameraCommandReplyObject _cameraCommandReply = null;
    private CameraConfigurationObject _cameraConfiguration = null;
    private CameraPanCalibrationObject _cameraPanCalibration = null;
    private CameraPanCalibrationValueObject _cameraPanCalibrationValue = null;
    private CameraStatusObject _cameraStatus = null;
    private CameraTiltCalibrationObject _cameraTiltCalibration = null;
    private CameraTiltCalibrationValueObject _cameraTiltCalibrationValue = null;
    private CameraZoomCalibrationObject _cameraZoomCalibration = null;
    private CameraZoomCalibrationValueObject _cameraZoomCalibrationValue = null;
    private CatalogObject _catalog = null;
    private ElementObject _element = null;
    private CollectionInfoObject _collectionInfo = null;
    private CountryObject _country = null;
    private CursorInfoObject _cursorInfo = null;
    private DateTimeTimeseriesValueObject _dateTimeTimeseriesValue = null;
    private DeviceHostObject _deviceHost = null;
    private DeviceHostConfigurationObject _deviceHostConfiguration = null;
    private DoubleTimeseriesValueObject _doubleTimeseriesValue = null;
    private FacilityTypeObject _facilityType = null;
    private GeoPosition2DTimeseriesValueObject _geoPosition2DTimeseriesValue = null;
    private GeoPosition3DTimeseriesValueObject _geoPosition3DTimeseriesValue = null;
    private GNSSDeviceCommandObject _gNSSDeviceCommand = null;
    private GNSSDeviceCommandReplyObject _gNSSDeviceCommandReply = null;
    private GNSSDeviceConfigurationObject _gNSSDeviceConfiguration = null;
    private GuidTimeseriesValueObject _guidTimeseriesValue = null;
    private GyroDeviceCommandObject _gyroDeviceCommand = null;
    private GyroDeviceCommandReplyObject _gyroDeviceCommandReply = null;
    private GyroDeviceConfigurationObject _gyroDeviceConfiguration = null;
    private CallsignObject _callsign = null;
    private InternationalMaritimeOrganizationNumberObject _internationalMaritimeOrganizationNumber = null;
    private MaritimeMobileServiceIdentityObject _maritimeMobileServiceIdentity = null;
    private NameObject _name = null;
    private Int16TimeseriesValueObject _int16TimeseriesValue = null;
    private Int32TimeseriesValueObject _int32TimeseriesValue = null;
    private Int64TimeseriesValueObject _int64TimeseriesValue = null;
    private BaseStationObject _baseStation = null;
    private CameraDeviceObject _cameraDevice = null;
    private GNSSDeviceObject _gNSSDevice = null;
    private GyroDeviceObject _gyroDevice = null;
    private LineInputDeviceObject _lineInputDevice = null;
    private OilSpillDetectorDeviceObject _oilSpillDetectorDevice = null;
    private RadioDeviceObject _radioDevice = null;
    private RadomeDeviceObject _radomeDevice = null;
    private AisDeviceObject _aisDevice = null;
    private RadarDeviceObject _radarDevice = null;
    private WeatherStationDeviceObject _weatherStationDevice = null;
    private FacilityObject _facility = null;
    private AircraftObject _aircraft = null;
    private AisAidToNavigationObject _aisAidToNavigation = null;
    private VehicleObject _vehicle = null;
    private VesselObject _vessel = null;
    private ItemIdentityLinkObject _itemIdentityLink = null;
    private ItemParentChildLinkObject _itemParentChildLink = null;
    private LineInputDeviceCommandObject _lineInputDeviceCommand = null;
    private LineInputDeviceCommandReplyObject _lineInputDeviceCommandReply = null;
    private LineInputDeviceConfigurationObject _lineInputDeviceConfiguration = null;
    private LineInputMessageRoutingObject _lineInputMessageRouting = null;
    private LineInputMessageRoutingDestinationObject _lineInputMessageRoutingDestination = null;
    private LineInputWhiteListEntryObject _lineInputWhiteListEntry = null;
    private LogApplicationObject _logApplication = null;
    private LogApplicationConfigurationObject _logApplicationConfiguration = null;
    private LogHostObject _logHost = null;
    private LogHostConfigurationObject _logHostConfiguration = null;
    private LogLocationObject _logLocation = null;
    private LogProcessObject _logProcess = null;
    private LogRecordObject _logRecord = null;
    private LogThreadObject _logThread = null;
    private LogTraceEntryObject _logTraceEntry = null;
    private MapElementObject _mapElement = null;
    private MapInfoObject _mapInfo = null;
    private MapServiceOptionsObject _mapServiceOptions = null;
    private MaritimeIdentificationDigitsObject _maritimeIdentificationDigits = null;
    private MediaProxySessionObject _mediaProxySession = null;
    private MediaProxySessionFileObject _mediaProxySessionFile = null;
    private MediaProxySessionOptionsObject _mediaProxySessionOptions = null;
    private MediaServiceObject _mediaService = null;
    private MediaServiceOptionsObject _mediaServiceOptions = null;
    private ElementTypeObject _elementType = null;
    private NamespaceObject _namespace = null;
    private OilSpillObject _oilSpill = null;
    private OilSpillDetectorCommandObject _oilSpillDetectorCommand = null;
    private OilSpillDetectorCommandReplyObject _oilSpillDetectorCommandReply = null;
    private OilSpillDetectorConfigurationObject _oilSpillDetectorConfiguration = null;
    private Position2DTimeseriesValueObject _position2DTimeseriesValue = null;
    private Position3DTimeseriesValueObject _position3DTimeseriesValue = null;
    private ProcessTrackValueResultObject _processTrackValueResult = null;
    private BinaryPropertyObject _binaryProperty = null;
    private BooleanPropertyObject _booleanProperty = null;
    private BytePropertyObject _byteProperty = null;
    private DateTimePropertyObject _dateTimeProperty = null;
    private DoublePropertyObject _doubleProperty = null;
    private GuidPropertyObject _guidProperty = null;
    private Int16PropertyObject _int16Property = null;
    private Int32PropertyObject _int32Property = null;
    private Int64PropertyObject _int64Property = null;
    private ReferencePropertyObject _referenceProperty = null;
    private SBytePropertyObject _sByteProperty = null;
    private SinglePropertyObject _singleProperty = null;
    private StringPropertyObject _stringProperty = null;
    private BinaryTimeseriesPropertyObject _binaryTimeseriesProperty = null;
    private BooleanTimeseriesPropertyObject _booleanTimeseriesProperty = null;
    private ByteTimeseriesPropertyObject _byteTimeseriesProperty = null;
    private DateTimeTimeseriesPropertyObject _dateTimeTimeseriesProperty = null;
    private DoubleTimeseriesPropertyObject _doubleTimeseriesProperty = null;
    private GuidTimeseriesPropertyObject _guidTimeseriesProperty = null;
    private Int16TimeseriesPropertyObject _int16TimeseriesProperty = null;
    private Int32TimeseriesPropertyObject _int32TimeseriesProperty = null;
    private Int64TimeseriesPropertyObject _int64TimeseriesProperty = null;
    private ReferenceTimeseriesPropertyObject _referenceTimeseriesProperty = null;
    private SByteTimeseriesPropertyObject _sByteTimeseriesProperty = null;
    private SingleTimeseriesPropertyObject _singleTimeseriesProperty = null;
    private StringTimeseriesPropertyObject _stringTimeseriesProperty = null;
    private TimeSpanTimeseriesPropertyObject _timeSpanTimeseriesProperty = null;
    private UInt16TimeseriesPropertyObject _uInt16TimeseriesProperty = null;
    private UInt32TimeseriesPropertyObject _uInt32TimeseriesProperty = null;
    private UInt64TimeseriesPropertyObject _uInt64TimeseriesProperty = null;
    private TimeSpanPropertyObject _timeSpanProperty = null;
    private UInt16PropertyObject _uInt16Property = null;
    private UInt32PropertyObject _uInt32Property = null;
    private UInt64PropertyObject _uInt64Property = null;
    private BinaryPropertyDefinitionObject _binaryPropertyDefinition = null;
    private BooleanPropertyDefinitionObject _booleanPropertyDefinition = null;
    private BytePropertyDefinitionObject _bytePropertyDefinition = null;
    private DateTimePropertyDefinitionObject _dateTimePropertyDefinition = null;
    private DoublePropertyDefinitionObject _doublePropertyDefinition = null;
    private GuidPropertyDefinitionObject _guidPropertyDefinition = null;
    private Int16PropertyDefinitionObject _int16PropertyDefinition = null;
    private Int32PropertyDefinitionObject _int32PropertyDefinition = null;
    private Int64PropertyDefinitionObject _int64PropertyDefinition = null;
    private ReferencePropertyDefinitionObject _referencePropertyDefinition = null;
    private SBytePropertyDefinitionObject _sBytePropertyDefinition = null;
    private SinglePropertyDefinitionObject _singlePropertyDefinition = null;
    private StringPropertyDefinitionObject _stringPropertyDefinition = null;
    private BinaryTimeseriesPropertyDefinitionObject _binaryTimeseriesPropertyDefinition = null;
    private BooleanTimeseriesPropertyDefinitionObject _booleanTimeseriesPropertyDefinition = null;
    private ByteTimeseriesPropertyDefinitionObject _byteTimeseriesPropertyDefinition = null;
    private DateTimeTimeseriesPropertyDefinitionObject _dateTimeTimeseriesPropertyDefinition = null;
    private DoubleTimeseriesPropertyDefinitionObject _doubleTimeseriesPropertyDefinition = null;
    private GuidTimeseriesPropertyDefinitionObject _guidTimeseriesPropertyDefinition = null;
    private Int16TimeseriesPropertyDefinitionObject _int16TimeseriesPropertyDefinition = null;
    private Int32TimeseriesPropertyDefinitionObject _int32TimeseriesPropertyDefinition = null;
    private Int64TimeseriesPropertyDefinitionObject _int64TimeseriesPropertyDefinition = null;
    private ReferenceTimeseriesPropertyDefinitionObject _referenceTimeseriesPropertyDefinition = null;
    private SByteTimeseriesPropertyDefinitionObject _sByteTimeseriesPropertyDefinition = null;
    private SingleTimeseriesPropertyDefinitionObject _singleTimeseriesPropertyDefinition = null;
    private StringTimeseriesPropertyDefinitionObject _stringTimeseriesPropertyDefinition = null;
    private TimeSpanTimeseriesPropertyDefinitionObject _timeSpanTimeseriesPropertyDefinition = null;
    private UInt16TimeseriesPropertyDefinitionObject _uInt16TimeseriesPropertyDefinition = null;
    private UInt32TimeseriesPropertyDefinitionObject _uInt32TimeseriesPropertyDefinition = null;
    private UInt64TimeseriesPropertyDefinitionObject _uInt64TimeseriesPropertyDefinition = null;
    private TimeSpanPropertyDefinitionObject _timeSpanPropertyDefinition = null;
    private UInt16PropertyDefinitionObject _uInt16PropertyDefinition = null;
    private UInt32PropertyDefinitionObject _uInt32PropertyDefinition = null;
    private UInt64PropertyDefinitionObject _uInt64PropertyDefinition = null;
    private RadarAlarmStatusObject _radarAlarmStatus = null;
    private RadarCommandObject _radarCommand = null;
    private RadarCommandGetStatusObject _radarCommandGetStatus = null;
    private RadarCommandReplyObject _radarCommandReply = null;
    private RadarCommandReplyGetStatusObject _radarCommandReplyGetStatus = null;
    private RadarConfigurationObject _radarConfiguration = null;
    private RadarImageObject _radarImage = null;
    private RadarRawTrackTableObject _radarRawTrackTable = null;
    private RadarStatusObject _radarStatus = null;
    private RadioCommandObject _radioCommand = null;
    private RadioCommandReplyObject _radioCommandReply = null;
    private RadioConfigurationObject _radioConfiguration = null;
    private RadomeCommandObject _radomeCommand = null;
    private RadomeCommandReplyObject _radomeCommandReply = null;
    private RadomeConfigurationObject _radomeConfiguration = null;
    private ReferenceTimeseriesValueObject _referenceTimeseriesValue = null;
    private SByteTimeseriesValueObject _sByteTimeseriesValue = null;
    private SecurityDomainObject _securityDomain = null;
    private SecurityLoginObject _securityLogin = null;
    private SecurityRoleObject _securityRole = null;
    private SecurityIdentifierRoleLinkObject _securityIdentifierRoleLink = null;
    private SecurityLoginSessionObject _securityLoginSession = null;
    private SecurityPermissionObject _securityPermission = null;
    private SingleTimeseriesValueObject _singleTimeseriesValue = null;
    private StringTimeseriesValueObject _stringTimeseriesValue = null;
    private BinaryTimeseriesObject _binaryTimeseries = null;
    private BooleanTimeseriesObject _booleanTimeseries = null;
    private AisAidToNavigationOffPositionTimeseriesObject _aisAidToNavigationOffPositionTimeseries = null;
    private DeviceEnabledTimeseriesObject _deviceEnabledTimeseries = null;
    private RadarAutomaticSensitivityTimeControlTimeseriesObject _radarAutomaticSensitivityTimeControlTimeseries = null;
    private RadarBlankSector1TimeseriesObject _radarBlankSector1Timeseries = null;
    private RadarBlankSector2TimeseriesObject _radarBlankSector2Timeseries = null;
    private RadarEnableAutomaticFrequencyControlTimeseriesObject _radarEnableAutomaticFrequencyControlTimeseries = null;
    private RadarEnableFastTimeConstantTimeseriesObject _radarEnableFastTimeConstantTimeseries = null;
    private RadarEnableSensitivityTimeControlTimeseriesObject _radarEnableSensitivityTimeControlTimeseries = null;
    private RadarPowerOnTimeseriesObject _radarPowerOnTimeseries = null;
    private RadarSaveSettingsTimeseriesObject _radarSaveSettingsTimeseries = null;
    private RadarTrackingTimeseriesObject _radarTrackingTimeseries = null;
    private MediaProxySessionEnabledTimeseriesObject _mediaProxySessionEnabledTimeseries = null;
    private MediaServiceEnabledTimeseriesObject _mediaServiceEnabledTimeseries = null;
    private ByteTimeseriesObject _byteTimeseries = null;
    private DateTimeTimeseriesObject _dateTimeTimeseries = null;
    private DoubleTimeseriesObject _doubleTimeseries = null;
    private GNSSAltitudeTimeseriesObject _gNSSAltitudeTimeseries = null;
    private GNSSLatitudeTimeseriesObject _gNSSLatitudeTimeseries = null;
    private GNSSLongitudeTimeseriesObject _gNSSLongitudeTimeseries = null;
    private GyroCourseTimeseriesObject _gyroCourseTimeseries = null;
    private GyroHeadingMagneticNorthTimeseriesObject _gyroHeadingMagneticNorthTimeseries = null;
    private GyroHeadingTrueNorthTimeseriesObject _gyroHeadingTrueNorthTimeseries = null;
    private GyroPitchTimeseriesObject _gyroPitchTimeseries = null;
    private GyroRateOfTurnTimeseriesObject _gyroRateOfTurnTimeseries = null;
    private GyroRollTimeseriesObject _gyroRollTimeseries = null;
    private GyroSpeedTimeseriesObject _gyroSpeedTimeseries = null;
    private RadarLatitudeTimeseriesObject _radarLatitudeTimeseries = null;
    private RadarLongitudeTimeseriesObject _radarLongitudeTimeseries = null;
    private RadomeDewPointTimeseriesObject _radomeDewPointTimeseries = null;
    private RadomePressureTimeseriesObject _radomePressureTimeseries = null;
    private RadomeTemperatureTimeseriesObject _radomeTemperatureTimeseries = null;
    private VesselDraughtTimeseriesObject _vesselDraughtTimeseries = null;
    private ViewLatitudeTimeseriesObject _viewLatitudeTimeseries = null;
    private ViewLongitudeTimeseriesObject _viewLongitudeTimeseries = null;
    private ViewZoomLevelTimeseriesObject _viewZoomLevelTimeseries = null;
    private WeatherStationAbsoluteHumidityTimeseriesObject _weatherStationAbsoluteHumidityTimeseries = null;
    private WeatherStationAirTemperatureTimeseriesObject _weatherStationAirTemperatureTimeseries = null;
    private WeatherStationBarometricPressureTimeseriesObject _weatherStationBarometricPressureTimeseries = null;
    private WeatherStationDewPointTimeseriesObject _weatherStationDewPointTimeseries = null;
    private WeatherStationRelativeHumidityTimeseriesObject _weatherStationRelativeHumidityTimeseries = null;
    private WeatherStationWaterTemperatureTimeseriesObject _weatherStationWaterTemperatureTimeseries = null;
    private WeatherStationWindDirectionTimeseriesObject _weatherStationWindDirectionTimeseries = null;
    private WeatherStationWindSpeedTimeseriesObject _weatherStationWindSpeedTimeseries = null;
    private GeoPosition2DTimeseriesObject _geoPosition2DTimeseries = null;
    private AisAidToNavigationPositionTimeseriesObject _aisAidToNavigationPositionTimeseries = null;
    private GeoPosition3DTimeseriesObject _geoPosition3DTimeseries = null;
    private GuidTimeseriesObject _guidTimeseries = null;
    private Int16TimeseriesObject _int16Timeseries = null;
    private Int32TimeseriesObject _int32Timeseries = null;
    private RadarAzimuthOffsetTimeseriesObject _radarAzimuthOffsetTimeseries = null;
    private RadarFastTimeConstantLevelTimeseriesObject _radarFastTimeConstantLevelTimeseries = null;
    private RadarFastTimeConstantModeTimeseriesObject _radarFastTimeConstantModeTimeseries = null;
    private RadarPulseTimeseriesObject _radarPulseTimeseries = null;
    private RadarSector1EndTimeseriesObject _radarSector1EndTimeseries = null;
    private RadarSector1StartTimeseriesObject _radarSector1StartTimeseries = null;
    private RadarSector2EndTimeseriesObject _radarSector2EndTimeseries = null;
    private RadarSector2StartTimeseriesObject _radarSector2StartTimeseries = null;
    private RadarSensitivityTimeControlLevelTimeseriesObject _radarSensitivityTimeControlLevelTimeseries = null;
    private RadarTuningTimeseriesObject _radarTuningTimeseries = null;
    private VesselPersonsOnBoardTimeseriesObject _vesselPersonsOnBoardTimeseries = null;
    private Int64TimeseriesObject _int64Timeseries = null;
    private Position2DTimeseriesObject _position2DTimeseries = null;
    private Position3DTimeseriesObject _position3DTimeseries = null;
    private ReferenceTimeseriesObject _referenceTimeseries = null;
    private SByteTimeseriesObject _sByteTimeseries = null;
    private SingleTimeseriesObject _singleTimeseries = null;
    private StringTimeseriesObject _stringTimeseries = null;
    private TimeSpanTimeseriesObject _timeSpanTimeseries = null;
    private UInt16TimeseriesObject _uInt16Timeseries = null;
    private UInt32TimeseriesObject _uInt32Timeseries = null;
    private RadomeStatusTimeseriesObject _radomeStatusTimeseries = null;
    private UInt64TimeseriesObject _uInt64Timeseries = null;
    private TimeseriesCatalogObject _timeseriesCatalog = null;
    private TimeseriesInfoObject _timeseriesInfo = null;
    private TimeSpanTimeseriesValueObject _timeSpanTimeseriesValue = null;
    private TrackableItemTrackLinkObject _trackableItemTrackLink = null;
    private TrackObject _track = null;
    private Track3DObject _track3D = null;
    private TrackerFilterParametersObject _trackerFilterParameters = null;
    private TrackerFilterParametersConfigurationObject _trackerFilterParametersConfiguration = null;
    private TrackInfoObject _trackInfo = null;
    private TrackingServiceOptionsObject _trackingServiceOptions = null;
    private TrackLinkObject _trackLink = null;
    private TrackValueObject _trackValue = null;
    private TrackValue3DObject _trackValue3D = null;
    private UInt16TimeseriesValueObject _uInt16TimeseriesValue = null;
    private UInt32TimeseriesValueObject _uInt32TimeseriesValue = null;
    private UInt64TimeseriesValueObject _uInt64TimeseriesValue = null;
    private VehicleTypeObject _vehicleType = null;
    private VesselTypeObject _vesselType = null;
    private ViewObject _view = null;
    private ViewCameraLinkObject _viewCameraLink = null;
    private ViewTrackerLinkObject _viewTrackerLink = null;
    private WeatherStationCommandObject _weatherStationCommand = null;
    private WeatherStationCommandReplyObject _weatherStationCommandReply = null;
    private WeatherStationConfigurationObject _weatherStationConfiguration = null;
    private CircularZoneObject _circularZone = null;
    private PolygonZoneObject _polygonZone = null;
    private ZoneExceptionsObject _zoneExceptions = null;
    private ZoneExceptionsVesselLinkObject _zoneExceptionsVesselLink = null;
    private ZoneTrackAlarmObject _zoneTrackAlarm = null;

    public AircraftTypeObject getAircraftType() {
        if (_aircraftType == null) {
            long rowVersion = 0;
            String name = "NameAircraftTypeUnitTest";

            _aircraftType = new AircraftTypeObject( ObjectState.New, AircraftTypePrimaryKey, rowVersion, name );
        }
        return _aircraftType;
    }

    public AisDeviceCommandObject getAisDeviceCommand() {
        if (_aisDeviceCommand == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _aisDeviceCommand = new AisDeviceCommandObject( ObjectState.New, AisDeviceCommandPrimaryKey, rowVersion, aisDevice, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _aisDeviceCommand;
    }

    public AisDeviceCommandReplyObject getAisDeviceCommandReply() {
        if (_aisDeviceCommandReply == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageAisDeviceCommandReplyUnitTest";

            _aisDeviceCommandReply = new AisDeviceCommandReplyObject( ObjectState.New, AisDeviceCommandReplyPrimaryKey, rowVersion, aisDevice, timestamp, command, status, message );
        }
        return _aisDeviceCommandReply;
    }

    public AisDeviceConfigurationObject getAisDeviceConfiguration() {
        if (_aisDeviceConfiguration == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            boolean filter = false;
            double northWestLatitude = 0.0;
            double northWestLongitude = 0.0;
            double southEastLatitude = 0.0;
            double southEastLongitude = 0.0;
            String comPort = "ComPortAisDeviceConfigurationU";
            int baudRate = 0;
            String iPAddress = "IPAddressAisDeviceConfigurationUnitTest";
            int port = 0;
            int udpPort = 0;
            boolean authenticate = false;
            String userName = "UserNameAisDeviceConfigurationUnitTest";
            String password = "PasswordAisDeviceConfigurationUnitTest";
            String authenticationURL = "AuthenticationURLAisDeviceConfigurationUnitTest";
            int connectionType = AisDeviceConnectionType.Unknown;
            int sourceUpdateRate = 0;
            String configurationURL = "ConfigurationURLAisDeviceConfigurationUnitTest";
            boolean storeReceivedSentences = false;

            _aisDeviceConfiguration = new AisDeviceConfigurationObject( ObjectState.New, AisDeviceConfigurationPrimaryKey, rowVersion, aisDevice, timestamp, filter, northWestLatitude, northWestLongitude, southEastLatitude, southEastLongitude, comPort, baudRate, iPAddress, port, udpPort, authenticate, userName, password, authenticationURL, connectionType, sourceUpdateRate, configurationURL, storeReceivedSentences );
        }
        return _aisDeviceConfiguration;
    }

    public AisDeviceRawMessageObject getAisDeviceRawMessage() {
        if (_aisDeviceRawMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            boolean isSent = false;
            String message = "MessageAisDeviceRawMessageUnitTest";

            _aisDeviceRawMessage = new AisDeviceRawMessageObject( ObjectState.New, AisDeviceRawMessagePrimaryKey, rowVersion, aisDevice, timestamp, isSent, message );
        }
        return _aisDeviceRawMessage;
    }

    public AisDeviceRawSentenceObject getAisDeviceRawSentence() {
        if (_aisDeviceRawSentence == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            String sentence = "SentenceAisDeviceRawSentenceUnitTest";

            _aisDeviceRawSentence = new AisDeviceRawSentenceObject( ObjectState.New, AisDeviceRawSentencePrimaryKey, rowVersion, aisDevice, timestamp, sentence );
        }
        return _aisDeviceRawSentence;
    }

    public AidToNavigationReportMessageObject getAidToNavigationReportMessage() {
        if (_aidToNavigationReportMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int navigationalAidType = NavigationalAidType.NotSpecified;
            String name = "NameAidToNavigationReportMessageUnitTest";
            int positionAccuracy = PositionAccuracy.Low;
            double longitude = 0.0;
            double latitude = 0.0;
            int dimensionToBow = 0;
            int dimensionToStern = 0;
            int dimensionToPort = 0;
            int dimensionToStarboard = 0;
            int positionFixType = PositionFixType.Undefined1;
            int timestamp = 0;
            boolean offPosition = false;
            int regionalReserved = 0;
            int raim = Raim.NotInUse;
            boolean virtualAid = false;
            boolean assigned = false;
            int spare = 0;
            String nameExtension = "NameExtensionAidToNavigationReportMessageUnitTest";

            _aidToNavigationReportMessage = new AidToNavigationReportMessageObject( ObjectState.New, AidToNavigationReportMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, navigationalAidType, name, positionAccuracy, longitude, latitude, dimensionToBow, dimensionToStern, dimensionToPort, dimensionToStarboard, positionFixType, timestamp, offPosition, regionalReserved, raim, virtualAid, assigned, spare, nameExtension );
        }
        return _aidToNavigationReportMessage;
    }

    public AisAddressedSafetyRelatedMessageObject getAisAddressedSafetyRelatedMessage() {
        if (_aisAddressedSafetyRelatedMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int sequenceNumber = 0;
            Guid destinationMmsi = null;
            boolean retransmitFlag = false;
            int spare = 0;
            String text = "TextAisAddressedSafetyRelatedMessageUnitTest";

            _aisAddressedSafetyRelatedMessage = new AisAddressedSafetyRelatedMessageObject( ObjectState.New, AisAddressedSafetyRelatedMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, sequenceNumber, destinationMmsi, retransmitFlag, spare, text );
        }
        return _aisAddressedSafetyRelatedMessage;
    }

    public AisBaseStationReportMessageObject getAisBaseStationReportMessage() {
        if (_aisBaseStationReportMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int positionAccuracy = PositionAccuracy.Low;
            double longitude = 0.0;
            double latitude = 0.0;
            int positionFixType = PositionFixType.Undefined1;
            int spare = 0;
            int raim = Raim.NotInUse;
            int radioStatus = 0;

            _aisBaseStationReportMessage = new AisBaseStationReportMessageObject( ObjectState.New, AisBaseStationReportMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, timestamp, positionAccuracy, longitude, latitude, positionFixType, spare, raim, radioStatus );
        }
        return _aisBaseStationReportMessage;
    }

    public AisBinaryAcknowledgeMessageObject getAisBinaryAcknowledgeMessage() {
        if (_aisBinaryAcknowledgeMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int spare = 0;
            int sequenceNumber1 = 0;
            Guid mmsi1 = null;
            Integer sequenceNumber2 = null;
            Guid mmsi2 = null;
            Integer sequenceNumber3 = null;
            Guid mmsi3 = null;
            Integer sequenceNumber4 = null;
            Guid mmsi4 = null;

            _aisBinaryAcknowledgeMessage = new AisBinaryAcknowledgeMessageObject( ObjectState.New, AisBinaryAcknowledgeMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, spare, sequenceNumber1, mmsi1, sequenceNumber2, mmsi2, sequenceNumber3, mmsi3, sequenceNumber4, mmsi4 );
        }
        return _aisBinaryAcknowledgeMessage;
    }

    public AisBinaryAddressedMessageObject getAisBinaryAddressedMessage() {
        if (_aisBinaryAddressedMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int sequenceNumber = 0;
            Guid destinationMmsi = null;
            boolean retransmitFlag = false;
            int spare = 0;
            int designatedAreaCode = 0;
            int functionalId = 0;
            String data = "DataAisBinaryAddressedMessageUnitTest";

            _aisBinaryAddressedMessage = new AisBinaryAddressedMessageObject( ObjectState.New, AisBinaryAddressedMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, sequenceNumber, destinationMmsi, retransmitFlag, spare, designatedAreaCode, functionalId, data );
        }
        return _aisBinaryAddressedMessage;
    }

    public AisBinaryBroadcastMessageObject getAisBinaryBroadcastMessage() {
        if (_aisBinaryBroadcastMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int spare = 0;
            int designatedAreaCode = 0;
            int functionalId = 0;
            String data = "DataAisBinaryBroadcastMessageUnitTest";

            _aisBinaryBroadcastMessage = new AisBinaryBroadcastMessageObject( ObjectState.New, AisBinaryBroadcastMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, spare, designatedAreaCode, functionalId, data );
        }
        return _aisBinaryBroadcastMessage;
    }

    public AisDataLinkManagementMessageObject getAisDataLinkManagementMessage() {
        if (_aisDataLinkManagementMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int spare = 0;
            int offset1 = 0;
            int reservedSlots1 = 0;
            int timeout1 = 0;
            int increment1 = 0;
            Integer offset2 = null;
            Integer reservedSlots2 = null;
            Integer timeout2 = null;
            Integer increment2 = null;
            Integer offset3 = null;
            Integer reservedSlots3 = null;
            Integer timeout3 = null;
            Integer increment3 = null;
            Integer offset4 = null;
            Integer reservedSlots4 = null;
            Integer timeout4 = null;
            Integer increment4 = null;

            _aisDataLinkManagementMessage = new AisDataLinkManagementMessageObject( ObjectState.New, AisDataLinkManagementMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, spare, offset1, reservedSlots1, timeout1, increment1, offset2, reservedSlots2, timeout2, increment2, offset3, reservedSlots3, timeout3, increment3, offset4, reservedSlots4, timeout4, increment4 );
        }
        return _aisDataLinkManagementMessage;
    }

    public AisExtendedClassBCsPositionReportMessageObject getAisExtendedClassBCsPositionReportMessage() {
        if (_aisExtendedClassBCsPositionReportMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int reserved = 0;
            double speedOverGround = 0.0;
            int positionAccuracy = PositionAccuracy.Low;
            double longitude = 0.0;
            double latitude = 0.0;
            double courseOverGround = 0.0;
            Integer trueHeading = null;
            int timestamp = 0;
            int regionalReserved = 0;
            Guid name = null;
            int shipType = ShipType.NotAvailable;
            int dimensionToBow = 0;
            int dimensionToStern = 0;
            int dimensionToPort = 0;
            int dimensionToStarboard = 0;
            int positionFixType = PositionFixType.Undefined1;
            int raim = Raim.NotInUse;
            boolean dataTerminalReady = false;
            boolean assigned = false;
            int spare = 0;

            _aisExtendedClassBCsPositionReportMessage = new AisExtendedClassBCsPositionReportMessageObject( ObjectState.New, AisExtendedClassBCsPositionReportMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, reserved, speedOverGround, positionAccuracy, longitude, latitude, courseOverGround, trueHeading, timestamp, regionalReserved, name, shipType, dimensionToBow, dimensionToStern, dimensionToPort, dimensionToStarboard, positionFixType, raim, dataTerminalReady, assigned, spare );
        }
        return _aisExtendedClassBCsPositionReportMessage;
    }

    public AisInterrogationMessageObject getAisInterrogationMessage() {
        if (_aisInterrogationMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            Guid interrogatedMmsi = null;
            int firstMessageType = AisMessageType.PositionReportClassA;
            int firstSlotOffset = 0;
            Integer secondMessageType = AisMessageType.PositionReportClassA;
            Integer secondSlotOffset = null;
            Guid secondStationInterrogationMmsi = null;
            Integer secondStationFirstMessageType = AisMessageType.PositionReportClassA;
            Integer secondStationFirstSlotOffset = null;

            _aisInterrogationMessage = new AisInterrogationMessageObject( ObjectState.New, AisInterrogationMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, interrogatedMmsi, firstMessageType, firstSlotOffset, secondMessageType, secondSlotOffset, secondStationInterrogationMmsi, secondStationFirstMessageType, secondStationFirstSlotOffset );
        }
        return _aisInterrogationMessage;
    }

    public AisPositionReportClassAAssignedScheduleMessageObject getAisPositionReportClassAAssignedScheduleMessage() {
        if (_aisPositionReportClassAAssignedScheduleMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int navigationStatus = NavigationStatus.UnderWayUsingEngine;
            Integer rateOfTurn = null;
            double speedOverGround = 0.0;
            int positionAccuracy = PositionAccuracy.Low;
            double longitude = 0.0;
            double latitude = 0.0;
            double courseOverGround = 0.0;
            Integer trueHeading = null;
            int timestamp = 0;
            int maneuverIndicator = ManeuverIndicator.NotAvailable;
            int spare = 0;
            int raim = Raim.NotInUse;
            int radioStatus = 0;

            _aisPositionReportClassAAssignedScheduleMessage = new AisPositionReportClassAAssignedScheduleMessageObject( ObjectState.New, AisPositionReportClassAAssignedScheduleMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, navigationStatus, rateOfTurn, speedOverGround, positionAccuracy, longitude, latitude, courseOverGround, trueHeading, timestamp, maneuverIndicator, spare, raim, radioStatus );
        }
        return _aisPositionReportClassAAssignedScheduleMessage;
    }

    public AisPositionReportClassAMessageObject getAisPositionReportClassAMessage() {
        if (_aisPositionReportClassAMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int navigationStatus = NavigationStatus.UnderWayUsingEngine;
            Integer rateOfTurn = null;
            double speedOverGround = 0.0;
            int positionAccuracy = PositionAccuracy.Low;
            double longitude = 0.0;
            double latitude = 0.0;
            double courseOverGround = 0.0;
            Integer trueHeading = null;
            int timestamp = 0;
            int maneuverIndicator = ManeuverIndicator.NotAvailable;
            int spare = 0;
            int raim = Raim.NotInUse;
            int radioStatus = 0;

            _aisPositionReportClassAMessage = new AisPositionReportClassAMessageObject( ObjectState.New, AisPositionReportClassAMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, navigationStatus, rateOfTurn, speedOverGround, positionAccuracy, longitude, latitude, courseOverGround, trueHeading, timestamp, maneuverIndicator, spare, raim, radioStatus );
        }
        return _aisPositionReportClassAMessage;
    }

    public AisPositionReportClassAResponseToInterrogationMessageObject getAisPositionReportClassAResponseToInterrogationMessage() {
        if (_aisPositionReportClassAResponseToInterrogationMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int navigationStatus = NavigationStatus.UnderWayUsingEngine;
            Integer rateOfTurn = null;
            double speedOverGround = 0.0;
            int positionAccuracy = PositionAccuracy.Low;
            double longitude = 0.0;
            double latitude = 0.0;
            double courseOverGround = 0.0;
            Integer trueHeading = null;
            int timestamp = 0;
            int maneuverIndicator = ManeuverIndicator.NotAvailable;
            int spare = 0;
            int raim = Raim.NotInUse;
            int radioStatus = 0;

            _aisPositionReportClassAResponseToInterrogationMessage = new AisPositionReportClassAResponseToInterrogationMessageObject( ObjectState.New, AisPositionReportClassAResponseToInterrogationMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, navigationStatus, rateOfTurn, speedOverGround, positionAccuracy, longitude, latitude, courseOverGround, trueHeading, timestamp, maneuverIndicator, spare, raim, radioStatus );
        }
        return _aisPositionReportClassAResponseToInterrogationMessage;
    }

    public AisPositionReportForLongRangeApplicationsMessageObject getAisPositionReportForLongRangeApplicationsMessage() {
        if (_aisPositionReportForLongRangeApplicationsMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int positionAccuracy = PositionAccuracy.Low;
            int raim = Raim.NotInUse;
            int navigationStatus = NavigationStatus.UnderWayUsingEngine;
            double longitude = 0.0;
            double latitude = 0.0;
            double speedOverGround = 0.0;
            double courseOverGround = 0.0;
            int gnssPositionStatus = GnssPositionStatus.CurrentGnssPosition;
            int spare = 0;

            _aisPositionReportForLongRangeApplicationsMessage = new AisPositionReportForLongRangeApplicationsMessageObject( ObjectState.New, AisPositionReportForLongRangeApplicationsMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, positionAccuracy, raim, navigationStatus, longitude, latitude, speedOverGround, courseOverGround, gnssPositionStatus, spare );
        }
        return _aisPositionReportForLongRangeApplicationsMessage;
    }

    public AisSafetyRelatedAcknowledgmentMessageObject getAisSafetyRelatedAcknowledgmentMessage() {
        if (_aisSafetyRelatedAcknowledgmentMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int spare = 0;
            int sequenceNumber1 = 0;
            Guid mmsi1 = null;
            Integer sequenceNumber2 = null;
            Guid mmsi2 = null;
            Integer sequenceNumber3 = null;
            Guid mmsi3 = null;
            Integer sequenceNumber4 = null;
            Guid mmsi4 = null;

            _aisSafetyRelatedAcknowledgmentMessage = new AisSafetyRelatedAcknowledgmentMessageObject( ObjectState.New, AisSafetyRelatedAcknowledgmentMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, spare, sequenceNumber1, mmsi1, sequenceNumber2, mmsi2, sequenceNumber3, mmsi3, sequenceNumber4, mmsi4 );
        }
        return _aisSafetyRelatedAcknowledgmentMessage;
    }

    public AisStandardClassBCsPositionReportMessageObject getAisStandardClassBCsPositionReportMessage() {
        if (_aisStandardClassBCsPositionReportMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int reserved = 0;
            double speedOverGround = 0.0;
            int positionAccuracy = PositionAccuracy.Low;
            double longitude = 0.0;
            double latitude = 0.0;
            double courseOverGround = 0.0;
            Integer trueHeading = null;
            int timestamp = 0;
            int regionalReserved = 0;
            boolean isCsUnit = false;
            boolean hasDisplay = false;
            boolean hasDscCapability = false;
            boolean band = false;
            boolean canAcceptMessage22 = false;
            boolean assigned = false;
            int raim = Raim.NotInUse;
            int radioStatus = 0;

            _aisStandardClassBCsPositionReportMessage = new AisStandardClassBCsPositionReportMessageObject( ObjectState.New, AisStandardClassBCsPositionReportMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, reserved, speedOverGround, positionAccuracy, longitude, latitude, courseOverGround, trueHeading, timestamp, regionalReserved, isCsUnit, hasDisplay, hasDscCapability, band, canAcceptMessage22, assigned, raim, radioStatus );
        }
        return _aisStandardClassBCsPositionReportMessage;
    }

    public AisStandardSarAircraftPositionReportMessageObject getAisStandardSarAircraftPositionReportMessage() {
        if (_aisStandardSarAircraftPositionReportMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int altitude = 0;
            int speedOverGround = 0;
            int positionAccuracy = PositionAccuracy.Low;
            double longitude = 0.0;
            double latitude = 0.0;
            double courseOverGround = 0.0;
            int timestamp = 0;
            int reserved = 0;
            boolean dataTerminalReady = false;
            int spare = 0;
            boolean assigned = false;
            int raim = Raim.NotInUse;
            int radioStatus = 0;

            _aisStandardSarAircraftPositionReportMessage = new AisStandardSarAircraftPositionReportMessageObject( ObjectState.New, AisStandardSarAircraftPositionReportMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, altitude, speedOverGround, positionAccuracy, longitude, latitude, courseOverGround, timestamp, reserved, dataTerminalReady, spare, assigned, raim, radioStatus );
        }
        return _aisStandardSarAircraftPositionReportMessage;
    }

    public AisStaticAndVoyageRelatedDataMessageObject getAisStaticAndVoyageRelatedDataMessage() {
        if (_aisStaticAndVoyageRelatedDataMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int aisVersion = 0;
            Guid imoNumber = null;
            Guid callsign = null;
            Guid shipName = null;
            int shipType = ShipType.NotAvailable;
            int dimensionToBow = 0;
            int dimensionToStern = 0;
            int dimensionToPort = 0;
            int dimensionToStarboard = 0;
            int positionFixType = PositionFixType.Undefined1;
            DateTime estimatedTimeOfArrival = null;
            double draught = 0.0;
            String destination = "DestinationAisStaticAndVoyageRelatedDataMessageUnitTest";
            boolean dataTerminalReady = false;
            int spare = 0;

            _aisStaticAndVoyageRelatedDataMessage = new AisStaticAndVoyageRelatedDataMessageObject( ObjectState.New, AisStaticAndVoyageRelatedDataMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, aisVersion, imoNumber, callsign, shipName, shipType, dimensionToBow, dimensionToStern, dimensionToPort, dimensionToStarboard, positionFixType, estimatedTimeOfArrival, draught, destination, dataTerminalReady, spare );
        }
        return _aisStaticAndVoyageRelatedDataMessage;
    }

    public AisStaticDataReportMessageObject getAisStaticDataReportMessage() {
        if (_aisStaticDataReportMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int partNumber = 0;

            _aisStaticDataReportMessage = new AisStaticDataReportMessageObject( ObjectState.New, AisStaticDataReportMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, partNumber );
        }
        return _aisStaticDataReportMessage;
    }

    public AisStaticDataReportPartAMessageObject getAisStaticDataReportPartAMessage() {
        if (_aisStaticDataReportPartAMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int partNumber = 0;
            Guid shipName = null;
            int spare = 0;

            _aisStaticDataReportPartAMessage = new AisStaticDataReportPartAMessageObject( ObjectState.New, AisStaticDataReportPartAMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, partNumber, shipName, spare );
        }
        return _aisStaticDataReportPartAMessage;
    }

    public AisStaticDataReportPartBMessageObject getAisStaticDataReportPartBMessage() {
        if (_aisStaticDataReportPartBMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int partNumber = 0;
            int shipType = ShipType.NotAvailable;
            String vendorId = "VendorIdAisStaticDataReportPartBMessageUnitTest";
            int unitModelCode = 0;
            int serialNumber = 0;
            Guid callsign = null;
            int dimensionToBow = 0;
            int dimensionToStern = 0;
            int dimensionToPort = 0;
            int dimensionToStarboard = 0;
            Guid mothershipMmsi = null;
            int positionFixType = PositionFixType.Undefined1;
            int spare = 0;

            _aisStaticDataReportPartBMessage = new AisStaticDataReportPartBMessageObject( ObjectState.New, AisStaticDataReportPartBMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, partNumber, shipType, vendorId, unitModelCode, serialNumber, callsign, dimensionToBow, dimensionToStern, dimensionToPort, dimensionToStarboard, mothershipMmsi, positionFixType, spare );
        }
        return _aisStaticDataReportPartBMessage;
    }

    public AisUtcAndDateInquiryMessageObject getAisUtcAndDateInquiryMessage() {
        if (_aisUtcAndDateInquiryMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            int spare1 = 0;
            Guid destinationMmsi = null;
            int spare2 = 0;

            _aisUtcAndDateInquiryMessage = new AisUtcAndDateInquiryMessageObject( ObjectState.New, AisUtcAndDateInquiryMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, spare1, destinationMmsi, spare2 );
        }
        return _aisUtcAndDateInquiryMessage;
    }

    public AisUtcAndDateResponseMessageObject getAisUtcAndDateResponseMessage() {
        if (_aisUtcAndDateResponseMessage == null) {
            long rowVersion = 0;
            Guid aisDevice = AisDevicePrimaryKey;
            DateTime receivedTimestamp = new DateTime(2025,10,18,9,0,0);
            long messageSequenceNumber = 0;
            int repeat = 0;
            Guid mmsi = null;
            DateTime datetime = new DateTime(2025,10,18,9,0,0);
            int positionAccuracy = PositionAccuracy.Low;
            double longitude = 0.0;
            double latitude = 0.0;
            int positionFixType = PositionFixType.Undefined1;
            int spare = 0;
            int raim = Raim.NotInUse;
            int radioStatus = 0;

            _aisUtcAndDateResponseMessage = new AisUtcAndDateResponseMessageObject( ObjectState.New, AisUtcAndDateResponseMessagePrimaryKey, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, datetime, positionAccuracy, longitude, latitude, positionFixType, spare, raim, radioStatus );
        }
        return _aisUtcAndDateResponseMessage;
    }

    public AlarmStateChangeObject getAlarmStateChange() {
        if (_alarmStateChange == null) {
            long rowVersion = 0;
            Guid alarm = ZoneTrackAlarmPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int state = AlarmState.Unknown;

            _alarmStateChange = new AlarmStateChangeObject( ObjectState.New, AlarmStateChangePrimaryKey, rowVersion, alarm, timestamp, state );
        }
        return _alarmStateChange;
    }

    public BaseStationTypeObject getBaseStationType() {
        if (_baseStationType == null) {
            long rowVersion = 0;
            String name = "NameBaseStationTypeUnitTest";

            _baseStationType = new BaseStationTypeObject( ObjectState.New, BaseStationTypePrimaryKey, rowVersion, name );
        }
        return _baseStationType;
    }

    public BinaryTimeseriesValueObject getBinaryTimeseriesValue() {
        if (_binaryTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = BinaryTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            byte[] value = new byte[0];

            _binaryTimeseriesValue = new BinaryTimeseriesValueObject( ObjectState.New, BinaryTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _binaryTimeseriesValue;
    }

    public BookmarkObject getBookmark() {
        if (_bookmark == null) {
            long rowVersion = 0;
            Guid view = ViewPrimaryKey;
            String name = "NameBookmarkUnitTest";
            DateTime timestamp = null;
            double latitude = 0.0;
            double longitude = 0.0;
            double zoomLevel = 0.0;

            _bookmark = new BookmarkObject( ObjectState.New, BookmarkPrimaryKey, rowVersion, view, name, timestamp, latitude, longitude, zoomLevel );
        }
        return _bookmark;
    }

    public BooleanTimeseriesValueObject getBooleanTimeseriesValue() {
        if (_booleanTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = BooleanTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Boolean value = null;

            _booleanTimeseriesValue = new BooleanTimeseriesValueObject( ObjectState.New, BooleanTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _booleanTimeseriesValue;
    }

    public ByteTimeseriesValueObject getByteTimeseriesValue() {
        if (_byteTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = ByteTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Byte value = null;

            _byteTimeseriesValue = new ByteTimeseriesValueObject( ObjectState.New, ByteTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _byteTimeseriesValue;
    }

    public CameraCommandObject getCameraCommand() {
        if (_cameraCommand == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _cameraCommand = new CameraCommandObject( ObjectState.New, CameraCommandPrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _cameraCommand;
    }

    public CameraCommandAbsoluteMoveObject getCameraCommandAbsoluteMove() {
        if (_cameraCommandAbsoluteMove == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            int positionPanTiltMode = CameraPanTiltMode.Unknown;
            Double panAngle = null;
            Double tiltAngle = null;
            int positionFocalLengthMode = CameraFocalLengthMode.Unknown;
            Double focalLength = null;
            int speedPanTiltMode = CameraPanTiltMode.Unknown;
            Double panSpeed = null;
            Double tiltSpeed = null;
            int speedFocalLengthMode = CameraFocalLengthMode.Unknown;
            Double zoomSpeed = null;

            _cameraCommandAbsoluteMove = new CameraCommandAbsoluteMoveObject( ObjectState.New, CameraCommandAbsoluteMovePrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, positionPanTiltMode, panAngle, tiltAngle, positionFocalLengthMode, focalLength, speedPanTiltMode, panSpeed, tiltSpeed, speedFocalLengthMode, zoomSpeed );
        }
        return _cameraCommandAbsoluteMove;
    }

    public CameraCommandAdjustPanTiltZoomObject getCameraCommandAdjustPanTiltZoom() {
        if (_cameraCommandAdjustPanTiltZoom == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            Double x = null;
            Double y = null;
            Double z = null;

            _cameraCommandAdjustPanTiltZoom = new CameraCommandAdjustPanTiltZoomObject( ObjectState.New, CameraCommandAdjustPanTiltZoomPrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, x, y, z );
        }
        return _cameraCommandAdjustPanTiltZoom;
    }

    public CameraCommandContinuousMoveObject getCameraCommandContinuousMove() {
        if (_cameraCommandContinuousMove == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            boolean normalized = false;
            Double panVelocity = null;
            Double tiltVelocity = null;
            Double zoomVelocity = null;
            TimeSpan duration = null;

            _cameraCommandContinuousMove = new CameraCommandContinuousMoveObject( ObjectState.New, CameraCommandContinuousMovePrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, normalized, panVelocity, tiltVelocity, zoomVelocity, duration );
        }
        return _cameraCommandContinuousMove;
    }

    public CameraCommandGeoMoveObject getCameraCommandGeoMove() {
        if (_cameraCommandGeoMove == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            double latitude = 0.0;
            double longitude = 0.0;
            Double altitude = null;
            Double viewportWidth = null;
            Double viewportHeight = null;

            _cameraCommandGeoMove = new CameraCommandGeoMoveObject( ObjectState.New, CameraCommandGeoMovePrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, latitude, longitude, altitude, viewportWidth, viewportHeight );
        }
        return _cameraCommandGeoMove;
    }

    public CameraCommandRelativeMoveObject getCameraCommandRelativeMove() {
        if (_cameraCommandRelativeMove == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            boolean normalized = false;
            Double panAngle = null;
            Double tiltAngle = null;
            Double focalLength = null;
            Double panSpeed = null;
            Double tiltSpeed = null;
            Double zoomSpeed = null;

            _cameraCommandRelativeMove = new CameraCommandRelativeMoveObject( ObjectState.New, CameraCommandRelativeMovePrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, normalized, panAngle, tiltAngle, focalLength, panSpeed, tiltSpeed, zoomSpeed );
        }
        return _cameraCommandRelativeMove;
    }

    public CameraCommandReleasePTZOwnershipObject getCameraCommandReleasePTZOwnership() {
        if (_cameraCommandReleasePTZOwnership == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _cameraCommandReleasePTZOwnership = new CameraCommandReleasePTZOwnershipObject( ObjectState.New, CameraCommandReleasePTZOwnershipPrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _cameraCommandReleasePTZOwnership;
    }

    public CameraCommandRequestPTZOwnershipObject getCameraCommandRequestPTZOwnership() {
        if (_cameraCommandRequestPTZOwnership == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _cameraCommandRequestPTZOwnership = new CameraCommandRequestPTZOwnershipObject( ObjectState.New, CameraCommandRequestPTZOwnershipPrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _cameraCommandRequestPTZOwnership;
    }

    public CameraCommandSetAutoFocusObject getCameraCommandSetAutoFocus() {
        if (_cameraCommandSetAutoFocus == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            boolean enabled = false;

            _cameraCommandSetAutoFocus = new CameraCommandSetAutoFocusObject( ObjectState.New, CameraCommandSetAutoFocusPrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, enabled );
        }
        return _cameraCommandSetAutoFocus;
    }

    public CameraCommandSetBlackAndWhiteObject getCameraCommandSetBlackAndWhite() {
        if (_cameraCommandSetBlackAndWhite == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            boolean enabled = false;

            _cameraCommandSetBlackAndWhite = new CameraCommandSetBlackAndWhiteObject( ObjectState.New, CameraCommandSetBlackAndWhitePrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, enabled );
        }
        return _cameraCommandSetBlackAndWhite;
    }

    public CameraCommandSetFollowedObject getCameraCommandSetFollowed() {
        if (_cameraCommandSetFollowed == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            Guid trackId = new Guid();
            int reason = CameraFollowReason.Alarm;

            _cameraCommandSetFollowed = new CameraCommandSetFollowedObject( ObjectState.New, CameraCommandSetFollowedPrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, trackId, reason );
        }
        return _cameraCommandSetFollowed;
    }

    public CameraCommandSetInfraRedLampObject getCameraCommandSetInfraRedLamp() {
        if (_cameraCommandSetInfraRedLamp == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            boolean enabled = false;

            _cameraCommandSetInfraRedLamp = new CameraCommandSetInfraRedLampObject( ObjectState.New, CameraCommandSetInfraRedLampPrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, enabled );
        }
        return _cameraCommandSetInfraRedLamp;
    }

    public CameraCommandSetWasherObject getCameraCommandSetWasher() {
        if (_cameraCommandSetWasher == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            boolean enabled = false;

            _cameraCommandSetWasher = new CameraCommandSetWasherObject( ObjectState.New, CameraCommandSetWasherPrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, enabled );
        }
        return _cameraCommandSetWasher;
    }

    public CameraCommandSetWiperObject getCameraCommandSetWiper() {
        if (_cameraCommandSetWiper == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            boolean enabled = false;

            _cameraCommandSetWiper = new CameraCommandSetWiperObject( ObjectState.New, CameraCommandSetWiperPrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, enabled );
        }
        return _cameraCommandSetWiper;
    }

    public CameraCommandStopObject getCameraCommandStop() {
        if (_cameraCommandStop == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;
            boolean panTilt = false;
            boolean zoom = false;

            _cameraCommandStop = new CameraCommandStopObject( ObjectState.New, CameraCommandStopPrimaryKey, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply, panTilt, zoom );
        }
        return _cameraCommandStop;
    }

    public CameraCommandReplyObject getCameraCommandReply() {
        if (_cameraCommandReply == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageCameraCommandReplyUnitTest";
            double panAngle = 0.0;
            double tiltAngle = 0.0;
            double focalLength = 0.0;

            _cameraCommandReply = new CameraCommandReplyObject( ObjectState.New, CameraCommandReplyPrimaryKey, rowVersion, camera, timestamp, command, status, message, panAngle, tiltAngle, focalLength );
        }
        return _cameraCommandReply;
    }

    public CameraConfigurationObject getCameraConfiguration() {
        if (_cameraConfiguration == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int cameraControlProtocol = CameraControlProtocol.Unknown;
            String cameraURL = "CameraURLCameraConfigurationUnitTest";
            String configurationURL = "ConfigurationURLCameraConfigurationUnitTest";
            String userName = "UserNameCameraConfigurationUnitTest";
            String password = "PasswordCameraConfigurationUnitTest";
            boolean useRtspUriOverride = false;
            String rtspUriOverride = "RtspUriOverrideCameraConfigurationUnitTest";
            double latitude = 0.0;
            double longitude = 0.0;
            double altitude = 0.0;
            boolean useRelativePosition = false;
            int panTiltMode = CameraPanTiltMode.Unknown;
            double minTiltAngle = 0.0;
            double maxTiltAngle = 0.0;
            double minTiltScaleAngle = 0.0;
            double maxTiltScaleAngle = 0.0;
            boolean useReverseTiltAngle = false;
            boolean useReverseNormalizedTiltAngle = false;
            double minTiltVelocity = 0.0;
            double maxTiltVelocity = 0.0;
            double minTiltSpeed = 0.0;
            double maxTiltSpeed = 0.0;
            double minPanAngle = 0.0;
            double maxPanAngle = 0.0;
            double minPanScaleAngle = 0.0;
            double maxPanScaleAngle = 0.0;
            boolean useReversePanAngle = false;
            boolean useReverseNormalizedPanAngle = false;
            double minPanVelocity = 0.0;
            double maxPanVelocity = 0.0;
            double minPanSpeed = 0.0;
            double maxPanSpeed = 0.0;
            int focalLengthMode = CameraFocalLengthMode.Unknown;
            double minFocalLength = 0.0;
            double maxFocalLength = 0.0;
            double minFocalLengthScale = 0.0;
            double maxFocalLengthScale = 0.0;
            double minZoomVelocity = 0.0;
            double maxZoomVelocity = 0.0;
            double minZoomSpeed = 0.0;
            double maxZoomSpeed = 0.0;
            double imageSensorWidth = 0.0;
            double imageSensorHeight = 0.0;
            double homePanAngle = 0.0;
            double homeTiltAngle = 0.0;
            double homeFocalLength = 0.0;
            double panOffset = 0.0;
            double tiltOffset = 0.0;
            double aimAltitude = 0.0;
            double minimumTargetWidth = 0.0;
            TimeSpan targetLockTimeout = new TimeSpan();
            TimeSpan updateStatusInterval = new TimeSpan();
            TimeSpan readTimeout = new TimeSpan();
            TimeSpan moveCommandStatusDelay = new TimeSpan();
            String ptzProfileName = "PtzProfileNameCameraConfigurationUnitTest";
            String ptzConfigurationToken = "PtzConfigurationTokenCameraConfigurationUnitTest";
            String videoSourceToken = "VideoSourceTokenCameraConfigurationUnitTest";

            _cameraConfiguration = new CameraConfigurationObject( ObjectState.New, CameraConfigurationPrimaryKey, rowVersion, camera, timestamp, cameraControlProtocol, cameraURL, configurationURL, userName, password, useRtspUriOverride, rtspUriOverride, latitude, longitude, altitude, useRelativePosition, panTiltMode, minTiltAngle, maxTiltAngle, minTiltScaleAngle, maxTiltScaleAngle, useReverseTiltAngle, useReverseNormalizedTiltAngle, minTiltVelocity, maxTiltVelocity, minTiltSpeed, maxTiltSpeed, minPanAngle, maxPanAngle, minPanScaleAngle, maxPanScaleAngle, useReversePanAngle, useReverseNormalizedPanAngle, minPanVelocity, maxPanVelocity, minPanSpeed, maxPanSpeed, focalLengthMode, minFocalLength, maxFocalLength, minFocalLengthScale, maxFocalLengthScale, minZoomVelocity, maxZoomVelocity, minZoomSpeed, maxZoomSpeed, imageSensorWidth, imageSensorHeight, homePanAngle, homeTiltAngle, homeFocalLength, panOffset, tiltOffset, aimAltitude, minimumTargetWidth, targetLockTimeout, updateStatusInterval, readTimeout, moveCommandStatusDelay, ptzProfileName, ptzConfigurationToken, videoSourceToken );
        }
        return _cameraConfiguration;
    }

    public CameraPanCalibrationObject getCameraPanCalibration() {
        if (_cameraPanCalibration == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);

            _cameraPanCalibration = new CameraPanCalibrationObject( ObjectState.New, CameraPanCalibrationPrimaryKey, rowVersion, camera, timestamp );
        }
        return _cameraPanCalibration;
    }

    public CameraPanCalibrationValueObject getCameraPanCalibrationValue() {
        if (_cameraPanCalibrationValue == null) {
            long rowVersion = 0;
            Guid panCalibration = CameraPanCalibrationPrimaryKey;
            double panAngle = 0.0;
            double panOffset = 0.0;

            _cameraPanCalibrationValue = new CameraPanCalibrationValueObject( ObjectState.New, CameraPanCalibrationValuePrimaryKey, rowVersion, panCalibration, panAngle, panOffset );
        }
        return _cameraPanCalibrationValue;
    }

    public CameraStatusObject getCameraStatus() {
        if (_cameraStatus == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            Guid track = null;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int positionPanTiltMode = CameraPanTiltMode.Unknown;
            double panAngle = 0.0;
            double tiltAngle = 0.0;
            int positionFocalLengthMode = CameraFocalLengthMode.Unknown;
            double focalLength = 0.0;
            int panTiltMoveStatus = CameraMoveStatus.Unknown;
            int zoomMoveStatus = CameraMoveStatus.Unknown;
            int velocityPanTiltMode = CameraPanTiltMode.Unknown;
            Double panVelocity = null;
            Double tiltVelocity = null;
            int velocityFocalLengthMode = CameraFocalLengthMode.Unknown;
            Double zoomVelocity = null;
            int activeFeatures = CameraFeatures.None;
            String error = "ErrorCameraStatusUnitTest";

            _cameraStatus = new CameraStatusObject( ObjectState.New, CameraStatusPrimaryKey, rowVersion, camera, track, timestamp, positionPanTiltMode, panAngle, tiltAngle, positionFocalLengthMode, focalLength, panTiltMoveStatus, zoomMoveStatus, velocityPanTiltMode, panVelocity, tiltVelocity, velocityFocalLengthMode, zoomVelocity, activeFeatures, error );
        }
        return _cameraStatus;
    }

    public CameraTiltCalibrationObject getCameraTiltCalibration() {
        if (_cameraTiltCalibration == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);

            _cameraTiltCalibration = new CameraTiltCalibrationObject( ObjectState.New, CameraTiltCalibrationPrimaryKey, rowVersion, camera, timestamp );
        }
        return _cameraTiltCalibration;
    }

    public CameraTiltCalibrationValueObject getCameraTiltCalibrationValue() {
        if (_cameraTiltCalibrationValue == null) {
            long rowVersion = 0;
            Guid tiltCalibration = CameraTiltCalibrationPrimaryKey;
            double panAngle = 0.0;
            double tiltOffset = 0.0;

            _cameraTiltCalibrationValue = new CameraTiltCalibrationValueObject( ObjectState.New, CameraTiltCalibrationValuePrimaryKey, rowVersion, tiltCalibration, panAngle, tiltOffset );
        }
        return _cameraTiltCalibrationValue;
    }

    public CameraZoomCalibrationObject getCameraZoomCalibration() {
        if (_cameraZoomCalibration == null) {
            long rowVersion = 0;
            Guid camera = CameraDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);

            _cameraZoomCalibration = new CameraZoomCalibrationObject( ObjectState.New, CameraZoomCalibrationPrimaryKey, rowVersion, camera, timestamp );
        }
        return _cameraZoomCalibration;
    }

    public CameraZoomCalibrationValueObject getCameraZoomCalibrationValue() {
        if (_cameraZoomCalibrationValue == null) {
            long rowVersion = 0;
            Guid zoomCalibration = CameraZoomCalibrationPrimaryKey;
            double focalLength = 0.0;
            double focalLengthOffset = 0.0;

            _cameraZoomCalibrationValue = new CameraZoomCalibrationValueObject( ObjectState.New, CameraZoomCalibrationValuePrimaryKey, rowVersion, zoomCalibration, focalLength, focalLengthOffset );
        }
        return _cameraZoomCalibrationValue;
    }

    public CatalogObject getCatalog() {
        if (_catalog == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameCatalogUnitTest";

            _catalog = new CatalogObject( ObjectState.New, CatalogPrimaryKey, rowVersion, catalog, name );
        }
        return _catalog;
    }

    public ElementObject getElement() {
        if (_element == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameElementUnitTest";
            Guid elementType = null;

            _element = new ElementObject( ObjectState.New, ElementPrimaryKey, rowVersion, catalog, name, elementType );
        }
        return _element;
    }

    public CollectionInfoObject getCollectionInfo() {
        if (_collectionInfo == null) {
            long rowVersion = 0;
            long count = 0;

            _collectionInfo = new CollectionInfoObject( ObjectState.New, CollectionInfoPrimaryKey, rowVersion, count );
        }
        return _collectionInfo;
    }

    public CountryObject getCountry() {
        if (_country == null) {
            long rowVersion = 0;
            String name = "NameCountryUnitTest";
            int code = 0;
            String alpha2 = "";
            String alpha3 = "A";

            _country = new CountryObject( ObjectState.New, CountryPrimaryKey, rowVersion, name, code, alpha2, alpha3 );
        }
        return _country;
    }

    public CursorInfoObject getCursorInfo() {
        if (_cursorInfo == null) {
            long rowVersion = 0;
            int typeCode = 0;

            _cursorInfo = new CursorInfoObject( ObjectState.New, CursorInfoPrimaryKey, rowVersion, typeCode );
        }
        return _cursorInfo;
    }

    public DateTimeTimeseriesValueObject getDateTimeTimeseriesValue() {
        if (_dateTimeTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = DateTimeTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            DateTime value = null;

            _dateTimeTimeseriesValue = new DateTimeTimeseriesValueObject( ObjectState.New, DateTimeTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _dateTimeTimeseriesValue;
    }

    public DeviceHostObject getDeviceHost() {
        if (_deviceHost == null) {
            long rowVersion = 0;
            String name = "NameDeviceHostUnitTest";

            _deviceHost = new DeviceHostObject( ObjectState.New, DeviceHostPrimaryKey, rowVersion, name );
        }
        return _deviceHost;
    }

    public DeviceHostConfigurationObject getDeviceHostConfiguration() {
        if (_deviceHostConfiguration == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            String hostname = "HostnameDeviceHostConfigurationUnitTest";
            int port = 0;
            String queueName = "QueueNameDeviceHostConfigurationUnitTest";

            _deviceHostConfiguration = new DeviceHostConfigurationObject( ObjectState.New, DeviceHostConfigurationPrimaryKey, rowVersion, host, timestamp, hostname, port, queueName );
        }
        return _deviceHostConfiguration;
    }

    public DoubleTimeseriesValueObject getDoubleTimeseriesValue() {
        if (_doubleTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = DoubleTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Double value = null;

            _doubleTimeseriesValue = new DoubleTimeseriesValueObject( ObjectState.New, DoubleTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _doubleTimeseriesValue;
    }

    public FacilityTypeObject getFacilityType() {
        if (_facilityType == null) {
            long rowVersion = 0;
            String name = "NameFacilityTypeUnitTest";

            _facilityType = new FacilityTypeObject( ObjectState.New, FacilityTypePrimaryKey, rowVersion, name );
        }
        return _facilityType;
    }

    public GeoPosition2DTimeseriesValueObject getGeoPosition2DTimeseriesValue() {
        if (_geoPosition2DTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = GeoPosition2DTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Double latitude = null;
            Double longitude = null;

            _geoPosition2DTimeseriesValue = new GeoPosition2DTimeseriesValueObject( ObjectState.New, GeoPosition2DTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, latitude, longitude );
        }
        return _geoPosition2DTimeseriesValue;
    }

    public GeoPosition3DTimeseriesValueObject getGeoPosition3DTimeseriesValue() {
        if (_geoPosition3DTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = GeoPosition3DTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Double latitude = null;
            Double longitude = null;
            Double altitude = null;

            _geoPosition3DTimeseriesValue = new GeoPosition3DTimeseriesValueObject( ObjectState.New, GeoPosition3DTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, latitude, longitude, altitude );
        }
        return _geoPosition3DTimeseriesValue;
    }

    public GNSSDeviceCommandObject getGNSSDeviceCommand() {
        if (_gNSSDeviceCommand == null) {
            long rowVersion = 0;
            Guid gNSSDevice = GNSSDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _gNSSDeviceCommand = new GNSSDeviceCommandObject( ObjectState.New, GNSSDeviceCommandPrimaryKey, rowVersion, gNSSDevice, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _gNSSDeviceCommand;
    }

    public GNSSDeviceCommandReplyObject getGNSSDeviceCommandReply() {
        if (_gNSSDeviceCommandReply == null) {
            long rowVersion = 0;
            Guid gNSSDevice = GNSSDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageGNSSDeviceCommandReplyUnitTest";

            _gNSSDeviceCommandReply = new GNSSDeviceCommandReplyObject( ObjectState.New, GNSSDeviceCommandReplyPrimaryKey, rowVersion, gNSSDevice, timestamp, command, status, message );
        }
        return _gNSSDeviceCommandReply;
    }

    public GNSSDeviceConfigurationObject getGNSSDeviceConfiguration() {
        if (_gNSSDeviceConfiguration == null) {
            long rowVersion = 0;
            Guid gNSSDevice = GNSSDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            double defaultLatitude = 0.0;
            double defaultLongitude = 0.0;
            double defaultAltitude = 0.0;
            double latitudeOffset = 0.0;
            double longitudeOffset = 0.0;
            double altitudeOffset = 0.0;

            _gNSSDeviceConfiguration = new GNSSDeviceConfigurationObject( ObjectState.New, GNSSDeviceConfigurationPrimaryKey, rowVersion, gNSSDevice, timestamp, defaultLatitude, defaultLongitude, defaultAltitude, latitudeOffset, longitudeOffset, altitudeOffset );
        }
        return _gNSSDeviceConfiguration;
    }

    public GuidTimeseriesValueObject getGuidTimeseriesValue() {
        if (_guidTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = GuidTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid value = null;

            _guidTimeseriesValue = new GuidTimeseriesValueObject( ObjectState.New, GuidTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _guidTimeseriesValue;
    }

    public GyroDeviceCommandObject getGyroDeviceCommand() {
        if (_gyroDeviceCommand == null) {
            long rowVersion = 0;
            Guid gyroDevice = GyroDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _gyroDeviceCommand = new GyroDeviceCommandObject( ObjectState.New, GyroDeviceCommandPrimaryKey, rowVersion, gyroDevice, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _gyroDeviceCommand;
    }

    public GyroDeviceCommandReplyObject getGyroDeviceCommandReply() {
        if (_gyroDeviceCommandReply == null) {
            long rowVersion = 0;
            Guid gyroDevice = GyroDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageGyroDeviceCommandReplyUnitTest";

            _gyroDeviceCommandReply = new GyroDeviceCommandReplyObject( ObjectState.New, GyroDeviceCommandReplyPrimaryKey, rowVersion, gyroDevice, timestamp, command, status, message );
        }
        return _gyroDeviceCommandReply;
    }

    public GyroDeviceConfigurationObject getGyroDeviceConfiguration() {
        if (_gyroDeviceConfiguration == null) {
            long rowVersion = 0;
            Guid gyroDevice = GyroDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            double defaultHeadingTrueNorth = 0.0;
            double defaultMagneticTrueNorth = 0.0;
            double headingTrueNorthOffset = 0.0;
            double headingMagneticNorthOffset = 0.0;
            String pitchTransducerName = "PitchTransducerNameGyroDeviceConfigurationUnitTest";
            String rollTransducerName = "RollTransducerNameGyroDeviceConfigurationUnitTest";

            _gyroDeviceConfiguration = new GyroDeviceConfigurationObject( ObjectState.New, GyroDeviceConfigurationPrimaryKey, rowVersion, gyroDevice, timestamp, defaultHeadingTrueNorth, defaultMagneticTrueNorth, headingTrueNorthOffset, headingMagneticNorthOffset, pitchTransducerName, rollTransducerName );
        }
        return _gyroDeviceConfiguration;
    }

    public CallsignObject getCallsign() {
        if (_callsign == null) {
            long rowVersion = 0;
            String identifier = "IdentifierCallsignUnitTest";

            _callsign = new CallsignObject( ObjectState.New, CallsignPrimaryKey, rowVersion, identifier );
        }
        return _callsign;
    }

    public InternationalMaritimeOrganizationNumberObject getInternationalMaritimeOrganizationNumber() {
        if (_internationalMaritimeOrganizationNumber == null) {
            long rowVersion = 0;
            long identifier = 0;

            _internationalMaritimeOrganizationNumber = new InternationalMaritimeOrganizationNumberObject( ObjectState.New, InternationalMaritimeOrganizationNumberPrimaryKey, rowVersion, identifier );
        }
        return _internationalMaritimeOrganizationNumber;
    }

    public MaritimeMobileServiceIdentityObject getMaritimeMobileServiceIdentity() {
        if (_maritimeMobileServiceIdentity == null) {
            long rowVersion = 0;
            long identifier = 0;

            _maritimeMobileServiceIdentity = new MaritimeMobileServiceIdentityObject( ObjectState.New, MaritimeMobileServiceIdentityPrimaryKey, rowVersion, identifier );
        }
        return _maritimeMobileServiceIdentity;
    }

    public NameObject getName() {
        if (_name == null) {
            long rowVersion = 0;
            String text = "TextNameUnitTest";

            _name = new NameObject( ObjectState.New, NamePrimaryKey, rowVersion, text );
        }
        return _name;
    }

    public Int16TimeseriesValueObject getInt16TimeseriesValue() {
        if (_int16TimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = Int16TimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Short value = null;

            _int16TimeseriesValue = new Int16TimeseriesValueObject( ObjectState.New, Int16TimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _int16TimeseriesValue;
    }

    public Int32TimeseriesValueObject getInt32TimeseriesValue() {
        if (_int32TimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = Int32TimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Integer value = null;

            _int32TimeseriesValue = new Int32TimeseriesValueObject( ObjectState.New, Int32TimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _int32TimeseriesValue;
    }

    public Int64TimeseriesValueObject getInt64TimeseriesValue() {
        if (_int64TimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = Int64TimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Long value = null;

            _int64TimeseriesValue = new Int64TimeseriesValueObject( ObjectState.New, Int64TimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _int64TimeseriesValue;
    }

    public BaseStationObject getBaseStation() {
        if (_baseStation == null) {
            long rowVersion = 0;
            String name = "NameBaseStationUnitTest";
            Guid type = null;

            _baseStation = new BaseStationObject( ObjectState.New, BaseStationPrimaryKey, rowVersion, name, type );
        }
        return _baseStation;
    }

    public CameraDeviceObject getCameraDevice() {
        if (_cameraDevice == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            String name = "NameCameraDeviceUnitTest";
            String description = "DescriptionCameraDeviceUnitTest";
            Guid enabledTimeseries = null;

            _cameraDevice = new CameraDeviceObject( ObjectState.New, CameraDevicePrimaryKey, rowVersion, host, name, description, enabledTimeseries );
        }
        return _cameraDevice;
    }

    public GNSSDeviceObject getGNSSDevice() {
        if (_gNSSDevice == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            String name = "NameGNSSDeviceUnitTest";
            String description = "DescriptionGNSSDeviceUnitTest";
            Guid enabledTimeseries = null;
            Guid latitudeTimeseries = null;
            Guid longitudeTimeseries = null;
            Guid altitudeTimeseries = null;

            _gNSSDevice = new GNSSDeviceObject( ObjectState.New, GNSSDevicePrimaryKey, rowVersion, host, name, description, enabledTimeseries, latitudeTimeseries, longitudeTimeseries, altitudeTimeseries );
        }
        return _gNSSDevice;
    }

    public GyroDeviceObject getGyroDevice() {
        if (_gyroDevice == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            String name = "NameGyroDeviceUnitTest";
            String description = "DescriptionGyroDeviceUnitTest";
            Guid enabledTimeseries = null;
            Guid headingTrueNorthTimeseries = null;
            Guid headingMagneticNorthTimeseries = null;
            Guid pitchTimeseries = null;
            Guid rateOfTurnTimeseries = null;
            Guid rollTimeseries = null;
            Guid courseTimeseries = null;
            Guid speedTimeseries = null;
            Guid gNSSDevice = null;

            _gyroDevice = new GyroDeviceObject( ObjectState.New, GyroDevicePrimaryKey, rowVersion, host, name, description, enabledTimeseries, headingTrueNorthTimeseries, headingMagneticNorthTimeseries, pitchTimeseries, rateOfTurnTimeseries, rollTimeseries, courseTimeseries, speedTimeseries, gNSSDevice );
        }
        return _gyroDevice;
    }

    public LineInputDeviceObject getLineInputDevice() {
        if (_lineInputDevice == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            String name = "NameLineInputDeviceUnitTest";
            String description = "DescriptionLineInputDeviceUnitTest";
            Guid enabledTimeseries = null;

            _lineInputDevice = new LineInputDeviceObject( ObjectState.New, LineInputDevicePrimaryKey, rowVersion, host, name, description, enabledTimeseries );
        }
        return _lineInputDevice;
    }

    public OilSpillDetectorDeviceObject getOilSpillDetectorDevice() {
        if (_oilSpillDetectorDevice == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            String name = "NameOilSpillDetectorDeviceUnitTest";
            String description = "DescriptionOilSpillDetectorDeviceUnitTest";
            Guid enabledTimeseries = null;

            _oilSpillDetectorDevice = new OilSpillDetectorDeviceObject( ObjectState.New, OilSpillDetectorDevicePrimaryKey, rowVersion, host, name, description, enabledTimeseries );
        }
        return _oilSpillDetectorDevice;
    }

    public RadioDeviceObject getRadioDevice() {
        if (_radioDevice == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            String name = "NameRadioDeviceUnitTest";
            String description = "DescriptionRadioDeviceUnitTest";
            Guid enabledTimeseries = null;

            _radioDevice = new RadioDeviceObject( ObjectState.New, RadioDevicePrimaryKey, rowVersion, host, name, description, enabledTimeseries );
        }
        return _radioDevice;
    }

    public RadomeDeviceObject getRadomeDevice() {
        if (_radomeDevice == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            String name = "NameRadomeDeviceUnitTest";
            String description = "DescriptionRadomeDeviceUnitTest";
            Guid enabledTimeseries = null;
            Guid radar = null;
            Guid pressureTimeseries = null;
            Guid temperatureTimeseries = null;
            Guid dewPointTimeseries = null;
            Guid statusTimeseries = null;

            _radomeDevice = new RadomeDeviceObject( ObjectState.New, RadomeDevicePrimaryKey, rowVersion, host, name, description, enabledTimeseries, radar, pressureTimeseries, temperatureTimeseries, dewPointTimeseries, statusTimeseries );
        }
        return _radomeDevice;
    }

    public AisDeviceObject getAisDevice() {
        if (_aisDevice == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            String name = "NameAisDeviceUnitTest";
            String description = "DescriptionAisDeviceUnitTest";
            Guid enabledTimeseries = null;

            _aisDevice = new AisDeviceObject( ObjectState.New, AisDevicePrimaryKey, rowVersion, host, name, description, enabledTimeseries );
        }
        return _aisDevice;
    }

    public RadarDeviceObject getRadarDevice() {
        if (_radarDevice == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            String name = "NameRadarDeviceUnitTest";
            String description = "DescriptionRadarDeviceUnitTest";
            Guid enabledTimeseries = null;
            Guid saveSettingsTimeseries = null;
            Guid powerOnTimeseries = null;
            Guid trackingOnTimeseries = null;
            Guid radarPulseTimeseries = null;
            Guid tuningTimeseries = null;
            Guid blankSector1Timeseries = null;
            Guid sector1StartTimeseries = null;
            Guid sector1EndTimeseries = null;
            Guid blankSector2Timeseries = null;
            Guid sector2StartTimeseries = null;
            Guid sector2EndTimeseries = null;
            Guid enableAutomaticFrequencyControlTimeseries = null;
            Guid azimuthOffsetTimeseries = null;
            Guid enableSensitivityTimeControlTimeseries = null;
            Guid automaticSensitivityTimeControlTimeseries = null;
            Guid sensitivityTimeControlLevelTimeseries = null;
            Guid enableFastTimeConstantTimeseries = null;
            Guid fastTimeConstantLevelTimeseries = null;
            Guid fastTimeConstantModeTimeseries = null;
            Guid latitudeTimeseries = null;
            Guid longitudeTimeseries = null;
            Guid radome = null;
            Guid gNSSDevice = null;

            _radarDevice = new RadarDeviceObject( ObjectState.New, RadarDevicePrimaryKey, rowVersion, host, name, description, enabledTimeseries, saveSettingsTimeseries, powerOnTimeseries, trackingOnTimeseries, radarPulseTimeseries, tuningTimeseries, blankSector1Timeseries, sector1StartTimeseries, sector1EndTimeseries, blankSector2Timeseries, sector2StartTimeseries, sector2EndTimeseries, enableAutomaticFrequencyControlTimeseries, azimuthOffsetTimeseries, enableSensitivityTimeControlTimeseries, automaticSensitivityTimeControlTimeseries, sensitivityTimeControlLevelTimeseries, enableFastTimeConstantTimeseries, fastTimeConstantLevelTimeseries, fastTimeConstantModeTimeseries, latitudeTimeseries, longitudeTimeseries, radome, gNSSDevice );
        }
        return _radarDevice;
    }

    public WeatherStationDeviceObject getWeatherStationDevice() {
        if (_weatherStationDevice == null) {
            long rowVersion = 0;
            Guid host = DeviceHostPrimaryKey;
            String name = "NameWeatherStationDeviceUnitTest";
            String description = "DescriptionWeatherStationDeviceUnitTest";
            Guid enabledTimeseries = null;
            Guid barometricPressureTimeseries = null;
            Guid airTemperatureTimeseries = null;
            Guid waterTemperatureTimeseries = null;
            Guid relativeHumidityTimeseries = null;
            Guid absoluteHumidityTimeseries = null;
            Guid dewPointTimeseries = null;
            Guid windDirectionTimeseries = null;
            Guid windSpeedTimeseries = null;
            Guid gyro = null;

            _weatherStationDevice = new WeatherStationDeviceObject( ObjectState.New, WeatherStationDevicePrimaryKey, rowVersion, host, name, description, enabledTimeseries, barometricPressureTimeseries, airTemperatureTimeseries, waterTemperatureTimeseries, relativeHumidityTimeseries, absoluteHumidityTimeseries, dewPointTimeseries, windDirectionTimeseries, windSpeedTimeseries, gyro );
        }
        return _weatherStationDevice;
    }

    public FacilityObject getFacility() {
        if (_facility == null) {
            long rowVersion = 0;
            String name = "NameFacilityUnitTest";
            Guid type = null;
            double longitude = 0.0;
            double latitude = 0.0;
            double altitude = 0.0;

            _facility = new FacilityObject( ObjectState.New, FacilityPrimaryKey, rowVersion, name, type, longitude, latitude, altitude );
        }
        return _facility;
    }

    public AircraftObject getAircraft() {
        if (_aircraft == null) {
            long rowVersion = 0;
            String name = "NameAircraftUnitTest";
            Guid type = null;

            _aircraft = new AircraftObject( ObjectState.New, AircraftPrimaryKey, rowVersion, name, type );
        }
        return _aircraft;
    }

    public AisAidToNavigationObject getAisAidToNavigation() {
        if (_aisAidToNavigation == null) {
            long rowVersion = 0;
            String name = "NameAisAidToNavigationUnitTest";
            Guid mMSI = null;
            int navigationalAidType = NavigationalAidType.NotSpecified;
            Guid position = null;
            boolean isVirtual = false;
            int toBow = 0;
            int toStern = 0;
            int toPort = 0;
            int toStarboard = 0;
            Guid offPositionTimeseries = null;

            _aisAidToNavigation = new AisAidToNavigationObject( ObjectState.New, AisAidToNavigationPrimaryKey, rowVersion, name, mMSI, navigationalAidType, position, isVirtual, toBow, toStern, toPort, toStarboard, offPositionTimeseries );
        }
        return _aisAidToNavigation;
    }

    public VehicleObject getVehicle() {
        if (_vehicle == null) {
            long rowVersion = 0;
            String name = "NameVehicleUnitTest";
            Guid type = null;

            _vehicle = new VehicleObject( ObjectState.New, VehiclePrimaryKey, rowVersion, name, type );
        }
        return _vehicle;
    }

    public VesselObject getVessel() {
        if (_vessel == null) {
            long rowVersion = 0;
            String name = "NameVesselUnitTest";
            Guid type = null;
            int toBow = 0;
            int toStern = 0;
            int toPort = 0;
            int toStarboard = 0;
            Guid draughtTimeseries = null;
            Guid personsOnBoardTimeseries = null;

            _vessel = new VesselObject( ObjectState.New, VesselPrimaryKey, rowVersion, name, type, toBow, toStern, toPort, toStarboard, draughtTimeseries, personsOnBoardTimeseries );
        }
        return _vessel;
    }

    public ItemIdentityLinkObject getItemIdentityLink() {
        if (_itemIdentityLink == null) {
            long rowVersion = 0;
            Guid item = BaseStationPrimaryKey;
            Guid identity = CallsignPrimaryKey;
            DateTime start = new DateTime(2025,10,18,9,0,0);
            DateTime end = null;

            _itemIdentityLink = new ItemIdentityLinkObject( ObjectState.New, ItemIdentityLinkPrimaryKey, rowVersion, item, identity, start, end );
        }
        return _itemIdentityLink;
    }

    public ItemParentChildLinkObject getItemParentChildLink() {
        if (_itemParentChildLink == null) {
            long rowVersion = 0;
            Guid parent = BaseStationPrimaryKey;
            Guid child = BaseStationPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);

            _itemParentChildLink = new ItemParentChildLinkObject( ObjectState.New, ItemParentChildLinkPrimaryKey, rowVersion, parent, child, timestamp );
        }
        return _itemParentChildLink;
    }

    public LineInputDeviceCommandObject getLineInputDeviceCommand() {
        if (_lineInputDeviceCommand == null) {
            long rowVersion = 0;
            Guid lineInputDevice = LineInputDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _lineInputDeviceCommand = new LineInputDeviceCommandObject( ObjectState.New, LineInputDeviceCommandPrimaryKey, rowVersion, lineInputDevice, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _lineInputDeviceCommand;
    }

    public LineInputDeviceCommandReplyObject getLineInputDeviceCommandReply() {
        if (_lineInputDeviceCommandReply == null) {
            long rowVersion = 0;
            Guid lineInputDevice = LineInputDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageLineInputDeviceCommandReplyUnitTest";

            _lineInputDeviceCommandReply = new LineInputDeviceCommandReplyObject( ObjectState.New, LineInputDeviceCommandReplyPrimaryKey, rowVersion, lineInputDevice, timestamp, command, status, message );
        }
        return _lineInputDeviceCommandReply;
    }

    public LineInputDeviceConfigurationObject getLineInputDeviceConfiguration() {
        if (_lineInputDeviceConfiguration == null) {
            long rowVersion = 0;
            Guid lineInputDevice = LineInputDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            boolean storeReceivedSentences = false;
            boolean storeSentMessages = false;
            boolean storeUnsentMessages = false;
            boolean nMEA = false;
            boolean strictNMEA = false;
            int connectionType = LineInputDeviceConnectionType.Unknown;
            int udpReceivePort = 0;
            String udpSendHostname = "UdpSendHostnameLineInputDeviceConfigurationUnitTest";
            int udpSendPort = 0;
            String tcpHostname = "TcpHostnameLineInputDeviceConfigurationUnitTest";
            int tcpPort = 0;
            boolean useHttpLogin = false;
            String loginHostname = "LoginHostnameLineInputDeviceConfigurationUnitTest";
            int loginPort = 0;
            String userName = "UserNameLineInputDeviceConfigurationUnitTest";
            String password = "PasswordLineInputDeviceConfigurationUnitTest";
            String comPort = "ComPortLineInputDeviceConfigurationUnitTest";
            int baudRate = 0;
            int dataBits = 0;
            boolean discardNull = false;
            boolean dtrEnable = false;
            int handshake = Handshake.None;
            String newLine = "NewLineLineInputDeviceConfigurationUnitTest";
            int parity = Parity.None;
            byte parityReplace = 0;
            int readBufferSize = 0;
            TimeSpan readTimeout = new TimeSpan();
            int receivedBytesThreshold = 0;
            boolean rtsEnable = false;
            int stopBits = StopBits.None;
            int writeBufferSize = 0;
            TimeSpan writeTimeout = new TimeSpan();
            String pairedComPort = "PairedComPortLineInputDeviceConfigurationUnitTest";

            _lineInputDeviceConfiguration = new LineInputDeviceConfigurationObject( ObjectState.New, LineInputDeviceConfigurationPrimaryKey, rowVersion, lineInputDevice, timestamp, storeReceivedSentences, storeSentMessages, storeUnsentMessages, nMEA, strictNMEA, connectionType, udpReceivePort, udpSendHostname, udpSendPort, tcpHostname, tcpPort, useHttpLogin, loginHostname, loginPort, userName, password, comPort, baudRate, dataBits, discardNull, dtrEnable, handshake, newLine, parity, parityReplace, readBufferSize, readTimeout, receivedBytesThreshold, rtsEnable, stopBits, writeBufferSize, writeTimeout, pairedComPort );
        }
        return _lineInputDeviceConfiguration;
    }

    public LineInputMessageRoutingObject getLineInputMessageRouting() {
        if (_lineInputMessageRouting == null) {
            long rowVersion = 0;
            Guid lineInputDevice = LineInputDevicePrimaryKey;
            String type = "TypeLineInputMessageRoutingUnitTest";

            _lineInputMessageRouting = new LineInputMessageRoutingObject( ObjectState.New, LineInputMessageRoutingPrimaryKey, rowVersion, lineInputDevice, type );
        }
        return _lineInputMessageRouting;
    }

    public LineInputMessageRoutingDestinationObject getLineInputMessageRoutingDestination() {
        if (_lineInputMessageRoutingDestination == null) {
            long rowVersion = 0;
            Guid routing = LineInputMessageRoutingPrimaryKey;
            Guid listener = null;

            _lineInputMessageRoutingDestination = new LineInputMessageRoutingDestinationObject( ObjectState.New, LineInputMessageRoutingDestinationPrimaryKey, rowVersion, routing, listener );
        }
        return _lineInputMessageRoutingDestination;
    }

    public LineInputWhiteListEntryObject getLineInputWhiteListEntry() {
        if (_lineInputWhiteListEntry == null) {
            long rowVersion = 0;
            Guid lineInputDevice = LineInputDevicePrimaryKey;
            String hostName = "HostNameLineInputWhiteListEntryUnitTest";
            int port = 0;

            _lineInputWhiteListEntry = new LineInputWhiteListEntryObject( ObjectState.New, LineInputWhiteListEntryPrimaryKey, rowVersion, lineInputDevice, hostName, port );
        }
        return _lineInputWhiteListEntry;
    }

    public LogApplicationObject getLogApplication() {
        if (_logApplication == null) {
            long rowVersion = 0;
            String name = "NameLogApplicationUnitTest";
            String description = "DescriptionLogApplicationUnitTest";

            _logApplication = new LogApplicationObject( ObjectState.New, LogApplicationPrimaryKey, rowVersion, name, description );
        }
        return _logApplication;
    }

    public LogApplicationConfigurationObject getLogApplicationConfiguration() {
        if (_logApplicationConfiguration == null) {
            long rowVersion = 0;
            Guid application = LogApplicationPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            boolean finest = false;
            boolean finer = false;
            boolean fine = false;
            boolean info = false;
            boolean notice = false;
            boolean warn = false;
            boolean error = false;
            boolean severe = false;
            boolean critical = false;
            boolean alert = false;
            boolean fatal = false;
            boolean emergency = false;

            _logApplicationConfiguration = new LogApplicationConfigurationObject( ObjectState.New, LogApplicationConfigurationPrimaryKey, rowVersion, application, timestamp, finest, finer, fine, info, notice, warn, error, severe, critical, alert, fatal, emergency );
        }
        return _logApplicationConfiguration;
    }

    public LogHostObject getLogHost() {
        if (_logHost == null) {
            long rowVersion = 0;
            String computerName = "ComputerNameLogHostUnitTest";
            String description = "DescriptionLogHostUnitTest";

            _logHost = new LogHostObject( ObjectState.New, LogHostPrimaryKey, rowVersion, computerName, description );
        }
        return _logHost;
    }

    public LogHostConfigurationObject getLogHostConfiguration() {
        if (_logHostConfiguration == null) {
            long rowVersion = 0;
            Guid host = LogHostPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            boolean finest = false;
            boolean finer = false;
            boolean fine = false;
            boolean info = false;
            boolean notice = false;
            boolean warn = false;
            boolean error = false;
            boolean severe = false;
            boolean critical = false;
            boolean alert = false;
            boolean fatal = false;
            boolean emergency = false;

            _logHostConfiguration = new LogHostConfigurationObject( ObjectState.New, LogHostConfigurationPrimaryKey, rowVersion, host, timestamp, finest, finer, fine, info, notice, warn, error, severe, critical, alert, fatal, emergency );
        }
        return _logHostConfiguration;
    }

    public LogLocationObject getLogLocation() {
        if (_logLocation == null) {
            long rowVersion = 0;
            String fileName = "FileNameLogLocationUnitTest";
            int lineNumber = 0;
            String namespace = "NamespaceLogLocationUnitTest";
            String className = "ClassNameLogLocationUnitTest";
            String methodName = "MethodNameLogLocationUnitTest";

            _logLocation = new LogLocationObject( ObjectState.New, LogLocationPrimaryKey, rowVersion, fileName, lineNumber, namespace, className, methodName );
        }
        return _logLocation;
    }

    public LogProcessObject getLogProcess() {
        if (_logProcess == null) {
            long rowVersion = 0;
            Guid application = LogApplicationPrimaryKey;
            Guid host = null;
            DateTime started = new DateTime(2025,10,18,9,0,0);
            DateTime stopped = null;
            long processId = 0;
            String path = "PathLogProcessUnitTest";
            String identity = "IdentityLogProcessUnitTest";

            _logProcess = new LogProcessObject( ObjectState.New, LogProcessPrimaryKey, rowVersion, application, host, started, stopped, processId, path, identity );
        }
        return _logProcess;
    }

    public LogRecordObject getLogRecord() {
        if (_logRecord == null) {
            long rowVersion = 0;
            Guid thread = LogThreadPrimaryKey;
            long sequenceNumber = 0;
            int level = LogLevel.Unknown;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int depth = 0;
            Guid location = LogLocationPrimaryKey;
            String message = "MessageLogRecordUnitTest";
            String exceptionString = "ExceptionStringLogRecordUnitTest";
            byte[] propertiesData = new byte[0];

            _logRecord = new LogRecordObject( ObjectState.New, LogRecordPrimaryKey, rowVersion, thread, sequenceNumber, level, timestamp, depth, location, message, exceptionString, propertiesData );
        }
        return _logRecord;
    }

    public LogThreadObject getLogThread() {
        if (_logThread == null) {
            long rowVersion = 0;
            Guid process = LogProcessPrimaryKey;
            DateTime started = new DateTime(2025,10,18,9,0,0);
            DateTime stopped = null;
            long threadId = 0;
            String name = "NameLogThreadUnitTest";

            _logThread = new LogThreadObject( ObjectState.New, LogThreadPrimaryKey, rowVersion, process, started, stopped, threadId, name );
        }
        return _logThread;
    }

    public LogTraceEntryObject getLogTraceEntry() {
        if (_logTraceEntry == null) {
            long rowVersion = 0;
            Guid thread = LogThreadPrimaryKey;
            long sequenceNumber = 0;
            Guid location = LogLocationPrimaryKey;
            int depth = 0;
            DateTime entered = new DateTime(2025,10,18,9,0,0);
            DateTime ended = null;

            _logTraceEntry = new LogTraceEntryObject( ObjectState.New, LogTraceEntryPrimaryKey, rowVersion, thread, sequenceNumber, location, depth, entered, ended );
        }
        return _logTraceEntry;
    }

    public MapElementObject getMapElement() {
        if (_mapElement == null) {
            long rowVersion = 0;
            Guid item = BaseStationPrimaryKey;
            int elementType = MapElementType.Unknown;
            double latitude = 0.0;
            double longitude = 0.0;
            double angle = 0.0;
            double left = 0.0;
            double top = 0.0;
            double width = 0.0;
            double height = 0.0;
            String label = "LabelMapElementUnitTest";
            byte[] data = new byte[0];

            _mapElement = new MapElementObject( ObjectState.New, MapElementPrimaryKey, rowVersion, item, elementType, latitude, longitude, angle, left, top, width, height, label, data );
        }
        return _mapElement;
    }

    public MapInfoObject getMapInfo() {
        if (_mapInfo == null) {
            long rowVersion = 0;
            int scale = 0;
            double latitude = 0.0;
            double longitude = 0.0;
            double northWestLatitude = 0.0;
            double northWestLongitude = 0.0;
            double southEastLatitude = 0.0;
            double southEastLongitude = 0.0;
            byte[] image = new byte[0];

            _mapInfo = new MapInfoObject( ObjectState.New, MapInfoPrimaryKey, rowVersion, scale, latitude, longitude, northWestLatitude, northWestLongitude, southEastLatitude, southEastLongitude, image );
        }
        return _mapInfo;
    }

    public MapServiceOptionsObject getMapServiceOptions() {
        if (_mapServiceOptions == null) {
            long rowVersion = 0;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            String ipAddress = "IpAddressMapServiceOptionsUnitTest";
            int port = 0;
            double imageScaleFactorX = 0.0;
            double imageOffsetX = 0.0;
            double imageScaleFactorY = 0.0;
            double imageOffsetY = 0.0;

            _mapServiceOptions = new MapServiceOptionsObject( ObjectState.New, MapServiceOptionsPrimaryKey, rowVersion, timestamp, ipAddress, port, imageScaleFactorX, imageOffsetX, imageScaleFactorY, imageOffsetY );
        }
        return _mapServiceOptions;
    }

    public MaritimeIdentificationDigitsObject getMaritimeIdentificationDigits() {
        if (_maritimeIdentificationDigits == null) {
            long rowVersion = 0;
            int code = 0;
            Guid country = CountryPrimaryKey;

            _maritimeIdentificationDigits = new MaritimeIdentificationDigitsObject( ObjectState.New, MaritimeIdentificationDigitsPrimaryKey, rowVersion, code, country );
        }
        return _maritimeIdentificationDigits;
    }

    public MediaProxySessionObject getMediaProxySession() {
        if (_mediaProxySession == null) {
            long rowVersion = 0;
            Guid service = MediaServicePrimaryKey;
            String name = "NameMediaProxySessionUnitTest";
            Guid enabledTimeseries = null;

            _mediaProxySession = new MediaProxySessionObject( ObjectState.New, MediaProxySessionPrimaryKey, rowVersion, service, name, enabledTimeseries );
        }
        return _mediaProxySession;
    }

    public MediaProxySessionFileObject getMediaProxySessionFile() {
        if (_mediaProxySessionFile == null) {
            long rowVersion = 0;
            Guid proxySession = MediaProxySessionPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            String streamName = "StreamNameMediaProxySessionFileUnitTest";

            _mediaProxySessionFile = new MediaProxySessionFileObject( ObjectState.New, MediaProxySessionFilePrimaryKey, rowVersion, proxySession, timestamp, streamName );
        }
        return _mediaProxySessionFile;
    }

    public MediaProxySessionOptionsObject getMediaProxySessionOptions() {
        if (_mediaProxySessionOptions == null) {
            long rowVersion = 0;
            Guid proxySession = MediaProxySessionPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            String sourceStreamUrl = "SourceStreamUrlMediaProxySessionOptionsUnitTest";
            String streamName = "StreamNameMediaProxySessionOptionsUnitTest";
            int mode = MediaProxySessionMode.Unknown;
            int tunnelOverHTTPPortNumber = 0;
            String username = "UsernameMediaProxySessionOptionsUnitTest";
            String password = "PasswordMediaProxySessionOptionsUnitTest";
            int recorderPortNumber = 0;
            int sessionType = MediaProxySessionType.Unknown;
            TimeSpan maxFileTime = new TimeSpan();
            TimeSpan maxFileRetention = new TimeSpan();
            String videoDirectory = "VideoDirectoryMediaProxySessionOptionsUnitTest";

            _mediaProxySessionOptions = new MediaProxySessionOptionsObject( ObjectState.New, MediaProxySessionOptionsPrimaryKey, rowVersion, proxySession, timestamp, sourceStreamUrl, streamName, mode, tunnelOverHTTPPortNumber, username, password, recorderPortNumber, sessionType, maxFileTime, maxFileRetention, videoDirectory );
        }
        return _mediaProxySessionOptions;
    }

    public MediaServiceObject getMediaService() {
        if (_mediaService == null) {
            long rowVersion = 0;
            Guid enabledTimeseries = null;

            _mediaService = new MediaServiceObject( ObjectState.New, MediaServicePrimaryKey, rowVersion, enabledTimeseries );
        }
        return _mediaService;
    }

    public MediaServiceOptionsObject getMediaServiceOptions() {
        if (_mediaServiceOptions == null) {
            long rowVersion = 0;
            Guid mediaService = MediaServicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int rtspPortNumber = 0;
            int httpPortNumber = 0;

            _mediaServiceOptions = new MediaServiceOptionsObject( ObjectState.New, MediaServiceOptionsPrimaryKey, rowVersion, mediaService, timestamp, rtspPortNumber, httpPortNumber );
        }
        return _mediaServiceOptions;
    }

    public ElementTypeObject getElementType() {
        if (_elementType == null) {
            long rowVersion = 0;
            Guid namespace = NamespacePrimaryKey;
            String name = "NameElementTypeUnitTest";
            String description = "DescriptionElementTypeUnitTest";

            _elementType = new ElementTypeObject( ObjectState.New, ElementTypePrimaryKey, rowVersion, namespace, name, description );
        }
        return _elementType;
    }

    public NamespaceObject getNamespace() {
        if (_namespace == null) {
            long rowVersion = 0;
            Guid namespace = NamespacePrimaryKey;
            String name = "NameNamespaceUnitTest";
            String description = "DescriptionNamespaceUnitTest";

            _namespace = new NamespaceObject( ObjectState.New, NamespacePrimaryKey, rowVersion, namespace, name, description );
        }
        return _namespace;
    }

    public OilSpillObject getOilSpill() {
        if (_oilSpill == null) {
            long rowVersion = 0;
            Guid oilSpillDetector = OilSpillDetectorDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            double oilArea = 0.0;
            byte[] shape = new byte[0];
            byte[] bSI = new byte[0];
            byte[] oil = new byte[0];
            byte[] trace = new byte[0];

            _oilSpill = new OilSpillObject( ObjectState.New, OilSpillPrimaryKey, rowVersion, oilSpillDetector, timestamp, oilArea, shape, bSI, oil, trace );
        }
        return _oilSpill;
    }

    public OilSpillDetectorCommandObject getOilSpillDetectorCommand() {
        if (_oilSpillDetectorCommand == null) {
            long rowVersion = 0;
            Guid oilSpillDetector = OilSpillDetectorDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _oilSpillDetectorCommand = new OilSpillDetectorCommandObject( ObjectState.New, OilSpillDetectorCommandPrimaryKey, rowVersion, oilSpillDetector, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _oilSpillDetectorCommand;
    }

    public OilSpillDetectorCommandReplyObject getOilSpillDetectorCommandReply() {
        if (_oilSpillDetectorCommandReply == null) {
            long rowVersion = 0;
            Guid oilSpillDetector = OilSpillDetectorDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageOilSpillDetectorCommandReplyUnitTest";

            _oilSpillDetectorCommandReply = new OilSpillDetectorCommandReplyObject( ObjectState.New, OilSpillDetectorCommandReplyPrimaryKey, rowVersion, oilSpillDetector, timestamp, command, status, message );
        }
        return _oilSpillDetectorCommandReply;
    }

    public OilSpillDetectorConfigurationObject getOilSpillDetectorConfiguration() {
        if (_oilSpillDetectorConfiguration == null) {
            long rowVersion = 0;
            Guid oilSpillDetector = OilSpillDetectorDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            double range = 0.0;
            double startAngle = 0.0;
            double endAngle = 0.0;
            double startRange = 0.0;
            double endRange = 0.0;
            int updateRate = 0;
            TimeSpan statusSendTime = new TimeSpan();
            boolean drawBorder = false;
            byte[] colors = new byte[0];
            boolean sendToServer = false;
            String directory = "DirectoryOilSpillDetectorConfigurationUnitTest";
            boolean transparentWater = false;
            boolean savePictures = false;
            boolean sendAsTarget = false;
            boolean writeLog = false;
            String targetFilePrefix = "TargetFilePrefixOilSpillDetectorConfigurationUnitTest";
            Guid targetMMSI = null;
            double latitude = 0.0;
            double longitude = 0.0;
            boolean testSourceEnabled = false;
            String proxyServer = "ProxyServerOilSpillDetectorConfigurationUnitTest";
            boolean useProxyServer = false;

            _oilSpillDetectorConfiguration = new OilSpillDetectorConfigurationObject( ObjectState.New, OilSpillDetectorConfigurationPrimaryKey, rowVersion, oilSpillDetector, timestamp, range, startAngle, endAngle, startRange, endRange, updateRate, statusSendTime, drawBorder, colors, sendToServer, directory, transparentWater, savePictures, sendAsTarget, writeLog, targetFilePrefix, targetMMSI, latitude, longitude, testSourceEnabled, proxyServer, useProxyServer );
        }
        return _oilSpillDetectorConfiguration;
    }

    public Position2DTimeseriesValueObject getPosition2DTimeseriesValue() {
        if (_position2DTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = Position2DTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Double x = null;
            Double y = null;

            _position2DTimeseriesValue = new Position2DTimeseriesValueObject( ObjectState.New, Position2DTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, x, y );
        }
        return _position2DTimeseriesValue;
    }

    public Position3DTimeseriesValueObject getPosition3DTimeseriesValue() {
        if (_position3DTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = Position3DTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Double x = null;
            Double y = null;
            Double z = null;

            _position3DTimeseriesValue = new Position3DTimeseriesValueObject( ObjectState.New, Position3DTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, x, y, z );
        }
        return _position3DTimeseriesValue;
    }

    public ProcessTrackValueResultObject getProcessTrackValueResult() {
        if (_processTrackValueResult == null) {
            long rowVersion = 0;
            boolean createdNewTrack = false;
            Guid trackId = new Guid();

            _processTrackValueResult = new ProcessTrackValueResultObject( ObjectState.New, ProcessTrackValueResultPrimaryKey, rowVersion, createdNewTrack, trackId );
        }
        return _processTrackValueResult;
    }

    public BinaryPropertyObject getBinaryProperty() {
        if (_binaryProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            byte[] value = new byte[0];

            _binaryProperty = new BinaryPropertyObject( ObjectState.New, BinaryPropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _binaryProperty;
    }

    public BooleanPropertyObject getBooleanProperty() {
        if (_booleanProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            boolean value = false;

            _booleanProperty = new BooleanPropertyObject( ObjectState.New, BooleanPropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _booleanProperty;
    }

    public BytePropertyObject getByteProperty() {
        if (_byteProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            byte value = 0;

            _byteProperty = new BytePropertyObject( ObjectState.New, BytePropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _byteProperty;
    }

    public DateTimePropertyObject getDateTimeProperty() {
        if (_dateTimeProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            DateTime value = new DateTime(2025,10,18,9,0,0);

            _dateTimeProperty = new DateTimePropertyObject( ObjectState.New, DateTimePropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _dateTimeProperty;
    }

    public DoublePropertyObject getDoubleProperty() {
        if (_doubleProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            double value = 0.0;

            _doubleProperty = new DoublePropertyObject( ObjectState.New, DoublePropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _doubleProperty;
    }

    public GuidPropertyObject getGuidProperty() {
        if (_guidProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid value = new Guid();

            _guidProperty = new GuidPropertyObject( ObjectState.New, GuidPropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _guidProperty;
    }

    public Int16PropertyObject getInt16Property() {
        if (_int16Property == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            short value = 0;

            _int16Property = new Int16PropertyObject( ObjectState.New, Int16PropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _int16Property;
    }

    public Int32PropertyObject getInt32Property() {
        if (_int32Property == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            int value = 0;

            _int32Property = new Int32PropertyObject( ObjectState.New, Int32PropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _int32Property;
    }

    public Int64PropertyObject getInt64Property() {
        if (_int64Property == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            long value = 0;

            _int64Property = new Int64PropertyObject( ObjectState.New, Int64PropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _int64Property;
    }

    public ReferencePropertyObject getReferenceProperty() {
        if (_referenceProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid value = null;

            _referenceProperty = new ReferencePropertyObject( ObjectState.New, ReferencePropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _referenceProperty;
    }

    public SBytePropertyObject getSByteProperty() {
        if (_sByteProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            byte value = 0;

            _sByteProperty = new SBytePropertyObject( ObjectState.New, SBytePropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _sByteProperty;
    }

    public SinglePropertyObject getSingleProperty() {
        if (_singleProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            float value = 0.0f;

            _singleProperty = new SinglePropertyObject( ObjectState.New, SinglePropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _singleProperty;
    }

    public StringPropertyObject getStringProperty() {
        if (_stringProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            String value = "ValueStringPropertyUnitTest";

            _stringProperty = new StringPropertyObject( ObjectState.New, StringPropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _stringProperty;
    }

    public BinaryTimeseriesPropertyObject getBinaryTimeseriesProperty() {
        if (_binaryTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _binaryTimeseriesProperty = new BinaryTimeseriesPropertyObject( ObjectState.New, BinaryTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _binaryTimeseriesProperty;
    }

    public BooleanTimeseriesPropertyObject getBooleanTimeseriesProperty() {
        if (_booleanTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _booleanTimeseriesProperty = new BooleanTimeseriesPropertyObject( ObjectState.New, BooleanTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _booleanTimeseriesProperty;
    }

    public ByteTimeseriesPropertyObject getByteTimeseriesProperty() {
        if (_byteTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _byteTimeseriesProperty = new ByteTimeseriesPropertyObject( ObjectState.New, ByteTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _byteTimeseriesProperty;
    }

    public DateTimeTimeseriesPropertyObject getDateTimeTimeseriesProperty() {
        if (_dateTimeTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _dateTimeTimeseriesProperty = new DateTimeTimeseriesPropertyObject( ObjectState.New, DateTimeTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _dateTimeTimeseriesProperty;
    }

    public DoubleTimeseriesPropertyObject getDoubleTimeseriesProperty() {
        if (_doubleTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _doubleTimeseriesProperty = new DoubleTimeseriesPropertyObject( ObjectState.New, DoubleTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _doubleTimeseriesProperty;
    }

    public GuidTimeseriesPropertyObject getGuidTimeseriesProperty() {
        if (_guidTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _guidTimeseriesProperty = new GuidTimeseriesPropertyObject( ObjectState.New, GuidTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _guidTimeseriesProperty;
    }

    public Int16TimeseriesPropertyObject getInt16TimeseriesProperty() {
        if (_int16TimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _int16TimeseriesProperty = new Int16TimeseriesPropertyObject( ObjectState.New, Int16TimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _int16TimeseriesProperty;
    }

    public Int32TimeseriesPropertyObject getInt32TimeseriesProperty() {
        if (_int32TimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _int32TimeseriesProperty = new Int32TimeseriesPropertyObject( ObjectState.New, Int32TimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _int32TimeseriesProperty;
    }

    public Int64TimeseriesPropertyObject getInt64TimeseriesProperty() {
        if (_int64TimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _int64TimeseriesProperty = new Int64TimeseriesPropertyObject( ObjectState.New, Int64TimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _int64TimeseriesProperty;
    }

    public ReferenceTimeseriesPropertyObject getReferenceTimeseriesProperty() {
        if (_referenceTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _referenceTimeseriesProperty = new ReferenceTimeseriesPropertyObject( ObjectState.New, ReferenceTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _referenceTimeseriesProperty;
    }

    public SByteTimeseriesPropertyObject getSByteTimeseriesProperty() {
        if (_sByteTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _sByteTimeseriesProperty = new SByteTimeseriesPropertyObject( ObjectState.New, SByteTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _sByteTimeseriesProperty;
    }

    public SingleTimeseriesPropertyObject getSingleTimeseriesProperty() {
        if (_singleTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _singleTimeseriesProperty = new SingleTimeseriesPropertyObject( ObjectState.New, SingleTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _singleTimeseriesProperty;
    }

    public StringTimeseriesPropertyObject getStringTimeseriesProperty() {
        if (_stringTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _stringTimeseriesProperty = new StringTimeseriesPropertyObject( ObjectState.New, StringTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _stringTimeseriesProperty;
    }

    public TimeSpanTimeseriesPropertyObject getTimeSpanTimeseriesProperty() {
        if (_timeSpanTimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _timeSpanTimeseriesProperty = new TimeSpanTimeseriesPropertyObject( ObjectState.New, TimeSpanTimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _timeSpanTimeseriesProperty;
    }

    public UInt16TimeseriesPropertyObject getUInt16TimeseriesProperty() {
        if (_uInt16TimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _uInt16TimeseriesProperty = new UInt16TimeseriesPropertyObject( ObjectState.New, UInt16TimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _uInt16TimeseriesProperty;
    }

    public UInt32TimeseriesPropertyObject getUInt32TimeseriesProperty() {
        if (_uInt32TimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _uInt32TimeseriesProperty = new UInt32TimeseriesPropertyObject( ObjectState.New, UInt32TimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _uInt32TimeseriesProperty;
    }

    public UInt64TimeseriesPropertyObject getUInt64TimeseriesProperty() {
        if (_uInt64TimeseriesProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            Guid timeseries = null;

            _uInt64TimeseriesProperty = new UInt64TimeseriesPropertyObject( ObjectState.New, UInt64TimeseriesPropertyPrimaryKey, rowVersion, element, definition, timeseries );
        }
        return _uInt64TimeseriesProperty;
    }

    public TimeSpanPropertyObject getTimeSpanProperty() {
        if (_timeSpanProperty == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            TimeSpan value = new TimeSpan();

            _timeSpanProperty = new TimeSpanPropertyObject( ObjectState.New, TimeSpanPropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _timeSpanProperty;
    }

    public UInt16PropertyObject getUInt16Property() {
        if (_uInt16Property == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            short value = 0;

            _uInt16Property = new UInt16PropertyObject( ObjectState.New, UInt16PropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _uInt16Property;
    }

    public UInt32PropertyObject getUInt32Property() {
        if (_uInt32Property == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            int value = 0;

            _uInt32Property = new UInt32PropertyObject( ObjectState.New, UInt32PropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _uInt32Property;
    }

    public UInt64PropertyObject getUInt64Property() {
        if (_uInt64Property == null) {
            long rowVersion = 0;
            Guid element = ElementPrimaryKey;
            Guid definition = BinaryPropertyDefinitionPrimaryKey;
            long value = 0;

            _uInt64Property = new UInt64PropertyObject( ObjectState.New, UInt64PropertyPrimaryKey, rowVersion, element, definition, value );
        }
        return _uInt64Property;
    }

    public BinaryPropertyDefinitionObject getBinaryPropertyDefinition() {
        if (_binaryPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameBinaryPropertyDefinitionUnitTest";
            String description = "DescriptionBinaryPropertyDefinitionUnitTest";
            byte[] defaultValue = new byte[0];

            _binaryPropertyDefinition = new BinaryPropertyDefinitionObject( ObjectState.New, BinaryPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue );
        }
        return _binaryPropertyDefinition;
    }

    public BooleanPropertyDefinitionObject getBooleanPropertyDefinition() {
        if (_booleanPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameBooleanPropertyDefinitionUnitTest";
            String description = "DescriptionBooleanPropertyDefinitionUnitTest";
            boolean defaultValue = false;

            _booleanPropertyDefinition = new BooleanPropertyDefinitionObject( ObjectState.New, BooleanPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue );
        }
        return _booleanPropertyDefinition;
    }

    public BytePropertyDefinitionObject getBytePropertyDefinition() {
        if (_bytePropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameBytePropertyDefinitionUnitTest";
            String description = "DescriptionBytePropertyDefinitionUnitTest";
            byte defaultValue = 0;
            byte minValue = 0;
            byte maxValue = 0;

            _bytePropertyDefinition = new BytePropertyDefinitionObject( ObjectState.New, BytePropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _bytePropertyDefinition;
    }

    public DateTimePropertyDefinitionObject getDateTimePropertyDefinition() {
        if (_dateTimePropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameDateTimePropertyDefinitionUnitTest";
            String description = "DescriptionDateTimePropertyDefinitionUnitTest";
            String defaultValue = "DefaultValueDateTimePropertyDefinitionUnitTest";
            String minValue = "MinValueDateTimePropertyDefinitionUnitTest";
            String maxValue = "MaxValueDateTimePropertyDefinitionUnitTest";

            _dateTimePropertyDefinition = new DateTimePropertyDefinitionObject( ObjectState.New, DateTimePropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _dateTimePropertyDefinition;
    }

    public DoublePropertyDefinitionObject getDoublePropertyDefinition() {
        if (_doublePropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameDoublePropertyDefinitionUnitTest";
            String description = "DescriptionDoublePropertyDefinitionUnitTest";
            double defaultValue = 0.0;
            double minValue = 0.0;
            double maxValue = 0.0;

            _doublePropertyDefinition = new DoublePropertyDefinitionObject( ObjectState.New, DoublePropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _doublePropertyDefinition;
    }

    public GuidPropertyDefinitionObject getGuidPropertyDefinition() {
        if (_guidPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameGuidPropertyDefinitionUnitTest";
            String description = "DescriptionGuidPropertyDefinitionUnitTest";
            Guid defaultValue = new Guid();

            _guidPropertyDefinition = new GuidPropertyDefinitionObject( ObjectState.New, GuidPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue );
        }
        return _guidPropertyDefinition;
    }

    public Int16PropertyDefinitionObject getInt16PropertyDefinition() {
        if (_int16PropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameInt16PropertyDefinitionUnitTest";
            String description = "DescriptionInt16PropertyDefinitionUnitTest";
            short defaultValue = 0;
            short minValue = 0;
            short maxValue = 0;

            _int16PropertyDefinition = new Int16PropertyDefinitionObject( ObjectState.New, Int16PropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _int16PropertyDefinition;
    }

    public Int32PropertyDefinitionObject getInt32PropertyDefinition() {
        if (_int32PropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameInt32PropertyDefinitionUnitTest";
            String description = "DescriptionInt32PropertyDefinitionUnitTest";
            int defaultValue = 0;
            int minValue = 0;
            int maxValue = 0;

            _int32PropertyDefinition = new Int32PropertyDefinitionObject( ObjectState.New, Int32PropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _int32PropertyDefinition;
    }

    public Int64PropertyDefinitionObject getInt64PropertyDefinition() {
        if (_int64PropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameInt64PropertyDefinitionUnitTest";
            String description = "DescriptionInt64PropertyDefinitionUnitTest";
            long defaultValue = 0;
            long minValue = 0;
            long maxValue = 0;

            _int64PropertyDefinition = new Int64PropertyDefinitionObject( ObjectState.New, Int64PropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _int64PropertyDefinition;
    }

    public ReferencePropertyDefinitionObject getReferencePropertyDefinition() {
        if (_referencePropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameReferencePropertyDefinitionUnitTest";
            String description = "DescriptionReferencePropertyDefinitionUnitTest";
            Guid defaultValue = null;
            Guid referencedElementType = null;

            _referencePropertyDefinition = new ReferencePropertyDefinitionObject( ObjectState.New, ReferencePropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, referencedElementType );
        }
        return _referencePropertyDefinition;
    }

    public SBytePropertyDefinitionObject getSBytePropertyDefinition() {
        if (_sBytePropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameSBytePropertyDefinitionUnitTest";
            String description = "DescriptionSBytePropertyDefinitionUnitTest";
            byte defaultValue = 0;
            byte minValue = 0;
            byte maxValue = 0;

            _sBytePropertyDefinition = new SBytePropertyDefinitionObject( ObjectState.New, SBytePropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _sBytePropertyDefinition;
    }

    public SinglePropertyDefinitionObject getSinglePropertyDefinition() {
        if (_singlePropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameSinglePropertyDefinitionUnitTest";
            String description = "DescriptionSinglePropertyDefinitionUnitTest";
            float defaultValue = 0.0f;
            float minValue = 0.0f;
            float maxValue = 0.0f;

            _singlePropertyDefinition = new SinglePropertyDefinitionObject( ObjectState.New, SinglePropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _singlePropertyDefinition;
    }

    public StringPropertyDefinitionObject getStringPropertyDefinition() {
        if (_stringPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameStringPropertyDefinitionUnitTest";
            String description = "DescriptionStringPropertyDefinitionUnitTest";
            String defaultValue = "DefaultValueStringPropertyDefinitionUnitTest";
            String pattern = "PatternStringPropertyDefinitionUnitTest";

            _stringPropertyDefinition = new StringPropertyDefinitionObject( ObjectState.New, StringPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, pattern );
        }
        return _stringPropertyDefinition;
    }

    public BinaryTimeseriesPropertyDefinitionObject getBinaryTimeseriesPropertyDefinition() {
        if (_binaryTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameBinaryTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionBinaryTimeseriesPropertyDefinitionUnitTest";

            _binaryTimeseriesPropertyDefinition = new BinaryTimeseriesPropertyDefinitionObject( ObjectState.New, BinaryTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description );
        }
        return _binaryTimeseriesPropertyDefinition;
    }

    public BooleanTimeseriesPropertyDefinitionObject getBooleanTimeseriesPropertyDefinition() {
        if (_booleanTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameBooleanTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionBooleanTimeseriesPropertyDefinitionUnitTest";

            _booleanTimeseriesPropertyDefinition = new BooleanTimeseriesPropertyDefinitionObject( ObjectState.New, BooleanTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description );
        }
        return _booleanTimeseriesPropertyDefinition;
    }

    public ByteTimeseriesPropertyDefinitionObject getByteTimeseriesPropertyDefinition() {
        if (_byteTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameByteTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionByteTimeseriesPropertyDefinitionUnitTest";
            byte minValue = 0;
            byte maxValue = 0;

            _byteTimeseriesPropertyDefinition = new ByteTimeseriesPropertyDefinitionObject( ObjectState.New, ByteTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _byteTimeseriesPropertyDefinition;
    }

    public DateTimeTimeseriesPropertyDefinitionObject getDateTimeTimeseriesPropertyDefinition() {
        if (_dateTimeTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameDateTimeTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionDateTimeTimeseriesPropertyDefinitionUnitTest";
            String minValue = "MinValueDateTimeTimeseriesPropertyDefinitionUnitTest";
            String maxValue = "MaxValueDateTimeTimeseriesPropertyDefinitionUnitTest";

            _dateTimeTimeseriesPropertyDefinition = new DateTimeTimeseriesPropertyDefinitionObject( ObjectState.New, DateTimeTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _dateTimeTimeseriesPropertyDefinition;
    }

    public DoubleTimeseriesPropertyDefinitionObject getDoubleTimeseriesPropertyDefinition() {
        if (_doubleTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameDoubleTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionDoubleTimeseriesPropertyDefinitionUnitTest";
            double minValue = 0.0;
            double maxValue = 0.0;

            _doubleTimeseriesPropertyDefinition = new DoubleTimeseriesPropertyDefinitionObject( ObjectState.New, DoubleTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _doubleTimeseriesPropertyDefinition;
    }

    public GuidTimeseriesPropertyDefinitionObject getGuidTimeseriesPropertyDefinition() {
        if (_guidTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameGuidTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionGuidTimeseriesPropertyDefinitionUnitTest";

            _guidTimeseriesPropertyDefinition = new GuidTimeseriesPropertyDefinitionObject( ObjectState.New, GuidTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description );
        }
        return _guidTimeseriesPropertyDefinition;
    }

    public Int16TimeseriesPropertyDefinitionObject getInt16TimeseriesPropertyDefinition() {
        if (_int16TimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameInt16TimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionInt16TimeseriesPropertyDefinitionUnitTest";
            short minValue = 0;
            short maxValue = 0;

            _int16TimeseriesPropertyDefinition = new Int16TimeseriesPropertyDefinitionObject( ObjectState.New, Int16TimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _int16TimeseriesPropertyDefinition;
    }

    public Int32TimeseriesPropertyDefinitionObject getInt32TimeseriesPropertyDefinition() {
        if (_int32TimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameInt32TimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionInt32TimeseriesPropertyDefinitionUnitTest";
            int minValue = 0;
            int maxValue = 0;

            _int32TimeseriesPropertyDefinition = new Int32TimeseriesPropertyDefinitionObject( ObjectState.New, Int32TimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _int32TimeseriesPropertyDefinition;
    }

    public Int64TimeseriesPropertyDefinitionObject getInt64TimeseriesPropertyDefinition() {
        if (_int64TimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameInt64TimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionInt64TimeseriesPropertyDefinitionUnitTest";
            long minValue = 0;
            long maxValue = 0;

            _int64TimeseriesPropertyDefinition = new Int64TimeseriesPropertyDefinitionObject( ObjectState.New, Int64TimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _int64TimeseriesPropertyDefinition;
    }

    public ReferenceTimeseriesPropertyDefinitionObject getReferenceTimeseriesPropertyDefinition() {
        if (_referenceTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameReferenceTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionReferenceTimeseriesPropertyDefinitionUnitTest";
            Guid referencedElementType = null;

            _referenceTimeseriesPropertyDefinition = new ReferenceTimeseriesPropertyDefinitionObject( ObjectState.New, ReferenceTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, referencedElementType );
        }
        return _referenceTimeseriesPropertyDefinition;
    }

    public SByteTimeseriesPropertyDefinitionObject getSByteTimeseriesPropertyDefinition() {
        if (_sByteTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameSByteTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionSByteTimeseriesPropertyDefinitionUnitTest";
            byte minValue = 0;
            byte maxValue = 0;

            _sByteTimeseriesPropertyDefinition = new SByteTimeseriesPropertyDefinitionObject( ObjectState.New, SByteTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _sByteTimeseriesPropertyDefinition;
    }

    public SingleTimeseriesPropertyDefinitionObject getSingleTimeseriesPropertyDefinition() {
        if (_singleTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameSingleTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionSingleTimeseriesPropertyDefinitionUnitTest";
            float minValue = 0.0f;
            float maxValue = 0.0f;

            _singleTimeseriesPropertyDefinition = new SingleTimeseriesPropertyDefinitionObject( ObjectState.New, SingleTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _singleTimeseriesPropertyDefinition;
    }

    public StringTimeseriesPropertyDefinitionObject getStringTimeseriesPropertyDefinition() {
        if (_stringTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameStringTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionStringTimeseriesPropertyDefinitionUnitTest";
            String pattern = "PatternStringTimeseriesPropertyDefinitionUnitTest";

            _stringTimeseriesPropertyDefinition = new StringTimeseriesPropertyDefinitionObject( ObjectState.New, StringTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, pattern );
        }
        return _stringTimeseriesPropertyDefinition;
    }

    public TimeSpanTimeseriesPropertyDefinitionObject getTimeSpanTimeseriesPropertyDefinition() {
        if (_timeSpanTimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameTimeSpanTimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionTimeSpanTimeseriesPropertyDefinitionUnitTest";
            TimeSpan minValue = new TimeSpan();
            TimeSpan maxValue = new TimeSpan();

            _timeSpanTimeseriesPropertyDefinition = new TimeSpanTimeseriesPropertyDefinitionObject( ObjectState.New, TimeSpanTimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _timeSpanTimeseriesPropertyDefinition;
    }

    public UInt16TimeseriesPropertyDefinitionObject getUInt16TimeseriesPropertyDefinition() {
        if (_uInt16TimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameUInt16TimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionUInt16TimeseriesPropertyDefinitionUnitTest";
            short minValue = 0;
            short maxValue = 0;

            _uInt16TimeseriesPropertyDefinition = new UInt16TimeseriesPropertyDefinitionObject( ObjectState.New, UInt16TimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _uInt16TimeseriesPropertyDefinition;
    }

    public UInt32TimeseriesPropertyDefinitionObject getUInt32TimeseriesPropertyDefinition() {
        if (_uInt32TimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameUInt32TimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionUInt32TimeseriesPropertyDefinitionUnitTest";
            int minValue = 0;
            int maxValue = 0;

            _uInt32TimeseriesPropertyDefinition = new UInt32TimeseriesPropertyDefinitionObject( ObjectState.New, UInt32TimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _uInt32TimeseriesPropertyDefinition;
    }

    public UInt64TimeseriesPropertyDefinitionObject getUInt64TimeseriesPropertyDefinition() {
        if (_uInt64TimeseriesPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameUInt64TimeseriesPropertyDefinitionUnitTest";
            String description = "DescriptionUInt64TimeseriesPropertyDefinitionUnitTest";
            long minValue = 0;
            long maxValue = 0;

            _uInt64TimeseriesPropertyDefinition = new UInt64TimeseriesPropertyDefinitionObject( ObjectState.New, UInt64TimeseriesPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, minValue, maxValue );
        }
        return _uInt64TimeseriesPropertyDefinition;
    }

    public TimeSpanPropertyDefinitionObject getTimeSpanPropertyDefinition() {
        if (_timeSpanPropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameTimeSpanPropertyDefinitionUnitTest";
            String description = "DescriptionTimeSpanPropertyDefinitionUnitTest";
            TimeSpan defaultValue = new TimeSpan();
            TimeSpan minValue = new TimeSpan();
            TimeSpan maxValue = new TimeSpan();

            _timeSpanPropertyDefinition = new TimeSpanPropertyDefinitionObject( ObjectState.New, TimeSpanPropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _timeSpanPropertyDefinition;
    }

    public UInt16PropertyDefinitionObject getUInt16PropertyDefinition() {
        if (_uInt16PropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameUInt16PropertyDefinitionUnitTest";
            String description = "DescriptionUInt16PropertyDefinitionUnitTest";
            short defaultValue = 0;
            short minValue = 0;
            short maxValue = 0;

            _uInt16PropertyDefinition = new UInt16PropertyDefinitionObject( ObjectState.New, UInt16PropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _uInt16PropertyDefinition;
    }

    public UInt32PropertyDefinitionObject getUInt32PropertyDefinition() {
        if (_uInt32PropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameUInt32PropertyDefinitionUnitTest";
            String description = "DescriptionUInt32PropertyDefinitionUnitTest";
            int defaultValue = 0;
            int minValue = 0;
            int maxValue = 0;

            _uInt32PropertyDefinition = new UInt32PropertyDefinitionObject( ObjectState.New, UInt32PropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _uInt32PropertyDefinition;
    }

    public UInt64PropertyDefinitionObject getUInt64PropertyDefinition() {
        if (_uInt64PropertyDefinition == null) {
            long rowVersion = 0;
            Guid elementType = ElementTypePrimaryKey;
            String name = "NameUInt64PropertyDefinitionUnitTest";
            String description = "DescriptionUInt64PropertyDefinitionUnitTest";
            long defaultValue = 0;
            long minValue = 0;
            long maxValue = 0;

            _uInt64PropertyDefinition = new UInt64PropertyDefinitionObject( ObjectState.New, UInt64PropertyDefinitionPrimaryKey, rowVersion, elementType, name, description, defaultValue, minValue, maxValue );
        }
        return _uInt64PropertyDefinition;
    }

    public RadarAlarmStatusObject getRadarAlarmStatus() {
        if (_radarAlarmStatus == null) {
            long rowVersion = 0;
            Guid radar = RadarDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int type = AlarmState.Unknown;

            _radarAlarmStatus = new RadarAlarmStatusObject( ObjectState.New, RadarAlarmStatusPrimaryKey, rowVersion, radar, timestamp, type );
        }
        return _radarAlarmStatus;
    }

    public RadarCommandObject getRadarCommand() {
        if (_radarCommand == null) {
            long rowVersion = 0;
            Guid radar = RadarDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _radarCommand = new RadarCommandObject( ObjectState.New, RadarCommandPrimaryKey, rowVersion, radar, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _radarCommand;
    }

    public RadarCommandGetStatusObject getRadarCommandGetStatus() {
        if (_radarCommandGetStatus == null) {
            long rowVersion = 0;
            Guid radar = RadarDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _radarCommandGetStatus = new RadarCommandGetStatusObject( ObjectState.New, RadarCommandGetStatusPrimaryKey, rowVersion, radar, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _radarCommandGetStatus;
    }

    public RadarCommandReplyObject getRadarCommandReply() {
        if (_radarCommandReply == null) {
            long rowVersion = 0;
            Guid radar = RadarDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageRadarCommandReplyUnitTest";

            _radarCommandReply = new RadarCommandReplyObject( ObjectState.New, RadarCommandReplyPrimaryKey, rowVersion, radar, timestamp, command, status, message );
        }
        return _radarCommandReply;
    }

    public RadarCommandReplyGetStatusObject getRadarCommandReplyGetStatus() {
        if (_radarCommandReplyGetStatus == null) {
            long rowVersion = 0;
            Guid radar = RadarDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageRadarCommandReplyGetStatusUnitTest";
            int azimuthCount = 0;
            int triggerCount = 0;
            TimeSpan rotationCount = new TimeSpan();
            int pulse = RadarPulse.Short;
            boolean tx = false;

            _radarCommandReplyGetStatus = new RadarCommandReplyGetStatusObject( ObjectState.New, RadarCommandReplyGetStatusPrimaryKey, rowVersion, radar, timestamp, command, status, message, azimuthCount, triggerCount, rotationCount, pulse, tx );
        }
        return _radarCommandReplyGetStatus;
    }

    public RadarConfigurationObject getRadarConfiguration() {
        if (_radarConfiguration == null) {
            long rowVersion = 0;
            Guid radar = RadarDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int radarProtocolVersion = 0;
            String radarIPAddress = "RadarIPAddressRadarConfigurationUnitTest";
            int radarPort = 0;
            int radarConfigurationPort = 0;
            TimeSpan skipMagicTimeout = new TimeSpan();
            TimeSpan readTimeout = new TimeSpan();
            TimeSpan synchronizationInterval = new TimeSpan();
            int targetsRefreshRate = 0;
            int range = 0;
            int sectorCount = 0;
            int sectorOffset = 0;
            int imageColor = 0;
            Integer imageSubstitutionColor = null;
            int transparentColor = 0;
            double imageScaleFactorX = 0.0;
            double imageOffsetX = 0.0;
            double imageScaleFactorY = 0.0;
            double imageOffsetY = 0.0;
            int radarImageType = RadarImageType.MaskedProcessed;
            int trackColor = 0;
            int vectorColor = 0;
            boolean enableNmea = false;
            String nmeaReceiverIPAddress = "NmeaReceiverIPAddressRadarConfigurationUnitTest";
            int nmeaReceiverPort = 0;
            String nmeaReceiverSourceId = "NmeaReceiverSourceIdRadarConfigurationUnitTest";

            _radarConfiguration = new RadarConfigurationObject( ObjectState.New, RadarConfigurationPrimaryKey, rowVersion, radar, timestamp, radarProtocolVersion, radarIPAddress, radarPort, radarConfigurationPort, skipMagicTimeout, readTimeout, synchronizationInterval, targetsRefreshRate, range, sectorCount, sectorOffset, imageColor, imageSubstitutionColor, transparentColor, imageScaleFactorX, imageOffsetX, imageScaleFactorY, imageOffsetY, radarImageType, trackColor, vectorColor, enableNmea, nmeaReceiverIPAddress, nmeaReceiverPort, nmeaReceiverSourceId );
        }
        return _radarConfiguration;
    }

    public RadarImageObject getRadarImage() {
        if (_radarImage == null) {
            long rowVersion = 0;
            Guid radar = RadarDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int depth = 0;
            int resolution = 0;
            int range = 0;
            byte[] image = new byte[0];

            _radarImage = new RadarImageObject( ObjectState.New, RadarImagePrimaryKey, rowVersion, radar, timestamp, depth, resolution, range, image );
        }
        return _radarImage;
    }

    public RadarRawTrackTableObject getRadarRawTrackTable() {
        if (_radarRawTrackTable == null) {
            long rowVersion = 0;
            Guid radar = RadarDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int count = 0;
            byte[] table = new byte[0];

            _radarRawTrackTable = new RadarRawTrackTableObject( ObjectState.New, RadarRawTrackTablePrimaryKey, rowVersion, radar, timestamp, count, table );
        }
        return _radarRawTrackTable;
    }

    public RadarStatusObject getRadarStatus() {
        if (_radarStatus == null) {
            long rowVersion = 0;
            Guid radar = RadarDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int azimuthCount = 0;
            int triggerCount = 0;
            TimeSpan rotationTime = new TimeSpan();
            int pulse = RadarPulse.Short;
            boolean tx = false;
            boolean tracking = false;

            _radarStatus = new RadarStatusObject( ObjectState.New, RadarStatusPrimaryKey, rowVersion, radar, timestamp, azimuthCount, triggerCount, rotationTime, pulse, tx, tracking );
        }
        return _radarStatus;
    }

    public RadioCommandObject getRadioCommand() {
        if (_radioCommand == null) {
            long rowVersion = 0;
            Guid radio = RadioDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _radioCommand = new RadioCommandObject( ObjectState.New, RadioCommandPrimaryKey, rowVersion, radio, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _radioCommand;
    }

    public RadioCommandReplyObject getRadioCommandReply() {
        if (_radioCommandReply == null) {
            long rowVersion = 0;
            Guid radio = RadioDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageRadioCommandReplyUnitTest";

            _radioCommandReply = new RadioCommandReplyObject( ObjectState.New, RadioCommandReplyPrimaryKey, rowVersion, radio, timestamp, command, status, message );
        }
        return _radioCommandReply;
    }

    public RadioConfigurationObject getRadioConfiguration() {
        if (_radioConfiguration == null) {
            long rowVersion = 0;
            Guid radio = RadioDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            double longitude = 0.0;
            double latitude = 0.0;
            String playbackUrl = "PlaybackUrlRadioConfigurationUnitTest";
            String radioIPAddress = "RadioIPAddressRadioConfigurationUnitTest";
            int radioPort = 0;
            String ed137IPAddress = "Ed137IPAddressRadioConfigurationUnitTest";
            int ed137Port = 0;

            _radioConfiguration = new RadioConfigurationObject( ObjectState.New, RadioConfigurationPrimaryKey, rowVersion, radio, timestamp, longitude, latitude, playbackUrl, radioIPAddress, radioPort, ed137IPAddress, ed137Port );
        }
        return _radioConfiguration;
    }

    public RadomeCommandObject getRadomeCommand() {
        if (_radomeCommand == null) {
            long rowVersion = 0;
            Guid radome = RadomeDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _radomeCommand = new RadomeCommandObject( ObjectState.New, RadomeCommandPrimaryKey, rowVersion, radome, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _radomeCommand;
    }

    public RadomeCommandReplyObject getRadomeCommandReply() {
        if (_radomeCommandReply == null) {
            long rowVersion = 0;
            Guid radome = RadomeDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageRadomeCommandReplyUnitTest";

            _radomeCommandReply = new RadomeCommandReplyObject( ObjectState.New, RadomeCommandReplyPrimaryKey, rowVersion, radome, timestamp, command, status, message );
        }
        return _radomeCommandReply;
    }

    public RadomeConfigurationObject getRadomeConfiguration() {
        if (_radomeConfiguration == null) {
            long rowVersion = 0;
            Guid radome = RadomeDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            TimeSpan interval = new TimeSpan();
            double lowPressureLimit = 0.0;
            double highPressureLimit = 0.0;
            double lowTemperatureLimit = 0.0;
            double highTemperatureLimit = 0.0;

            _radomeConfiguration = new RadomeConfigurationObject( ObjectState.New, RadomeConfigurationPrimaryKey, rowVersion, radome, timestamp, interval, lowPressureLimit, highPressureLimit, lowTemperatureLimit, highTemperatureLimit );
        }
        return _radomeConfiguration;
    }

    public ReferenceTimeseriesValueObject getReferenceTimeseriesValue() {
        if (_referenceTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = ReferenceTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid value = ElementPrimaryKey;

            _referenceTimeseriesValue = new ReferenceTimeseriesValueObject( ObjectState.New, ReferenceTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _referenceTimeseriesValue;
    }

    public SByteTimeseriesValueObject getSByteTimeseriesValue() {
        if (_sByteTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = SByteTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Byte value = null;

            _sByteTimeseriesValue = new SByteTimeseriesValueObject( ObjectState.New, SByteTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _sByteTimeseriesValue;
    }

    public SecurityDomainObject getSecurityDomain() {
        if (_securityDomain == null) {
            long rowVersion = 0;
            String name = "NameSecurityDomainUnitTest";
            String description = "DescriptionSecurityDomainUnitTest";

            _securityDomain = new SecurityDomainObject( ObjectState.New, SecurityDomainPrimaryKey, rowVersion, name, description );
        }
        return _securityDomain;
    }

    public SecurityLoginObject getSecurityLogin() {
        if (_securityLogin == null) {
            long rowVersion = 0;
            Guid domain = SecurityDomainPrimaryKey;
            String identity = "IdentitySecurityLoginUnitTest";
            String description = "DescriptionSecurityLoginUnitTest";

            _securityLogin = new SecurityLoginObject( ObjectState.New, SecurityLoginPrimaryKey, rowVersion, domain, identity, description );
        }
        return _securityLogin;
    }

    public SecurityRoleObject getSecurityRole() {
        if (_securityRole == null) {
            long rowVersion = 0;
            Guid domain = SecurityDomainPrimaryKey;
            String identity = "IdentitySecurityRoleUnitTest";
            String description = "DescriptionSecurityRoleUnitTest";
            String name = "NameSecurityRoleUnitTest";

            _securityRole = new SecurityRoleObject( ObjectState.New, SecurityRolePrimaryKey, rowVersion, domain, identity, description, name );
        }
        return _securityRole;
    }

    public SecurityIdentifierRoleLinkObject getSecurityIdentifierRoleLink() {
        if (_securityIdentifierRoleLink == null) {
            long rowVersion = 0;
            Guid member = SecurityLoginPrimaryKey;
            Guid role = SecurityRolePrimaryKey;
            DateTime start = new DateTime(2025,10,18,9,0,0);
            DateTime end = null;

            _securityIdentifierRoleLink = new SecurityIdentifierRoleLinkObject( ObjectState.New, SecurityIdentifierRoleLinkPrimaryKey, rowVersion, member, role, start, end );
        }
        return _securityIdentifierRoleLink;
    }

    public SecurityLoginSessionObject getSecurityLoginSession() {
        if (_securityLoginSession == null) {
            long rowVersion = 0;
            Guid login = SecurityLoginPrimaryKey;
            DateTime fromTime = new DateTime(2025,10,18,9,0,0);
            DateTime throughTime = null;
            Guid clientSession = new Guid();
            String notificationQueueName = "NotificationQueueNameSecurityLoginSessionUnitTest";
            String messageQueueName = "MessageQueueNameSecurityLoginSessionUnitTest";

            _securityLoginSession = new SecurityLoginSessionObject( ObjectState.New, SecurityLoginSessionPrimaryKey, rowVersion, login, fromTime, throughTime, clientSession, notificationQueueName, messageQueueName );
        }
        return _securityLoginSession;
    }

    public SecurityPermissionObject getSecurityPermission() {
        if (_securityPermission == null) {
            long rowVersion = 0;
            Guid identifier = SecurityLoginPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int typeCode = 0;
            boolean canCreate = false;
            boolean canRead = false;
            boolean canUpdate = false;
            boolean canDelete = false;

            _securityPermission = new SecurityPermissionObject( ObjectState.New, SecurityPermissionPrimaryKey, rowVersion, identifier, timestamp, typeCode, canCreate, canRead, canUpdate, canDelete );
        }
        return _securityPermission;
    }

    public SingleTimeseriesValueObject getSingleTimeseriesValue() {
        if (_singleTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = SingleTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Float value = null;

            _singleTimeseriesValue = new SingleTimeseriesValueObject( ObjectState.New, SingleTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _singleTimeseriesValue;
    }

    public StringTimeseriesValueObject getStringTimeseriesValue() {
        if (_stringTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = StringTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            String value = "ValueStringTimeseriesValueUnitTest";

            _stringTimeseriesValue = new StringTimeseriesValueObject( ObjectState.New, StringTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _stringTimeseriesValue;
    }

    public BinaryTimeseriesObject getBinaryTimeseries() {
        if (_binaryTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameBinaryTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _binaryTimeseries = new BinaryTimeseriesObject( ObjectState.New, BinaryTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _binaryTimeseries;
    }

    public BooleanTimeseriesObject getBooleanTimeseries() {
        if (_booleanTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameBooleanTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _booleanTimeseries = new BooleanTimeseriesObject( ObjectState.New, BooleanTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _booleanTimeseries;
    }

    public AisAidToNavigationOffPositionTimeseriesObject getAisAidToNavigationOffPositionTimeseries() {
        if (_aisAidToNavigationOffPositionTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameAisAidToNavigationOffPositionTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid aidToNavigation = null;

            _aisAidToNavigationOffPositionTimeseries = new AisAidToNavigationOffPositionTimeseriesObject( ObjectState.New, AisAidToNavigationOffPositionTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, aidToNavigation );
        }
        return _aisAidToNavigationOffPositionTimeseries;
    }

    public DeviceEnabledTimeseriesObject getDeviceEnabledTimeseries() {
        if (_deviceEnabledTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameDeviceEnabledTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid device = null;

            _deviceEnabledTimeseries = new DeviceEnabledTimeseriesObject( ObjectState.New, DeviceEnabledTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, device );
        }
        return _deviceEnabledTimeseries;
    }

    public RadarAutomaticSensitivityTimeControlTimeseriesObject getRadarAutomaticSensitivityTimeControlTimeseries() {
        if (_radarAutomaticSensitivityTimeControlTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarAutomaticSensitivityTimeControlTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarAutomaticSensitivityTimeControlTimeseries = new RadarAutomaticSensitivityTimeControlTimeseriesObject( ObjectState.New, RadarAutomaticSensitivityTimeControlTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarAutomaticSensitivityTimeControlTimeseries;
    }

    public RadarBlankSector1TimeseriesObject getRadarBlankSector1Timeseries() {
        if (_radarBlankSector1Timeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarBlankSector1TimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarBlankSector1Timeseries = new RadarBlankSector1TimeseriesObject( ObjectState.New, RadarBlankSector1TimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarBlankSector1Timeseries;
    }

    public RadarBlankSector2TimeseriesObject getRadarBlankSector2Timeseries() {
        if (_radarBlankSector2Timeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarBlankSector2TimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarBlankSector2Timeseries = new RadarBlankSector2TimeseriesObject( ObjectState.New, RadarBlankSector2TimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarBlankSector2Timeseries;
    }

    public RadarEnableAutomaticFrequencyControlTimeseriesObject getRadarEnableAutomaticFrequencyControlTimeseries() {
        if (_radarEnableAutomaticFrequencyControlTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarEnableAutomaticFrequencyControlTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarEnableAutomaticFrequencyControlTimeseries = new RadarEnableAutomaticFrequencyControlTimeseriesObject( ObjectState.New, RadarEnableAutomaticFrequencyControlTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarEnableAutomaticFrequencyControlTimeseries;
    }

    public RadarEnableFastTimeConstantTimeseriesObject getRadarEnableFastTimeConstantTimeseries() {
        if (_radarEnableFastTimeConstantTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarEnableFastTimeConstantTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarEnableFastTimeConstantTimeseries = new RadarEnableFastTimeConstantTimeseriesObject( ObjectState.New, RadarEnableFastTimeConstantTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarEnableFastTimeConstantTimeseries;
    }

    public RadarEnableSensitivityTimeControlTimeseriesObject getRadarEnableSensitivityTimeControlTimeseries() {
        if (_radarEnableSensitivityTimeControlTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarEnableSensitivityTimeControlTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarEnableSensitivityTimeControlTimeseries = new RadarEnableSensitivityTimeControlTimeseriesObject( ObjectState.New, RadarEnableSensitivityTimeControlTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarEnableSensitivityTimeControlTimeseries;
    }

    public RadarPowerOnTimeseriesObject getRadarPowerOnTimeseries() {
        if (_radarPowerOnTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarPowerOnTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarPowerOnTimeseries = new RadarPowerOnTimeseriesObject( ObjectState.New, RadarPowerOnTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarPowerOnTimeseries;
    }

    public RadarSaveSettingsTimeseriesObject getRadarSaveSettingsTimeseries() {
        if (_radarSaveSettingsTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarSaveSettingsTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarSaveSettingsTimeseries = new RadarSaveSettingsTimeseriesObject( ObjectState.New, RadarSaveSettingsTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarSaveSettingsTimeseries;
    }

    public RadarTrackingTimeseriesObject getRadarTrackingTimeseries() {
        if (_radarTrackingTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarTrackingTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarTrackingTimeseries = new RadarTrackingTimeseriesObject( ObjectState.New, RadarTrackingTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarTrackingTimeseries;
    }

    public MediaProxySessionEnabledTimeseriesObject getMediaProxySessionEnabledTimeseries() {
        if (_mediaProxySessionEnabledTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameMediaProxySessionEnabledTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid proxySession = null;

            _mediaProxySessionEnabledTimeseries = new MediaProxySessionEnabledTimeseriesObject( ObjectState.New, MediaProxySessionEnabledTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, proxySession );
        }
        return _mediaProxySessionEnabledTimeseries;
    }

    public MediaServiceEnabledTimeseriesObject getMediaServiceEnabledTimeseries() {
        if (_mediaServiceEnabledTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameMediaServiceEnabledTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid service = null;

            _mediaServiceEnabledTimeseries = new MediaServiceEnabledTimeseriesObject( ObjectState.New, MediaServiceEnabledTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, service );
        }
        return _mediaServiceEnabledTimeseries;
    }

    public ByteTimeseriesObject getByteTimeseries() {
        if (_byteTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameByteTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _byteTimeseries = new ByteTimeseriesObject( ObjectState.New, ByteTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _byteTimeseries;
    }

    public DateTimeTimeseriesObject getDateTimeTimeseries() {
        if (_dateTimeTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameDateTimeTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _dateTimeTimeseries = new DateTimeTimeseriesObject( ObjectState.New, DateTimeTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _dateTimeTimeseries;
    }

    public DoubleTimeseriesObject getDoubleTimeseries() {
        if (_doubleTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameDoubleTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _doubleTimeseries = new DoubleTimeseriesObject( ObjectState.New, DoubleTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _doubleTimeseries;
    }

    public GNSSAltitudeTimeseriesObject getGNSSAltitudeTimeseries() {
        if (_gNSSAltitudeTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGNSSAltitudeTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid gNSSDevice = null;

            _gNSSAltitudeTimeseries = new GNSSAltitudeTimeseriesObject( ObjectState.New, GNSSAltitudeTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, gNSSDevice );
        }
        return _gNSSAltitudeTimeseries;
    }

    public GNSSLatitudeTimeseriesObject getGNSSLatitudeTimeseries() {
        if (_gNSSLatitudeTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGNSSLatitudeTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid gNSSDevice = null;

            _gNSSLatitudeTimeseries = new GNSSLatitudeTimeseriesObject( ObjectState.New, GNSSLatitudeTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, gNSSDevice );
        }
        return _gNSSLatitudeTimeseries;
    }

    public GNSSLongitudeTimeseriesObject getGNSSLongitudeTimeseries() {
        if (_gNSSLongitudeTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGNSSLongitudeTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid gNSSDevice = null;

            _gNSSLongitudeTimeseries = new GNSSLongitudeTimeseriesObject( ObjectState.New, GNSSLongitudeTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, gNSSDevice );
        }
        return _gNSSLongitudeTimeseries;
    }

    public GyroCourseTimeseriesObject getGyroCourseTimeseries() {
        if (_gyroCourseTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGyroCourseTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid gyroDevice = null;

            _gyroCourseTimeseries = new GyroCourseTimeseriesObject( ObjectState.New, GyroCourseTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, gyroDevice );
        }
        return _gyroCourseTimeseries;
    }

    public GyroHeadingMagneticNorthTimeseriesObject getGyroHeadingMagneticNorthTimeseries() {
        if (_gyroHeadingMagneticNorthTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGyroHeadingMagneticNorthTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid gyroDevice = null;

            _gyroHeadingMagneticNorthTimeseries = new GyroHeadingMagneticNorthTimeseriesObject( ObjectState.New, GyroHeadingMagneticNorthTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, gyroDevice );
        }
        return _gyroHeadingMagneticNorthTimeseries;
    }

    public GyroHeadingTrueNorthTimeseriesObject getGyroHeadingTrueNorthTimeseries() {
        if (_gyroHeadingTrueNorthTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGyroHeadingTrueNorthTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid gyroDevice = null;

            _gyroHeadingTrueNorthTimeseries = new GyroHeadingTrueNorthTimeseriesObject( ObjectState.New, GyroHeadingTrueNorthTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, gyroDevice );
        }
        return _gyroHeadingTrueNorthTimeseries;
    }

    public GyroPitchTimeseriesObject getGyroPitchTimeseries() {
        if (_gyroPitchTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGyroPitchTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid gyroDevice = null;

            _gyroPitchTimeseries = new GyroPitchTimeseriesObject( ObjectState.New, GyroPitchTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, gyroDevice );
        }
        return _gyroPitchTimeseries;
    }

    public GyroRateOfTurnTimeseriesObject getGyroRateOfTurnTimeseries() {
        if (_gyroRateOfTurnTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGyroRateOfTurnTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid gyroDevice = null;

            _gyroRateOfTurnTimeseries = new GyroRateOfTurnTimeseriesObject( ObjectState.New, GyroRateOfTurnTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, gyroDevice );
        }
        return _gyroRateOfTurnTimeseries;
    }

    public GyroRollTimeseriesObject getGyroRollTimeseries() {
        if (_gyroRollTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGyroRollTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid gyroDevice = null;

            _gyroRollTimeseries = new GyroRollTimeseriesObject( ObjectState.New, GyroRollTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, gyroDevice );
        }
        return _gyroRollTimeseries;
    }

    public GyroSpeedTimeseriesObject getGyroSpeedTimeseries() {
        if (_gyroSpeedTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGyroSpeedTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid gyroDevice = null;

            _gyroSpeedTimeseries = new GyroSpeedTimeseriesObject( ObjectState.New, GyroSpeedTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, gyroDevice );
        }
        return _gyroSpeedTimeseries;
    }

    public RadarLatitudeTimeseriesObject getRadarLatitudeTimeseries() {
        if (_radarLatitudeTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarLatitudeTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarLatitudeTimeseries = new RadarLatitudeTimeseriesObject( ObjectState.New, RadarLatitudeTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarLatitudeTimeseries;
    }

    public RadarLongitudeTimeseriesObject getRadarLongitudeTimeseries() {
        if (_radarLongitudeTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarLongitudeTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarLongitudeTimeseries = new RadarLongitudeTimeseriesObject( ObjectState.New, RadarLongitudeTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarLongitudeTimeseries;
    }

    public RadomeDewPointTimeseriesObject getRadomeDewPointTimeseries() {
        if (_radomeDewPointTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadomeDewPointTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radome = null;

            _radomeDewPointTimeseries = new RadomeDewPointTimeseriesObject( ObjectState.New, RadomeDewPointTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radome );
        }
        return _radomeDewPointTimeseries;
    }

    public RadomePressureTimeseriesObject getRadomePressureTimeseries() {
        if (_radomePressureTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadomePressureTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radome = null;

            _radomePressureTimeseries = new RadomePressureTimeseriesObject( ObjectState.New, RadomePressureTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radome );
        }
        return _radomePressureTimeseries;
    }

    public RadomeTemperatureTimeseriesObject getRadomeTemperatureTimeseries() {
        if (_radomeTemperatureTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadomeTemperatureTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radome = null;

            _radomeTemperatureTimeseries = new RadomeTemperatureTimeseriesObject( ObjectState.New, RadomeTemperatureTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radome );
        }
        return _radomeTemperatureTimeseries;
    }

    public VesselDraughtTimeseriesObject getVesselDraughtTimeseries() {
        if (_vesselDraughtTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameVesselDraughtTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid vessel = null;

            _vesselDraughtTimeseries = new VesselDraughtTimeseriesObject( ObjectState.New, VesselDraughtTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, vessel );
        }
        return _vesselDraughtTimeseries;
    }

    public ViewLatitudeTimeseriesObject getViewLatitudeTimeseries() {
        if (_viewLatitudeTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameViewLatitudeTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid view = null;

            _viewLatitudeTimeseries = new ViewLatitudeTimeseriesObject( ObjectState.New, ViewLatitudeTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, view );
        }
        return _viewLatitudeTimeseries;
    }

    public ViewLongitudeTimeseriesObject getViewLongitudeTimeseries() {
        if (_viewLongitudeTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameViewLongitudeTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid view = null;

            _viewLongitudeTimeseries = new ViewLongitudeTimeseriesObject( ObjectState.New, ViewLongitudeTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, view );
        }
        return _viewLongitudeTimeseries;
    }

    public ViewZoomLevelTimeseriesObject getViewZoomLevelTimeseries() {
        if (_viewZoomLevelTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameViewZoomLevelTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid view = null;

            _viewZoomLevelTimeseries = new ViewZoomLevelTimeseriesObject( ObjectState.New, ViewZoomLevelTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, view );
        }
        return _viewZoomLevelTimeseries;
    }

    public WeatherStationAbsoluteHumidityTimeseriesObject getWeatherStationAbsoluteHumidityTimeseries() {
        if (_weatherStationAbsoluteHumidityTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameWeatherStationAbsoluteHumidityTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid weatherStation = null;

            _weatherStationAbsoluteHumidityTimeseries = new WeatherStationAbsoluteHumidityTimeseriesObject( ObjectState.New, WeatherStationAbsoluteHumidityTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, weatherStation );
        }
        return _weatherStationAbsoluteHumidityTimeseries;
    }

    public WeatherStationAirTemperatureTimeseriesObject getWeatherStationAirTemperatureTimeseries() {
        if (_weatherStationAirTemperatureTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameWeatherStationAirTemperatureTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid weatherStation = null;

            _weatherStationAirTemperatureTimeseries = new WeatherStationAirTemperatureTimeseriesObject( ObjectState.New, WeatherStationAirTemperatureTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, weatherStation );
        }
        return _weatherStationAirTemperatureTimeseries;
    }

    public WeatherStationBarometricPressureTimeseriesObject getWeatherStationBarometricPressureTimeseries() {
        if (_weatherStationBarometricPressureTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameWeatherStationBarometricPressureTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid weatherStation = null;

            _weatherStationBarometricPressureTimeseries = new WeatherStationBarometricPressureTimeseriesObject( ObjectState.New, WeatherStationBarometricPressureTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, weatherStation );
        }
        return _weatherStationBarometricPressureTimeseries;
    }

    public WeatherStationDewPointTimeseriesObject getWeatherStationDewPointTimeseries() {
        if (_weatherStationDewPointTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameWeatherStationDewPointTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid weatherStation = null;

            _weatherStationDewPointTimeseries = new WeatherStationDewPointTimeseriesObject( ObjectState.New, WeatherStationDewPointTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, weatherStation );
        }
        return _weatherStationDewPointTimeseries;
    }

    public WeatherStationRelativeHumidityTimeseriesObject getWeatherStationRelativeHumidityTimeseries() {
        if (_weatherStationRelativeHumidityTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameWeatherStationRelativeHumidityTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid weatherStation = null;

            _weatherStationRelativeHumidityTimeseries = new WeatherStationRelativeHumidityTimeseriesObject( ObjectState.New, WeatherStationRelativeHumidityTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, weatherStation );
        }
        return _weatherStationRelativeHumidityTimeseries;
    }

    public WeatherStationWaterTemperatureTimeseriesObject getWeatherStationWaterTemperatureTimeseries() {
        if (_weatherStationWaterTemperatureTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameWeatherStationWaterTemperatureTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid weatherStation = null;

            _weatherStationWaterTemperatureTimeseries = new WeatherStationWaterTemperatureTimeseriesObject( ObjectState.New, WeatherStationWaterTemperatureTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, weatherStation );
        }
        return _weatherStationWaterTemperatureTimeseries;
    }

    public WeatherStationWindDirectionTimeseriesObject getWeatherStationWindDirectionTimeseries() {
        if (_weatherStationWindDirectionTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameWeatherStationWindDirectionTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid weatherStation = null;

            _weatherStationWindDirectionTimeseries = new WeatherStationWindDirectionTimeseriesObject( ObjectState.New, WeatherStationWindDirectionTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, weatherStation );
        }
        return _weatherStationWindDirectionTimeseries;
    }

    public WeatherStationWindSpeedTimeseriesObject getWeatherStationWindSpeedTimeseries() {
        if (_weatherStationWindSpeedTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameWeatherStationWindSpeedTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid weatherStation = null;

            _weatherStationWindSpeedTimeseries = new WeatherStationWindSpeedTimeseriesObject( ObjectState.New, WeatherStationWindSpeedTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, weatherStation );
        }
        return _weatherStationWindSpeedTimeseries;
    }

    public GeoPosition2DTimeseriesObject getGeoPosition2DTimeseries() {
        if (_geoPosition2DTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGeoPosition2DTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _geoPosition2DTimeseries = new GeoPosition2DTimeseriesObject( ObjectState.New, GeoPosition2DTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _geoPosition2DTimeseries;
    }

    public AisAidToNavigationPositionTimeseriesObject getAisAidToNavigationPositionTimeseries() {
        if (_aisAidToNavigationPositionTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameAisAidToNavigationPositionTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid aidToNavigation = null;

            _aisAidToNavigationPositionTimeseries = new AisAidToNavigationPositionTimeseriesObject( ObjectState.New, AisAidToNavigationPositionTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, aidToNavigation );
        }
        return _aisAidToNavigationPositionTimeseries;
    }

    public GeoPosition3DTimeseriesObject getGeoPosition3DTimeseries() {
        if (_geoPosition3DTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGeoPosition3DTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _geoPosition3DTimeseries = new GeoPosition3DTimeseriesObject( ObjectState.New, GeoPosition3DTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _geoPosition3DTimeseries;
    }

    public GuidTimeseriesObject getGuidTimeseries() {
        if (_guidTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameGuidTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _guidTimeseries = new GuidTimeseriesObject( ObjectState.New, GuidTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _guidTimeseries;
    }

    public Int16TimeseriesObject getInt16Timeseries() {
        if (_int16Timeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameInt16TimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _int16Timeseries = new Int16TimeseriesObject( ObjectState.New, Int16TimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _int16Timeseries;
    }

    public Int32TimeseriesObject getInt32Timeseries() {
        if (_int32Timeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameInt32TimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _int32Timeseries = new Int32TimeseriesObject( ObjectState.New, Int32TimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _int32Timeseries;
    }

    public RadarAzimuthOffsetTimeseriesObject getRadarAzimuthOffsetTimeseries() {
        if (_radarAzimuthOffsetTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarAzimuthOffsetTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarAzimuthOffsetTimeseries = new RadarAzimuthOffsetTimeseriesObject( ObjectState.New, RadarAzimuthOffsetTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarAzimuthOffsetTimeseries;
    }

    public RadarFastTimeConstantLevelTimeseriesObject getRadarFastTimeConstantLevelTimeseries() {
        if (_radarFastTimeConstantLevelTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarFastTimeConstantLevelTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarFastTimeConstantLevelTimeseries = new RadarFastTimeConstantLevelTimeseriesObject( ObjectState.New, RadarFastTimeConstantLevelTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarFastTimeConstantLevelTimeseries;
    }

    public RadarFastTimeConstantModeTimeseriesObject getRadarFastTimeConstantModeTimeseries() {
        if (_radarFastTimeConstantModeTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarFastTimeConstantModeTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarFastTimeConstantModeTimeseries = new RadarFastTimeConstantModeTimeseriesObject( ObjectState.New, RadarFastTimeConstantModeTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarFastTimeConstantModeTimeseries;
    }

    public RadarPulseTimeseriesObject getRadarPulseTimeseries() {
        if (_radarPulseTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarPulseTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarPulseTimeseries = new RadarPulseTimeseriesObject( ObjectState.New, RadarPulseTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarPulseTimeseries;
    }

    public RadarSector1EndTimeseriesObject getRadarSector1EndTimeseries() {
        if (_radarSector1EndTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarSector1EndTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarSector1EndTimeseries = new RadarSector1EndTimeseriesObject( ObjectState.New, RadarSector1EndTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarSector1EndTimeseries;
    }

    public RadarSector1StartTimeseriesObject getRadarSector1StartTimeseries() {
        if (_radarSector1StartTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarSector1StartTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarSector1StartTimeseries = new RadarSector1StartTimeseriesObject( ObjectState.New, RadarSector1StartTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarSector1StartTimeseries;
    }

    public RadarSector2EndTimeseriesObject getRadarSector2EndTimeseries() {
        if (_radarSector2EndTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarSector2EndTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarSector2EndTimeseries = new RadarSector2EndTimeseriesObject( ObjectState.New, RadarSector2EndTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarSector2EndTimeseries;
    }

    public RadarSector2StartTimeseriesObject getRadarSector2StartTimeseries() {
        if (_radarSector2StartTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarSector2StartTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarSector2StartTimeseries = new RadarSector2StartTimeseriesObject( ObjectState.New, RadarSector2StartTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarSector2StartTimeseries;
    }

    public RadarSensitivityTimeControlLevelTimeseriesObject getRadarSensitivityTimeControlLevelTimeseries() {
        if (_radarSensitivityTimeControlLevelTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarSensitivityTimeControlLevelTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarSensitivityTimeControlLevelTimeseries = new RadarSensitivityTimeControlLevelTimeseriesObject( ObjectState.New, RadarSensitivityTimeControlLevelTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarSensitivityTimeControlLevelTimeseries;
    }

    public RadarTuningTimeseriesObject getRadarTuningTimeseries() {
        if (_radarTuningTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadarTuningTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radar = null;

            _radarTuningTimeseries = new RadarTuningTimeseriesObject( ObjectState.New, RadarTuningTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radar );
        }
        return _radarTuningTimeseries;
    }

    public VesselPersonsOnBoardTimeseriesObject getVesselPersonsOnBoardTimeseries() {
        if (_vesselPersonsOnBoardTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameVesselPersonsOnBoardTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid vessel = null;

            _vesselPersonsOnBoardTimeseries = new VesselPersonsOnBoardTimeseriesObject( ObjectState.New, VesselPersonsOnBoardTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, vessel );
        }
        return _vesselPersonsOnBoardTimeseries;
    }

    public Int64TimeseriesObject getInt64Timeseries() {
        if (_int64Timeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameInt64TimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _int64Timeseries = new Int64TimeseriesObject( ObjectState.New, Int64TimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _int64Timeseries;
    }

    public Position2DTimeseriesObject getPosition2DTimeseries() {
        if (_position2DTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NamePosition2DTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _position2DTimeseries = new Position2DTimeseriesObject( ObjectState.New, Position2DTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _position2DTimeseries;
    }

    public Position3DTimeseriesObject getPosition3DTimeseries() {
        if (_position3DTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NamePosition3DTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _position3DTimeseries = new Position3DTimeseriesObject( ObjectState.New, Position3DTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _position3DTimeseries;
    }

    public ReferenceTimeseriesObject getReferenceTimeseries() {
        if (_referenceTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameReferenceTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _referenceTimeseries = new ReferenceTimeseriesObject( ObjectState.New, ReferenceTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _referenceTimeseries;
    }

    public SByteTimeseriesObject getSByteTimeseries() {
        if (_sByteTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameSByteTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _sByteTimeseries = new SByteTimeseriesObject( ObjectState.New, SByteTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _sByteTimeseries;
    }

    public SingleTimeseriesObject getSingleTimeseries() {
        if (_singleTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameSingleTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _singleTimeseries = new SingleTimeseriesObject( ObjectState.New, SingleTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _singleTimeseries;
    }

    public StringTimeseriesObject getStringTimeseries() {
        if (_stringTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameStringTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _stringTimeseries = new StringTimeseriesObject( ObjectState.New, StringTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _stringTimeseries;
    }

    public TimeSpanTimeseriesObject getTimeSpanTimeseries() {
        if (_timeSpanTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameTimeSpanTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _timeSpanTimeseries = new TimeSpanTimeseriesObject( ObjectState.New, TimeSpanTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _timeSpanTimeseries;
    }

    public UInt16TimeseriesObject getUInt16Timeseries() {
        if (_uInt16Timeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameUInt16TimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _uInt16Timeseries = new UInt16TimeseriesObject( ObjectState.New, UInt16TimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _uInt16Timeseries;
    }

    public UInt32TimeseriesObject getUInt32Timeseries() {
        if (_uInt32Timeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameUInt32TimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _uInt32Timeseries = new UInt32TimeseriesObject( ObjectState.New, UInt32TimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _uInt32Timeseries;
    }

    public RadomeStatusTimeseriesObject getRadomeStatusTimeseries() {
        if (_radomeStatusTimeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameRadomeStatusTimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();
            Guid radome = null;

            _radomeStatusTimeseries = new RadomeStatusTimeseriesObject( ObjectState.New, RadomeStatusTimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention, radome );
        }
        return _radomeStatusTimeseries;
    }

    public UInt64TimeseriesObject getUInt64Timeseries() {
        if (_uInt64Timeseries == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameUInt64TimeseriesUnitTest";
            TimeSpan maxRetention = new TimeSpan();

            _uInt64Timeseries = new UInt64TimeseriesObject( ObjectState.New, UInt64TimeseriesPrimaryKey, rowVersion, catalog, name, maxRetention );
        }
        return _uInt64Timeseries;
    }

    public TimeseriesCatalogObject getTimeseriesCatalog() {
        if (_timeseriesCatalog == null) {
            long rowVersion = 0;
            Guid catalog = null;
            String name = "NameTimeseriesCatalogUnitTest";

            _timeseriesCatalog = new TimeseriesCatalogObject( ObjectState.New, TimeseriesCatalogPrimaryKey, rowVersion, catalog, name );
        }
        return _timeseriesCatalog;
    }

    public TimeseriesInfoObject getTimeseriesInfo() {
        if (_timeseriesInfo == null) {
            long rowVersion = 0;
            DateTime firstTimestamp = null;
            DateTime lastTimestamp = null;
            long count = 0;

            _timeseriesInfo = new TimeseriesInfoObject( ObjectState.New, TimeseriesInfoPrimaryKey, rowVersion, firstTimestamp, lastTimestamp, count );
        }
        return _timeseriesInfo;
    }

    public TimeSpanTimeseriesValueObject getTimeSpanTimeseriesValue() {
        if (_timeSpanTimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = TimeSpanTimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            TimeSpan value = null;

            _timeSpanTimeseriesValue = new TimeSpanTimeseriesValueObject( ObjectState.New, TimeSpanTimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _timeSpanTimeseriesValue;
    }

    public TrackableItemTrackLinkObject getTrackableItemTrackLink() {
        if (_trackableItemTrackLink == null) {
            long rowVersion = 0;
            Guid item = AircraftPrimaryKey;
            Guid track = TrackPrimaryKey;
            DateTime start = new DateTime(2025,10,18,9,0,0);
            DateTime end = null;

            _trackableItemTrackLink = new TrackableItemTrackLinkObject( ObjectState.New, TrackableItemTrackLinkPrimaryKey, rowVersion, item, track, start, end );
        }
        return _trackableItemTrackLink;
    }

    public TrackObject getTrack() {
        if (_track == null) {
            long rowVersion = 0;
            Guid tracker = AisDevicePrimaryKey;
            long trackNumber = 0;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);

            _track = new TrackObject( ObjectState.New, TrackPrimaryKey, rowVersion, tracker, trackNumber, timestamp );
        }
        return _track;
    }

    public Track3DObject getTrack3D() {
        if (_track3D == null) {
            long rowVersion = 0;
            Guid tracker = AisDevicePrimaryKey;
            long trackNumber = 0;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);

            _track3D = new Track3DObject( ObjectState.New, Track3DPrimaryKey, rowVersion, tracker, trackNumber, timestamp );
        }
        return _track3D;
    }

    public TrackerFilterParametersObject getTrackerFilterParameters() {
        if (_trackerFilterParameters == null) {
            long rowVersion = 0;
            Guid tracker = AisDevicePrimaryKey;
            String name = "NameTrackerFilterParametersUnitTest";

            _trackerFilterParameters = new TrackerFilterParametersObject( ObjectState.New, TrackerFilterParametersPrimaryKey, rowVersion, tracker, name );
        }
        return _trackerFilterParameters;
    }

    public TrackerFilterParametersConfigurationObject getTrackerFilterParametersConfiguration() {
        if (_trackerFilterParametersConfiguration == null) {
            long rowVersion = 0;
            Guid parameters = TrackerFilterParametersPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            boolean useNaivePredictor = false;
            int numberOfPoints = 0;
            int windowSize = 0;
            int stabilizeCount = 0;
            int maxBadPoints = 0;
            int modelType = TrackerFilterModelType.Unknown;
            double sigmaR = 0.0;
            double sigmaAcc = 0.0;
            double tauVel = 0.0;
            double tauAcc = 0.0;
            double deltaRMin = 0.0;
            double deltaVMax = 0.0;
            double deltaAMax = 0.0;

            _trackerFilterParametersConfiguration = new TrackerFilterParametersConfigurationObject( ObjectState.New, TrackerFilterParametersConfigurationPrimaryKey, rowVersion, parameters, timestamp, useNaivePredictor, numberOfPoints, windowSize, stabilizeCount, maxBadPoints, modelType, sigmaR, sigmaAcc, tauVel, tauAcc, deltaRMin, deltaVMax, deltaAMax );
        }
        return _trackerFilterParametersConfiguration;
    }

    public TrackInfoObject getTrackInfo() {
        if (_trackInfo == null) {
            long rowVersion = 0;
            DateTime firstTimestamp = null;
            DateTime lastTimestamp = null;
            long count = 0;
            Double northWestLatitude = null;
            Double northWestLongitude = null;
            Double southEastLatitude = null;
            Double southEastLongitude = null;

            _trackInfo = new TrackInfoObject( ObjectState.New, TrackInfoPrimaryKey, rowVersion, firstTimestamp, lastTimestamp, count, northWestLatitude, northWestLongitude, southEastLatitude, southEastLongitude );
        }
        return _trackInfo;
    }

    public TrackingServiceOptionsObject getTrackingServiceOptions() {
        if (_trackingServiceOptions == null) {
            long rowVersion = 0;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            TimeSpan timerInterval = new TimeSpan();
            TimeSpan maxAgeOfCurrentTrackValue = new TimeSpan();
            double falseThreshold = 0.0;
            double distanceThreshold = 0.0;
            double distanceUnmergeThreshold = 0.0;
            long unmergeLatency = 0;
            boolean kalmanFiltering = false;
            double maxCourseDeviation = 0.0;
            double maxSpeedDeviation = 0.0;
            double minimumSpeedThreshold = 0.0;

            _trackingServiceOptions = new TrackingServiceOptionsObject( ObjectState.New, TrackingServiceOptionsPrimaryKey, rowVersion, timestamp, timerInterval, maxAgeOfCurrentTrackValue, falseThreshold, distanceThreshold, distanceUnmergeThreshold, unmergeLatency, kalmanFiltering, maxCourseDeviation, maxSpeedDeviation, minimumSpeedThreshold );
        }
        return _trackingServiceOptions;
    }

    public TrackLinkObject getTrackLink() {
        if (_trackLink == null) {
            long rowVersion = 0;
            Guid primary = TrackPrimaryKey;
            Guid secondary = TrackPrimaryKey;
            DateTime start = new DateTime(2025,10,18,9,0,0);
            DateTime end = null;

            _trackLink = new TrackLinkObject( ObjectState.New, TrackLinkPrimaryKey, rowVersion, primary, secondary, start, end );
        }
        return _trackLink;
    }

    public TrackValueObject getTrackValue() {
        if (_trackValue == null) {
            long rowVersion = 0;
            Guid track = TrackPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int flags = TrackFlags.None;
            int status = TrackStatus.Unknown;
            double latitude = 0.0;
            double longitude = 0.0;
            double speed = 0.0;
            double course = 0.0;
            double heading = 0.0;

            _trackValue = new TrackValueObject( ObjectState.New, TrackValuePrimaryKey, rowVersion, track, timestamp, flags, status, latitude, longitude, speed, course, heading );
        }
        return _trackValue;
    }

    public TrackValue3DObject getTrackValue3D() {
        if (_trackValue3D == null) {
            long rowVersion = 0;
            Guid track = Track3DPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int flags = TrackFlags3D.None;
            int status = 0;
            double latitude = 0.0;
            double longitude = 0.0;
            double altitude = 0.0;
            double speed = 0.0;
            double course = 0.0;
            double rateOfClimb = 0.0;

            _trackValue3D = new TrackValue3DObject( ObjectState.New, TrackValue3DPrimaryKey, rowVersion, track, timestamp, flags, status, latitude, longitude, altitude, speed, course, rateOfClimb );
        }
        return _trackValue3D;
    }

    public UInt16TimeseriesValueObject getUInt16TimeseriesValue() {
        if (_uInt16TimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = UInt16TimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Short value = null;

            _uInt16TimeseriesValue = new UInt16TimeseriesValueObject( ObjectState.New, UInt16TimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _uInt16TimeseriesValue;
    }

    public UInt32TimeseriesValueObject getUInt32TimeseriesValue() {
        if (_uInt32TimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = UInt32TimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Integer value = null;

            _uInt32TimeseriesValue = new UInt32TimeseriesValueObject( ObjectState.New, UInt32TimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _uInt32TimeseriesValue;
    }

    public UInt64TimeseriesValueObject getUInt64TimeseriesValue() {
        if (_uInt64TimeseriesValue == null) {
            long rowVersion = 0;
            Guid timeseries = UInt64TimeseriesPrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Long value = null;

            _uInt64TimeseriesValue = new UInt64TimeseriesValueObject( ObjectState.New, UInt64TimeseriesValuePrimaryKey, rowVersion, timeseries, timestamp, value );
        }
        return _uInt64TimeseriesValue;
    }

    public VehicleTypeObject getVehicleType() {
        if (_vehicleType == null) {
            long rowVersion = 0;
            String name = "NameVehicleTypeUnitTest";

            _vehicleType = new VehicleTypeObject( ObjectState.New, VehicleTypePrimaryKey, rowVersion, name );
        }
        return _vehicleType;
    }

    public VesselTypeObject getVesselType() {
        if (_vesselType == null) {
            long rowVersion = 0;
            String name = "NameVesselTypeUnitTest";
            int code = 0;

            _vesselType = new VesselTypeObject( ObjectState.New, VesselTypePrimaryKey, rowVersion, name, code );
        }
        return _vesselType;
    }

    public ViewObject getView() {
        if (_view == null) {
            long rowVersion = 0;
            String name = "NameViewUnitTest";
            Guid latitudeTimeseries = null;
            Guid longitudeTimeseries = null;
            Guid zoomLevelTimeseries = null;

            _view = new ViewObject( ObjectState.New, ViewPrimaryKey, rowVersion, name, latitudeTimeseries, longitudeTimeseries, zoomLevelTimeseries );
        }
        return _view;
    }

    public ViewCameraLinkObject getViewCameraLink() {
        if (_viewCameraLink == null) {
            long rowVersion = 0;
            Guid view = ViewPrimaryKey;
            Guid camera = CameraDevicePrimaryKey;
            DateTime start = new DateTime(2025,10,18,9,0,0);
            DateTime end = null;

            _viewCameraLink = new ViewCameraLinkObject( ObjectState.New, ViewCameraLinkPrimaryKey, rowVersion, view, camera, start, end );
        }
        return _viewCameraLink;
    }

    public ViewTrackerLinkObject getViewTrackerLink() {
        if (_viewTrackerLink == null) {
            long rowVersion = 0;
            Guid view = ViewPrimaryKey;
            Guid tracker = AisDevicePrimaryKey;
            DateTime start = new DateTime(2025,10,18,9,0,0);
            DateTime end = null;

            _viewTrackerLink = new ViewTrackerLinkObject( ObjectState.New, ViewTrackerLinkPrimaryKey, rowVersion, view, tracker, start, end );
        }
        return _viewTrackerLink;
    }

    public WeatherStationCommandObject getWeatherStationCommand() {
        if (_weatherStationCommand == null) {
            long rowVersion = 0;
            Guid weatherStation = WeatherStationDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            int deviceCommandSourceType = DeviceCommandSourceType.Unknown;
            Guid deviceCommandSourceId = new Guid();
            Guid reply = null;

            _weatherStationCommand = new WeatherStationCommandObject( ObjectState.New, WeatherStationCommandPrimaryKey, rowVersion, weatherStation, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        }
        return _weatherStationCommand;
    }

    public WeatherStationCommandReplyObject getWeatherStationCommandReply() {
        if (_weatherStationCommandReply == null) {
            long rowVersion = 0;
            Guid weatherStation = WeatherStationDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            Guid command = null;
            int status = DeviceCommandReplyStatus.Unknown;
            String message = "MessageWeatherStationCommandReplyUnitTest";

            _weatherStationCommandReply = new WeatherStationCommandReplyObject( ObjectState.New, WeatherStationCommandReplyPrimaryKey, rowVersion, weatherStation, timestamp, command, status, message );
        }
        return _weatherStationCommandReply;
    }

    public WeatherStationConfigurationObject getWeatherStationConfiguration() {
        if (_weatherStationConfiguration == null) {
            long rowVersion = 0;
            Guid weatherStation = WeatherStationDevicePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            TimeSpan noDataTimeOut = new TimeSpan();
            TimeSpan sendInterval = new TimeSpan();
            double latitude = 0.0;
            double longitude = 0.0;
            double gyroOffset = 0.0;
            boolean enableAveraging = false;
            TimeSpan averagingInterval = new TimeSpan();

            _weatherStationConfiguration = new WeatherStationConfigurationObject( ObjectState.New, WeatherStationConfigurationPrimaryKey, rowVersion, weatherStation, timestamp, noDataTimeOut, sendInterval, latitude, longitude, gyroOffset, enableAveraging, averagingInterval );
        }
        return _weatherStationConfiguration;
    }

    public CircularZoneObject getCircularZone() {
        if (_circularZone == null) {
            long rowVersion = 0;
            String name = "NameCircularZoneUnitTest";
            double longitude = 0.0;
            double latitude = 0.0;
            int alarmType = ZoneAlarmType.None;
            TimeSpan alarmTime = new TimeSpan();
            TimeSpan radarTrackMinimumLifetime = new TimeSpan();
            double speed = 0.0;
            int strokeColor = 0;
            int fillColor = 0;
            double radius = 0.0;

            _circularZone = new CircularZoneObject( ObjectState.New, CircularZonePrimaryKey, rowVersion, name, longitude, latitude, alarmType, alarmTime, radarTrackMinimumLifetime, speed, strokeColor, fillColor, radius );
        }
        return _circularZone;
    }

    public PolygonZoneObject getPolygonZone() {
        if (_polygonZone == null) {
            long rowVersion = 0;
            String name = "NamePolygonZoneUnitTest";
            double longitude = 0.0;
            double latitude = 0.0;
            int alarmType = ZoneAlarmType.None;
            TimeSpan alarmTime = new TimeSpan();
            TimeSpan radarTrackMinimumLifetime = new TimeSpan();
            double speed = 0.0;
            int strokeColor = 0;
            int fillColor = 0;
            byte[] polygon = new byte[0];

            _polygonZone = new PolygonZoneObject( ObjectState.New, PolygonZonePrimaryKey, rowVersion, name, longitude, latitude, alarmType, alarmTime, radarTrackMinimumLifetime, speed, strokeColor, fillColor, polygon );
        }
        return _polygonZone;
    }

    public ZoneExceptionsObject getZoneExceptions() {
        if (_zoneExceptions == null) {
            long rowVersion = 0;
            Guid zone = CircularZonePrimaryKey;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);

            _zoneExceptions = new ZoneExceptionsObject( ObjectState.New, ZoneExceptionsPrimaryKey, rowVersion, zone, timestamp );
        }
        return _zoneExceptions;
    }

    public ZoneExceptionsVesselLinkObject getZoneExceptionsVesselLink() {
        if (_zoneExceptionsVesselLink == null) {
            long rowVersion = 0;
            Guid zoneExceptions = ZoneExceptionsPrimaryKey;
            Guid vessel = VesselPrimaryKey;

            _zoneExceptionsVesselLink = new ZoneExceptionsVesselLinkObject( ObjectState.New, ZoneExceptionsVesselLinkPrimaryKey, rowVersion, zoneExceptions, vessel );
        }
        return _zoneExceptionsVesselLink;
    }

    public ZoneTrackAlarmObject getZoneTrackAlarm() {
        if (_zoneTrackAlarm == null) {
            long rowVersion = 0;
            Guid track = TrackPrimaryKey;
            Guid zone = CircularZonePrimaryKey;
            Guid radarTrack = null;
            DateTime timestamp = new DateTime(2025,10,18,9,0,0);
            double latitude = 0.0;
            double longitude = 0.0;
            double speed = 0.0;
            Double course = null;
            Double heading = null;
            double enterLatitude = 0.0;
            double enterLongitude = 0.0;
            Double leaveLatitude = null;
            Double leaveLongitude = null;

            _zoneTrackAlarm = new ZoneTrackAlarmObject( ObjectState.New, ZoneTrackAlarmPrimaryKey, rowVersion, track, zone, radarTrack, timestamp, latitude, longitude, speed, course, heading, enterLatitude, enterLongitude, leaveLatitude, leaveLongitude );
        }
        return _zoneTrackAlarm;
    }


    public AbstractDataObjectWithGuidKey[] getDataObjects() {
        AbstractDataObjectWithGuidKey[] result = {
            getAircraftType( ),
            getBaseStationType( ),
            getCatalog( ),
            getElement( ),
            getCollectionInfo( ),
            getCountry( ),
            getCursorInfo( ),
            getDeviceHost( ),
            getFacilityType( ),
            getCallsign( ),
            getInternationalMaritimeOrganizationNumber( ),
            getMaritimeMobileServiceIdentity( ),
            getName( ),
            getBaseStation( ),
            getFacility( ),
            getAircraft( ),
            getAisAidToNavigation( ),
            getVehicle( ),
            getVessel( ),
            getLogApplication( ),
            getLogHost( ),
            getLogLocation( ),
            getMapInfo( ),
            getMapServiceOptions( ),
            getMediaService( ),
            getProcessTrackValueResult( ),
            getSecurityDomain( ),
            getBinaryTimeseries( ),
            getBooleanTimeseries( ),
            getAisAidToNavigationOffPositionTimeseries( ),
            getDeviceEnabledTimeseries( ),
            getRadarAutomaticSensitivityTimeControlTimeseries( ),
            getRadarBlankSector1Timeseries( ),
            getRadarBlankSector2Timeseries( ),
            getRadarEnableAutomaticFrequencyControlTimeseries( ),
            getRadarEnableFastTimeConstantTimeseries( ),
            getRadarEnableSensitivityTimeControlTimeseries( ),
            getRadarPowerOnTimeseries( ),
            getRadarSaveSettingsTimeseries( ),
            getRadarTrackingTimeseries( ),
            getMediaProxySessionEnabledTimeseries( ),
            getMediaServiceEnabledTimeseries( ),
            getByteTimeseries( ),
            getDateTimeTimeseries( ),
            getDoubleTimeseries( ),
            getGNSSAltitudeTimeseries( ),
            getGNSSLatitudeTimeseries( ),
            getGNSSLongitudeTimeseries( ),
            getGyroCourseTimeseries( ),
            getGyroHeadingMagneticNorthTimeseries( ),
            getGyroHeadingTrueNorthTimeseries( ),
            getGyroPitchTimeseries( ),
            getGyroRateOfTurnTimeseries( ),
            getGyroRollTimeseries( ),
            getGyroSpeedTimeseries( ),
            getRadarLatitudeTimeseries( ),
            getRadarLongitudeTimeseries( ),
            getRadomeDewPointTimeseries( ),
            getRadomePressureTimeseries( ),
            getRadomeTemperatureTimeseries( ),
            getVesselDraughtTimeseries( ),
            getViewLatitudeTimeseries( ),
            getViewLongitudeTimeseries( ),
            getViewZoomLevelTimeseries( ),
            getWeatherStationAbsoluteHumidityTimeseries( ),
            getWeatherStationAirTemperatureTimeseries( ),
            getWeatherStationBarometricPressureTimeseries( ),
            getWeatherStationDewPointTimeseries( ),
            getWeatherStationRelativeHumidityTimeseries( ),
            getWeatherStationWaterTemperatureTimeseries( ),
            getWeatherStationWindDirectionTimeseries( ),
            getWeatherStationWindSpeedTimeseries( ),
            getGeoPosition2DTimeseries( ),
            getAisAidToNavigationPositionTimeseries( ),
            getGeoPosition3DTimeseries( ),
            getGuidTimeseries( ),
            getInt16Timeseries( ),
            getInt32Timeseries( ),
            getRadarAzimuthOffsetTimeseries( ),
            getRadarFastTimeConstantLevelTimeseries( ),
            getRadarFastTimeConstantModeTimeseries( ),
            getRadarPulseTimeseries( ),
            getRadarSector1EndTimeseries( ),
            getRadarSector1StartTimeseries( ),
            getRadarSector2EndTimeseries( ),
            getRadarSector2StartTimeseries( ),
            getRadarSensitivityTimeControlLevelTimeseries( ),
            getRadarTuningTimeseries( ),
            getVesselPersonsOnBoardTimeseries( ),
            getInt64Timeseries( ),
            getPosition2DTimeseries( ),
            getPosition3DTimeseries( ),
            getReferenceTimeseries( ),
            getSByteTimeseries( ),
            getSingleTimeseries( ),
            getStringTimeseries( ),
            getTimeSpanTimeseries( ),
            getUInt16Timeseries( ),
            getUInt32Timeseries( ),
            getRadomeStatusTimeseries( ),
            getUInt64Timeseries( ),
            getTimeseriesCatalog( ),
            getTimeseriesInfo( ),
            getTrackInfo( ),
            getTrackingServiceOptions( ),
            getVehicleType( ),
            getVesselType( ),
            getView( ),
            getCircularZone( ),
            getPolygonZone( ),
            getMaritimeIdentificationDigits( ),
            getDeviceHostConfiguration( ),
            getCameraDevice( ),
            getGNSSDevice( ),
            getGyroDevice( ),
            getLineInputDevice( ),
            getOilSpillDetectorDevice( ),
            getRadioDevice( ),
            getRadomeDevice( ),
            getAisDevice( ),
            getRadarDevice( ),
            getWeatherStationDevice( ),
            getLogApplicationConfiguration( ),
            getLogProcess( ),
            getLogHostConfiguration( ),
            getMediaProxySession( ),
            getMediaServiceOptions( ),
            getSecurityLogin( ),
            getSecurityRole( ),
            getBinaryTimeseriesValue( ),
            getBooleanTimeseriesValue( ),
            getByteTimeseriesValue( ),
            getDateTimeTimeseriesValue( ),
            getDoubleTimeseriesValue( ),
            getGeoPosition2DTimeseriesValue( ),
            getGeoPosition3DTimeseriesValue( ),
            getGuidTimeseriesValue( ),
            getInt16TimeseriesValue( ),
            getInt32TimeseriesValue( ),
            getInt64TimeseriesValue( ),
            getPosition2DTimeseriesValue( ),
            getPosition3DTimeseriesValue( ),
            getReferenceTimeseriesValue( ),
            getSByteTimeseriesValue( ),
            getSingleTimeseriesValue( ),
            getStringTimeseriesValue( ),
            getTimeSpanTimeseriesValue( ),
            getUInt16TimeseriesValue( ),
            getUInt32TimeseriesValue( ),
            getUInt64TimeseriesValue( ),
            getBookmark( ),
            getZoneExceptions( ),
            getCameraCommand( ),
            getCameraCommandAbsoluteMove( ),
            getCameraCommandAdjustPanTiltZoom( ),
            getCameraCommandContinuousMove( ),
            getCameraCommandGeoMove( ),
            getCameraCommandRelativeMove( ),
            getCameraCommandReleasePTZOwnership( ),
            getCameraCommandRequestPTZOwnership( ),
            getCameraCommandSetAutoFocus( ),
            getCameraCommandSetBlackAndWhite( ),
            getCameraCommandSetFollowed( ),
            getCameraCommandSetInfraRedLamp( ),
            getCameraCommandSetWasher( ),
            getCameraCommandSetWiper( ),
            getCameraCommandStop( ),
            getCameraCommandReply( ),
            getCameraConfiguration( ),
            getCameraPanCalibration( ),
            getCameraStatus( ),
            getCameraTiltCalibration( ),
            getCameraZoomCalibration( ),
            getViewCameraLink( ),
            getGNSSDeviceCommand( ),
            getGNSSDeviceCommandReply( ),
            getGNSSDeviceConfiguration( ),
            getGyroDeviceCommand( ),
            getGyroDeviceCommandReply( ),
            getGyroDeviceConfiguration( ),
            getLineInputDeviceCommand( ),
            getLineInputDeviceCommandReply( ),
            getLineInputDeviceConfiguration( ),
            getLineInputMessageRouting( ),
            getLineInputWhiteListEntry( ),
            getOilSpill( ),
            getOilSpillDetectorCommand( ),
            getOilSpillDetectorCommandReply( ),
            getOilSpillDetectorConfiguration( ),
            getRadioCommand( ),
            getRadioCommandReply( ),
            getRadioConfiguration( ),
            getRadomeCommand( ),
            getRadomeCommandReply( ),
            getRadomeConfiguration( ),
            getAidToNavigationReportMessage( ),
            getAisAddressedSafetyRelatedMessage( ),
            getAisBaseStationReportMessage( ),
            getAisBinaryAcknowledgeMessage( ),
            getAisBinaryAddressedMessage( ),
            getAisBinaryBroadcastMessage( ),
            getAisDataLinkManagementMessage( ),
            getAisExtendedClassBCsPositionReportMessage( ),
            getAisInterrogationMessage( ),
            getAisPositionReportClassAAssignedScheduleMessage( ),
            getAisPositionReportClassAMessage( ),
            getAisPositionReportClassAResponseToInterrogationMessage( ),
            getAisPositionReportForLongRangeApplicationsMessage( ),
            getAisSafetyRelatedAcknowledgmentMessage( ),
            getAisStandardClassBCsPositionReportMessage( ),
            getAisStandardSarAircraftPositionReportMessage( ),
            getAisStaticAndVoyageRelatedDataMessage( ),
            getAisStaticDataReportMessage( ),
            getAisStaticDataReportPartAMessage( ),
            getAisStaticDataReportPartBMessage( ),
            getAisUtcAndDateInquiryMessage( ),
            getAisUtcAndDateResponseMessage( ),
            getAisDeviceCommand( ),
            getAisDeviceCommandReply( ),
            getAisDeviceConfiguration( ),
            getAisDeviceRawMessage( ),
            getAisDeviceRawSentence( ),
            getRadarAlarmStatus( ),
            getRadarCommand( ),
            getRadarCommandGetStatus( ),
            getRadarCommandReply( ),
            getRadarCommandReplyGetStatus( ),
            getRadarConfiguration( ),
            getRadarImage( ),
            getRadarRawTrackTable( ),
            getRadarStatus( ),
            getTrack( ),
            getTrack3D( ),
            getTrackerFilterParameters( ),
            getViewTrackerLink( ),
            getItemIdentityLink( ),
            getItemParentChildLink( ),
            getMapElement( ),
            getWeatherStationCommand( ),
            getWeatherStationCommandReply( ),
            getWeatherStationConfiguration( ),
            getLogThread( ),
            getMediaProxySessionFile( ),
            getMediaProxySessionOptions( ),
            getSecurityLoginSession( ),
            getSecurityIdentifierRoleLink( ),
            getSecurityPermission( ),
            getZoneExceptionsVesselLink( ),
            getCameraPanCalibrationValue( ),
            getCameraTiltCalibrationValue( ),
            getCameraZoomCalibrationValue( ),
            getLineInputMessageRoutingDestination( ),
            getTrackValue( ),
            getZoneTrackAlarm( ),
            getTrackableItemTrackLink( ),
            getTrackLink( ),
            getTrackValue3D( ),
            getTrackerFilterParametersConfiguration( ),
            getLogRecord( ),
            getLogTraceEntry( ),
            getAlarmStateChange( ),
            getElementType( ),
            getNamespace( ),
            getBinaryProperty( ),
            getBooleanProperty( ),
            getByteProperty( ),
            getDateTimeProperty( ),
            getDoubleProperty( ),
            getGuidProperty( ),
            getInt16Property( ),
            getInt32Property( ),
            getInt64Property( ),
            getReferenceProperty( ),
            getSByteProperty( ),
            getSingleProperty( ),
            getStringProperty( ),
            getBinaryTimeseriesProperty( ),
            getBooleanTimeseriesProperty( ),
            getByteTimeseriesProperty( ),
            getDateTimeTimeseriesProperty( ),
            getDoubleTimeseriesProperty( ),
            getGuidTimeseriesProperty( ),
            getInt16TimeseriesProperty( ),
            getInt32TimeseriesProperty( ),
            getInt64TimeseriesProperty( ),
            getReferenceTimeseriesProperty( ),
            getSByteTimeseriesProperty( ),
            getSingleTimeseriesProperty( ),
            getStringTimeseriesProperty( ),
            getTimeSpanTimeseriesProperty( ),
            getUInt16TimeseriesProperty( ),
            getUInt32TimeseriesProperty( ),
            getUInt64TimeseriesProperty( ),
            getTimeSpanProperty( ),
            getUInt16Property( ),
            getUInt32Property( ),
            getUInt64Property( ),
            getBinaryPropertyDefinition( ),
            getBooleanPropertyDefinition( ),
            getBytePropertyDefinition( ),
            getDateTimePropertyDefinition( ),
            getDoublePropertyDefinition( ),
            getGuidPropertyDefinition( ),
            getInt16PropertyDefinition( ),
            getInt32PropertyDefinition( ),
            getInt64PropertyDefinition( ),
            getReferencePropertyDefinition( ),
            getSBytePropertyDefinition( ),
            getSinglePropertyDefinition( ),
            getStringPropertyDefinition( ),
            getBinaryTimeseriesPropertyDefinition( ),
            getBooleanTimeseriesPropertyDefinition( ),
            getByteTimeseriesPropertyDefinition( ),
            getDateTimeTimeseriesPropertyDefinition( ),
            getDoubleTimeseriesPropertyDefinition( ),
            getGuidTimeseriesPropertyDefinition( ),
            getInt16TimeseriesPropertyDefinition( ),
            getInt32TimeseriesPropertyDefinition( ),
            getInt64TimeseriesPropertyDefinition( ),
            getReferenceTimeseriesPropertyDefinition( ),
            getSByteTimeseriesPropertyDefinition( ),
            getSingleTimeseriesPropertyDefinition( ),
            getStringTimeseriesPropertyDefinition( ),
            getTimeSpanTimeseriesPropertyDefinition( ),
            getUInt16TimeseriesPropertyDefinition( ),
            getUInt32TimeseriesPropertyDefinition( ),
            getUInt64TimeseriesPropertyDefinition( ),
            getTimeSpanPropertyDefinition( ),
            getUInt16PropertyDefinition( ),
            getUInt32PropertyDefinition( ),
            getUInt64PropertyDefinition( )

        };
        return result;
    }

/*
AircraftType
    <no dependencies>
BaseStationType
    <no dependencies>
CatalogElement is abstract
    <no dependencies>
Catalog
    <no dependencies>
Element
    <no dependencies>
CollectionInfo
    <no dependencies>
Country
    <no dependencies>
CursorInfo
    <no dependencies>
DeviceHost
    <no dependencies>
FacilityType
    <no dependencies>
Identity is abstract
    <no dependencies>
Callsign
    <no dependencies>
InternationalMaritimeOrganizationNumber
    <no dependencies>
MaritimeMobileServiceIdentity
    <no dependencies>
Name
    <no dependencies>
Item is abstract
    <no dependencies>
BaseStation
    <no dependencies>
Facility
    <no dependencies>
TrackableItem is abstract
    <no dependencies>
Aircraft
    <no dependencies>
AisAidToNavigation
    <no dependencies>
Vehicle
    <no dependencies>
Vessel
    <no dependencies>
LogApplication
    <no dependencies>
LogHost
    <no dependencies>
LogLocation
    <no dependencies>
MapInfo
    <no dependencies>
MapServiceOptions
    <no dependencies>
MediaService
    <no dependencies>
ProcessTrackValueResult
    <no dependencies>
SecurityDomain
    <no dependencies>
TimeseriesCatalogElement is abstract
    <no dependencies>
Timeseries is abstract
    <no dependencies>
BinaryTimeseries
    <no dependencies>
BooleanTimeseries
    <no dependencies>
AisAidToNavigationOffPositionTimeseries
    <no dependencies>
DeviceEnabledTimeseries
    <no dependencies>
RadarAutomaticSensitivityTimeControlTimeseries
    <no dependencies>
RadarBlankSector1Timeseries
    <no dependencies>
RadarBlankSector2Timeseries
    <no dependencies>
RadarEnableAutomaticFrequencyControlTimeseries
    <no dependencies>
RadarEnableFastTimeConstantTimeseries
    <no dependencies>
RadarEnableSensitivityTimeControlTimeseries
    <no dependencies>
RadarPowerOnTimeseries
    <no dependencies>
RadarSaveSettingsTimeseries
    <no dependencies>
RadarTrackingTimeseries
    <no dependencies>
MediaProxySessionEnabledTimeseries
    <no dependencies>
MediaServiceEnabledTimeseries
    <no dependencies>
ByteTimeseries
    <no dependencies>
DateTimeTimeseries
    <no dependencies>
DoubleTimeseries
    <no dependencies>
GNSSAltitudeTimeseries
    <no dependencies>
GNSSLatitudeTimeseries
    <no dependencies>
GNSSLongitudeTimeseries
    <no dependencies>
GyroCourseTimeseries
    <no dependencies>
GyroHeadingMagneticNorthTimeseries
    <no dependencies>
GyroHeadingTrueNorthTimeseries
    <no dependencies>
GyroPitchTimeseries
    <no dependencies>
GyroRateOfTurnTimeseries
    <no dependencies>
GyroRollTimeseries
    <no dependencies>
GyroSpeedTimeseries
    <no dependencies>
RadarLatitudeTimeseries
    <no dependencies>
RadarLongitudeTimeseries
    <no dependencies>
RadomeDewPointTimeseries
    <no dependencies>
RadomePressureTimeseries
    <no dependencies>
RadomeTemperatureTimeseries
    <no dependencies>
VesselDraughtTimeseries
    <no dependencies>
ViewLatitudeTimeseries
    <no dependencies>
ViewLongitudeTimeseries
    <no dependencies>
ViewZoomLevelTimeseries
    <no dependencies>
WeatherStationAbsoluteHumidityTimeseries
    <no dependencies>
WeatherStationAirTemperatureTimeseries
    <no dependencies>
WeatherStationBarometricPressureTimeseries
    <no dependencies>
WeatherStationDewPointTimeseries
    <no dependencies>
WeatherStationRelativeHumidityTimeseries
    <no dependencies>
WeatherStationWaterTemperatureTimeseries
    <no dependencies>
WeatherStationWindDirectionTimeseries
    <no dependencies>
WeatherStationWindSpeedTimeseries
    <no dependencies>
GeoPosition2DTimeseries
    <no dependencies>
AisAidToNavigationPositionTimeseries
    <no dependencies>
GeoPosition3DTimeseries
    <no dependencies>
GuidTimeseries
    <no dependencies>
Int16Timeseries
    <no dependencies>
Int32Timeseries
    <no dependencies>
RadarAzimuthOffsetTimeseries
    <no dependencies>
RadarFastTimeConstantLevelTimeseries
    <no dependencies>
RadarFastTimeConstantModeTimeseries
    <no dependencies>
RadarPulseTimeseries
    <no dependencies>
RadarSector1EndTimeseries
    <no dependencies>
RadarSector1StartTimeseries
    <no dependencies>
RadarSector2EndTimeseries
    <no dependencies>
RadarSector2StartTimeseries
    <no dependencies>
RadarSensitivityTimeControlLevelTimeseries
    <no dependencies>
RadarTuningTimeseries
    <no dependencies>
VesselPersonsOnBoardTimeseries
    <no dependencies>
Int64Timeseries
    <no dependencies>
Position2DTimeseries
    <no dependencies>
Position3DTimeseries
    <no dependencies>
ReferenceTimeseries
    <no dependencies>
SByteTimeseries
    <no dependencies>
SingleTimeseries
    <no dependencies>
StringTimeseries
    <no dependencies>
TimeSpanTimeseries
    <no dependencies>
UInt16Timeseries
    <no dependencies>
UInt32Timeseries
    <no dependencies>
RadomeStatusTimeseries
    <no dependencies>
UInt64Timeseries
    <no dependencies>
TimeseriesCatalog
    <no dependencies>
TimeseriesInfo
    <no dependencies>
TrackInfo
    <no dependencies>
TrackingServiceOptions
    <no dependencies>
VehicleType
    <no dependencies>
VesselType
    <no dependencies>
View
    <no dependencies>
Zone is abstract
    <no dependencies>
CircularZone
    <no dependencies>
PolygonZone
    <no dependencies>
MaritimeIdentificationDigits
    Country
DeviceHostConfiguration
    DeviceHost
Device is abstract
    DeviceHost
CameraDevice
    DeviceHost
GNSSDevice
    DeviceHost
GyroDevice
    DeviceHost
LineInputDevice
    DeviceHost
OilSpillDetectorDevice
    DeviceHost
RadioDevice
    DeviceHost
RadomeDevice
    DeviceHost
TrackerDevice is abstract
    DeviceHost
AisDevice
    DeviceHost
RadarDevice
    DeviceHost
WeatherStationDevice
    DeviceHost
LogApplicationConfiguration
    LogApplication
LogProcess
    LogApplication
LogHostConfiguration
    LogHost
MediaProxySession
    MediaService
MediaServiceOptions
    MediaService
SecurityIdentifier is abstract
    SecurityDomain
SecurityLogin
    SecurityDomain
SecurityRole
    SecurityDomain
BinaryTimeseriesValue
    BinaryTimeseries
BooleanTimeseriesValue
    RadarAutomaticSensitivityTimeControlTimeseries
    BooleanTimeseries
    RadarBlankSector1Timeseries
    AisAidToNavigationOffPositionTimeseries
    RadarBlankSector2Timeseries
    DeviceEnabledTimeseries
    MediaProxySessionEnabledTimeseries
    MediaServiceEnabledTimeseries
    RadarEnableAutomaticFrequencyControlTimeseries
    RadarEnableFastTimeConstantTimeseries
    RadarEnableSensitivityTimeControlTimeseries
    RadarPowerOnTimeseries
    RadarSaveSettingsTimeseries
    RadarTrackingTimeseries
ByteTimeseriesValue
    ByteTimeseries
DateTimeTimeseriesValue
    DateTimeTimeseries
DoubleTimeseriesValue
    GyroPitchTimeseries
    GyroHeadingMagneticNorthTimeseries
    DoubleTimeseries
    GNSSAltitudeTimeseries
    GyroHeadingTrueNorthTimeseries
    GNSSLatitudeTimeseries
    GyroCourseTimeseries
    GNSSLongitudeTimeseries
    RadomeTemperatureTimeseries
    GyroRateOfTurnTimeseries
    RadomePressureTimeseries
    GyroRollTimeseries
    GyroSpeedTimeseries
    RadarLatitudeTimeseries
    RadomeDewPointTimeseries
    RadarLongitudeTimeseries
    WeatherStationWindDirectionTimeseries
    VesselDraughtTimeseries
    WeatherStationDewPointTimeseries
    ViewLatitudeTimeseries
    ViewLongitudeTimeseries
    ViewZoomLevelTimeseries
    WeatherStationAbsoluteHumidityTimeseries
    WeatherStationAirTemperatureTimeseries
    WeatherStationBarometricPressureTimeseries
    WeatherStationRelativeHumidityTimeseries
    WeatherStationWaterTemperatureTimeseries
    WeatherStationWindSpeedTimeseries
GeoPosition2DTimeseriesValue
    GeoPosition2DTimeseries
    AisAidToNavigationPositionTimeseries
GeoPosition3DTimeseriesValue
    GeoPosition3DTimeseries
GuidTimeseriesValue
    GuidTimeseries
Int16TimeseriesValue
    Int16Timeseries
Int32TimeseriesValue
    Int32Timeseries
    RadarSector1EndTimeseries
    RadarAzimuthOffsetTimeseries
    RadarSector2StartTimeseries
    RadarFastTimeConstantModeTimeseries
    RadarFastTimeConstantLevelTimeseries
    RadarPulseTimeseries
    RadarSector1StartTimeseries
    RadarSector2EndTimeseries
    RadarSensitivityTimeControlLevelTimeseries
    RadarTuningTimeseries
    VesselPersonsOnBoardTimeseries
Int64TimeseriesValue
    Int64Timeseries
Position2DTimeseriesValue
    Position2DTimeseries
Position3DTimeseriesValue
    Position3DTimeseries
ReferenceTimeseriesValue
    ReferenceTimeseries
    Element
SByteTimeseriesValue
    SByteTimeseries
SingleTimeseriesValue
    SingleTimeseries
StringTimeseriesValue
    StringTimeseries
TimeSpanTimeseriesValue
    TimeSpanTimeseries
UInt16TimeseriesValue
    UInt16Timeseries
UInt32TimeseriesValue
    UInt32Timeseries
    RadomeStatusTimeseries
UInt64TimeseriesValue
    UInt64Timeseries
Bookmark
    View
ZoneExceptions
    CircularZone
    PolygonZone
CameraCommand
    CameraDevice
CameraCommandAbsoluteMove
    CameraDevice
CameraCommandAdjustPanTiltZoom
    CameraDevice
CameraCommandContinuousMove
    CameraDevice
CameraCommandGeoMove
    CameraDevice
CameraCommandRelativeMove
    CameraDevice
CameraCommandReleasePTZOwnership
    CameraDevice
CameraCommandRequestPTZOwnership
    CameraDevice
CameraCommandSetAutoFocus
    CameraDevice
CameraCommandSetBlackAndWhite
    CameraDevice
CameraCommandSetFollowed
    CameraDevice
CameraCommandSetInfraRedLamp
    CameraDevice
CameraCommandSetWasher
    CameraDevice
CameraCommandSetWiper
    CameraDevice
CameraCommandStop
    CameraDevice
CameraCommandReply
    CameraDevice
CameraConfiguration
    CameraDevice
CameraPanCalibration
    CameraDevice
CameraStatus
    CameraDevice
CameraTiltCalibration
    CameraDevice
CameraZoomCalibration
    CameraDevice
ViewCameraLink
    View
    CameraDevice
GNSSDeviceCommand
    GNSSDevice
GNSSDeviceCommandReply
    GNSSDevice
GNSSDeviceConfiguration
    GNSSDevice
GyroDeviceCommand
    GyroDevice
GyroDeviceCommandReply
    GyroDevice
GyroDeviceConfiguration
    GyroDevice
LineInputDeviceCommand
    LineInputDevice
LineInputDeviceCommandReply
    LineInputDevice
LineInputDeviceConfiguration
    LineInputDevice
LineInputMessageRouting
    LineInputDevice
LineInputWhiteListEntry
    LineInputDevice
OilSpill
    OilSpillDetectorDevice
OilSpillDetectorCommand
    OilSpillDetectorDevice
OilSpillDetectorCommandReply
    OilSpillDetectorDevice
OilSpillDetectorConfiguration
    OilSpillDetectorDevice
RadioCommand
    RadioDevice
RadioCommandReply
    RadioDevice
RadioConfiguration
    RadioDevice
RadomeCommand
    RadomeDevice
RadomeCommandReply
    RadomeDevice
RadomeConfiguration
    RadomeDevice
AisMessage is abstract
    AisDevice
AidToNavigationReportMessage
    AisDevice
AisAddressedSafetyRelatedMessage
    AisDevice
AisBaseStationReportMessage
    AisDevice
AisBinaryAcknowledgeMessage
    AisDevice
AisBinaryAddressedMessage
    AisDevice
AisBinaryBroadcastMessage
    AisDevice
AisDataLinkManagementMessage
    AisDevice
AisExtendedClassBCsPositionReportMessage
    AisDevice
AisInterrogationMessage
    AisDevice
AisPositionReportClassAMessageBase is abstract
    AisDevice
AisPositionReportClassAAssignedScheduleMessage
    AisDevice
AisPositionReportClassAMessage
    AisDevice
AisPositionReportClassAResponseToInterrogationMessage
    AisDevice
AisPositionReportForLongRangeApplicationsMessage
    AisDevice
AisSafetyRelatedAcknowledgmentMessage
    AisDevice
AisStandardClassBCsPositionReportMessage
    AisDevice
AisStandardSarAircraftPositionReportMessage
    AisDevice
AisStaticAndVoyageRelatedDataMessage
    AisDevice
AisStaticDataReportMessage
    AisDevice
AisStaticDataReportPartAMessage
    AisDevice
AisStaticDataReportPartBMessage
    AisDevice
AisUtcAndDateInquiryMessage
    AisDevice
AisUtcAndDateResponseMessage
    AisDevice
AisDeviceCommand
    AisDevice
AisDeviceCommandReply
    AisDevice
AisDeviceConfiguration
    AisDevice
AisDeviceRawMessage
    AisDevice
AisDeviceRawSentence
    AisDevice
RadarAlarmStatus
    RadarDevice
RadarCommand
    RadarDevice
RadarCommandGetStatus
    RadarDevice
RadarCommandReply
    RadarDevice
RadarCommandReplyGetStatus
    RadarDevice
RadarConfiguration
    RadarDevice
RadarImage
    RadarDevice
RadarRawTrackTable
    RadarDevice
RadarStatus
    RadarDevice
TrackBase is abstract
    AisDevice
    RadarDevice
Track
    AisDevice
    RadarDevice
Track3D
    AisDevice
    RadarDevice
TrackerFilterParameters
    AisDevice
    RadarDevice
ViewTrackerLink
    AisDevice
    View
    RadarDevice
ItemIdentityLink
    RadarDevice
    BaseStation
    WeatherStationDevice
    CameraDevice
    MaritimeMobileServiceIdentity
    GNSSDevice
    OilSpillDetectorDevice
    RadomeDevice
    GyroDevice
    LineInputDevice
    RadioDevice
    AisDevice
    Facility
    Aircraft
    AisAidToNavigation
    Vehicle
    Vessel
    Callsign
    InternationalMaritimeOrganizationNumber
    Name
ItemParentChildLink
    RadarDevice
    BaseStation
    WeatherStationDevice
    CameraDevice
    GNSSDevice
    OilSpillDetectorDevice
    RadomeDevice
    GyroDevice
    LineInputDevice
    RadioDevice
    AisDevice
    Facility
    Aircraft
    AisAidToNavigation
    Vehicle
    Vessel
MapElement
    RadarDevice
    BaseStation
    WeatherStationDevice
    CameraDevice
    GNSSDevice
    OilSpillDetectorDevice
    RadomeDevice
    GyroDevice
    LineInputDevice
    RadioDevice
    AisDevice
    Facility
    Aircraft
    AisAidToNavigation
    Vehicle
    Vessel
WeatherStationCommand
    WeatherStationDevice
WeatherStationCommandReply
    WeatherStationDevice
WeatherStationConfiguration
    WeatherStationDevice
LogThread
    LogProcess
MediaProxySessionFile
    MediaProxySession
MediaProxySessionOptions
    MediaProxySession
SecurityLoginSession
    SecurityLogin
SecurityIdentifierRoleLink
    SecurityLogin
    SecurityRole
SecurityPermission
    SecurityLogin
    SecurityRole
ZoneExceptionsVesselLink
    ZoneExceptions
    Vessel
CameraPanCalibrationValue
    CameraPanCalibration
CameraTiltCalibrationValue
    CameraTiltCalibration
CameraZoomCalibrationValue
    CameraZoomCalibration
LineInputMessageRoutingDestination
    LineInputMessageRouting
TrackValue
    Track
ZoneTrackAlarm
    Track
    CircularZone
    PolygonZone
TrackableItemTrackLink
    Track
    Aircraft
    AisAidToNavigation
    Vehicle
    Track3D
    Vessel
TrackLink
    Track
    Track3D
TrackValue3D
    Track3D
TrackerFilterParametersConfiguration
    TrackerFilterParameters
LogRecord
    LogThread
    LogLocation
LogTraceEntry
    LogThread
    LogLocation
AlarmStateChange
    ZoneTrackAlarm
NamespaceElement is abstract
    Namespace
ElementType
    Namespace
Namespace
    Namespace
Property is abstract
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
BinaryProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
BooleanProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
ByteProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
DateTimeProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
DoubleProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
GuidProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
Int16Property
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
Int32Property
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
Int64Property
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
ReferenceProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
SByteProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
SingleProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
StringProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
TimeseriesProperty is abstract
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
BinaryTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
BooleanTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
ByteTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
DateTimeTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
DoubleTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
GuidTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
Int16TimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
Int32TimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
Int64TimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
ReferenceTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
SByteTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
SingleTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
StringTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
TimeSpanTimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
UInt16TimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
UInt32TimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
UInt64TimeseriesProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
TimeSpanProperty
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
UInt16Property
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
UInt32Property
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
UInt64Property
    StringTimeseriesPropertyDefinition
    DateTimePropertyDefinition
    BooleanPropertyDefinition
    SingleTimeseriesPropertyDefinition
    Element
    BinaryPropertyDefinition
    GuidPropertyDefinition
    UInt32PropertyDefinition
    BytePropertyDefinition
    DoublePropertyDefinition
    Int16PropertyDefinition
    ReferencePropertyDefinition
    Int32PropertyDefinition
    Int64PropertyDefinition
    DoubleTimeseriesPropertyDefinition
    BooleanTimeseriesPropertyDefinition
    SBytePropertyDefinition
    SinglePropertyDefinition
    StringPropertyDefinition
    UInt16TimeseriesPropertyDefinition
    BinaryTimeseriesPropertyDefinition
    ByteTimeseriesPropertyDefinition
    DateTimeTimeseriesPropertyDefinition
    GuidTimeseriesPropertyDefinition
    Int16TimeseriesPropertyDefinition
    Int32TimeseriesPropertyDefinition
    Int64TimeseriesPropertyDefinition
    ReferenceTimeseriesPropertyDefinition
    SByteTimeseriesPropertyDefinition
    TimeSpanTimeseriesPropertyDefinition
    UInt32TimeseriesPropertyDefinition
    TimeSpanPropertyDefinition
    UInt64TimeseriesPropertyDefinition
    UInt16PropertyDefinition
    UInt64PropertyDefinition
PropertyDefinition is abstract
    ElementType
BinaryPropertyDefinition
    ElementType
BooleanPropertyDefinition
    ElementType
BytePropertyDefinition
    ElementType
DateTimePropertyDefinition
    ElementType
DoublePropertyDefinition
    ElementType
GuidPropertyDefinition
    ElementType
Int16PropertyDefinition
    ElementType
Int32PropertyDefinition
    ElementType
Int64PropertyDefinition
    ElementType
ReferencePropertyDefinition
    ElementType
SBytePropertyDefinition
    ElementType
SinglePropertyDefinition
    ElementType
StringPropertyDefinition
    ElementType
TimeseriesPropertyDefinition is abstract
    ElementType
BinaryTimeseriesPropertyDefinition
    ElementType
BooleanTimeseriesPropertyDefinition
    ElementType
ByteTimeseriesPropertyDefinition
    ElementType
DateTimeTimeseriesPropertyDefinition
    ElementType
DoubleTimeseriesPropertyDefinition
    ElementType
GuidTimeseriesPropertyDefinition
    ElementType
Int16TimeseriesPropertyDefinition
    ElementType
Int32TimeseriesPropertyDefinition
    ElementType
Int64TimeseriesPropertyDefinition
    ElementType
ReferenceTimeseriesPropertyDefinition
    ElementType
SByteTimeseriesPropertyDefinition
    ElementType
SingleTimeseriesPropertyDefinition
    ElementType
StringTimeseriesPropertyDefinition
    ElementType
TimeSpanTimeseriesPropertyDefinition
    ElementType
UInt16TimeseriesPropertyDefinition
    ElementType
UInt32TimeseriesPropertyDefinition
    ElementType
UInt64TimeseriesPropertyDefinition
    ElementType
TimeSpanPropertyDefinition
    ElementType
UInt16PropertyDefinition
    ElementType
UInt32PropertyDefinition
    ElementType
UInt64PropertyDefinition
    ElementType
*/
}
