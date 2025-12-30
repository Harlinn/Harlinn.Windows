/*
 * Schema: [HumanResources]
 */
IF NOT EXISTS (SELECT * FROM sys.schemas WHERE name = 'HumanResources')
BEGIN
    EXEC('CREATE SCHEMA [HumanResources]');
END
go

/*
 * Schema: [Person]
 */
IF NOT EXISTS (SELECT * FROM sys.schemas WHERE name = 'Person')
BEGIN
    EXEC('CREATE SCHEMA [Person]');
END
go

/*
 * Schema: [Production]
 */
IF NOT EXISTS (SELECT * FROM sys.schemas WHERE name = 'Production')
BEGIN
    EXEC('CREATE SCHEMA [Production]');
END
go

/*
 * Schema: [Purchasing]
 */
IF NOT EXISTS (SELECT * FROM sys.schemas WHERE name = 'Purchasing')
BEGIN
    EXEC('CREATE SCHEMA [Purchasing]');
END
go

/*
 * Schema: [Sales]
 */
IF NOT EXISTS (SELECT * FROM sys.schemas WHERE name = 'Sales')
BEGIN
    EXEC('CREATE SCHEMA [Sales]');
END
go

/*
 * [dbo].[AWBuildVersion]
 */
CREATE TABLE [dbo].[AWBuildVersion]
(
    [Systeminformationid] [tinyint] IDENTITY NOT NULL,
    [Database Version] [nvarchar](25) NOT NULL,
    [Versiondate] [datetime] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_AWBuildVersion_SystemInformationID] PRIMARY KEY([Systeminformationid])
)
go


/*
 * [dbo].[DatabaseLog]
 */
CREATE TABLE [dbo].[DatabaseLog]
(
    [Databaselogid] [int] IDENTITY NOT NULL,
    [Posttime] [datetime] NOT NULL,
    [Databaseuser] [sysname] NOT NULL,
    [Event] [sysname] NOT NULL,
    [Schema] [sysname] NULL,
    [Object] [sysname] NULL,
    [Tsql] [nvarchar](max) NOT NULL,
    [Xmlevent] [xml] NOT NULL,
    CONSTRAINT [PK_DatabaseLog_DatabaseLogID] PRIMARY KEY([Databaselogid])
)
go


/*
 * [dbo].[ErrorLog]
 */
CREATE TABLE [dbo].[ErrorLog]
(
    [Errorlogid] [int] IDENTITY NOT NULL,
    [Errortime] [datetime] NOT NULL DEFAULT (getdate()),
    [Username] [sysname] NOT NULL,
    [Errornumber] [int] NOT NULL,
    [Errorseverity] [int] NULL,
    [Errorstate] [int] NULL,
    [Errorprocedure] [nvarchar](126) NULL,
    [Errorline] [int] NULL,
    [Errormessage] [nvarchar](4000) NOT NULL,
    CONSTRAINT [PK_ErrorLog_ErrorLogID] PRIMARY KEY([Errorlogid])
)
go


/*
 * [HumanResources].[Department]
 */
CREATE TABLE [HumanResources].[Department]
(
    [Departmentid] [smallint] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Groupname] [name] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Department_DepartmentID] PRIMARY KEY([Departmentid])
)
go

ALTER TABLE [HumanResources].[Department]
  ADD CONSTRAINT AK_Department_Name UNIQUE([Name])
go


/*
 * [HumanResources].[Employee]
 */
CREATE TABLE [HumanResources].[Employee]
(
    [Businessentityid] [int] NOT NULL,
    [Nationalidnumber] [nvarchar](15) NOT NULL,
    [Loginid] [nvarchar](256) NOT NULL,
    [Organizationnode] [hierarchyid] NULL,
    [Organizationlevel] AS ([OrganizationNode].[GetLevel]()),
    [Jobtitle] [nvarchar](50) NOT NULL,
    [Birthdate] [date] NOT NULL,
    [Maritalstatus] [nchar](1) NOT NULL,
    [Gender] [nchar](1) NOT NULL,
    [Hiredate] [date] NOT NULL,
    [Salariedflag] [Flag] NOT NULL DEFAULT ((1)),
    [Vacationhours] [smallint] NOT NULL DEFAULT ((0)),
    [Sickleavehours] [smallint] NOT NULL DEFAULT ((0)),
    [Currentflag] [Flag] NOT NULL DEFAULT ((1)),
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Employee_BusinessEntityID] PRIMARY KEY([Businessentityid])
)
go

CREATE INDEX IX_Employee_OrganizationNode ON [HumanResources].[Employee]([Organizationnode])
go

CREATE INDEX IX_Employee_OrganizationLevel_OrganizationNode ON [HumanResources].[Employee]([Organizationlevel], [Organizationnode])
go

ALTER TABLE [HumanResources].[Employee]
  ADD CONSTRAINT AK_Employee_LoginID UNIQUE([Loginid])
go

ALTER TABLE [HumanResources].[Employee]
  ADD CONSTRAINT AK_Employee_NationalIDNumber UNIQUE([Nationalidnumber])
go

ALTER TABLE [HumanResources].[Employee]
  ADD CONSTRAINT AK_Employee_rowguid UNIQUE([Rowguid])
go


/*
 * [HumanResources].[EmployeeDepartmentHistory]
 */
CREATE TABLE [HumanResources].[EmployeeDepartmentHistory]
(
    [Businessentityid] [int] NOT NULL,
    [Departmentid] [smallint] NOT NULL,
    [Shiftid] [tinyint] NOT NULL,
    [Startdate] [date] NOT NULL,
    [Enddate] [date] NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_EmployeeDepartmentHistory_BusinessEntityID_StartDate_DepartmentID] PRIMARY KEY([Businessentityid], [Startdate], [Departmentid], [Shiftid])
)
go

CREATE INDEX IX_EmployeeDepartmentHistory_DepartmentID ON [HumanResources].[EmployeeDepartmentHistory]([Departmentid])
go

CREATE INDEX IX_EmployeeDepartmentHistory_ShiftID ON [HumanResources].[EmployeeDepartmentHistory]([Shiftid])
go


/*
 * [HumanResources].[EmployeePayHistory]
 */
CREATE TABLE [HumanResources].[EmployeePayHistory]
(
    [Businessentityid] [int] NOT NULL,
    [Ratechangedate] [datetime] NOT NULL,
    [Rate] [money] NOT NULL,
    [Payfrequency] [tinyint] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_EmployeePayHistory_BusinessEntityID_RateChangeDate] PRIMARY KEY([Businessentityid], [Ratechangedate])
)
go


/*
 * [HumanResources].[JobCandidate]
 */
CREATE TABLE [HumanResources].[JobCandidate]
(
    [Jobcandidateid] [int] IDENTITY NOT NULL,
    [Businessentityid] [int] NULL,
    [Resume] [xml] NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_JobCandidate_JobCandidateID] PRIMARY KEY([Jobcandidateid])
)
go

CREATE INDEX IX_JobCandidate_BusinessEntityID ON [HumanResources].[JobCandidate]([Businessentityid])
go


/*
 * [HumanResources].[Shift]
 */
CREATE TABLE [HumanResources].[Shift]
(
    [Shiftid] [tinyint] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Starttime] [time] NOT NULL,
    [Endtime] [time] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Shift_ShiftID] PRIMARY KEY([Shiftid])
)
go

ALTER TABLE [HumanResources].[Shift]
  ADD CONSTRAINT AK_Shift_Name UNIQUE([Name])
go

ALTER TABLE [HumanResources].[Shift]
  ADD CONSTRAINT AK_Shift_StartTime_EndTime UNIQUE([Starttime], [Endtime])
go


/*
 * [Person].[Address]
 */
CREATE TABLE [Person].[Address]
(
    [Addressid] [int] IDENTITY NOT NULL,
    [Addressline1] [nvarchar](60) NOT NULL,
    [Addressline2] [nvarchar](60) NULL,
    [City] [nvarchar](30) NOT NULL,
    [Stateprovinceid] [int] NOT NULL,
    [Postalcode] [nvarchar](15) NOT NULL,
    [Spatiallocation] [geography] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Address_AddressID] PRIMARY KEY([Addressid])
)
go

ALTER TABLE [Person].[Address]
  ADD CONSTRAINT AK_Address_rowguid UNIQUE([Rowguid])
go

ALTER TABLE [Person].[Address]
  ADD CONSTRAINT IX_Address_AddressLine1_AddressLine2_City_StateProvinceID_PostalCode UNIQUE([Addressline1], [Addressline2], [City], [Stateprovinceid], [Postalcode])
go

CREATE INDEX IX_Address_StateProvinceID ON [Person].[Address]([Stateprovinceid])
go


/*
 * [Person].[AddressType]
 */
CREATE TABLE [Person].[AddressType]
(
    [Addresstypeid] [int] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_AddressType_AddressTypeID] PRIMARY KEY([Addresstypeid])
)
go

ALTER TABLE [Person].[AddressType]
  ADD CONSTRAINT AK_AddressType_rowguid UNIQUE([Rowguid])
go

ALTER TABLE [Person].[AddressType]
  ADD CONSTRAINT AK_AddressType_Name UNIQUE([Name])
go


