using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Sales.Database.Readers;

public class SalespersonquotahistoryReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[SalesPersonQuotaHistory]";
    public const string TableName = "SalesPersonQuotaHistory";
    public const string ShortName = "s7";
    public const string Sql = """
        SELECT
          s7.[Businessentityid],
          s7.[Quotadate],
          s7.[Salesquota],
          s7.[Rowguid],
          s7.[Modifieddate]
        FROM
          [Sales].[SalesPersonQuotaHistory] s7
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int QUOTADATE_FIELD_ID = 1;
    public const int SALESQUOTA_FIELD_ID = 2;
    public const int ROWGUID_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public SalespersonquotahistoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public DateTime Quotadate
    {
        get
        {
            return Reader.GetDateTime(QUOTADATE_FIELD_ID);
        }
    }

    public decimal Salesquota
    {
        get
        {
            return Reader.GetDecimal(SALESQUOTA_FIELD_ID);
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


    public AdventureWorks.Sales.Types.SalespersonquotahistoryDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.SalespersonquotahistoryDataType(Businessentityid,
            Quotadate,
            Salesquota,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.SalespersonquotahistoryDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.SalespersonquotahistoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
