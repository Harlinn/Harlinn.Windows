using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Dbo.Database.Readers;

public class ErrorlogReader : IDisposable
{
    public const string QualifiedTableName = "[dbo].[ErrorLog]";
    public const string TableName = "ErrorLog";
    public const string ShortName = "e";
    public const string Sql = """
        SELECT
          e.[Errorlogid],
          e.[Errortime],
          e.[Username],
          e.[Errornumber],
          e.[Errorseverity],
          e.[Errorstate],
          e.[Errorprocedure],
          e.[Errorline],
          e.[Errormessage]
        FROM
          [dbo].[ErrorLog] e
        """;

    public const int ERRORLOGID_FIELD_ID = 0;
    public const int ERRORTIME_FIELD_ID = 1;
    public const int USERNAME_FIELD_ID = 2;
    public const int ERRORNUMBER_FIELD_ID = 3;
    public const int ERRORSEVERITY_FIELD_ID = 4;
    public const int ERRORSTATE_FIELD_ID = 5;
    public const int ERRORPROCEDURE_FIELD_ID = 6;
    public const int ERRORLINE_FIELD_ID = 7;
    public const int ERRORMESSAGE_FIELD_ID = 8;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ErrorlogReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Errorlogid
    {
        get
        {
            return Reader.GetInt32(ERRORLOGID_FIELD_ID);
        }
    }

    public DateTime Errortime
    {
        get
        {
            return Reader.GetDateTime(ERRORTIME_FIELD_ID);
        }
    }

    public string Username
    {
        get
        {
            return Reader.GetString(USERNAME_FIELD_ID);
        }
    }

    public int Errornumber
    {
        get
        {
            return Reader.GetInt32(ERRORNUMBER_FIELD_ID);
        }
    }

    public int? Errorseverity
    {
        get
        {
            return Reader.GetNullableInt32(ERRORSEVERITY_FIELD_ID);
        }
    }

    public int? Errorstate
    {
        get
        {
            return Reader.GetNullableInt32(ERRORSTATE_FIELD_ID);
        }
    }

    public string? Errorprocedure
    {
        get
        {
            return Reader.GetNullableString(ERRORPROCEDURE_FIELD_ID);
        }
    }

    public int? Errorline
    {
        get
        {
            return Reader.GetNullableInt32(ERRORLINE_FIELD_ID);
        }
    }

    public string Errormessage
    {
        get
        {
            return Reader.GetString(ERRORMESSAGE_FIELD_ID);
        }
    }


    public AdventureWorks.Dbo.Types.ErrorlogDataType ToDataObject()
    {
        return new AdventureWorks.Dbo.Types.ErrorlogDataType(Errorlogid,
            Errortime,
            Username,
            Errornumber,
            Errorseverity,
            Errorstate,
            Errorprocedure,
            Errorline,
            Errormessage);
    }

    public List<AdventureWorks.Dbo.Types.ErrorlogDataType> ToList()
    {
        var list = new List<AdventureWorks.Dbo.Types.ErrorlogDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
