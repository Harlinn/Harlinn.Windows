/*
 * Entity type identifiers
 *
 */
CREATE TABLE [dbo].[EntityTypes]
(
  [Id][int] IDENTITY(1, 1) NOT NULL,
  [EntityName][nvarchar](254) NOT NULL,
  CONSTRAINT [PK_EntityTypes] PRIMARY KEY( [Id] ),
  CONSTRAINT[ Unq_EntityName ] UNIQUE( [EntityName] )
)
go

/*
 * AircraftType
 *
 */
CREATE TABLE [dbo].[AircraftType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [PK_AircraftType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[AircraftType]
  ADD CONSTRAINT [UNQ_AircraftType_Name] UNIQUE([Name])
go

/*
 * AisMessage
 *
 */
CREATE TABLE [dbo].[AisMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between AisMessage
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [AisTransceiver] [uniqueidentifier] NOT NULL,
  [ReceivedTimestamp] [bigint] NOT NULL,
  [MessageSequenceNumber] [bigint] NOT NULL,
  [Repeat] [int] NOT NULL,
  [Mmsi] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_AisMessage_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_AisMessage] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[AisMessage]
  ADD CONSTRAINT [UNQ_AisMessage_AisTransceiver_ReceivedTimestamp] UNIQUE([AisTransceiver],[ReceivedTimestamp])
go

CREATE INDEX [IDX_AisMessage_ReceivedTimestamp] ON [dbo].[AisMessage]([ReceivedTimestamp])
go

CREATE INDEX [IDX_AisMessage_Mmsi_MessageSequenceNumber] ON [dbo].[AisMessage]([Mmsi],[MessageSequenceNumber])
go

/*
 * AidToNavigationReportMessage
 *
 * The AidToNavigationReportMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AidToNavigationReportMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AidToNavigationReportMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [NavigationalAidType] [int] NOT NULL,
  [Name] [nvarchar](100) NOT NULL,
  [PositionAccuracy] [int] NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [DimensionToBow] [int] NOT NULL,
  [DimensionToStern] [int] NOT NULL,
  [DimensionToPort] [int] NOT NULL,
  [DimensionToStarboard] [int] NOT NULL,
  [PositionFixType] [int] NOT NULL,
  [Timestamp] [int] NOT NULL,
  [OffPosition] [bit] NOT NULL,
  [RegionalReserved] [int] NOT NULL,
  [Raim] [int] NOT NULL,
  [VirtualAid] [bit] NOT NULL,
  [Assigned] [bit] NOT NULL,
  [Spare] [int] NOT NULL,
  [NameExtension] [nvarchar](100) NOT NULL,
  CONSTRAINT [FK_AidToNavigationReportMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AidToNavigationReportMessage] PRIMARY KEY([Id])
)
go

/*
 * AisAddressedSafetyRelatedMessage
 *
 * The AisAddressedSafetyRelatedMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisAddressedSafetyRelatedMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisAddressedSafetyRelatedMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [SequenceNumber] [int] NOT NULL,
  [DestinationMmsi] [uniqueidentifier] NOT NULL,
  [RetransmitFlag] [bit] NOT NULL,
  [Spare] [int] NOT NULL,
  [Text] [nvarchar](100) NOT NULL,
  CONSTRAINT [FK_AisAddressedSafetyRelatedMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisAddressedSafetyRelatedMessage] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisAddressedSafetyRelatedMessage_DestinationMmsi] ON [dbo].[AisAddressedSafetyRelatedMessage]([DestinationMmsi])
go

/*
 * AisBaseStationReportMessage
 *
 * The AisBaseStationReportMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisBaseStationReportMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisBaseStationReportMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [PositionAccuracy] [int] NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [PositionFixType] [int] NOT NULL,
  [Spare] [int] NOT NULL,
  [Raim] [int] NOT NULL,
  [RadioStatus] [int] NOT NULL,
  CONSTRAINT [FK_AisBaseStationReportMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisBaseStationReportMessage] PRIMARY KEY([Id])
)
go

/*
 * AisBinaryAcknowledgeMessage
 *
 * The AisBinaryAcknowledgeMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisBinaryAcknowledgeMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisBinaryAcknowledgeMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Spare] [int] NOT NULL,
  [SequenceNumber1] [int] NOT NULL,
  [Mmsi1] [uniqueidentifier] NOT NULL,
  [SequenceNumber2] [int] NOT NULL,
  [Mmsi2] [uniqueidentifier] NOT NULL,
  [SequenceNumber3] [int] NOT NULL,
  [Mmsi3] [uniqueidentifier] NOT NULL,
  [SequenceNumber4] [int] NOT NULL,
  [Mmsi4] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_AisBinaryAcknowledgeMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisBinaryAcknowledgeMessage] PRIMARY KEY([Id])
)
go

/*
 * AisBinaryAddressedMessage
 *
 * The AisBinaryAddressedMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisBinaryAddressedMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisBinaryAddressedMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [SequenceNumber] [int] NOT NULL,
  [DestinationMmsi] [uniqueidentifier] NOT NULL,
  [RetransmitFlag] [bit] NOT NULL,
  [Spare] [int] NOT NULL,
  [DesignatedAreaCode] [int] NOT NULL,
  [FunctionalId] [int] NOT NULL,
  [Data] [nvarchar](max) NOT NULL,
  CONSTRAINT [FK_AisBinaryAddressedMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisBinaryAddressedMessage] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisBinaryAddressedMessage_DestinationMmsi] ON [dbo].[AisBinaryAddressedMessage]([DestinationMmsi])
go

/*
 * AisBinaryBroadcastMessage
 *
 * The AisBinaryBroadcastMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisBinaryBroadcastMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisBinaryBroadcastMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Spare] [int] NOT NULL,
  [DesignatedAreaCode] [int] NOT NULL,
  [FunctionalId] [int] NOT NULL,
  [Data] [nvarchar](max) NOT NULL,
  CONSTRAINT [FK_AisBinaryBroadcastMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisBinaryBroadcastMessage] PRIMARY KEY([Id])
)
go

/*
 * AisDataLinkManagementMessage
 *
 * The AisDataLinkManagementMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisDataLinkManagementMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisDataLinkManagementMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Spare] [int] NOT NULL,
  [Offset1] [int] NOT NULL,
  [ReservedSlots1] [int] NOT NULL,
  [Timeout1] [int] NOT NULL,
  [Increment1] [int] NOT NULL,
  [Offset2] [int] NOT NULL,
  [ReservedSlots2] [int] NOT NULL,
  [Timeout2] [int] NOT NULL,
  [Increment2] [int] NOT NULL,
  [Offset3] [int] NOT NULL,
  [ReservedSlots3] [int] NOT NULL,
  [Timeout3] [int] NOT NULL,
  [Increment3] [int] NOT NULL,
  [Offset4] [int] NOT NULL,
  [ReservedSlots4] [int] NOT NULL,
  [Timeout4] [int] NOT NULL,
  [Increment4] [int] NOT NULL,
  CONSTRAINT [FK_AisDataLinkManagementMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisDataLinkManagementMessage] PRIMARY KEY([Id])
)
go

/*
 * AisExtendedClassBCsPositionReportMessage
 *
 * The AisExtendedClassBCsPositionReportMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisExtendedClassBCsPositionReportMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisExtendedClassBCsPositionReportMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Reserved] [int] NOT NULL,
  [SpeedOverGround] [float](53) NOT NULL,
  [PositionAccuracy] [int] NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [CourseOverGround] [float](53) NOT NULL,
  [TrueHeading] [int] NULL,
  [Timestamp] [int] NOT NULL,
  [RegionalReserved] [int] NOT NULL,
  [Name] [uniqueidentifier] NOT NULL,
  [ShipType] [int] NOT NULL,
  [DimensionToBow] [int] NOT NULL,
  [DimensionToStern] [int] NOT NULL,
  [DimensionToPort] [int] NOT NULL,
  [DimensionToStarboard] [int] NOT NULL,
  [PositionFixType] [int] NOT NULL,
  [Raim] [int] NOT NULL,
  [DataTerminalReady] [bit] NOT NULL,
  [Assigned] [bit] NOT NULL,
  [Spare] [int] NOT NULL,
  CONSTRAINT [FK_AisExtendedClassBCsPositionReportMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisExtendedClassBCsPositionReportMessage] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisExtendedClassBCsPositionReportMessage_Name] ON [dbo].[AisExtendedClassBCsPositionReportMessage]([Name])
go

/*
 * AisInterrogationMessage
 *
 * The AisInterrogationMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisInterrogationMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisInterrogationMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [InterrogatedMmsi] [uniqueidentifier] NOT NULL,
  [FirstMessageType] [int] NOT NULL,
  [FirstSlotOffset] [int] NOT NULL,
  [SecondMessageType] [int] NULL,
  [SecondSlotOffset] [int] NULL,
  [SecondStationInterrogationMmsi] [uniqueidentifier] NOT NULL,
  [SecondStationFirstMessageType] [int] NULL,
  [SecondStationFirstSlotOffset] [int] NULL,
  CONSTRAINT [FK_AisInterrogationMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisInterrogationMessage] PRIMARY KEY([Id])
)
go

/*
 * AisPositionReportClassAMessageBase
 *
 * The AisPositionReportClassAMessageBase entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisPositionReportClassAMessageBase].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisPositionReportClassAMessageBase]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [NavigationStatus] [int] NOT NULL,
  [RateOfTurn] [int] NULL,
  [SpeedOverGround] [float](53) NOT NULL,
  [PositionAccuracy] [int] NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [CourseOverGround] [float](53) NOT NULL,
  [TrueHeading] [int] NULL,
  [Timestamp] [int] NOT NULL,
  [ManeuverIndicator] [int] NOT NULL,
  [Spare] [int] NOT NULL,
  [Raim] [int] NOT NULL,
  [RadioStatus] [int] NOT NULL,
  CONSTRAINT [FK_AisPositionReportClassAMessageBase_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisPositionReportClassAMessageBase] PRIMARY KEY([Id])
)
go

/*
 * AisPositionReportClassAAssignedScheduleMessage
 *
 * The AisPositionReportClassAAssignedScheduleMessage entity a descendant of the AisPositionReportClassAMessageBase entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisPositionReportClassAAssignedScheduleMessage].[Id] field and the
 * [dbo].[AisPositionReportClassAMessageBase].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisPositionReportClassAAssignedScheduleMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_AisPositionReportClassAAssignedScheduleMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisPositionReportClassAMessageBase]([Id]),
  CONSTRAINT [PK_AisPositionReportClassAAssignedScheduleMessage] PRIMARY KEY([Id])
)
go

/*
 * AisPositionReportClassAMessage
 *
 * The AisPositionReportClassAMessage entity a descendant of the AisPositionReportClassAMessageBase entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisPositionReportClassAMessage].[Id] field and the
 * [dbo].[AisPositionReportClassAMessageBase].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisPositionReportClassAMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_AisPositionReportClassAMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisPositionReportClassAMessageBase]([Id]),
  CONSTRAINT [PK_AisPositionReportClassAMessage] PRIMARY KEY([Id])
)
go

/*
 * AisPositionReportClassAResponseToInterrogationMessage
 *
 * The AisPositionReportClassAResponseToInterrogationMessage entity a descendant of the AisPositionReportClassAMessageBase entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisPositionReportClassAResponseToInterrogationMessage].[Id] field and the
 * [dbo].[AisPositionReportClassAMessageBase].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisPositionReportClassAResponseToInterrogationMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_AisPositionReportClassAResponseToInterrogationMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisPositionReportClassAMessageBase]([Id]),
  CONSTRAINT [PK_AisPositionReportClassAResponseToInterrogationMessage] PRIMARY KEY([Id])
)
go

/*
 * AisPositionReportForLongRangeApplicationsMessage
 *
 * The AisPositionReportForLongRangeApplicationsMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisPositionReportForLongRangeApplicationsMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisPositionReportForLongRangeApplicationsMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [PositionAccuracy] [int] NOT NULL,
  [Raim] [int] NOT NULL,
  [NavigationStatus] [int] NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [SpeedOverGround] [float](53) NOT NULL,
  [CourseOverGround] [float](53) NOT NULL,
  [GnssPositionStatus] [int] NOT NULL,
  [Spare] [int] NOT NULL,
  CONSTRAINT [FK_AisPositionReportForLongRangeApplicationsMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisPositionReportForLongRangeApplicationsMessage] PRIMARY KEY([Id])
)
go

/*
 * AisSafetyRelatedAcknowledgmentMessage
 *
 * The AisSafetyRelatedAcknowledgmentMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisSafetyRelatedAcknowledgmentMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisSafetyRelatedAcknowledgmentMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Spare] [int] NOT NULL,
  [SequenceNumber1] [int] NOT NULL,
  [Mmsi1] [uniqueidentifier] NOT NULL,
  [SequenceNumber2] [int] NOT NULL,
  [Mmsi2] [uniqueidentifier] NOT NULL,
  [SequenceNumber3] [int] NOT NULL,
  [Mmsi3] [uniqueidentifier] NOT NULL,
  [SequenceNumber4] [int] NOT NULL,
  [Mmsi4] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_AisSafetyRelatedAcknowledgmentMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisSafetyRelatedAcknowledgmentMessage] PRIMARY KEY([Id])
)
go

/*
 * AisStandardClassBCsPositionReportMessage
 *
 * The AisStandardClassBCsPositionReportMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisStandardClassBCsPositionReportMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisStandardClassBCsPositionReportMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Reserved] [int] NOT NULL,
  [SpeedOverGround] [float](53) NOT NULL,
  [PositionAccuracy] [int] NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [CourseOverGround] [float](53) NOT NULL,
  [TrueHeading] [int] NULL,
  [Timestamp] [int] NOT NULL,
  [RegionalReserved] [int] NOT NULL,
  [IsCsUnit] [bit] NOT NULL,
  [HasDisplay] [bit] NOT NULL,
  [HasDscCapability] [bit] NOT NULL,
  [Band] [bit] NOT NULL,
  [CanAcceptMessage22] [bit] NOT NULL,
  [Assigned] [bit] NOT NULL,
  [Raim] [int] NOT NULL,
  [RadioStatus] [int] NOT NULL,
  CONSTRAINT [FK_AisStandardClassBCsPositionReportMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisStandardClassBCsPositionReportMessage] PRIMARY KEY([Id])
)
go

/*
 * AisStandardSarAircraftPositionReportMessage
 *
 * The AisStandardSarAircraftPositionReportMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisStandardSarAircraftPositionReportMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisStandardSarAircraftPositionReportMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Altitude] [int] NOT NULL,
  [SpeedOverGround] [int] NOT NULL,
  [PositionAccuracy] [int] NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [CourseOverGround] [float](53) NOT NULL,
  [Timestamp] [int] NOT NULL,
  [Reserved] [int] NOT NULL,
  [DataTerminalReady] [bit] NOT NULL,
  [Spare] [int] NOT NULL,
  [Assigned] [bit] NOT NULL,
  [Raim] [int] NOT NULL,
  [RadioStatus] [int] NOT NULL,
  CONSTRAINT [FK_AisStandardSarAircraftPositionReportMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisStandardSarAircraftPositionReportMessage] PRIMARY KEY([Id])
)
go

/*
 * AisStaticAndVoyageRelatedDataMessage
 *
 * The AisStaticAndVoyageRelatedDataMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisStaticAndVoyageRelatedDataMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisStaticAndVoyageRelatedDataMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [AisVersion] [int] NOT NULL,
  [ImoNumber] [uniqueidentifier] NOT NULL,
  [Callsign] [uniqueidentifier] NOT NULL,
  [ShipName] [uniqueidentifier] NOT NULL,
  [ShipType] [int] NOT NULL,
  [DimensionToBow] [int] NOT NULL,
  [DimensionToStern] [int] NOT NULL,
  [DimensionToPort] [int] NOT NULL,
  [DimensionToStarboard] [int] NOT NULL,
  [PositionFixType] [int] NOT NULL,
  [EstimatedTimeOfArrival] [bigint] NULL,
  [Draught] [float](53) NOT NULL,
  [Destination] [nvarchar](100) NOT NULL,
  [DataTerminalReady] [bit] NOT NULL,
  [Spare] [int] NOT NULL,
  CONSTRAINT [FK_AisStaticAndVoyageRelatedDataMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisStaticAndVoyageRelatedDataMessage] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisStaticAndVoyageRelatedDataMessage_ImoNumber] ON [dbo].[AisStaticAndVoyageRelatedDataMessage]([ImoNumber])
go

CREATE INDEX [IDX_AisStaticAndVoyageRelatedDataMessage_Callsign] ON [dbo].[AisStaticAndVoyageRelatedDataMessage]([Callsign])
go

CREATE INDEX [IDX_AisStaticAndVoyageRelatedDataMessage_ShipName] ON [dbo].[AisStaticAndVoyageRelatedDataMessage]([ShipName])
go

/*
 * AisStaticDataReportMessage
 *
 * The AisStaticDataReportMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisStaticDataReportMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisStaticDataReportMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [PartNumber] [int] NOT NULL,
  CONSTRAINT [FK_AisStaticDataReportMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisStaticDataReportMessage] PRIMARY KEY([Id])
)
go

/*
 * AisStaticDataReportPartAMessage
 *
 * The AisStaticDataReportPartAMessage entity a descendant of the AisStaticDataReportMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisStaticDataReportPartAMessage].[Id] field and the
 * [dbo].[AisStaticDataReportMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisStaticDataReportPartAMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [ShipName] [uniqueidentifier] NOT NULL,
  [Spare] [int] NOT NULL,
  CONSTRAINT [FK_AisStaticDataReportPartAMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisStaticDataReportMessage]([Id]),
  CONSTRAINT [PK_AisStaticDataReportPartAMessage] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisStaticDataReportPartAMessage_ShipName] ON [dbo].[AisStaticDataReportPartAMessage]([ShipName])
go

/*
 * AisStaticDataReportPartBMessage
 *
 * The AisStaticDataReportPartBMessage entity a descendant of the AisStaticDataReportMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisStaticDataReportPartBMessage].[Id] field and the
 * [dbo].[AisStaticDataReportMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisStaticDataReportPartBMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [ShipType] [int] NOT NULL,
  [VendorId] [nvarchar](100) NOT NULL,
  [UnitModelCode] [int] NOT NULL,
  [SerialNumber] [int] NOT NULL,
  [Callsign] [uniqueidentifier] NOT NULL,
  [DimensionToBow] [int] NOT NULL,
  [DimensionToStern] [int] NOT NULL,
  [DimensionToPort] [int] NOT NULL,
  [DimensionToStarboard] [int] NOT NULL,
  [MothershipMmsi] [uniqueidentifier] NOT NULL,
  [PositionFixType] [int] NOT NULL,
  [Spare] [int] NOT NULL,
  CONSTRAINT [FK_AisStaticDataReportPartBMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisStaticDataReportMessage]([Id]),
  CONSTRAINT [PK_AisStaticDataReportPartBMessage] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisStaticDataReportPartBMessage_Callsign] ON [dbo].[AisStaticDataReportPartBMessage]([Callsign])
go

CREATE INDEX [IDX_AisStaticDataReportPartBMessage_MothershipMmsi] ON [dbo].[AisStaticDataReportPartBMessage]([MothershipMmsi])
go

/*
 * AisUtcAndDateInquiryMessage
 *
 * The AisUtcAndDateInquiryMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisUtcAndDateInquiryMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisUtcAndDateInquiryMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Spare1] [int] NOT NULL,
  [DestinationMmsi] [int] NOT NULL,
  [Spare2] [int] NOT NULL,
  CONSTRAINT [FK_AisUtcAndDateInquiryMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisUtcAndDateInquiryMessage] PRIMARY KEY([Id])
)
go

/*
 * AisUtcAndDateResponseMessage
 *
 * The AisUtcAndDateResponseMessage entity a descendant of the AisMessage entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisUtcAndDateResponseMessage].[Id] field and the
 * [dbo].[AisMessage].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisUtcAndDateResponseMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Datetime] [bigint] NOT NULL,
  [PositionAccuracy] [int] NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [PositionFixType] [int] NOT NULL,
  [Spare] [int] NOT NULL,
  [Raim] [int] NOT NULL,
  [RadioStatus] [int] NOT NULL,
  CONSTRAINT [FK_AisUtcAndDateResponseMessage_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[AisMessage]([Id]),
  CONSTRAINT [PK_AisUtcAndDateResponseMessage] PRIMARY KEY([Id])
)
go

/*
 * AisTransceiverCommand
 *
 */
CREATE TABLE [dbo].[AisTransceiverCommand]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [AisTransceiver] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DeviceCommandSourceType] [int] NOT NULL,
  [DeviceCommandSourceId] [uniqueidentifier] NOT NULL,
  [Reply] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_AisTransceiverCommand] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisTransceiverCommand_AisTransceiver_Timestamp] ON [dbo].[AisTransceiverCommand]([AisTransceiver],[Timestamp])
go

CREATE INDEX [IDX_AisTransceiverCommand_Timestamp] ON [dbo].[AisTransceiverCommand]([Timestamp])
go

CREATE INDEX [IDX_AisTransceiverCommand_Reply] ON [dbo].[AisTransceiverCommand]([Reply])
go

/*
 * AisTransceiverCommandReply
 *
 */
CREATE TABLE [dbo].[AisTransceiverCommandReply]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [AisTransceiver] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Command] [uniqueidentifier] NOT NULL,
  [Status] [int] NOT NULL,
  [Message] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_AisTransceiverCommandReply] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisTransceiverCommandReply_AisTransceiver_Timestamp] ON [dbo].[AisTransceiverCommandReply]([AisTransceiver],[Timestamp])
go

CREATE INDEX [IDX_AisTransceiverCommandReply_Timestamp] ON [dbo].[AisTransceiverCommandReply]([Timestamp])
go

ALTER TABLE [dbo].[AisTransceiverCommandReply]
  ADD CONSTRAINT [UNQ_AisTransceiverCommandReply_Command] UNIQUE([Command])
go

/*
 * AisTransceiverConfiguration
 *
 */
CREATE TABLE [dbo].[AisTransceiverConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [AisTransceiver] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [UserName] [nvarchar](127) NOT NULL,
  [Password] [nvarchar](127) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [AisProviderLoginURL] [nvarchar](127) NOT NULL,
  [ComPort] [nvarchar](32) NOT NULL,
  [BaudRate] [int] NOT NULL,
  [FilterByArea] [bit] NOT NULL,
  [UpperLeftCornerLatitude] [float](53) NOT NULL,
  [UpperLeftCornerLongitude] [float](53) NOT NULL,
  [BottomRightCornerLatitude] [float](53) NOT NULL,
  [BottomRightCornerLongitude] [float](53) NOT NULL,
  [AisProviderIPAddress] [nvarchar](127) NOT NULL,
  [AisProviderPort] [int] NOT NULL,
  [UseLogin] [bit] NOT NULL,
  [AisProviderLoginPort] [int] NOT NULL,
  [CanSendAISMessage] [bit] NOT NULL,
  [TextMessageHeader] [nvarchar](max) NOT NULL,
  [Urls] [nvarchar](max) NOT NULL,
  [UdpPort] [int] NOT NULL,
  [ConnectionType] [int] NOT NULL,
  [EnableRefreshAidToNavigationIn30sec] [bit] NOT NULL,
  [EnableAidToNavigationFromFile] [bit] NOT NULL,
  [AidToNavigationHeader] [nvarchar](max) NOT NULL,
  [SendingMMSI] [bit] NOT NULL,
  [SourceUpdateRate] [int] NOT NULL,
  [EnableRefreshStayingStillTargetIn30sec] [bit] NOT NULL,
  [ExcludeSendAisBaseStation] [nvarchar](max) NOT NULL,
  [ExcludeSendAisA] [nvarchar](max) NOT NULL,
  [EnableSendBaseStationAlarms] [bit] NOT NULL,
  [AisWebConfig] [nvarchar](127) NOT NULL,
  [StoreReceivedSentences] [bit] NOT NULL,
  [StoreSentMessages] [bit] NOT NULL,
  [StoreUnsentMessages] [bit] NOT NULL,
  CONSTRAINT [PK_AisTransceiverConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[AisTransceiverConfiguration]
  ADD CONSTRAINT [UNQ_AisTransceiverConfiguration_AisTransceiver_Timestamp] UNIQUE([AisTransceiver],[Timestamp])
go

CREATE INDEX [IDX_AisTransceiverConfiguration_Timestamp] ON [dbo].[AisTransceiverConfiguration]([Timestamp])
go

/*
 * AisTransceiverRawMessage
 *
 */
CREATE TABLE [dbo].[AisTransceiverRawMessage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [AisTransceiver] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [IsSent] [bit] NOT NULL,
  [Message] [nvarchar](100) NOT NULL,
  CONSTRAINT [PK_AisTransceiverRawMessage] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisTransceiverRawMessage_AisTransceiver_Timestamp] ON [dbo].[AisTransceiverRawMessage]([AisTransceiver],[Timestamp])
go

CREATE INDEX [IDX_AisTransceiverRawMessage_Timestamp] ON [dbo].[AisTransceiverRawMessage]([Timestamp])
go

/*
 * AisTransceiverRawSentence
 *
 */
CREATE TABLE [dbo].[AisTransceiverRawSentence]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [AisTransceiver] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Sentence] [nvarchar](1024) NOT NULL,
  CONSTRAINT [PK_AisTransceiverRawSentence] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisTransceiverRawSentence_AisTransceiver_Timestamp] ON [dbo].[AisTransceiverRawSentence]([AisTransceiver],[Timestamp])
go

CREATE INDEX [IDX_AisTransceiverRawSentence_Timestamp] ON [dbo].[AisTransceiverRawSentence]([Timestamp])
go

/*
 * AlarmStateChange
 *
 */
CREATE TABLE [dbo].[AlarmStateChange]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Alarm] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [State] [int] NOT NULL,
  CONSTRAINT [PK_AlarmStateChange] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[AlarmStateChange]
  ADD CONSTRAINT [UNQ_AlarmStateChange_Alarm_Timestamp] UNIQUE([Alarm],[Timestamp])
go

CREATE INDEX [IDX_AlarmStateChange_Timestamp] ON [dbo].[AlarmStateChange]([Timestamp])
go

/*
 * BaseStationType
 *
 */
CREATE TABLE [dbo].[BaseStationType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [PK_BaseStationType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[BaseStationType]
  ADD CONSTRAINT [UNQ_BaseStationType_Name] UNIQUE([Name])
go

/*
 * BinaryTimeseriesValue
 *
 */
CREATE TABLE [dbo].[BinaryTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [varbinary](max) NOT NULL,
  CONSTRAINT [PK_BinaryTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[BinaryTimeseriesValue]
  ADD CONSTRAINT [UNQ_BinaryTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_BinaryTimeseriesValue_Timestamp] ON [dbo].[BinaryTimeseriesValue]([Timestamp])
go

/*
 * Bookmark
 *
 */
CREATE TABLE [dbo].[Bookmark]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [View] [uniqueidentifier] NOT NULL,
  [Name] [nvarchar](100) NOT NULL,
  [Timestamp] [bigint] NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [ZoomLevel] [float](53) NOT NULL,
  CONSTRAINT [PK_Bookmark] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Bookmark_View] ON [dbo].[Bookmark]([View])
go

/*
 * BooleanTimeseriesValue
 *
 */
CREATE TABLE [dbo].[BooleanTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [bit] NULL,
  CONSTRAINT [PK_BooleanTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[BooleanTimeseriesValue]
  ADD CONSTRAINT [UNQ_BooleanTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_BooleanTimeseriesValue_Timestamp] ON [dbo].[BooleanTimeseriesValue]([Timestamp])
go

/*
 * ByteTimeseriesValue
 *
 */
CREATE TABLE [dbo].[ByteTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [tinyint] NULL,
  CONSTRAINT [PK_ByteTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[ByteTimeseriesValue]
  ADD CONSTRAINT [UNQ_ByteTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_ByteTimeseriesValue_Timestamp] ON [dbo].[ByteTimeseriesValue]([Timestamp])
go

/*
 * CameraCommand
 *
 */
CREATE TABLE [dbo].[CameraCommand]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between CameraCommand
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Camera] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DeviceCommandSourceType] [int] NOT NULL,
  [DeviceCommandSourceId] [uniqueidentifier] NOT NULL,
  [Reply] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_CameraCommand_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_CameraCommand] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_CameraCommand_Camera_Timestamp] ON [dbo].[CameraCommand]([Camera],[Timestamp])
go

CREATE INDEX [IDX_CameraCommand_Timestamp] ON [dbo].[CameraCommand]([Timestamp])
go

CREATE INDEX [IDX_CameraCommand_Reply] ON [dbo].[CameraCommand]([Reply])
go

/*
 * CameraCommandAbsoluteMove
 *
 * The CameraCommandAbsoluteMove entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandAbsoluteMove].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandAbsoluteMove]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [PositionPanTiltMode] [int] NOT NULL,
  [PanAngle] [float](53) NULL,
  [TiltAngle] [float](53) NULL,
  [PositionFocalLengthMode] [int] NOT NULL,
  [FocalLength] [float](53) NULL,
  [SpeedPanTiltMode] [int] NOT NULL,
  [PanSpeed] [float](53) NULL,
  [TiltSpeed] [float](53) NULL,
  [SpeedFocalLengthMode] [int] NOT NULL,
  [ZoomSpeed] [float](53) NULL,
  CONSTRAINT [FK_CameraCommandAbsoluteMove_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandAbsoluteMove] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandAdjustPanTiltZoom
 *
 * The CameraCommandAdjustPanTiltZoom entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandAdjustPanTiltZoom].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandAdjustPanTiltZoom]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [X] [float](53) NULL,
  [Y] [float](53) NULL,
  [Z] [float](53) NULL,
  CONSTRAINT [FK_CameraCommandAdjustPanTiltZoom_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandAdjustPanTiltZoom] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandContinuousMove
 *
 * The CameraCommandContinuousMove entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandContinuousMove].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandContinuousMove]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Normalized] [bit] NOT NULL,
  [PanVelocity] [float](53) NULL,
  [TiltVelocity] [float](53) NULL,
  [ZoomVelocity] [float](53) NULL,
  [Duration] [bigint] NULL,
  CONSTRAINT [FK_CameraCommandContinuousMove_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandContinuousMove] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandGeoMove
 *
 * The CameraCommandGeoMove entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandGeoMove].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandGeoMove]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Altitude] [float](53) NULL,
  [ViewportWidth] [float](53) NULL,
  [ViewportHeight] [float](53) NULL,
  CONSTRAINT [FK_CameraCommandGeoMove_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandGeoMove] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandRelativeMove
 *
 * The CameraCommandRelativeMove entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandRelativeMove].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandRelativeMove]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Normalized] [bit] NOT NULL,
  [PanAngle] [float](53) NULL,
  [TiltAngle] [float](53) NULL,
  [FocalLength] [float](53) NULL,
  [PanSpeed] [float](53) NULL,
  [TiltSpeed] [float](53) NULL,
  [ZoomSpeed] [float](53) NULL,
  CONSTRAINT [FK_CameraCommandRelativeMove_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandRelativeMove] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandReleasePTZOwnership
 *
 * The CameraCommandReleasePTZOwnership entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandReleasePTZOwnership].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandReleasePTZOwnership]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_CameraCommandReleasePTZOwnership_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandReleasePTZOwnership] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandRequestPTZOwnership
 *
 * The CameraCommandRequestPTZOwnership entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandRequestPTZOwnership].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandRequestPTZOwnership]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_CameraCommandRequestPTZOwnership_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandRequestPTZOwnership] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandSetAutoFocus
 *
 * The CameraCommandSetAutoFocus entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandSetAutoFocus].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandSetAutoFocus]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Enabled] [bit] NOT NULL,
  CONSTRAINT [FK_CameraCommandSetAutoFocus_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandSetAutoFocus] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandSetBlackAndWhite
 *
 * The CameraCommandSetBlackAndWhite entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandSetBlackAndWhite].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandSetBlackAndWhite]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Enabled] [bit] NOT NULL,
  CONSTRAINT [FK_CameraCommandSetBlackAndWhite_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandSetBlackAndWhite] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandSetFollowed
 *
 * The CameraCommandSetFollowed entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandSetFollowed].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandSetFollowed]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [TrackId] [uniqueidentifier] NOT NULL,
  [Reason] [int] NOT NULL,
  CONSTRAINT [FK_CameraCommandSetFollowed_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandSetFollowed] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandSetInfraRedLamp
 *
 * The CameraCommandSetInfraRedLamp entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandSetInfraRedLamp].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandSetInfraRedLamp]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Enabled] [bit] NOT NULL,
  CONSTRAINT [FK_CameraCommandSetInfraRedLamp_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandSetInfraRedLamp] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandSetWasher
 *
 * The CameraCommandSetWasher entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandSetWasher].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandSetWasher]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Enabled] [bit] NOT NULL,
  CONSTRAINT [FK_CameraCommandSetWasher_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandSetWasher] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandSetWiper
 *
 * The CameraCommandSetWiper entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandSetWiper].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandSetWiper]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Enabled] [bit] NOT NULL,
  CONSTRAINT [FK_CameraCommandSetWiper_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandSetWiper] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandStop
 *
 * The CameraCommandStop entity a descendant of the CameraCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraCommandStop].[Id] field and the
 * [dbo].[CameraCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraCommandStop]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [PanTilt] [bit] NOT NULL,
  [Zoom] [bit] NOT NULL,
  CONSTRAINT [FK_CameraCommandStop_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CameraCommand]([Id]),
  CONSTRAINT [PK_CameraCommandStop] PRIMARY KEY([Id])
)
go

/*
 * CameraCommandReply
 *
 */
CREATE TABLE [dbo].[CameraCommandReply]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Camera] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Command] [uniqueidentifier] NOT NULL,
  [Status] [int] NOT NULL,
  [Message] [nvarchar](max) NOT NULL,
  [PanAngle] [float](53) NOT NULL,
  [TiltAngle] [float](53) NOT NULL,
  [FocalLength] [float](53) NOT NULL,
  CONSTRAINT [PK_CameraCommandReply] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_CameraCommandReply_Camera_Timestamp] ON [dbo].[CameraCommandReply]([Camera],[Timestamp])
