using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Production;

public class ProductcategoryDataType
{
    int _productcategoryid = 0;
    string _name = string.Empty;
    Guid _rowguid;
    DateTime _modifieddate;

    public ProductcategoryDataType( )
    {
    }

    public ProductcategoryDataType(int productcategoryid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        _productcategoryid = productcategoryid;
        _name = name;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
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
