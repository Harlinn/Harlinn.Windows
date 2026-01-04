using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Production.Database.Readers;

public class ProductmodelproductdescriptioncultureReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductModelProductDescriptionCulture]";
    public const string TableName = "ProductModelProductDescriptionCulture";
    public const string ShortName = "p12";
    public const string Sql = """
        SELECT
          p12.[Productmodelid],
          p12.[Productdescriptionid],
          p12.[Cultureid],
          p12.[Modifieddate]
        FROM
          [Production].[ProductModelProductDescriptionCulture] p12
        """;

    public const int PRODUCTMODELID_FIELD_ID = 0;
    public const int PRODUCTDESCRIPTIONID_FIELD_ID = 1;
    public const int CULTUREID_FIELD_ID = 2;
    public const int MODIFIEDDATE_FIELD_ID = 3;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductmodelproductdescriptioncultureReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Productmodelid
    {
        get
        {
            return Reader.GetInt32(PRODUCTMODELID_FIELD_ID);
        }
    }

    public int Productdescriptionid
    {
        get
        {
            return Reader.GetInt32(PRODUCTDESCRIPTIONID_FIELD_ID);
        }
    }

    public string Cultureid
    {
        get
        {
            return Reader.GetString(CULTUREID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.ProductmodelproductdescriptioncultureDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.ProductmodelproductdescriptioncultureDataType(Productmodelid,
            Productdescriptionid,
            Cultureid,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.ProductmodelproductdescriptioncultureDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.ProductmodelproductdescriptioncultureDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
