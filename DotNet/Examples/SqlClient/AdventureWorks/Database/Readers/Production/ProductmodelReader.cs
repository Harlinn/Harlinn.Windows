using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class ProductmodelReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductModel]";
    public const string TableName = "ProductModel";
    public const string ShortName = "p10";
    public const string Sql = """
        SELECT
          p10.[Productmodelid],
          p10.[Name],
          p10.[Catalogdescription],
          p10.[Instructions],
          p10.[Rowguid],
          p10.[Modifieddate]
        FROM
          [Production].[ProductModel] p10
        """;

    public const int PRODUCTMODELID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int CATALOGDESCRIPTION_FIELD_ID = 2;
    public const int INSTRUCTIONS_FIELD_ID = 3;
    public const int ROWGUID_FIELD_ID = 4;
    public const int MODIFIEDDATE_FIELD_ID = 5;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductmodelReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public SqlXml? Catalogdescription
    {
        get
        {
            return Reader.GetNullableSqlXml(CATALOGDESCRIPTION_FIELD_ID);
        }
    }

    public SqlXml? Instructions
    {
        get
        {
            return Reader.GetNullableSqlXml(INSTRUCTIONS_FIELD_ID);
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


    public Types.Production.ProductmodelDataType ToDataObject()
    {
        return new Types.Production.ProductmodelDataType(Productmodelid,
            Name,
            Catalogdescription,
            Instructions,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Production.ProductmodelDataType> ToList()
    {
        var list = new List<Types.Production.ProductmodelDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
