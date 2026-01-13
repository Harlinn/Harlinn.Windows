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

public class PersoncreditcardDataType
{
    int _businessentityid = 0;
    int _creditcardid = 0;
    DateTime _modifieddate;

    public PersoncreditcardDataType( )
    {
    }

    public PersoncreditcardDataType(int businessentityid,
        int creditcardid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _creditcardid = creditcardid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public int Creditcardid
    {
        get => _creditcardid;
        set => _creditcardid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
