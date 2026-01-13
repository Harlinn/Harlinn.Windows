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

public class ProductphotoDataType
{
    int _productphotoid = 0;
    byte[]? _thumbnailphoto;
    string? _thumbnailphotofilename;
    byte[]? _largephoto;
    string? _largephotofilename;
    DateTime _modifieddate;

    public ProductphotoDataType( )
    {
    }

    public ProductphotoDataType(int productphotoid,
        byte[]? thumbnailphoto,
        string? thumbnailphotofilename,
        byte[]? largephoto,
        string? largephotofilename,
        DateTime modifieddate)
    {
        _productphotoid = productphotoid;
        _thumbnailphoto = thumbnailphoto;
        _thumbnailphotofilename = thumbnailphotofilename;
        _largephoto = largephoto;
        _largephotofilename = largephotofilename;
        _modifieddate = modifieddate;
    }

    public int Productphotoid
    {
        get => _productphotoid;
        set => _productphotoid = value;
    }
    public byte[]? Thumbnailphoto
    {
        get => _thumbnailphoto;
        set => _thumbnailphoto = value;
    }
    public string? Thumbnailphotofilename
    {
        get => _thumbnailphotofilename;
        set => _thumbnailphotofilename = value;
    }
    public byte[]? Largephoto
    {
        get => _largephoto;
        set => _largephoto = value;
    }
    public string? Largephotofilename
    {
        get => _largephotofilename;
        set => _largephotofilename = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