go

CREATE INDEX [IDX_CameraCommandReply_Timestamp] ON [dbo].[CameraCommandReply]([Timestamp])
go

ALTER TABLE [dbo].[CameraCommandReply]
  ADD CONSTRAINT [UNQ_CameraCommandReply_Command] UNIQUE([Command])
go

/*
 * CameraConfiguration
 *
 */
CREATE TABLE [dbo].[CameraConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Camera] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [CameraControlProtocol] [int] NOT NULL,
  [CameraAddress] [nvarchar](127) NOT NULL,
  [CameraPort] [int] NOT NULL,
  [CameraControlAddress] [nvarchar](127) NOT NULL,
  [CameraControlPort] [int] NOT NULL,
  [CameraUserName] [nvarchar](127) NOT NULL,
  [CameraPassword] [nvarchar](127) NOT NULL,
  [UseRtspUriOverride] [bit] NOT NULL,
  [RtspUriOverride] [nvarchar](127) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Altitude] [float](53) NOT NULL,
  [UseRelativePosition] [bit] NOT NULL,
  [AzimuthFromGPS] [float](53) NOT NULL,
  [DistanceFromGPS] [float](53) NOT NULL,
  [PanTiltMode] [int] NOT NULL,
  [MinTiltAngle] [float](53) NOT NULL,
  [MaxTiltAngle] [float](53) NOT NULL,
  [MinTiltScaleAngle] [float](53) NOT NULL,
  [MaxTiltScaleAngle] [float](53) NOT NULL,
  [UseReverseTiltAngle] [bit] NOT NULL,
  [UseReverseNormalizedTiltAngle] [bit] NOT NULL,
  [MinTiltVelocity] [float](53) NOT NULL,
  [MaxTiltVelocity] [float](53) NOT NULL,
  [MinTiltSpeed] [float](53) NOT NULL,
  [MaxTiltSpeed] [float](53) NOT NULL,
  [MinPanAngle] [float](53) NOT NULL,
  [MaxPanAngle] [float](53) NOT NULL,
  [MinPanScaleAngle] [float](53) NOT NULL,
  [MaxPanScaleAngle] [float](53) NOT NULL,
  [UseReversePanAngle] [bit] NOT NULL,
  [UseReverseNormalizedPanAngle] [bit] NOT NULL,
  [MinPanVelocity] [float](53) NOT NULL,
  [MaxPanVelocity] [float](53) NOT NULL,
  [MinPanSpeed] [float](53) NOT NULL,
  [MaxPanSpeed] [float](53) NOT NULL,
  [FocalLengthMode] [int] NOT NULL,
  [MinFocalLength] [float](53) NOT NULL,
  [MaxFocalLength] [float](53) NOT NULL,
  [MinFocalLengthScale] [float](53) NOT NULL,
  [MaxFocalLengthScale] [float](53) NOT NULL,
  [MinZoomVelocity] [float](53) NOT NULL,
  [MaxZoomVelocity] [float](53) NOT NULL,
  [MinZoomSpeed] [float](53) NOT NULL,
  [MaxZoomSpeed] [float](53) NOT NULL,
  [ImageSensorWidth] [float](53) NOT NULL,
  [ImageSensorHeight] [float](53) NOT NULL,
  [HomePanAngle] [float](53) NOT NULL,
  [HomeTiltAngle] [float](53) NOT NULL,
  [HomeFocalLength] [float](53) NOT NULL,
  [PanOffset] [float](53) NOT NULL,
  [TiltOffset] [float](53) NOT NULL,
  [AimAltitude] [float](53) NOT NULL,
  [MinimumTargetWidth] [float](53) NOT NULL,
  [TargetLockTimeout] [bigint] NOT NULL,
  [UpdateStatusInterval] [bigint] NOT NULL,
  [ReadTimeout] [bigint] NOT NULL,
  [MoveCommandStatusDelay] [bigint] NOT NULL,
  [PtzProfileName] [nvarchar](127) NOT NULL,
  [PtzConfigurationToken] [nvarchar](127) NOT NULL,
  [VideoSourceToken] [nvarchar](127) NOT NULL,
  CONSTRAINT [PK_CameraConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[CameraConfiguration]
  ADD CONSTRAINT [UNQ_CameraConfiguration_Camera_Timestamp] UNIQUE([Camera],[Timestamp])
go

CREATE INDEX [IDX_CameraConfiguration_Timestamp] ON [dbo].[CameraConfiguration]([Timestamp])
go

/*
 * CameraPanCalibration
 *
 */
CREATE TABLE [dbo].[CameraPanCalibration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Camera] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  CONSTRAINT [PK_CameraPanCalibration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[CameraPanCalibration]
  ADD CONSTRAINT [UNQ_CameraPanCalibration_Camera_Timestamp] UNIQUE([Camera],[Timestamp])
go

CREATE INDEX [IDX_CameraPanCalibration_Timestamp] ON [dbo].[CameraPanCalibration]([Timestamp])
go

/*
 * CameraPanCalibrationValue
 *
 */
CREATE TABLE [dbo].[CameraPanCalibrationValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [PanCalibration] [uniqueidentifier] NOT NULL,
  [PanAngle] [float](53) NOT NULL,
  [PanOffset] [float](53) NOT NULL,
  CONSTRAINT [PK_CameraPanCalibrationValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[CameraPanCalibrationValue]
  ADD CONSTRAINT [UNQ_CameraPanCalibrationValue_PanCalibration_PanAngle] UNIQUE([PanCalibration],[PanAngle])
go

/*
 * CameraStatus
 *
 */
CREATE TABLE [dbo].[CameraStatus]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Camera] [uniqueidentifier] NOT NULL,
  [Track] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [PositionPanTiltMode] [int] NOT NULL,
  [PanAngle] [float](53) NOT NULL,
  [TiltAngle] [float](53) NOT NULL,
  [PositionFocalLengthMode] [int] NOT NULL,
  [FocalLength] [float](53) NOT NULL,
  [PanTiltMoveStatus] [int] NOT NULL,
  [ZoomMoveStatus] [int] NOT NULL,
  [VelocityPanTiltMode] [int] NOT NULL,
  [PanVelocity] [float](53) NULL,
  [TiltVelocity] [float](53) NULL,
  [VelocityFocalLengthMode] [int] NOT NULL,
  [ZoomVelocity] [float](53) NULL,
  [ActiveFeatures] [int] NOT NULL,
  [Error] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_CameraStatus] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[CameraStatus]
  ADD CONSTRAINT [UNQ_CameraStatus_Camera_Timestamp] UNIQUE([Camera],[Timestamp])
go

ALTER TABLE [dbo].[CameraStatus]
  ADD CONSTRAINT [UNQ_CameraStatus_Track_Timestamp] UNIQUE([Track],[Timestamp])
go

CREATE INDEX [IDX_CameraStatus_Timestamp] ON [dbo].[CameraStatus]([Timestamp])
go

/*
 * CameraTiltCalibration
 *
 */
CREATE TABLE [dbo].[CameraTiltCalibration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Camera] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  CONSTRAINT [PK_CameraTiltCalibration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[CameraTiltCalibration]
  ADD CONSTRAINT [UNQ_CameraTiltCalibration_Camera_Timestamp] UNIQUE([Camera],[Timestamp])
go

CREATE INDEX [IDX_CameraTiltCalibration_Timestamp] ON [dbo].[CameraTiltCalibration]([Timestamp])
go

/*
 * CameraTiltCalibrationValue
 *
 */
CREATE TABLE [dbo].[CameraTiltCalibrationValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [TiltCalibration] [uniqueidentifier] NOT NULL,
  [PanAngle] [float](53) NOT NULL,
  [TiltOffset] [float](53) NOT NULL,
  CONSTRAINT [PK_CameraTiltCalibrationValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[CameraTiltCalibrationValue]
  ADD CONSTRAINT [UNQ_CameraTiltCalibrationValue_TiltCalibration_PanAngle] UNIQUE([TiltCalibration],[PanAngle])
go

/*
 * CameraZoomCalibration
 *
 */
CREATE TABLE [dbo].[CameraZoomCalibration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Camera] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  CONSTRAINT [PK_CameraZoomCalibration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[CameraZoomCalibration]
  ADD CONSTRAINT [UNQ_CameraZoomCalibration_Camera_Timestamp] UNIQUE([Camera],[Timestamp])
go

CREATE INDEX [IDX_CameraZoomCalibration_Timestamp] ON [dbo].[CameraZoomCalibration]([Timestamp])
go

/*
 * CameraZoomCalibrationValue
 *
 */
CREATE TABLE [dbo].[CameraZoomCalibrationValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [ZoomCalibration] [uniqueidentifier] NOT NULL,
  [FocalLength] [float](53) NOT NULL,
  [FocalLengthOffset] [float](53) NOT NULL,
  CONSTRAINT [PK_CameraZoomCalibrationValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[CameraZoomCalibrationValue]
  ADD CONSTRAINT [UNQ_CameraZoomCalibrationValue_ZoomCalibration_FocalLength] UNIQUE([ZoomCalibration],[FocalLength])
go

/*
 * CatalogElement
 *
 */
CREATE TABLE [dbo].[CatalogElement]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between CatalogElement
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Catalog] [uniqueidentifier] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_CatalogElement_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_CatalogElement] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[CatalogElement]
  ADD CONSTRAINT [UNQ_CatalogElement_Catalog_Name] UNIQUE([Catalog],[Name])
go

/*
 * Catalog
 *
 * The Catalog entity a descendant of the CatalogElement entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Catalog].[Id] field and the
 * [dbo].[CatalogElement].[Id] field.
 *
 */
CREATE TABLE [dbo].[Catalog]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_Catalog_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CatalogElement]([Id]),
  CONSTRAINT [PK_Catalog] PRIMARY KEY([Id])
)
go

/*
 * Element
 *
 * The Element entity a descendant of the CatalogElement entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Element].[Id] field and the
 * [dbo].[CatalogElement].[Id] field.
 *
 */
CREATE TABLE [dbo].[Element]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [ElementType] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Element_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[CatalogElement]([Id]),
  CONSTRAINT [PK_Element] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Element_ElementType] ON [dbo].[Element]([ElementType])
go

/*
 * CollectionInfo
 *
 */
CREATE TABLE [dbo].[CollectionInfo]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Count] [bigint] NOT NULL,
  CONSTRAINT [PK_CollectionInfo] PRIMARY KEY([Id])
)
go

/*
 * Country
 *
 */
CREATE TABLE [dbo].[Country]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Code] [int] NOT NULL,
  [Alpha2] [nvarchar](2) NOT NULL,
  [Alpha3] [nvarchar](3) NOT NULL,
  CONSTRAINT [PK_Country] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Country]
  ADD CONSTRAINT [UNQ_Country_Name] UNIQUE([Name])
go

ALTER TABLE [dbo].[Country]
  ADD CONSTRAINT [UNQ_Country_Code] UNIQUE([Code])
go

ALTER TABLE [dbo].[Country]
  ADD CONSTRAINT [UNQ_Country_Alpha2] UNIQUE([Alpha2])
go

ALTER TABLE [dbo].[Country]
  ADD CONSTRAINT [UNQ_Country_Alpha3] UNIQUE([Alpha3])
go

/*
 * CursorInfo
 *
 */
CREATE TABLE [dbo].[CursorInfo]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [TypeCode] [int] NOT NULL,
  CONSTRAINT [PK_CursorInfo] PRIMARY KEY([Id])
)
go

/*
 * DateTimeTimeseriesValue
 *
 */
CREATE TABLE [dbo].[DateTimeTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [bigint] NULL,
  CONSTRAINT [PK_DateTimeTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[DateTimeTimeseriesValue]
  ADD CONSTRAINT [UNQ_DateTimeTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_DateTimeTimeseriesValue_Timestamp] ON [dbo].[DateTimeTimeseriesValue]([Timestamp])
go

/*
 * DeviceHost
 *
 */
CREATE TABLE [dbo].[DeviceHost]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * A DeviceHost is specifies the configuration of set of devices that are configured for a specific host computer. 
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * A DeviceHost is specifies the configuration of set of devices that are configured for a specific host computer. 
   */
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [PK_DeviceHost] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[DeviceHost]
  ADD CONSTRAINT [UNQ_DeviceHost_Name] UNIQUE([Name])
go

/*
 * DeviceHostConfiguration
 *
 */
CREATE TABLE [dbo].[DeviceHostConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Host] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Hostname] [nvarchar](127) NOT NULL,
  [Port] [int] NOT NULL,
  [QueueName] [nvarchar](100) NOT NULL,
  CONSTRAINT [PK_DeviceHostConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[DeviceHostConfiguration]
  ADD CONSTRAINT [UNQ_DeviceHostConfiguration_Host_Timestamp] UNIQUE([Host],[Timestamp])
go

CREATE INDEX [IDX_DeviceHostConfiguration_Timestamp] ON [dbo].[DeviceHostConfiguration]([Timestamp])
go

/*
 * DeviceType
 *
 */
CREATE TABLE [dbo].[DeviceType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between DeviceType
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [AssemblyName] [nvarchar](100) NOT NULL,
  [ClassName] [nvarchar](100) NOT NULL,
  [ProxyAssemblyName] [nvarchar](100) NOT NULL,
  [ProxyClassName] [nvarchar](100) NOT NULL,
  CONSTRAINT [FK_DeviceType_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_DeviceType] PRIMARY KEY([Id])
)
go

/*
 * AisTransceiverType
 *
 * The AisTransceiverType entity a descendant of the DeviceType entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisTransceiverType].[Id] field and the
 * [dbo].[DeviceType].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisTransceiverType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_AisTransceiverType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DeviceType]([Id]),
  CONSTRAINT [PK_AisTransceiverType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[AisTransceiverType]
  ADD CONSTRAINT [UNQ_AisTransceiverType_Name] UNIQUE([Name])
go

/*
 * CameraType
 *
 * The CameraType entity a descendant of the DeviceType entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CameraType].[Id] field and the
 * [dbo].[DeviceType].[Id] field.
 *
 */
CREATE TABLE [dbo].[CameraType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [CameraFeatures] [int] NOT NULL,
  CONSTRAINT [FK_CameraType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DeviceType]([Id]),
  CONSTRAINT [PK_CameraType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[CameraType]
  ADD CONSTRAINT [UNQ_CameraType_Name] UNIQUE([Name])
go

/*
 * GNSSDeviceType
 *
 * The GNSSDeviceType entity a descendant of the DeviceType entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GNSSDeviceType].[Id] field and the
 * [dbo].[DeviceType].[Id] field.
 *
 */
CREATE TABLE [dbo].[GNSSDeviceType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_GNSSDeviceType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DeviceType]([Id]),
  CONSTRAINT [PK_GNSSDeviceType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GNSSDeviceType]
  ADD CONSTRAINT [UNQ_GNSSDeviceType_Name] UNIQUE([Name])
go

/*
 * GyroDeviceType
 *
 * The GyroDeviceType entity a descendant of the DeviceType entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GyroDeviceType].[Id] field and the
 * [dbo].[DeviceType].[Id] field.
 *
 */
CREATE TABLE [dbo].[GyroDeviceType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_GyroDeviceType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DeviceType]([Id]),
  CONSTRAINT [PK_GyroDeviceType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GyroDeviceType]
  ADD CONSTRAINT [UNQ_GyroDeviceType_Name] UNIQUE([Name])
go

/*
 * LineInputDeviceType
 *
 * The LineInputDeviceType entity a descendant of the DeviceType entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[LineInputDeviceType].[Id] field and the
 * [dbo].[DeviceType].[Id] field.
 *
 */
CREATE TABLE [dbo].[LineInputDeviceType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_LineInputDeviceType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DeviceType]([Id]),
  CONSTRAINT [PK_LineInputDeviceType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[LineInputDeviceType]
  ADD CONSTRAINT [UNQ_LineInputDeviceType_Name] UNIQUE([Name])
go

/*
 * OilspillDetectorType
 *
 * The OilspillDetectorType entity a descendant of the DeviceType entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[OilspillDetectorType].[Id] field and the
 * [dbo].[DeviceType].[Id] field.
 *
 */
CREATE TABLE [dbo].[OilspillDetectorType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_OilspillDetectorType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DeviceType]([Id]),
  CONSTRAINT [PK_OilspillDetectorType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[OilspillDetectorType]
  ADD CONSTRAINT [UNQ_OilspillDetectorType_Name] UNIQUE([Name])
go

/*
 * RadarType
 *
 * The RadarType entity a descendant of the DeviceType entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarType].[Id] field and the
 * [dbo].[DeviceType].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [PulseShortMinusValue] [int] NULL,
  [PulseShortMinusDisplayText] [nvarchar](50) NOT NULL,
  [PulseShortValue] [int] NULL,
  [PulseShortDisplayText] [nvarchar](50) NOT NULL,
  [PulseShortPlusValue] [int] NULL,
  [PulseShortPlusDisplayText] [nvarchar](50) NOT NULL,
  [PulseMediumMinusValue] [int] NULL,
  [PulseMediumMinusDisplayText] [nvarchar](50) NOT NULL,
  [PulseMediumValue] [int] NULL,
  [PulseMediumDisplayText] [nvarchar](50) NOT NULL,
  [PulseMediumPlusValue] [int] NULL,
  [PulseMediumPlusDisplayText] [nvarchar](50) NOT NULL,
  [PulseLongMinusValue] [int] NULL,
  [PulseLongMinusDisplayText] [nvarchar](50) NOT NULL,
  [PulseLongValue] [int] NULL,
  [PulseLongDisplayText] [nvarchar](50) NOT NULL,
  [PulseLongPlusValue] [int] NULL,
  [PulseLongPlusDisplayText] [nvarchar](50) NOT NULL,
  CONSTRAINT [FK_RadarType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DeviceType]([Id]),
  CONSTRAINT [PK_RadarType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[RadarType]
  ADD CONSTRAINT [UNQ_RadarType_Name] UNIQUE([Name])
go

/*
 * RadioType
 *
 * The RadioType entity a descendant of the DeviceType entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadioType].[Id] field and the
 * [dbo].[DeviceType].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadioType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_RadioType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DeviceType]([Id]),
  CONSTRAINT [PK_RadioType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[RadioType]
  ADD CONSTRAINT [UNQ_RadioType_Name] UNIQUE([Name])
go

/*
 * RadomeType
 *
 * The RadomeType entity a descendant of the DeviceType entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadomeType].[Id] field and the
 * [dbo].[DeviceType].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadomeType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_RadomeType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DeviceType]([Id]),
  CONSTRAINT [PK_RadomeType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[RadomeType]
  ADD CONSTRAINT [UNQ_RadomeType_Name] UNIQUE([Name])
go

/*
 * WeatherStationType
 *
 * The WeatherStationType entity a descendant of the DeviceType entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[WeatherStationType].[Id] field and the
 * [dbo].[DeviceType].[Id] field.
 *
 */
CREATE TABLE [dbo].[WeatherStationType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_WeatherStationType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DeviceType]([Id]),
  CONSTRAINT [PK_WeatherStationType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[WeatherStationType]
  ADD CONSTRAINT [UNQ_WeatherStationType_Name] UNIQUE([Name])
go

/*
 * DoubleTimeseriesValue
 *
 */
CREATE TABLE [dbo].[DoubleTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [float](53) NULL,
  CONSTRAINT [PK_DoubleTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[DoubleTimeseriesValue]
  ADD CONSTRAINT [UNQ_DoubleTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_DoubleTimeseriesValue_Timestamp] ON [dbo].[DoubleTimeseriesValue]([Timestamp])
go

/*
 * FacilityType
 *
 */
CREATE TABLE [dbo].[FacilityType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [PK_FacilityType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[FacilityType]
  ADD CONSTRAINT [UNQ_FacilityType_Name] UNIQUE([Name])
go

/*
 * GeoPosition2DTimeseriesValue
 *
 */
CREATE TABLE [dbo].[GeoPosition2DTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Latitude] [float](53) NULL,
  [Longitude] [float](53) NULL,
  CONSTRAINT [PK_GeoPosition2DTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GeoPosition2DTimeseriesValue]
  ADD CONSTRAINT [UNQ_GeoPosition2DTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_GeoPosition2DTimeseriesValue_Timestamp] ON [dbo].[GeoPosition2DTimeseriesValue]([Timestamp])
go

/*
 * GeoPosition3DTimeseriesValue
 *
 */
CREATE TABLE [dbo].[GeoPosition3DTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Latitude] [float](53) NULL,
  [Longitude] [float](53) NULL,
  [Altitude] [float](53) NULL,
  CONSTRAINT [PK_GeoPosition3DTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GeoPosition3DTimeseriesValue]
  ADD CONSTRAINT [UNQ_GeoPosition3DTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_GeoPosition3DTimeseriesValue_Timestamp] ON [dbo].[GeoPosition3DTimeseriesValue]([Timestamp])
go

/*
 * GNSSDeviceCommand
 *
 */
CREATE TABLE [dbo].[GNSSDeviceCommand]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [GNSSDevice] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DeviceCommandSourceType] [int] NOT NULL,
  [DeviceCommandSourceId] [uniqueidentifier] NOT NULL,
  [Reply] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_GNSSDeviceCommand] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_GNSSDeviceCommand_GNSSDevice_Timestamp] ON [dbo].[GNSSDeviceCommand]([GNSSDevice],[Timestamp])
go

CREATE INDEX [IDX_GNSSDeviceCommand_Timestamp] ON [dbo].[GNSSDeviceCommand]([Timestamp])
go

CREATE INDEX [IDX_GNSSDeviceCommand_Reply] ON [dbo].[GNSSDeviceCommand]([Reply])
go

/*
 * GNSSDeviceCommandReply
 *
 */
CREATE TABLE [dbo].[GNSSDeviceCommandReply]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [GNSSDevice] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Command] [uniqueidentifier] NOT NULL,
  [Status] [int] NOT NULL,
  [Message] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_GNSSDeviceCommandReply] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_GNSSDeviceCommandReply_GNSSDevice_Timestamp] ON [dbo].[GNSSDeviceCommandReply]([GNSSDevice],[Timestamp])
go

CREATE INDEX [IDX_GNSSDeviceCommandReply_Timestamp] ON [dbo].[GNSSDeviceCommandReply]([Timestamp])
go

ALTER TABLE [dbo].[GNSSDeviceCommandReply]
  ADD CONSTRAINT [UNQ_GNSSDeviceCommandReply_Command] UNIQUE([Command])
go

/*
 * GNSSDeviceConfiguration
 *
 */
CREATE TABLE [dbo].[GNSSDeviceConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [GNSSDevice] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DefaultLatitude] [float](53) NOT NULL,
  [DefaultLongitude] [float](53) NOT NULL,
  [DefaultAltitude] [float](53) NOT NULL,
  [LatitudeOffset] [float](53) NOT NULL,
  [LongitudeOffset] [float](53) NOT NULL,
  [AltitudeOffset] [float](53) NOT NULL,
  CONSTRAINT [PK_GNSSDeviceConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GNSSDeviceConfiguration]
  ADD CONSTRAINT [UNQ_GNSSDeviceConfiguration_GNSSDevice_Timestamp] UNIQUE([GNSSDevice],[Timestamp])
go

CREATE INDEX [IDX_GNSSDeviceConfiguration_Timestamp] ON [dbo].[GNSSDeviceConfiguration]([Timestamp])
go

/*
 * GuidTimeseriesValue
 *
 */
CREATE TABLE [dbo].[GuidTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [uniqueidentifier] NULL,
  CONSTRAINT [PK_GuidTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GuidTimeseriesValue]
  ADD CONSTRAINT [UNQ_GuidTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_GuidTimeseriesValue_Timestamp] ON [dbo].[GuidTimeseriesValue]([Timestamp])
go

/*
 * GyroDeviceCommand
 *
 */
CREATE TABLE [dbo].[GyroDeviceCommand]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [GyroDevice] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DeviceCommandSourceType] [int] NOT NULL,
  [DeviceCommandSourceId] [uniqueidentifier] NOT NULL,
  [Reply] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_GyroDeviceCommand] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_GyroDeviceCommand_GyroDevice_Timestamp] ON [dbo].[GyroDeviceCommand]([GyroDevice],[Timestamp])
go

CREATE INDEX [IDX_GyroDeviceCommand_Timestamp] ON [dbo].[GyroDeviceCommand]([Timestamp])
go

CREATE INDEX [IDX_GyroDeviceCommand_Reply] ON [dbo].[GyroDeviceCommand]([Reply])
go

/*
 * GyroDeviceCommandReply
 *
 */
CREATE TABLE [dbo].[GyroDeviceCommandReply]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [GyroDevice] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Command] [uniqueidentifier] NOT NULL,
  [Status] [int] NOT NULL,
  [Message] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_GyroDeviceCommandReply] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_GyroDeviceCommandReply_GyroDevice_Timestamp] ON [dbo].[GyroDeviceCommandReply]([GyroDevice],[Timestamp])
go

CREATE INDEX [IDX_GyroDeviceCommandReply_Timestamp] ON [dbo].[GyroDeviceCommandReply]([Timestamp])
go

ALTER TABLE [dbo].[GyroDeviceCommandReply]
  ADD CONSTRAINT [UNQ_GyroDeviceCommandReply_Command] UNIQUE([Command])
go

/*
 * GyroDeviceConfiguration
 *
 */
CREATE TABLE [dbo].[GyroDeviceConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [GyroDevice] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DefaultHeadingTrueNorth] [float](53) NOT NULL,
  [DefaultMagneticTrueNorth] [float](53) NOT NULL,
  [HeadingTrueNorthOffset] [float](53) NOT NULL,
  [HeadingMagneticNorthOffset] [float](53) NOT NULL,
  [PitchTransducerName] [nvarchar](64) NOT NULL,
  [RollTransducerName] [nvarchar](64) NOT NULL,
  CONSTRAINT [PK_GyroDeviceConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GyroDeviceConfiguration]
  ADD CONSTRAINT [UNQ_GyroDeviceConfiguration_GyroDevice_Timestamp] UNIQUE([GyroDevice],[Timestamp])
go

CREATE INDEX [IDX_GyroDeviceConfiguration_Timestamp] ON [dbo].[GyroDeviceConfiguration]([Timestamp])
go

/*
 * Identity
 *
 */
CREATE TABLE [dbo].[Identity]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between Identity
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  /*
   * Identity base
   */
  [RowVersion] [bigint] NOT NULL,
  CONSTRAINT [FK_Identity_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_Identity] PRIMARY KEY([Id])
)
go

/*
 * Callsign
 *
 * The Callsign entity a descendant of the Identity entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Callsign].[Id] field and the
 * [dbo].[Identity].[Id] field.
 *
 */
CREATE TABLE [dbo].[Callsign]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Identity base
   */
  [Identifier] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_Callsign_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Identity]([Id]),
  CONSTRAINT [PK_Callsign] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Callsign]
  ADD CONSTRAINT [UNQ_Callsign_Identifier] UNIQUE([Identifier])
go

/*
 * InternationalMaritimeOrganizationNumber
 *
 * The InternationalMaritimeOrganizationNumber entity a descendant of the Identity entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[InternationalMaritimeOrganizationNumber].[Id] field and the
 * [dbo].[Identity].[Id] field.
 *
 */
CREATE TABLE [dbo].[InternationalMaritimeOrganizationNumber]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Identity base
   */
  [Identifier] [bigint] NOT NULL,
  CONSTRAINT [FK_InternationalMaritimeOrganizationNumber_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Identity]([Id]),
  CONSTRAINT [PK_InternationalMaritimeOrganizationNumber] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[InternationalMaritimeOrganizationNumber]
  ADD CONSTRAINT [UNQ_InternationalMaritimeOrganizationNumber_Identifier] UNIQUE([Identifier])
go

