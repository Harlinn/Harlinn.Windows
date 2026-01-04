CREATE OR ALTER PROCEDURE [dbo].[MergeAWBuildVersion]
@Data [dbo].[AwbuildversionTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [dbo].[AWBuildVersion] AS Target
      USING @Data AS Source
          ON Target.[Systeminformationid] = Source.[Systeminformationid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Database Version] = Source.[Database Version],
              Target.[Versiondate] = Source.[Versiondate],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Systeminformationid], [Database Version], [Versiondate], [Modifieddate])
          VALUES(Source.[Systeminformationid], Source.[Database Version], Source.[Versiondate], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [dbo].[MergeDatabaseLog]
@Data [dbo].[DatabaselogTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [dbo].[DatabaseLog] AS Target
      USING @Data AS Source
          ON Target.[Databaselogid] = Source.[Databaselogid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Posttime] = Source.[Posttime],
              Target.[Databaseuser] = Source.[Databaseuser],
              Target.[Event] = Source.[Event],
              Target.[Schema] = Source.[Schema],
              Target.[Object] = Source.[Object],
              Target.[Tsql] = Source.[Tsql],
              Target.[Xmlevent] = Source.[Xmlevent]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Databaselogid], [Posttime], [Databaseuser], [Event], [Schema], [Object], [Tsql], [Xmlevent])
          VALUES(Source.[Databaselogid], Source.[Posttime], Source.[Databaseuser], Source.[Event], Source.[Schema], Source.[Object], Source.[Tsql], Source.[Xmlevent]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [dbo].[MergeErrorLog]
@Data [dbo].[ErrorlogTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [dbo].[ErrorLog] AS Target
      USING @Data AS Source
          ON Target.[Errorlogid] = Source.[Errorlogid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Errortime] = Source.[Errortime],
              Target.[Username] = Source.[Username],
              Target.[Errornumber] = Source.[Errornumber],
              Target.[Errorseverity] = Source.[Errorseverity],
              Target.[Errorstate] = Source.[Errorstate],
              Target.[Errorprocedure] = Source.[Errorprocedure],
              Target.[Errorline] = Source.[Errorline],
              Target.[Errormessage] = Source.[Errormessage]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Errorlogid], [Errortime], [Username], [Errornumber], [Errorseverity], [Errorstate], [Errorprocedure], [Errorline], [Errormessage])
          VALUES(Source.[Errorlogid], Source.[Errortime], Source.[Username], Source.[Errornumber], Source.[Errorseverity], Source.[Errorstate], Source.[Errorprocedure], Source.[Errorline], Source.[Errormessage]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [HumanResources].[MergeDepartment]
@Data [HumanResources].[DepartmentTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [HumanResources].[Department] AS Target
      USING @Data AS Source
          ON Target.[Departmentid] = Source.[Departmentid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Groupname] = Source.[Groupname],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Departmentid], [Name], [Groupname], [Modifieddate])
          VALUES(Source.[Departmentid], Source.[Name], Source.[Groupname], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [HumanResources].[MergeEmployee]
@Data [HumanResources].[EmployeeTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [HumanResources].[Employee] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Nationalidnumber] = Source.[Nationalidnumber],
              Target.[Loginid] = Source.[Loginid],
              Target.[Organizationnode] = Source.[Organizationnode],
              Target.[Jobtitle] = Source.[Jobtitle],
              Target.[Birthdate] = Source.[Birthdate],
              Target.[Maritalstatus] = Source.[Maritalstatus],
              Target.[Gender] = Source.[Gender],
              Target.[Hiredate] = Source.[Hiredate],
              Target.[Salariedflag] = Source.[Salariedflag],
              Target.[Vacationhours] = Source.[Vacationhours],
              Target.[Sickleavehours] = Source.[Sickleavehours],
              Target.[Currentflag] = Source.[Currentflag],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Nationalidnumber], [Loginid], [Organizationnode], [Jobtitle], [Birthdate], [Maritalstatus], [Gender], [Hiredate], [Salariedflag], [Vacationhours], [Sickleavehours], [Currentflag], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Nationalidnumber], Source.[Loginid], Source.[Organizationnode], Source.[Jobtitle], Source.[Birthdate], Source.[Maritalstatus], Source.[Gender], Source.[Hiredate], Source.[Salariedflag], Source.[Vacationhours], Source.[Sickleavehours], Source.[Currentflag], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [HumanResources].[MergeEmployeeDepartmentHistory]
@Data [HumanResources].[EmployeedepartmenthistoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [HumanResources].[EmployeeDepartmentHistory] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid] AND Target.[Startdate] = Source.[Startdate] AND Target.[Departmentid] = Source.[Departmentid] AND Target.[Shiftid] = Source.[Shiftid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Enddate] = Source.[Enddate],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Departmentid], [Shiftid], [Startdate], [Enddate], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Departmentid], Source.[Shiftid], Source.[Startdate], Source.[Enddate], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [HumanResources].[MergeEmployeePayHistory]
@Data [HumanResources].[EmployeepayhistoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [HumanResources].[EmployeePayHistory] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid] AND Target.[Ratechangedate] = Source.[Ratechangedate]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Rate] = Source.[Rate],
              Target.[Payfrequency] = Source.[Payfrequency],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Ratechangedate], [Rate], [Payfrequency], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Ratechangedate], Source.[Rate], Source.[Payfrequency], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [HumanResources].[MergeJobCandidate]
@Data [HumanResources].[JobcandidateTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [HumanResources].[JobCandidate] AS Target
      USING @Data AS Source
          ON Target.[Jobcandidateid] = Source.[Jobcandidateid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Businessentityid] = Source.[Businessentityid],
              Target.[Resume] = Source.[Resume],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Jobcandidateid], [Businessentityid], [Resume], [Modifieddate])
          VALUES(Source.[Jobcandidateid], Source.[Businessentityid], Source.[Resume], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [HumanResources].[MergeShift]
@Data [HumanResources].[ShiftTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [HumanResources].[Shift] AS Target
      USING @Data AS Source
          ON Target.[Shiftid] = Source.[Shiftid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Starttime] = Source.[Starttime],
              Target.[Endtime] = Source.[Endtime],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Shiftid], [Name], [Starttime], [Endtime], [Modifieddate])
          VALUES(Source.[Shiftid], Source.[Name], Source.[Starttime], Source.[Endtime], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergeAddress]
