using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.HumanResources;

public class VjobcandidateeducationDataType
{
    readonly int _jobcandidateid = 0;
    readonly string? _edu_level;
    readonly DateTime? _edu_startdate;
    readonly DateTime? _edu_enddate;
    readonly string? _edu_degree;
    readonly string? _edu_major;
    readonly string? _edu_minor;
    readonly string? _edu_gpa;
    readonly string? _edu_gpascale;
    readonly string? _edu_school;
    readonly string? _edu_loc_countryregion;
    readonly string? _edu_loc_state;
    readonly string? _edu_loc_city;

    public VjobcandidateeducationDataType( )
    {
    }

    public VjobcandidateeducationDataType(int jobcandidateid,
        string? edu_level,
        DateTime? edu_startdate,
        DateTime? edu_enddate,
        string? edu_degree,
        string? edu_major,
        string? edu_minor,
        string? edu_gpa,
        string? edu_gpascale,
        string? edu_school,
        string? edu_loc_countryregion,
        string? edu_loc_state,
        string? edu_loc_city)
    {
        _jobcandidateid = jobcandidateid;
        _edu_level = edu_level;
        _edu_startdate = edu_startdate;
        _edu_enddate = edu_enddate;
        _edu_degree = edu_degree;
        _edu_major = edu_major;
        _edu_minor = edu_minor;
        _edu_gpa = edu_gpa;
        _edu_gpascale = edu_gpascale;
        _edu_school = edu_school;
        _edu_loc_countryregion = edu_loc_countryregion;
        _edu_loc_state = edu_loc_state;
        _edu_loc_city = edu_loc_city;
    }

    public int Jobcandidateid => _jobcandidateid;
    public string? Edu_level => _edu_level;
    public DateTime? Edu_startdate => _edu_startdate;
    public DateTime? Edu_enddate => _edu_enddate;
    public string? Edu_degree => _edu_degree;
    public string? Edu_major => _edu_major;
    public string? Edu_minor => _edu_minor;
    public string? Edu_gpa => _edu_gpa;
    public string? Edu_gpascale => _edu_gpascale;
    public string? Edu_school => _edu_school;
    public string? Edu_loc_countryregion => _edu_loc_countryregion;
    public string? Edu_loc_state => _edu_loc_state;
    public string? Edu_loc_city => _edu_loc_city;
}
