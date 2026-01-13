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
CREATE OR ALTER PROCEDURE [dbo].[UpdateAWBuildVersion]
  @systeminformationid [tinyint], 
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
      UPDATE [dbo].[AWBuildVersion]
        SET
           [Database Version] = @databaseVersion,
           [Versiondate] = @versiondate,
           [Modifieddate] = @modifieddate
         WHERE
           [Systeminformationid] = @systeminformationid
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

CREATE OR ALTER PROCEDURE [dbo].[UpdateDatabaseLog]
  @databaselogid [int], 
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
      UPDATE [dbo].[DatabaseLog]
        SET
           [Posttime] = @posttime,
           [Databaseuser] = @databaseuser,
           [Event] = @event,
           [Schema] = @schema,
           [Object] = @object,
           [Tsql] = @tsql,
           [Xmlevent] = @xmlevent
         WHERE
           [Databaselogid] = @databaselogid
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

CREATE OR ALTER PROCEDURE [dbo].[UpdateErrorLog]
  @errorlogid [int], 
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
      UPDATE [dbo].[ErrorLog]
        SET
           [Errortime] = @errortime,
           [Username] = @username,
           [Errornumber] = @errornumber,
           [Errorseverity] = @errorseverity,
           [Errorstate] = @errorstate,
           [Errorprocedure] = @errorprocedure,
           [Errorline] = @errorline,
           [Errormessage] = @errormessage
         WHERE
           [Errorlogid] = @errorlogid
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

CREATE OR ALTER PROCEDURE [HumanResources].[UpdateDepartment]
  @departmentid [smallint], 
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
      UPDATE [HumanResources].[Department]
        SET
           [Name] = @name,
           [Groupname] = @groupname,
           [Modifieddate] = @modifieddate
         WHERE
           [Departmentid] = @departmentid
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

CREATE OR ALTER PROCEDURE [HumanResources].[UpdateEmployee]
  @businessentityid [int], 
  @nationalidnumber [nvarchar](15), 
  @loginid [nvarchar](256), 
  @organizationnode [hierarchyid], 
  @organizationlevel [smallint], 
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
      UPDATE [HumanResources].[Employee]
        SET
           [Nationalidnumber] = @nationalidnumber,
           [Loginid] = @loginid,
           [Organizationnode] = @organizationnode,
           [Jobtitle] = @jobtitle,
           [Birthdate] = @birthdate,
           [Maritalstatus] = @maritalstatus,
           [Gender] = @gender,
           [Hiredate] = @hiredate,
           [Salariedflag] = @salariedflag,
           [Vacationhours] = @vacationhours,
           [Sickleavehours] = @sickleavehours,
           [Currentflag] = @currentflag,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid
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

CREATE OR ALTER PROCEDURE [HumanResources].[UpdateEmployeeDepartmentHistory]
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
      UPDATE [HumanResources].[EmployeeDepartmentHistory]
        SET
           [Enddate] = @enddate,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid AND [Startdate] = @startdate AND [Departmentid] = @departmentid AND [Shiftid] = @shiftid
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

CREATE OR ALTER PROCEDURE [HumanResources].[UpdateEmployeePayHistory]
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
      UPDATE [HumanResources].[EmployeePayHistory]
        SET
           [Rate] = @rate,
           [Payfrequency] = @payfrequency,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid AND [Ratechangedate] = @ratechangedate
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

CREATE OR ALTER PROCEDURE [HumanResources].[UpdateJobCandidate]
  @jobcandidateid [int], 
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
      UPDATE [HumanResources].[JobCandidate]
        SET
           [Businessentityid] = @businessentityid,
           [Resume] = @resume,
           [Modifieddate] = @modifieddate
         WHERE
           [Jobcandidateid] = @jobcandidateid
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

CREATE OR ALTER PROCEDURE [HumanResources].[Update1JobCandidate]
  @jobcandidateid [int], 
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
      UPDATE [HumanResources].[JobCandidate]
        SET
           [Businessentityid] = NULL,
           [Resume] = @resume,
           [Modifieddate] = @modifieddate
         WHERE
           [Jobcandidateid] = @jobcandidateid
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

CREATE OR ALTER PROCEDURE [HumanResources].[Update2JobCandidate]
  @jobcandidateid [int], 
  @businessentityid [int]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [HumanResources].[JobCandidate]
        SET
           [Businessentityid] = @businessentityid
         WHERE
           [Jobcandidateid] = @jobcandidateid
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER PROCEDURE [HumanResources].[UpdateShift]
  @shiftid [tinyint], 
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
      UPDATE [HumanResources].[Shift]
        SET
           [Name] = @name,
           [Starttime] = @starttime,
           [Endtime] = @endtime,
           [Modifieddate] = @modifieddate
         WHERE
           [Shiftid] = @shiftid
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

