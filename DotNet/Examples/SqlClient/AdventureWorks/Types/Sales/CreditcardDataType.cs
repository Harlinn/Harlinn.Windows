using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Sales;

public class CreditcardDataType
{
    int _creditcardid = 0;
    string _cardtype = string.Empty;
    string _cardnumber = string.Empty;
    byte _expmonth = 0;
    short _expyear = 0;
    DateTime _modifieddate;

    public CreditcardDataType( )
    {
    }

    public CreditcardDataType(int creditcardid,
        string cardtype,
        string cardnumber,
        byte expmonth,
        short expyear,
        DateTime modifieddate)
    {
        _creditcardid = creditcardid;
        _cardtype = cardtype;
        _cardnumber = cardnumber;
        _expmonth = expmonth;
        _expyear = expyear;
        _modifieddate = modifieddate;
    }

    public int Creditcardid
    {
        get => _creditcardid;
        set => _creditcardid = value;
    }
    public string Cardtype
    {
        get => _cardtype;
        set => _cardtype = value;
    }
    public string Cardnumber
    {
        get => _cardnumber;
        set => _cardnumber = value;
    }
    public byte Expmonth
    {
        get => _expmonth;
        set => _expmonth = value;
    }
    public short Expyear
    {
        get => _expyear;
        set => _expyear = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
