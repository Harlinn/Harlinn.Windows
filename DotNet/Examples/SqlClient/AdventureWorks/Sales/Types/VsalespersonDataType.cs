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

public class VsalespersonDataType
{
    readonly int _businessentityid = 0;
    readonly string? _title;
    readonly string _firstname = string.Empty;
    readonly string? _middlename;
    readonly string _lastname = string.Empty;
    readonly string? _suffix;
    readonly string _jobtitle = string.Empty;
    readonly string? _phonenumber;
    readonly string? _phonenumbertype;
    readonly string? _emailaddress;
    readonly int _emailpromotion = 0;
    readonly string _addressline1 = string.Empty;
    readonly string? _addressline2;
    readonly string _city = string.Empty;
    readonly string _stateprovincename = string.Empty;
    readonly string _postalcode = string.Empty;
    readonly string _countryregionname = string.Empty;
    readonly string? _territoryname;
    readonly string? _territorygroup;
    readonly decimal? _salesquota;
    readonly decimal _salesytd = 0m;
    readonly decimal _saleslastyear = 0m;

    public VsalespersonDataType( )
    {
    }

    public VsalespersonDataType(int businessentityid,
        string? title,
        string firstname,
        string? middlename,
        string lastname,
        string? suffix,
        string jobtitle,
        string? phonenumber,
        string? phonenumbertype,
        string? emailaddress,
        int emailpromotion,
        string addressline1,
        string? addressline2,
        string city,
        string stateprovincename,
        string postalcode,
        string countryregionname,
        string? territoryname,
        string? territorygroup,
        decimal? salesquota,
        decimal salesytd,
        decimal saleslastyear)
    {
        _businessentityid = businessentityid;
        _title = title;
        _firstname = firstname;
        _middlename = middlename;
        _lastname = lastname;
        _suffix = suffix;
        _jobtitle = jobtitle;
        _phonenumber = phonenumber;
        _phonenumbertype = phonenumbertype;
        _emailaddress = emailaddress;
        _emailpromotion = emailpromotion;
        _addressline1 = addressline1;
        _addressline2 = addressline2;
        _city = city;
        _stateprovincename = stateprovincename;
        _postalcode = postalcode;
        _countryregionname = countryregionname;
        _territoryname = territoryname;
        _territorygroup = territorygroup;
        _salesquota = salesquota;
        _salesytd = salesytd;
        _saleslastyear = saleslastyear;
    }

    public int Businessentityid => _businessentityid;
    public string? Title => _title;
    public string Firstname => _firstname;
    public string? Middlename => _middlename;
    public string Lastname => _lastname;
    public string? Suffix => _suffix;
    public string Jobtitle => _jobtitle;
    public string? Phonenumber => _phonenumber;
    public string? Phonenumbertype => _phonenumbertype;
    public string? Emailaddress => _emailaddress;
    public int Emailpromotion => _emailpromotion;
    public string Addressline1 => _addressline1;
    public string? Addressline2 => _addressline2;
    public string City => _city;
    public string Stateprovincename => _stateprovincename;
    public string Postalcode => _postalcode;
    public string Countryregionname => _countryregionname;
    public string? Territoryname => _territoryname;
    public string? Territorygroup => _territorygroup;
    public decimal? Salesquota => _salesquota;
    public decimal Salesytd => _salesytd;
    public decimal Saleslastyear => _saleslastyear;
}
