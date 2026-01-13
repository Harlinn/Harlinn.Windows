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

namespace AdventureWorks.Person.Database.Readers;

public class AddressReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[Address]";
    public const string TableName = "Address";
    public const string ShortName = "a0";
    public const string Sql = """
        SELECT
          a0.[Addressid],
          a0.[Addressline1],
          a0.[Addressline2],
          a0.[City],
          a0.[Stateprovinceid],
          a0.[Postalcode],
          a0.[Spatiallocation],
          a0.[Rowguid],
          a0.[Modifieddate]
        FROM
          [Person].[Address] a0
        """;

    public const int ADDRESSID_FIELD_ID = 0;
    public const int ADDRESSLINE1_FIELD_ID = 1;
    public const int ADDRESSLINE2_FIELD_ID = 2;
    public const int CITY_FIELD_ID = 3;
    public const int STATEPROVINCEID_FIELD_ID = 4;
    public const int POSTALCODE_FIELD_ID = 5;
    public const int SPATIALLOCATION_FIELD_ID = 6;
    public const int ROWGUID_FIELD_ID = 7;
    public const int MODIFIEDDATE_FIELD_ID = 8;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public AddressReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Addressid
    {
        get
        {
            return Reader.GetInt32(ADDRESSID_FIELD_ID);
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

    public int Stateprovinceid
    {
        get
        {
            return Reader.GetInt32(STATEPROVINCEID_FIELD_ID);
        }
    }

    public string Postalcode
    {
        get
        {
            return Reader.GetString(POSTALCODE_FIELD_ID);
        }
    }

    public SqlGeography? Spatiallocation
    {
        get
        {
            return Reader.GetNullableSqlGeography(SPATIALLOCATION_FIELD_ID);
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


    public AdventureWorks.Person.Types.AddressDataType ToDataObject()
    {
        return new AdventureWorks.Person.Types.AddressDataType(Addressid,
            Addressline1,
            Addressline2,
            City,
            Stateprovinceid,
            Postalcode,
            Spatiallocation,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Person.Types.AddressDataType> ToList()
    {
        var list = new List<AdventureWorks.Person.Types.AddressDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