CREATE OR ALTER PROCEDURE [Person].[UpdateAddress]
  @addressid [int], 
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
      UPDATE [Person].[Address]
        SET
           [Addressline1] = @addressline1,
           [Addressline2] = @addressline2,
           [City] = @city,
           [Stateprovinceid] = @stateprovinceid,
           [Postalcode] = @postalcode,
           [Spatiallocation] = @spatiallocation,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Addressid] = @addressid
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

CREATE OR ALTER PROCEDURE [Person].[UpdateAddressType]
  @addresstypeid [int], 
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
      UPDATE [Person].[AddressType]
        SET
           [Name] = @name,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Addresstypeid] = @addresstypeid
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

CREATE OR ALTER PROCEDURE [Person].[UpdateBusinessEntity]
  @businessentityid [int], 
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
      UPDATE [Person].[BusinessEntity]
        SET
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid
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

CREATE OR ALTER PROCEDURE [Person].[UpdateBusinessEntityAddress]
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
      UPDATE [Person].[BusinessEntityAddress]
        SET
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid AND [Addressid] = @addressid AND [Addresstypeid] = @addresstypeid
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

CREATE OR ALTER PROCEDURE [Person].[UpdateBusinessEntityContact]
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
      UPDATE [Person].[BusinessEntityContact]
        SET
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid AND [Personid] = @personid AND [Contacttypeid] = @contacttypeid
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

CREATE OR ALTER PROCEDURE [Person].[UpdateContactType]
  @contacttypeid [int], 
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
      UPDATE [Person].[ContactType]
        SET
           [Name] = @name,
           [Modifieddate] = @modifieddate
         WHERE
           [Contacttypeid] = @contacttypeid
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

CREATE OR ALTER PROCEDURE [Person].[UpdateCountryRegion]
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
      UPDATE [Person].[CountryRegion]
        SET
           [Name] = @name,
           [Modifieddate] = @modifieddate
         WHERE
           [Countryregioncode] = @countryregioncode
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

CREATE OR ALTER PROCEDURE [Person].[UpdateEmailAddress]
  @businessentityid [int], 
  @emailaddressid [int], 
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
      UPDATE [Person].[EmailAddress]
        SET
           [Emailaddress] = @emailaddress,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid AND [Emailaddressid] = @emailaddressid
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

CREATE OR ALTER PROCEDURE [Person].[UpdatePassword]
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
      UPDATE [Person].[Password]
        SET
           [Passwordhash] = @passwordhash,
           [Passwordsalt] = @passwordsalt,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid
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

CREATE OR ALTER PROCEDURE [Person].[UpdatePerson]
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
      UPDATE [Person].[Person]
        SET
           [Persontype] = @persontype,
           [Namestyle] = @namestyle,
           [Title] = @title,
           [Firstname] = @firstname,
           [Middlename] = @middlename,
           [Lastname] = @lastname,
           [Suffix] = @suffix,
           [Emailpromotion] = @emailpromotion,
           [Additionalcontactinfo] = @additionalcontactinfo,
           [Demographics] = @demographics,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid
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

CREATE OR ALTER PROCEDURE [Person].[UpdatePersonPhone]
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
      UPDATE [Person].[PersonPhone]
        SET
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid AND [Phonenumber] = @phonenumber AND [Phonenumbertypeid] = @phonenumbertypeid
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

CREATE OR ALTER PROCEDURE [Person].[UpdatePhoneNumberType]
  @phonenumbertypeid [int], 
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
      UPDATE [Person].[PhoneNumberType]
        SET
           [Name] = @name,
           [Modifieddate] = @modifieddate
         WHERE
           [Phonenumbertypeid] = @phonenumbertypeid
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

CREATE OR ALTER PROCEDURE [Person].[UpdateStateProvince]
  @stateprovinceid [int], 
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
      UPDATE [Person].[StateProvince]
        SET
           [Stateprovincecode] = @stateprovincecode,
           [Countryregioncode] = @countryregioncode,
           [Isonlystateprovinceflag] = @isonlystateprovinceflag,
           [Name] = @name,
           [Territoryid] = @territoryid,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Stateprovinceid] = @stateprovinceid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateBillOfMaterials]
  @billofmaterialsid [int], 
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
      UPDATE [Production].[BillOfMaterials]
        SET
           [Productassemblyid] = @productassemblyid,
           [Componentid] = @componentid,
           [Startdate] = @startdate,
           [Enddate] = @enddate,
           [Unitmeasurecode] = @unitmeasurecode,
           [Bomlevel] = @bomlevel,
           [Perassemblyqty] = @perassemblyqty,
           [Modifieddate] = @modifieddate
         WHERE
           [Billofmaterialsid] = @billofmaterialsid
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

