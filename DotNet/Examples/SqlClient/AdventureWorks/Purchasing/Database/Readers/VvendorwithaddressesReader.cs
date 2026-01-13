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

namespace AdventureWorks.Purchasing.Database.Readers;

public class VvendorwithaddressesReader : IDisposable
{
    public const string QualifiedTableName = "[Purchasing].[vVendorWithAddresses]";
    public const string TableName = "vVendorWithAddresses";
    public const string ShortName = "v11";
    public const string Sql = """
        SELECT
          v11.[Businessentityid],
          v11.[Name],
          v11.[Addresstype],
          v11.[Addressline1],
          v11.[Addressline2],
          v11.[City],
          v11.[Stateprovincename],
          v11.[Postalcode],
          v11.[Countryregionname]
        FROM
          [Purchasing].[vVendorWithAddresses] v11
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int ADDRESSTYPE_FIELD_ID = 2;
    public const int ADDRESSLINE1_FIELD_ID = 3;
    public const int ADDRESSLINE2_FIELD_ID = 4;
    public const int CITY_FIELD_ID = 5;
    public const int STATEPROVINCENAME_FIELD_ID = 6;
    public const int POSTALCODE_FIELD_ID = 7;
    public const int COUNTRYREGIONNAME_FIELD_ID = 8;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VvendorwithaddressesReader(SqlDataReader reader, bool ownsReader = false)
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


    public AdventureWorks.Purchasing.Types.VvendorwithaddressesDataType ToDataObject()
    {
        return new AdventureWorks.Purchasing.Types.VvendorwithaddressesDataType(Businessentityid,
            Name,
            Addresstype,
            Addressline1,
            Addressline2,
            City,
            Stateprovincename,
            Postalcode,
            Countryregionname);
    }

    public List<AdventureWorks.Purchasing.Types.VvendorwithaddressesDataType> ToList()
    {
        var list = new List<AdventureWorks.Purchasing.Types.VvendorwithaddressesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
