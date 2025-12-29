using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Person;

public class BusinessentityaddressDataType
{
    int _businessentityid = 0;
    int _addressid = 0;
    int _addresstypeid = 0;
    Guid _rowguid;
    DateTime _modifieddate;

    public BusinessentityaddressDataType( )
    {
    }

    public BusinessentityaddressDataType(int businessentityid,
        int addressid,
        int addresstypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _addressid = addressid;
        _addresstypeid = addresstypeid;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public int Addressid
    {
        get => _addressid;
        set => _addressid = value;
    }
    public int Addresstypeid
    {
        get => _addresstypeid;
        set => _addresstypeid = value;
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
