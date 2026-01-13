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

public class CustomerReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[Customer]";
    public const string TableName = "Customer";
    public const string ShortName = "c6";
    public const string Sql = """
        SELECT
          c6.[Customerid],
          c6.[Personid],
          c6.[Storeid],
          c6.[Territoryid],
          c6.[Accountnumber],
          c6.[Rowguid],
          c6.[Modifieddate]
        FROM
          [Sales].[Customer] c6
        """;

    public const int CUSTOMERID_FIELD_ID = 0;
    public const int PERSONID_FIELD_ID = 1;
    public const int STOREID_FIELD_ID = 2;
    public const int TERRITORYID_FIELD_ID = 3;
    public const int ACCOUNTNUMBER_FIELD_ID = 4;
    public const int ROWGUID_FIELD_ID = 5;
    public const int MODIFIEDDATE_FIELD_ID = 6;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public CustomerReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Customerid
    {
        get
        {
            return Reader.GetInt32(CUSTOMERID_FIELD_ID);
        }
    }

    public int? Personid
    {
        get
        {
            return Reader.GetNullableInt32(PERSONID_FIELD_ID);
        }
    }

    public int? Storeid
    {
        get
        {
            return Reader.GetNullableInt32(STOREID_FIELD_ID);
        }
    }

    public int? Territoryid
    {
        get
        {
            return Reader.GetNullableInt32(TERRITORYID_FIELD_ID);
        }
    }

    public string Accountnumber
    {
        get
        {
            return Reader.GetString(ACCOUNTNUMBER_FIELD_ID);
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


    public AdventureWorks.Sales.Types.CustomerDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.CustomerDataType(Customerid,
            Personid,
            Storeid,
            Territoryid,
            Accountnumber,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.CustomerDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.CustomerDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
