using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Sales.Types;

public class SpecialofferproductDataType
{
    int _specialofferid = 0;
    int _productid = 0;
    Guid _rowguid;
    DateTime _modifieddate;

    public SpecialofferproductDataType( )
    {
    }

    public SpecialofferproductDataType(int specialofferid,
        int productid,
        Guid rowguid,
        DateTime modifieddate)
    {
        _specialofferid = specialofferid;
        _productid = productid;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Specialofferid
    {
        get => _specialofferid;
        set => _specialofferid = value;
    }
    public int Productid
    {
        get => _productid;
        set => _productid = value;
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
