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
using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Dbo.Types;

public class AwbuildversionDataType
{
    byte _systeminformationid = 0;
    string _databaseVersion = string.Empty;
    DateTime _versiondate;
    DateTime _modifieddate;

    public AwbuildversionDataType( )
    {
    }

    public AwbuildversionDataType(byte systeminformationid,
        string databaseVersion,
        DateTime versiondate,
        DateTime modifieddate)
    {
        _systeminformationid = systeminformationid;
        _databaseVersion = databaseVersion;
        _versiondate = versiondate;
        _modifieddate = modifieddate;
    }

    public byte Systeminformationid
    {
        get => _systeminformationid;
        set => _systeminformationid = value;
    }
    public string DatabaseVersion
    {
        get => _databaseVersion;
        set => _databaseVersion = value;
    }
    public DateTime Versiondate
    {
        get => _versiondate;
        set => _versiondate = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
