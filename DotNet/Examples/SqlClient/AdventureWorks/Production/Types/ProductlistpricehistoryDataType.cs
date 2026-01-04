using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class ProductlistpricehistoryDataType
{
    int _productid = 0;
    DateTime _startdate;
    DateTime? _enddate;
    decimal _listprice = 0m;
    DateTime _modifieddate;

    public ProductlistpricehistoryDataType( )
    {
    }

    public ProductlistpricehistoryDataType(int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal listprice,
        DateTime modifieddate)
    {
        _productid = productid;
        _startdate = startdate;
        _enddate = enddate;
        _listprice = listprice;
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
    public decimal Listprice
    {
        get => _listprice;
        set => _listprice = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
