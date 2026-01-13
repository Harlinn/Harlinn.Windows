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
