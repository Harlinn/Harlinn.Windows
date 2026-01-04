using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Person.Types;

public class BusinessentityDataType
{
    int _businessentityid = 0;
    Guid _rowguid;
    DateTime _modifieddate;

    public BusinessentityDataType( )
    {
    }

    public BusinessentityDataType(int businessentityid,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
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
