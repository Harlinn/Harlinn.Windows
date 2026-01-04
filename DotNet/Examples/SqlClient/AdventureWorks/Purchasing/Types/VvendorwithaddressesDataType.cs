using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Purchasing.Types;

public class VvendorwithaddressesDataType
{
    readonly int _businessentityid = 0;
    readonly string _name = string.Empty;
    readonly string _addresstype = string.Empty;
    readonly string _addressline1 = string.Empty;
    readonly string? _addressline2;
    readonly string _city = string.Empty;
    readonly string _stateprovincename = string.Empty;
    readonly string _postalcode = string.Empty;
    readonly string _countryregionname = string.Empty;

    public VvendorwithaddressesDataType( )
    {
    }

    public VvendorwithaddressesDataType(int businessentityid,
        string name,
        string addresstype,
        string addressline1,
        string? addressline2,
        string city,
        string stateprovincename,
        string postalcode,
        string countryregionname)
    {
        _businessentityid = businessentityid;
        _name = name;
        _addresstype = addresstype;
        _addressline1 = addressline1;
        _addressline2 = addressline2;
        _city = city;
        _stateprovincename = stateprovincename;
        _postalcode = postalcode;
        _countryregionname = countryregionname;
    }

    public int Businessentityid => _businessentityid;
    public string Name => _name;
    public string Addresstype => _addresstype;
    public string Addressline1 => _addressline1;
    public string? Addressline2 => _addressline2;
    public string City => _city;
    public string Stateprovincename => _stateprovincename;
    public string Postalcode => _postalcode;
    public string Countryregionname => _countryregionname;
}
