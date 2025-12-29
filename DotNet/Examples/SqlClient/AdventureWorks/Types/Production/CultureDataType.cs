using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Production;

public class CultureDataType
{
    string _cultureid = string.Empty;
    string _name = string.Empty;
    DateTime _modifieddate;

    public CultureDataType( )
    {
    }

    public CultureDataType(string cultureid,
        string name,
        DateTime modifieddate)
    {
        _cultureid = cultureid;
        _name = name;
        _modifieddate = modifieddate;
    }

    public string Cultureid
    {
        get => _cultureid;
        set => _cultureid = value;
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
