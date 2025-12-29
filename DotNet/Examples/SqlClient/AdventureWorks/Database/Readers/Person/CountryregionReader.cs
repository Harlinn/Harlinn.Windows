using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Person;

public class CountryregionReader : IDisposable
{
    public const string QualifiedTableName = "[Person].[CountryRegion]";
    public const string TableName = "CountryRegion";
    public const string ShortName = "c0";
    public const string Sql = """
        SELECT
          c0.[Countryregioncode],
          c0.[Name],
          c0.[Modifieddate]
        FROM
          [Person].[CountryRegion] c0
        """;

    public const int COUNTRYREGIONCODE_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int MODIFIEDDATE_FIELD_ID = 2;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public CountryregionReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Countryregioncode
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONCODE_FIELD_ID);
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


    public Types.Person.CountryregionDataType ToDataObject()
    {
        return new Types.Person.CountryregionDataType(Countryregioncode,
            Name,
            Modifieddate);
    }

    public List<Types.Person.CountryregionDataType> ToList()
    {
        var list = new List<Types.Person.CountryregionDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
