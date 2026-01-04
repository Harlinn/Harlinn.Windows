using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Person.Database.Readers;

public class StateprovinceReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[StateProvince]";
    public const string TableName = "StateProvince";
    public const string ShortName = "s0";
    public const string Sql = """
        SELECT
          s0.[Stateprovinceid],
          s0.[Stateprovincecode],
          s0.[Countryregioncode],
          s0.[Isonlystateprovinceflag],
          s0.[Name],
          s0.[Territoryid],
          s0.[Rowguid],
          s0.[Modifieddate]
        FROM
          [Person].[StateProvince] s0
        """;

    public const int STATEPROVINCEID_FIELD_ID = 0;
    public const int STATEPROVINCECODE_FIELD_ID = 1;
    public const int COUNTRYREGIONCODE_FIELD_ID = 2;
    public const int ISONLYSTATEPROVINCEFLAG_FIELD_ID = 3;
    public const int NAME_FIELD_ID = 4;
    public const int TERRITORYID_FIELD_ID = 5;
    public const int ROWGUID_FIELD_ID = 6;
    public const int MODIFIEDDATE_FIELD_ID = 7;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public StateprovinceReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Stateprovinceid
    {
        get
        {
            return Reader.GetInt32(STATEPROVINCEID_FIELD_ID);
        }
    }

    public string Stateprovincecode
    {
        get
        {
            return Reader.GetString(STATEPROVINCECODE_FIELD_ID);
        }
    }

    public string Countryregioncode
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONCODE_FIELD_ID);
        }
    }

    public bool Isonlystateprovinceflag
    {
        get
        {
            return Reader.GetBoolean(ISONLYSTATEPROVINCEFLAG_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public int Territoryid
    {
        get
        {
            return Reader.GetInt32(TERRITORYID_FIELD_ID);
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


    public AdventureWorks.Person.Types.StateprovinceDataType ToDataObject()
    {
        return new AdventureWorks.Person.Types.StateprovinceDataType(Stateprovinceid,
            Stateprovincecode,
            Countryregioncode,
            Isonlystateprovinceflag,
            Name,
            Territoryid,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Person.Types.StateprovinceDataType> ToList()
    {
        var list = new List<AdventureWorks.Person.Types.StateprovinceDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
