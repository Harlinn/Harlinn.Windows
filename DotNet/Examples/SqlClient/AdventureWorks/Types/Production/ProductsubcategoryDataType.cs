using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Production;

public class ProductsubcategoryDataType
{
    int _productsubcategoryid = 0;
    int _productcategoryid = 0;
    string _name = string.Empty;
    Guid _rowguid;
    DateTime _modifieddate;

    public ProductsubcategoryDataType( )
    {
    }

    public ProductsubcategoryDataType(int productsubcategoryid,
        int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        _productsubcategoryid = productsubcategoryid;
        _productcategoryid = productcategoryid;
        _name = name;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Productsubcategoryid
    {
        get => _productsubcategoryid;
        set => _productsubcategoryid = value;
    }
    public int Productcategoryid
    {
        get => _productcategoryid;
        set => _productcategoryid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
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
