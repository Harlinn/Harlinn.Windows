using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Production.Database.Readers;

public class ProductdescriptionReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductDescription]";
    public const string TableName = "ProductDescription";
    public const string ShortName = "p6";
    public const string Sql = """
        SELECT
          p6.[Productdescriptionid],
          p6.[Description],
          p6.[Rowguid],
          p6.[Modifieddate]
        FROM
          [Production].[ProductDescription] p6
        """;

    public const int PRODUCTDESCRIPTIONID_FIELD_ID = 0;
    public const int DESCRIPTION_FIELD_ID = 1;
    public const int ROWGUID_FIELD_ID = 2;
    public const int MODIFIEDDATE_FIELD_ID = 3;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductdescriptionReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Productdescriptionid
    {
        get
        {
            return Reader.GetInt32(PRODUCTDESCRIPTIONID_FIELD_ID);
        }
    }

    public string Description
    {
        get
        {
            return Reader.GetString(DESCRIPTION_FIELD_ID);
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


    public AdventureWorks.Production.Types.ProductdescriptionDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.ProductdescriptionDataType(Productdescriptionid,
            Description,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.ProductdescriptionDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.ProductdescriptionDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
