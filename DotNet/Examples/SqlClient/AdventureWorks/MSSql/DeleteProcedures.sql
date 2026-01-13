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
CREATE OR ALTER PROCEDURE [dbo].[DeleteAWBuildVersion]
  @systeminformationid [tinyint]
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
      DELETE FROM [dbo].[AWBuildVersion]
        WHERE
          [Systeminformationid] = @systeminformationid

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

CREATE OR ALTER PROCEDURE [dbo].[DeleteDatabaseLog]
  @databaselogid [int]
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
      DELETE FROM [dbo].[DatabaseLog]
        WHERE
          [Databaselogid] = @databaselogid

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

CREATE OR ALTER PROCEDURE [dbo].[DeleteErrorLog]
  @errorlogid [int]
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
      DELETE FROM [dbo].[ErrorLog]
        WHERE
          [Errorlogid] = @errorlogid

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

CREATE OR ALTER PROCEDURE [HumanResources].[DeleteDepartment]
  @departmentid [smallint]
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
      DELETE FROM [HumanResources].[Department]
        WHERE
          [Departmentid] = @departmentid

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

CREATE OR ALTER PROCEDURE [HumanResources].[DeleteEmployee]
  @businessentityid [int]
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
      DELETE FROM [HumanResources].[Employee]
        WHERE
          [Businessentityid] = @businessentityid

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

CREATE OR ALTER PROCEDURE [HumanResources].[DeleteEmployeeDepartmentHistory]
  @businessentityid [int], 
  @startdate [date], 
  @departmentid [smallint], 
  @shiftid [tinyint]
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
      DELETE FROM [HumanResources].[EmployeeDepartmentHistory]
        WHERE
          [Businessentityid] = @businessentityid AND [Startdate] = @startdate AND [Departmentid] = @departmentid AND [Shiftid] = @shiftid

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

CREATE OR ALTER PROCEDURE [HumanResources].[DeleteEmployeePayHistory]
  @businessentityid [int], 
  @ratechangedate [datetime]
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
      DELETE FROM [HumanResources].[EmployeePayHistory]
        WHERE
          [Businessentityid] = @businessentityid AND [Ratechangedate] = @ratechangedate

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

CREATE OR ALTER PROCEDURE [HumanResources].[DeleteJobCandidate]
  @jobcandidateid [int]
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
      DELETE FROM [HumanResources].[JobCandidate]
        WHERE
          [Jobcandidateid] = @jobcandidateid

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

CREATE OR ALTER PROCEDURE [HumanResources].[DeleteShift]
  @shiftid [tinyint]
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
      DELETE FROM [HumanResources].[Shift]
        WHERE
          [Shiftid] = @shiftid

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

CREATE OR ALTER PROCEDURE [Person].[DeleteAddress]
  @addressid [int]
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
      DELETE FROM [Person].[Address]
        WHERE
          [Addressid] = @addressid

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

CREATE OR ALTER PROCEDURE [Person].[DeleteAddressType]
  @addresstypeid [int]
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
      DELETE FROM [Person].[AddressType]
        WHERE
          [Addresstypeid] = @addresstypeid

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

CREATE OR ALTER PROCEDURE [Person].[DeleteBusinessEntity]
  @businessentityid [int]
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
      DELETE FROM [Person].[BusinessEntity]
        WHERE
          [Businessentityid] = @businessentityid

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

CREATE OR ALTER PROCEDURE [Person].[DeleteBusinessEntityAddress]
  @businessentityid [int], 
  @addressid [int], 
  @addresstypeid [int]
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
      DELETE FROM [Person].[BusinessEntityAddress]
        WHERE
          [Businessentityid] = @businessentityid AND [Addressid] = @addressid AND [Addresstypeid] = @addresstypeid

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

CREATE OR ALTER PROCEDURE [Person].[DeleteBusinessEntityContact]
  @businessentityid [int], 
  @personid [int], 
  @contacttypeid [int]
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
      DELETE FROM [Person].[BusinessEntityContact]
        WHERE
          [Businessentityid] = @businessentityid AND [Personid] = @personid AND [Contacttypeid] = @contacttypeid

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

