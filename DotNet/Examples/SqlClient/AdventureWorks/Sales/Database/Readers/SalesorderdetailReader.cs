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

public class SalesorderdetailReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[SalesOrderDetail]";
    public const string TableName = "SalesOrderDetail";
    public const string ShortName = "s3";
    public const string Sql = """
        SELECT
          s3.[Salesorderid],
          s3.[Salesorderdetailid],
          s3.[Carriertrackingnumber],
          s3.[Orderqty],
          s3.[Productid],
          s3.[Specialofferid],
          s3.[Unitprice],
          s3.[Unitpricediscount],
          s3.[Linetotal],
          s3.[Rowguid],
          s3.[Modifieddate]
        FROM
          [Sales].[SalesOrderDetail] s3
        """;

    public const int SALESORDERID_FIELD_ID = 0;
    public const int SALESORDERDETAILID_FIELD_ID = 1;
    public const int CARRIERTRACKINGNUMBER_FIELD_ID = 2;
    public const int ORDERQTY_FIELD_ID = 3;
    public const int PRODUCTID_FIELD_ID = 4;
    public const int SPECIALOFFERID_FIELD_ID = 5;
    public const int UNITPRICE_FIELD_ID = 6;
    public const int UNITPRICEDISCOUNT_FIELD_ID = 7;
    public const int LINETOTAL_FIELD_ID = 8;
    public const int ROWGUID_FIELD_ID = 9;
    public const int MODIFIEDDATE_FIELD_ID = 10;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public SalesorderdetailReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Salesorderid
    {
        get
        {
            return Reader.GetInt32(SALESORDERID_FIELD_ID);
        }
    }

    public int Salesorderdetailid
    {
        get
        {
            return Reader.GetInt32(SALESORDERDETAILID_FIELD_ID);
        }
    }

    public string? Carriertrackingnumber
    {
        get
        {
            return Reader.GetNullableString(CARRIERTRACKINGNUMBER_FIELD_ID);
        }
    }

    public short Orderqty
    {
        get
        {
            return Reader.GetInt16(ORDERQTY_FIELD_ID);
        }
    }

    public int Productid
    {
        get
        {
            return Reader.GetInt32(PRODUCTID_FIELD_ID);
        }
    }

    public int Specialofferid
    {
        get
        {
            return Reader.GetInt32(SPECIALOFFERID_FIELD_ID);
        }
    }

    public decimal Unitprice
    {
        get
        {
            return Reader.GetDecimal(UNITPRICE_FIELD_ID);
        }
    }

    public decimal Unitpricediscount
    {
        get
        {
            return Reader.GetDecimal(UNITPRICEDISCOUNT_FIELD_ID);
        }
    }

    public decimal Linetotal
    {
        get
        {
            return Reader.GetDecimal(LINETOTAL_FIELD_ID);
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


    public AdventureWorks.Sales.Types.SalesorderdetailDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.SalesorderdetailDataType(Salesorderid,
            Salesorderdetailid,
            Carriertrackingnumber,
            Orderqty,
            Productid,
            Specialofferid,
            Unitprice,
            Unitpricediscount,
            Linetotal,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.SalesorderdetailDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.SalesorderdetailDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
