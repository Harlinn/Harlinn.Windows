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

public class PurchaseorderheaderDataType
{
    int _purchaseorderid = 0;
    byte _revisionnumber = 0;
    byte _status = 0;
    int _employeeid = 0;
    int _vendorid = 0;
    int _shipmethodid = 0;
    DateTime _orderdate;
    DateTime? _shipdate;
    decimal _subtotal = 0m;
    decimal _taxamt = 0m;
    decimal _freight = 0m;
    decimal _totaldue = 0m;
    DateTime _modifieddate;

    public PurchaseorderheaderDataType( )
    {
    }

    public PurchaseorderheaderDataType(int purchaseorderid,
        byte revisionnumber,
        byte status,
        int employeeid,
        int vendorid,
        int shipmethodid,
        DateTime orderdate,
        DateTime? shipdate,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        DateTime modifieddate)
    {
        _purchaseorderid = purchaseorderid;
        _revisionnumber = revisionnumber;
        _status = status;
        _employeeid = employeeid;
        _vendorid = vendorid;
        _shipmethodid = shipmethodid;
        _orderdate = orderdate;
        _shipdate = shipdate;
        _subtotal = subtotal;
        _taxamt = taxamt;
        _freight = freight;
        _totaldue = totaldue;
        _modifieddate = modifieddate;
    }

    public int Purchaseorderid
    {
        get => _purchaseorderid;
        set => _purchaseorderid = value;
    }
    public byte Revisionnumber
    {
        get => _revisionnumber;
        set => _revisionnumber = value;
    }
    public byte Status
    {
        get => _status;
        set => _status = value;
    }
    public int Employeeid
    {
        get => _employeeid;
        set => _employeeid = value;
    }
    public int Vendorid
    {
        get => _vendorid;
        set => _vendorid = value;
    }
    public int Shipmethodid
    {
        get => _shipmethodid;
        set => _shipmethodid = value;
    }
    public DateTime Orderdate
    {
        get => _orderdate;
        set => _orderdate = value;
    }
    public DateTime? Shipdate
    {
        get => _shipdate;
        set => _shipdate = value;
    }
    public decimal Subtotal
    {
        get => _subtotal;
        set => _subtotal = value;
    }
    public decimal Taxamt
    {
        get => _taxamt;
        set => _taxamt = value;
    }
    public decimal Freight
    {
        get => _freight;
        set => _freight = value;
    }
    public decimal Totaldue
    {
        get => _totaldue;
        set => _totaldue = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
