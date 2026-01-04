/*
 * [dbo].[AwbuildversionTableType]
 */
CREATE TYPE [dbo].[AwbuildversionTableType] AS TABLE
(
    [Systeminformationid] [tinyint] NOT NULL,
    [Database Version] [nvarchar](25) NOT NULL,
    [Versiondate] [datetime] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Systeminformationid]),
    INDEX idxPrimary NONCLUSTERED([Systeminformationid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [dbo].[DatabaselogTableType]
 */
CREATE TYPE [dbo].[DatabaselogTableType] AS TABLE
(
    [Databaselogid] [int] NOT NULL,
    [Posttime] [datetime] NOT NULL,
    [Databaseuser] [nvarchar](128) NOT NULL,
    [Event] [nvarchar](128) NOT NULL,
    [Schema] [nvarchar](128) NULL,
    [Object] [nvarchar](128) NULL,
    [Tsql] [nvarchar](max) NOT NULL,
    [Xmlevent] [xml] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Databaselogid]),
    INDEX idxPrimary NONCLUSTERED([Databaselogid])
)
go


/*
 * [dbo].[ErrorlogTableType]
 */
CREATE TYPE [dbo].[ErrorlogTableType] AS TABLE
(
    [Errorlogid] [int] NOT NULL,
    [Errortime] [datetime] NOT NULL,
    [Username] [nvarchar](128) NOT NULL,
    [Errornumber] [int] NOT NULL,
    [Errorseverity] [int] NULL,
    [Errorstate] [int] NULL,
    [Errorprocedure] [nvarchar](126) NULL,
    [Errorline] [int] NULL,
    [Errormessage] [nvarchar](4000) NOT NULL,
    PRIMARY KEY NONCLUSTERED([Errorlogid]),
    INDEX idxPrimary NONCLUSTERED([Errorlogid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [HumanResources].[DepartmentTableType]
 */
CREATE TYPE [HumanResources].[DepartmentTableType] AS TABLE
(
    [Departmentid] [smallint] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Groupname] [nvarchar](50) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Departmentid]),
    INDEX idxPrimary NONCLUSTERED([Departmentid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [HumanResources].[EmployeeTableType]
 */
CREATE TYPE [HumanResources].[EmployeeTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Nationalidnumber] [nvarchar](15) NOT NULL,
    [Loginid] [nvarchar](256) NOT NULL,
    [Organizationnode] [hierarchyid] NULL,
    [Jobtitle] [nvarchar](50) NOT NULL,
    [Birthdate] [date] NOT NULL,
    [Maritalstatus] [nvarchar](1) NOT NULL,
    [Gender] [nvarchar](1) NOT NULL,
    [Hiredate] [date] NOT NULL,
    [Salariedflag] [Flag] NOT NULL,
    [Vacationhours] [smallint] NOT NULL,
    [Sickleavehours] [smallint] NOT NULL,
    [Currentflag] [Flag] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid])
)
go


/*
 * [HumanResources].[EmployeedepartmenthistoryTableType]
 */
CREATE TYPE [HumanResources].[EmployeedepartmenthistoryTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Departmentid] [smallint] NOT NULL,
    [Shiftid] [tinyint] NOT NULL,
    [Startdate] [date] NOT NULL,
    [Enddate] [date] NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid], [Startdate], [Departmentid], [Shiftid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid], [Startdate], [Departmentid], [Shiftid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [HumanResources].[EmployeepayhistoryTableType]
 */
CREATE TYPE [HumanResources].[EmployeepayhistoryTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Ratechangedate] [datetime] NOT NULL,
    [Rate] [money] NOT NULL,
    [Payfrequency] [tinyint] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid], [Ratechangedate]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid], [Ratechangedate])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [HumanResources].[JobcandidateTableType]
 */
CREATE TYPE [HumanResources].[JobcandidateTableType] AS TABLE
(
    [Jobcandidateid] [int] NOT NULL,
    [Businessentityid] [int] NULL,
    [Resume] [xml] NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Jobcandidateid]),
    INDEX idxPrimary NONCLUSTERED([Jobcandidateid])
)
go


