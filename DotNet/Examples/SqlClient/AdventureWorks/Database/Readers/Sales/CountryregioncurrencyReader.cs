using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

public class CountryregioncurrencyReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[CountryRegionCurrency]";
    public const string TableName = "CountryRegionCurrency";
    public const string ShortName = "c2";
    public const string Sql = """
        SELECT
          c2.[Countryregioncode],
          c2.[Currencycode],
          c2.[Modifieddate]
        FROM
          [Sales].[CountryRegionCurrency] c2
        """;

    public const int COUNTRYREGIONCODE_FIELD_ID = 0;
    public const int CURRENCYCODE_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public CountryregioncurrencyReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Countryregioncode
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONCODE_FIELD_ID);
        }
    }

    public string Currencycode
    {
        get
        {
            return Reader.GetString(CURRENCYCODE_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Sales.CountryregioncurrencyDataType ToDataObject()
    {
        return new Types.Sales.CountryregioncurrencyDataType(Countryregioncode,
            Currencycode,
            Modifieddate);
    }

    public List<Types.Sales.CountryregioncurrencyDataType> ToList()
    {
        var list = new List<Types.Sales.CountryregioncurrencyDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