/*
 * [Person].[BusinessEntity]
 */
CREATE TABLE [Person].[BusinessEntity]
(
    [Businessentityid] [int] IDENTITY NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_BusinessEntity_BusinessEntityID] PRIMARY KEY([Businessentityid])
)
go

ALTER TABLE [Person].[BusinessEntity]
  ADD CONSTRAINT AK_BusinessEntity_rowguid UNIQUE([Rowguid])
go


/*
 * [Person].[BusinessEntityAddress]
 */
CREATE TABLE [Person].[BusinessEntityAddress]
(
    [Businessentityid] [int] NOT NULL,
    [Addressid] [int] NOT NULL,
    [Addresstypeid] [int] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_BusinessEntityAddress_BusinessEntityID_AddressID_AddressTypeID] PRIMARY KEY([Businessentityid], [Addressid], [Addresstypeid])
)
go

ALTER TABLE [Person].[BusinessEntityAddress]
  ADD CONSTRAINT AK_BusinessEntityAddress_rowguid UNIQUE([Rowguid])
go

CREATE INDEX IX_BusinessEntityAddress_AddressID ON [Person].[BusinessEntityAddress]([Addressid])
go

CREATE INDEX IX_BusinessEntityAddress_AddressTypeID ON [Person].[BusinessEntityAddress]([Addresstypeid])
go


/*
 * [Person].[BusinessEntityContact]
 */
CREATE TABLE [Person].[BusinessEntityContact]
(
    [Businessentityid] [int] NOT NULL,
    [Personid] [int] NOT NULL,
    [Contacttypeid] [int] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_BusinessEntityContact_BusinessEntityID_PersonID_ContactTypeID] PRIMARY KEY([Businessentityid], [Personid], [Contacttypeid])
)
go

ALTER TABLE [Person].[BusinessEntityContact]
  ADD CONSTRAINT AK_BusinessEntityContact_rowguid UNIQUE([Rowguid])
go

CREATE INDEX IX_BusinessEntityContact_PersonID ON [Person].[BusinessEntityContact]([Personid])
go

CREATE INDEX IX_BusinessEntityContact_ContactTypeID ON [Person].[BusinessEntityContact]([Contacttypeid])
go


/*
 * [Person].[ContactType]
 */
CREATE TABLE [Person].[ContactType]
(
    [Contacttypeid] [int] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ContactType_ContactTypeID] PRIMARY KEY([Contacttypeid])
)
go

ALTER TABLE [Person].[ContactType]
  ADD CONSTRAINT AK_ContactType_Name UNIQUE([Name])
go


/*
 * [Person].[CountryRegion]
 */
CREATE TABLE [Person].[CountryRegion]
(
    [Countryregioncode] [nvarchar](3) NOT NULL,
    [Name] [name] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_CountryRegion_CountryRegionCode] PRIMARY KEY([Countryregioncode])
)
go

ALTER TABLE [Person].[CountryRegion]
  ADD CONSTRAINT AK_CountryRegion_Name UNIQUE([Name])
go


/*
 * [Person].[EmailAddress]
 */
CREATE TABLE [Person].[EmailAddress]
(
    [Businessentityid] [int] NOT NULL,
    [Emailaddressid] [int] IDENTITY NOT NULL,
    [Emailaddress] [nvarchar](50) NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_EmailAddress_BusinessEntityID_EmailAddressID] PRIMARY KEY([Businessentityid], [Emailaddressid])
)
go

CREATE INDEX IX_EmailAddress_EmailAddress ON [Person].[EmailAddress]([Emailaddress])
go


/*
 * [Person].[Password]
 */
CREATE TABLE [Person].[Password]
(
    [Businessentityid] [int] NOT NULL,
    [Passwordhash] [varchar](128) NOT NULL,
    [Passwordsalt] [varchar](10) NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Password_BusinessEntityID] PRIMARY KEY([Businessentityid])
)
go


/*
 * [Person].[Person]
 */
CREATE TABLE [Person].[Person]
(
    [Businessentityid] [int] NOT NULL,
    [Persontype] [nchar](2) NOT NULL,
    [Namestyle] [NameStyle] NOT NULL DEFAULT ((0)),
    [Title] [nvarchar](8) NULL,
    [Firstname] [name] NOT NULL,
    [Middlename] [name] NULL,
    [Lastname] [name] NOT NULL,
    [Suffix] [nvarchar](10) NULL,
    [Emailpromotion] [int] NOT NULL DEFAULT ((0)),
    [Additionalcontactinfo] [xml] NULL,
    [Demographics] [xml] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Person_BusinessEntityID] PRIMARY KEY([Businessentityid])
)
go

CREATE INDEX IX_Person_LastName_FirstName_MiddleName ON [Person].[Person]([Lastname], [Firstname], [Middlename])
go

ALTER TABLE [Person].[Person]
  ADD CONSTRAINT AK_Person_rowguid UNIQUE([Rowguid])
go

CREATE INDEX PXML_Person_AddContact ON [Person].[Person]([Additionalcontactinfo])
go

CREATE INDEX PXML_Person_Demographics ON [Person].[Person]([Demographics])
go

CREATE INDEX XMLPATH_Person_Demographics ON [Person].[Person]([Demographics])
go

CREATE INDEX XMLPROPERTY_Person_Demographics ON [Person].[Person]([Demographics])
go

CREATE INDEX XMLVALUE_Person_Demographics ON [Person].[Person]([Demographics])
go


/*
 * [Person].[PersonPhone]
 */
CREATE TABLE [Person].[PersonPhone]
(
    [Businessentityid] [int] NOT NULL,
    [Phonenumber] [phone] NOT NULL,
    [Phonenumbertypeid] [int] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_PersonPhone_BusinessEntityID_PhoneNumber_PhoneNumberTypeID] PRIMARY KEY([Businessentityid], [Phonenumber], [Phonenumbertypeid])
)
go

CREATE INDEX IX_PersonPhone_PhoneNumber ON [Person].[PersonPhone]([Phonenumber])
go


/*
 * [Person].[PhoneNumberType]
 */
CREATE TABLE [Person].[PhoneNumberType]
(
    [Phonenumbertypeid] [int] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_PhoneNumberType_PhoneNumberTypeID] PRIMARY KEY([Phonenumbertypeid])
)
go


/*
 * [Person].[StateProvince]
 */
CREATE TABLE [Person].[StateProvince]
(
    [Stateprovinceid] [int] IDENTITY NOT NULL,
    [Stateprovincecode] [nchar](3) NOT NULL,
    [Countryregioncode] [nvarchar](3) NOT NULL,
    [Isonlystateprovinceflag] [Flag] NOT NULL DEFAULT ((1)),
    [Name] [name] NOT NULL,
    [Territoryid] [int] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_StateProvince_StateProvinceID] PRIMARY KEY([Stateprovinceid])
)
go

ALTER TABLE [Person].[StateProvince]
  ADD CONSTRAINT AK_StateProvince_Name UNIQUE([Name])
go

ALTER TABLE [Person].[StateProvince]
  ADD CONSTRAINT AK_StateProvince_StateProvinceCode_CountryRegionCode UNIQUE([Stateprovincecode], [Countryregioncode])
go

ALTER TABLE [Person].[StateProvince]
  ADD CONSTRAINT AK_StateProvince_rowguid UNIQUE([Rowguid])
go


/*
 * [Production].[BillOfMaterials]
 */
CREATE TABLE [Production].[BillOfMaterials]
(
    [Billofmaterialsid] [int] IDENTITY NOT NULL,
    [Productassemblyid] [int] NULL,
    [Componentid] [int] NOT NULL,
    [Startdate] [datetime] NOT NULL DEFAULT (getdate()),
    [Enddate] [datetime] NULL,
    [Unitmeasurecode] [nchar](3) NOT NULL,
    [Bomlevel] [smallint] NOT NULL,
    [Perassemblyqty] [decimal] NOT NULL DEFAULT ((1.00)),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_BillOfMaterials_BillOfMaterialsID] PRIMARY KEY([Billofmaterialsid])
)
go

ALTER TABLE [Production].[BillOfMaterials]
  ADD CONSTRAINT AK_BillOfMaterials_ProductAssemblyID_ComponentID_StartDate UNIQUE([Productassemblyid], [Componentid], [Startdate])
go

CREATE INDEX IX_BillOfMaterials_UnitMeasureCode ON [Production].[BillOfMaterials]([Unitmeasurecode])
go


/*
 * [Production].[Culture]
 */
CREATE TABLE [Production].[Culture]
(
    [Cultureid] [nchar](6) NOT NULL,
    [Name] [name] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Culture_CultureID] PRIMARY KEY([Cultureid])
)
go

ALTER TABLE [Production].[Culture]
  ADD CONSTRAINT AK_Culture_Name UNIQUE([Name])
go


/*
 * [Production].[Document]
 */