/*
 * MaritimeMobileServiceIdentity
 *
 * The MaritimeMobileServiceIdentity entity a descendant of the Identity entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[MaritimeMobileServiceIdentity].[Id] field and the
 * [dbo].[Identity].[Id] field.
 *
 */
CREATE TABLE [dbo].[MaritimeMobileServiceIdentity]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Identity base
   */
  [Identifier] [bigint] NOT NULL,
  CONSTRAINT [FK_MaritimeMobileServiceIdentity_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Identity]([Id]),
  CONSTRAINT [PK_MaritimeMobileServiceIdentity] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[MaritimeMobileServiceIdentity]
  ADD CONSTRAINT [UNQ_MaritimeMobileServiceIdentity_Identifier] UNIQUE([Identifier])
go

/*
 * Name
 *
 * The Name entity a descendant of the Identity entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Name].[Id] field and the
 * [dbo].[Identity].[Id] field.
 *
 */
CREATE TABLE [dbo].[Name]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Identity base
   */
  [Text] [nvarchar](100) NOT NULL,
  CONSTRAINT [FK_Name_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Identity]([Id]),
  CONSTRAINT [PK_Name] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Name]
  ADD CONSTRAINT [UNQ_Name_Text] UNIQUE([Text])
go

/*
 * Int16TimeseriesValue
 *
 */
CREATE TABLE [dbo].[Int16TimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [smallint] NULL,
  CONSTRAINT [PK_Int16TimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Int16TimeseriesValue]
  ADD CONSTRAINT [UNQ_Int16TimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_Int16TimeseriesValue_Timestamp] ON [dbo].[Int16TimeseriesValue]([Timestamp])
go

/*
 * Int32TimeseriesValue
 *
 */
CREATE TABLE [dbo].[Int32TimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [int] NULL,
  CONSTRAINT [PK_Int32TimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Int32TimeseriesValue]
  ADD CONSTRAINT [UNQ_Int32TimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_Int32TimeseriesValue_Timestamp] ON [dbo].[Int32TimeseriesValue]([Timestamp])
go

/*
 * Int64TimeseriesValue
 *
 */
CREATE TABLE [dbo].[Int64TimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [bigint] NULL,
  CONSTRAINT [PK_Int64TimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Int64TimeseriesValue]
  ADD CONSTRAINT [UNQ_Int64TimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_Int64TimeseriesValue_Timestamp] ON [dbo].[Int64TimeseriesValue]([Timestamp])
go

/*
 * Item
 *
 */
CREATE TABLE [dbo].[Item]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between Item
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  CONSTRAINT [FK_Item_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_Item] PRIMARY KEY([Id])
)
go

/*
 * BaseStation
 *
 * The BaseStation entity a descendant of the Item entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BaseStation].[Id] field and the
 * [dbo].[Item].[Id] field.
 *
 */
CREATE TABLE [dbo].[BaseStation]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_BaseStation_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Item]([Id]),
  CONSTRAINT [PK_BaseStation] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[BaseStation]
  ADD CONSTRAINT [UNQ_BaseStation_Name] UNIQUE([Name])
go

CREATE INDEX [IDX_BaseStation_Type] ON [dbo].[BaseStation]([Type])
go

/*
 * Device
 *
 * The Device entity a descendant of the Item entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Device].[Id] field and the
 * [dbo].[Item].[Id] field.
 *
 */
CREATE TABLE [dbo].[Device]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Host] [uniqueidentifier] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Description] [nvarchar](max) NOT NULL,
  [EnabledTimeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Device_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Item]([Id]),
  CONSTRAINT [PK_Device] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Device_Host] ON [dbo].[Device]([Host])
go

ALTER TABLE [dbo].[Device]
  ADD CONSTRAINT [UNQ_Device_Name] UNIQUE([Name])
go

/*
 * Camera
 *
 * The Camera entity a descendant of the Device entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Camera].[Id] field and the
 * [dbo].[Device].[Id] field.
 *
 */
CREATE TABLE [dbo].[Camera]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Camera_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Device]([Id]),
  CONSTRAINT [PK_Camera] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Camera_Type] ON [dbo].[Camera]([Type])
go

/*
 * GNSSDevice
 *
 * The GNSSDevice entity a descendant of the Device entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GNSSDevice].[Id] field and the
 * [dbo].[Device].[Id] field.
 *
 */
CREATE TABLE [dbo].[GNSSDevice]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  [LatitudeTimeseries] [uniqueidentifier] NOT NULL,
  [LongitudeTimeseries] [uniqueidentifier] NOT NULL,
  [AltitudeTimeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GNSSDevice_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Device]([Id]),
  CONSTRAINT [PK_GNSSDevice] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_GNSSDevice_Type] ON [dbo].[GNSSDevice]([Type])
go

/*
 * GyroDevice
 *
 * The GyroDevice entity a descendant of the Device entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GyroDevice].[Id] field and the
 * [dbo].[Device].[Id] field.
 *
 */
CREATE TABLE [dbo].[GyroDevice]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  [HeadingTrueNorthTimeseries] [uniqueidentifier] NOT NULL,
  [HeadingMagneticNorthTimeseries] [uniqueidentifier] NOT NULL,
  [PitchTimeseries] [uniqueidentifier] NOT NULL,
  [RateOfTurnTimeseries] [uniqueidentifier] NOT NULL,
  [RollTimeseries] [uniqueidentifier] NOT NULL,
  [CourseTimeseries] [uniqueidentifier] NOT NULL,
  [SpeedTimeseries] [uniqueidentifier] NOT NULL,
  [GNSSDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GyroDevice_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Device]([Id]),
  CONSTRAINT [PK_GyroDevice] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_GyroDevice_Type] ON [dbo].[GyroDevice]([Type])
go

CREATE INDEX [IDX_GyroDevice_GNSSDevice] ON [dbo].[GyroDevice]([GNSSDevice])
go

/*
 * LineInputDevice
 *
 * The LineInputDevice entity a descendant of the Device entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[LineInputDevice].[Id] field and the
 * [dbo].[Device].[Id] field.
 *
 */
CREATE TABLE [dbo].[LineInputDevice]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * A `LineInputDevice` device is a device that performs line oriented I/O on behalf of the server.
   */
  [Type] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_LineInputDevice_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Device]([Id]),
  CONSTRAINT [PK_LineInputDevice] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_LineInputDevice_Type] ON [dbo].[LineInputDevice]([Type])
go

/*
 * OilspillDetector
 *
 * The OilspillDetector entity a descendant of the Device entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[OilspillDetector].[Id] field and the
 * [dbo].[Device].[Id] field.
 *
 */
CREATE TABLE [dbo].[OilspillDetector]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_OilspillDetector_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Device]([Id]),
  CONSTRAINT [PK_OilspillDetector] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_OilspillDetector_Type] ON [dbo].[OilspillDetector]([Type])
go

/*
 * Radio
 *
 * The Radio entity a descendant of the Device entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Radio].[Id] field and the
 * [dbo].[Device].[Id] field.
 *
 */
CREATE TABLE [dbo].[Radio]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Radio_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Device]([Id]),
  CONSTRAINT [PK_Radio] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Radio_Type] ON [dbo].[Radio]([Type])
go

/*
 * Radome
 *
 * The Radome entity a descendant of the Device entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Radome].[Id] field and the
 * [dbo].[Device].[Id] field.
 *
 */
CREATE TABLE [dbo].[Radome]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * A Radome device.
   */
  [Type] [uniqueidentifier] NOT NULL,
  /*
   * A Radome device.
   */
  [Radar] [uniqueidentifier] NOT NULL,
  /*
   * A Radome device.
   */
  [PressureTimeseries] [uniqueidentifier] NOT NULL,
  /*
   * A Radome device.
   */
  [TemperatureTimeseries] [uniqueidentifier] NOT NULL,
  /*
   * A Radome device.
   */
  [DewPointTimeseries] [uniqueidentifier] NOT NULL,
  /*
   * A Radome device.
   */
  [StatusTimeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Radome_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Device]([Id]),
  CONSTRAINT [PK_Radome] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Radome_Type] ON [dbo].[Radome]([Type])
go

CREATE INDEX [IDX_Radome_Radar] ON [dbo].[Radome]([Radar])
go

/*
 * Tracker
 *
 * The Tracker entity a descendant of the Device entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Tracker].[Id] field and the
 * [dbo].[Device].[Id] field.
 *
 */
CREATE TABLE [dbo].[Tracker]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_Tracker_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Device]([Id]),
  CONSTRAINT [PK_Tracker] PRIMARY KEY([Id])
)
go

/*
 * AisTransceiver
 *
 * The AisTransceiver entity a descendant of the Tracker entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisTransceiver].[Id] field and the
 * [dbo].[Tracker].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisTransceiver]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_AisTransceiver_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Tracker]([Id]),
  CONSTRAINT [PK_AisTransceiver] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisTransceiver_Type] ON [dbo].[AisTransceiver]([Type])
go

/*
 * Radar
 *
 * The Radar entity a descendant of the Tracker entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Radar].[Id] field and the
 * [dbo].[Tracker].[Id] field.
 *
 */
CREATE TABLE [dbo].[Radar]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  [SaveSettingsTimeseries] [uniqueidentifier] NOT NULL,
  [PowerOnTimeseries] [uniqueidentifier] NOT NULL,
  [TrackingOnTimeseries] [uniqueidentifier] NOT NULL,
  [RadarPulseTimeseries] [uniqueidentifier] NOT NULL,
  [TuningTimeseries] [uniqueidentifier] NOT NULL,
  [BlankSector1Timeseries] [uniqueidentifier] NOT NULL,
  [Sector1StartTimeseries] [uniqueidentifier] NOT NULL,
  [Sector1EndTimeseries] [uniqueidentifier] NOT NULL,
  [BlankSector2Timeseries] [uniqueidentifier] NOT NULL,
  [Sector2StartTimeseries] [uniqueidentifier] NOT NULL,
  [Sector2EndTimeseries] [uniqueidentifier] NOT NULL,
  [EnableAutomaticFrequencyControlTimeseries] [uniqueidentifier] NOT NULL,
  [AzimuthOffsetTimeseries] [uniqueidentifier] NOT NULL,
  [EnableSensitivityTimeControlTimeseries] [uniqueidentifier] NOT NULL,
  [AutomaticSensitivityTimeControlTimeseries] [uniqueidentifier] NOT NULL,
  [SensitivityTimeControlLevelTimeseries] [uniqueidentifier] NOT NULL,
  [EnableFastTimeConstantTimeseries] [uniqueidentifier] NOT NULL,
  [FastTimeConstantLevelTimeseries] [uniqueidentifier] NOT NULL,
  [FastTimeConstantModeTimeseries] [uniqueidentifier] NOT NULL,
  [LatitudeTimeseries] [uniqueidentifier] NOT NULL,
  [LongitudeTimeseries] [uniqueidentifier] NOT NULL,
  [Radome] [uniqueidentifier] NOT NULL,
  [GNSSDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Radar_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Tracker]([Id]),
  CONSTRAINT [PK_Radar] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Radar_Type] ON [dbo].[Radar]([Type])
go

CREATE INDEX [IDX_Radar_Radome] ON [dbo].[Radar]([Radome])
go

CREATE INDEX [IDX_Radar_GNSSDevice] ON [dbo].[Radar]([GNSSDevice])
go

/*
 * WeatherStation
 *
 * The WeatherStation entity a descendant of the Device entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[WeatherStation].[Id] field and the
 * [dbo].[Device].[Id] field.
 *
 */
CREATE TABLE [dbo].[WeatherStation]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  [BarometricPressureTimeseries] [uniqueidentifier] NOT NULL,
  [AirTemperatureTimeseries] [uniqueidentifier] NOT NULL,
  [WaterTemperatureTimeseries] [uniqueidentifier] NOT NULL,
  [RelativeHumidityTimeseries] [uniqueidentifier] NOT NULL,
  [AbsoluteHumidityTimeseries] [uniqueidentifier] NOT NULL,
  [DewPointTimeseries] [uniqueidentifier] NOT NULL,
  [WindDirectionTimeseries] [uniqueidentifier] NOT NULL,
  [WindSpeedTimeseries] [uniqueidentifier] NOT NULL,
  [Gyro] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_WeatherStation_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Device]([Id]),
  CONSTRAINT [PK_WeatherStation] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_WeatherStation_Type] ON [dbo].[WeatherStation]([Type])
go

CREATE INDEX [IDX_WeatherStation_Gyro] ON [dbo].[WeatherStation]([Gyro])
go

/*
 * Facility
 *
 * The Facility entity a descendant of the Item entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Facility].[Id] field and the
 * [dbo].[Item].[Id] field.
 *
 */
CREATE TABLE [dbo].[Facility]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Altitude] [float](53) NOT NULL,
  CONSTRAINT [FK_Facility_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Item]([Id]),
  CONSTRAINT [PK_Facility] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Facility]
  ADD CONSTRAINT [UNQ_Facility_Name] UNIQUE([Name])
go

CREATE INDEX [IDX_Facility_Type] ON [dbo].[Facility]([Type])
go

/*
 * TrackableItem
 *
 * The TrackableItem entity a descendant of the Item entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[TrackableItem].[Id] field and the
 * [dbo].[Item].[Id] field.
 *
 */
CREATE TABLE [dbo].[TrackableItem]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_TrackableItem_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Item]([Id]),
  CONSTRAINT [PK_TrackableItem] PRIMARY KEY([Id])
)
go

/*
 * Aircraft
 *
 * The Aircraft entity a descendant of the TrackableItem entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Aircraft].[Id] field and the
 * [dbo].[TrackableItem].[Id] field.
 *
 */
CREATE TABLE [dbo].[Aircraft]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Aircraft_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TrackableItem]([Id]),
  CONSTRAINT [PK_Aircraft] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Aircraft_Name] ON [dbo].[Aircraft]([Name])
go

CREATE INDEX [IDX_Aircraft_Type] ON [dbo].[Aircraft]([Type])
go

/*
 * AisAidToNavigation
 *
 * The AisAidToNavigation entity a descendant of the TrackableItem entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisAidToNavigation].[Id] field and the
 * [dbo].[TrackableItem].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisAidToNavigation]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [MMSI] [uniqueidentifier] NOT NULL,
  [NavigationalAidType] [int] NOT NULL,
  [Position] [uniqueidentifier] NOT NULL,
  [IsVirtual] [bit] NOT NULL,
  [ToBow] [int] NOT NULL,
  [ToStern] [int] NOT NULL,
  [ToPort] [int] NOT NULL,
  [ToStarboard] [int] NOT NULL,
  [OffPositionTimeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_AisAidToNavigation_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TrackableItem]([Id]),
  CONSTRAINT [PK_AisAidToNavigation] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[AisAidToNavigation]
  ADD CONSTRAINT [UNQ_AisAidToNavigation_Name] UNIQUE([Name])
go

CREATE INDEX [IDX_AisAidToNavigation_MMSI] ON [dbo].[AisAidToNavigation]([MMSI])
go

/*
 * Vehicle
 *
 * The Vehicle entity a descendant of the TrackableItem entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Vehicle].[Id] field and the
 * [dbo].[TrackableItem].[Id] field.
 *
 */
CREATE TABLE [dbo].[Vehicle]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Vehicle_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TrackableItem]([Id]),
  CONSTRAINT [PK_Vehicle] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Vehicle]
  ADD CONSTRAINT [UNQ_Vehicle_Name] UNIQUE([Name])
go

CREATE INDEX [IDX_Vehicle_Type] ON [dbo].[Vehicle]([Type])
go

/*
 * Vessel
 *
 * The Vessel entity a descendant of the TrackableItem entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Vessel].[Id] field and the
 * [dbo].[TrackableItem].[Id] field.
 *
 */
CREATE TABLE [dbo].[Vessel]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Type] [uniqueidentifier] NOT NULL,
  [ToBow] [int] NOT NULL,
  [ToStern] [int] NOT NULL,
  [ToPort] [int] NOT NULL,
  [ToStarboard] [int] NOT NULL,
  [DraughtTimeseries] [uniqueidentifier] NOT NULL,
  [PersonsOnBoardTimeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Vessel_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TrackableItem]([Id]),
  CONSTRAINT [PK_Vessel] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Vessel_Name] ON [dbo].[Vessel]([Name])
go

CREATE INDEX [IDX_Vessel_Type] ON [dbo].[Vessel]([Type])
go

/*
 * ItemIdentityLink
 *
 */
CREATE TABLE [dbo].[ItemIdentityLink]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Item] [uniqueidentifier] NOT NULL,
  [Identity] [uniqueidentifier] NOT NULL,
  [Start] [bigint] NOT NULL,
  [End] [bigint] NULL,
  CONSTRAINT [PK_ItemIdentityLink] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_ItemIdentityLink_Item_Start] ON [dbo].[ItemIdentityLink]([Item],[Start])
go

CREATE INDEX [IDX_ItemIdentityLink_Item_End] ON [dbo].[ItemIdentityLink]([Item],[End])
go

CREATE INDEX [IDX_ItemIdentityLink_Identity_Start] ON [dbo].[ItemIdentityLink]([Identity],[Start])
go

CREATE INDEX [IDX_ItemIdentityLink_Identity_End] ON [dbo].[ItemIdentityLink]([Identity],[End])
go

CREATE INDEX [IDX_ItemIdentityLink_Start] ON [dbo].[ItemIdentityLink]([Start])
go

CREATE INDEX [IDX_ItemIdentityLink_End] ON [dbo].[ItemIdentityLink]([End])
go

/*
 * ItemParentChildLink
 *
 */
CREATE TABLE [dbo].[ItemParentChildLink]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Parent] [uniqueidentifier] NOT NULL,
  [Child] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  CONSTRAINT [PK_ItemParentChildLink] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[ItemParentChildLink]
  ADD CONSTRAINT [UNQ_ItemParentChildLink_Parent_Timestamp] UNIQUE([Parent],[Timestamp])
go

ALTER TABLE [dbo].[ItemParentChildLink]
  ADD CONSTRAINT [UNQ_ItemParentChildLink_Child_Timestamp] UNIQUE([Child],[Timestamp])
go

CREATE INDEX [IDX_ItemParentChildLink_Timestamp] ON [dbo].[ItemParentChildLink]([Timestamp])
go

/*
 * LineInputDeviceCommand
 *
 */
CREATE TABLE [dbo].[LineInputDeviceCommand]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [LineInputDevice] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DeviceCommandSourceType] [int] NOT NULL,
  [DeviceCommandSourceId] [uniqueidentifier] NOT NULL,
  [Reply] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_LineInputDeviceCommand] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_LineInputDeviceCommand_LineInputDevice_Timestamp] ON [dbo].[LineInputDeviceCommand]([LineInputDevice],[Timestamp])
go

CREATE INDEX [IDX_LineInputDeviceCommand_Timestamp] ON [dbo].[LineInputDeviceCommand]([Timestamp])
go

CREATE INDEX [IDX_LineInputDeviceCommand_Reply] ON [dbo].[LineInputDeviceCommand]([Reply])
go

/*
 * LineInputDeviceCommandReply
 *
 */
CREATE TABLE [dbo].[LineInputDeviceCommandReply]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [LineInputDevice] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Command] [uniqueidentifier] NOT NULL,
  [Status] [int] NOT NULL,
  [Message] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_LineInputDeviceCommandReply] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_LineInputDeviceCommandReply_LineInputDevice_Timestamp] ON [dbo].[LineInputDeviceCommandReply]([LineInputDevice],[Timestamp])
go

CREATE INDEX [IDX_LineInputDeviceCommandReply_Timestamp] ON [dbo].[LineInputDeviceCommandReply]([Timestamp])
go

ALTER TABLE [dbo].[LineInputDeviceCommandReply]
  ADD CONSTRAINT [UNQ_LineInputDeviceCommandReply_Command] UNIQUE([Command])
go

/*
 * LineInputDeviceConfiguration
 *
 */
CREATE TABLE [dbo].[LineInputDeviceConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [LineInputDevice] [uniqueidentifier] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [Timestamp] [bigint] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [StoreReceivedSentences] [bit] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [StoreSentMessages] [bit] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [StoreUnsentMessages] [bit] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [NMEA] [bit] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [StrictNMEA] [bit] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [ConnectionType] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [UdpReceivePort] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [UdpSendHostname] [nvarchar](100) NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [UdpSendPort] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [TcpHostname] [nvarchar](100) NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [TcpPort] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [UseHttpLogin] [bit] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [LoginHostname] [nvarchar](100) NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [LoginPort] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [UserName] [nvarchar](100) NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [Password] [nvarchar](100) NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [ComPort] [nvarchar](100) NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [BaudRate] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [DataBits] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [DiscardNull] [bit] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [DtrEnable] [bit] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [Handshake] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [NewLine] [nvarchar](100) NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [Parity] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [ParityReplace] [tinyint] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [ReadBufferSize] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [ReadTimeout] [bigint] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [ReceivedBytesThreshold] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [RtsEnable] [bit] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [StopBits] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [WriteBufferSize] [int] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [WriteTimeout] [bigint] NOT NULL,
  /*
   * The configuration for a `LineInputDevice`.
   */
  [PairedComPort] [nvarchar](100) NOT NULL,
  CONSTRAINT [PK_LineInputDeviceConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[LineInputDeviceConfiguration]
  ADD CONSTRAINT [UNQ_LineInputDeviceConfiguration_LineInputDevice_Timestamp] UNIQUE([LineInputDevice],[Timestamp])
go

CREATE INDEX [IDX_LineInputDeviceConfiguration_Timestamp] ON [dbo].[LineInputDeviceConfiguration]([Timestamp])
go

/*
 * LineInputMessageRouting
 *
 */
CREATE TABLE [dbo].[LineInputMessageRouting]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [LineInputDevice] [uniqueidentifier] NOT NULL,
  [Type] [nvarchar](100) NOT NULL,
  CONSTRAINT [PK_LineInputMessageRouting] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[LineInputMessageRouting]
  ADD CONSTRAINT [UNQ_LineInputMessageRouting_LineInputDevice_Type] UNIQUE([LineInputDevice],[Type])
go

/*
 * LineInputMessageRoutingDestination
 *
 */
CREATE TABLE [dbo].[LineInputMessageRoutingDestination]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Routing] [uniqueidentifier] NOT NULL,
  [Listener] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_LineInputMessageRoutingDestination] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[LineInputMessageRoutingDestination]
  ADD CONSTRAINT [UNQ_LineInputMessageRoutingDestination_Routing_Listener] UNIQUE([Routing],[Listener])
go

CREATE INDEX [IDX_LineInputMessageRoutingDestination_Listener] ON [dbo].[LineInputMessageRoutingDestination]([Listener])
go

/*
 * LineInputWhiteListEntry
 *
 */
CREATE TABLE [dbo].[LineInputWhiteListEntry]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [LineInputDevice] [uniqueidentifier] NOT NULL,
  [HostName] [nvarchar](128) NOT NULL,
  [Port] [int] NOT NULL,
  CONSTRAINT [PK_LineInputWhiteListEntry] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[LineInputWhiteListEntry]
  ADD CONSTRAINT [UNQ_LineInputWhiteListEntry_LineInputDevice_HostName_Port] UNIQUE([LineInputDevice],[HostName],[Port])
go

/*
 * LogApplication
 *
 */
CREATE TABLE [dbo].[LogApplication]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Information about an application that emits log entries.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Information about an application that emits log entries.
   */
  [Name] [nvarchar](127) NOT NULL,
  /*
   * Information about an application that emits log entries.
   */
  [Description] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_LogApplication] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[LogApplication]
  ADD CONSTRAINT [UNQ_LogApplication_Name] UNIQUE([Name])
go

/*
 * LogApplicationConfiguration
 *
 */
CREATE TABLE [dbo].[LogApplicationConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Application specific log configuration.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Application] [uniqueidentifier] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Timestamp] [bigint] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Finest] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Finer] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Fine] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Info] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Notice] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Warn] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Error] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Severe] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Critical] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Alert] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Fatal] [bit] NOT NULL,
  /*
   * Application specific log configuration.
   */
  [Emergency] [bit] NOT NULL,
  CONSTRAINT [PK_LogApplicationConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[LogApplicationConfiguration]
  ADD CONSTRAINT [UNQ_LogApplicationConfiguration_Application_Timestamp] UNIQUE([Application],[Timestamp])
go

CREATE INDEX [IDX_LogApplicationConfiguration_Timestamp] ON [dbo].[LogApplicationConfiguration]([Timestamp])
go

/*
 * LogHost
 *
 */
CREATE TABLE [dbo].[LogHost]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Information about a computer that hosts applications that emits log entries.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Information about a computer that hosts applications that emits log entries.
   */
  [ComputerName] [nvarchar](127) NOT NULL,
  /*
   * Information about a computer that hosts applications that emits log entries.
   */
  [Description] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_LogHost] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[LogHost]
  ADD CONSTRAINT [UNQ_LogHost_ComputerName] UNIQUE([ComputerName])
go

/*
 * LogHostConfiguration
 *
 */
CREATE TABLE [dbo].[LogHostConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Host] [uniqueidentifier] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Timestamp] [bigint] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Finest] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Finer] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Fine] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Info] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Notice] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Warn] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Error] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Severe] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Critical] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Alert] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Fatal] [bit] NOT NULL,
  /*
   * Computer specific log configuration.
   */
  [Emergency] [bit] NOT NULL,
  CONSTRAINT [PK_LogHostConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[LogHostConfiguration]
  ADD CONSTRAINT [UNQ_LogHostConfiguration_Host_Timestamp] UNIQUE([Host],[Timestamp])
go

CREATE INDEX [IDX_LogHostConfiguration_Timestamp] ON [dbo].[LogHostConfiguration]([Timestamp])
go

/*
 * LogLocation
 *
 */
CREATE TABLE [dbo].[LogLocation]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Position in the source code where the log entry was emitted.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Position in the source code where the log entry was emitted.
   */
  [FileName] [nvarchar](260) NOT NULL,
  /*
   * Position in the source code where the log entry was emitted.
   */
  [LineNumber] [int] NOT NULL,
  /*
   * Position in the source code where the log entry was emitted.
   */
  [Namespace] [nvarchar](512) NOT NULL,
  /*
   * Position in the source code where the log entry was emitted.
   */
  [ClassName] [nvarchar](512) NOT NULL,
  /*
   * Position in the source code where the log entry was emitted.
   */
  [MethodName] [nvarchar](255) NOT NULL,
  CONSTRAINT [PK_LogLocation] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[LogLocation]
  ADD CONSTRAINT [UNQ_LogLocation_FileName_LineNumber] UNIQUE([FileName],[LineNumber])
go

/*
 * LogProcess
 *
 */
CREATE TABLE [dbo].[LogProcess]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Information about a process that emits log entries.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Information about a process that emits log entries.
   */
  [Application] [uniqueidentifier] NOT NULL,
  /*
   * Information about a process that emits log entries.
   */
  [Host] [uniqueidentifier] NOT NULL,
  /*
   * Information about a process that emits log entries.
   */
  [Started] [bigint] NOT NULL,
  /*
   * Information about a process that emits log entries.
   */
  [Stopped] [bigint] NULL,
  /*
   * Information about a process that emits log entries.
   */
  [ProcessId] [bigint] NOT NULL,
  /*
   * Information about a process that emits log entries.
   */
  [Path] [nvarchar](max) NOT NULL,
  /*
   * Information about a process that emits log entries.
   */
  [Identity] [nvarchar](127) NOT NULL,
  CONSTRAINT [PK_LogProcess] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_LogProcess_Application_Started] ON [dbo].[LogProcess]([Application],[Started])
go

CREATE INDEX [IDX_LogProcess_Host_Started] ON [dbo].[LogProcess]([Host],[Started])
go

CREATE INDEX [IDX_LogProcess_Started] ON [dbo].[LogProcess]([Started])
go

/*
 * LogRecord
 *
 */
CREATE TABLE [dbo].[LogRecord]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Thread] [uniqueidentifier] NOT NULL,
  [SequenceNumber] [bigint] NOT NULL,
  [Level] [int] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Depth] [int] NOT NULL,
  [Location] [uniqueidentifier] NOT NULL,
  [Message] [nvarchar](2000) NOT NULL,
  [ExceptionString] [nvarchar](max) NOT NULL,
  [PropertiesData] [varbinary](max) NOT NULL,
  CONSTRAINT [PK_LogRecord] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_LogRecord_Thread_Timestamp] ON [dbo].[LogRecord]([Thread],[Timestamp])
go

CREATE INDEX [IDX_LogRecord_Timestamp] ON [dbo].[LogRecord]([Timestamp])
go

CREATE INDEX [IDX_LogRecord_Location] ON [dbo].[LogRecord]([Location])
go

/*
 * LogThread
 *
 */
CREATE TABLE [dbo].[LogThread]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Information about a thread that emits log entries.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Information about a thread that emits log entries.
   */
  [Process] [uniqueidentifier] NOT NULL,
  /*
   * Information about a thread that emits log entries.
   */
  [Started] [bigint] NOT NULL,
  /*
   * Information about a thread that emits log entries.
   */
  [Stopped] [bigint] NULL,
  /*
   * Information about a thread that emits log entries.
   */
  [ThreadId] [bigint] NOT NULL,
  /*
   * Information about a thread that emits log entries.
   */
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [PK_LogThread] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_LogThread_Process_Started] ON [dbo].[LogThread]([Process],[Started])
go

CREATE INDEX [IDX_LogThread_Started] ON [dbo].[LogThread]([Started])
go

/*
 * LogTraceEntry
 *
 */
CREATE TABLE [dbo].[LogTraceEntry]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Thread execution trace.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Thread execution trace.
   */
  [Thread] [uniqueidentifier] NOT NULL,
  /*
   * Thread execution trace.
   */
  [SequenceNumber] [bigint] NOT NULL,
  /*
   * Thread execution trace.
   */
  [Location] [uniqueidentifier] NOT NULL,
  /*
   * Thread execution trace.
   */
  [Depth] [int] NOT NULL,
  /*
   * Thread execution trace.
   */
  [Entered] [bigint] NOT NULL,
  /*
   * Thread execution trace.
   */
  [Ended] [bigint] NULL,
  CONSTRAINT [PK_LogTraceEntry] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_LogTraceEntry_Thread_Entered] ON [dbo].[LogTraceEntry]([Thread],[Entered])
go

CREATE INDEX [IDX_LogTraceEntry_Location_Entered] ON [dbo].[LogTraceEntry]([Location],[Entered])
go

CREATE INDEX [IDX_LogTraceEntry_Entered] ON [dbo].[LogTraceEntry]([Entered])
go

/*
 * MapElement
 *
 */
CREATE TABLE [dbo].[MapElement]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Item] [uniqueidentifier] NOT NULL,
  [ElementType] [int] NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Angle] [float](53) NOT NULL,
  [Left] [float](53) NOT NULL,
  [Top] [float](53) NOT NULL,
  [Width] [float](53) NOT NULL,
  [Height] [float](53) NOT NULL,
  [Label] [nvarchar](100) NOT NULL,
  [Data] [varbinary](max) NOT NULL,
  CONSTRAINT [PK_MapElement] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_MapElement_Item] ON [dbo].[MapElement]([Item])
