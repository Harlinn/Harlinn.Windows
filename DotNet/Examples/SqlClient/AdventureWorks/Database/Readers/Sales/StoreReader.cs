using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

public class StoreReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[Store]";
    public const string TableName = "Store";
    public const string ShortName = "s15";
    public const string Sql = """
        SELECT
          s15.[Businessentityid],
          s15.[Name],
          s15.[Salespersonid],
          s15.[Demographics],
          s15.[Rowguid],
          s15.[Modifieddate]
        FROM
          [Sales].[Store] s15
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int SALESPERSONID_FIELD_ID = 2;
    public const int DEMOGRAPHICS_FIELD_ID = 3;
    public const int ROWGUID_FIELD_ID = 4;
    public const int MODIFIEDDATE_FIELD_ID = 5;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public StoreReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public int? Salespersonid
    {
        get
        {
            return Reader.GetNullableInt32(SALESPERSONID_FIELD_ID);
        }
    }

    public SqlXml? Demographics
    {
        get
        {
            return Reader.GetNullableSqlXml(DEMOGRAPHICS_FIELD_ID);
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


    public Types.Sales.StoreDataType ToDataObject()
    {
        return new Types.Sales.StoreDataType(Businessentityid,
            Name,
            Salespersonid,
            Demographics,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Sales.StoreDataType> ToList()
    {
        var list = new List<Types.Sales.StoreDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
