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

namespace AdventureWorks.Purchasing.Types;

public class VendorDataType
{
    int _businessentityid = 0;
    string _accountnumber = string.Empty;
    string _name = string.Empty;
    byte _creditrating = 0;
    bool _preferredvendorstatus = false;
    bool _activeflag = false;
    string? _purchasingwebserviceurl;
    DateTime _modifieddate;

    public VendorDataType( )
    {
    }

    public VendorDataType(int businessentityid,
        string accountnumber,
        string name,
        byte creditrating,
        bool preferredvendorstatus,
        bool activeflag,
        string? purchasingwebserviceurl,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _accountnumber = accountnumber;
        _name = name;
        _creditrating = creditrating;
        _preferredvendorstatus = preferredvendorstatus;
        _activeflag = activeflag;
        _purchasingwebserviceurl = purchasingwebserviceurl;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public string Accountnumber
    {
        get => _accountnumber;
        set => _accountnumber = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public byte Creditrating
    {
        get => _creditrating;
        set => _creditrating = value;
    }
    public bool Preferredvendorstatus
    {
        get => _preferredvendorstatus;
        set => _preferredvendorstatus = value;
    }
    public bool Activeflag
    {
        get => _activeflag;
        set => _activeflag = value;
    }
    public string? Purchasingwebserviceurl
    {
        get => _purchasingwebserviceurl;
        set => _purchasingwebserviceurl = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
