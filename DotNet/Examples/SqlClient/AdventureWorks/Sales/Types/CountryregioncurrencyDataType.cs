using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Sales.Types;

public class CountryregioncurrencyDataType
{
    string _countryregioncode = string.Empty;
    string _currencycode = string.Empty;
    DateTime _modifieddate;

    public CountryregioncurrencyDataType( )
    {
    }

    public CountryregioncurrencyDataType(string countryregioncode,
        string currencycode,
        DateTime modifieddate)
    {
        _countryregioncode = countryregioncode;
        _currencycode = currencycode;
        _modifieddate = modifieddate;
    }

    public string Countryregioncode
    {
        get => _countryregioncode;
        set => _countryregioncode = value;
    }
    public string Currencycode
    {
        get => _currencycode;
        set => _currencycode = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