CREATE OR ALTER PROCEDURE [Production].[Update1BillOfMaterials]
  @billofmaterialsid [int], 
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
      UPDATE [Production].[BillOfMaterials]
        SET
           [Productassemblyid] = NULL,
           [Componentid] = @componentid,
           [Startdate] = @startdate,
           [Enddate] = @enddate,
           [Unitmeasurecode] = @unitmeasurecode,
           [Bomlevel] = @bomlevel,
           [Perassemblyqty] = @perassemblyqty,
           [Modifieddate] = @modifieddate
         WHERE
           [Billofmaterialsid] = @billofmaterialsid
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

CREATE OR ALTER PROCEDURE [Production].[Update2BillOfMaterials]
  @billofmaterialsid [int], 
  @productassemblyid [int]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Production].[BillOfMaterials]
        SET
           [Productassemblyid] = @productassemblyid
         WHERE
           [Billofmaterialsid] = @billofmaterialsid
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER PROCEDURE [Production].[UpdateCulture]
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
      UPDATE [Production].[Culture]
        SET
           [Name] = @name,
           [Modifieddate] = @modifieddate
         WHERE
           [Cultureid] = @cultureid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateDocument]
  @documentnode [hierarchyid], 
  @documentlevel [smallint], 
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
      UPDATE [Production].[Document]
        SET
           [Title] = @title,
           [Owner] = @owner,
           [Folderflag] = @folderflag,
           [Filename] = @filename,
           [Fileextension] = @fileextension,
           [Revision] = @revision,
           [Changenumber] = @changenumber,
           [Status] = @status,
           [Documentsummary] = @documentsummary,
           [Document] = @document,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Documentnode] = @documentnode
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

CREATE OR ALTER PROCEDURE [Production].[UpdateIllustration]
  @illustrationid [int], 
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
      UPDATE [Production].[Illustration]
        SET
           [Diagram] = @diagram,
           [Modifieddate] = @modifieddate
         WHERE
           [Illustrationid] = @illustrationid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateLocation]
  @locationid [smallint], 
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
      UPDATE [Production].[Location]
        SET
           [Name] = @name,
           [Costrate] = @costrate,
           [Availability] = @availability,
           [Modifieddate] = @modifieddate
         WHERE
           [Locationid] = @locationid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProduct]
  @productid [int], 
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
      UPDATE [Production].[Product]
        SET
           [Name] = @name,
           [Productnumber] = @productnumber,
           [Makeflag] = @makeflag,
           [Finishedgoodsflag] = @finishedgoodsflag,
           [Color] = @color,
           [Safetystocklevel] = @safetystocklevel,
           [Reorderpoint] = @reorderpoint,
           [Standardcost] = @standardcost,
           [Listprice] = @listprice,
           [Size] = @size,
           [Sizeunitmeasurecode] = @sizeunitmeasurecode,
           [Weightunitmeasurecode] = @weightunitmeasurecode,
           [Weight] = @weight,
           [Daystomanufacture] = @daystomanufacture,
           [Productline] = @productline,
           [Class] = @class,
           [Style] = @style,
           [Productsubcategoryid] = @productsubcategoryid,
           [Productmodelid] = @productmodelid,
           [Sellstartdate] = @sellstartdate,
           [Sellenddate] = @sellenddate,
           [Discontinueddate] = @discontinueddate,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Productid] = @productid
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

CREATE OR ALTER PROCEDURE [Production].[Update1Product]
  @productid [int], 
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
      UPDATE [Production].[Product]
        SET
           [Name] = @name,
           [Productnumber] = @productnumber,
           [Makeflag] = @makeflag,
           [Finishedgoodsflag] = @finishedgoodsflag,
           [Color] = @color,
           [Safetystocklevel] = @safetystocklevel,
           [Reorderpoint] = @reorderpoint,
           [Standardcost] = @standardcost,
           [Listprice] = @listprice,
           [Size] = @size,
           [Sizeunitmeasurecode] = NULL,
           [Weightunitmeasurecode] = NULL,
           [Weight] = @weight,
           [Daystomanufacture] = @daystomanufacture,
           [Productline] = @productline,
           [Class] = @class,
           [Style] = @style,
           [Productsubcategoryid] = NULL,
           [Productmodelid] = NULL,
           [Sellstartdate] = @sellstartdate,
           [Sellenddate] = @sellenddate,
           [Discontinueddate] = @discontinueddate,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Productid] = @productid
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

