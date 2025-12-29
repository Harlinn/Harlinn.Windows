using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Sales;

public class SalespersonDataType
{
    int _businessentityid = 0;
    int? _territoryid;
    decimal? _salesquota;
    decimal _bonus = 0m;
    decimal _commissionpct = 0m;
    decimal _salesytd = 0m;
    decimal _saleslastyear = 0m;
    Guid _rowguid;
    DateTime _modifieddate;

    public SalespersonDataType( )
    {
    }

    public SalespersonDataType(int businessentityid,
        int? territoryid,
        decimal? salesquota,
        decimal bonus,
        decimal commissionpct,
        decimal salesytd,
        decimal saleslastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _territoryid = territoryid;
        _salesquota = salesquota;
        _bonus = bonus;
        _commissionpct = commissionpct;
        _salesytd = salesytd;
        _saleslastyear = saleslastyear;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public int? Territoryid
    {
        get => _territoryid;
        set => _territoryid = value;
    }
    public decimal? Salesquota
    {
        get => _salesquota;
        set => _salesquota = value;
    }
    public decimal Bonus
    {
        get => _bonus;
        set => _bonus = value;
    }
    public decimal Commissionpct
    {
        get => _commissionpct;
        set => _commissionpct = value;
    }
    public decimal Salesytd
    {
        get => _salesytd;
        set => _salesytd = value;
    }
    public decimal Saleslastyear
    {
        get => _saleslastyear;
        set => _saleslastyear = value;
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
