
IF NOT EXISTS (SELECT * FROM sys.schemas WHERE name = 'Test1')
BEGIN
    EXEC('CREATE SCHEMA [Test1]');
END
go

IF NOT EXISTS (SELECT * FROM sys.schemas WHERE name = 'Test2')
BEGIN
    EXEC('CREATE SCHEMA [Test2]');
END
go


CREATE TABLE [Test1].[SimpleTable1]
(
    Id bigint NOT NULL,
    FirstName nvarchar(255) NOT NULL,
    MiddleName nvarchar(255) NULL,
    LastName nvarchar(255) NOT NULL,
    ExternalId nvarchar(20) NOT NULL,
    CONSTRAINT [PkTest1SimpleTable1Id] PRIMARY KEY(Id)
);

CREATE INDEX [IdxTest1SimpleTable1] ON [Test1].[SimpleTable1]([LastName],[FirstName],[MiddleName])
go

ALTER TABLE [Test1].[SimpleTable1]
  ADD CONSTRAINT [IdxTest1SimpleTable1ExternalId] UNIQUE([ExternalId])
go


CREATE TABLE [Test1].[Table1]
(
    Id bigint NOT NULL,
    BooleanValue bit NULL,
    TinyIntValue tinyint NULL,
    SmallIntValue smallint NULL,
    IntValue int NULL,
    BigIntValue bigint NULL,
    DecimalValue decimal(18, 2) NULL,
    SingleValue real NULL,
    DoubleValue float NULL,
    DateTimeValue datetime2 NULL,
    GuidValue uniqueidentifier NULL,
    CharValue char(10) NULL,
    VarCharValue varchar(100) NULL,
    NCharValue nchar(10) NULL,
    NVarCharValue nvarchar(100) NULL,
    NVarCharMaxValue nvarchar(max) NULL,
    BinaryValue binary(10) NULL,
    VarBinaryValue varbinary(100) NULL,
    VarBinaryMaxValue varbinary(max) NULL,
    CONSTRAINT [PK_Test1_Table1_Id] PRIMARY KEY(Id)
);