@Data [Person].[AddressTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[Address] AS Target
      USING @Data AS Source
          ON Target.[Addressid] = Source.[Addressid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Addressline1] = Source.[Addressline1],
              Target.[Addressline2] = Source.[Addressline2],
              Target.[City] = Source.[City],
              Target.[Stateprovinceid] = Source.[Stateprovinceid],
              Target.[Postalcode] = Source.[Postalcode],
              Target.[Spatiallocation] = Source.[Spatiallocation],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Addressid], [Addressline1], [Addressline2], [City], [Stateprovinceid], [Postalcode], [Spatiallocation], [Rowguid], [Modifieddate])
          VALUES(Source.[Addressid], Source.[Addressline1], Source.[Addressline2], Source.[City], Source.[Stateprovinceid], Source.[Postalcode], Source.[Spatiallocation], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergeAddressType]
@Data [Person].[AddresstypeTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[AddressType] AS Target
      USING @Data AS Source
          ON Target.[Addresstypeid] = Source.[Addresstypeid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Addresstypeid], [Name], [Rowguid], [Modifieddate])
          VALUES(Source.[Addresstypeid], Source.[Name], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergeBusinessEntity]
@Data [Person].[BusinessentityTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[BusinessEntity] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergeBusinessEntityAddress]
@Data [Person].[BusinessentityaddressTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[BusinessEntityAddress] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid] AND Target.[Addressid] = Source.[Addressid] AND Target.[Addresstypeid] = Source.[Addresstypeid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Addressid], [Addresstypeid], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Addressid], Source.[Addresstypeid], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergeBusinessEntityContact]
@Data [Person].[BusinessentitycontactTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[BusinessEntityContact] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid] AND Target.[Personid] = Source.[Personid] AND Target.[Contacttypeid] = Source.[Contacttypeid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Personid], [Contacttypeid], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Personid], Source.[Contacttypeid], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergeContactType]
@Data [Person].[ContacttypeTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[ContactType] AS Target
      USING @Data AS Source
          ON Target.[Contacttypeid] = Source.[Contacttypeid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Contacttypeid], [Name], [Modifieddate])
          VALUES(Source.[Contacttypeid], Source.[Name], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergeCountryRegion]
@Data [Person].[CountryregionTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[CountryRegion] AS Target
      USING @Data AS Source
          ON Target.[Countryregioncode] = Source.[Countryregioncode]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Countryregioncode], [Name], [Modifieddate])
          VALUES(Source.[Countryregioncode], Source.[Name], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergeEmailAddress]
@Data [Person].[EmailaddressTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[EmailAddress] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid] AND Target.[Emailaddressid] = Source.[Emailaddressid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Emailaddress] = Source.[Emailaddress],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Emailaddressid], [Emailaddress], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Emailaddressid], Source.[Emailaddress], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergePassword]
@Data [Person].[PasswordTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[Password] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Passwordhash] = Source.[Passwordhash],
              Target.[Passwordsalt] = Source.[Passwordsalt],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Passwordhash], [Passwordsalt], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Passwordhash], Source.[Passwordsalt], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergePerson]
@Data [Person].[PersonTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[Person] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Persontype] = Source.[Persontype],
              Target.[Namestyle] = Source.[Namestyle],
              Target.[Title] = Source.[Title],
              Target.[Firstname] = Source.[Firstname],
              Target.[Middlename] = Source.[Middlename],
              Target.[Lastname] = Source.[Lastname],
              Target.[Suffix] = Source.[Suffix],
              Target.[Emailpromotion] = Source.[Emailpromotion],
              Target.[Additionalcontactinfo] = Source.[Additionalcontactinfo],
              Target.[Demographics] = Source.[Demographics],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Persontype], [Namestyle], [Title], [Firstname], [Middlename], [Lastname], [Suffix], [Emailpromotion], [Additionalcontactinfo], [Demographics], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Persontype], Source.[Namestyle], Source.[Title], Source.[Firstname], Source.[Middlename], Source.[Lastname], Source.[Suffix], Source.[Emailpromotion], Source.[Additionalcontactinfo], Source.[Demographics], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergePersonPhone]
@Data [Person].[PersonphoneTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[PersonPhone] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid] AND Target.[Phonenumber] = Source.[Phonenumber] AND Target.[Phonenumbertypeid] = Source.[Phonenumbertypeid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Phonenumber], [Phonenumbertypeid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Phonenumber], Source.[Phonenumbertypeid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergePhoneNumberType]
@Data [Person].[PhonenumbertypeTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[PhoneNumberType] AS Target
      USING @Data AS Source
          ON Target.[Phonenumbertypeid] = Source.[Phonenumbertypeid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Phonenumbertypeid], [Name], [Modifieddate])
          VALUES(Source.[Phonenumbertypeid], Source.[Name], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Person].[MergeStateProvince]
@Data [Person].[StateprovinceTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Person].[StateProvince] AS Target
      USING @Data AS Source
          ON Target.[Stateprovinceid] = Source.[Stateprovinceid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Stateprovincecode] = Source.[Stateprovincecode],
              Target.[Countryregioncode] = Source.[Countryregioncode],
              Target.[Isonlystateprovinceflag] = Source.[Isonlystateprovinceflag],
              Target.[Name] = Source.[Name],
              Target.[Territoryid] = Source.[Territoryid],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Stateprovinceid], [Stateprovincecode], [Countryregioncode], [Isonlystateprovinceflag], [Name], [Territoryid], [Rowguid], [Modifieddate])
          VALUES(Source.[Stateprovinceid], Source.[Stateprovincecode], Source.[Countryregioncode], Source.[Isonlystateprovinceflag], Source.[Name], Source.[Territoryid], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeBillOfMaterials]