CREATE OR ALTER PROCEDURE [Production].[Update2Product]
  @productid [int], 
  @sizeunitmeasurecode [nchar](3), 
  @weightunitmeasurecode [nchar](3), 
  @productsubcategoryid [int], 
  @productmodelid [int]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Production].[Product]
        SET
           [Sizeunitmeasurecode] = @sizeunitmeasurecode,
           [Weightunitmeasurecode] = @weightunitmeasurecode,
           [Productsubcategoryid] = @productsubcategoryid,
           [Productmodelid] = @productmodelid
         WHERE
           [Productid] = @productid
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER PROCEDURE [Production].[UpdateProductCategory]
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
      UPDATE [Production].[ProductCategory]
        SET
           [Name] = @name,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Productcategoryid] = @productcategoryid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductCostHistory]
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
      UPDATE [Production].[ProductCostHistory]
        SET
           [Enddate] = @enddate,
           [Standardcost] = @standardcost,
           [Modifieddate] = @modifieddate
         WHERE
           [Productid] = @productid AND [Startdate] = @startdate
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductDescription]
  @productdescriptionid [int], 
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
      UPDATE [Production].[ProductDescription]
        SET
           [Description] = @description,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Productdescriptionid] = @productdescriptionid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductDocument]
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
      UPDATE [Production].[ProductDocument]
        SET
           [Modifieddate] = @modifieddate
         WHERE
           [Productid] = @productid AND [Documentnode] = @documentnode
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductInventory]
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
      UPDATE [Production].[ProductInventory]
        SET
           [Shelf] = @shelf,
           [Bin] = @bin,
           [Quantity] = @quantity,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Productid] = @productid AND [Locationid] = @locationid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductListPriceHistory]
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
      UPDATE [Production].[ProductListPriceHistory]
        SET
           [Enddate] = @enddate,
           [Listprice] = @listprice,
           [Modifieddate] = @modifieddate
         WHERE
           [Productid] = @productid AND [Startdate] = @startdate
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductModel]
  @productmodelid [int], 
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
      UPDATE [Production].[ProductModel]
        SET
           [Name] = @name,
           [Catalogdescription] = @catalogdescription,
           [Instructions] = @instructions,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Productmodelid] = @productmodelid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductModelIllustration]
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
      UPDATE [Production].[ProductModelIllustration]
        SET
           [Modifieddate] = @modifieddate
         WHERE
           [Productmodelid] = @productmodelid AND [Illustrationid] = @illustrationid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductModelProductDescriptionCulture]
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
      UPDATE [Production].[ProductModelProductDescriptionCulture]
        SET
           [Modifieddate] = @modifieddate
         WHERE
           [Productmodelid] = @productmodelid AND [Productdescriptionid] = @productdescriptionid AND [Cultureid] = @cultureid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductPhoto]
  @productphotoid [int], 
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
      UPDATE [Production].[ProductPhoto]
        SET
           [Thumbnailphoto] = @thumbnailphoto,
           [Thumbnailphotofilename] = @thumbnailphotofilename,
           [Largephoto] = @largephoto,
           [Largephotofilename] = @largephotofilename,
           [Modifieddate] = @modifieddate
         WHERE
           [Productphotoid] = @productphotoid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductProductPhoto]
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
      UPDATE [Production].[ProductProductPhoto]
        SET
           [Primary] = @primary,
           [Modifieddate] = @modifieddate
         WHERE
           [Productid] = @productid AND [Productphotoid] = @productphotoid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductReview]
  @productreviewid [int], 
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
      UPDATE [Production].[ProductReview]
        SET
           [Productid] = @productid,
           [Reviewername] = @reviewername,
           [Reviewdate] = @reviewdate,
           [Emailaddress] = @emailaddress,
           [Rating] = @rating,
           [Comments] = @comments,
           [Modifieddate] = @modifieddate
         WHERE
           [Productreviewid] = @productreviewid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateProductSubcategory]
  @productsubcategoryid [int], 
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
      UPDATE [Production].[ProductSubcategory]
        SET
           [Productcategoryid] = @productcategoryid,
           [Name] = @name,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Productsubcategoryid] = @productsubcategoryid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateScrapReason]
  @scrapreasonid [smallint], 
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
      UPDATE [Production].[ScrapReason]
        SET
           [Name] = @name,
           [Modifieddate] = @modifieddate
         WHERE
           [Scrapreasonid] = @scrapreasonid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateTransactionHistory]
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
      UPDATE [Production].[TransactionHistory]
        SET
           [Productid] = @productid,
           [Referenceorderid] = @referenceorderid,
           [Referenceorderlineid] = @referenceorderlineid,
           [Transactiondate] = @transactiondate,
           [Transactiontype] = @transactiontype,
           [Quantity] = @quantity,
           [Actualcost] = @actualcost,
           [Modifieddate] = @modifieddate
         WHERE
           [Transactionid] = @transactionid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateTransactionHistoryArchive]
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
      UPDATE [Production].[TransactionHistoryArchive]
        SET
           [Productid] = @productid,
           [Referenceorderid] = @referenceorderid,
           [Referenceorderlineid] = @referenceorderlineid,
           [Transactiondate] = @transactiondate,
           [Transactiontype] = @transactiontype,
           [Quantity] = @quantity,
           [Actualcost] = @actualcost,
           [Modifieddate] = @modifieddate
         WHERE
           [Transactionid] = @transactionid
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

