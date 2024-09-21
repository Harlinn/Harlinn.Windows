CREATE OR ALTER PROCEDURE [AircraftTypeInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AircraftType]([Id], [RowVersion], [Name])
          VALUES(@Id, 0, @Name);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AircraftTypeInsertTrigger]
ON [AircraftTypeView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AircraftTypeInsert] @Id,@RowVersion,@Name
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisDeviceCommandInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisDeviceCommand]([Id], [RowVersion], [AisDevice], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, 0, @AisDevice, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisDeviceCommandInsertTrigger]
ON [AisDeviceCommandView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisDeviceCommandInsert] @Id,@RowVersion,@AisDevice,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisDeviceCommandReplyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisDeviceCommandReply]([Id], [RowVersion], [AisDevice], [Timestamp], [Command], [Status], [Message])
          VALUES(@Id, 0, @AisDevice, @Timestamp, @Command, @Status, @Message);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisDeviceCommandReplyInsertTrigger]
ON [AisDeviceCommandReplyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [Timestamp],
        [Command],
        [Status],
        [Message]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @Timestamp,
        @Command,
        @Status,
        @Message
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisDeviceCommandReplyInsert] @Id,@RowVersion,@AisDevice,@Timestamp,@Command,@Status,@Message
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @Timestamp,
            @Command,
            @Status,
            @Message
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisDeviceConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Filter [bit],
  @NorthWestLatitude [float](53),
  @NorthWestLongitude [float](53),
  @SouthEastLatitude [float](53),
  @SouthEastLongitude [float](53),
  @ComPort [nvarchar](32),
  @BaudRate [int],
  @IPAddress [nvarchar](127),
  @Port [int],
  @UdpPort [int],
  @Authenticate [bit],
  @UserName [nvarchar](127),
  @Password [nvarchar](127),
  @AuthenticationURL [nvarchar](127),
  @ConnectionType [int],
  @SourceUpdateRate [int],
  @ConfigurationURL [nvarchar](127),
  @StoreReceivedSentences [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisDeviceConfiguration]([Id], [RowVersion], [AisDevice], [Timestamp], [Filter], [NorthWestLatitude], [NorthWestLongitude], [SouthEastLatitude], [SouthEastLongitude], [ComPort], [BaudRate], [IPAddress], [Port], [UdpPort], [Authenticate], [UserName], [Password], [AuthenticationURL], [ConnectionType], [SourceUpdateRate], [ConfigurationURL], [StoreReceivedSentences])
          VALUES(@Id, 0, @AisDevice, @Timestamp, @Filter, @NorthWestLatitude, @NorthWestLongitude, @SouthEastLatitude, @SouthEastLongitude, @ComPort, @BaudRate, @IPAddress, @Port, @UdpPort, @Authenticate, @UserName, @Password, @AuthenticationURL, @ConnectionType, @SourceUpdateRate, @ConfigurationURL, @StoreReceivedSentences);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisDeviceConfigurationInsertTrigger]
ON [AisDeviceConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [Timestamp],
        [Filter],
        [NorthWestLatitude],
        [NorthWestLongitude],
        [SouthEastLatitude],
        [SouthEastLongitude],
        [ComPort],
        [BaudRate],
        [IPAddress],
        [Port],
        [UdpPort],
        [Authenticate],
        [UserName],
        [Password],
        [AuthenticationURL],
        [ConnectionType],
        [SourceUpdateRate],
        [ConfigurationURL],
        [StoreReceivedSentences]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Filter [bit]
    DECLARE @NorthWestLatitude [float](53)
    DECLARE @NorthWestLongitude [float](53)
    DECLARE @SouthEastLatitude [float](53)
    DECLARE @SouthEastLongitude [float](53)
    DECLARE @ComPort [nvarchar](32)
    DECLARE @BaudRate [int]
    DECLARE @IPAddress [nvarchar](127)
    DECLARE @Port [int]
    DECLARE @UdpPort [int]
    DECLARE @Authenticate [bit]
    DECLARE @UserName [nvarchar](127)
    DECLARE @Password [nvarchar](127)
    DECLARE @AuthenticationURL [nvarchar](127)
    DECLARE @ConnectionType [int]
    DECLARE @SourceUpdateRate [int]
    DECLARE @ConfigurationURL [nvarchar](127)
    DECLARE @StoreReceivedSentences [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @Timestamp,
        @Filter,
        @NorthWestLatitude,
        @NorthWestLongitude,
        @SouthEastLatitude,
        @SouthEastLongitude,
        @ComPort,
        @BaudRate,
        @IPAddress,
        @Port,
        @UdpPort,
        @Authenticate,
        @UserName,
        @Password,
        @AuthenticationURL,
        @ConnectionType,
        @SourceUpdateRate,
        @ConfigurationURL,
        @StoreReceivedSentences
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisDeviceConfigurationInsert] @Id,@RowVersion,@AisDevice,@Timestamp,@Filter,@NorthWestLatitude,@NorthWestLongitude,@SouthEastLatitude,@SouthEastLongitude,@ComPort,@BaudRate,@IPAddress,@Port,@UdpPort,@Authenticate,@UserName,@Password,@AuthenticationURL,@ConnectionType,@SourceUpdateRate,@ConfigurationURL,@StoreReceivedSentences
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @Timestamp,
            @Filter,
            @NorthWestLatitude,
            @NorthWestLongitude,
            @SouthEastLatitude,
            @SouthEastLongitude,
            @ComPort,
            @BaudRate,
            @IPAddress,
            @Port,
            @UdpPort,
            @Authenticate,
            @UserName,
            @Password,
            @AuthenticationURL,
            @ConnectionType,
            @SourceUpdateRate,
            @ConfigurationURL,
            @StoreReceivedSentences
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisDeviceRawMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @Timestamp [bigint],
  @IsSent [bit],
  @Message [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisDeviceRawMessage]([Id], [RowVersion], [AisDevice], [Timestamp], [IsSent], [Message])
          VALUES(@Id, 0, @AisDevice, @Timestamp, @IsSent, @Message);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisDeviceRawMessageInsertTrigger]
ON [AisDeviceRawMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [Timestamp],
        [IsSent],
        [Message]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @IsSent [bit]
    DECLARE @Message [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @Timestamp,
        @IsSent,
        @Message
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisDeviceRawMessageInsert] @Id,@RowVersion,@AisDevice,@Timestamp,@IsSent,@Message
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @Timestamp,
            @IsSent,
            @Message
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisDeviceRawSentenceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Sentence [nvarchar](1024)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisDeviceRawSentence]([Id], [RowVersion], [AisDevice], [Timestamp], [Sentence])
          VALUES(@Id, 0, @AisDevice, @Timestamp, @Sentence);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisDeviceRawSentenceInsertTrigger]
ON [AisDeviceRawSentenceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [Timestamp],
        [Sentence]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Sentence [nvarchar](1024)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @Timestamp,
        @Sentence
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisDeviceRawSentenceInsert] @Id,@RowVersion,@AisDevice,@Timestamp,@Sentence
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @Timestamp,
            @Sentence
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AidToNavigationReportMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @NavigationalAidType [int],
  @Name [nvarchar](127),
  @PositionAccuracy [int],
  @Longitude [float](53),
  @Latitude [float](53),
  @DimensionToBow [int],
  @DimensionToStern [int],
  @DimensionToPort [int],
  @DimensionToStarboard [int],
  @PositionFixType [int],
  @Timestamp [int],
  @OffPosition [bit],
  @RegionalReserved [int],
  @Raim [int],
  @VirtualAid [bit],
  @Assigned [bit],
  @Spare [int],
  @NameExtension [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 10700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AidToNavigationReportMessage]([Id], [NavigationalAidType], [Name], [PositionAccuracy], [Longitude], [Latitude], [DimensionToBow], [DimensionToStern], [DimensionToPort], [DimensionToStarboard], [PositionFixType], [Timestamp], [OffPosition], [RegionalReserved], [Raim], [VirtualAid], [Assigned], [Spare], [NameExtension])
          VALUES(@Id, @NavigationalAidType, @Name, @PositionAccuracy, @Longitude, @Latitude, @DimensionToBow, @DimensionToStern, @DimensionToPort, @DimensionToStarboard, @PositionFixType, @Timestamp, @OffPosition, @RegionalReserved, @Raim, @VirtualAid, @Assigned, @Spare, @NameExtension);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AidToNavigationReportMessageInsertTrigger]
