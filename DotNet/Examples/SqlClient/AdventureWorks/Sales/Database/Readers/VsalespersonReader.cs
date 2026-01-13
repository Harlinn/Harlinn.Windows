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

namespace AdventureWorks.Sales.Database.Readers;

public class VsalespersonReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[vSalesPerson]";
    public const string TableName = "vSalesPerson";
    public const string ShortName = "v15";
    public const string Sql = """
        SELECT
          v15.[Businessentityid],
          v15.[Title],
          v15.[Firstname],
          v15.[Middlename],
          v15.[Lastname],
          v15.[Suffix],
          v15.[Jobtitle],
          v15.[Phonenumber],
          v15.[Phonenumbertype],
          v15.[Emailaddress],
          v15.[Emailpromotion],
          v15.[Addressline1],
          v15.[Addressline2],
          v15.[City],
          v15.[Stateprovincename],
          v15.[Postalcode],
          v15.[Countryregionname],
          v15.[Territoryname],
          v15.[Territorygroup],
          v15.[Salesquota],
          v15.[Salesytd],
          v15.[Saleslastyear]
        FROM
          [Sales].[vSalesPerson] v15
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
    public const int TERRITORYNAME_FIELD_ID = 17;
    public const int TERRITORYGROUP_FIELD_ID = 18;
    public const int SALESQUOTA_FIELD_ID = 19;
    public const int SALESYTD_FIELD_ID = 20;
    public const int SALESLASTYEAR_FIELD_ID = 21;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VsalespersonReader(SqlDataReader reader, bool ownsReader = false)
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

    public string? Territoryname
    {
        get
        {
            return Reader.GetNullableString(TERRITORYNAME_FIELD_ID);
        }
    }

    public string? Territorygroup
    {
        get
        {
            return Reader.GetNullableString(TERRITORYGROUP_FIELD_ID);
        }
    }

    public decimal? Salesquota
    {
        get
        {
            return Reader.GetNullableDecimal(SALESQUOTA_FIELD_ID);
        }
    }

    public decimal Salesytd
    {
        get
        {
            return Reader.GetDecimal(SALESYTD_FIELD_ID);
        }
    }

    public decimal Saleslastyear
    {
        get
        {
            return Reader.GetDecimal(SALESLASTYEAR_FIELD_ID);
        }
    }


    public AdventureWorks.Sales.Types.VsalespersonDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.VsalespersonDataType(Businessentityid,
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
            Territoryname,
            Territorygroup,
            Salesquota,
            Salesytd,
            Saleslastyear);
    }

    public List<AdventureWorks.Sales.Types.VsalespersonDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.VsalespersonDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
