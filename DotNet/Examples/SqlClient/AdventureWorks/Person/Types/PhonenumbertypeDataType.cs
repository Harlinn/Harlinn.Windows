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

public class PhonenumbertypeDataType
{
    int _phonenumbertypeid = 0;
    string _name = string.Empty;
    DateTime _modifieddate;

    public PhonenumbertypeDataType( )
    {
    }

    public PhonenumbertypeDataType(int phonenumbertypeid,
        string name,
        DateTime modifieddate)
    {
        _phonenumbertypeid = phonenumbertypeid;
        _name = name;
        _modifieddate = modifieddate;
    }

    public int Phonenumbertypeid
    {
        get => _phonenumbertypeid;
        set => _phonenumbertypeid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
