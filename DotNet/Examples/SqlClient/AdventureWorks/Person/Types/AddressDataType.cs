using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Person.Types;

public class AddressDataType
{
    int _addressid = 0;
    string _addressline1 = string.Empty;
    string? _addressline2;
    string _city = string.Empty;
    int _stateprovinceid = 0;
    string _postalcode = string.Empty;
    SqlGeography? _spatiallocation;
    Guid _rowguid;
    DateTime _modifieddate;

    public AddressDataType( )
    {
    }

    public AddressDataType(int addressid,
        string addressline1,
        string? addressline2,
        string city,
        int stateprovinceid,
        string postalcode,
        SqlGeography? spatiallocation,
        Guid rowguid,
        DateTime modifieddate)
    {
        _addressid = addressid;
        _addressline1 = addressline1;
        _addressline2 = addressline2;
        _city = city;
        _stateprovinceid = stateprovinceid;
        _postalcode = postalcode;
        _spatiallocation = spatiallocation;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Addressid
    {
        get => _addressid;
        set => _addressid = value;
    }
    public string Addressline1
    {
        get => _addressline1;
        set => _addressline1 = value;
    }
    public string? Addressline2
    {
        get => _addressline2;
        set => _addressline2 = value;
    }
    public string City
    {
        get => _city;
        set => _city = value;
    }
    public int Stateprovinceid
    {
        get => _stateprovinceid;
        set => _stateprovinceid = value;
    }
    public string Postalcode
    {
        get => _postalcode;
        set => _postalcode = value;
    }
    public SqlGeography? Spatiallocation
    {
        get => _spatiallocation;
        set => _spatiallocation = value;
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