ON [AidToNavigationReportMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [NavigationalAidType],
        [Name],
        [PositionAccuracy],
        [Longitude],
        [Latitude],
        [DimensionToBow],
        [DimensionToStern],
        [DimensionToPort],
        [DimensionToStarboard],
        [PositionFixType],
        [Timestamp],
        [OffPosition],
        [RegionalReserved],
        [Raim],
        [VirtualAid],
        [Assigned],
        [Spare],
        [NameExtension]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @NavigationalAidType [int]
    DECLARE @Name [nvarchar](127)
    DECLARE @PositionAccuracy [int]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @DimensionToBow [int]
    DECLARE @DimensionToStern [int]
    DECLARE @DimensionToPort [int]
    DECLARE @DimensionToStarboard [int]
    DECLARE @PositionFixType [int]
    DECLARE @Timestamp [int]
    DECLARE @OffPosition [bit]
    DECLARE @RegionalReserved [int]
    DECLARE @Raim [int]
    DECLARE @VirtualAid [bit]
    DECLARE @Assigned [bit]
    DECLARE @Spare [int]
    DECLARE @NameExtension [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @NavigationalAidType,
        @Name,
        @PositionAccuracy,
        @Longitude,
        @Latitude,
        @DimensionToBow,
        @DimensionToStern,
        @DimensionToPort,
        @DimensionToStarboard,
        @PositionFixType,
        @Timestamp,
        @OffPosition,
        @RegionalReserved,
        @Raim,
        @VirtualAid,
        @Assigned,
        @Spare,
        @NameExtension
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AidToNavigationReportMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@NavigationalAidType,@Name,@PositionAccuracy,@Longitude,@Latitude,@DimensionToBow,@DimensionToStern,@DimensionToPort,@DimensionToStarboard,@PositionFixType,@Timestamp,@OffPosition,@RegionalReserved,@Raim,@VirtualAid,@Assigned,@Spare,@NameExtension
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @NavigationalAidType,
            @Name,
            @PositionAccuracy,
            @Longitude,
            @Latitude,
            @DimensionToBow,
            @DimensionToStern,
            @DimensionToPort,
            @DimensionToStarboard,
            @PositionFixType,
            @Timestamp,
            @OffPosition,
            @RegionalReserved,
            @Raim,
            @VirtualAid,
            @Assigned,
            @Spare,
            @NameExtension
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisAddressedSafetyRelatedMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @SequenceNumber [int],
  @DestinationMmsi [uniqueidentifier],
  @RetransmitFlag [bit],
  @Spare [int],
  @Text [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 10800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisAddressedSafetyRelatedMessage]([Id], [SequenceNumber], [DestinationMmsi], [RetransmitFlag], [Spare], [Text])
          VALUES(@Id, @SequenceNumber, @DestinationMmsi, @RetransmitFlag, @Spare, @Text);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisAddressedSafetyRelatedMessageInsertTrigger]
ON [AisAddressedSafetyRelatedMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [SequenceNumber],
        [DestinationMmsi],
        [RetransmitFlag],
        [Spare],
        [Text]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @SequenceNumber [int]
    DECLARE @DestinationMmsi [uniqueidentifier]
    DECLARE @RetransmitFlag [bit]
    DECLARE @Spare [int]
    DECLARE @Text [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @SequenceNumber,
        @DestinationMmsi,
        @RetransmitFlag,
        @Spare,
        @Text
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisAddressedSafetyRelatedMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@SequenceNumber,@DestinationMmsi,@RetransmitFlag,@Spare,@Text
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @SequenceNumber,
            @DestinationMmsi,
            @RetransmitFlag,
            @Spare,
            @Text
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisBaseStationReportMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Timestamp [bigint],
  @PositionAccuracy [int],
  @Longitude [float](53),
  @Latitude [float](53),
  @PositionFixType [int],
  @Spare [int],
  @Raim [int],
  @RadioStatus [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 10900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisBaseStationReportMessage]([Id], [Timestamp], [PositionAccuracy], [Longitude], [Latitude], [PositionFixType], [Spare], [Raim], [RadioStatus])
          VALUES(@Id, @Timestamp, @PositionAccuracy, @Longitude, @Latitude, @PositionFixType, @Spare, @Raim, @RadioStatus);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisBaseStationReportMessageInsertTrigger]
ON [AisBaseStationReportMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [Timestamp],
        [PositionAccuracy],
        [Longitude],
        [Latitude],
        [PositionFixType],
        [Spare],
        [Raim],
        [RadioStatus]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @PositionAccuracy [int]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @PositionFixType [int]
    DECLARE @Spare [int]
    DECLARE @Raim [int]
    DECLARE @RadioStatus [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @Timestamp,
        @PositionAccuracy,
        @Longitude,
        @Latitude,
        @PositionFixType,
        @Spare,
        @Raim,
        @RadioStatus
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisBaseStationReportMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@Timestamp,@PositionAccuracy,@Longitude,@Latitude,@PositionFixType,@Spare,@Raim,@RadioStatus
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @Timestamp,
            @PositionAccuracy,
            @Longitude,
            @Latitude,
            @PositionFixType,
            @Spare,
            @Raim,
            @RadioStatus
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisBinaryAcknowledgeMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Spare [int],
  @SequenceNumber1 [int],
  @Mmsi1 [uniqueidentifier],
  @SequenceNumber2 [int],
  @Mmsi2 [uniqueidentifier],
  @SequenceNumber3 [int],
  @Mmsi3 [uniqueidentifier],
  @SequenceNumber4 [int],
  @Mmsi4 [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 11000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisBinaryAcknowledgeMessage]([Id], [Spare], [SequenceNumber1], [Mmsi1], [SequenceNumber2], [Mmsi2], [SequenceNumber3], [Mmsi3], [SequenceNumber4], [Mmsi4])
          VALUES(@Id, @Spare, @SequenceNumber1, @Mmsi1, @SequenceNumber2, @Mmsi2, @SequenceNumber3, @Mmsi3, @SequenceNumber4, @Mmsi4);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisBinaryAcknowledgeMessageInsertTrigger]
ON [AisBinaryAcknowledgeMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [Spare],
        [SequenceNumber1],
        [Mmsi1],
        [SequenceNumber2],
        [Mmsi2],
        [SequenceNumber3],
        [Mmsi3],
        [SequenceNumber4],
        [Mmsi4]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @Spare [int]
    DECLARE @SequenceNumber1 [int]
    DECLARE @Mmsi1 [uniqueidentifier]
    DECLARE @SequenceNumber2 [int]
    DECLARE @Mmsi2 [uniqueidentifier]
    DECLARE @SequenceNumber3 [int]
    DECLARE @Mmsi3 [uniqueidentifier]
    DECLARE @SequenceNumber4 [int]
    DECLARE @Mmsi4 [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @Spare,
        @SequenceNumber1,
        @Mmsi1,
        @SequenceNumber2,
        @Mmsi2,
        @SequenceNumber3,
        @Mmsi3,
        @SequenceNumber4,
        @Mmsi4
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisBinaryAcknowledgeMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@Spare,@SequenceNumber1,@Mmsi1,@SequenceNumber2,@Mmsi2,@SequenceNumber3,@Mmsi3,@SequenceNumber4,@Mmsi4
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @Spare,
            @SequenceNumber1,
            @Mmsi1,
            @SequenceNumber2,
            @Mmsi2,
            @SequenceNumber3,
            @Mmsi3,
            @SequenceNumber4,
            @Mmsi4
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisBinaryAddressedMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @SequenceNumber [int],
  @DestinationMmsi [uniqueidentifier],
  @RetransmitFlag [bit],
  @Spare [int],
  @DesignatedAreaCode [int],
  @FunctionalId [int],
  @Data [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 11100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisBinaryAddressedMessage]([Id], [SequenceNumber], [DestinationMmsi], [RetransmitFlag], [Spare], [DesignatedAreaCode], [FunctionalId], [Data])
          VALUES(@Id, @SequenceNumber, @DestinationMmsi, @RetransmitFlag, @Spare, @DesignatedAreaCode, @FunctionalId, @Data);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisBinaryAddressedMessageInsertTrigger]
ON [AisBinaryAddressedMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [SequenceNumber],
        [DestinationMmsi],
        [RetransmitFlag],
        [Spare],
        [DesignatedAreaCode],
        [FunctionalId],
        [Data]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @SequenceNumber [int]
    DECLARE @DestinationMmsi [uniqueidentifier]
    DECLARE @RetransmitFlag [bit]
    DECLARE @Spare [int]
    DECLARE @DesignatedAreaCode [int]
    DECLARE @FunctionalId [int]
    DECLARE @Data [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @SequenceNumber,
        @DestinationMmsi,
        @RetransmitFlag,
        @Spare,
        @DesignatedAreaCode,
        @FunctionalId,
        @Data
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisBinaryAddressedMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@SequenceNumber,@DestinationMmsi,@RetransmitFlag,@Spare,@DesignatedAreaCode,@FunctionalId,@Data
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @SequenceNumber,
            @DestinationMmsi,
            @RetransmitFlag,
            @Spare,
            @DesignatedAreaCode,
            @FunctionalId,
            @Data
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisBinaryBroadcastMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Spare [int],
  @DesignatedAreaCode [int],
  @FunctionalId [int],
  @Data [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 11200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisBinaryBroadcastMessage]([Id], [Spare], [DesignatedAreaCode], [FunctionalId], [Data])
          VALUES(@Id, @Spare, @DesignatedAreaCode, @FunctionalId, @Data);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisBinaryBroadcastMessageInsertTrigger]
ON [AisBinaryBroadcastMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [Spare],
        [DesignatedAreaCode],
        [FunctionalId],
        [Data]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @Spare [int]
    DECLARE @DesignatedAreaCode [int]
    DECLARE @FunctionalId [int]
    DECLARE @Data [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @Spare,
        @DesignatedAreaCode,
        @FunctionalId,
        @Data
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisBinaryBroadcastMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@Spare,@DesignatedAreaCode,@FunctionalId,@Data
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @Spare,
            @DesignatedAreaCode,
            @FunctionalId,
            @Data
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisDataLinkManagementMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Spare [int],
  @Offset1 [int],
  @ReservedSlots1 [int],
  @Timeout1 [int],
  @Increment1 [int],
  @Offset2 [int],
  @ReservedSlots2 [int],
  @Timeout2 [int],
  @Increment2 [int],
  @Offset3 [int],
  @ReservedSlots3 [int],
  @Timeout3 [int],
  @Increment3 [int],
  @Offset4 [int],
  @ReservedSlots4 [int],
  @Timeout4 [int],
  @Increment4 [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 11300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisDataLinkManagementMessage]([Id], [Spare], [Offset1], [ReservedSlots1], [Timeout1], [Increment1], [Offset2], [ReservedSlots2], [Timeout2], [Increment2], [Offset3], [ReservedSlots3], [Timeout3], [Increment3], [Offset4], [ReservedSlots4], [Timeout4], [Increment4])
          VALUES(@Id, @Spare, @Offset1, @ReservedSlots1, @Timeout1, @Increment1, @Offset2, @ReservedSlots2, @Timeout2, @Increment2, @Offset3, @ReservedSlots3, @Timeout3, @Increment3, @Offset4, @ReservedSlots4, @Timeout4, @Increment4);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisDataLinkManagementMessageInsertTrigger]
ON [AisDataLinkManagementMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [Spare],
        [Offset1],
        [ReservedSlots1],
        [Timeout1],
        [Increment1],
        [Offset2],
        [ReservedSlots2],
        [Timeout2],
        [Increment2],
        [Offset3],
        [ReservedSlots3],
        [Timeout3],
        [Increment3],
        [Offset4],
        [ReservedSlots4],
        [Timeout4],
        [Increment4]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @Spare [int]
    DECLARE @Offset1 [int]
    DECLARE @ReservedSlots1 [int]
    DECLARE @Timeout1 [int]
    DECLARE @Increment1 [int]
    DECLARE @Offset2 [int]
    DECLARE @ReservedSlots2 [int]
    DECLARE @Timeout2 [int]
    DECLARE @Increment2 [int]
    DECLARE @Offset3 [int]
    DECLARE @ReservedSlots3 [int]
    DECLARE @Timeout3 [int]
    DECLARE @Increment3 [int]
    DECLARE @Offset4 [int]
    DECLARE @ReservedSlots4 [int]
    DECLARE @Timeout4 [int]
    DECLARE @Increment4 [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @Spare,
        @Offset1,
        @ReservedSlots1,
        @Timeout1,
        @Increment1,
        @Offset2,
        @ReservedSlots2,
        @Timeout2,
        @Increment2,
        @Offset3,
        @ReservedSlots3,
        @Timeout3,
        @Increment3,
        @Offset4,
        @ReservedSlots4,
        @Timeout4,
        @Increment4
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisDataLinkManagementMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@Spare,@Offset1,@ReservedSlots1,@Timeout1,@Increment1,@Offset2,@ReservedSlots2,@Timeout2,@Increment2,@Offset3,@ReservedSlots3,@Timeout3,@Increment3,@Offset4,@ReservedSlots4,@Timeout4,@Increment4
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @Spare,
            @Offset1,
            @ReservedSlots1,
            @Timeout1,
            @Increment1,
            @Offset2,
            @ReservedSlots2,
            @Timeout2,
            @Increment2,
            @Offset3,
            @ReservedSlots3,
            @Timeout3,
            @Increment3,
            @Offset4,
            @ReservedSlots4,
            @Timeout4,
            @Increment4
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisExtendedClassBCsPositionReportMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Reserved [int],
  @SpeedOverGround [float](53),
  @PositionAccuracy [int],
  @Longitude [float](53),
  @Latitude [float](53),
  @CourseOverGround [float](53),
  @TrueHeading [int],
  @Timestamp [int],
  @RegionalReserved [int],
  @Name [uniqueidentifier],
  @ShipType [int],
  @DimensionToBow [int],
  @DimensionToStern [int],
  @DimensionToPort [int],
  @DimensionToStarboard [int],
  @PositionFixType [int],
  @Raim [int],
  @DataTerminalReady [bit],
  @Assigned [bit],
  @Spare [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 11400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisExtendedClassBCsPositionReportMessage]([Id], [Reserved], [SpeedOverGround], [PositionAccuracy], [Longitude], [Latitude], [CourseOverGround], [TrueHeading], [Timestamp], [RegionalReserved], [Name], [ShipType], [DimensionToBow], [DimensionToStern], [DimensionToPort], [DimensionToStarboard], [PositionFixType], [Raim], [DataTerminalReady], [Assigned], [Spare])
          VALUES(@Id, @Reserved, @SpeedOverGround, @PositionAccuracy, @Longitude, @Latitude, @CourseOverGround, @TrueHeading, @Timestamp, @RegionalReserved, @Name, @ShipType, @DimensionToBow, @DimensionToStern, @DimensionToPort, @DimensionToStarboard, @PositionFixType, @Raim, @DataTerminalReady, @Assigned, @Spare);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisExtendedClassBCsPositionReportMessageInsertTrigger]
ON [AisExtendedClassBCsPositionReportMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [Reserved],
        [SpeedOverGround],
        [PositionAccuracy],
        [Longitude],
        [Latitude],
        [CourseOverGround],
        [TrueHeading],
        [Timestamp],
        [RegionalReserved],
        [Name],
        [ShipType],
        [DimensionToBow],
        [DimensionToStern],
        [DimensionToPort],
        [DimensionToStarboard],
        [PositionFixType],
        [Raim],
        [DataTerminalReady],
        [Assigned],
        [Spare]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @Reserved [int]
    DECLARE @SpeedOverGround [float](53)
    DECLARE @PositionAccuracy [int]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @CourseOverGround [float](53)
    DECLARE @TrueHeading [int]
    DECLARE @Timestamp [int]
    DECLARE @RegionalReserved [int]
    DECLARE @Name [uniqueidentifier]
    DECLARE @ShipType [int]
    DECLARE @DimensionToBow [int]
    DECLARE @DimensionToStern [int]
    DECLARE @DimensionToPort [int]
    DECLARE @DimensionToStarboard [int]
    DECLARE @PositionFixType [int]
    DECLARE @Raim [int]
    DECLARE @DataTerminalReady [bit]
    DECLARE @Assigned [bit]
    DECLARE @Spare [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @Reserved,
        @SpeedOverGround,
        @PositionAccuracy,
        @Longitude,
        @Latitude,
        @CourseOverGround,
        @TrueHeading,
        @Timestamp,
        @RegionalReserved,
        @Name,
        @ShipType,
        @DimensionToBow,
        @DimensionToStern,
        @DimensionToPort,
        @DimensionToStarboard,
        @PositionFixType,
        @Raim,
        @DataTerminalReady,
        @Assigned,
        @Spare
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisExtendedClassBCsPositionReportMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@Reserved,@SpeedOverGround,@PositionAccuracy,@Longitude,@Latitude,@CourseOverGround,@TrueHeading,@Timestamp,@RegionalReserved,@Name,@ShipType,@DimensionToBow,@DimensionToStern,@DimensionToPort,@DimensionToStarboard,@PositionFixType,@Raim,@DataTerminalReady,@Assigned,@Spare
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @Reserved,
            @SpeedOverGround,
            @PositionAccuracy,
            @Longitude,
            @Latitude,
            @CourseOverGround,
            @TrueHeading,
            @Timestamp,
            @RegionalReserved,
            @Name,
            @ShipType,
            @DimensionToBow,
            @DimensionToStern,
            @DimensionToPort,
            @DimensionToStarboard,
            @PositionFixType,
            @Raim,
            @DataTerminalReady,
            @Assigned,
            @Spare
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisInterrogationMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @InterrogatedMmsi [uniqueidentifier],
  @FirstMessageType [int],
  @FirstSlotOffset [int],
  @SecondMessageType [int],
  @SecondSlotOffset [int],
  @SecondStationInterrogationMmsi [uniqueidentifier],
  @SecondStationFirstMessageType [int],
  @SecondStationFirstSlotOffset [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 11500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisInterrogationMessage]([Id], [InterrogatedMmsi], [FirstMessageType], [FirstSlotOffset], [SecondMessageType], [SecondSlotOffset], [SecondStationInterrogationMmsi], [SecondStationFirstMessageType], [SecondStationFirstSlotOffset])
          VALUES(@Id, @InterrogatedMmsi, @FirstMessageType, @FirstSlotOffset, @SecondMessageType, @SecondSlotOffset, @SecondStationInterrogationMmsi, @SecondStationFirstMessageType, @SecondStationFirstSlotOffset);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisInterrogationMessageInsertTrigger]
ON [AisInterrogationMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [InterrogatedMmsi],
        [FirstMessageType],
        [FirstSlotOffset],
        [SecondMessageType],
        [SecondSlotOffset],
        [SecondStationInterrogationMmsi],
        [SecondStationFirstMessageType],
        [SecondStationFirstSlotOffset]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @InterrogatedMmsi [uniqueidentifier]
    DECLARE @FirstMessageType [int]
    DECLARE @FirstSlotOffset [int]
    DECLARE @SecondMessageType [int]
    DECLARE @SecondSlotOffset [int]
    DECLARE @SecondStationInterrogationMmsi [uniqueidentifier]
    DECLARE @SecondStationFirstMessageType [int]
    DECLARE @SecondStationFirstSlotOffset [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @InterrogatedMmsi,
        @FirstMessageType,
        @FirstSlotOffset,
        @SecondMessageType,
        @SecondSlotOffset,
        @SecondStationInterrogationMmsi,
        @SecondStationFirstMessageType,
        @SecondStationFirstSlotOffset
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisInterrogationMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@InterrogatedMmsi,@FirstMessageType,@FirstSlotOffset,@SecondMessageType,@SecondSlotOffset,@SecondStationInterrogationMmsi,@SecondStationFirstMessageType,@SecondStationFirstSlotOffset
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @InterrogatedMmsi,
            @FirstMessageType,
            @FirstSlotOffset,
            @SecondMessageType,
            @SecondSlotOffset,
            @SecondStationInterrogationMmsi,
            @SecondStationFirstMessageType,
            @SecondStationFirstSlotOffset
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisPositionReportClassAAssignedScheduleMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @NavigationStatus [int],
  @RateOfTurn [int],
  @SpeedOverGround [float](53),
  @PositionAccuracy [int],
  @Longitude [float](53),
  @Latitude [float](53),
  @CourseOverGround [float](53),
  @TrueHeading [int],
  @Timestamp [int],
  @ManeuverIndicator [int],
  @Spare [int],
  @Raim [int],
  @RadioStatus [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 11700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisPositionReportClassAMessageBase]([Id], [NavigationStatus], [RateOfTurn], [SpeedOverGround], [PositionAccuracy], [Longitude], [Latitude], [CourseOverGround], [TrueHeading], [Timestamp], [ManeuverIndicator], [Spare], [Raim], [RadioStatus])
          VALUES(@Id, @NavigationStatus, @RateOfTurn, @SpeedOverGround, @PositionAccuracy, @Longitude, @Latitude, @CourseOverGround, @TrueHeading, @Timestamp, @ManeuverIndicator, @Spare, @Raim, @RadioStatus);
      INSERT INTO [AisPositionReportClassAAssignedScheduleMessage]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisPositionReportClassAAssignedScheduleMessageInsertTrigger]
ON [AisPositionReportClassAAssignedScheduleMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [NavigationStatus],
        [RateOfTurn],
        [SpeedOverGround],
        [PositionAccuracy],
        [Longitude],
        [Latitude],
        [CourseOverGround],
        [TrueHeading],
        [Timestamp],
        [ManeuverIndicator],
        [Spare],
        [Raim],
        [RadioStatus]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @NavigationStatus [int]
    DECLARE @RateOfTurn [int]
    DECLARE @SpeedOverGround [float](53)
    DECLARE @PositionAccuracy [int]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @CourseOverGround [float](53)
    DECLARE @TrueHeading [int]
    DECLARE @Timestamp [int]
    DECLARE @ManeuverIndicator [int]
    DECLARE @Spare [int]
    DECLARE @Raim [int]
    DECLARE @RadioStatus [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @NavigationStatus,
        @RateOfTurn,
        @SpeedOverGround,
        @PositionAccuracy,
        @Longitude,
        @Latitude,
        @CourseOverGround,
        @TrueHeading,
        @Timestamp,
        @ManeuverIndicator,
        @Spare,
        @Raim,
        @RadioStatus
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisPositionReportClassAAssignedScheduleMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@NavigationStatus,@RateOfTurn,@SpeedOverGround,@PositionAccuracy,@Longitude,@Latitude,@CourseOverGround,@TrueHeading,@Timestamp,@ManeuverIndicator,@Spare,@Raim,@RadioStatus
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @NavigationStatus,
            @RateOfTurn,
            @SpeedOverGround,
            @PositionAccuracy,
            @Longitude,
            @Latitude,
            @CourseOverGround,
            @TrueHeading,
            @Timestamp,
            @ManeuverIndicator,
            @Spare,
            @Raim,
            @RadioStatus
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisPositionReportClassAMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @NavigationStatus [int],
  @RateOfTurn [int],
  @SpeedOverGround [float](53),
  @PositionAccuracy [int],
  @Longitude [float](53),
  @Latitude [float](53),
  @CourseOverGround [float](53),
  @TrueHeading [int],
  @Timestamp [int],
  @ManeuverIndicator [int],
  @Spare [int],
  @Raim [int],
  @RadioStatus [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 11800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisPositionReportClassAMessageBase]([Id], [NavigationStatus], [RateOfTurn], [SpeedOverGround], [PositionAccuracy], [Longitude], [Latitude], [CourseOverGround], [TrueHeading], [Timestamp], [ManeuverIndicator], [Spare], [Raim], [RadioStatus])
          VALUES(@Id, @NavigationStatus, @RateOfTurn, @SpeedOverGround, @PositionAccuracy, @Longitude, @Latitude, @CourseOverGround, @TrueHeading, @Timestamp, @ManeuverIndicator, @Spare, @Raim, @RadioStatus);
      INSERT INTO [AisPositionReportClassAMessage]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisPositionReportClassAMessageInsertTrigger]
ON [AisPositionReportClassAMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [NavigationStatus],
        [RateOfTurn],
        [SpeedOverGround],
        [PositionAccuracy],
        [Longitude],
        [Latitude],
        [CourseOverGround],
        [TrueHeading],
        [Timestamp],
        [ManeuverIndicator],
        [Spare],
        [Raim],
        [RadioStatus]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @NavigationStatus [int]
    DECLARE @RateOfTurn [int]
    DECLARE @SpeedOverGround [float](53)
    DECLARE @PositionAccuracy [int]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @CourseOverGround [float](53)
    DECLARE @TrueHeading [int]
    DECLARE @Timestamp [int]
    DECLARE @ManeuverIndicator [int]
    DECLARE @Spare [int]
    DECLARE @Raim [int]
    DECLARE @RadioStatus [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @NavigationStatus,
        @RateOfTurn,
        @SpeedOverGround,
        @PositionAccuracy,
        @Longitude,
        @Latitude,
        @CourseOverGround,
        @TrueHeading,
        @Timestamp,
        @ManeuverIndicator,
        @Spare,
        @Raim,
        @RadioStatus
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisPositionReportClassAMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@NavigationStatus,@RateOfTurn,@SpeedOverGround,@PositionAccuracy,@Longitude,@Latitude,@CourseOverGround,@TrueHeading,@Timestamp,@ManeuverIndicator,@Spare,@Raim,@RadioStatus
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @NavigationStatus,
            @RateOfTurn,
            @SpeedOverGround,
            @PositionAccuracy,
            @Longitude,
            @Latitude,
            @CourseOverGround,
            @TrueHeading,
            @Timestamp,
            @ManeuverIndicator,
            @Spare,
            @Raim,
            @RadioStatus
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisPositionReportClassAResponseToInterrogationMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @NavigationStatus [int],
  @RateOfTurn [int],
  @SpeedOverGround [float](53),
  @PositionAccuracy [int],
  @Longitude [float](53),
  @Latitude [float](53),
  @CourseOverGround [float](53),
  @TrueHeading [int],
  @Timestamp [int],
  @ManeuverIndicator [int],
  @Spare [int],
  @Raim [int],
  @RadioStatus [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 11900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisPositionReportClassAMessageBase]([Id], [NavigationStatus], [RateOfTurn], [SpeedOverGround], [PositionAccuracy], [Longitude], [Latitude], [CourseOverGround], [TrueHeading], [Timestamp], [ManeuverIndicator], [Spare], [Raim], [RadioStatus])
          VALUES(@Id, @NavigationStatus, @RateOfTurn, @SpeedOverGround, @PositionAccuracy, @Longitude, @Latitude, @CourseOverGround, @TrueHeading, @Timestamp, @ManeuverIndicator, @Spare, @Raim, @RadioStatus);
      INSERT INTO [AisPositionReportClassAResponseToInterrogationMessage]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisPositionReportClassAResponseToInterrogationMessageInsertTrigger]
ON [AisPositionReportClassAResponseToInterrogationMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [NavigationStatus],
        [RateOfTurn],
        [SpeedOverGround],
        [PositionAccuracy],
        [Longitude],
        [Latitude],
        [CourseOverGround],
        [TrueHeading],
        [Timestamp],
        [ManeuverIndicator],
        [Spare],
        [Raim],
        [RadioStatus]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @NavigationStatus [int]
    DECLARE @RateOfTurn [int]
    DECLARE @SpeedOverGround [float](53)
    DECLARE @PositionAccuracy [int]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @CourseOverGround [float](53)
    DECLARE @TrueHeading [int]
    DECLARE @Timestamp [int]
    DECLARE @ManeuverIndicator [int]
    DECLARE @Spare [int]
    DECLARE @Raim [int]
    DECLARE @RadioStatus [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @NavigationStatus,
        @RateOfTurn,
        @SpeedOverGround,
        @PositionAccuracy,
        @Longitude,
        @Latitude,
        @CourseOverGround,
        @TrueHeading,
        @Timestamp,
        @ManeuverIndicator,
        @Spare,
        @Raim,
        @RadioStatus
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisPositionReportClassAResponseToInterrogationMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@NavigationStatus,@RateOfTurn,@SpeedOverGround,@PositionAccuracy,@Longitude,@Latitude,@CourseOverGround,@TrueHeading,@Timestamp,@ManeuverIndicator,@Spare,@Raim,@RadioStatus
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @NavigationStatus,
            @RateOfTurn,
            @SpeedOverGround,
            @PositionAccuracy,
            @Longitude,
            @Latitude,
            @CourseOverGround,
            @TrueHeading,
            @Timestamp,
            @ManeuverIndicator,
            @Spare,
            @Raim,
            @RadioStatus
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisPositionReportForLongRangeApplicationsMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @PositionAccuracy [int],
  @Raim [int],
  @NavigationStatus [int],
  @Longitude [float](53),
  @Latitude [float](53),
  @SpeedOverGround [float](53),
  @CourseOverGround [float](53),
  @GnssPositionStatus [int],
  @Spare [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 12000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisPositionReportForLongRangeApplicationsMessage]([Id], [PositionAccuracy], [Raim], [NavigationStatus], [Longitude], [Latitude], [SpeedOverGround], [CourseOverGround], [GnssPositionStatus], [Spare])
          VALUES(@Id, @PositionAccuracy, @Raim, @NavigationStatus, @Longitude, @Latitude, @SpeedOverGround, @CourseOverGround, @GnssPositionStatus, @Spare);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisPositionReportForLongRangeApplicationsMessageInsertTrigger]
ON [AisPositionReportForLongRangeApplicationsMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [PositionAccuracy],
        [Raim],
        [NavigationStatus],
        [Longitude],
        [Latitude],
        [SpeedOverGround],
        [CourseOverGround],
        [GnssPositionStatus],
        [Spare]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @PositionAccuracy [int]
    DECLARE @Raim [int]
    DECLARE @NavigationStatus [int]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @SpeedOverGround [float](53)
    DECLARE @CourseOverGround [float](53)
    DECLARE @GnssPositionStatus [int]
    DECLARE @Spare [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @PositionAccuracy,
        @Raim,
        @NavigationStatus,
        @Longitude,
        @Latitude,
        @SpeedOverGround,
        @CourseOverGround,
        @GnssPositionStatus,
        @Spare
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisPositionReportForLongRangeApplicationsMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@PositionAccuracy,@Raim,@NavigationStatus,@Longitude,@Latitude,@SpeedOverGround,@CourseOverGround,@GnssPositionStatus,@Spare
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @PositionAccuracy,
            @Raim,
            @NavigationStatus,
            @Longitude,
            @Latitude,
            @SpeedOverGround,
            @CourseOverGround,
            @GnssPositionStatus,
            @Spare
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisSafetyRelatedAcknowledgmentMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Spare [int],
  @SequenceNumber1 [int],
  @Mmsi1 [uniqueidentifier],
  @SequenceNumber2 [int],
  @Mmsi2 [uniqueidentifier],
  @SequenceNumber3 [int],
  @Mmsi3 [uniqueidentifier],
  @SequenceNumber4 [int],
  @Mmsi4 [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 12100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisSafetyRelatedAcknowledgmentMessage]([Id], [Spare], [SequenceNumber1], [Mmsi1], [SequenceNumber2], [Mmsi2], [SequenceNumber3], [Mmsi3], [SequenceNumber4], [Mmsi4])
          VALUES(@Id, @Spare, @SequenceNumber1, @Mmsi1, @SequenceNumber2, @Mmsi2, @SequenceNumber3, @Mmsi3, @SequenceNumber4, @Mmsi4);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisSafetyRelatedAcknowledgmentMessageInsertTrigger]
ON [AisSafetyRelatedAcknowledgmentMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [Spare],
        [SequenceNumber1],
        [Mmsi1],
        [SequenceNumber2],
        [Mmsi2],
        [SequenceNumber3],
        [Mmsi3],
        [SequenceNumber4],
        [Mmsi4]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @Spare [int]
    DECLARE @SequenceNumber1 [int]
    DECLARE @Mmsi1 [uniqueidentifier]
    DECLARE @SequenceNumber2 [int]
    DECLARE @Mmsi2 [uniqueidentifier]
    DECLARE @SequenceNumber3 [int]
    DECLARE @Mmsi3 [uniqueidentifier]
    DECLARE @SequenceNumber4 [int]
    DECLARE @Mmsi4 [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @Spare,
        @SequenceNumber1,
        @Mmsi1,
        @SequenceNumber2,
        @Mmsi2,
        @SequenceNumber3,
        @Mmsi3,
        @SequenceNumber4,
        @Mmsi4
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisSafetyRelatedAcknowledgmentMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@Spare,@SequenceNumber1,@Mmsi1,@SequenceNumber2,@Mmsi2,@SequenceNumber3,@Mmsi3,@SequenceNumber4,@Mmsi4
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @Spare,
            @SequenceNumber1,
            @Mmsi1,
            @SequenceNumber2,
            @Mmsi2,
            @SequenceNumber3,
            @Mmsi3,
            @SequenceNumber4,
            @Mmsi4
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisStandardClassBCsPositionReportMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Reserved [int],
  @SpeedOverGround [float](53),
  @PositionAccuracy [int],
  @Longitude [float](53),
  @Latitude [float](53),
  @CourseOverGround [float](53),
  @TrueHeading [int],
  @Timestamp [int],
  @RegionalReserved [int],
  @IsCsUnit [bit],
  @HasDisplay [bit],
  @HasDscCapability [bit],
  @Band [bit],
  @CanAcceptMessage22 [bit],
  @Assigned [bit],
  @Raim [int],
  @RadioStatus [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 12200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisStandardClassBCsPositionReportMessage]([Id], [Reserved], [SpeedOverGround], [PositionAccuracy], [Longitude], [Latitude], [CourseOverGround], [TrueHeading], [Timestamp], [RegionalReserved], [IsCsUnit], [HasDisplay], [HasDscCapability], [Band], [CanAcceptMessage22], [Assigned], [Raim], [RadioStatus])
          VALUES(@Id, @Reserved, @SpeedOverGround, @PositionAccuracy, @Longitude, @Latitude, @CourseOverGround, @TrueHeading, @Timestamp, @RegionalReserved, @IsCsUnit, @HasDisplay, @HasDscCapability, @Band, @CanAcceptMessage22, @Assigned, @Raim, @RadioStatus);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisStandardClassBCsPositionReportMessageInsertTrigger]
ON [AisStandardClassBCsPositionReportMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [Reserved],
        [SpeedOverGround],
        [PositionAccuracy],
        [Longitude],
        [Latitude],
        [CourseOverGround],
        [TrueHeading],
        [Timestamp],
        [RegionalReserved],
        [IsCsUnit],
        [HasDisplay],
        [HasDscCapability],
        [Band],
        [CanAcceptMessage22],
        [Assigned],
        [Raim],
        [RadioStatus]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @Reserved [int]
    DECLARE @SpeedOverGround [float](53)
    DECLARE @PositionAccuracy [int]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @CourseOverGround [float](53)
    DECLARE @TrueHeading [int]
    DECLARE @Timestamp [int]
    DECLARE @RegionalReserved [int]
    DECLARE @IsCsUnit [bit]
    DECLARE @HasDisplay [bit]
    DECLARE @HasDscCapability [bit]
    DECLARE @Band [bit]
    DECLARE @CanAcceptMessage22 [bit]
    DECLARE @Assigned [bit]
    DECLARE @Raim [int]
    DECLARE @RadioStatus [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @Reserved,
        @SpeedOverGround,
        @PositionAccuracy,
        @Longitude,
        @Latitude,
        @CourseOverGround,
        @TrueHeading,
        @Timestamp,
        @RegionalReserved,
        @IsCsUnit,
        @HasDisplay,
        @HasDscCapability,
        @Band,
        @CanAcceptMessage22,
        @Assigned,
        @Raim,
        @RadioStatus
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisStandardClassBCsPositionReportMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@Reserved,@SpeedOverGround,@PositionAccuracy,@Longitude,@Latitude,@CourseOverGround,@TrueHeading,@Timestamp,@RegionalReserved,@IsCsUnit,@HasDisplay,@HasDscCapability,@Band,@CanAcceptMessage22,@Assigned,@Raim,@RadioStatus
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @Reserved,
            @SpeedOverGround,
            @PositionAccuracy,
            @Longitude,
            @Latitude,
            @CourseOverGround,
            @TrueHeading,
            @Timestamp,
            @RegionalReserved,
            @IsCsUnit,
            @HasDisplay,
            @HasDscCapability,
            @Band,
            @CanAcceptMessage22,
            @Assigned,
            @Raim,
            @RadioStatus
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisStandardSarAircraftPositionReportMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Altitude [int],
  @SpeedOverGround [int],
  @PositionAccuracy [int],
  @Longitude [float](53),
  @Latitude [float](53),
  @CourseOverGround [float](53),
  @Timestamp [int],
  @Reserved [int],
  @DataTerminalReady [bit],
  @Spare [int],
  @Assigned [bit],
  @Raim [int],
  @RadioStatus [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 12300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisStandardSarAircraftPositionReportMessage]([Id], [Altitude], [SpeedOverGround], [PositionAccuracy], [Longitude], [Latitude], [CourseOverGround], [Timestamp], [Reserved], [DataTerminalReady], [Spare], [Assigned], [Raim], [RadioStatus])
          VALUES(@Id, @Altitude, @SpeedOverGround, @PositionAccuracy, @Longitude, @Latitude, @CourseOverGround, @Timestamp, @Reserved, @DataTerminalReady, @Spare, @Assigned, @Raim, @RadioStatus);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisStandardSarAircraftPositionReportMessageInsertTrigger]
ON [AisStandardSarAircraftPositionReportMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [Altitude],
        [SpeedOverGround],
        [PositionAccuracy],
        [Longitude],
        [Latitude],
        [CourseOverGround],
        [Timestamp],
        [Reserved],
        [DataTerminalReady],
        [Spare],
        [Assigned],
        [Raim],
        [RadioStatus]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @Altitude [int]
    DECLARE @SpeedOverGround [int]
    DECLARE @PositionAccuracy [int]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @CourseOverGround [float](53)
    DECLARE @Timestamp [int]
    DECLARE @Reserved [int]
    DECLARE @DataTerminalReady [bit]
    DECLARE @Spare [int]
    DECLARE @Assigned [bit]
    DECLARE @Raim [int]
    DECLARE @RadioStatus [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @Altitude,
        @SpeedOverGround,
        @PositionAccuracy,
        @Longitude,
        @Latitude,
        @CourseOverGround,
        @Timestamp,
        @Reserved,
        @DataTerminalReady,
        @Spare,
        @Assigned,
        @Raim,
        @RadioStatus
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisStandardSarAircraftPositionReportMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@Altitude,@SpeedOverGround,@PositionAccuracy,@Longitude,@Latitude,@CourseOverGround,@Timestamp,@Reserved,@DataTerminalReady,@Spare,@Assigned,@Raim,@RadioStatus
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @Altitude,
            @SpeedOverGround,
            @PositionAccuracy,
            @Longitude,
            @Latitude,
            @CourseOverGround,
            @Timestamp,
            @Reserved,
            @DataTerminalReady,
            @Spare,
            @Assigned,
            @Raim,
            @RadioStatus
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisStaticAndVoyageRelatedDataMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @AisVersion [int],
  @ImoNumber [uniqueidentifier],
  @Callsign [uniqueidentifier],
  @ShipName [uniqueidentifier],
  @ShipType [int],
  @DimensionToBow [int],
  @DimensionToStern [int],
  @DimensionToPort [int],
  @DimensionToStarboard [int],
  @PositionFixType [int],
  @EstimatedTimeOfArrival [bigint],
  @Draught [float](53),
  @Destination [nvarchar](127),
  @DataTerminalReady [bit],
  @Spare [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 12400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisStaticAndVoyageRelatedDataMessage]([Id], [AisVersion], [ImoNumber], [Callsign], [ShipName], [ShipType], [DimensionToBow], [DimensionToStern], [DimensionToPort], [DimensionToStarboard], [PositionFixType], [EstimatedTimeOfArrival], [Draught], [Destination], [DataTerminalReady], [Spare])
          VALUES(@Id, @AisVersion, @ImoNumber, @Callsign, @ShipName, @ShipType, @DimensionToBow, @DimensionToStern, @DimensionToPort, @DimensionToStarboard, @PositionFixType, @EstimatedTimeOfArrival, @Draught, @Destination, @DataTerminalReady, @Spare);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisStaticAndVoyageRelatedDataMessageInsertTrigger]
ON [AisStaticAndVoyageRelatedDataMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [AisVersion],
        [ImoNumber],
        [Callsign],
        [ShipName],
        [ShipType],
        [DimensionToBow],
        [DimensionToStern],
        [DimensionToPort],
        [DimensionToStarboard],
        [PositionFixType],
        [EstimatedTimeOfArrival],
        [Draught],
        [Destination],
        [DataTerminalReady],
        [Spare]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @AisVersion [int]
    DECLARE @ImoNumber [uniqueidentifier]
    DECLARE @Callsign [uniqueidentifier]
    DECLARE @ShipName [uniqueidentifier]
    DECLARE @ShipType [int]
    DECLARE @DimensionToBow [int]
    DECLARE @DimensionToStern [int]
    DECLARE @DimensionToPort [int]
    DECLARE @DimensionToStarboard [int]
    DECLARE @PositionFixType [int]
    DECLARE @EstimatedTimeOfArrival [bigint]
    DECLARE @Draught [float](53)
    DECLARE @Destination [nvarchar](127)
    DECLARE @DataTerminalReady [bit]
    DECLARE @Spare [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @AisVersion,
        @ImoNumber,
        @Callsign,
        @ShipName,
        @ShipType,
        @DimensionToBow,
        @DimensionToStern,
        @DimensionToPort,
        @DimensionToStarboard,
        @PositionFixType,
        @EstimatedTimeOfArrival,
        @Draught,
        @Destination,
        @DataTerminalReady,
        @Spare
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisStaticAndVoyageRelatedDataMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@AisVersion,@ImoNumber,@Callsign,@ShipName,@ShipType,@DimensionToBow,@DimensionToStern,@DimensionToPort,@DimensionToStarboard,@PositionFixType,@EstimatedTimeOfArrival,@Draught,@Destination,@DataTerminalReady,@Spare
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @AisVersion,
            @ImoNumber,
            @Callsign,
            @ShipName,
            @ShipType,
            @DimensionToBow,
            @DimensionToStern,
            @DimensionToPort,
            @DimensionToStarboard,
            @PositionFixType,
            @EstimatedTimeOfArrival,
            @Draught,
            @Destination,
            @DataTerminalReady,
            @Spare
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisStaticDataReportMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @PartNumber [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 12500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisStaticDataReportMessage]([Id], [PartNumber])
          VALUES(@Id, @PartNumber);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisStaticDataReportMessageInsertTrigger]
ON [AisStaticDataReportMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [PartNumber]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @PartNumber [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @PartNumber
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisStaticDataReportMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@PartNumber
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @PartNumber
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisStaticDataReportPartAMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @PartNumber [int],
  @ShipName [uniqueidentifier],
  @Spare [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 12600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisStaticDataReportMessage]([Id], [PartNumber])
          VALUES(@Id, @PartNumber);
      INSERT INTO [AisStaticDataReportPartAMessage]([Id], [ShipName], [Spare])
          VALUES(@Id, @ShipName, @Spare);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisStaticDataReportPartAMessageInsertTrigger]
ON [AisStaticDataReportPartAMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [PartNumber],
        [ShipName],
        [Spare]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @PartNumber [int]
    DECLARE @ShipName [uniqueidentifier]
    DECLARE @Spare [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @PartNumber,
        @ShipName,
        @Spare
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisStaticDataReportPartAMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@PartNumber,@ShipName,@Spare
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @PartNumber,
            @ShipName,
            @Spare
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisStaticDataReportPartBMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @PartNumber [int],
  @ShipType [int],
  @VendorId [nvarchar](127),
  @UnitModelCode [int],
  @SerialNumber [int],
  @Callsign [uniqueidentifier],
  @DimensionToBow [int],
  @DimensionToStern [int],
  @DimensionToPort [int],
  @DimensionToStarboard [int],
  @MothershipMmsi [uniqueidentifier],
  @PositionFixType [int],
  @Spare [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 12700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisStaticDataReportMessage]([Id], [PartNumber])
          VALUES(@Id, @PartNumber);
      INSERT INTO [AisStaticDataReportPartBMessage]([Id], [ShipType], [VendorId], [UnitModelCode], [SerialNumber], [Callsign], [DimensionToBow], [DimensionToStern], [DimensionToPort], [DimensionToStarboard], [MothershipMmsi], [PositionFixType], [Spare])
          VALUES(@Id, @ShipType, @VendorId, @UnitModelCode, @SerialNumber, @Callsign, @DimensionToBow, @DimensionToStern, @DimensionToPort, @DimensionToStarboard, @MothershipMmsi, @PositionFixType, @Spare);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisStaticDataReportPartBMessageInsertTrigger]
ON [AisStaticDataReportPartBMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [PartNumber],
        [ShipType],
        [VendorId],
        [UnitModelCode],
        [SerialNumber],
        [Callsign],
        [DimensionToBow],
        [DimensionToStern],
        [DimensionToPort],
        [DimensionToStarboard],
        [MothershipMmsi],
        [PositionFixType],
        [Spare]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @PartNumber [int]
    DECLARE @ShipType [int]
    DECLARE @VendorId [nvarchar](127)
    DECLARE @UnitModelCode [int]
    DECLARE @SerialNumber [int]
    DECLARE @Callsign [uniqueidentifier]
    DECLARE @DimensionToBow [int]
    DECLARE @DimensionToStern [int]
    DECLARE @DimensionToPort [int]
    DECLARE @DimensionToStarboard [int]
    DECLARE @MothershipMmsi [uniqueidentifier]
    DECLARE @PositionFixType [int]
    DECLARE @Spare [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @PartNumber,
        @ShipType,
        @VendorId,
        @UnitModelCode,
        @SerialNumber,
        @Callsign,
        @DimensionToBow,
        @DimensionToStern,
        @DimensionToPort,
        @DimensionToStarboard,
        @MothershipMmsi,
        @PositionFixType,
        @Spare
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisStaticDataReportPartBMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@PartNumber,@ShipType,@VendorId,@UnitModelCode,@SerialNumber,@Callsign,@DimensionToBow,@DimensionToStern,@DimensionToPort,@DimensionToStarboard,@MothershipMmsi,@PositionFixType,@Spare
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @PartNumber,
            @ShipType,
            @VendorId,
            @UnitModelCode,
            @SerialNumber,
            @Callsign,
            @DimensionToBow,
            @DimensionToStern,
            @DimensionToPort,
            @DimensionToStarboard,
            @MothershipMmsi,
            @PositionFixType,
            @Spare
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisUtcAndDateInquiryMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Spare1 [int],
  @DestinationMmsi [uniqueidentifier],
  @Spare2 [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 12800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisUtcAndDateInquiryMessage]([Id], [Spare1], [DestinationMmsi], [Spare2])
          VALUES(@Id, @Spare1, @DestinationMmsi, @Spare2);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisUtcAndDateInquiryMessageInsertTrigger]
ON [AisUtcAndDateInquiryMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [Spare1],
        [DestinationMmsi],
        [Spare2]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @Spare1 [int]
    DECLARE @DestinationMmsi [uniqueidentifier]
    DECLARE @Spare2 [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @Spare1,
        @DestinationMmsi,
        @Spare2
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisUtcAndDateInquiryMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@Spare1,@DestinationMmsi,@Spare2
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @Spare1,
            @DestinationMmsi,
            @Spare2
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisUtcAndDateResponseMessageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Datetime [bigint],
  @PositionAccuracy [int],
  @Longitude [float](53),
  @Latitude [float](53),
  @PositionFixType [int],
  @Spare [int],
  @Raim [int],
  @RadioStatus [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 12900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AisMessage]([Id], [EntityType], [RowVersion], [AisDevice], [ReceivedTimestamp], [MessageSequenceNumber], [Repeat], [Mmsi])
          VALUES(@Id, @EntityType, 0, @AisDevice, @ReceivedTimestamp, @MessageSequenceNumber, @Repeat, @Mmsi);
      INSERT INTO [AisUtcAndDateResponseMessage]([Id], [Datetime], [PositionAccuracy], [Longitude], [Latitude], [PositionFixType], [Spare], [Raim], [RadioStatus])
          VALUES(@Id, @Datetime, @PositionAccuracy, @Longitude, @Latitude, @PositionFixType, @Spare, @Raim, @RadioStatus);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisUtcAndDateResponseMessageInsertTrigger]
ON [AisUtcAndDateResponseMessageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [AisDevice],
        [ReceivedTimestamp],
        [MessageSequenceNumber],
        [Repeat],
        [Mmsi],
        [Datetime],
        [PositionAccuracy],
        [Longitude],
        [Latitude],
        [PositionFixType],
        [Spare],
        [Raim],
        [RadioStatus]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @AisDevice [uniqueidentifier]
    DECLARE @ReceivedTimestamp [bigint]
    DECLARE @MessageSequenceNumber [bigint]
    DECLARE @Repeat [int]
    DECLARE @Mmsi [uniqueidentifier]
    DECLARE @Datetime [bigint]
    DECLARE @PositionAccuracy [int]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @PositionFixType [int]
    DECLARE @Spare [int]
    DECLARE @Raim [int]
    DECLARE @RadioStatus [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @AisDevice,
        @ReceivedTimestamp,
        @MessageSequenceNumber,
        @Repeat,
        @Mmsi,
        @Datetime,
        @PositionAccuracy,
        @Longitude,
        @Latitude,
        @PositionFixType,
        @Spare,
        @Raim,
        @RadioStatus
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisUtcAndDateResponseMessageInsert] @Id,@RowVersion,@AisDevice,@ReceivedTimestamp,@MessageSequenceNumber,@Repeat,@Mmsi,@Datetime,@PositionAccuracy,@Longitude,@Latitude,@PositionFixType,@Spare,@Raim,@RadioStatus
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @AisDevice,
            @ReceivedTimestamp,
            @MessageSequenceNumber,
            @Repeat,
            @Mmsi,
            @Datetime,
            @PositionAccuracy,
            @Longitude,
            @Latitude,
            @PositionFixType,
            @Spare,
            @Raim,
            @RadioStatus
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AlarmStateChangeInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Alarm [uniqueidentifier],
  @Timestamp [bigint],
  @State [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [AlarmStateChange]([Id], [RowVersion], [Alarm], [Timestamp], [State])
          VALUES(@Id, 0, @Alarm, @Timestamp, @State);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AlarmStateChangeInsertTrigger]
ON [AlarmStateChangeView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Alarm],
        [Timestamp],
        [State]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Alarm [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @State [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Alarm,
        @Timestamp,
        @State
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AlarmStateChangeInsert] @Id,@RowVersion,@Alarm,@Timestamp,@State
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Alarm,
            @Timestamp,
            @State
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BaseStationTypeInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [BaseStationType]([Id], [RowVersion], [Name])
          VALUES(@Id, 0, @Name);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BaseStationTypeInsertTrigger]
ON [BaseStationTypeView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BaseStationTypeInsert] @Id,@RowVersion,@Name
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BinaryTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [varbinary](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [BinaryTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BinaryTimeseriesValueInsertTrigger]
ON [BinaryTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [varbinary](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BinaryTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BookmarkInsert]
  @Id [uniqueidentifier] OUTPUT,
  @View [uniqueidentifier],
  @Name [nvarchar](127),
  @Timestamp [bigint],
  @Latitude [float](53),
  @Longitude [float](53),
  @ZoomLevel [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Bookmark]([Id], [RowVersion], [View], [Name], [Timestamp], [Latitude], [Longitude], [ZoomLevel])
          VALUES(@Id, 0, @View, @Name, @Timestamp, @Latitude, @Longitude, @ZoomLevel);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BookmarkInsertTrigger]
ON [BookmarkView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [View],
        [Name],
        [Timestamp],
        [Latitude],
        [Longitude],
        [ZoomLevel]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @View [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Timestamp [bigint]
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @ZoomLevel [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @View,
        @Name,
        @Timestamp,
        @Latitude,
        @Longitude,
        @ZoomLevel
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BookmarkInsert] @Id,@RowVersion,@View,@Name,@Timestamp,@Latitude,@Longitude,@ZoomLevel
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @View,
            @Name,
            @Timestamp,
            @Latitude,
            @Longitude,
            @ZoomLevel
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BooleanTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [BooleanTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BooleanTimeseriesValueInsertTrigger]
ON [BooleanTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BooleanTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ByteTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [tinyint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [ByteTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ByteTimeseriesValueInsertTrigger]
ON [ByteTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [tinyint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ByteTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 13600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandInsertTrigger]
ON [CameraCommandView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandAbsoluteMoveInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @PositionPanTiltMode [int],
  @PanAngle [float](53),
  @TiltAngle [float](53),
  @PositionFocalLengthMode [int],
  @FocalLength [float](53),
  @SpeedPanTiltMode [int],
  @PanSpeed [float](53),
  @TiltSpeed [float](53),
  @SpeedFocalLengthMode [int],
  @ZoomSpeed [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 13700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandAbsoluteMove]([Id], [PositionPanTiltMode], [PanAngle], [TiltAngle], [PositionFocalLengthMode], [FocalLength], [SpeedPanTiltMode], [PanSpeed], [TiltSpeed], [SpeedFocalLengthMode], [ZoomSpeed])
          VALUES(@Id, @PositionPanTiltMode, @PanAngle, @TiltAngle, @PositionFocalLengthMode, @FocalLength, @SpeedPanTiltMode, @PanSpeed, @TiltSpeed, @SpeedFocalLengthMode, @ZoomSpeed);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandAbsoluteMoveInsertTrigger]
ON [CameraCommandAbsoluteMoveView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [PositionPanTiltMode],
        [PanAngle],
        [TiltAngle],
        [PositionFocalLengthMode],
        [FocalLength],
        [SpeedPanTiltMode],
        [PanSpeed],
        [TiltSpeed],
        [SpeedFocalLengthMode],
        [ZoomSpeed]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @PositionPanTiltMode [int]
    DECLARE @PanAngle [float](53)
    DECLARE @TiltAngle [float](53)
    DECLARE @PositionFocalLengthMode [int]
    DECLARE @FocalLength [float](53)
    DECLARE @SpeedPanTiltMode [int]
    DECLARE @PanSpeed [float](53)
    DECLARE @TiltSpeed [float](53)
    DECLARE @SpeedFocalLengthMode [int]
    DECLARE @ZoomSpeed [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @PositionPanTiltMode,
        @PanAngle,
        @TiltAngle,
        @PositionFocalLengthMode,
        @FocalLength,
        @SpeedPanTiltMode,
        @PanSpeed,
        @TiltSpeed,
        @SpeedFocalLengthMode,
        @ZoomSpeed
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandAbsoluteMoveInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@PositionPanTiltMode,@PanAngle,@TiltAngle,@PositionFocalLengthMode,@FocalLength,@SpeedPanTiltMode,@PanSpeed,@TiltSpeed,@SpeedFocalLengthMode,@ZoomSpeed
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @PositionPanTiltMode,
            @PanAngle,
            @TiltAngle,
            @PositionFocalLengthMode,
            @FocalLength,
            @SpeedPanTiltMode,
            @PanSpeed,
            @TiltSpeed,
            @SpeedFocalLengthMode,
            @ZoomSpeed
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandAdjustPanTiltZoomInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @X [float](53),
  @Y [float](53),
  @Z [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 13800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandAdjustPanTiltZoom]([Id], [X], [Y], [Z])
          VALUES(@Id, @X, @Y, @Z);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandAdjustPanTiltZoomInsertTrigger]
ON [CameraCommandAdjustPanTiltZoomView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [X],
        [Y],
        [Z]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @X [float](53)
    DECLARE @Y [float](53)
    DECLARE @Z [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @X,
        @Y,
        @Z
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandAdjustPanTiltZoomInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@X,@Y,@Z
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @X,
            @Y,
            @Z
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandContinuousMoveInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Normalized [bit],
  @PanVelocity [float](53),
  @TiltVelocity [float](53),
  @ZoomVelocity [float](53),
  @Duration [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 13900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandContinuousMove]([Id], [Normalized], [PanVelocity], [TiltVelocity], [ZoomVelocity], [Duration])
          VALUES(@Id, @Normalized, @PanVelocity, @TiltVelocity, @ZoomVelocity, @Duration);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandContinuousMoveInsertTrigger]
ON [CameraCommandContinuousMoveView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [Normalized],
        [PanVelocity],
        [TiltVelocity],
        [ZoomVelocity],
        [Duration]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @Normalized [bit]
    DECLARE @PanVelocity [float](53)
    DECLARE @TiltVelocity [float](53)
    DECLARE @ZoomVelocity [float](53)
    DECLARE @Duration [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @Normalized,
        @PanVelocity,
        @TiltVelocity,
        @ZoomVelocity,
        @Duration
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandContinuousMoveInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@Normalized,@PanVelocity,@TiltVelocity,@ZoomVelocity,@Duration
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @Normalized,
            @PanVelocity,
            @TiltVelocity,
            @ZoomVelocity,
            @Duration
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandGeoMoveInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Latitude [float](53),
  @Longitude [float](53),
  @Altitude [float](53),
  @ViewportWidth [float](53),
  @ViewportHeight [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 14000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandGeoMove]([Id], [Latitude], [Longitude], [Altitude], [ViewportWidth], [ViewportHeight])
          VALUES(@Id, @Latitude, @Longitude, @Altitude, @ViewportWidth, @ViewportHeight);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandGeoMoveInsertTrigger]
ON [CameraCommandGeoMoveView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [Latitude],
        [Longitude],
        [Altitude],
        [ViewportWidth],
        [ViewportHeight]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @Altitude [float](53)
    DECLARE @ViewportWidth [float](53)
    DECLARE @ViewportHeight [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @Latitude,
        @Longitude,
        @Altitude,
        @ViewportWidth,
        @ViewportHeight
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandGeoMoveInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@Latitude,@Longitude,@Altitude,@ViewportWidth,@ViewportHeight
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @Latitude,
            @Longitude,
            @Altitude,
            @ViewportWidth,
            @ViewportHeight
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandRelativeMoveInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Normalized [bit],
  @PanAngle [float](53),
  @TiltAngle [float](53),
  @FocalLength [float](53),
  @PanSpeed [float](53),
  @TiltSpeed [float](53),
  @ZoomSpeed [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 14100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandRelativeMove]([Id], [Normalized], [PanAngle], [TiltAngle], [FocalLength], [PanSpeed], [TiltSpeed], [ZoomSpeed])
          VALUES(@Id, @Normalized, @PanAngle, @TiltAngle, @FocalLength, @PanSpeed, @TiltSpeed, @ZoomSpeed);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandRelativeMoveInsertTrigger]
ON [CameraCommandRelativeMoveView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [Normalized],
        [PanAngle],
        [TiltAngle],
        [FocalLength],
        [PanSpeed],
        [TiltSpeed],
        [ZoomSpeed]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @Normalized [bit]
    DECLARE @PanAngle [float](53)
    DECLARE @TiltAngle [float](53)
    DECLARE @FocalLength [float](53)
    DECLARE @PanSpeed [float](53)
    DECLARE @TiltSpeed [float](53)
    DECLARE @ZoomSpeed [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @Normalized,
        @PanAngle,
        @TiltAngle,
        @FocalLength,
        @PanSpeed,
        @TiltSpeed,
        @ZoomSpeed
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandRelativeMoveInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@Normalized,@PanAngle,@TiltAngle,@FocalLength,@PanSpeed,@TiltSpeed,@ZoomSpeed
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @Normalized,
            @PanAngle,
            @TiltAngle,
            @FocalLength,
            @PanSpeed,
            @TiltSpeed,
            @ZoomSpeed
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandReleasePTZOwnershipInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 14200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandReleasePTZOwnership]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandReleasePTZOwnershipInsertTrigger]
ON [CameraCommandReleasePTZOwnershipView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandReleasePTZOwnershipInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandRequestPTZOwnershipInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 14300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandRequestPTZOwnership]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandRequestPTZOwnershipInsertTrigger]
ON [CameraCommandRequestPTZOwnershipView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandRequestPTZOwnershipInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandSetAutoFocusInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Enabled [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 14400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandSetAutoFocus]([Id], [Enabled])
          VALUES(@Id, @Enabled);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandSetAutoFocusInsertTrigger]
ON [CameraCommandSetAutoFocusView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [Enabled]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @Enabled [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @Enabled
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandSetAutoFocusInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@Enabled
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @Enabled
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandSetBlackAndWhiteInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Enabled [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 14500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandSetBlackAndWhite]([Id], [Enabled])
          VALUES(@Id, @Enabled);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandSetBlackAndWhiteInsertTrigger]
ON [CameraCommandSetBlackAndWhiteView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [Enabled]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @Enabled [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @Enabled
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandSetBlackAndWhiteInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@Enabled
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @Enabled
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandSetFollowedInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @TrackId [uniqueidentifier],
  @Reason [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 14600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandSetFollowed]([Id], [TrackId], [Reason])
          VALUES(@Id, @TrackId, @Reason);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandSetFollowedInsertTrigger]
ON [CameraCommandSetFollowedView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [TrackId],
        [Reason]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @TrackId [uniqueidentifier]
    DECLARE @Reason [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @TrackId,
        @Reason
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandSetFollowedInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@TrackId,@Reason
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @TrackId,
            @Reason
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandSetInfraRedLampInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Enabled [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 14700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandSetInfraRedLamp]([Id], [Enabled])
          VALUES(@Id, @Enabled);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandSetInfraRedLampInsertTrigger]
ON [CameraCommandSetInfraRedLampView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [Enabled]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @Enabled [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @Enabled
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandSetInfraRedLampInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@Enabled
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @Enabled
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandSetWasherInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Enabled [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 14800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandSetWasher]([Id], [Enabled])
          VALUES(@Id, @Enabled);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandSetWasherInsertTrigger]
ON [CameraCommandSetWasherView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [Enabled]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @Enabled [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @Enabled
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandSetWasherInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@Enabled
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @Enabled
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandSetWiperInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Enabled [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 14900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandSetWiper]([Id], [Enabled])
          VALUES(@Id, @Enabled);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandSetWiperInsertTrigger]
ON [CameraCommandSetWiperView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [Enabled]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @Enabled [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @Enabled
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandSetWiperInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@Enabled
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @Enabled
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandStopInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @PanTilt [bit],
  @Zoom [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 15000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommand]([Id], [EntityType], [RowVersion], [Camera], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Camera, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [CameraCommandStop]([Id], [PanTilt], [Zoom])
          VALUES(@Id, @PanTilt, @Zoom);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandStopInsertTrigger]
ON [CameraCommandStopView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply],
        [PanTilt],
        [Zoom]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    DECLARE @PanTilt [bit]
    DECLARE @Zoom [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply,
        @PanTilt,
        @Zoom
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandStopInsert] @Id,@RowVersion,@Camera,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply,@PanTilt,@Zoom
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply,
            @PanTilt,
            @Zoom
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraCommandReplyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max),
  @PanAngle [float](53),
  @TiltAngle [float](53),
  @FocalLength [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraCommandReply]([Id], [RowVersion], [Camera], [Timestamp], [Command], [Status], [Message], [PanAngle], [TiltAngle], [FocalLength])
          VALUES(@Id, 0, @Camera, @Timestamp, @Command, @Status, @Message, @PanAngle, @TiltAngle, @FocalLength);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraCommandReplyInsertTrigger]
ON [CameraCommandReplyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [Command],
        [Status],
        [Message],
        [PanAngle],
        [TiltAngle],
        [FocalLength]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    DECLARE @PanAngle [float](53)
    DECLARE @TiltAngle [float](53)
    DECLARE @FocalLength [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @Command,
        @Status,
        @Message,
        @PanAngle,
        @TiltAngle,
        @FocalLength
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraCommandReplyInsert] @Id,@RowVersion,@Camera,@Timestamp,@Command,@Status,@Message,@PanAngle,@TiltAngle,@FocalLength
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @Command,
            @Status,
            @Message,
            @PanAngle,
            @TiltAngle,
            @FocalLength
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @CameraControlProtocol [int],
  @CameraURL [nvarchar](127),
  @ConfigurationURL [nvarchar](127),
  @UserName [nvarchar](127),
  @Password [nvarchar](127),
  @UseRtspUriOverride [bit],
  @RtspUriOverride [nvarchar](127),
  @Latitude [float](53),
  @Longitude [float](53),
  @Altitude [float](53),
  @UseRelativePosition [bit],
  @PanTiltMode [int],
  @MinTiltAngle [float](53),
  @MaxTiltAngle [float](53),
  @MinTiltScaleAngle [float](53),
  @MaxTiltScaleAngle [float](53),
  @UseReverseTiltAngle [bit],
  @UseReverseNormalizedTiltAngle [bit],
  @MinTiltVelocity [float](53),
  @MaxTiltVelocity [float](53),
  @MinTiltSpeed [float](53),
  @MaxTiltSpeed [float](53),
  @MinPanAngle [float](53),
  @MaxPanAngle [float](53),
  @MinPanScaleAngle [float](53),
  @MaxPanScaleAngle [float](53),
  @UseReversePanAngle [bit],
  @UseReverseNormalizedPanAngle [bit],
  @MinPanVelocity [float](53),
  @MaxPanVelocity [float](53),
  @MinPanSpeed [float](53),
  @MaxPanSpeed [float](53),
  @FocalLengthMode [int],
  @MinFocalLength [float](53),
  @MaxFocalLength [float](53),
  @MinFocalLengthScale [float](53),
  @MaxFocalLengthScale [float](53),
  @MinZoomVelocity [float](53),
  @MaxZoomVelocity [float](53),
  @MinZoomSpeed [float](53),
  @MaxZoomSpeed [float](53),
  @ImageSensorWidth [float](53),
  @ImageSensorHeight [float](53),
  @HomePanAngle [float](53),
  @HomeTiltAngle [float](53),
  @HomeFocalLength [float](53),
  @PanOffset [float](53),
  @TiltOffset [float](53),
  @AimAltitude [float](53),
  @MinimumTargetWidth [float](53),
  @TargetLockTimeout [bigint],
  @UpdateStatusInterval [bigint],
  @ReadTimeout [bigint],
  @MoveCommandStatusDelay [bigint],
  @PtzProfileName [nvarchar](127),
  @PtzConfigurationToken [nvarchar](127),
  @VideoSourceToken [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraConfiguration]([Id], [RowVersion], [Camera], [Timestamp], [CameraControlProtocol], [CameraURL], [ConfigurationURL], [UserName], [Password], [UseRtspUriOverride], [RtspUriOverride], [Latitude], [Longitude], [Altitude], [UseRelativePosition], [PanTiltMode], [MinTiltAngle], [MaxTiltAngle], [MinTiltScaleAngle], [MaxTiltScaleAngle], [UseReverseTiltAngle], [UseReverseNormalizedTiltAngle], [MinTiltVelocity], [MaxTiltVelocity], [MinTiltSpeed], [MaxTiltSpeed], [MinPanAngle], [MaxPanAngle], [MinPanScaleAngle], [MaxPanScaleAngle], [UseReversePanAngle], [UseReverseNormalizedPanAngle], [MinPanVelocity], [MaxPanVelocity], [MinPanSpeed], [MaxPanSpeed], [FocalLengthMode], [MinFocalLength], [MaxFocalLength], [MinFocalLengthScale], [MaxFocalLengthScale], [MinZoomVelocity], [MaxZoomVelocity], [MinZoomSpeed], [MaxZoomSpeed], [ImageSensorWidth], [ImageSensorHeight], [HomePanAngle], [HomeTiltAngle], [HomeFocalLength], [PanOffset], [TiltOffset], [AimAltitude], [MinimumTargetWidth], [TargetLockTimeout], [UpdateStatusInterval], [ReadTimeout], [MoveCommandStatusDelay], [PtzProfileName], [PtzConfigurationToken], [VideoSourceToken])
          VALUES(@Id, 0, @Camera, @Timestamp, @CameraControlProtocol, @CameraURL, @ConfigurationURL, @UserName, @Password, @UseRtspUriOverride, @RtspUriOverride, @Latitude, @Longitude, @Altitude, @UseRelativePosition, @PanTiltMode, @MinTiltAngle, @MaxTiltAngle, @MinTiltScaleAngle, @MaxTiltScaleAngle, @UseReverseTiltAngle, @UseReverseNormalizedTiltAngle, @MinTiltVelocity, @MaxTiltVelocity, @MinTiltSpeed, @MaxTiltSpeed, @MinPanAngle, @MaxPanAngle, @MinPanScaleAngle, @MaxPanScaleAngle, @UseReversePanAngle, @UseReverseNormalizedPanAngle, @MinPanVelocity, @MaxPanVelocity, @MinPanSpeed, @MaxPanSpeed, @FocalLengthMode, @MinFocalLength, @MaxFocalLength, @MinFocalLengthScale, @MaxFocalLengthScale, @MinZoomVelocity, @MaxZoomVelocity, @MinZoomSpeed, @MaxZoomSpeed, @ImageSensorWidth, @ImageSensorHeight, @HomePanAngle, @HomeTiltAngle, @HomeFocalLength, @PanOffset, @TiltOffset, @AimAltitude, @MinimumTargetWidth, @TargetLockTimeout, @UpdateStatusInterval, @ReadTimeout, @MoveCommandStatusDelay, @PtzProfileName, @PtzConfigurationToken, @VideoSourceToken);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraConfigurationInsertTrigger]
ON [CameraConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp],
        [CameraControlProtocol],
        [CameraURL],
        [ConfigurationURL],
        [UserName],
        [Password],
        [UseRtspUriOverride],
        [RtspUriOverride],
        [Latitude],
        [Longitude],
        [Altitude],
        [UseRelativePosition],
        [PanTiltMode],
        [MinTiltAngle],
        [MaxTiltAngle],
        [MinTiltScaleAngle],
        [MaxTiltScaleAngle],
        [UseReverseTiltAngle],
        [UseReverseNormalizedTiltAngle],
        [MinTiltVelocity],
        [MaxTiltVelocity],
        [MinTiltSpeed],
        [MaxTiltSpeed],
        [MinPanAngle],
        [MaxPanAngle],
        [MinPanScaleAngle],
        [MaxPanScaleAngle],
        [UseReversePanAngle],
        [UseReverseNormalizedPanAngle],
        [MinPanVelocity],
        [MaxPanVelocity],
        [MinPanSpeed],
        [MaxPanSpeed],
        [FocalLengthMode],
        [MinFocalLength],
        [MaxFocalLength],
        [MinFocalLengthScale],
        [MaxFocalLengthScale],
        [MinZoomVelocity],
        [MaxZoomVelocity],
        [MinZoomSpeed],
        [MaxZoomSpeed],
        [ImageSensorWidth],
        [ImageSensorHeight],
        [HomePanAngle],
        [HomeTiltAngle],
        [HomeFocalLength],
        [PanOffset],
        [TiltOffset],
        [AimAltitude],
        [MinimumTargetWidth],
        [TargetLockTimeout],
        [UpdateStatusInterval],
        [ReadTimeout],
        [MoveCommandStatusDelay],
        [PtzProfileName],
        [PtzConfigurationToken],
        [VideoSourceToken]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @CameraControlProtocol [int]
    DECLARE @CameraURL [nvarchar](127)
    DECLARE @ConfigurationURL [nvarchar](127)
    DECLARE @UserName [nvarchar](127)
    DECLARE @Password [nvarchar](127)
    DECLARE @UseRtspUriOverride [bit]
    DECLARE @RtspUriOverride [nvarchar](127)
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @Altitude [float](53)
    DECLARE @UseRelativePosition [bit]
    DECLARE @PanTiltMode [int]
    DECLARE @MinTiltAngle [float](53)
    DECLARE @MaxTiltAngle [float](53)
    DECLARE @MinTiltScaleAngle [float](53)
    DECLARE @MaxTiltScaleAngle [float](53)
    DECLARE @UseReverseTiltAngle [bit]
    DECLARE @UseReverseNormalizedTiltAngle [bit]
    DECLARE @MinTiltVelocity [float](53)
    DECLARE @MaxTiltVelocity [float](53)
    DECLARE @MinTiltSpeed [float](53)
    DECLARE @MaxTiltSpeed [float](53)
    DECLARE @MinPanAngle [float](53)
    DECLARE @MaxPanAngle [float](53)
    DECLARE @MinPanScaleAngle [float](53)
    DECLARE @MaxPanScaleAngle [float](53)
    DECLARE @UseReversePanAngle [bit]
    DECLARE @UseReverseNormalizedPanAngle [bit]
    DECLARE @MinPanVelocity [float](53)
    DECLARE @MaxPanVelocity [float](53)
    DECLARE @MinPanSpeed [float](53)
    DECLARE @MaxPanSpeed [float](53)
    DECLARE @FocalLengthMode [int]
    DECLARE @MinFocalLength [float](53)
    DECLARE @MaxFocalLength [float](53)
    DECLARE @MinFocalLengthScale [float](53)
    DECLARE @MaxFocalLengthScale [float](53)
    DECLARE @MinZoomVelocity [float](53)
    DECLARE @MaxZoomVelocity [float](53)
    DECLARE @MinZoomSpeed [float](53)
    DECLARE @MaxZoomSpeed [float](53)
    DECLARE @ImageSensorWidth [float](53)
    DECLARE @ImageSensorHeight [float](53)
    DECLARE @HomePanAngle [float](53)
    DECLARE @HomeTiltAngle [float](53)
    DECLARE @HomeFocalLength [float](53)
    DECLARE @PanOffset [float](53)
    DECLARE @TiltOffset [float](53)
    DECLARE @AimAltitude [float](53)
    DECLARE @MinimumTargetWidth [float](53)
    DECLARE @TargetLockTimeout [bigint]
    DECLARE @UpdateStatusInterval [bigint]
    DECLARE @ReadTimeout [bigint]
    DECLARE @MoveCommandStatusDelay [bigint]
    DECLARE @PtzProfileName [nvarchar](127)
    DECLARE @PtzConfigurationToken [nvarchar](127)
    DECLARE @VideoSourceToken [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp,
        @CameraControlProtocol,
        @CameraURL,
        @ConfigurationURL,
        @UserName,
        @Password,
        @UseRtspUriOverride,
        @RtspUriOverride,
        @Latitude,
        @Longitude,
        @Altitude,
        @UseRelativePosition,
        @PanTiltMode,
        @MinTiltAngle,
        @MaxTiltAngle,
        @MinTiltScaleAngle,
        @MaxTiltScaleAngle,
        @UseReverseTiltAngle,
        @UseReverseNormalizedTiltAngle,
        @MinTiltVelocity,
        @MaxTiltVelocity,
        @MinTiltSpeed,
        @MaxTiltSpeed,
        @MinPanAngle,
        @MaxPanAngle,
        @MinPanScaleAngle,
        @MaxPanScaleAngle,
        @UseReversePanAngle,
        @UseReverseNormalizedPanAngle,
        @MinPanVelocity,
        @MaxPanVelocity,
        @MinPanSpeed,
        @MaxPanSpeed,
        @FocalLengthMode,
        @MinFocalLength,
        @MaxFocalLength,
        @MinFocalLengthScale,
        @MaxFocalLengthScale,
        @MinZoomVelocity,
        @MaxZoomVelocity,
        @MinZoomSpeed,
        @MaxZoomSpeed,
        @ImageSensorWidth,
        @ImageSensorHeight,
        @HomePanAngle,
        @HomeTiltAngle,
        @HomeFocalLength,
        @PanOffset,
        @TiltOffset,
        @AimAltitude,
        @MinimumTargetWidth,
        @TargetLockTimeout,
        @UpdateStatusInterval,
        @ReadTimeout,
        @MoveCommandStatusDelay,
        @PtzProfileName,
        @PtzConfigurationToken,
        @VideoSourceToken
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraConfigurationInsert] @Id,@RowVersion,@Camera,@Timestamp,@CameraControlProtocol,@CameraURL,@ConfigurationURL,@UserName,@Password,@UseRtspUriOverride,@RtspUriOverride,@Latitude,@Longitude,@Altitude,@UseRelativePosition,@PanTiltMode,@MinTiltAngle,@MaxTiltAngle,@MinTiltScaleAngle,@MaxTiltScaleAngle,@UseReverseTiltAngle,@UseReverseNormalizedTiltAngle,@MinTiltVelocity,@MaxTiltVelocity,@MinTiltSpeed,@MaxTiltSpeed,@MinPanAngle,@MaxPanAngle,@MinPanScaleAngle,@MaxPanScaleAngle,@UseReversePanAngle,@UseReverseNormalizedPanAngle,@MinPanVelocity,@MaxPanVelocity,@MinPanSpeed,@MaxPanSpeed,@FocalLengthMode,@MinFocalLength,@MaxFocalLength,@MinFocalLengthScale,@MaxFocalLengthScale,@MinZoomVelocity,@MaxZoomVelocity,@MinZoomSpeed,@MaxZoomSpeed,@ImageSensorWidth,@ImageSensorHeight,@HomePanAngle,@HomeTiltAngle,@HomeFocalLength,@PanOffset,@TiltOffset,@AimAltitude,@MinimumTargetWidth,@TargetLockTimeout,@UpdateStatusInterval,@ReadTimeout,@MoveCommandStatusDelay,@PtzProfileName,@PtzConfigurationToken,@VideoSourceToken
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp,
            @CameraControlProtocol,
            @CameraURL,
            @ConfigurationURL,
            @UserName,
            @Password,
            @UseRtspUriOverride,
            @RtspUriOverride,
            @Latitude,
            @Longitude,
            @Altitude,
            @UseRelativePosition,
            @PanTiltMode,
            @MinTiltAngle,
            @MaxTiltAngle,
            @MinTiltScaleAngle,
            @MaxTiltScaleAngle,
            @UseReverseTiltAngle,
            @UseReverseNormalizedTiltAngle,
            @MinTiltVelocity,
            @MaxTiltVelocity,
            @MinTiltSpeed,
            @MaxTiltSpeed,
            @MinPanAngle,
            @MaxPanAngle,
            @MinPanScaleAngle,
            @MaxPanScaleAngle,
            @UseReversePanAngle,
            @UseReverseNormalizedPanAngle,
            @MinPanVelocity,
            @MaxPanVelocity,
            @MinPanSpeed,
            @MaxPanSpeed,
            @FocalLengthMode,
            @MinFocalLength,
            @MaxFocalLength,
            @MinFocalLengthScale,
            @MaxFocalLengthScale,
            @MinZoomVelocity,
            @MaxZoomVelocity,
            @MinZoomSpeed,
            @MaxZoomSpeed,
            @ImageSensorWidth,
            @ImageSensorHeight,
            @HomePanAngle,
            @HomeTiltAngle,
            @HomeFocalLength,
            @PanOffset,
            @TiltOffset,
            @AimAltitude,
            @MinimumTargetWidth,
            @TargetLockTimeout,
            @UpdateStatusInterval,
            @ReadTimeout,
            @MoveCommandStatusDelay,
            @PtzProfileName,
            @PtzConfigurationToken,
            @VideoSourceToken
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraPanCalibrationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraPanCalibration]([Id], [RowVersion], [Camera], [Timestamp])
          VALUES(@Id, 0, @Camera, @Timestamp);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraPanCalibrationInsertTrigger]
ON [CameraPanCalibrationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraPanCalibrationInsert] @Id,@RowVersion,@Camera,@Timestamp
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraPanCalibrationValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @PanCalibration [uniqueidentifier],
  @PanAngle [float](53),
  @PanOffset [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraPanCalibrationValue]([Id], [RowVersion], [PanCalibration], [PanAngle], [PanOffset])
          VALUES(@Id, 0, @PanCalibration, @PanAngle, @PanOffset);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraPanCalibrationValueInsertTrigger]
ON [CameraPanCalibrationValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [PanCalibration],
        [PanAngle],
        [PanOffset]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @PanCalibration [uniqueidentifier]
    DECLARE @PanAngle [float](53)
    DECLARE @PanOffset [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @PanCalibration,
        @PanAngle,
        @PanOffset
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraPanCalibrationValueInsert] @Id,@RowVersion,@PanCalibration,@PanAngle,@PanOffset
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @PanCalibration,
            @PanAngle,
            @PanOffset
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraStatusInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Track [uniqueidentifier],
  @Timestamp [bigint],
  @PositionPanTiltMode [int],
  @PanAngle [float](53),
  @TiltAngle [float](53),
  @PositionFocalLengthMode [int],
  @FocalLength [float](53),
  @PanTiltMoveStatus [int],
  @ZoomMoveStatus [int],
  @VelocityPanTiltMode [int],
  @PanVelocity [float](53),
  @TiltVelocity [float](53),
  @VelocityFocalLengthMode [int],
  @ZoomVelocity [float](53),
  @ActiveFeatures [int],
  @Error [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraStatus]([Id], [RowVersion], [Camera], [Track], [Timestamp], [PositionPanTiltMode], [PanAngle], [TiltAngle], [PositionFocalLengthMode], [FocalLength], [PanTiltMoveStatus], [ZoomMoveStatus], [VelocityPanTiltMode], [PanVelocity], [TiltVelocity], [VelocityFocalLengthMode], [ZoomVelocity], [ActiveFeatures], [Error])
          VALUES(@Id, 0, @Camera, @Track, @Timestamp, @PositionPanTiltMode, @PanAngle, @TiltAngle, @PositionFocalLengthMode, @FocalLength, @PanTiltMoveStatus, @ZoomMoveStatus, @VelocityPanTiltMode, @PanVelocity, @TiltVelocity, @VelocityFocalLengthMode, @ZoomVelocity, @ActiveFeatures, @Error);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraStatusInsertTrigger]
ON [CameraStatusView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Track],
        [Timestamp],
        [PositionPanTiltMode],
        [PanAngle],
        [TiltAngle],
        [PositionFocalLengthMode],
        [FocalLength],
        [PanTiltMoveStatus],
        [ZoomMoveStatus],
        [VelocityPanTiltMode],
        [PanVelocity],
        [TiltVelocity],
        [VelocityFocalLengthMode],
        [ZoomVelocity],
        [ActiveFeatures],
        [Error]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Track [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @PositionPanTiltMode [int]
    DECLARE @PanAngle [float](53)
    DECLARE @TiltAngle [float](53)
    DECLARE @PositionFocalLengthMode [int]
    DECLARE @FocalLength [float](53)
    DECLARE @PanTiltMoveStatus [int]
    DECLARE @ZoomMoveStatus [int]
    DECLARE @VelocityPanTiltMode [int]
    DECLARE @PanVelocity [float](53)
    DECLARE @TiltVelocity [float](53)
    DECLARE @VelocityFocalLengthMode [int]
    DECLARE @ZoomVelocity [float](53)
    DECLARE @ActiveFeatures [int]
    DECLARE @Error [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Track,
        @Timestamp,
        @PositionPanTiltMode,
        @PanAngle,
        @TiltAngle,
        @PositionFocalLengthMode,
        @FocalLength,
        @PanTiltMoveStatus,
        @ZoomMoveStatus,
        @VelocityPanTiltMode,
        @PanVelocity,
        @TiltVelocity,
        @VelocityFocalLengthMode,
        @ZoomVelocity,
        @ActiveFeatures,
        @Error
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraStatusInsert] @Id,@RowVersion,@Camera,@Track,@Timestamp,@PositionPanTiltMode,@PanAngle,@TiltAngle,@PositionFocalLengthMode,@FocalLength,@PanTiltMoveStatus,@ZoomMoveStatus,@VelocityPanTiltMode,@PanVelocity,@TiltVelocity,@VelocityFocalLengthMode,@ZoomVelocity,@ActiveFeatures,@Error
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Track,
            @Timestamp,
            @PositionPanTiltMode,
            @PanAngle,
            @TiltAngle,
            @PositionFocalLengthMode,
            @FocalLength,
            @PanTiltMoveStatus,
            @ZoomMoveStatus,
            @VelocityPanTiltMode,
            @PanVelocity,
            @TiltVelocity,
            @VelocityFocalLengthMode,
            @ZoomVelocity,
            @ActiveFeatures,
            @Error
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraTiltCalibrationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraTiltCalibration]([Id], [RowVersion], [Camera], [Timestamp])
          VALUES(@Id, 0, @Camera, @Timestamp);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraTiltCalibrationInsertTrigger]
ON [CameraTiltCalibrationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraTiltCalibrationInsert] @Id,@RowVersion,@Camera,@Timestamp
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraTiltCalibrationValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @TiltCalibration [uniqueidentifier],
  @PanAngle [float](53),
  @TiltOffset [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraTiltCalibrationValue]([Id], [RowVersion], [TiltCalibration], [PanAngle], [TiltOffset])
          VALUES(@Id, 0, @TiltCalibration, @PanAngle, @TiltOffset);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraTiltCalibrationValueInsertTrigger]
ON [CameraTiltCalibrationValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [TiltCalibration],
        [PanAngle],
        [TiltOffset]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @TiltCalibration [uniqueidentifier]
    DECLARE @PanAngle [float](53)
    DECLARE @TiltOffset [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @TiltCalibration,
        @PanAngle,
        @TiltOffset
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraTiltCalibrationValueInsert] @Id,@RowVersion,@TiltCalibration,@PanAngle,@TiltOffset
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @TiltCalibration,
            @PanAngle,
            @TiltOffset
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraZoomCalibrationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraZoomCalibration]([Id], [RowVersion], [Camera], [Timestamp])
          VALUES(@Id, 0, @Camera, @Timestamp);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraZoomCalibrationInsertTrigger]
ON [CameraZoomCalibrationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Camera],
        [Timestamp]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Camera,
        @Timestamp
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraZoomCalibrationInsert] @Id,@RowVersion,@Camera,@Timestamp
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Camera,
            @Timestamp
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraZoomCalibrationValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ZoomCalibration [uniqueidentifier],
  @FocalLength [float](53),
  @FocalLengthOffset [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CameraZoomCalibrationValue]([Id], [RowVersion], [ZoomCalibration], [FocalLength], [FocalLengthOffset])
          VALUES(@Id, 0, @ZoomCalibration, @FocalLength, @FocalLengthOffset);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraZoomCalibrationValueInsertTrigger]
ON [CameraZoomCalibrationValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ZoomCalibration],
        [FocalLength],
        [FocalLengthOffset]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ZoomCalibration [uniqueidentifier]
    DECLARE @FocalLength [float](53)
    DECLARE @FocalLengthOffset [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ZoomCalibration,
        @FocalLength,
        @FocalLengthOffset
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraZoomCalibrationValueInsert] @Id,@RowVersion,@ZoomCalibration,@FocalLength,@FocalLengthOffset
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ZoomCalibration,
            @FocalLength,
            @FocalLengthOffset
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CatalogInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 16100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Catalog]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CatalogInsertTrigger]
ON [CatalogView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CatalogInsert] @Id,@RowVersion,@Catalog,@Name
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ElementInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @ElementType [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 16200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Element]([Id], [ElementType])
          VALUES(@Id, @ElementType);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ElementInsertTrigger]
ON [ElementView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [ElementType]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @ElementType [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @ElementType
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ElementInsert] @Id,@RowVersion,@Catalog,@Name,@ElementType
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @ElementType
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CollectionInfoInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Count [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CollectionInfo]([Id], [RowVersion], [Count])
          VALUES(@Id, 0, @Count);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CollectionInfoInsertTrigger]
ON [CollectionInfoView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Count]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Count [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Count
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CollectionInfoInsert] @Id,@RowVersion,@Count
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Count
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CountryInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Code [int],
  @Alpha2 [nvarchar](2),
  @Alpha3 [nvarchar](3)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Country]([Id], [RowVersion], [Name], [Code], [Alpha2], [Alpha3])
          VALUES(@Id, 0, @Name, @Code, @Alpha2, @Alpha3);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CountryInsertTrigger]
ON [CountryView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Code],
        [Alpha2],
        [Alpha3]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Code [int]
    DECLARE @Alpha2 [nvarchar](2)
    DECLARE @Alpha3 [nvarchar](3)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Code,
        @Alpha2,
        @Alpha3
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CountryInsert] @Id,@RowVersion,@Name,@Code,@Alpha2,@Alpha3
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Code,
            @Alpha2,
            @Alpha3
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CursorInfoInsert]
  @Id [uniqueidentifier] OUTPUT,
  @TypeCode [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [CursorInfo]([Id], [RowVersion], [TypeCode])
          VALUES(@Id, 0, @TypeCode);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CursorInfoInsertTrigger]
ON [CursorInfoView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [TypeCode]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @TypeCode [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @TypeCode
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CursorInfoInsert] @Id,@RowVersion,@TypeCode
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @TypeCode
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [DateTimeTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DateTimeTimeseriesValueInsertTrigger]
ON [DateTimeTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DateTimeTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DeviceHostInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [DeviceHost]([Id], [RowVersion], [Name])
          VALUES(@Id, 0, @Name);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DeviceHostInsertTrigger]
ON [DeviceHostView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DeviceHostInsert] @Id,@RowVersion,@Name
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DeviceHostConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Timestamp [bigint],
  @Hostname [nvarchar](127),
  @Port [int],
  @QueueName [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [DeviceHostConfiguration]([Id], [RowVersion], [Host], [Timestamp], [Hostname], [Port], [QueueName])
          VALUES(@Id, 0, @Host, @Timestamp, @Hostname, @Port, @QueueName);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DeviceHostConfigurationInsertTrigger]
ON [DeviceHostConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Timestamp],
        [Hostname],
        [Port],
        [QueueName]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Hostname [nvarchar](127)
    DECLARE @Port [int]
    DECLARE @QueueName [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Timestamp,
        @Hostname,
        @Port,
        @QueueName
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DeviceHostConfigurationInsert] @Id,@RowVersion,@Host,@Timestamp,@Hostname,@Port,@QueueName
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Timestamp,
            @Hostname,
            @Port,
            @QueueName
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DoubleTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [DoubleTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DoubleTimeseriesValueInsertTrigger]
ON [DoubleTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DoubleTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [FacilityTypeInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [FacilityType]([Id], [RowVersion], [Name])
          VALUES(@Id, 0, @Name);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [FacilityTypeInsertTrigger]
ON [FacilityTypeView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [FacilityTypeInsert] @Id,@RowVersion,@Name
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GeoPosition2DTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Latitude [float](53),
  @Longitude [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [GeoPosition2DTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Latitude], [Longitude])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Latitude, @Longitude);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GeoPosition2DTimeseriesValueInsertTrigger]
ON [GeoPosition2DTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Latitude],
        [Longitude]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Latitude,
        @Longitude
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GeoPosition2DTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Latitude,@Longitude
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Latitude,
            @Longitude
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GeoPosition3DTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Latitude [float](53),
  @Longitude [float](53),
  @Altitude [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [GeoPosition3DTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Latitude], [Longitude], [Altitude])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Latitude, @Longitude, @Altitude);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GeoPosition3DTimeseriesValueInsertTrigger]
ON [GeoPosition3DTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Latitude],
        [Longitude],
        [Altitude]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @Altitude [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Latitude,
        @Longitude,
        @Altitude
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GeoPosition3DTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Latitude,@Longitude,@Altitude
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Latitude,
            @Longitude,
            @Altitude
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GNSSDeviceCommandInsert]
  @Id [uniqueidentifier] OUTPUT,
  @GNSSDevice [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [GNSSDeviceCommand]([Id], [RowVersion], [GNSSDevice], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, 0, @GNSSDevice, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GNSSDeviceCommandInsertTrigger]
ON [GNSSDeviceCommandView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [GNSSDevice],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @GNSSDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @GNSSDevice,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GNSSDeviceCommandInsert] @Id,@RowVersion,@GNSSDevice,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @GNSSDevice,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GNSSDeviceCommandReplyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @GNSSDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [GNSSDeviceCommandReply]([Id], [RowVersion], [GNSSDevice], [Timestamp], [Command], [Status], [Message])
          VALUES(@Id, 0, @GNSSDevice, @Timestamp, @Command, @Status, @Message);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GNSSDeviceCommandReplyInsertTrigger]
ON [GNSSDeviceCommandReplyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [GNSSDevice],
        [Timestamp],
        [Command],
        [Status],
        [Message]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @GNSSDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @GNSSDevice,
        @Timestamp,
        @Command,
        @Status,
        @Message
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GNSSDeviceCommandReplyInsert] @Id,@RowVersion,@GNSSDevice,@Timestamp,@Command,@Status,@Message
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @GNSSDevice,
            @Timestamp,
            @Command,
            @Status,
            @Message
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GNSSDeviceConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @GNSSDevice [uniqueidentifier],
  @Timestamp [bigint],
  @DefaultLatitude [float](53),
  @DefaultLongitude [float](53),
  @DefaultAltitude [float](53),
  @LatitudeOffset [float](53),
  @LongitudeOffset [float](53),
  @AltitudeOffset [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [GNSSDeviceConfiguration]([Id], [RowVersion], [GNSSDevice], [Timestamp], [DefaultLatitude], [DefaultLongitude], [DefaultAltitude], [LatitudeOffset], [LongitudeOffset], [AltitudeOffset])
          VALUES(@Id, 0, @GNSSDevice, @Timestamp, @DefaultLatitude, @DefaultLongitude, @DefaultAltitude, @LatitudeOffset, @LongitudeOffset, @AltitudeOffset);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GNSSDeviceConfigurationInsertTrigger]
ON [GNSSDeviceConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [GNSSDevice],
        [Timestamp],
        [DefaultLatitude],
        [DefaultLongitude],
        [DefaultAltitude],
        [LatitudeOffset],
        [LongitudeOffset],
        [AltitudeOffset]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @GNSSDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DefaultLatitude [float](53)
    DECLARE @DefaultLongitude [float](53)
    DECLARE @DefaultAltitude [float](53)
    DECLARE @LatitudeOffset [float](53)
    DECLARE @LongitudeOffset [float](53)
    DECLARE @AltitudeOffset [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @GNSSDevice,
        @Timestamp,
        @DefaultLatitude,
        @DefaultLongitude,
        @DefaultAltitude,
        @LatitudeOffset,
        @LongitudeOffset,
        @AltitudeOffset
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GNSSDeviceConfigurationInsert] @Id,@RowVersion,@GNSSDevice,@Timestamp,@DefaultLatitude,@DefaultLongitude,@DefaultAltitude,@LatitudeOffset,@LongitudeOffset,@AltitudeOffset
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @GNSSDevice,
            @Timestamp,
            @DefaultLatitude,
            @DefaultLongitude,
            @DefaultAltitude,
            @LatitudeOffset,
            @LongitudeOffset,
            @AltitudeOffset
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GuidTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [GuidTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GuidTimeseriesValueInsertTrigger]
ON [GuidTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GuidTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroDeviceCommandInsert]
  @Id [uniqueidentifier] OUTPUT,
  @GyroDevice [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [GyroDeviceCommand]([Id], [RowVersion], [GyroDevice], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, 0, @GyroDevice, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroDeviceCommandInsertTrigger]
ON [GyroDeviceCommandView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [GyroDevice],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @GyroDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @GyroDevice,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroDeviceCommandInsert] @Id,@RowVersion,@GyroDevice,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @GyroDevice,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroDeviceCommandReplyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @GyroDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [GyroDeviceCommandReply]([Id], [RowVersion], [GyroDevice], [Timestamp], [Command], [Status], [Message])
          VALUES(@Id, 0, @GyroDevice, @Timestamp, @Command, @Status, @Message);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroDeviceCommandReplyInsertTrigger]
ON [GyroDeviceCommandReplyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [GyroDevice],
        [Timestamp],
        [Command],
        [Status],
        [Message]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @GyroDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @GyroDevice,
        @Timestamp,
        @Command,
        @Status,
        @Message
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroDeviceCommandReplyInsert] @Id,@RowVersion,@GyroDevice,@Timestamp,@Command,@Status,@Message
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @GyroDevice,
            @Timestamp,
            @Command,
            @Status,
            @Message
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroDeviceConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @GyroDevice [uniqueidentifier],
  @Timestamp [bigint],
  @DefaultHeadingTrueNorth [float](53),
  @DefaultMagneticTrueNorth [float](53),
  @HeadingTrueNorthOffset [float](53),
  @HeadingMagneticNorthOffset [float](53),
  @PitchTransducerName [nvarchar](64),
  @RollTransducerName [nvarchar](64)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [GyroDeviceConfiguration]([Id], [RowVersion], [GyroDevice], [Timestamp], [DefaultHeadingTrueNorth], [DefaultMagneticTrueNorth], [HeadingTrueNorthOffset], [HeadingMagneticNorthOffset], [PitchTransducerName], [RollTransducerName])
          VALUES(@Id, 0, @GyroDevice, @Timestamp, @DefaultHeadingTrueNorth, @DefaultMagneticTrueNorth, @HeadingTrueNorthOffset, @HeadingMagneticNorthOffset, @PitchTransducerName, @RollTransducerName);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroDeviceConfigurationInsertTrigger]
ON [GyroDeviceConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [GyroDevice],
        [Timestamp],
        [DefaultHeadingTrueNorth],
        [DefaultMagneticTrueNorth],
        [HeadingTrueNorthOffset],
        [HeadingMagneticNorthOffset],
        [PitchTransducerName],
        [RollTransducerName]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @GyroDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DefaultHeadingTrueNorth [float](53)
    DECLARE @DefaultMagneticTrueNorth [float](53)
    DECLARE @HeadingTrueNorthOffset [float](53)
    DECLARE @HeadingMagneticNorthOffset [float](53)
    DECLARE @PitchTransducerName [nvarchar](64)
    DECLARE @RollTransducerName [nvarchar](64)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @GyroDevice,
        @Timestamp,
        @DefaultHeadingTrueNorth,
        @DefaultMagneticTrueNorth,
        @HeadingTrueNorthOffset,
        @HeadingMagneticNorthOffset,
        @PitchTransducerName,
        @RollTransducerName
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroDeviceConfigurationInsert] @Id,@RowVersion,@GyroDevice,@Timestamp,@DefaultHeadingTrueNorth,@DefaultMagneticTrueNorth,@HeadingTrueNorthOffset,@HeadingMagneticNorthOffset,@PitchTransducerName,@RollTransducerName
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @GyroDevice,
            @Timestamp,
            @DefaultHeadingTrueNorth,
            @DefaultMagneticTrueNorth,
            @HeadingTrueNorthOffset,
            @HeadingMagneticNorthOffset,
            @PitchTransducerName,
            @RollTransducerName
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CallsignInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Identifier [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 18100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Identity]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Callsign]([Id], [Identifier])
          VALUES(@Id, @Identifier);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CallsignInsertTrigger]
ON [CallsignView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Identifier]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Identifier [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Identifier
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CallsignInsert] @Id,@RowVersion,@Identifier
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Identifier
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [InternationalMaritimeOrganizationNumberInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Identifier [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 18200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Identity]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [InternationalMaritimeOrganizationNumber]([Id], [Identifier])
          VALUES(@Id, @Identifier);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [InternationalMaritimeOrganizationNumberInsertTrigger]
ON [InternationalMaritimeOrganizationNumberView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Identifier]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Identifier [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Identifier
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [InternationalMaritimeOrganizationNumberInsert] @Id,@RowVersion,@Identifier
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Identifier
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MaritimeMobileServiceIdentityInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Identifier [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 18300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Identity]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [MaritimeMobileServiceIdentity]([Id], [Identifier])
          VALUES(@Id, @Identifier);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MaritimeMobileServiceIdentityInsertTrigger]
ON [MaritimeMobileServiceIdentityView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Identifier]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Identifier [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Identifier
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MaritimeMobileServiceIdentityInsert] @Id,@RowVersion,@Identifier
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Identifier
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [NameInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Text [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 18400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Identity]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Name]([Id], [Text])
          VALUES(@Id, @Text);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [NameInsertTrigger]
ON [NameView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Text]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Text [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Text
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [NameInsert] @Id,@RowVersion,@Text
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Text
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int16TimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [smallint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Int16TimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int16TimeseriesValueInsertTrigger]
ON [Int16TimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [smallint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int16TimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int32TimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Int32TimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int32TimeseriesValueInsertTrigger]
ON [Int32TimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int32TimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int64TimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Int64TimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int64TimeseriesValueInsertTrigger]
ON [Int64TimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int64TimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BaseStationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Type [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 18900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [BaseStation]([Id], [Name], [Type])
          VALUES(@Id, @Name, @Type);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BaseStationInsertTrigger]
ON [BaseStationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Type]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Type [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Type
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BaseStationInsert] @Id,@RowVersion,@Name,@Type
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Type
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CameraDeviceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 19100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Device]([Id], [Host], [Name], [Description], [EnabledTimeseries])
          VALUES(@Id, @Host, @Name, @Description, @EnabledTimeseries);
      INSERT INTO [CameraDevice]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CameraDeviceInsertTrigger]
ON [CameraDeviceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Name],
        [Description],
        [EnabledTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Name,
        @Description,
        @EnabledTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CameraDeviceInsert] @Id,@RowVersion,@Host,@Name,@Description,@EnabledTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Name,
            @Description,
            @EnabledTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GNSSDeviceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier],
  @LatitudeTimeseries [uniqueidentifier],
  @LongitudeTimeseries [uniqueidentifier],
  @AltitudeTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 19200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Device]([Id], [Host], [Name], [Description], [EnabledTimeseries])
          VALUES(@Id, @Host, @Name, @Description, @EnabledTimeseries);
      INSERT INTO [GNSSDevice]([Id], [LatitudeTimeseries], [LongitudeTimeseries], [AltitudeTimeseries])
          VALUES(@Id, @LatitudeTimeseries, @LongitudeTimeseries, @AltitudeTimeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GNSSDeviceInsertTrigger]
ON [GNSSDeviceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Name],
        [Description],
        [EnabledTimeseries],
        [LatitudeTimeseries],
        [LongitudeTimeseries],
        [AltitudeTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    DECLARE @LatitudeTimeseries [uniqueidentifier]
    DECLARE @LongitudeTimeseries [uniqueidentifier]
    DECLARE @AltitudeTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Name,
        @Description,
        @EnabledTimeseries,
        @LatitudeTimeseries,
        @LongitudeTimeseries,
        @AltitudeTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GNSSDeviceInsert] @Id,@RowVersion,@Host,@Name,@Description,@EnabledTimeseries,@LatitudeTimeseries,@LongitudeTimeseries,@AltitudeTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Name,
            @Description,
            @EnabledTimeseries,
            @LatitudeTimeseries,
            @LongitudeTimeseries,
            @AltitudeTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroDeviceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier],
  @HeadingTrueNorthTimeseries [uniqueidentifier],
  @HeadingMagneticNorthTimeseries [uniqueidentifier],
  @PitchTimeseries [uniqueidentifier],
  @RateOfTurnTimeseries [uniqueidentifier],
  @RollTimeseries [uniqueidentifier],
  @CourseTimeseries [uniqueidentifier],
  @SpeedTimeseries [uniqueidentifier],
  @GNSSDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 19300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Device]([Id], [Host], [Name], [Description], [EnabledTimeseries])
          VALUES(@Id, @Host, @Name, @Description, @EnabledTimeseries);
      INSERT INTO [GyroDevice]([Id], [HeadingTrueNorthTimeseries], [HeadingMagneticNorthTimeseries], [PitchTimeseries], [RateOfTurnTimeseries], [RollTimeseries], [CourseTimeseries], [SpeedTimeseries], [GNSSDevice])
          VALUES(@Id, @HeadingTrueNorthTimeseries, @HeadingMagneticNorthTimeseries, @PitchTimeseries, @RateOfTurnTimeseries, @RollTimeseries, @CourseTimeseries, @SpeedTimeseries, @GNSSDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroDeviceInsertTrigger]
ON [GyroDeviceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Name],
        [Description],
        [EnabledTimeseries],
        [HeadingTrueNorthTimeseries],
        [HeadingMagneticNorthTimeseries],
        [PitchTimeseries],
        [RateOfTurnTimeseries],
        [RollTimeseries],
        [CourseTimeseries],
        [SpeedTimeseries],
        [GNSSDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    DECLARE @HeadingTrueNorthTimeseries [uniqueidentifier]
    DECLARE @HeadingMagneticNorthTimeseries [uniqueidentifier]
    DECLARE @PitchTimeseries [uniqueidentifier]
    DECLARE @RateOfTurnTimeseries [uniqueidentifier]
    DECLARE @RollTimeseries [uniqueidentifier]
    DECLARE @CourseTimeseries [uniqueidentifier]
    DECLARE @SpeedTimeseries [uniqueidentifier]
    DECLARE @GNSSDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Name,
        @Description,
        @EnabledTimeseries,
        @HeadingTrueNorthTimeseries,
        @HeadingMagneticNorthTimeseries,
        @PitchTimeseries,
        @RateOfTurnTimeseries,
        @RollTimeseries,
        @CourseTimeseries,
        @SpeedTimeseries,
        @GNSSDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroDeviceInsert] @Id,@RowVersion,@Host,@Name,@Description,@EnabledTimeseries,@HeadingTrueNorthTimeseries,@HeadingMagneticNorthTimeseries,@PitchTimeseries,@RateOfTurnTimeseries,@RollTimeseries,@CourseTimeseries,@SpeedTimeseries,@GNSSDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Name,
            @Description,
            @EnabledTimeseries,
            @HeadingTrueNorthTimeseries,
            @HeadingMagneticNorthTimeseries,
            @PitchTimeseries,
            @RateOfTurnTimeseries,
            @RollTimeseries,
            @CourseTimeseries,
            @SpeedTimeseries,
            @GNSSDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LineInputDeviceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 19400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Device]([Id], [Host], [Name], [Description], [EnabledTimeseries])
          VALUES(@Id, @Host, @Name, @Description, @EnabledTimeseries);
      INSERT INTO [LineInputDevice]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LineInputDeviceInsertTrigger]
ON [LineInputDeviceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Name],
        [Description],
        [EnabledTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Name,
        @Description,
        @EnabledTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LineInputDeviceInsert] @Id,@RowVersion,@Host,@Name,@Description,@EnabledTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Name,
            @Description,
            @EnabledTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [OilSpillDetectorDeviceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 19500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Device]([Id], [Host], [Name], [Description], [EnabledTimeseries])
          VALUES(@Id, @Host, @Name, @Description, @EnabledTimeseries);
      INSERT INTO [OilSpillDetectorDevice]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [OilSpillDetectorDeviceInsertTrigger]
ON [OilSpillDetectorDeviceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Name],
        [Description],
        [EnabledTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Name,
        @Description,
        @EnabledTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [OilSpillDetectorDeviceInsert] @Id,@RowVersion,@Host,@Name,@Description,@EnabledTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Name,
            @Description,
            @EnabledTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadioDeviceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 19600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Device]([Id], [Host], [Name], [Description], [EnabledTimeseries])
          VALUES(@Id, @Host, @Name, @Description, @EnabledTimeseries);
      INSERT INTO [RadioDevice]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadioDeviceInsertTrigger]
ON [RadioDeviceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Name],
        [Description],
        [EnabledTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Name,
        @Description,
        @EnabledTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadioDeviceInsert] @Id,@RowVersion,@Host,@Name,@Description,@EnabledTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Name,
            @Description,
            @EnabledTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadomeDeviceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier],
  @Radar [uniqueidentifier],
  @PressureTimeseries [uniqueidentifier],
  @TemperatureTimeseries [uniqueidentifier],
  @DewPointTimeseries [uniqueidentifier],
  @StatusTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 19700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Device]([Id], [Host], [Name], [Description], [EnabledTimeseries])
          VALUES(@Id, @Host, @Name, @Description, @EnabledTimeseries);
      INSERT INTO [RadomeDevice]([Id], [Radar], [PressureTimeseries], [TemperatureTimeseries], [DewPointTimeseries], [StatusTimeseries])
          VALUES(@Id, @Radar, @PressureTimeseries, @TemperatureTimeseries, @DewPointTimeseries, @StatusTimeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadomeDeviceInsertTrigger]
ON [RadomeDeviceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Name],
        [Description],
        [EnabledTimeseries],
        [Radar],
        [PressureTimeseries],
        [TemperatureTimeseries],
        [DewPointTimeseries],
        [StatusTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    DECLARE @Radar [uniqueidentifier]
    DECLARE @PressureTimeseries [uniqueidentifier]
    DECLARE @TemperatureTimeseries [uniqueidentifier]
    DECLARE @DewPointTimeseries [uniqueidentifier]
    DECLARE @StatusTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Name,
        @Description,
        @EnabledTimeseries,
        @Radar,
        @PressureTimeseries,
        @TemperatureTimeseries,
        @DewPointTimeseries,
        @StatusTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadomeDeviceInsert] @Id,@RowVersion,@Host,@Name,@Description,@EnabledTimeseries,@Radar,@PressureTimeseries,@TemperatureTimeseries,@DewPointTimeseries,@StatusTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Name,
            @Description,
            @EnabledTimeseries,
            @Radar,
            @PressureTimeseries,
            @TemperatureTimeseries,
            @DewPointTimeseries,
            @StatusTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisDeviceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 19900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Device]([Id], [Host], [Name], [Description], [EnabledTimeseries])
          VALUES(@Id, @Host, @Name, @Description, @EnabledTimeseries);
      INSERT INTO [TrackerDevice]([Id])
          VALUES(@Id);
      INSERT INTO [AisDevice]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisDeviceInsertTrigger]
ON [AisDeviceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Name],
        [Description],
        [EnabledTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Name,
        @Description,
        @EnabledTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisDeviceInsert] @Id,@RowVersion,@Host,@Name,@Description,@EnabledTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Name,
            @Description,
            @EnabledTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarDeviceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier],
  @SaveSettingsTimeseries [uniqueidentifier],
  @PowerOnTimeseries [uniqueidentifier],
  @TrackingOnTimeseries [uniqueidentifier],
  @RadarPulseTimeseries [uniqueidentifier],
  @TuningTimeseries [uniqueidentifier],
  @BlankSector1Timeseries [uniqueidentifier],
  @Sector1StartTimeseries [uniqueidentifier],
  @Sector1EndTimeseries [uniqueidentifier],
  @BlankSector2Timeseries [uniqueidentifier],
  @Sector2StartTimeseries [uniqueidentifier],
  @Sector2EndTimeseries [uniqueidentifier],
  @EnableAutomaticFrequencyControlTimeseries [uniqueidentifier],
  @AzimuthOffsetTimeseries [uniqueidentifier],
  @EnableSensitivityTimeControlTimeseries [uniqueidentifier],
  @AutomaticSensitivityTimeControlTimeseries [uniqueidentifier],
  @SensitivityTimeControlLevelTimeseries [uniqueidentifier],
  @EnableFastTimeConstantTimeseries [uniqueidentifier],
  @FastTimeConstantLevelTimeseries [uniqueidentifier],
  @FastTimeConstantModeTimeseries [uniqueidentifier],
  @LatitudeTimeseries [uniqueidentifier],
  @LongitudeTimeseries [uniqueidentifier],
  @Radome [uniqueidentifier],
  @GNSSDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 20000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Device]([Id], [Host], [Name], [Description], [EnabledTimeseries])
          VALUES(@Id, @Host, @Name, @Description, @EnabledTimeseries);
      INSERT INTO [TrackerDevice]([Id])
          VALUES(@Id);
      INSERT INTO [RadarDevice]([Id], [SaveSettingsTimeseries], [PowerOnTimeseries], [TrackingOnTimeseries], [RadarPulseTimeseries], [TuningTimeseries], [BlankSector1Timeseries], [Sector1StartTimeseries], [Sector1EndTimeseries], [BlankSector2Timeseries], [Sector2StartTimeseries], [Sector2EndTimeseries], [EnableAutomaticFrequencyControlTimeseries], [AzimuthOffsetTimeseries], [EnableSensitivityTimeControlTimeseries], [AutomaticSensitivityTimeControlTimeseries], [SensitivityTimeControlLevelTimeseries], [EnableFastTimeConstantTimeseries], [FastTimeConstantLevelTimeseries], [FastTimeConstantModeTimeseries], [LatitudeTimeseries], [LongitudeTimeseries], [Radome], [GNSSDevice])
          VALUES(@Id, @SaveSettingsTimeseries, @PowerOnTimeseries, @TrackingOnTimeseries, @RadarPulseTimeseries, @TuningTimeseries, @BlankSector1Timeseries, @Sector1StartTimeseries, @Sector1EndTimeseries, @BlankSector2Timeseries, @Sector2StartTimeseries, @Sector2EndTimeseries, @EnableAutomaticFrequencyControlTimeseries, @AzimuthOffsetTimeseries, @EnableSensitivityTimeControlTimeseries, @AutomaticSensitivityTimeControlTimeseries, @SensitivityTimeControlLevelTimeseries, @EnableFastTimeConstantTimeseries, @FastTimeConstantLevelTimeseries, @FastTimeConstantModeTimeseries, @LatitudeTimeseries, @LongitudeTimeseries, @Radome, @GNSSDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarDeviceInsertTrigger]
ON [RadarDeviceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Name],
        [Description],
        [EnabledTimeseries],
        [SaveSettingsTimeseries],
        [PowerOnTimeseries],
        [TrackingOnTimeseries],
        [RadarPulseTimeseries],
        [TuningTimeseries],
        [BlankSector1Timeseries],
        [Sector1StartTimeseries],
        [Sector1EndTimeseries],
        [BlankSector2Timeseries],
        [Sector2StartTimeseries],
        [Sector2EndTimeseries],
        [EnableAutomaticFrequencyControlTimeseries],
        [AzimuthOffsetTimeseries],
        [EnableSensitivityTimeControlTimeseries],
        [AutomaticSensitivityTimeControlTimeseries],
        [SensitivityTimeControlLevelTimeseries],
        [EnableFastTimeConstantTimeseries],
        [FastTimeConstantLevelTimeseries],
        [FastTimeConstantModeTimeseries],
        [LatitudeTimeseries],
        [LongitudeTimeseries],
        [Radome],
        [GNSSDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    DECLARE @SaveSettingsTimeseries [uniqueidentifier]
    DECLARE @PowerOnTimeseries [uniqueidentifier]
    DECLARE @TrackingOnTimeseries [uniqueidentifier]
    DECLARE @RadarPulseTimeseries [uniqueidentifier]
    DECLARE @TuningTimeseries [uniqueidentifier]
    DECLARE @BlankSector1Timeseries [uniqueidentifier]
    DECLARE @Sector1StartTimeseries [uniqueidentifier]
    DECLARE @Sector1EndTimeseries [uniqueidentifier]
    DECLARE @BlankSector2Timeseries [uniqueidentifier]
    DECLARE @Sector2StartTimeseries [uniqueidentifier]
    DECLARE @Sector2EndTimeseries [uniqueidentifier]
    DECLARE @EnableAutomaticFrequencyControlTimeseries [uniqueidentifier]
    DECLARE @AzimuthOffsetTimeseries [uniqueidentifier]
    DECLARE @EnableSensitivityTimeControlTimeseries [uniqueidentifier]
    DECLARE @AutomaticSensitivityTimeControlTimeseries [uniqueidentifier]
    DECLARE @SensitivityTimeControlLevelTimeseries [uniqueidentifier]
    DECLARE @EnableFastTimeConstantTimeseries [uniqueidentifier]
    DECLARE @FastTimeConstantLevelTimeseries [uniqueidentifier]
    DECLARE @FastTimeConstantModeTimeseries [uniqueidentifier]
    DECLARE @LatitudeTimeseries [uniqueidentifier]
    DECLARE @LongitudeTimeseries [uniqueidentifier]
    DECLARE @Radome [uniqueidentifier]
    DECLARE @GNSSDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Name,
        @Description,
        @EnabledTimeseries,
        @SaveSettingsTimeseries,
        @PowerOnTimeseries,
        @TrackingOnTimeseries,
        @RadarPulseTimeseries,
        @TuningTimeseries,
        @BlankSector1Timeseries,
        @Sector1StartTimeseries,
        @Sector1EndTimeseries,
        @BlankSector2Timeseries,
        @Sector2StartTimeseries,
        @Sector2EndTimeseries,
        @EnableAutomaticFrequencyControlTimeseries,
        @AzimuthOffsetTimeseries,
        @EnableSensitivityTimeControlTimeseries,
        @AutomaticSensitivityTimeControlTimeseries,
        @SensitivityTimeControlLevelTimeseries,
        @EnableFastTimeConstantTimeseries,
        @FastTimeConstantLevelTimeseries,
        @FastTimeConstantModeTimeseries,
        @LatitudeTimeseries,
        @LongitudeTimeseries,
        @Radome,
        @GNSSDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarDeviceInsert] @Id,@RowVersion,@Host,@Name,@Description,@EnabledTimeseries,@SaveSettingsTimeseries,@PowerOnTimeseries,@TrackingOnTimeseries,@RadarPulseTimeseries,@TuningTimeseries,@BlankSector1Timeseries,@Sector1StartTimeseries,@Sector1EndTimeseries,@BlankSector2Timeseries,@Sector2StartTimeseries,@Sector2EndTimeseries,@EnableAutomaticFrequencyControlTimeseries,@AzimuthOffsetTimeseries,@EnableSensitivityTimeControlTimeseries,@AutomaticSensitivityTimeControlTimeseries,@SensitivityTimeControlLevelTimeseries,@EnableFastTimeConstantTimeseries,@FastTimeConstantLevelTimeseries,@FastTimeConstantModeTimeseries,@LatitudeTimeseries,@LongitudeTimeseries,@Radome,@GNSSDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Name,
            @Description,
            @EnabledTimeseries,
            @SaveSettingsTimeseries,
            @PowerOnTimeseries,
            @TrackingOnTimeseries,
            @RadarPulseTimeseries,
            @TuningTimeseries,
            @BlankSector1Timeseries,
            @Sector1StartTimeseries,
            @Sector1EndTimeseries,
            @BlankSector2Timeseries,
            @Sector2StartTimeseries,
            @Sector2EndTimeseries,
            @EnableAutomaticFrequencyControlTimeseries,
            @AzimuthOffsetTimeseries,
            @EnableSensitivityTimeControlTimeseries,
            @AutomaticSensitivityTimeControlTimeseries,
            @SensitivityTimeControlLevelTimeseries,
            @EnableFastTimeConstantTimeseries,
            @FastTimeConstantLevelTimeseries,
            @FastTimeConstantModeTimeseries,
            @LatitudeTimeseries,
            @LongitudeTimeseries,
            @Radome,
            @GNSSDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationDeviceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier],
  @BarometricPressureTimeseries [uniqueidentifier],
  @AirTemperatureTimeseries [uniqueidentifier],
  @WaterTemperatureTimeseries [uniqueidentifier],
  @RelativeHumidityTimeseries [uniqueidentifier],
  @AbsoluteHumidityTimeseries [uniqueidentifier],
  @DewPointTimeseries [uniqueidentifier],
  @WindDirectionTimeseries [uniqueidentifier],
  @WindSpeedTimeseries [uniqueidentifier],
  @Gyro [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 20100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Device]([Id], [Host], [Name], [Description], [EnabledTimeseries])
          VALUES(@Id, @Host, @Name, @Description, @EnabledTimeseries);
      INSERT INTO [WeatherStationDevice]([Id], [BarometricPressureTimeseries], [AirTemperatureTimeseries], [WaterTemperatureTimeseries], [RelativeHumidityTimeseries], [AbsoluteHumidityTimeseries], [DewPointTimeseries], [WindDirectionTimeseries], [WindSpeedTimeseries], [Gyro])
          VALUES(@Id, @BarometricPressureTimeseries, @AirTemperatureTimeseries, @WaterTemperatureTimeseries, @RelativeHumidityTimeseries, @AbsoluteHumidityTimeseries, @DewPointTimeseries, @WindDirectionTimeseries, @WindSpeedTimeseries, @Gyro);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationDeviceInsertTrigger]
ON [WeatherStationDeviceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Name],
        [Description],
        [EnabledTimeseries],
        [BarometricPressureTimeseries],
        [AirTemperatureTimeseries],
        [WaterTemperatureTimeseries],
        [RelativeHumidityTimeseries],
        [AbsoluteHumidityTimeseries],
        [DewPointTimeseries],
        [WindDirectionTimeseries],
        [WindSpeedTimeseries],
        [Gyro]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    DECLARE @BarometricPressureTimeseries [uniqueidentifier]
    DECLARE @AirTemperatureTimeseries [uniqueidentifier]
    DECLARE @WaterTemperatureTimeseries [uniqueidentifier]
    DECLARE @RelativeHumidityTimeseries [uniqueidentifier]
    DECLARE @AbsoluteHumidityTimeseries [uniqueidentifier]
    DECLARE @DewPointTimeseries [uniqueidentifier]
    DECLARE @WindDirectionTimeseries [uniqueidentifier]
    DECLARE @WindSpeedTimeseries [uniqueidentifier]
    DECLARE @Gyro [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Name,
        @Description,
        @EnabledTimeseries,
        @BarometricPressureTimeseries,
        @AirTemperatureTimeseries,
        @WaterTemperatureTimeseries,
        @RelativeHumidityTimeseries,
        @AbsoluteHumidityTimeseries,
        @DewPointTimeseries,
        @WindDirectionTimeseries,
        @WindSpeedTimeseries,
        @Gyro
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationDeviceInsert] @Id,@RowVersion,@Host,@Name,@Description,@EnabledTimeseries,@BarometricPressureTimeseries,@AirTemperatureTimeseries,@WaterTemperatureTimeseries,@RelativeHumidityTimeseries,@AbsoluteHumidityTimeseries,@DewPointTimeseries,@WindDirectionTimeseries,@WindSpeedTimeseries,@Gyro
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Name,
            @Description,
            @EnabledTimeseries,
            @BarometricPressureTimeseries,
            @AirTemperatureTimeseries,
            @WaterTemperatureTimeseries,
            @RelativeHumidityTimeseries,
            @AbsoluteHumidityTimeseries,
            @DewPointTimeseries,
            @WindDirectionTimeseries,
            @WindSpeedTimeseries,
            @Gyro
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [FacilityInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Type [uniqueidentifier],
  @Longitude [float](53),
  @Latitude [float](53),
  @Altitude [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 20200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [Facility]([Id], [Name], [Type], [Longitude], [Latitude], [Altitude])
          VALUES(@Id, @Name, @Type, @Longitude, @Latitude, @Altitude);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [FacilityInsertTrigger]
ON [FacilityView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Type],
        [Longitude],
        [Latitude],
        [Altitude]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Type [uniqueidentifier]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @Altitude [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Type,
        @Longitude,
        @Latitude,
        @Altitude
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [FacilityInsert] @Id,@RowVersion,@Name,@Type,@Longitude,@Latitude,@Altitude
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Type,
            @Longitude,
            @Latitude,
            @Altitude
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AircraftInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Type [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 20400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [TrackableItem]([Id])
          VALUES(@Id);
      INSERT INTO [Aircraft]([Id], [Name], [Type])
          VALUES(@Id, @Name, @Type);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AircraftInsertTrigger]
ON [AircraftView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Type]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Type [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Type
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AircraftInsert] @Id,@RowVersion,@Name,@Type
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Type
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisAidToNavigationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @MMSI [uniqueidentifier],
  @NavigationalAidType [int],
  @Position [uniqueidentifier],
  @IsVirtual [bit],
  @ToBow [int],
  @ToStern [int],
  @ToPort [int],
  @ToStarboard [int],
  @OffPositionTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 20500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [TrackableItem]([Id])
          VALUES(@Id);
      INSERT INTO [AisAidToNavigation]([Id], [Name], [MMSI], [NavigationalAidType], [Position], [IsVirtual], [ToBow], [ToStern], [ToPort], [ToStarboard], [OffPositionTimeseries])
          VALUES(@Id, @Name, @MMSI, @NavigationalAidType, @Position, @IsVirtual, @ToBow, @ToStern, @ToPort, @ToStarboard, @OffPositionTimeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisAidToNavigationInsertTrigger]
ON [AisAidToNavigationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [MMSI],
        [NavigationalAidType],
        [Position],
        [IsVirtual],
        [ToBow],
        [ToStern],
        [ToPort],
        [ToStarboard],
        [OffPositionTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @MMSI [uniqueidentifier]
    DECLARE @NavigationalAidType [int]
    DECLARE @Position [uniqueidentifier]
    DECLARE @IsVirtual [bit]
    DECLARE @ToBow [int]
    DECLARE @ToStern [int]
    DECLARE @ToPort [int]
    DECLARE @ToStarboard [int]
    DECLARE @OffPositionTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @MMSI,
        @NavigationalAidType,
        @Position,
        @IsVirtual,
        @ToBow,
        @ToStern,
        @ToPort,
        @ToStarboard,
        @OffPositionTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisAidToNavigationInsert] @Id,@RowVersion,@Name,@MMSI,@NavigationalAidType,@Position,@IsVirtual,@ToBow,@ToStern,@ToPort,@ToStarboard,@OffPositionTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @MMSI,
            @NavigationalAidType,
            @Position,
            @IsVirtual,
            @ToBow,
            @ToStern,
            @ToPort,
            @ToStarboard,
            @OffPositionTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [VehicleInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Type [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 20600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [TrackableItem]([Id])
          VALUES(@Id);
      INSERT INTO [Vehicle]([Id], [Name], [Type])
          VALUES(@Id, @Name, @Type);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [VehicleInsertTrigger]
ON [VehicleView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Type]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Type [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Type
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [VehicleInsert] @Id,@RowVersion,@Name,@Type
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Type
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [VesselInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Type [uniqueidentifier],
  @ToBow [int],
  @ToStern [int],
  @ToPort [int],
  @ToStarboard [int],
  @DraughtTimeseries [uniqueidentifier],
  @PersonsOnBoardTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 20700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Item]([Id], [EntityType], [RowVersion])
          VALUES(@Id, @EntityType, 0);
      INSERT INTO [TrackableItem]([Id])
          VALUES(@Id);
      INSERT INTO [Vessel]([Id], [Name], [Type], [ToBow], [ToStern], [ToPort], [ToStarboard], [DraughtTimeseries], [PersonsOnBoardTimeseries])
          VALUES(@Id, @Name, @Type, @ToBow, @ToStern, @ToPort, @ToStarboard, @DraughtTimeseries, @PersonsOnBoardTimeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [VesselInsertTrigger]
ON [VesselView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Type],
        [ToBow],
        [ToStern],
        [ToPort],
        [ToStarboard],
        [DraughtTimeseries],
        [PersonsOnBoardTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Type [uniqueidentifier]
    DECLARE @ToBow [int]
    DECLARE @ToStern [int]
    DECLARE @ToPort [int]
    DECLARE @ToStarboard [int]
    DECLARE @DraughtTimeseries [uniqueidentifier]
    DECLARE @PersonsOnBoardTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Type,
        @ToBow,
        @ToStern,
        @ToPort,
        @ToStarboard,
        @DraughtTimeseries,
        @PersonsOnBoardTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [VesselInsert] @Id,@RowVersion,@Name,@Type,@ToBow,@ToStern,@ToPort,@ToStarboard,@DraughtTimeseries,@PersonsOnBoardTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Type,
            @ToBow,
            @ToStern,
            @ToPort,
            @ToStarboard,
            @DraughtTimeseries,
            @PersonsOnBoardTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ItemIdentityLinkInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Item [uniqueidentifier],
  @Identity [uniqueidentifier],
  @Start [bigint],
  @End [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [ItemIdentityLink]([Id], [RowVersion], [Item], [Identity], [Start], [End])
          VALUES(@Id, 0, @Item, @Identity, @Start, @End);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ItemIdentityLinkInsertTrigger]
ON [ItemIdentityLinkView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Item],
        [Identity],
        [Start],
        [End]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Item [uniqueidentifier]
    DECLARE @Identity [uniqueidentifier]
    DECLARE @Start [bigint]
    DECLARE @End [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Item,
        @Identity,
        @Start,
        @End
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ItemIdentityLinkInsert] @Id,@RowVersion,@Item,@Identity,@Start,@End
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Item,
            @Identity,
            @Start,
            @End
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ItemParentChildLinkInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Parent [uniqueidentifier],
  @Child [uniqueidentifier],
  @Timestamp [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [ItemParentChildLink]([Id], [RowVersion], [Parent], [Child], [Timestamp])
          VALUES(@Id, 0, @Parent, @Child, @Timestamp);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ItemParentChildLinkInsertTrigger]
ON [ItemParentChildLinkView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Parent],
        [Child],
        [Timestamp]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Parent [uniqueidentifier]
    DECLARE @Child [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Parent,
        @Child,
        @Timestamp
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ItemParentChildLinkInsert] @Id,@RowVersion,@Parent,@Child,@Timestamp
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Parent,
            @Child,
            @Timestamp
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LineInputDeviceCommandInsert]
  @Id [uniqueidentifier] OUTPUT,
  @LineInputDevice [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LineInputDeviceCommand]([Id], [RowVersion], [LineInputDevice], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, 0, @LineInputDevice, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LineInputDeviceCommandInsertTrigger]
ON [LineInputDeviceCommandView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [LineInputDevice],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @LineInputDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @LineInputDevice,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LineInputDeviceCommandInsert] @Id,@RowVersion,@LineInputDevice,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @LineInputDevice,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LineInputDeviceCommandReplyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @LineInputDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LineInputDeviceCommandReply]([Id], [RowVersion], [LineInputDevice], [Timestamp], [Command], [Status], [Message])
          VALUES(@Id, 0, @LineInputDevice, @Timestamp, @Command, @Status, @Message);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LineInputDeviceCommandReplyInsertTrigger]
ON [LineInputDeviceCommandReplyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [LineInputDevice],
        [Timestamp],
        [Command],
        [Status],
        [Message]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @LineInputDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @LineInputDevice,
        @Timestamp,
        @Command,
        @Status,
        @Message
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LineInputDeviceCommandReplyInsert] @Id,@RowVersion,@LineInputDevice,@Timestamp,@Command,@Status,@Message
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @LineInputDevice,
            @Timestamp,
            @Command,
            @Status,
            @Message
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LineInputDeviceConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @LineInputDevice [uniqueidentifier],
  @Timestamp [bigint],
  @StoreReceivedSentences [bit],
  @StoreSentMessages [bit],
  @StoreUnsentMessages [bit],
  @NMEA [bit],
  @StrictNMEA [bit],
  @ConnectionType [int],
  @UdpReceivePort [int],
  @UdpSendHostname [nvarchar](127),
  @UdpSendPort [int],
  @TcpHostname [nvarchar](127),
  @TcpPort [int],
  @UseHttpLogin [bit],
  @LoginHostname [nvarchar](127),
  @LoginPort [int],
  @UserName [nvarchar](127),
  @Password [nvarchar](127),
  @ComPort [nvarchar](127),
  @BaudRate [int],
  @DataBits [int],
  @DiscardNull [bit],
  @DtrEnable [bit],
  @Handshake [int],
  @NewLine [nvarchar](127),
  @Parity [int],
  @ParityReplace [tinyint],
  @ReadBufferSize [int],
  @ReadTimeout [bigint],
  @ReceivedBytesThreshold [int],
  @RtsEnable [bit],
  @StopBits [int],
  @WriteBufferSize [int],
  @WriteTimeout [bigint],
  @PairedComPort [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LineInputDeviceConfiguration]([Id], [RowVersion], [LineInputDevice], [Timestamp], [StoreReceivedSentences], [StoreSentMessages], [StoreUnsentMessages], [NMEA], [StrictNMEA], [ConnectionType], [UdpReceivePort], [UdpSendHostname], [UdpSendPort], [TcpHostname], [TcpPort], [UseHttpLogin], [LoginHostname], [LoginPort], [UserName], [Password], [ComPort], [BaudRate], [DataBits], [DiscardNull], [DtrEnable], [Handshake], [NewLine], [Parity], [ParityReplace], [ReadBufferSize], [ReadTimeout], [ReceivedBytesThreshold], [RtsEnable], [StopBits], [WriteBufferSize], [WriteTimeout], [PairedComPort])
          VALUES(@Id, 0, @LineInputDevice, @Timestamp, @StoreReceivedSentences, @StoreSentMessages, @StoreUnsentMessages, @NMEA, @StrictNMEA, @ConnectionType, @UdpReceivePort, @UdpSendHostname, @UdpSendPort, @TcpHostname, @TcpPort, @UseHttpLogin, @LoginHostname, @LoginPort, @UserName, @Password, @ComPort, @BaudRate, @DataBits, @DiscardNull, @DtrEnable, @Handshake, @NewLine, @Parity, @ParityReplace, @ReadBufferSize, @ReadTimeout, @ReceivedBytesThreshold, @RtsEnable, @StopBits, @WriteBufferSize, @WriteTimeout, @PairedComPort);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LineInputDeviceConfigurationInsertTrigger]
ON [LineInputDeviceConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [LineInputDevice],
        [Timestamp],
        [StoreReceivedSentences],
        [StoreSentMessages],
        [StoreUnsentMessages],
        [NMEA],
        [StrictNMEA],
        [ConnectionType],
        [UdpReceivePort],
        [UdpSendHostname],
        [UdpSendPort],
        [TcpHostname],
        [TcpPort],
        [UseHttpLogin],
        [LoginHostname],
        [LoginPort],
        [UserName],
        [Password],
        [ComPort],
        [BaudRate],
        [DataBits],
        [DiscardNull],
        [DtrEnable],
        [Handshake],
        [NewLine],
        [Parity],
        [ParityReplace],
        [ReadBufferSize],
        [ReadTimeout],
        [ReceivedBytesThreshold],
        [RtsEnable],
        [StopBits],
        [WriteBufferSize],
        [WriteTimeout],
        [PairedComPort]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @LineInputDevice [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @StoreReceivedSentences [bit]
    DECLARE @StoreSentMessages [bit]
    DECLARE @StoreUnsentMessages [bit]
    DECLARE @NMEA [bit]
    DECLARE @StrictNMEA [bit]
    DECLARE @ConnectionType [int]
    DECLARE @UdpReceivePort [int]
    DECLARE @UdpSendHostname [nvarchar](127)
    DECLARE @UdpSendPort [int]
    DECLARE @TcpHostname [nvarchar](127)
    DECLARE @TcpPort [int]
    DECLARE @UseHttpLogin [bit]
    DECLARE @LoginHostname [nvarchar](127)
    DECLARE @LoginPort [int]
    DECLARE @UserName [nvarchar](127)
    DECLARE @Password [nvarchar](127)
    DECLARE @ComPort [nvarchar](127)
    DECLARE @BaudRate [int]
    DECLARE @DataBits [int]
    DECLARE @DiscardNull [bit]
    DECLARE @DtrEnable [bit]
    DECLARE @Handshake [int]
    DECLARE @NewLine [nvarchar](127)
    DECLARE @Parity [int]
    DECLARE @ParityReplace [tinyint]
    DECLARE @ReadBufferSize [int]
    DECLARE @ReadTimeout [bigint]
    DECLARE @ReceivedBytesThreshold [int]
    DECLARE @RtsEnable [bit]
    DECLARE @StopBits [int]
    DECLARE @WriteBufferSize [int]
    DECLARE @WriteTimeout [bigint]
    DECLARE @PairedComPort [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @LineInputDevice,
        @Timestamp,
        @StoreReceivedSentences,
        @StoreSentMessages,
        @StoreUnsentMessages,
        @NMEA,
        @StrictNMEA,
        @ConnectionType,
        @UdpReceivePort,
        @UdpSendHostname,
        @UdpSendPort,
        @TcpHostname,
        @TcpPort,
        @UseHttpLogin,
        @LoginHostname,
        @LoginPort,
        @UserName,
        @Password,
        @ComPort,
        @BaudRate,
        @DataBits,
        @DiscardNull,
        @DtrEnable,
        @Handshake,
        @NewLine,
        @Parity,
        @ParityReplace,
        @ReadBufferSize,
        @ReadTimeout,
        @ReceivedBytesThreshold,
        @RtsEnable,
        @StopBits,
        @WriteBufferSize,
        @WriteTimeout,
        @PairedComPort
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LineInputDeviceConfigurationInsert] @Id,@RowVersion,@LineInputDevice,@Timestamp,@StoreReceivedSentences,@StoreSentMessages,@StoreUnsentMessages,@NMEA,@StrictNMEA,@ConnectionType,@UdpReceivePort,@UdpSendHostname,@UdpSendPort,@TcpHostname,@TcpPort,@UseHttpLogin,@LoginHostname,@LoginPort,@UserName,@Password,@ComPort,@BaudRate,@DataBits,@DiscardNull,@DtrEnable,@Handshake,@NewLine,@Parity,@ParityReplace,@ReadBufferSize,@ReadTimeout,@ReceivedBytesThreshold,@RtsEnable,@StopBits,@WriteBufferSize,@WriteTimeout,@PairedComPort
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @LineInputDevice,
            @Timestamp,
            @StoreReceivedSentences,
            @StoreSentMessages,
            @StoreUnsentMessages,
            @NMEA,
            @StrictNMEA,
            @ConnectionType,
            @UdpReceivePort,
            @UdpSendHostname,
            @UdpSendPort,
            @TcpHostname,
            @TcpPort,
            @UseHttpLogin,
            @LoginHostname,
            @LoginPort,
            @UserName,
            @Password,
            @ComPort,
            @BaudRate,
            @DataBits,
            @DiscardNull,
            @DtrEnable,
            @Handshake,
            @NewLine,
            @Parity,
            @ParityReplace,
            @ReadBufferSize,
            @ReadTimeout,
            @ReceivedBytesThreshold,
            @RtsEnable,
            @StopBits,
            @WriteBufferSize,
            @WriteTimeout,
            @PairedComPort
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LineInputMessageRoutingInsert]
  @Id [uniqueidentifier] OUTPUT,
  @LineInputDevice [uniqueidentifier],
  @Type [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LineInputMessageRouting]([Id], [RowVersion], [LineInputDevice], [Type])
          VALUES(@Id, 0, @LineInputDevice, @Type);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LineInputMessageRoutingInsertTrigger]
ON [LineInputMessageRoutingView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [LineInputDevice],
        [Type]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @LineInputDevice [uniqueidentifier]
    DECLARE @Type [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @LineInputDevice,
        @Type
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LineInputMessageRoutingInsert] @Id,@RowVersion,@LineInputDevice,@Type
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @LineInputDevice,
            @Type
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LineInputMessageRoutingDestinationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Routing [uniqueidentifier],
  @Listener [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LineInputMessageRoutingDestination]([Id], [RowVersion], [Routing], [Listener])
          VALUES(@Id, 0, @Routing, @Listener);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LineInputMessageRoutingDestinationInsertTrigger]
ON [LineInputMessageRoutingDestinationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Routing],
        [Listener]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Routing [uniqueidentifier]
    DECLARE @Listener [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Routing,
        @Listener
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LineInputMessageRoutingDestinationInsert] @Id,@RowVersion,@Routing,@Listener
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Routing,
            @Listener
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LineInputWhiteListEntryInsert]
  @Id [uniqueidentifier] OUTPUT,
  @LineInputDevice [uniqueidentifier],
  @HostName [nvarchar](128),
  @Port [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LineInputWhiteListEntry]([Id], [RowVersion], [LineInputDevice], [HostName], [Port])
          VALUES(@Id, 0, @LineInputDevice, @HostName, @Port);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LineInputWhiteListEntryInsertTrigger]
ON [LineInputWhiteListEntryView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [LineInputDevice],
        [HostName],
        [Port]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @LineInputDevice [uniqueidentifier]
    DECLARE @HostName [nvarchar](128)
    DECLARE @Port [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @LineInputDevice,
        @HostName,
        @Port
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LineInputWhiteListEntryInsert] @Id,@RowVersion,@LineInputDevice,@HostName,@Port
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @LineInputDevice,
            @HostName,
            @Port
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LogApplicationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Description [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LogApplication]([Id], [RowVersion], [Name], [Description])
          VALUES(@Id, 0, @Name, @Description);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LogApplicationInsertTrigger]
ON [LogApplicationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Description]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Description
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LogApplicationInsert] @Id,@RowVersion,@Name,@Description
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Description
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LogApplicationConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Application [uniqueidentifier],
  @Timestamp [bigint],
  @Finest [bit],
  @Finer [bit],
  @Fine [bit],
  @Info [bit],
  @Notice [bit],
  @Warn [bit],
  @Error [bit],
  @Severe [bit],
  @Critical [bit],
  @Alert [bit],
  @Fatal [bit],
  @Emergency [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LogApplicationConfiguration]([Id], [RowVersion], [Application], [Timestamp], [Finest], [Finer], [Fine], [Info], [Notice], [Warn], [Error], [Severe], [Critical], [Alert], [Fatal], [Emergency])
          VALUES(@Id, 0, @Application, @Timestamp, @Finest, @Finer, @Fine, @Info, @Notice, @Warn, @Error, @Severe, @Critical, @Alert, @Fatal, @Emergency);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LogApplicationConfigurationInsertTrigger]
ON [LogApplicationConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Application],
        [Timestamp],
        [Finest],
        [Finer],
        [Fine],
        [Info],
        [Notice],
        [Warn],
        [Error],
        [Severe],
        [Critical],
        [Alert],
        [Fatal],
        [Emergency]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Application [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Finest [bit]
    DECLARE @Finer [bit]
    DECLARE @Fine [bit]
    DECLARE @Info [bit]
    DECLARE @Notice [bit]
    DECLARE @Warn [bit]
    DECLARE @Error [bit]
    DECLARE @Severe [bit]
    DECLARE @Critical [bit]
    DECLARE @Alert [bit]
    DECLARE @Fatal [bit]
    DECLARE @Emergency [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Application,
        @Timestamp,
        @Finest,
        @Finer,
        @Fine,
        @Info,
        @Notice,
        @Warn,
        @Error,
        @Severe,
        @Critical,
        @Alert,
        @Fatal,
        @Emergency
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LogApplicationConfigurationInsert] @Id,@RowVersion,@Application,@Timestamp,@Finest,@Finer,@Fine,@Info,@Notice,@Warn,@Error,@Severe,@Critical,@Alert,@Fatal,@Emergency
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Application,
            @Timestamp,
            @Finest,
            @Finer,
            @Fine,
            @Info,
            @Notice,
            @Warn,
            @Error,
            @Severe,
            @Critical,
            @Alert,
            @Fatal,
            @Emergency
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LogHostInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ComputerName [nvarchar](127),
  @Description [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LogHost]([Id], [RowVersion], [ComputerName], [Description])
          VALUES(@Id, 0, @ComputerName, @Description);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LogHostInsertTrigger]
ON [LogHostView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ComputerName],
        [Description]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ComputerName [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ComputerName,
        @Description
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LogHostInsert] @Id,@RowVersion,@ComputerName,@Description
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ComputerName,
            @Description
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LogHostConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Host [uniqueidentifier],
  @Timestamp [bigint],
  @Finest [bit],
  @Finer [bit],
  @Fine [bit],
  @Info [bit],
  @Notice [bit],
  @Warn [bit],
  @Error [bit],
  @Severe [bit],
  @Critical [bit],
  @Alert [bit],
  @Fatal [bit],
  @Emergency [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LogHostConfiguration]([Id], [RowVersion], [Host], [Timestamp], [Finest], [Finer], [Fine], [Info], [Notice], [Warn], [Error], [Severe], [Critical], [Alert], [Fatal], [Emergency])
          VALUES(@Id, 0, @Host, @Timestamp, @Finest, @Finer, @Fine, @Info, @Notice, @Warn, @Error, @Severe, @Critical, @Alert, @Fatal, @Emergency);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LogHostConfigurationInsertTrigger]
ON [LogHostConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Host],
        [Timestamp],
        [Finest],
        [Finer],
        [Fine],
        [Info],
        [Notice],
        [Warn],
        [Error],
        [Severe],
        [Critical],
        [Alert],
        [Fatal],
        [Emergency]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Finest [bit]
    DECLARE @Finer [bit]
    DECLARE @Fine [bit]
    DECLARE @Info [bit]
    DECLARE @Notice [bit]
    DECLARE @Warn [bit]
    DECLARE @Error [bit]
    DECLARE @Severe [bit]
    DECLARE @Critical [bit]
    DECLARE @Alert [bit]
    DECLARE @Fatal [bit]
    DECLARE @Emergency [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Host,
        @Timestamp,
        @Finest,
        @Finer,
        @Fine,
        @Info,
        @Notice,
        @Warn,
        @Error,
        @Severe,
        @Critical,
        @Alert,
        @Fatal,
        @Emergency
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LogHostConfigurationInsert] @Id,@RowVersion,@Host,@Timestamp,@Finest,@Finer,@Fine,@Info,@Notice,@Warn,@Error,@Severe,@Critical,@Alert,@Fatal,@Emergency
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Host,
            @Timestamp,
            @Finest,
            @Finer,
            @Fine,
            @Info,
            @Notice,
            @Warn,
            @Error,
            @Severe,
            @Critical,
            @Alert,
            @Fatal,
            @Emergency
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LogLocationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @FileName [nvarchar](260),
  @LineNumber [int],
  @Namespace [nvarchar](512),
  @ClassName [nvarchar](512),
  @MethodName [nvarchar](255)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LogLocation]([Id], [RowVersion], [FileName], [LineNumber], [Namespace], [ClassName], [MethodName])
          VALUES(@Id, 0, @FileName, @LineNumber, @Namespace, @ClassName, @MethodName);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LogLocationInsertTrigger]
ON [LogLocationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [FileName],
        [LineNumber],
        [Namespace],
        [ClassName],
        [MethodName]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @FileName [nvarchar](260)
    DECLARE @LineNumber [int]
    DECLARE @Namespace [nvarchar](512)
    DECLARE @ClassName [nvarchar](512)
    DECLARE @MethodName [nvarchar](255)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @FileName,
        @LineNumber,
        @Namespace,
        @ClassName,
        @MethodName
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LogLocationInsert] @Id,@RowVersion,@FileName,@LineNumber,@Namespace,@ClassName,@MethodName
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @FileName,
            @LineNumber,
            @Namespace,
            @ClassName,
            @MethodName
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LogProcessInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Application [uniqueidentifier],
  @Host [uniqueidentifier],
  @Started [bigint],
  @Stopped [bigint],
  @ProcessId [bigint],
  @Path [nvarchar](max),
  @Identity [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LogProcess]([Id], [RowVersion], [Application], [Host], [Started], [Stopped], [ProcessId], [Path], [Identity])
          VALUES(@Id, 0, @Application, @Host, @Started, @Stopped, @ProcessId, @Path, @Identity);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LogProcessInsertTrigger]
ON [LogProcessView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Application],
        [Host],
        [Started],
        [Stopped],
        [ProcessId],
        [Path],
        [Identity]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Application [uniqueidentifier]
    DECLARE @Host [uniqueidentifier]
    DECLARE @Started [bigint]
    DECLARE @Stopped [bigint]
    DECLARE @ProcessId [bigint]
    DECLARE @Path [nvarchar](max)
    DECLARE @Identity [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Application,
        @Host,
        @Started,
        @Stopped,
        @ProcessId,
        @Path,
        @Identity
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LogProcessInsert] @Id,@RowVersion,@Application,@Host,@Started,@Stopped,@ProcessId,@Path,@Identity
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Application,
            @Host,
            @Started,
            @Stopped,
            @ProcessId,
            @Path,
            @Identity
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LogRecordInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Thread [uniqueidentifier],
  @SequenceNumber [bigint],
  @Level [int],
  @Timestamp [bigint],
  @Depth [int],
  @Location [uniqueidentifier],
  @Message [nvarchar](2000),
  @ExceptionString [nvarchar](max),
  @PropertiesData [varbinary](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LogRecord]([Id], [RowVersion], [Thread], [SequenceNumber], [Level], [Timestamp], [Depth], [Location], [Message], [ExceptionString], [PropertiesData])
          VALUES(@Id, 0, @Thread, @SequenceNumber, @Level, @Timestamp, @Depth, @Location, @Message, @ExceptionString, @PropertiesData);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LogRecordInsertTrigger]
ON [LogRecordView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Thread],
        [SequenceNumber],
        [Level],
        [Timestamp],
        [Depth],
        [Location],
        [Message],
        [ExceptionString],
        [PropertiesData]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Thread [uniqueidentifier]
    DECLARE @SequenceNumber [bigint]
    DECLARE @Level [int]
    DECLARE @Timestamp [bigint]
    DECLARE @Depth [int]
    DECLARE @Location [uniqueidentifier]
    DECLARE @Message [nvarchar](2000)
    DECLARE @ExceptionString [nvarchar](max)
    DECLARE @PropertiesData [varbinary](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Thread,
        @SequenceNumber,
        @Level,
        @Timestamp,
        @Depth,
        @Location,
        @Message,
        @ExceptionString,
        @PropertiesData
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LogRecordInsert] @Id,@RowVersion,@Thread,@SequenceNumber,@Level,@Timestamp,@Depth,@Location,@Message,@ExceptionString,@PropertiesData
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Thread,
            @SequenceNumber,
            @Level,
            @Timestamp,
            @Depth,
            @Location,
            @Message,
            @ExceptionString,
            @PropertiesData
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LogThreadInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Process [uniqueidentifier],
  @Started [bigint],
  @Stopped [bigint],
  @ThreadId [bigint],
  @Name [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LogThread]([Id], [RowVersion], [Process], [Started], [Stopped], [ThreadId], [Name])
          VALUES(@Id, 0, @Process, @Started, @Stopped, @ThreadId, @Name);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LogThreadInsertTrigger]
ON [LogThreadView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Process],
        [Started],
        [Stopped],
        [ThreadId],
        [Name]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Process [uniqueidentifier]
    DECLARE @Started [bigint]
    DECLARE @Stopped [bigint]
    DECLARE @ThreadId [bigint]
    DECLARE @Name [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Process,
        @Started,
        @Stopped,
        @ThreadId,
        @Name
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LogThreadInsert] @Id,@RowVersion,@Process,@Started,@Stopped,@ThreadId,@Name
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Process,
            @Started,
            @Stopped,
            @ThreadId,
            @Name
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [LogTraceEntryInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Thread [uniqueidentifier],
  @SequenceNumber [bigint],
  @Location [uniqueidentifier],
  @Depth [int],
  @Entered [bigint],
  @Ended [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [LogTraceEntry]([Id], [RowVersion], [Thread], [SequenceNumber], [Location], [Depth], [Entered], [Ended])
          VALUES(@Id, 0, @Thread, @SequenceNumber, @Location, @Depth, @Entered, @Ended);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [LogTraceEntryInsertTrigger]
ON [LogTraceEntryView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Thread],
        [SequenceNumber],
        [Location],
        [Depth],
        [Entered],
        [Ended]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Thread [uniqueidentifier]
    DECLARE @SequenceNumber [bigint]
    DECLARE @Location [uniqueidentifier]
    DECLARE @Depth [int]
    DECLARE @Entered [bigint]
    DECLARE @Ended [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Thread,
        @SequenceNumber,
        @Location,
        @Depth,
        @Entered,
        @Ended
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [LogTraceEntryInsert] @Id,@RowVersion,@Thread,@SequenceNumber,@Location,@Depth,@Entered,@Ended
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Thread,
            @SequenceNumber,
            @Location,
            @Depth,
            @Entered,
            @Ended
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MapElementInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Item [uniqueidentifier],
  @ElementType [int],
  @Latitude [float](53),
  @Longitude [float](53),
  @Angle [float](53),
  @Left [float](53),
  @Top [float](53),
  @Width [float](53),
  @Height [float](53),
  @Label [nvarchar](127),
  @Data [varbinary](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [MapElement]([Id], [RowVersion], [Item], [ElementType], [Latitude], [Longitude], [Angle], [Left], [Top], [Width], [Height], [Label], [Data])
          VALUES(@Id, 0, @Item, @ElementType, @Latitude, @Longitude, @Angle, @Left, @Top, @Width, @Height, @Label, @Data);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MapElementInsertTrigger]
ON [MapElementView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Item],
        [ElementType],
        [Latitude],
        [Longitude],
        [Angle],
        [Left],
        [Top],
        [Width],
        [Height],
        [Label],
        [Data]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Item [uniqueidentifier]
    DECLARE @ElementType [int]
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @Angle [float](53)
    DECLARE @Left [float](53)
    DECLARE @Top [float](53)
    DECLARE @Width [float](53)
    DECLARE @Height [float](53)
    DECLARE @Label [nvarchar](127)
    DECLARE @Data [varbinary](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Item,
        @ElementType,
        @Latitude,
        @Longitude,
        @Angle,
        @Left,
        @Top,
        @Width,
        @Height,
        @Label,
        @Data
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MapElementInsert] @Id,@RowVersion,@Item,@ElementType,@Latitude,@Longitude,@Angle,@Left,@Top,@Width,@Height,@Label,@Data
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Item,
            @ElementType,
            @Latitude,
            @Longitude,
            @Angle,
            @Left,
            @Top,
            @Width,
            @Height,
            @Label,
            @Data
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MapInfoInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Scale [int],
  @Latitude [float](53),
  @Longitude [float](53),
  @NorthWestLatitude [float](53),
  @NorthWestLongitude [float](53),
  @SouthEastLatitude [float](53),
  @SouthEastLongitude [float](53),
  @Image [varbinary](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [MapInfo]([Id], [RowVersion], [Scale], [Latitude], [Longitude], [NorthWestLatitude], [NorthWestLongitude], [SouthEastLatitude], [SouthEastLongitude], [Image])
          VALUES(@Id, 0, @Scale, @Latitude, @Longitude, @NorthWestLatitude, @NorthWestLongitude, @SouthEastLatitude, @SouthEastLongitude, @Image);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MapInfoInsertTrigger]
ON [MapInfoView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Scale],
        [Latitude],
        [Longitude],
        [NorthWestLatitude],
        [NorthWestLongitude],
        [SouthEastLatitude],
        [SouthEastLongitude],
        [Image]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Scale [int]
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @NorthWestLatitude [float](53)
    DECLARE @NorthWestLongitude [float](53)
    DECLARE @SouthEastLatitude [float](53)
    DECLARE @SouthEastLongitude [float](53)
    DECLARE @Image [varbinary](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Scale,
        @Latitude,
        @Longitude,
        @NorthWestLatitude,
        @NorthWestLongitude,
        @SouthEastLatitude,
        @SouthEastLongitude,
        @Image
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MapInfoInsert] @Id,@RowVersion,@Scale,@Latitude,@Longitude,@NorthWestLatitude,@NorthWestLongitude,@SouthEastLatitude,@SouthEastLongitude,@Image
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Scale,
            @Latitude,
            @Longitude,
            @NorthWestLatitude,
            @NorthWestLongitude,
            @SouthEastLatitude,
            @SouthEastLongitude,
            @Image
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MapServiceOptionsInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timestamp [bigint],
  @IpAddress [nvarchar](127),
  @Port [int],
  @ImageScaleFactorX [float](53),
  @ImageOffsetX [float](53),
  @ImageScaleFactorY [float](53),
  @ImageOffsetY [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [MapServiceOptions]([Id], [RowVersion], [Timestamp], [IpAddress], [Port], [ImageScaleFactorX], [ImageOffsetX], [ImageScaleFactorY], [ImageOffsetY])
          VALUES(@Id, 0, @Timestamp, @IpAddress, @Port, @ImageScaleFactorX, @ImageOffsetX, @ImageScaleFactorY, @ImageOffsetY);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MapServiceOptionsInsertTrigger]
ON [MapServiceOptionsView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timestamp],
        [IpAddress],
        [Port],
        [ImageScaleFactorX],
        [ImageOffsetX],
        [ImageScaleFactorY],
        [ImageOffsetY]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timestamp [bigint]
    DECLARE @IpAddress [nvarchar](127)
    DECLARE @Port [int]
    DECLARE @ImageScaleFactorX [float](53)
    DECLARE @ImageOffsetX [float](53)
    DECLARE @ImageScaleFactorY [float](53)
    DECLARE @ImageOffsetY [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timestamp,
        @IpAddress,
        @Port,
        @ImageScaleFactorX,
        @ImageOffsetX,
        @ImageScaleFactorY,
        @ImageOffsetY
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MapServiceOptionsInsert] @Id,@RowVersion,@Timestamp,@IpAddress,@Port,@ImageScaleFactorX,@ImageOffsetX,@ImageScaleFactorY,@ImageOffsetY
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timestamp,
            @IpAddress,
            @Port,
            @ImageScaleFactorX,
            @ImageOffsetX,
            @ImageScaleFactorY,
            @ImageOffsetY
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MaritimeIdentificationDigitsInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Code [int],
  @Country [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [MaritimeIdentificationDigits]([Id], [RowVersion], [Code], [Country])
          VALUES(@Id, 0, @Code, @Country);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MaritimeIdentificationDigitsInsertTrigger]
ON [MaritimeIdentificationDigitsView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Code],
        [Country]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Code [int]
    DECLARE @Country [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Code,
        @Country
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MaritimeIdentificationDigitsInsert] @Id,@RowVersion,@Code,@Country
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Code,
            @Country
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MediaProxySessionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Service [uniqueidentifier],
  @Name [nvarchar](128),
  @EnabledTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [MediaProxySession]([Id], [RowVersion], [Service], [Name], [EnabledTimeseries])
          VALUES(@Id, 0, @Service, @Name, @EnabledTimeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MediaProxySessionInsertTrigger]
ON [MediaProxySessionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Service],
        [Name],
        [EnabledTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Service [uniqueidentifier]
    DECLARE @Name [nvarchar](128)
    DECLARE @EnabledTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Service,
        @Name,
        @EnabledTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MediaProxySessionInsert] @Id,@RowVersion,@Service,@Name,@EnabledTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Service,
            @Name,
            @EnabledTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MediaProxySessionFileInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ProxySession [uniqueidentifier],
  @Timestamp [bigint],
  @StreamName [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [MediaProxySessionFile]([Id], [RowVersion], [ProxySession], [Timestamp], [StreamName])
          VALUES(@Id, 0, @ProxySession, @Timestamp, @StreamName);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MediaProxySessionFileInsertTrigger]
ON [MediaProxySessionFileView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ProxySession],
        [Timestamp],
        [StreamName]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ProxySession [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @StreamName [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ProxySession,
        @Timestamp,
        @StreamName
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MediaProxySessionFileInsert] @Id,@RowVersion,@ProxySession,@Timestamp,@StreamName
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ProxySession,
            @Timestamp,
            @StreamName
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MediaProxySessionOptionsInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ProxySession [uniqueidentifier],
  @Timestamp [bigint],
  @SourceStreamUrl [nvarchar](255),
  @StreamName [nvarchar](255),
  @Mode [int],
  @TunnelOverHTTPPortNumber [int],
  @Username [nvarchar](128),
  @Password [nvarchar](128),
  @RecorderPortNumber [int],
  @SessionType [int],
  @MaxFileTime [bigint],
  @MaxFileRetention [bigint],
  @VideoDirectory [nvarchar](260)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [MediaProxySessionOptions]([Id], [RowVersion], [ProxySession], [Timestamp], [SourceStreamUrl], [StreamName], [Mode], [TunnelOverHTTPPortNumber], [Username], [Password], [RecorderPortNumber], [SessionType], [MaxFileTime], [MaxFileRetention], [VideoDirectory])
          VALUES(@Id, 0, @ProxySession, @Timestamp, @SourceStreamUrl, @StreamName, @Mode, @TunnelOverHTTPPortNumber, @Username, @Password, @RecorderPortNumber, @SessionType, @MaxFileTime, @MaxFileRetention, @VideoDirectory);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MediaProxySessionOptionsInsertTrigger]
ON [MediaProxySessionOptionsView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ProxySession],
        [Timestamp],
        [SourceStreamUrl],
        [StreamName],
        [Mode],
        [TunnelOverHTTPPortNumber],
        [Username],
        [Password],
        [RecorderPortNumber],
        [SessionType],
        [MaxFileTime],
        [MaxFileRetention],
        [VideoDirectory]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ProxySession [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @SourceStreamUrl [nvarchar](255)
    DECLARE @StreamName [nvarchar](255)
    DECLARE @Mode [int]
    DECLARE @TunnelOverHTTPPortNumber [int]
    DECLARE @Username [nvarchar](128)
    DECLARE @Password [nvarchar](128)
    DECLARE @RecorderPortNumber [int]
    DECLARE @SessionType [int]
    DECLARE @MaxFileTime [bigint]
    DECLARE @MaxFileRetention [bigint]
    DECLARE @VideoDirectory [nvarchar](260)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ProxySession,
        @Timestamp,
        @SourceStreamUrl,
        @StreamName,
        @Mode,
        @TunnelOverHTTPPortNumber,
        @Username,
        @Password,
        @RecorderPortNumber,
        @SessionType,
        @MaxFileTime,
        @MaxFileRetention,
        @VideoDirectory
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MediaProxySessionOptionsInsert] @Id,@RowVersion,@ProxySession,@Timestamp,@SourceStreamUrl,@StreamName,@Mode,@TunnelOverHTTPPortNumber,@Username,@Password,@RecorderPortNumber,@SessionType,@MaxFileTime,@MaxFileRetention,@VideoDirectory
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ProxySession,
            @Timestamp,
            @SourceStreamUrl,
            @StreamName,
            @Mode,
            @TunnelOverHTTPPortNumber,
            @Username,
            @Password,
            @RecorderPortNumber,
            @SessionType,
            @MaxFileTime,
            @MaxFileRetention,
            @VideoDirectory
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MediaServiceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @EnabledTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [MediaService]([Id], [RowVersion], [EnabledTimeseries])
          VALUES(@Id, 0, @EnabledTimeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MediaServiceInsertTrigger]
ON [MediaServiceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [EnabledTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @EnabledTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @EnabledTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MediaServiceInsert] @Id,@RowVersion,@EnabledTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @EnabledTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MediaServiceOptionsInsert]
  @Id [uniqueidentifier] OUTPUT,
  @MediaService [uniqueidentifier],
  @Timestamp [bigint],
  @RtspPortNumber [int],
  @HttpPortNumber [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [MediaServiceOptions]([Id], [RowVersion], [MediaService], [Timestamp], [RtspPortNumber], [HttpPortNumber])
          VALUES(@Id, 0, @MediaService, @Timestamp, @RtspPortNumber, @HttpPortNumber);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MediaServiceOptionsInsertTrigger]
ON [MediaServiceOptionsView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [MediaService],
        [Timestamp],
        [RtspPortNumber],
        [HttpPortNumber]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @MediaService [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @RtspPortNumber [int]
    DECLARE @HttpPortNumber [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @MediaService,
        @Timestamp,
        @RtspPortNumber,
        @HttpPortNumber
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MediaServiceOptionsInsert] @Id,@RowVersion,@MediaService,@Timestamp,@RtspPortNumber,@HttpPortNumber
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @MediaService,
            @Timestamp,
            @RtspPortNumber,
            @HttpPortNumber
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ElementTypeInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Namespace [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 23500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [NamespaceElement]([Id], [EntityType], [RowVersion], [Namespace], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @Namespace, @Name, @Description);
      INSERT INTO [ElementType]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ElementTypeInsertTrigger]
ON [ElementTypeView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Namespace],
        [Name],
        [Description]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Namespace [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Namespace,
        @Name,
        @Description
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ElementTypeInsert] @Id,@RowVersion,@Namespace,@Name,@Description
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Namespace,
            @Name,
            @Description
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [NamespaceInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Namespace [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 23600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [NamespaceElement]([Id], [EntityType], [RowVersion], [Namespace], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @Namespace, @Name, @Description);
      INSERT INTO [Namespace]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [NamespaceInsertTrigger]
ON [NamespaceView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Namespace],
        [Name],
        [Description]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Namespace [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Namespace,
        @Name,
        @Description
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [NamespaceInsert] @Id,@RowVersion,@Namespace,@Name,@Description
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Namespace,
            @Name,
            @Description
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [OilSpillInsert]
  @Id [uniqueidentifier] OUTPUT,
  @OilSpillDetector [uniqueidentifier],
  @Timestamp [bigint],
  @OilArea [float](53),
  @Shape [varbinary](max),
  @BSI [varbinary](max),
  @Oil [varbinary](max),
  @Trace [varbinary](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [OilSpill]([Id], [RowVersion], [OilSpillDetector], [Timestamp], [OilArea], [Shape], [BSI], [Oil], [Trace])
          VALUES(@Id, 0, @OilSpillDetector, @Timestamp, @OilArea, @Shape, @BSI, @Oil, @Trace);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [OilSpillInsertTrigger]
ON [OilSpillView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [OilSpillDetector],
        [Timestamp],
        [OilArea],
        [Shape],
        [BSI],
        [Oil],
        [Trace]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @OilSpillDetector [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @OilArea [float](53)
    DECLARE @Shape [varbinary](max)
    DECLARE @BSI [varbinary](max)
    DECLARE @Oil [varbinary](max)
    DECLARE @Trace [varbinary](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @OilSpillDetector,
        @Timestamp,
        @OilArea,
        @Shape,
        @BSI,
        @Oil,
        @Trace
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [OilSpillInsert] @Id,@RowVersion,@OilSpillDetector,@Timestamp,@OilArea,@Shape,@BSI,@Oil,@Trace
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @OilSpillDetector,
            @Timestamp,
            @OilArea,
            @Shape,
            @BSI,
            @Oil,
            @Trace
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [OilSpillDetectorCommandInsert]
  @Id [uniqueidentifier] OUTPUT,
  @OilSpillDetector [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [OilSpillDetectorCommand]([Id], [RowVersion], [OilSpillDetector], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, 0, @OilSpillDetector, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [OilSpillDetectorCommandInsertTrigger]
ON [OilSpillDetectorCommandView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [OilSpillDetector],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @OilSpillDetector [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @OilSpillDetector,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [OilSpillDetectorCommandInsert] @Id,@RowVersion,@OilSpillDetector,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @OilSpillDetector,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [OilSpillDetectorCommandReplyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @OilSpillDetector [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [OilSpillDetectorCommandReply]([Id], [RowVersion], [OilSpillDetector], [Timestamp], [Command], [Status], [Message])
          VALUES(@Id, 0, @OilSpillDetector, @Timestamp, @Command, @Status, @Message);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [OilSpillDetectorCommandReplyInsertTrigger]
ON [OilSpillDetectorCommandReplyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [OilSpillDetector],
        [Timestamp],
        [Command],
        [Status],
        [Message]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @OilSpillDetector [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @OilSpillDetector,
        @Timestamp,
        @Command,
        @Status,
        @Message
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [OilSpillDetectorCommandReplyInsert] @Id,@RowVersion,@OilSpillDetector,@Timestamp,@Command,@Status,@Message
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @OilSpillDetector,
            @Timestamp,
            @Command,
            @Status,
            @Message
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [OilSpillDetectorConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @OilSpillDetector [uniqueidentifier],
  @Timestamp [bigint],
  @Range [float](53),
  @StartAngle [float](53),
  @EndAngle [float](53),
  @StartRange [float](53),
  @EndRange [float](53),
  @UpdateRate [int],
  @StatusSendTime [bigint],
  @DrawBorder [bit],
  @Colors [varbinary](max),
  @SendToServer [bit],
  @Directory [nvarchar](260),
  @TransparentWater [bit],
  @SavePictures [bit],
  @SendAsTarget [bit],
  @WriteLog [bit],
  @TargetFilePrefix [nvarchar](127),
  @TargetMMSI [uniqueidentifier],
  @Latitude [float](53),
  @Longitude [float](53),
  @TestSourceEnabled [bit],
  @ProxyServer [nvarchar](127),
  @UseProxyServer [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [OilSpillDetectorConfiguration]([Id], [RowVersion], [OilSpillDetector], [Timestamp], [Range], [StartAngle], [EndAngle], [StartRange], [EndRange], [UpdateRate], [StatusSendTime], [DrawBorder], [Colors], [SendToServer], [Directory], [TransparentWater], [SavePictures], [SendAsTarget], [WriteLog], [TargetFilePrefix], [TargetMMSI], [Latitude], [Longitude], [TestSourceEnabled], [ProxyServer], [UseProxyServer])
          VALUES(@Id, 0, @OilSpillDetector, @Timestamp, @Range, @StartAngle, @EndAngle, @StartRange, @EndRange, @UpdateRate, @StatusSendTime, @DrawBorder, @Colors, @SendToServer, @Directory, @TransparentWater, @SavePictures, @SendAsTarget, @WriteLog, @TargetFilePrefix, @TargetMMSI, @Latitude, @Longitude, @TestSourceEnabled, @ProxyServer, @UseProxyServer);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [OilSpillDetectorConfigurationInsertTrigger]
ON [OilSpillDetectorConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [OilSpillDetector],
        [Timestamp],
        [Range],
        [StartAngle],
        [EndAngle],
        [StartRange],
        [EndRange],
        [UpdateRate],
        [StatusSendTime],
        [DrawBorder],
        [Colors],
        [SendToServer],
        [Directory],
        [TransparentWater],
        [SavePictures],
        [SendAsTarget],
        [WriteLog],
        [TargetFilePrefix],
        [TargetMMSI],
        [Latitude],
        [Longitude],
        [TestSourceEnabled],
        [ProxyServer],
        [UseProxyServer]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @OilSpillDetector [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Range [float](53)
    DECLARE @StartAngle [float](53)
    DECLARE @EndAngle [float](53)
    DECLARE @StartRange [float](53)
    DECLARE @EndRange [float](53)
    DECLARE @UpdateRate [int]
    DECLARE @StatusSendTime [bigint]
    DECLARE @DrawBorder [bit]
    DECLARE @Colors [varbinary](max)
    DECLARE @SendToServer [bit]
    DECLARE @Directory [nvarchar](260)
    DECLARE @TransparentWater [bit]
    DECLARE @SavePictures [bit]
    DECLARE @SendAsTarget [bit]
    DECLARE @WriteLog [bit]
    DECLARE @TargetFilePrefix [nvarchar](127)
    DECLARE @TargetMMSI [uniqueidentifier]
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @TestSourceEnabled [bit]
    DECLARE @ProxyServer [nvarchar](127)
    DECLARE @UseProxyServer [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @OilSpillDetector,
        @Timestamp,
        @Range,
        @StartAngle,
        @EndAngle,
        @StartRange,
        @EndRange,
        @UpdateRate,
        @StatusSendTime,
        @DrawBorder,
        @Colors,
        @SendToServer,
        @Directory,
        @TransparentWater,
        @SavePictures,
        @SendAsTarget,
        @WriteLog,
        @TargetFilePrefix,
        @TargetMMSI,
        @Latitude,
        @Longitude,
        @TestSourceEnabled,
        @ProxyServer,
        @UseProxyServer
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [OilSpillDetectorConfigurationInsert] @Id,@RowVersion,@OilSpillDetector,@Timestamp,@Range,@StartAngle,@EndAngle,@StartRange,@EndRange,@UpdateRate,@StatusSendTime,@DrawBorder,@Colors,@SendToServer,@Directory,@TransparentWater,@SavePictures,@SendAsTarget,@WriteLog,@TargetFilePrefix,@TargetMMSI,@Latitude,@Longitude,@TestSourceEnabled,@ProxyServer,@UseProxyServer
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @OilSpillDetector,
            @Timestamp,
            @Range,
            @StartAngle,
            @EndAngle,
            @StartRange,
            @EndRange,
            @UpdateRate,
            @StatusSendTime,
            @DrawBorder,
            @Colors,
            @SendToServer,
            @Directory,
            @TransparentWater,
            @SavePictures,
            @SendAsTarget,
            @WriteLog,
            @TargetFilePrefix,
            @TargetMMSI,
            @Latitude,
            @Longitude,
            @TestSourceEnabled,
            @ProxyServer,
            @UseProxyServer
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Position2DTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @X [float](53),
  @Y [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Position2DTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [X], [Y])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @X, @Y);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Position2DTimeseriesValueInsertTrigger]
ON [Position2DTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [X],
        [Y]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @X [float](53)
    DECLARE @Y [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @X,
        @Y
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Position2DTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@X,@Y
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @X,
            @Y
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Position3DTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @X [float](53),
  @Y [float](53),
  @Z [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Position3DTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [X], [Y], [Z])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @X, @Y, @Z);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Position3DTimeseriesValueInsertTrigger]
ON [Position3DTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [X],
        [Y],
        [Z]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @X [float](53)
    DECLARE @Y [float](53)
    DECLARE @Z [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @X,
        @Y,
        @Z
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Position3DTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@X,@Y,@Z
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @X,
            @Y,
            @Z
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ProcessTrackValueResultInsert]
  @Id [uniqueidentifier] OUTPUT,
  @CreatedNewTrack [bit],
  @TrackId [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [ProcessTrackValueResult]([Id], [RowVersion], [CreatedNewTrack], [TrackId])
          VALUES(@Id, 0, @CreatedNewTrack, @TrackId);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ProcessTrackValueResultInsertTrigger]
ON [ProcessTrackValueResultView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [CreatedNewTrack],
        [TrackId]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @CreatedNewTrack [bit]
    DECLARE @TrackId [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @CreatedNewTrack,
        @TrackId
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ProcessTrackValueResultInsert] @Id,@RowVersion,@CreatedNewTrack,@TrackId
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @CreatedNewTrack,
            @TrackId
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BinaryPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [varbinary](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 24500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [BinaryProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BinaryPropertyInsertTrigger]
ON [BinaryPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [varbinary](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BinaryPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BooleanPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 24600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [BooleanProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BooleanPropertyInsertTrigger]
ON [BooleanPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BooleanPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BytePropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [tinyint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 24700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [ByteProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BytePropertyInsertTrigger]
ON [BytePropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [tinyint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BytePropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DateTimePropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 24800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [DateTimeProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DateTimePropertyInsertTrigger]
ON [DateTimePropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DateTimePropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DoublePropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 24900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [DoubleProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DoublePropertyInsertTrigger]
ON [DoublePropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DoublePropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GuidPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 25000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [GuidProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GuidPropertyInsertTrigger]
ON [GuidPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GuidPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int16PropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [smallint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 25100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [Int16Property]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int16PropertyInsertTrigger]
ON [Int16PropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [smallint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int16PropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int32PropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 25200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [Int32Property]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int32PropertyInsertTrigger]
ON [Int32PropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int32PropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int64PropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 25300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [Int64Property]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int64PropertyInsertTrigger]
ON [Int64PropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int64PropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ReferencePropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 25400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [ReferenceProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ReferencePropertyInsertTrigger]
ON [ReferencePropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ReferencePropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SBytePropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [numeric](3,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 25500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [SByteProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SBytePropertyInsertTrigger]
ON [SBytePropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [numeric](3,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SBytePropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SinglePropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [float](24)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 25600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [SingleProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SinglePropertyInsertTrigger]
ON [SinglePropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [float](24)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SinglePropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [StringPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 25700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [StringProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [StringPropertyInsertTrigger]
ON [StringPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [StringPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BinaryTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 25900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [BinaryTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BinaryTimeseriesPropertyInsertTrigger]
ON [BinaryTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BinaryTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BooleanTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 26000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [BooleanTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BooleanTimeseriesPropertyInsertTrigger]
ON [BooleanTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BooleanTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ByteTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 26100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [ByteTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ByteTimeseriesPropertyInsertTrigger]
ON [ByteTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ByteTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 26200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [DateTimeTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DateTimeTimeseriesPropertyInsertTrigger]
ON [DateTimeTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DateTimeTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DoubleTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 26300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [DoubleTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DoubleTimeseriesPropertyInsertTrigger]
ON [DoubleTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DoubleTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GuidTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 26400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [GuidTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GuidTimeseriesPropertyInsertTrigger]
ON [GuidTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GuidTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int16TimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 26500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [Int16TimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int16TimeseriesPropertyInsertTrigger]
ON [Int16TimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int16TimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int32TimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 26600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [Int32TimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int32TimeseriesPropertyInsertTrigger]
ON [Int32TimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int32TimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int64TimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 26700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [Int64TimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int64TimeseriesPropertyInsertTrigger]
ON [Int64TimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int64TimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 26800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [ReferenceTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ReferenceTimeseriesPropertyInsertTrigger]
ON [ReferenceTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ReferenceTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SByteTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 26900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [SByteTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SByteTimeseriesPropertyInsertTrigger]
ON [SByteTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SByteTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SingleTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 27000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [SingleTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SingleTimeseriesPropertyInsertTrigger]
ON [SingleTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SingleTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [StringTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 27100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [StringTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [StringTimeseriesPropertyInsertTrigger]
ON [StringTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [StringTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 27200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [TimeSpanTimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TimeSpanTimeseriesPropertyInsertTrigger]
ON [TimeSpanTimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TimeSpanTimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt16TimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 27300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [UInt16TimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt16TimeseriesPropertyInsertTrigger]
ON [UInt16TimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt16TimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt32TimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 27400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [UInt32TimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt32TimeseriesPropertyInsertTrigger]
ON [UInt32TimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt32TimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt64TimeseriesPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 27500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeseriesProperty]([Id])
          VALUES(@Id);
      INSERT INTO [UInt64TimeseriesProperty]([Id], [Timeseries])
          VALUES(@Id, @Timeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt64TimeseriesPropertyInsertTrigger]
ON [UInt64TimeseriesPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Timeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Timeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Timeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt64TimeseriesPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Timeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Timeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TimeSpanPropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 27600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [TimeSpanProperty]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TimeSpanPropertyInsertTrigger]
ON [TimeSpanPropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TimeSpanPropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt16PropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [numeric](5,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 27700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [UInt16Property]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt16PropertyInsertTrigger]
ON [UInt16PropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [numeric](5,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt16PropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt32PropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [numeric](10,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 27800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [UInt32Property]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt32PropertyInsertTrigger]
ON [UInt32PropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [numeric](10,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt32PropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt64PropertyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 27900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Property]([Id], [EntityType], [RowVersion], [Element], [Definition])
          VALUES(@Id, @EntityType, 0, @Element, @Definition);
      INSERT INTO [UInt64Property]([Id], [Value])
          VALUES(@Id, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt64PropertyInsertTrigger]
ON [UInt64PropertyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Element],
        [Definition],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Element [uniqueidentifier]
    DECLARE @Definition [uniqueidentifier]
    DECLARE @Value [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Element,
        @Definition,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt64PropertyInsert] @Id,@RowVersion,@Element,@Definition,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Element,
            @Definition,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BinaryPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [varbinary](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 28100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [BinaryPropertyDefinition]([Id], [DefaultValue])
          VALUES(@Id, @DefaultValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BinaryPropertyDefinitionInsertTrigger]
ON [BinaryPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [varbinary](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BinaryPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BooleanPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 28200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [BooleanPropertyDefinition]([Id], [DefaultValue])
          VALUES(@Id, @DefaultValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BooleanPropertyDefinitionInsertTrigger]
ON [BooleanPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BooleanPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BytePropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [tinyint],
  @MinValue [tinyint],
  @MaxValue [tinyint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 28300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [BytePropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BytePropertyDefinitionInsertTrigger]
ON [BytePropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [tinyint]
    DECLARE @MinValue [tinyint]
    DECLARE @MaxValue [tinyint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BytePropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DateTimePropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [nvarchar](127),
  @MinValue [nvarchar](127),
  @MaxValue [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 28400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [DateTimePropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DateTimePropertyDefinitionInsertTrigger]
ON [DateTimePropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [nvarchar](127)
    DECLARE @MinValue [nvarchar](127)
    DECLARE @MaxValue [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DateTimePropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DoublePropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [float](53),
  @MinValue [float](53),
  @MaxValue [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 28500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [DoublePropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DoublePropertyDefinitionInsertTrigger]
ON [DoublePropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [float](53)
    DECLARE @MinValue [float](53)
    DECLARE @MaxValue [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DoublePropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GuidPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 28600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [GuidPropertyDefinition]([Id], [DefaultValue])
          VALUES(@Id, @DefaultValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GuidPropertyDefinitionInsertTrigger]
ON [GuidPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GuidPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int16PropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [smallint],
  @MinValue [smallint],
  @MaxValue [smallint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 28700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [Int16PropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int16PropertyDefinitionInsertTrigger]
ON [Int16PropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [smallint]
    DECLARE @MinValue [smallint]
    DECLARE @MaxValue [smallint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int16PropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int32PropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [int],
  @MinValue [int],
  @MaxValue [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 28800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [Int32PropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int32PropertyDefinitionInsertTrigger]
ON [Int32PropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [int]
    DECLARE @MinValue [int]
    DECLARE @MaxValue [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int32PropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int64PropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [bigint],
  @MinValue [bigint],
  @MaxValue [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 28900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [Int64PropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int64PropertyDefinitionInsertTrigger]
ON [Int64PropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [bigint]
    DECLARE @MinValue [bigint]
    DECLARE @MaxValue [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int64PropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ReferencePropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [uniqueidentifier],
  @ReferencedElementType [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 29000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [ReferencePropertyDefinition]([Id], [DefaultValue], [ReferencedElementType])
          VALUES(@Id, @DefaultValue, @ReferencedElementType);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ReferencePropertyDefinitionInsertTrigger]
ON [ReferencePropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [ReferencedElementType]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [uniqueidentifier]
    DECLARE @ReferencedElementType [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @ReferencedElementType
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ReferencePropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@ReferencedElementType
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @ReferencedElementType
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SBytePropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [numeric](3,0),
  @MinValue [numeric](3,0),
  @MaxValue [numeric](3,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 29100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [SBytePropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SBytePropertyDefinitionInsertTrigger]
ON [SBytePropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [numeric](3,0)
    DECLARE @MinValue [numeric](3,0)
    DECLARE @MaxValue [numeric](3,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SBytePropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SinglePropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [float](24),
  @MinValue [float](24),
  @MaxValue [float](24)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 29200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [SinglePropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SinglePropertyDefinitionInsertTrigger]
ON [SinglePropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [float](24)
    DECLARE @MinValue [float](24)
    DECLARE @MaxValue [float](24)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SinglePropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [StringPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [nvarchar](127),
  @Pattern [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 29300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [StringPropertyDefinition]([Id], [DefaultValue], [Pattern])
          VALUES(@Id, @DefaultValue, @Pattern);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [StringPropertyDefinitionInsertTrigger]
ON [StringPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [Pattern]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [nvarchar](127)
    DECLARE @Pattern [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @Pattern
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [StringPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@Pattern
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @Pattern
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BinaryTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 29500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [BinaryTimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BinaryTimeseriesPropertyDefinitionInsertTrigger]
ON [BinaryTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BinaryTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BooleanTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 29600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [BooleanTimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BooleanTimeseriesPropertyDefinitionInsertTrigger]
ON [BooleanTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BooleanTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ByteTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [tinyint],
  @MaxValue [tinyint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 29700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [ByteTimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ByteTimeseriesPropertyDefinitionInsertTrigger]
ON [ByteTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [tinyint]
    DECLARE @MaxValue [tinyint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ByteTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [nvarchar](127),
  @MaxValue [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 29800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [DateTimeTimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DateTimeTimeseriesPropertyDefinitionInsertTrigger]
ON [DateTimeTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [nvarchar](127)
    DECLARE @MaxValue [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DateTimeTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DoubleTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [float](53),
  @MaxValue [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 29900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [DoubleTimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DoubleTimeseriesPropertyDefinitionInsertTrigger]
ON [DoubleTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [float](53)
    DECLARE @MaxValue [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DoubleTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GuidTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 30000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [GuidTimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GuidTimeseriesPropertyDefinitionInsertTrigger]
ON [GuidTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GuidTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int16TimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [smallint],
  @MaxValue [smallint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 30100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [Int16TimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int16TimeseriesPropertyDefinitionInsertTrigger]
ON [Int16TimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [smallint]
    DECLARE @MaxValue [smallint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int16TimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int32TimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [int],
  @MaxValue [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 30200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [Int32TimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int32TimeseriesPropertyDefinitionInsertTrigger]
ON [Int32TimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [int]
    DECLARE @MaxValue [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int32TimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int64TimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [bigint],
  @MaxValue [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 30300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [Int64TimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int64TimeseriesPropertyDefinitionInsertTrigger]
ON [Int64TimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [bigint]
    DECLARE @MaxValue [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int64TimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @ReferencedElementType [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 30400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [ReferenceTimeseriesPropertyDefinition]([Id], [ReferencedElementType])
          VALUES(@Id, @ReferencedElementType);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ReferenceTimeseriesPropertyDefinitionInsertTrigger]
ON [ReferenceTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [ReferencedElementType]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @ReferencedElementType [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @ReferencedElementType
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ReferenceTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@ReferencedElementType
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @ReferencedElementType
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SByteTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [numeric](3,0),
  @MaxValue [numeric](3,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 30500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [SByteTimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SByteTimeseriesPropertyDefinitionInsertTrigger]
ON [SByteTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [numeric](3,0)
    DECLARE @MaxValue [numeric](3,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SByteTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SingleTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [float](24),
  @MaxValue [float](24)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 30600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [SingleTimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SingleTimeseriesPropertyDefinitionInsertTrigger]
ON [SingleTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [float](24)
    DECLARE @MaxValue [float](24)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SingleTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [StringTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @Pattern [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 30700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [StringTimeseriesPropertyDefinition]([Id], [Pattern])
          VALUES(@Id, @Pattern);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [StringTimeseriesPropertyDefinitionInsertTrigger]
ON [StringTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [Pattern]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @Pattern [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @Pattern
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [StringTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@Pattern
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @Pattern
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [bigint],
  @MaxValue [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 30800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [TimeSpanTimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TimeSpanTimeseriesPropertyDefinitionInsertTrigger]
ON [TimeSpanTimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [bigint]
    DECLARE @MaxValue [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TimeSpanTimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt16TimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [numeric](5,0),
  @MaxValue [numeric](5,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 30900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [UInt16TimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt16TimeseriesPropertyDefinitionInsertTrigger]
ON [UInt16TimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [numeric](5,0)
    DECLARE @MaxValue [numeric](5,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt16TimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt32TimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [numeric](10,0),
  @MaxValue [numeric](10,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 31000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [UInt32TimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt32TimeseriesPropertyDefinitionInsertTrigger]
ON [UInt32TimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [numeric](10,0)
    DECLARE @MaxValue [numeric](10,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt32TimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt64TimeseriesPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [bigint],
  @MaxValue [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 31100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeseriesPropertyDefinition]([Id])
          VALUES(@Id);
      INSERT INTO [UInt64TimeseriesPropertyDefinition]([Id], [MinValue], [MaxValue])
          VALUES(@Id, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt64TimeseriesPropertyDefinitionInsertTrigger]
ON [UInt64TimeseriesPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @MinValue [bigint]
    DECLARE @MaxValue [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt64TimeseriesPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TimeSpanPropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [bigint],
  @MinValue [bigint],
  @MaxValue [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 31200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [TimeSpanPropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TimeSpanPropertyDefinitionInsertTrigger]
ON [TimeSpanPropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [bigint]
    DECLARE @MinValue [bigint]
    DECLARE @MaxValue [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TimeSpanPropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt16PropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [numeric](5,0),
  @MinValue [numeric](5,0),
  @MaxValue [numeric](5,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 31300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [UInt16PropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt16PropertyDefinitionInsertTrigger]
ON [UInt16PropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [numeric](5,0)
    DECLARE @MinValue [numeric](5,0)
    DECLARE @MaxValue [numeric](5,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt16PropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt32PropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [numeric](10,0),
  @MinValue [numeric](10,0),
  @MaxValue [numeric](10,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 31400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [UInt32PropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt32PropertyDefinitionInsertTrigger]
ON [UInt32PropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [numeric](10,0)
    DECLARE @MinValue [numeric](10,0)
    DECLARE @MaxValue [numeric](10,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt32PropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt64PropertyDefinitionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [bigint],
  @MinValue [bigint],
  @MaxValue [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 31500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [PropertyDefinition]([Id], [EntityType], [RowVersion], [ElementType], [Name], [Description])
          VALUES(@Id, @EntityType, 0, @ElementType, @Name, @Description);
      INSERT INTO [UInt64PropertyDefinition]([Id], [DefaultValue], [MinValue], [MaxValue])
          VALUES(@Id, @DefaultValue, @MinValue, @MaxValue);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt64PropertyDefinitionInsertTrigger]
ON [UInt64PropertyDefinitionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ElementType],
        [Name],
        [Description],
        [DefaultValue],
        [MinValue],
        [MaxValue]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ElementType [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    DECLARE @DefaultValue [bigint]
    DECLARE @MinValue [bigint]
    DECLARE @MaxValue [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ElementType,
        @Name,
        @Description,
        @DefaultValue,
        @MinValue,
        @MaxValue
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt64PropertyDefinitionInsert] @Id,@RowVersion,@ElementType,@Name,@Description,@DefaultValue,@MinValue,@MaxValue
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ElementType,
            @Name,
            @Description,
            @DefaultValue,
            @MinValue,
            @MaxValue
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarAlarmStatusInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @Type [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadarAlarmStatus]([Id], [RowVersion], [Radar], [Timestamp], [Type])
          VALUES(@Id, 0, @Radar, @Timestamp, @Type);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarAlarmStatusInsertTrigger]
ON [RadarAlarmStatusView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radar],
        [Timestamp],
        [Type]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radar [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Type [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radar,
        @Timestamp,
        @Type
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarAlarmStatusInsert] @Id,@RowVersion,@Radar,@Timestamp,@Type
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radar,
            @Timestamp,
            @Type
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarCommandInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 31700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadarCommand]([Id], [EntityType], [RowVersion], [Radar], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Radar, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarCommandInsertTrigger]
ON [RadarCommandView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radar],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radar [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radar,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarCommandInsert] @Id,@RowVersion,@Radar,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radar,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarCommandGetStatusInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 31800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadarCommand]([Id], [EntityType], [RowVersion], [Radar], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, @EntityType, 0, @Radar, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      INSERT INTO [RadarCommandGetStatus]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarCommandGetStatusInsertTrigger]
ON [RadarCommandGetStatusView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radar],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radar [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radar,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarCommandGetStatusInsert] @Id,@RowVersion,@Radar,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radar,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarCommandReplyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 31900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadarCommandReply]([Id], [EntityType], [RowVersion], [Radar], [Timestamp], [Command], [Status], [Message])
          VALUES(@Id, @EntityType, 0, @Radar, @Timestamp, @Command, @Status, @Message);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarCommandReplyInsertTrigger]
ON [RadarCommandReplyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radar],
        [Timestamp],
        [Command],
        [Status],
        [Message]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radar [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radar,
        @Timestamp,
        @Command,
        @Status,
        @Message
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarCommandReplyInsert] @Id,@RowVersion,@Radar,@Timestamp,@Command,@Status,@Message
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radar,
            @Timestamp,
            @Command,
            @Status,
            @Message
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarCommandReplyGetStatusInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max),
  @AzimuthCount [int],
  @TriggerCount [int],
  @RotationCount [bigint],
  @Pulse [int],
  @Tx [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 32000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadarCommandReply]([Id], [EntityType], [RowVersion], [Radar], [Timestamp], [Command], [Status], [Message])
          VALUES(@Id, @EntityType, 0, @Radar, @Timestamp, @Command, @Status, @Message);
      INSERT INTO [RadarCommandReplyGetStatus]([Id], [AzimuthCount], [TriggerCount], [RotationCount], [Pulse], [Tx])
          VALUES(@Id, @AzimuthCount, @TriggerCount, @RotationCount, @Pulse, @Tx);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarCommandReplyGetStatusInsertTrigger]
ON [RadarCommandReplyGetStatusView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radar],
        [Timestamp],
        [Command],
        [Status],
        [Message],
        [AzimuthCount],
        [TriggerCount],
        [RotationCount],
        [Pulse],
        [Tx]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radar [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    DECLARE @AzimuthCount [int]
    DECLARE @TriggerCount [int]
    DECLARE @RotationCount [bigint]
    DECLARE @Pulse [int]
    DECLARE @Tx [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radar,
        @Timestamp,
        @Command,
        @Status,
        @Message,
        @AzimuthCount,
        @TriggerCount,
        @RotationCount,
        @Pulse,
        @Tx
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarCommandReplyGetStatusInsert] @Id,@RowVersion,@Radar,@Timestamp,@Command,@Status,@Message,@AzimuthCount,@TriggerCount,@RotationCount,@Pulse,@Tx
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radar,
            @Timestamp,
            @Command,
            @Status,
            @Message,
            @AzimuthCount,
            @TriggerCount,
            @RotationCount,
            @Pulse,
            @Tx
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @RadarProtocolVersion [int],
  @RadarIPAddress [nvarchar](127),
  @RadarPort [int],
  @RadarConfigurationPort [int],
  @SkipMagicTimeout [bigint],
  @ReadTimeout [bigint],
  @SynchronizationInterval [bigint],
  @TargetsRefreshRate [int],
  @Range [int],
  @SectorCount [int],
  @SectorOffset [int],
  @ImageColor [numeric](10,0),
  @ImageSubstitutionColor [numeric](10,0),
  @TransparentColor [numeric](10,0),
  @ImageScaleFactorX [float](53),
  @ImageOffsetX [float](53),
  @ImageScaleFactorY [float](53),
  @ImageOffsetY [float](53),
  @RadarImageType [int],
  @TrackColor [numeric](10,0),
  @VectorColor [numeric](10,0),
  @EnableNmea [bit],
  @NmeaReceiverIPAddress [nvarchar](127),
  @NmeaReceiverPort [int],
  @NmeaReceiverSourceId [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadarConfiguration]([Id], [RowVersion], [Radar], [Timestamp], [RadarProtocolVersion], [RadarIPAddress], [RadarPort], [RadarConfigurationPort], [SkipMagicTimeout], [ReadTimeout], [SynchronizationInterval], [TargetsRefreshRate], [Range], [SectorCount], [SectorOffset], [ImageColor], [ImageSubstitutionColor], [TransparentColor], [ImageScaleFactorX], [ImageOffsetX], [ImageScaleFactorY], [ImageOffsetY], [RadarImageType], [TrackColor], [VectorColor], [EnableNmea], [NmeaReceiverIPAddress], [NmeaReceiverPort], [NmeaReceiverSourceId])
          VALUES(@Id, 0, @Radar, @Timestamp, @RadarProtocolVersion, @RadarIPAddress, @RadarPort, @RadarConfigurationPort, @SkipMagicTimeout, @ReadTimeout, @SynchronizationInterval, @TargetsRefreshRate, @Range, @SectorCount, @SectorOffset, @ImageColor, @ImageSubstitutionColor, @TransparentColor, @ImageScaleFactorX, @ImageOffsetX, @ImageScaleFactorY, @ImageOffsetY, @RadarImageType, @TrackColor, @VectorColor, @EnableNmea, @NmeaReceiverIPAddress, @NmeaReceiverPort, @NmeaReceiverSourceId);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarConfigurationInsertTrigger]
ON [RadarConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radar],
        [Timestamp],
        [RadarProtocolVersion],
        [RadarIPAddress],
        [RadarPort],
        [RadarConfigurationPort],
        [SkipMagicTimeout],
        [ReadTimeout],
        [SynchronizationInterval],
        [TargetsRefreshRate],
        [Range],
        [SectorCount],
        [SectorOffset],
        [ImageColor],
        [ImageSubstitutionColor],
        [TransparentColor],
        [ImageScaleFactorX],
        [ImageOffsetX],
        [ImageScaleFactorY],
        [ImageOffsetY],
        [RadarImageType],
        [TrackColor],
        [VectorColor],
        [EnableNmea],
        [NmeaReceiverIPAddress],
        [NmeaReceiverPort],
        [NmeaReceiverSourceId]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radar [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @RadarProtocolVersion [int]
    DECLARE @RadarIPAddress [nvarchar](127)
    DECLARE @RadarPort [int]
    DECLARE @RadarConfigurationPort [int]
    DECLARE @SkipMagicTimeout [bigint]
    DECLARE @ReadTimeout [bigint]
    DECLARE @SynchronizationInterval [bigint]
    DECLARE @TargetsRefreshRate [int]
    DECLARE @Range [int]
    DECLARE @SectorCount [int]
    DECLARE @SectorOffset [int]
    DECLARE @ImageColor [numeric](10,0)
    DECLARE @ImageSubstitutionColor [numeric](10,0)
    DECLARE @TransparentColor [numeric](10,0)
    DECLARE @ImageScaleFactorX [float](53)
    DECLARE @ImageOffsetX [float](53)
    DECLARE @ImageScaleFactorY [float](53)
    DECLARE @ImageOffsetY [float](53)
    DECLARE @RadarImageType [int]
    DECLARE @TrackColor [numeric](10,0)
    DECLARE @VectorColor [numeric](10,0)
    DECLARE @EnableNmea [bit]
    DECLARE @NmeaReceiverIPAddress [nvarchar](127)
    DECLARE @NmeaReceiverPort [int]
    DECLARE @NmeaReceiverSourceId [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radar,
        @Timestamp,
        @RadarProtocolVersion,
        @RadarIPAddress,
        @RadarPort,
        @RadarConfigurationPort,
        @SkipMagicTimeout,
        @ReadTimeout,
        @SynchronizationInterval,
        @TargetsRefreshRate,
        @Range,
        @SectorCount,
        @SectorOffset,
        @ImageColor,
        @ImageSubstitutionColor,
        @TransparentColor,
        @ImageScaleFactorX,
        @ImageOffsetX,
        @ImageScaleFactorY,
        @ImageOffsetY,
        @RadarImageType,
        @TrackColor,
        @VectorColor,
        @EnableNmea,
        @NmeaReceiverIPAddress,
        @NmeaReceiverPort,
        @NmeaReceiverSourceId
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarConfigurationInsert] @Id,@RowVersion,@Radar,@Timestamp,@RadarProtocolVersion,@RadarIPAddress,@RadarPort,@RadarConfigurationPort,@SkipMagicTimeout,@ReadTimeout,@SynchronizationInterval,@TargetsRefreshRate,@Range,@SectorCount,@SectorOffset,@ImageColor,@ImageSubstitutionColor,@TransparentColor,@ImageScaleFactorX,@ImageOffsetX,@ImageScaleFactorY,@ImageOffsetY,@RadarImageType,@TrackColor,@VectorColor,@EnableNmea,@NmeaReceiverIPAddress,@NmeaReceiverPort,@NmeaReceiverSourceId
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radar,
            @Timestamp,
            @RadarProtocolVersion,
            @RadarIPAddress,
            @RadarPort,
            @RadarConfigurationPort,
            @SkipMagicTimeout,
            @ReadTimeout,
            @SynchronizationInterval,
            @TargetsRefreshRate,
            @Range,
            @SectorCount,
            @SectorOffset,
            @ImageColor,
            @ImageSubstitutionColor,
            @TransparentColor,
            @ImageScaleFactorX,
            @ImageOffsetX,
            @ImageScaleFactorY,
            @ImageOffsetY,
            @RadarImageType,
            @TrackColor,
            @VectorColor,
            @EnableNmea,
            @NmeaReceiverIPAddress,
            @NmeaReceiverPort,
            @NmeaReceiverSourceId
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarImageInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @Depth [numeric](10,0),
  @Resolution [int],
  @Range [int],
  @Image [varbinary](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadarImage]([Id], [RowVersion], [Radar], [Timestamp], [Depth], [Resolution], [Range], [Image])
          VALUES(@Id, 0, @Radar, @Timestamp, @Depth, @Resolution, @Range, @Image);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarImageInsertTrigger]
ON [RadarImageView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radar],
        [Timestamp],
        [Depth],
        [Resolution],
        [Range],
        [Image]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radar [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Depth [numeric](10,0)
    DECLARE @Resolution [int]
    DECLARE @Range [int]
    DECLARE @Image [varbinary](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radar,
        @Timestamp,
        @Depth,
        @Resolution,
        @Range,
        @Image
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarImageInsert] @Id,@RowVersion,@Radar,@Timestamp,@Depth,@Resolution,@Range,@Image
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radar,
            @Timestamp,
            @Depth,
            @Resolution,
            @Range,
            @Image
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarRawTrackTableInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @Count [int],
  @Table [varbinary](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadarRawTrackTable]([Id], [RowVersion], [Radar], [Timestamp], [Count], [Table])
          VALUES(@Id, 0, @Radar, @Timestamp, @Count, @Table);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarRawTrackTableInsertTrigger]
ON [RadarRawTrackTableView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radar],
        [Timestamp],
        [Count],
        [Table]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radar [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Count [int]
    DECLARE @Table [varbinary](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radar,
        @Timestamp,
        @Count,
        @Table
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarRawTrackTableInsert] @Id,@RowVersion,@Radar,@Timestamp,@Count,@Table
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radar,
            @Timestamp,
            @Count,
            @Table
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarStatusInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @AzimuthCount [int],
  @TriggerCount [int],
  @RotationTime [bigint],
  @Pulse [int],
  @Tx [bit],
  @Tracking [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadarStatus]([Id], [RowVersion], [Radar], [Timestamp], [AzimuthCount], [TriggerCount], [RotationTime], [Pulse], [Tx], [Tracking])
          VALUES(@Id, 0, @Radar, @Timestamp, @AzimuthCount, @TriggerCount, @RotationTime, @Pulse, @Tx, @Tracking);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarStatusInsertTrigger]
ON [RadarStatusView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radar],
        [Timestamp],
        [AzimuthCount],
        [TriggerCount],
        [RotationTime],
        [Pulse],
        [Tx],
        [Tracking]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radar [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @AzimuthCount [int]
    DECLARE @TriggerCount [int]
    DECLARE @RotationTime [bigint]
    DECLARE @Pulse [int]
    DECLARE @Tx [bit]
    DECLARE @Tracking [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radar,
        @Timestamp,
        @AzimuthCount,
        @TriggerCount,
        @RotationTime,
        @Pulse,
        @Tx,
        @Tracking
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarStatusInsert] @Id,@RowVersion,@Radar,@Timestamp,@AzimuthCount,@TriggerCount,@RotationTime,@Pulse,@Tx,@Tracking
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radar,
            @Timestamp,
            @AzimuthCount,
            @TriggerCount,
            @RotationTime,
            @Pulse,
            @Tx,
            @Tracking
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadioCommandInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radio [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadioCommand]([Id], [RowVersion], [Radio], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, 0, @Radio, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadioCommandInsertTrigger]
ON [RadioCommandView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radio],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radio [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radio,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadioCommandInsert] @Id,@RowVersion,@Radio,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radio,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadioCommandReplyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radio [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadioCommandReply]([Id], [RowVersion], [Radio], [Timestamp], [Command], [Status], [Message])
          VALUES(@Id, 0, @Radio, @Timestamp, @Command, @Status, @Message);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadioCommandReplyInsertTrigger]
ON [RadioCommandReplyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radio],
        [Timestamp],
        [Command],
        [Status],
        [Message]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radio [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radio,
        @Timestamp,
        @Command,
        @Status,
        @Message
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadioCommandReplyInsert] @Id,@RowVersion,@Radio,@Timestamp,@Command,@Status,@Message
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radio,
            @Timestamp,
            @Command,
            @Status,
            @Message
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadioConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radio [uniqueidentifier],
  @Timestamp [bigint],
  @Longitude [float](53),
  @Latitude [float](53),
  @PlaybackUrl [nvarchar](127),
  @RadioIPAddress [nvarchar](127),
  @RadioPort [int],
  @Ed137IPAddress [nvarchar](127),
  @Ed137Port [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadioConfiguration]([Id], [RowVersion], [Radio], [Timestamp], [Longitude], [Latitude], [PlaybackUrl], [RadioIPAddress], [RadioPort], [Ed137IPAddress], [Ed137Port])
          VALUES(@Id, 0, @Radio, @Timestamp, @Longitude, @Latitude, @PlaybackUrl, @RadioIPAddress, @RadioPort, @Ed137IPAddress, @Ed137Port);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadioConfigurationInsertTrigger]
ON [RadioConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radio],
        [Timestamp],
        [Longitude],
        [Latitude],
        [PlaybackUrl],
        [RadioIPAddress],
        [RadioPort],
        [Ed137IPAddress],
        [Ed137Port]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radio [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @PlaybackUrl [nvarchar](127)
    DECLARE @RadioIPAddress [nvarchar](127)
    DECLARE @RadioPort [int]
    DECLARE @Ed137IPAddress [nvarchar](127)
    DECLARE @Ed137Port [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radio,
        @Timestamp,
        @Longitude,
        @Latitude,
        @PlaybackUrl,
        @RadioIPAddress,
        @RadioPort,
        @Ed137IPAddress,
        @Ed137Port
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadioConfigurationInsert] @Id,@RowVersion,@Radio,@Timestamp,@Longitude,@Latitude,@PlaybackUrl,@RadioIPAddress,@RadioPort,@Ed137IPAddress,@Ed137Port
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radio,
            @Timestamp,
            @Longitude,
            @Latitude,
            @PlaybackUrl,
            @RadioIPAddress,
            @RadioPort,
            @Ed137IPAddress,
            @Ed137Port
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadomeCommandInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radome [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadomeCommand]([Id], [RowVersion], [Radome], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, 0, @Radome, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadomeCommandInsertTrigger]
ON [RadomeCommandView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radome],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radome [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radome,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadomeCommandInsert] @Id,@RowVersion,@Radome,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radome,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadomeCommandReplyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radome [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadomeCommandReply]([Id], [RowVersion], [Radome], [Timestamp], [Command], [Status], [Message])
          VALUES(@Id, 0, @Radome, @Timestamp, @Command, @Status, @Message);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadomeCommandReplyInsertTrigger]
ON [RadomeCommandReplyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radome],
        [Timestamp],
        [Command],
        [Status],
        [Message]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radome [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radome,
        @Timestamp,
        @Command,
        @Status,
        @Message
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadomeCommandReplyInsert] @Id,@RowVersion,@Radome,@Timestamp,@Command,@Status,@Message
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radome,
            @Timestamp,
            @Command,
            @Status,
            @Message
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadomeConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Radome [uniqueidentifier],
  @Timestamp [bigint],
  @Interval [bigint],
  @LowPressureLimit [float](53),
  @HighPressureLimit [float](53),
  @LowTemperatureLimit [float](53),
  @HighTemperatureLimit [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [RadomeConfiguration]([Id], [RowVersion], [Radome], [Timestamp], [Interval], [LowPressureLimit], [HighPressureLimit], [LowTemperatureLimit], [HighTemperatureLimit])
          VALUES(@Id, 0, @Radome, @Timestamp, @Interval, @LowPressureLimit, @HighPressureLimit, @LowTemperatureLimit, @HighTemperatureLimit);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadomeConfigurationInsertTrigger]
ON [RadomeConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Radome],
        [Timestamp],
        [Interval],
        [LowPressureLimit],
        [HighPressureLimit],
        [LowTemperatureLimit],
        [HighTemperatureLimit]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Radome [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Interval [bigint]
    DECLARE @LowPressureLimit [float](53)
    DECLARE @HighPressureLimit [float](53)
    DECLARE @LowTemperatureLimit [float](53)
    DECLARE @HighTemperatureLimit [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Radome,
        @Timestamp,
        @Interval,
        @LowPressureLimit,
        @HighPressureLimit,
        @LowTemperatureLimit,
        @HighTemperatureLimit
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadomeConfigurationInsert] @Id,@RowVersion,@Radome,@Timestamp,@Interval,@LowPressureLimit,@HighPressureLimit,@LowTemperatureLimit,@HighTemperatureLimit
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Radome,
            @Timestamp,
            @Interval,
            @LowPressureLimit,
            @HighPressureLimit,
            @LowTemperatureLimit,
            @HighTemperatureLimit
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [ReferenceTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ReferenceTimeseriesValueInsertTrigger]
ON [ReferenceTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ReferenceTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SByteTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [numeric](3,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [SByteTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SByteTimeseriesValueInsertTrigger]
ON [SByteTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [numeric](3,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SByteTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SecurityDomainInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Description [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [SecurityDomain]([Id], [RowVersion], [Name], [Description])
          VALUES(@Id, 0, @Name, @Description);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SecurityDomainInsertTrigger]
ON [SecurityDomainView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Description]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Description [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Description
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SecurityDomainInsert] @Id,@RowVersion,@Name,@Description
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Description
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SecurityLoginInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Domain [uniqueidentifier],
  @Identity [nvarchar](255),
  @Description [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 33500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [SecurityIdentifier]([Id], [EntityType], [RowVersion], [Domain], [Identity], [Description])
          VALUES(@Id, @EntityType, 0, @Domain, @Identity, @Description);
      INSERT INTO [SecurityLogin]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SecurityLoginInsertTrigger]
ON [SecurityLoginView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Domain],
        [Identity],
        [Description]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Domain [uniqueidentifier]
    DECLARE @Identity [nvarchar](255)
    DECLARE @Description [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Domain,
        @Identity,
        @Description
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SecurityLoginInsert] @Id,@RowVersion,@Domain,@Identity,@Description
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Domain,
            @Identity,
            @Description
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SecurityRoleInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Domain [uniqueidentifier],
  @Identity [nvarchar](255),
  @Description [nvarchar](max),
  @Name [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 33600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [SecurityIdentifier]([Id], [EntityType], [RowVersion], [Domain], [Identity], [Description])
          VALUES(@Id, @EntityType, 0, @Domain, @Identity, @Description);
      INSERT INTO [SecurityRole]([Id], [Name])
          VALUES(@Id, @Name);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SecurityRoleInsertTrigger]
ON [SecurityRoleView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Domain],
        [Identity],
        [Description],
        [Name]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Domain [uniqueidentifier]
    DECLARE @Identity [nvarchar](255)
    DECLARE @Description [nvarchar](max)
    DECLARE @Name [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Domain,
        @Identity,
        @Description,
        @Name
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SecurityRoleInsert] @Id,@RowVersion,@Domain,@Identity,@Description,@Name
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Domain,
            @Identity,
            @Description,
            @Name
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SecurityIdentifierRoleLinkInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Member [uniqueidentifier],
  @Role [uniqueidentifier],
  @Start [bigint],
  @End [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [SecurityIdentifierRoleLink]([Id], [RowVersion], [Member], [Role], [Start], [End])
          VALUES(@Id, 0, @Member, @Role, @Start, @End);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SecurityIdentifierRoleLinkInsertTrigger]
ON [SecurityIdentifierRoleLinkView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Member],
        [Role],
        [Start],
        [End]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Member [uniqueidentifier]
    DECLARE @Role [uniqueidentifier]
    DECLARE @Start [bigint]
    DECLARE @End [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Member,
        @Role,
        @Start,
        @End
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SecurityIdentifierRoleLinkInsert] @Id,@RowVersion,@Member,@Role,@Start,@End
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Member,
            @Role,
            @Start,
            @End
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SecurityLoginSessionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Login [uniqueidentifier],
  @FromTime [bigint],
  @ThroughTime [bigint],
  @ClientSession [uniqueidentifier],
  @NotificationQueueName [nvarchar](260),
  @MessageQueueName [nvarchar](260)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [SecurityLoginSession]([Id], [RowVersion], [Login], [FromTime], [ThroughTime], [ClientSession], [NotificationQueueName], [MessageQueueName])
          VALUES(@Id, 0, @Login, @FromTime, @ThroughTime, @ClientSession, @NotificationQueueName, @MessageQueueName);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SecurityLoginSessionInsertTrigger]
ON [SecurityLoginSessionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Login],
        [FromTime],
        [ThroughTime],
        [ClientSession],
        [NotificationQueueName],
        [MessageQueueName]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Login [uniqueidentifier]
    DECLARE @FromTime [bigint]
    DECLARE @ThroughTime [bigint]
    DECLARE @ClientSession [uniqueidentifier]
    DECLARE @NotificationQueueName [nvarchar](260)
    DECLARE @MessageQueueName [nvarchar](260)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Login,
        @FromTime,
        @ThroughTime,
        @ClientSession,
        @NotificationQueueName,
        @MessageQueueName
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SecurityLoginSessionInsert] @Id,@RowVersion,@Login,@FromTime,@ThroughTime,@ClientSession,@NotificationQueueName,@MessageQueueName
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Login,
            @FromTime,
            @ThroughTime,
            @ClientSession,
            @NotificationQueueName,
            @MessageQueueName
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SecurityPermissionInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Identifier [uniqueidentifier],
  @Timestamp [bigint],
  @TypeCode [int],
  @CanCreate [bit],
  @CanRead [bit],
  @CanUpdate [bit],
  @CanDelete [bit]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [SecurityPermission]([Id], [RowVersion], [Identifier], [Timestamp], [TypeCode], [CanCreate], [CanRead], [CanUpdate], [CanDelete])
          VALUES(@Id, 0, @Identifier, @Timestamp, @TypeCode, @CanCreate, @CanRead, @CanUpdate, @CanDelete);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SecurityPermissionInsertTrigger]
ON [SecurityPermissionView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Identifier],
        [Timestamp],
        [TypeCode],
        [CanCreate],
        [CanRead],
        [CanUpdate],
        [CanDelete]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Identifier [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @TypeCode [int]
    DECLARE @CanCreate [bit]
    DECLARE @CanRead [bit]
    DECLARE @CanUpdate [bit]
    DECLARE @CanDelete [bit]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Identifier,
        @Timestamp,
        @TypeCode,
        @CanCreate,
        @CanRead,
        @CanUpdate,
        @CanDelete
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SecurityPermissionInsert] @Id,@RowVersion,@Identifier,@Timestamp,@TypeCode,@CanCreate,@CanRead,@CanUpdate,@CanDelete
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Identifier,
            @Timestamp,
            @TypeCode,
            @CanCreate,
            @CanRead,
            @CanUpdate,
            @CanDelete
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SingleTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [float](24)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [SingleTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SingleTimeseriesValueInsertTrigger]
ON [SingleTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [float](24)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SingleTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [StringTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [StringTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [StringTimeseriesValueInsertTrigger]
ON [StringTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [StringTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BinaryTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 34400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BinaryTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BinaryTimeseriesInsertTrigger]
ON [BinaryTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BinaryTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [BooleanTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 34500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [BooleanTimeseriesInsertTrigger]
ON [BooleanTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [BooleanTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisAidToNavigationOffPositionTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @AidToNavigation [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 34600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [AisAidToNavigationOffPositionTimeseries]([Id], [AidToNavigation])
          VALUES(@Id, @AidToNavigation);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisAidToNavigationOffPositionTimeseriesInsertTrigger]
ON [AisAidToNavigationOffPositionTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [AidToNavigation]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @AidToNavigation [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @AidToNavigation
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisAidToNavigationOffPositionTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@AidToNavigation
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @AidToNavigation
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DeviceEnabledTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Device [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 34700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [DeviceEnabledTimeseries]([Id], [Device])
          VALUES(@Id, @Device);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DeviceEnabledTimeseriesInsertTrigger]
ON [DeviceEnabledTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Device]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Device [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Device
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DeviceEnabledTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Device
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Device
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarAutomaticSensitivityTimeControlTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 34800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarAutomaticSensitivityTimeControlTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarAutomaticSensitivityTimeControlTimeseriesInsertTrigger]
ON [RadarAutomaticSensitivityTimeControlTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarAutomaticSensitivityTimeControlTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarBlankSector1TimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 34900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarBlankSector1Timeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarBlankSector1TimeseriesInsertTrigger]
ON [RadarBlankSector1TimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarBlankSector1TimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarBlankSector2TimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 35000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarBlankSector2Timeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarBlankSector2TimeseriesInsertTrigger]
ON [RadarBlankSector2TimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarBlankSector2TimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarEnableAutomaticFrequencyControlTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 35100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarEnableAutomaticFrequencyControlTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarEnableAutomaticFrequencyControlTimeseriesInsertTrigger]
ON [RadarEnableAutomaticFrequencyControlTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarEnableAutomaticFrequencyControlTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarEnableFastTimeConstantTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 35200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarEnableFastTimeConstantTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarEnableFastTimeConstantTimeseriesInsertTrigger]
ON [RadarEnableFastTimeConstantTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarEnableFastTimeConstantTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarEnableSensitivityTimeControlTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 35300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarEnableSensitivityTimeControlTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarEnableSensitivityTimeControlTimeseriesInsertTrigger]
ON [RadarEnableSensitivityTimeControlTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarEnableSensitivityTimeControlTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarPowerOnTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 35400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarPowerOnTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarPowerOnTimeseriesInsertTrigger]
ON [RadarPowerOnTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarPowerOnTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarSaveSettingsTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 35500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarSaveSettingsTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarSaveSettingsTimeseriesInsertTrigger]
ON [RadarSaveSettingsTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarSaveSettingsTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarTrackingTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 35600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarTrackingTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarTrackingTimeseriesInsertTrigger]
ON [RadarTrackingTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarTrackingTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MediaProxySessionEnabledTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @ProxySession [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 35700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [MediaProxySessionEnabledTimeseries]([Id], [ProxySession])
          VALUES(@Id, @ProxySession);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MediaProxySessionEnabledTimeseriesInsertTrigger]
ON [MediaProxySessionEnabledTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [ProxySession]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @ProxySession [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @ProxySession
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MediaProxySessionEnabledTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@ProxySession
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @ProxySession
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [MediaServiceEnabledTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Service [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 35800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [BooleanTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [MediaServiceEnabledTimeseries]([Id], [Service])
          VALUES(@Id, @Service);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [MediaServiceEnabledTimeseriesInsertTrigger]
ON [MediaServiceEnabledTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Service]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Service [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Service
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [MediaServiceEnabledTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Service
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Service
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ByteTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 35900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [ByteTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ByteTimeseriesInsertTrigger]
ON [ByteTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ByteTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 36000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DateTimeTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DateTimeTimeseriesInsertTrigger]
ON [DateTimeTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DateTimeTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [DoubleTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 36100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [DoubleTimeseriesInsertTrigger]
ON [DoubleTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [DoubleTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GNSSAltitudeTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GNSSDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 36200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [GNSSAltitudeTimeseries]([Id], [GNSSDevice])
          VALUES(@Id, @GNSSDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GNSSAltitudeTimeseriesInsertTrigger]
ON [GNSSAltitudeTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [GNSSDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @GNSSDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @GNSSDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GNSSAltitudeTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@GNSSDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @GNSSDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GNSSLatitudeTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GNSSDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 36300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [GNSSLatitudeTimeseries]([Id], [GNSSDevice])
          VALUES(@Id, @GNSSDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GNSSLatitudeTimeseriesInsertTrigger]
ON [GNSSLatitudeTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [GNSSDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @GNSSDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @GNSSDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GNSSLatitudeTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@GNSSDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @GNSSDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GNSSLongitudeTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GNSSDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 36400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [GNSSLongitudeTimeseries]([Id], [GNSSDevice])
          VALUES(@Id, @GNSSDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GNSSLongitudeTimeseriesInsertTrigger]
ON [GNSSLongitudeTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [GNSSDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @GNSSDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @GNSSDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GNSSLongitudeTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@GNSSDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @GNSSDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroCourseTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 36500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [GyroCourseTimeseries]([Id], [GyroDevice])
          VALUES(@Id, @GyroDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroCourseTimeseriesInsertTrigger]
ON [GyroCourseTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [GyroDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @GyroDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @GyroDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroCourseTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@GyroDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @GyroDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroHeadingMagneticNorthTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 36600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [GyroHeadingMagneticNorthTimeseries]([Id], [GyroDevice])
          VALUES(@Id, @GyroDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroHeadingMagneticNorthTimeseriesInsertTrigger]
ON [GyroHeadingMagneticNorthTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [GyroDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @GyroDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @GyroDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroHeadingMagneticNorthTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@GyroDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @GyroDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroHeadingTrueNorthTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 36700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [GyroHeadingTrueNorthTimeseries]([Id], [GyroDevice])
          VALUES(@Id, @GyroDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroHeadingTrueNorthTimeseriesInsertTrigger]
ON [GyroHeadingTrueNorthTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [GyroDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @GyroDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @GyroDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroHeadingTrueNorthTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@GyroDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @GyroDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroPitchTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 36800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [GyroPitchTimeseries]([Id], [GyroDevice])
          VALUES(@Id, @GyroDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroPitchTimeseriesInsertTrigger]
ON [GyroPitchTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [GyroDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @GyroDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @GyroDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroPitchTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@GyroDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @GyroDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroRateOfTurnTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 36900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [GyroRateOfTurnTimeseries]([Id], [GyroDevice])
          VALUES(@Id, @GyroDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroRateOfTurnTimeseriesInsertTrigger]
ON [GyroRateOfTurnTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [GyroDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @GyroDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @GyroDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroRateOfTurnTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@GyroDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @GyroDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroRollTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 37000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [GyroRollTimeseries]([Id], [GyroDevice])
          VALUES(@Id, @GyroDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroRollTimeseriesInsertTrigger]
ON [GyroRollTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [GyroDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @GyroDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @GyroDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroRollTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@GyroDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @GyroDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GyroSpeedTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 37100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [GyroSpeedTimeseries]([Id], [GyroDevice])
          VALUES(@Id, @GyroDevice);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GyroSpeedTimeseriesInsertTrigger]
ON [GyroSpeedTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [GyroDevice]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @GyroDevice [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @GyroDevice
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GyroSpeedTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@GyroDevice
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @GyroDevice
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarLatitudeTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 37200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarLatitudeTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarLatitudeTimeseriesInsertTrigger]
ON [RadarLatitudeTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarLatitudeTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarLongitudeTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 37300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarLongitudeTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarLongitudeTimeseriesInsertTrigger]
ON [RadarLongitudeTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarLongitudeTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadomeDewPointTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radome [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 37400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadomeDewPointTimeseries]([Id], [Radome])
          VALUES(@Id, @Radome);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadomeDewPointTimeseriesInsertTrigger]
ON [RadomeDewPointTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radome]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radome [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radome
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadomeDewPointTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radome
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radome
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadomePressureTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radome [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 37500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadomePressureTimeseries]([Id], [Radome])
          VALUES(@Id, @Radome);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadomePressureTimeseriesInsertTrigger]
ON [RadomePressureTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radome]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radome [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radome
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadomePressureTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radome
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radome
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadomeTemperatureTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radome [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 37600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadomeTemperatureTimeseries]([Id], [Radome])
          VALUES(@Id, @Radome);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadomeTemperatureTimeseriesInsertTrigger]
ON [RadomeTemperatureTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radome]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radome [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radome
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadomeTemperatureTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radome
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radome
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [VesselDraughtTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Vessel [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 37700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [VesselDraughtTimeseries]([Id], [Vessel])
          VALUES(@Id, @Vessel);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [VesselDraughtTimeseriesInsertTrigger]
ON [VesselDraughtTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Vessel]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Vessel [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Vessel
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [VesselDraughtTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Vessel
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Vessel
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ViewLatitudeTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @View [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 37800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [ViewLatitudeTimeseries]([Id], [View])
          VALUES(@Id, @View);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ViewLatitudeTimeseriesInsertTrigger]
ON [ViewLatitudeTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [View]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @View [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @View
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ViewLatitudeTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@View
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @View
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ViewLongitudeTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @View [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 37900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [ViewLongitudeTimeseries]([Id], [View])
          VALUES(@Id, @View);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ViewLongitudeTimeseriesInsertTrigger]
ON [ViewLongitudeTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [View]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @View [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @View
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ViewLongitudeTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@View
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @View
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ViewZoomLevelTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @View [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 38000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [ViewZoomLevelTimeseries]([Id], [View])
          VALUES(@Id, @View);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ViewZoomLevelTimeseriesInsertTrigger]
ON [ViewZoomLevelTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [View]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @View [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @View
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ViewZoomLevelTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@View
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @View
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationAbsoluteHumidityTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 38100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [WeatherStationAbsoluteHumidityTimeseries]([Id], [WeatherStation])
          VALUES(@Id, @WeatherStation);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationAbsoluteHumidityTimeseriesInsertTrigger]
ON [WeatherStationAbsoluteHumidityTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [WeatherStation]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @WeatherStation
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationAbsoluteHumidityTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@WeatherStation
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @WeatherStation
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationAirTemperatureTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 38200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [WeatherStationAirTemperatureTimeseries]([Id], [WeatherStation])
          VALUES(@Id, @WeatherStation);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationAirTemperatureTimeseriesInsertTrigger]
ON [WeatherStationAirTemperatureTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [WeatherStation]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @WeatherStation
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationAirTemperatureTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@WeatherStation
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @WeatherStation
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationBarometricPressureTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 38300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [WeatherStationBarometricPressureTimeseries]([Id], [WeatherStation])
          VALUES(@Id, @WeatherStation);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationBarometricPressureTimeseriesInsertTrigger]
ON [WeatherStationBarometricPressureTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [WeatherStation]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @WeatherStation
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationBarometricPressureTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@WeatherStation
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @WeatherStation
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationDewPointTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 38400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [WeatherStationDewPointTimeseries]([Id], [WeatherStation])
          VALUES(@Id, @WeatherStation);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationDewPointTimeseriesInsertTrigger]
ON [WeatherStationDewPointTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [WeatherStation]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @WeatherStation
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationDewPointTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@WeatherStation
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @WeatherStation
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationRelativeHumidityTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 38500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [WeatherStationRelativeHumidityTimeseries]([Id], [WeatherStation])
          VALUES(@Id, @WeatherStation);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationRelativeHumidityTimeseriesInsertTrigger]
ON [WeatherStationRelativeHumidityTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [WeatherStation]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @WeatherStation
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationRelativeHumidityTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@WeatherStation
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @WeatherStation
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationWaterTemperatureTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 38600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [WeatherStationWaterTemperatureTimeseries]([Id], [WeatherStation])
          VALUES(@Id, @WeatherStation);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationWaterTemperatureTimeseriesInsertTrigger]
ON [WeatherStationWaterTemperatureTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [WeatherStation]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @WeatherStation
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationWaterTemperatureTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@WeatherStation
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @WeatherStation
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationWindDirectionTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 38700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [WeatherStationWindDirectionTimeseries]([Id], [WeatherStation])
          VALUES(@Id, @WeatherStation);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationWindDirectionTimeseriesInsertTrigger]
ON [WeatherStationWindDirectionTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [WeatherStation]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @WeatherStation
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationWindDirectionTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@WeatherStation
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @WeatherStation
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationWindSpeedTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 38800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [DoubleTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [WeatherStationWindSpeedTimeseries]([Id], [WeatherStation])
          VALUES(@Id, @WeatherStation);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationWindSpeedTimeseriesInsertTrigger]
ON [WeatherStationWindSpeedTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [WeatherStation]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @WeatherStation
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationWindSpeedTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@WeatherStation
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @WeatherStation
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GeoPosition2DTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 38900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [GeoPosition2DTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GeoPosition2DTimeseriesInsertTrigger]
ON [GeoPosition2DTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GeoPosition2DTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [AisAidToNavigationPositionTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @AidToNavigation [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 39000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [GeoPosition2DTimeseries]([Id])
          VALUES(@Id);
      INSERT INTO [AisAidToNavigationPositionTimeseries]([Id], [AidToNavigation])
          VALUES(@Id, @AidToNavigation);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [AisAidToNavigationPositionTimeseriesInsertTrigger]
ON [AisAidToNavigationPositionTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [AidToNavigation]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @AidToNavigation [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @AidToNavigation
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [AisAidToNavigationPositionTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@AidToNavigation
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @AidToNavigation
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GeoPosition3DTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 39100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [GeoPosition3DTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GeoPosition3DTimeseriesInsertTrigger]
ON [GeoPosition3DTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GeoPosition3DTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [GuidTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 39200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [GuidTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [GuidTimeseriesInsertTrigger]
ON [GuidTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [GuidTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int16TimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 39300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int16Timeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int16TimeseriesInsertTrigger]
ON [Int16TimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int16TimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int32TimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 39400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int32TimeseriesInsertTrigger]
ON [Int32TimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int32TimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarAzimuthOffsetTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 39500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarAzimuthOffsetTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarAzimuthOffsetTimeseriesInsertTrigger]
ON [RadarAzimuthOffsetTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarAzimuthOffsetTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarFastTimeConstantLevelTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 39600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarFastTimeConstantLevelTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarFastTimeConstantLevelTimeseriesInsertTrigger]
ON [RadarFastTimeConstantLevelTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarFastTimeConstantLevelTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarFastTimeConstantModeTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 39700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarFastTimeConstantModeTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarFastTimeConstantModeTimeseriesInsertTrigger]
ON [RadarFastTimeConstantModeTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarFastTimeConstantModeTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarPulseTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 39800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarPulseTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarPulseTimeseriesInsertTrigger]
ON [RadarPulseTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarPulseTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarSector1EndTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 39900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarSector1EndTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarSector1EndTimeseriesInsertTrigger]
ON [RadarSector1EndTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarSector1EndTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarSector1StartTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 40000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarSector1StartTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarSector1StartTimeseriesInsertTrigger]
ON [RadarSector1StartTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarSector1StartTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarSector2EndTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 40100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarSector2EndTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarSector2EndTimeseriesInsertTrigger]
ON [RadarSector2EndTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarSector2EndTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarSector2StartTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 40200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarSector2StartTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarSector2StartTimeseriesInsertTrigger]
ON [RadarSector2StartTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarSector2StartTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarSensitivityTimeControlLevelTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 40300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarSensitivityTimeControlLevelTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarSensitivityTimeControlLevelTimeseriesInsertTrigger]
ON [RadarSensitivityTimeControlLevelTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarSensitivityTimeControlLevelTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadarTuningTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 40400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadarTuningTimeseries]([Id], [Radar])
          VALUES(@Id, @Radar);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadarTuningTimeseriesInsertTrigger]
ON [RadarTuningTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radar]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radar [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radar
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadarTuningTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radar
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radar
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [VesselPersonsOnBoardTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Vessel [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 40500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [VesselPersonsOnBoardTimeseries]([Id], [Vessel])
          VALUES(@Id, @Vessel);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [VesselPersonsOnBoardTimeseriesInsertTrigger]
ON [VesselPersonsOnBoardTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Vessel]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Vessel [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Vessel
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [VesselPersonsOnBoardTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Vessel
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Vessel
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Int64TimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 40600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Int64Timeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Int64TimeseriesInsertTrigger]
ON [Int64TimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Int64TimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Position2DTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 40700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Position2DTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Position2DTimeseriesInsertTrigger]
ON [Position2DTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Position2DTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Position3DTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 40800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [Position3DTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Position3DTimeseriesInsertTrigger]
ON [Position3DTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Position3DTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 40900;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [ReferenceTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ReferenceTimeseriesInsertTrigger]
ON [ReferenceTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ReferenceTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SByteTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 41000;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [SByteTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SByteTimeseriesInsertTrigger]
ON [SByteTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SByteTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [SingleTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 41100;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [SingleTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [SingleTimeseriesInsertTrigger]
ON [SingleTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [SingleTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [StringTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 41200;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [StringTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [StringTimeseriesInsertTrigger]
ON [StringTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [StringTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 41300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [TimeSpanTimeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TimeSpanTimeseriesInsertTrigger]
ON [TimeSpanTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TimeSpanTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt16TimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 41400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [UInt16Timeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt16TimeseriesInsertTrigger]
ON [UInt16TimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt16TimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt32TimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 41500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [UInt32Timeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt32TimeseriesInsertTrigger]
ON [UInt32TimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt32TimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [RadomeStatusTimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radome [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 41600;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [UInt32Timeseries]([Id])
          VALUES(@Id);
      INSERT INTO [RadomeStatusTimeseries]([Id], [Radome])
          VALUES(@Id, @Radome);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [RadomeStatusTimeseriesInsertTrigger]
ON [RadomeStatusTimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention],
        [Radome]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    DECLARE @Radome [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention,
        @Radome
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [RadomeStatusTimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention,@Radome
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention,
            @Radome
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt64TimeseriesInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 41700;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [Timeseries]([Id], [MaxRetention])
          VALUES(@Id, @MaxRetention);
      INSERT INTO [UInt64Timeseries]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt64TimeseriesInsertTrigger]
ON [UInt64TimeseriesView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name],
        [MaxRetention]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    DECLARE @MaxRetention [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name,
        @MaxRetention
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt64TimeseriesInsert] @Id,@RowVersion,@Catalog,@Name,@MaxRetention
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name,
            @MaxRetention
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TimeseriesCatalogInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 41800;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesCatalogElement]([Id], [EntityType], [RowVersion], [Catalog], [Name])
          VALUES(@Id, @EntityType, 0, @Catalog, @Name);
      INSERT INTO [TimeseriesCatalog]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TimeseriesCatalogInsertTrigger]
ON [TimeseriesCatalogView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Catalog],
        [Name]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Catalog [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Catalog,
        @Name
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TimeseriesCatalogInsert] @Id,@RowVersion,@Catalog,@Name
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Catalog,
            @Name
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TimeseriesInfoInsert]
  @Id [uniqueidentifier] OUTPUT,
  @FirstTimestamp [bigint],
  @LastTimestamp [bigint],
  @Count [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeseriesInfo]([Id], [RowVersion], [FirstTimestamp], [LastTimestamp], [Count])
          VALUES(@Id, 0, @FirstTimestamp, @LastTimestamp, @Count);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TimeseriesInfoInsertTrigger]
ON [TimeseriesInfoView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [FirstTimestamp],
        [LastTimestamp],
        [Count]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @FirstTimestamp [bigint]
    DECLARE @LastTimestamp [bigint]
    DECLARE @Count [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @FirstTimestamp,
        @LastTimestamp,
        @Count
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TimeseriesInfoInsert] @Id,@RowVersion,@FirstTimestamp,@LastTimestamp,@Count
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @FirstTimestamp,
            @LastTimestamp,
            @Count
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TimeSpanTimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TimeSpanTimeseriesValueInsertTrigger]
ON [TimeSpanTimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TimeSpanTimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TrackableItemTrackLinkInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Item [uniqueidentifier],
  @Track [uniqueidentifier],
  @Start [bigint],
  @End [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TrackableItemTrackLink]([Id], [RowVersion], [Item], [Track], [Start], [End])
          VALUES(@Id, 0, @Item, @Track, @Start, @End);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TrackableItemTrackLinkInsertTrigger]
ON [TrackableItemTrackLinkView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Item],
        [Track],
        [Start],
        [End]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Item [uniqueidentifier]
    DECLARE @Track [uniqueidentifier]
    DECLARE @Start [bigint]
    DECLARE @End [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Item,
        @Track,
        @Start,
        @End
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TrackableItemTrackLinkInsert] @Id,@RowVersion,@Item,@Track,@Start,@End
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Item,
            @Track,
            @Start,
            @End
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TrackInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Tracker [uniqueidentifier],
  @TrackNumber [bigint],
  @Timestamp [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 42300;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TrackBase]([Id], [EntityType], [RowVersion], [Tracker], [TrackNumber], [Timestamp])
          VALUES(@Id, @EntityType, 0, @Tracker, @TrackNumber, @Timestamp);
      INSERT INTO [Track]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TrackInsertTrigger]
ON [TrackView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Tracker],
        [TrackNumber],
        [Timestamp]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Tracker [uniqueidentifier]
    DECLARE @TrackNumber [bigint]
    DECLARE @Timestamp [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Tracker,
        @TrackNumber,
        @Timestamp
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TrackInsert] @Id,@RowVersion,@Tracker,@TrackNumber,@Timestamp
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Tracker,
            @TrackNumber,
            @Timestamp
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [Track3DInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Tracker [uniqueidentifier],
  @TrackNumber [bigint],
  @Timestamp [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 42400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TrackBase]([Id], [EntityType], [RowVersion], [Tracker], [TrackNumber], [Timestamp])
          VALUES(@Id, @EntityType, 0, @Tracker, @TrackNumber, @Timestamp);
      INSERT INTO [Track3D]([Id])
          VALUES(@Id);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [Track3DInsertTrigger]
ON [Track3DView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Tracker],
        [TrackNumber],
        [Timestamp]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Tracker [uniqueidentifier]
    DECLARE @TrackNumber [bigint]
    DECLARE @Timestamp [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Tracker,
        @TrackNumber,
        @Timestamp
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [Track3DInsert] @Id,@RowVersion,@Tracker,@TrackNumber,@Timestamp
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Tracker,
            @TrackNumber,
            @Timestamp
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TrackerFilterParametersInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Tracker [uniqueidentifier],
  @Name [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TrackerFilterParameters]([Id], [RowVersion], [Tracker], [Name])
          VALUES(@Id, 0, @Tracker, @Name);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TrackerFilterParametersInsertTrigger]
ON [TrackerFilterParametersView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Tracker],
        [Name]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Tracker [uniqueidentifier]
    DECLARE @Name [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Tracker,
        @Name
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TrackerFilterParametersInsert] @Id,@RowVersion,@Tracker,@Name
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Tracker,
            @Name
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TrackerFilterParametersConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Parameters [uniqueidentifier],
  @Timestamp [bigint],
  @UseNaivePredictor [bit],
  @NumberOfPoints [int],
  @WindowSize [int],
  @StabilizeCount [int],
  @MaxBadPoints [int],
  @ModelType [int],
  @SigmaR [float](53),
  @SigmaAcc [float](53),
  @TauVel [float](53),
  @TauAcc [float](53),
  @DeltaRMin [float](53),
  @DeltaVMax [float](53),
  @DeltaAMax [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TrackerFilterParametersConfiguration]([Id], [RowVersion], [Parameters], [Timestamp], [UseNaivePredictor], [NumberOfPoints], [WindowSize], [StabilizeCount], [MaxBadPoints], [ModelType], [SigmaR], [SigmaAcc], [TauVel], [TauAcc], [DeltaRMin], [DeltaVMax], [DeltaAMax])
          VALUES(@Id, 0, @Parameters, @Timestamp, @UseNaivePredictor, @NumberOfPoints, @WindowSize, @StabilizeCount, @MaxBadPoints, @ModelType, @SigmaR, @SigmaAcc, @TauVel, @TauAcc, @DeltaRMin, @DeltaVMax, @DeltaAMax);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TrackerFilterParametersConfigurationInsertTrigger]
ON [TrackerFilterParametersConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Parameters],
        [Timestamp],
        [UseNaivePredictor],
        [NumberOfPoints],
        [WindowSize],
        [StabilizeCount],
        [MaxBadPoints],
        [ModelType],
        [SigmaR],
        [SigmaAcc],
        [TauVel],
        [TauAcc],
        [DeltaRMin],
        [DeltaVMax],
        [DeltaAMax]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Parameters [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @UseNaivePredictor [bit]
    DECLARE @NumberOfPoints [int]
    DECLARE @WindowSize [int]
    DECLARE @StabilizeCount [int]
    DECLARE @MaxBadPoints [int]
    DECLARE @ModelType [int]
    DECLARE @SigmaR [float](53)
    DECLARE @SigmaAcc [float](53)
    DECLARE @TauVel [float](53)
    DECLARE @TauAcc [float](53)
    DECLARE @DeltaRMin [float](53)
    DECLARE @DeltaVMax [float](53)
    DECLARE @DeltaAMax [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Parameters,
        @Timestamp,
        @UseNaivePredictor,
        @NumberOfPoints,
        @WindowSize,
        @StabilizeCount,
        @MaxBadPoints,
        @ModelType,
        @SigmaR,
        @SigmaAcc,
        @TauVel,
        @TauAcc,
        @DeltaRMin,
        @DeltaVMax,
        @DeltaAMax
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TrackerFilterParametersConfigurationInsert] @Id,@RowVersion,@Parameters,@Timestamp,@UseNaivePredictor,@NumberOfPoints,@WindowSize,@StabilizeCount,@MaxBadPoints,@ModelType,@SigmaR,@SigmaAcc,@TauVel,@TauAcc,@DeltaRMin,@DeltaVMax,@DeltaAMax
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Parameters,
            @Timestamp,
            @UseNaivePredictor,
            @NumberOfPoints,
            @WindowSize,
            @StabilizeCount,
            @MaxBadPoints,
            @ModelType,
            @SigmaR,
            @SigmaAcc,
            @TauVel,
            @TauAcc,
            @DeltaRMin,
            @DeltaVMax,
            @DeltaAMax
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TrackInfoInsert]
  @Id [uniqueidentifier] OUTPUT,
  @FirstTimestamp [bigint],
  @LastTimestamp [bigint],
  @Count [bigint],
  @NorthWestLatitude [float](53),
  @NorthWestLongitude [float](53),
  @SouthEastLatitude [float](53),
  @SouthEastLongitude [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TrackInfo]([Id], [RowVersion], [FirstTimestamp], [LastTimestamp], [Count], [NorthWestLatitude], [NorthWestLongitude], [SouthEastLatitude], [SouthEastLongitude])
          VALUES(@Id, 0, @FirstTimestamp, @LastTimestamp, @Count, @NorthWestLatitude, @NorthWestLongitude, @SouthEastLatitude, @SouthEastLongitude);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TrackInfoInsertTrigger]
ON [TrackInfoView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [FirstTimestamp],
        [LastTimestamp],
        [Count],
        [NorthWestLatitude],
        [NorthWestLongitude],
        [SouthEastLatitude],
        [SouthEastLongitude]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @FirstTimestamp [bigint]
    DECLARE @LastTimestamp [bigint]
    DECLARE @Count [bigint]
    DECLARE @NorthWestLatitude [float](53)
    DECLARE @NorthWestLongitude [float](53)
    DECLARE @SouthEastLatitude [float](53)
    DECLARE @SouthEastLongitude [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @FirstTimestamp,
        @LastTimestamp,
        @Count,
        @NorthWestLatitude,
        @NorthWestLongitude,
        @SouthEastLatitude,
        @SouthEastLongitude
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TrackInfoInsert] @Id,@RowVersion,@FirstTimestamp,@LastTimestamp,@Count,@NorthWestLatitude,@NorthWestLongitude,@SouthEastLatitude,@SouthEastLongitude
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @FirstTimestamp,
            @LastTimestamp,
            @Count,
            @NorthWestLatitude,
            @NorthWestLongitude,
            @SouthEastLatitude,
            @SouthEastLongitude
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TrackingServiceOptionsInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timestamp [bigint],
  @TimerInterval [bigint],
  @MaxAgeOfCurrentTrackValue [bigint],
  @FalseThreshold [float](53),
  @DistanceThreshold [float](53),
  @DistanceUnmergeThreshold [float](53),
  @UnmergeLatency [bigint],
  @KalmanFiltering [bit],
  @MaxCourseDeviation [float](53),
  @MaxSpeedDeviation [float](53),
  @MinimumSpeedThreshold [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TrackingServiceOptions]([Id], [RowVersion], [Timestamp], [TimerInterval], [MaxAgeOfCurrentTrackValue], [FalseThreshold], [DistanceThreshold], [DistanceUnmergeThreshold], [UnmergeLatency], [KalmanFiltering], [MaxCourseDeviation], [MaxSpeedDeviation], [MinimumSpeedThreshold])
          VALUES(@Id, 0, @Timestamp, @TimerInterval, @MaxAgeOfCurrentTrackValue, @FalseThreshold, @DistanceThreshold, @DistanceUnmergeThreshold, @UnmergeLatency, @KalmanFiltering, @MaxCourseDeviation, @MaxSpeedDeviation, @MinimumSpeedThreshold);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TrackingServiceOptionsInsertTrigger]
ON [TrackingServiceOptionsView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timestamp],
        [TimerInterval],
        [MaxAgeOfCurrentTrackValue],
        [FalseThreshold],
        [DistanceThreshold],
        [DistanceUnmergeThreshold],
        [UnmergeLatency],
        [KalmanFiltering],
        [MaxCourseDeviation],
        [MaxSpeedDeviation],
        [MinimumSpeedThreshold]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timestamp [bigint]
    DECLARE @TimerInterval [bigint]
    DECLARE @MaxAgeOfCurrentTrackValue [bigint]
    DECLARE @FalseThreshold [float](53)
    DECLARE @DistanceThreshold [float](53)
    DECLARE @DistanceUnmergeThreshold [float](53)
    DECLARE @UnmergeLatency [bigint]
    DECLARE @KalmanFiltering [bit]
    DECLARE @MaxCourseDeviation [float](53)
    DECLARE @MaxSpeedDeviation [float](53)
    DECLARE @MinimumSpeedThreshold [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timestamp,
        @TimerInterval,
        @MaxAgeOfCurrentTrackValue,
        @FalseThreshold,
        @DistanceThreshold,
        @DistanceUnmergeThreshold,
        @UnmergeLatency,
        @KalmanFiltering,
        @MaxCourseDeviation,
        @MaxSpeedDeviation,
        @MinimumSpeedThreshold
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TrackingServiceOptionsInsert] @Id,@RowVersion,@Timestamp,@TimerInterval,@MaxAgeOfCurrentTrackValue,@FalseThreshold,@DistanceThreshold,@DistanceUnmergeThreshold,@UnmergeLatency,@KalmanFiltering,@MaxCourseDeviation,@MaxSpeedDeviation,@MinimumSpeedThreshold
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timestamp,
            @TimerInterval,
            @MaxAgeOfCurrentTrackValue,
            @FalseThreshold,
            @DistanceThreshold,
            @DistanceUnmergeThreshold,
            @UnmergeLatency,
            @KalmanFiltering,
            @MaxCourseDeviation,
            @MaxSpeedDeviation,
            @MinimumSpeedThreshold
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TrackLinkInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Primary [uniqueidentifier],
  @Secondary [uniqueidentifier],
  @Start [bigint],
  @End [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TrackLink]([Id], [RowVersion], [Primary], [Secondary], [Start], [End])
          VALUES(@Id, 0, @Primary, @Secondary, @Start, @End);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TrackLinkInsertTrigger]
ON [TrackLinkView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Primary],
        [Secondary],
        [Start],
        [End]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Primary [uniqueidentifier]
    DECLARE @Secondary [uniqueidentifier]
    DECLARE @Start [bigint]
    DECLARE @End [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Primary,
        @Secondary,
        @Start,
        @End
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TrackLinkInsert] @Id,@RowVersion,@Primary,@Secondary,@Start,@End
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Primary,
            @Secondary,
            @Start,
            @End
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TrackValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Track [uniqueidentifier],
  @Timestamp [bigint],
  @Flags [int],
  @Status [int],
  @Latitude [float](53),
  @Longitude [float](53),
  @Speed [float](53),
  @Course [float](53),
  @Heading [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TrackValue]([Id], [RowVersion], [Track], [Timestamp], [Flags], [Status], [Latitude], [Longitude], [Speed], [Course], [Heading])
          VALUES(@Id, 0, @Track, @Timestamp, @Flags, @Status, @Latitude, @Longitude, @Speed, @Course, @Heading);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TrackValueInsertTrigger]
ON [TrackValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Track],
        [Timestamp],
        [Flags],
        [Status],
        [Latitude],
        [Longitude],
        [Speed],
        [Course],
        [Heading]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Track [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Flags [int]
    DECLARE @Status [int]
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @Speed [float](53)
    DECLARE @Course [float](53)
    DECLARE @Heading [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Track,
        @Timestamp,
        @Flags,
        @Status,
        @Latitude,
        @Longitude,
        @Speed,
        @Course,
        @Heading
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TrackValueInsert] @Id,@RowVersion,@Track,@Timestamp,@Flags,@Status,@Latitude,@Longitude,@Speed,@Course,@Heading
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Track,
            @Timestamp,
            @Flags,
            @Status,
            @Latitude,
            @Longitude,
            @Speed,
            @Course,
            @Heading
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [TrackValue3DInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Track [uniqueidentifier],
  @Timestamp [bigint],
  @Flags [int],
  @Status [numeric](10,0),
  @Latitude [float](53),
  @Longitude [float](53),
  @Altitude [float](53),
  @Speed [float](53),
  @Course [float](53),
  @RateOfClimb [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [TrackValue3D]([Id], [RowVersion], [Track], [Timestamp], [Flags], [Status], [Latitude], [Longitude], [Altitude], [Speed], [Course], [RateOfClimb])
          VALUES(@Id, 0, @Track, @Timestamp, @Flags, @Status, @Latitude, @Longitude, @Altitude, @Speed, @Course, @RateOfClimb);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [TrackValue3DInsertTrigger]
ON [TrackValue3DView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Track],
        [Timestamp],
        [Flags],
        [Status],
        [Latitude],
        [Longitude],
        [Altitude],
        [Speed],
        [Course],
        [RateOfClimb]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Track [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Flags [int]
    DECLARE @Status [numeric](10,0)
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @Altitude [float](53)
    DECLARE @Speed [float](53)
    DECLARE @Course [float](53)
    DECLARE @RateOfClimb [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Track,
        @Timestamp,
        @Flags,
        @Status,
        @Latitude,
        @Longitude,
        @Altitude,
        @Speed,
        @Course,
        @RateOfClimb
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [TrackValue3DInsert] @Id,@RowVersion,@Track,@Timestamp,@Flags,@Status,@Latitude,@Longitude,@Altitude,@Speed,@Course,@RateOfClimb
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Track,
            @Timestamp,
            @Flags,
            @Status,
            @Latitude,
            @Longitude,
            @Altitude,
            @Speed,
            @Course,
            @RateOfClimb
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt16TimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [numeric](5,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [UInt16TimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt16TimeseriesValueInsertTrigger]
ON [UInt16TimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [numeric](5,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt16TimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt32TimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [numeric](10,0)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [UInt32TimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt32TimeseriesValueInsertTrigger]
ON [UInt32TimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [numeric](10,0)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt32TimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [UInt64TimeseriesValueInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [UInt64TimeseriesValue]([Id], [RowVersion], [Timeseries], [Timestamp], [Value])
          VALUES(@Id, 0, @Timeseries, @Timestamp, @Value);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [UInt64TimeseriesValueInsertTrigger]
ON [UInt64TimeseriesValueView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Timeseries],
        [Timestamp],
        [Value]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Timeseries [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Value [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Timeseries,
        @Timestamp,
        @Value
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [UInt64TimeseriesValueInsert] @Id,@RowVersion,@Timeseries,@Timestamp,@Value
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Timeseries,
            @Timestamp,
            @Value
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [VehicleTypeInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [VehicleType]([Id], [RowVersion], [Name])
          VALUES(@Id, 0, @Name);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [VehicleTypeInsertTrigger]
ON [VehicleTypeView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [VehicleTypeInsert] @Id,@RowVersion,@Name
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [VesselTypeInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Code [int]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [VesselType]([Id], [RowVersion], [Name], [Code])
          VALUES(@Id, 0, @Name, @Code);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [VesselTypeInsertTrigger]
ON [VesselTypeView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Code]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Code [int]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Code
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [VesselTypeInsert] @Id,@RowVersion,@Name,@Code
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Code
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ViewInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @LatitudeTimeseries [uniqueidentifier],
  @LongitudeTimeseries [uniqueidentifier],
  @ZoomLevelTimeseries [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [View]([Id], [RowVersion], [Name], [LatitudeTimeseries], [LongitudeTimeseries], [ZoomLevelTimeseries])
          VALUES(@Id, 0, @Name, @LatitudeTimeseries, @LongitudeTimeseries, @ZoomLevelTimeseries);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ViewInsertTrigger]
ON [ViewView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [LatitudeTimeseries],
        [LongitudeTimeseries],
        [ZoomLevelTimeseries]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @LatitudeTimeseries [uniqueidentifier]
    DECLARE @LongitudeTimeseries [uniqueidentifier]
    DECLARE @ZoomLevelTimeseries [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @LatitudeTimeseries,
        @LongitudeTimeseries,
        @ZoomLevelTimeseries
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ViewInsert] @Id,@RowVersion,@Name,@LatitudeTimeseries,@LongitudeTimeseries,@ZoomLevelTimeseries
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @LatitudeTimeseries,
            @LongitudeTimeseries,
            @ZoomLevelTimeseries
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ViewCameraLinkInsert]
  @Id [uniqueidentifier] OUTPUT,
  @View [uniqueidentifier],
  @Camera [uniqueidentifier],
  @Start [bigint],
  @End [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [ViewCameraLink]([Id], [RowVersion], [View], [Camera], [Start], [End])
          VALUES(@Id, 0, @View, @Camera, @Start, @End);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ViewCameraLinkInsertTrigger]
ON [ViewCameraLinkView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [View],
        [Camera],
        [Start],
        [End]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @View [uniqueidentifier]
    DECLARE @Camera [uniqueidentifier]
    DECLARE @Start [bigint]
    DECLARE @End [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @View,
        @Camera,
        @Start,
        @End
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ViewCameraLinkInsert] @Id,@RowVersion,@View,@Camera,@Start,@End
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @View,
            @Camera,
            @Start,
            @End
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ViewTrackerLinkInsert]
  @Id [uniqueidentifier] OUTPUT,
  @View [uniqueidentifier],
  @Tracker [uniqueidentifier],
  @Start [bigint],
  @End [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [ViewTrackerLink]([Id], [RowVersion], [View], [Tracker], [Start], [End])
          VALUES(@Id, 0, @View, @Tracker, @Start, @End);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ViewTrackerLinkInsertTrigger]
ON [ViewTrackerLinkView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [View],
        [Tracker],
        [Start],
        [End]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @View [uniqueidentifier]
    DECLARE @Tracker [uniqueidentifier]
    DECLARE @Start [bigint]
    DECLARE @End [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @View,
        @Tracker,
        @Start,
        @End
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ViewTrackerLinkInsert] @Id,@RowVersion,@View,@Tracker,@Start,@End
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @View,
            @Tracker,
            @Start,
            @End
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationCommandInsert]
  @Id [uniqueidentifier] OUTPUT,
  @WeatherStation [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [WeatherStationCommand]([Id], [RowVersion], [WeatherStation], [Timestamp], [DeviceCommandSourceType], [DeviceCommandSourceId], [Reply])
          VALUES(@Id, 0, @WeatherStation, @Timestamp, @DeviceCommandSourceType, @DeviceCommandSourceId, @Reply);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationCommandInsertTrigger]
ON [WeatherStationCommandView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [WeatherStation],
        [Timestamp],
        [DeviceCommandSourceType],
        [DeviceCommandSourceId],
        [Reply]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @DeviceCommandSourceType [int]
    DECLARE @DeviceCommandSourceId [uniqueidentifier]
    DECLARE @Reply [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @WeatherStation,
        @Timestamp,
        @DeviceCommandSourceType,
        @DeviceCommandSourceId,
        @Reply
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationCommandInsert] @Id,@RowVersion,@WeatherStation,@Timestamp,@DeviceCommandSourceType,@DeviceCommandSourceId,@Reply
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @WeatherStation,
            @Timestamp,
            @DeviceCommandSourceType,
            @DeviceCommandSourceId,
            @Reply
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationCommandReplyInsert]
  @Id [uniqueidentifier] OUTPUT,
  @WeatherStation [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [WeatherStationCommandReply]([Id], [RowVersion], [WeatherStation], [Timestamp], [Command], [Status], [Message])
          VALUES(@Id, 0, @WeatherStation, @Timestamp, @Command, @Status, @Message);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationCommandReplyInsertTrigger]
ON [WeatherStationCommandReplyView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [WeatherStation],
        [Timestamp],
        [Command],
        [Status],
        [Message]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Command [uniqueidentifier]
    DECLARE @Status [int]
    DECLARE @Message [nvarchar](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @WeatherStation,
        @Timestamp,
        @Command,
        @Status,
        @Message
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationCommandReplyInsert] @Id,@RowVersion,@WeatherStation,@Timestamp,@Command,@Status,@Message
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @WeatherStation,
            @Timestamp,
            @Command,
            @Status,
            @Message
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [WeatherStationConfigurationInsert]
  @Id [uniqueidentifier] OUTPUT,
  @WeatherStation [uniqueidentifier],
  @Timestamp [bigint],
  @NoDataTimeOut [bigint],
  @SendInterval [bigint],
  @Latitude [float](53),
  @Longitude [float](53),
  @GyroOffset [float](53),
  @EnableAveraging [bit],
  @AveragingInterval [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [WeatherStationConfiguration]([Id], [RowVersion], [WeatherStation], [Timestamp], [NoDataTimeOut], [SendInterval], [Latitude], [Longitude], [GyroOffset], [EnableAveraging], [AveragingInterval])
          VALUES(@Id, 0, @WeatherStation, @Timestamp, @NoDataTimeOut, @SendInterval, @Latitude, @Longitude, @GyroOffset, @EnableAveraging, @AveragingInterval);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [WeatherStationConfigurationInsertTrigger]
ON [WeatherStationConfigurationView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [WeatherStation],
        [Timestamp],
        [NoDataTimeOut],
        [SendInterval],
        [Latitude],
        [Longitude],
        [GyroOffset],
        [EnableAveraging],
        [AveragingInterval]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @WeatherStation [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @NoDataTimeOut [bigint]
    DECLARE @SendInterval [bigint]
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @GyroOffset [float](53)
    DECLARE @EnableAveraging [bit]
    DECLARE @AveragingInterval [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @WeatherStation,
        @Timestamp,
        @NoDataTimeOut,
        @SendInterval,
        @Latitude,
        @Longitude,
        @GyroOffset,
        @EnableAveraging,
        @AveragingInterval
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [WeatherStationConfigurationInsert] @Id,@RowVersion,@WeatherStation,@Timestamp,@NoDataTimeOut,@SendInterval,@Latitude,@Longitude,@GyroOffset,@EnableAveraging,@AveragingInterval
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @WeatherStation,
            @Timestamp,
            @NoDataTimeOut,
            @SendInterval,
            @Latitude,
            @Longitude,
            @GyroOffset,
            @EnableAveraging,
            @AveragingInterval
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [CircularZoneInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Longitude [float](53),
  @Latitude [float](53),
  @AlarmType [int],
  @AlarmTime [bigint],
  @RadarTrackMinimumLifetime [bigint],
  @Speed [float](53),
  @StrokeColor [numeric](10,0),
  @FillColor [numeric](10,0),
  @Radius [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 44400;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Zone]([Id], [EntityType], [RowVersion], [Name], [Longitude], [Latitude], [AlarmType], [AlarmTime], [RadarTrackMinimumLifetime], [Speed], [StrokeColor], [FillColor])
          VALUES(@Id, @EntityType, 0, @Name, @Longitude, @Latitude, @AlarmType, @AlarmTime, @RadarTrackMinimumLifetime, @Speed, @StrokeColor, @FillColor);
      INSERT INTO [CircularZone]([Id], [Radius])
          VALUES(@Id, @Radius);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [CircularZoneInsertTrigger]
ON [CircularZoneView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Longitude],
        [Latitude],
        [AlarmType],
        [AlarmTime],
        [RadarTrackMinimumLifetime],
        [Speed],
        [StrokeColor],
        [FillColor],
        [Radius]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @AlarmType [int]
    DECLARE @AlarmTime [bigint]
    DECLARE @RadarTrackMinimumLifetime [bigint]
    DECLARE @Speed [float](53)
    DECLARE @StrokeColor [numeric](10,0)
    DECLARE @FillColor [numeric](10,0)
    DECLARE @Radius [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Longitude,
        @Latitude,
        @AlarmType,
        @AlarmTime,
        @RadarTrackMinimumLifetime,
        @Speed,
        @StrokeColor,
        @FillColor,
        @Radius
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [CircularZoneInsert] @Id,@RowVersion,@Name,@Longitude,@Latitude,@AlarmType,@AlarmTime,@RadarTrackMinimumLifetime,@Speed,@StrokeColor,@FillColor,@Radius
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Longitude,
            @Latitude,
            @AlarmType,
            @AlarmTime,
            @RadarTrackMinimumLifetime,
            @Speed,
            @StrokeColor,
            @FillColor,
            @Radius
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [PolygonZoneInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Name [nvarchar](127),
  @Longitude [float](53),
  @Latitude [float](53),
  @AlarmType [int],
  @AlarmTime [bigint],
  @RadarTrackMinimumLifetime [bigint],
  @Speed [float](53),
  @StrokeColor [numeric](10,0),
  @FillColor [numeric](10,0),
  @Polygon [varbinary](max)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @EntityType INT;
    SET @EntityType = 44500;
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Zone]([Id], [EntityType], [RowVersion], [Name], [Longitude], [Latitude], [AlarmType], [AlarmTime], [RadarTrackMinimumLifetime], [Speed], [StrokeColor], [FillColor])
          VALUES(@Id, @EntityType, 0, @Name, @Longitude, @Latitude, @AlarmType, @AlarmTime, @RadarTrackMinimumLifetime, @Speed, @StrokeColor, @FillColor);
      INSERT INTO [PolygonZone]([Id], [Polygon])
          VALUES(@Id, @Polygon);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [PolygonZoneInsertTrigger]
ON [PolygonZoneView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Name],
        [Longitude],
        [Latitude],
        [AlarmType],
        [AlarmTime],
        [RadarTrackMinimumLifetime],
        [Speed],
        [StrokeColor],
        [FillColor],
        [Polygon]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Name [nvarchar](127)
    DECLARE @Longitude [float](53)
    DECLARE @Latitude [float](53)
    DECLARE @AlarmType [int]
    DECLARE @AlarmTime [bigint]
    DECLARE @RadarTrackMinimumLifetime [bigint]
    DECLARE @Speed [float](53)
    DECLARE @StrokeColor [numeric](10,0)
    DECLARE @FillColor [numeric](10,0)
    DECLARE @Polygon [varbinary](max)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Name,
        @Longitude,
        @Latitude,
        @AlarmType,
        @AlarmTime,
        @RadarTrackMinimumLifetime,
        @Speed,
        @StrokeColor,
        @FillColor,
        @Polygon
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [PolygonZoneInsert] @Id,@RowVersion,@Name,@Longitude,@Latitude,@AlarmType,@AlarmTime,@RadarTrackMinimumLifetime,@Speed,@StrokeColor,@FillColor,@Polygon
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Name,
            @Longitude,
            @Latitude,
            @AlarmType,
            @AlarmTime,
            @RadarTrackMinimumLifetime,
            @Speed,
            @StrokeColor,
            @FillColor,
            @Polygon
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ZoneExceptionsInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Zone [uniqueidentifier],
  @Timestamp [bigint]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [ZoneExceptions]([Id], [RowVersion], [Zone], [Timestamp])
          VALUES(@Id, 0, @Zone, @Timestamp);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ZoneExceptionsInsertTrigger]
ON [ZoneExceptionsView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Zone],
        [Timestamp]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Zone [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Zone,
        @Timestamp
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ZoneExceptionsInsert] @Id,@RowVersion,@Zone,@Timestamp
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Zone,
            @Timestamp
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ZoneExceptionsVesselLinkInsert]
  @Id [uniqueidentifier] OUTPUT,
  @ZoneExceptions [uniqueidentifier],
  @Vessel [uniqueidentifier]
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [ZoneExceptionsVesselLink]([Id], [RowVersion], [ZoneExceptions], [Vessel])
          VALUES(@Id, 0, @ZoneExceptions, @Vessel);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ZoneExceptionsVesselLinkInsertTrigger]
ON [ZoneExceptionsVesselLinkView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [ZoneExceptions],
        [Vessel]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @ZoneExceptions [uniqueidentifier]
    DECLARE @Vessel [uniqueidentifier]
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @ZoneExceptions,
        @Vessel
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ZoneExceptionsVesselLinkInsert] @Id,@RowVersion,@ZoneExceptions,@Vessel
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @ZoneExceptions,
            @Vessel
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

CREATE OR ALTER PROCEDURE [ZoneTrackAlarmInsert]
  @Id [uniqueidentifier] OUTPUT,
  @Track [uniqueidentifier],
  @Zone [uniqueidentifier],
  @RadarTrack [uniqueidentifier],
  @Timestamp [bigint],
  @Latitude [float](53),
  @Longitude [float](53),
  @Speed [float](53),
  @Course [float](53),
  @Heading [float](53),
  @EnterLatitude [float](53),
  @EnterLongitude [float](53),
  @LeaveLatitude [float](53),
  @LeaveLongitude [float](53)
AS
  BEGIN
    IF @Id IS NULL
    BEGIN
      SET @Id = NEWID()
    END
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [ZoneTrackAlarm]([Id], [RowVersion], [Track], [Zone], [RadarTrack], [Timestamp], [Latitude], [Longitude], [Speed], [Course], [Heading], [EnterLatitude], [EnterLongitude], [LeaveLatitude], [LeaveLongitude])
          VALUES(@Id, 0, @Track, @Zone, @RadarTrack, @Timestamp, @Latitude, @Longitude, @Speed, @Course, @Heading, @EnterLatitude, @EnterLongitude, @LeaveLatitude, @LeaveLongitude);
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER TRIGGER [ZoneTrackAlarmInsertTrigger]
ON [ZoneTrackAlarmView]
INSTEAD OF INSERT AS
  BEGIN
    DECLARE @cur CURSOR
    SET @cur = CURSOR FOR
      SELECT
        [Id],
        [RowVersion],
        [Track],
        [Zone],
        [RadarTrack],
        [Timestamp],
        [Latitude],
        [Longitude],
        [Speed],
        [Course],
        [Heading],
        [EnterLatitude],
        [EnterLongitude],
        [LeaveLatitude],
        [LeaveLongitude]
      FROM inserted
    OPEN @cur
    DECLARE @Id [uniqueidentifier]
    DECLARE @RowVersion [bigint]
    DECLARE @Track [uniqueidentifier]
    DECLARE @Zone [uniqueidentifier]
    DECLARE @RadarTrack [uniqueidentifier]
    DECLARE @Timestamp [bigint]
    DECLARE @Latitude [float](53)
    DECLARE @Longitude [float](53)
    DECLARE @Speed [float](53)
    DECLARE @Course [float](53)
    DECLARE @Heading [float](53)
    DECLARE @EnterLatitude [float](53)
    DECLARE @EnterLongitude [float](53)
    DECLARE @LeaveLatitude [float](53)
    DECLARE @LeaveLongitude [float](53)
    FETCH NEXT FROM @cur INTO
        @Id,
        @RowVersion,
        @Track,
        @Zone,
        @RadarTrack,
        @Timestamp,
        @Latitude,
        @Longitude,
        @Speed,
        @Course,
        @Heading,
        @EnterLatitude,
        @EnterLongitude,
        @LeaveLatitude,
        @LeaveLongitude
    WHILE(@@fetch_status <> -1)
      BEGIN
        EXEC [ZoneTrackAlarmInsert] @Id,@RowVersion,@Track,@Zone,@RadarTrack,@Timestamp,@Latitude,@Longitude,@Speed,@Course,@Heading,@EnterLatitude,@EnterLongitude,@LeaveLatitude,@LeaveLongitude
        FETCH NEXT FROM @cur INTO
            @Id,
            @RowVersion,
            @Track,
            @Zone,
            @RadarTrack,
            @Timestamp,
            @Latitude,
            @Longitude,
            @Speed,
            @Course,
            @Heading,
            @EnterLatitude,
            @EnterLongitude,
            @LeaveLatitude,
            @LeaveLongitude
      END
    CLOSE @cur
    DEALLOCATE @cur
  END

GO