@Data [Production].[BillofmaterialsTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[BillOfMaterials] AS Target
      USING @Data AS Source
          ON Target.[Billofmaterialsid] = Source.[Billofmaterialsid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Productassemblyid] = Source.[Productassemblyid],
              Target.[Componentid] = Source.[Componentid],
              Target.[Startdate] = Source.[Startdate],
              Target.[Enddate] = Source.[Enddate],
              Target.[Unitmeasurecode] = Source.[Unitmeasurecode],
              Target.[Bomlevel] = Source.[Bomlevel],
              Target.[Perassemblyqty] = Source.[Perassemblyqty],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Billofmaterialsid], [Productassemblyid], [Componentid], [Startdate], [Enddate], [Unitmeasurecode], [Bomlevel], [Perassemblyqty], [Modifieddate])
          VALUES(Source.[Billofmaterialsid], Source.[Productassemblyid], Source.[Componentid], Source.[Startdate], Source.[Enddate], Source.[Unitmeasurecode], Source.[Bomlevel], Source.[Perassemblyqty], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeCulture]
@Data [Production].[CultureTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[Culture] AS Target
      USING @Data AS Source
          ON Target.[Cultureid] = Source.[Cultureid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Cultureid], [Name], [Modifieddate])
          VALUES(Source.[Cultureid], Source.[Name], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeDocument]
@Data [Production].[DocumentTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[Document] AS Target
      USING @Data AS Source
          ON Target.[Documentnode] = Source.[Documentnode]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Title] = Source.[Title],
              Target.[Owner] = Source.[Owner],
              Target.[Folderflag] = Source.[Folderflag],
              Target.[Filename] = Source.[Filename],
              Target.[Fileextension] = Source.[Fileextension],
              Target.[Revision] = Source.[Revision],
              Target.[Changenumber] = Source.[Changenumber],
              Target.[Status] = Source.[Status],
              Target.[Documentsummary] = Source.[Documentsummary],
              Target.[Document] = Source.[Document],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Documentnode], [Title], [Owner], [Folderflag], [Filename], [Fileextension], [Revision], [Changenumber], [Status], [Documentsummary], [Document], [Rowguid], [Modifieddate])
          VALUES(Source.[Documentnode], Source.[Title], Source.[Owner], Source.[Folderflag], Source.[Filename], Source.[Fileextension], Source.[Revision], Source.[Changenumber], Source.[Status], Source.[Documentsummary], Source.[Document], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeIllustration]
@Data [Production].[IllustrationTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[Illustration] AS Target
      USING @Data AS Source
          ON Target.[Illustrationid] = Source.[Illustrationid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Diagram] = Source.[Diagram],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Illustrationid], [Diagram], [Modifieddate])
          VALUES(Source.[Illustrationid], Source.[Diagram], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeLocation]
@Data [Production].[LocationTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[Location] AS Target
      USING @Data AS Source
          ON Target.[Locationid] = Source.[Locationid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Costrate] = Source.[Costrate],
              Target.[Availability] = Source.[Availability],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Locationid], [Name], [Costrate], [Availability], [Modifieddate])
          VALUES(Source.[Locationid], Source.[Name], Source.[Costrate], Source.[Availability], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProduct]
@Data [Production].[ProductTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[Product] AS Target
      USING @Data AS Source
          ON Target.[Productid] = Source.[Productid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Productnumber] = Source.[Productnumber],
              Target.[Makeflag] = Source.[Makeflag],
              Target.[Finishedgoodsflag] = Source.[Finishedgoodsflag],
              Target.[Color] = Source.[Color],
              Target.[Safetystocklevel] = Source.[Safetystocklevel],
              Target.[Reorderpoint] = Source.[Reorderpoint],
              Target.[Standardcost] = Source.[Standardcost],
              Target.[Listprice] = Source.[Listprice],
              Target.[Size] = Source.[Size],
              Target.[Sizeunitmeasurecode] = Source.[Sizeunitmeasurecode],
              Target.[Weightunitmeasurecode] = Source.[Weightunitmeasurecode],
              Target.[Weight] = Source.[Weight],
              Target.[Daystomanufacture] = Source.[Daystomanufacture],
              Target.[Productline] = Source.[Productline],
              Target.[Class] = Source.[Class],
              Target.[Style] = Source.[Style],
              Target.[Productsubcategoryid] = Source.[Productsubcategoryid],
              Target.[Productmodelid] = Source.[Productmodelid],
              Target.[Sellstartdate] = Source.[Sellstartdate],
              Target.[Sellenddate] = Source.[Sellenddate],
              Target.[Discontinueddate] = Source.[Discontinueddate],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productid], [Name], [Productnumber], [Makeflag], [Finishedgoodsflag], [Color], [Safetystocklevel], [Reorderpoint], [Standardcost], [Listprice], [Size], [Sizeunitmeasurecode], [Weightunitmeasurecode], [Weight], [Daystomanufacture], [Productline], [Class], [Style], [Productsubcategoryid], [Productmodelid], [Sellstartdate], [Sellenddate], [Discontinueddate], [Rowguid], [Modifieddate])
          VALUES(Source.[Productid], Source.[Name], Source.[Productnumber], Source.[Makeflag], Source.[Finishedgoodsflag], Source.[Color], Source.[Safetystocklevel], Source.[Reorderpoint], Source.[Standardcost], Source.[Listprice], Source.[Size], Source.[Sizeunitmeasurecode], Source.[Weightunitmeasurecode], Source.[Weight], Source.[Daystomanufacture], Source.[Productline], Source.[Class], Source.[Style], Source.[Productsubcategoryid], Source.[Productmodelid], Source.[Sellstartdate], Source.[Sellenddate], Source.[Discontinueddate], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductCategory]
@Data [Production].[ProductcategoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductCategory] AS Target
      USING @Data AS Source
          ON Target.[Productcategoryid] = Source.[Productcategoryid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productcategoryid], [Name], [Rowguid], [Modifieddate])
          VALUES(Source.[Productcategoryid], Source.[Name], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductCostHistory]
