using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

public class VsalespersonsalesbyfiscalyearsReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[vSalesPersonSalesByFiscalYears]";
    public const string TableName = "vSalesPersonSalesByFiscalYears";
    public const string ShortName = "v16";
    public const string Sql = """
        SELECT
          v16.[Salespersonid],
          v16.[Fullname],
          v16.[Jobtitle],
          v16.[Salesterritory],
          v16.[2002],
          v16.[2003],
          v16.[2004]
        FROM
          [Sales].[vSalesPersonSalesByFiscalYears] v16
        """;

    public const int SALESPERSONID_FIELD_ID = 0;
    public const int FULLNAME_FIELD_ID = 1;
    public const int JOBTITLE_FIELD_ID = 2;
    public const int SALESTERRITORY_FIELD_ID = 3;
    public const int D_2002_FIELD_ID = 4;
    public const int D_2003_FIELD_ID = 5;
    public const int D_2004_FIELD_ID = 6;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VsalespersonsalesbyfiscalyearsReader(SqlDataReader reader, bool ownsReader = false)
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

    public int? Salespersonid
    {
        get
        {
            return Reader.GetNullableInt32(SALESPERSONID_FIELD_ID);
        }
    }

    public string? Fullname
    {
        get
        {
            return Reader.GetNullableString(FULLNAME_FIELD_ID);
        }
    }

    public string Jobtitle
    {
        get
        {
            return Reader.GetString(JOBTITLE_FIELD_ID);
        }
    }

    public string Salesterritory
    {
        get
        {
            return Reader.GetString(SALESTERRITORY_FIELD_ID);
        }
    }

    public decimal? D_2002
    {
        get
        {
            return Reader.GetNullableDecimal(D_2002_FIELD_ID);
        }
    }

    public decimal? D_2003
    {
        get
        {
            return Reader.GetNullableDecimal(D_2003_FIELD_ID);
        }
    }

    public decimal? D_2004
    {
        get
        {
            return Reader.GetNullableDecimal(D_2004_FIELD_ID);
        }
    }


    public Types.Sales.VsalespersonsalesbyfiscalyearsDataType ToDataObject()
    {
        return new Types.Sales.VsalespersonsalesbyfiscalyearsDataType(Salespersonid,
            Fullname,
            Jobtitle,
            Salesterritory,
            D_2002,
            D_2003,
            D_2004);
    }

    public List<Types.Sales.VsalespersonsalesbyfiscalyearsDataType> ToList()
    {
        var list = new List<Types.Sales.VsalespersonsalesbyfiscalyearsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