/*
 * [HumanResources].[ShiftTableType]
 */
CREATE TYPE [HumanResources].[ShiftTableType] AS TABLE
(
    [Shiftid] [tinyint] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Starttime] [time] NOT NULL,
    [Endtime] [time] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Shiftid]),
    INDEX idxPrimary NONCLUSTERED([Shiftid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Person].[AddressTableType]
 */
CREATE TYPE [Person].[AddressTableType] AS TABLE
(
    [Addressid] [int] NOT NULL,
    [Addressline1] [nvarchar](60) NOT NULL,
    [Addressline2] [nvarchar](60) NULL,
    [City] [nvarchar](30) NOT NULL,
    [Stateprovinceid] [int] NOT NULL,
    [Postalcode] [nvarchar](15) NOT NULL,
    [Spatiallocation] [geography] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Addressid]),
    INDEX idxPrimary NONCLUSTERED([Addressid])
)
go


/*
 * [Person].[AddresstypeTableType]
 */
CREATE TYPE [Person].[AddresstypeTableType] AS TABLE
(
    [Addresstypeid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Addresstypeid]),
    INDEX idxPrimary NONCLUSTERED([Addresstypeid])
)
go


/*
 * [Person].[BusinessentityTableType]
 */
CREATE TYPE [Person].[BusinessentityTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid])
)
go


/*
 * [Person].[BusinessentityaddressTableType]
 */
CREATE TYPE [Person].[BusinessentityaddressTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Addressid] [int] NOT NULL,
    [Addresstypeid] [int] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid], [Addressid], [Addresstypeid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid], [Addressid], [Addresstypeid])
)
go


/*
 * [Person].[BusinessentitycontactTableType]
 */
CREATE TYPE [Person].[BusinessentitycontactTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Personid] [int] NOT NULL,
    [Contacttypeid] [int] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid], [Personid], [Contacttypeid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid], [Personid], [Contacttypeid])
)
go


/*
 * [Person].[ContacttypeTableType]
 */
CREATE TYPE [Person].[ContacttypeTableType] AS TABLE
(
    [Contacttypeid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Contacttypeid]),
    INDEX idxPrimary NONCLUSTERED([Contacttypeid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Person].[CountryregionTableType]
 */
CREATE TYPE [Person].[CountryregionTableType] AS TABLE
(
    [Countryregioncode] [nvarchar](3) NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Countryregioncode]),
    INDEX idxPrimary NONCLUSTERED([Countryregioncode])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Person].[EmailaddressTableType]
 */
CREATE TYPE [Person].[EmailaddressTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Emailaddressid] [int] NOT NULL,
    [Emailaddress] [nvarchar](50) NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid], [Emailaddressid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid], [Emailaddressid])
)
go


/*
 * [Person].[PasswordTableType]
 */
CREATE TYPE [Person].[PasswordTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Passwordhash] [nvarchar](128) NOT NULL,
    [Passwordsalt] [nvarchar](10) NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid])
)
go


/*
 * [Person].[PersonTableType]
 */
CREATE TYPE [Person].[PersonTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Persontype] [nvarchar](2) NOT NULL,
    [Namestyle] [NameStyle] NOT NULL,
    [Title] [nvarchar](8) NULL,
    [Firstname] [nvarchar](50) NOT NULL,
    [Middlename] [nvarchar](50) NULL,
    [Lastname] [nvarchar](50) NOT NULL,
    [Suffix] [nvarchar](10) NULL,
    [Emailpromotion] [int] NOT NULL,
    [Additionalcontactinfo] [xml] NULL,
    [Demographics] [xml] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid])
)
go


/*
 * [Person].[PersonphoneTableType]
 */
CREATE TYPE [Person].[PersonphoneTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Phonenumber] [nvarchar](25) NOT NULL,
    [Phonenumbertypeid] [int] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid], [Phonenumber], [Phonenumbertypeid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid], [Phonenumber], [Phonenumbertypeid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Person].[PhonenumbertypeTableType]
 */
