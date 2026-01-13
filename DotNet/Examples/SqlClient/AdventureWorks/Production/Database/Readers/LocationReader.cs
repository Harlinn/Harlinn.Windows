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

namespace AdventureWorks.Production.Database.Readers;

public class LocationReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[Location]";
    public const string TableName = "Location";
    public const string ShortName = "l";
    public const string Sql = """
        SELECT
          l.[Locationid],
          l.[Name],
          l.[Costrate],
          l.[Availability],
          l.[Modifieddate]
        FROM
          [Production].[Location] l
        """;

    public const int LOCATIONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int COSTRATE_FIELD_ID = 2;
    public const int AVAILABILITY_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public LocationReader(SqlDataReader reader, bool ownsReader = false)
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

    public short Locationid
    {
        get
        {
            return Reader.GetInt16(LOCATIONID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public decimal Costrate
    {
        get
        {
            return Reader.GetDecimal(COSTRATE_FIELD_ID);
        }
    }

    public decimal Availability
    {
        get
        {
            return Reader.GetDecimal(AVAILABILITY_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.LocationDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.LocationDataType(Locationid,
            Name,
            Costrate,
            Availability,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.LocationDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.LocationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
