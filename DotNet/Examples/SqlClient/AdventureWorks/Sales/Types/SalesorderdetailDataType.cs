using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Sales.Types;

public class SalesorderdetailDataType
{
    int _salesorderid = 0;
    int _salesorderdetailid = 0;
    string? _carriertrackingnumber;
    short _orderqty = 0;
    int _productid = 0;
    int _specialofferid = 0;
    decimal _unitprice = 0m;
    decimal _unitpricediscount = 0m;
    decimal _linetotal = 0m;
    Guid _rowguid;
    DateTime _modifieddate;

    public SalesorderdetailDataType( )
    {
    }

    public SalesorderdetailDataType(int salesorderid,
        int salesorderdetailid,
        string? carriertrackingnumber,
        short orderqty,
        int productid,
        int specialofferid,
        decimal unitprice,
        decimal unitpricediscount,
        decimal linetotal,
        Guid rowguid,
        DateTime modifieddate)
    {
        _salesorderid = salesorderid;
        _salesorderdetailid = salesorderdetailid;
        _carriertrackingnumber = carriertrackingnumber;
        _orderqty = orderqty;
        _productid = productid;
        _specialofferid = specialofferid;
        _unitprice = unitprice;
        _unitpricediscount = unitpricediscount;
        _linetotal = linetotal;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Salesorderid
    {
        get => _salesorderid;
        set => _salesorderid = value;
    }
    public int Salesorderdetailid
    {
        get => _salesorderdetailid;
        set => _salesorderdetailid = value;
    }
    public string? Carriertrackingnumber
    {
        get => _carriertrackingnumber;
        set => _carriertrackingnumber = value;
    }
    public short Orderqty
    {
        get => _orderqty;
        set => _orderqty = value;
    }
    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public int Specialofferid
    {
        get => _specialofferid;
        set => _specialofferid = value;
    }
    public decimal Unitprice
    {
        get => _unitprice;
        set => _unitprice = value;
    }
    public decimal Unitpricediscount
    {
        get => _unitpricediscount;
        set => _unitpricediscount = value;
    }
    public decimal Linetotal
    {
        get => _linetotal;
        set => _linetotal = value;
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
