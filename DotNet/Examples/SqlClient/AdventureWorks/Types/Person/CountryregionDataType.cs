using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Person;

public class CountryregionDataType
{
    string _countryregioncode = string.Empty;
    string _name = string.Empty;
    DateTime _modifieddate;

    public CountryregionDataType( )
    {
    }

    public CountryregionDataType(string countryregioncode,
        string name,
        DateTime modifieddate)
    {
        _countryregioncode = countryregioncode;
        _name = name;
        _modifieddate = modifieddate;
    }

    public string Countryregioncode
    {
        get => _countryregioncode;
        set => _countryregioncode = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
