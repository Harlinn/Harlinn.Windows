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
