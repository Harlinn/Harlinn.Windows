using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Person;

public class PasswordDataType
{
    int _businessentityid = 0;
    string _passwordhash = string.Empty;
    string _passwordsalt = string.Empty;
    Guid _rowguid;
    DateTime _modifieddate;

    public PasswordDataType( )
    {
    }

    public PasswordDataType(int businessentityid,
        string passwordhash,
        string passwordsalt,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _passwordhash = passwordhash;
        _passwordsalt = passwordsalt;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public string Passwordhash
    {
        get => _passwordhash;
        set => _passwordhash = value;
    }
    public string Passwordsalt
    {
        get => _passwordsalt;
        set => _passwordsalt = value;
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