@Data [Production].[ProductcosthistoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductCostHistory] AS Target
      USING @Data AS Source
          ON Target.[Productid] = Source.[Productid] AND Target.[Startdate] = Source.[Startdate]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Enddate] = Source.[Enddate],
              Target.[Standardcost] = Source.[Standardcost],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productid], [Startdate], [Enddate], [Standardcost], [Modifieddate])
          VALUES(Source.[Productid], Source.[Startdate], Source.[Enddate], Source.[Standardcost], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductDescription]
@Data [Production].[ProductdescriptionTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductDescription] AS Target
      USING @Data AS Source
          ON Target.[Productdescriptionid] = Source.[Productdescriptionid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Description] = Source.[Description],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productdescriptionid], [Description], [Rowguid], [Modifieddate])
          VALUES(Source.[Productdescriptionid], Source.[Description], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductDocument]
@Data [Production].[ProductdocumentTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductDocument] AS Target
      USING @Data AS Source
          ON Target.[Productid] = Source.[Productid] AND Target.[Documentnode] = Source.[Documentnode]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productid], [Documentnode], [Modifieddate])
          VALUES(Source.[Productid], Source.[Documentnode], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductInventory]
@Data [Production].[ProductinventoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductInventory] AS Target
      USING @Data AS Source
          ON Target.[Productid] = Source.[Productid] AND Target.[Locationid] = Source.[Locationid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Shelf] = Source.[Shelf],
              Target.[Bin] = Source.[Bin],
              Target.[Quantity] = Source.[Quantity],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productid], [Locationid], [Shelf], [Bin], [Quantity], [Rowguid], [Modifieddate])
          VALUES(Source.[Productid], Source.[Locationid], Source.[Shelf], Source.[Bin], Source.[Quantity], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductListPriceHistory]
@Data [Production].[ProductlistpricehistoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductListPriceHistory] AS Target
      USING @Data AS Source
          ON Target.[Productid] = Source.[Productid] AND Target.[Startdate] = Source.[Startdate]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Enddate] = Source.[Enddate],
              Target.[Listprice] = Source.[Listprice],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productid], [Startdate], [Enddate], [Listprice], [Modifieddate])
          VALUES(Source.[Productid], Source.[Startdate], Source.[Enddate], Source.[Listprice], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductModel]
@Data [Production].[ProductmodelTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductModel] AS Target
      USING @Data AS Source
          ON Target.[Productmodelid] = Source.[Productmodelid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Catalogdescription] = Source.[Catalogdescription],
              Target.[Instructions] = Source.[Instructions],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productmodelid], [Name], [Catalogdescription], [Instructions], [Rowguid], [Modifieddate])
          VALUES(Source.[Productmodelid], Source.[Name], Source.[Catalogdescription], Source.[Instructions], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductModelIllustration]
@Data [Production].[ProductmodelillustrationTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductModelIllustration] AS Target
      USING @Data AS Source
          ON Target.[Productmodelid] = Source.[Productmodelid] AND Target.[Illustrationid] = Source.[Illustrationid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productmodelid], [Illustrationid], [Modifieddate])
          VALUES(Source.[Productmodelid], Source.[Illustrationid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductModelProductDescriptionCulture]
@Data [Production].[ProductmodelproductdescriptioncultureTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductModelProductDescriptionCulture] AS Target
      USING @Data AS Source
          ON Target.[Productmodelid] = Source.[Productmodelid] AND Target.[Productdescriptionid] = Source.[Productdescriptionid] AND Target.[Cultureid] = Source.[Cultureid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productmodelid], [Productdescriptionid], [Cultureid], [Modifieddate])
          VALUES(Source.[Productmodelid], Source.[Productdescriptionid], Source.[Cultureid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductPhoto]
@Data [Production].[ProductphotoTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductPhoto] AS Target
      USING @Data AS Source
          ON Target.[Productphotoid] = Source.[Productphotoid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Thumbnailphoto] = Source.[Thumbnailphoto],
              Target.[Thumbnailphotofilename] = Source.[Thumbnailphotofilename],
              Target.[Largephoto] = Source.[Largephoto],
              Target.[Largephotofilename] = Source.[Largephotofilename],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productphotoid], [Thumbnailphoto], [Thumbnailphotofilename], [Largephoto], [Largephotofilename], [Modifieddate])
          VALUES(Source.[Productphotoid], Source.[Thumbnailphoto], Source.[Thumbnailphotofilename], Source.[Largephoto], Source.[Largephotofilename], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductProductPhoto]
@Data [Production].[ProductproductphotoTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductProductPhoto] AS Target
      USING @Data AS Source
          ON Target.[Productid] = Source.[Productid] AND Target.[Productphotoid] = Source.[Productphotoid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Primary] = Source.[Primary],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productid], [Productphotoid], [Primary], [Modifieddate])
          VALUES(Source.[Productid], Source.[Productphotoid], Source.[Primary], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductReview]
@Data [Production].[ProductreviewTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductReview] AS Target
      USING @Data AS Source
          ON Target.[Productreviewid] = Source.[Productreviewid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Productid] = Source.[Productid],
              Target.[Reviewername] = Source.[Reviewername],
              Target.[Reviewdate] = Source.[Reviewdate],
              Target.[Emailaddress] = Source.[Emailaddress],
              Target.[Rating] = Source.[Rating],
              Target.[Comments] = Source.[Comments],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productreviewid], [Productid], [Reviewername], [Reviewdate], [Emailaddress], [Rating], [Comments], [Modifieddate])
          VALUES(Source.[Productreviewid], Source.[Productid], Source.[Reviewername], Source.[Reviewdate], Source.[Emailaddress], Source.[Rating], Source.[Comments], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeProductSubcategory]
@Data [Production].[ProductsubcategoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ProductSubcategory] AS Target
      USING @Data AS Source
          ON Target.[Productsubcategoryid] = Source.[Productsubcategoryid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Productcategoryid] = Source.[Productcategoryid],
              Target.[Name] = Source.[Name],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productsubcategoryid], [Productcategoryid], [Name], [Rowguid], [Modifieddate])
          VALUES(Source.[Productsubcategoryid], Source.[Productcategoryid], Source.[Name], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeScrapReason]
