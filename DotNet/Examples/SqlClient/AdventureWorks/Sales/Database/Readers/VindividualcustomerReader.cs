using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Sales.Database.Readers;

public class VindividualcustomerReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[vIndividualCustomer]";
    public const string TableName = "vIndividualCustomer";
    public const string ShortName = "v13";
    public const string Sql = """
        SELECT
          v13.[Businessentityid],
          v13.[Title],
          v13.[Firstname],
          v13.[Middlename],
          v13.[Lastname],
          v13.[Suffix],
          v13.[Phonenumber],
          v13.[Phonenumbertype],
          v13.[Emailaddress],
          v13.[Emailpromotion],
          v13.[Addresstype],
          v13.[Addressline1],
          v13.[Addressline2],
          v13.[City],
          v13.[Stateprovincename],
          v13.[Postalcode],
          v13.[Countryregionname],
          v13.[Demographics]
        FROM
          [Sales].[vIndividualCustomer] v13
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int TITLE_FIELD_ID = 1;
    public const int FIRSTNAME_FIELD_ID = 2;
    public const int MIDDLENAME_FIELD_ID = 3;
    public const int LASTNAME_FIELD_ID = 4;
    public const int SUFFIX_FIELD_ID = 5;
    public const int PHONENUMBER_FIELD_ID = 6;
    public const int PHONENUMBERTYPE_FIELD_ID = 7;
    public const int EMAILADDRESS_FIELD_ID = 8;
    public const int EMAILPROMOTION_FIELD_ID = 9;
    public const int ADDRESSTYPE_FIELD_ID = 10;
    public const int ADDRESSLINE1_FIELD_ID = 11;
    public const int ADDRESSLINE2_FIELD_ID = 12;
    public const int CITY_FIELD_ID = 13;
    public const int STATEPROVINCENAME_FIELD_ID = 14;
    public const int POSTALCODE_FIELD_ID = 15;
    public const int COUNTRYREGIONNAME_FIELD_ID = 16;
    public const int DEMOGRAPHICS_FIELD_ID = 17;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VindividualcustomerReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Addresstype
    {
        get
        {
            return Reader.GetString(ADDRESSTYPE_FIELD_ID);
        }
    }

    public string Addressline1
    {
        get
        {
            return Reader.GetString(ADDRESSLINE1_FIELD_ID);
        }
    }

    public string? Addressline2
    {
        get
        {
            return Reader.GetNullableString(ADDRESSLINE2_FIELD_ID);
        }
    }

    public string City
    {
        get
        {
            return Reader.GetString(CITY_FIELD_ID);
        }
    }

    public string Stateprovincename
    {
        get
        {
            return Reader.GetString(STATEPROVINCENAME_FIELD_ID);
        }
    }

    public string Postalcode
    {
        get
        {
            return Reader.GetString(POSTALCODE_FIELD_ID);
        }
    }

    public string Countryregionname
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONNAME_FIELD_ID);
        }
    }

    public SqlXml? Demographics
    {
        get
        {
            return Reader.GetNullableSqlXml(DEMOGRAPHICS_FIELD_ID);
        }
    }


    public AdventureWorks.Sales.Types.VindividualcustomerDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.VindividualcustomerDataType(Businessentityid,
            Title,
            Firstname,
            Middlename,
            Lastname,
            Suffix,
            Phonenumber,
            Phonenumbertype,
            Emailaddress,
            Emailpromotion,
            Addresstype,
            Addressline1,
            Addressline2,
            City,
            Stateprovincename,
            Postalcode,
            Countryregionname,
            Demographics);
    }

    public List<AdventureWorks.Sales.Types.VindividualcustomerDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.VindividualcustomerDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
