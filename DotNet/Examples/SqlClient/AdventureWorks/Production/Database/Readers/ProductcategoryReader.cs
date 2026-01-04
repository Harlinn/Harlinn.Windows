using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Production.Database.Readers;

public class ProductcategoryReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductCategory]";
    public const string TableName = "ProductCategory";
    public const string ShortName = "p4";
    public const string Sql = """
        SELECT
          p4.[Productcategoryid],
          p4.[Name],
          p4.[Rowguid],
          p4.[Modifieddate]
        FROM
          [Production].[ProductCategory] p4
        """;

    public const int PRODUCTCATEGORYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int ROWGUID_FIELD_ID = 2;
    public const int MODIFIEDDATE_FIELD_ID = 3;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductcategoryReader(SqlDataReader reader, bool ownsReader = false)
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


    public AdventureWorks.Production.Types.ProductcategoryDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.ProductcategoryDataType(Productcategoryid,
            Name,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.ProductcategoryDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.ProductcategoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
