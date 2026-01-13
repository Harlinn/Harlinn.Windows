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

public class VproductmodelinstructionsDataType
{
    readonly int _productmodelid = 0;
    readonly string _name = string.Empty;
    readonly string? _instructions;
    readonly int? _locationid;
    readonly decimal? _setuphours;
    readonly decimal? _machinehours;
    readonly decimal? _laborhours;
    readonly int? _lotsize;
    readonly string? _step;
    readonly Guid _rowguid;
    readonly DateTime _modifieddate;

    public VproductmodelinstructionsDataType( )
    {
    }

    public VproductmodelinstructionsDataType(int productmodelid,
        string name,
        string? instructions,
        int? locationid,
        decimal? setuphours,
        decimal? machinehours,
        decimal? laborhours,
        int? lotsize,
        string? step,
        Guid rowguid,
        DateTime modifieddate)
    {
        _productmodelid = productmodelid;
        _name = name;
        _instructions = instructions;
        _locationid = locationid;
        _setuphours = setuphours;
        _machinehours = machinehours;
        _laborhours = laborhours;
        _lotsize = lotsize;
        _step = step;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Productmodelid => _productmodelid;
    public string Name => _name;
    public string? Instructions => _instructions;
    public int? Locationid => _locationid;
    public decimal? Setuphours => _setuphours;
    public decimal? Machinehours => _machinehours;
    public decimal? Laborhours => _laborhours;
    public int? Lotsize => _lotsize;
    public string? Step => _step;
    public Guid Rowguid => _rowguid;
    public DateTime Modifieddate => _modifieddate;
}
