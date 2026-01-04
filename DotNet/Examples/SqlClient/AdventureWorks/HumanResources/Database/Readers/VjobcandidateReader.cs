using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.HumanResources.Database.Readers;

public class VjobcandidateReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[vJobCandidate]";
    public const string TableName = "vJobCandidate";
    public const string ShortName = "v2";
    public const string Sql = """
        SELECT
          v2.[Jobcandidateid],
          v2.[Businessentityid],
          v2.[Name.prefix],
          v2.[Name.first],
          v2.[Name.middle],
          v2.[Name.last],
          v2.[Name.suffix],
          v2.[Skills],
          v2.[Addr.type],
          v2.[Addr.loc.countryregion],
          v2.[Addr.loc.state],
          v2.[Addr.loc.city],
          v2.[Addr.postalcode],
          v2.[Email],
          v2.[Website],
          v2.[Modifieddate]
        FROM
          [HumanResources].[vJobCandidate] v2
        """;

    public const int JOBCANDIDATEID_FIELD_ID = 0;
    public const int BUSINESSENTITYID_FIELD_ID = 1;
    public const int NAME_PREFIX_FIELD_ID = 2;
    public const int NAME_FIRST_FIELD_ID = 3;
    public const int NAME_MIDDLE_FIELD_ID = 4;
    public const int NAME_LAST_FIELD_ID = 5;
    public const int NAME_SUFFIX_FIELD_ID = 6;
    public const int SKILLS_FIELD_ID = 7;
    public const int ADDR_TYPE_FIELD_ID = 8;
    public const int ADDR_LOC_COUNTRYREGION_FIELD_ID = 9;
    public const int ADDR_LOC_STATE_FIELD_ID = 10;
    public const int ADDR_LOC_CITY_FIELD_ID = 11;
    public const int ADDR_POSTALCODE_FIELD_ID = 12;
    public const int EMAIL_FIELD_ID = 13;
    public const int WEBSITE_FIELD_ID = 14;
    public const int MODIFIEDDATE_FIELD_ID = 15;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VjobcandidateReader(SqlDataReader reader, bool ownsReader = false)
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

    public int? Businessentityid
    {
        get
        {
            return Reader.GetNullableInt32(BUSINESSENTITYID_FIELD_ID);
        }
    }

    public string? Name_prefix
    {
        get
        {
            return Reader.GetNullableString(NAME_PREFIX_FIELD_ID);
        }
    }

    public string? Name_first
    {
        get
        {
            return Reader.GetNullableString(NAME_FIRST_FIELD_ID);
        }
    }

    public string? Name_middle
    {
        get
        {
            return Reader.GetNullableString(NAME_MIDDLE_FIELD_ID);
        }
    }

    public string? Name_last
    {
        get
        {
            return Reader.GetNullableString(NAME_LAST_FIELD_ID);
        }
    }

    public string? Name_suffix
    {
        get
        {
            return Reader.GetNullableString(NAME_SUFFIX_FIELD_ID);
        }
    }

    public string? Skills
    {
        get
        {
            return Reader.GetNullableString(SKILLS_FIELD_ID);
        }
    }

    public string? Addr_type
    {
        get
        {
            return Reader.GetNullableString(ADDR_TYPE_FIELD_ID);
        }
    }

    public string? Addr_loc_countryregion
    {
        get
        {
            return Reader.GetNullableString(ADDR_LOC_COUNTRYREGION_FIELD_ID);
        }
    }

    public string? Addr_loc_state
    {
        get
        {
            return Reader.GetNullableString(ADDR_LOC_STATE_FIELD_ID);
        }
    }

    public string? Addr_loc_city
    {
        get
        {
            return Reader.GetNullableString(ADDR_LOC_CITY_FIELD_ID);
        }
    }

    public string? Addr_postalcode
    {
        get
        {
            return Reader.GetNullableString(ADDR_POSTALCODE_FIELD_ID);
        }
    }

    public string? Email
    {
        get
        {
            return Reader.GetNullableString(EMAIL_FIELD_ID);
        }
    }

    public string? Website
    {
        get
        {
            return Reader.GetNullableString(WEBSITE_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.HumanResources.Types.VjobcandidateDataType ToDataObject()
    {
        return new AdventureWorks.HumanResources.Types.VjobcandidateDataType(Jobcandidateid,
            Businessentityid,
            Name_prefix,
            Name_first,
            Name_middle,
            Name_last,
            Name_suffix,
            Skills,
            Addr_type,
            Addr_loc_countryregion,
            Addr_loc_state,
            Addr_loc_city,
            Addr_postalcode,
            Email,
            Website,
            Modifieddate);
    }

    public List<AdventureWorks.HumanResources.Types.VjobcandidateDataType> ToList()
    {
        var list = new List<AdventureWorks.HumanResources.Types.VjobcandidateDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
