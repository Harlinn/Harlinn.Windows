using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

public class SalesorderheaderReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[SalesOrderHeader]";
    public const string TableName = "SalesOrderHeader";
    public const string ShortName = "s4";
    public const string Sql = """
        SELECT
          s4.[Salesorderid],
          s4.[Revisionnumber],
          s4.[Orderdate],
          s4.[Duedate],
          s4.[Shipdate],
          s4.[Status],
          s4.[Onlineorderflag],
          s4.[Salesordernumber],
          s4.[Purchaseordernumber],
          s4.[Accountnumber],
          s4.[Customerid],
          s4.[Salespersonid],
          s4.[Territoryid],
          s4.[Billtoaddressid],
          s4.[Shiptoaddressid],
          s4.[Shipmethodid],
          s4.[Creditcardid],
          s4.[Creditcardapprovalcode],
          s4.[Currencyrateid],
          s4.[Subtotal],
          s4.[Taxamt],
          s4.[Freight],
          s4.[Totaldue],
          s4.[Comment],
          s4.[Rowguid],
          s4.[Modifieddate]
        FROM
          [Sales].[SalesOrderHeader] s4
        """;

    public const int SALESORDERID_FIELD_ID = 0;
    public const int REVISIONNUMBER_FIELD_ID = 1;
    public const int ORDERDATE_FIELD_ID = 2;
    public const int DUEDATE_FIELD_ID = 3;
    public const int SHIPDATE_FIELD_ID = 4;
    public const int STATUS_FIELD_ID = 5;
    public const int ONLINEORDERFLAG_FIELD_ID = 6;
    public const int SALESORDERNUMBER_FIELD_ID = 7;
    public const int PURCHASEORDERNUMBER_FIELD_ID = 8;
    public const int ACCOUNTNUMBER_FIELD_ID = 9;
    public const int CUSTOMERID_FIELD_ID = 10;
    public const int SALESPERSONID_FIELD_ID = 11;
    public const int TERRITORYID_FIELD_ID = 12;
    public const int BILLTOADDRESSID_FIELD_ID = 13;
    public const int SHIPTOADDRESSID_FIELD_ID = 14;
    public const int SHIPMETHODID_FIELD_ID = 15;
    public const int CREDITCARDID_FIELD_ID = 16;
    public const int CREDITCARDAPPROVALCODE_FIELD_ID = 17;
    public const int CURRENCYRATEID_FIELD_ID = 18;
    public const int SUBTOTAL_FIELD_ID = 19;
    public const int TAXAMT_FIELD_ID = 20;
    public const int FREIGHT_FIELD_ID = 21;
    public const int TOTALDUE_FIELD_ID = 22;
    public const int COMMENT_FIELD_ID = 23;
    public const int ROWGUID_FIELD_ID = 24;
    public const int MODIFIEDDATE_FIELD_ID = 25;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public SalesorderheaderReader(SqlDataReader reader, bool ownsReader = false)
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

    public byte Revisionnumber
    {
        get
        {
            return Reader.GetByte(REVISIONNUMBER_FIELD_ID);
        }
    }

    public DateTime Orderdate
    {
        get
        {
            return Reader.GetDateTime(ORDERDATE_FIELD_ID);
        }
    }

    public DateTime Duedate
    {
        get
        {
            return Reader.GetDateTime(DUEDATE_FIELD_ID);
        }
    }

    public DateTime? Shipdate
    {
        get
        {
            return Reader.GetNullableDateTime(SHIPDATE_FIELD_ID);
        }
    }

    public byte Status
    {
        get
        {
            return Reader.GetByte(STATUS_FIELD_ID);
        }
    }

    public bool Onlineorderflag
    {
        get
        {
            return Reader.GetBoolean(ONLINEORDERFLAG_FIELD_ID);
        }
    }

    public string Salesordernumber
    {
        get
        {
            return Reader.GetString(SALESORDERNUMBER_FIELD_ID);
        }
    }

    public string? Purchaseordernumber
    {
        get
        {
            return Reader.GetNullableString(PURCHASEORDERNUMBER_FIELD_ID);
        }
    }

    public string? Accountnumber
    {
        get
        {
            return Reader.GetNullableString(ACCOUNTNUMBER_FIELD_ID);
        }
    }

    public int Customerid
    {
        get
        {
            return Reader.GetInt32(CUSTOMERID_FIELD_ID);
        }
    }

    public int? Salespersonid
    {
        get
        {
            return Reader.GetNullableInt32(SALESPERSONID_FIELD_ID);
        }
    }

    public int? Territoryid
    {
        get
        {
            return Reader.GetNullableInt32(TERRITORYID_FIELD_ID);
        }
    }

    public int Billtoaddressid
    {
        get
        {
            return Reader.GetInt32(BILLTOADDRESSID_FIELD_ID);
        }
    }

    public int Shiptoaddressid
    {
        get
        {
            return Reader.GetInt32(SHIPTOADDRESSID_FIELD_ID);
        }
    }

    public int Shipmethodid
    {
        get
        {
            return Reader.GetInt32(SHIPMETHODID_FIELD_ID);
        }
    }

    public int? Creditcardid
    {
        get
        {
            return Reader.GetNullableInt32(CREDITCARDID_FIELD_ID);
        }
    }

    public string? Creditcardapprovalcode
    {
        get
        {
            return Reader.GetNullableString(CREDITCARDAPPROVALCODE_FIELD_ID);
        }
    }

    public int? Currencyrateid
    {
        get
        {
            return Reader.GetNullableInt32(CURRENCYRATEID_FIELD_ID);
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

    public string? Comment
    {
        get
        {
            return Reader.GetNullableString(COMMENT_FIELD_ID);
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


    public Types.Sales.SalesorderheaderDataType ToDataObject()
    {
        return new Types.Sales.SalesorderheaderDataType(Salesorderid,
            Revisionnumber,
            Orderdate,
            Duedate,
            Shipdate,
            Status,
            Onlineorderflag,
            Salesordernumber,
            Purchaseordernumber,
            Accountnumber,
            Customerid,
            Salespersonid,
            Territoryid,
            Billtoaddressid,
            Shiptoaddressid,
            Shipmethodid,
            Creditcardid,
            Creditcardapprovalcode,
            Currencyrateid,
            Subtotal,
            Taxamt,
            Freight,
            Totaldue,
            Comment,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Sales.SalesorderheaderDataType> ToList()
    {
        var list = new List<Types.Sales.SalesorderheaderDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
