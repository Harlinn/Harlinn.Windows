using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class TransactionhistoryarchiveReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[TransactionHistoryArchive]";
    public const string TableName = "TransactionHistoryArchive";
    public const string ShortName = "t0";
    public const string Sql = """
        SELECT
          t0.[Transactionid],
          t0.[Productid],
          t0.[Referenceorderid],
          t0.[Referenceorderlineid],
          t0.[Transactiondate],
          t0.[Transactiontype],
          t0.[Quantity],
          t0.[Actualcost],
          t0.[Modifieddate]
        FROM
          [Production].[TransactionHistoryArchive] t0
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

    public TransactionhistoryarchiveReader(SqlDataReader reader, bool ownsReader = false)
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


    public Types.Production.TransactionhistoryarchiveDataType ToDataObject()
    {
        return new Types.Production.TransactionhistoryarchiveDataType(Transactionid,
            Productid,
            Referenceorderid,
            Referenceorderlineid,
            Transactiondate,
            Transactiontype,
            Quantity,
            Actualcost,
            Modifieddate);
    }

    public List<Types.Production.TransactionhistoryarchiveDataType> ToList()
    {
        var list = new List<Types.Production.TransactionhistoryarchiveDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
