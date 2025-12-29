using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Person;

public class PersonDataType
{
    int _businessentityid = 0;
    string _persontype = string.Empty;
    bool _namestyle = false;
    string? _title;
    string _firstname = string.Empty;
    string? _middlename;
    string _lastname = string.Empty;
    string? _suffix;
    int _emailpromotion = 0;
    SqlXml? _additionalcontactinfo;
    SqlXml? _demographics;
    Guid _rowguid;
    DateTime _modifieddate;

    public PersonDataType( )
    {
    }

    public PersonDataType(int businessentityid,
        string persontype,
        bool namestyle,
        string? title,
        string firstname,
        string? middlename,
        string lastname,
        string? suffix,
        int emailpromotion,
        SqlXml? additionalcontactinfo,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _persontype = persontype;
        _namestyle = namestyle;
        _title = title;
        _firstname = firstname;
        _middlename = middlename;
        _lastname = lastname;
        _suffix = suffix;
        _emailpromotion = emailpromotion;
        _additionalcontactinfo = additionalcontactinfo;
        _demographics = demographics;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public string Persontype
    {
        get => _persontype;
        set => _persontype = value;
    }
    public bool Namestyle
    {
        get => _namestyle;
        set => _namestyle = value;
    }
    public string? Title
    {
        get => _title;
        set => _title = value;
    }
    public string Firstname
    {
        get => _firstname;
        set => _firstname = value;
    }
    public string? Middlename
    {
        get => _middlename;
        set => _middlename = value;
    }
    public string Lastname
    {
        get => _lastname;
        set => _lastname = value;
    }
    public string? Suffix
    {
        get => _suffix;
        set => _suffix = value;
    }
    public int Emailpromotion
    {
        get => _emailpromotion;
        set => _emailpromotion = value;
    }
    public SqlXml? Additionalcontactinfo
    {
        get => _additionalcontactinfo;
        set => _additionalcontactinfo = value;
    }
    public SqlXml? Demographics
    {
        get => _demographics;
        set => _demographics = value;
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
