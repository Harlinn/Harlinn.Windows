using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Sales;

public class SalesreasonDataType
{
    int _salesreasonid = 0;
    string _name = string.Empty;
    string _reasontype = string.Empty;
    DateTime _modifieddate;

    public SalesreasonDataType( )
    {
    }

    public SalesreasonDataType(int salesreasonid,
        string name,
        string reasontype,
        DateTime modifieddate)
    {
        _salesreasonid = salesreasonid;
        _name = name;
        _reasontype = reasontype;
        _modifieddate = modifieddate;
    }

    public int Salesreasonid
    {
        get => _salesreasonid;
        set => _salesreasonid = value;
    }
    public string Name
    {
        get => _name;
        set => _name = value;
    }
    public string Reasontype
    {
        get => _reasontype;
        set => _reasontype = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