CREATE TYPE [Person].[PhonenumbertypeTableType] AS TABLE
(
    [Phonenumbertypeid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Phonenumbertypeid]),
    INDEX idxPrimary NONCLUSTERED([Phonenumbertypeid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Person].[StateprovinceTableType]
 */
CREATE TYPE [Person].[StateprovinceTableType] AS TABLE
(
    [Stateprovinceid] [int] NOT NULL,
    [Stateprovincecode] [nvarchar](3) NOT NULL,
    [Countryregioncode] [nvarchar](3) NOT NULL,
    [Isonlystateprovinceflag] [Flag] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Territoryid] [int] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Stateprovinceid]),
    INDEX idxPrimary NONCLUSTERED([Stateprovinceid])
)
go


/*
 * [Production].[BillofmaterialsTableType]
 */
CREATE TYPE [Production].[BillofmaterialsTableType] AS TABLE
(
    [Billofmaterialsid] [int] NOT NULL,
    [Productassemblyid] [int] NULL,
    [Componentid] [int] NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NULL,
    [Unitmeasurecode] [nvarchar](3) NOT NULL,
    [Bomlevel] [smallint] NOT NULL,
    [Perassemblyqty] [decimal] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Billofmaterialsid]),
    INDEX idxPrimary NONCLUSTERED([Billofmaterialsid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[CultureTableType]
 */
CREATE TYPE [Production].[CultureTableType] AS TABLE
(
    [Cultureid] [nvarchar](6) NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Cultureid]),
    INDEX idxPrimary NONCLUSTERED([Cultureid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[DocumentTableType]
 */
CREATE TYPE [Production].[DocumentTableType] AS TABLE
(
    [Documentnode] [hierarchyid] NOT NULL,
    [Title] [nvarchar](50) NOT NULL,
    [Owner] [int] NOT NULL,
    [Folderflag] [bit] NOT NULL,
    [Filename] [nvarchar](400) NOT NULL,
    [Fileextension] [nvarchar](8) NOT NULL,
    [Revision] [nvarchar](5) NOT NULL,
    [Changenumber] [int] NOT NULL,
    [Status] [tinyint] NOT NULL,
    [Documentsummary] [nvarchar](max) NULL,
    [Document] [varbinary](max) NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Documentnode]),
    INDEX idxPrimary NONCLUSTERED([Documentnode])
)
go


/*
 * [Production].[IllustrationTableType]
 */
CREATE TYPE [Production].[IllustrationTableType] AS TABLE
(
    [Illustrationid] [int] NOT NULL,
    [Diagram] [xml] NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Illustrationid]),
    INDEX idxPrimary NONCLUSTERED([Illustrationid])
)
go


/*
 * [Production].[LocationTableType]
 */
CREATE TYPE [Production].[LocationTableType] AS TABLE
(
    [Locationid] [smallint] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Costrate] [smallmoney] NOT NULL,
    [Availability] [decimal] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Locationid]),
    INDEX idxPrimary NONCLUSTERED([Locationid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[ProductTableType]
 */
CREATE TYPE [Production].[ProductTableType] AS TABLE
(
    [Productid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Productnumber] [nvarchar](25) NOT NULL,
    [Makeflag] [Flag] NOT NULL,
    [Finishedgoodsflag] [Flag] NOT NULL,
    [Color] [nvarchar](15) NULL,
    [Safetystocklevel] [smallint] NOT NULL,
    [Reorderpoint] [smallint] NOT NULL,
    [Standardcost] [money] NOT NULL,
    [Listprice] [money] NOT NULL,
    [Size] [nvarchar](5) NULL,
    [Sizeunitmeasurecode] [nvarchar](3) NULL,
    [Weightunitmeasurecode] [nvarchar](3) NULL,
    [Weight] [decimal] NULL,
    [Daystomanufacture] [int] NOT NULL,
    [Productline] [nvarchar](2) NULL,
    [Class] [nvarchar](2) NULL,
    [Style] [nvarchar](2) NULL,
    [Productsubcategoryid] [int] NULL,
    [Productmodelid] [int] NULL,
    [Sellstartdate] [datetime] NOT NULL,
    [Sellenddate] [datetime] NULL,
    [Discontinueddate] [datetime] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productid]),
    INDEX idxPrimary NONCLUSTERED([Productid])
)
go


