CREATE OR ALTER VIEW AircraftTypeView
AS
 SELECT
  [AircraftType].[Id],
  [AircraftType].[RowVersion],
  [AircraftType].[Name]
 FROM [AircraftType]

go 

CREATE OR ALTER VIEW AisMessageView
AS
 SELECT
  [AisMessage].[Id],
  [AisMessage].[EntityType],
  [AisMessage].[RowVersion],
  [AisMessage].[AisTransceiver],
  [AisMessage].[ReceivedTimestamp],
  [AisMessage].[MessageSequenceNumber],
  [AisMessage].[Repeat],
  [AisMessage].[Mmsi]
 FROM [AisMessage]

go 

CREATE OR ALTER VIEW AidToNavigationReportMessageView
AS
 SELECT
  AisMessageView.*,
  [AidToNavigationReportMessage].[NavigationalAidType],
  [AidToNavigationReportMessage].[Name],
  [AidToNavigationReportMessage].[PositionAccuracy],
  [AidToNavigationReportMessage].[Longitude],
  [AidToNavigationReportMessage].[Latitude],
  [AidToNavigationReportMessage].[DimensionToBow],
  [AidToNavigationReportMessage].[DimensionToStern],
  [AidToNavigationReportMessage].[DimensionToPort],
  [AidToNavigationReportMessage].[DimensionToStarboard],
  [AidToNavigationReportMessage].[PositionFixType],
  [AidToNavigationReportMessage].[Timestamp],
  [AidToNavigationReportMessage].[OffPosition],
  [AidToNavigationReportMessage].[RegionalReserved],
  [AidToNavigationReportMessage].[Raim],
  [AidToNavigationReportMessage].[VirtualAid],
  [AidToNavigationReportMessage].[Assigned],
  [AidToNavigationReportMessage].[Spare],
  [AidToNavigationReportMessage].[NameExtension]
 FROM [AidToNavigationReportMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AidToNavigationReportMessage].Id)

go 

CREATE OR ALTER VIEW AisAddressedSafetyRelatedMessageView
AS
 SELECT
  AisMessageView.*,
  [AisAddressedSafetyRelatedMessage].[SequenceNumber],
  [AisAddressedSafetyRelatedMessage].[DestinationMmsi],
  [AisAddressedSafetyRelatedMessage].[RetransmitFlag],
  [AisAddressedSafetyRelatedMessage].[Spare],
  [AisAddressedSafetyRelatedMessage].[Text]
 FROM [AisAddressedSafetyRelatedMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisAddressedSafetyRelatedMessage].Id)

go 

CREATE OR ALTER VIEW AisBaseStationReportMessageView
AS
 SELECT
  AisMessageView.*,
  [AisBaseStationReportMessage].[Timestamp],
  [AisBaseStationReportMessage].[PositionAccuracy],
  [AisBaseStationReportMessage].[Longitude],
  [AisBaseStationReportMessage].[Latitude],
  [AisBaseStationReportMessage].[PositionFixType],
  [AisBaseStationReportMessage].[Spare],
  [AisBaseStationReportMessage].[Raim],
  [AisBaseStationReportMessage].[RadioStatus]
 FROM [AisBaseStationReportMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisBaseStationReportMessage].Id)

go 

CREATE OR ALTER VIEW AisBinaryAcknowledgeMessageView
AS
 SELECT
  AisMessageView.*,
  [AisBinaryAcknowledgeMessage].[Spare],
  [AisBinaryAcknowledgeMessage].[SequenceNumber1],
  [AisBinaryAcknowledgeMessage].[Mmsi1],
  [AisBinaryAcknowledgeMessage].[SequenceNumber2],
  [AisBinaryAcknowledgeMessage].[Mmsi2],
  [AisBinaryAcknowledgeMessage].[SequenceNumber3],
  [AisBinaryAcknowledgeMessage].[Mmsi3],
  [AisBinaryAcknowledgeMessage].[SequenceNumber4],
  [AisBinaryAcknowledgeMessage].[Mmsi4]
 FROM [AisBinaryAcknowledgeMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisBinaryAcknowledgeMessage].Id)

go 

CREATE OR ALTER VIEW AisBinaryAddressedMessageView
AS
 SELECT
  AisMessageView.*,
  [AisBinaryAddressedMessage].[SequenceNumber],
  [AisBinaryAddressedMessage].[DestinationMmsi],
  [AisBinaryAddressedMessage].[RetransmitFlag],
  [AisBinaryAddressedMessage].[Spare],
  [AisBinaryAddressedMessage].[DesignatedAreaCode],
  [AisBinaryAddressedMessage].[FunctionalId],
  [AisBinaryAddressedMessage].[Data]
 FROM [AisBinaryAddressedMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisBinaryAddressedMessage].Id)

go 

CREATE OR ALTER VIEW AisBinaryBroadcastMessageView
AS
 SELECT
  AisMessageView.*,
  [AisBinaryBroadcastMessage].[Spare],
  [AisBinaryBroadcastMessage].[DesignatedAreaCode],
  [AisBinaryBroadcastMessage].[FunctionalId],
  [AisBinaryBroadcastMessage].[Data]
 FROM [AisBinaryBroadcastMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisBinaryBroadcastMessage].Id)

go 

CREATE OR ALTER VIEW AisDataLinkManagementMessageView
AS
 SELECT
  AisMessageView.*,
  [AisDataLinkManagementMessage].[Spare],
  [AisDataLinkManagementMessage].[Offset1],
  [AisDataLinkManagementMessage].[ReservedSlots1],
  [AisDataLinkManagementMessage].[Timeout1],
  [AisDataLinkManagementMessage].[Increment1],
  [AisDataLinkManagementMessage].[Offset2],
  [AisDataLinkManagementMessage].[ReservedSlots2],
  [AisDataLinkManagementMessage].[Timeout2],
  [AisDataLinkManagementMessage].[Increment2],
  [AisDataLinkManagementMessage].[Offset3],
  [AisDataLinkManagementMessage].[ReservedSlots3],
  [AisDataLinkManagementMessage].[Timeout3],
  [AisDataLinkManagementMessage].[Increment3],
  [AisDataLinkManagementMessage].[Offset4],
  [AisDataLinkManagementMessage].[ReservedSlots4],
  [AisDataLinkManagementMessage].[Timeout4],
  [AisDataLinkManagementMessage].[Increment4]
 FROM [AisDataLinkManagementMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisDataLinkManagementMessage].Id)

go 

CREATE OR ALTER VIEW AisExtendedClassBCsPositionReportMessageView
AS
 SELECT
  AisMessageView.*,
  [AisExtendedClassBCsPositionReportMessage].[Reserved],
  [AisExtendedClassBCsPositionReportMessage].[SpeedOverGround],
  [AisExtendedClassBCsPositionReportMessage].[PositionAccuracy],
  [AisExtendedClassBCsPositionReportMessage].[Longitude],
  [AisExtendedClassBCsPositionReportMessage].[Latitude],
  [AisExtendedClassBCsPositionReportMessage].[CourseOverGround],
  [AisExtendedClassBCsPositionReportMessage].[TrueHeading],
  [AisExtendedClassBCsPositionReportMessage].[Timestamp],
  [AisExtendedClassBCsPositionReportMessage].[RegionalReserved],
  [AisExtendedClassBCsPositionReportMessage].[Name],
  [AisExtendedClassBCsPositionReportMessage].[ShipType],
  [AisExtendedClassBCsPositionReportMessage].[DimensionToBow],
  [AisExtendedClassBCsPositionReportMessage].[DimensionToStern],
  [AisExtendedClassBCsPositionReportMessage].[DimensionToPort],
  [AisExtendedClassBCsPositionReportMessage].[DimensionToStarboard],
  [AisExtendedClassBCsPositionReportMessage].[PositionFixType],
  [AisExtendedClassBCsPositionReportMessage].[Raim],
  [AisExtendedClassBCsPositionReportMessage].[DataTerminalReady],
  [AisExtendedClassBCsPositionReportMessage].[Assigned],
  [AisExtendedClassBCsPositionReportMessage].[Spare]
 FROM [AisExtendedClassBCsPositionReportMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisExtendedClassBCsPositionReportMessage].Id)

go 

CREATE OR ALTER VIEW AisInterrogationMessageView
AS
 SELECT
  AisMessageView.*,
  [AisInterrogationMessage].[InterrogatedMmsi],
  [AisInterrogationMessage].[FirstMessageType],
  [AisInterrogationMessage].[FirstSlotOffset],
  [AisInterrogationMessage].[SecondMessageType],
  [AisInterrogationMessage].[SecondSlotOffset],
  [AisInterrogationMessage].[SecondStationInterrogationMmsi],
  [AisInterrogationMessage].[SecondStationFirstMessageType],
  [AisInterrogationMessage].[SecondStationFirstSlotOffset]
 FROM [AisInterrogationMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisInterrogationMessage].Id)

go 

CREATE OR ALTER VIEW AisPositionReportClassAMessageBaseView
AS
 SELECT
  AisMessageView.*,
  [AisPositionReportClassAMessageBase].[NavigationStatus],
  [AisPositionReportClassAMessageBase].[RateOfTurn],
  [AisPositionReportClassAMessageBase].[SpeedOverGround],
  [AisPositionReportClassAMessageBase].[PositionAccuracy],
  [AisPositionReportClassAMessageBase].[Longitude],
  [AisPositionReportClassAMessageBase].[Latitude],
  [AisPositionReportClassAMessageBase].[CourseOverGround],
  [AisPositionReportClassAMessageBase].[TrueHeading],
  [AisPositionReportClassAMessageBase].[Timestamp],
  [AisPositionReportClassAMessageBase].[ManeuverIndicator],
  [AisPositionReportClassAMessageBase].[Spare],
  [AisPositionReportClassAMessageBase].[Raim],
  [AisPositionReportClassAMessageBase].[RadioStatus]
 FROM [AisPositionReportClassAMessageBase]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisPositionReportClassAMessageBase].Id)

go 

CREATE OR ALTER VIEW AisPositionReportClassAAssignedScheduleMessageView
AS
 SELECT
  AisPositionReportClassAMessageBaseView.*
 FROM [AisPositionReportClassAAssignedScheduleMessage]
 JOIN AisPositionReportClassAMessageBaseView ON ([AisPositionReportClassAMessageBaseView].Id = [AisPositionReportClassAAssignedScheduleMessage].Id)

go 

CREATE OR ALTER VIEW AisPositionReportClassAMessageView
AS
 SELECT
  AisPositionReportClassAMessageBaseView.*
 FROM [AisPositionReportClassAMessage]
 JOIN AisPositionReportClassAMessageBaseView ON ([AisPositionReportClassAMessageBaseView].Id = [AisPositionReportClassAMessage].Id)

go 

CREATE OR ALTER VIEW AisPositionReportClassAResponseToInterrogationMessageView
AS
 SELECT
  AisPositionReportClassAMessageBaseView.*
 FROM [AisPositionReportClassAResponseToInterrogationMessage]
 JOIN AisPositionReportClassAMessageBaseView ON ([AisPositionReportClassAMessageBaseView].Id = [AisPositionReportClassAResponseToInterrogationMessage].Id)

go 

CREATE OR ALTER VIEW AisPositionReportForLongRangeApplicationsMessageView
AS
 SELECT
  AisMessageView.*,
  [AisPositionReportForLongRangeApplicationsMessage].[PositionAccuracy],
  [AisPositionReportForLongRangeApplicationsMessage].[Raim],
  [AisPositionReportForLongRangeApplicationsMessage].[NavigationStatus],
  [AisPositionReportForLongRangeApplicationsMessage].[Longitude],
  [AisPositionReportForLongRangeApplicationsMessage].[Latitude],
  [AisPositionReportForLongRangeApplicationsMessage].[SpeedOverGround],
  [AisPositionReportForLongRangeApplicationsMessage].[CourseOverGround],
  [AisPositionReportForLongRangeApplicationsMessage].[GnssPositionStatus],
  [AisPositionReportForLongRangeApplicationsMessage].[Spare]
 FROM [AisPositionReportForLongRangeApplicationsMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisPositionReportForLongRangeApplicationsMessage].Id)

go 

CREATE OR ALTER VIEW AisSafetyRelatedAcknowledgmentMessageView
AS
 SELECT
  AisMessageView.*,
  [AisSafetyRelatedAcknowledgmentMessage].[Spare],
  [AisSafetyRelatedAcknowledgmentMessage].[SequenceNumber1],
  [AisSafetyRelatedAcknowledgmentMessage].[Mmsi1],
  [AisSafetyRelatedAcknowledgmentMessage].[SequenceNumber2],
  [AisSafetyRelatedAcknowledgmentMessage].[Mmsi2],
  [AisSafetyRelatedAcknowledgmentMessage].[SequenceNumber3],
  [AisSafetyRelatedAcknowledgmentMessage].[Mmsi3],
  [AisSafetyRelatedAcknowledgmentMessage].[SequenceNumber4],
  [AisSafetyRelatedAcknowledgmentMessage].[Mmsi4]
 FROM [AisSafetyRelatedAcknowledgmentMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisSafetyRelatedAcknowledgmentMessage].Id)

go 

CREATE OR ALTER VIEW AisStandardClassBCsPositionReportMessageView
AS
 SELECT
  AisMessageView.*,
  [AisStandardClassBCsPositionReportMessage].[Reserved],
  [AisStandardClassBCsPositionReportMessage].[SpeedOverGround],
  [AisStandardClassBCsPositionReportMessage].[PositionAccuracy],
  [AisStandardClassBCsPositionReportMessage].[Longitude],
  [AisStandardClassBCsPositionReportMessage].[Latitude],
  [AisStandardClassBCsPositionReportMessage].[CourseOverGround],
  [AisStandardClassBCsPositionReportMessage].[TrueHeading],
  [AisStandardClassBCsPositionReportMessage].[Timestamp],
  [AisStandardClassBCsPositionReportMessage].[RegionalReserved],
  [AisStandardClassBCsPositionReportMessage].[IsCsUnit],
  [AisStandardClassBCsPositionReportMessage].[HasDisplay],
  [AisStandardClassBCsPositionReportMessage].[HasDscCapability],
  [AisStandardClassBCsPositionReportMessage].[Band],
  [AisStandardClassBCsPositionReportMessage].[CanAcceptMessage22],
  [AisStandardClassBCsPositionReportMessage].[Assigned],
  [AisStandardClassBCsPositionReportMessage].[Raim],
  [AisStandardClassBCsPositionReportMessage].[RadioStatus]
 FROM [AisStandardClassBCsPositionReportMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisStandardClassBCsPositionReportMessage].Id)

go 

CREATE OR ALTER VIEW AisStandardSarAircraftPositionReportMessageView
AS
 SELECT
  AisMessageView.*,
  [AisStandardSarAircraftPositionReportMessage].[Altitude],
  [AisStandardSarAircraftPositionReportMessage].[SpeedOverGround],
  [AisStandardSarAircraftPositionReportMessage].[PositionAccuracy],
  [AisStandardSarAircraftPositionReportMessage].[Longitude],
  [AisStandardSarAircraftPositionReportMessage].[Latitude],
  [AisStandardSarAircraftPositionReportMessage].[CourseOverGround],
  [AisStandardSarAircraftPositionReportMessage].[Timestamp],
  [AisStandardSarAircraftPositionReportMessage].[Reserved],
  [AisStandardSarAircraftPositionReportMessage].[DataTerminalReady],
  [AisStandardSarAircraftPositionReportMessage].[Spare],
  [AisStandardSarAircraftPositionReportMessage].[Assigned],
  [AisStandardSarAircraftPositionReportMessage].[Raim],
  [AisStandardSarAircraftPositionReportMessage].[RadioStatus]
 FROM [AisStandardSarAircraftPositionReportMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisStandardSarAircraftPositionReportMessage].Id)

go 

CREATE OR ALTER VIEW AisStaticAndVoyageRelatedDataMessageView
AS
 SELECT
  AisMessageView.*,
  [AisStaticAndVoyageRelatedDataMessage].[AisVersion],
  [AisStaticAndVoyageRelatedDataMessage].[ImoNumber],
  [AisStaticAndVoyageRelatedDataMessage].[Callsign],
  [AisStaticAndVoyageRelatedDataMessage].[ShipName],
  [AisStaticAndVoyageRelatedDataMessage].[ShipType],
  [AisStaticAndVoyageRelatedDataMessage].[DimensionToBow],
  [AisStaticAndVoyageRelatedDataMessage].[DimensionToStern],
  [AisStaticAndVoyageRelatedDataMessage].[DimensionToPort],
  [AisStaticAndVoyageRelatedDataMessage].[DimensionToStarboard],
  [AisStaticAndVoyageRelatedDataMessage].[PositionFixType],
  [AisStaticAndVoyageRelatedDataMessage].[EstimatedTimeOfArrival],
  [AisStaticAndVoyageRelatedDataMessage].[Draught],
  [AisStaticAndVoyageRelatedDataMessage].[Destination],
  [AisStaticAndVoyageRelatedDataMessage].[DataTerminalReady],
  [AisStaticAndVoyageRelatedDataMessage].[Spare]
 FROM [AisStaticAndVoyageRelatedDataMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisStaticAndVoyageRelatedDataMessage].Id)

go 

CREATE OR ALTER VIEW AisStaticDataReportMessageView
AS
 SELECT
  AisMessageView.*,
  [AisStaticDataReportMessage].[PartNumber]
 FROM [AisStaticDataReportMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisStaticDataReportMessage].Id)

