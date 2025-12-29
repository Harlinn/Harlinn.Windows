using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class LocationReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[Location]";
    public const string TableName = "Location";
    public const string ShortName = "l";
    public const string Sql = """
        SELECT
          l.[Locationid],
          l.[Name],
          l.[Costrate],
          l.[Availability],
          l.[Modifieddate]
        FROM
          [Production].[Location] l
        """;

    public const int LOCATIONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int COSTRATE_FIELD_ID = 2;
    public const int AVAILABILITY_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public LocationReader(SqlDataReader reader, bool ownsReader = false)
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

    public short Locationid
    {
        get
        {
            return Reader.GetInt16(LOCATIONID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public decimal Costrate
    {
        get
        {
            return Reader.GetDecimal(COSTRATE_FIELD_ID);
        }
    }

    public decimal Availability
    {
        get
        {
            return Reader.GetDecimal(AVAILABILITY_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.Production.LocationDataType ToDataObject()
    {
        return new Types.Production.LocationDataType(Locationid,
            Name,
            Costrate,
            Availability,
            Modifieddate);
    }

    public List<Types.Production.LocationDataType> ToList()
    {
        var list = new List<Types.Production.LocationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
