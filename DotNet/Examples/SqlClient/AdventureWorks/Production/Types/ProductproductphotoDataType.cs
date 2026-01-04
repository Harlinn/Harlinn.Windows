using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class ProductproductphotoDataType
{
    int _productid = 0;
    int _productphotoid = 0;
    bool _primary = false;
    DateTime _modifieddate;

    public ProductproductphotoDataType( )
    {
    }

    public ProductproductphotoDataType(int productid,
        int productphotoid,
        bool primary,
        DateTime modifieddate)
    {
        _productid = productid;
        _productphotoid = productphotoid;
        _primary = primary;
        _modifieddate = modifieddate;
    }

    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public int Productphotoid
    {
        get => _productphotoid;
        set => _productphotoid = value;
    }
    public bool Primary
    {
        get => _primary;
        set => _primary = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
