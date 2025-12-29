using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Person;

public class PasswordReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[Password]";
    public const string TableName = "Password";
    public const string ShortName = "p";
    public const string Sql = """
        SELECT
          p.[Businessentityid],
          p.[Passwordhash],
          p.[Passwordsalt],
          p.[Rowguid],
          p.[Modifieddate]
        FROM
          [Person].[Password] p
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int PASSWORDHASH_FIELD_ID = 1;
    public const int PASSWORDSALT_FIELD_ID = 2;
    public const int ROWGUID_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public PasswordReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Businessentityid
    {
        get
        {
            return Reader.GetInt32(BUSINESSENTITYID_FIELD_ID);
        }
    }

    public string Passwordhash
    {
        get
        {
            return Reader.GetString(PASSWORDHASH_FIELD_ID);
        }
    }

    public string Passwordsalt
    {
        get
        {
            return Reader.GetString(PASSWORDSALT_FIELD_ID);
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


    public Types.Person.PasswordDataType ToDataObject()
    {
        return new Types.Person.PasswordDataType(Businessentityid,
            Passwordhash,
            Passwordsalt,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Person.PasswordDataType> ToList()
    {
        var list = new List<Types.Person.PasswordDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
