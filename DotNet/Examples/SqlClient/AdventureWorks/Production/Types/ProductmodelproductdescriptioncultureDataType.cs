using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class ProductmodelproductdescriptioncultureDataType
{
    int _productmodelid = 0;
    int _productdescriptionid = 0;
    string _cultureid = string.Empty;
    DateTime _modifieddate;

    public ProductmodelproductdescriptioncultureDataType( )
    {
    }

    public ProductmodelproductdescriptioncultureDataType(int productmodelid,
        int productdescriptionid,
        string cultureid,
        DateTime modifieddate)
    {
        _productmodelid = productmodelid;
        _productdescriptionid = productdescriptionid;
        _cultureid = cultureid;
        _modifieddate = modifieddate;
    }

    public int Productmodelid
    {
        get => _productmodelid;
        set => _productmodelid = value;
    }
    public int Productdescriptionid
    {
        get => _productdescriptionid;
        set => _productdescriptionid = value;
    }
    public string Cultureid
    {
        get => _cultureid;
        set => _cultureid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
