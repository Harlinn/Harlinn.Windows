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

public class SpecialofferproductDataType
{
    int _specialofferid = 0;
    int _productid = 0;
    Guid _rowguid;
    DateTime _modifieddate;

    public SpecialofferproductDataType( )
    {
    }

    public SpecialofferproductDataType(int specialofferid,
        int productid,
        Guid rowguid,
        DateTime modifieddate)
    {
        _specialofferid = specialofferid;
        _productid = productid;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Specialofferid
    {
        get => _specialofferid;
        set => _specialofferid = value;
    }
    public int Productid
    {
        get => _productid;
        set => _productid = value;
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
