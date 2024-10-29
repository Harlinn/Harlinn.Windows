--   Copyright 2024 Espen Harlinn
--
--   Licensed under the Apache License, Version 2.0 (the "License");
--   you may not use this file except in compliance with the License.
--   You may obtain a copy of the License at
--
--       http://www.apache.org/licenses/LICENSE-2.0
--
--   Unless required by applicable law or agreed to in writing, software
--   distributed under the License is distributed on an "AS IS" BASIS,
--   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
--   See the License for the specific language governing permissions and
--   limitations under the License.


CREATE TABLE SimpleTest1
(
Id NUMBER(19) NOT NULL,
OptimisticLock NUMBER(19) DEFAULT 0 NOT NULL,
Name NVARCHAR2(128) NOT NULL,
Description NVARCHAR2(1024),
CONSTRAINT PK_SimpleTest1 PRIMARY KEY(Id),
CONSTRAINT UNQ_SimpleTest1 UNIQUE(Name)
);

CREATE SEQUENCE SimpleTest1Seq;


CREATE TABLE OwnedObjectType
(
Id RAW(16) NOT NULL,
Name NVARCHAR2(128) NOT NULL,
OptimisticLock INTEGER DEFAULT 0 NOT NULL,
Created TIMESTAMP(9) NOT NULL,
Deleted TIMESTAMP(9),
Description CLOB,
CONSTRAINT PK_OwnedObjectType PRIMARY KEY(Id),
CONSTRAINT UNQ_OwnedObjectTypeName UNIQUE(Name)
);

INSERT INTO OwnedObjectType(Id, Name, OptimisticLock, Created, Description ) VALUES(SYS_GUID(),'Type123',0,SYSTIMESTAMP,'Type123 Description');


CREATE TABLE OwnedObject
(
Id RAW(16) NOT NULL,
Tp RAW(16) NOT NULL,
Owner RAW(16),
Name NVARCHAR2(128) NOT NULL,
OptimisticLock INTEGER DEFAULT 0 NOT NULL, 
Created TIMESTAMP(9) NOT NULL,
Deleted TIMESTAMP(9),
Description CLOB,
Data BLOB,
CONSTRAINT PK_OwnedObject PRIMARY KEY(Id),
CONSTRAINT UNQ_OwnerName UNIQUE(Owner,Name),
CONSTRAINT FK_OwnedObjectType FOREIGN KEY(Tp) REFERENCES OwnedObjectType(Id) ON DELETE CASCADE
);

ALTER TABLE OwnedObject
ADD CONSTRAINT FK_OwnedObjectOwner FOREIGN KEY(Owner) REFERENCES OwnedObject(Id) ON DELETE CASCADE;

CREATE TABLE TimeseriesSegment
(
	Id RAW(16) NOT NULL,
	FirstTimestamp TIMESTAMP(9) NOT NULL,
	OptimisticLock INTEGER DEFAULT 0 NOT NULL, 
	Data BLOB NOT NULL,
	CONSTRAINT PK_TimeseriesSegment PRIMARY KEY(Id,FirstTimestamp),
	CONSTRAINT FK_OwnedObject FOREIGN KEY(Id) REFERENCES OwnedObject(Id) ON DELETE CASCADE
) ORGANIZATION INDEX;

CREATE TABLE TimeseriesValue
(
	Id RAW(16) NOT NULL,
	Ts TIMESTAMP(9) NOT NULL,
	Flags INTEGER NOT NULL,
	Val BINARY_DOUBLE NOT NULL,
	CONSTRAINT PK_TSV PRIMARY KEY(Id,Ts),
	CONSTRAINT FK_TSVOwnedObject FOREIGN KEY(Id) REFERENCES OwnedObject(Id) ON DELETE CASCADE
);

CREATE TABLE TimeseriesValue1
(
Id NUMBER(19) NOT NULL,
Ts TIMESTAMP(9) NOT NULL,
Flags NUMBER(19) NOT NULL,
Val BINARY_DOUBLE NOT NULL,
CONSTRAINT PK_TSV1 PRIMARY KEY(Id,Ts)
) ORGANIZATION INDEX;


CREATE TABLE TimeseriesValue2
(
	Id NUMBER(19) NOT NULL,
	Ts NUMBER(19) NOT NULL,
	Flags NUMBER(19) NOT NULL,
	Val BINARY_DOUBLE NOT NULL,
	CONSTRAINT PK_TSV2 PRIMARY KEY(Id,Ts)
) ORGANIZATION INDEX;


--DROP TABLE TimeseriesSegment;
--DROP TABLE OwnedObject;
--DROP TABLE OwnedObjectType;
