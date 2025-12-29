using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Production;

public class ProductcosthistoryDataType
{
    int _productid = 0;
    DateTime _startdate;
    DateTime? _enddate;
    decimal _standardcost = 0m;
    DateTime _modifieddate;

    public ProductcosthistoryDataType( )
    {
    }

    public ProductcosthistoryDataType(int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal standardcost,
        DateTime modifieddate)
    {
        _productid = productid;
        _startdate = startdate;
        _enddate = enddate;
        _standardcost = standardcost;
        _modifieddate = modifieddate;
    }

    public int Productid
    {
        get => _productid;
        set => _productid = value;
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
    public decimal Standardcost
    {
        get => _standardcost;
        set => _standardcost = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
