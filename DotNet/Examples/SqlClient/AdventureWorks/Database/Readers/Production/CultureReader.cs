using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class CultureReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[Culture]";
    public const string TableName = "Culture";
    public const string ShortName = "c1";
    public const string Sql = """
        SELECT
          c1.[Cultureid],
          c1.[Name],
          c1.[Modifieddate]
        FROM
          [Production].[Culture] c1
        """;

    public const int CULTUREID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public CultureReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Cultureid
    {
        get
        {
            return Reader.GetString(CULTUREID_FIELD_ID);
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


    public Types.Production.CultureDataType ToDataObject()
    {
        return new Types.Production.CultureDataType(Cultureid,
            Name,
            Modifieddate);
    }

    public List<Types.Production.CultureDataType> ToList()
    {
        var list = new List<Types.Production.CultureDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
