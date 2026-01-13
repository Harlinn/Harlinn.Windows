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

public class ProductreviewDataType
{
    int _productreviewid = 0;
    int _productid = 0;
    string _reviewername = string.Empty;
    DateTime _reviewdate;
    string _emailaddress = string.Empty;
    int _rating = 0;
    string? _comments;
    DateTime _modifieddate;

    public ProductreviewDataType( )
    {
    }

    public ProductreviewDataType(int productreviewid,
        int productid,
        string reviewername,
        DateTime reviewdate,
        string emailaddress,
        int rating,
        string? comments,
        DateTime modifieddate)
    {
        _productreviewid = productreviewid;
        _productid = productid;
        _reviewername = reviewername;
        _reviewdate = reviewdate;
        _emailaddress = emailaddress;
        _rating = rating;
        _comments = comments;
        _modifieddate = modifieddate;
    }

    public int Productreviewid
    {
        get => _productreviewid;
        set => _productreviewid = value;
    }
    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public string Reviewername
    {
        get => _reviewername;
        set => _reviewername = value;
    }
    public DateTime Reviewdate
    {
        get => _reviewdate;
        set => _reviewdate = value;
    }
    public string Emailaddress
    {
        get => _emailaddress;
        set => _emailaddress = value;
    }
    public int Rating
    {
        get => _rating;
        set => _rating = value;
    }
    public string? Comments
    {
        get => _comments;
        set => _comments = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
