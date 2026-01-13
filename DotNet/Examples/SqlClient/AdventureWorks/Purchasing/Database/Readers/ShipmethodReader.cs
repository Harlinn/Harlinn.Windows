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

namespace AdventureWorks.Purchasing.Database.Readers;

public class ShipmethodReader : IDisposable
{
    public const string QualifiedTableName = "[Purchasing].[ShipMethod]";
    public const string TableName = "ShipMethod";
    public const string ShortName = "s2";
    public const string Sql = """
        SELECT
          s2.[Shipmethodid],
          s2.[Name],
          s2.[Shipbase],
          s2.[Shiprate],
          s2.[Rowguid],
          s2.[Modifieddate]
        FROM
          [Purchasing].[ShipMethod] s2
        """;

    public const int SHIPMETHODID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int SHIPBASE_FIELD_ID = 2;
    public const int SHIPRATE_FIELD_ID = 3;
    public const int ROWGUID_FIELD_ID = 4;
    public const int MODIFIEDDATE_FIELD_ID = 5;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ShipmethodReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Shipmethodid
    {
        get
        {
            return Reader.GetInt32(SHIPMETHODID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public decimal Shipbase
    {
        get
        {
            return Reader.GetDecimal(SHIPBASE_FIELD_ID);
        }
    }

    public decimal Shiprate
    {
        get
        {
            return Reader.GetDecimal(SHIPRATE_FIELD_ID);
        }
    }

    public Guid Rowguid
    {
        get
        {
            return Reader.GetGuid(ROWGUID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Purchasing.Types.ShipmethodDataType ToDataObject()
    {
        return new AdventureWorks.Purchasing.Types.ShipmethodDataType(Shipmethodid,
            Name,
            Shipbase,
            Shiprate,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Purchasing.Types.ShipmethodDataType> ToList()
    {
        var list = new List<AdventureWorks.Purchasing.Types.ShipmethodDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