CREATE OR ALTER PROCEDURE [Production].[UpdateUnitMeasure]
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
      UPDATE [Production].[UnitMeasure]
        SET
           [Name] = @name,
           [Modifieddate] = @modifieddate
         WHERE
           [Unitmeasurecode] = @unitmeasurecode
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

CREATE OR ALTER PROCEDURE [Production].[UpdateWorkOrder]
  @workorderid [int], 
  @productid [int], 
  @orderqty [int], 
  @stockedqty [int], 
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
      UPDATE [Production].[WorkOrder]
        SET
           [Productid] = @productid,
           [Orderqty] = @orderqty,
           [Scrappedqty] = @scrappedqty,
           [Startdate] = @startdate,
           [Enddate] = @enddate,
           [Duedate] = @duedate,
           [Scrapreasonid] = @scrapreasonid,
           [Modifieddate] = @modifieddate
         WHERE
           [Workorderid] = @workorderid
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

CREATE OR ALTER PROCEDURE [Production].[Update1WorkOrder]
  @workorderid [int], 
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
      UPDATE [Production].[WorkOrder]
        SET
           [Productid] = @productid,
           [Orderqty] = @orderqty,
           [Scrappedqty] = @scrappedqty,
           [Startdate] = @startdate,
           [Enddate] = @enddate,
           [Duedate] = @duedate,
           [Scrapreasonid] = NULL,
           [Modifieddate] = @modifieddate
         WHERE
           [Workorderid] = @workorderid
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

CREATE OR ALTER PROCEDURE [Production].[Update2WorkOrder]
  @workorderid [int], 
  @scrapreasonid [smallint]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Production].[WorkOrder]
        SET
           [Scrapreasonid] = @scrapreasonid
         WHERE
           [Workorderid] = @workorderid
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER PROCEDURE [Production].[UpdateWorkOrderRouting]
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
      UPDATE [Production].[WorkOrderRouting]
        SET
           [Locationid] = @locationid,
           [Scheduledstartdate] = @scheduledstartdate,
           [Scheduledenddate] = @scheduledenddate,
           [Actualstartdate] = @actualstartdate,
           [Actualenddate] = @actualenddate,
           [Actualresourcehrs] = @actualresourcehrs,
           [Plannedcost] = @plannedcost,
           [Actualcost] = @actualcost,
           [Modifieddate] = @modifieddate
         WHERE
           [Workorderid] = @workorderid AND [Productid] = @productid AND [Operationsequence] = @operationsequence
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

CREATE OR ALTER PROCEDURE [Purchasing].[UpdateProductVendor]
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
      UPDATE [Purchasing].[ProductVendor]
        SET
           [Averageleadtime] = @averageleadtime,
           [Standardprice] = @standardprice,
           [Lastreceiptcost] = @lastreceiptcost,
           [Lastreceiptdate] = @lastreceiptdate,
           [Minorderqty] = @minorderqty,
           [Maxorderqty] = @maxorderqty,
           [Onorderqty] = @onorderqty,
           [Unitmeasurecode] = @unitmeasurecode,
           [Modifieddate] = @modifieddate
         WHERE
           [Productid] = @productid AND [Businessentityid] = @businessentityid
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

CREATE OR ALTER PROCEDURE [Purchasing].[UpdatePurchaseOrderDetail]
  @purchaseorderid [int], 
  @purchaseorderdetailid [int], 
  @duedate [datetime], 
  @orderqty [smallint], 
  @productid [int], 
  @unitprice [money], 
  @linetotal [money], 
  @receivedqty [decimal], 
  @rejectedqty [decimal], 
  @stockedqty [decimal], 
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
      UPDATE [Purchasing].[PurchaseOrderDetail]
        SET
           [Duedate] = @duedate,
           [Orderqty] = @orderqty,
           [Productid] = @productid,
           [Unitprice] = @unitprice,
           [Receivedqty] = @receivedqty,
           [Rejectedqty] = @rejectedqty,
           [Modifieddate] = @modifieddate
         WHERE
           [Purchaseorderid] = @purchaseorderid AND [Purchaseorderdetailid] = @purchaseorderdetailid
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

