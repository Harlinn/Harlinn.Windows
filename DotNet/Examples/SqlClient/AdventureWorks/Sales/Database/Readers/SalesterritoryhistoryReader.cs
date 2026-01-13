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

namespace AdventureWorks.Sales.Database.Readers;

public class SalesterritoryhistoryReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[SalesTerritoryHistory]";
    public const string TableName = "SalesTerritoryHistory";
    public const string ShortName = "s11";
    public const string Sql = """
        SELECT
          s11.[Businessentityid],
          s11.[Territoryid],
          s11.[Startdate],
          s11.[Enddate],
          s11.[Rowguid],
          s11.[Modifieddate]
        FROM
          [Sales].[SalesTerritoryHistory] s11
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int TERRITORYID_FIELD_ID = 1;
    public const int STARTDATE_FIELD_ID = 2;
    public const int ENDDATE_FIELD_ID = 3;
    public const int ROWGUID_FIELD_ID = 4;
    public const int MODIFIEDDATE_FIELD_ID = 5;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public SalesterritoryhistoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Businessentityid
    {
        get
        {
            return Reader.GetInt32(BUSINESSENTITYID_FIELD_ID);
        }
    }

    public int Territoryid
    {
        get
        {
            return Reader.GetInt32(TERRITORYID_FIELD_ID);
        }
    }

    public DateTime Startdate
    {
        get
        {
            return Reader.GetDateTime(STARTDATE_FIELD_ID);
        }
    }

    public DateTime? Enddate
    {
        get
        {
            return Reader.GetNullableDateTime(ENDDATE_FIELD_ID);
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


    public AdventureWorks.Sales.Types.SalesterritoryhistoryDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.SalesterritoryhistoryDataType(Businessentityid,
            Territoryid,
            Startdate,
            Enddate,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.SalesterritoryhistoryDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.SalesterritoryhistoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
