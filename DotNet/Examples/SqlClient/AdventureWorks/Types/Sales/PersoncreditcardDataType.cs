using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.Sales;

public class PersoncreditcardDataType
{
    int _businessentityid = 0;
    int _creditcardid = 0;
    DateTime _modifieddate;

    public PersoncreditcardDataType( )
    {
    }

    public PersoncreditcardDataType(int businessentityid,
        int creditcardid,
        DateTime modifieddate)
    {
        _businessentityid = businessentityid;
        _creditcardid = creditcardid;
        _modifieddate = modifieddate;
    }

    public int Businessentityid
    {
        get => _businessentityid;
        set => _businessentityid = value;
    }
    public int Creditcardid
    {
        get => _creditcardid;
        set => _creditcardid = value;
    }
    public DateTime Modifieddate
    {
        get => _modifieddate;
        set => _modifieddate = value;
    }
}
