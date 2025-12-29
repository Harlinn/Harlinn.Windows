using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

public class VstorewithaddressesReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[vStoreWithAddresses]";
    public const string TableName = "vStoreWithAddresses";
    public const string ShortName = "v17";
    public const string Sql = """
        SELECT
          v17.[Businessentityid],
          v17.[Name],
          v17.[Addresstype],
          v17.[Addressline1],
          v17.[Addressline2],
          v17.[City],
          v17.[Stateprovincename],
          v17.[Postalcode],
          v17.[Countryregionname]
        FROM
          [Sales].[vStoreWithAddresses] v17
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int ADDRESSTYPE_FIELD_ID = 2;
    public const int ADDRESSLINE1_FIELD_ID = 3;
    public const int ADDRESSLINE2_FIELD_ID = 4;
    public const int CITY_FIELD_ID = 5;
    public const int STATEPROVINCENAME_FIELD_ID = 6;
    public const int POSTALCODE_FIELD_ID = 7;
    public const int COUNTRYREGIONNAME_FIELD_ID = 8;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VstorewithaddressesReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Addresstype
    {
        get
        {
            return Reader.GetString(ADDRESSTYPE_FIELD_ID);
        }
    }

    public string Addressline1
    {
        get
        {
            return Reader.GetString(ADDRESSLINE1_FIELD_ID);
        }
    }

    public string? Addressline2
    {
        get
        {
            return Reader.GetNullableString(ADDRESSLINE2_FIELD_ID);
        }
    }

    public string City
    {
        get
        {
            return Reader.GetString(CITY_FIELD_ID);
        }
    }

    public string Stateprovincename
    {
        get
        {
            return Reader.GetString(STATEPROVINCENAME_FIELD_ID);
        }
    }

    public string Postalcode
    {
        get
        {
            return Reader.GetString(POSTALCODE_FIELD_ID);
        }
    }

    public string Countryregionname
    {
        get
        {
            return Reader.GetString(COUNTRYREGIONNAME_FIELD_ID);
        }
    }


    public Types.Sales.VstorewithaddressesDataType ToDataObject()
    {
        return new Types.Sales.VstorewithaddressesDataType(Businessentityid,
            Name,
            Addresstype,
            Addressline1,
            Addressline2,
            City,
            Stateprovincename,
            Postalcode,
            Countryregionname);
    }

    public List<Types.Sales.VstorewithaddressesDataType> ToList()
    {
        var list = new List<Types.Sales.VstorewithaddressesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
