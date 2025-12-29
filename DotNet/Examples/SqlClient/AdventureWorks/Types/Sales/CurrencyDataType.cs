using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Sales;

public class CurrencyDataType
{
    string _currencycode = string.Empty;
    string _name = string.Empty;
    DateTime _modifieddate;

    public CurrencyDataType( )
    {
    }

    public CurrencyDataType(string currencycode,
        string name,
        DateTime modifieddate)
    {
        _currencycode = currencycode;
        _name = name;
        _modifieddate = modifieddate;
    }

    public string Currencycode
    {
        get => _currencycode;
        set => _currencycode = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
