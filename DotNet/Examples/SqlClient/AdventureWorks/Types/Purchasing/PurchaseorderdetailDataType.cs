using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Purchasing;

public class PurchaseorderdetailDataType
{
    int _purchaseorderid = 0;
    int _purchaseorderdetailid = 0;
    DateTime _duedate;
    short _orderqty = 0;
    int _productid = 0;
    decimal _unitprice = 0m;
    decimal _linetotal = 0m;
    decimal _receivedqty = 0m;
    decimal _rejectedqty = 0m;
    decimal _stockedqty = 0m;
    DateTime _modifieddate;

    public PurchaseorderdetailDataType( )
    {
    }

    public PurchaseorderdetailDataType(int purchaseorderid,
        int purchaseorderdetailid,
        DateTime duedate,
        short orderqty,
        int productid,
        decimal unitprice,
        decimal linetotal,
        decimal receivedqty,
        decimal rejectedqty,
        decimal stockedqty,
        DateTime modifieddate)
    {
        _purchaseorderid = purchaseorderid;
        _purchaseorderdetailid = purchaseorderdetailid;
        _duedate = duedate;
        _orderqty = orderqty;
        _productid = productid;
        _unitprice = unitprice;
        _linetotal = linetotal;
        _receivedqty = receivedqty;
        _rejectedqty = rejectedqty;
        _stockedqty = stockedqty;
        _modifieddate = modifieddate;
    }

    public int Purchaseorderid
    {
        get => _purchaseorderid;
        set => _purchaseorderid = value;
    }
    public int Purchaseorderdetailid
    {
        get => _purchaseorderdetailid;
        set => _purchaseorderdetailid = value;
    }
    public DateTime Duedate
    {
        get => _duedate;
        set => _duedate = value;
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
    public decimal Unitprice
    {
        get => _unitprice;
        set => _unitprice = value;
    }
    public decimal Linetotal
    {
        get => _linetotal;
        set => _linetotal = value;
    }
    public decimal Receivedqty
    {
        get => _receivedqty;
        set => _receivedqty = value;
    }
    public decimal Rejectedqty
    {
        get => _rejectedqty;
        set => _rejectedqty = value;
    }
    public decimal Stockedqty
    {
        get => _stockedqty;
        set => _stockedqty = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
