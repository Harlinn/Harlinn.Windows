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

public class ShoppingcartitemDataType
{
    int _shoppingcartitemid = 0;
    string _shoppingcartid = string.Empty;
    int _quantity = 0;
    int _productid = 0;
    DateTime _datecreated;
    DateTime _modifieddate;

    public ShoppingcartitemDataType( )
    {
    }

    public ShoppingcartitemDataType(int shoppingcartitemid,
        string shoppingcartid,
        int quantity,
        int productid,
        DateTime datecreated,
        DateTime modifieddate)
    {
        _shoppingcartitemid = shoppingcartitemid;
        _shoppingcartid = shoppingcartid;
        _quantity = quantity;
        _productid = productid;
        _datecreated = datecreated;
        _modifieddate = modifieddate;
    }

    public int Shoppingcartitemid
    {
        get => _shoppingcartitemid;
        set => _shoppingcartitemid = value;
    }
    public string Shoppingcartid
    {
        get => _shoppingcartid;
        set => _shoppingcartid = value;
    }
    public int Quantity
    {
        get => _quantity;
        set => _quantity = value;
    }
    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public DateTime Datecreated
    {
        get => _datecreated;
        set => _datecreated = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
