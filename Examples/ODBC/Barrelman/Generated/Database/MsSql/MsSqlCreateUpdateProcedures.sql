CREATE OR ALTER PROCEDURE [AircraftTypeUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU10000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AircraftType] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU10000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisDeviceCommandUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @AisDevice [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU10100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisDeviceCommand] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU10100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisDeviceCommandReplyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @AisDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU10200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisDeviceCommandReply] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU10200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisDeviceConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU10300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisDeviceConfiguration] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[Timestamp] = @Timestamp,[Filter] = @Filter,[NorthWestLatitude] = @NorthWestLatitude,[NorthWestLongitude] = @NorthWestLongitude,[SouthEastLatitude] = @SouthEastLatitude,[SouthEastLongitude] = @SouthEastLongitude,[ComPort] = @ComPort,[BaudRate] = @BaudRate,[IPAddress] = @IPAddress,[Port] = @Port,[UdpPort] = @UdpPort,[Authenticate] = @Authenticate,[UserName] = @UserName,[Password] = @Password,[AuthenticationURL] = @AuthenticationURL,[ConnectionType] = @ConnectionType,[SourceUpdateRate] = @SourceUpdateRate,[ConfigurationURL] = @ConfigurationURL,[StoreReceivedSentences] = @StoreReceivedSentences
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU10300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisDeviceRawMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @AisDevice [uniqueidentifier],
  @Timestamp [bigint],
  @IsSent [bit],
  @Message [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU10400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisDeviceRawMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[Timestamp] = @Timestamp,[IsSent] = @IsSent,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU10400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisDeviceRawSentenceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @AisDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Sentence [nvarchar](1024)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU10500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisDeviceRawSentence] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[Timestamp] = @Timestamp,[Sentence] = @Sentence
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU10500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AidToNavigationReportMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU10700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AidToNavigationReportMessage] SET [NavigationalAidType] = @NavigationalAidType,[Name] = @Name,[PositionAccuracy] = @PositionAccuracy,[Longitude] = @Longitude,[Latitude] = @Latitude,[DimensionToBow] = @DimensionToBow,[DimensionToStern] = @DimensionToStern,[DimensionToPort] = @DimensionToPort,[DimensionToStarboard] = @DimensionToStarboard,[PositionFixType] = @PositionFixType,[Timestamp] = @Timestamp,[OffPosition] = @OffPosition,[RegionalReserved] = @RegionalReserved,[Raim] = @Raim,[VirtualAid] = @VirtualAid,[Assigned] = @Assigned,[Spare] = @Spare,[NameExtension] = @NameExtension
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU10700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisAddressedSafetyRelatedMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU10800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisAddressedSafetyRelatedMessage] SET [SequenceNumber] = @SequenceNumber,[DestinationMmsi] = @DestinationMmsi,[RetransmitFlag] = @RetransmitFlag,[Spare] = @Spare,[Text] = @Text
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU10800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisBaseStationReportMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU10900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisBaseStationReportMessage] SET [Timestamp] = @Timestamp,[PositionAccuracy] = @PositionAccuracy,[Longitude] = @Longitude,[Latitude] = @Latitude,[PositionFixType] = @PositionFixType,[Spare] = @Spare,[Raim] = @Raim,[RadioStatus] = @RadioStatus
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU10900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisBinaryAcknowledgeMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU11000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisBinaryAcknowledgeMessage] SET [Spare] = @Spare,[SequenceNumber1] = @SequenceNumber1,[Mmsi1] = @Mmsi1,[SequenceNumber2] = @SequenceNumber2,[Mmsi2] = @Mmsi2,[SequenceNumber3] = @SequenceNumber3,[Mmsi3] = @Mmsi3,[SequenceNumber4] = @SequenceNumber4,[Mmsi4] = @Mmsi4
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU11000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisBinaryAddressedMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU11100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisBinaryAddressedMessage] SET [SequenceNumber] = @SequenceNumber,[DestinationMmsi] = @DestinationMmsi,[RetransmitFlag] = @RetransmitFlag,[Spare] = @Spare,[DesignatedAreaCode] = @DesignatedAreaCode,[FunctionalId] = @FunctionalId,[Data] = @Data
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU11100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisBinaryBroadcastMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU11200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisBinaryBroadcastMessage] SET [Spare] = @Spare,[DesignatedAreaCode] = @DesignatedAreaCode,[FunctionalId] = @FunctionalId,[Data] = @Data
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU11200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisDataLinkManagementMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU11300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisDataLinkManagementMessage] SET [Spare] = @Spare,[Offset1] = @Offset1,[ReservedSlots1] = @ReservedSlots1,[Timeout1] = @Timeout1,[Increment1] = @Increment1,[Offset2] = @Offset2,[ReservedSlots2] = @ReservedSlots2,[Timeout2] = @Timeout2,[Increment2] = @Increment2,[Offset3] = @Offset3,[ReservedSlots3] = @ReservedSlots3,[Timeout3] = @Timeout3,[Increment3] = @Increment3,[Offset4] = @Offset4,[ReservedSlots4] = @ReservedSlots4,[Timeout4] = @Timeout4,[Increment4] = @Increment4
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU11300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisExtendedClassBCsPositionReportMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU11400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisExtendedClassBCsPositionReportMessage] SET [Reserved] = @Reserved,[SpeedOverGround] = @SpeedOverGround,[PositionAccuracy] = @PositionAccuracy,[Longitude] = @Longitude,[Latitude] = @Latitude,[CourseOverGround] = @CourseOverGround,[TrueHeading] = @TrueHeading,[Timestamp] = @Timestamp,[RegionalReserved] = @RegionalReserved,[Name] = @Name,[ShipType] = @ShipType,[DimensionToBow] = @DimensionToBow,[DimensionToStern] = @DimensionToStern,[DimensionToPort] = @DimensionToPort,[DimensionToStarboard] = @DimensionToStarboard,[PositionFixType] = @PositionFixType,[Raim] = @Raim,[DataTerminalReady] = @DataTerminalReady,[Assigned] = @Assigned,[Spare] = @Spare
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU11400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisInterrogationMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU11500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisInterrogationMessage] SET [InterrogatedMmsi] = @InterrogatedMmsi,[FirstMessageType] = @FirstMessageType,[FirstSlotOffset] = @FirstSlotOffset,[SecondMessageType] = @SecondMessageType,[SecondSlotOffset] = @SecondSlotOffset,[SecondStationInterrogationMmsi] = @SecondStationInterrogationMmsi,[SecondStationFirstMessageType] = @SecondStationFirstMessageType,[SecondStationFirstSlotOffset] = @SecondStationFirstSlotOffset
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU11500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisPositionReportClassAAssignedScheduleMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU11700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisPositionReportClassAMessageBase] SET [NavigationStatus] = @NavigationStatus,[RateOfTurn] = @RateOfTurn,[SpeedOverGround] = @SpeedOverGround,[PositionAccuracy] = @PositionAccuracy,[Longitude] = @Longitude,[Latitude] = @Latitude,[CourseOverGround] = @CourseOverGround,[TrueHeading] = @TrueHeading,[Timestamp] = @Timestamp,[ManeuverIndicator] = @ManeuverIndicator,[Spare] = @Spare,[Raim] = @Raim,[RadioStatus] = @RadioStatus
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU11700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisPositionReportClassAMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU11800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisPositionReportClassAMessageBase] SET [NavigationStatus] = @NavigationStatus,[RateOfTurn] = @RateOfTurn,[SpeedOverGround] = @SpeedOverGround,[PositionAccuracy] = @PositionAccuracy,[Longitude] = @Longitude,[Latitude] = @Latitude,[CourseOverGround] = @CourseOverGround,[TrueHeading] = @TrueHeading,[Timestamp] = @Timestamp,[ManeuverIndicator] = @ManeuverIndicator,[Spare] = @Spare,[Raim] = @Raim,[RadioStatus] = @RadioStatus
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU11800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisPositionReportClassAResponseToInterrogationMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU11900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisPositionReportClassAMessageBase] SET [NavigationStatus] = @NavigationStatus,[RateOfTurn] = @RateOfTurn,[SpeedOverGround] = @SpeedOverGround,[PositionAccuracy] = @PositionAccuracy,[Longitude] = @Longitude,[Latitude] = @Latitude,[CourseOverGround] = @CourseOverGround,[TrueHeading] = @TrueHeading,[Timestamp] = @Timestamp,[ManeuverIndicator] = @ManeuverIndicator,[Spare] = @Spare,[Raim] = @Raim,[RadioStatus] = @RadioStatus
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU11900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisPositionReportForLongRangeApplicationsMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU12000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisPositionReportForLongRangeApplicationsMessage] SET [PositionAccuracy] = @PositionAccuracy,[Raim] = @Raim,[NavigationStatus] = @NavigationStatus,[Longitude] = @Longitude,[Latitude] = @Latitude,[SpeedOverGround] = @SpeedOverGround,[CourseOverGround] = @CourseOverGround,[GnssPositionStatus] = @GnssPositionStatus,[Spare] = @Spare
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU12000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisSafetyRelatedAcknowledgmentMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU12100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisSafetyRelatedAcknowledgmentMessage] SET [Spare] = @Spare,[SequenceNumber1] = @SequenceNumber1,[Mmsi1] = @Mmsi1,[SequenceNumber2] = @SequenceNumber2,[Mmsi2] = @Mmsi2,[SequenceNumber3] = @SequenceNumber3,[Mmsi3] = @Mmsi3,[SequenceNumber4] = @SequenceNumber4,[Mmsi4] = @Mmsi4
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU12100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisStandardClassBCsPositionReportMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU12200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisStandardClassBCsPositionReportMessage] SET [Reserved] = @Reserved,[SpeedOverGround] = @SpeedOverGround,[PositionAccuracy] = @PositionAccuracy,[Longitude] = @Longitude,[Latitude] = @Latitude,[CourseOverGround] = @CourseOverGround,[TrueHeading] = @TrueHeading,[Timestamp] = @Timestamp,[RegionalReserved] = @RegionalReserved,[IsCsUnit] = @IsCsUnit,[HasDisplay] = @HasDisplay,[HasDscCapability] = @HasDscCapability,[Band] = @Band,[CanAcceptMessage22] = @CanAcceptMessage22,[Assigned] = @Assigned,[Raim] = @Raim,[RadioStatus] = @RadioStatus
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU12200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisStandardSarAircraftPositionReportMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU12300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisStandardSarAircraftPositionReportMessage] SET [Altitude] = @Altitude,[SpeedOverGround] = @SpeedOverGround,[PositionAccuracy] = @PositionAccuracy,[Longitude] = @Longitude,[Latitude] = @Latitude,[CourseOverGround] = @CourseOverGround,[Timestamp] = @Timestamp,[Reserved] = @Reserved,[DataTerminalReady] = @DataTerminalReady,[Spare] = @Spare,[Assigned] = @Assigned,[Raim] = @Raim,[RadioStatus] = @RadioStatus
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU12300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisStaticAndVoyageRelatedDataMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU12400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisStaticAndVoyageRelatedDataMessage] SET [AisVersion] = @AisVersion,[ImoNumber] = @ImoNumber,[Callsign] = @Callsign,[ShipName] = @ShipName,[ShipType] = @ShipType,[DimensionToBow] = @DimensionToBow,[DimensionToStern] = @DimensionToStern,[DimensionToPort] = @DimensionToPort,[DimensionToStarboard] = @DimensionToStarboard,[PositionFixType] = @PositionFixType,[EstimatedTimeOfArrival] = @EstimatedTimeOfArrival,[Draught] = @Draught,[Destination] = @Destination,[DataTerminalReady] = @DataTerminalReady,[Spare] = @Spare
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU12400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisStaticDataReportMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @PartNumber [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU12500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisStaticDataReportMessage] SET [PartNumber] = @PartNumber
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU12500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisStaticDataReportPartAMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU12600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisStaticDataReportMessage] SET [PartNumber] = @PartNumber
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [AisStaticDataReportPartAMessage] SET [ShipName] = @ShipName,[Spare] = @Spare
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU12600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisStaticDataReportPartBMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU12700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisStaticDataReportMessage] SET [PartNumber] = @PartNumber
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [AisStaticDataReportPartBMessage] SET [ShipType] = @ShipType,[VendorId] = @VendorId,[UnitModelCode] = @UnitModelCode,[SerialNumber] = @SerialNumber,[Callsign] = @Callsign,[DimensionToBow] = @DimensionToBow,[DimensionToStern] = @DimensionToStern,[DimensionToPort] = @DimensionToPort,[DimensionToStarboard] = @DimensionToStarboard,[MothershipMmsi] = @MothershipMmsi,[PositionFixType] = @PositionFixType,[Spare] = @Spare
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU12700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisUtcAndDateInquiryMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @AisDevice [uniqueidentifier],
  @ReceivedTimestamp [bigint],
  @MessageSequenceNumber [bigint],
  @Repeat [int],
  @Mmsi [uniqueidentifier],
  @Spare1 [int],
  @DestinationMmsi [int],
  @Spare2 [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU12800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisUtcAndDateInquiryMessage] SET [Spare1] = @Spare1,[DestinationMmsi] = @DestinationMmsi,[Spare2] = @Spare2
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU12800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisUtcAndDateResponseMessageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU12900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AisMessage] SET [RowVersion] = [RowVersion] + 1,[AisDevice] = @AisDevice,[ReceivedTimestamp] = @ReceivedTimestamp,[MessageSequenceNumber] = @MessageSequenceNumber,[Repeat] = @Repeat,[Mmsi] = @Mmsi
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisUtcAndDateResponseMessage] SET [Datetime] = @Datetime,[PositionAccuracy] = @PositionAccuracy,[Longitude] = @Longitude,[Latitude] = @Latitude,[PositionFixType] = @PositionFixType,[Spare] = @Spare,[Raim] = @Raim,[RadioStatus] = @RadioStatus
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU12900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AlarmStateChangeUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Alarm [uniqueidentifier],
  @Timestamp [bigint],
  @State [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU13000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [AlarmStateChange] SET [RowVersion] = [RowVersion] + 1,[Alarm] = @Alarm,[Timestamp] = @Timestamp,[State] = @State
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU13000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BaseStationTypeUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU13100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [BaseStationType] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU13100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BinaryTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [varbinary](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU13200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [BinaryTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU13200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BookmarkUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @View [uniqueidentifier],
  @Name [nvarchar](127),
  @Timestamp [bigint],
  @Latitude [float](53),
  @Longitude [float](53),
  @ZoomLevel [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU13300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Bookmark] SET [RowVersion] = [RowVersion] + 1,[View] = @View,[Name] = @Name,[Timestamp] = @Timestamp,[Latitude] = @Latitude,[Longitude] = @Longitude,[ZoomLevel] = @ZoomLevel
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU13300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BooleanTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [bit]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU13400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [BooleanTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU13400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ByteTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [tinyint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU13500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [ByteTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU13500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU13600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU13600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandAbsoluteMoveUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU13700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandAbsoluteMove] SET [PositionPanTiltMode] = @PositionPanTiltMode,[PanAngle] = @PanAngle,[TiltAngle] = @TiltAngle,[PositionFocalLengthMode] = @PositionFocalLengthMode,[FocalLength] = @FocalLength,[SpeedPanTiltMode] = @SpeedPanTiltMode,[PanSpeed] = @PanSpeed,[TiltSpeed] = @TiltSpeed,[SpeedFocalLengthMode] = @SpeedFocalLengthMode,[ZoomSpeed] = @ZoomSpeed
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU13700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandAdjustPanTiltZoomUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU13800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandAdjustPanTiltZoom] SET [X] = @X,[Y] = @Y,[Z] = @Z
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU13800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandContinuousMoveUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU13900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandContinuousMove] SET [Normalized] = @Normalized,[PanVelocity] = @PanVelocity,[TiltVelocity] = @TiltVelocity,[ZoomVelocity] = @ZoomVelocity,[Duration] = @Duration
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU13900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandGeoMoveUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU14000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandGeoMove] SET [Latitude] = @Latitude,[Longitude] = @Longitude,[Altitude] = @Altitude,[ViewportWidth] = @ViewportWidth,[ViewportHeight] = @ViewportHeight
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU14000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandRelativeMoveUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU14100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandRelativeMove] SET [Normalized] = @Normalized,[PanAngle] = @PanAngle,[TiltAngle] = @TiltAngle,[FocalLength] = @FocalLength,[PanSpeed] = @PanSpeed,[TiltSpeed] = @TiltSpeed,[ZoomSpeed] = @ZoomSpeed
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU14100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandReleasePTZOwnershipUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU14200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU14200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandRequestPTZOwnershipUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU14300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU14300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandSetAutoFocusUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Enabled [bit]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU14400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandSetAutoFocus] SET [Enabled] = @Enabled
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU14400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandSetBlackAndWhiteUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Enabled [bit]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU14500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandSetBlackAndWhite] SET [Enabled] = @Enabled
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU14500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandSetFollowedUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @TrackId [uniqueidentifier],
  @Reason [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU14600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandSetFollowed] SET [TrackId] = @TrackId,[Reason] = @Reason
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU14600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandSetInfraRedLampUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Enabled [bit]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU14700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandSetInfraRedLamp] SET [Enabled] = @Enabled
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU14700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandSetWasherUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Enabled [bit]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU14800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandSetWasher] SET [Enabled] = @Enabled
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU14800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandSetWiperUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @Enabled [bit]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU14900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandSetWiper] SET [Enabled] = @Enabled
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU14900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandStopUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier],
  @PanTilt [bit],
  @Zoom [bit]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU15000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommand] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CameraCommandStop] SET [PanTilt] = @PanTilt,[Zoom] = @Zoom
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU15000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandReplyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU15100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraCommandReply] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message,[PanAngle] = @PanAngle,[TiltAngle] = @TiltAngle,[FocalLength] = @FocalLength
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU15100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU15200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraConfiguration] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp,[CameraControlProtocol] = @CameraControlProtocol,[CameraURL] = @CameraURL,[ConfigurationURL] = @ConfigurationURL,[UserName] = @UserName,[Password] = @Password,[UseRtspUriOverride] = @UseRtspUriOverride,[RtspUriOverride] = @RtspUriOverride,[Latitude] = @Latitude,[Longitude] = @Longitude,[Altitude] = @Altitude,[UseRelativePosition] = @UseRelativePosition,[PanTiltMode] = @PanTiltMode,[MinTiltAngle] = @MinTiltAngle,[MaxTiltAngle] = @MaxTiltAngle,[MinTiltScaleAngle] = @MinTiltScaleAngle,[MaxTiltScaleAngle] = @MaxTiltScaleAngle,[UseReverseTiltAngle] = @UseReverseTiltAngle,[UseReverseNormalizedTiltAngle] = @UseReverseNormalizedTiltAngle,[MinTiltVelocity] = @MinTiltVelocity,[MaxTiltVelocity] = @MaxTiltVelocity,[MinTiltSpeed] = @MinTiltSpeed,[MaxTiltSpeed] = @MaxTiltSpeed,[MinPanAngle] = @MinPanAngle,[MaxPanAngle] = @MaxPanAngle,[MinPanScaleAngle] = @MinPanScaleAngle,[MaxPanScaleAngle] = @MaxPanScaleAngle,[UseReversePanAngle] = @UseReversePanAngle,[UseReverseNormalizedPanAngle] = @UseReverseNormalizedPanAngle,[MinPanVelocity] = @MinPanVelocity,[MaxPanVelocity] = @MaxPanVelocity,[MinPanSpeed] = @MinPanSpeed,[MaxPanSpeed] = @MaxPanSpeed,[FocalLengthMode] = @FocalLengthMode,[MinFocalLength] = @MinFocalLength,[MaxFocalLength] = @MaxFocalLength,[MinFocalLengthScale] = @MinFocalLengthScale,[MaxFocalLengthScale] = @MaxFocalLengthScale,[MinZoomVelocity] = @MinZoomVelocity,[MaxZoomVelocity] = @MaxZoomVelocity,[MinZoomSpeed] = @MinZoomSpeed,[MaxZoomSpeed] = @MaxZoomSpeed,[ImageSensorWidth] = @ImageSensorWidth,[ImageSensorHeight] = @ImageSensorHeight,[HomePanAngle] = @HomePanAngle,[HomeTiltAngle] = @HomeTiltAngle,[HomeFocalLength] = @HomeFocalLength,[PanOffset] = @PanOffset,[TiltOffset] = @TiltOffset,[AimAltitude] = @AimAltitude,[MinimumTargetWidth] = @MinimumTargetWidth,[TargetLockTimeout] = @TargetLockTimeout,[UpdateStatusInterval] = @UpdateStatusInterval,[ReadTimeout] = @ReadTimeout,[MoveCommandStatusDelay] = @MoveCommandStatusDelay,[PtzProfileName] = @PtzProfileName,[PtzConfigurationToken] = @PtzConfigurationToken,[VideoSourceToken] = @VideoSourceToken
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU15200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraPanCalibrationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU15300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraPanCalibration] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU15300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraPanCalibrationValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @PanCalibration [uniqueidentifier],
  @PanAngle [float](53),
  @PanOffset [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU15400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraPanCalibrationValue] SET [RowVersion] = [RowVersion] + 1,[PanCalibration] = @PanCalibration,[PanAngle] = @PanAngle,[PanOffset] = @PanOffset
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU15400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraStatusUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU15500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraStatus] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Track] = @Track,[Timestamp] = @Timestamp,[PositionPanTiltMode] = @PositionPanTiltMode,[PanAngle] = @PanAngle,[TiltAngle] = @TiltAngle,[PositionFocalLengthMode] = @PositionFocalLengthMode,[FocalLength] = @FocalLength,[PanTiltMoveStatus] = @PanTiltMoveStatus,[ZoomMoveStatus] = @ZoomMoveStatus,[VelocityPanTiltMode] = @VelocityPanTiltMode,[PanVelocity] = @PanVelocity,[TiltVelocity] = @TiltVelocity,[VelocityFocalLengthMode] = @VelocityFocalLengthMode,[ZoomVelocity] = @ZoomVelocity,[ActiveFeatures] = @ActiveFeatures,[Error] = @Error
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU15500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraTiltCalibrationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU15600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraTiltCalibration] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU15600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraTiltCalibrationValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @TiltCalibration [uniqueidentifier],
  @PanAngle [float](53),
  @TiltOffset [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU15700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraTiltCalibrationValue] SET [RowVersion] = [RowVersion] + 1,[TiltCalibration] = @TiltCalibration,[PanAngle] = @PanAngle,[TiltOffset] = @TiltOffset
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU15700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraZoomCalibrationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Camera [uniqueidentifier],
  @Timestamp [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU15800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraZoomCalibration] SET [RowVersion] = [RowVersion] + 1,[Camera] = @Camera,[Timestamp] = @Timestamp
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU15800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraZoomCalibrationValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ZoomCalibration [uniqueidentifier],
  @FocalLength [float](53),
  @FocalLengthOffset [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU15900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CameraZoomCalibrationValue] SET [RowVersion] = [RowVersion] + 1,[ZoomCalibration] = @ZoomCalibration,[FocalLength] = @FocalLength,[FocalLengthOffset] = @FocalLengthOffset
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU15900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CatalogUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU16100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU16100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ElementUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @ElementType [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU16200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Element] SET [ElementType] = @ElementType
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU16200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CollectionInfoUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Count [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU16300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CollectionInfo] SET [RowVersion] = [RowVersion] + 1,[Count] = @Count
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU16300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CountryUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127),
  @Code [int],
  @Alpha2 [nvarchar](2),
  @Alpha3 [nvarchar](3)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU16400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Country] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name,[Code] = @Code,[Alpha2] = @Alpha2,[Alpha3] = @Alpha3
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU16400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CursorInfoUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @TypeCode [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU16500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [CursorInfo] SET [RowVersion] = [RowVersion] + 1,[TypeCode] = @TypeCode
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU16500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU16600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [DateTimeTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU16600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DeviceHostUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU16700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [DeviceHost] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU16700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DeviceHostConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Host [uniqueidentifier],
  @Timestamp [bigint],
  @Hostname [nvarchar](127),
  @Port [int],
  @QueueName [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU16800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [DeviceHostConfiguration] SET [RowVersion] = [RowVersion] + 1,[Host] = @Host,[Timestamp] = @Timestamp,[Hostname] = @Hostname,[Port] = @Port,[QueueName] = @QueueName
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU16800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DoubleTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU16900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [DoubleTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU16900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [FacilityTypeUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU17000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [FacilityType] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU17000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GeoPosition2DTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Latitude [float](53),
  @Longitude [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU17100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [GeoPosition2DTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Latitude] = @Latitude,[Longitude] = @Longitude
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU17100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GeoPosition3DTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Latitude [float](53),
  @Longitude [float](53),
  @Altitude [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU17200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [GeoPosition3DTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Latitude] = @Latitude,[Longitude] = @Longitude,[Altitude] = @Altitude
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU17200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GNSSDeviceCommandUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @GNSSDevice [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU17300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [GNSSDeviceCommand] SET [RowVersion] = [RowVersion] + 1,[GNSSDevice] = @GNSSDevice,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU17300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GNSSDeviceCommandReplyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @GNSSDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU17400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [GNSSDeviceCommandReply] SET [RowVersion] = [RowVersion] + 1,[GNSSDevice] = @GNSSDevice,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU17400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GNSSDeviceConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU17500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [GNSSDeviceConfiguration] SET [RowVersion] = [RowVersion] + 1,[GNSSDevice] = @GNSSDevice,[Timestamp] = @Timestamp,[DefaultLatitude] = @DefaultLatitude,[DefaultLongitude] = @DefaultLongitude,[DefaultAltitude] = @DefaultAltitude,[LatitudeOffset] = @LatitudeOffset,[LongitudeOffset] = @LongitudeOffset,[AltitudeOffset] = @AltitudeOffset
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU17500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GuidTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU17600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [GuidTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU17600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroDeviceCommandUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @GyroDevice [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU17700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [GyroDeviceCommand] SET [RowVersion] = [RowVersion] + 1,[GyroDevice] = @GyroDevice,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU17700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroDeviceCommandReplyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @GyroDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU17800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [GyroDeviceCommandReply] SET [RowVersion] = [RowVersion] + 1,[GyroDevice] = @GyroDevice,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU17800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroDeviceConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU17900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [GyroDeviceConfiguration] SET [RowVersion] = [RowVersion] + 1,[GyroDevice] = @GyroDevice,[Timestamp] = @Timestamp,[DefaultHeadingTrueNorth] = @DefaultHeadingTrueNorth,[DefaultMagneticTrueNorth] = @DefaultMagneticTrueNorth,[HeadingTrueNorthOffset] = @HeadingTrueNorthOffset,[HeadingMagneticNorthOffset] = @HeadingMagneticNorthOffset,[PitchTransducerName] = @PitchTransducerName,[RollTransducerName] = @RollTransducerName
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU17900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CallsignUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Identifier [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU18100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Identity] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Callsign] SET [Identifier] = @Identifier
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU18100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [InternationalMaritimeOrganizationNumberUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Identifier [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU18200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Identity] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [InternationalMaritimeOrganizationNumber] SET [Identifier] = @Identifier
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU18200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MaritimeMobileServiceIdentityUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Identifier [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU18300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Identity] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [MaritimeMobileServiceIdentity] SET [Identifier] = @Identifier
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU18300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [NameUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Text [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU18400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Identity] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Name] SET [Text] = @Text
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU18400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int16TimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [smallint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU18500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Int16TimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU18500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int32TimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU18600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Int32TimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU18600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int64TimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU18700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Int64TimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU18700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BaseStationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127),
  @Type [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU18900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [BaseStation] SET [Name] = @Name,[Type] = @Type
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU18900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraDeviceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU19100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Device] SET [Host] = @Host,[Name] = @Name,[Description] = @Description,[EnabledTimeseries] = @EnabledTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU19100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GNSSDeviceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier],
  @LatitudeTimeseries [uniqueidentifier],
  @LongitudeTimeseries [uniqueidentifier],
  @AltitudeTimeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU19200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Device] SET [Host] = @Host,[Name] = @Name,[Description] = @Description,[EnabledTimeseries] = @EnabledTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GNSSDevice] SET [LatitudeTimeseries] = @LatitudeTimeseries,[LongitudeTimeseries] = @LongitudeTimeseries,[AltitudeTimeseries] = @AltitudeTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU19200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroDeviceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU19300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Device] SET [Host] = @Host,[Name] = @Name,[Description] = @Description,[EnabledTimeseries] = @EnabledTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GyroDevice] SET [HeadingTrueNorthTimeseries] = @HeadingTrueNorthTimeseries,[HeadingMagneticNorthTimeseries] = @HeadingMagneticNorthTimeseries,[PitchTimeseries] = @PitchTimeseries,[RateOfTurnTimeseries] = @RateOfTurnTimeseries,[RollTimeseries] = @RollTimeseries,[CourseTimeseries] = @CourseTimeseries,[SpeedTimeseries] = @SpeedTimeseries,[GNSSDevice] = @GNSSDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU19300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputDeviceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU19400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Device] SET [Host] = @Host,[Name] = @Name,[Description] = @Description,[EnabledTimeseries] = @EnabledTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU19400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [OilSpillDetectorDeviceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU19500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Device] SET [Host] = @Host,[Name] = @Name,[Description] = @Description,[EnabledTimeseries] = @EnabledTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU19500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadioDeviceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU19600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Device] SET [Host] = @Host,[Name] = @Name,[Description] = @Description,[EnabledTimeseries] = @EnabledTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU19600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomeDeviceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU19700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Device] SET [Host] = @Host,[Name] = @Name,[Description] = @Description,[EnabledTimeseries] = @EnabledTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadomeDevice] SET [Radar] = @Radar,[PressureTimeseries] = @PressureTimeseries,[TemperatureTimeseries] = @TemperatureTimeseries,[DewPointTimeseries] = @DewPointTimeseries,[StatusTimeseries] = @StatusTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU19700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisDeviceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Host [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @EnabledTimeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU19900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Device] SET [Host] = @Host,[Name] = @Name,[Description] = @Description,[EnabledTimeseries] = @EnabledTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU19900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarDeviceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU20000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Device] SET [Host] = @Host,[Name] = @Name,[Description] = @Description,[EnabledTimeseries] = @EnabledTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarDevice] SET [SaveSettingsTimeseries] = @SaveSettingsTimeseries,[PowerOnTimeseries] = @PowerOnTimeseries,[TrackingOnTimeseries] = @TrackingOnTimeseries,[RadarPulseTimeseries] = @RadarPulseTimeseries,[TuningTimeseries] = @TuningTimeseries,[BlankSector1Timeseries] = @BlankSector1Timeseries,[Sector1StartTimeseries] = @Sector1StartTimeseries,[Sector1EndTimeseries] = @Sector1EndTimeseries,[BlankSector2Timeseries] = @BlankSector2Timeseries,[Sector2StartTimeseries] = @Sector2StartTimeseries,[Sector2EndTimeseries] = @Sector2EndTimeseries,[EnableAutomaticFrequencyControlTimeseries] = @EnableAutomaticFrequencyControlTimeseries,[AzimuthOffsetTimeseries] = @AzimuthOffsetTimeseries,[EnableSensitivityTimeControlTimeseries] = @EnableSensitivityTimeControlTimeseries,[AutomaticSensitivityTimeControlTimeseries] = @AutomaticSensitivityTimeControlTimeseries,[SensitivityTimeControlLevelTimeseries] = @SensitivityTimeControlLevelTimeseries,[EnableFastTimeConstantTimeseries] = @EnableFastTimeConstantTimeseries,[FastTimeConstantLevelTimeseries] = @FastTimeConstantLevelTimeseries,[FastTimeConstantModeTimeseries] = @FastTimeConstantModeTimeseries,[LatitudeTimeseries] = @LatitudeTimeseries,[LongitudeTimeseries] = @LongitudeTimeseries,[Radome] = @Radome,[GNSSDevice] = @GNSSDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU20000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationDeviceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU20100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Device] SET [Host] = @Host,[Name] = @Name,[Description] = @Description,[EnabledTimeseries] = @EnabledTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [WeatherStationDevice] SET [BarometricPressureTimeseries] = @BarometricPressureTimeseries,[AirTemperatureTimeseries] = @AirTemperatureTimeseries,[WaterTemperatureTimeseries] = @WaterTemperatureTimeseries,[RelativeHumidityTimeseries] = @RelativeHumidityTimeseries,[AbsoluteHumidityTimeseries] = @AbsoluteHumidityTimeseries,[DewPointTimeseries] = @DewPointTimeseries,[WindDirectionTimeseries] = @WindDirectionTimeseries,[WindSpeedTimeseries] = @WindSpeedTimeseries,[Gyro] = @Gyro
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU20100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [FacilityUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127),
  @Type [uniqueidentifier],
  @Longitude [float](53),
  @Latitude [float](53),
  @Altitude [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU20200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Facility] SET [Name] = @Name,[Type] = @Type,[Longitude] = @Longitude,[Latitude] = @Latitude,[Altitude] = @Altitude
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU20200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AircraftUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127),
  @Type [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU20400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Aircraft] SET [Name] = @Name,[Type] = @Type
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU20400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisAidToNavigationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU20500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [AisAidToNavigation] SET [Name] = @Name,[MMSI] = @MMSI,[NavigationalAidType] = @NavigationalAidType,[Position] = @Position,[IsVirtual] = @IsVirtual,[ToBow] = @ToBow,[ToStern] = @ToStern,[ToPort] = @ToPort,[ToStarboard] = @ToStarboard,[OffPositionTimeseries] = @OffPositionTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU20500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [VehicleUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127),
  @Type [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU20600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Vehicle] SET [Name] = @Name,[Type] = @Type
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU20600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [VesselUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU20700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Item] SET [RowVersion] = [RowVersion] + 1
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Vessel] SET [Name] = @Name,[Type] = @Type,[ToBow] = @ToBow,[ToStern] = @ToStern,[ToPort] = @ToPort,[ToStarboard] = @ToStarboard,[DraughtTimeseries] = @DraughtTimeseries,[PersonsOnBoardTimeseries] = @PersonsOnBoardTimeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU20700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ItemIdentityLinkUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Item [uniqueidentifier],
  @Identity [uniqueidentifier],
  @Start [bigint],
  @End [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU20800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [ItemIdentityLink] SET [RowVersion] = [RowVersion] + 1,[Item] = @Item,[Identity] = @Identity,[Start] = @Start,[End] = @End
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU20800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ItemParentChildLinkUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Parent [uniqueidentifier],
  @Child [uniqueidentifier],
  @Timestamp [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU20900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [ItemParentChildLink] SET [RowVersion] = [RowVersion] + 1,[Parent] = @Parent,[Child] = @Child,[Timestamp] = @Timestamp
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU20900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputDeviceCommandUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @LineInputDevice [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU21000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LineInputDeviceCommand] SET [RowVersion] = [RowVersion] + 1,[LineInputDevice] = @LineInputDevice,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU21000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputDeviceCommandReplyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @LineInputDevice [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU21100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LineInputDeviceCommandReply] SET [RowVersion] = [RowVersion] + 1,[LineInputDevice] = @LineInputDevice,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU21100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputDeviceConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU21200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LineInputDeviceConfiguration] SET [RowVersion] = [RowVersion] + 1,[LineInputDevice] = @LineInputDevice,[Timestamp] = @Timestamp,[StoreReceivedSentences] = @StoreReceivedSentences,[StoreSentMessages] = @StoreSentMessages,[StoreUnsentMessages] = @StoreUnsentMessages,[NMEA] = @NMEA,[StrictNMEA] = @StrictNMEA,[ConnectionType] = @ConnectionType,[UdpReceivePort] = @UdpReceivePort,[UdpSendHostname] = @UdpSendHostname,[UdpSendPort] = @UdpSendPort,[TcpHostname] = @TcpHostname,[TcpPort] = @TcpPort,[UseHttpLogin] = @UseHttpLogin,[LoginHostname] = @LoginHostname,[LoginPort] = @LoginPort,[UserName] = @UserName,[Password] = @Password,[ComPort] = @ComPort,[BaudRate] = @BaudRate,[DataBits] = @DataBits,[DiscardNull] = @DiscardNull,[DtrEnable] = @DtrEnable,[Handshake] = @Handshake,[NewLine] = @NewLine,[Parity] = @Parity,[ParityReplace] = @ParityReplace,[ReadBufferSize] = @ReadBufferSize,[ReadTimeout] = @ReadTimeout,[ReceivedBytesThreshold] = @ReceivedBytesThreshold,[RtsEnable] = @RtsEnable,[StopBits] = @StopBits,[WriteBufferSize] = @WriteBufferSize,[WriteTimeout] = @WriteTimeout,[PairedComPort] = @PairedComPort
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU21200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputMessageRoutingUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @LineInputDevice [uniqueidentifier],
  @Type [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU21300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LineInputMessageRouting] SET [RowVersion] = [RowVersion] + 1,[LineInputDevice] = @LineInputDevice,[Type] = @Type
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU21300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputMessageRoutingDestinationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Routing [uniqueidentifier],
  @Listener [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU21400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LineInputMessageRoutingDestination] SET [RowVersion] = [RowVersion] + 1,[Routing] = @Routing,[Listener] = @Listener
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU21400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputWhiteListEntryUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @LineInputDevice [uniqueidentifier],
  @HostName [nvarchar](128),
  @Port [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU21500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LineInputWhiteListEntry] SET [RowVersion] = [RowVersion] + 1,[LineInputDevice] = @LineInputDevice,[HostName] = @HostName,[Port] = @Port
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU21500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogApplicationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127),
  @Description [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU21600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LogApplication] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU21600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogApplicationConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU21700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LogApplicationConfiguration] SET [RowVersion] = [RowVersion] + 1,[Application] = @Application,[Timestamp] = @Timestamp,[Finest] = @Finest,[Finer] = @Finer,[Fine] = @Fine,[Info] = @Info,[Notice] = @Notice,[Warn] = @Warn,[Error] = @Error,[Severe] = @Severe,[Critical] = @Critical,[Alert] = @Alert,[Fatal] = @Fatal,[Emergency] = @Emergency
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU21700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogHostUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ComputerName [nvarchar](127),
  @Description [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU21800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LogHost] SET [RowVersion] = [RowVersion] + 1,[ComputerName] = @ComputerName,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU21800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogHostConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU21900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LogHostConfiguration] SET [RowVersion] = [RowVersion] + 1,[Host] = @Host,[Timestamp] = @Timestamp,[Finest] = @Finest,[Finer] = @Finer,[Fine] = @Fine,[Info] = @Info,[Notice] = @Notice,[Warn] = @Warn,[Error] = @Error,[Severe] = @Severe,[Critical] = @Critical,[Alert] = @Alert,[Fatal] = @Fatal,[Emergency] = @Emergency
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU21900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogLocationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @FileName [nvarchar](260),
  @LineNumber [int],
  @Namespace [nvarchar](512),
  @ClassName [nvarchar](512),
  @MethodName [nvarchar](255)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU22000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LogLocation] SET [RowVersion] = [RowVersion] + 1,[FileName] = @FileName,[LineNumber] = @LineNumber,[Namespace] = @Namespace,[ClassName] = @ClassName,[MethodName] = @MethodName
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU22000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogProcessUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Application [uniqueidentifier],
  @Host [uniqueidentifier],
  @Started [bigint],
  @Stopped [bigint],
  @ProcessId [bigint],
  @Path [nvarchar](max),
  @Identity [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU22100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LogProcess] SET [RowVersion] = [RowVersion] + 1,[Application] = @Application,[Host] = @Host,[Started] = @Started,[Stopped] = @Stopped,[ProcessId] = @ProcessId,[Path] = @Path,[Identity] = @Identity
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU22100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogRecordUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU22200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LogRecord] SET [RowVersion] = [RowVersion] + 1,[Thread] = @Thread,[SequenceNumber] = @SequenceNumber,[Level] = @Level,[Timestamp] = @Timestamp,[Depth] = @Depth,[Location] = @Location,[Message] = @Message,[ExceptionString] = @ExceptionString,[PropertiesData] = @PropertiesData
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU22200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogThreadUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Process [uniqueidentifier],
  @Started [bigint],
  @Stopped [bigint],
  @ThreadId [bigint],
  @Name [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU22300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LogThread] SET [RowVersion] = [RowVersion] + 1,[Process] = @Process,[Started] = @Started,[Stopped] = @Stopped,[ThreadId] = @ThreadId,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU22300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogTraceEntryUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Thread [uniqueidentifier],
  @SequenceNumber [bigint],
  @Location [uniqueidentifier],
  @Depth [int],
  @Entered [bigint],
  @Ended [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU22400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [LogTraceEntry] SET [RowVersion] = [RowVersion] + 1,[Thread] = @Thread,[SequenceNumber] = @SequenceNumber,[Location] = @Location,[Depth] = @Depth,[Entered] = @Entered,[Ended] = @Ended
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU22400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MapElementUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU22500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [MapElement] SET [RowVersion] = [RowVersion] + 1,[Item] = @Item,[ElementType] = @ElementType,[Latitude] = @Latitude,[Longitude] = @Longitude,[Angle] = @Angle,[Left] = @Left,[Top] = @Top,[Width] = @Width,[Height] = @Height,[Label] = @Label,[Data] = @Data
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU22500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MapInfoUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU22600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [MapInfo] SET [RowVersion] = [RowVersion] + 1,[Scale] = @Scale,[Latitude] = @Latitude,[Longitude] = @Longitude,[NorthWestLatitude] = @NorthWestLatitude,[NorthWestLongitude] = @NorthWestLongitude,[SouthEastLatitude] = @SouthEastLatitude,[SouthEastLongitude] = @SouthEastLongitude,[Image] = @Image
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU22600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MapServiceOptionsUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timestamp [bigint],
  @IpAddress [nvarchar](127),
  @Port [int],
  @ImageScaleFactorX [float](53),
  @ImageOffsetX [float](53),
  @ImageScaleFactorY [float](53),
  @ImageOffsetY [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU22700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [MapServiceOptions] SET [RowVersion] = [RowVersion] + 1,[Timestamp] = @Timestamp,[IpAddress] = @IpAddress,[Port] = @Port,[ImageScaleFactorX] = @ImageScaleFactorX,[ImageOffsetX] = @ImageOffsetX,[ImageScaleFactorY] = @ImageScaleFactorY,[ImageOffsetY] = @ImageOffsetY
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU22700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MaritimeIdentificationDigitsUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Code [int],
  @Country [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU22800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [MaritimeIdentificationDigits] SET [RowVersion] = [RowVersion] + 1,[Code] = @Code,[Country] = @Country
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU22800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaProxySessionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Service [uniqueidentifier],
  @Name [nvarchar](128),
  @EnabledTimeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU22900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [MediaProxySession] SET [RowVersion] = [RowVersion] + 1,[Service] = @Service,[Name] = @Name,[EnabledTimeseries] = @EnabledTimeseries
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU22900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaProxySessionFileUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ProxySession [uniqueidentifier],
  @Timestamp [bigint],
  @StreamName [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU23000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [MediaProxySessionFile] SET [RowVersion] = [RowVersion] + 1,[ProxySession] = @ProxySession,[Timestamp] = @Timestamp,[StreamName] = @StreamName
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU23000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaProxySessionOptionsUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU23100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [MediaProxySessionOptions] SET [RowVersion] = [RowVersion] + 1,[ProxySession] = @ProxySession,[Timestamp] = @Timestamp,[SourceStreamUrl] = @SourceStreamUrl,[StreamName] = @StreamName,[Mode] = @Mode,[TunnelOverHTTPPortNumber] = @TunnelOverHTTPPortNumber,[Username] = @Username,[Password] = @Password,[RecorderPortNumber] = @RecorderPortNumber,[SessionType] = @SessionType,[MaxFileTime] = @MaxFileTime,[MaxFileRetention] = @MaxFileRetention,[VideoDirectory] = @VideoDirectory
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU23100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaServiceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @EnabledTimeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU23200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [MediaService] SET [RowVersion] = [RowVersion] + 1,[EnabledTimeseries] = @EnabledTimeseries
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU23200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaServiceOptionsUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @MediaService [uniqueidentifier],
  @Timestamp [bigint],
  @RtspPortNumber [int],
  @HttpPortNumber [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU23300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [MediaServiceOptions] SET [RowVersion] = [RowVersion] + 1,[MediaService] = @MediaService,[Timestamp] = @Timestamp,[RtspPortNumber] = @RtspPortNumber,[HttpPortNumber] = @HttpPortNumber
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU23300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ElementTypeUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Namespace [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU23500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [NamespaceElement] SET [RowVersion] = [RowVersion] + 1,[Namespace] = @Namespace,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU23500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [NamespaceUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Namespace [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU23600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [NamespaceElement] SET [RowVersion] = [RowVersion] + 1,[Namespace] = @Namespace,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU23600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [OilSpillUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @OilSpillDetector [uniqueidentifier],
  @Timestamp [bigint],
  @OilArea [float](53),
  @Shape [varbinary](max),
  @BSI [varbinary](max),
  @Oil [varbinary](max),
  @Trace [varbinary](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU23700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [OilSpill] SET [RowVersion] = [RowVersion] + 1,[OilSpillDetector] = @OilSpillDetector,[Timestamp] = @Timestamp,[OilArea] = @OilArea,[Shape] = @Shape,[BSI] = @BSI,[Oil] = @Oil,[Trace] = @Trace
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU23700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [OilSpillDetectorCommandUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @OilSpillDetector [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU23800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [OilSpillDetectorCommand] SET [RowVersion] = [RowVersion] + 1,[OilSpillDetector] = @OilSpillDetector,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU23800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [OilSpillDetectorCommandReplyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @OilSpillDetector [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU23900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [OilSpillDetectorCommandReply] SET [RowVersion] = [RowVersion] + 1,[OilSpillDetector] = @OilSpillDetector,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU23900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [OilSpillDetectorConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU24000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [OilSpillDetectorConfiguration] SET [RowVersion] = [RowVersion] + 1,[OilSpillDetector] = @OilSpillDetector,[Timestamp] = @Timestamp,[Range] = @Range,[StartAngle] = @StartAngle,[EndAngle] = @EndAngle,[StartRange] = @StartRange,[EndRange] = @EndRange,[UpdateRate] = @UpdateRate,[StatusSendTime] = @StatusSendTime,[DrawBorder] = @DrawBorder,[Colors] = @Colors,[SendToServer] = @SendToServer,[Directory] = @Directory,[TransparentWater] = @TransparentWater,[SavePictures] = @SavePictures,[SendAsTarget] = @SendAsTarget,[WriteLog] = @WriteLog,[TargetFilePrefix] = @TargetFilePrefix,[TargetMMSI] = @TargetMMSI,[Latitude] = @Latitude,[Longitude] = @Longitude,[TestSourceEnabled] = @TestSourceEnabled,[ProxyServer] = @ProxyServer,[UseProxyServer] = @UseProxyServer
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU24000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Position2DTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @X [float](53),
  @Y [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU24100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Position2DTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[X] = @X,[Y] = @Y
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU24100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Position3DTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @X [float](53),
  @Y [float](53),
  @Z [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU24200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Position3DTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[X] = @X,[Y] = @Y,[Z] = @Z
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU24200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ProcessTrackValueResultUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @CreatedNewTrack [bit],
  @TrackId [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU24300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [ProcessTrackValueResult] SET [RowVersion] = [RowVersion] + 1,[CreatedNewTrack] = @CreatedNewTrack,[TrackId] = @TrackId
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU24300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BinaryPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [varbinary](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU24500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [BinaryProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU24500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BooleanPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [bit]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU24600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [BooleanProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU24600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BytePropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [tinyint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU24700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [ByteProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU24700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DateTimePropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU24800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [DateTimeProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU24800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DoublePropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU24900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [DoubleProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU24900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GuidPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU25000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [GuidProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU25000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int16PropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [smallint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU25100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int16Property] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU25100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int32PropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU25200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int32Property] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU25200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int64PropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU25300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int64Property] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU25300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ReferencePropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU25400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [ReferenceProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU25400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SBytePropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [numeric](3,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU25500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [SByteProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU25500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SinglePropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [float](24)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU25600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [SingleProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU25600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [StringPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU25700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [StringProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU25700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BinaryTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU25900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [BinaryTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU25900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BooleanTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU26000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [BooleanTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU26000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ByteTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU26100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [ByteTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU26100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU26200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [DateTimeTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU26200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DoubleTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU26300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [DoubleTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU26300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GuidTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU26400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [GuidTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU26400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int16TimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU26500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int16TimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU26500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int32TimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU26600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int32TimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU26600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int64TimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU26700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int64TimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU26700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU26800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [ReferenceTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU26800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SByteTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU26900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [SByteTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU26900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SingleTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU27000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [SingleTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU27000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [StringTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU27100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [StringTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU27100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU27200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [TimeSpanTimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU27200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt16TimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU27300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt16TimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU27300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt32TimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU27400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt32TimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU27400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt64TimeseriesPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Timeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU27500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt64TimeseriesProperty] SET [Timeseries] = @Timeseries
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU27500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TimeSpanPropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU27600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [TimeSpanProperty] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU27600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt16PropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [numeric](5,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU27700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt16Property] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU27700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt32PropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [numeric](10,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU27800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt32Property] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU27800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt64PropertyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Element [uniqueidentifier],
  @Definition [uniqueidentifier],
  @Value [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU27900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Property] SET [RowVersion] = [RowVersion] + 1,[Element] = @Element,[Definition] = @Definition
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt64Property] SET [Value] = @Value
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU27900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BinaryPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [varbinary](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU28100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [BinaryPropertyDefinition] SET [DefaultValue] = @DefaultValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU28100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BooleanPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [bit]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU28200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [BooleanPropertyDefinition] SET [DefaultValue] = @DefaultValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU28200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BytePropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [tinyint],
  @MinValue [tinyint],
  @MaxValue [tinyint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU28300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [BytePropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU28300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DateTimePropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [nvarchar](127),
  @MinValue [nvarchar](127),
  @MaxValue [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU28400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [DateTimePropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU28400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DoublePropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [float](53),
  @MinValue [float](53),
  @MaxValue [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU28500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [DoublePropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU28500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GuidPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU28600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [GuidPropertyDefinition] SET [DefaultValue] = @DefaultValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU28600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int16PropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [smallint],
  @MinValue [smallint],
  @MaxValue [smallint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU28700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int16PropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU28700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int32PropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [int],
  @MinValue [int],
  @MaxValue [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU28800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int32PropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU28800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int64PropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [bigint],
  @MinValue [bigint],
  @MaxValue [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU28900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int64PropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU28900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ReferencePropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [uniqueidentifier],
  @ReferencedElementType [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU29000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [ReferencePropertyDefinition] SET [DefaultValue] = @DefaultValue,[ReferencedElementType] = @ReferencedElementType
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU29000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SBytePropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [numeric](3,0),
  @MinValue [numeric](3,0),
  @MaxValue [numeric](3,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU29100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [SBytePropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU29100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SinglePropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [float](24),
  @MinValue [float](24),
  @MaxValue [float](24)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU29200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [SinglePropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU29200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [StringPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [nvarchar](127),
  @Pattern [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU29300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [StringPropertyDefinition] SET [DefaultValue] = @DefaultValue,[Pattern] = @Pattern
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU29300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BinaryTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU29500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU29500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BooleanTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU29600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU29600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ByteTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [tinyint],
  @MaxValue [tinyint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU29700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [ByteTimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU29700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [nvarchar](127),
  @MaxValue [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU29800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [DateTimeTimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU29800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DoubleTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [float](53),
  @MaxValue [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU29900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [DoubleTimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU29900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GuidTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU30000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU30000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int16TimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [smallint],
  @MaxValue [smallint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU30100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int16TimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU30100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int32TimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [int],
  @MaxValue [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU30200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int32TimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU30200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int64TimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [bigint],
  @MaxValue [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU30300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Int64TimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU30300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @ReferencedElementType [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU30400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [ReferenceTimeseriesPropertyDefinition] SET [ReferencedElementType] = @ReferencedElementType
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU30400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SByteTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [numeric](3,0),
  @MaxValue [numeric](3,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU30500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [SByteTimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU30500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SingleTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [float](24),
  @MaxValue [float](24)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU30600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [SingleTimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU30600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [StringTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @Pattern [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU30700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [StringTimeseriesPropertyDefinition] SET [Pattern] = @Pattern
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU30700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [bigint],
  @MaxValue [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU30800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [TimeSpanTimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU30800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt16TimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [numeric](5,0),
  @MaxValue [numeric](5,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU30900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt16TimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU30900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt32TimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [numeric](10,0),
  @MaxValue [numeric](10,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU31000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt32TimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU31000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt64TimeseriesPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @MinValue [bigint],
  @MaxValue [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU31100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt64TimeseriesPropertyDefinition] SET [MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU31100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TimeSpanPropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [bigint],
  @MinValue [bigint],
  @MaxValue [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU31200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [TimeSpanPropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU31200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt16PropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [numeric](5,0),
  @MinValue [numeric](5,0),
  @MaxValue [numeric](5,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU31300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt16PropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU31300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt32PropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [numeric](10,0),
  @MinValue [numeric](10,0),
  @MaxValue [numeric](10,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU31400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt32PropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU31400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt64PropertyDefinitionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ElementType [uniqueidentifier],
  @Name [nvarchar](127),
  @Description [nvarchar](max),
  @DefaultValue [bigint],
  @MinValue [bigint],
  @MaxValue [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU31500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [PropertyDefinition] SET [RowVersion] = [RowVersion] + 1,[ElementType] = @ElementType,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [UInt64PropertyDefinition] SET [DefaultValue] = @DefaultValue,[MinValue] = @MinValue,[MaxValue] = @MaxValue
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU31500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarAlarmStatusUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @Type [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU31600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadarAlarmStatus] SET [RowVersion] = [RowVersion] + 1,[Radar] = @Radar,[Timestamp] = @Timestamp,[Type] = @Type
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU31600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarCommandUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU31700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadarCommand] SET [RowVersion] = [RowVersion] + 1,[Radar] = @Radar,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU31700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarCommandGetStatusUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU31800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadarCommand] SET [RowVersion] = [RowVersion] + 1,[Radar] = @Radar,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU31800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarCommandReplyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU31900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadarCommandReply] SET [RowVersion] = [RowVersion] + 1,[Radar] = @Radar,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU31900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarCommandReplyGetStatusUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU32000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadarCommandReply] SET [RowVersion] = [RowVersion] + 1,[Radar] = @Radar,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [RadarCommandReplyGetStatus] SET [AzimuthCount] = @AzimuthCount,[TriggerCount] = @TriggerCount,[RotationCount] = @RotationCount,[Pulse] = @Pulse,[Tx] = @Tx
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU32000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU32100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadarConfiguration] SET [RowVersion] = [RowVersion] + 1,[Radar] = @Radar,[Timestamp] = @Timestamp,[RadarProtocolVersion] = @RadarProtocolVersion,[RadarIPAddress] = @RadarIPAddress,[RadarPort] = @RadarPort,[RadarConfigurationPort] = @RadarConfigurationPort,[SkipMagicTimeout] = @SkipMagicTimeout,[ReadTimeout] = @ReadTimeout,[SynchronizationInterval] = @SynchronizationInterval,[TargetsRefreshRate] = @TargetsRefreshRate,[Range] = @Range,[SectorCount] = @SectorCount,[SectorOffset] = @SectorOffset,[ImageColor] = @ImageColor,[ImageSubstitutionColor] = @ImageSubstitutionColor,[TransparentColor] = @TransparentColor,[ImageScaleFactorX] = @ImageScaleFactorX,[ImageOffsetX] = @ImageOffsetX,[ImageScaleFactorY] = @ImageScaleFactorY,[ImageOffsetY] = @ImageOffsetY,[RadarImageType] = @RadarImageType,[TrackColor] = @TrackColor,[VectorColor] = @VectorColor,[EnableNmea] = @EnableNmea,[NmeaReceiverIPAddress] = @NmeaReceiverIPAddress,[NmeaReceiverPort] = @NmeaReceiverPort,[NmeaReceiverSourceId] = @NmeaReceiverSourceId
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU32100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarImageUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @Depth [numeric](10,0),
  @Resolution [int],
  @Range [int],
  @Image [varbinary](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU32200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadarImage] SET [RowVersion] = [RowVersion] + 1,[Radar] = @Radar,[Timestamp] = @Timestamp,[Depth] = @Depth,[Resolution] = @Resolution,[Range] = @Range,[Image] = @Image
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU32200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarRawTrackTableUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radar [uniqueidentifier],
  @Timestamp [bigint],
  @Count [int],
  @Table [varbinary](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU32300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadarRawTrackTable] SET [RowVersion] = [RowVersion] + 1,[Radar] = @Radar,[Timestamp] = @Timestamp,[Count] = @Count,[Table] = @Table
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU32300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarStatusUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU32400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadarStatus] SET [RowVersion] = [RowVersion] + 1,[Radar] = @Radar,[Timestamp] = @Timestamp,[AzimuthCount] = @AzimuthCount,[TriggerCount] = @TriggerCount,[RotationTime] = @RotationTime,[Pulse] = @Pulse,[Tx] = @Tx,[Tracking] = @Tracking
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU32400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadioCommandUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radio [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU32500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadioCommand] SET [RowVersion] = [RowVersion] + 1,[Radio] = @Radio,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU32500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadioCommandReplyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radio [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU32600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadioCommandReply] SET [RowVersion] = [RowVersion] + 1,[Radio] = @Radio,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU32600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadioConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU32700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadioConfiguration] SET [RowVersion] = [RowVersion] + 1,[Radio] = @Radio,[Timestamp] = @Timestamp,[Longitude] = @Longitude,[Latitude] = @Latitude,[PlaybackUrl] = @PlaybackUrl,[RadioIPAddress] = @RadioIPAddress,[RadioPort] = @RadioPort,[Ed137IPAddress] = @Ed137IPAddress,[Ed137Port] = @Ed137Port
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU32700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomeCommandUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radome [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU32800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadomeCommand] SET [RowVersion] = [RowVersion] + 1,[Radome] = @Radome,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU32800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomeCommandReplyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radome [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU32900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadomeCommandReply] SET [RowVersion] = [RowVersion] + 1,[Radome] = @Radome,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU32900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomeConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Radome [uniqueidentifier],
  @Timestamp [bigint],
  @Interval [bigint],
  @LowPressureLimit [float](53),
  @HighPressureLimit [float](53),
  @LowTemperatureLimit [float](53),
  @HighTemperatureLimit [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU33000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [RadomeConfiguration] SET [RowVersion] = [RowVersion] + 1,[Radome] = @Radome,[Timestamp] = @Timestamp,[Interval] = @Interval,[LowPressureLimit] = @LowPressureLimit,[HighPressureLimit] = @HighPressureLimit,[LowTemperatureLimit] = @LowTemperatureLimit,[HighTemperatureLimit] = @HighTemperatureLimit
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU33000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU33100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [ReferenceTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU33100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SByteTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [numeric](3,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU33200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [SByteTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU33200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SecurityDomainUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127),
  @Description [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU33300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [SecurityDomain] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU33300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SecurityLoginUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Domain [uniqueidentifier],
  @Identity [nvarchar](255),
  @Description [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU33500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [SecurityIdentifier] SET [RowVersion] = [RowVersion] + 1,[Domain] = @Domain,[Identity] = @Identity,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU33500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SecurityRoleUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Domain [uniqueidentifier],
  @Identity [nvarchar](255),
  @Description [nvarchar](max),
  @Name [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU33600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [SecurityIdentifier] SET [RowVersion] = [RowVersion] + 1,[Domain] = @Domain,[Identity] = @Identity,[Description] = @Description
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [SecurityRole] SET [Name] = @Name
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU33600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SecurityIdentifierRoleLinkUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Member [uniqueidentifier],
  @Role [uniqueidentifier],
  @Start [bigint],
  @End [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU33700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [SecurityIdentifierRoleLink] SET [RowVersion] = [RowVersion] + 1,[Member] = @Member,[Role] = @Role,[Start] = @Start,[End] = @End
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU33700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SecurityLoginSessionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Login [uniqueidentifier],
  @FromTime [bigint],
  @ThroughTime [bigint],
  @ClientSession [uniqueidentifier],
  @NotificationQueueName [nvarchar](260),
  @MessageQueueName [nvarchar](260)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU33800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [SecurityLoginSession] SET [RowVersion] = [RowVersion] + 1,[Login] = @Login,[FromTime] = @FromTime,[ThroughTime] = @ThroughTime,[ClientSession] = @ClientSession,[NotificationQueueName] = @NotificationQueueName,[MessageQueueName] = @MessageQueueName
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU33800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SecurityPermissionUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Identifier [uniqueidentifier],
  @Timestamp [bigint],
  @TypeCode [int],
  @CanCreate [bit],
  @CanRead [bit],
  @CanUpdate [bit],
  @CanDelete [bit]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU33900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [SecurityPermission] SET [RowVersion] = [RowVersion] + 1,[Identifier] = @Identifier,[Timestamp] = @Timestamp,[TypeCode] = @TypeCode,[CanCreate] = @CanCreate,[CanRead] = @CanRead,[CanUpdate] = @CanUpdate,[CanDelete] = @CanDelete
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU33900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SingleTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [float](24)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU34000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [SingleTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU34000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [StringTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU34100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [StringTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU34100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BinaryTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU34400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU34400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BooleanTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU34500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU34500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisAidToNavigationOffPositionTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @AidToNavigation [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU34600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [AisAidToNavigationOffPositionTimeseries] SET [AidToNavigation] = @AidToNavigation
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU34600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DeviceEnabledTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Device [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU34700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [DeviceEnabledTimeseries] SET [Device] = @Device
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU34700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarAutomaticSensitivityTimeControlTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU34800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarAutomaticSensitivityTimeControlTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU34800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarBlankSector1TimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU34900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarBlankSector1Timeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU34900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarBlankSector2TimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU35000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarBlankSector2Timeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU35000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarEnableAutomaticFrequencyControlTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU35100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarEnableAutomaticFrequencyControlTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU35100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarEnableFastTimeConstantTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU35200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarEnableFastTimeConstantTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU35200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarEnableSensitivityTimeControlTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU35300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarEnableSensitivityTimeControlTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU35300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarPowerOnTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU35400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarPowerOnTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU35400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarSaveSettingsTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU35500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarSaveSettingsTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU35500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarTrackingTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU35600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarTrackingTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU35600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaProxySessionEnabledTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @ProxySession [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU35700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [MediaProxySessionEnabledTimeseries] SET [ProxySession] = @ProxySession
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU35700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaServiceEnabledTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Service [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU35800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [MediaServiceEnabledTimeseries] SET [Service] = @Service
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU35800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ByteTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU35900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU35900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU36000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU36000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DoubleTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU36100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU36100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GNSSAltitudeTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GNSSDevice [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU36200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GNSSAltitudeTimeseries] SET [GNSSDevice] = @GNSSDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU36200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GNSSLatitudeTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GNSSDevice [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU36300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GNSSLatitudeTimeseries] SET [GNSSDevice] = @GNSSDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU36300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GNSSLongitudeTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GNSSDevice [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU36400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GNSSLongitudeTimeseries] SET [GNSSDevice] = @GNSSDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU36400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroCourseTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU36500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GyroCourseTimeseries] SET [GyroDevice] = @GyroDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU36500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroHeadingMagneticNorthTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU36600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GyroHeadingMagneticNorthTimeseries] SET [GyroDevice] = @GyroDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU36600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroHeadingTrueNorthTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU36700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GyroHeadingTrueNorthTimeseries] SET [GyroDevice] = @GyroDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU36700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroPitchTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU36800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GyroPitchTimeseries] SET [GyroDevice] = @GyroDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU36800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroRateOfTurnTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU36900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GyroRateOfTurnTimeseries] SET [GyroDevice] = @GyroDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU36900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroRollTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU37000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GyroRollTimeseries] SET [GyroDevice] = @GyroDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU37000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroSpeedTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @GyroDevice [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU37100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [GyroSpeedTimeseries] SET [GyroDevice] = @GyroDevice
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU37100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarLatitudeTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU37200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarLatitudeTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU37200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarLongitudeTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU37300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarLongitudeTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU37300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomeDewPointTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radome [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU37400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadomeDewPointTimeseries] SET [Radome] = @Radome
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU37400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomePressureTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radome [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU37500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadomePressureTimeseries] SET [Radome] = @Radome
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU37500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomeTemperatureTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radome [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU37600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadomeTemperatureTimeseries] SET [Radome] = @Radome
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU37600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [VesselDraughtTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Vessel [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU37700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [VesselDraughtTimeseries] SET [Vessel] = @Vessel
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU37700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ViewLatitudeTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @View [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU37800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [ViewLatitudeTimeseries] SET [View] = @View
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU37800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ViewLongitudeTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @View [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU37900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [ViewLongitudeTimeseries] SET [View] = @View
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU37900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ViewZoomLevelTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @View [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU38000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [ViewZoomLevelTimeseries] SET [View] = @View
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU38000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationAbsoluteHumidityTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU38100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [WeatherStationAbsoluteHumidityTimeseries] SET [WeatherStation] = @WeatherStation
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU38100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationAirTemperatureTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU38200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [WeatherStationAirTemperatureTimeseries] SET [WeatherStation] = @WeatherStation
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU38200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationBarometricPressureTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU38300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [WeatherStationBarometricPressureTimeseries] SET [WeatherStation] = @WeatherStation
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU38300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationDewPointTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU38400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [WeatherStationDewPointTimeseries] SET [WeatherStation] = @WeatherStation
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU38400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationRelativeHumidityTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU38500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [WeatherStationRelativeHumidityTimeseries] SET [WeatherStation] = @WeatherStation
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU38500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationWaterTemperatureTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU38600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [WeatherStationWaterTemperatureTimeseries] SET [WeatherStation] = @WeatherStation
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU38600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationWindDirectionTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU38700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [WeatherStationWindDirectionTimeseries] SET [WeatherStation] = @WeatherStation
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU38700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationWindSpeedTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @WeatherStation [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU38800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [WeatherStationWindSpeedTimeseries] SET [WeatherStation] = @WeatherStation
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU38800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GeoPosition2DTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU38900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU38900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisAidToNavigationPositionTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @AidToNavigation [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU39000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [AisAidToNavigationPositionTimeseries] SET [AidToNavigation] = @AidToNavigation
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU39000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GeoPosition3DTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU39100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU39100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GuidTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU39200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU39200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int16TimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU39300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU39300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int32TimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU39400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU39400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarAzimuthOffsetTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU39500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarAzimuthOffsetTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU39500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarFastTimeConstantLevelTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU39600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarFastTimeConstantLevelTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU39600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarFastTimeConstantModeTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU39700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarFastTimeConstantModeTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU39700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarPulseTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU39800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarPulseTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU39800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarSector1EndTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU39900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarSector1EndTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU39900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarSector1StartTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU40000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarSector1StartTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU40000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarSector2EndTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU40100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarSector2EndTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU40100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarSector2StartTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU40200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarSector2StartTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU40200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarSensitivityTimeControlLevelTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU40300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarSensitivityTimeControlLevelTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU40300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarTuningTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radar [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU40400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadarTuningTimeseries] SET [Radar] = @Radar
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU40400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [VesselPersonsOnBoardTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Vessel [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU40500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [VesselPersonsOnBoardTimeseries] SET [Vessel] = @Vessel
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU40500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int64TimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU40600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU40600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Position2DTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU40700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU40700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Position3DTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU40800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU40800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU40900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU40900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SByteTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU41000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU41000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SingleTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU41100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU41100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [StringTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU41200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU41200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU41300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU41300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt16TimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU41400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU41400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt32TimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU41500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU41500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomeStatusTimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint],
  @Radome [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU41600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      UPDATE [RadomeStatusTimeseries] SET [Radome] = @Radome
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU41600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt64TimeseriesUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127),
  @MaxRetention [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU41700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [Timeseries] SET [MaxRetention] = @MaxRetention
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU41700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TimeseriesCatalogUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Catalog [uniqueidentifier],
  @Name [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU41800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesCatalogElement] SET [RowVersion] = [RowVersion] + 1,[Catalog] = @Catalog,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU41800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TimeseriesInfoUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @FirstTimestamp [bigint],
  @LastTimestamp [bigint],
  @Count [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU41900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeseriesInfo] SET [RowVersion] = [RowVersion] + 1,[FirstTimestamp] = @FirstTimestamp,[LastTimestamp] = @LastTimestamp,[Count] = @Count
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU41900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU42000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TimeSpanTimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU42000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackableItemTrackLinkUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Item [uniqueidentifier],
  @Track [uniqueidentifier],
  @Start [bigint],
  @End [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU42100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TrackableItemTrackLink] SET [RowVersion] = [RowVersion] + 1,[Item] = @Item,[Track] = @Track,[Start] = @Start,[End] = @End
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU42100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Tracker [uniqueidentifier],
  @TrackNumber [bigint],
  @Timestamp [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU42300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TrackBase] SET [RowVersion] = [RowVersion] + 1,[Tracker] = @Tracker,[TrackNumber] = @TrackNumber,[Timestamp] = @Timestamp
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU42300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Track3DUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Tracker [uniqueidentifier],
  @TrackNumber [bigint],
  @Timestamp [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU42400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TrackBase] SET [RowVersion] = [RowVersion] + 1,[Tracker] = @Tracker,[TrackNumber] = @TrackNumber,[Timestamp] = @Timestamp
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU42400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackerFilterParametersUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Tracker [uniqueidentifier],
  @Name [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU42500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TrackerFilterParameters] SET [RowVersion] = [RowVersion] + 1,[Tracker] = @Tracker,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU42500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackerFilterParametersConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU42600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TrackerFilterParametersConfiguration] SET [RowVersion] = [RowVersion] + 1,[Parameters] = @Parameters,[Timestamp] = @Timestamp,[UseNaivePredictor] = @UseNaivePredictor,[NumberOfPoints] = @NumberOfPoints,[WindowSize] = @WindowSize,[StabilizeCount] = @StabilizeCount,[MaxBadPoints] = @MaxBadPoints,[ModelType] = @ModelType,[SigmaR] = @SigmaR,[SigmaAcc] = @SigmaAcc,[TauVel] = @TauVel,[TauAcc] = @TauAcc,[DeltaRMin] = @DeltaRMin,[DeltaVMax] = @DeltaVMax,[DeltaAMax] = @DeltaAMax
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU42600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackInfoUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @FirstTimestamp [bigint],
  @LastTimestamp [bigint],
  @Count [bigint],
  @NorthWestLatitude [float](53),
  @NorthWestLongitude [float](53),
  @SouthEastLatitude [float](53),
  @SouthEastLongitude [float](53)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU42700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TrackInfo] SET [RowVersion] = [RowVersion] + 1,[FirstTimestamp] = @FirstTimestamp,[LastTimestamp] = @LastTimestamp,[Count] = @Count,[NorthWestLatitude] = @NorthWestLatitude,[NorthWestLongitude] = @NorthWestLongitude,[SouthEastLatitude] = @SouthEastLatitude,[SouthEastLongitude] = @SouthEastLongitude
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU42700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackingServiceOptionsUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU42800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TrackingServiceOptions] SET [RowVersion] = [RowVersion] + 1,[Timestamp] = @Timestamp,[TimerInterval] = @TimerInterval,[MaxAgeOfCurrentTrackValue] = @MaxAgeOfCurrentTrackValue,[FalseThreshold] = @FalseThreshold,[DistanceThreshold] = @DistanceThreshold,[DistanceUnmergeThreshold] = @DistanceUnmergeThreshold,[UnmergeLatency] = @UnmergeLatency,[KalmanFiltering] = @KalmanFiltering,[MaxCourseDeviation] = @MaxCourseDeviation,[MaxSpeedDeviation] = @MaxSpeedDeviation,[MinimumSpeedThreshold] = @MinimumSpeedThreshold
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU42800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackLinkUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Primary [uniqueidentifier],
  @Secondary [uniqueidentifier],
  @Start [bigint],
  @End [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU42900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TrackLink] SET [RowVersion] = [RowVersion] + 1,[Primary] = @Primary,[Secondary] = @Secondary,[Start] = @Start,[End] = @End
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU42900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU43000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TrackValue] SET [RowVersion] = [RowVersion] + 1,[Track] = @Track,[Timestamp] = @Timestamp,[Flags] = @Flags,[Status] = @Status,[Latitude] = @Latitude,[Longitude] = @Longitude,[Speed] = @Speed,[Course] = @Course,[Heading] = @Heading
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU43000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackValue3DUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU43100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [TrackValue3D] SET [RowVersion] = [RowVersion] + 1,[Track] = @Track,[Timestamp] = @Timestamp,[Flags] = @Flags,[Status] = @Status,[Latitude] = @Latitude,[Longitude] = @Longitude,[Altitude] = @Altitude,[Speed] = @Speed,[Course] = @Course,[RateOfClimb] = @RateOfClimb
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU43100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt16TimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [numeric](5,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU43200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [UInt16TimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU43200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt32TimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [numeric](10,0)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU43300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [UInt32TimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU43300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt64TimeseriesValueUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Timeseries [uniqueidentifier],
  @Timestamp [bigint],
  @Value [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU43400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [UInt64TimeseriesValue] SET [RowVersion] = [RowVersion] + 1,[Timeseries] = @Timeseries,[Timestamp] = @Timestamp,[Value] = @Value
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU43400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [VehicleTypeUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU43500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [VehicleType] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU43500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [VesselTypeUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127),
  @Code [int]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU43600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [VesselType] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name,[Code] = @Code
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU43600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ViewUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Name [nvarchar](127),
  @LatitudeTimeseries [uniqueidentifier],
  @LongitudeTimeseries [uniqueidentifier],
  @ZoomLevelTimeseries [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU43700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [View] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name,[LatitudeTimeseries] = @LatitudeTimeseries,[LongitudeTimeseries] = @LongitudeTimeseries,[ZoomLevelTimeseries] = @ZoomLevelTimeseries
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU43700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ViewCameraLinkUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @View [uniqueidentifier],
  @Camera [uniqueidentifier],
  @Start [bigint],
  @End [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU43800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [ViewCameraLink] SET [RowVersion] = [RowVersion] + 1,[View] = @View,[Camera] = @Camera,[Start] = @Start,[End] = @End
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU43800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ViewTrackerLinkUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @View [uniqueidentifier],
  @Tracker [uniqueidentifier],
  @Start [bigint],
  @End [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU43900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [ViewTrackerLink] SET [RowVersion] = [RowVersion] + 1,[View] = @View,[Tracker] = @Tracker,[Start] = @Start,[End] = @End
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU43900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationCommandUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @WeatherStation [uniqueidentifier],
  @Timestamp [bigint],
  @DeviceCommandSourceType [int],
  @DeviceCommandSourceId [uniqueidentifier],
  @Reply [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU44000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [WeatherStationCommand] SET [RowVersion] = [RowVersion] + 1,[WeatherStation] = @WeatherStation,[Timestamp] = @Timestamp,[DeviceCommandSourceType] = @DeviceCommandSourceType,[DeviceCommandSourceId] = @DeviceCommandSourceId,[Reply] = @Reply
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU44000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationCommandReplyUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @WeatherStation [uniqueidentifier],
  @Timestamp [bigint],
  @Command [uniqueidentifier],
  @Status [int],
  @Message [nvarchar](max)

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU44100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [WeatherStationCommandReply] SET [RowVersion] = [RowVersion] + 1,[WeatherStation] = @WeatherStation,[Timestamp] = @Timestamp,[Command] = @Command,[Status] = @Status,[Message] = @Message
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU44100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationConfigurationUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU44200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [WeatherStationConfiguration] SET [RowVersion] = [RowVersion] + 1,[WeatherStation] = @WeatherStation,[Timestamp] = @Timestamp,[NoDataTimeOut] = @NoDataTimeOut,[SendInterval] = @SendInterval,[Latitude] = @Latitude,[Longitude] = @Longitude,[GyroOffset] = @GyroOffset,[EnableAveraging] = @EnableAveraging,[AveragingInterval] = @AveragingInterval
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU44200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CircularZoneUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU44400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Zone] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name,[Longitude] = @Longitude,[Latitude] = @Latitude,[AlarmType] = @AlarmType,[AlarmTime] = @AlarmTime,[RadarTrackMinimumLifetime] = @RadarTrackMinimumLifetime,[Speed] = @Speed,[StrokeColor] = @StrokeColor,[FillColor] = @FillColor
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [CircularZone] SET [Radius] = @Radius
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU44400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [PolygonZoneUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU44500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Zone] SET [RowVersion] = [RowVersion] + 1,[Name] = @Name,[Longitude] = @Longitude,[Latitude] = @Latitude,[AlarmType] = @AlarmType,[AlarmTime] = @AlarmTime,[RadarTrackMinimumLifetime] = @RadarTrackMinimumLifetime,[Speed] = @Speed,[StrokeColor] = @StrokeColor,[FillColor] = @FillColor
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      UPDATE [PolygonZone] SET [Polygon] = @Polygon
          WHERE [Id] = @Id
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found',16,1);
        END

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU44500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ZoneExceptionsUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @Zone [uniqueidentifier],
  @Timestamp [bigint]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU44600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [ZoneExceptions] SET [RowVersion] = [RowVersion] + 1,[Zone] = @Zone,[Timestamp] = @Timestamp
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU44600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ZoneExceptionsVesselLinkUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
  @ZoneExceptions [uniqueidentifier],
  @Vessel [uniqueidentifier]

AS
  BEGIN
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU44700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [ZoneExceptionsVesselLink] SET [RowVersion] = [RowVersion] + 1,[ZoneExceptions] = @ZoneExceptions,[Vessel] = @Vessel
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU44700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ZoneTrackAlarmUpdate]
  @Id [uniqueidentifier],
  @RowVersion [bigint] OUTPUT,
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
    DECLARE @RowCnt INT;
    DECLARE @MyTableVar table(RowVersion INT);
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePointU44800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [ZoneTrackAlarm] SET [RowVersion] = [RowVersion] + 1,[Track] = @Track,[Zone] = @Zone,[RadarTrack] = @RadarTrack,[Timestamp] = @Timestamp,[Latitude] = @Latitude,[Longitude] = @Longitude,[Speed] = @Speed,[Course] = @Course,[Heading] = @Heading,[EnterLatitude] = @EnterLatitude,[EnterLongitude] = @EnterLongitude,[LeaveLatitude] = @LeaveLatitude,[LeaveLongitude] = @LeaveLongitude
          OUTPUT INSERTED.[RowVersion] INTO @MyTableVar 
          WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCnt = @@RowCount;
      IF @RowCnt = 0
        BEGIN
          RAISERROR('Row not found or concurrency error',16,1);
        END
      SET @RowVersion  = ( SELECT TOP 1 [RowVersion] FROM @MyTableVar);

      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePointU44800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

