using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class ProductdocumentDataType
{
    int _productid = 0;
    SqlHierarchyId _documentnode;
    DateTime _modifieddate;

    public ProductdocumentDataType( )
    {
    }

    public ProductdocumentDataType(int productid,
        SqlHierarchyId documentnode,
        DateTime modifieddate)
    {
        _productid = productid;
        _documentnode = documentnode;
        _modifieddate = modifieddate;
    }

    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public SqlHierarchyId Documentnode
    {
        get => _documentnode;
        set => _documentnode = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