go 

CREATE OR ALTER VIEW AisStaticDataReportPartAMessageView
AS
 SELECT
  AisStaticDataReportMessageView.*,
  [AisStaticDataReportPartAMessage].[ShipName],
  [AisStaticDataReportPartAMessage].[Spare]
 FROM [AisStaticDataReportPartAMessage]
 JOIN AisStaticDataReportMessageView ON ([AisStaticDataReportMessageView].Id = [AisStaticDataReportPartAMessage].Id)

go 

CREATE OR ALTER VIEW AisStaticDataReportPartBMessageView
AS
 SELECT
  AisStaticDataReportMessageView.*,
  [AisStaticDataReportPartBMessage].[ShipType],
  [AisStaticDataReportPartBMessage].[VendorId],
  [AisStaticDataReportPartBMessage].[UnitModelCode],
  [AisStaticDataReportPartBMessage].[SerialNumber],
  [AisStaticDataReportPartBMessage].[Callsign],
  [AisStaticDataReportPartBMessage].[DimensionToBow],
  [AisStaticDataReportPartBMessage].[DimensionToStern],
  [AisStaticDataReportPartBMessage].[DimensionToPort],
  [AisStaticDataReportPartBMessage].[DimensionToStarboard],
  [AisStaticDataReportPartBMessage].[MothershipMmsi],
  [AisStaticDataReportPartBMessage].[PositionFixType],
  [AisStaticDataReportPartBMessage].[Spare]
 FROM [AisStaticDataReportPartBMessage]
 JOIN AisStaticDataReportMessageView ON ([AisStaticDataReportMessageView].Id = [AisStaticDataReportPartBMessage].Id)

go 

CREATE OR ALTER VIEW AisUtcAndDateInquiryMessageView
AS
 SELECT
  AisMessageView.*,
  [AisUtcAndDateInquiryMessage].[Spare1],
  [AisUtcAndDateInquiryMessage].[DestinationMmsi],
  [AisUtcAndDateInquiryMessage].[Spare2]
 FROM [AisUtcAndDateInquiryMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisUtcAndDateInquiryMessage].Id)

go 

CREATE OR ALTER VIEW AisUtcAndDateResponseMessageView
AS
 SELECT
  AisMessageView.*,
  [AisUtcAndDateResponseMessage].[Datetime],
  [AisUtcAndDateResponseMessage].[PositionAccuracy],
  [AisUtcAndDateResponseMessage].[Longitude],
  [AisUtcAndDateResponseMessage].[Latitude],
  [AisUtcAndDateResponseMessage].[PositionFixType],
  [AisUtcAndDateResponseMessage].[Spare],
  [AisUtcAndDateResponseMessage].[Raim],
  [AisUtcAndDateResponseMessage].[RadioStatus]
 FROM [AisUtcAndDateResponseMessage]
 JOIN AisMessageView ON ([AisMessageView].Id = [AisUtcAndDateResponseMessage].Id)

go 

CREATE OR ALTER VIEW AisTransceiverCommandView
AS
 SELECT
  [AisTransceiverCommand].[Id],
  [AisTransceiverCommand].[RowVersion],
  [AisTransceiverCommand].[AisTransceiver],
  [AisTransceiverCommand].[Timestamp],
  [AisTransceiverCommand].[DeviceCommandSourceType],
  [AisTransceiverCommand].[DeviceCommandSourceId],
  [AisTransceiverCommand].[Reply]
 FROM [AisTransceiverCommand]

go 

CREATE OR ALTER VIEW AisTransceiverCommandReplyView
AS
 SELECT
  [AisTransceiverCommandReply].[Id],
  [AisTransceiverCommandReply].[RowVersion],
  [AisTransceiverCommandReply].[AisTransceiver],
  [AisTransceiverCommandReply].[Timestamp],
  [AisTransceiverCommandReply].[Command],
  [AisTransceiverCommandReply].[Status],
  [AisTransceiverCommandReply].[Message]
 FROM [AisTransceiverCommandReply]

go 

CREATE OR ALTER VIEW AisTransceiverConfigurationView
AS
 SELECT
  [AisTransceiverConfiguration].[Id],
  [AisTransceiverConfiguration].[RowVersion],
  [AisTransceiverConfiguration].[AisTransceiver],
  [AisTransceiverConfiguration].[Timestamp],
  [AisTransceiverConfiguration].[UserName],
  [AisTransceiverConfiguration].[Password],
  [AisTransceiverConfiguration].[Latitude],
  [AisTransceiverConfiguration].[Longitude],
  [AisTransceiverConfiguration].[AisProviderLoginURL],
  [AisTransceiverConfiguration].[ComPort],
  [AisTransceiverConfiguration].[BaudRate],
  [AisTransceiverConfiguration].[FilterByArea],
  [AisTransceiverConfiguration].[UpperLeftCornerLatitude],
  [AisTransceiverConfiguration].[UpperLeftCornerLongitude],
  [AisTransceiverConfiguration].[BottomRightCornerLatitude],
  [AisTransceiverConfiguration].[BottomRightCornerLongitude],
  [AisTransceiverConfiguration].[AisProviderIPAddress],
  [AisTransceiverConfiguration].[AisProviderPort],
  [AisTransceiverConfiguration].[UseLogin],
  [AisTransceiverConfiguration].[AisProviderLoginPort],
  [AisTransceiverConfiguration].[CanSendAISMessage],
  [AisTransceiverConfiguration].[TextMessageHeader],
  [AisTransceiverConfiguration].[Urls],
  [AisTransceiverConfiguration].[UdpPort],
  [AisTransceiverConfiguration].[ConnectionType],
  [AisTransceiverConfiguration].[EnableRefreshAidToNavigationIn30sec],
  [AisTransceiverConfiguration].[EnableAidToNavigationFromFile],
  [AisTransceiverConfiguration].[AidToNavigationHeader],
  [AisTransceiverConfiguration].[SendingMMSI],
  [AisTransceiverConfiguration].[SourceUpdateRate],
  [AisTransceiverConfiguration].[EnableRefreshStayingStillTargetIn30sec],
  [AisTransceiverConfiguration].[ExcludeSendAisBaseStation],
  [AisTransceiverConfiguration].[ExcludeSendAisA],
  [AisTransceiverConfiguration].[EnableSendBaseStationAlarms],
  [AisTransceiverConfiguration].[AisWebConfig],
  [AisTransceiverConfiguration].[EnableBaseStation600],
  [AisTransceiverConfiguration].[BaseStation600IPAddress],
  [AisTransceiverConfiguration].[BaseStation600Port],
  [AisTransceiverConfiguration].[EsdInputCount],
  [AisTransceiverConfiguration].[StoreReceivedSentences],
  [AisTransceiverConfiguration].[StoreSentMessages],
  [AisTransceiverConfiguration].[StoreUnsentMessages]
 FROM [AisTransceiverConfiguration]

go 

CREATE OR ALTER VIEW AisTransceiverRawMessageView
AS
 SELECT
  [AisTransceiverRawMessage].[Id],
  [AisTransceiverRawMessage].[RowVersion],
  [AisTransceiverRawMessage].[AisTransceiver],
  [AisTransceiverRawMessage].[Timestamp],
  [AisTransceiverRawMessage].[IsSent],
  [AisTransceiverRawMessage].[Message]
 FROM [AisTransceiverRawMessage]

go 

CREATE OR ALTER VIEW AisTransceiverRawSentenceView
AS
 SELECT
  [AisTransceiverRawSentence].[Id],
  [AisTransceiverRawSentence].[RowVersion],
  [AisTransceiverRawSentence].[AisTransceiver],
  [AisTransceiverRawSentence].[Timestamp],
  [AisTransceiverRawSentence].[Sentence]
 FROM [AisTransceiverRawSentence]

go 

CREATE OR ALTER VIEW AlarmStateChangeView
AS
 SELECT
  [AlarmStateChange].[Id],
  [AlarmStateChange].[RowVersion],
  [AlarmStateChange].[Alarm],
  [AlarmStateChange].[Timestamp],
  [AlarmStateChange].[State]
 FROM [AlarmStateChange]

go 

CREATE OR ALTER VIEW BaseStationTypeView
AS
 SELECT
  [BaseStationType].[Id],
  [BaseStationType].[RowVersion],
  [BaseStationType].[Name]
 FROM [BaseStationType]

go 

CREATE OR ALTER VIEW BinaryTimeseriesValueView
AS
 SELECT
  [BinaryTimeseriesValue].[Id],
  [BinaryTimeseriesValue].[RowVersion],
  [BinaryTimeseriesValue].[Timeseries],
  [BinaryTimeseriesValue].[Timestamp],
  [BinaryTimeseriesValue].[Value]
 FROM [BinaryTimeseriesValue]

go 

CREATE OR ALTER VIEW BookmarkView
AS
 SELECT
  [Bookmark].[Id],
  [Bookmark].[RowVersion],
  [Bookmark].[View],
  [Bookmark].[Name],
  [Bookmark].[Timestamp],
  [Bookmark].[Latitude],
  [Bookmark].[Longitude],
  [Bookmark].[ZoomLevel]
 FROM [Bookmark]

go 

CREATE OR ALTER VIEW BooleanTimeseriesValueView
AS
 SELECT
  [BooleanTimeseriesValue].[Id],
  [BooleanTimeseriesValue].[RowVersion],
  [BooleanTimeseriesValue].[Timeseries],
  [BooleanTimeseriesValue].[Timestamp],
  [BooleanTimeseriesValue].[Value]
 FROM [BooleanTimeseriesValue]

go 

CREATE OR ALTER VIEW ByteTimeseriesValueView
AS
 SELECT
  [ByteTimeseriesValue].[Id],
  [ByteTimeseriesValue].[RowVersion],
  [ByteTimeseriesValue].[Timeseries],
  [ByteTimeseriesValue].[Timestamp],
  [ByteTimeseriesValue].[Value]
 FROM [ByteTimeseriesValue]

go 

CREATE OR ALTER VIEW CameraCommandView
AS
 SELECT
  [CameraCommand].[Id],
  [CameraCommand].[EntityType],
  [CameraCommand].[RowVersion],
  [CameraCommand].[Camera],
  [CameraCommand].[Timestamp],
  [CameraCommand].[DeviceCommandSourceType],
  [CameraCommand].[DeviceCommandSourceId],
  [CameraCommand].[Reply]
 FROM [CameraCommand]

go 

CREATE OR ALTER VIEW CameraCommandAbsoluteMoveView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandAbsoluteMove].[PositionPanTiltMode],
  [CameraCommandAbsoluteMove].[PanAngle],
  [CameraCommandAbsoluteMove].[TiltAngle],
  [CameraCommandAbsoluteMove].[PositionFocalLengthMode],
  [CameraCommandAbsoluteMove].[FocalLength],
  [CameraCommandAbsoluteMove].[SpeedPanTiltMode],
  [CameraCommandAbsoluteMove].[PanSpeed],
  [CameraCommandAbsoluteMove].[TiltSpeed],
  [CameraCommandAbsoluteMove].[SpeedFocalLengthMode],
  [CameraCommandAbsoluteMove].[ZoomSpeed]
 FROM [CameraCommandAbsoluteMove]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandAbsoluteMove].Id)

go 

CREATE OR ALTER VIEW CameraCommandAdjustPanTiltZoomView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandAdjustPanTiltZoom].[X],
  [CameraCommandAdjustPanTiltZoom].[Y],
  [CameraCommandAdjustPanTiltZoom].[Z]
 FROM [CameraCommandAdjustPanTiltZoom]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandAdjustPanTiltZoom].Id)

go 

CREATE OR ALTER VIEW CameraCommandContinuousMoveView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandContinuousMove].[Normalized],
  [CameraCommandContinuousMove].[PanVelocity],
  [CameraCommandContinuousMove].[TiltVelocity],
  [CameraCommandContinuousMove].[ZoomVelocity],
  [CameraCommandContinuousMove].[Duration]
 FROM [CameraCommandContinuousMove]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandContinuousMove].Id)

go 

CREATE OR ALTER VIEW CameraCommandGeoMoveView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandGeoMove].[Latitude],
  [CameraCommandGeoMove].[Longitude],
  [CameraCommandGeoMove].[Altitude],
  [CameraCommandGeoMove].[ViewportWidth],
  [CameraCommandGeoMove].[ViewportHeight]
 FROM [CameraCommandGeoMove]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandGeoMove].Id)

go 

CREATE OR ALTER VIEW CameraCommandRelativeMoveView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandRelativeMove].[Normalized],
  [CameraCommandRelativeMove].[PanAngle],
  [CameraCommandRelativeMove].[TiltAngle],
  [CameraCommandRelativeMove].[FocalLength],
  [CameraCommandRelativeMove].[PanSpeed],
  [CameraCommandRelativeMove].[TiltSpeed],
  [CameraCommandRelativeMove].[ZoomSpeed]
 FROM [CameraCommandRelativeMove]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandRelativeMove].Id)

go 

CREATE OR ALTER VIEW CameraCommandReleasePTZOwnershipView
AS
 SELECT
  CameraCommandView.*
 FROM [CameraCommandReleasePTZOwnership]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandReleasePTZOwnership].Id)

go 

CREATE OR ALTER VIEW CameraCommandRequestPTZOwnershipView
AS
 SELECT
  CameraCommandView.*
 FROM [CameraCommandRequestPTZOwnership]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandRequestPTZOwnership].Id)

go 

CREATE OR ALTER VIEW CameraCommandSetAutoFocusView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandSetAutoFocus].[Enabled]
 FROM [CameraCommandSetAutoFocus]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandSetAutoFocus].Id)

go 

CREATE OR ALTER VIEW CameraCommandSetBlackAndWhiteView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandSetBlackAndWhite].[Enabled]
 FROM [CameraCommandSetBlackAndWhite]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandSetBlackAndWhite].Id)

go 

CREATE OR ALTER VIEW CameraCommandSetFollowedView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandSetFollowed].[TrackId],
  [CameraCommandSetFollowed].[Reason]
 FROM [CameraCommandSetFollowed]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandSetFollowed].Id)

go 

CREATE OR ALTER VIEW CameraCommandSetInfraRedLampView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandSetInfraRedLamp].[Enabled]
 FROM [CameraCommandSetInfraRedLamp]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandSetInfraRedLamp].Id)

go 

CREATE OR ALTER VIEW CameraCommandSetWasherView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandSetWasher].[Enabled]
 FROM [CameraCommandSetWasher]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandSetWasher].Id)

go 

CREATE OR ALTER VIEW CameraCommandSetWiperView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandSetWiper].[Enabled]
 FROM [CameraCommandSetWiper]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandSetWiper].Id)

go 

CREATE OR ALTER VIEW CameraCommandStopView
AS
 SELECT
  CameraCommandView.*,
  [CameraCommandStop].[PanTilt],
  [CameraCommandStop].[Zoom]
 FROM [CameraCommandStop]
 JOIN CameraCommandView ON ([CameraCommandView].Id = [CameraCommandStop].Id)

go 

CREATE OR ALTER VIEW CameraCommandReplyView
AS
 SELECT
  [CameraCommandReply].[Id],
  [CameraCommandReply].[RowVersion],
  [CameraCommandReply].[Camera],
  [CameraCommandReply].[Timestamp],
  [CameraCommandReply].[Command],
  [CameraCommandReply].[Status],
  [CameraCommandReply].[Message],
  [CameraCommandReply].[PanAngle],
  [CameraCommandReply].[TiltAngle],
  [CameraCommandReply].[FocalLength]
 FROM [CameraCommandReply]

go 

CREATE OR ALTER VIEW CameraConfigurationView
AS
 SELECT
  [CameraConfiguration].[Id],
  [CameraConfiguration].[RowVersion],
  [CameraConfiguration].[Camera],
  [CameraConfiguration].[Timestamp],
  [CameraConfiguration].[CameraControlProtocol],
  [CameraConfiguration].[CameraAddress],
  [CameraConfiguration].[CameraPort],
  [CameraConfiguration].[CameraControlAddress],
  [CameraConfiguration].[CameraControlPort],
  [CameraConfiguration].[CameraUserName],
  [CameraConfiguration].[CameraPassword],
  [CameraConfiguration].[UseRtspUriOverride],
  [CameraConfiguration].[RtspUriOverride],
  [CameraConfiguration].[Latitude],
  [CameraConfiguration].[Longitude],
  [CameraConfiguration].[Altitude],
  [CameraConfiguration].[UseRelativePosition],
  [CameraConfiguration].[AzimuthFromGPS],
  [CameraConfiguration].[DistanceFromGPS],
  [CameraConfiguration].[PanTiltMode],
  [CameraConfiguration].[MinTiltAngle],
  [CameraConfiguration].[MaxTiltAngle],
  [CameraConfiguration].[MinTiltScaleAngle],
  [CameraConfiguration].[MaxTiltScaleAngle],
  [CameraConfiguration].[UseReverseTiltAngle],
  [CameraConfiguration].[UseReverseNormalizedTiltAngle],
  [CameraConfiguration].[MinTiltVelocity],
  [CameraConfiguration].[MaxTiltVelocity],
  [CameraConfiguration].[MinTiltSpeed],
  [CameraConfiguration].[MaxTiltSpeed],
  [CameraConfiguration].[MinPanAngle],
  [CameraConfiguration].[MaxPanAngle],
  [CameraConfiguration].[MinPanScaleAngle],
  [CameraConfiguration].[MaxPanScaleAngle],
  [CameraConfiguration].[UseReversePanAngle],
  [CameraConfiguration].[UseReverseNormalizedPanAngle],
  [CameraConfiguration].[MinPanVelocity],
  [CameraConfiguration].[MaxPanVelocity],
  [CameraConfiguration].[MinPanSpeed],
  [CameraConfiguration].[MaxPanSpeed],
  [CameraConfiguration].[FocalLengthMode],
  [CameraConfiguration].[MinFocalLength],
  [CameraConfiguration].[MaxFocalLength],
  [CameraConfiguration].[MinFocalLengthScale],
  [CameraConfiguration].[MaxFocalLengthScale],
  [CameraConfiguration].[MinZoomVelocity],
  [CameraConfiguration].[MaxZoomVelocity],
  [CameraConfiguration].[MinZoomSpeed],
  [CameraConfiguration].[MaxZoomSpeed],
  [CameraConfiguration].[ImageSensorWidth],
  [CameraConfiguration].[ImageSensorHeight],
  [CameraConfiguration].[HomePanAngle],
  [CameraConfiguration].[HomeTiltAngle],
  [CameraConfiguration].[HomeFocalLength],
  [CameraConfiguration].[PanOffset],
  [CameraConfiguration].[TiltOffset],
  [CameraConfiguration].[AimAltitude],
  [CameraConfiguration].[MinimumTargetWidth],
  [CameraConfiguration].[TargetLockTimeout],
  [CameraConfiguration].[UpdateStatusInterval],
  [CameraConfiguration].[ReadTimeout],
  [CameraConfiguration].[MoveCommandStatusDelay],
  [CameraConfiguration].[PtzProfileName],
  [CameraConfiguration].[PtzConfigurationToken],
  [CameraConfiguration].[VideoSourceToken]
 FROM [CameraConfiguration]

