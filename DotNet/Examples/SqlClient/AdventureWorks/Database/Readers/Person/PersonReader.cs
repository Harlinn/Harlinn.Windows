using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Person;

public class PersonReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[Person]";
    public const string TableName = "Person";
    public const string ShortName = "p0";
    public const string Sql = """
        SELECT
          p0.[Businessentityid],
          p0.[Persontype],
          p0.[Namestyle],
          p0.[Title],
          p0.[Firstname],
          p0.[Middlename],
          p0.[Lastname],
          p0.[Suffix],
          p0.[Emailpromotion],
          p0.[Additionalcontactinfo],
          p0.[Demographics],
          p0.[Rowguid],
          p0.[Modifieddate]
        FROM
          [Person].[Person] p0
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int PERSONTYPE_FIELD_ID = 1;
    public const int NAMESTYLE_FIELD_ID = 2;
    public const int TITLE_FIELD_ID = 3;
    public const int FIRSTNAME_FIELD_ID = 4;
    public const int MIDDLENAME_FIELD_ID = 5;
    public const int LASTNAME_FIELD_ID = 6;
    public const int SUFFIX_FIELD_ID = 7;
    public const int EMAILPROMOTION_FIELD_ID = 8;
    public const int ADDITIONALCONTACTINFO_FIELD_ID = 9;
    public const int DEMOGRAPHICS_FIELD_ID = 10;
    public const int ROWGUID_FIELD_ID = 11;
    public const int MODIFIEDDATE_FIELD_ID = 12;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public PersonReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Persontype
    {
        get
        {
            return Reader.GetString(PERSONTYPE_FIELD_ID);
        }
    }

    public bool Namestyle
    {
        get
        {
            return Reader.GetBoolean(NAMESTYLE_FIELD_ID);
        }
    }

    public string? Title
    {
        get
        {
            return Reader.GetNullableString(TITLE_FIELD_ID);
        }
    }

    public string Firstname
    {
        get
        {
            return Reader.GetString(FIRSTNAME_FIELD_ID);
        }
    }

    public string? Middlename
    {
        get
        {
            return Reader.GetNullableString(MIDDLENAME_FIELD_ID);
        }
    }

    public string Lastname
    {
        get
        {
            return Reader.GetString(LASTNAME_FIELD_ID);
        }
    }

    public string? Suffix
    {
        get
        {
            return Reader.GetNullableString(SUFFIX_FIELD_ID);
        }
    }

    public int Emailpromotion
    {
        get
        {
            return Reader.GetInt32(EMAILPROMOTION_FIELD_ID);
        }
    }

    public SqlXml? Additionalcontactinfo
    {
        get
        {
            return Reader.GetNullableSqlXml(ADDITIONALCONTACTINFO_FIELD_ID);
        }
    }

    public SqlXml? Demographics
    {
        get
        {
            return Reader.GetNullableSqlXml(DEMOGRAPHICS_FIELD_ID);
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


    public Types.Person.PersonDataType ToDataObject()
    {
        return new Types.Person.PersonDataType(Businessentityid,
            Persontype,
            Namestyle,
            Title,
            Firstname,
            Middlename,
            Lastname,
            Suffix,
            Emailpromotion,
            Additionalcontactinfo,
            Demographics,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Person.PersonDataType> ToList()
    {
        var list = new List<Types.Person.PersonDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
