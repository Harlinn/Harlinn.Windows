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

public class SalestaxrateReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[SalesTaxRate]";
    public const string TableName = "SalesTaxRate";
    public const string ShortName = "s9";
    public const string Sql = """
        SELECT
          s9.[Salestaxrateid],
          s9.[Stateprovinceid],
          s9.[Taxtype],
          s9.[Taxrate],
          s9.[Name],
          s9.[Rowguid],
          s9.[Modifieddate]
        FROM
          [Sales].[SalesTaxRate] s9
        """;

    public const int SALESTAXRATEID_FIELD_ID = 0;
    public const int STATEPROVINCEID_FIELD_ID = 1;
    public const int TAXTYPE_FIELD_ID = 2;
    public const int TAXRATE_FIELD_ID = 3;
    public const int NAME_FIELD_ID = 4;
    public const int ROWGUID_FIELD_ID = 5;
    public const int MODIFIEDDATE_FIELD_ID = 6;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public SalestaxrateReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Salestaxrateid
    {
        get
        {
            return Reader.GetInt32(SALESTAXRATEID_FIELD_ID);
        }
    }

    public int Stateprovinceid
    {
        get
        {
            return Reader.GetInt32(STATEPROVINCEID_FIELD_ID);
        }
    }

    public byte Taxtype
    {
        get
        {
            return Reader.GetByte(TAXTYPE_FIELD_ID);
        }
    }

    public decimal Taxrate
    {
        get
        {
            return Reader.GetDecimal(TAXRATE_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
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


    public AdventureWorks.Sales.Types.SalestaxrateDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.SalestaxrateDataType(Salestaxrateid,
            Stateprovinceid,
            Taxtype,
            Taxrate,
            Name,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.SalestaxrateDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.SalestaxrateDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