/*
 * [Production].[ProductcategoryTableType]
 */
CREATE TYPE [Production].[ProductcategoryTableType] AS TABLE
(
    [Productcategoryid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productcategoryid]),
    INDEX idxPrimary NONCLUSTERED([Productcategoryid])
)
go


/*
 * [Production].[ProductcosthistoryTableType]
 */
CREATE TYPE [Production].[ProductcosthistoryTableType] AS TABLE
(
    [Productid] [int] NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NULL,
    [Standardcost] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productid], [Startdate]),
    INDEX idxPrimary NONCLUSTERED([Productid], [Startdate])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[ProductdescriptionTableType]
 */
CREATE TYPE [Production].[ProductdescriptionTableType] AS TABLE
(
    [Productdescriptionid] [int] NOT NULL,
    [Description] [nvarchar](400) NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productdescriptionid]),
    INDEX idxPrimary NONCLUSTERED([Productdescriptionid])
)
go


/*
 * [Production].[ProductdocumentTableType]
 */
CREATE TYPE [Production].[ProductdocumentTableType] AS TABLE
(
    [Productid] [int] NOT NULL,
    [Documentnode] [hierarchyid] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productid], [Documentnode]),
    INDEX idxPrimary NONCLUSTERED([Productid], [Documentnode])
)
go


/*
 * [Production].[ProductinventoryTableType]
 */
CREATE TYPE [Production].[ProductinventoryTableType] AS TABLE
(
    [Productid] [int] NOT NULL,
    [Locationid] [smallint] NOT NULL,
    [Shelf] [nvarchar](10) NOT NULL,
    [Bin] [tinyint] NOT NULL,
    [Quantity] [smallint] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productid], [Locationid]),
    INDEX idxPrimary NONCLUSTERED([Productid], [Locationid])
)
go


/*
 * [Production].[ProductlistpricehistoryTableType]
 */
CREATE TYPE [Production].[ProductlistpricehistoryTableType] AS TABLE
(
    [Productid] [int] NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NULL,
    [Listprice] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productid], [Startdate]),
    INDEX idxPrimary NONCLUSTERED([Productid], [Startdate])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[ProductmodelTableType]
 */
CREATE TYPE [Production].[ProductmodelTableType] AS TABLE
(
    [Productmodelid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Catalogdescription] [xml] NULL,
    [Instructions] [xml] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productmodelid]),
    INDEX idxPrimary NONCLUSTERED([Productmodelid])
)
go


/*
 * [Production].[ProductmodelillustrationTableType]
 */
