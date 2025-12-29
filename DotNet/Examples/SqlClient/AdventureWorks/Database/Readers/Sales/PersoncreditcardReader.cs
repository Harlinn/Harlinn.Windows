using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

public class PersoncreditcardReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[PersonCreditCard]";
    public const string TableName = "PersonCreditCard";
    public const string ShortName = "p20";
    public const string Sql = """
        SELECT
          p20.[Businessentityid],
          p20.[Creditcardid],
          p20.[Modifieddate]
        FROM
          [Sales].[PersonCreditCard] p20
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int CREDITCARDID_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public PersoncreditcardReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Businessentityid
    {
        get
        {
            return Reader.GetInt32(BUSINESSENTITYID_FIELD_ID);
        }
    }

    public int Creditcardid
    {
        get
        {
            return Reader.GetInt32(CREDITCARDID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Sales.PersoncreditcardDataType ToDataObject()
    {
        return new Types.Sales.PersoncreditcardDataType(Businessentityid,
            Creditcardid,
            Modifieddate);
    }

    public List<Types.Sales.PersoncreditcardDataType> ToList()
    {
        var list = new List<Types.Sales.PersoncreditcardDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
