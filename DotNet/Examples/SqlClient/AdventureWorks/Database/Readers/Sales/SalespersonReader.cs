using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

public class SalespersonReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[SalesPerson]";
    public const string TableName = "SalesPerson";
    public const string ShortName = "s6";
    public const string Sql = """
        SELECT
          s6.[Businessentityid],
          s6.[Territoryid],
          s6.[Salesquota],
          s6.[Bonus],
          s6.[Commissionpct],
          s6.[Salesytd],
          s6.[Saleslastyear],
          s6.[Rowguid],
          s6.[Modifieddate]
        FROM
          [Sales].[SalesPerson] s6
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int TERRITORYID_FIELD_ID = 1;
    public const int SALESQUOTA_FIELD_ID = 2;
    public const int BONUS_FIELD_ID = 3;
    public const int COMMISSIONPCT_FIELD_ID = 4;
    public const int SALESYTD_FIELD_ID = 5;
    public const int SALESLASTYEAR_FIELD_ID = 6;
    public const int ROWGUID_FIELD_ID = 7;
    public const int MODIFIEDDATE_FIELD_ID = 8;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public SalespersonReader(SqlDataReader reader, bool ownsReader = false)
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

    public int? Territoryid
    {
        get
        {
            return Reader.GetNullableInt32(TERRITORYID_FIELD_ID);
        }
    }

    public decimal? Salesquota
    {
        get
        {
            return Reader.GetNullableDecimal(SALESQUOTA_FIELD_ID);
        }
    }

    public decimal Bonus
    {
        get
        {
            return Reader.GetDecimal(BONUS_FIELD_ID);
        }
    }

    public decimal Commissionpct
    {
        get
        {
            return Reader.GetDecimal(COMMISSIONPCT_FIELD_ID);
        }
    }

    public decimal Salesytd
    {
        get
        {
            return Reader.GetDecimal(SALESYTD_FIELD_ID);
        }
    }

    public decimal Saleslastyear
    {
        get
        {
            return Reader.GetDecimal(SALESLASTYEAR_FIELD_ID);
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


    public Types.Sales.SalespersonDataType ToDataObject()
    {
        return new Types.Sales.SalespersonDataType(Businessentityid,
            Territoryid,
            Salesquota,
            Bonus,
            Commissionpct,
            Salesytd,
            Saleslastyear,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Sales.SalespersonDataType> ToList()
    {
        var list = new List<Types.Sales.SalespersonDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