CREATE TYPE [Production].[ProductmodelillustrationTableType] AS TABLE
(
    [Productmodelid] [int] NOT NULL,
    [Illustrationid] [int] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productmodelid], [Illustrationid]),
    INDEX idxPrimary NONCLUSTERED([Productmodelid], [Illustrationid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[ProductmodelproductdescriptioncultureTableType]
 */
CREATE TYPE [Production].[ProductmodelproductdescriptioncultureTableType] AS TABLE
(
    [Productmodelid] [int] NOT NULL,
    [Productdescriptionid] [int] NOT NULL,
    [Cultureid] [nvarchar](6) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productmodelid], [Productdescriptionid], [Cultureid]),
    INDEX idxPrimary NONCLUSTERED([Productmodelid], [Productdescriptionid], [Cultureid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[ProductphotoTableType]
 */
CREATE TYPE [Production].[ProductphotoTableType] AS TABLE
(
    [Productphotoid] [int] NOT NULL,
    [Thumbnailphoto] [varbinary](max) NULL,
    [Thumbnailphotofilename] [nvarchar](50) NULL,
    [Largephoto] [varbinary](max) NULL,
    [Largephotofilename] [nvarchar](50) NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productphotoid]),
    INDEX idxPrimary NONCLUSTERED([Productphotoid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[ProductproductphotoTableType]
 */
CREATE TYPE [Production].[ProductproductphotoTableType] AS TABLE
(
    [Productid] [int] NOT NULL,
    [Productphotoid] [int] NOT NULL,
    [Primary] [bit] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productid], [Productphotoid]),
    INDEX idxPrimary NONCLUSTERED([Productid], [Productphotoid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[ProductreviewTableType]
 */
CREATE TYPE [Production].[ProductreviewTableType] AS TABLE
(
    [Productreviewid] [int] NOT NULL,
    [Productid] [int] NOT NULL,
    [Reviewername] [nvarchar](50) NOT NULL,
    [Reviewdate] [datetime] NOT NULL,
    [Emailaddress] [nvarchar](50) NOT NULL,
    [Rating] [int] NOT NULL,
    [Comments] [nvarchar](3850) NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productreviewid]),
    INDEX idxPrimary NONCLUSTERED([Productreviewid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[ProductsubcategoryTableType]
 */
CREATE TYPE [Production].[ProductsubcategoryTableType] AS TABLE
(
    [Productsubcategoryid] [int] NOT NULL,
    [Productcategoryid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productsubcategoryid]),
    INDEX idxPrimary NONCLUSTERED([Productsubcategoryid])
)
go


/*
 * [Production].[ScrapreasonTableType]
 */
CREATE TYPE [Production].[ScrapreasonTableType] AS TABLE
(
    [Scrapreasonid] [smallint] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Scrapreasonid]),
    INDEX idxPrimary NONCLUSTERED([Scrapreasonid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[TransactionhistoryTableType]
 */
CREATE TYPE [Production].[TransactionhistoryTableType] AS TABLE
(
    [Transactionid] [int] NOT NULL,
    [Productid] [int] NOT NULL,
    [Referenceorderid] [int] NOT NULL,
    [Referenceorderlineid] [int] NOT NULL,
    [Transactiondate] [datetime] NOT NULL,
    [Transactiontype] [nvarchar](1) NOT NULL,
    [Quantity] [int] NOT NULL,
    [Actualcost] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Transactionid]),
    INDEX idxPrimary NONCLUSTERED([Transactionid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[TransactionhistoryarchiveTableType]
 */
CREATE TYPE [Production].[TransactionhistoryarchiveTableType] AS TABLE
(
    [Transactionid] [int] NOT NULL,
    [Productid] [int] NOT NULL,
    [Referenceorderid] [int] NOT NULL,
    [Referenceorderlineid] [int] NOT NULL,
    [Transactiondate] [datetime] NOT NULL,
    [Transactiontype] [nvarchar](1) NOT NULL,
    [Quantity] [int] NOT NULL,
    [Actualcost] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Transactionid]),
    INDEX idxPrimary NONCLUSTERED([Transactionid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[UnitmeasureTableType]
 */
CREATE TYPE [Production].[UnitmeasureTableType] AS TABLE
(
    [Unitmeasurecode] [nvarchar](3) NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Unitmeasurecode]),
    INDEX idxPrimary NONCLUSTERED([Unitmeasurecode])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[WorkorderTableType]
 */
CREATE TYPE [Production].[WorkorderTableType] AS TABLE
(
    [Workorderid] [int] NOT NULL,
    [Productid] [int] NOT NULL,
    [Orderqty] [int] NOT NULL,
    [Scrappedqty] [smallint] NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NULL,
    [Duedate] [datetime] NOT NULL,
    [Scrapreasonid] [smallint] NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Workorderid]),
    INDEX idxPrimary NONCLUSTERED([Workorderid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Production].[WorkorderroutingTableType]
 */
CREATE TYPE [Production].[WorkorderroutingTableType] AS TABLE
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
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Workorderid], [Productid], [Operationsequence]),
    INDEX idxPrimary NONCLUSTERED([Workorderid], [Productid], [Operationsequence])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Purchasing].[ProductvendorTableType]
 */
CREATE TYPE [Purchasing].[ProductvendorTableType] AS TABLE
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
    [Unitmeasurecode] [nvarchar](3) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Productid], [Businessentityid]),
    INDEX idxPrimary NONCLUSTERED([Productid], [Businessentityid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Purchasing].[PurchaseorderdetailTableType]
 */
CREATE TYPE [Purchasing].[PurchaseorderdetailTableType] AS TABLE
(
    [Purchaseorderid] [int] NOT NULL,
    [Purchaseorderdetailid] [int] NOT NULL,
    [Duedate] [datetime] NOT NULL,
    [Orderqty] [smallint] NOT NULL,
    [Productid] [int] NOT NULL,
    [Unitprice] [money] NOT NULL,
    [Receivedqty] [decimal] NOT NULL,
    [Rejectedqty] [decimal] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Purchaseorderid], [Purchaseorderdetailid]),
    INDEX idxPrimary NONCLUSTERED([Purchaseorderid], [Purchaseorderdetailid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Purchasing].[PurchaseorderheaderTableType]
 */
CREATE TYPE [Purchasing].[PurchaseorderheaderTableType] AS TABLE
(
    [Purchaseorderid] [int] NOT NULL,
    [Revisionnumber] [tinyint] NOT NULL,
    [Status] [tinyint] NOT NULL,
    [Employeeid] [int] NOT NULL,
    [Vendorid] [int] NOT NULL,
    [Shipmethodid] [int] NOT NULL,
    [Orderdate] [datetime] NOT NULL,
    [Shipdate] [datetime] NULL,
    [Subtotal] [money] NOT NULL,
    [Taxamt] [money] NOT NULL,
    [Freight] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Purchaseorderid]),
    INDEX idxPrimary NONCLUSTERED([Purchaseorderid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Purchasing].[ShipmethodTableType]
 */
CREATE TYPE [Purchasing].[ShipmethodTableType] AS TABLE
(
    [Shipmethodid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Shipbase] [money] NOT NULL,
    [Shiprate] [money] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Shipmethodid]),
    INDEX idxPrimary NONCLUSTERED([Shipmethodid])
)
go


/*
 * [Purchasing].[VendorTableType]
 */
CREATE TYPE [Purchasing].[VendorTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Accountnumber] [nvarchar](15) NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Creditrating] [tinyint] NOT NULL,
    [Preferredvendorstatus] [bit] NOT NULL,
    [Activeflag] [bit] NOT NULL,
    [Purchasingwebserviceurl] [nvarchar](1024) NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Sales].[CountryregioncurrencyTableType]
 */
