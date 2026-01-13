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

public class ProductcosthistoryDataType
{
    int _productid = 0;
    DateTime _startdate;
    DateTime? _enddate;
    decimal _standardcost = 0m;
    DateTime _modifieddate;

    public ProductcosthistoryDataType( )
    {
    }

    public ProductcosthistoryDataType(int productid,
        DateTime startdate,
        DateTime? enddate,
        decimal standardcost,
        DateTime modifieddate)
    {
        _productid = productid;
        _startdate = startdate;
        _enddate = enddate;
        _standardcost = standardcost;
        _modifieddate = modifieddate;
    }

    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public DateTime Startdate
    {
        get => _startdate;
        set => _startdate = value;
    }
    public DateTime? Enddate
    {
        get => _enddate;
        set => _enddate = value;
    }
    public decimal Standardcost
    {
        get => _standardcost;
        set => _standardcost = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
