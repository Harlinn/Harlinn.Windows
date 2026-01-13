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

public class EmployeepayhistoryReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[EmployeePayHistory]";
    public const string TableName = "EmployeePayHistory";
    public const string ShortName = "e2";
    public const string Sql = """
        SELECT
          e2.[Businessentityid],
          e2.[Ratechangedate],
          e2.[Rate],
          e2.[Payfrequency],
          e2.[Modifieddate]
        FROM
          [HumanResources].[EmployeePayHistory] e2
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int RATECHANGEDATE_FIELD_ID = 1;
    public const int RATE_FIELD_ID = 2;
    public const int PAYFREQUENCY_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public EmployeepayhistoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public DateTime Ratechangedate
    {
        get
        {
            return Reader.GetDateTime(RATECHANGEDATE_FIELD_ID);
        }
    }

    public decimal Rate
    {
        get
        {
            return Reader.GetDecimal(RATE_FIELD_ID);
        }
    }

    public byte Payfrequency
    {
        get
        {
            return Reader.GetByte(PAYFREQUENCY_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.HumanResources.Types.EmployeepayhistoryDataType ToDataObject()
    {
        return new AdventureWorks.HumanResources.Types.EmployeepayhistoryDataType(Businessentityid,
            Ratechangedate,
            Rate,
            Payfrequency,
            Modifieddate);
    }

    public List<AdventureWorks.HumanResources.Types.EmployeepayhistoryDataType> ToList()
    {
        var list = new List<AdventureWorks.HumanResources.Types.EmployeepayhistoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