CREATE TYPE [Sales].[CountryregioncurrencyTableType] AS TABLE
(
    [Countryregioncode] [nvarchar](3) NOT NULL,
    [Currencycode] [nvarchar](3) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Countryregioncode], [Currencycode]),
    INDEX idxPrimary NONCLUSTERED([Countryregioncode], [Currencycode])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Sales].[CreditcardTableType]
 */
CREATE TYPE [Sales].[CreditcardTableType] AS TABLE
(
    [Creditcardid] [int] NOT NULL,
    [Cardtype] [nvarchar](50) NOT NULL,
    [Cardnumber] [nvarchar](25) NOT NULL,
    [Expmonth] [tinyint] NOT NULL,
    [Expyear] [smallint] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Creditcardid]),
    INDEX idxPrimary NONCLUSTERED([Creditcardid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Sales].[CurrencyTableType]
 */
CREATE TYPE [Sales].[CurrencyTableType] AS TABLE
(
    [Currencycode] [nvarchar](3) NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Currencycode]),
    INDEX idxPrimary NONCLUSTERED([Currencycode])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Sales].[CurrencyrateTableType]
 */
CREATE TYPE [Sales].[CurrencyrateTableType] AS TABLE
(
    [Currencyrateid] [int] NOT NULL,
    [Currencyratedate] [datetime] NOT NULL,
    [Fromcurrencycode] [nvarchar](3) NOT NULL,
    [Tocurrencycode] [nvarchar](3) NOT NULL,
    [Averagerate] [money] NOT NULL,
    [Endofdayrate] [money] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Currencyrateid]),
    INDEX idxPrimary NONCLUSTERED([Currencyrateid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Sales].[CustomerTableType]
 */
CREATE TYPE [Sales].[CustomerTableType] AS TABLE
(
    [Customerid] [int] NOT NULL,
    [Personid] [int] NULL,
    [Storeid] [int] NULL,
    [Territoryid] [int] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Customerid]),
    INDEX idxPrimary NONCLUSTERED([Customerid])
)
go


