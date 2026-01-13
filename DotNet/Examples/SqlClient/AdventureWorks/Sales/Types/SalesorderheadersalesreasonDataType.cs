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

public class SalesorderheadersalesreasonDataType
{
    int _salesorderid = 0;
    int _salesreasonid = 0;
    DateTime _modifieddate;

    public SalesorderheadersalesreasonDataType( )
    {
    }

    public SalesorderheadersalesreasonDataType(int salesorderid,
        int salesreasonid,
        DateTime modifieddate)
    {
        _salesorderid = salesorderid;
        _salesreasonid = salesreasonid;
        _modifieddate = modifieddate;
    }

    public int Salesorderid
    {
        get => _salesorderid;
        set => _salesorderid = value;
    }
    public int Salesreasonid
    {
        get => _salesreasonid;
        set => _salesreasonid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
