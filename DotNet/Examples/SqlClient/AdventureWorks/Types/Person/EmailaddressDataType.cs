using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Person;

public class EmailaddressDataType
{
    int _businessentityid = 0;
    int _emailaddressid = 0;
    string? _emailaddress;
    Guid _rowguid;
    DateTime _modifieddate;

    public EmailaddressDataType( )
    {
    }

    public EmailaddressDataType(int businessentityid,
        int emailaddressid,
        string? emailaddress,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _emailaddressid = emailaddressid;
        _emailaddress = emailaddress;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public int Emailaddressid
    {
        get => _emailaddressid;
        set => _emailaddressid = value;
    }
    public string? Emailaddress
    {
        get => _emailaddress;
        set => _emailaddress = value;
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
