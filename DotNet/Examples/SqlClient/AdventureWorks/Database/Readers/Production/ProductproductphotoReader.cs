using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class ProductproductphotoReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductProductPhoto]";
    public const string TableName = "ProductProductPhoto";
    public const string ShortName = "p14";
    public const string Sql = """
        SELECT
          p14.[Productid],
          p14.[Productphotoid],
          p14.[Primary],
          p14.[Modifieddate]
        FROM
          [Production].[ProductProductPhoto] p14
        """;

    public const int PRODUCTID_FIELD_ID = 0;
    public const int PRODUCTPHOTOID_FIELD_ID = 1;
    public const int PRIMARY_FIELD_ID = 2;
    public const int MODIFIEDDATE_FIELD_ID = 3;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductproductphotoReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Productphotoid
    {
        get
        {
            return Reader.GetInt32(PRODUCTPHOTOID_FIELD_ID);
        }
    }

    public bool Primary
    {
        get
        {
            return Reader.GetBoolean(PRIMARY_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Production.ProductproductphotoDataType ToDataObject()
    {
        return new Types.Production.ProductproductphotoDataType(Productid,
            Productphotoid,
            Primary,
            Modifieddate);
    }

    public List<Types.Production.ProductproductphotoDataType> ToList()
    {
        var list = new List<Types.Production.ProductproductphotoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
