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

public class ProductDataType
{
    int _productid = 0;
    string _name = string.Empty;
    string _productnumber = string.Empty;
    bool _makeflag = false;
    bool _finishedgoodsflag = false;
    string? _color;
    short _safetystocklevel = 0;
    short _reorderpoint = 0;
    decimal _standardcost = 0m;
    decimal _listprice = 0m;
    string? _size;
    string? _sizeunitmeasurecode;
    string? _weightunitmeasurecode;
    decimal? _weight;
    int _daystomanufacture = 0;
    string? _productline;
    string? _class;
    string? _style;
    int? _productsubcategoryid;
    int? _productmodelid;
    DateTime _sellstartdate;
    DateTime? _sellenddate;
    DateTime? _discontinueddate;
    Guid _rowguid;
    DateTime _modifieddate;

    public ProductDataType( )
    {
    }

    public ProductDataType(int productid,
        string name,
        string productnumber,
        bool makeflag,
        bool finishedgoodsflag,
        string? color,
        short safetystocklevel,
        short reorderpoint,
        decimal standardcost,
        decimal listprice,
        string? size,
        string? sizeunitmeasurecode,
        string? weightunitmeasurecode,
        decimal? weight,
        int daystomanufacture,
        string? productline,
        string? class__,
        string? style,
        int? productsubcategoryid,
        int? productmodelid,
        DateTime sellstartdate,
        DateTime? sellenddate,
        DateTime? discontinueddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        _productid = productid;
        _name = name;
        _productnumber = productnumber;
        _makeflag = makeflag;
        _finishedgoodsflag = finishedgoodsflag;
        _color = color;
        _safetystocklevel = safetystocklevel;
        _reorderpoint = reorderpoint;
        _standardcost = standardcost;
        _listprice = listprice;
        _size = size;
        _sizeunitmeasurecode = sizeunitmeasurecode;
        _weightunitmeasurecode = weightunitmeasurecode;
        _weight = weight;
        _daystomanufacture = daystomanufacture;
        _productline = productline;
        _class = class__;
        _style = style;
        _productsubcategoryid = productsubcategoryid;
        _productmodelid = productmodelid;
        _sellstartdate = sellstartdate;
        _sellenddate = sellenddate;
        _discontinueddate = discontinueddate;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Productid
    {
        get => _productid;
        set => _productid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public string Productnumber
    {
        get => _productnumber;
        set => _productnumber = value;
    }
    public bool Makeflag
    {
        get => _makeflag;
        set => _makeflag = value;
    }
    public bool Finishedgoodsflag
    {
        get => _finishedgoodsflag;
        set => _finishedgoodsflag = value;
    }
    public string? Color
    {
        get => _color;
        set => _color = value;
    }
    public short Safetystocklevel
    {
        get => _safetystocklevel;
        set => _safetystocklevel = value;
    }
    public short Reorderpoint
    {
        get => _reorderpoint;
        set => _reorderpoint = value;
    }
    public decimal Standardcost
    {
        get => _standardcost;
        set => _standardcost = value;
    }
    public decimal Listprice
    {
        get => _listprice;
        set => _listprice = value;
    }
    public string? Size
    {
        get => _size;
        set => _size = value;
    }
    public string? Sizeunitmeasurecode
    {
        get => _sizeunitmeasurecode;
        set => _sizeunitmeasurecode = value;
    }
    public string? Weightunitmeasurecode
    {
        get => _weightunitmeasurecode;
        set => _weightunitmeasurecode = value;
    }
    public decimal? Weight
    {
        get => _weight;
        set => _weight = value;
    }
    public int Daystomanufacture
    {
        get => _daystomanufacture;
        set => _daystomanufacture = value;
    }
    public string? Productline
    {
        get => _productline;
        set => _productline = value;
    }
    public string? Class
    {
        get => _class;
        set => _class = value;
    }
    public string? Style
    {
        get => _style;
        set => _style = value;
    }
    public int? Productsubcategoryid
    {
        get => _productsubcategoryid;
        set => _productsubcategoryid = value;
    }
    public int? Productmodelid
    {
        get => _productmodelid;
        set => _productmodelid = value;
    }
    public DateTime Sellstartdate
    {
        get => _sellstartdate;
        set => _sellstartdate = value;
    }
    public DateTime? Sellenddate
    {
        get => _sellenddate;
        set => _sellenddate = value;
    }
    public DateTime? Discontinueddate
    {
        get => _discontinueddate;
        set => _discontinueddate = value;
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
