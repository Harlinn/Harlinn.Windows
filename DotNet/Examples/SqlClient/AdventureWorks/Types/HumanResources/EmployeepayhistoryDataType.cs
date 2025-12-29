using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.HumanResources;

public class EmployeepayhistoryDataType
{
    int _businessentityid = 0;
    DateTime _ratechangedate;
    decimal _rate = 0m;
    byte _payfrequency = 0;
    DateTime _modifieddate;

    public EmployeepayhistoryDataType( )
    {
    }

    public EmployeepayhistoryDataType(int businessentityid,
        DateTime ratechangedate,
        decimal rate,
        byte payfrequency,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _ratechangedate = ratechangedate;
        _rate = rate;
        _payfrequency = payfrequency;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public DateTime Ratechangedate
    {
        get => _ratechangedate;
        set => _ratechangedate = value;
    }
    public decimal Rate
    {
        get => _rate;
        set => _rate = value;
    }
    public byte Payfrequency
    {
        get => _payfrequency;
        set => _payfrequency = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
