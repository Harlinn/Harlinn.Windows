/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.HumanResources.Database.Readers;

public class VemployeeReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[vEmployee]";
    public const string TableName = "vEmployee";
    public const string ShortName = "v";
    public const string Sql = """
        SELECT
          v.[Businessentityid],
          v.[Title],
          v.[Firstname],
          v.[Middlename],
          v.[Lastname],
          v.[Suffix],
          v.[Jobtitle],
          v.[Phonenumber],
          v.[Phonenumbertype],
          v.[Emailaddress],
          v.[Emailpromotion],
          v.[Addressline1],
          v.[Addressline2],
          v.[City],
          v.[Stateprovincename],
          v.[Postalcode],
          v.[Countryregionname],
          v.[Additionalcontactinfo]
        FROM
          [HumanResources].[vEmployee] v
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int TITLE_FIELD_ID = 1;
    public const int FIRSTNAME_FIELD_ID = 2;
    public const int MIDDLENAME_FIELD_ID = 3;
    public const int LASTNAME_FIELD_ID = 4;
    public const int SUFFIX_FIELD_ID = 5;
    public const int JOBTITLE_FIELD_ID = 6;
    public const int PHONENUMBER_FIELD_ID = 7;
    public const int PHONENUMBERTYPE_FIELD_ID = 8;
    public const int EMAILADDRESS_FIELD_ID = 9;
    public const int EMAILPROMOTION_FIELD_ID = 10;
    public const int ADDRESSLINE1_FIELD_ID = 11;
    public const int ADDRESSLINE2_FIELD_ID = 12;
    public const int CITY_FIELD_ID = 13;
    public const int STATEPROVINCENAME_FIELD_ID = 14;
    public const int POSTALCODE_FIELD_ID = 15;
    public const int COUNTRYREGIONNAME_FIELD_ID = 16;
    public const int ADDITIONALCONTACTINFO_FIELD_ID = 17;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VemployeeReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Jobtitle
    {
        get
        {
            return Reader.GetString(JOBTITLE_FIELD_ID);
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

    public SqlXml? Additionalcontactinfo
    {
        get
        {
            return Reader.GetNullableSqlXml(ADDITIONALCONTACTINFO_FIELD_ID);
        }
    }


    public AdventureWorks.HumanResources.Types.VemployeeDataType ToDataObject()
    {
        return new AdventureWorks.HumanResources.Types.VemployeeDataType(Businessentityid,
            Title,
            Firstname,
            Middlename,
            Lastname,
            Suffix,
            Jobtitle,
            Phonenumber,
            Phonenumbertype,
            Emailaddress,
            Emailpromotion,
            Addressline1,
            Addressline2,
            City,
            Stateprovincename,
            Postalcode,
            Countryregionname,
            Additionalcontactinfo);
    }

    public List<AdventureWorks.HumanResources.Types.VemployeeDataType> ToList()
    {
        var list = new List<AdventureWorks.HumanResources.Types.VemployeeDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
