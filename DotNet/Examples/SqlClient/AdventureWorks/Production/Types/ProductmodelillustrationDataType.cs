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

namespace AdventureWorks.Production.Types;

public class ProductmodelillustrationDataType
{
    int _productmodelid = 0;
    int _illustrationid = 0;
    DateTime _modifieddate;

    public ProductmodelillustrationDataType( )
    {
    }

    public ProductmodelillustrationDataType(int productmodelid,
        int illustrationid,
        DateTime modifieddate)
    {
        _productmodelid = productmodelid;
        _illustrationid = illustrationid;
        _modifieddate = modifieddate;
    }

    public int Productmodelid
    {
        get => _productmodelid;
        set => _productmodelid = value;
    }
    public int Illustrationid
    {
        get => _illustrationid;
        set => _illustrationid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