go 

CREATE OR ALTER VIEW CameraPanCalibrationView
AS
 SELECT
  [CameraPanCalibration].[Id],
  [CameraPanCalibration].[RowVersion],
  [CameraPanCalibration].[Camera],
  [CameraPanCalibration].[Timestamp]
 FROM [CameraPanCalibration]

go 

CREATE OR ALTER VIEW CameraPanCalibrationValueView
AS
 SELECT
  [CameraPanCalibrationValue].[Id],
  [CameraPanCalibrationValue].[RowVersion],
  [CameraPanCalibrationValue].[PanCalibration],
  [CameraPanCalibrationValue].[PanAngle],
  [CameraPanCalibrationValue].[PanOffset]
 FROM [CameraPanCalibrationValue]

go 

CREATE OR ALTER VIEW CameraStatusView
AS
 SELECT
  [CameraStatus].[Id],
  [CameraStatus].[RowVersion],
  [CameraStatus].[Camera],
  [CameraStatus].[Track],
  [CameraStatus].[Timestamp],
  [CameraStatus].[PositionPanTiltMode],
  [CameraStatus].[PanAngle],
  [CameraStatus].[TiltAngle],
  [CameraStatus].[PositionFocalLengthMode],
  [CameraStatus].[FocalLength],
  [CameraStatus].[PanTiltMoveStatus],
  [CameraStatus].[ZoomMoveStatus],
  [CameraStatus].[VelocityPanTiltMode],
  [CameraStatus].[PanVelocity],
  [CameraStatus].[TiltVelocity],
  [CameraStatus].[VelocityFocalLengthMode],
  [CameraStatus].[ZoomVelocity],
  [CameraStatus].[ActiveFeatures],
  [CameraStatus].[Error]
 FROM [CameraStatus]

go 

CREATE OR ALTER VIEW CameraTiltCalibrationView
AS
 SELECT
  [CameraTiltCalibration].[Id],
  [CameraTiltCalibration].[RowVersion],
  [CameraTiltCalibration].[Camera],
  [CameraTiltCalibration].[Timestamp]
 FROM [CameraTiltCalibration]

go 

CREATE OR ALTER VIEW CameraTiltCalibrationValueView
AS
 SELECT
  [CameraTiltCalibrationValue].[Id],
  [CameraTiltCalibrationValue].[RowVersion],
  [CameraTiltCalibrationValue].[TiltCalibration],
  [CameraTiltCalibrationValue].[PanAngle],
  [CameraTiltCalibrationValue].[TiltOffset]
 FROM [CameraTiltCalibrationValue]

go 

CREATE OR ALTER VIEW CameraZoomCalibrationView
AS
 SELECT
  [CameraZoomCalibration].[Id],
  [CameraZoomCalibration].[RowVersion],
  [CameraZoomCalibration].[Camera],
  [CameraZoomCalibration].[Timestamp]
 FROM [CameraZoomCalibration]

go 

CREATE OR ALTER VIEW CameraZoomCalibrationValueView
AS
 SELECT
  [CameraZoomCalibrationValue].[Id],
  [CameraZoomCalibrationValue].[RowVersion],
  [CameraZoomCalibrationValue].[ZoomCalibration],
  [CameraZoomCalibrationValue].[FocalLength],
  [CameraZoomCalibrationValue].[FocalLengthOffset]
 FROM [CameraZoomCalibrationValue]

go 

CREATE OR ALTER VIEW CatalogElementView
AS
 SELECT
  [CatalogElement].[Id],
  [CatalogElement].[EntityType],
  [CatalogElement].[RowVersion],
  [CatalogElement].[Catalog],
  [CatalogElement].[Name]
 FROM [CatalogElement]

go 

CREATE OR ALTER VIEW CatalogView
AS
 SELECT
  CatalogElementView.*
 FROM [Catalog]
 JOIN CatalogElementView ON ([CatalogElementView].Id = [Catalog].Id)

go 

CREATE OR ALTER VIEW ElementView
AS
 SELECT
  CatalogElementView.*,
  [Element].[ElementType]
 FROM [Element]
 JOIN CatalogElementView ON ([CatalogElementView].Id = [Element].Id)

go 

CREATE OR ALTER VIEW CollectionInfoView
AS
 SELECT
  [CollectionInfo].[Id],
  [CollectionInfo].[RowVersion],
  [CollectionInfo].[Count]
 FROM [CollectionInfo]

go 

CREATE OR ALTER VIEW CountryView
AS
 SELECT
  [Country].[Id],
  [Country].[RowVersion],
  [Country].[Name],
  [Country].[Code],
  [Country].[Alpha2],
  [Country].[Alpha3]
 FROM [Country]

go 

CREATE OR ALTER VIEW CursorInfoView
AS
 SELECT
  [CursorInfo].[Id],
  [CursorInfo].[RowVersion],
  [CursorInfo].[TypeCode]
 FROM [CursorInfo]

go 

CREATE OR ALTER VIEW DateTimeTimeseriesValueView
AS
 SELECT
  [DateTimeTimeseriesValue].[Id],
  [DateTimeTimeseriesValue].[RowVersion],
  [DateTimeTimeseriesValue].[Timeseries],
  [DateTimeTimeseriesValue].[Timestamp],
  [DateTimeTimeseriesValue].[Value]
 FROM [DateTimeTimeseriesValue]

go 

CREATE OR ALTER VIEW DeviceHostView
AS
 SELECT
  [DeviceHost].[Id],
  [DeviceHost].[RowVersion],
  [DeviceHost].[Name]
 FROM [DeviceHost]

go 

CREATE OR ALTER VIEW DeviceHostConfigurationView
AS
 SELECT
  [DeviceHostConfiguration].[Id],
  [DeviceHostConfiguration].[RowVersion],
  [DeviceHostConfiguration].[Host],
  [DeviceHostConfiguration].[Timestamp],
  [DeviceHostConfiguration].[Hostname],
  [DeviceHostConfiguration].[Port],
  [DeviceHostConfiguration].[QueueName]
 FROM [DeviceHostConfiguration]

go 

CREATE OR ALTER VIEW DeviceTypeView
AS
 SELECT
  [DeviceType].[Id],
  [DeviceType].[EntityType],
  [DeviceType].[RowVersion],
  [DeviceType].[AssemblyName],
  [DeviceType].[ClassName],
  [DeviceType].[ProxyAssemblyName],
  [DeviceType].[ProxyClassName]
 FROM [DeviceType]

go 

CREATE OR ALTER VIEW AisTransceiverTypeView
AS
 SELECT
  DeviceTypeView.*,
  [AisTransceiverType].[Name]
 FROM [AisTransceiverType]
 JOIN DeviceTypeView ON ([DeviceTypeView].Id = [AisTransceiverType].Id)

go 

CREATE OR ALTER VIEW CameraTypeView
AS
 SELECT
  DeviceTypeView.*,
  [CameraType].[Name],
  [CameraType].[CameraFeatures]
 FROM [CameraType]
 JOIN DeviceTypeView ON ([DeviceTypeView].Id = [CameraType].Id)

go 

CREATE OR ALTER VIEW GNSSDeviceTypeView
AS
 SELECT
  DeviceTypeView.*,
  [GNSSDeviceType].[Name]
 FROM [GNSSDeviceType]
 JOIN DeviceTypeView ON ([DeviceTypeView].Id = [GNSSDeviceType].Id)

go 

CREATE OR ALTER VIEW GyroDeviceTypeView
AS
 SELECT
  DeviceTypeView.*,
  [GyroDeviceType].[Name]
 FROM [GyroDeviceType]
 JOIN DeviceTypeView ON ([DeviceTypeView].Id = [GyroDeviceType].Id)

go 

CREATE OR ALTER VIEW LineInputDeviceTypeView
AS
 SELECT
  DeviceTypeView.*,
  [LineInputDeviceType].[Name]
 FROM [LineInputDeviceType]
 JOIN DeviceTypeView ON ([DeviceTypeView].Id = [LineInputDeviceType].Id)

go 

CREATE OR ALTER VIEW OilspillDetectorTypeView
AS
 SELECT
  DeviceTypeView.*,
  [OilspillDetectorType].[Name]
 FROM [OilspillDetectorType]
 JOIN DeviceTypeView ON ([DeviceTypeView].Id = [OilspillDetectorType].Id)

go 

CREATE OR ALTER VIEW RadarTypeView
AS
 SELECT
  DeviceTypeView.*,
  [RadarType].[Name],
  [RadarType].[PulseShortMinusValue],
  [RadarType].[PulseShortMinusDisplayText],
  [RadarType].[PulseShortValue],
  [RadarType].[PulseShortDisplayText],
  [RadarType].[PulseShortPlusValue],
  [RadarType].[PulseShortPlusDisplayText],
  [RadarType].[PulseMediumMinusValue],
  [RadarType].[PulseMediumMinusDisplayText],
  [RadarType].[PulseMediumValue],
  [RadarType].[PulseMediumDisplayText],
  [RadarType].[PulseMediumPlusValue],
  [RadarType].[PulseMediumPlusDisplayText],
  [RadarType].[PulseLongMinusValue],
  [RadarType].[PulseLongMinusDisplayText],
  [RadarType].[PulseLongValue],
  [RadarType].[PulseLongDisplayText],
  [RadarType].[PulseLongPlusValue],
  [RadarType].[PulseLongPlusDisplayText]
 FROM [RadarType]
 JOIN DeviceTypeView ON ([DeviceTypeView].Id = [RadarType].Id)

go 

CREATE OR ALTER VIEW RadioTypeView
AS
 SELECT
  DeviceTypeView.*,
  [RadioType].[Name]
 FROM [RadioType]
 JOIN DeviceTypeView ON ([DeviceTypeView].Id = [RadioType].Id)

go 

CREATE OR ALTER VIEW RadomeTypeView
AS
 SELECT
  DeviceTypeView.*,
  [RadomeType].[Name]
 FROM [RadomeType]
 JOIN DeviceTypeView ON ([DeviceTypeView].Id = [RadomeType].Id)

go 

CREATE OR ALTER VIEW WeatherStationTypeView
AS
 SELECT
  DeviceTypeView.*,
  [WeatherStationType].[Name]
 FROM [WeatherStationType]
 JOIN DeviceTypeView ON ([DeviceTypeView].Id = [WeatherStationType].Id)

go 

CREATE OR ALTER VIEW DoubleTimeseriesValueView
AS
 SELECT
  [DoubleTimeseriesValue].[Id],
  [DoubleTimeseriesValue].[RowVersion],
  [DoubleTimeseriesValue].[Timeseries],
  [DoubleTimeseriesValue].[Timestamp],
  [DoubleTimeseriesValue].[Value]
 FROM [DoubleTimeseriesValue]

go 

CREATE OR ALTER VIEW FacilityTypeView
AS
 SELECT
  [FacilityType].[Id],
  [FacilityType].[RowVersion],
  [FacilityType].[Name]
 FROM [FacilityType]

go 

CREATE OR ALTER VIEW GeoPosition2DTimeseriesValueView
AS
 SELECT
  [GeoPosition2DTimeseriesValue].[Id],
  [GeoPosition2DTimeseriesValue].[RowVersion],
  [GeoPosition2DTimeseriesValue].[Timeseries],
  [GeoPosition2DTimeseriesValue].[Timestamp],
  [GeoPosition2DTimeseriesValue].[Latitude],
  [GeoPosition2DTimeseriesValue].[Longitude]
 FROM [GeoPosition2DTimeseriesValue]

go 

CREATE OR ALTER VIEW GeoPosition3DTimeseriesValueView
AS
 SELECT
  [GeoPosition3DTimeseriesValue].[Id],
  [GeoPosition3DTimeseriesValue].[RowVersion],
  [GeoPosition3DTimeseriesValue].[Timeseries],
  [GeoPosition3DTimeseriesValue].[Timestamp],
  [GeoPosition3DTimeseriesValue].[Latitude],
  [GeoPosition3DTimeseriesValue].[Longitude],
  [GeoPosition3DTimeseriesValue].[Altitude]
 FROM [GeoPosition3DTimeseriesValue]

go 

CREATE OR ALTER VIEW GNSSDeviceCommandView
AS
 SELECT
  [GNSSDeviceCommand].[Id],
  [GNSSDeviceCommand].[RowVersion],
  [GNSSDeviceCommand].[GNSSDevice],
  [GNSSDeviceCommand].[Timestamp],
  [GNSSDeviceCommand].[DeviceCommandSourceType],
  [GNSSDeviceCommand].[DeviceCommandSourceId],
  [GNSSDeviceCommand].[Reply]
 FROM [GNSSDeviceCommand]

go 

CREATE OR ALTER VIEW GNSSDeviceCommandReplyView
AS
 SELECT
  [GNSSDeviceCommandReply].[Id],
  [GNSSDeviceCommandReply].[RowVersion],
  [GNSSDeviceCommandReply].[GNSSDevice],
  [GNSSDeviceCommandReply].[Timestamp],
  [GNSSDeviceCommandReply].[Command],
  [GNSSDeviceCommandReply].[Status],
  [GNSSDeviceCommandReply].[Message]
 FROM [GNSSDeviceCommandReply]

go 

CREATE OR ALTER VIEW GNSSDeviceConfigurationView
AS
 SELECT
  [GNSSDeviceConfiguration].[Id],
  [GNSSDeviceConfiguration].[RowVersion],
  [GNSSDeviceConfiguration].[GNSSDevice],
  [GNSSDeviceConfiguration].[Timestamp],
  [GNSSDeviceConfiguration].[DefaultLatitude],
  [GNSSDeviceConfiguration].[DefaultLongitude],
  [GNSSDeviceConfiguration].[DefaultAltitude],
  [GNSSDeviceConfiguration].[LatitudeOffset],
  [GNSSDeviceConfiguration].[LongitudeOffset],
  [GNSSDeviceConfiguration].[AltitudeOffset]
 FROM [GNSSDeviceConfiguration]

go 

CREATE OR ALTER VIEW GuidTimeseriesValueView
AS
 SELECT
  [GuidTimeseriesValue].[Id],
  [GuidTimeseriesValue].[RowVersion],
  [GuidTimeseriesValue].[Timeseries],
  [GuidTimeseriesValue].[Timestamp],
  [GuidTimeseriesValue].[Value]
 FROM [GuidTimeseriesValue]

go 

CREATE OR ALTER VIEW GyroDeviceCommandView
AS
 SELECT
  [GyroDeviceCommand].[Id],
  [GyroDeviceCommand].[RowVersion],
  [GyroDeviceCommand].[GyroDevice],
  [GyroDeviceCommand].[Timestamp],
  [GyroDeviceCommand].[DeviceCommandSourceType],
  [GyroDeviceCommand].[DeviceCommandSourceId],
  [GyroDeviceCommand].[Reply]
 FROM [GyroDeviceCommand]

go 

CREATE OR ALTER VIEW GyroDeviceCommandReplyView
AS
 SELECT
  [GyroDeviceCommandReply].[Id],
  [GyroDeviceCommandReply].[RowVersion],
  [GyroDeviceCommandReply].[GyroDevice],
  [GyroDeviceCommandReply].[Timestamp],
  [GyroDeviceCommandReply].[Command],
  [GyroDeviceCommandReply].[Status],
  [GyroDeviceCommandReply].[Message]
 FROM [GyroDeviceCommandReply]

go 

CREATE OR ALTER VIEW GyroDeviceConfigurationView
AS
 SELECT
  [GyroDeviceConfiguration].[Id],
  [GyroDeviceConfiguration].[RowVersion],
  [GyroDeviceConfiguration].[GyroDevice],
  [GyroDeviceConfiguration].[Timestamp],
  [GyroDeviceConfiguration].[DefaultHeadingTrueNorth],
  [GyroDeviceConfiguration].[DefaultMagneticTrueNorth],
  [GyroDeviceConfiguration].[HeadingTrueNorthOffset],
  [GyroDeviceConfiguration].[HeadingMagneticNorthOffset],
  [GyroDeviceConfiguration].[PitchTransducerName],
  [GyroDeviceConfiguration].[RollTransducerName]
 FROM [GyroDeviceConfiguration]

