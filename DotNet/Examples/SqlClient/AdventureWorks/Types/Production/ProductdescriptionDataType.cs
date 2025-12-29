using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Production;

public class ProductdescriptionDataType
{
    int _productdescriptionid = 0;
    string _description = string.Empty;
    Guid _rowguid;
    DateTime _modifieddate;

    public ProductdescriptionDataType( )
    {
    }

    public ProductdescriptionDataType(int productdescriptionid,
        string description,
        Guid rowguid,
        DateTime modifieddate)
    {
        _productdescriptionid = productdescriptionid;
        _description = description;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Productdescriptionid
    {
        get => _productdescriptionid;
        set => _productdescriptionid = value;
    }
    public string Description
    {
        get => _description;
        set => _description = value;
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
