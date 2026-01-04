using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Sales.Types;

public class SalesorderheadersalesreasonDataType
{
    int _salesorderid = 0;
    int _salesreasonid = 0;
    DateTime _modifieddate;

    public SalesorderheadersalesreasonDataType( )
    {
    }

    public SalesorderheadersalesreasonDataType(int salesorderid,
        int salesreasonid,
        DateTime modifieddate)
    {
        _salesorderid = salesorderid;
        _salesreasonid = salesreasonid;
        _modifieddate = modifieddate;
    }

    public int Salesorderid
    {
        get => _salesorderid;
        set => _salesorderid = value;
    }
    public int Salesreasonid
    {
        get => _salesreasonid;
        set => _salesreasonid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
