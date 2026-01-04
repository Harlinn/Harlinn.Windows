using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Person.Database.Readers;

public class PhonenumbertypeReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[PhoneNumberType]";
    public const string TableName = "PhoneNumberType";
    public const string ShortName = "p2";
    public const string Sql = """
        SELECT
          p2.[Phonenumbertypeid],
          p2.[Name],
          p2.[Modifieddate]
        FROM
          [Person].[PhoneNumberType] p2
        """;

    public const int PHONENUMBERTYPEID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public PhonenumbertypeReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Phonenumbertypeid
    {
        get
        {
            return Reader.GetInt32(PHONENUMBERTYPEID_FIELD_ID);
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


    public AdventureWorks.Person.Types.PhonenumbertypeDataType ToDataObject()
    {
        return new AdventureWorks.Person.Types.PhonenumbertypeDataType(Phonenumbertypeid,
            Name,
            Modifieddate);
    }

    public List<AdventureWorks.Person.Types.PhonenumbertypeDataType> ToList()
    {
        var list = new List<AdventureWorks.Person.Types.PhonenumbertypeDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
