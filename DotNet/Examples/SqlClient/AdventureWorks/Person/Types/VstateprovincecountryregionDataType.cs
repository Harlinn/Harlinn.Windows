using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Person.Types;

public class VstateprovincecountryregionDataType
{
    readonly int _stateprovinceid = 0;
    readonly string _stateprovincecode = string.Empty;
    readonly bool _isonlystateprovinceflag = false;
    readonly string _stateprovincename = string.Empty;
    readonly int _territoryid = 0;
    readonly string _countryregioncode = string.Empty;
    readonly string _countryregionname = string.Empty;

    public VstateprovincecountryregionDataType( )
    {
    }

    public VstateprovincecountryregionDataType(int stateprovinceid,
        string stateprovincecode,
        bool isonlystateprovinceflag,
        string stateprovincename,
        int territoryid,
        string countryregioncode,
        string countryregionname)
    {
        _stateprovinceid = stateprovinceid;
        _stateprovincecode = stateprovincecode;
        _isonlystateprovinceflag = isonlystateprovinceflag;
        _stateprovincename = stateprovincename;
        _territoryid = territoryid;
        _countryregioncode = countryregioncode;
        _countryregionname = countryregionname;
    }

    public int Stateprovinceid => _stateprovinceid;
    public string Stateprovincecode => _stateprovincecode;
    public bool Isonlystateprovinceflag => _isonlystateprovinceflag;
    public string Stateprovincename => _stateprovincename;
    public int Territoryid => _territoryid;
    public string Countryregioncode => _countryregioncode;
    public string Countryregionname => _countryregionname;
}
