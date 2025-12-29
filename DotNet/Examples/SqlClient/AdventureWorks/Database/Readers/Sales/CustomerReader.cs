using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

public class CustomerReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[Customer]";
    public const string TableName = "Customer";
    public const string ShortName = "c6";
    public const string Sql = """
        SELECT
          c6.[Customerid],
          c6.[Personid],
          c6.[Storeid],
          c6.[Territoryid],
          c6.[Accountnumber],
          c6.[Rowguid],
          c6.[Modifieddate]
        FROM
          [Sales].[Customer] c6
        """;

    public const int CUSTOMERID_FIELD_ID = 0;
    public const int PERSONID_FIELD_ID = 1;
    public const int STOREID_FIELD_ID = 2;
    public const int TERRITORYID_FIELD_ID = 3;
    public const int ACCOUNTNUMBER_FIELD_ID = 4;
    public const int ROWGUID_FIELD_ID = 5;
    public const int MODIFIEDDATE_FIELD_ID = 6;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public CustomerReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Customerid
    {
        get
        {
            return Reader.GetInt32(CUSTOMERID_FIELD_ID);
        }
    }

    public int? Personid
    {
        get
        {
            return Reader.GetNullableInt32(PERSONID_FIELD_ID);
        }
    }

    public int? Storeid
    {
        get
        {
            return Reader.GetNullableInt32(STOREID_FIELD_ID);
        }
    }

    public int? Territoryid
    {
        get
        {
            return Reader.GetNullableInt32(TERRITORYID_FIELD_ID);
        }
    }

    public string Accountnumber
    {
        get
        {
            return Reader.GetString(ACCOUNTNUMBER_FIELD_ID);
        }
    }

    public Guid Rowguid
    {
        get
        {
            return Reader.GetGuid(ROWGUID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Sales.CustomerDataType ToDataObject()
    {
        return new Types.Sales.CustomerDataType(Customerid,
            Personid,
            Storeid,
            Territoryid,
            Accountnumber,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Sales.CustomerDataType> ToList()
    {
        var list = new List<Types.Sales.CustomerDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
