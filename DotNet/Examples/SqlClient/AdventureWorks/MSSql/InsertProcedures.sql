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
CREATE OR ALTER PROCEDURE [dbo].[InsertAWBuildVersion]
  @systeminformationid [tinyint] OUTPUT, 
  @databaseVersion [nvarchar](25), 
  @versiondate [datetime], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [dbo].[AWBuildVersion]([Database Version],
            [Versiondate],
            [Modifieddate])
          VALUES(@databaseVersion,
              @versiondate,
              @modifieddate)
      SET @systeminformationid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [dbo].[InsertDatabaseLog]
  @databaselogid [int] OUTPUT, 
  @posttime [datetime], 
  @databaseuser [sysname], 
  @event [sysname], 
  @schema [sysname], 
  @object [sysname], 
  @tsql [nvarchar](max), 
  @xmlevent [xml]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [dbo].[DatabaseLog]([Posttime],
            [Databaseuser],
            [Event],
            [Schema],
            [Object],
            [Tsql],
            [Xmlevent])
          VALUES(@posttime,
              @databaseuser,
              @event,
              @schema,
              @object,
              @tsql,
              @xmlevent)
      SET @databaselogid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [dbo].[InsertErrorLog]
  @errorlogid [int] OUTPUT, 
  @errortime [datetime], 
  @username [sysname], 
  @errornumber [int], 
  @errorseverity [int], 
  @errorstate [int], 
  @errorprocedure [nvarchar](126), 
  @errorline [int], 
  @errormessage [nvarchar](4000)
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [dbo].[ErrorLog]([Errortime],
            [Username],
            [Errornumber],
            [Errorseverity],
            [Errorstate],
            [Errorprocedure],
            [Errorline],
            [Errormessage])
          VALUES(@errortime,
              @username,
              @errornumber,
              @errorseverity,
              @errorstate,
              @errorprocedure,
              @errorline,
              @errormessage)
      SET @errorlogid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [HumanResources].[InsertDepartment]
  @departmentid [smallint] OUTPUT, 
  @name [name], 
  @groupname [name], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [HumanResources].[Department]([Name],
            [Groupname],
            [Modifieddate])
          VALUES(@name,
              @groupname,
              @modifieddate)
      SET @departmentid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [HumanResources].[InsertEmployee]
  @businessentityid [int], 
  @nationalidnumber [nvarchar](15), 
  @loginid [nvarchar](256), 
  @organizationnode [hierarchyid], 
  @jobtitle [nvarchar](50), 
  @birthdate [date], 
  @maritalstatus [nchar](1), 
  @gender [nchar](1), 
  @hiredate [date], 
  @salariedflag [Flag], 
  @vacationhours [smallint], 
  @sickleavehours [smallint], 
  @currentflag [Flag], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [HumanResources].[Employee]([Businessentityid],
            [Nationalidnumber],
            [Loginid],
            [Organizationnode],
            [Jobtitle],
            [Birthdate],
            [Maritalstatus],
            [Gender],
            [Hiredate],
            [Salariedflag],
            [Vacationhours],
            [Sickleavehours],
            [Currentflag],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @nationalidnumber,
              @loginid,
              @organizationnode,
              @jobtitle,
              @birthdate,
              @maritalstatus,
              @gender,
              @hiredate,
              @salariedflag,
              @vacationhours,
              @sickleavehours,
              @currentflag,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [HumanResources].[InsertEmployeeDepartmentHistory]
  @businessentityid [int], 
  @departmentid [smallint], 
  @shiftid [tinyint], 
  @startdate [date], 
  @enddate [date], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [HumanResources].[EmployeeDepartmentHistory]([Businessentityid],
            [Departmentid],
            [Shiftid],
            [Startdate],
            [Enddate],
            [Modifieddate])
          VALUES(@businessentityid,
              @departmentid,
              @shiftid,
              @startdate,
              @enddate,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [HumanResources].[InsertEmployeePayHistory]
  @businessentityid [int], 
  @ratechangedate [datetime], 
  @rate [money], 
  @payfrequency [tinyint], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [HumanResources].[EmployeePayHistory]([Businessentityid],
            [Ratechangedate],
            [Rate],
            [Payfrequency],
            [Modifieddate])
          VALUES(@businessentityid,
              @ratechangedate,
              @rate,
              @payfrequency,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [HumanResources].[InsertJobCandidate]
  @jobcandidateid [int] OUTPUT, 
  @businessentityid [int], 
  @resume [xml], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [HumanResources].[JobCandidate]([Businessentityid],
            [Resume],
            [Modifieddate])
          VALUES(@businessentityid,
              @resume,
              @modifieddate)
      SET @jobcandidateid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [HumanResources].[Insert1JobCandidate]
  @jobcandidateid [int] OUTPUT, 
  @resume [xml], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [HumanResources].[JobCandidate]([Resume],
            [Modifieddate])
          VALUES(@resume,
              @modifieddate)
      SET @jobcandidateid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [HumanResources].[InsertShift]
  @shiftid [tinyint] OUTPUT, 
  @name [name], 
  @starttime [time], 
  @endtime [time], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [HumanResources].[Shift]([Name],
            [Starttime],
            [Endtime],
            [Modifieddate])
          VALUES(@name,
              @starttime,
              @endtime,
              @modifieddate)
      SET @shiftid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Person].[InsertAddress]
  @addressid [int] OUTPUT, 
  @addressline1 [nvarchar](60), 
  @addressline2 [nvarchar](60), 
  @city [nvarchar](30), 
  @stateprovinceid [int], 
  @postalcode [nvarchar](15), 
  @spatiallocation [geography], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[Address]([Addressline1],
            [Addressline2],
            [City],
            [Stateprovinceid],
            [Postalcode],
            [Spatiallocation],
            [Rowguid],
            [Modifieddate])
          VALUES(@addressline1,
              @addressline2,
              @city,
              @stateprovinceid,
              @postalcode,
              @spatiallocation,
              @rowguid,
              @modifieddate)
      SET @addressid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Person].[InsertAddressType]
  @addresstypeid [int] OUTPUT, 
  @name [name], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[AddressType]([Name],
            [Rowguid],
            [Modifieddate])
          VALUES(@name,
              @rowguid,
              @modifieddate)
      SET @addresstypeid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Person].[InsertBusinessEntity]
  @businessentityid [int] OUTPUT, 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[BusinessEntity]([Rowguid],
            [Modifieddate])
          VALUES(@rowguid,
              @modifieddate)
      SET @businessentityid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Person].[InsertBusinessEntityAddress]
  @businessentityid [int], 
  @addressid [int], 
  @addresstypeid [int], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[BusinessEntityAddress]([Businessentityid],
            [Addressid],
            [Addresstypeid],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @addressid,
              @addresstypeid,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Person].[InsertBusinessEntityContact]
  @businessentityid [int], 
  @personid [int], 
  @contacttypeid [int], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[BusinessEntityContact]([Businessentityid],
            [Personid],
            [Contacttypeid],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @personid,
              @contacttypeid,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Person].[InsertContactType]
  @contacttypeid [int] OUTPUT, 
  @name [name], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[ContactType]([Name],
            [Modifieddate])
          VALUES(@name,
              @modifieddate)
      SET @contacttypeid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Person].[InsertCountryRegion]
  @countryregioncode [nvarchar](3), 
  @name [name], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[CountryRegion]([Countryregioncode],
            [Name],
            [Modifieddate])
          VALUES(@countryregioncode,
              @name,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Person].[InsertEmailAddress]
  @businessentityid [int], 
  @emailaddressid [int] OUTPUT, 
  @emailaddress [nvarchar](50), 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[EmailAddress]([Businessentityid],
            [Emailaddress],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @emailaddress,
              @rowguid,
              @modifieddate)
      SET @emailaddressid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Person].[InsertPassword]
  @businessentityid [int], 
  @passwordhash [varchar](128), 
  @passwordsalt [varchar](10), 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[Password]([Businessentityid],
            [Passwordhash],
            [Passwordsalt],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @passwordhash,
              @passwordsalt,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Person].[InsertPerson]
  @businessentityid [int], 
  @persontype [nchar](2), 
  @namestyle [NameStyle], 
  @title [nvarchar](8), 
  @firstname [name], 
  @middlename [name], 
  @lastname [name], 
  @suffix [nvarchar](10), 
  @emailpromotion [int], 
  @additionalcontactinfo [xml], 
  @demographics [xml], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[Person]([Businessentityid],
            [Persontype],
            [Namestyle],
            [Title],
            [Firstname],
            [Middlename],
            [Lastname],
            [Suffix],
            [Emailpromotion],
            [Additionalcontactinfo],
            [Demographics],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @persontype,
              @namestyle,
              @title,
              @firstname,
              @middlename,
              @lastname,
              @suffix,
              @emailpromotion,
              @additionalcontactinfo,
              @demographics,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Person].[InsertPersonPhone]
  @businessentityid [int], 
  @phonenumber [phone], 
  @phonenumbertypeid [int], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[PersonPhone]([Businessentityid],
            [Phonenumber],
            [Phonenumbertypeid],
            [Modifieddate])
          VALUES(@businessentityid,
              @phonenumber,
              @phonenumbertypeid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Person].[InsertPhoneNumberType]
  @phonenumbertypeid [int] OUTPUT, 
  @name [name], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[PhoneNumberType]([Name],
            [Modifieddate])
          VALUES(@name,
              @modifieddate)
      SET @phonenumbertypeid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Person].[InsertStateProvince]
  @stateprovinceid [int] OUTPUT, 
  @stateprovincecode [nchar](3), 
  @countryregioncode [nvarchar](3), 
  @isonlystateprovinceflag [Flag], 
  @name [name], 
  @territoryid [int], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Person].[StateProvince]([Stateprovincecode],
            [Countryregioncode],
            [Isonlystateprovinceflag],
            [Name],
            [Territoryid],
            [Rowguid],
            [Modifieddate])
          VALUES(@stateprovincecode,
              @countryregioncode,
              @isonlystateprovinceflag,
              @name,
              @territoryid,
              @rowguid,
              @modifieddate)
      SET @stateprovinceid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertBillOfMaterials]
  @billofmaterialsid [int] OUTPUT, 
  @productassemblyid [int], 
  @componentid [int], 
  @startdate [datetime], 
  @enddate [datetime], 
  @unitmeasurecode [nchar](3), 
  @bomlevel [smallint], 
  @perassemblyqty [decimal], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[BillOfMaterials]([Productassemblyid],
            [Componentid],
            [Startdate],
            [Enddate],
            [Unitmeasurecode],
            [Bomlevel],
            [Perassemblyqty],
            [Modifieddate])
          VALUES(@productassemblyid,
              @componentid,
              @startdate,
              @enddate,
              @unitmeasurecode,
              @bomlevel,
              @perassemblyqty,
              @modifieddate)
      SET @billofmaterialsid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[Insert1BillOfMaterials]
  @billofmaterialsid [int] OUTPUT, 
  @componentid [int], 
  @startdate [datetime], 
  @enddate [datetime], 
  @unitmeasurecode [nchar](3), 
  @bomlevel [smallint], 
  @perassemblyqty [decimal], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[BillOfMaterials]([Componentid],
            [Startdate],
            [Enddate],
            [Unitmeasurecode],
            [Bomlevel],
            [Perassemblyqty],
            [Modifieddate])
          VALUES(@componentid,
              @startdate,
              @enddate,
              @unitmeasurecode,
              @bomlevel,
              @perassemblyqty,
              @modifieddate)
      SET @billofmaterialsid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertCulture]
  @cultureid [nchar](6), 
  @name [name], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[Culture]([Cultureid],
            [Name],
            [Modifieddate])
          VALUES(@cultureid,
              @name,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertDocument]
  @documentnode [hierarchyid], 
  @title [nvarchar](50), 
  @owner [int], 
  @folderflag [bit], 
  @filename [nvarchar](400), 
  @fileextension [nvarchar](8), 
  @revision [nchar](5), 
  @changenumber [int], 
  @status [tinyint], 
  @documentsummary [nvarchar](max), 
  @document [varbinary](max), 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[Document]([Documentnode],
            [Title],
            [Owner],
            [Folderflag],
            [Filename],
            [Fileextension],
            [Revision],
            [Changenumber],
            [Status],
            [Documentsummary],
            [Document],
            [Rowguid],
            [Modifieddate])
          VALUES(@documentnode,
              @title,
              @owner,
              @folderflag,
              @filename,
              @fileextension,
              @revision,
              @changenumber,
              @status,
              @documentsummary,
              @document,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertIllustration]
  @illustrationid [int] OUTPUT, 
  @diagram [xml], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[Illustration]([Diagram],
            [Modifieddate])
          VALUES(@diagram,
              @modifieddate)
      SET @illustrationid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertLocation]
  @locationid [smallint] OUTPUT, 
  @name [name], 
  @costrate [smallmoney], 
  @availability [decimal], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[Location]([Name],
            [Costrate],
            [Availability],
            [Modifieddate])
          VALUES(@name,
              @costrate,
              @availability,
              @modifieddate)
      SET @locationid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertProduct]
  @productid [int] OUTPUT, 
  @name [name], 
  @productnumber [nvarchar](25), 
  @makeflag [Flag], 
  @finishedgoodsflag [Flag], 
  @color [nvarchar](15), 
  @safetystocklevel [smallint], 
  @reorderpoint [smallint], 
  @standardcost [money], 
  @listprice [money], 
  @size [nvarchar](5), 
  @sizeunitmeasurecode [nchar](3), 
  @weightunitmeasurecode [nchar](3), 
  @weight [decimal], 
  @daystomanufacture [int], 
  @productline [nchar](2), 
  @class [nchar](2), 
  @style [nchar](2), 
  @productsubcategoryid [int], 
  @productmodelid [int], 
  @sellstartdate [datetime], 
  @sellenddate [datetime], 
  @discontinueddate [datetime], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[Product]([Name],
            [Productnumber],
            [Makeflag],
            [Finishedgoodsflag],
            [Color],
            [Safetystocklevel],
            [Reorderpoint],
            [Standardcost],
            [Listprice],
            [Size],
            [Sizeunitmeasurecode],
            [Weightunitmeasurecode],
            [Weight],
            [Daystomanufacture],
            [Productline],
            [Class],
            [Style],
            [Productsubcategoryid],
            [Productmodelid],
            [Sellstartdate],
            [Sellenddate],
            [Discontinueddate],
            [Rowguid],
            [Modifieddate])
          VALUES(@name,
              @productnumber,
              @makeflag,
              @finishedgoodsflag,
              @color,
              @safetystocklevel,
              @reorderpoint,
              @standardcost,
              @listprice,
              @size,
              @sizeunitmeasurecode,
              @weightunitmeasurecode,
              @weight,
              @daystomanufacture,
              @productline,
              @class,
              @style,
              @productsubcategoryid,
              @productmodelid,
              @sellstartdate,
              @sellenddate,
              @discontinueddate,
              @rowguid,
              @modifieddate)
      SET @productid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[Insert1Product]
  @productid [int] OUTPUT, 
  @name [name], 
  @productnumber [nvarchar](25), 
  @makeflag [Flag], 
  @finishedgoodsflag [Flag], 
  @color [nvarchar](15), 
  @safetystocklevel [smallint], 
  @reorderpoint [smallint], 
  @standardcost [money], 
  @listprice [money], 
  @size [nvarchar](5), 
  @weight [decimal], 
  @daystomanufacture [int], 
  @productline [nchar](2), 
  @class [nchar](2), 
  @style [nchar](2), 
  @sellstartdate [datetime], 
  @sellenddate [datetime], 
  @discontinueddate [datetime], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[Product]([Name],
            [Productnumber],
            [Makeflag],
            [Finishedgoodsflag],
            [Color],
            [Safetystocklevel],
            [Reorderpoint],
            [Standardcost],
            [Listprice],
            [Size],
            [Weight],
            [Daystomanufacture],
            [Productline],
            [Class],
            [Style],
            [Sellstartdate],
            [Sellenddate],
            [Discontinueddate],
            [Rowguid],
            [Modifieddate])
          VALUES(@name,
              @productnumber,
              @makeflag,
              @finishedgoodsflag,
              @color,
              @safetystocklevel,
              @reorderpoint,
              @standardcost,
              @listprice,
              @size,
              @weight,
              @daystomanufacture,
              @productline,
              @class,
              @style,
              @sellstartdate,
              @sellenddate,
              @discontinueddate,
              @rowguid,
              @modifieddate)
      SET @productid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductCategory]
  @productcategoryid [int] OUTPUT, 
  @name [name], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductCategory]([Name],
            [Rowguid],
            [Modifieddate])
          VALUES(@name,
              @rowguid,
              @modifieddate)
      SET @productcategoryid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductCostHistory]
  @productid [int], 
  @startdate [datetime], 
  @enddate [datetime], 
  @standardcost [money], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductCostHistory]([Productid],
            [Startdate],
            [Enddate],
            [Standardcost],
            [Modifieddate])
          VALUES(@productid,
              @startdate,
              @enddate,
              @standardcost,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductDescription]
  @productdescriptionid [int] OUTPUT, 
  @description [nvarchar](400), 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductDescription]([Description],
            [Rowguid],
            [Modifieddate])
          VALUES(@description,
              @rowguid,
              @modifieddate)
      SET @productdescriptionid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductDocument]
  @productid [int], 
  @documentnode [hierarchyid], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductDocument]([Productid],
            [Documentnode],
            [Modifieddate])
          VALUES(@productid,
              @documentnode,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductInventory]
  @productid [int], 
  @locationid [smallint], 
  @shelf [nvarchar](10), 
  @bin [tinyint], 
  @quantity [smallint], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductInventory]([Productid],
            [Locationid],
            [Shelf],
            [Bin],
            [Quantity],
            [Rowguid],
            [Modifieddate])
          VALUES(@productid,
              @locationid,
              @shelf,
              @bin,
              @quantity,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductListPriceHistory]
  @productid [int], 
  @startdate [datetime], 
  @enddate [datetime], 
  @listprice [money], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductListPriceHistory]([Productid],
            [Startdate],
            [Enddate],
            [Listprice],
            [Modifieddate])
          VALUES(@productid,
              @startdate,
              @enddate,
              @listprice,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductModel]
  @productmodelid [int] OUTPUT, 
  @name [name], 
  @catalogdescription [xml], 
  @instructions [xml], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductModel]([Name],
            [Catalogdescription],
            [Instructions],
            [Rowguid],
            [Modifieddate])
          VALUES(@name,
              @catalogdescription,
              @instructions,
              @rowguid,
              @modifieddate)
      SET @productmodelid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductModelIllustration]
  @productmodelid [int], 
  @illustrationid [int], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductModelIllustration]([Productmodelid],
            [Illustrationid],
            [Modifieddate])
          VALUES(@productmodelid,
              @illustrationid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductModelProductDescriptionCulture]
  @productmodelid [int], 
  @productdescriptionid [int], 
  @cultureid [nchar](6), 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductModelProductDescriptionCulture]([Productmodelid],
            [Productdescriptionid],
            [Cultureid],
            [Modifieddate])
          VALUES(@productmodelid,
              @productdescriptionid,
              @cultureid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductPhoto]
  @productphotoid [int] OUTPUT, 
  @thumbnailphoto [varbinary](max), 
  @thumbnailphotofilename [nvarchar](50), 
  @largephoto [varbinary](max), 
  @largephotofilename [nvarchar](50), 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductPhoto]([Thumbnailphoto],
            [Thumbnailphotofilename],
            [Largephoto],
            [Largephotofilename],
            [Modifieddate])
          VALUES(@thumbnailphoto,
              @thumbnailphotofilename,
              @largephoto,
              @largephotofilename,
              @modifieddate)
      SET @productphotoid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductProductPhoto]
  @productid [int], 
  @productphotoid [int], 
  @primary [Flag], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductProductPhoto]([Productid],
            [Productphotoid],
            [Primary],
            [Modifieddate])
          VALUES(@productid,
              @productphotoid,
              @primary,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductReview]
  @productreviewid [int] OUTPUT, 
  @productid [int], 
  @reviewername [name], 
  @reviewdate [datetime], 
  @emailaddress [nvarchar](50), 
  @rating [int], 
  @comments [nvarchar](3850), 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductReview]([Productid],
            [Reviewername],
            [Reviewdate],
            [Emailaddress],
            [Rating],
            [Comments],
            [Modifieddate])
          VALUES(@productid,
              @reviewername,
              @reviewdate,
              @emailaddress,
              @rating,
              @comments,
              @modifieddate)
      SET @productreviewid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertProductSubcategory]
  @productsubcategoryid [int] OUTPUT, 
  @productcategoryid [int], 
  @name [name], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ProductSubcategory]([Productcategoryid],
            [Name],
            [Rowguid],
            [Modifieddate])
          VALUES(@productcategoryid,
              @name,
              @rowguid,
              @modifieddate)
      SET @productsubcategoryid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertScrapReason]
  @scrapreasonid [smallint] OUTPUT, 
  @name [name], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[ScrapReason]([Name],
            [Modifieddate])
          VALUES(@name,
              @modifieddate)
      SET @scrapreasonid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertTransactionHistory]
  @transactionid [int] OUTPUT, 
  @productid [int], 
  @referenceorderid [int], 
  @referenceorderlineid [int], 
  @transactiondate [datetime], 
  @transactiontype [nchar](1), 
  @quantity [int], 
  @actualcost [money], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[TransactionHistory]([Productid],
            [Referenceorderid],
            [Referenceorderlineid],
            [Transactiondate],
            [Transactiontype],
            [Quantity],
            [Actualcost],
            [Modifieddate])
          VALUES(@productid,
              @referenceorderid,
              @referenceorderlineid,
              @transactiondate,
              @transactiontype,
              @quantity,
              @actualcost,
              @modifieddate)
      SET @transactionid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertTransactionHistoryArchive]
  @transactionid [int], 
  @productid [int], 
  @referenceorderid [int], 
  @referenceorderlineid [int], 
  @transactiondate [datetime], 
  @transactiontype [nchar](1), 
  @quantity [int], 
  @actualcost [money], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[TransactionHistoryArchive]([Transactionid],
            [Productid],
            [Referenceorderid],
            [Referenceorderlineid],
            [Transactiondate],
            [Transactiontype],
            [Quantity],
            [Actualcost],
            [Modifieddate])
          VALUES(@transactionid,
              @productid,
              @referenceorderid,
              @referenceorderlineid,
              @transactiondate,
              @transactiontype,
              @quantity,
              @actualcost,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertUnitMeasure]
  @unitmeasurecode [nchar](3), 
  @name [name], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[UnitMeasure]([Unitmeasurecode],
            [Name],
            [Modifieddate])
          VALUES(@unitmeasurecode,
              @name,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Production].[InsertWorkOrder]
  @workorderid [int] OUTPUT, 
  @productid [int], 
  @orderqty [int], 
  @scrappedqty [smallint], 
  @startdate [datetime], 
  @enddate [datetime], 
  @duedate [datetime], 
  @scrapreasonid [smallint], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[WorkOrder]([Productid],
            [Orderqty],
            [Scrappedqty],
            [Startdate],
            [Enddate],
            [Duedate],
            [Scrapreasonid],
            [Modifieddate])
          VALUES(@productid,
              @orderqty,
              @scrappedqty,
              @startdate,
              @enddate,
              @duedate,
              @scrapreasonid,
              @modifieddate)
      SET @workorderid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[Insert1WorkOrder]
  @workorderid [int] OUTPUT, 
  @productid [int], 
  @orderqty [int], 
  @scrappedqty [smallint], 
  @startdate [datetime], 
  @enddate [datetime], 
  @duedate [datetime], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[WorkOrder]([Productid],
            [Orderqty],
            [Scrappedqty],
            [Startdate],
            [Enddate],
            [Duedate],
            [Modifieddate])
          VALUES(@productid,
              @orderqty,
              @scrappedqty,
              @startdate,
              @enddate,
              @duedate,
              @modifieddate)
      SET @workorderid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Production].[InsertWorkOrderRouting]
  @workorderid [int], 
  @productid [int], 
  @operationsequence [smallint], 
  @locationid [smallint], 
  @scheduledstartdate [datetime], 
  @scheduledenddate [datetime], 
  @actualstartdate [datetime], 
  @actualenddate [datetime], 
  @actualresourcehrs [decimal], 
  @plannedcost [money], 
  @actualcost [money], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Production].[WorkOrderRouting]([Workorderid],
            [Productid],
            [Operationsequence],
            [Locationid],
            [Scheduledstartdate],
            [Scheduledenddate],
            [Actualstartdate],
            [Actualenddate],
            [Actualresourcehrs],
            [Plannedcost],
            [Actualcost],
            [Modifieddate])
          VALUES(@workorderid,
              @productid,
              @operationsequence,
              @locationid,
              @scheduledstartdate,
              @scheduledenddate,
              @actualstartdate,
              @actualenddate,
              @actualresourcehrs,
              @plannedcost,
              @actualcost,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Purchasing].[InsertProductVendor]
  @productid [int], 
  @businessentityid [int], 
  @averageleadtime [int], 
  @standardprice [money], 
  @lastreceiptcost [money], 
  @lastreceiptdate [datetime], 
  @minorderqty [int], 
  @maxorderqty [int], 
  @onorderqty [int], 
  @unitmeasurecode [nchar](3), 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Purchasing].[ProductVendor]([Productid],
            [Businessentityid],
            [Averageleadtime],
            [Standardprice],
            [Lastreceiptcost],
            [Lastreceiptdate],
            [Minorderqty],
            [Maxorderqty],
            [Onorderqty],
            [Unitmeasurecode],
            [Modifieddate])
          VALUES(@productid,
              @businessentityid,
              @averageleadtime,
              @standardprice,
              @lastreceiptcost,
              @lastreceiptdate,
              @minorderqty,
              @maxorderqty,
              @onorderqty,
              @unitmeasurecode,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Purchasing].[InsertPurchaseOrderDetail]
  @purchaseorderid [int], 
  @purchaseorderdetailid [int] OUTPUT, 
  @duedate [datetime], 
  @orderqty [smallint], 
  @productid [int], 
  @unitprice [money], 
  @receivedqty [decimal], 
  @rejectedqty [decimal], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Purchasing].[PurchaseOrderDetail]([Purchaseorderid],
            [Duedate],
            [Orderqty],
            [Productid],
            [Unitprice],
            [Receivedqty],
            [Rejectedqty],
            [Modifieddate])
          VALUES(@purchaseorderid,
              @duedate,
              @orderqty,
              @productid,
              @unitprice,
              @receivedqty,
              @rejectedqty,
              @modifieddate)
      SET @purchaseorderdetailid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Purchasing].[InsertPurchaseOrderHeader]
  @purchaseorderid [int] OUTPUT, 
  @revisionnumber [tinyint], 
  @status [tinyint], 
  @employeeid [int], 
  @vendorid [int], 
  @shipmethodid [int], 
  @orderdate [datetime], 
  @shipdate [datetime], 
  @subtotal [money], 
  @taxamt [money], 
  @freight [money], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Purchasing].[PurchaseOrderHeader]([Revisionnumber],
            [Status],
            [Employeeid],
            [Vendorid],
            [Shipmethodid],
            [Orderdate],
            [Shipdate],
            [Subtotal],
            [Taxamt],
            [Freight],
            [Modifieddate])
          VALUES(@revisionnumber,
              @status,
              @employeeid,
              @vendorid,
              @shipmethodid,
              @orderdate,
              @shipdate,
              @subtotal,
              @taxamt,
              @freight,
              @modifieddate)
      SET @purchaseorderid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Purchasing].[InsertShipMethod]
  @shipmethodid [int] OUTPUT, 
  @name [name], 
  @shipbase [money], 
  @shiprate [money], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Purchasing].[ShipMethod]([Name],
            [Shipbase],
            [Shiprate],
            [Rowguid],
            [Modifieddate])
          VALUES(@name,
              @shipbase,
              @shiprate,
              @rowguid,
              @modifieddate)
      SET @shipmethodid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Purchasing].[InsertVendor]
  @businessentityid [int], 
  @accountnumber [accountnumber], 
  @name [name], 
  @creditrating [tinyint], 
  @preferredvendorstatus [Flag], 
  @activeflag [Flag], 
  @purchasingwebserviceurl [nvarchar](1024), 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Purchasing].[Vendor]([Businessentityid],
            [Accountnumber],
            [Name],
            [Creditrating],
            [Preferredvendorstatus],
            [Activeflag],
            [Purchasingwebserviceurl],
            [Modifieddate])
          VALUES(@businessentityid,
              @accountnumber,
              @name,
              @creditrating,
              @preferredvendorstatus,
              @activeflag,
              @purchasingwebserviceurl,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[InsertCountryRegionCurrency]
  @countryregioncode [nvarchar](3), 
  @currencycode [nchar](3), 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[CountryRegionCurrency]([Countryregioncode],
            [Currencycode],
            [Modifieddate])
          VALUES(@countryregioncode,
              @currencycode,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[InsertCreditCard]
  @creditcardid [int] OUTPUT, 
  @cardtype [nvarchar](50), 
  @cardnumber [nvarchar](25), 
  @expmonth [tinyint], 
  @expyear [smallint], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[CreditCard]([Cardtype],
            [Cardnumber],
            [Expmonth],
            [Expyear],
            [Modifieddate])
          VALUES(@cardtype,
              @cardnumber,
              @expmonth,
              @expyear,
              @modifieddate)
      SET @creditcardid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[InsertCurrency]
  @currencycode [nchar](3), 
  @name [name], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[Currency]([Currencycode],
            [Name],
            [Modifieddate])
          VALUES(@currencycode,
              @name,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[InsertCurrencyRate]
  @currencyrateid [int] OUTPUT, 
  @currencyratedate [datetime], 
  @fromcurrencycode [nchar](3), 
  @tocurrencycode [nchar](3), 
  @averagerate [money], 
  @endofdayrate [money], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[CurrencyRate]([Currencyratedate],
            [Fromcurrencycode],
            [Tocurrencycode],
            [Averagerate],
            [Endofdayrate],
            [Modifieddate])
          VALUES(@currencyratedate,
              @fromcurrencycode,
              @tocurrencycode,
              @averagerate,
              @endofdayrate,
              @modifieddate)
      SET @currencyrateid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[InsertCustomer]
  @customerid [int] OUTPUT, 
  @personid [int], 
  @storeid [int], 
  @territoryid [int], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[Customer]([Personid],
            [Storeid],
            [Territoryid],
            [Rowguid],
            [Modifieddate])
          VALUES(@personid,
              @storeid,
              @territoryid,
              @rowguid,
              @modifieddate)
      SET @customerid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[Insert1Customer]
  @customerid [int] OUTPUT, 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[Customer]([Rowguid],
            [Modifieddate])
          VALUES(@rowguid,
              @modifieddate)
      SET @customerid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[InsertPersonCreditCard]
  @businessentityid [int], 
  @creditcardid [int], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[PersonCreditCard]([Businessentityid],
            [Creditcardid],
            [Modifieddate])
          VALUES(@businessentityid,
              @creditcardid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSalesOrderDetail]
  @salesorderid [int], 
  @salesorderdetailid [int] OUTPUT, 
  @carriertrackingnumber [nvarchar](25), 
  @orderqty [smallint], 
  @productid [int], 
  @specialofferid [int], 
  @unitprice [money], 
  @unitpricediscount [money], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesOrderDetail]([Salesorderid],
            [Carriertrackingnumber],
            [Orderqty],
            [Productid],
            [Specialofferid],
            [Unitprice],
            [Unitpricediscount],
            [Rowguid],
            [Modifieddate])
          VALUES(@salesorderid,
              @carriertrackingnumber,
              @orderqty,
              @productid,
              @specialofferid,
              @unitprice,
              @unitpricediscount,
              @rowguid,
              @modifieddate)
      SET @salesorderdetailid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSalesOrderHeader]
  @salesorderid [int] OUTPUT, 
  @revisionnumber [tinyint], 
  @orderdate [datetime], 
  @duedate [datetime], 
  @shipdate [datetime], 
  @status [tinyint], 
  @onlineorderflag [Flag], 
  @purchaseordernumber [ordernumber], 
  @accountnumber [accountnumber], 
  @customerid [int], 
  @salespersonid [int], 
  @territoryid [int], 
  @billtoaddressid [int], 
  @shiptoaddressid [int], 
  @shipmethodid [int], 
  @creditcardid [int], 
  @creditcardapprovalcode [varchar](15), 
  @currencyrateid [int], 
  @subtotal [money], 
  @taxamt [money], 
  @freight [money], 
  @comment [nvarchar](128), 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesOrderHeader]([Revisionnumber],
            [Orderdate],
            [Duedate],
            [Shipdate],
            [Status],
            [Onlineorderflag],
            [Purchaseordernumber],
            [Accountnumber],
            [Customerid],
            [Salespersonid],
            [Territoryid],
            [Billtoaddressid],
            [Shiptoaddressid],
            [Shipmethodid],
            [Creditcardid],
            [Creditcardapprovalcode],
            [Currencyrateid],
            [Subtotal],
            [Taxamt],
            [Freight],
            [Comment],
            [Rowguid],
            [Modifieddate])
          VALUES(@revisionnumber,
              @orderdate,
              @duedate,
              @shipdate,
              @status,
              @onlineorderflag,
              @purchaseordernumber,
              @accountnumber,
              @customerid,
              @salespersonid,
              @territoryid,
              @billtoaddressid,
              @shiptoaddressid,
              @shipmethodid,
              @creditcardid,
              @creditcardapprovalcode,
              @currencyrateid,
              @subtotal,
              @taxamt,
              @freight,
              @comment,
              @rowguid,
              @modifieddate)
      SET @salesorderid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[Insert1SalesOrderHeader]
  @salesorderid [int] OUTPUT, 
  @revisionnumber [tinyint], 
  @orderdate [datetime], 
  @duedate [datetime], 
  @shipdate [datetime], 
  @status [tinyint], 
  @onlineorderflag [Flag], 
  @purchaseordernumber [ordernumber], 
  @accountnumber [accountnumber], 
  @customerid [int], 
  @billtoaddressid [int], 
  @shiptoaddressid [int], 
  @shipmethodid [int], 
  @creditcardapprovalcode [varchar](15), 
  @subtotal [money], 
  @taxamt [money], 
  @freight [money], 
  @comment [nvarchar](128), 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesOrderHeader]([Revisionnumber],
            [Orderdate],
            [Duedate],
            [Shipdate],
            [Status],
            [Onlineorderflag],
            [Purchaseordernumber],
            [Accountnumber],
            [Customerid],
            [Billtoaddressid],
            [Shiptoaddressid],
            [Shipmethodid],
            [Creditcardapprovalcode],
            [Subtotal],
            [Taxamt],
            [Freight],
            [Comment],
            [Rowguid],
            [Modifieddate])
          VALUES(@revisionnumber,
              @orderdate,
              @duedate,
              @shipdate,
              @status,
              @onlineorderflag,
              @purchaseordernumber,
              @accountnumber,
              @customerid,
              @billtoaddressid,
              @shiptoaddressid,
              @shipmethodid,
              @creditcardapprovalcode,
              @subtotal,
              @taxamt,
              @freight,
              @comment,
              @rowguid,
              @modifieddate)
      SET @salesorderid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSalesOrderHeaderSalesReason]
  @salesorderid [int], 
  @salesreasonid [int], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesOrderHeaderSalesReason]([Salesorderid],
            [Salesreasonid],
            [Modifieddate])
          VALUES(@salesorderid,
              @salesreasonid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSalesPerson]
  @businessentityid [int], 
  @territoryid [int], 
  @salesquota [money], 
  @bonus [money], 
  @commissionpct [smallmoney], 
  @salesytd [money], 
  @saleslastyear [money], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesPerson]([Businessentityid],
            [Territoryid],
            [Salesquota],
            [Bonus],
            [Commissionpct],
            [Salesytd],
            [Saleslastyear],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @territoryid,
              @salesquota,
              @bonus,
              @commissionpct,
              @salesytd,
              @saleslastyear,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[Insert1SalesPerson]
  @businessentityid [int], 
  @salesquota [money], 
  @bonus [money], 
  @commissionpct [smallmoney], 
  @salesytd [money], 
  @saleslastyear [money], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesPerson]([Businessentityid],
            [Salesquota],
            [Bonus],
            [Commissionpct],
            [Salesytd],
            [Saleslastyear],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @salesquota,
              @bonus,
              @commissionpct,
              @salesytd,
              @saleslastyear,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSalesPersonQuotaHistory]
  @businessentityid [int], 
  @quotadate [datetime], 
  @salesquota [money], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesPersonQuotaHistory]([Businessentityid],
            [Quotadate],
            [Salesquota],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @quotadate,
              @salesquota,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSalesReason]
  @salesreasonid [int] OUTPUT, 
  @name [name], 
  @reasontype [name], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesReason]([Name],
            [Reasontype],
            [Modifieddate])
          VALUES(@name,
              @reasontype,
              @modifieddate)
      SET @salesreasonid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSalesTaxRate]
  @salestaxrateid [int] OUTPUT, 
  @stateprovinceid [int], 
  @taxtype [tinyint], 
  @taxrate [smallmoney], 
  @name [name], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesTaxRate]([Stateprovinceid],
            [Taxtype],
            [Taxrate],
            [Name],
            [Rowguid],
            [Modifieddate])
          VALUES(@stateprovinceid,
              @taxtype,
              @taxrate,
              @name,
              @rowguid,
              @modifieddate)
      SET @salestaxrateid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSalesTerritory]
  @territoryid [int] OUTPUT, 
  @name [name], 
  @countryregioncode [nvarchar](3), 
  @group [nvarchar](50), 
  @salesytd [money], 
  @saleslastyear [money], 
  @costytd [money], 
  @costlastyear [money], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesTerritory]([Name],
            [Countryregioncode],
            [Group],
            [Salesytd],
            [Saleslastyear],
            [Costytd],
            [Costlastyear],
            [Rowguid],
            [Modifieddate])
          VALUES(@name,
              @countryregioncode,
              @group,
              @salesytd,
              @saleslastyear,
              @costytd,
              @costlastyear,
              @rowguid,
              @modifieddate)
      SET @territoryid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSalesTerritoryHistory]
  @businessentityid [int], 
  @territoryid [int], 
  @startdate [datetime], 
  @enddate [datetime], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SalesTerritoryHistory]([Businessentityid],
            [Territoryid],
            [Startdate],
            [Enddate],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @territoryid,
              @startdate,
              @enddate,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[InsertShoppingCartItem]
  @shoppingcartitemid [int] OUTPUT, 
  @shoppingcartid [nvarchar](50), 
  @quantity [int], 
  @productid [int], 
  @datecreated [datetime], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[ShoppingCartItem]([Shoppingcartid],
            [Quantity],
            [Productid],
            [Datecreated],
            [Modifieddate])
          VALUES(@shoppingcartid,
              @quantity,
              @productid,
              @datecreated,
              @modifieddate)
      SET @shoppingcartitemid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSpecialOffer]
  @specialofferid [int] OUTPUT, 
  @description [nvarchar](255), 
  @discountpct [smallmoney], 
  @type [nvarchar](50), 
  @category [nvarchar](50), 
  @startdate [datetime], 
  @enddate [datetime], 
  @minqty [int], 
  @maxqty [int], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SpecialOffer]([Description],
            [Discountpct],
            [Type],
            [Category],
            [Startdate],
            [Enddate],
            [Minqty],
            [Maxqty],
            [Rowguid],
            [Modifieddate])
          VALUES(@description,
              @discountpct,
              @type,
              @category,
              @startdate,
              @enddate,
              @minqty,
              @maxqty,
              @rowguid,
              @modifieddate)
      SET @specialofferid = SCOPE_IDENTITY();
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

CREATE OR ALTER PROCEDURE [Sales].[InsertSpecialOfferProduct]
  @specialofferid [int], 
  @productid [int], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[SpecialOfferProduct]([Specialofferid],
            [Productid],
            [Rowguid],
            [Modifieddate])
          VALUES(@specialofferid,
              @productid,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[InsertStore]
  @businessentityid [int], 
  @name [name], 
  @salespersonid [int], 
  @demographics [xml], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[Store]([Businessentityid],
            [Name],
            [Salespersonid],
            [Demographics],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @name,
              @salespersonid,
              @demographics,
              @rowguid,
              @modifieddate)
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

CREATE OR ALTER PROCEDURE [Sales].[Insert1Store]
  @businessentityid [int], 
  @name [name], 
  @demographics [xml], 
  @rowguid [uniqueidentifier], 
  @modifieddate [datetime]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      INSERT INTO [Sales].[Store]([Businessentityid],
            [Name],
            [Demographics],
            [Rowguid],
            [Modifieddate])
          VALUES(@businessentityid,
              @name,
              @demographics,
              @rowguid,
              @modifieddate)
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