go 

CREATE OR ALTER VIEW IdentityView
AS
 SELECT
  [Identity].[Id],
  [Identity].[EntityType],
  [Identity].[RowVersion]
 FROM [Identity]

go 

CREATE OR ALTER VIEW CallsignView
AS
 SELECT
  IdentityView.*,
  [Callsign].[Identifier]
 FROM [Callsign]
 JOIN IdentityView ON ([IdentityView].Id = [Callsign].Id)

go 

CREATE OR ALTER VIEW InternationalMaritimeOrganizationNumberView
AS
 SELECT
  IdentityView.*,
  [InternationalMaritimeOrganizationNumber].[Identifier]
 FROM [InternationalMaritimeOrganizationNumber]
 JOIN IdentityView ON ([IdentityView].Id = [InternationalMaritimeOrganizationNumber].Id)

go 

CREATE OR ALTER VIEW MaritimeMobileServiceIdentityView
AS
 SELECT
  IdentityView.*,
  [MaritimeMobileServiceIdentity].[Identifier]
 FROM [MaritimeMobileServiceIdentity]
 JOIN IdentityView ON ([IdentityView].Id = [MaritimeMobileServiceIdentity].Id)

go 

CREATE OR ALTER VIEW NameView
AS
 SELECT
  IdentityView.*,
  [Name].[Text]
 FROM [Name]
 JOIN IdentityView ON ([IdentityView].Id = [Name].Id)

go 

CREATE OR ALTER VIEW Int16TimeseriesValueView
AS
 SELECT
  [Int16TimeseriesValue].[Id],
  [Int16TimeseriesValue].[RowVersion],
  [Int16TimeseriesValue].[Timeseries],
  [Int16TimeseriesValue].[Timestamp],
  [Int16TimeseriesValue].[Value]
 FROM [Int16TimeseriesValue]

go 

CREATE OR ALTER VIEW Int32TimeseriesValueView
AS
 SELECT
  [Int32TimeseriesValue].[Id],
  [Int32TimeseriesValue].[RowVersion],
  [Int32TimeseriesValue].[Timeseries],
  [Int32TimeseriesValue].[Timestamp],
  [Int32TimeseriesValue].[Value]
 FROM [Int32TimeseriesValue]

go 

CREATE OR ALTER VIEW Int64TimeseriesValueView
AS
 SELECT
  [Int64TimeseriesValue].[Id],
  [Int64TimeseriesValue].[RowVersion],
  [Int64TimeseriesValue].[Timeseries],
  [Int64TimeseriesValue].[Timestamp],
  [Int64TimeseriesValue].[Value]
 FROM [Int64TimeseriesValue]

go 

CREATE OR ALTER VIEW ItemView
AS
 SELECT
  [Item].[Id],
  [Item].[EntityType],
  [Item].[RowVersion]
 FROM [Item]

go 

CREATE OR ALTER VIEW BaseStationView
AS
 SELECT
  ItemView.*,
  [BaseStation].[Name],
  [BaseStation].[Type]
 FROM [BaseStation]
 JOIN ItemView ON ([ItemView].Id = [BaseStation].Id)

go 

CREATE OR ALTER VIEW DeviceView
AS
 SELECT
  ItemView.*,
  [Device].[Host],
  [Device].[Name],
  [Device].[Description],
  [Device].[EnabledTimeseries]
 FROM [Device]
 JOIN ItemView ON ([ItemView].Id = [Device].Id)

go 

CREATE OR ALTER VIEW CameraView
AS
 SELECT
  DeviceView.*,
  [Camera].[Type]
 FROM [Camera]
 JOIN DeviceView ON ([DeviceView].Id = [Camera].Id)

go 

CREATE OR ALTER VIEW GNSSDeviceView
AS
 SELECT
  DeviceView.*,
  [GNSSDevice].[Type],
  [GNSSDevice].[LatitudeTimeseries],
  [GNSSDevice].[LongitudeTimeseries],
  [GNSSDevice].[AltitudeTimeseries]
 FROM [GNSSDevice]
 JOIN DeviceView ON ([DeviceView].Id = [GNSSDevice].Id)

go 

CREATE OR ALTER VIEW GyroDeviceView
AS
 SELECT
  DeviceView.*,
  [GyroDevice].[Type],
  [GyroDevice].[HeadingTrueNorthTimeseries],
  [GyroDevice].[HeadingMagneticNorthTimeseries],
  [GyroDevice].[PitchTimeseries],
  [GyroDevice].[RateOfTurnTimeseries],
  [GyroDevice].[RollTimeseries],
  [GyroDevice].[CourseTimeseries],
  [GyroDevice].[SpeedTimeseries],
  [GyroDevice].[GNSSDevice]
 FROM [GyroDevice]
 JOIN DeviceView ON ([DeviceView].Id = [GyroDevice].Id)

go 

CREATE OR ALTER VIEW LineInputDeviceView
AS
 SELECT
  DeviceView.*,
  [LineInputDevice].[Type]
 FROM [LineInputDevice]
 JOIN DeviceView ON ([DeviceView].Id = [LineInputDevice].Id)

go 

CREATE OR ALTER VIEW OilspillDetectorView
AS
 SELECT
  DeviceView.*,
  [OilspillDetector].[Type]
 FROM [OilspillDetector]
 JOIN DeviceView ON ([DeviceView].Id = [OilspillDetector].Id)

go 

CREATE OR ALTER VIEW RadioView
AS
 SELECT
  DeviceView.*,
  [Radio].[Type]
 FROM [Radio]
 JOIN DeviceView ON ([DeviceView].Id = [Radio].Id)

go 

CREATE OR ALTER VIEW RadomeView
AS
 SELECT
  DeviceView.*,
  [Radome].[Type],
  [Radome].[Radar],
  [Radome].[PressureTimeseries],
  [Radome].[TemperatureTimeseries],
  [Radome].[DewPointTimeseries],
  [Radome].[StatusTimeseries]
 FROM [Radome]
 JOIN DeviceView ON ([DeviceView].Id = [Radome].Id)

go 

CREATE OR ALTER VIEW TrackerView
AS
 SELECT
  DeviceView.*
 FROM [Tracker]
 JOIN DeviceView ON ([DeviceView].Id = [Tracker].Id)

go 

CREATE OR ALTER VIEW AisTransceiverView
AS
 SELECT
  TrackerView.*,
  [AisTransceiver].[Type]
 FROM [AisTransceiver]
 JOIN TrackerView ON ([TrackerView].Id = [AisTransceiver].Id)

go 

CREATE OR ALTER VIEW RadarView
AS
 SELECT
  TrackerView.*,
  [Radar].[Type],
  [Radar].[SaveSettingsTimeseries],
  [Radar].[PowerOnTimeseries],
  [Radar].[TrackingOnTimeseries],
  [Radar].[RadarPulseTimeseries],
  [Radar].[TuningTimeseries],
  [Radar].[BlankSector1Timeseries],
  [Radar].[Sector1StartTimeseries],
  [Radar].[Sector1EndTimeseries],
  [Radar].[BlankSector2Timeseries],
  [Radar].[Sector2StartTimeseries],
  [Radar].[Sector2EndTimeseries],
  [Radar].[EnableAutomaticFrequencyControlTimeseries],
  [Radar].[AzimuthOffsetTimeseries],
  [Radar].[EnableSensitivityTimeControlTimeseries],
  [Radar].[AutomaticSensitivityTimeControlTimeseries],
  [Radar].[SensitivityTimeControlLevelTimeseries],
  [Radar].[EnableFastTimeConstantTimeseries],
  [Radar].[FastTimeConstantLevelTimeseries],
  [Radar].[FastTimeConstantModeTimeseries],
  [Radar].[LatitudeTimeseries],
  [Radar].[LongitudeTimeseries],
  [Radar].[Radome],
  [Radar].[GNSSDevice]
 FROM [Radar]
 JOIN TrackerView ON ([TrackerView].Id = [Radar].Id)

go 

CREATE OR ALTER VIEW WeatherStationView
AS
 SELECT
  DeviceView.*,
  [WeatherStation].[Type],
  [WeatherStation].[BarometricPressureTimeseries],
  [WeatherStation].[AirTemperatureTimeseries],
  [WeatherStation].[WaterTemperatureTimeseries],
  [WeatherStation].[RelativeHumidityTimeseries],
  [WeatherStation].[AbsoluteHumidityTimeseries],
  [WeatherStation].[DewPointTimeseries],
  [WeatherStation].[WindDirectionTimeseries],
  [WeatherStation].[WindSpeedTimeseries],
  [WeatherStation].[Gyro]
 FROM [WeatherStation]
 JOIN DeviceView ON ([DeviceView].Id = [WeatherStation].Id)

go 

CREATE OR ALTER VIEW FacilityView
AS
 SELECT
  ItemView.*,
  [Facility].[Name],
  [Facility].[Type],
  [Facility].[Longitude],
  [Facility].[Latitude],
  [Facility].[Altitude]
 FROM [Facility]
 JOIN ItemView ON ([ItemView].Id = [Facility].Id)

go 

CREATE OR ALTER VIEW TrackableItemView
AS
 SELECT
  ItemView.*
 FROM [TrackableItem]
 JOIN ItemView ON ([ItemView].Id = [TrackableItem].Id)

go 

CREATE OR ALTER VIEW AircraftView
AS
 SELECT
  TrackableItemView.*,
  [Aircraft].[Name],
  [Aircraft].[Type]
 FROM [Aircraft]
 JOIN TrackableItemView ON ([TrackableItemView].Id = [Aircraft].Id)

go 

CREATE OR ALTER VIEW AisAidToNavigationView
AS
 SELECT
  TrackableItemView.*,
  [AisAidToNavigation].[Name],
  [AisAidToNavigation].[MMSI],
  [AisAidToNavigation].[NavigationalAidType],
  [AisAidToNavigation].[Position],
  [AisAidToNavigation].[IsVirtual],
  [AisAidToNavigation].[ToBow],
  [AisAidToNavigation].[ToStern],
  [AisAidToNavigation].[ToPort],
  [AisAidToNavigation].[ToStarboard],
  [AisAidToNavigation].[OffPositionTimeseries]
 FROM [AisAidToNavigation]
 JOIN TrackableItemView ON ([TrackableItemView].Id = [AisAidToNavigation].Id)

go 

CREATE OR ALTER VIEW VehicleView
AS
 SELECT
  TrackableItemView.*,
  [Vehicle].[Name],
  [Vehicle].[Type]
 FROM [Vehicle]
 JOIN TrackableItemView ON ([TrackableItemView].Id = [Vehicle].Id)

go 

CREATE OR ALTER VIEW VesselView
AS
 SELECT
  TrackableItemView.*,
  [Vessel].[Name],
  [Vessel].[Type],
  [Vessel].[ToBow],
  [Vessel].[ToStern],
  [Vessel].[ToPort],
  [Vessel].[ToStarboard],
  [Vessel].[DraughtTimeseries],
  [Vessel].[PersonsOnBoardTimeseries]
 FROM [Vessel]
 JOIN TrackableItemView ON ([TrackableItemView].Id = [Vessel].Id)

go 

CREATE OR ALTER VIEW ItemIdentityLinkView
AS
 SELECT
  [ItemIdentityLink].[Id],
  [ItemIdentityLink].[RowVersion],
  [ItemIdentityLink].[Item],
  [ItemIdentityLink].[Identity],
  [ItemIdentityLink].[Start],
  [ItemIdentityLink].[End]
 FROM [ItemIdentityLink]

go 

CREATE OR ALTER VIEW ItemParentChildLinkView
AS
 SELECT
  [ItemParentChildLink].[Id],
  [ItemParentChildLink].[RowVersion],
  [ItemParentChildLink].[Parent],
  [ItemParentChildLink].[Child],
  [ItemParentChildLink].[Timestamp]
 FROM [ItemParentChildLink]

go 

CREATE OR ALTER VIEW LineInputDeviceCommandView
AS
 SELECT
  [LineInputDeviceCommand].[Id],
  [LineInputDeviceCommand].[RowVersion],
  [LineInputDeviceCommand].[LineInputDevice],
  [LineInputDeviceCommand].[Timestamp],
  [LineInputDeviceCommand].[DeviceCommandSourceType],
  [LineInputDeviceCommand].[DeviceCommandSourceId],
  [LineInputDeviceCommand].[Reply]
 FROM [LineInputDeviceCommand]

go 

CREATE OR ALTER VIEW LineInputDeviceCommandReplyView
AS
 SELECT
  [LineInputDeviceCommandReply].[Id],
  [LineInputDeviceCommandReply].[RowVersion],
  [LineInputDeviceCommandReply].[LineInputDevice],
  [LineInputDeviceCommandReply].[Timestamp],
  [LineInputDeviceCommandReply].[Command],
  [LineInputDeviceCommandReply].[Status],
  [LineInputDeviceCommandReply].[Message]
 FROM [LineInputDeviceCommandReply]

go 

CREATE OR ALTER VIEW LineInputDeviceConfigurationView
AS
 SELECT
  [LineInputDeviceConfiguration].[Id],
  [LineInputDeviceConfiguration].[RowVersion],
  [LineInputDeviceConfiguration].[LineInputDevice],
  [LineInputDeviceConfiguration].[Timestamp],
  [LineInputDeviceConfiguration].[StoreReceivedSentences],
  [LineInputDeviceConfiguration].[StoreSentMessages],
  [LineInputDeviceConfiguration].[StoreUnsentMessages],
  [LineInputDeviceConfiguration].[NMEA],
  [LineInputDeviceConfiguration].[StrictNMEA],
  [LineInputDeviceConfiguration].[ConnectionType],
  [LineInputDeviceConfiguration].[UdpReceivePort],
  [LineInputDeviceConfiguration].[UdpSendHostname],
  [LineInputDeviceConfiguration].[UdpSendPort],
  [LineInputDeviceConfiguration].[TcpHostname],
  [LineInputDeviceConfiguration].[TcpPort],
  [LineInputDeviceConfiguration].[UseHttpLogin],
  [LineInputDeviceConfiguration].[LoginHostname],
  [LineInputDeviceConfiguration].[LoginPort],
  [LineInputDeviceConfiguration].[UserName],
  [LineInputDeviceConfiguration].[Password],
  [LineInputDeviceConfiguration].[ComPort],
  [LineInputDeviceConfiguration].[BaudRate],
  [LineInputDeviceConfiguration].[DataBits],
  [LineInputDeviceConfiguration].[DiscardNull],
  [LineInputDeviceConfiguration].[DtrEnable],
  [LineInputDeviceConfiguration].[Handshake],
  [LineInputDeviceConfiguration].[NewLine],
  [LineInputDeviceConfiguration].[Parity],
  [LineInputDeviceConfiguration].[ParityReplace],
  [LineInputDeviceConfiguration].[ReadBufferSize],
  [LineInputDeviceConfiguration].[ReadTimeout],
  [LineInputDeviceConfiguration].[ReceivedBytesThreshold],
  [LineInputDeviceConfiguration].[RtsEnable],
  [LineInputDeviceConfiguration].[StopBits],
  [LineInputDeviceConfiguration].[WriteBufferSize],
  [LineInputDeviceConfiguration].[WriteTimeout],
  [LineInputDeviceConfiguration].[PairedComPort]
 FROM [LineInputDeviceConfiguration]

go 

CREATE OR ALTER VIEW LineInputMessageRoutingView
AS
 SELECT
  [LineInputMessageRouting].[Id],
  [LineInputMessageRouting].[RowVersion],
  [LineInputMessageRouting].[LineInputDevice],
  [LineInputMessageRouting].[Type]
 FROM [LineInputMessageRouting]

go 

CREATE OR ALTER VIEW LineInputMessageRoutingDestinationView
AS
 SELECT
  [LineInputMessageRoutingDestination].[Id],
  [LineInputMessageRoutingDestination].[RowVersion],
  [LineInputMessageRoutingDestination].[Routing],
  [LineInputMessageRoutingDestination].[Listener]
 FROM [LineInputMessageRoutingDestination]

go 

CREATE OR ALTER VIEW LineInputWhiteListEntryView
AS
 SELECT
  [LineInputWhiteListEntry].[Id],
  [LineInputWhiteListEntry].[RowVersion],
  [LineInputWhiteListEntry].[LineInputDevice],
  [LineInputWhiteListEntry].[HostName],
  [LineInputWhiteListEntry].[Port]
 FROM [LineInputWhiteListEntry]

go 

CREATE OR ALTER VIEW LogApplicationView
AS
 SELECT
  [LogApplication].[Id],
  [LogApplication].[RowVersion],
  [LogApplication].[Name],
  [LogApplication].[Description]
 FROM [LogApplication]

go 

CREATE OR ALTER VIEW LogApplicationConfigurationView
AS
 SELECT
  [LogApplicationConfiguration].[Id],
  [LogApplicationConfiguration].[RowVersion],
  [LogApplicationConfiguration].[Application],
  [LogApplicationConfiguration].[Timestamp],
  [LogApplicationConfiguration].[Finest],
  [LogApplicationConfiguration].[Finer],
  [LogApplicationConfiguration].[Fine],
  [LogApplicationConfiguration].[Info],
  [LogApplicationConfiguration].[Notice],
  [LogApplicationConfiguration].[Warn],
  [LogApplicationConfiguration].[Error],
  [LogApplicationConfiguration].[Severe],
  [LogApplicationConfiguration].[Critical],
  [LogApplicationConfiguration].[Alert],
  [LogApplicationConfiguration].[Fatal],
  [LogApplicationConfiguration].[Emergency]
 FROM [LogApplicationConfiguration]

