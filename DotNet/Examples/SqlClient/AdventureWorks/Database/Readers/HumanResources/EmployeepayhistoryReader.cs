using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.HumanResources;

public class EmployeepayhistoryReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[EmployeePayHistory]";
    public const string TableName = "EmployeePayHistory";
    public const string ShortName = "e2";
    public const string Sql = """
        SELECT
          e2.[Businessentityid],
          e2.[Ratechangedate],
          e2.[Rate],
          e2.[Payfrequency],
          e2.[Modifieddate]
        FROM
          [HumanResources].[EmployeePayHistory] e2
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int RATECHANGEDATE_FIELD_ID = 1;
    public const int RATE_FIELD_ID = 2;
    public const int PAYFREQUENCY_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public EmployeepayhistoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public DateTime Ratechangedate
    {
        get
        {
            return Reader.GetDateTime(RATECHANGEDATE_FIELD_ID);
        }
    }

    public decimal Rate
    {
        get
        {
            return Reader.GetDecimal(RATE_FIELD_ID);
        }
    }

    public byte Payfrequency
    {
        get
        {
            return Reader.GetByte(PAYFREQUENCY_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.HumanResources.EmployeepayhistoryDataType ToDataObject()
    {
        return new Types.HumanResources.EmployeepayhistoryDataType(Businessentityid,
            Ratechangedate,
            Rate,
            Payfrequency,
            Modifieddate);
    }

    public List<Types.HumanResources.EmployeepayhistoryDataType> ToList()
    {
        var list = new List<Types.HumanResources.EmployeepayhistoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
