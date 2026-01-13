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

public class VstorewithdemographicsDataType
{
    readonly int _businessentityid = 0;
    readonly string _name = string.Empty;
    readonly decimal? _annualsales;
    readonly decimal? _annualrevenue;
    readonly string? _bankname;
    readonly string? _businesstype;
    readonly int? _yearopened;
    readonly string? _specialty;
    readonly int? _squarefeet;
    readonly string? _brands;
    readonly string? _internet;
    readonly int? _numberemployees;

    public VstorewithdemographicsDataType( )
    {
    }

    public VstorewithdemographicsDataType(int businessentityid,
        string name,
        decimal? annualsales,
        decimal? annualrevenue,
        string? bankname,
        string? businesstype,
        int? yearopened,
        string? specialty,
        int? squarefeet,
        string? brands,
        string? internet,
        int? numberemployees)
    {
        _businessentityid = businessentityid;
        _name = name;
        _annualsales = annualsales;
        _annualrevenue = annualrevenue;
        _bankname = bankname;
        _businesstype = businesstype;
        _yearopened = yearopened;
        _specialty = specialty;
        _squarefeet = squarefeet;
        _brands = brands;
        _internet = internet;
        _numberemployees = numberemployees;
    }

    public int Businessentityid => _businessentityid;
    public string Name => _name;
    public decimal? Annualsales => _annualsales;
    public decimal? Annualrevenue => _annualrevenue;
    public string? Bankname => _bankname;
    public string? Businesstype => _businesstype;
    public int? Yearopened => _yearopened;
    public string? Specialty => _specialty;
    public int? Squarefeet => _squarefeet;
    public string? Brands => _brands;
    public string? Internet => _internet;
    public int? Numberemployees => _numberemployees;
}
