using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Person;

public class BusinessentitycontactDataType
{
    int _businessentityid = 0;
    int _personid = 0;
    int _contacttypeid = 0;
    Guid _rowguid;
    DateTime _modifieddate;

    public BusinessentitycontactDataType( )
    {
    }

    public BusinessentitycontactDataType(int businessentityid,
        int personid,
        int contacttypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _personid = personid;
        _contacttypeid = contacttypeid;
        _rowguid = rowguid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public int Personid
    {
        get => _personid;
        set => _personid = value;
    }
    public int Contacttypeid
    {
        get => _contacttypeid;
        set => _contacttypeid = value;
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