go

/*
 * MapInfo
 *
 */
CREATE TABLE [dbo].[MapInfo]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Scale] [int] NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [NorthWestLatitude] [float](53) NOT NULL,
  [NorthWestLongitude] [float](53) NOT NULL,
  [SouthEastLatitude] [float](53) NOT NULL,
  [SouthEastLongitude] [float](53) NOT NULL,
  [Image] [varbinary](max) NOT NULL,
  CONSTRAINT [PK_MapInfo] PRIMARY KEY([Id])
)
go

/*
 * MapServiceOptions
 *
 */
CREATE TABLE [dbo].[MapServiceOptions]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [IpAddress] [nvarchar](127) NOT NULL,
  [Port] [int] NOT NULL,
  [ImageScaleFactorX] [float](53) NOT NULL,
  [ImageOffsetX] [float](53) NOT NULL,
  [ImageScaleFactorY] [float](53) NOT NULL,
  [ImageOffsetY] [float](53) NOT NULL,
  CONSTRAINT [PK_MapServiceOptions] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[MapServiceOptions]
  ADD CONSTRAINT [UNQ_MapServiceOptions_Timestamp] UNIQUE([Timestamp])
go

/*
 * MaritimeIdentificationDigits
 *
 */
CREATE TABLE [dbo].[MaritimeIdentificationDigits]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Code] [int] NOT NULL,
  [Country] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_MaritimeIdentificationDigits] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[MaritimeIdentificationDigits]
  ADD CONSTRAINT [UNQ_MaritimeIdentificationDigits_Code] UNIQUE([Code])
go

CREATE INDEX [IDX_MaritimeIdentificationDigits_Country] ON [dbo].[MaritimeIdentificationDigits]([Country])
go

/*
 * MediaProxySession
 *
 */
CREATE TABLE [dbo].[MediaProxySession]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Service] [uniqueidentifier] NOT NULL,
  [Name] [nvarchar](128) NOT NULL,
  [EnabledTimeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_MediaProxySession] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[MediaProxySession]
  ADD CONSTRAINT [UNQ_MediaProxySession_Service_Name] UNIQUE([Service],[Name])
go

/*
 * MediaProxySessionFile
 *
 */
CREATE TABLE [dbo].[MediaProxySessionFile]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [ProxySession] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [StreamName] [nvarchar](100) NOT NULL,
  CONSTRAINT [PK_MediaProxySessionFile] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[MediaProxySessionFile]
  ADD CONSTRAINT [UNQ_MediaProxySessionFile_ProxySession_Timestamp] UNIQUE([ProxySession],[Timestamp])
go

/*
 * MediaProxySessionOptions
 *
 */
CREATE TABLE [dbo].[MediaProxySessionOptions]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [ProxySession] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [SourceStreamUrl] [nvarchar](255) NOT NULL,
  [StreamName] [nvarchar](255) NOT NULL,
  [Mode] [int] NOT NULL,
  [TunnelOverHTTPPortNumber] [int] NOT NULL,
  [Username] [nvarchar](128) NOT NULL,
  [Password] [nvarchar](128) NOT NULL,
  [RecorderPortNumber] [int] NOT NULL,
  [SessionType] [int] NOT NULL,
  [MaxFileTime] [bigint] NOT NULL,
  [MaxFileRetention] [bigint] NOT NULL,
  [VideoDirectory] [nvarchar](260) NOT NULL,
  CONSTRAINT [PK_MediaProxySessionOptions] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[MediaProxySessionOptions]
  ADD CONSTRAINT [UNQ_MediaProxySessionOptions_ProxySession_Timestamp] UNIQUE([ProxySession],[Timestamp])
go

/*
 * MediaService
 *
 */
CREATE TABLE [dbo].[MediaService]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [EnabledTimeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_MediaService] PRIMARY KEY([Id])
)
go

/*
 * MediaServiceOptions
 *
 */
CREATE TABLE [dbo].[MediaServiceOptions]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [MediaService] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [RtspPortNumber] [int] NOT NULL,
  [HttpPortNumber] [int] NOT NULL,
  CONSTRAINT [PK_MediaServiceOptions] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[MediaServiceOptions]
  ADD CONSTRAINT [UNQ_MediaServiceOptions_MediaService_Timestamp] UNIQUE([MediaService],[Timestamp])
go

/*
 * NamespaceElement
 *
 */
CREATE TABLE [dbo].[NamespaceElement]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between NamespaceElement
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Namespace] [uniqueidentifier] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Description] [nvarchar](max) NOT NULL,
  CONSTRAINT [FK_NamespaceElement_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_NamespaceElement] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[NamespaceElement]
  ADD CONSTRAINT [UNQ_NamespaceElement_Namespace_Name] UNIQUE([Namespace],[Name])
go

/*
 * ElementType
 *
 * The ElementType entity a descendant of the NamespaceElement entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ElementType].[Id] field and the
 * [dbo].[NamespaceElement].[Id] field.
 *
 */
CREATE TABLE [dbo].[ElementType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_ElementType_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[NamespaceElement]([Id]),
  CONSTRAINT [PK_ElementType] PRIMARY KEY([Id])
)
go

/*
 * Namespace
 *
 * The Namespace entity a descendant of the NamespaceElement entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Namespace].[Id] field and the
 * [dbo].[NamespaceElement].[Id] field.
 *
 */
CREATE TABLE [dbo].[Namespace]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_Namespace_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[NamespaceElement]([Id]),
  CONSTRAINT [PK_Namespace] PRIMARY KEY([Id])
)
go

/*
 * Oilspill
 *
 */
CREATE TABLE [dbo].[Oilspill]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [OilSpillDetector] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [OilArea] [float](53) NOT NULL,
  [Shape] [varbinary](max) NOT NULL,
  [BSI] [varbinary](max) NOT NULL,
  [Oil] [varbinary](max) NOT NULL,
  [Trace] [varbinary](max) NOT NULL,
  CONSTRAINT [PK_Oilspill] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Oilspill_OilSpillDetector_Timestamp] ON [dbo].[Oilspill]([OilSpillDetector],[Timestamp])
go

CREATE INDEX [IDX_Oilspill_Timestamp] ON [dbo].[Oilspill]([Timestamp])
go

/*
 * OilspillDetectorCommand
 *
 */
CREATE TABLE [dbo].[OilspillDetectorCommand]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [OilSpillDetector] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DeviceCommandSourceType] [int] NOT NULL,
  [DeviceCommandSourceId] [uniqueidentifier] NOT NULL,
  [Reply] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_OilspillDetectorCommand] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_OilspillDetectorCommand_OilSpillDetector_Timestamp] ON [dbo].[OilspillDetectorCommand]([OilSpillDetector],[Timestamp])
go

CREATE INDEX [IDX_OilspillDetectorCommand_Timestamp] ON [dbo].[OilspillDetectorCommand]([Timestamp])
go

CREATE INDEX [IDX_OilspillDetectorCommand_Reply] ON [dbo].[OilspillDetectorCommand]([Reply])
go

/*
 * OilspillDetectorCommandReply
 *
 */
CREATE TABLE [dbo].[OilspillDetectorCommandReply]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [OilSpillDetector] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Command] [uniqueidentifier] NOT NULL,
  [Status] [int] NOT NULL,
  [Message] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_OilspillDetectorCommandReply] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_OilspillDetectorCommandReply_OilSpillDetector_Timestamp] ON [dbo].[OilspillDetectorCommandReply]([OilSpillDetector],[Timestamp])
go

CREATE INDEX [IDX_OilspillDetectorCommandReply_Timestamp] ON [dbo].[OilspillDetectorCommandReply]([Timestamp])
go

ALTER TABLE [dbo].[OilspillDetectorCommandReply]
  ADD CONSTRAINT [UNQ_OilspillDetectorCommandReply_Command] UNIQUE([Command])
go

/*
 * OilspillDetectorConfiguration
 *
 */
CREATE TABLE [dbo].[OilspillDetectorConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [OilSpillDetector] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Range] [float](53) NOT NULL,
  [StartAngle] [float](53) NOT NULL,
  [EndAngle] [float](53) NOT NULL,
  [StartRange] [float](53) NOT NULL,
  [EndRange] [float](53) NOT NULL,
  [UpdateRate] [int] NOT NULL,
  [StatusSendTime] [bigint] NOT NULL,
  [DrawBorder] [bit] NOT NULL,
  [Colors] [varbinary](max) NOT NULL,
  [SendToServer] [bit] NOT NULL,
  [Directory] [nvarchar](100) NOT NULL,
  [TransparentWater] [bit] NOT NULL,
  [SavePictures] [bit] NOT NULL,
  [SendAsTarget] [bit] NOT NULL,
  [WriteLog] [bit] NOT NULL,
  [TargetFilePrefix] [nvarchar](100) NOT NULL,
  [TargetMMSI] [uniqueidentifier] NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [TestSourceEnabled] [bit] NOT NULL,
  [ProxyServer] [nvarchar](100) NOT NULL,
  [UseProxyServer] [bit] NOT NULL,
  CONSTRAINT [PK_OilspillDetectorConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[OilspillDetectorConfiguration]
  ADD CONSTRAINT [UNQ_OilspillDetectorConfiguration_OilSpillDetector_Timestamp] UNIQUE([OilSpillDetector],[Timestamp])
go

CREATE INDEX [IDX_OilspillDetectorConfiguration_Timestamp] ON [dbo].[OilspillDetectorConfiguration]([Timestamp])
go

CREATE INDEX [IDX_OilspillDetectorConfiguration_TargetMMSI] ON [dbo].[OilspillDetectorConfiguration]([TargetMMSI])
go

/*
 * Position2DTimeseriesValue
 *
 */
CREATE TABLE [dbo].[Position2DTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [X] [float](53) NULL,
  [Y] [float](53) NULL,
  CONSTRAINT [PK_Position2DTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Position2DTimeseriesValue]
  ADD CONSTRAINT [UNQ_Position2DTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_Position2DTimeseriesValue_Timestamp] ON [dbo].[Position2DTimeseriesValue]([Timestamp])
go

/*
 * Position3DTimeseriesValue
 *
 */
CREATE TABLE [dbo].[Position3DTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [X] [float](53) NULL,
  [Y] [float](53) NULL,
  [Z] [float](53) NULL,
  CONSTRAINT [PK_Position3DTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Position3DTimeseriesValue]
  ADD CONSTRAINT [UNQ_Position3DTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_Position3DTimeseriesValue_Timestamp] ON [dbo].[Position3DTimeseriesValue]([Timestamp])
go

/*
 * ProcessTrackValueResult
 *
 */
CREATE TABLE [dbo].[ProcessTrackValueResult]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [CreatedNewTrack] [bit] NOT NULL,
  [TrackId] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_ProcessTrackValueResult] PRIMARY KEY([Id])
)
go

/*
 * Property
 *
 */
CREATE TABLE [dbo].[Property]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between Property
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Element] [uniqueidentifier] NOT NULL,
  [Definition] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Property_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_Property] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Property]
  ADD CONSTRAINT [UNQ_Property_Element_Definition] UNIQUE([Element],[Definition])
go

CREATE INDEX [IDX_Property_Definition] ON [dbo].[Property]([Definition])
go

/*
 * BinaryProperty
 *
 * The BinaryProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BinaryProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[BinaryProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [varbinary](max) NOT NULL,
  CONSTRAINT [FK_BinaryProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_BinaryProperty] PRIMARY KEY([Id])
)
go

/*
 * BooleanProperty
 *
 * The BooleanProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BooleanProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[BooleanProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [bit] NOT NULL,
  CONSTRAINT [FK_BooleanProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_BooleanProperty] PRIMARY KEY([Id])
)
go

/*
 * ByteProperty
 *
 * The ByteProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ByteProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[ByteProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [tinyint] NOT NULL,
  CONSTRAINT [FK_ByteProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_ByteProperty] PRIMARY KEY([Id])
)
go

/*
 * DateTimeProperty
 *
 * The DateTimeProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DateTimeProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[DateTimeProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [bigint] NOT NULL,
  CONSTRAINT [FK_DateTimeProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_DateTimeProperty] PRIMARY KEY([Id])
)
go

/*
 * DoubleProperty
 *
 * The DoubleProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DoubleProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[DoubleProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [float](53) NOT NULL,
  CONSTRAINT [FK_DoubleProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_DoubleProperty] PRIMARY KEY([Id])
)
go

/*
 * GuidProperty
 *
 * The GuidProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GuidProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[GuidProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GuidProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_GuidProperty] PRIMARY KEY([Id])
)
go

/*
 * Int16Property
 *
 * The Int16Property entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int16Property].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int16Property]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [smallint] NOT NULL,
  CONSTRAINT [FK_Int16Property_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_Int16Property] PRIMARY KEY([Id])
)
go

/*
 * Int32Property
 *
 * The Int32Property entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int32Property].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int32Property]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [int] NOT NULL,
  CONSTRAINT [FK_Int32Property_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_Int32Property] PRIMARY KEY([Id])
)
go

/*
 * Int64Property
 *
 * The Int64Property entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int64Property].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int64Property]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [bigint] NOT NULL,
  CONSTRAINT [FK_Int64Property_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_Int64Property] PRIMARY KEY([Id])
)
go

/*
 * ReferenceProperty
 *
 * The ReferenceProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ReferenceProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[ReferenceProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_ReferenceProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_ReferenceProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_ReferenceProperty_Value] ON [dbo].[ReferenceProperty]([Value])
go

/*
 * SByteProperty
 *
 * The SByteProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SByteProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[SByteProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [numeric](3,0) NOT NULL,
  CONSTRAINT [FK_SByteProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_SByteProperty] PRIMARY KEY([Id])
)
go

/*
 * SingleProperty
 *
 * The SingleProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SingleProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[SingleProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [float](24) NOT NULL,
  CONSTRAINT [FK_SingleProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_SingleProperty] PRIMARY KEY([Id])
)
go

/*
 * StringProperty
 *
 * The StringProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[StringProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[StringProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [nvarchar](100) NOT NULL,
  CONSTRAINT [FK_StringProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_StringProperty] PRIMARY KEY([Id])
)
go

/*
 * TimeseriesProperty
 *
 * The TimeseriesProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[TimeseriesProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[TimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_TimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_TimeseriesProperty] PRIMARY KEY([Id])
)
go

/*
 * BinaryTimeseriesProperty
 *
 * The BinaryTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BinaryTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[BinaryTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_BinaryTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_BinaryTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_BinaryTimeseriesProperty_Timeseries] ON [dbo].[BinaryTimeseriesProperty]([Timeseries])
go

/*
 * BooleanTimeseriesProperty
 *
 * The BooleanTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BooleanTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[BooleanTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_BooleanTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_BooleanTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_BooleanTimeseriesProperty_Timeseries] ON [dbo].[BooleanTimeseriesProperty]([Timeseries])
go

/*
 * ByteTimeseriesProperty
 *
 * The ByteTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ByteTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[ByteTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_ByteTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_ByteTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_ByteTimeseriesProperty_Timeseries] ON [dbo].[ByteTimeseriesProperty]([Timeseries])
go

/*
 * DateTimeTimeseriesProperty
 *
 * The DateTimeTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DateTimeTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[DateTimeTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_DateTimeTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_DateTimeTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_DateTimeTimeseriesProperty_Timeseries] ON [dbo].[DateTimeTimeseriesProperty]([Timeseries])
go

/*
 * DoubleTimeseriesProperty
 *
 * The DoubleTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DoubleTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[DoubleTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_DoubleTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_DoubleTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_DoubleTimeseriesProperty_Timeseries] ON [dbo].[DoubleTimeseriesProperty]([Timeseries])
go

/*
 * GuidTimeseriesProperty
 *
 * The GuidTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GuidTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[GuidTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GuidTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_GuidTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_GuidTimeseriesProperty_Timeseries] ON [dbo].[GuidTimeseriesProperty]([Timeseries])
go

/*
 * Int16TimeseriesProperty
 *
 * The Int16TimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int16TimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int16TimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Int16TimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_Int16TimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Int16TimeseriesProperty_Timeseries] ON [dbo].[Int16TimeseriesProperty]([Timeseries])
go

/*
 * Int32TimeseriesProperty
 *
 * The Int32TimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int32TimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int32TimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Int32TimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_Int32TimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Int32TimeseriesProperty_Timeseries] ON [dbo].[Int32TimeseriesProperty]([Timeseries])
go

/*
 * Int64TimeseriesProperty
 *
 * The Int64TimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int64TimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int64TimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_Int64TimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_Int64TimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_Int64TimeseriesProperty_Timeseries] ON [dbo].[Int64TimeseriesProperty]([Timeseries])
go

/*
 * ReferenceTimeseriesProperty
 *
 * The ReferenceTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ReferenceTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[ReferenceTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_ReferenceTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_ReferenceTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_ReferenceTimeseriesProperty_Timeseries] ON [dbo].[ReferenceTimeseriesProperty]([Timeseries])
go

/*
 * SByteTimeseriesProperty
 *
 * The SByteTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SByteTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[SByteTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_SByteTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_SByteTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_SByteTimeseriesProperty_Timeseries] ON [dbo].[SByteTimeseriesProperty]([Timeseries])
go

/*
 * SingleTimeseriesProperty
 *
 * The SingleTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SingleTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[SingleTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_SingleTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_SingleTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_SingleTimeseriesProperty_Timeseries] ON [dbo].[SingleTimeseriesProperty]([Timeseries])
go

/*
 * StringTimeseriesProperty
 *
 * The StringTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[StringTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[StringTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_StringTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_StringTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_StringTimeseriesProperty_Timeseries] ON [dbo].[StringTimeseriesProperty]([Timeseries])
go

/*
 * TimeSpanTimeseriesProperty
 *
 * The TimeSpanTimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[TimeSpanTimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[TimeSpanTimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_TimeSpanTimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_TimeSpanTimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_TimeSpanTimeseriesProperty_Timeseries] ON [dbo].[TimeSpanTimeseriesProperty]([Timeseries])
go

/*
 * UInt16TimeseriesProperty
 *
 * The UInt16TimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt16TimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt16TimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_UInt16TimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_UInt16TimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_UInt16TimeseriesProperty_Timeseries] ON [dbo].[UInt16TimeseriesProperty]([Timeseries])
go

/*
 * UInt32TimeseriesProperty
 *
 * The UInt32TimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt32TimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt32TimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_UInt32TimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_UInt32TimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_UInt32TimeseriesProperty_Timeseries] ON [dbo].[UInt32TimeseriesProperty]([Timeseries])
go

/*
 * UInt64TimeseriesProperty
 *
 * The UInt64TimeseriesProperty entity a descendant of the TimeseriesProperty entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt64TimeseriesProperty].[Id] field and the
 * [dbo].[TimeseriesProperty].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt64TimeseriesProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_UInt64TimeseriesProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesProperty]([Id]),
  CONSTRAINT [PK_UInt64TimeseriesProperty] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_UInt64TimeseriesProperty_Timeseries] ON [dbo].[UInt64TimeseriesProperty]([Timeseries])
go

/*
 * TimeSpanProperty
 *
 * The TimeSpanProperty entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[TimeSpanProperty].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[TimeSpanProperty]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [bigint] NOT NULL,
  CONSTRAINT [FK_TimeSpanProperty_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_TimeSpanProperty] PRIMARY KEY([Id])
)
go

/*
 * UInt16Property
 *
 * The UInt16Property entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt16Property].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt16Property]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [numeric](5,0) NOT NULL,
  CONSTRAINT [FK_UInt16Property_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_UInt16Property] PRIMARY KEY([Id])
)
go

/*
 * UInt32Property
 *
 * The UInt32Property entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt32Property].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt32Property]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [numeric](10,0) NOT NULL,
  CONSTRAINT [FK_UInt32Property_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_UInt32Property] PRIMARY KEY([Id])
)
go

/*
 * UInt64Property
 *
 * The UInt64Property entity a descendant of the Property entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt64Property].[Id] field and the
 * [dbo].[Property].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt64Property]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Value] [bigint] NOT NULL,
  CONSTRAINT [FK_UInt64Property_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Property]([Id]),
  CONSTRAINT [PK_UInt64Property] PRIMARY KEY([Id])
)
go

/*
 * PropertyDefinition
 *
 */
CREATE TABLE [dbo].[PropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between PropertyDefinition
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [ElementType] [uniqueidentifier] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Description] [nvarchar](max) NOT NULL,
  CONSTRAINT [FK_PropertyDefinition_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_PropertyDefinition] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[PropertyDefinition]
  ADD CONSTRAINT [UNQ_PropertyDefinition_ElementType_Name] UNIQUE([ElementType],[Name])
go

/*
 * BinaryPropertyDefinition
 *
 * The BinaryPropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BinaryPropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[BinaryPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [varbinary](max) NOT NULL,
  CONSTRAINT [FK_BinaryPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_BinaryPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * BooleanPropertyDefinition
 *
 * The BooleanPropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BooleanPropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[BooleanPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [bit] NOT NULL,
  CONSTRAINT [FK_BooleanPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_BooleanPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * BytePropertyDefinition
 *
 * The BytePropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BytePropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[BytePropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [tinyint] NOT NULL,
  [MinValue] [tinyint] NOT NULL,
  [MaxValue] [tinyint] NOT NULL,
  CONSTRAINT [FK_BytePropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_BytePropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * DateTimePropertyDefinition
 *
 * The DateTimePropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DateTimePropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[DateTimePropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [nvarchar](100) NOT NULL,
  [MinValue] [nvarchar](100) NOT NULL,
  [MaxValue] [nvarchar](100) NOT NULL,
  CONSTRAINT [FK_DateTimePropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_DateTimePropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * DoublePropertyDefinition
 *
 * The DoublePropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DoublePropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[DoublePropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [float](53) NOT NULL,
  [MinValue] [float](53) NOT NULL,
  [MaxValue] [float](53) NOT NULL,
  CONSTRAINT [FK_DoublePropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_DoublePropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * GuidPropertyDefinition
 *
 * The GuidPropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GuidPropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[GuidPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GuidPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_GuidPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * Int16PropertyDefinition
 *
 * The Int16PropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int16PropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int16PropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [smallint] NOT NULL,
  [MinValue] [smallint] NOT NULL,
  [MaxValue] [smallint] NOT NULL,
  CONSTRAINT [FK_Int16PropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_Int16PropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * Int32PropertyDefinition
 *
 * The Int32PropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int32PropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int32PropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [int] NOT NULL,
  [MinValue] [int] NOT NULL,
  [MaxValue] [int] NOT NULL,
  CONSTRAINT [FK_Int32PropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_Int32PropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * Int64PropertyDefinition
 *
 * The Int64PropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int64PropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int64PropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [bigint] NOT NULL,
  [MinValue] [bigint] NOT NULL,
  [MaxValue] [bigint] NOT NULL,
  CONSTRAINT [FK_Int64PropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_Int64PropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * ReferencePropertyDefinition
 *
 * The ReferencePropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ReferencePropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[ReferencePropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [uniqueidentifier] NOT NULL,
  [ReferencedElementType] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_ReferencePropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_ReferencePropertyDefinition] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_ReferencePropertyDefinition_DefaultValue] ON [dbo].[ReferencePropertyDefinition]([DefaultValue])
go

CREATE INDEX [IDX_ReferencePropertyDefinition_ReferencedElementType] ON [dbo].[ReferencePropertyDefinition]([ReferencedElementType])
go

/*
 * SBytePropertyDefinition
 *
 * The SBytePropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SBytePropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[SBytePropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [numeric](3,0) NOT NULL,
  [MinValue] [numeric](3,0) NOT NULL,
  [MaxValue] [numeric](3,0) NOT NULL,
  CONSTRAINT [FK_SBytePropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_SBytePropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * SinglePropertyDefinition
 *
 * The SinglePropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SinglePropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[SinglePropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [float](24) NOT NULL,
  [MinValue] [float](24) NOT NULL,
  [MaxValue] [float](24) NOT NULL,
  CONSTRAINT [FK_SinglePropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_SinglePropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * StringPropertyDefinition
 *
 * The StringPropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[StringPropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[StringPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [nvarchar](100) NOT NULL,
  [Pattern] [nvarchar](100) NOT NULL,
  CONSTRAINT [FK_StringPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_StringPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * TimeseriesPropertyDefinition
 *
 * The TimeseriesPropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[TimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[TimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_TimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_TimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * BinaryTimeseriesPropertyDefinition
 *
 * The BinaryTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BinaryTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[BinaryTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_BinaryTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_BinaryTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * BooleanTimeseriesPropertyDefinition
 *
 * The BooleanTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BooleanTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[BooleanTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_BooleanTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_BooleanTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * ByteTimeseriesPropertyDefinition
 *
 * The ByteTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ByteTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[ByteTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [tinyint] NOT NULL,
  [MaxValue] [tinyint] NOT NULL,
  CONSTRAINT [FK_ByteTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_ByteTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * DateTimeTimeseriesPropertyDefinition
 *
 * The DateTimeTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DateTimeTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[DateTimeTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [nvarchar](100) NOT NULL,
  [MaxValue] [nvarchar](100) NOT NULL,
  CONSTRAINT [FK_DateTimeTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_DateTimeTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * DoubleTimeseriesPropertyDefinition
 *
 * The DoubleTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DoubleTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[DoubleTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [float](53) NOT NULL,
  [MaxValue] [float](53) NOT NULL,
  CONSTRAINT [FK_DoubleTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_DoubleTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * GuidTimeseriesPropertyDefinition
 *
 * The GuidTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GuidTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[GuidTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_GuidTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_GuidTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * Int16TimeseriesPropertyDefinition
 *
 * The Int16TimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int16TimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int16TimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [smallint] NOT NULL,
  [MaxValue] [smallint] NOT NULL,
  CONSTRAINT [FK_Int16TimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_Int16TimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * Int32TimeseriesPropertyDefinition
 *
 * The Int32TimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int32TimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int32TimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [int] NOT NULL,
  [MaxValue] [int] NOT NULL,
  CONSTRAINT [FK_Int32TimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_Int32TimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * Int64TimeseriesPropertyDefinition
 *
 * The Int64TimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int64TimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int64TimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [bigint] NOT NULL,
  [MaxValue] [bigint] NOT NULL,
  CONSTRAINT [FK_Int64TimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_Int64TimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * ReferenceTimeseriesPropertyDefinition
 *
 * The ReferenceTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ReferenceTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[ReferenceTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [ReferencedElementType] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_ReferenceTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_ReferenceTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_ReferenceTimeseriesPropertyDefinition_ReferencedElementType] ON [dbo].[ReferenceTimeseriesPropertyDefinition]([ReferencedElementType])
go

/*
 * SByteTimeseriesPropertyDefinition
 *
 * The SByteTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SByteTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[SByteTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [numeric](3,0) NOT NULL,
  [MaxValue] [numeric](3,0) NOT NULL,
  CONSTRAINT [FK_SByteTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_SByteTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * SingleTimeseriesPropertyDefinition
 *
 * The SingleTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SingleTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[SingleTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [float](24) NOT NULL,
  [MaxValue] [float](24) NOT NULL,
  CONSTRAINT [FK_SingleTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_SingleTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * StringTimeseriesPropertyDefinition
 *
 * The StringTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[StringTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[StringTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Pattern] [nvarchar](100) NOT NULL,
  CONSTRAINT [FK_StringTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_StringTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * TimeSpanTimeseriesPropertyDefinition
 *
 * The TimeSpanTimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[TimeSpanTimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[TimeSpanTimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [bigint] NOT NULL,
  [MaxValue] [bigint] NOT NULL,
  CONSTRAINT [FK_TimeSpanTimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_TimeSpanTimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * UInt16TimeseriesPropertyDefinition
 *
 * The UInt16TimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt16TimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt16TimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [numeric](5,0) NOT NULL,
  [MaxValue] [numeric](5,0) NOT NULL,
  CONSTRAINT [FK_UInt16TimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_UInt16TimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * UInt32TimeseriesPropertyDefinition
 *
 * The UInt32TimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt32TimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt32TimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [numeric](10,0) NOT NULL,
  [MaxValue] [numeric](10,0) NOT NULL,
  CONSTRAINT [FK_UInt32TimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_UInt32TimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * UInt64TimeseriesPropertyDefinition
 *
 * The UInt64TimeseriesPropertyDefinition entity a descendant of the TimeseriesPropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt64TimeseriesPropertyDefinition].[Id] field and the
 * [dbo].[TimeseriesPropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt64TimeseriesPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MinValue] [bigint] NOT NULL,
  [MaxValue] [bigint] NOT NULL,
  CONSTRAINT [FK_UInt64TimeseriesPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesPropertyDefinition]([Id]),
  CONSTRAINT [PK_UInt64TimeseriesPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * TimeSpanPropertyDefinition
 *
 * The TimeSpanPropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[TimeSpanPropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[TimeSpanPropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [bigint] NOT NULL,
  [MinValue] [bigint] NOT NULL,
  [MaxValue] [bigint] NOT NULL,
  CONSTRAINT [FK_TimeSpanPropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_TimeSpanPropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * UInt16PropertyDefinition
 *
 * The UInt16PropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt16PropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt16PropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [numeric](5,0) NOT NULL,
  [MinValue] [numeric](5,0) NOT NULL,
  [MaxValue] [numeric](5,0) NOT NULL,
  CONSTRAINT [FK_UInt16PropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_UInt16PropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * UInt32PropertyDefinition
 *
 * The UInt32PropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt32PropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt32PropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [numeric](10,0) NOT NULL,
  [MinValue] [numeric](10,0) NOT NULL,
  [MaxValue] [numeric](10,0) NOT NULL,
  CONSTRAINT [FK_UInt32PropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_UInt32PropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * UInt64PropertyDefinition
 *
 * The UInt64PropertyDefinition entity a descendant of the PropertyDefinition entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt64PropertyDefinition].[Id] field and the
 * [dbo].[PropertyDefinition].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt64PropertyDefinition]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [DefaultValue] [bigint] NOT NULL,
  [MinValue] [bigint] NOT NULL,
  [MaxValue] [bigint] NOT NULL,
  CONSTRAINT [FK_UInt64PropertyDefinition_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[PropertyDefinition]([Id]),
  CONSTRAINT [PK_UInt64PropertyDefinition] PRIMARY KEY([Id])
)
go

/*
 * RadarAlarmStatus
 *
 */
CREATE TABLE [dbo].[RadarAlarmStatus]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Type] [int] NOT NULL,
  CONSTRAINT [PK_RadarAlarmStatus] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[RadarAlarmStatus]
  ADD CONSTRAINT [UNQ_RadarAlarmStatus_Radar_Timestamp] UNIQUE([Radar],[Timestamp])
