using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class UnitmeasureReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[UnitMeasure]";
    public const string TableName = "UnitMeasure";
    public const string ShortName = "u";
    public const string Sql = """
        SELECT
          u.[Unitmeasurecode],
          u.[Name],
          u.[Modifieddate]
        FROM
          [Production].[UnitMeasure] u
        """;

    public const int UNITMEASURECODE_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public UnitmeasureReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Unitmeasurecode
    {
        get
        {
            return Reader.GetString(UNITMEASURECODE_FIELD_ID);
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


    public Types.Production.UnitmeasureDataType ToDataObject()
    {
        return new Types.Production.UnitmeasureDataType(Unitmeasurecode,
            Name,
            Modifieddate);
    }

    public List<Types.Production.UnitmeasureDataType> ToList()
    {
        var list = new List<Types.Production.UnitmeasureDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
