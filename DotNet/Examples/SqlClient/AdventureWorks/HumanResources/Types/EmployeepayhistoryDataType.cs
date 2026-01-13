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

public class EmployeepayhistoryDataType
{
    int _businessentityid = 0;
    DateTime _ratechangedate;
    decimal _rate = 0m;
    byte _payfrequency = 0;
    DateTime _modifieddate;

    public EmployeepayhistoryDataType( )
    {
    }

    public EmployeepayhistoryDataType(int businessentityid,
        DateTime ratechangedate,
        decimal rate,
        byte payfrequency,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _ratechangedate = ratechangedate;
        _rate = rate;
        _payfrequency = payfrequency;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public DateTime Ratechangedate
    {
        get => _ratechangedate;
        set => _ratechangedate = value;
    }
    public decimal Rate
    {
        get => _rate;
        set => _rate = value;
    }
    public byte Payfrequency
    {
        get => _payfrequency;
        set => _payfrequency = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
