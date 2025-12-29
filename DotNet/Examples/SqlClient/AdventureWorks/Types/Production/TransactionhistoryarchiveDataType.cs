using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Production;

public class TransactionhistoryarchiveDataType
{
    int _transactionid = 0;
    int _productid = 0;
    int _referenceorderid = 0;
    int _referenceorderlineid = 0;
    DateTime _transactiondate;
    string _transactiontype = string.Empty;
    int _quantity = 0;
    decimal _actualcost = 0m;
    DateTime _modifieddate;

    public TransactionhistoryarchiveDataType( )
    {
    }

    public TransactionhistoryarchiveDataType(int transactionid,
        int productid,
        int referenceorderid,
        int referenceorderlineid,
        DateTime transactiondate,
        string transactiontype,
        int quantity,
        decimal actualcost,
        DateTime modifieddate)
    {
        _transactionid = transactionid;
        _productid = productid;
        _referenceorderid = referenceorderid;
        _referenceorderlineid = referenceorderlineid;
        _transactiondate = transactiondate;
        _transactiontype = transactiontype;
        _quantity = quantity;
        _actualcost = actualcost;
        _modifieddate = modifieddate;
    }

    public int Transactionid
    {
        get => _transactionid;
        set => _transactionid = value;
    }
    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public int Referenceorderid
    {
        get => _referenceorderid;
        set => _referenceorderid = value;
    }
    public int Referenceorderlineid
    {
        get => _referenceorderlineid;
        set => _referenceorderlineid = value;
    }
    public DateTime Transactiondate
    {
        get => _transactiondate;
        set => _transactiondate = value;
    }
    public string Transactiontype
    {
        get => _transactiontype;
        set => _transactiontype = value;
    }
    public int Quantity
    {
        get => _quantity;
        set => _quantity = value;
    }
    public decimal Actualcost
    {
        get => _actualcost;
        set => _actualcost = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