CREATE OR ALTER PROCEDURE [Purchasing].[UpdatePurchaseOrderHeader]
  @purchaseorderid [int], 
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
  @totaldue [money], 
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
      UPDATE [Purchasing].[PurchaseOrderHeader]
        SET
           [Revisionnumber] = @revisionnumber,
           [Status] = @status,
           [Employeeid] = @employeeid,
           [Vendorid] = @vendorid,
           [Shipmethodid] = @shipmethodid,
           [Orderdate] = @orderdate,
           [Shipdate] = @shipdate,
           [Subtotal] = @subtotal,
           [Taxamt] = @taxamt,
           [Freight] = @freight,
           [Modifieddate] = @modifieddate
         WHERE
           [Purchaseorderid] = @purchaseorderid
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

CREATE OR ALTER PROCEDURE [Purchasing].[UpdateShipMethod]
  @shipmethodid [int], 
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
      UPDATE [Purchasing].[ShipMethod]
        SET
           [Name] = @name,
           [Shipbase] = @shipbase,
           [Shiprate] = @shiprate,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Shipmethodid] = @shipmethodid
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

CREATE OR ALTER PROCEDURE [Purchasing].[UpdateVendor]
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
      UPDATE [Purchasing].[Vendor]
        SET
           [Accountnumber] = @accountnumber,
           [Name] = @name,
           [Creditrating] = @creditrating,
           [Preferredvendorstatus] = @preferredvendorstatus,
           [Activeflag] = @activeflag,
           [Purchasingwebserviceurl] = @purchasingwebserviceurl,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateCountryRegionCurrency]
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
      UPDATE [Sales].[CountryRegionCurrency]
        SET
           [Modifieddate] = @modifieddate
         WHERE
           [Countryregioncode] = @countryregioncode AND [Currencycode] = @currencycode
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateCreditCard]
  @creditcardid [int], 
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
      UPDATE [Sales].[CreditCard]
        SET
           [Cardtype] = @cardtype,
           [Cardnumber] = @cardnumber,
           [Expmonth] = @expmonth,
           [Expyear] = @expyear,
           [Modifieddate] = @modifieddate
         WHERE
           [Creditcardid] = @creditcardid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateCurrency]
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
      UPDATE [Sales].[Currency]
        SET
           [Name] = @name,
           [Modifieddate] = @modifieddate
         WHERE
           [Currencycode] = @currencycode
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateCurrencyRate]
  @currencyrateid [int], 
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
      UPDATE [Sales].[CurrencyRate]
        SET
           [Currencyratedate] = @currencyratedate,
           [Fromcurrencycode] = @fromcurrencycode,
           [Tocurrencycode] = @tocurrencycode,
           [Averagerate] = @averagerate,
           [Endofdayrate] = @endofdayrate,
           [Modifieddate] = @modifieddate
         WHERE
           [Currencyrateid] = @currencyrateid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateCustomer]
  @customerid [int], 
  @personid [int], 
  @storeid [int], 
  @territoryid [int], 
  @accountnumber [varchar](10), 
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
      UPDATE [Sales].[Customer]
        SET
           [Personid] = @personid,
           [Storeid] = @storeid,
           [Territoryid] = @territoryid,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Customerid] = @customerid
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

CREATE OR ALTER PROCEDURE [Sales].[Update1Customer]
  @customerid [int], 
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
      UPDATE [Sales].[Customer]
        SET
           [Personid] = NULL,
           [Storeid] = NULL,
           [Territoryid] = NULL,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Customerid] = @customerid
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

