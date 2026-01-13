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

public class CustomerDataType
{
    int _customerid = 0;
    int? _personid;
    int? _storeid;
    int? _territoryid;
    string _accountnumber = string.Empty;
    Guid _rowguid;
    DateTime _modifieddate;

    public CustomerDataType( )
    {
    }

    public CustomerDataType(int customerid,
        int? personid,
        int? storeid,
        int? territoryid,
        string accountnumber,
        Guid rowguid,
        DateTime modifieddate)
    {
        _customerid = customerid;
        _personid = personid;
        _storeid = storeid;
        _territoryid = territoryid;
        _accountnumber = accountnumber;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Customerid
    {
        get => _customerid;
        set => _customerid = value;
    }
    public int? Personid
    {
        get => _personid;
        set => _personid = value;
    }
    public int? Storeid
    {
        get => _storeid;
        set => _storeid = value;
    }
    public int? Territoryid
    {
        get => _territoryid;
        set => _territoryid = value;
    }
    public string Accountnumber
    {
        get => _accountnumber;
        set => _accountnumber = value;
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
