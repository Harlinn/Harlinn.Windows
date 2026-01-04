using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Sales.Database.Readers;

public class CreditcardReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[CreditCard]";
    public const string TableName = "CreditCard";
    public const string ShortName = "c3";
    public const string Sql = """
        SELECT
          c3.[Creditcardid],
          c3.[Cardtype],
          c3.[Cardnumber],
          c3.[Expmonth],
          c3.[Expyear],
          c3.[Modifieddate]
        FROM
          [Sales].[CreditCard] c3
        """;

    public const int CREDITCARDID_FIELD_ID = 0;
    public const int CARDTYPE_FIELD_ID = 1;
    public const int CARDNUMBER_FIELD_ID = 2;
    public const int EXPMONTH_FIELD_ID = 3;
    public const int EXPYEAR_FIELD_ID = 4;
    public const int MODIFIEDDATE_FIELD_ID = 5;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public CreditcardReader(SqlDataReader reader, bool ownsReader = false)
    {
        _reader = reader;
        _ownsReader = ownsReader;
    }

    public SqlDataReader Reader => _reader;

    public void Dispose()
    {
        if (_ownsReader)
        {
            ((IDisposable)_reader).Dispose();
        }
    }

    public bool Read()
    {
        return _reader.Read();
    }

    public int Creditcardid
    {
        get
        {
            return Reader.GetInt32(CREDITCARDID_FIELD_ID);
        }
    }

    public string Cardtype
    {
        get
        {
            return Reader.GetString(CARDTYPE_FIELD_ID);
        }
    }

    public string Cardnumber
    {
        get
        {
            return Reader.GetString(CARDNUMBER_FIELD_ID);
        }
    }

    public byte Expmonth
    {
        get
        {
            return Reader.GetByte(EXPMONTH_FIELD_ID);
        }
    }

    public short Expyear
    {
        get
        {
            return Reader.GetInt16(EXPYEAR_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Sales.Types.CreditcardDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.CreditcardDataType(Creditcardid,
            Cardtype,
            Cardnumber,
            Expmonth,
            Expyear,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.CreditcardDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.CreditcardDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