go 

CREATE OR ALTER VIEW LogHostView
AS
 SELECT
  [LogHost].[Id],
  [LogHost].[RowVersion],
  [LogHost].[ComputerName],
  [LogHost].[Description]
 FROM [LogHost]

go 

CREATE OR ALTER VIEW LogHostConfigurationView
AS
 SELECT
  [LogHostConfiguration].[Id],
  [LogHostConfiguration].[RowVersion],
  [LogHostConfiguration].[Host],
  [LogHostConfiguration].[Timestamp],
  [LogHostConfiguration].[Finest],
  [LogHostConfiguration].[Finer],
  [LogHostConfiguration].[Fine],
  [LogHostConfiguration].[Info],
  [LogHostConfiguration].[Notice],
  [LogHostConfiguration].[Warn],
  [LogHostConfiguration].[Error],
  [LogHostConfiguration].[Severe],
  [LogHostConfiguration].[Critical],
  [LogHostConfiguration].[Alert],
  [LogHostConfiguration].[Fatal],
  [LogHostConfiguration].[Emergency]
 FROM [LogHostConfiguration]

go 

CREATE OR ALTER VIEW LogLocationView
AS
 SELECT
  [LogLocation].[Id],
  [LogLocation].[RowVersion],
  [LogLocation].[FileName],
  [LogLocation].[LineNumber],
  [LogLocation].[Namespace],
  [LogLocation].[ClassName],
  [LogLocation].[MethodName]
 FROM [LogLocation]

go 

CREATE OR ALTER VIEW LogProcessView
AS
 SELECT
  [LogProcess].[Id],
  [LogProcess].[RowVersion],
  [LogProcess].[Application],
  [LogProcess].[Host],
  [LogProcess].[Started],
  [LogProcess].[Stopped],
  [LogProcess].[ProcessId],
  [LogProcess].[Path],
  [LogProcess].[Identity]
 FROM [LogProcess]

go 

CREATE OR ALTER VIEW LogRecordView
AS
 SELECT
  [LogRecord].[Id],
  [LogRecord].[RowVersion],
  [LogRecord].[Thread],
  [LogRecord].[SequenceNumber],
  [LogRecord].[Level],
  [LogRecord].[Timestamp],
  [LogRecord].[Depth],
  [LogRecord].[Location],
  [LogRecord].[Message],
  [LogRecord].[ExceptionString],
  [LogRecord].[PropertiesData]
 FROM [LogRecord]

go 

CREATE OR ALTER VIEW LogThreadView
AS
 SELECT
  [LogThread].[Id],
  [LogThread].[RowVersion],
  [LogThread].[Process],
  [LogThread].[Started],
  [LogThread].[Stopped],
  [LogThread].[ThreadId],
  [LogThread].[Name]
 FROM [LogThread]

go 

CREATE OR ALTER VIEW LogTraceEntryView
AS
 SELECT
  [LogTraceEntry].[Id],
  [LogTraceEntry].[RowVersion],
  [LogTraceEntry].[Thread],
  [LogTraceEntry].[SequenceNumber],
  [LogTraceEntry].[Location],
  [LogTraceEntry].[Depth],
  [LogTraceEntry].[Entered],
  [LogTraceEntry].[Ended]
 FROM [LogTraceEntry]

go 

CREATE OR ALTER VIEW MapElementView
AS
 SELECT
  [MapElement].[Id],
  [MapElement].[RowVersion],
  [MapElement].[Item],
  [MapElement].[ElementType],
  [MapElement].[Latitude],
  [MapElement].[Longitude],
  [MapElement].[Angle],
  [MapElement].[Left],
  [MapElement].[Top],
  [MapElement].[Width],
  [MapElement].[Height],
  [MapElement].[Label],
  [MapElement].[Data]
 FROM [MapElement]

go 

CREATE OR ALTER VIEW MapInfoView
AS
 SELECT
  [MapInfo].[Id],
  [MapInfo].[RowVersion],
  [MapInfo].[Scale],
  [MapInfo].[Latitude],
  [MapInfo].[Longitude],
  [MapInfo].[NorthWestLatitude],
  [MapInfo].[NorthWestLongitude],
  [MapInfo].[SouthEastLatitude],
  [MapInfo].[SouthEastLongitude],
  [MapInfo].[Image]
 FROM [MapInfo]

go 

CREATE OR ALTER VIEW MapServiceOptionsView
AS
 SELECT
  [MapServiceOptions].[Id],
  [MapServiceOptions].[RowVersion],
  [MapServiceOptions].[Timestamp],
  [MapServiceOptions].[IpAddress],
  [MapServiceOptions].[Port],
  [MapServiceOptions].[ImageScaleFactorX],
  [MapServiceOptions].[ImageOffsetX],
  [MapServiceOptions].[ImageScaleFactorY],
  [MapServiceOptions].[ImageOffsetY]
 FROM [MapServiceOptions]

go 

CREATE OR ALTER VIEW MaritimeIdentificationDigitsView
AS
 SELECT
  [MaritimeIdentificationDigits].[Id],
  [MaritimeIdentificationDigits].[RowVersion],
  [MaritimeIdentificationDigits].[Code],
  [MaritimeIdentificationDigits].[Country]
 FROM [MaritimeIdentificationDigits]

go 

CREATE OR ALTER VIEW MediaProxySessionView
AS
 SELECT
  [MediaProxySession].[Id],
  [MediaProxySession].[RowVersion],
  [MediaProxySession].[Service],
  [MediaProxySession].[Name],
  [MediaProxySession].[EnabledTimeseries]
 FROM [MediaProxySession]

go 

CREATE OR ALTER VIEW MediaProxySessionFileView
AS
 SELECT
  [MediaProxySessionFile].[Id],
  [MediaProxySessionFile].[RowVersion],
  [MediaProxySessionFile].[ProxySession],
  [MediaProxySessionFile].[Timestamp],
  [MediaProxySessionFile].[StreamName]
 FROM [MediaProxySessionFile]

go 

CREATE OR ALTER VIEW MediaProxySessionOptionsView
AS
 SELECT
  [MediaProxySessionOptions].[Id],
  [MediaProxySessionOptions].[RowVersion],
  [MediaProxySessionOptions].[ProxySession],
  [MediaProxySessionOptions].[Timestamp],
  [MediaProxySessionOptions].[SourceStreamUrl],
  [MediaProxySessionOptions].[StreamName],
  [MediaProxySessionOptions].[Mode],
  [MediaProxySessionOptions].[TunnelOverHTTPPortNumber],
  [MediaProxySessionOptions].[Username],
  [MediaProxySessionOptions].[Password],
  [MediaProxySessionOptions].[RecorderPortNumber],
  [MediaProxySessionOptions].[SessionType],
  [MediaProxySessionOptions].[MaxFileTime],
  [MediaProxySessionOptions].[MaxFileRetention],
  [MediaProxySessionOptions].[VideoDirectory]
 FROM [MediaProxySessionOptions]

go 

CREATE OR ALTER VIEW MediaServiceView
AS
 SELECT
  [MediaService].[Id],
  [MediaService].[RowVersion],
  [MediaService].[EnabledTimeseries]
 FROM [MediaService]

go 

CREATE OR ALTER VIEW MediaServiceOptionsView
AS
 SELECT
  [MediaServiceOptions].[Id],
  [MediaServiceOptions].[RowVersion],
  [MediaServiceOptions].[MediaService],
  [MediaServiceOptions].[Timestamp],
  [MediaServiceOptions].[RtspPortNumber],
  [MediaServiceOptions].[HttpPortNumber]
 FROM [MediaServiceOptions]

go 

CREATE OR ALTER VIEW NamespaceElementView
AS
 SELECT
  [NamespaceElement].[Id],
  [NamespaceElement].[EntityType],
  [NamespaceElement].[RowVersion],
  [NamespaceElement].[Namespace],
  [NamespaceElement].[Name],
  [NamespaceElement].[Description]
 FROM [NamespaceElement]

go 

CREATE OR ALTER VIEW ElementTypeView
AS
 SELECT
  NamespaceElementView.*
 FROM [ElementType]
 JOIN NamespaceElementView ON ([NamespaceElementView].Id = [ElementType].Id)

go 

CREATE OR ALTER VIEW NamespaceView
AS
 SELECT
  NamespaceElementView.*
 FROM [Namespace]
 JOIN NamespaceElementView ON ([NamespaceElementView].Id = [Namespace].Id)

go 

CREATE OR ALTER VIEW OilspillView
AS
 SELECT
  [Oilspill].[Id],
  [Oilspill].[RowVersion],
  [Oilspill].[OilSpillDetector],
  [Oilspill].[Timestamp],
  [Oilspill].[OilArea],
  [Oilspill].[Shape],
  [Oilspill].[BSI],
  [Oilspill].[Oil],
  [Oilspill].[Trace]
 FROM [Oilspill]

go 

CREATE OR ALTER VIEW OilspillDetectorCommandView
AS
 SELECT
  [OilspillDetectorCommand].[Id],
  [OilspillDetectorCommand].[RowVersion],
  [OilspillDetectorCommand].[OilSpillDetector],
  [OilspillDetectorCommand].[Timestamp],
  [OilspillDetectorCommand].[DeviceCommandSourceType],
  [OilspillDetectorCommand].[DeviceCommandSourceId],
  [OilspillDetectorCommand].[Reply]
 FROM [OilspillDetectorCommand]

go 

CREATE OR ALTER VIEW OilspillDetectorCommandReplyView
AS
 SELECT
  [OilspillDetectorCommandReply].[Id],
  [OilspillDetectorCommandReply].[RowVersion],
  [OilspillDetectorCommandReply].[OilSpillDetector],
  [OilspillDetectorCommandReply].[Timestamp],
  [OilspillDetectorCommandReply].[Command],
  [OilspillDetectorCommandReply].[Status],
  [OilspillDetectorCommandReply].[Message]
 FROM [OilspillDetectorCommandReply]

go 

CREATE OR ALTER VIEW OilspillDetectorConfigurationView
AS
 SELECT
  [OilspillDetectorConfiguration].[Id],
  [OilspillDetectorConfiguration].[RowVersion],
  [OilspillDetectorConfiguration].[OilSpillDetector],
  [OilspillDetectorConfiguration].[Timestamp],
  [OilspillDetectorConfiguration].[Range],
  [OilspillDetectorConfiguration].[StartAngle],
  [OilspillDetectorConfiguration].[EndAngle],
  [OilspillDetectorConfiguration].[StartRange],
  [OilspillDetectorConfiguration].[EndRange],
  [OilspillDetectorConfiguration].[UpdateRate],
  [OilspillDetectorConfiguration].[StatusSendTime],
  [OilspillDetectorConfiguration].[DrawBorder],
  [OilspillDetectorConfiguration].[Colors],
  [OilspillDetectorConfiguration].[SendToServer],
  [OilspillDetectorConfiguration].[Directory],
  [OilspillDetectorConfiguration].[TransparentWater],
  [OilspillDetectorConfiguration].[SavePictures],
  [OilspillDetectorConfiguration].[SendAsTarget],
  [OilspillDetectorConfiguration].[WriteLog],
  [OilspillDetectorConfiguration].[TargetFilePrefix],
  [OilspillDetectorConfiguration].[TargetMMSI],
  [OilspillDetectorConfiguration].[Latitude],
  [OilspillDetectorConfiguration].[Longitude],
  [OilspillDetectorConfiguration].[TestSourceEnabled],
  [OilspillDetectorConfiguration].[ProxyServer],
  [OilspillDetectorConfiguration].[UseProxyServer]
 FROM [OilspillDetectorConfiguration]

go 

CREATE OR ALTER VIEW Position2DTimeseriesValueView
AS
 SELECT
  [Position2DTimeseriesValue].[Id],
  [Position2DTimeseriesValue].[RowVersion],
  [Position2DTimeseriesValue].[Timeseries],
  [Position2DTimeseriesValue].[Timestamp],
  [Position2DTimeseriesValue].[X],
  [Position2DTimeseriesValue].[Y]
 FROM [Position2DTimeseriesValue]

go 

CREATE OR ALTER VIEW Position3DTimeseriesValueView
AS
 SELECT
  [Position3DTimeseriesValue].[Id],
  [Position3DTimeseriesValue].[RowVersion],
  [Position3DTimeseriesValue].[Timeseries],
  [Position3DTimeseriesValue].[Timestamp],
  [Position3DTimeseriesValue].[X],
  [Position3DTimeseriesValue].[Y],
  [Position3DTimeseriesValue].[Z]
 FROM [Position3DTimeseriesValue]

go 

CREATE OR ALTER VIEW ProcessTrackValueResultView
AS
 SELECT
  [ProcessTrackValueResult].[Id],
  [ProcessTrackValueResult].[RowVersion],
  [ProcessTrackValueResult].[CreatedNewTrack],
  [ProcessTrackValueResult].[TrackId]
 FROM [ProcessTrackValueResult]

go 

CREATE OR ALTER VIEW PropertyView
AS
 SELECT
  [Property].[Id],
  [Property].[EntityType],
  [Property].[RowVersion],
  [Property].[Element],
  [Property].[Definition]
 FROM [Property]

go 

CREATE OR ALTER VIEW BinaryPropertyView
AS
 SELECT
  PropertyView.*,
  [BinaryProperty].[Value]
 FROM [BinaryProperty]
 JOIN PropertyView ON ([PropertyView].Id = [BinaryProperty].Id)

go 

CREATE OR ALTER VIEW BooleanPropertyView
AS
 SELECT
  PropertyView.*,
  [BooleanProperty].[Value]
 FROM [BooleanProperty]
 JOIN PropertyView ON ([PropertyView].Id = [BooleanProperty].Id)

go 

CREATE OR ALTER VIEW BytePropertyView
AS
 SELECT
  PropertyView.*,
  [ByteProperty].[Value]
 FROM [ByteProperty]
 JOIN PropertyView ON ([PropertyView].Id = [ByteProperty].Id)

go 

CREATE OR ALTER VIEW DateTimePropertyView
AS
 SELECT
  PropertyView.*,
  [DateTimeProperty].[Value]
 FROM [DateTimeProperty]
 JOIN PropertyView ON ([PropertyView].Id = [DateTimeProperty].Id)

go 

CREATE OR ALTER VIEW DoublePropertyView
AS
 SELECT
  PropertyView.*,
  [DoubleProperty].[Value]
 FROM [DoubleProperty]
 JOIN PropertyView ON ([PropertyView].Id = [DoubleProperty].Id)

go 

CREATE OR ALTER VIEW GuidPropertyView
AS
 SELECT
  PropertyView.*,
  [GuidProperty].[Value]
 FROM [GuidProperty]
 JOIN PropertyView ON ([PropertyView].Id = [GuidProperty].Id)

go 

CREATE OR ALTER VIEW Int16PropertyView
AS
 SELECT
  PropertyView.*,
  [Int16Property].[Value]
 FROM [Int16Property]
 JOIN PropertyView ON ([PropertyView].Id = [Int16Property].Id)

go 

CREATE OR ALTER VIEW Int32PropertyView
AS
 SELECT
  PropertyView.*,
  [Int32Property].[Value]
 FROM [Int32Property]
 JOIN PropertyView ON ([PropertyView].Id = [Int32Property].Id)

go 

CREATE OR ALTER VIEW Int64PropertyView
AS
 SELECT
  PropertyView.*,
  [Int64Property].[Value]
 FROM [Int64Property]
 JOIN PropertyView ON ([PropertyView].Id = [Int64Property].Id)

go 

CREATE OR ALTER VIEW ReferencePropertyView
AS
 SELECT
  PropertyView.*,
  [ReferenceProperty].[Value]
 FROM [ReferenceProperty]
 JOIN PropertyView ON ([PropertyView].Id = [ReferenceProperty].Id)

go 

CREATE OR ALTER VIEW SBytePropertyView
AS
 SELECT
  PropertyView.*,
  [SByteProperty].[Value]
 FROM [SByteProperty]
 JOIN PropertyView ON ([PropertyView].Id = [SByteProperty].Id)

go 

CREATE OR ALTER VIEW SinglePropertyView
AS
 SELECT
  PropertyView.*,
  [SingleProperty].[Value]
 FROM [SingleProperty]
 JOIN PropertyView ON ([PropertyView].Id = [SingleProperty].Id)

go 

CREATE OR ALTER VIEW StringPropertyView
AS
 SELECT
  PropertyView.*,
  [StringProperty].[Value]
 FROM [StringProperty]
 JOIN PropertyView ON ([PropertyView].Id = [StringProperty].Id)

go 

