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

public class PersonphoneDataType
{
    int _businessentityid = 0;
    string _phonenumber = string.Empty;
    int _phonenumbertypeid = 0;
    DateTime _modifieddate;

    public PersonphoneDataType( )
    {
    }

    public PersonphoneDataType(int businessentityid,
        string phonenumber,
        int phonenumbertypeid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _phonenumber = phonenumber;
        _phonenumbertypeid = phonenumbertypeid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public string Phonenumber
    {
        get => _phonenumber;
        set => _phonenumber = value;
    }
    public int Phonenumbertypeid
    {
        get => _phonenumbertypeid;
        set => _phonenumbertypeid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
