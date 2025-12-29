using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Purchasing;

public class ShipmethodDataType
{
    int _shipmethodid = 0;
    string _name = string.Empty;
    decimal _shipbase = 0m;
    decimal _shiprate = 0m;
    Guid _rowguid;
    DateTime _modifieddate;

    public ShipmethodDataType( )
    {
    }

    public ShipmethodDataType(int shipmethodid,
        string name,
        decimal shipbase,
        decimal shiprate,
        Guid rowguid,
        DateTime modifieddate)
    {
        _shipmethodid = shipmethodid;
        _name = name;
        _shipbase = shipbase;
        _shiprate = shiprate;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Shipmethodid
    {
        get => _shipmethodid;
        set => _shipmethodid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public decimal Shipbase
    {
        get => _shipbase;
        set => _shipbase = value;
    }
    public decimal Shiprate
    {
        get => _shiprate;
        set => _shiprate = value;
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
