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

namespace AdventureWorks.Sales.Types;

public class SalesterritoryDataType
{
    int _territoryid = 0;
    string _name = string.Empty;
    string _countryregioncode = string.Empty;
    string _group = string.Empty;
    decimal _salesytd = 0m;
    decimal _saleslastyear = 0m;
    decimal _costytd = 0m;
    decimal _costlastyear = 0m;
    Guid _rowguid;
    DateTime _modifieddate;

    public SalesterritoryDataType( )
    {
    }

    public SalesterritoryDataType(int territoryid,
        string name,
        string countryregioncode,
        string group,
        decimal salesytd,
        decimal saleslastyear,
        decimal costytd,
        decimal costlastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        _territoryid = territoryid;
        _name = name;
        _countryregioncode = countryregioncode;
        _group = group;
        _salesytd = salesytd;
        _saleslastyear = saleslastyear;
        _costytd = costytd;
        _costlastyear = costlastyear;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Territoryid
    {
        get => _territoryid;
        set => _territoryid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public string Countryregioncode
    {
        get => _countryregioncode;
        set => _countryregioncode = value;
    }
    public string Group
    {
        get => _group;
        set => _group = value;
    }
    public decimal Salesytd
    {
        get => _salesytd;
        set => _salesytd = value;
    }
    public decimal Saleslastyear
    {
        get => _saleslastyear;
        set => _saleslastyear = value;
    }
    public decimal Costytd
    {
        get => _costytd;
        set => _costytd = value;
    }
    public decimal Costlastyear
    {
        get => _costlastyear;
        set => _costlastyear = value;
    }
    public Guid Rowguid
    {
        get => _rowguid;
        set => _rowguid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
