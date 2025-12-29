using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class ProductsubcategoryReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductSubcategory]";
    public const string TableName = "ProductSubcategory";
    public const string ShortName = "p16";
    public const string Sql = """
        SELECT
          p16.[Productsubcategoryid],
          p16.[Productcategoryid],
          p16.[Name],
          p16.[Rowguid],
          p16.[Modifieddate]
        FROM
          [Production].[ProductSubcategory] p16
        """;

    public const int PRODUCTSUBCATEGORYID_FIELD_ID = 0;
    public const int PRODUCTCATEGORYID_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int ROWGUID_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductsubcategoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Productsubcategoryid
    {
        get
        {
            return Reader.GetInt32(PRODUCTSUBCATEGORYID_FIELD_ID);
        }
    }

    public int Productcategoryid
    {
        get
        {
            return Reader.GetInt32(PRODUCTCATEGORYID_FIELD_ID);
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


    public Types.Production.ProductsubcategoryDataType ToDataObject()
    {
        return new Types.Production.ProductsubcategoryDataType(Productsubcategoryid,
            Productcategoryid,
            Name,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Production.ProductsubcategoryDataType> ToList()
    {
        var list = new List<Types.Production.ProductsubcategoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
