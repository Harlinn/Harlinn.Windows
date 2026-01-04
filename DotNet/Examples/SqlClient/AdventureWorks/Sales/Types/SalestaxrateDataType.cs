using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Sales.Types;

public class SalestaxrateDataType
{
    int _salestaxrateid = 0;
    int _stateprovinceid = 0;
    byte _taxtype = 0;
    decimal _taxrate = 0m;
    string _name = string.Empty;
    Guid _rowguid;
    DateTime _modifieddate;

    public SalestaxrateDataType( )
    {
    }

    public SalestaxrateDataType(int salestaxrateid,
        int stateprovinceid,
        byte taxtype,
        decimal taxrate,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        _salestaxrateid = salestaxrateid;
        _stateprovinceid = stateprovinceid;
        _taxtype = taxtype;
        _taxrate = taxrate;
        _name = name;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Salestaxrateid
    {
        get => _salestaxrateid;
        set => _salestaxrateid = value;
    }
    public int Stateprovinceid
    {
        get => _stateprovinceid;
        set => _stateprovinceid = value;
    }
    public byte Taxtype
    {
        get => _taxtype;
        set => _taxtype = value;
    }
    public decimal Taxrate
    {
        get => _taxrate;
        set => _taxrate = value;
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
