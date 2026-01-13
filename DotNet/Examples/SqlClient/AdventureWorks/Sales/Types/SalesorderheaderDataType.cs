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

public class SalesorderheaderDataType
{
    int _salesorderid = 0;
    byte _revisionnumber = 0;
    DateTime _orderdate;
    DateTime _duedate;
    DateTime? _shipdate;
    byte _status = 0;
    bool _onlineorderflag = false;
    string _salesordernumber = string.Empty;
    string? _purchaseordernumber;
    string? _accountnumber;
    int _customerid = 0;
    int? _salespersonid;
    int? _territoryid;
    int _billtoaddressid = 0;
    int _shiptoaddressid = 0;
    int _shipmethodid = 0;
    int? _creditcardid;
    string? _creditcardapprovalcode;
    int? _currencyrateid;
    decimal _subtotal = 0m;
    decimal _taxamt = 0m;
    decimal _freight = 0m;
    decimal _totaldue = 0m;
    string? _comment;
    Guid _rowguid;
    DateTime _modifieddate;

    public SalesorderheaderDataType( )
    {
    }

    public SalesorderheaderDataType(int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
        string salesordernumber,
        string? purchaseordernumber,
        string? accountnumber,
        int customerid,
        int? salespersonid,
        int? territoryid,
        int billtoaddressid,
        int shiptoaddressid,
        int shipmethodid,
        int? creditcardid,
        string? creditcardapprovalcode,
        int? currencyrateid,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        _salesorderid = salesorderid;
        _revisionnumber = revisionnumber;
        _orderdate = orderdate;
        _duedate = duedate;
        _shipdate = shipdate;
        _status = status;
        _onlineorderflag = onlineorderflag;
        _salesordernumber = salesordernumber;
        _purchaseordernumber = purchaseordernumber;
        _accountnumber = accountnumber;
        _customerid = customerid;
        _salespersonid = salespersonid;
        _territoryid = territoryid;
        _billtoaddressid = billtoaddressid;
        _shiptoaddressid = shiptoaddressid;
        _shipmethodid = shipmethodid;
        _creditcardid = creditcardid;
        _creditcardapprovalcode = creditcardapprovalcode;
        _currencyrateid = currencyrateid;
        _subtotal = subtotal;
        _taxamt = taxamt;
        _freight = freight;
        _totaldue = totaldue;
        _comment = comment;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Salesorderid
    {
        get => _salesorderid;
        set => _salesorderid = value;
    }
    public byte Revisionnumber
    {
        get => _revisionnumber;
        set => _revisionnumber = value;
    }
    public DateTime Orderdate
    {
        get => _orderdate;
        set => _orderdate = value;
    }
    public DateTime Duedate
    {
        get => _duedate;
        set => _duedate = value;
    }
    public DateTime? Shipdate
    {
        get => _shipdate;
        set => _shipdate = value;
    }
    public byte Status
    {
        get => _status;
        set => _status = value;
    }
    public bool Onlineorderflag
    {
        get => _onlineorderflag;
        set => _onlineorderflag = value;
    }
    public string Salesordernumber
    {
        get => _salesordernumber;
        set => _salesordernumber = value;
    }
    public string? Purchaseordernumber
    {
        get => _purchaseordernumber;
        set => _purchaseordernumber = value;
    }
    public string? Accountnumber
    {
        get => _accountnumber;
        set => _accountnumber = value;
    }
    public int Customerid
    {
        get => _customerid;
        set => _customerid = value;
    }
    public int? Salespersonid
    {
        get => _salespersonid;
        set => _salespersonid = value;
    }
    public int? Territoryid
    {
        get => _territoryid;
        set => _territoryid = value;
    }
    public int Billtoaddressid
    {
        get => _billtoaddressid;
        set => _billtoaddressid = value;
    }
    public int Shiptoaddressid
    {
        get => _shiptoaddressid;
        set => _shiptoaddressid = value;
    }
    public int Shipmethodid
    {
        get => _shipmethodid;
        set => _shipmethodid = value;
    }
    public int? Creditcardid
    {
        get => _creditcardid;
        set => _creditcardid = value;
    }
    public string? Creditcardapprovalcode
    {
        get => _creditcardapprovalcode;
        set => _creditcardapprovalcode = value;
    }
    public int? Currencyrateid
    {
        get => _currencyrateid;
        set => _currencyrateid = value;
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
    public string? Comment
    {
        get => _comment;
        set => _comment = value;
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
