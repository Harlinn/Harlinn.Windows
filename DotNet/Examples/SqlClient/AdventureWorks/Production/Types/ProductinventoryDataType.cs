using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class ProductinventoryDataType
{
    int _productid = 0;
    short _locationid = 0;
    string _shelf = string.Empty;
    byte _bin = 0;
    short _quantity = 0;
    Guid _rowguid;
    DateTime _modifieddate;

    public ProductinventoryDataType( )
    {
    }

    public ProductinventoryDataType(int productid,
        short locationid,
        string shelf,
        byte bin,
        short quantity,
        Guid rowguid,
        DateTime modifieddate)
    {
        _productid = productid;
        _locationid = locationid;
        _shelf = shelf;
        _bin = bin;
        _quantity = quantity;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public short Locationid
    {
        get => _locationid;
        set => _locationid = value;
    }
    public string Shelf
    {
        get => _shelf;
        set => _shelf = value;
    }
    public byte Bin
    {
        get => _bin;
        set => _bin = value;
    }
    public short Quantity
    {
        get => _quantity;
        set => _quantity = value;
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
