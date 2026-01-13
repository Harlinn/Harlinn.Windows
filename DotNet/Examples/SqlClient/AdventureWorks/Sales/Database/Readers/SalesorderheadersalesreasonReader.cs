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

public class SalesorderheadersalesreasonReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[SalesOrderHeaderSalesReason]";
    public const string TableName = "SalesOrderHeaderSalesReason";
    public const string ShortName = "s5";
    public const string Sql = """
        SELECT
          s5.[Salesorderid],
          s5.[Salesreasonid],
          s5.[Modifieddate]
        FROM
          [Sales].[SalesOrderHeaderSalesReason] s5
        """;

    public const int SALESORDERID_FIELD_ID = 0;
    public const int SALESREASONID_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public SalesorderheadersalesreasonReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Salesorderid
    {
        get
        {
            return Reader.GetInt32(SALESORDERID_FIELD_ID);
        }
    }

    public int Salesreasonid
    {
        get
        {
            return Reader.GetInt32(SALESREASONID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Sales.Types.SalesorderheadersalesreasonDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.SalesorderheadersalesreasonDataType(Salesorderid,
            Salesreasonid,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.SalesorderheadersalesreasonDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.SalesorderheadersalesreasonDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
