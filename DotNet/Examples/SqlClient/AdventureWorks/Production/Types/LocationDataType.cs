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

namespace AdventureWorks.Production.Types;

public class LocationDataType
{
    short _locationid = 0;
    string _name = string.Empty;
    decimal _costrate = 0m;
    decimal _availability = 0m;
    DateTime _modifieddate;

    public LocationDataType( )
    {
    }

    public LocationDataType(short locationid,
        string name,
        decimal costrate,
        decimal availability,
        DateTime modifieddate)
    {
        _locationid = locationid;
        _name = name;
        _costrate = costrate;
        _availability = availability;
        _modifieddate = modifieddate;
    }

    public short Locationid
    {
        get => _locationid;
        set => _locationid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public decimal Costrate
    {
        get => _costrate;
        set => _costrate = value;
    }
    public decimal Availability
    {
        get => _availability;
        set => _availability = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
