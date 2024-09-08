#include "pch.h"

#include "DataTypes.h"


namespace Barrelman::Types
{

    BARRELMAN_EXPORT std::shared_ptr<BaseData<Kind, Guid>> DataFactory( Kind kind )
    {
        std::shared_ptr<BaseData<Kind, Guid>> result;
        switch(kind)
        {
            case Kind::AircraftType:
                result = std::make_shared<AircraftTypeObject>( );
                break;
            case Kind::AisDeviceCommand:
                result = std::make_shared<AisDeviceCommandObject>( );
                break;
            case Kind::AisDeviceCommandReply:
                result = std::make_shared<AisDeviceCommandReplyObject>( );
                break;
            case Kind::AisDeviceConfiguration:
                result = std::make_shared<AisDeviceConfigurationObject>( );
                break;
            case Kind::AisDeviceRawMessage:
                result = std::make_shared<AisDeviceRawMessageObject>( );
                break;
            case Kind::AisDeviceRawSentence:
                result = std::make_shared<AisDeviceRawSentenceObject>( );
                break;
            case Kind::AidToNavigationReportMessage:
                result = std::make_shared<AidToNavigationReportMessageObject>( );
                break;
            case Kind::AisAddressedSafetyRelatedMessage:
                result = std::make_shared<AisAddressedSafetyRelatedMessageObject>( );
                break;
            case Kind::AisBaseStationReportMessage:
                result = std::make_shared<AisBaseStationReportMessageObject>( );
                break;
            case Kind::AisBinaryAcknowledgeMessage:
                result = std::make_shared<AisBinaryAcknowledgeMessageObject>( );
                break;
            case Kind::AisBinaryAddressedMessage:
                result = std::make_shared<AisBinaryAddressedMessageObject>( );
                break;
            case Kind::AisBinaryBroadcastMessage:
                result = std::make_shared<AisBinaryBroadcastMessageObject>( );
                break;
            case Kind::AisDataLinkManagementMessage:
                result = std::make_shared<AisDataLinkManagementMessageObject>( );
                break;
            case Kind::AisExtendedClassBCsPositionReportMessage:
                result = std::make_shared<AisExtendedClassBCsPositionReportMessageObject>( );
                break;
            case Kind::AisInterrogationMessage:
                result = std::make_shared<AisInterrogationMessageObject>( );
                break;
            case Kind::AisPositionReportClassAAssignedScheduleMessage:
                result = std::make_shared<AisPositionReportClassAAssignedScheduleMessageObject>( );
                break;
            case Kind::AisPositionReportClassAMessage:
                result = std::make_shared<AisPositionReportClassAMessageObject>( );
                break;
            case Kind::AisPositionReportClassAResponseToInterrogationMessage:
                result = std::make_shared<AisPositionReportClassAResponseToInterrogationMessageObject>( );
                break;
            case Kind::AisPositionReportForLongRangeApplicationsMessage:
                result = std::make_shared<AisPositionReportForLongRangeApplicationsMessageObject>( );
                break;
            case Kind::AisSafetyRelatedAcknowledgmentMessage:
                result = std::make_shared<AisSafetyRelatedAcknowledgmentMessageObject>( );
                break;
            case Kind::AisStandardClassBCsPositionReportMessage:
                result = std::make_shared<AisStandardClassBCsPositionReportMessageObject>( );
                break;
            case Kind::AisStandardSarAircraftPositionReportMessage:
                result = std::make_shared<AisStandardSarAircraftPositionReportMessageObject>( );
                break;
            case Kind::AisStaticAndVoyageRelatedDataMessage:
                result = std::make_shared<AisStaticAndVoyageRelatedDataMessageObject>( );
                break;
            case Kind::AisStaticDataReportMessage:
                result = std::make_shared<AisStaticDataReportMessageObject>( );
                break;
            case Kind::AisStaticDataReportPartAMessage:
                result = std::make_shared<AisStaticDataReportPartAMessageObject>( );
                break;
            case Kind::AisStaticDataReportPartBMessage:
                result = std::make_shared<AisStaticDataReportPartBMessageObject>( );
                break;
            case Kind::AisUtcAndDateInquiryMessage:
                result = std::make_shared<AisUtcAndDateInquiryMessageObject>( );
                break;
            case Kind::AisUtcAndDateResponseMessage:
                result = std::make_shared<AisUtcAndDateResponseMessageObject>( );
                break;
            case Kind::AlarmStateChange:
                result = std::make_shared<AlarmStateChangeObject>( );
                break;
            case Kind::BaseStationType:
                result = std::make_shared<BaseStationTypeObject>( );
                break;
            case Kind::BinaryTimeseriesValue:
                result = std::make_shared<BinaryTimeseriesValueObject>( );
                break;
            case Kind::Bookmark:
                result = std::make_shared<BookmarkObject>( );
                break;
            case Kind::BooleanTimeseriesValue:
                result = std::make_shared<BooleanTimeseriesValueObject>( );
                break;
            case Kind::ByteTimeseriesValue:
                result = std::make_shared<ByteTimeseriesValueObject>( );
                break;
            case Kind::CameraCommand:
                result = std::make_shared<CameraCommandObject>( );
                break;
            case Kind::CameraCommandAbsoluteMove:
                result = std::make_shared<CameraCommandAbsoluteMoveObject>( );
                break;
            case Kind::CameraCommandAdjustPanTiltZoom:
                result = std::make_shared<CameraCommandAdjustPanTiltZoomObject>( );
                break;
            case Kind::CameraCommandContinuousMove:
                result = std::make_shared<CameraCommandContinuousMoveObject>( );
                break;
            case Kind::CameraCommandGeoMove:
                result = std::make_shared<CameraCommandGeoMoveObject>( );
                break;
            case Kind::CameraCommandRelativeMove:
                result = std::make_shared<CameraCommandRelativeMoveObject>( );
                break;
            case Kind::CameraCommandReleasePTZOwnership:
                result = std::make_shared<CameraCommandReleasePTZOwnershipObject>( );
                break;
            case Kind::CameraCommandRequestPTZOwnership:
                result = std::make_shared<CameraCommandRequestPTZOwnershipObject>( );
                break;
            case Kind::CameraCommandSetAutoFocus:
                result = std::make_shared<CameraCommandSetAutoFocusObject>( );
                break;
            case Kind::CameraCommandSetBlackAndWhite:
                result = std::make_shared<CameraCommandSetBlackAndWhiteObject>( );
                break;
            case Kind::CameraCommandSetFollowed:
                result = std::make_shared<CameraCommandSetFollowedObject>( );
                break;
            case Kind::CameraCommandSetInfraRedLamp:
                result = std::make_shared<CameraCommandSetInfraRedLampObject>( );
                break;
            case Kind::CameraCommandSetWasher:
                result = std::make_shared<CameraCommandSetWasherObject>( );
                break;
            case Kind::CameraCommandSetWiper:
                result = std::make_shared<CameraCommandSetWiperObject>( );
                break;
            case Kind::CameraCommandStop:
                result = std::make_shared<CameraCommandStopObject>( );
                break;
            case Kind::CameraCommandReply:
                result = std::make_shared<CameraCommandReplyObject>( );
                break;
            case Kind::CameraConfiguration:
                result = std::make_shared<CameraConfigurationObject>( );
                break;
            case Kind::CameraPanCalibration:
                result = std::make_shared<CameraPanCalibrationObject>( );
                break;
            case Kind::CameraPanCalibrationValue:
                result = std::make_shared<CameraPanCalibrationValueObject>( );
                break;
            case Kind::CameraStatus:
                result = std::make_shared<CameraStatusObject>( );
                break;
            case Kind::CameraTiltCalibration:
                result = std::make_shared<CameraTiltCalibrationObject>( );
                break;
            case Kind::CameraTiltCalibrationValue:
                result = std::make_shared<CameraTiltCalibrationValueObject>( );
                break;
            case Kind::CameraZoomCalibration:
                result = std::make_shared<CameraZoomCalibrationObject>( );
                break;
            case Kind::CameraZoomCalibrationValue:
                result = std::make_shared<CameraZoomCalibrationValueObject>( );
                break;
            case Kind::Catalog:
                result = std::make_shared<CatalogObject>( );
                break;
            case Kind::Element:
                result = std::make_shared<ElementObject>( );
                break;
            case Kind::CollectionInfo:
                result = std::make_shared<CollectionInfoObject>( );
                break;
            case Kind::Country:
                result = std::make_shared<CountryObject>( );
                break;
            case Kind::CursorInfo:
                result = std::make_shared<CursorInfoObject>( );
                break;
            case Kind::DateTimeTimeseriesValue:
                result = std::make_shared<DateTimeTimeseriesValueObject>( );
                break;
            case Kind::DeviceHost:
                result = std::make_shared<DeviceHostObject>( );
                break;
            case Kind::DeviceHostConfiguration:
                result = std::make_shared<DeviceHostConfigurationObject>( );
                break;
            case Kind::DoubleTimeseriesValue:
                result = std::make_shared<DoubleTimeseriesValueObject>( );
                break;
            case Kind::FacilityType:
                result = std::make_shared<FacilityTypeObject>( );
                break;
            case Kind::GeoPosition2DTimeseriesValue:
                result = std::make_shared<GeoPosition2DTimeseriesValueObject>( );
                break;
            case Kind::GeoPosition3DTimeseriesValue:
                result = std::make_shared<GeoPosition3DTimeseriesValueObject>( );
                break;
            case Kind::GNSSDeviceCommand:
                result = std::make_shared<GNSSDeviceCommandObject>( );
                break;
            case Kind::GNSSDeviceCommandReply:
                result = std::make_shared<GNSSDeviceCommandReplyObject>( );
                break;
            case Kind::GNSSDeviceConfiguration:
                result = std::make_shared<GNSSDeviceConfigurationObject>( );
                break;
            case Kind::GuidTimeseriesValue:
                result = std::make_shared<GuidTimeseriesValueObject>( );
                break;
            case Kind::GyroDeviceCommand:
                result = std::make_shared<GyroDeviceCommandObject>( );
                break;
            case Kind::GyroDeviceCommandReply:
                result = std::make_shared<GyroDeviceCommandReplyObject>( );
                break;
            case Kind::GyroDeviceConfiguration:
                result = std::make_shared<GyroDeviceConfigurationObject>( );
                break;
            case Kind::Callsign:
                result = std::make_shared<CallsignObject>( );
                break;
            case Kind::InternationalMaritimeOrganizationNumber:
                result = std::make_shared<InternationalMaritimeOrganizationNumberObject>( );
                break;
            case Kind::MaritimeMobileServiceIdentity:
                result = std::make_shared<MaritimeMobileServiceIdentityObject>( );
                break;
            case Kind::Name:
                result = std::make_shared<NameObject>( );
                break;
            case Kind::Int16TimeseriesValue:
                result = std::make_shared<Int16TimeseriesValueObject>( );
                break;
            case Kind::Int32TimeseriesValue:
                result = std::make_shared<Int32TimeseriesValueObject>( );
                break;
            case Kind::Int64TimeseriesValue:
                result = std::make_shared<Int64TimeseriesValueObject>( );
                break;
            case Kind::BaseStation:
                result = std::make_shared<BaseStationObject>( );
                break;
            case Kind::CameraDevice:
                result = std::make_shared<CameraDeviceObject>( );
                break;
            case Kind::GNSSDevice:
                result = std::make_shared<GNSSDeviceObject>( );
                break;
            case Kind::GyroDevice:
                result = std::make_shared<GyroDeviceObject>( );
                break;
            case Kind::LineInputDevice:
                result = std::make_shared<LineInputDeviceObject>( );
                break;
            case Kind::OilSpillDetectorDevice:
                result = std::make_shared<OilSpillDetectorDeviceObject>( );
                break;
            case Kind::RadioDevice:
                result = std::make_shared<RadioDeviceObject>( );
                break;
            case Kind::RadomeDevice:
                result = std::make_shared<RadomeDeviceObject>( );
                break;
            case Kind::AisDevice:
                result = std::make_shared<AisDeviceObject>( );
                break;
            case Kind::RadarDevice:
                result = std::make_shared<RadarDeviceObject>( );
                break;
            case Kind::WeatherStationDevice:
                result = std::make_shared<WeatherStationDeviceObject>( );
                break;
            case Kind::Facility:
                result = std::make_shared<FacilityObject>( );
                break;
            case Kind::Aircraft:
                result = std::make_shared<AircraftObject>( );
                break;
            case Kind::AisAidToNavigation:
                result = std::make_shared<AisAidToNavigationObject>( );
                break;
            case Kind::Vehicle:
                result = std::make_shared<VehicleObject>( );
                break;
            case Kind::Vessel:
                result = std::make_shared<VesselObject>( );
                break;
            case Kind::ItemIdentityLink:
                result = std::make_shared<ItemIdentityLinkObject>( );
                break;
            case Kind::ItemParentChildLink:
                result = std::make_shared<ItemParentChildLinkObject>( );
                break;
            case Kind::LineInputDeviceCommand:
                result = std::make_shared<LineInputDeviceCommandObject>( );
                break;
            case Kind::LineInputDeviceCommandReply:
                result = std::make_shared<LineInputDeviceCommandReplyObject>( );
                break;
            case Kind::LineInputDeviceConfiguration:
                result = std::make_shared<LineInputDeviceConfigurationObject>( );
                break;
            case Kind::LineInputMessageRouting:
                result = std::make_shared<LineInputMessageRoutingObject>( );
                break;
            case Kind::LineInputMessageRoutingDestination:
                result = std::make_shared<LineInputMessageRoutingDestinationObject>( );
                break;
            case Kind::LineInputWhiteListEntry:
                result = std::make_shared<LineInputWhiteListEntryObject>( );
                break;
            case Kind::LogApplication:
                result = std::make_shared<LogApplicationObject>( );
                break;
            case Kind::LogApplicationConfiguration:
                result = std::make_shared<LogApplicationConfigurationObject>( );
                break;
            case Kind::LogHost:
                result = std::make_shared<LogHostObject>( );
                break;
            case Kind::LogHostConfiguration:
                result = std::make_shared<LogHostConfigurationObject>( );
                break;
            case Kind::LogLocation:
                result = std::make_shared<LogLocationObject>( );
                break;
            case Kind::LogProcess:
                result = std::make_shared<LogProcessObject>( );
                break;
            case Kind::LogRecord:
                result = std::make_shared<LogRecordObject>( );
                break;
            case Kind::LogThread:
                result = std::make_shared<LogThreadObject>( );
                break;
            case Kind::LogTraceEntry:
                result = std::make_shared<LogTraceEntryObject>( );
                break;
            case Kind::MapElement:
                result = std::make_shared<MapElementObject>( );
                break;
            case Kind::MapInfo:
                result = std::make_shared<MapInfoObject>( );
                break;
            case Kind::MapServiceOptions:
                result = std::make_shared<MapServiceOptionsObject>( );
                break;
            case Kind::MaritimeIdentificationDigits:
                result = std::make_shared<MaritimeIdentificationDigitsObject>( );
                break;
            case Kind::MediaProxySession:
                result = std::make_shared<MediaProxySessionObject>( );
                break;
            case Kind::MediaProxySessionFile:
                result = std::make_shared<MediaProxySessionFileObject>( );
                break;
            case Kind::MediaProxySessionOptions:
                result = std::make_shared<MediaProxySessionOptionsObject>( );
                break;
            case Kind::MediaService:
                result = std::make_shared<MediaServiceObject>( );
                break;
            case Kind::MediaServiceOptions:
                result = std::make_shared<MediaServiceOptionsObject>( );
                break;
            case Kind::ElementType:
                result = std::make_shared<ElementTypeObject>( );
                break;
            case Kind::Namespace:
                result = std::make_shared<NamespaceObject>( );
                break;
            case Kind::OilSpill:
                result = std::make_shared<OilSpillObject>( );
                break;
            case Kind::OilSpillDetectorCommand:
                result = std::make_shared<OilSpillDetectorCommandObject>( );
                break;
            case Kind::OilSpillDetectorCommandReply:
                result = std::make_shared<OilSpillDetectorCommandReplyObject>( );
                break;
            case Kind::OilSpillDetectorConfiguration:
                result = std::make_shared<OilSpillDetectorConfigurationObject>( );
                break;
            case Kind::Position2DTimeseriesValue:
                result = std::make_shared<Position2DTimeseriesValueObject>( );
                break;
            case Kind::Position3DTimeseriesValue:
                result = std::make_shared<Position3DTimeseriesValueObject>( );
                break;
            case Kind::ProcessTrackValueResult:
                result = std::make_shared<ProcessTrackValueResultObject>( );
                break;
            case Kind::BinaryProperty:
                result = std::make_shared<BinaryPropertyObject>( );
                break;
            case Kind::BooleanProperty:
                result = std::make_shared<BooleanPropertyObject>( );
                break;
            case Kind::ByteProperty:
                result = std::make_shared<BytePropertyObject>( );
                break;
            case Kind::DateTimeProperty:
                result = std::make_shared<DateTimePropertyObject>( );
                break;
            case Kind::DoubleProperty:
                result = std::make_shared<DoublePropertyObject>( );
                break;
            case Kind::GuidProperty:
                result = std::make_shared<GuidPropertyObject>( );
                break;
            case Kind::Int16Property:
                result = std::make_shared<Int16PropertyObject>( );
                break;
            case Kind::Int32Property:
                result = std::make_shared<Int32PropertyObject>( );
                break;
            case Kind::Int64Property:
                result = std::make_shared<Int64PropertyObject>( );
                break;
            case Kind::ReferenceProperty:
                result = std::make_shared<ReferencePropertyObject>( );
                break;
            case Kind::SByteProperty:
                result = std::make_shared<SBytePropertyObject>( );
                break;
            case Kind::SingleProperty:
                result = std::make_shared<SinglePropertyObject>( );
                break;
            case Kind::StringProperty:
                result = std::make_shared<StringPropertyObject>( );
                break;
            case Kind::BinaryTimeseriesProperty:
                result = std::make_shared<BinaryTimeseriesPropertyObject>( );
                break;
            case Kind::BooleanTimeseriesProperty:
                result = std::make_shared<BooleanTimeseriesPropertyObject>( );
                break;
            case Kind::ByteTimeseriesProperty:
                result = std::make_shared<ByteTimeseriesPropertyObject>( );
                break;
            case Kind::DateTimeTimeseriesProperty:
                result = std::make_shared<DateTimeTimeseriesPropertyObject>( );
                break;
            case Kind::DoubleTimeseriesProperty:
                result = std::make_shared<DoubleTimeseriesPropertyObject>( );
                break;
            case Kind::GuidTimeseriesProperty:
                result = std::make_shared<GuidTimeseriesPropertyObject>( );
                break;
            case Kind::Int16TimeseriesProperty:
                result = std::make_shared<Int16TimeseriesPropertyObject>( );
                break;
            case Kind::Int32TimeseriesProperty:
                result = std::make_shared<Int32TimeseriesPropertyObject>( );
                break;
            case Kind::Int64TimeseriesProperty:
                result = std::make_shared<Int64TimeseriesPropertyObject>( );
                break;
            case Kind::ReferenceTimeseriesProperty:
                result = std::make_shared<ReferenceTimeseriesPropertyObject>( );
                break;
            case Kind::SByteTimeseriesProperty:
                result = std::make_shared<SByteTimeseriesPropertyObject>( );
                break;
            case Kind::SingleTimeseriesProperty:
                result = std::make_shared<SingleTimeseriesPropertyObject>( );
                break;
            case Kind::StringTimeseriesProperty:
                result = std::make_shared<StringTimeseriesPropertyObject>( );
                break;
            case Kind::TimeSpanTimeseriesProperty:
                result = std::make_shared<TimeSpanTimeseriesPropertyObject>( );
                break;
            case Kind::UInt16TimeseriesProperty:
                result = std::make_shared<UInt16TimeseriesPropertyObject>( );
                break;
            case Kind::UInt32TimeseriesProperty:
                result = std::make_shared<UInt32TimeseriesPropertyObject>( );
                break;
            case Kind::UInt64TimeseriesProperty:
                result = std::make_shared<UInt64TimeseriesPropertyObject>( );
                break;
            case Kind::TimeSpanProperty:
                result = std::make_shared<TimeSpanPropertyObject>( );
                break;
            case Kind::UInt16Property:
                result = std::make_shared<UInt16PropertyObject>( );
                break;
            case Kind::UInt32Property:
                result = std::make_shared<UInt32PropertyObject>( );
                break;
            case Kind::UInt64Property:
                result = std::make_shared<UInt64PropertyObject>( );
                break;
            case Kind::BinaryPropertyDefinition:
                result = std::make_shared<BinaryPropertyDefinitionObject>( );
                break;
            case Kind::BooleanPropertyDefinition:
                result = std::make_shared<BooleanPropertyDefinitionObject>( );
                break;
            case Kind::BytePropertyDefinition:
                result = std::make_shared<BytePropertyDefinitionObject>( );
                break;
            case Kind::DateTimePropertyDefinition:
                result = std::make_shared<DateTimePropertyDefinitionObject>( );
                break;
            case Kind::DoublePropertyDefinition:
                result = std::make_shared<DoublePropertyDefinitionObject>( );
                break;
            case Kind::GuidPropertyDefinition:
                result = std::make_shared<GuidPropertyDefinitionObject>( );
                break;
            case Kind::Int16PropertyDefinition:
                result = std::make_shared<Int16PropertyDefinitionObject>( );
                break;
            case Kind::Int32PropertyDefinition:
                result = std::make_shared<Int32PropertyDefinitionObject>( );
                break;
            case Kind::Int64PropertyDefinition:
                result = std::make_shared<Int64PropertyDefinitionObject>( );
                break;
            case Kind::ReferencePropertyDefinition:
                result = std::make_shared<ReferencePropertyDefinitionObject>( );
                break;
            case Kind::SBytePropertyDefinition:
                result = std::make_shared<SBytePropertyDefinitionObject>( );
                break;
            case Kind::SinglePropertyDefinition:
                result = std::make_shared<SinglePropertyDefinitionObject>( );
                break;
            case Kind::StringPropertyDefinition:
                result = std::make_shared<StringPropertyDefinitionObject>( );
                break;
            case Kind::BinaryTimeseriesPropertyDefinition:
                result = std::make_shared<BinaryTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::BooleanTimeseriesPropertyDefinition:
                result = std::make_shared<BooleanTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::ByteTimeseriesPropertyDefinition:
                result = std::make_shared<ByteTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::DateTimeTimeseriesPropertyDefinition:
                result = std::make_shared<DateTimeTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::DoubleTimeseriesPropertyDefinition:
                result = std::make_shared<DoubleTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::GuidTimeseriesPropertyDefinition:
                result = std::make_shared<GuidTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::Int16TimeseriesPropertyDefinition:
                result = std::make_shared<Int16TimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::Int32TimeseriesPropertyDefinition:
                result = std::make_shared<Int32TimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::Int64TimeseriesPropertyDefinition:
                result = std::make_shared<Int64TimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::ReferenceTimeseriesPropertyDefinition:
                result = std::make_shared<ReferenceTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::SByteTimeseriesPropertyDefinition:
                result = std::make_shared<SByteTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::SingleTimeseriesPropertyDefinition:
                result = std::make_shared<SingleTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::StringTimeseriesPropertyDefinition:
                result = std::make_shared<StringTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::TimeSpanTimeseriesPropertyDefinition:
                result = std::make_shared<TimeSpanTimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::UInt16TimeseriesPropertyDefinition:
                result = std::make_shared<UInt16TimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::UInt32TimeseriesPropertyDefinition:
                result = std::make_shared<UInt32TimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::UInt64TimeseriesPropertyDefinition:
                result = std::make_shared<UInt64TimeseriesPropertyDefinitionObject>( );
                break;
            case Kind::TimeSpanPropertyDefinition:
                result = std::make_shared<TimeSpanPropertyDefinitionObject>( );
                break;
            case Kind::UInt16PropertyDefinition:
                result = std::make_shared<UInt16PropertyDefinitionObject>( );
                break;
            case Kind::UInt32PropertyDefinition:
                result = std::make_shared<UInt32PropertyDefinitionObject>( );
                break;
            case Kind::UInt64PropertyDefinition:
                result = std::make_shared<UInt64PropertyDefinitionObject>( );
                break;
            case Kind::RadarAlarmStatus:
                result = std::make_shared<RadarAlarmStatusObject>( );
                break;
            case Kind::RadarCommand:
                result = std::make_shared<RadarCommandObject>( );
                break;
            case Kind::RadarCommandGetStatus:
                result = std::make_shared<RadarCommandGetStatusObject>( );
                break;
            case Kind::RadarCommandReply:
                result = std::make_shared<RadarCommandReplyObject>( );
                break;
            case Kind::RadarCommandReplyGetStatus:
                result = std::make_shared<RadarCommandReplyGetStatusObject>( );
                break;
            case Kind::RadarConfiguration:
                result = std::make_shared<RadarConfigurationObject>( );
                break;
            case Kind::RadarImage:
                result = std::make_shared<RadarImageObject>( );
                break;
            case Kind::RadarRawTrackTable:
                result = std::make_shared<RadarRawTrackTableObject>( );
                break;
            case Kind::RadarStatus:
                result = std::make_shared<RadarStatusObject>( );
                break;
            case Kind::RadioCommand:
                result = std::make_shared<RadioCommandObject>( );
                break;
            case Kind::RadioCommandReply:
                result = std::make_shared<RadioCommandReplyObject>( );
                break;
            case Kind::RadioConfiguration:
                result = std::make_shared<RadioConfigurationObject>( );
                break;
            case Kind::RadomeCommand:
                result = std::make_shared<RadomeCommandObject>( );
                break;
            case Kind::RadomeCommandReply:
                result = std::make_shared<RadomeCommandReplyObject>( );
                break;
            case Kind::RadomeConfiguration:
                result = std::make_shared<RadomeConfigurationObject>( );
                break;
            case Kind::ReferenceTimeseriesValue:
                result = std::make_shared<ReferenceTimeseriesValueObject>( );
                break;
            case Kind::SByteTimeseriesValue:
                result = std::make_shared<SByteTimeseriesValueObject>( );
                break;
            case Kind::SecurityDomain:
                result = std::make_shared<SecurityDomainObject>( );
                break;
            case Kind::SecurityLogin:
                result = std::make_shared<SecurityLoginObject>( );
                break;
            case Kind::SecurityRole:
                result = std::make_shared<SecurityRoleObject>( );
                break;
            case Kind::SecurityIdentifierRoleLink:
                result = std::make_shared<SecurityIdentifierRoleLinkObject>( );
                break;
            case Kind::SecurityLoginSession:
                result = std::make_shared<SecurityLoginSessionObject>( );
                break;
            case Kind::SecurityPermission:
                result = std::make_shared<SecurityPermissionObject>( );
                break;
            case Kind::SingleTimeseriesValue:
                result = std::make_shared<SingleTimeseriesValueObject>( );
                break;
            case Kind::StringTimeseriesValue:
                result = std::make_shared<StringTimeseriesValueObject>( );
                break;
            case Kind::BinaryTimeseries:
                result = std::make_shared<BinaryTimeseriesObject>( );
                break;
            case Kind::BooleanTimeseries:
                result = std::make_shared<BooleanTimeseriesObject>( );
                break;
            case Kind::AisAidToNavigationOffPositionTimeseries:
                result = std::make_shared<AisAidToNavigationOffPositionTimeseriesObject>( );
                break;
            case Kind::DeviceEnabledTimeseries:
                result = std::make_shared<DeviceEnabledTimeseriesObject>( );
                break;
            case Kind::RadarAutomaticSensitivityTimeControlTimeseries:
                result = std::make_shared<RadarAutomaticSensitivityTimeControlTimeseriesObject>( );
                break;
            case Kind::RadarBlankSector1Timeseries:
                result = std::make_shared<RadarBlankSector1TimeseriesObject>( );
                break;
            case Kind::RadarBlankSector2Timeseries:
                result = std::make_shared<RadarBlankSector2TimeseriesObject>( );
                break;
            case Kind::RadarEnableAutomaticFrequencyControlTimeseries:
                result = std::make_shared<RadarEnableAutomaticFrequencyControlTimeseriesObject>( );
                break;
            case Kind::RadarEnableFastTimeConstantTimeseries:
                result = std::make_shared<RadarEnableFastTimeConstantTimeseriesObject>( );
                break;
            case Kind::RadarEnableSensitivityTimeControlTimeseries:
                result = std::make_shared<RadarEnableSensitivityTimeControlTimeseriesObject>( );
                break;
            case Kind::RadarPowerOnTimeseries:
                result = std::make_shared<RadarPowerOnTimeseriesObject>( );
                break;
            case Kind::RadarSaveSettingsTimeseries:
                result = std::make_shared<RadarSaveSettingsTimeseriesObject>( );
                break;
            case Kind::RadarTrackingTimeseries:
                result = std::make_shared<RadarTrackingTimeseriesObject>( );
                break;
            case Kind::MediaProxySessionEnabledTimeseries:
                result = std::make_shared<MediaProxySessionEnabledTimeseriesObject>( );
                break;
            case Kind::MediaServiceEnabledTimeseries:
                result = std::make_shared<MediaServiceEnabledTimeseriesObject>( );
                break;
            case Kind::ByteTimeseries:
                result = std::make_shared<ByteTimeseriesObject>( );
                break;
            case Kind::DateTimeTimeseries:
                result = std::make_shared<DateTimeTimeseriesObject>( );
                break;
            case Kind::DoubleTimeseries:
                result = std::make_shared<DoubleTimeseriesObject>( );
                break;
            case Kind::GNSSAltitudeTimeseries:
                result = std::make_shared<GNSSAltitudeTimeseriesObject>( );
                break;
            case Kind::GNSSLatitudeTimeseries:
                result = std::make_shared<GNSSLatitudeTimeseriesObject>( );
                break;
            case Kind::GNSSLongitudeTimeseries:
                result = std::make_shared<GNSSLongitudeTimeseriesObject>( );
                break;
            case Kind::GyroCourseTimeseries:
                result = std::make_shared<GyroCourseTimeseriesObject>( );
                break;
            case Kind::GyroHeadingMagneticNorthTimeseries:
                result = std::make_shared<GyroHeadingMagneticNorthTimeseriesObject>( );
                break;
            case Kind::GyroHeadingTrueNorthTimeseries:
                result = std::make_shared<GyroHeadingTrueNorthTimeseriesObject>( );
                break;
            case Kind::GyroPitchTimeseries:
                result = std::make_shared<GyroPitchTimeseriesObject>( );
                break;
            case Kind::GyroRateOfTurnTimeseries:
                result = std::make_shared<GyroRateOfTurnTimeseriesObject>( );
                break;
            case Kind::GyroRollTimeseries:
                result = std::make_shared<GyroRollTimeseriesObject>( );
                break;
            case Kind::GyroSpeedTimeseries:
                result = std::make_shared<GyroSpeedTimeseriesObject>( );
                break;
            case Kind::RadarLatitudeTimeseries:
                result = std::make_shared<RadarLatitudeTimeseriesObject>( );
                break;
            case Kind::RadarLongitudeTimeseries:
                result = std::make_shared<RadarLongitudeTimeseriesObject>( );
                break;
            case Kind::RadomeDewPointTimeseries:
                result = std::make_shared<RadomeDewPointTimeseriesObject>( );
                break;
            case Kind::RadomePressureTimeseries:
                result = std::make_shared<RadomePressureTimeseriesObject>( );
                break;
            case Kind::RadomeTemperatureTimeseries:
                result = std::make_shared<RadomeTemperatureTimeseriesObject>( );
                break;
            case Kind::VesselDraughtTimeseries:
                result = std::make_shared<VesselDraughtTimeseriesObject>( );
                break;
            case Kind::ViewLatitudeTimeseries:
                result = std::make_shared<ViewLatitudeTimeseriesObject>( );
                break;
            case Kind::ViewLongitudeTimeseries:
                result = std::make_shared<ViewLongitudeTimeseriesObject>( );
                break;
            case Kind::ViewZoomLevelTimeseries:
                result = std::make_shared<ViewZoomLevelTimeseriesObject>( );
                break;
            case Kind::WeatherStationAbsoluteHumidityTimeseries:
                result = std::make_shared<WeatherStationAbsoluteHumidityTimeseriesObject>( );
                break;
            case Kind::WeatherStationAirTemperatureTimeseries:
                result = std::make_shared<WeatherStationAirTemperatureTimeseriesObject>( );
                break;
            case Kind::WeatherStationBarometricPressureTimeseries:
                result = std::make_shared<WeatherStationBarometricPressureTimeseriesObject>( );
                break;
            case Kind::WeatherStationDewPointTimeseries:
                result = std::make_shared<WeatherStationDewPointTimeseriesObject>( );
                break;
            case Kind::WeatherStationRelativeHumidityTimeseries:
                result = std::make_shared<WeatherStationRelativeHumidityTimeseriesObject>( );
                break;
            case Kind::WeatherStationWaterTemperatureTimeseries:
                result = std::make_shared<WeatherStationWaterTemperatureTimeseriesObject>( );
                break;
            case Kind::WeatherStationWindDirectionTimeseries:
                result = std::make_shared<WeatherStationWindDirectionTimeseriesObject>( );
                break;
            case Kind::WeatherStationWindSpeedTimeseries:
                result = std::make_shared<WeatherStationWindSpeedTimeseriesObject>( );
                break;
            case Kind::GeoPosition2DTimeseries:
                result = std::make_shared<GeoPosition2DTimeseriesObject>( );
                break;
            case Kind::AisAidToNavigationPositionTimeseries:
                result = std::make_shared<AisAidToNavigationPositionTimeseriesObject>( );
                break;
            case Kind::GeoPosition3DTimeseries:
                result = std::make_shared<GeoPosition3DTimeseriesObject>( );
                break;
            case Kind::GuidTimeseries:
                result = std::make_shared<GuidTimeseriesObject>( );
                break;
            case Kind::Int16Timeseries:
                result = std::make_shared<Int16TimeseriesObject>( );
                break;
            case Kind::Int32Timeseries:
                result = std::make_shared<Int32TimeseriesObject>( );
                break;
            case Kind::RadarAzimuthOffsetTimeseries:
                result = std::make_shared<RadarAzimuthOffsetTimeseriesObject>( );
                break;
            case Kind::RadarFastTimeConstantLevelTimeseries:
                result = std::make_shared<RadarFastTimeConstantLevelTimeseriesObject>( );
                break;
            case Kind::RadarFastTimeConstantModeTimeseries:
                result = std::make_shared<RadarFastTimeConstantModeTimeseriesObject>( );
                break;
            case Kind::RadarPulseTimeseries:
                result = std::make_shared<RadarPulseTimeseriesObject>( );
                break;
            case Kind::RadarSector1EndTimeseries:
                result = std::make_shared<RadarSector1EndTimeseriesObject>( );
                break;
            case Kind::RadarSector1StartTimeseries:
                result = std::make_shared<RadarSector1StartTimeseriesObject>( );
                break;
            case Kind::RadarSector2EndTimeseries:
                result = std::make_shared<RadarSector2EndTimeseriesObject>( );
                break;
            case Kind::RadarSector2StartTimeseries:
                result = std::make_shared<RadarSector2StartTimeseriesObject>( );
                break;
            case Kind::RadarSensitivityTimeControlLevelTimeseries:
                result = std::make_shared<RadarSensitivityTimeControlLevelTimeseriesObject>( );
                break;
            case Kind::RadarTuningTimeseries:
                result = std::make_shared<RadarTuningTimeseriesObject>( );
                break;
            case Kind::VesselPersonsOnBoardTimeseries:
                result = std::make_shared<VesselPersonsOnBoardTimeseriesObject>( );
                break;
            case Kind::Int64Timeseries:
                result = std::make_shared<Int64TimeseriesObject>( );
                break;
            case Kind::Position2DTimeseries:
                result = std::make_shared<Position2DTimeseriesObject>( );
                break;
            case Kind::Position3DTimeseries:
                result = std::make_shared<Position3DTimeseriesObject>( );
                break;
            case Kind::ReferenceTimeseries:
                result = std::make_shared<ReferenceTimeseriesObject>( );
                break;
            case Kind::SByteTimeseries:
                result = std::make_shared<SByteTimeseriesObject>( );
                break;
            case Kind::SingleTimeseries:
                result = std::make_shared<SingleTimeseriesObject>( );
                break;
            case Kind::StringTimeseries:
                result = std::make_shared<StringTimeseriesObject>( );
                break;
            case Kind::TimeSpanTimeseries:
                result = std::make_shared<TimeSpanTimeseriesObject>( );
                break;
            case Kind::UInt16Timeseries:
                result = std::make_shared<UInt16TimeseriesObject>( );
                break;
            case Kind::UInt32Timeseries:
                result = std::make_shared<UInt32TimeseriesObject>( );
                break;
            case Kind::RadomeStatusTimeseries:
                result = std::make_shared<RadomeStatusTimeseriesObject>( );
                break;
            case Kind::UInt64Timeseries:
                result = std::make_shared<UInt64TimeseriesObject>( );
                break;
            case Kind::TimeseriesCatalog:
                result = std::make_shared<TimeseriesCatalogObject>( );
                break;
            case Kind::TimeseriesInfo:
                result = std::make_shared<TimeseriesInfoObject>( );
                break;
            case Kind::TimeSpanTimeseriesValue:
                result = std::make_shared<TimeSpanTimeseriesValueObject>( );
                break;
            case Kind::TrackableItemTrackLink:
                result = std::make_shared<TrackableItemTrackLinkObject>( );
                break;
            case Kind::Track:
                result = std::make_shared<TrackObject>( );
                break;
            case Kind::Track3D:
                result = std::make_shared<Track3DObject>( );
                break;
            case Kind::TrackerFilterParameters:
                result = std::make_shared<TrackerFilterParametersObject>( );
                break;
            case Kind::TrackerFilterParametersConfiguration:
                result = std::make_shared<TrackerFilterParametersConfigurationObject>( );
                break;
            case Kind::TrackInfo:
                result = std::make_shared<TrackInfoObject>( );
                break;
            case Kind::TrackingServiceOptions:
                result = std::make_shared<TrackingServiceOptionsObject>( );
                break;
            case Kind::TrackLink:
                result = std::make_shared<TrackLinkObject>( );
                break;
            case Kind::TrackValue:
                result = std::make_shared<TrackValueObject>( );
                break;
            case Kind::TrackValue3D:
                result = std::make_shared<TrackValue3DObject>( );
                break;
            case Kind::UInt16TimeseriesValue:
                result = std::make_shared<UInt16TimeseriesValueObject>( );
                break;
            case Kind::UInt32TimeseriesValue:
                result = std::make_shared<UInt32TimeseriesValueObject>( );
                break;
            case Kind::UInt64TimeseriesValue:
                result = std::make_shared<UInt64TimeseriesValueObject>( );
                break;
            case Kind::VehicleType:
                result = std::make_shared<VehicleTypeObject>( );
                break;
            case Kind::VesselType:
                result = std::make_shared<VesselTypeObject>( );
                break;
            case Kind::View:
                result = std::make_shared<ViewObject>( );
                break;
            case Kind::ViewCameraLink:
                result = std::make_shared<ViewCameraLinkObject>( );
                break;
            case Kind::ViewTrackerLink:
                result = std::make_shared<ViewTrackerLinkObject>( );
                break;
            case Kind::WeatherStationCommand:
                result = std::make_shared<WeatherStationCommandObject>( );
                break;
            case Kind::WeatherStationCommandReply:
                result = std::make_shared<WeatherStationCommandReplyObject>( );
                break;
            case Kind::WeatherStationConfiguration:
                result = std::make_shared<WeatherStationConfigurationObject>( );
                break;
            case Kind::CircularZone:
                result = std::make_shared<CircularZoneObject>( );
                break;
            case Kind::PolygonZone:
                result = std::make_shared<PolygonZoneObject>( );
                break;
            case Kind::ZoneExceptions:
                result = std::make_shared<ZoneExceptionsObject>( );
                break;
            case Kind::ZoneExceptionsVesselLink:
                result = std::make_shared<ZoneExceptionsVesselLinkObject>( );
                break;
            case Kind::ZoneTrackAlarm:
                result = std::make_shared<ZoneTrackAlarmObject>( );
                break;
        }
        return result;
    }
}