CREATE OR ALTER PROCEDURE [Person].[DeleteContactType]
  @contacttypeid [int]
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
      DELETE FROM [Person].[ContactType]
        WHERE
          [Contacttypeid] = @contacttypeid

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

CREATE OR ALTER PROCEDURE [Person].[DeleteCountryRegion]
  @countryregioncode [nvarchar](3)
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
      DELETE FROM [Person].[CountryRegion]
        WHERE
          [Countryregioncode] = @countryregioncode

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

CREATE OR ALTER PROCEDURE [Person].[DeleteEmailAddress]
  @businessentityid [int], 
  @emailaddressid [int]
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
      DELETE FROM [Person].[EmailAddress]
        WHERE
          [Businessentityid] = @businessentityid AND [Emailaddressid] = @emailaddressid

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

CREATE OR ALTER PROCEDURE [Person].[DeletePassword]
  @businessentityid [int]
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
      DELETE FROM [Person].[Password]
        WHERE
          [Businessentityid] = @businessentityid

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

CREATE OR ALTER PROCEDURE [Person].[DeletePerson]
  @businessentityid [int]
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
      DELETE FROM [Person].[Person]
        WHERE
          [Businessentityid] = @businessentityid

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

CREATE OR ALTER PROCEDURE [Person].[DeletePersonPhone]
  @businessentityid [int], 
  @phonenumber [phone], 
  @phonenumbertypeid [int]
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
      DELETE FROM [Person].[PersonPhone]
        WHERE
          [Businessentityid] = @businessentityid AND [Phonenumber] = @phonenumber AND [Phonenumbertypeid] = @phonenumbertypeid

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

CREATE OR ALTER PROCEDURE [Person].[DeletePhoneNumberType]
  @phonenumbertypeid [int]
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
      DELETE FROM [Person].[PhoneNumberType]
        WHERE
          [Phonenumbertypeid] = @phonenumbertypeid

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

CREATE OR ALTER PROCEDURE [Person].[DeleteStateProvince]
  @stateprovinceid [int]
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
      DELETE FROM [Person].[StateProvince]
        WHERE
          [Stateprovinceid] = @stateprovinceid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteBillOfMaterials]
  @billofmaterialsid [int]
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
      DELETE FROM [Production].[BillOfMaterials]
        WHERE
          [Billofmaterialsid] = @billofmaterialsid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteCulture]
  @cultureid [nchar](6)
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
      DELETE FROM [Production].[Culture]
        WHERE
          [Cultureid] = @cultureid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteDocument]
  @documentnode [hierarchyid]
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
      DELETE FROM [Production].[Document]
        WHERE
          [Documentnode] = @documentnode

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

