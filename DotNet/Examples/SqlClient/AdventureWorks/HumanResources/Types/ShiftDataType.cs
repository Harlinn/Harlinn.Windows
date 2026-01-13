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
