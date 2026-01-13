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

public class VpersondemographicsDataType
{
    readonly int _businessentityid = 0;
    readonly decimal? _totalpurchaseytd;
    readonly DateTime? _datefirstpurchase;
    readonly DateTime? _birthdate;
    readonly string? _maritalstatus;
    readonly string? _yearlyincome;
    readonly string? _gender;
    readonly int? _totalchildren;
    readonly int? _numberchildrenathome;
    readonly string? _education;
    readonly string? _occupation;
    readonly bool? _homeownerflag;
    readonly int? _numbercarsowned;

    public VpersondemographicsDataType( )
    {
    }

    public VpersondemographicsDataType(int businessentityid,
        decimal? totalpurchaseytd,
        DateTime? datefirstpurchase,
        DateTime? birthdate,
        string? maritalstatus,
        string? yearlyincome,
        string? gender,
        int? totalchildren,
        int? numberchildrenathome,
        string? education,
        string? occupation,
        bool? homeownerflag,
        int? numbercarsowned)
    {
        _businessentityid = businessentityid;
        _totalpurchaseytd = totalpurchaseytd;
        _datefirstpurchase = datefirstpurchase;
        _birthdate = birthdate;
        _maritalstatus = maritalstatus;
        _yearlyincome = yearlyincome;
        _gender = gender;
        _totalchildren = totalchildren;
        _numberchildrenathome = numberchildrenathome;
        _education = education;
        _occupation = occupation;
        _homeownerflag = homeownerflag;
        _numbercarsowned = numbercarsowned;
    }

    public int Businessentityid => _businessentityid;
    public decimal? Totalpurchaseytd => _totalpurchaseytd;
    public DateTime? Datefirstpurchase => _datefirstpurchase;
    public DateTime? Birthdate => _birthdate;
    public string? Maritalstatus => _maritalstatus;
    public string? Yearlyincome => _yearlyincome;
    public string? Gender => _gender;
    public int? Totalchildren => _totalchildren;
    public int? Numberchildrenathome => _numberchildrenathome;
    public string? Education => _education;
    public string? Occupation => _occupation;
    public bool? Homeownerflag => _homeownerflag;
    public int? Numbercarsowned => _numbercarsowned;
}
