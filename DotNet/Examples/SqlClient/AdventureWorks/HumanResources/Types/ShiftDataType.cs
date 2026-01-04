using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.HumanResources.Types;

public class ShiftDataType
{
    byte _shiftid = 0;
    string _name = string.Empty;
    DateTime _starttime;
    DateTime _endtime;
    DateTime _modifieddate;

    public ShiftDataType( )
    {
    }

    public ShiftDataType(byte shiftid,
        string name,
        DateTime starttime,
        DateTime endtime,
        DateTime modifieddate)
    {
        _shiftid = shiftid;
        _name = name;
        _starttime = starttime;
        _endtime = endtime;
        _modifieddate = modifieddate;
    }

    public byte Shiftid
    {
        get => _shiftid;
        set => _shiftid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public DateTime Starttime
    {
        get => _starttime;
        set => _starttime = value;
    }
    public DateTime Endtime
    {
        get => _endtime;
        set => _endtime = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
