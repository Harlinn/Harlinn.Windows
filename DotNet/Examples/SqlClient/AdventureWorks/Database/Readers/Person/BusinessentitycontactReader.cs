using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Person;

public class BusinessentitycontactReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[BusinessEntityContact]";
    public const string TableName = "BusinessEntityContact";
    public const string ShortName = "b1";
    public const string Sql = """
        SELECT
          b1.[Businessentityid],
          b1.[Personid],
          b1.[Contacttypeid],
          b1.[Rowguid],
          b1.[Modifieddate]
        FROM
          [Person].[BusinessEntityContact] b1
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int PERSONID_FIELD_ID = 1;
    public const int CONTACTTYPEID_FIELD_ID = 2;
    public const int ROWGUID_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public BusinessentitycontactReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Personid
    {
        get
        {
            return Reader.GetInt32(PERSONID_FIELD_ID);
        }
    }

    public int Contacttypeid
    {
        get
        {
            return Reader.GetInt32(CONTACTTYPEID_FIELD_ID);
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


    public Types.Person.BusinessentitycontactDataType ToDataObject()
    {
        return new Types.Person.BusinessentitycontactDataType(Businessentityid,
            Personid,
            Contacttypeid,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Person.BusinessentitycontactDataType> ToList()
    {
        var list = new List<Types.Person.BusinessentitycontactDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
