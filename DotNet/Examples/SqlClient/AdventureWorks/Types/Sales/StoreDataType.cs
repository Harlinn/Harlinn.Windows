using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Sales;

public class StoreDataType
{
    int _businessentityid = 0;
    string _name = string.Empty;
    int? _salespersonid;
    SqlXml? _demographics;
    Guid _rowguid;
    DateTime _modifieddate;

    public StoreDataType( )
    {
    }

    public StoreDataType(int businessentityid,
        string name,
        int? salespersonid,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _name = name;
        _salespersonid = salespersonid;
        _demographics = demographics;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public int? Salespersonid
    {
        get => _salespersonid;
        set => _salespersonid = value;
    }
    public SqlXml? Demographics
    {
        get => _demographics;
        set => _demographics = value;
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
