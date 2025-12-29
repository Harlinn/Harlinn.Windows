using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

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


    public Types.Sales.SalesorderheadersalesreasonDataType ToDataObject()
    {
        return new Types.Sales.SalesorderheadersalesreasonDataType(Salesorderid,
            Salesreasonid,
            Modifieddate);
    }

    public List<Types.Sales.SalesorderheadersalesreasonDataType> ToList()
    {
        var list = new List<Types.Sales.SalesorderheadersalesreasonDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