CREATE TABLE [Production].[Document]
(
    [Documentnode] [hierarchyid] NOT NULL,
    [Documentlevel] AS ([DocumentNode].[GetLevel]()),
    [Title] [nvarchar](50) NOT NULL,
    [Owner] [int] NOT NULL,
    [Folderflag] [bit] NOT NULL DEFAULT ((0)),
    [Filename] [nvarchar](400) NOT NULL,
    [Fileextension] [nvarchar](8) NOT NULL,
    [Revision] [nchar](5) NOT NULL,
    [Changenumber] [int] NOT NULL DEFAULT ((0)),
    [Status] [tinyint] NOT NULL,
    [Documentsummary] [nvarchar](max) NULL,
    [Document] [varbinary](max) NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Document_DocumentNode] PRIMARY KEY([Documentnode])
)
go

ALTER TABLE [Production].[Document]
  ADD CONSTRAINT UQ__Document__F73921F7C81C642F UNIQUE([Rowguid])
go

ALTER TABLE [Production].[Document]
  ADD CONSTRAINT AK_Document_DocumentLevel_DocumentNode UNIQUE([Documentlevel], [Documentnode])
go

ALTER TABLE [Production].[Document]
  ADD CONSTRAINT AK_Document_rowguid UNIQUE([Rowguid])
go

CREATE INDEX IX_Document_FileName_Revision ON [Production].[Document]([Filename], [Revision])
go


/*
 * [Production].[Illustration]
 */
CREATE TABLE [Production].[Illustration]
(
    [Illustrationid] [int] IDENTITY NOT NULL,
    [Diagram] [xml] NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Illustration_IllustrationID] PRIMARY KEY([Illustrationid])
)
go


/*
 * [Production].[Location]
 */
CREATE TABLE [Production].[Location]
(
    [Locationid] [smallint] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Costrate] [smallmoney] NOT NULL DEFAULT ((0.00)),
    [Availability] [decimal] NOT NULL DEFAULT ((0.00)),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Location_LocationID] PRIMARY KEY([Locationid])
)
go

ALTER TABLE [Production].[Location]
  ADD CONSTRAINT AK_Location_Name UNIQUE([Name])
go


/*
 * [Production].[Product]
 */
CREATE TABLE [Production].[Product]
(
    [Productid] [int] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Productnumber] [nvarchar](25) NOT NULL,
    [Makeflag] [Flag] NOT NULL DEFAULT ((1)),
    [Finishedgoodsflag] [Flag] NOT NULL DEFAULT ((1)),
    [Color] [nvarchar](15) NULL,
    [Safetystocklevel] [smallint] NOT NULL,
    [Reorderpoint] [smallint] NOT NULL,
    [Standardcost] [money] NOT NULL,
    [Listprice] [money] NOT NULL,
    [Size] [nvarchar](5) NULL,
    [Sizeunitmeasurecode] [nchar](3) NULL,
    [Weightunitmeasurecode] [nchar](3) NULL,
    [Weight] [decimal] NULL,
    [Daystomanufacture] [int] NOT NULL,
    [Productline] [nchar](2) NULL,
    [Class] [nchar](2) NULL,
    [Style] [nchar](2) NULL,
    [Productsubcategoryid] [int] NULL,
    [Productmodelid] [int] NULL,
    [Sellstartdate] [datetime] NOT NULL,
    [Sellenddate] [datetime] NULL,
    [Discontinueddate] [datetime] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Product_ProductID] PRIMARY KEY([Productid])
)
go

ALTER TABLE [Production].[Product]
  ADD CONSTRAINT AK_Product_ProductNumber UNIQUE([Productnumber])
go

ALTER TABLE [Production].[Product]
  ADD CONSTRAINT AK_Product_Name UNIQUE([Name])
go

ALTER TABLE [Production].[Product]
  ADD CONSTRAINT AK_Product_rowguid UNIQUE([Rowguid])
go


/*
 * [Production].[ProductCategory]
 */
CREATE TABLE [Production].[ProductCategory]
(
    [Productcategoryid] [int] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductCategory_ProductCategoryID] PRIMARY KEY([Productcategoryid])
)
go

ALTER TABLE [Production].[ProductCategory]
  ADD CONSTRAINT AK_ProductCategory_Name UNIQUE([Name])
go

ALTER TABLE [Production].[ProductCategory]
  ADD CONSTRAINT AK_ProductCategory_rowguid UNIQUE([Rowguid])
go


/*
 * [Production].[ProductCostHistory]
 */
CREATE TABLE [Production].[ProductCostHistory]
(
    [Productid] [int] NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NULL,
    [Standardcost] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductCostHistory_ProductID_StartDate] PRIMARY KEY([Productid], [Startdate])
)
go


/*
 * [Production].[ProductDescription]
 */
CREATE TABLE [Production].[ProductDescription]
(
    [Productdescriptionid] [int] IDENTITY NOT NULL,
    [Description] [nvarchar](400) NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductDescription_ProductDescriptionID] PRIMARY KEY([Productdescriptionid])
)
go

ALTER TABLE [Production].[ProductDescription]
  ADD CONSTRAINT AK_ProductDescription_rowguid UNIQUE([Rowguid])
go


/*
 * [Production].[ProductDocument]
 */
CREATE TABLE [Production].[ProductDocument]
(
    [Productid] [int] NOT NULL,
    [Documentnode] [hierarchyid] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductDocument_ProductID_DocumentNode] PRIMARY KEY([Productid], [Documentnode])
)
go


/*
 * [Production].[ProductInventory]
 */
CREATE TABLE [Production].[ProductInventory]
(
    [Productid] [int] NOT NULL,
    [Locationid] [smallint] NOT NULL,
    [Shelf] [nvarchar](10) NOT NULL,
    [Bin] [tinyint] NOT NULL,
    [Quantity] [smallint] NOT NULL DEFAULT ((0)),
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductInventory_ProductID_LocationID] PRIMARY KEY([Productid], [Locationid])
)
go


/*
 * [Production].[ProductListPriceHistory]
 */
CREATE TABLE [Production].[ProductListPriceHistory]
(
    [Productid] [int] NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NULL,
    [Listprice] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductListPriceHistory_ProductID_StartDate] PRIMARY KEY([Productid], [Startdate])
)
go


/*
 * [Production].[ProductModel]
 */
CREATE TABLE [Production].[ProductModel]
(
    [Productmodelid] [int] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Catalogdescription] [xml] NULL,
    [Instructions] [xml] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductModel_ProductModelID] PRIMARY KEY([Productmodelid])
)
go

ALTER TABLE [Production].[ProductModel]
  ADD CONSTRAINT AK_ProductModel_Name UNIQUE([Name])
go

ALTER TABLE [Production].[ProductModel]
  ADD CONSTRAINT AK_ProductModel_rowguid UNIQUE([Rowguid])
go

CREATE INDEX PXML_ProductModel_CatalogDescription ON [Production].[ProductModel]([Catalogdescription])
go

CREATE INDEX PXML_ProductModel_Instructions ON [Production].[ProductModel]([Instructions])
go


/*
 * [Production].[ProductModelIllustration]
 */
CREATE TABLE [Production].[ProductModelIllustration]
(
    [Productmodelid] [int] NOT NULL,
    [Illustrationid] [int] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductModelIllustration_ProductModelID_IllustrationID] PRIMARY KEY([Productmodelid], [Illustrationid])
)
go


/*
 * [Production].[ProductModelProductDescriptionCulture]
 */
CREATE TABLE [Production].[ProductModelProductDescriptionCulture]
(
    [Productmodelid] [int] NOT NULL,
    [Productdescriptionid] [int] NOT NULL,
    [Cultureid] [nchar](6) NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductModelProductDescriptionCulture_ProductModelID_ProductDescriptionID_CultureID] PRIMARY KEY([Productmodelid], [Productdescriptionid], [Cultureid])
)
go


/*
 * [Production].[ProductPhoto]
 */
CREATE TABLE [Production].[ProductPhoto]
(
    [Productphotoid] [int] IDENTITY NOT NULL,
    [Thumbnailphoto] [varbinary](max) NULL,
    [Thumbnailphotofilename] [nvarchar](50) NULL,
    [Largephoto] [varbinary](max) NULL,
    [Largephotofilename] [nvarchar](50) NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductPhoto_ProductPhotoID] PRIMARY KEY([Productphotoid])
)
go


/*
 * [Production].[ProductProductPhoto]
 */
CREATE TABLE [Production].[ProductProductPhoto]
(
    [Productid] [int] NOT NULL,
    [Productphotoid] [int] NOT NULL,
    [Primary] [Flag] NOT NULL DEFAULT ((0)),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductProductPhoto_ProductID_ProductPhotoID] PRIMARY KEY([Productid], [Productphotoid])
)
go


/*
 * [Production].[ProductReview]
 */
CREATE TABLE [Production].[ProductReview]
(
    [Productreviewid] [int] IDENTITY NOT NULL,
    [Productid] [int] NOT NULL,
    [Reviewername] [name] NOT NULL,
    [Reviewdate] [datetime] NOT NULL DEFAULT (getdate()),
    [Emailaddress] [nvarchar](50) NOT NULL,
    [Rating] [int] NOT NULL,
    [Comments] [nvarchar](3850) NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductReview_ProductReviewID] PRIMARY KEY([Productreviewid])
)
go

CREATE INDEX IX_ProductReview_ProductID_Name ON [Production].[ProductReview]([Comments], [Productid], [Reviewername])
go


/*
 * [Production].[ProductSubcategory]
 */
