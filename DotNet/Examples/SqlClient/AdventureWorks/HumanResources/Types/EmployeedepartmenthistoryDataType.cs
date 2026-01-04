using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.HumanResources.Types;

public class EmployeedepartmenthistoryDataType
{
    int _businessentityid = 0;
    short _departmentid = 0;
    byte _shiftid = 0;
    DateTime _startdate;
    DateTime? _enddate;
    DateTime _modifieddate;

    public EmployeedepartmenthistoryDataType( )
    {
    }

    public EmployeedepartmenthistoryDataType(int businessentityid,
        short departmentid,
        byte shiftid,
        DateTime startdate,
        DateTime? enddate,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _departmentid = departmentid;
        _shiftid = shiftid;
        _startdate = startdate;
        _enddate = enddate;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public short Departmentid
    {
        get => _departmentid;
        set => _departmentid = value;
    }
    public byte Shiftid
    {
        get => _shiftid;
        set => _shiftid = value;
    }
    public DateTime Startdate
    {
        get => _startdate;
        set => _startdate = value;
    }
    public DateTime? Enddate
    {
        get => _enddate;
        set => _enddate = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
