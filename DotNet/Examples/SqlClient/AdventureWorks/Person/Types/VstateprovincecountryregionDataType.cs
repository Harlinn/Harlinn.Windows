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

namespace AdventureWorks.Person.Types;

public class VstateprovincecountryregionDataType
{
    readonly int _stateprovinceid = 0;
    readonly string _stateprovincecode = string.Empty;
    readonly bool _isonlystateprovinceflag = false;
    readonly string _stateprovincename = string.Empty;
    readonly int _territoryid = 0;
    readonly string _countryregioncode = string.Empty;
    readonly string _countryregionname = string.Empty;

    public VstateprovincecountryregionDataType( )
    {
    }

    public VstateprovincecountryregionDataType(int stateprovinceid,
        string stateprovincecode,
        bool isonlystateprovinceflag,
        string stateprovincename,
        int territoryid,
        string countryregioncode,
        string countryregionname)
    {
        _stateprovinceid = stateprovinceid;
        _stateprovincecode = stateprovincecode;
        _isonlystateprovinceflag = isonlystateprovinceflag;
        _stateprovincename = stateprovincename;
        _territoryid = territoryid;
        _countryregioncode = countryregioncode;
        _countryregionname = countryregionname;
    }

    public int Stateprovinceid => _stateprovinceid;
    public string Stateprovincecode => _stateprovincecode;
    public bool Isonlystateprovinceflag => _isonlystateprovinceflag;
    public string Stateprovincename => _stateprovincename;
    public int Territoryid => _territoryid;
    public string Countryregioncode => _countryregioncode;
    public string Countryregionname => _countryregionname;
}
