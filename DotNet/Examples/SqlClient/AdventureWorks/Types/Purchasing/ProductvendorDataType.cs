using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Purchasing;

public class ProductvendorDataType
{
    int _productid = 0;
    int _businessentityid = 0;
    int _averageleadtime = 0;
    decimal _standardprice = 0m;
    decimal? _lastreceiptcost;
    DateTime? _lastreceiptdate;
    int _minorderqty = 0;
    int _maxorderqty = 0;
    int? _onorderqty;
    string _unitmeasurecode = string.Empty;
    DateTime _modifieddate;

    public ProductvendorDataType( )
    {
    }

    public ProductvendorDataType(int productid,
        int businessentityid,
        int averageleadtime,
        decimal standardprice,
        decimal? lastreceiptcost,
        DateTime? lastreceiptdate,
        int minorderqty,
        int maxorderqty,
        int? onorderqty,
        string unitmeasurecode,
        DateTime modifieddate)
    {
        _productid = productid;
        _businessentityid = businessentityid;
        _averageleadtime = averageleadtime;
        _standardprice = standardprice;
        _lastreceiptcost = lastreceiptcost;
        _lastreceiptdate = lastreceiptdate;
        _minorderqty = minorderqty;
        _maxorderqty = maxorderqty;
        _onorderqty = onorderqty;
        _unitmeasurecode = unitmeasurecode;
        _modifieddate = modifieddate;
    }

    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public int Averageleadtime
    {
        get => _averageleadtime;
        set => _averageleadtime = value;
    }
    public decimal Standardprice
    {
        get => _standardprice;
        set => _standardprice = value;
    }
    public decimal? Lastreceiptcost
    {
        get => _lastreceiptcost;
        set => _lastreceiptcost = value;
    }
    public DateTime? Lastreceiptdate
    {
        get => _lastreceiptdate;
        set => _lastreceiptdate = value;
    }
    public int Minorderqty
    {
        get => _minorderqty;
        set => _minorderqty = value;
    }
    public int Maxorderqty
    {
        get => _maxorderqty;
        set => _maxorderqty = value;
    }
    public int? Onorderqty
    {
        get => _onorderqty;
        set => _onorderqty = value;
    }
    public string Unitmeasurecode
    {
        get => _unitmeasurecode;
        set => _unitmeasurecode = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