CREATE OR ALTER VIEW TimeseriesPropertyView
AS
 SELECT
  PropertyView.*
 FROM [TimeseriesProperty]
 JOIN PropertyView ON ([PropertyView].Id = [TimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW BinaryTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [BinaryTimeseriesProperty].[Timeseries]
 FROM [BinaryTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [BinaryTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW BooleanTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [BooleanTimeseriesProperty].[Timeseries]
 FROM [BooleanTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [BooleanTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW ByteTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [ByteTimeseriesProperty].[Timeseries]
 FROM [ByteTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [ByteTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW DateTimeTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [DateTimeTimeseriesProperty].[Timeseries]
 FROM [DateTimeTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [DateTimeTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW DoubleTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [DoubleTimeseriesProperty].[Timeseries]
 FROM [DoubleTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [DoubleTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW GuidTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [GuidTimeseriesProperty].[Timeseries]
 FROM [GuidTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [GuidTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW Int16TimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [Int16TimeseriesProperty].[Timeseries]
 FROM [Int16TimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [Int16TimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW Int32TimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [Int32TimeseriesProperty].[Timeseries]
 FROM [Int32TimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [Int32TimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW Int64TimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [Int64TimeseriesProperty].[Timeseries]
 FROM [Int64TimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [Int64TimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW ReferenceTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [ReferenceTimeseriesProperty].[Timeseries]
 FROM [ReferenceTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [ReferenceTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW SByteTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [SByteTimeseriesProperty].[Timeseries]
 FROM [SByteTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [SByteTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW SingleTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [SingleTimeseriesProperty].[Timeseries]
 FROM [SingleTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [SingleTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW StringTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [StringTimeseriesProperty].[Timeseries]
 FROM [StringTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [StringTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW TimeSpanTimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [TimeSpanTimeseriesProperty].[Timeseries]
 FROM [TimeSpanTimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [TimeSpanTimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW UInt16TimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [UInt16TimeseriesProperty].[Timeseries]
 FROM [UInt16TimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [UInt16TimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW UInt32TimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [UInt32TimeseriesProperty].[Timeseries]
 FROM [UInt32TimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [UInt32TimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW UInt64TimeseriesPropertyView
AS
 SELECT
  TimeseriesPropertyView.*,
  [UInt64TimeseriesProperty].[Timeseries]
 FROM [UInt64TimeseriesProperty]
 JOIN TimeseriesPropertyView ON ([TimeseriesPropertyView].Id = [UInt64TimeseriesProperty].Id)

go 

CREATE OR ALTER VIEW TimeSpanPropertyView
AS
 SELECT
  PropertyView.*,
  [TimeSpanProperty].[Value]
 FROM [TimeSpanProperty]
 JOIN PropertyView ON ([PropertyView].Id = [TimeSpanProperty].Id)

go 

CREATE OR ALTER VIEW UInt16PropertyView
AS
 SELECT
  PropertyView.*,
  [UInt16Property].[Value]
 FROM [UInt16Property]
 JOIN PropertyView ON ([PropertyView].Id = [UInt16Property].Id)

go 

CREATE OR ALTER VIEW UInt32PropertyView
AS
 SELECT
  PropertyView.*,
  [UInt32Property].[Value]
 FROM [UInt32Property]
 JOIN PropertyView ON ([PropertyView].Id = [UInt32Property].Id)

go 

CREATE OR ALTER VIEW UInt64PropertyView
AS
 SELECT
  PropertyView.*,
  [UInt64Property].[Value]
 FROM [UInt64Property]
 JOIN PropertyView ON ([PropertyView].Id = [UInt64Property].Id)

go 

CREATE OR ALTER VIEW PropertyDefinitionView
AS
 SELECT
  [PropertyDefinition].[Id],
  [PropertyDefinition].[EntityType],
  [PropertyDefinition].[RowVersion],
  [PropertyDefinition].[ElementType],
  [PropertyDefinition].[Name],
  [PropertyDefinition].[Description]
 FROM [PropertyDefinition]

go 

CREATE OR ALTER VIEW BinaryPropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [BinaryPropertyDefinition].[DefaultValue]
 FROM [BinaryPropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [BinaryPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW BooleanPropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [BooleanPropertyDefinition].[DefaultValue]
 FROM [BooleanPropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [BooleanPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW BytePropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [BytePropertyDefinition].[DefaultValue],
  [BytePropertyDefinition].[MinValue],
  [BytePropertyDefinition].[MaxValue]
 FROM [BytePropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [BytePropertyDefinition].Id)

go 

CREATE OR ALTER VIEW DateTimePropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [DateTimePropertyDefinition].[DefaultValue],
  [DateTimePropertyDefinition].[MinValue],
  [DateTimePropertyDefinition].[MaxValue]
 FROM [DateTimePropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [DateTimePropertyDefinition].Id)

go 

CREATE OR ALTER VIEW DoublePropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [DoublePropertyDefinition].[DefaultValue],
  [DoublePropertyDefinition].[MinValue],
  [DoublePropertyDefinition].[MaxValue]
 FROM [DoublePropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [DoublePropertyDefinition].Id)

go 

CREATE OR ALTER VIEW GuidPropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [GuidPropertyDefinition].[DefaultValue]
 FROM [GuidPropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [GuidPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW Int16PropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [Int16PropertyDefinition].[DefaultValue],
  [Int16PropertyDefinition].[MinValue],
  [Int16PropertyDefinition].[MaxValue]
 FROM [Int16PropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [Int16PropertyDefinition].Id)

go 

CREATE OR ALTER VIEW Int32PropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [Int32PropertyDefinition].[DefaultValue],
  [Int32PropertyDefinition].[MinValue],
  [Int32PropertyDefinition].[MaxValue]
 FROM [Int32PropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [Int32PropertyDefinition].Id)

go 

CREATE OR ALTER VIEW Int64PropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [Int64PropertyDefinition].[DefaultValue],
  [Int64PropertyDefinition].[MinValue],
  [Int64PropertyDefinition].[MaxValue]
 FROM [Int64PropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [Int64PropertyDefinition].Id)

go 

CREATE OR ALTER VIEW ReferencePropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [ReferencePropertyDefinition].[DefaultValue],
  [ReferencePropertyDefinition].[ReferencedElementType]
 FROM [ReferencePropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [ReferencePropertyDefinition].Id)

go 

CREATE OR ALTER VIEW SBytePropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [SBytePropertyDefinition].[DefaultValue],
  [SBytePropertyDefinition].[MinValue],
  [SBytePropertyDefinition].[MaxValue]
 FROM [SBytePropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [SBytePropertyDefinition].Id)

go 

CREATE OR ALTER VIEW SinglePropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [SinglePropertyDefinition].[DefaultValue],
  [SinglePropertyDefinition].[MinValue],
  [SinglePropertyDefinition].[MaxValue]
 FROM [SinglePropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [SinglePropertyDefinition].Id)

go 

CREATE OR ALTER VIEW StringPropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [StringPropertyDefinition].[DefaultValue],
  [StringPropertyDefinition].[Pattern]
 FROM [StringPropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [StringPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW TimeseriesPropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*
 FROM [TimeseriesPropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [TimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW BinaryTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*
 FROM [BinaryTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [BinaryTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW BooleanTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*
 FROM [BooleanTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [BooleanTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW ByteTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [ByteTimeseriesPropertyDefinition].[MinValue],
  [ByteTimeseriesPropertyDefinition].[MaxValue]
 FROM [ByteTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [ByteTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW DateTimeTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [DateTimeTimeseriesPropertyDefinition].[MinValue],
  [DateTimeTimeseriesPropertyDefinition].[MaxValue]
 FROM [DateTimeTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [DateTimeTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW DoubleTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [DoubleTimeseriesPropertyDefinition].[MinValue],
  [DoubleTimeseriesPropertyDefinition].[MaxValue]
 FROM [DoubleTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [DoubleTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW GuidTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*
 FROM [GuidTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [GuidTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW Int16TimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [Int16TimeseriesPropertyDefinition].[MinValue],
  [Int16TimeseriesPropertyDefinition].[MaxValue]
 FROM [Int16TimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [Int16TimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW Int32TimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [Int32TimeseriesPropertyDefinition].[MinValue],
  [Int32TimeseriesPropertyDefinition].[MaxValue]
 FROM [Int32TimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [Int32TimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW Int64TimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [Int64TimeseriesPropertyDefinition].[MinValue],
  [Int64TimeseriesPropertyDefinition].[MaxValue]
 FROM [Int64TimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [Int64TimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW ReferenceTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [ReferenceTimeseriesPropertyDefinition].[ReferencedElementType]
 FROM [ReferenceTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [ReferenceTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW SByteTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [SByteTimeseriesPropertyDefinition].[MinValue],
  [SByteTimeseriesPropertyDefinition].[MaxValue]
 FROM [SByteTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [SByteTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW SingleTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [SingleTimeseriesPropertyDefinition].[MinValue],
  [SingleTimeseriesPropertyDefinition].[MaxValue]
 FROM [SingleTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [SingleTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW StringTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [StringTimeseriesPropertyDefinition].[Pattern]
 FROM [StringTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [StringTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW TimeSpanTimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [TimeSpanTimeseriesPropertyDefinition].[MinValue],
  [TimeSpanTimeseriesPropertyDefinition].[MaxValue]
 FROM [TimeSpanTimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [TimeSpanTimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW UInt16TimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [UInt16TimeseriesPropertyDefinition].[MinValue],
  [UInt16TimeseriesPropertyDefinition].[MaxValue]
 FROM [UInt16TimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [UInt16TimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW UInt32TimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [UInt32TimeseriesPropertyDefinition].[MinValue],
  [UInt32TimeseriesPropertyDefinition].[MaxValue]
 FROM [UInt32TimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [UInt32TimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW UInt64TimeseriesPropertyDefinitionView
AS
 SELECT
  TimeseriesPropertyDefinitionView.*,
  [UInt64TimeseriesPropertyDefinition].[MinValue],
  [UInt64TimeseriesPropertyDefinition].[MaxValue]
 FROM [UInt64TimeseriesPropertyDefinition]
 JOIN TimeseriesPropertyDefinitionView ON ([TimeseriesPropertyDefinitionView].Id = [UInt64TimeseriesPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW TimeSpanPropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [TimeSpanPropertyDefinition].[DefaultValue],
  [TimeSpanPropertyDefinition].[MinValue],
  [TimeSpanPropertyDefinition].[MaxValue]
 FROM [TimeSpanPropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [TimeSpanPropertyDefinition].Id)

go 

CREATE OR ALTER VIEW UInt16PropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [UInt16PropertyDefinition].[DefaultValue],
  [UInt16PropertyDefinition].[MinValue],
  [UInt16PropertyDefinition].[MaxValue]
 FROM [UInt16PropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [UInt16PropertyDefinition].Id)

go 

CREATE OR ALTER VIEW UInt32PropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [UInt32PropertyDefinition].[DefaultValue],
  [UInt32PropertyDefinition].[MinValue],
  [UInt32PropertyDefinition].[MaxValue]
 FROM [UInt32PropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [UInt32PropertyDefinition].Id)

go 

CREATE OR ALTER VIEW UInt64PropertyDefinitionView
AS
 SELECT
  PropertyDefinitionView.*,
  [UInt64PropertyDefinition].[DefaultValue],
  [UInt64PropertyDefinition].[MinValue],
  [UInt64PropertyDefinition].[MaxValue]
 FROM [UInt64PropertyDefinition]
 JOIN PropertyDefinitionView ON ([PropertyDefinitionView].Id = [UInt64PropertyDefinition].Id)

go 

CREATE OR ALTER VIEW RadarAlarmStatusView
AS
 SELECT
  [RadarAlarmStatus].[Id],
  [RadarAlarmStatus].[RowVersion],
  [RadarAlarmStatus].[Radar],
  [RadarAlarmStatus].[Timestamp],
  [RadarAlarmStatus].[Type]
 FROM [RadarAlarmStatus]

go 

CREATE OR ALTER VIEW RadarCommandView
AS
 SELECT
  [RadarCommand].[Id],
  [RadarCommand].[EntityType],
  [RadarCommand].[RowVersion],
  [RadarCommand].[Radar],
  [RadarCommand].[Timestamp],
  [RadarCommand].[DeviceCommandSourceType],
  [RadarCommand].[DeviceCommandSourceId],
  [RadarCommand].[Reply]
 FROM [RadarCommand]

go 

CREATE OR ALTER VIEW RadarCommandGetStatusView
AS
 SELECT
  RadarCommandView.*
 FROM [RadarCommandGetStatus]
 JOIN RadarCommandView ON ([RadarCommandView].Id = [RadarCommandGetStatus].Id)

go 

CREATE OR ALTER VIEW RadarCommandReplyView
AS
 SELECT
  [RadarCommandReply].[Id],
  [RadarCommandReply].[EntityType],
  [RadarCommandReply].[RowVersion],
  [RadarCommandReply].[Radar],
  [RadarCommandReply].[Timestamp],
  [RadarCommandReply].[Command],
  [RadarCommandReply].[Status],
  [RadarCommandReply].[Message]
 FROM [RadarCommandReply]

go 

CREATE OR ALTER VIEW RadarCommandReplyGetStatusView
AS
 SELECT
  RadarCommandReplyView.*,
  [RadarCommandReplyGetStatus].[AzimuthCount],
  [RadarCommandReplyGetStatus].[TriggerCount],
  [RadarCommandReplyGetStatus].[RotationCount],
  [RadarCommandReplyGetStatus].[Pulse],
  [RadarCommandReplyGetStatus].[Tx]
 FROM [RadarCommandReplyGetStatus]
 JOIN RadarCommandReplyView ON ([RadarCommandReplyView].Id = [RadarCommandReplyGetStatus].Id)

go 

CREATE OR ALTER VIEW RadarConfigurationView
AS
 SELECT
  [RadarConfiguration].[Id],
  [RadarConfiguration].[RowVersion],
  [RadarConfiguration].[Radar],
  [RadarConfiguration].[Timestamp],
  [RadarConfiguration].[RadarProtocolVersion],
  [RadarConfiguration].[RadarIPAddress],
  [RadarConfiguration].[RadarPort],
  [RadarConfiguration].[RadarConfigurationPort],
  [RadarConfiguration].[SkipMagicTimeout],
  [RadarConfiguration].[ReadTimeout],
  [RadarConfiguration].[SynchronizationInterval],
  [RadarConfiguration].[TargetsRefreshRate],
  [RadarConfiguration].[Range],
  [RadarConfiguration].[SectorCount],
  [RadarConfiguration].[SectorOffset],
  [RadarConfiguration].[ImageColor],
  [RadarConfiguration].[ImageSubstitutionColor],
  [RadarConfiguration].[TransparentColor],
  [RadarConfiguration].[ImageScaleFactorX],
  [RadarConfiguration].[ImageOffsetX],
  [RadarConfiguration].[ImageScaleFactorY],
  [RadarConfiguration].[ImageOffsetY],
  [RadarConfiguration].[RadarImageType],
  [RadarConfiguration].[TrackColor],
  [RadarConfiguration].[VectorColor],
  [RadarConfiguration].[EnableNmea],
  [RadarConfiguration].[NmeaReceiverIPAddress],
  [RadarConfiguration].[NmeaReceiverPort],
  [RadarConfiguration].[NmeaReceiverSourceId]
 FROM [RadarConfiguration]

go 

CREATE OR ALTER VIEW RadarImageView
AS
 SELECT
  [RadarImage].[Id],
  [RadarImage].[RowVersion],
  [RadarImage].[Radar],
  [RadarImage].[Timestamp],
  [RadarImage].[Depth],
  [RadarImage].[Resolution],
  [RadarImage].[Range],
  [RadarImage].[Image]
 FROM [RadarImage]

go 

CREATE OR ALTER VIEW RadarRawTrackTableView
AS
 SELECT
  [RadarRawTrackTable].[Id],
  [RadarRawTrackTable].[RowVersion],
  [RadarRawTrackTable].[Radar],
  [RadarRawTrackTable].[Timestamp],
  [RadarRawTrackTable].[Count],
  [RadarRawTrackTable].[Table]
 FROM [RadarRawTrackTable]

go 

CREATE OR ALTER VIEW RadarStatusView
AS
 SELECT
  [RadarStatus].[Id],
  [RadarStatus].[RowVersion],
  [RadarStatus].[Radar],
  [RadarStatus].[Timestamp],
  [RadarStatus].[AzimuthCount],
  [RadarStatus].[TriggerCount],
  [RadarStatus].[RotationTime],
  [RadarStatus].[Pulse],
  [RadarStatus].[Tx],
  [RadarStatus].[Tracking]
 FROM [RadarStatus]

go 

CREATE OR ALTER VIEW RadioCommandView
AS
 SELECT
  [RadioCommand].[Id],
  [RadioCommand].[RowVersion],
  [RadioCommand].[Radio],
  [RadioCommand].[Timestamp],
  [RadioCommand].[DeviceCommandSourceType],
  [RadioCommand].[DeviceCommandSourceId],
  [RadioCommand].[Reply]
 FROM [RadioCommand]

go 

CREATE OR ALTER VIEW RadioCommandReplyView
AS
 SELECT
  [RadioCommandReply].[Id],
  [RadioCommandReply].[RowVersion],
  [RadioCommandReply].[Radio],
  [RadioCommandReply].[Timestamp],
  [RadioCommandReply].[Command],
  [RadioCommandReply].[Status],
  [RadioCommandReply].[Message]
 FROM [RadioCommandReply]

go 

CREATE OR ALTER VIEW RadioConfigurationView
AS
 SELECT
  [RadioConfiguration].[Id],
  [RadioConfiguration].[RowVersion],
  [RadioConfiguration].[Radio],
  [RadioConfiguration].[Timestamp],
  [RadioConfiguration].[Longitude],
  [RadioConfiguration].[Latitude],
  [RadioConfiguration].[PlaybackUrl],
  [RadioConfiguration].[RadioIPAddress],
  [RadioConfiguration].[RadioPort],
  [RadioConfiguration].[Ed137IPAddress],
  [RadioConfiguration].[Ed137Port]
 FROM [RadioConfiguration]

go 

CREATE OR ALTER VIEW RadomeCommandView
AS
 SELECT
  [RadomeCommand].[Id],
  [RadomeCommand].[RowVersion],
  [RadomeCommand].[Radome],
  [RadomeCommand].[Timestamp],
  [RadomeCommand].[DeviceCommandSourceType],
  [RadomeCommand].[DeviceCommandSourceId],
  [RadomeCommand].[Reply]
 FROM [RadomeCommand]

go 

CREATE OR ALTER VIEW RadomeCommandReplyView
AS
 SELECT
  [RadomeCommandReply].[Id],
  [RadomeCommandReply].[RowVersion],
  [RadomeCommandReply].[Radome],
  [RadomeCommandReply].[Timestamp],
  [RadomeCommandReply].[Command],
  [RadomeCommandReply].[Status],
  [RadomeCommandReply].[Message]
 FROM [RadomeCommandReply]

go 

CREATE OR ALTER VIEW RadomeConfigurationView
AS
 SELECT
  [RadomeConfiguration].[Id],
  [RadomeConfiguration].[RowVersion],
  [RadomeConfiguration].[Radome],
  [RadomeConfiguration].[Timestamp],
  [RadomeConfiguration].[Interval],
  [RadomeConfiguration].[LowPressureLimit],
  [RadomeConfiguration].[HighPressureLimit],
  [RadomeConfiguration].[LowTemperatureLimit],
  [RadomeConfiguration].[HighTemperatureLimit]
 FROM [RadomeConfiguration]

go 

CREATE OR ALTER VIEW ReferenceTimeseriesValueView
AS
 SELECT
  [ReferenceTimeseriesValue].[Id],
  [ReferenceTimeseriesValue].[RowVersion],
  [ReferenceTimeseriesValue].[Timeseries],
  [ReferenceTimeseriesValue].[Timestamp],
  [ReferenceTimeseriesValue].[Value]
 FROM [ReferenceTimeseriesValue]

go 

CREATE OR ALTER VIEW SByteTimeseriesValueView
AS
 SELECT
  [SByteTimeseriesValue].[Id],
  [SByteTimeseriesValue].[RowVersion],
  [SByteTimeseriesValue].[Timeseries],
  [SByteTimeseriesValue].[Timestamp],
  [SByteTimeseriesValue].[Value]
 FROM [SByteTimeseriesValue]

go 

CREATE OR ALTER VIEW SecurityDomainView
AS
 SELECT
  [SecurityDomain].[Id],
  [SecurityDomain].[RowVersion],
  [SecurityDomain].[Name],
  [SecurityDomain].[Description]
 FROM [SecurityDomain]

go 

CREATE OR ALTER VIEW SecurityIdentifierView
AS
 SELECT
  [SecurityIdentifier].[Id],
  [SecurityIdentifier].[EntityType],
  [SecurityIdentifier].[RowVersion],
  [SecurityIdentifier].[Domain],
  [SecurityIdentifier].[Identity],
  [SecurityIdentifier].[Description]
 FROM [SecurityIdentifier]

go 

CREATE OR ALTER VIEW SecurityLoginView
AS
 SELECT
  SecurityIdentifierView.*
 FROM [SecurityLogin]
 JOIN SecurityIdentifierView ON ([SecurityIdentifierView].Id = [SecurityLogin].Id)

go 

CREATE OR ALTER VIEW SecurityRoleView
AS
 SELECT
  SecurityIdentifierView.*,
  [SecurityRole].[Name]
 FROM [SecurityRole]
 JOIN SecurityIdentifierView ON ([SecurityIdentifierView].Id = [SecurityRole].Id)

go 

CREATE OR ALTER VIEW SecurityIdentifierRoleLinkView
AS
 SELECT
  [SecurityIdentifierRoleLink].[Id],
  [SecurityIdentifierRoleLink].[RowVersion],
  [SecurityIdentifierRoleLink].[Member],
  [SecurityIdentifierRoleLink].[Role],
  [SecurityIdentifierRoleLink].[Start],
  [SecurityIdentifierRoleLink].[End]
 FROM [SecurityIdentifierRoleLink]

go 

CREATE OR ALTER VIEW SecurityLoginSessionView
AS
 SELECT
  [SecurityLoginSession].[Id],
  [SecurityLoginSession].[RowVersion],
  [SecurityLoginSession].[Login],
  [SecurityLoginSession].[FromTime],
  [SecurityLoginSession].[ThroughTime],
  [SecurityLoginSession].[ClientSession],
  [SecurityLoginSession].[NotificationQueueName],
  [SecurityLoginSession].[MessageQueueName]
 FROM [SecurityLoginSession]

go 

CREATE OR ALTER VIEW SecurityPermissionView
AS
 SELECT
  [SecurityPermission].[Id],
  [SecurityPermission].[RowVersion],
  [SecurityPermission].[Identifier],
  [SecurityPermission].[Timestamp],
  [SecurityPermission].[TypeCode],
  [SecurityPermission].[CanCreate],
  [SecurityPermission].[CanRead],
  [SecurityPermission].[CanUpdate],
  [SecurityPermission].[CanDelete]
 FROM [SecurityPermission]

go 

CREATE OR ALTER VIEW SingleTimeseriesValueView
AS
 SELECT
  [SingleTimeseriesValue].[Id],
  [SingleTimeseriesValue].[RowVersion],
  [SingleTimeseriesValue].[Timeseries],
  [SingleTimeseriesValue].[Timestamp],
  [SingleTimeseriesValue].[Value]
 FROM [SingleTimeseriesValue]

go 

CREATE OR ALTER VIEW StringTimeseriesValueView
AS
 SELECT
  [StringTimeseriesValue].[Id],
  [StringTimeseriesValue].[RowVersion],
  [StringTimeseriesValue].[Timeseries],
  [StringTimeseriesValue].[Timestamp],
  [StringTimeseriesValue].[Value]
 FROM [StringTimeseriesValue]

go 

CREATE OR ALTER VIEW TimeseriesCatalogElementView
AS
 SELECT
  [TimeseriesCatalogElement].[Id],
  [TimeseriesCatalogElement].[EntityType],
  [TimeseriesCatalogElement].[RowVersion],
  [TimeseriesCatalogElement].[Catalog],
  [TimeseriesCatalogElement].[Name]
 FROM [TimeseriesCatalogElement]

go 

CREATE OR ALTER VIEW TimeseriesView
AS
 SELECT
  TimeseriesCatalogElementView.*,
  [Timeseries].[MaxRetention]
 FROM [Timeseries]
 JOIN TimeseriesCatalogElementView ON ([TimeseriesCatalogElementView].Id = [Timeseries].Id)

go 

CREATE OR ALTER VIEW BinaryTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [BinaryTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [BinaryTimeseries].Id)

go 

CREATE OR ALTER VIEW BooleanTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [BooleanTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [BooleanTimeseries].Id)

go 

CREATE OR ALTER VIEW AisAidToNavigationOffPositionTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [AisAidToNavigationOffPositionTimeseries].[AidToNavigation]
 FROM [AisAidToNavigationOffPositionTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [AisAidToNavigationOffPositionTimeseries].Id)

go 

CREATE OR ALTER VIEW DeviceEnabledTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [DeviceEnabledTimeseries].[Device]
 FROM [DeviceEnabledTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [DeviceEnabledTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarAutomaticSensitivityTimeControlTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [RadarAutomaticSensitivityTimeControlTimeseries].[Radar]
 FROM [RadarAutomaticSensitivityTimeControlTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [RadarAutomaticSensitivityTimeControlTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarBlankSector1TimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [RadarBlankSector1Timeseries].[Radar]
 FROM [RadarBlankSector1Timeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [RadarBlankSector1Timeseries].Id)

go 

CREATE OR ALTER VIEW RadarBlankSector2TimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [RadarBlankSector2Timeseries].[Radar]
 FROM [RadarBlankSector2Timeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [RadarBlankSector2Timeseries].Id)

go 

CREATE OR ALTER VIEW RadarEnableAutomaticFrequencyControlTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [RadarEnableAutomaticFrequencyControlTimeseries].[Radar]
 FROM [RadarEnableAutomaticFrequencyControlTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [RadarEnableAutomaticFrequencyControlTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarEnableFastTimeConstantTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [RadarEnableFastTimeConstantTimeseries].[Radar]
 FROM [RadarEnableFastTimeConstantTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [RadarEnableFastTimeConstantTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarEnableSensitivityTimeControlTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [RadarEnableSensitivityTimeControlTimeseries].[Radar]
 FROM [RadarEnableSensitivityTimeControlTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [RadarEnableSensitivityTimeControlTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarPowerOnTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [RadarPowerOnTimeseries].[Radar]
 FROM [RadarPowerOnTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [RadarPowerOnTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarSaveSettingsTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [RadarSaveSettingsTimeseries].[Radar]
 FROM [RadarSaveSettingsTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [RadarSaveSettingsTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarTrackingTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [RadarTrackingTimeseries].[Radar]
 FROM [RadarTrackingTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [RadarTrackingTimeseries].Id)

go 

CREATE OR ALTER VIEW MediaProxySessionEnabledTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [MediaProxySessionEnabledTimeseries].[ProxySession]
 FROM [MediaProxySessionEnabledTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [MediaProxySessionEnabledTimeseries].Id)

go 

CREATE OR ALTER VIEW MediaServiceEnabledTimeseriesView
AS
 SELECT
  BooleanTimeseriesView.*,
  [MediaServiceEnabledTimeseries].[Service]
 FROM [MediaServiceEnabledTimeseries]
 JOIN BooleanTimeseriesView ON ([BooleanTimeseriesView].Id = [MediaServiceEnabledTimeseries].Id)

go 

CREATE OR ALTER VIEW ByteTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [ByteTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [ByteTimeseries].Id)

go 

CREATE OR ALTER VIEW DateTimeTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [DateTimeTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [DateTimeTimeseries].Id)

go 

CREATE OR ALTER VIEW DoubleTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [DoubleTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [DoubleTimeseries].Id)

go 

CREATE OR ALTER VIEW GNSSAltitudeTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [GNSSAltitudeTimeseries].[GNSSDevice]
 FROM [GNSSAltitudeTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [GNSSAltitudeTimeseries].Id)

go 

CREATE OR ALTER VIEW GNSSLatitudeTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [GNSSLatitudeTimeseries].[GNSSDevice]
 FROM [GNSSLatitudeTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [GNSSLatitudeTimeseries].Id)

go 

CREATE OR ALTER VIEW GNSSLongitudeTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [GNSSLongitudeTimeseries].[GNSSDevice]
 FROM [GNSSLongitudeTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [GNSSLongitudeTimeseries].Id)

go 

CREATE OR ALTER VIEW GyroCourseTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [GyroCourseTimeseries].[GyroDevice]
 FROM [GyroCourseTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [GyroCourseTimeseries].Id)

go 

CREATE OR ALTER VIEW GyroHeadingMagneticNorthTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [GyroHeadingMagneticNorthTimeseries].[GyroDevice]
 FROM [GyroHeadingMagneticNorthTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [GyroHeadingMagneticNorthTimeseries].Id)

go 

CREATE OR ALTER VIEW GyroHeadingTrueNorthTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [GyroHeadingTrueNorthTimeseries].[GyroDevice]
 FROM [GyroHeadingTrueNorthTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [GyroHeadingTrueNorthTimeseries].Id)

go 

CREATE OR ALTER VIEW GyroPitchTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [GyroPitchTimeseries].[GyroDevice]
 FROM [GyroPitchTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [GyroPitchTimeseries].Id)

go 

CREATE OR ALTER VIEW GyroRateOfTurnTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [GyroRateOfTurnTimeseries].[GyroDevice]
 FROM [GyroRateOfTurnTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [GyroRateOfTurnTimeseries].Id)

go 

CREATE OR ALTER VIEW GyroRollTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [GyroRollTimeseries].[GyroDevice]
 FROM [GyroRollTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [GyroRollTimeseries].Id)

go 

CREATE OR ALTER VIEW GyroSpeedTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [GyroSpeedTimeseries].[GyroDevice]
 FROM [GyroSpeedTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [GyroSpeedTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarLatitudeTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [RadarLatitudeTimeseries].[Radar]
 FROM [RadarLatitudeTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [RadarLatitudeTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarLongitudeTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [RadarLongitudeTimeseries].[Radar]
 FROM [RadarLongitudeTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [RadarLongitudeTimeseries].Id)

go 

CREATE OR ALTER VIEW RadomeDewPointTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [RadomeDewPointTimeseries].[Radome]
 FROM [RadomeDewPointTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [RadomeDewPointTimeseries].Id)

go 

CREATE OR ALTER VIEW RadomePressureTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [RadomePressureTimeseries].[Radome]
 FROM [RadomePressureTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [RadomePressureTimeseries].Id)

go 

CREATE OR ALTER VIEW RadomeTemperatureTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [RadomeTemperatureTimeseries].[Radome]
 FROM [RadomeTemperatureTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [RadomeTemperatureTimeseries].Id)

go 

CREATE OR ALTER VIEW VesselDraughtTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [VesselDraughtTimeseries].[Vessel]
 FROM [VesselDraughtTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [VesselDraughtTimeseries].Id)

go 

CREATE OR ALTER VIEW ViewLatitudeTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [ViewLatitudeTimeseries].[View]
 FROM [ViewLatitudeTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [ViewLatitudeTimeseries].Id)

go 

CREATE OR ALTER VIEW ViewLongitudeTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [ViewLongitudeTimeseries].[View]
 FROM [ViewLongitudeTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [ViewLongitudeTimeseries].Id)

go 

CREATE OR ALTER VIEW ViewZoomLevelTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [ViewZoomLevelTimeseries].[View]
 FROM [ViewZoomLevelTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [ViewZoomLevelTimeseries].Id)

go 

CREATE OR ALTER VIEW WeatherStationAbsoluteHumidityTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [WeatherStationAbsoluteHumidityTimeseries].[WeatherStation]
 FROM [WeatherStationAbsoluteHumidityTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [WeatherStationAbsoluteHumidityTimeseries].Id)

go 

CREATE OR ALTER VIEW WeatherStationAirTemperatureTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [WeatherStationAirTemperatureTimeseries].[WeatherStation]
 FROM [WeatherStationAirTemperatureTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [WeatherStationAirTemperatureTimeseries].Id)

go 

CREATE OR ALTER VIEW WeatherStationBarometricPressureTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [WeatherStationBarometricPressureTimeseries].[WeatherStation]
 FROM [WeatherStationBarometricPressureTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [WeatherStationBarometricPressureTimeseries].Id)

go 

CREATE OR ALTER VIEW WeatherStationDewPointTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [WeatherStationDewPointTimeseries].[WeatherStation]
 FROM [WeatherStationDewPointTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [WeatherStationDewPointTimeseries].Id)

go 

CREATE OR ALTER VIEW WeatherStationRelativeHumidityTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [WeatherStationRelativeHumidityTimeseries].[WeatherStation]
 FROM [WeatherStationRelativeHumidityTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [WeatherStationRelativeHumidityTimeseries].Id)

go 

CREATE OR ALTER VIEW WeatherStationWaterTemperatureTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [WeatherStationWaterTemperatureTimeseries].[WeatherStation]
 FROM [WeatherStationWaterTemperatureTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [WeatherStationWaterTemperatureTimeseries].Id)

go 

CREATE OR ALTER VIEW WeatherStationWindDirectionTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [WeatherStationWindDirectionTimeseries].[WeatherStation]
 FROM [WeatherStationWindDirectionTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [WeatherStationWindDirectionTimeseries].Id)

go 

CREATE OR ALTER VIEW WeatherStationWindSpeedTimeseriesView
AS
 SELECT
  DoubleTimeseriesView.*,
  [WeatherStationWindSpeedTimeseries].[WeatherStation]
 FROM [WeatherStationWindSpeedTimeseries]
 JOIN DoubleTimeseriesView ON ([DoubleTimeseriesView].Id = [WeatherStationWindSpeedTimeseries].Id)

go 

CREATE OR ALTER VIEW GeoPosition2DTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [GeoPosition2DTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [GeoPosition2DTimeseries].Id)

go 

CREATE OR ALTER VIEW AisAidToNavigationPositionTimeseriesView
AS
 SELECT
  GeoPosition2DTimeseriesView.*,
  [AisAidToNavigationPositionTimeseries].[AidToNavigation]
 FROM [AisAidToNavigationPositionTimeseries]
 JOIN GeoPosition2DTimeseriesView ON ([GeoPosition2DTimeseriesView].Id = [AisAidToNavigationPositionTimeseries].Id)

go 

CREATE OR ALTER VIEW GeoPosition3DTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [GeoPosition3DTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [GeoPosition3DTimeseries].Id)

go 

CREATE OR ALTER VIEW GuidTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [GuidTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [GuidTimeseries].Id)

go 

CREATE OR ALTER VIEW Int16TimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [Int16Timeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [Int16Timeseries].Id)

go 

CREATE OR ALTER VIEW Int32TimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [Int32Timeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [Int32Timeseries].Id)

go 

CREATE OR ALTER VIEW RadarAzimuthOffsetTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [RadarAzimuthOffsetTimeseries].[Radar]
 FROM [RadarAzimuthOffsetTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [RadarAzimuthOffsetTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarFastTimeConstantLevelTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [RadarFastTimeConstantLevelTimeseries].[Radar]
 FROM [RadarFastTimeConstantLevelTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [RadarFastTimeConstantLevelTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarFastTimeConstantModeTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [RadarFastTimeConstantModeTimeseries].[Radar]
 FROM [RadarFastTimeConstantModeTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [RadarFastTimeConstantModeTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarPulseTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [RadarPulseTimeseries].[Radar]
 FROM [RadarPulseTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [RadarPulseTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarSector1EndTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [RadarSector1EndTimeseries].[Radar]
 FROM [RadarSector1EndTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [RadarSector1EndTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarSector1StartTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [RadarSector1StartTimeseries].[Radar]
 FROM [RadarSector1StartTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [RadarSector1StartTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarSector2EndTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [RadarSector2EndTimeseries].[Radar]
 FROM [RadarSector2EndTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [RadarSector2EndTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarSector2StartTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [RadarSector2StartTimeseries].[Radar]
 FROM [RadarSector2StartTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [RadarSector2StartTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarSensitivityTimeControlLevelTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [RadarSensitivityTimeControlLevelTimeseries].[Radar]
 FROM [RadarSensitivityTimeControlLevelTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [RadarSensitivityTimeControlLevelTimeseries].Id)

go 

CREATE OR ALTER VIEW RadarTuningTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [RadarTuningTimeseries].[Radar]
 FROM [RadarTuningTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [RadarTuningTimeseries].Id)

go 

CREATE OR ALTER VIEW VesselPersonsOnBoardTimeseriesView
AS
 SELECT
  Int32TimeseriesView.*,
  [VesselPersonsOnBoardTimeseries].[Vessel]
 FROM [VesselPersonsOnBoardTimeseries]
 JOIN Int32TimeseriesView ON ([Int32TimeseriesView].Id = [VesselPersonsOnBoardTimeseries].Id)

go 

CREATE OR ALTER VIEW Int64TimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [Int64Timeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [Int64Timeseries].Id)

go 

CREATE OR ALTER VIEW Position2DTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [Position2DTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [Position2DTimeseries].Id)

go 

CREATE OR ALTER VIEW Position3DTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [Position3DTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [Position3DTimeseries].Id)

go 

CREATE OR ALTER VIEW ReferenceTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [ReferenceTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [ReferenceTimeseries].Id)

go 

CREATE OR ALTER VIEW SByteTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [SByteTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [SByteTimeseries].Id)

go 

CREATE OR ALTER VIEW SingleTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [SingleTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [SingleTimeseries].Id)

go 

CREATE OR ALTER VIEW StringTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [StringTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [StringTimeseries].Id)

go 

CREATE OR ALTER VIEW TimeSpanTimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [TimeSpanTimeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [TimeSpanTimeseries].Id)

go 

CREATE OR ALTER VIEW UInt16TimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [UInt16Timeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [UInt16Timeseries].Id)

go 

CREATE OR ALTER VIEW UInt32TimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [UInt32Timeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [UInt32Timeseries].Id)

go 

CREATE OR ALTER VIEW RadomeStatusTimeseriesView
AS
 SELECT
  UInt32TimeseriesView.*,
  [RadomeStatusTimeseries].[Radome]
 FROM [RadomeStatusTimeseries]
 JOIN UInt32TimeseriesView ON ([UInt32TimeseriesView].Id = [RadomeStatusTimeseries].Id)

go 

CREATE OR ALTER VIEW UInt64TimeseriesView
AS
 SELECT
  TimeseriesView.*
 FROM [UInt64Timeseries]
 JOIN TimeseriesView ON ([TimeseriesView].Id = [UInt64Timeseries].Id)

go 

CREATE OR ALTER VIEW TimeseriesCatalogView
AS
 SELECT
  TimeseriesCatalogElementView.*
 FROM [TimeseriesCatalog]
 JOIN TimeseriesCatalogElementView ON ([TimeseriesCatalogElementView].Id = [TimeseriesCatalog].Id)

go 

CREATE OR ALTER VIEW TimeseriesInfoView
AS
 SELECT
  [TimeseriesInfo].[Id],
  [TimeseriesInfo].[RowVersion],
  [TimeseriesInfo].[FirstTimestamp],
  [TimeseriesInfo].[LastTimestamp],
  [TimeseriesInfo].[Count]
 FROM [TimeseriesInfo]

go 

CREATE OR ALTER VIEW TimeSpanTimeseriesValueView
AS
 SELECT
  [TimeSpanTimeseriesValue].[Id],
  [TimeSpanTimeseriesValue].[RowVersion],
  [TimeSpanTimeseriesValue].[Timeseries],
  [TimeSpanTimeseriesValue].[Timestamp],
  [TimeSpanTimeseriesValue].[Value]
 FROM [TimeSpanTimeseriesValue]

go 

CREATE OR ALTER VIEW TrackableItemTrackLinkView
AS
 SELECT
  [TrackableItemTrackLink].[Id],
  [TrackableItemTrackLink].[RowVersion],
  [TrackableItemTrackLink].[Item],
  [TrackableItemTrackLink].[Track],
  [TrackableItemTrackLink].[Start],
  [TrackableItemTrackLink].[End]
 FROM [TrackableItemTrackLink]

go 

CREATE OR ALTER VIEW TrackBaseView
AS
 SELECT
  [TrackBase].[Id],
  [TrackBase].[EntityType],
  [TrackBase].[RowVersion],
  [TrackBase].[Tracker],
  [TrackBase].[TrackNumber],
  [TrackBase].[Timestamp]
 FROM [TrackBase]

go 

CREATE OR ALTER VIEW TrackView
AS
 SELECT
  TrackBaseView.*
 FROM [Track]
 JOIN TrackBaseView ON ([TrackBaseView].Id = [Track].Id)

go 

CREATE OR ALTER VIEW Track3DView
AS
 SELECT
  TrackBaseView.*
 FROM [Track3D]
 JOIN TrackBaseView ON ([TrackBaseView].Id = [Track3D].Id)

go 

CREATE OR ALTER VIEW TrackerFilterParametersView
AS
 SELECT
  [TrackerFilterParameters].[Id],
  [TrackerFilterParameters].[RowVersion],
  [TrackerFilterParameters].[Tracker],
  [TrackerFilterParameters].[Name]
 FROM [TrackerFilterParameters]

go 

CREATE OR ALTER VIEW TrackerFilterParametersConfigurationView
AS
 SELECT
  [TrackerFilterParametersConfiguration].[Id],
  [TrackerFilterParametersConfiguration].[RowVersion],
  [TrackerFilterParametersConfiguration].[Parameters],
  [TrackerFilterParametersConfiguration].[Timestamp],
  [TrackerFilterParametersConfiguration].[UseNaivePredictor],
  [TrackerFilterParametersConfiguration].[NumberOfPoints],
  [TrackerFilterParametersConfiguration].[WindowSize],
  [TrackerFilterParametersConfiguration].[StabilizeCount],
  [TrackerFilterParametersConfiguration].[MaxBadPoints],
  [TrackerFilterParametersConfiguration].[ModelType],
  [TrackerFilterParametersConfiguration].[SigmaR],
  [TrackerFilterParametersConfiguration].[SigmaAcc],
  [TrackerFilterParametersConfiguration].[TauVel],
  [TrackerFilterParametersConfiguration].[TauAcc],
  [TrackerFilterParametersConfiguration].[DeltaRMin],
  [TrackerFilterParametersConfiguration].[DeltaVMax],
  [TrackerFilterParametersConfiguration].[DeltaAMax]
 FROM [TrackerFilterParametersConfiguration]

go 

CREATE OR ALTER VIEW TrackInfoView
AS
 SELECT
  [TrackInfo].[Id],
  [TrackInfo].[RowVersion],
  [TrackInfo].[FirstTimestamp],
  [TrackInfo].[LastTimestamp],
  [TrackInfo].[Count],
  [TrackInfo].[NorthWestLatitude],
  [TrackInfo].[NorthWestLongitude],
  [TrackInfo].[SouthEastLatitude],
  [TrackInfo].[SouthEastLongitude]
 FROM [TrackInfo]

go 

CREATE OR ALTER VIEW TrackingServiceOptionsView
AS
 SELECT
  [TrackingServiceOptions].[Id],
  [TrackingServiceOptions].[RowVersion],
  [TrackingServiceOptions].[Timestamp],
  [TrackingServiceOptions].[TimerInterval],
  [TrackingServiceOptions].[MaxAgeOfCurrentTrackValue],
  [TrackingServiceOptions].[FalseThreshold],
  [TrackingServiceOptions].[DistanceThreshold],
  [TrackingServiceOptions].[DistanceUnmergeThreshold],
  [TrackingServiceOptions].[UnmergeLatency],
  [TrackingServiceOptions].[KalmanFiltering],
  [TrackingServiceOptions].[MaxCourseDeviation],
  [TrackingServiceOptions].[MaxSpeedDeviation],
  [TrackingServiceOptions].[MinimumSpeedThreshold]
 FROM [TrackingServiceOptions]

go 

CREATE OR ALTER VIEW TrackLinkView
AS
 SELECT
  [TrackLink].[Id],
  [TrackLink].[RowVersion],
  [TrackLink].[Primary],
  [TrackLink].[Secondary],
  [TrackLink].[Start],
  [TrackLink].[End]
 FROM [TrackLink]

go 

CREATE OR ALTER VIEW TrackValueView
AS
 SELECT
  [TrackValue].[Id],
  [TrackValue].[RowVersion],
  [TrackValue].[Track],
  [TrackValue].[Timestamp],
  [TrackValue].[Flags],
  [TrackValue].[Status],
  [TrackValue].[Latitude],
  [TrackValue].[Longitude],
  [TrackValue].[Speed],
  [TrackValue].[Course],
  [TrackValue].[Heading]
 FROM [TrackValue]

go 

CREATE OR ALTER VIEW TrackValue3DView
AS
 SELECT
  [TrackValue3D].[Id],
  [TrackValue3D].[RowVersion],
  [TrackValue3D].[Track],
  [TrackValue3D].[Timestamp],
  [TrackValue3D].[Flags],
  [TrackValue3D].[Status],
  [TrackValue3D].[Latitude],
  [TrackValue3D].[Longitude],
  [TrackValue3D].[Altitude],
  [TrackValue3D].[Speed],
  [TrackValue3D].[Course],
  [TrackValue3D].[RateOfClimb]
 FROM [TrackValue3D]

go 

CREATE OR ALTER VIEW UInt16TimeseriesValueView
AS
 SELECT
  [UInt16TimeseriesValue].[Id],
  [UInt16TimeseriesValue].[RowVersion],
  [UInt16TimeseriesValue].[Timeseries],
  [UInt16TimeseriesValue].[Timestamp],
  [UInt16TimeseriesValue].[Value]
 FROM [UInt16TimeseriesValue]

go 

CREATE OR ALTER VIEW UInt32TimeseriesValueView
AS
 SELECT
  [UInt32TimeseriesValue].[Id],
  [UInt32TimeseriesValue].[RowVersion],
  [UInt32TimeseriesValue].[Timeseries],
  [UInt32TimeseriesValue].[Timestamp],
  [UInt32TimeseriesValue].[Value]
 FROM [UInt32TimeseriesValue]

go 

CREATE OR ALTER VIEW UInt64TimeseriesValueView
AS
 SELECT
  [UInt64TimeseriesValue].[Id],
  [UInt64TimeseriesValue].[RowVersion],
  [UInt64TimeseriesValue].[Timeseries],
  [UInt64TimeseriesValue].[Timestamp],
  [UInt64TimeseriesValue].[Value]
 FROM [UInt64TimeseriesValue]

go 

CREATE OR ALTER VIEW VehicleTypeView
AS
 SELECT
  [VehicleType].[Id],
  [VehicleType].[RowVersion],
  [VehicleType].[Name]
 FROM [VehicleType]

go 

CREATE OR ALTER VIEW VesselTypeView
AS
 SELECT
  [VesselType].[Id],
  [VesselType].[RowVersion],
  [VesselType].[Name],
  [VesselType].[Code]
 FROM [VesselType]

go 

CREATE OR ALTER VIEW ViewView
AS
 SELECT
  [View].[Id],
  [View].[RowVersion],
  [View].[Name],
  [View].[LatitudeTimeseries],
  [View].[LongitudeTimeseries],
  [View].[ZoomLevelTimeseries]
 FROM [View]

go 

CREATE OR ALTER VIEW ViewCameraLinkView
AS
 SELECT
  [ViewCameraLink].[Id],
  [ViewCameraLink].[RowVersion],
  [ViewCameraLink].[View],
  [ViewCameraLink].[Camera],
  [ViewCameraLink].[Start],
  [ViewCameraLink].[End]
 FROM [ViewCameraLink]

go 

CREATE OR ALTER VIEW ViewTrackerLinkView
AS
 SELECT
  [ViewTrackerLink].[Id],
  [ViewTrackerLink].[RowVersion],
  [ViewTrackerLink].[View],
  [ViewTrackerLink].[Tracker],
  [ViewTrackerLink].[Start],
  [ViewTrackerLink].[End]
 FROM [ViewTrackerLink]

go 

CREATE OR ALTER VIEW WeatherStationCommandView
AS
 SELECT
  [WeatherStationCommand].[Id],
  [WeatherStationCommand].[RowVersion],
  [WeatherStationCommand].[WeatherStation],
  [WeatherStationCommand].[Timestamp],
  [WeatherStationCommand].[DeviceCommandSourceType],
  [WeatherStationCommand].[DeviceCommandSourceId],
  [WeatherStationCommand].[Reply]
 FROM [WeatherStationCommand]

go 

CREATE OR ALTER VIEW WeatherStationCommandReplyView
AS
 SELECT
  [WeatherStationCommandReply].[Id],
  [WeatherStationCommandReply].[RowVersion],
  [WeatherStationCommandReply].[WeatherStation],
  [WeatherStationCommandReply].[Timestamp],
  [WeatherStationCommandReply].[Command],
  [WeatherStationCommandReply].[Status],
  [WeatherStationCommandReply].[Message]
 FROM [WeatherStationCommandReply]

go 

CREATE OR ALTER VIEW WeatherStationConfigurationView
AS
 SELECT
  [WeatherStationConfiguration].[Id],
  [WeatherStationConfiguration].[RowVersion],
  [WeatherStationConfiguration].[WeatherStation],
  [WeatherStationConfiguration].[Timestamp],
  [WeatherStationConfiguration].[NoDataTimeOut],
  [WeatherStationConfiguration].[SendInterval],
  [WeatherStationConfiguration].[Latitude],
  [WeatherStationConfiguration].[Longitude],
  [WeatherStationConfiguration].[GyroOffset],
  [WeatherStationConfiguration].[EnableAveraging],
  [WeatherStationConfiguration].[AveragingInterval]
 FROM [WeatherStationConfiguration]

go 

CREATE OR ALTER VIEW ZoneView
AS
 SELECT
  [Zone].[Id],
  [Zone].[EntityType],
  [Zone].[RowVersion],
  [Zone].[Name],
  [Zone].[Longitude],
  [Zone].[Latitude],
  [Zone].[AlarmType],
  [Zone].[AlarmTime],
  [Zone].[RadarTrackMinimumLifetime],
  [Zone].[Speed],
  [Zone].[StrokeColor],
  [Zone].[FillColor]
 FROM [Zone]

go 

CREATE OR ALTER VIEW CircularZoneView
AS
 SELECT
  ZoneView.*,
  [CircularZone].[Radius]
 FROM [CircularZone]
 JOIN ZoneView ON ([ZoneView].Id = [CircularZone].Id)

go 

CREATE OR ALTER VIEW PolygonZoneView
AS
 SELECT
  ZoneView.*,
  [PolygonZone].[Polygon]
 FROM [PolygonZone]
 JOIN ZoneView ON ([ZoneView].Id = [PolygonZone].Id)

go 

CREATE OR ALTER VIEW ZoneExceptionsView
AS
 SELECT
  [ZoneExceptions].[Id],
  [ZoneExceptions].[RowVersion],
  [ZoneExceptions].[Zone],
  [ZoneExceptions].[Timestamp]
 FROM [ZoneExceptions]

go 

CREATE OR ALTER VIEW ZoneExceptionsVesselLinkView
AS
 SELECT
  [ZoneExceptionsVesselLink].[Id],
  [ZoneExceptionsVesselLink].[RowVersion],
  [ZoneExceptionsVesselLink].[ZoneExceptions],
  [ZoneExceptionsVesselLink].[Vessel]
 FROM [ZoneExceptionsVesselLink]

go 

CREATE OR ALTER VIEW ZoneTrackAlarmView
AS
 SELECT
  [ZoneTrackAlarm].[Id],
  [ZoneTrackAlarm].[RowVersion],
  [ZoneTrackAlarm].[Track],
  [ZoneTrackAlarm].[Zone],
  [ZoneTrackAlarm].[RadarTrack],
  [ZoneTrackAlarm].[Timestamp],
  [ZoneTrackAlarm].[Latitude],
  [ZoneTrackAlarm].[Longitude],
  [ZoneTrackAlarm].[Speed],
  [ZoneTrackAlarm].[Course],
  [ZoneTrackAlarm].[Heading],
  [ZoneTrackAlarm].[EnterLatitude],
  [ZoneTrackAlarm].[EnterLongitude],
  [ZoneTrackAlarm].[LeaveLatitude],
  [ZoneTrackAlarm].[LeaveLongitude]
 FROM [ZoneTrackAlarm]

go 

