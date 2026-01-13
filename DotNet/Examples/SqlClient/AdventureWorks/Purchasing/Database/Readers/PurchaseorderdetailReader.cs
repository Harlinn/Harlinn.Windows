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

public class PurchaseorderdetailReader : IDisposable
{
    public const string QualifiedTableName = "[Purchasing].[PurchaseOrderDetail]";
    public const string TableName = "PurchaseOrderDetail";
    public const string ShortName = "p18";
    public const string Sql = """
        SELECT
          p18.[Purchaseorderid],
          p18.[Purchaseorderdetailid],
          p18.[Duedate],
          p18.[Orderqty],
          p18.[Productid],
          p18.[Unitprice],
          p18.[Linetotal],
          p18.[Receivedqty],
          p18.[Rejectedqty],
          p18.[Stockedqty],
          p18.[Modifieddate]
        FROM
          [Purchasing].[PurchaseOrderDetail] p18
        """;

    public const int PURCHASEORDERID_FIELD_ID = 0;
    public const int PURCHASEORDERDETAILID_FIELD_ID = 1;
    public const int DUEDATE_FIELD_ID = 2;
    public const int ORDERQTY_FIELD_ID = 3;
    public const int PRODUCTID_FIELD_ID = 4;
    public const int UNITPRICE_FIELD_ID = 5;
    public const int LINETOTAL_FIELD_ID = 6;
    public const int RECEIVEDQTY_FIELD_ID = 7;
    public const int REJECTEDQTY_FIELD_ID = 8;
    public const int STOCKEDQTY_FIELD_ID = 9;
    public const int MODIFIEDDATE_FIELD_ID = 10;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public PurchaseorderdetailReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Purchaseorderid
    {
        get
        {
            return Reader.GetInt32(PURCHASEORDERID_FIELD_ID);
        }
    }

    public int Purchaseorderdetailid
    {
        get
        {
            return Reader.GetInt32(PURCHASEORDERDETAILID_FIELD_ID);
        }
    }

    public DateTime Duedate
    {
        get
        {
            return Reader.GetDateTime(DUEDATE_FIELD_ID);
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

    public decimal Unitprice
    {
        get
        {
            return Reader.GetDecimal(UNITPRICE_FIELD_ID);
        }
    }

    public decimal Linetotal
    {
        get
        {
            return Reader.GetDecimal(LINETOTAL_FIELD_ID);
        }
    }

    public decimal Receivedqty
    {
        get
        {
            return Reader.GetDecimal(RECEIVEDQTY_FIELD_ID);
        }
    }

    public decimal Rejectedqty
    {
        get
        {
            return Reader.GetDecimal(REJECTEDQTY_FIELD_ID);
        }
    }

    public decimal Stockedqty
    {
        get
        {
            return Reader.GetDecimal(STOCKEDQTY_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Purchasing.Types.PurchaseorderdetailDataType ToDataObject()
    {
        return new AdventureWorks.Purchasing.Types.PurchaseorderdetailDataType(Purchaseorderid,
            Purchaseorderdetailid,
            Duedate,
            Orderqty,
            Productid,
            Unitprice,
            Linetotal,
            Receivedqty,
            Rejectedqty,
            Stockedqty,
            Modifieddate);
    }

    public List<AdventureWorks.Purchasing.Types.PurchaseorderdetailDataType> ToList()
    {
        var list = new List<AdventureWorks.Purchasing.Types.PurchaseorderdetailDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
