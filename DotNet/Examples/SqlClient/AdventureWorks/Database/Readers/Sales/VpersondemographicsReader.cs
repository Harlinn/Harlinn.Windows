using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Sales;

public class VpersondemographicsReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[vPersonDemographics]";
    public const string TableName = "vPersonDemographics";
    public const string ShortName = "v14";
    public const string Sql = """
        SELECT
          v14.[Businessentityid],
          v14.[Totalpurchaseytd],
          v14.[Datefirstpurchase],
          v14.[Birthdate],
          v14.[Maritalstatus],
          v14.[Yearlyincome],
          v14.[Gender],
          v14.[Totalchildren],
          v14.[Numberchildrenathome],
          v14.[Education],
          v14.[Occupation],
          v14.[Homeownerflag],
          v14.[Numbercarsowned]
        FROM
          [Sales].[vPersonDemographics] v14
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int TOTALPURCHASEYTD_FIELD_ID = 1;
    public const int DATEFIRSTPURCHASE_FIELD_ID = 2;
    public const int BIRTHDATE_FIELD_ID = 3;
    public const int MARITALSTATUS_FIELD_ID = 4;
    public const int YEARLYINCOME_FIELD_ID = 5;
    public const int GENDER_FIELD_ID = 6;
    public const int TOTALCHILDREN_FIELD_ID = 7;
    public const int NUMBERCHILDRENATHOME_FIELD_ID = 8;
    public const int EDUCATION_FIELD_ID = 9;
    public const int OCCUPATION_FIELD_ID = 10;
    public const int HOMEOWNERFLAG_FIELD_ID = 11;
    public const int NUMBERCARSOWNED_FIELD_ID = 12;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VpersondemographicsReader(SqlDataReader reader, bool ownsReader = false)
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

    public decimal? Totalpurchaseytd
    {
        get
        {
            return Reader.GetNullableDecimal(TOTALPURCHASEYTD_FIELD_ID);
        }
    }

    public DateTime? Datefirstpurchase
    {
        get
        {
            return Reader.GetNullableDateTime(DATEFIRSTPURCHASE_FIELD_ID);
        }
    }

    public DateTime? Birthdate
    {
        get
        {
            return Reader.GetNullableDateTime(BIRTHDATE_FIELD_ID);
        }
    }

    public string? Maritalstatus
    {
        get
        {
            return Reader.GetNullableString(MARITALSTATUS_FIELD_ID);
        }
    }

    public string? Yearlyincome
    {
        get
        {
            return Reader.GetNullableString(YEARLYINCOME_FIELD_ID);
        }
    }

    public string? Gender
    {
        get
        {
            return Reader.GetNullableString(GENDER_FIELD_ID);
        }
    }

    public int? Totalchildren
    {
        get
        {
            return Reader.GetNullableInt32(TOTALCHILDREN_FIELD_ID);
        }
    }

    public int? Numberchildrenathome
    {
        get
        {
            return Reader.GetNullableInt32(NUMBERCHILDRENATHOME_FIELD_ID);
        }
    }

    public string? Education
    {
        get
        {
            return Reader.GetNullableString(EDUCATION_FIELD_ID);
        }
    }

    public string? Occupation
    {
        get
        {
            return Reader.GetNullableString(OCCUPATION_FIELD_ID);
        }
    }

    public bool? Homeownerflag
    {
        get
        {
            return Reader.GetNullableBoolean(HOMEOWNERFLAG_FIELD_ID);
        }
    }

    public int? Numbercarsowned
    {
        get
        {
            return Reader.GetNullableInt32(NUMBERCARSOWNED_FIELD_ID);
        }
    }


    public Types.Sales.VpersondemographicsDataType ToDataObject()
    {
        return new Types.Sales.VpersondemographicsDataType(Businessentityid,
            Totalpurchaseytd,
            Datefirstpurchase,
            Birthdate,
            Maritalstatus,
            Yearlyincome,
            Gender,
            Totalchildren,
            Numberchildrenathome,
            Education,
            Occupation,
            Homeownerflag,
            Numbercarsowned);
    }

    public List<Types.Sales.VpersondemographicsDataType> ToList()
    {
        var list = new List<Types.Sales.VpersondemographicsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