@Data [Production].[ScrapreasonTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[ScrapReason] AS Target
      USING @Data AS Source
          ON Target.[Scrapreasonid] = Source.[Scrapreasonid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Scrapreasonid], [Name], [Modifieddate])
          VALUES(Source.[Scrapreasonid], Source.[Name], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeTransactionHistory]
@Data [Production].[TransactionhistoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[TransactionHistory] AS Target
      USING @Data AS Source
          ON Target.[Transactionid] = Source.[Transactionid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Productid] = Source.[Productid],
              Target.[Referenceorderid] = Source.[Referenceorderid],
              Target.[Referenceorderlineid] = Source.[Referenceorderlineid],
              Target.[Transactiondate] = Source.[Transactiondate],
              Target.[Transactiontype] = Source.[Transactiontype],
              Target.[Quantity] = Source.[Quantity],
              Target.[Actualcost] = Source.[Actualcost],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Transactionid], [Productid], [Referenceorderid], [Referenceorderlineid], [Transactiondate], [Transactiontype], [Quantity], [Actualcost], [Modifieddate])
          VALUES(Source.[Transactionid], Source.[Productid], Source.[Referenceorderid], Source.[Referenceorderlineid], Source.[Transactiondate], Source.[Transactiontype], Source.[Quantity], Source.[Actualcost], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeTransactionHistoryArchive]
@Data [Production].[TransactionhistoryarchiveTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[TransactionHistoryArchive] AS Target
      USING @Data AS Source
          ON Target.[Transactionid] = Source.[Transactionid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Productid] = Source.[Productid],
              Target.[Referenceorderid] = Source.[Referenceorderid],
              Target.[Referenceorderlineid] = Source.[Referenceorderlineid],
              Target.[Transactiondate] = Source.[Transactiondate],
              Target.[Transactiontype] = Source.[Transactiontype],
              Target.[Quantity] = Source.[Quantity],
              Target.[Actualcost] = Source.[Actualcost],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Transactionid], [Productid], [Referenceorderid], [Referenceorderlineid], [Transactiondate], [Transactiontype], [Quantity], [Actualcost], [Modifieddate])
          VALUES(Source.[Transactionid], Source.[Productid], Source.[Referenceorderid], Source.[Referenceorderlineid], Source.[Transactiondate], Source.[Transactiontype], Source.[Quantity], Source.[Actualcost], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeUnitMeasure]
@Data [Production].[UnitmeasureTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[UnitMeasure] AS Target
      USING @Data AS Source
          ON Target.[Unitmeasurecode] = Source.[Unitmeasurecode]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Unitmeasurecode], [Name], [Modifieddate])
          VALUES(Source.[Unitmeasurecode], Source.[Name], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeWorkOrder]
@Data [Production].[WorkorderTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[WorkOrder] AS Target
      USING @Data AS Source
          ON Target.[Workorderid] = Source.[Workorderid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Productid] = Source.[Productid],
              Target.[Orderqty] = Source.[Orderqty],
              Target.[Scrappedqty] = Source.[Scrappedqty],
              Target.[Startdate] = Source.[Startdate],
              Target.[Enddate] = Source.[Enddate],
              Target.[Duedate] = Source.[Duedate],
              Target.[Scrapreasonid] = Source.[Scrapreasonid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Workorderid], [Productid], [Orderqty], [Scrappedqty], [Startdate], [Enddate], [Duedate], [Scrapreasonid], [Modifieddate])
          VALUES(Source.[Workorderid], Source.[Productid], Source.[Orderqty], Source.[Scrappedqty], Source.[Startdate], Source.[Enddate], Source.[Duedate], Source.[Scrapreasonid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Production].[MergeWorkOrderRouting]
@Data [Production].[WorkorderroutingTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Production].[WorkOrderRouting] AS Target
      USING @Data AS Source
          ON Target.[Workorderid] = Source.[Workorderid] AND Target.[Productid] = Source.[Productid] AND Target.[Operationsequence] = Source.[Operationsequence]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Locationid] = Source.[Locationid],
              Target.[Scheduledstartdate] = Source.[Scheduledstartdate],
              Target.[Scheduledenddate] = Source.[Scheduledenddate],
              Target.[Actualstartdate] = Source.[Actualstartdate],
              Target.[Actualenddate] = Source.[Actualenddate],
              Target.[Actualresourcehrs] = Source.[Actualresourcehrs],
              Target.[Plannedcost] = Source.[Plannedcost],
              Target.[Actualcost] = Source.[Actualcost],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Workorderid], [Productid], [Operationsequence], [Locationid], [Scheduledstartdate], [Scheduledenddate], [Actualstartdate], [Actualenddate], [Actualresourcehrs], [Plannedcost], [Actualcost], [Modifieddate])
          VALUES(Source.[Workorderid], Source.[Productid], Source.[Operationsequence], Source.[Locationid], Source.[Scheduledstartdate], Source.[Scheduledenddate], Source.[Actualstartdate], Source.[Actualenddate], Source.[Actualresourcehrs], Source.[Plannedcost], Source.[Actualcost], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Purchasing].[MergeProductVendor]
@Data [Purchasing].[ProductvendorTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Purchasing].[ProductVendor] AS Target
      USING @Data AS Source
          ON Target.[Productid] = Source.[Productid] AND Target.[Businessentityid] = Source.[Businessentityid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Averageleadtime] = Source.[Averageleadtime],
              Target.[Standardprice] = Source.[Standardprice],
              Target.[Lastreceiptcost] = Source.[Lastreceiptcost],
              Target.[Lastreceiptdate] = Source.[Lastreceiptdate],
              Target.[Minorderqty] = Source.[Minorderqty],
              Target.[Maxorderqty] = Source.[Maxorderqty],
              Target.[Onorderqty] = Source.[Onorderqty],
              Target.[Unitmeasurecode] = Source.[Unitmeasurecode],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Productid], [Businessentityid], [Averageleadtime], [Standardprice], [Lastreceiptcost], [Lastreceiptdate], [Minorderqty], [Maxorderqty], [Onorderqty], [Unitmeasurecode], [Modifieddate])
          VALUES(Source.[Productid], Source.[Businessentityid], Source.[Averageleadtime], Source.[Standardprice], Source.[Lastreceiptcost], Source.[Lastreceiptdate], Source.[Minorderqty], Source.[Maxorderqty], Source.[Onorderqty], Source.[Unitmeasurecode], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Purchasing].[MergePurchaseOrderDetail]
