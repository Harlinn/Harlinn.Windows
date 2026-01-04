using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Purchasing.Database.Readers;

public class VvendorwithcontactsReader : IDisposable
{
    public const string QualifiedTableName = "[Purchasing].[vVendorWithContacts]";
    public const string TableName = "vVendorWithContacts";
    public const string ShortName = "v12";
    public const string Sql = """
        SELECT
          v12.[Businessentityid],
          v12.[Name],
          v12.[Contacttype],
          v12.[Title],
          v12.[Firstname],
          v12.[Middlename],
          v12.[Lastname],
          v12.[Suffix],
          v12.[Phonenumber],
          v12.[Phonenumbertype],
          v12.[Emailaddress],
          v12.[Emailpromotion]
        FROM
          [Purchasing].[vVendorWithContacts] v12
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int CONTACTTYPE_FIELD_ID = 2;
    public const int TITLE_FIELD_ID = 3;
    public const int FIRSTNAME_FIELD_ID = 4;
    public const int MIDDLENAME_FIELD_ID = 5;
    public const int LASTNAME_FIELD_ID = 6;
    public const int SUFFIX_FIELD_ID = 7;
    public const int PHONENUMBER_FIELD_ID = 8;
    public const int PHONENUMBERTYPE_FIELD_ID = 9;
    public const int EMAILADDRESS_FIELD_ID = 10;
    public const int EMAILPROMOTION_FIELD_ID = 11;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VvendorwithcontactsReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public string Contacttype
    {
        get
        {
            return Reader.GetString(CONTACTTYPE_FIELD_ID);
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

    public string? Phonenumber
    {
        get
        {
            return Reader.GetNullableString(PHONENUMBER_FIELD_ID);
        }
    }

    public string? Phonenumbertype
    {
        get
        {
            return Reader.GetNullableString(PHONENUMBERTYPE_FIELD_ID);
        }
    }

    public string? Emailaddress
    {
        get
        {
            return Reader.GetNullableString(EMAILADDRESS_FIELD_ID);
        }
    }

    public int Emailpromotion
    {
        get
        {
            return Reader.GetInt32(EMAILPROMOTION_FIELD_ID);
        }
    }


    public AdventureWorks.Purchasing.Types.VvendorwithcontactsDataType ToDataObject()
    {
        return new AdventureWorks.Purchasing.Types.VvendorwithcontactsDataType(Businessentityid,
            Name,
            Contacttype,
            Title,
            Firstname,
            Middlename,
            Lastname,
            Suffix,
            Phonenumber,
            Phonenumbertype,
            Emailaddress,
            Emailpromotion);
    }

    public List<AdventureWorks.Purchasing.Types.VvendorwithcontactsDataType> ToList()
    {
        var list = new List<AdventureWorks.Purchasing.Types.VvendorwithcontactsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