/*
 * [Sales].[PersoncreditcardTableType]
 */
CREATE TYPE [Sales].[PersoncreditcardTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Creditcardid] [int] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid], [Creditcardid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid], [Creditcardid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Sales].[SalesorderdetailTableType]
 */
CREATE TYPE [Sales].[SalesorderdetailTableType] AS TABLE
(
    [Salesorderid] [int] NOT NULL,
    [Salesorderdetailid] [int] NOT NULL,
    [Carriertrackingnumber] [nvarchar](25) NULL,
    [Orderqty] [smallint] NOT NULL,
    [Productid] [int] NOT NULL,
    [Specialofferid] [int] NOT NULL,
    [Unitprice] [money] NOT NULL,
    [Unitpricediscount] [money] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Salesorderid], [Salesorderdetailid]),
    INDEX idxPrimary NONCLUSTERED([Salesorderid], [Salesorderdetailid])
)
go


/*
 * [Sales].[SalesorderheaderTableType]
 */
CREATE TYPE [Sales].[SalesorderheaderTableType] AS TABLE
(
    [Salesorderid] [int] NOT NULL,
    [Revisionnumber] [tinyint] NOT NULL,
    [Orderdate] [datetime] NOT NULL,
    [Duedate] [datetime] NOT NULL,
    [Shipdate] [datetime] NULL,
    [Status] [tinyint] NOT NULL,
    [Onlineorderflag] [Flag] NOT NULL,
    [Purchaseordernumber] [nvarchar](25) NULL,
    [Accountnumber] [nvarchar](15) NULL,
    [Customerid] [int] NOT NULL,
    [Salespersonid] [int] NULL,
    [Territoryid] [int] NULL,
    [Billtoaddressid] [int] NOT NULL,
    [Shiptoaddressid] [int] NOT NULL,
    [Shipmethodid] [int] NOT NULL,
    [Creditcardid] [int] NULL,
    [Creditcardapprovalcode] [nvarchar](15) NULL,
    [Currencyrateid] [int] NULL,
    [Subtotal] [money] NOT NULL,
    [Taxamt] [money] NOT NULL,
    [Freight] [money] NOT NULL,
    [Comment] [nvarchar](128) NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Salesorderid]),
    INDEX idxPrimary NONCLUSTERED([Salesorderid])
)
go


/*
 * [Sales].[SalesorderheadersalesreasonTableType]
 */
CREATE TYPE [Sales].[SalesorderheadersalesreasonTableType] AS TABLE
(
    [Salesorderid] [int] NOT NULL,
    [Salesreasonid] [int] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Salesorderid], [Salesreasonid]),
    INDEX idxPrimary NONCLUSTERED([Salesorderid], [Salesreasonid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Sales].[SalespersonTableType]
 */
CREATE TYPE [Sales].[SalespersonTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Territoryid] [int] NULL,
    [Salesquota] [money] NULL,
    [Bonus] [money] NOT NULL,
    [Commissionpct] [smallmoney] NOT NULL,
    [Salesytd] [money] NOT NULL,
    [Saleslastyear] [money] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid])
)
go


/*
 * [Sales].[SalespersonquotahistoryTableType]
 */
