using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Person.Types;

public class StateprovinceDataType
{
    int _stateprovinceid = 0;
    string _stateprovincecode = string.Empty;
    string _countryregioncode = string.Empty;
    bool _isonlystateprovinceflag = false;
    string _name = string.Empty;
    int _territoryid = 0;
    Guid _rowguid;
    DateTime _modifieddate;

    public StateprovinceDataType( )
    {
    }

    public StateprovinceDataType(int stateprovinceid,
        string stateprovincecode,
        string countryregioncode,
        bool isonlystateprovinceflag,
        string name,
        int territoryid,
        Guid rowguid,
        DateTime modifieddate)
    {
        _stateprovinceid = stateprovinceid;
        _stateprovincecode = stateprovincecode;
        _countryregioncode = countryregioncode;
        _isonlystateprovinceflag = isonlystateprovinceflag;
        _name = name;
        _territoryid = territoryid;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Stateprovinceid
    {
        get => _stateprovinceid;
        set => _stateprovinceid = value;
    }
    public string Stateprovincecode
    {
        get => _stateprovincecode;
        set => _stateprovincecode = value;
    }
    public string Countryregioncode
    {
        get => _countryregioncode;
        set => _countryregioncode = value;
    }
    public bool Isonlystateprovinceflag
    {
        get => _isonlystateprovinceflag;
        set => _isonlystateprovinceflag = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public int Territoryid
    {
        get => _territoryid;
        set => _territoryid = value;
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
