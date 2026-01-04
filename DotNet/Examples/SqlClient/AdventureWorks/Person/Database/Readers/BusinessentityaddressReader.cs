using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Person.Database.Readers;

public class BusinessentityaddressReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[BusinessEntityAddress]";
    public const string TableName = "BusinessEntityAddress";
    public const string ShortName = "b0";
    public const string Sql = """
        SELECT
          b0.[Businessentityid],
          b0.[Addressid],
          b0.[Addresstypeid],
          b0.[Rowguid],
          b0.[Modifieddate]
        FROM
          [Person].[BusinessEntityAddress] b0
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int ADDRESSID_FIELD_ID = 1;
    public const int ADDRESSTYPEID_FIELD_ID = 2;
    public const int ROWGUID_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public BusinessentityaddressReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Addressid
    {
        get
        {
            return Reader.GetInt32(ADDRESSID_FIELD_ID);
        }
    }

    public int Addresstypeid
    {
        get
        {
            return Reader.GetInt32(ADDRESSTYPEID_FIELD_ID);
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


    public AdventureWorks.Person.Types.BusinessentityaddressDataType ToDataObject()
    {
        return new AdventureWorks.Person.Types.BusinessentityaddressDataType(Businessentityid,
            Addressid,
            Addresstypeid,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Person.Types.BusinessentityaddressDataType> ToList()
    {
        var list = new List<AdventureWorks.Person.Types.BusinessentityaddressDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
