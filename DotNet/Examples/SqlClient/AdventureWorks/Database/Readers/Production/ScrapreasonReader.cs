using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class ScrapreasonReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ScrapReason]";
    public const string TableName = "ScrapReason";
    public const string ShortName = "s1";
    public const string Sql = """
        SELECT
          s1.[Scrapreasonid],
          s1.[Name],
          s1.[Modifieddate]
        FROM
          [Production].[ScrapReason] s1
        """;

    public const int SCRAPREASONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ScrapreasonReader(SqlDataReader reader, bool ownsReader = false)
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

    public short Scrapreasonid
    {
        get
        {
            return Reader.GetInt16(SCRAPREASONID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Production.ScrapreasonDataType ToDataObject()
    {
        return new Types.Production.ScrapreasonDataType(Scrapreasonid,
            Name,
            Modifieddate);
    }

    public List<Types.Production.ScrapreasonDataType> ToList()
    {
        var list = new List<Types.Production.ScrapreasonDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