CREATE TABLE [Production].[ProductSubcategory]
(
    [Productsubcategoryid] [int] IDENTITY NOT NULL,
    [Productcategoryid] [int] NOT NULL,
    [Name] [name] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductSubcategory_ProductSubcategoryID] PRIMARY KEY([Productsubcategoryid])
)
go

ALTER TABLE [Production].[ProductSubcategory]
  ADD CONSTRAINT AK_ProductSubcategory_Name UNIQUE([Name])
go

ALTER TABLE [Production].[ProductSubcategory]
  ADD CONSTRAINT AK_ProductSubcategory_rowguid UNIQUE([Rowguid])
go


/*
 * [Production].[ScrapReason]
 */
CREATE TABLE [Production].[ScrapReason]
(
    [Scrapreasonid] [smallint] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ScrapReason_ScrapReasonID] PRIMARY KEY([Scrapreasonid])
)
go

ALTER TABLE [Production].[ScrapReason]
  ADD CONSTRAINT AK_ScrapReason_Name UNIQUE([Name])
go


/*
 * [Production].[TransactionHistory]
 */
CREATE TABLE [Production].[TransactionHistory]
(
    [Transactionid] [int] IDENTITY(100000,1) NOT NULL,
    [Productid] [int] NOT NULL,
    [Referenceorderid] [int] NOT NULL,
    [Referenceorderlineid] [int] NOT NULL DEFAULT ((0)),
    [Transactiondate] [datetime] NOT NULL DEFAULT (getdate()),
    [Transactiontype] [nchar](1) NOT NULL,
    [Quantity] [int] NOT NULL,
    [Actualcost] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_TransactionHistory_TransactionID] PRIMARY KEY([Transactionid])
)
go

CREATE INDEX IX_TransactionHistory_ProductID ON [Production].[TransactionHistory]([Productid])
go

CREATE INDEX IX_TransactionHistory_ReferenceOrderID_ReferenceOrderLineID ON [Production].[TransactionHistory]([Referenceorderid], [Referenceorderlineid])
go


/*
 * [Production].[TransactionHistoryArchive]
 */
CREATE TABLE [Production].[TransactionHistoryArchive]
(
    [Transactionid] [int] NOT NULL,
    [Productid] [int] NOT NULL,
    [Referenceorderid] [int] NOT NULL,
    [Referenceorderlineid] [int] NOT NULL DEFAULT ((0)),
    [Transactiondate] [datetime] NOT NULL DEFAULT (getdate()),
    [Transactiontype] [nchar](1) NOT NULL,
    [Quantity] [int] NOT NULL,
    [Actualcost] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_TransactionHistoryArchive_TransactionID] PRIMARY KEY([Transactionid])
)
go

CREATE INDEX IX_TransactionHistoryArchive_ProductID ON [Production].[TransactionHistoryArchive]([Productid])
go

CREATE INDEX IX_TransactionHistoryArchive_ReferenceOrderID_ReferenceOrderLineID ON [Production].[TransactionHistoryArchive]([Referenceorderid], [Referenceorderlineid])
go


/*
 * [Production].[UnitMeasure]
 */
CREATE TABLE [Production].[UnitMeasure]
(
    [Unitmeasurecode] [nchar](3) NOT NULL,
    [Name] [name] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_UnitMeasure_UnitMeasureCode] PRIMARY KEY([Unitmeasurecode])
)
go

ALTER TABLE [Production].[UnitMeasure]
  ADD CONSTRAINT AK_UnitMeasure_Name UNIQUE([Name])
go


/*
 * [Production].[WorkOrder]
 */
CREATE TABLE [Production].[WorkOrder]
(
    [Workorderid] [int] IDENTITY NOT NULL,
    [Productid] [int] NOT NULL,
    [Orderqty] [int] NOT NULL,
    [Stockedqty] AS (isnull([OrderQty]-[ScrappedQty],(0))),
    [Scrappedqty] [smallint] NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NULL,
    [Duedate] [datetime] NOT NULL,
    [Scrapreasonid] [smallint] NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_WorkOrder_WorkOrderID] PRIMARY KEY([Workorderid])
)
go

CREATE INDEX IX_WorkOrder_ScrapReasonID ON [Production].[WorkOrder]([Scrapreasonid])
go

CREATE INDEX IX_WorkOrder_ProductID ON [Production].[WorkOrder]([Productid])
go


/*
 * [Production].[WorkOrderRouting]
 */
CREATE TABLE [Production].[WorkOrderRouting]
(
    [Workorderid] [int] NOT NULL,
    [Productid] [int] NOT NULL,
    [Operationsequence] [smallint] NOT NULL,
    [Locationid] [smallint] NOT NULL,
    [Scheduledstartdate] [datetime] NOT NULL,
    [Scheduledenddate] [datetime] NOT NULL,
    [Actualstartdate] [datetime] NULL,
    [Actualenddate] [datetime] NULL,
    [Actualresourcehrs] [decimal] NULL,
    [Plannedcost] [money] NOT NULL,
    [Actualcost] [money] NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_WorkOrderRouting_WorkOrderID_ProductID_OperationSequence] PRIMARY KEY([Workorderid], [Productid], [Operationsequence])
)
go

CREATE INDEX IX_WorkOrderRouting_ProductID ON [Production].[WorkOrderRouting]([Productid])
go


/*
 * [Purchasing].[ProductVendor]
 */
CREATE TABLE [Purchasing].[ProductVendor]
(
    [Productid] [int] NOT NULL,
    [Businessentityid] [int] NOT NULL,
    [Averageleadtime] [int] NOT NULL,
    [Standardprice] [money] NOT NULL,
    [Lastreceiptcost] [money] NULL,
    [Lastreceiptdate] [datetime] NULL,
    [Minorderqty] [int] NOT NULL,
    [Maxorderqty] [int] NOT NULL,
    [Onorderqty] [int] NULL,
    [Unitmeasurecode] [nchar](3) NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ProductVendor_ProductID_BusinessEntityID] PRIMARY KEY([Productid], [Businessentityid])
)
go

CREATE INDEX IX_ProductVendor_UnitMeasureCode ON [Purchasing].[ProductVendor]([Unitmeasurecode])
go

CREATE INDEX IX_ProductVendor_BusinessEntityID ON [Purchasing].[ProductVendor]([Businessentityid])
go


/*
 * [Purchasing].[PurchaseOrderDetail]
 */
CREATE TABLE [Purchasing].[PurchaseOrderDetail]
(
    [Purchaseorderid] [int] NOT NULL,
    [Purchaseorderdetailid] [int] IDENTITY NOT NULL,
    [Duedate] [datetime] NOT NULL,
    [Orderqty] [smallint] NOT NULL,
    [Productid] [int] NOT NULL,
    [Unitprice] [money] NOT NULL,
    [Linetotal] AS (isnull([OrderQty]*[UnitPrice],(0.00))),
    [Receivedqty] [decimal] NOT NULL,
    [Rejectedqty] [decimal] NOT NULL,
    [Stockedqty] AS (isnull([ReceivedQty]-[RejectedQty],(0.00))),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_PurchaseOrderDetail_PurchaseOrderID_PurchaseOrderDetailID] PRIMARY KEY([Purchaseorderid], [Purchaseorderdetailid])
)
go

CREATE INDEX IX_PurchaseOrderDetail_ProductID ON [Purchasing].[PurchaseOrderDetail]([Productid])
go


/*
 * [Purchasing].[PurchaseOrderHeader]
 */
CREATE TABLE [Purchasing].[PurchaseOrderHeader]
(
    [Purchaseorderid] [int] IDENTITY NOT NULL,
    [Revisionnumber] [tinyint] NOT NULL DEFAULT ((0)),
    [Status] [tinyint] NOT NULL DEFAULT ((1)),
    [Employeeid] [int] NOT NULL,
    [Vendorid] [int] NOT NULL,
    [Shipmethodid] [int] NOT NULL,
    [Orderdate] [datetime] NOT NULL DEFAULT (getdate()),
    [Shipdate] [datetime] NULL,
    [Subtotal] [money] NOT NULL DEFAULT ((0.00)),
    [Taxamt] [money] NOT NULL DEFAULT ((0.00)),
    [Freight] [money] NOT NULL DEFAULT ((0.00)),
    [Totaldue] AS ((isnull(([SubTotal]+[TaxAmt])+[Freight],(0)))) PERSISTED,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_PurchaseOrderHeader_PurchaseOrderID] PRIMARY KEY([Purchaseorderid])
)
go

CREATE INDEX IX_PurchaseOrderHeader_VendorID ON [Purchasing].[PurchaseOrderHeader]([Vendorid])
go

CREATE INDEX IX_PurchaseOrderHeader_EmployeeID ON [Purchasing].[PurchaseOrderHeader]([Employeeid])
go


/*
 * [Purchasing].[ShipMethod]
 */
CREATE TABLE [Purchasing].[ShipMethod]
(
    [Shipmethodid] [int] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Shipbase] [money] NOT NULL DEFAULT ((0.00)),
    [Shiprate] [money] NOT NULL DEFAULT ((0.00)),
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ShipMethod_ShipMethodID] PRIMARY KEY([Shipmethodid])
)
go

