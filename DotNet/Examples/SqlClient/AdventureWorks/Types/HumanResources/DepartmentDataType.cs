using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.HumanResources;

public class DepartmentDataType
{
    short _departmentid = 0;
    string _name = string.Empty;
    string _groupname = string.Empty;
    DateTime _modifieddate;

    public DepartmentDataType( )
    {
    }

    public DepartmentDataType(short departmentid,
        string name,
        string groupname,
        DateTime modifieddate)
    {
        _departmentid = departmentid;
        _name = name;
        _groupname = groupname;
        _modifieddate = modifieddate;
    }

    public short Departmentid
    {
        get => _departmentid;
        set => _departmentid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public string Groupname
    {
        get => _groupname;
        set => _groupname = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
