using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Sales.Types;

public class SalesterritoryhistoryDataType
{
    int _businessentityid = 0;
    int _territoryid = 0;
    DateTime _startdate;
    DateTime? _enddate;
    Guid _rowguid;
    DateTime _modifieddate;

    public SalesterritoryhistoryDataType( )
    {
    }

    public SalesterritoryhistoryDataType(int businessentityid,
        int territoryid,
        DateTime startdate,
        DateTime? enddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _territoryid = territoryid;
        _startdate = startdate;
        _enddate = enddate;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public int Territoryid
    {
        get => _territoryid;
        set => _territoryid = value;
    }
    public DateTime Startdate
    {
        get => _startdate;
        set => _startdate = value;
    }
    public DateTime? Enddate
    {
        get => _enddate;
        set => _enddate = value;
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
