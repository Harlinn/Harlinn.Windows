using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Person;

public class VstateprovincecountryregionReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[vStateProvinceCountryRegion]";
    public const string TableName = "vStateProvinceCountryRegion";
    public const string ShortName = "v6";
    public const string Sql = """
        SELECT
          v6.[Stateprovinceid],
          v6.[Stateprovincecode],
          v6.[Isonlystateprovinceflag],
          v6.[Stateprovincename],
          v6.[Territoryid],
          v6.[Countryregioncode],
          v6.[Countryregionname]
        FROM
          [Person].[vStateProvinceCountryRegion] v6
        """;

    public const int STATEPROVINCEID_FIELD_ID = 0;
    public const int STATEPROVINCECODE_FIELD_ID = 1;
    public const int ISONLYSTATEPROVINCEFLAG_FIELD_ID = 2;
    public const int STATEPROVINCENAME_FIELD_ID = 3;
    public const int TERRITORYID_FIELD_ID = 4;
    public const int COUNTRYREGIONCODE_FIELD_ID = 5;
    public const int COUNTRYREGIONNAME_FIELD_ID = 6;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VstateprovincecountryregionReader(SqlDataReader reader, bool ownsReader = false)
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

    public bool Isonlystateprovinceflag
    {
        get
        {
            return Reader.GetBoolean(ISONLYSTATEPROVINCEFLAG_FIELD_ID);
        }
    }

    public string Stateprovincename
    {
        get
        {
            return Reader.GetString(STATEPROVINCENAME_FIELD_ID);
        }
    }

    public int Territoryid
    {
        get
        {
            return Reader.GetInt32(TERRITORYID_FIELD_ID);
        }
    }

    public string Countryregioncode
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONCODE_FIELD_ID);
        }
    }

    public string Countryregionname
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONNAME_FIELD_ID);
        }
    }


    public Types.Person.VstateprovincecountryregionDataType ToDataObject()
    {
        return new Types.Person.VstateprovincecountryregionDataType(Stateprovinceid,
            Stateprovincecode,
            Isonlystateprovinceflag,
            Stateprovincename,
            Territoryid,
            Countryregioncode,
            Countryregionname);
    }

    public List<Types.Person.VstateprovincecountryregionDataType> ToList()
    {
        var list = new List<Types.Person.VstateprovincecountryregionDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
