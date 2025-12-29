using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Sales;

public class ShoppingcartitemDataType
{
    int _shoppingcartitemid = 0;
    string _shoppingcartid = string.Empty;
    int _quantity = 0;
    int _productid = 0;
    DateTime _datecreated;
    DateTime _modifieddate;

    public ShoppingcartitemDataType( )
    {
    }

    public ShoppingcartitemDataType(int shoppingcartitemid,
        string shoppingcartid,
        int quantity,
        int productid,
        DateTime datecreated,
        DateTime modifieddate)
    {
        _shoppingcartitemid = shoppingcartitemid;
        _shoppingcartid = shoppingcartid;
        _quantity = quantity;
        _productid = productid;
        _datecreated = datecreated;
        _modifieddate = modifieddate;
    }

    public int Shoppingcartitemid
    {
        get => _shoppingcartitemid;
        set => _shoppingcartitemid = value;
    }
    public string Shoppingcartid
    {
        get => _shoppingcartid;
        set => _shoppingcartid = value;
    }
    public int Quantity
    {
        get => _quantity;
        set => _quantity = value;
    }
    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public DateTime Datecreated
    {
        get => _datecreated;
        set => _datecreated = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
