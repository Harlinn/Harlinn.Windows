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

public class SalespersonquotahistoryDataType
{
    int _businessentityid = 0;
    DateTime _quotadate;
    decimal _salesquota = 0m;
    Guid _rowguid;
    DateTime _modifieddate;

    public SalespersonquotahistoryDataType( )
    {
    }

    public SalespersonquotahistoryDataType(int businessentityid,
        DateTime quotadate,
        decimal salesquota,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _quotadate = quotadate;
        _salesquota = salesquota;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public DateTime Quotadate
    {
        get => _quotadate;
        set => _quotadate = value;
    }
    public decimal Salesquota
    {
        get => _salesquota;
        set => _salesquota = value;
    }
    public Guid Rowguid
    {
        get => _rowguid;
        set => _rowguid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