@Data [Purchasing].[PurchaseorderdetailTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Purchasing].[PurchaseOrderDetail] AS Target
      USING @Data AS Source
          ON Target.[Purchaseorderid] = Source.[Purchaseorderid] AND Target.[Purchaseorderdetailid] = Source.[Purchaseorderdetailid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Duedate] = Source.[Duedate],
              Target.[Orderqty] = Source.[Orderqty],
              Target.[Productid] = Source.[Productid],
              Target.[Unitprice] = Source.[Unitprice],
              Target.[Receivedqty] = Source.[Receivedqty],
              Target.[Rejectedqty] = Source.[Rejectedqty],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Purchaseorderid], [Purchaseorderdetailid], [Duedate], [Orderqty], [Productid], [Unitprice], [Receivedqty], [Rejectedqty], [Modifieddate])
          VALUES(Source.[Purchaseorderid], Source.[Purchaseorderdetailid], Source.[Duedate], Source.[Orderqty], Source.[Productid], Source.[Unitprice], Source.[Receivedqty], Source.[Rejectedqty], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Purchasing].[MergePurchaseOrderHeader]
@Data [Purchasing].[PurchaseorderheaderTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Purchasing].[PurchaseOrderHeader] AS Target
      USING @Data AS Source
          ON Target.[Purchaseorderid] = Source.[Purchaseorderid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Revisionnumber] = Source.[Revisionnumber],
              Target.[Status] = Source.[Status],
              Target.[Employeeid] = Source.[Employeeid],
              Target.[Vendorid] = Source.[Vendorid],
              Target.[Shipmethodid] = Source.[Shipmethodid],
              Target.[Orderdate] = Source.[Orderdate],
              Target.[Shipdate] = Source.[Shipdate],
              Target.[Subtotal] = Source.[Subtotal],
              Target.[Taxamt] = Source.[Taxamt],
              Target.[Freight] = Source.[Freight],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Purchaseorderid], [Revisionnumber], [Status], [Employeeid], [Vendorid], [Shipmethodid], [Orderdate], [Shipdate], [Subtotal], [Taxamt], [Freight], [Modifieddate])
          VALUES(Source.[Purchaseorderid], Source.[Revisionnumber], Source.[Status], Source.[Employeeid], Source.[Vendorid], Source.[Shipmethodid], Source.[Orderdate], Source.[Shipdate], Source.[Subtotal], Source.[Taxamt], Source.[Freight], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Purchasing].[MergeShipMethod]
@Data [Purchasing].[ShipmethodTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Purchasing].[ShipMethod] AS Target
      USING @Data AS Source
          ON Target.[Shipmethodid] = Source.[Shipmethodid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Shipbase] = Source.[Shipbase],
              Target.[Shiprate] = Source.[Shiprate],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Shipmethodid], [Name], [Shipbase], [Shiprate], [Rowguid], [Modifieddate])
          VALUES(Source.[Shipmethodid], Source.[Name], Source.[Shipbase], Source.[Shiprate], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Purchasing].[MergeVendor]
@Data [Purchasing].[VendorTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Purchasing].[Vendor] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Accountnumber] = Source.[Accountnumber],
              Target.[Name] = Source.[Name],
              Target.[Creditrating] = Source.[Creditrating],
              Target.[Preferredvendorstatus] = Source.[Preferredvendorstatus],
              Target.[Activeflag] = Source.[Activeflag],
              Target.[Purchasingwebserviceurl] = Source.[Purchasingwebserviceurl],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Accountnumber], [Name], [Creditrating], [Preferredvendorstatus], [Activeflag], [Purchasingwebserviceurl], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Accountnumber], Source.[Name], Source.[Creditrating], Source.[Preferredvendorstatus], Source.[Activeflag], Source.[Purchasingwebserviceurl], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeCountryRegionCurrency]
@Data [Sales].[CountryregioncurrencyTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[CountryRegionCurrency] AS Target
      USING @Data AS Source
          ON Target.[Countryregioncode] = Source.[Countryregioncode] AND Target.[Currencycode] = Source.[Currencycode]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Countryregioncode], [Currencycode], [Modifieddate])
          VALUES(Source.[Countryregioncode], Source.[Currencycode], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeCreditCard]
@Data [Sales].[CreditcardTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[CreditCard] AS Target
      USING @Data AS Source
          ON Target.[Creditcardid] = Source.[Creditcardid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Cardtype] = Source.[Cardtype],
              Target.[Cardnumber] = Source.[Cardnumber],
              Target.[Expmonth] = Source.[Expmonth],
              Target.[Expyear] = Source.[Expyear],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Creditcardid], [Cardtype], [Cardnumber], [Expmonth], [Expyear], [Modifieddate])
          VALUES(Source.[Creditcardid], Source.[Cardtype], Source.[Cardnumber], Source.[Expmonth], Source.[Expyear], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeCurrency]
@Data [Sales].[CurrencyTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[Currency] AS Target
      USING @Data AS Source
          ON Target.[Currencycode] = Source.[Currencycode]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Currencycode], [Name], [Modifieddate])
          VALUES(Source.[Currencycode], Source.[Name], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeCurrencyRate]
@Data [Sales].[CurrencyrateTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[CurrencyRate] AS Target
      USING @Data AS Source
          ON Target.[Currencyrateid] = Source.[Currencyrateid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Currencyratedate] = Source.[Currencyratedate],
              Target.[Fromcurrencycode] = Source.[Fromcurrencycode],
              Target.[Tocurrencycode] = Source.[Tocurrencycode],
              Target.[Averagerate] = Source.[Averagerate],
              Target.[Endofdayrate] = Source.[Endofdayrate],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Currencyrateid], [Currencyratedate], [Fromcurrencycode], [Tocurrencycode], [Averagerate], [Endofdayrate], [Modifieddate])
          VALUES(Source.[Currencyrateid], Source.[Currencyratedate], Source.[Fromcurrencycode], Source.[Tocurrencycode], Source.[Averagerate], Source.[Endofdayrate], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeCustomer]