CREATE OR ALTER PROCEDURE [Sales].[Update2Customer]
  @customerid [int], 
  @personid [int], 
  @storeid [int], 
  @territoryid [int]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Sales].[Customer]
        SET
           [Personid] = @personid,
           [Storeid] = @storeid,
           [Territoryid] = @territoryid
         WHERE
           [Customerid] = @customerid
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER PROCEDURE [Sales].[UpdatePersonCreditCard]
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
      UPDATE [Sales].[PersonCreditCard]
        SET
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid AND [Creditcardid] = @creditcardid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateSalesOrderDetail]
  @salesorderid [int], 
  @salesorderdetailid [int], 
  @carriertrackingnumber [nvarchar](25), 
  @orderqty [smallint], 
  @productid [int], 
  @specialofferid [int], 
  @unitprice [money], 
  @unitpricediscount [money], 
  @linetotal [numeric], 
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
      UPDATE [Sales].[SalesOrderDetail]
        SET
           [Carriertrackingnumber] = @carriertrackingnumber,
           [Orderqty] = @orderqty,
           [Productid] = @productid,
           [Specialofferid] = @specialofferid,
           [Unitprice] = @unitprice,
           [Unitpricediscount] = @unitpricediscount,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Salesorderid] = @salesorderid AND [Salesorderdetailid] = @salesorderdetailid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateSalesOrderHeader]
  @salesorderid [int], 
  @revisionnumber [tinyint], 
  @orderdate [datetime], 
  @duedate [datetime], 
  @shipdate [datetime], 
  @status [tinyint], 
  @onlineorderflag [Flag], 
  @salesordernumber [nvarchar](25), 
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
  @totaldue [money], 
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
      UPDATE [Sales].[SalesOrderHeader]
        SET
           [Revisionnumber] = @revisionnumber,
           [Orderdate] = @orderdate,
           [Duedate] = @duedate,
           [Shipdate] = @shipdate,
           [Status] = @status,
           [Onlineorderflag] = @onlineorderflag,
           [Purchaseordernumber] = @purchaseordernumber,
           [Accountnumber] = @accountnumber,
           [Customerid] = @customerid,
           [Salespersonid] = @salespersonid,
           [Territoryid] = @territoryid,
           [Billtoaddressid] = @billtoaddressid,
           [Shiptoaddressid] = @shiptoaddressid,
           [Shipmethodid] = @shipmethodid,
           [Creditcardid] = @creditcardid,
           [Creditcardapprovalcode] = @creditcardapprovalcode,
           [Currencyrateid] = @currencyrateid,
           [Subtotal] = @subtotal,
           [Taxamt] = @taxamt,
           [Freight] = @freight,
           [Comment] = @comment,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Salesorderid] = @salesorderid
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

CREATE OR ALTER PROCEDURE [Sales].[Update1SalesOrderHeader]
  @salesorderid [int], 
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
      UPDATE [Sales].[SalesOrderHeader]
        SET
           [Revisionnumber] = @revisionnumber,
           [Orderdate] = @orderdate,
           [Duedate] = @duedate,
           [Shipdate] = @shipdate,
           [Status] = @status,
           [Onlineorderflag] = @onlineorderflag,
           [Purchaseordernumber] = @purchaseordernumber,
           [Accountnumber] = @accountnumber,
           [Customerid] = @customerid,
           [Salespersonid] = NULL,
           [Territoryid] = NULL,
           [Billtoaddressid] = @billtoaddressid,
           [Shiptoaddressid] = @shiptoaddressid,
           [Shipmethodid] = @shipmethodid,
           [Creditcardid] = NULL,
           [Creditcardapprovalcode] = @creditcardapprovalcode,
           [Currencyrateid] = NULL,
           [Subtotal] = @subtotal,
           [Taxamt] = @taxamt,
           [Freight] = @freight,
           [Comment] = @comment,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Salesorderid] = @salesorderid
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

CREATE OR ALTER PROCEDURE [Sales].[Update2SalesOrderHeader]
  @salesorderid [int], 
  @salespersonid [int], 
  @territoryid [int], 
  @creditcardid [int], 
  @currencyrateid [int]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Sales].[SalesOrderHeader]
        SET
           [Salespersonid] = @salespersonid,
           [Territoryid] = @territoryid,
           [Creditcardid] = @creditcardid,
           [Currencyrateid] = @currencyrateid
         WHERE
           [Salesorderid] = @salesorderid
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER PROCEDURE [Sales].[UpdateSalesOrderHeaderSalesReason]
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
      UPDATE [Sales].[SalesOrderHeaderSalesReason]
        SET
           [Modifieddate] = @modifieddate
         WHERE
           [Salesorderid] = @salesorderid AND [Salesreasonid] = @salesreasonid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateSalesPerson]
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
      UPDATE [Sales].[SalesPerson]
        SET
           [Territoryid] = @territoryid,
           [Salesquota] = @salesquota,
           [Bonus] = @bonus,
           [Commissionpct] = @commissionpct,
           [Salesytd] = @salesytd,
           [Saleslastyear] = @saleslastyear,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid
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

CREATE OR ALTER PROCEDURE [Sales].[Update1SalesPerson]
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
      UPDATE [Sales].[SalesPerson]
        SET
           [Territoryid] = NULL,
           [Salesquota] = @salesquota,
           [Bonus] = @bonus,
           [Commissionpct] = @commissionpct,
           [Salesytd] = @salesytd,
           [Saleslastyear] = @saleslastyear,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid
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

