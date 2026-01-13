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
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.HumanResources.Types;

public class VjobcandidateemploymentDataType
{
    readonly int _jobcandidateid = 0;
    readonly DateTime? _emp_startdate;
    readonly DateTime? _emp_enddate;
    readonly string? _emp_orgname;
    readonly string? _emp_jobtitle;
    readonly string? _emp_responsibility;
    readonly string? _emp_functioncategory;
    readonly string? _emp_industrycategory;
    readonly string? _emp_loc_countryregion;
    readonly string? _emp_loc_state;
    readonly string? _emp_loc_city;

    public VjobcandidateemploymentDataType( )
    {
    }

    public VjobcandidateemploymentDataType(int jobcandidateid,
        DateTime? emp_startdate,
        DateTime? emp_enddate,
        string? emp_orgname,
        string? emp_jobtitle,
        string? emp_responsibility,
        string? emp_functioncategory,
        string? emp_industrycategory,
        string? emp_loc_countryregion,
        string? emp_loc_state,
        string? emp_loc_city)
    {
        _jobcandidateid = jobcandidateid;
        _emp_startdate = emp_startdate;
        _emp_enddate = emp_enddate;
        _emp_orgname = emp_orgname;
        _emp_jobtitle = emp_jobtitle;
        _emp_responsibility = emp_responsibility;
        _emp_functioncategory = emp_functioncategory;
        _emp_industrycategory = emp_industrycategory;
        _emp_loc_countryregion = emp_loc_countryregion;
        _emp_loc_state = emp_loc_state;
        _emp_loc_city = emp_loc_city;
    }

    public int Jobcandidateid => _jobcandidateid;
    public DateTime? Emp_startdate => _emp_startdate;
    public DateTime? Emp_enddate => _emp_enddate;
    public string? Emp_orgname => _emp_orgname;
    public string? Emp_jobtitle => _emp_jobtitle;
    public string? Emp_responsibility => _emp_responsibility;
    public string? Emp_functioncategory => _emp_functioncategory;
    public string? Emp_industrycategory => _emp_industrycategory;
    public string? Emp_loc_countryregion => _emp_loc_countryregion;
    public string? Emp_loc_state => _emp_loc_state;
    public string? Emp_loc_city => _emp_loc_city;
}
