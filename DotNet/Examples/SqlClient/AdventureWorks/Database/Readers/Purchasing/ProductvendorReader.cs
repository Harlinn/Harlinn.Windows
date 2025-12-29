using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Purchasing;

public class ProductvendorReader : IDisposable
{
    public const string QualifiedTableName = "[Purchasing].[ProductVendor]";
    public const string TableName = "ProductVendor";
    public const string ShortName = "p17";
    public const string Sql = """
        SELECT
          p17.[Productid],
          p17.[Businessentityid],
          p17.[Averageleadtime],
          p17.[Standardprice],
          p17.[Lastreceiptcost],
          p17.[Lastreceiptdate],
          p17.[Minorderqty],
          p17.[Maxorderqty],
          p17.[Onorderqty],
          p17.[Unitmeasurecode],
          p17.[Modifieddate]
        FROM
          [Purchasing].[ProductVendor] p17
        """;

    public const int PRODUCTID_FIELD_ID = 0;
    public const int BUSINESSENTITYID_FIELD_ID = 1;
    public const int AVERAGELEADTIME_FIELD_ID = 2;
    public const int STANDARDPRICE_FIELD_ID = 3;
    public const int LASTRECEIPTCOST_FIELD_ID = 4;
    public const int LASTRECEIPTDATE_FIELD_ID = 5;
    public const int MINORDERQTY_FIELD_ID = 6;
    public const int MAXORDERQTY_FIELD_ID = 7;
    public const int ONORDERQTY_FIELD_ID = 8;
    public const int UNITMEASURECODE_FIELD_ID = 9;
    public const int MODIFIEDDATE_FIELD_ID = 10;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductvendorReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Businessentityid
    {
        get
        {
            return Reader.GetInt32(BUSINESSENTITYID_FIELD_ID);
        }
    }

    public int Averageleadtime
    {
        get
        {
            return Reader.GetInt32(AVERAGELEADTIME_FIELD_ID);
        }
    }

    public decimal Standardprice
    {
        get
        {
            return Reader.GetDecimal(STANDARDPRICE_FIELD_ID);
        }
    }

    public decimal? Lastreceiptcost
    {
        get
        {
            return Reader.GetNullableDecimal(LASTRECEIPTCOST_FIELD_ID);
        }
    }

    public DateTime? Lastreceiptdate
    {
        get
        {
            return Reader.GetNullableDateTime(LASTRECEIPTDATE_FIELD_ID);
        }
    }

    public int Minorderqty
    {
        get
        {
            return Reader.GetInt32(MINORDERQTY_FIELD_ID);
        }
    }

    public int Maxorderqty
    {
        get
        {
            return Reader.GetInt32(MAXORDERQTY_FIELD_ID);
        }
    }

    public int? Onorderqty
    {
        get
        {
            return Reader.GetNullableInt32(ONORDERQTY_FIELD_ID);
        }
    }

    public string Unitmeasurecode
    {
        get
        {
            return Reader.GetString(UNITMEASURECODE_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Purchasing.ProductvendorDataType ToDataObject()
    {
        return new Types.Purchasing.ProductvendorDataType(Productid,
            Businessentityid,
            Averageleadtime,
            Standardprice,
            Lastreceiptcost,
            Lastreceiptdate,
            Minorderqty,
            Maxorderqty,
            Onorderqty,
            Unitmeasurecode,
            Modifieddate);
    }

    public List<Types.Purchasing.ProductvendorDataType> ToList()
    {
        var list = new List<Types.Purchasing.ProductvendorDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