ALTER TABLE [Purchasing].[ShipMethod]
  ADD CONSTRAINT AK_ShipMethod_Name UNIQUE([Name])
go

ALTER TABLE [Purchasing].[ShipMethod]
  ADD CONSTRAINT AK_ShipMethod_rowguid UNIQUE([Rowguid])
go


/*
 * [Purchasing].[Vendor]
 */
CREATE TABLE [Purchasing].[Vendor]
(
    [Businessentityid] [int] NOT NULL,
    [Accountnumber] [accountnumber] NOT NULL,
    [Name] [name] NOT NULL,
    [Creditrating] [tinyint] NOT NULL,
    [Preferredvendorstatus] [Flag] NOT NULL DEFAULT ((1)),
    [Activeflag] [Flag] NOT NULL DEFAULT ((1)),
    [Purchasingwebserviceurl] [nvarchar](1024) NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Vendor_BusinessEntityID] PRIMARY KEY([Businessentityid])
)
go

ALTER TABLE [Purchasing].[Vendor]
  ADD CONSTRAINT AK_Vendor_AccountNumber UNIQUE([Accountnumber])
go


/*
 * [Sales].[CountryRegionCurrency]
 */
CREATE TABLE [Sales].[CountryRegionCurrency]
(
    [Countryregioncode] [nvarchar](3) NOT NULL,
    [Currencycode] [nchar](3) NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_CountryRegionCurrency_CountryRegionCode_CurrencyCode] PRIMARY KEY([Countryregioncode], [Currencycode])
)
go

CREATE INDEX IX_CountryRegionCurrency_CurrencyCode ON [Sales].[CountryRegionCurrency]([Currencycode])
go


/*
 * [Sales].[CreditCard]
 */
CREATE TABLE [Sales].[CreditCard]
(
    [Creditcardid] [int] IDENTITY NOT NULL,
    [Cardtype] [nvarchar](50) NOT NULL,
    [Cardnumber] [nvarchar](25) NOT NULL,
    [Expmonth] [tinyint] NOT NULL,
    [Expyear] [smallint] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_CreditCard_CreditCardID] PRIMARY KEY([Creditcardid])
)
go

ALTER TABLE [Sales].[CreditCard]
  ADD CONSTRAINT AK_CreditCard_CardNumber UNIQUE([Cardnumber])
go


/*
 * [Sales].[Currency]
 */
CREATE TABLE [Sales].[Currency]
(
    [Currencycode] [nchar](3) NOT NULL,
    [Name] [name] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Currency_CurrencyCode] PRIMARY KEY([Currencycode])
)
go

ALTER TABLE [Sales].[Currency]
  ADD CONSTRAINT AK_Currency_Name UNIQUE([Name])
go


/*
 * [Sales].[CurrencyRate]
 */
CREATE TABLE [Sales].[CurrencyRate]
(
    [Currencyrateid] [int] IDENTITY NOT NULL,
    [Currencyratedate] [datetime] NOT NULL,
    [Fromcurrencycode] [nchar](3) NOT NULL,
    [Tocurrencycode] [nchar](3) NOT NULL,
    [Averagerate] [money] NOT NULL,
    [Endofdayrate] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_CurrencyRate_CurrencyRateID] PRIMARY KEY([Currencyrateid])
)
go

ALTER TABLE [Sales].[CurrencyRate]
  ADD CONSTRAINT AK_CurrencyRate_CurrencyRateDate_FromCurrencyCode_ToCurrencyCode UNIQUE([Currencyratedate], [Fromcurrencycode], [Tocurrencycode])
go


/*
 * [Sales].[Customer]
 */
CREATE TABLE [Sales].[Customer]
(
    [Customerid] [int] IDENTITY NOT NULL,
    [Personid] [int] NULL,
    [Storeid] [int] NULL,
    [Territoryid] [int] NULL,
    [Accountnumber] AS (isnull('AW'+[dbo].[ufnLeadingZeros]([CustomerID]),'')),
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Customer_CustomerID] PRIMARY KEY([Customerid])
)
go

ALTER TABLE [Sales].[Customer]
  ADD CONSTRAINT AK_Customer_rowguid UNIQUE([Rowguid])
go

ALTER TABLE [Sales].[Customer]
  ADD CONSTRAINT AK_Customer_AccountNumber UNIQUE([Accountnumber])
go

CREATE INDEX IX_Customer_TerritoryID ON [Sales].[Customer]([Territoryid])
go


/*
 * [Sales].[PersonCreditCard]
 */
CREATE TABLE [Sales].[PersonCreditCard]
(
    [Businessentityid] [int] NOT NULL,
    [Creditcardid] [int] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_PersonCreditCard_BusinessEntityID_CreditCardID] PRIMARY KEY([Businessentityid], [Creditcardid])
)
go


/*
 * [Sales].[SalesOrderDetail]
 */
CREATE TABLE [Sales].[SalesOrderDetail]
(
    [Salesorderid] [int] NOT NULL,
    [Salesorderdetailid] [int] IDENTITY NOT NULL,
    [Carriertrackingnumber] [nvarchar](25) NULL,
    [Orderqty] [smallint] NOT NULL,
    [Productid] [int] NOT NULL,
    [Specialofferid] [int] NOT NULL,
    [Unitprice] [money] NOT NULL,
    [Unitpricediscount] [money] NOT NULL DEFAULT ((0.0)),
    [Linetotal] AS (isnull(([UnitPrice]*((1.0)-[UnitPriceDiscount]))*[OrderQty],(0.0))),
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SalesOrderDetail_SalesOrderID_SalesOrderDetailID] PRIMARY KEY([Salesorderid], [Salesorderdetailid])
)
go

ALTER TABLE [Sales].[SalesOrderDetail]
  ADD CONSTRAINT AK_SalesOrderDetail_rowguid UNIQUE([Rowguid])
go

CREATE INDEX IX_SalesOrderDetail_ProductID ON [Sales].[SalesOrderDetail]([Productid])
go


/*
 * [Sales].[SalesOrderHeader]
 */
CREATE TABLE [Sales].[SalesOrderHeader]
(
    [Salesorderid] [int] IDENTITY NOT NULL,
    [Revisionnumber] [tinyint] NOT NULL DEFAULT ((0)),
    [Orderdate] [datetime] NOT NULL DEFAULT (getdate()),
    [Duedate] [datetime] NOT NULL,
    [Shipdate] [datetime] NULL,
    [Status] [tinyint] NOT NULL DEFAULT ((1)),
    [Onlineorderflag] [Flag] NOT NULL DEFAULT ((1)),
    [Salesordernumber] AS (isnull(N'SO'+CONVERT([nvarchar](23),[SalesOrderID]),N'*** ERROR ***')),
    [Purchaseordernumber] [ordernumber] NULL,
    [Accountnumber] [accountnumber] NULL,
    [Customerid] [int] NOT NULL,
    [Salespersonid] [int] NULL,
    [Territoryid] [int] NULL,
    [Billtoaddressid] [int] NOT NULL,
    [Shiptoaddressid] [int] NOT NULL,
    [Shipmethodid] [int] NOT NULL,
    [Creditcardid] [int] NULL,
    [Creditcardapprovalcode] [varchar](15) NULL,
    [Currencyrateid] [int] NULL,
    [Subtotal] [money] NOT NULL DEFAULT ((0.00)),
    [Taxamt] [money] NOT NULL DEFAULT ((0.00)),
    [Freight] [money] NOT NULL DEFAULT ((0.00)),
    [Totaldue] AS (isnull(([SubTotal]+[TaxAmt])+[Freight],(0))),
    [Comment] [nvarchar](128) NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SalesOrderHeader_SalesOrderID] PRIMARY KEY([Salesorderid])
)
go

ALTER TABLE [Sales].[SalesOrderHeader]
  ADD CONSTRAINT AK_SalesOrderHeader_rowguid UNIQUE([Rowguid])
go

ALTER TABLE [Sales].[SalesOrderHeader]
  ADD CONSTRAINT AK_SalesOrderHeader_SalesOrderNumber UNIQUE([Salesordernumber])
go

CREATE INDEX IX_SalesOrderHeader_CustomerID ON [Sales].[SalesOrderHeader]([Customerid])
go

CREATE INDEX IX_SalesOrderHeader_SalesPersonID ON [Sales].[SalesOrderHeader]([Salespersonid])
go


/*
 * [Sales].[SalesOrderHeaderSalesReason]
 */
CREATE TABLE [Sales].[SalesOrderHeaderSalesReason]
(
    [Salesorderid] [int] NOT NULL,
    [Salesreasonid] [int] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SalesOrderHeaderSalesReason_SalesOrderID_SalesReasonID] PRIMARY KEY([Salesorderid], [Salesreasonid])
)
go


/*
 * [Sales].[SalesPerson]
 */
CREATE TABLE [Sales].[SalesPerson]
(
    [Businessentityid] [int] NOT NULL,
    [Territoryid] [int] NULL,
    [Salesquota] [money] NULL,
    [Bonus] [money] NOT NULL DEFAULT ((0.00)),
    [Commissionpct] [smallmoney] NOT NULL DEFAULT ((0.00)),
    [Salesytd] [money] NOT NULL DEFAULT ((0.00)),
    [Saleslastyear] [money] NOT NULL DEFAULT ((0.00)),
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SalesPerson_BusinessEntityID] PRIMARY KEY([Businessentityid])
)
go

