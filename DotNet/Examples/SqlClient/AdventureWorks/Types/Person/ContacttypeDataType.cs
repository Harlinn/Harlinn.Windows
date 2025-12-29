using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Person;

public class ContacttypeDataType
{
    int _contacttypeid = 0;
    string _name = string.Empty;
    DateTime _modifieddate;

    public ContacttypeDataType( )
    {
    }

    public ContacttypeDataType(int contacttypeid,
        string name,
        DateTime modifieddate)
    {
        _contacttypeid = contacttypeid;
        _name = name;
        _modifieddate = modifieddate;
    }

    public int Contacttypeid
    {
        get => _contacttypeid;
        set => _contacttypeid = value;
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