CREATE OR ALTER PROCEDURE [Sales].[Update2SalesPerson]
  @businessentityid [int], 
  @territoryid [int]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Sales].[SalesPerson]
        SET
           [Territoryid] = @territoryid
         WHERE
           [Businessentityid] = @businessentityid
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

CREATE OR ALTER PROCEDURE [Sales].[UpdateSalesPersonQuotaHistory]
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
      UPDATE [Sales].[SalesPersonQuotaHistory]
        SET
           [Salesquota] = @salesquota,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid AND [Quotadate] = @quotadate
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateSalesReason]
  @salesreasonid [int], 
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
      UPDATE [Sales].[SalesReason]
        SET
           [Name] = @name,
           [Reasontype] = @reasontype,
           [Modifieddate] = @modifieddate
         WHERE
           [Salesreasonid] = @salesreasonid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateSalesTaxRate]
  @salestaxrateid [int], 
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
      UPDATE [Sales].[SalesTaxRate]
        SET
           [Stateprovinceid] = @stateprovinceid,
           [Taxtype] = @taxtype,
           [Taxrate] = @taxrate,
           [Name] = @name,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Salestaxrateid] = @salestaxrateid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateSalesTerritory]
  @territoryid [int], 
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
      UPDATE [Sales].[SalesTerritory]
        SET
           [Name] = @name,
           [Countryregioncode] = @countryregioncode,
           [Group] = @group,
           [Salesytd] = @salesytd,
           [Saleslastyear] = @saleslastyear,
           [Costytd] = @costytd,
           [Costlastyear] = @costlastyear,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Territoryid] = @territoryid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateSalesTerritoryHistory]
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
      UPDATE [Sales].[SalesTerritoryHistory]
        SET
           [Enddate] = @enddate,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid AND [Startdate] = @startdate AND [Territoryid] = @territoryid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateShoppingCartItem]
  @shoppingcartitemid [int], 
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
      UPDATE [Sales].[ShoppingCartItem]
        SET
           [Shoppingcartid] = @shoppingcartid,
           [Quantity] = @quantity,
           [Productid] = @productid,
           [Datecreated] = @datecreated,
           [Modifieddate] = @modifieddate
         WHERE
           [Shoppingcartitemid] = @shoppingcartitemid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateSpecialOffer]
  @specialofferid [int], 
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
      UPDATE [Sales].[SpecialOffer]
        SET
           [Description] = @description,
           [Discountpct] = @discountpct,
           [Type] = @type,
           [Category] = @category,
           [Startdate] = @startdate,
           [Enddate] = @enddate,
           [Minqty] = @minqty,
           [Maxqty] = @maxqty,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Specialofferid] = @specialofferid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateSpecialOfferProduct]
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
      UPDATE [Sales].[SpecialOfferProduct]
        SET
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Specialofferid] = @specialofferid AND [Productid] = @productid
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

CREATE OR ALTER PROCEDURE [Sales].[UpdateStore]
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
      UPDATE [Sales].[Store]
        SET
           [Name] = @name,
           [Salespersonid] = @salespersonid,
           [Demographics] = @demographics,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid
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

CREATE OR ALTER PROCEDURE [Sales].[Update1Store]
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
      UPDATE [Sales].[Store]
        SET
           [Name] = @name,
           [Salespersonid] = NULL,
           [Demographics] = @demographics,
           [Rowguid] = @rowguid,
           [Modifieddate] = @modifieddate
         WHERE
           [Businessentityid] = @businessentityid
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

CREATE OR ALTER PROCEDURE [Sales].[Update2Store]
  @businessentityid [int], 
  @salespersonid [int]
AS
  BEGIN
    DECLARE @TranCounter INT;
    SET @TranCounter = @@TRANCOUNT;
    IF @TranCounter > 0
      SAVE TRANSACTION SavePoint0;
    ELSE
      BEGIN TRANSACTION;
    BEGIN TRY
      UPDATE [Sales].[Store]
        SET
           [Salespersonid] = @salespersonid
         WHERE
           [Businessentityid] = @businessentityid
      IF @TranCounter = 0
          COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        DECLARE @ErrorSeverity INT;
        DECLARE @ErrorState INT;
        SELECT @ErrorMessage = ERROR_MESSAGE(),
            @ErrorSeverity = ERROR_SEVERITY(),
            @ErrorState = ERROR_STATE();
        IF @TranCounter = 0
          ROLLBACK TRANSACTION;
        ELSE
          IF XACT_STATE() <> -1
            ROLLBACK TRANSACTION SavePoint0;
        RAISERROR(
            @ErrorMessage,
            @ErrorSeverity,
            @ErrorState);
    END CATCH
  END

GO

