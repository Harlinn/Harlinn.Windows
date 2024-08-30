#include "pch.h"

#include "DataTypes.h"


namespace Barrelman::Data
{

    BARRELMAN_EXPORT std::shared_ptr<BaseData<Kind, Guid>> DataFactory( Kind kind )
    {
        std::shared_ptr<BaseData<Kind, Guid>> result;
        switch(kind)
        {
            case Kind::AircraftType:
                result = std::make_shared<AircraftTypeData>( );
                break;
            case Kind::AisDeviceCommand:
                result = std::make_shared<AisDeviceCommandData>( );
                break;
            case Kind::AisDeviceCommandReply:
                result = std::make_shared<AisDeviceCommandReplyData>( );
                break;
            case Kind::AisDeviceConfiguration:
                result = std::make_shared<AisDeviceConfigurationData>( );
                break;
            case Kind::AisDeviceRawMessage:
                result = std::make_shared<AisDeviceRawMessageData>( );
                break;
            case Kind::AisDeviceRawSentence:
                result = std::make_shared<AisDeviceRawSentenceData>( );
                break;
            case Kind::AidToNavigationReportMessage:
                result = std::make_shared<AidToNavigationReportMessageData>( );
                break;
            case Kind::AisAddressedSafetyRelatedMessage:
                result = std::make_shared<AisAddressedSafetyRelatedMessageData>( );
                break;
            case Kind::AisBaseStationReportMessage:
                result = std::make_shared<AisBaseStationReportMessageData>( );
                break;
            case Kind::AisBinaryAcknowledgeMessage:
                result = std::make_shared<AisBinaryAcknowledgeMessageData>( );
                break;
            case Kind::AisBinaryAddressedMessage:
                result = std::make_shared<AisBinaryAddressedMessageData>( );
                break;
            case Kind::AisBinaryBroadcastMessage:
                result = std::make_shared<AisBinaryBroadcastMessageData>( );
                break;
            case Kind::AisDataLinkManagementMessage:
                result = std::make_shared<AisDataLinkManagementMessageData>( );
                break;
            case Kind::AisExtendedClassBCsPositionReportMessage:
                result = std::make_shared<AisExtendedClassBCsPositionReportMessageData>( );
                break;
            case Kind::AisInterrogationMessage:
                result = std::make_shared<AisInterrogationMessageData>( );
                break;
            case Kind::AisPositionReportClassAAssignedScheduleMessage:
                result = std::make_shared<AisPositionReportClassAAssignedScheduleMessageData>( );
                break;
            case Kind::AisPositionReportClassAMessage:
                result = std::make_shared<AisPositionReportClassAMessageData>( );
                break;
            case Kind::AisPositionReportClassAResponseToInterrogationMessage:
                result = std::make_shared<AisPositionReportClassAResponseToInterrogationMessageData>( );
                break;
            case Kind::AisPositionReportForLongRangeApplicationsMessage:
                result = std::make_shared<AisPositionReportForLongRangeApplicationsMessageData>( );
                break;
            case Kind::AisSafetyRelatedAcknowledgmentMessage:
                result = std::make_shared<AisSafetyRelatedAcknowledgmentMessageData>( );
                break;
            case Kind::AisStandardClassBCsPositionReportMessage:
                result = std::make_shared<AisStandardClassBCsPositionReportMessageData>( );
                break;
            case Kind::AisStandardSarAircraftPositionReportMessage:
                result = std::make_shared<AisStandardSarAircraftPositionReportMessageData>( );
                break;
            case Kind::AisStaticAndVoyageRelatedDataMessage:
                result = std::make_shared<AisStaticAndVoyageRelatedDataMessageData>( );
                break;
            case Kind::AisStaticDataReportMessage:
                result = std::make_shared<AisStaticDataReportMessageData>( );
                break;
            case Kind::AisStaticDataReportPartAMessage:
                result = std::make_shared<AisStaticDataReportPartAMessageData>( );
                break;
            case Kind::AisStaticDataReportPartBMessage:
                result = std::make_shared<AisStaticDataReportPartBMessageData>( );
                break;
            case Kind::AisUtcAndDateInquiryMessage:
                result = std::make_shared<AisUtcAndDateInquiryMessageData>( );
                break;
            case Kind::AisUtcAndDateResponseMessage:
                result = std::make_shared<AisUtcAndDateResponseMessageData>( );
                break;
            case Kind::AlarmStateChange:
                result = std::make_shared<AlarmStateChangeData>( );
                break;
            case Kind::BaseStationType:
                result = std::make_shared<BaseStationTypeData>( );
                break;
            case Kind::BinaryTimeseriesValue:
                result = std::make_shared<BinaryTimeseriesValueData>( );
                break;
            case Kind::Bookmark:
                result = std::make_shared<BookmarkData>( );
                break;
            case Kind::BooleanTimeseriesValue:
                result = std::make_shared<BooleanTimeseriesValueData>( );
                break;
            case Kind::ByteTimeseriesValue:
                result = std::make_shared<ByteTimeseriesValueData>( );
                break;
            case Kind::CameraCommand:
                result = std::make_shared<CameraCommandData>( );
                break;
            case Kind::CameraCommandAbsoluteMove:
                result = std::make_shared<CameraCommandAbsoluteMoveData>( );
                break;
            case Kind::CameraCommandAdjustPanTiltZoom:
                result = std::make_shared<CameraCommandAdjustPanTiltZoomData>( );
                break;
            case Kind::CameraCommandContinuousMove:
                result = std::make_shared<CameraCommandContinuousMoveData>( );
                break;
            case Kind::CameraCommandGeoMove:
                result = std::make_shared<CameraCommandGeoMoveData>( );
                break;
            case Kind::CameraCommandRelativeMove:
                result = std::make_shared<CameraCommandRelativeMoveData>( );
                break;
            case Kind::CameraCommandReleasePTZOwnership:
                result = std::make_shared<CameraCommandReleasePTZOwnershipData>( );
                break;
            case Kind::CameraCommandRequestPTZOwnership:
                result = std::make_shared<CameraCommandRequestPTZOwnershipData>( );
                break;
            case Kind::CameraCommandSetAutoFocus:
                result = std::make_shared<CameraCommandSetAutoFocusData>( );
                break;
            case Kind::CameraCommandSetBlackAndWhite:
                result = std::make_shared<CameraCommandSetBlackAndWhiteData>( );
                break;
            case Kind::CameraCommandSetFollowed:
                result = std::make_shared<CameraCommandSetFollowedData>( );
                break;
            case Kind::CameraCommandSetInfraRedLamp:
                result = std::make_shared<CameraCommandSetInfraRedLampData>( );
                break;
            case Kind::CameraCommandSetWasher:
                result = std::make_shared<CameraCommandSetWasherData>( );
                break;
            case Kind::CameraCommandSetWiper:
                result = std::make_shared<CameraCommandSetWiperData>( );
                break;
            case Kind::CameraCommandStop:
                result = std::make_shared<CameraCommandStopData>( );
                break;
            case Kind::CameraCommandReply:
                result = std::make_shared<CameraCommandReplyData>( );
                break;
            case Kind::CameraConfiguration:
                result = std::make_shared<CameraConfigurationData>( );
                break;
            case Kind::CameraPanCalibration:
                result = std::make_shared<CameraPanCalibrationData>( );
                break;
            case Kind::CameraPanCalibrationValue:
                result = std::make_shared<CameraPanCalibrationValueData>( );
                break;
            case Kind::CameraStatus:
                result = std::make_shared<CameraStatusData>( );
                break;
            case Kind::CameraTiltCalibration:
                result = std::make_shared<CameraTiltCalibrationData>( );
                break;
            case Kind::CameraTiltCalibrationValue:
                result = std::make_shared<CameraTiltCalibrationValueData>( );
                break;
            case Kind::CameraZoomCalibration:
                result = std::make_shared<CameraZoomCalibrationData>( );
                break;
            case Kind::CameraZoomCalibrationValue:
                result = std::make_shared<CameraZoomCalibrationValueData>( );
                break;
            case Kind::Catalog:
                result = std::make_shared<CatalogData>( );
                break;
            case Kind::Element:
                result = std::make_shared<ElementData>( );
                break;
            case Kind::CollectionInfo:
                result = std::make_shared<CollectionInfoData>( );
                break;
            case Kind::Country:
                result = std::make_shared<CountryData>( );
                break;
            case Kind::CursorInfo:
                result = std::make_shared<CursorInfoData>( );
                break;
            case Kind::DateTimeTimeseriesValue:
                result = std::make_shared<DateTimeTimeseriesValueData>( );
                break;
            case Kind::DeviceHost:
                result = std::make_shared<DeviceHostData>( );
                break;
            case Kind::DeviceHostConfiguration:
                result = std::make_shared<DeviceHostConfigurationData>( );
                break;
            case Kind::DoubleTimeseriesValue:
                result = std::make_shared<DoubleTimeseriesValueData>( );
                break;
            case Kind::FacilityType:
                result = std::make_shared<FacilityTypeData>( );
                break;
            case Kind::GeoPosition2DTimeseriesValue:
                result = std::make_shared<GeoPosition2DTimeseriesValueData>( );
                break;
            case Kind::GeoPosition3DTimeseriesValue:
                result = std::make_shared<GeoPosition3DTimeseriesValueData>( );
                break;
            case Kind::GNSSDeviceCommand:
                result = std::make_shared<GNSSDeviceCommandData>( );
                break;
            case Kind::GNSSDeviceCommandReply:
                result = std::make_shared<GNSSDeviceCommandReplyData>( );
                break;
            case Kind::GNSSDeviceConfiguration:
                result = std::make_shared<GNSSDeviceConfigurationData>( );
                break;
            case Kind::GuidTimeseriesValue:
                result = std::make_shared<GuidTimeseriesValueData>( );
                break;
            case Kind::GyroDeviceCommand:
                result = std::make_shared<GyroDeviceCommandData>( );
                break;
            case Kind::GyroDeviceCommandReply:
                result = std::make_shared<GyroDeviceCommandReplyData>( );
                break;
            case Kind::GyroDeviceConfiguration:
                result = std::make_shared<GyroDeviceConfigurationData>( );
                break;
            case Kind::Callsign:
                result = std::make_shared<CallsignData>( );
                break;
            case Kind::InternationalMaritimeOrganizationNumber:
                result = std::make_shared<InternationalMaritimeOrganizationNumberData>( );
                break;
            case Kind::MaritimeMobileServiceIdentity:
                result = std::make_shared<MaritimeMobileServiceIdentityData>( );
                break;
            case Kind::Name:
                result = std::make_shared<NameData>( );
                break;
            case Kind::Int16TimeseriesValue:
                result = std::make_shared<Int16TimeseriesValueData>( );
                break;
            case Kind::Int32TimeseriesValue:
                result = std::make_shared<Int32TimeseriesValueData>( );
                break;
            case Kind::Int64TimeseriesValue:
                result = std::make_shared<Int64TimeseriesValueData>( );
                break;
            case Kind::BaseStation:
                result = std::make_shared<BaseStationData>( );
                break;
            case Kind::CameraDevice:
                result = std::make_shared<CameraDeviceData>( );
                break;
            case Kind::GNSSDevice:
                result = std::make_shared<GNSSDeviceData>( );
                break;
            case Kind::GyroDevice:
                result = std::make_shared<GyroDeviceData>( );
                break;
            case Kind::LineInputDevice:
                result = std::make_shared<LineInputDeviceData>( );
                break;
            case Kind::OilSpillDetectorDevice:
                result = std::make_shared<OilSpillDetectorDeviceData>( );
                break;
            case Kind::RadioDevice:
                result = std::make_shared<RadioDeviceData>( );
                break;
            case Kind::RadomeDevice:
                result = std::make_shared<RadomeDeviceData>( );
                break;
            case Kind::AisDevice:
                result = std::make_shared<AisDeviceData>( );
                break;
            case Kind::RadarDevice:
                result = std::make_shared<RadarDeviceData>( );
                break;
            case Kind::WeatherStationDevice:
                result = std::make_shared<WeatherStationDeviceData>( );
                break;
            case Kind::Facility:
                result = std::make_shared<FacilityData>( );
                break;
            case Kind::Aircraft:
                result = std::make_shared<AircraftData>( );
                break;
            case Kind::AisAidToNavigation:
                result = std::make_shared<AisAidToNavigationData>( );
                break;
            case Kind::Vehicle:
                result = std::make_shared<VehicleData>( );
                break;
            case Kind::Vessel:
                result = std::make_shared<VesselData>( );
                break;
            case Kind::ItemIdentityLink:
                result = std::make_shared<ItemIdentityLinkData>( );
                break;
            case Kind::ItemParentChildLink:
                result = std::make_shared<ItemParentChildLinkData>( );
                break;
            case Kind::LineInputDeviceCommand:
                result = std::make_shared<LineInputDeviceCommandData>( );
                break;
            case Kind::LineInputDeviceCommandReply:
                result = std::make_shared<LineInputDeviceCommandReplyData>( );
                break;
            case Kind::LineInputDeviceConfiguration:
                result = std::make_shared<LineInputDeviceConfigurationData>( );
                break;
            case Kind::LineInputMessageRouting:
                result = std::make_shared<LineInputMessageRoutingData>( );
                break;
            case Kind::LineInputMessageRoutingDestination:
                result = std::make_shared<LineInputMessageRoutingDestinationData>( );
                break;
            case Kind::LineInputWhiteListEntry:
                result = std::make_shared<LineInputWhiteListEntryData>( );
                break;
            case Kind::LogApplication:
                result = std::make_shared<LogApplicationData>( );
                break;
            case Kind::LogApplicationConfiguration:
                result = std::make_shared<LogApplicationConfigurationData>( );
                break;
            case Kind::LogHost:
                result = std::make_shared<LogHostData>( );
                break;
            case Kind::LogHostConfiguration:
                result = std::make_shared<LogHostConfigurationData>( );
                break;
            case Kind::LogLocation:
                result = std::make_shared<LogLocationData>( );
                break;
            case Kind::LogProcess:
                result = std::make_shared<LogProcessData>( );
                break;
            case Kind::LogRecord:
                result = std::make_shared<LogRecordData>( );
                break;
            case Kind::LogThread:
                result = std::make_shared<LogThreadData>( );
                break;
            case Kind::LogTraceEntry:
                result = std::make_shared<LogTraceEntryData>( );
                break;
            case Kind::MapElement:
                result = std::make_shared<MapElementData>( );
                break;
            case Kind::MapInfo:
                result = std::make_shared<MapInfoData>( );
                break;
            case Kind::MapServiceOptions:
                result = std::make_shared<MapServiceOptionsData>( );
                break;
            case Kind::MaritimeIdentificationDigits:
                result = std::make_shared<MaritimeIdentificationDigitsData>( );
                break;
            case Kind::MediaProxySession:
                result = std::make_shared<MediaProxySessionData>( );
                break;
            case Kind::MediaProxySessionFile:
                result = std::make_shared<MediaProxySessionFileData>( );
                break;
            case Kind::MediaProxySessionOptions:
                result = std::make_shared<MediaProxySessionOptionsData>( );
                break;
            case Kind::MediaService:
                result = std::make_shared<MediaServiceData>( );
                break;
            case Kind::MediaServiceOptions:
                result = std::make_shared<MediaServiceOptionsData>( );
                break;
            case Kind::ElementType:
                result = std::make_shared<ElementTypeData>( );
                break;
            case Kind::Namespace:
                result = std::make_shared<NamespaceData>( );
                break;
            case Kind::OilSpill:
                result = std::make_shared<OilSpillData>( );
                break;
            case Kind::OilSpillDetectorCommand:
                result = std::make_shared<OilSpillDetectorCommandData>( );
                break;
            case Kind::OilSpillDetectorCommandReply:
                result = std::make_shared<OilSpillDetectorCommandReplyData>( );
                break;
            case Kind::OilSpillDetectorConfiguration:
                result = std::make_shared<OilSpillDetectorConfigurationData>( );
                break;
            case Kind::Position2DTimeseriesValue:
                result = std::make_shared<Position2DTimeseriesValueData>( );
                break;
            case Kind::Position3DTimeseriesValue:
                result = std::make_shared<Position3DTimeseriesValueData>( );
                break;
            case Kind::ProcessTrackValueResult:
                result = std::make_shared<ProcessTrackValueResultData>( );
                break;
            case Kind::BinaryProperty:
                result = std::make_shared<BinaryPropertyData>( );
                break;
            case Kind::BooleanProperty:
                result = std::make_shared<BooleanPropertyData>( );
                break;
            case Kind::ByteProperty:
                result = std::make_shared<BytePropertyData>( );
                break;
            case Kind::DateTimeProperty:
                result = std::make_shared<DateTimePropertyData>( );
                break;
            case Kind::DoubleProperty:
                result = std::make_shared<DoublePropertyData>( );
                break;
            case Kind::GuidProperty:
                result = std::make_shared<GuidPropertyData>( );
                break;
            case Kind::Int16Property:
                result = std::make_shared<Int16PropertyData>( );
                break;
            case Kind::Int32Property:
                result = std::make_shared<Int32PropertyData>( );
                break;
            case Kind::Int64Property:
                result = std::make_shared<Int64PropertyData>( );
                break;
            case Kind::ReferenceProperty:
                result = std::make_shared<ReferencePropertyData>( );
                break;
            case Kind::SByteProperty:
                result = std::make_shared<SBytePropertyData>( );
                break;
            case Kind::SingleProperty:
                result = std::make_shared<SinglePropertyData>( );
                break;
            case Kind::StringProperty:
                result = std::make_shared<StringPropertyData>( );
                break;
            case Kind::BinaryTimeseriesProperty:
                result = std::make_shared<BinaryTimeseriesPropertyData>( );
                break;
            case Kind::BooleanTimeseriesProperty:
                result = std::make_shared<BooleanTimeseriesPropertyData>( );
                break;
            case Kind::ByteTimeseriesProperty:
                result = std::make_shared<ByteTimeseriesPropertyData>( );
                break;
            case Kind::DateTimeTimeseriesProperty:
                result = std::make_shared<DateTimeTimeseriesPropertyData>( );
                break;
            case Kind::DoubleTimeseriesProperty:
                result = std::make_shared<DoubleTimeseriesPropertyData>( );
                break;
            case Kind::GuidTimeseriesProperty:
                result = std::make_shared<GuidTimeseriesPropertyData>( );
                break;
            case Kind::Int16TimeseriesProperty:
                result = std::make_shared<Int16TimeseriesPropertyData>( );
                break;
            case Kind::Int32TimeseriesProperty:
                result = std::make_shared<Int32TimeseriesPropertyData>( );
                break;
            case Kind::Int64TimeseriesProperty:
                result = std::make_shared<Int64TimeseriesPropertyData>( );
                break;
            case Kind::ReferenceTimeseriesProperty:
                result = std::make_shared<ReferenceTimeseriesPropertyData>( );
                break;
            case Kind::SByteTimeseriesProperty:
                result = std::make_shared<SByteTimeseriesPropertyData>( );
                break;
            case Kind::SingleTimeseriesProperty:
                result = std::make_shared<SingleTimeseriesPropertyData>( );
                break;
            case Kind::StringTimeseriesProperty:
                result = std::make_shared<StringTimeseriesPropertyData>( );
                break;
            case Kind::TimeSpanTimeseriesProperty:
                result = std::make_shared<TimeSpanTimeseriesPropertyData>( );
                break;
            case Kind::UInt16TimeseriesProperty:
                result = std::make_shared<UInt16TimeseriesPropertyData>( );
                break;
            case Kind::UInt32TimeseriesProperty:
                result = std::make_shared<UInt32TimeseriesPropertyData>( );
                break;
            case Kind::UInt64TimeseriesProperty:
                result = std::make_shared<UInt64TimeseriesPropertyData>( );
                break;
            case Kind::TimeSpanProperty:
                result = std::make_shared<TimeSpanPropertyData>( );
                break;
            case Kind::UInt16Property:
                result = std::make_shared<UInt16PropertyData>( );
                break;
            case Kind::UInt32Property:
                result = std::make_shared<UInt32PropertyData>( );
                break;
            case Kind::UInt64Property:
                result = std::make_shared<UInt64PropertyData>( );
                break;
            case Kind::BinaryPropertyDefinition:
                result = std::make_shared<BinaryPropertyDefinitionData>( );
                break;
            case Kind::BooleanPropertyDefinition:
                result = std::make_shared<BooleanPropertyDefinitionData>( );
                break;
            case Kind::BytePropertyDefinition:
                result = std::make_shared<BytePropertyDefinitionData>( );
                break;
            case Kind::DateTimePropertyDefinition:
                result = std::make_shared<DateTimePropertyDefinitionData>( );
                break;
            case Kind::DoublePropertyDefinition:
                result = std::make_shared<DoublePropertyDefinitionData>( );
                break;
            case Kind::GuidPropertyDefinition:
                result = std::make_shared<GuidPropertyDefinitionData>( );
                break;
            case Kind::Int16PropertyDefinition:
                result = std::make_shared<Int16PropertyDefinitionData>( );
                break;
            case Kind::Int32PropertyDefinition:
                result = std::make_shared<Int32PropertyDefinitionData>( );
                break;
            case Kind::Int64PropertyDefinition:
                result = std::make_shared<Int64PropertyDefinitionData>( );
                break;
            case Kind::ReferencePropertyDefinition:
                result = std::make_shared<ReferencePropertyDefinitionData>( );
                break;
            case Kind::SBytePropertyDefinition:
                result = std::make_shared<SBytePropertyDefinitionData>( );
                break;
            case Kind::SinglePropertyDefinition:
                result = std::make_shared<SinglePropertyDefinitionData>( );
                break;
            case Kind::StringPropertyDefinition:
                result = std::make_shared<StringPropertyDefinitionData>( );
                break;
            case Kind::BinaryTimeseriesPropertyDefinition:
                result = std::make_shared<BinaryTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::BooleanTimeseriesPropertyDefinition:
                result = std::make_shared<BooleanTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::ByteTimeseriesPropertyDefinition:
                result = std::make_shared<ByteTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::DateTimeTimeseriesPropertyDefinition:
                result = std::make_shared<DateTimeTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::DoubleTimeseriesPropertyDefinition:
                result = std::make_shared<DoubleTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::GuidTimeseriesPropertyDefinition:
                result = std::make_shared<GuidTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::Int16TimeseriesPropertyDefinition:
                result = std::make_shared<Int16TimeseriesPropertyDefinitionData>( );
                break;
            case Kind::Int32TimeseriesPropertyDefinition:
                result = std::make_shared<Int32TimeseriesPropertyDefinitionData>( );
                break;
            case Kind::Int64TimeseriesPropertyDefinition:
                result = std::make_shared<Int64TimeseriesPropertyDefinitionData>( );
                break;
            case Kind::ReferenceTimeseriesPropertyDefinition:
                result = std::make_shared<ReferenceTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::SByteTimeseriesPropertyDefinition:
                result = std::make_shared<SByteTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::SingleTimeseriesPropertyDefinition:
                result = std::make_shared<SingleTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::StringTimeseriesPropertyDefinition:
                result = std::make_shared<StringTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::TimeSpanTimeseriesPropertyDefinition:
                result = std::make_shared<TimeSpanTimeseriesPropertyDefinitionData>( );
                break;
            case Kind::UInt16TimeseriesPropertyDefinition:
                result = std::make_shared<UInt16TimeseriesPropertyDefinitionData>( );
                break;
            case Kind::UInt32TimeseriesPropertyDefinition:
                result = std::make_shared<UInt32TimeseriesPropertyDefinitionData>( );
                break;
            case Kind::UInt64TimeseriesPropertyDefinition:
                result = std::make_shared<UInt64TimeseriesPropertyDefinitionData>( );
                break;
            case Kind::TimeSpanPropertyDefinition:
                result = std::make_shared<TimeSpanPropertyDefinitionData>( );
                break;
            case Kind::UInt16PropertyDefinition:
                result = std::make_shared<UInt16PropertyDefinitionData>( );
                break;
            case Kind::UInt32PropertyDefinition:
                result = std::make_shared<UInt32PropertyDefinitionData>( );
                break;
            case Kind::UInt64PropertyDefinition:
                result = std::make_shared<UInt64PropertyDefinitionData>( );
                break;
            case Kind::RadarAlarmStatus:
                result = std::make_shared<RadarAlarmStatusData>( );
                break;
            case Kind::RadarCommand:
                result = std::make_shared<RadarCommandData>( );
                break;
            case Kind::RadarCommandGetStatus:
                result = std::make_shared<RadarCommandGetStatusData>( );
                break;
            case Kind::RadarCommandReply:
                result = std::make_shared<RadarCommandReplyData>( );
                break;
            case Kind::RadarCommandReplyGetStatus:
                result = std::make_shared<RadarCommandReplyGetStatusData>( );
                break;
            case Kind::RadarConfiguration:
                result = std::make_shared<RadarConfigurationData>( );
                break;
            case Kind::RadarImage:
                result = std::make_shared<RadarImageData>( );
                break;
            case Kind::RadarRawTrackTable:
                result = std::make_shared<RadarRawTrackTableData>( );
                break;
            case Kind::RadarStatus:
                result = std::make_shared<RadarStatusData>( );
                break;
            case Kind::RadioCommand:
                result = std::make_shared<RadioCommandData>( );
                break;
            case Kind::RadioCommandReply:
                result = std::make_shared<RadioCommandReplyData>( );
                break;
            case Kind::RadioConfiguration:
                result = std::make_shared<RadioConfigurationData>( );
                break;
            case Kind::RadomeCommand:
                result = std::make_shared<RadomeCommandData>( );
                break;
            case Kind::RadomeCommandReply:
                result = std::make_shared<RadomeCommandReplyData>( );
                break;
            case Kind::RadomeConfiguration:
                result = std::make_shared<RadomeConfigurationData>( );
                break;
            case Kind::ReferenceTimeseriesValue:
                result = std::make_shared<ReferenceTimeseriesValueData>( );
                break;
            case Kind::SByteTimeseriesValue:
                result = std::make_shared<SByteTimeseriesValueData>( );
                break;
            case Kind::SecurityDomain:
                result = std::make_shared<SecurityDomainData>( );
                break;
            case Kind::SecurityLogin:
                result = std::make_shared<SecurityLoginData>( );
                break;
            case Kind::SecurityRole:
                result = std::make_shared<SecurityRoleData>( );
                break;
            case Kind::SecurityIdentifierRoleLink:
                result = std::make_shared<SecurityIdentifierRoleLinkData>( );
                break;
            case Kind::SecurityLoginSession:
                result = std::make_shared<SecurityLoginSessionData>( );
                break;
            case Kind::SecurityPermission:
                result = std::make_shared<SecurityPermissionData>( );
                break;
            case Kind::SingleTimeseriesValue:
                result = std::make_shared<SingleTimeseriesValueData>( );
                break;
            case Kind::StringTimeseriesValue:
                result = std::make_shared<StringTimeseriesValueData>( );
                break;
            case Kind::BinaryTimeseries:
                result = std::make_shared<BinaryTimeseriesData>( );
                break;
            case Kind::BooleanTimeseries:
                result = std::make_shared<BooleanTimeseriesData>( );
                break;
            case Kind::AisAidToNavigationOffPositionTimeseries:
                result = std::make_shared<AisAidToNavigationOffPositionTimeseriesData>( );
                break;
            case Kind::DeviceEnabledTimeseries:
                result = std::make_shared<DeviceEnabledTimeseriesData>( );
                break;
            case Kind::RadarAutomaticSensitivityTimeControlTimeseries:
                result = std::make_shared<RadarAutomaticSensitivityTimeControlTimeseriesData>( );
                break;
            case Kind::RadarBlankSector1Timeseries:
                result = std::make_shared<RadarBlankSector1TimeseriesData>( );
                break;
            case Kind::RadarBlankSector2Timeseries:
                result = std::make_shared<RadarBlankSector2TimeseriesData>( );
                break;
            case Kind::RadarEnableAutomaticFrequencyControlTimeseries:
                result = std::make_shared<RadarEnableAutomaticFrequencyControlTimeseriesData>( );
                break;
            case Kind::RadarEnableFastTimeConstantTimeseries:
                result = std::make_shared<RadarEnableFastTimeConstantTimeseriesData>( );
                break;
            case Kind::RadarEnableSensitivityTimeControlTimeseries:
                result = std::make_shared<RadarEnableSensitivityTimeControlTimeseriesData>( );
                break;
            case Kind::RadarPowerOnTimeseries:
                result = std::make_shared<RadarPowerOnTimeseriesData>( );
                break;
            case Kind::RadarSaveSettingsTimeseries:
                result = std::make_shared<RadarSaveSettingsTimeseriesData>( );
                break;
            case Kind::RadarTrackingTimeseries:
                result = std::make_shared<RadarTrackingTimeseriesData>( );
                break;
            case Kind::MediaProxySessionEnabledTimeseries:
                result = std::make_shared<MediaProxySessionEnabledTimeseriesData>( );
                break;
            case Kind::MediaServiceEnabledTimeseries:
                result = std::make_shared<MediaServiceEnabledTimeseriesData>( );
                break;
            case Kind::ByteTimeseries:
                result = std::make_shared<ByteTimeseriesData>( );
                break;
            case Kind::DateTimeTimeseries:
                result = std::make_shared<DateTimeTimeseriesData>( );
                break;
            case Kind::DoubleTimeseries:
                result = std::make_shared<DoubleTimeseriesData>( );
                break;
            case Kind::GNSSAltitudeTimeseries:
                result = std::make_shared<GNSSAltitudeTimeseriesData>( );
                break;
            case Kind::GNSSLatitudeTimeseries:
                result = std::make_shared<GNSSLatitudeTimeseriesData>( );
                break;
            case Kind::GNSSLongitudeTimeseries:
                result = std::make_shared<GNSSLongitudeTimeseriesData>( );
                break;
            case Kind::GyroCourseTimeseries:
                result = std::make_shared<GyroCourseTimeseriesData>( );
                break;
            case Kind::GyroHeadingMagneticNorthTimeseries:
                result = std::make_shared<GyroHeadingMagneticNorthTimeseriesData>( );
                break;
            case Kind::GyroHeadingTrueNorthTimeseries:
                result = std::make_shared<GyroHeadingTrueNorthTimeseriesData>( );
                break;
            case Kind::GyroPitchTimeseries:
                result = std::make_shared<GyroPitchTimeseriesData>( );
                break;
            case Kind::GyroRateOfTurnTimeseries:
                result = std::make_shared<GyroRateOfTurnTimeseriesData>( );
                break;
            case Kind::GyroRollTimeseries:
                result = std::make_shared<GyroRollTimeseriesData>( );
                break;
            case Kind::GyroSpeedTimeseries:
                result = std::make_shared<GyroSpeedTimeseriesData>( );
                break;
            case Kind::RadarLatitudeTimeseries:
                result = std::make_shared<RadarLatitudeTimeseriesData>( );
                break;
            case Kind::RadarLongitudeTimeseries:
                result = std::make_shared<RadarLongitudeTimeseriesData>( );
                break;
            case Kind::RadomeDewPointTimeseries:
                result = std::make_shared<RadomeDewPointTimeseriesData>( );
                break;
            case Kind::RadomePressureTimeseries:
                result = std::make_shared<RadomePressureTimeseriesData>( );
                break;
            case Kind::RadomeTemperatureTimeseries:
                result = std::make_shared<RadomeTemperatureTimeseriesData>( );
                break;
            case Kind::VesselDraughtTimeseries:
                result = std::make_shared<VesselDraughtTimeseriesData>( );
                break;
            case Kind::ViewLatitudeTimeseries:
                result = std::make_shared<ViewLatitudeTimeseriesData>( );
                break;
            case Kind::ViewLongitudeTimeseries:
                result = std::make_shared<ViewLongitudeTimeseriesData>( );
                break;
            case Kind::ViewZoomLevelTimeseries:
                result = std::make_shared<ViewZoomLevelTimeseriesData>( );
                break;
            case Kind::WeatherStationAbsoluteHumidityTimeseries:
                result = std::make_shared<WeatherStationAbsoluteHumidityTimeseriesData>( );
                break;
            case Kind::WeatherStationAirTemperatureTimeseries:
                result = std::make_shared<WeatherStationAirTemperatureTimeseriesData>( );
                break;
            case Kind::WeatherStationBarometricPressureTimeseries:
                result = std::make_shared<WeatherStationBarometricPressureTimeseriesData>( );
                break;
            case Kind::WeatherStationDewPointTimeseries:
                result = std::make_shared<WeatherStationDewPointTimeseriesData>( );
                break;
            case Kind::WeatherStationRelativeHumidityTimeseries:
                result = std::make_shared<WeatherStationRelativeHumidityTimeseriesData>( );
                break;
            case Kind::WeatherStationWaterTemperatureTimeseries:
                result = std::make_shared<WeatherStationWaterTemperatureTimeseriesData>( );
                break;
            case Kind::WeatherStationWindDirectionTimeseries:
                result = std::make_shared<WeatherStationWindDirectionTimeseriesData>( );
                break;
            case Kind::WeatherStationWindSpeedTimeseries:
                result = std::make_shared<WeatherStationWindSpeedTimeseriesData>( );
                break;
            case Kind::GeoPosition2DTimeseries:
                result = std::make_shared<GeoPosition2DTimeseriesData>( );
                break;
            case Kind::AisAidToNavigationPositionTimeseries:
                result = std::make_shared<AisAidToNavigationPositionTimeseriesData>( );
                break;
            case Kind::GeoPosition3DTimeseries:
                result = std::make_shared<GeoPosition3DTimeseriesData>( );
                break;
            case Kind::GuidTimeseries:
                result = std::make_shared<GuidTimeseriesData>( );
                break;
            case Kind::Int16Timeseries:
                result = std::make_shared<Int16TimeseriesData>( );
                break;
            case Kind::Int32Timeseries:
                result = std::make_shared<Int32TimeseriesData>( );
                break;
            case Kind::RadarAzimuthOffsetTimeseries:
                result = std::make_shared<RadarAzimuthOffsetTimeseriesData>( );
                break;
            case Kind::RadarFastTimeConstantLevelTimeseries:
                result = std::make_shared<RadarFastTimeConstantLevelTimeseriesData>( );
                break;
            case Kind::RadarFastTimeConstantModeTimeseries:
                result = std::make_shared<RadarFastTimeConstantModeTimeseriesData>( );
                break;
            case Kind::RadarPulseTimeseries:
                result = std::make_shared<RadarPulseTimeseriesData>( );
                break;
            case Kind::RadarSector1EndTimeseries:
                result = std::make_shared<RadarSector1EndTimeseriesData>( );
                break;
            case Kind::RadarSector1StartTimeseries:
                result = std::make_shared<RadarSector1StartTimeseriesData>( );
                break;
            case Kind::RadarSector2EndTimeseries:
                result = std::make_shared<RadarSector2EndTimeseriesData>( );
                break;
            case Kind::RadarSector2StartTimeseries:
                result = std::make_shared<RadarSector2StartTimeseriesData>( );
                break;
            case Kind::RadarSensitivityTimeControlLevelTimeseries:
                result = std::make_shared<RadarSensitivityTimeControlLevelTimeseriesData>( );
                break;
            case Kind::RadarTuningTimeseries:
                result = std::make_shared<RadarTuningTimeseriesData>( );
                break;
            case Kind::VesselPersonsOnBoardTimeseries:
                result = std::make_shared<VesselPersonsOnBoardTimeseriesData>( );
                break;
            case Kind::Int64Timeseries:
                result = std::make_shared<Int64TimeseriesData>( );
                break;
            case Kind::Position2DTimeseries:
                result = std::make_shared<Position2DTimeseriesData>( );
                break;
            case Kind::Position3DTimeseries:
                result = std::make_shared<Position3DTimeseriesData>( );
                break;
            case Kind::ReferenceTimeseries:
                result = std::make_shared<ReferenceTimeseriesData>( );
                break;
            case Kind::SByteTimeseries:
                result = std::make_shared<SByteTimeseriesData>( );
                break;
            case Kind::SingleTimeseries:
                result = std::make_shared<SingleTimeseriesData>( );
                break;
            case Kind::StringTimeseries:
                result = std::make_shared<StringTimeseriesData>( );
                break;
            case Kind::TimeSpanTimeseries:
                result = std::make_shared<TimeSpanTimeseriesData>( );
                break;
            case Kind::UInt16Timeseries:
                result = std::make_shared<UInt16TimeseriesData>( );
                break;
            case Kind::UInt32Timeseries:
                result = std::make_shared<UInt32TimeseriesData>( );
                break;
            case Kind::RadomeStatusTimeseries:
                result = std::make_shared<RadomeStatusTimeseriesData>( );
                break;
            case Kind::UInt64Timeseries:
                result = std::make_shared<UInt64TimeseriesData>( );
                break;
            case Kind::TimeseriesCatalog:
                result = std::make_shared<TimeseriesCatalogData>( );
                break;
            case Kind::TimeseriesInfo:
                result = std::make_shared<TimeseriesInfoData>( );
                break;
            case Kind::TimeSpanTimeseriesValue:
                result = std::make_shared<TimeSpanTimeseriesValueData>( );
                break;
            case Kind::TrackableItemTrackLink:
                result = std::make_shared<TrackableItemTrackLinkData>( );
                break;
            case Kind::Track:
                result = std::make_shared<TrackData>( );
                break;
            case Kind::Track3D:
                result = std::make_shared<Track3DData>( );
                break;
            case Kind::TrackerFilterParameters:
                result = std::make_shared<TrackerFilterParametersData>( );
                break;
            case Kind::TrackerFilterParametersConfiguration:
                result = std::make_shared<TrackerFilterParametersConfigurationData>( );
                break;
            case Kind::TrackInfo:
                result = std::make_shared<TrackInfoData>( );
                break;
            case Kind::TrackingServiceOptions:
                result = std::make_shared<TrackingServiceOptionsData>( );
                break;
            case Kind::TrackLink:
                result = std::make_shared<TrackLinkData>( );
                break;
            case Kind::TrackValue:
                result = std::make_shared<TrackValueData>( );
                break;
            case Kind::TrackValue3D:
                result = std::make_shared<TrackValue3DData>( );
                break;
            case Kind::UInt16TimeseriesValue:
                result = std::make_shared<UInt16TimeseriesValueData>( );
                break;
            case Kind::UInt32TimeseriesValue:
                result = std::make_shared<UInt32TimeseriesValueData>( );
                break;
            case Kind::UInt64TimeseriesValue:
                result = std::make_shared<UInt64TimeseriesValueData>( );
                break;
            case Kind::VehicleType:
                result = std::make_shared<VehicleTypeData>( );
                break;
            case Kind::VesselType:
                result = std::make_shared<VesselTypeData>( );
                break;
            case Kind::View:
                result = std::make_shared<ViewData>( );
                break;
            case Kind::ViewCameraLink:
                result = std::make_shared<ViewCameraLinkData>( );
                break;
            case Kind::ViewTrackerLink:
                result = std::make_shared<ViewTrackerLinkData>( );
                break;
            case Kind::WeatherStationCommand:
                result = std::make_shared<WeatherStationCommandData>( );
                break;
            case Kind::WeatherStationCommandReply:
                result = std::make_shared<WeatherStationCommandReplyData>( );
                break;
            case Kind::WeatherStationConfiguration:
                result = std::make_shared<WeatherStationConfigurationData>( );
                break;
            case Kind::CircularZone:
                result = std::make_shared<CircularZoneData>( );
                break;
            case Kind::PolygonZone:
                result = std::make_shared<PolygonZoneData>( );
                break;
            case Kind::ZoneExceptions:
                result = std::make_shared<ZoneExceptionsData>( );
                break;
            case Kind::ZoneExceptionsVesselLink:
                result = std::make_shared<ZoneExceptionsVesselLinkData>( );
                break;
            case Kind::ZoneTrackAlarm:
                result = std::make_shared<ZoneTrackAlarmData>( );
                break;
        }
        return result;
    }
}
