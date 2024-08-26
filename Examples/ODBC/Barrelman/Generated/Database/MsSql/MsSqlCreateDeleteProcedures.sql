CREATE OR ALTER PROCEDURE [AircraftTypeDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AircraftType] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint10000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AidToNavigationReportMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AidToNavigationReportMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10200;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisAddressedSafetyRelatedMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisAddressedSafetyRelatedMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10300;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisBaseStationReportMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisBaseStationReportMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10400;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisBinaryAcknowledgeMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisBinaryAcknowledgeMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10500;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisBinaryAddressedMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisBinaryAddressedMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10600;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisBinaryBroadcastMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisBinaryBroadcastMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10700;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisDataLinkManagementMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisDataLinkManagementMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10800;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisExtendedClassBCsPositionReportMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint10900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisExtendedClassBCsPositionReportMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint10900;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisInterrogationMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisInterrogationMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11000;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisPositionReportClassAAssignedScheduleMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisPositionReportClassAAssignedScheduleMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11200;
        RETURN
      END
      DELETE FROM [dbo].[AisPositionReportClassAMessageBase] WHERE [Id] = @Id;
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisPositionReportClassAMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisPositionReportClassAMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11300;
        RETURN
      END
      DELETE FROM [dbo].[AisPositionReportClassAMessageBase] WHERE [Id] = @Id;
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisPositionReportClassAResponseToInterrogationMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisPositionReportClassAResponseToInterrogationMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11400;
        RETURN
      END
      DELETE FROM [dbo].[AisPositionReportClassAMessageBase] WHERE [Id] = @Id;
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisPositionReportForLongRangeApplicationsMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisPositionReportForLongRangeApplicationsMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11500;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisSafetyRelatedAcknowledgmentMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisSafetyRelatedAcknowledgmentMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11600;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisStandardClassBCsPositionReportMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisStandardClassBCsPositionReportMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11700;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisStandardSarAircraftPositionReportMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisStandardSarAircraftPositionReportMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11800;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisStaticAndVoyageRelatedDataMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint11900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisStaticAndVoyageRelatedDataMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint11900;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisStaticDataReportMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisStaticDataReportMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12000;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisStaticDataReportPartAMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisStaticDataReportPartAMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12100;
        RETURN
      END
      DELETE FROM [dbo].[AisStaticDataReportMessage] WHERE [Id] = @Id;
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisStaticDataReportPartBMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisStaticDataReportPartBMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12200;
        RETURN
      END
      DELETE FROM [dbo].[AisStaticDataReportMessage] WHERE [Id] = @Id;
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisUtcAndDateInquiryMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisUtcAndDateInquiryMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12300;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisUtcAndDateResponseMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisUtcAndDateResponseMessage] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12400;
        RETURN
      END
      DELETE FROM [dbo].[AisMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisTransceiverCommandDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisTransceiverCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint12500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisTransceiverCommandReplyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisTransceiverCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint12600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisTransceiverConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisTransceiverConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint12700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisTransceiverRawMessageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisTransceiverRawMessage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint12800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AisTransceiverRawSentenceDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint12900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisTransceiverRawSentence] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint12900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint12900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [AlarmStateChangeDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AlarmStateChange] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint13000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BaseStationTypeDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BaseStationType] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint13100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BinaryTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BinaryTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint13200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BookmarkDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Bookmark] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint13300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BooleanTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BooleanTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13400;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint13400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ByteTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ByteTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint13500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint13600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraCommandAbsoluteMoveDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandAbsoluteMove] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13700;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandAdjustPanTiltZoomDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandAdjustPanTiltZoom] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13800;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandContinuousMoveDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint13900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandContinuousMove] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint13900;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandGeoMoveDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandGeoMove] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14000;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandRelativeMoveDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandRelativeMove] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14100;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandReleasePTZOwnershipDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandReleasePTZOwnership] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14200;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandRequestPTZOwnershipDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandRequestPTZOwnership] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14300;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandSetAutoFocusDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandSetAutoFocus] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14400;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandSetBlackAndWhiteDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandSetBlackAndWhite] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14500;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandSetFollowedDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandSetFollowed] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14600;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandSetInfraRedLampDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandSetInfraRedLamp] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14700;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandSetWasherDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandSetWasher] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14800;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandSetWiperDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint14900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandSetWiper] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint14900;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandStopDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandStop] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15000;
        RETURN
      END
      DELETE FROM [dbo].[CameraCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraCommandReplyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint15100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint15200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraPanCalibrationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraPanCalibration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint15300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraPanCalibrationValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraPanCalibrationValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15400;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint15400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraStatusDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraStatus] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint15500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraTiltCalibrationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraTiltCalibration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint15600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraTiltCalibrationValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraTiltCalibrationValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint15700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraZoomCalibrationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraZoomCalibration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint15800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CameraZoomCalibrationValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint15900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CameraZoomCalibrationValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint15900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint15900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CatalogDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Catalog] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16100;
        RETURN
      END
      DELETE FROM [dbo].[CatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ElementDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Element] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16200;
        RETURN
      END
      DELETE FROM [dbo].[CatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CollectionInfoDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CollectionInfo] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint16300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CountryDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Country] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16400;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint16400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CursorInfoDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CursorInfo] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint16500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DateTimeTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint16600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DeviceHostDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DeviceHost] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint16700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DeviceHostConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DeviceHostConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint16800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [DoubleTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint16900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DoubleTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint16900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint16900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [FacilityTypeDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[FacilityType] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint17000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GeoPosition2DTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GeoPosition2DTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint17100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GeoPosition3DTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GeoPosition3DTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint17200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GNSSDeviceCommandDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GNSSDeviceCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint17300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GNSSDeviceCommandReplyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GNSSDeviceCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17400;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint17400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GNSSDeviceConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GNSSDeviceConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint17500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GuidTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GuidTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint17600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroDeviceCommandDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroDeviceCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint17700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroDeviceCommandReplyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroDeviceCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint17800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [GyroDeviceConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint17900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroDeviceConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint17900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint17900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CallsignDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Callsign] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18100;
        RETURN
      END
      DELETE FROM [dbo].[Identity] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [InternationalMaritimeOrganizationNumberDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[InternationalMaritimeOrganizationNumber] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18200;
        RETURN
      END
      DELETE FROM [dbo].[Identity] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [MaritimeMobileServiceIdentityDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MaritimeMobileServiceIdentity] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18300;
        RETURN
      END
      DELETE FROM [dbo].[Identity] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [NameDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Name] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18400;
        RETURN
      END
      DELETE FROM [dbo].[Identity] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int16TimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int16TimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint18500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int32TimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int32TimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint18600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Int64TimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int64TimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint18700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BaseStationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint18900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BaseStation] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint18900;
        RETURN
      END
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [CameraDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Camera] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19100;
        RETURN
      END
      DELETE FROM [dbo].[Device] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GNSSDeviceDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GNSSDevice] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19200;
        RETURN
      END
      DELETE FROM [dbo].[Device] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GyroDeviceDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroDevice] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19300;
        RETURN
      END
      DELETE FROM [dbo].[Device] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [LineInputDeviceDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LineInputDevice] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19400;
        RETURN
      END
      DELETE FROM [dbo].[Device] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [OilspillDetectorDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[OilspillDetector] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19500;
        RETURN
      END
      DELETE FROM [dbo].[Device] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadioDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Radio] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19600;
        RETURN
      END
      DELETE FROM [dbo].[Device] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadomeDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Radome] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19700;
        RETURN
      END
      DELETE FROM [dbo].[Device] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisTransceiverDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint19900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisTransceiver] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint19900;
        RETURN
      END
      DELETE FROM [dbo].[Tracker] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Device] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Radar] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20000;
        RETURN
      END
      DELETE FROM [dbo].[Tracker] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Device] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [WeatherStationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStation] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20100;
        RETURN
      END
      DELETE FROM [dbo].[Device] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [FacilityDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Facility] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20200;
        RETURN
      END
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AircraftDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Aircraft] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20400;
        RETURN
      END
      DELETE FROM [dbo].[TrackableItem] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisAidToNavigationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisAidToNavigation] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20500;
        RETURN
      END
      DELETE FROM [dbo].[TrackableItem] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [VehicleDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Vehicle] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20600;
        RETURN
      END
      DELETE FROM [dbo].[TrackableItem] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [VesselDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Vessel] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20700;
        RETURN
      END
      DELETE FROM [dbo].[TrackableItem] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Item] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ItemIdentityLinkDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ItemIdentityLink] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint20800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ItemParentChildLinkDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint20900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ItemParentChildLink] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint20900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint20900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputDeviceCommandDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LineInputDeviceCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint21000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputDeviceCommandReplyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LineInputDeviceCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint21100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputDeviceConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LineInputDeviceConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint21200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputMessageRoutingDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LineInputMessageRouting] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint21300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputMessageRoutingDestinationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LineInputMessageRoutingDestination] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21400;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint21400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LineInputWhiteListEntryDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LineInputWhiteListEntry] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint21500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogApplicationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LogApplication] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint21600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogApplicationConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LogApplicationConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint21700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogHostDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LogHost] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint21800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogHostConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint21900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LogHostConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint21900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint21900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogLocationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LogLocation] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint22000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogProcessDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LogProcess] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint22100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogRecordDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LogRecord] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint22200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogThreadDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LogThread] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint22300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [LogTraceEntryDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[LogTraceEntry] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22400;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint22400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MapElementDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MapElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint22500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MapInfoDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MapInfo] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint22600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MapServiceOptionsDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MapServiceOptions] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint22700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MaritimeIdentificationDigitsDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MaritimeIdentificationDigits] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint22800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaProxySessionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint22900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MediaProxySession] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint22900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint22900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaProxySessionFileDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MediaProxySessionFile] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint23000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaProxySessionOptionsDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MediaProxySessionOptions] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint23100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaServiceDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MediaService] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint23200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [MediaServiceOptionsDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MediaServiceOptions] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint23300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ElementTypeDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ElementType] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23500;
        RETURN
      END
      DELETE FROM [dbo].[NamespaceElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [NamespaceDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Namespace] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23600;
        RETURN
      END
      DELETE FROM [dbo].[NamespaceElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [OilspillDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Oilspill] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint23700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [OilspillDetectorCommandDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[OilspillDetectorCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint23800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [OilspillDetectorCommandReplyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint23900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[OilspillDetectorCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint23900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint23900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [OilspillDetectorConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[OilspillDetectorConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint24000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Position2DTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Position2DTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint24100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Position3DTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Position3DTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint24200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ProcessTrackValueResultDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ProcessTrackValueResult] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint24300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BinaryPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BinaryProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24500;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [BooleanPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BooleanProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24600;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [BytePropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ByteProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24700;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DateTimePropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DateTimeProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24800;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DoublePropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint24900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DoubleProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint24900;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GuidPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GuidProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25000;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int16PropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int16Property] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25100;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int32PropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int32Property] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25200;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int64PropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int64Property] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25300;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ReferencePropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ReferenceProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25400;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SBytePropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SByteProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25500;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SinglePropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SingleProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25600;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [StringPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[StringProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25700;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [BinaryTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint25900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BinaryTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint25900;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [BooleanTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BooleanTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26000;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ByteTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ByteTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26100;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DateTimeTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26200;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DoubleTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DoubleTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26300;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GuidTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GuidTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26400;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int16TimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int16TimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26500;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int32TimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int32TimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26600;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int64TimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int64TimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26700;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ReferenceTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26800;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SByteTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint26900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SByteTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint26900;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SingleTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SingleTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27000;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [StringTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[StringTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27100;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TimeSpanTimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27200;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt16TimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt16TimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27300;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt32TimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt32TimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27400;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt64TimeseriesPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt64TimeseriesProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27500;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesProperty] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [TimeSpanPropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TimeSpanProperty] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27600;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt16PropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt16Property] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27700;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt32PropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt32Property] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27800;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt64PropertyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint27900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt64Property] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint27900;
        RETURN
      END
      DELETE FROM [dbo].[Property] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [BinaryPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BinaryPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28100;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [BooleanPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BooleanPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28200;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [BytePropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BytePropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28300;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DateTimePropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DateTimePropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28400;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DoublePropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DoublePropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28500;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GuidPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GuidPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28600;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int16PropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int16PropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28700;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int32PropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int32PropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28800;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int64PropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint28900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int64PropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint28900;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ReferencePropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ReferencePropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29000;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SBytePropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SBytePropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29100;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SinglePropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SinglePropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29200;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [StringPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[StringPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29300;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [BinaryTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BinaryTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29500;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [BooleanTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BooleanTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29600;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ByteTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ByteTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29700;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DateTimeTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29800;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DoubleTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint29900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DoubleTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint29900;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GuidTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GuidTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30000;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int16TimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int16TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30100;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int32TimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int32TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30200;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int64TimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int64TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30300;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ReferenceTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30400;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SByteTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SByteTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30500;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SingleTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SingleTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30600;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [StringTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[StringTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30700;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TimeSpanTimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30800;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt16TimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint30900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt16TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint30900;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt32TimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt32TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31000;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt64TimeseriesPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt64TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31100;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesPropertyDefinition] WHERE [Id] = @Id;
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [TimeSpanPropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TimeSpanPropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31200;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt16PropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt16PropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31300;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt32PropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt32PropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31400;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt64PropertyDefinitionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt64PropertyDefinition] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31500;
        RETURN
      END
      DELETE FROM [dbo].[PropertyDefinition] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarAlarmStatusDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarAlarmStatus] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint31600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarCommandDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint31700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarCommandGetStatusDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarCommandGetStatus] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31800;
        RETURN
      END
      DELETE FROM [dbo].[RadarCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarCommandReplyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint31900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint31900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint31900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarCommandReplyGetStatusDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarCommandReplyGetStatus] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32000;
        RETURN
      END
      DELETE FROM [dbo].[RadarCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint32100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarImageDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarImage] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint32200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarRawTrackTableDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarRawTrackTable] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint32300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadarStatusDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarStatus] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32400;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint32400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadioCommandDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadioCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint32500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadioCommandReplyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadioCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint32600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadioConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadioConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint32700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomeCommandDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadomeCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint32800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomeCommandReplyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint32900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadomeCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint32900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint32900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [RadomeConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadomeConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint33000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ReferenceTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint33100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SByteTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SByteTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint33200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SecurityDomainDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SecurityDomain] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint33300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SecurityLoginDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SecurityLogin] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33500;
        RETURN
      END
      DELETE FROM [dbo].[SecurityIdentifier] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SecurityRoleDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SecurityRole] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33600;
        RETURN
      END
      DELETE FROM [dbo].[SecurityIdentifier] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SecurityIdentifierRoleLinkDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SecurityIdentifierRoleLink] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint33700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SecurityLoginSessionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SecurityLoginSession] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint33800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SecurityPermissionDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint33900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SecurityPermission] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint33900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint33900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [SingleTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SingleTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint34000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [StringTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[StringTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint34100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [BinaryTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BinaryTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34400;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [BooleanTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34500;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisAidToNavigationOffPositionTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisAidToNavigationOffPositionTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34600;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DeviceEnabledTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DeviceEnabledTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34700;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarAutomaticSensitivityTimeControlTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarAutomaticSensitivityTimeControlTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34800;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarBlankSector1TimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint34900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarBlankSector1Timeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint34900;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarBlankSector2TimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarBlankSector2Timeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35000;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarEnableAutomaticFrequencyControlTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarEnableAutomaticFrequencyControlTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35100;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarEnableFastTimeConstantTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarEnableFastTimeConstantTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35200;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarEnableSensitivityTimeControlTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarEnableSensitivityTimeControlTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35300;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarPowerOnTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarPowerOnTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35400;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarSaveSettingsTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarSaveSettingsTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35500;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarTrackingTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarTrackingTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35600;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [MediaProxySessionEnabledTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MediaProxySessionEnabledTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35700;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [MediaServiceEnabledTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[MediaServiceEnabledTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35800;
        RETURN
      END
      DELETE FROM [dbo].[BooleanTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ByteTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint35900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ByteTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint35900;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DateTimeTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DateTimeTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36000;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [DoubleTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36100;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GNSSAltitudeTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GNSSAltitudeTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36200;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GNSSLatitudeTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GNSSLatitudeTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36300;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GNSSLongitudeTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GNSSLongitudeTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36400;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GyroCourseTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroCourseTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36500;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GyroHeadingMagneticNorthTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroHeadingMagneticNorthTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36600;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GyroHeadingTrueNorthTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroHeadingTrueNorthTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36700;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GyroPitchTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroPitchTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36800;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GyroRateOfTurnTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint36900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroRateOfTurnTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint36900;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GyroRollTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroRollTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37000;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GyroSpeedTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GyroSpeedTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37100;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarLatitudeTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarLatitudeTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37200;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarLongitudeTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarLongitudeTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37300;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadomeDewPointTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadomeDewPointTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37400;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadomePressureTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadomePressureTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37500;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadomeTemperatureTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadomeTemperatureTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37600;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [VesselDraughtTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[VesselDraughtTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37700;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ViewLatitudeTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ViewLatitudeTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37800;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ViewLongitudeTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint37900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ViewLongitudeTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint37900;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ViewZoomLevelTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ViewZoomLevelTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38000;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [WeatherStationAbsoluteHumidityTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationAbsoluteHumidityTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38100;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [WeatherStationAirTemperatureTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationAirTemperatureTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38200;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [WeatherStationBarometricPressureTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationBarometricPressureTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38300;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [WeatherStationDewPointTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationDewPointTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38400;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [WeatherStationRelativeHumidityTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationRelativeHumidityTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38500;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [WeatherStationWaterTemperatureTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationWaterTemperatureTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38600;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [WeatherStationWindDirectionTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationWindDirectionTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38700;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [WeatherStationWindSpeedTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationWindSpeedTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38800;
        RETURN
      END
      DELETE FROM [dbo].[DoubleTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GeoPosition2DTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint38900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GeoPosition2DTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint38900;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [AisAidToNavigationPositionTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[AisAidToNavigationPositionTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39000;
        RETURN
      END
      DELETE FROM [dbo].[GeoPosition2DTimeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GeoPosition3DTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GeoPosition3DTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39100;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [GuidTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[GuidTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39200;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int16TimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int16Timeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39300;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int32TimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39400;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarAzimuthOffsetTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarAzimuthOffsetTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39500;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarFastTimeConstantLevelTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarFastTimeConstantLevelTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39600;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarFastTimeConstantModeTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarFastTimeConstantModeTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39700;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarPulseTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarPulseTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39800;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarSector1EndTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint39900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarSector1EndTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint39900;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarSector1StartTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarSector1StartTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40000;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarSector2EndTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarSector2EndTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40100;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarSector2StartTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarSector2StartTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40200;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarSensitivityTimeControlLevelTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarSensitivityTimeControlLevelTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40300;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadarTuningTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadarTuningTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40400;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [VesselPersonsOnBoardTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[VesselPersonsOnBoardTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40500;
        RETURN
      END
      DELETE FROM [dbo].[Int32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Int64TimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Int64Timeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40600;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Position2DTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Position2DTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40700;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Position3DTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Position3DTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40800;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ReferenceTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint40900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ReferenceTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint40900;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SByteTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SByteTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41000;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [SingleTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[SingleTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41100;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [StringTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[StringTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41200;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TimeSpanTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41300;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt16TimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt16Timeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41400;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt32TimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt32Timeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41500;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [RadomeStatusTimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[RadomeStatusTimeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41600;
        RETURN
      END
      DELETE FROM [dbo].[UInt32Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [UInt64TimeseriesDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt64Timeseries] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41700;
        RETURN
      END
      DELETE FROM [dbo].[Timeseries] WHERE [Id] = @Id;
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [TimeseriesCatalogDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TimeseriesCatalog] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41800;
        RETURN
      END
      DELETE FROM [dbo].[TimeseriesCatalogElement] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [TimeseriesInfoDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint41900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TimeseriesInfo] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint41900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint41900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TimeSpanTimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TimeSpanTimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint42000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackableItemTrackLinkDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TrackableItemTrackLink] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint42100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Track] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42300;
        RETURN
      END
      DELETE FROM [dbo].[TrackBase] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [Track3DDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[Track3D] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42400;
        RETURN
      END
      DELETE FROM [dbo].[TrackBase] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [TrackerFilterParametersDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TrackerFilterParameters] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint42500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackerFilterParametersConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TrackerFilterParametersConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint42600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackInfoDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TrackInfo] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint42700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackingServiceOptionsDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TrackingServiceOptions] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint42800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackLinkDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint42900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TrackLink] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint42900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint42900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TrackValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint43000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [TrackValue3DDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[TrackValue3D] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint43100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt16TimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt16TimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint43200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt32TimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43300;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt32TimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43300;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint43300;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [UInt64TimeseriesValueDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[UInt64TimeseriesValue] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43400;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint43400;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [VehicleTypeDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[VehicleType] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43500;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint43500;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [VesselTypeDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[VesselType] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint43600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ViewDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[View] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint43700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ViewCameraLinkDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ViewCameraLink] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint43800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ViewTrackerLinkDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint43900;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ViewTrackerLink] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint43900;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint43900;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationCommandDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44000;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationCommand] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44000;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint44000;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationCommandReplyDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44100;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationCommandReply] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44100;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint44100;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [WeatherStationConfigurationDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44200;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[WeatherStationConfiguration] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44200;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint44200;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [CircularZoneDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44400;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[CircularZone] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44400;
        RETURN
      END
      DELETE FROM [dbo].[Zone] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [PolygonZoneDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44500;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[PolygonZone] WHERE [Id] = @Id;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44500;
        RETURN
      END
      DELETE FROM [dbo].[Zone] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
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

CREATE OR ALTER PROCEDURE [ZoneExceptionsDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44600;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ZoneExceptions] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44600;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint44600;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ZoneExceptionsVesselLinkDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44700;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ZoneExceptionsVesselLink] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44700;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint44700;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [ZoneTrackAlarmDelete]
  @Id [uniqueidentifier],
  @RowVersion [bigint],
  @RowCount int OUTPUT
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint44800;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      DELETE FROM [dbo].[ZoneTrackAlarm] WHERE [Id] = @Id AND [RowVersion] = @RowVersion;
      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint44800;
        RETURN
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
            ROLLBACK TRANSACTION SavePoint44800;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END
GO