ALTER TABLE [Sales].[SalesPerson]
  ADD CONSTRAINT AK_SalesPerson_rowguid UNIQUE([Rowguid])
go


/*
 * [Sales].[SalesPersonQuotaHistory]
 */
CREATE TABLE [Sales].[SalesPersonQuotaHistory]
(
    [Businessentityid] [int] NOT NULL,
    [Quotadate] [datetime] NOT NULL,
    [Salesquota] [money] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SalesPersonQuotaHistory_BusinessEntityID_QuotaDate] PRIMARY KEY([Businessentityid], [Quotadate])
)
go

ALTER TABLE [Sales].[SalesPersonQuotaHistory]
  ADD CONSTRAINT AK_SalesPersonQuotaHistory_rowguid UNIQUE([Rowguid])
go


/*
 * [Sales].[SalesReason]
 */
CREATE TABLE [Sales].[SalesReason]
(
    [Salesreasonid] [int] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Reasontype] [name] NOT NULL,
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SalesReason_SalesReasonID] PRIMARY KEY([Salesreasonid])
)
go


/*
 * [Sales].[SalesTaxRate]
 */
CREATE TABLE [Sales].[SalesTaxRate]
(
    [Salestaxrateid] [int] IDENTITY NOT NULL,
    [Stateprovinceid] [int] NOT NULL,
    [Taxtype] [tinyint] NOT NULL,
    [Taxrate] [smallmoney] NOT NULL DEFAULT ((0.00)),
    [Name] [name] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SalesTaxRate_SalesTaxRateID] PRIMARY KEY([Salestaxrateid])
)
go

ALTER TABLE [Sales].[SalesTaxRate]
  ADD CONSTRAINT AK_SalesTaxRate_StateProvinceID_TaxType UNIQUE([Stateprovinceid], [Taxtype])
go

ALTER TABLE [Sales].[SalesTaxRate]
  ADD CONSTRAINT AK_SalesTaxRate_rowguid UNIQUE([Rowguid])
go


/*
 * [Sales].[SalesTerritory]
 */
CREATE TABLE [Sales].[SalesTerritory]
(
    [Territoryid] [int] IDENTITY NOT NULL,
    [Name] [name] NOT NULL,
    [Countryregioncode] [nvarchar](3) NOT NULL,
    [Group] [nvarchar](50) NOT NULL,
    [Salesytd] [money] NOT NULL DEFAULT ((0.00)),
    [Saleslastyear] [money] NOT NULL DEFAULT ((0.00)),
    [Costytd] [money] NOT NULL DEFAULT ((0.00)),
    [Costlastyear] [money] NOT NULL DEFAULT ((0.00)),
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SalesTerritory_TerritoryID] PRIMARY KEY([Territoryid])
)
go

ALTER TABLE [Sales].[SalesTerritory]
  ADD CONSTRAINT AK_SalesTerritory_Name UNIQUE([Name])
go

ALTER TABLE [Sales].[SalesTerritory]
  ADD CONSTRAINT AK_SalesTerritory_rowguid UNIQUE([Rowguid])
go


/*
 * [Sales].[SalesTerritoryHistory]
 */
CREATE TABLE [Sales].[SalesTerritoryHistory]
(
    [Businessentityid] [int] NOT NULL,
    [Territoryid] [int] NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SalesTerritoryHistory_BusinessEntityID_StartDate_TerritoryID] PRIMARY KEY([Businessentityid], [Startdate], [Territoryid])
)
go

ALTER TABLE [Sales].[SalesTerritoryHistory]
  ADD CONSTRAINT AK_SalesTerritoryHistory_rowguid UNIQUE([Rowguid])
go


/*
 * [Sales].[ShoppingCartItem]
 */
CREATE TABLE [Sales].[ShoppingCartItem]
(
    [Shoppingcartitemid] [int] IDENTITY NOT NULL,
    [Shoppingcartid] [nvarchar](50) NOT NULL,
    [Quantity] [int] NOT NULL DEFAULT ((1)),
    [Productid] [int] NOT NULL,
    [Datecreated] [datetime] NOT NULL DEFAULT (getdate()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_ShoppingCartItem_ShoppingCartItemID] PRIMARY KEY([Shoppingcartitemid])
)
go

CREATE INDEX IX_ShoppingCartItem_ShoppingCartID_ProductID ON [Sales].[ShoppingCartItem]([Shoppingcartid], [Productid])
go


/*
 * [Sales].[SpecialOffer]
 */
CREATE TABLE [Sales].[SpecialOffer]
(
    [Specialofferid] [int] IDENTITY NOT NULL,
    [Description] [nvarchar](255) NOT NULL,
    [Discountpct] [smallmoney] NOT NULL DEFAULT ((0.00)),
    [Type] [nvarchar](50) NOT NULL,
    [Category] [nvarchar](50) NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NOT NULL,
    [Minqty] [int] NOT NULL DEFAULT ((0)),
    [Maxqty] [int] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SpecialOffer_SpecialOfferID] PRIMARY KEY([Specialofferid])
)
go

ALTER TABLE [Sales].[SpecialOffer]
  ADD CONSTRAINT AK_SpecialOffer_rowguid UNIQUE([Rowguid])
go


/*
 * [Sales].[SpecialOfferProduct]
 */
CREATE TABLE [Sales].[SpecialOfferProduct]
(
    [Specialofferid] [int] NOT NULL,
    [Productid] [int] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_SpecialOfferProduct_SpecialOfferID_ProductID] PRIMARY KEY([Specialofferid], [Productid])
)
go

ALTER TABLE [Sales].[SpecialOfferProduct]
  ADD CONSTRAINT AK_SpecialOfferProduct_rowguid UNIQUE([Rowguid])
go

CREATE INDEX IX_SpecialOfferProduct_ProductID ON [Sales].[SpecialOfferProduct]([Productid])
go


/*
 * [Sales].[Store]
 */
CREATE TABLE [Sales].[Store]
(
    [Businessentityid] [int] NOT NULL,
    [Name] [name] NOT NULL,
    [Salespersonid] [int] NULL,
    [Demographics] [xml] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL DEFAULT (newid()),
    [Modifieddate] [datetime] NOT NULL DEFAULT (getdate()),
    CONSTRAINT [PK_Store_BusinessEntityID] PRIMARY KEY([Businessentityid])
)
go

ALTER TABLE [Sales].[Store]
  ADD CONSTRAINT AK_Store_rowguid UNIQUE([Rowguid])
go

CREATE INDEX IX_Store_SalesPersonID ON [Sales].[Store]([Salespersonid])
go

CREATE INDEX PXML_Store_Demographics ON [Sales].[Store]([Demographics])
go


ALTER TABLE [HumanResources].[Employee]
  ADD CONSTRAINT FK_Employee_Person_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Person].[Person]([Businessentityid])
go

ALTER TABLE [HumanResources].[EmployeeDepartmentHistory]
  ADD CONSTRAINT FK_EmployeeDepartmentHistory_Department_DepartmentID FOREIGN KEY([Departmentid])
  REFERENCES [HumanResources].[Department]([Departmentid])
go

ALTER TABLE [HumanResources].[EmployeeDepartmentHistory]
  ADD CONSTRAINT FK_EmployeeDepartmentHistory_Employee_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [HumanResources].[Employee]([Businessentityid])
go

ALTER TABLE [HumanResources].[EmployeeDepartmentHistory]
  ADD CONSTRAINT FK_EmployeeDepartmentHistory_Shift_ShiftID FOREIGN KEY([Shiftid])
  REFERENCES [HumanResources].[Shift]([Shiftid])
go

ALTER TABLE [HumanResources].[EmployeePayHistory]
  ADD CONSTRAINT FK_EmployeePayHistory_Employee_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [HumanResources].[Employee]([Businessentityid])
go

ALTER TABLE [HumanResources].[JobCandidate]
  ADD CONSTRAINT FK_JobCandidate_Employee_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [HumanResources].[Employee]([Businessentityid])
go

ALTER TABLE [Person].[Address]
  ADD CONSTRAINT FK_Address_StateProvince_StateProvinceID FOREIGN KEY([Stateprovinceid])
  REFERENCES [Person].[StateProvince]([Stateprovinceid])
go

ALTER TABLE [Person].[BusinessEntityAddress]
  ADD CONSTRAINT FK_BusinessEntityAddress_Address_AddressID FOREIGN KEY([Addressid])
  REFERENCES [Person].[Address]([Addressid])
go

ALTER TABLE [Person].[BusinessEntityAddress]
  ADD CONSTRAINT FK_BusinessEntityAddress_AddressType_AddressTypeID FOREIGN KEY([Addresstypeid])
  REFERENCES [Person].[AddressType]([Addresstypeid])
go

ALTER TABLE [Person].[BusinessEntityAddress]
  ADD CONSTRAINT FK_BusinessEntityAddress_BusinessEntity_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Person].[BusinessEntity]([Businessentityid])
go

ALTER TABLE [Person].[BusinessEntityContact]
  ADD CONSTRAINT FK_BusinessEntityContact_Person_PersonID FOREIGN KEY([Personid])
  REFERENCES [Person].[Person]([Businessentityid])
