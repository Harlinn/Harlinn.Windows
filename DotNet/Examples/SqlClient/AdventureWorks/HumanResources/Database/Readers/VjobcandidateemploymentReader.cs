/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.HumanResources.Database.Readers;

public class VjobcandidateemploymentReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[vJobCandidateEmployment]";
    public const string TableName = "vJobCandidateEmployment";
    public const string ShortName = "v4";
    public const string Sql = """
        SELECT
          v4.[Jobcandidateid],
          v4.[Emp.startdate],
          v4.[Emp.enddate],
          v4.[Emp.orgname],
          v4.[Emp.jobtitle],
          v4.[Emp.responsibility],
          v4.[Emp.functioncategory],
          v4.[Emp.industrycategory],
          v4.[Emp.loc.countryregion],
          v4.[Emp.loc.state],
          v4.[Emp.loc.city]
        FROM
          [HumanResources].[vJobCandidateEmployment] v4
        """;

    public const int JOBCANDIDATEID_FIELD_ID = 0;
    public const int EMP_STARTDATE_FIELD_ID = 1;
    public const int EMP_ENDDATE_FIELD_ID = 2;
    public const int EMP_ORGNAME_FIELD_ID = 3;
    public const int EMP_JOBTITLE_FIELD_ID = 4;
    public const int EMP_RESPONSIBILITY_FIELD_ID = 5;
    public const int EMP_FUNCTIONCATEGORY_FIELD_ID = 6;
    public const int EMP_INDUSTRYCATEGORY_FIELD_ID = 7;
    public const int EMP_LOC_COUNTRYREGION_FIELD_ID = 8;
    public const int EMP_LOC_STATE_FIELD_ID = 9;
    public const int EMP_LOC_CITY_FIELD_ID = 10;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VjobcandidateemploymentReader(SqlDataReader reader, bool ownsReader = false)
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

    public DateTime? Emp_startdate
    {
        get
        {
            return Reader.GetNullableDateTime(EMP_STARTDATE_FIELD_ID);
        }
    }

    public DateTime? Emp_enddate
    {
        get
        {
            return Reader.GetNullableDateTime(EMP_ENDDATE_FIELD_ID);
        }
    }

    public string? Emp_orgname
    {
        get
        {
            return Reader.GetNullableString(EMP_ORGNAME_FIELD_ID);
        }
    }

    public string? Emp_jobtitle
    {
        get
        {
            return Reader.GetNullableString(EMP_JOBTITLE_FIELD_ID);
        }
    }

    public string? Emp_responsibility
    {
        get
        {
            return Reader.GetNullableString(EMP_RESPONSIBILITY_FIELD_ID);
        }
    }

    public string? Emp_functioncategory
    {
        get
        {
            return Reader.GetNullableString(EMP_FUNCTIONCATEGORY_FIELD_ID);
        }
    }

    public string? Emp_industrycategory
    {
        get
        {
            return Reader.GetNullableString(EMP_INDUSTRYCATEGORY_FIELD_ID);
        }
    }

    public string? Emp_loc_countryregion
    {
        get
        {
            return Reader.GetNullableString(EMP_LOC_COUNTRYREGION_FIELD_ID);
        }
    }

    public string? Emp_loc_state
    {
        get
        {
            return Reader.GetNullableString(EMP_LOC_STATE_FIELD_ID);
        }
    }

    public string? Emp_loc_city
    {
        get
        {
            return Reader.GetNullableString(EMP_LOC_CITY_FIELD_ID);
        }
    }


    public AdventureWorks.HumanResources.Types.VjobcandidateemploymentDataType ToDataObject()
    {
        return new AdventureWorks.HumanResources.Types.VjobcandidateemploymentDataType(Jobcandidateid,
            Emp_startdate,
            Emp_enddate,
            Emp_orgname,
            Emp_jobtitle,
            Emp_responsibility,
            Emp_functioncategory,
            Emp_industrycategory,
            Emp_loc_countryregion,
            Emp_loc_state,
            Emp_loc_city);
    }

    public List<AdventureWorks.HumanResources.Types.VjobcandidateemploymentDataType> ToList()
    {
        var list = new List<AdventureWorks.HumanResources.Types.VjobcandidateemploymentDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