CREATE TYPE [Sales].[SalespersonquotahistoryTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Quotadate] [datetime] NOT NULL,
    [Salesquota] [money] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid], [Quotadate]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid], [Quotadate])
)
go


/*
 * [Sales].[SalesreasonTableType]
 */
CREATE TYPE [Sales].[SalesreasonTableType] AS TABLE
(
    [Salesreasonid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Reasontype] [nvarchar](50) NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Salesreasonid]),
    INDEX idxPrimary NONCLUSTERED([Salesreasonid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Sales].[SalestaxrateTableType]
 */
CREATE TYPE [Sales].[SalestaxrateTableType] AS TABLE
(
    [Salestaxrateid] [int] NOT NULL,
    [Stateprovinceid] [int] NOT NULL,
    [Taxtype] [tinyint] NOT NULL,
    [Taxrate] [smallmoney] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Salestaxrateid]),
    INDEX idxPrimary NONCLUSTERED([Salestaxrateid])
)
go


/*
 * [Sales].[SalesterritoryTableType]
 */
CREATE TYPE [Sales].[SalesterritoryTableType] AS TABLE
(
    [Territoryid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Countryregioncode] [nvarchar](3) NOT NULL,
    [Group] [nvarchar](50) NOT NULL,
    [Salesytd] [money] NOT NULL,
    [Saleslastyear] [money] NOT NULL,
    [Costytd] [money] NOT NULL,
    [Costlastyear] [money] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Territoryid]),
    INDEX idxPrimary NONCLUSTERED([Territoryid])
)
go


/*
 * [Sales].[SalesterritoryhistoryTableType]
 */
CREATE TYPE [Sales].[SalesterritoryhistoryTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Territoryid] [int] NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid], [Startdate], [Territoryid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid], [Startdate], [Territoryid])
)
go


/*
 * [Sales].[ShoppingcartitemTableType]
 */
CREATE TYPE [Sales].[ShoppingcartitemTableType] AS TABLE
(
    [Shoppingcartitemid] [int] NOT NULL,
    [Shoppingcartid] [nvarchar](50) NOT NULL,
    [Quantity] [int] NOT NULL,
    [Productid] [int] NOT NULL,
    [Datecreated] [datetime] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Shoppingcartitemid]),
    INDEX idxPrimary NONCLUSTERED([Shoppingcartitemid])
)
WITH (MEMORY_OPTIMIZED = ON);
go


/*
 * [Sales].[SpecialofferTableType]
 */
CREATE TYPE [Sales].[SpecialofferTableType] AS TABLE
(
    [Specialofferid] [int] NOT NULL,
    [Description] [nvarchar](255) NOT NULL,
    [Discountpct] [smallmoney] NOT NULL,
    [Type] [nvarchar](50) NOT NULL,
    [Category] [nvarchar](50) NOT NULL,
    [Startdate] [datetime] NOT NULL,
    [Enddate] [datetime] NOT NULL,
    [Minqty] [int] NOT NULL,
    [Maxqty] [int] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Specialofferid]),
    INDEX idxPrimary NONCLUSTERED([Specialofferid])
)
go


/*
 * [Sales].[SpecialofferproductTableType]
 */
CREATE TYPE [Sales].[SpecialofferproductTableType] AS TABLE
(
    [Specialofferid] [int] NOT NULL,
    [Productid] [int] NOT NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Specialofferid], [Productid]),
    INDEX idxPrimary NONCLUSTERED([Specialofferid], [Productid])
)
go


/*
 * [Sales].[StoreTableType]
 */
CREATE TYPE [Sales].[StoreTableType] AS TABLE
(
    [Businessentityid] [int] NOT NULL,
    [Name] [nvarchar](50) NOT NULL,
    [Salespersonid] [int] NULL,
    [Demographics] [xml] NULL,
    [Rowguid] [uniqueidentifier] NOT NULL,
    [Modifieddate] [datetime] NOT NULL,
    PRIMARY KEY NONCLUSTERED([Businessentityid]),
    INDEX idxPrimary NONCLUSTERED([Businessentityid])
)
go