@Data [Sales].[CustomerTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[Customer] AS Target
      USING @Data AS Source
          ON Target.[Customerid] = Source.[Customerid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Personid] = Source.[Personid],
              Target.[Storeid] = Source.[Storeid],
              Target.[Territoryid] = Source.[Territoryid],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Customerid], [Personid], [Storeid], [Territoryid], [Rowguid], [Modifieddate])
          VALUES(Source.[Customerid], Source.[Personid], Source.[Storeid], Source.[Territoryid], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergePersonCreditCard]
@Data [Sales].[PersoncreditcardTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[PersonCreditCard] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid] AND Target.[Creditcardid] = Source.[Creditcardid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Creditcardid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Creditcardid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSalesOrderDetail]
@Data [Sales].[SalesorderdetailTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SalesOrderDetail] AS Target
      USING @Data AS Source
          ON Target.[Salesorderid] = Source.[Salesorderid] AND Target.[Salesorderdetailid] = Source.[Salesorderdetailid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Carriertrackingnumber] = Source.[Carriertrackingnumber],
              Target.[Orderqty] = Source.[Orderqty],
              Target.[Productid] = Source.[Productid],
              Target.[Specialofferid] = Source.[Specialofferid],
              Target.[Unitprice] = Source.[Unitprice],
              Target.[Unitpricediscount] = Source.[Unitpricediscount],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Salesorderid], [Salesorderdetailid], [Carriertrackingnumber], [Orderqty], [Productid], [Specialofferid], [Unitprice], [Unitpricediscount], [Rowguid], [Modifieddate])
          VALUES(Source.[Salesorderid], Source.[Salesorderdetailid], Source.[Carriertrackingnumber], Source.[Orderqty], Source.[Productid], Source.[Specialofferid], Source.[Unitprice], Source.[Unitpricediscount], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSalesOrderHeader]
@Data [Sales].[SalesorderheaderTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SalesOrderHeader] AS Target
      USING @Data AS Source
          ON Target.[Salesorderid] = Source.[Salesorderid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Revisionnumber] = Source.[Revisionnumber],
              Target.[Orderdate] = Source.[Orderdate],
              Target.[Duedate] = Source.[Duedate],
              Target.[Shipdate] = Source.[Shipdate],
              Target.[Status] = Source.[Status],
              Target.[Onlineorderflag] = Source.[Onlineorderflag],
              Target.[Purchaseordernumber] = Source.[Purchaseordernumber],
              Target.[Accountnumber] = Source.[Accountnumber],
              Target.[Customerid] = Source.[Customerid],
              Target.[Salespersonid] = Source.[Salespersonid],
              Target.[Territoryid] = Source.[Territoryid],
              Target.[Billtoaddressid] = Source.[Billtoaddressid],
              Target.[Shiptoaddressid] = Source.[Shiptoaddressid],
              Target.[Shipmethodid] = Source.[Shipmethodid],
              Target.[Creditcardid] = Source.[Creditcardid],
              Target.[Creditcardapprovalcode] = Source.[Creditcardapprovalcode],
              Target.[Currencyrateid] = Source.[Currencyrateid],
              Target.[Subtotal] = Source.[Subtotal],
              Target.[Taxamt] = Source.[Taxamt],
              Target.[Freight] = Source.[Freight],
              Target.[Comment] = Source.[Comment],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Salesorderid], [Revisionnumber], [Orderdate], [Duedate], [Shipdate], [Status], [Onlineorderflag], [Purchaseordernumber], [Accountnumber], [Customerid], [Salespersonid], [Territoryid], [Billtoaddressid], [Shiptoaddressid], [Shipmethodid], [Creditcardid], [Creditcardapprovalcode], [Currencyrateid], [Subtotal], [Taxamt], [Freight], [Comment], [Rowguid], [Modifieddate])
          VALUES(Source.[Salesorderid], Source.[Revisionnumber], Source.[Orderdate], Source.[Duedate], Source.[Shipdate], Source.[Status], Source.[Onlineorderflag], Source.[Purchaseordernumber], Source.[Accountnumber], Source.[Customerid], Source.[Salespersonid], Source.[Territoryid], Source.[Billtoaddressid], Source.[Shiptoaddressid], Source.[Shipmethodid], Source.[Creditcardid], Source.[Creditcardapprovalcode], Source.[Currencyrateid], Source.[Subtotal], Source.[Taxamt], Source.[Freight], Source.[Comment], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSalesOrderHeaderSalesReason]
@Data [Sales].[SalesorderheadersalesreasonTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SalesOrderHeaderSalesReason] AS Target
      USING @Data AS Source
          ON Target.[Salesorderid] = Source.[Salesorderid] AND Target.[Salesreasonid] = Source.[Salesreasonid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Salesorderid], [Salesreasonid], [Modifieddate])
          VALUES(Source.[Salesorderid], Source.[Salesreasonid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSalesPerson]
@Data [Sales].[SalespersonTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SalesPerson] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Territoryid] = Source.[Territoryid],
              Target.[Salesquota] = Source.[Salesquota],
              Target.[Bonus] = Source.[Bonus],
              Target.[Commissionpct] = Source.[Commissionpct],
              Target.[Salesytd] = Source.[Salesytd],
              Target.[Saleslastyear] = Source.[Saleslastyear],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Territoryid], [Salesquota], [Bonus], [Commissionpct], [Salesytd], [Saleslastyear], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Territoryid], Source.[Salesquota], Source.[Bonus], Source.[Commissionpct], Source.[Salesytd], Source.[Saleslastyear], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSalesPersonQuotaHistory]
