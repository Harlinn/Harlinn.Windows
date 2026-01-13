/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.HumanResources.Types;

public class VemployeedepartmenthistoryDataType
{
    readonly int _businessentityid = 0;
    readonly string? _title;
    readonly string _firstname = string.Empty;
    readonly string? _middlename;
    readonly string _lastname = string.Empty;
    readonly string? _suffix;
    readonly string _shift = string.Empty;
    readonly string _department = string.Empty;
    readonly string _groupname = string.Empty;
    readonly DateTime _startdate;
    readonly DateTime? _enddate;

    public VemployeedepartmenthistoryDataType( )
    {
    }

    public VemployeedepartmenthistoryDataType(int businessentityid,
        string? title,
        string firstname,
        string? middlename,
        string lastname,
        string? suffix,
        string shift,
        string department,
        string groupname,
        DateTime startdate,
        DateTime? enddate)
    {
        _businessentityid = businessentityid;
        _title = title;
        _firstname = firstname;
        _middlename = middlename;
        _lastname = lastname;
        _suffix = suffix;
        _shift = shift;
        _department = department;
        _groupname = groupname;
        _startdate = startdate;
        _enddate = enddate;
    }

    public int Businessentityid => _businessentityid;
    public string? Title => _title;
    public string Firstname => _firstname;
    public string? Middlename => _middlename;
    public string Lastname => _lastname;
    public string? Suffix => _suffix;
    public string Shift => _shift;
    public string Department => _department;
    public string Groupname => _groupname;
    public DateTime Startdate => _startdate;
    public DateTime? Enddate => _enddate;
}
