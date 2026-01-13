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

public class VproductmodelcatalogdescriptionDataType
{
    readonly int _productmodelid = 0;
    readonly string _name = string.Empty;
    readonly string? _summary;
    readonly string? _manufacturer;
    readonly string? _copyright;
    readonly string? _producturl;
    readonly string? _warrantyperiod;
    readonly string? _warrantydescription;
    readonly string? _noofyears;
    readonly string? _maintenancedescription;
    readonly string? _wheel;
    readonly string? _saddle;
    readonly string? _pedal;
    readonly string? _bikeframe;
    readonly string? _crankset;
    readonly string? _pictureangle;
    readonly string? _picturesize;
    readonly string? _productphotoid;
    readonly string? _material;
    readonly string? _color;
    readonly string? _productline;
    readonly string? _style;
    readonly string? _riderexperience;
    readonly Guid _rowguid;
    readonly DateTime _modifieddate;

    public VproductmodelcatalogdescriptionDataType( )
    {
    }

    public VproductmodelcatalogdescriptionDataType(int productmodelid,
        string name,
        string? summary,
        string? manufacturer,
        string? copyright,
        string? producturl,
        string? warrantyperiod,
        string? warrantydescription,
        string? noofyears,
        string? maintenancedescription,
        string? wheel,
        string? saddle,
        string? pedal,
        string? bikeframe,
        string? crankset,
        string? pictureangle,
        string? picturesize,
        string? productphotoid,
        string? material,
        string? color,
        string? productline,
        string? style,
        string? riderexperience,
        Guid rowguid,
        DateTime modifieddate)
    {
        _productmodelid = productmodelid;
        _name = name;
        _summary = summary;
        _manufacturer = manufacturer;
        _copyright = copyright;
        _producturl = producturl;
        _warrantyperiod = warrantyperiod;
        _warrantydescription = warrantydescription;
        _noofyears = noofyears;
        _maintenancedescription = maintenancedescription;
        _wheel = wheel;
        _saddle = saddle;
        _pedal = pedal;
        _bikeframe = bikeframe;
        _crankset = crankset;
        _pictureangle = pictureangle;
        _picturesize = picturesize;
        _productphotoid = productphotoid;
        _material = material;
        _color = color;
        _productline = productline;
        _style = style;
        _riderexperience = riderexperience;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Productmodelid => _productmodelid;
    public string Name => _name;
    public string? Summary => _summary;
    public string? Manufacturer => _manufacturer;
    public string? Copyright => _copyright;
    public string? Producturl => _producturl;
    public string? Warrantyperiod => _warrantyperiod;
    public string? Warrantydescription => _warrantydescription;
    public string? Noofyears => _noofyears;
    public string? Maintenancedescription => _maintenancedescription;
    public string? Wheel => _wheel;
    public string? Saddle => _saddle;
    public string? Pedal => _pedal;
    public string? Bikeframe => _bikeframe;
    public string? Crankset => _crankset;
    public string? Pictureangle => _pictureangle;
    public string? Picturesize => _picturesize;
    public string? Productphotoid => _productphotoid;
    public string? Material => _material;
    public string? Color => _color;
    public string? Productline => _productline;
    public string? Style => _style;
    public string? Riderexperience => _riderexperience;
    public Guid Rowguid => _rowguid;
    public DateTime Modifieddate => _modifieddate;
}
