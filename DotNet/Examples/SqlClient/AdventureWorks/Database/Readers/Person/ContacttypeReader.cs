using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Person;

public class ContacttypeReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[ContactType]";
    public const string TableName = "ContactType";
    public const string ShortName = "c";
    public const string Sql = """
        SELECT
          c.[Contacttypeid],
          c.[Name],
          c.[Modifieddate]
        FROM
          [Person].[ContactType] c
        """;

    public const int CONTACTTYPEID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ContacttypeReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Contacttypeid
    {
        get
        {
            return Reader.GetInt32(CONTACTTYPEID_FIELD_ID);
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


    public Types.Person.ContacttypeDataType ToDataObject()
    {
        return new Types.Person.ContacttypeDataType(Contacttypeid,
            Name,
            Modifieddate);
    }

    public List<Types.Person.ContacttypeDataType> ToList()
    {
        var list = new List<Types.Person.ContacttypeDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
