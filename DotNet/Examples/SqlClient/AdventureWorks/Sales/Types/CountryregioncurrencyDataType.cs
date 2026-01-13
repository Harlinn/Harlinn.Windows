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

public class CountryregioncurrencyDataType
{
    string _countryregioncode = string.Empty;
    string _currencycode = string.Empty;
    DateTime _modifieddate;

    public CountryregioncurrencyDataType( )
    {
    }

    public CountryregioncurrencyDataType(string countryregioncode,
        string currencycode,
        DateTime modifieddate)
    {
        _countryregioncode = countryregioncode;
        _currencycode = currencycode;
        _modifieddate = modifieddate;
    }

    public string Countryregioncode
    {
        get => _countryregioncode;
        set => _countryregioncode = value;
    }
    public string Currencycode
    {
        get => _currencycode;
        set => _currencycode = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
