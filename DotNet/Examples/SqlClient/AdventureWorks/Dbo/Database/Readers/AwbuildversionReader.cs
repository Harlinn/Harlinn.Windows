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
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Dbo.Database.Readers;

public class AwbuildversionReader : IDisposable
{
    public const string QualifiedTableName = "[dbo].[AWBuildVersion]";
    public const string TableName = "AWBuildVersion";
    public const string ShortName = "a";
    public const string Sql = """
        SELECT
          a.[Systeminformationid],
          a.[Database Version],
          a.[Versiondate],
          a.[Modifieddate]
        FROM
          [dbo].[AWBuildVersion] a
        """;

    public const int SYSTEMINFORMATIONID_FIELD_ID = 0;
    public const int DATABASEVERSION_FIELD_ID = 1;
    public const int VERSIONDATE_FIELD_ID = 2;
    public const int MODIFIEDDATE_FIELD_ID = 3;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public AwbuildversionReader(SqlDataReader reader, bool ownsReader = false)
    {
        _reader = reader;
        _ownsReader = ownsReader;
    }

    public SqlDataReader Reader => _reader;

    public void Dispose()
    {
        if (_ownsReader)
        {
            ((IDisposable)_reader).Dispose();
        }
    }

    public bool Read()
    {
        return _reader.Read();
    }

    public byte Systeminformationid
    {
        get
        {
            return Reader.GetByte(SYSTEMINFORMATIONID_FIELD_ID);
        }
    }

    public string DatabaseVersion
    {
        get
        {
            return Reader.GetString(DATABASEVERSION_FIELD_ID);
        }
    }

    public DateTime Versiondate
    {
        get
        {
            return Reader.GetDateTime(VERSIONDATE_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Dbo.Types.AwbuildversionDataType ToDataObject()
    {
        return new AdventureWorks.Dbo.Types.AwbuildversionDataType(Systeminformationid,
            DatabaseVersion,
            Versiondate,
            Modifieddate);
    }

    public List<AdventureWorks.Dbo.Types.AwbuildversionDataType> ToList()
    {
        var list = new List<AdventureWorks.Dbo.Types.AwbuildversionDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
