using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Sales.Database.Readers;

public class VstorewithdemographicsReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[vStoreWithDemographics]";
    public const string TableName = "vStoreWithDemographics";
    public const string ShortName = "v19";
    public const string Sql = """
        SELECT
          v19.[Businessentityid],
          v19.[Name],
          v19.[Annualsales],
          v19.[Annualrevenue],
          v19.[Bankname],
          v19.[Businesstype],
          v19.[Yearopened],
          v19.[Specialty],
          v19.[Squarefeet],
          v19.[Brands],
          v19.[Internet],
          v19.[Numberemployees]
        FROM
          [Sales].[vStoreWithDemographics] v19
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int ANNUALSALES_FIELD_ID = 2;
    public const int ANNUALREVENUE_FIELD_ID = 3;
    public const int BANKNAME_FIELD_ID = 4;
    public const int BUSINESSTYPE_FIELD_ID = 5;
    public const int YEAROPENED_FIELD_ID = 6;
    public const int SPECIALTY_FIELD_ID = 7;
    public const int SQUAREFEET_FIELD_ID = 8;
    public const int BRANDS_FIELD_ID = 9;
    public const int INTERNET_FIELD_ID = 10;
    public const int NUMBEREMPLOYEES_FIELD_ID = 11;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VstorewithdemographicsReader(SqlDataReader reader, bool ownsReader = false)
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

    public decimal? Annualsales
    {
        get
        {
            return Reader.GetNullableDecimal(ANNUALSALES_FIELD_ID);
        }
    }

    public decimal? Annualrevenue
    {
        get
        {
            return Reader.GetNullableDecimal(ANNUALREVENUE_FIELD_ID);
        }
    }

    public string? Bankname
    {
        get
        {
            return Reader.GetNullableString(BANKNAME_FIELD_ID);
        }
    }

    public string? Businesstype
    {
        get
        {
            return Reader.GetNullableString(BUSINESSTYPE_FIELD_ID);
        }
    }

    public int? Yearopened
    {
        get
        {
            return Reader.GetNullableInt32(YEAROPENED_FIELD_ID);
        }
    }

    public string? Specialty
    {
        get
        {
            return Reader.GetNullableString(SPECIALTY_FIELD_ID);
        }
    }

    public int? Squarefeet
    {
        get
        {
            return Reader.GetNullableInt32(SQUAREFEET_FIELD_ID);
        }
    }

    public string? Brands
    {
        get
        {
            return Reader.GetNullableString(BRANDS_FIELD_ID);
        }
    }

    public string? Internet
    {
        get
        {
            return Reader.GetNullableString(INTERNET_FIELD_ID);
        }
    }

    public int? Numberemployees
    {
        get
        {
            return Reader.GetNullableInt32(NUMBEREMPLOYEES_FIELD_ID);
        }
    }


    public AdventureWorks.Sales.Types.VstorewithdemographicsDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.VstorewithdemographicsDataType(Businessentityid,
            Name,
            Annualsales,
            Annualrevenue,
            Bankname,
            Businesstype,
            Yearopened,
            Specialty,
            Squarefeet,
            Brands,
            Internet,
            Numberemployees);
    }

    public List<AdventureWorks.Sales.Types.VstorewithdemographicsDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.VstorewithdemographicsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
