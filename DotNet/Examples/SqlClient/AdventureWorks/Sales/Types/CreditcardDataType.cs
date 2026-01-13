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

public class CreditcardDataType
{
    int _creditcardid = 0;
    string _cardtype = string.Empty;
    string _cardnumber = string.Empty;
    byte _expmonth = 0;
    short _expyear = 0;
    DateTime _modifieddate;

    public CreditcardDataType( )
    {
    }

    public CreditcardDataType(int creditcardid,
        string cardtype,
        string cardnumber,
        byte expmonth,
        short expyear,
        DateTime modifieddate)
    {
        _creditcardid = creditcardid;
        _cardtype = cardtype;
        _cardnumber = cardnumber;
        _expmonth = expmonth;
        _expyear = expyear;
        _modifieddate = modifieddate;
    }

    public int Creditcardid
    {
        get => _creditcardid;
        set => _creditcardid = value;
    }
    public string Cardtype
    {
        get => _cardtype;
        set => _cardtype = value;
    }
    public string Cardnumber
    {
        get => _cardnumber;
        set => _cardnumber = value;
    }
    public byte Expmonth
    {
        get => _expmonth;
        set => _expmonth = value;
    }
    public short Expyear
    {
        get => _expyear;
        set => _expyear = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
