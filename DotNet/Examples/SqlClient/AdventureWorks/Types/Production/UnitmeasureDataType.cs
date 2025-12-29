using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Production;

public class UnitmeasureDataType
{
    string _unitmeasurecode = string.Empty;
    string _name = string.Empty;
    DateTime _modifieddate;

    public UnitmeasureDataType( )
    {
    }

    public UnitmeasureDataType(string unitmeasurecode,
        string name,
        DateTime modifieddate)
    {
        _unitmeasurecode = unitmeasurecode;
        _name = name;
        _modifieddate = modifieddate;
    }

    public string Unitmeasurecode
    {
        get => _unitmeasurecode;
        set => _unitmeasurecode = value;
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
