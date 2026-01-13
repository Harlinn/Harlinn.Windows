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

namespace AdventureWorks.Person.Types;

public class BusinessentityaddressDataType
{
    int _businessentityid = 0;
    int _addressid = 0;
    int _addresstypeid = 0;
    Guid _rowguid;
    DateTime _modifieddate;

    public BusinessentityaddressDataType( )
    {
    }

    public BusinessentityaddressDataType(int businessentityid,
        int addressid,
        int addresstypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _addressid = addressid;
        _addresstypeid = addresstypeid;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public int Addressid
    {
        get => _addressid;
        set => _addressid = value;
    }
    public int Addresstypeid
    {
        get => _addresstypeid;
        set => _addresstypeid = value;
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
