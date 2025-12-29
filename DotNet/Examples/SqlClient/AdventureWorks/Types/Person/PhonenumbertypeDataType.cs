using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Person;

public class PhonenumbertypeDataType
{
    int _phonenumbertypeid = 0;
    string _name = string.Empty;
    DateTime _modifieddate;

    public PhonenumbertypeDataType( )
    {
    }

    public PhonenumbertypeDataType(int phonenumbertypeid,
        string name,
        DateTime modifieddate)
    {
        _phonenumbertypeid = phonenumbertypeid;
        _name = name;
        _modifieddate = modifieddate;
    }

    public int Phonenumbertypeid
    {
        get => _phonenumbertypeid;
        set => _phonenumbertypeid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