go

ALTER TABLE [Person].[BusinessEntityContact]
  ADD CONSTRAINT FK_BusinessEntityContact_ContactType_ContactTypeID FOREIGN KEY([Contacttypeid])
  REFERENCES [Person].[ContactType]([Contacttypeid])
go

ALTER TABLE [Person].[BusinessEntityContact]
  ADD CONSTRAINT FK_BusinessEntityContact_BusinessEntity_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Person].[BusinessEntity]([Businessentityid])
go

ALTER TABLE [Person].[EmailAddress]
  ADD CONSTRAINT FK_EmailAddress_Person_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Person].[Person]([Businessentityid])
go

ALTER TABLE [Person].[Password]
  ADD CONSTRAINT FK_Password_Person_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Person].[Person]([Businessentityid])
go

ALTER TABLE [Person].[Person]
  ADD CONSTRAINT FK_Person_BusinessEntity_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Person].[BusinessEntity]([Businessentityid])
go

ALTER TABLE [Person].[PersonPhone]
  ADD CONSTRAINT FK_PersonPhone_Person_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Person].[Person]([Businessentityid])
go

ALTER TABLE [Person].[PersonPhone]
  ADD CONSTRAINT FK_PersonPhone_PhoneNumberType_PhoneNumberTypeID FOREIGN KEY([Phonenumbertypeid])
  REFERENCES [Person].[PhoneNumberType]([Phonenumbertypeid])
go

ALTER TABLE [Person].[StateProvince]
  ADD CONSTRAINT FK_StateProvince_CountryRegion_CountryRegionCode FOREIGN KEY([Countryregioncode])
  REFERENCES [Person].[CountryRegion]([Countryregioncode])
go

ALTER TABLE [Person].[StateProvince]
  ADD CONSTRAINT FK_StateProvince_SalesTerritory_TerritoryID FOREIGN KEY([Territoryid])
  REFERENCES [Sales].[SalesTerritory]([Territoryid])
go

ALTER TABLE [Production].[BillOfMaterials]
  ADD CONSTRAINT FK_BillOfMaterials_Product_ProductAssemblyID FOREIGN KEY([Productassemblyid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Production].[BillOfMaterials]
  ADD CONSTRAINT FK_BillOfMaterials_Product_ComponentID FOREIGN KEY([Componentid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Production].[BillOfMaterials]
  ADD CONSTRAINT FK_BillOfMaterials_UnitMeasure_UnitMeasureCode FOREIGN KEY([Unitmeasurecode])
  REFERENCES [Production].[UnitMeasure]([Unitmeasurecode])
go

ALTER TABLE [Production].[Document]
  ADD CONSTRAINT FK_Document_Employee_Owner FOREIGN KEY([Owner])
  REFERENCES [HumanResources].[Employee]([Businessentityid])
go

ALTER TABLE [Production].[Product]
  ADD CONSTRAINT FK_Product_UnitMeasure_SizeUnitMeasureCode FOREIGN KEY([Sizeunitmeasurecode])
  REFERENCES [Production].[UnitMeasure]([Unitmeasurecode])
go

ALTER TABLE [Production].[Product]
  ADD CONSTRAINT FK_Product_UnitMeasure_WeightUnitMeasureCode FOREIGN KEY([Weightunitmeasurecode])
  REFERENCES [Production].[UnitMeasure]([Unitmeasurecode])
go

ALTER TABLE [Production].[Product]
  ADD CONSTRAINT FK_Product_ProductModel_ProductModelID FOREIGN KEY([Productmodelid])
  REFERENCES [Production].[ProductModel]([Productmodelid])
go

ALTER TABLE [Production].[Product]
  ADD CONSTRAINT FK_Product_ProductSubcategory_ProductSubcategoryID FOREIGN KEY([Productsubcategoryid])
  REFERENCES [Production].[ProductSubcategory]([Productsubcategoryid])
go

ALTER TABLE [Production].[ProductCostHistory]
  ADD CONSTRAINT FK_ProductCostHistory_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Production].[ProductDocument]
  ADD CONSTRAINT FK_ProductDocument_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Production].[ProductDocument]
  ADD CONSTRAINT FK_ProductDocument_Document_DocumentNode FOREIGN KEY([Documentnode])
  REFERENCES [Production].[Document]([Documentnode])
go

ALTER TABLE [Production].[ProductInventory]
  ADD CONSTRAINT FK_ProductInventory_Location_LocationID FOREIGN KEY([Locationid])
  REFERENCES [Production].[Location]([Locationid])
go

ALTER TABLE [Production].[ProductInventory]
  ADD CONSTRAINT FK_ProductInventory_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Production].[ProductListPriceHistory]
  ADD CONSTRAINT FK_ProductListPriceHistory_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Production].[ProductModelIllustration]
  ADD CONSTRAINT FK_ProductModelIllustration_ProductModel_ProductModelID FOREIGN KEY([Productmodelid])
  REFERENCES [Production].[ProductModel]([Productmodelid])
go

ALTER TABLE [Production].[ProductModelIllustration]
  ADD CONSTRAINT FK_ProductModelIllustration_Illustration_IllustrationID FOREIGN KEY([Illustrationid])
  REFERENCES [Production].[Illustration]([Illustrationid])
go

ALTER TABLE [Production].[ProductModelProductDescriptionCulture]
  ADD CONSTRAINT FK_ProductModelProductDescriptionCulture_ProductDescription_ProductDescriptionID FOREIGN KEY([Productdescriptionid])
  REFERENCES [Production].[ProductDescription]([Productdescriptionid])
go

ALTER TABLE [Production].[ProductModelProductDescriptionCulture]
  ADD CONSTRAINT FK_ProductModelProductDescriptionCulture_Culture_CultureID FOREIGN KEY([Cultureid])
  REFERENCES [Production].[Culture]([Cultureid])
go

ALTER TABLE [Production].[ProductModelProductDescriptionCulture]
  ADD CONSTRAINT FK_ProductModelProductDescriptionCulture_ProductModel_ProductModelID FOREIGN KEY([Productmodelid])
  REFERENCES [Production].[ProductModel]([Productmodelid])
go

ALTER TABLE [Production].[ProductProductPhoto]
  ADD CONSTRAINT FK_ProductProductPhoto_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Production].[ProductProductPhoto]
  ADD CONSTRAINT FK_ProductProductPhoto_ProductPhoto_ProductPhotoID FOREIGN KEY([Productphotoid])
  REFERENCES [Production].[ProductPhoto]([Productphotoid])
go

ALTER TABLE [Production].[ProductReview]
  ADD CONSTRAINT FK_ProductReview_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Production].[ProductSubcategory]
  ADD CONSTRAINT FK_ProductSubcategory_ProductCategory_ProductCategoryID FOREIGN KEY([Productcategoryid])
  REFERENCES [Production].[ProductCategory]([Productcategoryid])
go

ALTER TABLE [Production].[TransactionHistory]
  ADD CONSTRAINT FK_TransactionHistory_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Production].[WorkOrder]
  ADD CONSTRAINT FK_WorkOrder_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Production].[WorkOrder]
  ADD CONSTRAINT FK_WorkOrder_ScrapReason_ScrapReasonID FOREIGN KEY([Scrapreasonid])
  REFERENCES [Production].[ScrapReason]([Scrapreasonid])
go

ALTER TABLE [Production].[WorkOrderRouting]
  ADD CONSTRAINT FK_WorkOrderRouting_Location_LocationID FOREIGN KEY([Locationid])
  REFERENCES [Production].[Location]([Locationid])
go

ALTER TABLE [Production].[WorkOrderRouting]
  ADD CONSTRAINT FK_WorkOrderRouting_WorkOrder_WorkOrderID FOREIGN KEY([Workorderid])
  REFERENCES [Production].[WorkOrder]([Workorderid])
go

ALTER TABLE [Purchasing].[ProductVendor]
  ADD CONSTRAINT FK_ProductVendor_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Purchasing].[ProductVendor]
  ADD CONSTRAINT FK_ProductVendor_UnitMeasure_UnitMeasureCode FOREIGN KEY([Unitmeasurecode])
  REFERENCES [Production].[UnitMeasure]([Unitmeasurecode])
go

ALTER TABLE [Purchasing].[ProductVendor]
  ADD CONSTRAINT FK_ProductVendor_Vendor_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Purchasing].[Vendor]([Businessentityid])
go

ALTER TABLE [Purchasing].[PurchaseOrderDetail]
  ADD CONSTRAINT FK_PurchaseOrderDetail_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Purchasing].[PurchaseOrderDetail]
  ADD CONSTRAINT FK_PurchaseOrderDetail_PurchaseOrderHeader_PurchaseOrderID FOREIGN KEY([Purchaseorderid])
  REFERENCES [Purchasing].[PurchaseOrderHeader]([Purchaseorderid])
go

ALTER TABLE [Purchasing].[PurchaseOrderHeader]
  ADD CONSTRAINT FK_PurchaseOrderHeader_Employee_EmployeeID FOREIGN KEY([Employeeid])
  REFERENCES [HumanResources].[Employee]([Businessentityid])
go

