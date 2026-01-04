using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Sales.Database.Readers;

public class SalesreasonReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[SalesReason]";
    public const string TableName = "SalesReason";
    public const string ShortName = "s8";
    public const string Sql = """
        SELECT
          s8.[Salesreasonid],
          s8.[Name],
          s8.[Reasontype],
          s8.[Modifieddate]
        FROM
          [Sales].[SalesReason] s8
        """;

    public const int SALESREASONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int REASONTYPE_FIELD_ID = 2;
    public const int MODIFIEDDATE_FIELD_ID = 3;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public SalesreasonReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Salesreasonid
    {
        get
        {
            return Reader.GetInt32(SALESREASONID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public string Reasontype
    {
        get
        {
            return Reader.GetString(REASONTYPE_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Sales.Types.SalesreasonDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.SalesreasonDataType(Salesreasonid,
            Name,
            Reasontype,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.SalesreasonDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.SalesreasonDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
