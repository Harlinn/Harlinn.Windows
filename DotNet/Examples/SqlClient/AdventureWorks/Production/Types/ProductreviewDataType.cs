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
