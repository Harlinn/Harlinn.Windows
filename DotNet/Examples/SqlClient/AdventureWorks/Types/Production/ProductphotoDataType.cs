using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Production;

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