go

CREATE INDEX [IDX_RadarAlarmStatus_Timestamp] ON [dbo].[RadarAlarmStatus]([Timestamp])
go

/*
 * RadarCommand
 *
 */
CREATE TABLE [dbo].[RadarCommand]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between RadarCommand
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DeviceCommandSourceType] [int] NOT NULL,
  [DeviceCommandSourceId] [uniqueidentifier] NOT NULL,
  [Reply] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarCommand_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_RadarCommand] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_RadarCommand_Radar_Timestamp] ON [dbo].[RadarCommand]([Radar],[Timestamp])
go

CREATE INDEX [IDX_RadarCommand_Timestamp] ON [dbo].[RadarCommand]([Timestamp])
go

CREATE INDEX [IDX_RadarCommand_Reply] ON [dbo].[RadarCommand]([Reply])
go

/*
 * RadarCommandGetStatus
 *
 * The RadarCommandGetStatus entity a descendant of the RadarCommand entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarCommandGetStatus].[Id] field and the
 * [dbo].[RadarCommand].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarCommandGetStatus]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_RadarCommandGetStatus_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[RadarCommand]([Id]),
  CONSTRAINT [PK_RadarCommandGetStatus] PRIMARY KEY([Id])
)
go

/*
 * RadarCommandReply
 *
 */
CREATE TABLE [dbo].[RadarCommandReply]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between RadarCommandReply
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Command] [uniqueidentifier] NOT NULL,
  [Status] [int] NOT NULL,
  [Message] [nvarchar](max) NOT NULL,
  CONSTRAINT [FK_RadarCommandReply_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_RadarCommandReply] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_RadarCommandReply_Radar_Timestamp] ON [dbo].[RadarCommandReply]([Radar],[Timestamp])
go

CREATE INDEX [IDX_RadarCommandReply_Timestamp] ON [dbo].[RadarCommandReply]([Timestamp])
go

ALTER TABLE [dbo].[RadarCommandReply]
  ADD CONSTRAINT [UNQ_RadarCommandReply_Command] UNIQUE([Command])
go

/*
 * RadarCommandReplyGetStatus
 *
 * The RadarCommandReplyGetStatus entity a descendant of the RadarCommandReply entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarCommandReplyGetStatus].[Id] field and the
 * [dbo].[RadarCommandReply].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarCommandReplyGetStatus]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [AzimuthCount] [int] NOT NULL,
  [TriggerCount] [int] NOT NULL,
  [RotationCount] [bigint] NOT NULL,
  [Pulse] [int] NOT NULL,
  [Tx] [bit] NOT NULL,
  CONSTRAINT [FK_RadarCommandReplyGetStatus_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[RadarCommandReply]([Id]),
  CONSTRAINT [PK_RadarCommandReplyGetStatus] PRIMARY KEY([Id])
)
go

/*
 * RadarConfiguration
 *
 */
CREATE TABLE [dbo].[RadarConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [RadarProtocolVersion] [int] NOT NULL,
  [RadarIPAddress] [nvarchar](100) NOT NULL,
  [RadarPort] [int] NOT NULL,
  [RadarConfigurationPort] [int] NOT NULL,
  [SkipMagicTimeout] [bigint] NOT NULL,
  [ReadTimeout] [bigint] NOT NULL,
  [SynchronizationInterval] [bigint] NOT NULL,
  [TargetsRefreshRate] [int] NOT NULL,
  [Range] [int] NOT NULL,
  [SectorCount] [int] NOT NULL,
  [SectorOffset] [int] NOT NULL,
  [ImageColor] [numeric](10,0) NOT NULL,
  [ImageSubstitutionColor] [numeric](10,0) NULL,
  [TransparentColor] [numeric](10,0) NOT NULL,
  [ImageScaleFactorX] [float](53) NOT NULL,
  [ImageOffsetX] [float](53) NOT NULL,
  [ImageScaleFactorY] [float](53) NOT NULL,
  [ImageOffsetY] [float](53) NOT NULL,
  [RadarImageType] [int] NOT NULL,
  [TrackColor] [numeric](10,0) NOT NULL,
  [VectorColor] [numeric](10,0) NOT NULL,
  [EnableNmea] [bit] NOT NULL,
  [NmeaReceiverIPAddress] [nvarchar](100) NOT NULL,
  [NmeaReceiverPort] [int] NOT NULL,
  [NmeaReceiverSourceId] [nvarchar](100) NOT NULL,
  CONSTRAINT [PK_RadarConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[RadarConfiguration]
  ADD CONSTRAINT [UNQ_RadarConfiguration_Radar_Timestamp] UNIQUE([Radar],[Timestamp])
go

CREATE INDEX [IDX_RadarConfiguration_Timestamp] ON [dbo].[RadarConfiguration]([Timestamp])
go

/*
 * RadarImage
 *
 */
CREATE TABLE [dbo].[RadarImage]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Depth] [numeric](10,0) NOT NULL,
  [Resolution] [int] NOT NULL,
  [Range] [int] NOT NULL,
  [Image] [varbinary](max) NOT NULL,
  CONSTRAINT [PK_RadarImage] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[RadarImage]
  ADD CONSTRAINT [UNQ_RadarImage_Radar_Timestamp] UNIQUE([Radar],[Timestamp])
go

CREATE INDEX [IDX_RadarImage_Timestamp] ON [dbo].[RadarImage]([Timestamp])
go

/*
 * RadarRawTrackTable
 *
 */
CREATE TABLE [dbo].[RadarRawTrackTable]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Count] [int] NOT NULL,
  [Table] [varbinary](max) NOT NULL,
  CONSTRAINT [PK_RadarRawTrackTable] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[RadarRawTrackTable]
  ADD CONSTRAINT [UNQ_RadarRawTrackTable_Radar_Timestamp] UNIQUE([Radar],[Timestamp])
go

CREATE INDEX [IDX_RadarRawTrackTable_Timestamp] ON [dbo].[RadarRawTrackTable]([Timestamp])
go

/*
 * RadarStatus
 *
 */
CREATE TABLE [dbo].[RadarStatus]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [AzimuthCount] [int] NOT NULL,
  [TriggerCount] [int] NOT NULL,
  [RotationTime] [bigint] NOT NULL,
  [Pulse] [int] NOT NULL,
  [Tx] [bit] NOT NULL,
  [Tracking] [bit] NOT NULL,
  CONSTRAINT [PK_RadarStatus] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[RadarStatus]
  ADD CONSTRAINT [UNQ_RadarStatus_Radar_Timestamp] UNIQUE([Radar],[Timestamp])
go

CREATE INDEX [IDX_RadarStatus_Timestamp] ON [dbo].[RadarStatus]([Timestamp])
go

/*
 * RadioCommand
 *
 */
CREATE TABLE [dbo].[RadioCommand]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radio] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DeviceCommandSourceType] [int] NOT NULL,
  [DeviceCommandSourceId] [uniqueidentifier] NOT NULL,
  [Reply] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_RadioCommand] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_RadioCommand_Radio_Timestamp] ON [dbo].[RadioCommand]([Radio],[Timestamp])
go

CREATE INDEX [IDX_RadioCommand_Timestamp] ON [dbo].[RadioCommand]([Timestamp])
go

CREATE INDEX [IDX_RadioCommand_Reply] ON [dbo].[RadioCommand]([Reply])
go

/*
 * RadioCommandReply
 *
 */
CREATE TABLE [dbo].[RadioCommandReply]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radio] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Command] [uniqueidentifier] NOT NULL,
  [Status] [int] NOT NULL,
  [Message] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_RadioCommandReply] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_RadioCommandReply_Radio_Timestamp] ON [dbo].[RadioCommandReply]([Radio],[Timestamp])
go

CREATE INDEX [IDX_RadioCommandReply_Timestamp] ON [dbo].[RadioCommandReply]([Timestamp])
go

ALTER TABLE [dbo].[RadioCommandReply]
  ADD CONSTRAINT [UNQ_RadioCommandReply_Command] UNIQUE([Command])
go

/*
 * RadioConfiguration
 *
 */
CREATE TABLE [dbo].[RadioConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radio] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [PlaybackUrl] [nvarchar](100) NOT NULL,
  [RadioIPAddress] [nvarchar](100) NOT NULL,
  [RadioPort] [int] NOT NULL,
  [Ed137IPAddress] [nvarchar](100) NOT NULL,
  [Ed137Port] [int] NOT NULL,
  CONSTRAINT [PK_RadioConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[RadioConfiguration]
  ADD CONSTRAINT [UNQ_RadioConfiguration_Radio_Timestamp] UNIQUE([Radio],[Timestamp])
go

CREATE INDEX [IDX_RadioConfiguration_Timestamp] ON [dbo].[RadioConfiguration]([Timestamp])
go

/*
 * RadomeCommand
 *
 */
CREATE TABLE [dbo].[RadomeCommand]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radome] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DeviceCommandSourceType] [int] NOT NULL,
  [DeviceCommandSourceId] [uniqueidentifier] NOT NULL,
  [Reply] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_RadomeCommand] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_RadomeCommand_Radome_Timestamp] ON [dbo].[RadomeCommand]([Radome],[Timestamp])
go

CREATE INDEX [IDX_RadomeCommand_Timestamp] ON [dbo].[RadomeCommand]([Timestamp])
go

CREATE INDEX [IDX_RadomeCommand_Reply] ON [dbo].[RadomeCommand]([Reply])
go

/*
 * RadomeCommandReply
 *
 */
CREATE TABLE [dbo].[RadomeCommandReply]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Radome] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Command] [uniqueidentifier] NOT NULL,
  [Status] [int] NOT NULL,
  [Message] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_RadomeCommandReply] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_RadomeCommandReply_Radome_Timestamp] ON [dbo].[RadomeCommandReply]([Radome],[Timestamp])
go

CREATE INDEX [IDX_RadomeCommandReply_Timestamp] ON [dbo].[RadomeCommandReply]([Timestamp])
go

ALTER TABLE [dbo].[RadomeCommandReply]
  ADD CONSTRAINT [UNQ_RadomeCommandReply_Command] UNIQUE([Command])
go

/*
 * RadomeConfiguration
 *
 */
CREATE TABLE [dbo].[RadomeConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Configuration information for a Radome device.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Configuration information for a Radome device.
   */
  [Radome] [uniqueidentifier] NOT NULL,
  /*
   * Configuration information for a Radome device.
   */
  [Timestamp] [bigint] NOT NULL,
  /*
   * Configuration information for a Radome device.
   */
  [Interval] [bigint] NOT NULL,
  /*
   * Configuration information for a Radome device.
   */
  [LowPressureLimit] [float](53) NOT NULL,
  /*
   * Configuration information for a Radome device.
   */
  [HighPressureLimit] [float](53) NOT NULL,
  /*
   * Configuration information for a Radome device.
   */
  [LowTemperatureLimit] [float](53) NOT NULL,
  /*
   * Configuration information for a Radome device.
   */
  [HighTemperatureLimit] [float](53) NOT NULL,
  CONSTRAINT [PK_RadomeConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[RadomeConfiguration]
  ADD CONSTRAINT [UNQ_RadomeConfiguration_Radome_Timestamp] UNIQUE([Radome],[Timestamp])
go

CREATE INDEX [IDX_RadomeConfiguration_Timestamp] ON [dbo].[RadomeConfiguration]([Timestamp])
go

/*
 * ReferenceTimeseriesValue
 *
 */
CREATE TABLE [dbo].[ReferenceTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_ReferenceTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[ReferenceTimeseriesValue]
  ADD CONSTRAINT [UNQ_ReferenceTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_ReferenceTimeseriesValue_Timestamp] ON [dbo].[ReferenceTimeseriesValue]([Timestamp])
go

CREATE INDEX [IDX_ReferenceTimeseriesValue_Value] ON [dbo].[ReferenceTimeseriesValue]([Value])
go

/*
 * SByteTimeseriesValue
 *
 */
CREATE TABLE [dbo].[SByteTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [numeric](3,0) NULL,
  CONSTRAINT [PK_SByteTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[SByteTimeseriesValue]
  ADD CONSTRAINT [UNQ_SByteTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_SByteTimeseriesValue_Timestamp] ON [dbo].[SByteTimeseriesValue]([Timestamp])
go

/*
 * SecurityDomain
 *
 */
CREATE TABLE [dbo].[SecurityDomain]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Description] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_SecurityDomain] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[SecurityDomain]
  ADD CONSTRAINT [UNQ_SecurityDomain_Name] UNIQUE([Name])
go

/*
 * SecurityIdentifier
 *
 */
CREATE TABLE [dbo].[SecurityIdentifier]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between SecurityIdentifier
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  /*
   * Base class for SecurityLogin and SecurityRole. Tracks the granted permissions in the system.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Base class for SecurityLogin and SecurityRole. Tracks the granted permissions in the system.
   */
  [Domain] [uniqueidentifier] NOT NULL,
  /*
   * Base class for SecurityLogin and SecurityRole. Tracks the granted permissions in the system.
   */
  [Identity] [nvarchar](255) NOT NULL,
  /*
   * Base class for SecurityLogin and SecurityRole. Tracks the granted permissions in the system.
   */
  [Description] [nvarchar](max) NOT NULL,
  CONSTRAINT [FK_SecurityIdentifier_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_SecurityIdentifier] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[SecurityIdentifier]
  ADD CONSTRAINT [UNQ_SecurityIdentifier_Domain_Identity] UNIQUE([Domain],[Identity])
go

/*
 * SecurityLogin
 *
 * The SecurityLogin entity a descendant of the SecurityIdentifier entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SecurityLogin].[Id] field and the
 * [dbo].[SecurityIdentifier].[Id] field.
 *
 */
CREATE TABLE [dbo].[SecurityLogin]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_SecurityLogin_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[SecurityIdentifier]([Id]),
  CONSTRAINT [PK_SecurityLogin] PRIMARY KEY([Id])
)
go

/*
 * SecurityRole
 *
 * The SecurityRole entity a descendant of the SecurityIdentifier entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SecurityRole].[Id] field and the
 * [dbo].[SecurityIdentifier].[Id] field.
 *
 */
CREATE TABLE [dbo].[SecurityRole]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Base class for SecurityLogin and SecurityRole. Tracks the granted permissions in the system.
   */
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [FK_SecurityRole_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[SecurityIdentifier]([Id]),
  CONSTRAINT [PK_SecurityRole] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[SecurityRole]
  ADD CONSTRAINT [UNQ_SecurityRole_Name] UNIQUE([Name])
go

/*
 * SecurityIdentifierRoleLink
 *
 */
CREATE TABLE [dbo].[SecurityIdentifierRoleLink]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Member] [uniqueidentifier] NOT NULL,
  [Role] [uniqueidentifier] NOT NULL,
  [Start] [bigint] NOT NULL,
  [End] [bigint] NULL,
  CONSTRAINT [PK_SecurityIdentifierRoleLink] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_SecurityIdentifierRoleLink_Member_Start] ON [dbo].[SecurityIdentifierRoleLink]([Member],[Start])
go

CREATE INDEX [IDX_SecurityIdentifierRoleLink_Role_Start] ON [dbo].[SecurityIdentifierRoleLink]([Role],[Start])
go

CREATE INDEX [IDX_SecurityIdentifierRoleLink_Start] ON [dbo].[SecurityIdentifierRoleLink]([Start])
go

/*
 * SecurityLoginSession
 *
 */
CREATE TABLE [dbo].[SecurityLoginSession]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Login] [uniqueidentifier] NOT NULL,
  [FromTime] [bigint] NOT NULL,
  [ThroughTime] [bigint] NULL,
  [ClientSession] [uniqueidentifier] NOT NULL,
  [NotificationQueueName] [nvarchar](260) NOT NULL,
  [MessageQueueName] [nvarchar](260) NOT NULL,
  CONSTRAINT [PK_SecurityLoginSession] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_SecurityLoginSession_Login_FromTime] ON [dbo].[SecurityLoginSession]([Login],[FromTime])
go

CREATE INDEX [IDX_SecurityLoginSession_FromTime] ON [dbo].[SecurityLoginSession]([FromTime])
go

/*
 * SecurityPermission
 *
 */
CREATE TABLE [dbo].[SecurityPermission]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Identifier] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [TypeCode] [int] NOT NULL,
  [CanCreate] [bit] NOT NULL,
  [CanRead] [bit] NOT NULL,
  [CanUpdate] [bit] NOT NULL,
  [CanDelete] [bit] NOT NULL,
  CONSTRAINT [PK_SecurityPermission] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[SecurityPermission]
  ADD CONSTRAINT [UNQ_SecurityPermission_Identifier_TypeCode_Timestamp] UNIQUE([Identifier],[TypeCode],[Timestamp])
go

CREATE INDEX [IDX_SecurityPermission_Timestamp] ON [dbo].[SecurityPermission]([Timestamp])
go

/*
 * SingleTimeseriesValue
 *
 */
CREATE TABLE [dbo].[SingleTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [float](24) NULL,
  CONSTRAINT [PK_SingleTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[SingleTimeseriesValue]
  ADD CONSTRAINT [UNQ_SingleTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_SingleTimeseriesValue_Timestamp] ON [dbo].[SingleTimeseriesValue]([Timestamp])
go

/*
 * StringTimeseriesValue
 *
 */
CREATE TABLE [dbo].[StringTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_StringTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[StringTimeseriesValue]
  ADD CONSTRAINT [UNQ_StringTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_StringTimeseriesValue_Timestamp] ON [dbo].[StringTimeseriesValue]([Timestamp])
go

/*
 * TimeseriesCatalogElement
 *
 */
CREATE TABLE [dbo].[TimeseriesCatalogElement]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between TimeseriesCatalogElement
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Catalog] [uniqueidentifier] NOT NULL,
  [Name] [nvarchar](100) NOT NULL,
  CONSTRAINT [FK_TimeseriesCatalogElement_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_TimeseriesCatalogElement] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[TimeseriesCatalogElement]
  ADD CONSTRAINT [UNQ_TimeseriesCatalogElement_Catalog_Name] UNIQUE([Catalog],[Name])
go

/*
 * Timeseries
 *
 * The Timeseries entity a descendant of the TimeseriesCatalogElement entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Timeseries].[Id] field and the
 * [dbo].[TimeseriesCatalogElement].[Id] field.
 *
 */
CREATE TABLE [dbo].[Timeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [MaxRetention] [bigint] NOT NULL,
  CONSTRAINT [FK_Timeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesCatalogElement]([Id]),
  CONSTRAINT [PK_Timeseries] PRIMARY KEY([Id])
)
go

/*
 * BinaryTimeseries
 *
 * The BinaryTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BinaryTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[BinaryTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_BinaryTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_BinaryTimeseries] PRIMARY KEY([Id])
)
go

/*
 * BooleanTimeseries
 *
 * The BooleanTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[BooleanTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[BooleanTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_BooleanTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_BooleanTimeseries] PRIMARY KEY([Id])
)
go

/*
 * AisAidToNavigationOffPositionTimeseries
 *
 * The AisAidToNavigationOffPositionTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisAidToNavigationOffPositionTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisAidToNavigationOffPositionTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [AidToNavigation] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_AisAidToNavigationOffPositionTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_AisAidToNavigationOffPositionTimeseries] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_AisAidToNavigationOffPositionTimeseries_AidToNavigation] ON [dbo].[AisAidToNavigationOffPositionTimeseries]([AidToNavigation])
go

/*
 * DeviceEnabledTimeseries
 *
 * The DeviceEnabledTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DeviceEnabledTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[DeviceEnabledTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Tracks the Enabled state of a Device.
   */
  [Device] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_DeviceEnabledTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_DeviceEnabledTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarAutomaticSensitivityTimeControlTimeseries
 *
 * The RadarAutomaticSensitivityTimeControlTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarAutomaticSensitivityTimeControlTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarAutomaticSensitivityTimeControlTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarAutomaticSensitivityTimeControlTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_RadarAutomaticSensitivityTimeControlTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarBlankSector1Timeseries
 *
 * The RadarBlankSector1Timeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarBlankSector1Timeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarBlankSector1Timeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarBlankSector1Timeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_RadarBlankSector1Timeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarBlankSector2Timeseries
 *
 * The RadarBlankSector2Timeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarBlankSector2Timeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarBlankSector2Timeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarBlankSector2Timeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_RadarBlankSector2Timeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarEnableAutomaticFrequencyControlTimeseries
 *
 * The RadarEnableAutomaticFrequencyControlTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarEnableAutomaticFrequencyControlTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarEnableAutomaticFrequencyControlTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarEnableAutomaticFrequencyControlTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_RadarEnableAutomaticFrequencyControlTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarEnableFastTimeConstantTimeseries
 *
 * The RadarEnableFastTimeConstantTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarEnableFastTimeConstantTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarEnableFastTimeConstantTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarEnableFastTimeConstantTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_RadarEnableFastTimeConstantTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarEnableSensitivityTimeControlTimeseries
 *
 * The RadarEnableSensitivityTimeControlTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarEnableSensitivityTimeControlTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarEnableSensitivityTimeControlTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarEnableSensitivityTimeControlTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_RadarEnableSensitivityTimeControlTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarPowerOnTimeseries
 *
 * The RadarPowerOnTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarPowerOnTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarPowerOnTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarPowerOnTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_RadarPowerOnTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarSaveSettingsTimeseries
 *
 * The RadarSaveSettingsTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarSaveSettingsTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarSaveSettingsTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarSaveSettingsTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_RadarSaveSettingsTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarTrackingTimeseries
 *
 * The RadarTrackingTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarTrackingTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarTrackingTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarTrackingTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_RadarTrackingTimeseries] PRIMARY KEY([Id])
)
go

/*
 * MediaProxySessionEnabledTimeseries
 *
 * The MediaProxySessionEnabledTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[MediaProxySessionEnabledTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[MediaProxySessionEnabledTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Tracks the Enabled state of a Media Proxy Session.
   */
  [ProxySession] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_MediaProxySessionEnabledTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_MediaProxySessionEnabledTimeseries] PRIMARY KEY([Id])
)
go

/*
 * MediaServiceEnabledTimeseries
 *
 * The MediaServiceEnabledTimeseries entity a descendant of the BooleanTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[MediaServiceEnabledTimeseries].[Id] field and the
 * [dbo].[BooleanTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[MediaServiceEnabledTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Tracks the Enabled state of the Media Service.
   */
  [Service] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_MediaServiceEnabledTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[BooleanTimeseries]([Id]),
  CONSTRAINT [PK_MediaServiceEnabledTimeseries] PRIMARY KEY([Id])
)
go

/*
 * ByteTimeseries
 *
 * The ByteTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ByteTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[ByteTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_ByteTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_ByteTimeseries] PRIMARY KEY([Id])
)
go

/*
 * DateTimeTimeseries
 *
 * The DateTimeTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DateTimeTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[DateTimeTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_DateTimeTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_DateTimeTimeseries] PRIMARY KEY([Id])
)
go

/*
 * DoubleTimeseries
 *
 * The DoubleTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[DoubleTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[DoubleTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_DoubleTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_DoubleTimeseries] PRIMARY KEY([Id])
)
go

/*
 * GNSSAltitudeTimeseries
 *
 * The GNSSAltitudeTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GNSSAltitudeTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GNSSAltitudeTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [GNSSDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GNSSAltitudeTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_GNSSAltitudeTimeseries] PRIMARY KEY([Id])
)
go

/*
 * GNSSLatitudeTimeseries
 *
 * The GNSSLatitudeTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GNSSLatitudeTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GNSSLatitudeTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [GNSSDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GNSSLatitudeTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_GNSSLatitudeTimeseries] PRIMARY KEY([Id])
)
go

/*
 * GNSSLongitudeTimeseries
 *
 * The GNSSLongitudeTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GNSSLongitudeTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GNSSLongitudeTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [GNSSDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GNSSLongitudeTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_GNSSLongitudeTimeseries] PRIMARY KEY([Id])
)
go

/*
 * GyroCourseTimeseries
 *
 * The GyroCourseTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GyroCourseTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GyroCourseTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [GyroDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GyroCourseTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_GyroCourseTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GyroCourseTimeseries]
  ADD CONSTRAINT [UNQ_GyroCourseTimeseries_GyroDevice] UNIQUE([GyroDevice])
go

/*
 * GyroHeadingMagneticNorthTimeseries
 *
 * The GyroHeadingMagneticNorthTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GyroHeadingMagneticNorthTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GyroHeadingMagneticNorthTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [GyroDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GyroHeadingMagneticNorthTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_GyroHeadingMagneticNorthTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GyroHeadingMagneticNorthTimeseries]
  ADD CONSTRAINT [UNQ_GyroHeadingMagneticNorthTimeseries_GyroDevice] UNIQUE([GyroDevice])
go

/*
 * GyroHeadingTrueNorthTimeseries
 *
 * The GyroHeadingTrueNorthTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GyroHeadingTrueNorthTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GyroHeadingTrueNorthTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [GyroDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GyroHeadingTrueNorthTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_GyroHeadingTrueNorthTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GyroHeadingTrueNorthTimeseries]
  ADD CONSTRAINT [UNQ_GyroHeadingTrueNorthTimeseries_GyroDevice] UNIQUE([GyroDevice])
go

/*
 * GyroPitchTimeseries
 *
 * The GyroPitchTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GyroPitchTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GyroPitchTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [GyroDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GyroPitchTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_GyroPitchTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GyroPitchTimeseries]
  ADD CONSTRAINT [UNQ_GyroPitchTimeseries_GyroDevice] UNIQUE([GyroDevice])
go

/*
 * GyroRateOfTurnTimeseries
 *
 * The GyroRateOfTurnTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GyroRateOfTurnTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GyroRateOfTurnTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [GyroDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GyroRateOfTurnTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_GyroRateOfTurnTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GyroRateOfTurnTimeseries]
  ADD CONSTRAINT [UNQ_GyroRateOfTurnTimeseries_GyroDevice] UNIQUE([GyroDevice])
go

/*
 * GyroRollTimeseries
 *
 * The GyroRollTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GyroRollTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GyroRollTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [GyroDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GyroRollTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_GyroRollTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GyroRollTimeseries]
  ADD CONSTRAINT [UNQ_GyroRollTimeseries_GyroDevice] UNIQUE([GyroDevice])
go

/*
 * GyroSpeedTimeseries
 *
 * The GyroSpeedTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GyroSpeedTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GyroSpeedTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [GyroDevice] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_GyroSpeedTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_GyroSpeedTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[GyroSpeedTimeseries]
  ADD CONSTRAINT [UNQ_GyroSpeedTimeseries_GyroDevice] UNIQUE([GyroDevice])
go

/*
 * RadarLatitudeTimeseries
 *
 * The RadarLatitudeTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarLatitudeTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarLatitudeTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarLatitudeTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_RadarLatitudeTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarLongitudeTimeseries
 *
 * The RadarLongitudeTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarLongitudeTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarLongitudeTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarLongitudeTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_RadarLongitudeTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadomeDewPointTimeseries
 *
 * The RadomeDewPointTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadomeDewPointTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadomeDewPointTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Tracks the Dew Point of a Radome.
   */
  [Radome] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadomeDewPointTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_RadomeDewPointTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadomePressureTimeseries
 *
 * The RadomePressureTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadomePressureTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadomePressureTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Tracks the Pressure of a Radome.
   */
  [Radome] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadomePressureTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_RadomePressureTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadomeTemperatureTimeseries
 *
 * The RadomeTemperatureTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadomeTemperatureTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadomeTemperatureTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Tracks the Temperature of a Radome.
   */
  [Radome] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadomeTemperatureTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_RadomeTemperatureTimeseries] PRIMARY KEY([Id])
)
go

