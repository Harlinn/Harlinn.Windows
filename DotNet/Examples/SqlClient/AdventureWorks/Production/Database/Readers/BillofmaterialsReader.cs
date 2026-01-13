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

public class BillofmaterialsReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[BillOfMaterials]";
    public const string TableName = "BillOfMaterials";
    public const string ShortName = "b2";
    public const string Sql = """
        SELECT
          b2.[Billofmaterialsid],
          b2.[Productassemblyid],
          b2.[Componentid],
          b2.[Startdate],
          b2.[Enddate],
          b2.[Unitmeasurecode],
          b2.[Bomlevel],
          b2.[Perassemblyqty],
          b2.[Modifieddate]
        FROM
          [Production].[BillOfMaterials] b2
        """;

    public const int BILLOFMATERIALSID_FIELD_ID = 0;
    public const int PRODUCTASSEMBLYID_FIELD_ID = 1;
    public const int COMPONENTID_FIELD_ID = 2;
    public const int STARTDATE_FIELD_ID = 3;
    public const int ENDDATE_FIELD_ID = 4;
    public const int UNITMEASURECODE_FIELD_ID = 5;
    public const int BOMLEVEL_FIELD_ID = 6;
    public const int PERASSEMBLYQTY_FIELD_ID = 7;
    public const int MODIFIEDDATE_FIELD_ID = 8;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public BillofmaterialsReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Billofmaterialsid
    {
        get
        {
            return Reader.GetInt32(BILLOFMATERIALSID_FIELD_ID);
        }
    }

    public int? Productassemblyid
    {
        get
        {
            return Reader.GetNullableInt32(PRODUCTASSEMBLYID_FIELD_ID);
        }
    }

    public int Componentid
    {
        get
        {
            return Reader.GetInt32(COMPONENTID_FIELD_ID);
        }
    }

    public DateTime Startdate
    {
        get
        {
            return Reader.GetDateTime(STARTDATE_FIELD_ID);
        }
    }

    public DateTime? Enddate
    {
        get
        {
            return Reader.GetNullableDateTime(ENDDATE_FIELD_ID);
        }
    }

    public string Unitmeasurecode
    {
        get
        {
            return Reader.GetString(UNITMEASURECODE_FIELD_ID);
        }
    }

    public short Bomlevel
    {
        get
        {
            return Reader.GetInt16(BOMLEVEL_FIELD_ID);
        }
    }

    public decimal Perassemblyqty
    {
        get
        {
            return Reader.GetDecimal(PERASSEMBLYQTY_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.BillofmaterialsDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.BillofmaterialsDataType(Billofmaterialsid,
            Productassemblyid,
            Componentid,
            Startdate,
            Enddate,
            Unitmeasurecode,
            Bomlevel,
            Perassemblyqty,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.BillofmaterialsDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.BillofmaterialsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
