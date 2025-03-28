/*
   Copyright 2024 Espen Harlinn

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

CREATE TABLE dbo.TimeseriesValue1
(
	Id bigint NOT NULL,
	Ts datetime2(7) NOT NULL,
	Flags int NOT NULL,
	val double precision NOT NULL,
	CONSTRAINT PK_TSV1 PRIMARY KEY(ID,Ts)
); 
go 

INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 1, '2021-01-01 00:00:01.0000001', 0, 1.0 )
go
INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 1, '2021-01-01 00:00:02.0000001', 0, 2.0 )
go
INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 1, '2021-01-01 00:00:03.0000001', 0, 3.0 )
go

INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 2, '2021-01-01 00:00:01.0000002', 0, 1.0 )
go
INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 2, '2021-01-01 00:00:02.0000002', 0, 2.0 )
go
INSERT INTO dbo.TimeseriesValue1( Id, Ts, Flags, val ) VALUES( 2, '2021-01-01 00:00:03.0000002', 0, 3.0 )
go


CREATE TABLE dbo.TimeseriesValue2
(
	Id bigint NOT NULL,
	Ts bigint NOT NULL,
	Flags int NOT NULL,
	val double precision NOT NULL,
	CONSTRAINT PK_TSV2 PRIMARY KEY(ID,Ts)
); 
go 


CREATE TABLE [dbo].[Track]
(
	[Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
	[OptimisticLockField] [int] NOT NULL,
	[Tracker] [uniqueidentifier] NOT NULL,
	[TrackNumber] [bigint] NOT NULL,
	[Timestamp] [bigint] NOT NULL,
    CONSTRAINT [PK_Track] PRIMARY KEY([Id] ),
	CONSTRAINT [UNQ_Track_TrackNumber_Timestamp] UNIQUE ([Tracker],[TrackNumber],[Timestamp])
 );
go

CREATE TABLE [dbo].[TrackValues]
(
	[Id] [uniqueidentifier] ROWGUIDCOL NOT NULL,
	[OptimisticLockField] [int] NOT NULL,
	[Track] [uniqueidentifier] NOT NULL,
	[Timestamp] [bigint] NOT NULL,
	[Flags] [int] NOT NULL,
	[Status] [int] NOT NULL,
	[Latitude] [float] NOT NULL,
	[Longitude] [float] NOT NULL,
	[Speed] [float] NOT NULL,
	[Course] [float] NOT NULL,
	[Heading] [float] NOT NULL,
	CONSTRAINT [PK_dbo.TrackValues] PRIMARY KEY ( [Id] ),
	CONSTRAINT [UNQ_TrackValue_Track_Timestamp] UNIQUE ([Track],[Timestamp]),
	CONSTRAINT [FK_TrackValue_Track] FOREIGN KEY([Track]) REFERENCES [dbo].[Track] ([Id])
);
GO

CREATE OR ALTER VIEW TrackViewEx
AS
  SELECT 
     t1.[Id]
    ,t1.[OptimisticLockField]
    ,t1.[Tracker]
    ,t1.[TrackNumber]
    ,ISNULL((SELECT MAX( tv.[Timestamp] ) FROM [dbo].[TrackValues] tv WHERE tv.Track = t1.Id ), t1.[Timestamp]) As [Timestamp]
FROM [dbo].[Track] t1
GO 

CREATE TABLE [dbo].TestTable1
(
	Id bigint NOT NULL Primary key,
	BitValue bit,
	TinyIntValue tinyint,
	SmallIntValue smallint,
	IntValue int,
	BigIntValue bigint,
	DecimalValue decimal(38,4),
	NumericValue numeric(18,6),
	RealValue real,
	FloatValue float,
	SmallMoneyValue smallmoney,
	MoneyValue money,
	DateValue date,
	DateTimeValue datetime,
	DateTime2Value datetime2,
	DateTimeOffsetValue datetimeoffset,
	SmallDateTimeValue smalldatetime,
	TimeValue time,
	UniqueidentifierValue uniqueidentifier,
	RowVersionValue	rowversion,
	BinaryValue binary(4),
	VarBinaryValue varbinary(max),
	CharValue char(4),
	VarCharValue varchar(max),
	NCharValue nchar(4),
	NVarCharValue nvarchar(max),
	TextValue text,
	NTextValue ntext,
	ImageValue image
);
go

INSERT INTO [dbo].TestTable1 VALUES (
1,1,1,1,1,1,1,1,1,1,
1,1,
DATEFROMPARTS(2024,2,25),
DATETIMEFROMPARTS(2024,2,25,12,01,01,555),
DATETIME2FROMPARTS ( 2011, 8, 15, 14, 23, 44, 500, 3 ),
DATETIMEOFFSETFROMPARTS ( 2011, 8, 15, 14, 30, 00, 500, 12, 30, 3 ),
SMALLDATETIMEFROMPARTS ( 2010, 12, 31, 23, 59 ),
TIMEFROMPARTS ( 23, 59, 59, 0, 0 ),
CONVERT(uniqueidentifier,N'0E984725-C51C-4BF4-9960-E1C80E27ABA0'),
DEFAULT,
CONVERT(binary(4),'0x0F0F0F0F',1),
CONVERT(varbinary(max),'0x0FFFFFFF0FFFFFFF',1),
'abcd',
'abcdef',
N'abcd',
N'abcdef',
'Text',
N'NText',
CONVERT(image,'0x0FFFFFFF0FFFFFFF0FFFFFFF0FFFFFFF',1)
);
go

CREATE TABLE [dbo].TestTable2
(
	Id bigint NOT NULL Primary key,
	BitValue bit NOT NULL,
	TinyIntValue tinyint NOT NULL,
	SmallIntValue smallint NOT NULL,
	IntValue int NOT NULL,
	BigIntValue bigint NOT NULL,
	DecimalValue decimal(38,4) NOT NULL,
	NumericValue numeric(18,6) NOT NULL,
	RealValue real NOT NULL,
	FloatValue float NOT NULL,
	SmallMoneyValue smallmoney NOT NULL,
	MoneyValue money NOT NULL,
	DateValue date NOT NULL,
	DateTimeValue datetime NOT NULL,
	DateTime2Value datetime2 NOT NULL,
	DateTimeOffsetValue datetimeoffset NOT NULL,
	SmallDateTimeValue smalldatetime NOT NULL,
	TimeValue time NOT NULL,
	UniqueidentifierValue uniqueidentifier NOT NULL,
	RowVersionValue	rowversion NOT NULL,
	BinaryValue binary(4) NOT NULL,
	VarBinaryValue varbinary(max) NOT NULL,
	CharValue char(4) NOT NULL,
	VarCharValue varchar(max) NOT NULL,
	NCharValue nchar(4) NOT NULL,
	NVarCharValue nvarchar(max) NOT NULL,
	TextValue text NOT NULL,
	NTextValue ntext NOT NULL,
	ImageValue image NOT NULL
);
go

INSERT INTO [dbo].TestTable2 VALUES (
1,1,1,1,1,1,1,1,1,1,
1,1,
DATEFROMPARTS(2024,2,25),
DATETIMEFROMPARTS(2024,2,25,12,01,01,555),
DATETIME2FROMPARTS ( 2011, 8, 15, 14, 23, 44, 500, 3 ),
DATETIMEOFFSETFROMPARTS ( 2011, 8, 15, 14, 30, 00, 500, 12, 30, 3 ),
SMALLDATETIMEFROMPARTS ( 2010, 12, 31, 23, 59 ),
TIMEFROMPARTS ( 23, 59, 59, 0, 0 ),
CONVERT(uniqueidentifier,N'0E984725-C51C-4BF4-9960-E1C80E27ABA0'),
DEFAULT,
CONVERT(binary(4),'0x0F0F0F0F',1),
CONVERT(varbinary(max),'0x0FFFFFFF0FFFFFFF',1),
'abcd',
'abcdef',
N'abcd',
N'abcdef',
'Text',
N'NText',
CONVERT(image,'0x0FFFFFFF0FFFFFFF0FFFFFFF0FFFFFFF',1)
);
go



CREATE TABLE Persons
(
    Id int IDENTITY(1,1) PRIMARY KEY,
    LastName nvarchar(255) NOT NULL,
    FirstName nvarchar(255) NOT NULL,
	MiddleName nvarchar(255)
);
go

INSERT INTO Persons(LastName, FirstName) VALUES(N'John',N'Smith');
go


CREATE SCHEMA TestSchema;
go

CREATE TABLE TestSchema.TestTable3
(
	Id bigint NOT NULL Primary key,
	BitValue bit NOT NULL,
);
go

CREATE FUNCTION TestFunction1(@a INT, @b INT)
RETURNS INT
WITH EXECUTE AS CALLER
AS
BEGIN
	RETURN @a+@b;
END;
go

CREATE TABLE TestSchema.TestTable4
(
	Id bigint NOT NULL Primary key,
	[Value] varchar(max)
);
go


CREATE TABLE TestSchema.TestTable5
(
	Id bigint NOT NULL Primary key,
	[Value] nvarchar(max)
);
go

CREATE TABLE TestSchema.TestTable6
(
	Id bigint NOT NULL Primary key,
	[Value] varbinary(max)
);
go


