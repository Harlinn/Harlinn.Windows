using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Sales;

public class CurrencyrateDataType
{
    int _currencyrateid = 0;
    DateTime _currencyratedate;
    string _fromcurrencycode = string.Empty;
    string _tocurrencycode = string.Empty;
    decimal _averagerate = 0m;
    decimal _endofdayrate = 0m;
    DateTime _modifieddate;

    public CurrencyrateDataType( )
    {
    }

    public CurrencyrateDataType(int currencyrateid,
        DateTime currencyratedate,
        string fromcurrencycode,
        string tocurrencycode,
        decimal averagerate,
        decimal endofdayrate,
        DateTime modifieddate)
    {
        _currencyrateid = currencyrateid;
        _currencyratedate = currencyratedate;
        _fromcurrencycode = fromcurrencycode;
        _tocurrencycode = tocurrencycode;
        _averagerate = averagerate;
        _endofdayrate = endofdayrate;
        _modifieddate = modifieddate;
    }

    public int Currencyrateid
    {
        get => _currencyrateid;
        set => _currencyrateid = value;
    }
    public DateTime Currencyratedate
    {
        get => _currencyratedate;
        set => _currencyratedate = value;
    }
    public string Fromcurrencycode
    {
        get => _fromcurrencycode;
        set => _fromcurrencycode = value;
    }
    public string Tocurrencycode
    {
        get => _tocurrencycode;
        set => _tocurrencycode = value;
    }
    public decimal Averagerate
    {
        get => _averagerate;
        set => _averagerate = value;
    }
    public decimal Endofdayrate
    {
        get => _endofdayrate;
        set => _endofdayrate = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
