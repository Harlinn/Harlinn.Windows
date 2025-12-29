using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Production;

public class VproductanddescriptionDataType
{
    readonly int _productid = 0;
    readonly string _name = string.Empty;
    readonly string _productmodel = string.Empty;
    readonly string _cultureid = string.Empty;
    readonly string _description = string.Empty;

    public VproductanddescriptionDataType( )
    {
    }

    public VproductanddescriptionDataType(int productid,
        string name,
        string productmodel,
        string cultureid,
        string description)
    {
        _productid = productid;
        _name = name;
        _productmodel = productmodel;
        _cultureid = cultureid;
        _description = description;
    }

    public int Productid => _productid;
    public string Name => _name;
    public string Productmodel => _productmodel;
    public string Cultureid => _cultureid;
    public string Description => _description;
}
