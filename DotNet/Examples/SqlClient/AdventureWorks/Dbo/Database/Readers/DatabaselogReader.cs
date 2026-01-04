using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Dbo.Database.Readers;

public class DatabaselogReader : IDisposable
{
    public const string QualifiedTableName = "[dbo].[DatabaseLog]";
    public const string TableName = "DatabaseLog";
    public const string ShortName = "d";
    public const string Sql = """
        SELECT
          d.[Databaselogid],
          d.[Posttime],
          d.[Databaseuser],
          d.[Event],
          d.[Schema],
          d.[Object],
          d.[Tsql],
          d.[Xmlevent]
        FROM
          [dbo].[DatabaseLog] d
        """;

    public const int DATABASELOGID_FIELD_ID = 0;
    public const int POSTTIME_FIELD_ID = 1;
    public const int DATABASEUSER_FIELD_ID = 2;
    public const int EVENT_FIELD_ID = 3;
    public const int SCHEMA_FIELD_ID = 4;
    public const int OBJECT_FIELD_ID = 5;
    public const int TSQL_FIELD_ID = 6;
    public const int XMLEVENT_FIELD_ID = 7;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public DatabaselogReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Databaselogid
    {
        get
        {
            return Reader.GetInt32(DATABASELOGID_FIELD_ID);
        }
    }

    public DateTime Posttime
    {
        get
        {
            return Reader.GetDateTime(POSTTIME_FIELD_ID);
        }
    }

    public string Databaseuser
    {
        get
        {
            return Reader.GetString(DATABASEUSER_FIELD_ID);
        }
    }

    public string Event
    {
        get
        {
            return Reader.GetString(EVENT_FIELD_ID);
        }
    }

    public string? Schema
    {
        get
        {
            return Reader.GetNullableString(SCHEMA_FIELD_ID);
        }
    }

    public string? Object
    {
        get
        {
            return Reader.GetNullableString(OBJECT_FIELD_ID);
        }
    }

    public string Tsql
    {
        get
        {
            return Reader.GetString(TSQL_FIELD_ID);
        }
    }

    public SqlXml Xmlevent
    {
        get
        {
            return Reader.GetSqlXml(XMLEVENT_FIELD_ID);
        }
    }


    public AdventureWorks.Dbo.Types.DatabaselogDataType ToDataObject()
    {
        return new AdventureWorks.Dbo.Types.DatabaselogDataType(Databaselogid,
            Posttime,
            Databaseuser,
            Event,
            Schema,
            Object,
            Tsql,
            Xmlevent);
    }

    public List<AdventureWorks.Dbo.Types.DatabaselogDataType> ToList()
    {
        var list = new List<AdventureWorks.Dbo.Types.DatabaselogDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
