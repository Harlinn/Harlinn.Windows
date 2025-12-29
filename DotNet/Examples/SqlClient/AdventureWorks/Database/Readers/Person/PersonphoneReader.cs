using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Person;

public class PersonphoneReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[PersonPhone]";
    public const string TableName = "PersonPhone";
    public const string ShortName = "p1";
    public const string Sql = """
        SELECT
          p1.[Businessentityid],
          p1.[Phonenumber],
          p1.[Phonenumbertypeid],
          p1.[Modifieddate]
        FROM
          [Person].[PersonPhone] p1
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int PHONENUMBER_FIELD_ID = 1;
    public const int PHONENUMBERTYPEID_FIELD_ID = 2;
    public const int MODIFIEDDATE_FIELD_ID = 3;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public PersonphoneReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Phonenumber
    {
        get
        {
            return Reader.GetString(PHONENUMBER_FIELD_ID);
        }
    }

    public int Phonenumbertypeid
    {
        get
        {
            return Reader.GetInt32(PHONENUMBERTYPEID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Person.PersonphoneDataType ToDataObject()
    {
        return new Types.Person.PersonphoneDataType(Businessentityid,
            Phonenumber,
            Phonenumbertypeid,
            Modifieddate);
    }

    public List<Types.Person.PersonphoneDataType> ToList()
    {
        var list = new List<Types.Person.PersonphoneDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
