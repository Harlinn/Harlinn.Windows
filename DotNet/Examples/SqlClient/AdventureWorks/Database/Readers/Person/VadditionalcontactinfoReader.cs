using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Person;

public class VadditionalcontactinfoReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[vAdditionalContactInfo]";
    public const string TableName = "vAdditionalContactInfo";
    public const string ShortName = "v5";
    public const string Sql = """
        SELECT
          v5.[Businessentityid],
          v5.[Firstname],
          v5.[Middlename],
          v5.[Lastname],
          v5.[Telephonenumber],
          v5.[Telephonespecialinstructions],
          v5.[Street],
          v5.[City],
          v5.[Stateprovince],
          v5.[Postalcode],
          v5.[Countryregion],
          v5.[Homeaddressspecialinstructions],
          v5.[Emailaddress],
          v5.[Emailspecialinstructions],
          v5.[Emailtelephonenumber],
          v5.[Rowguid],
          v5.[Modifieddate]
        FROM
          [Person].[vAdditionalContactInfo] v5
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int FIRSTNAME_FIELD_ID = 1;
    public const int MIDDLENAME_FIELD_ID = 2;
    public const int LASTNAME_FIELD_ID = 3;
    public const int TELEPHONENUMBER_FIELD_ID = 4;
    public const int TELEPHONESPECIALINSTRUCTIONS_FIELD_ID = 5;
    public const int STREET_FIELD_ID = 6;
    public const int CITY_FIELD_ID = 7;
    public const int STATEPROVINCE_FIELD_ID = 8;
    public const int POSTALCODE_FIELD_ID = 9;
    public const int COUNTRYREGION_FIELD_ID = 10;
    public const int HOMEADDRESSSPECIALINSTRUCTIONS_FIELD_ID = 11;
    public const int EMAILADDRESS_FIELD_ID = 12;
    public const int EMAILSPECIALINSTRUCTIONS_FIELD_ID = 13;
    public const int EMAILTELEPHONENUMBER_FIELD_ID = 14;
    public const int ROWGUID_FIELD_ID = 15;
    public const int MODIFIEDDATE_FIELD_ID = 16;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VadditionalcontactinfoReader(SqlDataReader reader, bool ownsReader = false)
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

    public string? Telephonenumber
    {
        get
        {
            return Reader.GetNullableString(TELEPHONENUMBER_FIELD_ID);
        }
    }

    public string? Telephonespecialinstructions
    {
        get
        {
            return Reader.GetNullableString(TELEPHONESPECIALINSTRUCTIONS_FIELD_ID);
        }
    }

    public string? Street
    {
        get
        {
            return Reader.GetNullableString(STREET_FIELD_ID);
        }
    }

    public string? City
    {
        get
        {
            return Reader.GetNullableString(CITY_FIELD_ID);
        }
    }

    public string? Stateprovince
    {
        get
        {
            return Reader.GetNullableString(STATEPROVINCE_FIELD_ID);
        }
    }

    public string? Postalcode
    {
        get
        {
            return Reader.GetNullableString(POSTALCODE_FIELD_ID);
        }
    }

    public string? Countryregion
    {
        get
        {
            return Reader.GetNullableString(COUNTRYREGION_FIELD_ID);
        }
    }

    public string? Homeaddressspecialinstructions
    {
        get
        {
            return Reader.GetNullableString(HOMEADDRESSSPECIALINSTRUCTIONS_FIELD_ID);
        }
    }

    public string? Emailaddress
    {
        get
        {
            return Reader.GetNullableString(EMAILADDRESS_FIELD_ID);
        }
    }

    public string? Emailspecialinstructions
    {
        get
        {
            return Reader.GetNullableString(EMAILSPECIALINSTRUCTIONS_FIELD_ID);
        }
    }

    public string? Emailtelephonenumber
    {
        get
        {
            return Reader.GetNullableString(EMAILTELEPHONENUMBER_FIELD_ID);
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


    public Types.Person.VadditionalcontactinfoDataType ToDataObject()
    {
        return new Types.Person.VadditionalcontactinfoDataType(Businessentityid,
            Firstname,
            Middlename,
            Lastname,
            Telephonenumber,
            Telephonespecialinstructions,
            Street,
            City,
            Stateprovince,
            Postalcode,
            Countryregion,
            Homeaddressspecialinstructions,
            Emailaddress,
            Emailspecialinstructions,
            Emailtelephonenumber,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Person.VadditionalcontactinfoDataType> ToList()
    {
        var list = new List<Types.Person.VadditionalcontactinfoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
