using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Person;

public class BusinessentityReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[BusinessEntity]";
    public const string TableName = "BusinessEntity";
    public const string ShortName = "b";
    public const string Sql = """
        SELECT
          b.[Businessentityid],
          b.[Rowguid],
          b.[Modifieddate]
        FROM
          [Person].[BusinessEntity] b
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int ROWGUID_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public BusinessentityReader(SqlDataReader reader, bool ownsReader = false)
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


    public Types.Person.BusinessentityDataType ToDataObject()
    {
        return new Types.Person.BusinessentityDataType(Businessentityid,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Person.BusinessentityDataType> ToList()
    {
        var list = new List<Types.Person.BusinessentityDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
