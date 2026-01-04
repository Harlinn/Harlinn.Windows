using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.HumanResources.Database.Readers;

public class VjobcandidateeducationReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[vJobCandidateEducation]";
    public const string TableName = "vJobCandidateEducation";
    public const string ShortName = "v3";
    public const string Sql = """
        SELECT
          v3.[Jobcandidateid],
          v3.[Edu.level],
          v3.[Edu.startdate],
          v3.[Edu.enddate],
          v3.[Edu.degree],
          v3.[Edu.major],
          v3.[Edu.minor],
          v3.[Edu.gpa],
          v3.[Edu.gpascale],
          v3.[Edu.school],
          v3.[Edu.loc.countryregion],
          v3.[Edu.loc.state],
          v3.[Edu.loc.city]
        FROM
          [HumanResources].[vJobCandidateEducation] v3
        """;

    public const int JOBCANDIDATEID_FIELD_ID = 0;
    public const int EDU_LEVEL_FIELD_ID = 1;
    public const int EDU_STARTDATE_FIELD_ID = 2;
    public const int EDU_ENDDATE_FIELD_ID = 3;
    public const int EDU_DEGREE_FIELD_ID = 4;
    public const int EDU_MAJOR_FIELD_ID = 5;
    public const int EDU_MINOR_FIELD_ID = 6;
    public const int EDU_GPA_FIELD_ID = 7;
    public const int EDU_GPASCALE_FIELD_ID = 8;
    public const int EDU_SCHOOL_FIELD_ID = 9;
    public const int EDU_LOC_COUNTRYREGION_FIELD_ID = 10;
    public const int EDU_LOC_STATE_FIELD_ID = 11;
    public const int EDU_LOC_CITY_FIELD_ID = 12;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VjobcandidateeducationReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Jobcandidateid
    {
        get
        {
            return Reader.GetInt32(JOBCANDIDATEID_FIELD_ID);
        }
    }

    public string? Edu_level
    {
        get
        {
            return Reader.GetNullableString(EDU_LEVEL_FIELD_ID);
        }
    }

    public DateTime? Edu_startdate
    {
        get
        {
            return Reader.GetNullableDateTime(EDU_STARTDATE_FIELD_ID);
        }
    }

    public DateTime? Edu_enddate
    {
        get
        {
            return Reader.GetNullableDateTime(EDU_ENDDATE_FIELD_ID);
        }
    }

    public string? Edu_degree
    {
        get
        {
            return Reader.GetNullableString(EDU_DEGREE_FIELD_ID);
        }
    }

    public string? Edu_major
    {
        get
        {
            return Reader.GetNullableString(EDU_MAJOR_FIELD_ID);
        }
    }

    public string? Edu_minor
    {
        get
        {
            return Reader.GetNullableString(EDU_MINOR_FIELD_ID);
        }
    }

    public string? Edu_gpa
    {
        get
        {
            return Reader.GetNullableString(EDU_GPA_FIELD_ID);
        }
    }

    public string? Edu_gpascale
    {
        get
        {
            return Reader.GetNullableString(EDU_GPASCALE_FIELD_ID);
        }
    }

    public string? Edu_school
    {
        get
        {
            return Reader.GetNullableString(EDU_SCHOOL_FIELD_ID);
        }
    }

    public string? Edu_loc_countryregion
    {
        get
        {
            return Reader.GetNullableString(EDU_LOC_COUNTRYREGION_FIELD_ID);
        }
    }

    public string? Edu_loc_state
    {
        get
        {
            return Reader.GetNullableString(EDU_LOC_STATE_FIELD_ID);
        }
    }

    public string? Edu_loc_city
    {
        get
        {
            return Reader.GetNullableString(EDU_LOC_CITY_FIELD_ID);
        }
    }


    public AdventureWorks.HumanResources.Types.VjobcandidateeducationDataType ToDataObject()
    {
        return new AdventureWorks.HumanResources.Types.VjobcandidateeducationDataType(Jobcandidateid,
            Edu_level,
            Edu_startdate,
            Edu_enddate,
            Edu_degree,
            Edu_major,
            Edu_minor,
            Edu_gpa,
            Edu_gpascale,
            Edu_school,
            Edu_loc_countryregion,
            Edu_loc_state,
            Edu_loc_city);
    }

    public List<AdventureWorks.HumanResources.Types.VjobcandidateeducationDataType> ToList()
    {
        var list = new List<AdventureWorks.HumanResources.Types.VjobcandidateeducationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
