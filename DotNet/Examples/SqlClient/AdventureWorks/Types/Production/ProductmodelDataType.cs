using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Production;

public class ProductmodelDataType
{
    int _productmodelid = 0;
    string _name = string.Empty;
    SqlXml? _catalogdescription;
    SqlXml? _instructions;
    Guid _rowguid;
    DateTime _modifieddate;

    public ProductmodelDataType( )
    {
    }

    public ProductmodelDataType(int productmodelid,
        string name,
        SqlXml? catalogdescription,
        SqlXml? instructions,
        Guid rowguid,
        DateTime modifieddate)
    {
        _productmodelid = productmodelid;
        _name = name;
        _catalogdescription = catalogdescription;
        _instructions = instructions;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Productmodelid
    {
        get => _productmodelid;
        set => _productmodelid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public SqlXml? Catalogdescription
    {
        get => _catalogdescription;
        set => _catalogdescription = value;
    }
    public SqlXml? Instructions
    {
        get => _instructions;
        set => _instructions = value;
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
