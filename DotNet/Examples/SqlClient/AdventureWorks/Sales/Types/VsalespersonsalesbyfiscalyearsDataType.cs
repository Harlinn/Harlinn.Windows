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

public class VsalespersonsalesbyfiscalyearsDataType
{
    readonly int? _salespersonid;
    readonly string? _fullname;
    readonly string _jobtitle = string.Empty;
    readonly string _salesterritory = string.Empty;
    readonly decimal? _2002;
    readonly decimal? _2003;
    readonly decimal? _2004;

    public VsalespersonsalesbyfiscalyearsDataType( )
    {
    }

    public VsalespersonsalesbyfiscalyearsDataType(int? salespersonid,
        string? fullname,
        string jobtitle,
        string salesterritory,
        decimal? d_2002,
        decimal? d_2003,
        decimal? d_2004)
    {
        _salespersonid = salespersonid;
        _fullname = fullname;
        _jobtitle = jobtitle;
        _salesterritory = salesterritory;
        _2002 = d_2002;
        _2003 = d_2003;
        _2004 = d_2004;
    }

    public int? Salespersonid => _salespersonid;
    public string? Fullname => _fullname;
    public string Jobtitle => _jobtitle;
    public string Salesterritory => _salesterritory;
    public decimal? D_2002 => _2002;
    public decimal? D_2003 => _2003;
    public decimal? D_2004 => _2004;
}
