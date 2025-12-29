using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class ProductmodelillustrationReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductModelIllustration]";
    public const string TableName = "ProductModelIllustration";
    public const string ShortName = "p11";
    public const string Sql = """
        SELECT
          p11.[Productmodelid],
          p11.[Illustrationid],
          p11.[Modifieddate]
        FROM
          [Production].[ProductModelIllustration] p11
        """;

    public const int PRODUCTMODELID_FIELD_ID = 0;
    public const int ILLUSTRATIONID_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductmodelillustrationReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Illustrationid
    {
        get
        {
            return Reader.GetInt32(ILLUSTRATIONID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Production.ProductmodelillustrationDataType ToDataObject()
    {
        return new Types.Production.ProductmodelillustrationDataType(Productmodelid,
            Illustrationid,
            Modifieddate);
    }

    public List<Types.Production.ProductmodelillustrationDataType> ToList()
    {
        var list = new List<Types.Production.ProductmodelillustrationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
