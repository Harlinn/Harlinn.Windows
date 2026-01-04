using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Production.Database.Readers;

public class ProductcosthistoryReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductCostHistory]";
    public const string TableName = "ProductCostHistory";
    public const string ShortName = "p5";
    public const string Sql = """
        SELECT
          p5.[Productid],
          p5.[Startdate],
          p5.[Enddate],
          p5.[Standardcost],
          p5.[Modifieddate]
        FROM
          [Production].[ProductCostHistory] p5
        """;

    public const int PRODUCTID_FIELD_ID = 0;
    public const int STARTDATE_FIELD_ID = 1;
    public const int ENDDATE_FIELD_ID = 2;
    public const int STANDARDCOST_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductcosthistoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public decimal Standardcost
    {
        get
        {
            return Reader.GetDecimal(STANDARDCOST_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.ProductcosthistoryDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.ProductcosthistoryDataType(Productid,
            Startdate,
            Enddate,
            Standardcost,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.ProductcosthistoryDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.ProductcosthistoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
