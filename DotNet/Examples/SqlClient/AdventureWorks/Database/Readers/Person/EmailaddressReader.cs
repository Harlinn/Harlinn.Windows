using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Person;

public class EmailaddressReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[EmailAddress]";
    public const string TableName = "EmailAddress";
    public const string ShortName = "e3";
    public const string Sql = """
        SELECT
          e3.[Businessentityid],
          e3.[Emailaddressid],
          e3.[Emailaddress],
          e3.[Rowguid],
          e3.[Modifieddate]
        FROM
          [Person].[EmailAddress] e3
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int EMAILADDRESSID_FIELD_ID = 1;
    public const int EMAILADDRESS_FIELD_ID = 2;
    public const int ROWGUID_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public EmailaddressReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Emailaddressid
    {
        get
        {
            return Reader.GetInt32(EMAILADDRESSID_FIELD_ID);
        }
    }

    public string? Emailaddress
    {
        get
        {
            return Reader.GetNullableString(EMAILADDRESS_FIELD_ID);
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


    public Types.Person.EmailaddressDataType ToDataObject()
    {
        return new Types.Person.EmailaddressDataType(Businessentityid,
            Emailaddressid,
            Emailaddress,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Person.EmailaddressDataType> ToList()
    {
        var list = new List<Types.Person.EmailaddressDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
