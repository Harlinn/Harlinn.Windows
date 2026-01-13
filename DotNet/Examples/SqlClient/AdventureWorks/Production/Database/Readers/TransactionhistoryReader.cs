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

public class TransactionhistoryReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[TransactionHistory]";
    public const string TableName = "TransactionHistory";
    public const string ShortName = "t";
    public const string Sql = """
        SELECT
          t.[Transactionid],
          t.[Productid],
          t.[Referenceorderid],
          t.[Referenceorderlineid],
          t.[Transactiondate],
          t.[Transactiontype],
          t.[Quantity],
          t.[Actualcost],
          t.[Modifieddate]
        FROM
          [Production].[TransactionHistory] t
        """;

    public const int TRANSACTIONID_FIELD_ID = 0;
    public const int PRODUCTID_FIELD_ID = 1;
    public const int REFERENCEORDERID_FIELD_ID = 2;
    public const int REFERENCEORDERLINEID_FIELD_ID = 3;
    public const int TRANSACTIONDATE_FIELD_ID = 4;
    public const int TRANSACTIONTYPE_FIELD_ID = 5;
    public const int QUANTITY_FIELD_ID = 6;
    public const int ACTUALCOST_FIELD_ID = 7;
    public const int MODIFIEDDATE_FIELD_ID = 8;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public TransactionhistoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Transactionid
    {
        get
        {
            return Reader.GetInt32(TRANSACTIONID_FIELD_ID);
        }
    }

    public int Productid
    {
        get
        {
            return Reader.GetInt32(PRODUCTID_FIELD_ID);
        }
    }

    public int Referenceorderid
    {
        get
        {
            return Reader.GetInt32(REFERENCEORDERID_FIELD_ID);
        }
    }

    public int Referenceorderlineid
    {
        get
        {
            return Reader.GetInt32(REFERENCEORDERLINEID_FIELD_ID);
        }
    }

    public DateTime Transactiondate
    {
        get
        {
            return Reader.GetDateTime(TRANSACTIONDATE_FIELD_ID);
        }
    }

    public string Transactiontype
    {
        get
        {
            return Reader.GetString(TRANSACTIONTYPE_FIELD_ID);
        }
    }

    public int Quantity
    {
        get
        {
            return Reader.GetInt32(QUANTITY_FIELD_ID);
        }
    }

    public decimal Actualcost
    {
        get
        {
            return Reader.GetDecimal(ACTUALCOST_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.TransactionhistoryDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.TransactionhistoryDataType(Transactionid,
            Productid,
            Referenceorderid,
            Referenceorderlineid,
            Transactiondate,
            Transactiontype,
            Quantity,
            Actualcost,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.TransactionhistoryDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.TransactionhistoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
