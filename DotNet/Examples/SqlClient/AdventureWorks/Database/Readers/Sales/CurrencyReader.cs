using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

public class CurrencyReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[Currency]";
    public const string TableName = "Currency";
    public const string ShortName = "c4";
    public const string Sql = """
        SELECT
          c4.[Currencycode],
          c4.[Name],
          c4.[Modifieddate]
        FROM
          [Sales].[Currency] c4
        """;

    public const int CURRENCYCODE_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public CurrencyReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Currencycode
    {
        get
        {
            return Reader.GetString(CURRENCYCODE_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Sales.CurrencyDataType ToDataObject()
    {
        return new Types.Sales.CurrencyDataType(Currencycode,
            Name,
            Modifieddate);
    }

    public List<Types.Sales.CurrencyDataType> ToList()
    {
        var list = new List<Types.Sales.CurrencyDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
