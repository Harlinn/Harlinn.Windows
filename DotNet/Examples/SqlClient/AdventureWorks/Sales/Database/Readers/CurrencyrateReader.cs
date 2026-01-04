using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Sales.Database.Readers;

public class CurrencyrateReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[CurrencyRate]";
    public const string TableName = "CurrencyRate";
    public const string ShortName = "c5";
    public const string Sql = """
        SELECT
          c5.[Currencyrateid],
          c5.[Currencyratedate],
          c5.[Fromcurrencycode],
          c5.[Tocurrencycode],
          c5.[Averagerate],
          c5.[Endofdayrate],
          c5.[Modifieddate]
        FROM
          [Sales].[CurrencyRate] c5
        """;

    public const int CURRENCYRATEID_FIELD_ID = 0;
    public const int CURRENCYRATEDATE_FIELD_ID = 1;
    public const int FROMCURRENCYCODE_FIELD_ID = 2;
    public const int TOCURRENCYCODE_FIELD_ID = 3;
    public const int AVERAGERATE_FIELD_ID = 4;
    public const int ENDOFDAYRATE_FIELD_ID = 5;
    public const int MODIFIEDDATE_FIELD_ID = 6;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public CurrencyrateReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Currencyrateid
    {
        get
        {
            return Reader.GetInt32(CURRENCYRATEID_FIELD_ID);
        }
    }

    public DateTime Currencyratedate
    {
        get
        {
            return Reader.GetDateTime(CURRENCYRATEDATE_FIELD_ID);
        }
    }

    public string Fromcurrencycode
    {
        get
        {
            return Reader.GetString(FROMCURRENCYCODE_FIELD_ID);
        }
    }

    public string Tocurrencycode
    {
        get
        {
            return Reader.GetString(TOCURRENCYCODE_FIELD_ID);
        }
    }

    public decimal Averagerate
    {
        get
        {
            return Reader.GetDecimal(AVERAGERATE_FIELD_ID);
        }
    }

    public decimal Endofdayrate
    {
        get
        {
            return Reader.GetDecimal(ENDOFDAYRATE_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Sales.Types.CurrencyrateDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.CurrencyrateDataType(Currencyrateid,
            Currencyratedate,
            Fromcurrencycode,
            Tocurrencycode,
            Averagerate,
            Endofdayrate,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.CurrencyrateDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.CurrencyrateDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
