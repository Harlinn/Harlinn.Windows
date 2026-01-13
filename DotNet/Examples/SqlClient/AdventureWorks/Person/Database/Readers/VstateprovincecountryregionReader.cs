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

public class VstateprovincecountryregionReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[vStateProvinceCountryRegion]";
    public const string TableName = "vStateProvinceCountryRegion";
    public const string ShortName = "v6";
    public const string Sql = """
        SELECT
          v6.[Stateprovinceid],
          v6.[Stateprovincecode],
          v6.[Isonlystateprovinceflag],
          v6.[Stateprovincename],
          v6.[Territoryid],
          v6.[Countryregioncode],
          v6.[Countryregionname]
        FROM
          [Person].[vStateProvinceCountryRegion] v6
        """;

    public const int STATEPROVINCEID_FIELD_ID = 0;
    public const int STATEPROVINCECODE_FIELD_ID = 1;
    public const int ISONLYSTATEPROVINCEFLAG_FIELD_ID = 2;
    public const int STATEPROVINCENAME_FIELD_ID = 3;
    public const int TERRITORYID_FIELD_ID = 4;
    public const int COUNTRYREGIONCODE_FIELD_ID = 5;
    public const int COUNTRYREGIONNAME_FIELD_ID = 6;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VstateprovincecountryregionReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Stateprovinceid
    {
        get
        {
            return Reader.GetInt32(STATEPROVINCEID_FIELD_ID);
        }
    }

    public string Stateprovincecode
    {
        get
        {
            return Reader.GetString(STATEPROVINCECODE_FIELD_ID);
        }
    }

    public bool Isonlystateprovinceflag
    {
        get
        {
            return Reader.GetBoolean(ISONLYSTATEPROVINCEFLAG_FIELD_ID);
        }
    }

    public string Stateprovincename
    {
        get
        {
            return Reader.GetString(STATEPROVINCENAME_FIELD_ID);
        }
    }

    public int Territoryid
    {
        get
        {
            return Reader.GetInt32(TERRITORYID_FIELD_ID);
        }
    }

    public string Countryregioncode
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONCODE_FIELD_ID);
        }
    }

    public string Countryregionname
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONNAME_FIELD_ID);
        }
    }


    public AdventureWorks.Person.Types.VstateprovincecountryregionDataType ToDataObject()
    {
        return new AdventureWorks.Person.Types.VstateprovincecountryregionDataType(Stateprovinceid,
            Stateprovincecode,
            Isonlystateprovinceflag,
            Stateprovincename,
            Territoryid,
            Countryregioncode,
            Countryregionname);
    }

    public List<AdventureWorks.Person.Types.VstateprovincecountryregionDataType> ToList()
    {
        var list = new List<AdventureWorks.Person.Types.VstateprovincecountryregionDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
