using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.HumanResources.Types;

public class VemployeedepartmentDataType
{
    readonly int _businessentityid = 0;
    readonly string? _title;
    readonly string _firstname = string.Empty;
    readonly string? _middlename;
    readonly string _lastname = string.Empty;
    readonly string? _suffix;
    readonly string _jobtitle = string.Empty;
    readonly string _department = string.Empty;
    readonly string _groupname = string.Empty;
    readonly DateTime _startdate;

    public VemployeedepartmentDataType( )
    {
    }

    public VemployeedepartmentDataType(int businessentityid,
        string? title,
        string firstname,
        string? middlename,
        string lastname,
        string? suffix,
        string jobtitle,
        string department,
        string groupname,
        DateTime startdate)
    {
        _businessentityid = businessentityid;
        _title = title;
        _firstname = firstname;
        _middlename = middlename;
        _lastname = lastname;
        _suffix = suffix;
        _jobtitle = jobtitle;
        _department = department;
        _groupname = groupname;
        _startdate = startdate;
    }

    public int Businessentityid => _businessentityid;
    public string? Title => _title;
    public string Firstname => _firstname;
    public string? Middlename => _middlename;
    public string Lastname => _lastname;
    public string? Suffix => _suffix;
    public string Jobtitle => _jobtitle;
    public string Department => _department;
    public string Groupname => _groupname;
    public DateTime Startdate => _startdate;
}
