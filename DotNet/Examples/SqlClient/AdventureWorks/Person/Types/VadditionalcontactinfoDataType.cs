using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Person.Types;

public class VadditionalcontactinfoDataType
{
    readonly int _businessentityid = 0;
    readonly string _firstname = string.Empty;
    readonly string? _middlename;
    readonly string _lastname = string.Empty;
    readonly string? _telephonenumber;
    readonly string? _telephonespecialinstructions;
    readonly string? _street;
    readonly string? _city;
    readonly string? _stateprovince;
    readonly string? _postalcode;
    readonly string? _countryregion;
    readonly string? _homeaddressspecialinstructions;
    readonly string? _emailaddress;
    readonly string? _emailspecialinstructions;
    readonly string? _emailtelephonenumber;
    readonly Guid _rowguid;
    readonly DateTime _modifieddate;

    public VadditionalcontactinfoDataType( )
    {
    }

    public VadditionalcontactinfoDataType(int businessentityid,
        string firstname,
        string? middlename,
        string lastname,
        string? telephonenumber,
        string? telephonespecialinstructions,
        string? street,
        string? city,
        string? stateprovince,
        string? postalcode,
        string? countryregion,
        string? homeaddressspecialinstructions,
        string? emailaddress,
        string? emailspecialinstructions,
        string? emailtelephonenumber,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _firstname = firstname;
        _middlename = middlename;
        _lastname = lastname;
        _telephonenumber = telephonenumber;
        _telephonespecialinstructions = telephonespecialinstructions;
        _street = street;
        _city = city;
        _stateprovince = stateprovince;
        _postalcode = postalcode;
        _countryregion = countryregion;
        _homeaddressspecialinstructions = homeaddressspecialinstructions;
        _emailaddress = emailaddress;
        _emailspecialinstructions = emailspecialinstructions;
        _emailtelephonenumber = emailtelephonenumber;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid => _businessentityid;
    public string Firstname => _firstname;
    public string? Middlename => _middlename;
    public string Lastname => _lastname;
    public string? Telephonenumber => _telephonenumber;
    public string? Telephonespecialinstructions => _telephonespecialinstructions;
    public string? Street => _street;
    public string? City => _city;
    public string? Stateprovince => _stateprovince;
    public string? Postalcode => _postalcode;
    public string? Countryregion => _countryregion;
    public string? Homeaddressspecialinstructions => _homeaddressspecialinstructions;
    public string? Emailaddress => _emailaddress;
    public string? Emailspecialinstructions => _emailspecialinstructions;
    public string? Emailtelephonenumber => _emailtelephonenumber;
    public Guid Rowguid => _rowguid;
    public DateTime Modifieddate => _modifieddate;
}