/*
 * VesselDraughtTimeseries
 *
 * The VesselDraughtTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[VesselDraughtTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[VesselDraughtTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Vessel] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_VesselDraughtTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_VesselDraughtTimeseries] PRIMARY KEY([Id])
)
go

/*
 * ViewLatitudeTimeseries
 *
 * The ViewLatitudeTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ViewLatitudeTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[ViewLatitudeTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [View] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_ViewLatitudeTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_ViewLatitudeTimeseries] PRIMARY KEY([Id])
)
go

/*
 * ViewLongitudeTimeseries
 *
 * The ViewLongitudeTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ViewLongitudeTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[ViewLongitudeTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [View] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_ViewLongitudeTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_ViewLongitudeTimeseries] PRIMARY KEY([Id])
)
go

/*
 * ViewZoomLevelTimeseries
 *
 * The ViewZoomLevelTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ViewZoomLevelTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[ViewZoomLevelTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [View] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_ViewZoomLevelTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_ViewZoomLevelTimeseries] PRIMARY KEY([Id])
)
go

/*
 * WeatherStationAbsoluteHumidityTimeseries
 *
 * The WeatherStationAbsoluteHumidityTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[WeatherStationAbsoluteHumidityTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[WeatherStationAbsoluteHumidityTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_WeatherStationAbsoluteHumidityTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_WeatherStationAbsoluteHumidityTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[WeatherStationAbsoluteHumidityTimeseries]
  ADD CONSTRAINT [UNQ_WeatherStationAbsoluteHumidityTimeseries_WeatherStation] UNIQUE([WeatherStation])
go

/*
 * WeatherStationAirTemperatureTimeseries
 *
 * The WeatherStationAirTemperatureTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[WeatherStationAirTemperatureTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[WeatherStationAirTemperatureTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_WeatherStationAirTemperatureTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_WeatherStationAirTemperatureTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[WeatherStationAirTemperatureTimeseries]
  ADD CONSTRAINT [UNQ_WeatherStationAirTemperatureTimeseries_WeatherStation] UNIQUE([WeatherStation])
go

/*
 * WeatherStationBarometricPressureTimeseries
 *
 * The WeatherStationBarometricPressureTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[WeatherStationBarometricPressureTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[WeatherStationBarometricPressureTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_WeatherStationBarometricPressureTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_WeatherStationBarometricPressureTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[WeatherStationBarometricPressureTimeseries]
  ADD CONSTRAINT [UNQ_WeatherStationBarometricPressureTimeseries_WeatherStation] UNIQUE([WeatherStation])
go

/*
 * WeatherStationDewPointTimeseries
 *
 * The WeatherStationDewPointTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[WeatherStationDewPointTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[WeatherStationDewPointTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_WeatherStationDewPointTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_WeatherStationDewPointTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[WeatherStationDewPointTimeseries]
  ADD CONSTRAINT [UNQ_WeatherStationDewPointTimeseries_WeatherStation] UNIQUE([WeatherStation])
go

/*
 * WeatherStationRelativeHumidityTimeseries
 *
 * The WeatherStationRelativeHumidityTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[WeatherStationRelativeHumidityTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[WeatherStationRelativeHumidityTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_WeatherStationRelativeHumidityTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_WeatherStationRelativeHumidityTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[WeatherStationRelativeHumidityTimeseries]
  ADD CONSTRAINT [UNQ_WeatherStationRelativeHumidityTimeseries_WeatherStation] UNIQUE([WeatherStation])
go

/*
 * WeatherStationWaterTemperatureTimeseries
 *
 * The WeatherStationWaterTemperatureTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[WeatherStationWaterTemperatureTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[WeatherStationWaterTemperatureTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_WeatherStationWaterTemperatureTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_WeatherStationWaterTemperatureTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[WeatherStationWaterTemperatureTimeseries]
  ADD CONSTRAINT [UNQ_WeatherStationWaterTemperatureTimeseries_WeatherStation] UNIQUE([WeatherStation])
go

/*
 * WeatherStationWindDirectionTimeseries
 *
 * The WeatherStationWindDirectionTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[WeatherStationWindDirectionTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[WeatherStationWindDirectionTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_WeatherStationWindDirectionTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_WeatherStationWindDirectionTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[WeatherStationWindDirectionTimeseries]
  ADD CONSTRAINT [UNQ_WeatherStationWindDirectionTimeseries_WeatherStation] UNIQUE([WeatherStation])
go

/*
 * WeatherStationWindSpeedTimeseries
 *
 * The WeatherStationWindSpeedTimeseries entity a descendant of the DoubleTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[WeatherStationWindSpeedTimeseries].[Id] field and the
 * [dbo].[DoubleTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[WeatherStationWindSpeedTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_WeatherStationWindSpeedTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[DoubleTimeseries]([Id]),
  CONSTRAINT [PK_WeatherStationWindSpeedTimeseries] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[WeatherStationWindSpeedTimeseries]
  ADD CONSTRAINT [UNQ_WeatherStationWindSpeedTimeseries_WeatherStation] UNIQUE([WeatherStation])
go

/*
 * GeoPosition2DTimeseries
 *
 * The GeoPosition2DTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GeoPosition2DTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GeoPosition2DTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_GeoPosition2DTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_GeoPosition2DTimeseries] PRIMARY KEY([Id])
)
go

/*
 * AisAidToNavigationPositionTimeseries
 *
 * The AisAidToNavigationPositionTimeseries entity a descendant of the GeoPosition2DTimeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[AisAidToNavigationPositionTimeseries].[Id] field and the
 * [dbo].[GeoPosition2DTimeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[AisAidToNavigationPositionTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [AidToNavigation] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_AisAidToNavigationPositionTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[GeoPosition2DTimeseries]([Id]),
  CONSTRAINT [PK_AisAidToNavigationPositionTimeseries] PRIMARY KEY([Id])
)
go

/*
 * GeoPosition3DTimeseries
 *
 * The GeoPosition3DTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GeoPosition3DTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GeoPosition3DTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_GeoPosition3DTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_GeoPosition3DTimeseries] PRIMARY KEY([Id])
)
go

/*
 * GuidTimeseries
 *
 * The GuidTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[GuidTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[GuidTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_GuidTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_GuidTimeseries] PRIMARY KEY([Id])
)
go

/*
 * Int16Timeseries
 *
 * The Int16Timeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int16Timeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int16Timeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_Int16Timeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_Int16Timeseries] PRIMARY KEY([Id])
)
go

/*
 * Int32Timeseries
 *
 * The Int32Timeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int32Timeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int32Timeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_Int32Timeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_Int32Timeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarAzimuthOffsetTimeseries
 *
 * The RadarAzimuthOffsetTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarAzimuthOffsetTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarAzimuthOffsetTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarAzimuthOffsetTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_RadarAzimuthOffsetTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarFastTimeConstantLevelTimeseries
 *
 * The RadarFastTimeConstantLevelTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarFastTimeConstantLevelTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarFastTimeConstantLevelTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarFastTimeConstantLevelTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_RadarFastTimeConstantLevelTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarFastTimeConstantModeTimeseries
 *
 * The RadarFastTimeConstantModeTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarFastTimeConstantModeTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarFastTimeConstantModeTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarFastTimeConstantModeTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_RadarFastTimeConstantModeTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarPulseTimeseries
 *
 * The RadarPulseTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarPulseTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarPulseTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarPulseTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_RadarPulseTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarSector1EndTimeseries
 *
 * The RadarSector1EndTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarSector1EndTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarSector1EndTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarSector1EndTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_RadarSector1EndTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarSector1StartTimeseries
 *
 * The RadarSector1StartTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarSector1StartTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarSector1StartTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarSector1StartTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_RadarSector1StartTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarSector2EndTimeseries
 *
 * The RadarSector2EndTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarSector2EndTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarSector2EndTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarSector2EndTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_RadarSector2EndTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarSector2StartTimeseries
 *
 * The RadarSector2StartTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarSector2StartTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarSector2StartTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarSector2StartTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_RadarSector2StartTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarSensitivityTimeControlLevelTimeseries
 *
 * The RadarSensitivityTimeControlLevelTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarSensitivityTimeControlLevelTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarSensitivityTimeControlLevelTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarSensitivityTimeControlLevelTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_RadarSensitivityTimeControlLevelTimeseries] PRIMARY KEY([Id])
)
go

/*
 * RadarTuningTimeseries
 *
 * The RadarTuningTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadarTuningTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadarTuningTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radar] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadarTuningTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_RadarTuningTimeseries] PRIMARY KEY([Id])
)
go

/*
 * VesselPersonsOnBoardTimeseries
 *
 * The VesselPersonsOnBoardTimeseries entity a descendant of the Int32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[VesselPersonsOnBoardTimeseries].[Id] field and the
 * [dbo].[Int32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[VesselPersonsOnBoardTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Vessel] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_VesselPersonsOnBoardTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Int32Timeseries]([Id]),
  CONSTRAINT [PK_VesselPersonsOnBoardTimeseries] PRIMARY KEY([Id])
)
go

/*
 * Int64Timeseries
 *
 * The Int64Timeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Int64Timeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[Int64Timeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_Int64Timeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_Int64Timeseries] PRIMARY KEY([Id])
)
go

/*
 * Position2DTimeseries
 *
 * The Position2DTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Position2DTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[Position2DTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_Position2DTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_Position2DTimeseries] PRIMARY KEY([Id])
)
go

/*
 * Position3DTimeseries
 *
 * The Position3DTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Position3DTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[Position3DTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_Position3DTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_Position3DTimeseries] PRIMARY KEY([Id])
)
go

/*
 * ReferenceTimeseries
 *
 * The ReferenceTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[ReferenceTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[ReferenceTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_ReferenceTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_ReferenceTimeseries] PRIMARY KEY([Id])
)
go

/*
 * SByteTimeseries
 *
 * The SByteTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SByteTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[SByteTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_SByteTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_SByteTimeseries] PRIMARY KEY([Id])
)
go

/*
 * SingleTimeseries
 *
 * The SingleTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[SingleTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[SingleTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_SingleTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_SingleTimeseries] PRIMARY KEY([Id])
)
go

/*
 * StringTimeseries
 *
 * The StringTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[StringTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[StringTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_StringTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_StringTimeseries] PRIMARY KEY([Id])
)
go

/*
 * TimeSpanTimeseries
 *
 * The TimeSpanTimeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[TimeSpanTimeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[TimeSpanTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_TimeSpanTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_TimeSpanTimeseries] PRIMARY KEY([Id])
)
go

/*
 * UInt16Timeseries
 *
 * The UInt16Timeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt16Timeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt16Timeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_UInt16Timeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_UInt16Timeseries] PRIMARY KEY([Id])
)
go

/*
 * UInt32Timeseries
 *
 * The UInt32Timeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt32Timeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt32Timeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_UInt32Timeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_UInt32Timeseries] PRIMARY KEY([Id])
)
go

/*
 * RadomeStatusTimeseries
 *
 * The RadomeStatusTimeseries entity a descendant of the UInt32Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[RadomeStatusTimeseries].[Id] field and the
 * [dbo].[UInt32Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[RadomeStatusTimeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Tracks the Status of a Radome.
   */
  [Radome] [uniqueidentifier] NOT NULL,
  CONSTRAINT [FK_RadomeStatusTimeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[UInt32Timeseries]([Id]),
  CONSTRAINT [PK_RadomeStatusTimeseries] PRIMARY KEY([Id])
)
go

/*
 * UInt64Timeseries
 *
 * The UInt64Timeseries entity a descendant of the Timeseries entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[UInt64Timeseries].[Id] field and the
 * [dbo].[Timeseries].[Id] field.
 *
 */
CREATE TABLE [dbo].[UInt64Timeseries]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_UInt64Timeseries_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Timeseries]([Id]),
  CONSTRAINT [PK_UInt64Timeseries] PRIMARY KEY([Id])
)
go

/*
 * TimeseriesCatalog
 *
 * The TimeseriesCatalog entity a descendant of the TimeseriesCatalogElement entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[TimeseriesCatalog].[Id] field and the
 * [dbo].[TimeseriesCatalogElement].[Id] field.
 *
 */
CREATE TABLE [dbo].[TimeseriesCatalog]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_TimeseriesCatalog_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TimeseriesCatalogElement]([Id]),
  CONSTRAINT [PK_TimeseriesCatalog] PRIMARY KEY([Id])
)
go

/*
 * TimeseriesInfo
 *
 */
CREATE TABLE [dbo].[TimeseriesInfo]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [FirstTimestamp] [bigint] NULL,
  [LastTimestamp] [bigint] NULL,
  [Count] [bigint] NOT NULL,
  CONSTRAINT [PK_TimeseriesInfo] PRIMARY KEY([Id])
)
go

/*
 * TimeSpanTimeseriesValue
 *
 */
CREATE TABLE [dbo].[TimeSpanTimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [bigint] NULL,
  CONSTRAINT [PK_TimeSpanTimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[TimeSpanTimeseriesValue]
  ADD CONSTRAINT [UNQ_TimeSpanTimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_TimeSpanTimeseriesValue_Timestamp] ON [dbo].[TimeSpanTimeseriesValue]([Timestamp])
go

/*
 * TrackableItemTrackLink
 *
 */
CREATE TABLE [dbo].[TrackableItemTrackLink]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Item] [uniqueidentifier] NOT NULL,
  [Track] [uniqueidentifier] NOT NULL,
  [Start] [bigint] NOT NULL,
  [End] [bigint] NULL,
  CONSTRAINT [PK_TrackableItemTrackLink] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[TrackableItemTrackLink]
  ADD CONSTRAINT [UNQ_TrackableItemTrackLink_Item_Start] UNIQUE([Item],[Start])
go

CREATE INDEX [IDX_TrackableItemTrackLink_Item_End] ON [dbo].[TrackableItemTrackLink]([Item],[End])
go

ALTER TABLE [dbo].[TrackableItemTrackLink]
  ADD CONSTRAINT [UNQ_TrackableItemTrackLink_Track_Start] UNIQUE([Track],[Start])
go

CREATE INDEX [IDX_TrackableItemTrackLink_Track_End] ON [dbo].[TrackableItemTrackLink]([Track],[End])
go

CREATE INDEX [IDX_TrackableItemTrackLink_Start] ON [dbo].[TrackableItemTrackLink]([Start])
go

/*
 * TrackBase
 *
 */
CREATE TABLE [dbo].[TrackBase]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between TrackBase
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Tracker] [uniqueidentifier] NOT NULL,
  [TrackNumber] [bigint] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  CONSTRAINT [FK_TrackBase_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_TrackBase] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[TrackBase]
  ADD CONSTRAINT [UNQ_TrackBase_Tracker_TrackNumber_Timestamp] UNIQUE([Tracker],[TrackNumber],[Timestamp])
go

CREATE INDEX [IDX_TrackBase_Tracker_Timestamp] ON [dbo].[TrackBase]([Tracker],[Timestamp])
go

CREATE INDEX [IDX_TrackBase_TrackNumber] ON [dbo].[TrackBase]([TrackNumber])
go

CREATE INDEX [IDX_TrackBase_Timestamp] ON [dbo].[TrackBase]([Timestamp])
go

/*
 * Track
 *
 * The Track entity a descendant of the TrackBase entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Track].[Id] field and the
 * [dbo].[TrackBase].[Id] field.
 *
 */
CREATE TABLE [dbo].[Track]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_Track_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TrackBase]([Id]),
  CONSTRAINT [PK_Track] PRIMARY KEY([Id])
)
go

/*
 * Track3D
 *
 * The Track3D entity a descendant of the TrackBase entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[Track3D].[Id] field and the
 * [dbo].[TrackBase].[Id] field.
 *
 */
CREATE TABLE [dbo].[Track3D]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  CONSTRAINT [FK_Track3D_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[TrackBase]([Id]),
  CONSTRAINT [PK_Track3D] PRIMARY KEY([Id])
)
go

/*
 * TrackerFilterParameters
 *
 */
CREATE TABLE [dbo].[TrackerFilterParameters]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Tracker] [uniqueidentifier] NOT NULL,
  [Name] [nvarchar](100) NOT NULL,
  CONSTRAINT [PK_TrackerFilterParameters] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[TrackerFilterParameters]
  ADD CONSTRAINT [UNQ_TrackerFilterParameters_Tracker_Name] UNIQUE([Tracker],[Name])
go

/*
 * TrackerFilterParametersConfiguration
 *
 */
CREATE TABLE [dbo].[TrackerFilterParametersConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [RowVersion] [bigint] NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [Parameters] [uniqueidentifier] NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [Timestamp] [bigint] NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [UseNaivePredictor] [bit] NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [NumberOfPoints] [int] NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [WindowSize] [int] NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [StabilizeCount] [int] NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [MaxBadPoints] [int] NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [ModelType] [int] NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [SigmaR] [float](53) NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [SigmaAcc] [float](53) NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [TauVel] [float](53) NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [TauAcc] [float](53) NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [DeltaRMin] [float](53) NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [DeltaVMax] [float](53) NOT NULL,
  /*
   * Configuration information for the Tracker Filter Parameters element.
   */
  [DeltaAMax] [float](53) NOT NULL,
  CONSTRAINT [PK_TrackerFilterParametersConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[TrackerFilterParametersConfiguration]
  ADD CONSTRAINT [UNQ_TrackerFilterParametersConfiguration_Parameters_Timestamp] UNIQUE([Parameters],[Timestamp])
go

CREATE INDEX [IDX_TrackerFilterParametersConfiguration_Timestamp] ON [dbo].[TrackerFilterParametersConfiguration]([Timestamp])
go

/*
 * TrackInfo
 *
 */
CREATE TABLE [dbo].[TrackInfo]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [FirstTimestamp] [bigint] NULL,
  [LastTimestamp] [bigint] NULL,
  [Count] [bigint] NOT NULL,
  [NorthWestLatitude] [float](53) NULL,
  [NorthWestLongitude] [float](53) NULL,
  [SouthEastLatitude] [float](53) NULL,
  [SouthEastLongitude] [float](53) NULL,
  CONSTRAINT [PK_TrackInfo] PRIMARY KEY([Id])
)
go

/*
 * TrackingServiceOptions
 *
 */
CREATE TABLE [dbo].[TrackingServiceOptions]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [TimerInterval] [bigint] NOT NULL,
  [MaxAgeOfCurrentTrackValue] [bigint] NOT NULL,
  [FalseThreshold] [float](53) NOT NULL,
  [DistanceThreshold] [float](53) NOT NULL,
  [DistanceUnmergeThreshold] [float](53) NOT NULL,
  [UnmergeLatency] [bigint] NOT NULL,
  [KalmanFiltering] [bit] NOT NULL,
  [MaxCourseDeviation] [float](53) NOT NULL,
  [MaxSpeedDeviation] [float](53) NOT NULL,
  [MinimumSpeedThreshold] [float](53) NOT NULL,
  CONSTRAINT [PK_TrackingServiceOptions] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[TrackingServiceOptions]
  ADD CONSTRAINT [UNQ_TrackingServiceOptions_Timestamp] UNIQUE([Timestamp])
go

/*
 * TrackLink
 *
 */
CREATE TABLE [dbo].[TrackLink]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Primary] [uniqueidentifier] NOT NULL,
  [Secondary] [uniqueidentifier] NOT NULL,
  [Start] [bigint] NOT NULL,
  [End] [bigint] NULL,
  CONSTRAINT [PK_TrackLink] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_TrackLink_Primary_Start] ON [dbo].[TrackLink]([Primary],[Start])
go

CREATE INDEX [IDX_TrackLink_Secondary_Start] ON [dbo].[TrackLink]([Secondary],[Start])
go

CREATE INDEX [IDX_TrackLink_Start] ON [dbo].[TrackLink]([Start])
go

/*
 * TrackValue
 *
 */
CREATE TABLE [dbo].[TrackValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Track] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Flags] [int] NOT NULL,
  [Status] [int] NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Speed] [float](53) NOT NULL,
  [Course] [float](53) NOT NULL,
  [Heading] [float](53) NOT NULL,
  CONSTRAINT [PK_TrackValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[TrackValue]
  ADD CONSTRAINT [UNQ_TrackValue_Track_Timestamp] UNIQUE([Track],[Timestamp])
go

CREATE INDEX [IDX_TrackValue_Timestamp] ON [dbo].[TrackValue]([Timestamp])
go

/*
 * TrackValue3D
 *
 */
CREATE TABLE [dbo].[TrackValue3D]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Track] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Flags] [int] NOT NULL,
  [Status] [numeric](10,0) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Altitude] [float](53) NOT NULL,
  [Speed] [float](53) NOT NULL,
  [Course] [float](53) NOT NULL,
  [RateOfClimb] [float](53) NOT NULL,
  CONSTRAINT [PK_TrackValue3D] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[TrackValue3D]
  ADD CONSTRAINT [UNQ_TrackValue3D_Track_Timestamp] UNIQUE([Track],[Timestamp])
go

CREATE INDEX [IDX_TrackValue3D_Timestamp] ON [dbo].[TrackValue3D]([Timestamp])
go

/*
 * UInt16TimeseriesValue
 *
 */
CREATE TABLE [dbo].[UInt16TimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [numeric](5,0) NULL,
  CONSTRAINT [PK_UInt16TimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[UInt16TimeseriesValue]
  ADD CONSTRAINT [UNQ_UInt16TimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_UInt16TimeseriesValue_Timestamp] ON [dbo].[UInt16TimeseriesValue]([Timestamp])
go

/*
 * UInt32TimeseriesValue
 *
 */
CREATE TABLE [dbo].[UInt32TimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [numeric](10,0) NULL,
  CONSTRAINT [PK_UInt32TimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[UInt32TimeseriesValue]
  ADD CONSTRAINT [UNQ_UInt32TimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_UInt32TimeseriesValue_Timestamp] ON [dbo].[UInt32TimeseriesValue]([Timestamp])
go

/*
 * UInt64TimeseriesValue
 *
 */
CREATE TABLE [dbo].[UInt64TimeseriesValue]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Timeseries] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Value] [bigint] NULL,
  CONSTRAINT [PK_UInt64TimeseriesValue] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[UInt64TimeseriesValue]
  ADD CONSTRAINT [UNQ_UInt64TimeseriesValue_Timeseries_Timestamp] UNIQUE([Timeseries],[Timestamp])
go

CREATE INDEX [IDX_UInt64TimeseriesValue_Timestamp] ON [dbo].[UInt64TimeseriesValue]([Timestamp])
go

/*
 * VehicleType
 *
 */
CREATE TABLE [dbo].[VehicleType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  CONSTRAINT [PK_VehicleType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[VehicleType]
  ADD CONSTRAINT [UNQ_VehicleType_Name] UNIQUE([Name])
go

/*
 * VesselType
 *
 */
CREATE TABLE [dbo].[VesselType]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Code] [int] NOT NULL,
  CONSTRAINT [PK_VesselType] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[VesselType]
  ADD CONSTRAINT [UNQ_VesselType_Name] UNIQUE([Name])
go

ALTER TABLE [dbo].[VesselType]
  ADD CONSTRAINT [UNQ_VesselType_Code] UNIQUE([Code])
go

/*
 * View
 *
 */
CREATE TABLE [dbo].[View]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [LatitudeTimeseries] [uniqueidentifier] NOT NULL,
  [LongitudeTimeseries] [uniqueidentifier] NOT NULL,
  [ZoomLevelTimeseries] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_View] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[View]
  ADD CONSTRAINT [UNQ_View_Name] UNIQUE([Name])
go

/*
 * ViewCameraLink
 *
 */
CREATE TABLE [dbo].[ViewCameraLink]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [View] [uniqueidentifier] NOT NULL,
  [Camera] [uniqueidentifier] NOT NULL,
  [Start] [bigint] NOT NULL,
  [End] [bigint] NULL,
  CONSTRAINT [PK_ViewCameraLink] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[ViewCameraLink]
  ADD CONSTRAINT [UNQ_ViewCameraLink_View_Start] UNIQUE([View],[Start])
go

ALTER TABLE [dbo].[ViewCameraLink]
  ADD CONSTRAINT [UNQ_ViewCameraLink_Camera_Start] UNIQUE([Camera],[Start])
go

CREATE INDEX [IDX_ViewCameraLink_Start] ON [dbo].[ViewCameraLink]([Start])
go

/*
 * ViewTrackerLink
 *
 */
CREATE TABLE [dbo].[ViewTrackerLink]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [View] [uniqueidentifier] NOT NULL,
  [Tracker] [uniqueidentifier] NOT NULL,
  [Start] [bigint] NOT NULL,
  [End] [bigint] NULL,
  CONSTRAINT [PK_ViewTrackerLink] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[ViewTrackerLink]
  ADD CONSTRAINT [UNQ_ViewTrackerLink_View_Start] UNIQUE([View],[Start])
go

ALTER TABLE [dbo].[ViewTrackerLink]
  ADD CONSTRAINT [UNQ_ViewTrackerLink_Tracker_Start] UNIQUE([Tracker],[Start])
go

CREATE INDEX [IDX_ViewTrackerLink_Start] ON [dbo].[ViewTrackerLink]([Start])
go

/*
 * WeatherStationCommand
 *
 */
CREATE TABLE [dbo].[WeatherStationCommand]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [DeviceCommandSourceType] [int] NOT NULL,
  [DeviceCommandSourceId] [uniqueidentifier] NOT NULL,
  [Reply] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_WeatherStationCommand] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_WeatherStationCommand_WeatherStation_Timestamp] ON [dbo].[WeatherStationCommand]([WeatherStation],[Timestamp])
go

CREATE INDEX [IDX_WeatherStationCommand_Timestamp] ON [dbo].[WeatherStationCommand]([Timestamp])
go

CREATE INDEX [IDX_WeatherStationCommand_Reply] ON [dbo].[WeatherStationCommand]([Reply])
go

/*
 * WeatherStationCommandReply
 *
 */
CREATE TABLE [dbo].[WeatherStationCommandReply]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Command] [uniqueidentifier] NOT NULL,
  [Status] [int] NOT NULL,
  [Message] [nvarchar](max) NOT NULL,
  CONSTRAINT [PK_WeatherStationCommandReply] PRIMARY KEY([Id])
)
go

CREATE INDEX [IDX_WeatherStationCommandReply_WeatherStation_Timestamp] ON [dbo].[WeatherStationCommandReply]([WeatherStation],[Timestamp])
go

CREATE INDEX [IDX_WeatherStationCommandReply_Timestamp] ON [dbo].[WeatherStationCommandReply]([Timestamp])
go

ALTER TABLE [dbo].[WeatherStationCommandReply]
  ADD CONSTRAINT [UNQ_WeatherStationCommandReply_Command] UNIQUE([Command])
go

/*
 * WeatherStationConfiguration
 *
 */
CREATE TABLE [dbo].[WeatherStationConfiguration]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [WeatherStation] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [NoDataTimeOut] [bigint] NOT NULL,
  [SendInterval] [bigint] NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [GyroOffset] [float](53) NOT NULL,
  [EnableAveraging] [bit] NOT NULL,
  [AveragingInterval] [bigint] NOT NULL,
  CONSTRAINT [PK_WeatherStationConfiguration] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[WeatherStationConfiguration]
  ADD CONSTRAINT [UNQ_WeatherStationConfiguration_WeatherStation_Timestamp] UNIQUE([WeatherStation],[Timestamp])
go

CREATE INDEX [IDX_WeatherStationConfiguration_Timestamp] ON [dbo].[WeatherStationConfiguration]([Timestamp])
go

/*
 * Zone
 *
 */
CREATE TABLE [dbo].[Zone]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  /*
   * [EntityType] discriminates between Zone
   * derived entity types.
   */
  [EntityType] [int] NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Name] [nvarchar](127) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [AlarmType] [int] NOT NULL,
  [AlarmTime] [bigint] NOT NULL,
  [RadarTrackMinimumLifetime] [bigint] NOT NULL,
  [Speed] [float](53) NOT NULL,
  [StrokeColor] [numeric](10,0) NOT NULL,
  [FillColor] [numeric](10,0) NOT NULL,
  CONSTRAINT [FK_Zone_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),
  CONSTRAINT [PK_Zone] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[Zone]
  ADD CONSTRAINT [UNQ_Zone_Name] UNIQUE([Name])
go

/*
 * CircularZone
 *
 * The CircularZone entity a descendant of the Zone entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[CircularZone].[Id] field and the
 * [dbo].[Zone].[Id] field.
 *
 */
CREATE TABLE [dbo].[CircularZone]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Radius] [float](53) NOT NULL,
  CONSTRAINT [FK_CircularZone_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Zone]([Id]),
  CONSTRAINT [PK_CircularZone] PRIMARY KEY([Id])
)
go

/*
 * PolygonZone
 *
 * The PolygonZone entity a descendant of the Zone entity.
 *
 * Hence the one-to-one relationship between the 
 * [dbo].[PolygonZone].[Id] field and the
 * [dbo].[Zone].[Id] field.
 *
 */
CREATE TABLE [dbo].[PolygonZone]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [Polygon] [varbinary](max) NOT NULL,
  CONSTRAINT [FK_PolygonZone_Id] FOREIGN KEY([Id]) REFERENCES [dbo].[Zone]([Id]),
  CONSTRAINT [PK_PolygonZone] PRIMARY KEY([Id])
)
go

/*
 * ZoneExceptions
 *
 */
CREATE TABLE [dbo].[ZoneExceptions]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Zone] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  CONSTRAINT [PK_ZoneExceptions] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[ZoneExceptions]
  ADD CONSTRAINT [UNQ_ZoneExceptions_Zone_Timestamp] UNIQUE([Zone],[Timestamp])
go

CREATE INDEX [IDX_ZoneExceptions_Timestamp] ON [dbo].[ZoneExceptions]([Timestamp])
go

/*
 * ZoneExceptionsVesselLink
 *
 */
CREATE TABLE [dbo].[ZoneExceptionsVesselLink]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [ZoneExceptions] [uniqueidentifier] NOT NULL,
  [Vessel] [uniqueidentifier] NOT NULL,
  CONSTRAINT [PK_ZoneExceptionsVesselLink] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[ZoneExceptionsVesselLink]
  ADD CONSTRAINT [UNQ_ZoneExceptionsVesselLink_ZoneExceptions_Vessel] UNIQUE([ZoneExceptions],[Vessel])
go

CREATE INDEX [IDX_ZoneExceptionsVesselLink_Vessel] ON [dbo].[ZoneExceptionsVesselLink]([Vessel])
go

/*
 * ZoneTrackAlarm
 *
 */
