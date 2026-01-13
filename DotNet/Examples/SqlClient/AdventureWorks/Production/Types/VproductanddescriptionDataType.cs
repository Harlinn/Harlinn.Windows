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

public class VproductanddescriptionDataType
{
    readonly int _productid = 0;
    readonly string _name = string.Empty;
    readonly string _productmodel = string.Empty;
    readonly string _cultureid = string.Empty;
    readonly string _description = string.Empty;

    public VproductanddescriptionDataType( )
    {
    }

    public VproductanddescriptionDataType(int productid,
        string name,
        string productmodel,
        string cultureid,
        string description)
    {
        _productid = productid;
        _name = name;
        _productmodel = productmodel;
        _cultureid = cultureid;
        _description = description;
    }

    public int Productid => _productid;
    public string Name => _name;
    public string Productmodel => _productmodel;
    public string Cultureid => _cultureid;
    public string Description => _description;
}
