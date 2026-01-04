using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Sales.Types;

public class VstorewithcontactsDataType
{
    readonly int _businessentityid = 0;
    readonly string _name = string.Empty;
    readonly string _contacttype = string.Empty;
    readonly string? _title;
    readonly string _firstname = string.Empty;
    readonly string? _middlename;
    readonly string _lastname = string.Empty;
    readonly string? _suffix;
    readonly string? _phonenumber;
    readonly string? _phonenumbertype;
    readonly string? _emailaddress;
    readonly int _emailpromotion = 0;

    public VstorewithcontactsDataType( )
    {
    }

    public VstorewithcontactsDataType(int businessentityid,
        string name,
        string contacttype,
        string? title,
        string firstname,
        string? middlename,
        string lastname,
        string? suffix,
        string? phonenumber,
        string? phonenumbertype,
        string? emailaddress,
        int emailpromotion)
    {
        _businessentityid = businessentityid;
        _name = name;
        _contacttype = contacttype;
        _title = title;
        _firstname = firstname;
        _middlename = middlename;
        _lastname = lastname;
        _suffix = suffix;
        _phonenumber = phonenumber;
        _phonenumbertype = phonenumbertype;
        _emailaddress = emailaddress;
        _emailpromotion = emailpromotion;
    }

    public int Businessentityid => _businessentityid;
    public string Name => _name;
    public string Contacttype => _contacttype;
    public string? Title => _title;
    public string Firstname => _firstname;
    public string? Middlename => _middlename;
    public string Lastname => _lastname;
    public string? Suffix => _suffix;
    public string? Phonenumber => _phonenumber;
    public string? Phonenumbertype => _phonenumbertype;
    public string? Emailaddress => _emailaddress;
    public int Emailpromotion => _emailpromotion;
}
