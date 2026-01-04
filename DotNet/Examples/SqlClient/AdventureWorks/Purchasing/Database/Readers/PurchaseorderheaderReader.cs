using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Purchasing.Database.Readers;

public class PurchaseorderheaderReader : IDisposable
{
    public const string QualifiedTableName = "[Purchasing].[PurchaseOrderHeader]";
    public const string TableName = "PurchaseOrderHeader";
    public const string ShortName = "p19";
    public const string Sql = """
        SELECT
          p19.[Purchaseorderid],
          p19.[Revisionnumber],
          p19.[Status],
          p19.[Employeeid],
          p19.[Vendorid],
          p19.[Shipmethodid],
          p19.[Orderdate],
          p19.[Shipdate],
          p19.[Subtotal],
          p19.[Taxamt],
          p19.[Freight],
          p19.[Totaldue],
          p19.[Modifieddate]
        FROM
          [Purchasing].[PurchaseOrderHeader] p19
        """;

    public const int PURCHASEORDERID_FIELD_ID = 0;
    public const int REVISIONNUMBER_FIELD_ID = 1;
    public const int STATUS_FIELD_ID = 2;
    public const int EMPLOYEEID_FIELD_ID = 3;
    public const int VENDORID_FIELD_ID = 4;
    public const int SHIPMETHODID_FIELD_ID = 5;
    public const int ORDERDATE_FIELD_ID = 6;
    public const int SHIPDATE_FIELD_ID = 7;
    public const int SUBTOTAL_FIELD_ID = 8;
    public const int TAXAMT_FIELD_ID = 9;
    public const int FREIGHT_FIELD_ID = 10;
    public const int TOTALDUE_FIELD_ID = 11;
    public const int MODIFIEDDATE_FIELD_ID = 12;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public PurchaseorderheaderReader(SqlDataReader reader, bool ownsReader = false)
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

    public byte Revisionnumber
    {
        get
        {
            return Reader.GetByte(REVISIONNUMBER_FIELD_ID);
        }
    }

    public byte Status
    {
        get
        {
            return Reader.GetByte(STATUS_FIELD_ID);
        }
    }

    public int Employeeid
    {
        get
        {
            return Reader.GetInt32(EMPLOYEEID_FIELD_ID);
        }
    }

    public int Vendorid
    {
        get
        {
            return Reader.GetInt32(VENDORID_FIELD_ID);
        }
    }

    public int Shipmethodid
    {
        get
        {
            return Reader.GetInt32(SHIPMETHODID_FIELD_ID);
        }
    }

    public DateTime Orderdate
    {
        get
        {
            return Reader.GetDateTime(ORDERDATE_FIELD_ID);
        }
    }

    public DateTime? Shipdate
    {
        get
        {
            return Reader.GetNullableDateTime(SHIPDATE_FIELD_ID);
        }
    }

    public decimal Subtotal
    {
        get
        {
            return Reader.GetDecimal(SUBTOTAL_FIELD_ID);
        }
    }

    public decimal Taxamt
    {
        get
        {
            return Reader.GetDecimal(TAXAMT_FIELD_ID);
        }
    }

    public decimal Freight
    {
        get
        {
            return Reader.GetDecimal(FREIGHT_FIELD_ID);
        }
    }

    public decimal Totaldue
    {
        get
        {
            return Reader.GetDecimal(TOTALDUE_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Purchasing.Types.PurchaseorderheaderDataType ToDataObject()
    {
        return new AdventureWorks.Purchasing.Types.PurchaseorderheaderDataType(Purchaseorderid,
            Revisionnumber,
            Status,
            Employeeid,
            Vendorid,
            Shipmethodid,
            Orderdate,
            Shipdate,
            Subtotal,
            Taxamt,
            Freight,
            Totaldue,
            Modifieddate);
    }

    public List<AdventureWorks.Purchasing.Types.PurchaseorderheaderDataType> ToList()
    {
        var list = new List<AdventureWorks.Purchasing.Types.PurchaseorderheaderDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
