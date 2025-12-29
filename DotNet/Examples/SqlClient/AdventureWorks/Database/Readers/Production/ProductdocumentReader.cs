using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class ProductdocumentReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductDocument]";
    public const string TableName = "ProductDocument";
    public const string ShortName = "p7";
    public const string Sql = """
        SELECT
          p7.[Productid],
          p7.[Documentnode],
          p7.[Modifieddate]
        FROM
          [Production].[ProductDocument] p7
        """;

    public const int PRODUCTID_FIELD_ID = 0;
    public const int DOCUMENTNODE_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductdocumentReader(SqlDataReader reader, bool ownsReader = false)
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

    public SqlHierarchyId Documentnode
    {
        get
        {
            return Reader.GetSqlHierarchyId(DOCUMENTNODE_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Production.ProductdocumentDataType ToDataObject()
    {
        return new Types.Production.ProductdocumentDataType(Productid,
            Documentnode,
            Modifieddate);
    }

    public List<Types.Production.ProductdocumentDataType> ToList()
    {
        var list = new List<Types.Production.ProductdocumentDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