@Data [Sales].[SalespersonquotahistoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SalesPersonQuotaHistory] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid] AND Target.[Quotadate] = Source.[Quotadate]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Salesquota] = Source.[Salesquota],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Quotadate], [Salesquota], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Quotadate], Source.[Salesquota], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSalesReason]
@Data [Sales].[SalesreasonTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SalesReason] AS Target
      USING @Data AS Source
          ON Target.[Salesreasonid] = Source.[Salesreasonid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Reasontype] = Source.[Reasontype],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Salesreasonid], [Name], [Reasontype], [Modifieddate])
          VALUES(Source.[Salesreasonid], Source.[Name], Source.[Reasontype], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSalesTaxRate]
@Data [Sales].[SalestaxrateTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SalesTaxRate] AS Target
      USING @Data AS Source
          ON Target.[Salestaxrateid] = Source.[Salestaxrateid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Stateprovinceid] = Source.[Stateprovinceid],
              Target.[Taxtype] = Source.[Taxtype],
              Target.[Taxrate] = Source.[Taxrate],
              Target.[Name] = Source.[Name],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Salestaxrateid], [Stateprovinceid], [Taxtype], [Taxrate], [Name], [Rowguid], [Modifieddate])
          VALUES(Source.[Salestaxrateid], Source.[Stateprovinceid], Source.[Taxtype], Source.[Taxrate], Source.[Name], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSalesTerritory]
@Data [Sales].[SalesterritoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SalesTerritory] AS Target
      USING @Data AS Source
          ON Target.[Territoryid] = Source.[Territoryid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Countryregioncode] = Source.[Countryregioncode],
              Target.[Group] = Source.[Group],
              Target.[Salesytd] = Source.[Salesytd],
              Target.[Saleslastyear] = Source.[Saleslastyear],
              Target.[Costytd] = Source.[Costytd],
              Target.[Costlastyear] = Source.[Costlastyear],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Territoryid], [Name], [Countryregioncode], [Group], [Salesytd], [Saleslastyear], [Costytd], [Costlastyear], [Rowguid], [Modifieddate])
          VALUES(Source.[Territoryid], Source.[Name], Source.[Countryregioncode], Source.[Group], Source.[Salesytd], Source.[Saleslastyear], Source.[Costytd], Source.[Costlastyear], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSalesTerritoryHistory]
@Data [Sales].[SalesterritoryhistoryTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SalesTerritoryHistory] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid] AND Target.[Startdate] = Source.[Startdate] AND Target.[Territoryid] = Source.[Territoryid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Enddate] = Source.[Enddate],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Territoryid], [Startdate], [Enddate], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Territoryid], Source.[Startdate], Source.[Enddate], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeShoppingCartItem]
@Data [Sales].[ShoppingcartitemTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[ShoppingCartItem] AS Target
      USING @Data AS Source
          ON Target.[Shoppingcartitemid] = Source.[Shoppingcartitemid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Shoppingcartid] = Source.[Shoppingcartid],
              Target.[Quantity] = Source.[Quantity],
              Target.[Productid] = Source.[Productid],
              Target.[Datecreated] = Source.[Datecreated],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Shoppingcartitemid], [Shoppingcartid], [Quantity], [Productid], [Datecreated], [Modifieddate])
          VALUES(Source.[Shoppingcartitemid], Source.[Shoppingcartid], Source.[Quantity], Source.[Productid], Source.[Datecreated], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSpecialOffer]
@Data [Sales].[SpecialofferTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SpecialOffer] AS Target
      USING @Data AS Source
          ON Target.[Specialofferid] = Source.[Specialofferid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Description] = Source.[Description],
              Target.[Discountpct] = Source.[Discountpct],
              Target.[Type] = Source.[Type],
              Target.[Category] = Source.[Category],
              Target.[Startdate] = Source.[Startdate],
              Target.[Enddate] = Source.[Enddate],
              Target.[Minqty] = Source.[Minqty],
              Target.[Maxqty] = Source.[Maxqty],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Specialofferid], [Description], [Discountpct], [Type], [Category], [Startdate], [Enddate], [Minqty], [Maxqty], [Rowguid], [Modifieddate])
          VALUES(Source.[Specialofferid], Source.[Description], Source.[Discountpct], Source.[Type], Source.[Category], Source.[Startdate], Source.[Enddate], Source.[Minqty], Source.[Maxqty], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeSpecialOfferProduct]
@Data [Sales].[SpecialofferproductTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[SpecialOfferProduct] AS Target
      USING @Data AS Source
          ON Target.[Specialofferid] = Source.[Specialofferid] AND Target.[Productid] = Source.[Productid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Specialofferid], [Productid], [Rowguid], [Modifieddate])
          VALUES(Source.[Specialofferid], Source.[Productid], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

CREATE OR ALTER PROCEDURE [Sales].[MergeStore]
@Data [Sales].[StoreTableType] READONLY
AS
  BEGIN
    DECLARE @TranCounter INT;
    DECLARE @RowCount INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      MERGE INTO [Sales].[Store] AS Target
      USING @Data AS Source
          ON Target.[Businessentityid] = Source.[Businessentityid]
      WHEN MATCHED THEN
          UPDATE SET
              Target.[Name] = Source.[Name],
              Target.[Salespersonid] = Source.[Salespersonid],
              Target.[Demographics] = Source.[Demographics],
              Target.[Rowguid] = Source.[Rowguid],
              Target.[Modifieddate] = Source.[Modifieddate]
      WHEN NOT MATCHED BY TARGET THEN
          INSERT([Businessentityid], [Name], [Salespersonid], [Demographics], [Rowguid], [Modifieddate])
          VALUES(Source.[Businessentityid], Source.[Name], Source.[Salespersonid], Source.[Demographics], Source.[Rowguid], Source.[Modifieddate]);

      SET @RowCount = @@ROWCOUNT;
      IF @RowCount = 0
      BEGIN
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RETURN
      END
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @MyXErrorMessage NVARCHAR(4000);
        DECLARE @MyXErrorSeverity INT;
        DECLARE @MyXErrorState INT;
        SELECT @MyXErrorMessage = ERROR_MESSAGE(),
            @MyXErrorSeverity = ERROR_SEVERITY(),
            @MyXErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @MyXErrorMessage,
            @MyXErrorSeverity,
            @MyXErrorState);
    END CATCH
  END
GO

