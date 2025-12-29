using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

namespace AdventureWorks.Types.HumanResources;

public class VjobcandidateDataType
{
    readonly int _jobcandidateid = 0;
    readonly int? _businessentityid;
    readonly string? _name_prefix;
    readonly string? _name_first;
    readonly string? _name_middle;
    readonly string? _name_last;
    readonly string? _name_suffix;
    readonly string? _skills;
    readonly string? _addr_type;
    readonly string? _addr_loc_countryregion;
    readonly string? _addr_loc_state;
    readonly string? _addr_loc_city;
    readonly string? _addr_postalcode;
    readonly string? _email;
    readonly string? _website;
    readonly DateTime _modifieddate;

    public VjobcandidateDataType( )
    {
    }

    public VjobcandidateDataType(int jobcandidateid,
        int? businessentityid,
        string? name_prefix,
        string? name_first,
        string? name_middle,
        string? name_last,
        string? name_suffix,
        string? skills,
        string? addr_type,
        string? addr_loc_countryregion,
        string? addr_loc_state,
        string? addr_loc_city,
        string? addr_postalcode,
        string? email,
        string? website,
        DateTime modifieddate)
    {
        _jobcandidateid = jobcandidateid;
        _businessentityid = businessentityid;
        _name_prefix = name_prefix;
        _name_first = name_first;
        _name_middle = name_middle;
        _name_last = name_last;
        _name_suffix = name_suffix;
        _skills = skills;
        _addr_type = addr_type;
        _addr_loc_countryregion = addr_loc_countryregion;
        _addr_loc_state = addr_loc_state;
        _addr_loc_city = addr_loc_city;
        _addr_postalcode = addr_postalcode;
        _email = email;
        _website = website;
        _modifieddate = modifieddate;
    }

    public int Jobcandidateid => _jobcandidateid;
    public int? Businessentityid => _businessentityid;
    public string? Name_prefix => _name_prefix;
    public string? Name_first => _name_first;
    public string? Name_middle => _name_middle;
    public string? Name_last => _name_last;
    public string? Name_suffix => _name_suffix;
    public string? Skills => _skills;
    public string? Addr_type => _addr_type;
    public string? Addr_loc_countryregion => _addr_loc_countryregion;
    public string? Addr_loc_state => _addr_loc_state;
    public string? Addr_loc_city => _addr_loc_city;
    public string? Addr_postalcode => _addr_postalcode;
    public string? Email => _email;
    public string? Website => _website;
    public DateTime Modifieddate => _modifieddate;
}
