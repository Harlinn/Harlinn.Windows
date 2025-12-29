using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class IllustrationReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[Illustration]";
    public const string TableName = "Illustration";
    public const string ShortName = "i";
    public const string Sql = """
        SELECT
          i.[Illustrationid],
          i.[Diagram],
          i.[Modifieddate]
        FROM
          [Production].[Illustration] i
        """;

    public const int ILLUSTRATIONID_FIELD_ID = 0;
    public const int DIAGRAM_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public IllustrationReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Illustrationid
    {
        get
        {
            return Reader.GetInt32(ILLUSTRATIONID_FIELD_ID);
        }
    }

    public SqlXml? Diagram
    {
        get
        {
            return Reader.GetNullableSqlXml(DIAGRAM_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Production.IllustrationDataType ToDataObject()
    {
        return new Types.Production.IllustrationDataType(Illustrationid,
            Diagram,
            Modifieddate);
    }

    public List<Types.Production.IllustrationDataType> ToList()
    {
        var list = new List<Types.Production.IllustrationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