CREATE OR ALTER PROCEDURE [Production].[DeleteIllustration]
  @illustrationid [int]
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
      DELETE FROM [Production].[Illustration]
        WHERE
          [Illustrationid] = @illustrationid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteLocation]
  @locationid [smallint]
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
      DELETE FROM [Production].[Location]
        WHERE
          [Locationid] = @locationid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProduct]
  @productid [int]
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
      DELETE FROM [Production].[Product]
        WHERE
          [Productid] = @productid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductCategory]
  @productcategoryid [int]
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
      DELETE FROM [Production].[ProductCategory]
        WHERE
          [Productcategoryid] = @productcategoryid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductCostHistory]
  @productid [int], 
  @startdate [datetime]
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
      DELETE FROM [Production].[ProductCostHistory]
        WHERE
          [Productid] = @productid AND [Startdate] = @startdate

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductDescription]
  @productdescriptionid [int]
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
      DELETE FROM [Production].[ProductDescription]
        WHERE
          [Productdescriptionid] = @productdescriptionid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductDocument]
  @productid [int], 
  @documentnode [hierarchyid]
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
      DELETE FROM [Production].[ProductDocument]
        WHERE
          [Productid] = @productid AND [Documentnode] = @documentnode

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductInventory]
  @productid [int], 
  @locationid [smallint]
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
      DELETE FROM [Production].[ProductInventory]
        WHERE
          [Productid] = @productid AND [Locationid] = @locationid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductListPriceHistory]
  @productid [int], 
  @startdate [datetime]
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
      DELETE FROM [Production].[ProductListPriceHistory]
        WHERE
          [Productid] = @productid AND [Startdate] = @startdate

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductModel]
  @productmodelid [int]
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
      DELETE FROM [Production].[ProductModel]
        WHERE
          [Productmodelid] = @productmodelid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductModelIllustration]
  @productmodelid [int], 
  @illustrationid [int]
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
      DELETE FROM [Production].[ProductModelIllustration]
        WHERE
          [Productmodelid] = @productmodelid AND [Illustrationid] = @illustrationid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductModelProductDescriptionCulture]
  @productmodelid [int], 
  @productdescriptionid [int], 
  @cultureid [nchar](6)
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
      DELETE FROM [Production].[ProductModelProductDescriptionCulture]
        WHERE
          [Productmodelid] = @productmodelid AND [Productdescriptionid] = @productdescriptionid AND [Cultureid] = @cultureid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductPhoto]
  @productphotoid [int]
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
      DELETE FROM [Production].[ProductPhoto]
        WHERE
          [Productphotoid] = @productphotoid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductProductPhoto]
  @productid [int], 
  @productphotoid [int]
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
      DELETE FROM [Production].[ProductProductPhoto]
        WHERE
          [Productid] = @productid AND [Productphotoid] = @productphotoid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductReview]
  @productreviewid [int]
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
      DELETE FROM [Production].[ProductReview]
        WHERE
          [Productreviewid] = @productreviewid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteProductSubcategory]
  @productsubcategoryid [int]
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
      DELETE FROM [Production].[ProductSubcategory]
        WHERE
          [Productsubcategoryid] = @productsubcategoryid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteScrapReason]
  @scrapreasonid [smallint]
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
      DELETE FROM [Production].[ScrapReason]
        WHERE
          [Scrapreasonid] = @scrapreasonid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteTransactionHistory]
  @transactionid [int]
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
      DELETE FROM [Production].[TransactionHistory]
        WHERE
          [Transactionid] = @transactionid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteTransactionHistoryArchive]
  @transactionid [int]
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
      DELETE FROM [Production].[TransactionHistoryArchive]
        WHERE
          [Transactionid] = @transactionid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteUnitMeasure]
  @unitmeasurecode [nchar](3)
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
      DELETE FROM [Production].[UnitMeasure]
        WHERE
          [Unitmeasurecode] = @unitmeasurecode

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

CREATE OR ALTER PROCEDURE [Production].[DeleteWorkOrder]
  @workorderid [int]
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
      DELETE FROM [Production].[WorkOrder]
        WHERE
          [Workorderid] = @workorderid

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

CREATE OR ALTER PROCEDURE [Production].[DeleteWorkOrderRouting]
  @workorderid [int], 
  @productid [int], 
  @operationsequence [smallint]
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
      DELETE FROM [Production].[WorkOrderRouting]
        WHERE
          [Workorderid] = @workorderid AND [Productid] = @productid AND [Operationsequence] = @operationsequence

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

CREATE OR ALTER PROCEDURE [Purchasing].[DeleteProductVendor]
  @productid [int], 
  @businessentityid [int]
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
      DELETE FROM [Purchasing].[ProductVendor]
        WHERE
          [Productid] = @productid AND [Businessentityid] = @businessentityid

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

CREATE OR ALTER PROCEDURE [Purchasing].[DeletePurchaseOrderDetail]
  @purchaseorderid [int], 
  @purchaseorderdetailid [int]
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
      DELETE FROM [Purchasing].[PurchaseOrderDetail]
        WHERE
          [Purchaseorderid] = @purchaseorderid AND [Purchaseorderdetailid] = @purchaseorderdetailid

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

CREATE OR ALTER PROCEDURE [Purchasing].[DeletePurchaseOrderHeader]
  @purchaseorderid [int]
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
      DELETE FROM [Purchasing].[PurchaseOrderHeader]
        WHERE
          [Purchaseorderid] = @purchaseorderid

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

CREATE OR ALTER PROCEDURE [Purchasing].[DeleteShipMethod]
  @shipmethodid [int]
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
      DELETE FROM [Purchasing].[ShipMethod]
        WHERE
          [Shipmethodid] = @shipmethodid

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

