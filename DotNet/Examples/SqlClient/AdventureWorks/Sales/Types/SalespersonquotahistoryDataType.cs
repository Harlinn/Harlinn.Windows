using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Sales.Types;

public class SalespersonquotahistoryDataType
{
    int _businessentityid = 0;
    DateTime _quotadate;
    decimal _salesquota = 0m;
    Guid _rowguid;
    DateTime _modifieddate;

    public SalespersonquotahistoryDataType( )
    {
    }

    public SalespersonquotahistoryDataType(int businessentityid,
        DateTime quotadate,
        decimal salesquota,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _quotadate = quotadate;
        _salesquota = salesquota;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public DateTime Quotadate
    {
        get => _quotadate;
        set => _quotadate = value;
    }
    public decimal Salesquota
    {
        get => _salesquota;
        set => _salesquota = value;
    }
    public Guid Rowguid
    {
        get => _rowguid;
        set => _rowguid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