ALTER TABLE [Purchasing].[PurchaseOrderHeader]
  ADD CONSTRAINT FK_PurchaseOrderHeader_Vendor_VendorID FOREIGN KEY([Vendorid])
  REFERENCES [Purchasing].[Vendor]([Businessentityid])
go

ALTER TABLE [Purchasing].[PurchaseOrderHeader]
  ADD CONSTRAINT FK_PurchaseOrderHeader_ShipMethod_ShipMethodID FOREIGN KEY([Shipmethodid])
  REFERENCES [Purchasing].[ShipMethod]([Shipmethodid])
go

ALTER TABLE [Purchasing].[Vendor]
  ADD CONSTRAINT FK_Vendor_BusinessEntity_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Person].[BusinessEntity]([Businessentityid])
go

ALTER TABLE [Sales].[CountryRegionCurrency]
  ADD CONSTRAINT FK_CountryRegionCurrency_CountryRegion_CountryRegionCode FOREIGN KEY([Countryregioncode])
  REFERENCES [Person].[CountryRegion]([Countryregioncode])
go

ALTER TABLE [Sales].[CountryRegionCurrency]
  ADD CONSTRAINT FK_CountryRegionCurrency_Currency_CurrencyCode FOREIGN KEY([Currencycode])
  REFERENCES [Sales].[Currency]([Currencycode])
go

ALTER TABLE [Sales].[CurrencyRate]
  ADD CONSTRAINT FK_CurrencyRate_Currency_FromCurrencyCode FOREIGN KEY([Fromcurrencycode])
  REFERENCES [Sales].[Currency]([Currencycode])
go

ALTER TABLE [Sales].[CurrencyRate]
  ADD CONSTRAINT FK_CurrencyRate_Currency_ToCurrencyCode FOREIGN KEY([Tocurrencycode])
  REFERENCES [Sales].[Currency]([Currencycode])
go

ALTER TABLE [Sales].[Customer]
  ADD CONSTRAINT FK_Customer_Person_PersonID FOREIGN KEY([Personid])
  REFERENCES [Person].[Person]([Businessentityid])
go

ALTER TABLE [Sales].[Customer]
  ADD CONSTRAINT FK_Customer_Store_StoreID FOREIGN KEY([Storeid])
  REFERENCES [Sales].[Store]([Businessentityid])
go

ALTER TABLE [Sales].[Customer]
  ADD CONSTRAINT FK_Customer_SalesTerritory_TerritoryID FOREIGN KEY([Territoryid])
  REFERENCES [Sales].[SalesTerritory]([Territoryid])
go

ALTER TABLE [Sales].[PersonCreditCard]
  ADD CONSTRAINT FK_PersonCreditCard_Person_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Person].[Person]([Businessentityid])
go

ALTER TABLE [Sales].[PersonCreditCard]
  ADD CONSTRAINT FK_PersonCreditCard_CreditCard_CreditCardID FOREIGN KEY([Creditcardid])
  REFERENCES [Sales].[CreditCard]([Creditcardid])
go

ALTER TABLE [Sales].[SalesOrderDetail]
  ADD CONSTRAINT FK_SalesOrderDetail_SalesOrderHeader_SalesOrderID FOREIGN KEY([Salesorderid])
  REFERENCES [Sales].[SalesOrderHeader]([Salesorderid])
go

ALTER TABLE [Sales].[SalesOrderDetail]
  ADD CONSTRAINT FK_SalesOrderDetail_SpecialOfferProduct_SpecialOfferIDProductID FOREIGN KEY([Specialofferid], [Productid])
  REFERENCES [Sales].[SpecialOfferProduct]([Specialofferid], [Productid])
go

ALTER TABLE [Sales].[SalesOrderHeader]
  ADD CONSTRAINT FK_SalesOrderHeader_Address_BillToAddressID FOREIGN KEY([Billtoaddressid])
  REFERENCES [Person].[Address]([Addressid])
go

ALTER TABLE [Sales].[SalesOrderHeader]
  ADD CONSTRAINT FK_SalesOrderHeader_Address_ShipToAddressID FOREIGN KEY([Shiptoaddressid])
  REFERENCES [Person].[Address]([Addressid])
go

ALTER TABLE [Sales].[SalesOrderHeader]
  ADD CONSTRAINT FK_SalesOrderHeader_CreditCard_CreditCardID FOREIGN KEY([Creditcardid])
  REFERENCES [Sales].[CreditCard]([Creditcardid])
go

ALTER TABLE [Sales].[SalesOrderHeader]
  ADD CONSTRAINT FK_SalesOrderHeader_CurrencyRate_CurrencyRateID FOREIGN KEY([Currencyrateid])
  REFERENCES [Sales].[CurrencyRate]([Currencyrateid])
go

ALTER TABLE [Sales].[SalesOrderHeader]
  ADD CONSTRAINT FK_SalesOrderHeader_Customer_CustomerID FOREIGN KEY([Customerid])
  REFERENCES [Sales].[Customer]([Customerid])
go

ALTER TABLE [Sales].[SalesOrderHeader]
  ADD CONSTRAINT FK_SalesOrderHeader_SalesPerson_SalesPersonID FOREIGN KEY([Salespersonid])
  REFERENCES [Sales].[SalesPerson]([Businessentityid])
go

ALTER TABLE [Sales].[SalesOrderHeader]
  ADD CONSTRAINT FK_SalesOrderHeader_ShipMethod_ShipMethodID FOREIGN KEY([Shipmethodid])
  REFERENCES [Purchasing].[ShipMethod]([Shipmethodid])
go

ALTER TABLE [Sales].[SalesOrderHeader]
  ADD CONSTRAINT FK_SalesOrderHeader_SalesTerritory_TerritoryID FOREIGN KEY([Territoryid])
  REFERENCES [Sales].[SalesTerritory]([Territoryid])
go

ALTER TABLE [Sales].[SalesOrderHeaderSalesReason]
  ADD CONSTRAINT FK_SalesOrderHeaderSalesReason_SalesReason_SalesReasonID FOREIGN KEY([Salesreasonid])
  REFERENCES [Sales].[SalesReason]([Salesreasonid])
go

ALTER TABLE [Sales].[SalesOrderHeaderSalesReason]
  ADD CONSTRAINT FK_SalesOrderHeaderSalesReason_SalesOrderHeader_SalesOrderID FOREIGN KEY([Salesorderid])
  REFERENCES [Sales].[SalesOrderHeader]([Salesorderid])
go

ALTER TABLE [Sales].[SalesPerson]
  ADD CONSTRAINT FK_SalesPerson_Employee_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [HumanResources].[Employee]([Businessentityid])
go

ALTER TABLE [Sales].[SalesPerson]
  ADD CONSTRAINT FK_SalesPerson_SalesTerritory_TerritoryID FOREIGN KEY([Territoryid])
  REFERENCES [Sales].[SalesTerritory]([Territoryid])
go

ALTER TABLE [Sales].[SalesPersonQuotaHistory]
  ADD CONSTRAINT FK_SalesPersonQuotaHistory_SalesPerson_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Sales].[SalesPerson]([Businessentityid])
go

ALTER TABLE [Sales].[SalesTaxRate]
  ADD CONSTRAINT FK_SalesTaxRate_StateProvince_StateProvinceID FOREIGN KEY([Stateprovinceid])
  REFERENCES [Person].[StateProvince]([Stateprovinceid])
go

ALTER TABLE [Sales].[SalesTerritory]
  ADD CONSTRAINT FK_SalesTerritory_CountryRegion_CountryRegionCode FOREIGN KEY([Countryregioncode])
  REFERENCES [Person].[CountryRegion]([Countryregioncode])
go

ALTER TABLE [Sales].[SalesTerritoryHistory]
  ADD CONSTRAINT FK_SalesTerritoryHistory_SalesPerson_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Sales].[SalesPerson]([Businessentityid])
go

ALTER TABLE [Sales].[SalesTerritoryHistory]
  ADD CONSTRAINT FK_SalesTerritoryHistory_SalesTerritory_TerritoryID FOREIGN KEY([Territoryid])
  REFERENCES [Sales].[SalesTerritory]([Territoryid])
go

ALTER TABLE [Sales].[ShoppingCartItem]
  ADD CONSTRAINT FK_ShoppingCartItem_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Sales].[SpecialOfferProduct]
  ADD CONSTRAINT FK_SpecialOfferProduct_Product_ProductID FOREIGN KEY([Productid])
  REFERENCES [Production].[Product]([Productid])
go

ALTER TABLE [Sales].[SpecialOfferProduct]
  ADD CONSTRAINT FK_SpecialOfferProduct_SpecialOffer_SpecialOfferID FOREIGN KEY([Specialofferid])
  REFERENCES [Sales].[SpecialOffer]([Specialofferid])
go

ALTER TABLE [Sales].[Store]
  ADD CONSTRAINT FK_Store_BusinessEntity_BusinessEntityID FOREIGN KEY([Businessentityid])
  REFERENCES [Person].[BusinessEntity]([Businessentityid])
go

ALTER TABLE [Sales].[Store]
  ADD CONSTRAINT FK_Store_SalesPerson_SalesPersonID FOREIGN KEY([Salespersonid])
  REFERENCES [Sales].[SalesPerson]([Businessentityid])
go

