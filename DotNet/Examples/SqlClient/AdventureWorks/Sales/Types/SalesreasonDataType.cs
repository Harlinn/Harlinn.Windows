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

public class SalesreasonDataType
{
    int _salesreasonid = 0;
    string _name = string.Empty;
    string _reasontype = string.Empty;
    DateTime _modifieddate;

    public SalesreasonDataType( )
    {
    }

    public SalesreasonDataType(int salesreasonid,
        string name,
        string reasontype,
        DateTime modifieddate)
    {
        _salesreasonid = salesreasonid;
        _name = name;
        _reasontype = reasontype;
        _modifieddate = modifieddate;
    }

    public int Salesreasonid
    {
        get => _salesreasonid;
        set => _salesreasonid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public string Reasontype
    {
        get => _reasontype;
        set => _reasontype = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
