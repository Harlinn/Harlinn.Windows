using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Person;

public class AddresstypeDataType
{
    int _addresstypeid = 0;
    string _name = string.Empty;
    Guid _rowguid;
    DateTime _modifieddate;

    public AddresstypeDataType( )
    {
    }

    public AddresstypeDataType(int addresstypeid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        _addresstypeid = addresstypeid;
        _name = name;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Addresstypeid
    {
        get => _addresstypeid;
        set => _addresstypeid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
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