CREATE OR ALTER PROCEDURE [Purchasing].[DeleteVendor]
  @businessentityid [int]
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
      DELETE FROM [Purchasing].[Vendor]
        WHERE
          [Businessentityid] = @businessentityid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteCountryRegionCurrency]
  @countryregioncode [nvarchar](3), 
  @currencycode [nchar](3)
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
      DELETE FROM [Sales].[CountryRegionCurrency]
        WHERE
          [Countryregioncode] = @countryregioncode AND [Currencycode] = @currencycode

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteCreditCard]
  @creditcardid [int]
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
      DELETE FROM [Sales].[CreditCard]
        WHERE
          [Creditcardid] = @creditcardid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteCurrency]
  @currencycode [nchar](3)
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
      DELETE FROM [Sales].[Currency]
        WHERE
          [Currencycode] = @currencycode

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteCurrencyRate]
  @currencyrateid [int]
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
      DELETE FROM [Sales].[CurrencyRate]
        WHERE
          [Currencyrateid] = @currencyrateid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteCustomer]
  @customerid [int]
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
      DELETE FROM [Sales].[Customer]
        WHERE
          [Customerid] = @customerid

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

CREATE OR ALTER PROCEDURE [Sales].[DeletePersonCreditCard]
  @businessentityid [int], 
  @creditcardid [int]
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
      DELETE FROM [Sales].[PersonCreditCard]
        WHERE
          [Businessentityid] = @businessentityid AND [Creditcardid] = @creditcardid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSalesOrderDetail]
  @salesorderid [int], 
  @salesorderdetailid [int]
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
      DELETE FROM [Sales].[SalesOrderDetail]
        WHERE
          [Salesorderid] = @salesorderid AND [Salesorderdetailid] = @salesorderdetailid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSalesOrderHeader]
  @salesorderid [int]
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
      DELETE FROM [Sales].[SalesOrderHeader]
        WHERE
          [Salesorderid] = @salesorderid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSalesOrderHeaderSalesReason]
  @salesorderid [int], 
  @salesreasonid [int]
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
      DELETE FROM [Sales].[SalesOrderHeaderSalesReason]
        WHERE
          [Salesorderid] = @salesorderid AND [Salesreasonid] = @salesreasonid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSalesPerson]
  @businessentityid [int]
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
      DELETE FROM [Sales].[SalesPerson]
        WHERE
          [Businessentityid] = @businessentityid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSalesPersonQuotaHistory]
  @businessentityid [int], 
  @quotadate [datetime]
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
      DELETE FROM [Sales].[SalesPersonQuotaHistory]
        WHERE
          [Businessentityid] = @businessentityid AND [Quotadate] = @quotadate

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSalesReason]
  @salesreasonid [int]
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
      DELETE FROM [Sales].[SalesReason]
        WHERE
          [Salesreasonid] = @salesreasonid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSalesTaxRate]
  @salestaxrateid [int]
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
      DELETE FROM [Sales].[SalesTaxRate]
        WHERE
          [Salestaxrateid] = @salestaxrateid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSalesTerritory]
  @territoryid [int]
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
      DELETE FROM [Sales].[SalesTerritory]
        WHERE
          [Territoryid] = @territoryid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSalesTerritoryHistory]
  @businessentityid [int], 
  @startdate [datetime], 
  @territoryid [int]
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
      DELETE FROM [Sales].[SalesTerritoryHistory]
        WHERE
          [Businessentityid] = @businessentityid AND [Startdate] = @startdate AND [Territoryid] = @territoryid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteShoppingCartItem]
  @shoppingcartitemid [int]
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
      DELETE FROM [Sales].[ShoppingCartItem]
        WHERE
          [Shoppingcartitemid] = @shoppingcartitemid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSpecialOffer]
  @specialofferid [int]
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
      DELETE FROM [Sales].[SpecialOffer]
        WHERE
          [Specialofferid] = @specialofferid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteSpecialOfferProduct]
  @specialofferid [int], 
  @productid [int]
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
      DELETE FROM [Sales].[SpecialOfferProduct]
        WHERE
          [Specialofferid] = @specialofferid AND [Productid] = @productid

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

CREATE OR ALTER PROCEDURE [Sales].[DeleteStore]
  @businessentityid [int]
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
      DELETE FROM [Sales].[Store]
        WHERE
          [Businessentityid] = @businessentityid

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

