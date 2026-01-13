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

public class ProductlistpricehistoryReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductListPriceHistory]";
    public const string TableName = "ProductListPriceHistory";
    public const string ShortName = "p9";
    public const string Sql = """
        SELECT
          p9.[Productid],
          p9.[Startdate],
          p9.[Enddate],
          p9.[Listprice],
          p9.[Modifieddate]
        FROM
          [Production].[ProductListPriceHistory] p9
        """;

    public const int PRODUCTID_FIELD_ID = 0;
    public const int STARTDATE_FIELD_ID = 1;
    public const int ENDDATE_FIELD_ID = 2;
    public const int LISTPRICE_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductlistpricehistoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Productid
    {
        get
        {
            return Reader.GetInt32(PRODUCTID_FIELD_ID);
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

    public decimal Listprice
    {
        get
        {
            return Reader.GetDecimal(LISTPRICE_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.ProductlistpricehistoryDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.ProductlistpricehistoryDataType(Productid,
            Startdate,
            Enddate,
            Listprice,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.ProductlistpricehistoryDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.ProductlistpricehistoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