CREATE TABLE [dbo].[ZoneTrackAlarm]
(
  [Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
  [RowVersion] [bigint] NOT NULL,
  [Track] [uniqueidentifier] NOT NULL,
  [Zone] [uniqueidentifier] NOT NULL,
  [RadarTrack] [uniqueidentifier] NOT NULL,
  [Timestamp] [bigint] NOT NULL,
  [Latitude] [float](53) NOT NULL,
  [Longitude] [float](53) NOT NULL,
  [Speed] [float](53) NOT NULL,
  [Course] [float](53) NULL,
  [Heading] [float](53) NULL,
  [EnterLatitude] [float](53) NOT NULL,
  [EnterLongitude] [float](53) NOT NULL,
  [LeaveLatitude] [float](53) NULL,
  [LeaveLongitude] [float](53) NULL,
  CONSTRAINT [PK_ZoneTrackAlarm] PRIMARY KEY([Id])
)
go

ALTER TABLE [dbo].[ZoneTrackAlarm]
  ADD CONSTRAINT [UNQ_ZoneTrackAlarm_Track_Timestamp] UNIQUE([Track],[Timestamp])
go

ALTER TABLE [dbo].[ZoneTrackAlarm]
  ADD CONSTRAINT [UNQ_ZoneTrackAlarm_Zone_Track_Timestamp] UNIQUE([Zone],[Track],[Timestamp])
go

CREATE INDEX [IDX_ZoneTrackAlarm_Timestamp] ON [dbo].[ZoneTrackAlarm]([Timestamp])
go

ALTER TABLE [dbo].[AisMessage]
  ADD CONSTRAINT [FK_AisMessage_AisTransceiver] FOREIGN KEY([AisTransceiver]) REFERENCES [dbo].[AisTransceiver]([Id])
go

ALTER TABLE [dbo].[AisMessage]
  ADD CONSTRAINT [FK_AisMessage_Mmsi] FOREIGN KEY([Mmsi]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisAddressedSafetyRelatedMessage]
  ADD CONSTRAINT [FK_AisAddressedSafetyRelatedMessage_DestinationMmsi] FOREIGN KEY([DestinationMmsi]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisBinaryAcknowledgeMessage]
  ADD CONSTRAINT [FK_AisBinaryAcknowledgeMessage_Mmsi1] FOREIGN KEY([Mmsi1]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisBinaryAcknowledgeMessage]
  ADD CONSTRAINT [FK_AisBinaryAcknowledgeMessage_Mmsi2] FOREIGN KEY([Mmsi2]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisBinaryAcknowledgeMessage]
  ADD CONSTRAINT [FK_AisBinaryAcknowledgeMessage_Mmsi3] FOREIGN KEY([Mmsi3]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisBinaryAcknowledgeMessage]
  ADD CONSTRAINT [FK_AisBinaryAcknowledgeMessage_Mmsi4] FOREIGN KEY([Mmsi4]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisBinaryAddressedMessage]
  ADD CONSTRAINT [FK_AisBinaryAddressedMessage_DestinationMmsi] FOREIGN KEY([DestinationMmsi]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisExtendedClassBCsPositionReportMessage]
  ADD CONSTRAINT [FK_AisExtendedClassBCsPositionReportMessage_Name] FOREIGN KEY([Name]) REFERENCES [dbo].[Name]([Id])
go

ALTER TABLE [dbo].[AisInterrogationMessage]
  ADD CONSTRAINT [FK_AisInterrogationMessage_InterrogatedMmsi] FOREIGN KEY([InterrogatedMmsi]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisInterrogationMessage]
  ADD CONSTRAINT [FK_AisInterrogationMessage_SecondStationInterrogationMmsi] FOREIGN KEY([SecondStationInterrogationMmsi]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisSafetyRelatedAcknowledgmentMessage]
  ADD CONSTRAINT [FK_AisSafetyRelatedAcknowledgmentMessage_Mmsi1] FOREIGN KEY([Mmsi1]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisSafetyRelatedAcknowledgmentMessage]
  ADD CONSTRAINT [FK_AisSafetyRelatedAcknowledgmentMessage_Mmsi2] FOREIGN KEY([Mmsi2]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisSafetyRelatedAcknowledgmentMessage]
  ADD CONSTRAINT [FK_AisSafetyRelatedAcknowledgmentMessage_Mmsi3] FOREIGN KEY([Mmsi3]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisSafetyRelatedAcknowledgmentMessage]
  ADD CONSTRAINT [FK_AisSafetyRelatedAcknowledgmentMessage_Mmsi4] FOREIGN KEY([Mmsi4]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisStaticAndVoyageRelatedDataMessage]
  ADD CONSTRAINT [FK_AisStaticAndVoyageRelatedDataMessage_ImoNumber] FOREIGN KEY([ImoNumber]) REFERENCES [dbo].[InternationalMaritimeOrganizationNumber]([Id])
go

ALTER TABLE [dbo].[AisStaticAndVoyageRelatedDataMessage]
  ADD CONSTRAINT [FK_AisStaticAndVoyageRelatedDataMessage_Callsign] FOREIGN KEY([Callsign]) REFERENCES [dbo].[Callsign]([Id])
go

ALTER TABLE [dbo].[AisStaticAndVoyageRelatedDataMessage]
  ADD CONSTRAINT [FK_AisStaticAndVoyageRelatedDataMessage_ShipName] FOREIGN KEY([ShipName]) REFERENCES [dbo].[Name]([Id])
go

ALTER TABLE [dbo].[AisStaticDataReportPartAMessage]
  ADD CONSTRAINT [FK_AisStaticDataReportPartAMessage_ShipName] FOREIGN KEY([ShipName]) REFERENCES [dbo].[Name]([Id])
go

ALTER TABLE [dbo].[AisStaticDataReportPartBMessage]
  ADD CONSTRAINT [FK_AisStaticDataReportPartBMessage_Callsign] FOREIGN KEY([Callsign]) REFERENCES [dbo].[Callsign]([Id])
go

ALTER TABLE [dbo].[AisStaticDataReportPartBMessage]
  ADD CONSTRAINT [FK_AisStaticDataReportPartBMessage_MothershipMmsi] FOREIGN KEY([MothershipMmsi]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisTransceiverCommand]
  ADD CONSTRAINT [FK_AisTransceiverCommand_AisTransceiver] FOREIGN KEY([AisTransceiver]) REFERENCES [dbo].[AisTransceiver]([Id])
go

ALTER TABLE [dbo].[AisTransceiverCommand]
  ADD CONSTRAINT [FK_AisTransceiverCommand_Reply] FOREIGN KEY([Reply]) REFERENCES [dbo].[AisTransceiverCommandReply]([Id])
go

ALTER TABLE [dbo].[AisTransceiverCommandReply]
  ADD CONSTRAINT [FK_AisTransceiverCommandReply_AisTransceiver] FOREIGN KEY([AisTransceiver]) REFERENCES [dbo].[AisTransceiver]([Id])
go

ALTER TABLE [dbo].[AisTransceiverCommandReply]
  ADD CONSTRAINT [FK_AisTransceiverCommandReply_Command] FOREIGN KEY([Command]) REFERENCES [dbo].[AisTransceiverCommand]([Id])
go

ALTER TABLE [dbo].[AisTransceiverConfiguration]
  ADD CONSTRAINT [FK_AisTransceiverConfiguration_AisTransceiver] FOREIGN KEY([AisTransceiver]) REFERENCES [dbo].[AisTransceiver]([Id])
go

ALTER TABLE [dbo].[AisTransceiverRawMessage]
  ADD CONSTRAINT [FK_AisTransceiverRawMessage_AisTransceiver] FOREIGN KEY([AisTransceiver]) REFERENCES [dbo].[AisTransceiver]([Id])
go

ALTER TABLE [dbo].[AisTransceiverRawSentence]
  ADD CONSTRAINT [FK_AisTransceiverRawSentence_AisTransceiver] FOREIGN KEY([AisTransceiver]) REFERENCES [dbo].[AisTransceiver]([Id])
go

ALTER TABLE [dbo].[AlarmStateChange]
  ADD CONSTRAINT [FK_AlarmStateChange_Alarm] FOREIGN KEY([Alarm]) REFERENCES [dbo].[ZoneTrackAlarm]([Id])
go

ALTER TABLE [dbo].[BinaryTimeseriesValue]
  ADD CONSTRAINT [FK_BinaryTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[BinaryTimeseries]([Id])
go

ALTER TABLE [dbo].[Bookmark]
  ADD CONSTRAINT [FK_Bookmark_View] FOREIGN KEY([View]) REFERENCES [dbo].[View]([Id])
go

ALTER TABLE [dbo].[BooleanTimeseriesValue]
  ADD CONSTRAINT [FK_BooleanTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[BooleanTimeseries]([Id])
go

ALTER TABLE [dbo].[ByteTimeseriesValue]
  ADD CONSTRAINT [FK_ByteTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[ByteTimeseries]([Id])
go

ALTER TABLE [dbo].[CameraCommand]
  ADD CONSTRAINT [FK_CameraCommand_Camera] FOREIGN KEY([Camera]) REFERENCES [dbo].[Camera]([Id])
go

ALTER TABLE [dbo].[CameraCommand]
  ADD CONSTRAINT [FK_CameraCommand_Reply] FOREIGN KEY([Reply]) REFERENCES [dbo].[CameraCommandReply]([Id])
go

ALTER TABLE [dbo].[CameraCommandReply]
  ADD CONSTRAINT [FK_CameraCommandReply_Camera] FOREIGN KEY([Camera]) REFERENCES [dbo].[Camera]([Id])
go

ALTER TABLE [dbo].[CameraCommandReply]
  ADD CONSTRAINT [FK_CameraCommandReply_Command] FOREIGN KEY([Command]) REFERENCES [dbo].[CameraCommand]([Id])
go

ALTER TABLE [dbo].[CameraConfiguration]
  ADD CONSTRAINT [FK_CameraConfiguration_Camera] FOREIGN KEY([Camera]) REFERENCES [dbo].[Camera]([Id])
go

ALTER TABLE [dbo].[CameraPanCalibration]
  ADD CONSTRAINT [FK_CameraPanCalibration_Camera] FOREIGN KEY([Camera]) REFERENCES [dbo].[Camera]([Id])
go

ALTER TABLE [dbo].[CameraPanCalibrationValue]
  ADD CONSTRAINT [FK_CameraPanCalibrationValue_PanCalibration] FOREIGN KEY([PanCalibration]) REFERENCES [dbo].[CameraPanCalibration]([Id])
go

ALTER TABLE [dbo].[CameraStatus]
  ADD CONSTRAINT [FK_CameraStatus_Camera] FOREIGN KEY([Camera]) REFERENCES [dbo].[Camera]([Id])
go

ALTER TABLE [dbo].[CameraStatus]
  ADD CONSTRAINT [FK_CameraStatus_Track] FOREIGN KEY([Track]) REFERENCES [dbo].[TrackBase]([Id])
go

ALTER TABLE [dbo].[CameraTiltCalibration]
  ADD CONSTRAINT [FK_CameraTiltCalibration_Camera] FOREIGN KEY([Camera]) REFERENCES [dbo].[Camera]([Id])
go

ALTER TABLE [dbo].[CameraTiltCalibrationValue]
  ADD CONSTRAINT [FK_CameraTiltCalibrationValue_TiltCalibration] FOREIGN KEY([TiltCalibration]) REFERENCES [dbo].[CameraTiltCalibration]([Id])
go

ALTER TABLE [dbo].[CameraZoomCalibration]
  ADD CONSTRAINT [FK_CameraZoomCalibration_Camera] FOREIGN KEY([Camera]) REFERENCES [dbo].[Camera]([Id])
go

ALTER TABLE [dbo].[CameraZoomCalibrationValue]
  ADD CONSTRAINT [FK_CameraZoomCalibrationValue_ZoomCalibration] FOREIGN KEY([ZoomCalibration]) REFERENCES [dbo].[CameraZoomCalibration]([Id])
go

ALTER TABLE [dbo].[CatalogElement]
  ADD CONSTRAINT [FK_CatalogElement_Catalog] FOREIGN KEY([Catalog]) REFERENCES [dbo].[Catalog]([Id])
go

ALTER TABLE [dbo].[Element]
  ADD CONSTRAINT [FK_Element_ElementType] FOREIGN KEY([ElementType]) REFERENCES [dbo].[ElementType]([Id])
go

ALTER TABLE [dbo].[DateTimeTimeseriesValue]
  ADD CONSTRAINT [FK_DateTimeTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[DateTimeTimeseries]([Id])
go

ALTER TABLE [dbo].[DeviceHostConfiguration]
  ADD CONSTRAINT [FK_DeviceHostConfiguration_Host] FOREIGN KEY([Host]) REFERENCES [dbo].[DeviceHost]([Id])
go

ALTER TABLE [dbo].[DoubleTimeseriesValue]
  ADD CONSTRAINT [FK_DoubleTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[DoubleTimeseries]([Id])
go

ALTER TABLE [dbo].[GeoPosition2DTimeseriesValue]
  ADD CONSTRAINT [FK_GeoPosition2DTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[GeoPosition2DTimeseries]([Id])
go

ALTER TABLE [dbo].[GeoPosition3DTimeseriesValue]
  ADD CONSTRAINT [FK_GeoPosition3DTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[GeoPosition3DTimeseries]([Id])
go

ALTER TABLE [dbo].[GNSSDeviceCommand]
  ADD CONSTRAINT [FK_GNSSDeviceCommand_GNSSDevice] FOREIGN KEY([GNSSDevice]) REFERENCES [dbo].[GNSSDevice]([Id])
go

ALTER TABLE [dbo].[GNSSDeviceCommand]
  ADD CONSTRAINT [FK_GNSSDeviceCommand_Reply] FOREIGN KEY([Reply]) REFERENCES [dbo].[GNSSDeviceCommandReply]([Id])
go

ALTER TABLE [dbo].[GNSSDeviceCommandReply]
  ADD CONSTRAINT [FK_GNSSDeviceCommandReply_GNSSDevice] FOREIGN KEY([GNSSDevice]) REFERENCES [dbo].[GNSSDevice]([Id])
go

ALTER TABLE [dbo].[GNSSDeviceCommandReply]
  ADD CONSTRAINT [FK_GNSSDeviceCommandReply_Command] FOREIGN KEY([Command]) REFERENCES [dbo].[GNSSDeviceCommand]([Id])
go

ALTER TABLE [dbo].[GNSSDeviceConfiguration]
  ADD CONSTRAINT [FK_GNSSDeviceConfiguration_GNSSDevice] FOREIGN KEY([GNSSDevice]) REFERENCES [dbo].[GNSSDevice]([Id])
go

ALTER TABLE [dbo].[GuidTimeseriesValue]
  ADD CONSTRAINT [FK_GuidTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[GuidTimeseries]([Id])
go

ALTER TABLE [dbo].[GyroDeviceCommand]
  ADD CONSTRAINT [FK_GyroDeviceCommand_GyroDevice] FOREIGN KEY([GyroDevice]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[GyroDeviceCommand]
  ADD CONSTRAINT [FK_GyroDeviceCommand_Reply] FOREIGN KEY([Reply]) REFERENCES [dbo].[GyroDeviceCommandReply]([Id])
go

ALTER TABLE [dbo].[GyroDeviceCommandReply]
  ADD CONSTRAINT [FK_GyroDeviceCommandReply_GyroDevice] FOREIGN KEY([GyroDevice]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[GyroDeviceCommandReply]
  ADD CONSTRAINT [FK_GyroDeviceCommandReply_Command] FOREIGN KEY([Command]) REFERENCES [dbo].[GyroDeviceCommand]([Id])
go

ALTER TABLE [dbo].[GyroDeviceConfiguration]
  ADD CONSTRAINT [FK_GyroDeviceConfiguration_GyroDevice] FOREIGN KEY([GyroDevice]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[Int16TimeseriesValue]
  ADD CONSTRAINT [FK_Int16TimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[Int16Timeseries]([Id])
go

ALTER TABLE [dbo].[Int32TimeseriesValue]
  ADD CONSTRAINT [FK_Int32TimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[Int32Timeseries]([Id])
go

ALTER TABLE [dbo].[Int64TimeseriesValue]
  ADD CONSTRAINT [FK_Int64TimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[Int64Timeseries]([Id])
go

ALTER TABLE [dbo].[BaseStation]
  ADD CONSTRAINT [FK_BaseStation_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[BaseStationType]([Id])
go

ALTER TABLE [dbo].[Device]
  ADD CONSTRAINT [FK_Device_Host] FOREIGN KEY([Host]) REFERENCES [dbo].[DeviceHost]([Id])
go

ALTER TABLE [dbo].[Device]
  ADD CONSTRAINT [FK_Device_EnabledTimeseries] FOREIGN KEY([EnabledTimeseries]) REFERENCES [dbo].[DeviceEnabledTimeseries]([Id])
go

ALTER TABLE [dbo].[Camera]
  ADD CONSTRAINT [FK_Camera_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[CameraType]([Id])
go

ALTER TABLE [dbo].[GNSSDevice]
  ADD CONSTRAINT [FK_GNSSDevice_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[GNSSDeviceType]([Id])
go

ALTER TABLE [dbo].[GNSSDevice]
  ADD CONSTRAINT [FK_GNSSDevice_LatitudeTimeseries] FOREIGN KEY([LatitudeTimeseries]) REFERENCES [dbo].[GNSSLatitudeTimeseries]([Id])
go

ALTER TABLE [dbo].[GNSSDevice]
  ADD CONSTRAINT [FK_GNSSDevice_LongitudeTimeseries] FOREIGN KEY([LongitudeTimeseries]) REFERENCES [dbo].[GNSSLongitudeTimeseries]([Id])
go

ALTER TABLE [dbo].[GNSSDevice]
  ADD CONSTRAINT [FK_GNSSDevice_AltitudeTimeseries] FOREIGN KEY([AltitudeTimeseries]) REFERENCES [dbo].[GNSSAltitudeTimeseries]([Id])
go

ALTER TABLE [dbo].[GyroDevice]
  ADD CONSTRAINT [FK_GyroDevice_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[GyroDeviceType]([Id])
go

ALTER TABLE [dbo].[GyroDevice]
  ADD CONSTRAINT [FK_GyroDevice_HeadingTrueNorthTimeseries] FOREIGN KEY([HeadingTrueNorthTimeseries]) REFERENCES [dbo].[GyroHeadingTrueNorthTimeseries]([Id])
go

ALTER TABLE [dbo].[GyroDevice]
  ADD CONSTRAINT [FK_GyroDevice_HeadingMagneticNorthTimeseries] FOREIGN KEY([HeadingMagneticNorthTimeseries]) REFERENCES [dbo].[GyroHeadingMagneticNorthTimeseries]([Id])
go

ALTER TABLE [dbo].[GyroDevice]
  ADD CONSTRAINT [FK_GyroDevice_PitchTimeseries] FOREIGN KEY([PitchTimeseries]) REFERENCES [dbo].[GyroPitchTimeseries]([Id])
go

ALTER TABLE [dbo].[GyroDevice]
  ADD CONSTRAINT [FK_GyroDevice_RateOfTurnTimeseries] FOREIGN KEY([RateOfTurnTimeseries]) REFERENCES [dbo].[GyroRateOfTurnTimeseries]([Id])
go

ALTER TABLE [dbo].[GyroDevice]
  ADD CONSTRAINT [FK_GyroDevice_RollTimeseries] FOREIGN KEY([RollTimeseries]) REFERENCES [dbo].[GyroRollTimeseries]([Id])
go

ALTER TABLE [dbo].[GyroDevice]
  ADD CONSTRAINT [FK_GyroDevice_CourseTimeseries] FOREIGN KEY([CourseTimeseries]) REFERENCES [dbo].[GyroCourseTimeseries]([Id])
go

ALTER TABLE [dbo].[GyroDevice]
  ADD CONSTRAINT [FK_GyroDevice_SpeedTimeseries] FOREIGN KEY([SpeedTimeseries]) REFERENCES [dbo].[GyroSpeedTimeseries]([Id])
go

ALTER TABLE [dbo].[GyroDevice]
  ADD CONSTRAINT [FK_GyroDevice_GNSSDevice] FOREIGN KEY([GNSSDevice]) REFERENCES [dbo].[GNSSDevice]([Id])
go

ALTER TABLE [dbo].[LineInputDevice]
  ADD CONSTRAINT [FK_LineInputDevice_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[LineInputDeviceType]([Id])
go

ALTER TABLE [dbo].[OilspillDetector]
  ADD CONSTRAINT [FK_OilspillDetector_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[OilspillDetectorType]([Id])
go

ALTER TABLE [dbo].[Radio]
  ADD CONSTRAINT [FK_Radio_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[RadioType]([Id])
go

ALTER TABLE [dbo].[Radome]
  ADD CONSTRAINT [FK_Radome_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[RadomeType]([Id])
go

ALTER TABLE [dbo].[Radome]
  ADD CONSTRAINT [FK_Radome_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[Radome]
  ADD CONSTRAINT [FK_Radome_PressureTimeseries] FOREIGN KEY([PressureTimeseries]) REFERENCES [dbo].[RadomePressureTimeseries]([Id])
go

ALTER TABLE [dbo].[Radome]
  ADD CONSTRAINT [FK_Radome_TemperatureTimeseries] FOREIGN KEY([TemperatureTimeseries]) REFERENCES [dbo].[RadomeTemperatureTimeseries]([Id])
go

ALTER TABLE [dbo].[Radome]
  ADD CONSTRAINT [FK_Radome_DewPointTimeseries] FOREIGN KEY([DewPointTimeseries]) REFERENCES [dbo].[RadomeDewPointTimeseries]([Id])
go

ALTER TABLE [dbo].[Radome]
  ADD CONSTRAINT [FK_Radome_StatusTimeseries] FOREIGN KEY([StatusTimeseries]) REFERENCES [dbo].[RadomeStatusTimeseries]([Id])
go

ALTER TABLE [dbo].[AisTransceiver]
  ADD CONSTRAINT [FK_AisTransceiver_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[AisTransceiverType]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[RadarType]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_SaveSettingsTimeseries] FOREIGN KEY([SaveSettingsTimeseries]) REFERENCES [dbo].[RadarSaveSettingsTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_PowerOnTimeseries] FOREIGN KEY([PowerOnTimeseries]) REFERENCES [dbo].[RadarPowerOnTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_TrackingOnTimeseries] FOREIGN KEY([TrackingOnTimeseries]) REFERENCES [dbo].[RadarTrackingTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_RadarPulseTimeseries] FOREIGN KEY([RadarPulseTimeseries]) REFERENCES [dbo].[RadarPulseTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_TuningTimeseries] FOREIGN KEY([TuningTimeseries]) REFERENCES [dbo].[RadarTuningTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_BlankSector1Timeseries] FOREIGN KEY([BlankSector1Timeseries]) REFERENCES [dbo].[RadarBlankSector1Timeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_Sector1StartTimeseries] FOREIGN KEY([Sector1StartTimeseries]) REFERENCES [dbo].[RadarSector1StartTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_Sector1EndTimeseries] FOREIGN KEY([Sector1EndTimeseries]) REFERENCES [dbo].[RadarSector1EndTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_BlankSector2Timeseries] FOREIGN KEY([BlankSector2Timeseries]) REFERENCES [dbo].[RadarBlankSector2Timeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_Sector2StartTimeseries] FOREIGN KEY([Sector2StartTimeseries]) REFERENCES [dbo].[RadarSector2StartTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_Sector2EndTimeseries] FOREIGN KEY([Sector2EndTimeseries]) REFERENCES [dbo].[RadarSector2EndTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_EnableAutomaticFrequencyControlTimeseries] FOREIGN KEY([EnableAutomaticFrequencyControlTimeseries]) REFERENCES [dbo].[RadarEnableAutomaticFrequencyControlTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_AzimuthOffsetTimeseries] FOREIGN KEY([AzimuthOffsetTimeseries]) REFERENCES [dbo].[RadarAzimuthOffsetTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_EnableSensitivityTimeControlTimeseries] FOREIGN KEY([EnableSensitivityTimeControlTimeseries]) REFERENCES [dbo].[RadarEnableSensitivityTimeControlTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_AutomaticSensitivityTimeControlTimeseries] FOREIGN KEY([AutomaticSensitivityTimeControlTimeseries]) REFERENCES [dbo].[RadarAutomaticSensitivityTimeControlTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_SensitivityTimeControlLevelTimeseries] FOREIGN KEY([SensitivityTimeControlLevelTimeseries]) REFERENCES [dbo].[RadarSensitivityTimeControlLevelTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_EnableFastTimeConstantTimeseries] FOREIGN KEY([EnableFastTimeConstantTimeseries]) REFERENCES [dbo].[RadarEnableFastTimeConstantTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_FastTimeConstantLevelTimeseries] FOREIGN KEY([FastTimeConstantLevelTimeseries]) REFERENCES [dbo].[RadarFastTimeConstantLevelTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_FastTimeConstantModeTimeseries] FOREIGN KEY([FastTimeConstantModeTimeseries]) REFERENCES [dbo].[RadarFastTimeConstantModeTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_LatitudeTimeseries] FOREIGN KEY([LatitudeTimeseries]) REFERENCES [dbo].[RadarLatitudeTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_LongitudeTimeseries] FOREIGN KEY([LongitudeTimeseries]) REFERENCES [dbo].[RadarLongitudeTimeseries]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_Radome] FOREIGN KEY([Radome]) REFERENCES [dbo].[Radome]([Id])
go

ALTER TABLE [dbo].[Radar]
  ADD CONSTRAINT [FK_Radar_GNSSDevice] FOREIGN KEY([GNSSDevice]) REFERENCES [dbo].[GNSSDevice]([Id])
go

ALTER TABLE [dbo].[WeatherStation]
  ADD CONSTRAINT [FK_WeatherStation_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[WeatherStationType]([Id])
go

ALTER TABLE [dbo].[WeatherStation]
  ADD CONSTRAINT [FK_WeatherStation_BarometricPressureTimeseries] FOREIGN KEY([BarometricPressureTimeseries]) REFERENCES [dbo].[WeatherStationBarometricPressureTimeseries]([Id])
go

ALTER TABLE [dbo].[WeatherStation]
  ADD CONSTRAINT [FK_WeatherStation_AirTemperatureTimeseries] FOREIGN KEY([AirTemperatureTimeseries]) REFERENCES [dbo].[WeatherStationAirTemperatureTimeseries]([Id])
go

ALTER TABLE [dbo].[WeatherStation]
  ADD CONSTRAINT [FK_WeatherStation_WaterTemperatureTimeseries] FOREIGN KEY([WaterTemperatureTimeseries]) REFERENCES [dbo].[WeatherStationWaterTemperatureTimeseries]([Id])
go

ALTER TABLE [dbo].[WeatherStation]
  ADD CONSTRAINT [FK_WeatherStation_RelativeHumidityTimeseries] FOREIGN KEY([RelativeHumidityTimeseries]) REFERENCES [dbo].[WeatherStationRelativeHumidityTimeseries]([Id])
go

ALTER TABLE [dbo].[WeatherStation]
  ADD CONSTRAINT [FK_WeatherStation_AbsoluteHumidityTimeseries] FOREIGN KEY([AbsoluteHumidityTimeseries]) REFERENCES [dbo].[WeatherStationAbsoluteHumidityTimeseries]([Id])
go

ALTER TABLE [dbo].[WeatherStation]
  ADD CONSTRAINT [FK_WeatherStation_DewPointTimeseries] FOREIGN KEY([DewPointTimeseries]) REFERENCES [dbo].[WeatherStationDewPointTimeseries]([Id])
go

ALTER TABLE [dbo].[WeatherStation]
  ADD CONSTRAINT [FK_WeatherStation_WindDirectionTimeseries] FOREIGN KEY([WindDirectionTimeseries]) REFERENCES [dbo].[WeatherStationWindDirectionTimeseries]([Id])
go

ALTER TABLE [dbo].[WeatherStation]
  ADD CONSTRAINT [FK_WeatherStation_WindSpeedTimeseries] FOREIGN KEY([WindSpeedTimeseries]) REFERENCES [dbo].[WeatherStationWindSpeedTimeseries]([Id])
go

ALTER TABLE [dbo].[WeatherStation]
  ADD CONSTRAINT [FK_WeatherStation_Gyro] FOREIGN KEY([Gyro]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[Facility]
  ADD CONSTRAINT [FK_Facility_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[FacilityType]([Id])
go

ALTER TABLE [dbo].[Aircraft]
  ADD CONSTRAINT [FK_Aircraft_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[AircraftType]([Id])
go

ALTER TABLE [dbo].[AisAidToNavigation]
  ADD CONSTRAINT [FK_AisAidToNavigation_MMSI] FOREIGN KEY([MMSI]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[AisAidToNavigation]
  ADD CONSTRAINT [FK_AisAidToNavigation_Position] FOREIGN KEY([Position]) REFERENCES [dbo].[AisAidToNavigationPositionTimeseries]([Id])
go

ALTER TABLE [dbo].[AisAidToNavigation]
  ADD CONSTRAINT [FK_AisAidToNavigation_OffPositionTimeseries] FOREIGN KEY([OffPositionTimeseries]) REFERENCES [dbo].[AisAidToNavigationOffPositionTimeseries]([Id])
go

ALTER TABLE [dbo].[Vehicle]
  ADD CONSTRAINT [FK_Vehicle_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[VehicleType]([Id])
go

ALTER TABLE [dbo].[Vessel]
  ADD CONSTRAINT [FK_Vessel_Type] FOREIGN KEY([Type]) REFERENCES [dbo].[VesselType]([Id])
go

ALTER TABLE [dbo].[Vessel]
  ADD CONSTRAINT [FK_Vessel_DraughtTimeseries] FOREIGN KEY([DraughtTimeseries]) REFERENCES [dbo].[VesselDraughtTimeseries]([Id])
go

ALTER TABLE [dbo].[Vessel]
  ADD CONSTRAINT [FK_Vessel_PersonsOnBoardTimeseries] FOREIGN KEY([PersonsOnBoardTimeseries]) REFERENCES [dbo].[VesselPersonsOnBoardTimeseries]([Id])
go

ALTER TABLE [dbo].[ItemIdentityLink]
  ADD CONSTRAINT [FK_ItemIdentityLink_Item] FOREIGN KEY([Item]) REFERENCES [dbo].[Item]([Id])
go

ALTER TABLE [dbo].[ItemIdentityLink]
  ADD CONSTRAINT [FK_ItemIdentityLink_Identity] FOREIGN KEY([Identity]) REFERENCES [dbo].[Identity]([Id])
go

ALTER TABLE [dbo].[ItemParentChildLink]
  ADD CONSTRAINT [FK_ItemParentChildLink_Parent] FOREIGN KEY([Parent]) REFERENCES [dbo].[Item]([Id])
go

ALTER TABLE [dbo].[ItemParentChildLink]
  ADD CONSTRAINT [FK_ItemParentChildLink_Child] FOREIGN KEY([Child]) REFERENCES [dbo].[Item]([Id])
go

ALTER TABLE [dbo].[LineInputDeviceCommand]
  ADD CONSTRAINT [FK_LineInputDeviceCommand_LineInputDevice] FOREIGN KEY([LineInputDevice]) REFERENCES [dbo].[LineInputDevice]([Id])
go

ALTER TABLE [dbo].[LineInputDeviceCommand]
  ADD CONSTRAINT [FK_LineInputDeviceCommand_Reply] FOREIGN KEY([Reply]) REFERENCES [dbo].[LineInputDeviceCommandReply]([Id])
go

ALTER TABLE [dbo].[LineInputDeviceCommandReply]
  ADD CONSTRAINT [FK_LineInputDeviceCommandReply_LineInputDevice] FOREIGN KEY([LineInputDevice]) REFERENCES [dbo].[LineInputDevice]([Id])
go

ALTER TABLE [dbo].[LineInputDeviceCommandReply]
  ADD CONSTRAINT [FK_LineInputDeviceCommandReply_Command] FOREIGN KEY([Command]) REFERENCES [dbo].[LineInputDeviceCommand]([Id])
go

ALTER TABLE [dbo].[LineInputDeviceConfiguration]
  ADD CONSTRAINT [FK_LineInputDeviceConfiguration_LineInputDevice] FOREIGN KEY([LineInputDevice]) REFERENCES [dbo].[LineInputDevice]([Id])
go

ALTER TABLE [dbo].[LineInputMessageRouting]
  ADD CONSTRAINT [FK_LineInputMessageRouting_LineInputDevice] FOREIGN KEY([LineInputDevice]) REFERENCES [dbo].[LineInputDevice]([Id])
go

ALTER TABLE [dbo].[LineInputMessageRoutingDestination]
  ADD CONSTRAINT [FK_LineInputMessageRoutingDestination_Routing] FOREIGN KEY([Routing]) REFERENCES [dbo].[LineInputMessageRouting]([Id])
go

ALTER TABLE [dbo].[LineInputMessageRoutingDestination]
  ADD CONSTRAINT [FK_LineInputMessageRoutingDestination_Listener] FOREIGN KEY([Listener]) REFERENCES [dbo].[Device]([Id])
go

ALTER TABLE [dbo].[LineInputWhiteListEntry]
  ADD CONSTRAINT [FK_LineInputWhiteListEntry_LineInputDevice] FOREIGN KEY([LineInputDevice]) REFERENCES [dbo].[LineInputDevice]([Id])
go

ALTER TABLE [dbo].[LogApplicationConfiguration]
  ADD CONSTRAINT [FK_LogApplicationConfiguration_Application] FOREIGN KEY([Application]) REFERENCES [dbo].[LogApplication]([Id])
go

ALTER TABLE [dbo].[LogHostConfiguration]
  ADD CONSTRAINT [FK_LogHostConfiguration_Host] FOREIGN KEY([Host]) REFERENCES [dbo].[LogHost]([Id])
go

ALTER TABLE [dbo].[LogProcess]
  ADD CONSTRAINT [FK_LogProcess_Application] FOREIGN KEY([Application]) REFERENCES [dbo].[LogApplication]([Id])
go

ALTER TABLE [dbo].[LogProcess]
  ADD CONSTRAINT [FK_LogProcess_Host] FOREIGN KEY([Host]) REFERENCES [dbo].[LogHost]([Id])
go

ALTER TABLE [dbo].[LogRecord]
  ADD CONSTRAINT [FK_LogRecord_Thread] FOREIGN KEY([Thread]) REFERENCES [dbo].[LogThread]([Id])
go

ALTER TABLE [dbo].[LogRecord]
  ADD CONSTRAINT [FK_LogRecord_Location] FOREIGN KEY([Location]) REFERENCES [dbo].[LogLocation]([Id])
go

ALTER TABLE [dbo].[LogThread]
  ADD CONSTRAINT [FK_LogThread_Process] FOREIGN KEY([Process]) REFERENCES [dbo].[LogProcess]([Id])
go

ALTER TABLE [dbo].[LogTraceEntry]
  ADD CONSTRAINT [FK_LogTraceEntry_Thread] FOREIGN KEY([Thread]) REFERENCES [dbo].[LogThread]([Id])
go

ALTER TABLE [dbo].[LogTraceEntry]
  ADD CONSTRAINT [FK_LogTraceEntry_Location] FOREIGN KEY([Location]) REFERENCES [dbo].[LogLocation]([Id])
go

ALTER TABLE [dbo].[MapElement]
  ADD CONSTRAINT [FK_MapElement_Item] FOREIGN KEY([Item]) REFERENCES [dbo].[Item]([Id])
go

ALTER TABLE [dbo].[MaritimeIdentificationDigits]
  ADD CONSTRAINT [FK_MaritimeIdentificationDigits_Country] FOREIGN KEY([Country]) REFERENCES [dbo].[Country]([Id])
go

ALTER TABLE [dbo].[MediaProxySession]
  ADD CONSTRAINT [FK_MediaProxySession_Service] FOREIGN KEY([Service]) REFERENCES [dbo].[MediaService]([Id])
go

ALTER TABLE [dbo].[MediaProxySession]
  ADD CONSTRAINT [FK_MediaProxySession_EnabledTimeseries] FOREIGN KEY([EnabledTimeseries]) REFERENCES [dbo].[MediaProxySessionEnabledTimeseries]([Id])
go

ALTER TABLE [dbo].[MediaProxySessionFile]
  ADD CONSTRAINT [FK_MediaProxySessionFile_ProxySession] FOREIGN KEY([ProxySession]) REFERENCES [dbo].[MediaProxySession]([Id])
go

ALTER TABLE [dbo].[MediaProxySessionOptions]
  ADD CONSTRAINT [FK_MediaProxySessionOptions_ProxySession] FOREIGN KEY([ProxySession]) REFERENCES [dbo].[MediaProxySession]([Id])
go

ALTER TABLE [dbo].[MediaService]
  ADD CONSTRAINT [FK_MediaService_EnabledTimeseries] FOREIGN KEY([EnabledTimeseries]) REFERENCES [dbo].[MediaServiceEnabledTimeseries]([Id])
go

ALTER TABLE [dbo].[MediaServiceOptions]
  ADD CONSTRAINT [FK_MediaServiceOptions_MediaService] FOREIGN KEY([MediaService]) REFERENCES [dbo].[MediaService]([Id])
go

ALTER TABLE [dbo].[NamespaceElement]
  ADD CONSTRAINT [FK_NamespaceElement_Namespace] FOREIGN KEY([Namespace]) REFERENCES [dbo].[Namespace]([Id])
go

ALTER TABLE [dbo].[Oilspill]
  ADD CONSTRAINT [FK_Oilspill_OilSpillDetector] FOREIGN KEY([OilSpillDetector]) REFERENCES [dbo].[OilspillDetector]([Id])
go

ALTER TABLE [dbo].[OilspillDetectorCommand]
  ADD CONSTRAINT [FK_OilspillDetectorCommand_OilSpillDetector] FOREIGN KEY([OilSpillDetector]) REFERENCES [dbo].[OilspillDetector]([Id])
go

ALTER TABLE [dbo].[OilspillDetectorCommand]
  ADD CONSTRAINT [FK_OilspillDetectorCommand_Reply] FOREIGN KEY([Reply]) REFERENCES [dbo].[OilspillDetectorCommandReply]([Id])
go

ALTER TABLE [dbo].[OilspillDetectorCommandReply]
  ADD CONSTRAINT [FK_OilspillDetectorCommandReply_OilSpillDetector] FOREIGN KEY([OilSpillDetector]) REFERENCES [dbo].[OilspillDetector]([Id])
go

ALTER TABLE [dbo].[OilspillDetectorCommandReply]
  ADD CONSTRAINT [FK_OilspillDetectorCommandReply_Command] FOREIGN KEY([Command]) REFERENCES [dbo].[OilspillDetectorCommand]([Id])
go

ALTER TABLE [dbo].[OilspillDetectorConfiguration]
  ADD CONSTRAINT [FK_OilspillDetectorConfiguration_OilSpillDetector] FOREIGN KEY([OilSpillDetector]) REFERENCES [dbo].[OilspillDetector]([Id])
go

ALTER TABLE [dbo].[OilspillDetectorConfiguration]
  ADD CONSTRAINT [FK_OilspillDetectorConfiguration_TargetMMSI] FOREIGN KEY([TargetMMSI]) REFERENCES [dbo].[MaritimeMobileServiceIdentity]([Id])
go

ALTER TABLE [dbo].[Position2DTimeseriesValue]
  ADD CONSTRAINT [FK_Position2DTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[Position2DTimeseries]([Id])
go

ALTER TABLE [dbo].[Position3DTimeseriesValue]
  ADD CONSTRAINT [FK_Position3DTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[Position3DTimeseries]([Id])
go

ALTER TABLE [dbo].[Property]
  ADD CONSTRAINT [FK_Property_Element] FOREIGN KEY([Element]) REFERENCES [dbo].[Element]([Id])
go

ALTER TABLE [dbo].[Property]
  ADD CONSTRAINT [FK_Property_Definition] FOREIGN KEY([Definition]) REFERENCES [dbo].[PropertyDefinition]([Id])
go

ALTER TABLE [dbo].[ReferenceProperty]
  ADD CONSTRAINT [FK_ReferenceProperty_Value] FOREIGN KEY([Value]) REFERENCES [dbo].[Element]([Id])
go

ALTER TABLE [dbo].[BinaryTimeseriesProperty]
  ADD CONSTRAINT [FK_BinaryTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[BinaryTimeseries]([Id])
go

ALTER TABLE [dbo].[BooleanTimeseriesProperty]
  ADD CONSTRAINT [FK_BooleanTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[BooleanTimeseries]([Id])
go

ALTER TABLE [dbo].[ByteTimeseriesProperty]
  ADD CONSTRAINT [FK_ByteTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[ByteTimeseries]([Id])
go

ALTER TABLE [dbo].[DateTimeTimeseriesProperty]
  ADD CONSTRAINT [FK_DateTimeTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[DateTimeTimeseries]([Id])
go

ALTER TABLE [dbo].[DoubleTimeseriesProperty]
  ADD CONSTRAINT [FK_DoubleTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[DoubleTimeseries]([Id])
go

ALTER TABLE [dbo].[GuidTimeseriesProperty]
  ADD CONSTRAINT [FK_GuidTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[GuidTimeseries]([Id])
go

ALTER TABLE [dbo].[Int16TimeseriesProperty]
  ADD CONSTRAINT [FK_Int16TimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[Int16Timeseries]([Id])
go

ALTER TABLE [dbo].[Int32TimeseriesProperty]
  ADD CONSTRAINT [FK_Int32TimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[Int32Timeseries]([Id])
go

ALTER TABLE [dbo].[Int64TimeseriesProperty]
  ADD CONSTRAINT [FK_Int64TimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[Int64Timeseries]([Id])
go

ALTER TABLE [dbo].[ReferenceTimeseriesProperty]
  ADD CONSTRAINT [FK_ReferenceTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[ReferenceTimeseries]([Id])
go

ALTER TABLE [dbo].[SByteTimeseriesProperty]
  ADD CONSTRAINT [FK_SByteTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[SByteTimeseries]([Id])
go

ALTER TABLE [dbo].[SingleTimeseriesProperty]
  ADD CONSTRAINT [FK_SingleTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[SingleTimeseries]([Id])
go

ALTER TABLE [dbo].[StringTimeseriesProperty]
  ADD CONSTRAINT [FK_StringTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[StringTimeseries]([Id])
go

ALTER TABLE [dbo].[TimeSpanTimeseriesProperty]
  ADD CONSTRAINT [FK_TimeSpanTimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[TimeSpanTimeseries]([Id])
go

ALTER TABLE [dbo].[UInt16TimeseriesProperty]
  ADD CONSTRAINT [FK_UInt16TimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[UInt16Timeseries]([Id])
go

ALTER TABLE [dbo].[UInt32TimeseriesProperty]
  ADD CONSTRAINT [FK_UInt32TimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[UInt32Timeseries]([Id])
go

ALTER TABLE [dbo].[UInt64TimeseriesProperty]
  ADD CONSTRAINT [FK_UInt64TimeseriesProperty_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[UInt64Timeseries]([Id])
go

ALTER TABLE [dbo].[PropertyDefinition]
  ADD CONSTRAINT [FK_PropertyDefinition_ElementType] FOREIGN KEY([ElementType]) REFERENCES [dbo].[ElementType]([Id])
go

ALTER TABLE [dbo].[ReferencePropertyDefinition]
  ADD CONSTRAINT [FK_ReferencePropertyDefinition_DefaultValue] FOREIGN KEY([DefaultValue]) REFERENCES [dbo].[Element]([Id])
go

ALTER TABLE [dbo].[ReferencePropertyDefinition]
  ADD CONSTRAINT [FK_ReferencePropertyDefinition_ReferencedElementType] FOREIGN KEY([ReferencedElementType]) REFERENCES [dbo].[ElementType]([Id])
go

ALTER TABLE [dbo].[ReferenceTimeseriesPropertyDefinition]
  ADD CONSTRAINT [FK_ReferenceTimeseriesPropertyDefinition_ReferencedElementType] FOREIGN KEY([ReferencedElementType]) REFERENCES [dbo].[ElementType]([Id])
go

ALTER TABLE [dbo].[RadarAlarmStatus]
  ADD CONSTRAINT [FK_RadarAlarmStatus_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarCommand]
  ADD CONSTRAINT [FK_RadarCommand_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarCommand]
  ADD CONSTRAINT [FK_RadarCommand_Reply] FOREIGN KEY([Reply]) REFERENCES [dbo].[RadarCommandReply]([Id])
go

ALTER TABLE [dbo].[RadarCommandReply]
  ADD CONSTRAINT [FK_RadarCommandReply_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarCommandReply]
  ADD CONSTRAINT [FK_RadarCommandReply_Command] FOREIGN KEY([Command]) REFERENCES [dbo].[RadarCommand]([Id])
go

ALTER TABLE [dbo].[RadarConfiguration]
  ADD CONSTRAINT [FK_RadarConfiguration_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarImage]
  ADD CONSTRAINT [FK_RadarImage_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarRawTrackTable]
  ADD CONSTRAINT [FK_RadarRawTrackTable_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarStatus]
  ADD CONSTRAINT [FK_RadarStatus_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadioCommand]
  ADD CONSTRAINT [FK_RadioCommand_Radio] FOREIGN KEY([Radio]) REFERENCES [dbo].[Radio]([Id])
go

ALTER TABLE [dbo].[RadioCommand]
  ADD CONSTRAINT [FK_RadioCommand_Reply] FOREIGN KEY([Reply]) REFERENCES [dbo].[RadioCommandReply]([Id])
go

ALTER TABLE [dbo].[RadioCommandReply]
  ADD CONSTRAINT [FK_RadioCommandReply_Radio] FOREIGN KEY([Radio]) REFERENCES [dbo].[Radio]([Id])
go

ALTER TABLE [dbo].[RadioCommandReply]
  ADD CONSTRAINT [FK_RadioCommandReply_Command] FOREIGN KEY([Command]) REFERENCES [dbo].[RadioCommand]([Id])
go

ALTER TABLE [dbo].[RadioConfiguration]
  ADD CONSTRAINT [FK_RadioConfiguration_Radio] FOREIGN KEY([Radio]) REFERENCES [dbo].[Radio]([Id])
go

ALTER TABLE [dbo].[RadomeCommand]
  ADD CONSTRAINT [FK_RadomeCommand_Radome] FOREIGN KEY([Radome]) REFERENCES [dbo].[Radome]([Id])
go

ALTER TABLE [dbo].[RadomeCommand]
  ADD CONSTRAINT [FK_RadomeCommand_Reply] FOREIGN KEY([Reply]) REFERENCES [dbo].[RadomeCommandReply]([Id])
go

ALTER TABLE [dbo].[RadomeCommandReply]
  ADD CONSTRAINT [FK_RadomeCommandReply_Radome] FOREIGN KEY([Radome]) REFERENCES [dbo].[Radome]([Id])
go

ALTER TABLE [dbo].[RadomeCommandReply]
  ADD CONSTRAINT [FK_RadomeCommandReply_Command] FOREIGN KEY([Command]) REFERENCES [dbo].[RadomeCommand]([Id])
go

ALTER TABLE [dbo].[RadomeConfiguration]
  ADD CONSTRAINT [FK_RadomeConfiguration_Radome] FOREIGN KEY([Radome]) REFERENCES [dbo].[Radome]([Id])
go

ALTER TABLE [dbo].[ReferenceTimeseriesValue]
  ADD CONSTRAINT [FK_ReferenceTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[ReferenceTimeseries]([Id])
go

ALTER TABLE [dbo].[ReferenceTimeseriesValue]
  ADD CONSTRAINT [FK_ReferenceTimeseriesValue_Value] FOREIGN KEY([Value]) REFERENCES [dbo].[Element]([Id])
go

ALTER TABLE [dbo].[SByteTimeseriesValue]
  ADD CONSTRAINT [FK_SByteTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[SByteTimeseries]([Id])
go

ALTER TABLE [dbo].[SecurityIdentifier]
  ADD CONSTRAINT [FK_SecurityIdentifier_Domain] FOREIGN KEY([Domain]) REFERENCES [dbo].[SecurityDomain]([Id])
go

ALTER TABLE [dbo].[SecurityIdentifierRoleLink]
  ADD CONSTRAINT [FK_SecurityIdentifierRoleLink_Member] FOREIGN KEY([Member]) REFERENCES [dbo].[SecurityIdentifier]([Id])
go

ALTER TABLE [dbo].[SecurityIdentifierRoleLink]
  ADD CONSTRAINT [FK_SecurityIdentifierRoleLink_Role] FOREIGN KEY([Role]) REFERENCES [dbo].[SecurityRole]([Id])
go

ALTER TABLE [dbo].[SecurityLoginSession]
  ADD CONSTRAINT [FK_SecurityLoginSession_Login] FOREIGN KEY([Login]) REFERENCES [dbo].[SecurityLogin]([Id])
go

ALTER TABLE [dbo].[SecurityPermission]
  ADD CONSTRAINT [FK_SecurityPermission_Identifier] FOREIGN KEY([Identifier]) REFERENCES [dbo].[SecurityIdentifier]([Id])
go

ALTER TABLE [dbo].[SingleTimeseriesValue]
  ADD CONSTRAINT [FK_SingleTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[SingleTimeseries]([Id])
go

ALTER TABLE [dbo].[StringTimeseriesValue]
  ADD CONSTRAINT [FK_StringTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[StringTimeseries]([Id])
go

ALTER TABLE [dbo].[TimeseriesCatalogElement]
  ADD CONSTRAINT [FK_TimeseriesCatalogElement_Catalog] FOREIGN KEY([Catalog]) REFERENCES [dbo].[TimeseriesCatalog]([Id])
go

ALTER TABLE [dbo].[AisAidToNavigationOffPositionTimeseries]
  ADD CONSTRAINT [FK_AisAidToNavigationOffPositionTimeseries_AidToNavigation] FOREIGN KEY([AidToNavigation]) REFERENCES [dbo].[AisAidToNavigation]([Id])
go

ALTER TABLE [dbo].[DeviceEnabledTimeseries]
  ADD CONSTRAINT [FK_DeviceEnabledTimeseries_Device] FOREIGN KEY([Device]) REFERENCES [dbo].[Device]([Id])
go

ALTER TABLE [dbo].[RadarAutomaticSensitivityTimeControlTimeseries]
  ADD CONSTRAINT [FK_RadarAutomaticSensitivityTimeControlTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarBlankSector1Timeseries]
  ADD CONSTRAINT [FK_RadarBlankSector1Timeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarBlankSector2Timeseries]
  ADD CONSTRAINT [FK_RadarBlankSector2Timeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarEnableAutomaticFrequencyControlTimeseries]
  ADD CONSTRAINT [FK_RadarEnableAutomaticFrequencyControlTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarEnableFastTimeConstantTimeseries]
  ADD CONSTRAINT [FK_RadarEnableFastTimeConstantTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarEnableSensitivityTimeControlTimeseries]
  ADD CONSTRAINT [FK_RadarEnableSensitivityTimeControlTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarPowerOnTimeseries]
  ADD CONSTRAINT [FK_RadarPowerOnTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarSaveSettingsTimeseries]
  ADD CONSTRAINT [FK_RadarSaveSettingsTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarTrackingTimeseries]
  ADD CONSTRAINT [FK_RadarTrackingTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[MediaProxySessionEnabledTimeseries]
  ADD CONSTRAINT [FK_MediaProxySessionEnabledTimeseries_ProxySession] FOREIGN KEY([ProxySession]) REFERENCES [dbo].[MediaProxySession]([Id])
go

ALTER TABLE [dbo].[MediaServiceEnabledTimeseries]
  ADD CONSTRAINT [FK_MediaServiceEnabledTimeseries_Service] FOREIGN KEY([Service]) REFERENCES [dbo].[MediaService]([Id])
go

ALTER TABLE [dbo].[GNSSAltitudeTimeseries]
  ADD CONSTRAINT [FK_GNSSAltitudeTimeseries_GNSSDevice] FOREIGN KEY([GNSSDevice]) REFERENCES [dbo].[GNSSDevice]([Id])
go

ALTER TABLE [dbo].[GNSSLatitudeTimeseries]
  ADD CONSTRAINT [FK_GNSSLatitudeTimeseries_GNSSDevice] FOREIGN KEY([GNSSDevice]) REFERENCES [dbo].[GNSSDevice]([Id])
go

ALTER TABLE [dbo].[GNSSLongitudeTimeseries]
  ADD CONSTRAINT [FK_GNSSLongitudeTimeseries_GNSSDevice] FOREIGN KEY([GNSSDevice]) REFERENCES [dbo].[GNSSDevice]([Id])
go

ALTER TABLE [dbo].[GyroCourseTimeseries]
  ADD CONSTRAINT [FK_GyroCourseTimeseries_GyroDevice] FOREIGN KEY([GyroDevice]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[GyroHeadingMagneticNorthTimeseries]
  ADD CONSTRAINT [FK_GyroHeadingMagneticNorthTimeseries_GyroDevice] FOREIGN KEY([GyroDevice]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[GyroHeadingTrueNorthTimeseries]
  ADD CONSTRAINT [FK_GyroHeadingTrueNorthTimeseries_GyroDevice] FOREIGN KEY([GyroDevice]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[GyroPitchTimeseries]
  ADD CONSTRAINT [FK_GyroPitchTimeseries_GyroDevice] FOREIGN KEY([GyroDevice]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[GyroRateOfTurnTimeseries]
  ADD CONSTRAINT [FK_GyroRateOfTurnTimeseries_GyroDevice] FOREIGN KEY([GyroDevice]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[GyroRollTimeseries]
  ADD CONSTRAINT [FK_GyroRollTimeseries_GyroDevice] FOREIGN KEY([GyroDevice]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[GyroSpeedTimeseries]
  ADD CONSTRAINT [FK_GyroSpeedTimeseries_GyroDevice] FOREIGN KEY([GyroDevice]) REFERENCES [dbo].[GyroDevice]([Id])
go

ALTER TABLE [dbo].[RadarLatitudeTimeseries]
  ADD CONSTRAINT [FK_RadarLatitudeTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarLongitudeTimeseries]
  ADD CONSTRAINT [FK_RadarLongitudeTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadomeDewPointTimeseries]
  ADD CONSTRAINT [FK_RadomeDewPointTimeseries_Radome] FOREIGN KEY([Radome]) REFERENCES [dbo].[Radome]([Id])
go

ALTER TABLE [dbo].[RadomePressureTimeseries]
  ADD CONSTRAINT [FK_RadomePressureTimeseries_Radome] FOREIGN KEY([Radome]) REFERENCES [dbo].[Radome]([Id])
go

ALTER TABLE [dbo].[RadomeTemperatureTimeseries]
  ADD CONSTRAINT [FK_RadomeTemperatureTimeseries_Radome] FOREIGN KEY([Radome]) REFERENCES [dbo].[Radome]([Id])
go

ALTER TABLE [dbo].[VesselDraughtTimeseries]
  ADD CONSTRAINT [FK_VesselDraughtTimeseries_Vessel] FOREIGN KEY([Vessel]) REFERENCES [dbo].[Vessel]([Id])
go

ALTER TABLE [dbo].[ViewLatitudeTimeseries]
  ADD CONSTRAINT [FK_ViewLatitudeTimeseries_View] FOREIGN KEY([View]) REFERENCES [dbo].[View]([Id])
go

ALTER TABLE [dbo].[ViewLongitudeTimeseries]
  ADD CONSTRAINT [FK_ViewLongitudeTimeseries_View] FOREIGN KEY([View]) REFERENCES [dbo].[View]([Id])
go

ALTER TABLE [dbo].[ViewZoomLevelTimeseries]
  ADD CONSTRAINT [FK_ViewZoomLevelTimeseries_View] FOREIGN KEY([View]) REFERENCES [dbo].[View]([Id])
go

ALTER TABLE [dbo].[WeatherStationAbsoluteHumidityTimeseries]
  ADD CONSTRAINT [FK_WeatherStationAbsoluteHumidityTimeseries_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[WeatherStationAirTemperatureTimeseries]
  ADD CONSTRAINT [FK_WeatherStationAirTemperatureTimeseries_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[WeatherStationBarometricPressureTimeseries]
  ADD CONSTRAINT [FK_WeatherStationBarometricPressureTimeseries_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[WeatherStationDewPointTimeseries]
  ADD CONSTRAINT [FK_WeatherStationDewPointTimeseries_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[WeatherStationRelativeHumidityTimeseries]
  ADD CONSTRAINT [FK_WeatherStationRelativeHumidityTimeseries_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[WeatherStationWaterTemperatureTimeseries]
  ADD CONSTRAINT [FK_WeatherStationWaterTemperatureTimeseries_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[WeatherStationWindDirectionTimeseries]
  ADD CONSTRAINT [FK_WeatherStationWindDirectionTimeseries_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[WeatherStationWindSpeedTimeseries]
  ADD CONSTRAINT [FK_WeatherStationWindSpeedTimeseries_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[AisAidToNavigationPositionTimeseries]
  ADD CONSTRAINT [FK_AisAidToNavigationPositionTimeseries_AidToNavigation] FOREIGN KEY([AidToNavigation]) REFERENCES [dbo].[AisAidToNavigation]([Id])
go

ALTER TABLE [dbo].[RadarAzimuthOffsetTimeseries]
  ADD CONSTRAINT [FK_RadarAzimuthOffsetTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarFastTimeConstantLevelTimeseries]
  ADD CONSTRAINT [FK_RadarFastTimeConstantLevelTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarFastTimeConstantModeTimeseries]
  ADD CONSTRAINT [FK_RadarFastTimeConstantModeTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarPulseTimeseries]
  ADD CONSTRAINT [FK_RadarPulseTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarSector1EndTimeseries]
  ADD CONSTRAINT [FK_RadarSector1EndTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarSector1StartTimeseries]
  ADD CONSTRAINT [FK_RadarSector1StartTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarSector2EndTimeseries]
  ADD CONSTRAINT [FK_RadarSector2EndTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarSector2StartTimeseries]
  ADD CONSTRAINT [FK_RadarSector2StartTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarSensitivityTimeControlLevelTimeseries]
  ADD CONSTRAINT [FK_RadarSensitivityTimeControlLevelTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[RadarTuningTimeseries]
  ADD CONSTRAINT [FK_RadarTuningTimeseries_Radar] FOREIGN KEY([Radar]) REFERENCES [dbo].[Radar]([Id])
go

ALTER TABLE [dbo].[VesselPersonsOnBoardTimeseries]
  ADD CONSTRAINT [FK_VesselPersonsOnBoardTimeseries_Vessel] FOREIGN KEY([Vessel]) REFERENCES [dbo].[Vessel]([Id])
go

ALTER TABLE [dbo].[RadomeStatusTimeseries]
  ADD CONSTRAINT [FK_RadomeStatusTimeseries_Radome] FOREIGN KEY([Radome]) REFERENCES [dbo].[Radome]([Id])
go

ALTER TABLE [dbo].[TimeSpanTimeseriesValue]
  ADD CONSTRAINT [FK_TimeSpanTimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[TimeSpanTimeseries]([Id])
go

ALTER TABLE [dbo].[TrackableItemTrackLink]
  ADD CONSTRAINT [FK_TrackableItemTrackLink_Item] FOREIGN KEY([Item]) REFERENCES [dbo].[TrackableItem]([Id])
go

ALTER TABLE [dbo].[TrackableItemTrackLink]
  ADD CONSTRAINT [FK_TrackableItemTrackLink_Track] FOREIGN KEY([Track]) REFERENCES [dbo].[TrackBase]([Id])
go

ALTER TABLE [dbo].[TrackBase]
  ADD CONSTRAINT [FK_TrackBase_Tracker] FOREIGN KEY([Tracker]) REFERENCES [dbo].[Tracker]([Id])
go

ALTER TABLE [dbo].[TrackerFilterParameters]
  ADD CONSTRAINT [FK_TrackerFilterParameters_Tracker] FOREIGN KEY([Tracker]) REFERENCES [dbo].[Tracker]([Id])
go

ALTER TABLE [dbo].[TrackerFilterParametersConfiguration]
  ADD CONSTRAINT [FK_TrackerFilterParametersConfiguration_Parameters] FOREIGN KEY([Parameters]) REFERENCES [dbo].[TrackerFilterParameters]([Id])
go

ALTER TABLE [dbo].[TrackLink]
  ADD CONSTRAINT [FK_TrackLink_Primary] FOREIGN KEY([Primary]) REFERENCES [dbo].[TrackBase]([Id])
go

ALTER TABLE [dbo].[TrackLink]
  ADD CONSTRAINT [FK_TrackLink_Secondary] FOREIGN KEY([Secondary]) REFERENCES [dbo].[TrackBase]([Id])
go

ALTER TABLE [dbo].[TrackValue]
  ADD CONSTRAINT [FK_TrackValue_Track] FOREIGN KEY([Track]) REFERENCES [dbo].[Track]([Id])
go

ALTER TABLE [dbo].[TrackValue3D]
  ADD CONSTRAINT [FK_TrackValue3D_Track] FOREIGN KEY([Track]) REFERENCES [dbo].[Track3D]([Id])
go

ALTER TABLE [dbo].[UInt16TimeseriesValue]
  ADD CONSTRAINT [FK_UInt16TimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[UInt16Timeseries]([Id])
go

ALTER TABLE [dbo].[UInt32TimeseriesValue]
  ADD CONSTRAINT [FK_UInt32TimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[UInt32Timeseries]([Id])
go

ALTER TABLE [dbo].[UInt64TimeseriesValue]
  ADD CONSTRAINT [FK_UInt64TimeseriesValue_Timeseries] FOREIGN KEY([Timeseries]) REFERENCES [dbo].[UInt64Timeseries]([Id])
go

ALTER TABLE [dbo].[View]
  ADD CONSTRAINT [FK_View_LatitudeTimeseries] FOREIGN KEY([LatitudeTimeseries]) REFERENCES [dbo].[ViewLatitudeTimeseries]([Id])
go

ALTER TABLE [dbo].[View]
  ADD CONSTRAINT [FK_View_LongitudeTimeseries] FOREIGN KEY([LongitudeTimeseries]) REFERENCES [dbo].[ViewLongitudeTimeseries]([Id])
go

ALTER TABLE [dbo].[View]
  ADD CONSTRAINT [FK_View_ZoomLevelTimeseries] FOREIGN KEY([ZoomLevelTimeseries]) REFERENCES [dbo].[ViewZoomLevelTimeseries]([Id])
go

ALTER TABLE [dbo].[ViewCameraLink]
  ADD CONSTRAINT [FK_ViewCameraLink_View] FOREIGN KEY([View]) REFERENCES [dbo].[View]([Id])
go

ALTER TABLE [dbo].[ViewCameraLink]
  ADD CONSTRAINT [FK_ViewCameraLink_Camera] FOREIGN KEY([Camera]) REFERENCES [dbo].[Camera]([Id])
go

ALTER TABLE [dbo].[ViewTrackerLink]
  ADD CONSTRAINT [FK_ViewTrackerLink_View] FOREIGN KEY([View]) REFERENCES [dbo].[View]([Id])
go

ALTER TABLE [dbo].[ViewTrackerLink]
  ADD CONSTRAINT [FK_ViewTrackerLink_Tracker] FOREIGN KEY([Tracker]) REFERENCES [dbo].[Tracker]([Id])
go

ALTER TABLE [dbo].[WeatherStationCommand]
  ADD CONSTRAINT [FK_WeatherStationCommand_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[WeatherStationCommand]
  ADD CONSTRAINT [FK_WeatherStationCommand_Reply] FOREIGN KEY([Reply]) REFERENCES [dbo].[WeatherStationCommandReply]([Id])
go

ALTER TABLE [dbo].[WeatherStationCommandReply]
  ADD CONSTRAINT [FK_WeatherStationCommandReply_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[WeatherStationCommandReply]
  ADD CONSTRAINT [FK_WeatherStationCommandReply_Command] FOREIGN KEY([Command]) REFERENCES [dbo].[WeatherStationCommand]([Id])
go

ALTER TABLE [dbo].[WeatherStationConfiguration]
  ADD CONSTRAINT [FK_WeatherStationConfiguration_WeatherStation] FOREIGN KEY([WeatherStation]) REFERENCES [dbo].[WeatherStation]([Id])
go

ALTER TABLE [dbo].[ZoneExceptions]
  ADD CONSTRAINT [FK_ZoneExceptions_Zone] FOREIGN KEY([Zone]) REFERENCES [dbo].[Zone]([Id])
go

ALTER TABLE [dbo].[ZoneExceptionsVesselLink]
  ADD CONSTRAINT [FK_ZoneExceptionsVesselLink_ZoneExceptions] FOREIGN KEY([ZoneExceptions]) REFERENCES [dbo].[ZoneExceptions]([Id])
go

ALTER TABLE [dbo].[ZoneExceptionsVesselLink]
  ADD CONSTRAINT [FK_ZoneExceptionsVesselLink_Vessel] FOREIGN KEY([Vessel]) REFERENCES [dbo].[Vessel]([Id])
go

ALTER TABLE [dbo].[ZoneTrackAlarm]
  ADD CONSTRAINT [FK_ZoneTrackAlarm_Track] FOREIGN KEY([Track]) REFERENCES [dbo].[Track]([Id])
go

ALTER TABLE [dbo].[ZoneTrackAlarm]
  ADD CONSTRAINT [FK_ZoneTrackAlarm_Zone] FOREIGN KEY([Zone]) REFERENCES [dbo].[Zone]([Id])
go

ALTER TABLE [dbo].[ZoneTrackAlarm]
  ADD CONSTRAINT [FK_ZoneTrackAlarm_RadarTrack] FOREIGN KEY([RadarTrack]) REFERENCES [dbo].[Track]([Id])
go

