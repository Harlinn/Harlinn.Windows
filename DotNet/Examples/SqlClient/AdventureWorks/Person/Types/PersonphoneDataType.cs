using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Person.Types;

public class PersonphoneDataType
{
    int _businessentityid = 0;
    string _phonenumber = string.Empty;
    int _phonenumbertypeid = 0;
    DateTime _modifieddate;

    public PersonphoneDataType( )
    {
    }

    public PersonphoneDataType(int businessentityid,
        string phonenumber,
        int phonenumbertypeid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _phonenumber = phonenumber;
        _phonenumbertypeid = phonenumbertypeid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public string Phonenumber
    {
        get => _phonenumber;
        set => _phonenumber = value;
    }
    public int Phonenumbertypeid
    {
        get => _phonenumbertypeid;
        set => _phonenumbertypeid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
