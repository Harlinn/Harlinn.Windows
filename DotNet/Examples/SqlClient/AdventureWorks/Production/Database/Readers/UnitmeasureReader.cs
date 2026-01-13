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

namespace AdventureWorks.Production.Database.Readers;

public class UnitmeasureReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[UnitMeasure]";
    public const string TableName = "UnitMeasure";
    public const string ShortName = "u";
    public const string Sql = """
        SELECT
          u.[Unitmeasurecode],
          u.[Name],
          u.[Modifieddate]
        FROM
          [Production].[UnitMeasure] u
        """;

    public const int UNITMEASURECODE_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public UnitmeasureReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Unitmeasurecode
    {
        get
        {
            return Reader.GetString(UNITMEASURECODE_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.UnitmeasureDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.UnitmeasureDataType(Unitmeasurecode,
            Name,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.UnitmeasureDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.UnitmeasureDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
