using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.HumanResources.Database.Readers;

public class ShiftReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[Shift]";
    public const string TableName = "Shift";
    public const string ShortName = "s";
    public const string Sql = """
        SELECT
          s.[Shiftid],
          s.[Name],
          s.[Starttime],
          s.[Endtime],
          s.[Modifieddate]
        FROM
          [HumanResources].[Shift] s
        """;

    public const int SHIFTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int STARTTIME_FIELD_ID = 2;
    public const int ENDTIME_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ShiftReader(SqlDataReader reader, bool ownsReader = false)
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

    public byte Shiftid
    {
        get
        {
            return Reader.GetByte(SHIFTID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public DateTime Starttime
    {
        get
        {
            return Reader.GetDateTime(STARTTIME_FIELD_ID);
        }
    }

    public DateTime Endtime
    {
        get
        {
            return Reader.GetDateTime(ENDTIME_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.HumanResources.Types.ShiftDataType ToDataObject()
    {
        return new AdventureWorks.HumanResources.Types.ShiftDataType(Shiftid,
            Name,
            Starttime,
            Endtime,
            Modifieddate);
    }

    public List<AdventureWorks.HumanResources.Types.ShiftDataType> ToList()
    {
        var list = new List<AdventureWorks.HumanResources.Types.ShiftDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
