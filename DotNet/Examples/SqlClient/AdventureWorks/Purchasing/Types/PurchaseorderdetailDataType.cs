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

public class PurchaseorderdetailDataType
{
    int _purchaseorderid = 0;
    int _purchaseorderdetailid = 0;
    DateTime _duedate;
    short _orderqty = 0;
    int _productid = 0;
    decimal _unitprice = 0m;
    decimal _linetotal = 0m;
    decimal _receivedqty = 0m;
    decimal _rejectedqty = 0m;
    decimal _stockedqty = 0m;
    DateTime _modifieddate;

    public PurchaseorderdetailDataType( )
    {
    }

    public PurchaseorderdetailDataType(int purchaseorderid,
        int purchaseorderdetailid,
        DateTime duedate,
        short orderqty,
        int productid,
        decimal unitprice,
        decimal linetotal,
        decimal receivedqty,
        decimal rejectedqty,
        decimal stockedqty,
        DateTime modifieddate)
    {
        _purchaseorderid = purchaseorderid;
        _purchaseorderdetailid = purchaseorderdetailid;
        _duedate = duedate;
        _orderqty = orderqty;
        _productid = productid;
        _unitprice = unitprice;
        _linetotal = linetotal;
        _receivedqty = receivedqty;
        _rejectedqty = rejectedqty;
        _stockedqty = stockedqty;
        _modifieddate = modifieddate;
    }

    public int Purchaseorderid
    {
        get => _purchaseorderid;
        set => _purchaseorderid = value;
    }
    public int Purchaseorderdetailid
    {
        get => _purchaseorderdetailid;
        set => _purchaseorderdetailid = value;
    }
    public DateTime Duedate
    {
        get => _duedate;
        set => _duedate = value;
    }
    public short Orderqty
    {
        get => _orderqty;
        set => _orderqty = value;
    }
    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public decimal Unitprice
    {
        get => _unitprice;
        set => _unitprice = value;
    }
    public decimal Linetotal
    {
        get => _linetotal;
        set => _linetotal = value;
    }
    public decimal Receivedqty
    {
        get => _receivedqty;
        set => _receivedqty = value;
    }
    public decimal Rejectedqty
    {
        get => _rejectedqty;
        set => _rejectedqty = value;
    }
    public decimal Stockedqty
    {
        get => _stockedqty;
        set => _stockedqty = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
