using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Production.Types;

public class ScrapreasonDataType
{
    short _scrapreasonid = 0;
    string _name = string.Empty;
    DateTime _modifieddate;

    public ScrapreasonDataType( )
    {
    }

    public ScrapreasonDataType(short scrapreasonid,
        string name,
        DateTime modifieddate)
    {
        _scrapreasonid = scrapreasonid;
        _name = name;
        _modifieddate = modifieddate;
    }

    public short Scrapreasonid
    {
        get => _scrapreasonid;
        set => _scrapreasonid = value;
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
