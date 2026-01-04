using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class ProductmodelillustrationDataType
{
    int _productmodelid = 0;
    int _illustrationid = 0;
    DateTime _modifieddate;

    public ProductmodelillustrationDataType( )
    {
    }

    public ProductmodelillustrationDataType(int productmodelid,
        int illustrationid,
        DateTime modifieddate)
    {
        _productmodelid = productmodelid;
        _illustrationid = illustrationid;
        _modifieddate = modifieddate;
    }

    public int Productmodelid
    {
        get => _productmodelid;
        set => _productmodelid = value;
    }
    public int Illustrationid
    {
        get => _illustrationid;
        set => _illustrationid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
